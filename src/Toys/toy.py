import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-t','--tagger', nargs='+', dest = 'taggers', default = ['OS'])
#parser.add_argument('-n','--ncpu', type = int, dest = 'ncpu', default = 32)
#parser.add_argument('-p','--plot', dest = 'plot', action = 'store_true', default = False)
parser.add_argument('-u','--blindFlag', dest = 'blindFlag', action = 'store_true', default = False)
parser.add_argument('-C','--conf', type = str, dest = 'conf', default = 'PIPI')
parser.add_argument('-s','--splitConf', type = str, dest = 'splitConf', default = '')
parser.add_argument('-y','--years', nargs='+', dest = 'years', default = ['Tot'])
parser.add_argument('-m','--magnet', type = str, dest = 'magnet', default = 'Tot')
parser.add_argument('-b','--bdtCut', type = str, dest = 'bdtCut', default = '0.1')
parser.add_argument('-d','--outDir', type = str, dest = 'outDir', default = 'results_Template')
#parser.add_argument('-r','--range', type = str, dest = 'range', default = 'total')
#parser.add_argument('-f','--finalState', type = str, dest = 'finalState', default = 'PIPI')
#parser.add_argument('-v','--var', type = str, dest = 'var', default = 'mass')
#parser.add_argument('-B','--Btag', type = str, dest = 'Btag', default = 'tot')
#parser.add_argument('-F','--Ftag', type = str, dest = 'Ftag', default = 'tot')
#parser.add_argument('-A','--Atag', type = str, dest = 'Atag', default = 'OS')
parser.add_argument('-i','--toyIndex', type = str, dest = 'toyIndex', default = '0')
args = parser.parse_args()

import B2DXFitters

from B2DXFitters.WS import WS

import ROOT
from ROOT import RooFit, gROOT, gSystem, TCanvas

from ROOT import RooWorkspace, RooAbsReal, RooRealVar, RooCategory, RooMsgService, RooProduct

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


from ROOT import RooArgSet, RooConstVar
import os, sys
B2HH_SRC = os.getenv("B2HH_SRC")
B2HH_OUT = os.getenv("B2HH_OUT")
FitTotal_path = os.path.abspath(B2HH_SRC+'/FitTotal')
sys.path.append(FitTotal_path)
from configurations import configuration
config = configuration.getConfigs(args.splitConf)
from copy import deepcopy

if config['generate']['flag']: 
  from ROOT import TDatime, gSystem, RooRandom
  jobpid = gSystem.GetPid()
  now = TDatime()
  today = now.GetDate()
  clock = now.GetTime()
  seqJob = int(args.toyIndex)
  rndSeed = today+clock+jobpid+seqJob;
  RooRandom.randomGenerator().SetSeed(rndSeed);

ws = RooWorkspace()
zero = WS( ws, RooConstVar("zero","zero",0))
one  = WS( ws, RooConstVar("one","one",1))

unblindState = WS( ws, RooCategory('unblindState','unblindState'))
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
                                          'pipi' : '-1.3.-1.3',
                                          'kk'   : '2.-2.2.-2' },
                          },
            'magnet'    : args.magnet,
            'bdkpi'     : { 'state' : 'kpi',
                            'pid'   : '5.-2.-5.3' },
            'bskpi'     : { 'state' : 'kpi',
                            'pid'   : '5.-2.-5.3' },
            'bdpipi_kpi' : { 'state' : 'kpi',
                             'pid' : '5.-2.-5.3' },
            'bskk_kpi' : { 'state' : 'kpi',
                             'pid' : '5.-2.-5.3' },
            'bdpipi'    : { 'state' : 'pipi',
                            'pid'   : '-1.3.-1.3' },
            'bspipi'    : { 'state' : 'pipi',
                            'pid'   : '-1.3.-1.3' },
            'bdkpi_pipi' : { 'state' : 'pipi',
                             'pid' : '-1.3.-1.3' },
            'bskpi_pipi' : { 'state' : 'pipi',      ###new bskpi_pipi -> actually bspik_pipi but easier convention
                             'pid' : '-1.3.-1.3' }, ###new bskpi_pipi
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
                            'pid'   : '-1.3.-1.3' },
            'bkg_kk'    : { 'state' : 'kk',
                            'pid' : '2.-2.2.-2' },
            'phys_kpi1' : { 'state' : 'kpi',
                            'pid'   : '5.-2.-5.3' },
            'phys_kpi2' : { 'state' : 'kpi',
                            'pid'   : '5.-2.-5.3' },
            'phys_pipi' : { 'state' : 'pipi',
                            'pid'   : '-1.3.-1.3' },
            'phys_kk' : { 'state' : 'kk',
                          'pid' : '2.-2.2.-2' }
           }


taggerList = args.taggers
sstagName = None
for tagName in taggerList:
  if "SS" in tagName:
    sstagName = tagName

