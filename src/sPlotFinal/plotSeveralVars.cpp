//source /cvmfs/sft.cern.ch/lcg/views/LCG_105/x86_64-centos7-gcc12-opt/setup.sh
#include <iostream>
#include <vector>
#include <map>
using namespace std;
#include "TString.h"
#include "TFile.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1D.h"
#include "TLine.h"
#include "ROOT/RResultPtr.hxx"
#include "ROOT/RDFHelpers.hxx"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RDF/InterfaceUtils.hxx"
using namespace ROOT;

template <typename RDF> 
auto defineAll(RDF df){
    return df.Define("logPiplusIPCHI2", "log(piplusIPCHI2)")
        .Define("logBIPCHI2", "log(bIPCHI2)")
        .Define("logBVTXCHI2", "log(bVTXCHI2)")
        .Define("logtauKKCHI2", "log(tauKKCHI2)")
        .Define("acosBDIRA", "acos(bDIRA)")
        .Define("logBFDCHI2", "log(bFDCHI2)")
        .Define("bIPCHI2overIP", "bIPCHI2/bIP")
        .Define("piplusIPCHI2overIP", "piplusIPCHI2/piplusIP")
        .Define("logPiplusGhostProb", "log(piplusGhostProb)")
        .Define("logBIP2overIPCHI2", "log(bIP*bIP/bIPCHI2)")
        .Define("logBFD2overFDCHI2", "log(bFD*bFD/bFDCHI2)")
        .Define("minPT", "min(piplusPT,piminusPT)")
        .Define("maxPT", "max(piplusPT,piminusPT)")
        .Define("sumPT", "piplusPT+piminusPT")
        .Define("bPL", "sqrt(bP*bP-bPT*bPT)")
        .Define("mk2", "(493.677/1000.0)*(493.677/1000.0)")
        .Define("c", "0.299792458")
        .Define("dx", "bENDVx-bPVx")
        .Define("dy", "bENDVy-bPVy")
        .Define("dz", "bENDVz-bPVz")
        .Define("logdz", "log(bENDVz-bPVz)")
        .Define("piplusPX", "piplusPx/1000.0")
        .Define("piplusPY", "piplusPy/1000.0")
        .Define("piplusPZ", "piplusPz/1000.0")
        .Define("piminusPX", "piminusPx/1000.0")
        .Define("piminusPY", "piminusPy/1000.0")
        .Define("piminusPZ", "piminusPz/1000.0")
        .Define("px", "piplusPX+piminusPX")
        .Define("py", "piplusPY+piminusPY")
        .Define("pz", "piplusPZ+piminusPZ")
        .Define("P1", "piplusPX*piplusPX + piplusPY*piplusPY + piplusPZ*piplusPZ")
        .Define("P2", "piminusPX*piminusPX + piminusPY*piminusPY + piminusPZ*piminusPZ")
        .Define("P12", "piplusPX*piminusPX + piplusPY*piminusPY + piplusPZ*piminusPZ")
        .Define("E12", "(sqrt(mk2 + P1))*(sqrt(mk2 + P2))")
        .Define("L", "sqrt(dx*dx + dy*dy + dz*dz)")
        .Define("P", "sqrt(px*px + py*py + pz*pz)")
        .Define("M", "sqrt(2*(mk2+E12-P12))")
        .Define("t_noDTF", "M/P*L/c")
        .Define("DTFdiff", "tauKK-t_noDTF")
        .Define("bTheta", "2*atan(exp(-bETA))")
        .Define("piplusTheta", "2*atan(exp(-piplusETA))")
        .Define("hhAngle", "180.0/acos(-1)*acos((piplusPx*piminusPx/1.0e6+piplusPy*piminusPy/1.0e6+piplusPz*piminusPz/1.0e6)/(piplusP*piminusP))")
        .Define("logPiplusIP2overIPCHI2", "log(piplusIP*piplusIP/piplusIPCHI2)");
}

