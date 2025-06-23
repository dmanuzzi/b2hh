#python train.py -m $1 -i $2 -t $3 -d $4  #model [gradient], idBDT [1,2,3], trees, tree depth 

#train on top of previous selection -> bspipi is already cut in bdtPIPI, should do the same also for the background (add it here)

import argparse
import sys
# Create the argument parser
calls = 0 
def get_memory_usage():
    global calls
    with open("/proc/self/status") as f:
        for line in f:
            if line.startswith("VmRSS:"):
                pkb = int(line.split()[1])
                gb = pkb / (1024 ** 2)
                print(f"{calls}: Memory usage (Resident Set): {gb:.4f} GB")
                calls += 1
                break
                

get_memory_usage()


# Add argument for selecting the model
parser = argparse.ArgumentParser(description="Program to process input arguments for the model.")
parser.add_argument('-m', '--model', required=True, type=str, choices=["gradient"], help="Type of model (e.g., 'xgboost', 'randomforest').")
parser.add_argument('-i', '--id', required=True, type=int, choices=[1, 2, 3],help="Model ID (1, 2, or 3).")
parser.add_argument('-t', '--trees', required=True, type=int, help="Number of trees (e.g., 100, 200).")
parser.add_argument('-d', '--depth', required=True, type=int, help="Depth of trees (e.g., 5, 10).")
args = parser.parse_args()


# Access the parsed arguments
selected_model = args.model
id = args.id
numTrees = args.trees
depth = args.depth

print(f"Selected model: {selected_model}")
print(f"total of {numTrees} trees and {depth} depth")
print(f"for idBDT: {id}")

import os

#b2hh_home = os.environ.get('B2HH_HOME')
b2hh_out = os.environ.get('B2HH_OUT')

def create_directory(directory):
    if not os.path.exists(directory):
        os.makedirs(directory,exist_ok=True)
        print(f"Directory '{directory}' created.")
    else:
        print(f"Directory '{directory}' already exists.")

models_directory = f"{b2hh_out}/newBDTtrain/models/{selected_model}_{numTrees}_{depth}"
output_directory = f"{b2hh_out}/newBDTtrain/plots/{selected_model}_{numTrees}_{depth}"

create_directory(output_directory)
create_directory(models_directory)
create_directory(f"{b2hh_out}/newBDTtrain/plots/{selected_model}_{numTrees}_{depth}/{id}")

from joblib import dump, load

import pandas as pd
import numpy as np
import math

import ROOT
import uproot
import sys

import matplotlib.pyplot as plt

print("make sure you are on the 128 GB ram machines -> up to 40 GB may be required")
print("performing BDT training of the acc signal reweighted bspipis over loose preselection")

bdtNum=1

bdtNum = id

bdtTargetSet=2

bdtTargetSet=id+1
if bdtTargetSet == 4:
    bdtTargetSet = 1

selectString       = f'idBDT=={bdtNum}'              #do not use weight here
selectStringSignal = f'idBDT=={bdtNum} and weight>0'
print("This code will perform the training on idBDT =",bdtNum)

##selectTargetString = f'idBDT=={bdtTargetSet}'
##selectTargetStringSignal = f'idBDT=={bdtTargetSet} and weight>0' #add also the cut on PID for the signal

selectTargetString       = f'idBDT=={bdtTargetSet}'               #do not use weight here
selectTargetStringSignal = f'idBDT=={bdtTargetSet} and weight>0 ' # and piplusDLLKPI<-1 and piminusDLLKPI<-1 and piplusDLLPPI<3 and piminusDLLPPI<3 #removed PID requirements, in the signal the requirements already act in the PID reweighting

print("Target set has idBDT =",bdtTargetSet)

sidebandString = "bdtPIPI>0 and massPIPI>5.6 and massPIPI<6.19 and piplusDLLKPI<-1 and piminusDLLKPI<-1 and piplusDLLPPI<3 and piminusDLLPPI<3" # and piplusDLLKPI<-2 and piminusDLLKPI<-2 and piplusDLLPPI<3 and piminusDLLPPI<3
#PID cuts on the sideband, PID is applied on the MC via the reweighting

######################################################################################################################################################################
#Signal 
######################################################################################################################################################################