from ROOT import RooDataSet, RooProdPdf, RooArgList, TFile, TTree, RooAddPdf
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
    getTemplates(name,year,nfinTaggingSignal,
                 [ 'eta'+tag for tag in taggerList ], ws)

    createMassSignal(name,year,config,ws)
    createSignalAcceptance(name,year,args.magnet,config,'%s_%s'%(args.conf.split('_')[0],args.bdtCut),args.outDir,ws)
    createSignalTimeResModel(name,year,config,ws)
    createSignalOmegas(name,year,config,taggerList,ws)
    createSignalSinusoidTerms(name,year,config,taggerList,ws)
    createSignalTimePdf(name,year,config,ws)

    pdfmass = ws.obj("%s_pdfmass_%s" % (name,year))
    pdftime = ws.obj("%s_pdftime_%s" % (name,year))
    pdftimeGenT = ws.obj("%s_pdftimeGenT_%s" % (name,year))
    pdftimeGenU = ws.obj("%s_pdftimeGenU_%s" % (name,year))
    pdf = WS(ws, RooProdPdf("%s_pdf_%s" % (name,year),
                            "%s_pdf_%s" % (name,year),
                            RooArgList(pdfmass,pdftime)))
    pdfGenT = WS(ws, RooProdPdf("%s_pdfGenT_%s" % (name,year),
                                "%s_pdfGenT_%s" % (name,year),
                                RooArgList(pdfmass,pdftimeGenT)))
    pdfGenU = WS(ws, RooProdPdf("%s_pdfGenU_%s" % (name,year),
                                "%s_pdfGenU_%s" % (name,year),
                                RooArgList(pdfmass,pdftimeGenU)))

  for name in ['bdkpi','bskpi','bdpipi','bskk']:
    createMassResoModel(name,year,config,ws)
  print('-------------------- Cross-feed Bkg ---------------------')
  for name in [ 'bdkpi_pipi','bskpi_pipi','bdkpi_kk', 'lbpk_kk', 'bdpipi_kpi','bskk_kpi' ]: ###new bskpi_pipi
    #for name in [ 'bdkpi_pipi','bdkpi_kk', 'bdpipi_kpi','bskk_kpi' ]:
    print('---------------------- %s -----------------------'%name)
    nfinTaggingCross = inputs['tagging']['file'].format(fState = selConf[name]['state'],
                                                        bdtName= selConf['bdt']['name'],
                                                        bdtCut = selConf['bdt']['cut'],
                                                        year   = year,
                                                        magnet = selConf['magnet'])
    getTemplatesCross(name,year,nfinTaggingCross,
                      [ 'eta'+tag for tag in taggerList ], ws)

    createMassCrossFeed(name,year,config,selConf,ws)
    createSignalAcceptance(name,year,args.magnet,config,'%s_%s'%(args.conf.split('_')[0],args.bdtCut),args.outDir,ws)
    createSignalTimeResModel(name,year,config,ws)
    createSignalOmegas(name,year,config,taggerList,ws)
    createSignalSinusoidTerms(name,year,config,taggerList,ws)
    createSignalTimePdf(name,year,config,ws)

    pdfmass = ws.obj("%s_pdfmass_%s" % (name,year))
    pdftime = ws.obj("%s_pdftime_%s" % (name,year))
    pdftimeGenT = ws.obj("%s_pdftimeGenT_%s" % (name,year))
    pdftimeGenU = ws.obj("%s_pdftimeGenU_%s" % (name,year))

    pdf = WS(ws, RooProdPdf("%s_pdf_%s" % (name,year),
                            "%s_pdf_%s" % (name,year),
                            RooArgList(pdfmass,pdftime)))
    pdfGenT = WS(ws, RooProdPdf("%s_pdfGenT_%s" % (name,year),
                                "%s_pdfGenT_%s" % (name,year),
                                RooArgList(pdfmass,pdftimeGenT)))
    pdfGenU = WS(ws, RooProdPdf("%s_pdfGenU_%s" % (name,year),
                                "%s_pdfGenU_%s" % (name,year),
                                RooArgList(pdfmass,pdftimeGenU)))

  print('---------------------- Comb Bkg -----------------------')
  for name,state in [('bkg_kpi','kpi'),('bkg_pipi','pipi'),('bkg_kk','kk')]:
    nfinTaggingBkg = inputs['tagging']['file'].format(fState=selConf[name]['state'],
                                                      bdtName=selConf['bdt']['name'],
                                                      bdtCut=selConf['bdt']['cut'],
                                                      year=year,
                                                      magnet=selConf['magnet'])

    getTemplates(name,year,nfinTaggingBkg,
                 ['eta'+tag for tag in taggerList ], ws)

    createMassCombBkg(name,year,config,selConf,sstagName, ws)
    createBkgTimePdf(name,year,config,selConf,sstagName,ws)
    createBkgOmega(name,year,config,taggerList,ws)
    createBkgTag(name,year,config,taggerList,state,ws)


    pdfList = RooArgList()
    pdfmass = ws.obj("%s_pdfmass_%s" % (name,year))
    pdftime = ws.obj("%s_pdftime_%s" % (name,year))
    pdfomega = ws.obj("%s_pdftag_%s" % (name,year))
    pdfstate = ws.obj("%s_pdfstate_%s" % (name,year))

    pdf = WS(ws, RooProdPdf("%s_pdf_%s"%(name,year),
                            "%s_pdf_%s"%(name,year),
                            RooArgSet(pdfomega),
                            RooFit.Conditional(RooArgSet(pdftime),
                                               RooArgSet(ws.obj('time'))),
                            RooFit.Conditional(RooArgSet(pdfmass),
                                               RooArgSet(ws.obj('mass'))),
                            RooFit.Conditional(RooArgSet(pdfstate),
                                               RooArgSet(ws.obj('p')))))
  print('---------------------- Phys. Bkg -----------------------')
  for name,state in [('phys_kpi1','kpi'),('phys_kpi2','kpi'),('phys_pipi','pipi'),('phys_kk','kk')]:
    nfinTaggingPhys = inputs['tagging']['file'].format(fState  = selConf[name]['state'],
                                                       bdtName = selConf['bdt']['name'],
                                                       bdtCut  = selConf['bdt']['cut'],
                                                       year    = year,
                                                       magnet  = selConf['magnet'])

    getTemplates(name,year,nfinTaggingPhys,
                 ['eta'+tag for tag in taggerList ], ws)

    createMassPhysBkg(name,year,config,ws)
    createPhysTimePdf(name,year,config,selConf,sstagName,ws)
    createPhysOmega(name,year,config,taggerList,ws)
    createBkgTag(name,year,config,taggerList,state,ws)

    pdfList = RooArgList()
    pdfmass = ws.obj("%s_pdfmass_%s" % (name,year))
    pdftime = ws.obj("%s_pdftime_%s" % (name,year))
    pdfomega = ws.obj("%s_pdftag_%s" % (name,year))
    pdfstate = ws.obj("%s_pdfstate_%s" % (name,year))
    pdfTimeOmega = WS(ws, RooProdPdf("%s_pdfTimeTag_%s"%(name,year),
                                     "%s_pdfTimeTag_%s"%(name,year),
                                     RooArgSet(pdfomega),
                                     RooFit.Conditional(RooArgSet(pdftime),
                                                        RooArgSet(ws.obj('time'))),
                                     RooFit.Conditional(RooArgSet(pdfstate),
                                                        RooArgSet(ws.obj('p')))))

    pdfList.add(pdfmass)
    pdfList.add(pdfTimeOmega)

    pdf = WS( ws, RooProdPdf("%s_pdf_%s" % (name,year),
                             "%s_pdf_%s" % (name,year), pdfList))

    pdf.Print("v")
  print('********************************************************')
