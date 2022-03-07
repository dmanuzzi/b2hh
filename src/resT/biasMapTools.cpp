#ifndef BIASMAPTOOLS_cpp
#define BIASMAPTOOLS_cpp

#include "biasMapTools.h"
#include <fstream>
#include "TObjArray.h"

TString biasMapTools::nfin_path_Jpsi = "/storage/gpfs_data/local/lhcb/users/dmanuzzi/B2HH/resT";
map <TString, vector<TString>> biasMapTools::tag_nfins_Jpsi = {
                   {"Jpsi_2016_Up",
                    {nfin_path_Jpsi + "/Jpsi_data_2016_MagUp.root/ntp"}},
                   {"Jpsi_2017_Up",
                    {nfin_path_Jpsi + "/Jpsi_data_2017_MagUp.root/ntp"}},
                   {"Jpsi_2018_Up",
                    {nfin_path_Jpsi + "/Jpsi_data_2018_MagUp.root/ntp"}},
                   {"Jpsi_2016_Down",
                    {nfin_path_Jpsi + "/Jpsi_data_2016_MagDw.root/ntp"}},
                   {"Jpsi_2017_Down",
                    {nfin_path_Jpsi + "/Jpsi_data_2017_MagDw.root/ntp"}},
                   {"Jpsi_2018_Down",
                    {nfin_path_Jpsi + "/Jpsi_data_2018_MagDw.root/ntp"}},
                   {"Jpsi_2016_Tot",
                    {nfin_path_Jpsi + "/Jpsi_data_2016_MagUp.root/ntp",
                     nfin_path_Jpsi + "/Jpsi_data_2016_MagDw.root/ntp"}},
                   {"Jpsi_2017_Tot",
                    {nfin_path_Jpsi + "/Jpsi_data_2017_MagUp.root/ntp",
                     nfin_path_Jpsi + "/Jpsi_data_2017_MagDw.root/ntp"}},
                   {"Jpsi_2018_Tot",
                    {nfin_path_Jpsi + "/Jpsi_data_2018_MagUp.root/ntp",
                     nfin_path_Jpsi + "/Jpsi_data_2018_MagDw.root/ntp"}},
};

void biasMapTools::ActivateAndSetBranch(TTree *tin, TString nbranch, void *var)
{
    tin->SetBranchStatus(nbranch, 1);
    tin->SetBranchAddress(nbranch, var);
}

vector<Double_t> biasMapTools::makeBins(int Nbins, double binMin, double binMax)
{
    vector<double> binContainer;
    for (int i = 0; i <= Nbins; ++i)
    {
        double newBin = binMin + (binMax - binMin) / ((double)Nbins) * ((double)i);
        binContainer.push_back(newBin);
    }
    return binContainer;
};

biasMapTools::biasMapTools(){    
    minTime = -0.5; // ps
    maxTime = +0.5; // ps
    //RooRealVar time("time", "time", biasMapTools::minTime, biasMapTools::maxTime, "ps");
    m_tag_data = "";
    m_tag_test = "";
    
    m_NbinsTot = 0;
    tmp_bin = 0;
}

biasMapTools::biasMapTools(TString tag_test, TString tag_data,
                           vector<TString> tag_vars,
                           vector<vector<Double_t>> binnings)
{
    biasMapTools();
    m_tag_test = tag_test;
    m_tag_data = tag_data;
    m_tag_data_test = m_tag_data+"_"+m_tag_test;
    m_tag_vars = tag_vars;
    m_binnings = binnings;
    if (m_tag_vars.size() != m_binnings.size())
        printf("ERROR: size of vars is different from size of binnings!\n");
    m_Nvars = (Int_t)(m_tag_vars.size());
    vars = vector<Double_t>(m_Nvars, 0.);

    m_NbinsTot = 1;
    m_Nbins.clear();
    for (auto binning : m_binnings)
    {
        m_Nbins.push_back((Int_t)(binning.size() - 1));
        m_NbinsTot *= m_Nbins.back();
    }
    printf("NbinsTot: %d\n", m_NbinsTot);

    m_sumX = vector<Double_t>(m_NbinsTot, 0.);
    m_sumX2 = vector<Double_t>(m_NbinsTot, 0.);
    m_countBin = vector<Int_t>(m_NbinsTot, 0.);
    m_meanBin = vector<Double_t>(m_NbinsTot, 0);
    m_rmsBin = vector<Double_t>(m_NbinsTot, 0);
    m_meanErrBin = vector<Double_t>(m_NbinsTot, 0);
    v_h_var.clear();
    for (int i = 0; i < m_Nvars; ++i)
    {
        TString nhist = Form("h_%s_var_%s",
                             m_tag_data_test.Data(), 
                             m_tag_vars[i].Data());
        v_h_var.push_back(new TH1D(nhist, nhist,
                                   m_Nbins[i], binnings[i].data()));
        v_h_var.back()->GetXaxis()->SetTitle(Form("%s (%s)", 
                                             m_tag_vars[i].Data(),
                                             m_tag_data.Data()));
        v_h_var.back()->GetYaxis()->SetTitle("Number of Candidates");
    }

    tmp_bins = vector<Int_t>(m_Nvars, 0);
    v_h_slice2D.clear();
}


