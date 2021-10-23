#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <TROOT.h>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TRandom3.h>
#include <TH2D.h>
#include <TH3D.h>
#include <RooFit.h>
#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooKeysPdf.h>
#include <RooWorkspace.h>
#include <optionParser.h>
#include <algorithm>
#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>

using namespace std;
using namespace RooFit;

Bool_t fiducialFlag(Double_t P, Double_t ETA) {

  double m1 = 0;                  double q1 = 2;
  double m2 = (3.75-2)/(120-25);  double q2 = 2 - m2*25;
  double m3 = (6-3.75)/(135-120); double q3 = 3.75 - m3*120;

  bool ret = (ETA > P*m1+q1 && P<=25)||
             (ETA > P*m2+q2 && P>25 && P<=120)||
             (ETA > P*m3+q3 && P>120);
  return ret;

}

int main(int argc, char * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./create [options]\n");
    printf("Options:\n");
    printf("  -d <decay>      : name of the decay used to optimise BDT ([PIPI,KK], default = PIPI)\n");
    printf("  -f <finalState> : final state hypothesis (default = pipi)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = -1)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2015,2016,2017,2018,201516,20151618,Tot], default = Tot)\n");
    return 0;
  }

  TString decay         = getOption(argc,argv,"-d","PIPI");
  TString finalState    = getOption(argc,argv,"-f","pipi");
  Double_t bdtCut       = atof(getOption(argc,argv,"-b","-1"));
  TString magnet        = getOption(argc,argv,"-m","Tot");
  TString year          = getOption(argc,argv,"-y","Tot");

  printf("EXECUTING ./create -d %s -f %s -b %g -m %s -y %s\n",
         decay.Data(),finalState.Data(),bdtCut,magnet.Data(),year.Data());

  Double_t mpi = phys::mpi, mk = phys::mk, mp = phys::mp;
  Double_t mPlus   = 0,  mMinus    = 0;
  TString hypoPlus = "", hypoMinus = "";
  TString namePlus = "", nameMinus = "";
  if(finalState=="kpi")  { mPlus = mk;  mMinus = mpi; hypoPlus = "K";  hypoMinus = "PI"; }
  if(finalState=="pik")  { mPlus = mpi; mMinus = mk;  hypoPlus = "PI"; hypoMinus = "K";  }
  if(finalState=="pipi") { mPlus = mpi; mMinus = mpi; hypoPlus = "PI"; hypoMinus = "PI"; }
  if(finalState=="kk")   { mPlus = mk;  mMinus = mk;  hypoPlus = "K";  hypoMinus = "K";  }
  if(finalState=="pk")   { mPlus = mp;  mMinus = mk;  hypoPlus = "P";  hypoMinus = "K";  }
  if(finalState=="kp")   { mPlus = mk;  mMinus = mp;  hypoPlus = "K";  hypoMinus = "P";  }
  if(finalState=="ppi")  { mPlus = mp;  mMinus = mpi; hypoPlus = "P";  hypoMinus = "PI"; }
  if(finalState=="pip")  { mPlus = mpi; mMinus = mp;  hypoPlus = "PI"; hypoMinus = "P";  }

  TString decays[12] = {"bdpipi","bdkpi","bdpik","bdkk",
                        "bskk","bskpi","bspik","bspipi",
                        "lbpk","lbkp","lbppi","lbpip" };
  TString tmpDecay;
  Double_t truePPlus = 0, truePMinus = 0, truePP = 0,
           piplusP = 0, piplusETA = 0, 
           piminusP = 0, piminusETA = 0,
           trueMass = 0, Weight = 0,
           BDT = 0;
  TChain * inChain = new TChain("inChain");

  Int_t nEntries;

  TTree * outTree;

  std::vector<std::pair<Double_t,Int_t>> totEntries(0);
  TRandom3 rand(192837465);

  RooRealVar *mass = new RooRealVar("mass", "mass", sPlot_cuts::templates_massMin,
                                                    sPlot_cuts::templates_massMax);
  mass->setBins(10000,"cache");

  RooDataSet * data;
  RooKeysPdf * pdf;

  RooWorkspace * outWS = new RooWorkspace("Templates","Templates");


  for(Int_t iDecay = 0; iDecay < 12; iDecay++) {

    if(iDecay > 0) { delete pdf; delete data;
                     outTree->Reset(); inChain->Reset(); }

    outTree = new TTree("outTree","outTree");
    outTree->SetDirectory(0);
    outTree->Branch("mass",  &trueMass);
    outTree->Branch("weight",&Weight  );

    tmpDecay = decays[iDecay];

    if(tmpDecay=="bdkpi")  { namePlus   = "Kplus";  nameMinus   = "PIminus";  }
    if(tmpDecay=="bdpik")  { namePlus   = "PIplus"; nameMinus   = "Kminus";   }
    if(tmpDecay=="bdpipi") { namePlus   = "PIplus"; nameMinus   = "PIminus";  }
    if(tmpDecay=="bdkk")   { namePlus   = "Kplus";  nameMinus   = "Kminus";   }
    if(tmpDecay=="bskpi")  { namePlus   = "Kplus";  nameMinus   = "PIminus";  }
    if(tmpDecay=="bspik")  { namePlus   = "PIplus"; nameMinus   = "Kminus";   }
    if(tmpDecay=="bspipi") { namePlus   = "PIplus"; nameMinus   = "PIminus";  }
    if(tmpDecay=="bskk")   { namePlus   = "Kplus";  nameMinus   = "Kminus";   }
    if(tmpDecay=="lbpk")   { namePlus   = "Pplus";  nameMinus   = "Kminus";   }
    if(tmpDecay=="lbkp")   { namePlus   = "Kplus";  nameMinus   = "Pminus";   }
    if(tmpDecay=="lbppi")  { namePlus   = "Pplus";  nameMinus   = "PIminus";  }
    if(tmpDecay=="lbpip")  { namePlus   = "PIplus"; nameMinus   = "Pminus";   }

    
    auto tag_years = datasetFlags::chain_years[year];
    auto tag_magnet = datasetFlags::chain_magnet[magnet];
    chainAdder::chainAdder(inChain, "${B2HH_OUT}/Data/tuple_merged/%s_%s_%s.root/b2hh",
                           tmpDecay, tag_years, tag_magnet);

    inChain->SetBranchStatus(Form("bdt%s",decay.Data()),1); inChain->SetBranchAddress(Form("bdt%s",decay.Data()),&BDT);
    inChain->SetBranchStatus("piplusP",    1); inChain->SetBranchAddress("piplusP",    &piplusP   );
    inChain->SetBranchStatus("piplusETA",  1); inChain->SetBranchAddress("piplusETA",  &piplusETA );
    inChain->SetBranchStatus("piminusP",   1); inChain->SetBranchAddress("piminusP",   &piminusP  );
    inChain->SetBranchStatus("piminusETA", 1); inChain->SetBranchAddress("piminusETA", &piminusETA);
    inChain->SetBranchStatus("truePPlus",  1); inChain->SetBranchAddress("truePPlus",  &truePPlus );
    inChain->SetBranchStatus("truePMinus", 1); inChain->SetBranchAddress("truePMinus", &truePMinus);
    inChain->SetBranchStatus("truePP",     1); inChain->SetBranchAddress("truePP",     &truePP    );
    nEntries = inChain->GetEntries();
    for(Int_t iEntry = 0; iEntry < nEntries; ++iEntry) {
      inChain->GetEntry(iEntry);
      if(BDT<bdtCut) continue;
      totEntries.push_back(std::make_pair(rand.Uniform(0,1),iEntry));
    }
    std::sort(totEntries.begin(),totEntries.end());
  
    std::sort(totEntries.begin(), totEntries.begin()+5000, [](const std::pair<Double_t,Int_t> &left, const std::pair<Double_t,Int_t> &right) {
                                                        return left.second < right.second;
                                                      });
    for(Int_t iEntry = 0; iEntry < 5000; ++iEntry) {

      inChain->GetEntry(totEntries[iEntry].second);

      trueMass = sqrt(mPlus*mPlus+mMinus*mMinus+
                      2*(sqrt((mPlus*mPlus+truePPlus)*(mMinus*mMinus+truePMinus))-truePP));

      trueMass/=1000;

      outTree->Fill();
   
    }

    totEntries.clear();

    data = new RooDataSet(Form("data_%s",tmpDecay.Data()),Form("data_%s",tmpDecay.Data()),
                          outTree,RooArgSet(*mass));
    pdf  = new RooKeysPdf(Form("%s_%s",tmpDecay.Data(),finalState.Data()),
                          Form("%s_%s",tmpDecay.Data(),finalState.Data()),
                          *mass,*data,RooKeysPdf::MirrorLeft,2);

    outWS->import(*pdf);

  }

  outWS->writeToFile(Form("${B2HH_OUT}/sPlot/template/Templates_%s_%g_%s_%s.root",
                          decay.Data(),bdtCut,year.Data(),magnet.Data()),
                     kTRUE);

  return 0;
}
