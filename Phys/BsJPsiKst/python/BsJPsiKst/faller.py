from ROOT import *
from math import *
from scipy import random as rnd

import os
os.sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu/")
from RTuple import *

Vus = 0.2252
sVus = 0.0009

Gamma = 65*pi/180

Vus2 = Vus*Vus
eps = Vus2/(1-Vus2)

su3 = 1
GR = 4.4e-05/0.9e-03

def Hf_exp(eps, su3, GR):
    return 1/eps*su3*GR

def TH(eps, af, thf, Gamma):
    ct = cos(thf)
    st = sin(thf)
    sg = sin(Gamma)
    cg = cos(Gamma)
    Hf = (1 - 2*af*ct*cg + af*af)*1./(1+eps*af*ct*cg+eps*eps*af*af)
    Af = (2*af*st*sg)*1./(1-2*af*ct*cg+af*af)
    tg = (2*eps*af*ct*sg+eps*eps*af*af*sin(2*Gamma))*1./(1+2*eps*af*ct*cg+eps*eps*af*af*cos(2*Gamma))
    
    return Hf,Af, tg




def maketup():
    tup = RTuple("Faller",["tg/F","Af/F","Hf/F", "Hf_exp/F", "af/F","thf/F"])
    Hf_e = Hf_exp(eps, su3, GR)
    for i in range(1000000):
        af = 2*rnd.random()
        thf = 2*pi*rnd.random()

        Hf, Af, tg = TH(eps,af,thf,Gamma)
        tup.fillItem("Hf_exp", Hf_e)
        tup.fillItem("af",af)
        tup.fillItem("thf",thf)
        tup.fillItem("Hf",Hf)
        tup.fillItem("Af",Af)
        tup.fillItem("tg", tg)
    
        tup.fill()

    tup.close()
    
def make_phis_h(Hf,sHf, Af, sAf):
    h1 = TH1F("prior","prior",100, -0.2,0.2)
    h2 = TH1F("posterior","posterior",100, -0.2,0.2)
    h3 = TH1F("ratio","ratio",100, -0.2,0.2)
    f = TFile("Faller.root")
    t = f.Get("T")
    
    for entry in t:
        delta = atan(t.tg)
        wH = exp( - 0.5 *( (t.Hf - Hf )/sHf)**2)
        wA = exp( - 0.5 *( (t.Af - Af )/sAf)**2)
        h1.Fill(delta)
        h2.Fill(delta,wH*wA )
        h3.Fill(delta,wH*wA )
    f.Close()
    h3.Divide(h1)
    return h3, h2, h1
        
def makeLL(h):
    g = TGraph()
    j = 0
    l = []
    for i in range(h.GetNbinsX()): l.append(h.GetBinContent(i+1))
    l.sort()
    l.reverse()
    y0 = l[0]
    for i in range(h.GetNbinsX()):
        x = h.GetBinCenter(i+1)
        y = h.GetBinContent(i+1)
        if y == 0: continue
       
        g.SetPoint(j, x, -2*log(y/y0))
        j+= 1
    g.GetXaxis().SetTitle("#Delta #phi_{s} (rad)")
    g.GetYaxis().SetTitle("-2#timesDLL")
    g.SetLineColor(kRed)
    g.SetLineWidth(3)
    
    return g
                   
