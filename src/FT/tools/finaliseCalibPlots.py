import sys

modes = ['Bs2Dspi', 'Bd2Dpi']
combs = ['comb', 'uncomb', 'combAUTO']

argc = len(sys.argv)
if argc != 5:
    print 'wrong number of arguments (%d given, 4 required)'%(argc-1)
    exit()
mode = sys.argv[1]
year = sys.argv[2]
comb = sys.argv[3]

if mode not in modes:
    print 'wrong mode option (%s)' %s
    print 'available options are: %s'%modes
    exit()
if comb not in combs:
    print 'wrong combination option (%s)' %s
    print 'available options are: %s'%combs
    exit()
cutTags = sys.argv[4].split('-')
print cutTags, sys.argv[4]
cutTag = cutTags[0]
if cutTag == 'empty': cutTag='' 
inCutTag = ''
if len(cutTags)>1:
    inCutTag = cutTags[1]
print(mode, year, comb, cutTag, inCutTag)
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
#    tags = ['OS_Combination']
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

translate_cutTag = {
    ''     : '1',
    '_PT1' : 'lab0_PT<10000',
    '_PT2' : 'lab0_PT>10000',
    '_half0' : 'eventNumber%2==0',
    '_half0.PT1' : 'eventNumber%2==0&&lab0_PT<10000',
    '_half0.PT2' : 'eventNumber%2==0&&lab0_PT>10000',
    '_half1' : 'eventNumber%2==1',
    '_half1.PT1' : 'eventNumber%2==1&&lab0_PT<10000',
    '_half1.PT2' : 'eventNumber%2==1&&lab0_PT>10000',    
}
#################################################################
#################################################################
#################################################################
import ROOT
ROOT.gROOT.SetBatch()
from array import array
def getMeans(tin, nbranch_eta, nbranch_q, p0, p1):
    print('********** ', nbranch_eta, nbranch_q)
    eta     = array('d', [0.])
    q       = array('i', [0])
    sWeight = array('d', [0.])
    wPT     = array('d', [0.])
    tin.SetBranchAddress(nbranch_eta, eta)
    tin.SetBranchAddress(nbranch_q, q)
    tin.SetBranchAddress('sWeight', sWeight)
    tin.SetBranchAddress('wPT', wPT)


    nentries = tin.GetEntries()
    print('Entries: ', nentries)
    eta_mean=0.
    tot=0.
    tot_tagged= 0.
    for i in list(range(0, nentries)):
        tin.GetEntry(i)
        weight = sWeight[0]*wPT[0]
        if eta[0]>=0.5: q[0]=0
        tot       += weight
        tot_tagged   += weight*abs(q[0])
        eta_mean     += weight*abs(q[0])*eta[0]
#        print('-----',i, weight,leaf_sw.GetValue(), leaf_wPT.GetValue(),  q, eta, tot, tot_tagged, eta_mean)
    eff_mean = tot_tagged/tot
    eta_mean = eta_mean/tot_tagged
    omega_mean=0.
    power_mean=0.
    for i in list(range(0, nentries)):
        tin.GetEntry(i)
        weight = sWeight[0]*wPT[0]
        if eta[0]>=0.5: q[0]=0
        omega  = p0+eta_mean+p1*(eta[0]-eta_mean)
        D2     = (1.0-2.0*omega)*(1.0-2.0*omega)
        omega_mean += weight*abs(q[0])*omega
        power_mean += weight*abs(q[0])*D2

    omega_mean = omega_mean/tot_tagged
    power_mean = power_mean/tot

    return eff_mean, eta_mean, omega_mean, power_mean

def getCalibParams(mode, year, ncomb, vtag, tag, cutTag):
    nfin = '../%s_calib/EPMout_%s_%s%s%s/EspressoCalibrations.py'%(mode,year,vtag,ncomb[0],cutTag)
    fin = open(nfin)
    lines = fin.read().split('\n')[:-1]
#    print(lines)
    print('********** ', tag)
    eta=0.
    p0=0.
    p0err=0.
    p1=0.
    p1err=0.
    for line in lines:
        if tag not in line: continue
        if   tag+'_Eta'   in line: eta   = float(line.split(' ')[-1])
        elif tag+'_P0Err' in line:  p0err= float(line.split(' ')[-1])
        elif tag+'_P0'    in line:  p0   = float(line.split(' ')[-1])
        elif tag+'_P1Err' in line:  p1err= float(line.split(' ')[-1])
        elif tag+'_P1'    in line:  p1   = float(line.split(' ')[-1])
        
    print('>>>>>> ',eta, p0, p0err, p1, p1err)
    fin.close()
    return eta, p0, p0err, p1, p1err
