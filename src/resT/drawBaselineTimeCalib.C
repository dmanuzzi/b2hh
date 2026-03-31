{
  TFile * _file0 = TFile::Open("DVtuple.root", "READ");
  TTree * t = (TTree*)_file0->Get("DecayTree/DecayTree");
  TH2D * h = new TH2D("h", "h", 25,0,100,100,-100,100);
  t->Draw("Jpsi_TAU*1e6:Jpsi_TAUERR*1e6>>h", "Jpsi_TRUEID==443", "goff");
  TProfile * pfx = h->ProfileX("_pfx", 1, -1, "s");
  pfx->SetTitle("pfx;#delta [fs]; #sigma [fs]");
  vector<Double_t> x,y;
  for (int i=1; i<= pfx->GetNbinsX(); ++i){
    x.push_back(pfx->GetBinCenter(i));
    y.push_back(pfx->GetBinError(i));
  }
  TCanvas * c0 = new TCanvas("c0","c0", 600,400);
  h->Draw("colz");
  TCanvas * c1 = new TCanvas("c1","c1", 600,400);
  pfx->Draw();
  TGraph * g = new TGraph(y.size(), x.data(), y.data());
  g->SetTitle("Decay Time Calibration;#delta [fs]; #sigma [fs]");
  g->Print();
  TCanvas * c2 = new TCanvas("c2","c2", 600,400);
  g->SetMarkerStyle(20);
  g->Draw("AP");
}
