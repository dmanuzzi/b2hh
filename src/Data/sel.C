#define sel_cxx
#include "sel.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TTree.h>
#include <TRandom3.h>
#include <vector>

 
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include <config_datasets.h>
using namespace std;
using namespace TMVA;

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

void sel::Loop()
{
//   In a ROOT session, you can do:
//      root> .L sel.C
//      root> sel t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   B0_Hlt2B2HHDecision_TOS=0; B0_Hlt2B2HH_B2HHDecision_TOS=0;

   std::vector<TString> varNames;
   varNames.push_back("min[p_{T}(h^{+}),p_{T}(h^{-})] := var0");
   varNames.push_back("log(min[#chi^{2}_{IP}(h^{+}), #chi^{2}_{IP}(h^{-})]) := var1");
   varNames.push_back("max[p_{T}(h^{+}),p_{T}(h^{-})] := var2");
   varNames.push_back("log(max[#chi^{2}_{IP}(h^{+}), #chi^{2}_{IP}(h^{-})]) := var3");
   varNames.push_back("d_{CA} := var4");
   varNames.push_back("#chi^{2}_{vtx}(H_{b}}^{0}) := var5");
   varNames.push_back("#chi^{2}_{IP}(H_{b})^{0} := var6");
   varNames.push_back("log(chi^{2}_{FD}(H_{b})^{0})) := var7");
   varNames.push_back("p_{T}(H_{b}) := var8");
   // varNames.push_back("min(piplusPT,piminusPT)");
   // varNames.push_back("log(min(piplusIPCHI2,piminusIPCHI2))");
   // varNames.push_back("max(piplusPT,piminusPT)");
   // varNames.push_back("log(max(piplusIPCHI2,piminusIPCHI2))");
   // varNames.push_back("bDOCA");
   // varNames.push_back("bVTXCHI2");
   // varNames.push_back("bIPCHI2");
   // varNames.push_back("log(bFDCHI2)");
   // varNames.push_back("bPT");
   std::vector<Double_t> vars(varNames.size());

   TMVA::Reader *readerPIPI = new TMVA::Reader(varNames, "!Color:!Silent", true);
   readerPIPI->BookMVA(bdtWeights::bdtPIPI[fyear][0].first, bdtWeights::bdtPIPI[fyear][0].second);
   readerPIPI->BookMVA(bdtWeights::bdtPIPI[fyear][1].first, bdtWeights::bdtPIPI[fyear][1].second);
   readerPIPI->BookMVA(bdtWeights::bdtPIPI[fyear][2].first, bdtWeights::bdtPIPI[fyear][2].second);
   TMVA::Reader *readerKK = new TMVA::Reader(varNames, "!Color:!Silent", true);
   readerKK->BookMVA(bdtWeights::bdtKK[fyear][0].first, bdtWeights::bdtKK[fyear][0].second);
   readerKK->BookMVA(bdtWeights::bdtKK[fyear][1].first, bdtWeights::bdtKK[fyear][1].second);
   readerKK->BookMVA(bdtWeights::bdtKK[fyear][2].first, bdtWeights::bdtKK[fyear][2].second);
   // TMVA::Reader *readerGPIPI = new TMVA::Reader(varNames, "!Color:!Silent", true);
   // readerGPIPI->BookMVA(bdtWeights::bdtgPIPI[fyear][0].first, bdtWeights::bdtgPIPI[fyear][0].second);
   // readerGPIPI->BookMVA(bdtWeights::bdtgPIPI[fyear][1].first, bdtWeights::bdtgPIPI[fyear][1].second);
   // readerGPIPI->BookMVA(bdtWeights::bdtgPIPI[fyear][2].first, bdtWeights::bdtgPIPI[fyear][2].second);
   // TMVA::Reader *readerGKK = new TMVA::Reader(varNames, "!Color:!Silent", true);
   // readerGKK->BookMVA(bdtWeights::bdtgKK[fyear][0].first, bdtWeights::bdtgKK[fyear][0].second);
   // readerGKK->BookMVA(bdtWeights::bdtgKK[fyear][1].first, bdtWeights::bdtgKK[fyear][1].second);
   // readerGKK->BookMVA(bdtWeights::bdtgKK[fyear][2].first, bdtWeights::bdtgKK[fyear][2].second);

   TRandom3 * myRandom = new TRandom3(192837465); Double_t myRand = 0;
   Int_t nPos = -999; Double_t vlight = 0.299792458;

   // BDT Variables
   Double_t bIPCHI2 = 0, bFDCHI2 = 0, bIPCHI2NEXT = 0,
            bPVCHI2 = 0, bVTXCHI2 = 0, bDIRA = 0, bDOCA = 0;
   Double_t bdtPIPI = 0, bdtKK = 0, bdtgPIPI = 0, bdtgKK = 0,
            BDT1_PIPI = 0, BDT2_PIPI = 0, BDT3_PIPI = 0,
            BDT1_KK = 0, BDT2_KK = 0, BDT3_KK = 0,
            BDTG1_PIPI = 0, BDTG2_PIPI = 0, BDTG3_PIPI = 0,
            BDTG1_KK = 0, BDTG2_KK = 0, BDTG3_KK = 0;
   Double_t radialDistancePV = 0, radialDistance = 0;

   // B Kinematic
   Double_t bP      = 0, bPT = 0, bETA       = 0, bPHI = 0;
   
   // Tracks Kinematic + PID
   Double_t piplusP  = 0, piplusPT  = 0, piplusETA  = 0, piplusPHI  = 0,
            piplusIPCHI2   = 0, piplusTRACKCHI2  = 0,
            piplusDLLKPI   = 0, piplusDLLPPI     = 0,
            piplusProbKPI  = 0, piplusProbPPI    = 0,
            piminusP = 0, piminusPT = 0, piminusETA = 0, piminusPHI = 0,
            piminusIPCHI2  = 0, piminusTRACKCHI2 = 0,
            piminusDLLKPI  = 0, piminusDLLPPI    = 0,
            piminusProbKPI = 0, piminusProbPPI   = 0;
   Int_t    piplus_ISMUON = 0, piminus_ISMUON = 0;

   // Masses and Mass Errors
   Double_t massPIPI = 0, massKPI = 0, massPIK = 0, massKK  = 0,
            massPK   = 0, massKP  = 0, massPPI = 0, massPIP = 0;
   Double_t massPIPIErr = 0, massKPIErr = 0, massPIKErr = 0, massKKErr  = 0,
            massPKErr   = 0, massKPErr  = 0, massPPIErr = 0, massPIPErr = 0;



   // Decay times and Decay time errors
   Double_t tauPIPI = 0, tauKPI = 0, tauPIK = 0, tauKK  = 0,
            tauPK   = 0, tauKP  = 0, tauPPI = 0, tauPIP = 0,
            tauPIPICheck = 0;
   Double_t tauPIPICHI2 = 0, tauPIPIStatus = 0,
            tauKPICHI2  = 0, tauKPIStatus  = 0,
            tauPIKCHI2  = 0, tauPIKStatus  = 0,
            tauKKCHI2   = 0, tauKKStatus   = 0,
            tauPKCHI2   = 0, tauPKStatus   = 0,
            tauKPCHI2   = 0, tauKPStatus   = 0,
            tauPPICHI2  = 0, tauPPIStatus  = 0,
            tauPIPCHI2  = 0, tauPIPStatus  = 0,
            tauPIPICheckCHI2 = 0;
   Double_t tauPIPIErr = 0, tauKPIErr = 0, tauPIKErr = 0, tauKKErr  = 0,
            tauPKErr   = 0, tauKPErr  = 0, tauPPIErr = 0, tauPIPErr = 0,
            tauPIPICheckErr = 0;

   // Event Variables
   Int_t     idBDT = 0; 
   Int_t   year = ((fyear == "2017s29r2p2")? 2017 : fyear.Atoi());
   






   // Trigger Variables
   Bool_t l0GlobalDec  = false, l0GlobalTOS  = false, l0GlobalTIS  = false,
          l0HadronDec  = false, l0HadronTOS  = false, l0HadronTIS  = false,
          hlt1TrackDec = false, hlt1TrackTOS = false, hlt1TrackTIS = false,
          hlt2TopoDec  = false, hlt2TopoTOS  = false, hlt2TopoTIS  = false,
          hlt2B2HHDec  = false, hlt2B2HHTOS  = false, hlt2B2HHTIS  = false;

   // Tagging Variables
   Int_t qOScharm = 0, qOSele = 0, qOSk = 0, qOSmu = 0, qOSvtx = 0, qOS = 0,
         qSSpi = 0, qSSp = 0, qSSk = 0, qSS = 0, 
         qOSele_old = 0, qOSk_old = 0, qOSmu_old = 0, qSSk_old = 0;
   Double_t etaOScharm = 0, etaOSele = 0, etaOSk = 0, etaOSmu = 0, etaOSvtx = 0, etaOS = 0,
            etaSSpi = 0, etaSSp = 0, etaSSk = 0, etaSS = 0,
            etaOSele_old = 0, etaOSk_old = 0, etaOSmu_old = 0, etaSSk_old = 0;

   Bool_t preselection = false;

   TTree * outTree = new TTree("b2hh","b2hh");
   // BDT Variables
   outTree->Branch("bIPCHI2",    &bIPCHI2,    "bIPCHI2/D");
   outTree->Branch("bIPCHI2NEXT",&bIPCHI2NEXT,"bIPCHI2NEXT/D");
   outTree->Branch("bFDCHI2",    &bFDCHI2,    "bFDCHI2/D");
   outTree->Branch("bPVCHI2",    &bPVCHI2,    "bPVCHI2/D");
   outTree->Branch("bVTXCHI2",   &bVTXCHI2,   "bVTXCHI2/D");
   outTree->Branch("bDOCA",      &bDOCA,      "bDOCA/D");
   outTree->Branch("bDIRA",      &bDIRA,      "bDIRA/D");

   outTree->Branch("rFD",        &radialDistance,"rFD/D");
   outTree->Branch("rFDPV",      &radialDistancePV,"rFDPV/D");

   outTree->Branch("bdtPIPI",    &bdtPIPI,    "bdtPIPI/D");
   outTree->Branch("bdtKK",      &bdtKK,      "bdtKK/D");
   outTree->Branch("BDT1_PIPI",  &BDT1_PIPI,  "BDT1_PIPI/D");
   outTree->Branch("BDT2_PIPI",  &BDT2_PIPI,  "BDT2_PIPI/D");
   outTree->Branch("BDT3_PIPI",  &BDT3_PIPI,  "BDT3_PIPI/D");
   outTree->Branch("BDT1_KK",    &BDT1_KK,    "BDT1_KK/D");
   outTree->Branch("BDT2_KK",    &BDT2_KK,    "BDT2_KK/D");
   outTree->Branch("BDT3_KK",    &BDT3_KK,    "BDT3_KK/D");
   outTree->Branch("bdtgPIPI",   &bdtgPIPI,   "bdtgPIPI/D");
   outTree->Branch("bdtgKK",     &bdtgKK,     "bdtgKK/D");
   outTree->Branch("BDTG1_PIPI", &BDTG1_PIPI, "BDTG1_PIPI/D");
   outTree->Branch("BDTG2_PIPI", &BDTG2_PIPI, "BDTG2_PIPI/D");
   outTree->Branch("BDTG3_PIPI", &BDTG3_PIPI, "BDTG3_PIPI/D");
   outTree->Branch("BDTG1_KK",   &BDTG1_KK,   "BDTG1_KK/D");
   outTree->Branch("BDTG2_KK",   &BDTG2_KK,   "BDTG2_KK/D");
   outTree->Branch("BDTG3_KK",   &BDTG3_KK,   "BDTG3_KK/D");

   // B Kinematic
   outTree->Branch("bP",&bP,"bP/D"); 
   outTree->Branch("bPT",&bPT,"bPT/D"); 
   outTree->Branch("bETA",&bETA,"bETA/D"); 
   outTree->Branch("bPHI",&bPHI,"bPHI/D");
   // Tracks Kinematic + PID
   outTree->Branch("piplusP",&piplusP,"piplusP/D");
   outTree->Branch("piplusPT",&piplusPT,"piplusPT/D");
   outTree->Branch("piplusETA",&piplusETA,"piplusETA/D");
   outTree->Branch("piplusPHI",&piplusPHI,"piplusPHI/D");
   outTree->Branch("piplusIPCHI2",&piplusIPCHI2,"piplusIPCHI2/D");
   outTree->Branch("piplusTRACKCHI2",&piplusTRACKCHI2,"piplusTRACKCHI2/D");
   outTree->Branch("piplusDLLKPI",&piplusDLLKPI,"piplusDLLKPI/D");
   outTree->Branch("piplusDLLPPI",&piplusDLLPPI,"piplusDLLPPI/D");
   outTree->Branch("piplusProbKPI",&piplusProbKPI,"piplusProbKPI/D");
   outTree->Branch("piplusProbPPI",&piplusProbPPI,"piplusProbPPI/D");
   outTree->Branch("piplus_ISMUON",&piplus_ISMUON,"piplus_ISMUON/I");
   outTree->Branch("piminusP",&piminusP,"piminusP/D");
   outTree->Branch("piminusPT",&piminusPT,"piminusPT/D");
   outTree->Branch("piminusETA",&piminusETA,"piminusETA/D");
   outTree->Branch("piminusPHI",&piminusPHI,"piminusPHI/D");
   outTree->Branch("piminusIPCHI2",&piminusIPCHI2,"piminusIPCHI2/D");
   outTree->Branch("piminusTRACKCHI2",&piminusTRACKCHI2,"piminusTRACKCHI2/D");
   outTree->Branch("piminusDLLKPI",&piminusDLLKPI,"piminusDLLKPI/D");
   outTree->Branch("piminusDLLPPI",&piminusDLLPPI,"piminusDLLPPI/D");
   outTree->Branch("piminusProbKPI",&piminusProbKPI,"piminusProbKPI/D");
   outTree->Branch("piminusProbPPI",&piminusProbPPI,"piminusProbPPI/D");
   outTree->Branch("piminus_ISMUON",&piminus_ISMUON,"piminus_ISMUON/I");

   // Masses and Mass Errors
   outTree->Branch("massPIPI",&massPIPI,"massPIPI/D"); outTree->Branch("massPIPIErr",&massPIPIErr,"massPIPIErr/D");
   outTree->Branch("massKPI",&massKPI,"massKPI/D");    outTree->Branch("massKPIErr",&massKPIErr,"massKPIErr/D");
   outTree->Branch("massPIK",&massPIK,"massPIK/D");    outTree->Branch("massPIKErr",&massPIKErr,"massPIKErr/D");
   outTree->Branch("massKK",&massKK,"massKK/D");       outTree->Branch("massKKErr",&massKKErr,"massKKErr/D");
   outTree->Branch("massPK",&massPK,"massPK/D");       outTree->Branch("massPKErr",&massPKErr,"massPKErr/D");
   outTree->Branch("massKP",&massKP,"massKP/D");       outTree->Branch("massKPErr",&massKPErr,"massKPErr/D");
   outTree->Branch("massPPI",&massPPI,"massPPI/D");    outTree->Branch("massPPIErr",&massPPIErr,"massPPIErr/D");
   outTree->Branch("massPIP",&massPIP,"massPIP/D");    outTree->Branch("massPIPErr",&massPIPErr,"massPIPErr/D");

   // Decay times and Decay time errors
   outTree->Branch("tauPIPI",&tauPIPI,"tauPIPI/D"); outTree->Branch("tauPIPIErr",&tauPIPIErr,"tauPIPIErr/D");
   outTree->Branch("tauKPI",&tauKPI,"tauKPI/D");    outTree->Branch("tauKPIErr",&tauKPIErr,"tauKPIErr/D");
   outTree->Branch("tauPIK",&tauPIK,"tauPIK/D");    outTree->Branch("tauPIKErr",&tauPIKErr,"tauPIKErr/D");
   outTree->Branch("tauKK",&tauKK,"tauKK/D");       outTree->Branch("tauKKErr",&tauKKErr,"tauKKErr/D");
   outTree->Branch("tauPK",&tauPK,"tauPK/D");       outTree->Branch("tauPKErr",&tauPKErr,"tauPKErr/D");
   outTree->Branch("tauKP",&tauKP,"tauKP/D");       outTree->Branch("tauKPErr",&tauKPErr,"tauKPErr/D");
   outTree->Branch("tauPPI",&tauPPI,"tauPPI/D");    outTree->Branch("tauPPIErr",&tauPPIErr,"tauPPIErr/D");
   outTree->Branch("tauPIP",&tauPIP,"tauPIP/D");    outTree->Branch("tauPIPErr",&tauPIPErr,"tauPIPErr/D");

   outTree->Branch("tauPIPICheck",&tauPIPICheck,"tauPIPICheck/D"); 
   outTree->Branch("tauPIPICheckErr",&tauPIPICheckErr,"tauPIPICheckErr/D");

   outTree->Branch("tauPIPICHI2",&tauPIPICHI2,"tauPIPICHI2/D"); outTree->Branch("tauPIPIStatus",&tauPIPIStatus,"tauPIPIStatus/D");
   outTree->Branch("tauKPICHI2", &tauKPICHI2, "tauKPICHI2/D");  outTree->Branch("tauKPIStatus", &tauKPIStatus, "tauKPIStatus/D");
   outTree->Branch("tauPIKCHI2", &tauPIKCHI2, "tauPIKCHI2/D");  outTree->Branch("tauPIKStatus", &tauPIKStatus, "tauPIKStatus/D");
   outTree->Branch("tauKKCHI2",  &tauKKCHI2,  "tauKKCHI2/D");   outTree->Branch("tauKKStatus",  &tauKKStatus,  "tauKKStatus/D");
   outTree->Branch("tauPKCHI2",  &tauPKCHI2,  "tauPKCHI2/D");   outTree->Branch("tauPKStatus",  &tauPKStatus,  "tauPKStatus/D");
   outTree->Branch("tauKPCHI2",  &tauKPCHI2,  "tauKPCHI2/D");   outTree->Branch("tauKPStatus",  &tauKPStatus,  "tauKPStatus/D");
   outTree->Branch("tauPPICHI2", &tauPPICHI2, "tauPPICHI2/D");  outTree->Branch("tauPPIStatus", &tauPPIStatus, "tauPPIStatus/D");
   outTree->Branch("tauPIPCHI2", &tauPIPCHI2, "tauPIPCHI2/D");  outTree->Branch("tauPIPStatus", &tauPIPStatus, "tauPIPStatus/D");

   outTree->Branch("tauPIPICheckCHI2",&tauPIPICheckCHI2,"tauPIPICheckCHI2/D");


   // Event variables
   outTree->Branch("nPVs",&nPVs,"nPVs/I");
   outTree->Branch("nTracks",&nTracks,"nTracks/I");
   outTree->Branch("nSPDHits",&nSPDHits,"nSPDHits/I");
   outTree->Branch("runNumber",&runNumber,"runNumber/i");
   outTree->Branch("eventNumber",&eventNumber,"eventNumber/l");
   outTree->Branch("Polarity",&Polarity,"Polarity/S");
   outTree->Branch("Year",&year,"Year/I");
   outTree->Branch("idBDT",&idBDT,"idBDT/I");

   // Trigger variables
   outTree->Branch("l0GlobalDec",&l0GlobalDec,"l0GlobalDec/O");
   outTree->Branch("l0GlobalTOS",&l0GlobalTOS,"l0GlobalTOS/O");
   outTree->Branch("l0GlobalTIS",&l0GlobalTIS,"l0GlobalTIS/O");
   outTree->Branch("l0HadronDec",&l0HadronDec,"l0HadronDec/O");
   outTree->Branch("l0HadronTOS",&l0HadronTOS,"l0HadronTOS/O");
   outTree->Branch("l0HadronTIS",&l0HadronTIS,"l0HadronTIS/O");
   outTree->Branch("hlt1TrackDec",&hlt1TrackDec,"hlt1TrackDec/O");
   outTree->Branch("hlt1TrackTOS",&hlt1TrackTOS,"hlt1TrackTOS/O");
   outTree->Branch("hlt1TrackTIS",&hlt1TrackTIS,"hlt1TrackTIS/O");
   outTree->Branch("hlt2TopoDec",&hlt2TopoDec,"hlt2TopoDec/O");
   outTree->Branch("hlt2TopoTOS",&hlt2TopoTOS,"hlt2TopoTOS/O");
   outTree->Branch("hlt2TopoTIS",&hlt2TopoTIS,"hlt2TopoTIS/O");
   outTree->Branch("hlt2B2HHDec",&hlt2B2HHDec,"hlt2B2HHDec/O");
   outTree->Branch("hlt2B2HHTOS",&hlt2B2HHTOS,"hlt2B2HHTOS/O");
   outTree->Branch("hlt2B2HHTIS",&hlt2B2HHTIS,"hlt2B2HHTIS/O");

   // Tagging Variables
   outTree->Branch("qOScharm",&qOScharm,"qOScharm/I");
   outTree->Branch("qOSele",  &qOSele,  "qOSele/I");
   outTree->Branch("qOSk",    &qOSk,    "qOSk/I");
   outTree->Branch("qOSmu",   &qOSmu,   "qOSmu/I");
   outTree->Branch("qOSvtx",  &qOSvtx,  "qOSvtx/I");
   outTree->Branch("qOS",     &qOS,     "qOS/I");
   outTree->Branch("qSSpi",   &qSSpi,   "qSSpi/I");
   outTree->Branch("qSSp",    &qSSp,    "qSSp/I");
   outTree->Branch("qSS",     &qSS,     "qSS/I");
   outTree->Branch("qSSk",    &qSSk,    "qSSk/I");

   outTree->Branch("qOSele_old",  &qOSele_old,  "qOSele_old/I");
   outTree->Branch("qOSk_old",    &qOSk_old,    "qOSk_old/I");
   outTree->Branch("qOSmu_old",   &qOSmu_old,   "qOSmu_old/I");
   outTree->Branch("qSSk_old",    &qSSk_old,    "qSSk_old/I");
   

   outTree->Branch("etaOScharm",&etaOScharm,"etaOScharm/D");
   outTree->Branch("etaOSele",  &etaOSele,  "etaOSele/D");
   outTree->Branch("etaOSk",    &etaOSk,    "etaOSk/D");
   outTree->Branch("etaOSmu",   &etaOSmu,   "etaOSmu/D");
   outTree->Branch("etaOSvtx",  &etaOSvtx,  "etaOSvtx/D");
   outTree->Branch("etaOS",     &etaOS,     "etaOS/D");
   outTree->Branch("etaSSpi",   &etaSSpi,   "etaSSpi/D");
   outTree->Branch("etaSSp",    &etaSSp,    "etaSSp/D");
   outTree->Branch("etaSS",     &etaSS,     "etaSS/D");
   outTree->Branch("etaSSk",    &etaSSk,    "etaSSk/D");

   outTree->Branch("etaOSele_old",  &etaOSele_old,  "etaOSele_old/D");
   outTree->Branch("etaOSk_old",    &etaOSk_old,    "etaOSk_old/D");
   outTree->Branch("etaOSmu_old",   &etaOSmu_old,   "etaOSmu_old/D");
   outTree->Branch("etaSSk_old",    &etaSSk_old,    "etaSSk_old/D");
   

   std::vector<Int_t> tmp_qOS, tmp_qSS;
   std::vector<Double_t> tmp_etaOS, tmp_etaSS, p0OS, p1OS, etaHatOS;
   //Tagging variables Charm,Ele,Kaon,Muon,Vtx
   //p0OS.push_back(0.3500); p1OS.push_back(0.722); etaHatOS.push_back(0.3580);
   //p0OS.push_back(0.2947); p1OS.push_back(1.486); etaHatOS.push_back(0.3177);
   //p0OS.push_back(0.3762); p1OS.push_back(1.492); etaHatOS.push_back(0.3782);
   //p0OS.push_back(0.2560); p1OS.push_back(1.339); etaHatOS.push_back(0.2800);
   //p0OS.push_back(0.3697); p1OS.push_back(1.059); etaHatOS.push_back(0.3797);
   // old FT calibration by Stefano
   // p0OS.push_back(0.3650-0.02438); p1OS.push_back(1-0.11462); etaHatOS.push_back(0.3650);
   // p0OS.push_back(0.3493-0.02348); p1OS.push_back(1+0.38189); etaHatOS.push_back(0.3493);
   // p0OS.push_back(0.3807-0.00511); p1OS.push_back(1+0.37668); etaHatOS.push_back(0.3807);
   // p0OS.push_back(0.3097-0.00922); p1OS.push_back(1+0.22421); etaHatOS.push_back(0.3097);
   // p0OS.push_back(0.3895-0.01080); p1OS.push_back(1-0.05588); etaHatOS.push_back(0.3895);


   std::vector<Double_t> p0SS, p1SS, etaHatSS;
   //Tagging variables SSpi, SSp
   //p0SS.push_back(0.4743); p1SS.push_back(0.976); etaHatSS.push_back(0.4727);
   //p0SS.push_back(0.4741); p1SS.push_back(0.953); etaHatSS.push_back(0.4780);
   // old FT calibration by Stefano
   // p0SS.push_back(0.4463+0.00256); p1SS.push_back(1-0.01856); etaHatSS.push_back(0.4463);
   // p0SS.push_back(0.4604-0.00236); p1SS.push_back(1+0.00071); etaHatSS.push_back(0.4604);
   if (fyear=="2015" || fyear == "2016"){
      p0OS.push_back(0.3427); p1OS.push_back(0.914); etaHatOS.push_back(0.3658);
      p0OS.push_back(0.3630); p1OS.push_back(1.363); etaHatOS.push_back(0.3592);
      p0OS.push_back(0.3905); p1OS.push_back(1.400); etaHatOS.push_back(0.4081);
      p0OS.push_back(0.3190); p1OS.push_back(1.257); etaHatOS.push_back(0.3357);
      p0OS.push_back(0.3838); p1OS.push_back(1.124); etaHatOS.push_back(0.3873);

      p0SS.push_back(0.4537); p1SS.push_back(0.915); etaHatSS.push_back(0.4488);
      p0SS.push_back(0.4601); p1SS.push_back(0.948); etaHatSS.push_back(0.4625);
   } else if (fyear == "2017"){
      p0OS.push_back(0.3584); p1OS.push_back(0.763); etaHatOS.push_back(0.3656);
      p0OS.push_back(0.3648); p1OS.push_back(0.778); etaHatOS.push_back(0.3075);
      p0OS.push_back(0.3739); p1OS.push_back(0.972); etaHatOS.push_back(0.4015);
      p0OS.push_back(0.3236); p1OS.push_back(0.948); etaHatOS.push_back(0.2735);
      p0OS.push_back(0.3759); p1OS.push_back(1.088); etaHatOS.push_back(0.3853);

      p0SS.push_back(0.4511); p1SS.push_back(0.952); etaHatSS.push_back(0.4482);
      p0SS.push_back(0.4593); p1SS.push_back(0.893); etaHatSS.push_back(0.4624);
   } else if (fyear == "2017s29r2p2"){
      p0OS.push_back(0.3584); p1OS.push_back(0.763); etaHatOS.push_back(0.3656);
      p0OS.push_back(0.3693); p1OS.push_back(1.308); etaHatOS.push_back(0.3586);
      p0OS.push_back(0.3863); p1OS.push_back(1.338); etaHatOS.push_back(0.4073);
      p0OS.push_back(0.3104); p1OS.push_back(1.353); etaHatOS.push_back(0.3345);
      p0OS.push_back(0.3759); p1OS.push_back(1.088); etaHatOS.push_back(0.3853);

      p0SS.push_back(0.4511); p1SS.push_back(0.952); etaHatSS.push_back(0.4482);
      p0SS.push_back(0.4593); p1SS.push_back(0.893); etaHatSS.push_back(0.4624);
   }else if (fyear == "2018"){
      p0OS.push_back(0.3543); p1OS.push_back(0.863); etaHatOS.push_back(0.3650);
      p0OS.push_back(0.3730); p1OS.push_back(1.250); etaHatOS.push_back(0.3587);
      p0OS.push_back(0.3963); p1OS.push_back(1.378); etaHatOS.push_back(0.4078);
      p0OS.push_back(0.3068); p1OS.push_back(1.289); etaHatOS.push_back(0.3309);
      p0OS.push_back(0.3802); p1OS.push_back(1.083); etaHatOS.push_back(0.3846);

      p0SS.push_back(0.4530); p1SS.push_back(0.926); etaHatSS.push_back(0.4484);
      p0SS.push_back(0.4602); p1SS.push_back(0.857); etaHatSS.push_back(0.4624);
   }
   else
      return;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      nPos = -999;
      preselection = piplus_hasRich&&piminus_hasRich&&
                     piplus_RichPIDk>-900&&piminus_RichPIDk>-900&&
                     piplus_RichPIDp>-900&&piminus_RichPIDp>-900&&
                     max(piplus_TRACK_CHI2NDOF,piminus_TRACK_CHI2NDOF)<3&&
                     max(piplus_TRACK_GhostProb,piminus_TRACK_GhostProb)<0.5&&
                     piplus_P<500000&&piminus_P<500000&&
                     B0_TAU>0&&B0_PT>1200&&//B0_M<5800&&
                     (B0_L0HadronDecision_TOS==1||
                      B0_L0Global_TIS==1)&&
                     (B0_Hlt1TrackMVADecision_TOS==1||
                      B0_Hlt1TwoTrackMVADecision_TOS==1)&&
                     (B0_Hlt2B2HH_B2HHDecision_TOS==1||
                      B0_Hlt2B2HHDecision_TOS==1);//||
                     // B0_Hlt2Topo2BodyDecision_TOS==1);

      if(!preselection) continue;
      for(int npv = 0; npv<B0_MKK_nPV; npv++) {
        if(fabs((B0_MKK_PV_Z[npv]-B0_OWNPV_Z)/B0_OWNPV_Z)<1e-3) {
          nPos = npv; break;
        }
      }
      if(nPos<0) continue;
      if(B0_MKPi_status[nPos] !=0 ||
         B0_MPiK_status[nPos] !=0 ||
         B0_MKK_status[nPos]  !=0 ||
         B0_MPK_status[nPos]  !=0 ||
         B0_MKP_status[nPos]  !=0 ||
         B0_MPPi_status[nPos] !=0 ||
         B0_MPiP_status[nPos] !=0 ) continue;

      idBDT = (eventNumber % 3 ) + 1;

      
      // BDT Variables
      bIPCHI2        = B0_IPCHI2_OWNPV;
      bIPCHI2NEXT    = B0_MINIPCHI2NEXTBEST;
      bFDCHI2        = B0_FDCHI2_OWNPV;
      bPVCHI2        = B0_OWNPV_CHI2;
      bVTXCHI2       = B0_ENDVERTEX_CHI2/B0_ENDVERTEX_NDOF;
      bDOCA          = B0_DOCA;
      bDIRA          = B0_DIRA_OWNPV;

      radialDistance   = sqrt(B0_ENDVERTEX_X*B0_ENDVERTEX_X+
                              B0_ENDVERTEX_Y*B0_ENDVERTEX_Y);
      radialDistancePV = sqrt((B0_ENDVERTEX_X-B0_OWNPV_X)*(B0_ENDVERTEX_X-B0_OWNPV_X)+
                              (B0_ENDVERTEX_Y-B0_OWNPV_Y)*(B0_ENDVERTEX_Y-B0_OWNPV_Y));

      // B Kinematic
      bP             = B0_P/1000;
      bPT            = B0_PT/1000;
      bETA           = 0.5*log((B0_P+B0_PZ)/(B0_P-B0_PZ));
      bPHI           = atan2(B0_PY,B0_PX);
      // Tracks Kinematic + PID
      piplusP        = piplus_P/1000;
      piplusPT       = piplus_PT/1000;
      piplusETA      = 0.5*log((piplus_P+piplus_PZ)/(piplus_P-piplus_PZ));
      piplusPHI      = atan2(piplus_PY,piplus_PX);
      piplusIPCHI2   = piplus_IPCHI2_OWNPV;
      piplusTRACKCHI2 = piplus_TRACK_CHI2NDOF;
      piplusDLLKPI   = piplus_RichPIDk;
      piplusDLLPPI   = piplus_RichPIDp;
      piplusProbKPI  = log(piplus_ProbNNk/piplus_ProbNNpi);
      piplusProbPPI  = log(piplus_ProbNNp/piplus_ProbNNpi);
      piplus_ISMUON  = piplus_isMuon;
      piminusP       = piminus_P/1000;
      piminusPT      = piminus_PT/1000;
      piminusETA     = 0.5*log((piminus_P+piminus_PZ)/(piminus_P-piminus_PZ));
      piminusPHI     = atan2(piminus_PY,piminus_PX);
      piminusIPCHI2  = piminus_IPCHI2_OWNPV;
      piminusTRACKCHI2 = piminus_TRACK_CHI2NDOF;
      piminusDLLKPI  = piminus_RichPIDk;
      piminusDLLPPI  = piminus_RichPIDp;
      piminusProbKPI = log(piminus_ProbNNk/piminus_ProbNNpi);
      piminusProbPPI = log(piminus_ProbNNp/piminus_ProbNNpi);
      piminus_ISMUON = piminus_isMuon;
      // Masses and Mass Errors
      massPIPI       = B0_MPiPi_M[nPos]/1000;  massPIPIErr = B0_MPiPi_MERR[nPos]/1000;
      massKPI        = B0_MKPi_M[nPos]/1000;   massKPIErr  = B0_MKPi_MERR[nPos]/1000; 
      massPIK        = B0_MPiK_M[nPos]/1000;   massPIKErr  = B0_MPiK_MERR[nPos]/1000;
      massKK         = B0_MKK_M[nPos]/1000;    massKKErr   = B0_MKK_MERR[nPos]/1000;
      massPK         = B0_MPK_M[nPos]/1000;    massPKErr   = B0_MPK_MERR[nPos]/1000;
      massKP         = B0_MKP_M[nPos]/1000;    massKPErr   = B0_MKP_MERR[nPos]/1000;
      massPPI        = B0_MPPi_M[nPos]/1000;   massPPIErr  = B0_MPPi_MERR[nPos]/1000;
      massPIP        = B0_MPiP_M[nPos]/1000;   massPIPErr  = B0_MPiP_MERR[nPos]/1000;
      // Decay times and Decay time errors
      tauPIPI        = B0_MPiPi_ctau[nPos]/vlight; tauPIPIErr = B0_MPiPi_ctauErr[nPos]/vlight;
      tauKPI         = B0_MKPi_ctau[nPos]/vlight;  tauKPIErr  = B0_MKPi_ctauErr[nPos]/vlight;
      tauPIK         = B0_MPiK_ctau[nPos]/vlight;  tauPIKErr  = B0_MPiK_ctauErr[nPos]/vlight;
      tauKK          = B0_MKK_ctau[nPos]/vlight;   tauKKErr   = B0_MKK_ctauErr[nPos]/vlight; 
      tauPK          = B0_MPK_ctau[nPos]/vlight;   tauPKErr   = B0_MPK_ctauErr[nPos]/vlight;
      tauKP          = B0_MKP_ctau[nPos]/vlight;   tauKPErr   = B0_MKP_ctauErr[nPos]/vlight;
      tauPPI         = B0_MPPi_ctau[nPos]/vlight;  tauPPIErr  = B0_MPPi_ctauErr[nPos]/vlight; 
      tauPIP         = B0_MPiP_ctau[nPos]/vlight;  tauPIPErr  = B0_MPiP_ctauErr[nPos]/vlight;
      tauPIPICheck   = B0_TAU*1000;                tauPIPICheckErr = B0_TAUERR*1000;

      tauPIPICHI2    = B0_MPiPi_chi2[nPos];
      tauKPICHI2     = B0_MKPi_chi2[nPos];
      tauPIKCHI2     = B0_MPiK_chi2[nPos];
      tauKKCHI2      = B0_MKK_chi2[nPos];
      tauPKCHI2      = B0_MPK_chi2[nPos];
      tauKPCHI2      = B0_MKP_chi2[nPos];
      tauPPICHI2     = B0_MPPi_chi2[nPos];
      tauPIPCHI2     = B0_MPiP_chi2[nPos];
      tauPIPICheckCHI2 = B0_TAUCHI2;

      tauPIPIStatus  = B0_MPiPi_status[nPos];
      tauKPIStatus   = B0_MKPi_status[nPos];
      tauPIKStatus   = B0_MPiK_status[nPos];
      tauKKStatus    = B0_MKK_status[nPos];
      tauPKStatus    = B0_MPK_status[nPos];
      tauKPStatus    = B0_MKP_status[nPos];
      tauPPIStatus   = B0_MPPi_status[nPos];
      tauPIPStatus   = B0_MPiP_status[nPos];

      // Trigger Variables
      l0GlobalDec  = B0_L0Global_Dec;
      l0GlobalTOS  = B0_L0Global_TOS;
      l0GlobalTIS  = B0_L0Global_TIS;
      l0HadronDec  = B0_L0HadronDecision_Dec;
      l0HadronTOS  = B0_L0HadronDecision_TOS;
      l0HadronTIS  = B0_L0HadronDecision_TIS;
      hlt1TrackDec = (B0_Hlt1TrackMVADecision_Dec||B0_Hlt1TwoTrackMVADecision_Dec);
      hlt1TrackDec = (B0_Hlt1TrackMVADecision_Dec||B0_Hlt1TwoTrackMVADecision_Dec);
      hlt1TrackTOS = (B0_Hlt1TrackMVADecision_TOS||B0_Hlt1TwoTrackMVADecision_TOS);
      hlt1TrackTOS = (B0_Hlt1TrackMVADecision_TOS||B0_Hlt1TwoTrackMVADecision_TOS);
      hlt1TrackTIS = (B0_Hlt1TrackMVADecision_TIS||B0_Hlt1TwoTrackMVADecision_TIS);
      hlt1TrackTIS = (B0_Hlt1TrackMVADecision_TIS||B0_Hlt1TwoTrackMVADecision_TIS);
      hlt2TopoDec  = B0_Hlt2Topo2BodyDecision_Dec;
      hlt2TopoTOS  = B0_Hlt2Topo2BodyDecision_TOS;
      hlt2TopoTIS  = B0_Hlt2Topo2BodyDecision_TIS;
      hlt2B2HHDec  = B0_Hlt2B2HH_B2HHDecision_Dec;
      hlt2B2HHTOS  = B0_Hlt2B2HH_B2HHDecision_TOS;
      hlt2B2HHTIS  = B0_Hlt2B2HH_B2HHDecision_TIS;
      // Tagging variables Charm,Ele,Kaon,Muon,Vtx
      // B0_OSCharm_TAGETA != 0 ? etaOScharm = B0_OSCharm_TAGETA : etaOScharm = 0.5;
      // B0_OSCharm_TAGETA != 0 ? qOScharm   = B0_OSCharm_TAGDEC : qOScharm = 0;
      qOScharm     = (B0_OSCharm_TAGETA != 0    &&
                      B0_OSCharm_TAGETA          < 0.5) ? B0_OSCharm_TAGDEC          : 0;
      etaOScharm   = (B0_OSCharm_TAGETA != 0    &&
                      B0_OSCharm_TAGETA          < 0.5) ? B0_OSCharm_TAGETA          : 0.5;
      qOSele_old   = (B0_OSElectron_TAGETA       < 0.5) ? B0_OSElectron_TAGDEC       : 0;
      etaOSele_old = (B0_OSElectron_TAGETA       < 0.5) ? B0_OSElectron_TAGETA       : 0.5;
      qOSele       = (B0_OSElectronLatest_TAGETA < 0.5) ? B0_OSElectronLatest_TAGDEC : 0;
      etaOSele     = (B0_OSElectronLatest_TAGETA < 0.5) ? B0_OSElectronLatest_TAGETA : 0.5;
      qOSk_old     = (B0_OSKaon_TAGETA           < 0.5) ? B0_OSKaon_TAGDEC           : 0;
      etaOSk_old   = (B0_OSKaon_TAGETA           < 0.5) ? B0_OSKaon_TAGETA           : 0.5;
      qOSk         = (B0_OSKaonLatest_TAGETA     < 0.5) ? B0_OSKaonLatest_TAGDEC     : 0;
      etaOSk       = (B0_OSKaonLatest_TAGETA     < 0.5) ? B0_OSKaonLatest_TAGETA     : 0.5;
      qOSmu_old    = (B0_OSMuon_TAGETA           < 0.5) ? B0_OSMuon_TAGDEC           : 0;
      etaOSmu_old  = (B0_OSMuon_TAGETA           < 0.5) ? B0_OSMuon_TAGETA           : 0.5;
      qOSmu        = (B0_OSMuonLatest_TAGETA     < 0.5) ? B0_OSMuonLatest_TAGDEC     : 0; 
      etaOSmu      = (B0_OSMuonLatest_TAGETA     < 0.5) ? B0_OSMuonLatest_TAGETA     : 0.5; 
      qOSvtx       = (B0_OSVtxCh_TAGETA          < 0.5) ? B0_OSVtxCh_TAGDEC          : 0;    
      etaOSvtx     = (B0_OSVtxCh_TAGETA          < 0.5) ? B0_OSVtxCh_TAGETA          : 0.5;    
      qSSk_old     = (B0_SSKaon_TAGETA           < 0.5) ? B0_SSKaon_TAGDEC           : 0;
      etaSSk_old   = (B0_SSKaon_TAGETA           < 0.5) ? B0_SSKaon_TAGETA           : 0.5;
      qSSk         = (B0_SSKaonLatest_TAGETA     < 0.5) ? B0_SSKaonLatest_TAGDEC     : 0;
      etaSSk       = (B0_SSKaonLatest_TAGETA     < 0.5) ? B0_SSKaonLatest_TAGETA     : 0.5;
      qSSpi        = (B0_SSPion_TAGETA           < 0.5) ? B0_SSPion_TAGDEC           : 0;
      etaSSpi      = (B0_SSPion_TAGETA           < 0.5) ? B0_SSPion_TAGETA           : 0.5;
      qSSp         = (B0_SSProton_TAGETA         < 0.5) ? B0_SSProton_TAGDEC         : 0;
      etaSSp       = (B0_SSProton_TAGETA         < 0.5) ? B0_SSProton_TAGETA         : 0.5;
      
      if (fyear != "2017") {
        tmp_qOS   = {qOScharm, qOSele, qOSk, qOSmu, qOSvtx};
        tmp_etaOS = {etaOScharm, etaOSele, etaOSk, etaOSmu, etaOSvtx};
      } else {
        tmp_qOS   = {qOScharm, qOSele_old, qOSk_old, qOSmu_old, qOSvtx};
        tmp_etaOS = {etaOScharm, etaOSele_old, etaOSk_old, etaOSmu_old, etaOSvtx};
      }
      combineTaggers(qOS,etaOS,tmp_qOS,tmp_etaOS,p0OS,p1OS,etaHatOS);
      tmp_qOS.clear(); tmp_etaOS.clear();

      tmp_qSS   = {qSSpi, qSSp};
      tmp_etaSS = {etaSSpi, etaSSp};
      combineTaggers(qSS,etaSS,tmp_qSS,tmp_etaSS,p0SS,p1SS,etaHatSS);
      tmp_qSS.clear(); tmp_etaSS.clear();
      
      vars[0] = min(piplusPT,piminusPT);
      vars[1] = log(min(piplusIPCHI2,piminusIPCHI2));
      vars[2] = max(piplusPT,piminusPT);
      vars[3] = log(max(piplusIPCHI2,piminusIPCHI2));
      vars[4] = bDOCA;
      vars[5] = bVTXCHI2;
      vars[6] = bIPCHI2;
      vars[7] = log(bFDCHI2);
      vars[8] = bPT;

      BDT1_PIPI = readerPIPI->EvaluateMVA(vars, bdtWeights::bdtPIPI[fyear][0].first);
      BDT2_PIPI = readerPIPI->EvaluateMVA(vars, bdtWeights::bdtPIPI[fyear][1].first);
      BDT3_PIPI = readerPIPI->EvaluateMVA(vars, bdtWeights::bdtPIPI[fyear][2].first);
      BDT1_KK = readerKK->EvaluateMVA(vars, bdtWeights::bdtKK[fyear][0].first);
      BDT2_KK = readerKK->EvaluateMVA(vars, bdtWeights::bdtKK[fyear][1].first);
      BDT3_KK = readerKK->EvaluateMVA(vars, bdtWeights::bdtKK[fyear][2].first);

      // BDTG1_PIPI = readerGPIPI->EvaluateMVA(vars, "BDT1");
      // BDTG2_PIPI = readerGPIPI->EvaluateMVA(vars, "BDT2");
      // BDTG3_PIPI = readerGPIPI->EvaluateMVA(vars, "BDT3");
      // BDTG1_KK = readerGKK->EvaluateMVA(vars, "BDT1");
      // BDTG2_KK = readerGKK->EvaluateMVA(vars, "BDT2");
      // BDTG3_KK = readerGKK->EvaluateMVA(vars, "BDT3");

      bdtPIPI = idBDT == 2 ? BDT1_PIPI : idBDT == 3 ? BDT2_PIPI : BDT3_PIPI;
      bdtKK   = idBDT == 2 ? BDT1_KK   : idBDT == 3 ? BDT2_KK   : BDT3_KK;
      bdtgPIPI = idBDT == 2 ? BDTG1_PIPI : idBDT == 3 ? BDTG2_PIPI : BDTG3_PIPI;
      bdtgKK   = idBDT == 2 ? BDTG1_KK   : idBDT == 3 ? BDTG2_KK   : BDTG3_KK;

      outTree->Fill();

      //if(jentry%10000 == 0) printf("PROCESSED 10k EVENTS\n");
   }

   TFile * outFile = new TFile(Form("$B2HH_OUT/Data/tuple/%s_%s_%s_%d.root",fdecay.Data(),fyear.Data(),fmagnet.Data(),findex),
                               "RECREATE","",6);
   outTree->Write("",TObject::kOverwrite);
   outFile->Close();

}
