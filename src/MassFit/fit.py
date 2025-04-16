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
parser.add_argument('-sw','--sWeight', dest = 'sWeight', action = 'store_true', default = False)
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
args = parser.parse_args()

import B2DXFitters
from B2DXFitters.WS import WS
import ROOT
from ROOT import RooFit, gROOT, gSystem, TFile, TTree, TCanvas
from ROOT import RooWorkspace, RooMsgService
from ROOT import RooAbsReal, RooRealVar, RooConstVar, RooCategory, RooProduct
from ROOT import RooDataSet, RooProdPdf,  RooAddPdf
from ROOT import RooArgSet, RooArgList

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

createObservables(config,ws)


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
taggerList = args.taggers 
sstagName = None
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
  for name in [ 'bdkpi','bskpi', 'bdpipi', 'bspipi', 'bskk','bdkk' ]:
    print('Decay: %s'%name)
    nfinTaggingSignal = inputs['tagging']['file'].format(fState  = selConf[name]['state'],
                                                         bdtName = selConf['bdt']['name'],
                                                         bdtCut  = selConf['bdt']['cut'],
                                                         year    = year,
                                                         magnet  = selConf['magnet'])
    
    createMassSignal(name,year,config,ws)
    
    pdfmass = ws.obj("%s_pdfmass_%s" % (name,year))
    
  # perche per gli atri no
  for name in ['bdkpi','bskpi','bdpipi','bskk']:
    createMassResoModel(name,year,config,ws)
  print('-------------------- Cross-feed Bkg ---------------------')
  for name in [ 'bdkpi_pipi','bdkpi_kk', 'lbpk_kk', 'bdpipi_kpi','bskk_kpi' ]:
    print('---------------------- %s -----------------------'%name)
    
    createMassCrossFeed(name,year,config,selConf,ws)
    pdfmass = ws.obj("%s_pdfmass_%s" % (name,year))
    
  print('---------------------- Comb Bkg -----------------------')
  for name,state in [('bkg_kpi','kpi'),('bkg_pipi','pipi'),('bkg_kk','kk')]:
    createMassCombBkg(name,year,config,selConf,sstagName, ws)
    pdfmass = ws.obj("%s_pdfmass_%s" % (name,year))
  print('---------------------- Phys. Bkg -----------------------')
  for name,state in [('phys_kpi1','kpi'),('phys_kpi2','kpi'),('phys_pipi','pipi'),('phys_kk','kk')]:
    createMassPhysBkg(name,year,config,ws)
    #createBkgTag(name,year,config,taggerList,state,ws)
    pdfmass = ws.obj("%s_pdfmass_%s" % (name,year))
  print('********************************************************')
print('********************************************************')

runNumber = WS(ws, RooRealVar("runNumber_d", "runNumber_d", 0, 1.0e10))
eventNumber = WS(ws, RooRealVar("eventNumber_d", "eventNumber_d", 0, 1.0e10))

obs = RooArgSet()
obsList  = ['mass', 'p', 'fState', 'time']
obsList += [ 'eta'+tag for tag in taggerList ]
obsList += [ 'q'+tag for tag in taggerList ]
obsList += ['runNumber_d', 'eventNumber_d']


print('Required observables: ')
print(obsList)
for ob in obsList:
  tmp = ws.obj(ob)
  obs.add(tmp)

