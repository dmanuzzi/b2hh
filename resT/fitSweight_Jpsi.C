#include <iostream>
#include <fstream>
#include "TString.h"
#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TAxis.h"
#include <vector>
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooStats/SPlot.h"
#include "RooPlot.h"
#include "RooCBShape.h"
#include "RooGExpModel.h"
#include "RooFFTConvPdf.h"
#include "RooFitResult.h"
#include "RooChebychev.h"
#include "RooFormulaVar.h"
using namespace std;
using namespace RooFit;
int fitSweight_Jpsi(TString tag, vector<TString> nfins){

  Bool_t isMC = tag.Contains("MC");
  Double_t massMin=2990;
  Double_t massMax=3200;
  RooRealVar *x = new RooRealVar("Jpsi_MM", "Jpsi_MM", massMin, massMax, "MeV");
  RooRealVar *tau = new RooRealVar("Jpsi_TAU", "Jpsi_TAU", -1e-3, 1e-3, "ns");
  RooRealVar *tauE= new RooRealVar("Jpsi_TAUERR", "Jpsi_TAUERR", 0.01e-3, 0.1e-3, "ns");
  int Nbins=210;
  x->setBins(Nbins);
  tau->setBins(Nbins);
  tauE->setBins(Nbins);
  printf("Data import: start\n");
  TChain * chainIN = new TChain("input_"+tag);
  for (auto nfin : nfins){
    chainIN->Add(nfin+"/ntp");
  }
  printf("Data import: end %lld\n", chainIN->GetEntries());
  TTree * chainSEL = (TTree*)chainIN->CloneTree(0);
  UInt_t runNumber = 0; chainIN->SetBranchAddress("runNumber", &runNumber);
  for (Int_t i=0, nentries = chainIN->GetEntries(); i<nentries; ++i){
    chainIN->GetEntry(i);
    if (runNumber>210300 && tag.Contains("lowRun")) continue;
    if (runNumber<210300 && tag.Contains("highRun")) continue;
    chainSEL->Fill();
  }
  printf("Data import: end %lld\n", chainSEL->GetEntries());
  
  printf("Dataset building: start\n");
  RooAbsData::setDefaultStorageType(RooAbsData::Tree);
  RooDataSet *data = new RooDataSet("data","data",RooArgSet(*x, *tau, *tauE),Import(*chainSEL));
  data->convertToTreeStore();
  data->Print("v");
  printf("Dataset building: end\n");
  ////////////////////////////////////
  ////////////////////////////////////
  RooRealVar  *m12   = new RooRealVar("mean", "mean", 3097, 3097-100, 3097+100);
  RooRealVar  *s11   = new RooRealVar("sigma", "sigma",20, 0, 100);
  RooRealVar  *fs12  = new RooRealVar("fsigma21", "sigma2/sigma1",1, 0, 100);
  RooRealVar  *fs13  = new RooRealVar("fsigma31", "sigma3/sigma1",1, 0, 100);  
  RooFormulaVar  *s12   = new RooFormulaVar("s12", "sigma2", "@0*@1", RooArgSet(*s11, *fs12));
  RooFormulaVar  *s13   = new RooFormulaVar("s13", "sigma3", "@0*@1", RooArgSet(*s11, *fs13));
  
  RooRealVar  *s14   = new RooRealVar("s14", "sigma14",30, 0, 100);  
  RooRealVar  *alpha1= new RooRealVar("alpha1", "alpha1", 0.9, -100, 100); 
  RooRealVar  *alpha2= new RooRealVar("alpha2", "alpha2", 1.3, -100, 100); 
  RooRealVar  *alpha3= new RooRealVar("alpha3", "alpha3", 4.04, -100, 100); 
  RooRealVar  *n1    = new RooRealVar("n1", "n1", 1.0, -300, 300);
  RooRealVar  *n2    = new RooRealVar("n2", "n2", 100, -300, 300);
  RooRealVar  *n3    = new RooRealVar("n3", "n3", 5, -300, 300);
  RooRealVar  *f1    = new RooRealVar("f1", "f1", 0.14, 0, 1);
  RooRealVar  *f2    = new RooRealVar("f2", "f2", 0.85, 0, 1);
  RooRealVar  *f3    = new RooRealVar("f3", "f3", 0.10, 0, 1);
  
  RooCBShape  *cball1= new RooCBShape("cball1", "cball1", *x, *m12, *s11, *alpha1, *n1);
  RooCBShape  *cball2= new RooCBShape("cball2", "cball2", *x, *m12, *s12, *alpha2, *n1);
  RooCBShape  *cball3= new RooCBShape("cball3", "cball3", *x, *m12, *s13, *alpha1, *n1);
  RooCBShape  *cball4= new RooCBShape("cball4", "cball4", *x, *m12, *s14, *alpha1, *n1);
  RooGaussian *gauss2= new RooGaussian("gauss2","gauss2", *x, *m12, *s12);
  
  RooAddPdf   *modelSIG = new RooAddPdf("modelSIG", "modelSIG", RooArgSet(*cball1, *gauss2, *cball3), RooArgSet(*f1, *f2));
  //RooAddPdf   *modelSIG = new RooAddPdf("modelSIG", "modelSIG", RooArgSet(*cball1, *cball2, *cball3), RooArgSet(*f1, *f2));
  //RooAddPdf   *modelSIG = new RooAddPdf("modelSIG", "modelSIG", RooArgSet(*cball1, *cball2), RooArgSet(*f1));
  
  RooRealVar  *mBKG    = new RooRealVar("mBKG", "meanBKG", 3097, 3097-100, 3097+100);
  RooRealVar  *sBKG    = new RooRealVar("sBKG", "sigmaBKG", 50, 0, 100);
  RooGaussian *gausBKG = new RooGaussian("gausBKG", "gausBKG", *x, *mBKG, *sBKG);
  
  RooRealVar  *p0BKG    = new RooRealVar("p0BKG", "p0BKG", 0.05, -1e7, 1e7);
  RooRealVar  *p1BKG    = new RooRealVar("p1BKG", "p1BKG",-0.80, -1e7, 1e7);
  RooRealVar  *p2BKG    = new RooRealVar("p2BKG", "p2BKG", 0, -1e7, 1e7);
  RooChebychev *polBKG  = new RooChebychev("polBKG", "polBKG", *x, RooArgList(*p0BKG,*p1BKG/*, *p2BKG*/));

  RooRealVar  *lBKG     = new RooRealVar("lBKG", "lBKG", -0.01, -1e7, 1e7);
  RooExponential *expBKG= new RooExponential("expBKG", "expBKG", *x, *lBKG);

  RooRealVar  *fBKG     = new RooRealVar("fBKG", "fBKG", 1);

  RooAbsPdf   *modelBKG = nullptr;
  if (!isMC && tag.Contains("gausBKG"))
    modelBKG = gausBKG;
  if (!isMC && tag.Contains("polBKG"))
    modelBKG = polBKG;
  if (!isMC && tag.Contains("expBKG"))
    modelBKG = expBKG;
  
  RooRealVar  *Nsig  = new RooRealVar("Nsig", "N of signal events", 10000, 0, 1e7);
  RooRealVar  *Nbkg   = new RooRealVar("Nbkg", "N of background events", 10000, 0, 1e7);
  
  RooAddPdf  *model = nullptr;
  if (isMC){
    model = new RooAddPdf("model", "model", RooArgSet(*modelSIG), RooArgSet(*Nsig));
  } else {
    model = new RooAddPdf("model", "model", RooArgSet(*modelSIG,*modelBKG), RooArgSet(*Nsig,*Nbkg));
  }
  ////////////////////////////////////
  ////////////////////////////////////
  RooArgSet * params = model->getParameters(RooArgSet(*x));
  if (isMC) params->readFromFile("params/params_"+tag+".txt");
  else      params->readFromFile("params/params_"+tag+".txt");
  //else      params->readFromFile("params/params_Jpsi_MC_2016.txt");
  TFile *fout = new TFile("plots/"+tag+".root","RECREATE");
  
  RooFitResult *results = nullptr;
  if (isMC)  
    results = modelSIG->fitTo(*data, NumCPU(12), Offset(), Save(kTRUE), Verbose(kTRUE), PrintLevel(3));
  else
    results = model->fitTo(*data, NumCPU(12), Extended(), Offset(), Save(kTRUE), Verbose(kTRUE), PrintLevel(3));
  
  results->Print("v");
  params->writeToFile("params/params_"+tag+".txt");
  ofstream outStream("results/results_"+tag+".txt", ios_base::out);
  outStream << "******** "+tag+" ********\n";
  results->printMultiline(outStream, 20, kTRUE);
  outStream.close();
  

  x->setBins(Nbins);
  TCanvas *cdata = new TCanvas("data", "data",700,725);
  cdata->cd();
  TPad * upperPadTot = new TPad("upperPadTot","upperPadTot",0,0.2,1,1);
  upperPadTot->SetLeftMargin(0.15); upperPadTot->SetBottomMargin(0.15);
  TPad * lowerPadTot = new TPad("lowerPadTot","lowerPadTot",0,0,1,0.2);
  lowerPadTot->SetLeftMargin(0.15);
  lowerPadTot->Draw();
  upperPadTot->Draw();
  RooPlot* frame = x->frame(Name("sPlot_"+tag));
  frame->SetTitle(Form("sPlot for %s\n",tag.Data()));
  frame->GetXaxis()->SetTitleSize(0.05);  frame->GetXaxis()->SetLabelSize(0.05);
  frame->GetXaxis()->SetTitleOffset(1.1); frame->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) [MeV]");
  frame->GetXaxis()->SetTickLength(0.05); frame->GetXaxis()->SetNdivisions(404,kTRUE);
  frame->GetYaxis()->SetTitleSize(0.05);  frame->GetYaxis()->SetLabelSize(0.05);
  frame->GetYaxis()->SetTitleOffset(1.5);
  frame->GetYaxis()->SetTickLength(0.05); frame->GetYaxis()->SetNdivisions(406,kTRUE);
  data ->plotOn(frame);
  model->plotOn(frame, Components(*cball1), LineColor(kRed),  LineStyle(kDashed));
  //model->plotOn(frame, Components(*cball2), LineColor(kMagenta), LineStyle(kDashed));
  model->plotOn(frame, Components(*gauss2), LineColor(kMagenta), LineStyle(kDashed));
  model->plotOn(frame, Components(*cball3), LineColor(kCyan+2), LineStyle(kDashed));
  model->plotOn(frame, Components(*modelSIG), LineColor(kGreen+2));
  if (!isMC){
    model->plotOn(frame, Components(*modelBKG), LineColor(kBlack));
  }
  model->plotOn(frame, LineColor(kBlue));
  RooHist * hpullTot = frame->pullHist();
  hpullTot->SetFillColor(kBlue);
  RooPlot * pulls  = x->frame(Name("pulls_"+tag));
  pulls->SetTitle("");
  pulls->addPlotable(hpullTot,"BX") ;
  pulls->GetXaxis()->SetTitleSize(0);     pulls->GetXaxis()->SetLabelSize(0);
  pulls->GetXaxis()->SetTickLength(0.15); 
  pulls->GetYaxis()->SetTitleSize(0.15);  pulls->GetYaxis()->SetLabelSize(0.15);
  pulls->GetYaxis()->SetTitleOffset(0.2); pulls->GetYaxis()->SetTitle("pull");
  pulls->GetYaxis()->SetRangeUser(-5,5);
  pulls->GetYaxis()->SetTickLength(0.05); 
  upperPadTot->cd();
  frame->GetYaxis()->SetRangeUser(1., frame->GetMaximum());
  frame->Draw();
  lowerPadTot->cd();
  pulls->Draw("B");
  cdata->SaveAs(Form("plots/%s_%s.pdf", cdata->GetName(), tag.Data()));
  upperPadTot->SetLogy();
  cdata->Update();
  cdata->SaveAs(Form("plots/%s_%s_log.pdf", cdata->GetName(), tag.Data()));
  fout->WriteTObject(cdata, cdata->GetName(), "Overwrite");

   
  RooStats::SPlot *splot = nullptr;
  const TTree *outTree = nullptr;
  RooDataSet *sdata1 = nullptr;
  TCanvas *cTau = nullptr;
  TCanvas *cTauE = nullptr;
  RooPlot *frame2 = nullptr;
  RooPlot *frame3 = nullptr;
  
  if (!isMC){
    splot = new RooStats::SPlot("splot", "splot", *data, model, RooArgSet(*Nsig, *Nbkg));
    splot->Print("v");
    data->Print("v");
    printf("exporting output TTree: start\n");
    outTree = data->tree();
    fout->WriteTObject(outTree, outTree->GetName(), "Overwrite");
    printf("exporting output TTree: done\n");


    sdata1 = new RooDataSet("ntp", "ntp", data,*(data->get()), 0, "Nsig_sw");
    cTau = new TCanvas("cTau", "cTau");
    cTau->cd();
    frame2 = tau->frame();
    data  ->plotOn(frame2,  DataError(RooAbsData::SumW2), MarkerColor(kBlack));
    sdata1->plotOn(frame2,  DataError(RooAbsData::SumW2), MarkerColor(kGreen+2));
    frame2->Draw();
    cTau ->SaveAs(Form("plots/%s_%s.pdf", cTau ->GetName(), tag.Data()));
    fout->WriteTObject(cTau , cTau->GetName(),  "Overwrite");

    cTauE = new TCanvas("cTauErr", "cTauErr");
    cTauE->cd();
    frame3 = tauE->frame();
    data  ->plotOn(frame3,  DataError(RooAbsData::SumW2), MarkerColor(kBlack));
    sdata1->plotOn(frame3,  DataError(RooAbsData::SumW2), MarkerColor(kGreen+2));
    frame3->Draw();
    cTauE->SaveAs(Form("plots/%s_%s.pdf", cTauE->GetName(), tag.Data()));
    fout->WriteTObject(cTauE, cTauE->GetName(), "Overwrite");
  }
  
  fout->ls();
  fout->Close();
  printf("Fit entries: %g\n", data->sumEntries());
  return 1;
}