print('********************************************************')

obs = RooArgSet()
obsList  = [ 'mass','time','p','fState']#,'timeErr' ]
obsList += [ 'eta'+tag for tag in taggerList ]
obsList += [ 'q'+tag for tag in taggerList ]
print('Required observables: ')
for ob in obsList:
  tmp = ws.obj(ob)
  obs.add(tmp)


from ROOT import RooFormulaVar

totalPdfList = RooArgList()
totalPdfGenListT = RooArgList()
totalPdfGenListU = RooArgList()

print('Creating yields variables')
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
  n_bskpi_pipi = WS( ws, RooFormulaVar("n_bskpi_pipi_%s"%year,"n_bskpi_pipi_%s"%year,"@0*(@1+@2)/(@3+@4)",             ###new bskpi_pipi
                                       RooArgList(n_bskpi,
                                                  ws.obj('eff_bdkpi_pipi_%s'%year),ws.obj('eff_bdpik_pipi_%s'%year),  ###see better
                                                  ws.obj('eff_bdkpi_kpi_%s'%year),ws.obj('eff_bdpik_pik_%s'%year))))  ###see better
  n_bdkpi_kk = WS( ws, RooFormulaVar("n_bdkpi_kk_%s"%year,"n_bdkpi_kk_%s"%year,"@0*(@1+@2)/(@3+@4)",
                                     RooArgList(n_bdkpi,
                                                ws.obj('eff_bdkpi_kk_%s'%year),ws.obj('eff_bdpik_kk_%s'%year),
                                                ws.obj('eff_bdkpi_kpi_%s'%year),ws.obj('eff_bdpik_pik_%s'%year))))

  R_bdkk = WS(ws, RooRealVar("R_bdkk_%s"%year,"R_bdkk_%s"%year,0.01,0,1))
  n_bdkk = WS(ws, RooFormulaVar("n_bdkk_%s"%year,"n_bdkk_%s"%year,"@0*@1",RooArgList(n_bskk,R_bdkk)))
  R_lbpk = WS(ws, RooRealVar("R_lbpk_%s"%year,"R_lbpk_%s"%year,0.02,0,1))
  n_lbpk_kk = WS(ws, RooFormulaVar("n_lbpk_kk_%s"%year,"n_lbpk_kk_%s"%year,"@0*@1",RooArgList(n_bskk,R_lbpk)))
  n_bkg_kpi = WS( ws, RooRealVar("n_bkg_kpi_%s"%year,"n_bkg_kpi_%s"%year,100000,0,1e6))
  n_bkg_pipi = WS( ws, RooRealVar("n_bkg_pipi_%s"%year,"n_bkg_pipi_%s"%year,100000,0,1e6))
  n_bkg_kk = WS( ws, RooRealVar("n_bkg_kk_%s"%year,"n_bkg_kk_%s"%year,10000,0,1e6))
  n_phys_kpi1 = WS( ws, RooRealVar("n_phys_kpi1_%s"%year,"n_phys_kpi1_%s"%year,10000,0,1e6))
  n_phys_kpi2 = WS( ws, RooRealVar("n_phys_kpi2_%s"%year,"n_phys_kpi2_%s"%year,1000,0,1e6))
  n_phys_pipi = WS( ws, RooRealVar("n_phys_pipi_%s"%year,"n_phys_pipi_%s"%year,1000,0,1e6))
  n_phys_kk = WS( ws, RooRealVar("n_phys_kk_%s"%year,"n_phys_kk_%s"%year,1000,0,1e6))

  yieldsKPI = RooArgList()
  pdfsKPI = RooArgList()
  pdfsKPIGenT = RooArgList()
  pdfsKPIGenU = RooArgList()
  mass = ws.obj('mass')
  for name in ['bdkpi','bskpi','bdpipi_kpi','bskk_kpi']:
    yieldsKPI.add(ws.obj('n_%s_%s'%(name,year)))
    pdfsKPI.add(ws.obj('%s_pdf_%s'%(name,year)))
    pdfsKPIGenT.add(ws.obj('%s_pdfGenT_%s'%(name,year)))
    pdfsKPIGenU.add(ws.obj('%s_pdfGenU_%s'%(name,year))) 
  for name in ['bkg_kpi','phys_kpi1','phys_kpi2']:
    yieldsKPI.add(ws.obj('n_%s_%s'%(name,year)))
    pdfsKPI.add(ws.obj('%s_pdf_%s'%(name,year)))
    pdfsKPIGenT.add(ws.obj('%s_pdf_%s'%(name,year)))
    pdfsKPIGenU.add(ws.obj('%s_pdf_%s'%(name,year)))
  
  yieldsPIPI = RooArgList()
  pdfsPIPI = RooArgList()
  pdfsPIPIGenT = RooArgList()
  pdfsPIPIGenU = RooArgList()
  for name in ['bdpipi','bspipi','bdkpi_pipi', 'bskpi_pipi']:
    yieldsPIPI.add(ws.obj('n_%s_%s'%(name,year)))
    pdfsPIPI.add(ws.obj('%s_pdf_%s'%(name,year)))
    pdfsPIPIGenT.add(ws.obj('%s_pdfGenT_%s'%(name,year)))
    pdfsPIPIGenU.add(ws.obj('%s_pdfGenU_%s'%(name,year))) 
  for name in ['bkg_pipi','phys_pipi']:
    yieldsPIPI.add(ws.obj('n_%s_%s'%(name,year)))
    pdfsPIPI.add(ws.obj('%s_pdf_%s'%(name,year)))
    pdfsPIPIGenT.add(ws.obj('%s_pdf_%s'%(name,year)))
    pdfsPIPIGenU.add(ws.obj('%s_pdf_%s'%(name,year)))
  
  yieldsKK = RooArgList()
  pdfsKK = RooArgList()
  pdfsKKGenT = RooArgList()
  pdfsKKGenU = RooArgList()
  for name in ['bskk','bdkpi_kk','bdkk','lbpk_kk']:
    yieldsKK.add(ws.obj('n_%s_%s'%(name,year)))
    pdfsKK.add(ws.obj('%s_pdf_%s'%(name,year)))
    pdfsKKGenT.add(ws.obj('%s_pdfGenT_%s'%(name,year)))
    pdfsKKGenU.add(ws.obj('%s_pdfGenU_%s'%(name,year)))
  for name in ['bkg_kk','phys_kk']:
    yieldsKK.add(ws.obj('n_%s_%s'%(name,year)))
    pdfsKK.add(ws.obj('%s_pdf_%s'%(name,year)))
    pdfsKKGenT.add(ws.obj('%s_pdf_%s'%(name,year)))
    pdfsKKGenU.add(ws.obj('%s_pdf_%s'%(name,year)))
  
  from ROOT import RooAddPdf

  pdfKPI = WS( ws, RooAddPdf("pdf_kpi_%s"%year,"pdf_kpi_%s"%year,pdfsKPI,yieldsKPI))
  totalPdfList.add(pdfKPI)
  pdfPIPI = WS( ws, RooAddPdf("pdf_pipi_%s"%year,"pdf_pipi_%s"%year,pdfsPIPI,yieldsPIPI))
  totalPdfList.add(pdfPIPI)
  pdfKK = WS( ws, RooAddPdf("pdf_kk_%s"%year,"pdf_kk_%s"%year,pdfsKK,yieldsKK))
  totalPdfList.add(pdfKK)

  pdfKPIGenT = WS( ws, RooAddPdf("pdf_kpiGenT_%s"%year,"pdf_kpiGenT_%s"%year,pdfsKPIGenT,yieldsKPI))
  totalPdfGenListT.add(pdfKPIGenT)
  pdfPIPIGenT = WS( ws, RooAddPdf("pdf_pipiGenT_%s"%year,"pdf_pipiGenT_%s"%year,pdfsPIPIGenT,yieldsPIPI))
  totalPdfGenListT.add(pdfPIPIGenT)
  pdfKKGenT = WS( ws, RooAddPdf("pdf_kkGenT_%s"%year,"pdf_kkGenT_%s"%year,pdfsKKGenT,yieldsKK))
  totalPdfGenListT.add(pdfKKGenT)

  pdfKPIGenU = WS( ws, RooAddPdf("pdf_kpiGenU_%s"%year,"pdf_kpiGenU_%s"%year,pdfsKPIGenU,yieldsKPI))
  totalPdfGenListU.add(pdfKPIGenU)
  pdfPIPIGenU = WS( ws, RooAddPdf("pdf_pipiGenU_%s"%year,"pdf_pipiGenU_%s"%year,pdfsPIPIGenU,yieldsPIPI))
  totalPdfGenListU.add(pdfPIPIGenU)
  pdfKKGenU = WS( ws, RooAddPdf("pdf_kkGenU_%s"%year,"pdf_kkGenU_%s"%year,pdfsKKGenU,yieldsKK))
  totalPdfGenListU.add(pdfKKGenU)