print('Creating yields variables')
totalPdfList = RooArgList()
from ROOT import RooFormulaVar
for year in args.years:
  n_bdkpi  = WS( ws, RooRealVar("n_bdkpi_%s"%year,"n_bdkpi_%s"%year,97000,0,1e6))
  n_bskpi  = WS( ws, RooRealVar("n_bskpi_%s"%year,"n_bskpi_%s"%year,9000,0,1e6))
  n_bdpipi = WS( ws, RooRealVar("n_bdpipi_%s"%year,"n_bdpipi_%s"%year,27000,0,1e6))
  n_bspipi = WS( ws, RooRealVar("n_bspipi_%s"%year,"n_bspipi_%s"%year,500,0,1e6))
  n_bskk   = WS( ws, RooRealVar("n_bskk_%s"%year,"n_bskk_%s"%year,44317,0,1e6))
  n_bdpipi_kpi = WS( ws, RooFormulaVar("n_bdpipi_kpi_%s"%year,"n_bdpipi_kpi_%s"%year,"@0*(@1+@2)/@3",
                                       RooArgList(n_bdpipi,
                                                  ws.obj('eff_bdpipi_kpi_%s'%year),ws.obj('eff_bdpipi_pik_%s'%year),
                                                  ws.obj('eff_bdpipi_pipi_%s'%year))))
  n_bskk_kpi = WS( ws, RooFormulaVar("n_bskk_kpi_%s"%year,"n_bskk_kpi_%s"%year,"@0*(@1+@2)/@3",
                                       RooArgList(n_bskk,
                                                  ws.obj('eff_bskk_kpi_%s'%year),ws.obj('eff_bskk_pik_%s'%year),
                                                  ws.obj('eff_bskk_kk_%s'%year))))
  n_bdkpi_pipi = WS( ws, RooFormulaVar("n_bdkpi_pipi_%s"%year,"n_bdkpi_pipi_%s"%year,"@0*(@1+@2)/(@3+@4)",
                                       RooArgList(n_bdkpi,
                                                  ws.obj('eff_bdkpi_pipi_%s'%year),ws.obj('eff_bdpik_pipi_%s'%year),
                                                  ws.obj('eff_bdkpi_kpi_%s'%year),ws.obj('eff_bdpik_pik_%s'%year))))
  # n_bdkpi_kk = WS( ws, RooFormulaVar("n_bdkpi_kk_%s"%year,"n_bdkpi_kk_%s"%year,"@0*(@1+@2)/(@3+@4)",
  #                                    RooArgList(n_bdkpi,
  #                                               ws.obj('eff_bdkpi_kk_%s'%year),ws.obj('eff_bdpik_kk_%s'%year),
  #                                               ws.obj('eff_bdkpi_kpi_%s'%year),ws.obj('eff_bdpik_pik_%s'%year))))
  n_bdkpi_kk = WS( ws, RooRealVar("n_bdkpi_kk_%s"%year,"n_bdkpi_kk_%s"%year,3500,0,1e6))
  n_bdkk = WS(ws, RooRealVar("n_bdkk_%s"%year,"n_bdkk_%s"%year,1260,0,1e6))
  #R_bdkk = WS(ws, RooRealVar("R_bdkk_%s"%year,"R_bdkk_%s"%year,0.01,0,1))
  #n_bdkk = WS(ws, RooFormulaVar("n_bdkk_%s"%year,"n_bdkk_%s"%year,"@0*@1",RooArgList(n_bskk,R_bdkk)))
  n_lbpk_kk = WS(ws, RooRealVar("n_lbpk_kk_%s"%year,"n_lbpk_kk_%s"%year,730,0,1e6))
  #R_lbpk = WS(ws, RooRealVar("R_lbpk_%s"%year,"R_lbpk_%s"%year,0.02,0,1))
  #n_lbpk_kk = WS(ws, RooFormulaVar("n_lbpk_kk_%s"%year,"n_lbpk_kk_%s"%year,"@0*@1",RooArgList(n_bskk,R_lbpk)))
  n_bkg_kpi = WS( ws, RooRealVar("n_bkg_kpi_%s"%year,"n_bkg_kpi_%s"%year,100000,0,1e6))
  n_bkg_pipi = WS( ws, RooRealVar("n_bkg_pipi_%s"%year,"n_bkg_pipi_%s"%year,100000,0,1e6))
  n_bkg_kk = WS( ws, RooRealVar("n_bkg_kk_%s"%year,"n_bkg_kk_%s"%year,10000,0,1e6))
  n_phys_kpi1 = WS( ws, RooRealVar("n_phys_kpi1_%s"%year,"n_phys_kpi1_%s"%year,10000,0,1e6))
  n_phys_kpi2 = WS( ws, RooRealVar("n_phys_kpi2_%s"%year,"n_phys_kpi2_%s"%year,1000,0,1e6))
  n_phys_pipi = WS( ws, RooRealVar("n_phys_pipi_%s"%year,"n_phys_pipi_%s"%year,1000,0,1e6))
  n_phys_kk = WS( ws, RooRealVar("n_phys_kk_%s"%year,"n_phys_kk_%s"%year,1000,0,1e6))

  yieldsKPI = RooArgList()
  pdfsKPI = RooArgList()
  pdfsKPIGen = RooArgList()
  mass = ws.obj('mass')

  for name in ['bdkpi','bskpi','bdpipi_kpi','bskk_kpi']:
    yieldsKPI.add(ws.obj('n_%s_%s'%(name,year)))
    pdfsKPI.add(ws.obj('%s_pdfmass_%s'%(name,year)))
    #pdfsKPIGen.add(ws.obj('%s_pdfGen_%s'%(name,year)))
  for name in ['bkg_kpi','phys_kpi1','phys_kpi2']:
    yieldsKPI.add(ws.obj('n_%s_%s'%(name,year)))
    pdfsKPI.add(ws.obj('%s_pdfmass_%s'%(name,year)))
  
  yieldsPIPI  = RooArgList()
  pdfsPIPI    = RooArgList()
  pdfsPIPIGen = RooArgList()

  for name in ['bdpipi','bspipi','bdkpi_pipi']:
    yieldsPIPI.add(ws.obj('n_%s_%s'%(name,year)))
    pdfsPIPI.add(ws.obj('%s_pdfmass_%s'%(name,year)))
    #pdfsPIPIGen.add(ws.obj('%s_pdfGen_%s'%(name,year))
  for name in ['bkg_pipi','phys_pipi']:
    yieldsPIPI.add(ws.obj('n_%s_%s'%(name,year)))
    pdfsPIPI.add(ws.obj('%s_pdfmass_%s'%(name,year)))
  
  yieldsKK   = RooArgList()
  pdfsKK     = RooArgList()
  pdfsMassKK = RooArgList()

  for name in ['bskk','bdkpi_kk','bdkk','lbpk_kk']:
  #for name in ['bskk','bdkk']:
    yieldsKK.add(ws.obj('n_%s_%s'%(name,year)))
    pdfsKK.add(ws.obj('%s_pdfmass_%s'%(name,year)))
    #pdfsKPIGen.add(ws.obj('%s_pdfGen_%s'%(name,year)))
  for name in ['bkg_kk','phys_kk']:
    yieldsKK.add(ws.obj('n_%s_%s'%(name,year)))
    pdfsKK.add(ws.obj('%s_pdfmass_%s'%(name,year)))
  
  from ROOT import RooAddPdf
  pdfKPI = WS( ws, RooAddPdf("pdf_kpi_%s"%year,"pdf_kpi_%s"%year,pdfsKPI,yieldsKPI))
  #totalPdfList.add(pdfKPI)
  pdfPIPI = WS( ws, RooAddPdf("pdf_pipi_%s"%year,"pdf_pipi_%s"%year,pdfsPIPI,yieldsPIPI))
  #totalPdfList.add(pdfPIPI)
  pdfKK = WS( ws, RooAddPdf("pdf_kk_%s"%year,"pdf_kk_%s"%year,pdfsKK,yieldsKK))
  totalPdfList.add(pdfKK)


