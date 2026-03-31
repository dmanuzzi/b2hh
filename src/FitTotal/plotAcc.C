// plot_spline_from_fitresult.cpp

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cstdlib>

#include "TFile.h"
#include "TCanvas.h"
#include "TObject.h"

#include "RooFitResult.h"
#include "RooArgList.h"
#include "RooAbsArg.h"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooPlot.h"

#include "RooCubicSplineFun.h"

static std::vector<double> parseKnots(const std::string& text) {
    std::vector<double> knots;
    std::stringstream ss(text);
    std::string item;

    while (std::getline(ss, item, ',')) {
        if (!item.empty()) {
            knots.push_back(std::atof(item.c_str()));
        }
    }
    return knots;
}

static RooFitResult* getFitResult(TFile* f, const std::string& name) {
    if (!f) {
        throw std::runtime_error("Null TFile pointer");
    }

    TObject* obj = f->Get(name.c_str());
    if (!obj) {
        throw std::runtime_error(
            "Object '" + name + "' not found in file '" + std::string(f->GetName()) + "'"
        );
    }

    RooFitResult* fitres = dynamic_cast<RooFitResult*>(obj);
    if (!fitres) {
        throw std::runtime_error("Object '" + name + "' is not a RooFitResult");
    }

    return fitres;
}

static RooArgList buildCoeffListFromNamedParameters(
    RooFitResult* fitres,
    const std::string& prefix,
    int nCoeffs
) {
    RooArgList coeffs;
    const RooArgList& pars = fitres->floatParsFinal();

    for (int i = 0; i < nCoeffs; ++i) {
        std::ostringstream pname;
        pname << prefix << i;

        RooAbsArg* arg = pars.find(pname.str().c_str());
        if (!arg) {
            throw std::runtime_error(
                "Parameter '" + pname.str() + "' not found in RooFitResult::floatParsFinal()"
            );
        }

        coeffs.add(*arg);
    }

    return coeffs;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr
            << "Usage:\n"
            << "  " << argv[0]
            << " input.root knot1,knot2,... [fitResultName] [xname] [output.png]\n\n"
            << "Example:\n"
            << "  " << argv[0]
            << " myfit.root 0.3,0.6,0.9,1.2,1.5,1.8,2.1,2.4,2.7,3.0,3.3,3.6,3.9,4.2,4.5,4.8,5.1"
            << " fitResult time spline.png\n";
        return 1;
    }

    const std::string inputFile     = argv[1];
    const std::string knotString    = argv[2];
    const std::string fitResultName = (argc > 3) ? argv[3] : "fitResult";
    const std::string xName         = (argc > 4) ? argv[4] : "x";
    const std::string outputName    = (argc > 5) ? argv[5] : "roo_cubic_spline.png";

    const std::string coeffPrefix = "bskk_accTimeT_201516_smoothed_bin_";
    const int nCoeffs = 19;  // bins 0...18

    std::vector<double> knots = parseKnots(knotString);
    if (knots.size() + 2 != (std::size_t)nCoeffs) {
        std::cerr
            << "Error: RooCubicSplineFun requires nCoeff = nKnots + 2.\n"
            << "You provided " << knots.size() << " knots, but there are "
            << nCoeffs << " coefficients.\n"
            << "Expected " << (nCoeffs - 2) << " knots.\n";
        return 1;
    }

    const double xmin = knots.front();
    const double xmax = knots.back();

    try {
        TFile* f = TFile::Open(inputFile.c_str(), "READ");
        if (!f || f->IsZombie()) {
            throw std::runtime_error("Cannot open file '" + inputFile + "'");
        }

        RooFitResult* fitres = getFitResult(f, fitResultName);

        // Build coefficient list in the required spline order:
        // bskk_accTimeT_201516_smoothed_bin_0 ... _18
        RooArgList coeffs = buildCoeffListFromNamedParameters(
            fitres, coeffPrefix, nCoeffs
        );

        RooRealVar x(xName.c_str(), xName.c_str(), xmin, xmax);

        RooCubicSplineFun spline(
            "cubicSpline",
            "RooCubicSplineFun from RooFitResult coefficients",
            x,
            knots,
            coeffs
        );

        RooPlot* frame = x.frame();
        frame->SetTitle("RooCubicSplineFun from RooFitResult");
        spline.plotOn(frame);

        TCanvas c("c", "c", 800, 600);
        frame->Draw();
        c.SaveAs(outputName.c_str());

        std::cout << "Saved plot to: " << outputName << std::endl;
        std::cout << "Coefficients used:" << std::endl;
        for (int i = 0; i < coeffs.getSize(); ++i) {
            RooAbsReal* p = dynamic_cast<RooAbsReal*>(coeffs.at(i));
            if (p) {
                std::cout << "  [" << i << "] "
                          << p->GetName() << " = "
                          << p->getVal() << std::endl;
            }
        }

        f->Close();
        delete f;
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 2;
    }

    return 0;
}
