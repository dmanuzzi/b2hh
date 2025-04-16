#include <iostream>
#include "TChain.h"
#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include <vector>
#include <utility>
#include <algorithm>
#include "config_datasets.h"
using namespace std;


int addVariables(TString nfin_sw, vector<TString> nfins_data, TString nfout){
    TChain tin_sw("b2hhW", "b2hhW");
    tin_sw.Add(nfin_sw);
    
    Double_t runNumber_sw, eventNumber_sw, mass_sw, time_sw(0.), weight_sw;
    tin_sw.SetBranchAddress("runNumber_d", &runNumber_sw);
    tin_sw.SetBranchAddress("eventNumber_d", &eventNumber_sw);
    tin_sw.SetBranchAddress("mass", &mass_sw);
    tin_sw.SetBranchAddress("time", &time_sw);
    tin_sw.SetBranchAddress("weight", &weight_sw);

    vector<vector<Double_t>> info_sw;
    Long64_t nentries_sw = tin_sw.GetEntries();
    info_sw.reserve(nentries_sw);
    vector<Double_t> tmp_info_sw(5,0);
    for (Long64_t ientry=0; ientry<nentries_sw; ++ientry){
        tin_sw.GetEntry(ientry);
        tmp_info_sw[0] = runNumber_sw;
        tmp_info_sw[1] = eventNumber_sw;
        tmp_info_sw[2] = mass_sw;
        tmp_info_sw[3] = time_sw;
        tmp_info_sw[4] = weight_sw;
        info_sw.push_back(tmp_info_sw);
    }
    Double_t eps = 1.0e-4;
    // for_each(info_sw.begin(), info_sw.begin() + 10, [](vector<Double_t> v)
    //          { printf("------------- %.0f    %.0f \n", v[0], v[1]); });

    auto compareVectPair = [](vector<double> v1, vector<double> v2){
        return (v1[0] != v2[0]) ? (v1[0] < v2[0]) : (v1[1] < v2[1]);
    };
    sort(info_sw.begin(), info_sw.end(), compareVectPair);
    // for_each(info_sw.begin(), info_sw.begin() + 10, [](vector<Double_t> v)
    //          { printf("++++++++++++++ %.0f    %.0f \n", v[0], v[1]); });

    TChain tin_data("b2hh", "b2hh");
    for (TString nfin_data : nfins_data)
        tin_data.Add(nfin_data);
    // tin_data.SetBranchStatus("*",0);
    // tin_data.SetBranchStatus("runNumber", 1);
    // tin_data.SetBranchStatus("eventNumber", 1);
    // tin_data.SetBranchStatus("massKK", 1);
    // tin_data.SetBranchStatus("tauKK", 1);
    UInt_t runNumber;
    ULong64_t eventNumber;
    Double_t massKK, tauKK, tauKKErr;
    Int_t Year;
    tin_data.SetBranchAddress("runNumber", &runNumber);
    tin_data.SetBranchAddress("eventNumber", &eventNumber);
    tin_data.SetBranchAddress("massKK", &massKK);
    tin_data.SetBranchAddress("tauKK", &tauKK);
    tin_data.SetBranchAddress("tauKKErr", &tauKKErr);
    tin_data.SetBranchAddress("Year", &Year);
    vector<pair<Long64_t, Double_t>> found_entries;
    found_entries.reserve(nentries_sw);
    auto it_info = info_sw.begin();
    auto it_info_begin = info_sw.begin();
    auto it_info_end = info_sw.end();
    vector<Double_t> to_find(2,0.);
    Long64_t nentries_data = tin_data.GetEntries();
    TFile fout(nfout, "RECREATE");
    tin_data.SetBranchStatus("*",1);
    TTree *tout = (TTree *)tin_data.CloneTree(0);
    Double_t weight;
    Double_t time;
    Double_t timeErr;
    Int_t p=2, fState=0;
    tout->Branch("weight", &weight, "weight/D");
    tout->Branch("time", &time, "time/D");
    tout->Branch("timeErr", &timeErr, "timeErr/D");
    tout->Branch("p", &p, "p/I");
    tout->Branch("fState", &fState, "fState/I");

    for (Long64_t ientry=0; ientry<nentries_data; ++ientry){
        tin_data.GetEntry(ientry);
        if (ientry%100000 == 0) printf("at entry %lld\n", ientry);
        to_find[0] = runNumber;
        to_find[1] = eventNumber;
        it_info = lower_bound(it_info_begin, it_info_end, to_find, compareVectPair);
        while ((it_info != it_info_end) && (it_info->at(0) == runNumber) && (it_info->at(1) == eventNumber))
        {
            if ((it_info->at(2) != massKK) || (it_info->at(3) != tauKK)) {
                ++it_info;
                continue;
            }
            found_entries.push_back(make_pair(ientry,it_info->at(4)));
            weight = it_info->at(4);
            time = tauKK;
            timeErr = tauKKErr;
            p = 2;
            TString nYear;
            if (Year == 2017) 
                nYear = "2017s29r2p2";
            else if (Year == 2015 || Year == 2016)
                nYear = "201516";
            else 
                nYear = Form("%d",Year);
            p = datasetFlags::spectrumKK;
            fState = datasetFlags::yearFlags[nYear] + datasetFlags::spectrumKK;
            tout->Fill();
            break;
        }
        // if (tout->GetEntries()>100) break;
    }
    UInt_t Nfound = found_entries.size();
    printf("Found %u candidates out of %lld (%.3f)\n", Nfound, nentries_sw, (double)Nfound/(double)nentries_sw); 
    // printf("Start saving output file\n");

    // TFile fout(nfout, "RECREATE");
    // tin_data.SetBranchStatus("*",1);
    // TTree *tout = (TTree *)tin_data.CloneTree(0);
    // Double_t weight;
    // tout->Branch("weight", &weight, "weight/D");
    // for (auto& pentry : found_entries){
    //     tin_data.GetEntry(pentry.first);
    //     weight = pentry.second;
    //     tout->Fill();
    // }
    fout.WriteTObject(tout, "b2hh");
    fout.ls();
    fout.Close();
    return 1;
}

// printf("WARNING! candidate with runNumber: %u, eventNumber: %llu not found!\n", runNumber, eventNumber);
// continue;
