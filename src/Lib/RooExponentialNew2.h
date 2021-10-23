/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: RooExponentialNew2.h,v 1.10 2007/07/12 20:30:49 wouter Exp $
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
#ifndef ROO_EXPONENTIALNEW2_h
#define ROO_EXPONENTIALNEW2_h

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "TF1.h"

class RooRealVar;
class RooAbsReal;

class RooExponentialNew2 : public RooAbsPdf {
public:
  RooExponentialNew2() {} ;
  RooExponentialNew2(const char *name, const char *title,
             RooAbsCategory& _qOS, RooAbsCategory& _qSS, 
             RooAbsReal& _x, RooAbsReal& _time, 
             RooAbsReal& _p0_11, RooAbsReal& _p1_11, RooAbsReal& _p2_11,
             RooAbsReal& _p0_10, RooAbsReal& _p1_10, RooAbsReal& _p2_10,
             RooAbsReal& _p0_01, RooAbsReal& _p1_01, RooAbsReal& _p2_01,
             RooAbsReal& _p0_00, RooAbsReal& _p1_00, RooAbsReal& _p2_00);
  RooExponentialNew2(const RooExponentialNew2& other, const char* name=0);
  virtual TObject* clone(const char* newname) const { return new RooExponentialNew2(*this,newname); }
  inline virtual ~RooExponentialNew2() { }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:
  RooCategoryProxy qOS;
  RooCategoryProxy qSS;
  RooRealProxy x;
  RooRealProxy time;
  RooRealProxy p0_11;
  RooRealProxy p1_11;
  RooRealProxy p2_11;
  RooRealProxy p0_10;
  RooRealProxy p1_10;
  RooRealProxy p2_10;
  RooRealProxy p0_01;
  RooRealProxy p1_01;
  RooRealProxy p2_01;
  RooRealProxy p0_00;
  RooRealProxy p1_00;
  RooRealProxy p2_00;

  Double_t evaluate() const;
  Double_t funcSlope() const;

private:
  ClassDef(RooExponentialNew2,1) // Exponential PDF
};

#endif