TH1D getReweightHisto1D(ROOT::RDF::RNode df0, ROOT::RDF::RNode dfT,
                        TString previous_weight,
                        TString rew_var, int Nbins, double vmin, double vmax,
                        TString nfout = "test.root"){
    if (!df0.HasColumn("rewweight_var"))
        df0 = df0.Define("reweight_var", (rew_var!="")?rew_var.Data():"1");
    if (!dfT.HasColumn("rewweight_var"))
        dfT = dfT.Define("reweight_var", (rew_var!="")?rew_var.Data():"1");
    auto h0 = df0.Histo1D({"hOrig", TString("hOrig; " + rew_var).Data(), Nbins, vmin, vmax},
                          "reweight_var", previous_weight.Data());
    auto hT = dfT.Histo1D({"hTarget", TString("hTarget; " + rew_var).Data(), Nbins, vmin, vmax},
                          "reweight_var", previous_weight.Data());
    h0->Scale(1.0 / h0->Integral());
    hT->Scale(1.0 / hT->Integral());
    TH1D hR("h_ratio", "h_ratio", Nbins, vmin, vmax);
    hR.Divide(hT.GetPtr(), h0.GetPtr());
    h0->Print();
    hT->Print();
    hR.Print();
    TFile fout(nfout, "RECREATE");
    fout.WriteTObject(h0.GetPtr());
    fout.WriteTObject(hT.GetPtr());
    fout.WriteTObject(&hR);
    fout.ls();
    fout.Close();
    return hR;
}

auto reweight1D(ROOT::RDF::RNode df0, TH1D* hR,
                TString previous_weight,
                TString rew_var,
                TString nfout = "test.root")
{
    if (rew_var == ""){
        return df0.Define("reweight_var", "1").Define("reweight",previous_weight.Data());
    }
    if (!df0.HasColumn("rewweight_var"))
        df0 = df0.Define("reweight_var", rew_var.Data());
    auto getWeight = [hR](const double x, const double w) { 
        auto ibin = hR->FindBin(x);
        return hR->GetBinContent(ibin) * w; 
    };
    auto df_out = df0.Define("reweight", getWeight, {"reweight_var", previous_weight.Data()});
    df_out.Display("reweight")->Print();
    // auto h1 = df0.Histo1D({"hNew", TString("hNew; " + rew_var).Data(), Nbins, vmin, vmax},
    //                       "reweight_var", "reweight");
    // auto hrew = df0.Histo1D({"h_reweight", "h_reweight", Nbins, -5, 5}, "reweight");
    // TFile fout(nfout, "UPDATE");
    // fout.WriteTObject(hrew.GetPtr());
    // fout.WriteTObject(h1.GetPtr());
    // fout.ls();
    // fout.Close();
    return df_out;
}

ROOT::RDF::RNode create_dfMB(bool inputRisMassCut, TString nfin, ROOT::RDF::RNode dfSW)
{
    if (inputRisMassCut){
        return dfSW.Filter("massKK>5.3 && massKK<5.45").Redefine("weight","1");
    } else {
        RDataFrame dfMB("b2hh", nfin);
        return defineAll(dfMB);
    }
}

struct histConf {
    TString nvar;
    TString label;
    TString title;
    int Nbins;
    double vmin;
    double vmax;
    histConf(){};
    histConf(TString _nvar, TString _label, TString _title, 
             int _Nbins, double _vmin, double _vmax){
        nvar = _nvar;
        label = _label;
        title = _title;
        Nbins = _Nbins;
        vmin = _vmin;
        vmax = _vmax;
    };
};

