print('********************************************************')
print('********************************************************')
print('**                                                    **')
print('**                   B2HH FITTER                      **')
print('**                                                    **')
print('********************************************************')
print('********************************************************')


import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-u','--blindFlag', dest = 'blindFlag', action = 'store_true', default = False)
parser.add_argument('-n','--ncpu', type = int, dest = 'ncpu', default = 32)
parser.add_argument('-t','--tagger', nargs='+', dest = 'taggers', default = ['OS'])
parser.add_argument('-p','--plot', dest = 'plot', action = 'store_true', default = False)
parser.add_argument('-C','--conf', type = str, dest = 'conf', default = 'PIPI')
parser.add_argument('-s','--splitConf', type = str, dest = 'splitConf', default = '')
parser.add_argument('-y','--years', nargs='+', dest = 'years', default = ['201516'])
parser.add_argument('-m','--magnet', type = str, dest = 'magnet', default = 'Tot')
parser.add_argument('-b','--bdtCut', type = str, dest = 'bdtCut', default = '0.12')
parser.add_argument('-d','--outDir', type = str, dest = 'outDir', default = 'results_Template')
parser.add_argument('-r','--range', type = str, dest = 'range', default = 'total')
parser.add_argument('-f','--finalState', type = str, dest = 'finalState', default = 'PIPI')
parser.add_argument('-v','--var', type = str, dest = 'var', default = 'mass')
parser.add_argument('-B','--Btag', type = str, dest = 'Btag', default = 'tot')
parser.add_argument('-F','--Ftag', type = str, dest = 'Ftag', default = 'tot')
parser.add_argument('-A','--Atag', type = str, dest = 'Atag', default = 'OS')
parser.add_argument('-w','--wVar', type = str, dest = 'wVar', default = '' )
parser.add_argument('-V','--useTrueTau', dest = 'useTrueTau', action = 'store_true', default = False)
args = parser.parse_args()

useWeights = (not ('noWeights' in args.outDir))
isMC = ('MC_' in args.outDir)
if 'rew.' in args.outDir:
  args.wVar = args.outDir.split('rew.')[1]
  print('Reweight variable:', args.wVar)
doReweight = (args.wVar != '')
useTrueTag = (isMC and ('trueTag' in args.outDir))
import B2DXFitters
from B2DXFitters.WS import WS
import ROOT
from ROOT import RooFit, gROOT, gSystem, TFile, TTree, TCanvas
from ROOT import RooWorkspace, RooMsgService
from ROOT import RooAbsReal, RooRealVar, RooConstVar, RooCategory, RooProduct
from ROOT import RooDataSet, RooProdPdf,  RooAddPdf
from ROOT import RooArgSet, RooArgList
from math import log
# safe settings for numerical integration (if needed)
RooAbsReal.defaultIntegratorConfig().setEpsAbs(1e-9)
RooAbsReal.defaultIntegratorConfig().setEpsRel(1e-9)
RooAbsReal.defaultIntegratorConfig().getConfigSection(
    'RooAdaptiveGaussKronrodIntegrator1D').setCatLabel('method','15Points')
RooAbsReal.defaultIntegratorConfig().getConfigSection(
    'RooAdaptiveGaussKronrodIntegrator1D').setRealValue('maxSeg', 1000 )
RooAbsReal.defaultIntegratorConfig().method1D().setLabel(
    'RooAdaptiveGaussKronrodIntegrator1D')
RooAbsReal.defaultIntegratorConfig().method1DOpen().setLabel(
    'RooAdaptiveGaussKronrodIntegrator1D')

RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING);
for i in range(RooMsgService.instance().numStreams()) :
  RooMsgService.instance().getStream(i).removeTopic(RooFit.Integration);
  RooMsgService.instance().getStream(i).removeTopic(RooFit.Eval);
  RooMsgService.instance().getStream(i).removeTopic(RooFit.Plotting);

RooMsgService.instance().addStream(RooFit.INFO,RooFit.Topic(RooFit.Integration))
RooMsgService.instance().addStream(RooFit.DEBUG,RooFit.Topic(RooFit.Optimization))

gSystem.AddIncludePath(" -D__USE_XOPEN2K8 ")
gROOT.ProcessLine(".L ../Lib/RooTimeAccPdf.cxx+")
gROOT.ProcessLine(".L ../Lib/RooTimeAccPhysPdf.cxx+")
gROOT.ProcessLine(".L ../Lib/RooFcoshFSFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooFcosFSFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooFcoshFStoCPFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooFcosFStoCPFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooFcoshCPFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooFcosCPFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooFsinhCPFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooFsinCPFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooFcoshCPtoFSFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooFcosCPtoFSFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooFsinhCPtoFSFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooFsinCPtoFSFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooOmegaFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooOmegaFuncSS.cxx+")
gROOT.ProcessLine(".L ../Lib/RooSfitOmegaFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooOmegaBkgFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooOmegaBkgFuncNew.cxx+")
gROOT.ProcessLine(".L ../Lib/RooTagFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooTagFuncNew.cxx+")
gROOT.ProcessLine(".L ../Lib/RooJohnsonFunc.cxx+")
gROOT.ProcessLine(".L ../Lib/RooTimePdfBkg.cxx+")
gROOT.ProcessLine(".L ../Lib/RooTimePdfBkgNew.cxx+")
gROOT.ProcessLine(".L ../Lib/RooTimePdfBkgNew2.cxx+")
gROOT.ProcessLine(".L ../Lib/RooBDecaySpecial.cxx+")
gROOT.ProcessLine(".L ../Lib/RooBDecayNew.cxx+")
gROOT.ProcessLine(".L ../Lib/RooTimePdfPhysNew.cxx+")
gROOT.ProcessLine(".L ../Lib/RooTimePdfPhysNew2.cxx+")
gROOT.ProcessLine(".L ../Lib/RooExponentialNew.cxx+")
gROOT.ProcessLine(".L ../Lib/RooExponentialNew2.cxx+")
gROOT.ProcessLine(".L ../Lib/RooKeysPdfSpecial.cxx+")
print('Special RooFit classes imported')


#from configurationSplit import config as config
from configurations import configuration
# confModule = __import__('configuration{splitConf}'.format(splitConf=args.splitConf))
# config = confModule.config
config = configuration.getConfigs(args.splitConf)
#from configuration import config as config
print('Configuration module imported')
from copy import deepcopy
if config['generate']['flag']: 
  from ROOT import TDatime, gSystem, RooRandom
  jobpid = gSystem.GetPid()
  now = TDatime()
  today = now.GetDate()
  clock = now.GetTime()
  seqJob = 1
  rndSeed = today+clock+jobpid+seqJob;
  RooRandom.randomGenerator().SetSeed(rndSeed);

ws = RooWorkspace()
zero = WS(ws, RooConstVar("zero","zero",0))
one  = WS(ws, RooConstVar("one","one",1))

