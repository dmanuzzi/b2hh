/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id$
 * Authors:                                                                  *
 *   GR, Gerhard Raven, VU&Nikhef Amsterdam
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_CS_GAUSS_MODELNEW
#define ROO_CS_GAUSS_MODELNEW

#include <complex>
#include "RooResolutionModel.h"
#include "RooRealProxy.h"
#include "RooCategory.h"
#include "RooCategoryProxy.h"
#include "RooAbsEffResModel.h"

class RooAbsReal;
class RooRealVar;
class RooAbsGaussModelEfficiency;

class RooGaussEfficiencyModelNew : public RooResolutionModel, public RooAbsEffResModel {
public:

  // Constructors, assignment etc
  inline RooGaussEfficiencyModelNew() : _flatSFInt(kFALSE)  { }
  RooGaussEfficiencyModelNew(const char *name, const char *title,
            RooRealVar& x, 
            RooAbsGaussModelEfficiency& spline1,
            RooAbsGaussModelEfficiency& spline2,
            RooCategory& _q,
            RooAbsReal& mean,   RooAbsReal& sigma );
  RooGaussEfficiencyModelNew(const char *name, const char *title,
            RooRealVar& x, 
            RooAbsGaussModelEfficiency& spline1,
            RooAbsGaussModelEfficiency& spline2,
            RooCategory& _q,
            RooAbsReal& mean,   RooAbsReal& sigma,
            RooAbsReal& meanSF, RooAbsReal& sigmaSF) ;
  RooGaussEfficiencyModelNew(const RooGaussEfficiencyModelNew& other, const char* name=0);
  virtual ~RooGaussEfficiencyModelNew();

  virtual TObject* clone(const char* newname) const { return new RooGaussEfficiencyModelNew(*this,newname) ; }

  virtual Int_t basisCode(const char* name) const ;
  virtual Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  virtual Double_t analyticalIntegral(Int_t code, const char* rangeName) const ;

  // TODO: move this one to the mixin-interface
  virtual RooAbsGenContext* modelGenContext(const RooAbsAnaConvPdf& convPdf, const RooArgSet &vars,
                                             const RooDataSet *prototype=0, const RooArgSet* auxProto=0,
                                             Bool_t verbose= kFALSE) const;
  Bool_t isDirectGenSafe(const RooAbsArg& arg) const;
  Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK) const;
  void generateEvent(Int_t code);

  void advertiseFlatScaleFactorIntegral(Bool_t flag) { _flatSFInt = flag ; }

  virtual const RooAbsReal* efficiency() const;

  virtual RooArgSet* observables() const;

private:

  virtual Double_t evaluate() const ;

  std::complex<double> evalInt1(Double_t xmin, Double_t xmax,
                               Double_t scale, Double_t offset,
                               const std::complex<double>& z) const;
  std::complex<double> evalInt2(Double_t xmin, Double_t xmax,
                               Double_t scale, Double_t offset,
                               const std::complex<double>& z) const;

  Bool_t _flatSFInt ;

  RooRealProxy eff1 ;
  RooRealProxy eff2 ;
  RooCategoryProxy q;
  RooRealProxy mean ;
  RooRealProxy sigma ;
  RooRealProxy msf ;
  RooRealProxy ssf ;

  ClassDef(RooGaussEfficiencyModelNew,1)
};

#endif
