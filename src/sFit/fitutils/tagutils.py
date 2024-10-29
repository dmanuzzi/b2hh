from B2DXFitters.WS import WS

def createSignalOmegas(name = 'bdkpi', year = '', config = {}, taggerList = [], ws = None) :
  print("tagutils: createSingnalOmegas: starts")
  from ROOT import RooRealVar, RooOmegaFunc, RooOmegaFuncSS, RooSfitOmegaFunc
  conf = config[name]['tag'][year]
  for tagName in taggerList :

    eps = 0
    p0 = 0
    p1 = 0
    epsAsym = 0
    deltap0 = 0
    deltap1 = 0
    etaHat = 0

    varDict = conf[tagName]
    for varName,varVals in varDict.iteritems():

      tmp = 0
      if type(varVals) == str:
        tmp = ws.obj("%s" %(varVals))
  
      else:
        tmp = WS ( ws, RooRealVar("%s_%s%s_%s" % (name,varName,tagName,year),
                                  "%s_%s%s_%s" % (name,varName,tagName,year),
                                  varVals[0],varVals[1],varVals[2]))
        tmp.setConstant(varVals[3])

      if varName == 'eps' : eps = tmp
      if varName == 'p0' : p0 = tmp
      if varName == 'p1' : p1 = tmp
      if varName == 'epsAsym' : epsAsym = tmp
      if varName == 'deltap0' : deltap0 = tmp
      if varName == 'deltap1' : deltap1 = tmp
      if varName == 'etaHat' : etaHat = tmp
     
    q = ws.obj("q%s" % tagName)
    eta = ws.obj("eta%s" % tagName)
    etaHistPdf = ws.obj("%s_%s_HistPdf_%s" % (name,eta.GetName(),year))
    etaAvg = etaHistPdf.dataHist().mean(eta)
    if 'SS' in tagName: 
      time = ws.obj('time')
      OmegaT    = WS( ws, RooOmegaFuncSS("%s_Omega%sT_%s" % (name,tagName,year),
                                         "%s_Omega%sT_%s" % (name,tagName,year),
                                         q,eta,time,
                                         eps,p0,p1,
                                         epsAsym,deltap0,deltap1,
                                         etaHistPdf,etaHat,etaAvg,
                                         RooOmegaFuncSS.B,RooOmegaFuncSS.Tag))
      OmegabarT = WS( ws, RooOmegaFuncSS("%s_Omegabar%sT_%s" % (name,tagName,year),
                                         "%s_Omegabar%sT_%s" % (name,tagName,year),
                                         q,eta,time,
                                         eps,p0,p1,
                                         epsAsym,deltap0,deltap1,
                                         etaHistPdf,etaHat,etaAvg,
                                         RooOmegaFuncSS.Bbar,RooOmegaFuncSS.Tag))
      OmegaU    = WS( ws, RooOmegaFuncSS("%s_Omega%sU_%s" % (name,tagName,year),
                                         "%s_Omega%sU_%s" % (name,tagName,year),
                                         q,eta,time,
                                         eps,p0,p1,
                                         epsAsym,deltap0,deltap1,
                                         etaHistPdf,etaHat,etaAvg,
                                         RooOmegaFuncSS.B,RooOmegaFuncSS.Untag))
      OmegabarU = WS( ws, RooOmegaFuncSS("%s_Omegabar%sU_%s" % (name,tagName,year),
                                         "%s_Omegabar%sU_%s" % (name,tagName,year),
                                         q,eta,time,
                                         eps,p0,p1,
                                         epsAsym,deltap0,deltap1,
                                         etaHistPdf,etaHat,etaAvg,
                                         RooOmegaFuncSS.Bbar,RooOmegaFuncSS.Untag))
      Omega     = WS( ws, RooOmegaFunc("%s_Omega%s_%s" % (name,tagName,year),
                                       "%s_Omega%s_%s" % (name,tagName,year),
                                       q,eta,
                                       eps,p0,p1,
                                       epsAsym,deltap0,deltap1,
                                       etaHistPdf,etaHat,etaAvg,RooOmegaFunc.B))
      Omegabar  = WS( ws, RooOmegaFunc("%s_Omegabar%s_%s" % (name,tagName,year),
                                       "%s_Omegabar%s_%s" % (name,tagName,year),
                                       q,eta,
                                       eps,p0,p1,
                                       epsAsym,deltap0,deltap1,
                                       etaHistPdf,etaHat,etaAvg,RooOmegaFunc.Bbar))

    else:
      Omega = WS( ws, RooOmegaFunc("%s_Omega%s_%s" % (name,tagName,year),
                                   "%s_Omega%s_%s" % (name,tagName,year),
                                   q,eta,
                                   eps,p0,p1,
                                   epsAsym,deltap0,deltap1,
                                   etaHistPdf,etaHat,etaAvg,RooOmegaFunc.B))
      Omegabar = WS( ws, RooOmegaFunc("%s_Omegabar%s_%s" % (name,tagName,year),
                                      "%s_Omegabar%s_%s" % (name,tagName,year),
                                      q,eta,
                                      eps,p0,p1,
                                      epsAsym,deltap0,deltap1,
                                      etaHistPdf,etaHat,etaAvg,RooOmegaFunc.Bbar))
  print("tagutils: createSingnalOmegas: ends")

 
