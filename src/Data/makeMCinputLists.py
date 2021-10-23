import json
import os

B2HH_CONFIG = os.environ.get('B2HH_CONFIG')
B2HH_OUT = os.environ.get('B2HH_OUT')
outDir = B2HH_OUT+'/Data/inputLists'
if not os.path.exists(outDir): os.mkdir(outDir)


filePaths = open(B2HH_CONFIG+'/inputMCpaths.json', 'r')
inputPaths = json.loads(filePaths.read())
filePaths.close()
#print inputPaths

evtTypeToName = {
    '11102021' : ['bdkk'],
    '11102005' : ['bdkpi', 'bdpik'],
    '11102015' : ['bdpipi'],
    '13102004' : ['bskk'],
    '13102015' : ['bskpi', 'bspik'],
    '13102021' : ['bspipi'],
    '15102001' : ['lbkp', 'lbpk'],
    '15102011' : ['lbpip', 'lbppi'],
}

for jobName in list(inputPaths.keys()):
    configs = jobName.split('_')
    evtType = configs[2]
    year = '20'+configs[3]
    mag = configs[4]
    if mag == 'MagUp': mag = 'Up'
    if mag == 'MagDown': mag = 'Down'
    for name in evtTypeToName[evtType]:
        print(evtType, name,  year, mag)
        nfout = outDir+'/%s_%s_%s.txt'%(name,year,mag)
        nfout_tmp = nfout+'.tmp'
        path = inputPaths[jobName].replace('root://eoslhcb.cern.ch/', '')
        print(path)
        os.system('A=`ls %s`'%(path))
        os.system('A=`ls %s` && echo "$A">%s'%(path, nfout_tmp))
        fout_tmp = open(nfout_tmp, 'r')
        fout = open(nfout,'w')
        fout.write(fout_tmp.read().replace('/eos/lhcb/grid/prod/lhcb', 'root://eoslhcb.cern.ch//eos/lhcb/grid/prod/lhcb'))
        fout.close()
        fout_tmp.close()
        os.system('rm -f %s'%nfout_tmp)