unblindState = WS(ws, RooCategory('unblindState','unblindState'))
unblindState.defineType('Unblind',0)
unblindState.defineType('Blind',  1)

from fitutils.utils         import createObservables, createPIDVariables, getTemplates, getTemplatesCross
from fitutils.massutils     import createMassSignal, createMassResoModel, createMassCrossFeed, createMassCombBkg, createMassPhysBkg
from fitutils.accutils      import createSignalAcceptance, createBkgAcceptance, createPhysAcceptance
from fitutils.resmodelutils import createSignalTimeResModel
from fitutils.tagutils      import createSignalOmegas, createSignalSinusoidTerms, createBkgOmega, createPhysOmega, createBkgTag
from fitutils.timeutils     import createSignalTimePdf, createBkgTimePdf, createPhysTimePdf
from fitutils.inpututils    import inputs

createObservables(config,ws,args.outDir)
sWeight = WS(ws, RooRealVar("weight", "weight", -10000,10000))
wVar_min = 0
wVar_max = 0
wVar_Nbins = 0
wVars = []
if doReweight :
  if args.wVar == 'tauKKErr':
    wVar_min = 0
    wVar_max = 0.1
    wVar_Nbins = 100
    wVar = WS(ws, RooRealVar("tauKKErr", "tauKKErr", 0,0.1))
    wVars += [wVar.GetName()]
  elif args.wVar == 'bPT':
    wVar_min = 0
    wVar_max = 20
    wVar_Nbins = 100
    wVar = WS(ws, RooRealVar("bPT", "bPT", wVar_min,wVar_max))
    wVars += [wVar.GetName()]
  elif args.wVar == 'logIP2overIPICHI2':
    wVar_min = -9.5
    wVar_max = -6
    wVar_Nbins = 150
    wVar1= WS(ws, RooRealVar("bIP", "bIP", 0,0.15))
    wVar2= WS(ws, RooRealVar("bIPCHI2", "bIPCHI2", 0,9))
    wVars += [wVar1.GetName(), wVar2.GetName()]
  else:
    print('Weight var named %s is not configured'%args.wVar)
    exit()
    
selConf = { 'bdt'       : { 'name'   : args.conf.split('_')[0],
                            'config' : args.conf.split('_')[0],
                            'cut'    : args.bdtCut,
                            'pid'    : {  'kpi'  : '5.-2.-5.3',
                                          'pik'  : '-5.3.5.-2',
                                          'pipi' : '-2.3.-2.3',
                                          'kk'   : '2.-2.2.-2' },
                          },
            'magnet'    : args.magnet,
#            'year'      : '2016',
            'bdkpi'     : { 'state' : 'kpi',
                            'pid'   : '5.-2.-5.3' },
            'bskpi'     : { 'state' : 'kpi',
                            'pid'   : '5.-2.-5.3' },
            'bdpipi_kpi' : { 'state' : 'kpi',
                             'pid' : '5.-2.-5.3' },
            'bskk_kpi' : { 'state' : 'kpi',
                             'pid' : '5.-2.-5.3' },
            'bdpipi'    : { 'state' : 'pipi',
                            'pid'   : '-2.3.-2.3' },
            'bspipi'    : { 'state' : 'pipi',
                            'pid'   : '-2.3.-2.3' },
            'bdkpi_pipi' : { 'state' : 'pipi',
                             'pid' : '-2.3.-2.3' },
            'bskk'      : { 'state' : 'kk',
                            'pid' : '2.-2.2.-2' },
            'bdkk'      : { 'state' : 'kk',
                            'pid' : '2.-2.2.-2' },
            'bdkpi_kk' : { 'state' : 'kk',
                           'pid' : '2.-2.2.-2' },
            'lbpk_kk' : { 'state' : 'kk',
                           'pid' : '2.-2.2.-2' },
            'bkg_kpi'   : { 'state' : 'kpi',
                            'pid'   : '5.-2.-5.3' },
            'bkg_pipi'   : { 'state' : 'pipi',
                            'pid'   : '-2.3.-2.3' },
            'bkg_kk'    : { 'state' : 'kk',
                            'pid' : '2.-2.2.-2' },
            'phys_kpi1' : { 'state' : 'kpi',
                            'pid'   : '5.-2.-5.3' },
            'phys_kpi2' : { 'state' : 'kpi',
                            'pid'   : '5.-2.-5.3' },
            'phys_pipi' : { 'state' : 'pipi',
                            'pid'   : '-2.3.-2.3' },
            'phys_kk' : { 'state' : 'kk',
                          'pid' : '2.-2.2.-2' },
}
minT = config['observables']['time']['range'][0]
maxT = config['observables']['time']['range'][1]
unitT = config['observables']['time']['units']

taggerList = args.taggers 
sstagName = ''
for tagName in taggerList:
  if "SS" in tagName:
    sstagName = tagName

print('********************************************************')
print('START LOADING PDF INPUTS...')
modelYears = args.years
for year in modelYears:
  print("year: %s"%year)
  createPIDVariables(selConf,year,ws)
  print('---------------------- Signals -------------------------')
  for name in [ 'bdkpi','bskpi', 'bskk' ]:
    print('Decay: %s'%name)
    nfinTaggingSignal = inputs['tagging']['file'].format(fState  = selConf[name]['state'],
                                                         bdtName = selConf['bdt']['name'],
                                                         bdtCut  = selConf['bdt']['cut'],
                                                         year    = year,
                                                        #  year    = "201516",
                                                         magnet  = selConf['magnet'])
    if name == 'bskk' and isMC:
      nfinTaggingSignal = nfinTaggingSignal.replace('Tagging', 'TaggingMC')
    getTemplates(name,year,nfinTaggingSignal,
                 [ 'eta'+tag for tag in taggerList ], ws)
    createSignalAcceptance(name,year,args.magnet,config,'%s_%s'%(args.conf.split('_')[0],args.bdtCut),args.outDir,ws, isMC=isMC, useWeights=useWeights, useTrueTau=args.useTrueTau, useTrueTag=useTrueTag)
    createSignalTimeResModel(name,year,config,ws)
    createSignalOmegas(name,year,config,taggerList,ws)
    createSignalSinusoidTerms(name,year,config,taggerList,ws,args.outDir)
    createSignalTimePdf(name,year,config,ws)

    pdftime = ws.obj("%s_pdftime_%s" % (name,year))
    pdf = WS(ws, RooProdPdf("%s_pdf_%s" % (name,year),
                            "%s_pdf_%s" % (name,year),
                            RooArgList(pdftime)))
  
obs = RooArgSet()
obsList  = [ 'mass', 'time','p','fState']#,'timeErr' ]
obsList += [ 'eta'+tag for tag in taggerList ]
obsList += [ 'q'+tag for tag in taggerList ]
obsList += [ 'weight']
if doReweight:
  # obsList += [ args.wVar ]
  obsList += wVars

