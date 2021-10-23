import os
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-n','--name', type = str, dest = 'name', default = 'PIPI',
                    help='Name decay used for BDT optimisation [PIPI,KK] (default = PIPI)')
parser.add_argument('-b','--bdt', type = str, dest = 'bdt', default = '0.04',
                    help='Cut on BDT (default = 0.04)')
parser.add_argument('-y','--year', type = str, dest = 'year', default = '2016',
                    help='Year of data taking [2015,2016,Tot] (default = 2016)')
parser.add_argument('-m','--magnet', type = str, dest = 'magnet', default = 'Tot',
                    help='Magnet polarity [Up,Down,Tot] (default = Tot)')
parser.add_argument('-F','--makeFit', dest = 'makeFit', action = 'store_true', default = False,
                    help='Flag to make the fit of slope dependency from time')
args = parser.parse_args()

os.environ['LD_LIBRARY_PATH'] = '%s:%s'%(os.getenv('PWD'),os.getenv('LD_LIBRARY_PATH'))

# for code in ['provaVin','createTemplate','createPhysTemplate']:
# 	command = 'make %s'%code
# 	try:
# 		os.system(command)
# 	except:
# 		print 'Compilation of %s.C failed'%code
# 		eixt(1)

makeFit = ''
if args.makeFit: makeFit = '-F'

command = '${B2HH_SRC}/TimeModels/provaVin -n %s -b %s -m %s -y %s -f KPI %s'%(args.name,args.bdt,args.magnet,args.year,makeFit)
os.system(command)
command = '${B2HH_SRC}/TimeModels/provaVin -n %s -b %s -m %s -y %s -f PIPI %s'%(args.name,args.bdt,args.magnet,args.year,makeFit)
os.system(command)
command = '${B2HH_SRC}/TimeModels/provaVin -n %s -b %s -m %s -y %s -f KK %s'%(args.name,args.bdt,args.magnet,args.year,makeFit)
os.system(command)


command = '${B2HH_SRC}/TimeModels/createTemplate -n %s -b %s -m %s -y %s -f KPI'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)
command = '${B2HH_SRC}/TimeModels/createTemplate -n %s -b %s -m %s -y %s -f PIPI'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)
command = '${B2HH_SRC}/TimeModels/createTemplate -n %s -b %s -m %s -y %s -f KK'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)

command = '${B2HH_SRC}/TimeModels/createPhysTemplate -n %s -b %s -m %s -y %s -f KPI'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)
command = '${B2HH_SRC}/TimeModels/createPhysTemplate -n %s -b %s -m %s -y %s -f PIPI'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)
command = '${B2HH_SRC}/TimeModels/createPhysTemplate -n %s -b %s -m %s -y %s -f KK'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)
