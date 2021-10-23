#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TString.h>
#include <TTree.h>

using namespace std;

Int_t findOption(Int_t argc, Char_t * argv[], TString option) {

  for(Int_t i = 1; i<argc; i++)
   if(option==argv[i]) return i;
  return -1;

}

const Char_t * getOption(Int_t argc, Char_t * argv[], TString option, TString default_value) {

  Int_t iOption = findOption(argc,argv,option);
  if(iOption>0 && iOption < argc-1)
    return argv[iOption+1];
  return default_value.Data();

}

Bool_t getBoolOption(Int_t argc, Char_t * argv[], TString option) {

  Int_t iOption = findOption(argc,argv,option);
  if(iOption>0 && iOption < argc)
    return true;
  else
    return false;

}


void setBranchStatuses(TTree * tree, std::vector<TString> &vars) {

  tree->SetBranchStatus("*",0);
  for(auto name: vars) tree->SetBranchStatus(name,1);

}

bool sortbysec(const pair<int,int> &a, 
              const pair<int,int> &b) 
{ 
    return (a.second < b.second); 
} 