from B2DXFitters.WS import WS
import sys
from inpututils import inputs
def createPIDVariables(selConf = {}, year = '', ws = None) :
  print('utils: createPIDVariables: starts')
  from ROOT import RooRealVar
  import os
  import sqlite3 as sql
  inDataBase = inputs['effPID']['file']
  print('utils: createPIDVariables: input database: %s'%inDataBase)
  pidEffs= sql.connect(inDataBase)
  curs   = pidEffs.cursor()
  name   = selConf['bdt']['name']
  config = selConf['bdt']['config']
  bdtCut = selConf['bdt']['cut']
  magnet = selConf['magnet']
  year   = year
  decays = ['bdkpi','bdpik','bskpi','bspik','bdpipi','bspipi','bskk']
  cuts   = selConf['bdt']['pid']
  #{ 'kpi' : '5.-5.-5.5',
  #         'pik' : '-5.5.5.-5',
  #         'pipi' : '-3.5.-3.5',
  #         'kk' : '4.0.4.0' }
  #         'kk' : '4.-5.4.-5' }
  
  for decay in decays:
    for state,cut in cuts.iteritems():
      cut1 = cut.split('.')[0]
      cut2 = cut.split('.')[1]
      cut3 = cut.split('.')[2]
      cut4 = cut.split('.')[3]
      #config = cut
      command = 'select eff from pidEffs where finalState=\"%s\" and decay = \"%s\" and name = \"%s\" \
                 and magnet = \"%s\" and year = \"%s\" and plusCUT1=%s and plusCUT2 = %s \
                 and minusCUT1 = %s and minusCUT2 = %s \
                 and splotFlag = 1 and bdtConfig=\"%s\" and bdtCUT = %s;' % (state,decay,name,magnet,year,
                                                                            cut1,cut2,cut3,cut4,config,bdtCut)
      print command
      eff = curs.execute(command).fetchone()[0]
      
      effVar = WS( ws, RooRealVar('eff_%s_%s_%s' % (decay,state,year),
                                  'eff_%s_%s_%s' % (decay,state,year),
                                  eff))
      effVar.Print()
  
  print('utils: createPIDVariables: ends')


def createObservables(config, ws) :
  print('utils: createObservables: starts')
  from ROOT import RooRealVar, RooCategory
  conf = config['observables']
  tmp = None
  for name in conf.keys():
    if 'range' in conf[name].keys():
      tmpRange = conf[name]['range']
      tmp = WS( ws, RooRealVar(name,name,tmpRange[0],tmpRange[1]))
      if 'binnings' in conf[name].keys():
        for binName,bins in conf[name]['binnings'].iteritems():
          tmp.setBins(bins,binName)
      if 'units' in conf[name].keys():
        tmp.setUnit(conf[name]['units'])
      
    if 'types' in conf[name].keys():
      tmp = WS(ws, RooCategory(name,name))
      for catType in conf[name]['types']:
        tmp.defineType(catType[0],catType[1])
        print catType[0], catType[1]
    tmp.Print()
  del tmp
  print('utils: createObservables: ends')
  
def getTemplates(name = 'bdkpi', year = '', fileName = 'histos.root', varNames = [], ws = None) :
  print('utils: getTemplates: starts')
  from ROOT import TFile, TH1D, RooDataHist, RooHistPdf, RooArgList, RooArgSet, RooUniform
  print('utils: getTemplates: input file: %s'%fileName)
  inFile = TFile(fileName,"READ")
  for varName in varNames :
    var = ws.obj(varName)
    hname = "h_%s_%s" % (name,varName)
    #hname = "h_%s_%s" % ('bdpipi','etaOS')
    print('utils: getTemplates: input histogram: %s' %(hname))
    h = inFile.Get(hname)

    dataHist = RooDataHist("%s_%s_Hist_%s" % (name,varName,year),
                           "%s_%s_Hist_%s" % (name,varName,year),
                           RooArgList(var),h)
    histPdf  = WS(ws, RooHistPdf("%s_%s_HistPdf_%s" % (name,varName,year),
                                 "%s_%s_HistPdf_%s" % (name,varName,year),
                                 RooArgSet(var),dataHist))
    histPdf.setUnitNorm(True)
    del h, dataHist
    
  inFile.Close()
  del inFile
  print('utils: getTemplates: ends')
  
def getTemplatesCross(name = 'bdkpi_pipi', year = '', fileName = 'histos.root', varNames = [], ws = None) :
  print('utils: getTemplatesCross: starts')
  from ROOT import TFile, TH1D, RooDataHist, RooHistPdf, RooArgList, RooArgSet
  print("utils: getTemplatesCross: input file: %s" % (fileName))
  inFile = TFile(fileName,"READ")
  #inFile.ls()
  for varName in varNames :
    var = ws.obj(varName)
                                                    ###############
    #print("utils: getTemplatesCross: %s h_%s_%s" % (name,'bdpipi','etaOS')) ###############
    #h = inFile.Get("h_%s_%s" % ('bdpipi','etaOS'))                          ###############
                                                                              ###############
    print("utils: getTemplatesCross: %s h_%s_%s" % (name,name.split('_')[0],varName))
    h = inFile.Get("h_%s_%s" % (name.split('_')[0],varName))
    h.Print()
    dataHist = RooDataHist("%s_%s_Hist_%s" % (name,varName,year),
                           "%s_%s_Hist_%s" % (name,varName,year),
                           RooArgList(var),h)
    histPdf  = WS(ws, RooHistPdf("%s_%s_HistPdf_%s" % (name,varName,year),
                                 "%s_%s_HistPdf_%s" % (name,varName,year),
                                 RooArgSet(var),dataHist))
    histPdf.setUnitNorm(True)
    histPdf.Print("v")
    del h, dataHist

  inFile.Close()
  del inFile
  print('utils: getTemplatesCross: ends')
  
class Logger(object):

  def __init__(self):
      self.terminal = sys.stdout
      self.log = open("logfile.log", "a")

  def write(self, message):
      self.terminal.write(message)
      self.log.write(message)  

  def flush(self):
      #this flush method is needed for python 3 compatibility.
      #this handles the flush command by doing nothing.
      #you might want to specify some extra behavior here.
      pass    
