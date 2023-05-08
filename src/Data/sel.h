//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May 25 23:13:54 2018 by ROOT version 6.06/02
// from TTree PreSelB2HH/PreSelB2HH
// found on file: /storage/gpfs_data/local/lhcb/users/perazzini/gangadir/workspace/perazzini/LocalXML/199/6/output//b2hh.root
//////////////////////////////////////////////////////////

#ifndef sel_h
#define sel_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class sel {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   TString         fdecay;
   TString         fyear;
   TString         fmagnet;
   Int_t           findex;
// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxB0_ENDVERTEX_COV = 1;
   const Int_t kMaxB0_OWNPV_COV = 1;
   const Int_t kMaxB0_TOPPV_COV = 1;
   const Int_t kMaxpiplus_OWNPV_COV = 1;
   const Int_t kMaxpiplus_TOPPV_COV = 1;
   const Int_t kMaxpiplus_ORIVX_COV = 1;
   const Int_t kMaxpiminus_OWNPV_COV = 1;
   const Int_t kMaxpiminus_TOPPV_COV = 1;
   const Int_t kMaxpiminus_ORIVX_COV = 1;

   // Declaration of leaf types
   Double_t        B0_DOCA;
   Double_t        B0_RichPIDk;
   Double_t        B0_RichPIDp;
   Double_t        B0_MINIP;
   Double_t        B0_MINIPCHI2;
   Double_t        B0_MINIPNEXTBEST;
   Double_t        B0_MINIPCHI2NEXTBEST;
   Double_t        B0_ENDVERTEX_X;
   Double_t        B0_ENDVERTEX_Y;
   Double_t        B0_ENDVERTEX_Z;
   Double_t        B0_ENDVERTEX_XERR;
   Double_t        B0_ENDVERTEX_YERR;
   Double_t        B0_ENDVERTEX_ZERR;
   Double_t        B0_ENDVERTEX_CHI2;
   Int_t           B0_ENDVERTEX_NDOF;
   Float_t         B0_ENDVERTEX_COV_[3][3];
   Double_t        B0_OWNPV_X;
   Double_t        B0_OWNPV_Y;
   Double_t        B0_OWNPV_Z;
   Double_t        B0_OWNPV_XERR;
   Double_t        B0_OWNPV_YERR;
   Double_t        B0_OWNPV_ZERR;
   Double_t        B0_OWNPV_CHI2;
   Int_t           B0_OWNPV_NDOF;
   Float_t         B0_OWNPV_COV_[3][3];
   Double_t        B0_IP_OWNPV;
   Double_t        B0_IPCHI2_OWNPV;
   Double_t        B0_FD_OWNPV;
   Double_t        B0_FDCHI2_OWNPV;
   Double_t        B0_DIRA_OWNPV;
   Double_t        B0_TOPPV_X;
   Double_t        B0_TOPPV_Y;
   Double_t        B0_TOPPV_Z;
   Double_t        B0_TOPPV_XERR;
   Double_t        B0_TOPPV_YERR;
   Double_t        B0_TOPPV_ZERR;
   Double_t        B0_TOPPV_CHI2;
   Int_t           B0_TOPPV_NDOF;
   Float_t         B0_TOPPV_COV_[3][3];
   Double_t        B0_IP_TOPPV;
   Double_t        B0_IPCHI2_TOPPV;
   Double_t        B0_FD_TOPPV;
   Double_t        B0_FDCHI2_TOPPV;
   Double_t        B0_DIRA_TOPPV;
   Double_t        B0_P;
   Double_t        B0_PT;
   Double_t        B0_PE;
   Double_t        B0_PX;
   Double_t        B0_PY;
   Double_t        B0_PZ;
   Double_t        B0_REFPX;
   Double_t        B0_REFPY;
   Double_t        B0_REFPZ;
   Double_t        B0_MM;
   Double_t        B0_MMERR;
   Double_t        B0_M;
   Int_t           B0_ID;
   Double_t        B0_TAU;
   Double_t        B0_TAUERR;
   Double_t        B0_TAUCHI2;
   Bool_t          B0_L0Global_Dec;
   Bool_t          B0_L0Global_TIS;
   Bool_t          B0_L0Global_TOS;
   Bool_t          B0_Hlt1Global_Dec;
   Bool_t          B0_Hlt1Global_TIS;
   Bool_t          B0_Hlt1Global_TOS;
   Bool_t          B0_Hlt1Phys_Dec;
   Bool_t          B0_Hlt1Phys_TIS;
   Bool_t          B0_Hlt1Phys_TOS;
   Bool_t          B0_Hlt2Global_Dec;
   Bool_t          B0_Hlt2Global_TIS;
   Bool_t          B0_Hlt2Global_TOS;
   Bool_t          B0_Hlt2Phys_Dec;
   Bool_t          B0_Hlt2Phys_TIS;
   Bool_t          B0_Hlt2Phys_TOS;
   Bool_t          B0_L0DiMuonDecision_Dec;
   Bool_t          B0_L0DiMuonDecision_TIS;
   Bool_t          B0_L0DiMuonDecision_TOS;
   Bool_t          B0_L0ElectronDecision_Dec;
   Bool_t          B0_L0ElectronDecision_TIS;
   Bool_t          B0_L0ElectronDecision_TOS;
   Bool_t          B0_L0HadronDecision_Dec;
   Bool_t          B0_L0HadronDecision_TIS;
   Bool_t          B0_L0HadronDecision_TOS;
   Bool_t          B0_L0MuonDecision_Dec;
   Bool_t          B0_L0MuonDecision_TIS;
   Bool_t          B0_L0MuonDecision_TOS;
   Bool_t          B0_L0JetElDecision_Dec;
   Bool_t          B0_L0JetElDecision_TIS;
   Bool_t          B0_L0JetElDecision_TOS;
   Bool_t          B0_L0JetPhDecision_Dec;
   Bool_t          B0_L0JetPhDecision_TIS;
   Bool_t          B0_L0JetPhDecision_TOS;
   Bool_t          B0_L0MuonEWDecision_Dec;
   Bool_t          B0_L0MuonEWDecision_TIS;
   Bool_t          B0_L0MuonEWDecision_TOS;
   Bool_t          B0_L0PhotonDecision_Dec;
   Bool_t          B0_L0PhotonDecision_TIS;
   Bool_t          B0_L0PhotonDecision_TOS;
   Bool_t          B0_Hlt1TrackMVADecision_Dec;
   Bool_t          B0_Hlt1TrackMVADecision_TIS;
   Bool_t          B0_Hlt1TrackMVADecision_TOS;
   Bool_t          B0_Hlt1TrackMuonDecision_Dec;
   Bool_t          B0_Hlt1TrackMuonDecision_TIS;
   Bool_t          B0_Hlt1TrackMuonDecision_TOS;
   Bool_t          B0_Hlt1TwoTrackMVADecision_Dec;
   Bool_t          B0_Hlt1TwoTrackMVADecision_TIS;
   Bool_t          B0_Hlt1TwoTrackMVADecision_TOS;
   Bool_t          B0_Hlt2B2HH_B2HHDecision_Dec;
   Bool_t          B0_Hlt2B2HH_B2HHDecision_TIS;
   Bool_t          B0_Hlt2B2HH_B2HHDecision_TOS;
   Bool_t          B0_Hlt2B2HHDecision_Dec;
   Bool_t          B0_Hlt2B2HHDecision_TIS;
   Bool_t          B0_Hlt2B2HHDecision_TOS;
   Bool_t          B0_Hlt2Topo2BodyDecision_Dec;
   Bool_t          B0_Hlt2Topo2BodyDecision_TIS;
   Bool_t          B0_Hlt2Topo2BodyDecision_TOS;
   Int_t           B0_OSCharm_TAGDEC;
   Double_t        B0_OSCharm_TAGETA;
   Double_t        B0_OSCharm_CHARGE;
   Double_t        B0_OSCharm_MVAOUT;
   Int_t           B0_OSElectron_TAGDEC;
   Double_t        B0_OSElectron_TAGETA;
   Double_t        B0_OSElectron_CHARGE;
   Double_t        B0_OSElectron_MVAOUT;
   Int_t           B0_OSElectronLatest_TAGDEC;
   Double_t        B0_OSElectronLatest_TAGETA;
   Double_t        B0_OSElectronLatest_CHARGE;
   Double_t        B0_OSElectronLatest_MVAOUT;
   Int_t           B0_OSKaon_TAGDEC;
   Double_t        B0_OSKaon_TAGETA;
   Double_t        B0_OSKaon_CHARGE;
   Double_t        B0_OSKaon_MVAOUT;
   Int_t           B0_OSKaonLatest_TAGDEC;
   Double_t        B0_OSKaonLatest_TAGETA;
   Double_t        B0_OSKaonLatest_CHARGE;
   Double_t        B0_OSKaonLatest_MVAOUT;
   Int_t           B0_OSMuon_TAGDEC;
   Double_t        B0_OSMuon_TAGETA;
   Double_t        B0_OSMuon_CHARGE;
   Double_t        B0_OSMuon_MVAOUT;
   Int_t           B0_OSMuonLatest_TAGDEC;
   Double_t        B0_OSMuonLatest_TAGETA;
   Double_t        B0_OSMuonLatest_CHARGE;
   Double_t        B0_OSMuonLatest_MVAOUT;
   Int_t           B0_OSVtxCh_TAGDEC;
   Double_t        B0_OSVtxCh_TAGETA;
   Double_t        B0_OSVtxCh_CHARGE;
   Double_t        B0_OSVtxCh_MVAOUT;
   Int_t           B0_SSKaon_TAGDEC;
   Double_t        B0_SSKaon_TAGETA;
   Double_t        B0_SSKaon_CHARGE;
   Double_t        B0_SSKaon_MVAOUT;
   Int_t           B0_SSKaonLatest_TAGDEC;
   Double_t        B0_SSKaonLatest_TAGETA;
   Double_t        B0_SSKaonLatest_CHARGE;
   Double_t        B0_SSKaonLatest_MVAOUT;
   Int_t           B0_SSPion_TAGDEC;
   Double_t        B0_SSPion_TAGETA;
   Double_t        B0_SSPion_CHARGE;
   Double_t        B0_SSPion_MVAOUT;
   Int_t           B0_SSProton_TAGDEC;
   Double_t        B0_SSProton_TAGETA;
   Double_t        B0_SSProton_CHARGE;
   Double_t        B0_SSProton_MVAOUT;
   Int_t           B0_MKK_nPV;
   Float_t         B0_MKK_M[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_MERR[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_P[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_PERR[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_PV_X[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_PV_Y[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_PV_Z[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_PV_key[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_chi2[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_ctau[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_ctauErr[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_decayLength[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_decayLengthErr[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_nDOF[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_nIter[100];   //[B0_MKK_nPV]
   Float_t         B0_MKK_status[100];   //[B0_MKK_nPV]
   Int_t           B0_MKP_nPV;
   Float_t         B0_MKP_M[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_MERR[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_P[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_PERR[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_PV_X[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_PV_Y[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_PV_Z[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_PV_key[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_chi2[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_ctau[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_ctauErr[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_decayLength[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_decayLengthErr[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_nDOF[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_nIter[100];   //[B0_MKP_nPV]
   Float_t         B0_MKP_status[100];   //[B0_MKP_nPV]
   Int_t           B0_MKPi_nPV;
   Float_t         B0_MKPi_M[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_MERR[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_P[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_PERR[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_PV_X[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_PV_Y[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_PV_Z[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_PV_key[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_chi2[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_ctau[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_ctauErr[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_decayLength[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_decayLengthErr[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_nDOF[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_nIter[100];   //[B0_MKPi_nPV]
   Float_t         B0_MKPi_status[100];   //[B0_MKPi_nPV]
   Int_t           B0_MPK_nPV;
   Float_t         B0_MPK_M[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_MERR[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_P[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_PERR[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_PV_X[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_PV_Y[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_PV_Z[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_PV_key[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_chi2[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_ctau[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_ctauErr[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_decayLength[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_decayLengthErr[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_nDOF[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_nIter[100];   //[B0_MPK_nPV]
   Float_t         B0_MPK_status[100];   //[B0_MPK_nPV]
   Int_t           B0_MPPi_nPV;
   Float_t         B0_MPPi_M[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_MERR[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_P[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_PERR[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_PV_X[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_PV_Y[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_PV_Z[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_PV_key[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_chi2[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_ctau[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_ctauErr[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_decayLength[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_decayLengthErr[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_nDOF[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_nIter[100];   //[B0_MPPi_nPV]
   Float_t         B0_MPPi_status[100];   //[B0_MPPi_nPV]
   Int_t           B0_MPiK_nPV;
   Float_t         B0_MPiK_M[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_MERR[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_P[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_PERR[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_PV_X[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_PV_Y[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_PV_Z[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_PV_key[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_chi2[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_ctau[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_ctauErr[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_decayLength[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_decayLengthErr[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_nDOF[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_nIter[100];   //[B0_MPiK_nPV]
   Float_t         B0_MPiK_status[100];   //[B0_MPiK_nPV]
   Int_t           B0_MPiP_nPV;
   Float_t         B0_MPiP_M[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_MERR[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_P[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_PERR[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_PV_X[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_PV_Y[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_PV_Z[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_PV_key[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_chi2[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_ctau[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_ctauErr[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_decayLength[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_decayLengthErr[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_nDOF[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_nIter[100];   //[B0_MPiP_nPV]
   Float_t         B0_MPiP_status[100];   //[B0_MPiP_nPV]
   Int_t           B0_MPiPi_nPV;
   Float_t         B0_MPiPi_M[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_MERR[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_P[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_PERR[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_PV_X[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_PV_Y[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_PV_Z[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_PV_key[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_chi2[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_ctau[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_ctauErr[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_decayLength[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_decayLengthErr[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_nDOF[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_nIter[100];   //[B0_MPiPi_nPV]
   Float_t         B0_MPiPi_status[100];   //[B0_MPiPi_nPV]
   Double_t        piplus_DOCA;
   Double_t        piplus_RichPIDk;
   Double_t        piplus_RichPIDp;
   Double_t        piplus_MC12TuneV2_ProbNNe;
   Double_t        piplus_MC12TuneV2_ProbNNmu;
   Double_t        piplus_MC12TuneV2_ProbNNpi;
   Double_t        piplus_MC12TuneV2_ProbNNk;
   Double_t        piplus_MC12TuneV2_ProbNNp;
   Double_t        piplus_MC12TuneV2_ProbNNghost;
   Double_t        piplus_MC12TuneV3_ProbNNe;
   Double_t        piplus_MC12TuneV3_ProbNNmu;
   Double_t        piplus_MC12TuneV3_ProbNNpi;
   Double_t        piplus_MC12TuneV3_ProbNNk;
   Double_t        piplus_MC12TuneV3_ProbNNp;
   Double_t        piplus_MC12TuneV3_ProbNNghost;
   Double_t        piplus_MC12TuneV4_ProbNNe;
   Double_t        piplus_MC12TuneV4_ProbNNmu;
   Double_t        piplus_MC12TuneV4_ProbNNpi;
   Double_t        piplus_MC12TuneV4_ProbNNk;
   Double_t        piplus_MC12TuneV4_ProbNNp;
   Double_t        piplus_MC12TuneV4_ProbNNghost;
   Double_t        piplus_MC15TuneV1_ProbNNe;
   Double_t        piplus_MC15TuneV1_ProbNNmu;
   Double_t        piplus_MC15TuneV1_ProbNNpi;
   Double_t        piplus_MC15TuneV1_ProbNNk;
   Double_t        piplus_MC15TuneV1_ProbNNp;
   Double_t        piplus_MC15TuneV1_ProbNNghost;
   Double_t        piplus_MINIP;
   Double_t        piplus_MINIPCHI2;
   Double_t        piplus_MINIPNEXTBEST;
   Double_t        piplus_MINIPCHI2NEXTBEST;
   Double_t        piplus_OWNPV_X;
   Double_t        piplus_OWNPV_Y;
   Double_t        piplus_OWNPV_Z;
   Double_t        piplus_OWNPV_XERR;
   Double_t        piplus_OWNPV_YERR;
   Double_t        piplus_OWNPV_ZERR;
   Double_t        piplus_OWNPV_CHI2;
   Int_t           piplus_OWNPV_NDOF;
   Float_t         piplus_OWNPV_COV_[3][3];
   Double_t        piplus_IP_OWNPV;
   Double_t        piplus_IPCHI2_OWNPV;
   Double_t        piplus_TOPPV_X;
   Double_t        piplus_TOPPV_Y;
   Double_t        piplus_TOPPV_Z;
   Double_t        piplus_TOPPV_XERR;
   Double_t        piplus_TOPPV_YERR;
   Double_t        piplus_TOPPV_ZERR;
   Double_t        piplus_TOPPV_CHI2;
   Int_t           piplus_TOPPV_NDOF;
   Float_t         piplus_TOPPV_COV_[3][3];
   Double_t        piplus_IP_TOPPV;
   Double_t        piplus_IPCHI2_TOPPV;
   Double_t        piplus_ORIVX_X;
   Double_t        piplus_ORIVX_Y;
   Double_t        piplus_ORIVX_Z;
   Double_t        piplus_ORIVX_XERR;
   Double_t        piplus_ORIVX_YERR;
   Double_t        piplus_ORIVX_ZERR;
   Double_t        piplus_ORIVX_CHI2;
   Int_t           piplus_ORIVX_NDOF;
   Float_t         piplus_ORIVX_COV_[3][3];
   Double_t        piplus_IP_ORIVX;
   Double_t        piplus_IPCHI2_ORIVX;
   Double_t        piplus_P;
   Double_t        piplus_PT;
   Double_t        piplus_PE;
   Double_t        piplus_PX;
   Double_t        piplus_PY;
   Double_t        piplus_PZ;
   Double_t        piplus_REFPX;
   Double_t        piplus_REFPY;
   Double_t        piplus_REFPZ;
   Double_t        piplus_M;
   Double_t        piplus_AtVtx_PE;
   Double_t        piplus_AtVtx_PX;
   Double_t        piplus_AtVtx_PY;
   Double_t        piplus_AtVtx_PZ;
   Int_t           piplus_ID;
   Double_t        piplus_PIDe;
   Double_t        piplus_PIDmu;
   Double_t        piplus_PIDK;
   Double_t        piplus_PIDp;
   Double_t        piplus_ProbNNe;
   Double_t        piplus_ProbNNk;
   Double_t        piplus_ProbNNp;
   Double_t        piplus_ProbNNpi;
   Double_t        piplus_ProbNNmu;
   Double_t        piplus_ProbNNghost;
   Bool_t          piplus_hasMuon;
   Bool_t          piplus_isMuon;
   Bool_t          piplus_hasRich;
   Bool_t          piplus_UsedRichAerogel;
   Bool_t          piplus_UsedRich1Gas;
   Bool_t          piplus_UsedRich2Gas;
   Bool_t          piplus_RichAboveElThres;
   Bool_t          piplus_RichAboveMuThres;
   Bool_t          piplus_RichAbovePiThres;
   Bool_t          piplus_RichAboveKaThres;
   Bool_t          piplus_RichAbovePrThres;
   Bool_t          piplus_hasCalo;
   Bool_t          piplus_L0Global_Dec;
   Bool_t          piplus_L0Global_TIS;
   Bool_t          piplus_L0Global_TOS;
   Bool_t          piplus_Hlt1Global_Dec;
   Bool_t          piplus_Hlt1Global_TIS;
   Bool_t          piplus_Hlt1Global_TOS;
   Bool_t          piplus_Hlt1Phys_Dec;
   Bool_t          piplus_Hlt1Phys_TIS;
   Bool_t          piplus_Hlt1Phys_TOS;
   Bool_t          piplus_Hlt2Global_Dec;
   Bool_t          piplus_Hlt2Global_TIS;
   Bool_t          piplus_Hlt2Global_TOS;
   Bool_t          piplus_Hlt2Phys_Dec;
   Bool_t          piplus_Hlt2Phys_TIS;
   Bool_t          piplus_Hlt2Phys_TOS;
   Bool_t          piplus_L0DiMuonDecision_Dec;
   Bool_t          piplus_L0DiMuonDecision_TIS;
   Bool_t          piplus_L0DiMuonDecision_TOS;
   Bool_t          piplus_L0ElectronDecision_Dec;
   Bool_t          piplus_L0ElectronDecision_TIS;
   Bool_t          piplus_L0ElectronDecision_TOS;
   Bool_t          piplus_L0HadronDecision_Dec;
   Bool_t          piplus_L0HadronDecision_TIS;
   Bool_t          piplus_L0HadronDecision_TOS;
   Bool_t          piplus_L0MuonDecision_Dec;
   Bool_t          piplus_L0MuonDecision_TIS;
   Bool_t          piplus_L0MuonDecision_TOS;
   Bool_t          piplus_L0JetElDecision_Dec;
   Bool_t          piplus_L0JetElDecision_TIS;
   Bool_t          piplus_L0JetElDecision_TOS;
   Bool_t          piplus_L0JetPhDecision_Dec;
   Bool_t          piplus_L0JetPhDecision_TIS;
   Bool_t          piplus_L0JetPhDecision_TOS;
   Bool_t          piplus_L0MuonEWDecision_Dec;
   Bool_t          piplus_L0MuonEWDecision_TIS;
   Bool_t          piplus_L0MuonEWDecision_TOS;
   Bool_t          piplus_L0PhotonDecision_Dec;
   Bool_t          piplus_L0PhotonDecision_TIS;
   Bool_t          piplus_L0PhotonDecision_TOS;
   Bool_t          piplus_Hlt1TrackMVADecision_Dec;
   Bool_t          piplus_Hlt1TrackMVADecision_TIS;
   Bool_t          piplus_Hlt1TrackMVADecision_TOS;
   Bool_t          piplus_Hlt1TrackMuonDecision_Dec;
   Bool_t          piplus_Hlt1TrackMuonDecision_TIS;
   Bool_t          piplus_Hlt1TrackMuonDecision_TOS;
   Bool_t          piplus_Hlt1TwoTrackMVADecision_Dec;
   Bool_t          piplus_Hlt1TwoTrackMVADecision_TIS;
   Bool_t          piplus_Hlt1TwoTrackMVADecision_TOS;
   Bool_t          piplus_Hlt2B2HH_B2HHDecision_Dec;
   Bool_t          piplus_Hlt2B2HH_B2HHDecision_TIS;
   Bool_t          piplus_Hlt2B2HH_B2HHDecision_TOS;
   Bool_t          piplus_Hlt2B2HHDecision_Dec;
   Bool_t          piplus_Hlt2B2HHDecision_TIS;
   Bool_t          piplus_Hlt2B2HHDecision_TOS;
   Bool_t          piplus_Hlt2Topo2BodyDecision_Dec;
   Bool_t          piplus_Hlt2Topo2BodyDecision_TIS;
   Bool_t          piplus_Hlt2Topo2BodyDecision_TOS;
   Int_t           piplus_TRACK_Type;
   Int_t           piplus_TRACK_Key;
   Double_t        piplus_TRACK_CHI2NDOF;
   Double_t        piplus_TRACK_PCHI2;
   Double_t        piplus_TRACK_MatchCHI2;
   Double_t        piplus_TRACK_GhostProb;
   Double_t        piplus_TRACK_CloneDist;
   Double_t        piplus_TRACK_Likelihood;
   Double_t        piminus_DOCA;
   Double_t        piminus_RichPIDk;
   Double_t        piminus_RichPIDp;
   Double_t        piminus_MC12TuneV2_ProbNNe;
   Double_t        piminus_MC12TuneV2_ProbNNmu;
   Double_t        piminus_MC12TuneV2_ProbNNpi;
   Double_t        piminus_MC12TuneV2_ProbNNk;
   Double_t        piminus_MC12TuneV2_ProbNNp;
   Double_t        piminus_MC12TuneV2_ProbNNghost;
   Double_t        piminus_MC12TuneV3_ProbNNe;
   Double_t        piminus_MC12TuneV3_ProbNNmu;
   Double_t        piminus_MC12TuneV3_ProbNNpi;
   Double_t        piminus_MC12TuneV3_ProbNNk;
   Double_t        piminus_MC12TuneV3_ProbNNp;
   Double_t        piminus_MC12TuneV3_ProbNNghost;
   Double_t        piminus_MC12TuneV4_ProbNNe;
   Double_t        piminus_MC12TuneV4_ProbNNmu;
   Double_t        piminus_MC12TuneV4_ProbNNpi;
   Double_t        piminus_MC12TuneV4_ProbNNk;
   Double_t        piminus_MC12TuneV4_ProbNNp;
   Double_t        piminus_MC12TuneV4_ProbNNghost;
   Double_t        piminus_MC15TuneV1_ProbNNe;
   Double_t        piminus_MC15TuneV1_ProbNNmu;
   Double_t        piminus_MC15TuneV1_ProbNNpi;
   Double_t        piminus_MC15TuneV1_ProbNNk;
   Double_t        piminus_MC15TuneV1_ProbNNp;
   Double_t        piminus_MC15TuneV1_ProbNNghost;
   Double_t        piminus_MINIP;
   Double_t        piminus_MINIPCHI2;
   Double_t        piminus_MINIPNEXTBEST;
   Double_t        piminus_MINIPCHI2NEXTBEST;
   Double_t        piminus_OWNPV_X;
   Double_t        piminus_OWNPV_Y;
   Double_t        piminus_OWNPV_Z;
   Double_t        piminus_OWNPV_XERR;
   Double_t        piminus_OWNPV_YERR;
   Double_t        piminus_OWNPV_ZERR;
   Double_t        piminus_OWNPV_CHI2;
   Int_t           piminus_OWNPV_NDOF;
   Float_t         piminus_OWNPV_COV_[3][3];
   Double_t        piminus_IP_OWNPV;
   Double_t        piminus_IPCHI2_OWNPV;
   Double_t        piminus_TOPPV_X;
   Double_t        piminus_TOPPV_Y;
   Double_t        piminus_TOPPV_Z;
   Double_t        piminus_TOPPV_XERR;
   Double_t        piminus_TOPPV_YERR;
   Double_t        piminus_TOPPV_ZERR;
   Double_t        piminus_TOPPV_CHI2;
   Int_t           piminus_TOPPV_NDOF;
   Float_t         piminus_TOPPV_COV_[3][3];
   Double_t        piminus_IP_TOPPV;
   Double_t        piminus_IPCHI2_TOPPV;
   Double_t        piminus_ORIVX_X;
   Double_t        piminus_ORIVX_Y;
   Double_t        piminus_ORIVX_Z;
   Double_t        piminus_ORIVX_XERR;
   Double_t        piminus_ORIVX_YERR;
   Double_t        piminus_ORIVX_ZERR;
   Double_t        piminus_ORIVX_CHI2;
   Int_t           piminus_ORIVX_NDOF;
   Float_t         piminus_ORIVX_COV_[3][3];
   Double_t        piminus_IP_ORIVX;
   Double_t        piminus_IPCHI2_ORIVX;
   Double_t        piminus_P;
   Double_t        piminus_PT;
   Double_t        piminus_PE;
   Double_t        piminus_PX;
   Double_t        piminus_PY;
   Double_t        piminus_PZ;
   Double_t        piminus_REFPX;
   Double_t        piminus_REFPY;
   Double_t        piminus_REFPZ;
   Double_t        piminus_M;
   Double_t        piminus_AtVtx_PE;
   Double_t        piminus_AtVtx_PX;
   Double_t        piminus_AtVtx_PY;
   Double_t        piminus_AtVtx_PZ;
   Int_t           piminus_ID;
   Double_t        piminus_PIDe;
   Double_t        piminus_PIDmu;
   Double_t        piminus_PIDK;
   Double_t        piminus_PIDp;
   Double_t        piminus_ProbNNe;
   Double_t        piminus_ProbNNk;
   Double_t        piminus_ProbNNp;
   Double_t        piminus_ProbNNpi;
   Double_t        piminus_ProbNNmu;
   Double_t        piminus_ProbNNghost;
   Bool_t          piminus_hasMuon;
   Bool_t          piminus_isMuon;
   Bool_t          piminus_hasRich;
   Bool_t          piminus_UsedRichAerogel;
   Bool_t          piminus_UsedRich1Gas;
   Bool_t          piminus_UsedRich2Gas;
   Bool_t          piminus_RichAboveElThres;
   Bool_t          piminus_RichAboveMuThres;
   Bool_t          piminus_RichAbovePiThres;
   Bool_t          piminus_RichAboveKaThres;
   Bool_t          piminus_RichAbovePrThres;
   Bool_t          piminus_hasCalo;
   Bool_t          piminus_L0Global_Dec;
   Bool_t          piminus_L0Global_TIS;
   Bool_t          piminus_L0Global_TOS;
   Bool_t          piminus_Hlt1Global_Dec;
   Bool_t          piminus_Hlt1Global_TIS;
   Bool_t          piminus_Hlt1Global_TOS;
   Bool_t          piminus_Hlt1Phys_Dec;
   Bool_t          piminus_Hlt1Phys_TIS;
   Bool_t          piminus_Hlt1Phys_TOS;
   Bool_t          piminus_Hlt2Global_Dec;
   Bool_t          piminus_Hlt2Global_TIS;
   Bool_t          piminus_Hlt2Global_TOS;
   Bool_t          piminus_Hlt2Phys_Dec;
   Bool_t          piminus_Hlt2Phys_TIS;
   Bool_t          piminus_Hlt2Phys_TOS;
   Bool_t          piminus_L0DiMuonDecision_Dec;
   Bool_t          piminus_L0DiMuonDecision_TIS;
   Bool_t          piminus_L0DiMuonDecision_TOS;
   Bool_t          piminus_L0ElectronDecision_Dec;
   Bool_t          piminus_L0ElectronDecision_TIS;
   Bool_t          piminus_L0ElectronDecision_TOS;
   Bool_t          piminus_L0HadronDecision_Dec;
   Bool_t          piminus_L0HadronDecision_TIS;
   Bool_t          piminus_L0HadronDecision_TOS;
   Bool_t          piminus_L0MuonDecision_Dec;
   Bool_t          piminus_L0MuonDecision_TIS;
   Bool_t          piminus_L0MuonDecision_TOS;
   Bool_t          piminus_L0JetElDecision_Dec;
   Bool_t          piminus_L0JetElDecision_TIS;
   Bool_t          piminus_L0JetElDecision_TOS;
   Bool_t          piminus_L0JetPhDecision_Dec;
   Bool_t          piminus_L0JetPhDecision_TIS;
   Bool_t          piminus_L0JetPhDecision_TOS;
   Bool_t          piminus_L0MuonEWDecision_Dec;
   Bool_t          piminus_L0MuonEWDecision_TIS;
   Bool_t          piminus_L0MuonEWDecision_TOS;
   Bool_t          piminus_L0PhotonDecision_Dec;
   Bool_t          piminus_L0PhotonDecision_TIS;
   Bool_t          piminus_L0PhotonDecision_TOS;
   Bool_t          piminus_Hlt1TrackMVADecision_Dec;
   Bool_t          piminus_Hlt1TrackMVADecision_TIS;
   Bool_t          piminus_Hlt1TrackMVADecision_TOS;
   Bool_t          piminus_Hlt1TrackMuonDecision_Dec;
   Bool_t          piminus_Hlt1TrackMuonDecision_TIS;
   Bool_t          piminus_Hlt1TrackMuonDecision_TOS;
   Bool_t          piminus_Hlt1TwoTrackMVADecision_Dec;
   Bool_t          piminus_Hlt1TwoTrackMVADecision_TIS;
   Bool_t          piminus_Hlt1TwoTrackMVADecision_TOS;
   Bool_t          piminus_Hlt2B2HH_B2HHDecision_Dec;
   Bool_t          piminus_Hlt2B2HH_B2HHDecision_TIS;
   Bool_t          piminus_Hlt2B2HH_B2HHDecision_TOS;
   Bool_t          piminus_Hlt2B2HHDecision_Dec;
   Bool_t          piminus_Hlt2B2HHDecision_TIS;
   Bool_t          piminus_Hlt2B2HHDecision_TOS;
   Bool_t          piminus_Hlt2Topo2BodyDecision_Dec;
   Bool_t          piminus_Hlt2Topo2BodyDecision_TIS;
   Bool_t          piminus_Hlt2Topo2BodyDecision_TOS;
   Int_t           piminus_TRACK_Type;
   Int_t           piminus_TRACK_Key;
   Double_t        piminus_TRACK_CHI2NDOF;
   Double_t        piminus_TRACK_PCHI2;
   Double_t        piminus_TRACK_MatchCHI2;
   Double_t        piminus_TRACK_GhostProb;
   Double_t        piminus_TRACK_CloneDist;
   Double_t        piminus_TRACK_Likelihood;
   UInt_t          nCandidate;
   ULong64_t       totCandidates;
   ULong64_t       EventInSequence;
   UInt_t          runNumber;
   ULong64_t       eventNumber;
   UInt_t          BCID;
   Int_t           BCType;
   UInt_t          OdinTCK;
   UInt_t          L0DUTCK;
   UInt_t          HLT1TCK;
   UInt_t          HLT2TCK;
   ULong64_t       GpsTime;
   Short_t         Polarity;
   Int_t           nPV;
   Float_t         PVX[100];   //[nPV]
   Float_t         PVY[100];   //[nPV]
   Float_t         PVZ[100];   //[nPV]
   Float_t         PVXERR[100];   //[nPV]
   Float_t         PVYERR[100];   //[nPV]
   Float_t         PVZERR[100];   //[nPV]
   Float_t         PVCHI2[100];   //[nPV]
   Float_t         PVNDOF[100];   //[nPV]
   Float_t         PVNTRACKS[100];   //[nPV]
   Int_t           nPVs;
   Int_t           nTracks;
   Int_t           nLongTracks;
   Int_t           nDownstreamTracks;
   Int_t           nUpstreamTracks;
   Int_t           nVeloTracks;
   Int_t           nTTracks;
   Int_t           nBackTracks;
   Int_t           nRich1Hits;
   Int_t           nRich2Hits;
   Int_t           nVeloClusters;
   Int_t           nITClusters;
   Int_t           nTTClusters;
   Int_t           nOTClusters;
   Int_t           nSPDHits;
   Int_t           nMuonCoordsS0;
   Int_t           nMuonCoordsS1;
   Int_t           nMuonCoordsS2;
   Int_t           nMuonCoordsS3;
   Int_t           nMuonCoordsS4;
   Int_t           nMuonTracks;

   // List of branches
   TBranch        *b_B0_DOCA;   //!
   TBranch        *b_B0_RichPIDk;   //!
   TBranch        *b_B0_RichPIDp;   //!
   TBranch        *b_B0_MINIP;   //!
   TBranch        *b_B0_MINIPCHI2;   //!
   TBranch        *b_B0_MINIPNEXTBEST;   //!
   TBranch        *b_B0_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_B0_ENDVERTEX_X;   //!
   TBranch        *b_B0_ENDVERTEX_Y;   //!
   TBranch        *b_B0_ENDVERTEX_Z;   //!
   TBranch        *b_B0_ENDVERTEX_XERR;   //!
   TBranch        *b_B0_ENDVERTEX_YERR;   //!
   TBranch        *b_B0_ENDVERTEX_ZERR;   //!
   TBranch        *b_B0_ENDVERTEX_CHI2;   //!
   TBranch        *b_B0_ENDVERTEX_NDOF;   //!
   TBranch        *b_B0_ENDVERTEX_COV_;   //!
   TBranch        *b_B0_OWNPV_X;   //!
   TBranch        *b_B0_OWNPV_Y;   //!
   TBranch        *b_B0_OWNPV_Z;   //!
   TBranch        *b_B0_OWNPV_XERR;   //!
   TBranch        *b_B0_OWNPV_YERR;   //!
   TBranch        *b_B0_OWNPV_ZERR;   //!
   TBranch        *b_B0_OWNPV_CHI2;   //!
   TBranch        *b_B0_OWNPV_NDOF;   //!
   TBranch        *b_B0_OWNPV_COV_;   //!
   TBranch        *b_B0_IP_OWNPV;   //!
   TBranch        *b_B0_IPCHI2_OWNPV;   //!
   TBranch        *b_B0_FD_OWNPV;   //!
   TBranch        *b_B0_FDCHI2_OWNPV;   //!
   TBranch        *b_B0_DIRA_OWNPV;   //!
   TBranch        *b_B0_TOPPV_X;   //!
   TBranch        *b_B0_TOPPV_Y;   //!
   TBranch        *b_B0_TOPPV_Z;   //!
   TBranch        *b_B0_TOPPV_XERR;   //!
   TBranch        *b_B0_TOPPV_YERR;   //!
   TBranch        *b_B0_TOPPV_ZERR;   //!
   TBranch        *b_B0_TOPPV_CHI2;   //!
   TBranch        *b_B0_TOPPV_NDOF;   //!
   TBranch        *b_B0_TOPPV_COV_;   //!
   TBranch        *b_B0_IP_TOPPV;   //!
   TBranch        *b_B0_IPCHI2_TOPPV;   //!
   TBranch        *b_B0_FD_TOPPV;   //!
   TBranch        *b_B0_FDCHI2_TOPPV;   //!
   TBranch        *b_B0_DIRA_TOPPV;   //!
   TBranch        *b_B0_P;   //!
   TBranch        *b_B0_PT;   //!
   TBranch        *b_B0_PE;   //!
   TBranch        *b_B0_PX;   //!
   TBranch        *b_B0_PY;   //!
   TBranch        *b_B0_PZ;   //!
   TBranch        *b_B0_REFPX;   //!
   TBranch        *b_B0_REFPY;   //!
   TBranch        *b_B0_REFPZ;   //!
   TBranch        *b_B0_MM;   //!
   TBranch        *b_B0_MMERR;   //!
   TBranch        *b_B0_M;   //!
   TBranch        *b_B0_ID;   //!
   TBranch        *b_B0_TAU;   //!
   TBranch        *b_B0_TAUERR;   //!
   TBranch        *b_B0_TAUCHI2;   //!
   TBranch        *b_B0_L0Global_Dec;   //!
   TBranch        *b_B0_L0Global_TIS;   //!
   TBranch        *b_B0_L0Global_TOS;   //!
   TBranch        *b_B0_Hlt1Global_Dec;   //!
   TBranch        *b_B0_Hlt1Global_TIS;   //!
   TBranch        *b_B0_Hlt1Global_TOS;   //!
   TBranch        *b_B0_Hlt1Phys_Dec;   //!
   TBranch        *b_B0_Hlt1Phys_TIS;   //!
   TBranch        *b_B0_Hlt1Phys_TOS;   //!
   TBranch        *b_B0_Hlt2Global_Dec;   //!
   TBranch        *b_B0_Hlt2Global_TIS;   //!
   TBranch        *b_B0_Hlt2Global_TOS;   //!
   TBranch        *b_B0_Hlt2Phys_Dec;   //!
   TBranch        *b_B0_Hlt2Phys_TIS;   //!
   TBranch        *b_B0_Hlt2Phys_TOS;   //!
   TBranch        *b_B0_L0DiMuonDecision_Dec;   //!
   TBranch        *b_B0_L0DiMuonDecision_TIS;   //!
   TBranch        *b_B0_L0DiMuonDecision_TOS;   //!
   TBranch        *b_B0_L0ElectronDecision_Dec;   //!
   TBranch        *b_B0_L0ElectronDecision_TIS;   //!
   TBranch        *b_B0_L0ElectronDecision_TOS;   //!
   TBranch        *b_B0_L0HadronDecision_Dec;   //!
   TBranch        *b_B0_L0HadronDecision_TIS;   //!
   TBranch        *b_B0_L0HadronDecision_TOS;   //!
   TBranch        *b_B0_L0MuonDecision_Dec;   //!
   TBranch        *b_B0_L0MuonDecision_TIS;   //!
   TBranch        *b_B0_L0MuonDecision_TOS;   //!
   TBranch        *b_B0_L0JetElDecision_Dec;   //!
   TBranch        *b_B0_L0JetElDecision_TIS;   //!
   TBranch        *b_B0_L0JetElDecision_TOS;   //!
   TBranch        *b_B0_L0JetPhDecision_Dec;   //!
   TBranch        *b_B0_L0JetPhDecision_TIS;   //!
   TBranch        *b_B0_L0JetPhDecision_TOS;   //!
   TBranch        *b_B0_L0MuonEWDecision_Dec;   //!
   TBranch        *b_B0_L0MuonEWDecision_TIS;   //!
   TBranch        *b_B0_L0MuonEWDecision_TOS;   //!
   TBranch        *b_B0_L0PhotonDecision_Dec;   //!
   TBranch        *b_B0_L0PhotonDecision_TIS;   //!
   TBranch        *b_B0_L0PhotonDecision_TOS;   //!
   TBranch        *b_B0_Hlt1TrackMVADecision_Dec;   //!
   TBranch        *b_B0_Hlt1TrackMVADecision_TIS;   //!
   TBranch        *b_B0_Hlt1TrackMVADecision_TOS;   //!
   TBranch        *b_B0_Hlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_B0_Hlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_B0_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_B0_Hlt1TwoTrackMVADecision_Dec;   //!
   TBranch        *b_B0_Hlt1TwoTrackMVADecision_TIS;   //!
   TBranch        *b_B0_Hlt1TwoTrackMVADecision_TOS;   //!
   TBranch        *b_B0_Hlt2B2HH_B2HHDecision_Dec;   //!
   TBranch        *b_B0_Hlt2B2HH_B2HHDecision_TIS;   //!
   TBranch        *b_B0_Hlt2B2HH_B2HHDecision_TOS;   //!
   TBranch        *b_B0_Hlt2B2HHDecision_Dec;   //!
   TBranch        *b_B0_Hlt2B2HHDecision_TIS;   //!
   TBranch        *b_B0_Hlt2B2HHDecision_TOS;   //!
   TBranch        *b_B0_Hlt2Topo2BodyDecision_Dec;   //!
   TBranch        *b_B0_Hlt2Topo2BodyDecision_TIS;   //!
   TBranch        *b_B0_Hlt2Topo2BodyDecision_TOS;   //!
   TBranch        *b_B0_OSCharm_TAGDEC;   //!
   TBranch        *b_B0_OSCharm_TAGETA;   //!
   TBranch        *b_B0_OSCharm_CHARGE;   //!
   TBranch        *b_B0_OSCharm_MVAOUT;   //!
   TBranch        *b_B0_OSElectron_TAGDEC;   //!
   TBranch        *b_B0_OSElectron_TAGETA;   //!
   TBranch        *b_B0_OSElectron_CHARGE;   //!
   TBranch        *b_B0_OSElectron_MVAOUT;   //!
   TBranch        *b_B0_OSElectronLatest_TAGDEC;   //!
   TBranch        *b_B0_OSElectronLatest_TAGETA;   //!
   TBranch        *b_B0_OSElectronLatest_CHARGE;   //!
   TBranch        *b_B0_OSElectronLatest_MVAOUT;   //!
   TBranch        *b_B0_OSKaon_TAGDEC;   //!
   TBranch        *b_B0_OSKaon_TAGETA;   //!
   TBranch        *b_B0_OSKaon_CHARGE;   //!
   TBranch        *b_B0_OSKaon_MVAOUT;   //!
   TBranch        *b_B0_OSKaonLatest_TAGDEC;   //!
   TBranch        *b_B0_OSKaonLatest_TAGETA;   //!
   TBranch        *b_B0_OSKaonLatest_CHARGE;   //!
   TBranch        *b_B0_OSKaonLatest_MVAOUT;   //!
   TBranch        *b_B0_OSMuon_TAGDEC;   //!
   TBranch        *b_B0_OSMuon_TAGETA;   //!
   TBranch        *b_B0_OSMuon_CHARGE;   //!
   TBranch        *b_B0_OSMuon_MVAOUT;   //!
   TBranch        *b_B0_OSMuonLatest_TAGDEC;   //!
   TBranch        *b_B0_OSMuonLatest_TAGETA;   //!
   TBranch        *b_B0_OSMuonLatest_CHARGE;   //!
   TBranch        *b_B0_OSMuonLatest_MVAOUT;   //!
   TBranch        *b_B0_OSVtxCh_TAGDEC;   //!
   TBranch        *b_B0_OSVtxCh_TAGETA;   //!
   TBranch        *b_B0_OSVtxCh_CHARGE;   //!
   TBranch        *b_B0_OSVtxCh_MVAOUT;   //!
   TBranch        *b_B0_SSKaon_TAGDEC;   //!
   TBranch        *b_B0_SSKaon_TAGETA;   //!
   TBranch        *b_B0_SSKaon_CHARGE;   //!
   TBranch        *b_B0_SSKaon_MVAOUT;   //!
   TBranch        *b_B0_SSKaonLatest_TAGDEC;   //!
   TBranch        *b_B0_SSKaonLatest_TAGETA;   //!
   TBranch        *b_B0_SSKaonLatest_CHARGE;   //!
   TBranch        *b_B0_SSKaonLatest_MVAOUT;   //!
   TBranch        *b_B0_SSPion_TAGDEC;   //!
   TBranch        *b_B0_SSPion_TAGETA;   //!
   TBranch        *b_B0_SSPion_CHARGE;   //!
   TBranch        *b_B0_SSPion_MVAOUT;   //!
   TBranch        *b_B0_SSProton_TAGDEC;   //!
   TBranch        *b_B0_SSProton_TAGETA;   //!
   TBranch        *b_B0_SSProton_CHARGE;   //!
   TBranch        *b_B0_SSProton_MVAOUT;   //!
   TBranch        *b_B0_MKK_nPV;   //!
   TBranch        *b_B0_MKK_M;   //!
   TBranch        *b_B0_MKK_MERR;   //!
   TBranch        *b_B0_MKK_P;   //!
   TBranch        *b_B0_MKK_PERR;   //!
   TBranch        *b_B0_MKK_PV_X;   //!
   TBranch        *b_B0_MKK_PV_Y;   //!
   TBranch        *b_B0_MKK_PV_Z;   //!
   TBranch        *b_B0_MKK_PV_key;   //!
   TBranch        *b_B0_MKK_chi2;   //!
   TBranch        *b_B0_MKK_ctau;   //!
   TBranch        *b_B0_MKK_ctauErr;   //!
   TBranch        *b_B0_MKK_decayLength;   //!
   TBranch        *b_B0_MKK_decayLengthErr;   //!
   TBranch        *b_B0_MKK_nDOF;   //!
   TBranch        *b_B0_MKK_nIter;   //!
   TBranch        *b_B0_MKK_status;   //!
   TBranch        *b_B0_MKP_nPV;   //!
   TBranch        *b_B0_MKP_M;   //!
   TBranch        *b_B0_MKP_MERR;   //!
   TBranch        *b_B0_MKP_P;   //!
   TBranch        *b_B0_MKP_PERR;   //!
   TBranch        *b_B0_MKP_PV_X;   //!
   TBranch        *b_B0_MKP_PV_Y;   //!
   TBranch        *b_B0_MKP_PV_Z;   //!
   TBranch        *b_B0_MKP_PV_key;   //!
   TBranch        *b_B0_MKP_chi2;   //!
   TBranch        *b_B0_MKP_ctau;   //!
   TBranch        *b_B0_MKP_ctauErr;   //!
   TBranch        *b_B0_MKP_decayLength;   //!
   TBranch        *b_B0_MKP_decayLengthErr;   //!
   TBranch        *b_B0_MKP_nDOF;   //!
   TBranch        *b_B0_MKP_nIter;   //!
   TBranch        *b_B0_MKP_status;   //!
   TBranch        *b_B0_MKPi_nPV;   //!
   TBranch        *b_B0_MKPi_M;   //!
   TBranch        *b_B0_MKPi_MERR;   //!
   TBranch        *b_B0_MKPi_P;   //!
   TBranch        *b_B0_MKPi_PERR;   //!
   TBranch        *b_B0_MKPi_PV_X;   //!
   TBranch        *b_B0_MKPi_PV_Y;   //!
   TBranch        *b_B0_MKPi_PV_Z;   //!
   TBranch        *b_B0_MKPi_PV_key;   //!
   TBranch        *b_B0_MKPi_chi2;   //!
   TBranch        *b_B0_MKPi_ctau;   //!
   TBranch        *b_B0_MKPi_ctauErr;   //!
   TBranch        *b_B0_MKPi_decayLength;   //!
   TBranch        *b_B0_MKPi_decayLengthErr;   //!
   TBranch        *b_B0_MKPi_nDOF;   //!
   TBranch        *b_B0_MKPi_nIter;   //!
   TBranch        *b_B0_MKPi_status;   //!
   TBranch        *b_B0_MPK_nPV;   //!
   TBranch        *b_B0_MPK_M;   //!
   TBranch        *b_B0_MPK_MERR;   //!
   TBranch        *b_B0_MPK_P;   //!
   TBranch        *b_B0_MPK_PERR;   //!
   TBranch        *b_B0_MPK_PV_X;   //!
   TBranch        *b_B0_MPK_PV_Y;   //!
   TBranch        *b_B0_MPK_PV_Z;   //!
   TBranch        *b_B0_MPK_PV_key;   //!
   TBranch        *b_B0_MPK_chi2;   //!
   TBranch        *b_B0_MPK_ctau;   //!
   TBranch        *b_B0_MPK_ctauErr;   //!
   TBranch        *b_B0_MPK_decayLength;   //!
   TBranch        *b_B0_MPK_decayLengthErr;   //!
   TBranch        *b_B0_MPK_nDOF;   //!
   TBranch        *b_B0_MPK_nIter;   //!
   TBranch        *b_B0_MPK_status;   //!
   TBranch        *b_B0_MPPi_nPV;   //!
   TBranch        *b_B0_MPPi_M;   //!
   TBranch        *b_B0_MPPi_MERR;   //!
   TBranch        *b_B0_MPPi_P;   //!
   TBranch        *b_B0_MPPi_PERR;   //!
   TBranch        *b_B0_MPPi_PV_X;   //!
   TBranch        *b_B0_MPPi_PV_Y;   //!
   TBranch        *b_B0_MPPi_PV_Z;   //!
   TBranch        *b_B0_MPPi_PV_key;   //!
   TBranch        *b_B0_MPPi_chi2;   //!
   TBranch        *b_B0_MPPi_ctau;   //!
   TBranch        *b_B0_MPPi_ctauErr;   //!
   TBranch        *b_B0_MPPi_decayLength;   //!
   TBranch        *b_B0_MPPi_decayLengthErr;   //!
   TBranch        *b_B0_MPPi_nDOF;   //!
   TBranch        *b_B0_MPPi_nIter;   //!
   TBranch        *b_B0_MPPi_status;   //!
   TBranch        *b_B0_MPiK_nPV;   //!
   TBranch        *b_B0_MPiK_M;   //!
   TBranch        *b_B0_MPiK_MERR;   //!
   TBranch        *b_B0_MPiK_P;   //!
   TBranch        *b_B0_MPiK_PERR;   //!
   TBranch        *b_B0_MPiK_PV_X;   //!
   TBranch        *b_B0_MPiK_PV_Y;   //!
   TBranch        *b_B0_MPiK_PV_Z;   //!
   TBranch        *b_B0_MPiK_PV_key;   //!
   TBranch        *b_B0_MPiK_chi2;   //!
   TBranch        *b_B0_MPiK_ctau;   //!
   TBranch        *b_B0_MPiK_ctauErr;   //!
   TBranch        *b_B0_MPiK_decayLength;   //!
   TBranch        *b_B0_MPiK_decayLengthErr;   //!
   TBranch        *b_B0_MPiK_nDOF;   //!
   TBranch        *b_B0_MPiK_nIter;   //!
   TBranch        *b_B0_MPiK_status;   //!
   TBranch        *b_B0_MPiP_nPV;   //!
   TBranch        *b_B0_MPiP_M;   //!
   TBranch        *b_B0_MPiP_MERR;   //!
   TBranch        *b_B0_MPiP_P;   //!
   TBranch        *b_B0_MPiP_PERR;   //!
   TBranch        *b_B0_MPiP_PV_X;   //!
   TBranch        *b_B0_MPiP_PV_Y;   //!
   TBranch        *b_B0_MPiP_PV_Z;   //!
   TBranch        *b_B0_MPiP_PV_key;   //!
   TBranch        *b_B0_MPiP_chi2;   //!
   TBranch        *b_B0_MPiP_ctau;   //!
   TBranch        *b_B0_MPiP_ctauErr;   //!
   TBranch        *b_B0_MPiP_decayLength;   //!
   TBranch        *b_B0_MPiP_decayLengthErr;   //!
   TBranch        *b_B0_MPiP_nDOF;   //!
   TBranch        *b_B0_MPiP_nIter;   //!
   TBranch        *b_B0_MPiP_status;   //!
   TBranch        *b_B0_MPiPi_nPV;   //!
   TBranch        *b_B0_MPiPi_M;   //!
   TBranch        *b_B0_MPiPi_MERR;   //!
   TBranch        *b_B0_MPiPi_P;   //!
   TBranch        *b_B0_MPiPi_PERR;   //!
   TBranch        *b_B0_MPiPi_PV_X;   //!
   TBranch        *b_B0_MPiPi_PV_Y;   //!
   TBranch        *b_B0_MPiPi_PV_Z;   //!
   TBranch        *b_B0_MPiPi_PV_key;   //!
   TBranch        *b_B0_MPiPi_chi2;   //!
   TBranch        *b_B0_MPiPi_ctau;   //!
   TBranch        *b_B0_MPiPi_ctauErr;   //!
   TBranch        *b_B0_MPiPi_decayLength;   //!
   TBranch        *b_B0_MPiPi_decayLengthErr;   //!
   TBranch        *b_B0_MPiPi_nDOF;   //!
   TBranch        *b_B0_MPiPi_nIter;   //!
   TBranch        *b_B0_MPiPi_status;   //!
   TBranch        *b_piplus_DOCA;   //!
   TBranch        *b_piplus_RichPIDk;   //!
   TBranch        *b_piplus_RichPIDp;   //!
   TBranch        *b_piplus_MC12TuneV2_ProbNNe;   //!
   TBranch        *b_piplus_MC12TuneV2_ProbNNmu;   //!
   TBranch        *b_piplus_MC12TuneV2_ProbNNpi;   //!
   TBranch        *b_piplus_MC12TuneV2_ProbNNk;   //!
   TBranch        *b_piplus_MC12TuneV2_ProbNNp;   //!
   TBranch        *b_piplus_MC12TuneV2_ProbNNghost;   //!
   TBranch        *b_piplus_MC12TuneV3_ProbNNe;   //!
   TBranch        *b_piplus_MC12TuneV3_ProbNNmu;   //!
   TBranch        *b_piplus_MC12TuneV3_ProbNNpi;   //!
   TBranch        *b_piplus_MC12TuneV3_ProbNNk;   //!
   TBranch        *b_piplus_MC12TuneV3_ProbNNp;   //!
   TBranch        *b_piplus_MC12TuneV3_ProbNNghost;   //!
   TBranch        *b_piplus_MC12TuneV4_ProbNNe;   //!
   TBranch        *b_piplus_MC12TuneV4_ProbNNmu;   //!
   TBranch        *b_piplus_MC12TuneV4_ProbNNpi;   //!
   TBranch        *b_piplus_MC12TuneV4_ProbNNk;   //!
   TBranch        *b_piplus_MC12TuneV4_ProbNNp;   //!
   TBranch        *b_piplus_MC12TuneV4_ProbNNghost;   //!
   TBranch        *b_piplus_MC15TuneV1_ProbNNe;   //!
   TBranch        *b_piplus_MC15TuneV1_ProbNNmu;   //!
   TBranch        *b_piplus_MC15TuneV1_ProbNNpi;   //!
   TBranch        *b_piplus_MC15TuneV1_ProbNNk;   //!
   TBranch        *b_piplus_MC15TuneV1_ProbNNp;   //!
   TBranch        *b_piplus_MC15TuneV1_ProbNNghost;   //!
   TBranch        *b_piplus_MINIP;   //!
   TBranch        *b_piplus_MINIPCHI2;   //!
   TBranch        *b_piplus_MINIPNEXTBEST;   //!
   TBranch        *b_piplus_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_piplus_OWNPV_X;   //!
   TBranch        *b_piplus_OWNPV_Y;   //!
   TBranch        *b_piplus_OWNPV_Z;   //!
   TBranch        *b_piplus_OWNPV_XERR;   //!
   TBranch        *b_piplus_OWNPV_YERR;   //!
   TBranch        *b_piplus_OWNPV_ZERR;   //!
   TBranch        *b_piplus_OWNPV_CHI2;   //!
   TBranch        *b_piplus_OWNPV_NDOF;   //!
   TBranch        *b_piplus_OWNPV_COV_;   //!
   TBranch        *b_piplus_IP_OWNPV;   //!
   TBranch        *b_piplus_IPCHI2_OWNPV;   //!
   TBranch        *b_piplus_TOPPV_X;   //!
   TBranch        *b_piplus_TOPPV_Y;   //!
   TBranch        *b_piplus_TOPPV_Z;   //!
   TBranch        *b_piplus_TOPPV_XERR;   //!
   TBranch        *b_piplus_TOPPV_YERR;   //!
   TBranch        *b_piplus_TOPPV_ZERR;   //!
   TBranch        *b_piplus_TOPPV_CHI2;   //!
   TBranch        *b_piplus_TOPPV_NDOF;   //!
   TBranch        *b_piplus_TOPPV_COV_;   //!
   TBranch        *b_piplus_IP_TOPPV;   //!
   TBranch        *b_piplus_IPCHI2_TOPPV;   //!
   TBranch        *b_piplus_ORIVX_X;   //!
   TBranch        *b_piplus_ORIVX_Y;   //!
   TBranch        *b_piplus_ORIVX_Z;   //!
   TBranch        *b_piplus_ORIVX_XERR;   //!
   TBranch        *b_piplus_ORIVX_YERR;   //!
   TBranch        *b_piplus_ORIVX_ZERR;   //!
   TBranch        *b_piplus_ORIVX_CHI2;   //!
   TBranch        *b_piplus_ORIVX_NDOF;   //!
   TBranch        *b_piplus_ORIVX_COV_;   //!
   TBranch        *b_piplus_IP_ORIVX;   //!
   TBranch        *b_piplus_IPCHI2_ORIVX;   //!
   TBranch        *b_piplus_P;   //!
   TBranch        *b_piplus_PT;   //!
   TBranch        *b_piplus_PE;   //!
   TBranch        *b_piplus_PX;   //!
   TBranch        *b_piplus_PY;   //!
   TBranch        *b_piplus_PZ;   //!
   TBranch        *b_piplus_REFPX;   //!
   TBranch        *b_piplus_REFPY;   //!
   TBranch        *b_piplus_REFPZ;   //!
   TBranch        *b_piplus_M;   //!
   TBranch        *b_piplus_AtVtx_PE;   //!
   TBranch        *b_piplus_AtVtx_PX;   //!
   TBranch        *b_piplus_AtVtx_PY;   //!
   TBranch        *b_piplus_AtVtx_PZ;   //!
   TBranch        *b_piplus_ID;   //!
   TBranch        *b_piplus_PIDe;   //!
   TBranch        *b_piplus_PIDmu;   //!
   TBranch        *b_piplus_PIDK;   //!
   TBranch        *b_piplus_PIDp;   //!
   TBranch        *b_piplus_ProbNNe;   //!
   TBranch        *b_piplus_ProbNNk;   //!
   TBranch        *b_piplus_ProbNNp;   //!
   TBranch        *b_piplus_ProbNNpi;   //!
   TBranch        *b_piplus_ProbNNmu;   //!
   TBranch        *b_piplus_ProbNNghost;   //!
   TBranch        *b_piplus_hasMuon;   //!
   TBranch        *b_piplus_isMuon;   //!
   TBranch        *b_piplus_hasRich;   //!
   TBranch        *b_piplus_UsedRichAerogel;   //!
   TBranch        *b_piplus_UsedRich1Gas;   //!
   TBranch        *b_piplus_UsedRich2Gas;   //!
   TBranch        *b_piplus_RichAboveElThres;   //!
   TBranch        *b_piplus_RichAboveMuThres;   //!
   TBranch        *b_piplus_RichAbovePiThres;   //!
   TBranch        *b_piplus_RichAboveKaThres;   //!
   TBranch        *b_piplus_RichAbovePrThres;   //!
   TBranch        *b_piplus_hasCalo;   //!
   TBranch        *b_piplus_L0Global_Dec;   //!
   TBranch        *b_piplus_L0Global_TIS;   //!
   TBranch        *b_piplus_L0Global_TOS;   //!
   TBranch        *b_piplus_Hlt1Global_Dec;   //!
   TBranch        *b_piplus_Hlt1Global_TIS;   //!
   TBranch        *b_piplus_Hlt1Global_TOS;   //!
   TBranch        *b_piplus_Hlt1Phys_Dec;   //!
   TBranch        *b_piplus_Hlt1Phys_TIS;   //!
   TBranch        *b_piplus_Hlt1Phys_TOS;   //!
   TBranch        *b_piplus_Hlt2Global_Dec;   //!
   TBranch        *b_piplus_Hlt2Global_TIS;   //!
   TBranch        *b_piplus_Hlt2Global_TOS;   //!
   TBranch        *b_piplus_Hlt2Phys_Dec;   //!
   TBranch        *b_piplus_Hlt2Phys_TIS;   //!
   TBranch        *b_piplus_Hlt2Phys_TOS;   //!
   TBranch        *b_piplus_L0DiMuonDecision_Dec;   //!
   TBranch        *b_piplus_L0DiMuonDecision_TIS;   //!
   TBranch        *b_piplus_L0DiMuonDecision_TOS;   //!
   TBranch        *b_piplus_L0ElectronDecision_Dec;   //!
   TBranch        *b_piplus_L0ElectronDecision_TIS;   //!
   TBranch        *b_piplus_L0ElectronDecision_TOS;   //!
   TBranch        *b_piplus_L0HadronDecision_Dec;   //!
   TBranch        *b_piplus_L0HadronDecision_TIS;   //!
   TBranch        *b_piplus_L0HadronDecision_TOS;   //!
   TBranch        *b_piplus_L0MuonDecision_Dec;   //!
   TBranch        *b_piplus_L0MuonDecision_TIS;   //!
   TBranch        *b_piplus_L0MuonDecision_TOS;   //!
   TBranch        *b_piplus_L0JetElDecision_Dec;   //!
   TBranch        *b_piplus_L0JetElDecision_TIS;   //!
   TBranch        *b_piplus_L0JetElDecision_TOS;   //!
   TBranch        *b_piplus_L0JetPhDecision_Dec;   //!
   TBranch        *b_piplus_L0JetPhDecision_TIS;   //!
   TBranch        *b_piplus_L0JetPhDecision_TOS;   //!
   TBranch        *b_piplus_L0MuonEWDecision_Dec;   //!
   TBranch        *b_piplus_L0MuonEWDecision_TIS;   //!
   TBranch        *b_piplus_L0MuonEWDecision_TOS;   //!
   TBranch        *b_piplus_L0PhotonDecision_Dec;   //!
   TBranch        *b_piplus_L0PhotonDecision_TIS;   //!
   TBranch        *b_piplus_L0PhotonDecision_TOS;   //!
   TBranch        *b_piplus_Hlt1TrackMVADecision_Dec;   //!
   TBranch        *b_piplus_Hlt1TrackMVADecision_TIS;   //!
   TBranch        *b_piplus_Hlt1TrackMVADecision_TOS;   //!
   TBranch        *b_piplus_Hlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_piplus_Hlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_piplus_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_piplus_Hlt1TwoTrackMVADecision_Dec;   //!
   TBranch        *b_piplus_Hlt1TwoTrackMVADecision_TIS;   //!
   TBranch        *b_piplus_Hlt1TwoTrackMVADecision_TOS;   //!
   TBranch        *b_piplus_Hlt2B2HH_B2HHDecision_Dec;   //!
   TBranch        *b_piplus_Hlt2B2HH_B2HHDecision_TIS;   //!
   TBranch        *b_piplus_Hlt2B2HH_B2HHDecision_TOS;   //!
   TBranch        *b_piplus_Hlt2B2HHDecision_Dec;   //!
   TBranch        *b_piplus_Hlt2B2HHDecision_TIS;   //!
   TBranch        *b_piplus_Hlt2B2HHDecision_TOS;   //!
   TBranch        *b_piplus_Hlt2Topo2BodyDecision_Dec;   //!
   TBranch        *b_piplus_Hlt2Topo2BodyDecision_TIS;   //!
   TBranch        *b_piplus_Hlt2Topo2BodyDecision_TOS;   //!
   TBranch        *b_piplus_TRACK_Type;   //!
   TBranch        *b_piplus_TRACK_Key;   //!
   TBranch        *b_piplus_TRACK_CHI2NDOF;   //!
   TBranch        *b_piplus_TRACK_PCHI2;   //!
   TBranch        *b_piplus_TRACK_MatchCHI2;   //!
   TBranch        *b_piplus_TRACK_GhostProb;   //!
   TBranch        *b_piplus_TRACK_CloneDist;   //!
   TBranch        *b_piplus_TRACK_Likelihood;   //!
   TBranch        *b_piminus_DOCA;   //!
   TBranch        *b_piminus_RichPIDk;   //!
   TBranch        *b_piminus_RichPIDp;   //!
   TBranch        *b_piminus_MC12TuneV2_ProbNNe;   //!
   TBranch        *b_piminus_MC12TuneV2_ProbNNmu;   //!
   TBranch        *b_piminus_MC12TuneV2_ProbNNpi;   //!
   TBranch        *b_piminus_MC12TuneV2_ProbNNk;   //!
   TBranch        *b_piminus_MC12TuneV2_ProbNNp;   //!
   TBranch        *b_piminus_MC12TuneV2_ProbNNghost;   //!
   TBranch        *b_piminus_MC12TuneV3_ProbNNe;   //!
   TBranch        *b_piminus_MC12TuneV3_ProbNNmu;   //!
   TBranch        *b_piminus_MC12TuneV3_ProbNNpi;   //!
   TBranch        *b_piminus_MC12TuneV3_ProbNNk;   //!
   TBranch        *b_piminus_MC12TuneV3_ProbNNp;   //!
   TBranch        *b_piminus_MC12TuneV3_ProbNNghost;   //!
   TBranch        *b_piminus_MC12TuneV4_ProbNNe;   //!
   TBranch        *b_piminus_MC12TuneV4_ProbNNmu;   //!
   TBranch        *b_piminus_MC12TuneV4_ProbNNpi;   //!
   TBranch        *b_piminus_MC12TuneV4_ProbNNk;   //!
   TBranch        *b_piminus_MC12TuneV4_ProbNNp;   //!
   TBranch        *b_piminus_MC12TuneV4_ProbNNghost;   //!
   TBranch        *b_piminus_MC15TuneV1_ProbNNe;   //!
   TBranch        *b_piminus_MC15TuneV1_ProbNNmu;   //!
   TBranch        *b_piminus_MC15TuneV1_ProbNNpi;   //!
   TBranch        *b_piminus_MC15TuneV1_ProbNNk;   //!
   TBranch        *b_piminus_MC15TuneV1_ProbNNp;   //!
   TBranch        *b_piminus_MC15TuneV1_ProbNNghost;   //!
   TBranch        *b_piminus_MINIP;   //!
   TBranch        *b_piminus_MINIPCHI2;   //!
   TBranch        *b_piminus_MINIPNEXTBEST;   //!
   TBranch        *b_piminus_MINIPCHI2NEXTBEST;   //!
   TBranch        *b_piminus_OWNPV_X;   //!
   TBranch        *b_piminus_OWNPV_Y;   //!
   TBranch        *b_piminus_OWNPV_Z;   //!
   TBranch        *b_piminus_OWNPV_XERR;   //!
   TBranch        *b_piminus_OWNPV_YERR;   //!
   TBranch        *b_piminus_OWNPV_ZERR;   //!
   TBranch        *b_piminus_OWNPV_CHI2;   //!
   TBranch        *b_piminus_OWNPV_NDOF;   //!
   TBranch        *b_piminus_OWNPV_COV_;   //!
   TBranch        *b_piminus_IP_OWNPV;   //!
   TBranch        *b_piminus_IPCHI2_OWNPV;   //!
   TBranch        *b_piminus_TOPPV_X;   //!
   TBranch        *b_piminus_TOPPV_Y;   //!
   TBranch        *b_piminus_TOPPV_Z;   //!
   TBranch        *b_piminus_TOPPV_XERR;   //!
   TBranch        *b_piminus_TOPPV_YERR;   //!
   TBranch        *b_piminus_TOPPV_ZERR;   //!
   TBranch        *b_piminus_TOPPV_CHI2;   //!
   TBranch        *b_piminus_TOPPV_NDOF;   //!
   TBranch        *b_piminus_TOPPV_COV_;   //!
   TBranch        *b_piminus_IP_TOPPV;   //!
   TBranch        *b_piminus_IPCHI2_TOPPV;   //!
   TBranch        *b_piminus_ORIVX_X;   //!
   TBranch        *b_piminus_ORIVX_Y;   //!
   TBranch        *b_piminus_ORIVX_Z;   //!
   TBranch        *b_piminus_ORIVX_XERR;   //!
   TBranch        *b_piminus_ORIVX_YERR;   //!
   TBranch        *b_piminus_ORIVX_ZERR;   //!
   TBranch        *b_piminus_ORIVX_CHI2;   //!
   TBranch        *b_piminus_ORIVX_NDOF;   //!
   TBranch        *b_piminus_ORIVX_COV_;   //!
   TBranch        *b_piminus_IP_ORIVX;   //!
   TBranch        *b_piminus_IPCHI2_ORIVX;   //!
   TBranch        *b_piminus_P;   //!
   TBranch        *b_piminus_PT;   //!
   TBranch        *b_piminus_PE;   //!
   TBranch        *b_piminus_PX;   //!
   TBranch        *b_piminus_PY;   //!
   TBranch        *b_piminus_PZ;   //!
   TBranch        *b_piminus_REFPX;   //!
   TBranch        *b_piminus_REFPY;   //!
   TBranch        *b_piminus_REFPZ;   //!
   TBranch        *b_piminus_M;   //!
   TBranch        *b_piminus_AtVtx_PE;   //!
   TBranch        *b_piminus_AtVtx_PX;   //!
   TBranch        *b_piminus_AtVtx_PY;   //!
   TBranch        *b_piminus_AtVtx_PZ;   //!
   TBranch        *b_piminus_ID;   //!
   TBranch        *b_piminus_PIDe;   //!
   TBranch        *b_piminus_PIDmu;   //!
   TBranch        *b_piminus_PIDK;   //!
   TBranch        *b_piminus_PIDp;   //!
   TBranch        *b_piminus_ProbNNe;   //!
   TBranch        *b_piminus_ProbNNk;   //!
   TBranch        *b_piminus_ProbNNp;   //!
   TBranch        *b_piminus_ProbNNpi;   //!
   TBranch        *b_piminus_ProbNNmu;   //!
   TBranch        *b_piminus_ProbNNghost;   //!
   TBranch        *b_piminus_hasMuon;   //!
   TBranch        *b_piminus_isMuon;   //!
   TBranch        *b_piminus_hasRich;   //!
   TBranch        *b_piminus_UsedRichAerogel;   //!
   TBranch        *b_piminus_UsedRich1Gas;   //!
   TBranch        *b_piminus_UsedRich2Gas;   //!
   TBranch        *b_piminus_RichAboveElThres;   //!
   TBranch        *b_piminus_RichAboveMuThres;   //!
   TBranch        *b_piminus_RichAbovePiThres;   //!
   TBranch        *b_piminus_RichAboveKaThres;   //!
   TBranch        *b_piminus_RichAbovePrThres;   //!
   TBranch        *b_piminus_hasCalo;   //!
   TBranch        *b_piminus_L0Global_Dec;   //!
   TBranch        *b_piminus_L0Global_TIS;   //!
   TBranch        *b_piminus_L0Global_TOS;   //!
   TBranch        *b_piminus_Hlt1Global_Dec;   //!
   TBranch        *b_piminus_Hlt1Global_TIS;   //!
   TBranch        *b_piminus_Hlt1Global_TOS;   //!
   TBranch        *b_piminus_Hlt1Phys_Dec;   //!
   TBranch        *b_piminus_Hlt1Phys_TIS;   //!
   TBranch        *b_piminus_Hlt1Phys_TOS;   //!
   TBranch        *b_piminus_Hlt2Global_Dec;   //!
   TBranch        *b_piminus_Hlt2Global_TIS;   //!
   TBranch        *b_piminus_Hlt2Global_TOS;   //!
   TBranch        *b_piminus_Hlt2Phys_Dec;   //!
   TBranch        *b_piminus_Hlt2Phys_TIS;   //!
   TBranch        *b_piminus_Hlt2Phys_TOS;   //!
   TBranch        *b_piminus_L0DiMuonDecision_Dec;   //!
   TBranch        *b_piminus_L0DiMuonDecision_TIS;   //!
   TBranch        *b_piminus_L0DiMuonDecision_TOS;   //!
   TBranch        *b_piminus_L0ElectronDecision_Dec;   //!
   TBranch        *b_piminus_L0ElectronDecision_TIS;   //!
   TBranch        *b_piminus_L0ElectronDecision_TOS;   //!
   TBranch        *b_piminus_L0HadronDecision_Dec;   //!
   TBranch        *b_piminus_L0HadronDecision_TIS;   //!
   TBranch        *b_piminus_L0HadronDecision_TOS;   //!
   TBranch        *b_piminus_L0MuonDecision_Dec;   //!
   TBranch        *b_piminus_L0MuonDecision_TIS;   //!
   TBranch        *b_piminus_L0MuonDecision_TOS;   //!
   TBranch        *b_piminus_L0JetElDecision_Dec;   //!
   TBranch        *b_piminus_L0JetElDecision_TIS;   //!
   TBranch        *b_piminus_L0JetElDecision_TOS;   //!
   TBranch        *b_piminus_L0JetPhDecision_Dec;   //!
   TBranch        *b_piminus_L0JetPhDecision_TIS;   //!
   TBranch        *b_piminus_L0JetPhDecision_TOS;   //!
   TBranch        *b_piminus_L0MuonEWDecision_Dec;   //!
   TBranch        *b_piminus_L0MuonEWDecision_TIS;   //!
   TBranch        *b_piminus_L0MuonEWDecision_TOS;   //!
   TBranch        *b_piminus_L0PhotonDecision_Dec;   //!
   TBranch        *b_piminus_L0PhotonDecision_TIS;   //!
   TBranch        *b_piminus_L0PhotonDecision_TOS;   //!
   TBranch        *b_piminus_Hlt1TrackMVADecision_Dec;   //!
   TBranch        *b_piminus_Hlt1TrackMVADecision_TIS;   //!
   TBranch        *b_piminus_Hlt1TrackMVADecision_TOS;   //!
   TBranch        *b_piminus_Hlt1TrackMuonDecision_Dec;   //!
   TBranch        *b_piminus_Hlt1TrackMuonDecision_TIS;   //!
   TBranch        *b_piminus_Hlt1TrackMuonDecision_TOS;   //!
   TBranch        *b_piminus_Hlt1TwoTrackMVADecision_Dec;   //!
   TBranch        *b_piminus_Hlt1TwoTrackMVADecision_TIS;   //!
   TBranch        *b_piminus_Hlt1TwoTrackMVADecision_TOS;   //!
   TBranch        *b_piminus_Hlt2B2HH_B2HHDecision_Dec;   //!
   TBranch        *b_piminus_Hlt2B2HH_B2HHDecision_TIS;   //!
   TBranch        *b_piminus_Hlt2B2HH_B2HHDecision_TOS;   //!
   TBranch        *b_piminus_Hlt2B2HHDecision_Dec;   //!
   TBranch        *b_piminus_Hlt2B2HHDecision_TIS;   //!
   TBranch        *b_piminus_Hlt2B2HHDecision_TOS;   //!
   TBranch        *b_piminus_Hlt2Topo2BodyDecision_Dec;   //!
   TBranch        *b_piminus_Hlt2Topo2BodyDecision_TIS;   //!
   TBranch        *b_piminus_Hlt2Topo2BodyDecision_TOS;   //!
   TBranch        *b_piminus_TRACK_Type;   //!
   TBranch        *b_piminus_TRACK_Key;   //!
   TBranch        *b_piminus_TRACK_CHI2NDOF;   //!
   TBranch        *b_piminus_TRACK_PCHI2;   //!
   TBranch        *b_piminus_TRACK_MatchCHI2;   //!
   TBranch        *b_piminus_TRACK_GhostProb;   //!
   TBranch        *b_piminus_TRACK_CloneDist;   //!
   TBranch        *b_piminus_TRACK_Likelihood;   //!
   TBranch        *b_nCandidate;   //!
   TBranch        *b_totCandidates;   //!
   TBranch        *b_EventInSequence;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_BCID;   //!
   TBranch        *b_BCType;   //!
   TBranch        *b_OdinTCK;   //!
   TBranch        *b_L0DUTCK;   //!
   TBranch        *b_HLT1TCK;   //!
   TBranch        *b_HLT2TCK;   //!
   TBranch        *b_GpsTime;   //!
   TBranch        *b_Polarity;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_PVX;   //!
   TBranch        *b_PVY;   //!
   TBranch        *b_PVZ;   //!
   TBranch        *b_PVXERR;   //!
   TBranch        *b_PVYERR;   //!
   TBranch        *b_PVZERR;   //!
   TBranch        *b_PVCHI2;   //!
   TBranch        *b_PVNDOF;   //!
   TBranch        *b_PVNTRACKS;   //!
   TBranch        *b_nPVs;   //!
   TBranch        *b_nTracks;   //!
   TBranch        *b_nLongTracks;   //!
   TBranch        *b_nDownstreamTracks;   //!
   TBranch        *b_nUpstreamTracks;   //!
   TBranch        *b_nVeloTracks;   //!
   TBranch        *b_nTTracks;   //!
   TBranch        *b_nBackTracks;   //!
   TBranch        *b_nRich1Hits;   //!
   TBranch        *b_nRich2Hits;   //!
   TBranch        *b_nVeloClusters;   //!
   TBranch        *b_nITClusters;   //!
   TBranch        *b_nTTClusters;   //!
   TBranch        *b_nOTClusters;   //!
   TBranch        *b_nSPDHits;   //!
   TBranch        *b_nMuonCoordsS0;   //!
   TBranch        *b_nMuonCoordsS1;   //!
   TBranch        *b_nMuonCoordsS2;   //!
   TBranch        *b_nMuonCoordsS3;   //!
   TBranch        *b_nMuonCoordsS4;   //!
   TBranch        *b_nMuonTracks;   //!

   sel(TTree *tree=0, TString decay="b2hh", TString year="2015", TString magnet="Up", Int_t index=1);
   virtual ~sel();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef sel_cxx
sel::sel(TTree *tree, TString decay, TString year, TString magnet, Int_t index) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   fdecay = decay;
   fyear = year;
   fmagnet = magnet;
   findex = index;
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/storage/gpfs_data/local/lhcb/users/perazzini/gangadir/workspace/perazzini/LocalXML/199/6/output//b2hh.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/storage/gpfs_data/local/lhcb/users/perazzini/gangadir/workspace/perazzini/LocalXML/199/6/output//b2hh.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/storage/gpfs_data/local/lhcb/users/perazzini/gangadir/workspace/perazzini/LocalXML/199/6/output//b2hh.root:/PreSelB2HH");
      dir->GetObject("PreSelB2HH",tree);

   }
   Init(tree);
}

sel::~sel()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t sel::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t sel::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void sel::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("B0_DOCA", &B0_DOCA, &b_B0_DOCA);
   fChain->SetBranchAddress("B0_RichPIDk", &B0_RichPIDk, &b_B0_RichPIDk);
   fChain->SetBranchAddress("B0_RichPIDp", &B0_RichPIDp, &b_B0_RichPIDp);
   fChain->SetBranchAddress("B0_MINIP", &B0_MINIP, &b_B0_MINIP);
   fChain->SetBranchAddress("B0_MINIPCHI2", &B0_MINIPCHI2, &b_B0_MINIPCHI2);
   fChain->SetBranchAddress("B0_MINIPNEXTBEST", &B0_MINIPNEXTBEST, &b_B0_MINIPNEXTBEST);
   fChain->SetBranchAddress("B0_MINIPCHI2NEXTBEST", &B0_MINIPCHI2NEXTBEST, &b_B0_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("B0_ENDVERTEX_X", &B0_ENDVERTEX_X, &b_B0_ENDVERTEX_X);
   fChain->SetBranchAddress("B0_ENDVERTEX_Y", &B0_ENDVERTEX_Y, &b_B0_ENDVERTEX_Y);
   fChain->SetBranchAddress("B0_ENDVERTEX_Z", &B0_ENDVERTEX_Z, &b_B0_ENDVERTEX_Z);
   fChain->SetBranchAddress("B0_ENDVERTEX_XERR", &B0_ENDVERTEX_XERR, &b_B0_ENDVERTEX_XERR);
   fChain->SetBranchAddress("B0_ENDVERTEX_YERR", &B0_ENDVERTEX_YERR, &b_B0_ENDVERTEX_YERR);
   fChain->SetBranchAddress("B0_ENDVERTEX_ZERR", &B0_ENDVERTEX_ZERR, &b_B0_ENDVERTEX_ZERR);
   fChain->SetBranchAddress("B0_ENDVERTEX_CHI2", &B0_ENDVERTEX_CHI2, &b_B0_ENDVERTEX_CHI2);
   fChain->SetBranchAddress("B0_ENDVERTEX_NDOF", &B0_ENDVERTEX_NDOF, &b_B0_ENDVERTEX_NDOF);
   fChain->SetBranchAddress("B0_ENDVERTEX_COV_", B0_ENDVERTEX_COV_, &b_B0_ENDVERTEX_COV_);
   fChain->SetBranchAddress("B0_OWNPV_X", &B0_OWNPV_X, &b_B0_OWNPV_X);
   fChain->SetBranchAddress("B0_OWNPV_Y", &B0_OWNPV_Y, &b_B0_OWNPV_Y);
   fChain->SetBranchAddress("B0_OWNPV_Z", &B0_OWNPV_Z, &b_B0_OWNPV_Z);
   fChain->SetBranchAddress("B0_OWNPV_XERR", &B0_OWNPV_XERR, &b_B0_OWNPV_XERR);
   fChain->SetBranchAddress("B0_OWNPV_YERR", &B0_OWNPV_YERR, &b_B0_OWNPV_YERR);
   fChain->SetBranchAddress("B0_OWNPV_ZERR", &B0_OWNPV_ZERR, &b_B0_OWNPV_ZERR);
   fChain->SetBranchAddress("B0_OWNPV_CHI2", &B0_OWNPV_CHI2, &b_B0_OWNPV_CHI2);
   fChain->SetBranchAddress("B0_OWNPV_NDOF", &B0_OWNPV_NDOF, &b_B0_OWNPV_NDOF);
   fChain->SetBranchAddress("B0_OWNPV_COV_", B0_OWNPV_COV_, &b_B0_OWNPV_COV_);
   fChain->SetBranchAddress("B0_IP_OWNPV", &B0_IP_OWNPV, &b_B0_IP_OWNPV);
   fChain->SetBranchAddress("B0_IPCHI2_OWNPV", &B0_IPCHI2_OWNPV, &b_B0_IPCHI2_OWNPV);
   fChain->SetBranchAddress("B0_FD_OWNPV", &B0_FD_OWNPV, &b_B0_FD_OWNPV);
   fChain->SetBranchAddress("B0_FDCHI2_OWNPV", &B0_FDCHI2_OWNPV, &b_B0_FDCHI2_OWNPV);
   fChain->SetBranchAddress("B0_DIRA_OWNPV", &B0_DIRA_OWNPV, &b_B0_DIRA_OWNPV);
   fChain->SetBranchAddress("B0_TOPPV_X", &B0_TOPPV_X, &b_B0_TOPPV_X);
   fChain->SetBranchAddress("B0_TOPPV_Y", &B0_TOPPV_Y, &b_B0_TOPPV_Y);
   fChain->SetBranchAddress("B0_TOPPV_Z", &B0_TOPPV_Z, &b_B0_TOPPV_Z);
   fChain->SetBranchAddress("B0_TOPPV_XERR", &B0_TOPPV_XERR, &b_B0_TOPPV_XERR);
   fChain->SetBranchAddress("B0_TOPPV_YERR", &B0_TOPPV_YERR, &b_B0_TOPPV_YERR);
   fChain->SetBranchAddress("B0_TOPPV_ZERR", &B0_TOPPV_ZERR, &b_B0_TOPPV_ZERR);
   fChain->SetBranchAddress("B0_TOPPV_CHI2", &B0_TOPPV_CHI2, &b_B0_TOPPV_CHI2);
   fChain->SetBranchAddress("B0_TOPPV_NDOF", &B0_TOPPV_NDOF, &b_B0_TOPPV_NDOF);
   fChain->SetBranchAddress("B0_TOPPV_COV_", B0_TOPPV_COV_, &b_B0_TOPPV_COV_);
   fChain->SetBranchAddress("B0_IP_TOPPV", &B0_IP_TOPPV, &b_B0_IP_TOPPV);
   fChain->SetBranchAddress("B0_IPCHI2_TOPPV", &B0_IPCHI2_TOPPV, &b_B0_IPCHI2_TOPPV);
   fChain->SetBranchAddress("B0_FD_TOPPV", &B0_FD_TOPPV, &b_B0_FD_TOPPV);
   fChain->SetBranchAddress("B0_FDCHI2_TOPPV", &B0_FDCHI2_TOPPV, &b_B0_FDCHI2_TOPPV);
   fChain->SetBranchAddress("B0_DIRA_TOPPV", &B0_DIRA_TOPPV, &b_B0_DIRA_TOPPV);
   fChain->SetBranchAddress("B0_P", &B0_P, &b_B0_P);
   fChain->SetBranchAddress("B0_PT", &B0_PT, &b_B0_PT);
   fChain->SetBranchAddress("B0_PE", &B0_PE, &b_B0_PE);
   fChain->SetBranchAddress("B0_PX", &B0_PX, &b_B0_PX);
   fChain->SetBranchAddress("B0_PY", &B0_PY, &b_B0_PY);
   fChain->SetBranchAddress("B0_PZ", &B0_PZ, &b_B0_PZ);
   fChain->SetBranchAddress("B0_REFPX", &B0_REFPX, &b_B0_REFPX);
   fChain->SetBranchAddress("B0_REFPY", &B0_REFPY, &b_B0_REFPY);
   fChain->SetBranchAddress("B0_REFPZ", &B0_REFPZ, &b_B0_REFPZ);
   fChain->SetBranchAddress("B0_MM", &B0_MM, &b_B0_MM);
   fChain->SetBranchAddress("B0_MMERR", &B0_MMERR, &b_B0_MMERR);
   fChain->SetBranchAddress("B0_M", &B0_M, &b_B0_M);
   fChain->SetBranchAddress("B0_ID", &B0_ID, &b_B0_ID);
   fChain->SetBranchAddress("B0_TAU", &B0_TAU, &b_B0_TAU);
   fChain->SetBranchAddress("B0_TAUERR", &B0_TAUERR, &b_B0_TAUERR);
   fChain->SetBranchAddress("B0_TAUCHI2", &B0_TAUCHI2, &b_B0_TAUCHI2);
   fChain->SetBranchAddress("B0_L0Global_Dec", &B0_L0Global_Dec, &b_B0_L0Global_Dec);
   fChain->SetBranchAddress("B0_L0Global_TIS", &B0_L0Global_TIS, &b_B0_L0Global_TIS);
   fChain->SetBranchAddress("B0_L0Global_TOS", &B0_L0Global_TOS, &b_B0_L0Global_TOS);
   fChain->SetBranchAddress("B0_Hlt1Global_Dec", &B0_Hlt1Global_Dec, &b_B0_Hlt1Global_Dec);
   fChain->SetBranchAddress("B0_Hlt1Global_TIS", &B0_Hlt1Global_TIS, &b_B0_Hlt1Global_TIS);
   fChain->SetBranchAddress("B0_Hlt1Global_TOS", &B0_Hlt1Global_TOS, &b_B0_Hlt1Global_TOS);
   fChain->SetBranchAddress("B0_Hlt1Phys_Dec", &B0_Hlt1Phys_Dec, &b_B0_Hlt1Phys_Dec);
   fChain->SetBranchAddress("B0_Hlt1Phys_TIS", &B0_Hlt1Phys_TIS, &b_B0_Hlt1Phys_TIS);
   fChain->SetBranchAddress("B0_Hlt1Phys_TOS", &B0_Hlt1Phys_TOS, &b_B0_Hlt1Phys_TOS);
   fChain->SetBranchAddress("B0_Hlt2Global_Dec", &B0_Hlt2Global_Dec, &b_B0_Hlt2Global_Dec);
   fChain->SetBranchAddress("B0_Hlt2Global_TIS", &B0_Hlt2Global_TIS, &b_B0_Hlt2Global_TIS);
   fChain->SetBranchAddress("B0_Hlt2Global_TOS", &B0_Hlt2Global_TOS, &b_B0_Hlt2Global_TOS);
   fChain->SetBranchAddress("B0_Hlt2Phys_Dec", &B0_Hlt2Phys_Dec, &b_B0_Hlt2Phys_Dec);
   fChain->SetBranchAddress("B0_Hlt2Phys_TIS", &B0_Hlt2Phys_TIS, &b_B0_Hlt2Phys_TIS);
   fChain->SetBranchAddress("B0_Hlt2Phys_TOS", &B0_Hlt2Phys_TOS, &b_B0_Hlt2Phys_TOS);
   fChain->SetBranchAddress("B0_L0DiMuonDecision_Dec", &B0_L0DiMuonDecision_Dec, &b_B0_L0DiMuonDecision_Dec);
   fChain->SetBranchAddress("B0_L0DiMuonDecision_TIS", &B0_L0DiMuonDecision_TIS, &b_B0_L0DiMuonDecision_TIS);
   fChain->SetBranchAddress("B0_L0DiMuonDecision_TOS", &B0_L0DiMuonDecision_TOS, &b_B0_L0DiMuonDecision_TOS);
   fChain->SetBranchAddress("B0_L0ElectronDecision_Dec", &B0_L0ElectronDecision_Dec, &b_B0_L0ElectronDecision_Dec);
   fChain->SetBranchAddress("B0_L0ElectronDecision_TIS", &B0_L0ElectronDecision_TIS, &b_B0_L0ElectronDecision_TIS);
   fChain->SetBranchAddress("B0_L0ElectronDecision_TOS", &B0_L0ElectronDecision_TOS, &b_B0_L0ElectronDecision_TOS);
   fChain->SetBranchAddress("B0_L0HadronDecision_Dec", &B0_L0HadronDecision_Dec, &b_B0_L0HadronDecision_Dec);
   fChain->SetBranchAddress("B0_L0HadronDecision_TIS", &B0_L0HadronDecision_TIS, &b_B0_L0HadronDecision_TIS);
   fChain->SetBranchAddress("B0_L0HadronDecision_TOS", &B0_L0HadronDecision_TOS, &b_B0_L0HadronDecision_TOS);
   fChain->SetBranchAddress("B0_L0MuonDecision_Dec", &B0_L0MuonDecision_Dec, &b_B0_L0MuonDecision_Dec);
   fChain->SetBranchAddress("B0_L0MuonDecision_TIS", &B0_L0MuonDecision_TIS, &b_B0_L0MuonDecision_TIS);
   fChain->SetBranchAddress("B0_L0MuonDecision_TOS", &B0_L0MuonDecision_TOS, &b_B0_L0MuonDecision_TOS);
   fChain->SetBranchAddress("B0_L0JetElDecision_Dec", &B0_L0JetElDecision_Dec, &b_B0_L0JetElDecision_Dec);
   fChain->SetBranchAddress("B0_L0JetElDecision_TIS", &B0_L0JetElDecision_TIS, &b_B0_L0JetElDecision_TIS);
   fChain->SetBranchAddress("B0_L0JetElDecision_TOS", &B0_L0JetElDecision_TOS, &b_B0_L0JetElDecision_TOS);
   fChain->SetBranchAddress("B0_L0JetPhDecision_Dec", &B0_L0JetPhDecision_Dec, &b_B0_L0JetPhDecision_Dec);
   fChain->SetBranchAddress("B0_L0JetPhDecision_TIS", &B0_L0JetPhDecision_TIS, &b_B0_L0JetPhDecision_TIS);
   fChain->SetBranchAddress("B0_L0JetPhDecision_TOS", &B0_L0JetPhDecision_TOS, &b_B0_L0JetPhDecision_TOS);
   fChain->SetBranchAddress("B0_L0MuonEWDecision_Dec", &B0_L0MuonEWDecision_Dec, &b_B0_L0MuonEWDecision_Dec);
   fChain->SetBranchAddress("B0_L0MuonEWDecision_TIS", &B0_L0MuonEWDecision_TIS, &b_B0_L0MuonEWDecision_TIS);
   fChain->SetBranchAddress("B0_L0MuonEWDecision_TOS", &B0_L0MuonEWDecision_TOS, &b_B0_L0MuonEWDecision_TOS);
   fChain->SetBranchAddress("B0_L0PhotonDecision_Dec", &B0_L0PhotonDecision_Dec, &b_B0_L0PhotonDecision_Dec);
   fChain->SetBranchAddress("B0_L0PhotonDecision_TIS", &B0_L0PhotonDecision_TIS, &b_B0_L0PhotonDecision_TIS);
   fChain->SetBranchAddress("B0_L0PhotonDecision_TOS", &B0_L0PhotonDecision_TOS, &b_B0_L0PhotonDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt1TrackMVADecision_Dec", &B0_Hlt1TrackMVADecision_Dec, &b_B0_Hlt1TrackMVADecision_Dec);
   fChain->SetBranchAddress("B0_Hlt1TrackMVADecision_TIS", &B0_Hlt1TrackMVADecision_TIS, &b_B0_Hlt1TrackMVADecision_TIS);
   fChain->SetBranchAddress("B0_Hlt1TrackMVADecision_TOS", &B0_Hlt1TrackMVADecision_TOS, &b_B0_Hlt1TrackMVADecision_TOS);
   fChain->SetBranchAddress("B0_Hlt1TrackMuonDecision_Dec", &B0_Hlt1TrackMuonDecision_Dec, &b_B0_Hlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt1TrackMuonDecision_TIS", &B0_Hlt1TrackMuonDecision_TIS, &b_B0_Hlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt1TrackMuonDecision_TOS", &B0_Hlt1TrackMuonDecision_TOS, &b_B0_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt1TwoTrackMVADecision_Dec", &B0_Hlt1TwoTrackMVADecision_Dec, &b_B0_Hlt1TwoTrackMVADecision_Dec);
   fChain->SetBranchAddress("B0_Hlt1TwoTrackMVADecision_TIS", &B0_Hlt1TwoTrackMVADecision_TIS, &b_B0_Hlt1TwoTrackMVADecision_TIS);
   fChain->SetBranchAddress("B0_Hlt1TwoTrackMVADecision_TOS", &B0_Hlt1TwoTrackMVADecision_TOS, &b_B0_Hlt1TwoTrackMVADecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2B2HH_B2HHDecision_Dec", &B0_Hlt2B2HH_B2HHDecision_Dec, &b_B0_Hlt2B2HH_B2HHDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2B2HH_B2HHDecision_TIS", &B0_Hlt2B2HH_B2HHDecision_TIS, &b_B0_Hlt2B2HH_B2HHDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2B2HH_B2HHDecision_TOS", &B0_Hlt2B2HH_B2HHDecision_TOS, &b_B0_Hlt2B2HH_B2HHDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2B2HHDecision_Dec", &B0_Hlt2B2HHDecision_Dec, &b_B0_Hlt2B2HHDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2B2HHDecision_TIS", &B0_Hlt2B2HHDecision_TIS, &b_B0_Hlt2B2HHDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2B2HHDecision_TOS", &B0_Hlt2B2HHDecision_TOS, &b_B0_Hlt2B2HHDecision_TOS);
   fChain->SetBranchAddress("B0_Hlt2Topo2BodyDecision_Dec", &B0_Hlt2Topo2BodyDecision_Dec, &b_B0_Hlt2Topo2BodyDecision_Dec);
   fChain->SetBranchAddress("B0_Hlt2Topo2BodyDecision_TIS", &B0_Hlt2Topo2BodyDecision_TIS, &b_B0_Hlt2Topo2BodyDecision_TIS);
   fChain->SetBranchAddress("B0_Hlt2Topo2BodyDecision_TOS", &B0_Hlt2Topo2BodyDecision_TOS, &b_B0_Hlt2Topo2BodyDecision_TOS);
   // tagging variables
   TString nOSCharm = "OSCharm";
   TString nOSElectron = "OSElectron";
   TString nOSKaon = "OSKaon";
   TString nOSMuon = "OSMuon";   
   TString nOSVtxCh= "OSVtxCh";
   TString nSSKaon = "SSKaon";
   TString nSSPion = "SSPion";
   TString nSSProton = "SSProton";
   if (fyear == "2017"){
      nOSCharm = "OS_Charm";
      nOSElectron = "OS_Electron";
      nOSKaon = "OS_Kaon";
      nOSMuon = "OS_Muon";   
      nOSVtxCh= "VtxCharge";
      nSSKaon = "SS_nnetKaon";
      nSSPion = "SS_PionBDT";
      nSSProton = "SS_Proton";
   }
   fChain->SetBranchAddress("B0_"+nOSCharm+"_TAGDEC", &B0_OSCharm_TAGDEC, &b_B0_OSCharm_TAGDEC);
   fChain->SetBranchAddress("B0_"+nOSCharm+"_TAGETA", &B0_OSCharm_TAGETA, &b_B0_OSCharm_TAGETA);
   fChain->SetBranchAddress("B0_"+nOSCharm+"_CHARGE", &B0_OSCharm_CHARGE, &b_B0_OSCharm_CHARGE);
   fChain->SetBranchAddress("B0_"+nOSCharm+"_MVAOUT", &B0_OSCharm_MVAOUT, &b_B0_OSCharm_MVAOUT);
   fChain->SetBranchAddress("B0_"+nOSElectron+"_TAGDEC", &B0_OSElectron_TAGDEC, &b_B0_OSElectron_TAGDEC);
   fChain->SetBranchAddress("B0_"+nOSElectron+"_TAGETA", &B0_OSElectron_TAGETA, &b_B0_OSElectron_TAGETA);
   fChain->SetBranchAddress("B0_"+nOSElectron+"_CHARGE", &B0_OSElectron_CHARGE, &b_B0_OSElectron_CHARGE);
   fChain->SetBranchAddress("B0_"+nOSElectron+"_MVAOUT", &B0_OSElectron_MVAOUT, &b_B0_OSElectron_MVAOUT);
   fChain->SetBranchAddress("B0_OSElectronLatest_TAGDEC", &B0_OSElectronLatest_TAGDEC, &b_B0_OSElectronLatest_TAGDEC);
   fChain->SetBranchAddress("B0_OSElectronLatest_TAGETA", &B0_OSElectronLatest_TAGETA, &b_B0_OSElectronLatest_TAGETA);
   fChain->SetBranchAddress("B0_OSElectronLatest_CHARGE", &B0_OSElectronLatest_CHARGE, &b_B0_OSElectronLatest_CHARGE);
   fChain->SetBranchAddress("B0_OSElectronLatest_MVAOUT", &B0_OSElectronLatest_MVAOUT, &b_B0_OSElectronLatest_MVAOUT);
   fChain->SetBranchAddress("B0_"+nOSKaon+"_TAGDEC", &B0_OSKaon_TAGDEC, &b_B0_OSKaon_TAGDEC);
   fChain->SetBranchAddress("B0_"+nOSKaon+"_TAGETA", &B0_OSKaon_TAGETA, &b_B0_OSKaon_TAGETA);
   fChain->SetBranchAddress("B0_"+nOSKaon+"_CHARGE", &B0_OSKaon_CHARGE, &b_B0_OSKaon_CHARGE);
   fChain->SetBranchAddress("B0_"+nOSKaon+"_MVAOUT", &B0_OSKaon_MVAOUT, &b_B0_OSKaon_MVAOUT);
   fChain->SetBranchAddress("B0_OSKaonLatest_TAGDEC", &B0_OSKaonLatest_TAGDEC, &b_B0_OSKaonLatest_TAGDEC);
   fChain->SetBranchAddress("B0_OSKaonLatest_TAGETA", &B0_OSKaonLatest_TAGETA, &b_B0_OSKaonLatest_TAGETA);
   fChain->SetBranchAddress("B0_OSKaonLatest_CHARGE", &B0_OSKaonLatest_CHARGE, &b_B0_OSKaonLatest_CHARGE);
   fChain->SetBranchAddress("B0_OSKaonLatest_MVAOUT", &B0_OSKaonLatest_MVAOUT, &b_B0_OSKaonLatest_MVAOUT);
   fChain->SetBranchAddress("B0_"+nOSMuon+"_TAGDEC", &B0_OSMuon_TAGDEC, &b_B0_OSMuon_TAGDEC);
   fChain->SetBranchAddress("B0_"+nOSMuon+"_TAGETA", &B0_OSMuon_TAGETA, &b_B0_OSMuon_TAGETA);
   fChain->SetBranchAddress("B0_"+nOSMuon+"_CHARGE", &B0_OSMuon_CHARGE, &b_B0_OSMuon_CHARGE);
   fChain->SetBranchAddress("B0_"+nOSMuon+"_MVAOUT", &B0_OSMuon_MVAOUT, &b_B0_OSMuon_MVAOUT);
   fChain->SetBranchAddress("B0_OSMuonLatest_TAGDEC", &B0_OSMuonLatest_TAGDEC, &b_B0_OSMuonLatest_TAGDEC);
   fChain->SetBranchAddress("B0_OSMuonLatest_TAGETA", &B0_OSMuonLatest_TAGETA, &b_B0_OSMuonLatest_TAGETA);
   fChain->SetBranchAddress("B0_OSMuonLatest_CHARGE", &B0_OSMuonLatest_CHARGE, &b_B0_OSMuonLatest_CHARGE);
   fChain->SetBranchAddress("B0_OSMuonLatest_MVAOUT", &B0_OSMuonLatest_MVAOUT, &b_B0_OSMuonLatest_MVAOUT);
   fChain->SetBranchAddress("B0_"+nOSVtxCh+"_TAGDEC", &B0_OSVtxCh_TAGDEC, &b_B0_OSVtxCh_TAGDEC);
   fChain->SetBranchAddress("B0_"+nOSVtxCh+"_TAGETA", &B0_OSVtxCh_TAGETA, &b_B0_OSVtxCh_TAGETA);
   fChain->SetBranchAddress("B0_"+nOSVtxCh+"_CHARGE", &B0_OSVtxCh_CHARGE, &b_B0_OSVtxCh_CHARGE);
   fChain->SetBranchAddress("B0_"+nOSVtxCh+"_MVAOUT", &B0_OSVtxCh_MVAOUT, &b_B0_OSVtxCh_MVAOUT);
   fChain->SetBranchAddress("B0_"+nSSKaon+"_TAGDEC", &B0_SSKaon_TAGDEC, &b_B0_SSKaon_TAGDEC);
   fChain->SetBranchAddress("B0_"+nSSKaon+"_TAGETA", &B0_SSKaon_TAGETA, &b_B0_SSKaon_TAGETA);
   fChain->SetBranchAddress("B0_"+nSSKaon+"_CHARGE", &B0_SSKaon_CHARGE, &b_B0_SSKaon_CHARGE);
   fChain->SetBranchAddress("B0_"+nSSKaon+"_MVAOUT", &B0_SSKaon_MVAOUT, &b_B0_SSKaon_MVAOUT);
   fChain->SetBranchAddress("B0_SSKaonLatest_TAGDEC", &B0_SSKaonLatest_TAGDEC, &b_B0_SSKaonLatest_TAGDEC);
   fChain->SetBranchAddress("B0_SSKaonLatest_TAGETA", &B0_SSKaonLatest_TAGETA, &b_B0_SSKaonLatest_TAGETA);
   fChain->SetBranchAddress("B0_SSKaonLatest_CHARGE", &B0_SSKaonLatest_CHARGE, &b_B0_SSKaonLatest_CHARGE);
   fChain->SetBranchAddress("B0_SSKaonLatest_MVAOUT", &B0_SSKaonLatest_MVAOUT, &b_B0_SSKaonLatest_MVAOUT);
   fChain->SetBranchAddress("B0_"+nSSPion+"_TAGDEC", &B0_SSPion_TAGDEC, &b_B0_SSPion_TAGDEC);
   fChain->SetBranchAddress("B0_"+nSSPion+"_TAGETA", &B0_SSPion_TAGETA, &b_B0_SSPion_TAGETA);
   fChain->SetBranchAddress("B0_"+nSSPion+"_CHARGE", &B0_SSPion_CHARGE, &b_B0_SSPion_CHARGE);
   fChain->SetBranchAddress("B0_"+nSSPion+"_MVAOUT", &B0_SSPion_MVAOUT, &b_B0_SSPion_MVAOUT);
   fChain->SetBranchAddress("B0_"+nSSProton+"_TAGDEC", &B0_SSProton_TAGDEC, &b_B0_SSProton_TAGDEC);
   fChain->SetBranchAddress("B0_"+nSSProton+"_TAGETA", &B0_SSProton_TAGETA, &b_B0_SSProton_TAGETA);
   fChain->SetBranchAddress("B0_"+nSSProton+"_CHARGE", &B0_SSProton_CHARGE, &b_B0_SSProton_CHARGE);
   fChain->SetBranchAddress("B0_"+nSSProton+"_MVAOUT", &B0_SSProton_MVAOUT, &b_B0_SSProton_MVAOUT);

   fChain->SetBranchAddress("B0_MKK_nPV", &B0_MKK_nPV, &b_B0_MKK_nPV);
   fChain->SetBranchAddress("B0_MKK_M", B0_MKK_M, &b_B0_MKK_M);
   fChain->SetBranchAddress("B0_MKK_MERR", B0_MKK_MERR, &b_B0_MKK_MERR);
   fChain->SetBranchAddress("B0_MKK_P", B0_MKK_P, &b_B0_MKK_P);
   fChain->SetBranchAddress("B0_MKK_PERR", B0_MKK_PERR, &b_B0_MKK_PERR);
   fChain->SetBranchAddress("B0_MKK_PV_X", B0_MKK_PV_X, &b_B0_MKK_PV_X);
   fChain->SetBranchAddress("B0_MKK_PV_Y", B0_MKK_PV_Y, &b_B0_MKK_PV_Y);
   fChain->SetBranchAddress("B0_MKK_PV_Z", B0_MKK_PV_Z, &b_B0_MKK_PV_Z);
   fChain->SetBranchAddress("B0_MKK_PV_key", B0_MKK_PV_key, &b_B0_MKK_PV_key);
   fChain->SetBranchAddress("B0_MKK_chi2", B0_MKK_chi2, &b_B0_MKK_chi2);
   fChain->SetBranchAddress("B0_MKK_ctau", B0_MKK_ctau, &b_B0_MKK_ctau);
   fChain->SetBranchAddress("B0_MKK_ctauErr", B0_MKK_ctauErr, &b_B0_MKK_ctauErr);
   fChain->SetBranchAddress("B0_MKK_decayLength", B0_MKK_decayLength, &b_B0_MKK_decayLength);
   fChain->SetBranchAddress("B0_MKK_decayLengthErr", B0_MKK_decayLengthErr, &b_B0_MKK_decayLengthErr);
   fChain->SetBranchAddress("B0_MKK_nDOF", B0_MKK_nDOF, &b_B0_MKK_nDOF);
   fChain->SetBranchAddress("B0_MKK_nIter", B0_MKK_nIter, &b_B0_MKK_nIter);
   fChain->SetBranchAddress("B0_MKK_status", B0_MKK_status, &b_B0_MKK_status);
   fChain->SetBranchAddress("B0_MKP_nPV", &B0_MKP_nPV, &b_B0_MKP_nPV);
   fChain->SetBranchAddress("B0_MKP_M", B0_MKP_M, &b_B0_MKP_M);
   fChain->SetBranchAddress("B0_MKP_MERR", B0_MKP_MERR, &b_B0_MKP_MERR);
   fChain->SetBranchAddress("B0_MKP_P", B0_MKP_P, &b_B0_MKP_P);
   fChain->SetBranchAddress("B0_MKP_PERR", B0_MKP_PERR, &b_B0_MKP_PERR);
   fChain->SetBranchAddress("B0_MKP_PV_X", B0_MKP_PV_X, &b_B0_MKP_PV_X);
   fChain->SetBranchAddress("B0_MKP_PV_Y", B0_MKP_PV_Y, &b_B0_MKP_PV_Y);
   fChain->SetBranchAddress("B0_MKP_PV_Z", B0_MKP_PV_Z, &b_B0_MKP_PV_Z);
   fChain->SetBranchAddress("B0_MKP_PV_key", B0_MKP_PV_key, &b_B0_MKP_PV_key);
   fChain->SetBranchAddress("B0_MKP_chi2", B0_MKP_chi2, &b_B0_MKP_chi2);
   fChain->SetBranchAddress("B0_MKP_ctau", B0_MKP_ctau, &b_B0_MKP_ctau);
   fChain->SetBranchAddress("B0_MKP_ctauErr", B0_MKP_ctauErr, &b_B0_MKP_ctauErr);
   fChain->SetBranchAddress("B0_MKP_decayLength", B0_MKP_decayLength, &b_B0_MKP_decayLength);
   fChain->SetBranchAddress("B0_MKP_decayLengthErr", B0_MKP_decayLengthErr, &b_B0_MKP_decayLengthErr);
   fChain->SetBranchAddress("B0_MKP_nDOF", B0_MKP_nDOF, &b_B0_MKP_nDOF);
   fChain->SetBranchAddress("B0_MKP_nIter", B0_MKP_nIter, &b_B0_MKP_nIter);
   fChain->SetBranchAddress("B0_MKP_status", B0_MKP_status, &b_B0_MKP_status);
   fChain->SetBranchAddress("B0_MKPi_nPV", &B0_MKPi_nPV, &b_B0_MKPi_nPV);
   fChain->SetBranchAddress("B0_MKPi_M", B0_MKPi_M, &b_B0_MKPi_M);
   fChain->SetBranchAddress("B0_MKPi_MERR", B0_MKPi_MERR, &b_B0_MKPi_MERR);
   fChain->SetBranchAddress("B0_MKPi_P", B0_MKPi_P, &b_B0_MKPi_P);
   fChain->SetBranchAddress("B0_MKPi_PERR", B0_MKPi_PERR, &b_B0_MKPi_PERR);
   fChain->SetBranchAddress("B0_MKPi_PV_X", B0_MKPi_PV_X, &b_B0_MKPi_PV_X);
   fChain->SetBranchAddress("B0_MKPi_PV_Y", B0_MKPi_PV_Y, &b_B0_MKPi_PV_Y);
   fChain->SetBranchAddress("B0_MKPi_PV_Z", B0_MKPi_PV_Z, &b_B0_MKPi_PV_Z);
   fChain->SetBranchAddress("B0_MKPi_PV_key", B0_MKPi_PV_key, &b_B0_MKPi_PV_key);
   fChain->SetBranchAddress("B0_MKPi_chi2", B0_MKPi_chi2, &b_B0_MKPi_chi2);
   fChain->SetBranchAddress("B0_MKPi_ctau", B0_MKPi_ctau, &b_B0_MKPi_ctau);
   fChain->SetBranchAddress("B0_MKPi_ctauErr", B0_MKPi_ctauErr, &b_B0_MKPi_ctauErr);
   fChain->SetBranchAddress("B0_MKPi_decayLength", B0_MKPi_decayLength, &b_B0_MKPi_decayLength);
   fChain->SetBranchAddress("B0_MKPi_decayLengthErr", B0_MKPi_decayLengthErr, &b_B0_MKPi_decayLengthErr);
   fChain->SetBranchAddress("B0_MKPi_nDOF", B0_MKPi_nDOF, &b_B0_MKPi_nDOF);
   fChain->SetBranchAddress("B0_MKPi_nIter", B0_MKPi_nIter, &b_B0_MKPi_nIter);
   fChain->SetBranchAddress("B0_MKPi_status", B0_MKPi_status, &b_B0_MKPi_status);
   fChain->SetBranchAddress("B0_MPK_nPV", &B0_MPK_nPV, &b_B0_MPK_nPV);
   fChain->SetBranchAddress("B0_MPK_M", B0_MPK_M, &b_B0_MPK_M);
   fChain->SetBranchAddress("B0_MPK_MERR", B0_MPK_MERR, &b_B0_MPK_MERR);
   fChain->SetBranchAddress("B0_MPK_P", B0_MPK_P, &b_B0_MPK_P);
   fChain->SetBranchAddress("B0_MPK_PERR", B0_MPK_PERR, &b_B0_MPK_PERR);
   fChain->SetBranchAddress("B0_MPK_PV_X", B0_MPK_PV_X, &b_B0_MPK_PV_X);
   fChain->SetBranchAddress("B0_MPK_PV_Y", B0_MPK_PV_Y, &b_B0_MPK_PV_Y);
   fChain->SetBranchAddress("B0_MPK_PV_Z", B0_MPK_PV_Z, &b_B0_MPK_PV_Z);
   fChain->SetBranchAddress("B0_MPK_PV_key", B0_MPK_PV_key, &b_B0_MPK_PV_key);
   fChain->SetBranchAddress("B0_MPK_chi2", B0_MPK_chi2, &b_B0_MPK_chi2);
   fChain->SetBranchAddress("B0_MPK_ctau", B0_MPK_ctau, &b_B0_MPK_ctau);
   fChain->SetBranchAddress("B0_MPK_ctauErr", B0_MPK_ctauErr, &b_B0_MPK_ctauErr);
   fChain->SetBranchAddress("B0_MPK_decayLength", B0_MPK_decayLength, &b_B0_MPK_decayLength);
   fChain->SetBranchAddress("B0_MPK_decayLengthErr", B0_MPK_decayLengthErr, &b_B0_MPK_decayLengthErr);
   fChain->SetBranchAddress("B0_MPK_nDOF", B0_MPK_nDOF, &b_B0_MPK_nDOF);
   fChain->SetBranchAddress("B0_MPK_nIter", B0_MPK_nIter, &b_B0_MPK_nIter);
   fChain->SetBranchAddress("B0_MPK_status", B0_MPK_status, &b_B0_MPK_status);
   fChain->SetBranchAddress("B0_MPPi_nPV", &B0_MPPi_nPV, &b_B0_MPPi_nPV);
   fChain->SetBranchAddress("B0_MPPi_M", B0_MPPi_M, &b_B0_MPPi_M);
   fChain->SetBranchAddress("B0_MPPi_MERR", B0_MPPi_MERR, &b_B0_MPPi_MERR);
   fChain->SetBranchAddress("B0_MPPi_P", B0_MPPi_P, &b_B0_MPPi_P);
   fChain->SetBranchAddress("B0_MPPi_PERR", B0_MPPi_PERR, &b_B0_MPPi_PERR);
   fChain->SetBranchAddress("B0_MPPi_PV_X", B0_MPPi_PV_X, &b_B0_MPPi_PV_X);
   fChain->SetBranchAddress("B0_MPPi_PV_Y", B0_MPPi_PV_Y, &b_B0_MPPi_PV_Y);
   fChain->SetBranchAddress("B0_MPPi_PV_Z", B0_MPPi_PV_Z, &b_B0_MPPi_PV_Z);
   fChain->SetBranchAddress("B0_MPPi_PV_key", B0_MPPi_PV_key, &b_B0_MPPi_PV_key);
   fChain->SetBranchAddress("B0_MPPi_chi2", B0_MPPi_chi2, &b_B0_MPPi_chi2);
   fChain->SetBranchAddress("B0_MPPi_ctau", B0_MPPi_ctau, &b_B0_MPPi_ctau);
   fChain->SetBranchAddress("B0_MPPi_ctauErr", B0_MPPi_ctauErr, &b_B0_MPPi_ctauErr);
   fChain->SetBranchAddress("B0_MPPi_decayLength", B0_MPPi_decayLength, &b_B0_MPPi_decayLength);
   fChain->SetBranchAddress("B0_MPPi_decayLengthErr", B0_MPPi_decayLengthErr, &b_B0_MPPi_decayLengthErr);
   fChain->SetBranchAddress("B0_MPPi_nDOF", B0_MPPi_nDOF, &b_B0_MPPi_nDOF);
   fChain->SetBranchAddress("B0_MPPi_nIter", B0_MPPi_nIter, &b_B0_MPPi_nIter);
   fChain->SetBranchAddress("B0_MPPi_status", B0_MPPi_status, &b_B0_MPPi_status);
   fChain->SetBranchAddress("B0_MPiK_nPV", &B0_MPiK_nPV, &b_B0_MPiK_nPV);
   fChain->SetBranchAddress("B0_MPiK_M", B0_MPiK_M, &b_B0_MPiK_M);
   fChain->SetBranchAddress("B0_MPiK_MERR", B0_MPiK_MERR, &b_B0_MPiK_MERR);
   fChain->SetBranchAddress("B0_MPiK_P", B0_MPiK_P, &b_B0_MPiK_P);
   fChain->SetBranchAddress("B0_MPiK_PERR", B0_MPiK_PERR, &b_B0_MPiK_PERR);
   fChain->SetBranchAddress("B0_MPiK_PV_X", B0_MPiK_PV_X, &b_B0_MPiK_PV_X);
   fChain->SetBranchAddress("B0_MPiK_PV_Y", B0_MPiK_PV_Y, &b_B0_MPiK_PV_Y);
   fChain->SetBranchAddress("B0_MPiK_PV_Z", B0_MPiK_PV_Z, &b_B0_MPiK_PV_Z);
   fChain->SetBranchAddress("B0_MPiK_PV_key", B0_MPiK_PV_key, &b_B0_MPiK_PV_key);
   fChain->SetBranchAddress("B0_MPiK_chi2", B0_MPiK_chi2, &b_B0_MPiK_chi2);
   fChain->SetBranchAddress("B0_MPiK_ctau", B0_MPiK_ctau, &b_B0_MPiK_ctau);
   fChain->SetBranchAddress("B0_MPiK_ctauErr", B0_MPiK_ctauErr, &b_B0_MPiK_ctauErr);
   fChain->SetBranchAddress("B0_MPiK_decayLength", B0_MPiK_decayLength, &b_B0_MPiK_decayLength);
   fChain->SetBranchAddress("B0_MPiK_decayLengthErr", B0_MPiK_decayLengthErr, &b_B0_MPiK_decayLengthErr);
   fChain->SetBranchAddress("B0_MPiK_nDOF", B0_MPiK_nDOF, &b_B0_MPiK_nDOF);
   fChain->SetBranchAddress("B0_MPiK_nIter", B0_MPiK_nIter, &b_B0_MPiK_nIter);
   fChain->SetBranchAddress("B0_MPiK_status", B0_MPiK_status, &b_B0_MPiK_status);
   fChain->SetBranchAddress("B0_MPiP_nPV", &B0_MPiP_nPV, &b_B0_MPiP_nPV);
   fChain->SetBranchAddress("B0_MPiP_M", B0_MPiP_M, &b_B0_MPiP_M);
   fChain->SetBranchAddress("B0_MPiP_MERR", B0_MPiP_MERR, &b_B0_MPiP_MERR);
   fChain->SetBranchAddress("B0_MPiP_P", B0_MPiP_P, &b_B0_MPiP_P);
   fChain->SetBranchAddress("B0_MPiP_PERR", B0_MPiP_PERR, &b_B0_MPiP_PERR);
   fChain->SetBranchAddress("B0_MPiP_PV_X", B0_MPiP_PV_X, &b_B0_MPiP_PV_X);
   fChain->SetBranchAddress("B0_MPiP_PV_Y", B0_MPiP_PV_Y, &b_B0_MPiP_PV_Y);
   fChain->SetBranchAddress("B0_MPiP_PV_Z", B0_MPiP_PV_Z, &b_B0_MPiP_PV_Z);
   fChain->SetBranchAddress("B0_MPiP_PV_key", B0_MPiP_PV_key, &b_B0_MPiP_PV_key);
   fChain->SetBranchAddress("B0_MPiP_chi2", B0_MPiP_chi2, &b_B0_MPiP_chi2);
   fChain->SetBranchAddress("B0_MPiP_ctau", B0_MPiP_ctau, &b_B0_MPiP_ctau);
   fChain->SetBranchAddress("B0_MPiP_ctauErr", B0_MPiP_ctauErr, &b_B0_MPiP_ctauErr);
   fChain->SetBranchAddress("B0_MPiP_decayLength", B0_MPiP_decayLength, &b_B0_MPiP_decayLength);
   fChain->SetBranchAddress("B0_MPiP_decayLengthErr", B0_MPiP_decayLengthErr, &b_B0_MPiP_decayLengthErr);
   fChain->SetBranchAddress("B0_MPiP_nDOF", B0_MPiP_nDOF, &b_B0_MPiP_nDOF);
   fChain->SetBranchAddress("B0_MPiP_nIter", B0_MPiP_nIter, &b_B0_MPiP_nIter);
   fChain->SetBranchAddress("B0_MPiP_status", B0_MPiP_status, &b_B0_MPiP_status);
   fChain->SetBranchAddress("B0_MPiPi_nPV", &B0_MPiPi_nPV, &b_B0_MPiPi_nPV);
   fChain->SetBranchAddress("B0_MPiPi_M", B0_MPiPi_M, &b_B0_MPiPi_M);
   fChain->SetBranchAddress("B0_MPiPi_MERR", B0_MPiPi_MERR, &b_B0_MPiPi_MERR);
   fChain->SetBranchAddress("B0_MPiPi_P", B0_MPiPi_P, &b_B0_MPiPi_P);
   fChain->SetBranchAddress("B0_MPiPi_PERR", B0_MPiPi_PERR, &b_B0_MPiPi_PERR);
   fChain->SetBranchAddress("B0_MPiPi_PV_X", B0_MPiPi_PV_X, &b_B0_MPiPi_PV_X);
   fChain->SetBranchAddress("B0_MPiPi_PV_Y", B0_MPiPi_PV_Y, &b_B0_MPiPi_PV_Y);
   fChain->SetBranchAddress("B0_MPiPi_PV_Z", B0_MPiPi_PV_Z, &b_B0_MPiPi_PV_Z);
   fChain->SetBranchAddress("B0_MPiPi_PV_key", B0_MPiPi_PV_key, &b_B0_MPiPi_PV_key);
   fChain->SetBranchAddress("B0_MPiPi_chi2", B0_MPiPi_chi2, &b_B0_MPiPi_chi2);
   fChain->SetBranchAddress("B0_MPiPi_ctau", B0_MPiPi_ctau, &b_B0_MPiPi_ctau);
   fChain->SetBranchAddress("B0_MPiPi_ctauErr", B0_MPiPi_ctauErr, &b_B0_MPiPi_ctauErr);
   fChain->SetBranchAddress("B0_MPiPi_decayLength", B0_MPiPi_decayLength, &b_B0_MPiPi_decayLength);
   fChain->SetBranchAddress("B0_MPiPi_decayLengthErr", B0_MPiPi_decayLengthErr, &b_B0_MPiPi_decayLengthErr);
   fChain->SetBranchAddress("B0_MPiPi_nDOF", B0_MPiPi_nDOF, &b_B0_MPiPi_nDOF);
   fChain->SetBranchAddress("B0_MPiPi_nIter", B0_MPiPi_nIter, &b_B0_MPiPi_nIter);
   fChain->SetBranchAddress("B0_MPiPi_status", B0_MPiPi_status, &b_B0_MPiPi_status);
   fChain->SetBranchAddress("piplus_DOCA", &piplus_DOCA, &b_piplus_DOCA);
   fChain->SetBranchAddress("piplus_RichPIDk", &piplus_RichPIDk, &b_piplus_RichPIDk);
   fChain->SetBranchAddress("piplus_RichPIDp", &piplus_RichPIDp, &b_piplus_RichPIDp);
   fChain->SetBranchAddress("piplus_MC12TuneV2_ProbNNe", &piplus_MC12TuneV2_ProbNNe, &b_piplus_MC12TuneV2_ProbNNe);
   fChain->SetBranchAddress("piplus_MC12TuneV2_ProbNNmu", &piplus_MC12TuneV2_ProbNNmu, &b_piplus_MC12TuneV2_ProbNNmu);
   fChain->SetBranchAddress("piplus_MC12TuneV2_ProbNNpi", &piplus_MC12TuneV2_ProbNNpi, &b_piplus_MC12TuneV2_ProbNNpi);
   fChain->SetBranchAddress("piplus_MC12TuneV2_ProbNNk", &piplus_MC12TuneV2_ProbNNk, &b_piplus_MC12TuneV2_ProbNNk);
   fChain->SetBranchAddress("piplus_MC12TuneV2_ProbNNp", &piplus_MC12TuneV2_ProbNNp, &b_piplus_MC12TuneV2_ProbNNp);
   fChain->SetBranchAddress("piplus_MC12TuneV2_ProbNNghost", &piplus_MC12TuneV2_ProbNNghost, &b_piplus_MC12TuneV2_ProbNNghost);
   fChain->SetBranchAddress("piplus_MC12TuneV3_ProbNNe", &piplus_MC12TuneV3_ProbNNe, &b_piplus_MC12TuneV3_ProbNNe);
   fChain->SetBranchAddress("piplus_MC12TuneV3_ProbNNmu", &piplus_MC12TuneV3_ProbNNmu, &b_piplus_MC12TuneV3_ProbNNmu);
   fChain->SetBranchAddress("piplus_MC12TuneV3_ProbNNpi", &piplus_MC12TuneV3_ProbNNpi, &b_piplus_MC12TuneV3_ProbNNpi);
   fChain->SetBranchAddress("piplus_MC12TuneV3_ProbNNk", &piplus_MC12TuneV3_ProbNNk, &b_piplus_MC12TuneV3_ProbNNk);
   fChain->SetBranchAddress("piplus_MC12TuneV3_ProbNNp", &piplus_MC12TuneV3_ProbNNp, &b_piplus_MC12TuneV3_ProbNNp);
   fChain->SetBranchAddress("piplus_MC12TuneV3_ProbNNghost", &piplus_MC12TuneV3_ProbNNghost, &b_piplus_MC12TuneV3_ProbNNghost);
   fChain->SetBranchAddress("piplus_MC12TuneV4_ProbNNe", &piplus_MC12TuneV4_ProbNNe, &b_piplus_MC12TuneV4_ProbNNe);
   fChain->SetBranchAddress("piplus_MC12TuneV4_ProbNNmu", &piplus_MC12TuneV4_ProbNNmu, &b_piplus_MC12TuneV4_ProbNNmu);
   fChain->SetBranchAddress("piplus_MC12TuneV4_ProbNNpi", &piplus_MC12TuneV4_ProbNNpi, &b_piplus_MC12TuneV4_ProbNNpi);
   fChain->SetBranchAddress("piplus_MC12TuneV4_ProbNNk", &piplus_MC12TuneV4_ProbNNk, &b_piplus_MC12TuneV4_ProbNNk);
   fChain->SetBranchAddress("piplus_MC12TuneV4_ProbNNp", &piplus_MC12TuneV4_ProbNNp, &b_piplus_MC12TuneV4_ProbNNp);
   fChain->SetBranchAddress("piplus_MC12TuneV4_ProbNNghost", &piplus_MC12TuneV4_ProbNNghost, &b_piplus_MC12TuneV4_ProbNNghost);
   fChain->SetBranchAddress("piplus_MC15TuneV1_ProbNNe", &piplus_MC15TuneV1_ProbNNe, &b_piplus_MC15TuneV1_ProbNNe);
   fChain->SetBranchAddress("piplus_MC15TuneV1_ProbNNmu", &piplus_MC15TuneV1_ProbNNmu, &b_piplus_MC15TuneV1_ProbNNmu);
   fChain->SetBranchAddress("piplus_MC15TuneV1_ProbNNpi", &piplus_MC15TuneV1_ProbNNpi, &b_piplus_MC15TuneV1_ProbNNpi);
   fChain->SetBranchAddress("piplus_MC15TuneV1_ProbNNk", &piplus_MC15TuneV1_ProbNNk, &b_piplus_MC15TuneV1_ProbNNk);
   fChain->SetBranchAddress("piplus_MC15TuneV1_ProbNNp", &piplus_MC15TuneV1_ProbNNp, &b_piplus_MC15TuneV1_ProbNNp);
   fChain->SetBranchAddress("piplus_MC15TuneV1_ProbNNghost", &piplus_MC15TuneV1_ProbNNghost, &b_piplus_MC15TuneV1_ProbNNghost);
   fChain->SetBranchAddress("piplus_MINIP", &piplus_MINIP, &b_piplus_MINIP);
   fChain->SetBranchAddress("piplus_MINIPCHI2", &piplus_MINIPCHI2, &b_piplus_MINIPCHI2);
   fChain->SetBranchAddress("piplus_MINIPNEXTBEST", &piplus_MINIPNEXTBEST, &b_piplus_MINIPNEXTBEST);
   fChain->SetBranchAddress("piplus_MINIPCHI2NEXTBEST", &piplus_MINIPCHI2NEXTBEST, &b_piplus_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("piplus_OWNPV_X", &piplus_OWNPV_X, &b_piplus_OWNPV_X);
   fChain->SetBranchAddress("piplus_OWNPV_Y", &piplus_OWNPV_Y, &b_piplus_OWNPV_Y);
   fChain->SetBranchAddress("piplus_OWNPV_Z", &piplus_OWNPV_Z, &b_piplus_OWNPV_Z);
   fChain->SetBranchAddress("piplus_OWNPV_XERR", &piplus_OWNPV_XERR, &b_piplus_OWNPV_XERR);
   fChain->SetBranchAddress("piplus_OWNPV_YERR", &piplus_OWNPV_YERR, &b_piplus_OWNPV_YERR);
   fChain->SetBranchAddress("piplus_OWNPV_ZERR", &piplus_OWNPV_ZERR, &b_piplus_OWNPV_ZERR);
   fChain->SetBranchAddress("piplus_OWNPV_CHI2", &piplus_OWNPV_CHI2, &b_piplus_OWNPV_CHI2);
   fChain->SetBranchAddress("piplus_OWNPV_NDOF", &piplus_OWNPV_NDOF, &b_piplus_OWNPV_NDOF);
   fChain->SetBranchAddress("piplus_OWNPV_COV_", piplus_OWNPV_COV_, &b_piplus_OWNPV_COV_);
   fChain->SetBranchAddress("piplus_IP_OWNPV", &piplus_IP_OWNPV, &b_piplus_IP_OWNPV);
   fChain->SetBranchAddress("piplus_IPCHI2_OWNPV", &piplus_IPCHI2_OWNPV, &b_piplus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("piplus_TOPPV_X", &piplus_TOPPV_X, &b_piplus_TOPPV_X);
   fChain->SetBranchAddress("piplus_TOPPV_Y", &piplus_TOPPV_Y, &b_piplus_TOPPV_Y);
   fChain->SetBranchAddress("piplus_TOPPV_Z", &piplus_TOPPV_Z, &b_piplus_TOPPV_Z);
   fChain->SetBranchAddress("piplus_TOPPV_XERR", &piplus_TOPPV_XERR, &b_piplus_TOPPV_XERR);
   fChain->SetBranchAddress("piplus_TOPPV_YERR", &piplus_TOPPV_YERR, &b_piplus_TOPPV_YERR);
   fChain->SetBranchAddress("piplus_TOPPV_ZERR", &piplus_TOPPV_ZERR, &b_piplus_TOPPV_ZERR);
   fChain->SetBranchAddress("piplus_TOPPV_CHI2", &piplus_TOPPV_CHI2, &b_piplus_TOPPV_CHI2);
   fChain->SetBranchAddress("piplus_TOPPV_NDOF", &piplus_TOPPV_NDOF, &b_piplus_TOPPV_NDOF);
   fChain->SetBranchAddress("piplus_TOPPV_COV_", piplus_TOPPV_COV_, &b_piplus_TOPPV_COV_);
   fChain->SetBranchAddress("piplus_IP_TOPPV", &piplus_IP_TOPPV, &b_piplus_IP_TOPPV);
   fChain->SetBranchAddress("piplus_IPCHI2_TOPPV", &piplus_IPCHI2_TOPPV, &b_piplus_IPCHI2_TOPPV);
   fChain->SetBranchAddress("piplus_ORIVX_X", &piplus_ORIVX_X, &b_piplus_ORIVX_X);
   fChain->SetBranchAddress("piplus_ORIVX_Y", &piplus_ORIVX_Y, &b_piplus_ORIVX_Y);
   fChain->SetBranchAddress("piplus_ORIVX_Z", &piplus_ORIVX_Z, &b_piplus_ORIVX_Z);
   fChain->SetBranchAddress("piplus_ORIVX_XERR", &piplus_ORIVX_XERR, &b_piplus_ORIVX_XERR);
   fChain->SetBranchAddress("piplus_ORIVX_YERR", &piplus_ORIVX_YERR, &b_piplus_ORIVX_YERR);
   fChain->SetBranchAddress("piplus_ORIVX_ZERR", &piplus_ORIVX_ZERR, &b_piplus_ORIVX_ZERR);
   fChain->SetBranchAddress("piplus_ORIVX_CHI2", &piplus_ORIVX_CHI2, &b_piplus_ORIVX_CHI2);
   fChain->SetBranchAddress("piplus_ORIVX_NDOF", &piplus_ORIVX_NDOF, &b_piplus_ORIVX_NDOF);
   fChain->SetBranchAddress("piplus_ORIVX_COV_", piplus_ORIVX_COV_, &b_piplus_ORIVX_COV_);
   fChain->SetBranchAddress("piplus_IP_ORIVX", &piplus_IP_ORIVX, &b_piplus_IP_ORIVX);
   fChain->SetBranchAddress("piplus_IPCHI2_ORIVX", &piplus_IPCHI2_ORIVX, &b_piplus_IPCHI2_ORIVX);
   fChain->SetBranchAddress("piplus_P", &piplus_P, &b_piplus_P);
   fChain->SetBranchAddress("piplus_PT", &piplus_PT, &b_piplus_PT);
   fChain->SetBranchAddress("piplus_PE", &piplus_PE, &b_piplus_PE);
   fChain->SetBranchAddress("piplus_PX", &piplus_PX, &b_piplus_PX);
   fChain->SetBranchAddress("piplus_PY", &piplus_PY, &b_piplus_PY);
   fChain->SetBranchAddress("piplus_PZ", &piplus_PZ, &b_piplus_PZ);
   fChain->SetBranchAddress("piplus_REFPX", &piplus_REFPX, &b_piplus_REFPX);
   fChain->SetBranchAddress("piplus_REFPY", &piplus_REFPY, &b_piplus_REFPY);
   fChain->SetBranchAddress("piplus_REFPZ", &piplus_REFPZ, &b_piplus_REFPZ);
   fChain->SetBranchAddress("piplus_M", &piplus_M, &b_piplus_M);
   fChain->SetBranchAddress("piplus_AtVtx_PE", &piplus_AtVtx_PE, &b_piplus_AtVtx_PE);
   fChain->SetBranchAddress("piplus_AtVtx_PX", &piplus_AtVtx_PX, &b_piplus_AtVtx_PX);
   fChain->SetBranchAddress("piplus_AtVtx_PY", &piplus_AtVtx_PY, &b_piplus_AtVtx_PY);
   fChain->SetBranchAddress("piplus_AtVtx_PZ", &piplus_AtVtx_PZ, &b_piplus_AtVtx_PZ);
   fChain->SetBranchAddress("piplus_ID", &piplus_ID, &b_piplus_ID);
   fChain->SetBranchAddress("piplus_PIDe", &piplus_PIDe, &b_piplus_PIDe);
   fChain->SetBranchAddress("piplus_PIDmu", &piplus_PIDmu, &b_piplus_PIDmu);
   fChain->SetBranchAddress("piplus_PIDK", &piplus_PIDK, &b_piplus_PIDK);
   fChain->SetBranchAddress("piplus_PIDp", &piplus_PIDp, &b_piplus_PIDp);
   fChain->SetBranchAddress("piplus_ProbNNe", &piplus_ProbNNe, &b_piplus_ProbNNe);
   fChain->SetBranchAddress("piplus_ProbNNk", &piplus_ProbNNk, &b_piplus_ProbNNk);
   fChain->SetBranchAddress("piplus_ProbNNp", &piplus_ProbNNp, &b_piplus_ProbNNp);
   fChain->SetBranchAddress("piplus_ProbNNpi", &piplus_ProbNNpi, &b_piplus_ProbNNpi);
   fChain->SetBranchAddress("piplus_ProbNNmu", &piplus_ProbNNmu, &b_piplus_ProbNNmu);
   fChain->SetBranchAddress("piplus_ProbNNghost", &piplus_ProbNNghost, &b_piplus_ProbNNghost);
   fChain->SetBranchAddress("piplus_hasMuon", &piplus_hasMuon, &b_piplus_hasMuon);
   fChain->SetBranchAddress("piplus_isMuon", &piplus_isMuon, &b_piplus_isMuon);
   fChain->SetBranchAddress("piplus_hasRich", &piplus_hasRich, &b_piplus_hasRich);
   fChain->SetBranchAddress("piplus_UsedRichAerogel", &piplus_UsedRichAerogel, &b_piplus_UsedRichAerogel);
   fChain->SetBranchAddress("piplus_UsedRich1Gas", &piplus_UsedRich1Gas, &b_piplus_UsedRich1Gas);
   fChain->SetBranchAddress("piplus_UsedRich2Gas", &piplus_UsedRich2Gas, &b_piplus_UsedRich2Gas);
   fChain->SetBranchAddress("piplus_RichAboveElThres", &piplus_RichAboveElThres, &b_piplus_RichAboveElThres);
   fChain->SetBranchAddress("piplus_RichAboveMuThres", &piplus_RichAboveMuThres, &b_piplus_RichAboveMuThres);
   fChain->SetBranchAddress("piplus_RichAbovePiThres", &piplus_RichAbovePiThres, &b_piplus_RichAbovePiThres);
   fChain->SetBranchAddress("piplus_RichAboveKaThres", &piplus_RichAboveKaThres, &b_piplus_RichAboveKaThres);
   fChain->SetBranchAddress("piplus_RichAbovePrThres", &piplus_RichAbovePrThres, &b_piplus_RichAbovePrThres);
   fChain->SetBranchAddress("piplus_hasCalo", &piplus_hasCalo, &b_piplus_hasCalo);
   fChain->SetBranchAddress("piplus_L0Global_Dec", &piplus_L0Global_Dec, &b_piplus_L0Global_Dec);
   fChain->SetBranchAddress("piplus_L0Global_TIS", &piplus_L0Global_TIS, &b_piplus_L0Global_TIS);
   fChain->SetBranchAddress("piplus_L0Global_TOS", &piplus_L0Global_TOS, &b_piplus_L0Global_TOS);
   fChain->SetBranchAddress("piplus_Hlt1Global_Dec", &piplus_Hlt1Global_Dec, &b_piplus_Hlt1Global_Dec);
   fChain->SetBranchAddress("piplus_Hlt1Global_TIS", &piplus_Hlt1Global_TIS, &b_piplus_Hlt1Global_TIS);
   fChain->SetBranchAddress("piplus_Hlt1Global_TOS", &piplus_Hlt1Global_TOS, &b_piplus_Hlt1Global_TOS);
   fChain->SetBranchAddress("piplus_Hlt1Phys_Dec", &piplus_Hlt1Phys_Dec, &b_piplus_Hlt1Phys_Dec);
   fChain->SetBranchAddress("piplus_Hlt1Phys_TIS", &piplus_Hlt1Phys_TIS, &b_piplus_Hlt1Phys_TIS);
   fChain->SetBranchAddress("piplus_Hlt1Phys_TOS", &piplus_Hlt1Phys_TOS, &b_piplus_Hlt1Phys_TOS);
   fChain->SetBranchAddress("piplus_Hlt2Global_Dec", &piplus_Hlt2Global_Dec, &b_piplus_Hlt2Global_Dec);
   fChain->SetBranchAddress("piplus_Hlt2Global_TIS", &piplus_Hlt2Global_TIS, &b_piplus_Hlt2Global_TIS);
   fChain->SetBranchAddress("piplus_Hlt2Global_TOS", &piplus_Hlt2Global_TOS, &b_piplus_Hlt2Global_TOS);
   fChain->SetBranchAddress("piplus_Hlt2Phys_Dec", &piplus_Hlt2Phys_Dec, &b_piplus_Hlt2Phys_Dec);
   fChain->SetBranchAddress("piplus_Hlt2Phys_TIS", &piplus_Hlt2Phys_TIS, &b_piplus_Hlt2Phys_TIS);
   fChain->SetBranchAddress("piplus_Hlt2Phys_TOS", &piplus_Hlt2Phys_TOS, &b_piplus_Hlt2Phys_TOS);
   fChain->SetBranchAddress("piplus_L0DiMuonDecision_Dec", &piplus_L0DiMuonDecision_Dec, &b_piplus_L0DiMuonDecision_Dec);
   fChain->SetBranchAddress("piplus_L0DiMuonDecision_TIS", &piplus_L0DiMuonDecision_TIS, &b_piplus_L0DiMuonDecision_TIS);
   fChain->SetBranchAddress("piplus_L0DiMuonDecision_TOS", &piplus_L0DiMuonDecision_TOS, &b_piplus_L0DiMuonDecision_TOS);
   fChain->SetBranchAddress("piplus_L0ElectronDecision_Dec", &piplus_L0ElectronDecision_Dec, &b_piplus_L0ElectronDecision_Dec);
   fChain->SetBranchAddress("piplus_L0ElectronDecision_TIS", &piplus_L0ElectronDecision_TIS, &b_piplus_L0ElectronDecision_TIS);
   fChain->SetBranchAddress("piplus_L0ElectronDecision_TOS", &piplus_L0ElectronDecision_TOS, &b_piplus_L0ElectronDecision_TOS);
   fChain->SetBranchAddress("piplus_L0HadronDecision_Dec", &piplus_L0HadronDecision_Dec, &b_piplus_L0HadronDecision_Dec);
   fChain->SetBranchAddress("piplus_L0HadronDecision_TIS", &piplus_L0HadronDecision_TIS, &b_piplus_L0HadronDecision_TIS);
   fChain->SetBranchAddress("piplus_L0HadronDecision_TOS", &piplus_L0HadronDecision_TOS, &b_piplus_L0HadronDecision_TOS);
   fChain->SetBranchAddress("piplus_L0MuonDecision_Dec", &piplus_L0MuonDecision_Dec, &b_piplus_L0MuonDecision_Dec);
   fChain->SetBranchAddress("piplus_L0MuonDecision_TIS", &piplus_L0MuonDecision_TIS, &b_piplus_L0MuonDecision_TIS);
   fChain->SetBranchAddress("piplus_L0MuonDecision_TOS", &piplus_L0MuonDecision_TOS, &b_piplus_L0MuonDecision_TOS);
   fChain->SetBranchAddress("piplus_L0JetElDecision_Dec", &piplus_L0JetElDecision_Dec, &b_piplus_L0JetElDecision_Dec);
   fChain->SetBranchAddress("piplus_L0JetElDecision_TIS", &piplus_L0JetElDecision_TIS, &b_piplus_L0JetElDecision_TIS);
   fChain->SetBranchAddress("piplus_L0JetElDecision_TOS", &piplus_L0JetElDecision_TOS, &b_piplus_L0JetElDecision_TOS);
   fChain->SetBranchAddress("piplus_L0JetPhDecision_Dec", &piplus_L0JetPhDecision_Dec, &b_piplus_L0JetPhDecision_Dec);
   fChain->SetBranchAddress("piplus_L0JetPhDecision_TIS", &piplus_L0JetPhDecision_TIS, &b_piplus_L0JetPhDecision_TIS);
   fChain->SetBranchAddress("piplus_L0JetPhDecision_TOS", &piplus_L0JetPhDecision_TOS, &b_piplus_L0JetPhDecision_TOS);
   fChain->SetBranchAddress("piplus_L0MuonEWDecision_Dec", &piplus_L0MuonEWDecision_Dec, &b_piplus_L0MuonEWDecision_Dec);
   fChain->SetBranchAddress("piplus_L0MuonEWDecision_TIS", &piplus_L0MuonEWDecision_TIS, &b_piplus_L0MuonEWDecision_TIS);
   fChain->SetBranchAddress("piplus_L0MuonEWDecision_TOS", &piplus_L0MuonEWDecision_TOS, &b_piplus_L0MuonEWDecision_TOS);
   fChain->SetBranchAddress("piplus_L0PhotonDecision_Dec", &piplus_L0PhotonDecision_Dec, &b_piplus_L0PhotonDecision_Dec);
   fChain->SetBranchAddress("piplus_L0PhotonDecision_TIS", &piplus_L0PhotonDecision_TIS, &b_piplus_L0PhotonDecision_TIS);
   fChain->SetBranchAddress("piplus_L0PhotonDecision_TOS", &piplus_L0PhotonDecision_TOS, &b_piplus_L0PhotonDecision_TOS);
   fChain->SetBranchAddress("piplus_Hlt1TrackMVADecision_Dec", &piplus_Hlt1TrackMVADecision_Dec, &b_piplus_Hlt1TrackMVADecision_Dec);
   fChain->SetBranchAddress("piplus_Hlt1TrackMVADecision_TIS", &piplus_Hlt1TrackMVADecision_TIS, &b_piplus_Hlt1TrackMVADecision_TIS);
   fChain->SetBranchAddress("piplus_Hlt1TrackMVADecision_TOS", &piplus_Hlt1TrackMVADecision_TOS, &b_piplus_Hlt1TrackMVADecision_TOS);
   fChain->SetBranchAddress("piplus_Hlt1TrackMuonDecision_Dec", &piplus_Hlt1TrackMuonDecision_Dec, &b_piplus_Hlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("piplus_Hlt1TrackMuonDecision_TIS", &piplus_Hlt1TrackMuonDecision_TIS, &b_piplus_Hlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("piplus_Hlt1TrackMuonDecision_TOS", &piplus_Hlt1TrackMuonDecision_TOS, &b_piplus_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("piplus_Hlt1TwoTrackMVADecision_Dec", &piplus_Hlt1TwoTrackMVADecision_Dec, &b_piplus_Hlt1TwoTrackMVADecision_Dec);
   fChain->SetBranchAddress("piplus_Hlt1TwoTrackMVADecision_TIS", &piplus_Hlt1TwoTrackMVADecision_TIS, &b_piplus_Hlt1TwoTrackMVADecision_TIS);
   fChain->SetBranchAddress("piplus_Hlt1TwoTrackMVADecision_TOS", &piplus_Hlt1TwoTrackMVADecision_TOS, &b_piplus_Hlt1TwoTrackMVADecision_TOS);
   fChain->SetBranchAddress("piplus_Hlt2B2HH_B2HHDecision_Dec", &piplus_Hlt2B2HH_B2HHDecision_Dec, &b_piplus_Hlt2B2HH_B2HHDecision_Dec);
   fChain->SetBranchAddress("piplus_Hlt2B2HH_B2HHDecision_TIS", &piplus_Hlt2B2HH_B2HHDecision_TIS, &b_piplus_Hlt2B2HH_B2HHDecision_TIS);
   fChain->SetBranchAddress("piplus_Hlt2B2HH_B2HHDecision_TOS", &piplus_Hlt2B2HH_B2HHDecision_TOS, &b_piplus_Hlt2B2HH_B2HHDecision_TOS);
   fChain->SetBranchAddress("piplus_Hlt2B2HHDecision_Dec", &piplus_Hlt2B2HHDecision_Dec, &b_piplus_Hlt2B2HHDecision_Dec);
   fChain->SetBranchAddress("piplus_Hlt2B2HHDecision_TIS", &piplus_Hlt2B2HHDecision_TIS, &b_piplus_Hlt2B2HHDecision_TIS);
   fChain->SetBranchAddress("piplus_Hlt2B2HHDecision_TOS", &piplus_Hlt2B2HHDecision_TOS, &b_piplus_Hlt2B2HHDecision_TOS);
   fChain->SetBranchAddress("piplus_Hlt2Topo2BodyDecision_Dec", &piplus_Hlt2Topo2BodyDecision_Dec, &b_piplus_Hlt2Topo2BodyDecision_Dec);
   fChain->SetBranchAddress("piplus_Hlt2Topo2BodyDecision_TIS", &piplus_Hlt2Topo2BodyDecision_TIS, &b_piplus_Hlt2Topo2BodyDecision_TIS);
   fChain->SetBranchAddress("piplus_Hlt2Topo2BodyDecision_TOS", &piplus_Hlt2Topo2BodyDecision_TOS, &b_piplus_Hlt2Topo2BodyDecision_TOS);
   fChain->SetBranchAddress("piplus_TRACK_Type", &piplus_TRACK_Type, &b_piplus_TRACK_Type);
   fChain->SetBranchAddress("piplus_TRACK_Key", &piplus_TRACK_Key, &b_piplus_TRACK_Key);
   fChain->SetBranchAddress("piplus_TRACK_CHI2NDOF", &piplus_TRACK_CHI2NDOF, &b_piplus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("piplus_TRACK_PCHI2", &piplus_TRACK_PCHI2, &b_piplus_TRACK_PCHI2);
   fChain->SetBranchAddress("piplus_TRACK_MatchCHI2", &piplus_TRACK_MatchCHI2, &b_piplus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("piplus_TRACK_GhostProb", &piplus_TRACK_GhostProb, &b_piplus_TRACK_GhostProb);
   fChain->SetBranchAddress("piplus_TRACK_CloneDist", &piplus_TRACK_CloneDist, &b_piplus_TRACK_CloneDist);
   fChain->SetBranchAddress("piplus_TRACK_Likelihood", &piplus_TRACK_Likelihood, &b_piplus_TRACK_Likelihood);
   fChain->SetBranchAddress("piminus_DOCA", &piminus_DOCA, &b_piminus_DOCA);
   fChain->SetBranchAddress("piminus_RichPIDk", &piminus_RichPIDk, &b_piminus_RichPIDk);
   fChain->SetBranchAddress("piminus_RichPIDp", &piminus_RichPIDp, &b_piminus_RichPIDp);
   // fChain->SetBranchAddress("piminus_MC12TuneV2_ProbNNe", &piminus_MC12TuneV2_ProbNNe, &b_piminus_MC12TuneV2_ProbNNe);
   // fChain->SetBranchAddress("piminus_MC12TuneV2_ProbNNmu", &piminus_MC12TuneV2_ProbNNmu, &b_piminus_MC12TuneV2_ProbNNmu);
   // fChain->SetBranchAddress("piminus_MC12TuneV2_ProbNNpi", &piminus_MC12TuneV2_ProbNNpi, &b_piminus_MC12TuneV2_ProbNNpi);
   // fChain->SetBranchAddress("piminus_MC12TuneV2_ProbNNk", &piminus_MC12TuneV2_ProbNNk, &b_piminus_MC12TuneV2_ProbNNk);
   // fChain->SetBranchAddress("piminus_MC12TuneV2_ProbNNp", &piminus_MC12TuneV2_ProbNNp, &b_piminus_MC12TuneV2_ProbNNp);
   // fChain->SetBranchAddress("piminus_MC12TuneV2_ProbNNghost", &piminus_MC12TuneV2_ProbNNghost, &b_piminus_MC12TuneV2_ProbNNghost);
   // fChain->SetBranchAddress("piminus_MC12TuneV3_ProbNNe", &piminus_MC12TuneV3_ProbNNe, &b_piminus_MC12TuneV3_ProbNNe);
   // fChain->SetBranchAddress("piminus_MC12TuneV3_ProbNNmu", &piminus_MC12TuneV3_ProbNNmu, &b_piminus_MC12TuneV3_ProbNNmu);
   // fChain->SetBranchAddress("piminus_MC12TuneV3_ProbNNpi", &piminus_MC12TuneV3_ProbNNpi, &b_piminus_MC12TuneV3_ProbNNpi);
   // fChain->SetBranchAddress("piminus_MC12TuneV3_ProbNNk", &piminus_MC12TuneV3_ProbNNk, &b_piminus_MC12TuneV3_ProbNNk);
   // fChain->SetBranchAddress("piminus_MC12TuneV3_ProbNNp", &piminus_MC12TuneV3_ProbNNp, &b_piminus_MC12TuneV3_ProbNNp);
   // fChain->SetBranchAddress("piminus_MC12TuneV3_ProbNNghost", &piminus_MC12TuneV3_ProbNNghost, &b_piminus_MC12TuneV3_ProbNNghost);
   // fChain->SetBranchAddress("piminus_MC12TuneV4_ProbNNe", &piminus_MC12TuneV4_ProbNNe, &b_piminus_MC12TuneV4_ProbNNe);
   // fChain->SetBranchAddress("piminus_MC12TuneV4_ProbNNmu", &piminus_MC12TuneV4_ProbNNmu, &b_piminus_MC12TuneV4_ProbNNmu);
   // fChain->SetBranchAddress("piminus_MC12TuneV4_ProbNNpi", &piminus_MC12TuneV4_ProbNNpi, &b_piminus_MC12TuneV4_ProbNNpi);
   // fChain->SetBranchAddress("piminus_MC12TuneV4_ProbNNk", &piminus_MC12TuneV4_ProbNNk, &b_piminus_MC12TuneV4_ProbNNk);
   // fChain->SetBranchAddress("piminus_MC12TuneV4_ProbNNp", &piminus_MC12TuneV4_ProbNNp, &b_piminus_MC12TuneV4_ProbNNp);
   // fChain->SetBranchAddress("piminus_MC12TuneV4_ProbNNghost", &piminus_MC12TuneV4_ProbNNghost, &b_piminus_MC12TuneV4_ProbNNghost);
   // fChain->SetBranchAddress("piminus_MC15TuneV1_ProbNNe", &piminus_MC15TuneV1_ProbNNe, &b_piminus_MC15TuneV1_ProbNNe);
   // fChain->SetBranchAddress("piminus_MC15TuneV1_ProbNNmu", &piminus_MC15TuneV1_ProbNNmu, &b_piminus_MC15TuneV1_ProbNNmu);
   // fChain->SetBranchAddress("piminus_MC15TuneV1_ProbNNpi", &piminus_MC15TuneV1_ProbNNpi, &b_piminus_MC15TuneV1_ProbNNpi);
   // fChain->SetBranchAddress("piminus_MC15TuneV1_ProbNNk", &piminus_MC15TuneV1_ProbNNk, &b_piminus_MC15TuneV1_ProbNNk);
   // fChain->SetBranchAddress("piminus_MC15TuneV1_ProbNNp", &piminus_MC15TuneV1_ProbNNp, &b_piminus_MC15TuneV1_ProbNNp);
   // fChain->SetBranchAddress("piminus_MC15TuneV1_ProbNNghost", &piminus_MC15TuneV1_ProbNNghost, &b_piminus_MC15TuneV1_ProbNNghost);
   fChain->SetBranchAddress("piminus_MINIP", &piminus_MINIP, &b_piminus_MINIP);
   fChain->SetBranchAddress("piminus_MINIPCHI2", &piminus_MINIPCHI2, &b_piminus_MINIPCHI2);
   fChain->SetBranchAddress("piminus_MINIPNEXTBEST", &piminus_MINIPNEXTBEST, &b_piminus_MINIPNEXTBEST);
   fChain->SetBranchAddress("piminus_MINIPCHI2NEXTBEST", &piminus_MINIPCHI2NEXTBEST, &b_piminus_MINIPCHI2NEXTBEST);
   fChain->SetBranchAddress("piminus_OWNPV_X", &piminus_OWNPV_X, &b_piminus_OWNPV_X);
   fChain->SetBranchAddress("piminus_OWNPV_Y", &piminus_OWNPV_Y, &b_piminus_OWNPV_Y);
   fChain->SetBranchAddress("piminus_OWNPV_Z", &piminus_OWNPV_Z, &b_piminus_OWNPV_Z);
   fChain->SetBranchAddress("piminus_OWNPV_XERR", &piminus_OWNPV_XERR, &b_piminus_OWNPV_XERR);
   fChain->SetBranchAddress("piminus_OWNPV_YERR", &piminus_OWNPV_YERR, &b_piminus_OWNPV_YERR);
   fChain->SetBranchAddress("piminus_OWNPV_ZERR", &piminus_OWNPV_ZERR, &b_piminus_OWNPV_ZERR);
   fChain->SetBranchAddress("piminus_OWNPV_CHI2", &piminus_OWNPV_CHI2, &b_piminus_OWNPV_CHI2);
   fChain->SetBranchAddress("piminus_OWNPV_NDOF", &piminus_OWNPV_NDOF, &b_piminus_OWNPV_NDOF);
   fChain->SetBranchAddress("piminus_OWNPV_COV_", piminus_OWNPV_COV_, &b_piminus_OWNPV_COV_);
   fChain->SetBranchAddress("piminus_IP_OWNPV", &piminus_IP_OWNPV, &b_piminus_IP_OWNPV);
   fChain->SetBranchAddress("piminus_IPCHI2_OWNPV", &piminus_IPCHI2_OWNPV, &b_piminus_IPCHI2_OWNPV);
   fChain->SetBranchAddress("piminus_TOPPV_X", &piminus_TOPPV_X, &b_piminus_TOPPV_X);
   fChain->SetBranchAddress("piminus_TOPPV_Y", &piminus_TOPPV_Y, &b_piminus_TOPPV_Y);
   fChain->SetBranchAddress("piminus_TOPPV_Z", &piminus_TOPPV_Z, &b_piminus_TOPPV_Z);
   fChain->SetBranchAddress("piminus_TOPPV_XERR", &piminus_TOPPV_XERR, &b_piminus_TOPPV_XERR);
   fChain->SetBranchAddress("piminus_TOPPV_YERR", &piminus_TOPPV_YERR, &b_piminus_TOPPV_YERR);
   fChain->SetBranchAddress("piminus_TOPPV_ZERR", &piminus_TOPPV_ZERR, &b_piminus_TOPPV_ZERR);
   fChain->SetBranchAddress("piminus_TOPPV_CHI2", &piminus_TOPPV_CHI2, &b_piminus_TOPPV_CHI2);
   fChain->SetBranchAddress("piminus_TOPPV_NDOF", &piminus_TOPPV_NDOF, &b_piminus_TOPPV_NDOF);
   fChain->SetBranchAddress("piminus_TOPPV_COV_", piminus_TOPPV_COV_, &b_piminus_TOPPV_COV_);
   fChain->SetBranchAddress("piminus_IP_TOPPV", &piminus_IP_TOPPV, &b_piminus_IP_TOPPV);
   fChain->SetBranchAddress("piminus_IPCHI2_TOPPV", &piminus_IPCHI2_TOPPV, &b_piminus_IPCHI2_TOPPV);
   fChain->SetBranchAddress("piminus_ORIVX_X", &piminus_ORIVX_X, &b_piminus_ORIVX_X);
   fChain->SetBranchAddress("piminus_ORIVX_Y", &piminus_ORIVX_Y, &b_piminus_ORIVX_Y);
   fChain->SetBranchAddress("piminus_ORIVX_Z", &piminus_ORIVX_Z, &b_piminus_ORIVX_Z);
   fChain->SetBranchAddress("piminus_ORIVX_XERR", &piminus_ORIVX_XERR, &b_piminus_ORIVX_XERR);
   fChain->SetBranchAddress("piminus_ORIVX_YERR", &piminus_ORIVX_YERR, &b_piminus_ORIVX_YERR);
   fChain->SetBranchAddress("piminus_ORIVX_ZERR", &piminus_ORIVX_ZERR, &b_piminus_ORIVX_ZERR);
   fChain->SetBranchAddress("piminus_ORIVX_CHI2", &piminus_ORIVX_CHI2, &b_piminus_ORIVX_CHI2);
   fChain->SetBranchAddress("piminus_ORIVX_NDOF", &piminus_ORIVX_NDOF, &b_piminus_ORIVX_NDOF);
   fChain->SetBranchAddress("piminus_ORIVX_COV_", piminus_ORIVX_COV_, &b_piminus_ORIVX_COV_);
   fChain->SetBranchAddress("piminus_IP_ORIVX", &piminus_IP_ORIVX, &b_piminus_IP_ORIVX);
   fChain->SetBranchAddress("piminus_IPCHI2_ORIVX", &piminus_IPCHI2_ORIVX, &b_piminus_IPCHI2_ORIVX);
   fChain->SetBranchAddress("piminus_P", &piminus_P, &b_piminus_P);
   fChain->SetBranchAddress("piminus_PT", &piminus_PT, &b_piminus_PT);
   fChain->SetBranchAddress("piminus_PE", &piminus_PE, &b_piminus_PE);
   fChain->SetBranchAddress("piminus_PX", &piminus_PX, &b_piminus_PX);
   fChain->SetBranchAddress("piminus_PY", &piminus_PY, &b_piminus_PY);
   fChain->SetBranchAddress("piminus_PZ", &piminus_PZ, &b_piminus_PZ);
   fChain->SetBranchAddress("piminus_REFPX", &piminus_REFPX, &b_piminus_REFPX);
   fChain->SetBranchAddress("piminus_REFPY", &piminus_REFPY, &b_piminus_REFPY);
   fChain->SetBranchAddress("piminus_REFPZ", &piminus_REFPZ, &b_piminus_REFPZ);
   fChain->SetBranchAddress("piminus_M", &piminus_M, &b_piminus_M);
   fChain->SetBranchAddress("piminus_AtVtx_PE", &piminus_AtVtx_PE, &b_piminus_AtVtx_PE);
   fChain->SetBranchAddress("piminus_AtVtx_PX", &piminus_AtVtx_PX, &b_piminus_AtVtx_PX);
   fChain->SetBranchAddress("piminus_AtVtx_PY", &piminus_AtVtx_PY, &b_piminus_AtVtx_PY);
   fChain->SetBranchAddress("piminus_AtVtx_PZ", &piminus_AtVtx_PZ, &b_piminus_AtVtx_PZ);
   fChain->SetBranchAddress("piminus_ID", &piminus_ID, &b_piminus_ID);
   fChain->SetBranchAddress("piminus_PIDe", &piminus_PIDe, &b_piminus_PIDe);
   fChain->SetBranchAddress("piminus_PIDmu", &piminus_PIDmu, &b_piminus_PIDmu);
   fChain->SetBranchAddress("piminus_PIDK", &piminus_PIDK, &b_piminus_PIDK);
   fChain->SetBranchAddress("piminus_PIDp", &piminus_PIDp, &b_piminus_PIDp);
   fChain->SetBranchAddress("piminus_ProbNNe", &piminus_ProbNNe, &b_piminus_ProbNNe);
   fChain->SetBranchAddress("piminus_ProbNNk", &piminus_ProbNNk, &b_piminus_ProbNNk);
   fChain->SetBranchAddress("piminus_ProbNNp", &piminus_ProbNNp, &b_piminus_ProbNNp);
   fChain->SetBranchAddress("piminus_ProbNNpi", &piminus_ProbNNpi, &b_piminus_ProbNNpi);
   fChain->SetBranchAddress("piminus_ProbNNmu", &piminus_ProbNNmu, &b_piminus_ProbNNmu);
   fChain->SetBranchAddress("piminus_ProbNNghost", &piminus_ProbNNghost, &b_piminus_ProbNNghost);
   fChain->SetBranchAddress("piminus_hasMuon", &piminus_hasMuon, &b_piminus_hasMuon);
   fChain->SetBranchAddress("piminus_isMuon", &piminus_isMuon, &b_piminus_isMuon);
   fChain->SetBranchAddress("piminus_hasRich", &piminus_hasRich, &b_piminus_hasRich);
   fChain->SetBranchAddress("piminus_UsedRichAerogel", &piminus_UsedRichAerogel, &b_piminus_UsedRichAerogel);
   fChain->SetBranchAddress("piminus_UsedRich1Gas", &piminus_UsedRich1Gas, &b_piminus_UsedRich1Gas);
   fChain->SetBranchAddress("piminus_UsedRich2Gas", &piminus_UsedRich2Gas, &b_piminus_UsedRich2Gas);
   fChain->SetBranchAddress("piminus_RichAboveElThres", &piminus_RichAboveElThres, &b_piminus_RichAboveElThres);
   fChain->SetBranchAddress("piminus_RichAboveMuThres", &piminus_RichAboveMuThres, &b_piminus_RichAboveMuThres);
   fChain->SetBranchAddress("piminus_RichAbovePiThres", &piminus_RichAbovePiThres, &b_piminus_RichAbovePiThres);
   fChain->SetBranchAddress("piminus_RichAboveKaThres", &piminus_RichAboveKaThres, &b_piminus_RichAboveKaThres);
   fChain->SetBranchAddress("piminus_RichAbovePrThres", &piminus_RichAbovePrThres, &b_piminus_RichAbovePrThres);
   fChain->SetBranchAddress("piminus_hasCalo", &piminus_hasCalo, &b_piminus_hasCalo);
   fChain->SetBranchAddress("piminus_L0Global_Dec", &piminus_L0Global_Dec, &b_piminus_L0Global_Dec);
   fChain->SetBranchAddress("piminus_L0Global_TIS", &piminus_L0Global_TIS, &b_piminus_L0Global_TIS);
   fChain->SetBranchAddress("piminus_L0Global_TOS", &piminus_L0Global_TOS, &b_piminus_L0Global_TOS);
   fChain->SetBranchAddress("piminus_Hlt1Global_Dec", &piminus_Hlt1Global_Dec, &b_piminus_Hlt1Global_Dec);
   fChain->SetBranchAddress("piminus_Hlt1Global_TIS", &piminus_Hlt1Global_TIS, &b_piminus_Hlt1Global_TIS);
   fChain->SetBranchAddress("piminus_Hlt1Global_TOS", &piminus_Hlt1Global_TOS, &b_piminus_Hlt1Global_TOS);
   fChain->SetBranchAddress("piminus_Hlt1Phys_Dec", &piminus_Hlt1Phys_Dec, &b_piminus_Hlt1Phys_Dec);
   fChain->SetBranchAddress("piminus_Hlt1Phys_TIS", &piminus_Hlt1Phys_TIS, &b_piminus_Hlt1Phys_TIS);
   fChain->SetBranchAddress("piminus_Hlt1Phys_TOS", &piminus_Hlt1Phys_TOS, &b_piminus_Hlt1Phys_TOS);
   fChain->SetBranchAddress("piminus_Hlt2Global_Dec", &piminus_Hlt2Global_Dec, &b_piminus_Hlt2Global_Dec);
   fChain->SetBranchAddress("piminus_Hlt2Global_TIS", &piminus_Hlt2Global_TIS, &b_piminus_Hlt2Global_TIS);
   fChain->SetBranchAddress("piminus_Hlt2Global_TOS", &piminus_Hlt2Global_TOS, &b_piminus_Hlt2Global_TOS);
   fChain->SetBranchAddress("piminus_Hlt2Phys_Dec", &piminus_Hlt2Phys_Dec, &b_piminus_Hlt2Phys_Dec);
   fChain->SetBranchAddress("piminus_Hlt2Phys_TIS", &piminus_Hlt2Phys_TIS, &b_piminus_Hlt2Phys_TIS);
   fChain->SetBranchAddress("piminus_Hlt2Phys_TOS", &piminus_Hlt2Phys_TOS, &b_piminus_Hlt2Phys_TOS);
   fChain->SetBranchAddress("piminus_L0DiMuonDecision_Dec", &piminus_L0DiMuonDecision_Dec, &b_piminus_L0DiMuonDecision_Dec);
   fChain->SetBranchAddress("piminus_L0DiMuonDecision_TIS", &piminus_L0DiMuonDecision_TIS, &b_piminus_L0DiMuonDecision_TIS);
   fChain->SetBranchAddress("piminus_L0DiMuonDecision_TOS", &piminus_L0DiMuonDecision_TOS, &b_piminus_L0DiMuonDecision_TOS);
   fChain->SetBranchAddress("piminus_L0ElectronDecision_Dec", &piminus_L0ElectronDecision_Dec, &b_piminus_L0ElectronDecision_Dec);
   fChain->SetBranchAddress("piminus_L0ElectronDecision_TIS", &piminus_L0ElectronDecision_TIS, &b_piminus_L0ElectronDecision_TIS);
   fChain->SetBranchAddress("piminus_L0ElectronDecision_TOS", &piminus_L0ElectronDecision_TOS, &b_piminus_L0ElectronDecision_TOS);
   fChain->SetBranchAddress("piminus_L0HadronDecision_Dec", &piminus_L0HadronDecision_Dec, &b_piminus_L0HadronDecision_Dec);
   fChain->SetBranchAddress("piminus_L0HadronDecision_TIS", &piminus_L0HadronDecision_TIS, &b_piminus_L0HadronDecision_TIS);
   fChain->SetBranchAddress("piminus_L0HadronDecision_TOS", &piminus_L0HadronDecision_TOS, &b_piminus_L0HadronDecision_TOS);
   fChain->SetBranchAddress("piminus_L0MuonDecision_Dec", &piminus_L0MuonDecision_Dec, &b_piminus_L0MuonDecision_Dec);
   fChain->SetBranchAddress("piminus_L0MuonDecision_TIS", &piminus_L0MuonDecision_TIS, &b_piminus_L0MuonDecision_TIS);
   fChain->SetBranchAddress("piminus_L0MuonDecision_TOS", &piminus_L0MuonDecision_TOS, &b_piminus_L0MuonDecision_TOS);
   fChain->SetBranchAddress("piminus_L0JetElDecision_Dec", &piminus_L0JetElDecision_Dec, &b_piminus_L0JetElDecision_Dec);
   fChain->SetBranchAddress("piminus_L0JetElDecision_TIS", &piminus_L0JetElDecision_TIS, &b_piminus_L0JetElDecision_TIS);
   fChain->SetBranchAddress("piminus_L0JetElDecision_TOS", &piminus_L0JetElDecision_TOS, &b_piminus_L0JetElDecision_TOS);
   fChain->SetBranchAddress("piminus_L0JetPhDecision_Dec", &piminus_L0JetPhDecision_Dec, &b_piminus_L0JetPhDecision_Dec);
   fChain->SetBranchAddress("piminus_L0JetPhDecision_TIS", &piminus_L0JetPhDecision_TIS, &b_piminus_L0JetPhDecision_TIS);
   fChain->SetBranchAddress("piminus_L0JetPhDecision_TOS", &piminus_L0JetPhDecision_TOS, &b_piminus_L0JetPhDecision_TOS);
   fChain->SetBranchAddress("piminus_L0MuonEWDecision_Dec", &piminus_L0MuonEWDecision_Dec, &b_piminus_L0MuonEWDecision_Dec);
   fChain->SetBranchAddress("piminus_L0MuonEWDecision_TIS", &piminus_L0MuonEWDecision_TIS, &b_piminus_L0MuonEWDecision_TIS);
   fChain->SetBranchAddress("piminus_L0MuonEWDecision_TOS", &piminus_L0MuonEWDecision_TOS, &b_piminus_L0MuonEWDecision_TOS);
   fChain->SetBranchAddress("piminus_L0PhotonDecision_Dec", &piminus_L0PhotonDecision_Dec, &b_piminus_L0PhotonDecision_Dec);
   fChain->SetBranchAddress("piminus_L0PhotonDecision_TIS", &piminus_L0PhotonDecision_TIS, &b_piminus_L0PhotonDecision_TIS);
   fChain->SetBranchAddress("piminus_L0PhotonDecision_TOS", &piminus_L0PhotonDecision_TOS, &b_piminus_L0PhotonDecision_TOS);
   fChain->SetBranchAddress("piminus_Hlt1TrackMVADecision_Dec", &piminus_Hlt1TrackMVADecision_Dec, &b_piminus_Hlt1TrackMVADecision_Dec);
   fChain->SetBranchAddress("piminus_Hlt1TrackMVADecision_TIS", &piminus_Hlt1TrackMVADecision_TIS, &b_piminus_Hlt1TrackMVADecision_TIS);
   fChain->SetBranchAddress("piminus_Hlt1TrackMVADecision_TOS", &piminus_Hlt1TrackMVADecision_TOS, &b_piminus_Hlt1TrackMVADecision_TOS);
   fChain->SetBranchAddress("piminus_Hlt1TrackMuonDecision_Dec", &piminus_Hlt1TrackMuonDecision_Dec, &b_piminus_Hlt1TrackMuonDecision_Dec);
   fChain->SetBranchAddress("piminus_Hlt1TrackMuonDecision_TIS", &piminus_Hlt1TrackMuonDecision_TIS, &b_piminus_Hlt1TrackMuonDecision_TIS);
   fChain->SetBranchAddress("piminus_Hlt1TrackMuonDecision_TOS", &piminus_Hlt1TrackMuonDecision_TOS, &b_piminus_Hlt1TrackMuonDecision_TOS);
   fChain->SetBranchAddress("piminus_Hlt1TwoTrackMVADecision_Dec", &piminus_Hlt1TwoTrackMVADecision_Dec, &b_piminus_Hlt1TwoTrackMVADecision_Dec);
   fChain->SetBranchAddress("piminus_Hlt1TwoTrackMVADecision_TIS", &piminus_Hlt1TwoTrackMVADecision_TIS, &b_piminus_Hlt1TwoTrackMVADecision_TIS);
   fChain->SetBranchAddress("piminus_Hlt1TwoTrackMVADecision_TOS", &piminus_Hlt1TwoTrackMVADecision_TOS, &b_piminus_Hlt1TwoTrackMVADecision_TOS);
   fChain->SetBranchAddress("piminus_Hlt2B2HH_B2HHDecision_Dec", &piminus_Hlt2B2HH_B2HHDecision_Dec, &b_piminus_Hlt2B2HH_B2HHDecision_Dec);
   fChain->SetBranchAddress("piminus_Hlt2B2HH_B2HHDecision_TIS", &piminus_Hlt2B2HH_B2HHDecision_TIS, &b_piminus_Hlt2B2HH_B2HHDecision_TIS);
   fChain->SetBranchAddress("piminus_Hlt2B2HH_B2HHDecision_TOS", &piminus_Hlt2B2HH_B2HHDecision_TOS, &b_piminus_Hlt2B2HH_B2HHDecision_TOS);
   fChain->SetBranchAddress("piminus_Hlt2B2HHDecision_Dec", &piminus_Hlt2B2HHDecision_Dec, &b_piminus_Hlt2B2HHDecision_Dec);
   fChain->SetBranchAddress("piminus_Hlt2B2HHDecision_TIS", &piminus_Hlt2B2HHDecision_TIS, &b_piminus_Hlt2B2HHDecision_TIS);
   fChain->SetBranchAddress("piminus_Hlt2B2HHDecision_TOS", &piminus_Hlt2B2HHDecision_TOS, &b_piminus_Hlt2B2HHDecision_TOS);
   fChain->SetBranchAddress("piminus_Hlt2Topo2BodyDecision_Dec", &piminus_Hlt2Topo2BodyDecision_Dec, &b_piminus_Hlt2Topo2BodyDecision_Dec);
   fChain->SetBranchAddress("piminus_Hlt2Topo2BodyDecision_TIS", &piminus_Hlt2Topo2BodyDecision_TIS, &b_piminus_Hlt2Topo2BodyDecision_TIS);
   fChain->SetBranchAddress("piminus_Hlt2Topo2BodyDecision_TOS", &piminus_Hlt2Topo2BodyDecision_TOS, &b_piminus_Hlt2Topo2BodyDecision_TOS);
   fChain->SetBranchAddress("piminus_TRACK_Type", &piminus_TRACK_Type, &b_piminus_TRACK_Type);
   fChain->SetBranchAddress("piminus_TRACK_Key", &piminus_TRACK_Key, &b_piminus_TRACK_Key);
   fChain->SetBranchAddress("piminus_TRACK_CHI2NDOF", &piminus_TRACK_CHI2NDOF, &b_piminus_TRACK_CHI2NDOF);
   fChain->SetBranchAddress("piminus_TRACK_PCHI2", &piminus_TRACK_PCHI2, &b_piminus_TRACK_PCHI2);
   fChain->SetBranchAddress("piminus_TRACK_MatchCHI2", &piminus_TRACK_MatchCHI2, &b_piminus_TRACK_MatchCHI2);
   fChain->SetBranchAddress("piminus_TRACK_GhostProb", &piminus_TRACK_GhostProb, &b_piminus_TRACK_GhostProb);
   fChain->SetBranchAddress("piminus_TRACK_CloneDist", &piminus_TRACK_CloneDist, &b_piminus_TRACK_CloneDist);
   fChain->SetBranchAddress("piminus_TRACK_Likelihood", &piminus_TRACK_Likelihood, &b_piminus_TRACK_Likelihood);
   fChain->SetBranchAddress("nCandidate", &nCandidate, &b_nCandidate);
   fChain->SetBranchAddress("totCandidates", &totCandidates, &b_totCandidates);
   fChain->SetBranchAddress("EventInSequence", &EventInSequence, &b_EventInSequence);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("BCID", &BCID, &b_BCID);
   fChain->SetBranchAddress("BCType", &BCType, &b_BCType);
   fChain->SetBranchAddress("OdinTCK", &OdinTCK, &b_OdinTCK);
   fChain->SetBranchAddress("L0DUTCK", &L0DUTCK, &b_L0DUTCK);
   fChain->SetBranchAddress("HLT1TCK", &HLT1TCK, &b_HLT1TCK);
   fChain->SetBranchAddress("HLT2TCK", &HLT2TCK, &b_HLT2TCK);
   fChain->SetBranchAddress("GpsTime", &GpsTime, &b_GpsTime);
   fChain->SetBranchAddress("Polarity", &Polarity, &b_Polarity);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("PVX", PVX, &b_PVX);
   fChain->SetBranchAddress("PVY", PVY, &b_PVY);
   fChain->SetBranchAddress("PVZ", PVZ, &b_PVZ);
   fChain->SetBranchAddress("PVXERR", PVXERR, &b_PVXERR);
   fChain->SetBranchAddress("PVYERR", PVYERR, &b_PVYERR);
   fChain->SetBranchAddress("PVZERR", PVZERR, &b_PVZERR);
   fChain->SetBranchAddress("PVCHI2", PVCHI2, &b_PVCHI2);
   fChain->SetBranchAddress("PVNDOF", PVNDOF, &b_PVNDOF);
   fChain->SetBranchAddress("PVNTRACKS", PVNTRACKS, &b_PVNTRACKS);
   fChain->SetBranchAddress("nPVs", &nPVs, &b_nPVs);
   fChain->SetBranchAddress("nTracks", &nTracks, &b_nTracks);
   fChain->SetBranchAddress("nLongTracks", &nLongTracks, &b_nLongTracks);
   fChain->SetBranchAddress("nDownstreamTracks", &nDownstreamTracks, &b_nDownstreamTracks);
   fChain->SetBranchAddress("nUpstreamTracks", &nUpstreamTracks, &b_nUpstreamTracks);
   fChain->SetBranchAddress("nVeloTracks", &nVeloTracks, &b_nVeloTracks);
   fChain->SetBranchAddress("nTTracks", &nTTracks, &b_nTTracks);
   fChain->SetBranchAddress("nBackTracks", &nBackTracks, &b_nBackTracks);
   fChain->SetBranchAddress("nRich1Hits", &nRich1Hits, &b_nRich1Hits);
   fChain->SetBranchAddress("nRich2Hits", &nRich2Hits, &b_nRich2Hits);
   fChain->SetBranchAddress("nVeloClusters", &nVeloClusters, &b_nVeloClusters);
   fChain->SetBranchAddress("nITClusters", &nITClusters, &b_nITClusters);
   fChain->SetBranchAddress("nTTClusters", &nTTClusters, &b_nTTClusters);
   fChain->SetBranchAddress("nOTClusters", &nOTClusters, &b_nOTClusters);
   fChain->SetBranchAddress("nSPDHits", &nSPDHits, &b_nSPDHits);
   fChain->SetBranchAddress("nMuonCoordsS0", &nMuonCoordsS0, &b_nMuonCoordsS0);
   fChain->SetBranchAddress("nMuonCoordsS1", &nMuonCoordsS1, &b_nMuonCoordsS1);
   fChain->SetBranchAddress("nMuonCoordsS2", &nMuonCoordsS2, &b_nMuonCoordsS2);
   fChain->SetBranchAddress("nMuonCoordsS3", &nMuonCoordsS3, &b_nMuonCoordsS3);
   fChain->SetBranchAddress("nMuonCoordsS4", &nMuonCoordsS4, &b_nMuonCoordsS4);
   fChain->SetBranchAddress("nMuonTracks", &nMuonTracks, &b_nMuonTracks);
   Notify();
}

Bool_t sel::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void sel::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t sel::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef sel_cxx