from ROOT import RooSimultaneous
fState = ws.obj('fState')
totalPdfList.Print()
fState.Print('v')
pdf = WS( ws, RooSimultaneous("pdf","pdf",totalPdfList,fState))
pdfGenT = WS( ws, RooSimultaneous("pdfGenT","pdfGenT",totalPdfGenListT,fState))
pdfGenU = WS( ws, RooSimultaneous("pdfGenU","pdfGenU",totalPdfGenListU,fState))
   
pdfName = 'pdf'
pdf = ws.obj(pdfName)
print('Whole pdf created')
print('********************************************************')

params = pdf.getParameters(obs)
cut = '%s_%s' % (selConf['bdt']['name'],selConf['bdt']['cut'])
for tag in taggerList:
  cut = cut+"_"+tag

nfinInputParams = inputs['fitParams']['file'].format(outdir    = args.outDir,
                                                     bdtName   = selConf['bdt']['name'],
                                                     bdtCut    = selConf['bdt']['cut'],
                                                     taggers   = '_'.join(taggerList),
                                                     magnet    = args.magnet,
                                                     blindState= 'Blind' if args.blindFlag else 'Unblind' )
print("Reading input params from: %s" % (nfinInputParams))
params.readFromFile(nfinInputParams)

params.selectByName('*_smoothed_*').setAttribAll('Constant',True)
print('initial parameters:')
params.Print("v")

