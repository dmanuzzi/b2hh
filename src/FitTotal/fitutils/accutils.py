from B2DXFitters.WS import WS
from ROOT import RooCubicSplineFun, RooBinnedFun
from inpututils import inputs

def createSignalAcceptance(name = 'bdkpi', year = '', config = {}, selConf = 'bdpipi_-3.5.-3.5', outDir = '', ws = None) :
  print('accutils: createSignalAcceptance: starts')
  print('accutils: createSignalAcceptance: channel: %s'%name)
  print('accutils: createSignalAcceptance:    year: %s'%year)
  print('accutils: createSignalAcceptance: selConf: %s'%selConf)
  
  from copy import deepcopy
  #from ROOT import RooBinning, RooRealVar, RooArgList, RooCubicSplineFun, RooConstVar, RooPolyVar, RooProduct, RooFormulaVar, TH1, TFile, RooBinnedFun
  from ROOT import RooBinning, RooRealVar, RooArgList, RooConstVar, RooPolyVar, RooProduct, RooFormulaVar, TH1, TFile

  conf = config[name]['acc'][year]
  
  if type(conf) == str:
    accT = ws.obj('%s_accTimeT_%s' % (conf,year))
    accT = WS(ws, accT.clone('%s_accTimeT_%s' % (name,year)))
    accU = ws.obj('%s_accTimeU_%s' % (conf,year))
    accU = WS(ws, accU.clone('%s_accTimeU_%s' % (name,year)))

    if config['generate']['flag']:
      accNormT = ws.obj('%s_accTimeNormT_%s' % (conf,year))
      accNormT = WS(ws, accNormT.clone('%s_accTimeNormT_%s' % (name,year)))
      accNormU = ws.obj('%s_accTimeNormU_%s' % (conf,year))
      accNormU = WS(ws, accNormU.clone('%s_accTimeNormU_%s' % (name,year)))

  elif type(conf) == list:
    smooth = conf[0]
    constCoeffs = conf[1]
    inFile = None
    histo = None
    histo1 = None
    histo2 = None
    inFileName = inputs['acceptance']['file'].format(bdtName = selConf.split('_')[0],
                                                     bdtCut  = selConf.split('_')[1],
                                                     year    = year,
                                                     #year    = '201516',
                                                     magnet  = 'Tot')
    inFile = TFile(inFileName)
    print('accutils: createSingnalAcceptance:  input file: %s'%(inFile.GetName()))
    
    from ROOT import TGraphErrors
    histo1 = inFile.Get('acc_%s_NewT'%name)
    histo2 = inFile.Get('acc_%s_NewU'%name)
    print("accutils: createSingnalAcceptance: histo1 name: %s"%(histo1.GetName()))
    print("accutils: createSingnalAcceptance: histo2 name: %s"%(histo2.GetName()))
    
    #if name == 'bdkpi':
    #nodes = [0.2,0.27,0.35,0.45,0.6,0.75,0.9,1,1.25,1.75,3,5]
    #histo2 = TGraphErrors(len(nodes))
    #histo1 = TGraphErrors(len(nodes))
    #for i in range(len(nodes)):
    #  histo2.SetPoint(i,nodes[i],1);
    #  histo2.SetPointError(i,0,0);
    #  histo1.SetPoint(i,nodes[i],1);
    #  histo1.SetPointError(i,0,0);

    if smooth > 0:
      print("accutils: createSingnalAcceptance: BUILDING ACCEPTANCE WITH SPLINES")
      accT = WS(ws, RooCubicSplineFun('%s_accTimeT_%s'%(name,year),'%s_accTimeT_%s'%(name,year),
                             ws.obj('time'),histo1,constCoeffs))
      accU = WS(ws, RooCubicSplineFun('%s_accTimeU_%s'%(name,year),'%s_accTimeU_%s'%(name,year),
                             ws.obj('time'),histo2,constCoeffs))

      lastCoeffT = accT.coefficients().at(accT.coefficients().getSize()-1).getVal()
      lastCoeffU = accU.coefficients().at(accU.coefficients().getSize()-1).getVal()
      for i in xrange(0,accT.coefficients().getSize()):
        accT.coefficients().at(i).setVal(accT.coefficients().at(i).getVal()/lastCoeffT)
        accU.coefficients().at(i).setVal(accU.coefficients().at(i).getVal()/lastCoeffU)
      #acc2 = WS(ws, acc1.clone('%s_accTime2_%s'%(name,year)))
      
      if config['generate']['flag']:
        mT = max([accT.coefficients().at(j).getVal() for j in
            xrange(0, accT.coefficients().getSize())])
        cT = WS(ws, RooConstVar('%s_kCoeffNormT_%s' % (name,year),
                               '%s_kCoeffNormT_%s' % (name,year), 0.99 / mT))
        mU = max([accU.coefficients().at(j).getVal() for j in
            xrange(0, accU.coefficients().getSize())])
        cU = WS(ws, RooConstVar('%s_kCoeffNormU_%s' % (name,year),
                               '%s_kCoeffNormU_%s' % (name,year), 0.99 / mU))

        accNormT = WS(ws, RooProduct('%s_accTimeNormT_%s' % (name,year),
                                    '%s_accTimeNormT_%s' % (name,year),
                                    RooArgList(accT, cT)))
        accNormU = WS(ws, RooProduct('%s_accTimeNormU_%s' % (name,year),
                                    '%s_accTimeNormU_%s' % (name,year),
                                    RooArgList(accU, cU)))

    else:
      print("accutils: createSingnalAcceptance: BUILDING ACCEPTANCE WITH HISTOGRAMS")
      WS(ws, RooBinnedFun('%s_accTime_%s'%(name,year),'%s_accTime_%s'%(name,year),
                            ws.obj('time'),histo,constCoeffs))


  else:
    #print name

    if 'kRatios' in conf.keys():

      nodes = deepcopy(conf['kNodes'])
      nameOther = conf['kCoeffs']
      ratios = deepcopy(conf['kRatios'])
      time = ws.obj('time')
      accBinning = ws.obj( '%s_accKnotBinning_%s' % (nameOther,year) )
      oldBinning = time.getBinning()

      kCoeffList = RooArgList()
      i = 0
      for rat in ratios:
        r = WS( ws, RooRealVar('%s_kRatio_%s_%d'%(name,year,i),'%s_kRatio_%s_%d'%(name,year,i),rat,0,3))
        c = ws.obj('%s_kCoeff_%s_%d'%(nameOther,year,i))
        cprime = WS( ws, RooFormulaVar("%s_kCoeff_%s_%d"%(name,year,i),"%s_kCoeff_%s_%d"%(name,year,i),
                                       '@0*@1',RooArgList(r,c)))
        kCoeffList.add(cprime)
        i = i+1
      c = RooConstVar("%s_kCoeff_%s_%d"%(name,year,i),"%s_kCoeff_%s_%d"%(name,year,i),1)
      kCoeffList.add(c)
      i = i+1
      nodes.append(time.getMax())
      nodes.reverse()
      slope = (nodes[0] - nodes[1]) / (nodes[2] - nodes[1])
      kCoeffListLast = RooArgList(
                WS(ws, RooConstVar("%s_kCoeff_%s_%d_c0"%(name,year,i),
                                   "%s_kCoeff_%s_%d_c0"%(name,year,i), 1.-slope)),
                WS(ws, RooConstVar("%s_kCoeff_%s_%d_c1"%(name,year,i),
                                   "%s_kCoeff_%s_%d_c1"%(name,year,i), slope)))

      kCoeffList.add( WS ( ws, RooPolyVar("%s_kCoeff_%s_%d"%(name,year,i),"%s_kCoeff_%s_%d"%(name,year,i),
                                          kCoeffList.at(kCoeffList.getSize() - 2), kCoeffListLast)))

      acc = WS(ws, RooCubicSplineFun('%s_accTime_%s' % (name,year),
                                     '%s_accTime_%s' % (name,year),
                                     time, '%s_accKnotBinning_%s' % (nameOther,year),
                                     kCoeffList))

      if config['generate']['flag']:
        m = max([kCoeffList.at(j).getVal() for j in
            xrange(0, kCoeffList.getSize())])
        c = WS(ws, RooConstVar('%s_kCoeffNorm_%s' % (name,year),
                               '%s_kCoeffNorm_%s' % (name,year), 0.99 / m))
        accNorm = WS(ws, RooProduct('%s_accTimeNorm_%s' % (name,year),
                                    '%s_accTimeNorm_%s' % (name,year),
                                    RooArgList(acc, c)))

    else:

      nodes = deepcopy(conf['kNodes'])
      coeffs = deepcopy(conf['kCoeffs'])
      time = ws.obj('time')
      accBinning = WS(ws, RooBinning(time.getMin(),time.getMax(),"%s_accKnotBinning_%s" % (name,year)))
      for node in nodes:
        accBinning.addBoundary(node)
      accBinning.removeBoundary(time.getMin())
      accBinning.removeBoundary(time.getMax())
      accBinning.removeBoundary(time.getMin())
      accBinning.removeBoundary(time.getMax())

      oldBinning = time.getBinning()
      time.setBinning(accBinning,"%s_accKnotBinning_%s" % (name,year))
      time.setBinning(oldBinning)
      time.setRange(time.getMin(),time.getMax())

      kCoeffList = RooArgList()
      i = 0
      for coef in coeffs:
        c = WS( ws, RooRealVar("%s_kCoeff_%s_%d"%(name,year,i),"%s_kCoeff_%s_%d"%(name,year,i),coef,0,3))
        #c.setConstant(True)
        kCoeffList.add(c)
        i = i+1
      c = RooConstVar("%s_kCoeff_%s_%d"%(name,year,i),"%s_kCoeff_%s_%d"%(name,year,i),1)
      kCoeffList.add(c)
      i = i+1
      nodes.append(time.getMax())
      nodes.reverse()
      slope = (nodes[0] - nodes[1]) / (nodes[2] - nodes[1])
      kCoeffListLast = RooArgList(
                WS(ws, RooConstVar("%s_kCoeff_%s_%d_c0"%(name,year,i),
                                   "%s_kCoeff_%s_%d_c0"%(name,year,i), 1.-slope)),
                WS(ws, RooConstVar("%s_kCoeff_%s_%d_c1"%(name,year,i),
                                   "%s_kCoeff_%s_%d_c1"%(name,year,i), slope)))

      kCoeffList.add( WS ( ws, RooPolyVar("%s_kCoeff_%s_%d"%(name,year,i),"%s_kCoeff_%s_%d"%(name,year,i),
                                          kCoeffList.at(kCoeffList.getSize() - 2), kCoeffListLast)))

      acc = WS(ws, RooCubicSplineFun('%s_accTime_%s' % (name,year),
                                     '%s_accTime_%s' % (name,year),
                                     time, '%s_accKnotBinning_%s' % (name,year),
                                     kCoeffList))

      if config['generate']['flag']:
        m = max([kCoeffList.at(j).getVal() for j in
            xrange(0, kCoeffList.getSize())])
        c = WS(ws, RooConstVar('%s_kCoeffNorm_%s' % (name,year),
                               '%s_kCoeffNorm_%s' % (name,year), 0.1 / m))
        accNorm = WS(ws, RooProduct('%s_accTimeNorm_%s' % (name,year),
                                    '%s_accTimeNorm_%s' % (name,year),
                                    RooArgList(acc, c)))
  print('accutils: createSignalAcceptance: ends')
  


