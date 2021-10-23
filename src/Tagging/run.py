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
args = parser.parse_args()

# command = 'make pidWeights'
# try:
#   os.system(command)
# except:
#   print 'Compilation of pidWeights.C failed'
#   exit
# command = 'make reweightSS'
# try:
#   os.system(command)
# except:
#   print 'Compilation of reweightSS.C failed'
#   exit
# command = 'make makeTemplates'
# try:
#   os.system(command)
# except:
#   print 'Compilation of makeTemplates.C failed'
#   exit
# command = 'make createBKG'
# try:
#   os.system(command)
# except:
#   print 'Compilation of createBKG.C failed'
#   exit



pathSRC='${B2HH_SRC}/Tagging/'

command = pathSRC+'pidWeights -d %s -b %s -m %s -y %s -f PIPI -c -2.3.-2.3'%(args.name,args.bdt,args.magnet,args.year) 
print command
os.system(command)
command = pathSRC+'reweightSS -d %s -b %s -m %s -y %s -f pipi -c bddpi'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)
command = pathSRC+'reweightSS -d %s -b %s -m %s -y %s -f pipi -c bsdspi'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)
command = pathSRC+'makeTemplates -n %s -b %s -m %s -y %s -f 0 -r bd'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)
command = pathSRC+'createBKG -C %s -b %s -m %s -y %s -f pipi -c -2.3.-2.3'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)

command = pathSRC+'pidWeights -d %s -b %s -m %s -y %s -f KK -c 2.-2.2.-2'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)
command = pathSRC+'reweightSS -d %s -b %s -m %s -y %s -f kk -c bddpi'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)
command = pathSRC+'reweightSS -d %s -b %s -m %s -y %s -f kk -c bsdspi'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)
command = pathSRC+'makeTemplates -n %s -b %s -m %s -y %s -f 2 -r bs'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)
command = pathSRC+'createBKG -C %s -b %s -m %s -y %s -f kk -c 2.-2.2.-2'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)

command = pathSRC+'pidWeights -d %s -b %s -m %s -y %s -f KPI -c 5.-2.-5.3'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)
command = pathSRC+'reweightSS -d %s -b %s -m %s -y %s -f kpi -c bddpi'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)
command = pathSRC+'reweightSS -d %s -b %s -m %s -y %s -f kpi -c bsdspi'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)
command = pathSRC+'makeTemplates -n %s -b %s -m %s -y %s -f 1 -r bd'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)
command = pathSRC+'createBKG -C %s -b %s -m %s -y %s -f kpi -c 5.-2.-5.3'%(args.name,args.bdt,args.magnet,args.year)
print command
os.system(command)

