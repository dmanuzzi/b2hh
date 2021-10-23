#ifndef config_DATASETS_h
#define config_DATASETS_h

#include <iostream>
#include <map>
#include <vector>
#include <TString.h>

namespace datasetFlags {
    std::map<TString, Int_t> yearFlags = {
        {"2015",          0},
        {"2016",         10},
        {"2017",         20},
        {"2017s29r2p2",  20},
        {"2018",         30},
        {"Tot",         100},
        {"201516",      200},
        {"20151618",    300},
        {"201718",      400},
    };
    std::map<TString, std::vector<TString>> chain_years = {
        {"2015"       , {"2015"}},
        {"2016"       , {"2016"}},
        {"2017"       , {"2017"}},
        {"2017s29r2p2", {"2017s29r2p2"}},
        {"2018"       , {"2018"}},
        {"201516"     , {"2015", "2016"}},
        {"Tot"        , {"2015", "2016", "2017s29r2p2", "2018"}},
        {"20151618"   , {"2015", "2016", "2018"}},
        {"201718"     , {"2017s29r2p2", "2018"}},
    };

    std::map<TString, std::vector<TString>> chain_magnet = {
        {"Up"  , {"Up"}},
        {"Down", {"Down"}},
        {"Tot" , {"Up", "Down"}},
    };

    const Int_t spectrumPIPI =  0;
    const Int_t spectrumKPI  =  1;
    const Int_t spectrumPIK  = -1;
    const Int_t spectrumKK   =  1;

    std::map<TString, Int_t> spectrumFlags = {
        {"PIPI", spectrumPIPI},
        {"KPI", spectrumKPI},
        {"PIK", spectrumPIK},
        {"KK", spectrumKK},
    };
};

namespace bdtWeights {
    std::map<TString, std::vector<TString>> bdtPIPI = {
        {"2015", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bdpipi_-2.3.-2.3_Tot_201516/weights/BDT1_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bdpipi_-2.3.-2.3_Tot_201516/weights/BDT2_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bdpipi_-2.3.-2.3_Tot_201516/weights/BDT3_BDT.weights.xml"}},
        {"2016", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bdpipi_-2.3.-2.3_Tot_201516/weights/BDT1_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bdpipi_-2.3.-2.3_Tot_201516/weights/BDT2_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bdpipi_-2.3.-2.3_Tot_201516/weights/BDT3_BDT.weights.xml"}},
        {"2017s29r2p2", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bdpipi_-2.3.-2.3_Tot_2017s29r2p2/weights/BDT1_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bdpipi_-2.3.-2.3_Tot_2017s29r2p2/weights/BDT2_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bdpipi_-2.3.-2.3_Tot_2017s29r2p2/weights/BDT3_BDT.weights.xml"}},
        {"2018", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bdpipi_-2.3.-2.3_Tot_2018/weights/BDT1_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bdpipi_-2.3.-2.3_Tot_2018/weights/BDT2_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bdpipi_-2.3.-2.3_Tot_2018/weights/BDT3_BDT.weights.xml"}},
    };
    std::map<TString, std::vector<TString>> bdtgPIPI = {
        {"2015", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bdpipi_-2.3.-2.3_Tot_201516/weights/BDT1_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bdpipi_-2.3.-2.3_Tot_201516/weights/BDT2_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bdpipi_-2.3.-2.3_Tot_201516/weights/BDT3_BDTG.weights.xml"}},
        {"2016", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bdpipi_-2.3.-2.3_Tot_201516/weights/BDT1_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bdpipi_-2.3.-2.3_Tot_201516/weights/BDT2_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bdpipi_-2.3.-2.3_Tot_201516/weights/BDT3_BDTG.weights.xml"}},
        {"2017s29r2p2", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bdpipi_-2.3.-2.3_Tot_2017s29r2p2/weights/BDT1_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bdpipi_-2.3.-2.3_Tot_2017s29r2p2/weights/BDT2_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bdpipi_-2.3.-2.3_Tot_2017s29r2p2/weights/BDT3_BDTG.weights.xml"}},
        {"2018", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bdpipi_-2.3.-2.3_Tot_2018/weights/BDT1_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bdpipi_-2.3.-2.3_Tot_2018/weights/BDT2_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bdpipi_-2.3.-2.3_Tot_2018/weights/BDT3_BDTG.weights.xml"}},
    };
    std::map<TString, std::vector<TString>> bdtKK = {
        {"2015", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bskk_2.-2.2.-2_Tot_201516/weights/BDT1_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bskk_2.-2.2.-2_Tot_201516/weights/BDT2_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bskk_2.-2.2.-2_Tot_201516/weights/BDT3_BDT.weights.xml"}},
        {"2016", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bskk_2.-2.2.-2_Tot_201516/weights/BDT1_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bskk_2.-2.2.-2_Tot_201516/weights/BDT2_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bskk_2.-2.2.-2_Tot_201516/weights/BDT3_BDT.weights.xml"}},
        {"2017s29r2p2", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bskk_2.-2.2.-2_Tot_2017s29r2p2/weights/BDT1_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bskk_2.-2.2.-2_Tot_2017s29r2p2/weights/BDT2_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bskk_2.-2.2.-2_Tot_2017s29r2p2/weights/BDT3_BDT.weights.xml"}},
        {"2018", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bskk_2.-2.2.-2_Tot_2018/weights/BDT1_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bskk_2.-2.2.-2_Tot_2018/weights/BDT2_BDT.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bskk_2.-2.2.-2_Tot_2018/weights/BDT3_BDT.weights.xml"}},
    };
    std::map<TString, std::vector<TString>> bdtgKK = {
        {"2015", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bskk_2.-2.2.-2_Tot_201516/weights/BDT1_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bskk_2.-2.2.-2_Tot_201516/weights/BDT2_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bskk_2.-2.2.-2_Tot_201516/weights/BDT3_BDTG.weights.xml"}},
        {"2016", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bskk_2.-2.2.-2_Tot_201516/weights/BDT1_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bskk_2.-2.2.-2_Tot_201516/weights/BDT2_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bskk_2.-2.2.-2_Tot_201516/weights/BDT3_BDTG.weights.xml"}},
        {"2017s29r2p2", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bskk_2.-2.2.-2_Tot_2017s29r2p2/weights/BDT1_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bskk_2.-2.2.-2_Tot_2017s29r2p2/weights/BDT2_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bskk_2.-2.2.-2_Tot_2017s29r2p2/weights/BDT3_BDTG.weights.xml"}},
        {"2018", {"/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1/bskk_2.-2.2.-2_Tot_2018/weights/BDT1_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2/bskk_2.-2.2.-2_Tot_2018/weights/BDT2_BDTG.weights.xml", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3/bskk_2.-2.2.-2_Tot_2018/weights/BDT3_BDTG.weights.xml"}},
    };
};

#endif