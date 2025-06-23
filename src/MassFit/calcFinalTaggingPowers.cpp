#include <iostream>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include <map>
#include <vector>
using namespace std;
Double_t getOmega(Double_t &eta, Double_t &p0, Double_t &p1, Double_t &etaHat)
{

    Double_t w = p0 + p1 * (eta - etaHat);
    return w;
}
void combineTaggers(Int_t &qTot, Double_t &etaTot,
                    std::vector<Int_t> &q, std::vector<Double_t> &eta,
                    std::vector<Double_t> &p0, std::vector<Double_t> &p1, 
                    std::vector<Double_t> &etaHat) {

  qTot = 0; etaTot = 0;
  Double_t pB = 1, pBbar = 1, w = 0;

  ULong64_t nTaggers = q.size();
  if(eta.size() != nTaggers || p0.size() != nTaggers ||
     p1.size()  != nTaggers || etaHat.size() != nTaggers) { printf("Some input has wrong size\n"); return; }

  for(ULong64_t i = 0; i < nTaggers; ++i) {

    w = getOmega(eta[i],p0[i],p1[i],etaHat[i]);
    pB    *= (q[i] == 1)*(1-w) + (q[i] ==-1)*w + (q[i] == 0)*0.5;
    pBbar *= (q[i] ==-1)*(1-w) + (q[i] == 1)*w + (q[i] == 0)*0.5;

  }

  pB = pB/(pB+pBbar);

  if     (pB == 0.5) { etaTot = 0.5;  qTot =  0; }
  else if(pB >  0.5) { etaTot = 1-pB; qTot =  1; }
  else               { etaTot = pB;   qTot = -1; }

}




void doCalcFinalTaggingPowers(TString nfinTag,
                              map<TString, vector<Double_t>> taggigCalibParams)
{
    printf("++++++++++++  %s +++++++++++\n", nfinTag.Data());
    TString nfin = "${B2HH_OUT}/Reduce/b2hh_"+nfinTag+".root";
    TFile *fin = TFile::Open(nfin , "READ");
    TTree *tin = (TTree*)fin->Get("b2hh");
    
    Double_t minMass = 0;
    Double_t maxMass = 0;
    
    Int_t p=0, qOS=0, qSS=0;
    Double_t etaOS=0, etaSS=0;
    Double_t mass=0;
    
    TString nTagSS = "";
    if      (nfin.Contains("b2hh_KK")){
        nTagSS = "SSk";
        minMass = 5.33;
        maxMass = 5.45;
    }   
    else if (nfin.Contains("b2hh_PIPI")){
        nTagSS = "SS";
        minMass = 5.23;
        maxMass = 5.32;
    } 
    
    tin->SetBranchStatus("*", 0);
    tin->SetBranchStatus("mass", 1);
    tin->SetBranchStatus("p", 1);
    tin->SetBranchStatus("qOS", 1);
    tin->SetBranchStatus("q"+nTagSS, 1);
    tin->SetBranchStatus("etaOS", 1);
    tin->SetBranchStatus("eta"+nTagSS, 1);

    tin->SetBranchAddress("mass", &mass);
    tin->SetBranchAddress("p", &p);
    tin->SetBranchAddress("qOS", &qOS);
    tin->SetBranchAddress("etaOS", &etaOS);
    tin->SetBranchAddress("q"+nTagSS, &qSS);
    tin->SetBranchAddress("eta"+nTagSS, &etaSS);

    Int_t nentries = tin->GetEntries();
    Double_t sumPowerOS=0., NpowerOS=0., NtaggedOS=0., sumOmegaOS=0.;
    Double_t sumPowerSS = 0., NpowerSS = 0., NtaggedSS=0., sumOmegaSS=0.;
    Double_t sumPowerTot = 0., NpowerTot = 0., NtaggedTot=0., sumOmegaTot=0.;  
    Double_t etaHatOS = taggigCalibParams[nfinTag+"_OS"][0];
    Double_t p0OS = taggigCalibParams[nfinTag + "_OS"][1];
    Double_t p1OS = taggigCalibParams[nfinTag + "_OS"][2];
    Double_t etaHatSS = taggigCalibParams[nfinTag + "_" + nTagSS][0];
    Double_t p0SS = taggigCalibParams[nfinTag + "_" + nTagSS][1];
    Double_t p1SS = taggigCalibParams[nfinTag + "_" + nTagSS][2];
    // printf("etaHatOS: %g, p0OS: %g, p1OS: %g\n", etaHatOS, p0OS, p1OS);
    // printf("etaHat%s: %g, p0%s: %g, p1%s: %g\n", nTagSS.Data(), etaHatSS,
        //    nTagSS.Data(), p0SS,
        //    nTagSS.Data(), p1SS);

    auto calibOStag = [etaHatOS, p0OS, p1OS](Double_t eta)
    {
        return p0OS + p1OS * (eta - etaHatOS);
    };
    auto calibSStag = [etaHatSS, p0SS, p1SS](Double_t eta)
    {
        return p0SS + p1SS * (eta - etaHatSS);
    };
    Double_t omegaOS = 0, omegaSS = 0;
    Double_t omegaTot = 0;
    Int_t qTot = 0;
    for (Int_t i = 0; i < nentries; ++i)
    {
        tin->GetEntry(i);
        if (abs(p)!=1) continue;
        if (mass>maxMass) continue;
        if (mass<minMass) continue;
        omegaOS = calibOStag(etaOS);
        omegaSS = calibSStag(etaSS);
        // omegaOS = etaOS;
        // omegaSS = etaSS;
        vector<Int_t> v_q = {qOS, qSS};
        vector<Double_t> v_omega = {etaOS, etaSS};
        vector<Double_t> v_p0 = {p0OS, p0SS};
        vector<Double_t> v_p1 = {p1OS, p1SS};
        vector<Double_t> v_etaHat = {etaHatOS, etaHatSS};

        combineTaggers(qTot, omegaTot,
                       v_q, v_omega,
                       v_p0, v_p1, v_etaHat);

        sumPowerOS += abs(qOS) * (1 - 2 * omegaOS) * (1 - 2 * omegaOS);
        sumPowerSS += abs(qSS) * (1 - 2 * omegaSS) * (1 - 2 * omegaSS);
        sumPowerTot += abs(qTot) * (1 - 2 * omegaTot) * (1 - 2 * omegaTot);
	sumOmegaOS += abs(qOS)*omegaOS;
	sumOmegaSS += abs(qSS)*omegaSS;
	sumOmegaTot += abs(qTot)*omegaTot;
	NtaggedOS += abs(qOS);
	NtaggedSS += abs(qSS);
	NtaggedTot += abs(qTot);
        NpowerOS += 1;
        NpowerSS += 1;
        NpowerTot += 1;

    }
    Double_t powerOS = sumPowerOS / NpowerOS;
    Double_t powerSS = sumPowerSS / NpowerSS;
    Double_t powerTot = sumPowerTot / NpowerTot;
    Double_t effOS = NtaggedOS / NpowerOS;
    Double_t effSS = NtaggedSS / NpowerSS;
    Double_t effTot = NtaggedTot / NpowerTot;
    Double_t avgOmegaOS = sumOmegaOS / NtaggedOS;
    Double_t avgOmegaSS = sumOmegaSS / NtaggedSS;
    Double_t avgOmegaTot = sumOmegaTot / NtaggedTot;
    //Double_t avgOmegaOS = sumOmegaOS / NpowerOS;
    //Double_t avgOmegaSS = sumOmegaSS / NpowerSS;
    //Double_t avgOmegaTot = sumOmegaTot / NpowerTot;

    printf("power OS : %.1f %%\n", powerOS*100);
    printf("power %s : %.1f %%\n", nTagSS.Data(), powerSS * 100);
    printf("power Tot: %.1f %%\n", powerTot * 100);

    printf("effOS : %.3f \n", effOS);
    printf("effSS : %.3f \n", effSS);
    printf("effTot: %.3f \n", effTot);

    printf("avgOmegaOS : %.3f -- %.3f \n", avgOmegaOS, 0.5*(1-sqrt(powerOS/effOS)));
    printf("avgOmegaSS : %.3f -- %.3f\n", avgOmegaSS, 0.5*(1-sqrt(powerSS/effSS)));
    printf("avgOmegaTot: %.3f -- %.3f \n", avgOmegaTot, 0.5*(1-sqrt(powerTot/effTot)));

    fin->Close();

}