print("Testing full dataset...",flush=True)
print("opening MCs for the signal...",flush=True)

branchesToLoad_signal = ["idBDT",
                         "BDTtrain_minpt","BDTtrain_logminchi2ip","BDTtrain_maxpt","BDTtrain_logmaxchi2ip",
                         "BDTtrain_doca","BDTtrain_vtxchi2","BDTtrain_ipchi2B0","BDTtrain_logfdchi2B0","BDTtrain_ptB0",
                        "weight","massPIPI"]
                        #"piplusDLLKPI","piminusDLLKPI","piplusDLLPPI","piminusDLLPPI","massPIPI"] #["idBDT","bDOCA","bVTXCHI2","bIPCHI2","bFDCHI2","bPT"] #["idBDT"]
mcFiles = [
    f"{b2hh_out}/AccSignal/kineWeight/bspipi_pipi_PIPI_0_201516_Tot_Kine.root",
    f"{b2hh_out}/AccSignal/kineWeight/bspipi_pipi_PIPI_0_2017s29r2p2_Tot_Kine.root",
    f"{b2hh_out}/AccSignal/kineWeight/bspipi_pipi_PIPI_0_2018_Tot_Kine.root",
    ]
treeName = "b2hh"

print("attempt concat",flush=True)


signalChain = uproot.concatenate(
    {f: treeName for f in mcFiles},
    filter_name=branchesToLoad_signal,
    library="pd"  # optional, gets NumPy arrays
)


signal = signalChain.query(selectStringSignal).copy()  
tsignal = signalChain.query(selectTargetString).copy() 

signal["classifyTag"]=1 #tell this is the signal 
print(signal)
signalEntrySum = signal["weight"].sum()
print("weight sum of  sig (rw)  ", signalEntrySum) ##how many entries we have

#signalFinal = signal[["idBDT","bPT","logbFDCHI2","bIPCHI2","bVTXCHI2","bDOCA","logMaxPiIPCHI2","maxpiPT","logMinPiIPCHI2","minpiPT","weight","classifyTag"]]
signalFinal = signal[["idBDT","BDTtrain_ptB0","BDTtrain_logfdchi2B0","BDTtrain_ipchi2B0","BDTtrain_vtxchi2","BDTtrain_doca",
                        "BDTtrain_logmaxchi2ip","BDTtrain_maxpt","BDTtrain_logminchi2ip","BDTtrain_minpt",
                        "weight","classifyTag"]]

tsignal["classifyTag"]=1 #tell this is the signal also on the target 
tsignalEntrySum = tsignal["weight"].sum()
print("weight sum of tsig (rw)  ", tsignalEntrySum) ##how many entries we have

#signalFinal = signal[["idBDT","bPT","logbFDCHI2","bIPCHI2","bVTXCHI2","bDOCA","logMaxPiIPCHI2","maxpiPT","logMinPiIPCHI2","minpiPT","weight","classifyTag"]]
tsignalFinal = tsignal[["idBDT","BDTtrain_ptB0","BDTtrain_logfdchi2B0","BDTtrain_ipchi2B0","BDTtrain_vtxchi2","BDTtrain_doca",
                        "BDTtrain_logmaxchi2ip","BDTtrain_maxpt","BDTtrain_logminchi2ip","BDTtrain_minpt",
                        "weight","classifyTag"]]


######################################################################################################################################################################
#BACKGROUND
######################################################################################################################################################################

print("opening Bkg for the signal...",flush=True)


branchesToLoad_sideband = ["idBDT",
                         "BDTtrain_minpt","BDTtrain_logminchi2ip","BDTtrain_maxpt","BDTtrain_logmaxchi2ip",
                         "BDTtrain_doca","BDTtrain_vtxchi2","BDTtrain_ipchi2B0","BDTtrain_logfdchi2B0","BDTtrain_ptB0",
                         #"weight",  #no weight here
                         "piplusDLLKPI","piminusDLLKPI","piplusDLLPPI","piminusDLLPPI","massPIPI","bdtPIPI"] #["idBDT","bDOCA","bVTXCHI2","bIPCHI2","bFDCHI2","bPT"] #["idBDT"]
get_memory_usage()

