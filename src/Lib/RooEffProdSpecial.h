/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: RooEffProdSpecial.h,v 1.2 2007/05/11 10:14:56 verkerke Exp $
 * Authors:                                                                  *
 *   GR, Gerhard Raven, NIKHEF/VU                                            *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_EFF_PROD_SPECIAL_h
#define ROO_EFF_PROD_SPECIAL_h

#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooObjCacheManager.h"

class RooEffProdSpecial: public RooAbsPdf {
public:
  // Constructors, assignment etc
  inline RooEffProdSpecial() : _nset(0), _fixedNset(0) { };
  virtual ~RooEffProdSpecial();
  RooEffProdSpecial(const char *name, const char *title, RooAbsPdf& pdf, RooAbsReal& efficiency);
  RooEffProdSpecial(const RooEffProdSpecial& other, const char* name=0);

  virtual TObject* clone(const char* newname) const { return new RooEffProdSpecial(*this,newname); }

  virtual RooAbsGenContext* genContext(const RooArgSet &vars, const RooDataSet *prototype,
                                       const RooArgSet* auxProto, Bool_t verbose) const;

  virtual Double_t getValV(const RooArgSet* set=0) const ;

  virtual Bool_t forceAnalyticalInt(const RooAbsArg& /*dep*/) const { 
    // Return kTRUE to force RooRealIntegral to offer all observables for internal integration
    return kTRUE ; 
  }
  Int_t getAnalyticalIntegralWN(RooArgSet& allVars, RooArgSet& numVars, const RooArgSet* normSet, const char* rangeName=0) const ;
  Double_t analyticalIntegralWN(Int_t code, const RooArgSet* normSet, const char* rangeName=0) const ;
  
protected:
  
  const RooAbsPdf* pdf() const { 
    // Return pointer to pdf in product
    return (RooAbsPdf*) _pdf.absArg() ; 
  }
  const RooAbsReal* eff() const { 
    // Return pointer to efficiency function in product
    return (RooAbsReal*) _eff.absArg() ; 
  }

  // Function evaluation
  virtual Double_t evaluate() const ;

  class CacheElem : public RooAbsCacheElement {
  public:
    CacheElem() : _clone(0), _int(0) {} 
    virtual ~CacheElem() { delete _int ; delete _clone ; }
    // Payload
    RooArgSet   _intObs ;
    RooEffProdSpecial* _clone ;
    RooAbsReal* _int ;    
    // Cache management functions
    virtual RooArgList containedArgs(Action) ;
  } ;
  mutable RooObjCacheManager _cacheMgr ; //! The cache manager


  // the real stuff...
  RooRealProxy _pdf ;               // Probability Density function
  RooRealProxy _eff;                // Efficiency function
  mutable const RooArgSet* _nset  ; //! Normalization set to be used in evaluation

  RooArgSet* _fixedNset ; //! Fixed normalization set overriding default normalization set (if provided)

  ClassDef(RooEffProdSpecial,2) // Product operator p.d.f of (PDF x efficiency) implementing optimized generator context
};

#endif
