#include <iostream>
#include <vector>

#include "TChain.h"
#include "TString.h"
#include "TH1D.h"
#include "TF1.h"
#include "RooMultiVarGaussian.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "TMatrixDSym.h"
#include "RooArgList.h"
#include <optionParser.h>
#include <expandFileName.h>
using namespace std;
using namespace RooFit;

  //int averageSigmaT(){
Int_t main(Int_t argc, Char_t * argv[]){

  TString help = argv[1];
  if(help =="-h" || help == "--help") {
    printf("Usage of resolution:\n");
    printf("  ./resolution [options]\n");
    printf("Options:\n");
    printf("  -n <bdtName>    : BDT name (use NONE for Jpsi)\n");
    printf("  -b <bdtCut>     : cut on BDT (default = NONE)\n");
    printf("  -m <magnet>     : magnet polarity ([Up,Down,Tot], default = Tot)\n");
    printf("  -y <year>       : year of data taking [2015,2016,2017,2018, 201516,20151618,Tot]\n");
    printf("  -M <fit model>  : resolution dependence on decay-time error [pol1,pol2,pol3,pol4] \n");
    return 0;
  }

  TString bdtName       = getOption(argc,argv,"-n","NONE");
  TString bdtCut        = getOption(argc,argv,"-b","NONE");
  TString magnet        = getOption(argc,argv,"-m","Tot");
  TString year          = getOption(argc,argv,"-y","");
  TString fitModel      = getOption(argc,argv,"-M","");


  TString nfin_b2hh = Form("${B2HH_OUT}/Reduce/b2hh_%s_%s_%s_%s.root/b2hh",
			   bdtName.Data(),bdtCut.Data(),
			   year.Data(),magnet.Data());
  
  TString nfin_params_path = "${B2HH_OUT}/resT/params";
  TString nfin_params_bskk_MC  = Form("%s/paramsRes_MCw_bskk_kk%s_%s_%s_%s.txt",
				      nfin_params_path.Data(),
				      (bdtName=="NONE")?"":Form("_%s_%s",bdtName.Data(),bdtCut.Data()),
				      year.Data(),magnet.Data(),fitModel.Data());
  expandFileName::expandFileName(nfin_params_bskk_MC);

  TString Jpsi_year = year;
  if (year == "201516") Jpsi_year = "2016";
  if (year == "2017s29r2p2") Jpsi_year = "2017";
  
  TString nfin_params_Jpsi_MC  = Form("%s/paramsRes_MC_Jpsi_%s_%s_%s.txt",
				      nfin_params_path.Data(),
				      Jpsi_year.Data(),magnet.Data(),fitModel.Data());
  expandFileName::expandFileName(nfin_params_Jpsi_MC);

  TString nfin_params_Jpsi_data= Form("%s/paramsRes_dataw_Jpsi_%s_%s_%s.txt",
				      nfin_params_path.Data(),
				      Jpsi_year.Data(),magnet.Data(),fitModel.Data());
  expandFileName::expandFileName(nfin_params_Jpsi_data);

  
  RooArgSet params_MC_Jpsi;
  RooRealVar roo_p0_MC_Jpsi("p0","p0", 0.040, "ps"); params_MC_Jpsi.add(roo_p0_MC_Jpsi);
  RooRealVar roo_p1_MC_Jpsi("p1","p1", 0.000, "ps"); params_MC_Jpsi.add(roo_p1_MC_Jpsi);
  params_MC_Jpsi.readFromFile(nfin_params_Jpsi_MC);
  params_MC_Jpsi.Print("v");
  Double_t p0_MC_Jpsi = roo_p0_MC_Jpsi.getVal(), p0_MC_Jpsi_err = roo_p0_MC_Jpsi.getError();
  Double_t p1_MC_Jpsi = roo_p1_MC_Jpsi.getVal(), p1_MC_Jpsi_err = roo_p1_MC_Jpsi.getError();

  RooArgSet params_data_Jpsi;
  RooRealVar roo_p0_data_Jpsi("p0","p0", 0.040, "ps");   params_data_Jpsi.add(roo_p0_data_Jpsi);
  RooRealVar roo_p1_data_Jpsi("p1","p1", 0.000, "");     params_data_Jpsi.add(roo_p1_data_Jpsi);
  RooRealVar roo_q0_data_Jpsi("mm0","mm0", 0.000, "ps");   params_data_Jpsi.add(roo_q0_data_Jpsi);
  RooRealVar roo_q1_data_Jpsi("mm1","mm1", 0.000, "");     params_data_Jpsi.add(roo_q1_data_Jpsi);
  RooRealVar roo_q2_data_Jpsi("mm2","mm2", 0.000, "1/ps"); params_data_Jpsi.add(roo_q2_data_Jpsi);
  params_data_Jpsi.readFromFile(nfin_params_Jpsi_data);
  params_data_Jpsi.Print("v");
  Double_t p0_data_Jpsi = roo_p0_data_Jpsi.getVal(), p0_data_Jpsi_err = roo_p0_data_Jpsi.getError();
  Double_t p1_data_Jpsi = roo_p1_data_Jpsi.getVal(), p1_data_Jpsi_err = roo_p1_data_Jpsi.getError();
  Double_t q0 = roo_q0_data_Jpsi.getVal(), q0_err = roo_q0_data_Jpsi.getError(); 
  Double_t q1 = roo_q1_data_Jpsi.getVal(), q1_err = roo_q1_data_Jpsi.getError(); 
  Double_t q2 = roo_q2_data_Jpsi.getVal(), q2_err = roo_q2_data_Jpsi.getError(); 
  
  RooArgSet params_MC_Bs;
  RooRealVar roo_p0_MC_Bs("p0","p0", 0.040, "ps");   params_MC_Bs.add(roo_p0_MC_Bs); 
  RooRealVar roo_p1_MC_Bs("p1","p1", 0.0, "");       params_MC_Bs.add(roo_p1_MC_Bs); 
  RooRealVar roo_f_MC_Bs("f1","f1", 0.0, "");        params_MC_Bs.add(roo_f_MC_Bs); 
  RooRealVar roo_C_MC_Bs("q0","q0", 0.0, "");        params_MC_Bs.add(roo_C_MC_Bs); 
  params_MC_Bs.readFromFile(nfin_params_bskk_MC);
  params_MC_Bs.Print("v");

  Double_t p0_MC_Bs = roo_p0_MC_Bs.getVal(), p0_MC_Bs_err = roo_p0_MC_Bs.getError();
  Double_t p1_MC_Bs = roo_p1_MC_Bs.getVal(), p1_MC_Bs_err = roo_p1_MC_Bs.getError();
  Double_t f_MC_Bs = roo_f_MC_Bs.getVal(), f_MC_Bs_err = roo_f_MC_Bs.getError();
  Double_t C_MC_Bs = roo_C_MC_Bs.getVal(), C_MC_Bs_err = roo_C_MC_Bs.getError();
  //  vector<TString> nfins = {"$B2HH_HOME/data/reduced/b2hh_KK_0.04_2017_Tot.root/b2hh"};
  Int_t nExp = 10000;
  Int_t CandPerExp = 4000;


  Double_t deltaM = 17.749;
  TChain c("ntp");
  c.Add(nfin_b2hh);
  Double_t tauErr=0.;
  Double_t count=0.;
  Double_t D=0., MU=0;
  Double_t mass=0.;
  Int_t p = 0;
  c.SetBranchStatus("*", 0);
  c.SetBranchStatus("timeErr", 1);
  c.SetBranchAddress("timeErr", &tauErr);
  c.SetBranchStatus("mass",1);
  c.SetBranchAddress("mass", &mass);
  c.SetBranchStatus("p",1);
  c.SetBranchAddress("p", &p);
  
  Int_t nentries = c.GetEntries();

  auto getD = [deltaM](Double_t sigma){
    return exp(-deltaM*deltaM*sigma*sigma/2.);
  };
  auto getSigmaEff = [deltaM](Double_t DD){
    return sqrt(-2*log(DD))/deltaM;
  };
  auto calibErr = [](Double_t p0, Double_t p1, Double_t dt){
    return p0+p1*(dt-0.04);
  };
  auto getMU = [q0, q1, q2](Double_t dt){
    return q0+q1*(dt-0.04)+q2*(dt-0.04)*(dt-0.04);
  };

  TH1D h_tauErr("h_tauErr", "h_tauErr; tauErr [ps]; Candidates", 200, 0,0.1);
  for (Int_t i=0;i<nentries; ++i){
    c.GetEntry(i);
    if (p != 2)    continue;
    if (mass<5.33) continue;
    if (mass>5.45) continue;
    h_tauErr.Fill(tauErr);
    Double_t sigma1_MC_Bs    = calibErr(p0_MC_Bs, p1_MC_Bs, tauErr);
    Double_t sigma2_MC_Bs    = C_MC_Bs*sigma1_MC_Bs;
    Double_t D_MC_Bs_1       = getD(sigma1_MC_Bs);
    Double_t D_MC_Bs_2       = getD(sigma2_MC_Bs);
    Double_t D_MC_Bs         = f_MC_Bs*D_MC_Bs_1+(1-f_MC_Bs)*D_MC_Bs_2;
    Double_t sigma_MC_Bs     = getSigmaEff(D_MC_Bs);
    Double_t sigma_MC_Jpsi   = calibErr(p0_MC_Jpsi, p1_MC_Jpsi, tauErr);
    Double_t sigma_data_Jpsi = calibErr(p0_data_Jpsi, p1_data_Jpsi, tauErr);
    Double_t sigma_i         = sigma_MC_Bs*sigma_data_Jpsi/sigma_MC_Jpsi; 
    //    Double_t sigma_i         = sigma_MC_Bs;
    //    Double_t sigma_i         = sigma_MC_Jpsi; 

    D += getD(sigma_i);
    MU+= getMU(tauErr);
    
    count += 1.;
    //printf("dt: %g count %g D: %g sBsMC: %g sJpsiMC: %g sJpsiData: %g\n",tauErr,  count,  sigma_i,  sigma_MC_Bs, sigma_data_Jpsi, sigma_MC_Jpsi);
  }
  Double_t Dmean = D/count;
  Double_t MUmean= MU/count;
  Double_t sigma_eff_tot = getSigmaEff(Dmean);
  printf("sigma eff tot = %g fs\n", sigma_eff_tot*1000);
  printf("mean %g fs\n", MUmean*1000);
  return 0;
  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////
  /*
  RooRealVar var_p0_MC_Jpsi("p0_MC_Jpsi", "p0_MC_Jpsi", p0_MC_Jpsi, p0_MC_Jpsi-5*p0_MC_Jpsi_err, p0_MC_Jpsi+5*p0_MC_Jpsi_err);
  RooRealVar  mu_p0_MC_Jpsi("mu_p0_MC_Jpsi", "mu_p0_MC_Jpsi", p0_MC_Jpsi, p0_MC_Jpsi-5*p0_MC_Jpsi_err, p0_MC_Jpsi+5*p0_MC_Jpsi_err);
  RooRealVar var_p1_MC_Jpsi("p1_MC_Jpsi", "p1_MC_Jpsi", p1_MC_Jpsi, p1_MC_Jpsi-5*p1_MC_Jpsi_err, p1_MC_Jpsi+5*p1_MC_Jpsi_err);
  RooRealVar  mu_p1_MC_Jpsi("mu_p1_MC_Jpsi", "mu_p1_MC_Jpsi", p1_MC_Jpsi, p1_MC_Jpsi-5*p1_MC_Jpsi_err, p1_MC_Jpsi+5*p1_MC_Jpsi_err);
  TMatrixDSym cov_MC_Jpsi(2);
  cov_MC_Jpsi(0,0) = p0_MC_Jpsi_err*p0_MC_Jpsi_err;
  cov_MC_Jpsi(0,1) = p0_MC_Jpsi_err*p1_MC_Jpsi_err*(-0.005);
  cov_MC_Jpsi(1,1) = p1_MC_Jpsi_err*p1_MC_Jpsi_err;
  RooMultiVarGaussian gaus_MC_Jpsi("gaus_MC_Jpsi", "gaus_MC_Jpsi", 
                                  RooArgList(var_p0_MC_Jpsi, var_p1_MC_Jpsi), 
                                  RooArgList(mu_p0_MC_Jpsi, mu_p1_MC_Jpsi), cov_MC_Jpsi);
  RooDataSet *values_MC_Jpsi = gaus_MC_Jpsi.generate(RooArgList(var_p0_MC_Jpsi, var_p1_MC_Jpsi), nExp);
  const RooArgSet* obs_MC_Jpsi = values_MC_Jpsi->get();
  RooRealVar * val_p0_MC_Jpsi = (RooRealVar*)obs_MC_Jpsi->find("p0_MC_Jpsi");
  RooRealVar * val_p1_MC_Jpsi = (RooRealVar*)obs_MC_Jpsi->find("p1_MC_Jpsi");

  RooRealVar var_p0_data_Jpsi("p0_data_Jpsi", "p0_data_Jpsi", p0_data_Jpsi, p0_data_Jpsi-5*p0_data_Jpsi_err, p0_data_Jpsi+5*p0_data_Jpsi_err);
  RooRealVar  mu_p0_data_Jpsi("mu_p0_data_Jpsi", "mu_p0_data_Jpsi", p0_data_Jpsi, p0_data_Jpsi-5*p0_data_Jpsi_err, p0_data_Jpsi+5*p0_data_Jpsi_err);
  RooRealVar var_p1_data_Jpsi("p1_data_Jpsi", "p1_data_Jpsi", p1_data_Jpsi, p1_data_Jpsi-5*p1_data_Jpsi_err, p1_data_Jpsi+5*p1_data_Jpsi_err);
  RooRealVar  mu_p1_data_Jpsi("mu_p1_data_Jpsi", "mu_p1_data_Jpsi", p1_data_Jpsi, p1_data_Jpsi-5*p1_data_Jpsi_err, p1_data_Jpsi+5*p1_data_Jpsi_err);
  TMatrixDSym cov_data_Jpsi(2);
  cov_data_Jpsi(0,0) = p0_data_Jpsi_err*p0_data_Jpsi_err;
  cov_data_Jpsi(0,1) = p0_data_Jpsi_err*p1_data_Jpsi_err*0.031;
  cov_data_Jpsi(1,1) = p1_data_Jpsi_err*p1_data_Jpsi_err;
  RooMultiVarGaussian gaus_data_Jpsi("gaus_data_Jpsi", "gaus_data_Jpsi", RooArgList(var_p0_data_Jpsi, var_p1_data_Jpsi), RooArgList(mu_p0_data_Jpsi, mu_p1_data_Jpsi), cov_data_Jpsi);
  RooDataSet *values_data_Jpsi = gaus_data_Jpsi.generate(RooArgList(var_p0_data_Jpsi, var_p1_data_Jpsi), nExp);
  const RooArgSet* obs_data_Jpsi = values_data_Jpsi->get();
  RooRealVar * val_p0_data_Jpsi = (RooRealVar*)obs_data_Jpsi->find("p0_data_Jpsi");
  RooRealVar * val_p1_data_Jpsi = (RooRealVar*)obs_data_Jpsi->find("p1_data_Jpsi");
  
  RooRealVar var_p0_MC_Bs("p0_MC_Bs", "p0_MC_Bs", p0_MC_Bs, p0_MC_Bs-5*p0_MC_Bs_err, p0_MC_Bs+5*p0_MC_Bs_err);
  RooRealVar  mu_p0_MC_Bs("mu_p0_MC_Bs", "mu_p0_MC_Bs", p0_MC_Bs, p0_MC_Bs-5*p0_MC_Bs_err, p0_MC_Bs+5*p0_MC_Bs_err);
  RooRealVar var_p1_MC_Bs("p1_MC_Bs", "p1_MC_Bs", p1_MC_Bs, p1_MC_Bs-5*p1_MC_Bs_err, p1_MC_Bs+5*p1_MC_Bs_err);
  RooRealVar  mu_p1_MC_Bs("mu_p1_MC_Bs", "mu_p1_MC_Bs", p1_MC_Bs, p1_MC_Bs-5*p1_MC_Bs_err, p1_MC_Bs+5*p1_MC_Bs_err);
  RooRealVar var_f_MC_Bs("f_MC_Bs", "f_MC_Bs", f_MC_Bs, f_MC_Bs-5*f_MC_Bs_err, f_MC_Bs+5*f_MC_Bs_err);
  RooRealVar  mu_f_MC_Bs("mu_f_MC_Bs", "mu_f_MC_Bs", f_MC_Bs, f_MC_Bs-5*f_MC_Bs_err, f_MC_Bs+5*f_MC_Bs_err);
  RooRealVar var_C_MC_Bs("C_MC_Bs", "C_MC_Bs", C_MC_Bs, C_MC_Bs-5*C_MC_Bs_err, C_MC_Bs+5*C_MC_Bs_err);
  RooRealVar  mu_C_MC_Bs("mu_C_MC_Bs", "mu_C_MC_Bs", C_MC_Bs, C_MC_Bs-5*C_MC_Bs_err, C_MC_Bs+5*C_MC_Bs_err);
  TMatrixDSym cov_MC_Bs(4);
  cov_MC_Bs(0,0) = p0_MC_Bs_err*p0_MC_Bs_err;
  cov_MC_Bs(0,1) = p0_MC_Bs_err*p1_MC_Bs_err*0.709;
  cov_MC_Bs(0,2) = p0_MC_Bs_err*f_MC_Bs*0.607;
  cov_MC_Bs(0,3) = p0_MC_Bs_err*C_MC_Bs*0.409;
  cov_MC_Bs(1,1) = p1_MC_Bs_err*p1_MC_Bs_err;
  cov_MC_Bs(1,2) = p1_MC_Bs_err*f_MC_Bs*0.246;
  cov_MC_Bs(1,3) = p1_MC_Bs_err*C_MC_Bs*0.174;
  cov_MC_Bs(2,2) = f_MC_Bs*f_MC_Bs;
  cov_MC_Bs(2,2) = f_MC_Bs*C_MC_Bs*0.797;
  cov_MC_Bs(3,3) = C_MC_Bs*C_MC_Bs;
  RooMultiVarGaussian gaus_MC_Bs("gaus_MC_Bs", "gaus_MC_Bs", RooArgList(var_p0_MC_Bs, var_p1_MC_Bs, var_f_MC_Bs, var_C_MC_Bs), RooArgList(mu_p0_MC_Bs, mu_p1_MC_Bs, mu_f_MC_Bs, mu_C_MC_Bs), cov_MC_Bs);
  RooDataSet *values_MC_Bs = gaus_MC_Bs.generate(RooArgList(var_p0_MC_Bs, var_p1_MC_Bs, var_f_MC_Bs, var_C_MC_Bs), nExp);
  const RooArgSet* obs_MC_Bs = values_MC_Bs->get();
  RooRealVar * val_p0_MC_Bs = (RooRealVar*)obs_MC_Bs->find("p0_MC_Bs");
  RooRealVar * val_p1_MC_Bs = (RooRealVar*)obs_MC_Bs->find("p1_MC_Bs");
  RooRealVar * val_f_MC_Bs  = (RooRealVar*)obs_MC_Bs->find("f_MC_Bs");
  RooRealVar * val_C_MC_Bs  = (RooRealVar*)obs_MC_Bs->find("C_MC_Bs");
  
  h_tauErr.Print();
  TH1D * h_toy_sigmaEff = new TH1D("h_toy_sigmaEff", "h_toy_sigmaEff; #sigma_t [fs]", 100, 40, 44);
  for (int iExp=0; iExp<nExp; ++iExp){
    printf("\r Exp: %d", iExp);
    Double_t tmp_D=0;
    Double_t tmp_count=0;
    values_MC_Jpsi->get(iExp);
    values_data_Jpsi->get(iExp);
    values_MC_Bs->get(iExp);
    Double_t tmp_p0_MC_Jpsi = val_p0_MC_Jpsi->getVal();
    Double_t tmp_p1_MC_Jpsi = val_p1_MC_Jpsi->getVal();
    Double_t tmp_p0_data_Jpsi = val_p0_data_Jpsi->getVal();
    Double_t tmp_p1_data_Jpsi = val_p1_data_Jpsi->getVal();
    Double_t tmp_p0_MC_Bs = val_p0_MC_Bs->getVal();
    Double_t tmp_p1_MC_Bs = val_p1_MC_Bs->getVal();
    Double_t tmp_f_MC_Bs = val_f_MC_Bs->getVal();
    Double_t tmp_C_MC_Bs = val_C_MC_Bs->getVal();

    for (int jCand=0; jCand<CandPerExp; ++jCand){
      Double_t tmp_tauErr = h_tauErr.GetRandom();
      Double_t sigma1_MC_Bs = calibErr(tmp_p0_MC_Bs, tmp_p1_MC_Bs, tmp_tauErr);
      Double_t sigma2_MC_Bs = tmp_C_MC_Bs*sigma1_MC_Bs;
      Double_t D_MC_Bs_1 = getD(sigma1_MC_Bs);
      Double_t D_MC_Bs_2 = getD(sigma2_MC_Bs);
      Double_t D_MC_Bs = tmp_f_MC_Bs*D_MC_Bs_1+(1-tmp_f_MC_Bs)*D_MC_Bs_2;
      Double_t sigma_MC_Bs = getSigmaEff(D_MC_Bs);
      Double_t sigma_MC_Jpsi = calibErr(tmp_p0_MC_Jpsi, tmp_p1_MC_Jpsi, tmp_tauErr);
      Double_t sigma_data_Jpsi = calibErr(tmp_p0_data_Jpsi, tmp_p1_data_Jpsi, tmp_tauErr);
      Double_t sigma_i = sigma_MC_Bs*sigma_data_Jpsi/sigma_MC_Jpsi;
      tmp_D+= getD(sigma_i);
      tmp_count += 1.;
    }
    Double_t tmp_Dmean = tmp_D/tmp_count;
    Double_t tmp_sigma_eff_tot = getSigmaEff(tmp_Dmean);
    h_toy_sigmaEff->Fill(tmp_sigma_eff_tot*1000);
  }
  h_toy_sigmaEff->Draw();
  printf("\nsigma eff tot = %g +/- %g fs\n", h_toy_sigmaEff->GetMean(), h_toy_sigmaEff->GetStdDev());
  */
  return 1;
}


  /*  
  //vector<TString> nfins;
  if (year == "2015" || year == "2016" || year == "201516"){
    p0_MC_Jpsi = 0.036377, p0_MC_Jpsi_err = 0.000017;
    p1_MC_Jpsi = 0.8851, p1_MC_Jpsi_err = 0.0013;
    p0_data_Jpsi = 0.038660, p0_data_Jpsi_err = 0.000044;
    p1_data_Jpsi = 0.9152, p1_data_Jpsi_err = 0.0035;
    p0_MC_Bs = 0.040521, p0_MC_Bs_err = 0.000058;
    p1_MC_Bs = 0.9648, p1_MC_Bs_err = 0.0034;
    f_MC_Bs = 0.97287, f_MC_Bs_err = 0.00089;
    C_MC_Bs = 2.665, C_MC_Bs_err = 0.027;
    q0 = -0.004439, q1 = -0.105, q2 = 5.67;
    // nfins = {"$storage_Bs2KK_MC/bskk_2016_Up.root/b2hh",
    //          "$storage_Bs2KK_MC/bskk_2016_Down.root/b2hh"};
    //nfins = {"$B2HH_HOME/FitTotal/reduced/b2hh_KK_0.04_201516_Tot.root/b2hh"};
    //nfins = {"$B2HH_HOME/FitTotal/reduced/b2hh_KK_0.04_201516_Tot.root/b2hh"};
  } else if (year == "2017s29r2p2"){
    p0_MC_Jpsi = 0.036290, p0_MC_Jpsi_err = 0.000017;
    p1_MC_Jpsi = 0.8830, p1_MC_Jpsi_err = 0.0013;
    p0_data_Jpsi = 0.038868, p0_data_Jpsi_err = 0.000037;
    p1_data_Jpsi = 0.9293, p1_data_Jpsi_err = 0.0030;
    p0_MC_Bs = 0.040400, p0_MC_Bs_err = 0.000033;
    p1_MC_Bs = 0.9648, p1_MC_Bs_err = 0.0019;
    f_MC_Bs = 0.97259, f_MC_Bs_err = 0.00052;
    C_MC_Bs = 2.658, C_MC_Bs_err = 0.016;
    q0 = -0.00538, q1 = -0.121, q2 = 6.1;
    // nfins = {"$storage_Bs2KK_MC/bskk_2017_Up.root/b2hh",
    //          "$storage_Bs2KK_MC/bskk_2017_Down.root/b2hh"};
    //nfins = {"$B2HH_HOME/FitTotal/reduced/b2hh_KK_0.04_2017_Tot.root/b2hh"};
  } else if (year == "2018"){
    p0_MC_Jpsi = 0.036329, p0_MC_Jpsi_err = 0.000017;
    p1_MC_Jpsi = 0.8829, p1_MC_Jpsi_err = 0.0013;
    p0_data_Jpsi = 0.038709, p0_data_Jpsi_err = 0.000038;
    p1_data_Jpsi = 0.9186, p1_data_Jpsi_err = 0.0031;
    p0_MC_Bs = 0.040316, p0_MC_Bs_err = 0.000036;
    p1_MC_Bs = 0.9588, p1_MC_Bs_err = 0.0021;
    f_MC_Bs = 0.97075, f_MC_Bs_err = 0.00059;
    C_MC_Bs = 2.603, C_MC_Bs_err = 0.016;
    q0 = -0.0044, q1 = -0.125, q2 = 5.8;
    // nfins = {"$storage_Bs2KK_MC/bskk_2018_Up.root/b2hh",
    //          "$storage_Bs2KK_MC/bskk_2018_Down.root/b2hh"};
    //nfins = {"$B2HH_HOME/FitTotal/reduced/b2hh_KK_0.04_2018_Tot.root/b2hh"};
  } else return 0;
  */
