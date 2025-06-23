TH1D * drawFeature(TChain *chain, TString feature, TString cut, int nBins, double min, double max){
    TH1D *h = new TH1D("h"+feature,"h"+feature,nBins,min,max);
    chain->Draw(feature+">>h"+feature,cut,"");
    h->Scale(1./h->Integral()); //already normalised
    return h;
}

void drawCanvas(TH1D *hSig, TH1D *hBkg, TString feature, TString title){
    TCanvas *c = new TCanvas("c","c",800,600);
    hSig->SetTitle(title);
    hSig->SetStats(0);
    hSig->SetLineWidth(2);
    hBkg->SetLineWidth(2);
    hSig->SetLineColor(kBlue);
    hSig->SetFillColor(kBlue-9);
    hBkg->SetLineColor(kRed);
    hBkg->SetFillStyle(3354);
    hBkg->SetFillColor(kRed);
    hSig->SetMaximum(1.1*std::max(hSig->GetMaximum(),hBkg->GetMaximum()));
    hSig->Draw("hist");
    hBkg->Draw("hist same");
    TLegend *leg = new TLegend(0.6,0.6,0.88,0.88);
    leg->AddEntry(hSig,"Signal","f");
    leg->AddEntry(hBkg,"Background","f");
    leg->SetFillColor(0);
    leg->SetLineColor(0);  
    leg->SetBorderSize(0);
    leg->Draw();
    //c->SetTitle(titles);
    c->SaveAs("${B2HH_OUT}/newBDTtrain/featurePlots/"+feature+".pdf");
    c->SaveAs("${B2HH_OUT}/newBDTtrain/featurePlots/"+feature+".root");
}

