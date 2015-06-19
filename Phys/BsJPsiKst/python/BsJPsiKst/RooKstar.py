from ROOT import *
from Urania import PDG
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/Kstar_evtgen.cxx++')

my_mom = PDG.Bs

m = RooRealVar("m","m",PDG.Kplus.mass+PDG.piplus.mass,my_mom.mass-PDG.Jpsi.mass)#1740)
m0 = RooRealVar("m0","m0",896.1)#-10,896.+10)
G0 = RooRealVar("G0","G0",50.5)#48.7-10,48.7+10)
r_kst = RooRealVar("r_kst","r_kst",0.003)
m_kaon = RooRealVar("m_kaon","m_kaon",PDG.Kplus.mass)
m_pion = RooRealVar("m_pion","m_pion",PDG.piplus.mass)
mb = RooRealVar("mb","mb",my_mom.mass)#-10,5279.53+10)
mv = RooRealVar("mv","mv",PDG.Jpsi.mass)#-10,3096.916+10)
L0 = RooRealVar("L0","L0",0.)
L1 = RooRealVar("L1","L1",1.)
cnR = RooRealVar("cPnR","cPnR",0)

BW = Kstar_evtgen("BW","BW",m,m0,G0,m_kaon,m_pion,L1,mb,mv,L0)

