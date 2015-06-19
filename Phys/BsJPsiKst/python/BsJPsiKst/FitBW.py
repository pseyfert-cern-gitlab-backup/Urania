from ROOT import *
from math import *
from array import *


gROOT.ProcessLine(".x BreitWignerP.cxx++")
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/Kmatrix_nonRes.cxx++')
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/TwoBW.cxx+')
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/Kstar_evtgen.cxx++')



m = RooRealVar("m","m",0,222200)#1740)
m0 = RooRealVar("m0","m0",896.1)#-10,896.+10)
G0 = RooRealVar("G0","G0",50.5)#48.7-10,48.7+10)
r_kst = RooRealVar("r_kst","r_kst",0.003)
m_kaon = RooRealVar("m_kaon","m_kaon",493.677000)
m_pion = RooRealVar("m_pion","m_pion",139.570180)
mb = RooRealVar("mb","mb",5279.4)#-10,5279.53+10)
mv = RooRealVar("mv","mv",2*105.658367)#-10,3096.916+10)
L0 = RooRealVar("L0","L0",0.)
L1 = RooRealVar("L1","L1",1.)
cnR = RooRealVar("cPnR","cPnR",0)

beta = RooRealVar("beta","beta",0)
phase = RooRealVar("phase","phase",0)
m1P = RooRealVar("m1P","m1P",1414)#,1390,1430)
gamma1P = RooRealVar("gamma1P","gamma1P",232.)#,200,250.)




# BW = BreitWignerP("BW","BW",m,m0,G0,r_kst,m_kaon,m_pion)

#BW = Kmatrix_nonRes("BW","BW",m, m0, G0,cnR,L0,mb,mv,L1)
#BW = TwoBW("Signal", "Signaml",m , beta,phase,m0,m1P,G0,gamma1P,L1, mb,mv)
BW = Kstar_evtgen("BW","BW",m,m0,G0,m_kaon,m_pion,L1,mb,mv,L0)



f = TFile("M_Kpi_gen.root")
mkpi = f.Get("htemp")


data = RooDataHist("data","data",RooArgList(m),mkpi)

# BW.fitTo(data,RooFit.Range(700,1600))


cv = TCanvas()
fr = m.frame()
RooAbsData.plotOn(data,fr)
BW.plotOn(fr)
fr.Draw()


mp = RooRealVar("mp","mp",0,22220000)#m_kaon.getVal()+m_pion.getVal(),mb.getVal()-mv.getVal())
mp.setRange("massCut",m0.getVal()+15*G0.getVal(),mb.getVal()-mv.getVal())

# BWp = Kmatrix_nonRes("BWp","BWp",mp, m0, G0,cnR,L0,mb,mv,L1)

BWp = Kstar_evtgen("BWp","BWp",mp,m0,G0,m_kaon,m_pion,L1,mb,mv,L0)


total = BWp.createIntegral(RooArgSet(mp)).getVal()
masscut = BWp.createIntegral(RooArgSet(mp),"massCut").getVal()

otra = BWp.createIntegral(RooArgSet(mp),RooArgSet(mp),"massCut").getVal()

print "1-masscut/total = ",masscut/total
print "1-masscut/total = ",otra

