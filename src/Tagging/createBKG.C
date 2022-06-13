#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <optionParser.h>
#include <makePull.h>
#include <TROOT.h>
#include <TString.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TCanvas.h>
#include <TF1.h>

#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>
#include "TRandom.h"
using namespace std;

Int_t main(Int_t argc, Char_t * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./createBKG [options]\n");
    printf("Options:\n");
    printf("  -C <bdtConf>    : configuration of trained BDT (default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = -1)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2011,2012,Tot], default = Tot)\n");
    printf("  -f <finalState> : final state hypothesis (default = kpi)\n");
    printf("  -c <cut>        : pid cuts depending on final state (default = 5.-2.-5.3)\n");
    return 0;
  }

  TString configuration = getOption(argc,argv,"-C","PIPI");
  Double_t bdtCut       = atof(getOption(argc,argv,"-b","-1"));
  TString magnet        = getOption(argc,argv,"-m","Tot");
  TString year          = getOption(argc,argv,"-y","Tot");
  TString finalState   = getOption(argc,argv,"-f","kpi");
  TString cuts          = getOption(argc,argv,"-c","5.-2.-5.3");
  Int_t pidPlus1        = atoi(((TObjString *)cuts.Tokenize('.')->At(0))->String());
  Int_t pidPlus2        = atoi(((TObjString *)cuts.Tokenize('.')->At(1))->String());
  Int_t pidMinus1       = atoi(((TObjString *)cuts.Tokenize('.')->At(2))->String());
  Int_t pidMinus2       = atoi(((TObjString *)cuts.Tokenize('.')->At(3))->String());

  printf("EXECUTING ./createBKG -C %s -b %g -m %s -y %s -f %s -c %d.%d.%d.%d\n",
         configuration.Data(),bdtCut,magnet.Data(),year.Data(),
         finalState.Data(),pidPlus1,pidPlus2,pidMinus1,pidMinus2);

  Double_t minMassWinBkg = tagging_cuts::massMinBkg;
  Double_t maxMassWinBkg = tagging_cuts::massMaxBkg;

  gROOT->SetStyle("Plain");

  Double_t mass = 0, etaOS = 0, etaSSk = 0, etaSSpiBDT = 0, etaSSp = 0, etaSS = 0;

  Int_t fState = 0, stateCut = 0;
  
  if     (finalState=="kpi")  stateCut = datasetFlags::spectrumKPI;
  else if(finalState=="pipi") stateCut = datasetFlags::spectrumPIPI;
  else if(finalState=="kk")   stateCut = datasetFlags::spectrumKK;
  stateCut += datasetFlags::yearFlags[year];
  
  TH1D * hetaOS_bkg          = new TH1D("hetaOS_bkg","hetaOS_bkg",50,0,0.5);
  TH1D * hetaSSk_bkg         = new TH1D("hetaSSk_bkg","hetaSSk_bkg",50,0,0.5);
  TH1D * hetaSSpiBDT_bkg     = new TH1D("hetaSSpiBDT_bkg","hetaSSpiBDT_bkg",100,0,0.5);
  TH1D * hetaSSp_bkg         = new TH1D("hetaSSp_bkg","hetaSSp_bkg",100,0,0.5);
  TH1D * hetaSS_bkg          = new TH1D("hetaSS_bkg","hetaSS_bkg",100,0,0.5);
  TH1D * hetaOS_physTmp      = new TH1D("hetaOS_physTmp","hetaOS_physTmp",50,0,0.5);
  TH1D * hetaSSk_physTmp     = new TH1D("hetaSSk_physTmp","hetaSSk_physTmp",50,0,0.5);
  TH1D * hetaSSpiBDT_physTmp = new TH1D("hetaSSpiBDT_physTmp","hetaSSpiBDT_physTmp",100,0,0.5);
  TH1D * hetaSSp_physTmp     = new TH1D("hetaSSp_physTmp","hetaSSp_physTmp",100,0,0.5);
  TH1D * hetaSS_physTmp      = new TH1D("hetaSS_physTmp","hetaSS_physTmp",100,0,0.5);

  hetaOS_bkg->Sumw2();
  hetaSSk_bkg->Sumw2();
  hetaSSpiBDT_bkg->Sumw2();
  hetaSSp_bkg->Sumw2();
  hetaSS_bkg->Sumw2();
  hetaOS_physTmp->Sumw2();
  hetaSSk_physTmp->Sumw2();
  hetaSSpiBDT_physTmp->Sumw2();
  hetaSSp_physTmp->Sumw2();
  hetaSS_physTmp->Sumw2();

  TChain * inChain = new TChain("b2hh","b2hh");
  inChain->Add(Form("${B2HH_OUT}/Reduce/b2hh_%s_%g_%s_%s.root/b2hh",configuration.Data(),bdtCut,year.Data(),magnet.Data()));
  inChain->SetBranchAddress("mass",&mass);
  inChain->SetBranchAddress("fState",&fState);
  inChain->SetBranchAddress("etaOS",&etaOS);
  inChain->SetBranchAddress("etaSSk",&etaSSk);
  inChain->SetBranchAddress("etaSSpi",&etaSSpiBDT);
  inChain->SetBranchAddress("etaSSp",&etaSSp);
  inChain->SetBranchAddress("etaSS",&etaSS);

  Int_t nEntries = inChain->GetEntries();
  gRandom->SetSeed(nEntries);
  for(Int_t iEntry = 0; iEntry < nEntries; iEntry++) {

    inChain->GetEntry(iEntry);

    if(fState!=stateCut) continue;

    if(mass>minMassWinBkg&&mass<maxMassWinBkg) {
      hetaOS_bkg->Fill(etaOS);
      hetaSSk_bkg->Fill(gRandom->Uniform(0.0, 0.5));
      hetaSSpiBDT_bkg->Fill(gRandom->Uniform(0.0, 0.5));
      hetaSSp_bkg->Fill(gRandom->Uniform(0.0, 0.5));
      hetaSS_bkg->Fill(gRandom->Uniform(0.0, 0.5));
    }
    else if(mass<tagging_cuts::massMaxPhys&&mass>tagging_cuts::massMinPhys) {
      hetaOS_physTmp->Fill(etaOS);
      hetaSSk_physTmp->Fill(gRandom->Uniform(0.0, 0.5));
      hetaSSpiBDT_physTmp->Fill(gRandom->Uniform(0.0, 0.5));
      hetaSSp_physTmp->Fill(gRandom->Uniform(0.0, 0.5));
      hetaSS_physTmp->Fill(gRandom->Uniform(0.0, 0.5));
    }
  }

  TF1 * myExpo = new TF1("myExpo","[0]*exp(-[0]*x)/(exp(-[0]*[1])-exp(-[0]*[2]))",minMassWinBkg,maxMassWinBkg);
  myExpo->SetParameter(0, 0.5);
  myExpo->FixParameter(1, minMassWinBkg);
  myExpo->FixParameter(2, maxMassWinBkg);
  inChain->UnbinnedFit("myExpo", "mass",
                       Form("fState==%d&&mass>%g&&mass<%g&&time>%g&&time<%g&&timeErr<%g", 
                            stateCut,minMassWinBkg,maxMassWinBkg,tagging_cuts::timeMin,tagging_cuts::timeMax, tagging_cuts::timeErrMax),
                       "Q");
  Double_t alpha = myExpo->GetParameter(0); 
  Double_t scale = (exp(-alpha*5.0)-exp(-alpha*5.2))/(exp(-alpha*minMassWinBkg)-exp(-alpha*maxMassWinBkg));

  hetaOS_physTmp->Smooth(1,"r");
  hetaOS_bkg->Smooth(1,"r");

  TH1D * hetaOS_phys = (TH1D *) hetaOS_physTmp->Clone("hetaOS_phys");
  subtractHistos(hetaOS_phys,hetaOS_bkg,scale);
  TH1D * hetaSSk_phys = (TH1D *) hetaSSk_physTmp->Clone("hetaSSk_phys");
  subtractHistos(hetaSSk_phys,hetaSSk_bkg,scale);
  TH1D * hetaSSpiBDT_phys = (TH1D *) hetaSSpiBDT_physTmp->Clone("hetaSSpiBDT_phys");
  subtractHistos(hetaSSpiBDT_phys,hetaSSpiBDT_bkg,scale);
  TH1D * hetaSSp_phys = (TH1D *) hetaSSp_physTmp->Clone("hetaSSp_phys");
  subtractHistos(hetaSSp_phys,hetaSSp_bkg,scale);
  TH1D * hetaSS_phys = (TH1D *) hetaSS_physTmp->Clone("hetaSS_phys");
  subtractHistos(hetaSS_phys,hetaSS_bkg,scale);

  //TH1D * hetaOS_phys= subtractHistos(hetaOS_phys,hetaOS_bkg,"hetaOS_phys",scale);
  //TH1D * hetaSSk_phys= subtractHistos(hetaSSk_phys,hetaSSk_bkg,"hetaSSk_phys",scale);
  //TH1D * hetaSSpiBDT_phys= subtractHistos(hetaSSpiBDT_phys,hetaSSpiBDT_bkg,"hetaSSpiBDT_phys",scale);
  //TH1D * hetaSSp_phys= subtractHistos(hetaSSp_phys,hetaSSp_bkg,"hetaSSp_phys",scale);
  //TH1D * hetaSS_phys= subtractHistos(hetaSS_phys,hetaSS_bkg,"hetaSS_phys",scale);
  setStyle(hetaOS_bkg,kBlack,2,1,3001,"#eta_{OS}","Normalized Units"); setToZero(hetaOS_bkg);
  setStyle(hetaOS_phys,kBlue,2,1,3001,"#eta_{OS}","Normalized Units"); setToZero(hetaOS_phys);
  setStyle(hetaOS_phys,kRed,2,1,3001,"#eta_{OS}","Normalized Units"); setToZero(hetaOS_phys);

  setStyle(hetaSSk_bkg,kBlack,2,1,3001,"#eta_{SSk}","Normalized Units"); setToZero(hetaSSk_bkg);
  setStyle(hetaSSk_phys,kBlue,2,1,3001,"#eta_{SSk}","Normalized Units"); setToZero(hetaSSk_phys);
  setStyle(hetaSSk_phys,kRed,2,1,3001,"#eta_{SSk}","Normalized Units"); setToZero(hetaSSk_phys);

  setStyle(hetaSSpiBDT_bkg,kBlack,2,1,3001,"#eta_{SS#piBDT}","Normalized Units"); setToZero(hetaSSpiBDT_bkg);
  setStyle(hetaSSpiBDT_phys,kBlue,2,1,3001,"#eta_{SS#piBDT}","Normalized Units"); setToZero(hetaSSpiBDT_phys);
  setStyle(hetaSSpiBDT_phys,kRed,2,1,3001,"#eta_{SS#piBDT}","Normalized Units"); setToZero(hetaSSpiBDT_phys);

  setStyle(hetaSSp_bkg,kBlack,2,1,3001,"#eta_{SSp}","Normalized Units"); setToZero(hetaSSp_bkg);
  setStyle(hetaSSp_phys,kBlue,2,1,3001,"#eta_{SSp}","Normalized Units"); setToZero(hetaSSp_phys);
  setStyle(hetaSSp_phys,kRed,2,1,3001,"#eta_{SSp}","Normalized Units"); setToZero(hetaSSp_phys);

  setStyle(hetaSS_bkg,kBlack,2,1,3001,"#eta_{SS}","Normalized Units"); setToZero(hetaSS_bkg);
  setStyle(hetaSS_phys,kBlue,2,1,3001,"#eta_{SS}","Normalized Units"); setToZero(hetaSS_phys);
  setStyle(hetaSS_phys,kRed,2,1,3001,"#eta_{SS}","Normalized Units"); setToZero(hetaSS_phys);

  TFile * outFile = new TFile(Form("${B2HH_OUT}/Tagging/templates/%s_%s_%g_%s_%s.root",
                                   finalState.Data(),configuration.Data(),
                                   bdtCut,year.Data(),magnet.Data()),"UPDATE");

  std::vector<TString> postFixes = {"","1","2"};
  for(auto postFix: postFixes) {
    shiftToZero(hetaOS_phys);
    shiftToZero(hetaOS_bkg);
    shiftToZero(hetaSSk_phys);
    shiftToZero(hetaSSk_bkg);
    shiftToZero(hetaSSpiBDT_phys);
    shiftToZero(hetaSSpiBDT_bkg);
    shiftToZero(hetaSSp_phys);
    shiftToZero(hetaSSp_bkg);
    shiftToZero(hetaSS_phys);
    shiftToZero(hetaSS_bkg);

    //hetaOS_phys->Smooth(1,"r");
    //hetaSSk_phys->Smooth(1,"r");
    //hetaSSpiBDT_phys->Smooth(1,"r");
    //hetaSSp_phys->Smooth(1,"r");
    //hetaSS_phys->Smooth(1,"r");

    //hetaOS_bkg->Smooth(1,"r");
    //hetaSSk_bkg->Smooth(1,"r");
    //hetaSSpiBDT_bkg->Smooth(1,"r");
    //hetaSSp_bkg->Smooth(1,"r");
    //hetaSS_bkg->Smooth(1,"r");

    hetaOS_phys->Scale(1./hetaOS_phys->Integral("width")); 
    hetaSSk_phys->Scale(1./hetaSSk_phys->Integral("width")); 
    hetaSSpiBDT_phys->Scale(1./hetaSSpiBDT_phys->Integral("width")); 
    hetaSSp_phys->Scale(1./hetaSSp_phys->Integral("width")); 
    hetaSS_phys->Scale(1./hetaSS_phys->Integral("width")); 

    hetaOS_bkg->Scale(1./hetaOS_bkg->Integral("width"));
    hetaSSk_bkg->Scale(1./hetaSSk_bkg->Integral("width"));
    hetaSSpiBDT_bkg->Scale(1./hetaSSpiBDT_bkg->Integral("width"));
    hetaSSp_bkg->Scale(1./hetaSSp_bkg->Integral("width"));
    hetaSS_bkg->Scale(1./hetaSS_bkg->Integral("width"));

    outFile->WriteTObject(hetaOS_phys,Form("h_phys_%s%s_etaOS",
                                              finalState.Data(),postFix.Data()),"Overwrite");
    outFile->WriteTObject(hetaOS_bkg,Form("h_bkg_%s_etaOS",finalState.Data()),"Overwrite");
  
    outFile->WriteTObject(hetaSSk_phys,Form("h_phys_%s%s_etaSSk",
                                              finalState.Data(),postFix.Data()),"Overwrite");
    outFile->WriteTObject(hetaSSk_bkg,Form("h_bkg_%s_etaSSk",finalState.Data()),"Overwrite");

    outFile->WriteTObject(hetaSSpiBDT_phys,Form("h_phys_%s%s_etaSSpi",
                                              finalState.Data(),postFix.Data()),"Overwrite");
    outFile->WriteTObject(hetaSSpiBDT_bkg,Form("h_bkg_%s_etaSSpi",finalState.Data()),"Overwrite");

    outFile->WriteTObject(hetaSSp_phys,Form("h_phys_%s%s_etaSSp",
                                              finalState.Data(),postFix.Data()),"Overwrite");
    outFile->WriteTObject(hetaSSp_bkg,Form("h_bkg_%s_etaSSp",finalState.Data()),"Overwrite");

    outFile->WriteTObject(hetaSS_phys,Form("h_phys_%s%s_etaSS",
                                              finalState.Data(),postFix.Data()),"Overwrite");
    outFile->WriteTObject(hetaSS_bkg,Form("h_bkg_%s_etaSS",finalState.Data()),"Overwrite");
  }
  for (TH1 *h : {hetaSS_bkg, hetaSS_phys, hetaSSk_bkg, hetaSSk_phys, hetaOS_bkg, hetaOS_phys})
  {
    TCanvas *c = new TCanvas("c_" + TString(h->GetName()),
                             "c_" + TString(h->GetName()));
    h->Draw();
    c->SaveAs(Form("${B2HH_OUT}/Tagging/plots/%s_%s_%g_%s_%s.root",
                   finalState.Data(), configuration.Data(),
                   bdtCut, year.Data(), magnet.Data()));
    c->SaveAs(Form("${B2HH_OUT}/Tagging/plots/%s_%s_%g_%s_%s.pdf",
                   finalState.Data(), configuration.Data(),
                   bdtCut, year.Data(), magnet.Data()));
  }

  outFile->Close();

  return 0;

} 