from ROOT import RooSimultaneous
fState = ws.obj('fState')
totalPdfList.Print()
fState.Print('v')
pdf = WS(ws, RooSimultaneous("pdf","pdf",totalPdfList,fState))
   
pdfName = 'pdf'
pdf = ws.obj(pdfName)
print('Whole pdf created')
print('********************************************************')

params = pdf.getParameters(obs)

nfinInputParams = inputs['fitParams']['file'].format(outdir    = args.outDir,
                                                     bdtName   = selConf['bdt']['name'],
                                                     bdtCut    = selConf['bdt']['cut'],
                                                     taggers   = '_'.join(taggerList),
                                                     magnet    = args.magnet,
                                                     blindState= 'Blind' if args.blindFlag else 'Unblind' )
print("Reading input params from: %s" % (nfinInputParams))
params.readFromFile(nfinInputParams)
print('initial parameters:')
params.Print("v")
print('********************************************************')


print('Loading data...')
from ROOT import TFile, TTree, TChain
chain = TChain("b2hh","b2hh")
for year in args.years:
  nfinData = inputs['data']['file'].format(bdtName = selConf['bdt']['name'],
                                           bdtCut  = selConf['bdt']['cut'],
                                           year    = year,
                                           magnet  = args.magnet)
  print(nfinData)
  chain.Add(nfinData)

  
  
chain.Print()
chain.Print("p*")
print chain.GetEntries("p==-1")
print( "Number of entries in TChain: %d"%(chain.GetEntries()))
obs.Print('v')
data = RooDataSet("data","data",obs,RooFit.Import(chain))
print( "Number of entries in RooDataSet: %d"%(data.numEntries()))
data.Print('v')
ws.obj('p').Print('v')


