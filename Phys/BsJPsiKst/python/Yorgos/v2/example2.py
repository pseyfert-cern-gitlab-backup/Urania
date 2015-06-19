from ROOT import *
from math import *
from ROOT import *
from math import *
from Urania.Helicity import *
from sympy import lambdify
from SomeUtils.alyabar import HelicityAngles
from array import array
from Urania.MassAmplitudes import *
from sympy import re



#f_MC_data_1 = TFile("/afs/cern.ch/user/g/gchatzik/jpsikst/BsJpsipipi.root")
#f_MC_tree_1 = f_MC_data_1.Get("DecayTree")

'''
f_MC_data_1 = TFile("/afs/cern.ch/user/g/gchatzik/jpsikst/BsJpsiKK_MC_BDTG_2012_selected.root")
f_MC_tree_1 = f_MC_data_1.Get("DecayTree")

Mmin = 2*PDG.Kplus.mass
Mmax = PDG.Bs.mass - PDG.Jpsi.mass
func=lambdify(mass,f0_Syr,("numpy"))
def MW(Mpions):return 1./(Mpions**2 - pow(513,2) - 513 * 335J)

def MW1(Mkaons_):return 1./(Mkaons_**2 - pow(1019.445,2) - 1019.445 * 4.26J)
def MW2(Mkaons_):return 1./(Mkaons_**2 - pow(1525,2) - 1525 * 76J)



def norm_BW():
    Sum=0
    Nbins = 1000
    dm = (Mmax - (Mmin-600) )*1./Nbins
    for i in range(Nbins):
        m = Mmin + i*dm
        thingie = func(m + 0J)
        Number=(thingie*thingie.conjugate()).real
        Sum=Sum+Number*dm
    return Sum
B0=norm_BW()
NB_0=pow(B0,-0.5)
c0=NB_0
'''
'''
def norm_BW1():
    Sum=0
    Nbins = 1000
    dm = (Mmax - Mmin)*1./Nbins
    for i in range(Nbins):
        m = Mmin + i*dm
        thingie = MW1(m)
        Number=(thingie*thingie.conjugate()).real
        Sum=Sum+Number*dm
    return Sum
B1=norm_BW1()
NB_1=pow(B1, -0.5)
c1=NB_1
'''
'''
def norm_BW2():
    Sum=0
    Nbins = 1000
    dm = (Mmax - Mmin)*1./Nbins
    for i in range(Nbins):
        m = Mmin + i*dm
        thingie = MW2(m)
        Number=(thingie*thingie.conjugate()).real
        Sum=Sum+Number*dm
    return Sum
B2=norm_BW2()
NB_2=pow(B2, -0.5)
c2=NB_2
'''

'''
def norm_BW():
    Sum=0
    Nbins = 1000
    dm = (Mmax - Mmin)*1./Nbins
    for i in range(Nbins):
        m = Mmin + i*dm
        thingie = MW(m + 0J)
        Number=(thingie*thingie.conjugate()).real
        Sum=Sum+Number*dm
    return Sum
B3=norm_BW()
NB_3=pow(B0,-0.5)
c3=NB_3
'''



############################################################
'''
c=TGraph()
for i in range(223,1835):
    m=i + 0J
    x=i
    k=func(m)
    l=(k*c0*c0*k.conjugate()).real
    c.SetPoint(i,x,l)
c.Draw("A*")
'''
'''
p=TGraph()
for i in range(int(f_MC_tree_1.GetEntries())):
    f_MC_tree_1.GetEntry(i)
    m=f_MC_tree_1.Inv_mass + 0J
    x=f_MC_tree_1.Inv_mass
    k=func(m)
    ll=(k*c0*c0*k.conjugate()).real
    p.SetPoint(i,x,ll)
'''
'''
n=TGraph()
for i in range(int(f_MC_tree_1.GetEntries())):
    f_MC_tree_1.GetEntry(i)
    m=f_MC_tree_1.Inv_mass + 0J
    x=f_MC_tree_1.Inv_mass
    k=func(m)
    lll=(k*c0*c0*k.conjugate()).real
    n.SetPoint(i,x,lll)
n.Draw("A*")
#p.Draw("*")
#n.Draw("*")
'''

############################################################

'''
c=TGraph()
for i in range(500,1500):
    m=i
    x=i
    k=MW1(m)
    l=(k*k.conjugate()).real
    c.SetPoint(i,x,l)

p=TGraph()
for i in range(int(f_MC_tree_1.GetEntries())):
    f_MC_tree_1.GetEntry(i)
    m=f_MC_tree_1.Mkaons_
    x=f_MC_tree_1.Mkaons_
    k=MW1(m)
    ll=(k*k.conjugate()).real
    p.SetPoint(i,x,ll)
'''



'''
##############################################################
c=TGraph()
for i in range(500,int(Mmax)):
    m=i
    x=i
    k=MW2(m)
    l=(k*k.conjugate()).real
    c.SetPoint(i,x,l)

p=TGraph()
for i in range(int(f_MC_tree_1.GetEntries())):
    f_MC_tree_1.GetEntry(i)
    m=f_MC_tree_1.Inv_mass
    x=f_MC_tree_1.Inv_mass
    k=MW2(m)
    ll=(k*k.conjugate()).real
    p.SetPoint(i,x,ll)

n=TGraph()
for i in range(int(f_MC_tree_1.GetEntries())):
    f_MC_tree_1.GetEntry(i)
    m=f_MC_tree_1.Inv_mass
    x=f_MC_tree_1.Inv_mass
    k=MW2(m)
    lll=(k*c0*c0*k.conjugate()).real
    n.SetPoint(i,x,lll)
#c.Draw("A*")
#p.Draw("A*")
n.Draw("A*")
###########################################################

'''

'''
n=TGraph()
Sum=0
for i in range(int(f_MC_tree_1.GetEntries())):
    f_MC_tree_1.GetEntry(i)
    m=f_MC_tree_1.Inv_mass
    x=f_MC_tree_1.Inv_mass
    k=MW(m)
    lll=(k*c3*c3*k.conjugate()).real
    Sum=lll+Sum
    n.SetPoint(i,x,lll)
    print Sum
#c.Draw("A*")
#p.Draw("A*")
n.Draw("A*")
'''

ch=TChain("DecayTree")
ch.Add("BdJpsipipi.root")
ch.Add("BsJpsiKK_MC_BDTG_2012_selected.root")
ch.Add("BsJpsipipi.root")
ch.Merge("3_decay_modes_v2.root")

'''
ch=TChain("DecayTree")
ch.Add("BdJpsipipi.root")
ch.Add("BsJpsipipi.root")
ch.Merge("2_decay_modes_pipi_v2.root")
'''
