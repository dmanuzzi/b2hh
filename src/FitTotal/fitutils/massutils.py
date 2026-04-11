from B2DXFitters.WS import WS as WS
from inpututils import inputs
def createMassSignal(name = 'bdkpi', year = '', config = {}, ws = None):
  print('massutils: createMassSignal: starts')
  print('massutils: createMassSignal: channel: %s'%name)
  print('massutils: createMassSignal: year: %s'%year)
  
  from ROOT import RooRealVar, RooCachedPdf, RooArgSet, RooCBShape

  mass = ws.obj('mass')
  conf = config[name]['mass'][year]

  mean      = 0
  delta     = 0
  alpha     = 0
  alpha1    = 0
  alpha2    = 0
  sigmaTail = 0
  sigma1    = 0
  sigma2    = 0
  frac      = 0
  fracTail  = 0

  for varName,varVals in conf.iteritems():
    tmp = 0
    if type(varVals) == str:
      tmp = ws.obj('%s' % (varVals))
      print varVals
    else:
      tmp = WS( ws, RooRealVar("%s_mass_%s_%s" % (name,varName,year),
                               "%s_mass_%s_%s" % (name,varName,year),
                               varVals[0],varVals[1],varVals[2]))
      tmp.setConstant(varVals[3])
    tmp.Print()

    if varName == 'mean'      : mean      = tmp
    if varName == 'delta'     : delta     = tmp
    if varName == 'alpha'     : alpha     = tmp
    if varName == 'alpha1'    : alpha1    = tmp
    if varName == 'alpha2'    : alpha2    = tmp
    if varName == 'sigmaTail' : sigmaTail = tmp
    if varName == 'sigma1'    : sigma1    = tmp
    if varName == 'sigma2'    : sigma2    = tmp
    if varName == 'frac'      : frac      = tmp
    if varName == 'fracTail'  : fracTail  = tmp

  from ROOT import RooGaussian, RooFormulaVar, RooArgList, RooJohnsonFunc, RooAddPdf

  #print mean.GetName(),delta.GetName(),sigma1.GetName(),sigma2.GetName()
  shift = WS( ws, RooFormulaVar("%s_mass_shift_%s" % (name,year),
                                "%s_mass_shift_%s" % (name,year),
                                "@0+@1",RooArgList(mean,delta)))
  g1 = WS( ws, RooGaussian("%s_g1_%s" % (name,year),
                           "%s_g1_%s" % (name,year),
                           mass,shift,sigma1))
  g2 = WS( ws, RooGaussian("%s_g2_%s" % (name,year),
                           "%s_g2_%s" % (name,year),
                           mass,shift,sigma2))
  tail = WS( ws, RooJohnsonFunc("%s_massTail_%s" % (name,year),
                                "%s_massTail_%s" % (name,year),
                                mass,shift,sigma1,alpha1,alpha2))
  g = WS(ws, RooAddPdf("%s_g_%s" % (name,year),
                       "%s_g_%s" % (name,year),
                       RooArgList(g1,g2),RooArgList(frac)))
  pdf = WS( ws, RooAddPdf("%s_pdfmass_%s" % (name,year),
                          "%s_pdfmass_%s" % (name,year),
                          RooArgList(tail,g),RooArgList(fracTail)))
  pdf.Print()
  print('massutils: createMassSignal: ends')
  


def createMassResoModel(name = 'bdkpi', year = '', config = {}, ws = None):

  from ROOT import RooRealVar, RooGaussModel, RooAddModel, RooArgList, RooExponentialNew

  mass = ws.obj('mass')
  conf = config[name]['mass'][year]

  delta = 0
  sigma1 = 0
  sigma2 = 0
  frac = 0
  
  for varName,varVals in conf.iteritems():
  
    tmp = 0
    if type(varVals) == str:
      tmp = ws.obj("%s" %(varVals))
  
    else:
      tmp = ws.obj("%s_mass_%s_%s" % (name,varName,year))
      #tmp = WS( ws, RooRealVar("%s_mass_%s" % (name,varName),
      #                         "%s_mass_%s" % (name,varName),
      #                         varVals[0],varVals[1],varVals[2]))
      #tmp.setConstant(varVals[3])

    if varName == 'delta'  : delta = tmp
    if varName == 'sigma1' : sigma1 = tmp
    if varName == 'sigma2' : sigma2 = tmp
    if varName == 'frac'   : frac = tmp

  resModel1 = WS(ws, RooGaussModel("%s_mass_resModel1_%s" % (name,year),
                                   "%s_mass_resModel1_%s" % (name,year),
                                   mass,delta,sigma1))
  resModel2 = WS(ws, RooGaussModel("%s_mass_resModel2_%s" % (name,year),
                                   "%s_mass_resModel2_%s" % (name,year),
                                   mass,delta,sigma2))
  resModel = WS(ws, RooAddModel("%s_mass_resModel_%s" % (name,year),
                                "%s_mass_resModel_%s" % (name,year),
                                RooArgList(resModel1,resModel2),RooArgList(frac)))


