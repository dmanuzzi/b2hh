#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <optionParser.h>
#include <makePull.h>
#include <vector>
#include <map>
#include "TRandom.h"
using namespace std;

Double_t getOmega(Double_t &eta, Double_t &p0, Double_t &p1, Double_t &etaHat) {

  Double_t w = p0 + p1*(eta-etaHat);
  return w;

}
void combineTaggers(Int_t &qTot, Double_t &etaTot,
                    std::vector<Int_t> &q, std::vector<Double_t> &eta,
                    std::vector<Double_t> &p0, std::vector<Double_t> &p1, std::vector<Double_t> &etaHat) {

  qTot = 0; etaTot = 0;
  Double_t pB = 1, pBbar = 1, w = 0;

  ULong64_t nTaggers = q.size();
  if(eta.size() != nTaggers || p0.size() != nTaggers ||
     p1.size()  != nTaggers || etaHat.size() != nTaggers) { printf("Some input has wrong size\n"); return; }

  for(ULong64_t i = 0; i < nTaggers; ++i) {

    w = getOmega(eta[i],p0[i],p1[i],etaHat[i]);
    pB    *= (q[i] == 1)*(1-w) + (q[i] ==-1)*w + (q[i] == 0)*0.5;
    pBbar *= (q[i] ==-1)*(1-w) + (q[i] == 1)*w + (q[i] == 0)*0.5;

  }

  pB = pB/(pB+pBbar);

  if     (pB == 0.5) { etaTot = 0.5;  qTot =  0; }
  else if(pB >  0.5) { etaTot = 1-pB; qTot =  1; }
  else               { etaTot = pB;   qTot = -1; }

}

