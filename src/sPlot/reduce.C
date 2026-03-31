#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TMVA/Reader.h>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TH3D.h>
#include <TH2D.h>
#include <optionParser.h>
#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>

using namespace std;

int main(int argc, char * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./reduce [options]\n");
    printf("Options:\n");
    printf("  -d <decay>      : name of the decay used to optimise BDT (default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = -1)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2015,2016,2017,2018,201516,20151618,Tot], default = Tot)\n");
    printf("  -f <finalState> : final state hypothesis ([KPI,PIPI,KK], default = PIPI)\n");
    return 0;
  }

  TString decay         = getOption(argc,argv,"-d","PIPI");
  Double_t bdtCut       = atof(getOption(argc,argv,"-b","-1"));
  TString magnet        = getOption(argc,argv,"-m","Tot");
  TString year          = getOption(argc,argv,"-y","Tot");
  TString finalState    = getOption(argc,argv,"-f","PIPI");

  printf("EXECUTING ./reduce -d %s -b %g -m %s -y %s -f %s\n",
         decay.Data(),bdtCut,magnet.Data(),year.Data(),finalState.Data());

  Int_t    nSPD = 0, nPVs = 0;
  Double_t BDT = 0, massPIPI = 0;
  Double_t piplusP  = 0, piplusETA  = 0, piplusPHI  = 0,
           piminusP = 0, piminusETA = 0, piminusPHI = 0,
           bP = 0, bPT = 0, bETA = 0, bPHI = 0,
           npvs = 0, nspd = 0; 
  Double_t etaOS = 0, etaSSpi = 0, etaSSp = 0, etaSSk = 0, etaSS = 0,
           time = 0, timeErr = 0;
  UInt_t runNumber = 0;
  ULong64_t eventNumber = 0;

  TChain * inChain = new TChain("b2hh","b2hh");
  auto tag_years = datasetFlags::chain_years[year];
  auto tag_magnet = datasetFlags::chain_magnet[magnet];
  chainAdder::chainAdder(inChain, "${B2HH_OUT}/Data/tuple_merged/%s_%s_%s.root/b2hh",
                         "b2hh", tag_years, tag_magnet);

  std::vector<TString> vars = {"bPT","bP","bETA","bPHI","massPIPI",
                               Form("tau%s",finalState.Data()),
                               Form("tau%sErr",finalState.Data()),
                               Form("bdt%s",decay.Data()),
                               "piplusP","piplusETA","piplusPHI",
                               "piminusP","piminusETA","piminusPHI",
                               "nSPDHits","nPVs",
                               "etaOS","etaSSpi","etaSSp","etaSSk","etaSS",
                               "runNumber","eventNumber"};
  setBranchStatuses(inChain,vars);
  inChain->SetBranchAddress("bPT",        &bPT       );
  inChain->SetBranchAddress("bP",         &bP        );
  inChain->SetBranchAddress("bETA",       &bETA      );
  inChain->SetBranchAddress("bPHI",       &bPHI      );
  inChain->SetBranchAddress("massPIPI",   &massPIPI  );
  inChain->SetBranchAddress(Form("tau%s",finalState.Data()),&time );
  inChain->SetBranchAddress(Form("tau%sErr",finalState.Data()),&timeErr );
  inChain->SetBranchAddress(Form("bdt%s",decay.Data()),&BDT);
  inChain->SetBranchAddress("piplusP",    &piplusP   );
  inChain->SetBranchAddress("piplusETA",  &piplusETA );
  inChain->SetBranchAddress("piplusPHI",  &piplusPHI );
  inChain->SetBranchAddress("piminusP",   &piminusP  );
  inChain->SetBranchAddress("piminusETA", &piminusETA);
  inChain->SetBranchAddress("piminusPHI", &piminusPHI);
  inChain->SetBranchAddress("nSPDHits",   &nSPD   );
  inChain->SetBranchAddress("nPVs",       &nPVs      );
  inChain->SetBranchAddress("etaOS",&etaOS); 
  inChain->SetBranchAddress("etaSSpi",&etaSSpi); 
  inChain->SetBranchAddress("etaSSp", &etaSSp); 
  inChain->SetBranchAddress("etaSSk", &etaSSk); 
  inChain->SetBranchAddress("etaSS",  &etaSS); 
  inChain->SetBranchAddress("runNumber",&runNumber);
  inChain->SetBranchAddress("eventNumber",&eventNumber);

  TFile * outFile = TFile::Open(Form("${B2HH_OUT}/sPlot/tuple_reduced/b2hh_%s_%g_%s_%s_%s.root",
                                     decay.Data(),bdtCut,
                                     year.Data(),magnet.Data(),
                                     finalState.Data()),
                                "RECREATE");

  //  TTree * outTree = new TTree("b2hh","b2hh");
  inChain->SetBranchStatus("*",1);
  TTree * outTree = inChain->CloneTree(0);
  outTree->Branch("mass",         &massPIPI,     "mass/D");
  outTree->Branch("time",         &time,         "time/D");
  outTree->Branch("timeErr",      &timeErr,      "timeErr/D");
  outTree->Branch("BDT",&BDT,"BDT/D");

  /*
  outTree->Branch("piplusP",      &piplusP,      "piplusP/D"); 
  outTree->Branch("piplusETA",    &piplusETA,    "piplusETA/D" );
  outTree->Branch("piplusPHI",    &piplusPHI,    "piplusPHI/D");
  outTree->Branch("piminusP",     &piminusP,     "piminusP/D"); 
  outTree->Branch("piminusETA",   &piminusETA,   "piminusETA/D");
  outTree->Branch("piminusPHI",   &piminusPHI,   "piminusPHI/D");
  outTree->Branch("nSPDHits",     &nspd,         "nSPDHits/D");
  outTree->Branch("nPVs",         &npvs,         "nPVs/D");
  outTree->Branch("bPT",          &bPT,          "bPT/D");
  outTree->Branch("bP",           &bP,           "bP/D");
  outTree->Branch("bETA",         &bETA,         "bETA/D");
  outTree->Branch("bPHI",         &bPHI,         "bPHI/D");
  
  outTree->Branch("etaOS",        &etaOS,        "etaOS/D");
  outTree->Branch("etaSSk",       &etaSSk,       "etaSSk/D");
  outTree->Branch("etaSSpi",      &etaSSpi,      "etaSSpi/D");
  outTree->Branch("etaSSp",       &etaSSp,       "etaSSp/D");
  outTree->Branch("etaSS",        &etaSS,        "etaSS/D");

  outTree->Branch("runNumber",&runNumber,"runNumber/i");
  outTree->Branch("eventNumber",&eventNumber,"eventNumber/l");
  */
  
  for(Long64_t ievt = 0, nEntries = inChain->GetEntries(); ievt < nEntries; ++ievt) {
    inChain->GetEntry(ievt);

    if( massPIPI < sPlot_cuts::data_massMin || 
        massPIPI > sPlot_cuts::data_massMax) continue;

    if(BDT<bdtCut) continue;

    //    nspd     = (Double_t) nSPD;
    //    npvs     = (Double_t) nPVs;
    if(time > sPlot_cuts::timeMin &&
       time < sPlot_cuts::timeMax &&
       timeErr < sPlot_cuts::timeErrMax)
      outTree->Fill();
  }

  outTree->Write("",TObject::kOverwrite);
  outFile->Close();

  return 0;

}
