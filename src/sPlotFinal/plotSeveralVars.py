#source /cvmfs/sft.cern.ch/lcg/views/LCG_105/x86_64-centos7-gcc12-opt/setup.sh

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-iG','--inputG', type=str, dest = 'inputG')
parser.add_argument('-iB','--inputB', type=str, dest = 'inputB')
parser.add_argument('-iR','--inputR', type=str, dest = 'inputR', default = '')
parser.add_argument('-o','--outFile', type = str, dest = 'outFile', default = 'output_compare.root')
parser.add_argument('-d','--dir', type = str, dest = 'dir', default = './')
parser.add_argument('-rw','--reweight', type = str, dest = 'reweight', default = '')
args = parser.parse_args()
do_reweight = (args.reweight != '')
inputRisMassCut = (args.inputR == '')

import ROOT
ROOT.gROOT.SetBatch(True)
# ROOT.EnableImplicitMT()
# fout = ROOT.TFile.Open(args.outFile, 'RECREATE')

def defineAll(df):
    df = df.Define('logPiplusIPCHI2', 'log(piplusIPCHI2)').Define('logBIPCHI2', 'log(bIPCHI2)').Define('logBVTXCHI2', 'log(bVTXCHI2)').Define('acosBDIRA', 'acos(bDIRA)').Define('logBFDCHI2', 'log(bFDCHI2)')
    df = df.Define('bIPCHI2overIP', 'bIPCHI2/bIP').Define('piplusIPCHI2overIP', 'piplusIPCHI2/piplusIP').Define('logPiplusGhostProb', 'log(piplusGhostProb)')
    df = df.Define('logBIP2overIPCHI2', 'log(bIP*bIP/bIPCHI2)').Define('logPiplusIP2overIPCHI2', 'log(piplusIP*piplusIP/piplusIPCHI2)')
    return df



ROOT.gInterpreter.Declare("""
ROOT::RDF::RNode MyTransformation(ROOT::RDF::RNode df0,ROOT::RDF::RNode dfT,int Nbins, double vmin, double vmax, TString previous_weight="", TString nfout="test.root") {
    TFile fout(nfout,"RECREATE");
    auto h0 = df0.Histo1D({"h0_reweight","h0_reweight",Nbins,vmin,vmax},"reweight_var",previous_weight);
    h0->Scale(1.0/h0->Integral());
    h0->Print();
    auto hT = dfT.Histo1D({"hT_reweight","hT_reweight",Nbins,vmin,vmax},"reweight_var",previous_weight);
    hT->Scale(1.0/hT->Integral());
    hT->Print();
    TH1D hR("h_ratio", "h_ratio",Nbins,vmin,vmax);
    hR.Divide(hT.GetPtr(), h0.GetPtr());    
    hR.Print();
    if (previous_weight == ""){
        auto getWeight = [&hR](double x){ return hR.GetBinContent(hR.FindBin(x)); };
        df0 = df0.Define("reweight", getWeight, {"reweight_var"});
    } else {
        auto getWeight = [&hR](double x, double w){ return hR.GetBinContent(hR.FindBin(x))*w; };
        df0 = df0.Define("reweight", getWeight, {"reweight_var", previous_weight.Data()});
    }
    df0.Display("reweight")->Print();
    auto h1 = df0.Histo1D({"h1_reweight","h1_reweight",Nbins,vmin,vmax},"reweight_var","reweight");
    auto hrew = df0.Histo1D({"h_reweight","h_reweight",Nbins,-5,5},"reweight");
    fout.WriteTObject(h0.GetPtr());
    fout.WriteTObject(hT.GetPtr());
    fout.WriteTObject(&hR);
    fout.WriteTObject(h1.GetPtr());
    fout.WriteTObject(hrew.GetPtr());
    fout.ls();
    fout.Close();
    return df0;
}
""" )

    
def reweight1D(df0, dfT, nvar, vmin, vmax, Nbins=150, previous_weight='', nfout='test.root'):
    print(nvar)
    return df0

rewFunct = lambda x : x+0.5

