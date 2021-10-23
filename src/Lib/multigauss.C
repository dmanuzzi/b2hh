#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <multigauss.h>

gaussND::gaussND(std::vector<Double_t> &means, TMatrixDSym &covMatrix) {

  Int_t sizeMeans = means.size();
  Int_t sizeCov   = covMatrix.GetNrows(); 
  if(sizeMeans!=sizeCov) {
    printf("Size of means is different from size of covariance matrix\n");
  }
  setSize(sizeMeans);
  setMeans(means);
  _y = std::vector<Double_t>(sizeMeans,0);
  setCov(covMatrix);

}

void gaussND::setCov(TMatrixDSym &covMatrix) { 
  _covMatrix = new TMatrixDSym(_size);
  _invCovMatrix = new TMatrixDSym(_size);
  for(Int_t i = 0; i < _size; ++i) {
    for(Int_t j = 0; j < _size; ++j) {
      _covMatrix[0][i][j] = covMatrix[i][j];
      _invCovMatrix[0][i][j] = covMatrix[i][j];
    }
  } 
  _choleskyMatrix = new TMatrixD(_size,_size);
  cholesky();
  Double_t det = 0;
  _invCovMatrix->Invert(&det);

}

void gaussND::cholesky() {

  for(Int_t i = 0; i < _size; i++) {
    for (Int_t j = 0; j < (i+1); j++) {
      Double_t s = 0;
      for (Int_t k = 0; k < j; k++)
        s += _choleskyMatrix[0][i][k] * _choleskyMatrix[0][j][k];

      _choleskyMatrix[0][i][j] = (i == j) ? sqrt(_covMatrix[0][i][i] - s) :
                                         (_covMatrix[0][i][j] - s)/ _choleskyMatrix[0][j][j];
      printf("STICAZZI %d %d %g %g\n",i,j,_covMatrix[0][i][j],_choleskyMatrix[0][i][j]);
    }
  }

}
    
void gaussND::generate(Double_t *x) {

  for(Int_t i = 0; i < _size; ++i) {
    x[i] = _means[i];
    _y[i] = gRandom->Gaus(0,1);
  }

  for(Int_t i = 0; i < _size; ++i) {
    for(Int_t j = 0; j < _size; ++j) {
      x[i] += _choleskyMatrix[0][i][j]*_y[j];
    }
  }

}

Double_t gaussND::logLikelihood(Double_t * x) {

  Double_t arg = 0;
  for(Int_t i = 0; i < _size; ++i) {
    for(Int_t j = 0; j < _size; ++j) {
      arg += (x[i]-_means[i])*_invCovMatrix[0][i][j]*(x[j]-_means[j]);
    }
  }

  Double_t retVal = 0.5*arg;
  return retVal;

}
