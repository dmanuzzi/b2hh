#include <iostream>

#include "biasMapTools.cpp"

using namespace std;

int makeBiasMap(TString tag){
    

    TChain *tin = new TChain("tin_"+tag, "tin_"+tag);
    for (auto nfin : biasMapTools::tag_nfins_Jpsi[tag]){
        printf("for tag %s, importing file: %s\n", tag.Data(), nfin.Data());
        tin->Add(nfin);
    }

    Int_t nentries = tin->GetEntries();
    printf("entries to read: %d\n", nentries);

    tin->SetBranchStatus("*", 0);
    double Jpsi_MM=0, Jpsi_TAU=0;
    double muplus_PX=0, muplus_PY=0, muplus_PZ=0, muplus_P=0;
    double muminus_PX=0, muminus_PY=0, muminus_PZ=0, muminus_P=0;
    
    biasMapTools::ActivateAndSetBranch(tin, "Jpsi_MM", &Jpsi_MM);
    biasMapTools::ActivateAndSetBranch(tin, "Jpsi_TAU", &Jpsi_TAU);
    biasMapTools::ActivateAndSetBranch(tin, "muplus_PX", &muplus_PX);
    biasMapTools::ActivateAndSetBranch(tin, "muplus_PY", &muplus_PY);
    biasMapTools::ActivateAndSetBranch(tin, "muplus_PZ", &muplus_PZ);
    biasMapTools::ActivateAndSetBranch(tin, "muplus_P", &muplus_P);
    biasMapTools::ActivateAndSetBranch(tin, "muminus_PX", &muminus_PX);
    biasMapTools::ActivateAndSetBranch(tin, "muminus_PY", &muminus_PY);
    biasMapTools::ActivateAndSetBranch(tin, "muminus_PZ", &muminus_PZ);
    biasMapTools::ActivateAndSetBranch(tin, "muminus_P", &muminus_P);

    auto bins_muplus_PHI    = biasMapTools::makeBins(8, -acos(-1), acos(-1));
    auto bins_muminus_PHI   = biasMapTools::makeBins(8, -acos(-1), acos(-1));
    auto bins_muplus_ETA  = biasMapTools::makeBins(6, 2, 5);
    auto bins_muminus_ETA = biasMapTools::makeBins(6, 2, 5);
    auto bins_muplus_TANTHETA    = biasMapTools::makeBins(4, 0, 0.25);
    auto bins_muminus_TANTHETA   = biasMapTools::makeBins(4, 0, 0.25);

    // auto bins_muplus_THETA = biasMapTools::makeBins(2, 0, 0.25);
    // auto bins_muminus_THETA = biasMapTools::makeBins(2, 0, 0.25);
    vector<Double_t> bins_muplus_THETA = {0, 0.035, 0.06, 0.09, 0.13, 0.18, 0.25};
    vector<Double_t> bins_muminus_THETA = {0, 0.035, 0.06, 0.09, 0.13, 0.18, 0.25};

    auto bins_muplus_angx   = biasMapTools::makeBins(10, -0.28, 0.28);
    auto bins_muminus_angx = biasMapTools::makeBins(10, -0.28, 0.28);
    auto bins_muplus_angy = biasMapTools::makeBins(4, -0.28, 0.28);
    auto bins_muminus_angy = biasMapTools::makeBins(4, -0.28, 0.28);

    vector<TString> tag_vars_PhiTheta = {
      "phiPlus",
      "phiMinus",
      "thetaPlus",
      "thetaMinus"  
    };
    
    vector<vector<Double_t>> binnings_PhiTheta = {
        bins_muplus_PHI,
        bins_muminus_PHI,
        bins_muplus_THETA,
        bins_muminus_THETA,
    };

    biasMapTools toolsPhiTheta("PhiTheta", tag,
                                tag_vars_PhiTheta, 
                                binnings_PhiTheta);

    auto calcVars_PhiTheta = [&muplus_PX, &muplus_PY, &muplus_PZ, &muplus_P,
                              &muminus_PX, &muminus_PY, &muminus_PZ, &muminus_P,
                              &toolsPhiTheta]()
    {
        toolsPhiTheta.vars[0] = atan2(muplus_PY, muplus_PX);
        toolsPhiTheta.vars[1] = atan2(muminus_PY, muminus_PX);
        toolsPhiTheta.vars[2] = asin(sqrt(muplus_PX * muplus_PX + muplus_PY * muplus_PY) / muplus_P);
        toolsPhiTheta.vars[3] = asin(sqrt(muminus_PX * muminus_PX + muminus_PY * muminus_PY) / muminus_P);
    };
    auto selection = [&Jpsi_MM](){
        return (abs(Jpsi_MM-3096)<20);
    };

    
    Double_t Jpsi_TAU_ps = 0;

    
    for (int ientry = 0; ientry < nentries; ++ientry)
    {
        tin->GetEntry(ientry);
        if (ientry%10000 == 0) printf("\r reading %1.2f", (float)ientry/(float)nentries);
        if (!selection()) continue;
        calcVars_PhiTheta();
        Jpsi_TAU_ps = Jpsi_TAU*1000.0;
        toolsPhiTheta.fill(Jpsi_TAU_ps);
        // if (ientry > 10)
        //     break;
        
        //if (ientry > 1.0e6) break;
    }

    gROOT->ProcessLine(".L ../../tools/lhcbStyle.C");
    gStyle->SetPaintTextFormat("3.0f");
    gStyle->SetPalette(kRainBow);

    toolsPhiTheta.draw_vars("./plots_PhiTheta", "norm hist");   
    toolsPhiTheta.calcProfiles();
    toolsPhiTheta.draw_distrib2D_slice("distrib", {"phiPlus", "thetaPlus"},
                                       "./plots_PhiTheta", "pol");
    toolsPhiTheta.draw_distrib2D_slice("biasMap", {"phiPlus", "thetaPlus"},
                                       "./plots_PhiTheta", "pol");
    toolsPhiTheta.exportBiasMaps("./biases");

    return 1;
}

