from include import *
from array import array

def read_value_error(f):
    return tuple(map(float, f.readline().strip().split(" \\pm ")))

myBins = []
counts = []
bin_means = []
resolution = []
for (bIndex, b) in enumerate(bins):
    if bIndex == len(myBins) - 1: continue
    myBins.append(b)
    f = open("{}/{:03d}.txt".format(fit_dir, bIndex))
    bin_means.append(float(f.readline().strip()))
    counts.append(float(f.readline().strip()))
    mean = read_value_error(f)
    sigma = read_value_error(f)
    sigma2 = read_value_error(f)
    frac = read_value_error(f)
    myResolution = read_value_error(f)
    dilution = read_value_error(f)
    sigma_eff = read_value_error(f)
    if options.combVar == "sigma":
        resolution.append(sigma)
    elif options.combVar == "weighted_sum":
        resolution.append(myResolution)
    elif options.combVar == "eff_sigma":
        resolution.append(sigma_eff)
    else:
        assert(False)
    f.close()

c = ROOT.TCanvas("c", "c", 800, 600)
c.cd()

graph = ROOT.RooHist(myBins[0][1] - myBins[0][0])
for (b, m, v) in zip(myBins, bin_means, resolution):
    if options.centerBin:
        bin_mean = sum(b) / 2.
        lower_error = upper_error = (b[1] - b[0]) / 2.
    else:
        bin_mean = m
        lower_error = bin_mean - b[0]
        upper_error = b[1] - bin_mean

    graph.addBinWithXYError(bin_mean, v[0], lower_error, upper_error, v[1], v[1])

bounds = (myBins[0][0], 100.)# myBins[-1][1])

graph.SetTitle("Decay-time resolution")
graph.SetMarkerStyle(ROOT.kDot)
graph.GetXaxis().SetTitle("Per-event decay-time error, #sigma_{{t}} ({})".format('fs'))
graph.GetXaxis().SetRangeUser(0., bounds[1])
graph.GetYaxis().SetTitle("Decay-time resolution, #sigma ({})".format('fs'))
graph.GetYaxis().SetTitleOffset(1.25)
graph.GetYaxis().SetRangeUser(0., bounds[1])

counts_overlay = "DsK_Data_Weighted"
if counts_overlay == "DsPi_MC":
    counts_overlay_file = ROOT.TFile.Open({"DsPi_MC": "{}/TD_DsK3fb_MC/B2DX_MC_Bs_Dspi_KKpi_PTR.root".format(base_dir)}[counts_overlay])
    counts_overlay_tree = counts_overlay_file.Get("DecayTree")
    assert(isinstance(counts_overlay_tree, ROOT.TTree))
    counts_overlay_tree.Draw("lab0_LifetimeFit_ctauErr0/{}>>counts_overlay_th1".format(speedOfLight_mm_fs))
    counts_overlay_th1 = ROOT.gDirectory.Get("counts_overlay_th1")
    counts_overlay_th1.Scale(1./150.)
    #h_counts = ROOT.RooHist(counts_overlay_th1)
elif counts_overlay == "DsK_Data_Weighted":
    counts_overlay_file = ROOT.TFile.Open("DsK_Nominal_Weighted.root")
    counts_overlay_data = counts_overlay_file.Get("dataSet_time_weighted")
    assert(isinstance(counts_overlay_data, ROOT.RooDataSet))
    counts_overlay_var = ROOT.RooRealVar("BeautyTimeErr", "BeautyTimeErr", 0., 100., "ps")
    counts_overlay_var2 = counts_overlay_data.addColumn(RooFormulaVar("BeautyTimeErr_fs", "BeautyTimeErr_fs", "BeautyTimeErr*1000.", RooArgList(counts_overlay_var)))
    counts_overlay_th1 = ROOT.RooAbsData.createHistogram(counts_overlay_data, "counts_overlay_th1", counts_overlay_var2, ROOT.RooFit.Binning(22, 0., 100.))
    # Scale is arbitrary, just to make it fit nicely in the existing plot
    counts_overlay_th1.Scale(3.8 * 100. / counts_overlay_data.sumEntries())
    counts_overlay_th1.SetOption("")
    counts_overlay_th1.SetMarkerStyle(ROOT.kDot)
    counts_overlay_th1.SetMarkerSize(0.)

"""
h_counts = ROOT.RooHist(myBins[0][1] - myBins[0][0])
h_counts.SetFillColorAlpha(ROOT.kRed, 0.)
h_counts.SetLineColor(ROOT.kRed)
for (b, c) in zip(myBins, counts):
    bin_mean = sum(b) / 2.
    if options.centerBin:
        lower_error = upper_error = (b[1] - b[0]) / 2.
    else:
        lower_error = bin_mean - b[0]
        upper_error = b[1] - bin_mean

    h_counts.addBinWithXYError(bin_mean, c * bounds[1] / (1.1 * max(counts)), lower_error, upper_error, 0., 0.)
#h_counts.Scale(bounds[1] / (1.1 * max(counts)))
"""

mean = 36.

"""
formula = ROOT.TF1("fquad", "[0]*x*x + [1]*x + [2]", *bounds)
formula.SetParameter(0, 0.)
formula.SetParameter(1, 1.)
formula.SetParameter(2, 0.)
formula.SetLineColor(ROOT.kBlue)
fitResult_quad = graph.Fit(formula, "VS+")
fitResult_quad.Print()

formula = ROOT.TF1("flin", "[0]*x", *bounds)
formula.SetParameter(0, 1.)
formula.SetParameter(1, 0.)
formula.SetLineColor(ROOT.kRed)
fitResult_lin = graph.Fit(formula, "VS+")
fitResult_lin.Print()
"""

