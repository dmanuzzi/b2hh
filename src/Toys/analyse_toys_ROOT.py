import ROOT
import numpy as np
import matplotlib.pyplot as plt
import argparse
import scipy.stats as stats
from math import pi,sqrt
import os,sys
def get_initial_parameters(root_files, variables, fit_result_name):
    init_values = {}
    init_errors = {}

    for file_name in root_files:
        file = ROOT.TFile.Open(file_name)
        if not file or file.IsZombie():
            continue

        fit_result = file.Get(fit_result_name)
        if not fit_result or not isinstance(fit_result, ROOT.RooFitResult):
            continue

        consistent = True
        for param in variables:
            val = 0
            err = 0
            rpv = fit_result.floatParsInit().find(param)
            if not rpv:
                rpv = fit_result.constPars().find(param)
                val = rpv.getVal()
                err = 0
                if not rpv:
                    print "Warning: Initial parameter {} not found in {}".format(param, file_name)
                    consistent = False
                    break
            else:
                val = rpv.getVal()
                err = rpv.getError()

            if param not in init_values:
                init_values[param] = val
                init_errors[param] = err
            else:
                if abs(init_values[param] - val) > 1e-6 or abs(init_errors[param] - err) > 1e-6:
                    print "Mismatch in initial value or error for parameter '{}' in file {}".format(param, file_name)
                    return None, None  # Inconsistent

        if consistent:
            file.Close()
            break

        file.Close()

    return init_values, init_errors

def get_all_variable_names(nfin,fit_result_name):
    file = ROOT.TFile.Open(nfin)
    if not file or file.IsZombie():
        print "Warning: Couldn't open file", file_name
        return 0

    fit_result = file.Get(fit_result_name)
    if not fit_result or not isinstance(fit_result, ROOT.RooFitResult):
        print "Warning: RooFitResult '{}' not found or invalid in {}".format(fit_result_name, file_name)
        file.Close()
        return 0
    variables = []
    rpv = fit_result.floatParsFinal()
    for i in range(0,rpv.getSize()):
        variables.append(rpv.at(i).GetName())
    rpv = fit_result.constPars()
    #for i in range(rpv.getSize())
    #    variables.append(rpv.at(i).GetName())
    return variables

def extract_fit_results(root_files, variables, fit_result_name):
    param_values = {param: [] for param in variables}
    param_errors = {param: [] for param in variables}
    edm_list = []

    n_converged = 0
    n_failed = 0
      
    
    for file_name in root_files:
        file = ROOT.TFile.Open(file_name)
        if not file or file.IsZombie():
            print "Warning: Couldn't open file", file_name
            continue

        fit_result = file.Get(fit_result_name)
        if not fit_result or not isinstance(fit_result, ROOT.RooFitResult):
            print "Warning: RooFitResult '{}' not found or invalid in {}".format(fit_result_name, file_name)
            n_failed += 1
            file.Close()
            continue

        fit_status = fit_result.status()
        edm = fit_result.edm()

        if fit_status != 0:
            print "Fit did not converge in", file_name, "(status = {})".format(fit_status)
            n_failed += 1
            file.Close()
            continue

        edm_list.append(edm)
           
        for param in variables:
            rpv = fit_result.floatParsFinal().find(param)
            if not rpv:
                rpv = fit_result.constPars().find(param)
                if not rpv:
                    print "Warning: Parameter {} not found in {}".format(param, file_name)
                    param_values[param].append(np.nan)
                    param_errors[param].append(np.nan)
                else:
                    param_values[param].append(rpv.getVal())
                    param_errors[param].append(0)
            else:
                param_values[param].append(rpv.getVal())
                param_errors[param].append(rpv.getError())
                    

        n_converged += 1
        file.Close()

    return param_values, param_errors, edm_list, n_converged, n_failed

