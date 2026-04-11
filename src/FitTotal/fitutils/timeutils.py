from B2DXFitters.WS import WS
from inpututils import inputs
def createSignalTimePdf(name = 'bdkpi', year = '', config = {}, ws = None) :
  print("timeutils: createSignalTimePdf: starts")
  
  from ROOT import RooRealConstant, RooRealVar, RooBDecaySpecial, RooBDecayNew, RooBDecay, RooProdPdf, RooFit, RooArgSet, RooFormulaVar, RooArgList, RooEffProd, RooProduct 
  conf = config[name]['time'][year]

  G = 0
  tau = 0
  dM = 0
  dG = 0

  for varName,varVals in conf.iteritems():
    tmp = 0
    if type(varVals) == str:
      tmp = ws.obj("%s" %(varVals))
      tau = ws.obj('%s'%(varVals.replace('G','tau')))

    else:
      tmp = WS( ws, RooRealVar("%s_%s_%s" % (name,varName,year),
                               "%s_%s_%s" % (name,varName,year),
                               varVals[0],varVals[1],varVals[2]))
      tmp.setConstant(varVals[3])

    if varName == 'G': 
      G = tmp
      tau = WS(ws, RooFormulaVar('%s_tau_%s'%(name,year),'%s_tau_%s'%(name,year),'1./@0',RooArgList(G)))
    if varName == 'dM' : dM = tmp
    if varName == 'dG' : dG = tmp

  time = ws.obj("time")
  fcoshT = ws.obj("%s_fcoshT_%s" % (name,year))
  fsinhT = ws.obj("%s_fsinhT_%s" % (name,year))
  fcosT  = ws.obj("%s_fcosT_%s"  % (name,year))
  fsinT  = ws.obj("%s_fsinT_%s"  % (name,year))

  fcoshU = ws.obj("%s_fcoshU_%s" % (name,year))
  fsinhU = ws.obj("%s_fsinhU_%s" % (name,year))
  fcosU  = ws.obj("%s_fcosU_%s"  % (name,year))
  fsinU  = ws.obj("%s_fsinU_%s"  % (name,year))

  fcoshGen = ws.obj("%s_fcoshGen_%s" % (name,year))
  fsinhGen = ws.obj("%s_fsinhGen_%s" % (name,year))
  fcosGen  = ws.obj("%s_fcosGen_%s"  % (name,year))
  fsinGen  = ws.obj("%s_fsinGen_%s"  % (name,year))

  resTAccT = ws.obj("%s_resTAccT_%s" % (name,year))
  resTAccU = ws.obj("%s_resTAccU_%s" % (name,year))

  resT = ws.obj('%s_resT_%s' % (name,year))

  timepdfT = WS( ws, RooBDecaySpecial("%s_pdftimeT_%s" % (name,year),
                               "%s_pdftimeT_%s" % (name,year),
                               time,tau,dG,
                               fcoshT,fsinhT,fcosT,fsinT,dM,
                               resTAccT,RooBDecaySpecial.SingleSided)) 
  timepdfU = WS( ws, RooBDecaySpecial("%s_pdftimeU_%s" % (name,year),
                               "%s_pdftimeU_%s" % (name,year),
                               time,tau,dG,
                               fcoshU,fsinhU,fcosU,fsinU,dM,
                               resTAccU,RooBDecaySpecial.SingleSided)) 
  #qSS = ws.obj('qSS')
  timepdf = WS(ws, RooBDecayNew("%s_pdftime_%s" % (name,year),
                                "%s_pdftime_%s" % (name,year),
                                timepdfT,timepdfU))

  if config['generate']['flag']:

    accT = ws.obj('%s_accTimeNormT_%s'%(name,year))
    accU = ws.obj('%s_accTimeNormU_%s'%(name,year))
    timepdfTNoAcc = WS( ws, RooBDecay("%s_pdftimeNoAccT_%s" % (name,year),
                                      "%s_pdftimeNoAccT_%s" % (name,year),
                                      time,tau,dG,
                                      fcoshGen,fsinhGen,fcosGen,fsinGen,dM,
                                      resT,RooBDecay.SingleSided))
    timepdfUNoAcc = WS( ws, RooBDecay("%s_pdftimeNoAccU_%s" % (name,year),
                                      "%s_pdftimeNoAccU_%s" % (name,year),
                                      time,tau,dG,
                                      fcoshGen,fsinhGen,fcosGen,fsinGen,dM,
                                      resT,RooBDecay.SingleSided))
    timepdfT = WS( ws, RooEffProd('%s_pdftimeGenT_%s' % (name,year),
                                  '%s_pdftimeGenT_%s' % (name,year),
                                  timepdfTNoAcc,accT))
    timepdfU = WS( ws, RooEffProd('%s_pdftimeGenU_%s' % (name,year),
                                  '%s_pdftimeGenU_%s' % (name,year),
                                  timepdfUNoAcc,accU))

  obs = [ key for key in config['observables'].keys() if key != 'timeErr' and key != 'mass' and key != 'fState' ]
  listObs = RooArgSet()
  for ob in obs:
    obsVar = ws.obj(ob)
    listObs.add(obsVar)

  if 'timeErr' in config['observables'].keys():
    timeErrPdf = ws.obj("%s_timeErr_HistPdf_%s" % (name,year))
    if 'mean2' in config[name]['timeErr'].keys():
      timeErrPdf = ws.obj('%s_pdftimeErr_%s' % (name,year))
      print 'USING PDF NOT FROM TEMPLATE %s**************************************************'%(name)
    timepdf = ws.obj('%s_pdftime_%s'%(name,year))
    print 'USING PDF NAMED %s ***********************************'%(timeErrPdf.GetName())
    tmp = WS( ws, RooProdPdf("%s_pdftimeWE_%s" % (name,year),
                             "%s_pdftimeWE_%s" % (name,year),
                             RooArgSet(timeErrPdf),
                             RooFit.Conditional(RooArgSet(timepdf),listObs)))

    if config['generate']['flag']:
      timePdf = ws.obj("%s_pdftimeGen_%s" % (name,year))
      tmp = WS( ws, RooProdPdf("%s_pdftimeGenWE_%s" % (name,year),
                               "%s_pdftimeGenWE_%s" % (name,year),
                               RooArgSet(timeErrPdf),
                               RooFit.Conditional(RooArgSet(timePdf),listObs)))
  print("timeutils: createSignalTimePdf: ends")
  

