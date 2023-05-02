#!/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_69/Python/2.7.6/x86_64-slc6-gcc48-opt/bin/python
import os
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-t','--tagger', nargs='+', dest = 'taggers', default = ['OS'])
parser.add_argument('-C','--conf', type = str, dest = 'conf', default = 'PIPI')
parser.add_argument('-b','--bdtCut', type = str, dest = 'bdtCut', default = '0.12')
parser.add_argument('-y','--years', nargs='+', dest = 'years', default = ['201516'])
parser.add_argument('-m','--magnet', type = str, dest = 'magnet', default = 'Tot')
#parser.add_argument('-s','--splitConf', type = str, dest = 'splitConf', default = '')
parser.add_argument('-d','--outDir', type = str, dest = 'outDir', default = 'results_Template')
parser.add_argument('-n','--ncpu', type = int, dest = 'ncpu', default = 32)

# parser.add_argument('-u','--blindFlag', dest = 'blindFlag', action = 'store_true', default = False)
# parser.add_argument('-p','--plot', dest = 'plot', action = 'store_true', default = False)
# parser.add_argument('-r','--range', type = str, dest = 'range', default = 'total')
# parser.add_argument('-f','--finalState', type = str, dest = 'finalState', default = 'PIPI')
# parser.add_argument('-v','--var', type = str, dest = 'var', default = 'mass')
# parser.add_argument('-B','--Btag', type = str, dest = 'Btag', default = 'tot')
# parser.add_argument('-F','--Ftag', type = str, dest = 'Ftag', default = 'tot')
# parser.add_argument('-A','--Atag', type = str, dest = 'Atag', default = 'OS')
args = parser.parse_args()

taggers = args.taggers
conf    = args.conf
bdtCut  = args.bdtCut
years   = args.years
magnet  = args.magnet
outDir  = args.outDir
nCPUs   = args.ncpu 

finalStates = { 
    'PIPI_{year}' : ['tot'],
    'KPI_{year}'  : ['tot', 'kpi', 'pik'],
    'KK_{year}'   : ['tot'],               
}

#btags = ['B','Bbar', 'Untag', 'tot']
btags = ['B','Bbar', 'tot']

variables = { 
    'mass'    : ['total'],
#    'time'    : ['bkg','sig5.23', 'sig5.33','sig5.45','total','3body'],    
#    'eta'     : ['bkg','sig5.23', 'sig5.33','sig5.45','total','3body'],
#    'asym'    : ['asymKK','asymPIPI','asymKPI','asymKPIBs','bkg',
#                 'asymKKLow','asymKKHigh'],
    'time'    : ['total'],    
    'eta'     : ['total'],
    'asym'    : ['asymKK','asymPIPI','asymKPI','asymKPIBs'],
}

pathRUN = os.environ.get('B2HH_RUN')
fjobs = open(pathRUN+'/FitTotal/jobsPlots.txt', 'a')
taggerList = '_'.join(taggers)
for year in years:
    for finalState_tmp in finalStates.keys():
        finalState = finalState_tmp.format(year=year)
        ftags = finalStates[finalState_tmp]
        pdfConfiguration = finalState.split('_')[1]
        for ftag in ftags:
            for btag in btags:
                for var in variables.keys():
                    ranges = variables[var]
                    for rangePlot in ranges:
                        for tagger in taggers:
                            if var == 'asym':
                                if btag!='tot':
                                    continue
                                if rangePlot == 'asymKK' and 'KK' not in finalState:
                                    continue
                                if rangePlot == 'asymPIPI' and 'PIPI' not in finalState:
                                    continue
                                if rangePlot == 'asymKPI' and 'KPI' not in finalState:
                                    continue
                                nCPUs = 32
                            else:
                                if '45' in rangePlot and 'KK' not in finalState:
                                    continue
                                #if btag != 'tot' and tagger == 'OS': continue
                                if btag == 'Untag' and var == 'eta': continue
                                #if btag == 'tot' and var == 'eta': continue
                                if btag == 'tot' and tagger != 'OS': continue
                                nCPUs = 1

                            command = taggerList
                            command+= ' '+conf
                            command+= ' '+bdtCut
                            command+= ' '+year
                            command+= ' '+magnet
                            command+= ' '+year
                            command+= ' '+outDir
                            command+= ' '+str(nCPUs)
                            command+= ' '+var
                            command+= ' '+rangePlot
                            command+= ' '+finalState
                            command+= ' '+btag
                            command+= ' '+ftag
                            command+= ' '+tagger
                            fjobs.write('%s\n'%command)

                                
fjobs.close()
