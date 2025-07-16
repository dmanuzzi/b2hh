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

def addNote(stringWithComments):
    fout.write('\\clearpage\n')
    fout.write('\\section{Notes}\n')
    fout.write(f'{stringWithComments}\n')

    #fout.write('%s\n',stringWithComments)



years = ['201516', '2017s29r2p2', '2018', 'Tot']
years = ['Tot']
mags = ['Up', 'Down', 'Tot']
mags = ['Tot']
#mags = ['Tot']
#confs = ['KK_0.1', 'PIPI_0.2']
confs = ['PIPI_0']
confs = ['PIPI_0','GraNEW_0.86']
confs = ['GraNEW_0.86']
confs = ['GraNEW_0.78','GraNEW_0.8','GraNEW_0.83','GraNEW_0.86','GraNEW_0.89']

modes = ['PIPI', 'KK', 'KPI']
tags12  = ['ftag11', 'ftag10', 'ftag01', 'ftag00']
tagsTemplate = ['11', '10', '01', '00']
tagsTemplatePhys = ['U', 'T']
fout  = open('TimeModels.tex','w')

fout.write('\\documentclass[10pt,a4paper]{article}\n')
fout.write('\\usepackage[utf8]{inputenc}\n')
fout.write('\\usepackage{amsmath}\n')
fout.write('\\usepackage{amsfonts}\n')
fout.write('\\usepackage{amssymb}\n')
fout.write('\\usepackage{graphicx}\n')
#fout.write('\\usepackage{epstopdf}\n')#waiting for the package
fout.write('\\usepackage{geometry}\n')
fout.write('\\usepackage{hyperref}\n')
fout.write('\\graphicspath{{/ceph-data/lhcb_g/users/mcaporal/bspipi/out/TimeModels/}}\n') #new
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
for year in years:
    fout.write('\\clearpage\n')
    for mag in mags:
        if mag != mags[0]: fout.write('\\clearpage\n')
        fout.write('\\section{Year: %s, Magnet: %s}\n'%(year,mag))
        for conf in confs:
            #if (conf in ['KK_0.06', 'KK_0.08'] and year != '201516'): continue
            if conf !=  confs[0]: fout.write('\\clearpage\n')
            bdtType = conf.split('_')[0]
            bdtCut  = conf.split('_')[1]
            fout.write('\\subsection{Selection: $\\mathtt{bdt%s}>%s$}\n'%(bdtType, bdtCut))
            for mode in modes:
                if mode !=  modes[0]: fout.write('\\clearpage\n')
                fout.write('\\subsubsection{Final state: %s}\n'%(mode))
                nfigs12=[]
                nfigsTemplate=[]
                nfigsTemplatePhys=[]
                addFigure(fout, ['plots/pdf/Fig12_%s_%s_%s_%s.pdf'%(conf,mag,year,mode)],
                          label='fig12 %s %s %s %s untagged'%(year, mag, bdtType, mode),
                          caption='Invariant mass slope as a function of the decay time in the right-hand sideband ($m \\in [5.5, 6.2]~\mathrm{GeV}$). Year: %s; Magnet: %s; $\\mathtt{bdt%s}>%s$; Spectrum: %s; F. Tagging: None'%(year,mag, bdtType, bdtCut, mode),
                          width=0.5, itemsPerLine=1)

                for tag in tags12:
                    nfigs12+= ['plots/pdf/Fig12_%s_%s_%s_%s_%s.pdf'%(conf,mag,year,mode,tag)]
                for tag in tagsTemplate:
                    nfigsTemplate+= ['plots/pdf/template_%s_%s_%s_%s__%s.pdf'%(conf,mag,year,mode.lower(),tag)]
                for tag in tagsTemplatePhys:
                    nfigsTemplatePhys+= ['plots/pdf/templatePhys_%s_%s_%s_%s_%s.pdf'%(mode.lower(),conf,year,mag,tag)]

                addFigure(fout, nfigs12,
                          label='fig12 %s %s %s %s tagged'%(year, mag, bdtType, mode),
                          caption='Invariant mass slope as a function of the decay time in the right-hand sideband ($m \\in [5.5, 6.2]~\mathrm{GeV}$). Year: %s; Magnet: %s; $\\mathtt{bdt%s}>%s$; Spectrum: %s; F. Tagging (from top-left to bottom-right): OS and SS tagged, OS only tagged, SS only tagged, untagged.'%(year, mag, bdtType, bdtCut, mode),
                          width=0.3, itemsPerLine=2)
                addFigure(fout, nfigsTemplate,
                          label='template %s %s %s'%(year, bdtType, mode),
                          caption='Template for combinatorial background. Year: %s; Magnet: %s; $\\mathtt{bdt%s}>%s$; Spectrum: %s; F. Tagging (from top-left to bottom-right): OS and SS tagged, OS only tagged, SS only tagged, untagged.'%(year, mag, bdtType, bdtCut, mode),
                          width=0.3, itemsPerLine=2)
                addFigure(fout, nfigsTemplatePhys,
                          label='template phys %s %s %s'%(year, bdtType, mode),
                          caption='Templates for partially reconstructed bakground. Left: SS-untagged, right: SS-tagged. Year: %s; Magnet: %s; $\\mathtt{bdt%s}>%s$; Spectrum: %s.'%(year, mag, bdtType, bdtCut, mode),
                          width=0.3, itemsPerLine=2)

