from B2DXFitters.WS import WS

def createSignalTimeResModel(name = 'bdkpi', year = '', config = {}, ws = None) :
  print("resmodelutils: createSingnalTimeResModel: starts")
  print("resmodelutils: createSingnalTimeResModel: channel: %s"%name)
  print("resmodelutils: createSingnalTimeResModel:    year: %s"%year)
  from ROOT import RooRealVar, RooGaussEfficiencyModel, RooGaussEfficiencyModelNew, RooArgSet, RooGaussModel

  conf = config[name]['timeErr'][year]
  time = ws.obj('time')
  timeErr = ws.obj('timeErr')
  accTimeT = ws.obj('%s_accTimeT_%s'%(name,year))
  accTimeU = ws.obj('%s_accTimeU_%s'%(name,year))

  mean = 0
  sigma = 0
  sf_mean = 0
  sf_sigma = 0
  sf_ratio = 0
  frac = 0
 
  for varName,varVals in conf.iteritems():

    tmp = 0
    if type(varVals) == str:
      tmp = ws.obj('%s' % (varVals))
    else:
      tmp = WS( ws, RooRealVar('%s_timeErr_%s_%s' % (name,varName,year),
                               '%s_timeErr_%s_%s' % (name,varName,year),
                               varVals[0],varVals[1],varVals[2]))
      tmp.setConstant(varVals[3])

    if varName == 'mean'     : mean = tmp
    if varName == 'sf_mean'  : sf_mean = tmp
    if varName == 'sf_sigma' : sf_sigma = tmp
    if varName == 'sf_ratio' : sf_ratio = tmp
    if varName == 'frac'     : frac = tmp
    if varName == 'sigma'    : sigma = tmp

  resTAcc  = 0
  resTAcc1 = 0
  resTAcc2 = 0

  if sigma == 0:

    from ROOT import RooFormulaVar, RooArgList, RooAddModel
    timeErrFunc1 = WS( ws, RooFormulaVar("%s_timeErrFunc1_%s" % (name,year),
                                         "%s_timeErrFunc1_%s" % (name,year),
                                         "@1+@2*(@0-0.03)",RooArgList(timeErr,sf_mean,sf_sigma)))
    timeErrFunc2 = WS( ws, RooFormulaVar("%s_timeErrFunc2_%s" % (name,year),
                                         "%s_timeErrFunc2_%s" % (name,year),
                                         "@0*@1",RooArgList(timeErrFunc1,sf_ratio)))
    resTAcc1 = WS( ws, RooGaussEfficiencyModel('%s_resTAcc1_%s' % (name,year),
                                               '%s_resTAcc1_%s' % (name,year),
                                               time,accTime,mean,timeErrFunc1))
    resTAcc1.setParameterizeIntegral(RooArgSet(ws.obj('timeErr')))
    resTAcc2 = WS( ws, RooGaussEfficiencyModel('%s_resTAcc2_%s' % (name,year),
                                               '%s_resTAcc2_%s' % (name,year),
                                               time,accTime,mean,timeErrFunc2))
    resTAcc2.setParameterizeIntegral(RooArgSet(ws.obj('timeErr')))
    resTAcc = WS( ws, RooAddModel('%s_resTAcc_%s' % (name,year),
                                  '%s_resTAcc_%s' % (name,year),
                                  RooArgList(resTAcc1,resTAcc2),RooArgList(frac)))

    if config['generate']['flag']:

      resT1 = WS( ws, RooGaussModel('%s_resT1_%s' % (name,year),
                                    '%s_resT1_%s' % (name,year),
                                    time,mean,timeErrFunc1))
      resT2 = WS( ws, RooGaussModel('%s_resT2_%s' % (name,year),
                                    '%s_resT2_%s' % (name,year),
                                    time,mean,timeErrFunc2))
      resT  = WS( ws, RooAddModel('%s_resT_%s' % (name,year),
                                  '%s_resT_%s' % (name,year),
                                  RooArgList(resT1,resT2),RooArgList(frac)))

  else:

    #qSS = ws.obj('qSS')
    #resTAcc = WS( ws, RooGaussEfficiencyModelNew('%s_resTAcc_%s' % (name,year),
    #                                          '%s_resTAcc_%s' % (name,year),
    #                                          time,accTime1,accTime2,qSS,mean,sigma,sf_mean,sf_sigma))
    resTAccT = WS(ws, RooGaussEfficiencyModel('%s_resTAccT_%s' % (name,year),
                                              '%s_resTAccT_%s' % (name,year),
                                              time,accTimeT,mean,sigma,sf_mean,sf_sigma))
    resTAccU = WS(ws, RooGaussEfficiencyModel('%s_resTAccU_%s' % (name,year),
                                              '%s_resTAccU_%s' % (name,year),
                                              time,accTimeU,mean,sigma,sf_mean,sf_sigma))

    #resTAcc.setParameterizeIntegral(RooArgSet(ws.obj('timeErr')))

    if config['generate']['flag']:

      resT = WS( ws, RooGaussModel('%s_resT_%s' % (name,year),
                                   '%s_resT_%s' % (name,year),
                                   time,mean,sigma,sf_mean,sf_sigma))
 
  print("resmodelutils: createSingnalTimeResModel: ends")
  return resTAcc

