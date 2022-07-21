#include <iostream>

#include <vector>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TPad.h"
using namespace std;

int main(int argc, char* argv[]){
  TString mode = argv[1];
  TString year = argv[2];
  TString magn = argv[3];
  vector<TString> nfs_in = {
    Form("/home/LHCB-T3/dmanuzzi/B2HH/data/%s/%s/Mag%s/B2DX_%s_%s_%s_sWeight.root",
	 mode.Data(), year.Data(), magn.Data(), year.Data(), magn.Data(), mode.Data())
  };
  
  vector<TString> nfs_target = {
    "/home/LHCB-T3/dmanuzzi/B2HH/MC/samples/Bs2KK/bskk_2016_Up.root",
    "/home/LHCB-T3/dmanuzzi/B2HH/MC/samples/Bs2KK/bskk_2016_Down.root"
  };
 
  TString nf_out = Form("/home/LHCB-T3/dmanuzzi/B2HH/data/%s/%s/Mag%s/B2DX_%s_%s_%s_sWeight_wPT.root",
			mode.Data(), year.Data(), magn.Data(), year.Data(), magn.Data(), mode.Data());


  Int_t nbins_PT = 100;
  Double_t min_PT = 0.; //MeV
  Double_t max_PT = 30000.; //MeV

  ///////////////////////////////////////
  TH1::SetDefaultSumw2();

  TChain t_in("DecayTree");
  for (auto nf_in : nfs_in){
    t_in.Add(nf_in);
  }
  
  TChain t_target("b2hh");
  for (auto nf_target : nfs_target){
    t_target.Add(nf_target);
  }

  TFile f_out(nf_out, "RECREATE");
  // TTree t_out("DecayTree_wPT", "DecayTree_wPT");
  TTree * t_out = t_in.CloneTree(-1);
  Double_t wPT=0.;
  TBranch * b_wPT = t_out->Branch("wPT", &wPT, "wPT/D");

  t_in.SetBranchStatus("*", 0);
  t_in.SetBranchStatus("lab0_PT", 1);
  t_in.SetBranchStatus("sWeight", 1);
  Double_t lab0_PT=0., sWeight=0.;
  t_in.SetBranchAddress("lab0_PT", &lab0_PT);
  t_in.SetBranchAddress("sWeight", &sWeight);
  TH1D h_PT_in("h_PT_in", "input; p_{T}(B^{0}) [MeV];", nbins_PT, min_PT, max_PT);
  Int_t nentries_in = t_in.GetEntries();
  for (int i=0; i<nentries_in; ++i){
    t_in.GetEntry(i);
    h_PT_in.Fill(lab0_PT, sWeight);
  }
  h_PT_in.Print("v");
  t_target.SetBranchStatus("*", 0);
  t_target.SetBranchStatus("bPT", 1);
  t_target.SetBranchStatus("idBDT",1);
  t_target.SetBranchStatus("BDT1_KK",1);
  t_target.SetBranchStatus("BDT2_KK",1);
  t_target.SetBranchStatus("BDT3_KK",1);

  t_target.SetBranchStatus("piplusDLLKPI",1);
  t_target.SetBranchStatus("piplusDLLPPI",1);
  t_target.SetBranchStatus("piminusDLLKPI",1);
  t_target.SetBranchStatus("piminusDLLPPI",1);
  t_target.SetBranchStatus("massPIPI",1);
  t_target.SetBranchStatus("massKPI",1);
  t_target.SetBranchStatus("massPIK",1);
  t_target.SetBranchStatus("massKK",1);
  t_target.SetBranchStatus("tauPIPI",1);
  t_target.SetBranchStatus("tauKPI",1);
  t_target.SetBranchStatus("tauPIK",1);
  t_target.SetBranchStatus("tauKK",1);
  t_target.SetBranchStatus("tauPIPIErr",1);
  t_target.SetBranchStatus("tauKPIErr",1);
  t_target.SetBranchStatus("tauPIKErr",1);
  t_target.SetBranchStatus("tauKKErr",1);

  Double_t bPT=0.;
  Int_t idBDT=0;
  Double_t BDT1_KK=0., BDT2_KK=0., BDT3_KK=0.;
  Double_t piplusDLLKPI=0., piplusDLLPPI=0., piminusDLLKPI=0., piminusDLLPPI=0.;
  Double_t massPIPI=0., massKPI=0., massPIK=0., massKK=0.;
  Double_t tauPIPI=0., tauKPI=0., tauPIK=0., tauKK=0.;
  Double_t tauPIPIErr=0., tauKPIErr=0., tauPIKErr=0., tauKKErr=0.;
  
  t_target.SetBranchAddress("bPT", &bPT);
  t_target.SetBranchAddress("idBDT", &idBDT);
  t_target.SetBranchAddress("BDT1_KK", &BDT1_KK);
  t_target.SetBranchAddress("BDT2_KK", &BDT2_KK);
  t_target.SetBranchAddress("BDT3_KK", &BDT3_KK);
  t_target.SetBranchAddress("piplusDLLKPI", &piplusDLLKPI);
  t_target.SetBranchAddress("piplusDLLPPI", &piplusDLLPPI);
  t_target.SetBranchAddress("piminusDLLKPI", &piminusDLLKPI);
  t_target.SetBranchAddress("piminusDLLPPI", &piminusDLLPPI);
  t_target.SetBranchAddress("massPIPI", &massPIPI);
  t_target.SetBranchAddress("massKPI", &massKPI);
  t_target.SetBranchAddress("massPIK", &massKPI);
  t_target.SetBranchAddress("massKK", &massKK);
  t_target.SetBranchAddress("tauPIPI", &tauPIPI);
  t_target.SetBranchAddress("tauKPI", &tauKPI);
  t_target.SetBranchAddress("tauPIK", &tauKPI);
  t_target.SetBranchAddress("tauKK", &tauKK);
  t_target.SetBranchAddress("tauPIPIErr", &tauPIPIErr);
  t_target.SetBranchAddress("tauKPIErr", &tauKPIErr);
  t_target.SetBranchAddress("tauPIKErr", &tauKPIErr);
  t_target.SetBranchAddress("tauKKErr", &tauKKErr);
  vector<Double_t> cutsPIPI = {-2,3,-2,3};
  vector<Double_t> cutsKPI  = {5,-2,-5,3};
  vector<Double_t> cutsPIK  = {-5,3,5,-2};
  vector<Double_t> cutsKK   = {2,-2,2,-2};
  Double_t bdtCut = 0.04;
  TH1D h_PT_target("h_PT_target", "target; p_{T}(B^{0}) [MeV];", nbins_PT, min_PT, max_PT);
  Int_t nentries_target = t_target.GetEntries();
  for (int i=0; i<nentries_target; ++i){
    t_target.GetEntry(i);
    Double_t BDTs[3] = {BDT1_KK, BDT2_KK, BDT3_KK};
    Double_t BDT = BDTs[idBDT-1];
    if (BDT<bdtCut) continue;
    bool cutPIPI = (piplusDLLKPI < cutsPIPI[0] && piplusDLLPPI < cutsPIPI[1] &&
		    piminusDLLKPI < cutsPIPI[2] && piminusDLLPPI < cutsPIPI[3] &&
		    massPIPI > 5 && massPIPI < 6.2 &&
		    tauPIPI>0.2 && tauPIPI<14.2 && tauPIPIErr<0.1);
    bool cutKPI  = (piplusDLLKPI > cutsKPI[0] && piplusDLLKPI-piplusDLLPPI > cutsKPI[1] &&
		    piminusDLLKPI < cutsKPI[2] && piminusDLLPPI < cutsKPI[3] &&
		    massKPI > 5 && massKPI < 6.2 &&
                    tauKPI>0.2 && tauKPI<14.2 && tauKPIErr<0.1);
    bool cutPIK  = (piplusDLLKPI < cutsPIK[0] && piplusDLLPPI < cutsPIK[1] &&
		    piminusDLLKPI > cutsPIK[2] && piminusDLLKPI-piminusDLLPPI > cutsPIK[3] &&
		    massPIK > 5 && massPIK < 6.2 &&
                    tauPIK>0.2 && tauPIK<14.2 && tauPIKErr<0.1);
    bool cutKK   = (piplusDLLKPI > cutsKK[0] && piplusDLLKPI-piplusDLLPPI > cutsKK[1] &&
		    piminusDLLKPI > cutsKK[2] && piminusDLLKPI-piminusDLLPPI > cutsKK[3] &&
		    massKK > 5 && massKK < 6.2 &&
                    tauKK>0.2 && tauKK<14.2 && tauKKErr<0.1);
    if (cutPIPI) continue;
    if (cutKPI ) continue;
    if (cutPIK ) continue;
    if (!cutKK ) continue;
    h_PT_target.Fill(bPT*1000);
  }
  h_PT_target.Print("v");
  h_PT_target.Scale(h_PT_in.Integral()/h_PT_target.Integral());
  TH1D h_ratio_PT("h_ratio_PT", "ratio; p_{T}(B^{0}) [GeV]; target/input", nbins_PT, min_PT, max_PT);
  h_ratio_PT.Divide(&h_PT_target, &h_PT_in);
  h_ratio_PT.Print("v");


  
  TH1D h_PT_out("h_PT_out", "output; p_{T}(B^{0}) [MeV];", nbins_PT, min_PT, max_PT);
  for (int i=0; i<nentries_in; ++i){
    t_in.GetEntry(i);
    wPT = (lab0_PT>max_PT || lab0_PT<min_PT)? 0. : h_ratio_PT.GetBinContent(h_ratio_PT.FindBin(lab0_PT));
    b_wPT->Fill();
    //t_out->Fill();
    h_PT_out.Fill(lab0_PT, sWeight*wPT);
  }
  h_PT_out.Print("v");

  TCanvas canv("reweigh_monitor", "reweigh monitor", 600, 600);
  h_PT_in.SetMarkerColor(kRed);
  h_PT_target.SetMarkerColor(kGreen+2);
  h_PT_out.SetMarkerColor(kBlue);
  h_PT_in.SetMarkerStyle(20);
  h_PT_target.SetMarkerStyle(20);
  h_PT_out.SetMarkerStyle(24);
  TPad pad1("pad1","pad1", 0.05,0.27,0.95,0.95);  
  pad1.Draw();
  pad1.cd();
  THStack stack("hs_reweigh_monitor", "hs_reweigh_monitor");
  stack.Add(&h_PT_in);
  stack.Add(&h_PT_target);
  stack.Add(&h_PT_out);
  //stack.GetXaxis()->SetTitle("p_{T}(B^{0}) [MeV]"); not working
  stack.Draw("nostack,e1p");
  pad1.SetGridx();
  pad1.SetGridy();
  pad1.BuildLegend();
  canv.cd();
  TPad pad2("pad2","pad2", 0.05,0.05,0.95,0.25);
  pad2.Draw();
  pad2.cd();
  pad2.SetGridx();
  pad2.SetGridy();
  h_ratio_PT.Draw("PE1");

  f_out.WriteTObject(t_out);
  f_out.WriteTObject(&h_PT_in);
  f_out.WriteTObject(&h_PT_target);
  f_out.WriteTObject(&h_ratio_PT);
  f_out.WriteTObject(&h_PT_out);
  f_out.WriteTObject(&canv);
  f_out.Print("v");
  f_out.Close();
  
  return 0;
}
