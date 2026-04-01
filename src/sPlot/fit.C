#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TApplication.h>
#include <RooRealVar.h>
#include <RooGaussModel.h>
#include <TFile.h>
#include <RooWorkspace.h>
#include <RooKeysPdf.h>
#include <RooFFTConvPdf.h>
#include <RooAddPdf.h>
#include <RooArgusBG.h>
#include <TChain.h>
#include <RooDataSet.h>
#include <TSystem.h>
#include <TROOT.h>
#include <RooDataHist.h>
#include <RooArgSet.h>
#include <RooFitResult.h>
#include <RooExponential.h>
#include <RooPlot.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <TAxis.h>
#include <RooAbsCollection.h>
#include <RooStats/SPlot.h>
#include <optionParser.h>
#include <RooCategory.h>
#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>
#include <expandFileName.h>

using namespace std;
using namespace RooFit;

Int_t main(Int_t argc, Char_t * argv[]){

  gROOT->SetStyle("Plain");

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./fit [options]\n");
    printf("Options:\n");
    printf("  -d <decay>      : name of the decay used to optimise BDT (default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = -1)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2015,2016,2017,2018,201516,20151618,Tot], default = Tot)\n");
    printf("  -f <finalState> : final state hypothesis ([KPI,PIPI,KK], default = pipi)\n");
    return 0;
  }

  TString decay         = getOption(argc,argv,"-d","bdpipi");
  Double_t bdtCut       = atof(getOption(argc,argv,"-b","-1"));
  TString magnet        = getOption(argc,argv,"-m","Tot");
  TString year          = getOption(argc,argv,"-y","Tot");
  TString finalState    = getOption(argc,argv,"-f","pipi");

  printf("EXECUTING ./fit -d %s -b %g -m %s -y %s -f %s\n",
         decay.Data(),bdtCut,magnet.Data(),year.Data(),finalState.Data());

  RooRealVar * mass = new RooRealVar("mass","m_{#pi#pi}",sPlot_cuts::data_massMin,
                                                         sPlot_cuts::data_massMax,"GeV/c^{2}");
  mass->setPlotLabel("m_{#pi#pi}");
  mass->setBins(10000,"cache");
  RooRealVar * nSPDHits = new RooRealVar("nSPDHits","nSPDHits",0.,10000.);
  RooRealVar * nPVs = new RooRealVar("nPVs","nPVs",0.,10000.);
  RooRealVar * bPT = new RooRealVar("bPT","bPT",0.,100.);
  RooRealVar * bETA = new RooRealVar("bETA","bETA",0.,10.);
  RooRealVar * bPHI = new RooRealVar("bPHI","bPHI",-10.,10.);

  RooRealVar * etaOS = new RooRealVar("etaOS","etaOS",0,0.5);
  RooRealVar * etaSSk = new RooRealVar("etaSSk","etaSSk",0,0.5);
  RooRealVar * etaSSpi = new RooRealVar("etaSSpi","etaSSpi",0,0.5);
  RooRealVar * etaSSp = new RooRealVar("etaSSp","etaSSp",0,0.5);
  RooRealVar * etaSS  = new RooRealVar("etaSS","etaSS",0,0.5);

  RooRealVar * piplusP   = new RooRealVar("piplusP","piplusP",0,1e6);
  RooRealVar * piplusETA = new RooRealVar("piplusETA","piplusETA",0,1e6);
  RooRealVar * piplusPHI = new RooRealVar("piplusPHI","piplusPHI",-10,10);
  RooRealVar * piminusP   = new RooRealVar("piminusP","piminusP",0,1e6);
  RooRealVar * piminusETA = new RooRealVar("piminusETA","piminusETA",0,1e6);
  RooRealVar * piminusPHI = new RooRealVar("piminusPHI","piminusPHI",-10,10);
  
  RooRealVar * piplusPT = new RooRealVar("piplusPT","piplusPT",0,1e6);
  RooRealVar * piplusIPCHI2 = new RooRealVar("piplusIPCHI2","piplusIPCHI2",0,1e6);
  RooRealVar * piminusPT = new RooRealVar("piminusPT","piminusPT",0,1e6);
  RooRealVar * piminusIPCHI2 = new RooRealVar("piminusIPCHI2","piminusIPCHI2",0,1e6);
  RooRealVar * bDOCA = new RooRealVar("bDOCA","bDOCA",0,1e6);
  RooRealVar * bDIRA = new RooRealVar("bDIRA","bDIRA",0,2);
  
  RooRealVar * bVTXCHI2 = new RooRealVar("bVTXCHI2","bVTXCHI2",0,100);
  RooRealVar * bIPCHI2 = new RooRealVar("bIPCHI2","bIPCHI2",0,100);
  RooRealVar * bIPCHI2NEXT = new RooRealVar("bIPCHI2NEXT","bIPCHI2NEXT",-100,1e9);
  RooRealVar * bFDCHI2 = new RooRealVar("bFDCHI2","bFDCHI2",0,1e6);
  RooRealVar * rFD = new RooRealVar("rFD","rFD",0,1e6);
  RooRealVar * rFDPV = new RooRealVar("rFDPV","rFDPV",0,1e6);
  
  RooRealVar * bP = new RooRealVar("bP","bP",0,1e6);
  RooRealVar * bPVx = new RooRealVar("bPVx","bPVx",-1e6,1e6);
  RooRealVar * bPVy = new RooRealVar("bPVy","bPVy",-1e6,1e6);
  RooRealVar * bPVz = new RooRealVar("bPVz","bPVz",-1e6,1e6);
  RooRealVar * bENDVx = new RooRealVar("bENDVx","bENDVx",-1e6,1e6);
  RooRealVar * bENDVy = new RooRealVar("bENDVy","bENDVy",-1e6,1e6);
  RooRealVar * bENDVz = new RooRealVar("bENDVz","bENDVz",-1e6,1e6);
  RooRealVar * piplusDLLKPI = new RooRealVar("piplusDLLKPI","piplusKPI",-1e6,1e6);
  RooRealVar * piplusDLLPPI = new RooRealVar("piplusDLLPPI","piplusPPI",-1e6,1e6);
  RooRealVar * piplusTRACKCHI2 = new RooRealVar("piplusTRACKCHI2","piplusTRACKCHI2",0,1e6);
  RooRealVar * piminusDLLKPI = new RooRealVar("piminusDLLKPI","piminusKPI",-1e6,1e6);
  RooRealVar * piminusDLLPPI = new RooRealVar("piminusDLLPPI","piminusPPI",-1e6,1e6);
  RooRealVar * piminusTRACKCHI2 = new RooRealVar("piminusTRACKCHI2","piminusTRACKCHI2",0,1e6);
  
  RooRealVar * time = new RooRealVar("time","time",sPlot_cuts::timeMin,sPlot_cuts::timeMax);
  RooRealVar * timeErr = new RooRealVar("timeErr","timeErr",0,sPlot_cuts::timeErrMax);

  RooArgSet * obs = new RooArgSet();
  obs->add(*mass); 
  obs->add(*time); obs->add(*timeErr); 
  obs->add(*nSPDHits);  obs->add(*nPVs);
  obs->add(*bPT); obs->add(*bETA); obs->add(*bPHI);
  obs->add(*etaOS); 
  obs->add(*etaSSk); obs->add(*etaSSpi); obs->add(*etaSSp); obs->add(*etaSS);
  obs->add(*piplusP); obs->add(*piplusETA); obs->add(*piplusPHI);
  obs->add(*piminusP); obs->add(*piminusETA); obs->add(*piminusPHI);
  
  obs->add(*piplusPT);
  obs->add(*piplusIPCHI2);
  obs->add(*piminusPT);
  obs->add(*piminusIPCHI2);
  obs->add(*bDOCA);
  obs->add(*bDIRA);
  
  obs->add(*bVTXCHI2);
  obs->add(*bIPCHI2);
  obs->add(*bIPCHI2NEXT);
  obs->add(*bFDCHI2);
  obs->add(*rFD);
  obs->add(*rFDPV);
  
  obs->add(*bP);
  obs->add(*bPVx);
  obs->add(*bPVy);
  obs->add(*bPVz);
  obs->add(*bENDVx);
  obs->add(*bENDVy);
  obs->add(*bENDVz);
  obs->add(*piplusDLLKPI);
  obs->add(*piplusDLLPPI);
  obs->add(*piplusTRACKCHI2);
  obs->add(*piminusDLLKPI);
  obs->add(*piminusDLLPPI);
  obs->add(*piminusTRACKCHI2);
  
  Double_t r_bdkpi = 1, r_bdpipi = 0.262,
           r_bskk = 0.316, r_bskpi = 0.074,
           r_bdkk = 0.018*r_bskk, r_bspipi = 0.05*r_bdpipi,
           r_lbpk = 0.071, r_lbppi = 0.045;
  Double_t tot = r_bdkpi+r_bdpipi+r_bdkk+r_bskk+r_bskpi+r_bspipi+r_lbpk+r_lbppi;

  RooRealVar * delta   = new RooRealVar("delta","delta",0,-0.03,0.03);
  RooRealVar * sigma   = new RooRealVar("sigma","sigma",0.025,0.005,0.1);
  RooGaussModel * resM = new RooGaussModel("resM","resM",*mass,*delta,*sigma);

  TFile * templatesFile = new TFile(Form("${B2HH_OUT}/sPlot/template/Templates_%s_%g_%s_%s.root",
                                         decay.Data(),bdtCut,year.Data(),magnet.Data()));
  templatesFile->Print("v");
  RooWorkspace * w = (RooWorkspace *) templatesFile->Get("Templates");
  w->Print("v");
 
  RooKeysPdf * pdf_bdkpi_tmp = (RooKeysPdf *) w->pdf("bdkpi_pipi");
  RooFFTConvPdf * pdf_bdkpi = new RooFFTConvPdf("pdf_bdkpi","pdf_bdkpi",*mass,*pdf_bdkpi_tmp,*resM);
  pdf_bdkpi->setBufferFraction(0.2);
  pdf_bdkpi->setBufferStrategy(RooFFTConvPdf::Flat);

  RooKeysPdf * pdf_bdpipi_tmp = (RooKeysPdf *) w->pdf("bdpipi_pipi");
  RooFFTConvPdf * pdf_bdpipi = new RooFFTConvPdf("pdf_bdpipi","pdf_bdpipi",*mass,*pdf_bdpipi_tmp,*resM);
  pdf_bdpipi->setBufferFraction(0.2);
  pdf_bdpipi->setBufferStrategy(RooFFTConvPdf::Flat);

  RooKeysPdf * pdf_bdkk_tmp = (RooKeysPdf *) w->pdf("bdkk_pipi");
  RooFFTConvPdf * pdf_bdkk = new RooFFTConvPdf("pdf_bdkk","pdf_bdkk",*mass,*pdf_bdkk_tmp,*resM);
  pdf_bdkk->setBufferFraction(0.2);
  pdf_bdkk->setBufferStrategy(RooFFTConvPdf::Flat);

  RooKeysPdf * pdf_bskk_tmp = (RooKeysPdf *) w->pdf("bskk_pipi");
  RooFFTConvPdf * pdf_bskk = new RooFFTConvPdf("pdf_bskk","pdf_bskk",*mass,*pdf_bskk_tmp,*resM);
  pdf_bskk->setBufferFraction(0.2);
  pdf_bskk->setBufferStrategy(RooFFTConvPdf::Flat);

  RooKeysPdf * pdf_bskpi_tmp = (RooKeysPdf *) w->pdf("bskpi_pipi");
  RooFFTConvPdf * pdf_bskpi = new RooFFTConvPdf("pdf_bskpi","pdf_bskpi",*mass,*pdf_bskpi_tmp,*resM);
  pdf_bskpi->setBufferFraction(0.2);
  pdf_bskpi->setBufferStrategy(RooFFTConvPdf::Flat);

  RooKeysPdf * pdf_bspipi_tmp = (RooKeysPdf *) w->pdf("bspipi_pipi");
  RooFFTConvPdf * pdf_bspipi = new RooFFTConvPdf("pdf_bspipi","pdf_bspipi",*mass,*pdf_bspipi_tmp,*resM);
  pdf_bspipi->setBufferFraction(0.2);
  pdf_bspipi->setBufferStrategy(RooFFTConvPdf::Flat);

  RooKeysPdf * pdf_lbpk_tmp = (RooKeysPdf *) w->pdf("lbpk_pipi");
  RooFFTConvPdf * pdf_lbpk = new RooFFTConvPdf("pdf_lbpk","pdf_lbpk",*mass,*pdf_lbpk_tmp,*resM);
  pdf_lbpk->setBufferFraction(0.2);
  pdf_lbpk->setBufferStrategy(RooFFTConvPdf::Flat);

  RooKeysPdf * pdf_lbppi_tmp = (RooKeysPdf *) w->pdf("lbppi_pipi");
  RooFFTConvPdf * pdf_lbppi = new RooFFTConvPdf("pdf_lbppi","pdf_lbppi",*mass,*pdf_lbppi_tmp,*resM);
  pdf_lbppi->setBufferFraction(0.2);
  pdf_lbppi->setBufferStrategy(RooFFTConvPdf::Flat);

  printf("STOCAZZO\n");
  //RooRealVar * f_bdkpi  = new RooRealVar("f_bdkpi" ,"f_bdkpi" ,r_bdkpi/tot);
  RooRealVar * f_bdpipi = new RooRealVar("f_bdpipi","f_bdpipi",r_bdpipi/tot);
  RooRealVar * f_bdkk   = new RooRealVar("f_bdkk",  "f_bdkk",  r_bdkk/tot);
  RooRealVar * f_bskk   = new RooRealVar("f_bskk"  ,"f_bskk"  ,r_bskk/tot);
  RooRealVar * f_bskpi  = new RooRealVar("f_bskpi" ,"f_bskpi" ,r_bskpi/tot);
  RooRealVar * f_bspipi = new RooRealVar("f_bspipi","f_bspipi",r_bspipi/tot);
  RooRealVar * f_lbpk   = new RooRealVar("f_lbpk"  ,"f_lbpk"  ,r_lbpk/tot);
  RooRealVar * f_lbppi  = new RooRealVar("f_lbppi" ,"f_lbppi" ,r_lbppi/tot);

  RooAddPdf * pdfSig = new RooAddPdf("pdfSig","pdfSig",
                                     RooArgSet(*pdf_bskk,*pdf_bskpi,
                                               *pdf_bdkk,*pdf_bspipi,
                                               *pdf_lbpk,*pdf_lbppi,
                                               *pdf_bdpipi,*pdf_bdkpi),
                                    RooArgSet(*f_bskk,*f_bskpi,
                                               *f_bdkk,*f_bspipi,
                                               *f_lbpk,*f_lbppi,
                                               *f_bdpipi));

  RooRealVar * m0 = new RooRealVar("m0","m0",5.146,5.0,5.3);
  RooRealVar * cA = new RooRealVar("cA","cA",-30.,-100.,0.);
  RooArgusBG * argus_tmp = new RooArgusBG("argus_tmp","argus_tmp",*mass,*m0,*cA);
  RooFFTConvPdf * argus = new RooFFTConvPdf("argus","argus",*mass,*argus_tmp,*resM);
  argus->setBufferFraction(0.2);

  RooRealVar * slope = new RooRealVar("slope","slope",-1.,-10.,0.);
  RooExponential * bkg = new RooExponential("bkg","bkg",*mass,*slope);

  RooRealVar * NSig = new RooRealVar("NSig","NSig",400000.,0.,1e7);
  RooRealVar * N3Body = new RooRealVar("N3Body","N3Body",300000.,0.,1e6);
  RooRealVar * Nbkg = new RooRealVar("Nbkg","Nbkg",500000.,0.,1e7);

  RooAddPdf * pdf = new RooAddPdf("pdf","pdf",RooArgSet(*pdfSig,*argus,*bkg),
                                              RooArgSet(*NSig,*N3Body,*Nbkg));
  TChain * chain = new TChain("b2hh","b2hh");
  chain->Add(Form("${B2HH_OUT}/sPlot/tuple_reduced/b2hh_%s_%g_%s_%s_%s.root",
                  decay.Data(),bdtCut,year.Data(),magnet.Data(),finalState.Data()));

  RooDataSet * data = new RooDataSet("data","data",*obs,Import(*chain)); 
  mass->setBins(640);
  RooDataHist * dataH = new RooDataHist("dataH","dataH",RooArgSet(*mass),*data);

  RooArgSet* params = pdf->getParameters(*mass);
  TString nfParams = Form("${B2HH_OUT}/sPlot/params/params_%s_%g_%s_%s_%s.txt",
                          decay.Data(), bdtCut, year.Data(), magnet.Data(), finalState.Data());
  system(Form("touch %s", nfParams.Data()));
  expandFileName::expandFileName(nfParams);
  printf("Reading parameters from %s\n", nfParams.Data());
  params->readFromFile(nfParams);
  params->Print();
  RooFitResult * r = pdf->fitTo(*dataH,Strategy(2),Verbose(kTRUE),PrintLevel(3),Offset(kTRUE),Save(),NumCPU(12));
  r->Print("v");

  params->writeToFile(nfParams);

  TCanvas * c = new TCanvas("c","c",700,725);
  c->cd();
  RooPlot * plot = mass->frame(80); plot->SetTitle("");
  plot->GetXaxis()->SetTitleSize(0.05); plot->GetXaxis()->SetLabelSize(0.05);
  plot->GetXaxis()->SetTitleOffset(1.1);
  plot->GetXaxis()->SetTickLength(0.05); plot->GetXaxis()->SetNdivisions(404,kTRUE);
  plot->GetYaxis()->SetTitleSize(0.05); plot->GetYaxis()->SetLabelSize(0.05);
  plot->GetYaxis()->SetTitleOffset(2.0);
  plot->GetYaxis()->SetTickLength(0.05); plot->GetYaxis()->SetNdivisions(406,kTRUE);

  data->plotOn(plot,Name("Data"));
  pdf->plotOn(plot,Components("pdf_bdkpi"),Name("bdkpi"),LineColor(kBlack),LineWidth(2),LineStyle(0),
              DrawOption("LF2"),FillStyle(3254),FillColor(kBlack));
  pdf->plotOn(plot,Components("pdf_bdkpi"),LineColor(kBlack),LineWidth(2),FillStyle(0));

  pdf->plotOn(plot,Components("pdf_bskk"),Name("bskk"),LineColor(kBlack),LineStyle(2),LineWidth(3),FillColor(kWhite));

  pdf->plotOn(plot,Components("pdf_bdpipi"),Name("bdpipi"),LineColor(kBlack),LineWidth(2),LineStyle(0),
              DrawOption("LF2"),FillStyle(3200),FillColor(kBlack));
  pdf->plotOn(plot,Components("pdf_bdpipi"),LineColor(kBlack),LineWidth(2),FillStyle(0));

  pdf->plotOn(plot,Components("pdf_bskpi"),Name("bskpi"),LineColor(kBlack),LineWidth(2),LineStyle(0),
              DrawOption("LF2"),FillStyle(3244),FillColor(kBlack));
  pdf->plotOn(plot,Components("pdf_bskpi"),LineColor(kBlack),LineWidth(2),FillStyle(0));

  pdf->plotOn(plot,Components("pdf_lbpk"),Name("lbpk"),LineColor(kBlack),LineWidth(2),LineStyle(0),
              DrawOption("LF2"),FillStyle(1001),FillColor(kGray+1));
  pdf->plotOn(plot,Components("pdf_lbpk"),LineColor(kBlack),LineWidth(2),FillStyle(0));

  pdf->plotOn(plot,Components("pdf_lbppi"),Name("lbppi"),LineColor(kBlack),LineWidth(2),LineStyle(0),
              DrawOption("LF2"),FillStyle(1001),FillColor(kGray+3));
  pdf->plotOn(plot,Components("pdf_lbppi"),LineColor(kBlack),LineWidth(2),FillStyle(0));

