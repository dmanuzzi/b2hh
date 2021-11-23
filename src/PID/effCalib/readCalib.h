bool applyCutK(double &dllkpi, double &dllppi, int &cut1, int &cut2) {

  if(dllkpi > cut1 && dllkpi-dllppi > cut2) return true;
  else                                      return false;

}

bool applyCutPI(double &dllkpi, double &dllppi, int &cut1, int &cut2) {

  if(dllkpi < cut1 && dllppi < cut2) return true;
  else                               return false;

}

bool applyCutP(double &dllkpi, double &dllppi, int &cut1, int &cut2) {

  if(dllppi > cut1 && dllppi-dllkpi > cut2) return true;
  else                                      return false;

}

bool readCalibrationData(TString &decay, TString &particle, TString &charge,
                         double * eff, double * effErr, TString &cuts, TString &magnet, TString &year,
                         binScheme &binX,binScheme &binY, binScheme &binZ, binScheme &binT) {

  TString fileName;

  TString calDataDir = "${B2HH_OUT}/PID/prepareCalib/PIDcalibLists";
  TChain * calTree = new TChain(Form("%s%s_tot",particle.Data(),charge.Data()));
  TFileCollection * fileList = new TFileCollection("fileList","fileList",
                                                   Form("%s/list_%s%s_%s_%s.txt",calDataDir.Data(),
                                                                                 particle.Data(),charge.Data(),
                                                                                 magnet.Data(),year.Data()));
  calTree->AddFileInfoList((TCollection *)fileList->GetList());
  calTree->SetBranchStatus("*",0);
  calTree->SetBranchStatus(binX.name, 1);
  calTree->SetBranchStatus(binY.name, 1);
  calTree->SetBranchStatus(binZ.name, 1);
  calTree->SetBranchStatus(binT.name, 1);
  calTree->SetBranchStatus("DLLKPI",  1);
  calTree->SetBranchStatus("DLLPPI",  1);
  calTree->SetBranchStatus("weight",  1);

  TString Cut1 = ((TObjString *)cuts.Tokenize('.')->At(0))->String();
  TString Cut2 = ((TObjString *)cuts.Tokenize('.')->At(1))->String();
  int cut1 = Cut1.Atoi(); int cut2 = Cut2.Atoi();

  bool (*applyCut)(double &, double &, int &, int &) = 0;
  if     (decay=="K")  applyCut = &applyCutK; 
  else if(decay=="PI") applyCut = &applyCutPI;
  else if(decay=="P")  applyCut = &applyCutP; 
/*
  auto applyCut =  decay == "K"  ? [](double &dllkpi, double &dllppi int &cut1, int &cut2) {
                                     return (dllkpi > cut1 && dllkpi-dllppi > cut2);} :
                   decay == "PI" ? [](double &dllkpi, double &dllppi int &cut1, int &cut2) {
                                     return (dllkpi < cut1 && dllppi < cut2);} :
                   decay == "P"  ? [](double &dllkpi, double &dllppi int &cut1, int &cut2) {
                                     return (dllppi > cut1 && dllppi-dllkpi > cut2);} :
                   return NULL;
  if(!applyCut) {printf("PARTILCE HYPOTHESIS NOT RECOGNISED FOR applyCut FUNCTION\n"); exit(); }
*/
  double x = 0, y = 0, z = 0, wgt = 0;
  double dllkpi = 0, dllppi = 0;
  int t = 0;
  calTree->SetBranchAddress(binX.name, &x        );
  calTree->SetBranchAddress(binY.name, &y        );
  calTree->SetBranchAddress(binZ.name, &z        );
  calTree->SetBranchAddress(binT.name, &t        );
  calTree->SetBranchAddress("DLLKPI",  &dllkpi   );
  calTree->SetBranchAddress("DLLPPI",  &dllppi   );
  calTree->SetBranchAddress("weight",  &wgt      );

  printf("READING CALIBRATION FROM %s/list_%s%s_%s_%s.txt\n",calDataDir.Data(),
                                                             particle.Data(),charge.Data(),
                                                             magnet.Data(),year.Data());

  int nBinsX = (int)binX.intervals.size();
  int nBinsY = (int)binY.intervals.size();
  int nBinsZ = (int)binZ.intervals.size();
  int nBinsT = (int)binT.intervals.size();
  int currentBin = 0;
  double norm[nBinsX][nBinsY][nBinsZ][nBinsT];
  double notPass[nBinsX][nBinsY][nBinsZ][nBinsT];
  double notPass2[nBinsX][nBinsY][nBinsZ][nBinsT];
  int iX = 0, iY = 0, iZ = 0, iT = 0;
  for(iX = 0; iX < nBinsX; iX++)
    for(iY = 0; iY < nBinsY; iY++)
      for(iZ = 0; iZ < nBinsZ; iZ++)
        for(iT = 0; iT < nBinsT; iT++) {
          norm[iX][iY][iZ][iT] = 0;
          notPass[iX][iY][iZ][iT] = 0;
          notPass2[iX][iY][iZ][iT] = 0;
        }

  for(int ientry = 0, nentries = calTree->GetEntries(); ientry < nentries; ++ientry) {
    calTree->GetEntry(ientry);

    if(!(x>=binX.start && x<binX.end &&
         y>=binY.start && y<binY.end &&
         z>=binZ.start && z<binZ.end &&
         t>=binT.start && t<binT.end)) continue;

    iX = findBin(x,binX); iY = findBin(y,binY);
    iZ = findBin(z,binZ); iT = findBin(t,binT);
    currentBin = iX*nBinsY*nBinsZ*nBinsT+iY*nBinsZ*nBinsT+iZ*nBinsT+iT;

    norm[iX][iY][iZ][iT] += wgt;
    if(applyCut(dllkpi,dllppi,cut1,cut2)) {
      eff[currentBin] += wgt;
      effErr[currentBin] += wgt*wgt;
    }
    else {
      notPass[iX][iY][iZ][iT]  += wgt; 
      notPass2[iX][iY][iZ][iT] += wgt*wgt; 
    }
  }

  for(iX = 0; iX < nBinsX; iX++)
    for(iY = 0; iY < nBinsY; iY++)
      for(iZ = 0; iZ < nBinsZ; iZ++)
        for(iT = 0; iT < nBinsT; iT++) {
          currentBin = iX*nBinsY*nBinsZ*nBinsT+iY*nBinsZ*nBinsT+iZ*nBinsT+iT;
          if     (norm[iX][iY][iZ][iT]<=0)  { eff[currentBin] = 0; effErr[currentBin] = 0; }
          else {
            effErr[currentBin] = sqrt(effErr[currentBin]*notPass[iX][iY][iZ][iT]*notPass[iX][iY][iZ][iT]+
                                      notPass2[iX][iY][iZ][iT]*eff[currentBin]*eff[currentBin]);
            effErr[currentBin]/=(norm[iX][iY][iZ][iT]*norm[iX][iY][iZ][iT]);      
            eff[currentBin] /= norm[iX][iY][iZ][iT];
          }
        }
  return true;

}