Int_t biasMapTools::getBin1D(Double_t &val, Int_t iVar){
    auto begin = m_binnings[iVar].begin();
    auto end = m_binnings[iVar].end();
    auto it = upper_bound(begin, end, val);
    if (it == begin) return 1;
    if (it == end) return m_Nbins[iVar];
    return distance(begin, it);
}

vector<Int_t> biasMapTools::getBinND(vector<Double_t> &vals){
    vector<Int_t> bins(m_Nvars, 0);
    Int_t iVar = 0;
    //printf("++++++++++++++++\n");
    transform(vals.begin(), vals.end(), bins.begin(), [&iVar, this](Double_t &val){
        auto bin = this->getBin1D(val, iVar);
        //printf("ivar: %d, var: %g, ibin: %d\n", iVar, val, bin);
        ++iVar;
        return bin;
    });
    // for_each(bins.begin(),  bins.end(), [](Int_t i){printf(" %d ",i);});
    // printf("\n++++++++++++++++\n");
    return bins;
}

Int_t biasMapTools::getBin(vector<Int_t> &bins){
    Int_t prod = 1;
    Int_t ret = bins[0];
    for (Int_t idim = 1; idim < m_Nvars; ++ idim){
        prod *= m_Nbins[idim-1];
        ret += (bins[idim]-1)*prod;
    }
    // printf("*** bin: %d\n",ret);
    return ret;
}

vector<Int_t> biasMapTools::getBinIndices(Int_t ibin){
    vector<Int_t> ret(m_Nvars,0);
    Int_t prod = 1.;
    for (Int_t idim = 0; idim < m_Nvars-1; ++idim)
        prod *= m_Nbins[idim];
    for (Int_t idim = m_Nvars-1; idim >= 0; --idim)
    {
        int ratio = ibin / prod;
        int mod = ibin % prod;
        if (mod==0)
            ret[idim] = ibin / prod;
        else 
            ret[idim] = ibin / prod + (idim ? 1 : 0);
        // printf("prod: %d, ret: %d, ibin: %d idim: %d\n", prod, ret[idim], ibin, idim);
        ibin = ibin - prod * (ret[idim]-1);
        if (idim>0)
            prod = prod/m_Nbins[idim-1];
    }
    // printf("prod: %d, ibin: %d\n", prod, ibin);
    return ret;
}

vector<Double_t> biasMapTools::getBinCenter(Int_t ibin){
    auto Ibins = this->getBinIndices(ibin);
    vector<Double_t> ret(m_Nvars,0);
    transform(Ibins.begin(), Ibins.end(), m_binnings.begin(), ret.begin(), 
              [](Int_t I, vector<Double_t> binning){
              return (binning[I]+binning[I-1])/2.; });
    return ret;
}



Int_t biasMapTools::getNvars(){
    return m_Nvars;
}

void biasMapTools::fill(Double_t &val){
    tmp_bins = biasMapTools::getBinND(this->vars);
    tmp_bin = biasMapTools::getBin(tmp_bins) - 1;
    m_countBin[tmp_bin] += 1;
    m_sumX[tmp_bin] += val;
    m_sumX2[tmp_bin] += val * val;

    transform(this->vars.begin(), this->vars.end(), 
              this->v_h_var.begin(), this->vars.begin(),
              [](Double_t &var, TH1D *h_var)
              { h_var->Fill(var); return var; });
}

void biasMapTools::draw_vars(TString pathOut, TString opt){
    for (TH1D* h_var : this->v_h_var)
    {
        TString ncanv = Form("canv_%s", h_var->GetName());
        TCanvas *canv = new TCanvas(ncanv, ncanv, 500, 400);
        if (opt.Contains("norm")){
            h_var->Scale(1. / h_var->Integral());
            h_var->GetYaxis()->SetTitle("Frac. of Candidates");
            h_var->SetMinimum(0);
        }
        if (opt.Contains("hist"))
            h_var->Draw("hist");
        if (pathOut != "")
            canv->SaveAs(Form(pathOut+"/%s.pdf", canv->GetName()));
    }
}

