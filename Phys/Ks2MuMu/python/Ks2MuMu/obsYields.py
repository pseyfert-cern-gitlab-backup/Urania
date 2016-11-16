from ROOT import *
import cPickle
from fiducial import *

BDTNAME = "BDTDTOSA"
trig = tis
epsTOS = cPickle.load(file("eps_TOS"))
epsTIS = cPickle.load(file("eps_TIS"))
eps_old = cPickle.load(file("eff_BDT_old"))

#eps = eps_old#TIS
eps =epsTIS
f = TFile("MM_A_unblind.root")
t = f.Get("T")
if "TOS" in BDTNAME:
    fiducial = fiducialtos
    trig = xtos
    eps = epsTOS
    #f = TFile("minbias.root")
    #t = f.Get("T")
fiducial += aa + mW
#f = TFile("ks2pipi1fbA_TIS.root")

l = []
for i in range(10):
    l.append(t.GetEntries(fiducial + aa + trig +aa + dll+ aa +  BDTNAME +">"+str(eps(1-.1*i)) + aa + BDTNAME + "<" + str(eps(.9-.1*i))))




TISA =[0L, 3L, 1L, 0L, 1L, 0L, 0L, 1L, 0L, 0L]
TOSA =[1L, 2L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 1L]
TISB = [2L, 3L, 3L, 1L, 0L, 0L, 0L, 0L, 0L, 0L]
TOSB = [4L, 2L, 1L, 1L, 0L, 2L, 0L, 0L, 0L, 0L]
