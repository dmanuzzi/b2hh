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
#include <RooNumIntConfig.h>
#include <RooAbsReal.h>
#include <RooBDecay.h>
#include <RooRealConstant.h>
#include <RooGaussModel.h>
#include <TPaveText.h>
#include <TLegend.h>
#include <RooCurve.h>

#include <config_datasets.h>
#include <chainAdder.h>
#include <constValues.h>
#include <expandFileName.h>
using namespace std;
using namespace RooFit;

Int_t main(Int_t argc, Char_t * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of optim:\n");
    printf("  ./fitAcc2 [options]\n");
    printf("Options:\n");
    printf("  -C <name>       : decay used for BDT train ([PIPI, KK], default = PIPI)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = 0.12)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking ([2011,2012,Tot], default = 2016)\n");
    printf("  -n <decay>      : decay under study (default = bdkpi)\n");
    printf("  -f <finalState> : considered final state hypothesis (default = kpi)\n");
    printf("  -T              : flag for tagged acceptance\n");
    printf("  -D              : flag for data acceptance\n");
    printf("  -F              : flag for executing the fit\n");
    return 0;
  }


  RooAbsReal::defaultIntegratorConfig()->setEpsAbs(1e-9) ;
  RooAbsReal::defaultIntegratorConfig()->setEpsRel(1e-9) ;
  RooAbsReal::defaultIntegratorConfig()->getConfigSection("RooAdaptiveGaussKronrodIntegrator1D").setCatLabel("method","15Points");
  RooAbsReal::defaultIntegratorConfig()->getConfigSection("RooAdaptiveGaussKronrodIntegrator1D").setRealValue("maxSeg", 1000 );
  RooAbsReal::defaultIntegratorConfig()->method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D");
  RooAbsReal::defaultIntegratorConfig()->method1DOpen().setLabel("RooAdaptiveGaussKronrodIntegrator1D");

  RooAbsReal::defaultIntegratorConfig()->Print("v");

  TString configuration = getOption(argc,argv,"-C","PIPI");
  Double_t bdtCut = atof(getOption(argc,argv,"-b","0.12"));
  TString name = getOption(argc,argv,"-n","bdkpi");
  TString finalState = getOption(argc,argv,"-f","kpi");
  TString magnet = getOption(argc,argv,"-m","Tot");
  TString year = getOption(argc,argv,"-y","Tot");
  Bool_t tagFlag = getBoolOption(argc,argv,"-T");
  Bool_t dataFlag = getBoolOption(argc,argv,"-D");
  Bool_t fitFlag = getBoolOption(argc,argv,"-F");

  TString taggerName = "";
  if(configuration=="PIPI") taggerName = "qSS";
  else if (year == "2017")  taggerName = "qSSk_old";
  else                      taggerName = "qSSk";

  RooRealVar * time = new RooRealVar("time","Decay time",accSignal_cuts::minTimeFit,accSignal_cuts::maxTimeFit,"ps");
  //  RooRealVar * mass = new RooRealVar("mass","Invariant mass",5.366,6.2);
  RooCategory * q = new RooCategory(taggerName,taggerName);
  // q->defineType("B",1); q->defineType("Bbar",-1);
  // if(!tagFlag) q->defineType("Untag",0);
  q->defineType("Untag", 0);
  RooRealVar *weight = new RooRealVar("weight", "weight", -1e6, 1e6);

  // Double_t tauData = 1.520, tauBd  = 1.519,
  //          tauBsH  = 1.661, tauBsL = 1.405,
  //          tauLb   = 1.451, tauKK  = 1.512,
  //          tauBs = 2./(1./tauBsH+1./tauBsL),
  //          dgBs  = (1./tauBsL-1./tauBsH);
  // Double_t CKK = 0.23945601652608023, SKK = 0.22134502198975092;
  // Double_t ADGKK = -sqrt(1-CKK*CKK-SKK*SKK);
  // Double_t dGoGKK = 0.179518, GKK = 1./tauKK;
  // Double_t dGKK = dGoGKK*GKK;
  // Double_t tauKKH = 1/(GKK-0.5*dGKK),
  //          tauKKL = 1/(GKK+0.5*dGKK);
