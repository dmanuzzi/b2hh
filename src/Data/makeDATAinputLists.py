import json
import os

B2HH_CONFIG = os.environ.get('B2HH_CONFIG')
B2HH_OUT = os.environ.get('B2HH_OUT')
outDir = B2HH_OUT+'/Data/inputLists'
if not os.path.exists(outDir): os.mkdir(outDir)

filePaths  = open(B2HH_CONFIG+'/inputDATApaths.json', 'r')
inputPaths = json.loads(filePaths.read())
filePaths.close()
#print inputPaths

for jobName in list(inputPaths.keys()):
    configs = jobName.split('_')
    name = "b2hh"
    year = configs[0]
    mag = configs[1]
    if mag == 'MagUp': mag = 'Up'
    if mag == 'MagDown': mag = 'Down'
    print name,  year, mag
    nfout = outDir+'/%s_%s_%s.txt'%(name,year,mag)
    nfout_tmp = nfout+'.tmp'
    path = inputPaths[jobName].replace('root://eoslhcb.cern.ch/', '')
    print path
    #os.system('A=`xrdfs root://eoslhcb.cern.ch ls %s`'%(path))
    os.system('A=`xrdfs root://eoslhcb.cern.ch ls %s` && echo "$A">%s'%(path, nfout_tmp))
    fout_tmp = open(nfout_tmp, 'r')
    fout = open(nfout,'w')
    fout.write(fout_tmp.read().replace('/eos/lhcb/grid/prod/lhcb', 'root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb'))
    fout.close()
    fout_tmp.close()
    os.system('rm -f %s'%nfout_tmp)
