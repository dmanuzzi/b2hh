#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TApplication.h>
#include <RooFit.h>
#include <TChain.h>
#include <RooFitResult.h>
#include <RooRealVar.h>
#include <RooExponential.h>
#include <optionParser.h>
#include <TString.h>
#include <TROOT.h>
#include <RooTimeAccPdf.h>
#include <RooEffProd.h>
#include <RooExponential.h>
#include <RooDataSet.h>
#include <RooPlot.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TAxis.h>
#include <RooHist.h>
#include <RooCategory.h>
#include <RooAddPdf.h>
#include <TF1.h>
#include <TFile.h>
#include <TGraphErrors.h>

#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>

using namespace std;
using namespace RooFit;

Int_t main(Int_t argc, Char_t * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./makeRatio [options]\n");
    printf("Options:\n");
    printf("  -C <name>       : decay used for BDT train ([PIPI, KK], default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = 0.04)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2011,2012,Tot], default = 2016)\n");
    printf("  -n <decay>      : decay under study (default = bdkpi)\n");
    printf("  -f <finalState> : considered final state hypothesis (default = kpi)\n");
    printf("  -T              : flag for tagged acceptance\n");
    printf("  -D              : flag for data acceptance\n");
    return 0;
  }

  TString configuration = getOption(argc,argv,"-C","PIPI");
  Double_t bdtCut = atof(getOption(argc,argv,"-b","0.1"));
  TString name = getOption(argc,argv,"-n","bdkpi");
  TString finalState = getOption(argc,argv,"-f","kpi");
  TString magnet = getOption(argc,argv,"-m","Tot");
  TString year = getOption(argc,argv,"-y","Tot");
  Bool_t tagFlag = getBoolOption(argc,argv,"-T");
  TString suffix;
  if(tagFlag) suffix = "NewT";
  else        suffix = "NewU";
  Bool_t dataFlag = getBoolOption(argc,argv,"-D");

  TFile * fileNorm; TFile * file; TFile * fileData;
  if(tagFlag) {
    fileNorm = TFile::Open(Form("${B2HH_OUT}/AccSignal/plots/plotT_bdkpi_kpi_%s_%g_%s_%s_Kine.root",
				configuration.Data(),bdtCut,
				year.Data(),magnet.Data()),"READ");
    file     = TFile::Open(Form("${B2HH_OUT}/AccSignal/plots/plotT_%s_%s_%s_%g_%s_%s_Kine.root",
				name.Data(),finalState.Data(),
				configuration.Data(),bdtCut,
				year.Data(),magnet.Data()),"UPDATE");
    fileData = TFile::Open(Form("${B2HH_OUT}/AccSignal/plots/plotT_data_%s_%g_%s_%s_Sub.root",
				configuration.Data(),bdtCut,
				year.Data(),magnet.Data()),"READ");
  }
  else {
    fileNorm = TFile::Open(Form("${B2HH_OUT}/AccSignal/plots/plot_bdkpi_kpi_%s_%g_%s_%s_Kine.root",
				configuration.Data(),bdtCut,
				year.Data(),magnet.Data()),"READ");
    file     = TFile::Open(Form("${B2HH_OUT}/AccSignal/plots/plot_%s_%s_%s_%g_%s_%s_Kine.root",
				name.Data(),finalState.Data(),
				configuration.Data(),bdtCut,
				year.Data(),magnet.Data()),"UPDATE");
    fileData = TFile::Open(Form("${B2HH_OUT}/AccSignal/plots/plot_data_%s_%g_%s_%s_Sub.root",
				configuration.Data(),bdtCut,
				year.Data(),magnet.Data()),"READ");
  }

  TF1 * fNorm = (TF1 *) fileNorm->Get("f_bdkpi_kpi_accU");
  TF1 * f     = (TF1 *) file->Get(Form("f_%s_%s_accU",name.Data(),finalState.Data()));
  TF1 * fData = (TF1 *) fileData->Get("f_data_accU");

  TF1 * fRatio = new TF1(Form("fRatio_%s_%s",name.Data(),finalState.Data()),
                         "(TMath::Max(0.,[0]*(1 + [1]*tanh([2]*(x-[3])) + [4]*tanh([5]*(x-[6]) + [7]*(x-[6])**2 + [8]*(x-[6])**3 ) ) )*(1+(x>[10])*[9]*(x-[10])*(x-[10])))/(TMath::Max(0.001,[11]*(1 + [12]*tanh([13]*(x-[14])) + [15]*tanh([16]*(x-[17]) + [18]*(x-[17])**2 + [19]*(x-[17])**3 ) ) )*(1+(x>[21])*[20]*(x-[21])*(x-[21])))",accSignal_cuts::minTimeFit, accSignal_cuts::maxTimeFit);
  for(Int_t i = 0; i < 11; ++i)
    fRatio->SetParameter(i,f->GetParameter(i));
  for(Int_t i = 0; i < 11; ++i)
    fRatio->SetParameter(i+11,fNorm->GetParameter(i));
  fRatio->SetNpx(10000);
  fRatio->Draw();

  TF1 * fAcc = new TF1(Form("fAcc_%s_%s",name.Data(),finalState.Data()),
                       "(TMath::Max(0.,[0]*(1 + [1]*tanh([2]*(x-[3])) + [4]*tanh([5]*(x-[6]) + [7]*(x-[6])**2 + [8]*(x-[6])**3 ) ) )*(1+(x>[10])*[9]*(x-[10])*(x-[10])))/(TMath::Max(0.,[11]*(1 + [12]*tanh([13]*(x-[14])) + [15]*tanh([16]*(x-[17]) + [18]*(x-[17])**2 + [19]*(x-[17])**3 ) ) )*(1+(x>[21])*[20]*(x-[21])*(x-[21])))*(TMath::Max(0.,[22]*(1 + [23]*tanh([24]*(x-[25])) + [26]*tanh([27]*(x-[28]) + [29]*(x-[28])**2 + [30]*(x-[28])**3 ) ) )*(1+(x>[32])*[31]*(x-[32])*(x-[32])))",accSignal_cuts::minTimeFit, accSignal_cuts::maxTimeFit);
  for(Int_t i = 0; i < 11; ++i)
    fAcc->SetParameter(i,f->GetParameter(i));
  for(Int_t i = 0; i < 11; ++i)
    fAcc->SetParameter(i+11,fNorm->GetParameter(i));
  for(Int_t i = 0; i < 11; ++i)
    fAcc->SetParameter(i+22,fData->GetParameter(i));

  fAcc->SetNpx(10000);
  fAcc->Draw();

  TFile * outFile = new TFile(Form("${B2HH_OUT}/AccSignal/acceptances/acceptancesNew_%s_%g_%s_%s.root",configuration.Data(),bdtCut,year.Data(),magnet.Data()),"UPDATE");
  Double_t y = 0;
  TGraphErrors * gr;
  auto knots = accSignal_cuts::knots;
  
  Int_t nKnots = (Int_t) knots.size();
  if(dataFlag) {
    gr = new TGraphErrors(nKnots);
    Int_t count = 0;
    for(auto x: knots) {
      y = fData->Eval(x);
      gr->SetPoint(count,x,y);
      gr->SetPointError(count,0,0);
      ++count;
    }
    gr->SetNameTitle(Form("acc_bdkpi_%s",suffix.Data()),Form("acc_bdkpi_%s",suffix.Data()));
    outFile->WriteTObject(gr,"","Overwrite");
  }
  else {
    gr = new TGraphErrors(nKnots);
    Int_t count = 0;
    for(auto x: knots) {
      if(fNorm->Eval(x) < 0.001) y = 0;
      else                    y = fAcc->Eval(x);
      printf("%g %g\n",x,y);
      
      gr->SetPoint(count,x,y);
      gr->SetPointError(count,0,0);
      ++count;
    }
    if(name.EndsWith(finalState))
      gr->SetNameTitle(Form("acc_%s_%s",name.Data(),suffix.Data()),
                       Form("acc_%s_%s",name.Data(),suffix.Data()));
    else
      gr->SetNameTitle(Form("acc_%s_%s_%s",name.Data(),finalState.Data(),suffix.Data()),
                       Form("acc_%s_%s_%s",name.Data(),finalState.Data(),suffix.Data()));

    outFile->WriteTObject(gr,"","Overwrite");
    //file->WriteTObject(fAcc,"","Overwrite");
    //file->WriteTObject(fRatio,"","Overwrite");
  }

  file->Close();
  fileNorm->Close();
  fileData->Close();
  outFile->Close();

  return 0;

}
    