#best solution to avoid loading millions of useless events
dataFiles = [
    f"{b2hh_out}/Data/tuple_merged/sideband_b2hh_2015_Up.root",
    f"{b2hh_out}/Data/tuple_merged/sideband_b2hh_2015_Down.root",
    f"{b2hh_out}/Data/tuple_merged/sideband_b2hh_2016_Up.root",
    f"{b2hh_out}/Data/tuple_merged/sideband_b2hh_2016_Down.root",
    f"{b2hh_out}/Data/tuple_merged/sideband_b2hh_2017s29r2p2_Up.root",
    f"{b2hh_out}/Data/tuple_merged/sideband_b2hh_2017s29r2p2_Down.root",
    f"{b2hh_out}/Data/tuple_merged/sideband_b2hh_2018_Up.root",
    f"{b2hh_out}/Data/tuple_merged/sideband_b2hh_2018_Down.root",
    ]
treeName = "b2hh"

get_memory_usage()

bkgChain = uproot.concatenate(
    {f: treeName for f in dataFiles},
    filter_name=branchesToLoad_sideband,
    library="pd"  # optional, gets NumPy arrays
)
bkg = bkgChain.query(f"{selectString} and {sidebandString}").copy() 
tbkg = bkgChain.query(f"{selectTargetString} and {sidebandString}").copy()
print(bkgChain)
print(bkg)
print(tbkg)

bkg["weight"] = 10  #balancing the training
tbkg["weight"] = 10

bkg["classifyTag"]=0

tbkg["classifyTag"]=0

bkgEntrySum = bkg["weight"].sum()
tbkgEntrySum = tbkg["weight"].sum()
print("weight sum of bkg       ", bkgEntrySum)
print("weight sum of tbkg      ", tbkgEntrySum)

trainRation = bkgEntrySum / signalEntrySum
print("training balance (best if close to 1)",trainRation, flush=True)

get_memory_usage()

bkgChain = 0 # deallocate the monster, hope it does not crash eheh

bkgFinal  =  bkg[["idBDT","BDTtrain_ptB0","BDTtrain_logfdchi2B0","BDTtrain_ipchi2B0","BDTtrain_vtxchi2","BDTtrain_doca",
                        "BDTtrain_logmaxchi2ip","BDTtrain_maxpt","BDTtrain_logminchi2ip","BDTtrain_minpt",
                        "weight","classifyTag"]]


tbkgFinal = tbkg[["idBDT","BDTtrain_ptB0","BDTtrain_logfdchi2B0","BDTtrain_ipchi2B0","BDTtrain_vtxchi2","BDTtrain_doca",
                        "BDTtrain_logmaxchi2ip","BDTtrain_maxpt","BDTtrain_logminchi2ip","BDTtrain_minpt",
                        "weight","classifyTag"]]

get_memory_usage()


#from sklearn.datasets import make_hastie_10_2
from sklearn.ensemble import GradientBoostingClassifier
#from sklearn.ensemble import AdaBoostClassifier
#from sklearn.metrics import confusion_matrix
#from sklearn.metrics import roc_curve, auc


training_set = pd.concat([signalFinal, bkgFinal], ignore_index=True)
target_set   = pd.concat([tsignalFinal, tbkgFinal], ignore_index=True)
training_set = training_set.sample(frac=1,random_state=69) #randomize the combined set
print(training_set)

#features ready for training
features = training_set[["BDTtrain_ptB0","BDTtrain_logfdchi2B0","BDTtrain_ipchi2B0","BDTtrain_vtxchi2","BDTtrain_doca","BDTtrain_logmaxchi2ip","BDTtrain_maxpt","BDTtrain_logminchi2ip","BDTtrain_minpt"]]
target = training_set["classifyTag"]
weight = training_set["weight"]

#tfeatures ready for training
tfeatures = target_set[["BDTtrain_ptB0","BDTtrain_logfdchi2B0","BDTtrain_ipchi2B0","BDTtrain_vtxchi2","BDTtrain_doca","BDTtrain_logmaxchi2ip","BDTtrain_maxpt","BDTtrain_logminchi2ip","BDTtrain_minpt"]]
ttarget = target_set["classifyTag"]
tweight = target_set["weight"]