Int_t main(Int_t argc, Char_t * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./reduce [options]\n");
    printf("Options:\n");
    printf("  -d <decay>      : name of the decay used to optimise BDT (default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = -1)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2015,2016,Tot], default = Tot)\n");
    printf("  -f <finalState> : final state hypothesis ([kpi,pipi,kk], default = pipi)\n");
    printf("  -c <flavour>    : final state hypothesis ([bddpi,bsdspi], default = bddpi)\n");
    return 0;
  }

  TString decay         = getOption(argc,argv,"-d","bdpipi");
  Double_t bdtCut       = atof(getOption(argc,argv,"-b","-1"));
  TString magnet        = getOption(argc,argv,"-m","Tot");
  TString year          = getOption(argc,argv,"-y","Tot");
  TString finalState    = getOption(argc,argv,"-f","pipi");
  TString flavour       = getOption(argc,argv,"-c","bddpi");
  printf("%s %g %s %s %s %s\n",decay.Data(),bdtCut,magnet.Data(),year.Data(),finalState.Data(),flavour.Data());
  std::vector<Double_t> p0SS, p1SS, etaHatSS;
  //Tagging variables SSpi, SSp
  // p0SS.push_back(0.4463+0.00256); p1SS.push_back(1-0.01856); etaHatSS.push_back(0.4463); //to be updated
  // p0SS.push_back(0.4604-0.00236); p1SS.push_back(1+0.00071); etaHatSS.push_back(0.4604);
  if (year=="2015" || year=="2016" || year=="201516"){
    p0SS.push_back(0.4537); p1SS.push_back(0.915); etaHatSS.push_back(0.4488);
    p0SS.push_back(0.4601); p1SS.push_back(0.948); etaHatSS.push_back(0.4625);
  } else if (year == "2017"){
    p0SS.push_back(0.4511); p1SS.push_back(0.952); etaHatSS.push_back(0.4482);
    p0SS.push_back(0.4593); p1SS.push_back(0.893); etaHatSS.push_back(0.4624);
  } else if (year == "2017s29r2p2"){
    p0SS.push_back(0.4511); p1SS.push_back(0.952); etaHatSS.push_back(0.4482);
    p0SS.push_back(0.4593); p1SS.push_back(0.893); etaHatSS.push_back(0.4624);
  } else if (year == "2018"){
    p0SS.push_back(0.4530); p1SS.push_back(0.926); etaHatSS.push_back(0.4484);
    p0SS.push_back(0.4602); p1SS.push_back(0.857); etaHatSS.push_back(0.4624);
  } else if (year == "20151618") {
    p0SS.push_back(0.4533); p1SS.push_back(0.910); etaHatSS.push_back(0.4486);
    p0SS.push_back(0.4601); p1SS.push_back(0.903); etaHatSS.push_back(0.4625);
  }
  Double_t bPT = 0, weight = 0, 
           etaSSpi = 0, etaSSp = 0, etaSS = 0, etaSSk = 0, 
           time = 0, timeErr = 0;
  Int_t nSPDHits = 0, 
        qSSpi = 0, qSSp = 0, qSS = 0, qSSk = 0;
  std::vector<Int_t> q;
  std::vector<Double_t> eta;

  TChain * chain = new TChain("DecayTree","DecayTree");
  std::map<TString,TString> Flavour;
  Flavour["bddpi"] = "Bd2Dpi";
  Flavour["bsdspi"] = "Bs2Dspi";
  std::map<TString,vector<TString>> Years;
  Years["2015"] = {"2015"};
  Years["2016"] = {"2016"};
  Years["2017"] = {"2017"};
  Years["2017s29r2p2"] = {"2017"};
  Years["2018"] = {"2018"};
  Years["201516"] = {"2015", "2016"};
  Years["20151618"] = {"2015", "2016", "2018"};
  Years["Tot"] = {"2015", "2016", "2017", "2018"};
  std::map<TString,vector<TString>> Mags;
  Mags["Up"] = {"Up"};
  Mags["Down"] = {"Dw"};
  Mags["Tot"] = {"Up", "Dw"};
  for (auto Year : Years[year]){
    for (auto Mag : Mags[magnet]){
      chain->Add(Form("/storage/gpfs_data/local/lhcb/users/dmanuzzi/B2HH/data/%s/%s/Mag%s/B2DX_%s_%s_%s_sWeight.root",
                      Flavour[flavour].Data(), Year.Data(), Mag.Data(),
                      Year.Data(), Mag.Data(), Flavour[flavour].Data()));
    }
  }
  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("BeautyTime",1);
  chain->SetBranchStatus("BeautyTimeErr",1);
  chain->SetBranchStatus("lab0_PT",1);
  chain->SetBranchStatus("lab0_SSPion_TAGETA",1);
  chain->SetBranchStatus("lab0_SSPion_TAGDEC",1);
  chain->SetBranchStatus("lab0_SSProton_TAGETA",1);
  chain->SetBranchStatus("lab0_SSProton_TAGDEC",1);
  chain->SetBranchStatus("lab0_SSKaonLatest_TAGETA",1);
  chain->SetBranchStatus("lab0_SSKaonLatest_TAGDEC",1);
  chain->SetBranchStatus("lab0_SSKaon_TAGETA",1);
  chain->SetBranchStatus("lab0_SSKaon_TAGDEC",1);
  chain->SetBranchStatus("sWeight",1);
  chain->SetBranchStatus("nSPDHits",1);
      
  chain->SetBranchAddress("BeautyTime",&time);
  chain->SetBranchAddress("BeautyTimeErr",&timeErr);
  chain->SetBranchAddress("lab0_PT",&bPT);
  chain->SetBranchAddress("lab0_SSPion_TAGETA", &etaSSpi);
  chain->SetBranchAddress("lab0_SSPion_TAGDEC", &qSSpi);
  chain->SetBranchAddress("lab0_SSProton_TAGETA", &etaSSp);
  chain->SetBranchAddress("lab0_SSProton_TAGDEC", &qSSp);
  if (year == "2017"){
    chain->SetBranchAddress("lab0_SSKaon_TAGETA", &etaSSk);
    chain->SetBranchAddress("lab0_SSKaon_TAGDEC", &qSSk);
  } else {
    chain->SetBranchAddress("lab0_SSKaonLatest_TAGETA", &etaSSk);
    chain->SetBranchAddress("lab0_SSKaonLatest_TAGDEC", &qSSk);
  }
  chain->SetBranchAddress("sWeight",&weight);
  chain->SetBranchAddress("nSPDHits",&nSPDHits);

  TFile *inFile = TFile::Open(Form("${B2HH_OUT}/Tagging/templates/%s_%s_%g_%s_%s.root", 
                                   finalState.Data(), decay.Data(), bdtCut, year.Data(), magnet.Data()), "UPDATE");

  TH1D * h_b2hh_PT;  TH1D * h_b2hh_SPD;  TH2D * h_b2hh_PT_SPD;
  TH1D * h_bdpi_PT;  TH1D * h_bdpi_SPD;  TH2D * h_bdpi_PT_SPD;
  TH1D * h_bdpiW_PT; TH1D * h_bdpiW_SPD; TH2D * h_bdpiW_PT_SPD;
  TH1D * hRatioPT;   TH1D * hRatioSPD;   TH2D * hRatio;
  Int_t binPT = 50, binSPD = 20; Double_t maxPT = 50, maxSPD = 1000;
  h_bdpi_PT = new TH1D("h_bdpi_PT","h_bdpi_PT",binPT,0,maxPT);
  h_bdpi_PT->Sumw2();
  h_bdpi_PT->SetLineWidth(2); h_bdpi_PT->SetLineColor(kBlue);

  h_bdpi_SPD = new TH1D("h_bdpi_SPD","h_bdpi_SPD",binSPD,0,maxSPD);
  h_bdpi_SPD->Sumw2();
  h_bdpi_SPD->SetLineWidth(2); h_bdpi_SPD->SetLineColor(kBlue);

  h_bdpi_PT_SPD = new TH2D("h_bdpi_PT_SPD","h_bdpi_PT_SPD",binPT,0,maxPT,binSPD,0,maxSPD);
  h_bdpi_PT_SPD->Sumw2();
  h_bdpi_PT_SPD->SetLineWidth(2); h_bdpi_PT_SPD->SetLineColor(kBlue);
  for(Int_t iEntry = 0, nEntries = chain->GetEntries(); iEntry < nEntries; ++iEntry) {

    chain->GetEntry(iEntry);
    if(nSPDHits>1000) continue;
    if(bPT/1000>50) continue;

    h_bdpi_PT->Fill(bPT/1000,weight); 
    h_bdpi_SPD->Fill(nSPDHits,weight);
    h_bdpi_PT_SPD->Fill(bPT/1000,nSPDHits,weight);

  }
  h_bdpi_PT->Scale(1./h_bdpi_PT->Integral("width"));
  h_bdpi_SPD->Scale(1./h_bdpi_SPD->Integral("width"));
  h_bdpi_PT_SPD->Scale(1./h_bdpi_PT_SPD->Integral("width"));

  TString bmeson = flavour == "bddpi" ? "bd" :
                   flavour == "bsdspi" ? "bs" : "";

  TFile *outFile = TFile::Open(Form("${B2HH_OUT}/Tagging/test/Test_%s_%s_%g_%s_%s.root",
                                    finalState.Data(), decay.Data(), bdtCut, year.Data(), magnet.Data()),
                               "RECREATE");

  TH1D * h_bdpi_etaSSpi; TH1D * h_bdpi_etaSSp; TH1D * h_bdpi_etaSS; TH1D * h_bdpi_etaSSk;
  TH1D * h_b2hh_etaSSpi; TH1D * h_b2hh_etaSSp; TH1D * h_b2hh_etaSS; TH1D * h_b2hh_etaSSk;
  TH1D * h_bdpi_etaSSpiTmp; TH1D * h_bdpi_etaSSpTmp; TH1D * h_bdpi_etaSSTmp; TH1D * h_bdpi_etaSSkTmp;
  TH1D * h_b2hh_etaSSpiTmp; TH1D * h_b2hh_etaSSpTmp; TH1D * h_b2hh_etaSSTmp; TH1D * h_b2hh_etaSSkTmp;

  Int_t iBin = 0; Double_t newweight = 0;
  std::vector<TString> names = {"kpi","pipi","kk"};
  for(auto name: names) {

    h_b2hh_PT = (TH1D *) inFile->Get(Form("h_%s%s_PT",bmeson.Data(),name.Data()));
    h_b2hh_PT->SetLineWidth(2); h_b2hh_PT->SetLineColor(kRed);
    h_b2hh_SPD  = (TH1D *) inFile->Get(Form("h_%s%s_SPD",bmeson.Data(),name.Data()));
    h_b2hh_SPD->SetLineWidth(2); h_b2hh_SPD->SetLineColor(kRed);
    h_b2hh_PT_SPD = (TH2D *) inFile->Get(Form("h_%s%s_PT_SPD",bmeson.Data(),name.Data()));

    h_bdpiW_PT = new TH1D(Form("h_%s%sW_PT",bmeson.Data(),name.Data()),
                          Form("h_%s%sW_PT",bmeson.Data(),name.Data()),binPT,0,maxPT);
    h_bdpiW_PT->SetMarkerStyle(20); h_bdpiW_PT->SetMarkerSize(1.2); h_bdpiW_PT->SetMarkerColor(kBlue);
    h_bdpiW_SPD = new TH1D(Form("h_%s%sW_SPD",bmeson.Data(),name.Data()),
                           Form("h_%s%sW_SPD",bmeson.Data(),name.Data()),binSPD,0,maxSPD);
    h_bdpiW_SPD->SetMarkerStyle(20); h_bdpiW_SPD->SetMarkerSize(1.2); h_bdpiW_SPD->SetMarkerColor(kBlue);
    h_bdpiW_PT_SPD = new TH2D(Form("h_%s%sW_PT_SPD",bmeson.Data(),name.Data()),
                              Form("h_%s%sW_PT_SPD",bmeson.Data(),name.Data()),binPT,0,maxPT,binSPD,0,maxSPD);
    h_bdpiW_PT_SPD->Sumw2();

    hRatioPT = (TH1D *) h_b2hh_PT->Clone("hRatioPT");
    hRatioPT->Divide(h_bdpi_PT);
    hRatioSPD = (TH1D *) h_b2hh_SPD->Clone("hRatioSPD");
    hRatioSPD->Divide(h_bdpi_SPD);
    hRatio = (TH2D *) h_b2hh_PT_SPD->Clone("hRatio");
    hRatio->Divide(h_bdpi_PT_SPD);

    h_bdpi_etaSSpiTmp   = new TH1D("h_bdpi_etaSSpiTmp", "h_bdpi_etaSSpiTmp", 51,0,0.51); h_bdpi_etaSSpiTmp->Sumw2();
    h_bdpi_etaSSpTmp    = new TH1D("h_bdpi_etaSSpTmp",  "h_bdpi_etaSSpTmp",  51,0,0.51); h_bdpi_etaSSpTmp->Sumw2();
    h_bdpi_etaSSTmp     = new TH1D("h_bdpi_etaSSTmp",   "h_bdpi_etaSSTmp",   51,0,0.51); h_bdpi_etaSSTmp->Sumw2();
    h_bdpi_etaSSkTmp    = new TH1D("h_bdpi_etaSSkTmp",  "h_bdpi_etaSSkTmp",  51,0,0.51); h_bdpi_etaSSkTmp->Sumw2();
    h_b2hh_etaSSpiTmp   = (TH1D *) h_bdpi_etaSSpiTmp->Clone( Form("h_%s%s_etaSSpiTmp", bmeson.Data(),name.Data()));
    h_b2hh_etaSSpTmp    = (TH1D *) h_bdpi_etaSSpTmp->Clone(  Form("h_%s%s_etaSSpTmp",  bmeson.Data(),name.Data()));
    h_b2hh_etaSSTmp     = (TH1D *) h_bdpi_etaSSTmp->Clone(   Form("h_%s%s_etaSSTmp",   bmeson.Data(),name.Data()));
    h_b2hh_etaSSkTmp    = (TH1D *) h_bdpi_etaSSkTmp->Clone(Form("h_%s%s_etaSSkTmp",bmeson.Data(),name.Data()));
    gRandom->SetSeed(TString(outFile->GetName()).Hash());
    for(Int_t iEntry = 0, nEntries = chain->GetEntries(); iEntry < nEntries; ++iEntry) {

      chain->GetEntry(iEntry);
      if(nSPDHits>maxSPD) continue;
      if(bPT/1000>maxPT) continue;
      etaSSpi = gRandom->Uniform(0.0, 0.5);
      etaSSp = gRandom->Uniform(0.0, 0.5);
      etaSSk = gRandom->Uniform(0.0, 0.5);

      iBin = hRatio->FindBin(bPT/1000,nSPDHits);
      newweight = weight*hRatio->GetBinContent(iBin);
      h_b2hh_etaSSpiTmp->Fill(etaSSpi,newweight);
      h_bdpi_etaSSpiTmp->Fill(etaSSpi);
      h_b2hh_etaSSpTmp->Fill(etaSSp,newweight);
      h_bdpi_etaSSpTmp->Fill(etaSSp);

      q.push_back(qSSpi); eta.push_back(etaSSpi);
      q.push_back(qSSp);  eta.push_back(etaSSp);
      combineTaggers(qSS,etaSS,q,eta,p0SS,p1SS,etaHatSS);
      h_b2hh_etaSSTmp->Fill(etaSS,newweight);
      h_bdpi_etaSSTmp->Fill(etaSS);
      q.clear(); eta.clear();

      h_b2hh_etaSSkTmp->Fill(etaSSk,newweight);
      h_bdpi_etaSSkTmp->Fill(etaSSk);
      h_bdpiW_PT->Fill(bPT/1000,newweight);
      h_bdpiW_SPD->Fill(nSPDHits,newweight);
      h_bdpiW_PT_SPD->Fill(bPT/1000,nSPDHits,newweight);
    }

    h_bdpi_etaSSpi = new TH1D("h_bdpi_etaSSpi", "h_bdpi_etaSSpi", 50,0,0.5); h_bdpi_etaSSpi->Sumw2();
    h_bdpi_etaSSp  = new TH1D("h_bdpi_etaSSp",  "h_bdpi_etaSSp",  50,0,0.5); h_bdpi_etaSSp->Sumw2();
    h_bdpi_etaSS   = new TH1D("h_bdpi_etaSS",   "h_bdpi_etaSS",   50,0,0.5); h_bdpi_etaSS->Sumw2();
    h_bdpi_etaSSk  = new TH1D("h_bdpi_etaSSk",  "h_bdpi_etaSSk",  50,0,0.5); h_bdpi_etaSSk->Sumw2();
    h_b2hh_etaSSpi = (TH1D *) h_bdpi_etaSSpi->Clone( Form("h_%s%s_etaSSpi", bmeson.Data(),name.Data()));
    h_b2hh_etaSSp  = (TH1D *) h_bdpi_etaSSp ->Clone( Form("h_%s%s_etaSSp",  bmeson.Data(),name.Data()));
    h_b2hh_etaSS   = (TH1D *) h_bdpi_etaSS  ->Clone( Form("h_%s%s_etaSS",   bmeson.Data(),name.Data()));
    h_b2hh_etaSSk  = (TH1D *) h_bdpi_etaSSk ->Clone( Form("h_%s%s_etaSSk",  bmeson.Data(),name.Data()));

    for(Int_t i = 0; i < 100; ++i) {

      h_bdpi_etaSSpi->SetBinContent(i+1,h_bdpi_etaSSpiTmp->GetBinContent(i+1));
      h_bdpi_etaSSp->SetBinContent(i+1, h_bdpi_etaSSpTmp->GetBinContent(i+1));
      h_bdpi_etaSS->SetBinContent(i+1,  h_bdpi_etaSSTmp->GetBinContent(i+1));
      h_bdpi_etaSSk->SetBinContent(i+1, h_bdpi_etaSSkTmp->GetBinContent(i+1));
      h_b2hh_etaSSpi->SetBinContent(i+1,h_b2hh_etaSSpiTmp->GetBinContent(i+1));
      h_b2hh_etaSSp->SetBinContent(i+1, h_b2hh_etaSSpTmp->GetBinContent(i+1));
      h_b2hh_etaSS->SetBinContent(i+1,  h_b2hh_etaSSTmp->GetBinContent(i+1));
      h_b2hh_etaSSk->SetBinContent(i+1, h_b2hh_etaSSkTmp->GetBinContent(i+1));

      h_bdpi_etaSSpi->SetBinError(i+1,h_bdpi_etaSSpiTmp->GetBinError(i+1));
      h_bdpi_etaSSp->SetBinError(i+1, h_bdpi_etaSSpTmp->GetBinError(i+1));
      h_bdpi_etaSS->SetBinError(i+1,  h_bdpi_etaSSTmp->GetBinError(i+1));
      h_bdpi_etaSSk->SetBinError(i+1, h_bdpi_etaSSkTmp->GetBinError(i+1));
      h_b2hh_etaSSpi->SetBinError(i+1,h_b2hh_etaSSpiTmp->GetBinError(i+1));
      h_b2hh_etaSSp->SetBinError(i+1, h_b2hh_etaSSpTmp->GetBinError(i+1));
      h_b2hh_etaSS->SetBinError(i+1,  h_b2hh_etaSSTmp->GetBinError(i+1));
      h_b2hh_etaSSk->SetBinError(i+1, h_b2hh_etaSSkTmp->GetBinError(i+1));

    }

    shiftToZero(h_b2hh_etaSSpi);
    shiftToZero(h_b2hh_etaSSp);
    shiftToZero(h_b2hh_etaSS);
    shiftToZero(h_b2hh_etaSSk);
    //h_b2hh_etaSSpi->Smooth(1,"r");
    //h_b2hh_etaSSp->Smooth(1,"r");
    //h_b2hh_etaSS->Smooth(1,"r");
    //h_b2hh_etaSSk->Smooth(1,"r");

    h_b2hh_etaSSpi->Scale(1./h_b2hh_etaSSpi->Integral("width"));
    h_b2hh_etaSSp->Scale(1./h_b2hh_etaSSp->Integral("width"));
    h_b2hh_etaSS->Scale(1./h_b2hh_etaSS->Integral("width"));
    h_b2hh_etaSSk->Scale(1./h_b2hh_etaSSk->Integral("width"));
    h_bdpi_etaSSpi->Scale(1./h_bdpi_etaSSpi->Integral("width"));
    h_bdpi_etaSSp->Scale(1./h_bdpi_etaSSp->Integral("width"));
    h_bdpi_etaSS->Scale(1./h_bdpi_etaSS->Integral("width"));
    h_bdpi_etaSSk->Scale(1./h_bdpi_etaSSk->Integral("width"));
    h_bdpiW_PT->Scale(1./h_bdpiW_PT->Integral("width"));
    h_bdpiW_SPD->Scale(1./h_bdpiW_SPD->Integral("width"));
    h_bdpiW_PT_SPD->Scale(1./h_bdpiW_PT_SPD->Integral("width"));

    inFile->WriteTObject(h_b2hh_etaSSpi,"","Overwrite");
    inFile->WriteTObject(h_b2hh_etaSSp,"","Overwrite");
    inFile->WriteTObject(h_b2hh_etaSS,"","Overwrite");
    inFile->WriteTObject(h_b2hh_etaSSk,"","Overwrite");
    if(bmeson=="bd"&&name=="kpi") {

      TH1D * hLbPK_etaSSpi = (TH1D *) h_b2hh_etaSSpi->Clone("h_lbpk_etaSSpi");
      TH1D * hLbPK_etaSSp  = (TH1D *) h_b2hh_etaSSp->Clone("h_lbpk_etaSSp");
      TH1D * hLbPK_etaSS   = (TH1D *) h_b2hh_etaSS->Clone("h_lbpk_etaSS");
      TH1D * hLbPK_etaSSk  = (TH1D *) h_b2hh_etaSSk->Clone("h_lbpk_etaSSk");
      inFile->WriteTObject(hLbPK_etaSSpi,"","Overwrite");
      inFile->WriteTObject(hLbPK_etaSSp,"","Overwrite");
      inFile->WriteTObject(hLbPK_etaSS,"","Overwrite");
      inFile->WriteTObject(hLbPK_etaSSk,"","Overwrite");

      TH1D * hLbPPI_etaSSpi = (TH1D *) h_b2hh_etaSSpi->Clone("h_lbppi_etaSSpi");
      TH1D * hLbPPI_etaSSp  = (TH1D *) h_b2hh_etaSSp->Clone("h_lbppi_etaSSp");
      TH1D * hLbPPI_etaSS   = (TH1D *) h_b2hh_etaSS->Clone("h_lbppi_etaSS");
      TH1D * hLbPPI_etaSSk  = (TH1D *) h_b2hh_etaSSk->Clone("h_lbppi_etaSSk");
      inFile->WriteTObject(hLbPPI_etaSSpi,"","Overwrite");
      inFile->WriteTObject(hLbPPI_etaSSp,"","Overwrite");
      inFile->WriteTObject(hLbPPI_etaSS,"","Overwrite");
      inFile->WriteTObject(hLbPPI_etaSSk,"","Overwrite");

    }
    printf("STICAZZI %s",h_b2hh_etaSS->GetName());

    outFile->WriteTObject(h_bdpi_PT,"","Overwrite");
    outFile->WriteTObject(h_b2hh_PT,"","Overwrite");
    outFile->WriteTObject(h_bdpiW_PT,"","Overwrite");
    outFile->WriteTObject(h_bdpi_SPD,"","Overwrite");
    outFile->WriteTObject(h_b2hh_SPD,"","Overwrite");
    outFile->WriteTObject(h_bdpiW_SPD,"","Overwrite");
    outFile->WriteTObject(h_b2hh_PT_SPD,"","Overwrite");
    outFile->WriteTObject(h_bdpi_PT_SPD,"","Overwrite");
    outFile->WriteTObject(h_bdpiW_PT_SPD,"","Overwrite");

    delete h_bdpi_etaSSpiTmp; delete h_bdpi_etaSSpTmp; delete h_bdpi_etaSSTmp; delete h_bdpi_etaSSkTmp;
    delete h_b2hh_etaSSpiTmp; delete h_b2hh_etaSSpTmp; delete h_b2hh_etaSSTmp; delete h_b2hh_etaSSkTmp;
    delete h_bdpi_etaSSpi; delete h_bdpi_etaSSp; delete h_bdpi_etaSS; delete h_bdpi_etaSSk;
    delete h_b2hh_etaSSpi; delete h_b2hh_etaSSp; delete h_b2hh_etaSS; delete h_b2hh_etaSSk;

    delete h_bdpiW_PT; delete h_bdpiW_SPD;
    delete hRatioPT; delete hRatioSPD; delete hRatio;
  }

  inFile->Close();
  outFile->Close();
  /*
  TCanvas * cPT = new TCanvas("cPT","cPT");
  cPT->cd();
  h_bdkpi_PT->Draw("hist");
  h_bddpi_PT->Draw("histsame");
  h_bddpiW_PT->Draw("pesame");

  TCanvas * cRatioPT = new TCanvas("cRatioPT","cRatioPT");
  cRatioPT->cd();
  hRatioPT->Draw();

  TCanvas * cSPD = new TCanvas("cSPD","cSPD");
  cSPD->cd();
  h_bdkpi_SPD->Draw("hist");
  h_bddpi_SPD->Draw("histsame");
  h_bddpiW_SPD->Draw("pesame");

  TCanvas * cRatioSPD = new TCanvas("cRatioSPD","cRatioSPD");
  cRatioSPD->cd();
  hRatioSPD->Draw();

  TCanvas * cPTSPD = new TCanvas("cPTSPD","cPTSPD");
  cPTSPD->cd();
  h_bddpi_etaSSpi->Draw("hist");
  h_bddpiW_etaSSpi->Draw("pesame");
  
  myApp.Run();
  */
  return 0;

}
