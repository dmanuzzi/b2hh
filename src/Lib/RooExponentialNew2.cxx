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
#ifndef ROO_EXPONENTIALNEW2_cxx
#define ROO_EXPONENTIALNEW2_cxx

#include "RooFit.h"

#include "Riostream.h"
#include "Riostream.h"
#include <math.h>

#include "RooExponentialNew2.h"
#include "RooRealVar.h"
#include "TF1.h"

using namespace std;

ClassImp(RooExponentialNew2)


//_____________________________________________________________________________
RooExponentialNew2::RooExponentialNew2(const char *name, const char *title,
			       RooAbsCategory& _qOS, RooAbsCategory& _qSS,
             RooAbsReal& _x, RooAbsReal& _time, 
             RooAbsReal& _p0_11, RooAbsReal& _p1_11, RooAbsReal& _p2_11,
             RooAbsReal& _p0_10, RooAbsReal& _p1_10, RooAbsReal& _p2_10,
             RooAbsReal& _p0_01, RooAbsReal& _p1_01, RooAbsReal& _p2_01,
             RooAbsReal& _p0_00, RooAbsReal& _p1_00, RooAbsReal& _p2_00) :
  RooAbsPdf(name, title), 
  qOS("qOS","qOS",this,_qOS),
  qSS("qSS","qSS",this,_qSS),
  x("x","Dependent",this,_x),
  time("time","time",this,_time),
  p0_11("p0_11","p0_11",this,_p0_11),
  p1_11("p1_11","p1_11",this,_p1_11),
  p2_11("p2_11","p2_11",this,_p2_11),
  p0_10("p0_10","p0_10",this,_p0_10),
  p1_10("p1_10","p1_10",this,_p1_10),
  p2_10("p2_10","p2_10",this,_p2_10),
  p0_01("p0_01","p0_01",this,_p0_01),
  p1_01("p1_01","p1_01",this,_p1_01),
  p2_01("p2_01","p2_01",this,_p2_01),
  p0_00("p0_00","p0_00",this,_p0_00),
  p1_00("p1_00","p1_00",this,_p1_00),
  p2_00("p2_00","p2_00",this,_p2_00)
{

  //[0]*(1+tanh([1]*(x-[2])))

}

Double_t RooExponentialNew2::funcSlope() const {

  Double_t ret = 0;
  if(qOS!=0&&qSS!=0)
    ret = p0_11*(1+tanh(p1_11*(time-p2_11)));
  else if(qOS!=0&&qSS==0)
    ret = p0_10*(1+tanh(p1_10*(time-p2_10)));
  else if(qOS==0&&qSS!=0)
    ret = p0_01*(1+tanh(p1_01*(time-p2_01)));
  else if(qOS==0&&qSS==0)
    ret = p0_00*(1+tanh(p1_00*(time-p2_00)));
  else { printf("CRETINO\n"); exit(1); }

  return ret;

}

//_____________________________________________________________________________
RooExponentialNew2::RooExponentialNew2(const RooExponentialNew2& other, const char* name) :
  RooAbsPdf(other, name), 
  qOS("qOS",this,other.qOS),
  qSS("qSS",this,other.qSS),
  x("x",this,other.x),
  time("time",this,other.time),
  p0_11("p0_11",this,other.p0_11),
  p1_11("p1_11",this,other.p1_11),
  p2_11("p2_11",this,other.p2_11),
  p0_10("p0_10",this,other.p0_10),
  p1_10("p1_10",this,other.p1_10),
  p2_10("p2_10",this,other.p2_10),
  p0_01("p0_01",this,other.p0_01),
  p1_01("p1_01",this,other.p1_01),
  p2_01("p2_01",this,other.p2_01),
  p0_00("p0_00",this,other.p0_00),
  p1_00("p1_00",this,other.p1_00),
  p2_00("p2_00",this,other.p2_00)

{

}



//_____________________________________________________________________________
Double_t RooExponentialNew2::evaluate() const{
  //cout << "exp(x=" << x << ",c=" << c << ")=" << exp(c*x) << endl ;

  Double_t slope = funcSlope();
  Double_t retVal = exp(slope*x);
  return retVal;
}


//_____________________________________________________________________________
Int_t RooExponentialNew2::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const 
{
  if (matchArgs(allVars,analVars,x)) return 1 ;
  return 0 ;
}


//_____________________________________________________________________________
Double_t RooExponentialNew2::analyticalIntegral(Int_t code, const char* rangeName) const 
{

  Double_t retVal = 0;
  Double_t xMax = x.max(rangeName);
  Double_t xMin = x.min(rangeName);
  //Double_t xMax = 5.0;
  //Double_t xMin = 6.2;

  Double_t slope = funcSlope();

  if(code==1) {
    if(slope==0.0)
      retVal = (xMax - xMin);
    else
      retVal =  ( exp( slope*xMax ) - exp( slope*xMin ) )/slope;
  }
  if (retVal<0)
    printf("retVal: %g, slope: %g, xMax: %g, xMin: %g\n",
            retVal, slope, xMax, xMin);
  return retVal ;
}

#endif