#!/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_69/Python/2.7.6/x86_64-slc6-gcc48-opt/bin/python
import os


args = [
    # {
    #     'taggers' : ['OS', 'SS'],
    #     'directory' : '2018_noSS',
    #     'configuration' : 'PIPI',
    #     'bdtCut' : '0.12'
    # },
    # {
    #     'taggers' : ['OS', 'SSk'],
    #     'directory' : '2018_noSS',
    #     'bdtCut' : '0.04'
    #     'configuration' : 'KK',
    # },
    #{
    #    'taggers' : ['OS', 'SS'],
    #    'directory' : '201516_noSS',
    #    'configuration' : 'PIPI',
    #    'bdtCut' : '0.12'
    #},
    #{
    #    'taggers' : ['OS', 'SSk'],
    #    'directory' : '201516_noSS',
    #    'configuration' : 'KK',
    #    'bdtCut' : '0.04'
    #},
    #{
    #     'taggers' : ['OS', 'SSk'],
    #     'directory' : '201516_from1.5ps',
    #     'configuration' : 'KK',
    #     'bdtCut' : '0.04'
    #},
    #{
    #     'taggers' : ['OS', 'SSk'],
    #     'directory' : '2017s29r2p2_from1.5ps',
    #     'configuration' : 'KK',
    #     'bdtCut' : '0.04'
    # },
    {
        'taggers' : ['OS', 'SSk'],
        'directory' : '201516_tightPIDkk',
        'years' : ['201516'],
        'configuration' : 'KK',
        'bdtCut' : '0.12'
    },
    {
        'taggers' : ['OS', 'SSk'],
        'directory' : '2017s29r2p2_tightPIDkk',
        'years' : ['2017s29r2p2'],
        'configuration' : 'KK',
        'bdtCut' : '0.12'
    },
    {
        'taggers' : ['OS', 'SSk'],
        'directory' : '2018_tightPIDkk',
        'years' : ['2018'],
        'configuration' : 'KK',
        'bdtCut' : '0.12'
    },
]

finalStates = { 
                'PIPI_{year}' : ['tot'],
                'KPI_{year}'  : ['tot', 'kpi', 'pik'],
                'KK_{year}'   : ['tot'],               
}
btags = ['B','Bbar', 'Untag', 'tot']
#btags = ['B','Bbar', 'Untag']#['tot']
#btags = ['Untag']
#btags = ['tot']

variables = { 
    #'mass'  : ['total'],
    #'time'  : ['bkg','sig5.23', 'sig5.33','sig5.45','total','3body'],    
    #'timeErr' : ['total','sig','3body','bkg'],
    #'eta'  : ['bkg','sig5.23', 'sig5.33','sig5.45','total','3body'],
    #'asym' : ['asymKK','asymPIPI','asymKPI','asymKPIBs','bkg'],
    'asym' : ['asymKKLow','asymKKHigh'],
}


fjobs = open('plotsToRun.txt', 'w')
for arg in args:
    taggerList = '_'.join(arg['taggers'])
    for year in arg['years']:
        for finalState_tmp in finalStates.keys():
            finalState = finalState_tmp.format(year=year)
            ftags = finalStates[finalState_tmp]
            pdfConfiguration = finalState.split('_')[1]
            for ftag in ftags:
                for btag in btags:
                    for var in variables.keys():
                        ranges = variables[var]
                        for rangePlot in ranges:
                                for tagger in arg['taggers']:
                                    nCPUs = 0
                                    #if tagger == 'OS': continue
                                    if var == 'asym':
                                        if btag!='tot' or ftag == 'kpi' or ftag == 'pik':
                                            continue
                                        #if 'OS' in tagger: continue 
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

                                    opt_str = '%s_%s_%s_%d_%s_%s_%s_%s_%s_%s_%s_%s_%s'%(
                                        taggerList,
                                        arg['configuration'],
                                        arg['bdtCut'],
                                        nCPUs,
                                        arg['directory'],
                                        pdfConfiguration,
                                        pdfConfiguration,
                                        var,
                                        rangePlot,
                                        finalState,
                                        btag,
                                        ftag,
                                        tagger
                                    )
                                    fjobs.write('%s\n'%opt_str)
                                    foptsName = 'plot_opts/opts_%s.sh'%opt_str
                                    fopts = open(foptsName, 'w')
                                    fopts.write('#!/bin/bash\n')
                                    fopts.write('hostname\n')
                                    fopts.write('cd $B2HH_HOME/FitTotal\n')
                                    fopts.write('source /home/LHCB-T3/dmanuzzi/B2HH/envSetup.sh\n')
                                    # fopts.write('export B2DXFITTERSROOT=/home/LHCB/dmanuzzi/B2HH/B2DXFitters\n')
                                    # fopts.write('export PYTHONPATH=/home/LHCB/dmanuzzi/B2HH/B2DXFitters/python:$PYTHONPATH\n')
                                    # fopts.write('export LD_LIBRARY_PATH=/home/LHCB/dmanuzzi/B2HH/B2DXFitters/standalone:$LD_LIBRARY_PATH\n')
                                                                    
                                    command = 'python fit.py'
                                    command += ' -m Tot'
                                    command += ' -t %s'%' '.join(arg['taggers'])
                                    command += ' -C %s'%arg['configuration']
                                    command += ' -b %s'%arg['bdtCut']
                                    command += ' -n %d'%nCPUs
                                    command += ' -d %s'%arg['directory']
                                    command += ' -s %s'%pdfConfiguration
                                    command += ' -y %s'%pdfConfiguration
                                    command += ' -p'                               
                                    command += ' -v %s'%var
                                    command += ' -r %s'%rangePlot
                                    command += ' -f %s'%finalState
                                    command += ' -B %s'%btag
                                    command += ' -F %s'%ftag
                                    command += ' -A %s'%tagger
                                    command += '\n'                               
                                    fopts.write(command)
                                    fopts.close()
                                    os.system('chmod +x %s'%foptsName)

                                
fjobs.close()
os.system('condor_submit submitPlot.jdl')          
