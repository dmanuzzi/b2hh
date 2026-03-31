#include <iostream>
#include <fstream>
#include "TROOT.h"
#include "TSystem.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooHistPdf.h"
#include "RooArgSet.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooGaussModel.h"
#include "RooDecay.h"
#include "RooMultiVarGaussian.h"
#include "RooMinuit.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TString.h"
#include "TChain.h"
#include "TPaveText.h"

using namespace RooFit;

Int_t resFit(TString tag, vector<TString> nfins){

  gSystem->Load("libRooFit.so");

  gROOT->SetStyle("Plain");
  bool isMC = tag.Contains("MC");
  bool isBs2KK = tag.Contains("bskk");
  /*
  TString PTcut = "Jpsi_PT>0";
  if      (tag.Contains("notVeryLowPT")) PTcut = "Jpsi_PT>1500";
  else if (tag.Contains("VeryLowPT"))    PTcut = "Jpsi_PT>0 && Jpsi_PT<1500";
  else if (tag.Contains("LowPT"))        PTcut = "Jpsi_PT>1500 && Jpsi_PT<5000";
  else if (tag.Contains("MediumPT"))     PTcut = "Jpsi_PT>5000 && Jpsi_PT<7000";
  else if (tag.Contains("HighPT"))       PTcut = "Jpsi_PT>7000";
  //RooRealVar * Jpsi_PT = new RooRealVar("Jpsi_PT","Jpsi_PT",0,100e3);
  */
/*
  RooNumIntConfig &conf=RooNumIntConfig::defaultConfig();
  conf.method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D");
  RooAbsReal::defaultIntegratorConfig()->setEpsAbs(1e-8) ;
  RooAbsReal::defaultIntegratorConfig()->setEpsRel(1e-8) ;
  RooAbsReal::defaultIntegratorConfig()->Print("v");
*/
  Double_t deltaTauMin = -0.5;
  Double_t deltaTauMax = +0.5;
  Double_t timeErrMin  = +0.01;
  Double_t timeErrMax  = +0.10;
  if (tag.Contains("Y1S")) {
    deltaTauMin = -0.3;
    deltaTauMax = +0.3;
    timeErrMax = 0.1;
  };
  Int_t nbins = (deltaTauMax - deltaTauMin)/0.0025;

  RooRealVar * deltaTau = new RooRealVar("deltaTau","deltaTau",deltaTauMin, deltaTauMax);
  RooRealVar * timeErr  = new RooRealVar("timeErr","timeErr", timeErrMin, timeErrMax);
  RooRealVar * w        = new RooRealVar("sWeight", "sWeight", -1e7, 1e7);
  RooArgSet * obs = new RooArgSet();
  obs->add(*deltaTau); obs->add(*timeErr); obs->add(*w);

  //deltaTau->setBins(nbins);
  timeErr->setBins(nbins);
  
  TChain * chain = new TChain(tag,tag);
  for (auto nfin : nfins){
    printf("%s\n",nfin.Data());
    chain->Add(nfin);  
  }
  
  RooAbsData::setDefaultStorageType(RooAbsData::Tree);
  //RooDataSet * data = new RooDataSet("data","data",RooArgSet(*deltaTau, *timeErr),Import(*chain));
  RooDataSet * data = new RooDataSet("data","data",RooArgSet(*deltaTau, *timeErr, *w),Import(*chain));// WeightVar(*w));
  //RooDataSet * data = new RooDataSet("data","data",RooArgSet(*deltaTau, *timeErr, /* *Jpsi_PT,*/ *w),Import(*chain), WeightVar(*w) /*, Cut(PTcut)*/);
  //RooDataSet * data = (RooDataSet *) datatmp->reduce(EventRange(0,500000));

  data->Print("v");
  
  RooDataHist * histErr = new RooDataHist("histErr","histErr", *timeErr, *data);
  RooHistPdf  * errPdf  = new RooHistPdf("errPdf"  ,"errPdf" , *timeErr, *histErr);

  RooAbsReal * mean1 = nullptr;
  RooRealVar * mm0 = new RooRealVar("mm0","mm0",-0.00378, -10, 10);
  RooRealVar * mm1 = new RooRealVar("mm1","mm1",-0.06102, -10, 10);
  RooRealVar * mm2 = new RooRealVar("mm2","mm2", 3.60097, -10, 10);
  if (isMC)  mean1 = new RooRealVar("mean1","mean1",0.0, -0.1, 0.1);
  else       mean1 = new RooFormulaVar("mean1", "mean1", "@1+@2*(@0-0.04)+@3*(@0-0.04)**2", RooArgSet(*timeErr, *mm0,*mm1,*mm2));
  RooRealVar * mean2 = new RooRealVar("mean2","mean2",0,-0.1,0.1);
  RooRealVar * mean3 = new RooRealVar("mean3","mean3",0,-0.1,0.1);
  RooRealVar * p0 = new RooRealVar("p0","p0",0.03,-5,5);
  RooRealVar * p1 = new RooRealVar("p1","p1",0.9,-5,5);
  RooRealVar * p2 = new RooRealVar("p2","p2",-0.1, -10,10);
  RooRealVar * p3 = new RooRealVar("p3","p3",-0.1, -100,100);
  RooRealVar * p4 = new RooRealVar("p4","p4",-0.1, -100,100);
  RooFormulaVar * sigmaT1 = nullptr;
  if (tag.Contains("pol2")) 
    sigmaT1 = new RooFormulaVar("sigmaT1","sigmaT1","@1+@2*(@0-0.04)+@3*(@0-0.04)**2", RooArgSet(*timeErr,*p0,*p1, *p2));
  else if (tag.Contains("pol3")) 
    sigmaT1 = new RooFormulaVar("sigmaT1","sigmaT1","@1+@2*(@0-0.04)+@3*(@0-0.04)**2+@4*(@0-0.04)**3", RooArgSet(*timeErr,*p0,*p1,*p2,*p3));
  else if (tag.Contains("pol4")) 
    sigmaT1 = new RooFormulaVar("sigmaT1","sigmaT1","@1+@2*(@0-0.04)+@3*(@0-0.04)**2+@4*(@0-0.04)**3+@5*(@0-0.04)**4", RooArgSet(*timeErr,*p0,*p1,*p2,*p3,*p4));
  else 
    sigmaT1 = new RooFormulaVar("sigmaT1","sigmaT1","@1+@2*(@0-0.04)",RooArgSet(*timeErr,*p0,*p1));
  
  
  RooRealVar * q0 = new RooRealVar("q0","q0",1.5,0.001,10);
  RooRealVar * q1 = new RooRealVar("q1","q1",1,0,5);
  //RooFormulaVar * sigmaT2 = new RooFormulaVar("sigmaT2","sigmaT2","@3*(@1+@2*(@0-0.03))",RooArgSet(*timeErr,*p0,*p1,*q0));
  RooFormulaVar * sigmaT2 = new RooFormulaVar("sigmaT2","sigmaT2","@0*@1",RooArgSet(*q0, *sigmaT1));
  RooRealVar * sigma3 = new RooRealVar("sigma3","sigma3",0.1, 0.01, 1);

  RooRealVar * t0 = new RooRealVar("t0","t0",1,-10,10);
  RooRealVar * t1 = new RooRealVar("t1","t1",0.1, -5 , 5);
  RooFormulaVar * frac = new RooFormulaVar("frac","frac","@1+@2*(@0-0.04)",RooArgSet(*timeErr,*t0,*t1));
  RooRealVar *f1  = new RooRealVar("f1","f1",0.8, 0.,1);
  RooRealVar *f3  = new RooRealVar("f3","f3",0.5, 0,1);
  
  RooGaussian * g1 = new RooGaussian("g1","g1",*deltaTau,*mean1,*sigmaT1);
  RooGaussian * g2 = new RooGaussian("g2","g2",*deltaTau,*mean1,*sigmaT2);
  RooGaussian * g3 = new RooGaussian("g3","g3",*deltaTau,*mean1,*sigma3);
  RooAddPdf * g12 = nullptr;
  if (isMC){  
    g12 = new RooAddPdf("g12","g12",RooArgSet(*g1,*g2),RooArgSet(*f1));
  }  else
    g12 = new RooAddPdf("g12","g12",RooArgSet(*g1,*g2),RooArgSet(*frac));

  RooRealVar    *sigmaFly    = new RooRealVar("sigmaFly","sigmaFly",0.1,0.01,5.); 
  RooGaussModel *gaussFly    = new RooGaussModel("gaussfly","gaussfly", *deltaTau,*mean1,*sigmaT1);
  RooRealVar    *tauFly      = new RooRealVar("tauFly","lifetime",1.54, 0, 5);
  RooDecay      *pdfFly      = new RooDecay("model","decay (x) gauss",*deltaTau,*tauFly,*gaussFly,  RooDecay::DecayType::SingleSided);
  RooRealVar    *fFly        = new RooRealVar("fFly","fFly",0.1, 0,1);
  
  RooRealVar    *Nsig        = new RooRealVar("Nsig", "Nsig", 5e5, 0, 1e8);
  RooRealVar    *Nbkg        = new RooRealVar("Nbkg", "Nbkg", 5e3, 0, 1e8);
  RooRealVar    *fracS       = new RooRealVar("fracS","fracS", 0.99,0,1);
  
  RooAbsPdf * pdf  = nullptr;
  RooProdPdf * pdfs = nullptr;
  RooProdPdf * pdfb = nullptr;
  if (isMC){
    if (isBs2KK) pdf = new RooProdPdf("pdf","pdf",*errPdf,Conditional(*g12,*deltaTau));
    else         pdf = new RooProdPdf("pdf","pdf",*errPdf,Conditional(*g1 ,*deltaTau));
  } else {
    pdf = new RooProdPdf("pdf","pdf",*errPdf,Conditional(*g1,*deltaTau));
    // pdfs = new RooProdPdf("pdfs","pdfs",*errPdf,Conditional(*g1,*deltaTau));
    // pdfb = new RooProdPdf("pdfb","pdfb",*errPdf,Conditional(*pdfFly,*deltaTau));
    // pdf  = new RooAddPdf("pdf", "pdf", RooArgSet(*pdfs, *pdfb), RooArgSet(*fracS));
  }
  
  
  RooArgSet * params = pdf->getParameters(RooArgSet(*deltaTau,*timeErr));
  
  params->readFromFile("params/paramsRes_"+tag+".txt");
  
  RooDataSet * dataNew = new RooDataSet("dataNew","dataNew",*obs);
  for(Int_t i = 0; i < data->numEntries(); ++i) {
    obs->assignFast(*(data->get(i)));
    //printf("DATA %g:%g|%g\n",deltaTau->getVal(),timeErr->getVal(),w->getVal());
    Double_t val = pdf->getVal(RooArgSet(*deltaTau,*timeErr));
    if(val <= 0) {
      printf("ERROR %g\n",val);
      obs->Print("v");
    }
    else {
      dataNew->add(*obs);
      //if(!(i%100000)) printf("DATA %g:%g|%g\n",deltaTau->getVal(),timeErr->getVal(),w->getVal());
    }
  }

  RooDataSet * dataFinal = new RooDataSet("dataFinal","dataFinal",*obs,Import(*dataNew),WeightVar(*w));  
  
  RooFitResult *r1 = nullptr, *r2=nullptr, *r3=nullptr;
  r1 = pdf->fitTo(*dataFinal, Offset(),  Verbose(kTRUE), PrintLevel(3), Strategy(2), Save(), NumCPU(12), SumW2Error(!isMC));
  // RooAbsReal *nll = pdf->createNLL(*dataFinal, Offset(),  Verbose(kTRUE), PrintLevel(3), Strategy(2), Save(), NumCPU(12), SumW2Error(!isMC));
  // RooMinuit m(*nll);
  // m.printLevel(3);
  // m.migrad();
  // r1 = m.save();
  // m.hesse();
  // r2 = m.save();
  // m.minos();
  // r3 = m.save();
  r1->Print("v");
  // r2->Print("v");
  // r3->Print("v");
  RooMultiVarGaussian *hesse = (RooMultiVarGaussian*)r1->createHessePdf(*(pdf->getParameters(RooArgSet(*deltaTau,*timeErr))));
  RooArgSet *finalPars = hesse->getParameters(*(pdf->getParameters(RooArgSet(*deltaTau,*timeErr))));
  finalPars->writeToStream(cout, false);
  hesse->covarianceMatrix().Print();
  // for (auto finalPar = finalPars->begin(); finalPar != finalPars->end(); ++finalPar){
  //   finalPar->Print("v");
  // }
  //return 0;
  params->writeToFile("params/paramsRes_"+tag+".txt");
  ofstream outStream("results/results_"+tag+".txt", ios_base::out);
  outStream << "******** "+tag+" ********\n";
  r1->printMultiline(outStream, 20, kTRUE);
  outStream.close();
  
  TCanvas * c[100];
  RooPlot * plot[100];
  RooHist * hpull[100];
  RooPlot * pulls[100];
  TPad*    upperPad[100];
  TPad*    lowerPad[100];

  TFile * outFile = new TFile("plots/resFit_"+tag+".root","RECREATE");
  
  Int_t bin=0;
  Double_t rangeMin = timeErrMin;
  Double_t rangeMax = timeErrMin+0.005;
  while (rangeMax<timeErrMax+0.001){
    printf("********* BIN %d, timeErr in [%.3f, %.3f] ps\n", bin, rangeMin, rangeMax);
    c[bin] = new TCanvas(Form("c_%d",bin),Form("c_%d",bin),700,725,700,725);
    c[bin]->cd();
    upperPad[bin] = new TPad(Form("upperPad_%d",bin),Form("upperPad_%d",bin),0,0.2,1,1);
    upperPad[bin]->SetLeftMargin(0.15); upperPad[bin]->SetBottomMargin(0.15);
    lowerPad[bin] = new TPad(Form("lowerPad_%d",bin),Form("lowerPad_%d",bin),0,0,1,0.2);
    lowerPad[bin]->SetLeftMargin(0.15);
    lowerPad[bin]->Draw();
    upperPad[bin]->Draw();

    plot[bin] = new RooPlot(Form("plot_%d",bin),Form("plot_%d",bin),*deltaTau,deltaTauMin, deltaTauMax, nbins);
    plot[bin]->SetTitle("");
    plot[bin]->GetXaxis()->SetTitleSize(0.05);  plot[bin]->GetXaxis()->SetLabelSize(0.05);
    plot[bin]->GetXaxis()->SetTitleOffset(1.1); plot[bin]->GetXaxis()->SetTitle("#tau-#tau_{MC} (ps)");
    plot[bin]->GetXaxis()->SetTickLength(0.05); plot[bin]->GetXaxis()->SetNdivisions(404,kTRUE);
    plot[bin]->GetYaxis()->SetTitleSize(0.05);  plot[bin]->GetYaxis()->SetLabelSize(0.05);
    plot[bin]->GetYaxis()->SetTitleOffset(1.5);
    plot[bin]->GetYaxis()->SetTickLength(0.05); plot[bin]->GetYaxis()->SetNdivisions(406,kTRUE);

    timeErr->setRange(Form("range_%d",bin),rangeMin,rangeMax);
    data->plotOn(plot[bin],CutRange(Form("range_%d",bin)));
    if (!isMC){
      pdf->plotOn(plot[bin],Components(*pdfFly),LineColor(kBlack),LineStyle(kDashed),
                            ProjectionRange(Form("range_%d",bin)));
    }
    pdf->plotOn(plot[bin],Components(*g1),LineColor(kGreen+2),LineStyle(kDashed),
                          ProjectionRange(Form("range_%d",bin)));
  
    pdf->plotOn(plot[bin],ProjectionRange(Form("range_%d",bin)));
    hpull[bin] = plot[bin]->pullHist();
    hpull[bin]->SetFillColor(kBlue);
    pulls[bin] = new RooPlot(Form("pull_%d",bin),Form("pull_%d",bin),*deltaTau,deltaTauMin, deltaTauMax, nbins);
    pulls[bin]->SetTitle("");
    pulls[bin]->addPlotable(hpull[bin],"BX") ;
    pulls[bin]->GetXaxis()->SetTitleSize(0);     pulls[bin]->GetXaxis()->SetLabelSize(0);
    pulls[bin]->GetXaxis()->SetTickLength(0.15); pulls[bin]->GetXaxis()->SetNdivisions(404,kTRUE);
    pulls[bin]->GetYaxis()->SetTitleSize(0.15);  pulls[bin]->GetYaxis()->SetLabelSize(0.15);
    pulls[bin]->GetYaxis()->SetTitleOffset(0.2); pulls[bin]->GetYaxis()->SetTitle("pull");
    pulls[bin]->GetYaxis()->SetRangeUser(-5,5);
    pulls[bin]->GetYaxis()->SetTickLength(0.05); pulls[bin]->GetYaxis()->SetNdivisions(502,kTRUE);

    TPaveText* binBox = new TPaveText(upperPad[bin]->GetLeftMargin() + 0.06,
                                    0.85 - upperPad[bin]->GetTopMargin(),
                                    upperPad[bin]->GetLeftMargin() + 0.20,
                                    0.95 - upperPad[bin]->GetTopMargin(),
                                    "BRNDC");
    binBox->SetFillColor(0);
    binBox->SetTextAlign(12);
    binBox->SetBorderSize(0);
    binBox->SetTextFont(132);
    binBox->SetTextColor(1);
    binBox->SetTextSize(0.04);
    binBox->SetTextAlign(12);
    binBox->AddText(Form("#delta_{t} #in [%.3f, %.3f] ps", rangeMin, rangeMax));
    upperPad[bin]->cd();
    plot[bin]->Draw();
    binBox->Draw("same");
    lowerPad[bin]->cd();
    pulls[bin]->Draw("B");
    c[bin]->SaveAs(Form("plots/resFit_%s_bin%d.pdf", tag.Data(), bin));
    outFile->WriteTObject(c[bin],"","Overwrite");
    rangeMin = rangeMax;
    rangeMax+= 0.005;
    bin+=1; 
    if (bin>99) break;
  }
  
  TCanvas * cTot = new TCanvas("cTot","cTot",700,725,700,725);
  cTot->cd();
  TPad * upperPadTot = new TPad("upperPadTot","upperPadTot",0,0.2,1,1);
  upperPadTot->SetLeftMargin(0.15); upperPadTot->SetBottomMargin(0.15);
  TPad * lowerPadTot = new TPad("lowerPadTot","lowerPadTot",0,0,1,0.2);
  lowerPadTot->SetLeftMargin(0.15);
  lowerPadTot->Draw();
  upperPadTot->Draw();
  RooPlot * plotTot = new RooPlot("plotTot","plotTot",*deltaTau, deltaTauMin, deltaTauMax, nbins);
  plotTot->SetTitle("");
  plotTot->GetXaxis()->SetTitleSize(0.05);  plotTot->GetXaxis()->SetLabelSize(0.05);
  plotTot->GetXaxis()->SetTitleOffset(1.1); plotTot->GetXaxis()->SetTitle("#tau-#tau_{MC} (ps)");
  plotTot->GetXaxis()->SetTickLength(0.05); plotTot->GetXaxis()->SetNdivisions(404,kTRUE);
  plotTot->GetYaxis()->SetTitleSize(0.05);  plotTot->GetYaxis()->SetLabelSize(0.05);
  plotTot->GetYaxis()->SetTitleOffset(1.5);
  plotTot->GetYaxis()->SetTickLength(0.05); plotTot->GetYaxis()->SetNdivisions(406,kTRUE);
  dataFinal->plotOn(plotTot);
  pdf->plotOn(plotTot,Components(*g1),LineColor(kGreen+2),LineStyle(kDashed));    
  if (isMC && isBs2KK) pdf->plotOn(plotTot,Components(*g2),LineColor(kCyan+2),LineStyle(kDashed));    
  if (!isMC){
    pdf->plotOn(plotTot,Components(*pdfFly),LineColor(kBlack),LineStyle(kDashed));
  }
  pdf->plotOn(plotTot);
  plotTot->SetMinimum(0.1);
  RooHist * hpullTot = plotTot->pullHist();
  hpullTot->SetFillColor(kBlue);
  RooPlot * pullsTot  = new RooPlot("pullTot","pullTot",*deltaTau, deltaTauMin, deltaTauMax, nbins);
  pullsTot->SetTitle("");
  pullsTot->addPlotable(hpullTot,"BX") ;
  pullsTot->GetXaxis()->SetTitleSize(0);     pullsTot->GetXaxis()->SetLabelSize(0);
  pullsTot->GetXaxis()->SetTickLength(0.15); pullsTot->GetXaxis()->SetNdivisions(404,kTRUE);
  pullsTot->GetYaxis()->SetTitleSize(0.15);  pullsTot->GetYaxis()->SetLabelSize(0.15);
  pullsTot->GetYaxis()->SetTitleOffset(0.2); pullsTot->GetYaxis()->SetTitle("pull");
  pullsTot->GetYaxis()->SetRangeUser(-5,5);
  pullsTot->GetYaxis()->SetTickLength(0.05); pullsTot->GetYaxis()->SetNdivisions(502,kTRUE);

  upperPadTot->cd();
  plotTot->Draw();
  lowerPadTot->cd();
  pullsTot->Draw("B");

  outFile->WriteTObject(cTot,"","Overwrite");
  cTot->SaveAs("plots/resFit_"+tag+".pdf");
  upperPadTot->SetLogy();
  cTot->SaveAs("plots/resFit_"+tag+"_log.pdf");
  outFile->ls();
  outFile->Close();
  printf("**** Fitted candidates: %g\n", dataFinal->sumEntries());
  printf("STOCAZZO\n");

  return 1;
}