bool reweightTracks(double * eff, double * effRew,double * effErr, double * effErrRew,
                    binScheme &binX, binScheme &binY, binScheme &binZ, binScheme &binT,
                    TString &magnet, TString &year) {

  TFile * trackFile = new TFile(Form("${B2HH_OUT}/PID/effCalib/results/nSPD_sWeight_PIPI_0.2_%s_%s.root",magnet.Data(),year.Data()),"READ");
  TH1D * hTRK = (TH1D *) trackFile->Get("hB2HH");
  //correct negative bins
  for (int i=1; i<=hTRK->GetNbinsX(); ++i){
    double tmp_v = hTRK->GetBinContent(i);
    if (tmp_v<0.) {
      printf("WARNING: in histogram \"%s\", bin n. is negative -> Value forced to 0.\n ", hTRK->GetName());
      hTRK->SetBinContent(i,0.);
    }
  }


  int nBinsX = (int) binX.intervals.size();
  int nBinsY = (int) binY.intervals.size();
  int nBinsZ = (int) binZ.intervals.size();
  int nBinsT = (int) binT.intervals.size();

  double fractions[nBinsX][nBinsY][nBinsZ][nBinsT];
  int currentBin = 0, currentBinTrack = 0;
  double currTrack = 0;
  int nExtractions = 1000000;
  int iX = 0, iY = 0, iZ = 0, iT = 0;
  for(iX = 0; iX < nBinsX; iX++) {
    for(iY = 0; iY < nBinsY; iY++) {
      for(iZ = 0; iZ < nBinsZ; iZ++) {
        currentBin = iX*nBinsY*nBinsZ+iY*nBinsZ+iZ;

        // Initializing fractions to 0
        for(iT = 0; iT < nBinsT; iT++) 
          fractions[iX][iY][iZ][iT] = 0;

        for(int n = 0; n < nExtractions; n++) {

          currTrack = hTRK->GetRandom();
          if(currTrack > binT.end) { 
            n--; continue; }
          iT = findBin(currTrack,binT); 
          currentBinTrack = iX*nBinsY*nBinsZ*nBinsT+
                            iY*nBinsZ*nBinsT+
                            iZ*nBinsT+iT;
          effRew[currentBin] += eff[currentBinTrack];
          fractions[iX][iY][iZ][iT]++; // Filling fraction

        }
  
        // 
        for(iT = 0; iT < nBinsT; iT++) { 
          fractions[iX][iY][iZ][iT] /= nExtractions; // transforming fractions into weights

          // Actual computation of errors
          effErrRew[currentBin] += fractions[iX][iY][iZ][iT]*eff[currentBinTrack]*eff[currentBinTrack]/
                                   nExtractions;
          effErrRew[currentBin] += effErr[currentBinTrack]*effErr[currentBinTrack]*
                                   fractions[iX][iY][iZ][iT]*fractions[iX][iY][iZ][iT];
         
        }
        effRew[currentBin]/=nExtractions;
        effErrRew[currentBin] = sqrt(effErrRew[currentBin]); // Final error
      }
    }
  }
  trackFile->Close();

  return true;

}