print('Required observables: ')
print(obsList)
for ob in obsList:
  tmp = ws.obj(ob)
  obs.add(tmp)


  
print('Creating yields variables')
totalPdfList = RooArgList()
from ROOT import RooFormulaVar
pdfName = ''
if len(args.years)>1:
  for year in args.years:
    yieldsKK   = RooArgList()
    pdfsKK     = RooArgList()
    n_bskk   = WS( ws, RooRealVar("n_bskk_%s"%year,"n_bskk_%s"%year,44317,0,1e6))
    yieldsKK.add(ws.obj('n_bskk_%s'%year))
    pdfsKK.add(ws.obj('bskk_pdf_%s'%year))
    pdfKK = WS( ws, RooAddPdf("pdf_kk_%s"%year,"pdf_kk_%s"%year,pdfsKK,yieldsKK))
    totalPdfList.add(pdfKK)
    
  from ROOT import RooSimultaneous
  fState = ws.obj('fState')
  totalPdfList.Print()
  fState.Print('v')
  pdf = WS(ws, RooSimultaneous("pdf","pdf",totalPdfList,fState))
  pdfName = 'pdf'
else:
  pdfName = 'bskk_pdf_%s'%args.years[0]
  
pdf = ws.obj(pdfName)
print('Whole pdf created')
print('********************************************************')

params = pdf.getParameters(obs)
inputParamDir = '%s_%s_%s_%s'%(selConf['bdt']['name'],
                               selConf['bdt']['cut'],
                               '__'.join(args.years),
                               args.magnet)
if isMC :
  inputParamDir = 'MC_'+inputParamDir
# input_taggerList = '_'.join(taggerList)
# if 'OSonly' in args.outDir:
#   inputParamDir += '_OSonly'
# if 'SSonly' in args.outDir:
#   input_taggerList = 'OS_SSk'

nfinInputParams = inputs['fitParams']['file'].format(outdir    = inputParamDir,
                                                     bdtName   = selConf['bdt']['name'],
                                                     bdtCut    = selConf['bdt']['cut'],
                                                    #  taggers   = input_taggerList,
                                                     taggers   = 'OS_SSk',
                                                     magnet    = args.magnet,
                                                     blindState= 'Blind' if args.blindFlag else 'Unblind' )
print("Reading input params from: %s" % (nfinInputParams))
params.readFromFile(nfinInputParams)

#params.selectByName('*_smoothed_*').setAttribAll('Constant',True)
# params.selectByName('bskk_acctime*_*bin0').setAttribAll('Constant',True)
# params.selectByName('bskk_acctime*_*bin18').setAttribAll('Constant',True)
params.selectByName('*').setAttribAll('Constant',True)
if ('setTbias' in args.outDir):
  Tbias = float(args.outDir.split('setTbias')[1].split('_')[0])/1000.
  print('+ setTbias: enabled. Tbias',Tbias,'ps')
  _par = ws.obj('bdkpi_timeErr_mean_%s'%year)
  _par.setVal(Tbias)
  
if ('freeAccT' in args.outDir):
  for year in args.years:
    nodes = [0.201, 0.27, 0.4, 0.6, 0.8, 1, 1.25, 1.75, 2, 2.3, 3, 4, 5, 6, 7, 8, 9]
    for _i in list(range(1,12)):
      _par = ws.obj('bskk_accTimeT_%s_smoothed_bin_%d'%(year,_i))
      _par.setVal((nodes[_i]-nodes[0])/(nodes[11]-nodes[0]))
      _par.setConstant(False)
if ('freeAccU' in args.outDir):
  for year in args.years:
    nodes = [0.201, 0.27, 0.4, 0.6, 0.8, 1, 1.25, 1.75, 2, 2.3, 3, 4, 5, 6, 7, 8, 9]
    for _i in list(range(1,12)):
      _par = ws.obj('bskk_accTimeU_%s_smoothed_bin_%d'%(year,_i))
      _par.setVal((nodes[_i]-nodes[0])/(nodes[11]-nodes[0]))
      _par.setConstant(False)
if ('zeroAsymCalibFT' in args.outDir):
    for year in args.years:
      for npar in ['deltap0SSk', 'deltap1SSk']:
        _par = ws.obj('bskpi_%s_%d'%(npar,year))
        _par.setVal(0)
        _par.setConstant(True)
if ('ADG-' in args.outDir):
  _val = float( args.outDir.split('ADG-')[1].split('_')[0] )
  for year in args.years:
    _bskk_D = ws.obj('bskk_D_%s'%year)
    _bskk_D.setVal(_val)
    _bskk_D.setConstant(True)
if ('freeCKKSKK' in args.outDir):
  params.selectByName('bskk_C_*').setAttribAll('Constant',False)
  params.selectByName('bskk_S_*').setAttribAll('Constant',False)
if ('freeCPV' in args.outDir):
  params.selectByName('bskk_C_*').setAttribAll('Constant',False)
  params.selectByName('bskk_S_*').setAttribAll('Constant',False)
  params.selectByName('bskk_D_*').setAttribAll('Constant',False)
if ('freeAp' in args.outDir):
  params.selectByName('bskpi_AP_*').setAttribAll('Constant',False)
if ('freeEpsFT' in args.outDir):
  params.selectByName('bskk_epsOS_*').setAttribAll('Constant',False)
  params.selectByName('bskk_epsSSk_*').setAttribAll('Constant',False)
if ('freeEpsAsymFT' in args.outDir):
  params.selectByName('bdkpi_epsAsymOS_*').setAttribAll('Constant',False)
  params.selectByName('bskk_epsAsymSSk_*').setAttribAll('Constant',False)

if useTrueTag:
  for year in args.years:  
    _var = ws.obj('bskk_epsOS_%s'%(year))
    _var.setVal(1)
    _var.setConstant(True)
    for _nvar in ['epsAsymOS', 'p0OS', 'deltap0OS', 'p1OS', 'deltap1OS']:
      _var = ws.obj('bdkpi_%s_%s'%(_nvar,year))
      _var.setVal(0)
      _var.setConstant(True)

if 'baselineEpsFT' not in args.outDir:
  for year in args.years:  
    if ('_qOSplus_'  in args.outDir) or ('_qOSminus_' in args.outDir): 
      _bskk_epsOS = ws.obj('bskk_epsOS_%s'%year)
      _bskk_epsOS.setVal(1)
      _bskk_epsOS.setConstant(True)
      _bdkpi_epsAsymOS = ws.obj('bdkpi_epsAsymOS_%s'%year)
      _bdkpi_epsAsymOS.setVal(0)
      _bdkpi_epsAsymOS.setConstant(True)

  if ('_qSSplus_'  in args.outDir) or ('_qSSminus_' in args.outDir): 
    _bskpi_epsSSk = ws.obj('bskk_epsSSk_%s'%year)
    _bskpi_epsSSk.setVal(1)
    _bskpi_epsSSk.setConstant(True)
    _bskk_epsAsymSSk = ws.obj('bskk_epsAsymSSk_%s'%year)
    _bskk_epsAsymSSk.setVal(0)
    _bskk_epsAsymSSk.setConstant(True)


