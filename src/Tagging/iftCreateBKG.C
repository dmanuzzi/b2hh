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

    Double_t mass = 0, etaIFT_Bd = 0, etaIFT_Bs = 0, etaDummy = 0;

    Int_t fState = 0, stateCut = 0;
    
    if     (finalState=="kpi")  stateCut = datasetFlags::spectrumKPI;
    else if(finalState=="pipi") stateCut = datasetFlags::spectrumPIPI;
    else if(finalState=="kk")   stateCut = datasetFlags::spectrumKK;
    stateCut += datasetFlags::yearFlags[year];
    
    TH1D * hetaIFT_Bd_bkg = new TH1D("hetaIFT_Bd_bkg","hetaIFT_Bd_bkg",50,0,0.5);
    TH1D * hetaIFT_Bs_bkg = new TH1D("hetaIFT_Bs_bkg","hetaIFT_Bs_bkg",50,0,0.5);
    TH1D * hetaDummy_bkg  = new TH1D("hetaDummy_bkg", "hetaDummy_bkg", 50,0,0.5);
    TH1D * hetaIFT_Bd_physTmp = new TH1D("hetaIFT_Bd_physTmp","hetaIFT_Bd_physTmp",50,0,0.5);
    TH1D * hetaIFT_Bs_physTmp = new TH1D("hetaIFT_Bs_physTmp","hetaIFT_Bs_physTmp",50,0,0.5);
    TH1D * hetaDummy_physTmp  = new TH1D("hetaDummy_physTmp", "hetaDummy_physTmp", 50,0,0.5);
    hetaIFT_Bd_bkg->Sumw2();
    hetaIFT_Bs_bkg->Sumw2();
    hetaDummy_bkg->Sumw2();
    hetaIFT_Bd_physTmp->Sumw2();
    hetaIFT_Bs_physTmp->Sumw2();
    hetaDummy_physTmp->Sumw2();


    TChain * inChain = new TChain("b2hh","b2hh");
    inChain->Add(Form("${B2HH_OUT}/Reduce/b2hh_%s_%g_%s_%s.root/b2hh",configuration.Data(),bdtCut,year.Data(),magnet.Data()));
    inChain->SetBranchAddress("mass",&mass);
    inChain->SetBranchAddress("fState",&fState);
    inChain->SetBranchAddress("etaIFT_Bd",&etaIFT_Bd);
    inChain->SetBranchAddress("etaIFT_Bs",&etaIFT_Bs);
    inChain->SetBranchAddress("etaDummy",&etaDummy);

    Int_t nEntries = inChain->GetEntries();
    for(Int_t iEntry = 0; iEntry < nEntries; iEntry++) {

        inChain->GetEntry(iEntry);

        if(fState!=stateCut) continue;

        if(mass>minMassWinBkg&&mass<maxMassWinBkg) {
            hetaIFT_Bd_bkg->Fill(etaIFT_Bd);
            hetaIFT_Bs_bkg->Fill(etaIFT_Bs);
            hetaDummy_bkg->Fill(etaDummy);
        }
        else if(mass<tagging_cuts::massMaxPhys&&mass>tagging_cuts::massMinPhys) {
            hetaIFT_Bd_physTmp->Fill(etaIFT_Bd);
            hetaIFT_Bs_physTmp->Fill(etaIFT_Bs);
            hetaDummy_physTmp->Fill(etaDummy);
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

    //hetaOS_physTmp->Smooth(1,"r");
    //hetaOS_bkg->Smooth(1,"r");

    TH1D * hetaIFT_Bd_phys = (TH1D *) hetaIFT_Bd_physTmp->Clone("hetaIFT_Bd_phys");
    subtractHistos(hetaIFT_Bd_phys,hetaIFT_Bd_bkg,scale);
    TH1D * hetaIFT_Bs_phys = (TH1D *) hetaIFT_Bs_physTmp->Clone("hetaIFT_Bs_phys");
    subtractHistos(hetaIFT_Bs_phys,hetaIFT_Bs_bkg,scale);
    TH1D * hetaDummy_phys = (TH1D *) hetaDummy_physTmp->Clone("hetaDummy_phys");
    subtractHistos(hetaDummy_phys,hetaDummy_bkg,scale);


    setStyle(hetaIFT_Bd_bkg,  kBlack,2,1,3001,"#eta_{IFT B^{0}}","Normalized Units"); setToZero(hetaIFT_Bd_bkg);
    setStyle(hetaIFT_Bd_phys,  kBlue,2,1,3001,"#eta_{IFT B^{0}}","Normalized Units"); setToZero(hetaIFT_Bd_phys);
    setStyle(hetaIFT_Bd_physTmp,kRed,2,1,3001,"#eta_{IFT B^{0}}","Normalized Units"); setToZero(hetaIFT_Bd_physTmp);
    setStyle(hetaIFT_Bs_bkg,  kBlack,2,1,3001,"#eta_{IFT B_{s}^{0}}","Normalized Units"); setToZero(hetaIFT_Bs_bkg);
    setStyle(hetaIFT_Bs_phys,  kBlue,2,1,3001,"#eta_{IFT B_{s}^{0}}","Normalized Units"); setToZero(hetaIFT_Bs_phys);
    setStyle(hetaIFT_Bs_physTmp,kRed,2,1,3001,"#eta_{IFT B_{s}^{0}}","Normalized Units"); setToZero(hetaIFT_Bs_physTmp);

    setStyle(hetaDummy_bkg,  kBlack,2,1,3001,"#eta","Normalized Units"); setToZero(hetaDummy_bkg);
    setStyle(hetaDummy_phys,  kBlue,2,1,3001,"#eta","Normalized Units"); setToZero(hetaDummy_phys);
    setStyle(hetaDummy_physTmp,kRed,2,1,3001,"#eta","Normalized Units"); setToZero(hetaDummy_physTmp);

    TString outFileName = Form("${B2HH_OUT}/Tagging/iftTemplates/%s_%g_%s_%s_%s.root",
                                   configuration.Data(),bdtCut,
                                   finalState.Data(),year.Data(),magnet.Data());
    printf("saving file to... %s", outFileName.Data());
    TFile * outFile = new TFile(outFileName,"UPDATE");

    std::vector<TString> postFixes = {"","1","2"};
    for(auto postFix: postFixes) {
        shiftToZero(hetaIFT_Bd_phys);
        shiftToZero(hetaIFT_Bd_bkg);
        shiftToZero(hetaIFT_Bs_phys);
        shiftToZero(hetaIFT_Bs_bkg);
        shiftToZero(hetaDummy_phys);
        shiftToZero(hetaDummy_bkg);

        hetaIFT_Bd_phys->Scale(1./hetaIFT_Bd_phys->Integral("width")); 
        hetaIFT_Bd_bkg->Scale(1./hetaIFT_Bd_bkg->Integral("width")); 
        hetaIFT_Bs_phys->Scale(1./hetaIFT_Bs_phys->Integral("width")); 
        hetaIFT_Bs_bkg->Scale(1./hetaIFT_Bs_bkg->Integral("width")); 
        hetaDummy_phys->Scale(1./hetaDummy_phys->Integral("width")); 
        hetaDummy_bkg->Scale(1./hetaDummy_bkg->Integral("width")); 

        outFile->WriteTObject(hetaIFT_Bd_phys,Form("h_phys_%s%s_etaIFT_Bd",
                                                finalState.Data(),postFix.Data()),"Overwrite");
        outFile->WriteTObject(hetaIFT_Bd_bkg, Form("h_bkg_%s_etaIFT_Bd",finalState.Data()),"Overwrite");
    
        outFile->WriteTObject(hetaIFT_Bs_phys,Form("h_phys_%s%s_etaIFT_Bs",
                                                finalState.Data(),postFix.Data()),"Overwrite");
        outFile->WriteTObject(hetaIFT_Bs_bkg, Form("h_bkg_%s_etaIFT_Bs",finalState.Data()),"Overwrite");

        outFile->WriteTObject(hetaDummy_phys,Form("h_phys_%s%s_etaDummy",
                                                finalState.Data(),postFix.Data()),"Overwrite");
        outFile->WriteTObject(hetaDummy_bkg,Form("h_bkg_%s_etaDummy",finalState.Data()),"Overwrite");
    }
    for (TH1 *h : {hetaIFT_Bd_bkg, hetaIFT_Bd_phys, hetaIFT_Bs_bkg, hetaIFT_Bs_phys, hetaDummy_bkg, hetaDummy_phys})
    {
        TCanvas *c = new TCanvas("c_" + TString(h->GetName()),
                                "c_" + TString(h->GetName()));
        h->Draw();
        c->SaveAs(Form("${B2HH_OUT}/Tagging/iftTemplates/plots/%s_%s_%g_%s_%s.root",
                    finalState.Data(), configuration.Data(),
                    bdtCut, year.Data(), magnet.Data()));
        c->SaveAs(Form("${B2HH_OUT}/Tagging/iftTemplates/plots/%s_%s_%g_%s_%s.pdf",
                    finalState.Data(), configuration.Data(),
                    bdtCut, year.Data(), magnet.Data()));
    }

  outFile->Close();

  return 0;

} 
