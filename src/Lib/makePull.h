#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TGraphErrors.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TString.h>
#include <TLegend.h>
#include <TChain.h>

using namespace std;

TH1D * makePull(TH1D &h1, TH1D &h2, TString name) {

  Int_t nbins = h1.GetNbinsX();
  TH1D * tmpGraph = new TH1D(name,"",nbins,h1.GetXaxis()->GetXmin(),h1.GetXaxis()->GetXmax());
  Double_t tmp1 = 0, tmpErr1 = 0, tmp2 = 0, tmpErr2 = 0;
  Double_t pull = 0, pullErr = 0;
  for(Int_t ibin = 0; ibin < nbins; ibin++) {

    tmp1 = h1.GetBinContent(ibin+1);
    tmpErr1 = h1.GetBinError(ibin+1);
    tmp2 = h2.GetBinContent(ibin+1);
    tmpErr2 = h2.GetBinError(ibin+1);

    if(tmpErr1!=0&&tmpErr2!=0)
      pull = (tmp1-tmp2)/sqrt(tmpErr1*tmpErr1+tmpErr2*tmpErr2);
    else
      pull = 0;
    pullErr = 0;
    tmpGraph->SetBinContent(ibin+1,pull);
    tmpGraph->SetBinError(ibin+1,pullErr);

  }

  tmpGraph->SetStats(kFALSE);
  Double_t max = TMath::Max(tmpGraph->GetMaximum(),fabs(tmpGraph->GetMinimum()));
  tmpGraph->GetYaxis()->SetRangeUser((Int_t) (-1.1*max - 1) ,(Int_t) (1.1*max + 1));
  tmpGraph->SetFillColor(kBlack);
  tmpGraph->GetYaxis()->SetNdivisions(502,kTRUE);
  tmpGraph->GetXaxis()->SetTitleSize(0);     tmpGraph->GetXaxis()->SetLabelSize(0);
  tmpGraph->GetXaxis()->SetTickLength(0.15); tmpGraph->GetXaxis()->SetNdivisions(404,kFALSE);
  tmpGraph->GetYaxis()->SetTitleSize(0.15);  tmpGraph->GetYaxis()->SetLabelSize(0.15);
  tmpGraph->GetYaxis()->SetTitleOffset(0.2); tmpGraph->GetYaxis()->SetTitle("pull");
  tmpGraph->GetYaxis()->SetTickLength(0.05); tmpGraph->GetYaxis()->SetNdivisions(502,kFALSE);

  return tmpGraph;

}

void setStyle(TH1D * h, Color_t color, Width_t width, Size_t size, Style_t fstyle, const Char_t * xaxis, const Char_t * yaxis) {

  h->Sumw2();
  h->SetStats(kFALSE);
  h->SetTitle("");
  h->SetLineColor(color); h->SetLineWidth(width);
  h->SetMarkerColor(color); 
  h->SetMarkerStyle(20); h->SetMarkerSize(size);
  h->SetFillColor(color); h->SetFillStyle(fstyle);
  h->Scale(1./h->Integral("width"));
  h->GetXaxis()->SetTitleSize(0.05);  h->GetXaxis()->SetLabelSize(0.05);
  h->GetXaxis()->SetTitleOffset(1.1); h->GetXaxis()->SetTitle(xaxis);
  h->GetXaxis()->SetTickLength(0.05); h->GetXaxis()->SetNdivisions(406,kTRUE);
  h->GetXaxis()->SetTickLength(0.05); h->GetXaxis()->SetNdivisions(406,kTRUE);
  h->GetYaxis()->SetTitleSize(0.05);  h->GetYaxis()->SetLabelSize(0.05);
  h->GetYaxis()->SetTitleOffset(1.5); h->GetYaxis()->SetTitle(yaxis);
  h->GetYaxis()->SetTickLength(0.05); h->GetYaxis()->SetNdivisions(406,kTRUE);

}

