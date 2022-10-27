#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TMVA/Reader.h>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TH3D.h>
#include <TH2D.h>
#include <TRandom3.h>
#include <TBits.h>
#include <optionParser.h>
#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>
using namespace std;

void getCuts(Int_t argc, Char_t * argv[], TString option,
             Int_t *cut, TString default_value) {

  TString value;
  int iOptions = findOption(argc,argv,option);
  if(iOptions > 0 && iOptions < argc-1)
    value = argv[iOptions+1];
  else
    value = default_value;

  for(Int_t iCut = 0; iCut < value.Tokenize(".")->GetEntries(); iCut++)
    cut[iCut] = ((TObjString *) value.Tokenize(".")->At(iCut))->String().Atoi();
    
}

inline Double_t getHHAngle(Double_t phi1, Double_t eta1,
                           Double_t phi2, Double_t eta2)
{
  Double_t theta1 = 2 * atan(exp(-eta1));
  Double_t theta2 = 2 * atan(exp(-eta2));
  Double_t cosAng = sin(theta1) * sin(theta2) * cos(phi2 - phi1) +
                    cos(theta1) * cos(theta2);
  Double_t angRad = acos(cosAng);
  Double_t angGrad = angRad * 180 / acos(-1);
  return angGrad;
}

int main(int argc, char * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./reduce [options]\n");
    printf("Options:\n");
    printf("  -n <name>       : decay used for BDT train ([PIPI, KK], default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = 0.04)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2011,2012,Tot], default = 2016)\n");
    printf("  -pipi <pipiCut> : PID cuts for pipi final state (default = -2.3.-2.3)\n");
    printf("  -kk   <kkCut>   : PID cuts for kk final state (default = 2.-2.2.-2)\n");
    printf("  -kpi <kpiCut>   : PID cuts for kpi final state (default = 5.-2.-5.3)\n");
    printf("  -pik <pikCut>   : PID cuts for pik final state (default = -5.3.5.-2)\n");
    return 0;
  }

  TString name          = getOption(argc,argv,"-n","PIPI");
  Double_t bdtCut       = atof(getOption(argc,argv,"-b","0.04"));
  TString magnet        = getOption(argc,argv,"-m","Tot");
  TString year          = getOption(argc,argv,"-y","2016");
  std::vector<Int_t> cutsPIPI(4,0);
  std::vector<Int_t> cutsKK(4,0);
  std::vector<Int_t> cutsKPI(4,0);
  std::vector<Int_t> cutsPIK(4,0);
  getCuts(argc,argv,"-pipi",&cutsPIPI[0],"-2.3.-2.3");
  getCuts(argc,argv,"-kpi", &cutsKPI[0], "5.-2.-5.3");
  getCuts(argc,argv,"-pik", &cutsPIK[0], "-5.3.5.-2");
  getCuts(argc,argv,"-kk",  &cutsKK[0],  "5.-2.5.-2");

  printf("EXECUTING ./reduce -n %s -b %g -m %s -y %s -pipi %d.%d.%d.%d -kk %d.%d.%d.%d -kpi %d.%d.%d.%d -pik %d.%d.%d.%d\n",
         name.Data(),bdtCut,magnet.Data(),year.Data(),
         cutsPIPI[0],cutsPIPI[1],cutsPIPI[2],cutsPIPI[3],
         cutsKK[0],cutsKK[1],cutsKK[2],cutsKK[3],
         cutsKPI[0],cutsKPI[1],cutsKPI[2],cutsKPI[3],
         cutsPIK[0],cutsPIK[1],cutsPIK[2],cutsPIK[3]);


  TRandom3 evtRand1(192837465);

  Int_t fStateIdx = datasetFlags::yearFlags[year];
  

  Int_t    p = 0, fState = 0, nSPDHits = 0;
  Double_t BDT = 0, rFD = 0, rFDPV = 0, bPT = 0, bP = 0, bETA = 0,
           mass = 0, massPIPI = 0, massKPI = 0, massPIK = 0, massKK = 0;
  Double_t time = 0, timePIPI = 0, timeKPI = 0, timePIK = 0, timeKK = 0,
           timeErr = 0, timePIPIErr = 0, timeKPIErr = 0, timePIKErr = 0, timeKKErr = 0;
  Int_t    qOS = 0, qSSk = 0, qSSpi = 0, qSSp = 0, qSS = 0;
  Double_t etaOS = 0, etaSSk = 0, etaSSpi = 0, etaSSp = 0, etaSS = 0;
  Double_t piplusDLLKPI = 0, piplusDLLPPI = 0, 
           piminusDLLKPI = 0, piminusDLLPPI = 0;
  UInt_t runNumber = 0; ULong64_t eventNumber = 0;
  Double_t piplusP = 0, piminusP = 0;
  

  
  TChain * inChain = new TChain("inChain","inChain");
  auto tag_years = datasetFlags::chain_years[year];
  auto tag_magnet = datasetFlags::chain_magnet[magnet];
  chainAdder::chainAdder(inChain, "${B2HH_OUT}/Data/tuple_merged/%s_%s_%s.root/b2hh", 
                                  "b2hh", tag_years, tag_magnet);
  
  inChain->SetBranchStatus("*", 0);
  inChain->SetBranchStatus("bPT", 1);
  inChain->SetBranchStatus("rFD*",1);
  inChain->SetBranchStatus("bP",1);        inChain->SetBranchStatus("bETA",1);
  inChain->SetBranchStatus("mass*",1);     inChain->SetBranchStatus("*DLL*",1);
  inChain->SetBranchStatus("runNumber",1); inChain->SetBranchStatus("eventNumber",1);
  inChain->SetBranchStatus("tau*",1);
  inChain->SetBranchStatus("eta*",1);      inChain->SetBranchStatus("q*",1);
  inChain->SetBranchStatus("nSPDHits",1);
  inChain->SetBranchStatus("bdt"+name, 1);
  // MASS VARIABLES
  inChain->SetBranchAddress("massPIPI",     &massPIPI);
  inChain->SetBranchAddress("massKPI",      &massKPI);       
  inChain->SetBranchAddress("massPIK",      &massPIK);
  inChain->SetBranchAddress("massKK",       &massKK);
  // TIME VARIABLES
  inChain->SetBranchAddress("tauPIPI",      &timePIPI);      inChain->SetBranchAddress("tauPIPIErr",   &timePIPIErr);
  inChain->SetBranchAddress("tauKPI",       &timeKPI);       inChain->SetBranchAddress("tauKPIErr",    &timeKPIErr);
  inChain->SetBranchAddress("tauPIK",       &timePIK);       inChain->SetBranchAddress("tauPIKErr",    &timePIKErr);
  inChain->SetBranchAddress("tauKK",        &timeKK);        inChain->SetBranchAddress("tauKKErr",     &timeKKErr);
  // TAGGING VARIABLES
  inChain->SetBranchAddress("qOS",       &qOS);              inChain->SetBranchAddress("etaOS",        &etaOS);
  if (year == "2017"){
    inChain->SetBranchAddress("qSSk_old",    &qSSk);         inChain->SetBranchAddress("etaSSk_old",   &etaSSk);
  } else {
    inChain->SetBranchAddress("qSSk",    &qSSk);             inChain->SetBranchAddress("etaSSk",       &etaSSk);
  } 
  inChain->SetBranchAddress("qSSk",    &qSSk);               inChain->SetBranchAddress("etaSSk",       &etaSSk);
  inChain->SetBranchAddress("qSSpi",  &qSSpi);               inChain->SetBranchAddress("etaSSpi",      &etaSSpi);
  inChain->SetBranchAddress("qSSp",      &qSSp);             inChain->SetBranchAddress("etaSSp",       &etaSSp);
  inChain->SetBranchAddress("qSS",      &qSS);               inChain->SetBranchAddress("etaSS",        &etaSS);
  // PID VARIABLES
  inChain->SetBranchAddress("piplusDLLKPI", &piplusDLLKPI);  inChain->SetBranchAddress("piplusDLLPPI", &piplusDLLPPI);
  inChain->SetBranchAddress("piminusDLLKPI",&piminusDLLKPI); inChain->SetBranchAddress("piminusDLLPPI",&piminusDLLPPI);
  inChain->SetBranchAddress("rFD",&rFD);
  inChain->SetBranchAddress("rFDPV",&rFDPV);
  inChain->SetBranchAddress("bPT",&bPT);
  inChain->SetBranchAddress("bP",&bP);
  inChain->SetBranchAddress("bETA",&bETA);
  inChain->SetBranchAddress("nSPDHits",&nSPDHits);
  // EVENT VARIABLES
  inChain->SetBranchAddress(Form("bdt%s",name.Data()),&BDT);
  inChain->SetBranchAddress("runNumber",    &runNumber);
  inChain->SetBranchAddress("eventNumber",  &eventNumber);

  Double_t piplusETA, piplusPHI, piminusETA, piminusPHI, hhAngle; 
  inChain->SetBranchStatus("piplusETA"),  inChain->SetBranchAddress("piplusETA", &piplusETA);
  inChain->SetBranchStatus("piplusPHI"),  inChain->SetBranchAddress("piplusPHI", &piplusPHI);
  inChain->SetBranchStatus("piminusETA"), inChain->SetBranchAddress("piminusETA", &piminusETA);
  inChain->SetBranchStatus("piminusPHI"), inChain->SetBranchAddress("piminusPHI", &piminusPHI);
  
  inChain->SetBranchStatus("piplusP"),    inChain->SetBranchAddress("piplusP", &piplusP);
  inChain->SetBranchStatus("piminusP"),   inChain->SetBranchAddress("piminusP", &piminusP);
  
  
  TTree * outTree = new TTree("b2hh_bak","b2hh_bak");
  outTree->SetDirectory(0);
  outTree->Branch("rFD",        &rFD,        "rFD/D");
  outTree->Branch("rFDPV",      &rFDPV,      "rFDPV/D");
  outTree->Branch("bPT",        &bPT,        "bPT/D");
  outTree->Branch("bETA",       &bETA,       "bETA/D");
  outTree->Branch("bP",         &bP,         "bP/D");
  outTree->Branch("nSPDHits",   &nSPDHits,   "nSPDHits/I");
  outTree->Branch("mass",       &mass,       "mass/D");
  outTree->Branch("time",       &time,       "time/D");
  outTree->Branch("timeErr",    &timeErr,    "timeErr/D");
  outTree->Branch("p",          &p,          "p/I");
  outTree->Branch("fState",     &fState,     "fState/I");
  outTree->Branch("qOS",        &qOS,        "qOS/I");
  outTree->Branch("qSSk",       &qSSk,       "qSSk/I");
  outTree->Branch("qSSpi",      &qSSpi,      "qSSpi/I");
  outTree->Branch("qSSp",       &qSSp,       "qSSp/I");
  outTree->Branch("qSS",        &qSS,        "qSS/I");
  outTree->Branch("etaOS",      &etaOS,      "etaOS/D");
  outTree->Branch("etaSSk",     &etaSSk,     "etaSSk/D");
  outTree->Branch("etaSSpi",    &etaSSpi,    "etaSSpi/D");
  outTree->Branch("etaSSp",     &etaSSp,     "etaSSp/D");
  outTree->Branch("etaSS",      &etaSS,      "etaSS/D");
  outTree->Branch("runNumber",  &runNumber,  "runNumber/i");
  outTree->Branch("eventNumber",&eventNumber,"eventNumber/l");
  outTree->Branch(Form("bdt%s",name.Data()),&BDT,Form("bdt%s/D",name.Data()));
  outTree->Branch("hhAngle",    &hhAngle,   "hhAngle/D");
  outTree->Branch("piplusP",    &piplusP,   "piplusP/D");
  outTree->Branch("piminusP",   &piminusP,  "piminusP/D");
  Long64_t nEntries = inChain->GetEntries();

  Double_t mass_min = selection_cuts::mass_min;
  Double_t mass_max = selection_cuts::mass_max;
  Double_t time_min = selection_cuts::time_min;
  Double_t time_max = selection_cuts::time_max;
  Double_t timeErr_max = selection_cuts::timeErr_max;

  for(Long64_t ievt = 0; ievt < nEntries; ++ievt) {

    inChain->GetEntry(ievt);

    if (!(ievt%100000)) printf("Analysed event %lld/%lld\n",ievt,nEntries);
    if (BDT<bdtCut) continue;
    Bool_t isPIPI = piplusDLLKPI < cutsPIPI[0] && piplusDLLPPI < cutsPIPI[1] &&
                    piminusDLLKPI < cutsPIPI[2] && piminusDLLPPI < cutsPIPI[3];
    
    Bool_t isKPI = piplusDLLKPI > cutsKPI[0] && piplusDLLKPI - piplusDLLPPI > cutsKPI[1] &&
                   piminusDLLKPI < cutsKPI[2] && piminusDLLPPI < cutsKPI[3];
    
    Bool_t isPIK = piplusDLLKPI < cutsPIK[0] && piplusDLLPPI < cutsPIK[1] &&
                   piminusDLLKPI > cutsPIK[2] && piminusDLLKPI - piminusDLLPPI > cutsPIK[3];
    
    Bool_t isKK = piplusDLLKPI > cutsKK[0] && piplusDLLKPI - piplusDLLPPI > cutsKK[1] &&
                  piminusDLLKPI > cutsKK[2] && piminusDLLKPI - piminusDLLPPI > cutsKK[3];
    
    if (isPIPI){
      p = datasetFlags::spectrumPIPI;
      mass = massPIPI;
      time = timePIPI;
      timeErr = timePIPIErr;
    } else if (isKPI){
      p = datasetFlags::spectrumKPI;
      mass = massKPI;
      time = timeKPI;
      timeErr = timeKPIErr;
    } else if (isPIK){
      p = datasetFlags::spectrumPIK;
      mass = massPIK;
      time = timePIK;
      timeErr = timePIKErr;
    } else if (isKK){
      p = datasetFlags::spectrumKK;
      mass = massKK;
      time = timeKK;
      timeErr = timeKKErr;
    } else continue;
    
    if (mass < mass_min) continue;
    if (mass > mass_max) continue;
    if (time < time_min) continue;
    if (time > time_max) continue;
    if (timeErr > timeErr_max) continue;
    
    fState = abs(p) + fStateIdx;
    hhAngle = getHHAngle(piplusPHI, piplusETA, piminusPHI, piminusETA);
    outTree->Fill();
  }

  printf("\n");

  TTree * outTreeRed = outTree->CloneTree(0);
  outTreeRed->SetDirectory(0);
  outTreeRed->SetName("b2hh"); outTreeRed->SetTitle("b2hh");
  ULong64_t redEntries = outTree->GetEntries();
  ULong64_t readEntries = 0, ientry = 0;
  TRandom3 evtRand(192837465);
  map< pair< UInt_t, ULong64_t >, Bool_t > selEvents;
  pair< UInt_t, ULong64_t > tmpPair;
  TBits redEntry(redEntries);
  while(1) {
    ientry = evtRand.Integer(redEntries);
    if(redEntry.TestBitNumber(ientry)) continue; 
    redEntry.SetBitNumber(ientry);
    outTree->GetEntry(ientry);
    readEntries++;
    if(readEntries % 1000 == 0) printf("%llu/%llu \b\r",readEntries,redEntries);
    tmpPair = std::make_pair(runNumber,eventNumber);
    if(selEvents.find(tmpPair)!= selEvents.end() && selEvents[tmpPair]) continue;
    selEvents[tmpPair] = true;
    outTreeRed->Fill();
    if(readEntries>=redEntries) break;
  }
  printf("\n");

  TFile * outFile = TFile::Open(Form("${B2HH_OUT}/Reduce/b2hh_%s_%g_%s_%s.root",name.Data(),bdtCut,year.Data(),magnet.Data()),"RECREATE");
  outFile->WriteTObject(outTree,"","Overwrite");
  outFile->WriteTObject(outTreeRed,"","Overwrite");
  outFile->Close();

}