def createMassCombBkg(name = 'bkg_kpi', year = '', config = {}, selConf = {}, sstagName = "SS", ws = None):

  from ROOT import RooRealVar, RooExponential, RooExponentialNew, RooExponentialNew2

  mass = ws.obj('mass')
  conf = config[name]['mass'][year]
  slope = 0
  p0    = 0
  p1    = 0
  p2    = 0
  p0_11 = 0
  p1_11 = 0
  p2_11 = 0
  p0_10 = 0
  p1_10 = 0
  p2_10 = 0
  p0_01 = 0
  p1_01 = 0
  p2_01 = 0
  p0_00 = 0
  p1_00 = 0
  p2_00 = 0

  for varName,varVals in conf.iteritems():

    tmp = 0
    if type(varVals) == str:
      tmp = ws.obj('%s' %(varVals))
    else:
      tmp = WS( ws, RooRealVar("%s_mass_%s_%s" %(name,varName,year),
                               "%s_mass_%s" %(name,varName),
                               varVals[0],varVals[1],varVals[2]))
      tmp.setConstant(varVals[3])


    if varName == 'slope'   : slope = tmp
    if varName == 'p0'      : p0    = tmp
    if varName == 'p1'      : p1    = tmp
    if varName == 'p2'      : p2    = tmp
    if varName == 'p0_11'   : p0_11 = tmp
    if varName == 'p1_11'   : p1_11 = tmp
    if varName == 'p2_11'   : p2_11 = tmp
    if varName == 'p0_10'   : p0_10 = tmp
    if varName == 'p1_10'   : p1_10 = tmp
    if varName == 'p2_10'   : p2_10 = tmp
    if varName == 'p0_01'   : p0_01 = tmp
    if varName == 'p1_01'   : p1_01 = tmp
    if varName == 'p2_01'   : p2_01 = tmp
    if varName == 'p0_00'   : p0_00 = tmp
    if varName == 'p1_00'   : p1_00 = tmp
    if varName == 'p2_00'   : p2_00 = tmp

  #pdf = WS( ws, RooExponential("%s_pdfmass_%s" % (name,year),
  #                             "%s_pdfmass_%s" % (name,year),
  #                             mass,slope))
  qOS = ws.obj('qOS')
  qSS = None
  if sstagName != None:
    qSS = ws.obj('q%s'%sstagName)
  else:
    qSS = ws.obj('qDummy')
  time = ws.obj('time')
  finalState = name.split('_')[1]
  from ROOT import TFile
  #pdf = WS( ws, RooExponentialNew("%s_pdfmass_%s" % (name,year),
  #                                "%s_pdfmass_%s" % (name,year),
  #                                qSS,mass,slopeT,slopeU))
  if selConf['bdt']['name'] == "PIPI":
    pdf = WS( ws, RooExponentialNew2("%s_pdfmass_%s" % (name,year),
                                     "%s_pdfmass_%s" % (name,year),
                                     qOS,qSS,mass,time,
                                     p0,p1,p2,
                                     p0,p1,p2,
                                     p0,p1,p2,
                                     p0,p1,p2))
  else:
    pdf = WS( ws, RooExponentialNew2("%s_pdfmass_%s" % (name,year),
                                    "%s_pdfmass_%s" % (name,year),
                                    qOS,qSS,mass,time,
                                    p0_11,p1_11,p2_11,
                                    p0_10,p1_10,p2_10,
                                    p0_01,p1_01,p2_01,
                                    p0_00,p1_00,p2_00))
    
  #pdf = WS( ws, RooExponentialNew2("%s_pdfmass_%s" % (name,year),
  #                                  "%s_pdfmass_%s" % (name,year),
  #                                  qOS,qSS,mass,time,
  #                                  p0_11,p1,p2,
  #                                  p0_10,p1,p2,
  #                                  p0_01,p1,p2,
  #                                  p0_00,p1,p2))

  from ROOT import RooArgSet
  params = pdf.getParameters(RooArgSet(mass,time,qOS,qSS))
  finalState = name.split('_')[1]
  nParamsFile = inputs['mass']['bkg']['file'].format(fState   = finalState,
                                                     bdtName = selConf['bdt']['name'],
                                                     bdtCut  = selConf['bdt']['cut'],
                                                     year    = year,
                                                     magnet  = selConf['magnet'])
  params.readFromFile(nParamsFile)
  #params.selectByName('*_p0_*').setAttribAll('Constant',False)
  params.Print("v")

