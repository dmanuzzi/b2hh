import ROOT
from ROOT import RooFit
#from plotOpts20151618 import plotOpts20151618 as plotOpts20151618
from plotOpts201516   import plotOpts201516   as plotOpts201516
from plotOpts2017     import plotOpts2017     as plotOpts2017
from plotOpts2018     import plotOpts2018     as plotOpts2018
from plotOpts2017s29r2p2 import plotOpts2017s29r2p2 as plotOpts2017s29r2p2
from plotOptsTot      import plotOptsTot      as plotOptsTot

plotOpts = {}
#plotOpts.update(plotOpts20151618)
plotOpts.update(plotOpts201516)
plotOpts.update(plotOpts2017)
plotOpts.update(plotOpts2018)
plotOpts.update(plotOpts2017s29r2p2)
plotOpts.update(plotOptsTot)
