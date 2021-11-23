Int_t plotMaps(TString hypo, TString cuts, TString binning, TString magnet, TString year){

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);

  TFile * inFile = new TFile("TrackEff/eff"+hypo+"_"+cuts+"_"+binning+"_"+magnet+"_"+year+".root","READ");

  TH3D * hEffKplus_isK   = (TH3D *) inFile->Get("hEffKplus_is"+hypo);
  TH2D * hEffKplus = (TH2D *) hEffKplus_isK->Project3D("YX"); 
  hEffKplus->SetName("hEffKplus"); hEffKplus->SetTitle("");
  hEffKplus->SetStats(kFALSE);

  TH3D * hEffKminus_isK  = (TH3D *) inFile->Get("hEffKminus_is"+hypo);
  TH2D * hEffKminus = (TH2D *) hEffKminus_isK->Project3D("YX"); 
  hEffKminus->SetName("hEffKminus"); hEffKminus->SetTitle("");
  hEffKminus->SetStats(kFALSE);

  TH3D * hEffPIplus_isK  = (TH3D *) inFile->Get("hEffPIplus_is"+hypo);
  TH2D * hEffPIplus = (TH2D *) hEffPIplus_isK->Project3D("YX"); 
  hEffPIplus->SetName("hEffPIplus"); hEffPIplus->SetTitle("");
  hEffPIplus->SetStats(kFALSE);

  TH3D * hEffPIminus_isK = (TH3D *) inFile->Get("hEffPIminus_is"+hypo);
  TH2D * hEffPIminus = (TH2D *) hEffPIminus_isK->Project3D("YX"); 
  hEffPIminus->SetName("hEffPIminus"); hEffPIminus->SetTitle("");
  hEffPIminus->SetStats(kFALSE);

  TH3D * hEffPplus_isK  = (TH3D *) inFile->Get("hEffPplus_is"+hypo);
  TH2D * hEffPplus = (TH2D *) hEffPplus_isK->Project3D("YX"); 
  hEffPplus->SetName("hEffPplus"); hEffPplus->SetTitle("");
  hEffPplus->SetStats(kFALSE);
  
  TH3D * hEffPminus_isK = (TH3D *) inFile->Get("hEffPminus_is"+hypo);
  TH2D * hEffPminus = (TH2D *) hEffPminus_isK->Project3D("YX");
  hEffPminus->SetName("hEffPminus"); hEffPminus->SetTitle("");
  hEffPminus->SetStats(kFALSE);

  /////////////////////////////////////////////////

  
  TCanvas * cKplus = new TCanvas("cKplus","cKplus");
  cKplus->cd();
  hEffKplus->Draw("zcol");
  hEffKplus->GetXaxis()->SetRangeUser(0,321);
  hEffKplus->GetXaxis()->SetTitleSize(0.06);        hEffKplus->GetXaxis()->SetLabelSize(0.06);
  hEffKplus->GetXaxis()->SetTitle("p (GeV/c^{2})"); hEffKplus->GetXaxis()->SetTitleOffset(1.1);
  hEffKplus->GetXaxis()->SetTickLength(0.05);       hEffKplus->GetXaxis()->SetNdivisions(505,kTRUE);

  hEffKplus->GetYaxis()->SetTitleSize(0.08); hEffKplus->GetYaxis()->SetLabelSize(0.06);
  hEffKplus->GetYaxis()->SetTitle("#eta"); hEffKplus->GetYaxis()->SetTitleOffset(0.5);
  hEffKplus->GetYaxis()->SetTickLength(0.05); hEffKplus->GetYaxis()->SetNdivisions(505,kTRUE);

  hEffKplus->GetZaxis()->SetRangeUser(0,hEffKplus->GetMaximum()*1.1);
  hEffKplus->GetZaxis()->SetNdivisions(505,kTRUE); hEffKplus->SetContour(99);

  TPad * myPad = (TPad *) cKplus->GetPad(0);
  myPad->SetLeftMargin(0.15); myPad->SetBottomMargin(0.15); myPad->SetRightMargin(0.15);
  myPad->SetBorderSize(0);
  cKplus->Draw();
  TPaletteAxis * palette = (TPaletteAxis *) hEffKplus->GetListOfFunctions()->FindObject("palette");
  palette->GetAxis()->SetTitle("#varepsilon_{K^{+}}"); 
  palette->GetAxis()->SetTitleSize(0.1); palette->GetAxis()->SetTitleOffset(0.3);
  palette->GetAxis()->SetLabelSize(0.05);
  cKplus->Draw();

  /////////////////////////////////////////////

  TCanvas * cKminus = new TCanvas("cKminus","cKminus");
  cKminus->cd();
  hEffKminus->Draw("zcol");
  hEffKminus->GetXaxis()->SetRangeUser(0,321);
  hEffKminus->GetXaxis()->SetTitleSize(0.06);        hEffKminus->GetXaxis()->SetLabelSize(0.06);
  hEffKminus->GetXaxis()->SetTitle("p (GeV/c^{2})"); hEffKminus->GetXaxis()->SetTitleOffset(1.1);
  hEffKminus->GetXaxis()->SetTickLength(0.05);       hEffKminus->GetXaxis()->SetNdivisions(505,kTRUE);

  hEffKminus->GetYaxis()->SetTitleSize(0.08);  hEffKminus->GetYaxis()->SetLabelSize(0.06);
  hEffKminus->GetYaxis()->SetTitle("#eta");    hEffKminus->GetYaxis()->SetTitleOffset(0.5);
  hEffKminus->GetYaxis()->SetTickLength(0.05); hEffKminus->GetYaxis()->SetNdivisions(505,kTRUE);

  hEffKminus->GetZaxis()->SetRangeUser(0,hEffKminus->GetMaximum()*1.1);
  hEffKminus->GetZaxis()->SetNdivisions(505,kTRUE); hEffKminus->SetContour(99);

  myPad = (TPad *) cKminus->GetPad(0);
  myPad->SetLeftMargin(0.15); myPad->SetBottomMargin(0.15); myPad->SetRightMargin(0.15);
  myPad->SetBorderSize(0);
  cKminus->Draw();
  palette = (TPaletteAxis *) hEffKminus->GetListOfFunctions()->FindObject("palette");
  palette->GetAxis()->SetTitle("#varepsilon_{K^{-}}"); 
  palette->GetAxis()->SetTitleSize(0.1); palette->GetAxis()->SetTitleOffset(0.3);
  palette->GetAxis()->SetLabelSize(0.05); 
  cKminus->Draw();

  /////////////////////////////////////////////

  TCanvas * cPIplus = new TCanvas("cPIplus","cPIplus");
  cPIplus->cd();
  hEffPIplus->Draw("zcol");
  hEffPIplus->GetXaxis()->SetRangeUser(0,321);
  hEffPIplus->GetXaxis()->SetTitleSize(0.06);        hEffPIplus->GetXaxis()->SetLabelSize(0.06);
  hEffPIplus->GetXaxis()->SetTitle("p (GeV/c^{2})"); hEffPIplus->GetXaxis()->SetTitleOffset(1.1);
  hEffPIplus->GetXaxis()->SetTickLength(0.05);       hEffPIplus->GetXaxis()->SetNdivisions(505,kTRUE);

  hEffPIplus->GetYaxis()->SetTitleSize(0.08);  hEffPIplus->GetYaxis()->SetLabelSize(0.06);
  hEffPIplus->GetYaxis()->SetTitle("#eta");    hEffPIplus->GetYaxis()->SetTitleOffset(0.5);
  hEffPIplus->GetYaxis()->SetTickLength(0.05); hEffPIplus->GetYaxis()->SetNdivisions(505,kTRUE);

  hEffPIplus->GetZaxis()->SetRangeUser(0,hEffPIplus->GetMaximum()*1.1);
  hEffPIplus->GetZaxis()->SetNdivisions(505,kTRUE); hEffPIplus->SetContour(99);

  myPad = (TPad *) cPIplus->GetPad(0);
  myPad->SetLeftMargin(0.15); myPad->SetBottomMargin(0.15); myPad->SetRightMargin(0.15);
  myPad->SetBorderSize(0);
  cPIplus->Draw();
  palette = (TPaletteAxis *) hEffPIplus->GetListOfFunctions()->FindObject("palette");
  palette->GetAxis()->SetTitle("#varepsilon_{#pi^{+}}"); 
  palette->GetAxis()->SetTitleSize(0.1); palette->GetAxis()->SetTitleOffset(0.3);
  palette->GetAxis()->SetLabelSize(0.05); 
  cPIplus->Draw();

  /////////////////////////////////////////////

  TCanvas * cPIminus = new TCanvas("cPIminus","cPIminus");
  cPIminus->cd();
  hEffPIminus->Draw("zcol");
  hEffPIminus->GetXaxis()->SetRangeUser(0,321);
  hEffPIminus->GetXaxis()->SetTitleSize(0.06);        hEffPIminus->GetXaxis()->SetLabelSize(0.06);
  hEffPIminus->GetXaxis()->SetTitle("p (GeV/c^{2})"); hEffPIminus->GetXaxis()->SetTitleOffset(1.1);
  hEffPIminus->GetXaxis()->SetTickLength(0.05);       hEffPIminus->GetXaxis()->SetNdivisions(505,kTRUE);

  hEffPIminus->GetYaxis()->SetTitleSize(0.08);  hEffPIminus->GetYaxis()->SetLabelSize(0.06);
  hEffPIminus->GetYaxis()->SetTitle("#eta");    hEffPIminus->GetYaxis()->SetTitleOffset(0.5);
  hEffPIminus->GetYaxis()->SetTickLength(0.05); hEffPIminus->GetYaxis()->SetNdivisions(505,kTRUE);

  hEffPIminus->GetZaxis()->SetRangeUser(0,hEffPIminus->GetMaximum()*1.1);
  hEffPIminus->GetZaxis()->SetNdivisions(505,kTRUE); hEffPIminus->SetContour(99);

  myPad = (TPad *) cPIminus->GetPad(0);
  myPad->SetLeftMargin(0.15); myPad->SetBottomMargin(0.15); myPad->SetRightMargin(0.15);
  myPad->SetBorderSize(0);
  cPIminus->Draw();
  palette = (TPaletteAxis *) hEffPIminus->GetListOfFunctions()->FindObject("palette");
  palette->GetAxis()->SetTitle("#varepsilon_{#pi^{-}}");
  palette->GetAxis()->SetTitleSize(0.1); palette->GetAxis()->SetTitleOffset(0.3);
  palette->GetAxis()->SetLabelSize(0.05);
  cPIminus->Draw();

  /////////////////////////////////////////////

  TLine * line1 = new TLine(0,2,25,2); line1->SetLineWidth(3);
  TLine * line2 = new TLine(25,2,120,3.75); line2->SetLineWidth(3);
  TLine * line3 = new TLine(120,3.75,135,6); line3->SetLineWidth(3);

  TCanvas * cPplus = new TCanvas("cPplus","cPplus");
  cPplus->cd();
  hEffPplus->Draw("zcol");
  hEffPplus->GetXaxis()->SetRangeUser(0,321);
  hEffPplus->GetXaxis()->SetTitleSize(0.06);        hEffPplus->GetXaxis()->SetLabelSize(0.06);
  hEffPplus->GetXaxis()->SetTitle("p (GeV/c^{2})"); hEffPplus->GetXaxis()->SetTitleOffset(1.1);
  hEffPplus->GetXaxis()->SetTickLength(0.05);       hEffPplus->GetXaxis()->SetNdivisions(505,kTRUE);

  hEffPplus->GetYaxis()->SetTitleSize(0.08);  hEffPplus->GetYaxis()->SetLabelSize(0.06);
  hEffPplus->GetYaxis()->SetTitle("#eta");    hEffPplus->GetYaxis()->SetTitleOffset(0.5);
  hEffPplus->GetYaxis()->SetTickLength(0.05); hEffPplus->GetYaxis()->SetNdivisions(505,kTRUE);

  hEffPplus->GetZaxis()->SetRangeUser(0,hEffPplus->GetMaximum());
  hEffPplus->GetZaxis()->SetNdivisions(505,kTRUE); hEffPplus->SetContour(99);

  myPad = (TPad *) cPplus->GetPad(0);
  myPad->SetLeftMargin(0.15); myPad->SetBottomMargin(0.15); myPad->SetRightMargin(0.15);
  myPad->SetBorderSize(0);
  cPplus->Draw();
  palette = (TPaletteAxis *) hEffPplus->GetListOfFunctions()->FindObject("palette");
  palette->GetAxis()->SetTitle("#varepsilon_{p}");
  palette->GetAxis()->SetTitleSize(0.1); palette->GetAxis()->SetTitleOffset(0.3);
  palette->GetAxis()->SetLabelSize(0.05);
  cPplus->Draw();
  line1->Draw("same"); line2->Draw("same"); line3->Draw("same");

  /////////////////////////////////////////////

  TCanvas * cPminus = new TCanvas("cPminus","cPminus");
  cPminus->cd();
  hEffPminus->Draw("zcol");
  hEffPminus->GetXaxis()->SetRangeUser(0,321);
  hEffPminus->GetXaxis()->SetTitleSize(0.06);        hEffPminus->GetXaxis()->SetLabelSize(0.06);
  hEffPminus->GetXaxis()->SetTitle("p (GeV/c^{2})"); hEffPminus->GetXaxis()->SetTitleOffset(1.1);
  hEffPminus->GetXaxis()->SetTickLength(0.05);       hEffPminus->GetXaxis()->SetNdivisions(505,kTRUE);

  hEffPminus->GetYaxis()->SetTitleSize(0.08);  hEffPminus->GetYaxis()->SetLabelSize(0.06);
  hEffPminus->GetYaxis()->SetTitle("#eta");    hEffPminus->GetYaxis()->SetTitleOffset(0.5);
  hEffPminus->GetYaxis()->SetTickLength(0.05); hEffPminus->GetYaxis()->SetNdivisions(505,kTRUE);

  hEffPminus->GetZaxis()->SetRangeUser(0,hEffPminus->GetMaximum());
  hEffPminus->GetZaxis()->SetNdivisions(505,kTRUE); hEffPminus->SetContour(99);

  myPad = (TPad *) cPminus->GetPad(0);
  myPad->SetLeftMargin(0.15); myPad->SetBottomMargin(0.15); myPad->SetRightMargin(0.15);
  myPad->SetBorderSize(0);
  cPminus->Draw();
  palette = (TPaletteAxis *) hEffPminus->GetListOfFunctions()->FindObject("palette");
  palette->GetAxis()->SetTitle("#varepsilon_{#bar{p}}");
  palette->GetAxis()->SetTitleSize(0.1); palette->GetAxis()->SetTitleOffset(0.3);
  palette->GetAxis()->SetLabelSize(0.05);
  cPminus->Draw();
  line1->Draw("same"); line2->Draw("same"); line3->Draw("same");

  return 0;
}