void setStyle(TGraphErrors * h, Color_t color, Width_t width, Size_t size, Style_t fstyle, const Char_t * xaxis, const Char_t * yaxis) {

  h->SetTitle("");
  h->SetLineColor(color); h->SetLineWidth(width);
  h->SetMarkerColor(color);
  h->SetMarkerStyle(22); h->SetMarkerSize(size);
  h->SetFillColor(color); h->SetFillStyle(fstyle);
  h->GetXaxis()->SetTitleSize(0.05);  h->GetXaxis()->SetLabelSize(0.05);
  h->GetXaxis()->SetTitleOffset(1.1); h->GetXaxis()->SetTitle(xaxis);
  h->GetXaxis()->SetTickLength(0.05); h->GetXaxis()->SetNdivisions(406,kTRUE);
  h->GetYaxis()->SetTitleSize(0.05);  h->GetYaxis()->SetLabelSize(0.05);
  h->GetYaxis()->SetTitleOffset(1.5); h->GetYaxis()->SetTitle(yaxis);
  h->GetYaxis()->SetTickLength(0.05); h->GetYaxis()->SetNdivisions(406,kTRUE);

}

void setStyle(TCanvas * h) {

  TPad * myPad = (TPad *) h->GetPad(0);
  myPad->SetBottomMargin(0.15);
  myPad->SetLeftMargin(0.15);

}

void setToZero(TH1D * h) {

  Int_t nBins = h->GetNbinsX();
  for(Int_t iBin = 0; iBin < nBins; iBin++) {
    if(h->GetBinContent(iBin+1) < 0) h->SetBinContent(iBin+1,0);
  }

}

void subtractHistos(TH1D * h, TH1D * hRef, Double_t scale) {

  h->Sumw2(); hRef->Sumw2();

  //TH1D * hSub = (TH1D *) h->Clone(name);
  h->Add(hRef,-scale);
  //return hSub;

}

void adjustCanvas(TCanvas * c) {

  TPad * myPad = (TPad *) c->GetPad(0);
  myPad->SetLeftMargin(0.15); myPad->SetBottomMargin(0.15); myPad->SetBorderSize(0);

}

void adjustHistogram(TH1D * h, const Char_t * xname, const Char_t * yname, EColor color, Int_t style) {

  h->Scale(1./h->Integral("width"));
  h->GetXaxis()->SetTitleSize(0.05); h->GetXaxis()->SetLabelSize(0.05);
  h->GetXaxis()->SetTitleOffset(1.2); h->GetXaxis()->SetTitle(Form("%s",xname));
  h->GetXaxis()->SetTickLength(0.05);

  h->GetYaxis()->SetTitleSize(0.05); h->GetYaxis()->SetLabelSize(0.05);
  TString nameHist; nameHist.Form(Form("Entries/(%g %s)",
                                        (h->GetXaxis()->GetXmax()-h->GetXaxis()->GetXmin())/
                                         h->GetNbinsX(),yname));
  h->GetYaxis()->SetTitleOffset(1.3); h->GetYaxis()->SetTitle(nameHist);
  h->GetYaxis()->SetTickLength(0.05);

  h->SetFillColor(color);
  h->SetFillStyle(style);

}

void fillLegend(TLegend * leg, const Char_t * name, TH1D * h1, TH1D * h2) {

  leg->SetName(name);
  leg->SetTextSize(0.04);
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->AddEntry(h1,"Signal","f");
  leg->AddEntry(h2,"Background","f");

}

void shiftToZero(TH1D * h) {

  for(Int_t i = 0, n = h->GetNbinsX(); i < n; ++i) {

    if(h->GetBinContent(i+1) < 0)
      h->SetBinContent(i+1,0);

  }

}

void activateBranches(TChain * chain, std::vector<TString> &names) {

  chain->SetBranchStatus("*",0);
  for(auto name: names) 
    chain->SetBranchStatus(name,1);

}
