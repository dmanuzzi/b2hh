####  #  #   #     #   #  ####
#     #   # #      ## ##  #
####  #    #       # # #  ####
#     #   # #      #   #  #
#     #  #   #     #   #  ####



from math import log10, floor
nfout = 'fitresults.tex'
configs = [
#    ('PIPI', '0.12'),
    ('GraNEW', '0.86')
]
#configs+= [('KK', '0.06'), ('KK', '0.08')]
#configs = [('KK', '0.04')]
fStates = ['PIPI', 'KK', 'KPI']
#fStates = ['KPI']
#ps = ['kpi', 'pik', 'tot']
ps = ['tot']
#vars = ['mass', 'time','eta','asym']
vars = ['mass']
#Btags= ['B', 'Bbar', 'Untag', 'tot']
Btags= ['tot']

#Btags= ['tot']
nfileTemplate = '{{{dir}/plots/{var}_{massRange}_{fState}_{year}_{config}_{bdt}_{Btag}_{p}_{Atag}}}.pdf'
# dirs=['KK_0.1_201516_Tot', '../../../b2hhNewBDT/FitTotal/KK_0.1_201516_Tot']
# dirs=['KK_0.1_2018_Tot', '../../../b2hhNewBDT/FitTotal/KK_0.1_2018_Tot']
# dirs=['KK_0.1_2017s29r2p2_Tot', '../../../b2hhNewBDT/FitTotal/KK_0.1_2017s29r2p2_Tot']
#dirs = ['KK_0.1_201516_Tot', 'KK_0.1_2017s29r2p2_Tot', 'KK_0.1_2018_Tot']
dirs = ['BDT_0.98_201516_Tot', 'BDT_0.98_2017s29r2p2_Tot', 'BDT_0.98_2018_Tot']


#dirs=['KK_0.1_201112_Tot', 'reference_ANA']
mags=['Tot']
years=['201516', '2017s29r2p2', '2018', 'Tot']
slices=['total','bkg','3body', 'sig5.33', 'sig5.45']
slices=['total']
def addFigure(file, nfigs, label, caption,
              width=0.5, itemsPerLine=1,
              pars={'.': '.'}):
    fout.write('\\begin{figure}[h!]\n')
    fout.write('\\centering\n')
    count=0
    for K in pars.keys():
        for V in pars[K]:
            for nfig in nfigs:
                count+=1
                newline=''
                if count%itemsPerLine == 0: newline='\\\\'
                fout.write('\\includegraphics[width=%f\\textwidth]{%s}%s\n'%(width,
                                                                             nfig.replace(K, V),
                                                                             newline))
    fout.write('\\caption{%s}\n'%caption)
    fout.write('\\label{fig:%s}\n'%label)
    fout.write('\\end{figure}\n')
    fout.write('\n')

def rounder(val, err):
    #toRound =floor(log10(abs(err)))-1
    if abs(err)<1.0e-6: return val, err, 0
    toRound =floor(log10(abs(err)))-1
    val = round(val, -toRound)
    err = round(err, -toRound)
    return val, err, -toRound

def readResults(nfin):
    print('readResults: START')
    results={}
    fin = open(nfin, 'r')
    lines= fin.read().split('\n')[:-2]
    #print(lines)
    for line in lines:
        infoRaw = line.replace('  ', ' ').replace('2018','201516').replace('2017s29r2p2', '201516').replace('2017','201516').replace('20151618', '201516').split(' ')
        #infoRaw = line.replace('  ', ' ').split(' ')
        if len(infoRaw) < 6:
            print('skip line', infoRaw)
            continue
        else:
            print(infoRaw)
        varName = infoRaw[0].replace('201516', '').replace('smoothed_bin_', '')
        val     = infoRaw[2]
        if infoRaw[3] == 'C' or infoRaw[5] == 'C':
            isConst = True
            err = 0.
        else:
            isConst = False
            try:
                float(infoRaw[4])
            except:
                err = 0
            else:
                err = infoRaw[4]

        infoOut = { 'val' : val, 'err' : err, 'isConst': isConst}
        results[varName] = infoOut
    #print(results)
    print('readResults: END')
    fin.close()
    return results