vector<histConf> fillHistosList(){
    vector<histConf> var_list;
    var_list.emplace_back("massKK", "_massKK", "massKK; m(B^{0}_{s})", 100, 5.0, 6.2);
    var_list.emplace_back("massKKErr", "_massKKErr", "massKKErr; #sigma_{m}(B^{0}_{s})", 100, 0.014, 0.031);
    var_list.emplace_back("nPVs", "_nPVs", "nPVs; Number of PV", 9, 0.5, 9.5);
    var_list.emplace_back("nTracks", "_nTracks", "nTracks; Number of Tracks", 100, 0, 500);
    var_list.emplace_back("nSPDHits", "_nSPDHits", "nSPDHits; nSPDHits", 150, 0, 1000);
    var_list.emplace_back("tauKK", "_tauKK", "tauKK; tauKK [ps]", 150, 0, 8);
    var_list.emplace_back("tauKKErr", "_tauKKErr", "tauKKErr; tauKKErr [ps]", 150, 0, 0.1);
    var_list.emplace_back("tauKKCHI2", "_tauKKCHI2", "tauKKCHI2; tauKKCHI2", 150, 0, 15);
    var_list.emplace_back("logtauKKCHI2", "_logtauKKCHI2", "logtauKKCHI2; log(tauKKCHI2)", 150, 0, 15);
    var_list.emplace_back("t_noDTF", "_t_noDTF", "t_noDTF; t_noDTF [ps]", 150, 0, 8);
    var_list.emplace_back("DTFdiff", "_DTFdiff", "DTFdiff; DTFdiff [ps]", 150, -0.05, 0.05);
    var_list.emplace_back("bPT", "_bPT", "bPT; p_{T}(B_{s}^{0}) [GeV]", 100, 0, 25);
    var_list.emplace_back("bPL", "_bPL", "bPL; p_{L}(B_{s}^{0}) [GeV]", 100, 0, 300);
    var_list.emplace_back("bP", "_bP", "bP; p(B_{s}^{0}) [GeV]", 100, 0, 300);
    var_list.emplace_back("piplusPT", "_piplusPT", "piplusPT; p_{T}(#pi^{+}) [GeV]", 100, 0, 15);
    var_list.emplace_back("maxPT", "_maxPT", "maxPT; max[p_{T}(#pi^{+}),p_{T}(#pi^{-})] [GeV]", 150, 2, 18);
    var_list.emplace_back("minPT", "_minPT", "minPT; min[p_{T}(#pi^{+}),p_{T}(#pi^{-})] [GeV]", 150, 1, 11);
    var_list.emplace_back("sumPT", "_sumPT", "sumPT; p_{T}(#pi^{+})+p_{T}(#pi^{-}) [GeV]", 150, 4, 25);
    var_list.emplace_back("bPVx", "_bPVx", "bPVx; x(PV) [mm]", 200, 0.70, 0.95);
    var_list.emplace_back("bPVy", "_bPVy", "bPVy; y(PV) [mm]", 200, -0.3, 0.3);
    var_list.emplace_back("bPVz", "_bPVz", "bPVz; z(PV) [mm]", 200, -120, 120);
    var_list.emplace_back("bENDVx", "_bENDVx", "bENDVx; x(ENDV) [mm]", 100, -3, 4);
    var_list.emplace_back("bENDVy", "_bENDVy", "bENDVy; y(ENDV) [mm]", 150, -3, 3);
    var_list.emplace_back("bENDVz", "_bENDVz", "bENDVz; z(ENDV) [mm]", 150, -150, 150);
    var_list.emplace_back("bPVxErr", "_bPVxErr", "bPVxErr; #delta x(PV) [mm]", 150, 0, 0.025);
    var_list.emplace_back("bPVyErr", "_bPVyErr", "bPVyErr; #delta y(PV) [mm]", 150, 0, 0.025);
    var_list.emplace_back("bPVzErr", "_bPVzErr", "bPVzErr; #delta z(PV) [mm]", 200, 0, 0.15);
    var_list.emplace_back("bENDVxErr", "_bENDVxErr", "bENDVxErr; #delta x(ENDV) [mm]", 150, 0.004, 0.04);
    var_list.emplace_back("bENDVyErr", "_bENDVyErr", "bENDVyErr; #delta y(ENDV) [mm]", 150, 0.004, 0.04);
    var_list.emplace_back("bENDVzErr", "_bENDVzErr", "bENDVzErr; #delta z(ENDV) [mm]", 200, 0.02, 0.50);
    var_list.emplace_back("dx", "_dx", "dx; x(ENDV)-x(PV) [mm]", 150, -2, 2);
    var_list.emplace_back("dy", "_dy", "dy; y(ENDV)-y(PV) [mm]", 150, -2, 2);
    var_list.emplace_back("dz", "_dz", "dz; z(ENDV)-z(PV) [mm]", 150, 0, 40);
    var_list.emplace_back("logdz", "_logdz", "log(dz); log[z(ENDV)-z(PV) [mm]]", 150, -1, 5);
    var_list.emplace_back("rFD", "_rFD", "rFD; rFD [mm]", 100, 0, 4);
    var_list.emplace_back("rFDPV", "_rFDPV", "rFDPV; rFDPV [mm]", 100, 0, 4);
    var_list.emplace_back("bFD", "_bFD", "bFD; FD(B^{0}_{s})", 150, 0, 50);
    var_list.emplace_back("etaOS", "_etaOS", "etaOS; #eta_{OS}", 70, 0, 0.499);
    var_list.emplace_back("etaSSk", "_etaSSk", "etaSSk; #eta_{SSk}", 75, 0, 0.499);
    var_list.emplace_back("qOS", "_qOS", "qOS; q_{OS}", 3, -1.5, 1.5);
    var_list.emplace_back("qSSk", "_qSSk", "qSSk; q_{SSk}", 3, -1.5, 1.5);
    var_list.emplace_back("piplusETA", "_piplusETA", "piplusETA; #eta(#pi^{+})", 90, 1.5, 5);
    var_list.emplace_back("piplusPHI", "_piplusPHI", "piplusPHI; #phi(#pi^{+})", 90, -3.14159, 3.14159);
    var_list.emplace_back("bETA", "_bETA", "bETA; #eta(B^{0}_{s})", 100, 1.5, 5);
    var_list.emplace_back("bPHI", "_bPHI", "bPHI; #phi(B^{0}_{s})", 85, -3.14159, 3.14159);
    var_list.emplace_back("logPiplusIPCHI2", "_piplusIPCHI2", "piplusIPCHI2; log[#chi^{2}_{IP}(#pi^{+})]", 100, 2, 12);
    var_list.emplace_back("piplusTRACKCHI2", "_piplusTRACKCHI2", "piplusTRACKCHI2; #chi^{2}_{track}(#pi^{+})", 200, 0, 3);
    var_list.emplace_back("logBIPCHI2", "_bIPCHI2", "bIPCHI2; log[#chi^{2}_{IP}(B_{s}^{0})]", 100, -6, 3);
    var_list.emplace_back("logBFDCHI2", "_bFDCHI2", "bFDCHI2; log[#chi^{2}_{FD}(B_{s}^{0})]", 100, 4, 14);
    var_list.emplace_back("bDOCA", "_bDOCA", "bDOCA; DOCA(B^{0}_{s})", 100, 0, 0.1);
    var_list.emplace_back("bPVCHI2", "_bPVCHI2", "bPVCHI2; #chi^{2}_{PV}(B_{s}^{0})", 100, 0, 130);
    var_list.emplace_back("logBVTXCHI2", "_bVTXCHI2", "bVTXCHI2; log[#chi^{2}_{VTX}(B_{s}^{0})]", 100, -10, 3);
    var_list.emplace_back("acosBDIRA", "_bDIRA", "bDIRA; acos(B^{0}_{s} direction angle)", 100, 0, 0.015);
    var_list.emplace_back("bIP", "_bIP", "bIP; IP(B^{0}_{s})", 100, 0, 0.08);
    var_list.emplace_back("bIPCHI2overIP", "_bIPCHI2overIP", "bIPCHI2overIP; #chi^{2}_{IP}/IP (B^{0}_{s})", 100, 0, 350);
    var_list.emplace_back("logBIP2overIPCHI2", "_logBIP2overIPCHI2", "logBIP2overIPCHI2; log(IP^{2}/#chi^{2}_{IP}) (B^{0}_{s})", 100, -9.5, -6);
    var_list.emplace_back("logBFD2overFDCHI2", "_logBFD2overFDCHI2", "logBFD2overFDCHI2; log(FD^{2}/#chi^{2}_{FD}) (B^{0}_{s})", 100, -7, 0);
    var_list.emplace_back("piplusIP", "_piplusIP", "piplusIP; IP(#pi^{+})", 100, 0, 3);
    var_list.emplace_back("logPiplusGhostProb", "_piplusGhostProb", "piplusGhostProb; log[Ghost Prob. (#pi^{+})]", 200, -7, -1);
    var_list.emplace_back("piplusIPCHI2overIP", "_piplusIPCHI2overIP", "piplusIPCHI2overIP; #chi^{2}_{IP}/IP (#pi^{+})", 100, 0, 8000);
    var_list.emplace_back("logPiplusIP2overIPCHI2", "_logPiplusIP2overIPCHI2", "logPiplusIP2overIPCHI2; log(IP^{2}/#chi^{2}_{IP}) (#pi^{+})", 100, -10, -4);
    var_list.emplace_back("piplusDLLKPI", "_piplusDLLKPI", "piplusDLLKPI; DLLKPI (#pi^{+})", 200, 0, 100);
    var_list.emplace_back("piplusDLLPPI", "_piplusDLLPPI", "piplusDLLPPI; DLLPPI (#pi^{+})", 200, -100, 70);
    var_list.emplace_back("bdtKK", "_bdtKK", "bdtKK; bdtKK", 100, 0.08, 0.7);
    var_list.emplace_back("hhAngle", "_hhAngle", "hhAngle; hhAngle [grad]", 100, 0, 30);
    var_list.emplace_back("bTheta", "_btheta", "bTheta; #theta (B) [rad]", 100, 0, 0.300);
    var_list.emplace_back("piplusTheta", "_piplustheta", "piplusTheta; #theta (#pi^{+}) [rad]", 100, 0, 0.300);

    return var_list;
};

