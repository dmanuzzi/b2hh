#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include "TString.h"
#include "TFile.h"
#include "TChain.h"
#include "TList.h"

TTree* selTree(TString nfin, int N, int seed=0, 
                int force_fState=0, bool skip_fromBc=false){
    TChain* c = new TChain("c", "c");
    c->Add(nfin);
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
    std::for_each(v_sel.begin(), v_sel.begin() + N, [](int &v)
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

    
    for (int ientry=0; ientry<Nentries; ++ientry){
        if (v_sel[ientry] != 1) continue;
        c->GetEntry(ientry);
        fState = force_fState;
	if (fromBc==1) printf("STOCAZZO\n");
        tout->Fill();
    }
    return tout;
}

int mixTuples(TString nfin1, int N1, //only fromBc
              TString nfin2, int N2, //normal MC
              TString nfout, TString ntout,
              int shuffle = 0,
              int force_fState = 0)
{
    TList *list = new TList;
    TTree *tout1 = selTree(nfin1, N1, (shuffle!=0 ? 1 : 0), force_fState, false);
    tout1->SetName("input1");
    TTree *tout2 = selTree(nfin2, N2, (shuffle!=0 ? 2 : 0), force_fState, true);
    tout1->SetName("input2");
    list->Add(tout1);
    list->Add(tout2);
    TTree* tout = TTree::MergeTrees(list);
    tout->Print();
    tout->SetName(ntout);
    TFile *fout = new TFile(nfout, "RECREATE");
    fout->WriteTObject(tout, ntout);
    fout->ls();
    fout->Close();
    return 1;
}
