#include "TChain.h"
#include <TFileCollection.h>
#include <TCollection.h>
#include "TH2D.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TPaletteAxis.h"
#include <cmath>
#include <map>
using namespace std;

int main(int argc, char * argv[]){
  TString mode = argv[1]; 
  TString particle = argv[2];
  TString charge = argv[3];
  TString year = argv[4];
  TString magnet = argv[5];

  TCanvas *c = nullptr;
  TFile *outFile = nullptr;
  TH2D *hKin = nullptr;
  TString tag="";
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);

  if (mode == "CAL"){
    tag = Form("%s%s_%s_%s", particle.Data(), charge.Data(),  magnet.Data(), year.Data());;
    outFile = new TFile("plots/particleKinematic_CAL_"+tag+".root","RECREATE");
    TFileCollection * calList = new TFileCollection("list_"+tag,"list"+tag,"../PIDcalibLists/list_"+tag+".txt");
    TChain * calChain = new TChain(particle+charge+"_tot",particle+charge+"_tot");
    calChain->AddFileInfoList((TCollection *) calList->GetList());
    hKin = new TH2D("hKin_"+tag,"",250,0,500,20,1.,6.);
    calChain->Draw("ETA:P>>hKin_"+tag, "weight", "goff");
    c = new TCanvas("canv_"+tag, "canv_"+tag);
    
  } else if (mode == "SIG"){
    map<TString, TString> MCsamples;
    MCsamples["PIplus"]  = "bdpik";
    MCsamples["Kplus"]   = "bdkpi";
    MCsamples["Pplus"]   = "lbppi";
    MCsamples["PIminus"] = "bdkpi";
    MCsamples["Kminus"]  = "bdpik";
    MCsamples["Pminus"]  = "lbpip";
    TString BDTnameCut = argv[6];
    TString BDTname = ((TObjString *)BDTnameCut.Tokenize('_')->At(0))->String();
    TString BDTcut  = ((TObjString *)BDTnameCut.Tokenize('_')->At(1))->String();
    tag = Form("%s_%s%s_%s_%s", BDTnameCut.Data(), particle.Data(), charge.Data(),  magnet.Data(), year.Data());;
    outFile = new TFile("plots/particleKinematic_SIG_"+tag+".root","RECREATE");
    TFileCollection * sigList = new TFileCollection("list_"+tag,"list"+tag,
						    Form("../../Data/selectedLists/list_%s_%s_%s.txt",
							 MCsamples[particle+charge].Data(), magnet.Data(), year.Data()));
    TChain * sigChain = new TChain("b2hh","b2hh");
    sigChain->AddFileInfoList((TCollection *) sigList->GetList());
    hKin = new TH2D("hKin_"+tag,"",250,0,500,20,1.,6.);
    sigChain->Draw(Form("pi%sETA:pi%sP>>hKin_%s", charge.Data(), charge.Data(), tag.Data()), 
		   Form("BDT1_%s>%s",BDTname.Data(), BDTcut.Data()), "goff");
    c = new TCanvas("canv_"+tag, "canv_"+tag);
  } else return 0;

  c->SetLogz();
  hKin->SetStats(kFALSE);
  hKin->Draw("colz");
   
  hKin->GetXaxis()->SetTitleSize(0.06);        hKin->GetXaxis()->SetLabelSize(0.06);
  hKin->GetXaxis()->SetTitle("p (GeV/c)");     hKin->GetXaxis()->SetTitleOffset(1.1);
  hKin->GetXaxis()->SetTickLength(0.05);       hKin->GetXaxis()->SetNdivisions(505,kTRUE);

  hKin->GetYaxis()->SetTitleSize(0.08);  hKin->GetYaxis()->SetLabelSize(0.06);
  hKin->GetYaxis()->SetTitle("#eta");    hKin->GetYaxis()->SetTitleOffset(0.5);
  hKin->GetYaxis()->SetTickLength(0.05); hKin->GetYaxis()->SetNdivisions(505,kTRUE);

  hKin->GetZaxis()->SetRangeUser(0,hKin->GetMaximum());
  hKin->GetZaxis()->SetNdivisions(505,kTRUE); hKin->SetContour(99);
  hKin->GetZaxis()->SetTitle("Events");
   
  TPad * myPad = (TPad *) c->GetPad(0);
  myPad->SetLeftMargin(0.15); myPad->SetBottomMargin(0.15); myPad->SetRightMargin(0.15);
  myPad->SetBorderSize(0);
  c->Draw();
  TPaletteAxis * palette = (TPaletteAxis *) hKin->GetListOfFunctions()->FindObject("palette");
  palette->GetAxis()->SetTitle("Events");
  palette->GetAxis()->SetTitleSize(0.1); palette->GetAxis()->SetTitleOffset(0.3);
  palette->GetAxis()->SetLabelSize(0.05);
  palette->Draw();
  c->Draw();

  c->SaveAs("plots/particleKinematic_"+mode+"_"+tag+".pdf");
  outFile->WriteTObject(hKin);
  outFile->Close();


  return 1;
}
