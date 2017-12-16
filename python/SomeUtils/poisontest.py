from alyabar import *

from scipy import random as rnd
from ROOT import *

pfunc = "BG"

if pfunc == "95":
    def poissonE(x):
        a,b = poissonErrors95(x)
        return a/1.96, b/1.96
elif pfunc == "50":
    def poissonE(x):
        a,b = poissonErrors50(x)
        return a/.6745, b/.6745
elif pfunc == "BG":
    def poissonE(x): return fuckingErrors(x)
elif pfunc == "BGX":
    def poissonE(x):
        a, b= fuckingErrors(x)
        return a, a
else:
    def poissonE(x): return poissonErrors(x)


def poisontest(n, N, sc = 0):
    gh = TH1F("G","G",N+1, -0.5, N+0.5)
    gh2 = TH1F("G2","G2",N+1, -0.5, N+0.5)
    gh3 = TH1F("G3","G3",N+1, -0.5, N+0.5)
    fucker = TH1F("F","F",N+1, -0.5, N+0.5)
    
    ph = TH1F("P","P",N+1, -0.5, N+0.5)
    mp = n + 0.5
    for i in range(10000):
        x = ph.Fill(rnd.poisson(mp))
    su, sl = poissonErrors(n)
    su2, sl2 = poissonErrors95(n)
    su3, sl3 = poissonErrors50(n)
    su4, sl4 = fuckingErrors(n)
    for i in range(10000):
        x0 = rnd.random()
        if x0 <0.5: x = gh.Fill(n+ rnd.normal(0,su))
        else: x = gh.Fill(n- rnd.normal(0,sl))
    for i in range(10000):
        x0 = rnd.random()
        if x0 <0.5: x = gh2.Fill(n+ rnd.normal(0,su2/1.96))
        else: x = gh2.Fill(n- rnd.normal(0,sl2/1.96))
    for i in range(10000):
        x0 = rnd.random()
        if x0 <0.5: x = gh3.Fill(n+ rnd.normal(0,su3/0.6745))
        else: x = gh3.Fill(n- rnd.normal(0,sl3/0.6745))
    for i in range(10000):
        x0 = rnd.random()
        if x0 <0.5: x = fucker.Fill(n+ rnd.normal(0,su4))
        else: x = fucker.Fill(n- rnd.normal(0,sl4))
    gh.SetLineColor(kRed)
    gh2.SetLineColor(kGreen)
    gh3.SetLineColor(kMagenta)
    fucker.SetLineColor(kBlack)
    ph.SetLineWidth(4)
    fucker.SetLineWidth(4)
    
    c = TCanvas()
    if not sc:
        gh.Draw()
        ph.Draw("same")
        gh2.Draw("same")
        gh3.Draw("same")
        fucker.Draw("same")
    else:
        gh.DrawNormalized()
        ph.DrawNormalized("same")
        gh2.DrawNormalized("same")
        gh3.DrawNormalized("same")
        fucker.DrawNormalized("same")
        
    return c, gh, ph, gh2, gh3, fucker



def makepoisson(mean, N):
    ph = TH1F("G","G",N+1, -0.5, int(N))
    for i in range(100000):
        x = ph.Fill(rnd.poisson(mean))
    return ph
def getMPV(h):
    y0 = -1
    for i in range(h.GetNbinsX()):
        if h.GetBinContent(i+1) > y0:
            y0 =  h.GetBinContent(i+1)
            x0 =  h.GetBinCenter(i+1)
    return x0
def makeJunk(mpv, sp, sn, N):
   
    f1 = sp*1./mpv
    f2 = 0
    if sn!=0 :f2 = sn*1./mpv
    #print f1, f2, mpv
    ph = TH1F("G","G",N+1, -0.5, N+0.5)
    for i in range(100000):
        sk = rnd.normal()
        x = ph.Fill(mpv*(1+ sk*0.5*(f1-f2) + sk*sk*0.5*(f1+f2) ))
    return ph


