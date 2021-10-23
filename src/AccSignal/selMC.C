#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <TROOT.h>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TRandom3.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <RooFit.h>
#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooKeysPdf.h>
#include <RooWorkspace.h>
#include <optionParser.h>

#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>

using namespace std;
using namespace RooFit;

Bool_t fiducialFlag(Double_t P, Double_t ETA) {

  double m1 = 0;                  double q1 = 2;
  double m2 = (3.75-2)/(120-25);  double q2 = 2 - m2*25;
  double m3 = (6-3.75)/(135-120); double q3 = 3.75 - m3*120;

  bool ret = (ETA > P*m1+q1 && P<=25)||
             (ETA > P*m2+q2 && P>25 && P<=120)||
             (ETA > P*m3+q3 && P>120);
  return ret;

}

Int_t main(Int_t argc, Char_t * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./selMC_new [options]\n");
    printf("Options:\n");
    printf("  -n <name>       : name of the decay for BDT optimisation (default = PIPI)\n");
    printf("  -d <decay>      : name of the decay to be processed (default = bdkpi)\n");
    printf("  -f <finalState> : final state hypothesis (default = pipi)\n");
    printf("  -c <cut>        : pid cuts depending on final state (default = -3.5.-3.5)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = -1)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2011,2012,Tot], default = Tot)\n");
    printf("  -F <effNoFid>   : efficiencies out of fiductial region (pk_kp_ppi_pip, default = 0_0_0_0)\n");
    return 0;
  }

  TString name         = getOption(argc,argv,"-n","PIPI");
  TString decay         = getOption(argc,argv,"-d","bdpipi");
  TString finalState    = getOption(argc,argv,"-f","pipi");
  TString cuts          = getOption(argc,argv,"-c","-3.5.-3.5");
  Int_t pidPlus1        = atoi(((TObjString *)cuts.Tokenize('.')->At(0))->String());
  Int_t pidPlus2        = atoi(((TObjString *)cuts.Tokenize('.')->At(1))->String());
  Int_t pidMinus1       = atoi(((TObjString *)cuts.Tokenize('.')->At(2))->String());
  Int_t pidMinus2       = atoi(((TObjString *)cuts.Tokenize('.')->At(3))->String());
  Double_t bdtCut       = atof(getOption(argc,argv,"-b","-1"));
  TString magnet        = getOption(argc,argv,"-m","Tot");
  TString year          = getOption(argc,argv,"-y","Tot");
  TString fiducialEff   = getOption(argc,argv,"-F","0_0_0_0");
  Double_t effNoFiducialPK  = atof((((TObjString *)fiducialEff.Tokenize('_')->At(0))->String()));
  Double_t effNoFiducialKP  = atof((((TObjString *)fiducialEff.Tokenize('_')->At(1))->String()));
  Double_t effNoFiducialPPI = atof((((TObjString *)fiducialEff.Tokenize('_')->At(2))->String()));
  Double_t effNoFiducialPIP = atof((((TObjString *)fiducialEff.Tokenize('_')->At(3))->String()));

  printf("EXECUTING ./selMC_new -d %s -f %s -c %d.%d.%d.%d -b %g -m %s -y %s -F %g_%g_%g_%g\n",
         decay.Data(),finalState.Data(),pidPlus1,pidPlus2,pidMinus1,pidMinus2,
         bdtCut,magnet.Data(),year.Data(),effNoFiducialPK,effNoFiducialKP,effNoFiducialPPI,effNoFiducialPIP);
  Int_t qOS = 0, qSS = 0, qSSk = 0, triggerFlag = 0;
  Double_t piplusP = 0, piplusETA = 0, piplusPT = 0, piplusPHI = 0, piplusIPCHI2 = 0,
           piplusPX = 0, piplusPY = 0, piplusPZ = 0,
           piminusP = 0, piminusETA = 0, piminusPT = 0, piminusPHI = 0, piminusIPCHI2 = 0,
           piminusPX = 0, piminusPY = 0, piminusPZ = 0, costheta = 0,
           BDT = 0, mass = 0,
           truetau = 0, tau = 0, bETA = 0, bP = 0, timeErr = 0,
           etaOS = 0, etaSS = 0, etaSSk = 0;
  Float_t bPT = 0, bIPCHI2 = 0, bFDCHI2 = 0;
  Double_t piplusDLLKPI = 0, piplusDLLPPI = 0,
           piminusDLLKPI = 0, piminusDLLPPI = 0;
  Double_t piplusHlt1Loose = 0, piplusHlt1Tight = 0,
           piminusHlt1Loose = 0, piminusHlt1Tight = 0;
 
  TString hypoPlus = "", hypoMinus = "";
  TString namePlus = "", nameMinus = "";
  TString timeName = "";
  if(finalState=="kpi")  { hypoPlus = "K";  hypoMinus = "PI"; timeName = "KPI"; }
  if(finalState=="pik")  { hypoPlus = "PI"; hypoMinus = "K";  timeName = "PIK"; }
  if(finalState=="pipi") { hypoPlus = "PI"; hypoMinus = "PI"; timeName = "PIPI"; }
  if(finalState=="kk")   { hypoPlus = "K";  hypoMinus = "K";  timeName = "KK"; }

  if(decay=="bdkpi")  { namePlus   = "Kplus";  nameMinus   = "PIminus"; }
  if(decay=="bdpik")  { namePlus   = "PIplus"; nameMinus   = "Kminus";  }
  if(decay=="bdpipi") { namePlus   = "PIplus"; nameMinus   = "PIminus";         }
  if(decay=="bdkk")   { namePlus   = "Kplus";  nameMinus   = "Kminus";          }
  if(decay=="bskpi")  { namePlus   = "Kplus";  nameMinus   = "PIminus"; }
  if(decay=="bspik")  { namePlus   = "PIplus"; nameMinus   = "Kminus";  }
  if(decay=="bspipi") { namePlus   = "PIplus"; nameMinus   = "PIminus";         }
  if(decay=="bskk")   { namePlus   = "Kplus";  nameMinus   = "Kminus";          }
  if(decay=="lbpk")   { namePlus   = "Pplus";  nameMinus   = "Kminus";          }
  if(decay=="lbkp")   { namePlus   = "Kplus";  nameMinus   = "Pminus";          }
  if(decay=="lbppi")  { namePlus   = "Pplus";  nameMinus   = "PIminus";         }
  if(decay=="lbpip")  { namePlus   = "PIplus"; nameMinus   = "Pminus";          }
  TFile * effFilePlus  = TFile::Open(Form("${B2HH_OUT}/PID/effCalib/TrackEff/eff%s_%d.%d_71_10_1_6_%s_%s.root",
                                     hypoPlus.Data(),pidPlus1,pidPlus2,magnet.Data(),year.Data()),"READ");
  TFile * effFileMinus = TFile::Open(Form("${B2HH_OUT}/PID/effCalib/TrackEff/eff%s_%d.%d_71_10_1_6_%s_%s.root",
                                     hypoMinus.Data(),pidMinus1,pidMinus2,magnet.Data(),year.Data()),"READ");

  TH3D * hEffPlus     = (TH3D *) effFilePlus->Get(Form("hEff%s_is%s",namePlus.Data(),hypoPlus.Data()));
  TH3D * hEffMinus    = (TH3D *) effFileMinus->Get(Form("hEff%s_is%s",nameMinus.Data(),hypoMinus.Data()));
  TH2D * hEffPlus2D   = (TH2D *) hEffPlus->Project3D("yx");
  TH2D * hEffMinus2D  = (TH2D *) hEffMinus->Project3D("yx");

  TChain * inChain = new TChain("inChain","inChain");
  auto tag_years = datasetFlags::chain_years[year];
  auto tag_magnet = datasetFlags::chain_magnet[magnet];
  chainAdder::chainAdder(inChain, "${B2HH_OUT}/Data/tuple_merged/%s_%s_%s.root/b2hh",
                         decay, tag_years, tag_magnet);

  inChain->SetBranchStatus("*",                       0);
  inChain->SetBranchStatus("piplusP",                 1);
  inChain->SetBranchStatus("piplusPT",                1);
  inChain->SetBranchStatus("piplusPHI",               1);
  inChain->SetBranchStatus("piplusETA",               1);
  inChain->SetBranchStatus("piplusIPCHI2",            1);
  inChain->SetBranchStatus("piminusP",                1);
  inChain->SetBranchStatus("piminusPT",               1);
  inChain->SetBranchStatus("piminusPHI",              1);
  inChain->SetBranchStatus("piminusETA",              1);
  inChain->SetBranchStatus("piminusIPCHI2",           1);
  inChain->SetBranchStatus("bIPCHI2",                 1);
  inChain->SetBranchStatus("bFDCHI2",                 1);
  inChain->SetBranchStatus("bPT",                     1);
  inChain->SetBranchStatus("bP",                      1);
  inChain->SetBranchStatus("bETA",                    1);
  inChain->SetBranchStatus("mass"+timeName,           1);
  inChain->SetBranchStatus("tau"+timeName,            1);
  inChain->SetBranchStatus("trueTau",                 1);
  inChain->SetBranchStatus("tau"+timeName+"Err",      1);
  inChain->SetBranchStatus(Form("bdt%s",name.Data()), 1);
  inChain->SetBranchStatus("Polarity",                1);
  inChain->SetBranchStatus("Year",                    1);
  inChain->SetBranchStatus("qOS*",                    1);
  inChain->SetBranchStatus("etaOS*",                  1);
  inChain->SetBranchStatus("qSS*",                    1);
  inChain->SetBranchStatus("etaSS*",                  1);
  inChain->SetBranchAddress("piplusP",                &piplusP);
  inChain->SetBranchAddress("piplusPT",               &piplusPT);
  inChain->SetBranchAddress("piplusPHI",              &piplusPHI);
  inChain->SetBranchAddress("piplusETA",              &piplusETA);
  inChain->SetBranchAddress("piplusIPCHI2",           &piplusIPCHI2);
  inChain->SetBranchAddress("piminusP",               &piminusP);
  inChain->SetBranchAddress("piminusPT",              &piminusPT);
  inChain->SetBranchAddress("piminusPHI",             &piminusPHI);
  inChain->SetBranchAddress("piminusETA",             &piminusETA);
  inChain->SetBranchAddress("piminusIPCHI2",          &piminusIPCHI2);
  inChain->SetBranchAddress("bIPCHI2",                &bIPCHI2);
  inChain->SetBranchAddress("bFDCHI2",                &bFDCHI2);
  inChain->SetBranchAddress("piplusDLLKPI",           &piplusDLLKPI);
  inChain->SetBranchAddress("piplusDLLPPI",           &piplusDLLPPI);
  inChain->SetBranchAddress("piminusDLLKPI",          &piminusDLLKPI);
  inChain->SetBranchAddress("piminusDLLPPI",          &piminusDLLPPI);
  inChain->SetBranchAddress("bPT",                    &bPT);
  inChain->SetBranchAddress("bP",                     &bP);
  inChain->SetBranchAddress("bETA",                   &bETA);
  inChain->SetBranchAddress("mass"+timeName,          &mass);
  inChain->SetBranchAddress("tau"+timeName,           &tau);
  inChain->SetBranchAddress("trueTau",                &truetau);
  inChain->SetBranchAddress("tau"+timeName+"Err",     &timeErr);
  inChain->SetBranchAddress(Form("bdt%s",name.Data()),&BDT);
  /*
  inChain->SetBranchAddress("qOS",                    &qOS);
  inChain->SetBranchAddress("qSS",                    &qSS);
  inChain->SetBranchAddress("qSSk",                   &qSSk);
  inChain->SetBranchAddress("etaOS",                  &etaOS);
  inChain->SetBranchAddress("etaSS",                  &etaSS);
  inChain->SetBranchAddress("etaSSk",                 &etaSSk);
  */
  Double_t weight = 0;
  TFile * outFile = new TFile(Form("${B2HH_OUT}/AccSignal/selectedMC/%s_%s_%s_%g_%s_%s.root",
                                   decay.Data(),finalState.Data(),
                                   name.Data(),bdtCut,year.Data(),magnet.Data()),
                              "RECREATE");
  /*
  TTree * outTreeLoose = inChain->CloneTree(0);
  outTreeLoose->Branch("trueTau",&truetau,"trueTau/D");
  outTreeLoose->Branch("time",&tau,"time/D");
  outTreeLoose->Branch("mass",&mass,"mass/D");
  outTreeLoose->Branch("timeErr",&timeErr,"timeErr/D");
  outTreeLoose->Branch("weight",&weight,"weight/D");
  outTreeLoose->Branch("bPT",&bPT,"bPT/F");
  outTreeLoose->Branch("piplusHlt1Tight",&piplusHlt1Tight,"piplusHlt1Tight/D");
  outTreeLoose->Branch("piplusHlt1Loose",&piplusHlt1Loose,"piplusHlt1Loose/D");
  outTreeLoose->Branch("piminusHlt1Tight",&piminusHlt1Tight,"piminusHlt1Tight/D");
  outTreeLoose->Branch("piminusHlt1Loose",&piminusHlt1Loose,"piminusHlt1Loose/D");
  outTreeLoose->Branch("triggerFlag",&triggerFlag,"triggerFlag/I");
  */
  TTree * outTree = inChain->CloneTree(0);
  outTree->Branch("trueTau",&truetau,"trueTau/D");
  outTree->Branch("time",&tau,"time/D");
  outTree->Branch("mass",&mass,"mass/D");
  outTree->Branch("timeErr",&timeErr,"timeErr/D");
  outTree->Branch("weight",&weight,"weight/D");
  outTree->Branch("bPT",&bPT,"bPT/F");
  outTree->Branch("piplusHlt1Tight",&piplusHlt1Tight,"piplusHlt1Tight/D");
  outTree->Branch("piplusHlt1Loose",&piplusHlt1Loose,"piplusHlt1Loose/D");
  outTree->Branch("piminusHlt1Tight",&piminusHlt1Tight,"piminusHlt1Tight/D");
  outTree->Branch("piminusHlt1Loose",&piminusHlt1Loose,"piminusHlt1Loose/D");
  outTree->Branch("triggerFlag",&triggerFlag,"triggerFlag/I");

  TRandom3 myRandom(1029384756);

  Long64_t nEntries = inChain->GetEntries();

  
  for(Int_t iEntry = 0; iEntry < nEntries; iEntry++) {

    inChain->GetEntry(iEntry);


    if (mass<selection_cuts::mass_min) continue;
    if (mass>selection_cuts::mass_max) continue;
    if (tau<selection_cuts::time_min) continue;
    if (tau>selection_cuts::time_max) continue;
    if (timeErr>selection_cuts::timeErr_max) continue;
    if (BDT<bdtCut) continue;
        
      
    piplusPZ = sqrt(piplusP*piplusP-piplusPT*piplusPT);
    piplusPX = piplusPT*cos(piplusPHI);
    piplusPY = piplusPT*sin(piplusPHI);
    piminusPZ = sqrt(piminusP*piminusP-piminusPT*piminusPT);
    piminusPX = piminusPT*cos(piminusPHI);
    piminusPY = piminusPT*sin(piminusPHI);

    costheta = (piplusPX*piminusPX+piplusPY*piminusPY+piplusPZ*piminusPZ)/piplusP/piminusP;

    weight = hEffPlus2D->Interpolate(piplusP,piplusETA)*
             hEffMinus2D->Interpolate(piminusP,piminusETA);
    if     (decay == "lbpk"  && !fiducialFlag(piplusP,piplusETA))
      weight = effNoFiducialPK;
    else if(decay == "lbkp"  && !fiducialFlag(piminusP,piminusETA))
      weight = effNoFiducialKP;
    else if(decay == "lbppi" && !fiducialFlag(piplusP,piplusETA))
      weight = effNoFiducialPPI;
    else if(decay == "lbpip" && !fiducialFlag(piminusP,piminusETA))
      weight = effNoFiducialPIP;

    /*
    piplusHlt1Loose = log(piplusIPCHI2) - 1.0/((piplusPT - 1.0)/(piplusPT-1.0))
                                        - (1.1 / 25.0) * (25.0 - piplusPT)
                                        - log(7.4);
    piplusHlt1Tight = log(piplusIPCHI2) - 1.0/((piplusPT - 1.0)/(piplusPT-1.0))
                                        - (2.3 / 25.0) * (25.0 - piplusPT)
                                        - log(7.4);

    piminusHlt1Loose = log(piminusIPCHI2) - 1.0/((piminusPT - 1.0)/(piminusPT-1.0))
                                          - (1.1 / 25.0) * (25.0 - piminusPT)
                                          - log(7.4);
    piminusHlt1Tight = log(piminusIPCHI2) - 1.0/((piminusPT - 1.0)/(piminusPT-1.0))
                                          - (2.3 / 25.0) * (25.0 - piminusPT)
                                          - log(7.4);

    if(myRandom.Uniform(0,1)<0.75) {
      triggerFlag = 0;
      outTreeLoose->Fill();
    }
    else {
      triggerFlag = 1;
      if(max(piplusHlt1Tight,piminusHlt1Tight)>0) outTree->Fill();
    }
    */

    outTree->Fill();    
  }

  /*
  for(Int_t iEntry = 0, nEntries = outTree->GetEntries(), nEntriesCheck = outTreeLoose->GetEntries(); iEntry < 3*nEntries; ++iEntry) {
    if(iEntry > nEntriesCheck) printf("SONO UN COGLIONE\n");
    outTreeLoose->GetEntry(iEntry);
    outTree->Fill();
  }
  */
  outFile->WriteTObject(outTree,"","Overwrite");
  outFile->Close();
  effFilePlus->Close();
  effFileMinus->Close();
  return 0;

}