#########################################################################################3
pathMode = '../%s_calib'%mode
for vtag in ['oldTags', 'newTags']:
    ndir = '%s/EPMout_%s_%s%s%s'%(pathMode,year,vtag,ncomb[0],cutTag)
    fin =  ROOT.TFile(ndir+'/EspressoHistograms.root')
    print fin
    if not fin: 
        print 'ERROR: file "%s" not found'%(ndir+'/EspressoHistograms.root')
        continue
    #fin.ls()
    for tag in tags:
        canv3 = 0
        canv1 = fin.Get(tag+'_Calibration')
        failed = not canv1
            
        if failed:
            print 'Calibration Failed'
            canv3 = ROOT.TCanvas(tag+'_CalibrationEtaDist',tag+'_CalibrationEtaDist', 796, 772)
        else:
            canv3 = canv1.Clone(tag+'_CalibrationEtaDist')            
            
        #canv3 = canv1.Clone(tag+'_CalibrationEtaDist')
        canv3.SetName(tag+'_CalibrationEtaDist')
        canv3.cd()
        nfin = '%s/data/{year}/Mag{mag}/B2DX_{year}_{mag}_%s_sWeight_wPT%s%s.root'%(pathMode, mode, ncomb[1], inCutTag)
        #print nfin
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
        
        print(translate_cutTag[cutTag])
        nDec = ''
        if   'eta' in translate[vtag][tag]: nDec=translate[vtag][tag].replace('eta', 'q')
        elif 'ETA' in translate[vtag][tag]: nDec=translate[vtag][tag].replace('ETA', 'DEC')         
    #      print(nDec)
        ## EFF MEAN
        nhist_dec = 'h_dec_%s_%s_%s'%(year,vtag,tag)
        hDec = ROOT.TH1D(nhist_dec, nhist_dec, 2, -0.5, 1.5);
        chain.Draw('abs('+nDec+')>>'+nhist_dec, 'sWeight*wPT*(%s)'%translate_cutTag[cutTag], 'goff')
        effMean = hDec.GetMean();
 #       print('eff Mean', effMean)

        ## ETA MEAN
        nhist_eta = 'h_eta_%s_%s_%s'%(year,vtag,tag)
        hEta = ROOT.TH1D(nhist_eta, nhist_eta, 100, 0, 0.5);
#        print(translate[vtag][tag])
        chain.Draw(translate[vtag][tag]+'>>'+nhist_eta, 'sWeight*wPT*(%s)'%translate_cutTag[cutTag], 'goff')
        etaMean = hEta.GetMean();
#        print('ETA MEAN:', etaMean)
        rightmax = 1.1*hEta.GetMaximum()
        scale = 1
        

        etaMean2, p0, p0err, p1, p1err = getCalibParams(mode, year, ncomb, vtag, tag, cutTag)
        
        ## OMEGA MEAN
        nhist_Omega = 'h_Omega_%s_%s_%s'%(year,vtag,tag)
        hOmega = ROOT.TH1D(nhist_Omega, nhist_Omega, 100, 0, 1);
        nOmega = '%f+%f+%f*(%s-%f)'%(p0, etaMean, p1, translate[vtag][tag], etaMean)
        #print(nOmega)
        chain.Draw('abs('+nOmega+')>>'+nhist_Omega, 'sWeight*wPT*(%s && %s!=0)'%(translate_cutTag[cutTag], nDec), 'goff')
        omegaMean = hOmega.GetMean();
 #       print('omega Mean', omegaMean)

        ## POWER
        nhist_power = 'h_power_%s_%s_%s'%(year,vtag,tag)
        hpower = ROOT.TH1D(nhist_power, nhist_power, 100, 0, 1);
        npower = 'abs(%s)*(1-2*(%s))**2'%(nDec, nOmega)
        #print(npower)
        chain.Draw(npower+'>>'+nhist_power, 'sWeight*wPT*(%s)'%translate_cutTag[cutTag], 'goff')
        powerMean = hpower.GetMean();
        #hpower.Print()
  #      print('power Mean', powerMean)

        eff_mean, eta_mean, omega_mean, power_mean = getMeans(chain, translate[vtag][tag], nDec, p0, p1)
        print('HIST', effMean, etaMean, omegaMean, powerMean)
        print('LOOP', eff_mean, eta_mean, omega_mean, power_mean)

        if not failed:
            if rightmax<0.0001: 
                canv3.SaveAs('%s/%s.pdf'%(ndir,canv3.GetName()))
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
            hEta.SetLineColor(ROOT.kBlue)
            hEta.SetLineWidth(3)
            hEta.SetMarkerColor(ROOT.kBlue)
            hEta.SetMarkerStyle(20)
            hEta.Scale(scale)
            '''
            Box = ROOT.TPaveText(ROOT.gStyle.GetPadLeftMargin() + 0.06,
                                 0.80 - ROOT.gStyle.GetPadTopMargin(),
                                 ROOT.gStyle.GetPadLeftMargin() + 0.40,
                                 0.97 - ROOT.gStyle.GetPadTopMargin(),
                                 "BRNDC");
            Box.SetTextAlign(12)
            Box.SetBorderSize(0)
            Box.SetTextFont(132)
            Box.SetTextColor(1)
            Box.SetTextSize(0.05)
            Box.SetTextAlign(12)
            Box.AddText('#hat{#eta}: %.5f\n'%(eta_mean))
            Box.AddText('#hat{#omega}: %.5f\n'%(omega_mean))
            Box.AddText('#hat{#epsilon}: %.5f\n'%(eff_mean))
            Box.AddText('<|q|(1-2#omega)^{2}>: %.5f\n'%(power_mean))
            Box.Draw('same')
            '''
            hEta.Draw('hist same')
            #Box.SetFillColor(ROOT.kWhite)
            #canv3.Modified()
        else:
            canv3.cd()
            hEta.SetLineColor(ROOT.kBlue)
            hEta.SetMarkerColor(ROOT.kBlue)
            hEta.Scale(scale)
            hEta.Draw('P')
            msg = ROOT.TPaveText(0.3, 0.45, 0.6, 0.55)
            msg.AddText("Calibration Failed")
            msg.Draw("same")
            
        canv3.SaveAs('%s/results/EPMout_%s_%s%s%s__%s.pdf'%(pathMode,year,vtag,ncomb[0],cutTag,canv3.GetName()))
        #canv3.SaveAs('%s/results/EPMout_%s_%s%s%s__%s.png'%(pathMode,year,vtag,ncomb[0],cutTag,canv3.GetName()))
