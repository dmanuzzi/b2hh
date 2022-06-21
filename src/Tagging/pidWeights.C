#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TMVA/Reader.h>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TH3D.h>
#include <TH2D.h>
#include <TH1D.h>
#include <optionParser.h>
#include <makePull.h>
#include <TROOT.h>
#include "TRandom.h"
using namespace std;




int main(int argc, char * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./reduce [options]\n");
    printf("Options:\n");
    printf("  -d <decay>      : name of the decay used to optimise BDT (default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = -1)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2015,2016,Tot], default = Tot)\n");
    printf("  -f <finalState> : final state hypothesis ([KPI,PIPI,KK], default = PIPI)\n");
    printf("  -c <pidCut>     : PID requirements (default = -2.3.-2.3)\n");
    return 0;
  }

  TString decay         = getOption(argc,argv,"-d","bdpipi");
  Double_t bdtCut       = atof(getOption(argc,argv,"-b","-1"));
  TString magnet        = getOption(argc,argv,"-m","Tot");
  TString year          = getOption(argc,argv,"-y","Tot");
  TString finalState    = getOption(argc,argv,"-f","pipi");
  TString pidCut        = getOption(argc,argv,"-c","-2.3.-2.3");

  TString hypoPlus = "", hypoMinus = "",
          namePlus = "", nameMinus = ""; 
  Double_t etaOS = 0,   
           piplusP = 0, piplusETA = 0,
           piminusP = 0, piminusETA = 0, 
           bPT = 0, nSPDHits = 0, 
           weight = 0, weightPID = 0;
  TChain * chain = new TChain("b2hhW","b2hhW");
  chain->Add(Form("${B2HH_OUT}/sPlot/tuple_reduced/b2hh_%s_%g_%s_%s_%s.root",
                  decay.Data(),bdtCut,
                  year.Data(),magnet.Data(),
                  finalState.Data()));
  printf("READING FILE ${B2HH_OUT}/sPlot/tuple_reduced/b2hh_%s_%g_%s_%s_%s.root\n", decay.Data(), bdtCut, year.Data(), magnet.Data(), finalState.Data());
  chain->SetBranchAddress("etaOS",     &etaOS);
  chain->SetBranchAddress("bPT",       &bPT);
  chain->SetBranchAddress("piplusP",   &piplusP);
  chain->SetBranchAddress("piplusETA", &piplusETA);
  chain->SetBranchAddress("piminusP",  &piminusP);
  chain->SetBranchAddress("piminusETA",&piminusETA);
  chain->SetBranchAddress("nSPDHits",  &nSPDHits);
  chain->SetBranchAddress("weight",    &weight);

  if(finalState=="PIPI") { hypoPlus = "PI"; hypoMinus = "PI"; }
  if(finalState=="KPI")  { hypoPlus = "K";  hypoMinus = "PI"; }
  if(finalState=="KK")   { hypoPlus = "K";  hypoMinus = "K";  }

  TString cutPlus1  = ((TObjString *)pidCut.Tokenize('.')->At(0))->String();
  TString cutPlus2  = ((TObjString *)pidCut.Tokenize('.')->At(1))->String();
  TString cutMinus1 = ((TObjString *)pidCut.Tokenize('.')->At(2))->String();
  TString cutMinus2 = ((TObjString *)pidCut.Tokenize('.')->At(3))->String();

  TFile * filePlus  = TFile::Open(Form("${B2HH_OUT}/PID/effCalib/TrackEff/eff%s_%s.%s_71_10_1_6_%s_%s.root",
                                       hypoPlus.Data(),cutPlus1.Data(),cutPlus2.Data(),
                                       magnet.Data(),year.Data()),
                                  "READ");
  TFile *fileMinus = TFile::Open(Form("${B2HH_OUT}/PID/effCalib/TrackEff/eff%s_%s.%s_71_10_1_6_%s_%s.root",
                                      hypoMinus.Data(), cutMinus1.Data(), cutMinus2.Data(),
                                      magnet.Data(), year.Data()),
                                 "READ");
  TH3D * hEffPlus3D; TH3D * hEffMinus3D;
  TH2D * hEffPlus;   TH2D * hEffMinus;
  TH1D * hEtaOS; 
  TH1D * hPT;        TH1D * hSPD;
  TH2D * hPT_SPD;
  finalState.ToLower();
  TFile *outFile = TFile::Open(Form("${B2HH_OUT}/Tagging/templates/%s_%s_%g_%s_%s.root",
                                    finalState.Data(), decay.Data(), bdtCut, year.Data(), magnet.Data()),
                               "RECREATE");
  std::vector<TString> channels = {"bdkpi","bskpi","bdpipi","bspipi","bskk","bdkk","lbpk","lbppi"};
  for(auto channel: channels) {

    printf("WRITING HISTOGRAMS FOR %s\n",channel.Data());

    if(channel=="bdkpi")  { namePlus = "Kplus";  nameMinus = "PIminus"; }
    if(channel=="bskpi")  { namePlus = "Kplus";  nameMinus = "PIminus"; }
    if(channel=="bdpipi") { namePlus = "PIplus"; nameMinus = "PIminus"; }
    if(channel=="bspipi") { namePlus = "PIplus"; nameMinus = "PIminus"; }
    if(channel=="bskk")   { namePlus = "Kplus";  nameMinus = "Kminus";  }
    if(channel=="bdkk")   { namePlus = "Kplus";  nameMinus = "Kminus";  }
    if(channel=="lbpk")   { namePlus = "Pplus";  nameMinus = "Kminus";  }
    if(channel=="lbppi")  { namePlus = "Pplus";  nameMinus = "PIminus";  }

    hEtaOS   = new TH1D(Form("h_%s_etaOS",channel.Data()),Form("h_%s_etaOS",channel.Data()),
                        50,0,0.5);
    hPT      = new TH1D(Form("h_%s_PT",channel.Data()),Form("h_%s_PT",channel.Data()),50,0,50);
    hSPD     = new TH1D(Form("h_%s_SPD",channel.Data()),Form("h_%s_SPD",channel.Data()),20,0,1000);
    hPT_SPD  = new TH2D(Form("h_%s_PT_SPD",channel.Data()),
                        Form("h_%s_PT_SPD",channel.Data()),50,0,50,20,0,1000);
    hEffPlus3D  = (TH3D *) filePlus->Get(Form("hEff%s_is%s",namePlus.Data(),hypoPlus.Data()));
    hEffMinus3D = (TH3D *) fileMinus->Get(Form("hEff%s_is%s",nameMinus.Data(),hypoMinus.Data()));
    hEffPlus    = (TH2D *) hEffPlus3D->Project3D("yx");
    hEffMinus   = (TH2D *) hEffMinus3D->Project3D("yx");

    for(Int_t iEntry = 0, nEntries = chain->GetEntries(); iEntry < nEntries; ++iEntry) {

      weightPID = 0;
      chain->GetEntry(iEntry);

      weightPID = hEffPlus->Interpolate(piplusP,piplusETA)*
                  hEffMinus->Interpolate(piminusP,piminusETA);
      //hEtaOS->Fill(etaOS,weight*weightPID);
      hEtaOS->Fill(gRandom->Uniform(0,0.5));
      hPT->Fill(bPT, weight * weightPID);
      hSPD->Fill(nSPDHits,weight*weightPID);
      hPT_SPD->Fill(bPT,nSPDHits,weight*weightPID);
    }

    hEtaOS->Sumw2();
    hEtaOS->Smooth(1,"r");
    hEtaOS->Scale(1./hEtaOS->Integral("width"));
    hPT->Sumw2();
    hPT->Scale(1./hPT->Integral("width"));
    hSPD->Sumw2();
    hSPD->Scale(1./hSPD->Integral("width"));
    hPT_SPD->Sumw2();
    hPT_SPD->Scale(1./hPT_SPD->Integral("width"));

    shiftToZero(hEtaOS);
    outFile->WriteTObject(hEtaOS,"","Overwrite");
    outFile->WriteTObject(hPT,"","Overwrite");
    outFile->WriteTObject(hSPD,"","Overwrite");
    outFile->WriteTObject(hPT_SPD,"","Overwrite");
    delete hEtaOS; delete hPT; delete hSPD; delete hPT_SPD;

  }
  delete hEffPlus3D; delete hEffMinus3D; delete hEffPlus; delete hEffMinus;
  filePlus->Close();
  filePlus->Close();
  outFile->Close();
  return 0;

}
