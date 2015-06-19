from Urania.MassAmplitudes import *
from scipy import random as rnd
from ROOT import *
from Urania import * ## make available the old ".tree()" method of RooDataSets
from SomeUtils.numericFunctionClass import *

AccessPackage("Bs2MuMu")
from smartpyROOT import *
recoverTree()
from OurSites import *
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/Kstar_evtgen.cxx++')
t,fp = getTuple(NTUPLE_PATH + "/MC/Bd_2012p", thing = "DecayTree")
f2 = TFile("/tmp/eraseme","recreate")

lo = PDG.Kplus.mass + PDG.piplus.mass
hi = PDG.Bs.mass - PDG.Jpsi.mass #- 0.001
Nbins = 1000
L0 = RooRealVar("L0","L0",0.)
L1 = RooRealVar("L0","L0",0.)

m0P = RooRealVar("m0P","m0P",PDG.Kst0.mass)
gamma0P = RooRealVar("gamma0P","gamma0P",PDG.Kst0.width)
P1mass = RooRealVar("P1_mass","M(K#pi) ",lo, hi,"MeV/c^{2}")

mb = RooRealVar("mb","mb",PDG.Bd.mass)
mv = RooRealVar("mv","mv",PDG.Jpsi.mass)
m_kaon = RooRealVar("m_kaon","m_kaon",PDG.Kplus.mass)
m_pion = RooRealVar("m_pion","m_pion",PDG.piplus.mass)

def_sw = FlatSwave
gen = Kstar_evtgen("Signal","Signal",P1mass,m0P,gamma0P,m_kaon,m_pion,L1,mb,mv,L0)
eu = gen.generate(RooArgSet(P1mass),1000000)



#BREAK

def evCsp(phi, sw = def_sw,pw = Kst02Kpi_EvtGen , PS = B2JpsiKpi_ps):
    """
    phi is the efficiency curve, created in  Kpi_bins_efficiency_curves.py
    sw and pw are the propagators of the two interfering waves
    PS is an overall phase space factor
    """
    pwconj = pw.conjugate()
    pwconj= pwconj.subs( mass, mass.conjugate()) ## mass is real, let's make life easier
    swconj= sw.conjugate().subs( mass, mass.conjugate()) ## mass is real, let's make life easier
    f1 = (pw*pwconj*PS).subs([(mul,lo),(muh,hi)])
    f2 = (sw*swconj*PS).subs([(mul,lo),(muh,hi)])
    f3 = (swconj*pw*PS).subs([(mul,lo),(muh,hi)])
    c = 0
    d = 0
    csp = 0
    for i in range(Nbins+1):
        mvar = lo + (hi-lo)*i*1./Nbins
        eff = phi(mvar)
        dc = re(f1.subs(mass,mvar).n())
        dd = re(f2.subs(mass,mvar).n())
        dcsp = f3.subs(mass,mvar).n()
        
        c+= dc*eff
        d+= dd*eff
        csp += dcsp*eff

    c = c.n()
    d = d.n()
    
    csp = csp*1./Sqrt(d*c)
    csp = csp.n()
    x = re(csp)
    y = im(csp)

    CSP = sqrt(x**2 + y**2)
    theta = -atan(y/x)
    if theta < 0 : theta = theta+pi
    

    return CSP, theta

class step:
    def __init__(self, m0,m1):
        self.m0 = m0
        self.m1 = m1
    def __call__(self,m):
        if m < self.m0 or m > self.m1: return 0
        else: return 1
        
def makePhi(t, x0,x1):
    #cut = "mKK > " + str(x0) + "&&" + "mKK<"+str(x1) +" && ID1 == 321 && ID2 == -321"
    s0 = str(lo)
    s1 = "1060"
    label = str(int(x0)) + str(int(x1))
    h3 = TH1F("num", "num", 200,lo,hi)
    h4 = TH1F("den", "den", 200,lo,hi)
    for entry in t:
        if abs(entry.Kplus_TRUEID) != 321: continue
        if abs(entry.piminus_TRUEID) != 211 : continue
        p1 = vector(entry.Kplus_TRUEP_X, entry.Kplus_TRUEP_Y, entry.Kplus_TRUEP_Z)
        p2 = vector(entry.piminus_TRUEP_X, entry.piminus_TRUEP_Y, entry.piminus_TRUEP_Z)
        mcm = sqrt(IM2(p1,p2, PDG.Kplus.mass, PDG.piplus.mass))
        
        #h3.Fill(mcm)
        #mKK = rnd.normal(entry.mKK,res1)
        if mcm< x0:continue
        if mcm>x1: continue
        h3.Fill(mcm)
    tgen = eu.tree()
    for entry in tgen: h4.Fill(tgen.P1_mass)
    
    h3.Divide(h4)
    x, y = [], []
    for i in range(1,h3.GetNbinsX()+1):
        x.append(h3.GetBinCenter(i))
        y.append(h3.GetBinContent(i))
    return NF(x,y)
#ph = makePhi(t,700,800)

Kpibins = [825,860,895,930,965]

phis = []
for i in range(len(Kpibins)-1):
    x0 = Kpibins[i]
    x1 = Kpibins[i+1]
    phis.append(makePhi(t,x0,x1))

for phi in phis:
    print evCsp(phi)
