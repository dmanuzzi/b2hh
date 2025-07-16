import os
#import pandas as pd
#import matplotlib
#import matplotlib.pyplot as plt
from math import log10, floor

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


def readFitParams(nfin):
    ret = {}
    fin = open(nfin, 'r')
    text = fin.read()
    lines = [ l for l in text.split('\n')[:-1] if l != '' ]
    for line in lines:
        ll = [ l for l in line.split(' ') if l != '' ]
        if '<none>' in ll:
            ret[ll[0]] = (float(ll[2]), float(ll[4]))
    fin.close()
    return ret


years = ['201516', '2017s29r2p2', '2018', 'Tot']
years = ['Tot']
#confs = ['PIPI_0.2', 'KK_0.1']
confs = ['GraNEW_0.86']
confs = ['GraNEW_0.76', 'GraNEW_0.78', 'GraNEW_0.8', 'GraNEW_0.82', 'GraNEW_0.84', 'GraNEW_0.86']
confs = ['GraNEW_0.78', 'GraNEW_0.8', 'GraNEW_0.83', 'GraNEW_0.86', 'GraNEW_0.89']
#confs = ['PIPI_0']
modess= {'Data\\_kpi' : ['Data_kpi'],
         'kpi'  : ['bdkpi_kpi' ,'bdpipi_kpi' ,'bskk_kpi'    ,'bskpi_kpi'],
         'pipi' : ['bdkpi_pipi','bdpipi_pipi','bspipi_pipi', 'bskpi_pipi'],
         'kk'   : ['bdkpi_kk'  ,'bdkk_kk'    ,'bskk_kk'    ,'lbpk_kk']}
tags  = ['tot', 'tag']
fout  = open('AccSignal.tex','w')

fout.write('\\documentclass[10pt,a4paper]{article}\n')
fout.write('\\usepackage[utf8]{inputenc}\n')
fout.write('\\usepackage{amsmath}\n')
fout.write('\\usepackage{amsfonts}\n')
fout.write('\\usepackage{amssymb}\n')
fout.write('\\usepackage{graphicx}\n')
fout.write('\\usepackage{geometry}\n')
fout.write('\\usepackage{hyperref}\n')
#fout.write('\\usepackage{grffile}\n')
fout.write('\\graphicspath{{/ceph-data/lhcb_g/users/mcaporal/bspipi/out/AccSignal/}}\n') #new

fout.write('\\geometry{a4paper,top=1cm,bottom=1.5cm,left=0.5cm,right=0.5cm,heightrounded,bindingoffset=5mm}\n')
fout.write('\n')

fout.write('\\begin{document}\n')
fout.write('\\tableofcontents\n')
################################################################################
################################################################################
################################################################################
fout.write('\\clearpage\n')
fout.write('\\section{Intro}\n')
################################################################################
################################################################################
################################################################################
fout.write('\\section{Fit for Acceptances}\n')
for year in years:
    if not year == years[0]:
        fout.write('\\clearpage\n')
    fout.write('\\subsection{Year: %s}\n'%year)
    for conf in confs:
        if not conf == confs[0]:
            fout.write('\\clearpage\n')
        bdtType = conf.split('_')[0]
        bdtCut  = conf.split('_')[1]
        fout.write('\\subsubsection{Selection: $\\mathtt{bdt%s}>%s$}\n'%(bdtType, bdtCut))
        for fstate, modes in iter(modess.items()):
            nfigs=[]
            for tag in tags:
                for mode in modes:
                    nfigs+= ['plots/fitAcc/pdf/fitForAcc_%s_%s_%s_Tot_%s.pdf'%(mode,conf,year,tag)] # {} removed as they were showing issues
            addFigure(fout, nfigs,
                      label='fitForAcc %s %s'%(year, bdtType),
                      caption='Fit for acceptaces. Year %s. Final State: %s. Selection: $\\mathtt{bdt%s}>%s$. Top: \\texttt{untagged}, bottom: \\texttt{tagged}.'%(year,fstate, bdtType, bdtCut),
                      width=0.24, itemsPerLine=len(modes))
