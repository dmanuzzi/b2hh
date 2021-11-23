#!/cvmfs/lhcb.cern.ch/lib/lcg/releases/LCG_69/Python/2.7.6/x86_64-slc6-gcc48-opt/bin/python


import os

basedir = '%s/'%(os.getenv('PWD'))
condordir='%s/condor_log'%basedir
outdir  = '%s/condor_log/out/'%basedir
errdir  = '%s/condor_log/err/'%basedir
logdir  = '%s/condor_log/log/'%basedir
histodir= '%s/TrackEff'%basedir

if not os.path.exists(condordir):os.mkdir(condordir)
if not os.path.exists(outdir)  : os.mkdir(outdir)
if not os.path.exists(errdir)  : os.mkdir(errdir)
if not os.path.exists(logdir)  : os.mkdir(logdir)
if not os.path.exists(histodir): os.mkdir(histodir)

#hypotheses = { 'PI' : ['0.3']+['-%d.3' % i for i in range(1,10)],
#               'K'  : ['%d.-2' % i for i in range(0,10)],
#               #'P'  : ['10.10']
#}

hypotheses = { 
  'P'   : ['10.10'],
  'K'   : ['2.-2', '5.-2'],
  'PI'  : ['-2.3', '-5.3']
  #'K'   : ['5.-5'],
}

magnets = ['Up', 'Down']
years   = ['201516', '2017', '2018']
#years   = ['201516']
#years   = ['20151618']
binning = [('71','10','1','6')] #P, ETA, PHI, SPD
"""
binning = [('36',  '5', '4','6'),
           ('36',  '5', '8','6'),
           ('36',  '5','16','6'),
           ('36', '10', '4','6'),
           ('36', '10', '8','6'),
           ('36', '10','16','6'),
           ('36', '20', '4','6'),
           ('36', '20', '8','6'),
           ('36', '20','16','6'),

           ('71',  '5', '4','6'),
           ('71',  '5', '8','6'),
           ('71',  '5','16','6'),
           ('71', '10', '4','6'),
           ('71', '10', '8','6'),
           ('71', '10','16','6'),
           ('71', '20', '4','6'),
           ('71', '20', '8','6'),
           ('71', '20','16','6'),

           ('140', '5', '4','6'),
           ('140', '5', '8','6'),
           ('140', '5','16','6'),
           ('140','10', '4','6'),
           ('140','10', '8','6'),
           ('140','10','16','6'),
           ('140','20', '4','6'),
           ('140','20', '8','6'),
           #('140','20','16','6'),
]
"""
reweight = '1'

runFile = open('run.sh', 'w')
runFile.write('''#!/bin/bash
source /cvmfs/sft.cern.ch/lcg/views/LCG_97a/x86_64-centos7-gcc9-opt/setup.sh
cd {basedir}
./eff -x "$1" -y "$2" -z "$3" -t "$4" -m "$5" -Y "$6" -f "$7" -c "$8" -r "$9"
'''.format(basedir=basedir))
runFile.close()
os.system('chmod +x run.sh')

submitFile = open('submit.jdl', 'w')
submitFile.write('''executable   = {basedir}/run.sh
JobBatchName = PIDcalib_$(Y)_$(m)
arguments    = $(x) $(y) $(z) $(t) $(m) $(year) $(f) $(c) $(r) 
universe     = vanilla
getenv       = True
output       = {outdir}/PIDcalib_$(x)_$(y)_$(z)_$(t)_$(m)_$(year)_$(f)_$(c)_$(r).txt
error        = {errdir}/PIDcalib_$(x)_$(y)_$(z)_$(t)_$(m)_$(year)_$(f)_$(c)_$(r).txt
log          = {logdir}/PIDcalib_$(x)_$(y)_$(z)_$(t)_$(m)_$(year)_$(f)_$(c)_$(r).txt
queue x, y, z, t, m, year, f, c, r from jobs.txt
'''.format(basedir=basedir, outdir=outdir, errdir=errdir, logdir=logdir))
submitFile.close()

for magnet in magnets:
  for year in years:
    jobFile = open('jobs.txt', 'w')
    for hypo,cuts in hypotheses.iteritems():
      for cut in cuts:
        for binP,binETA,binPHI,binTracks in binning:
          jobFile.write('binP_%s binETA_%s binPHI_%s binSPD_%s %s %s %s %s %s\n'%(binP,binETA,binPHI,binTracks,magnet,year,hypo,cut,reweight))

    jobFile.close()
    os.system('condor_submit submit.jdl')