def createSignalSinusoidTerms(name = 'bdkpi', year = '', config = {}, taggerList = [], ws = None, opt=None) :
  print("tagutils: createSingnalSinusoidTerms: starts")
  from ROOT import ( RooFcoshFSFunc, RooFcosFSFunc, 
                     RooFcoshCPFunc, RooFcosCPFunc, RooFsinhCPFunc, RooFsinCPFunc,
                     RooFcoshFStoCPFunc, RooFcosFStoCPFunc,
                     RooFcoshCPtoFSFunc, RooFcosCPtoFSFunc, RooFsinhCPtoFSFunc, RooFsinCPtoFSFunc,
                     RooRealVar, RooConstVar, RooRealConstant, RooFormulaVar, RooArgSet, RooArgList,
                     RooUnblindPrecision )

  
  conf = config[name]['CP'][year]

  AMP = 0
  PHI = 0
  C = 0
  S = 0
  D = 0
  ACP = 0
  Af = 0
  AP = 0
  for varName,varVals in conf.iteritems():

    if varName == 'CPState' : continue
    if (varName == 'D') and ('DfuncCS' in opt): continue
    tmp = 0
    tmp_unblind = 0
    if type(varVals) == str:
      tmp = ws.obj("%s" % (varVals))
      if tmp.GetName() in config['blind'].keys():
        print "BLINDING ENABLED: %s %s"%(tmp.GetName(),config['blind'][tmp.GetName()])
        tmp_unblind = ws.obj("%s_unblind" % (tmp.GetName()))
      else:
        print "BLINDING DISABLED %s"%(tmp.GetName())
        tmp_unblind = tmp
    else:
      tmp = WS( ws, RooRealVar("%s_%s_%s" % (name,varName,year),
                               "%s_%s_%s" % (name,varName,year),
                               varVals[0],varVals[1],varVals[2]))
      tmp.setConstant(varVals[3])
      tmp.Print()
      if tmp.GetName() in config['blind'].keys():
        print "BLINDING ENABLED: %s %s"%(tmp.GetName(),config['blind'][tmp.GetName()])
        tmp_unblind = WS( ws, RooUnblindPrecision('%s_%s_%s_unblind'%(name,varName,year),
                                                  '%s_%s_%s_unblind'%(name,varName,year),
                                                  config['blind'][tmp.GetName()],0.,0.1,
                                                  tmp,ws.obj('unblindState'),False))
        if tmp_unblind.isHidden():
          print "========== IS HIDDEN!"
        else:
          print "---------- EASY, IT IS NOT HIDDEN!"
          
      else:
        print "BLINDING DISABLED %s"%(tmp.GetName())
        tmp_unblind = tmp
    if varName == 'AMP' : AMP = tmp_unblind
    if varName == 'PHI' : PHI = tmp_unblind
    if varName == 'C'   : C   = tmp_unblind
    if varName == 'S'   : S   = tmp_unblind
    if varName == 'D'   : D   = tmp_unblind
    if varName == 'ACP' : ACP = tmp_unblind
    if varName == 'Af'  : Af  = tmp_unblind
    if varName == 'AP'  : AP  = tmp_unblind

  if D   != 0: D.Print()
  if ACP != 0 : ACP.Print()
  if Af  != 0 : Af.Print()
  if AP  != 0 : AP.Print()
 
  if C != 0 and S != 0 and AMP == 0 and PHI == 0: 
    C.Print()
    S.Print()
  elif C == 0 and S == 0 and AMP != 0 and PHI != 0:
    C = WS(ws, RooFormulaVar('%s_C_%s'%(name,year),'%s_C_%s'%(name,year),
                             '@0*cos(@1)', RooArgList(AMP,PHI)))
    S = WS(ws, RooFormulaVar('%s_S_%s'%(name,year),'%s_S_%s'%(name,year),
                             '@0*sin(@1)', RooArgList(AMP,PHI)))
    AMP.Print()
    PHI.Print()
    C.Print()
    S.Print()
  if C != 0 and S != 0 and D == 0:
    D = WS(ws, RooFormulaVar('%s_D_%s'%(name,year),'%s_D_%s'%(name,year),
                             '-sqrt(1-@0*@0-@1*@1)', RooArgList(C,S)))  
    D.Print()
     
  p = ws.obj("p")
  OmegasT = []
  OmegabarsT = []
  OmegasU = []
  OmegabarsU = []
  OmegasGen = []
  OmegabarsGen = []

  for tagName in taggerList :
    if "SS" in tagName:
      OmegasT.append(ws.obj("%s_Omega%sT_%s" % (name,tagName,year)))
      OmegabarsT.append(ws.obj("%s_Omegabar%sT_%s" % (name,tagName,year)))
      OmegasU.append(ws.obj("%s_Omega%sU_%s" % (name,tagName,year)))
      OmegabarsU.append(ws.obj("%s_Omegabar%sU_%s" % (name,tagName,year)))
      OmegasGen.append(ws.obj("%s_Omega%s_%s" % (name,tagName,year)))
      OmegabarsGen.append(ws.obj("%s_Omegabar%s_%s" % (name,tagName,year)))
    else:
      OmegasT.append(ws.obj("%s_Omega%s_%s" % (name,tagName,year)))
      OmegabarsT.append(ws.obj("%s_Omegabar%s_%s" % (name,tagName,year)))
      OmegasU.append(ws.obj("%s_Omega%s_%s" % (name,tagName,year)))
      OmegabarsU.append(ws.obj("%s_Omegabar%s_%s" % (name,tagName,year)))
      OmegasGen.append(ws.obj("%s_Omega%s_%s" % (name,tagName,year)))
      OmegabarsGen.append(ws.obj("%s_Omegabar%s_%s" % (name,tagName,year)))


  for i in range(len(OmegasT),2):
    OmegasT.append(RooRealConstant.value(1))
    OmegabarsT.append(RooRealConstant.value(1))
    OmegasU.append(RooRealConstant.value(1))
    OmegabarsU.append(RooRealConstant.value(1))
    OmegasGen.append(RooRealConstant.value(1))
    OmegabarsGen.append(RooRealConstant.value(1))

  flagCosh = 0
  flagSinh = 0
  flagCos  = 0
  flagSin  = 0
  if conf['CPState'] and conf['CPState'][0] == 'FS':

    if conf['CPState'][1] == 'Bd':
      flagCosh = RooFcoshFSFunc.Bd
      flagCos  = RooFcosFSFunc.Bd
    else:
      flagCosh = RooFcoshFSFunc.Bs
      flagCos  = RooFcosFSFunc.Bs

    fcoshT = WS( ws, RooFcoshFSFunc("%s_fcoshT_%s" % (name,year),
                                    "%s_fcoshT_%s" % (name,year),
                                    ACP, Af, AP,
                                    OmegasT[0],OmegasT[1],
                                    OmegabarsT[0],OmegabarsT[1],
                                    p,flagCosh))
    fsinhT = WS( ws, RooConstVar("%s_fsinhT_%s" % (name,year),
                                "%s_fsinhT_%s" % (name,year), 0))
    fcosT  = WS( ws, RooFcosFSFunc("%s_fcosT_%s" % (name,year),
                                  "%s_fcosT_%s" % (name,year),
                                  ACP, Af, AP,
                                  OmegasT[0],OmegasT[1],
                                  OmegabarsT[0],OmegabarsT[1],
                                  p,flagCos))
    fsinT  = WS( ws, RooConstVar("%s_fsinT_%s" % (name,year),
                                "%s_fsinT_%s" % (name,year), 0))
    fcoshU = WS( ws, RooFcoshFSFunc("%s_fcoshU_%s" % (name,year),
                                    "%s_fcoshU_%s" % (name,year),
                                    ACP, Af, AP,
                                    OmegasU[0],OmegasU[1],
                                    OmegabarsU[0],OmegabarsU[1],
                                    p,flagCosh))
    fsinhU = WS( ws, RooConstVar("%s_fsinhU_%s" % (name,year),
                                "%s_fsinhU_%s" % (name,year), 0))
    fcosU  = WS( ws, RooFcosFSFunc("%s_fcosU_%s" % (name,year),
                                  "%s_fcosU_%s" % (name,year),
                                  ACP, Af, AP,
                                  OmegasU[0],OmegasU[1],
                                  OmegabarsU[0],OmegabarsU[1],
                                  p,flagCos))
    fsinU  = WS( ws, RooConstVar("%s_fsinU_%s" % (name,year),
                                "%s_fsinU_%s" % (name,year), 0))

    fcoshGen = WS( ws, RooFcoshFSFunc("%s_fcoshGen_%s" % (name,year),
                                    "%s_fcoshGen_%s" % (name,year),
                                    ACP, Af, AP,
                                    OmegasGen[0],OmegasGen[1],
                                    OmegabarsGen[0],OmegabarsGen[1],
                                    p,flagCosh))
    fsinhGen = WS( ws, RooConstVar("%s_fsinhGen_%s" % (name,year),
                                   "%s_fsinhGen_%s" % (name,year), 0))
    fcosGen  = WS( ws, RooFcosFSFunc("%s_fcosGen_%s" % (name,year),
                                     "%s_fcosGen_%s" % (name,year),
                                     ACP, Af, AP,
                                     OmegasGen[0],OmegasGen[1],
                                     OmegabarsGen[0],OmegabarsGen[1],
                                     p,flagCos))
    fsinGen  = WS( ws, RooConstVar("%s_fsinGen_%s" % (name,year),
                                   "%s_fsinGen_%s" % (name,year), 0))

  elif conf['CPState'] and conf['CPState'][0] == 'CP':

    if conf['CPState'][1] == 'Bd':
      flagCosh = RooFcoshCPFunc.Bd
      flagSinh = RooFsinhCPFunc.Bd
      flagCos  = RooFcosCPFunc.Bd
      flagSin  = RooFsinCPFunc.Bd
    else:
      flagCosh = RooFcoshCPFunc.Bs
      flagSinh = RooFcoshCPFunc.Bs
      flagCos  = RooFcoshCPFunc.Bs
      flagSin  = RooFcoshCPFunc.Bs
 
    fcoshT = WS( ws, RooFcoshCPFunc("%s_fcoshT_%s" % (name,year),
                                   "%s_fcoshT_%s" % (name,year),
                                   C, S, AP,
                                   OmegasT[0],OmegasT[1],
                                   OmegabarsT[0],OmegabarsT[1],
                                   p,flagCosh))
    fsinhT = WS( ws, RooFsinhCPFunc("%s_fsinhT_%s" % (name,year),
                                   "%s_fsinhT_%s" % (name,year),
                                   C, S, D, AP,
                                   OmegasT[0],OmegasT[1],
                                   OmegabarsT[0],OmegabarsT[1],
                                   p,flagSinh))
    fcosT  = WS( ws, RooFcosCPFunc("%s_fcosT_%s" % (name,year),
                                  "%s_fcosT_%s" % (name,year),
                                  C, AP,
                                  OmegasT[0],OmegasT[1],
                                  OmegabarsT[0],OmegabarsT[1],
                                  p,flagCos))
    fsinT  = WS( ws, RooFsinCPFunc("%s_fsinT_%s" % (name,year),
                                  "%s_fsinT_%s" % (name,year),
                                  S, AP,
                                  OmegasT[0],OmegasT[1],
                                  OmegabarsT[0],OmegabarsT[1],
                                  p,flagSin))

    fcoshU = WS( ws, RooFcoshCPFunc("%s_fcoshU_%s" % (name,year),
                                   "%s_fcoshU_%s" % (name,year),
                                   C, S, AP,
                                   OmegasU[0],OmegasU[1],
                                   OmegabarsU[0],OmegabarsU[1],
                                   p,flagCosh))
    fsinhU = WS( ws, RooFsinhCPFunc("%s_fsinhU_%s" % (name,year),
                                   "%s_fsinhU_%s" % (name,year),
                                   C, S, D, AP,
                                   OmegasU[0],OmegasU[1],
                                   OmegabarsU[0],OmegabarsU[1],
                                   p,flagSinh))
    fcosU  = WS( ws, RooFcosCPFunc("%s_fcosU_%s" % (name,year),
                                  "%s_fcosU_%s" % (name,year),
                                  C, AP,
                                  OmegasU[0],OmegasU[1],
                                  OmegabarsU[0],OmegabarsU[1],
                                  p,flagCos))
    fsinU  = WS( ws, RooFsinCPFunc("%s_fsinU_%s" % (name,year),
                                  "%s_fsinU_%s" % (name,year),
                                  S, AP,
                                  OmegasU[0],OmegasU[1],
                                  OmegabarsU[0],OmegabarsU[1],
                                  p,flagSin))

    fcoshGen = WS( ws, RooFcoshCPFunc("%s_fcoshGen_%s" % (name,year),
                                      "%s_fcoshGen_%s" % (name,year),
                                      C, S, AP,
                                      OmegasGen[0],OmegasGen[1],
                                      OmegabarsGen[0],OmegabarsGen[1],
                                      p,flagCosh))
    fsinhGen = WS( ws, RooFsinhCPFunc("%s_fsinhGen_%s" % (name,year),
                                      "%s_fsinhGen_%s" % (name,year),
                                      C, S, D, AP,
                                      OmegasGen[0],OmegasGen[1],
                                      OmegabarsGen[0],OmegabarsGen[1],
                                      p,flagSinh))
    fcosGen  = WS( ws, RooFcosCPFunc("%s_fcosGen_%s" % (name,year),
                                     "%s_fcosGen_%s" % (name,year),
                                     C, AP,
                                     OmegasGen[0],OmegasGen[1],
                                     OmegabarsGen[0],OmegabarsGen[1],
                                     p,flagCos))
    fsinGen  = WS( ws, RooFsinCPFunc("%s_fsinGen_%s" % (name,year),
                                     "%s_fsinGen_%s" % (name,year),
                                     S, AP,
                                     OmegasGen[0],OmegasGen[1],
                                     OmegabarsGen[0],OmegabarsGen[1],
                                     p,flagSin))

  elif conf['CPState'] and conf['CPState'][0] == 'FStoCP':

    if conf['CPState'][1] == 'Bd':
      flagCosh = RooFcoshFSFunc.Bd
      flagCos  = RooFcosFSFunc.Bd
    else:
      flagCosh = RooFcoshFSFunc.Bs
      flagCos  = RooFcosFSFunc.Bs

    fcoshT = WS( ws, RooFcoshFStoCPFunc("%s_fcoshT_%s" % (name,year),
                                       "%s_fcoshT_%s" % (name,year),
                                       ACP, Af, AP,
                                       OmegasT[0],OmegasT[1],
                                       OmegabarsT[0],OmegabarsT[1],
                                       p,flagCosh))
    fsinhT = WS( ws, RooConstVar("%s_fsinhT_%s" % (name,year),
                                "%s_fsinhT_%s" % (name,year), 0))
    fcosT  = WS( ws, RooFcosFStoCPFunc("%s_fcosT_%s" % (name,year),
                                      "%s_fcosT_%s" % (name,year),
                                      ACP, Af, AP,
                                      OmegasT[0],OmegasT[1],
                                      OmegabarsT[0],OmegabarsT[1],
                                      p,flagCos))
    fsinT  = WS( ws, RooConstVar("%s_fsinT_%s" % (name,year),
                                "%s_fsinT_%s" % (name,year), 0))


    fcoshU = WS( ws, RooFcoshFStoCPFunc("%s_fcoshU_%s" % (name,year),
                                       "%s_fcoshU_%s" % (name,year),
                                       ACP, Af, AP,
                                       OmegasU[0],OmegasU[1],
                                       OmegabarsU[0],OmegabarsU[1],
                                       p,flagCosh))
    fsinhU = WS( ws, RooConstVar("%s_fsinhU_%s" % (name,year),
                                "%s_fsinhU_%s" % (name,year), 0))
    fcosU  = WS( ws, RooFcosFStoCPFunc("%s_fcosU_%s" % (name,year),
                                      "%s_fcosU_%s" % (name,year),
                                      ACP, Af, AP,
                                      OmegasU[0],OmegasU[1],
                                      OmegabarsU[0],OmegabarsU[1],
                                      p,flagCos))
    fsinU  = WS( ws, RooConstVar("%s_fsinU_%s" % (name,year),
                                "%s_fsinU_%s" % (name,year), 0))

    fcoshGen = WS( ws, RooFcoshFStoCPFunc("%s_fcoshGen_%s" % (name,year),
                                          "%s_fcoshGen_%s" % (name,year),
                                          ACP, Af, AP,
                                          OmegasGen[0],OmegasGen[1],
                                          OmegabarsGen[0],OmegabarsGen[1],
                                          p,flagCosh))
    fsinhGen = WS( ws, RooConstVar("%s_fsinhGen_%s" % (name,year),
                                   "%s_fsinhGen_%s" % (name,year), 0))
    fcosGen  = WS( ws, RooFcosFStoCPFunc("%s_fcosGen_%s" % (name,year),
                                         "%s_fcosU_%s" % (name,year),
                                         ACP, Af, AP,
                                         OmegasGen[0],OmegasGen[1],
                                         OmegabarsGen[0],OmegabarsGen[1],
                                         p,flagCos))
    fsinGen  = WS( ws, RooConstVar("%s_fsinGen_%s" % (name,year),
                                   "%s_fsinGen_%s" % (name,year), 0))

  elif conf['CPState'] and conf['CPState'][0] == 'CPtoFS':

    if conf['CPState'][1] == 'Bd':
      flagCosh = RooFcoshCPFunc.Bd
      flagSinh = RooFsinhCPFunc.Bd
      flagCos  = RooFcosCPFunc.Bd
      flagSin  = RooFsinCPFunc.Bd
    else:
      flagCosh = RooFcoshCPFunc.Bs
      flagSinh = RooFcoshCPFunc.Bs
      flagCos  = RooFcoshCPFunc.Bs
      flagSin  = RooFcoshCPFunc.Bs

    effKPI = 0
    effPIK = 0
    print "#####################", name
    if name.split('_')[0] == "bdpipi": 
      effKPI = ws.obj('eff_bdpipi_kpi_%s'%year)
      effPIK = ws.obj('eff_bdpipi_pik_%s'%year)
    elif name.split('_')[0] == 'bskk':
      effKPI = ws.obj('eff_bskk_kpi_%s'%year)
      effPIK = ws.obj('eff_bskk_pik_%s'%year)

    effKPI.Print()
    effPIK.Print()
    fcoshT = WS( ws, RooFcoshCPtoFSFunc("%s_fcoshT_%s" % (name,year),
                                   "%s_fcoshT_%s" % (name,year),
                                   C, S, AP,
                                   effKPI, effPIK,
                                   OmegasT[0],OmegasT[1],
                                   OmegabarsT[0],OmegabarsT[1],
                                   p,flagCosh))
    fsinhT = WS( ws, RooFsinhCPtoFSFunc("%s_fsinhT_%s" % (name,year),
                                   "%s_fsinhT_%s" % (name,year),
                                   C, S, D, AP,
                                   effKPI,effPIK,
                                   OmegasT[0],OmegasT[1],
                                   OmegabarsT[0],OmegabarsT[1],
                                   p,flagSinh))
    fcosT  = WS( ws, RooFcosCPtoFSFunc("%s_fcosT_%s" % (name,year),
                                  "%s_fcosT_%s" % (name,year),
                                  C, AP,
                                  effKPI,effPIK,
                                  OmegasT[0],OmegasT[1],
                                  OmegabarsT[0],OmegabarsT[1],
                                  p,flagCos))
    fsinT  = WS( ws, RooFsinCPtoFSFunc("%s_fsinT_%s" % (name,year),
                                  "%s_fsinT_%s" % (name,year),
                                  S, AP,
                                  effKPI,effPIK,
                                  OmegasT[0],OmegasT[1],
                                  OmegabarsT[0],OmegabarsT[1],
                                  p,flagSin))

    fcoshU = WS( ws, RooFcoshCPtoFSFunc("%s_fcoshU_%s" % (name,year),
                                   "%s_fcoshU_%s" % (name,year),
                                   C, S, AP,
                                   effKPI, effPIK,
                                   OmegasU[0],OmegasU[1],
                                   OmegabarsU[0],OmegabarsU[1],
                                   p,flagCosh))
    fsinhU = WS( ws, RooFsinhCPtoFSFunc("%s_fsinhU_%s" % (name,year),
                                   "%s_fsinhU_%s" % (name,year),
                                   C, S, D, AP,
                                   effKPI,effPIK,
                                   OmegasU[0],OmegasU[1],
                                   OmegabarsU[0],OmegabarsU[1],
                                   p,flagSinh))
    fcosU  = WS( ws, RooFcosCPtoFSFunc("%s_fcosU_%s" % (name,year),
                                  "%s_fcosU_%s" % (name,year),
                                  C, AP,
                                  effKPI,effPIK,
                                  OmegasU[0],OmegasU[1],
                                  OmegabarsU[0],OmegabarsU[1],
                                  p,flagCos))
    fsinU  = WS( ws, RooFsinCPtoFSFunc("%s_fsinU_%s" % (name,year),
                                  "%s_fsinU_%s" % (name,year),
                                  S, AP,
                                  effKPI,effPIK,
                                  OmegasU[0],OmegasU[1],
                                  OmegabarsU[0],OmegabarsU[1],
                                  p,flagSin))

    fcoshUGen = WS( ws, RooFcoshCPtoFSFunc("%s_fcoshGen_%s" % (name,year),
                                           "%s_fcoshGen_%s" % (name,year),
                                           C, S, AP,
                                           effKPI, effPIK,
                                           OmegasGen[0],OmegasGen[1],
                                           OmegabarsGen[0],OmegabarsGen[1],
                                           p,flagCosh))
    fsinhGen = WS( ws, RooFsinhCPtoFSFunc("%s_fsinhGen_%s" % (name,year),
                                          "%s_fsinhU_%s" % (name,year),
                                          C, S, D, AP,
                                          effKPI,effPIK,
                                          OmegasGen[0],OmegasGen[1],
                                          OmegabarsGen[0],OmegabarsGen[1],
                                          p,flagSinh))
    fcosGen  = WS( ws, RooFcosCPtoFSFunc("%s_fcosGen_%s" % (name,year),
                                         "%s_fcosGen_%s" % (name,year),
                                         C, AP,
                                         effKPI,effPIK,
                                         OmegasGen[0],OmegasGen[1],
                                         OmegabarsGen[0],OmegabarsGen[1],
                                         p,flagCos))
    fsinGen  = WS( ws, RooFsinCPtoFSFunc("%s_fsinGen_%s" % (name,year),
                                         "%s_fsinGen_%s" % (name,year),
                                         S, AP,
                                         effKPI,effPIK,
                                         OmegasGen[0],OmegasGen[1],
                                         OmegabarsGen[0],OmegabarsGen[1],
                                         p,flagSin))
  print("tagutils: createSingnalSinusoidTerms: ends")
  