Int_t biasMapTools::getVarIndex(TString nvar){
    auto it = find(m_tag_vars.begin(), m_tag_vars.end(), nvar);
    if (it == m_tag_vars.end()) return -1;
    return distance(m_tag_vars.begin(), it);
}


void biasMapTools::draw_distrib2D_slice(TString tag, vector<TString> nvars_toPlot, 
                                        TString pathOut, TString opt){
    if (nvars_toPlot.size() != 2){
        printf("ERROR in biasMapTools::draw_distrib2D_slice, the number of variables to plot is not 2!\n");
        return;
    }

    Int_t iVar1 = this->getVarIndex(nvars_toPlot[0]);
    Int_t iVar2 = this->getVarIndex(nvars_toPlot[1]);
    printf("Var to plot: %s %s\n", m_tag_vars[iVar1].Data(), m_tag_vars[iVar2].Data());
    vector<Int_t> iVars_toSlice;
    printf("Var to slice: ");
    for (int i=0; i<m_Nvars; ++i){
        if (i == iVar1 || i == iVar2) continue;
        iVars_toSlice.push_back(i);
        printf(" %s ", m_tag_vars[i].Data());
    }
    Int_t Nvars_toSlice = iVars_toSlice.size();
    // printf("\nNvars_toSlice: %d\n", Nvars_toSlice);
    vector<Int_t> iVar_toSlice_Nbins(Nvars_toSlice,0);
    transform(iVars_toSlice.begin(), iVars_toSlice.end(),
              iVar_toSlice_Nbins.begin(), [this](Int_t i){ return this->m_Nbins[i]; });
    // printf("iVar_toSlice_Nbins: ");
    // for_each(iVar_toSlice_Nbins.begin(), iVar_toSlice_Nbins.end(), [](Int_t i){printf(" %d ", i);});
    Int_t Nslices = 1;
    for_each(iVar_toSlice_Nbins.begin(), iVar_toSlice_Nbins.end(), 
            [&Nslices](Int_t N){ Nslices *= N; });
    // printf("\nNslices: %d\n", Nslices);
    
    v_h_slice2D[tag] = vector<TH2D *>(Nslices, nullptr);
    for (Int_t i=0; i<Nslices; ++i){
        Int_t i_slice = i+1;
        auto iBin_slice = biasMapTools::getBinIndices(i_slice, iVar_toSlice_Nbins);
        TString nslice = "";
        for_each(iBin_slice.begin(), iBin_slice.end(), [&nslice](Int_t k){
            nslice += Form("_%d",k);
        });
        TString nhist = Form("h_slice_%s_%s_%s", tag.Data(), 
                            m_tag_data_test.Data(),
                            nslice.Data());
        v_h_slice2D[tag][i] = new TH2D(nhist, nhist,
                                       m_Nbins[iVar1], m_binnings[iVar1].data(),
                                       m_Nbins[iVar2], m_binnings[iVar2].data());
        v_h_slice2D[tag][i]->GetXaxis()->SetTitle(m_tag_vars[iVar1]);
        v_h_slice2D[tag][i]->GetYaxis()->SetTitle(m_tag_vars[iVar2]);
    }

    for (int i = 0; i < m_NbinsTot; ++i){
        int ibin = i+1; 
        // printf("ibin: %d\n", ibin);
        auto iBins = this->getBinIndices(ibin);
        //for_each(iBins.begin(), iBins.end(), [](int i){printf(" %d ", i);} );
        vector<Int_t> iBins_toSlice;
        for_each(iVars_toSlice.begin(), iVars_toSlice.end(), [&iBins_toSlice, &iBins](Int_t k)
                 { iBins_toSlice.push_back(iBins[k]); });
        // for_each(iBins_toSlice.begin(), iBins_toSlice.end(), [](int i)
        //          { printf("iBin to slice %d \n",i); });
        int i_slice = biasMapTools::getBin(iBins_toSlice, iVar_toSlice_Nbins);
        TH2D *h = v_h_slice2D[tag][i_slice-1];
        auto binCenter = this->getBinCenter(ibin);
        // for_each(binCenter.begin(), binCenter.end(), [](double i)
        //          { printf(" %g ", i); });
        auto h_ibin = h->FindBin(binCenter[iVar1], binCenter[iVar2]);
        //printf("\n %d %d %g %g \n", h_ibin, m_countBin[i] ,m_meanBin[i], m_meanErrBin[i]);
        TString nhist = h->GetName();
        if (nhist.Contains("_biasMap_")){
            h->SetBinContent(h_ibin, m_meanBin[i]);
            h->SetBinError(h_ibin, m_meanErrBin[i]);
        }
        else if (nhist.Contains("_distrib_")){
            h->SetBinContent(h_ibin, m_countBin[i]);
            h->SetBinError(h_ibin, sqrt(m_countBin[i]));
        }
    }

    for (Int_t i = 0; i < Nslices; ++i)
    {
        TH2D *h = v_h_slice2D[tag][i];
        TString nhist = h->GetName();
        TString ncanv = "canv_" + nhist;
        TCanvas *canv = nullptr;
        if (opt.Contains("pol")) {
            canv = new TCanvas(ncanv, ncanv, 900, 400);
            canv->Divide(2);
        } else {
            canv = new TCanvas(ncanv, ncanv, 450, 400);
        }

        if (nhist.Contains("_biasMap_"))
        {
            canv->cd(1);
            h->Scale(1000);
            h->SetMinimum(-20);
            h->SetMaximum(+20);
            h->SetMarkerSize(1.8);
            h->Draw("colz texte");
            if (opt.Contains("pol")){
                canv->cd(2);
                gPad->DrawFrame(-m_binnings[iVar2].back(), -m_binnings[iVar2].back(),
                                +m_binnings[iVar2].back(), +m_binnings[iVar2].back());
                h->Draw("same pol colz texte");
            }
        }
        else if (nhist.Contains("_distrib_"))
        {
            //h->Scale(1. / h->Integral());
            h->SetMinimum(0);
            h->SetMaximum(5000);
            h->SetMarkerSize(1.5);
            canv->cd(1);
            h->Draw("colz text");
            if (opt.Contains("pol")){
                canv->cd(2);
                gPad->DrawFrame(-m_binnings[iVar2].back(), -m_binnings[iVar2].back(),
                                +m_binnings[iVar2].back(), +m_binnings[iVar2].back());
                h->Draw("same pol colz");
            }
        }
        if (pathOut != ""){
            canv->SaveAs(Form(pathOut + "/%s.pdf", canv->GetName()));
            canv->SaveAs(Form(pathOut+"/%s.root", canv->GetName()));
        }
    }
}

