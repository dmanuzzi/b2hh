from B2DXFitters.WS import WS as WS

def makeCanvas(name,config,width,height,plot,pull,outFile) :

  from ROOT import TCanvas, TPad, TLegend, RooCurve, RooFit, TPaveText


  c = TCanvas(name,name,width,height)
  c.cd()
  upperPad = c.GetPad(0)
  
  upperPad = TPad(name+"_upperPad",name+"_upperPad",0,0.2,1,1)
  upperPad.SetLeftMargin(0.2)
  upperPad.SetBottomMargin(0.15)
  upperPad.SetBorderSize(0)
  lowerPad = TPad(name+"_lowerPad",name+"_lowerPad",0,0,1,0.2)
  lowerPad.SetLeftMargin(0.2)
  lowerPad.SetBorderSize(0)
  lowerPad.Draw()
  upperPad.Draw()
  
  upperPad.cd() 
  #print "DENTRO MAKE CANVAS ",plot.GetXaxis().GetXmin(),plot.GetXaxis().GetXmax()
  plot.Draw()

  lowerPad.cd()
  #print "DENTRO MAKE CANVAS ",pull.GetXaxis().GetXmin(),pull.GetXaxis().GetXmax()
  pull.Draw()

  #print "DENTRO MAKE CANVAS ",plot.GetXaxis().GetXmin(),plot.GetXaxis().GetXmax()
  
  upperPad.cd()
  leg = TLegend(0.5,0.3,0.85,0.7,"")
  leg.SetName("leg%s"%name)
  leg.SetTextFont(132);
  leg.SetTextSize(0.06);
  leg.SetFillColor(RooFit.kWhite) 
  leg.SetBorderSize(0);
  keys = config.keys()
  keys.sort()
  from ROOT import TColor
  colorIdx = int(1000)
  colors = {}
  for comp in keys:
    if type(config[comp]['color']) == int:
      colors[comp] = [config[comp]['color'],0]
    else:
      print config[comp]['color'][0],config[comp]['color'][1],config[comp]['color'][2]
      colors[comp] = [colorIdx,TColor(colorIdx,config[comp]['color'][0],config[comp]['color'][1],config[comp]['color'][2])]
      colorIdx = colorIdx+1

  for comp in keys:
    color = colors[comp][0]
    compName = config[comp]['name']
    compLabel = config[comp]['plotName']
    print compName,compLabel
    curv = c.FindObject(compName)
    curv.SetFillColor(color)
    curv.SetLineColor(color)
    leg.AddEntry(curv,compLabel,"f")
    del compName, compLabel,curv
  if 'plot_eta' not in plot.GetName():
    leg.Draw("same")

  lhcb = TPaveText(0.5,0.75,0.68,0.85,"NDC")
  lhcb.AddText("LHCb Preliminary");
  lhcb.SetFillColor(RooFit.kWhite);
  lhcb.SetTextFont(132);
  lhcb.SetTextSize(0.06);
  lhcb.SetX1NDC(0.65);
  lhcb.SetX2NDC(0.65);
  lhcb.SetY1NDC(0.75);
  lhcb.SetY2NDC(0.75);
  lhcb.Draw("same");

  c.ls()
  c.Update()

  print "DENTRO MAKE CANVAS ",plot.GetXaxis().GetXmin(),plot.GetXaxis().GetXmax()

  
  #outFile.WriteTObject(c,"","Overwrite")
  figureName = outFile.GetName()
  # c.SaveAs('%s.eps'%(figureName.replace('.root','').replace('.','_').replace('1_2ps', '1.2ps').replace('1_5ps', '1.5ps')))
  # c.SaveAs('%s.pdf'%(figureName.replace('.root','').replace('.','_').replace('1_2ps', '1.2ps').replace('1_5ps', '1.5ps')))
  c.SaveAs('%s.eps'%(figureName.replace('.root','')))
  c.SaveAs('%s.pdf'%(figureName.replace('.root','')))
  outFile.WriteTObject(c,"","Overwrite")
  outFile.ls()
  plot.Print('v')

  return c
  #del c, upperPad, lowerPad 
  #del c, myPad, leg, keys, lhcb 


