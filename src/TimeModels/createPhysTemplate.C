#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <RooFit.h>
#include <RooKeysPdfSpecial.h>
#include <RooHistPdf.h>
#include <RooDataHist.h>
#include <TH1D.h>
#include <RooRealVar.h>
#include <RooCategory.h>
#include <RooDataSet.h>
#include <RooArgSet.h>
#include <TChain.h>
#include <TFile.h>
#include <optionParser.h>
#include <TCanvas.h>
#include <RooPlot.h>
#include <RooWorkspace.h>
#include <TRandom3.h>
#include <TPad.h>
#include <TAxis.h>
#include <RooHist.h>

#include <algorithm>
#include <functional>
#include <array>

#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>

using namespace std;
using namespace RooFit;

Bool_t compareSecond(const pair<Int_t,Double_t>&a, const pair<Int_t,Double_t>&b) {

  return a.second < b.second;

}
Bool_t compareFirst(const pair<Int_t,Double_t>&a, const pair<Int_t,Double_t>&b) {

  return a.first < b.first;
  
}

Int_t main(Int_t argc, Char_t * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./test [options]\n");
    printf("Options:\n");
    printf("  -n <name>       : decay used for BDT train ([PIPI, KK], default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = 0.04)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2011,2012,Tot], default = 2016)\n");
    printf("  -f <finalState> : ID of final state ([PIPI,KPI,KK], default = PIPI)\n");
    return 0;
  }

  TString name          = getOption(argc,argv,"-n","PIPI");
  Double_t bdtCut       = atof(getOption(argc,argv,"-b","0.12"));
  TString magnet        = getOption(argc,argv,"-m","Tot");
  TString year          = getOption(argc,argv,"-y","2016");
  TString finalState    = getOption(argc,argv,"-f","PIPI");
  TString tagName       = (name == "PIPI" ? "SS" : "SSk");

  Int_t finalStateIdx = datasetFlags::yearFlags[year] +
                        datasetFlags::spectrumFlags[finalState];
  Double_t massCut = ((finalState == "KK") ? timeModels_cuts::massCutKK : timeModels_cuts::massCutPIPI);

  TRandom3 myRandom(192837464);

  const Double_t minWinTot = timeModels_cuts::minWinTot;
  const Double_t maxWinTot = timeModels_cuts::maxWinTot;
  const Double_t minTimeFit = timeModels_cuts::minTimeFit;
  const Double_t maxTimeFit = timeModels_cuts::maxTimeFit;

  Double_t Time = 0, Mass = 0, Weight3 = 0;
  Int_t QOS = 0, QSS = 0, FState = 0;
  RooRealVar * time = new RooRealVar("time","time",minTimeFit,maxTimeFit);
  RooRealVar * mass = new RooRealVar("mass","mass",minWinTot,maxWinTot);
  RooRealVar * weight3 = new RooRealVar("weight3","weight3",-1e6,1e6);
  RooCategory * qOS = new RooCategory("qOS","qOS");
  qOS->defineType("B",1); qOS->defineType("Bbar",-1); qOS->defineType("Untag",0);
  RooCategory * qSS = new RooCategory(Form("q%s",tagName.Data()),Form("q%s",tagName.Data()));
  qSS->defineType("B",1); qSS->defineType("Bbar",-1); qSS->defineType("Untag",0);
  RooCategory * fState = new RooCategory("fState","fState");
  fState->defineType(Form("%s_%s",finalState.Data(),year.Data()),finalStateIdx);

  RooArgSet * obs = new RooArgSet();
  obs->add(*mass); obs->add(*time);
  obs->add(*qOS);  obs->add(*qSS);
  obs->add(*weight3); 

  RooDataSet * dataPhysT; RooDataSet * dataPhysU;

  TChain * chainPhys = new TChain("chainPhys","chainPhys");
  chainPhys->Add(Form("${B2HH_OUT}/Reduce/b2hh_%s_%g_%s_%s.root/b2hh",name.Data(),bdtCut,year.Data(),magnet.Data()));
  chainPhys->SetBranchStatus("*",0);
  chainPhys->SetBranchStatus("mass",1);   chainPhys->SetBranchStatus("time",1); 
  chainPhys->SetBranchStatus("qOS",1);   chainPhys->SetBranchStatus(Form("q%s",tagName.Data()),1); 
  chainPhys->SetBranchStatus("fState",1);
  chainPhys->SetBranchAddress("mass",&Mass);
  chainPhys->SetBranchAddress("time",&Time);
  chainPhys->SetBranchAddress("qOS",&QOS);
  chainPhys->SetBranchAddress(Form("q%s",tagName.Data()),&QSS);
  chainPhys->SetBranchAddress("fState",&FState);
  TTree * physTreeT = (TTree *) chainPhys->CloneTree(0);
  physTreeT->Branch("weight3",&Weight3,"weight3/D");
  TTree * physTreeU = (TTree *) chainPhys->CloneTree(0);
  physTreeU->Branch("weight3",&Weight3,"weight3/D");
  for(Int_t iEntry = 0, nEntries = chainPhys->GetEntries(); iEntry < nEntries; ++iEntry) {
    chainPhys->GetEntry(iEntry);
    if(FState!=finalStateIdx) continue;
    if(Mass>massCut) continue;
    if(Mass<minWinTot) continue;
    if(Time<minTimeFit) continue;
    if(Time>maxTimeFit) continue;
    Weight3 = 1; 
    if     (QSS!=0) physTreeT->Fill();
    else if(QSS==0) physTreeU->Fill();
  }

  TChain * chainBkg = new TChain("chainBkg","chainBkg");
  chainBkg->Add(Form("${B2HH_OUT}/TimeModels/weightedFiles/bkg_%s_%s_%g_%s_%s.root/b2hh",finalState.Data(),name.Data(),bdtCut,year.Data(),magnet.Data()));
  chainBkg->SetBranchStatus("*",0);
  chainBkg->SetBranchStatus("mass",1);   chainBkg->SetBranchStatus("time",1); 
  chainBkg->SetBranchStatus("qOS",1);    chainBkg->SetBranchStatus(Form("q%s",tagName.Data()),1); 
  chainBkg->SetBranchStatus("fState",1); chainBkg->SetBranchStatus("weight3",1);
  chainBkg->SetBranchAddress("mass",&Mass);
  chainBkg->SetBranchAddress("time",&Time);
  chainBkg->SetBranchAddress("qOS",&QOS);
  chainBkg->SetBranchAddress(Form("q%s",tagName.Data()),&QSS);
  chainBkg->SetBranchAddress("fState",&FState);
  chainBkg->SetBranchAddress("weight3",&Weight3);
  for(Int_t iEntry = 0, nEntries = chainBkg->GetEntries(); iEntry < nEntries; ++iEntry) {
    chainBkg->GetEntry(iEntry);
    if     (QSS!=0) physTreeT->Fill();
    else if(QSS==0) physTreeU->Fill();
  }
  std::vector<std::pair<Int_t,Double_t>> vectEntriesT(0);
  std::vector<std::pair<Int_t,Double_t>> vectEntriesU(0);
  //for(Int_t iEntry = 0, nEntries = physTreeT->GetEntries(); iEntry < (nEntries > 50000 ? 50000 : nEntries); ++iEntry) 
  //  vectEntriesT.push_back(myRandom.Integer(nEntries));
  //for(Int_t iEntry = 0, nEntries = physTreeU->GetEntries(); iEntry < (nEntries > 50000 ? 50000 : nEntries); ++iEntry) 
  //  vectEntriesU.push_back(myRandom.Integer(nEntries));
  for(Int_t iEntry = 0, nEntries = physTreeT->GetEntries(); iEntry < nEntries; ++iEntry) 
    vectEntriesT.push_back(std::make_pair(iEntry,myRandom.Uniform(0,1)));
  for(Int_t iEntry = 0, nEntries = physTreeU->GetEntries(); iEntry < nEntries; ++iEntry) 
    vectEntriesU.push_back(std::make_pair(iEntry,myRandom.Uniform(0,1)));

  //std::sort(vectEntriesT.begin(),vectEntriesT.end(),compareSecond);
  //std::sort(vectEntriesU.begin(),vectEntriesU.end(),compareSecond);
  std::sort(vectEntriesT.begin(),vectEntriesT.end(),
            [](const pair<Int_t,Double_t>&a, const pair<Int_t,Double_t>&b)
            { return a.second < b.second; } );
  std::sort(vectEntriesU.begin(),vectEntriesU.end(),
            [](const pair<Int_t,Double_t>&a, const pair<Int_t,Double_t>&b)
            { return a.second < b.second; } );


  Int_t maxEntriesT = (Int_t) vectEntriesT.size();// > 50000 ? 50000 : (Int_t) vectEntriesT.size();
  Int_t maxEntriesU = (Int_t) vectEntriesU.size();// > 50000 ? 50000 : (Int_t) vectEntriesU.size();

  std::vector<std::pair<Int_t,Double_t>> entriesT(vectEntriesT.begin(),vectEntriesT.begin()+maxEntriesT);
  std::vector<std::pair<Int_t,Double_t>> entriesU(vectEntriesU.begin(),vectEntriesU.begin()+maxEntriesU);
  //std::sort(entriesT.begin(),entriesT.end(),compareFirst);
  //std::sort(entriesU.begin(),entriesU.end(),compareFirst);
  std::sort(entriesT.begin(), entriesT.end(),
            [](const pair<Int_t,Double_t>&a, const pair<Int_t,Double_t>&b) {
              return a.first < b.first; } 
           );
  std::sort(entriesT.begin(), entriesT.end(),
            [](const pair<Int_t,Double_t>&a, const pair<Int_t,Double_t>&b) {
              return a.first < b.first; } 
           );


  TH1D * histPhysT = new TH1D("histPhysT","histPhysT",140,minTimeFit,maxTimeFit);
  TH1D * histPhysU = new TH1D("histPhysU","histPhysU",140,minTimeFit,maxTimeFit);
  dataPhysT = new RooDataSet("dataPhysT", "dataPhysT", *obs, WeightVar("weight3"));
  for(auto tmp: entriesT) {
    physTreeT->GetEntry(tmp.first);
    time->setVal(Time); mass->setVal(Mass);
    qOS->setIndex(QOS); qSS->setIndex(QSS);
    weight3->setVal(Weight3);
    dataPhysT->add(*obs,Weight3);
    histPhysT->Fill(Time,Weight3);
  }
  dataPhysU = new RooDataSet("dataPhysU","dataPhysU",*obs,WeightVar("weight3"));
  for(auto tmp: entriesU) {
    physTreeU->GetEntry(tmp.first);
    time->setVal(Time); mass->setVal(Mass);
    qOS->setIndex(QOS); qSS->setIndex(QSS);
    weight3->setVal(Weight3);
    dataPhysU->add(*obs,Weight3);
    histPhysU->Fill(Time,Weight3);
  }

  printf("PhysT %d %g\n",dataPhysT->numEntries(),dataPhysT->sumEntries());
  printf("PhysU %d %g\n",dataPhysU->numEntries(),dataPhysU->sumEntries());

  finalState.ToLower();

  //RooDataHist * dataPhysHistT = new RooDataHist("dataPhysHistT","dataPhysHistT",RooArgSet(*time),histPhysT);
  //RooHistPdf * pdfPhysHistT = new RooHistPDf(Form("phys_%s_pdftimeHistT_%s",finalState.Data(),year.Data()),
  //                                           Form("phys_%s_pdftimeHistT_%s",finalState.Data(),year.Data()),
  //                                           RooArgSet(*time),dataPhysHistT,2);
  //RooHistPdf * pdfPhys1HistT = new RooHistPDf(*pdfPhysHistT,
  //                                            Form("phys_%s1_pdftimeHistT_%s",finalState.Data(),year.Data())
  //RooHistPdf * pdfPhys2HistT = new RooHistPDf(*pdfPhysHistT,
  //                                            Form("phys_%s2_pdftimeHistT_%s",finalState.Data(),year.Data())

  //RooDataHist * dataPhysHistU = new RooDataHist("dataPhysHistU","dataPhysHistU",RooArgSet(*time),histPhysU);
  //RooHistPdf * pdfPhysHistU = new RooHistPDf(Form("phys_%s_pdftimeHistU_%s",finalState.Data(),year.Data()),
  //                                           Form("phys_%s_pdftimeHistU_%s",finalState.Data(),year.Data()),
  //                                           RooArgSet(*time),dataPhysHistU,2);
  //RooHistPdf * pdfPhys1HistU = new RooHistPDf(*pdfPhysHistU,
  //                                            Form("phys_%s1_pdftimeHistU_%s",finalState.Data(),year.Data())
  //RooHistPdf * pdfPhys2HistU = new RooHistPDf(*pdfPhysHistU,
  //                                            Form("phys_%s2_pdftimeHistU_%s",finalState.Data(),year.Data())


  RooKeysPdfSpecial * pdfPhysT = new RooKeysPdfSpecial(Form("phys_%s_pdftimeT_%s",finalState.Data(),year.Data()),
                                                       Form("phys_%s_pdftimeT_%s",finalState.Data(),year.Data()),
                                                       *time,*dataPhysT,RooKeysPdfSpecial::NoMirror,1);

  RooKeysPdfSpecial * pdfPhys1T = new RooKeysPdfSpecial(*pdfPhysT,Form("phys_%s1_pdftimeT_%s",finalState.Data(),year.Data()));
  RooKeysPdfSpecial * pdfPhys2T = new RooKeysPdfSpecial(*pdfPhysT,Form("phys_%s2_pdftimeT_%s",finalState.Data(),year.Data()));

  RooKeysPdfSpecial * pdfPhysU; RooKeysPdfSpecial * pdfPhys1U; RooKeysPdfSpecial * pdfPhys2U;

  if(finalState=="kk" && name=="PIPI" ) {
    pdfPhysU = new RooKeysPdfSpecial(Form("phys_%s_pdftimeU_%s",finalState.Data(),year.Data()),
                                     Form("phys_%s_pdftimeU_%s",finalState.Data(),year.Data()),
                                     *time,*dataPhysT,RooKeysPdfSpecial::NoMirror,1);
    pdfPhys1U = new RooKeysPdfSpecial(*pdfPhysT,Form("phys_%s1_pdftimeU_%s",finalState.Data(),year.Data()));
    pdfPhys2U = new RooKeysPdfSpecial(*pdfPhysT,Form("phys_%s2_pdftimeU_%s",finalState.Data(),year.Data()));
  }
  else {
    pdfPhysU = new RooKeysPdfSpecial(Form("phys_%s_pdftimeU_%s",finalState.Data(),year.Data()),
                                     Form("phys_%s_pdftimeU_%s",finalState.Data(),year.Data()),
                                     *time,*dataPhysU,RooKeysPdfSpecial::NoMirror,1);
    pdfPhys1U = new RooKeysPdfSpecial(*pdfPhysU,Form("phys_%s1_pdftimeU_%s",finalState.Data(),year.Data()));
    pdfPhys2U = new RooKeysPdfSpecial(*pdfPhysU,Form("phys_%s2_pdftimeU_%s",finalState.Data(),year.Data()));
  }
  
  RooWorkspace * myWS = new RooWorkspace("templates","templates");
  myWS->import(*dataPhysT); myWS->import(*dataPhysU);
  myWS->import(*pdfPhysT);  myWS->import(*pdfPhysU);
  myWS->import(*pdfPhys1T);  myWS->import(*pdfPhys1U);
  myWS->import(*pdfPhys2T);  myWS->import(*pdfPhys2U);

  // tmp: used for 2017 KK_0.04 kk Tagged, because of uknown error 
  // myWS->import(*dataPhysU);
  // myWS->import(*pdfPhysU);
  // myWS->import(*pdfPhys1U);
  // myWS->import(*pdfPhys2U);
  // pdfPhysU->SetName(TString(pdfPhysU->GetName()).ReplaceAll("pdftimeU", "pdftimeT"));
  // pdfPhys1U->SetName(TString(pdfPhys1U->GetName()).ReplaceAll("pdftimeU", "pdftimeT"));
  // pdfPhys2U->SetName(TString(pdfPhys2U->GetName()).ReplaceAll("pdftimeU", "pdftimeT"));
  // myWS->import(*dataPhysT);
  // myWS->import(*pdfPhysU);
  // myWS->import(*pdfPhys1U);
  // myWS->import(*pdfPhys2U);
  //myWS->import(*pdfPhysHistT);  myWS->import(*pdfPhysHistU);
  //myWS->import(*pdfPhys1HistT);  myWS->import(*pdfPhys1HistU);
  //myWS->import(*pdfPhys2HistT);  myWS->import(*pdfPhys2HistU);

  RooPlot * plotT = time->frame(minTimeFit,maxTimeFit,180);
  dataPhysT->plotOn(plotT);
  printf("FANCULO\n");
  pdfPhysT->Print("v");
  pdfPhysT->plotOn(plotT);
  printf("FANCULO\n");
  TCanvas * cT = new TCanvas("cT","cT",700,725);
  cT->cd();
  TPad * upperPadT = new TPad("upperPadT","upperPadT",0,0.2,1,1);
  upperPadT->SetLeftMargin(0.15);
  upperPadT->SetBottomMargin(0.15);
  TPad * lowerPadT = new TPad("lowerPadT","lowerPadT",0,0,1,0.2);
  lowerPadT->SetLeftMargin(0.15);
  lowerPadT->Draw();
  upperPadT->Draw();
  upperPadT->cd() ;
  plotT->Draw();
  RooHist * hpullT = plotT->pullHist();
  hpullT->SetFillColor(kBlue);
  RooPlot * pullsT = time->frame(minTimeFit,maxTimeFit,180);
  pullsT->SetTitle("");
  pullsT->addPlotable(hpullT,"BX");
  pullsT->GetYaxis()->SetRangeUser(-5,5);
  lowerPadT->cd();
  pullsT->Draw();
  cT->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/templatePhys_%s_%s_%g_%s_%s_T.eps",
		  finalState.Data(),name.Data(),
		  bdtCut,year.Data(),magnet.Data()));
  cT->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/templatePhys_%s_%s_%g_%s_%s_T.pdf",
		  finalState.Data(),name.Data(),
		  bdtCut,year.Data(),magnet.Data()));

  RooPlot * plotU = time->frame(minTimeFit,maxTimeFit,280);
  dataPhysU->plotOn(plotU);
  printf("STOCAZZO\n");
  pdfPhysU->plotOn(plotU);
  printf("STOCAZZO\n");
  TCanvas * cU = new TCanvas("cU","cU",700,725);
  cU->cd();
  TPad * upperPadU = new TPad("upperPadU","upperPadU",0,0.2,1,1);
  upperPadU->SetLeftMargin(0.15);
  upperPadU->SetBottomMargin(0.15);
  TPad * lowerPadU = new TPad("lowerPadU","lowerPadU",0,0,1,0.2);
  lowerPadU->SetLeftMargin(0.15);
  lowerPadU->Draw();
  upperPadU->Draw();
  upperPadU->cd() ;
  plotU->Draw();
  RooHist * hpullU = plotU->pullHist();
  hpullU->SetFillColor(kBlue);
  RooPlot * pullsU = time->frame(minTimeFit,maxTimeFit,280);
  pullsU->SetTitle("");
  pullsU->addPlotable(hpullU,"BX");
  pullsU->GetYaxis()->SetRangeUser(-5,5);
  lowerPadU->cd();
  pullsU->Draw();
  cU->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/templatePhys_%s_%s_%g_%s_%s_U.eps",
		  finalState.Data(),name.Data(),
		  bdtCut,year.Data(),magnet.Data()));
  cU->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/templatePhys_%s_%s_%g_%s_%s_U.pdf",
		  finalState.Data(),name.Data(),
		  bdtCut,year.Data(),magnet.Data()));
  
  TFile * outFile = TFile::Open(Form("${B2HH_OUT}/TimeModels/templateFiles/templatesPhys_%s_%s_%g_%s_%s.root",
                                     finalState.Data(),name.Data(),
                                     bdtCut,year.Data(),magnet.Data()),"RECREATE");
  outFile->WriteTObject(myWS,"","Overwrite");
  outFile->WriteTObject(cT,"","Overwrite");
  outFile->WriteTObject(cU,"","Overwrite");
  outFile->Close();

  return 0;

}
