from ROOT import *

from SomeMassModels.FiterBasis import *
from Bs2JpsiPhiParams import CBparams_smeared_noMatch#, CBparams_smeared#, CBparams

gROOT.ProcessLine(\
    "struct MyStruct{\
     Float_t sWFloat;\
    };")
from ROOT import MyStruct

class SigIpatiaFiter(FiterBasis):
    def __init__(self,tree, var,cuts="", shorTime = False, weight_var=0): FiterBasis. __init__(self,tree, var,cuts, shorTime, weight_var, sigf = ipatia_signal, bkgf = exp_bkg, fit_in_init = 0)


fixParams = ["a","a2","n","n2","zeta", "l"]
AllParams = ["a","a2","n","n2","zeta", "l"] + ["mean","sigma", "indx"]

def doMassFit(tuple, tailtable, wvar, var = "mass"):
    fitter = SigIpatiaFiter(tuple, var, "",weight_var = wvar)
    for thing in fixParams:
        val = getattr(tailtable,thing)
        if val < getattr(fitter,thing).getMin(): getattr(fitter,thing).setMin(val - 0.1)
        if val > getattr(fitter,thing).getMax(): getattr(fitter,thing).setMax(val + 0.1)
        getattr(fitter,thing).setVal(val)
        getattr(fitter,thing).setConstant(kTRUE)
    fitter.fit(minos = kFALSE)
    for thing in AllParams: getattr(fitter,thing).setConstant(kTRUE)
    return fitter

class sWeighter:
    def __init__(self,name, op):
        #op.fit(minos=kFALSE)
        self.sData = RooStats.SPlot("sData " + name ,"An SPlot" + name,op.data,op.model,RooArgList(op.nsig, op.nbkg))
        self.sWlits = 2*[[]]
        self.sWValue = MyStruct()
        self.sWBranch = op.tree.Branch("sWeights_" + name, AddressOf(self.sWValue,'sWFloat'), "sWeights_" + name + "/F")
        for i in range(op.tree.GetEntries()):
            #self.sWList[0].append(self.sData.GetSWeight(i,"nsig"))
            #self.sWList[1].append(self.sData.GetSWeight(i,"nbkg"))
            self.sWValue.sWFloat = self.sData.GetSWeight(i,"nsig")#sWList[0][entry] 
            self.sWBranch.Fill()

        op.tree.Write("",TObject.kOverwrite)


## from ROOT import *
## from Bs2JpsiPhiParams.Selections import KKbins
## f = TFile("nTupleC_merged.root")
## t = f.Get("DecayTree")
## f2 = TFile("/tmp/uoeo.root","recreate")
## t2 = t.CopyTree(KKbins[0])
## op = doMassFit(t2,CBparams_smeared_noMatch.BiasedBin1,"wMC")
## b = sWeighter("ipa",op)
