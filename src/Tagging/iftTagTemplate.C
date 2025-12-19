#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <TROOT.h>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TRandom3.h>
#include <TH2D.h>
#include <TH3D.h>
#include <RooFit.h>
#include <RooRealVar.h>
#include <RooDataSet.h>
#include <RooKeysPdf.h>
#include <RooWorkspace.h>
#include <optionParser.h>
#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>
#include <RooPlot.h>
#include <TCanvas.h>

using namespace std;
using namespace RooFit;

int main(int argc, char * argv[]) {

    TString help = argv[1];
    if(help =="-h" || help == "--help") {
        printf("Usage of optim:\n");
        printf("  ./create [options]\n");
        printf("Options:\n");
        printf("  -d <decay>      : name of the decay used to optimise BDT ([PIPI,KK], default = PIPI)\n");
        printf("  -f <finalState> : final state hypothesis (default = pipi)\n");
        printf("  -c <cut>        : pid cuts depending on final state (default = -3.5.-3.5)\n");
        printf("  -b <bdtCut>     : cut on BDT (default = -1)\n");
        printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
        printf("  -y <year>       : year of data taking ([201516,2017s29r2p2,2018], default = 201516)\n");
        //printf("  -F <effNoFid>   : efficiencies out of fiductial region (pk_kp_ppi_pip, default = 0_0_0_0)\n");
        return 0;
    }

    TString decay         = getOption(argc,argv,"-d",""); //investigate
    TString finalState    = getOption(argc,argv,"-f","");
    TString cuts          = getOption(argc,argv,"-c","");
    Int_t pidPlus1        = atoi(((TObjString *)cuts.Tokenize('.')->At(0))->String());
    Int_t pidPlus2        = atoi(((TObjString *)cuts.Tokenize('.')->At(1))->String());
    Int_t pidMinus1       = atoi(((TObjString *)cuts.Tokenize('.')->At(2))->String());
    Int_t pidMinus2       = atoi(((TObjString *)cuts.Tokenize('.')->At(3))->String());
    Double_t bdtCut       = atof(getOption(argc,argv,"-b",""));
    TString magnet        = getOption(argc,argv,"-m","");
    TString year          = getOption(argc,argv,"-y","");


    printf("EXECUTING ./iftTagTemplates -d %s -f %s -c %d.%d.%d.%d -b %g -m %s -y %s\n",
            decay.Data(),finalState.Data(),pidPlus1,pidPlus2,pidMinus1,pidMinus2,
            bdtCut,magnet.Data(),year.Data());

    TString hypoPlus = "", hypoMinus = "";
    TString namePlus = "", nameMinus = "";
    if(finalState=="kpi")  { hypoPlus = "K";  hypoMinus = "PI"; }
    if(finalState=="pik")  { hypoPlus = "PI"; hypoMinus = "K";  }
    if(finalState=="pipi") { hypoPlus = "PI"; hypoMinus = "PI"; }
    if(finalState=="kk")   { hypoPlus = "K";  hypoMinus = "K";  }
    if(finalState=="pk")   { hypoPlus = "P";  hypoMinus = "K";  }
    if(finalState=="kp")   { hypoPlus = "K";  hypoMinus = "P";  }
    if(finalState=="ppi")  { hypoPlus = "P";  hypoMinus = "PI"; }
    if(finalState=="pip")  { hypoPlus = "PI"; hypoMinus = "P";  }

    TString decays[12] = {"bdpipi","bdkpi","bdpik","bdkk",
                            "bskk","bskpi","bspik","bspipi",
                            "lbpk","lbkp","lbppi","lbpip" };
    TString tmpDecay;
    Double_t //truePPlus = 0, truePMinus = 0, truePP = 0,
            piplusP = 0, piplusETA = 0, 
            piminusP = 0, piminusETA = 0,
            piplusDLLKPI = 0, piplusDLLPPI = 0,
            piminusDLLKPI = 0, piminusDLLPPI = 0,
            etaIFT_Bd = 0, etaIFT_Bs = 0,
            //trueMass = 0, Weight = 0,
            BDT = 0, PIDweight = 0;
    Bool_t qIFT_Bd, qIFT_Bs;
    TChain * inChain = new TChain("inChain");

    Int_t nEntries;

    TFile * effFilePlus; TFile * effFileMinus;
    TH3D * hEffPlus; TH3D * hEffMinus;
    TH2D * hEffPlus2D; TH2D * hEffMinus2D;

    TFile *f = new TFile(Form("${B2HH_OUT}/Tagging/iftTemplates/%s_%g_%s_%s_%s.root",decay.Data(),bdtCut,finalState.Data(),year.Data(),magnet.Data()), "RECREATE");

    for(Int_t iDecay = 0; iDecay < 12; iDecay++) {

      if(iDecay > 0) { 
                        inChain->Reset();
                        effFilePlus->Close(); 
                        effFileMinus->Close(); 
                    }

        tmpDecay = decays[iDecay];

        if(tmpDecay=="bdkpi")  { namePlus   = "Kplus";  nameMinus   = "PIminus";  }
        if(tmpDecay=="bdpik")  { namePlus   = "PIplus"; nameMinus   = "Kminus";   }
        if(tmpDecay=="bdpipi") { namePlus   = "PIplus"; nameMinus   = "PIminus";  }
        if(tmpDecay=="bdkk")   { namePlus   = "Kplus";  nameMinus   = "Kminus";   }
        if(tmpDecay=="bskpi")  { namePlus   = "Kplus";  nameMinus   = "PIminus";  }
        if(tmpDecay=="bspik")  { namePlus   = "PIplus"; nameMinus   = "Kminus";   }
        if(tmpDecay=="bspipi") { namePlus   = "PIplus"; nameMinus   = "PIminus";  }
        if(tmpDecay=="bskk")   { namePlus   = "Kplus";  nameMinus   = "Kminus";   }
        if(tmpDecay=="lbpk")   { namePlus   = "Pplus";  nameMinus   = "Kminus";   }
        if(tmpDecay=="lbkp")   { namePlus   = "Kplus";  nameMinus   = "Pminus";   }
        if(tmpDecay=="lbppi")  { namePlus   = "Pplus";  nameMinus   = "PIminus";  }
        if(tmpDecay=="lbpip")  { namePlus   = "PIplus"; nameMinus   = "Pminus";   }

        TString effFilePlusName = Form("${B2HH_OUT}/PID/effCalib/TrackEff/eff%s_%d.%d_71_10_1_6_%s_%s.root",
                                        hypoPlus.Data(),pidPlus1,pidPlus2,magnet.Data(),year.Data());
        TString effFileMinusName = Form("${B2HH_OUT}/PID/effCalib/TrackEff/eff%s_%d.%d_71_10_1_6_%s_%s.root",
                                        hypoMinus.Data(),pidMinus1,pidMinus2,magnet.Data(),year.Data());
        printf("%s\n", tmpDecay.Data());                                        

        effFilePlus  = TFile::Open(effFilePlusName,"READ");
        effFileMinus = TFile::Open(effFileMinusName,"READ");

        TString hEffPlusName  = Form("hEff%s_is%s",namePlus.Data(),hypoPlus.Data());
        TString hEffMinusName = Form("hEff%s_is%s",nameMinus.Data(),hypoMinus.Data());

        printf("opening %s -> %s\n", effFilePlusName.Data(),  hEffPlusName.Data());
        printf("opening %s -> %s\n", effFileMinusName.Data(), hEffMinusName.Data());
        hEffPlus      = (TH3D *) effFilePlus->Get(hEffPlusName);
        hEffMinus     = (TH3D *) effFileMinus->Get(hEffMinusName);
        hEffPlus2D    = (TH2D *) hEffPlus->Project3D("yx");
        hEffMinus2D   = (TH2D *) hEffMinus->Project3D("yx");

        auto tag_years = datasetFlags::chain_years[year];
        auto tag_magnet = datasetFlags::chain_magnet[magnet];
        chainAdder::chainAdder(inChain, "${B2HH_OUT}/Data/tuple_merged/%s_%s_%s.root/b2hh",
                            tmpDecay, tag_years, tag_magnet);

        inChain->SetBranchStatus(Form("bdt%s",decay.Data()),1); inChain->SetBranchAddress(Form("bdt%s",decay.Data()),&BDT);
        inChain->SetBranchStatus("piplusP",    1); inChain->SetBranchAddress("piplusP",    &piplusP   );
        inChain->SetBranchStatus("piplusETA",  1); inChain->SetBranchAddress("piplusETA",  &piplusETA );
        inChain->SetBranchStatus("piminusP",   1); inChain->SetBranchAddress("piminusP",   &piminusP  );
        inChain->SetBranchStatus("piminusETA", 1); inChain->SetBranchAddress("piminusETA", &piminusETA);

        inChain->SetBranchStatus("piplusDLLKPI",1); inChain->SetBranchAddress("piplusDLLKPI",&piplusDLLKPI);
        inChain->SetBranchStatus("piplusDLLPPI",1); inChain->SetBranchAddress("piplusDLLPPI",&piplusDLLPPI);
        inChain->SetBranchStatus("piminusDLLKPI",1); inChain->SetBranchAddress("piminusDLLKPI",&piminusDLLKPI);
        inChain->SetBranchStatus("piminusDLLPPI",1); inChain->SetBranchAddress("piminusDLLPPI",&piminusDLLPPI);

        //hardcoded IFT branches? 
        inChain->SetBranchStatus("qIFT_Bd",1); inChain->SetBranchAddress("qIFT_Bd",&qIFT_Bd);
        inChain->SetBranchStatus("qIFT_Bs",1); inChain->SetBranchAddress("qIFT_Bs",&qIFT_Bs);

        inChain->SetBranchStatus("etaIFT_Bd",1); inChain->SetBranchAddress("etaIFT_Bd",&etaIFT_Bd);
        inChain->SetBranchStatus("etaIFT_Bs",1); inChain->SetBranchAddress("etaIFT_Bs",&etaIFT_Bs);
        
        TH1D * hetaIFT_Bd = new TH1D(Form("h_%s_etaIFT_Bd",tmpDecay.Data()),Form("h_%s_etaIFT_Bd",tmpDecay.Data()),100,0,0.5);
        TH1D * hetaIFT_Bs = new TH1D(Form("h_%s_etaIFT_Bs",tmpDecay.Data()),Form("h_%s_etaIFT_Bs",tmpDecay.Data()),100,0,0.5);
        hetaIFT_Bd->Sumw2();
        hetaIFT_Bs->Sumw2();
        
        nEntries = inChain->GetEntries();
        //nEntries = 1000;

        for(Int_t iEntry = 0; iEntry < nEntries; ++iEntry) {
            inChain->GetEntry(iEntry);
            if(BDT<bdtCut) continue;
            PIDweight = hEffPlus2D->Interpolate(piplusP,piplusETA)*
                        hEffMinus2D->Interpolate(piminusP,piminusETA);
            hetaIFT_Bd->Fill(etaIFT_Bd,PIDweight);
            hetaIFT_Bs->Fill(etaIFT_Bs,PIDweight);
            
        }
        f->cd();
        hetaIFT_Bd->Write();
        hetaIFT_Bs->Write();
	TString saveHistoPath = Form("Tagging/iftTemplates/plots/%s_%s_%s_%g_%s_%s",
				     tmpDecay.Data(),finalState.Data(),decay.Data(),bdtCut,year.Data(),magnet.Data());
	TCanvas * cBd = new TCanvas("cBd","cBd",800,600);
	hetaIFT_Bd->Draw();
	cBd->SaveAs(Form("${B2HH_OUT}/%s_IFT_Bd.pdf",saveHistoPath.Data()));
	cBd->SaveAs(Form("${B2HH_OUT}/%s_IFT_Bd.root",saveHistoPath.Data()));
	TCanvas * cBs =	new TCanvas("cBs","cBs",800,600);
	hetaIFT_Bs->Draw();
	cBs->SaveAs(Form("${B2HH_OUT}/%s_IFT_Bs.pdf",saveHistoPath.Data()));
	cBs->SaveAs(Form("${B2HH_OUT}/%s_IFT_Bs.root",saveHistoPath.Data()));
	//channel/final state/bdt/bdtcut/year/magnet
	delete cBd; delete cBs;
    }
}
