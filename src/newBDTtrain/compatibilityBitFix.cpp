#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <iostream>

void compatibilityBitFix(TString channel="bspipi", TString year="2015", TString magnet="Up"){

    TString inputPath  = "${B2HH_OUT}/newBDTtrain/forNorm/temp";
    TString outputPath = "${B2HH_OUT}/newBDTtrain/forNorm/bitFix/";
    TString inputTreePath  = Form("%s/%s_%s_%s.root",inputPath.Data(), channel.Data(),year.Data(),magnet.Data());
    TString outputFilePath = Form("%s/%s_%s_%s.root",outputPath.Data(),channel.Data(),year.Data(),magnet.Data());

    std::cout << inputTreePath << " to " << outputFilePath << "\n";
    // Open the original ROOT file containing the TTree

    TFile *inputFile = TFile::Open(inputTreePath, "READ");

    // Get the original TTree (assumed to be named "myTree" in this example)
    TTree *inputTree = (TTree*)inputFile->Get("b2hh");

    // Create a new ROOT file for the copy
    TFile *outputFile = TFile::Open(outputFilePath, "RECREATE");

    // Enable forward compatibility bit k630 in the output file
    outputFile->SetBit(TFile::k630forwardCompatibility);
    //outputFile->SetBit(TFile::k630forwardCompatibility);

    // Copy the TTree from the input file to the output file

    inputTree->CloneTree()->Write("",TFile::kWriteDelete); // Clone the tree and write it to the new file
    //inputTree->CopyTree("bdtPIPI>0")->Write("",TFile::kWriteDelete); // Clone the tree and write it to the new file
    //check if this works-> so no need to cut afterwards
    
    // Close the files
    outputFile->Close();
    inputFile->Close();

    std::cout << "Tree written to " << outputFilePath << "\n";
}

//void testFix(){
//  copyTTreeWithForwardCompatibility("/home/ceph/mcaporal/b2hhRew/out/Data/BDTAdded","bdkpi_2015_Down.root");
//  copyTTreeWithForwardCompatibility("/home/ceph/mcaporal/b2hhRew/out/Data/BDTAdded","bdkpi_2015_Up.root");
//}