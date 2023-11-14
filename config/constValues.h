#ifndef config_CONSTVALUES_h
#define config_CONSTVALUES_h

using namespace std;
namespace selection_cuts {
    
    const Double_t mass_min = 5.0;
    const Double_t mass_max = 6.2;

    const Double_t time_min =  0.2;
    const Double_t time_max = 14.2;
    
    const Double_t timeErr_max = 0.1;
};

namespace phys {
    const Double_t dms = 17.757;
    const Double_t dmd = 0.5065;
    const Double_t mpi = 139.57018;
    const Double_t mk = 493.677;
    const Double_t mp = 938.272030;
};


namespace timeModels_cuts {
    const Double_t minWinTot = selection_cuts::mass_min;
    const Double_t maxWinTot = selection_cuts::mass_max;
    const Double_t minWinLow = minWinTot;
    const Double_t maxWinLow = 5.366;
    const Double_t minWinFit = 5.5;
    const Double_t maxWinFit = maxWinTot;
    const Double_t minWinHigh = maxWinLow; 
    const Double_t maxWinHigh = maxWinTot;
    const Double_t minWinSig = 5.23;
    const Double_t maxWinSig = 5.32;
    const Double_t minTimeFit = selection_cuts::time_min;
    const Double_t maxTimeFit = selection_cuts::time_max;

    const Double_t massCutPIPI = 5.15;
    const Double_t massCutKK   = 5.20;
}

namespace accSignal_cuts {
    const Double_t mass_min_sig = timeModels_cuts::minWinSig;
    const Double_t mass_max_sig = timeModels_cuts::maxWinSig;
    const Double_t minTimeFit   = selection_cuts::time_min;
    const Double_t maxTimeFit   = selection_cuts::time_max;
    std::vector<Double_t> knots = {0.201, 0.27, 0.4, 0.6, 0.8, 1, 1.25, 1.75, 2, 2.3, 3, 4, 5, 6, 7, 8, 9};
    // std::vector<Double_t> knots = {0.2,0.27,0.4,0.6,0.8,1,1.25,1.75,2,2.3,3,4,5,6,7,8,9};
    // std::vector<Double_t> knots = {1.2, 1.5, 1.75, 2, 2.3, 3, 4, 5, 6, 7, 8, 9};
    //  std::vector<Double_t> knots = {1.5,1.75,2,2.3,3,4,5,6,7,8,9};
};

namespace accSignal_consts {
    const Double_t  tauData = 1.520, tauBd = 1.519,
                    tauBsH = 1.661, tauBsL = 1.405,
                    tauLb = 1.451, tauKK = 1.512,
                    tauBs = 2. / (1. / tauBsH + 1. / tauBsL),
                    dgBs = (1. / tauBsL - 1. / tauBsH);
    const Double_t CKK = 0.23945601652608023, SKK = 0.22134502198975092;
    const Double_t ADGKK = -sqrt(1 - CKK * CKK - SKK * SKK);
    const Double_t dGoGKK = 0.179518, GKK = 1. / tauKK;
    const Double_t dGKK = dGoGKK * GKK;
    const Double_t tauKKH = 1 / (GKK - 0.5 * dGKK),
                   tauKKL = 1 / (GKK + 0.5 * dGKK);
    // const Double_t dms = phys::dms;
    const Double_t dms = 17.8;
    const Double_t dmd = phys::dmd;
};

namespace tagging_cuts {
    const Double_t massMinBd   = 5.20;
    const Double_t massMaxBd   = 5.34;
    const Double_t massMinBs   = 5.34;
    const Double_t massMaxBs   = 5.44;
    const Double_t massMinBkg  = timeModels_cuts::minWinFit;
    const Double_t massMaxBkg  = timeModels_cuts::maxWinFit;
    const Double_t timeMin     = selection_cuts::time_min;
    const Double_t timeMax     = selection_cuts::time_max;
    const Double_t timeErrMax  = selection_cuts::timeErr_max;
    const Double_t massMinPhys = selection_cuts::mass_min;
    const Double_t massMaxPhys = massMinBd;
};

namespace sPlot_cuts {
    const Double_t templates_massMin = 4.5;
    const Double_t templates_massMax = 6.7;
    const Double_t data_massMin = 5.0;
    const Double_t data_massMax = 5.8;
    const Double_t timeMin = selection_cuts::time_min;
    const Double_t timeMax = selection_cuts::time_max;
    const Double_t timeErrMax = selection_cuts::timeErr_max;
}
#endif