#fState = ws.obj('fState')
#obs.remove(fState)

#################################### ADJUSTING ACCEPTANCES #########################################

for year in args.years:
  ws.obj('qOS').setLabel('Untag')
  ws.obj('q%s'%sstagName).setLabel('Untag')
  ws.obj('p').setLabel('kpi')
  for name in ['bdkpi','bdpipi_kpi','bskk_kpi', 'bskpi']:
    pdfT = ws.obj('%s_pdftimeGenT_%s'%(name,year))
    pdfU = ws.obj('%s_pdftimeGenU_%s'%(name,year))
    integralPdfT = pdfT.createIntegral(RooArgSet(ws.obj('time')))
    integralPdfU = pdfU.createIntegral(RooArgSet(ws.obj('time')))
    print 'Integrals for tagged/untagged pdf of %s: %g'%(name,integralPdfU.getVal()/integralPdfT.getVal())
    ratio = integralPdfU.getVal()/integralPdfT.getVal()
    accParams = params.selectByName('%s_accTimeT_%s_*'%(name,year))
    parIter = accParams.createIterator()
    while 1:
      tmp = parIter.Next()
      if not tmp: break
      tmp.setVal(tmp.getVal()*ratio)

  ws.obj('p').setLabel('pipi')
  for name in ['bdkpi_pipi','bdpipi','bspipi','bskpi_pipi']:
    pdfT = ws.obj('%s_pdftimeGenT_%s'%(name,year))
    pdfU = ws.obj('%s_pdftimeGenU_%s'%(name,year))
    integralPdfT = pdfT.createIntegral(RooArgSet(ws.obj('time')))
    integralPdfU = pdfU.createIntegral(RooArgSet(ws.obj('time')))
    print 'Integrals for tagged/untagged pdf of %s: %g'%(name,integralPdfU.getVal()/integralPdfT.getVal())
    ratio = integralPdfU.getVal()/integralPdfT.getVal()
    accParams = params.selectByName('%s_accTimeT_%s_*'%(name,year))
    parIter = accParams.createIterator()
    while 1:
      tmp = parIter.Next()
      if not tmp: break
      tmp.setVal(tmp.getVal()*ratio)

  ws.obj('p').setLabel('kk')
  for name in ['bdkpi_kk','bskk','bdkk','lbpk_kk']:
    pdfT = ws.obj('%s_pdftimeGenT_%s'%(name,year))
    pdfU = ws.obj('%s_pdftimeGenU_%s'%(name,year))
    integralPdfT = pdfT.createIntegral(RooArgSet(ws.obj('time')))
    integralPdfU = pdfU.createIntegral(RooArgSet(ws.obj('time')))
    print 'Integrals for tagged/untagged pdf of %s: %g'%(name,integralPdfU.getVal()/integralPdfT.getVal())
    ratio = integralPdfU.getVal()/integralPdfT.getVal()
    accParams = params.selectByName('%s_accTimeT_%s_*'%(name,year))
    parIter = accParams.createIterator()
    while 1:
      tmp = parIter.Next()
      if not tmp: break
      tmp.setVal(tmp.getVal()*ratio)