def makeCanvasAsym(name,width,height,hAsym,asymGraph, ymin=-0.1,ymax=+0.1) :

  from ROOT import TCanvas, TPad, RooFit, TPaveText, TLine

  hAsym.SetTitle("")
  hAsym.SetStats(RooFit.kFALSE)
  hAsym.SetMarkerStyle(20)
  hAsym.SetMarkerColor(RooFit.kBlack)
  hAsym.SetLineColor(RooFit.kBlack)
  hAsym.SetMinimum(ymin)
  hAsym.SetMaximum(ymax)
  
  hAsym.GetXaxis().SetTitleOffset(1.1)
  hAsym.GetXaxis().SetTickLength(0.05)
  hAsym.GetXaxis().SetTitleFont(132);
  hAsym.GetXaxis().SetLabelFont(132);
  hAsym.GetXaxis().SetTitleSize(0.06);
  hAsym.GetXaxis().SetLabelSize(0.06);

  hAsym.GetYaxis().SetTickLength(0.05)
  hAsym.GetYaxis().SetTitleFont(132);
  hAsym.GetYaxis().SetLabelFont(132);
  hAsym.GetYaxis().SetTitleSize(0.06);
  hAsym.GetYaxis().SetLabelSize(0.06);
  hAsym.GetYaxis().SetTitleOffset(1.70);

  hAsym.GetXaxis().SetTitle("Decay time [ps]")
  hAsym.GetYaxis().SetTitle("Asymmetry")

  asymGraph.SetLineWidth(3)
  asymGraph.SetLineColor(RooFit.kRed)
  asymGraph.SetMarkerColor(RooFit.kRed)

  c = TCanvas(name,name,width,height)
  c.cd()

  myPad = c.GetPad(0)
  myPad.SetLeftMargin(0.2)
  myPad.SetBottomMargin(0.15)
  myPad.SetBorderSize(0)
  myPad.cd()

  zero = TLine(0,0,hAsym.GetXaxis().GetXmax(),0)
  zero.SetLineStyle(2)
  hAsym.Draw("PE1")
  zero.Draw("same")
  asymGraph.Draw("PCsame")
  zero.Draw("same")
  hAsym.Draw("PE1same")
  asymGraph.Draw("PCsame")
  lhcb = TPaveText(0.5,0.75,0.68,0.85,"NDC")
  lhcb.AddText("LHCb Preliminary");
  lhcb.SetFillColor(RooFit.kWhite);
  lhcb.SetTextFont(132);
  lhcb.SetTextSize(0.05);
  #lhcb.SetX1NDC(0.65);
  #lhcb.SetX2NDC(0.65);
  #lhcb.SetY1NDC(0.75);
  #lhcb.SetY2NDC(0.75);
  lhcb.Draw("same")
  c.Update()
  return c

def makePlot(plotName,xAxisTitle,var,minVal,maxVal,nBins) :

  from ROOT import RooPlot, RooFit

  plot = var.frame(RooFit.Range(minVal,maxVal),
                   RooFit.Bins(nBins),
                   RooFit.Name('%s'%plotName),
                   RooFit.Title(''))
  plot.SetName('%s'%plotName)
  plot.SetTitle('')
  plot.GetXaxis().SetTitleSize(0.05)
  plot.GetXaxis().SetLabelSize(0.05)
  plot.GetXaxis().SetTitleOffset(1.1)
  plot.GetXaxis().SetTitle(xAxisTitle)
  plot.GetXaxis().SetTickLength(0.05)
  plot.GetXaxis().SetLabelFont(62)
  plot.GetXaxis().SetTitleFont(62)
  plot.GetYaxis().SetTitleSize(0.05)
  plot.GetYaxis().SetLabelSize(0.05)
  plot.GetYaxis().SetTitleOffset(1.7)
  plot.GetYaxis().SetTickLength(0.05)
  plot.GetYaxis().SetLabelFont(62)
  plot.GetYaxis().SetTitleFont(62)
  plot.GetXaxis().SetTitleFont(132);   
  plot.GetXaxis().SetLabelFont(132);
  plot.GetXaxis().SetTitleSize(0.06); 
  plot.GetXaxis().SetLabelSize(0.06);
  plot.GetYaxis().SetTitleFont(132);   
  plot.GetYaxis().SetLabelFont(132);
  plot.GetYaxis().SetTitleSize(0.06); 
  plot.GetYaxis().SetLabelSize(0.06);
  plot.GetYaxis().SetTitleOffset(1.70);

  return plot


def makePull(plot,var,minVal,maxVal,nBins) :

  from ROOT import RooHist, RooFit, RooPlot
  hpull = plot.pullHist()
  hpull.SetFillColor(RooFit.kBlue)
  pulls = var.frame(RooFit.Range(minVal,maxVal),
                    RooFit.Bins(nBins),
                    RooFit.Name('pull_%s'%var.GetName()),
                    RooFit.Title(''))
  pulls.SetTitle("")
  pulls.addPlotable(hpull,"BX")
  pulls.GetXaxis().SetTitleSize(0)
  pulls.GetXaxis().SetLabelSize(0)
  pulls.GetXaxis().SetTickLength(0.15) 
  pulls.GetYaxis().SetTitleSize(0.15)  
  pulls.GetYaxis().SetLabelSize(0.15)
  pulls.GetYaxis().SetTitleOffset(0.2)
  pulls.GetYaxis().SetTitle("pull")
  pulls.GetYaxis().SetRangeUser(-5,5)
  pulls.GetYaxis().SetTickLength(0.05)
  pulls.GetYaxis().SetNdivisions(502,False)
  return pulls

