#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include "TString.h"
#include "TFile.h"
#include "TChain.h"
#include "TList.h"

TTree* selTree(TString nfin, int N, int seed=0, 
                int force_fState=0, bool skip_fromBc=false,
                int Nmax = 61100){
    TChain* c = new TChain("c", "c");
    c->Add(nfin);
    if (N == 0){
        TTree *tout = c->CloneTree(0);
        return tout;
    }
    int Nentries = c->GetEntries();
    
    std::vector<int> v_fromBc(Nentries, 0);
    int fromBc = 0;
    if (skip_fromBc){
        int count = 0;
        c->SetBranchStatus("*", 0);
        c->SetBranchStatus("fromBc", 1);
	    c->SetBranchAddress("fromBc", &fromBc);
        for (int ientry = 0; ientry < Nentries; ++ientry){
            c->GetEntry(ientry);
            if (fromBc == 1){
                v_fromBc[ientry] = 1;
	        	count += 1;
	        }
        }
        c->SetBranchStatus("*", 1);
	    printf("skip fromBc: %d candidates found\n",count);
    }

    std::vector<int> v_sel(Nentries, 0);
    assert(N <= Nentries);
    std::for_each(v_sel.begin(), v_sel.begin() + min(Nmax,Nentries), [](int &v)
                  { v = 1; });
    if (seed != 0){
        // std::random_device rd;
        std::mt19937 g(seed);
        // std::shuffle(v_sel.begin(), v_sel.begin() + (v_sel.size() - 1), g);
        std::shuffle(v_sel.begin(), v_sel.end(), g);
    }
    if (skip_fromBc){
        for (int i=0; i<Nentries; ++i){
            if (v_fromBc[i]==1 && v_sel[i]==1){
                v_sel[i]=0;
                for (int j = 0; j<Nentries; ++j){
                    if (v_sel[j]!=1 && v_fromBc[j]!=1) {
                        v_sel[j] = 1;
                        break;
                    }
                }
            }
        }
    }

    
    TTree *tout = c->CloneTree(0);
    int fState = 0;
    if (force_fState != 0)
        tout->SetBranchAddress("fState", &fState);

    // ofstream myfile;
    // myfile.open(Form("example_%d_%d.txt",skip_fromBc?1:2,N));
    int count = 0;
    for (int ientry=0; ientry<Nentries; ++ientry){
        if (v_sel[ientry] != 1) continue;
        c->GetEntry(ientry);
        fState = force_fState;
	    // if (fromBc==1) printf("STOCAZZO\n");
        tout->Fill();
        // myfile << ientry << "\n";
        count+=1;
        if (count >= N) break;
    }
    // myfile.close();

    return tout;
}

int mixTuples(TString nfin1, int N1, //only fromBc
              TString nfin2, int N2, //normal MC
              TString nfout, TString ntout,
              int shuffle = 0,
              int force_fState = 0)
{
    TList *list = new TList;
    TTree *tout1 = selTree(nfin1, N1, (shuffle!=0 ? 1+force_fState : 0), force_fState, false);
    tout1->SetName("input1");
    tout1->Print();
    TTree *tout2 = selTree(nfin2, N2, (shuffle!=0 ? 2+force_fState : 0), force_fState, true);
    tout2->SetName("input2");
    tout2->Print();
    if (N1!=0) list->Add(tout1);
    if (N2!=0) list->Add(tout2);
    TTree* tout = TTree::MergeTrees(list);
    tout->Print();
    tout->SetName(ntout);
    TFile *fout = new TFile(nfout, "RECREATE");
    fout->WriteTObject(tout, ntout);
    fout->ls();
    fout->Close();
    return 1;
}

int injectFromBc(){
    TString nfinFromBc  = "${B2HH_OUT}/Reduce/bskk_kk_KK_0.1_Tot_Kine_fromBc.root/b2hh";
    TString nfin_201516 = "${B2HH_OUT}/AccSignal/kineWeight/bskk_kk_KK_0.1_201516_Tot_Kine.root/b2hh";
    TString nfin_2017 = "${B2HH_OUT}/AccSignal/kineWeight/bskk_kk_KK_0.1_2017s29r2p2_Tot_Kine.root/b2hh";
    TString nfin_2018 = "${B2HH_OUT}/AccSignal/kineWeight/bskk_kk_KK_0.1_2018_Tot_Kine.root/b2hh";
    mixTuples(nfinFromBc, 0, nfin_201516, 61000,
              "${B2HH_OUT}/Reduce/bskk_kk_KK_0.1_201516_Tot_Kine_0.000fromBc.root",
              "b2hh", 1, 202);
    mixTuples(nfinFromBc, 9150, nfin_201516, 51850,
              "${B2HH_OUT}/Reduce/bskk_kk_KK_0.1_201516_Tot_Kine_0.150fromBc.root",
              "b2hh", 1, 202);
    
    mixTuples(nfinFromBc, 0, nfin_2017, 61000,
              "${B2HH_OUT}/Reduce/bskk_kk_KK_0.1_2017s29r2p2_Tot_Kine_0.000fromBc.root",
              "b2hh", 1, 22);
    mixTuples(nfinFromBc, 9150, nfin_2017, 5185,
              "${B2HH_OUT}/Reduce/bskk_kk_KK_0.1_2017s29r2p2_Tot_Kine_0.150fromBc.root",
              "b2hh", 1, 22);
    
    mixTuples(nfinFromBc, 0, nfin_2018, 61000,
              "${B2HH_OUT}/Reduce/bskk_kk_KK_0.1_2018_Tot_Kine_0.000fromBc.root",
              "b2hh", 1, 32);
    mixTuples(nfinFromBc, 9150, nfin_2018, 5185,
              "${B2HH_OUT}/Reduce/bskk_kk_KK_0.1_2018_Tot_Kine_0.150fromBc.root",
              "b2hh", 1, 32);
    
    return 1;
}