void drawingFeatures(){ // disegniamo il 2018 e via
    TChain *signal = new TChain("signal","signal");
    TChain *background = new TChain("background","background"); // + copies postBDT
    //TChain *signalOnTop = new TChain("signalOnTop","signalOnTop");
    //TChain *backgroundOnTop = new TChain("backgroundOnTop","backgroundOnTop");

    signal->Add("${B2HH_OUT}/AccSignal/kineWeight/bspipi_pipi_PIPI_0_2018_Tot_Kine.root/b2hh");
    background->Add("${B2HH_OUT}/Data/tuple_merged/sideband_b2hh_2018_Up.root/b2hh");
    background->Add("${B2HH_OUT}/Data/tuple_merged/sideband_b2hh_2018_Down.root/b2hh");

    signal->Add("${B2HH_OUT}/AccSignal/kineWeight/bspipi_pipi_PIPI_0_201516_Tot_Kine.root/b2hh");
    signal->Add("${B2HH_OUT}/AccSignal/kineWeight/bspipi_pipi_PIPI_0_2017s29r2p2_Tot_Kine.root/b2hh");

    background->Add("${B2HH_OUT}/Data/tuple_merged/sideband_b2hh_2015_Up.root/b2hh");
    background->Add("${B2HH_OUT}/Data/tuple_merged/sideband_b2hh_2015_Down.root/b2hh");    
    background->Add("${B2HH_OUT}/Data/tuple_merged/sideband_b2hh_2016_Up.root/b2hh");
    background->Add("${B2HH_OUT}/Data/tuple_merged/sideband_b2hh_2016_Down.root/b2hh");    
    background->Add("${B2HH_OUT}/Data/tuple_merged/sideband_b2hh_2017s29r2p2_Up.root/b2hh");
    background->Add("${B2HH_OUT}/Data/tuple_merged/sideband_b2hh_2017s29r2p2_Down.root/b2hh");

    TH1D * hSig      = new TH1D("hSig","hSig",100,0,50);
    TH1D * hSigOnTOp = new TH1D("hSigOnTOp","hSigOnTOp",100,0,50);

    TH1D * hBkg      = new TH1D("hBkg","hBkg",100,0,50);
    TH1D * hBkgOnTOp = new TH1D("hBkgOnTOp","hBkgOnTOp",100,0,50);

    signal->Draw("BDTtrain_ptB0>>hSig","weight",""); // il peso si occupa di tutto 
    background->Draw("BDTtrain_ptB0>>hBkg","bdtPIPI>0 && piplusDLLKPI<-1 && piminusDLLKPI<-1 && piplusDLLPPI<3 && piminusDLLPPI<3",""); // massa a posto, manca taglio BDT e PID

    TCanvas *c = new TCanvas("c","c",800,600);
    hSig->Draw();
    hBkg->Draw("same");
    c->Draw();

    std::vector<TH1D *> hsig;
    std::vector<TH1D *> hbkg;
    std::vector<double> binsMin = {0, 4, 0,0,0,   2, 0.5, 2,0.5};
    std::vector<double> binsMax = {30,14,9,8,0.15,12,14, 12,14};

    std::vector<TString> features = {"BDTtrain_ptB0","BDTtrain_logfdchi2B0","BDTtrain_ipchi2B0","BDTtrain_vtxchi2","BDTtrain_doca",
                                     "BDTtrain_logmaxchi2ip","BDTtrain_maxpt","BDTtrain_logminchi2ip","BDTtrain_minpt"};

    std::vector<TString> titles = {"p_{T}(H_{b}^{0});[GeV/c];",
                                   "log(#chi^{2}_{FD}(H_{b}^{0}));;",
                                   "#chi^{2}_{IP}(H_{b}^{0})",
                                   "#chi^{2}_{vtx}(H_{b}^{0})",
                                   "d_{CA};[mm];",
                                   "log(max[#chi^{2}_{IP}(h^{+}),#chi^{2}_{IP}(h^{-})]);;",
                                   "max[p_{T}(h^{+}),p_{T}(h^{-})];[GeV/c];",
                                   "log(min[#chi^{2}_{IP}(h^{+}),#chi^{2}_{IP}(h^{-})]);;",
                                   "min[p_{T}(h^{+}),p_{T}(h^{-})];[GeV/c];"};

    for (int i = 0; i < features.size(); i++){
        hsig.push_back(drawFeature(signal,features[i],"weight",100,binsMin[i],binsMax[i]));
        hbkg.push_back(drawFeature(background,features[i],"bdtPIPI>0 && piplusDLLKPI<-1 && piminusDLLKPI<-1 && piplusDLLPPI<3 && piminusDLLPPI<3",100,binsMin[i],binsMax[i]));
    }

    for (int i = 0; i < features.size(); i++){
        drawCanvas(hsig[i],hbkg[i],features[i],titles[i]);
    }

    TCanvas *c2 = new TCanvas("c2","c2",1000,800);
    c2->Divide(3,3);
    for (int i = 0; i < features.size(); i++){
        c2->cd(9-i);
        hsig[i]->SetTitle(titles[i]);
        hsig[i]->SetStats(0);
        hsig[i]->SetLineWidth(1);
        hbkg[i]->SetLineWidth(1);
        hsig[i]->SetLineColor(kBlue);
        hsig[i]->SetFillColor(kBlue-9);
        hbkg[i]->SetLineColor(kRed);
        hbkg[i]->SetFillStyle(3354);
        hbkg[i]->SetFillColor(kRed);
        hsig[i]->SetMaximum(1.1*std::max(hsig[i]->GetMaximum(),hbkg[i]->GetMaximum()));
        hsig[i]->Draw("hist");
        hbkg[i]->Draw("hist same");
    }
    c2->cd(1);
    TLegend *leg = new TLegend(0.5,0.45,0.88,0.85);
    leg->AddEntry(hsig[0],"Signal","f");
    leg->AddEntry(hbkg[0],"Background","f");
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    leg->SetBorderSize(0);
    leg->Draw();
    c2->SaveAs("${B2HH_OUT}/newBDTtrain/featurePlots/AllFeatures.pdf");
    c2->SaveAs("${B2HH_OUT}/newBDTtrain/featurePlots/AllFeatures.root");
}