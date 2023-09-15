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

using namespace std;

Int_t main(Int_t argc, Char_t * argv[]) {

	TString name              = getOption(argc,argv,"-n","PIPI");
	TString decay             = getOption(argc,argv,"-d","bdpipi");
	TString decay2            = getOption(argc,argv,"-d2","");
	TString finalState        = getOption(argc,argv,"-f","pipi");
	TString finalState2       = getOption(argc,argv,"-f2","");
	TString bmeson            = getOption(argc,argv,"-B","bd");
	Double_t bdtCut           = atof(getOption(argc,argv,"-b","-1"));
	TString magnet            = getOption(argc,argv,"-m","Tot");
	TString year              = getOption(argc,argv,"-y","Tot");

  const Bool_t flagBmeson = (bmeson=="bd");
  Double_t bP = 0;
  Double_t weight_data = 0, bPT_data = 0, bETA_data = 0;
  TChain * chainData = new TChain("data","data");
  chainData->Add(Form("${B2HH_OUT}/sPlot/tuple_reduced/b2hh_%s_%g_%s_%s_PIPI.root/b2hhW",name.Data(),bdtCut,year.Data(),magnet.Data()));
  // chainData->Add(Form("${B2HH_OUT}/Reduce/b2hh_%s_%g_%s_%s_moreVaraibles.root/b2hh",name.Data(),bdtCut,year.Data(),magnet.Data()));
  chainData->SetBranchStatus("*", 0);
  chainData->SetBranchStatus("bPT", 1);
  chainData->SetBranchStatus("bETA", 1);
  chainData->SetBranchStatus("weight", 1);
  chainData->SetBranchAddress("bPT",&bPT_data);
  chainData->SetBranchAddress("bETA",&bETA_data);
  chainData->SetBranchAddress("weight",&weight_data);

  TChain * chainMC = new TChain("mc","mc");
  chainMC->Add(Form("${B2HH_OUT}/AccSignal/selectedMC/%s_%s_%s_%g_%s_%s.root/b2hh",decay.Data(),finalState.Data(),name.Data(),bdtCut,year.Data(),magnet.Data()));
  if(decay2!="")
    chainMC->Add(Form("${B2HH_OUT}/AccSignal/selectedMC/%s_%s_%s_%g_%s_%s.root/b2hh", decay2.Data(), finalState2.Data(), name.Data(), bdtCut, year.Data(), magnet.Data()));

  Double_t weight_mc = 0, bPT_mc = 0, bETA_mc = 0;
  chainMC->SetBranchStatus("*", 0);
  chainMC->SetBranchStatus("bPT", 1);
  chainMC->SetBranchStatus("bETA", 1);
  chainMC->SetBranchStatus("weight", 1);
  chainMC->SetBranchAddress("bPT", &bPT_mc);
  chainMC->SetBranchAddress("bETA",&bETA_mc);
  chainMC->SetBranchAddress("weight",&weight_mc);
  
  TH1D * hEtaData = new TH1D("hEtaData","hEtaData",50, 0,10);  hEtaData->Sumw2();
  TH1D * hPData  = new TH1D("hPData", "hPData", 100,0,1000); hPData->Sumw2();
  TH2D * hPEtaData = new TH2D("hPEtaData","hPEtaData",100,0,1000,50,0,10); hPEtaData->Sumw2();

  TH1D * hEtaMC = new TH1D(Form("hEtaMC_%s",decay.Data()),Form("hEtaMC_%s",decay.Data()),50, 0,10);  hEtaMC->Sumw2();
  TH1D * hPMC  = new TH1D(Form("hPMC_%s",decay.Data()),Form("hPMC_%s",decay.Data()), 100,0,1000); hPMC->Sumw2();
  TH2D * hPEtaMC = new TH2D(Form("hPEtaMC_%s",decay.Data()),Form("hPEtaMC_%s",decay.Data()),100,0,1000,50,0,10); hPEtaMC->Sumw2();

  TH1D * hEtaCheck = new TH1D(Form("hEtaCheck_%s",decay.Data()),Form("hEtaCheck_%s",decay.Data()),50, 0,10);  hEtaCheck->Sumw2();
  TH1D * hPCheck  = new TH1D(Form("hPCheck_%s",decay.Data()),Form("hPCheck_%s",decay.Data()), 100,0,1000); hPCheck->Sumw2();
  TH2D * hPEtaCheck = new TH2D(Form("hPEtaCheck_%s",decay.Data()),Form("hPEtaMC_%s",decay.Data()),100,0,1000,50,0,10); hPEtaCheck->Sumw2();

  printf("Loop on Data\n");
  for(Int_t iEntry = 0, nEntries = chainData->GetEntries(); iEntry < nEntries; ++iEntry) {
    chainData->GetEntry(iEntry);
    bP = bPT_data*cosh(bETA_data);
    hEtaData->Fill(bETA_data,weight_data);
    hPData->Fill(bP,weight_data);
    hPEtaData->Fill(bP,bETA_data,weight_data);
  }
  hEtaData->Scale(1./hEtaData->Integral("width"));
  hPData->Scale(1./hPData->Integral("width"));
  hPEtaData->Scale(1./hPEtaData->Integral("width"));
  printf("Loop on MC\n");
  for(Int_t iEntry = 0, nEntries = chainMC->GetEntries(); iEntry < nEntries; ++iEntry) {
    chainMC->GetEntry(iEntry);
    bP = bPT_mc*cosh(bETA_mc);
    hEtaMC->Fill(bETA_mc);
    hPMC->Fill(bP);
    hPEtaMC->Fill(bP, bETA_mc);
  }
  hEtaMC->Scale(1./hEtaMC->Integral("width"));
  hPMC->Scale(1./hPMC->Integral("width"));
  hPEtaMC->Scale(1./hPEtaMC->Integral("width"));
  TH1D * hEtaRatio = (TH1D *) hEtaData->Clone(Form("hEtaRatio_%s",decay.Data()));
  hEtaRatio->Divide(hEtaMC);
  TH1D * hPRatio = (TH1D *) hPData->Clone(Form("hPRatio_%s",decay.Data()));
  hPRatio->Divide(hPMC);
  TH2D * hPEtaRatio = (TH2D *) hPEtaData->Clone(Form("hPEtaRatio_%s",decay.Data()));
  hPEtaRatio->Divide(hPEtaMC);

  
  TFile * outFile = TFile::Open(Form("${B2HH_OUT}/AccSignal/kineWeight/%s_%s_%s_%g_%s_%s_Kine.root",decay.Data(),finalState.Data(),name.Data(),bdtCut,year.Data(),magnet.Data()),"RECREATE");
  chainMC->SetBranchStatus("*", 1);
  chainMC->SetBranchAddress("bPT", &bPT_mc);
  chainMC->SetBranchAddress("bETA", &bETA_mc);
  chainMC->SetBranchAddress("weight", &weight_mc);

  Double_t weight2 = 0;
  // TBranch *b_weight2 = chainMC->Branch("weight2", &weight2, "weight2/D");
  // for(Int_t iEntry = 0, nEntries = chainMC->GetEntries(); iEntry < nEntries; ++iEntry) {

  //   chainMC->GetEntry(iEntry);
  //   bP = bPT_mc*cosh(bETA_mc);
  //   weight2 = hPEtaRatio->Interpolate(bP,bETA_mc);
  //   // weight *= weight2;//hPEtaRatio->Interpolate(bP,bETA);
  //   hEtaCheck->Fill(bETA_mc,weight2*weight_mc);
  //   hPCheck->Fill(bP, weight2 * weight_mc);
  //   hPEtaCheck->Fill(bP, bETA_mc, weight2 * weight_mc);

  //   b_weight2->Fill();
  // }
  // outFile->WriteTObject(chainMC, "", "Overwrite");
  // outFile->Close();
  printf("Apply weights\n");
  Int_t pp = 2, ffState=0;
  if       (year == "201516") ffState = 202;
  else if  (year == "2017s29r2p2") ffState = 22;
  else if  (year == "2018") ffState = 32;
  TTree * outChain = (TTree *) chainMC->CloneTree(0);
  outChain->Branch("weight2",&weight2,"weight2/D");
  outChain->Branch("p", &pp, "p/I");
  outChain->Branch("fState", &ffState, "fState/I");

  for (Int_t iEntry = 0, nEntries = chainMC->GetEntries(); iEntry < nEntries; ++iEntry)
  {
    chainMC->GetEntry(iEntry);
    bP = bPT_mc * cosh(bETA_mc);
    weight2 = hPEtaRatio->Interpolate(bP, bETA_mc);
    // printf("%g %g %g %g \n", bPT_mc, bETA_mc, weight_mc, weight2);
    hEtaCheck->Fill(bETA_mc, weight2);
    hPCheck->Fill(bP, weight2);
    hPEtaCheck->Fill(bP, bETA_mc, weight2);

    //   chainMC->GetEntry(iEntry);
    //   bP = bPT*cosh(bETA);
    //   weight2 = hPEtaRatio->Interpolate(bP,bETA);
      weight_mc *= weight2;//hPEtaRatio->Interpolate(bP,bETA);
    //   hEtaCheck->Fill(bETA,weight2);
    //   hPCheck->Fill(bP,weight2);
    //   hPEtaCheck->Fill(bP,bETA,weight2);

      outChain->Fill();
  }
    outFile->WriteTObject(outChain, "", "Overwrite");
    outFile->Close();

    hEtaCheck->Scale(1. / hEtaCheck->Integral("width"));
    hPCheck->Scale(1. / hPCheck->Integral("width"));
    hPEtaCheck->Scale(1. / hPEtaCheck->Integral("width"));

    printf("STOCAZZ4\n");
    TCanvas *cEta = new TCanvas("cEta", "cEta");
    cEta->cd();
    hEtaMC->Draw("hist");
    hEtaData->Draw("pe1same");
    hEtaCheck->SetLineColor(kGreen + 2);
    hEtaCheck->Draw("hist same");
    cEta->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/kineWeight_%s_%s_%s_%g_%s_%s_cEta.root", decay.Data(), finalState.Data(), name.Data(), bdtCut, year.Data(), magnet.Data()));
    cEta->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/kineWeight_%s_%s_%s_%g_%s_%s_cEta.pdf", decay.Data(), finalState.Data(), name.Data(), bdtCut, year.Data(), magnet.Data()));

    TCanvas *cP = new TCanvas("cP", "cP");
    cP->cd();
    hPMC->Draw("hist");
    hPData->Draw("pe1same");
    hPCheck->SetLineColor(kGreen + 2);
    hPCheck->Draw("hist same");
    cP->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/kineWeight_%s_%s_%s_%g_%s_%s_cP.root", decay.Data(), finalState.Data(), name.Data(), bdtCut, year.Data(), magnet.Data()));
    cP->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/kineWeight_%s_%s_%s_%g_%s_%s_cP.pdf", decay.Data(), finalState.Data(), name.Data(), bdtCut, year.Data(), magnet.Data()));

    outFile = new TFile(Form("${B2HH_OUT}/AccSignal/kineWeight/kineRatio_%s_%s_%s_%g_%s_%s.root", decay.Data(), finalState.Data(), name.Data(), bdtCut, year.Data(), magnet.Data()), "RECREATE");
    outFile->WriteTObject(hEtaData, "", "Overwrite");
    outFile->WriteTObject(hPData, "", "Overwrite");
    outFile->WriteTObject(hPEtaData, "", "Overwrite");
    outFile->WriteTObject(hEtaMC, "", "Overwrite");
    outFile->WriteTObject(hPMC, "", "Overwrite");
    outFile->WriteTObject(hPEtaMC, "", "Overwrite");

    outFile->WriteTObject(hEtaRatio, "", "Overwrite");
    outFile->WriteTObject(hPRatio, "", "Overwrite");
    outFile->WriteTObject(hPEtaRatio, "", "Overwrite");

    outFile->WriteTObject(hEtaCheck, "", "Overwrite");
    outFile->WriteTObject(hPCheck, "", "Overwrite");
    outFile->WriteTObject(hPEtaCheck, "", "Overwrite");
    outFile->Close();

    return 0;


}