#params.setAttribAll('Constant',True)
#ws.obj('bskk_C_2015').setConstant(False)
#ws.obj('bskk_S_2015').setConstant(False)
#ws.obj('bskk_D_2015').setConstant(False)
print('initial parameters:')
params.Print("v")
print('********************************************************')

#################################### ADJUSTING ACCEPTANCES #########################################

#obs.remove(ws.obj('fState'))
ws.obj('p').Print('v')
print('----------+++++++++++++', args.outDir)
for year in args.years:
  if '_qOSplus_'  in args.outDir: break
  if '_qSSplus_'  in args.outDir: break
  if '_qOSminus_' in args.outDir: break
  if '_qSSminus_' in args.outDir: break
  if useTrueTag: break
  ws.obj('qOS').setLabel('Untag')
  if sstagName != '':
    ws.obj('q%s'%sstagName).setLabel('Untag')
  ws.obj('p').setLabel('kk')
  #for name in ['bdkpi_kk','bskk','bdkk','lbpk_kk']:
  for name in ['bskk']:
    pdfT = ws.obj('%s_pdftimeGenT_%s'%(name,year))
    pdfU = ws.obj('%s_pdftimeGenU_%s'%(name,year))
    integralPdfT = pdfT.createIntegral(RooArgSet(ws.obj('time')))
    integralPdfU = pdfU.createIntegral(RooArgSet(ws.obj('time')))
    print('Integrals for tagged/untagged pdf of %s: %g'%(name,integralPdfU.getVal()/integralPdfT.getVal()))
    ratio     = integralPdfU.getVal()/integralPdfT.getVal()
    accParams = params.selectByName('%s_accTimeT_%s_*'%(name,year))
    parIter   = accParams.createIterator() 
    while 1:
      tmp = parIter.Next()
      if not tmp: break
      tmp.setVal(tmp.getVal()*ratio)


#obs.add(ws.obj('fState'))

#################################### ADJUSTING ACCEPTANCES #########################################

print('Loading data...')
from ROOT import TFile, TTree, TChain
chain = TChain("B2HH","B2HH")
for year in args.years:
  if 'addFromBc' in args.outDir:
    _fracFromBc = float(args.outDir.split('addFromBc-')[1])
    nfinMCbskk   = inputs['MC']['addFromBc'].format(year=year, frac=_fracFromBc)
    print(nfinMCbskk)    
    chain.Add(nfinMCbskk)
  else:
    dataType = 'MC' if isMC else 'data'
    nfinData = inputs[dataType]['file'].format(outdir  = args.outDir,
                                               bdtName = selConf['bdt']['name'],
                                               bdtCut  = selConf['bdt']['cut'],
                                               year    = year,
                                               magnet  = args.magnet)
    print(nfinData)
    chain.Add(nfinData)

chain.Print()
print( "Number of entries in TChain: %d"%(chain.GetEntries()))
chainNew = None
if 'l0HadronTOS' in args.outDir:
  chainNew = chain.CopyTree("l0HadronTOS")
elif 'l0GlobalTIS' in args.outDir:
  chainNew = chain.CopyTree("l0GlobalTIS")
elif 'lowGhostProb' in args.outDir:
  chainNew = chain.CopyTree("log(piplusGhostProb)<-5.3 && log(piminusGhostProb)<-5.3")
elif 'highGhostProb' in args.outDir:
  chainNew = chain.CopyTree("log(piplusGhostProb)>-5.3 && log(piminusGhostProb)>-5.3")
elif 'lowbETA' in args.outDir:
  chainNew = chain.CopyTree("bETA<3")
elif 'highbETA' in args.outDir:
  chainNew = chain.CopyTree("bETA>3")
elif 'massBs' in args.outDir:
  chainNew = chain.CopyTree("massKK>5.32 && massKK<5.45")
elif 'noISMUON' in args.outDir:
  chainNew = chain.CopyTree("(!piplus_ISMUON && !piminus_ISMUON)")
else:
  chainNew = chain
chainNew.Print()
print( "Number of entries in TChain New: %d"%(chainNew.GetEntries()))
obs.Print('v')
newObs = RooArgSet()
print('Observable names: ', obsList)
if args.useTrueTau or useTrueTag:
  for obsName in obsList:
    if obsName == 'time' and args.useTrueTau:
      trueTime = WS(ws, RooRealVar('trueTau', 'trueTau', minT, maxT, unitT))
      newObs.add(ws.obj('trueTau'))
    elif useTrueTag and (obsName in ['qOS', 'qSSk', 'qSS']):
      qTrue = WS(ws, RooCategory("qTrue", "qTrue"))
      qTrue.defineType('B', +1)
      qTrue.defineType('Bbar', -1)
      newObs.add(ws.obj('qTrue'))
    else:
      newObs.add(ws.obj(obsName))    
else:
  newObs = obs
if 'tauKPI' in args.outDir:
  tauKPI = WS(ws, RooRealVar('tauKPI', 'tauKPI', minT, maxT, unitT))
  newObs.add(ws.obj('tauKPI'))
  tauPIK = WS(ws, RooRealVar('tauPIK', 'tauPIK', minT, maxT, unitT))
  newObs.add(ws.obj('tauPIK'))
if 'tauPIPI' in args.outDir:
  tauPIPI = WS(ws, RooRealVar('tauPIPI', 'tauPIPI', minT, maxT, unitT))
  newObs.add(ws.obj('tauPIPI'))
if 'tauKK' in args.outDir:
  tauKK = WS(ws, RooRealVar('tauKK', 'tauKK', minT, maxT, unitT))
  newObs.add(ws.obj('tauKK'))
