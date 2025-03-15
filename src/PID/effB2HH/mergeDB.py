#!/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_74root6/Python/2.7.9/x86_64-slc6-gcc48-opt/bin/python

import sqlite3
import os
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-d','--dir', type = str, dest = 'dir', default = 'jobs')
args = parser.parse_args()

inputList = [ file for file in os.listdir(args.dir+'/jobs') if '.db' in file ]
outDB = sqlite3.connect(args.dir+'/pidEffs.db')

curr = outDB.cursor()

curr.execute('create table if not exists pidEffs \
               (decay varchar(7),finalState varchar(5),name varchar(10),bdtConfig varchar(7),\
                bdtCUT float,plusCUT1 integer,plusCUT2 integer,minusCUT1 integer,minusCUT2 integer,\
                magnet varchar(5),year varchar(4), splotFlag integer,\
                eff double,effErr double,\
                fracFiducialPlus double,   effFiducialPlus double,   effFiducialPlusMC double,\
                fracNoFiducialPlus double, effNoFiducialPlus double, effNoFiducialPlusMC double,\
                fracFiducialMinus double,  effFiducialMinus double,  effFiducialMinusMC double,\
                fracNoFiducialMinus double,effNoFiducialMinus double,effNoFiducialMinusMC double,\
                primary key (decay,finalState,name,plusCUT1,plusCUT2,minusCUT1,minusCUT2,\
                bdtConfig,bdtCUT,magnet,year,splotFlag));')
print(inputList)
for file in inputList:

  print(file)
  command = 'attach \"%s\" as toMerge;' %(args.dir+'/jobs/'+file)
  print(command)
  curr.execute(command)
  outDB.commit()

  #command = 'begin;'
  #curr.execute(command)
  #outDB.commit()

  command = 'insert into pidEffs select * from toMerge.pidEffs;'
  print(command)
  curr.execute(command)
  outDB.commit()

  command = 'detach database toMerge;'
  curr.execute(command)
  outDB.commit()

