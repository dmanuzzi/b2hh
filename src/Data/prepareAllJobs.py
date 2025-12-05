import argparse
parser = argparse.ArgumentParser()
parser.add_argument('-o','--outFile', type = str, dest = 'outFile', default = 'jobs.txt')
parser.add_argument('-c','--code', type = str, dest = 'code', default = 'sel')
parser.add_argument('-d','--decays', nargs='+', dest = 'decays', default = ['b2hh'])
parser.add_argument('-y','--years', nargs='+', dest = 'years', default = ['2015', '2016', '2017s29r2p2', '2018'])
parser.add_argument('-m','--magnets', nargs='+', dest = 'magnets', default = ['Up', 'Down'])
parser.add_argument('-n','--NmaxJobs', type = int, dest = 'NmaxJobs', default = 200)
args = parser.parse_args()
    

import os
B2HH_RUN = os.environ.get('B2HH_RUN')
B2HH_OUT = os.environ.get('B2HH_OUT')

dir_inputs = B2HH_OUT+'/Data/inputLists/'
dir_selJobs = B2HH_OUT+'/Data/selJobs_inputLists/'
if not os.path.exists(dir_selJobs):
    os.mkdir(dir_selJobs)

#nfjobs = B2HH_RUN+'/Data/jobs.txt'
nfjobs = args.outFile
fjobs = open(nfjobs, 'a')
NmaxJobs = args.NmaxJobs
code = args.code
for decay in args.decays:
    for year in args.years:
        for mag in args.magnets:
            tmpYear = year
            if code == 'mc' and year == '2017s29r2p2': tmpYear = '2017'
            nfin = dir_inputs+'{decay}_{year}_{mag}.txt'.format(decay = decay, 
                                                                year = tmpYear, 
                                                                mag = mag)
            nfsplit=dir_selJobs+'{decay}_{year}_{mag}_{index}.txt'.format(decay = decay, 
                                                                            year = year, 
                                                                            mag = mag,
                                                                            index= '{index}')
            os.system('rm -rf '+nfsplit.format(index='*'))
            print nfin
            fin = open(nfin, 'r')
            inputs = fin.read().split('\n')[:-1]
            Ninputs = len(inputs)
            Njobs = min(NmaxJobs, Ninputs)
            NfilesPerJob = int(Ninputs/Njobs)
            r = Ninputs - NfilesPerJob*Njobs
            index = 0    
            firstInput = 0
            lastInput = NfilesPerJob
            if index < r: lastInput+=1
            while True:
                fsplit = open(nfsplit.format(index=index), 'w')
                for nfile in inputs[firstInput:lastInput]:
                    fsplit.write(nfile+'\n')
                fsplit.close()
                jobArguments = decay+' '
                jobArguments+= year+' '
                jobArguments+= mag+' '
                jobArguments+= code+' '
                jobArguments+= str(index)+' '
                jobArguments+= nfsplit.format(index=index)
                fjobs.write(jobArguments+'\n')
                if (lastInput==Ninputs): break
                
                index += 1
                firstInput = lastInput
                lastInput = firstInput+NfilesPerJob
                if index < r: lastInput+=1
                if lastInput > Ninputs: lastInput = Ninputs
            fin.close()
fjobs.close()