dfMC = ROOT.RDataFrame('b2hh', args.inputG)
dfMC = defineAll(dfMC)
dfSW = ROOT.RDataFrame('b2hh', args.inputB)
dfSW = defineAll(dfSW)
dfMB = None
if inputRisMassCut:
    dfMB = dfSW.Filter('massKK>5.3 && massKK<5.45')
else:
    dfMB = ROOT.RDataFrame('b2hh', args.inputR)
    dfMB = defineAll(dfMB)    
    
if do_reweight:
    nvar = args.reweight
    Nbins = 150
    vmin = -9.5
    vmax = -6
    dfMC = dfMC.Define('reweight_var', nvar)
    dfSW = dfSW.Define('reweight_var', nvar)
    dfMB = dfMB.Define('reweight_var', nvar)
    dfSW = dfSW.Define('reweight', rewFunct, ['reweight_var'])    
    dfMB = dfMB.Define('reweight', rewFunct, ['reweight_var'])    
    # dfSW = ROOT.MyTransformation(ROOT.RDF.AsRNode(dfSW),ROOT.RDF.AsRNode(dfMC), 
    #                              Nbins,vmin,vmax,
    #                              'weight','rewSW.root')
    # dfMB = ROOT.MyTransformation(ROOT.RDF.AsRNode(dfMB),ROOT.RDF.AsRNode(dfMC), 
    #                              Nbins,vmin,vmax,
    #                              '' if inputRisMassCut else 'weight', 'rewMB.root')
    
    
