########
# DATA #
########

# This is the file/directory that you want to run
# Multiple files can be specified by setting NumFiles = N
# and then setting RootFile_1, RootFile_2, ..., RootFile_N

# NumFiles = 2
# RootFile_1 = "{nfin1}"
# RootFile_2 = "{nfin2}"
TupleName = "DecayTree"
Nmax = -1  # Events to run, -1 means all

########################
# CALIBRATION SETTINGS #
########################

#CalibrationMode = "{B}"
DoCalibrations = 1
CalibrationLink = "MISTAG"
CalibrationDegree = 1
CalibrationModel = "POLY"
UseNewtonRaphson = 0 #use MINUIT

##########################
# PLOTTING               #
##########################

PlotLabel = "LHCb"
PlotTitle = 1
PlotExtension = ".pdf"
PlotStatBox = 0

##########################
# DECAY TIME             #
##########################

#Resolution
UseTau                    = 1
UseTauErr                 = 1
ResolutionGaussian1_A     = 1.0262e-05
ResolutionGaussian1_B     = 1.28
TauUnits                  = "ps"
BranchTau                 = "BeautyTime"
BranchTauErr              = "BeautyTimeErr"
DrawOscillationPlots      = 1

#Physics (all in ps, ps^-1 etc... always!!!)
#DeltaM = 17.761
#Lifetime = 1.512
#DeltaGamma = 0.0913
#DeltaM = 0.5065
#Lifetime = 1.527
#DeltaGamma = 0.000001
##########################
# BRANCH NAMES AND TYPES #
##########################
BranchID                 = "lab0_ID"
UseWeight                = 1
WeightFormula            = "sWeight*wPT"

OS_Charm_Use             = 1
OS_Charm_BranchDec       = "lab0_OSCharm_TAGDEC"
OS_Charm_BranchProb      = "lab0_OSCharm_TAGETA"

OS_Electron_Use          = 1
OS_Electron_BranchDec    = "lab0_OSElectron_TAGDEC"
OS_Electron_BranchProb   = "lab0_OSElectron_TAGETA"

OS_Kaon_Use              = 1 
OS_Kaon_BranchDec        = "lab0_OSKaon_TAGDEC"
OS_Kaon_BranchProb       = "lab0_OSKaon_TAGETA"

OS_Muon_Use              = 1
OS_Muon_BranchDec        = "lab0_OSMuon_TAGDEC"
OS_Muon_BranchProb       = "lab0_OSMuon_TAGETA"

VtxCharge_Use            = 1
VtxCharge_BranchDec      = "lab0_OSVtxCh_TAGDEC"
VtxCharge_BranchProb     = "lab0_OSVtxCh_TAGETA"

SS_Kaon_Use              = 1
SS_Kaon_BranchDec        = "lab0_SSKaon_TAGDEC"
SS_Kaon_BranchProb       = "lab0_SSKaon_TAGETA"

SS_Pion_Use              = 1
SS_Pion_BranchDec        = "lab0_SSPion_TAGDEC"
SS_Pion_BranchProb       = "lab0_SSPion_TAGETA"

SS_Proton_Use            = 1        
SS_Proton_BranchDec      = "lab0_SSProton_TAGDEC"
SS_Proton_BranchProb     = "lab0_SSProton_TAGETA"