def isVarPhys(nvar):
    if '_C_' in nvar: return True
    if '_S_' in nvar: return True
    if '_D_' in nvar: return True
    if '_G_' in nvar: return True
    if '_dM_' in nvar: return True
    if '_dG_' in nvar: return True
    if '_ACP_' in nvar: return True
    if '_AP_' in nvar: return True
    if '_Af_' in nvar: return True
    return False

def isVarEffPID(nvar):
    return (nvar[:4] == 'eff_')

def isVarYield(nvar):
    return (nvar[:2] == 'n_' or nvar[:2] == 'R_')

def isVarResT(nvar):
    return ('timeErr' in nvar)

def isVarFT(nvar):
    if 'OS' in nvar: return True
    if 'SS' in nvar: return True
    if 'etaHat' in nvar: return True
    if 'Atag' in nvar: return True
    return False
def isVarFTbkg(nvar):
    return (isVarFT(nvar) and 'bkg' in nvar)
def isVarFTsig(nvar):
    return (isVarFT(nvar) and not isVarFTbkg(nvar))

def isVarTimeAcc(nvar):
    return ('accTime' in nvar)

def isVarBkgMass(nvar):
    return (('_mass_' in nvar) and ('bkg_' in nvar))
def isVarSigMass(nvar):
    return (('_mass_' in nvar) and not isVarBkgMass(nvar))

def isVarAll(nvar):
    return ('_' in nvar)


def printResultsTable(fout, results, varsets, tags, label, caption):
    values = {}
    ntags = []
    requirements = []
    for varset in varsets:
        if 'Phys' in varset: requirements.append(isVarPhys)
        if 'EffPID' in varset: requirements.append(isVarEffPID)
        if 'Yield' in varset: requirements.append(isVarYield)
        if 'ResT' in varset: requirements.append(isVarResT)
        if 'FTbkg' in varset: requirements.append(isVarFTbkg)
        if 'FTsig' in varset: requirements.append(isVarFTsig)
        if 'TimeAcc' in varset: requirements.append(isVarTimeAcc)
        if 'BkgMass' in varset: requirements.append(isVarBkgMass)
        if 'SigMass' in varset: requirements.append(isVarSigMass)
        if 'All' in varset: requirements.append(isVarAll)

    for tag in tags:
        sel = tag[0]
        bdt = tag[1]
        dir = tag[2]
        ntag = '%s_%s_%s'%(sel,bdt,dir)
        ntags.append(ntag)
        for var in list(results[sel][bdt][dir].keys()):
            skipVar = True
            for requirement in requirements:
                if requirement(var): skipVar = False
            if skipVar: continue
            if var not in values.keys():
                values[var] = {}
            values[var][ntag] = results[sel][bdt][dir][var]

    fout.write('\\begin{table}[h!]\n')
    fout.write('\\centering\n')
    fout.write('\\begin{tabular}{%s}\n'%('c'*(len(tags)+1)))
    fout.write('\\hline\n')
    topLine = ' \\textbf{--} '
    for ntag in ntags:
        topLine += '& \\textbf{%s}'%ntag.replace('_','-').replace('KK-0.1-', '')
    topLine += '\\\\\n'
    fout.write(topLine)
    fout.write('\\hline\n')
    tmpTemplate = '& \\textcolor{black}{$%.*f \\pm %.*f$}'
    tmpTemplateConst = '& \\textcolor{blue}{$%f$}'
    for var in values.keys():
        color = 'Green'
        for ntag1 in ntags:
            if color == 'red' : break
            if ntag1 not in values[var].keys(): continue
            val1 = float(values[var][ntag1]['val'])
            err1 = float(values[var][ntag1]['err'])
            for ntag2 in ntags:
                if ntag2 not in values[var].keys(): continue
                if values[var][ntag2]['isConst']:
                    if not values[var][ntag1]['isConst']:
                        color = 'red'
                        break
                    elif values[var][ntag1]['val'] != values[var][ntag2]['val']:
                        color = 'blue'
                else:
                    val2 = float(values[var][ntag2]['val'])
                    err2 = float(values[var][ntag2]['err'])
                    diff = 0
                    try:
                        diff = abs(val1-val2)/(err1**2+err2**2)**0.5
                    except:
                        diff = 100

                    if  diff > 2:
                        color = 'red'
                        break
        line = '\\textcolor{%s}{$\mathtt{%s}$} '%(color,var.replace('_', '~'))
        for ntag in ntags:
            if ntag not in values[var].keys():
                line += ' & '
            else:
                if values[var][ntag]['isConst']:
                    val = float(values[var][ntag]['val'])
                    line += tmpTemplateConst%(val)
                else:
                    val = float(values[var][ntag]['val'])
                    err = float(values[var][ntag]['err'])
                    Val,Err,digits = rounder(val,err)
                    line += tmpTemplate%(digits,Val,digits,Err)
        line += '\\\\\n'
        fout.write(line)
    fout.write('\\hline\n')
    fout.write('\\end{tabular}\n')
    fout.write('\\caption{%s}\n'%caption)
    fout.write('\\label{%s}\n'%label)
    fout.write('\\end{table}\n')

