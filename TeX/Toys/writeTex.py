import os
#import pandas as pd
#import matplotlib
#import matplotlib.pyplot as plt
from math import log10, floor

def addFigure(file, nfigs, label, caption,
              width=0.5, itemsPerLine=1,
              pars={'.': '.'}):
    fout.write('\\begin{figure}[!ht]\n')
#    fout.write('\\centering\n')
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




#years = ['201516', '2017s29r2p2', '2018', 'Tot']
years = ['Tot']
confs = ['GraNEW_0.78', 'GraNEW_0.8', 'GraNEW_0.83', 'GraNEW_0.86', 'GraNEW_0.89']
Ncol = 3
Nrow = len(confs)
fout  = open('toys.tex','w')

fout.write('\\documentclass[10pt,a4paper]{article}\n')
fout.write('\\usepackage[utf8]{inputenc}\n')
fout.write('\\usepackage{amsmath}\n')
fout.write('\\usepackage{amsfonts}\n')
fout.write('\\usepackage{amssymb}\n')
fout.write('\\usepackage{graphicx}\n')
fout.write('\\usepackage{geometry}\n')
fout.write('\\usepackage{hyperref}\n')
#fout.write('\\usepackage{grffile}\n')
#fout.write('\\graphicspath{{/ceph-data/lhcb_g/users/mcaporal/bspipi/out/AccSignal/}}\n') #new
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
    _ndir = '../../out/Toys/{}_{}_Tot_noCPVbspipi/plots'.format(confs[0],year)
    nvars = [f.replace('.pdf','') for f in os.listdir(_ndir) if os.path.isfile(os.path.join(_ndir, f)) and ('_pull' not in f) and ('_err' not in f)]
    nvars.sort()
    Nfig = 0
    for nvar in nvars:
        fout.write('\\subsubsection{\\texttt{%s}}\n'%(nvar.replace('canv_','').replace('_','\\_')))
        nfigs = []
        for conf in confs:
            nfigs.append(f'../../out/Toys/{conf}_{year}_Tot_noCPVbspipi/plots/{nvar}.pdf')
            nfigs.append(f'../../out/Toys/{conf}_{year}_Tot_noCPVbspipi/plots/{nvar}_err.pdf')
            nfigs.append(f'../../out/Toys/{conf}_{year}_Tot_noCPVbspipi/plots/{nvar}_pull.pdf')
        addFigure(fout, nfigs,
                  label=nvar.replace('_',':'),
                  caption="Year: %s, Variable: \\texttt{%s}. From top to bottom: \\texttt{%s}"%(year,nvar.replace('_','\\_'), ('} , \\texttt{'.join(confs)).replace('_', '\\_')),
                  width=1/Ncol-0.01, itemsPerLine=Ncol)
        Nfig += 1
        if Nfig:
            fout.write('\\clearpage\n')
#        if Nfig > 4:
#            break

fout.write('The End\n')
fout.write('\\end{document}\n')
fout.close()

os.system('pdflatex toys.tex')
os.system('pdflatex toys.tex')
#os.system('open AccSignal.pdf')
