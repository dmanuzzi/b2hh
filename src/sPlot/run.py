import os
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-n','--name', type = str, dest = 'name', default = 'PIPI',
                    help='Name decay used for BDT optimisation [PIPI,KK] (default = PIPI)')
parser.add_argument('-b','--bdt', type = str, dest = 'bdt', default = '0.12',
                    help='Cut on BDT (default = 0.12)')
parser.add_argument('-y','--year', type = str, dest = 'year', default = '2016',
                    help='Year of data taking [2015,2016,2017,2018,201516,20151618 Tot] (default = 2016)')
parser.add_argument('-m','--magnet', type = str, dest = 'magnet', default = 'Tot',
                    help='Magnet polarity [Up,Down,Tot] (default = Tot)')
args = parser.parse_args()



pathSRC = '${B2HH_SRC}/sPlot/'

command = pathSRC+'create -d %s -b %s -m %s -y %s -f pipi'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)



command = pathSRC+'reduce -d %s -b %s -m %s -y %s -f PIPI'%(args.name,args.bdt,args.magnet,args.year) 
os.system(command)
command = pathSRC+'reduce -d %s -b %s -m %s -y %s -f KPI'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)
command = pathSRC+'reduce -d %s -b %s -m %s -y %s -f KK'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)


command = pathSRC+'fit -d %s -b %s -m %s -y %s -f PIPI'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)
command = pathSRC+'fit -d %s -b %s -m %s -y %s -f KPI'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)
command = pathSRC+'fit -d %s -b %s -m %s -y %s -f KK'%(args.name,args.bdt,args.magnet,args.year)
os.system(command)
