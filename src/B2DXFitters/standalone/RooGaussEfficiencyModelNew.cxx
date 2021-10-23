/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 * @(#)root/roofit:$Id: RooGaussModel.cxx 44982 2012-07-10 08:36:13Z moneta $
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
// Class RooGaussModel implements a RooResolutionModel that models a Gaussian
// distribution. Object of class RooGaussModel can be used
// for analytical convolutions with classes inheriting from RooAbsAnaConvPdf
// After  the convolution  is applied,  the result is multiplied with an
// efficiency, which can be any implementation of the RooAbsGaussModelEfficiency
// interface
// END_HTML
//
#include <memory>

#include "RVersion.h"

#include "B2DXFitters/RooGaussEfficiencyModelNew.h"
#include "B2DXFitters/RooEffConvGenContext.h"
#include "B2DXFitters/RooAbsGaussModelEfficiency.h"
#include "RooMath.h"
#include "RooRealConstant.h"
#include "RooRandom.h"

using namespace std;

namespace {
    enum basisType { noBasis=0  ,  expBasis= 3
                   , sinBasis=13,  cosBasis=23
                   , sinhBasis=63, coshBasis=53 };
    static const Double_t rootpi(sqrt(TMath::Pi())) ;

    std::complex<double> evalApprox(Double_t x, const std::complex<double>& z) {
      // compute exp(-x^2)cwerf(-i(z-x)), cwerf(z) = exp(-z^2)erfc(-iz)
      // use the approximation: erfc(z) = exp(-z*z)/(sqrt(pi)*z)
      // to explicitly cancel the divergent exp(y*y) behaviour of
      // CWERF for z = x + i y with large negative y
      static const std::complex<double> mi(0,-1);
      std::complex<double> zp  = mi*(z-x);
      std::complex<double> zsq = zp*zp;
      std::complex<double> v = -zsq - x*x;
      std::complex<double> iz(z.imag()+x,z.real()-x); // ???
      return exp(v)*(exp(zsq)/(iz*rootpi) + 1.)*2. ;
    }

    // Calculate Re[exp(-x^2) cwerf(i (z-x) )], taking care of numerical instabilities
    Double_t evalRe(Double_t x, const std::complex<double>& z) {
      Double_t re =  z.real()-x;
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,34,8)
      return (re>-5.0) ? RooMath::faddeeva_fast(std::complex<double>(-z.imag(),re)).real()*exp(-x*x)
                       : evalApprox(x,z).real() ;
#else
      return (re>-5.0) ? RooMath::FastComplexErrFunc(RooComplex(-z.imag(),re)).re()*exp(-x*x)
                       : evalApprox(x,z).real() ;
#endif
    }

    // Calculate Im[exp(-x^2) cwerf(i(z-x))], taking care of numerical instabilities
    Double_t evalIm(Double_t x, const std::complex<double>& z) {
      Double_t re = z.real()-x;
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,34,8)
      return (re>-5.0) ? RooMath::faddeeva_fast(std::complex<double>(-z.imag(),re)).imag()*exp(-x*x)
                       : evalApprox(x,z).imag() ;
#else
      return (re>-5.0) ? RooMath::FastComplexErrFunc(RooComplex(-z.imag(),re)).im()*exp(-x*x)
                       : evalApprox(x,z).imag() ;
#endif
    }

}


//_____________________________________________________________________________
RooGaussEfficiencyModelNew::RooGaussEfficiencyModelNew(const char *name, const char *title, 
                                                 RooRealVar& xx, 
                                                 RooAbsGaussModelEfficiency& _eff1,
                                                 RooAbsGaussModelEfficiency& _eff2, 
                                                 RooCategory& _q,
                                                 RooAbsReal& _mean, RooAbsReal& _sigma )
   : RooResolutionModel(name, title, xx),
     RooAbsEffResModel(),
     _flatSFInt(kFALSE),
     eff1("eff1","Spline describing efficiency1",this,_eff1),
     eff2("eff2","Spline describing efficiency2",this,_eff2),
     q("q","q",this,_q),
     mean("mean","Mean",this,_mean),
     sigma("sigma","Width",this,_sigma),
     msf("msf","Mean Scale Factor",this,RooRealConstant::value(1.0)),
     ssf("ssf","Sigma Scale Factor",this,RooRealConstant::value(1.0))
{
   // make sure 'x' matches the eff argument!
   std::auto_ptr<RooArgSet> svar1( eff1.arg().getVariables() );
   assert( svar1->contains( convVar() ) );
   std::auto_ptr<RooArgSet> svar2( eff2.arg().getVariables() );
   assert( svar2->contains( convVar() ) );

}

