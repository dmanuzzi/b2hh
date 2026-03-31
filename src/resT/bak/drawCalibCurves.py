import ROOT

f = open('resolution_stats.txt', 'r')
lines = f.read().split('Tag')[1:]
print lines
f.close()
colors = {
    'MC_2015_Jpsi' : [ROOT.kRed, 1],
    'MC_2016_Jpsi' : [ROOT.kOrange+7, 1],
    'MC_2017_Jpsi' : [ROOT.kGreen+2, 1],
    'MC_2018_Jpsi' : [ROOT.kBlue, 1],
    'data_2015_Jpsi' : [ROOT.kRed, 2],
    'data_2016_Jpsi' : [ROOT.kOrange+7, 2],
    'data_2017_Jpsi' : [ROOT.kGreen+2, 2],
    'data_2018_Jpsi' : [ROOT.kBlue, 2],
    
    #'MC_2015_Y3S' : [ROOT.kRed, 2],
    # 'MC_2016_Y3S' : [ROOT.kOrange+7, 2],
    # 'MC_2017_Y3S' : [ROOT.kGreen+2, 2],
    # 'MC_2018_Y3S' : [ROOT.kBlue, 2],
}
ROOT.TF1.DrawClone._creates = False
ROOT.TGraph.DrawClone._creates = False
ROOT.TGraphErrors.DrawClone._creates = False

c = ROOT.TCanvas('SimpleCalib', 'SimpleCalib')
c.cd()
f = ROOT.TF1("f","[0]+[1]*(x-[2])",0.0,0.1)
gs = []
for line in lines:
    tag = line.split(',')[0] 
    tag = tag.replace(': ','')
    print tag
    params = line.split('\n')[1].replace('[0]+[1]*(x-[2]) --->', '').replace(' ','').split(';')[:-1]
    print params
    par0 = params[0].replace('[0]=','').split('+/-')
    par1 = params[1].replace('[1]=','').split('+/-')
    par2 = params[2].replace('[2]=','').split('+/-')
    print par0, par1, par2
    maxVal = 0.1
    f.SetTitle(tag)
    f.SetName(tag)
    f.SetParameter(0,float(par0[0]))
    f.SetParameter(1,float(par1[0]))
    f.SetParameter(2,float(par2[0]))
    print f.GetParameter(0), f.GetParameter(1), f.GetParameter(2)
    if tag not in colors.keys():
        print 'wrong tag: ', tag, 'EXIT!'
        break
    f.SetLineColor(colors[tag][0])
    f.SetLineStyle(colors[tag][1])
    f.Print("v")
    
    if line == lines[0]:
        f.Draw()
        print 'stocazzo'
    else:
        f.DrawClone("Lsame")
        print 'sticazzi'
#    c.Update()
    
    fcanv = ROOT.TFile('plots/%s.root'%tag)
    canv = fcanv.Get('cSF_'+tag)
    print 'fanculo'
    canv.ls()
    g = canv.GetListOfPrimitives().At(1).Clone()
    gx = g.GetX()
    gy = g.GetY()
    gxe = g.GetEX()
    gye = g.GetEY()
    print gx
    print gy
    gg = ROOT.TGraph(10, gx, gy)
    #gg.SetPointError(0,0,0)
    gs.append(gg)
    gg.Print()
    gg.SetName('g_'+tag)
    gg.SetTitle('g_'+tag)    
    gs[-1].Print()
    gg.SetMarkerColor(colors[tag][0])
    gg.GetXaxis().Print("v")
    print gg.GetXaxis().GetXmin(), gg.GetXaxis().GetXmax()
    g.GetYaxis().Print("v")
    print gg.GetYaxis().GetXmin(), gg.GetYaxis().GetXmax()
    gs[-1].Draw("Psame")
    #fcanv.Close()
    c.Update()
    break

c.BuildLegend()
c.Update()
c.SaveAs("plots/%s.root"%c.GetName())
c.SaveAs("plots/%s.pdf"%c.GetName())
c.SaveAs("plots/%s.png"%c.GetName())
