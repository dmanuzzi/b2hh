#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TChain.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TF1.h>
#include <TString.h>
#include <TFile.h>
#include <optionParser.h>
#include <makePull.h>

#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>
#include "TRandom.h"
using namespace std;

Int_t main(Int_t argc, Char_t * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./reduce [options]\n");
    printf("Options:\n");
    printf("  -n <name>   : decay used for BDT train ([PIPI, KK], default = PIPI)\n");
    printf("  -b <bdtCut> : cut on BDT (default = 0.04)\n");
    printf("  -m <magnet> : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>   : year of data taking ([2015,2016,Tot], default = Tot)\n");
    printf("  -f <fState> : considered final state [0=pipi,1=kpi,2=kk] (default = 0)\n");
    printf("  -r <range>  : center signal range around [bd,bs] (default = bd)\n");
    return 0;
  }

  TString name = getOption(argc,argv,"-n","PIPI");
  TString bdtCut = getOption(argc,argv,"-b","0.04");
  TString magnet = getOption(argc,argv,"-m","Tot");
  TString year = getOption(argc,argv,"-y","Tot");
  TString range = getOption(argc,argv,"-r","bd");
  Int_t finalStateIdx = atoi(getOption(argc,argv,"-f","0"));
  TString finalState;
  switch(finalStateIdx) {
    case 0: finalState = "pipi";
            break;
    case 1: finalState = "kpi";
            break;
    case 2: finalState = "kk";
            break;
  }
  finalStateIdx += datasetFlags::yearFlags[year];
  
  printf("makeTemplates: finalState = %s, finalStateIDx = %d\n",finalState.Data(),finalStateIdx);
  Double_t massMin = (range == "bd" ? tagging_cuts::massMinBd : tagging_cuts::massMinBs);
  Double_t massMax = (range == "bd" ? tagging_cuts::massMaxBd : tagging_cuts::massMaxBs);
  Double_t massMinBkg = tagging_cuts::massMinBkg;
  Double_t massMaxBkg = tagging_cuts::massMaxBkg;

  TApplication myApp("myApp",&argc,argv);

  Int_t fState = 0, nSPDHits = 0;
  Double_t bPT = 0, mass = 0, time = 0, timeErr = 0, 
           etaSSpi = 0, etaSSp = 0, etaSS = 0, etaSSk = 0;

  TChain * chain = new TChain("b2hh","b2hh");
  chain->Add(Form("${B2HH_OUT}/Reduce/b2hh_%s_%s_%s_%s.root",name.Data(),bdtCut.Data(),year.Data(),magnet.Data()));
  chain->SetBranchAddress("bPT",     &bPT);
  chain->SetBranchAddress("nSPDHits",&nSPDHits);
  chain->SetBranchAddress("fState",  &fState); 
  chain->SetBranchAddress("mass",    &mass);
  chain->SetBranchAddress("time",    &time);
  chain->SetBranchAddress("timeErr", &timeErr);
  chain->SetBranchAddress("etaSSpi", &etaSSpi);
  chain->SetBranchAddress("etaSSp",  &etaSSp);
  chain->SetBranchAddress("etaSS",   &etaSS);
  chain->SetBranchAddress("etaSSk",  &etaSSk);

  TH1D * h_b2hh_PT     = new TH1D("h_b2hh_PT",    "h_b2hh_PT",50,0,50);               h_b2hh_PT->Sumw2();
  TH1D * h_bkg_PT      = (TH1D *) h_b2hh_PT->Clone("h_bkg_PT");
  TH1D * h_b2hh_SPD    = new TH1D("h_b2hh_SPD",   "h_b2hh_SPD",20,0,1000);            h_b2hh_SPD->Sumw2();
  TH1D * h_bkg_SPD     = (TH1D *) h_b2hh_SPD->Clone("h_bkg_SPD");
  TH2D * h_b2hh_PT_SPD = new TH2D("h_b2hh_PT_SPD","h_b2hh_PT_SPD",50,0,50,20,0,1000); h_b2hh_PT_SPD->Sumw2();
  TH2D * h_bkg_PT_SPD  = (TH2D *) h_b2hh_PT_SPD->Clone("h_bkg_PT_SPD");

  TH1D * h_b2hh_etaSSpi = new TH1D("h_b2hh_etaSSpi","h_b2hh_etaSSpi",100,0,0.5); h_b2hh_etaSSpi->Sumw2();
  TH1D * h_bkg_etaSSpi  = new TH1D("h_bkg_etaSSpi", "h_bkg_etaSSpi", 100,0,0.5); h_bkg_etaSSpi->Sumw2();
  TH1D * h_b2hh_etaSSp  = new TH1D("h_b2hh_etaSSp", "h_b2hh_etaSSp", 100,0,0.5); h_b2hh_etaSSp->Sumw2();
  TH1D * h_bkg_etaSSp   = new TH1D("h_bkg_etaSSp",  "h_bkg_etaSSp",  100,0,0.5); h_bkg_etaSSp->Sumw2();
  TH1D * h_b2hh_etaSS   = new TH1D("h_b2hh_etaSS",  "h_b2hh_etaSS",  100,0,0.5); h_b2hh_etaSS->Sumw2();
  TH1D * h_bkg_etaSS    = new TH1D("h_bkg_etaSS",   "h_bkg_etaSS",   100,0,0.5); h_bkg_etaSS->Sumw2();
  TH1D * h_b2hh_etaSSk  = new TH1D("h_b2hh_etaSSk", "h_b2hh_etaSSk", 50,0,0.5);  h_b2hh_etaSSk->Sumw2();
  TH1D * h_bkg_etaSSk   = new TH1D("h_bkg_etaSSk",  "h_bkg_etaSSk",  50,0,0.5);  h_bkg_etaSSk->Sumw2();
  gRandom->SetSeed(chain->GetEntries());
  Bool_t selection = false;
  for(Int_t iEntry = 0, nEntries = chain->GetEntries(); iEntry < nEntries; ++iEntry) {

    chain->GetEntry(iEntry);
    selection = fState==finalStateIdx&&
                time>accSignal_cuts::minTimeFit&&
                time<accSignal_cuts::maxTimeFit&&
                timeErr<accSignal_cuts::maxTimeFit;
    // if(!selection) continue;
    if(mass>massMin&&mass<massMax) { 
      h_b2hh_PT->Fill(bPT); 
      h_b2hh_SPD->Fill(nSPDHits);
      h_b2hh_PT_SPD->Fill(bPT,nSPDHits);
      h_b2hh_etaSSpi->Fill(gRandom->Uniform(0.0, 0.5));
      h_b2hh_etaSSp->Fill(gRandom->Uniform(0.0, 0.5));
      h_b2hh_etaSS->Fill(gRandom->Uniform(0.0, 0.5));
      h_b2hh_etaSSk->Fill(gRandom->Uniform(0.0, 0.5));
    }
    else if(mass>massMinBkg&&mass<massMaxBkg) {
      h_bkg_PT->Fill(bPT);
      h_bkg_SPD->Fill(nSPDHits);
      h_bkg_PT_SPD->Fill(bPT,nSPDHits);
      h_bkg_etaSSpi->Fill(gRandom->Uniform(0.0, 0.5));
      h_bkg_etaSSp->Fill(gRandom->Uniform(0.0, 0.5));
      h_bkg_etaSS->Fill(gRandom->Uniform(0.0, 0.5));
      h_bkg_etaSSk->Fill(gRandom->Uniform(0.0, 0.5));
    }

  }

  TF1 * myExpo = new TF1("myExpo","[0]*exp(-[0]*x)/(exp(-[0]*[1])-exp(-[0]*[2]))",massMinBkg,massMaxBkg);
  myExpo->SetParameter(0,0.1);
  myExpo->FixParameter(1, massMinBkg);
  myExpo->FixParameter(2, massMaxBkg);

  chain->UnbinnedFit("myExpo","mass",
                     Form("fState==%d&&mass>%g&&mass<%g&&time>0.2&&time<14.2&&timeErr<0.1",finalStateIdx, massMinBkg,massMaxBkg),"Q");
  Double_t alpha = myExpo->GetParameter(0);
  Double_t myRatio = (exp(-alpha*massMin)-exp(-alpha*massMax))/(exp(-alpha*massMinBkg)-exp(-alpha*massMaxBkg));
  printf("makeTemplates: myRatio = %g\n",myRatio);

  h_b2hh_PT->Add(h_bkg_PT,-myRatio);
  h_b2hh_SPD->Add(h_bkg_SPD,-myRatio);
  h_b2hh_PT_SPD->Add(h_bkg_PT_SPD,-myRatio);

  h_b2hh_etaSSpi->Add(h_bkg_etaSSpi,-myRatio);
  h_b2hh_etaSSp->Add(h_bkg_etaSSp,-myRatio);
  h_b2hh_etaSS->Add(h_bkg_etaSS,-myRatio);
  h_b2hh_etaSSk->Add(h_bkg_etaSSk,-myRatio);


  h_b2hh_PT->Scale(1./h_b2hh_PT->Integral("width"));
  h_b2hh_SPD->Scale(1./h_b2hh_SPD->Integral("width"));
  h_b2hh_PT_SPD->Scale(1./h_b2hh_PT_SPD->Integral("width"));


  TFile * outFile = TFile::Open(Form("${B2HH_OUT}/Tagging/templates/%s_%s_%s_%s_%s.root",
                                     finalState.Data(),name.Data(),bdtCut.Data(),year.Data(),magnet.Data()),
                                "UPDATE");
  shiftToZero(h_b2hh_etaSSpi);
  shiftToZero(h_b2hh_etaSSp);
  shiftToZero(h_b2hh_etaSS);
  shiftToZero(h_b2hh_etaSSk);
  //h_b2hh_etaSSpi->Smooth(1,"r");
  //h_b2hh_etaSSp->Smooth(1,"r");
  //h_b2hh_etaSS->Smooth(1,"r");
  //h_b2hh_etaSSk->Smooth(1,"r");
  h_b2hh_etaSSpi->Scale(1./h_b2hh_etaSSpi->Integral("width"));
  h_b2hh_etaSSp->Scale(1./h_b2hh_etaSSp->Integral("width"));
  h_b2hh_etaSS->Scale(1./h_b2hh_etaSS->Integral("width"));
  h_b2hh_etaSSk->Scale(1./h_b2hh_etaSSk->Integral("width"));

  outFile->WriteTObject(h_b2hh_PT,    Form("h_%s%s_PT",    range.Data(),finalState.Data()),"Overwrite");
  outFile->WriteTObject(h_b2hh_SPD,   Form("h_%s%s_SPD",   range.Data(),finalState.Data()),"Overwrite");
  outFile->WriteTObject(h_b2hh_PT_SPD,Form("h_%s%s_PT_SPD",range.Data(),finalState.Data()),"Overwrite");

  outFile->WriteTObject(h_b2hh_etaSSpi,Form("h_%s%s_etaSSpi",range.Data(),finalState.Data()),"Overwrite");
  outFile->WriteTObject(h_b2hh_etaSSp, Form("h_%s%s_etaSSp", range.Data(),finalState.Data()),"Overwrite");
  outFile->WriteTObject(h_b2hh_etaSS,  Form("h_%s%s_etaSS",  range.Data(),finalState.Data()),"Overwrite");
  outFile->WriteTObject(h_b2hh_etaSSk, Form("h_%s%s_etaSSk", range.Data(),finalState.Data()),"Overwrite");

  for (TH1* h : {h_b2hh_etaSSk, h_b2hh_etaSS}){
    TCanvas *c = new TCanvas("c_"+TString(h->GetName()),
                             "c_"+TString(h->GetName()));
    h->Draw();
    c->SaveAs(Form("${B2HH_OUT}/Tagging/plots/%s_%s_%s_%s_%s.root",
                   finalState.Data(), name.Data(), bdtCut.Data(), year.Data(), magnet.Data()));
    c->SaveAs(Form("${B2HH_OUT}/Tagging/plots/%s_%s_%s_%s_%s.pdf",
                   finalState.Data(), name.Data(), bdtCut.Data(), year.Data(), magnet.Data()));
  }

  outFile->Close();

  return 0;

}
