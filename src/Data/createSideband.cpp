#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <cstdlib>     // for getenv
#include <iostream>    // for std::cout, std::cerr
#include <string>

int createSideband(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " -y <year> -m <Magnet: Up|Down>\n";
        return 1;
    }

    std::string year;
    std::string magnet;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-y" || arg == "--year") {
            if (i + 1 < argc) {
                year = argv[++i];
            } else {
                std::cerr << "--year requires a value\n";
                return 1;
            }
        } else if (arg == "-m" || arg == "--magnet") {
            if (i + 1 < argc) {
                magnet = argv[++i];
                if (magnet != "Up" && magnet != "Down") {
                    std::cerr << "Magnet must be 'Up' or 'Down'\n";
                    return 1;
                }
            } else {
                std::cerr << "--magnet requires a value\n";
                return 1;
            }
        }
    }

    const char* b2hh_out = std::getenv("B2HH_OUT");
    if (!b2hh_out) {
        std::cerr << "Environment variable B2HH_OUT is not set\n";
        return 1;
    }

    TString input_filename = Form("%s/Data/tuple_merged/b2hh_%s_%s.root", b2hh_out, year.c_str(), magnet.c_str());
    TFile* input_file = TFile::Open(input_filename);
    if (!input_file || input_file->IsZombie()) {
        std::cerr << "Could not open input file: " << input_filename << "\n";
        return 1;
    }

    TTree* input_tree = (TTree*)input_file->Get("b2hh");
    if (!input_tree) {
        std::cerr << "Tree 'b2hh' not found in file.\n";
        return 1;
    }

    // Define the cut string
    TString cut = "massPIPI>5.6 && massPIPI<6.19"; //strange cutoff effects above

    // Create the output file and apply the cut
    TString output_filename = Form("%s/Data/tuple_merged/sideband_b2hh_%s_%s.root", b2hh_out, year.c_str(), magnet.c_str());
    TFile* output_file = new TFile(output_filename, "RECREATE");

    TTree* filtered_tree = input_tree->CopyTree(cut);

    // Write and close files
    output_file->cd();
    filtered_tree->Write();
    output_file->Close();
    input_file->Close();

    std::cout << "Filtered tree written to " << output_filename << "\n";
    return 0;
}