void setHistStyle(TH1D* h, int colour){
    h->SetLineColor(colour);
    h->SetMarkerColor(colour);
    h->SetMarkerStyle(0);
    TString name = h->GetName();
    if (!name.Contains("OS") && 
        !name.Contains("SS") && 
        !name.Contains("DLL") && 
        !name.Contains("nTracks"))
        h->GetXaxis()->SetRange(-1, h->GetNbinsX() + 1);
    h->Scale(1.0 / h->Integral());
}

TH1D* makeRatioHisto(TH1D* hNum, TH1D* hDen, int colour){
    TString name = hNum->GetName();
    TH1D* hRatio = new TH1D("hRatio_" + name, "hRatio_" + name,
                            hNum->GetXaxis()->GetNbins(),
                            hNum->GetXaxis()->GetXmin(),
                            hNum->GetXaxis()->GetXmax());
    hRatio->GetXaxis()->SetTitle("");
    hRatio->GetYaxis()->SetTitle("");
    hRatio->Add(hNum);
    hRatio->Divide(hDen);
    hRatio->SetMinimum(0.5);
    hRatio->SetMaximum(1.5);
    hRatio->SetLineColor(colour);
    hRatio->SetMarkerColor(colour);
    hRatio->SetMarkerStyle(0);
    return hRatio;
}

