//code should create a chain with the data

//optimise on all years at once? training was on all of them, makes sense to have single working point

//for every BDT 
// -> see what is left of the signal (within 3 sigmas from the mean)
// -> from sideband extract resiudual combinatorial background

//FoM: S/sqrt(S+B)
// S -> from norm extract the number of Bdpipi signal event -> transpose via fs/fd and BR ratio to expected Bspipi yield
//      this corresponds to the integral of the accsignal reweighted signal
// B -> from the fit to the sideband region transposed to the region of interest


//no way ti=o make it work for all branches i guess -> we do one at a time + sending to condor
#include <vector>

#include "RooArgSet.h"
#include "RooRealVar.h"
#include "TString.h"
#include "TMath.h"
#include "TGraph.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"

using namespace RooFit;





//for the signal -> it uses the reweighting (weight branch)
std::vector<Double_t> getValues(TChain* chain, TString branchName, int tests, double massMin, double massMax) {
    std::vector<Double_t> values;
    double step = 1.0/tests;

    for (int i = 0; i<tests; ++i) {
        TH1D * h = new TH1D(Form("h_%d", i), Form("h_%d", i), 500, massMin, massMax); 
        chain->Draw(Form("massPIPI>>h_%d", i), Form("weight && %s > %f", branchName.Data(), i * step), "goff");       
        values.push_back(h->Integral());
        std::cout << "histo integral " << h->Integral()/values[0] << std::endl;
        delete h;
    }
    return values;
}





//for thye background -> entries are not reweighted
//need to perform the fit
std::vector<Double_t> getValues(TTree* tree, TString branchName, RooRealVar *mass, int tests, double massMin, double massMax, double massBsMin, double massBsMax) {
    std::vector<Double_t> values;
    double step = 1.0/tests;
    //double scalingConstant = ; // relate the sidebandyield to the expected yield in the region of interest
    RooRealVar *slope = new RooRealVar("slope", "slope", -1, -10, 1);
    RooRealVar *sideYield = new RooRealVar("sideYield", "sideYield", 1E5, 0, 1E6);
    RooExponential *pdf_bkg = new RooExponential("pdf_bkg", "pdf_bkg", *mass, *slope);
    RooExtendPdf *bkg_model = new RooExtendPdf("bkg_model", "bkg_model", *pdf_bkg, *sideYield);
    int nBins = 100;

    for (int i = 0; i<tests; ++i) {
        TH1D * h = new TH1D(Form("h_%d", i), Form("h_%d", i), nBins, massMin, massMax); 
        tree->Draw(Form("massPIPI>>h_%d", i), Form("          %s > %f", branchName.Data(), i * step), "goff");

        RooDataHist *data = new RooDataHist("data", "data", RooArgSet(*mass), h);
        data->Print("v");
        RooFitResult *r = bkg_model->fitTo(*data, Strategy(2),
                                         NumCPU(4), PrintLevel(1), Verbose(kFALSE), Save());
        
        TCanvas *c = new TCanvas("c", "c", 700, 700);
        RooPlot *plot = mass->frame(massMin, massMax, nBins);
        data->plotOn(plot);
        bkg_model->plotOn(plot, LineColor(kBlue), LineWidth(2), LineStyle(1));
        //plot->SetTitle("");
        plot->Draw("goff");
        //h->Draw();
        c->SaveAs(Form("${B2HH_OUT}/newBDTtrain/BDToptim/%s/sideband_%f.pdf", branchName.Data(), i*step));


        r->Print("v");
        double slopeVal = slope->getVal();
        double expectedYield = sideYield->getVal() * (TMath::Exp(- slopeVal *massBsMin) - TMath::Exp(- slopeVal *massBsMax))/(TMath::Exp(- slopeVal *massMin) - TMath::Exp(- slopeVal *massMax));
        values.push_back(expectedYield); // no need to normalise
        std::cout << "\n" << i*step << ": " << expectedYield <<  " (Bs RoI)/" << sideYield->getVal() << " (fitted sideband) "<<std::endl;
        std::cout << "    " << values[i]/values[0] << "%\n" << std::endl;
        //std::cout << "histo integral " << h->Integral() << " (" << h->Integral()/values[0] << "%) " << std::endl;
        delete h;
        delete data;
        delete r;

        delete c;
        
        //delete slope, sideYield;
    }
    return values;
}












