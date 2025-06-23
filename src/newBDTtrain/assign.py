#python assign.py -c bspipi -y 2018 -p Tot

#chunk assigner ONLY FOR OPTIMISATION
#assign the BDT values to the trees (assign all the trained models so that we can optimise the selection on all of them at the same time and choose the best one at the end)
#since the chunks are already processed there, i think the best is to load the models inside the chunk loop

#to do:
#need to change the name with the new variables, remove the redundancy of the single ids
#assign to the reweighted bspipi files, the -> on top of the previous selection

import uproot
import numpy as np
import pandas as pd
from joblib import load

#import ROOT

def create_directory(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)
        print(f"Directory '{directory}' created.")
    else:
        print(f"Directory '{directory}' already exists.")

#def process_tree(input_file, tree_name, model_path, output_file, chunk_size=100000):
def process_tree(input_file, tree_name, model_path, models_list, output_file, chunk_size=100000):
 
    try:
        print(f"Processing tree {input_file} in chunks...", flush=True)

        with uproot.open(input_file) as file:
            tree = file[tree_name]
            treeSize = tree.num_entries
            models_num = len(models_list)

            model = load(f"{model_path}/{models_list[0]}/1.joblib")
            feature_names = model.feature_names_in_
            print(f"Feature names: {feature_names}") #just to be sure

            # Initialize the output file and tree
            with uproot.recreate(output_file) as new_file:
                # Create an empty dictionary to hold the columns for the new tree
                new_tree = {}

                # Loop through the tree in chunks
                for start in range(0, treeSize, chunk_size):
                    stop = min(start + chunk_size, treeSize)

                    # Extract the current chunk of data

                    chunk = tree.arrays(library="np", entry_start=start, entry_stop=stop)

                    #columns = ["BDTtrain_ptB0","BDTtrain_logfdchi2B0","BDTtrain_ipchi2B0",
                    #           "BDTtrain_vtxchi2","BDTtrain_doca","BDTtrain_logmaxchi2ip",
                    #           "BDTtrain_maxpt","BDTtrain_logminchi2ip","BDTtrain_minpt"]
                    #final_features = chunkpd[columns]
                    
                    # Stack the final features for model prediction

                    """
                    final_features = np.column_stack([
                        chunk["BDTtrain_ptB0"],
                        chunk["BDTtrain_logfdchi2B0"],
                        chunk["BDTtrain_ipchi2B0"],
                        chunk["BDTtrain_vtxchi2"],
                        chunk["BDTtrain_doca"],
                        chunk["BDTtrain_logmaxchi2ip"],
                        chunk["BDTtrain_maxpt"],
                        chunk["BDTtrain_logminchi2ip"],
                        chunk["BDTtrain_minpt"]
                    ])
                    """
                    
                    final_features = pd.DataFrame({name: chunk[name] for name in feature_names})
                    
                    new_chunk = {k: chunk[k] for k in chunk.keys()}

                    for i in range(models_num):
                        # Load the models -> postponed to add multiple models
                        print(f"Events {start}: Loading models {models_list[i]} from {model_path}")
                        model1 = load(f"{model_path}/{models_list[i]}/1.joblib")
                        model2 = load(f"{model_path}/{models_list[i]}/2.joblib")
                        model3 = load(f"{model_path}/{models_list[i]}/3.joblib")

                        # Get model predictions
                        bdt_values1 = model1.predict_proba(final_features)[:, 1]
                        bdt_values2 = model2.predict_proba(final_features)[:, 1]
                        bdt_values3 = model3.predict_proba(final_features)[:, 1]

                        # Assign BDT values based on the condition
                        conditions = [
                            (chunk["idBDT"] == 1),  # idBDT == 1, use model3
                            (chunk["idBDT"] == 2),  # idBDT == 2, use model1
                            (chunk["idBDT"] == 3)   # idBDT == 3, use model2
                        ]
                        choices = [bdt_values3, bdt_values1, bdt_values2]
                        graBDT = np.select(conditions, choices, default=np.nan)

                        new_chunk[f"bdt{models_list[i]}"] = graBDT  #adding the different BDT values 

                    # Write the chunk to the new ROOT file
                    if not new_tree:
                        # Initialize the tree structure in the new file
                        new_tree = new_chunk
                    else:
                        # Add the new columns to the tree incrementally
                        for key, value in new_chunk.items():
                            new_tree[key] = np.concatenate([new_tree[key], value]) if key in new_tree else value

                # Create the TTree in the new file
                new_file[tree_name] = new_tree

        print(f"Modified tree saved to {output_file}", flush=True)

    except Exception as e:
        print(f"Error processing the tree: {e}")



import argparse
import sys
# Create the argument parser

parser = argparse.ArgumentParser(description="Program to process input arguments for the model.")
parser.add_argument('-c', '--channel', required=True, type=str, help="channel (b2hh, bspipi, sideband_b2hh etc)")
parser.add_argument('-y', '--year', required=True, type=str,help="year (2015,2016,2017s29r2p2,2018)")
parser.add_argument('-p', '--polarity', required=True, type=str, help="magnet (Up or Down)")
args = parser.parse_args()



import os

b2hh_out = os.environ.get('B2HH_OUT')
input_path = f"{b2hh_out}"
output_path = f"{b2hh_out}/newBDTtrain/forNorm/temp/"
create_directory(output_path)

#output_path = "/home/ceph/mcaporal/b2hhRew/out/Data/BDTAdded630Compatibility"
#print('trying to add the k630 bit compatibility') #fixed in compatibilityBitFix.cpp

# Access the parsed arguments
channel = args.channel
year = args.year
polarity = args.polarity

input_file = ""

if channel == "bspipi":
    input_path = f"{b2hh_out}/AccSignal/kineWeight/"
    input_file = f"{input_path}/{channel}_pipi_PIPI_0_{year}_{polarity}_Kine.root"
else:
    input_path = f"{b2hh_out}/Data/tuple_merged/"
    input_file = f"{input_path}/{channel}_{year}_{polarity}.root"




models_list = ["gradient_300_3", "gradient_300_4", "gradient_300_5", "gradient_300_6",
               "gradient_400_3", "gradient_400_4", "gradient_400_5", "gradient_400_6",
               "gradient_500_3", "gradient_500_4", "gradient_500_5", "gradient_500_6",
               "gradient_600_3", "gradient_600_4", "gradient_600_5", "gradient_600_6",
               "gradient_700_3", "gradient_700_4", "gradient_700_5", "gradient_700_6"]

#models_list = ["gradient_10_3", "gradient_10_4"]

process_tree(
                input_file=input_file,
                tree_name="b2hh",
                model_path=f"{b2hh_out}/newBDTtrain/models/",
                models_list=models_list,
                output_file=f"{output_path}/{channel}_{year}_{polarity}.root"
            )