print(f'training {numTrees} (it may be the time to go fetch a coffee)...',flush=True)
clf = 0

if selected_model == 'gradient':
    clf = GradientBoostingClassifier(n_estimators=numTrees, learning_rate=0.1 ,max_depth=depth, random_state=1, verbose = 1).fit(features, target, weight) # this learning rate may be too high -> tmva goes for 0.001 #500 at 1.0 trees took 40 min to run
if selected_model == 'adaboost':
    clf = AdaBoostClassifier(n_estimators=numTrees, learning_rate=0.15 , random_state=1).fit(features, target, weight) # this learning rate may be too high -> tmva goes for 0.001 #500 at 1.0 trees took 40 min to run    

modelFile = f'{models_directory}/{bdtNum}.joblib'
dump(clf, modelFile)
print("model saved to", modelFile)
print("", flush=True)

print("Accuracies:    (very naive method for first estimation)")
accuracy = clf.score(features,target,weight)#
print(f'TRAINING: Accuracy of model {bdtNum} on {bdtNum}', accuracy)

taccuracy = clf.score(tfeatures,ttarget,tweight)#
print(f'TEST:     Accuracy of model {bdtNum} on {bdtTargetSet}', taccuracy)



###################################################################################






#some plotting to verify we are doing things correctly

"""
predictClassBDT = clf.predict_proba(tfeatures)
print("predicted probabilities for target sample")
predictOutBDT = predictClassBDT[:, 1]
tcombined_set=tcombined_set.copy()
tcombined_set[f"{selected_model}_{numTrees}_{depth}"]=predictOutBDT
setOut = {key: tcombined_set[key].values for key in ["idBDT","bPT","logbFDCHI2","bIPCHI2","bVTXCHI2","bDOCA","logMaxPiIPCHI2","maxpiPT","logMinPiIPCHI2","minpiPT","weight","piplusDLLKPI","piminusDLLKPI","piplusDLLPPI","piminusDLLPPI","massPIPI","classifyTag","outBDT"]}
rdfSetOut = ROOT.RDF.FromNumpy(setOut)
#outTreeDir = f'/home/LHCB-T3/caporale/b2hh/out/newTrees/addBDT/bspipi_trainedwithBDT{bdtNum}.root'
#rdfSetOut.Snapshot('b2hh', outTreeDir)
#print("reduced tree saved:",outTreeDir)
"""


print("assignments for plotting")
signalForResponse = signalFinal[["BDTtrain_ptB0","BDTtrain_logfdchi2B0","BDTtrain_ipchi2B0","BDTtrain_vtxchi2","BDTtrain_doca",
                                 "BDTtrain_logmaxchi2ip","BDTtrain_maxpt","BDTtrain_logminchi2ip","BDTtrain_minpt"]]
predictProbaForSignal = clf.predict_proba(signalForResponse)
positiveClassProbabilitiesSig = predictProbaForSignal[:, 1]

bkgForResponse = bkgFinal[["BDTtrain_ptB0","BDTtrain_logfdchi2B0","BDTtrain_ipchi2B0","BDTtrain_vtxchi2","BDTtrain_doca",
                           "BDTtrain_logmaxchi2ip","BDTtrain_maxpt","BDTtrain_logminchi2ip","BDTtrain_minpt"]] # bkg->bkg_cut
predictProbaForBkg = clf.predict_proba(bkgForResponse)
positiveClassProbabilitiesBkg = predictProbaForBkg[:, 1]

tsignalForResponse = tsignalFinal[["BDTtrain_ptB0","BDTtrain_logfdchi2B0","BDTtrain_ipchi2B0","BDTtrain_vtxchi2","BDTtrain_doca",
                                 "BDTtrain_logmaxchi2ip","BDTtrain_maxpt","BDTtrain_logminchi2ip","BDTtrain_minpt"]]
tpredictProbaForSignal = clf.predict_proba(tsignalForResponse)
tpositiveClassProbabilitiesSig = tpredictProbaForSignal[:, 1]

