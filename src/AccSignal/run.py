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
args = parser.parse_args()

os.environ['LD_LIBRARY_PATH'] = '%s:%s'%(os.getenv('PWD'),os.getenv('LD_LIBRARY_PATH'))

# command = 'make selMC'
# try: 
# 	os.system(command)
# except:
# 	print 'Compilation of selMC.C failed'
# 	exit(1)

doSelMC = False
doKineWeight = True
doSubtractBkg = True
pathSRC = '${B2HH_SRC}/AccSignal/'
if doSelMC:
        command = pathSRC+'selMC -n %s -d bdkpi -f kpi -b %s -m %s -y %s -c 5.-2.-5.3 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)
        command = pathSRC+'selMC -n %s -d bdpik -f pik -b %s -m %s -y %s -c -5.3.5.-2 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)
        command = pathSRC+'selMC -n %s -d bdkpi -f pipi -b %s -m %s -y %s -c -2.3.-2.3 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)
        command = pathSRC+'selMC -n %s -d bdpik -f pipi -b %s -m %s -y %s -c -2.3.-2.3 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)
        command = pathSRC+'selMC -n %s -d bdkpi -f kk -b %s -m %s -y %s -c 2.-2.2.-2 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)
        command = pathSRC+'selMC -n %s -d bdpik -f kk -b %s -m %s -y %s -c 2.-2.2.-2 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)

        command = pathSRC+'selMC -n %s -d bskpi -f kpi -b %s -m %s -y %s -c 5.-2.-5.3 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)
        command = pathSRC+'selMC -n %s -d bspik -f pik -b %s -m %s -y %s -c -5.3.5.-2 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)

        command = pathSRC+'selMC -n %s -d bdpipi -f pipi -b %s -m %s -y %s -c -2.3.-2.3 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)
        command = pathSRC+'selMC -n %s -d bdpipi -f kpi -b %s -m %s -y %s -c 5.-2.-5.3 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)

        command = pathSRC+'selMC -n %s -d bspipi -f pipi -b %s -m %s -y %s -c -2.3.-2.3 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)
        command = pathSRC+'selMC -n %s -d bspipi -f kpi -b %s -m %s -y %s -c 5.-2.-5.3 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)

        command = pathSRC+'selMC -n %s -d bskk -f kk -b %s -m %s -y %s -c 2.-2.2.-2 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)
        command = pathSRC+'selMC -n %s -d bskk -f kpi -b %s -m %s -y %s -c 5.-2.-5.3 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)

        command = pathSRC+'selMC -n %s -d bdkk -f kk -b %s -m %s -y %s -c 2.-2.2.-2 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)

        command = pathSRC+'selMC -n %s -d lbpk -f kk -b %s -m %s -y %s -c 2.-2.2.-2 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)
        command = pathSRC+'selMC -n %s -d lbkp -f kk -b %s -m %s -y %s -c 2.-2.2.-2 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)

        command = pathSRC+'selMC -n %s -d lbppi -f kpi -b %s -m %s -y %s -c 5.-2.-5.3 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)
        command = pathSRC+'selMC -n %s -d lbpip -f pik -b %s -m %s -y %s -c -5.3.5.-2 -F 0_0_0_0'%(args.name,args.bdt,args.magnet,args.year)
        os.system(command)

# command = 'make kineWeight2'
# try: 
# 	os.system(command)
# except:
# 	print 'Compilation of kineWeight2.C failed'
# 	exit(1)

if doKineWeight:
        command = pathSRC+'kineWeight2 -n %s -b %s -y %s -m %s -d bdkpi -f kpi -d2 bdpik -f2 pik -B bd'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)
        command = pathSRC+'kineWeight2 -n %s -b %s -y %s -m %s -d bdkpi -f pipi -d2 bdpik -f2 pipi -B bd'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)
        command = pathSRC+'kineWeight2 -n %s -b %s -y %s -m %s -d bdkpi -f kk -d2 bdpik -f2 kk -B bd'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)
        command = pathSRC+'kineWeight2 -n %s -b %s -y %s -m %s -d bdpipi -f pipi -B bd'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)
        command = pathSRC+'kineWeight2 -n %s -b %s -y %s -m %s -d bdpipi -f kpi -B bd'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)
        command = pathSRC+'kineWeight2 -n %s -b %s -y %s -m %s -d bdkk -f kk -B bd'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)
        command = pathSRC+'kineWeight2 -n %s -b %s -y %s -m %s -d bskk -f kk -B bs'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)
        command = pathSRC+'kineWeight2 -n %s -b %s -y %s -m %s -d bskk -f kpi -B bs'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)
        command = pathSRC+'kineWeight2 -n %s -b %s -y %s -m %s -d bskpi -f kpi -d2 bspik -f2 pik -B bs'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)
        command = pathSRC+'kineWeight2 -n %s -b %s -y %s -m %s -d bspipi -f pipi -B bs'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)
        command = pathSRC+'kineWeight2 -n %s -b %s -y %s -m %s -d lbpk -f kk -d2 lbkp -f2 kk -B bs'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)
        command = pathSRC+'kineWeight2 -n %s -b %s -y %s -m %s -d lbppi -f kpi -d2 lbpip -f2 pik -B bs'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)

# command = 'make subtractBkg'
# try:
#   os.system(command)
# except:
#   print 'Compilation of subtractBkg.C failed'
#   exit

if doSubtractBkg:
        command = pathSRC+'subtractBkg -n %s -b %s -y %s -m %s'%(args.name,args.bdt,args.year,args.magnet)
        os.system(command)


