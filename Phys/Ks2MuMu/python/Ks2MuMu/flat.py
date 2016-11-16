from ROOT import *
from fiducial import *
from SomeUtils.numericFunctionClass import *
#from SomeUtils.numericFunctionClass import *
fmm = TFile("~/vol5/ks/ksmumu1fbB_TOS.root")
tm = fmm.Get("T")
fp = TFile("~/vol5/ks/ks2pipi1fbB_TOS.root")
tp = fp.Get("T")
fx = TFile("ww","recreate")
tx = tm.CopyTree(fiducial + aa + "Bmass<500 && L0Tos && Hlt1Tos && Hlt2Tos && Bmass<1000 && BDTDTOSB>0.2 && " + traintos)
CU = 0.2
x, y = [], []
for entry in tx:
    #if entry.BDTDTOSB <CU:continue
    y.append(entry.BDTDTOSB)

y.sort()

for i in range(len(y)):
    #if i %10: continue
    eff = 1 - i*1./len(y)
    x.append(eff)

eps = NF(x,y)

import cPickle
cPickle.dump(eps, file("eps_TOS","w"))
