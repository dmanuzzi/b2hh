#ifndef BIASMAPTOOLS_h
#define BIASMAPTOOLS_h
#include <map>
#include <vector>
#include <utility>
#include <algorithm>

#include "TString.h"
#include "TFile.h"
#include "TChain.h"
#include "TH2D.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooGaussian.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "TAxis.h"
#include "TPad.h"
#include "TROOT.h"
#include "TStyle.h"
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace RooFit;

class biasMapTools {
    private:
        

        TString m_tag_data;
        TString m_tag_test;
        TString m_tag_data_test;
        vector<TString> m_tag_vars;
        Int_t m_Nvars;
        
        vector<vector<Double_t>> m_binnings;
        vector<Int_t> m_Nbins;
        Int_t m_NbinsTot;

        vector<Double_t> m_sumX; 
        vector<Double_t> m_sumX2;
        vector<Int_t> m_countBin;

        Int_t tmp_bin;
        vector<Int_t> tmp_bins;

        vector<Double_t> m_meanBin;
        vector<Double_t> m_meanErrBin;
        vector<Double_t> m_rmsBin;

    public:
        biasMapTools();
        static TString nfin_path_Jpsi;
        static map<TString, vector<TString>> tag_nfins_Jpsi;

        vector<Double_t> vars;
        vector<TH1D *> v_h_var;

        map<TString, vector<TH2D *>> v_h_slice2D;
        

        Double_t minTime; // ps
        Double_t maxTime; // ps
        // RooRealVar time("time", "time", biasMap::minTime, biasMap::maxTime, "ps");
        
        biasMapTools(TString tag_test, TString tag_data, vector<TString> tag_vars,
                     vector<vector<Double_t>> binnings);
        
        static void ActivateAndSetBranch(TTree *tin, TString nbranch, void *var);
        static vector<Double_t>    makeBins            (int Nbins, double binMin, double binMax);
        static Int_t               getBin              (vector<Int_t> &bins, vector<Int_t> &Nbins);
        static vector<Int_t>       getBinIndices       (Int_t ibin, vector<Int_t> &Nbins);
        
        Int_t               getBin1D        (Double_t &val, Int_t iVar);
        vector<Int_t>       getBinND        (vector<Double_t> &vals);
        Int_t               getBin          (vector<Int_t> &bins);
        vector<Int_t>       getBinIndices   (Int_t ibin);
        vector<Double_t>    getBinCenter    (Int_t ibin);
        Int_t               getNvars();

        void                updateSumX      (Int_t iBin, Double_t &val) { m_sumX[iBin] += val; }
        void                updateSumX2     (Int_t iBin, Double_t &val) { m_sumX2[iBin] += val*val; }
        void                updateEntries   (Int_t iBin) { m_countBin[iBin] += 1; }
        void                fill            (Double_t &val);
        void                draw_vars       (TString pathOut = "./", TString opt = "norm");
        void                draw_distrib2D_slice(TString tag, vector<TString> nvars_toPlot, 
                                                 TString pathOut = "./", TString opt = "");
        Int_t               getVarIndex     (TString nvar);
        void                calcProfiles    (Int_t minEntries = 50);

        void                exportBiasMaps  (TString pathOut = "./");

        biasMapTools(TString tag_test, TString tag_data, vector<TString> tag_vars,
                     TString nfin);
        void                importBiasMaps  (TString nfin);
        Double_t            getBias();
        Double_t            getBiasErr();
};


#endif