#################################### ADJUSTING ACCEPTANCES #########################################

from ROOT import TFile, TTree, TChain
data = {}
dataAll = {
  'KPI' : {},
  'PIPI' : {},
  'KK' : {},
}

import random

p = ws.obj('p')


############################ GENERATE KPI #################################
for year in args.years:
  data['KPI'] = {}
  data['KPI'][year] = {}
  dataAll['KPI'][year] = RooDataSet('dataKPI','dataKPI',obs)
  dataAll['PIPI'][year] = RooDataSet('dataPIPI','dataPIPI',obs)
  dataAll['KK'][year] = RooDataSet('dataKK','dataKK',obs)
  
  p.clearTypes()
  p.defineType('kpi',1)
  p.defineType('pik',-1)
  data['KPI'][year]['bkg_kpi'] = ws.obj('bkg_kpi_pdf_%s'%year).generate(obs,RooFit.NumEvents(int(ws.obj('n_bkg_kpi_%s'%year).getVal())),
                                                                      RooFit.Verbose(False),
                                                                      RooFit.AutoBinned(True),
                                                                      RooFit.Extended())
  for name in ['phys_kpi1','phys_kpi2']:
    data['KPI'][year][name] = ws.obj('%s_pdf_%s'%(name,year)).generate(obs,RooFit.NumEvents(int(ws.obj('n_%s_%s'%(name,year)).getVal())),
                                                                      RooFit.Verbose(False),
                                                                      RooFit.AutoBinned(True),
                                                                      RooFit.Extended())
  
  for name in ['bdkpi','bskpi','bdpipi_kpi','bskk_kpi']:
    pdfT = ws.obj('%s_pdfGenT_%s'%(name,year))
    yields = int(ws.obj('n_%s_%s'%(name,year)).getVal())
    dataT = pdfT.generate(obs,RooFit.NumEvents(yields),
                          RooFit.Verbose(False),
                          RooFit.AutoBinned(True),
                          RooFit.Extended())
    taggedYields = dataT.sumEntries('q%s!=q%s::Untag'%(sstagName,sstagName))
    untaggedYields = dataT.sumEntries('q%s==q%s::Untag'%(sstagName,sstagName))
    taggingEff = taggedYields/(taggedYields+untaggedYields)
    dataT = dataT.reduce(RooFit.Cut('q%s!=q%s::Untag'%(sstagName,sstagName)))
    data['KPI'][year][name] = dataT
    accT = ws.obj('%s_accTimeT_%s'%(name,year))
    accU = ws.obj('%s_accTimeU_%s'%(name,year))
    pdfU = ws.obj('%s_pdfGenU_%s'%(name,year))
    n = 0
    dataU = RooDataSet('dataU','dataU',obs)
    while n < untaggedYields:
      dataUTMP = pdfU.generate(obs,RooFit.NumEvents(int(yields)),
                               RooFit.Verbose(False),
                               RooFit.AutoBinned(True),
                               RooFit.Extended())
      dataUTMP = dataUTMP.reduce(RooFit.Cut('q%s==q%s::Untag'%(sstagName,sstagName)))
      i = 0
      for i in range(dataUTMP.numEntries()):
        obs.assignFast(dataUTMP.get(i))
        if random.uniform(0,pdfU.getVal()) > taggingEff*pdfT.getVal():
          dataU.add(obs)
          n = n+1
        if n >= untaggedYields: break
    data['KPI'][year][name].append(dataU)
  
  for k,d in data['KPI'][year].iteritems():
    dataAll['KPI'][year].append(d)

  ############################ GENERATE PIPI ################################
  data['PIPI'] = {}
  data['PIPI'][year] = {}
  
  p.clearTypes()
  p.defineType('pipi',0)
  data['PIPI'][year]['bkg_pipi'] = ws.obj('bkg_pipi_pdf_%s'%year).generate(obs,RooFit.NumEvents(int(ws.obj('n_bkg_pipi_%s'%year).getVal())),
                                                                           RooFit.Verbose(False),
                                                                           RooFit.AutoBinned(True),
                                                                           RooFit.Extended())
  for name in ['phys_pipi']:
    data['PIPI'][year][name] = ws.obj('%s_pdf_%s'%(name,year)).generate(obs,RooFit.NumEvents(int(ws.obj('n_%s_%s'%(name,year)).getVal())),
                                                                        RooFit.Verbose(False),
                                                                        RooFit.AutoBinned(True),
                                                                        RooFit.Extended())
  
  for name in ['bdpipi','bspipi','bdkpi_pipi']:
    pdfT = ws.obj('%s_pdfGenT_%s'%(name,year))
    yields = int(ws.obj('n_%s_%s'%(name,year)).getVal())
    dataT = pdfT.generate(obs,RooFit.NumEvents(yields),
                          RooFit.Verbose(False),
                          RooFit.AutoBinned(True),
                          RooFit.Extended())
    taggedYields = dataT.sumEntries('q%s!=q%s::Untag'%(sstagName,sstagName))
    untaggedYields = dataT.sumEntries('q%s==q%s::Untag'%(sstagName,sstagName))
    taggingEff = taggedYields/(taggedYields+untaggedYields)
    dataT = dataT.reduce(RooFit.Cut('q%s!=q%s::Untag'%(sstagName,sstagName)))
    data['PIPI'][year][name] = dataT
    accT = ws.obj('%s_accTimeT_%s'%(name,year))
    accU = ws.obj('%s_accTimeU_%s'%(name,year))
    pdfU = ws.obj('%s_pdfGenU_%s'%(name,year))
    n = 0
    dataU = RooDataSet('dataU','dataU',obs)
    while n < untaggedYields:
      dataUTMP = pdfU.generate(obs,RooFit.NumEvents(yields),
                               RooFit.Verbose(False),
                               RooFit.AutoBinned(True),
                               RooFit.Extended())
      dataUTMP = dataUTMP.reduce(RooFit.Cut('q%s==q%s::Untag'%(sstagName,sstagName)))
      i = 0
      for i in range(dataUTMP.numEntries()):
        obs.assignFast(dataUTMP.get(i))
        if random.uniform(0,pdfU.getVal()) > taggingEff*pdfT.getVal():
          dataU.add(obs)
          n = n+1
        if n >= untaggedYields: break
    data['PIPI'][year][name].append(dataU)
  
  for k,d in data['PIPI'][year].iteritems():
    dataAll['PIPI'][year].append(d)

  ############################ GENERATE KK #################################
  data['KK'] = {}
  data['KK'][year] = {}
  p.clearTypes()
  p.defineType('kk',2)
  data['KK'][year]['bkg_kk'] = ws.obj('bkg_kk_pdf_%s'%year).generate(obs,RooFit.NumEvents(int(ws.obj('n_bkg_kk_%s'%year).getVal())),
                                                                   RooFit.Verbose(False),
                                                                   RooFit.AutoBinned(True),
                                                                   RooFit.Extended())
  for name in ['phys_kk']:
    data['KK'][year][name] = ws.obj('%s_pdf_%s'%(name,year)).generate(obs,RooFit.NumEvents(int(ws.obj('n_%s_%s'%(name,year)).getVal())),
                                                                      RooFit.Verbose(False),
                                                                      RooFit.AutoBinned(True),
                                                                      RooFit.Extended())
  
  for name in ['bskk','bdkk','bdkpi_kk','lbpk_kk']:
    pdfT = ws.obj('%s_pdfGenT_%s'%(name,year))
    yields = int(ws.obj('n_%s_%s'%(name,year)).getVal())
    dataT = pdfT.generate(obs,RooFit.NumEvents(yields),
                          RooFit.Verbose(False),
                          RooFit.AutoBinned(True),
                          RooFit.Extended())
    taggedYields = dataT.sumEntries('q%s!=q%s::Untag'%(sstagName,sstagName))
    untaggedYields = dataT.sumEntries('q%s==q%s::Untag'%(sstagName,sstagName))
    taggingEff = taggedYields/(taggedYields+untaggedYields)
    dataT = dataT.reduce(RooFit.Cut('q%s!=q%s::Untag'%(sstagName,sstagName)))
    data['KK'][year][name] = dataT
    accT = ws.obj('%s_accTimeT_%s'%(name,year))
    accU = ws.obj('%s_accTimeU_%s'%(name,year))
    pdfU = ws.obj('%s_pdfGenU_%s'%(name,year))
    n = 0
    dataU = RooDataSet('dataU','dataU',obs)
    while n < untaggedYields:
      dataUTMP = pdfU.generate(obs,RooFit.NumEvents(yields),
                               RooFit.Verbose(False),
                               RooFit.AutoBinned(True),
                               RooFit.Extended())
      dataUTMP = dataUTMP.reduce(RooFit.Cut('q%s==q%s::Untag'%(sstagName,sstagName)))
      i = 0
      for i in range(dataUTMP.numEntries()):
        obs.assignFast(dataUTMP.get(i))
        #ratio = taggingEff * accT.getVal()/accU.getVal()
        if random.uniform(0,pdfU.getVal()) > taggingEff*pdfT.getVal():
          dataU.add(obs)
          n = n+1
        if n >= untaggedYields: break
    data['KK'][year][name].append(dataU)
  
  for k,d in data['KK'][year].iteritems():
    dataAll['KK'][year].append(d)