def plotPDFS(plot,data,pdfName,dataCut,varName,slices,varRange,conf,state,ws, numCPUs=1) :
  from ROOT import RooFit, RooArgSet, RooAbsReal, ROOT
  print conf
  config = conf[state]
  print config
  data.plotOn(plot,RooFit.Cut(dataCut),RooFit.CutRange(varRange),RooFit.Name('data'))
  print "IN PLOT PDFS ",plot.GetXaxis().GetXmin(),plot.GetXaxis().GetXmax()
  print "DATA TO BE PLOTTED: %g"%data.sumEntries()
  
  pdf = ws.obj(pdfName)
  ## Prepare projection dataset to handle quickly the plotting
  projVars = RooArgSet()
  fState = ws.obj('fState')
  projVars.add(fState)
  var = None
  var = ws.obj('timeErr')
  ## if plotting something different from timeErr then add timeErr to the projection dataset
  if var != None:
    if 'timeErr' != varName:
      projVars.add(var)

  ## select properly the projection dataset
  projds = data.reduce(RooFit.SelectVars(projVars),RooFit.Cut(dataCut),RooFit.CutRange(varRange))

  ## Add plot options
  plotopts = [RooFit.Slice(fState,state),
              RooFit.ProjWData(projVars,data),
              RooFit.NumCPU(numCPUs),
              RooFit.ProjectionRange(varRange)]#,
  #            RooFit.NormRange(varRange) ]
  plotopts += slices # ADDING REQUEST FOR DISCRETE VARIABLES

  print plotopts

  ## if plotting timeErr, remove the relative normalization
  if var != None:
    if 'timeErr' != varName:
      plotopts.append(RooFit.Normalization(1./projds.sumEntries(),RooAbsReal.Relative))
  ## create list to pass to plotOn for the global pdf
  from ROOT import RooLinkedList
  plotoptsList = RooLinkedList()
  for opt in plotopts:
    plotoptsList.Add(opt)
    opt.Print("v")
  pdf.plotOn(plot,plotoptsList)

  keys = config.keys()
  keys.sort()
  print keys
  #from ROOT import TColor
  #colorIdx = int(1000)
  for k in keys:
    #color = None
    #if type(config[k]['color']) == int:
    #  color = config[k]['color']
    #else:
    #  print config[k]['color'][0],config[k]['color'][1],config[k]['color'][2]
    #  color = TColor(colorIdx,config[k]['color'][0],config[k]['color'][1],config[k]['color'][2])
    #  color = colorIdx
    #  colorIdx = colorIdx+1

    component = config[k]['components']
    componentname = config[k]['name']
    componentplotopts = list(plotopts) 
    componentplotopts += [ RooFit.Components(component) ]
    componentplotopts += [ RooFit.Name(componentname) ]
    fillstyle = config[k]['fill']
    if fillstyle: componentplotopts += [ RooFit.DrawOption('LF2') ]
    #componentplotopts += [ RooFit.LineColor(color) ]
    #componentplotopts += [ RooFit.FillColor(color) ]
    componentplotopts += [RooFit.FillStyle(fillstyle) ]

    componentplotoptsList = RooLinkedList()
    ## create list to pass to plotOn for the various components
    for opt in componentplotopts:
      componentplotoptsList.Add(opt)
      opt.Print("v")
    ## plot the component
    pdf.plotOn(plot,componentplotoptsList)
    
    #del componentplotoptsList
    #del componentplotopts
    #del component, componentname, color


  ## plot again the total pdf for pulls
  finalplotopts = [ RooFit.Name('final'),
                     RooFit.LineColor(RooFit.kBlack) ]
  for opt in finalplotopts:
    plotoptsList.Add(opt)

  pdf.plotOn(plot,plotoptsList)
  data.plotOn(plot,RooFit.Cut(dataCut),RooFit.CutRange(varRange),RooFit.Name('data'))
  #del plotopts, plotoptsList, keys, config, pdf, projVars, fState, var, projds
  print("PLOT PDFS ENDS")
  

