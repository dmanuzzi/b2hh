#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <optionParser.h>
#include <TString.h>
#include <TMath.h>


using namespace std;

Int_t main(Int_t argc, Char_t * argv[]) {

	TString name              = getOption(argc,argv,"-n","PIPI");
	TString decay             = getOption(argc,argv,"-d","bdpipi");
	TString decay2            = getOption(argc,argv,"-d2","");
	TString finalState        = getOption(argc,argv,"-f","pipi");
	TString finalState2       = getOption(argc,argv,"-f2","");
	TString bmeson            = getOption(argc,argv,"-B","bd");
	Double_t bdtCut           = atof(getOption(argc,argv,"-b","-1"));
	TString magnet            = getOption(argc,argv,"-m","Tot");
	TString year              = getOption(argc,argv,"-y","Tot");

  const Bool_t flagBmeson = (bmeson=="bd");

  cout << "executing kineweight2 with the following options:\n";
  cout << "  -n <name>       : name of the decay for BDT optimisation:\n" << name << endl;
  cout << "  -d <decay>      : name of the decay to be processed:\n" << decay << endl;
  cout << "  -d2 <decay2>    : name of the decay to be processed:\n" << decay2 << endl;
  cout << "  -f <finalState> : final state hypothesis (default = pipi):\n" << finalState << endl;
  cout << "  -f2 <finalState2> : final state hypothesis (default = pipi):\n" << finalState2 << endl;
  cout << "  -b <bdtCut>     : cut on BDT:\n" << bdtCut << endl;
  cout << "  -m <magnet>     : magnet polarity:\n" << magnet << endl;
  cout << "  -y <year>       : year of data taking ([2011,2012,Tot], default = Tot):\n"  << year << endl;
  cout << "  -B <bmeson>     : b meson type ([bd,bs]):\n";

  Double_t weight = 0, weight1 = 0, weight2 = 0, weight3 = 0, bP = 0, bPT = 0, bETA = 0;
  Float_t mass = 0;
  TChain * chainData = new TChain("data","data");
  chainData->Add(Form("${B2HH_OUT}/sPlot/tuple_reduced/b2hh_%s_%g_%s_%s_PIPI.root/b2hhW",name.Data(),bdtCut,year.Data(),magnet.Data()));
  chainData->SetBranchAddress("bPT",&bPT);
  chainData->SetBranchAddress("bETA",&bETA);
  chainData->SetBranchAddress("weight",&weight);

  TChain * chainMC = new TChain("mc","mc");
  chainMC->Add(Form("${B2HH_OUT}/AccSignal/selectedMC/%s_%s_%s_%g_%s_%s.root/b2hh",decay.Data(),finalState.Data(),name.Data(),bdtCut,year.Data(),magnet.Data()));
  if(decay2!="")
    chainMC->Add(Form("${B2HH_OUT}/AccSignal/selectedMC/%s_%s_%s_%g_%s_%s.root/b2hh", decay2.Data(), finalState2.Data(), name.Data(), bdtCut, year.Data(), magnet.Data()));

  chainMC->SetBranchAddress("bPT",&bPT);
  chainMC->SetBranchAddress("bETA",&bETA);
  chainMC->SetBranchAddress("weight",&weight);
  
  TH1D * hEtaData = new TH1D("hEtaData","hEtaData",50, 0,10);  hEtaData->Sumw2();
  TH1D * hPData  = new TH1D("hPData", "hPData", 100,0,1000); hPData->Sumw2();
  TH2D * hPEtaData = new TH2D("hPEtaData","hPEtaData",100,0,1000,50,0,10); hPEtaData->Sumw2();

  TH1D * hEtaMC = new TH1D(Form("hEtaMC_%s",decay.Data()),Form("hEtaMC_%s",decay.Data()),50, 0,10);  hEtaMC->Sumw2();
  TH1D * hPMC  = new TH1D(Form("hPMC_%s",decay.Data()),Form("hPMC_%s",decay.Data()), 100,0,1000); hPMC->Sumw2();
  TH2D * hPEtaMC = new TH2D(Form("hPEtaMC_%s",decay.Data()),Form("hPEtaMC_%s",decay.Data()),100,0,1000,50,0,10); hPEtaMC->Sumw2();

  TH1D * hEtaCheck = new TH1D(Form("hEtaCheck_%s",decay.Data()),Form("hEtaCheck_%s",decay.Data()),50, 0,10);  hEtaCheck->Sumw2();
  TH1D * hPCheck  = new TH1D(Form("hPCheck_%s",decay.Data()),Form("hPCheck_%s",decay.Data()), 100,0,1000); hPCheck->Sumw2();
  TH2D * hPEtaCheck = new TH2D(Form("hPEtaCheck_%s",decay.Data()),Form("hPEtaMC_%s",decay.Data()),100,0,1000,50,0,10); hPEtaCheck->Sumw2();

  Double_t trueTau = 0; // adding time correction for the bspipi
  chainMC->SetBranchAddress("trueTau",&trueTau);


  for(Int_t iEntry = 0, nEntries = chainData->GetEntries(); iEntry < nEntries; ++iEntry) {
    chainData->GetEntry(iEntry);
    bP = bPT*cosh(bETA);
    hEtaData->Fill(bETA,weight);
    hPData->Fill(bP,weight);
    hPEtaData->Fill(bP,bETA,weight);
  }
  hEtaData->Scale(1./hEtaData->Integral("width"));
  hPData->Scale(1./hPData->Integral("width"));
  hPEtaData->Scale(1./hPEtaData->Integral("width"));
  
  for(Int_t iEntry = 0, nEntries = chainMC->GetEntries(); iEntry < nEntries; ++iEntry) {
    chainMC->GetEntry(iEntry);
    bP = bPT*cosh(bETA);
    hEtaMC->Fill(bETA);
    hPMC->Fill(bP);
    hPEtaMC->Fill(bP,bETA);
  }
  hEtaMC->Scale(1./hEtaMC->Integral("width"));
  hPMC->Scale(1./hPMC->Integral("width"));
  hPEtaMC->Scale(1./hPEtaMC->Integral("width"));

  TH1D * hEtaRatio = (TH1D *) hEtaData->Clone(Form("hEtaRatio_%s",decay.Data()));
  hEtaRatio->Divide(hEtaMC);
  TH1D * hPRatio = (TH1D *) hPData->Clone(Form("hPRatio_%s",decay.Data()));
  hPRatio->Divide(hPMC);
  TH2D * hPEtaRatio = (TH2D *) hPEtaData->Clone(Form("hPEtaRatio_%s",decay.Data()));
  hPEtaRatio->Divide(hPEtaMC);

  TCanvas * cEta = new TCanvas("cEta","cEta");
  cEta->cd();
  hEtaMC->Draw("hist");
  hEtaData->Draw("pesame");
  cEta->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/kineWeight_%s_%s_%g_%s_%s_cEta.root",decay.Data(),name.Data(),bdtCut,year.Data(),magnet.Data()));
  cEta->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/kineWeight_%s_%s_%g_%s_%s_cEta.eps",decay.Data(),name.Data(),bdtCut,year.Data(),magnet.Data()));

  TCanvas * cP = new TCanvas("cP","cP");
  cP->cd();
  hPMC->Draw("hist");
  hPData->Draw("pesame");
  cP->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/kineWeight_%s_%s_%g_%s_%s_cP.root",decay.Data(),name.Data(),bdtCut,year.Data(),magnet.Data()));
  cP->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/kineWeight_%s_%s_%g_%s_%s_cP.eps",decay.Data(),name.Data(),bdtCut,year.Data(),magnet.Data()));

  TString outFileName = Form("${B2HH_OUT}/AccSignal/kineWeight/kineRatio_%s_%g_%s_%s.root",name.Data(),bdtCut,year.Data(),magnet.Data());
  cout << "Opening output file: " << outFileName << endl;
  TFile * outFile = new TFile(outFileName,"UPDATE");
  outFile->WriteTObject(hEtaData,    "","Overwrite");
  outFile->WriteTObject(hPData,      "","Overwrite");
  outFile->WriteTObject(hPEtaData,   "","Overwrite");
  outFile->WriteTObject(hEtaMC,      "","Overwrite");
  outFile->WriteTObject(hPMC,        "","Overwrite");
  outFile->WriteTObject(hPEtaMC,     "","Overwrite");

  outFile->WriteTObject(hEtaRatio,   "","Overwrite");
  outFile->WriteTObject(hPRatio,     "","Overwrite");
  outFile->WriteTObject(hPEtaRatio,  "","Overwrite");
  outFile->Close();

  cout << "Output files saved in "<< outFileName << "\n";


  outFileName = Form("${B2HH_OUT}/AccSignal/kineWeight/%s_%s_%s_%g_%s_%s_Kine.root",decay.Data(),finalState.Data(),name.Data(),bdtCut,year.Data(),magnet.Data());
  outFile = TFile::Open(outFileName,"RECREATE");
  TTree * outChain = (TTree *) chainMC->CloneTree(0);
  outChain->Branch("weight1",&weight1,"weight1/D");// PID
  outChain->Branch("weight2",&weight2,"weight2/D");// Kinematic
  outChain->Branch("weight3",&weight3,"weight3/D");// Time

  int negativeEntries = 0; //some weight2 from the kinemap are negative -> removed for trining purposes (keep them under control)
  for(Int_t iEntry = 0, nEntries = chainMC->GetEntries(); iEntry < nEntries; ++iEntry) {

    chainMC->GetEntry(iEntry);
    bP = bPT*cosh(bETA);
    weight1 = weight; // old PID weight gets assigned to weight 1
    weight2 = hPEtaRatio->Interpolate(bP,bETA); // kine weight -> may yeild negative values due to sPlotting
    if (weight2<0) {
      ++negativeEntries;
      if(decay=="bspipi"&&name=="PIPI") {weight2 = 0;} // removing negative values for BDT training
    }
    if (decay=="bspipi"&&name=="PIPI"){weight3 = TMath::Exp(-trueTau/1.431)/(TMath::Exp(-trueTau/1.522));} // weight3 for fixing bspipi timing
    else weight3 = 1.0;
    //weight *= weight2*weight3;//hPEtaRatio->Interpolate(bP,bETA); // weight contains PID, Kinematic and time correction
    weight = weight1*weight2*weight3;
    hEtaCheck->Fill(bETA,weight2);
    hPCheck->Fill(bP,weight2);
    hPEtaCheck->Fill(bP,bETA,weight2);

    outChain->Fill();
  }
  double negativeRatio = (double)negativeEntries/(double)chainMC->GetEntries();
  cout << "Number of negative entries: " << negativeEntries << "\nout of: " << chainMC->GetEntries() << endl;
  cout << "Negatives are: " << negativeRatio*100 << "%% (applies only to bspipi)" << endl;

  hEtaCheck->Scale(1./hEtaCheck->Integral("width"));
  hPCheck->Scale(1./hPCheck->Integral("width"));
  hPEtaCheck->Scale(1./hPEtaCheck->Integral("width"));

  outFile->WriteTObject(outChain,"","Overwrite");
  outFile->Close();

  outFile = new TFile(Form("${B2HH_OUT}/AccSignal/kineWeight/kineRatio_%s_%g_%s_%s.root",name.Data(),bdtCut,year.Data(),magnet.Data()),"UPDATE");
  outFile->WriteTObject(hEtaCheck,      "","Overwrite");
  outFile->WriteTObject(hPCheck,        "","Overwrite");
  outFile->WriteTObject(hPEtaCheck,     "","Overwrite");
  outFile->Close();
  cout << "output files closed correctly" << endl;


  return 0;
}