def createBkgTimePdf(name = 'bkg_kpi', year = '', config = {}, selConf = {}, sstagName = "SS", ws = None) :
  print("timeutils: createBkgTimePdf: starts")
  from ROOT import ( RooRealConstant, RooRealVar, RooExponential, RooProdPdf,
                     RooFit, RooArgSet, RooFormulaVar, RooArgList, RooTimeAccPdf, RooTimePdfBkgNew, RooTimePdfBkgNew2, RooUniform, RooArgSet)
  confTime = config[name]['time'][year]
  confAcc = config[name]['acc'][year]

  if 'template' in confTime.keys():

    from ROOT import TFile, RooWorkspace, RooKeysPdf, RooKeysPdfSpecial
    finalState = name.split('_')[1]
    templateFileName = inputs['time']['bkg']['file'].format(fState  = finalState,
                                                            bdtName = selConf['bdt']['name'],
                                                            bdtCut  = selConf['bdt']['cut'],
                                                            year    = year,
                                                            magnet  = selConf['magnet'])
    templateFile = TFile(templateFileName,'READ')
    templateFile.Print("v")
    myWS = templateFile.Get('templates')
    time = ws.obj("time")
    pdfTot = WS(ws, myWS.pdf('%s_pdftimeU_%s' % (name,year)))
    pdf1OS = WS(ws, myWS.pdf('%s_pdftime1OS_%s' % (name,year)))
    pdf0OS = WS(ws, myWS.pdf('%s_pdftime0OS_%s' % (name,year)))
    pdf11 = WS(ws, myWS.pdf('%s_pdftime11_%s' % (name,year)))
    pdf10 = WS(ws, myWS.pdf('%s_pdftime10_%s' % (name,year)))
    pdf01 = WS(ws, myWS.pdf('%s_pdftime01_%s' % (name,year)))
    pdf00 = WS(ws, myWS.pdf('%s_pdftime00_%s' % (name,year)))

    del myWS
    templateFile.Close()
    qOS = ws.obj('qOS')
    qSS = None
    if sstagName != None:
      qSS = ws.obj('q%s'%sstagName)
    else:
      qSS = ws.obj('qDummy')
      pdf11 = pdfTot
      pdf10 = pdfTot
      pdf01 = pdfTot
      pdf00 = pdfTot
      
    pdf = WS(ws, RooTimePdfBkgNew2('%s_pdftime_%s'%(name,year),
                                   '%s_pdftime_%s'%(name,year),
                                   qOS,qSS,pdf11,pdf10,pdf01,pdf00))
    print "CONFIGURING BKG WITH TEMPLATES@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
  else:

    c11 = 0
    c10 = 0
    c01 = 0
    c00 = 0
    tau1_11 = 0
    tau1_10 = 0
    tau1_01 = 0
    tau1_00 = 0
    tau2_11 = 0
    tau2_10 = 0
    tau2_01 = 0
    tau2_00 = 0
    frac11 = 0
    frac10 = 0
    frac01 = 0
    frac00 = 0

    for varName,varVals in confTime.iteritems():

      tmp = 0
      if type(varVals) == str:
        tmp = ws.obj("%s" %(varVals))

      else:

        tmp = WS( ws, RooRealVar("%s_%s_%s" % (name,varName,year),
                                 "%s_%s_%s" % (name,varName,year),
                                 varVals[0],varVals[1],varVals[2]))
        tmp.setConstant(varVals[3])
  
      if varName == 'tau1_11' : tau1_11 = tmp
      if varName == 'tau1_10' : tau1_10 = tmp
      if varName == 'tau1_01' : tau1_01 = tmp
      if varName == 'tau1_00' : tau1_00 = tmp
      if varName == 'tau2_11' : tau2_11 = tmp
      if varName == 'tau2_10' : tau2_10 = tmp
      if varName == 'tau2_01' : tau2_01 = tmp
      if varName == 'tau2_00' : tau2_00 = tmp
      if varName == 'frac11'  : frac11  = tmp
      if varName == 'frac10'  : frac10  = tmp
      if varName == 'frac01'  : frac01  = tmp
      if varName == 'frac00'  : frac00  = tmp

    for varName,varVals in confAcc.iteritems():

      tmp = 0
      if type(varVals) == str:
        tmp = ws.obj("%s" %(varVals))

      else:

        tmp = WS( ws, RooRealVar("%s_%s_%s" % (name,varName,year),
                                 "%s_%s_%s" % (name,varName,year),
                                 varVals[0],varVals[1],varVals[2]))
        tmp.setConstant(varVals[3])
  
      if varName == 'c11'     : c11     = tmp
      if varName == 'c10'     : c10     = tmp
      if varName == 'c01'     : c01     = tmp
      if varName == 'c00'     : c00     = tmp

    time = ws.obj("time")
    qOS = ws.obj('qOS')
    qSS = None
    if sstagName != None:
      qSS = ws.obj('q%s'%sstagName)
    else:
      qSS = ws.obj('qDummy')
    pdf = WS(ws, RooTimePdfBkgNew("%s_pdftime_%s" % (name,year),
                                  "%s_pdftime_%s" % (name,year),
                                  qOS,qSS,time,
                                  c11,frac11,tau1_11,tau2_11,
                                  c10,frac10,tau1_10,tau2_10,
                                  c01,frac01,tau1_01,tau2_01,
                                  c00,frac00,tau1_00,tau2_00))
  print("timeutils: createBkgTimePdf: ends")
  