void biasMapTools::calcProfiles(Int_t minEntries){
    m_meanBin.clear();
    m_rmsBin.clear();
    m_meanErrBin.clear();
    m_meanBin    = vector<Double_t>(m_NbinsTot,0);
    m_rmsBin     = vector<Double_t>(m_NbinsTot,0);
    m_meanErrBin = vector<Double_t>(m_NbinsTot,0);
    for (int ibin = 0; ibin < m_NbinsTot; ++ibin)
    {
        double count   = (Double_t)m_countBin[ibin];
        double mean    = (count < minEntries) ? 0 : m_sumX[ibin] / count;
        double rms     = (count < minEntries) ? 0 : sqrt(m_sumX2[ibin] / count - mean * mean);
        double meanErr = (count < 1)? 0 : rms / sqrt(count);
        m_meanBin[ibin] = mean;
        m_rmsBin[ibin] = rms;
        m_meanErrBin[ibin] = meanErr;
        printf("ibin: %d, entries: %.0f, mean: %.3f +/- %.3f, rms: %.3f\n",
               ibin+1, count, mean, meanErr, rms);
    }
}

Int_t biasMapTools::getBin(vector<Int_t> &bins, vector<Int_t> &Nbins)
{
    Int_t prod = 1;
    Int_t ret = bins[0];
    for (Int_t idim = 1; idim < (Int_t)Nbins.size(); ++idim)
    {
        prod *= Nbins[idim - 1];
        ret += (bins[idim] - 1) * prod;
    }
    return ret;
}

vector<Int_t> biasMapTools::getBinIndices(Int_t ibin, vector<Int_t> &Nbins)
{
    vector<Int_t> ret(Nbins.size(), 0);
    Int_t prod = 1.;
    for (Int_t idim = 0; idim < (Int_t)Nbins.size() - 1; ++idim)
        prod *= Nbins[idim];
    for (Int_t idim = (Int_t)Nbins.size() - 1; idim >= 0; --idim)
    {
        int ratio = ibin / prod;
        int mod = ibin % prod;
        if (mod == 0)
            ret[idim] = ibin / prod;
        else
            ret[idim] = ibin / prod + (idim ? 1 : 0);
        // printf("prod: %d, ret: %d, ibin: %d idim: %d\n", prod, ret[idim], ibin, idim);
        ibin = ibin - prod * (ret[idim] - 1);
        if (idim > 0)
            prod = prod / Nbins[idim - 1];
    }
    // printf("prod: %d, ibin: %d\n", prod, ibin);
    return ret;
}