##################################################################
##################################################################
##################################################################
##################################################################
##################################################################
##################################################################
##################################################################

tmp_count=0
infUp = float('inf')
infDw = float('-inf')
if not args.plot:
  dataNew = RooDataSet("data","data",obs)
  for i in range(data.numEntries()):
    obs.assignFast(data.get(i))
    val = pdf.getVal(obs)
    tmpM = data.get(i).find('mass').getValV()
    for tmpMM,tmpTT in [(5.21437,13.7251), (5.31177,12.1925), (5.28351,12.162)]: 
      if abs(tmpMM-tmpM)<0.001: 
        val = -1
        break
    if val > 0 and val > infDw and val < infUp:
      dataNew.add(obs)
      tmp_count+=1
    else:
      print("null pdf!\n")
      obs.Print("v")
    #if tmp_count>2E4: break ### just for test!!!

  print(data.numEntries(),dataNew.numEntries())
  data = dataNew

from ROOT import RooFitResult, RooNLLVar, RooMinuit, RooAbsArg, RooAbsPdf
r = RooFitResult()

c = None
plot = None
pull = None

if not args.plot and not args.sWeight:
  
  fitOpts = [RooFit.Save(),
             #RooFit.Strategy(2),
             RooFit.Optimize(2),
             #RooFit.Hesse(0),
             #RooFit.Minimizer("Minuit","migrad"),
             RooFit.Offset(),
             #RooFit.PrintLevel(3),
             RooFit.Verbose(1),
             RooFit.NumCPU(args.ncpu),
             RooFit.Extended()]#,
  #           RooFit.SplitRange(True),
  #           RooFit.Range('testLow,testHigh')]
  #           #RooFit.ExternalConstraints(pdfConstrained) ]
  from ROOT import RooLinkedList
  fitoptsList  = RooLinkedList()
  fitoptsList2 = RooLinkedList()
  for opt in fitOpts:
    fitoptsList.Add(opt)

  #r = pdf.fitTo(data,fitoptsList)
  # Inizializza tutte le cache presenti nella PDF
  #from ROOT import RooNLLVar

  #pdf.fitTo(data,fitoptsList)
  for year in args.years:
    ws.obj('bkg_kpi_pdfmass_%s'%year).setAttribute("NOCacheAndTrack")
    ws.obj('bkg_pipi_pdfmass_%s'%year).setAttribute("NOCacheAndTrack")
    ws.obj('bkg_kk_pdfmass_%s'%year).setAttribute("NOCacheAndTrack")
    
  
  from ROOT import RooNLLVar
  ws.obj('mass').setRange('testLow_KPI_Tot',5.0,5.2)
  ws.obj('mass').setRange('testHigh_KPI_Tot',5.1,6.2)
  ws.obj('mass').setRange('testLow_PIPI_Tot',5.0,5.2)
  ws.obj('mass').setRange('testHigh_PIPI_Tot',5.1,6.2)
  ws.obj('mass').setRange('testLow_KK_Tot',5.0,5.29)
  ws.obj('mass').setRange('testHigh_KK_Tot',5.1,6.2)

  
   
  nll = pdf.createNLL(data,fitoptsList)
  m = RooMinuit(nll)
  m.setPrintLevel(3)
  m.setStrategy(2)
  m.setVerbose(True)
  m.migrad()
  r = m.save()
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