############################ PUTTING EVERYTHING TOGETHER ###############################
p.clearTypes()
p.defineType('pipi',0)
p.defineType('kpi',1)
p.defineType('pik',-1)
p.defineType('kk',2)
import array
def rename_idx_branches_and_save(_tree,_fout):

    # Store buffers for branch values
    branch_buffers = {}
    new_tree = ROOT.TTree(_tree.GetName(), _tree.GetTitle())
    for branch in _tree.GetListOfBranches():
        name = branch.GetName()
        leaf = branch.GetLeaf(name)
        leaf_type = leaf.GetTypeName()
        buf = None
        format_char = None
        # Determine C++ type and format string
        if leaf_type == "Int_t":
            buf = array.array('i',[0])
            format_char = 'I'
        elif leaf_type == "Float_t":
            buf = array.array('f',[0.])
            format_char = 'F'
        elif leaf_type == "Double_t":
            buf = array.array('d',[0.])
            format_char = 'D'
        elif leaf_type == "UInt_t":
            buf = array.array('I',[0])
            format_char = 'i'
        elif leaf_type == "Long64_t":
            buf = array.array('l',[0])
            format_char = 'L'
        else:
            print("Skipping unsupported type: %s for branch %s"%(leaf_type,name))
            continue

        # Bind the input branch to the buffer
        _tree.SetBranchAddress(name, buf)

        # Rename if ends in _idx
        new_name = name[:-4] if name.endswith("_idx") else name

        # Create new branch with new name
        new_tree.Branch(new_name, buf, "%s/%s"%(new_name,format_char))
        branch_buffers[name] = buf

    # Fill new tree
    for i in range(_tree.GetEntries()):
        _tree.GetEntry(i)
        new_tree.Fill()
    new_tree.Print()
    _fout.WriteTObject(new_tree,'','Overwrite')
    _fout.ls()