void makeCanvas(TH1D* hMC, TH1D* hSW, TH1D* hMB=0, TString outdir="./"){
    setHistStyle(hSW, kBlue);
    setHistStyle(hMC, kGreen+2);
    TH1D* hRatio = makeRatioHisto(hSW, hMC, kBlue);
    hRatio->GetYaxis()->SetTitle("DATA / MC");
    hRatio->GetXaxis()->SetLabelSize(0.15);
    hRatio->GetYaxis()->SetLabelSize(0.15);
    hRatio->GetYaxis()->SetTitleSize(0.15);
    hRatio->GetYaxis()->SetNdivisions(5,2,0,true);

    if (!(TString(hSW->GetName()).Contains("mass"))){
        hSW->SetMinimum(0);
        hMC->SetMinimum(0);
    }
    double tmpMax = max(hSW->GetMaximum(), hMC->GetMaximum());
    hSW->SetMaximum(tmpMax*1.05);
    hMC->SetMaximum(tmpMax*1.05);
    
    TH1D* hRatio2 = 0;
    if (hMB != 0){
        setHistStyle(hMB, kRed);
        hRatio2 = makeRatioHisto(hMB, hMC, kRed);
        if (!(TString(hSW->GetName()).Contains("mass")))
            hMB->SetMinimum(0);
        tmpMax = max(tmpMax, hMB->GetMaximum());
        hSW->SetMaximum(tmpMax*1.05);
        hMC->SetMaximum(tmpMax*1.05);
        hMB->SetMaximum(tmpMax*1.05);
    }

    TString name = TString(hSW->GetName()).ReplaceAll("h_SW_", "_");
    TCanvas canv("canv_"+name, "canv_"+name);
    canv.cd();
    canv.GetPad(0);
    TPad upperPad(name+"_upperPad",name+"_upperPad",0,0.2,1,1);
    upperPad.SetLeftMargin(0.2);
    upperPad.SetBottomMargin(0.15);
    upperPad.SetBorderSize(0);
    TPad lowerPad(name+"_lowerPad",name+"_lowerPad",0,0,1,0.2);
    lowerPad.SetLeftMargin(0.2);
    lowerPad.SetBorderSize(0);
    lowerPad.Draw();
    upperPad.Draw();
    upperPad.cd();
    hSW->DrawCopy("pe");
    if (hMB != 0) hMB->DrawCopy("pe same");
    hMC->DrawCopy("hist same");
    upperPad.SetGridx();
    upperPad.SetGridy();
    lowerPad.cd();
    hRatio->DrawCopy("e1");
    if (hRatio2 != 0) hRatio2->DrawCopy("e1 same");
    TLine l0(hRatio->GetXaxis()->GetXmin(), 1, hRatio->GetXaxis()->GetXmax(), 1);
    l0.SetLineColor(kBlack);
    l0.SetLineStyle(kSolid);
    l0.SetLineWidth(2);
    l0.DrawClone("same");
    lowerPad.SetGridx();
    lowerPad.SetGridy();
    canv.Draw();
    canv.SaveAs(Form("%s/%s.pdf", outdir.Data(), canv.GetName()));
    canv.SaveAs(Form("%s/%s.root",outdir.Data(), canv.GetName()));
    
    delete hRatio;
    if (hMB!=0) delete hRatio2;
}


