from ROOT import *
from array import array as afC
from SomeUtils.alyabar import *
from fiducial import *
import histoTex as M
import cPickle
from SomeUtils.numericFunctionClass import *
eps = cPickle.load(file("eps_TIS"))
#f = TFile("KsMuMu_MC)
fa = TFile("PiPi_A_unblind.root")
fb = TFile("PiPi_B_unblind.root")
ta = fa.Get("T")
tb = fb.Get("T")

#mw = "&& Bmass>485 && Bmass<510"
#mw = "&& Bmass>490 && Bmass<506"
mw = "&& Bmass>492 && Bmass<504"

h = TH1F("A","A", 10,0,1)
h2 = TH1F("A","A", 10,0,1)

h3 = TH1F("A","A", 100,0,4000)
h4 = TH1F("A","A", 100,0,4000)

y = eps.DataBase.keys()
x = eps.DataBase.values()

epsInv = NF(x,y)


#def findBin(bdt):
f2 = TFile("/tmp/eraseme.root", "recreate")
t2 = ta.CopyTree(fiducial + mw+"&& L0Tis && Hlt1Tis && Hlt2Tis && BDTDA > 0.2")

for entry in t2:
    bdt = 1-epsInv(entry.BDTDA)
    h.Fill(bdt)
    Blife_ps_r = entry.Blife_ps_r
    h2.Fill(bdt, exp(-Blife_ps_r/51160) /exp(-Blife_ps_r/89.5))
    h3.Fill(entry.Bpt)
    h4.Fill(entry.Bpt, exp(-Blife_ps_r/51160) /exp(-Blife_ps_r/89.5))
h.SetLineColor(kRed)
h2.SetLineColor(kBlue)
h3.SetLineColor(kRed)
h4.SetLineColor(kBlue)
c = TCanvas()
c.Divide(2,1)
c.cd(1)
h.Draw()
h2.Draw("same")
c.cd(2)
h3.Draw()
h4.Draw("same")
BREAK

for i in range (10):
    print  i+1, "&",  ta.GetEntries(fiducial + mw+"&& L0Tis && Hlt1Tis && Hlt2Tis && BDTDA>"+str(eps(1-0.1*i))+" && BDTDA < " +str(eps(0.9-0.1*i))), "\\\\"
    h.SetBinContent(i+1,ta.GetEntries(fiducial + mw+"&& L0Tis && Hlt1Tis && Hlt2Tis && BDTDA>"+str(eps(1-0.1*i))+" && BDTDA < " +str(eps(0.9-0.1*i))))
    

BREAK                   
for i in range (10):
    print  i+1, "&",  tb.GetEntries(fiducial + mw+"&& L0Tis && Hlt1Tis && Hlt2Tis && BDTDB>"+str(eps(1-0.1*i))+" && BDTDB < " +str(eps(0.9-0.1*i))), "\\\\"
