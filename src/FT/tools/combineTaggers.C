#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
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


int main(int argc, char *argv[]){
	if (argc != 5){
		printf("COMBINE TAGGERS: ERROR, wrong number of arguments! (%d given instead of 4)\n", argc-1);
		return 0;
	}
	TString nfin        = argv[1];
	TString nfcalibs_new = argv[2];
	TString nfcalibs_old = argv[3];
	TString nfout       = argv[4];
	
	printf("Input      : %s\n", nfin.Data());
	printf("Calib. new : %s\n", nfcalibs_new.Data());
	printf("Calib. old : %s\n", nfcalibs_old.Data());
	printf("Output     : %s\n", nfout.Data());
	

  map<TString,Float_t> calibs;
	string line;
	TString tline;
	// get calib for new taggers
  ifstream fcalib_new(nfcalibs_new.Data());
  if (fcalib_new.is_open()){
    while ( getline(fcalib_new,line) )
    {
      //cout << line << '\n';
      tline = line.data();
      tline.ReplaceAll(" ", "");
      tline.ReplaceAll("\n", "");
      auto mark = tline.First("=");
      if (mark<0) continue;
      TString key = tline(0,mark);
      TString sval= tline(mark+1, tline.Length());
      if (!sval.IsFloat()) continue;
      Float_t val = atof(sval.Data()); 
      calibs[key] = val;
    }
    fcalib_new.close();
  } else {
    printf("COMBINE TAGGERS: ERROR, unable to open file %s\n", nfcalibs_new.Data()); 
    return 0;
  }
  // get calib for old taggers
	ifstream fcalib_old(nfcalibs_old.Data());
  if (fcalib_old.is_open()){
    while ( getline(fcalib_old,line) )
    {
      //cout << line << '\n';
      tline = line.data();
      tline.ReplaceAll(" ", "");
      tline.ReplaceAll("\n", "");
      auto mark = tline.First("=");
      if (mark<0) continue;
      TString key = tline(0,mark);
      key.Append("_old");
      TString sval= tline(mark+1, tline.Length());
      if (!sval.IsFloat()) continue;
      Float_t val = atof(sval.Data()); 
      calibs[key] = val;
    }
   	fcalib_old.close();
  } else {
    printf("COMBINE TAGGERS: ERROR, unable to open file %s\n", nfcalibs_old.Data()); 
    return 0;
  }

  // for (auto p : calibs)
  //   		cout << p.first << " " << p.second << endl;


  std::vector<Double_t> p0OS, p1OS, etaHatOS;
  // //Tagging variables Charm,Ele,Kaon,Muon,Vtx
  // //p0OS.push_back(0.3500); p1OS.push_back(0.722); etaHatOS.push_back(0.3580);
  // //p0OS.push_back(0.2947); p1OS.push_back(1.486); etaHatOS.push_back(0.3177);
  // //p0OS.push_back(0.3762); p1OS.push_back(1.492); etaHatOS.push_back(0.3782);
  // //p0OS.push_back(0.2560); p1OS.push_back(1.339); etaHatOS.push_back(0.2800);
  // //p0OS.push_back(0.3697); p1OS.push_back(1.059); etaHatOS.push_back(0.3797);
  // p0OS.push_back(0.3650-0.02438); p1OS.push_back(1-0.11462); etaHatOS.push_back(0.3650);
  // p0OS.push_back(0.3493-0.02348); p1OS.push_back(1+0.38189); etaHatOS.push_back(0.3493);
  // p0OS.push_back(0.3807-0.00511); p1OS.push_back(1+0.37668); etaHatOS.push_back(0.3807);
  // p0OS.push_back(0.3097-0.00922); p1OS.push_back(1+0.22421); etaHatOS.push_back(0.3097);
  // p0OS.push_back(0.3895-0.01080); p1OS.push_back(1-0.05588); etaHatOS.push_back(0.3895);
  vector<TString> OStaggers = {"OS_Charm", "OS_Electron", "OS_Kaon", "OS_Muon", "VtxCharge"};
  for (auto OStagger : OStaggers){
    Float_t tmp_etaHat = calibs[OStagger+"_Eta"]; 
    Float_t tmp_p0 = calibs[OStagger+"_P0"]+tmp_etaHat;
    Float_t tmp_p1 = calibs[OStagger+"_P1"];
    p0OS.push_back(tmp_p0);
    p1OS.push_back(tmp_p1);
    etaHatOS.push_back(tmp_etaHat);
  }
  std::vector<Double_t> p0SS, p1SS, etaHatSS;
  // //Tagging variables SSpi, SSp
  // //p0SS.push_back(0.4743); p1SS.push_back(0.976); etaHatSS.push_back(0.4727);
  // //p0SS.push_back(0.4741); p1SS.push_back(0.953); etaHatSS.push_back(0.4780);
  // p0SS.push_back(0.4463+0.00256); p1SS.push_back(1-0.01856); etaHatSS.push_back(0.4463);
  // p0SS.push_back(0.4604-0.00236); p1SS.push_back(1+0.00071); etaHatSS.push_back(0.4604);
  vector<TString> SStaggers = {"SS_Pion", "SS_Proton"};
  for (auto SStagger : SStaggers){
    Float_t tmp_etaHat = calibs[SStagger+"_Eta"]; 
    Float_t tmp_p0 = calibs[SStagger+"_P0"]+tmp_etaHat;
    Float_t tmp_p1 = calibs[SStagger+"_P1"];
    p0SS.push_back(tmp_p0);
    p1SS.push_back(tmp_p1);
    etaHatSS.push_back(tmp_etaHat);
  }

  TFile fin(nfin, "READ");
  TTree * tin = (TTree*)fin.Get("DecayTree");
  //tin->Print();
  tin->SetBranchStatus("*",0);
  tin->SetBranchStatus("*Number",1);
  tin->SetBranchStatus("*TAGDEC",1);
  tin->SetBranchStatus("*TAGETA",1);
  tin->SetBranchStatus("*TaggingTool*",0);
  tin->SetBranchStatus("sWeight",1);
  tin->SetBranchStatus("wPT",1);
  Int_t qOScharm=0, qOSele=0, qOSk=0, qOSmu=0, qOSvtx=0;
  Double_t etaOScharm=0, etaOSele=0, etaOSk=0, etaOSmu=0, etaOSvtx=0;
  Int_t qSSpi=0, qSSp=0;
  Double_t etaSSpi=0, etaSSp=0;
	
  Int_t qOSele_old=0, qOSk_old=0, qOSmu_old=0;
  Double_t etaOSele_old=0, etaOSk_old=0, etaOSmu_old=0;
	
  tin->SetBranchAddress("lab0_OSCharm_TAGDEC", &qOScharm);
  tin->SetBranchAddress("lab0_OSElectronLatest_TAGDEC", &qOSele);
  tin->SetBranchAddress("lab0_OSElectron_TAGDEC", &qOSele_old);
  tin->SetBranchAddress("lab0_OSKaonLatest_TAGDEC", &qOSk);
  tin->SetBranchAddress("lab0_OSKaon_TAGDEC", &qOSk_old);
  tin->SetBranchAddress("lab0_OSMuonLatest_TAGDEC", &qOSmu);
  tin->SetBranchAddress("lab0_OSMuon_TAGDEC", &qOSmu_old);
  tin->SetBranchAddress("lab0_OSVtxCh_TAGDEC", &qOSvtx);
  tin->SetBranchAddress("lab0_SSPion_TAGDEC", &qSSpi);
  tin->SetBranchAddress("lab0_SSProton_TAGDEC", &qSSp);
	
  tin->SetBranchAddress("lab0_OSCharm_TAGETA", &etaOScharm);
  tin->SetBranchAddress("lab0_OSElectronLatest_TAGETA", &etaOSele);
  tin->SetBranchAddress("lab0_OSElectron_TAGETA", &etaOSele_old);
  tin->SetBranchAddress("lab0_OSKaonLatest_TAGETA", &etaOSk);
  tin->SetBranchAddress("lab0_OSKaon_TAGETA", &etaOSk_old);
  tin->SetBranchAddress("lab0_OSMuonLatest_TAGETA", &etaOSmu);
  tin->SetBranchAddress("lab0_OSMuon_TAGETA", &etaOSmu_old);
  tin->SetBranchAddress("lab0_OSVtxCh_TAGETA", &etaOSvtx);
  tin->SetBranchAddress("lab0_SSPion_TAGETA", &etaSSpi);
  tin->SetBranchAddress("lab0_SSProton_TAGETA", &etaSSp);

  tin->SetBranchStatus("BeautyTime",1);
  tin->SetBranchStatus("BeautyTimeErr",1);
  tin->SetBranchStatus("lab0_ID",1);
  tin->SetBranchStatus("lab0_PT",1);
	
  TFile fout(nfout, "RECREATE");
  TTree * tout = tin->CloneTree(0);
  Int_t qOS=0, qSS=0;
  Double_t etaOS=0, etaSS=0;
  tout->Branch("qOS", &qOS, "qOS/I");
  tout->Branch("qSS", &qSS, "qSS/I");
  tout->Branch("etaOS", &etaOS, "etaOS/D");
  tout->Branch("etaSS", &etaSS, "etaSS/D");

  Int_t qOS_old=0, qSS_old=0;
  Double_t etaOS_old=0, etaSS_old=0;
  tout->Branch("qOS_old", &qOS_old, "qOS_old/I");
  tout->Branch("qSS_old", &qSS_old, "qSS_old/I");
  tout->Branch("etaOS_old", &etaOS_old, "etaOS_old/D");
  tout->Branch("etaSS_old", &etaSS_old, "etaSS_old/D");

  Int_t nentries = tin->GetEntries();
  vector<Int_t> tmp_qOS, tmp_qSS;
  vector<Double_t> tmp_etaOS, tmp_etaSS;
  vector<Int_t> tmp_qOS_old, tmp_qSS_old;
  vector<Double_t> tmp_etaOS_old, tmp_etaSS_old;
  for (Int_t i=0; i<nentries; ++i){
    tin->GetEntry(i);
    tmp_qOS   = {qOScharm, qOSele, qOSk, qOSmu, qOSvtx};
    tmp_etaOS = {etaOScharm, etaOSele, etaOSk, etaOSmu, etaOSvtx};
    tmp_qSS   = {qSSpi, qSSp};
    tmp_etaSS = {etaSSpi, etaSSp};
		
    tmp_qOS_old   = {qOScharm, qOSele_old, qOSk_old, qOSmu_old, qOSvtx};
    tmp_etaOS_old = {etaOScharm, etaOSele_old, etaOSk_old, etaOSmu_old, etaOSvtx};
    tmp_qSS_old   = {qSSpi, qSSp};
    tmp_etaSS_old = {etaSSpi, etaSSp};
		
    combineTaggers(qOS, etaOS, tmp_qOS, tmp_etaOS,p0OS, p1OS, etaHatOS);
    combineTaggers(qSS, etaSS, tmp_qSS, tmp_etaSS,p0SS, p1SS, etaHatSS);
    combineTaggers(qOS_old, etaOS_old, tmp_qOS_old, tmp_etaOS_old,p0OS, p1OS, etaHatOS);
    combineTaggers(qSS_old, etaSS_old, tmp_qSS_old, tmp_etaSS_old,p0SS, p1SS, etaHatSS);
		
    tout->Fill();
  }

  fout.WriteTObject(tout);
  //fout.Print();
  fout.Close();
  fin.Close();

  return 1;
}