int plotSeveralVars(TString nfin1, TString nfin2, TString nfin3 = "",
                    TString nfout = "output_compare.root", TString outDir = "./",
                    TString rew_var = "", TString selection="(1)")
{
    // EnableImplicitMT();                    // Tell ROOT you want to go parallel
    bool do_reweight = (rew_var != "");
    bool inputRisMassCut = (nfin3 == "");
    // Step 0-1: Import data and define new variables
    RDataFrame dfMC_0("b2hh", nfin1);
    RDataFrame dfSW_0("b2hh", nfin2);
    auto dfMC_1 = defineAll(dfMC_0).Filter(selection.Data());
    auto dfSW_1 = defineAll(dfSW_0).Filter(selection.Data());
    auto dfMB_1 = create_dfMB(inputRisMassCut, nfin3, dfSW_1).Filter(selection.Data());
    // Step 2: reweighting
    int Nbins = 0;
    double vmin = 0;
    double vmax = 0;
    if (rew_var == "log(bIP*bIP/bIPCHI2)"){
        Nbins = 150;
        vmin = -9.5;
        vmax = -6.0;
    } else if (rew_var == "log(bFDCHI2)"){
        Nbins = 100;
        vmin = 4;
        vmax = 14;
    }
    else if (rew_var == "log(bFD*bFD/bFDCHI2)"){
        Nbins = 100;
        vmin = -7;
        vmax =  0;
    } else if (rew_var == "tauKK"){
        Nbins = 150;
        vmin = 0.2;
        vmax = 14.2;
    }
    else if (rew_var == "tauKKErr"){
        Nbins = 150;
        vmin = 0.0;
        vmax = 0.1;
    } else if (rew_var == "hhAngle"){
        Nbins = 150;
        vmin = 2;
        vmax = 30;
    } else if (rew_var == "piplusTRACKCHI2"){
        Nbins = 150;
        vmin = 0;
        vmax = 3;
    }
    TH1D hR1 = getReweightHisto1D(dfSW_1, dfMC_1, "weight", rew_var,
                                  Nbins, vmin, vmax, "rewSW.root");
    TH1D hR2 = getReweightHisto1D(dfMB_1, dfMC_1, "weight", rew_var, 
                               Nbins, vmin, vmax, "rewMB.root");
    TH1D hR3 = getReweightHisto1D(dfMC_1, dfMC_1, "weight", rew_var, 
                               Nbins, vmin, vmax, "rewMB.root");
    auto dfSW = reweight1D(dfSW_1, &hR1, "weight", rew_var, "rewSW.root");
    auto dfMB = reweight1D(dfMB_1, &hR2, "weight", rew_var, "rewMB.root");
    auto dfMC = reweight1D(dfMC_1, &hR3, "weight", rew_var, "rewMC.root");

    vector<histConf> var_list = fillHistosList();
    gROOT->ProcessLine(".L ${B2HH_SRC}/Tools/lhcbStyle.C");
    gStyle->SetLabelSize(0.02, "x");
    gStyle->SetTitleSize(0.06, "x");
    gStyle->SetOptStat(0);

    // // from os import system
    system("mkdir -p "+outDir);

    dfSW.Describe().Print();  
    dfSW.Display("nPVs")->Print();
    dfSW.Display("reweight_var")->Print();
    if (dfSW.HasColumn("reweight")) printf("STOCAZZO\n");
    else printf("FANCULO\n");
    dfSW.Display("logPiplusIPCHI2")->Print();
    dfSW.Display("reweight")->Print();
    vector<vector<ROOT::RDF::RResultPtr<TH1D>>> allhists;
    for (auto opts : var_list){
        auto nvar = opts.nvar;
        auto hname = opts.label;
        auto htitle = opts.title;
        auto Nbins = opts.Nbins;
        auto vmin = opts.vmin;
        auto vmax = opts.vmax;
        cout << nvar.Data() << endl;
        auto hMC = dfMC.Histo1D<double>({TString("h_MC"+hname).Data(), TString("h_MC"+htitle).Data(), 
                                 Nbins, vmin, vmax}, 
                                 nvar.Data(), "reweight");
        auto hSW = dfSW.Histo1D<double>({TString("h_SW" + hname).Data(), TString("h_SW" + htitle).Data(),
                                         Nbins, vmin, vmax},
                                        nvar.Data(), "reweight");
        auto hMB = dfMB.Histo1D<double>({TString("h_MB" + hname).Data(), TString("h_MB" + htitle).Data(),
                                         Nbins, vmin, vmax},
                                        nvar.Data(), "reweight");
        vector<ROOT::RDF::RResultPtr<TH1D>> hists;
        hists.push_back(hMC);
        hists.push_back(hSW);
        hists.push_back(hMB);
        allhists.push_back(hists);
    }
    for (auto& hists : allhists){
        cout << hists[0]->GetName() << endl;
        makeCanvas(hists[0].GetPtr(),
                   hists[1].GetPtr(),
                   hists[2].GetPtr(),
                   outDir);
    }
    return 0;
}