formula = ROOT.TF1("flin_decor", "[0]*(x-{}) + [1]".format(mean), *bounds)
formula.SetParameter(0, 1.)
formula.SetParameter(1, 55.)
formula.SetLineColor(ROOT.kMagenta)
fitResult_lin_decor = graph.Fit(formula, "VS+")
fitResult_lin_decor.Print()

#formula = ROOT.TF1("fmodel", "sqrt([0]*[0]*x*x + [1]*[1])", *bounds)
#formula.SetParameter(0, 1.)
#formula.SetParameter(1, 0.)
#formula.SetLineColor(ROOT.kCyan)
#fitResult_model = graph.Fit(formula, "VS+")
#fitResult_model.Print()

singleGauss = ROOT.TF1("singleGauss", "1.772 * x", 0., 100.)
singleGauss.SetLineColor(ROOT.kMagenta)
singleGauss.SetLineStyle(ROOT.kDashed)
secondApproach = ROOT.TF1("secondApproach", "1.243 * x + 0.568", 0., 100.)
secondApproach.SetLineColor(ROOT.kMagenta)
secondApproach.SetLineStyle(ROOT.kDashed)

one = ROOT.TF1("one", "x", *bounds)
one.SetLineColor(ROOT.kGreen)
old = ROOT.TF1("old", "1.37*x", *bounds)
old.SetLineColor(ROOT.kOrange)

lhcbName = ROOT.TPaveText(ROOT.gStyle.GetPadLeftMargin() + 0.05, 0.91 - ROOT.gStyle.GetPadTopMargin(), ROOT.gStyle.GetPadLeftMargin() + 0.20, 0.99 - ROOT.gStyle.GetPadTopMargin(), "BRNDC");
lhcbName.AddText("LHCb");
lhcbName.SetFillColor(0);
lhcbName.SetTextAlign(12);
lhcbName.SetBorderSize(0);

BsDsPi_Latex = "#font[12]{B^{0}_{s}#rightarrow D_{s}^{#font[122]{-}} #pi^{+}}"
BsDsK_Latex  = "#font[12]{B^{0}_{s}#rightarrow D_{s}^{#mp} K^{#pm}}"

legend = ROOT.TLegend(.23, .75, .55, .87)
legend.SetFillColor(0)
legend.SetTextSize(0.045)
legend.AddEntry(graph, "Prompt #font[12]{D_{s}} data", "LE")
legend.AddEntry(counts_overlay_th1, {"DsPi_MC": BsDsPi_Latex + " MC", "DsK_Data_Weighted": BsDsK_Latex + " data"}[counts_overlay], "F")

c = ROOT.TCanvas("c", "c", 800, 600)
c.cd()

graph.Draw("APZ0")
counts_overlay_th1.Draw("AH SAME HIST")
lhcbName.Draw()
legend.Draw("SAME")
singleGauss.Draw("SAME")
secondApproach.Draw("SAME")
ROOT.gPad.Modified()
ROOT.gPad.Update()

c.SaveAs("{}/CombinationLinear_{}.pdf".format(fit_dir, comb_desc))

with open("{}/CombinationLinear_{}.txt".format(fit_dir, comb_desc), "w") as f:
    #f.write("Quadratic: ({:.3f} \\pm {:.3f}) \\delta_{{\\tau}}^2 + ({:.3f} \\pm {:.3f}) \\delta_{{\\tau}} + ({:.3f} \\pm {:.3f})\n".format(fitResult_quad.Value(0), fitResult_quad.Error(0), fitResult_quad.Value(1), fitResult_quad.Error(1), fitResult_quad.Value(2), fitResult_quad.Error(2)))
    #f.write("Linear: ({:.3f} \\pm {:.3f}) \\delta_{{\\tau}} + ({:.3f} \\pm {:.3f})\n".format(fitResult_lin.Value(0), fitResult_lin.Error(0), fitResult_lin.Value(1), fitResult_lin.Error(1)))
    f.write("Linear: ({:.3f} \\pm {:.3f}) (\\delta_{{\\tau}} - 40 fs) + ({:.3f} \\pm {:.3f})\n".format(fitResult_lin_decor.Value(0), fitResult_lin_decor.Error(0), fitResult_lin_decor.Value(1), fitResult_lin_decor.Error(1)))

"""
# DILUTION
graph = ROOT.RooHist(myBins[0][1] - myBins[0][0])
for (b, v) in zip(myBins, dilution):
    graph.addBinWithError((b[1] + b[0]) / 2., v[0], v[1], v[1], b[1] - b[0], 1., ROOT.kFALSE)

graph.SetTitle("Dilution")
graph.SetMarkerStyle(ROOT.kDot)
graph.GetXaxis().SetTitle("Per-event decay-time error")
graph.GetXaxis().SetRangeUser(myBins[0][0], myBins[-1][1])
graph.GetYaxis().SetTitle("Dilution")
graph.GetYaxis().SetTitleOffset(1.25)
graph.GetYaxis().SetRangeUser(0., 1.)

graph.Draw("AP")
c.SaveAs("FitResults/Dilution_{}.pdf".format(desc))
"""

