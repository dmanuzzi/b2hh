#!/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_84/Python/2.7.10/x86_64-slc6-gcc48-opt/bin/python

import os
import sqlite3 as sql

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-i','--inputFile', type = str, dest = 'inputFile', default = 'pidEffs.db')
parser.add_argument('-o','-outDir', type = str, dest = 'outDir', default = './')
parser.add_argument('-f','--fState', type = str, dest = 'fState', default = 'kk')
parser.add_argument('-c','--pidCuts', type = str, dest = 'pidCuts', default = '2.-2.2.-2')
parser.add_argument('-y','--year', type = str, dest = 'year', default = '201516')
parser.add_argument('-m','--magnet', type = str, dest = 'magnet', default = 'Tot')
parser.add_argument('-n','--bdtName', type = str, dest = 'bdtName', default = 'KK')
parser.add_argument('-b','--bdtCut', type = str, dest = 'bdtCut', default = '0.04')
args = parser.parse_args()

pidEffs = sql.connect(args.inputFile)
curs = pidEffs.cursor()


decays = ['bdkpi','bdpik','bdpipi','bskk']

conName = args.bdtName
cut = args.pidCuts
cut1 = cut.split('.')[0]
cut2 = cut.split('.')[1]
cut3 = cut.split('.')[2]
cut4 = cut.split('.')[3]
year = args.year
magnet = args.magnet
bdtCut = args.bdtCut
fState = args.fState        
outFile = open(args.outDir+'/results/effs_%s_%s_%s_%s_%s.txt'%(fState,cut,bdtCut,year,magnet),'w')

for decay in decays:

  command = 'select eff from pidEffs where finalState="%s" and decay="%s"'
  command+= ' and plusCUT1=%s and plusCUT2=%s and minusCUT1=%s and minusCUT2=%s'
  command+= ' and year="%s" and magnet="%s" and splotFlag=1'
  command+= ' and bdtConfig="%s" and bdtCUT=%s;'
  command = command%(fState,decay,cut1,cut2,cut3,cut4,year,magnet,conName,bdtCut)
  print(command)
  pidEff = curs.execute(command).fetchone()[0]

  outFile.write('eff_%s_%s = %5.4g C L(-INF - +INF)\n'%(decay,fState,pidEff))

outFile.close()






