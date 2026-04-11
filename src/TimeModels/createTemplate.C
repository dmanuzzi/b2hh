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

  RooDataSet * dataU;
  RooDataSet * data1OS; RooDataSet * data0OS;
  RooDataSet * data11; RooDataSet * data10;
  RooDataSet * data01; RooDataSet * data00;

  RooKeysPdfSpecial * pdfU;
  RooKeysPdfSpecial * pdf1OS; RooKeysPdfSpecial * pdf0OS;
  RooKeysPdfSpecial * pdf11; RooKeysPdfSpecial * pdf10;
  RooKeysPdfSpecial * pdf01; RooKeysPdfSpecial * pdf00;



  dataU = new RooDataSet("dataU","dataU",*obs,Import(*chain),
                                                 WeightVar(Form("weight%s",massWinName.Data())));
  data1OS = new RooDataSet("data1OS","data1OS",*obs,Import(*chain),
                                                 Cut("qOS!=0"),
                                                 WeightVar(Form("weight%s",massWinName.Data())));
  data0OS = new RooDataSet("data0OS","data0OS",*obs,Import(*chain),
                                                 Cut("qOS==0"),
                                                 WeightVar(Form("weight%s",massWinName.Data())));

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
  
  
  finalState.ToLower();
  pdfU = new RooKeysPdfSpecial(Form("bkg_%s_pdftimeU_%s",finalState.Data(),year.Data()),
				 Form("bkg_%s_pdftimeU_%s",finalState.Data(),year.Data()),
				 *time,*dataU,RooKeysPdfSpecial::NoMirror,1);
  pdf1OS = new RooKeysPdfSpecial(Form("bkg_%s_pdftime1OS_%s",finalState.Data(),year.Data()),
				 Form("bkg_%s_pdftime1OS_%s",finalState.Data(),year.Data()),
				 *time,*data1OS,RooKeysPdfSpecial::NoMirror,1);
  pdf0OS = new RooKeysPdfSpecial(Form("bkg_%s_pdftime0OS_%s",finalState.Data(),year.Data()),
				 Form("bkg_%s_pdftime0OS_%s",finalState.Data(),year.Data()),
				 *time,*data0OS,RooKeysPdfSpecial::NoMirror,1);

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
  myWS->import(*dataU);      myWS->import(*pdfU);
  myWS->import(*data1OS);    myWS->import(*pdf1OS);
  myWS->import(*data0OS);    myWS->import(*pdf0OS);
  myWS->import(*data11);     myWS->import(*pdf11);
  myWS->import(*data10);     myWS->import(*pdf10);
  myWS->import(*data01);     myWS->import(*pdf01);
  myWS->import(*data00);     myWS->import(*pdf00);

  ///////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////
  RooPlot * plot1OS = time->frame(minTimeFit,maxTimeFit,280);
  data1OS->plotOn(plot1OS);
  pdf1OS->plotOn(plot1OS);
  TCanvas * c1OS = new TCanvas("c1OS","c1OS",700,725);
  c1OS->cd();
  TPad * upperPad1OS = new TPad("upperPad1OS","upperPad1OS",0,0.2,1,1);
  upperPad1OS->SetLeftMargin(0.15);
  upperPad1OS->SetBottomMargin(0.15);
  TPad * lowerPad1OS = new TPad("lowerPad1OS","lowerPad1OS",0,0,1,0.2);
  lowerPad1OS->SetLeftMargin(0.15);
  lowerPad1OS->Draw();
  upperPad1OS->Draw();
  upperPad1OS->cd() ;
  plot1OS->Draw();
  RooHist * hpull1OS = plot1OS->pullHist();
  hpull1OS->SetFillColor(kBlue);
  RooPlot * pulls1OS = time->frame(minTimeFit,maxTimeFit,280);
  pulls1OS->SetTitle("");
  pulls1OS->addPlotable(hpull1OS,"BX");
  pulls1OS->GetYaxis()->SetRangeUser(-5,5);
  lowerPad1OS->cd();
  pulls1OS->Draw();
  c1OS->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/template_%s_%g_%s_%s_%s_%s_1OS.pdf", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));
  ///////////////////////////////////////////////////////////////
  RooPlot * plot0OS = time->frame(minTimeFit,maxTimeFit,280);
  data0OS->plotOn(plot0OS);
  pdf0OS->plotOn(plot0OS);
  TCanvas * c0OS = new TCanvas("c0OS","c0OS",700,725);
  c0OS->cd();
  TPad * upperPad0OS = new TPad("upperPad0OS","upperPad0OS",0,0.2,1,1);
  upperPad0OS->SetLeftMargin(0.15);
  upperPad0OS->SetBottomMargin(0.15);
  TPad * lowerPad0OS = new TPad("lowerPad0OS","lowerPad0OS",0,0,1,0.2);
  lowerPad0OS->SetLeftMargin(0.15);
  lowerPad0OS->Draw();
  upperPad0OS->Draw();
  upperPad0OS->cd() ;
  plot0OS->Draw();
  RooHist * hpull0OS = plot0OS->pullHist();
  hpull0OS->SetFillColor(kBlue);
  RooPlot * pulls0OS = time->frame(minTimeFit,maxTimeFit,280);
  pulls0OS->SetTitle("");
  pulls0OS->addPlotable(hpull0OS,"BX");
  pulls0OS->GetYaxis()->SetRangeUser(-5,5);
  lowerPad0OS->cd();
  pulls0OS->Draw();
  c0OS->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/template_%s_%g_%s_%s_%s_%s_0OS.pdf", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));
  ///////////////////////////////////////////////////////////////
  RooPlot * plotU = time->frame(minTimeFit,maxTimeFit,280);
  dataU->plotOn(plotU);
  pdfU->plotOn(plotU);
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
  cU->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/template_%s_%g_%s_%s_%s_%s_U.pdf", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));


  ///////////////////////////////////////////////////////////////
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
  c11->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/template_%s_%g_%s_%s_%s_%s_11.eps", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));
  c11->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/template_%s_%g_%s_%s_%s_%s_11.pdf", 
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
  c10->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/template_%s_%g_%s_%s_%s_%s_10.eps", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));
  c10->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/template_%s_%g_%s_%s_%s_%s_10.pdf", 
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
  c01->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/template_%s_%g_%s_%s_%s_%s_01.eps", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));
  c01->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/template_%s_%g_%s_%s_%s_%s_01.pdf", 
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

  c00->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/template_%s_%g_%s_%s_%s_%s_00.eps", 
		   name.Data(), bdtCut, magnet.Data(), year.Data(), 
		   finalState.Data(), massWinName.Data()));
  c00->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/template_%s_%g_%s_%s_%s_%s_00.pdf", 
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
  outFile->WriteTObject(c1OS,"","Overwrite");
  outFile->WriteTObject(c0OS,"","Overwrite");
  outFile->WriteTObject(cU,"","Overwrite");
  
  outFile->Close();

  return 0;

}
