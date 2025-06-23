//for execution source envSetup.sh/source $setup_LCG_new/ make norm/ ./runNorm.sh bdpipi Tot 2018 -1.3.-1.3 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "RooNumIntConfig.h"
#include "RooAbsReal.h"
#include "TROOT.h"
#include "TString.h"
#include "RooFit.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooAddPdf.h"
#include "RooGaussModel.h"
#include "RooArgusBG.h"
#include "RooFFTConvPdf.h"
#include "RooWorkspace.h"
#include "RooExponential.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "RooCurve.h"
#include "TPaveText.h"
#include "RooKeysPdf.h"
#include "TAxis.h"
#include "optionParser.h"
#include "sel_RooJohnsonFunc.h"
#include "RooHist.h" //RooHist.h

using namespace std;
using namespace RooFit;

Bool_t cut_bdpipi(Double_t &piplusDLLKPI, Double_t &piplusDLLPPI, 
                  Double_t &piminusDLLKPI, Double_t &piminusDLLPPI, 
                  Int_t &cut1, Int_t &cut2){
  return (piplusDLLKPI < cut1 && piplusDLLPPI < cut2 && 
          piminusDLLKPI < cut1 && piminusDLLPPI < cut2);
}
Bool_t cut_bskk(Double_t &piplusDLLKPI, Double_t &piplusDLLPPI,
                Double_t &piminusDLLKPI, Double_t &piminusDLLPPI,
                Int_t &cut1, Int_t &cut2){
    return (piplusDLLKPI > cut1 && (piplusDLLKPI - piplusDLLPPI) > cut2 && 
            piminusDLLKPI > cut1 && (piminusDLLKPI - piminusDLLPPI) > cut2);
}

