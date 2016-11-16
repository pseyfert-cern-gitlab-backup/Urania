from ROOT import *
import cPickle
from fiducial import *

BDTNAME = "BDTDTOSB"
trig = tis
epsTOS = cPickle.load(file("eps_TOS"))
epsTIS = cPickle.load(file("eps_TIS"))
eps_old = cPickle.load(file("eff_BDT_old"))

#eps = eps_old#TIS
eps =epsTIS
f = TFile("PiPi_B_unblind.root")
t = f.Get("T")
if "TOS" in BDTNAME:
    fiducial = fiducialtos
    trig ="(1>0)"# xtos
    eps = epsTOS
    f = TFile("minbias.root")
    t = f.Get("T")
fiducial += aa + mW
#f = TFile("ks2pipi1fbA_TIS.root")

l = []
for i in range(10):
    l.append(t.GetEntries(fiducial + aa + trig +aa + BDTNAME +">"+str(eps(1-.1*i)) + aa + BDTNAME + "<" + str(eps(.9-.1*i))))

