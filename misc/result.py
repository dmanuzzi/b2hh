import ROOT
ROOT.gROOT.SetBatch()
import re
import array
import os

def extract_values_from_file(base_path, year, channel):
    file_path = f"{base_path}/GraNEW_0.86_{year}_Tot/params_GraNEW_0.86_OS_SSk_Tot.txt.Unblind"
    file_path = f"{base_path}/GraNEW_0.86_{year}_Tot/params_GraNEW_0.86_OS_SS_Tot.txt.Unblind"
    label = f"{channel}_{year}"
    pattern = re.compile(
        fr'^{re.escape(label)}\s*=\s*([\-+]?\d*\.?\d+(?:[eE][\-+]?\d+)?)\s*\+/-\s*([\-+]?\d*\.?\d+(?:[eE][\-+]?\d+)?)'
    )

    with open(file_path, 'r') as f:
        for line in f:
            match = pattern.match(line)
            if match:
                y = float(match.group(1))
                ey = float(match.group(2))
                ex = 0.0  # No uncertainty on x
                return y, ey, ex

    raise ValueError(f"No match found for {label}")

# Paths and config
basepath = "/home/ceph/mcaporal/bspipi/index/FitTotal/out"
channels = ["bdpipi_C","bdpipi_S","bskk_C","bskk_S","bskk_D","bdkpi_ACP","bskpi_ACP"] #"bspipi_C", "bspipi_S","bspipi_D",
years = ["201516", "2017s29r2p2", "2018"]

os.makedirs("plots", exist_ok=True)

canvasAll = ROOT.TCanvas("","",800,2000)
canvasAll.Divide(2,5)
canvasIterationIndex = 1

# Loop over each channel
for channel in channels:
    x_vals = []
    y_vals = []
    ex_vals = []
    ey_vals = []
    labels = []

    for i, year in enumerate(years):
        try:
            y, ey, ex = extract_values_from_file(basepath, year, channel)
            x_vals.append(i)
            y_vals.append(y)
            ex_vals.append(ex)
            ey_vals.append(ey)
            labels.append(year)
        except Exception as e:
            print(f"Warning: {channel}_{year}: {e}")

    n = len(x_vals)
    if n == 0:
        print(f"No valid points for {channel}")
        continue

    # Create TGraphErrors
    graph = ROOT.TGraphErrors(
        n,
        array.array("d", x_vals),
        array.array("d", y_vals),
        array.array("d", ex_vals),
        array.array("d", ey_vals)
    )    

    graph.SetName(f"graph_{channel}")
    graph.SetTitle(f"{channel};Year;Value")
    tf1min = -0.5 #on the x axis
    tf1max = 3.5

    fitFunc = ROOT.TF1(f"fitfunc_{channel}","[0]",tf1min,tf1max)
    fitFunc.SetParameter(0,0)
    fitFunc.SetLineColor(ROOT.kRed)
    graph.Fit(fitFunc)

    fitFuncUp  = ROOT.TF1(f"fitfuncUp_{channel}","[0]",tf1min,tf1max)
    fitFuncUp.SetParameter(0,fitFunc.GetParameter(0)+fitFunc.GetParError(0))
    fitFuncLow = ROOT.TF1(f"fitfuncLow_{channel}","[0]",tf1min,tf1max)
    fitFuncLow.SetParameter(0,fitFunc.GetParameter(0)-fitFunc.GetParError(0))
    fitFuncUp2  = ROOT.TF1(f"fitfuncUp2_{channel}","[0]",tf1min,tf1max)
    fitFuncUp2.SetParameter(0,fitFunc.GetParameter(0)+2*fitFunc.GetParError(0))
    fitFuncLow2 = ROOT.TF1(f"fitfuncLow2_{channel}","[0]",tf1min,tf1max)
    fitFuncLow2.SetParameter(0,fitFunc.GetParameter(0)-2*fitFunc.GetParError(0))
    fitFuncUp3  = ROOT.TF1(f"fitfuncUp3_{channel}","[0]",tf1min,tf1max)
    fitFuncUp3.SetParameter(0,fitFunc.GetParameter(0)+3*fitFunc.GetParError(0))
    fitFuncLow3 = ROOT.TF1(f"fitfuncLow3_{channel}","[0]",tf1min,tf1max)
    fitFuncLow3.SetParameter(0,fitFunc.GetParameter(0)-3*fitFunc.GetParError(0))
    fitFuncUp.SetLineColorAlpha(ROOT.kRed,0.5)
    fitFuncLow.SetLineColorAlpha(ROOT.kRed,0.5)
    fitFuncUp2.SetLineColorAlpha(ROOT.kRed,0.3)
    fitFuncLow2.SetLineColorAlpha(ROOT.kRed,0.3)
    fitFuncUp3.SetLineColorAlpha(ROOT.kRed,0.2)
    fitFuncLow3.SetLineColorAlpha(ROOT.kRed,0.2)

    graph.SetMarkerStyle(20)

    # Create dummy histogram frame to hold x-axis labels
    hframe = ROOT.TH1F(f"hframe_{channel}", f"hframe_{channel}", n, -0.5, n - 0.5)

    for i, label in enumerate(labels):
        hframe.GetXaxis().SetBinLabel(i + 1, label)
    ROOT.gStyle.SetOptFit(1)

    canvas = ROOT.TCanvas(channel, channel, 800, 600)
    canvas.cd()
    hframe.SetMinimum(min(y_vals) - max(ey_vals)*1.5)
    hframe.SetMaximum(max(y_vals) + max(ey_vals)*1.5)
    hframe.SetStats(0)
    hframe.SetTitle(f";{channel};")
    hframe.Draw("AXIS")  
    graph.Draw("P SAME")
    fitFunc.Draw("SAME")
    fitFuncUp.Draw("SAME")
    fitFuncLow.Draw("SAME")    
    fitFuncUp2.Draw("SAME")
    fitFuncLow2.Draw("SAME")
    fitFuncUp3.Draw("SAME")
    fitFuncLow3.Draw("SAME")
    canvas.SaveAs(f"plots/{channel}.pdf")
    canvas.SaveAs(f"plots/{channel}.root")