fout = open(nfout, 'w')
fout.write('\\documentclass[10pt,a4paper]{article}\n')
fout.write('\\usepackage[utf8]{inputenc}\n')
fout.write('\\usepackage{amsmath}\n')
fout.write('\\usepackage{amsfonts}\n')
fout.write('\\usepackage{amssymb}\n')
fout.write('\\usepackage{graphicx}\n')
fout.write('\\usepackage{geometry}\n')
fout.write('\\usepackage{hyperref}\n')
fout.write('\\usepackage[dvipsnames]{xcolor}\n')
fout.write('\\geometry{a4paper,top=1cm,bottom=1.5cm,left=0.5cm,right=0.5cm,heightrounded,bindingoffset=5mm}\n')
fout.write('\n')

fout.write('\\begin{document}\n')
fout.write('\\tableofcontents\n')

fout.write('\\clearpage\n')
from itertools import product
for year,mag in product(years,mags):
        #if year == 'hhAngle5' : continue
        if year != years[0] or mag != mags[0]: fout.write('\\clearpage\n')
        for sel,bdt in configs:
            if (sel,bdt) != configs[0]: fout.write('\\clearpage\n')
            dir = '%s_%s_%s_%s'%(sel, bdt, year,mag)
            fout.write('\\section{Configuration: %s %s %s %s }\n'%(year, mag, sel, bdt))
            ssTagger ='SS'
            if sel == 'KK': ssTagger = 'SSk'
            taggers = [ssTagger, 'OS']
            for fState in fStates:
                if fState != fStates[0]: fout.write('\\clearpage\n')
                for slice in slices:
                    if slice == 'sig5.45' and fState != 'KK': continue
                    if slice != slices[0]: fout.write('\\clearpage\n')
                    fout.write('\\subsubsection{Final state: %s, mass range: %s}\n'%(fState, slice))
                    for var in vars:
                        nfigs = []
                        massRanges = []
                        figList= 'From left to right:'
                        if var == 'asym':
                            if slice != 'total': continue
                            massRanges = ['asym'+fState]
                            if fState == 'KPI':
                                massRanges = ['asymKPIBs']
                        else:
                            massRanges = [slice]

                        if var == 'mass' and slice != 'total': continue
                        for massRange,tagger,Btag, p in product(massRanges,taggers,Btags, ps):
                            Atag = tagger
                            if var == 'asym' and Btag != 'tot': continue
                            if Btag == 'tot' and p != 'tot': continue
                            if Btag == 'tot' and Atag != 'OS' and var != 'asym': continue
                            if var == 'eta'  and (Btag == 'tot' or Btag == 'Untag'): continue

                            figList += ' \\texttt{%s\\_%s\\_%s},'%(tagger, Btag,p)
                            nfigs.append(nfileTemplate.format(dir=dir,
                                                              var=var,
                                                              massRange=massRange,
                                                              year=year,
                                                              fState=fState,
                                                              config=sel,
                                                            #bdt=bdt.replace('.', '_'),
                                                              bdt=bdt,
                                                              Btag=Btag,
                                                              tag='OS_%s'%ssTagger,
                                                              p=p,
                                                              Atag=Atag))

                        if len(nfigs) == 0: continue
                        itemsPerLine = 2 if var == 'asym' else 5
                        width = 0.5  if var == 'asym' else 0.5 #was 0.3 and 0.19
                        figList += '.'
                        figList = figList.replace(',.', '.')

                        addFigure(fout, nfigs,
                                 label='fig:%s_%s_%s_%s_%s_%s_%s'%(dir,year,sel, bdt,
                                                            fState,slice,var),
                                 caption='''Fit results for %s. Observable: %s.
                                            Year: %s, Magnet: %s,
                                            config: %s, $\\mathtt{bdt}>%s$,
                                            final state: %s,
                                            mass range: %s. %s'''%(dir.replace('_','-'),
                                                               var,
                                                               year, mag, sel, bdt,
                                                               fState, slice,
                                                               figList),
                                  width=width, itemsPerLine=itemsPerLine)

