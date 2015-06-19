from SomeUtils.numericFunctionClass import NF
import RooKstar
from Urania import PDG
#from Urania.MassAmplitudes import *

#Eff_Curves = {}

#t,f = getTuple(MCSelTuple)
M_min = PDG.Kplus.mass+PDG.piplus.mass
M_max = 1740.
den_calc = RooKstar.BW.createCdf(RooKstar.m)
def do(cut, bins = 1000):
    h = TH1F("num","num",bins,M_min, M_max)
    f2 = TFile("/tmp/yet_more_hjunk.root","recreate")
    t2 = t.CopyTree(cut)
    for entry in t2: hnum.Fill(entry.wtf)
    x,y = [], []
    for i in range(bins):
        x0 = h.GetBinLowEdge(i+1)
        x1 = h.GetBinLowEdge(i+2)
        x.append(h.GetBinCenter(i+1))
        num = h.GetBinContent(i+1)
        RooKstar.m.setVal(x1)
        q0 = den_calc.getVal()
        q1 = RooKstar.m.setVal(x0)
        den = q1 - q0
        y.append(num*1./den)

    return NF(x,y)