def plot_histograms(param_values, param_errors,variables,
                    edm_list, n_converged,n_failed,
                    init_values, init_errors,
                    outdir):
    ROOT.gROOT.SetBatch(True)
    for param in variables:
        data = np.array(param_values[param])
        errs = np.array(param_errors[param])
        data = data[~np.isnan(data)]  # Remove NaNs
        errs = errs[~np.isnan(errs)]  # Remove NaNs
        init_val = init_values[param]
        init_err = init_errors[param]
                       
        # Default bin settings
        bins = 20
        mu = np.mean(data)
        rms= np.std(data)
        range_min = init_val - 5*rms
        range_max = init_val + 5*rms
        rms_mu = np.mean(errs)
        rms_rms = np.std(errs)
        range_min_err = rms_mu - 5*rms_rms
        range_max_err = rms_mu + 5*rms_rms
        
        bins_size = (range_max-range_min)/bins
        h_var = ROOT.TH1D('h_'+param, 'Histogram of %s; %s; Entries / %.3f'%(param,param,(range_max-range_min)/float(bins)),
                          bins,range_min,range_max)
        h_var.Sumw2()

        h_err = ROOT.TH1D('h_err_'+param, 'Histogram of %s errors; %s; Entries / %.3f'%(param,param,(range_max_err-range_min_err)/float(bins)),
                          bins,range_min_err,range_max_err)
        h_err.Sumw2()

        hpull = ROOT.TH1D('pull_'+param, 'Pull of %s; Pull of %s; Entries / (%d #times  %.3f)'%(param,param, len(data), 10.0/bins),
                          bins,-5,5)
        hpull.Sumw2()
        # Filling histograms
        for v,err in zip(data,errs):
            h_var.Fill(v, float(bins)/(range_max-range_min))
            h_err.Fill(err, float(bins)/(range_max_err-range_min_err))
            hpull.Fill((v-init_val)/err,float(bins)/(10.0*float(len(data))))

        #plotting values
        canv = ROOT.TCanvas("canv_"+param, "Plot of "+param,600,400)
        canv.cd()
        h_var.DrawCopy("hist")
        fgaus = ROOT.TF1('fgaus','[0]/(sqrt(2.0*acos(-1))*[2])*exp(-(x-[1])*(x-[1])/(2.0*[2]*[2]))',range_min,range_max)
        fgaus.SetParLimits(0,0.0,1000.0)
        fgaus.SetParLimits(1,range_min,range_max)
        fgaus.SetParLimits(2,0, 5*rms)
        fgaus.FixParameter(0, float(len(data)))
#        fgaus.SetParameter(0, len(data))
        fgaus.SetParameter(1, mu)
        fgaus.SetParameter(2, rms)
        fit_result = h_var.Fit(fgaus, "WL E V S")

        if fit_result.Get() and fit_result.Get().IsValid(): # chck f fit succeded       
            fit_mu = fgaus.GetParameter(1)
            fit_mu_err = fgaus.GetParError(1)
            fit_sigma = fgaus.GetParameter(2)
            fit_sigma_err = fgaus.GetParError(2)
            fit_N = fgaus.GetParameter(0)
            fit_N_err =  fgaus.GetParError(0)
            fit_chi2 = fgaus.GetChisquare()
            chi2 = h_var.Chisquare(fgaus)
            fit_ndof = fgaus.GetNDF()
            fit_p_value = ROOT.TMath.Prob(fit_chi2, fit_ndof)
            p_value = ROOT.TMath.Prob(chi2, fit_ndof)
            fgaus.SetLineColor(ROOT.kRed)
            canv.cd()
            fgaus.Draw("same")
            latex = ROOT.TLatex()
            latex.SetNDC()
            latex.SetTextSize(0.04)
            latex.DrawLatex(0.13, 0.85, "N = %.3f (fixed)"%(fit_N))
            latex.DrawLatex(0.13, 0.80, "#mu = %.3f #pm %.3f"%(fit_mu,fit_mu_err))
            latex.DrawLatex(0.13, 0.75, "#sigma = %.3f #pm %.3f"%(fit_sigma,fit_sigma_err))
            latex.DrawLatex(0.13, 0.70, "#Chi^{2}/DoF = %.3f / %d"%(chi2,fit_ndof))
            latex.DrawLatex(0.13, 0.65, "p-value = %.3f"%(p_value))
        
        canv.SaveAs("{}/{}.pdf".format(outdir,canv.GetName()))


        # Plotting errors
        canv = ROOT.TCanvas("canv_"+param+"_err", "Plot of "+param,600,400)
        canv.cd()
        h_err.SetMarkerColor(ROOT.kRed)
        h_err.SetMarkerStyle(20)
        h_err.SetLineColor(ROOT.kRed)
        h_err.DrawCopy("PE2")
        fgaus = ROOT.TF1('fgaus_err','[0]/(sqrt(2.0*acos(-1))*[2])*exp(-(x-[1])*(x-[1])/(2.0*[2]*[2]))',range_min_err,range_max_err)
        fgaus.SetParLimits(0,0.0,1000.0)
        fgaus.SetParLimits(1,range_min_err,range_max_err)
        fgaus.SetParLimits(2,0, 5*rms_rms)
        fgaus.FixParameter(0, float(len(data)))