def createBkgAcceptance(name = 'bkg_kpi', year = '', config = {}, ws = None) :

  from ROOT import RooRealVar, RooTimeAccPdf

  conf = config[name]['acc'][year]

  c1 = 0
  c2 = 0

  for varName,varVals in conf.iteritems():

    tmp = 0
    if type(varVals) == str:
      tmp = ws.obj("%s" % (varVals))

    else:

      tmp = WS( ws, RooRealVar("%s_%s_%s" % (name,varName,year),
                               "%s_%s_%s" % (name,varName,year),
                               varVals[0],varVals[1],varVals[2]))
      tmp.setConstant(varVals[3])

    if varName == 'c1' : c1 = tmp
    if varName == 'c2' : c2 = tmp

  time = ws.obj('time')

  accT = WS( ws, RooTimeAccPdf("%s_accTime_Tag_%s" % (name,year),
                               "%s_accTime_Tag_%s" % (name,year),
                               time,c1))
  accU = WS( ws, RooTimeAccPdf("%s_accTime_Untag_%s" % (name,year),
                               "%s_accTime_Untag_%s" % (name,year),
                               time,c2))

def createPhysAcceptance(name = 'phys_kpi1', year = '', config = {}, ws = None) :

  from copy import deepcopy
  from ROOT import RooBinning, RooRealVar, RooArgList, RooConstVar, RooPolyVar, RooProduct, RooFormulaVar, TH1, TFile, RooTimeAccPhysPdf

  conf = config[name]['acc'][year]
  c1 = 0
  c2 = 0
  c3 = 0

  if type(conf) == str:
    acc = ws.obj('%s_accTime_%s' % (conf,year))
    acc = WS(ws, acc.clone('%s_accTime_%s' % (name,year)))

  else:
    for varName,varVals in conf.iteritems():

      tmp = 0
      if type(varVals) == str:
        tmp = ws.obj("%s" % (varVals))

      else:

        tmp = WS( ws, RooRealVar("%s_%s_%s" % (name,varName,year),
                                 "%s_%s_%s" % (name,varName,year),
                                 varVals[0],varVals[1],varVals[2]))
        tmp.setConstant(varVals[3])

      if varName == 'c1' : c1 = tmp
      if varName == 'c2' : c2 = tmp
      if varName == 'c3' : c3 = tmp

    time = ws.obj('time')

    acc = WS( ws, RooTimeAccPhysPdf("%s_accTime_%s" % (name,year),
                                    "%s_accTime_%s" % (name,year),
                                    time,c1,c2,c3))