//_____________________________________________________________________________
RooGaussEfficiencyModelNew::RooGaussEfficiencyModelNew(const char *name, const char *title,
                                                     RooRealVar& xx, 
                                                     RooAbsGaussModelEfficiency& _eff1,
                                                     RooAbsGaussModelEfficiency& _eff2,
                                                     RooCategory& _q,
                                                     RooAbsReal& _mean, RooAbsReal& _sigma,
                                                     RooAbsReal& _meanSF, RooAbsReal& _sigmaSF)
   : RooResolutionModel(name,title,xx),
     RooAbsEffResModel(),
     _flatSFInt(kFALSE),
     eff1("eff1","Spline describing efficiency1",this,_eff1),
     eff2("eff2","Spline describing efficiency2",this,_eff2),
     q("q","q",this,_q),
     mean("mean","Mean",this,_mean),
     sigma("sigma","Width",this,_sigma),
     msf("msf","Mean Scale Factor",this,_meanSF),
     ssf("ssf","Sigma Scale Factor",this,_sigmaSF)
{
   // make sure 'x' matches the spline argument!
   std::auto_ptr<RooArgSet> svar1( eff1.arg().getVariables() );
   assert( svar1->contains( convVar() ) );
   std::auto_ptr<RooArgSet> svar2( eff2.arg().getVariables() );
   assert( svar2->contains( convVar() ) );

  
   //unRegisterProxy(q);
 
   //for (int i=0 ; i<numProxies() ; i++) {
   //   RooAbsProxy* p = getProxy(i) ;
   //   if (!p) continue ;
   //   printf("%d %s\n",p->nset(),p->name());
      //if(!strcmp(p->name(),"q")) unRegisterProxy(RooArgProxy(p));
//      getProxy(i)->changeNormSet(nset) ;
   //}
   //exit(1);

}

//_____________________________________________________________________________
RooGaussEfficiencyModelNew::RooGaussEfficiencyModelNew(const RooGaussEfficiencyModelNew& other,
                                                   const char* name)
   : RooResolutionModel(other,name),
     RooAbsEffResModel(),
     _flatSFInt(other._flatSFInt),
     eff1("eff1",this,other.eff1),
     eff2("eff2",this,other.eff2),
     q("q",this,other.q),
     mean("mean",this,other.mean),
     sigma("sigma",this,other.sigma),
     msf("msf",this,other.msf),
     ssf("ssf",this,other.ssf)
{

    //unRegisterProxy(q);
}

//_____________________________________________________________________________
RooGaussEfficiencyModelNew::~RooGaussEfficiencyModelNew()
{
  // Destructor
}

//_____________________________________________________________________________
Int_t RooGaussEfficiencyModelNew::basisCode(const char* name) const
{
  if (!TString("exp(-@0/@1)"              ).CompareTo(name)) return expBasis;
  if (!TString("exp(-@0/@1)*sin(@0*@2)"   ).CompareTo(name)) return sinBasis;
  if (!TString("exp(-@0/@1)*cos(@0*@2)"   ).CompareTo(name)) return cosBasis;
  if (!TString("exp(-@0/@1)*cosh(@0*@2/2)").CompareTo(name)) return coshBasis;
  if (!TString("exp(-@0/@1)*sinh(@0*@2/2)").CompareTo(name)) return sinhBasis;
  return 0 ;
}

//_____________________________________________________________________________
const RooAbsReal* RooGaussEfficiencyModelNew::efficiency() const
{
    if(q==0) return &eff1.arg();
    else     return &eff2.arg();
}

