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
  TString opts          = getOption(argc, argv, "-o", "_");
  if (opts == "_") opts = "";
  TString hypoPlus = "", hypoMinus = "",
          namePlus = "", nameMinus = ""; 
  Double_t timeErr = 0,   
           piplusP = 0, piplusETA = 0,
           piminusP = 0, piminusETA = 0, 
           bPT = 0, nSPDHits = 0, bETA = 0,
           weight = 0, weightPID = 0;
  TChain * chain = new TChain("b2hhW","b2hhW");
  chain->Add(Form("${B2HH_OUT}/sPlot/tuple_reduced/b2hh_%s_%g_%s_%s_%s.root",
                  decay.Data(),bdtCut,
                  year.Data(),magnet.Data(),
                  finalState.Data()));
  printf("READING FILE ${B2HH_OUT}/sPlot/tuple_reduced/b2hh_%s_%g_%s_%s_%s.root\n", decay.Data(), bdtCut, year.Data(), magnet.Data(), finalState.Data());
  chain->SetBranchAddress("timeErr", &timeErr);
  chain->SetBranchAddress("bPT",       &bPT);
  chain->SetBranchAddress("bETA",      &bETA);
  chain->SetBranchAddress("piplusP", &piplusP);
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
  // TH3D * hEffPlus3D; TH3D * hEffMinus3D;
  // TH2D * hEffPlus;   TH2D * hEffMinus;
  // TH1D * hTimeErr; 
  // TH1D * hPT;        TH1D * hSPD;
  // TH2D * hPT_SPD;
  finalState.ToLower();
  TFile *outFile = TFile::Open(Form("${B2HH_OUT}/TimeErr/templates/%s_%s_%g_%s_%s%s.root",
                                    finalState.Data(), decay.Data(), bdtCut, year.Data(), magnet.Data(),opts.Data()),
                               "RECREATE");
  std::vector<TString> channels = {"bdkpi","bskpi","bdpipi","bspipi","bskk","bdkk","lbpk","lbppi"};
  std::vector<TH1D> v_hTimeErr, v_hPT, v_hSPD;
  std::vector<TH2D> v_hPT_SPD;
  std::vector<TH3D*> v_hEffPlus3D, v_hEffMinus3D;
  std::vector<TH2D*> v_hEffPlus, v_hEffMinus;
  Int_t Nchannels = (Int_t)channels.size();
  for(auto channel: channels) {

    printf("PREPARING HISTOGRAMS FOR %s\n",channel.Data());

    if(channel=="bdkpi")  { namePlus = "Kplus";  nameMinus = "PIminus"; }
    if(channel=="bskpi")  { namePlus = "Kplus";  nameMinus = "PIminus"; }
    if(channel=="bdpipi") { namePlus = "PIplus"; nameMinus = "PIminus"; }
    if(channel=="bspipi") { namePlus = "PIplus"; nameMinus = "PIminus"; }
    if(channel=="bskk")   { namePlus = "Kplus";  nameMinus = "Kminus";  }
    if(channel=="bdkk")   { namePlus = "Kplus";  nameMinus = "Kminus";  }
    if(channel=="lbpk")   { namePlus = "Pplus";  nameMinus = "Kminus";  }
    if(channel=="lbppi")  { namePlus = "Pplus";  nameMinus = "PIminus";  }

    v_hTimeErr .emplace_back(Form("h_%s_timeErr",channel.Data()),Form("h_%s_timeErr",channel.Data()),
                            70,0,0.1);
    v_hPT      .emplace_back(Form("h_%s_PT",channel.Data()),Form("h_%s_PT",channel.Data()),50,0,50);
    v_hSPD     .emplace_back(Form("h_%s_SPD",channel.Data()),Form("h_%s_SPD",channel.Data()),20,0,1000);
    v_hPT_SPD  .emplace_back(Form("h_%s_PT_SPD",channel.Data()),
                             Form("h_%s_PT_SPD",channel.Data()),50,0,50,20,0,1000);
    v_hEffPlus3D .push_back((TH3D *) filePlus->Get(Form("hEff%s_is%s",namePlus.Data(),hypoPlus.Data())));
    v_hEffMinus3D.push_back((TH3D *) fileMinus->Get(Form("hEff%s_is%s",nameMinus.Data(),hypoMinus.Data())));
    v_hEffPlus .push_back((TH2D *) v_hEffPlus3D.back()->Project3D("yx"));
    v_hEffMinus.push_back((TH2D *) v_hEffMinus3D.back()->Project3D("yx"));
  }
  
  for(Int_t iEntry = 0, nEntries = chain->GetEntries(); iEntry < nEntries; ++iEntry) {
    weightPID = 0;
    chain->GetEntry(iEntry);
    
    if (opts.Contains("lowbETA") && bETA>3) continue;
    if (opts.Contains("highETA") && bETA<3) continue;
    
    for (Int_t i=0; i<Nchannels; ++i){
      weightPID = v_hEffPlus[i]->Interpolate(piplusP,piplusETA)*
                  v_hEffMinus[i]->Interpolate(piminusP,piminusETA);
      v_hTimeErr[i].Fill(timeErr,weight*weightPID);
      v_hPT[i].Fill(bPT,weight*weightPID);
      v_hSPD[i].Fill(nSPDHits,weight*weightPID);
      v_hPT_SPD[i].Fill(bPT,nSPDHits,weight*weightPID);
    }
  }
  printf("STOCAZZO\n");
  for (Int_t i=0; i<Nchannels; ++i){
    v_hTimeErr[i].Sumw2();
    v_hTimeErr[i].Smooth(1,"r");
    v_hTimeErr[i].Scale(1./v_hTimeErr[i].Integral("width"));
    v_hPT[i].Sumw2();
    v_hPT[i].Scale(1./v_hPT[i].Integral("width"));
    v_hSPD[i].Sumw2();
    v_hSPD[i].Scale(1./v_hSPD[i].Integral("width"));
    v_hPT_SPD[i].Sumw2();
    v_hPT_SPD[i].Scale(1./v_hPT_SPD[i].Integral("width"));

    shiftToZero(&(v_hTimeErr[i]));
    outFile->WriteTObject(&(v_hTimeErr[i]),"","Overwrite");
    outFile->WriteTObject(&(v_hPT[i]),"","Overwrite");
    outFile->WriteTObject(&(v_hSPD[i]),"","Overwrite");
    outFile->WriteTObject(&(v_hPT_SPD[i]),"","Overwrite");
  }

  outFile->ls();
  filePlus->Close();
  filePlus->Close();
  outFile->Close();
  return 0;

}
