import sys

modes = ['Bs2Dspi', 'Bd2Dpi']
combs = ['comb', 'uncomb', 'combAUTO']

argc = len(sys.argv)
if argc != 3:
    print 'wrong number of arguments (%d given, 2 required)'%(argc-1)
    exit()
mode = sys.argv[1]
comb = sys.argv[2]

if mode not in modes:
    print 'wrong mode option (%s)' %s
    print 'available options are: %s'%modes
    exit()
if comb not in combs:
    print 'wrong combination option (%s)' %s
    print 'available options are: %s'%combs
    exit()
##############################################################

translate1 = {
    'newTags' : {
        'OS_Muon'     : 'lab0_OSMuonLatest_TAGETA', 
        'OS_Electron' : 'lab0_OSElectronLatest_TAGETA', 
        'OS_Charm'    : 'lab0_OSCharm_TAGETA',
        'OS_Kaon'     : 'lab0_OSKaonLatest_TAGETA', 
        'VtxCharge'   : 'lab0_OSVtxCh_TAGETA', 
        'SS_Kaon'     : 'lab0_SSKaonLatest_TAGETA',
        'SS_Pion'     : 'lab0_SSPion_TAGETA', 
        'SS_Proton'   : 'lab0_SSProton_TAGETA'
    },
    'oldTags' : {
        'OS_Muon'     : 'lab0_OSMuon_TAGETA', 
        'OS_Electron' : 'lab0_OSElectron_TAGETA', 
        'OS_Charm'    : 'lab0_OSCharm_TAGETA',
        'OS_Kaon'     : 'lab0_OSKaon_TAGETA', 
        'VtxCharge'   : 'lab0_OSVtxCh_TAGETA', 
        'SS_Kaon'     : 'lab0_SSKaon_TAGETA',
        'SS_Pion'     : 'lab0_SSPion_TAGETA', 
        'SS_Proton'   : 'lab0_SSProton_TAGETA'
    }
}
translate2 = {
    'newTags' : {
        'OS_Charm'    : 'etaOS',
        'OS_Electron' : 'etaSS'
    },
    'oldTags' : {
        'OS_Charm'    : 'etaOS_old',
        'OS_Electron' : 'etaSS_old'
    }
}
translate3 = {
    'newTags' : {
        'OS_Combination' : 'etaOS',
        'SS_Combination' : 'etaSS'
    },
    'oldTags' : {
        'OS_Combination' : 'etaOS_old',
        'SS_Combination' : 'etaSS_old'
    }
}
tags = []
ncomb= []
translate = {}
if comb == 'combAUTO':
    tags = ['OS_Combination', 'SS_Combination']
    ncomb= ['_combinedAUTO', '_TagComb']
    translate = translate3
elif comb == 'comb':
    tags = ['OS_Charm', 'OS_Electron']
    ncomb= ['_combined', '_TagComb']
    translate = translate2
elif comb == 'uncomb':
    tags = ['OS_Muon', 'OS_Electron', 'OS_Charm',
            'OS_Kaon', 'VtxCharge', 'SS_Kaon',
            'SS_Pion', 'SS_Proton']
    ncomb= ['', '']
    translate = translate1

#################################################################
#################################################################
#################################################################
import ROOT
ROOT.gROOT.SetBatch()


pathMode = '../%s_calib'%mode
for year in ['2015and2016','2015', '2016', '2017', '2018', 'All']:
#for year in ['2015', '2016', '2017', '2018', 'All']:
    for vtag in ['oldTags', 'newTags']:
        
        ndir = '%s/EPMout_%s_%s%s'%(pathMode,year,vtag,ncomb[0])
        fin =  ROOT.TFile(ndir+'/EspressoHistograms.root')
        for tag in tags:
            canv1 = fin.Get(tag+'_Calibration')
            canv3 = canv1.Clone(tag+'_CalibrationEtaDist')
            canv3.SetName(tag+'_CalibrationEtaDist')
            canv3.cd()
            nfin = '%s/data/{year}/Mag{mag}/B2DX_{year}_{mag}_%s_sWeight%s.root'%(pathMode, mode, ncomb[1])
            chain = ROOT.TChain('DecayTree')
            convert_years = {'2015' : ['2015'],
                             '2016' : ['2016'],
                             '2017' : ['2017'],
                             '2018' : ['2018'],
                             '2015and2016' : ['2015','2016'],
                             'All' : ['2015','2016', '2017', '2018'],
            }
            for convert_year in convert_years[year]:
                chain.Add(nfin.format(mag='Up', year=convert_year))
                chain.Add(nfin.format(mag='Dw', year=convert_year))
            nhist = 'h_eta_%s_%s_%s'%(year,vtag,tag)
            h2 = ROOT.TH1D(nhist, nhist, 80, 0, 0.5);
            chain.Draw(translate[vtag][tag]+'>>'+nhist, 'sWeight', 'goff')
            rightmax = 1.1*h2.GetMaximum()
            if rightmax<0.0001: 
                canv3.SaveAs('EPMout_%s_%s%s/%s.pdf'%(year,vtag,canv3.GetName()))
                continue
            c2 = canv3.GetPrimitive(tag+'_Calibration_c2')
            c1 = canv3.GetPrimitive(tag+'_Calibration_c1')
            d1 = canv3.GetPrimitive(tag+'_Calibration_d1')
            c2.GetXaxis().SetLimits(0,0.5)
            c2.GetYaxis().SetRangeUser(0,0.5)
            c1.GetXaxis().SetLimits(0,0.5)
            c1.GetYaxis().SetRangeUser(0,0.5)
            d1.GetXaxis().SetLimits(0,0.5)
            d1.GetYaxis().SetRangeUser(0,0.5)
            canv3.Clear()
            canv3.Draw()
            pad = canv3.GetPad(0)
            scale = pad.GetUymax()/rightmax*0.5
            h2.SetLineColor(ROOT.kGray)
            h2.SetMarkerColor(ROOT.kGray)
            h2.Scale(scale)
            h2.Draw('hist same')
            '''
            axis = ROOT.TGaxis(pad.GetUxmax(),pad.GetUymin(),
            pad.GetUxmax(), pad.GetUymax(),0,rightmax,510,"+L");
            axis.SetLineColor(ROOT.kGray);
            axis.SetTextColor(ROOT.kGray);
            axis.SetLabelColor(ROOT.kGray);
            axis.Draw();
            '''
            canv3.Print()
            #canv3.ls()
            canv3.SaveAs('%s/%s.pdf'%(ndir,canv3.GetName()))
