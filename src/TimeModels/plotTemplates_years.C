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
#include "RooWorkspace.h"
#include "RooAbsPdf.h"
#include "RooRealVar.h"
#include "RooPlot.h"
using namespace std;
using namespace RooFit; 


int main(int argc, char *argv[]){
  gROOT->ProcessLine(".x ${B2HH_SRC}/Tools/lhcbStyle.C");
  gROOT->ProcessLine(".L ${B2HH_SRC}/TimeModels/RooKeysPdfSpecial_cxx.so");
  
  TString mode    = argv[1];
  TString bdt     = argv[2];
  TString bdtType = ((TObjString *)bdt.Tokenize('_')->At(0))->String();
  TString bdtCut  = ((TObjString *)bdt.Tokenize('_')->At(1))->String();
  TString magnet  = argv[3];
  TString tag     = argv[4];
  TString prefix  = "bkg";
  Bool_t  is3body = false;
  if (tag == "T" || tag == "U"){ 
    is3body = true;
    prefix = "phys";
  }
  map< TString, vector<int> > year_color;
  //  year_color["20151618"]={kBlack,   kSolid, 2};
  year_color["201516"] = {kGreen+2, kSolid, 2};
  year_color["2017s29r2p2"]   = {kRed, kDashed, 2};
  year_color["2018"]   = {kBlue, 8, 2};
  
  TString config =  Form("template%s_%s_%s_%s_%s_%s", 
			 prefix.Data(), mode.Data(), 
			 bdtType.Data(), bdtCut.Data(), 
			 magnet.Data(), tag.Data());
  
  TCanvas c("c_"+config, "c_"+config);

  TLegend * leg = new TLegend(0.55,0.35,0.85,0.55,"");
  RooPlot *plot = nullptr;
  int cont=0;
  for (auto it : year_color){
    cont += 1;
    TString tmp_year = it.first;
    int tmp_lineColor = it.second[0];
    int tmp_lineStyle = it.second[1];
    int tmp_lineWidth = it.second[2];
    TString tmp_nfin = Form("${B2HH_OUT}/TimeModels/templateFiles/templates%s_%s_%s_%s_%s_%s.root", 
			    (is3body)?"Phys": "", mode.Data(),
			    bdtType.Data(), bdtCut.Data(), 
			    tmp_year.Data(), magnet.Data());
    TString tmp_nfunc= Form("%s_%s_pdftime%s_%s", 
			    prefix.Data(), mode.Data(),
			    tag.Data(), tmp_year.Data());
    printf("File: %s, template: %s\n", tmp_nfin.Data(), tmp_nfunc.Data());

    TFile* tmp_fin = new TFile(tmp_nfin, "READ");
    RooWorkspace* tmp_ws = (RooWorkspace*)tmp_fin->Get("templates");
    RooAbsPdf* tmp_func = (RooAbsPdf*)tmp_ws->obj(tmp_nfunc);
    if (cont ==1){
      RooRealVar* time = (RooRealVar*)tmp_ws->obj("time");
      plot = time->frame();
      plot->GetXaxis()->SetRangeUser(0.2,5);
    }
    tmp_func->plotOn(plot, LineColor(tmp_lineColor), LineStyle(tmp_lineStyle), LineWidth(tmp_lineWidth));
    plot->Draw(cont==1?"":"same");
    c.Update();
    RooCurve* tmp_curve = (RooCurve*)c.FindObject(Form("%s_Norm[time]",tmp_func->GetName()));
    leg->AddEntry(tmp_curve,tmp_year,"l");
  }
  

  plot->SetTitle("");
  plot->GetXaxis()->SetTitle("Decay time [ps]");
  plot->GetYaxis()->SetTitle("");
  plot->Draw("same");
  
  TPaveText * lhcb = new TPaveText(0.55,0.55,0.85,0.85,"NDC");
  lhcb->SetTextAlign(12);
  lhcb->AddText("LHCb");
  lhcb->AddText(Form("Spectrum: %s",  mode.Data()));
  lhcb->AddText(Form("bdt%s>%s, Tagging: %s", bdtType.Data(), bdtCut.Data(), tag.Data()));
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
  c.SaveAs(Form("${B2HH_OUT}/TimeModels/plots/%s.root", config.Data()));
  //c.SaveAs(Form(""${B2HH_OUT}/TimeModels/plots/%s.png" , config.Data()));
  c.SaveAs(Form("${B2HH_OUT}/TimeModels/plots/%s.pdf" , config.Data()));
  //  c.SaveAs(Form(""${B2HH_OUT}/TimeModels/plots/%s.eps" , config.Data()));
  return 1;
}
