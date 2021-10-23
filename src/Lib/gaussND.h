#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <TMatrixDSym.h>
#include <TMatrixD.h>
#include <TRandom3.h>
#include <TTree.h>
#include <TFile.h>

using namespace std;

TMatrixD cholesky(TMatrixDSym &cov) {

  Int_t n = cov.GetNcols();
  TMatrixD L(n,n);

  for(Int_t i = 0; i < n; i++) {
    for (Int_t j = 0; j < (i+1); j++) {
      Double_t s = 0;
      for (Int_t k = 0; k < j; k++)
        s += L[i][k] * L[j][k];

      L[i][j] = (i == j) ? sqrt(cov[i][i] - s) :
                           (cov[i][j] - s)/L[j][j];

    }
  }

  return L;

}

void gaussND(std::vector<Double_t> &means, TMatrixD &cov, std::vector<Double_t> &x) {

  Int_t n = cov.GetNcols();

  std::vector<Double_t> tmp(2,0);

  for(Int_t i = 0; i<n; ++i) {

    x[i] = means[i];
    tmp[i] = gRandom->Gaus(0,1);
  }
  for(Int_t i = 0; i<n; ++i) {

    for(Int_t j = 0; j<n; j++) {

      x[i] += cov[i][j]*tmp[j];

    }
  }

}
