from ROOT import *
from math import *
from scipy import random as rnd

import os
os.sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu/")
from RTuple import *

from penguin_inputs import *
Gamma = gamma
su3 = 1
GR = 3.61e-02
Kstpol_f = [0.484, 0.181, 1- .484-.181]
Phipol_f =  [0.5241, 1- 0.5241-.2504 , 0.2504]
def Hf_exp(eps, su3, GR, i):
    return 1/eps*su3*GR*Kstpol_f[i]/Phipol_f[i]

Hf_e_0 = Hf_exp(eps, su3, GR,0)
Hf_e_pa = Hf_exp(eps, su3, GR,1)
Hf_e_pe = Hf_exp(eps, su3, GR,2)
priors = {"P": "PolarPrior", "C": "CartesianPrior"}
colors = {"P": kBlue, "C":kRed}

def TH(eps, af, thf, Gamma):
    ct = cos(thf)
    st = sin(thf)
    sg = sin(Gamma)
    cg = cos(Gamma)
    Hf = (1 - 2*af*ct*cg + af*af)*1./(1+2*eps*af*ct*cg+eps*eps*af*af)
    Af = (2*af*st*sg)*1./(1-2*af*ct*cg+af*af)
    tg = (2*eps*af*ct*sg+eps*eps*af*af*sin(2*Gamma))*1./(1+2*eps*af*ct*cg+eps*eps*af*af*cos(2*Gamma))
    
    return Hf,Af, tg




def maketup_Polar(N=10000000):
    tup = RTuple("./Faller_PolarPrior",["tg/F","Af/F","Hf/F", "Hf_exp_0/F", "Hf_exp_pa/F","Hf_exp_pe/F","af/F","thf/F"])
    
    for i in range(10000000):
        af = 2*rnd.random()
        thf = 2*pi*rnd.random()

        Hf, Af, tg = TH(eps,af,thf,Gamma)
        tup.fillItem("Hf_exp_0", Hf_e_0)
        tup.fillItem("Hf_exp_pa", Hf_e_pa)
        tup.fillItem("Hf_exp_pe", Hf_e_pe)
        tup.fillItem("af",af)
        tup.fillItem("thf",thf)
        tup.fillItem("Hf",Hf)
        tup.fillItem("Af",Af)
        tup.fillItem("tg", tg)
    
        tup.fill()

    tup.close()
def maketup_Cartesian(N=10000000):
    tup = RTuple("./Faller_CartesianPrior",["tg/F","Af/F","Hf/F", "Hf_exp_0/F", "Hf_exp_pa/F","Hf_exp_pe/F","af/F","thf/F"])
   
    for i in range(10000000):
        re_af = -1 + 2*rnd.random()
        im_af = -1 + 2*rnd.random()
        af = sqrt(re_af**2 + im_af**2)
        thf = atan(im_af/re_af)
        if im_af <0 and re_af > 0: thf +=2*pi
        if re_af < 0: thf += pi
        
        
        Hf, Af, tg = TH(eps,af,thf,Gamma)
        tup.fillItem("Hf_exp_0", Hf_e_0)
        tup.fillItem("Hf_exp_pa", Hf_e_pa)
        tup.fillItem("Hf_exp_pe", Hf_e_pe)
        tup.fillItem("af",af)
        tup.fillItem("thf",thf)
        tup.fillItem("Hf",Hf)
        tup.fillItem("Af",Af)
        tup.fillItem("tg", tg)
    
        tup.fill()

    tup.close()
def make_phis_h(Hf,sHf, Af, sAf, opt = "P"):
   
    h1 = TH1F("prior","prior",100, -0.2,0.2)
    h2 = TH1F("posterior","posterior",100, -0.2,0.2)
    h3 = TH1F("ratio","ratio",100, -0.2,0.2)
    f = TFile("Faller_" + priors[opt]+".root")
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
        
def cook2DLL(h):
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
                   
def make2DLL(Hf,sHf, Af, sAf, opt = "P"):
    
    hs = make_phis_h(Hf,sHf, Af, sAf, opt )
    g = cook2DLL(hs[0])
    g.SetLineColor(colors[opt])
    return g
