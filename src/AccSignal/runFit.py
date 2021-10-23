import os
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-n','--name', type = str, dest = 'name', default = 'PIPI',
                    help='BDT optimisation [PIPI,KK] (default = PIPI)')
parser.add_argument('-b','--bdt', type = str, dest = 'bdt', default = '0.04',
                    help='BDT cut (default = 0.04)')
parser.add_argument('-y','--year', type = str, dest = 'year', default = '2016',
                    help='Year of data taking [2015,2016,Tot] (default = 2016)')
parser.add_argument('-m','--magnet', type = str, dest = 'magnet', default = 'Tot',
                    help='Magnet polarity [Up,Down,Tot] (default = Tot)')
parser.add_argument('-F','--Fit', dest = 'fitFlag', action = 'store_true', default = False,
                    help='If present, the fit is performed')
args = parser.parse_args()

taggerName = ''
if args.name == 'PIPI': taggerName = 'SS'
else:                   taggerName = 'SSk'

fitFlag = ""
if args.fitFlag: fitFlag = "-F"

os.environ['LD_LIBRARY_PATH'] = '%s:%s'%(os.getenv('PWD'),os.getenv('LD_LIBRARY_PATH'))

# command = 'make fitAcc'
# try: 
#   os.system(command)
# except:
#   print 'Compilation of fitAcc.C failed'
#   exit(1)
pathSRC = '${B2HH_SRC}/AccSignal/'

command = pathSRC+'fitAcc -C %s -b %s -m %s -y %s -n bdkpi -f kpi -D %s'%(args.name,args.bdt,args.magnet,args.year,fitFlag)
print "------------->", command
os.system(command)

command = pathSRC+'fitAcc -C %s -b %s -m %s -y %s -n bdkpi -f kpi -D -T %s'%(args.name,args.bdt,args.magnet,args.year,fitFlag)
print "------------->", command
os.system(command)

for name in ['bdkpi_kpi','bdkpi_pipi','bdkpi_kk','bdpipi_pipi','bdpipi_kpi','bdkk_kk','bskk_kk','bskk_kpi','bskpi_kpi','bspipi_pipi','lbpk_kk']:
  decay = name.split('_')[0]
  finalState = name.split('_')[1]
  command = pathSRC+'fitAcc -C %s -b %s -m %s -y %s -n %s -f %s %s'%(args.name,args.bdt,args.magnet,args.year,decay,finalState,fitFlag)
  print "------------->", command
  os.system(command)
  command = pathSRC+'fitAcc -C %s -b %s -m %s -y %s -n %s -f %s -T %s'%(args.name,args.bdt,args.magnet,args.year,decay,finalState,fitFlag)
  print "------------->", command
  os.system(command)

# command = 'make makeRatio'
# try: 
#   os.system(command)
# except:
#   print 'Compilation of makeRatio.C failed'
#   exit(1)

command = pathSRC+'makeRatio -C %s -b %s -m %s -y %s -n bdkpi -f kpi -D'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)
command = pathSRC+'makeRatio -C %s -b %s -m %s -y %s -n bdkpi -f kpi -D -T'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)

for name in ['bdkpi_pipi','bdkpi_kk','bdpipi_pipi','bdpipi_kpi','bdkk_kk','bskk_kk','bskk_kpi','bskpi_kpi','bspipi_pipi','lbpk_kk']:
  decay = name.split('_')[0]
  finalState = name.split('_')[1]
  command = pathSRC+'makeRatio -C %s -b %s -m %s -y %s -n %s -f %s'%(args.name,args.bdt,args.magnet,args.year,decay,finalState)
  os.system(command)
  command = pathSRC+'makeRatio -C %s -b %s -m %s -y %s -n %s -f %s -T'%(args.name,args.bdt,args.magnet,args.year,decay,finalState)
  os.system(command)


