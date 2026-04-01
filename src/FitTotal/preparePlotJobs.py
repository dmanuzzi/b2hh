#!/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_69/Python/2.7.6/x86_64-slc6-gcc48-opt/bin/python
import os
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-t','--tagger', nargs='+', dest = 'taggers')
parser.add_argument('-C','--conf', type = str, dest = 'conf')
parser.add_argument('-b','--bdtCut', type = str, dest = 'bdtCut')
parser.add_argument('-y','--years', nargs='+', dest = 'years')
parser.add_argument('-m','--magnet', type = str, dest = 'magnet')
parser.add_argument('-p','--pidConfig', type = str, dest = 'pidConfig')
parser.add_argument('-d','--outDir', type = str, dest = 'outDir')
parser.add_argument('-n','--ncpu', type = int, dest = 'ncpu')

args = parser.parse_args()

taggers = args.taggers
conf    = args.conf
bdtCut  = args.bdtCut
years   = args.years
magnet  = args.magnet
pidConfig= args.pidConfig
outDir  = args.outDir
nCPUs   = args.ncpu 
finalStates = { 
    'PIPI_{year}' : ['tot'],
    'KPI_{year}'  : ['tot', 'kpi', 'pik'],
    'KK_{year}'   : ['tot'],               
}

btags = ['B','Bbar', 'Untag', 'tot']
#btags = ['B','Bbar', 'tot']

variables = { 
    'mass'    : ['total'],
    'time'    : ['bkg','sig5.23', 'sig5.33','sig5.45','total','3body'],    
    'eta'     : ['bkg','sig5.23', 'sig5.33','sig5.45','total','3body'],
    'asym'    : ['asymKK','asymPIPI','asymKPI','asymKPIBs','bkg',
                 'asymKKLow','asymKKHigh'],
#    'time'    : ['total'],    
#    'eta'     : ['total'],
#    'asym'    : ['asymKK','asymPIPI','asymKPI','asymKPIBs'],
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
                                nCPUs = 16
                            else:
                                if '45' in rangePlot and 'KK' not in finalState:
                                    continue
                                #if btag != 'tot' and tagger == 'OS': continue
                                if btag == 'Untag' and var == 'eta': continue
                                #if btag == 'tot' and var == 'eta': continue
                                if btag == 'tot' and tagger != 'OS': continue
                                nCPUs = 4

                            command = taggerList
                            command+= ' '+conf
                            command+= ' '+bdtCut
                            command+= ' '+year
                            command+= ' '+magnet
                            command+= ' '+pidConfig
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