if 'noDTF' in args.outDir:
  piplusPx = WS(ws, RooRealVar('piplusPx', 'piplusPx', -1e6, 1e6, 'MeV/c'))
  piplusPy = WS(ws, RooRealVar('piplusPy', 'piplusPy', -1e6, 1e6, 'MeV/c'))
  piplusPz = WS(ws, RooRealVar('piplusPz', 'piplusPz', 0, 1000000, 'MeV/c'))
  piminusPx = WS(ws, RooRealVar('piminusPx', 'piminusPx', -1e6, 1e6, 'MeV/c'))
  piminusPy = WS(ws, RooRealVar('piminusPy', 'piminusPy', -1e6, 1e6, 'MeV/c'))
  piminusPz = WS(ws, RooRealVar('piminusPz', 'piminusPz', 0, 1000000, 'MeV/c'))
  bPVx = WS(ws, RooRealVar('bPVx', 'bPVx', -5000, +5000, 'mm'))
  bPVy = WS(ws, RooRealVar('bPVy', 'bPVy', -5000, +5000, 'mm'))
  bPVz = WS(ws, RooRealVar('bPVz', 'bPVz', -5000, +5000, 'mm'))
  bENDVx = WS(ws, RooRealVar('bENDVx', 'bENDVx', -5000, +5000, 'mm'))
  bENDVy = WS(ws, RooRealVar('bENDVy', 'bENDVy', -5000, +5000, 'mm'))
  bENDVz = WS(ws, RooRealVar('bENDVz', 'bENDVz', -5000, +5000, 'mm'))
  newObs.add(ws.obj('piplusPx'))
  newObs.add(ws.obj('piplusPy'))
  newObs.add(ws.obj('piplusPz'))
  newObs.add(ws.obj('piminusPx'))
  newObs.add(ws.obj('piminusPy'))
  newObs.add(ws.obj('piminusPz'))
  newObs.add(ws.obj('bPVx'))
  newObs.add(ws.obj('bPVy'))
  newObs.add(ws.obj('bPVz'))
  newObs.add(ws.obj('bENDVx'))
  newObs.add(ws.obj('bENDVy'))
  newObs.add(ws.obj('bENDVz'))

print('newObs:')
newObs.Print('v')
data_sel = '1'
if ('_qOSplus_'  in args.outDir): data_sel+= ' && qOS==+1'
if ('_qOSminus_' in args.outDir): data_sel+= ' && qOS==-1'
if ('_qSSplus_'  in args.outDir): data_sel+= ' && q%s==+1'%sstagName
if ('_qSSminus_' in args.outDir): data_sel+= ' && q%s==-1'%sstagName
#data = RooDataSet("data","data",newObs, RooFit.Import(chain), RooFit.Cut(data_sel))
data = RooDataSet("data","data",newObs, RooFit.Import(chainNew), RooFit.Cut(data_sel))
data.Print('v')
if args.useTrueTau:
  data.changeObservableName('trueTau', 'time')
  data.Print('v')
if useTrueTag:
  data.changeObservableName('qTrue', 'qOS')
  data.Print('v')
print( "Number of entries in RooDataSet: %d"%(data.numEntries()))
data.Print('v')
ws.obj('p').Print('v')


hwStart = None
hwTarget = None
hwRatio = None
hwEnd = None
if doReweight:
  nfinTarget = inputs[dataType]['file'].format(outdir  = args.outDir,
                                              bdtName = selConf['bdt']['name'],
                                              bdtCut  = selConf['bdt']['cut'],
                                              year    = '201516',
                                              magnet  = args.magnet)
  chainTarget = TChain("b2hh", "b2hh")
  chainTarget.Add(nfinTarget)
  hwStart = ROOT.TH1D("hwStart", "hwStart", wVar_Nbins, wVar_min, wVar_max)
  hwTarget = ROOT.TH1D("hwTarget", "hwTarget", wVar_Nbins, wVar_min, wVar_max)
  hwRatio = ROOT.TH1D("hwRatio", "hwRatio", wVar_Nbins, wVar_min, wVar_max)
  hwEnd = ROOT.TH1D("hwEnd", "hwEnd", wVar_Nbins, wVar_min, wVar_max)
  varName = args.wVar
  if args.wVar == 'logIP2overIPICHI2':
    varName = 'log(bIP*bIP/bIPCHI2)'
  chainNew.Draw(varName+">>hwStart", "weight", "goff")
  chainTarget.Draw(varName+">>hwTarget", "weight", "goff")
  hwStart.Scale(1./hwStart.Integral())
  hwTarget.Scale(1./hwTarget.Integral())
  hwRatio.Divide(hwTarget, hwStart)



tmp_count=0
infUp = float('inf')
infDw = float('-inf')
dataNew = RooDataSet("data","data", obs, RooFit.WeightVar(sWeight))
shiftT = 0
if 'ShiftT' in args.outDir:
  shiftT = float(args.outDir.split('ShiftT')[1].split('_')[0])/1000.0
  print('Shift time of all data: enabled. Shift value:', shiftT, 'ns')
for i in range(data.numEntries()):
  obs.assignFast(data.get(i))
  _time = obs.find('time')
  tmpTimeOld = _time.getValV()
  if 'tauKPI' in args.outDir:
    timeName = 'tauKPI' if RooRandom.integer(2) else 'tauPIK'
    tmpTimeOld = obs.find(timeName).getValV()
  if 'tauPIPI' in args.outDir:
    tmpTimeOld = obs.find('tauPIPI').getValV()
  if 'tauKK' in args.outDir:
    tmpTimeOld = obs.find('tauKK').getValV()
  if 'noDTF' in args.outDir:
    piplusPx = obs.find('piplusPx').getValV()/1000.0
    piplusPy = obs.find('piplusPy').getValV()/1000.0
    piplusPz= obs.find('piplusPz').getValV()/1000.0
    piminusPx= obs.find('piminusPx').getValV()/1000.0
    piminusPy= obs.find('piminusPy').getValV()/1000.0
    piminusPz= obs.find('piminusPz').getValV()/1000.0
    bPVx = obs.find('bPVx').getValV()
    bPVy = obs.find('bPVy').getValV()
    bPVz = obs.find('bPVz').getValV()
    bENDVx = obs.find('bENDVx').getValV()
    bENDVy = obs.find('bENDVy').getValV()
    bENDVz = obs.find('bENDVz').getValV()
    mk2 = (493.677/1000.0)**2
    c = 0.299792458
    dx = bENDVx - bPVx
    dy = bENDVy - bPVy
    dz = bENDVz - bPVz
    px = (piplusPx + piminusPx)
    py = (piplusPy + piminusPy)
    pz = (piplusPz + piminusPz)
    P1 = piplusPx**2 + piplusPy**2 + piplusPz**2
    P2 = piminusPx**2 + piminusPy**2 + piminusPz**2
    P12 = piplusPx*piminusPx + piplusPy*piminusPy + piplusPz*piminusPz  
    E12 = ((mk2 + P1)**0.5)*((mk2 + P2))**0.5
    l = (dx*dx + dy*dy + dz*dz)**0.5
    p = (px*px + py*py + pz*pz)**0.5
    m = (2*(mk2+E12-P12))**0.5
    tmpTimeOld = m/p*l/c

  _time.setVal(tmpTimeOld+shiftT)
  tmpTime = _time.getValV()
  if i<10:
    print(i,'Time shift: ', tmpTimeOld,'goes to', tmpTime)


  val = pdf.getVal(obs)
  if (val<=0) or (val<=infDw) or (val>=infUp):
    print("null pdf!\n")
    obs.Print("v")
    continue 

  tmpW=1.0
  if useWeights:
    tmpW = data.get(i).find('weight').getValV()
  if doReweight:
    tmp_wVar = 0
    if args.wVar == 'logIP2overIPICHI2':
      bIP = data.get(i).find('bIP').getValV()
      bIPCHI2 = data.get(i).find('bIPCHI2').getValV()
      tmp_wVar = log(bIP*bIP/bIPCHI2)
    else:  
      tmp_wVar = data.get(i).find(args.wVar).getValV()
    tmpWW = hwRatio.GetBinContent(hwRatio.FindBin(tmp_wVar))
    if (abs(tmpWW)>2): 
      print('**********************', tmp_wVar, tmpWW, tmpTime)  
      continue
    tmpW = tmpW*tmpWW
    hwEnd.Fill(tmp_wVar, tmpW)
  
  dataNew.add(obs, tmpW)
  tmp_count+=1
    
  # if tmp_count>10000: break ### just for test!!!