/*
  RooRealVar * gammaData = new RooRealVar("gammaData","gammaData",-1./tauData);
  RooRealVar * gammaBd = new RooRealVar("gammaBd","gammaBd",-1./tauBd);
  RooRealVar * gammaH = new RooRealVar("gammaH","gammaH",-1./tauBsH);
  RooRealVar * gammaL = new RooRealVar("gammaL","gammaL",-1./tauBsL);
  RooRealVar * gammaHKK = new RooRealVar("gammaHKK","gammaHKK",-1./tauKKH);
  RooRealVar * gammaLKK = new RooRealVar("gammaLKK","gammaLKK",-1./tauKKL);
  RooRealVar * fracBs = new RooRealVar("fracBs","fracBs",0.5);
  RooRealVar * fracKK = new RooRealVar("fracKK","fracKK",0.5*(1-ADGKK));
  RooRealVar * gammaLb = new RooRealVar("gammaLb","gammaLb",-1./tauLb);

  RooExponential * expData = new RooExponential("expData","expData",*time,*gammaData);
  RooExponential * expBd = new RooExponential("expBd","expBd",*time,*gammaBd);
  RooExponential * expH = new RooExponential("expH","expH",*time,*gammaH);
  RooExponential * expL = new RooExponential("expL","expL",*time,*gammaL);
  RooAddPdf * expBs = new RooAddPdf("expBs","expBs",RooArgSet(*expH,*expL),RooArgSet(*fracBs));

  RooExponential * expHKK = new RooExponential("expHKK","expHKK",*time,*gammaHKK);
  RooExponential * expLKK = new RooExponential("expLKK","expLKK",*time,*gammaLKK);
  RooAddPdf * expKK = new RooAddPdf("expKK","expKK",RooArgSet(*expLKK,*expHKK),RooArgSet(*fracKK));

  RooExponential * expLb = new RooExponential("expLb","expLb",*time,*gammaLb);
*/
  RooRealVar *gammaData = new RooRealVar("gammaData", "gammaData", accSignal_consts::tauData);
  RooRealVar *gammaBd = new RooRealVar("gammaBd", "gammaBd", accSignal_consts::tauBd);
  RooRealVar *gammaBs = new RooRealVar("gammaBs", "gammaBs", accSignal_consts::tauBs);
  RooRealVar *deltaGammaBs = new RooRealVar("deltaGammaBs", "deltaGammaBs", accSignal_consts::dgBs);
  RooRealVar *gammaKK = new RooRealVar("gammaKK", "gammaKK", accSignal_consts::tauKK);
  RooRealVar *deltaGammaKK = new RooRealVar("deltaGammaKK", "deltaGammaKK", accSignal_consts::dGKK);
  RooRealVar *adgKK = new RooRealVar("adgKK", "adgKK", accSignal_consts::ADGKK);
  RooRealVar *gammaLb = new RooRealVar("gammaLb", "gammaLb", accSignal_consts::tauLb);

  RooGaussModel * resT = new RooGaussModel("resT","resT",*time,RooRealConstant::value(-0.003),RooRealConstant::value(0.040));
  RooRealVar * dms = new RooRealVar("dms","dms",accSignal_consts::dms);
  RooRealVar *dmd = new RooRealVar("dmd", "dmd", accSignal_consts::dmd);

  //RooBDecay * expData = new RooBDecay("expData","expData",*time,*gammaData,RooRealConstant::value(0.0),
  //                                                        RooRealConstant::value(1.0+0.084*0.011),RooRealConstant::value(0.0),
  //                                                        RooRealConstant::value(-0.095*0.01),RooRealConstant::value(0.0),
  //                                                        *dmd,*resT,RooBDecay::SingleSided);
  RooBDecay * expData = new RooBDecay("expData","expData",*time,*gammaData,RooRealConstant::value(0.0),
                                                          RooRealConstant::value(1.0),RooRealConstant::value(0.0),
                                                          RooRealConstant::value(0.0),RooRealConstant::value(0.0),
                                                          *dmd,*resT,RooBDecay::SingleSided);

  RooBDecay * expBd   = new RooBDecay("expBd",  "expBd",  *time,*gammaBd,RooRealConstant::value(0.0),
                                                          RooRealConstant::value(1.0),RooRealConstant::value(0.0),
                                                          RooRealConstant::value(0.0),RooRealConstant::value(0.0),
                                                          *dmd,*resT,RooBDecay::SingleSided);

  RooBDecay * expBs   = new RooBDecay("expBs",  "expBs",  *time,*gammaBs,*deltaGammaBs,
                                                          RooRealConstant::value(1.0),RooRealConstant::value(0.0),
                                                          RooRealConstant::value(0.0),RooRealConstant::value(0.0),
                                                          *dms,*resT,RooBDecay::SingleSided);

  RooBDecay * expKK   = new RooBDecay("expKK",  "expKK",  *time,*gammaKK,*deltaGammaKK,
                                                          RooRealConstant::value(1.0),*adgKK,
                                                          RooRealConstant::value(0.0),RooRealConstant::value(0.0),
                                                          *dms,*resT,RooBDecay::SingleSided);

  RooBDecay * expLb   = new RooBDecay("expLb",  "expLb",  *time,*gammaLb,RooRealConstant::value(0.0),
                                                          RooRealConstant::value(1.0),RooRealConstant::value(0.0),
                                                          RooRealConstant::value(0.0),RooRealConstant::value(0.0),
                                                          *dmd,*resT,RooBDecay::SingleSided);


  RooRealVar * p0 = new RooRealVar("p0","p0",0,10);
  RooRealVar * p1 = new RooRealVar("p1","p1",-100,100);
  RooRealVar * p2 = new RooRealVar("p2","p2",-100,100);
  RooRealVar * p3 = new RooRealVar("p3","p3",-100,100);
  RooRealVar * p4 = new RooRealVar("p4","p4",-100,100);
  RooRealVar * p5 = new RooRealVar("p5","p5",-100,100);
  RooRealVar * p6 = new RooRealVar("p6","p6",-100,100);
  RooRealVar * p7 = new RooRealVar("p7","p7",-100,100);
  RooRealVar * p8 = new RooRealVar("p8","p8",-100,100);
  RooRealVar * p9 = new RooRealVar("p9","p9",-100,100);
  RooRealVar * p10 = new RooRealVar("p10","p10",3,10);
  RooTimeAccPdf * acc = new RooTimeAccPdf("acc","acc",*time,*p0,*p1,*p2,*p3,*p4,*p5,
                                                            *p6,*p7,*p8,*p9,*p10);
 
  RooEffProd * pdf;
  if(dataFlag) {
    pdf = new RooEffProd("pdf","pdf",*expData,*acc);
  } else {
    if (name == "bdkpi" || name == "bdpipi" || name == "bdkk") 
      pdf = new RooEffProd("pdf","pdf",*expBd,*acc);
    else if (name == "bskpi" || name == "bspipi")
      pdf = new RooEffProd("pdf","pdf",*expBs,*acc);
    else if (name == "bskk")
      pdf = new RooEffProd("pdf","pdf",*expKK,*acc);
    else if (name == "lbpk")
      pdf = new RooEffProd("pdf","pdf",*expLb,*acc);
    else { printf("WRONG DECAY NAME\n"); return 0; }
  }
  time->setRange("total",accSignal_cuts::minTimeFit, accSignal_cuts::maxTimeFit);
  RooAbsReal * pdfIntegral = pdf->createIntegral(RooArgSet(*time),"total");


  TChain * chain = new TChain("b2hh","b2hh");
  if(dataFlag){
    chain->Add(Form("${B2HH_OUT}/AccSignal/bkgSubtractedSamples/b2hh_%s_%g_%s_%s_Sub.root",configuration.Data(),bdtCut,year.Data(),magnet.Data()));
  } else {
    // chain->Add(Form("${B2HH_OUT}/AccSignal/kineWeight/%s_%s_%s_%g_%s_%s_Kine.root", name.Data(), finalState.Data(),
    //                 configuration.Data(), bdtCut,
    //                 year.Data(),
    //                 magnet.Data()));
    if (name == "bskk" && finalState == "kk"){
      chain->Add(Form("${B2HH_OUT}/Reduce/b2hh_%s_%g_%s_%s.root", 
                      configuration.Data(), bdtCut,
                      year.Data(),
                      magnet.Data()));
    } else {
      chain->Add(Form("${B2HH_OUT}/AccSignal/selectedMC/%s_%s_%s_%g_%s_%s.root", name.Data(), finalState.Data(),
                      configuration.Data(), bdtCut,
                      year.Data(),
                      magnet.Data()));
    }
  }
  RooArgSet * obs = new RooArgSet();
  obs->add(*time); obs->add(*q); //obs->add(*weight);
  //obs->add(*mass);

  RooArgSet * params = pdf->getParameters(*obs);
  TString nfParams = Form("${B2HH_OUT}/AccSignal/params/params%s_%s_%s_%g_%s_%s_%s.txt",
                          (tagFlag?"T":""), (dataFlag?"data":TString(name+"_"+finalState).Data()),
                          configuration.Data(), bdtCut, year.Data(), magnet.Data(),
                          (dataFlag?"Sub":"Kine"));
  system(Form("touch %s", nfParams.Data()));
  expandFileName::expandFileName(nfParams);
  printf("read parameter file: %s\n", nfParams.Data());
  params->readFromFile(nfParams);
  // if (dataFlag)
  // {
  //   if(tagFlag)
  //     params->readFromFile(Form("${B2HH_OUT}/AccSignal/params/paramsT_data_%s_%g_%s_%s_Sub.txt",
  //                               configuration.Data(), bdtCut, year.Data(), magnet.Data()));
  //   else
  //     params->readFromFile(Form("${B2HH_OUT}/AccSignal/params/params_data_%s_%g_%s_%s_Sub.txt",
  //                               configuration.Data(), bdtCut, year.Data(), magnet.Data()));
  // }
  // else {
  //   if(tagFlag)
  //     params->readFromFile(Form("${B2HH_OUT}/AccSignal/params/paramsT_%s_%s_%s_%g_%s_%s_Kine.txt",
  //                               name.Data(), finalState.Data(),
  //                               configuration.Data(), bdtCut,
  //                               year.Data(), magnet.Data()));
  //   else
  //     params->readFromFile(Form("${B2HH_OUT}/AccSignal/params/params_%s_%s_%s_%g_%s_%s_Kine.txt",
  //                               name.Data(), finalState.Data(),
  //                               configuration.Data(), bdtCut,
  //                               year.Data(), magnet.Data()));
  // }
  params->Print("v");
 
