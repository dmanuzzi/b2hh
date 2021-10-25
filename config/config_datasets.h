#ifndef config_DATASETS_h
#define config_DATASETS_h

#include <iostream>
#include <map>
#include <vector>
#include <utility>
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
    const Int_t spectrumKK   =  2;

    std::map<TString, Int_t> spectrumFlags = {
        {"PIPI", spectrumPIPI},
        {"KPI", spectrumKPI},
        {"PIK", spectrumPIK},
        {"KK", spectrumKK},
    };
};

namespace bdtWeights {
  std::map<TString, std::vector<std::pair<TString,TString>>> bdtPIPI = {
    {"2015", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bdpipi_Tot_201516/weights/BDT1_BDT.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bdpipi_Tot_201516/weights/BDT2_BDT.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bdpipi_Tot_201516/weights/BDT3_BDT.weights.xml"},
      }},
    {"2016", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bdpipi_Tot_201516/weights/BDT1_BDT.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bdpipi_Tot_201516/weights/BDT2_BDT.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bdpipi_Tot_201516/weights/BDT3_BDT.weights.xml"},
      }},
    {"2017s29r2p2", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bdpipi_Tot_2017s29r2p2/weights/BDT1_BDT.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bdpipi_Tot_2017s29r2p2/weights/BDT2_BDT.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bdpipi_Tot_2017s29r2p2/weights/BDT3_BDT.weights.xml"},
      }},
    {"2018", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bdpipi_Tot_2017s29r2p2/weights/BDT1_BDT.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bdpipi_Tot_2017s29r2p2/weights/BDT2_BDT.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bdpipi_Tot_2017s29r2p2/weights/BDT3_BDT.weights.xml"},
      }},
  };
  std::map<TString, std::vector<std::pair<TString,TString>>> bdtgPIPI = {
    {"2015", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bdpipi_Tot_201516/weights/BDT1_BDTG.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bdpipi_Tot_201516/weights/BDT2_BDTG.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bdpipi_Tot_201516/weights/BDT3_BDTG.weights.xml"},
      }},
    {"2016", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bdpipi_Tot_201516/weights/BDT1_BDTG.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bdpipi_Tot_201516/weights/BDT2_BDTG.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bdpipi_Tot_201516/weights/BDT3_BDTG.weights.xml"},
      }},
    {"2017s29r2p2", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bdpipi_Tot_2017s29r2p2/weights/BDT1_BDTG.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bdpipi_Tot_2017s29r2p2/weights/BDT2_BDTG.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bdpipi_Tot_2017s29r2p2/weights/BDT3_BDTG.weights.xml"},
      }},
    {"2018", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bdpipi_Tot_2017s29r2p2/weights/BDT1_BDTG.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bdpipi_Tot_2017s29r2p2/weights/BDT2_BDTG.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bdpipi_Tot_2017s29r2p2/weights/BDT3_BDTG.weights.xml"},
      }},
  };
  std::map<TString, std::vector<std::pair<TString,TString>>> bdtKK = {
    {"2015", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bskk_Tot_201516/weights/BDT1_BDT.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bskk_Tot_201516/weights/BDT2_BDT.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bskk_Tot_201516/weights/BDT3_BDT.weights.xml"},
      }},
    {"2016", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bskk_Tot_201516/weights/BDT1_BDT.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bskk_Tot_201516/weights/BDT2_BDT.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bskk_Tot_201516/weights/BDT3_BDT.weights.xml"},
      }},
    {"2017s29r2p2", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bskk_Tot_2017s29r2p2/weights/BDT1_BDT.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bskk_Tot_2017s29r2p2/weights/BDT2_BDT.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bskk_Tot_2017s29r2p2/weights/BDT3_BDT.weights.xml"},
      }},
    {"2018", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bskk_Tot_2017s29r2p2/weights/BDT1_BDT.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bskk_Tot_2017s29r2p2/weights/BDT2_BDT.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bskk_Tot_2017s29r2p2/weights/BDT3_BDT.weights.xml"},
      }},
  };
  std::map<TString, std::vector<std::pair<TString,TString>>> bdtgKK = {
    {"2015", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bskk_Tot_201516/weights/BDT1_BDTG.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bskk_Tot_201516/weights/BDT2_BDTG.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bskk_Tot_201516/weights/BDT3_BDTG.weights.xml"},
      }},
    {"2016", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bskk_Tot_201516/weights/BDT1_BDTG.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bskk_Tot_201516/weights/BDT2_BDTG.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bskk_Tot_201516/weights/BDT3_BDTG.weights.xml"},
      }},
    {"2017s29r2p2", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bskk_Tot_2017s29r2p2/weights/BDT1_BDTG.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bskk_Tot_2017s29r2p2/weights/BDT2_BDTG.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bskk_Tot_2017s29r2p2/weights/BDT3_BDTG.weights.xml"},
      }},
    {"2018", {
	{"BDT1", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset1_bskk_Tot_2017s29r2p2/weights/BDT1_BDTG.weights.xml"},
	{"BDT2", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset2_bskk_Tot_2017s29r2p2/weights/BDT2_BDTG.weights.xml"},
	{"BDT3", "/home/LHCB-T3/dmanuzzi/B2HH/Selection.new/dataset3_bskk_Tot_2017s29r2p2/weights/BDT3_BDTG.weights.xml"},
      }},
  };
};
/*
namespace bdtWeights {
    std::map<TString, std::vector<std::pair<TString,TString>>> bdtPIPI = {
        {"2015", {
                     {"BDT1_PIPI", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bdpipi.weights.xml"},
                     {"BDT2_PIPI", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bdpipi.weights.xml"},
                     {"BDT3_PIPI", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bdpipi.weights.xml"},
                 }},
        {"2016", {
                     {"BDT1_PIPI", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bdpipi.weights.xml"},
                     {"BDT2_PIPI", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bdpipi.weights.xml"},
                     {"BDT3_PIPI", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bdpipi.weights.xml"},
                 }},
        {"2017s29r2p2", {
                            {"BDT1_PIPI", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bdpipi.weights.xml"},
                            {"BDT2_PIPI", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bdpipi.weights.xml"},
                            {"BDT3_PIPI", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bdpipi.weights.xml"},
                        }},
        {"2018", {
                     {"BDT1_PIPI", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bdpipi.weights.xml"},
                     {"BDT2_PIPI", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bdpipi.weights.xml"},
                     {"BDT3_PIPI", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bdpipi.weights.xml"},
                 }},
    };
    std::map<TString, std::vector<std::pair<TString, TString>>> bdtKK = {
        {"2015", {
                     {"BDT1_KK", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bskk.weights.xml"},
                     {"BDT2_KK", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bskk.weights.xml"},
                     {"BDT3_KK", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bskk.weights.xml"},
                 }},
        {"2016", {
                     {"BDT1_KK", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bskk.weights.xml"},
                     {"BDT2_KK", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bskk.weights.xml"},
                     {"BDT3_KK", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bskk.weights.xml"},
                 }},
        {"2017s29r2p2", {
                            {"BDT1_KK", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bskk.weights.xml"},
                            {"BDT2_KK", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bskk.weights.xml"},
                            {"BDT3_KK", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bskk.weights.xml"},
                        }},
        {"2018", {
                     {"BDT1_KK", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bskk.weights.xml"},
                     {"BDT2_KK", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bskk.weights.xml"},
                     {"BDT3_KK", "/home/LHCB-T3/dmanuzzi/B2HH/Data/weights/BDT1_bskk.weights.xml"},
                 }},
    };
};
*/
#endif