fout.write('\\clearpage\n')
fout.write('\\section{Summary of input params}\n')
inputs = {}
#for sel,bdt in configs:
#    if sel not in inputs.keys():
#        inputs[sel] = {}
#    inputs[sel][bdt] = {}
#    for dir in dirs:
#        inputs[sel][bdt][dir] = {}
#        years = dir.split('_')
#        ssTagger ='SS'
#        if sel == 'KK': ssTagger = 'SSk'
#        inputs[sel][bdt][dir] = readResults('%s/input_params_%s_%s_OS_%s_Tot.txt.Unblind'%(dir,sel,
#                            bdt,ssTagger))

#for config in configs:
#    tags = []
#    for dir in dirs:
#        tags.append((config[0], config[1], dir))
#    varsetss = [['Phys'], ['ResT'],
#                ['FTsig'], ['TimeAcc'], ]
#    for varsets in varsetss:
#        label='tab:%s_%s_%s'%(config[0],config[1], '_'.join(varsets))
#        caption='''Fit inputs for $\\mathtt{bdt%s}> %s$.
#        Variable set: %s'''%(config[0],config[1], ', '.join(varsets))
#        printResultsTable(fout, inputs, varsets = varsets,
#                          tags = tags, label=label, caption=caption)


fout.write('\\clearpage\n')
fout.write('\\section{Summary of results}\n')
# # for sel,bdt in configs:
# #     for dir in dirs:
# #         years = dir.split('_')
# #         ssTagger ='SS'
# #         if sel == 'KK': ssTagger = 'SSk'
# #         res = readResults('%s/params_%s_%s_OS_%s_Tot.txt.Unblind'%(dir,sel,
# #                             bdt,ssTagger))
# #         label='tab:%s_%s_%s'%(dir,sel, bdt),
# #         caption='''Fit results for %s.
# #                    config: %s, $\\mathtt{bdt}>%s$'''%(dir.replace('_','-'),
# #                                       sel, bdt),
# # printResultsTable(fout, res, label, caption)
results = {}
for sel,bdt in configs:
    if sel not in results.keys():
        results[sel] = {}
    results[sel][bdt] = {}
    for dir in dirs:
        results[sel][bdt][dir] = {}
        years = dir.split('_')
        ssTagger ='SS'
        #if sel == 'KK': ssTagger = 'SSk'
        results[sel][bdt][dir] = readResults('%s/params_%s_%s_OS_%s_Tot.txt.Unblind'%(dir,sel,
                            bdt,ssTagger))

for dir in dirs:
    label='tab:%s'%(dir)
    caption='''Fit results for %s.'''%(dir.replace('_','-'))
    tags = [
        ('BDT', '0.98', dir),
    ]
    #printResultsTable(fout, results, varsets = ['Phys'], tags = tags,
    printResultsTable(fout, results, varsets = ['All'], tags = tags,
                      label=label, caption=caption)

for config in configs:
    tags = []
    for dir in dirs:
        tags.append((config[0], config[1], dir))
    #varsetss = [['Phys'], ['ResT'],
    #            ['FTsig'], ['TimeAcc'], ['Yields']]
    varsetss = [['Yields'],['EffPID']]
    for varsets in varsetss:
        label='tab:%s_%s_%s'%(config[0],config[1], '_'.join(varsets))
        caption='''Fit results for $\\mathtt{bdt%s}> %s$.
        Variable set: %s'''%(config[0],config[1], ', '.join(varsets))
        printResultsTable(fout, results, varsets = varsets,
                          tags = tags, label=label, caption=caption)

fout.write('\\end{document}\n')
fout.close()

import os
try:
    os.system('pdflatex %s'%nfout)
except:
    print('error in compilation')
else:
    os.system('pdflatex %s'%nfout)
    os.system('open %s'%nfout.replace('tex', 'pdf'))