def makeDataAsym(inTree,varNames,varRange,stateName,taggerName,ws) :

  from ROOT import TH1D

  variables = []
  dataCut = '1>0&&'
  for name in varNames:
    var = ws.obj(name)
    variables += [var]
    varMin = var.getMin(varRange) 
    varMax = var.getMax(varRange) 
    dataCut += '%s>%g&&%s<%g&&' % (name,varMin,name,varMax)
  dataCut += '(1>0)'
  time = ws.obj('time')
  fState = ws.obj('fState')
  fState.setLabel(stateName)
  index = fState.getIndex()

  #binBorders = [0.65, 1.25, 1.85, 2.45, 3.05, 3.65, 4.25, 4.85, 5.45, 6.05, 6.65, 7.25, 7.85, 8.45, 9.05, 9.65, 10.85, 12.65] 
  h_bkpi = TH1D("h_bkpi","h_bkpi",20,time.getMin(varRange),time.getMax(varRange))
  h_bpik = TH1D("h_bpik","h_bpik",20,time.getMin(varRange),time.getMax(varRange))
  h_bbarkpi = TH1D("h_bbarkpi","h_bbarkpi",20,time.getMin(varRange),time.getMax(varRange))
  h_bbarpik = TH1D("h_bbarpik","h_bbarpik",20,time.getMin(varRange),time.getMax(varRange))

  h_bkpi.Sumw2()
  h_bpik.Sumw2()
  h_bbarkpi.Sumw2()
  h_bbarpik.Sumw2()

  inTree.Draw("time>>h_bkpi","fState==%d&&q%s==1&&p==1&&%s"%(index,taggerName,dataCut))
  print "fState==%d&&q%s==1&&p==1&&%s"%(index,taggerName,dataCut)
  inTree.Draw("time>>h_bpik","fState==%d&&q%s==1&&p==-1&&%s"%(index,taggerName,dataCut))
  print "fState==%d&&q%s==1&&p==-1&&%s"%(index,taggerName,dataCut)
  inTree.Draw("time>>h_bbarkpi","fState==%d&&q%s==-1&&p==1&&%s"%(index,taggerName,dataCut))
  print "fState==%d&&q%s==-1&&p==1&&%s"%(index,taggerName,dataCut)
  inTree.Draw("time>>h_bbarpik","fState==%d&&q%s==-1&&p==-1&&%s"%(index,taggerName,dataCut))
  print "fState==%d&&q%s==-1&&p==-1&&%s"%(index,taggerName,dataCut)

  h_mix = h_bpik.Clone("h_mix")
  h_mix.Add(h_bbarkpi)
  h_unmix = h_bkpi.Clone("h_unmix")
  h_unmix.Add(h_bbarpik)

  h_sub = h_unmix.Clone("h_sub")
  h_sum = h_unmix.Clone("h_sum")
  h_sub.Add(h_mix,-1)
  h_sum.Add(h_mix)
  h_sub.Divide(h_sum)

  return h_sub

def makeDataAsymCP(inTree,varNames,varRange,stateName,taggerName,ws) :

  from ROOT import TH1D

  variables = []
  dataCut = '1>0&&'
  for name in varNames:
    var = ws.obj(name)
    variables += [var]
    varMin = var.getMin(varRange)
    varMax = var.getMax(varRange)
    dataCut += '%s>%g&&%s<%g&&' % (name,varMin,name,varMax)
  dataCut += '(1>0)'
  time = ws.obj('time')
  fState = ws.obj('fState')
  fState.setLabel(stateName)
  index = fState.getIndex()

  h_b = TH1D("h_b","h_b",20,time.getMin(varRange),time.getMax(varRange))
  h_bbar = TH1D("h_bbar","h_bbar",20,time.getMin(varRange),time.getMax(varRange))

  h_b.Sumw2()
  h_bbar.Sumw2()

  inTree.Draw("time>>h_b","fState==%d&&q%s==1&&p==0&&%s"%(index,taggerName,dataCut))
  inTree.Draw("time>>h_bbar","fState==%d&&q%s==-1&&p==0&&%s"%(index,taggerName,dataCut))

  h_sub = h_bbar.Clone("h_sub")
  h_sum = h_bbar.Clone("h_sum")
  h_sub.Add(h_b,-1)
  h_sum.Add(h_b)
  h_sub.Divide(h_sum)

  return h_sub

def makeDataAsymBs(inTree,varNames,varRange,stateName,taggerName,ws) :

  from ROOT import TH1D
  import math
  variables = []
  dataCut = '1>0&&'
  for name in varNames:
    var = ws.obj(name)
    variables += [var]
    varMin = var.getMin(varRange) 
    varMax = var.getMax(varRange)
    dataCut += '%s>%g&&%s<%g' % (name,varMin,name,varMax)
  time = ws.obj('time')
  fState = ws.obj('fState')
  fState.setLabel(stateName)
  index = fState.getIndex()

  dM = 0
  for tmpYear in ['201516', '2017', '2017s29r2p2', '2018']:
    tmpObj =  ws.obj('bskpi_dM_%s'%tmpYear)
    if tmpObj != None:
      dM = tmpObj.getVal()
      break

  T = 2*math.acos(-1)/dM

  h_bkpi = TH1D("h_bkpi","h_bkpi",6,0,T)
  h_bpik = TH1D("h_bpik","h_bpik",6,0,T)
  h_bbarkpi = TH1D("h_bbarkpi","h_bbarkpi",6,0,T)
  h_bbarpik = TH1D("h_bbarpik","h_bbarpik",6,0,T)

  h_bkpi.Sumw2()
  h_bpik.Sumw2()
  h_bbarkpi.Sumw2()
  h_bbarpik.Sumw2()

  inTree.Draw("fmod(time-%g,%g)>>h_bkpi" % (time.getMin(varRange),T),"fState==%d&&q%s==1&&p==1&&%s"%(index,taggerName,dataCut))
  inTree.Draw("fmod(time-%g,%g)>>h_bpik" % (time.getMin(varRange),T),"fState==%d&&q%s==1&&p==-1&&%s"%(index,taggerName,dataCut))
  inTree.Draw("fmod(time-%g,%g)>>h_bbarkpi" % (time.getMin(varRange),T),"fState==%d&&q%s==-1&&p==1&&%s"%(index,taggerName,dataCut))
  inTree.Draw("fmod(time-%g,%g)>>h_bbarpik" % (time.getMin(varRange),T),"fState==%d&&q%s==-1&&p==-1&&%s"%(index,taggerName,dataCut))

  h_mix = h_bpik.Clone("h_mix")
  h_mix.Add(h_bbarkpi)
  h_unmix = h_bkpi.Clone("h_unmix")
  h_unmix.Add(h_bbarpik)

  h_sub = h_unmix.Clone("h_sub")
  h_sum = h_unmix.Clone("h_sum")
  h_sub.Add(h_mix,-1)
  h_sum.Add(h_mix)
  h_sub.Divide(h_sum)

  return h_sub

