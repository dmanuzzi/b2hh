/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: RooExponentialNew.h,v 1.10 2007/07/12 20:30:49 wouter Exp $
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_EXPONENTIALNEW_h
#define ROO_EXPONENTIALNEW_h

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"

class RooRealVar;
class RooAbsReal;

class RooExponentialNew : public RooAbsPdf {
public:
  RooExponentialNew() {} ;
  RooExponentialNew(const char *name, const char *title,
		 RooAbsCategory& _q, RooAbsReal& _x, RooAbsReal& _cT, RooAbsReal& _cU);
  RooExponentialNew(const RooExponentialNew& other, const char* name=0);
  virtual TObject* clone(const char* newname) const { return new RooExponentialNew(*this,newname); }
  inline virtual ~RooExponentialNew() { }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:
  RooCategoryProxy q;
  RooRealProxy x;
  RooRealProxy cT;
  RooRealProxy cU;

  Double_t evaluate() const;

private:
  ClassDef(RooExponentialNew,1) // Exponential PDF
};

#endif