Int_t calcFinalTaggingPowers(){
    map<TString, vector<Double_t>> taggigCalibParams = {
      {"KK_0.1_201516_Tot_OS", {0.37, 0.4029, 0.848}},
      {"KK_0.1_2017s29r2p2_Tot_OS", {0.37, 0.3990, 0.817}},
      {"KK_0.1_2018_Tot_OS", {0.37, 0.3950, 0.834}},

      {"KK_0.1_201516_Tot_SSk", {0.42645, 0.4370, 0.660}},
      {"KK_0.1_2017s29r2p2_Tot_SSk", {0.42645, 0.44500, 0.73000}},
      {"KK_0.1_2018_Tot_SSk", {0.42645, 0.43700, 0.78000}},

      {"PIPI_0.2_201516_Tot_OS", {0.37, 0.4041, 0.834}},
      {"PIPI_0.2_2017s29r2p2_Tot_OS", {0.37, 0.3974, 0.774}},
      {"PIPI_0.2_2018_Tot_OS", {0.37, 0.3966, 0.835}},
      
      {"PIPI_0.2_201516_Tot_SS", {0.44, 0.4364, 0.980}},
      {"PIPI_0.2_2017s29r2p2_Tot_SS", {0.44, 0.4391, 1.007}},
      {"PIPI_0.2_2018_Tot_SS", {0.44, 0.4390, 0.895}},
    };

    doCalcFinalTaggingPowers("PIPI_0.2_201516_Tot", taggigCalibParams);
    doCalcFinalTaggingPowers("PIPI_0.2_2017s29r2p2_Tot", taggigCalibParams);
    doCalcFinalTaggingPowers("PIPI_0.2_2018_Tot", taggigCalibParams);
    doCalcFinalTaggingPowers("KK_0.1_201516_Tot", taggigCalibParams);
    doCalcFinalTaggingPowers("KK_0.1_2017s29r2p2_Tot", taggigCalibParams);
    doCalcFinalTaggingPowers("KK_0.1_2018_Tot", taggigCalibParams);
    

    return 1;
}
