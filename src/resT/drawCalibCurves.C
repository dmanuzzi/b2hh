{
  vector<TString> tags = {"MC_2015_Jpsi", "MC_2016_Jpsi", "MC_2017_Jpsi", "MC_2018_Jpsi",
                          //"MC_2015_Y3S", "MC_2016_Y3S", "MC_2017_Y3S", "MC_2018_Y3S",
                          "data_2015_Jpsi", "data_2016_Jpsi", "data_2017_Jpsi", "data_2018_Jpsi",
                        };
  map<TString,int> cols;
  cols["MC_2015_Jpsi"] = kRed;
  cols["MC_2016_Jpsi"] = kOrange+7;
  cols["MC_2017_Jpsi"] = kGreen+2;
  cols["MC_2018_Jpsi"] = kBlue;
  
  cols["data_2015_Jpsi"] = kRed;
  cols["data_2016_Jpsi"] = kOrange+7;
  cols["data_2017_Jpsi"] = kGreen+2;
  cols["data_2018_Jpsi"] = kBlue;
  
  cols["MC_2015_Y3S"] = kRed;
  cols["MC_2016_Y3S"] = kOrange+7;
  cols["MC_2017_Y3S"] = kGreen+2;
  cols["MC_2018_Y3S"] = kBlue;
  
  vector<TString> years = {"2015", "2016", "2017", "2018"};
  TFile *fout = new TFile("plots/SimpleCalibs.root", "RECREATE");
  for (auto year : years){
    int count = 0; 
    TCanvas *c1 = new TCanvas("SimpleCalibs_"+year, "SimpleCalibs_"+year);
    c1->cd();
  
    for (auto tag : tags){
      if (!tag.Contains(year)) continue;
      TFile * f = TFile::Open("plots/"+tag+".root", "READ");
      TCanvas * c = (TCanvas*)f->Get("cSF_"+tag);
      c->ls();
      TGraphErrors * g = ((TGraphErrors*)c->GetListOfPrimitives()->At(1));
      g->SetMarkerColor(cols[tag]);
      g->SetName(tag);
      g->SetTitle(tag);
      if (tag.Contains("data")) g->SetLineStyle(1);
      if (tag.Contains("MC"))   g->SetLineStyle(2);
      if (tag.Contains("Jpsi")) g->SetMarkerStyle(20);
      if (tag.Contains("Y3S"))  g->SetMarkerStyle(21);

      g->SetLineColor(cols[tag]);
      c1->cd();

      if (count == 0)
        g->Draw("APLE1");
      else 
        g->Draw("PLE1same");
      ++count;
      fout->WriteTObject(g, g->GetName());
    }
    c1->BuildLegend();
    fout->WriteTObject(c1, c1->GetName());
    
  }
  fout->ls();
  fout->Close();
}