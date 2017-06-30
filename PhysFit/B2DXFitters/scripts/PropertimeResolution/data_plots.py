from include import *

from ROOT import TFile, TTree
from ROOT import RooFit, RooAddPdf, RooArgList, RooArgSet, RooCBShape, RooFormulaVar, RooGaussian, RooRealVar, RooWorkspace

print("Writing to {}".format(dp_dir))

print("Opening the workspace...")
f = TFile.Open(os.path.join(ws_dir, "w_data_{}.root".format(desc)))
w = f.Get("w")
dataset = w.data('data')
assert(isinstance(dataset, ROOT.RooAbsData))

x = w.var("lab0_MM")
frame = x.frame()
dataset.plotOn(frame)
c = ROOT.TCanvas('c', 'c')
frame.Draw()
c.SaveAs(os.path.join(dp_dir, "lab0_MM.pdf"))
del c
del frame
del x

x = w.var("lab2_MM")
frame = x.frame(1890., 2070.)
dataset.plotOn(frame)
c = ROOT.TCanvas('c', 'c')
frame.Draw()
c.SaveAs(os.path.join(dp_dir, "lab2_MM.pdf"))
del c
del frame
del x

x = w.var("lab0_LifetimeFit_TAU")
frame = x.frame(-500., 50000.)
dataset.plotOn(frame)
c = ROOT.TCanvas('c', 'c')
frame.Draw()
c.SaveAs(os.path.join(dp_dir, "lab0_LifetimeFit_TAU.pdf"))
del c
del frame
del x

if is_MC:
    x = w.var("lab0_TRUETAU")
    frame = x.frame(0., 0.02)
    dataset.plotOn(frame)
    c = ROOT.TCanvas('c', 'c')
    frame.Draw()
    c.SaveAs(os.path.join(dp_dir, "lab0_TRUETAU.pdf"))
    del c
    del frame
    del x

    x = w.var("lab0_LifetimeFit_TAU_DIFF")
    frame = x.frame(-150., 150.)
    dataset.plotOn(frame)
    c = ROOT.TCanvas('c', 'c')
    frame.Draw()
    c.SaveAs(os.path.join(dp_dir, "lab0_LifetimeFit_TAU_DIFF.pdf"))
    del c
    del frame
    del x

x = w.var("lab0_LifetimeFit_TAU_PULL")
frame = x.frame(-10., 10.)
dataset.plotOn(frame)
c = ROOT.TCanvas('c', 'c')
frame.Draw()
c.SaveAs(os.path.join("lab0_LifetimeFit_TAU_PULL.pdf"))
del c
del frame
del x

x = w.var("lab0_LifetimeFit_TAUERR")
frame = x.frame(0., 150.)
dataset.plotOn(frame)
c = ROOT.TCanvas('c', 'c')
frame.Draw()
c.SaveAs(os.path.join("lab0_LifetimeFit_TAUERR.pdf"))
del c
del frame
del x

cuts_bin = "lab0_LifetimeFit_ctauErr0/{0} > 23.44 && lab0_LifetimeFit_ctauErr0/{0} < 24.24".format(speedOfLight_mm_fs)
x = w.var("lab0_LifetimeFit_TAU")
frame = x.frame(-100., 300.)
dataset.reduce(cuts_bin).plotOn(frame)
c = ROOT.TCanvas('c', 'c')
frame.Draw()
c.SaveAs(os.path.join("lab0_LifetimeFit_TAU_bin.pdf"))
del c
del frame
del x

f.Close()