tbkgForResponse = tbkgFinal[["BDTtrain_ptB0","BDTtrain_logfdchi2B0","BDTtrain_ipchi2B0","BDTtrain_vtxchi2","BDTtrain_doca",
                            "BDTtrain_logmaxchi2ip","BDTtrain_maxpt","BDTtrain_logminchi2ip","BDTtrain_minpt"]] # bkg->bkg_cut
tpredictProbaForBkg = clf.predict_proba(tbkgForResponse)
tpositiveClassProbabilitiesBkg = tpredictProbaForBkg[:, 1]


print("Now doing the plots...")
bins = np.linspace(0,1,100) 
colors = ['orange','blue']

plt.figure()
plt.hist([positiveClassProbabilitiesSig,tpositiveClassProbabilitiesSig],bins,weights=[signalFinal["weight"],tsignalFinal["weight"]], label=[f'training{bdtNum}',f'test{bdtTargetSet}'], color = colors, density=True)
plt.legend(loc='upper left')
plt.suptitle(f'Signal Response BDT{bdtNum}')
outPlotDirectorySig = f'{output_directory}/{bdtNum}/{selected_model}_idBDT{bdtNum}_{numTrees}_{depth}_SigResponse.pdf'
plt.savefig(outPlotDirectorySig)
print("see sig training response with: evince", outPlotDirectorySig)


plt.figure()
plt.hist([positiveClassProbabilitiesSig,tpositiveClassProbabilitiesSig],bins,weights=[signalFinal["weight"],tsignalFinal["weight"]], label=[f'training{bdtNum}',f'test{bdtTargetSet}'], color = colors, density=True)
plt.legend(loc='upper left')
plt.yscale('log')
plt.suptitle(f'Signal Response BDT{bdtNum}')
outPlotDirectorySigLog = f'{output_directory}/{bdtNum}/{selected_model}_idBDT{bdtNum}_{numTrees}_{depth}_SigResponseLog.pdf'
plt.savefig(outPlotDirectorySigLog)
print("see sig training response with: evince", outPlotDirectorySigLog)

plt.figure()
plt.hist([positiveClassProbabilitiesBkg,tpositiveClassProbabilitiesBkg],bins,label=[f'training{bdtNum}',f'test{bdtTargetSet}'],color = colors, density=True)
plt.legend(loc='upper right')
plt.suptitle(f'Background Response BDT{bdtNum}')
outPlotDirectoryBkg = f'{output_directory}/{bdtNum}/{selected_model}_idBDT{bdtNum}_{numTrees}_{depth}_BkgResponse.pdf'
plt.savefig(outPlotDirectoryBkg)
print("see bkg training response with: evince", outPlotDirectoryBkg)


plt.figure()
plt.hist([positiveClassProbabilitiesBkg,tpositiveClassProbabilitiesBkg],bins,label=[f'training{bdtNum}',f'test{bdtTargetSet}'],color = colors, density=True)
plt.legend(loc='upper right')
plt.yscale('log')
plt.suptitle(f'Background Response BDT{bdtNum}')
outPlotDirectoryBkgLog = f'{output_directory}/{bdtNum}/{selected_model}_idBDT{bdtNum}_{numTrees}_{depth}_BkgLogResponse.pdf'
plt.savefig(outPlotDirectoryBkgLog)
print("see bkg training response with: evince", outPlotDirectoryBkgLog)




###################################################################################
from sklearn.metrics import roc_curve, auc
from scipy.stats import ks_2samp

# ROC curves for TRAIN and TEST
train_scores = clf.predict_proba(features)[:, 1]
test_scores = clf.predict_proba(tfeatures)[:, 1]

fpr_train, tpr_train, _ = roc_curve(target, train_scores, sample_weight=weight)
fpr_test, tpr_test, _ = roc_curve(ttarget, test_scores, sample_weight=tweight)

auc_train = auc(fpr_train, tpr_train)
auc_test = auc(fpr_test, tpr_test)