################################################################################
'''
fout.write('\\clearpage\n')
fout.write('\\section{Acceptance compariasons: year}\n')
for conf in confs:
     if not conf == confs[0]:
         fout.write('\\clearpage\n')
     bdtType = conf.split('_')[0]
     bdtCut  = conf.split('_')[1]
     fout.write('\\subsection{Selection: $\\mathtt{bdt%s}>%s$}\n'%(bdtType, bdtCut))
     for fstate, modes in iter(modess.items()):
         nfigs=[]
         for tag in tags:
             for mode in modes:
                 t = ''
                 if tag == 'tag': t = 'T'
                 if mode == 'Data_kpi': mode = 'data'
                 nfigs+= ['plots/{acceptances%s_%s_%s_Tot}.pdf'%(t,mode,conf,)]
         addFigure(fout, nfigs,
                   label='acceptance comp %s '%(bdtType),
                   caption='Acceptance compariason depending on the year of data taking. Final State: %s. Selection: $\\mathtt{bdt%s}>%s$. Top: \\texttt{untagged}, bottom: \\texttt{tagged}.'%(fstate, bdtType, bdtCut),
                   width=0.24, itemsPerLine=len(modes))
################################################################################

fout.write('\\clearpage\n')
fout.write('\\section{Acceptance compariasons: BDT cut}\n')
for year in years:
    fout.write('\\subsection{Year: %s}\n'%(year))
    for fstate, modes in iter(modess.items()):
        nfigs=[]
        for tag in tags:
            for mode in modes:
                t = ''
                if tag == 'tag': t = 'T'
                if mode == 'Data_kpi': mode = 'data'
                nfigs+= ['plots/{acceptances%s_%s_%s_Tot}.pdf'%(t,mode,year)]
        #addFigure(fout, nfigs,
        #          label='acceptance comp %s '%(year),
        #          caption='Acceptance compariason depending on the BDT requirement. Final State: %s. Year: %s. Top: \\texttt{untagged}, bottom: \\texttt{tagged}.'%(fstate, year),
        #          width=0.24, itemsPerLine=len(modes))
################################################################################
fout.write('\\clearpage\n')
fout.write('\\section{FINAL Acceptance compariasons: year}\n')
for conf in confs:
     if not conf == confs[0]:
         fout.write('\\clearpage\n')
     bdtType = conf.split('_')[0]
     bdtCut  = conf.split('_')[1]
     fout.write('\\subsection{Selection: $\\mathtt{bdt%s}>%s$}\n'%(bdtType, bdtCut))
     for fstate, modes in iter(modess.items()):
         if fstate == 'Data\\_kpi': continue
         nfigs=[]
         for tag in tags:
             for mode in modes:
                 t = ''
                 if fstate in mode.split('_')[0]: mode = mode.split('_')[0]
                 if tag == 'tag': t = 'T'
                 else: t = 'U'
                 if mode == 'Data_kpi': mode = 'data'
                 nfigs+= ['plotsRatios/{acceptances%s_%s_%s_Tot}.pdf'%(t,mode,conf,)]
         addFigure(fout, nfigs,
                   label='FINAL acceptance comp %s '%(bdtType),
                   caption='FINAL Acceptance compariason depending on the year of data taking. Final State: %s. Selection: $\\mathtt{bdt%s}>%s$. Top: \\texttt{untagged}, bottom: \\texttt{tagged}.'%(fstate, bdtType, bdtCut),
                   width=0.24, itemsPerLine=len(modes))

'''
fout.write('\\end{document}\n')
fout.close()

os.system('pdflatex AccSignal.tex')
os.system('pdflatex AccSignal.tex')
#os.system('open AccSignal.pdf')