def makeDataAsymBsCP(inTree,varNames,varRange,stateName,taggerName,ws) :

  from ROOT import TH1D
  import math

  variables = []
  dataCut = '1>0&&'
  for name in varNames:
    var = ws.obj(name)
    variables += [var]
    varMin = var.getMin(varRange)
    varMax = var.getMax(varRange)
    dataCut += '%s>%g&&%s<%g&&' % (name,varMin,name,varMax)
  dataCut += '(1>0)'
  time = ws.obj('time')
  fState = ws.obj('fState')
  fState.setLabel(stateName)
  index = fState.getIndex()

  dM = 0
  for tmpYear in ['201516', '2017', '2017s29r2p2', '2018']:
    tmpObj =  ws.obj('bskpi_dM_%s'%tmpYear)
    if tmpObj != None:
      dM = tmpObj.getVal()
      break

  T = 2*math.acos(-1)/dM

  h_b = TH1D("h_b","h_b",7,0,T)
  h_bbar = TH1D("h_bbar","h_bbar",7,0,T)

  h_b.Sumw2()
  h_bbar.Sumw2()

  inTree.Draw("fmod(time-%g,%g)>>h_b" % (time.getMin(varRange),T),"fState==%d&&q%s==1&&p==2&&%s"%(index,taggerName,dataCut))
  inTree.Draw("fmod(time-%g,%g)>>h_bbar" % (time.getMin(varRange),T),"fState==%d&&q%s==-1&&p==2&&%s"%(index,taggerName,dataCut))

  h_sub = h_bbar.Clone("h_sub")
  h_sum = h_bbar.Clone("h_sum")
  h_sub.Add(h_b,-1)
  h_sum.Add(h_b)
  h_sub.Divide(h_sum)

  return h_sub