//_____________________________________________________________________________
RooArgSet* RooGaussEfficiencyModelNew::observables() const {
   // Return pointer to pdf in product
   // verify whether efficiency depends on additional observables!!!
   return new RooArgSet(convVar());
}

//_____________________________________________________________________________
std::complex<double> RooGaussEfficiencyModelNew::evalInt1(Double_t umin, Double_t umax,
                                                       Double_t scale, Double_t _offset,
                                                       const std::complex<double>& z) const
{
    const RooAbsGaussModelEfficiency &sp = dynamic_cast<const RooAbsGaussModelEfficiency&>( eff1.arg() );
    return sp.productAnalyticalIntegral( umin, umax, scale, _offset, z) ;
}

std::complex<double> RooGaussEfficiencyModelNew::evalInt2(Double_t umin, Double_t umax,
                                                       Double_t scale, Double_t _offset,
                                                       const std::complex<double>& z) const
{
    const RooAbsGaussModelEfficiency &sp = dynamic_cast<const RooAbsGaussModelEfficiency&>( eff2.arg() );
    return sp.productAnalyticalIntegral( umin, umax, scale, _offset, z) ;
}

//_____________________________________________________________________________
Double_t RooGaussEfficiencyModelNew::evaluate() const
{

  basisType basiscode = (basisType) _basisCode ;
  Double_t tau    = (basiscode!=noBasis)                           ? ((RooAbsReal*)basis().getParameter(1))->getVal() : 0 ;
  Double_t omega  = (basiscode==sinBasis  || basiscode==cosBasis)  ? ((RooAbsReal*)basis().getParameter(2))->getVal() : 0 ;
  Double_t dGamma = (basiscode==sinhBasis || basiscode==coshBasis) ? ((RooAbsReal*)basis().getParameter(2))->getVal() : 0 ;
  if (basiscode  == coshBasis && basiscode!=noBasis && dGamma==0 ) basiscode = expBasis;

  Double_t scale = sigma*ssf*TMath::Sqrt2();
  Double_t u = (x-mean*msf)/scale;
  // *** 1st form: Straight Gaussian, used for unconvoluted PDF or expBasis with 0 lifetime ***
  if (basiscode==noBasis || ((basiscode==expBasis || basiscode==cosBasis) && tau==0)) {
    if (verboseEval()>2) cout << "RooGaussEfficiencyModelNew::evaluate(" << GetName() << ") 1st form" << endl ;
    Double_t _eff= (q==0) ? eff1.arg().getVal() :
                            eff2.arg().getVal();
    if (TMath::IsNaN(_eff))
       cxcoutE(Tracing) << "RooGaussEfficiencyModelNew::evaluate(" << GetName()
                        << ") got nan during efficiency " << endl;
    Double_t xVal = x, meanVal = mean, sigmaVal = sigma, msfVal = msf, ssfVal = ssf;
    Int_t iq = q;
    printf("STICAZZI1 %d %g %g\n",iq,xVal,_eff);
    return _eff * exp(-u*u)/(scale*rootpi) ; // ???
  }

  // *** 2nd form: 0, used for sinBasis, linBasis, and quadBasis with tau=0 ***
  if (tau==0) {
    if (verboseEval()>2) cout << "RooGaussEfficiencyModelNew::evaluate(" << GetName() << ") 2nd form" << endl ;
    return 0. ;
  }
  std::complex<double> z( double(1)/tau, -omega ); z*=0.5*scale;

  Double_t val(0);
  if (verboseEval()>2) cout << "RooGaussEfficiencyModelNew::evaluate(" << GetName() << ") basiscode = " <<  basiscode << " z = " << z << ", u = " << u << endl ;

  switch (basiscode) {
    case expBasis:
    case cosBasis:
        val +=             evalRe(u,z);
        break;
    case sinBasis:
        val += z.imag()!=0 ? evalIm(u,z) : 0;
        break;
    case coshBasis:
    case sinhBasis: {
        std::complex<double> y( scale * dGamma / 4 , 0 );
        val += (                                      evalRe(u,z-y)
               + ( basiscode == coshBasis ? +1 : -1 )*evalRe(u,z+y) )/2;
        break;
    }
    default:
        assert(0);
  }
  if (TMath::IsNaN(val))
     cxcoutE(Tracing) << "RooGaussEfficiencyModelNew::evaluate(" << GetName()
                      << ") got nan during basiscode = " << basiscode << endl;
  Double_t _eff= (q==0) ? eff1 : eff2;
  if (TMath::IsNaN(_eff))
     cxcoutE(Tracing) << "RooGaussEfficiencyModelNew::evaluate(" << GetName()
                      << ") got nan during efficiency " << endl;

  Double_t xVal = x, meanVal = mean, sigmaVal = sigma, msfVal = msf, ssfVal = ssf;
  Int_t iq = q;
  printf("STICAZZI2 %d %g %g %g\n",iq,xVal,_eff,val);
  return _eff*val;
}


