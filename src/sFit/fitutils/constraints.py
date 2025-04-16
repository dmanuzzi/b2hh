from B2DXFitters.WS import WS as WS


def makeConstraint(ws = None):


  import ROOT
  from ROOT import RooMultiVarGaussian, RooRealVar, RooArgList, TMatrixDSym

  bskpi_G = ws.obj('bskpi_G')
  bskpi_dG = ws.obj('bskpi_dG')
  bskpi_G_mean = WS(ws, RooRealVar('bskpi_G_mean','bskpi_G_mean',bskpi_G.getVal()))
  bskpi_dG_mean = WS(ws, RooRealVar('bskpi_dG_mean','bskpi_dG_mean',bskpi_dG.getVal()))
  covMatrix = TMatrixDSym(2)
  covMatrix[0][0] = bskpi_G.getError()*bskpi_G.getError()
  covMatrix[1][1] = bskpi_dG.getError()*bskpi_dG.getError()
  covMatrix[1][0] = -0.292*bskpi_G.getError()*bskpi_dG.getError()
  covMatrix[0][1] = -0.292*bskpi_G.getError()*bskpi_dG.getError()
  constGsvsdG = WS( ws, RooMultiVarGaussian('const_bskpi_G_bskpi_dG','const_bskpi_G_bskpi_dG',
                                           RooArgList(bskpi_G,bskpi_dG),
                                           RooArgList(bskpi_G_mean,bskpi_dG_mean),
                                           covMatrix))

  bdkpi_G = ws.obj('bdkpi_G')
  bdkpi_G_mean =  WS(ws, RooRealVar('bdkpi_G_mean','bdkpi_G_mean',bdkpi_G.getVal()))
  bdkpi_G_sigma =  WS(ws, RooRealVar('bdkpi_G_sigma','bdkpi_G_sigma',bdkpi_G.getError()))
  from ROOT import RooGaussian
  constGd = WS(ws, RooGaussian('const_bdkpi_G','const_bdkpi_G',
                               bdkpi_G,bdkpi_G_mean,bdkpi_G_sigma))


  bdkpi_dM = ws.obj('bdkpi_dM')
  bdkpi_dM_mean  = WS(ws, RooRealVar('bdkpi_dM_mean','bdkpi_dM_mean',bdkpi_dM.getVal()))
  bdkpi_dM_sigma = WS(ws, RooRealVar('bdkpi_dM_sigma','bdkpi_dM_sigma',bdkpi_dM.getError()))
  constdMD = WS(ws, RooGaussian('const_bdkpi_dM','const_bdkpi_dM',
                                bdkpi_dM,bdkpi_dM_mean,bdkpi_dM_sigma))

  bskpi_dM = ws.obj('bskpi_dM')
  bskpi_dM_mean  = WS(ws, RooRealVar('bskpi_dM_mean','bskpi_dM_mean',bskpi_dM.getVal()))
  bskpi_dM_sigma = WS(ws, RooRealVar('bskpi_dM_sigma','bskpi_dM_sigma',bskpi_dM.getError()))
  constdMS = WS(ws, RooGaussian('const_bskpi_dM','const_bskpi_dM',
                                bskpi_dM,bskpi_dM_mean,bskpi_dM_sigma))

  bdkpi_timeErr_sf_mean = ws.obj('bdkpi_timeErr_sf_mean')
  bdkpi_timeErr_sf_sigma = ws.obj('bdkpi_timeErr_sf_sigma')

  bdkpi_timeErr_sf_mean_mean = WS(ws, RooRealVar('bdkpi_timeErr_sf_mean_mean',
                                                 'bdkpi_timeErr_sf_mean_mean',bdkpi_timeErr_sf_mean.getVal()))
  bdkpi_timeErr_sf_sigma_mean = WS(ws, RooRealVar('bdkpi_timeErr_sf_sigma_mean',
                                                 'bdkpi_timeErr_sf_sigma_mean',bdkpi_timeErr_sf_sigma.getVal()))
  covMatrixTimeErr = TMatrixDSym(2)
  covMatrix[0][0] = bdkpi_timeErr_sf_mean.getError()*bdkpi_timeErr_sf_mean.getError()
  covMatrix[1][1] = bdkpi_timeErr_sf_sigma.getError()*bdkpi_timeErr_sf_sigma.getError()
  covMatrix[1][0] = -0.32*bdkpi_timeErr_sf_mean.getError()*bdkpi_timeErr_sf_sigma.getError()
  covMatrix[0][1] = -0.32*bdkpi_timeErr_sf_mean.getError()*bdkpi_timeErr_sf_sigma.getError()
  constTimeErr = WS( ws, RooMultiVarGaussian('constTimeErr','constTimeErr',
                                             RooArgList(bdkpi_timeErr_sf_mean,bdkpi_timeErr_sf_sigma),
                                             RooArgList(bdkpi_timeErr_sf_mean_mean,bdkpi_timeErr_sf_sigma_mean),
                                             covMatrixTimeErr))

  return [constGsvsdG,constGd,constdMD,constdMS,constTimeErr]