def createPhysOmega(name = 'phys_kpi1', year = '', config = {}, taggerList = [], ws = None) :
  print("tagutils: createPhysOmega: starts")

  from ROOT import RooRealVar, RooOmegaBkgFunc, RooArgList
  conf = config[name]['tag'][year]
  omegaList = RooArgList()
  for tagName in taggerList :

    eps = 0
    epsAsym = 0

    varDict = conf[tagName]
    for varName,varVals in varDict.iteritems():

      tmp = 0
      if type(varVals) == str:
        tmp = ws.obj("%s" %(varVals))
      else:
        tmp = WS ( ws, RooRealVar("%s_%s%s_%s" % (name,varName,tagName,year),
                                  "%s_%s%s_%s" % (name,varName,tagName,year),
                                  varVals[0],varVals[1],varVals[2]))
        tmp.setConstant(varVals[3])

      if varName == 'eps' : eps = tmp
      if varName == 'epsAsym' : epsAsym = tmp

    q = ws.obj("q%s" % tagName)
    eta = ws.obj("eta%s" % tagName)
    etaHistPdf = ws.obj("%s_%s_HistPdf_%s" % (name,eta.GetName(),year))
    omega = WS( ws, RooOmegaBkgFunc("%s_Omega%s_%s" % (name, tagName, year),
                                    "%s_Omega%s_%s" % (name, tagName, year),
                                    q,eta,eps,epsAsym,etaHistPdf) )
    omegaList.add(omega)

  from ROOT import RooProdPdf
  pdf = WS( ws, RooProdPdf("%s_pdftag_%s" % (name,year),
                           "%s_pdftag_%s" % (name,year),
                           omegaList) )
  print("tagutils: createPhysOmega: ends")
  

