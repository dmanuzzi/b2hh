#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TString.h>
#include <TChain.h>
#include <TH1D.h>
#include <TFile.h>
#include <TFileCollection.h>
#include <TCollection.h>

using namespace std;

Int_t main(Int_t argc, Char_t *argv[]) {


  TString magnet = argv[1];
  TString year   = argv[2];

  TH1D * hB2HH = new TH1D("hB2HH","hB2HH",500,0,1000);
  hB2HH->Sumw2();
  TH1D * hD2HH = new TH1D("hD2HH","hD2HH",500,0,1000);
  hD2HH->Sumw2();
  TH1D * hL2HH = new TH1D("hL2HH","hL2HH",500,0,1000);
  hL2HH->Sumw2();

  Int_t nSPD = 0; Double_t weight = 0;
  TChain * chain = new TChain("b2hh","b2hh");
  TFileCollection * b2hhList = new TFileCollection("b2hhList","b2hhList",
                                                   Form("../../Data/selectedLists/list_b2hh_%s_%s.txt",magnet.Data(),year.Data()));
  chain->AddFileInfoList((TCollection *) b2hhList->GetList());
  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("nSPDHits",1);
  chain->SetBranchAddress("nSPDHits",&nSPD);
  for(Int_t ientry = 0, nentries = chain->GetEntries(); ientry < nentries; ++ientry) {

    chain->GetEntry(ientry);
    hB2HH->Fill(nSPD);

  }
  chain->Reset();

  chain = new TChain("Kplus_tot","Kplus_tot");
  TFileCollection * d2hhList = new TFileCollection("d2hhList","d2hhList",
                                                   Form("../PIDcalibLists/list_Kplus_%s_%s.txt",magnet.Data(),year.Data()));
  chain->AddFileInfoList((TCollection*) d2hhList->GetList());
  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("nSPDHits",1);
  chain->SetBranchStatus("weight",1);
  chain->SetBranchAddress("nSPDHits",&nSPD);
  chain->SetBranchAddress("weight",&weight);
  for(Int_t ientry = 0, nentries = chain->GetEntries(); ientry < nentries; ++ientry) {

    chain->GetEntry(ientry);
    hD2HH->Fill(nSPD,weight);

  }
  chain->Reset();

  chain = new TChain("Pplus_tot","Pplus_tot");
  TFileCollection * l2hhList = new TFileCollection("l2hhList","l2hhList",
                                                   Form("../PIDcalibLists/list_Pplus_%s_%s.txt",magnet.Data(),year.Data()));
  chain->AddFileInfoList((TCollection*) l2hhList->GetList());
  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("nSPDHits",1);
  chain->SetBranchStatus("weight",1);
  chain->SetBranchAddress("nSPDHits",&nSPD);
  chain->SetBranchAddress("weight",&weight);
  for(Int_t ientry = 0, nentries = chain->GetEntries(); ientry < nentries; ++ientry) {

    chain->GetEntry(ientry);
    hL2HH->Fill(nSPD,weight);

  }
  chain->Reset();


  hB2HH->Scale(1./hB2HH->Integral("width"));
  hD2HH->Scale(1./hD2HH->Integral("width"));
  hL2HH->Scale(1./hL2HH->Integral("width"));

  TFile * outFile = new TFile(Form("nSPD_%s_%s.root",magnet.Data(),year.Data()),"RECREATE");
  outFile->WriteTObject(hB2HH,"","Overwrite");
  outFile->WriteTObject(hD2HH,"","Overwrite");
  outFile->WriteTObject(hL2HH,"","Overwrite");
  outFile->Close();

  return 0;

}

