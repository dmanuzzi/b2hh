/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 * @(#)root/roofit:$Id$
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

//////////////////////////////////////////////////////////////////////////////
//
// BEGIN_HTML
// Exponential p.d.f
// END_HTML
//
#ifndef ROO_EXPONENTIALNEW_cxx
#define ROO_EXPONENTIALNEW_cxx

#include "RooFit.h"

#include "Riostream.h"
#include "Riostream.h"
#include <math.h>

#include "RooExponentialNew.h"
#include "RooRealVar.h"

using namespace std;

ClassImp(RooExponentialNew)


//_____________________________________________________________________________
RooExponentialNew::RooExponentialNew(const char *name, const char *title,
			       RooAbsCategory& _q, RooAbsReal& _x, RooAbsReal& _cT, RooAbsReal& _cU) :
  RooAbsPdf(name, title), 
  q("q","q",this,_q),
  x("x","Dependent",this,_x),
  cT("cT","ExponentT",this,_cT),
  cU("cU","ExponentU",this,_cU)

{
}


//_____________________________________________________________________________
RooExponentialNew::RooExponentialNew(const RooExponentialNew& other, const char* name) :
  RooAbsPdf(other, name), 
  q("q",this,other.q),
  x("x",this,other.x), 
  cT("cT",this,other.cT),
  cU("cU",this,other.cU)

{
}


//_____________________________________________________________________________
Double_t RooExponentialNew::evaluate() const{
  //cout << "exp(x=" << x << ",c=" << c << ")=" << exp(c*x) << endl ;

  Double_t retVal = q == 0 ? exp(cU*x) : exp(cT*x);
  return retVal;
}


//_____________________________________________________________________________
Int_t RooExponentialNew::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const 
{
  if (matchArgs(allVars,analVars,x)) return 1 ;
  return 0 ;
}


//_____________________________________________________________________________
Double_t RooExponentialNew::analyticalIntegral(Int_t code, const char* rangeName) const 
{

  Double_t retVal = 0;
  Double_t xMax = x.max(rangeName);
  Double_t xMin = x.min(rangeName);

  if(code==1) {
    if(q==0) {
      if(cU==0.0)
        retVal = (xMax - xMin);
      else
        retVal =  ( exp( cU*xMax ) - exp( cU*xMin ) )/cU;
    }
    else {
      if(cT==0.0)
        retVal = (xMax - xMin);
      else
        retVal =  ( exp( cT*xMax ) - exp( cT*xMin ) )/cT;
    }
  }
  return retVal ;
}

#endif