#include <iostream>
#include <vector>
#include <map>
#include "TString.h"
#include "TFile.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TObjString.h"
#include "TROOT.h"
#include "TGraphErrors.h"
using namespace std;


int main(int argc, char *argv[]){
  gROOT->ProcessLine(".x ${B2HH_SRC}/Tools/lhcbStyle.C");
  TString mode    = argv[1];
  TString bdt     = argv[2];
  TString bdtType = ((TObjString *)bdt.Tokenize('_')->At(0))->String();
  TString bdtCut  = ((TObjString *)bdt.Tokenize('_')->At(1))->String();
  TString magnet  = argv[3];
  TString tag     = ""; 
  if (argc==5)
    tag = argv[4];
  

  TString dataType = "DATA";
  TString decay    = "bdkpi";
  TString fstate   = "kpi";
  //  if (mode != "data"){
  //  dataType = "MC";
  //  decay    = ((TObjString *)mode.Tokenize('_')->At(0))->String();
  //  fstate   = ((TObjString *)mode.Tokenize('_')->At(1))->String();
  //}
  TString ftState = "Untagged";
  if (tag == "T") ftState = "Tagged";

  map< TString, vector<int> > year_color;
  //  year_color["20151618"]={kBlack, kSolid, 2};
  year_color["201516"] = {kGreen+2, kSolid, 2};
  //  year_color["2017"]   = {kRed, kDashed, 2};
  year_color["2017s29r2p2"]   = {kRed, kDashed, 2};
  year_color["2018"]   = {kBlue, 8, 2};

  TString suffix = "Kine";
  if (mode == "data") suffix = "Sub";
  TString config =  Form("acceptances%s_%s_%s_%s_%s", 
			 tag.Data(), mode.Data(), 
			 bdtType.Data(), bdtCut.Data(), 
			 magnet.Data());
  
  //TFile fout(Form("plots/%s.root", config.Data()), "RECREATE");
  TCanvas c("c_"+config, "c_"+config);
  //c.SetLeftMargin(0.15);
  //c.SetBottomMargin(0.15);

  TLegend * leg = new TLegend(0.55,0.35,0.75,0.55,"");

  int cont=0;
  for (auto it : year_color){
    cont += 1;
    TString tmp_year = it.first;
    int tmp_lineColor = it.second[0];
    int tmp_lineStyle = it.second[1];
    int tmp_lineWidth = it.second[2];
    TString tmp_nfin = Form("${B2HH_OUT}/AccSignal/acceptances/acceptancesNew_%s_%s_%s_%s.root", 
    			    bdtType.Data(), bdtCut.Data(), 
    			    tmp_year.Data(), magnet.Data());
    
    TString tmp_nfunc= Form("acc_%s_New%s", mode.Data(),tag.Data());
    printf("File: %s, function: %s\n", tmp_nfin.Data(), tmp_nfunc.Data());

    TFile *tmp_fin = new TFile(tmp_nfin, "READ");
    //TF1 *tmp_func = (TF1*)tmp_fin->Get(tmp_nfunc);
    TGraphErrors *tmp_func = (TGraphErrors*)tmp_fin->Get(tmp_nfunc);
    tmp_func->SetName(Form("%s_%s", tmp_func->GetName(), tmp_year.Data()));
    tmp_func->Print("v");
    tmp_func->SetLineColor(tmp_lineColor);
    tmp_func->SetLineStyle(tmp_lineStyle);
    tmp_func->SetLineWidth(tmp_lineWidth);
    if (cont == 1){
      tmp_func->Draw("AL");
      tmp_func->GetXaxis()->SetRangeUser(0,5);
      tmp_func->GetYaxis()->SetRangeUser(0,1.05);
      tmp_func->GetXaxis()->SetTitle("Decay time [ps]");
      tmp_func->GetYaxis()->SetTitle("Decay-time efficiency");
      tmp_func->SetTitle("");
      tmp_func->Draw("AL");
    } else
      tmp_func->Draw("Lsame");
    auto * tmp_curve = c.FindObject(tmp_func->GetName());
    leg->AddEntry(tmp_curve,tmp_year,"l");
  }
  
  TPaveText * lhcb = new TPaveText(0.55,0.55,0.75,0.85,"NDC");
  lhcb->SetTextAlign(12);
  lhcb->AddText("LHCb");
  //  lhcb->AddText(Form("%s %s, f. state: %s", dataType.Data(), decay.Data(), fstate.Data()));
  lhcb->AddText(Form("mode: %s", mode.Data()));
  lhcb->AddText(Form("bdt%s>%s, %s", bdtType.Data(), bdtCut.Data(), ftState.Data()));
  lhcb->SetFillColor(kWhite);
  //lhcb->SetTextFont(132);
  lhcb->SetTextSize(0.05);
  lhcb->Draw("same");
  leg->SetName("leg");
  //leg->SetTextFont(132);
  leg->SetTextSize(0.05);
  leg->SetFillColor(kWhite);
  //leg->SetBorderSize(0);
  //leg->SetX1(0.35);
  //leg->SetX2(0.35);
  //leg->SetY1(0.55);
  //leg->SetY2(0.75);
  leg->Draw("same");
  c.SaveAs(Form("${B2HH_OUT}/AccSignal/plots/finalAcc_%s.root", config.Data()));
  c.SaveAs(Form("${B2HH_OUT}/AccSignal/plots/finalAcc%s.pdf", config.Data()));
  return 1;
}
