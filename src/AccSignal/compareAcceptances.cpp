#include <iostream> 
using namespace std;


int compareAcceptances(TString nfin1, TString nfin2){
    TFile *fin1 = new TFile(nfin1, "READ");
    TFile *fin2 = new TFile(nfin2, "READ");
    TString suffix1 = (nfin1.Contains("NewT") ? "NewT" : "NewU");
    TString suffix2 = (nfin2.Contains("NewT") ? "NewT" : "NewU");
    TGraphErrors* acc1 = (TGraphErrors*)fin1->Get(Form("acc_bskk_%s",suffix1.Data()));
    TGraphErrors* acc2 = (TGraphErrors*)fin2->Get(Form("acc_bskk_%s",suffix2.Data()));
    acc1->SetLineColor(kBlue);
    acc2->SetLineColor(kRed);
    acc1->SetLineWidth(2);
    acc2->SetLineWidth(2);
    TCanvas *c1 = new TCanvas();
    acc1->Draw("AL");
    acc2->Draw("L same");
    return 1;
}