//  RooDataSet * data = new RooDataSet("data","data",*obs,Import(*chain),WeightVar("weight"));
  RooDataSet *data = new RooDataSet("data", "data", *obs, Import(*chain));

  if(fitFlag) {
    RooFitResult * res = pdf->fitTo(*data,NumCPU(12),Verbose(kTRUE),
				    PrintLevel(3),Strategy(2),Hesse(),
				    SumW2Error(kFALSE),Offset(kTRUE),Save());
    res->Print("v");
  }
  
  params->writeToFile(nfParams);
  // if(dataFlag) {
  //   if(tagFlag) 
  //     params->writeToFile(Form("${B2HH_OUT}/AccSignal/params/paramsT_data_%s_%g_%s_%s_Sub.txt",
	// 		       configuration.Data(),bdtCut,year.Data(),magnet.Data()));
  //   else
  //     params->writeToFile(Form("${B2HH_OUT}/AccSignal/params/params_data_%s_%g_%s_%s_Sub.txt",
	// 		       configuration.Data(),bdtCut,year.Data(),magnet.Data()));
  // }
  // else {
  //   if(tagFlag)
  //     params->writeToFile(Form("${B2HH_OUT}/AccSignal/params/paramsT_%s_%s_%s_%g_%s_%s_Kine.txt",
	// 		       name.Data(),finalState.Data(),
	// 		       configuration.Data(),bdtCut,
	// 		       year.Data(),magnet.Data()));
  //   else
  //     params->writeToFile(Form("${B2HH_OUT}/AccSignal/params/params_%s_%s_%s_%g_%s_%s_Kine.txt",
	// 		       name.Data(),finalState.Data(),
	// 		       configuration.Data(),bdtCut,
	// 		       year.Data(),magnet.Data()));
  // }
  RooPlot * plot = time->frame(accSignal_cuts::minTimeFit, accSignal_cuts::maxTimeFit,280);
  plot->SetTitle("");
  data->plotOn(plot,MarkerSize(0.8));
  acc->plotOn(plot,LineColor(kRed),Normalization(1,RooAbsReal::Relative),Name("acc"));
  pdf->plotOn(plot,Name("pdf"),LineWidth(2));
  data->plotOn(plot,MarkerSize(0.8));

  plot->GetXaxis()->SetTitle("Decay time [ps]");
  plot->GetXaxis()->SetTitleSize(0.05);
  plot->GetXaxis()->SetLabelSize(0.05);
  plot->GetXaxis()->SetTitleOffset(1.1);
  plot->GetXaxis()->SetTickLength(0.05);
  plot->GetXaxis()->SetLabelFont(62);
  plot->GetXaxis()->SetTitleFont(62);
  plot->GetYaxis()->SetTitle("Candidates / ( 0.05 ps )");
  plot->GetYaxis()->SetTitleSize(0.05);
  plot->GetYaxis()->SetLabelSize(0.05);
  plot->GetYaxis()->SetTitleOffset(1.7);
  plot->GetYaxis()->SetTickLength(0.05);
  plot->GetYaxis()->SetLabelFont(62);
  plot->GetYaxis()->SetTitleFont(62);
  plot->GetXaxis()->SetTitleFont(132);
  plot->GetXaxis()->SetLabelFont(132);
  plot->GetXaxis()->SetTitleSize(0.06);
  plot->GetXaxis()->SetLabelSize(0.06);
  plot->GetYaxis()->SetTitleFont(132);
  plot->GetYaxis()->SetLabelFont(132);
  plot->GetYaxis()->SetTitleSize(0.06);
  plot->GetYaxis()->SetLabelSize(0.06);
  plot->GetYaxis()->SetTitleOffset(1.70);
  plot->GetYaxis()->SetNdivisions(509,kTRUE);
  plot->SetMinimum(0);
  /*
  TCanvas * c1 = new TCanvas("c1","c1",700,700);
  TPad * upperPad = (TPad *) c1->GetPad(0);
  upperPad->SetLeftMargin(0.2);
  upperPad->SetBottomMargin(0.15);
  upperPad->cd();
  plot->Draw();
  */
  TPaveText * lhcb = new TPaveText(0.35,0.55,0.55,0.85,"NDC");
  lhcb->SetTextAlign(12);
  lhcb->AddText("LHCb");
  //  lhcb->AddText("1.9 fb^{-1}");  
  /*
  if(!tagFlag)
    lhcb->AddText("#it{B}^{0}#rightarrow #it{K}^{+}#it{#pi}^{ #minus}");
  else {
    if(configuration=="PIPI")
      lhcb->AddText("SSc-tagged #it{B}^{0}#rightarrow #it{K}^{+}#it{#pi}^{ #minus}");
    else
      lhcb->AddText("SS#it{K}-tagged #it{B}^{0}#rightarrow #it{K}^{+}#it{#pi}^{ #minus}");
  }
  if(configuration=="PIPI")
      lhcb->AddText("#it{#pi}^{+}#it{#pi}^{ #minus} BDT selection");
  else
      lhcb->AddText("#it{K}^{+}#it{K}^{ #minus} BDT selection");
  */
  lhcb->AddText(Form("Year: %s, mag: %s", year.Data(), magnet.Data()));
  lhcb->AddText(Form("%s %s, f. state: %s", (dataFlag?"DATA":"MC"), name.Data(), finalState.Data()));
  lhcb->AddText(Form("bdt%s>%g, %s",configuration.Data(), bdtCut, (tagFlag?"tagged":"untagged")));
  lhcb->SetFillColor(kWhite);
  lhcb->SetTextFont(132);
  lhcb->SetTextSize(0.05);
  //lhcb->Draw("same");

  //c1->Update();

  
  //c1->Update();

  TCanvas * c1 = new TCanvas("c1","c1",700,725);
  c1->cd();
  TPad * upperPad = new TPad("upperPad","upperPad",0,0.2,1,1);
  upperPad->SetLeftMargin(0.15);
  upperPad->SetBottomMargin(0.15);
  TPad * lowerPad = new TPad("lowerPad","lowerPad",0,0,1,0.2);
  lowerPad->SetLeftMargin(0.15);
  lowerPad->Draw();
  upperPad->Draw();
  upperPad->cd();
  plot->Draw();

  TLegend * leg = new TLegend(0.35,0.45,0.55,0.55,"");
  leg->SetName("leg");
  leg->SetTextFont(132);
  leg->SetTextSize(0.06);
  //leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  //leg->SetX1(0.35);
  //leg->SetX2(0.35);
  //leg->SetY1(0.55);
  //leg->SetY2(0.75);
  RooCurve * myAcc = (RooCurve *) c1->FindObject("acc");
  leg->AddEntry(myAcc,"Decay-time efficiency","l");
  //leg->Draw("same");

  lhcb->Draw("same");
  leg->Draw("same");

  RooHist * hpull = plot->pullHist();
  hpull->SetFillColor(kBlue);
  RooPlot * pulls = time->frame(accSignal_cuts::minTimeFit, accSignal_cuts::maxTimeFit,280);
  pulls->SetTitle("");
  pulls->addPlotable(hpull,"BX");
  pulls->GetYaxis()->SetRangeUser(-5,5);
  pulls->GetYaxis()->SetTitle("pull");
  pulls->GetYaxis()->SetTitleSize(0.1);
  pulls->GetYaxis()->SetLabelSize(0.1);
  pulls->GetYaxis()->SetNdivisions(504,kTRUE);
  pulls->GetYaxis()->SetTitleOffset(0.2);
  lowerPad->cd();
  pulls->Draw();

  TFile * outFile;

  if(dataFlag) {
    if(tagFlag)
      outFile = TFile::Open(Form("${B2HH_OUT}/AccSignal/plots/plotT_data_%s_%g_%s_%s_Sub.root",
				 configuration.Data(),bdtCut,
				 year.Data(),magnet.Data()),"RECREATE");
    else
      outFile = TFile::Open(Form("${B2HH_OUT}/AccSignal/plots/plot_data_%s_%g_%s_%s_Sub.root",
				 configuration.Data(),bdtCut,
				 year.Data(),magnet.Data()),"RECREATE");
  }
  else {
    if(tagFlag)
      outFile = TFile::Open(Form("${B2HH_OUT}/AccSignal/plots/plotT_%s_%s_%s_%g_%s_%s_Kine.root",
				 name.Data(),finalState.Data(),
				 configuration.Data(),bdtCut,
				 year.Data(),magnet.Data()),"RECREATE");
    else
      outFile = TFile::Open(Form("${B2HH_OUT}/AccSignal/plots/plot_%s_%s_%s_%g_%s_%s_Kine.root",
				 name.Data(),finalState.Data(),
				 configuration.Data(),bdtCut,
				 year.Data(),magnet.Data()),"RECREATE");
  }
  outFile->WriteTObject(c1,"","Overwrite");
  for (TString format : {"eps", "pdf", "png", "C" })
    c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAcc_%s_%s_%s_%g_%s_%s_%s.%s",
		    (dataFlag?"Data":name.Data()),finalState.Data(),
		    configuration.Data(),bdtCut, year.Data(),magnet.Data(),
		    (tagFlag?"tag":"tot"), format.Data()));

  /*
  if(dataFlag) {
    if(tagFlag) {
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAccData_%s_%g_%s_%s_tag.eps",configuration.Data(),bdtCut));
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAccData_%s_%g_%s_%s_tag.pdf",configuration.Data(),bdtCut));
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAccData_%s_%g_%s_%s_tag.png",configuration.Data(),bdtCut));
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAccData_%s_%g_%s_%s_tag.C",  configuration.Data(),bdtCut));
    }
    else {
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAccData_%s_%g_%s_%s_tot.eps",configuration.Data(),bdtCut));
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAccData_%s_%g_%s_%s_tot.pdf",configuration.Data(),bdtCut));
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAccData_%s_%g_%s_%s_tot.png",configuration.Data(),bdtCut));
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAccData_%s_%g_%s_%s_tot.C",  configuration.Data(),bdtCut));
    }
  }
  else {
    if(tagFlag) {
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAcc_%s_%s_%s_%g_%s_%s_tag.eps",name.Data(),finalState.Data(),configuration.Data(),bdtCut));
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAcc_%s_%s_%s_%g_%s_%s_tag.pdf",name.Data(),finalState.Data(),configuration.Data(),bdtCut));
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAcc_%s_%s_%s_%g_%s_%s_tag.png",name.Data(),finalState.Data(),configuration.Data(),bdtCut));
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAcc_%s_%s_%s_%g_%s_%s_tag.C",  name.Data(),finalState.Data(),configuration.Data(),bdtCut));
    }
    else {
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAcc_%s_%s_%s_%g_%s_%s_tot.eps",name.Data(),finalState.Data(),configuration.Data(),bdtCut));
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAcc_%s_%s_%s_%g_%s_%s_tot.pdf",name.Data(),finalState.Data(),configuration.Data(),bdtCut));
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAcc_%s_%s_%s_%g_%s_%s_tot.png",name.Data(),finalState.Data(),configuration.Data(),bdtCut));
      c1->SaveAs(Form("${B2HH_OUT}/AccSignal/plots/fitForAcc_%s_%s_%s_%g_%s_%s_tot.C",  name.Data(),finalState.Data(),configuration.Data(),bdtCut));
    }
  }
  */
  TF1 * fU;
  if(dataFlag)
    fU = new TF1("f_data_accU","TMath::Max(0.,[0]*(1 + [1]*tanh([2]*(x-[3])) + [4]*tanh([5]*(x-[6]) + [7]*(x-[6])**2 + [8]*(x-[6])**3 ) ) )*(1+(x>[10])*[9]*(x-[10])*(x-[10]))",accSignal_cuts::minTimeFit, accSignal_cuts::maxTimeFit);
  else
    fU = new TF1(Form("f_%s_%s_accU",name.Data(),finalState.Data()),"TMath::Max(0.,[0]*(1 + [1]*tanh([2]*(x-[3])) + [4]*tanh([5]*(x-[6]) + [7]*(x-[6])**2 + [8]*(x-[6])**3 ) ) )*(1+(x>[10])*[9]*(x-[10])*(x-[10]))",accSignal_cuts::minTimeFit, accSignal_cuts::maxTimeFit);

  p0->setVal(1./pdfIntegral->getVal());
  fU->SetParameter(0,p0->getVal());
  fU->SetParameter(1,p1->getVal());
  fU->SetParameter(2,p2->getVal());
  fU->SetParameter(3,p3->getVal());
  fU->SetParameter(4,p4->getVal());
  fU->SetParameter(5,p5->getVal());
  fU->SetParameter(6,p6->getVal());
  fU->SetParameter(7,p7->getVal());
  fU->SetParameter(8,p8->getVal());
  fU->SetParameter(9,p9->getVal());
  fU->SetParameter(10,p10->getVal());
  Double_t funcMax = fU->GetMaximum();
  fU->SetParameter(0,p0->getVal()/funcMax);

  outFile->WriteTObject(fU,"","Overwrite");
  outFile->Close();

  return 0;
}