for i in range(data.numEntries()):
  _time = dataNew.get(i).find('time')
  tmpTime = _time.getValV()
  print(i,'Time new: ', tmpTime)
  if i>10: 
    break

print(data.numEntries(),dataNew.numEntries())
data = dataNew
data.Print('v')

if doReweight:
  canv = ROOT.TCanvas()
  canv.cd()
  hwStart.SetLineColor(ROOT.kRed)
  hwTarget.SetLineColor(ROOT.kGreen+2)
  hwEnd.SetLineColor(ROOT.kBlue)
  hwStart.SetMarkerColor(ROOT.kRed)
  hwTarget.SetMarkerColor(ROOT.kGreen+2)
  hwEnd.SetMarkerColor(ROOT.kBlue)
  hwStart.SetMarkerStyle(20)
  hwTarget.SetMarkerStyle(20)
  hwEnd.SetMarkerStyle(24)
  hwEnd.DrawNormalized('p')
  hwStart.Draw("p same")
  hwTarget.Draw('p same')
  hwEnd.DrawNormalized('p same')
  canv.Update()
  ncanv_out = str(inputs['outParams']['path']+'/reWeight_{wVar}.pdf').format(outdir = args.outDir, wVar = args.wVar)
  ncanv_out = str(inputs['outParams']['path']+'/reWeight_{wVar}.root').format(outdir = args.outDir, wVar = args.wVar)
  canv.SaveAs(ncanv_out)

from ROOT import RooFitResult, RooNLLVar, RooMinuit, RooAbsArg, RooAbsPdf
r = RooFitResult()

c = None
plot = None
pull = None

if not args.plot:
  #params.selectByName('*').setAttribAll('Constant',True)
  
  fitOpts = [RooFit.Save(),
             RooFit.Strategy(2),
             RooFit.Optimize(2),
             #RooFit.Hesse(0),
             #RooFit.Minimizer("Minuit","migrad"),
             RooFit.Offset(),
             RooFit.PrintLevel(3),
             #RooFit.AsymptoticError(1),
             RooFit.SumW2Error(0),
             RooFit.Verbose(1),
             RooFit.NumCPU(args.ncpu),
             #RooFit.Extended()
             ]#,
  #           RooFit.SplitRange(True),
  #           RooFit.Range('testLow,testHigh')]
  #           #RooFit.ExternalConstraints(pdfConstrained) ]
  from ROOT import RooLinkedList
  fitoptsList  = RooLinkedList()
  fitoptsList2 = RooLinkedList()
  for opt in fitOpts:
    fitoptsList.Add(opt)

  
  from ROOT import RooNLLVar
  ws.obj('mass').setRange('testLow_KPI_Tot',5.0,5.2)
  ws.obj('mass').setRange('testHigh_KPI_Tot',5.1,6.2)
  ws.obj('mass').setRange('testLow_PIPI_Tot',5.0,5.2)
  ws.obj('mass').setRange('testHigh_PIPI_Tot',5.1,6.2)
  ws.obj('mass').setRange('testLow_KK_Tot',5.0,5.29)
  ws.obj('mass').setRange('testHigh_KK_Tot',5.1,6.2)

  #params.selectByName('*').setAttribAll('Constant',True)
  
  r = pdf.fitTo(data,fitoptsList)
    
  # nll = pdf.createNLL(data,fitoptsList)
  # m = RooMinuit(nll)
  # m.setPrintLevel(3)
  # m.setStrategy(2)
  # m.setVerbose(True)
  # m.migrad()
  # r = m.save()
  r.Print("v")
  outFileName = inputs['outParams']['fileRes'].format(outdir    = args.outDir,
                                                      bdtName   = selConf['bdt']['name'],
                                                      bdtCut    = selConf['bdt']['cut'],
                                                      taggers   = '_'.join(taggerList),
                                                      magnet    = args.magnet,
                                                      blindState= 'Blind' if args.blindFlag else 'Unblind')
  outFile = TFile(outFileName,"RECREATE")
  outFile.WriteTObject(r,"","Overwrite")
  outFile.Close()
 
  nfoutParams = inputs['outParams']['filePar'].format(outdir    = args.outDir,
                                                      bdtName   = selConf['bdt']['name'],
                                                      bdtCut    = selConf['bdt']['cut'],
                                                      taggers   = '_'.join(taggerList),
                                                      magnet    = args.magnet,
                                                      blindState= 'Blind' if args.blindFlag else 'Unblind')
  params.writeToFile(nfoutParams)