plt.figure()
plt.plot(fpr_train, tpr_train, label=f"Train ROC (AUC = {auc_train:.3f})", color='darkorange')
plt.plot(fpr_test, tpr_test, label=f"Test ROC (AUC = {auc_test:.3f})", color='blue')
plt.plot([0, 1], [0, 1], 'k--')
plt.xlabel("False Positive Rate")
plt.ylabel("True Positive Rate")
plt.title(f"ROC Curve BDT{bdtNum}")
plt.legend(loc="lower right")
plt.grid(True)
outPlotROC = f"{output_directory}/{bdtNum}/{selected_model}_idBDT{bdtNum}_{numTrees}_{depth}_ROCcurve.pdf"
plt.savefig(outPlotROC)
print("ROC curve saved:", outPlotROC)

# KS Test: Compare classifier outputs for signal train vs test
sig_train = positiveClassProbabilitiesSig
sig_test = tpositiveClassProbabilitiesSig

ks_stat, ks_pvalue = ks_2samp(sig_train, sig_test)
print(f"KS Statistic Sig: {ks_stat:.4f}, p-value: {ks_pvalue:.4g}")

plt.figure()
plt.hist(sig_train, bins=bins, weights=signalFinal["weight"], alpha=0.8, label="Train Signal", color="orange", density=True)
plt.hist(sig_test, bins=bins, weights=tsignalFinal["weight"], alpha=0.4, label="Test Signal", color="blue", density=True)
plt.xlabel("BDT Output")
plt.ylabel("Normalized Entries")
plt.title(f"KS Test for Overtraining\nKS Stat={ks_stat:.3f}, p={ks_pvalue:.2g}")
plt.legend()
outPlotKS = f"{output_directory}/{bdtNum}/{selected_model}_idBDT{bdtNum}_{numTrees}_{depth}_KSSig_overtrain.pdf"
plt.savefig(outPlotKS)
print("KS plot saved:", outPlotKS)

# KS Test: Compare classifier outputs for bkg train vs test
bkg_train = positiveClassProbabilitiesBkg
bkg_test = tpositiveClassProbabilitiesBkg

ks_statBkg, ks_pvalueBkg = ks_2samp(bkg_train, bkg_test)
print(f"KS Statistic Bkg: {ks_statBkg:.4f}, p-value: {ks_pvalueBkg:.4g}")

plt.figure()
plt.hist(bkg_train, bins=bins, alpha=0.8, label="Train Bkg", color="orange", density=True)
plt.hist(bkg_test, bins=bins, alpha=0.4, label="Test Bkg", color="blue", density=True)
plt.xlabel("BDT Output")
plt.ylabel("Normalized Entries")
plt.title(f"KS Test for Overtraining\nKS Stat={ks_statBkg:.3f}, p={ks_pvalueBkg:.2g}")
plt.legend()
outPlotKSBkg = f"{output_directory}/{bdtNum}/{selected_model}_idBDT{bdtNum}_{numTrees}_{depth}_KSBkg_overtrain.pdf"
plt.savefig(outPlotKSBkg)
print("KS plot saved:", outPlotKSBkg)

# printing list of possible issues?

results_file = f"{output_directory}/{bdtNum}/{selected_model}_{bdtNum}_{numTrees}_{depth}_metrics.txt"
with open(results_file, "w") as f:
    f.write(f"AUC (train): {auc_train:.8f}\n")
    f.write(f"AUC (test):  {auc_test:.8f}\n")
    f.write("Signal\n")
    f.write(f"-KS Statistic: {ks_stat:.8f}\n")
    f.write(f"-KS p-value: {ks_pvalue:.8f}\n")
    f.write("Bkg\n")
    f.write(f"-KS Statistic: {ks_statBkg:.8f}\n")
    f.write(f"-KS p-value: {ks_pvalueBkg:.8f}\n")

print("Metrics written to", results_file)


importances = clf.feature_importances_
feature_names = ["ptB0","logfdchi2B0","ipchi2B0","vtxchi2","doca","logmaxchi2ip","maxpt","logminchi2ip","minpt"]

plt.figure(figsize=(10, 6))
plt.barh(feature_names, importances, color='skyblue')
plt.xlabel('Feature Importance')
plt.title(f'Feature Importances BDT{bdtNum}')
plt.tight_layout()

importance_plot_path = f"{output_directory}/{bdtNum}/feature_importance_{selected_model}_idBDT{bdtNum}_{numTrees}_{depth}.pdf"
plt.savefig(importance_plot_path)
print(f"Feature importance plot saved to {importance_plot_path}")