#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <RooFit.h>
#include <RooRealVar.h>
#include <RooCategory.h>
#include <RooDataSet.h>
#include <RooFormulaVar.h>
#include <TChain.h>
#include <RooExponential.h>
#include <RooFormulaVar.h>
#include <RooUniform.h>
#include <RooProdPdf.h>
#include <optionParser.h>
#include <RooArgSet.h>
#include <RooFitResult.h>
#include <RooPlot.h>
#include <TString.h>
#include <TChain.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TPaveText.h>

#include <algorithm>
#include <functional>
#include <array>

#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>

using namespace std;
using namespace RooFit;

Int_t main(Int_t argc, Char_t * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./test [options]\n");
    printf("Options:\n");
    printf("  -n <name>       : decay used for BDT train ([PIPI, KK], default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = 0.04)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2015,2016,2017,2018, 201516,20151618,Tot], default = 2016)\n");
    printf("  -f <finalState> : ID of final state ([PIPI,KPI,KK], default = PIPI)\n");
    printf("  -F              : if present will perform the fit\n");
    return 0;
  }

  TString name          = getOption(argc,argv,"-n","PIPI");
  Double_t bdtCut       = atof(getOption(argc,argv,"-b","0.12"));
  TString magnet        = getOption(argc,argv,"-m","Tot");
  TString year          = getOption(argc,argv,"-y","2016");
  TString finalState    = getOption(argc,argv,"-f","PIPI");
  Bool_t fitFlag        = getBoolOption(argc,argv,"-F");
  if(!fitFlag)
    printf("EXECUTING ./provaVin -n %s -b %g -y %s -m %s -f %s\n",
	   name.Data(),bdtCut,year.Data(),magnet.Data(),finalState.Data());
  else
    printf("EXECUTING ./provaVin -n %s -b %g -y %s -m %s -f %s -F\n",
	   name.Data(),bdtCut,year.Data(),magnet.Data(),finalState.Data());

  TString tagName = (name=="PIPI" ? "SS" : "SSk");
  Int_t finalStateIdx = datasetFlags::yearFlags[year] + 
                        datasetFlags::spectrumFlags[finalState];
  
  Double_t massCut = ((finalState == "KK")? timeModels_cuts::massCutKK : timeModels_cuts::massCutPIPI);
  
  // Double_t minWinTot  = 5.0,    maxWinTot  = 6.2,
  //          minWinLow  = 5.0,    maxWinLow  = 5.366,
  //          minWinHigh = 5.366,  maxWinFit  = 6.2,
  //          minWinFit  = 5.5,    maxWinHigh = 6.2,
  //          minWinSig  = 5.23,   maxWinSig  = 5.32;

  RooRealVar *mass  = new RooRealVar("mass", "mass", timeModels_cuts::minWinFit,  timeModels_cuts::maxWinFit);
  RooRealVar * time = new RooRealVar("time", "time", timeModels_cuts::minTimeFit, timeModels_cuts::maxTimeFit);
  RooCategory * fState = new RooCategory("fState","fState");
  fState->defineType(finalState.Data(),finalStateIdx);
  RooCategory * qOS = new RooCategory("qOS","qOS");
  qOS->defineType("B",1); qOS->defineType("Bbar",-1); qOS->defineType("Untag",0);
  RooCategory * qSS = new RooCategory(Form("q%s",tagName.Data()),Form("q%s",tagName.Data()));
  qSS->defineType("B",1); qSS->defineType("Bbar",-1); qSS->defineType("Untag",0);

  RooArgSet * obs = new RooArgSet();
  obs->add(*mass); obs->add(*time);
  obs->add(*fState);
  obs->add(*qOS); obs->add(*qSS);

  Double_t Mass = 0, Time = 0;
  Int_t FState = 0, QOS = 0, QSS = 0;
  TChain * chain = new TChain("b2hh","b2hh");
  chain->Add(Form("${B2HH_OUT}/Reduce/b2hh_%s_%g_%s_%s.root",name.Data(),bdtCut,year.Data(),magnet.Data()));
  printf("${B2HH_OUT}/Reduce/b2hh_%s_%g_%s_%s.root", name.Data(), bdtCut, year.Data(), magnet.Data());

  chain->SetBranchStatus("*",0);
  chain->SetBranchStatus("mass",1);   chain->SetBranchAddress("mass",&Mass);
  chain->SetBranchStatus("time",1);   chain->SetBranchAddress("time",&Time);
  chain->SetBranchStatus("fState",1); chain->SetBranchAddress("fState",&FState);
  chain->SetBranchStatus("qOS",1);    chain->SetBranchAddress("qOS",&QOS);
  chain->SetBranchStatus(Form("q%s",tagName.Data()),1);    
  chain->SetBranchAddress(Form("q%s",tagName.Data()),&QSS);

  RooDataSet * data   = new RooDataSet("data",  "data",  *obs,Import(*chain));
  RooDataSet * data11 = new RooDataSet("data11","data11",*obs,Import(*chain),Cut(Form("qOS!=0&&q%s!=0",tagName.Data())));
  RooDataSet * data10 = new RooDataSet("data10","data10",*obs,Import(*chain),Cut(Form("qOS!=0&&q%s==0",tagName.Data())));
  RooDataSet * data01 = new RooDataSet("data01","data01",*obs,Import(*chain),Cut(Form("qOS==0&&q%s!=0",tagName.Data())));
  RooDataSet * data00 = new RooDataSet("data00","data00",*obs,Import(*chain),Cut(Form("qOS==0&&q%s==0",tagName.Data())));

  finalState.ToLower();
  RooRealVar * p0    = new RooRealVar(Form("bkg_%s_mass_p0_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p0_%s",finalState.Data(),year.Data()),-0.5,-100,100);
  RooRealVar * p1    = new RooRealVar(Form("bkg_%s_mass_p1_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p1_%s",finalState.Data(),year.Data()),2,-100,100);
  RooRealVar * p2    = new RooRealVar(Form("bkg_%s_mass_p2_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p2_%s",finalState.Data(),year.Data()),0.5,-100,100);
  RooRealVar * p0_11 = new RooRealVar(Form("bkg_%s_mass_p0_11_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p0_11_%s",finalState.Data(),year.Data()),-0.5,-100,100);
  RooRealVar * p1_11 = new RooRealVar(Form("bkg_%s_mass_p1_11_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p1_11_%s",finalState.Data(),year.Data()),2,-100,100);
  RooRealVar * p2_11 = new RooRealVar(Form("bkg_%s_mass_p2_11_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p2_11_%s",finalState.Data(),year.Data()),0.5,-100,100);
  RooRealVar * p0_10 = new RooRealVar(Form("bkg_%s_mass_p0_10_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p0_10_%s",finalState.Data(),year.Data()),-0.5,-100,100);
  RooRealVar * p1_10 = new RooRealVar(Form("bkg_%s_mass_p1_10_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p1_10_%s",finalState.Data(),year.Data()),2,-100,100);
  RooRealVar * p2_10 = new RooRealVar(Form("bkg_%s_mass_p2_10_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p2_10_%s",finalState.Data(),year.Data()),0.5,-100,100);
  RooRealVar * p0_01 = new RooRealVar(Form("bkg_%s_mass_p0_01_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p0_01_%s",finalState.Data(),year.Data()),-0.5,-100,100);
  RooRealVar * p1_01 = new RooRealVar(Form("bkg_%s_mass_p1_01_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p1_01_%s",finalState.Data(),year.Data()),2,-100,100);
  RooRealVar * p2_01 = new RooRealVar(Form("bkg_%s_mass_p2_01_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p2_01_%s",finalState.Data(),year.Data()),0.5,-100,100);
  RooRealVar * p0_00 = new RooRealVar(Form("bkg_%s_mass_p0_00_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p0_00_%s",finalState.Data(),year.Data()),-0.5,-100,100);
  RooRealVar * p1_00 = new RooRealVar(Form("bkg_%s_mass_p1_00_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p1_00_%s",finalState.Data(),year.Data()),2,-100,100);
  RooRealVar * p2_00 = new RooRealVar(Form("bkg_%s_mass_p2_00_%s",finalState.Data(),year.Data()),
				      Form("bkg_%s_mass_p2_00_%s",finalState.Data(),year.Data()),0.5,-100,100);
  RooArgSet * params = new RooArgSet();
  params->add(*p0);    params->add(*p1);    params->add(*p2);
  params->add(*p0_11); params->add(*p1_11); params->add(*p2_11);
  params->add(*p0_10); params->add(*p1_10); params->add(*p2_10);
  params->add(*p0_01); params->add(*p1_01); params->add(*p2_01);
  params->add(*p0_00); params->add(*p1_00); params->add(*p2_00);

  RooFormulaVar * slope   = new RooFormulaVar("slope",  "slope",  "@0*(1+tanh(@1*(@3-@2)))",RooArgList(*p0,*p1,*p2,*time));
  RooFormulaVar * slope11 = new RooFormulaVar("slope11","slope11","@0*(1+tanh(@1*(@3-@2)))",RooArgList(*p0_11,*p1_11,*p2_11,*time));
  RooFormulaVar * slope10 = new RooFormulaVar("slope10","slope10","@0*(1+tanh(@1*(@3-@2)))",RooArgList(*p0_10,*p1_10,*p2_10,*time));
  RooFormulaVar * slope01 = new RooFormulaVar("slope01","slope01","@0*(1+tanh(@1*(@3-@2)))",RooArgList(*p0_01,*p1_01,*p2_01,*time));
  RooFormulaVar * slope00 = new RooFormulaVar("slope00","slope00","@0*(1+tanh(@1*(@3-@2)))",RooArgList(*p0_00,*p1_00,*p2_00,*time));

  RooExponential * expT  = new RooExponential("expT", "expT", *mass,*slope);
  RooExponential * exp11 = new RooExponential("exp11","exp11",*mass,*slope11);
  RooExponential * exp10 = new RooExponential("exp10","exp10",*mass,*slope10);
  RooExponential * exp01 = new RooExponential("exp01","exp01",*mass,*slope01);
  RooExponential * exp00 = new RooExponential("exp00","exp00",*mass,*slope00);

  RooUniform * pdfT = new RooUniform("pdfT","pdfT",*time);

  RooProdPdf * pdf   = new RooProdPdf("pdf",  "pdf",  RooArgSet(*pdfT),Conditional(RooArgSet(*expT), RooArgSet(*mass)));
  RooProdPdf * pdf11 = new RooProdPdf("pdf11","pdf11",RooArgSet(*pdfT),Conditional(RooArgSet(*exp11),RooArgSet(*mass)));
  RooProdPdf * pdf10 = new RooProdPdf("pdf10","pdf10",RooArgSet(*pdfT),Conditional(RooArgSet(*exp10),RooArgSet(*mass)));
  RooProdPdf * pdf01 = new RooProdPdf("pdf01","pdf01",RooArgSet(*pdfT),Conditional(RooArgSet(*exp01),RooArgSet(*mass)));
  RooProdPdf * pdf00 = new RooProdPdf("pdf00","pdf00",RooArgSet(*pdfT),Conditional(RooArgSet(*exp00),RooArgSet(*mass)));

  params->Print("v");
  printf("READING PARAMETERS #####################################################\n");
  params->readFromFile(Form("${B2HH_OUT}/TimeModels/params/params_bkg_%s_%s_%g_%s_%s.txt",
			    finalState.Data(),name.Data(),
			    bdtCut,year.Data(),magnet.Data()));
  params->setAttribAll("Constant",kFALSE);
  params->Print("v");

  if(fitFlag) {
    printf("&&&&&&&&&&&& Unbinned Fit\n");
    RooFitResult * r   = pdf->fitTo(*data,Verbose(kTRUE),PrintLevel(3),Save());
    printf("&&&&&&&&&&&& Unbinned Fit 11\n");
    RooFitResult * r11 = pdf11->fitTo(*data11,Verbose(kTRUE),PrintLevel(3),Save());
    printf("&&&&&&&&&&&& Unbinned Fit 10\n");
    RooFitResult * r10 = pdf10->fitTo(*data10,Verbose(kTRUE),PrintLevel(3),Save());
    printf("&&&&&&&&&&&& Unbinned Fit 01\n");
    RooFitResult * r01 = pdf01->fitTo(*data01,Verbose(kTRUE),PrintLevel(3),Save());
    printf("&&&&&&&&&&&& Unbinned Fit 00\n");
    RooFitResult * r00 = pdf00->fitTo(*data00,Verbose(kTRUE),PrintLevel(3),Save());
    
    r->Print("v");
    r11->Print("v");
    r10->Print("v");
    r01->Print("v");
    r00->Print("v");
	  
    params->setAttribAll("Constant",kTRUE);
    params->writeToFile(Form("${B2HH_OUT}/TimeModels/params/params_bkg_%s_%s_%g_%s_%s.txt",
                             finalState.Data(), name.Data(),
                             bdtCut, year.Data(), magnet.Data()));
  }

  TF1 * fslope   = new TF1("fslope"  ,"[0]*(1+tanh([1]*(x-[2])))", timeModels_cuts::minTimeFit, timeModels_cuts::maxTimeFit);
  fslope->SetParameter(0,p0->getVal());
  fslope->SetParameter(1,p1->getVal());
  fslope->SetParameter(2,p2->getVal());
	
  TF1 * fslope11 = new TF1("fslope11","[0]*(1+tanh([1]*(x-[2])))", timeModels_cuts::minTimeFit, timeModels_cuts::maxTimeFit);
  fslope11->SetParameter(0,p0_11->getVal());
  fslope11->SetParameter(1,p1_11->getVal());
  fslope11->SetParameter(2,p2_11->getVal());

  TF1 * fslope10 = new TF1("fslope10","[0]*(1+tanh([1]*(x-[2])))", timeModels_cuts::minTimeFit, timeModels_cuts::maxTimeFit);
  fslope10->SetParameter(0,p0_10->getVal());
  fslope10->SetParameter(1,p1_10->getVal());
  fslope10->SetParameter(2,p2_10->getVal());
	
  TF1 * fslope01 = new TF1("fslope01","[0]*(1+tanh([1]*(x-[2])))", timeModels_cuts::minTimeFit, timeModels_cuts::maxTimeFit);
  fslope01->SetParameter(0,p0_01->getVal());
  fslope01->SetParameter(1,p1_01->getVal());
  fslope01->SetParameter(2,p2_01->getVal());
	
  TF1 * fslope00 = new TF1("fslope00","[0]*(1+tanh([1]*(x-[2])))", timeModels_cuts::minTimeFit, timeModels_cuts::maxTimeFit);
  fslope00->SetParameter(0,p0_00->getVal());
  fslope00->SetParameter(1,p1_00->getVal());
  fslope00->SetParameter(2,p2_00->getVal());

  Double_t weight = 0, weightLow = 0, weightHigh = 0, weight3 = 0, weightS = 0, slopeTMP = 0;
  finalState.ToUpper();
  TFile * outFile = TFile::Open(Form("${B2HH_OUT}/TimeModels/weightedFiles/bkg_%s_%s_%g_%s_%s.root",
				     finalState.Data(),name.Data(),
				     bdtCut,year.Data(),magnet.Data()),"RECREATE");
  TTree * outTree = (TTree *) chain->CloneTree(0);
  outTree->Branch("weight",    &weight,    "weight/D");
  outTree->Branch("weightLow", &weightLow, "weightLow/D");
  outTree->Branch("weightHigh",&weightHigh,"weightHigh/D");
  outTree->Branch("weight3",   &weight3,   "weight3/D");
  outTree->Branch("weightS",   &weightS,   "weightS/D");

  std::vector<Double_t> dataV11, dataV10, dataV01, dataV00, dataV;
  auto calcWeight = [](Double_t tmpSlope, Double_t minWinNum, Double_t maxWinNum){
    Double_t a1 = exp(tmpSlope * minWinNum);
    Double_t a2 = exp(tmpSlope * maxWinNum);
    Double_t b1 = exp(tmpSlope * timeModels_cuts::minWinFit);
    Double_t b2 = exp(tmpSlope * timeModels_cuts::maxWinFit);
    return (a1-a2) / (b1-b2);
  };
  for(Int_t iEntry = 0, nEntries = chain->GetEntries(); iEntry < nEntries; ++iEntry) {
    chain->GetEntry(iEntry);
    if(FState!=finalStateIdx) continue;
    if(Mass<timeModels_cuts::minWinFit) continue;
    if(Mass>timeModels_cuts::maxWinFit) continue;
    if(Time<timeModels_cuts::minTimeFit) continue;
    if(Time>timeModels_cuts::maxTimeFit) continue;
    dataV.push_back(Time);
    if       (QOS!=0&&QSS!=0) {
      slopeTMP = fslope11->Eval(Time);
      dataV11.push_back(Time);
    } else if(QOS!=0&&QSS==0) {
      slopeTMP = fslope10->Eval(Time);
      dataV10.push_back(Time);
    } else if(QOS==0&&QSS!=0) {
      slopeTMP = fslope01->Eval(Time);
      dataV01.push_back(Time);
    } else if(QOS==0&&QSS==0) {
      slopeTMP = fslope00->Eval(Time);
      dataV00.push_back(Time);  
    } else { printf("COGLIONE\n"); continue; }
    weight     =  calcWeight(slopeTMP, timeModels_cuts::minWinTot, timeModels_cuts::maxWinTot);
    weightLow  =  calcWeight(slopeTMP, timeModels_cuts::minWinLow, timeModels_cuts::maxWinLow);
    weightHigh =  calcWeight(slopeTMP, timeModels_cuts::minWinHigh, timeModels_cuts::maxWinHigh);
    weight3    = -calcWeight(slopeTMP, timeModels_cuts::minWinTot, massCut);
    weightS    = -calcWeight(slopeTMP, timeModels_cuts::minWinSig, timeModels_cuts::maxWinSig);
    if(slopeTMP<-5){ weight = weightLow = weightHigh = weight3 = weightS = 1.; }
    if(std::isnan(weight))     { printf("W: %g %g %g %d %d\n",slopeTMP,Time,weight,QOS,QSS); continue; }
    if(std::isnan(weightLow))  { printf("WL: %g %g %g %d %d\n",slopeTMP,Time,weightLow,QOS,QSS); continue; }
    if(std::isnan(weightHigh)) { printf("WH: %g %g %g %d %d\n",slopeTMP,Time,weightHigh,QOS,QSS); continue; }
    if(std::isnan(weightS))    { printf("WS: %g %g %g %d %d\n",slopeTMP,Time,weightS,QOS,QSS); continue; }
    if(std::isnan(weight3))    { printf("W3: %g %g %g %d %d\n",slopeTMP,Time,weight3,QOS,QSS); continue; }
    outTree->Fill();
		    
  }

  sort(dataV.begin(),dataV.end());
  sort(dataV11.begin(),dataV11.end());
  sort(dataV10.begin(),dataV10.end());
  sort(dataV01.begin(),dataV01.end());
  sort(dataV00.begin(),dataV00.end());

  TF1 * fExp = new TF1("fExp",Form("[0]*[1]*exp(-[1]*x)/(exp(-[1]*%f)-exp(-[1]*%f))", 
                                   timeModels_cuts::minWinFit, timeModels_cuts::maxWinFit),
                        timeModels_cuts::minWinFit, timeModels_cuts::maxWinFit);
  fExp->SetParameter(0,1);
  fExp->SetParameter(1,1);
  fExp->SetParLimits(0,1,1);
  fExp->FixParameter(0,1);
  fExp->SetParLimits(1,-10,10);

  Int_t nEntries   = (Int_t) dataV.size();
  Int_t nEntries11 = (Int_t) dataV11.size();
  Int_t nEntries10 = (Int_t) dataV10.size();
  Int_t nEntries01 = (Int_t) dataV01.size();
  Int_t nEntries00 = (Int_t) dataV00.size();
  
  Int_t nEntriesPerBin   = year == "2015" ? 100 : 1000,
        nEntriesPerBin11 = year == "2015" ? 100 :  500,
        nEntriesPerBin10 = year == "2015" ? 100 :  500,
	nEntriesPerBin01 = year == "2015" ? 100 :  500,
	nEntriesPerBin00 = year == "2015" ? 100 :  500;

  Int_t nBins   = nEntries  /nEntriesPerBin;
  Int_t nBins11 = nEntries11/nEntriesPerBin11;
  Int_t nBins10 = nEntries10/nEntriesPerBin10;
  Int_t nBins01 = nEntries01/nEntriesPerBin01;
  Int_t nBins00 = nEntries00/nEntriesPerBin00;

  Double_t slopes[nBins+1], mean[nBins+1],
    slopesErr[nBins+1], meanErr[nBins+1],
    slopesErrLow[nBins+1], meanErrLow[nBins+1],
    slopesErrHigh[nBins+1], meanErrHigh[nBins+1], tot = 0;
  Double_t slopes11[nBins11+1], mean11[nBins11+1],
    slopesErr11[nBins11+1], meanErr11[nBins11+1];
  Double_t slopes10[nBins10+1], mean10[nBins10+1],
    slopesErr10[nBins10+1], meanErr10[nBins10+1];
  Double_t slopes01[nBins01+1], mean01[nBins01+1],
    slopesErr01[nBins01+1], meanErr01[nBins01+1];
  Double_t slopes00[nBins00+1], mean00[nBins00+1],
    slopesErr00[nBins00+1], meanErr00[nBins00+1];

  std::vector<Double_t> bins;
  std::vector<Double_t> bins11;
  std::vector<Double_t> bins10;
  std::vector<Double_t> bins01;
  std::vector<Double_t> bins00;
  bins.push_back(timeModels_cuts::minTimeFit);
  bins11.push_back(timeModels_cuts::minTimeFit);
  bins10.push_back(timeModels_cuts::minTimeFit);
  bins01.push_back(timeModels_cuts::minTimeFit);
  bins00.push_back(timeModels_cuts::minTimeFit);

  ////////////////////////////////////////////////////////////////////////////////

  for(Int_t i = 0; i < nBins-1; ++i) {
    slopes[i] = 0; mean[i] = 0;
    slopesErr[i] = 0; meanErr[i] = 0;
    slopesErrLow[i] = 0; meanErrLow[i] = 0;
    slopesErrHigh[i] = 0; meanErrHigh[i] = 0;
    bins.push_back(0.5*(dataV[nEntriesPerBin*(i+1)-1]+dataV[nEntriesPerBin*(i+1)]));
    for(Int_t j = nEntriesPerBin*i; j < nEntriesPerBin*(i+1) ; ++j) {
      mean[i] += dataV[j];
    }
    mean[i] /= nEntriesPerBin;
    meanErrLow[i] = mean[i]-bins[i];
    meanErrHigh[i] = bins[i+1]-mean[i];
  }
  bins.push_back(timeModels_cuts::maxTimeFit);
  mean[nBins-1] = 0;
  for(Int_t j = nEntriesPerBin*(nBins-1), n = (Int_t) dataV.size(); j < n ; ++j) {
    mean[nBins-1] += dataV[j];
    tot++;
  }
  mean[nBins-1] /= tot;
  meanErrLow[nBins-1] = mean[nBins-1]-bins[nBins-1];
  meanErrHigh[nBins-1] = bins[nBins]-mean[nBins-1];

  

  tot = 0;
  
  ////////////////////////////////////////////////////////////////////////////////

  for(Int_t i = 0; i < nBins11; ++i) {
    slopes11[i] = 0; mean11[i] = 0;
    slopesErr11[i] = 0; meanErr11[i] = 0;
    bins11.push_back(0.5*(dataV11[nEntriesPerBin11*(i+1)-1]+dataV11[nEntriesPerBin11*(i+1)]));
    for(Int_t j = nEntriesPerBin11*i; j < nEntriesPerBin11*(i+1) ; ++j) {
      mean11[i] += dataV11[j];
    }
    mean11[i] /= nEntriesPerBin11;
  }
  bins11.push_back(timeModels_cuts::maxTimeFit);
  mean11[nBins11] = 0;
  for(Int_t j = nEntriesPerBin11*nBins11, n = (Int_t) dataV11.size(); j < n ; ++j) {
    mean11[nBins11] += dataV11[j];
    tot++;
  }
  mean11[nBins11] /= tot;
  tot = 0;

  ////////////////////////////////////////////////////////////////////////////////

  for(Int_t i = 0; i < nBins10; ++i) {
    slopes10[i] = 0; mean10[i] = 0;
    slopesErr10[i] = 0; meanErr10[i] = 0;
    bins10.push_back(0.5*(dataV10[nEntriesPerBin10*(i+1)-1]+dataV10[nEntriesPerBin10*(i+1)]));
    for(Int_t j = nEntriesPerBin10*i; j < nEntriesPerBin10*(i+1) ; ++j) {
      mean10[i] += dataV10[j];
    }
    mean10[i] /= nEntriesPerBin10;
  }
  bins10.push_back(timeModels_cuts::maxTimeFit);
  mean10[nBins10] = 0;
  for(Int_t j = nEntriesPerBin10*nBins10, n = (Int_t) dataV10.size(); j < n ; ++j) {
    mean10[nBins10] += dataV10[j];
    tot++;
  }
  mean10[nBins10] /= tot;
  tot = 0;
  
  /////////////////////////////////////////////////////////////////////////////////

  for(Int_t i = 0; i < nBins01; ++i) {
    slopes01[i] = 0; mean01[i] = 0;
    slopesErr01[i] = 0; meanErr01[i] = 0;
    bins01.push_back(0.5*(dataV01[nEntriesPerBin01*(i+1)-1]+dataV01[nEntriesPerBin01*(i+1)]));
    for(Int_t j = nEntriesPerBin01*i; j < nEntriesPerBin01*(i+1) ; ++j) {
      mean01[i] += dataV01[j];
    }
    mean01[i] /= nEntriesPerBin01;
  }
  bins01.push_back(timeModels_cuts::maxTimeFit);
  mean01[nBins01] = 0;
  for(Int_t j = nEntriesPerBin01*nBins01, n = (Int_t) dataV01.size(); j < n ; ++j) {
    mean01[nBins01] += dataV01[j];
    tot++;
  }
  mean01[nBins01] /= tot;
  tot = 0;
	
  /////////////////////////////////////////////////////////////////////////////////

  for(Int_t i = 0; i < nBins00; ++i) {
    slopes00[i] = 0; mean00[i] = 0;
    slopesErr00[i] = 0; meanErr00[i] = 0;
    bins00.push_back(0.5*(dataV00[nEntriesPerBin00*(i+1)-1]+dataV00[nEntriesPerBin00*(i+1)]));
    for(Int_t j = nEntriesPerBin00*i; j < nEntriesPerBin00*(i+1) ; ++j) {
      mean00[i] += dataV00[j];
    }
    mean00[i] /= nEntriesPerBin00;
  }
  bins00.push_back(timeModels_cuts::maxTimeFit);
  mean00[nBins00] = 0;
  for(Int_t j = nEntriesPerBin00*nBins00, n = (Int_t) dataV00.size(); j < n ; ++j) {
    mean00[nBins00] += dataV00[j];
    tot++;
  }
  mean00[nBins00] /= tot;
  tot = 0;
  
  /////////////////////////////////////////////////////////////////////////////////

  for(Int_t i = 0, n = (Int_t) bins.size()-1; i < n; ++i) {
    chain->UnbinnedFit("fExp","mass",Form("fState==%d&&time>%g&&time<%g&&mass>%g&&mass<%g",
					                                finalStateIdx,bins[i],bins[i+1], timeModels_cuts::minWinFit, timeModels_cuts::maxWinFit),"Q");
    slopes[i] = fExp->GetParameter(1);
    slopesErr[i] = fExp->GetParError(1);
  }

  /////////////////////////////////////////////////////////////////////////////////

  for(Int_t i = 0, n = (Int_t) bins11.size()-1; i < n; ++i) {
    chain->UnbinnedFit("fExp", "mass", Form("fState==%d&&time>%g&&time<%g&&mass>%g&&mass<%g&&qOS!=0&&q%s!=0", 
                                            finalStateIdx, bins11[i], bins11[i + 1], timeModels_cuts::minWinFit, timeModels_cuts::maxWinFit, tagName.Data()), "Q");
    slopes11[i] = -fExp->GetParameter(1);
    slopesErr11[i] = fExp->GetParError(1);
  }

  ////////////////////////////////////////////////////////////////////////////////

  for(Int_t i = 0, n = (Int_t) bins10.size()-1; i < n; ++i) {
    chain->UnbinnedFit("fExp", "mass", Form("fState==%d&&time>%g&&time<%g&&mass>%g&&mass<%g&&qOS!=0&&q%s==0", 
                                            finalStateIdx, bins10[i], bins10[i + 1], timeModels_cuts::minWinFit, timeModels_cuts::maxWinFit, tagName.Data()), "Q");
    slopes10[i] = -fExp->GetParameter(1);
    slopesErr10[i] = fExp->GetParError(1);
  }

  ////////////////////////////////////////////////////////////////////////////////

  for(Int_t i = 0, n = (Int_t) bins01.size()-1; i < n; ++i) {
    chain->UnbinnedFit("fExp", "mass", Form("fState==%d&&time>%g&&time<%g&&mass>%g&&mass<%g&&qOS==0&&q%s!=0", 
                                            finalStateIdx, bins01[i], bins01[i + 1], timeModels_cuts::minWinFit, timeModels_cuts::maxWinFit, tagName.Data()), "Q");
    slopes01[i] = -fExp->GetParameter(1);
    slopesErr01[i] = fExp->GetParError(1);
  }

  ////////////////////////////////////////////////////////////////////////////////
  
  for(Int_t i = 0, n = (Int_t) bins00.size()-1; i < n; ++i) {
    chain->UnbinnedFit("fExp", "mass", Form("fState==%d&&time>%g&&time<%g&&mass>%g&&mass<%g&&qOS==0&&q%s==0", 
                                            finalStateIdx, bins00[i], bins00[i + 1], timeModels_cuts::minWinFit, timeModels_cuts::maxWinFit, tagName.Data()), "Q");
    slopes00[i] = -fExp->GetParameter(1);
    slopesErr00[i] = fExp->GetParError(1);
  }

  TGraphAsymmErrors * gr = new TGraphAsymmErrors(nBins,mean,slopes,meanErrLow,meanErrHigh,slopesErr,slopesErr);
  gr->SetTitle("");
  TCanvas * c = new TCanvas("c","c");
  c->cd();
  TPad * myPad = (TPad *) c->GetPad(0);
  myPad->SetLeftMargin(0.15);
  myPad->SetBottomMargin(0.15);
  auto setGraphStyle = [](TGraph *gr, Bool_t invertY=false){
    gr->SetMarkerStyle(20);
    gr->SetMarkerColor(kBlack);
    // gr->GetXaxis()->SetRangeUser(0.2,10.2);
    gr->GetXaxis()->SetLimits(0.2,10.2);
    if (invertY)    gr->GetYaxis()->SetRangeUser(-2,0);
    else            gr->GetYaxis()->SetRangeUser(0,2);
    gr->GetXaxis()->SetTitle("Decay time [ps]");
    gr->GetYaxis()->SetTitle("slope [#it{c}^{2}/GeV]");
    gr->GetXaxis()->SetLabelFont(132);
    gr->GetXaxis()->SetLabelSize(0.06);
    gr->GetXaxis()->SetTitleFont(132);
    gr->GetXaxis()->SetTitleSize(0.06);
    gr->GetYaxis()->SetLabelFont(132);
    gr->GetYaxis()->SetLabelSize(0.06);
    gr->GetYaxis()->SetTitleFont(132);
    gr->GetYaxis()->SetTitleSize(0.06);
    gr->SetTitle("");
  };
  setGraphStyle(gr,false);
  gr->Draw("APE");
  fslope->SetParameter(0,-fslope->GetParameter(0));
  fslope->Draw("same");
  //  gr->Draw("PEsame");

  TPaveText * lhcb = new TPaveText(0.25,0.75,0.35,0.85,"NDC");
  lhcb->SetTextAlign(12);
  lhcb->AddText("LHCb");
  //lhcb->AddText("1.9 fb^{-1}");
  lhcb->SetFillColor(kWhite);
  lhcb->SetTextFont(132);
  lhcb->SetTextSize(0.06);
  lhcb->Draw("same");

  //TPaveText * sample = new TPaveText(0.25,0.75,0.35,0.85,"NDC");

  c->Draw();
  c->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s.eps" , name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));
  c->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s.png" , name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));
  c->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s.pdf" , name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));
  c->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s.C"   , name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));
  c->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s.root", name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));


	/*

	  TGraphErrors * gr = new TGraphErrors(nBins+1,mean,slopes,meanErr,slopesErr);
	  TCanvas * c = new TCanvas("c","c");
	  c->cd();
	  gr->SetMarkerStyle(20);
	  gr->SetMarkerColor(kBlack);
	  gr->Draw("APE");
	  fslope->SetParameter(0,-fslope->GetParameter(0));
	  fslope->Draw("same");
	*/
	////////////////////////////////////////////////////////////////////////////////
  
  TGraphErrors * gr11 = new TGraphErrors(nBins11+1,mean11,slopes11,meanErr11,slopesErr11);
  TCanvas * c11 = new TCanvas("c11","c11");
  c11->cd();
  c11->SetLeftMargin(0.15);
  c11->SetBottomMargin(0.15);
  gr11->SetMarkerStyle(20);
  gr11->SetMarkerColor(kBlack);
  setGraphStyle(gr11, true);
  gr11->Draw("APE");  
  fslope11->Draw("same");
  c11->Update();
  c11->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s_ftag11.eps" , name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));
  c11->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s_ftag11.pdf" , name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));
 
  ////////////////////////////////////////////////////////////////////////////////
  
  TGraphErrors * gr10 = new TGraphErrors(nBins10+1,mean10,slopes10,meanErr10,slopesErr10);
  TCanvas * c10 = new TCanvas("c10","c10");
  c10->cd();
  c10->SetLeftMargin(0.15);
  c10->SetBottomMargin(0.15);
  gr10->SetMarkerStyle(20);
  gr10->SetMarkerColor(kBlack);
  setGraphStyle(gr10, true);
  gr10->Draw("APE");
  fslope10->Draw("same");
  c10->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s_ftag10.eps" , name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));
  c10->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s_ftag10.pdf" , name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));
 
  ////////////////////////////////////////////////////////////////////////////////
  
  TGraphErrors * gr01 = new TGraphErrors(nBins01+1,mean01,slopes01,meanErr01,slopesErr01);
  TCanvas * c01 = new TCanvas("c01","c01");
  c01->cd();
  c01->SetLeftMargin(0.15);
  c01->SetBottomMargin(0.15);
  gr01->SetMarkerStyle(20);
  gr01->SetMarkerColor(kBlack);
  setGraphStyle(gr01, true);
  gr01->Draw("APE");
  fslope01->Draw("same");
  c01->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s_ftag01.eps" , name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));
  c01->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s_ftag01.pdf" , name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));

  ////////////////////////////////////////////////////////////////////////////////
  
  TGraphErrors * gr00 = new TGraphErrors(nBins00+1,mean00,slopes00,meanErr00,slopesErr00);
  TCanvas * c00 = new TCanvas("c00","c00");
  c00->cd();
  c00->SetLeftMargin(0.15);
  c00->SetBottomMargin(0.15);
  gr00->SetMarkerStyle(20);
  gr00->SetMarkerColor(kBlack);
  setGraphStyle(gr00, true);
  gr00->Draw("APE");
  fslope00->Draw("same");
  c00->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s_ftag00.eps" , name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));
  c00->SaveAs(Form("${B2HH_OUT}/TimeModels/plots/Fig12_%s_%g_%s_%s_%s_ftag00.pdf" , name.Data(), bdtCut, magnet.Data(), year.Data(), finalState.Data()));


  outFile->WriteTObject(outTree,"","Overwrite");
  outFile->WriteTObject(c,"","Overwrite");
  outFile->WriteTObject(fslope,"","Overwrite");
  outFile->WriteTObject(c11,"","Overwrite");
  outFile->WriteTObject(fslope11,"","Overwrite");
  outFile->WriteTObject(c10,"","Overwrite");
  outFile->WriteTObject(fslope10,"","Overwrite");
  outFile->WriteTObject(c01,"","Overwrite");
  outFile->WriteTObject(fslope01,"","Overwrite");
  outFile->WriteTObject(c00,"","Overwrite");
  outFile->WriteTObject(fslope00,"","Overwrite");
  
  outFile->Close();


  return 0;
}
