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

#include "RooFit.h"

#include "Riostream.h"
#include "Riostream.h"
#include <math.h>

#include "RooPolyNew.h"
#include "RooRealVar.h"

using namespace std;

ClassImp(RooPolyNew)


//_____________________________________________________________________________
RooPolyNew::RooPolyNew(const char *name, const char *title,
			       RooAbsCategory& _q, RooAbsReal& _x, RooAbsReal& _cT, RooAbsReal& _cU) :
  RooAbsPdf(name, title), 
  q("q","q",this,_q),
  x("x","Dependent",this,_x),
  cT("cT","ExponentT",this,_cT),
  cU("cU","ExponentU",this,_cU)

{
}


//_____________________________________________________________________________
RooPolyNew::RooPolyNew(const RooPolyNew& other, const char* name) :
  RooAbsPdf(other, name), 
  q("q",this,other.q),
  x("x",this,other.x), 
  cT("cT",this,other.cT),
  cU("cU",this,other.cU)

{
}


//_____________________________________________________________________________
Double_t RooPolyNew::evaluate() const{
  //cout << "exp(x=" << x << ",c=" << c << ")=" << exp(c*x) << endl ;

  Double_t retVal = q == 0 ? 1+cU*x : 1+cT*x;
  return retVal;
}


//_____________________________________________________________________________
Int_t RooPolyNew::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const 
{
  if (matchArgs(allVars,analVars,x)) return 1 ;
  return 0 ;
}


//_____________________________________________________________________________
Double_t RooPolyNew::analyticalIntegral(Int_t code, const char* rangeName) const 
{

  Double_t retVal = 0;
  Double_t xMax = x.max(rangeName);
  Double_t xMin = x.min(rangeName);

  if(code==1) {
    if(q==0) {
      if(cU==0.0)
        retVal = (xMax - xMin);
      else
        retVal =  xMax - xMin + 0.5*cU*(xMax*xMax-xMin*xMin);
    }
    else {
      if(cT==0.0)
        retVal = (xMax - xMin);
      else
        retVal = xMax - xMin + 0.5*cT*(xMax*xMax-xMin*xMin);
    }
  }
  return retVal ;
}