"""
  else:

    tau1T = 0
    tau2T = 0
    frac1T = 0
    tau1U = 0
    tau2U = 0
    frac1U = 0

    for varName,varVals in conf.iteritems():

      tmp = 0
      if type(varVals) == str:
        tmp = ws.obj("%s" %(varVals))

      else:

        tmp = WS( ws, RooRealVar("%s_%s_%s" % (name,varName,year),
                                 "%s_%s_%s" % (name,varName,year),
                                 varVals[0],varVals[1],varVals[2]))
        tmp.setConstant(varVals[3])
  
      if varName == 'tau1T'  : tau1T  = tmp
      if varName == 'tau2T'  : tau2T  = tmp
      if varName == 'frac1T' : frac1T = tmp
      if varName == 'tau1U'  : tau1U  = tmp
      if varName == 'tau2U'  : tau2U  = tmp
      if varName == 'frac1U' : frac1U = tmp

    time = ws.obj("time")

    pdfT1 = WS( ws, RooExponential("%s_timepdfT1_%s" % (name,year),
                                  "%s_timepdfT1_%s" % (name,year),
                                  time,tau1T))
    pdfT2 = WS( ws, RooExponential("%s_timepdfT2_%s" % (name,year),
                                  "%s_timepdfT2_%s" % (name,year),
                                  time,tau2T))
    pdfU1 = WS( ws, RooExponential("%s_timepdfU1_%s" % (name,year),
                                  "%s_timepdfU1_%s" % (name,year),
                                  time,tau1U))
    pdfU2 = WS( ws, RooExponential("%s_timepdfU2_%s" % (name,year),
                                  "%s_timepdfU2_%s" % (name,year),
                                  time,tau2U))

    from ROOT import RooAddPdf
    pdfT  = WS( ws, RooAddPdf("%s_pdftimeNoAccT_%s" % (name,year),
                              "%s_pdftimeNoAccT_%s" % (name,year),
                              RooArgList(pdfT1,pdfT2),RooArgList(frac1T)))
    pdfU  = WS( ws, RooAddPdf("%s_pdftimeNoAccU_%s" % (name,year),
                              "%s_pdftimeNoAccU_%s" % (name,year),
                              RooArgList(pdfU1,pdfU2),RooArgList(frac1U)))

    accT  = ws.obj("%s_accTime_Tag_%s" % (name,year))
    accU  = ws.obj("%s_accTime_Untag_%s" % (name,year))

    from ROOT import RooEffProd
    pdfAccT = WS( ws, RooEffProd("%s_pdftimeT_%s" % (name,year),
                                "%s_pdftimeT_%s" % (name,year),
                                pdfT,accT) )
    pdfAccU = WS( ws, RooEffProd("%s_pdftimeU_%s" % (name,year),
                                "%s_pdftimeU_%s" % (name,year),
                                pdfU,accU) )
    q = ws.obj('qSS')
    pdf = WS(ws, RooTimePdfBkg("%s_pdftime_%s" % (name,year),
                               "%s_pdftime_%s" % (name,year),
                               q,time,pdfAccT,pdfAccU))
"""

