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
#include <TTree.h>
#include <TChain.h>
#include <TTreeFormula.h>
#include <TH1D.h>
#include <TH3D.h>
#include <binScheme.h>
#include <optionParser.h>
#include <TMVA/Reader.h>
#include <readB.h>
#include <sqlite3.h>
#include <sqlManage.h>
#include <expandFileName.h>
using namespace std;

int main(int argc, char * argv[]) {

  TString help = argv[1];  
  if(help =="-h" || help == "--help") {
    printf("Usage of effB2HH:\n");
    printf("  ./effB2HH [options]\n");
    printf("Options:\n");
    printf("  -x <binXFile>   : will take the binning from <binXFile>.bin (default = binP_71)\n");
    printf("  -y <binYFile>   : will take the binning from <binYFile>.bin (default = binETA_10)\n");
    printf("  -z <binZFile>   : will take the binning from <binZFile>.bin (default = binPHI_1)\n");
    printf("  -t <binTFile>   : will take the binning from <binTFile>.bin (default = binTracks_5)\n");
    printf("  -n <name>       : define the channel {\"bdpipi\",\"bskk\"} for which BDT is trained\n");
    printf("  -m <magnet>     : define the configuration {\"Up\",\"Down\",\"Tot\"} of the magnet\n");
    printf("                    (default = \"Tot\")\n");
    printf("  -Y <year>       : define the year of data taking {\"2015\",\"2016\",\"2017\",\"2018\",\"201516\",\"20151618\",\"Tot\"}\n");
    printf("                    (default = \"Tot\")\n");
    printf("  -f <finalState> : define final state hypothesis (default = kk)\n");
    printf("  -c <cuts>       : define cuts to apply. The meaning of cuts will be automatically\n");
    printf("                    interpreted depending on finalState (default = 13.0.13.0 that means\n");
    printf("                    DLLKPI(+) > 13 && DLLKP(+) > 0 && DLLKPI(-) > 13 && DLLKP(-) > 0\n");
    printf("  -s              : flag to use or sPlot instead of MC for B kinematic\n");
    printf("  -b <bdtCUT>     : value of bdtCUT used to perform sPlot for B kinematic (default = -1)\n");
    printf("  -C <optimConf>  : Configuration of PID cuts used to train the BDT (default = "" - MC is used)\n");
    return 0;
  }

  // Preparing binnings
  binScheme binX; binScheme binY; binScheme binZ; binScheme binT;
  if(createBinning(getOption(argc,argv,"-x","binP_71"),binX)<0) return -1;

  if(createBinning(getOption(argc,argv,"-y","binETA_10"),binY)<0) return -1;

  if(createBinning(getOption(argc,argv,"-z","binPHI_1"),binZ)<0) return -1;

  if(createBinning(getOption(argc,argv,"-t","binTracks_5"),binT)<0) return -1;

  printf("COMPUTING EFFICIENCIES FOR %d(%s)x%d(%s)x%d(%s) BINS\n",
         (int)binX.intervals.size(),binX.name.Data(), 
         (int)binY.intervals.size(),binY.name.Data(), 
         (int)binZ.intervals.size(),binZ.name.Data());

  // Configuring magnet, year, hypothesis and cuts
  TString name   = getOption(argc,argv,"-n","bskk");
  TString magnet = getOption(argc,argv,"-m","Tot");
  TString year   = getOption(argc,argv,"-Y","Tot");
  TString finalState = getOption(argc,argv,"-f","kk");
  TString cuts       = getOption(argc,argv,"-c","13.0.13.0");
  bool splotFlag     = getBooleanOption(argc,argv,"-s",false);
  TString bdtCUT     = getOption(argc,argv,"-b","-1");
  TString optimConf  = getOption(argc,argv,"-C","");

  printf("EVALUATING EFFICIENCIES FOR HYPOTHESIS %s WITH CUTS %s IN THE MAGNET %s CONFIGURATION OF %s DATA TAKING\n",
         finalState.Data(),cuts.Data(),magnet.Data(),year.Data());


  // Efficiencies
  double eff;                  double effErr;
  double effFiducialPlusMC;    double effFiducialPlus;
  double effFiducialMinusMC;   double effFiducialMinus;
  double effNoFiducialPlusMC;  double effNoFiducialPlus;
  double effNoFiducialMinusMC; double effNoFiducialMinus;
  double fracFiducialPlus;     double fracNoFiducialPlus;
  double fracFiducialMinus;    double fracNoFiducialMinus;
  std::vector<TString> decays = {"bdkpi","bdpik","bdpipi","bdkk","bskk","bskpi","bspik","bspipi","lbpk","lbkp","lbppi","lbpip"};

  TString sqliteFileName = Form("${B2HH_OUT}/PID/effB2HH/jobs/pidEffs_%s_%s_%s_%s_%s_%s_%s.db",
                                finalState.Data(),name.Data(),optimConf.Data(),bdtCUT.Data(),cuts.Data(),
                                magnet.Data(),year.Data());
  expandFileName::expandFileName(sqliteFileName);
  sqlite3 * db; int rc = sqlite3_open(sqliteFileName.Data(),&db);
  if(rc) { printf("NOT POSSIBLE TO OPEN DB\n"); return 1; }
  if(!createDB(db,"pidEffs")) {printf("NOT POSSIBLE TO CREATE DBASE\n"); return 1; }

  // Output file for histograms
  for(auto decay: decays) {

    // Initialize efficiencies
    eff                  = 0; effErr              = 0;
    effFiducialPlusMC    = 0; effFiducialPlus     = 0;
    effFiducialMinusMC   = 0; effFiducialMinus    = 0;
    effNoFiducialPlusMC  = 0; effNoFiducialPlus   = 0;
    effNoFiducialMinusMC = 0; effNoFiducialMinus  = 0;
    fracFiducialPlus     = 0; fracNoFiducialPlus  = 0;
    fracFiducialMinus    = 0; fracNoFiducialMinus = 0;

    // Filling efficiencies
    if(!readBMCData(decay,name,finalState,cuts,magnet,year,
                    bdtCUT,optimConf,
                    effFiducialPlusMC, effNoFiducialPlusMC,
                    effFiducialMinusMC,effNoFiducialMinusMC,
                    binX,binY,binZ,binT)) { printf("Error reading B MC data\n"); return -1; }

    //printf("effFiducialPlusMC %g\n effNoFiducialPlusMC %g\n effFiducialMinusMC %g\n effNoFiducialMinusMC %g\n",
    //       effFiducialPlusMC,effNoFiducialPlusMC,effFiducialMinusMC,effNoFiducialMinusMC);

    if(!readBData(decay,name,finalState,cuts,magnet,year,
                  bdtCUT,optimConf,eff,effErr,
                  effFiducialPlus, effFiducialMinus,
                  effNoFiducialPlus, effNoFiducialMinus,
                  fracFiducialPlus,fracFiducialMinus,
                  fracNoFiducialPlus,fracNoFiducialMinus,
                  binX,binY,binZ,binT,splotFlag)) { printf("Error reading B data\n"); return -1; }

    //if(decay=="lbpk"||decay=="lbppi") {
    //  effNoFiducialPlus  = effFiducialPlusMC !=0 ?
    //                       effNoFiducialPlusMC*effFiducialPlus/effFiducialPlusMC : 0;
    //  eff = fracFiducialPlus*effFiducialPlus+fracNoFiducialPlus*effNoFiducialPlus;
    //}
    //else if(decay=="lbkp"||decay=="lbpip") {
    //  effNoFiducialMinus = effFiducialMinusMC !=0 ?
    //                       effNoFiducialMinusMC*effFiducialMinus/effFiducialMinusMC : 0;
    //  eff = fracFiducialMinus*effFiducialMinus+fracNoFiducialMinus*effNoFiducialMinus;
    //}

    printf("eff_%s_%s = %lf +/- %lf C L(-INF - +INF)\n",decay.Data(),finalState.Data(),eff,effErr);

    effNoFiducialPlusMC  = 0; effNoFiducialPlus   = 0;
    effNoFiducialMinusMC = 0; effNoFiducialMinus  = 0;

    if(!fillDB(db,decay,finalState,name,optimConf,
               bdtCUT,cuts,splotFlag,magnet,year,eff,effErr,
               fracFiducialPlus,   effFiducialPlus,  effFiducialPlusMC,
               fracNoFiducialPlus, effNoFiducialPlus,effNoFiducialPlusMC,
               fracFiducialMinus,  effFiducialMinus,effFiducialMinusMC,
               fracNoFiducialMinus,effNoFiducialMinus,effNoFiducialMinusMC)) 
      { printf("Error filling the output dbase\n"); return -1; }
            
    printf("\n\n");
  }

  sqlite3_close(db);


  return 0;

}