var_list = [
    ('massKK', '_massKK', 'massKK; m(B^{0}_{s})', 100, 5.0, 6.2),
    ('nPVs', '_nPVs', 'nPVs; Number of PV', 9, 0.5, 9.5),
    ('nTracks', '_nTracks', 'nTracks; Number of Tracks', 100, 0, 500),
    ('tauKK', '_tauKK', 'tauKK; tauKK [ps]', 200, 0, 8),
    ('tauKKErr', '_tauKKErr', 'tauKKErr; tauKKErr [ps]', 200, 0, 0.1),
    ('bPT', '_bPT', 'bPT; p_{T}(B_{s}^{0}) [GeV]', 100, 0, 25),
    ('piplusPT', '_piplusPT', 'piplusPT; p_{T}(#pi^{+}) [GeV]', 100, 0, 15), 
    ('bPVx', '_bPVx', 'bPVx; x(PV) [mm]', 200, 0.70, 0.95),
    ('bPVy', '_bPVy', 'bPVy; y(PV) [mm]', 200, -0.3, 0.3),
    ('bPVz', '_bPVz', 'bPVz; z(PV) [mm]', 200, -120, 120),
    ('bENDVx', '_bENDVx', 'bENDVx; x(ENDV) [mm]', 100, -3, 4),
    ('bENDVy', '_bENDVy', 'bENDVy; y(ENDV) [mm]', 150, -3, 3),
    ('bENDVz', '_bENDVz', 'bENDVz; z(ENDV) [mm]', 150, -150, 150),
    ('bPVxErr', '_bPVxErr', 'bPVxErr; #delta x(PV) [mm]', 150, 0, 0.025),
    ('bPVyErr', '_bPVyErr', 'bPVyErr; #delta y(PV) [mm]', 150, 0, 0.025),
    ('bPVzErr', '_bPVzErr', 'bPVzErr; #delta z(PV) [mm]', 200, 0, 0.15),
    ('bENDVxErr', '_bENDVxErr', 'bENDVxErr; #delta x(ENDV) [mm]', 150, 0.004, 0.04),
    ('bENDVyErr', '_bENDVyErr', 'bENDVyErr; #delta y(ENDV) [mm]', 150, 0.004, 0.04),
    ('bENDVzErr', '_bENDVzErr', 'bENDVzErr; #delta z(ENDV) [mm]', 200, 0.02, 0.50),
    ('rFD', '_rFD', 'rFD; rFD [mm]', 100, 0, 4),
    ('rFDPV', '_rFDPV', 'rFDPV; rFDPV [mm]', 100, 0, 4),
    ('bFD', '_bFD', 'bFD; FD(B^{0}_{s})', 150, 0, 50),
    
    ('etaOS', '_etaOS', 'etaOS; #eta_{OS}', 70, 0, 0.499),
    ('etaSSk', '_etaSSk', 'etaSSk; #eta_{SSk}', 75, 0, 0.499),
    ('qOS', '_qOS', 'qOS; q_{OS}', 3, -1.5, 1.5),
    ('qSSk', '_qSSk', 'qSSk; q_{SSk}', 3, -1.5, 1.5),
    ('piplusETA', '_piplusETA', 'piplusETA; #eta(#pi^{+})', 90, 1.5, 5), 
    ('piplusPHI', '_piplusPHI', 'piplusPHI; #phi(#pi^{+})', 90, -3.14159, 3.14159),
    ('bETA', '_bETA', 'bETA; #eta(B^{0}_{s})', 100, 1.5, 5), 
    ('bPHI', '_bPHI', 'bPHI; #phi(B^{0}_{s})', 85, -3.14159, 3.14159),
    ('logPiplusIPCHI2', '_piplusIPCHI2', 'piplusIPCHI2; log[#chi^{2}_{IP}(#pi^{+})]', 100, 2, 12),
    ('piplusTRACKCHI2', '_piplusTRACKCHI2', 'piplusTRACKCHI2; #chi^{2}_{track}(#pi^{+})', 200, 0, 3),
    ('logBIPCHI2', '_bIPCHI2', 'bIPCHI2; log[#chi^{2}_{IP}(B_{s}^{0})]', 100, -6, 3),
    ('logBFDCHI2', '_bFDCHI2', 'bFDCHI2; log[#chi^{2}_{FD}(B_{s}^{0})]', 100, 4, 14),
    ('bDOCA', '_bDOCA', 'bDOCA; DOCA(B^{0}_{s})', 100, 0, 0.1),
    ('bPVCHI2', '_bPVCHI2', 'bPVCHI2; #chi^{2}_{PV}(B_{s}^{0})', 100, 0, 130),
    ('logBVTXCHI2', '_bVTXCHI2', 'bVTXCHI2; log[#chi^{2}_{VTX}(B_{s}^{0})]', 100, -10, 3),
    ('acosBDIRA', '_bDIRA', 'bDIRA; acos(B^{0}_{s} direction angle)', 100, 0, 0.015),
    ('bIP', '_bIP', 'bIP; IP(B^{0}_{s})', 100, 0, 0.08),
    ('bIPCHI2overIP', '_bIPCHI2overIP', 'bIPCHI2overIP; #chi^{2}_{IP}/IP (B^{0}_{s})', 100, 0, 350),
    ('logBIP2overIPCHI2', '_logBIP2overIPCHI2', 'logBIP2overIPCHI2; log(IP^{2}/#chi^{2}_{IP}) (B^{0}_{s})', 100, -9.5, -6),
    ('piplusIP', '_piplusIP', 'piplusIP; IP(#pi^{+})', 100, 0, 3),
    ('logPiplusGhostProb', '_piplusGhostProb', 'piplusGhostProb; log[Ghost Prob. (#pi^{+})]', 200, -7, -1),
    ('piplusIPCHI2overIP', '_piplusIPCHI2overIP', 'piplusIPCHI2overIP; #chi^{2}_{IP}/IP (#pi^{+})', 100, 0, 8000),
    ('logPiplusIP2overIPCHI2', '_logPiplusIP2overIPCHI2', 'logPiplusIP2overIPCHI2; log(IP^{2}/#chi^{2}_{IP}) (#pi^{+})', 100, -10, -4),
    ('piplusDLLKPI', '_piplusDLLKPI', 'piplusDLLKPI; DLLKPI (#pi^{+})', 200, 0, 100),
    ('piplusDLLPPI', '_piplusDLLPPI', 'piplusDLLPPI; DLLPPI (#pi^{+})', 200, -100, 70),
    ('bdtKK', '_bdtKK', 'bdtKK; bdtKK', 100, 0.08, 0.7),
]


########################################
########################################
########################################
########################################