def createPhysTimePdf(name = 'bkg_kpi', year = '', config = {}, selConf = {}, sstagName = "SS", ws = None) :
  print("timeutils: createPhysTimePdf: starts")
  from ROOT import ( RooRealConstant, RooRealVar, RooExponential, RooProdPdf,
                     RooFit, RooArgSet, RooFormulaVar, RooArgList, RooTimeAccPdf, RooTimePdfPhysNew,
                     RooTimePdfPhysNew2 )
  confTime = config[name]['time'][year]
  confAcc = config[name]['acc'][year]

  if 'template' in confTime.keys():

    from ROOT import TFile, RooWorkspace, RooKeysPdf, RooKeysPdfSpecial

    finalState = name.split('_')[1]
    finalState = ''.join([i for i in finalState if not i.isdigit()]) 
    templateFile = None
    templateFileName = inputs['time']['phys']['file'].format(fState  = finalState,
                                                             bdtName = selConf['bdt']['name'],
                                                             bdtCut  = selConf['bdt']['cut'],
                                                             year    = year,
                                                             magnet  = selConf['magnet'])
    templateFile = TFile(templateFileName,'READ')
    templateFile.Print("v")
    myWS = templateFile.Get('templates')
    myWS.Print("v")
    pdfTot = WS(ws, myWS.pdf('%s_pdftimeTU_%s' % (name.replace('kpi1', 'kpi').replace('kpi2', 'kpi'),year)))
    pdfT = WS(ws, myWS.pdf('%s_pdftimeT_%s' % (name,year)))
    pdfU = WS(ws, myWS.pdf('%s_pdftimeU_%s' % (name,year)))

    del myWS
    templateFile.Close()
    qSS = None
    if sstagName != None:
      qSS = ws.obj('q%s'%sstagName)
    else:
      qSS = ws.obj('qDummy')
      pdfT = pdfTot
      pdfU = pdfTot
    pdf = WS(ws, RooTimePdfPhysNew2('%s_pdftime_%s'%(name,year),
                                    '%s_pdftime_%s'%(name,year),
                                    qSS,pdfT,pdfU))
    print "CONFIGURING PHYS BKG WITH TEMPLATES@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
  else:

    a0 = 0
    b0 = 0
    c0 = 0
    a1 = 0
    b1 = 0
    c1 = 0
    G  = 0

    for varName,varVals in confTime.iteritems():

      tmp = 0
      if type(varVals) == str:
        tmp = ws.obj("%s" %(varVals))

      else:

        tmp = WS( ws, RooRealVar("%s_%s_%s" % (name,varName,year),
                                 "%s_%s_%s" % (name,varName,year),
                                 varVals[0],varVals[1],varVals[2]))
        tmp.setConstant(varVals[3])
  
      if varName == 'G' : G = tmp

    for varName,varVals in confAcc.iteritems():

      tmp = 0
      if type(varVals) == str:
        tmp = ws.obj("%s" %(varVals))

      else:

        tmp = WS( ws, RooRealVar("%s_%s_%s" % (name,varName,year),
                                 "%s_%s_%s" % (name,varName,year),
                                 varVals[0],varVals[1],varVals[2]))
        tmp.setConstant(varVals[3])
  
      if varName == 'a0' : a0 = tmp
      if varName == 'b0' : b0 = tmp
      if varName == 'c0' : c0 = tmp
      if varName == 'a1' : a1 = tmp
      if varName == 'b1' : b1 = tmp
      if varName == 'c1' : c1 = tmp


    time = ws.obj("time")
    qOS = ws.obj('qOS')
    qSS = None
    if sstagName!=None:
      qSS = ws.obj('q%s'%sstagName)
    else:
      qSS = ws.obj('qDummy')
    pdf = WS(ws, RooTimePdfPhysNew("%s_pdftime_%s" % (name,year),
                                  "%s_pdftime_%s" % (name,year),
                                  qSS,time,
                                  c0,b0,a0,c1,b1,a1,G))
  
  print("timeutils: createPhysTimePdf: ends")
  