from ROOT import RooAbsData
link_options = []
for fs in ['KPI','PIPI','KK']:
  for y in args.years:
    link_options.append(RooFit.Link('%s_%s'%(fs,y),dataAll[fs][y]))
    for k,d in data[fs][y].iteritems():
      d.setDefaultStorageType(RooAbsData.Tree)
      d.Print('v')
      dataOut = RooDataSet('dataOut','dataOut',obs,RooFit.Import(d))
      outTree = dataOut.tree()
      outTree.SetName(k)
      outTree.SetTitle(k)
      outTree.Print()
      outFile = TFile('%s/Toys/%s/%s/%s_%s_%s.root' % (B2HH_OUT,args.outDir,args.toyIndex,k,args.outDir,args.toyIndex),'RECREATE')
      rename_idx_branches_and_save(outTree,outFile)
      #outFile.WriteTObject(outTree,'','Overwrite')
      outFile.Close()
      del dataOut
      
fState = ws.obj('fState')
dataTot = RooDataSet('data','data',obs,RooFit.Index(fState),*link_options)
dataTot.setDefaultStorageType(RooAbsData.Tree)
dataTot.Print('v')
obs.add(ws.obj('fState'))
dataOut = RooDataSet('dataOut','dataOut',obs,RooFit.Import(dataTot))
outTree = dataOut.tree()
outTree.SetName('b2hh')
outTree.SetTitle('b2hh')
outTree.Print()
outFile = TFile('%s/Toys/%s/%s/b2hh_%s_%s.root' % (B2HH_OUT,args.outDir,args.toyIndex,args.outDir,args.toyIndex),'RECREATE')
rename_idx_branches_and_save(outTree,outFile)
#outFile.WriteTObject(outTree,'','Overwrite')
outFile.Close()