ROOT.gROOT.ProcessLine(".L ${B2HH_SRC}/Tools/lhcbStyle.C")
#ROOT.gStyle.SetLabelSize(0.02, "x")
ROOT.gStyle.SetTitleSize(0.06, "x")
ROOT.gStyle.SetOptStat(0)

def  makeCanvas(hSW, hMC, hMB=None, name=''):
    hSW.SetLineColor(ROOT.kBlue)
    hSW.SetMarkerColor(ROOT.kBlue)
    hSW.SetMarkerStyle(0)
    if ('OS' not in name) and ('SS' not in name) and ('DLL' not in name) and ('nTracks' not in name):
        hSW.GetXaxis().SetRange(-1, hSW.GetNbinsX()+1);
    hSW.Scale(1.0/hSW.Integral())
    
    hMC.SetLineColor(ROOT.kGreen+2)
    hMC.SetMarkerColor(ROOT.kGreen+2)
    hMC.SetMarkerStyle(0)
    if ('OS' not in name) and ('SS' not in name) and ('DLL' not in name):
        hMC.GetXaxis().SetRange(-1, hMC.GetNbinsX()+1);
    hMC.Scale(1.0/hMC.Integral())
    
    hRatio = ROOT.TH1D('hRatio_'+name, 'hRatio_'+name, 
                    hSW.GetXaxis().GetNbins(),
                    hSW.GetXaxis().GetXmin(),
                    hSW.GetXaxis().GetXmax())
    hRatio.GetXaxis().SetTitle("")
    hRatio.GetYaxis().SetTitle('DATA / MC')
    hRatio.Add(hSW)
    hRatio.Divide(hMC)
    hRatio.SetMinimum(0.5)
    hRatio.SetMaximum(1.5)
    hRatio.SetLineColor(ROOT.kBlue)
    hRatio.SetMarkerColor(ROOT.kBlue)
    hRatio.SetMarkerStyle(0)
    hRatio.GetXaxis().SetLabelSize(0.15)
    hRatio.GetYaxis().SetLabelSize(0.15)
    hRatio.GetYaxis().SetTitleSize(0.15)
    hRatio.GetYaxis().SetNdivisions(5,2,0,True)

    hRatio2 = None
    if hMB != None:
        hMB.SetLineColor(ROOT.kRed)
        hMB.SetLineWidth(1)
        hMB.SetMarkerColor(ROOT.kRed)
        hMB.SetMarkerStyle(0)
        if ('OS' not in name) and ('SS' not in name) and ('DLL' not in name):
            hMB.GetXaxis().SetRange(-1, hMB.GetNbinsX()+1);
        hMB.Scale(1.0/hMB.Integral())

        hRatio2 = ROOT.TH1D('hRatio2_'+name, 'hRatio2_'+name, 
                            hMB.GetXaxis().GetNbins(),
                            hMB.GetXaxis().GetXmin(),
                            hMB.GetXaxis().GetXmax())
        hRatio2.Add(hMB)
        hRatio2.Divide(hMC)
        hRatio2.SetLineColor(ROOT.kRed)
        hRatio2.SetLineWidth(1)
        hRatio2.SetMarkerColor(ROOT.kRed)
        hRatio2.SetMarkerStyle(0)

    tmpMax = max(hSW.GetMaximum(), hMC.GetMaximum())
    if 'mass' not in name:
        hSW.SetMinimum(0)
        hMC.SetMinimum(0)
    hSW.SetMaximum(tmpMax*1.05)
    hMC.SetMaximum(tmpMax*1.05)
    if hMB != None:
        tmpMax = max(tmpMax, hMB.GetMaximum())
        hSW.SetMaximum(tmpMax*1.05)
        hMC.SetMaximum(tmpMax*1.05)
        hMB.SetMaximum(tmpMax*1.05)
        if 'mass' not in name:
            hMB.SetMinimum(0)

    canv = ROOT.TCanvas('canv_'+name, 'canv_'+name)
    canv.cd()
    upperPad = canv.GetPad(0)
    upperPad = ROOT.TPad(name+"_upperPad",name+"_upperPad",0,0.2,1,1)
    upperPad.SetLeftMargin(0.2)
    upperPad.SetBottomMargin(0.15)
    upperPad.SetBorderSize(0)
    lowerPad = ROOT.TPad(name+"_lowerPad",name+"_lowerPad",0,0,1,0.2)
    lowerPad.SetLeftMargin(0.2)
    lowerPad.SetBorderSize(0)
    lowerPad.Draw()
    upperPad.Draw()
    upperPad.cd() 
    hSW.DrawCopy('pe')
    if hMB != None: hMB.DrawCopy('pe same')
    hMC.DrawCopy('hist same')
    upperPad.SetGridx()
    upperPad.SetGridy()
    lowerPad.cd()
    hRatio.DrawCopy('e1')
    if hRatio2 != None: hRatio2.DrawCopy('e1 same')
    l0 = ROOT.TLine(hRatio.GetXaxis().GetXmin(), 1, hRatio.GetXaxis().GetXmax(), 1)
    l0.SetLineColor(ROOT.kBlack)
    l0.SetLineStyle(ROOT.kSolid)
    l0.SetLineWidth(2)
    l0.DrawClone('same')
    lowerPad.SetGridx()
    lowerPad.SetGridy()
    return canv


