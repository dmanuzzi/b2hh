#include <vector>
#include <map>

#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>


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

void setNames(TString &decay, TString &finalState,
              TString &namePlus, TString &nameMinus) {

  if     (decay=="bdkpi")  { namePlus = "Kplus";  nameMinus = "PIminus"; }
  else if(decay=="bdpik")  { namePlus = "PIplus"; nameMinus = "Kminus";  }
  else if(decay=="bdpipi") { namePlus = "PIplus"; nameMinus = "PIminus"; }
  else if(decay=="bdkk")   { namePlus = "Kplus";  nameMinus = "Kminus";  }
  else if(decay=="bskk")   { namePlus = "Kplus";  nameMinus = "Kminus";  }
  else if(decay=="bskpi")  { namePlus = "Kplus";  nameMinus = "PIminus"; }
  else if(decay=="bspik")  { namePlus = "PIplus"; nameMinus = "Kminus";  }
  else if(decay=="bspipi") { namePlus = "PIplus"; nameMinus = "PIminus"; }
  else if(decay=="lbpk")   { namePlus = "Pplus";  nameMinus = "Kminus";  }
  else if(decay=="lbkp")   { namePlus = "Kplus";  nameMinus = "Pminus";  }
  else if(decay=="lbppi")  { namePlus = "Pplus";  nameMinus = "PIminus"; }
  else if(decay=="lbpip")  { namePlus = "PIplus"; nameMinus = "Pminus";  }

}
void setHypos(TString &decay, TString &finalState,
              TString &hypoPlus, TString &hypoMinus) {
  if     (finalState=="pipi") { hypoPlus = "PI"; hypoMinus = "PI"; }
  else if(finalState=="kpi")  { hypoPlus = "K";  hypoMinus = "PI"; }
  else if(finalState=="pik")  { hypoPlus = "PI"; hypoMinus = "K";  }
  else if(finalState=="kk")   { hypoPlus = "K";  hypoMinus = "K";  }
  else if(finalState=="pk")   { hypoPlus = "P";  hypoMinus = "K";  }
  else if(finalState=="kp")   { hypoPlus = "K";  hypoMinus = "P";  }
  else if(finalState=="ppi")  { hypoPlus = "P";  hypoMinus = "PI"; }
  else if(finalState=="pip")  { hypoPlus = "PI"; hypoMinus = "P";  }
}

