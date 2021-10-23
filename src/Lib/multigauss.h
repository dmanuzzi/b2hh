#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TMatrixDSym.h>
#include <TMatrixD.h>
#include <TRandom3.h>

using namespace std;

class gaussND {

  public:

    gaussND(){};
    gaussND(std::vector<Double_t> &means, TMatrixDSym &covMatrix);
    ~gaussND(){};
    void generate(Double_t *x);
    TMatrixDSym * getCov() { return _covMatrix; }
    TMatrixDSym * getInvCov() { return _invCovMatrix; }
    Double_t logLikelihood(Double_t * x);
    
  private:

    Int_t _size = 0;
    std::vector<Double_t> _means;
    std::vector<Double_t> _y; // used in generation
    void setSize(Int_t &size) { _size = size;}
    void setMeans(std::vector<Double_t> &means) { _means = means; }
    void setCov(TMatrixDSym &covMatrix);
    void cholesky();
    TMatrixDSym * _covMatrix;
    TMatrixDSym * _invCovMatrix;
    TMatrixD    * _choleskyMatrix;
};
