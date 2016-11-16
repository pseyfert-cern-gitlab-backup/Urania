from ROOT import *
import os
f = TFile(os.environ["KS2MUMUROOT"] + "/operators/2011_MarkovChainPosterior.root")
hm = f.Get("posterior")

gROOT.ProcessLine(".L $URANIAROOT/src/RooAmorosoPdf.cxx++")

x = RooRealVar("posterior", "posterior", hm.GetBinLowEdge(1),hm.GetBinLowEdge(hm.GetNbinsX()+1))

theta = RooRealVar("theta","theta",-10, -1000,-0.11)#1000) ## kind of sigma
alpha = RooRealVar("alpha","alpha",1)#, .1, 10) alpha = 1 is Fisher-Tippet distrib.
offset = RooRealVar("mean","mean",20,1,300)
beta = RooRealVar("beta", "beta", 2,-7,3000)
## var = "B_s0_MMERR"
h2m = RooDataHist(x.GetName(),x.GetName(),RooArgList(x), hm)
model = RooAmorosoPdf("testing", "testing" ,x, offset, theta, alpha, beta)
fr = x.frame()
model.fitTo(h2m, RooFit.Offset(kTRUE), RooFit.Minos(kTRUE))
h2m.plotOn(fr)
model.plotOn(fr)
fr.Draw()