//_____________________________________________________________________________
Int_t RooGaussEfficiencyModelNew::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const
{
  switch(_basisCode) {
  // Analytical integration capability of raw PDF
  case noBasis:
    // Optionally advertise flat integral over sigma scale factor
    if (_flatSFInt && matchArgs(allVars,analVars,RooArgSet(convVar(),ssf.arg()))) return 2 ;
    //if (matchArgs(allVars,analVars,RooArgSet(convVar(),q.arg()))) {printf("MINCHIE1\n"); return 1;}
    if (matchArgs(allVars,analVars,convVar())) return 1 ;
    //if (matchArgs(allVars,analVars,RooArgSet(q.arg()))) {printf("MINCHIE2\n"); return 1;}
    break ;

  // Analytical integration capability of convoluted PDF
  case expBasis:
  case sinBasis:
  case cosBasis:
  case coshBasis:
  case sinhBasis:
    // Optionally advertise flat integral over sigma scale factor
    if (_flatSFInt && matchArgs(allVars,analVars,RooArgSet(convVar(),ssf.arg()))) return 2 ;
    if (matchArgs(allVars,analVars,RooArgSet(convVar(),q.arg()))) return 3;
    if (matchArgs(allVars,analVars,convVar())) return 1 ;
    if (matchArgs(allVars,analVars,RooArgSet(q.arg()))) return 4;
    break ;
  }
  return 0 ;
}

