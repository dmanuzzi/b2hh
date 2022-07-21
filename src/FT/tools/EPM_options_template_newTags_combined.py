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
OS_Charm_BranchDec       = "qOS"
OS_Charm_BranchProb      = "etaOS"

OS_Electron_Use          = 1
OS_Electron_BranchDec    = "qSS"
OS_Electron_BranchProb   = "etaSS"

