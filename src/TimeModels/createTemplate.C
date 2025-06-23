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
#include <RooWorkspace.h>
#include <optionParser.h>
#include <TCanvas.h>
#include <RooPlot.h>
#include <RooWorkspace.h>
#include <TPad.h>
#include <RooHist.h>
#include <TAxis.h>
#include <makePull.h>
#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>

using namespace std;
using namespace RooFit;

Int_t main(Int_t argc, Char_t * argv[]) {
  cout << "------------------------------------------------------------------------------------------" << endl;
  cout << "Create Template Main" << endl;
  cout << "------------------------------------------------------------------------------------------" << endl;
  cerr << "------------------------------------------------------------------------------------------" << endl;
  cerr << "Create Template Main" << endl;
  cerr << "------------------------------------------------------------------------------------------" << endl;
  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./test [options]\n");
    printf("Options:\n");
    printf("  -n <name>       : decay used for BDT train ([PIPI, KK], default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = 0.12)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2015,2016,2017,2018,201516,20151618,Tot], default = 201516)\n");
    printf("  -f <finalState> : ID of final state ([PIPI,KPI,KK], default = PIPI)\n");
    printf("  -M <massWindow> : Mass window ([Low,High,None], default = None)\n");
    return 0;
  }

  TString name          = getOption(argc,argv,"-n","");
  Double_t bdtCut       = atof(getOption(argc,argv,"-b",""));
  TString magnet        = getOption(argc,argv,"-m","");
  TString year          = getOption(argc,argv,"-y","");
  TString finalState    = getOption(argc,argv,"-f","");
  TString massWinName   = getOption(argc,argv,"-M","");
  TString tagName       = (name == "PIPI" ? "SS" : "SSk");

  const Double_t minWinTot = timeModels_cuts::minWinTot;
  const Double_t maxWinTot = timeModels_cuts::maxWinTot;
  const Double_t minWinFit = timeModels_cuts::minWinFit;
  const Double_t maxWinFit = timeModels_cuts::maxWinFit;
  const Double_t minTimeFit = timeModels_cuts::minTimeFit;
  const Double_t maxTimeFit = timeModels_cuts::maxTimeFit;

  RooRealVar * time = new RooRealVar("time","time",minTimeFit,maxTimeFit);
  RooRealVar * mass = new RooRealVar("mass","mass",min(minWinFit,minWinTot),max(maxWinFit,maxWinTot));
  //RooRealVar * weight = new RooRealVar("weight","weight",-1e6,1e6);
  RooRealVar * weight = new RooRealVar(Form("weight%s",massWinName.Data()),
                                       Form("weight%s",massWinName.Data()),-1e6,1e6);
  RooCategory * qOS = new RooCategory("qOS","qOS");
  qOS->defineType("B",1); qOS->defineType("Bbar",-1); qOS->defineType("Untag",0);
  RooCategory * qSS = new RooCategory(Form("q%s",tagName.Data()),Form("q%s",tagName.Data()));
  qSS->defineType("B",1); qSS->defineType("Bbar",-1); qSS->defineType("Untag",0);

  Int_t FState = datasetFlags::yearFlags[year] +
                 datasetFlags::spectrumFlags[finalState];
  
  RooCategory * fState = new RooCategory("fState","fState");
  fState->defineType(Form("%s_%s",finalState.Data(),year.Data()),FState);

  RooArgSet * obs = new RooArgSet();
  obs->add(*mass); obs->add(*time);
  obs->add(*qOS);  obs->add(*qSS);
  obs->add(*weight); 
  
  RooArgSet * obs2 = new RooArgSet();
  obs2->add(*mass); obs2->add(*time);
  obs2->add(*qOS);  obs2->add(*qSS);
  obs2->add(*fState);
  
  printf("STOCAZZO\n");

  Double_t Time = 0, Mass = 0, Weight = 0;
  Int_t QOS = 0, QSS = 0;
  TChain * chain = new TChain("b2hh","b2hh");
  chain->Add(Form("${B2HH_OUT}/TimeModels/weightedFiles/bkg_%s_%s_%g_%s_%s.root/b2hh",finalState.Data(),name.Data(),bdtCut,year.Data(),magnet.Data()));
  chain->SetBranchAddress("time",&Time);
  chain->SetBranchAddress("mass",&Mass);
  chain->SetBranchAddress(Form("weight%s",massWinName.Data()),&Weight);
  chain->SetBranchAddress("qOS",&QOS);
  chain->SetBranchAddress(Form("q%s",tagName.Data()),&QSS);

  TChain * chain2 = new TChain("b2hh2","b2hh2");
  chain2->Add(Form("${B2HH_OUT}/Reduce/b2hh_%s_%g_%s_%s.root/b2hh",name.Data(),bdtCut,year.Data(),magnet.Data()));

  RooDataSet * data11; RooDataSet * data10;
  RooDataSet * data01; RooDataSet * data00;

  TH1D * hist11 = new TH1D("hist11","hits11",140,minTimeFit,maxTimeFit);
  TH1D * hist10 = new TH1D("hist10","hits10",140,minTimeFit,maxTimeFit);
  TH1D * hist01 = new TH1D("hist01","hits01",140,minTimeFit,maxTimeFit);
  TH1D * hist00 = new TH1D("hist00","hits00",140,minTimeFit,maxTimeFit);
  //RooDataHist * dataH11; RooDataHist * dataH10;
  //RooDataHist * dataH01; RooDataHist * dataH00;

  RooDataSet * dataU11; RooDataSet * dataU10;
  RooDataSet * dataU01; RooDataSet * dataU00;

  RooKeysPdfSpecial * pdf11; RooKeysPdfSpecial * pdf10;
  RooKeysPdfSpecial * pdf01; RooKeysPdfSpecial * pdf00;

  //RooHistPdf * pdfHist11; RooHistPdf * pdfHist10;
  //RooHistPdf * pdfHist01; RooHistPdf * pdfHist00;

  for(Int_t iEntry = 0, nEntries = chain->GetEntries(); iEntry < nEntries; ++iEntry) {
    chain->GetEntry(iEntry);
    if     (QOS!=0&&QSS!=0) hist11->Fill(Time,Weight);
    else if(QOS!=0&&QSS==0) hist10->Fill(Time,Weight);
    else if(QOS==0&&QSS!=0) hist01->Fill(Time,Weight);
    else if(QOS==0&&QSS==0) hist00->Fill(Time,Weight);
  }
  setToZero(hist11); setToZero(hist10); setToZero(hist01); setToZero(hist00);
  hist11->Scale(1./hist11->Integral("width"));
  hist10->Scale(1./hist10->Integral("width"));
  hist01->Scale(1./hist01->Integral("width"));
  hist00->Scale(1./hist00->Integral("width"));

  //dataH11 = new RooDataHist("dataH11","dataH11",RooArgSet(*time),hist11);
  //dataH10 = new RooDataHist("dataH10","dataH10",RooArgSet(*time),hist10);
  //dataH01 = new RooDataHist("dataH01","dataH01",RooArgSet(*time),hist01);
  //dataH00 = new RooDataHist("dataH00","dataH00",RooArgSet(*time),hist00);

  //pdfHist11 = new RooHistPdf(Form("bkg_%s_pdfHisttime11_%s",finalState.Data(),year.Data()),
  //                           Form("bkg_%s_pdfHisttime11_%s",finalState.Data(),year.Data()),
  //                           RooArgSet(*time),*dataH11,2);
  //pdfHist10 = new RooHistPdf(Form("bkg_%s_pdfHisttime10_%s",finalState.Data(),year.Data()),
  //                           Form("bkg_%s_pdfHisttime10_%s",finalState.Data(),year.Data()),
  //                           RooArgSet(*time),*dataH10,2);
  //pdfHist01 = new RooHistPdf(Form("bkg_%s_pdfHisttime01_%s",finalState.Data(),year.Data()),
  //                           Form("bkg_%s_pdfHisttime01_%s",finalState.Data(),year.Data()),
  //                           RooArgSet(*time),*dataH01,2);
  //pdfHist00 = new RooHistPdf(Form("bkg_%s_pdfHisttime00_%s",finalState.Data(),year.Data()),
  //                           Form("bkg_%s_pdfHisttime00_%s",finalState.Data(),year.Data()),
  //                           RooArgSet(*time),*dataH00,2);


  data11 = new RooDataSet("data11","data11",*obs,Import(*chain),
                                                 Cut(Form("qOS!=0&&q%s!=0",tagName.Data())),
                                                 WeightVar(Form("weight%s",massWinName.Data())));
  data10 = new RooDataSet("data10","data10",*obs,Import(*chain),
                                                 Cut(Form("qOS!=0&&q%s==0",tagName.Data())),
                                                 WeightVar(Form("weight%s",massWinName.Data())));
  data01 = new RooDataSet("data01","data01",*obs,Import(*chain),
                                                 Cut(Form("qOS==0&&q%s!=0",tagName.Data())),
                                                 WeightVar(Form("weight%s",massWinName.Data())));
  data00 = new RooDataSet("data00","data00",*obs,Import(*chain),
                                                 Cut(Form("qOS==0&&q%s==0",tagName.Data())),
                                                 WeightVar(Form("weight%s",massWinName.Data())));
  
  dataU11 = new RooDataSet("dataU11","dataU11",*obs2,Import(*chain2),
                                                     Cut(Form("qOS!=0&&q%s!=0&&mass>%g&&mass<%g",
                                                              tagName.Data(),minWinTot,maxWinTot)));
  dataU10 = new RooDataSet("dataU10","dataU10",*obs2,Import(*chain2),
                                                     Cut(Form("qOS!=0&&q%s==0&&mass>%g&&mass<%g",
                                                              tagName.Data(),minWinTot,maxWinTot)));
  dataU01 = new RooDataSet("dataU01","dataU01",*obs2,Import(*chain2),
                                                     Cut(Form("qOS==0&&q%s!=0&&mass>%g&&mass<%g",
                                                              tagName.Data(),minWinTot,maxWinTot)));
  dataU00 = new RooDataSet("dataU00","dataU00",*obs2,Import(*chain2),
                                                     Cut(Form("qOS==0&&q%s==0&&mass>%g&&mass<%g",
                                                              tagName.Data(),minWinTot,maxWinTot)));
  
  finalState.ToLower();
  pdf11 = new RooKeysPdfSpecial(Form("bkg_%s_pdftime11_%s",finalState.Data(),year.Data()),
                                Form("bkg_%s_pdftime11_%s",finalState.Data(),year.Data()),
                                *time,*data11,RooKeysPdfSpecial::NoMirror,1);
  pdf10 = new RooKeysPdfSpecial(Form("bkg_%s_pdftime10_%s",finalState.Data(),year.Data()),
                                Form("bkg_%s_pdftime10_%s",finalState.Data(),year.Data()),
                                *time,*data10,RooKeysPdfSpecial::NoMirror,1);
  pdf01 = new RooKeysPdfSpecial(Form("bkg_%s_pdftime01_%s",finalState.Data(),year.Data()),
                                Form("bkg_%s_pdftime01_%s",finalState.Data(),year.Data()),
                                *time,*data01,RooKeysPdfSpecial::NoMirror,1);
  pdf00 = new RooKeysPdfSpecial(Form("bkg_%s_pdftime00_%s",finalState.Data(),year.Data()),
                                Form("bkg_%s_pdftime00_%s",finalState.Data(),year.Data()),
                                *time,*data00,RooKeysPdfSpecial::NoMirror,1);

  RooWorkspace * myWS = new RooWorkspace("templates","templates");
  myWS->import(*data11);     myWS->import(*pdf11);
  myWS->import(*data10);     myWS->import(*pdf10);
  myWS->import(*data01);     myWS->import(*pdf01);
  myWS->import(*data00);     myWS->import(*pdf00);
  //myWS->import(*dataH11);    myWS->import(*pdfHist11);
  //myWS->import(*dataH10);    myWS->import(*pdfHist10);
  //myWS->import(*dataH01);    myWS->import(*pdfHist01);
  //myWS->import(*dataH00);    myWS->import(*pdfHist00);

  RooPlot * plot11 = time->frame(minTimeFit,maxTimeFit,280);
  data11->plotOn(plot11);
  pdf11->plotOn(plot11);
  TCanvas * c11 = new TCanvas("c11","c11",700,725);
  c11->cd();
  TPad * upperPad11 = new TPad("upperPad11","upperPad11",0,0.2,1,1);
  upperPad11->SetLeftMargin(0.15);
  upperPad11->SetBottomMargin(0.15);
  TPad * lowerPad11 = new TPad("lowerPad11","lowerPad11",0,0,1,0.2);
  lowerPad11->SetLeftMargin(0.15);
  lowerPad11->Draw();
  upperPad11->Draw();
  upperPad11->cd() ;
  plot11->Draw();
  RooHist * hpull11 = plot11->pullHist();
  hpull11->SetFillColor(kBlue);
  RooPlot * pulls11 = time->frame(minTimeFit,maxTimeFit,280);
  pulls11->SetTitle("");
  pulls11->addPlotable(hpull11,"BX");
  pulls11->GetYaxis()->SetRangeUser(-5,5);
  lowerPad11->cd();
  pulls11->Draw();
  c11->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/others/template_%s_%g_%s_%s_%s_%s_11.eps", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));
  c11->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/pdf/template_%s_%g_%s_%s_%s_%s_11.pdf", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));

  RooPlot * plot10 = time->frame(minTimeFit,maxTimeFit,280);
  data10->plotOn(plot10);
  pdf10->plotOn(plot10);
  TCanvas * c10 = new TCanvas("c10","c10",700,725);
  c10->cd();
  TPad * upperPad10 = new TPad("upperPad10","upperPad10",0,0.2,1,1);
  upperPad10->SetLeftMargin(0.15);
  upperPad10->SetBottomMargin(0.15);
  TPad * lowerPad10 = new TPad("lowerPad10","lowerPad10",0,0,1,0.2);
  lowerPad10->SetLeftMargin(0.15);
  lowerPad10->Draw();
  upperPad10->Draw();
  upperPad10->cd() ;
  plot10->Draw();
  RooHist * hpull10 = plot10->pullHist();
  hpull10->SetFillColor(kBlue);
  RooPlot * pulls10 = time->frame(minTimeFit,maxTimeFit,280);
  pulls10->SetTitle("");
  pulls10->addPlotable(hpull10,"BX");
  pulls10->GetYaxis()->SetRangeUser(-5,5);
  lowerPad10->cd();
  pulls10->Draw();
  c10->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/others/template_%s_%g_%s_%s_%s_%s_10.eps", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));
  c10->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/pdf/template_%s_%g_%s_%s_%s_%s_10.pdf", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));

  RooPlot * plot01 = time->frame(minTimeFit,maxTimeFit,280);
  data01->plotOn(plot01);
  pdf01->plotOn(plot01);
  TCanvas * c01 = new TCanvas("c01","c01",700,725);
  c01->cd();
  TPad * upperPad01 = new TPad("upperPad01","upperPad01",0,0.2,1,1);
  upperPad01->SetLeftMargin(0.15);
  upperPad01->SetBottomMargin(0.15);
  TPad * lowerPad01 = new TPad("lowerPad01","lowerPad01",0,0,1,0.2);
  lowerPad01->SetLeftMargin(0.15);
  lowerPad01->Draw();
  upperPad01->Draw();
  upperPad01->cd() ;
  plot01->Draw();
  RooHist * hpull01 = plot01->pullHist();
  hpull01->SetFillColor(kBlue);
  RooPlot * pulls01 = time->frame(minTimeFit,maxTimeFit,280);
  pulls01->SetTitle("");
  pulls01->addPlotable(hpull01,"BX");
  pulls01->GetYaxis()->SetRangeUser(-5,5);
  lowerPad01->cd();
  pulls01->Draw();
  c01->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/others/template_%s_%g_%s_%s_%s_%s_01.eps", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));
  c01->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/pdf/template_%s_%g_%s_%s_%s_%s_01.pdf", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));

  RooPlot * plot00 = time->frame(minTimeFit,maxTimeFit,280);
  data00->plotOn(plot00);
  pdf00->plotOn(plot00);
  TCanvas * c00 = new TCanvas("c00","c00",700,725);
  c00->cd();
  TPad * upperPad00 = new TPad("upperPad00","upperPad00",0,0.2,1,1);
  upperPad00->SetLeftMargin(0.15);
  upperPad00->SetBottomMargin(0.15);
  TPad * lowerPad00 = new TPad("lowerPad00","lowerPad00",0,0,1,0.2);
  lowerPad00->SetLeftMargin(0.15);
  lowerPad00->Draw();
  upperPad00->Draw();
  upperPad00->cd() ;
  plot00->Draw();
  RooHist * hpull00 = plot00->pullHist();
  hpull00->SetFillColor(kBlue);
  RooPlot * pulls00 = time->frame(minTimeFit,maxTimeFit,280);
  pulls00->SetTitle("");
  pulls00->addPlotable(hpull00,"BX");
  pulls00->GetYaxis()->SetRangeUser(-5,5);
  lowerPad00->cd();
  pulls00->Draw();

  c00->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/others/template_%s_%g_%s_%s_%s_%s_00.eps", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));
  c00->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/pdf/template_%s_%g_%s_%s_%s_%s_00.pdf", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));

  TFile * outFile = TFile::Open(Form("${B2HH_OUT}/TimeModels/templateFiles/templates%s_%s_%s_%g_%s_%s.root",
                                     massWinName.Data(),finalState.Data(),name.Data(),
                                     bdtCut,year.Data(),magnet.Data()),"RECREATE");
  outFile->WriteTObject(myWS,"","Overwrite");
  outFile->WriteTObject(c11,"","Overwrite");
  outFile->WriteTObject(c10,"","Overwrite");
  outFile->WriteTObject(c01,"","Overwrite");
  outFile->WriteTObject(c00,"","Overwrite");
  outFile->Close();

  cout << "createTemplate done" << endl;

  return 0;

}