//_____________________________________________________________________________
Double_t RooGaussEfficiencyModelNew::analyticalIntegral(Int_t code, const char* rangeName) const
{
  // Code must be 1 or 2
  printf("INTEGRATION CODE %d\n",code);
 
  //if(code==3) return 1; 

  if(code==4) return evaluate();

  //assert(code==1||code==2) ;
  Double_t ssfInt( code==2 ? (ssf.max(rangeName)-ssf.min(rangeName)) : 1.0 );

  basisType basiscode = (basisType) _basisCode ;
  Double_t tau    = (basiscode!=noBasis)                           ? ((RooAbsReal*)basis().getParameter(1))->getVal() : 0 ;
  Double_t omega  = (basiscode==sinBasis  || basiscode==cosBasis)  ? ((RooAbsReal*)basis().getParameter(2))->getVal() : 0 ;
  Double_t dGamma = (basiscode==sinhBasis || basiscode==coshBasis) ? ((RooAbsReal*)basis().getParameter(2))->getVal() : 0 ;
  if (basiscode == coshBasis && basiscode!=noBasis && dGamma==0 ) basiscode = expBasis;

  Double_t scale  = sigma*ssf*TMath::Sqrt2();
  Double_t _offset = mean*msf;
  Double_t umin = (x.min(rangeName)-_offset)/scale;
  Double_t umax = (x.max(rangeName)-_offset)/scale;

  if (basiscode==noBasis || ((basiscode==expBasis || basiscode==cosBasis) && tau==0)) {
    if (verboseEval()>0) cout << "RooGaussEfficiencyModelNew::analyticalIntegral(" << GetName() << ") 1st form" << endl ;
    Double_t result =  0.5*(RooMath::erf( umax )-RooMath::erf( umin )) ;
    if (TMath::IsNaN(result)) { cxcoutE(Tracing) << "RooGaussEfficiencyModelNew::analyticalIntegral(" << GetName() << ") got nan during case 1 " << endl; }
    return result*ssfInt ; // ???
  }
  if (tau==0) {
    if (verboseEval()>0) cout << "RooGaussEfficiencyModelNew::analyticalIntegral(" << GetName() << ") 2nd form" << endl ;
    return 0. ;
  }

  std::complex<double> z( double(1)/tau, -omega ); z=0.5*z*scale;

  if (verboseEval()>0) cout << "RooGaussEfficiencyModelNew::analyticalIntegral(" << GetName() << ") basiscode = " << basiscode << " z = " << z << endl ;

  Double_t result(0);
  switch (basiscode) {
    case expBasis:
    case cosBasis:
        result +=  (q==0) ? evalInt1(umin,umax,scale,_offset,z).real() :
                            evalInt2(umin,umax,scale,_offset,z).real();
        break;
    case sinBasis:
        result += z.imag()!=0 ? ( (q==0) ? evalInt1(umin,umax,scale,_offset,z).imag() :
                                           evalInt2(umin,umax,scale,_offset,z).imag() ) : 0 ;
        break;
    case coshBasis:
    case sinhBasis: {
        std::complex<double> y( scale * dGamma / 4 , 0 );
        result += 0.5 * ( ((q==0) ? evalInt1(umin,umax,scale,_offset,z-y).real() :
                                    evalInt2(umin,umax,scale,_offset,z-y).real() ) 
                        + ( basiscode == coshBasis ? +1 : -1 )*(
                          (q==0) ? evalInt1(umin,umax,scale,_offset,z+y).real() :
                                   evalInt2(umin,umax,scale,_offset,z+y).real() ) );
        break;
    }
    default:
        assert(0) ;
  }
  if (TMath::IsNaN(result)) { cxcoutE(Tracing) << "RooGaussEfficiencyModelNew::analyticalIntegral("
                                               << GetName() << ") got nan for basiscode = "
                                               << basiscode << endl;
  }
  Int_t iq = q;
  Double_t time = x;
  printf("INTEGRAL: %d %g %g %g %g\n",iq,time,scale,result,ssfInt);
  
  return (code==3) ? scale*result*ssfInt : scale*result*ssfInt;
}


//_____________________________________________________________________________
RooAbsGenContext* RooGaussEfficiencyModelNew::modelGenContext
(const RooAbsAnaConvPdf& convPdf, const RooArgSet &vars, const RooDataSet *prototype,
 const RooArgSet* auxProto, Bool_t verbose) const
{
   return new RooEffConvGenContext(convPdf, vars, prototype, auxProto, verbose);
}

//_____________________________________________________________________________
Bool_t RooGaussEfficiencyModelNew::isDirectGenSafe(const RooAbsArg& arg) const
{
   return (!TString(convVar().GetName()).CompareTo(arg.GetName())) 
       || RooResolutionModel::isDirectGenSafe(arg);
}

//_____________________________________________________________________________
Int_t RooGaussEfficiencyModelNew::getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t /*staticInitOK*/) const
{
  if (matchArgs(directVars,generateVars,x)) { return 1 ;  }
  return 0 ;
}

//_____________________________________________________________________________
void RooGaussEfficiencyModelNew::generateEvent(Int_t code)
{
  if (code != 1) {
    coutE(InputArguments) << "RooGaussEfficiencyModelNew::generateEvent("
        << GetName()<< "): argument \"code\" can only have value 1"
        << std::endl;
    assert(code==1);
  }

  Double_t xmin = x.min();
  Double_t xmax = x.max();
  Double_t m = mean*msf;
  Double_t s = sigma*ssf;
  TRandom *generator = RooRandom::randomGenerator();
  while(true) {
    Double_t xgen = generator->Gaus(m,s);
    if (xgen<xmax && xgen>xmin) {
      x = xgen ; return ;
    }
  }
}

