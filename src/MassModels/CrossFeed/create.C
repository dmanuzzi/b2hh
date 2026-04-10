#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
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
    printf("  -c <cut>        : pid cuts depending on final state (default = -3.5.-3.5)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = -1)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([201516,2017s29r2p2,2018], default = 201516)\n");
    printf("  -F <effNoFid>   : efficiencies out of fiductial region (pk_kp_ppi_pip, default = 0_0_0_0)\n");
    return 0;
  }

  TString decay         = getOption(argc,argv,"-d","");
  TString finalState    = getOption(argc,argv,"-f","");
  TString cuts          = getOption(argc,argv,"-c","");
  Int_t pidPlus1        = atoi(((TObjString *)cuts.Tokenize('.')->At(0))->String());
  Int_t pidPlus2        = atoi(((TObjString *)cuts.Tokenize('.')->At(1))->String());
  Int_t pidMinus1       = atoi(((TObjString *)cuts.Tokenize('.')->At(2))->String());
  Int_t pidMinus2       = atoi(((TObjString *)cuts.Tokenize('.')->At(3))->String());
  Double_t bdtCut       = atof(getOption(argc,argv,"-b",""));
  TString magnet        = getOption(argc,argv,"-m","");
  TString year          = getOption(argc,argv,"-y","");
  TString fiducialEff   = getOption(argc,argv,"-F","0_0_0_0");
  Double_t effNoFiducialPK  = atof((((TObjString *)fiducialEff.Tokenize('_')->At(0))->String()));
  Double_t effNoFiducialKP  = atof((((TObjString *)fiducialEff.Tokenize('_')->At(1))->String()));
  Double_t effNoFiducialPPI = atof((((TObjString *)fiducialEff.Tokenize('_')->At(2))->String()));
  Double_t effNoFiducialPIP = atof((((TObjString *)fiducialEff.Tokenize('_')->At(3))->String()));

  printf("EXECUTING ./create -d %s -f %s -c %d.%d.%d.%d -b %g -m %s -y %s -F %g_%g_%g_%g\n",
         decay.Data(),finalState.Data(),pidPlus1,pidPlus2,pidMinus1,pidMinus2,
         bdtCut,magnet.Data(),year.Data(),effNoFiducialPK,effNoFiducialKP,effNoFiducialPPI,effNoFiducialPIP);

  Double_t mpi = 139.57018, mk = 493.677, mp = 938.272030;
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
           piplusDLLKPI = 0, piplusDLLPPI = 0,
           piminusDLLKPI = 0, piminusDLLPPI = 0,
           trueMass = 0, Weight = 0,
           BDT = 0;
  TChain * inChain = new TChain("inChain");

  Int_t nEntries;

  TTree * outTree;

  std::vector<std::pair<Double_t,Int_t>> totEntries(0);
  TRandom3 rand(192837465);

  TFile * effFilePlus; TFile * effFileMinus;
  TH3D * hEffPlus; TH3D * hEffMinus;
  TH2D * hEffPlus2D; TH2D * hEffMinus2D;

  RooRealVar * mass = new RooRealVar("mass","mass",4.5,6.7);
  mass->setBins(10000,"cache");

  RooRealVar * weight = new RooRealVar("weight","weight",-1e6,1e6);
  RooDataSet * data = nullptr; 
  RooKeysPdf * pdf = nullptr;

  RooWorkspace * outWS = new RooWorkspace(Form("%s_%s_%g_%d.%d.%d.%d",
                                               finalState.Data(),decay.Data(),
                                               bdtCut,pidPlus1,pidPlus2,pidMinus1,pidMinus2),
                                          Form("%s_%s_%g_%d.%d.%d.%d",
                                               finalState.Data(),decay.Data(),
                                               bdtCut,pidPlus1,pidPlus2,pidMinus1,pidMinus2));
  for(Int_t iDecay = 0; iDecay < 12; iDecay++) {
    printf("iDecay %d\n",iDecay);

    if(iDecay > 0) { delete pdf; delete data;
                     outTree->Reset(); inChain->Reset();
                     effFilePlus->Close(); effFileMinus->Close(); }

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

    effFilePlus  = TFile::Open(Form("${B2HH_OUT}/PID/effCalib/TrackEff/eff%s_%d.%d_71_10_1_6_%s_%s.root",
                                    hypoPlus.Data(),pidPlus1,pidPlus2,magnet.Data(),year.Data()),"READ");
    effFileMinus = TFile::Open(Form("${B2HH_OUT}/PID/effCalib/TrackEff/eff%s_%d.%d_71_10_1_6_%s_%s.root",
                                    hypoMinus.Data(),pidMinus1,pidMinus2,magnet.Data(),year.Data()),"READ");
    hEffPlus     = (TH3D *) effFilePlus->Get(Form("hEff%s_is%s",namePlus.Data(),hypoPlus.Data()));
    hEffMinus    = (TH3D *) effFileMinus->Get(Form("hEff%s_is%s",nameMinus.Data(),hypoMinus.Data()));
    hEffPlus2D   = (TH2D *) hEffPlus->Project3D("yx");
    hEffMinus2D  = (TH2D *) hEffMinus->Project3D("yx");

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
    inChain->SetBranchStatus("piplusDLLKPI",1); inChain->SetBranchAddress("piplusDLLKPI",&piplusDLLKPI);
    inChain->SetBranchStatus("piplusDLLPPI",1); inChain->SetBranchAddress("piplusDLLPPI",&piplusDLLPPI);
    inChain->SetBranchStatus("piminusDLLKPI",1); inChain->SetBranchAddress("piminusDLLKPI",&piminusDLLKPI);
    inChain->SetBranchStatus("piminusDLLPPI",1); inChain->SetBranchAddress("piminusDLLPPI",&piminusDLLPPI);
    inChain->Print();
    nEntries = inChain->GetEntries();
    for(Int_t iEntry = 0; iEntry < nEntries; ++iEntry) {
      inChain->GetEntry(iEntry);
      if(BDT<bdtCut) continue;
      //if(piplusDLLKPI > 3 && piplusDLLKPI-piplusDLLPPI > -5 &&
      //   piminusDLLKPI < -3 && piminusDLLPPI < 5)  
      totEntries.push_back(std::make_pair(rand.Uniform(0,1),iEntry)); 
    }

    Int_t sizeEntries = min((Int_t) totEntries.size(),5000);
    std::sort(totEntries.begin(),totEntries.end());
  
    std::sort(totEntries.begin(), totEntries.begin()+sizeEntries, [](const std::pair<Double_t,Int_t> &left, const std::pair<Double_t,Int_t> &right) {
                                                        return left.second < right.second;
                                                      });
    printf("STOCAZZO %d\n",(Int_t) totEntries.size());
    for(Int_t iEntry = 0; iEntry < sizeEntries; ++iEntry) {

      inChain->GetEntry(totEntries[iEntry].second);

      trueMass = sqrt(mPlus*mPlus+mMinus*mMinus+
                      2*(sqrt((mPlus*mPlus+truePPlus)*(mMinus*mMinus+truePMinus))-truePP));

      trueMass/=1000;

      Weight = hEffPlus2D->Interpolate(piplusP,piplusETA)*
               hEffMinus2D->Interpolate(piminusP,piminusETA);
      /*
      if     (decay == "lbpk"  && !fiducialFlag(piplusP,piplusETA))
        Weight = effNoFiducialPK;
      else if(decay == "lbkp"  && !fiducialFlag(piminusP,piminusETA))
        Weight = effNoFiducialKP;
      else if(decay == "lbppi" && !fiducialFlag(piplusP,piplusETA))
        Weight = effNoFiducialPPI;
      else if(decay == "lbpip" && !fiducialFlag(piminusP,piminusETA))
        Weight = effNoFiducialPIP;
      */
      //Weight = 1; 
      outTree->Fill();
    }
    totEntries.clear();

    data = new RooDataSet(Form("data_%s",tmpDecay.Data()),Form("data_%s",tmpDecay.Data()),
                          outTree,RooArgSet(*mass,*weight),"","weight");
    pdf  = new RooKeysPdf(Form("%s_%s",tmpDecay.Data(),finalState.Data()),
                          Form("%s_%s",tmpDecay.Data(),finalState.Data()),
                          *mass,*data,RooKeysPdf::MirrorLeft,1);

    outWS->import(*pdf);
    outWS->import(*data);

  }

  outWS->writeToFile(Form("${B2HH_OUT}/MassModels/CrossFeed/%s_%s_%g_%d.%d.%d.%d_%s_%s.root",
                          finalState.Data(),decay.Data(),bdtCut,
                          pidPlus1,pidPlus2,pidMinus1,pidMinus2,magnet.Data(),year.Data()),
                     kTRUE);

  effFilePlus->Close(); effFileMinus->Close(); 

  return 0;
}
