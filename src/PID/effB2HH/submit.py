#!/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_69/Python/2.7.6/x86_64-slc6-gcc48-opt/bin/python

import os
import sqlite3 as sql

basedir=os.getenv('PWD')
outdir=basedir+'/condor_log/out/'
errdir=basedir+'/condor_log/err/'
logdir=basedir+'/condor_log/log/'
def myrange(start,stop,step):
  while start <= stop:
    yield start
    start += step

if not os.path.exists(outdir):   os.mkdir(outdir)
if not os.path.exists(errdir):   os.mkdir(errdir)
if not os.path.exists(logdir):   os.mkdir(logdir)

config = { 
           #'PIPI' : { 'kk'    : ['5.-5.5.-5'],
           #           'kpi'   : ['5.-2.-5.3'],
           #           'pik'   : ['-5.3.5.-2'],
           #           'pipi'  : ['-2.3.-2.3'],
           #           'kk'    : ['2.-2.2.-2'],
           #         },
           'KK'   : { 
                       #'kk'    : ['5.-5.5.-5'],
                      #'kpi'   : ['5.-2.-5.3'],
                      #'pik'   : ['-5.3.5.-2'],
                      #'pipi'  : ['-2.3.-2.3'],
                      'kk'    : ['2.-2.2.-2'],
                    },
} 

binnings = [('71','10','1','6')]
magnets = ["Tot"]
#years = ['2015','2016','2017', '2018', '20151618']
#years = ['20151618']
#years = ['2017s29r2p2']
#years = ['2018']
#years = ['201516']
years = ['201516', '2017s29r2p2', '2018']
conName = ''#'-3.5.-3.5'
bdtCuts = {#'PIPI' : ['0.12'], 
           'KK' : ['0.12']
           #'KK' : ['0.04','0.06', '0.08']
}
splotFlag = ' -s'


runFile = open('run.sh', 'w')
runFile.write('''#!/bin/bash
source /cvmfs/sft.cern.ch/lcg/views/LCG_97a/x86_64-centos7-gcc9-opt/setup.sh
cd %s
./effB2HH -x "$1" -y "$2" -z "$3" -t "$4" -f "$5" -c "$6" -m "$7" -Y "$8" -n "$9" -C "${10}" -b "${11}" "${12}"
'''%basedir)
runFile.close()
os.system('chmod +x run.sh')

submitFile = open('submit.jdl', 'w')
submitFile.write('''executable   = {basedir}/run.sh
JobBatchName = PIDcalibEffB2HH_$(year)_$(m)
arguments    = $(x) $(y) $(z) $(t) $(f) $(c) $(m) $(year) $(n) $(conName) $(b) $(s)
universe     = vanilla
getenv       = True
Requirements = (machine == "lhcb-256g-96ht-a.cr.cnaf.infn.it")
output       = {outdir}/PIDcalibEffB2HH_$(x)_$(y)_$(z)_$(t)_$(f)_$(c)_$(m)_$(year)_$(n)_$(conName)_$(b)_$(s).txt
error        = {errdir}/PIDcalibEffB2HH_$(x)_$(y)_$(z)_$(t)_$(f)_$(c)_$(m)_$(year)_$(n)_$(conName)_$(b)_$(s).txt
log          = {logdir}/PIDcalibEffB2HH_$(x)_$(y)_$(z)_$(t)_$(f)_$(c)_$(m)_$(year)_$(n)_$(conName)_$(b)_$(s).txt
queue x, y, z, t, f, c, m, year, n, conName, b, s from jobs.txt
'''.format(basedir=basedir, outdir=outdir, errdir=errdir, logdir=logdir))
submitFile.close()

for magnet in magnets:

  for year in years:

    jobFile = open('jobs.txt', 'w')
    for name in config.keys():

      conName = name

      for finalState,cuts in list(config[name].items()):

        for cut in cuts:

          for binP,binETA,binPHI,binTracks in binnings:

            for bdt in bdtCuts[conName]:
             
              outfile = '%s/%s_%s_%s_%s_%s.out' %(outdir,finalState,name,conName,bdt,cut)
              if os.path.exists(outfile): os.remove(outfile)
              errfile = '%s/%s_%s_%s_%s_%s.err' %(errdir,finalState,name,conName,bdt,cut)
              if os.path.exists(errfile): os.remove(errfile)
              dbfile  = '%s/out/pidEffs_%s_%s_%s_%s_%s_%s_%s.db' % (basedir,finalState,name,conName,bdt,cut,magnet,year)
              if os.path.exists(dbfile): os.remove(dbfile)

              jobFile.write('binP_%s binETA_%s binPHI_%s binSPD_%s %s %s %s %s %s %s %s %s\n'%(binP,binETA,binPHI,binTracks,finalState,cut,magnet,year,name,conName,bdt,splotFlag))
        
    jobFile.close()
    os.system('condor_submit submit.jdl')