def createBkgTimeErrShape(name = 'bdkpi', year = '', config = {}, ws = None) :

  from ROOT import RooRealVar, RooDecay, RooGaussModel, RooAddModel, RooArgList

  if config[name].has_key('timeErr'):
    conf = config[name]['timeErr']
  else:
    return None
  timeErr = ws.obj('timeErr')

  alpha = 0
  mean1 = 0
  mean2 = 0
  sigma = 0
  frac  = 0

  for varName,varVals in conf.iteritems():

    tmp = 0
    if type(varVals) == str:

      tmp = ws.obj('%s_timeErr_%s' % (varVals,varName))

    else:
      tmp = WS( ws, RooRealVar('%s_timeErr_%s' % (name,varName),
                               '%s_timeErr_%s' % (name,varName),
                               varVals[0],varVals[1],varVals[2]))
      tmp.setConstant(varVals[3])

    if varName == 'alpha' : alpha = tmp
    if varName == 'mean1' : mean1 = tmp
    if varName == 'mean2' : mean2 = tmp
    if varName == 'sigma' : sigma = tmp
    if varName == 'frac'  : frac  = tmp

  res1 = WS(ws, RooGaussModel('%s_res1_timeErr_%s'%(name,year),
                              '%s_res1_timeErr_%s'%(name,year),
                              timeErr,mean1,sigma))
  res2 = WS(ws, RooGaussModel('%s_res2_timeErr_%s'%(name,year),
                              '%s_res2_timeErr_%s'%(name,year),
                              timeErr,mean2,sigma))
  res = WS(ws, RooAddModel('%s_res_timeErr_%s'%(name,year),
                           '%s_res_timeErr_%s'%(name,year),
                           RooArgList(res1,res2),RooArgList(frac)))

  timeErrPdf = WS(ws, RooDecay('%s_pdftimeErr_%s'%(name,year),
                               '%s_pdftimeErr_%s'%(name,year),
                               timeErr,alpha,res,RooDecay.SingleSided))

  #return timeErrPdf

def createSigTimeErrShape(name = 'bdkpi', year = '', config = {}, ws = None) :

  from ROOT import RooRealVar, RooDecay, RooGaussModel, RooAddModel, RooArgList

  if config[name].has_key('timeErr'):
    conf = config[name]['timeErr']
  else:
    return None
  timeErr = ws.obj('timeErr')

  alpha = 0
  mean1 = 0
  mean2 = 0
  sigma = 0
  frac  = 0

  for varName,varVals in conf.iteritems():

    tmp = 0
    if type(varVals) == str:

      tmp = ws.obj('%s_timeErr_%s' % (varVals,varName))

    else:
      tmp = WS( ws, RooRealVar('%s_timeErr_%s' % (name,varName),
                               '%s_timeErr_%s' % (name,varName),
                               varVals[0],varVals[1],varVals[2]))
      tmp.setConstant(varVals[3])

    if varName == 'alpha' : alpha = tmp
    if varName == 'mean1' : mean1 = tmp
    if varName == 'mean2' : mean2 = tmp
    if varName == 'sigma2' : sigma = tmp
    if varName == 'frac2'  : frac  = tmp

  res1 = WS(ws, RooGaussModel('%s_res1_timeErr_%s'%(name,year),
                              '%s_res1_timeErr_%s'%(name,year),
                              timeErr,mean1,sigma))
  res2 = WS(ws, RooGaussModel('%s_res2_timeErr_%s'%(name,year),
                              '%s_res2_timeErr_%s'%(name,year),
                              timeErr,mean2,sigma))
  res = WS(ws, RooAddModel('%s_res_timeErr_%s'%(name,year),
                           '%s_res_timeErr_%s'%(name,year),
                           RooArgList(res1,res2),RooArgList(frac)))

  timeErrPdf = WS(ws, RooDecay('%s_pdftimeErr_%s'%(name,year),
                               '%s_pdftimeErr_%s'%(name,year),
                               timeErr,alpha,res,RooDecay.SingleSided))