int getBiasMap()
{
    vector<TString> tags = {
        "Jpsi_2016_Up",
        "Jpsi_2017_Up",
        "Jpsi_2018_Up",
        "Jpsi_2016_Down",
        "Jpsi_2017_Down",
        "Jpsi_2018_Down",
        "Jpsi_2016_Tot",
        "Jpsi_2017_Tot",
        "Jpsi_2018_Tot",
    };
    for (auto tag : tags)
        makeBiasMap(tag);

    return 1;
}












// vector<Double_t> bias, biasErr;
    // vector<Int_t> fitOK;
    // for (int icont=0; icont<(int)containers.size(); ++icont){
    //     printf("icont: %d\n",icont);
    //     containers[icont].Print("v");
    //     Double_t norm = (Double_t)countBin[icont];
    //     RooRealVar mu("mu", "mu", meanBin[icont], biasMapTools::minTime, biasMapTools::maxTime);
    //     RooRealVar rms1("rms1", "rms1", rmsBin[icont], rmsBin[icont] * 0.1, rmsBin[icont] * 1.9);
    //     RooGaussian gaus1("gaus1", "gaus1", biasMapTools::time, mu, rms1);
    //     RooRealVar Ngaus1("Ngaus1", "Ngaus1", 0.9 * norm, 0, norm * 100);

    //     RooRealVar frms12("frms12", "frms12", 0.7, 0, 1);
    //     RooFormulaVar rms2("rms2", "rms2", "@0/@1", RooArgList(rms1, frms12));
    //     RooGaussian gaus2("gaus2", "gaus2", biasMapTools::time, mu, rms2);
    //     RooRealVar fgaus12("fgaus12", "fgaus12", 0.9, 0, 1);
    //     RooRealVar Ngaus2("Ngaus2", "Ngaus2", 0.1 * norm, 0, norm * 100);

    //     RooRealVar frms13("frms13", "frms13", 0.3, 0, 1);
    //     RooFormulaVar rms3("rms3", "rms3", "@0/@1", RooArgList(rms1, frms13));
    //     RooGaussian gaus3("gaus3", "gaus3", biasMapTools::time, mu, rms3);
    //     RooRealVar fgaus13("fgaus13", "fgaus13", 0.9, 0, 1);
    //     RooRealVar Ngaus3("Ngaus3", "Ngaus3", 0.1 * norm, 0, norm * 100);

    //     RooAddPdf model("model3gaus", "model3gaus", RooArgList(gaus1, gaus2, gaus3), RooArgList(Ngaus1, Ngaus2, Ngaus3));

    //     RooFitResult *fitRes = model.fitTo(containers[icont], Save(kTRUE), Extended(kTRUE), Verbose(kFALSE), PrintLevel(0), NumCPU(16));
    //     bias.push_back(mu.getValV());
    //     biasErr.push_back(mu.getError());
    //     fitOK.push_back(fitRes->covQual()==3);
    //     fitRes->Print("v");

    //     TString ncanv = Form("canv_%s", containers[icont].GetName());
    //     TCanvas *canv = new TCanvas(ncanv, ncanv, 500, 600);
    //     canv->cd();
    //     TPad *upperPad = new TPad(ncanv + "_upperPad", ncanv + "_upperPad", 0, 0.2, 1, 1);
    //     TPad *lowerPad = new TPad(ncanv + "_lowerPad", ncanv + "_lowerPad", 0, 0, 1, 0.2);
    //     upperPad->SetLeftMargin(0.2);
    //     upperPad->SetBottomMargin(0.15);
    //     upperPad->SetBorderSize(0);
    //     lowerPad->SetLeftMargin(0.2);
    //     lowerPad->SetBorderSize(0);
    //     upperPad->Draw();
    //     lowerPad->Draw();

    //     upperPad->cd();
    //     RooPlot *frame = biasMapTools::time.frame();
    //     containers[icont].plotOn(frame);
    //     model.plotOn(frame);
    //     model.plotOn(frame, Components("gaus1"), LineStyle(kDashed), LineColor(kGreen + 2));
    //     model.plotOn(frame, Components("gaus2"), LineStyle(kDashed), LineColor(kRed));
    //     model.plotOn(frame, Components("gaus3"), LineStyle(kDashed), LineColor(kMagenta));
    //     model.plotOn(frame);
    //     frame->Draw();

    //     lowerPad->cd();
    //     RooHist *hpull = frame->pullHist();
    //     RooPlot *frame2 = biasMapTools::time.frame();

    //     hpull->SetTitle("");
    //     hpull->SetFillColor(kBlue);
    //     frame2->addPlotable(hpull, "BX");
    //     frame2->GetXaxis()->SetTitleSize(0);
    //     frame2->GetXaxis()->SetLabelSize(0);
    //     frame2->GetXaxis()->SetTickLength(0.15);
    //     frame2->GetYaxis()->SetTitleSize(0.15);
    //     frame2->GetYaxis()->SetLabelSize(0.15);
    //     frame2->GetYaxis()->SetTitleOffset(0.2);
    //     frame2->GetYaxis()->SetTitle("pull");
    //     frame2->GetYaxis()->SetRangeUser(-5, 5);
    //     frame2->GetYaxis()->SetTickLength(0.05);
    //     frame2->GetYaxis()->SetNdivisions(502, false);
    //     frame2->Draw();
    //     canv->SaveAs(Form("plots_NDIM/%s.root", canv->GetName()));
    //     canv->SaveAs(Form("plots_NDIM/%s.pdf", canv->GetName()));
    //     upperPad->SetLogy();
    //     canv->Draw();
    //     canv->SaveAs(Form("plots_NDIM/%s_log.pdf", canv->GetName()));
    // }
    // for (int ibin = 0; ibin < NbinsTot; ++ibin)
    // {
    //     double count = (Double_t)countBin[ibin];
    //     double mean = meanBin[ibin];
    //     double rms = rmsBin[ibin];
    //     double meanErr = rms/sqrt(count);
    //     printf("\n");
    //     printf("BASIC -- ibin: %d,  mean: %2.3f +/- %2.3f fs, rms: %.3f fs, entries: %.0f\n",
    //            ibin, mean*1000, meanErr*1000, rms*1000, count);
    //     mean = bias[ibin];
    //     meanErr = biasErr[ibin];
    //     printf("FIT   -- ibin: %d,  mean: %2.3f +/- %2.3f fs, fitStatus: %d\n",
    //            ibin, mean * 1000, meanErr * 1000, fitOK[ibin]);
    // }