void biasMapTools::exportBiasMaps(TString pathOut)
{
    TString nfout = Form("%s/biases_%s.txt", pathOut.Data(), m_tag_data_test.Data());
    FILE *pFile = fopen(nfout.Data(), "w");
    for (vector<Double_t> binning : m_binnings)
    {
        for (Double_t bin : binning)
        {
            fprintf(pFile, "%g, ", bin);
        }
        fprintf(pFile, "\n");
    }
    for (auto bias : m_meanBin)
        fprintf(pFile, "%g, ", bias);
    fprintf(pFile, "\n");
    for (auto biasErr : m_meanErrBin)
        fprintf(pFile, "%g, ", biasErr);
    fprintf(pFile, "\n");
    for (auto count : m_countBin)
        fprintf(pFile, "%d, ", count);
    fprintf(pFile, "\n");
    fclose(pFile);
}

biasMapTools::biasMapTools(TString tag_test, TString tag_data, vector<TString> tag_vars, TString nfin)
{
    biasMapTools();
    m_tag_test = tag_test;
    m_tag_data = tag_data;
    m_tag_data_test = m_tag_data + "_" + m_tag_test;
    m_tag_vars = tag_vars;
    m_Nvars = (Int_t)(m_tag_vars.size());
    m_binnings = vector<vector<Double_t>>(m_Nvars, vector<Double_t>());
    m_Nbins = vector<Int_t>(m_Nvars, 0);
    vars = vector<Double_t>(m_Nvars, 0.);
    importBiasMaps(nfin);
}

void biasMapTools::importBiasMaps(TString nfin){
    ifstream is(nfin.Data());
    TString line;
    for (int iVar=0; iVar<m_Nvars; ++iVar){
        line.ReadToDelim(is, '\n');
        // printf("iVar: %d\n line: %s\n", iVar, line.Data());
        TObjArray* binLimits = line.Tokenize(", ");
        m_Nbins[iVar] = binLimits->GetEntries() - 1;
        
        for (int iLim = 0; iLim < m_Nbins[iVar]+1; ++iLim){
            double binLim = ((TObjString *)binLimits->At(iLim))->String().Atof();
            m_binnings[iVar].push_back(binLim);
            //printf(" %g ", binLim);
        }
       // printf("\n");
    }
    m_NbinsTot = 1;
    for_each(m_Nbins.begin(), m_Nbins.end(), [this](Int_t Nbins){ 
        this->m_NbinsTot *= Nbins;
    });
    m_meanBin.clear();
    m_meanBin = vector<Double_t>(m_NbinsTot,0);
    m_meanErrBin.clear();
    m_meanErrBin = vector<Double_t>(m_NbinsTot, 0);
    m_rmsBin.clear();
    m_rmsBin = vector<Double_t>(m_NbinsTot, 0);
    m_countBin.clear();
    m_countBin = vector<Int_t>(m_NbinsTot, 0);
    m_sumX.clear();
    m_sumX = vector<Double_t>(m_NbinsTot, 0);
    m_sumX2.clear();
    m_sumX2 = vector<Double_t>(m_NbinsTot, 0);

    //bias
    line.ReadToDelim(is, '\n');
    //printf("biases: %s\n", line.Data()); 
    TObjArray *biases = line.Tokenize(", ");
    for (int iBias = 0; iBias < m_NbinsTot; ++iBias){
        double bias = ((TObjString *)biases->At(iBias))->String().Atof();
        m_meanBin[iBias] = bias;
        //printf("**** %g ", bias);
    }
    //printf("\n");

    // biasErr
    line.ReadToDelim(is, '\n');
    //printf("biasesErr: %s\n", line.Data());
    TObjArray *biasesErr = line.Tokenize(", ");
    for (int iBias = 0; iBias < m_NbinsTot; ++iBias)
    {
        double biasErr = ((TObjString *)biasesErr->At(iBias))->String().Atof();
        m_meanErrBin[iBias] = biasErr;
        // printf("**** %g ", biasErr);
    }
    // printf("\n");
}

Double_t biasMapTools::getBias(){
    auto bins = this->getBinND(this->vars);
    auto ibin = this->getBin(bins);
    return m_meanBin[ibin-1];
}

Double_t biasMapTools::getBiasErr(){
    auto bins = this->getBinND(this->vars);
    auto ibin = this->getBin(bins);
    return m_meanErrBin[ibin - 1];
}

#endif