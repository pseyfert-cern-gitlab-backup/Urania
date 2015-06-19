from ROOT import *
from Cuts2013 import cuts12noKpi as cuts12
from parameters import KpiBins4 as Kpibins
BIN = 3
Mmax = Kpibins[BIN+1] 
Mmin = Kpibins[BIN] 

m_0 =5368-40
m_1 = 5368+40

#f = TFile("~/NTuplesFast/MassStudy/BdJpsiKstMC2012_BDTG_selected.root")
f = TFile("~/w7folder/NTuples/Bs_Jpsi_Kst_2013/MC/2012-4000GeV-MagUpAndDown-Nu2.5-Pythia8_Sim08a_Digi13_Trig0x409f0045_Reco14a_s20_dv33r4_WideLine_BDTG_wCosines.root")
t = f.Get("DecayTree")
mvar = "B0_MM"
f2 = TFile("/tmp/eraseme","recreate")
#t2 = t.CopyTree("isMCT && !mc_Nphotons && (mc_kaon_edvz < 3000 || mc_kaon_edvz>7500) && (mc_pion_edvz < 3000 || mc_pion_edvz>7500)")
#t2 = t.CopyTree("isMCT && !mc_Nphotons && (mc_kaon_edvz>7500) && ( mc_pion_edvz>7500)")
t2 = t.CopyTree("abs(B0_TRUEID) == 511 && Kst_892_0_MM >" +str(Mmin) + "&& Kst_892_0_MM< " +str(Mmax)+ "&& " + cuts12 )# && !mc_Nphotons && mc_kaon_edvz > 10000 && mc_pion_edvz> 10000")
gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx+")

mass = RooRealVar(mvar,mvar,5150, 5650.)
# IPATIA
a2 = RooRealVar("a2","a2",3,1,200)
a = RooRealVar("a","a" , 3,1,200)
n = RooRealVar("n","n",1.,0.8,10)
n2 = RooRealVar("n2","n2",1.,0.8,60)

ipa_s = RooRealVar("ipa_s","ipa_s", 3, 12) #1,40
ipa_m = RooRealVar("ipa_m","ipa_m",5270,5290)
beta = RooRealVar("beta","beta",0)
zeta = RooRealVar("zeta","zeta",1e-04)#1e-03, 0,1)
#zeta = RooRealVar("zeta","zeta",sqrt(3.60634e-04*0.023006975056415125))#0,1
l = RooRealVar("l","l",-6, -.1)
#l = RooRealVar("l","l",-2.64332e-01)

ipatia = RooIpatia2("bullshit_miriam","bullshit_miriam",mass,l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)


sigma0= RooRealVar("sigma0","sigma0", 3.5)
mean0= RooRealVar("mean0","mean0",0)
res0 = RooGaussian("reso0","reso0",mass,mean0,sigma0)
ipa2 = RooFFTConvPdf("ipa2","ipa2",mass, ipatia,res0,1)

data = RooDataSet("data","data", t2, RooArgSet(mass))

hm = TH1F("a"+mass.GetName(),"a"+mass.GetName(),200, mass.getMin(),mass.getMax())
for i in range(t2.GetEntries()):
    t2.GetEntry(i)
    mval = getattr(t2,mass.GetName())
    hm.Fill( mval )

h2m = RooDataHist(mass.GetName(),mass.GetName(),RooArgList(mass), hm)
ipatia.fitTo(h2m,RooFit.Minos(0), RooFit.Offset(kTRUE)) #2
fr = mass.frame()
h2m.plotOn(fr)
ipatia.plotOn(fr)
fr.Draw()
prlist = [a,a2,n,n2,l]
out = {}
for thing in prlist:
    out[thing.GetName()] = thing.getVal()
print out
BREAK
def getPrediction():
    cdf = ipatia.createCdf(RooArgSet(mass))
    mass.setVal(m_0)
    I0 = cdf.getVal()
    mass.setVal(m_1)
    I1 = cdf.getVal()
    I =  I1 - I0
    i_s0 = ipa_s.getVal()
    ipa_s.setVal(i_s0+ ipa_s.getError())
    mass.setVal(m_0)
    I0 = cdf.getVal()
    mass.setVal(m_1)
    I1 = cdf.getVal()
    sI1 =  abs( (I1 - I0) - I)
    ipa_s.setVal(i_s0)
    l_0 = l.getVal()
    l.setVal(l_0- l.getError())
    mass.setVal(m_0)
    I0 = cdf.getVal()
    mass.setVal(m_1)
    I1 = cdf.getVal()
    sI2 =  abs( (I1 - I0) - I)
    l.setVal(l_0)
    sI = sqrt(sI1**2 + sI2**2)
    
    return I, sI
ipa_P = getPrediction()

ipa2.fitTo(h2m,RooFit.Minos(0), RooFit.Offset(kTRUE)) #2
ipa2.plotOn(fr, RooFit.LineColor(kMagenta))
fr.Draw()
#BREAK


def getPredictionYpsilon():
    cdf = ipa2.createCdf(RooArgSet(mass))
    mass.setVal(m_0)
    I0 = cdf.getVal()
    mass.setVal(m_1)
    I1 = cdf.getVal()
    I =  I1 - I0
    i_s0 = ipa_s.getVal()
    ipa_s.setVal(i_s0+ ipa_s.getError())
    mass.setVal(m_0)
    I0 = cdf.getVal()
    mass.setVal(m_1)
    I1 = cdf.getVal()
    sI1 =  abs( (I1 - I0) - I)
    ipa_s.setVal(i_s0)
    l_0 = l.getVal()
    l.setVal(l_0- l.getError())
    mass.setVal(m_0)
    I0 = cdf.getVal()
    mass.setVal(m_1)
    I1 = cdf.getVal()
    sI2 =  abs( (I1 - I0) - I)
    l.setVal(l_0)
    sI = sqrt(sI1**2 + sI2**2)
    
    print I, sI

print ipa_P
getPredictionYpsilon()
from SomeUtils.alyabar import nonIndepErrors
print nonIndepErrors(t2.GetEntries("B0_MM > "+str(m_0) + " && B0_MM < "+str(m_1)), t2.GetEntries("B0_MM > "+str(mass.getMin()) + " && B0_MM < "+str(mass.getMax())))

#(0.005477163015224657, 0.0002514154993267586)
#(0.003240550409905444, 0.00019762713080260572)