elif not args.sWeight:
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
  mass.setRange("asymKK",5.30,5.44)
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
    plot = makePlot("plot_time_%s_%s_%s_%s" %(state,rangePlot,btag,ftag),"Decay time [ps]",time,time.getMin(),time.getMax(),280)
    plotPDFS(plot,data,pdfName,datacut,"time",slices,rangePlot,plotOpts,state,ws)
    pull = makePull(plot,time,time.getMin(),time.getMax(),280)
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
        plot = makePlot("plot_eta%s_%s_%s_%s_%s" %(tag,state,rangePlot,btag,ftag),"#eta_{"+tag+"}",eta,eta.getMin(),eta.getMax(),100)
      
      plotPDFS(plot,data,pdfName,datacut,"etaOS",slices,rangePlot,plotOpts,state,ws)
      #plotPDFS(plot,data,pdfName,datacut,tag,slices,rangePlot,plotOpts,state,ws)
      if tag == 'SSk':
        pull = makePull(plot,eta,eta.getMin(),eta.getMax(),50)
      else:
        pull = makePull(plot,eta,eta.getMin(),eta.getMax(),100)
      makeCanvas("c_eta%s_%s_%s_%s_%s" %(tag,state,rangePlot,btag,ftag),plotOpts[state],700,725,plot,pull,outFile)
      #del plot
      #del pull
      #del eta
    outFile.Close()

  elif var == 'asym':    
    if 'PIPI' in state: 
      ### ASYMMETRY PLOTS
      hAsym = makeDataAsymCP(chain,['mass'],rangePlot,state,'%s'%args.Atag,ws)
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
        hAsym = makeDataAsym(chain,['mass'],rangePlot,state,'%s'%args.Atag,ws)
        ctmp,asymGraph = makePdfAsym(data,pdfName,'%s'%args.Atag,state,rangePlot,ws)
        c = makeCanvasAsym('cACPBd2KPI_%s_%s'%(args.Atag,rangePlot),700,700,hAsym,asymGraph)
        c.Draw()
        c.SaveAs('%s.pdf'%(outFile.GetName().replace('.root','')))
        ctmp.SaveAs('%s_tmp.pdf'%(outFile.GetName().replace('.root','')))
        outFile.WriteTObject(c,"","Overwrite")
        outFile.WriteTObject(ctmp,"","Overwrite")
      else:
        hAsym = makeDataAsymBs(chain,['mass'],rangePlot,state,'%s'%args.Atag,ws)
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
      hAsym = makeDataAsymBsCP(chain,['mass'],rangePlot,state,'%s'%args.Atag,ws)
      ctmp,asymGraph = makePdfAsymBsCP(data,pdfName,'%s'%args.Atag,state,rangePlot,ws)
      c = makeCanvasAsym('cACPBs2KK_%s_%s'%(args.Atag,rangePlot),700,700,hAsym,asymGraph)
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


if args.sWeight:
  nfinPlotParams = inputs['outParams']['filePar'].format(outdir    = args.outDir,
                                                         bdtName   = selConf['bdt']['name'],
                                                         bdtCut    = selConf['bdt']['cut'],
                                                         taggers   = '_'.join(taggerList),
                                                         magnet    = args.magnet,
                                                         blindState= 'Blind' if args.blindFlag else 'Unblind')
  params.readFromFile(nfinPlotParams)
  params.setAttribAll('Constant',True)
  yields = RooArgList(params.selectByName("n_*"))
  yields.setAttribAll('Constant', False)
  yields.Print("v")
  print("PLOTTING PARAMETERS")
  params.Print('v')

  from ROOT import RooStats
  from ROOT import RooAbsData
  myPlot = RooStats.SPlot("myPlot","myPlot", data, pdf, yields)
  myPlot.Print("v")
  data.Print("v")
  weight = RooRealVar("n_bskk_%s_sw"%args.years[0], "n_bskk_%s_sw"%args.years[0], -1e6, 1e6)
  obs.add(weight)
  data.setDefaultStorageType(RooAbsData.Tree)
  dataS = RooDataSet("b2hhW", "b2hhW", obs, RooFit.Import(data))
  dataS.changeObservableName("n_bskk_%s_sw"%args.years[0],"weight")
  dataS.setDefaultStorageType(RooAbsData.Tree)
  dataS.SetName("b2hhW")
  dataS.SetTitle("b2hhW")
  dataS.Print("v")
  
  outFile = TFile("${B2HH_OUT}/sPlotFinal/%s/b2hh_sWeight.root"%args.outDir,  "RECREATE")
  #outTree = dataS.GetClonedTree()
  outTree = dataS.tree()
  outTree.SetName("b2hhW")
  outTree.SetName("b2hhW")
  outTree.GetBranch("p_idx").SetName('p')
  outTree.GetBranch("fState_idx").SetName('fState')
  outTree.GetBranch("qOS_idx").SetName('qOS')
  outTree.GetBranch("qSSk_idx").SetName('qSSk')
  outTree.Print()
  outFile.WriteTObject(outTree,"b2hhW","Overwrite")
  outFile.Close()
  
  

print "exit"

#import os
#mypid = os.getpid()
#os.system('kill %s' %( str(mypid) ) )