################################################################################
'''
fout.write('\\clearpage\n')
fout.write('\\section{Template comparisons: year}\n')
for conf in confs:
    #if conf in ['KK_0.04','KK_0.06', 'KK_0.08']: continue
    if not conf == confs[0]:
        fout.write('\\clearpage\n')
    bdtType = conf.split('_')[0]
    bdtCut  = conf.split('_')[1]
    fout.write('\\subsection{Selection: $\\mathtt{bdt%s}>%s$}\n'%(bdtType, bdtCut))
    for mode in modes:
        if mode !=  modes[0]: fout.write('\\clearpage\n')
        fout.write('\\subsubsection{Final state: %s}\n'%(mode))
        nfigsTemplate=[]
        nfigsTemplatePhys=[]
        for tag in tagsTemplate:
            nfigsTemplate+= ['plots/others/{templatebkg_%s_%s_%s_Tot_%s}.eps'%(mode.lower(),bdtType, bdtCut,tag)]
        for tag in tagsTemplatePhys:
            nfigsTemplatePhys+= ['plots/others/{templatephys_%s_%s_%s_Tot_%s}.eps'%(mode.lower(),bdtType, bdtCut,tag)]
        addFigure(fout, nfigsTemplate,
                  label='template comp %s %s'%(bdtType, mode),
                  caption='Template comparison for combinatorial background, depending on the data-taking year. $\\mathtt{bdt%s}>%s$; Spectrum: %s; F. Tagging (from top-left to bottom-right): OS and SS tagged, OS only tagged, SS only tagged, untagged.'%(bdtType, bdtCut, mode),
                  width=0.3, itemsPerLine=2)
        addFigure(fout, nfigsTemplatePhys,
                  label='template phys  comp %s %s'%(bdtType, mode),
                  caption='Template comparison for partially reconstructed bakground, dependig on the data-taking year. Left: SS-untagged, right: SS-tagged. $\\mathtt{bdt%s}>%s$; Spectrum: %s.'%(bdtType, bdtCut, mode),
                  width=0.3, itemsPerLine=2)
'''
################################################################################
'''
fout.write('\\clearpage\n')
fout.write('\\section{Template comparisons: BDT cut}\n')
for year in ['201516','2017', '2018']:
    fout.write('\\subsection{Year: %s}\n'%(year))
    for mode in modes:
        if mode !=  modes[0]: fout.write('\\clearpage\n')
        fout.write('\\subsubsection{Final state: %s}\n'%(mode))
        nfigsTemplate=[]
        nfigsTemplatePhys=[]
        for tag in tagsTemplate:
            nfigsTemplate+= ['plots/others/{templatebkg_%s_%s_Tot_%s}.eps'%(mode.lower(),year,tag)]
        for tag in tagsTemplatePhys:
            nfigsTemplatePhys+= ['plots/others/{templatephys_%s_%s_Tot_%s}.eps'%(mode.lower(),year,tag)]
        addFigure(fout, nfigsTemplate,
                  label='template comp %s %s'%(year, mode),
                  caption='Template comparison for combinatorial background, depending on BDT requirement. Year: %s; Spectrum: %s; F. Tagging (from top-left to bottom-right): OS and SS tagged, OS only tagged, SS only tagged, untagged.'%(year, mode),
                  width=0.3, itemsPerLine=2)
        addFigure(fout, nfigsTemplatePhys,
                  label='template phys  comp %s %s'%(year, mode),
                  caption='Template comparison for partially reconstructed bakground, dependig on BDT requirement. Left: SS-untagged, right: SS-tagged. Year: %s; Spectrum: %s.'%(year, mode),
                  width=0.3, itemsPerLine=2)

################################################################################
'''
addNote("nominal, with all years included. trying to look for better significances in the different years (kind of pre-toys optimisation)")

fout.write('\\end{document}\n')
fout.close()

os.system('pdflatex -interaction=nonstopmode TimeModels.tex')
os.system('pdflatex -interaction=nonstopmode TimeModels.tex')

#os.system('pdflatex --shell-escape TimeModels.tex') #shell escaping needed for the epstopdf package when eps are not in same directory
#os.system('pdflatex --shell-escape TimeModels.tex')
#os.system('open TimeModels.pdf')
