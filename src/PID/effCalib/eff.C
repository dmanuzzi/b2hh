#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <TString.h>
#include <TObjString.h>
#include <TObjArray.h>
#include <TFile.h>
#include <TChain.h>
#include <TFileCollection.h>
#include <TCollection.h>
#include <TH1D.h>
#include <TH3D.h>
#include <binScheme.h>
#include <optionParser.h>
#include <readCalib.h>

using namespace std;

int main(int argc, char * argv[]) {


  if(getBooleanOption(argc,argv,"-h",false)) {
    printf("Usage of eff:\n");
    printf("  ./eff [options]\n");
    printf("Options:\n");
    printf("  -x <binXFile>   : will take the binning from <binXFile>.bin (default = binP_71)\n");
    printf("  -y <binYFile>   : will take the binning from <binYFile>.bin (default = binETA_10)\n");
    printf("  -z <binZFile>   : will take the binning from <binZFile>.bin (default = binPHI_1)\n");
    printf("  -t <binTFile>   : will take the binning from <binTFile>.bin (default = binSPD_6)\n");
    printf("  -m <magnet>     : define the polarity {\"Up\", \"Down\", \"Tot\"} of the magnet\n");
    printf("                    (default = \"Tot\", i.e. sum MagUp and MagDown)\n");
    printf("  -Y <year>       : define year of data taking {\"2011\",\"2012\",\"Tot\"}\n"); 
    printf("                    (default = \"Tot\", i.e. sum of 2011 and 2012)\n");
    printf("  -f <hypothesis> : define the hypothesis to be evaluated {PI, K, P} (default = K)\n");
    printf("  -c <cuts>       : define cuts to apply. The meaning of cuts will be automatically\n");
    printf("                    interpreted depending on hypothesis (default = 13.0 that means\n");
    printf("                    DLLKPI > 13 && DLLKP > 0\n");
    printf("  -r <reweight>   : flag to activate the reweight in the number of tracks\n");
    printf("                    (default = 1)\n");
    return 0;
  }
  // Preparing binnings
  binScheme binX; binScheme binY; binScheme binZ; binScheme binT;
  if(createBinning(getOption(argc,argv,"-x","binP_71"),binX)<0) return -1;
  double * binningX = histoBinning(binX);
  int nBinsX = binX.intervals.size();

  if(createBinning(getOption(argc,argv,"-y","binETA_10"),binY)<0) return -1;
  double * binningY = histoBinning(binY);
  int nBinsY = binY.intervals.size();

  if(createBinning(getOption(argc,argv,"-z","binPHI_1"),binZ)<0) return -1;
  double * binningZ = histoBinning(binZ);
  int nBinsZ = binZ.intervals.size();

  if(createBinning(getOption(argc,argv,"-t","binSPD_6"),binT)<0) return -1;
  int nBinsT = binT.intervals.size();

  printf("PREPARING EFFICIENCIES FOR %d(%s)x%d(%s)x%d(%s)x%d(%s) BINNING\n",
         (int)binX.intervals.size(),binX.name.Data(), 
         (int)binY.intervals.size(),binY.name.Data(), 
         (int)binZ.intervals.size(),binZ.name.Data(), 
         (int)binT.intervals.size(),binT.name.Data());

  // Configuring magnet, year, hypothesis and cuts
  TString magnet     = getOption(argc,argv,"-m","Tot"); 
  TString year       = getOption(argc,argv,"-Y","Tot"); 
  TString decay      = getOption(argc,argv,"-f","K");
  TString cuts       = getOption(argc,argv,"-c","13.0");
  Int_t   rewTracks  = getOption(argc,argv,"-r","1").Atoi();

  printf("EVALUATING EFFICIENCIES FOR HYPOTHESIS %s WITH CUTS %s IN THE MAGNET %s CONFIGURATION OF %s DATA TAKING\n",
         decay.Data(),cuts.Data(),magnet.Data(),year.Data());


  // Efficiencies
  double eff[nBinsX][nBinsY][nBinsZ][nBinsT];  double effErr[nBinsX][nBinsY][nBinsZ][nBinsT];
  double effRew[nBinsX][nBinsY][nBinsZ];       double effErrRew[nBinsX][nBinsY][nBinsZ];

  std::vector<TString> particles = {"PI","K","P"};
  std::vector<TString> charges   = {"plus","minus"};

  // Output file for histograms
  TString binName; binName.Form("%d_%d_%d_%d",nBinsX,nBinsY,nBinsZ,nBinsT);
  TFile * outFile = new TFile(Form("${B2HH_OUT}/PID/effCalib/TrackEff/eff%s_%s_%s_%s_%s.root",decay.Data(),cuts.Data(),binName.Data(),
                                                                magnet.Data(),year.Data()),"RECREATE");
  for(auto particle: particles) {

    for(auto charge: charges) {

      // Initialize efficiencies
      for(int iX = 0; iX < nBinsX; iX++) {
        for(int iY = 0; iY < nBinsY; iY++) {
          for(int iZ = 0; iZ < nBinsZ; iZ++) {
            effRew[iX][iY][iZ] = 0;  effErrRew[iX][iY][iZ] = 0;
            for(int iT = 0; iT < nBinsT; iT++) { 
              eff[iX][iY][iZ][iT] = 0;  effErr[iX][iY][iZ][iT] = 0;
            }
          }
        }
      }

      // Filling efficiencies
      TString yearCalib = year;
      if (year == "2017s29r2p2") yearCalib = "2017";
      if(!readCalibrationData(decay,particle,charge,
                              (double *)eff,(double *)effErr,cuts,magnet,yearCalib,
                              binX,binY,binZ,binT)) { printf("Error reading calibration data\n"); return -1; }
 
      // Integrate out the number of tracks
      if(rewTracks) {
        printf("REWEIGHTING IN THE NUMBER OF TRACKS\n");
        if(!reweightTracks((double *) eff, (double *) effRew,(double *) effErr, (double *) effErrRew,
                           binX,binY,binZ,binT,magnet,year)) {
            printf("Error reweighting the number of tracks\n"); return -1; }

        // Output histogram
        TH3D * h = new TH3D(Form("hEff%s%s_is%s",particle.Data(),charge.Data(),decay.Data()),
                            Form("hEff%s%s_is%s",particle.Data(),charge.Data(),decay.Data()),
                            nBinsX,binningX,nBinsY,binningY,nBinsZ,binningZ);

        // Filling output histogram
        for(int iX = 0; iX < nBinsX; iX++) {
          for(int iY = 0; iY < nBinsY; iY++) {
            for(int iZ = 0; iZ < nBinsZ; iZ++) {
              //h->SetBinContent(iX+1,iY+1,iZ+1,effRew[iX][iY][iZ]<=1&&effRew[iX][iY][iZ]>=0?
              h->SetBinContent(iX+1,iY+1,iZ+1,effRew[iX][iY][iZ]>=0?
                                              effRew[iX][iY][iZ] : 0);
              h->SetBinError(  iX+1,iY+1,iZ+1,effErrRew[iX][iY][iZ]);
            }
          }
        }

        outFile->WriteTObject(h);
        delete h;

      }
      else {
        TH3D * h = new TH3D(Form("hEff%s%s_is%s",particle.Data(),charge.Data(),decay.Data()),
                            Form("hEff%s%s_is%s",particle.Data(),charge.Data(),decay.Data()),
                            nBinsX,binningX,nBinsY,binningY,nBinsZ,binningZ);

        // Filling output histogram
        for(int iX = 0; iX < nBinsX; iX++) {
          for(int iY = 0; iY < nBinsY; iY++) {
            for(int iZ = 0; iZ < nBinsZ; iZ++) {
              //h->SetBinContent(iX+1,iY+1,iZ+1,eff[iX][iY][iZ][0]<=1&&eff[iX][iY][iZ][0]>=0?
              h->SetBinContent(iX+1,iY+1,iZ+1,eff[iX][iY][iZ][0]>=0?
                                              eff[iX][iY][iZ][0] : 0);
              h->SetBinError(  iX+1,iY+1,iZ+1,effErr[iX][iY][iZ][0]);
            }
          }
        }

        outFile->WriteTObject(h);
        delete h;

      }

    }

  }

  outFile->Close();

  return 0;

}