def createBkgOmega(name = 'bkg_kpi', year = '', config = {}, taggerList = [], ws = None) :
  print("tagutils: createBkgOmega: starts")
  from ROOT import RooRealVar, RooOmegaBkgFunc, RooArgList, RooRealConstant, RooOmegaBkgFuncNew
  conf = config[name]['tag'][year]
  #omegaList = RooArgList()
  epsOS1 = 0
  epsOS0 = 0
  epsAsymOS1 = 0
  epsAsymOS0 = 0
  epsSS = 0
  epsAsymSS = 0

  for tagName in taggerList :

    varDict = conf[tagName]
    for varName,varVals in varDict.iteritems():
      tmp = 0
      if type(varVals) == str:
        tmp = ws.obj("%s" %(varVals))
      else:
        tmp = WS ( ws, RooRealVar("%s_%s%s_%s" % (name,varName,tagName,year),
                                  "%s_%s%s_%s" % (name,varName,tagName,year),
                                  varVals[0],varVals[1],varVals[2]))
        tmp.setConstant(varVals[3])
      #print "VARIABLE UNDER CONSTRUCTION %s\n"%(tmp.GetName())
      if 'OS' in tagName:
        if varName == 'eps1'     : epsOS1 = tmp
        if varName == 'epsAsym1' : epsAsymOS1 = tmp
        if varName == 'eps0'     : epsOS0 = tmp
        if varName == 'epsAsym0' : epsAsymOS0 = tmp
      else:
        if varName == 'eps'      : epsSS = tmp
        if varName == 'epsAsym'  : epsAsymSS = tmp

  qOS = None
  qSS = None
  etaOS = None
  etaSS = None
  etaHistPdfOS = None
  etaHistPdfSS = None

  for tagName in taggerList:
    if "OS" in tagName:
      qOS = ws.obj("q%s"%tagName)
      etaOS = ws.obj("eta%s"%tagName)
      etaHistPdfOS = ws.obj("%s_eta%s_HistPdf_%s" % (name,tagName,year))
    elif "SS" in tagName:
      qSS = ws.obj("q%s"%tagName)
      etaSS = ws.obj("eta%s"%tagName)
      etaHistPdfSS = ws.obj("%s_eta%s_HistPdf_%s" % (name,tagName,year))
    else:
      print "Wrong name for tagger"

  omega = WS( ws, RooOmegaBkgFuncNew("%s_pdftag_%s" % (name, year),
                                     "%s_pdftag_%s" % (name, year),
                                     qOS,qSS,etaOS,etaSS,
                                     epsOS0,epsOS1,epsAsymOS0,epsAsymOS1,
                                     epsSS,epsAsymSS,
                                     etaHistPdfOS,etaHistPdfSS) )
  print("tagutils: createBkgOmega: ends")
  