def makePdfAsym(data,pdfName,taggerName,fStateName,massRange,ws,numCPUs=1) :

  from ROOT import RooBinning, RooAbsData, TH1D, RooFit, TCanvas, RooArgSet, RooAbsReal, ROOT
  import math

  time = ws.obj('time')
  timeMin = time.getMin()
  timeMax = time.getMax()

  from ROOT import RooPlot
  pdf = ws.obj(pdfName)
  q = ws.obj("q%s"%(taggerName))
  p = ws.obj("p")
  fState = ws.obj('fState')
  timeErr = ws.obj('timeErr')
  q.setRange("taggedBKPI","B")
  q.setRange("taggedBPIK","B")
  q.setRange("taggedBbarKPI","Bbar")
  q.setRange("taggedBbarPIK","Bbar")
  p.setRange("taggedBKPI","kpi")
  p.setRange("taggedBPIK","pik")
  p.setRange("taggedBbarKPI","kpi")
  p.setRange("taggedBbarPIK","pik")
  mass = ws.obj('mass')
  massMin = mass.getMin(massRange)
  massMax = mass.getMax(massRange)
  mass.setRange("taggedBKPI",massMin,massMax)
  mass.setRange("taggedBPIK",massMin,massMax)
  mass.setRange("taggedBbarKPI",massMin,massMax)
  mass.setRange("taggedBbarPIK",massMin,massMax)

  plotT = time.frame()

  projVars = RooArgSet()
  projVars.add(fState)
  if timeErr != None:
    projVars.add(timeErr)

  projdsB2KPI    = data.reduce(RooFit.SelectVars(projVars),
                               RooFit.Cut("fState==fState::%s&&q%s==1&&p==1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  projdsB2PIK    = data.reduce(RooFit.SelectVars(projVars),
                               RooFit.Cut("fState==fState::%s&&q%s==1&&p==-1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  projdsBbar2KPI = data.reduce(RooFit.SelectVars(projVars),
                               RooFit.Cut("fState==fState::%s&&q%s==-1&&p==1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  projdsBbar2PIK = data.reduce(RooFit.SelectVars(projVars),
                               RooFit.Cut("fState==fState::%s&&q%s==-1&&p==-1"%(fStateName,taggerName)),RooFit.CutRange(massRange))

  data.plotOn(plotT,RooFit.Cut("fState==fState::%s&&q%s==1&&p==1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'kpi'),
                   RooFit.Slice(q,'B'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsB2KPI.sumEntries(),RooAbsReal.Relative),
                   #RooFit.Normalization(1./projdsB2KPI.sumEntries(),RooAbsReal.NumEvent),
                   RooFit.Name("B2KPI"),
                   RooFit.Precision(1e-5))
  
  data.plotOn(plotT,RooFit.Cut("fState==fState::%s&&q%s==1&&p==-1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'pik'),
                   RooFit.Slice(q,'B'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsB2PIK.sumEntries(),RooAbsReal.Relative),
                   #RooFit.Normalization(1./projdsB2PIK.sumEntries(),RooAbsReal.NumEvent),
                   RooFit.Name("B2PIK"),
                   RooFit.Precision(1e-5))

  data.plotOn(plotT,RooFit.Cut("fState==fState::%s&&q%s==-1&&p==1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'kpi'),
                   RooFit.Slice(q,'Bbar'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsBbar2KPI.sumEntries(),RooAbsReal.Relative),
                   #RooFit.Normalization(1./projdsBbar2KPI.sumEntries(),RooAbsReal.NumEvent),
                   RooFit.Name("Bbar2KPI"),
                   RooFit.Precision(1e-5))

  data.plotOn(plotT,RooFit.Cut("fState==fState::%s&&q%s==-1&&p==-1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'pik'),
                   RooFit.Slice(q,'Bbar'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsBbar2PIK.sumEntries(),RooAbsReal.Relative),
                   #RooFit.Normalization(1./projdsBbar2PIK.sumEntries(),RooAbsReal.NumEvent),
                   RooFit.Name("Bbar2PIK"),
                   RooFit.Precision(1e-5))

  from ROOT import TGraph, RooCurve
  asymGraph = TGraph(1000)
  bdkpi = plotT.getCurve("B2KPI")
  bdpik = plotT.getCurve("B2PIK")
  bbarkpi = plotT.getCurve("Bbar2KPI")
  bbarpik = plotT.getCurve("Bbar2PIK")
  for i in range(1000):
    x = timeMin + (timeMax-timeMin)/1000*i
    unmix = bdkpi.Eval(x)+bbarpik.Eval(x)
    mix   = bdpik.Eval(x)+bbarkpi.Eval(x)
    asym  = (unmix-mix)/(unmix+mix)
    asymGraph.SetPoint(i+1,x,asym)

  from ROOT import TCanvas
  ctmp = TCanvas('ctmpBd2KPI','ctmpBd2KPI')
  ctmp.cd()
  plotT.Draw()
  return ctmp,asymGraph


def makePdfAsymCP(data,pdfName,taggerName,fStateName,massRange,ws,numCPUs=1) :

  from ROOT import RooBinning, RooAbsData, TH1D, RooFit, TCanvas, RooArgSet, RooAbsReal, ROOT
  import math

  time = ws.obj('time')
  timeMin = time.getMin()
  timeMax = time.getMax()

  from ROOT import RooPlot
  pdf = ws.obj(pdfName)
  q = ws.obj("q%s"%(taggerName))
  p = ws.obj("p")
  fState = ws.obj('fState')
  timeErr = ws.obj('timeErr')
  q.setRange("taggedB","B")
  q.setRange("taggedBbar","Bbar")
  mass = ws.obj('mass')
  massMin = mass.getMin(massRange)
  massMax = mass.getMax(massRange)

  plotT = time.frame()

  projVars = RooArgSet()
  projVars.add(fState)
  if timeErr != None:
    projVars.add(timeErr)

  projdsB    = data.reduce(RooFit.SelectVars(projVars),
                           RooFit.Cut("fState==fState::%s&&q%s==1&&p==0"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  projdsBbar = data.reduce(RooFit.SelectVars(projVars),
                           RooFit.Cut("fState==fState::%s&&q%s==-1&&p==0"%(fStateName,taggerName)),RooFit.CutRange(massRange))

  data.plotOn(plotT,RooFit.Cut("fState==fState::%s&&q%s==1&&p==0"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'pipi'),
                   RooFit.Slice(q,'B'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsB.sumEntries(),RooAbsReal.Relative),
                   RooFit.Name("B"),
                   RooFit.Precision(1e-5))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'pipi'),
                   RooFit.Slice(q,'B'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsB.sumEntries(),RooAbsReal.Relative),
                   RooFit.Name("BdTopipi"),
                   RooFit.Precision(1e-5),
                   RooFit.Components('bdpipi_pdf'))

  data.plotOn(plotT,RooFit.Cut("fState==fState::%s&&q%s==-1&&p==0"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'pipi'),
                   RooFit.Slice(q,'Bbar'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsBbar.sumEntries(),RooAbsReal.Relative),
                   RooFit.Name("Bbar"),
                   RooFit.Precision(1e-5))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'pipi'),
                   RooFit.Slice(q,'Bbar'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsBbar.sumEntries(),RooAbsReal.Relative),
                   RooFit.Name("BbarTopipi"),
                   RooFit.Precision(1e-5),
                   RooFit.Components('bdpipi_pdf'))

  from ROOT import TGraph, RooCurve
  asymGraph = TGraph(1000)
  b    = plotT.getCurve("B")
  bbar = plotT.getCurve("Bbar")
  for i in range(1000):
    x = timeMin + (timeMax-timeMin)/1000*i
    unmix = bbar.Eval(x)
    mix   = b.Eval(x)
    asym  = (unmix-mix)/(unmix+mix)
    asymGraph.SetPoint(i+1,x,asym)
  from ROOT import TCanvas
  ctmp = TCanvas('ctmpBd2PIPI','ctmpBd2PIPI')
  ctmp.cd()
  plotT.Draw()
  ctmp.SaveAs("pdfAsymCP.root")
  return ctmp,asymGraph

def makePdfAsymBs(data,pdfName,taggerName,fStateName,massRange,ws,numCPUs=1) :

  from ROOT import RooBinning, RooAbsData, TH1D, RooFit, TCanvas, RooArgSet, RooAbsReal, ROOT
  import math

  time = ws.obj('time')
  timeMin = time.getMin()
  timeMax = time.getMax()
  dM = 0
  for tmpYear in ['201516', '2017', '2017s29r2p2', '2018']:
    tmpObj =  ws.obj('bskpi_dM_%s'%tmpYear)
    if tmpObj != None:
      dM = tmpObj.getVal()
      break

  T = 2*math.acos(-1)/dM

  from ROOT import RooPlot
  pdf = ws.obj(pdfName)
  q = ws.obj("q%s"%(taggerName))
  p = ws.obj("p")
  fState = ws.obj('fState')
  timeErr = ws.obj('timeErr')
  q.setRange("taggedBKPI","B")
  q.setRange("taggedBPIK","B")
  q.setRange("taggedBbarKPI","Bbar")
  q.setRange("taggedBbarPIK","Bbar")
  p.setRange("taggedBKPI","kpi")
  p.setRange("taggedBPIK","pik")
  p.setRange("taggedBbarKPI","kpi")
  p.setRange("taggedBbarPIK","pik")
  mass = ws.obj('mass')
  massMin = mass.getMin(massRange)
  massMax = mass.getMax(massRange)
  mass.setRange("taggedBKPI",massMin,massMax)
  mass.setRange("taggedBPIK",massMin,massMax)
  mass.setRange("taggedBbarKPI",massMin,massMax)
  mass.setRange("taggedBbarPIK",massMin,massMax)

  plotT = time.frame()

  projVars = RooArgSet()
  projVars.add(fState)
  if timeErr != None:
    projVars.add(timeErr)

  projdsB2KPI    = data.reduce(RooFit.SelectVars(projVars),
                               RooFit.Cut("fState==fState::%s&&q%s==1&&p==1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  projdsB2PIK    = data.reduce(RooFit.SelectVars(projVars),
                               RooFit.Cut("fState==fState::%s&&q%s==1&&p==-1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  projdsBbar2KPI = data.reduce(RooFit.SelectVars(projVars),
                               RooFit.Cut("fState==fState::%s&&q%s==-1&&p==1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  projdsBbar2PIK = data.reduce(RooFit.SelectVars(projVars),
                               RooFit.Cut("fState==fState::%s&&q%s==-1&&p==-1"%(fStateName,taggerName)),RooFit.CutRange(massRange))

  data.plotOn(plotT,RooFit.Cut("fState==fState::%s&&q%s==1&&p==1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'kpi'),
                   RooFit.Slice(q,'B'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsB2KPI.sumEntries(),RooAbsReal.Relative),
                   RooFit.Name("B2KPI"),
                   RooFit.Precision(1e-5))
  
  data.plotOn(plotT,RooFit.Cut("fState==fState::%s&&q%s==1&&p==-1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'pik'),
                   RooFit.Slice(q,'B'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsB2PIK.sumEntries(),RooAbsReal.Relative),
                   RooFit.Name("B2PIK"),
                   RooFit.Precision(1e-5))

  data.plotOn(plotT,RooFit.Cut("fState==fState::%s&&q%s==-1&&p==1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'kpi'),
                   RooFit.Slice(q,'Bbar'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsBbar2KPI.sumEntries(),RooAbsReal.Relative),
                   RooFit.Name("Bbar2KPI"),
                   RooFit.Precision(1e-5))
  data.plotOn(plotT,RooFit.Cut("fState==fState::%s&&q%s==-1&&p==-1"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'pik'),
                   RooFit.Slice(q,'Bbar'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsBbar2PIK.sumEntries(),RooAbsReal.Relative),
                   RooFit.Name("Bbar2PIK"),
                   RooFit.Precision(1e-5))

  from ROOT import TGraph, RooCurve
  asymGraph = TGraph(1000)
  b2kpi = plotT.getCurve("B2KPI")
  b2pik = plotT.getCurve("B2PIK")
  bbar2kpi = plotT.getCurve("Bbar2KPI")
  bbar2pik = plotT.getCurve("Bbar2PIK")

  nT = int((timeMax-timeMin)/T)
  for i in range(1000):
    unmix = 0
    mix = 0
    for iT in range(nT):
      x = timeMin+(iT+1./1000*i)*T
      unmix = unmix + bbar2pik.Eval(x)+b2kpi.Eval(x)
      mix   = mix + b2pik.Eval(x)+bbar2kpi.Eval(x)
    asym  = (unmix-mix)/(unmix+mix)
    x = 1./1000*i*T
    asymGraph.SetPoint(i+1,x,asym)

  ctmp = TCanvas('ctmpBs2PIK','ctmpBs2KPI')
  ctmp.cd()
  plotT.Draw()
  return ctmp,asymGraph


def makePdfAsymBsCP(data,pdfName,taggerName,fStateName,massRange,ws,numCPUs=1) :

  from ROOT import RooBinning, RooAbsData, TH1D, RooFit, TCanvas, RooArgSet, RooAbsReal, ROOT
  import math
  time = ws.obj('time')
  timeMin = time.getMin()
  timeMax = time.getMax()
  dM = 0
  for tmpYear in ['201516', '2017', '2017s29r2p2', '2018']:
    tmpObj =  ws.obj('bskpi_dM_%s'%tmpYear)
    if tmpObj != None:
      dM = tmpObj.getVal()
      break

  T = 2*math.acos(-1)/dM



  from ROOT import RooPlot
  pdf = ws.obj(pdfName)
  q = ws.obj("q%s"%(taggerName))
  p = ws.obj("p")
  fState = ws.obj('fState')
  timeErr = ws.obj('timeErr')
  q.setRange("taggedB","B")
  q.setRange("taggedBbar","Bbar")
  mass = ws.obj('mass')
  massMin = mass.getMin(massRange)
  massMax = mass.getMax(massRange)

  plotT = time.frame()

  projVars = RooArgSet()
  projVars.add(fState)
  if timeErr != None:
    projVars.add(timeErr)

  projdsB    = data.reduce(RooFit.SelectVars(projVars),
                           RooFit.Cut("fState==fState::%s&&q%s==1&&p==2"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  projdsBbar = data.reduce(RooFit.SelectVars(projVars),
                           RooFit.Cut("fState==fState::%s&&q%s==-1&&p==2"%(fStateName,taggerName)),RooFit.CutRange(massRange))

  data.plotOn(plotT,RooFit.Cut("fState==fState::%s&&q%s==1&&p==2"%(fStateName,taggerName)),RooFit.CutRange(massRange))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'kk'),
                   RooFit.Slice(q,'B'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsB.sumEntries(),RooAbsReal.Relative),
                   RooFit.Name("B"),
                   RooFit.Precision(1e-5))
  data.plotOn(plotT,RooFit.Cut("fState==fState::%s&&q%s==-1&&p==2"%(fStateName,taggerName)),RooFit.CutRange(massRange),
                    RooFit.MarkerColor(RooFit.kRed))
  pdf.plotOn(plotT,RooFit.Slice(fState,fStateName),
                   RooFit.Slice(p,'kk'),
                   RooFit.Slice(q,'Bbar'),
                   RooFit.ProjWData(projVars,data),
                   RooFit.NumCPU(numCPUs),
                   RooFit.ProjectionRange(massRange),
                   #RooFit.Normalization(1./projdsBbar.sumEntries(),RooAbsReal.Relative),
                   RooFit.Name("Bbar"),
                   RooFit.Precision(1e-5))

  from ROOT import TGraph, RooCurve
  asymGraph = TGraph(1000)
  b = plotT.getCurve("B")
  bbar = plotT.getCurve("Bbar")
  b.Print('v')
  bbar.Print('v')
  nT = int((timeMax-timeMin)/T)
  for i in range(1000):
    unmix = 0
    mix = 0
    for iT in range(nT):
      x = timeMin+(iT+1./1000*i)*T
      unmix = unmix + bbar.Eval(x)
      mix   = mix + b.Eval(x)
    asym  = (unmix-mix)/(unmix+mix)
    x = 1./1000*i*T
    asymGraph.SetPoint(i+1,x,asym)

  ctmp = TCanvas('ctmpBs2KK','ctmpBs2KK')
  ctmp.cd()
  plotT.Draw()
  return ctmp,asymGraph

