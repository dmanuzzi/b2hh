//after optim has finished running sort the best expected significances



#include <vector>
#include <algorithm>
#include <iostream>
#include "TString.h"

void bestBDTSorter() {

    std::vector<double> bestBDTvalues;
    std::vector<double> bestCuts;
    std::vector<TString> bdtNames; // same as bdtlist but acts as consistency check


    std::vector<TString> bdtlist = {
        "bdtgradient_300_3", "bdtgradient_300_4", "bdtgradient_300_5", "bdtgradient_300_6",
        "bdtgradient_400_3", "bdtgradient_400_4", "bdtgradient_400_5", "bdtgradient_400_6",
        "bdtgradient_500_3", "bdtgradient_500_4", "bdtgradient_500_5", "bdtgradient_500_6",
        "bdtgradient_600_3", "bdtgradient_600_4", "bdtgradient_600_5", "bdtgradient_600_6",
        "bdtgradient_700_3", "bdtgradient_700_4", "bdtgradient_700_5", "bdtgradient_700_6"
    };

    const char* basePath = getenv("B2HH_OUT");
    
    for(TString testedBDT : bdtlist) {
        std::ifstream textfile(Form("%s/newBDTtrain/BDToptim/bestSignificances/%s_significance.txt", basePath, testedBDT.Data()));
        if (!textfile.is_open()) {
            std::cerr << "Error opening file: " << Form("%s/newBDTtrain/BDToptim/bestSignificances/%s_significance.txt", basePath, testedBDT.Data()) << std::endl;
            continue;
        }

        double significance, cut;
        TString bdtName;
        while (textfile >> significance >> cut >> bdtName) {
            bestBDTvalues.push_back(significance);
            bestCuts.push_back(cut);
            bdtNames.push_back(bdtName);
            if (bdtName != testedBDT) {
                std::cerr << "Warning: potential mismatch in BDT name: " << bdtName << " vs " << testedBDT << std::endl;
            }
        }
    }
    
    //std::vector<double> values = {3.14, 2.71, 1.61};
    //std::vector<TString> labels = {"pi", "e", "phi"};
    //std::vector<TString> descriptions = {"circle", "natural log", "golden ratio"};

    // Step 1: Zip the data into a tuple vector
    std::vector<std::tuple<double, double, TString>> zipped;
    for (size_t i = 0; i < bestBDTvalues.size(); ++i) {
        zipped.emplace_back(bestBDTvalues[i], bestCuts[i], bdtNames[i]);
    }

    // Step 2: Sort the zipped vector by the double value in descending order
    std::sort(zipped.begin(), zipped.end(), [](const auto& a, const auto& b) {
        return std::get<0>(a) > std::get<0>(b); // descending
    });

    // Step 3: Unzip the sorted data back into the original vectors
    for (size_t i = 0; i < zipped.size(); ++i) {
        bestBDTvalues[i] = std::get<0>(zipped[i]);
        bestCuts[i] = std::get<1>(zipped[i]);
        bdtNames[i] = std::get<2>(zipped[i]);
    }

    // Output result
    std::ofstream outtextfile(Form("%s/newBDTtrain/BDToptim/bestSignificances/sorted_significances.txt", basePath));

    for (size_t i = 0; i < bestBDTvalues.size(); ++i) {
        std::cout << bestBDTvalues[i] << " - " << bestCuts[i] << " - " << bdtNames[i] << std::endl;
        outtextfile << bestBDTvalues[i] << " - " << bestCuts[i] << " - " << bdtNames[i] << std::endl;
    }
    outtextfile.close();
}