#        fgaus.SetParameter(0, len(data))
        fgaus.SetParameter(1, rms_mu)
        fgaus.SetParameter(2, rms_rms)
        fit_result = h_err.Fit(fgaus, "WL E V S")
        if fit_result.Get() and fit_result.Get().IsValid():         # Check if fit succeeded
            fit_mu = fgaus.GetParameter(1)
            fit_mu_err = fgaus.GetParError(1)
            fit_sigma = fgaus.GetParameter(2)
            fit_sigma_err = fgaus.GetParError(2)
            fit_N = fgaus.GetParameter(0)
            fit_N_err =  fgaus.GetParError(0)
            fit_chi2 = fgaus.GetChisquare()
            chi2 = h_err.Chisquare(fgaus)
            fit_ndof = fgaus.GetNDF()
            fit_p_value = ROOT.TMath.Prob(fit_chi2, fit_ndof)
            p_value = ROOT.TMath.Prob(chi2, fit_ndof)
            fgaus.SetLineColor(ROOT.kRed)
            canv.cd()
            fgaus.SetLineColor(ROOT.kBlue)
            fgaus.Draw("same")
            latex = ROOT.TLatex()
            latex.SetNDC()
            latex.SetTextSize(0.04)
            latex.DrawLatex(0.13, 0.85, "N = %.3f (fixed)"%(fit_N))
            latex.DrawLatex(0.13, 0.80, "#mu = %.3f #pm %.3f"%(fit_mu,fit_mu_err))
            latex.DrawLatex(0.13, 0.75, "#sigma = %.3f #pm %.3f"%(fit_sigma,fit_sigma_err))
            latex.DrawLatex(0.13, 0.70, "#Chi^{2}/DoF = %.3f / %d"%(chi2,fit_ndof))
            latex.DrawLatex(0.13, 0.65, "p-value = %.3f"%(p_value))

        canv.SaveAs("{}/{}.pdf".format(outdir,canv.GetName()))

        # Plotting pulls
        canvPull = ROOT.TCanvas("canv_"+param+"_pull", "Pull of "+param,600,400)
        canvPull.cd()
        hpull.SetMarkerStyle(20)
        hpull.SetMarkerColor(ROOT.kBlack)
        hpull.SetLineColor(ROOT.kBlack)
        hpull.DrawCopy("PE2")

#        fgaus = ROOT.TF1('fgaus2','gaus',-5,+5)
        fgaus = ROOT.TF1('fgaus2','[0]/(sqrt(2.0*acos(-1))*[2])*exp(-(x-[1])*(x-[1])/(2.0*[2]*[2]))',-5,+5)
        fgaus.SetParLimits(0,0.0,100.0)
        fgaus.SetParLimits(1,-5.0,+5.0)
        fgaus.SetParLimits(2,0,+5.0)
        fgaus.FixParameter(0, 1.0)
        fgaus.SetParameter(1, 0.0)
        fgaus.SetParameter(2, 1.0)
        fgaus.Print()
        fit_result = hpull.Fit(fgaus, "WL SQ")
        fit_result.Print("v")
        # Check if fit succeeded
        if fit_result.Get() and fit_result.Get().IsValid():
            cov_matrix = fit_result.Get().GetCovarianceMatrix()
            cov_02 = cov_matrix[0][2]  # or use .At(i, j)

            fit_mu = fgaus.GetParameter(1)
            fit_mu_err = fgaus.GetParError(1)
            fit_sigma = fgaus.GetParameter(2)
            fit_sigma_err = fgaus.GetParError(2)
            fit_N = fgaus.GetParameter(0)
            fit_N_err =  fgaus.GetParError(0)
            fit_chi2 = fgaus.GetChisquare()
            chi2 = hpull.Chisquare(fgaus)
            fit_ndof = fgaus.GetNDF()
            fit_p_value = ROOT.TMath.Prob(fit_chi2, fit_ndof)
            p_value = ROOT.TMath.Prob(chi2, fit_ndof)
            fgaus.SetLineColor(ROOT.kRed)
            canvPull.cd()
            fgaus.Draw("same")
            latex = ROOT.TLatex()
            latex.SetNDC()
            latex.SetTextSize(0.04)
