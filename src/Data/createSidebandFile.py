import ROOT
import os 
import argparse
import sys
# Create the argument parser


# Add argument for selecting the model
parser = argparse.ArgumentParser(description="Pcreating separate sideband files")
parser.add_argument('-y', '--year', required=True, type=str, help="year ('2015', '2016', '2017s29r2p2', '2018').")
parser.add_argument('-m', '--magnet',   required=True, type=str, choices=["Up","Down"],help="Magnet ('Up' or 'Down').")
args = parser.parse_args()

year = args.year
magnet = args.magnet

b2hh_out = os.environ.get('B2HH_OUT')

# Open input file and get the tree
input_file = ROOT.TFile.Open(f"{b2hh_out}/Data/tuple_merged/b2hh_{year}_{magnet}.root")
input_tree = input_file.Get("b2hh")

# Apply a cut (e.g., keep only entries where 'mass' > 3.0)
cut = "massPIPI>5.6 && massPIPI<5.8" #only the mass range, no PID cuts (later)

# Create output file and clone the tree with the cut
output_file = ROOT.TFile(f"{b2hh_out}/Data/tuple_merged/sideband_b2hh_{year}_{magnet}.root", "RECREATE")
filtered_tree = input_tree.CopyTree(cut)

# Write the new tree to the output file
output_file.cd()
filtered_tree.Write()
output_file.Close()
input_file.Close()