"""
def createPhysTimePdf(name = 'phys_kpi1', year = '', config = {}, ws = None) :

  from ROOT import ( RooRealConstant, RooRealVar, RooExponential, RooProdPdf,
                     RooFit, RooArgSet, RooFormulaVar, RooArgList, RooTimeAccPdf )
  conf = config[name]['time'][year]

  tau1 = 0
  tau2 = 0
  frac1 = 0

  for varName,varVals in conf.iteritems():

    tmp = 0
    if type(varVals) == str:
      tmp = ws.obj("%s" %(varVals))

    else:

      tmp = WS( ws, RooRealVar("%s_%s_%s" % (name,varName,year),
                               "%s_%s_%s" % (name,varName,year),
                               varVals[0],varVals[1],varVals[2]))
      tmp.setConstant(varVals[3])

    if varName == 'tau1' : tau1 = tmp
    if varName == 'tau2' : tau2 = tmp
    if varName == 'frac1' : frac1 = tmp

  time = ws.obj("time")

  pdf1 = WS( ws, RooExponential("%s_timepdf1_%s" % (name,year),
                                "%s_timepdf1_%s" % (name,year),
                                time,tau1))
  pdf2 = WS( ws, RooExponential("%s_timepdf2_%s" % (name,year),
                                "%s_timepdf2_%s" % (name,year),
                                time,tau2))

  from ROOT import RooAddPdf
  pdf  = WS( ws, RooAddPdf("%s_pdftimeNoAcc_%s" % (name,year),
                           "%s_pdftimeNoAcc_%s" % (name,year),
                           RooArgList(pdf1,pdf2),RooArgList(frac1)))

  acc  = ws.obj("%s_accTime_%s" % (name,year))
  from ROOT import RooEffProd
  pdfAcc = WS( ws, RooEffProd("%s_pdftime_%s" % (name,year),
                              "%s_pdftime_%s" % (name,year),
                              pdf,acc) )
 
"""