def createBkgTag(name = 'phys_kpi1', year = '', config = {}, taggerList = [], state = "kpi", ws = None) :
  print("tagutils: createBkgTag: starts")
  
  from ROOT import RooRealVar, RooTagFunc, RooTagFuncNew, RooArgList
  conf = config[name]['CP'][year]

  ACP = 0
  AtagOS = 0
  AtagSS = 0
  for varName,varVals in conf.iteritems():
    tmp = 0
    if type(varVals) == str:
      tmp = ws.obj("%s" % (varVals))
    else:
      tmp = WS( ws, RooRealVar("%s_%s_%s" % (name,varName,year),
                               "%s_%s_%s" % (name,varName,year),
                               varVals[0],varVals[1],varVals[2] ) )
      tmp.setConstant(varVals[3])
    if varName == "ACP"      : ACP = tmp
    if varName == 'AtagOS'   : AtagOS = tmp
    if varName == 'AtagSS'   : AtagSS = tmp

  qj = 0
  qi = ws.obj('qOS')
  for tagger in taggerList:
    if 'SS' in tagger: 
      qj = ws.obj('q%s'%tagger)

  p = ws.obj('p')
  if state == "kpi":
    pdf = WS( ws, RooTagFuncNew("%s_pdfstate_%s" % (name,year),
                             "%s_pdfstate_%s" % (name,year),
                             p,qi,qj,ACP,AtagOS,AtagSS,RooTagFuncNew.KPI) )
  elif state == "pipi":
    pdf = WS( ws, RooTagFuncNew("%s_pdfstate_%s" % (name,year),
                             "%s_pdfstate_%s" % (name,year),
                             p,qi,qj,ACP,AtagOS,AtagSS,RooTagFuncNew.PIPI) )
  elif state == "kk":
    pdf = WS( ws, RooTagFuncNew("%s_pdfstate_%s" % (name,year),
                             "%s_pdfstate_%s" % (name,year),
                             p,qi,qj,ACP,AtagOS,AtagSS,RooTagFuncNew.KK) )
  print("tagutils: createBkgTag: ends")
  
