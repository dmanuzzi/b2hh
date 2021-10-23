#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Double_t getOmega(Double_t &eta, Double_t &p0,  Double_t &p1, Double_t &etaHat) {

  Double_t omega = p0+p1*(eta-etaHat);

  return omega;

}

void combineTag(Int_t &q1, Double_t &w1, Int_t &q2, Double_t &w2, Int_t &q, Double_t &w) {

  Double_t pB     = (q1==1)*(1-w1)+(q1==-1)*w1+(q1==0)*0.5;
  Double_t pBbar  = (q1==-1)*(1-w1)+(q1==1)*w1+(q1==0)*0.5;
           pB    *= (q2==1)*(1-w2)+(q2==-1)*w2+(q2==0)*0.5;
           pBbar *= (q2==-1)*(1-w2)+(q2==1)*w2+(q2==0)*0.5;

  pB /= (pB+pBbar);

  if(pB > 0.5) { q =  1; w = (1-pB); }
  else         { q = -1; w = pB;     }


}

void combineTag(Int_t &q1, Double_t &w1, 
                Int_t &q2, Double_t &w2, 
                Int_t &q3, Double_t &w3,
                Int_t &q,  Double_t &w) {

  Double_t pB     = (q1==1)*(1-w1)+(q1==-1)*w1+(q1==0)*0.5;
  Double_t pBbar  = (q1==-1)*(1-w1)+(q1==1)*w1+(q1==0)*0.5;
           pB    *= (q2==1)*(1-w2)+(q2==-1)*w2+(q2==0)*0.5;
           pBbar *= (q2==-1)*(1-w2)+(q2==1)*w2+(q2==0)*0.5;
           pB    *= (q3==1)*(1-w3)+(q3==-1)*w3+(q3==0)*0.5;
           pBbar *= (q3==-1)*(1-w3)+(q3==1)*w3+(q3==0)*0.5;

  pB /= (pB+pBbar);

  if(pB > 0.5) { q =  1; w = (1-pB); }
  else         { q = -1; w = pB;     }


}

