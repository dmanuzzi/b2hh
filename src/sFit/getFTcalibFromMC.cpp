void getFTcalibFromMC(TString nfin){


    TFile* fin = new TFile(nfin, "READ");
    TTree* tin = (TTree*)fin->Get("b2hh");

    TH1D *hNtrue = new TH1D("hNtrue", "hNtrue", 3, -1.5, 1.5);
    tin->Draw("qTrue>>hNtrue", "weight", "goff");
    double Nu = hNtrue->GetBinContent(3);
    double Nd = hNtrue->GetBinContent(1);
    double Ap = (Nd-Nu)/(Nd+Nu);
    printf(" Ap = %.4f\n", Ap);
    TH1D* hNOS = new TH1D("hNOS", "hNOS", 3, -1.5,1.5);
    tin->Draw("qTrue>>hNOS", "weight*(qOS!=0)", "goff");
    double NOSu = hNOS->GetBinContent(3);
    double NOSd = hNOS->GetBinContent(1);
    double epsOSu = NOSu / Nu;
    double epsOSd = NOSd / Nd;
    double epsOS = (epsOSu + epsOSd)/2.0;
    double epsAsymOS = (NOSu-NOSd)/(NOSu+NOSd);
    double Ntot = hNtrue->Integral();
    printf(" epsOS = %.4f\n", (NOSu+NOSd)/Ntot);
    printf("<epsOS> = %.4f; espAsymOS = %.4f\n", epsOS, epsAsymOS);
    
    TH1D *hNSSk = new TH1D("hNSSk", "hNSSk", 3, -1.5, 1.5);
    tin->Draw("qTrue>>hNSSk", "weight*(qSSk!=0)", "goff");
    double NSSku = hNSSk->GetBinContent(3);
    double NSSkd = hNSSk->GetBinContent(1);
    double epsSSku = NSSku / Nu;
    double epsSSkd = NSSkd / Nd;
    double epsSSk = (epsSSku + epsSSkd) / 2.0;
    double epsAsymSSk = (NSSku - NSSkd) / (NSSku + NSSkd);
    printf(" epsSSk  = %.4f\n", (NSSku+NSSkd)/Ntot);
    printf("<epsSSk> = %.4f; espAsymSSk = %.4f\n", epsSSk, epsAsymSSk);
    

    int Nbins = 50; 
    TProfile *hOS = new TProfile("hOS", "hOS", Nbins, 0, 0.5);
    tin->Draw("(qOS!=qTrue):etaOS>>hOS", "weight*(qOS!=0)", "prof goff");
    TF1* fOS = new TF1("fOS", "[0]+[1]*(x-0.37)", 0,0.5);
    fOS->SetParameter(0, 0.37), fOS->SetParameter(1, 1);
    hOS->Fit(fOS, "Q");
    printf("calib OS:     p0 = %.4f +/- %.4f; p1 = %.4f +/- %.4f;\n",
           fOS->GetParameter(0), fOS->GetParError(0), fOS->GetParameter(1), fOS->GetParError(1));
    TCanvas* cOS = new TCanvas("cOS", "cOS");
    cOS->cd();
    hOS->Draw();
    // ----------------------------------------------------------
    // ----------------------------------------------------------
    // ----------------------------------------------------------
    TProfile *hOSb = new TProfile("hOSb", "hOSb", Nbins, 0, 0.5);
    tin->Draw("(qOS!=qTrue):etaOS>>hOSb", "weight*(qOS!=0 && qTrue==+1)", "prof goff");
    hOSb->Fit(fOS, "Q");
    double p0b = fOS->GetParameter(0);
    double p1b = fOS->GetParameter(1);
    printf("calib OSb:    p0 = %.4f +/- %.4f; p1 = %.4f +/- %.4f;\n",
           fOS->GetParameter(0), fOS->GetParError(0), fOS->GetParameter(1), fOS->GetParError(1));
    TCanvas *cOSb = new TCanvas("cOSb", "cOSb");
    cOSb->cd();
    hOSb->Draw();

    TProfile *hOSbar = new TProfile("hOSbar", "hOSbar", Nbins, 0, 0.5);
    tin->Draw("(qOS!=qTrue):etaOS>>hOSbar", "weight*(qOS!=0 && qTrue==-1)", "prof goff");
    hOSbar->Fit(fOS, "Q");
    double p0bar = fOS->GetParameter(0);
    double p1bar = fOS->GetParameter(1);
    printf("calib OSbar:  p0 = %.4f +/- %.4f; p1 = %.4f +/- %.4f;\n",
           fOS->GetParameter(0), fOS->GetParError(0), fOS->GetParameter(1), fOS->GetParError(1));
    TCanvas *cOSbar = new TCanvas("cOSbar", "cOSbar");
    cOSbar->cd();
    hOSbar->Draw();
    printf("OS:          <p0> = %.4f; delta p0 = %.4f\n", (p0b+p0bar)/2.0, (p0b-p0bar)/(p0b+p0bar));
    printf("OS:          <p1> = %.4f; delta p1 = %.4f\n", (p1b+p1bar)/2.0, (p1b-p1bar)/(p1b+p1bar));
    // ----------------------------------------------------------
    // ----------------------------------------------------------
    TProfile *hSSk = new TProfile("hSSk", "hSSk", Nbins, 0, 0.5);
    tin->Draw("(qSSk!=qTrue):etaSSk>>hSSk", "weight*(qSSk!=0)", "prof goff");
    TF1 *fSSk = new TF1("fSSk", "[0]+[1]*(x-0.429)", 0, 0.5);
    fSSk->SetParameter(0, 0.429), fSSk->SetParameter(1, 1);
    hSSk->Fit(fSSk, "Q");
    printf("calib SSk:     p0 = %.4f +/- %.4f; p1 = %.4f +/- %.4f;\n",
           fSSk->GetParameter(0), fSSk->GetParError(0), fSSk->GetParameter(1), fSSk->GetParError(1));
    TCanvas *cSSk = new TCanvas("cSSk", "cSSk");
    cSSk->cd();
    hSSk->Draw();

    TProfile *hSSkb = new TProfile("hSSkb", "hSSkb", Nbins, 0, 0.5);
    tin->Draw("(qSSk!=qTrue):etaSSk>>hSSkb", "weight*(qSSk!=0 && qTrue==+1)", "prof goff");
    hSSkb->Fit(fSSk, "Q");
    p0b = fSSk->GetParameter(0);
    p1b = fSSk->GetParameter(1);
    printf("calib SSkb:    p0 = %.4f +/- %.4f; p1 = %.4f +/- %.4f;\n",
           fSSk->GetParameter(0), fSSk->GetParError(0), fSSk->GetParameter(1), fSSk->GetParError(1));
    TCanvas *cSSkb = new TCanvas("cSSkb", "cSSkb");
    cSSkb->cd();
    hSSkb->Draw();

    TProfile *hSSkbar = new TProfile("hSSkbar", "hSSkbar", Nbins, 0, 0.5);
    tin->Draw("(qSSk!=qTrue):etaSSk>>hSSkbar", "weight*(qSSk!=0 && qTrue==-1)", "prof goff");
    hSSkbar->Fit(fSSk, "Q");
    p0bar = fSSk->GetParameter(0);
    p1bar = fSSk->GetParameter(1);
    printf("calib SSkbar:  p0 = %.4f +/- %.4f; p1 = %.4f +/- %.4f;\n",
           fSSk->GetParameter(0), fSSk->GetParError(0), fSSk->GetParameter(1), fSSk->GetParError(1));
    TCanvas *cSSkbar = new TCanvas("cSSkbar", "cSSkbar");
    cSSkbar->cd();
    hSSkbar->Draw();
    printf("SSk:          <p0> = %.4f; delta p0 = %.4f\n", (p0b + p0bar) / 2.0, (p0b - p0bar) / (p0b + p0bar));
    printf("SSk:          <p1> = %.4f; delta p1 = %.4f\n", (p1b + p1bar) / 2.0, (p1b - p1bar) / (p1b + p1bar));
}