#            latex.DrawLatex(0.13, 0.85, "N = %.3f #pm %.3f"%(fit_N,fit_N_err))
            latex.DrawLatex(0.13, 0.85, "N = %.3f (fixed)"%(fit_N))
            latex.DrawLatex(0.13, 0.80, "#mu = %.3f #pm %.3f"%(fit_mu,fit_mu_err))
            latex.DrawLatex(0.13, 0.75, "#sigma = %.3f #pm %.3f"%(fit_sigma,fit_sigma_err))
            latex.DrawLatex(0.13, 0.70, "#Chi^{2}/DoF = %.3f / %d"%(chi2,fit_ndof))
            latex.DrawLatex(0.13, 0.65, "p-value = %.3f"%(p_value))

        fnorm = ROOT.TF1('fnorm','gaus',-5,+5)
        fnorm.SetLineColor(ROOT.kGreen+2)
        fnorm.SetLineStyle(ROOT.kDashed)
        fnorm.SetParameter(0, 1.0/sqrt(2*pi))
        fnorm.SetParameter(1, 0.0)
        fnorm.SetParameter(2, 1.0)
        fnorm.Print("v")
        fnorm.Draw("same")

        canvPull.SaveAs("{}/{}.pdf".format(outdir,canvPull.GetName()))
        
        
    '''
    # EDM plot
    edm_ax = axs[2*n_vars]
    edm_data = np.array(edm_list)
    edm_ax.hist(edm_data, bins=20, alpha=0.7, color='blue', edgecolor='black')
    edm_ax.set_title("EDM Distribution")
    edm_ax.set_xlabel("EDM")
    edm_ax.set_ylabel("Entries")
    if len(edm_data) > 0:
        mean = np.mean(edm_data)
        rms = np.std(edm_data)
        text = "Mean = {:.3f}\nRMS  = {:.3f}".format(mean, rms)
        edm_ax.text(0.95, 0.95, text,
                    transform=edm_ax.transAxes,
                    verticalalignment='top',
                    horizontalalignment='right',
                    fontsize=10,
                    bbox=dict(facecolor='white', alpha=0.6, edgecolor='gray'))
    
    # Fit status summary
    status_ax = axs[2*n_vars + 1]
    #status_ax.bar(["Converged", "Failed"], [n_converged, n_failed], color=["green", "red"], alpha=0.7)
    x = [0, 1]
    status_ax.bar(x, [n_converged, n_failed], color=["green", "red"], alpha=0.7)
    status_ax.set_xticks(x)
    status_ax.set_xticklabels(["Converged", "Failed"])
    status_ax.set_title("Fit Status Summary")
    status_ax.set_ylabel("Number of Fits")
    
    try:
        plt.tight_layout()
    except RuntimeError:
        print("Warning: tight_layout failed, using subplots_adjust instead.")
        plt.subplots_adjust(hspace=0.4, wspace=0.3, top=0.95, bottom=0.05, left=0.07, right=0.95)
    plt.savefig(output_pdf)
    print "Plots saved to:", output_pdf
    plt.show()
        '''
def main():
    parser = argparse.ArgumentParser(description="Analyze RooFitResult from ROOT files.")
    parser.add_argument(
        "-f", "--files", nargs="+", required=True,
        help="List of ROOT files containing RooFitResult"
    )
    parser.add_argument(
        "-v", "--variables", default="all",
        help="Comma-separated list of parameter names to extract (e.g., A,B,C)"
    )
    parser.add_argument(
        "-n", "--fitname", default="nll_pdf_data",
        help="Name of the RooFitResult object inside the ROOT files"
    )
    parser.add_argument(
        "-o", "--outdir", default="./plots",
        help="Output directory for plots"
    )

    args = parser.parse_args()

    root_files = args.files
    fit_result_name = args.fitname
    if args.variables == 'all':
        variables = get_all_variable_names(root_files[0],fit_result_name)
    else:
        variables = [v.strip() for v in args.variables.split(",")]

    
    param_values, param_errors, edm_list, n_converged, n_failed = extract_fit_results(
        root_files, variables, fit_result_name
    )

    print "\nSummary:"
    print "Converged fits:", n_converged
    print "Failed fits   :", n_failed
    print "\nExtracted values:"
    for param in variables:
        print "{}: {}".format(param, param_values[param])
        
    init_values, init_errors = get_initial_parameters(root_files, variables, fit_result_name)

    if not os.path.exists(args.outdir):
        print "\nCreating directory {}".format(args.outdir)
        os.makedirs(args.outdir)
    plot_histograms(param_values, param_errors,variables,
                    edm_list, n_converged, n_failed,
                    init_values, init_errors,
                    outdir=args.outdir)

if __name__ == "__main__":
    main()