def createMassPhysBkg(name = "physKPI", year = '', config = {}, ws = None):

  from ROOT import RooRealVar, RooArgusBG

  mass = ws.obj('mass')
  conf = config[name]['mass'][year]
  m0 = 0
  cA = 0
  for varName,varVals in conf.iteritems():

    if varName == 'resModel' : continue

    tmp = 0
    if type(varVals) == str:
      tmp = ws.obj("%s" %(varVals))
    else:
      tmp = WS( ws, RooRealVar("%s_mass_%s_%s" %(name,varName,year),
                               "%s_mass_%s_%s" %(name,varName,year),
                               varVals[0],varVals[1],varVals[2]))
      tmp.setConstant(varVals[3])

    if varName == 'm0' : m0 = tmp
    if varName == 'cA' : cA = tmp

  pdf = WS( ws, RooArgusBG("%s_pdfmassTMP_%s" % (name,year),
                           "%s_pdfmassTMP_%s" % (name,year),
                           mass,m0,cA))

  resModel = ws.obj('%s' % (conf['resModel']))
  from ROOT import RooFFTConvPdf
  pdf = WS( ws, RooFFTConvPdf("%s_pdfmass_%s" % (name,year),
                              "%s_pdfmass_%s" % (name,year),
                              mass,pdf,resModel))
  pdf.setBufferFraction(0.5)
  pdf.setBufferStrategy(RooFFTConvPdf.Flat);


def createMassCrossFeed(name = "bdkpi_pipi", year = '',config = {}, selOpts = {}, ws = None):

  #from ROOT import *
  from ROOT import TFile, TObject, RooFit, RooWorkspace, RooFFTConvPdf, RooKeysPdf

  conf       = config[name]['mass'][year]
  decay      = name.split('_')[0]
  finalState = name.split('_')[1]
  mass       = ws.obj('mass')
  resModel   = ws.obj('%s' % (conf['resModel']))
  fileName   = inputs['mass']['cross']['file'].format(fState=finalState,
                                                      bdtName=selOpts['bdt']['name'],
                                                      bdtCut=selOpts['bdt']['cut'],
                                                      pid=selOpts['bdt']['pid'][finalState],
                                                      magnet=selOpts['magnet'],
                                                      year=year)
  
  wsName = '%s_%s_%s_%s' % (finalState,selOpts['bdt']['name'],
                            selOpts['bdt']['cut'],selOpts[name]['pid'])
  tempName = '%s_%s' %(decay,finalState)

  
  tempFile = TFile(fileName,"READ")
  print('massutils: createMassCrossFeed: input file: %s'%(tempFile.GetName()))
  myWS = tempFile.Get(wsName)
  print('massutils: createMassCrossFeed: work space: %s'%(myWS.GetName()))
  pdftmp = myWS.pdf(tempName)
  print('massutils: createMassCrossFeed:   pdf name: %s'%(pdftmp.GetName()))
  
  pdf = WS( ws, RooFFTConvPdf('%s_pdfmass_%s' % (name,year),
                              '%s_pdfmass_%s' % (name,year),
                              mass,pdftmp,resModel) )
  pdf.setBufferFraction(0.5)
  pdf.setBufferStrategy(RooFFTConvPdf.Flat)

  del myWS, pdftmp
  tempFile.Close()
  del tempFile