bool readBMCData(TString &decay, TString &name, TString &finalState,TString &cuts, 
                 TString &magnet, TString &year,
                 TString &bdtCutName, TString &optimConf,
                 double &effFiducialPlusMC, double &effNoFiducialPlusMC,
                 double &effFiducialMinusMC,double &effNoFiducialMinusMC,
                 binScheme &binX, binScheme &binY, binScheme &binZ, binScheme &binT) {

  TString namePlus, nameMinus;
  setNames(decay,finalState,namePlus,nameMinus);
  bool (*applyCutPlus)(double &, double &, int &, int &)  = 0;
  bool (*applyCutMinus)(double &, double &, int &, int &) = 0;
  if     (finalState=="pipi") { applyCutPlus = applyCutPI; applyCutMinus = applyCutPI; }
  else if(finalState=="kpi")  { applyCutPlus = applyCutK;  applyCutMinus = applyCutPI; }
  else if(finalState=="pik")  { applyCutPlus = applyCutPI; applyCutMinus = applyCutK;  }
  else if(finalState=="kk")   { applyCutPlus = applyCutK;  applyCutMinus = applyCutK;  }
  else if(finalState=="pk")   { applyCutPlus = applyCutP;  applyCutMinus = applyCutK;  }
  else if(finalState=="kp")   { applyCutPlus = applyCutK;  applyCutMinus = applyCutP;  }
  else if(finalState=="ppi")  { applyCutPlus = applyCutP;  applyCutMinus = applyCutPI; }
  else if(finalState=="pip")  { applyCutPlus = applyCutPI; applyCutMinus = applyCutP;  }

  TChain *bTree = new TChain(decay, decay);
  auto tag_years = datasetFlags::chain_years[year];
  auto tag_magnet = datasetFlags::chain_magnet[magnet];
  chainAdder::chainAdder(bTree, "${B2HH_OUT}/Data/tuple_merged/%s_%s_%s.root/b2hh",
                         decay, tag_years, tag_magnet);

  bTree->SetBranchStatus("*",0);
  // VARIABLES FOR BDT
  bTree->SetBranchStatus(Form("bdt%s",optimConf.Data()),1);
  // VARIABLES FOR PID
  bTree->SetBranchStatus("piplus"+binX.name,1);
  bTree->SetBranchStatus("piplus"+binY.name,1);
  bTree->SetBranchStatus("piplus"+binZ.name,1);
  bTree->SetBranchStatus("piplusDLLKPI",1);
  bTree->SetBranchStatus("piplusDLLPPI",1);
  bTree->SetBranchStatus("piminus"+binX.name,1);
  bTree->SetBranchStatus("piminus"+binY.name,1);
  bTree->SetBranchStatus("piminus"+binZ.name,1);
  bTree->SetBranchStatus("piminusDLLKPI",1);
  bTree->SetBranchStatus("piminusDLLPPI",1);
  //bTree->SetBranchStatus("weight",1);

  TString CutPlus1  = ((TObjString *)cuts.Tokenize('.')->At(0))->String();
  TString CutPlus2  = ((TObjString *)cuts.Tokenize('.')->At(1))->String();
  TString CutMinus1 = ((TObjString *)cuts.Tokenize('.')->At(2))->String();
  TString CutMinus2 = ((TObjString *)cuts.Tokenize('.')->At(3))->String();
  int cutPlus1  = CutPlus1.Atoi();  int cutPlus2  = CutPlus2.Atoi();
  int cutMinus1 = CutMinus1.Atoi(); int cutMinus2 = CutMinus2.Atoi();

  Long64_t nentries = bTree->GetEntries();

  // VARIABLES FOR BDT
  Double_t BDT = 0;
  // VARIABLES FOR PID
  double plusX  = 0, plusY  = 0, plusZ  = 0, plusDLLKPI  = 0, plusDLLPPI  = 0,
         minusX = 0, minusY = 0, minusZ = 0, minusDLLKPI = 0, minusDLLPPI = 0,
         weight = 1;
  bTree->SetBranchAddress(Form("bdt%s",optimConf.Data()),&BDT);
  bTree->SetBranchAddress("piplus"+binX.name,&plusX);
  bTree->SetBranchAddress("piplus"+binY.name,&plusY);
  bTree->SetBranchAddress("piplus"+binZ.name,&plusZ);
  bTree->SetBranchAddress("piplusDLLKPI",&plusDLLKPI);
  bTree->SetBranchAddress("piplusDLLPPI",&plusDLLPPI);
  bTree->SetBranchAddress("piminus"+binX.name,&minusX);
  bTree->SetBranchAddress("piminus"+binY.name,&minusY);
  bTree->SetBranchAddress("piminus"+binZ.name,&minusZ);
  bTree->SetBranchAddress("piminusDLLKPI",&minusDLLKPI);
  bTree->SetBranchAddress("piminusDLLPPI",&minusDLLPPI);

  Double_t bdtCut = bdtCutName.Atof();

  double totFiducialPlus   = 0, totFiducialMinus   = 0,
         totNoFiducialPlus = 0, totNoFiducialMinus = 0;
  for(Long64_t ievt = 0; ievt < nentries; ievt++) {
    bTree->GetEntry(ievt);

    if(!(plusX>=binX.start  && plusX<binX.end  &&
         plusY>=binY.start  && plusY<binY.end  &&
         plusZ>=binZ.start  && plusZ<binZ.end  &&
         minusX>=binX.start && minusX<binX.end &&
         minusY>=binY.start && minusY<binY.end &&
         minusZ>=binZ.start && minusZ<binZ.end)) continue;

    if(!(BDT>bdtCut)) continue;

    if(fiducialCut(plusX,plusY)) {
      totFiducialPlus += weight;
      if(applyCutPlus(plusDLLKPI,plusDLLPPI,cutPlus1,cutPlus2)&&
         applyCutMinus(minusDLLKPI,minusDLLPPI,cutMinus1,cutMinus2))
        effFiducialPlusMC += weight;
    }
    else {
      totNoFiducialPlus += weight;
      if(applyCutPlus(plusDLLKPI,plusDLLPPI,cutPlus1,cutPlus2)&&
         applyCutMinus(minusDLLKPI,minusDLLPPI,cutMinus1,cutMinus2))
        effNoFiducialPlusMC += weight;
    }
    if(fiducialCut(minusX,minusY)) {
      totFiducialMinus += weight;
      if(applyCutPlus(plusDLLKPI,plusDLLPPI,cutPlus1,cutPlus2)&&
         applyCutMinus(minusDLLKPI,minusDLLPPI,cutMinus1,cutMinus2))
        effFiducialMinusMC += weight;
    }
    else {
      totNoFiducialMinus += weight;
      if(applyCutPlus(plusDLLKPI,plusDLLPPI,cutPlus1,cutPlus2)&&
         applyCutMinus(minusDLLKPI,minusDLLPPI,cutMinus1,cutMinus2)) 
        effNoFiducialMinusMC += weight;
    }

  }

  effFiducialPlusMC    /= totFiducialPlus;
  effNoFiducialPlusMC  /= totNoFiducialPlus;
  effFiducialMinusMC   /= totFiducialMinus;
  effNoFiducialMinusMC /= totNoFiducialMinus;

  bTree->Reset();
  delete bTree;

  return true;

}