Int_t main(Int_t argc, Char_t *argv[]){ 


  TString help = argv[1]; 
  if (help == "-h" || help == "--help")
  {
    printf("Usage of optim:\n");
    printf("  ./optim [options]\n");
    printf("Options:\n");
    printf("  -d <decay>     : name of the decay for which performing the optimisation ([bdpipi,bskk], default = bdpipi)\n");
    printf("  -m <magnet>    : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>      : year of data taking ([2015,2016,2017,2018,201516,20151618,Tot], default = Tot)\n");
    printf("  -c <pidCuts>    : PID requirements, depending on <name>\n");
    printf("  -r <bdkpiFrac> : Contamination from B0->Kpi (default = 0.1)\n");
    return 0;
  }

  TString decay = getOption(argc, argv, "-d", "bdpipi");
  TString magnet = getOption(argc, argv, "-m", "Tot");
  TString year = getOption(argc, argv, "-y", "Tot");
  TString pidCuts;
  if (decay == "bdpipi"){
    pidCuts = "-1.3.-1.3"; //should become -1.3.-1.3
  } else if (decay == "bskk"){
    pidCuts = "2.-2.2.-2";
  } else {
    printf("Name '%s' is not in the list of available decays (['bdpipi', 'bskk'])", decay.Data());
    return 0;
  }
  pidCuts = getOption(argc, argv, "-c", pidCuts.Data());
  Double_t ratio = atof(getOption(argc, argv, "-r", "0.2"));
  TString jobTag = Form("%s_%s_%s_%s", decay.Data(), pidCuts.Data(), magnet.Data(), year.Data());

  printf("EXECUTING ./norm -d %s -m %s -y %s -c %s -r %g\n",
         decay.Data(), magnet.Data(), year.Data(), pidCuts.Data(), ratio);
  RooNumIntConfig &conf = RooNumIntConfig::defaultConfig();
  conf.method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D");
  RooAbsReal::defaultIntegratorConfig()->setEpsAbs(1e-8);
  RooAbsReal::defaultIntegratorConfig()->setEpsRel(1e-8);

  std::cout << "1\n";
  TString configuration = pidCuts;
  Int_t pidPlus1 = atoi(((TObjString *)pidCuts.Tokenize('.')->At(0))->String());
  Int_t pidPlus2 = atoi(((TObjString *)pidCuts.Tokenize('.')->At(1))->String());
  //Int_t pidMinus1 = atoi(((TObjString *)pidCuts.Tokenize('.')->At(2))->String());
  //Int_t pidMinus2 = atoi(((TObjString *)pidCuts.Tokenize('.')->At(3))->String());
  Int_t cut1 = pidPlus1;
  Int_t cut2 = pidPlus2;

  TString massName, massLabel, signalName, finalState, bdtName, bdtCut;
  Double_t meanVal = 0, m0Val = 0, sigmaVal = 0,
           ySig = 0, yBkg = 0, yPhys = 0, alphaVal = 0;

  if (decay == "bdpipi"){
    massName = "massPIPI";
    massLabel = "m_{#pi^{+}#pi^{-}} [GeV/c^{2}]";
    signalName = "B^{0}#rightarrow #pi^{+}#pi^{-}";
    finalState = "pipi";
    bdtName = "PIPI";
    bdtCut = "-1";
    meanVal = 5.2794;
    m0Val = 5.145;
    sigmaVal = 0.023;
    alphaVal = 0.66;
    ySig = 30000;
    yBkg = 1000000;
    yPhys = 30000;
  } else if (decay == "bskk") {
    massName = "massKK";
    massLabel = "m_{K^{+}K^{-}} [GeV/c^{2}]";
    signalName = "B_{s}^{0}#rightarrow K^{+}K^{-}";
    finalState = "kk";
    bdtName = "KK";
    bdtCut = "-1";
    meanVal = 5.3669;
    m0Val = 5.232;
    sigmaVal = 0.023;
    alphaVal = 0.58;
    ySig = 40000;
    yBkg = 50000;
    yPhys = 1000;
  }

  RooRealVar *mass = new RooRealVar("mass", massName, 5, 5.8, "GeV/c^{2}");
  mass->setPlotLabel(massLabel);
  mass->setBins(10000, "cache");
  
  // SIGNAL
  RooRealVar *mean = new RooRealVar("mean", "mean", meanVal);
  RooRealVar *delta = new RooRealVar("delta", "delta", 0.006, -0.01, 0.01);
  RooFormulaVar *mean2 = new RooFormulaVar("mean2", "mean2", "@0+@1", RooArgSet(*mean, *delta));
  RooRealVar *sigma = new RooRealVar("sigma", "sigma", sigmaVal, 0.01, 0.04);
  RooRealVar *alpha1 = new RooRealVar("alpha1", "alpha1", alphaVal);
  RooRealVar *alpha2 = new RooRealVar("alpha2", "alpha2", 0.52);
  RooRealVar *frac = new RooRealVar("frac", "frac", 0.16); //was 0.16 0.16*0.035/0.02*0.55/0.6 = 0.26

  RooGaussian *g = new RooGaussian("g", "g", *mass, *mean2, *sigma);
  sel_RooJohnsonFunc *tail = new sel_RooJohnsonFunc("tail", "tail", *mass, *mean2, *sigma, *alpha1, *alpha2);
  
  RooAddPdf *pdf_sig = new RooAddPdf("pdf_sig", "pdf_sig", RooArgSet(*tail, *g), RooArgSet(*frac));

  RooRealVar *meanS = new RooRealVar("meanS", "meanS", 5.3669);
  RooFormulaVar *mean2S = new RooFormulaVar("mean2S", "mean2S", "@0+@1", RooArgSet(*meanS, *delta));
  RooGaussian *gS = new RooGaussian("gS", "gS", *mass, *mean2S, *sigma);
  sel_RooJohnsonFunc *tailS = new sel_RooJohnsonFunc("tailS", "tailS", *mass, *mean2S, *sigma, *alpha1, *alpha2);
  RooAddPdf *pdf_sigS = new RooAddPdf("pdf_sigS", "pdf_sigS", RooArgSet(*tailS, *gS), RooArgSet(*frac));

  // PHYS
  RooGaussModel *resM = new RooGaussModel("resM", "resM", *mass, *delta, *sigma);
  RooRealVar *m0 = new RooRealVar("m0", "m0", m0Val);
  RooRealVar *cA = new RooRealVar("cA", "cA", -12., -100., 0.);
  RooArgusBG *pdf_phys_tmp = new RooArgusBG("pdf_phys_tmp", "pdf_phys_tmp", *mass, *m0, *cA);
  RooFFTConvPdf *pdf_phys = new RooFFTConvPdf("pdf_phys", "pdf_phys", *mass, *pdf_phys_tmp, *resM);
  pdf_phys->setBufferFraction(0.5);
  
  // CROSS-FEED
  TString cfMassModelName = Form("${B2HH_OUT}/MassModels/CrossFeed/%s_%s_%s_%s_%s_%s.root",finalState.Data(), bdtName.Data(), bdtCut.Data(),configuration.Data(), magnet.Data(), year.Data());
  std::cout << "Crossfeed MassModel is: " << cfMassModelName << std::endl;
  TFile *inFile = new TFile(cfMassModelName,"READ");
  inFile->Print();
  RooWorkspace *myWS_tmp = (RooWorkspace *)inFile->Get(Form("%s_%s_%s_%s",
                                                            finalState.Data(), bdtName.Data(),
                                                            bdtCut.Data(), configuration.Data()));
  RooWorkspace *myWS = (RooWorkspace *)myWS_tmp->Clone();
  delete myWS_tmp;
  inFile->Close();
  RooKeysPdf *pdf_cross_tmp = (RooKeysPdf *)myWS->pdf("bdkpi_" + finalState);
  RooFFTConvPdf *pdf_cross = new RooFFTConvPdf("pdf_cross", "pdf_cross", *mass, *pdf_cross_tmp, *resM);
  pdf_cross->setBufferFraction(0.5);
  pdf_cross->setBufferStrategy(RooFFTConvPdf::Flat);

  // BKG
  RooRealVar *slope = new RooRealVar("slope", "slope", -1, -10, 1);
  RooExponential *pdf_bkg = new RooExponential("pdf_bkg", "pdf_bkg", *mass, *slope);

  // YIELDS
  RooRealVar *n_sig = new RooRealVar("n_sig", "n_sig", ySig, 0, 1000000);
  RooRealVar *n_sigS = new RooRealVar("n_sigS", "n_sigS", 500, 0, 1000000);
  RooRealVar *yRatio = new RooRealVar("yRatio", "yRatio", ratio, 0,1); ////was 0.16 0.16*0.035/0.02*0.55/0.6 = 0.26
  RooFormulaVar *n_cross = new RooFormulaVar("n_cross", "n_cross", "@0*@1", RooArgSet(*n_sig, *yRatio));
  RooRealVar *n_phys = new RooRealVar("n_phys", "n_phys", yPhys, 0, 1000000);
  RooRealVar *n_bkg = new RooRealVar("n_bkg", "n_bkg", yBkg, 0, 10000000);

  RooAddPdf *pdf;
  if (decay == "bdpipi"){
    if (bdtCut.Atof() > -1)
       pdf = new RooAddPdf("pdf", "pdf", RooArgSet(*pdf_sig, *pdf_sigS, *pdf_cross, *pdf_bkg, *pdf_phys),
                          RooArgSet(*n_sig, *n_sigS, *n_cross, *n_bkg, *n_phys));
    else
       pdf = new RooAddPdf("pdf", "pdf", RooArgSet(*pdf_sig, *pdf_cross, *pdf_bkg, *pdf_phys),
                          RooArgSet(*n_sig, *n_cross, *n_bkg, *n_phys));
  } else
      pdf = new RooAddPdf("pdf", "pdf", RooArgSet(*pdf_sig, *pdf_cross, *pdf_bkg, *pdf_phys),
                          RooArgSet(*n_sig, *n_cross, *n_bkg, *n_phys));

  TChain *chain = new TChain("PreSelB2HH");
  map<TString, vector<TString>> tag_years;
  tag_years["2015"] = {"2015"};
  tag_years["2016"] = {"2016"};
  //tag_years["2017"] = {"2017"};
  tag_years["2017"] = {"2017s29r2p2"};
  tag_years["2017s29r2p2"] = {"2017s29r2p2"};
  tag_years["2018"] = {"2018"};
  tag_years["201516"] = {"2015", "2016"};
  tag_years["20151618"] = {"2015", "2016", "2018"};
  //tag_years["Tot"] = {"2015", "2016", "2017", "2018"};
  tag_years["Tot"] = {"201516", "2017s29r2p2", "2018"};

  map<TString, vector<TString>> tag_magnet;
  tag_magnet["Up"] = {"Up"};
  tag_magnet["Down"] = {"Down"};
  tag_magnet["Tot"] = {"Up", "Down"};
  //tag_magnet["Tot"] = {"Up"};
  for (TString tmpYear : tag_years[year]){
    for (TString tmpMagnet : tag_magnet[magnet]){
      chain->Add(Form("${B2HH_OUT}/newBDTtrain/forNorm/bitFix/b2hh_%s_%s.root/b2hh",
                    tmpYear.Data(), tmpMagnet.Data()));
    }
  }

  Double_t piplusDLLKPI = 0, piplusDLLPPI = 0, piminusDLLKPI = 0, piminusDLLPPI = 0;
  Double_t massV = 0;
  chain->SetBranchStatus("*", 0);
  chain->SetBranchStatus("piplusDLLKPI", 1), chain->SetBranchAddress("piplusDLLKPI", &piplusDLLKPI);
  chain->SetBranchStatus("piplusDLLPPI", 1), chain->SetBranchAddress("piplusDLLPPI", &piplusDLLPPI);
  chain->SetBranchStatus("piminusDLLKPI", 1), chain->SetBranchAddress("piminusDLLKPI", &piminusDLLKPI);
  chain->SetBranchStatus("piminusDLLPPI", 1), chain->SetBranchAddress("piminusDLLPPI", &piminusDLLPPI);
  chain->SetBranchStatus(massName, 1), chain->SetBranchAddress(massName, &massV);
  RooDataSet *data = new RooDataSet("data", "data", RooArgSet(*mass));
  RooArgSet obs;
  obs.add(*mass);  
  auto mycut = ((decay == "bskk")? cut_bskk : cut_bdpipi);
  for (Int_t ientry = 0, nentries = chain->GetEntries(); ientry < nentries; ++ientry){
    chain->GetEntry(ientry); 
    if (!mycut(piplusDLLKPI,piplusDLLPPI,
               piminusDLLKPI,piminusDLLPPI,
               cut1,cut2)) continue;
    if (massV < 5.0) continue;
    //if (massV > 5.8) continue;
    if (massV > 6.1) continue;
    mass->setVal(massV);  
    if (pdf->getVal(obs) < 0) continue;
    data->add(obs);
  }
  data->Print("v");

  RooArgSet *params = pdf->getParameters(*mass);
  params->readFromFile(Form("${B2HH_OUT}/newBDTtrain/Norm/params/params_%s.txt", jobTag.Data()));
  RooFitResult *r = pdf->fitTo(*data, Strategy(2), Offset(kTRUE), Extended(),
                              NumCPU(48), PrintLevel(3), Verbose(kTRUE), Save());
  r->Print("v");
  params->writeToFile(Form("${B2HH_OUT}/newBDTtrain/Norm/params/params_%s.txt", jobTag.Data()));

  if (r->edm() < 1e-3 && r->covQual() == 3)
    printf("FIT HAS CONVERGED\n");
   else
    printf("FIT HAS NOT CONVERGED\n");

  RooPlot *plot = mass->frame(5, 6.1, 160);
  plot->SetTitle("");
  plot->GetXaxis()->SetTitleSize(0.05);
  plot->GetXaxis()->SetLabelSize(0.05);
  plot->GetXaxis()->SetTitleOffset(1.1);
  plot->GetXaxis()->SetTitle(massLabel);
  plot->GetXaxis()->SetTickLength(0.05);
  plot->GetXaxis()->SetNdivisions(404, kTRUE);
  plot->GetYaxis()->SetTitleSize(0.04);
  plot->GetYaxis()->SetLabelSize(0.04);
  plot->GetYaxis()->SetTitleOffset(1.9);
  plot->GetYaxis()->SetTickLength(0.05);
  plot->GetYaxis()->SetNdivisions(406, kTRUE);
  //plot->GetYaxis()->SetTitle("Candidates"); // / ( 4 MeV/c^{2})");

  data->plotOn(plot);
  pdf->plotOn(plot, Components("pdf_sig"), Name("signal"), LineColor(kBlack), LineStyle(2), LineWidth(3), FillColor(kWhite));
  pdf->plotOn(plot, Components("pdf_cross"), Name("crossfeed"), LineColor(kBlack), LineWidth(2), LineStyle(0),
              DrawOption("LF2"), FillStyle(3254), FillColor(kBlack));
  pdf->plotOn(plot, Components("pdf_cross"), LineColor(kBlack), LineWidth(2), FillStyle(0));
  pdf->plotOn(plot, Components("pdf_phys"), Name("3body"), LineColor(kBlack), LineWidth(3), LineStyle(9), FillColor(kWhite));
  pdf->plotOn(plot, Components("pdf_bkg"), Name("combinatorial"), LineColor(kBlack), LineWidth(3), LineStyle(5), FillColor(kWhite));
  pdf->plotOn(plot);
  data->plotOn(plot);

  TCanvas *c = new TCanvas("c", "c", 700, 700);
  
  c->cd();
  //TPad *myPad = (TPad *)c->GetPad(0);
  //myPad->SetLeftMargin(0.15);
  //myPad->SetBottomMargin(0.15);
  auto upperPad1 = new TPad("upperPad", "upperPad", .02, .2525, .998, .995);
  auto lowerPad1= new TPad("lowerPad", "lowerPad", .02,  .005, .998, .250);
  upperPad1->SetBottomMargin(0.01);
  upperPad1->SetBorderMode(0);
  lowerPad1->SetTopMargin(0.001);
  lowerPad1->SetBottomMargin(0.45);
  lowerPad1->SetBorderMode(0);
  lowerPad1->SetFillStyle(4000);
  lowerPad1->Draw();
  upperPad1->Draw();
  upperPad1->cd();
  //upperPad1->SetGrid();
  upperPad1->SetTicks();
  //upperPad1->SetLogy();
  plot->Draw();

  TLegend *leg;
  if (decay == "bdpipi")
    //leg = new TLegend(0.55, 0.55, 0.82, 0.75, "");
    leg = new TLegend(0.75, 0.75, 0.9, 0.9, "");
  else
    leg = new TLegend(0.55, 0.5, 0.82, 0.75, "");
  leg->SetName("leg");
  leg->SetTextSize(0.04);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  RooCurve *curv_sig = (RooCurve *)c->FindObject("signal");
  leg->AddEntry(curv_sig, signalName, "f");
  RooCurve *curv_crossfeed = (RooCurve *)c->FindObject("crossfeed");
  leg->AddEntry(curv_crossfeed, "B^{0}#rightarrow K^{+}#pi^{-}", "f");
  RooCurve *curv_3body = (RooCurve *)c->FindObject("3body");
  leg->AddEntry(curv_3body, "3-Body Bkg.", "f");
  RooCurve *curv_bkg = (RooCurve *)c->FindObject("combinatorial");
  leg->AddEntry(curv_bkg, "Comb. bkg.", "f");
  leg->Draw("same");

  TPaveText *lhcb;
  if (decay == "bdpipi")
    lhcb = new TPaveText(0.75, 0.55, 0.9, 0.75, "NDC");
  else
    lhcb = new TPaveText(0.57, 0.75, 0.85, 0.88, "NDC");
  lhcb->AddText("LHCb Preliminary");
  lhcb->SetTextSize(0.05);
  lhcb->SetFillColor(kWhite);
  //lhcb->Draw("same");

  lowerPad1->cd();
  auto hpull1 = plot->pullHist();
  hpull1->SetFillColor(kBlue);
  auto pulls_plot1 = mass->frame(5, 5.8, 160);
  pulls_plot1->addPlotable(hpull1,"BX");
  pulls_plot1->SetTitle(";#it{m} [GeV]; Pulls"); //";#it{m} [GeV/#it{c}^{2}]; Pulls"
  pulls_plot1->GetYaxis()->SetTitleSize(0.10);
  pulls_plot1->GetXaxis()->SetTitleSize(0.15);
  pulls_plot1->GetYaxis()->SetTitleOffset(0.34);
  pulls_plot1->GetYaxis()->SetLabelSize(0.13);
  pulls_plot1->GetXaxis()->SetLabelSize(0.13);
  pulls_plot1->GetXaxis()->SetNoExponent(kTRUE);
  pulls_plot1->GetYaxis()->SetNdivisions(103);
  pulls_plot1->GetXaxis()->SetNdivisions(plot->GetXaxis()->GetNdivisions());
  pulls_plot1->GetYaxis()->SetRangeUser(-6,6);
  //lowerPad1->cd();
  pulls_plot1->Draw("B");

  c->SaveAs(Form("${B2HH_OUT}/newBDTtrain/Norm/plots/%s.pdf",jobTag.Data()));
  TFile *outFile = new TFile(Form("${B2HH_OUT}/newBDTtrain/Norm/%s.root", jobTag.Data()), "RECREATE");
  outFile->WriteTObject(r, "norm", "Overwrite");
  outFile->WriteTObject(c, "c", "Overwrite");
  outFile->Close();

  return 0;
}