from os import system
system(f'mkdir -p {args.dir}')
allhists = []


dfSW.Describe().Print()  
dfSW.Display('nPVs').Print()  
dfSW.Display('reweight_var').Print()  
if dfSW.HasColumn('reweight'):
    print('STOCAZZO')
else:
    print('FANCULO')
dfSW.Display('reweight').Print()  


for varname, hname, htitle, Nbins, varmin, varmax in var_list: 
    hMC = dfMC.Histo1D(('h_MC'+hname, 'h_MC'+htitle, Nbins, varmin, varmax), varname, 'weight')
    hSW = dfSW.Histo1D(('h_SW'+hname, 'h_SW'+htitle, Nbins, varmin, varmax), varname, 'reweight' if do_reweight else 'weight')
    hMB = None
    if do_reweight:
        hMB  = dfMB.Histo1D(('h_MB'+hname, 'h_MB'+htitle, Nbins, varmin, varmax), varname, 'reweight')
    elif inputRisMassCut:
        hMB  = dfMB.Histo1D(('h_MB'+hname, 'h_MB'+htitle, Nbins, varmin, varmax), varname)
    else:
        hMB  = dfMB.Histo1D(('h_MB'+hname, 'h_MB'+htitle, Nbins, varmin, varmax), varname, 'weight')
    
    
# print('Start making canvases')    
# for hname, hSW, hMC, hMB in allhists:
#     print(hname)
#     canv = makeCanvas(name=hname, hSW=hSW.GetValue(), hMC=hMC.GetValue(), hMB=hMB.GetValue())
#     canv.Draw()
#     canv.SaveAs(f'{args.dir}/{canv.GetName()}.pdf')
#     canv.SaveAs(f'{args.dir}/{canv.GetName()}.root')

#dfSW.Describe().Print()

# fout.Write()
# fout.Close()


'''
'massKK'
'nPVs',
'nTracks',
'tauKK',
'tauKKErr',
'bPT',
'piplusPT',
'bPVx',
'bPVy',
'bPVz',
'bENDVx',
'bENDVy',
'bENDVz',
'bPVxErr',
'bPVyErr',
'bPVzErr',
'bENDVxErr',
'bENDVyErr',
'bENDVzErr',
'rFD',
'rFDPV',
'bFD',

'etaOS',
'etaSSk',
'qOS',
'qSSk',
'piplusETA',
'piplusPHI',
'bETA',
'bPHI',
'piplusIPCHI2',
'piplusTRACKCHI2',
'bIPCHI2',
'bFDCHI2',
'bDOCA',
'bPVCHI2',
'bVTXCHI2',
'bDIRA',
'bIP',
'bIPCHI2overIP',
'logBIP2overIPCHI2',
'piplusIP',
'piplusGhostProb',
'piplusIPCHI2overIP',
'logPiplusIP2overIPCHI2',
'piplusDLLKPI',
'piplusDLLPPI',
    
'''