void optim(TString testedBDT = "bdtgradient_300_3"){

    double massMin = 5;
    double massMax = 6.1;

    double massBs = 5.366; //using GeV
    double sigmaMassResolution = 0.02; // 20 MeV
    double massBsMin = massBs - 3 * sigmaMassResolution;
    double massBsMax = massBs + 3 * sigmaMassResolution; 

    double massMinSideband = 5.6; // GeV in PIPI hypothesis
    double massMaxSideband = 6.1; // GeV in PIPI hypothesis

    int exploredCutsNum = 100;//10; 

    RooRealVar *mass = new RooRealVar("mass", "massPIPI", massMin, massMax, "GeV/c^{2}");

    ///////////////////
    //  S i g n a l  //
    ///////////////////

    
    //does not want to read from the params file for whatever reason.... -> HARD CODING IS THE SOLUTION
    Double_t sigYield = 0;
    sigYield = 46324 + 54021 + 55652;
    Double_t sigYieldErr = 0;
    sigYieldErr = sqrt(779*779 + 785*785 + 966*966);

    std::vector<TString> years = {"201516", "2017s29r2p2", "2018"};


    Double_t massPIPI_sig, weight_sig;

    TChain * sigChain = new TChain("sigChain","sigChain");
    for (const auto& year : years) {
        TString fileName = Form("${B2HH_OUT}/newBDTtrain/forNorm/bitFix/bspipi_%s_Tot.root/b2hh", year.Data());
        std::cout << "Loading file: " << fileName << std::endl;
        sigChain->Add(fileName);
    }

    sigChain->SetBranchStatus("*", 0);
    sigChain->SetBranchStatus("massPIPI", 1), sigChain->SetBranchAddress("massPIPI", &massPIPI_sig);
    sigChain->SetBranchStatus("weight", 1), sigChain->SetBranchAddress("weight", &weight_sig);

    std::vector<Double_t> sig_survivingBDTcuts(exploredCutsNum,0);

    sigChain->SetBranchStatus(testedBDT, 1);


    sigChain->Print();
    std::cout << "BDT: " << testedBDT << std::endl;

    sig_survivingBDTcuts = getValues(sigChain, testedBDT, exploredCutsNum, massBsMin, massBsMax);
   

    /////////////////////////
    // B a c k g r o u n d //
    /////////////////////////

    std::cout << "Looking at the bkg\n";

    std::vector<TString> yearsBkg = {"2015", "2016", "2017s29r2p2", "2018"};

    TChain * bkgChain = new TChain("bkgChain","bkgChain");
    for (const auto& year : yearsBkg) {
        TString fileNameUp   = Form("${B2HH_OUT}/newBDTtrain/forNorm/bitFix/b2hh_%s_Up.root/b2hh", year.Data());
        TString fileNameDown = Form("${B2HH_OUT}/newBDTtrain/forNorm/bitFix/b2hh_%s_Down.root/b2hh", year.Data());

        std::cout << "Loading file: " << fileNameUp << " (and Down)" << std::endl;
        bkgChain->Add(fileNameUp);
        bkgChain->Add(fileNameDown);
    }

    Double_t piplusDLLKPI = 0, piplusDLLPPI = 0, piminusDLLKPI = 0, piminusDLLPPI = 0;
    Double_t massPIPI_bkg = 0;
    Double_t oldBDT_bkg = 0, newBDT_bkg = 0;
    bkgChain->SetBranchStatus("*", 0);
    bkgChain->SetBranchStatus("piplusDLLKPI", 1), bkgChain->SetBranchAddress("piplusDLLKPI", &piplusDLLKPI);
    bkgChain->SetBranchStatus("piplusDLLPPI", 1), bkgChain->SetBranchAddress("piplusDLLPPI", &piplusDLLPPI);
    bkgChain->SetBranchStatus("piminusDLLKPI", 1), bkgChain->SetBranchAddress("piminusDLLKPI", &piminusDLLKPI);
    bkgChain->SetBranchStatus("piminusDLLPPI", 1), bkgChain->SetBranchAddress("piminusDLLPPI", &piminusDLLPPI);
    bkgChain->SetBranchStatus("massPIPI", 1), bkgChain->SetBranchAddress("massPIPI", &massPIPI_bkg);
    bkgChain->SetBranchStatus("bdtPIPI", 1), bkgChain->SetBranchAddress("bdtPIPI", &oldBDT_bkg);
    bkgChain->SetBranchStatus(Form("%s",testedBDT.Data()), 1), bkgChain->SetBranchAddress(Form("%s",testedBDT.Data()), &newBDT_bkg);
    
    //TTree * bkg_cut = bkgChain->CopyTree(Form("%s > 0", testedBDT.Data()));
    TTree * bkg_cut = bkgChain->CopyTree(Form("bdtPIPI > 0 && piplusDLLKPI < -1 && piplusDLLPPI < 3 && piminusDLLKPI < -1 && piminusDLLPPI < 3 && massPIPI > %f && massPIPI < %f",massMinSideband,massMaxSideband));
    
    bkg_cut->Print();


    std::vector<Double_t> bkg_survivingBDTcuts(exploredCutsNum,0);
    bkg_survivingBDTcuts = getValues(bkg_cut, testedBDT, mass,exploredCutsNum, massMinSideband, massMaxSideband, massBsMin, massBsMax);



    ///////////////////////////////
    //  S i g n i f i c a n c e  //
    ///////////////////////////////
    Double_t significance[exploredCutsNum];
    Double_t cuts[exploredCutsNum];

    double scaleBdToBs = 0.035;//
    // BR Bd to pipi is ( 5.36  +- 0.16  ) 10-6
    // BR Bs to pipi is ( 7.4   +- 1.1   ) 10-7
    //fs/fs             ( 0.254 +- 0.008 )

    for (int i = 0; i<exploredCutsNum; ++i) {
        cuts[i] = i*1.0/exploredCutsNum;

        significance[i] = scaleBdToBs*sigYield*sig_survivingBDTcuts[i]/sig_survivingBDTcuts[0]/sqrt((scaleBdToBs*sig_survivingBDTcuts[i]*sigYield/sig_survivingBDTcuts[0]) + bkg_survivingBDTcuts[i]);
        std::cout << "Significance for cut " << i << ": " << significance[i] << std::endl;
    }

        // Create the TGraph
        TGraph* significanceGraph = new TGraph(exploredCutsNum, cuts, significance);
        significanceGraph->SetTitle(Form("Significance %s;BDT;S/#sqrt{S+B}",testedBDT.Data()));
        //significanceGraph->SetMarkerStyle(20);
        significanceGraph->SetLineColor(kBlue);
    
        // Draw the graph
        TCanvas* canvasSignificance = new TCanvas("canvasSignificance", "canvasSignificance", 800, 600);
        canvasSignificance->SetTicks(1, 1);
        significanceGraph->Draw("APL");
        canvasSignificance->SaveAs(Form("${B2HH_OUT}/newBDTtrain/BDToptim/%s/significance_%s.pdf", testedBDT.Data(), testedBDT.Data()));
        canvasSignificance->SaveAs(Form("${B2HH_OUT}/newBDTtrain/BDToptim/%s/significance_%s.root", testedBDT.Data(), testedBDT.Data()));
        canvasSignificance->SaveAs(Form("${B2HH_OUT}/newBDTtrain/BDToptim/bestSignificances/significance_%s.pdf", testedBDT.Data()));


        double bestSignificance = 0;
        double bestCut = 0;

        for (int i = 0; i<exploredCutsNum; ++i) {
            if (significance[i] > bestSignificance) {
                bestSignificance = significance[i];
                bestCut = cuts[i];
            }
        }

        TCanvas * pipispectreBestCut = new TCanvas("pipispectreBestCut", "pipispectreBestCut", 700, 700);
        TH1D * hmass = new TH1D("hmass", "hmass", 200, massMin, massMax);
        bkgChain->Draw("massPIPI>>hmass", Form("bdtPIPI > 0 && %s > %f && piplusDLLKPI < -1 && piplusDLLPPI < 3 && piminusDLLKPI < -1 && piminusDLLPPI < 3", testedBDT.Data(), bestCut), "goff");
        hmass->SetTitle(Form("Best cut: %f (S/#sqrt{S+B}=%f);;mass_{#pi#pi}", bestCut,bestSignificance));
        hmass->Draw("histo");
        pipispectreBestCut->SaveAs(Form("${B2HH_OUT}/newBDTtrain/BDToptim/%s/massPIPI_BestCut_%s.pdf", testedBDT.Data(), testedBDT.Data()));
        pipispectreBestCut->SaveAs(Form("${B2HH_OUT}/newBDTtrain/BDToptim/bestSignificances/massPIPI_BestCut_%s.pdf", testedBDT.Data()));

        const char* basePath = getenv("B2HH_OUT");
        TString textfileName = Form("${B2HH_OUT}/newBDTtrain/BDToptim/bestSignificances/%s_significance.txt", testedBDT.Data());
        std::ofstream textfile(Form("%s/newBDTtrain/BDToptim/bestSignificances/%s_significance.txt", basePath, testedBDT.Data()));
        textfile << bestSignificance << " " << bestCut << " " << testedBDT << "\n";
        //textfile << "maximum significance for the BDT cut and the corresponding cut value" << "\n";
        textfile.close();
        std::cout << "Best significance saved in " << textfileName << std::endl;
}