def poisontest2(n, N, sc = 0):
    gh = TH1F("G","G",N+1, -0.5, N+0.5)
    gh2 = TH1F("G2","G2",N+1, -0.5, N+0.5)
    gh3 = TH1F("G3","G3",N+1, -0.5, N+0.5)
    fucker = TH1F("F","F",N+1, -0.5, N+0.5)
    
    ph = TH1F("P","P",N+1, -0.5, N+0.5)
    mp = n + 0.5
    for i in range(10000):
        x = ph.Fill(rnd.poisson(mp))
    su, sl = poissonErrors(n)
    su2, sl2 = poissonErrors95(n)
    su2, sl2 = su2/1.96, sl2/1.96
    su3, sl3 = poissonErrors50(n)
    su3,sl3 = su3/.6745, sl3/.6745
    su4, sl4 = fuckingErrors(n)
    gh = makeJunk(n, su,-sl,N)#, N+0.5)
    gh2 = makeJunk(n, su2,-sl2,N)#, N+0.5)
    gh3 = makeJunk(n, su3,-sl3,N)#, N+0.5)
    fucker = makeJunk(n, su4,-sl4,N)#, N+0.5)
    
    
    gh.SetLineColor(kRed)
    gh2.SetLineColor(kGreen)
    gh3.SetLineColor(kMagenta)
    fucker.SetLineColor(kBlack)
    ph.SetLineWidth(4)
    fucker.SetLineWidth(4)
    
    c = TCanvas()
    if not sc:
        gh.Draw()
        ph.Draw("same")
        gh2.Draw("same")
        gh3.Draw("same")
        fucker.Draw("same")
    else:
        gh.DrawNormalized()
        ph.DrawNormalized("same")
        gh2.DrawNormalized("same")
        gh3.DrawNormalized("same")
        fucker.DrawNormalized("same")
        
    return c, gh, ph, gh2, gh3, fucker
def poissonMPV():
    h = {}
    y = {}
    g = TGraph()
    for i in range(10):
        x = i + 0.5
        h[x] = makepoisson(x)
        y[x] = getMPV(h[x])
        g.SetPoint(i, y[x], x-y[x])
    return h, y, g

def do_nos(mpv):

    h5 = makepoisson(mpv + 0.5,int(round(mpv + 10*sqrt(mpv))))


    x = RooRealVar("P","P",-0.5,60)
    h = RooDataHist("data","data", RooArgList(x), h5)
    mean = RooRealVar("m","m",mpv)#+0.2, mpv-1, mpv + 1)
    s1 = RooRealVar("s1","s1",sqrt(mpv),0.1,70)
    s2 = RooRealVar("s2","s2",-1.*sqrt(mpv),-70,-0.1)
    #s1b = RooRealVar("s1b","s1b",sqrt(mpv),0.1,70)
    #s2b = RooRealVar("s2b","s2b",-1.*sqrt(mpv),-70,-0.1)
    model = RooGenericPdf("Gb","exp( -0.5 * (1/(2*(s1/m+s2/m)) *((s2/m-s1/m) + sqrt((s2/m-s1/m)^2 -8*(s1/m+s2/m)*(1-P/m)  ) ))^2)",RooArgList(x,mean,s1,s2))
    model2 = RooBifurGauss("Gb","A Bifurcated Gaussian Distribution",x,mean,s1b,s2b)
    model.fitTo(h,RooFit.Minos(kTRUE))
    #model2.fitTo(h,RooFit.Minos(kTRUE))

    return abs(s1.getVal()), abs(s2.getVal())

a, b = {}, {}
for i in range(1,20):
    a[i], b[i] = do_nos(i)

mpv = 1
h5 = makepoisson(mpv + 0.5,int(round(mpv + 10*sqrt(mpv))))
x = RooRealVar("P","P",-0.5,60)
h = RooDataHist("data","data", RooArgList(x), h5)
mean = RooRealVar("m","m",mpv)#+0.2, mpv-1, mpv + 1)
s1 = RooRealVar("s1","s1",sqrt(mpv),0.1,70)
s2 = RooRealVar("s2","s2",-1.*sqrt(mpv),-70,-0.1)
#s1b = RooRealVar("s1b","s1b",sqrt(mpv),0.1,70)
#s2b = RooRealVar("s2b","s2b",-1.*sqrt(mpv),-70,-0.1)
model = RooGenericPdf("Gb","exp( -0.5 * (1/(2*(s1/m+s2/m)) *((s2/m-s1/m) + sqrt((s2/m-s1/m)^2 -8*(s1/m+s2/m)*(1-P/m)  ) ))^2)",RooArgList(x,mean,s1,s2))
model2 = RooBifurGauss("Gb","A Bifurcated Gaussian Distribution",x,mean,s1b,s2b)
model.fitTo(h,RooFit.Minos(kTRUE))
fr = x.frame()
h.plotOn(fr)
model.plotOn(fr)
#model2.plotOn(fr,RooFit.LineColor(kRed))
fr.Draw()
## f = TFile("~/vol5/limitResults.root")
## t = f.Get("TParam")
## t.Draw("SbGL8>>h5")
## mathieu = TH1F("mathieu","mathieu",40+1, -0.5, 40+0.5)
## for i in range(t.GetEntries()):
##     t.GetEntry(i)
##     mathieu.Fill(t.SbGL8)
