#ifndef tool_TIMEBIASINFO_h
#define tool_TIMEBIASINFO_h

#include "TString.h"
#include <map>
#include "TH2D.h"
#include "TCanvas.h"
#include "TAxis.h"
using namespace std;

namespace timeBiasInfo {
    map<TString, TString> mapsFileNames_ZangdZ = {
        {"2015_MagUp",        "/home/LHCB-T3/dmanuzzi/B2HH/tests_bug2018/biasJpsi/plots/canv_ZangdZ_2016_MagUp_fitProfZ.root"},
        {"2016_MagUp",        "/home/LHCB-T3/dmanuzzi/B2HH/tests_bug2018/biasJpsi/plots/canv_ZangdZ_2016_MagUp_fitProfZ.root"},
        {"2017s29r2p2_MagUp", "/home/LHCB-T3/dmanuzzi/B2HH/tests_bug2018/biasJpsi/plots/canv_ZangdZ_2017_MagUp_fitProfZ.root"},
        {"2018_MagUp",        "/home/LHCB-T3/dmanuzzi/B2HH/tests_bug2018/biasJpsi/plots/canv_ZangdZ_2018_MagUp_fitProfZ.root"},
        
        {"2015_MagDown",        "/home/LHCB-T3/dmanuzzi/B2HH/tests_bug2018/biasJpsi/plots/canv_ZangdZ_2016_MagDw_fitProfZ.root"},
        {"2016_MagDown",        "/home/LHCB-T3/dmanuzzi/B2HH/tests_bug2018/biasJpsi/plots/canv_ZangdZ_2016_MagDw_fitProfZ.root"},
        {"2017s29r2p2_MagDown", "/home/LHCB-T3/dmanuzzi/B2HH/tests_bug2018/biasJpsi/plots/canv_ZangdZ_2017_MagDw_fitProfZ.root"},
        {"2018_MagDown",        "/home/LHCB-T3/dmanuzzi/B2HH/tests_bug2018/biasJpsi/plots/canv_ZangdZ_2018_MagDw_fitProfZ.root"},
    };
    TH1 *getMap(TString year, TString pol, TString infoType = "ZangdZ"){
        TH1* ret = 0;
        if (infoType == "ZangdZ"){
            TString tag = Form("%s_Mag%s", year.Data(), pol.Data());
            printf("************** tag: %s, map file name: %s\n", tag.Data(), timeBiasInfo::mapsFileNames_ZangdZ[tag].Data());
            TFile *fin = TFile::Open(timeBiasInfo::mapsFileNames_ZangdZ[tag], "READ");
            if (pol == "Down") pol = "Dw";
            if (year == "2017s29r2p2") year = "2017";
            if (year == "2015") year = "2016";
            tag = Form("%s_Mag%s", year.Data(), pol.Data());
            TCanvas *canv = (TCanvas *)fin->Get("canv_ZangdZ_" + tag + "_fitProfZ");
            canv->Print();
            ret = (TH2D*)canv->FindObject("ZangdZ_" + tag + "_fitProfZ");
            ret->SetDirectory(0);
            //h2->Print();
            //ret = (TH2D*)h2->Clone();
            fin->Close();
            ret->Print();
            return ret;
        } else return 0;
    };

    Double_t getTimeBias_ZangdZ(TH2D* h, Double_t &x, Double_t &y){
        TAxis* xaxis = h->GetXaxis();
        TAxis* yaxis = h->GetYaxis();
        if (x > xaxis->GetXmax()) return 0.;
        if (x < xaxis->GetXmin()) return 0.;
        if (y > yaxis->GetXmax()) return 0.;
        if (y < yaxis->GetXmin()) return 0.;
        Int_t ibin = h->FindBin(x,y);
        Double_t bias_mum = h->GetBinContent(ibin);
        return bias_mum / 299.792458; // [ps]
    }
    Double_t getZBias_ZangdZ(TH2D* h, Double_t &x, Double_t &y){
        TAxis* xaxis = h->GetXaxis();
        TAxis* yaxis = h->GetYaxis();
        if (x > xaxis->GetXmax()) return -9999.;
        if (x < xaxis->GetXmin()) return -9999.;
        if (y > yaxis->GetXmax()) return -9999.;
        if (y < yaxis->GetXmin()) return -9999.;
        Int_t ibin = h->FindBin(x,y);
        Double_t bias_mum = h->GetBinContent(ibin);
        return bias_mum/1000.; // [mm]
    }

}

#endif