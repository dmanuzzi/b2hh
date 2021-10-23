/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: RooPolyNew.h,v 1.10 2007/07/12 20:30:49 wouter Exp $
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
#ifndef ROO_POLYNEW
#define ROO_POLYNEW

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"

class RooRealVar;
class RooAbsReal;

class RooPolyNew : public RooAbsPdf {
public:
  RooPolyNew() {} ;
  RooPolyNew(const char *name, const char *title,
		 RooAbsCategory& _q, RooAbsReal& _x, RooAbsReal& _cT, RooAbsReal& _cU);
  RooPolyNew(const RooPolyNew& other, const char* name=0);
  virtual TObject* clone(const char* newname) const { return new RooPolyNew(*this,newname); }
  inline virtual ~RooPolyNew() { }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const ;
  Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const ;

protected:
  RooCategoryProxy q;
  RooRealProxy x;
  RooRealProxy cT;
  RooRealProxy cU;

  Double_t evaluate() const;

private:
  ClassDef(RooPolyNew,1) // Poly PDF
};

#endif
