void setMyStyle(TH1* h, Int_t col, Int_t markerStyle){
  h->SetLineColor(col);
  h->SetMarkerColor(col);
  h->SetMarkerStyle(markerStyle);
} 


TH1D* plotAsymFast(TString nfin,  TString name, Int_t nBins = 7, 
		   TString bCut = "(1)", TString minT = "0.2"){
  TChain *tin = new TChain("b2hh");
  if (nfin == "yTot") {
    tin->Add("out/Reduce/b2hh_KK_0.1_201516_Tot.root");
    tin->Add("out/Reduce/b2hh_KK_0.1_2017s29r2p2_Tot.root");
    tin->Add("out/Reduce/b2hh_KK_0.1_2018_Tot.root");
  } else
    tin->Add(nfin);
  TH1::SetDefaultSumw2();
  TH1D *hB = new TH1D("hB_"+name, "hB_"+name, nBins,0.0,0.35498222);
  TH1D *hBbar = new TH1D("hBbar_"+name, "hBbar_"+name, nBins,0.0,0.35498222);
  TH1D *hSum = new TH1D("hSum_"+name, "hSum_"+name, nBins,0.0,0.35498222);
  TH1D *hDif = new TH1D("hdif_"+name, "hDif_"+name, nBins,0.0,0.35498222);
  TH1D *hAsym = new TH1D("hAsym_"+name, "hAsym_"+name, nBins,0.0,0.35498222);
  TString isB = "(((qOS==1)*(1-etaOS)+(qOS==-1)*etaOS)*((qSSk==1)*(1-etaSSk)+(qSSk==-1)*etaSSk)>0.5)"
  tin->Draw("fmod(tauKK-"+minT+",0.35498222)>>hB_"+name, "weight*("+isB+" && tauKK>"+minT+" && "+bCut+")", "goff");
  tin->Draw("fmod(tauKK-"+minT+",0.35498222)>>hBbar_"+name,"weight*(!"+isB+" && tauKK>"+minT+" && "+bCut+")", "goff");
  hSum->Add(hB);
  hSum->Add(hBbar);
  hDif->Add(hBbar);
  hDif->Add(hB, -1);
  hAsym->Add(hDif);
  hAsym->Divide(hSum);
  return hAsym;
};