bool readBData(TString &decay, TString &name, TString &finalState,TString &cuts, TString &magnet, TString &year,
               TString &bdtCutName, TString &optimConf,
               double &eff, double &effErr,
               double &effFiducialPlus,double &effFiducialMinus,
               double &effNoFiducialPlus,double &effNoFiducialMinus,
               double &fracFiducialPlus,double &fracFiducialMinus,
               double &fracNoFiducialPlus,double &fracNoFiducialMinus,
               binScheme &binX, binScheme &binY, binScheme &binZ, binScheme &binT,
               bool splotFlag) {

  TString CutPlus1  = ((TObjString *)cuts.Tokenize('.')->At(0))->String();
  TString CutPlus2  = ((TObjString *)cuts.Tokenize('.')->At(1))->String();
  TString CutMinus1 = ((TObjString *)cuts.Tokenize('.')->At(2))->String();
  TString CutMinus2 = ((TObjString *)cuts.Tokenize('.')->At(3))->String();

  TString namePlus, nameMinus, hypoPlus, hypoMinus, binName;
  setNames(decay,finalState,namePlus,nameMinus);
  setHypos(decay,finalState,hypoPlus,hypoMinus);

  const int nBinsX = (const int)binX.intervals.size();
  const int nBinsY = (const int)binY.intervals.size();
  const int nBinsZ = (const int)binZ.intervals.size();
  const int nBinsT = (const int)binT.intervals.size();
  binName.Form("%d_%d_%d_%d",nBinsX,nBinsY,nBinsZ,nBinsT);

  TString effPath  = "${B2HH_OUT}/PID/effCalib/TrackEff/";
  TFile * effFilePlus  = 
    TFile::Open(Form("%s/eff%s_%s.%s_%s_%s_%s.root",effPath.Data(),hypoPlus.Data(),
                                                    CutPlus1.Data(),CutPlus2.Data(),binName.Data(),magnet.Data(),year.Data()));
  TFile * effFileMinus = 
    TFile::Open(Form("%s/eff%s_%s.%s_%s_%s_%s.root",effPath.Data(),hypoMinus.Data(),
                                                    CutMinus1.Data(),CutMinus2.Data(),binName.Data(),magnet.Data(),year.Data()));
  TH3D * hEffPlus  = (TH3D *) effFilePlus->Get(Form("hEff%s_is%s",namePlus.Data(),hypoPlus.Data()));
  TH3D * hEffMinus = (TH3D *) effFileMinus->Get(Form("hEff%s_is%s",nameMinus.Data(),hypoMinus.Data()));

  TString dataPath = splotFlag ? "${B2HH_OUT}/sPlot/tuple_reduced" : "${B2HH_OUT}/Data/tuple_merged";
  TString fileName  = splotFlag ? "b2hh_"+optimConf+"_"+bdtCutName : decay;
  TString suffixName = splotFlag ? "_PIPI" : "";
  TString treeName = splotFlag ? "b2hhW" : "b2hh";
  TChain * bTree = new TChain(treeName.Data(),treeName.Data());
  if(!splotFlag) {
    auto tag_years = datasetFlags::chain_years[year];
    auto tag_magnet = datasetFlags::chain_magnet[magnet];
    chainAdder::chainAdder(bTree, dataPath+"/%s_%s_%s.root/b2hh",
                           fileName, tag_years, tag_magnet);
  } else {
    bTree->Add(Form("%s/%s_%s_%s%s.root",dataPath.Data(),fileName.Data(),
                                         year.Data(),magnet.Data(),suffixName.Data()));
    printf("Adding file %s/%s_%s_%s%s.root\n",dataPath.Data(),fileName.Data(),
                                              year.Data(),magnet.Data(),suffixName.Data());
  }
  bTree->Print();
  bTree->SetBranchStatus("*",0);
  // VARIABLES FOR BDT
  if(!splotFlag) {
    bTree->SetBranchStatus(Form("bdt%s",optimConf.Data()),1);
  }
  // VARIABLES FOR PID
  bTree->SetBranchStatus("piplus"+binX.name,1);
  bTree->SetBranchStatus("piplus"+binY.name,1);
  bTree->SetBranchStatus("piplus"+binZ.name,1);
  bTree->SetBranchStatus("piminus"+binX.name,1);
  bTree->SetBranchStatus("piminus"+binY.name,1);
  bTree->SetBranchStatus("piminus"+binZ.name,1);
  if(splotFlag)
    bTree->SetBranchStatus("weight" ,1);

  Long64_t nentries = bTree->GetEntries();
  // VARIABLES FOR BDT
  Double_t BDT = 0;
  if(!splotFlag) {
    bTree->SetBranchAddress(Form("bdt%s",optimConf.Data()),&BDT);
  }
  // VARIABLES FOR PID
  double plusX  = 0, plusY  = 0, plusZ  = 0,
         minusX = 0, minusY = 0, minusZ = 0,
         weight = 1;
  bTree->SetBranchAddress("piplus"+binX.name,&plusX);
  bTree->SetBranchAddress("piplus"+binY.name,&plusY);
  bTree->SetBranchAddress("piplus"+binZ.name,&plusZ);
  bTree->SetBranchAddress("piminus"+binX.name,&minusX);
  bTree->SetBranchAddress("piminus"+binY.name,&minusY);
  bTree->SetBranchAddress("piminus"+binZ.name,&minusZ);
  if(splotFlag)
    bTree->SetBranchAddress("weight",&weight);

  double tot               = 0,
         totFiducialPlus   = 0, totFiducialMinus   = 0,
         totNoFiducialPlus = 0, totNoFiducialMinus = 0,
         effPlus           = 0, effMinus           = 0,
         errPlus           = 0, errMinus           = 0;

  int posPlusX  = 0, posPlusY  = 0, posPlusZ  = 0,
      posMinusX = 0, posMinusY = 0, posMinusZ = 0;

  int totBins = nBinsX*nBinsY*nBinsZ*nBinsX*nBinsY*nBinsZ;
  double * fractions  = new double[totBins];
  double * fractions2 = new double[totBins];
  int totBinsIndex = 0;

  for(int iXplus = 0; iXplus < nBinsX; iXplus++) {
    for(int iYplus = 0; iYplus < nBinsY; iYplus++) {
      for(int iZplus = 0; iZplus < nBinsZ; iZplus++) {
        for(int iXminus = 0; iXminus < nBinsX; iXminus++) {
          for(int iYminus = 0; iYminus < nBinsY; iYminus++) {
            for(int iZminus = 0; iZminus < nBinsZ; iZminus++) {

              totBinsIndex = iXplus*nBinsY*nBinsZ*nBinsX*nBinsY*nBinsZ+
                             iYplus*nBinsZ*nBinsX*nBinsY*nBinsZ+
                             iZplus*nBinsX*nBinsY*nBinsZ+
                             iXminus*nBinsY*nBinsZ+
                             iYminus*nBinsZ+iZminus;
              fractions[totBinsIndex] = 0;
              fractions2[totBinsIndex] = 0;
            }
          }
        }
      }
    }
  }

  Bool_t bdtSelection = true;
  Double_t bdtCut = bdtCutName.Atof();
  for(Long64_t ievt = 0; ievt < nentries; ievt++) {
    bTree->GetEntry(ievt);

    if(!(plusX>=binX.start  && plusX<binX.end  &&
         plusY>=binY.start  && plusY<binY.end  &&
         plusZ>=binZ.start  && plusZ<binZ.end  &&
         minusX>=binX.start && minusX<binX.end &&
         minusY>=binY.start && minusY<binY.end &&
         minusZ>=binZ.start && minusZ<binZ.end)) continue;
    if(!splotFlag) {
      bdtSelection = BDT>bdtCut;
    }
    if(!bdtSelection) continue;

    posPlusX  = findBin(plusX,binX);
    posPlusY  = findBin(plusY,binY);
    posPlusZ  = findBin(plusZ,binZ);
    posMinusX = findBin(minusX,binX);
    posMinusY = findBin(minusY,binY);
    posMinusZ = findBin(minusZ,binZ);
    effPlus  = hEffPlus->GetBinContent(posPlusX+1,posPlusY+1,posPlusZ+1);
    effMinus = hEffMinus->GetBinContent(posMinusX+1,posMinusY+1,posMinusZ+1);
    errPlus  = hEffPlus->GetBinError(posPlusX+1,posPlusY+1,posPlusZ+1);
    errMinus = hEffMinus->GetBinError(posMinusX+1,posMinusY+1,posMinusZ+1);

    totBinsIndex = posPlusX*nBinsY*nBinsZ*nBinsX*nBinsY*nBinsZ+
                   posPlusY*nBinsZ*nBinsX*nBinsY*nBinsZ+
                   posPlusZ*nBinsX*nBinsY*nBinsZ+
                   posMinusX*nBinsY*nBinsZ+
                   posMinusY*nBinsZ+posMinusZ;

    tot += weight;
    eff += weight*effPlus*effMinus;
    fractions[totBinsIndex] += weight;
    fractions2[totBinsIndex] += weight*weight;
    if(fiducialCut(plusX,plusY)) {
      totFiducialPlus += weight;
      effFiducialPlus += weight*effPlus*effMinus;
    }
    else {
      totNoFiducialPlus += weight;
      effNoFiducialPlus += weight*effPlus*effMinus;
    }
    if(fiducialCut(minusX,minusY)) {
      totFiducialMinus += weight;
      effFiducialMinus += weight*effPlus*effMinus;
    }
    else {
      totNoFiducialMinus += weight;
      effNoFiducialMinus += weight*effPlus*effMinus;
    }

  }

  eff /= tot;

  //Computing efficiency error
  double fractionTMP = 0, fraction2TMP = 0;
  for(int iXplus = 0; iXplus < nBinsX; iXplus++) {
    for(int iYplus = 0; iYplus < nBinsY; iYplus++) {
      for(int iZplus = 0; iZplus < nBinsZ; iZplus++) {
        for(int iXminus = 0; iXminus < nBinsX; iXminus++) {
          for(int iYminus = 0; iYminus < nBinsY; iYminus++) {
            for(int iZminus = 0; iZminus < nBinsZ; iZminus++) {
              totBinsIndex = iXplus*nBinsY*nBinsZ*nBinsX*nBinsY*nBinsZ+
                             iYplus*nBinsZ*nBinsX*nBinsY*nBinsZ+
                             iZplus*nBinsX*nBinsY*nBinsZ+
                             iXminus*nBinsY*nBinsZ+
                             iYminus*nBinsZ+iZminus;
              fractionTMP = fractions[totBinsIndex];
              fraction2TMP = fractions[totBinsIndex];
              effPlus  = hEffPlus->GetBinContent(iXplus+1,iYplus+1,iZplus+1);
              effMinus = hEffMinus->GetBinContent(iXminus+1,iYminus+1,iZminus+1);
              errPlus  = hEffPlus->GetBinError(iXplus+1,iYplus+1,iZplus+1);
              errMinus = hEffMinus->GetBinError(iXminus+1,iYminus+1,iZminus+1);
             
              effErr += fraction2TMP*effPlus*effPlus*effMinus*effMinus/tot/tot;
              effErr += fractionTMP*fractionTMP*(effPlus*effPlus*errMinus*errMinus+
                                                 effMinus*effMinus*errPlus*errPlus)/tot/tot;

            }
          }
        }
      }
    }
  }

  effErr = sqrt(effErr);
  effFiducialPlus    /= totFiducialPlus;
  effNoFiducialPlus  /= totNoFiducialPlus;
  effFiducialMinus   /= totFiducialMinus;
  effNoFiducialMinus /= totFiducialMinus;
  fracFiducialPlus    = totFiducialPlus/tot;
  fracNoFiducialPlus  = totNoFiducialPlus/tot;
  fracFiducialMinus   = totFiducialMinus/tot;
  fracNoFiducialMinus = totNoFiducialMinus/tot;
 
  bTree->Reset();
  delete bTree;
  delete hEffPlus; delete hEffMinus;
  delete fractions; delete fractions2;

  effFilePlus->Close();
  effFileMinus->Close();

  delete effFilePlus; delete effFileMinus;
 
  return true;

}