else:
  from fitutils.plotutils import makeCanvas, makePlot, plotPDFS, makePull, makeDataAsym, makeDataAsymBs, makePdfAsym, makePdfAsymBs, makeDataAsymBsCP, makePdfAsymBsCP, makeCanvasAsym, makeDataAsymCP, makePdfAsymCP
  from plotOpts.plotOpts  import plotOpts
  
  nfinPlotParams = inputs['outParams']['filePar'].format(outdir    = args.outDir,
                                                         bdtName   = selConf['bdt']['name'],
                                                         bdtCut    = selConf['bdt']['cut'],
                                                         taggers   = '_'.join(taggerList),
                                                         magnet    = args.magnet,
                                                         blindState= 'Blind' if args.blindFlag else 'Unblind')
  params.readFromFile(nfinPlotParams)

  print("PLOTTING PARAMETERS")
  params.Print('v')

  mass = ws.obj('mass')
  mass.setRange("bd",5.22,5.37)
  mass.setRange("bs",5.38,5.4)
  mass.setRange("3body",5,5.15)
  mass.setRange("sig",5.2,5.45)
  mass.setRange("sig5.23",5.23,5.32)
  mass.setRange("sig5.33",5.20,5.33)
  mass.setRange("sig5.45",5.33,5.45)
  mass.setRange("sigTest0",5.20,5.25)
  mass.setRange("sigTest1",5.33,5.39)
  mass.setRange("sigTest2",5.39,5.45)
  mass.setRange("bkg",5.5,6.2)
  mass.setRange("bkg5.6",5.6,5.9)
  mass.setRange("bkg5.9",5.9,6.2)
  mass.setRange("total",5,6.2)
  mass.setRange("bkg000",5.2,5.3)
  mass.setRange("bkg00",5.3,5.4)
  mass.setRange("bkg0",5.4,5.5)
  mass.setRange("bkg1",5.5,5.6)
  mass.setRange("bkg2",5.6,5.7)
  mass.setRange("bkg3",5.7,5.8)
  mass.setRange("bkg4",5.8,5.9)
  mass.setRange("bkg5",5.9,6.0)
  mass.setRange("bkg6",6.0,6.1)
  mass.setRange("bkg7",6.1,6.2)
  mass.setRange("3body1",5,5.1)
  mass.setRange("3body2",5.1,5.2)

  mass.setRange("asymKPI",5.20,5.32)
  mass.setRange("asymKPIBs",5.32,5.45)
  mass.setRange("asymPIPI",5.20,5.35)
  mass.setRange("asymKK",5.0,6.2)
  mass.setRange("asymKKLow",5.30,5.366)
  mass.setRange("asymKKHigh",5.366,5.44)

  #time = ws.obj('time')
  #time.setRange("provaVincenzo",0.2,3.2)

  time      = ws.obj('time')
  timeErr   = ws.obj('timeErr')

  state     = args.finalState
  var       = args.var
  rangePlot = args.range
   
  btag      = args.Btag
  ftag      = args.Ftag
  slices    = []
  datacut   = 'fState==fState::%s'%state

  if btag == 'Tag':
    datacut+= '&&(q%s==q%s::B||q%s==q%s::Bbar)'%(args.Atag,args.Atag,args.Atag,args.Atag)
    slices += [RooFit.Slice(ws.obj('q%s'%args.Atag),'B,Bbar')]#,RooFit.Slice(ws.obj('q%s'%args.Atag),'Bbar')]
  if btag == 'B':
    datacut+= '&&q%s==q%s::B'%(args.Atag,args.Atag)
    slices += [RooFit.Slice(ws.obj('q%s'%args.Atag),'B')]
  elif btag == 'Bbar':
    datacut+= '&&q%s==q%s::Bbar'%(args.Atag,args.Atag)
    slices += [RooFit.Slice(ws.obj('q%s'%args.Atag),'Bbar')]
  elif btag == 'Untag':
    datacut+= '&&q%s==q%s::Untag'%(args.Atag,args.Atag)
    slices += [RooFit.Slice(ws.obj('q%s'%args.Atag),'Untag')]

  if ftag == 'kpi':
    datacut+= '&&p==p::kpi'
    slices += [RooFit.Slice(ws.obj('p'),'kpi')]
  elif ftag == 'pik':
    datacut+= '&&p==p::pik'
    slices += [RooFit.Slice(ws.obj('p'),'pik')]

  print(slices)
  print(datacut)
  outFileName = inputs['outParams']['plot'].format(
    outdir = args.outDir,
    var = var,
    rangePlot = rangePlot,
    state = state,
    bdtName = selConf['bdt']['name'],
    bdtCut = selConf['bdt']['cut'],
    Btag = btag,
    Ftag = ftag,
    Atag = args.Atag
  )
  #args.directory,var,rangePlot,finalState,cut.replace('.','_'),btag,ftag,tagger)
  outFile = TFile(outFileName,"RECREATE")

  if var == 'mass':
    massName = None
    if   'KPI' in state : massName = "#it{m_{K^{#pm}#pi^{#mp}}} [GeV/#it{c}^{2}]"
    #if   'KPI' in state : massName = "#it{m_{K^{ #minus}#pi^{ +}}} [GeV/#it{c}^{2}]"
    elif 'PIPI' in state : massName = "#it{m_{#pi^{ +}#pi^{ #minus}}} [GeV/#it{c}^{2}]"
    elif 'KK' in state  : massName = "#it{m_{K^{ +}K^{ #minus}}} [GeV/#it{c}^{2}]"
    ### MASS PLOT
    print("mass plot: makePlot ",state,btag,ftag,mass.getMin(state),mass.getMax(state))
    plot = makePlot("plot_mass_%s_%s_%s"%(state,btag,ftag),massName,mass,mass.getMin(state),mass.getMax(state),240)
    print("mass plot: plotPDFS ",plot.GetXaxis().GetXmax(), plot.GetXaxis().GetXmin())
    plotPDFS(plot,data,pdfName,datacut,"mass",slices,"",plotOpts,state,ws)
    print("mass plot: pull ",plot.GetXaxis().GetXmin(), plot.GetXaxis().GetXmax())
    pull = makePull(plot,mass,mass.getMin(state),mass.getMax(state),240)
    print("mass plot: makeCanvas ",plot.GetXaxis().GetXmin(), plot.GetXaxis().GetXmax())
    c = makeCanvas("c_mass_%s_%s_%s_%s"%(state,btag,ftag,args.Atag),plotOpts[state],700,725,plot,pull,outFile)
    #del plot
    #del pull
    #del c
    outFile.Close()

  elif var == 'time':
    ### TIME PLOT
    # Nbins = (280 if (isMC and not 'addFromBc' in args.outDir) else 140)
    Nbins = (280 if (isMC and not 'addFromBc' in args.outDir) else 100)
    plot = makePlot("plot_time_%s_%s_%s_%s" %(state,rangePlot,btag,ftag),"Decay time [ps]",time,time.getMin(),time.getMax(),Nbins)
    plotPDFS(plot,data,pdfName,datacut,"time",slices,rangePlot,plotOpts,state,ws)
    pull = makePull(plot,time,time.getMin(),time.getMax(),Nbins)
    c = makeCanvas("c_time_%s_%s_%s_%s_%s" %(state,rangePlot,btag,ftag,args.Atag),plotOpts[state],700,725,plot,pull,outFile)
    #del plot
    #del pull
    #del c
    outFile.Close()

  elif var == 'timeErr':
    ## TIMEERR PLOT
    plot = makePlot("plot_timeErr_%s_%s_%s_%s" %(state,rangePlot,btag,ftag),"#delta_{t} (ps)",timeErr,timeErr.getMin(),timeErr.getMax(),40)
    plotPDFS(plot,data,pdfName,datacut,"timeErr",slices,rangePlot,plotOpts,state,ws)
    pull = makePull(plot,timeErr,timeErr.getMin(),timeErr.getMax(),40)
    c = makeCanvas("c_timeErr_%s_%s_%s_%s_%s" %(state,rangePlot,btag,ftag,args.Atag),plotOpts[state],700,725,plot,pull,outFile)
    #del plot
    #del pull
    #del c
    outFile.Close()

  elif var == 'eta':
    for tag in taggerList:
      if tag != args.Atag: continue
      ### ETAOS PLOT
      eta = ws.obj('eta'+tag)
      plot = None
      pull = None
      if tag == 'SSk':
        plot = makePlot("plot_eta%s_%s_%s_%s_%s" %(tag,state,rangePlot,btag,ftag),"#eta_{"+tag+"}",eta,eta.getMin(),eta.getMax(),50)
      else:
        plot = makePlot("plot_eta%s_%s_%s_%s_%s" %(tag,state,rangePlot,btag,ftag),"#eta_{"+tag+"}",eta,eta.getMin(),eta.getMax(),50)
      
      plotPDFS(plot,data,pdfName,datacut,"etaOS",slices,rangePlot,plotOpts,state,ws)
      #plotPDFS(plot,data,pdfName,datacut,tag,slices,rangePlot,plotOpts,state,ws)
      if tag == 'SSk':
        pull = makePull(plot,eta,eta.getMin(),eta.getMax(),50)
      else:
        pull = makePull(plot,eta,eta.getMin(),eta.getMax(),50)
      makeCanvas("c_eta%s_%s_%s_%s_%s" %(tag,state,rangePlot,btag,ftag),plotOpts[state],700,725,plot,pull,outFile)
      #del plot
      #del pull
      #del eta
    outFile.Close()

  elif var == 'asym':    
    if 'PIPI' in state: 
      ### ASYMMETRY PLOTS
      hAsym = makeDataAsymCP(chainNew,['mass'],rangePlot,state,'%s'%args.Atag,ws)
      ctmp,asymGraph = makePdfAsymCP(data,pdfName,'%s'%args.Atag,state,rangePlot,ws)
      c = makeCanvasAsym('cACPBd2PIPI_%s_%s'%(args.Atag,rangePlot),700,700,hAsym,asymGraph)
      c.Draw()
      # c.SaveAs('%s.pdf'%(outFile.GetName().replace('.root','').replace('.','_').replace('1_2ps', '1.2ps').replace('1_5ps', '1.5ps')))
      # ctmp.SaveAs('%s_tmp.pdf'%(outFile.GetName().replace('.root','').replace('.','_').replace('1_2ps', '1.2ps').replace('1_5ps', '1.5ps')))  
      c.SaveAs('%s.pdf'%(outFile.GetName().replace('.root','')))
      ctmp.SaveAs('%s_tmp.pdf'%(outFile.GetName().replace('.root','')))  
      outFile.WriteTObject(c,"","Overwrite")
      outFile.WriteTObject(ctmp,"","Overwrite")
      #del hAsym
      #del ctmp
      #del asymGraph
      #del c
      outFile.Close()
    
    elif 'KPI' in state: 
      ### ASYMMETRY PLOTS
      if "Bs" not in rangePlot:
        hAsym = makeDataAsym(chainNew,['mass'],rangePlot,state,'%s'%args.Atag,ws)
        ctmp,asymGraph = makePdfAsym(data,pdfName,'%s'%args.Atag,state,rangePlot,ws)
        c = makeCanvasAsym('cACPBd2KPI_%s_%s'%(args.Atag,rangePlot),700,700,hAsym,asymGraph)
        c.Draw()
        c.SaveAs('%s.pdf'%(outFile.GetName().replace('.root','')))
        ctmp.SaveAs('%s_tmp.pdf'%(outFile.GetName().replace('.root','')))
        outFile.WriteTObject(c,"","Overwrite")
        outFile.WriteTObject(ctmp,"","Overwrite")
      else:
        hAsym = makeDataAsymBs(chainNew,['mass'],rangePlot,state,'%s'%args.Atag,ws)
        ctmp,asymGraph = makePdfAsymBs(data,pdfName,'%s'%args.Atag,state,rangePlot,ws)
        c = makeCanvasAsym('cACPBs2KPI_%s_%s'%(args.Atag,rangePlot),700,700,hAsym,asymGraph)
        c.Draw()
        # c.SaveAs('%s.pdf'%(outFile.GetName().replace('.root','').replace('.','_').replace('1_2ps', '1.2ps').replace('1_5ps', '1.5ps')))
        # ctmp.SaveAs('%s_tmp.pdf'%(outFile.GetName().replace('.root','').replace('.','_').replace('1_2ps', '1.2ps').replace('1_5ps', '1.5ps')))
        c.SaveAs('%s.pdf'%(outFile.GetName().replace('.root','')))
        ctmp.SaveAs('%s_tmp.pdf'%(outFile.GetName().replace('.root','')))
        outFile.WriteTObject(c,"","Overwrite")
        outFile.WriteTObject(ctmp,"","Overwrite")
      #c.Draw()
      #outFile.WriteTObject(c,"","Overwrite")
      #outFile.WriteTObject(ctmp,"","Overwrite")
      #del hAsym
      #del ctmp
      #del asymGraph
      #del c
      outFile.Close()
    elif 'KK' in state:  
      ### ASYMMETRY PLOTS
      asym_Nbins = (21 if (isMC and not 'addFromBc' in args.outDir) else 7)
      tmpAtag = ('True' if useTrueTag else args.Atag)
      hAsym = makeDataAsymBsCP(chainNew,[],rangePlot,state,tmpAtag,ws, Nbins=asym_Nbins)
      # hAsym = makeDataAsymBsCP(chainNew,[],rangePlot,state,'%s'%args.Atag,ws, Nbins=asym_Nbins)
      ctmp,asymGraph = makePdfAsymBsCP(data,pdfName,'%s'%args.Atag,state,rangePlot,ws)
      _Amin = (-0.3 if (isMC and not 'addFromBc' in args.outDir) or useTrueTag else -0.1)
      _Amax = (+0.3 if (isMC and not 'addFromBc' in args.outDir) or useTrueTag else +0.1)
      c = makeCanvasAsym('cACPBs2KK_%s_%s'%(args.Atag,rangePlot),700,700,hAsym,asymGraph,ymin=_Amin,ymax=_Amax)
      c.Draw()
      # c.SaveAs('%s.pdf'%(outFile.GetName().replace('.root','').replace('.','_').replace('1_2ps', '1.2ps').replace('1_5ps', '1.5ps')))
      # ctmp.SaveAs('%s_tmp.pdf'%(outFile.GetName().replace('.root','').replace('.','_').replace('1_2ps', '1.2ps').replace('1_5ps', '1.5ps')))
      c.SaveAs('%s.pdf'%(outFile.GetName().replace('.root','')))
      ctmp.SaveAs('%s_tmp.pdf'%(outFile.GetName().replace('.root','')))
      outFile.WriteTObject(c,"","Overwrite")
      outFile.WriteTObject(ctmp,"","Overwrite")
      #del hAsym
      #del ctmp
      #del asymGraph
      #del c
      outFile.Close()
  
  print "plot ends"

print "exit"

#import os
#mypid = os.getpid()
#os.system('kill %s' %( str(mypid) ) )

