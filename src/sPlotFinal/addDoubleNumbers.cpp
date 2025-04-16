#include <iostream>
#include "TTree.h"
#include "TString.h"
#include "TFile.h"
#include "TBranch.h"

int addDoubleNumbers(TString nfin, TString nfout){
    ULong64_t eventNumber;
    UInt_t runNumber;
    Double_t eventNumber_d;
    Double_t runNumber_d;
    TFile fin(nfin, "READ");
    TTree* tin = (TTree*)fin.Get("b2hh");
    tin->SetBranchAddress("eventNumber", &eventNumber);
    tin->SetBranchAddress("runNumber", &runNumber);
    TFile fout(nfout, "RECREATE");
    TTree* tout = (TTree*)tin->CloneTree(0);
    tout->Branch("eventNumber_d", &eventNumber_d, "eventNumber_d/D");
    tout->Branch("runNumber_d", &runNumber_d, "runNumber_d/D");

    for (Long64_t i=0; i<tin->GetEntries(); ++i){
        tin->GetEntry(i);
        eventNumber_d = (Double_t)eventNumber;
        runNumber_d = (Double_t)runNumber;
        tout->Fill();
    }
    fout.WriteTObject(tout, "b2hh");
    fout.ls();
    fout.Close();
    fin.Close();
    return 1;
}