/*
  pdf->plotOn(plot,Components("pdf_bspipi"),Name("bspipi"),LineColor(kBlack),DrawOption("LF2"));
  pdf->plotOn(plot,Components("pdf_bspipi"),Name("bspipi"),LineColor(kBlack),DrawOption("LF2"));

  pdf->plotOn(plot,Components("pdf_bdkk"),Name("bdkk"),LineColor(kBlack),DrawOption("LF2"));
  pdf->plotOn(plot,Components("pdf_bdkk"),Name("bdkk"),LineColor(kBlack),DrawOption("LF2"));
*/
  pdf->plotOn(plot,Components("argus"),Name("argus"),LineColor(kBlack),LineWidth(3),LineStyle(9),FillColor(kWhite));
  pdf->plotOn(plot,Components("bkg"),Name("bkg"),LineColor(kBlack),LineWidth(3),LineStyle(5),FillColor(kWhite));

  pdf->plotOn(plot,Name("tot"));
  plot->Draw();

  TPad * myPad = (TPad *) c->GetPad(0);
  myPad->SetLeftMargin(0.2); myPad->SetBottomMargin(0.15); myPad->SetBorderSize(0);
  c->Draw();

  TLegend * leg1 = new TLegend(0.6,0.6,0.85,0.85,"");
  leg1->SetName("leg1"); leg1->SetTextSize(0.04);
  leg1->SetFillColor(kWhite); leg1->SetBorderSize(0);
  RooCurve * curv_bdkpi = (RooCurve *) c->FindObject("bdkpi");
  leg1->AddEntry(curv_bdkpi,"B^{0}#rightarrow K^{+}#pi^{-}","f");
  RooCurve * curv_bdpipi = (RooCurve *) c->FindObject("bdpipi");
  leg1->AddEntry(curv_bdpipi,"B^{0}#rightarrow #pi^{+}#pi^{-}","f");
  RooCurve * curv_bskk = (RooCurve *) c->FindObject("bskk");
  leg1->AddEntry(curv_bskk,"B_{s}^{0}#rightarrow K^{+}K^{-}","f");
  RooCurve * curv_bskpi = (RooCurve *) c->FindObject("bskpi");
  leg1->AddEntry(curv_bskpi,"B_{s}^{0}#rightarrow #pi^{+}K^{-}","f");

  TLegend * leg2 = new TLegend(0.6,0.34,0.85,0.6,"");
  leg2->SetName("leg2"); leg2->SetTextSize(0.04);
  leg2->SetFillColor(kWhite); leg2->SetBorderSize(0);
  RooCurve * curv_lbpk = (RooCurve *) c->FindObject("lbpk");
  leg2->AddEntry(curv_lbpk,"#Lambda_{b}^{0}#rightarrow pK^{-}","f");
  RooCurve * curv_lbppi = (RooCurve *) c->FindObject("lbppi");
  leg2->AddEntry(curv_lbppi,"#Lambda_{b}^{0}#rightarrow p#pi^{-}","f");
  RooCurve * curv_argus = (RooCurve *) c->FindObject("argus");
  leg2->AddEntry(curv_argus,"B#rightarrow 3-body","f");
  RooCurve * curv_bkg = (RooCurve *) c->FindObject("bkg");
  leg2->AddEntry(curv_bkg,"Comb. bkg","f");

  leg1->Draw("same");
  leg2->Draw("same");

  c->Update();
  c->Draw();
  c->SaveAs(Form("${B2HH_OUT}/sPlot/plots/fit_b2hh_%s_%g_%s_%s_%s.pdf",
                 decay.Data(), bdtCut, year.Data(), magnet.Data(), finalState.Data()));
  params->setAttribAll("Constant",kTRUE);
  RooArgSet * yields = (RooArgSet *) params->selectByName("N*");
  yields->setAttribAll("Constant",kFALSE);

  
  RooStats::SPlot * myPlot = new RooStats::SPlot("myPlot","myPlot",*data,pdf,*yields);
  myPlot->Print("v");

  RooRealVar * weight = new RooRealVar("NSig_sw","NSig_sw",-1e6,1e6);
  obs->add(*weight);
  data->setDefaultStorageType(RooAbsData::Tree);
  RooDataSet * dataS = new RooDataSet("b2hhW","b2hhW",*obs,Import(*data));
  dataS->changeObservableName("NSig_sw","weight");
  //dataS->setDefaultStorageType(RooAbsData::Tree);

  dataS->SetName("b2hhW"); dataS->SetTitle("b2hhW");
  //const TTree * outTree = dataS->tree();
  
  TFile *outFile = new TFile(Form("${B2HH_OUT}/sPlot/tuple_reduced/b2hh_%s_%g_%s_%s_%s.root",
                                  decay.Data(), bdtCut, year.Data(), magnet.Data(), finalState.Data()),
                             "UPDATE");

  TTree * outTree = dataS->GetClonedTree();

  //outTree->SetName("b2hhW"); outTree->SetName("b2hhW");

  //TFile * outFile = new TFile("sameNew.root","UPDATE");
  //TFile * outFile = new TFile(Form("b2hh_%s_%g_%s_%s_%s.root",
  //                                 decay.Data(),bdtCut,year.Data(),magnet.Data(),finalState.Data()),
  //                            "UPDATE");
  
  outFile->WriteTObject(c,"","Overwrite");
  outFile->WriteTObject(outTree,"b2hhW","Overwrite");
  outFile->Close();

  templatesFile->Close();

  return 0;
}
