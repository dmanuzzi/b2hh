import ROOT
import os
import argparse


parser = argparse.ArgumentParser()
parser.add_argument('-d','--data', nargs='+', dest = 'data')
parser.add_argument('-y','--year', type = str, dest = 'year')
parser.add_argument('-m','--magnet', type = str, dest = 'magnet')
parser.add_argument('-n','--name', type = str, dest = 'name', default = 'b2hh')
parser.add_argument('-c','--code', type = str, dest = 'code', default = 'sel')
parser.add_argument('-i','--index', type = int, dest = 'index')
args = parser.parse_args()

inputs = []
for inputFile in args.data:
  fin = open(inputFile, 'r')
  inputs += fin.read().split('\n')[:-1]
  fin.close()
print 'Analysing file', inputs

ROOT.gROOT.ProcessLine('.L $B2HH_SRC/Data/%s.C'%(args.code))
chain = ROOT.TChain('Signal_Tuple/DecayTree')

for inputFile in inputs: 
  chain.Add(inputFile)

sel = __import__('ROOT.%s'%args.code,globals(),locals(),['%s'%args.code])
plot = sel(chain,args.name,args.year,args.magnet,args.index)
plot.Loop()

