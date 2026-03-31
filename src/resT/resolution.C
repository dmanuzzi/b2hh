#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TF1.h"
#include "TH1D.h"
#include "TFitResult.h"
#include "makePull.C"
#include "TRandom3.h"
#include <vector>
#include <map>
#include "TPaveText.h"
#include "TROOT.h"
#include "TStyle.h"
#include <expandFileName.h>
#include <optionParser.h>

using namespace std;

Int_t main(Int_t argc, Char_t * argv[]) {

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of resolution:\n");
    printf("  ./resolution [options]\n");
    printf("Options:\n");
    printf("  -n <bdtName>    : BDT name (use NONE for Jpsi)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = NONE)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking [2015,2016,2017,2018, 201516,20151618,Tot]\n");
    printf("  -d <decay>      : decay under study [Jpsi,bskk_kk,bspipi_pipi] (Y1S not implemented at the moment)\n");
    printf("  -D <DataType>   : [MC, data]\n");
    printf("  -P <PIDsel>     : include this to add PID selection\n");
    printf("  -w <weightName> : 'NONE' to avoid weights\n");
    
    return 0;
  }
  TString bdtName       = getOption(argc,argv,"-n","NONE");
  TString bdtCut        = getOption(argc,argv,"-b","NONE");
  TString magnet        = getOption(argc,argv,"-m","Tot");
  TString year          = getOption(argc,argv,"-y","");
  TString decay         = getOption(argc,argv,"-d","");
  TString dataType      = getOption(argc,argv,"-D","");
  TString weightName    = getOption(argc,argv,"-w","NONE");
  TString PIDsel        = getOption(argc,argv,"-P","NONE");

  gROOT->SetStyle("Plain");
  //  Bool_t isMC   = tag.Contains("MC");

  Bool_t isMC   = dataType.Contains("MC");
  Bool_t isJpsi = (decay == "Jpsi");
  Bool_t isY1S  = (decay == "Y1S");
  Bool_t isB2HH = (!isJpsi && !isY1S);
  Bool_t isWeighted = (weightName!="NONE");
  Bool_t doPIDsel= (PIDsel!="NONE");
  TString tag = Form("%s%s_%s%s_%s_%s",
		     dataType.Data(),(isWeighted?"w":""),
		     decay.Data(),
		     (bdtName=="NONE")?"":Form("_%s_%s",bdtName.Data(),bdtCut.Data()),
		     year.Data(),magnet.Data());
    
  Double_t deltaTauMin =-0.5;
  Double_t deltaTauMax = 0.5;
  Double_t minVal  = +0.01;
  Double_t maxVal  = +0.10;
  Double_t Mmin = 0., Mmax= 0.;
  
  if      (isJpsi) { Mmin = 2.99, Mmax= 3.2; }
  else if (isY1S)  { Mmin = 9.00, Mmax= 9.8; }
  else if (isB2HH) { Mmin = 5.00, Mmax= 6.2; }

  TChain * inChain = new TChain("chain_"+tag);
  if (isJpsi){
    if (isMC){
      TString _path = "/ceph-data/lhcb_g/users/manuzzi/B2HH/MC/Jpsi2mumuPrompt";
      inChain->Add(_path+"/Jpsi_MC_"+year+"_MagUp_reduced.root/ntp");
      inChain->Add(_path+"/Jpsi_MC_"+year+"_MagDw_reduced.root/ntp");
    } else {
      TString _path = "/home/ceph/manuzzi/B2HH/resT/sWeights/plots";
      inChain->Add(_path+"/Jpsi_"+dataType+"_"+year+"_polBKG.root/merged");
    }
  } else {
    TString _path = "${B2HH_OUT}/AccSignal/selectedMC";
    TString _nfin = _path+"/"+decay+"_"+bdtName+"_"+bdtCut+"_"+year+"_"+magnet+".root/b2hh";
    inChain->Add(_nfin);
  }

  inChain->Print();
  Double_t tau=0, trueTau=0., tauErr=0, Nsig_sw=1.;
  Double_t head_M=0, head_TRUEPT=0., head_PT=0;
  Int_t head_MC_MOTHER_ID=0;
  inChain->SetBranchStatus("*",0);
  if (isJpsi || isY1S){
    inChain->SetBranchStatus("Jpsi_TAU",    1);
    inChain->SetBranchStatus("Jpsi_TAUERR", 1);
    inChain->SetBranchStatus("Jpsi_MM",     1);
    inChain->SetBranchAddress("Jpsi_TAU",    &tau);
    inChain->SetBranchAddress("Jpsi_TAUERR", &tauErr);
    inChain->SetBranchAddress("Jpsi_MM",     &head_M);
    
    if (isMC){
      inChain->SetBranchStatus("Jpsi_TRUEPT", 1);
      inChain->SetBranchStatus("Jpsi_MC_MOTHER_ID", 1);
      inChain->SetBranchAddress("Jpsi_TRUEPT", &head_TRUEPT);
      inChain->SetBranchAddress("Jpsi_MC_MOTHER_ID", &head_MC_MOTHER_ID);    
    }
  }

  //  Int_t fromBc=-1;
  if (isB2HH){
    inChain->SetBranchStatus("time"   , 1);
    inChain->SetBranchStatus("timeErr", 1);
    inChain->SetBranchStatus("mass"  , 1);
    inChain->SetBranchStatus("bPT"     , 1);
    
    inChain->SetBranchAddress("time"   , &tau);
    inChain->SetBranchAddress("timeErr", &tauErr);
    inChain->SetBranchAddress("mass"  , &head_M);
    inChain->SetBranchAddress("bPT"     , &head_PT);
    
    if (isMC){
      inChain->SetBranchStatus("trueTau", 1);
      //      inChain->SetBranchStatus("fromBc" , 1);
      inChain->SetBranchAddress("trueTau", &trueTau);
      //      inChain->SetBranchAddress("fromBc" , &fromBc);
    } else return 0;
  }
  if (isWeighted){
    inChain->SetBranchStatus(weightName, 1);
    inChain->SetBranchAddress(weightName,    &Nsig_sw) ;
  }


  Long64_t nEntriesIN = inChain->GetEntries();
  const Int_t nBins = 26; 
  Double_t meanTot = 0, totTot = 0;
  vector<Double_t> meanTAU(nBins, 0.);
  vector<Double_t> mean(nBins, 0.);
  vector<Double_t> mean2(nBins, 0.);
  vector<Double_t> rms(nBins, 0.);
  vector<Double_t> rms2(nBins, 0.);
  vector<Double_t> tot(nBins, 0.);

  
  Int_t iBin = 0;
  TH1D * tauRes = new TH1D("tauRes_"+tag, "tauRes_"+tag, nBins,minVal,maxVal); tauRes->Sumw2();
  TH1D * hJpsiM = new TH1D("M_"+tag,    "M_"+tag+"; m(#mu^{+}#mu^{-}) [GeV]", 100, Mmin,   Mmax);
  TH1D * hTau   = new TH1D("Tau_"+tag,  "Tau_"+tag+"; #tau-#tau_{true} [ps]", 100, deltaTauMin,  deltaTauMax);
  TH1D * hTauE  = new TH1D("TauE_"+tag, "TauErr_"+tag+"; RMS_{#tau} [ps]",      100, minVal, maxVal);

  TFile * outFile = new TFile("${B2HH_OUT}/resT/tuples/"+tag+".root","RECREATE");
  Double_t timeErr=0., deltaTau=0., sWeight=1.;
  Double_t M=0., PT=0., TRUEPT=0.;
  Int_t MCMOTHERID=0;
  TTree * outTree = new TTree("ntp","ntp");
  outTree->Branch("timeErr",&timeErr,"timeErr/D");
  outTree->Branch("deltaTau",&deltaTau,"deltaTau/D");
  outTree->Branch("sWeight",&sWeight,"sWeight/D");
  outTree->Branch("M",&M,"M/D");
  outTree->Branch("PT",&PT,"PT/D");
  outTree->Branch("TRUEPT",&TRUEPT,"TRUEPT/D");
  outTree->Branch("MC_MOTHER_ID",&MCMOTHERID,"MC_MOTHER_ID/I");


  for(Int_t iEntry = 0; iEntry < nEntriesIN; iEntry++) {
    inChain->GetEntry(iEntry);
    tau = tau-trueTau;
    
    if (!isB2HH) {
      head_M = head_M/1000.;
      tauErr = tauErr*1000.;
      tau    = tau*1000.;
    }
    if (head_M < Mmin)     continue;
    if (head_M > Mmax)     continue;
    if (tauErr < minVal)   continue;
    if (tauErr > maxVal)   continue;
    if (tau < deltaTauMin) continue;
    if (tau > deltaTauMax) continue;


    hJpsiM->Fill(head_M, Nsig_sw);
    tauRes->Fill(tauErr, Nsig_sw);
    hTau  ->Fill(tau,    Nsig_sw);
    hTauE ->Fill(tauErr, Nsig_sw);
    iBin = tauRes->FindBin(tauErr) - 1;

    meanTot    += tauErr*Nsig_sw; 
    totTot     += 1*Nsig_sw;
    meanTAU[iBin] += tau*Nsig_sw;
    mean[iBin] += tauErr*Nsig_sw;
    rms[iBin]  += tau*Nsig_sw;
    //    mean2[iBin]+= tauErr*tauErr*Nsig_sw*Nsig_sw;
    //    rms2[iBin] += tau*tau*Nsig_sw*Nsig_sw;
    mean2[iBin]+= tauErr*tauErr*Nsig_sw;
    rms2[iBin] += tau*tau*Nsig_sw;
    tot[iBin]  += 1*Nsig_sw;

    timeErr    = tauErr; 
    deltaTau   = tau;
    sWeight    = Nsig_sw;
    M          = head_M;
    PT         = head_PT;
    TRUEPT     = head_TRUEPT;
    MCMOTHERID = head_MC_MOTHER_ID;
    outTree->Fill();
  }


  outFile->WriteTObject(outTree,"","Overwrite");
  outFile->Close();

  setStyle(tauRes,kBlue,2,1,3001,"#sigma_{#tau} (ps)","Normalizaed Units");

  setToZero(tauRes);

  meanTot /= totTot;
  TString nfout_stats = "${B2HH_OUT}/resT/stats/stats_"+tag+".txt";
  expandFileName::expandFileName(nfout_stats);
  FILE* fStats = fopen(nfout_stats.Data(), "a");
  fprintf(fStats, "********* %s ********* \n", tag.Data());
  fprintf(fStats, "totTot: %g \n meanTot: %g\n", totTot, meanTot);

  TF1 * f = nullptr;
  if (isY1S) f = new TF1("f","[0]+[1]*(x-[2])+[3]*(x-[2])*(x-[2])",minVal,maxVal);
  else       f = new TF1("f","[0]+[1]*(x-[2])",minVal,maxVal);
  //TF1 * f = new TF1("f","[0]+[1]*(x-[2])+[3]*(x-[2])**2+[4]*(x-[2])**3",minVal,maxVal);
  //TF1 * f = new TF1("f","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x",0,maxVal);
  f->SetParameter(0,0.229186);
  f->SetParameter(1,0.596504);
  f->FixParameter(2,0.04);
  f->SetParameter(3,-4.5);
  f->SetParameter(4,0.1);
  f->SetLineColor(kBlue);

  TGraphErrors * g = new TGraphErrors(nBins);
  TGraphErrors * gmean = new TGraphErrors(nBins);
  Double_t x = 0, y = 0, xErr = 0, yErr = 0;
  for(Int_t i = 0; i < nBins; i++) { 
    if(tot[i] != 0) {
      meanTAU[i] /= tot[i];
      mean[i] /= tot[i]; mean2[i] /= tot[i];
      rms[i] /= tot[i]; rms2[i] /= tot[i];
    }
    else {
      mean[i] = 0; mean2[i] = 0;
      rms[i]  = 0; rms2[i]  = 0;
    }

    x = mean[i]; 
    y = sqrt(rms2[i]-rms[i]*rms[i]); 
    xErr = sqrt(mean2[i]-mean[i]*mean[i])/sqrt(tot[i]-1);
    yErr = y/sqrt(2*tot[i]);
    double tauErr = y/sqrt(tot[i]);
    g->SetPoint(i,x,y);
    g->SetPointError(i,xErr,yErr);
    gmean->SetPoint(i, x, meanTAU[i]);
    gmean->SetPointError(i, xErr, tauErr);
    printf("%g %g %g %g\n",x,xErr,y,yErr);

  }

  TCanvas * cSF = new TCanvas("cSF_"+tag,"cSF_"+tag);
  cSF->cd();
  setStyle(cSF);

  g->SetMarkerStyle(22);  g->SetMarkerColor(kBlue); g->SetMarkerSize(1.2);
  setStyle(g,kBlue,2,1.2,3001,"#delta_{t} (ps)","RMS(t) (ps)");
  g->Fit(f,"S","",0.01,maxVal).Get()->Print("v");
  g->Draw("APE1");
  g->GetXaxis()->SetLimits(0, maxVal);
  //g->GetYaxis()->SetRangeUser(0, maxVal);
  g->Draw("APE1same");
  f->Draw("same");
  fprintf(fStats, "[0]+[1]*(x-[2]) ---> [0] = %g +/- %g;  [1] = %g +/- %g;  [2] = %g +/- %g;\n", 
	  f->GetParameter(0), f->GetParError(0), f->GetParameter(1), f->GetParError(1), f->GetParameter(2), f->GetParError(2));
  fclose(fStats);

  TPaveText* fit1Box = new TPaveText(gStyle->GetPadLeftMargin() + 0.06,
                                    0.85 - gStyle->GetPadTopMargin(),
                                    gStyle->GetPadLeftMargin() + 0.20,
                                    0.95 - gStyle->GetPadTopMargin(),
                                    "BRNDC");
  fit1Box->SetFillColor(0);
  fit1Box->SetTextAlign(12);
  fit1Box->SetBorderSize(0);
  fit1Box->SetTextFont(132);
  fit1Box->SetTextColor(1);
  fit1Box->SetTextSize(0.04);
  fit1Box->SetTextAlign(12);
  int toRound1 = floor(log10(f->GetParError(0)));
  int toRound2 = floor(log10(f->GetParError(1)));
  if (isY1S){
    int toRound3 = floor(log10(f->GetParError(3)));  
    fit1Box->AddText(Form("RMS(t) = %.*f + (%.*f)*(#delta_{t}-0.04) + (%.*f)*(#delta_{t}-0.04)^{2}  ps\n",
                          -toRound1, f->GetParameter(0),-toRound2, f->GetParameter(1),-toRound3, f->GetParameter(3)));
  } else {
    fit1Box->AddText(Form("RMS(t) = %.*f + %.*f*(#delta_{t}-0.04) ps\n",-toRound1, f->GetParameter(0),-toRound2, f->GetParameter(1)));  
  }
  fit1Box->Draw("same");

  Double_t maxScale = tauRes->GetMaximum();
  tauRes->Scale(g->GetYaxis()->GetXmax()*0.9/maxScale);
  //tauRes->Scale(maxVal*0.9/maxScale);
  tauRes->Draw("histsame"); 
  cSF->SaveAs("${B2HH_OUT}/resT/plots/"+tag+".png");
  cSF->SaveAs("${B2HH_OUT}/resT/plots/"+tag+".pdf");

  TCanvas *cM = new TCanvas("cM_"+tag, "cM_"+tag);
  hJpsiM->SetMarkerStyle(20);
  hJpsiM->SetMarkerColor(kBlack);
  hJpsiM->Draw("PE1");
  cM->SaveAs("${B2HH_OUT}/resT/plots/M_"+tag+".png");
  cM->SaveAs("${B2HH_OUT}/resT/plots/M_"+tag+".pdf");

  TCanvas *cTau = new TCanvas("cTau_"+tag, "cTau_"+tag);
  hTau->Draw("hist");
  cTau->SaveAs("${B2HH_OUT}/resT/plots/tau_"+tag+".png");
  cTau->SaveAs("${B2HH_OUT}/resT/plots/tau_"+tag+".pdf");
  TCanvas *cTauE = new TCanvas("cTauE_"+tag, "cTauE_"+tag);
  hTauE->Draw("hist");
  cTauE->SaveAs("${B2HH_OUT}/resT/plots/tauE_"+tag+".png");
  cTauE->SaveAs("${B2HH_OUT}/resT/plots/tauE_"+tag+".pdf");

  TCanvas *cTauMean = new TCanvas("cTauMean", "cTauMean");
  gmean->SetMarkerStyle(22);  gmean->SetMarkerColor(kRed); gmean->SetMarkerSize(1.2);
  setStyle(gmean,kRed,2,1.2,3001,"#delta_{t} (ps)","mean(t) (ps)");
  //gmean->SetTitle("gmean; #delta_{t} (ps); mean(t) (ps)");
  gmean->Draw("APLE1");
  gmean->SetMinimum(-0.01);
  gmean->SetMaximum(+0.01);
  gmean->Draw("APLE1same");
  
  TF1 * fTau = new TF1("fTau","[0]+[1]*(x-0.04)+[2]*(x-0.04)**2",0,maxVal);
  if (!isMC){
    fTau->SetParameter(0, -3.8927e-03);
    fTau->SetParameter(1, -8.3123e-02);
    fTau->SetParameter(2,  4.8226e+00);
  } else {
    fTau->SetParameter(0, 0.0);
    fTau->FixParameter(1, 0.0);
    fTau->FixParameter(2, 0.0);
  }
  gmean->Fit(fTau, "S", "", minVal, maxVal).Get()->Print("v");
  fTau->Draw("Lsame");

  TPaveText* fit2Box = new TPaveText(gStyle->GetPadLeftMargin() + 0.06,
                                    0.85 - gStyle->GetPadTopMargin(),
                                    gStyle->GetPadLeftMargin() + 0.20,
                                    0.95 - gStyle->GetPadTopMargin(),
                                    "BRNDC");
  fit2Box->SetFillColor(0);
  fit2Box->SetTextAlign(12);
  fit2Box->SetBorderSize(0);
  fit2Box->SetTextFont(132);
  fit2Box->SetTextColor(1);
  fit2Box->SetTextSize(0.04);
  fit2Box->SetTextAlign(12);
  if (isMC){
    int toRound_tmp = floor(log10(fTau->GetParError(0)));
    fit2Box->AddText(Form("mean(t) = %.*f #pm %.*f ps\n", -toRound_tmp, fTau->GetParameter(0), -toRound_tmp, fTau->GetParError(0)));
  } else {
    int toRound0_tmp = floor(log10(fTau->GetParError(0)));
    int toRound1_tmp = floor(log10(fTau->GetParError(1)));
    int toRound2_tmp = floor(log10(fTau->GetParError(2)));
    
    fit2Box->AddText(Form("mean(t) = %.*f + (%.*f)*(#delta_{t}-0.04)+(%.*f)*(#delta_{t}-0.04)^{2} ps\n",
                          -toRound0_tmp, fTau->GetParameter(0), 
                          -toRound1_tmp, fTau->GetParameter(1),
                          -toRound2_tmp, fTau->GetParameter(2)));
  }
  fit2Box->Draw("same");  
  cTauMean->SaveAs("${B2HH_OUT}/resT/plots/tauMean_"+tag+".png");
  cTauMean->SaveAs("${B2HH_OUT}/resT/plots/tauMean_"+tag+".pdf");

  TFile *fout = new TFile("${B2HH_OUT}/resT/plots/"+tag+".root", "RECREATE");
  fout->WriteTObject(cSF);
  fout->WriteTObject(cM);
  fout->WriteTObject(cTau);
  fout->WriteTObject(cTauE);
  fout->WriteTObject(cTauMean);

  fout->Print();
  fout->Close();
  return 1;
}


