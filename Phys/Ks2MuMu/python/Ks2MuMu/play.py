from ROOT import *

fp = TFile("~/vol5/ks/kspipi1fbB.root")
tp = fp.Get("T")

fm = TFile("~/vol5/ks/ksmumu1fbB.root")
tm = fm.Get("T")
armenteros = "(((4*AP_pt^2/1115.683^2 + (AP_alpha-0.69169)^2) > 4.7*100.7^2/(1115.683^2) || (4*AP_pt^2/1115.683^2 + (AP_alpha-0.69169)^2) < 3.5*100.7^2/(1115.683^2)) && ((4*AP_pt^2/1115.683^2 + (AP_alpha+0.69169)^2) > 4.7*100.7^2/(1115.683^2) || (4*AP_pt^2/1115.683^2 + (AP_alpha+0.69169)^2) < 3.5*100.7^2/(1115.683^2)))"
fiducial = "Blife_ps_r <130 && mu1ptot < 1e05 && mu2ptot < 1e05 && Vchi2 < 25 &&" + armenteros

massW = "abs(Bmass-497.614)<15"
BREAK
#tm.Draw("BDTDA","("+fiducial + " && Bmass>500)*209812/57054")
#tp.Draw("BDTDA",fiducial + "&&" + massW, "same")

g = TGraph()

Mi = 1./tp.GetEntries(fiducial + "&& L0Tis && Hlt1Tis && Hlt2Tis && BDTDB>0.2" + massW)
x0, y0 = [], []

for i in range(100):
    x = 0.2 + 0.01*i
    y =  tp.GetEntries(fiducial + "&& L0Tis && Hlt1Tis && Hlt2Tis && BDTDB>"+str(x) + "&&" + massW)*Mi
    x0.append(x)
    y0.append(y)
    g.SetPoint(i,x,y)
from SomeUtils.numericFunctionClass import *

eps = NF(y0,x0)
