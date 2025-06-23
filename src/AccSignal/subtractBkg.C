#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <optionParser.h>
#include <TString.h>
#include <cmath>

#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>

using namespace std;

Int_t main(Int_t argc, Char_t * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./subtractBkg [options]\n");
    printf("Options:\n");
    printf("  -n <name>       : name of the decay for BDT optimisation (default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = -1)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2011,2012,Tot], default = Tot)\n");
    return 0;
  }

  TString name = getOption(argc,argv,"-n","PIPI");
  Double_t bdtCut = atof(getOption(argc,argv,"-b","-1"));
  TString magnet = getOption(argc,argv,"-m","Tot");
  TString year = getOption(argc,argv,"-y","Tot");
  TString tagName = "SSk"; // Bspipi analysis wants always the SSk tagger
  //if     (name=="PIPI") tagName = "SS";
  //else if(name=="KK")   tagName = "SSk";


  TH1D * hMCS = new TH1D("hMCS","hMCS",280,0.2,14.2); hMCS->Sumw2();
  TH1D * hMCL = new TH1D("hMCL","hMCL",280,0.2,14.2); hMCL->Sumw2();
  Double_t mass = 0, time = 0, weight = 0;//, weight2 = 0;
  Int_t qOS = 0, qSS = 0, fState = 0;
  Int_t finalStateIdx = datasetFlags::spectrumKPI + datasetFlags::yearFlags[year];

  TChain * chainNorm = new TChain("chainNorm","chainNorm");
  chainNorm->Add(Form("${B2HH_OUT}/Reduce/b2hh_%s_%g_%s_%s.root/b2hh",name.Data(),bdtCut,year.Data(),magnet.Data()));
  chainNorm->SetBranchStatus("*",0);
  chainNorm->SetBranchStatus("mass",1); chainNorm->SetBranchStatus("time",1);
  chainNorm->SetBranchStatus("qOS",1);  chainNorm->SetBranchStatus(Form("q%s",tagName.Data()),1);
  chainNorm->SetBranchStatus("fState",1);
  chainNorm->SetBranchAddress("mass",&mass);
  chainNorm->SetBranchAddress("time",&time);
  chainNorm->SetBranchAddress("qOS",&qOS);
  chainNorm->SetBranchAddress(Form("q%s",tagName.Data()),&qSS);
  chainNorm->SetBranchAddress("fState",&fState);
  TTree * outTree = (TTree *) chainNorm->CloneTree(0);
  outTree->Branch("weight",&weight,"weight/D");
  for(Int_t iEntry = 0, nEntries = chainNorm->GetEntries(); iEntry < nEntries; ++iEntry) {
    chainNorm->GetEntry(iEntry);
    if(fState!=finalStateIdx) continue;
    if(mass<accSignal_cuts::mass_min_sig) continue;
    if(mass>accSignal_cuts::mass_max_sig) continue;
    weight = 1;
    outTree->Fill();
  }

  TChain * chainBkg = new TChain("chainBkg","chainBkg");
  chainBkg->Add(Form("${B2HH_OUT}/TimeModels/weightedFiles/bkg_KPI_%s_%g_%s_%s.root/b2hh",name.Data(),bdtCut,year.Data(),magnet.Data()));
  chainBkg->SetBranchStatus("*",0);
  chainBkg->SetBranchStatus("mass",1); chainBkg->SetBranchStatus("time",1);
  chainBkg->SetBranchStatus("qOS",1);  chainBkg->SetBranchStatus(Form("q%s",tagName.Data()),1);
  chainBkg->SetBranchAddress("mass",&mass);
  chainBkg->SetBranchAddress("time",&time);
  chainBkg->SetBranchAddress("qOS",&qOS);
  chainBkg->SetBranchAddress(Form("q%s",tagName.Data()),&qSS);
  chainBkg->SetBranchAddress("weightS",&weight);
  chainBkg->SetBranchAddress("fState",&fState);
  for(Int_t iEntry = 0, nEntries = chainBkg->GetEntries(); iEntry < nEntries; ++iEntry) {
    chainBkg->GetEntry(iEntry);
    if(isnan(weight)) continue;  
    outTree->Fill();
  }

  TFile * outFile = TFile::Open(Form("${B2HH_OUT}/AccSignal/bkgSubtractedSamples/b2hh_%s_%g_%s_%s_Sub.root",
				     name.Data(),bdtCut,year.Data(),magnet.Data()),"RECREATE");
  outFile->WriteTObject(outTree,"","Overwrite");
  outFile->Close();

  return 0;
}
