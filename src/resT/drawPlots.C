#include <iostream>
#include "resolution.C"
using namespace std;

int main(){
  
  resolution("Jpsi_MC_2018", {"$storage_Jpsi_MC/Jpsi_MC_2018_MagUp_reduced_test.root/ntp", "$storage_Jpsi_MC/Jpsi_MC_2018_MagDw_reduced_test.root/ntp"});
  //resolution("Jpsi_data_2018_sw", {"../sWeights/plots/Jpsi_data_2018_gausBKG.root/merged"});
  //resolution("data_2015_Jpsi_sw", {"../sWeights/plots/Jpsi_data_2015_gausBKG.root/merged"});
  //  resolution("data_2016_Jpsi_sw", {"../sWeights/plots/Jpsi_data_2016_gausBKG.root/merged"});
  //  resolution("data_2017_Jpsi_sw", {"../sWeights/plots/Jpsi_data_2017_gausBKG.root/merged"});
  //  resolution("data_2018_Jpsi_sw", {"../sWeights/plots/Jpsi_data_2018_gausBKG.root/merged"});

  return 1;
}
