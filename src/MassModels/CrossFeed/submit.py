import os
#import sqlite3 as sql

def myrange(start,stop,step):
  while start <= stop:
    yield start
    start += step

basedir=os.getenv('PWD')
outdir='%s/condor_log/out/' % basedir
if not os.path.exists(outdir):   os.mkdir(outdir)
errdir='%s/condor_log/err/' % basedir
if not os.path.exists(errdir):   os.mkdir(errdir)
logdir='%s/condor_log/log/' % basedir
if not os.path.exists(logdir):   os.mkdir(logdir)
modeldir='%s/Models/' % basedir
if not os.path.exists(modeldir): os.mkdir(modeldir)

#pidEffs = sql.connect('../../PID/B2HH/pidEffs.db')
#curs = pidEffs.cursor()

magnet = "Tot"
#years = ['2017', '2018']
#years+= ['201516']
#years = ['20151618']
years = ['201516', '2017s29r2p2', '2018']

configs = { 'PIPI_0.12'  : { 'finalStates' : { 'kpi'  : '5.-2.-5.3',
                                               'pik'  : '-5.3.5.-2',
                                               'pipi' : '-2.3.-2.3',
                                               'kk'   : '2.-2.2.-2'},
                             'bdt'         : '0.12',
                           },
           'KK_0.04'   : { 'finalStates' : { 'kpi'   : '5.-2.-5.3', 
                                             'pik'  : '-5.3.5.-2',
                                             'pipi' : '-2.3.-2.3',
                                             'kk'   : '2.-2.2.-2'},
                           'bdt'         : '0.04',
                         },
            'KK_0.06'   : { 'finalStates' : { 'kpi'   : '5.-2.-5.3', 
                                              'pik'  : '-5.3.5.-2',
                                              'pipi' : '-2.3.-2.3',
                                              'kk'   : '2.-2.2.-2'},
                            'bdt'         : '0.06',
                         },
            'KK_0.08'   : { 'finalStates' : { 'kpi'   : '5.-2.-5.3', 
                                              'pik'  : '-5.3.5.-2',
                                              'pipi' : '-2.3.-2.3',
                                              'kk'   : '2.-2.2.-2'},
                           'bdt'         : '0.08',
                          },
            
}
configs = {
  'KK_0.12'   : { 'finalStates' : { #'kpi'   : '5.-2.-5.3', 
                                    #'pik'  : '-5.3.5.-2',
                                    #'pipi' : '-2.3.-2.3',
                                    'kk'   : '2.-2.2.-2',
                                    #'kk'   : '5.-5.5.-5'
  },
                  'bdt'         : '0.12',
                },
}


fileRun = open('run.sh', 'w')
fileRun.write('''#!/bin/bash
hostname
cd {basedir}
echo $ROOTSYS
lb-run -c x86_64-slc6-gcc48-opt DaVinci/v36r1p1 ./create -d $1 -f $2 -c $3 -b $4 -m $5 -y $6 -F $7
#./create -d $1 -f $2 -c $3 -b $4 -m $5 -y $6 -F $7
'''.format(basedir=basedir))
fileRun.close()
os.system('chmod +x run.sh')

fileSubmit = open('submit.jdl', 'w')
fileSubmit.write('''executable   = {basedir}/run.sh
JobBatchName = MassModels_CrossFedd
arguments    = $(d) $(f) $(c) $(b) $(m) $(y) $(effNoFid)
universe     = vanilla
getenv       = True
Requirements = (machine == "lhcb-256g-96ht-a.cr.cnaf.infn.it")
output       = {outdir}/MassModels_CrossFeed_$(d)_$(f)_$(c)_$(b)_$(m)_$(y)_$(effNoFid).txt
error        = {errdir}/MassModels_CrossFeed_$(d)_$(f)_$(c)_$(b)_$(m)_$(y)_$(effNoFid).txt
log          = {logdir}/MassModels_CrossFeed_$(d)_$(f)_$(c)_$(b)_$(m)_$(y)_$(effNoFid).txt
queue d, f, c, b, m, y, effNoFid from jobs.txt
'''.format(basedir=basedir, outdir=outdir, errdir=errdir, logdir=logdir))
fileSubmit.close()

fileJobs = open('jobs.txt', 'w')
for year in years:
  for key,config in list(configs.items()):
    decay = key.split('_')[0]
    bdtCut = config['bdt']

    for finalState,cuts in list(config['finalStates'].items()):

      cut1 = cuts.split('.')[0]
      cut2 = cuts.split('.')[1]
      cut3 = cuts.split('.')[2]
      cut4 = cuts.split('.')[3]

      
      modelFile = '%s/%s_%s_%s_%s_%s_%s.root' % (outdir,finalState,decay,bdtCut,cuts,magnet,year)
      if os.path.exists(modelFile): os.remove(modelFile)
      '''    
    command = 'select effNoFiducialPlus from pidEffs where finalState=\"%s\" and decay=\"lbpk\" \
               and plusCUT1=%s and plusCUT2=%s and minusCUT1=%s and minusCUT2=%s \
               and magnet = \"%s\" and year = \"%s" \
               and splotFlag=1 and bdtConfig=\"%s\" and bdtCUT=%s;' % (finalState,cut1,cut2,cut3,cut4,magnet,year,decay,bdtCut)
    effNoFiducialPK  = curs.execute(command).fetchone()[0]

    command = 'select effNoFiducialPlus from pidEffs where finalState=\"%s\" and decay=\"lbkp\" \
               and plusCUT1=%s and plusCUT2=%s and minusCUT1=%s and minusCUT2=%s \
               and magnet = \"%s\" and year = \"%s" \
               and splotFlag=1 and bdtConfig=\"%s\" and bdtCUT=%s;' % (finalState,cut1,cut2,cut3,cut4,magnet,year,decay,bdtCut)
    effNoFiducialKP  = curs.execute(command).fetchone()[0]

    command = 'select effNoFiducialPlus from pidEffs where finalState=\"%s\" and decay=\"lbppi\" \
               and plusCUT1=%s and plusCUT2=%s and minusCUT1=%s and minusCUT2=%s \
               and magnet = \"%s\" and year = \"%s" \
               and splotFlag=1 and bdtConfig=\"%s\" and bdtCUT=%s;' % (finalState,cut1,cut2,cut3,cut4,magnet,year,decay,bdtCut)
    effNoFiducialPPI  = curs.execute(command).fetchone()[0]

    command = 'select effNoFiducialPlus from pidEffs where finalState=\"%s\" and decay=\"lbpip\" \
               and plusCUT1=%s and plusCUT2=%s and minusCUT1=%s and minusCUT2=%s \
               and magnet = \"%s\" and year = \"%s" \
               and splotFlag=1 and bdtConfig=\"%s\" and bdtCUT=%s;' % (finalState,cut1,cut2,cut3,cut4,magnet,year,decay,bdtCut)
    effNoFiducialPIP  = curs.execute(command).fetchone()[0]
    '''
      effNoFiducialPK  = 0
      effNoFiducialKP  = 0
      effNoFiducialPPI = 0
      effNoFiducialPIP = 0
      
      fileJobs.write('%s %s %s %s %s %s %g_%g_%g_%g\n' % (decay,finalState,cuts,bdtCut,magnet,year,effNoFiducialPK,effNoFiducialKP,effNoFiducialPPI,effNoFiducialPIP)
)
      
fileJobs.close()
os.system('condor_submit submit.jdl')

