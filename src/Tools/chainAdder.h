#ifndef tool_CHAINADDER_h
#define tool_CHAINADDER_h
#include "TChain.h"
#include "TString.h"
#include <vector>
#include <fstream>
using namespace std;

namespace chainAdder {
    Int_t chainAdder(TChain *chain, 
                     TString nfinTemplate, 
                     TString decay, 
                     vector<TString> years, 
                     vector<TString> magnets){
        for (TString tmpYear : years){
            for (TString tmpMagnet : magnets){
                TString tmpnfin = Form(nfinTemplate.Data(), 
                                       decay.Data(), tmpYear.Data(), tmpMagnet.Data());
                // TString testnfin = tmpnfin.ReplaceAll("\/b2hh", "");
                // ifstream f(testnfin.Data());
                // if (!f.good()){
                //     printf("chainAdder : File %s not found\n", tmpnfin.Data());
                //     return 0;
                // } 
                chain->Add(tmpnfin);
            }
        }
        return 1;
    };
};

#endif