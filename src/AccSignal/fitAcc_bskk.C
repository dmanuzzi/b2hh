#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TApplication.h>
#include <RooFit.h>
#include <TChain.h>
#include <RooFitResult.h>
#include <RooRealVar.h>
#include <RooExponential.h>
#include <optionParser.h>
#include <TString.h>
#include <TROOT.h>
#include <RooTimeAccPdf.h>
#include <RooEffProd.h>
#include <RooExponential.h>
#include <RooDataSet.h>
#include <RooPlot.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TAxis.h>
#include <RooHist.h>
#include <RooCategory.h>
#include <RooAddPdf.h>
#include <TF1.h>
#include <TFile.h>
#include <RooNumIntConfig.h>
#include <RooAbsReal.h>
#include <RooBDecay.h>
#include <RooRealConstant.h>
#include <RooGaussModel.h>
#include <TPaveText.h>
#include <TLegend.h>
#include <RooCurve.h>

#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>
#include <expandFileName.h>
using namespace std;
using namespace RooFit;

Int_t main(Int_t argc, Char_t * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./fitAcc2 [options]\n");
    printf("Options:\n");
    printf("  -C <name>       : decay used for BDT train ([PIPI, KK], default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = 0.12)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2011,2012,Tot], default = 2016)\n");
    printf("  -n <decay>      : decay under study (default = bdkpi)\n");
    printf("  -f <finalState> : considered final state hypothesis (default = kpi)\n");
    printf("  -F              : flag for executing the fit\n");
    printf("  -W              : enable reweighting of kinematic and PID");
    printf("  -V              : consider the true decay time instead of the reconstructed one");
    return 0;
  }


  RooAbsReal::defaultIntegratorConfig()->setEpsAbs(1e-9) ;
  RooAbsReal::defaultIntegratorConfig()->setEpsRel(1e-9) ;
  RooAbsReal::defaultIntegratorConfig()->getConfigSection("RooAdaptiveGaussKronrodIntegrator1D").setCatLabel("method","15Points");
  RooAbsReal::defaultIntegratorConfig()->getConfigSection("RooAdaptiveGaussKronrodIntegrator1D").setRealValue("maxSeg", 1000 );
  RooAbsReal::defaultIntegratorConfig()->method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D");
  RooAbsReal::defaultIntegratorConfig()->method1DOpen().setLabel("RooAdaptiveGaussKronrodIntegrator1D");

  RooAbsReal::defaultIntegratorConfig()->Print("v");

  TString configuration = getOption(argc,argv,"-C","PIPI");
  Double_t bdtCut = atof(getOption(argc,argv,"-b","0.12"));
  TString name = getOption(argc,argv,"-n","bdkpi");
  TString finalState = getOption(argc,argv,"-f","kpi");
  TString magnet = getOption(argc,argv,"-m","Tot");
  TString year = getOption(argc,argv,"-y","Tot");
  Bool_t fitFlag = getBoolOption(argc,argv,"-F");
  Bool_t useWeights = getBoolOption(argc, argv, "-W");
  Bool_t useTrueTau = getBoolOption(argc, argv, "-V");
  TString taggerName = getOption(argc, argv, "-Q", "qSSk");
  Int_t flav = atoi(getOption(argc, argv, "-q", "4"));
  
  TString nTauVar = (useTrueTau ? "trueTau" : "time");
  RooRealVar * time = new RooRealVar(nTauVar, "Decay time",accSignal_cuts::minTimeFit,accSignal_cuts::maxTimeFit,"ps");
  RooCategory * q = new RooCategory(taggerName,taggerName);
  if (flav == 0) {
    q->defineType("Untag", 0);
  } else if (flav == +1){
    q->defineType("B", +1);
  } else if (flav == +2){
    q->defineType("Bbar", -1);
  } else if (flav == +3){
    q->defineType("B", +1);
    q->defineType("Bbar", -1);
  } else if (flav == +4){
    q->defineType("B", +1);
    q->defineType("Bbar", -1);
    q->defineType("Untag", 0);
  } 
  
  RooRealVar * weight = new RooRealVar("weight","weight",-1e6,1e6);

  RooRealVar *gammaData = new RooRealVar("gammaData", "gammaData", accSignal_consts::tauData);
  RooRealVar *gammaBd = new RooRealVar("gammaBd", "gammaBd", accSignal_consts::tauBd);
  RooRealVar *gammaBs = new RooRealVar("gammaBs", "gammaBs", accSignal_consts::tauBs);
  RooRealVar *deltaGammaBs = new RooRealVar("deltaGammaBs", "deltaGammaBs", accSignal_consts::dgBs);
  RooRealVar *gammaKK = new RooRealVar("gammaKK", "gammaKK", accSignal_consts::tauKK);
  RooRealVar *deltaGammaKK = new RooRealVar("deltaGammaKK", "deltaGammaKK", accSignal_consts::dGKK);
  RooRealVar *gammaLb = new RooRealVar("gammaLb", "gammaLb", accSignal_consts::tauLb);
  RooRealVar *sigmaT = new RooRealVar("sigmaT", "sigmaT", 0.04, 0.00001, 1);
  RooGaussModel * resT = new RooGaussModel("resT","resT",*time,RooRealConstant::value(0.000),*sigmaT);
  // RooGaussModel *resT = new RooGaussModel("resT", "resT", *time, RooRealConstant::value(0.000), RooRealConstant::value(useTrueTau ? 0.001 : 0.040));
  RooRealVar *dms = new RooRealVar("dms", "dms", accSignal_consts::dms);
  RooRealVar *dmd = new RooRealVar("dmd", "dmd", accSignal_consts::dmd);

  RooBDecay *bskk_Untag = new RooBDecay("bskk_Untag", "bskk_Untag", *time, *gammaKK, *deltaGammaKK,
                                        RooRealConstant::value(1.0), RooRealConstant::value(accSignal_consts::ADGKK),
                                        RooRealConstant::value(0.0), RooRealConstant::value(0.0),
                                        *dms, *resT, RooBDecay::SingleSided);
  RooBDecay *bskk_Bs = new RooBDecay("bskk_Bs", "bskk_Bs", *time, *gammaKK, *deltaGammaKK,
                                        RooRealConstant::value(1.0), RooRealConstant::value(accSignal_consts::ADGKK),
                                        RooRealConstant::value(+accSignal_consts::CKK), RooRealConstant::value(-accSignal_consts::SKK),
                                        *dms, *resT, RooBDecay::SingleSided);
  RooBDecay *bskk_Bsbar = new RooBDecay("bskk_Bsbar", "bskk_Bsbar", *time, *gammaKK, *deltaGammaKK,
                                        RooRealConstant::value(1.0), RooRealConstant::value(accSignal_consts::ADGKK),
                                        RooRealConstant::value(-accSignal_consts::CKK), RooRealConstant::value(+accSignal_consts::SKK),
                                        *dms, *resT, RooBDecay::SingleSided);

  RooRealVar *p0 = new RooRealVar("p0", "p0", 0, 10);
  RooRealVar *p1 = new RooRealVar("p1", "p1", -100, 100);
  RooRealVar *p2 = new RooRealVar("p2", "p2", -100, 100);
  RooRealVar *p3 = new RooRealVar("p3", "p3", -100, 100);
  RooRealVar *p4 = new RooRealVar("p4", "p4", -100, 100);
  RooRealVar *p5 = new RooRealVar("p5", "p5", -100, 100);
  RooRealVar *p6 = new RooRealVar("p6", "p6", -100, 100);
  RooRealVar *p7 = new RooRealVar("p7", "p7", -100, 100);
  RooRealVar *p8 = new RooRealVar("p8", "p8", -100, 100);
  RooRealVar *p9 = new RooRealVar("p9", "p9", -100, 100);
  RooRealVar *p10 = new RooRealVar("p10", "p10", 3, 10);
  RooTimeAccPdf *acc = new RooTimeAccPdf("acc", "acc", *time, *p0, *p1, *p2, *p3, *p4, *p5,
                                         *p6, *p7, *p8, *p9, *p10);

  RooEffProd *pdf;
  if (flav == 0 || flav == 3 || flav == 4)
    pdf = new RooEffProd("pdf","pdf",*bskk_Untag,*acc);
  else if (flav == 1)
    pdf = new RooEffProd("pdf", "pdf", *bskk_Bs, *acc);
  else if (flav == 2)
    pdf = new RooEffProd("pdf", "pdf", *bskk_Bsbar, *acc);
  else return -1;
  time->setRange("total",accSignal_cuts::minTimeFit, accSignal_cuts::maxTimeFit);
  RooAbsReal * pdfIntegral = pdf->createIntegral(RooArgSet(*time),"total");


  TChain * chain = new TChain("b2hh","b2hh");
  chain->Add(Form("${B2HH_OUT}/AccSignal/kineWeight/%s_%s_%s_%g_%s_%s_Kine.root", 
                  name.Data(), finalState.Data(),
                  configuration.Data(), bdtCut,
                  year.Data(), magnet.Data()));

  RooArgSet * obs = new RooArgSet();
  obs->add(*time); obs->add(*q); 
  if (useWeights) obs->add(*weight);
  //obs->add(*mass);
  
  RooArgSet * params = pdf->getParameters(*obs);
  TString nfParams = Form("${B2HH_OUT}/AccSignal/params_test/params_%s_%s_%g_%s_%s_%s.txt",
                          TString(name+"_"+finalState).Data(),
                          configuration.Data(), bdtCut, year.Data(), magnet.Data(),
                          "Kine");
  TString optLabel = "";
  if (!useWeights){
    nfParams.ReplaceAll(".txt", "_noW.txt");
    optLabel += "_noW";
  } 
  if (useTrueTau){
    nfParams.ReplaceAll(".txt", "_trueTau.txt");
    optLabel += "_trueTau";
  }
  optLabel+= Form("_%s_case%d",taggerName.Data(),flav);

  system(Form("touch %s", nfParams.Data()));
  expandFileName::expandFileName(nfParams);
  printf("read parameter file: %s\n", nfParams.Data());
  params->readFromFile(nfParams);
  dms->setVal(accSignal_consts::dms);
  params->Print("v");
 
  RooDataSet * data = nullptr;
  if (useWeights)
    data = new RooDataSet("data","data", *obs,Import(*chain), WeightVar(*weight));
  else
    data = new RooDataSet("data", "data", *obs, Import(*chain));

  data->Print("v");
  if(fitFlag) {
    RooFitResult * res = pdf->fitTo(*data,NumCPU(12),Verbose(kTRUE),
				    PrintLevel(3),Strategy(2),Hesse(),
				    SumW2Error(kFALSE),Offset(kTRUE),Save());
    res->Print("v");
  }

  nfParams.ReplaceAll(".txt", Form("case%d.txt",flav));
  params->writeToFile(nfParams);
  
  
  RooPlot * plot = time->frame(accSignal_cuts::minTimeFit, accSignal_cuts::maxTimeFit,280);
  plot->SetTitle("");
  data->plotOn(plot,MarkerSize(0.8));
  acc->plotOn(plot,LineColor(kRed),Normalization(1,RooAbsReal::Relative),Name("acc"));
  pdf->plotOn(plot,Name("pdf"),LineWidth(2));
  data->plotOn(plot,MarkerSize(0.8));

  plot->GetXaxis()->SetTitle("Decay time [ps]");
  plot->GetXaxis()->SetTitleSize(0.05);
  plot->GetXaxis()->SetLabelSize(0.05);
  plot->GetXaxis()->SetTitleOffset(1.1);
  plot->GetXaxis()->SetTickLength(0.05);
  plot->GetXaxis()->SetLabelFont(62);
  plot->GetXaxis()->SetTitleFont(62);
  plot->GetYaxis()->SetTitle("Candidates / ( 0.05 ps )");
  plot->GetYaxis()->SetTitleSize(0.05);
  plot->GetYaxis()->SetLabelSize(0.05);
  plot->GetYaxis()->SetTitleOffset(1.7);
  plot->GetYaxis()->SetTickLength(0.05);
  plot->GetYaxis()->SetLabelFont(62);
  plot->GetYaxis()->SetTitleFont(62);
  plot->GetXaxis()->SetTitleFont(132);
  plot->GetXaxis()->SetLabelFont(132);
  plot->GetXaxis()->SetTitleSize(0.06);
  plot->GetXaxis()->SetLabelSize(0.06);
  plot->GetYaxis()->SetTitleFont(132);
  plot->GetYaxis()->SetLabelFont(132);
  plot->GetYaxis()->SetTitleSize(0.06);
  plot->GetYaxis()->SetLabelSize(0.06);
  plot->GetYaxis()->SetTitleOffset(1.70);
  plot->GetYaxis()->SetNdivisions(509,kTRUE);
  plot->SetMinimum(0);
  
  TPaveText * lhcb = new TPaveText(0.35,0.55,0.55,0.85,"NDC");
  lhcb->SetTextAlign(12);
  lhcb->AddText("LHCb");
  lhcb->AddText(Form("Year: %s, mag: %s %s", year.Data(), magnet.Data(), optLabel.Data()));
  lhcb->AddText(Form("%s %s, f. state: %s", "MC", name.Data(), finalState.Data()));
  lhcb->AddText(Form("bdt%s>%g, case %d",configuration.Data(), bdtCut, flav));
  lhcb->SetFillColor(kWhite);
  lhcb->SetTextFont(132);
  lhcb->SetTextSize(0.05);
  
  TCanvas * c1 = new TCanvas("c1","c1",700,725);
  c1->cd();
  TPad * upperPad = new TPad("upperPad","upperPad",0,0.2,1,1);
  upperPad->SetLeftMargin(0.15);
  upperPad->SetBottomMargin(0.15);
  TPad * lowerPad = new TPad("lowerPad","lowerPad",0,0,1,0.2);
  lowerPad->SetLeftMargin(0.15);
  lowerPad->Draw();
  upperPad->Draw();
  upperPad->cd();
  plot->Draw();

  TLegend * leg = new TLegend(0.35,0.45,0.55,0.55,"");
  leg->SetName("leg");
  leg->SetTextFont(132);
  leg->SetTextSize(0.06);
  //leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  //leg->SetX1(0.35);
  //leg->SetX2(0.35);
  //leg->SetY1(0.55);
  //leg->SetY2(0.75);
  RooCurve * myAcc = (RooCurve *) c1->FindObject("acc");
  leg->AddEntry(myAcc,"Decay-time efficiency","l");
  //leg->Draw("same");

  lhcb->Draw("same");
  leg->Draw("same");

  RooHist * hpull = plot->pullHist();
  hpull->SetFillColor(kBlue);
  RooPlot * pulls = time->frame(accSignal_cuts::minTimeFit, accSignal_cuts::maxTimeFit,280);
  pulls->SetTitle("");
  pulls->addPlotable(hpull,"BX");
  pulls->GetYaxis()->SetRangeUser(-5,5);
  pulls->GetYaxis()->SetTitle("pull");
  pulls->GetYaxis()->SetTitleSize(0.1);
  pulls->GetYaxis()->SetLabelSize(0.1);
  pulls->GetYaxis()->SetNdivisions(504,kTRUE);
  pulls->GetYaxis()->SetTitleOffset(0.2);
  lowerPad->cd();
  pulls->Draw();

  TFile * outFile = TFile::Open(Form("${B2HH_OUT}/AccSignal/plots_test/plot_%s_%s_%s_%g_%s_%s_Kine%s.root",
                                 name.Data(), finalState.Data(),
                                 configuration.Data(), bdtCut,
                                 year.Data(), magnet.Data(), optLabel.Data()),
                                 "RECREATE");
  
  outFile->WriteTObject(c1,"","Overwrite");
  for (TString format : {"pdf"})
    c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots_test/fitForAcc_%s_%s_%s_%g_%s_%s_%s.%s",
                    name.Data(), finalState.Data(),
                    configuration.Data(), bdtCut, year.Data(), magnet.Data(),
                    optLabel.Data(), format.Data()));

  TF1 * fU;
  // if(dataFlag)
  //   fU = new TF1("f_data_accU","TMath::Max(0.,[0]*(1 + [1]*tanh([2]*(x-[3])) + [4]*tanh([5]*(x-[6]) + [7]*(x-[6])**2 + [8]*(x-[6])**3 ) ) )*(1+(x>[10])*[9]*(x-[10])*(x-[10]))",accSignal_cuts::minTimeFit, accSignal_cuts::maxTimeFit);
  // else
    fU = new TF1(Form("f_%s_%s_accU",name.Data(),finalState.Data()),"TMath::Max(0.,[0]*(1 + [1]*tanh([2]*(x-[3])) + [4]*tanh([5]*(x-[6]) + [7]*(x-[6])**2 + [8]*(x-[6])**3 ) ) )*(1+(x>[10])*[9]*(x-[10])*(x-[10]))",accSignal_cuts::minTimeFit, accSignal_cuts::maxTimeFit);

  p0->setVal(1./pdfIntegral->getVal());
  fU->SetParameter(0,p0->getVal());
  fU->SetParameter(1,p1->getVal());
  fU->SetParameter(2,p2->getVal());
  fU->SetParameter(3,p3->getVal());
  fU->SetParameter(4,p4->getVal());
  fU->SetParameter(5,p5->getVal());
  fU->SetParameter(6,p6->getVal());
  fU->SetParameter(7,p7->getVal());
  fU->SetParameter(8,p8->getVal());
  fU->SetParameter(9,p9->getVal());
  fU->SetParameter(10,p10->getVal());
  Double_t funcMax = fU->GetMaximum();
  fU->SetParameter(0,p0->getVal()/funcMax);

  outFile->WriteTObject(fU,"","Overwrite");
  outFile->Close();

  return 0;
}
