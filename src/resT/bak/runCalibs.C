#include <iostream>
#include "resolution.C"
#include "resFit.C"
using namespace std;


int runCalibs(){
  
  //////////////////////// Jpsi
  /////// 2016 MC
  //resolution("Jpsi_MC_2016", {"$storage_Jpsi_MC/Jpsi_MC_2016_MagUp_reduced.root/ntp",
  //                            "$storage_Jpsi_MC/Jpsi_MC_2016_MagDw_reduced.root/ntp"});
  // resFit("Jpsi_MC_2016", {"tuples/Jpsi_MC_2016.root/ntp"});
  // /////// 2016 data
  resolution("Jpsi_data_2016_sw", {"../sWeights/plots/Jpsi_data_2016_polBKG.root/merged"});
  // resFit("Jpsi_data_2016", {"tuples/Jpsi_data_2016_sw.root/ntp"});
  
  /////// 2017 MC
  //resolution("Jpsi_MC_2017", {"$storage_Jpsi_MC/Jpsi_MC_2017_MagUp_reduced.root/ntp",
  //                            "$storage_Jpsi_MC/Jpsi_MC_2017_MagDw_reduced.root/ntp"});
  // resFit("Jpsi_MC_2017", {"tuples/Jpsi_MC_2017.root/ntp"});
  // /////// 2017 data
  resolution("Jpsi_data_2017_sw", {"../sWeights/plots/Jpsi_data_2017_polBKG.root/merged"});
  // resFit("Jpsi_data_2017", {"tuples/Jpsi_data_2017_sw.root/ntp"});
  
  /////// 2018 MC
  //resolution("Jpsi_MC_2018", {"$storage_Jpsi_MC/Jpsi_MC_2018_MagUp_reduced.root/ntp",
  //                            "$storage_Jpsi_MC/Jpsi_MC_2018_MagDw_reduced.root/ntp"});
  // resFit("Jpsi_MC_2018", {"tuples/Jpsi_MC_2018.root/ntp"});
  // /////// 2018 data
  resolution("Jpsi_data_2018_sw", {"../sWeights/plots/Jpsi_data_2018_polBKG.root/merged"});
  //  resFit("Jpsi_data_2018", {"tuples/Jpsi_data_2018_sw.root/ntp"});
  //  resolution("Jpsi_data_2018_lowRun_sw", {"../sWeights/plots/Jpsi_data_2018_polBKG_lowRun.root/RooTreeDataStore_merged_merged"});
  //  resolution("Jpsi_data_2018_highRun_sw", {"../sWeights/plots/Jpsi_data_2018_polBKG_highRun.root/RooTreeDataStore_merged_merged"});
  
  //////////////////////// Bs2KK
  ////// 2016 MC
  // resolution("bskk_MC_2016", {"$storage_Bs2KK_MC/bskk_2016_Up.root/b2hh",
  //                             "$storage_Bs2KK_MC/bskk_2016_Down.root/b2hh"});
  resolution("bskk_MC_2016_PIDsel", {"$storage_Bs2KK_MC/bskk_2016_Up.root/b2hh",
                                     "$storage_Bs2KK_MC/bskk_2016_Down.root/b2hh"});
  // resFit("bskk_MC_2016", {"tuples/bskk_MC_2016.root/ntp"});
  resFit("bskk_MC_2016_PIDsel", {"tuples/bskk_MC_2016_PIDsel.root/ntp"});
  //// 2017 MC
  //resolution("bskk_MC_2017", {"$storage_Bs2KK_MC/bskk_2017_Up.root/b2hh",
  //"$storage_Bs2KK_MC/bskk_2017_Down.root/b2hh"});
  resolution("bskk_MC_2017_PIDsel", {"$storage_Bs2KK_MC/bskk_2017_Up.root/b2hh",
                                     "$storage_Bs2KK_MC/bskk_2017_Down.root/b2hh"});
  //resFit("bskk_MC_2017", {"tuples/bskk_MC_2017.root/ntp"});
  resFit("bskk_MC_2017_PIDsel", {"tuples/bskk_MC_2017_PIDsel.root/ntp"});
  //// 2018 MC
  //  resolution("bskk_MC_2018", {"$storage_Bs2KK_MC/bskk_2018_Up.root/b2hh",
  //"$storage_Bs2KK_MC/bskk_2018_Down.root/b2hh"});
  resolution("bskk_MC_2018_PIDsel", {"$storage_Bs2KK_MC/bskk_2018_Up.root/b2hh",
                                     "$storage_Bs2KK_MC/bskk_2018_Down.root/b2hh"});
  /// resFit("bskk_MC_2018", {"tuples/bskk_MC_2018.root/ntp"});
  resFit("bskk_MC_2018_PIDsel", {"tuples/bskk_MC_2018_PIDsel.root/ntp"});
    

  //////////////////////// Y1S
  /////// 2016 MC
  // resolution("Y1S_MC_2016", {"$storage_Y1S_MC/Y1S_MC_2016_MagUp_reduced.root/ntp",
  //                            "$storage_Y1S_MC/Y1S_MC_2016_MagDw_reduced.root/ntp"});
  // resFit("Y1S_MC_2016_pol2", {"tuples/Y1S_MC_2016.root/ntp"});
  // /////// 2016 data
  //resolution("Y1S_data_2016_sw", {"../sWeights/plots/Y1S_data_2016.root/merged"});
  //  resFit("Y1S_data_2016_pol3", {"tuples/Y1S_data_2016_sw.root/ntp"});
  
  /////// 2017 MC
  // resolution("Y1S_MC_2017", {"$storage_Y1S_MC/Y1S_MC_2017_MagUp_reduced.root/ntp",
  //                             "$storage_Y1S_MC/Y1S_MC_2017_MagDw_reduced.root/ntp"});
  // resFit("Y1S_MC_2017", {"tuples/Y1S_MC_2017.root/ntp"});
  // /////// 2017 data
  // resolution("Y1S_data_2017_sw", {"../sWeights/plots/Y1S_data_2017.root/merged"});
  // resFit("Y1S_data_2017", {"tuples/Y1S_data_2017_sw.root/ntp"});
  
  /////// 2018 MC
  // resolution("Y1S_MC_2018", {"$storage_Y1S_MC/Y1S_MC_2018_MagUp_reduced.root/ntp",
  //                             "$storage_Y1S_MC/Y1S_MC_2018_MagDw_reduced.root/ntp"});
  // resFit("Y1S_MC_2018", {"tuples/Y1S_MC_2018.root/ntp"});
  // /////// 2018 data
  // resolution("Y1S_data_2018_sw", {"../sWeights/plots/Y1S_data_2018.root/merged"});
  // resFit("Y1S_data_2018", {"tuples/Y1S_data_2018_sw.root/ntp"});
  



  

  return 1;
}
