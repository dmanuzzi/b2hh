
//old norm does not want to be compiled :rage:
//only issue with the johnson tails -> We'll see down the line

//normalisation -> take the 3 b2hh files at cut bdtPIPI > 0 
// create the chain / fit the total model (signal: gaussian+johnson (cannot use the usual johnson tail), crossfeeed from massModels, comb bkg: exponential, 3 body: argus)
//simplified ->Only Bd to pipi and B0 crossfeed as Kpi



#include <iostream>
#include <vector>
#include <map>

#include "TFile.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooKeysPdf.h"
#include "RooFFTConvPdf.h"
#include "RooArgusBG.h"
#include "RooFormulaVar.h"
#include "RooWorkspace.h"
#include "RooGaussModel.h"
#include "RooArgSet.h"
#include "RooCurve.h"
#include "RooFit.h"
#include "TAxis.h"
#include "RooFitResult.h"
#include "RooHist.h"
#include "TObject.h"
#include "TSystem.h"

#include "sel_RooJohnsonFunc.h"
using namespace RooFit;
//using namespace std;


int main(int argc, char** argv) {
  if (argc < 3) {
      std::cerr << "Usage: ./mymacro <year> <mode>\n";
      return 1;
  }

  TString year = argv[1];
  TString magnet = argv[2];



//void normalisation(TString year="2018", TString magnet="Tot"){


    RooRealVar *mass = new RooRealVar("mass", "massPIPI", 5, 6.1, "GeV/c^{2}");

    
    TString massName, massLabel, signalName, finalState, bdtName, bdtCut;
    Double_t meanVal = 0, m0Val = 0, sigmaVal = 0,
             ySig = 0, yBkg = 0, yPhys = 0, alphaVal = 0;

    massName = "massPIPI";
    massLabel = "m_{#pi^{+}#pi^{-}} [GeV/c^{2}]";
    signalName = "B^{0}#rightarrow #pi^{+}#pi^{-}";
    finalState = "pipi";
    bdtName = "PIPI";
    bdtCut = "-1";
    meanVal = 5.2795; //B0 mass
    m0Val = 5.145; //argus endpoint -> B0 mass after we lose the pi0
    sigmaVal = 0.023;
    alphaVal = 0.66;
    ySig = 30000;
    yBkg = 1000000;
    yPhys = 30000;

    //DEFINING THE MODEL
    //signal
    RooRealVar *mean = new RooRealVar("mean", "mean", meanVal);
    RooRealVar *delta = new RooRealVar("delta", "delta", 0.006, -0.01, 0.01);
    RooFormulaVar *shiftedMean = new RooFormulaVar("shiftedMean", "shiftedMean", "@0+@1", RooArgSet(*mean, *delta));
    RooRealVar *sigma = new RooRealVar("sigma", "sigma", sigmaVal, 0.01, 0.04);

    RooRealVar *alpha1 = new RooRealVar("alpha1", "alpha1", alphaVal);
    RooRealVar *alpha2 = new RooRealVar("alpha2", "alpha2", 0.52);
    RooRealVar *frac = new RooRealVar("frac", "frac", 0.16); //was 0.16 0.16*0.035/0.02*0.55/0.6 = 0.26 ->should this contamination increase? we got more stuff in?

    RooGaussian *g = new RooGaussian("g", "g", *mass, *shiftedMean, *sigma);
    sel_RooJohnsonFunc *tail = new sel_RooJohnsonFunc("tail", "tail", *mass, *shiftedMean, *sigma, *alpha1, *alpha2);
    
    RooAddPdf *pdf_sig = new RooAddPdf("pdf_sig", "pdf_sig", RooArgSet(*tail, *g), RooArgSet(*frac));

    /*
    RooRealVar *meanBS = new RooRealVar("meanBS", "meanBS", 5.3669); //Bs mass
    RooFormulaVar *shiftedMeanBs = new RooFormulaVar("shiftedMeanBs", "shiftedMeanBs", "@0+@1", RooArgSet(*meanBS, *delta));

    RooGaussian *gS = new RooGaussian("gS", "gS", *mass, *shiftedMeanBs, *sigma);
    sel_RooJohnsonFunc *tailS = new sel_RooJohnsonFunc("tailS", "tailS", *mass, *meanBS, *sigma, *alpha1, *alpha2);
    RooAddPdf *pdf_sigS = new RooAddPdf("pdf_sigS", "pdf_sigS", RooArgSet(*tailS, *gS), RooArgSet(*frac));
    */ //no need, we are only looking at the B0pipi peak


    // PHYS
    RooGaussModel *resM = new RooGaussModel("resM", "resM", *mass, *delta, *sigma);
    RooRealVar *m0 = new RooRealVar("m0", "m0", m0Val); //argus endpoint
    RooRealVar *cA = new RooRealVar("cA", "cA", -12., -100., 0.);
    RooArgusBG *pdf_phys_tmp = new RooArgusBG("pdf_phys_tmp", "pdf_phys_tmp", *mass, *m0, *cA);
    RooFFTConvPdf *pdf_phys = new RooFFTConvPdf("pdf_phys", "pdf_phys", *mass, *pdf_phys_tmp, *resM);
    pdf_phys->setBufferFraction(0.5);


    // CROSS-FEED
    //TString cfMassModelName = Form("${B2HH_OUT}/MassModels/CrossFeed/%s_%s_%s_%s_%s_%s.root",finalState.Data(), bdtName.Data(), bdtCut.Data(),configuration.Data(), magnet.Data(), year.Data());
    TString cfMassModelName = Form("${B2HH_OUT}/MassModels/CrossFeed/pipi_PIPI_0_-1.3.-1.3_Tot_%s.root",year.Data());
    //sticazzi della portabilità, spero di girarlo una volta sola
    std::cout << "Crossfeed MassModel is: " << cfMassModelName << std::endl;
    TFile *inFile = new TFile(cfMassModelName,"READ");
    inFile->Print();
    //RooWorkspace *myWS_tmp = (RooWorkspace *)inFile->Get(Form("%s_%s_%s_%s",finalState.Data(), bdtName.Data(),bdtCut.Data(), configuration.Data())); //"pipi_PIPI_0_-1.3.-1.3"
    RooWorkspace *myWS_tmp = (RooWorkspace *)inFile->Get("pipi_PIPI_0_-1.3.-1.3");
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
    RooRealVar *n_sig = new RooRealVar("n_sig", "n_sig", ySig, 0, 1E6);
    //RooRealVar *n_sigS = new RooRealVar("n_sigS", "n_sigS", 500, 0, 1000000);
    RooRealVar *yRatio = new RooRealVar("yRatio", "yRatio", 0.16, 0,1); ////was 0.16 0.16*0.035/0.02*0.55/0.6 = 0.26
    RooFormulaVar *n_cross = new RooFormulaVar("n_cross", "n_cross", "@0*@1", RooArgSet(*n_sig, *yRatio));
    RooRealVar *n_phys = new RooRealVar("n_phys", "n_phys", yPhys, 0, 1E6);
    RooRealVar *n_bkg = new RooRealVar("n_bkg", "n_bkg", yBkg, 0, 1E7); //10Mil

    RooAddPdf *pdf = new RooAddPdf("pdf", "pdf", 
        RooArgSet(*pdf_sig, *pdf_cross, *pdf_bkg, *pdf_phys),
        RooArgSet(*n_sig,   *n_cross,   *n_bkg,   *n_phys)
    ); //removed the Bs part 

    TChain *chain = new TChain("b2hh");

    //maps with years //running 201516, 2017s29r2p2, 2018
    std::map<TString, std::vector<TString>> tag_years;
    //tag_years["2015"] = {"2015"};
    //tag_years["2016"] = {"2016"};
    //tag_years["2017"] = {"2017"};
    
    //FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX FIX 

    tag_years["2017"] = {"2017s29r2p2"};
    tag_years["2017s29r2p2"] = {"2017s29r2p2"};
    tag_years["2018"] = {"2018"};
    tag_years["201516"] = {"2015", "2016"};
    
    
    //tag_years["20151618"] = {"2015", "2016", "2018"};
    //tag_years["Tot"] = {"2015", "2016", "2017", "2018"};
    //tag_years["Tot"] = {"201516", "2017s29r2p2", "2018"};
  
    //maps with magnets
    std::map<TString, std::vector<TString>> tag_magnet;
    //tag_magnet["Up"] = {"Up"};
    //tag_magnet["Down"] = {"Down"};
    tag_magnet["Tot"] = {"Up", "Down"}; //most likely running on Tot -> no magnet split
    //tag_magnet["Tot"] = {"Up"};
    
    //adding the chains
    for (TString tmpYear : tag_years[year]){
      for (TString tmpMagnet : tag_magnet[magnet]){
        chain->Add(Form("${B2HH_OUT}/newBDTtrain/forNorm/bitFix/b2hh_%s_%s.root/b2hh",
                      tmpYear.Data(), tmpMagnet.Data()));
      }
    }

    //adding the PID and old BDT cuts
    Double_t piplusDLLKPI = 0, piplusDLLPPI = 0, piminusDLLKPI = 0, piminusDLLPPI = 0;
    Double_t massV = 0, oldBDT = 0;
    chain->SetBranchStatus("*", 0);
    chain->SetBranchStatus("piplusDLLKPI", 1), chain->SetBranchAddress("piplusDLLKPI", &piplusDLLKPI);
    chain->SetBranchStatus("piplusDLLPPI", 1), chain->SetBranchAddress("piplusDLLPPI", &piplusDLLPPI);
    chain->SetBranchStatus("piminusDLLKPI", 1), chain->SetBranchAddress("piminusDLLKPI", &piminusDLLKPI);
    chain->SetBranchStatus("piminusDLLPPI", 1), chain->SetBranchAddress("piminusDLLPPI", &piminusDLLPPI);
    chain->SetBranchStatus(massName, 1), chain->SetBranchAddress(massName, &massV);
    chain->SetBranchStatus("bdtPIPI", 1), chain->SetBranchAddress("bdtPIPI", &oldBDT);

    RooDataSet *data = new RooDataSet("data", "data", RooArgSet(*mass));
    RooArgSet obs;
    obs.add(*mass);  
    //auto mycut = ((decay == "bskk")? cut_bskk : cut_bdpipi);
    for (Int_t ientry = 0, nentries = chain->GetEntries(); ientry < nentries; ++ientry){
      chain->GetEntry(ientry); 
      //if (!mycut(piplusDLLKPI,piplusDLLPPI,piminusDLLKPI,piminusDLLPPI,cut1,cut2)) continue;
      if (oldBDT < 0) continue; // old BDT cut //should prune a lot of stuff
      if (piplusDLLKPI > -1 || piplusDLLPPI > 3 || piminusDLLKPI > -1 || piminusDLLPPI > 3) continue; // piplusDLLPPI<3 and piminusDLLPPI<3
      if (massV < 5.0) continue;
      if (massV > 6.1) continue;

      mass->setVal(massV);  
      if (pdf->getVal(obs) < 0) continue;
      data->add(obs);
    }
    data->Print("v");

    TString jobTag = Form("Normalisation_-1.3.-1.3_Tot_%s", year.Data());

    TString outDir = gSystem->Getenv("B2HH_OUT");
    TString paramFile = Form("%s/newBDTtrain/Norm/params/params_%s.txt", outDir.Data(), jobTag.Data());

    RooArgSet *params = pdf->getParameters(*mass);
    //params->readFromFile(Form("$B2HH_OUT/newBDTtrain/Norm/params/params_%s.txt", jobTag.Data())); // not working for some reason -> not expanding
    params->readFromFile(paramFile);
    RooFitResult *r = pdf->fitTo(*data, Strategy(2), Offset(kTRUE), Extended(),
                              NumCPU(12), PrintLevel(3), Verbose(kTRUE), Save());
    r->Print("v");
    //params->writeToFile(Form("$B2HH_OUT/newBDTtrain/Norm/params/params_%s.txt", jobTag.Data())); // not working for some reason -> not expanding
    params->writeToFile(paramFile);
    //params->writeToFile(Form("params_%s.txt", jobTag.Data()));


    if (r->edm() < 1e-3 && r->covQual() == 3) {
        printf("FIT HAS CONVERGED\n");
    }
    else {
        printf("FIT HAS NOT CONVERGED\n");
    }


    RooPlot *plot = mass->frame(5, 6.1, 160);
    plot->SetTitle("");
    plot->GetXaxis()->SetTitleSize(0.05);
    plot->GetXaxis()->SetLabelSize(0.05);
    plot->GetXaxis()->SetTitleOffset(1.1);
    //plot->GetXaxis()->SetTitle(massLabel);
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
  
    TLegend *leg = new TLegend(0.75, 0.75, 0.9, 0.9);
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
  
    TPaveText *lhcb = new TPaveText(0.75, 0.55, 0.9, 0.75, "NDC");
    lhcb->AddText("LHCb Preliminary");
    lhcb->SetTextSize(0.05);
    lhcb->SetFillColor(kWhite);
    //lhcb->Draw("same");
  
    lowerPad1->cd();
    auto hpull1 = plot->pullHist();
    hpull1->SetFillColor(kBlue);
    auto pulls_plot1 = mass->frame(5, 6.1, 160);
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


/*COMPILING INSTRUCTION
1) ensure this file has a main function

2) Create the LinkDef.h file with the following content:
// LinkDef.h

#ifdef __CINT__
#pragma link C++ class sel_RooJohnsonFunc+;
#endif

3) Generate the dictionary with rootcling: (bash)
bash:

rootcling -f sel_RooJohnsonFunc_dict.cxx \
          -c sel_RooJohnsonFunc.h LinkDef.h

4) compile everything
bash:

g++ normalisation.cpp sel_RooJohnsonFunc.cxx sel_RooJohnsonFunc_dict.cxx \
    -o normalisation `root-config --cflags --libs` -lRooFit -lRooFitCore

5) run with (example) // env setup + sourcing setup_lcg_105

./normalisation 2018 Tot 
*/
