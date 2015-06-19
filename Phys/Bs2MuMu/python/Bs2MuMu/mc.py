from ROOT import *
from MCLimit import *
import sys
from XTuple import *
from SomeUtils.alyabar import *
from SomeMassModels import B2JpsiModels

from SomeUtils.numericFunctionClass import *
from triggerclass import *
def getOutput(filename, keyname = "BR"):
    ch = channelData(filename, typ="ASCII")
    #ts = ch.takeKey("ts")
    #ts0 = min(ts)
    for i in range(len(ch)):
        ch[i]["evt"] = i
        ch[i]["oCLsb"] = 1-ch[i]["CLsb"]
        ch[i]["oCLs"] = 1-ch[i]["CLs"]
        #ch[i]["ets"] = (ch[i]["ts"]-ts0)
    x = ch.takeKey(keyname)
    y0 = ch.takeKey("oCLsb")
    y1 = ch.takeKey("oCLs")
    #y = ch.takeKey("ets")
    f1 = NF(x,y0)
    #f2 = NF(x,y)
    f3 = NF(x,y1)
    return f1.derivativeF(), f3.derivativeF(),ch #, f2

kPaula = TColor.GetColor("#ff99cc")
class MCObject:
    def __init__(self, name, key = "BR"):
        self.l = getOutput(name,key)
        self.Prob = self.l[0]
        self.Pmax = max(self.Prob.DataBase.values())
        #self.ts = self.l[-1]
        x =[]
        y = []
        ll = []
        for key in self.Prob.DataBase.keys():
            if self.Prob(key)<=0: continue
            x.append(key)
            ll.append(-log(self.Prob(key)/self.Pmax))
            y.append(-2*log(self.Prob(key)/self.Pmax))
        self.chi2 = NF(x,y)
        self.ll = NF(x, ll)
        
    def simplify(self,N):
        x, y = [], []
        for i in range(len(self.Prob.References)):
            x0=self.Prob.References[i]
            
            if i%N: continue
            x.append(x0)
            y.append(self.Prob(x0))
            #i+=1
        #print x, y
        self.Prob = NF(x,y)
        x2 =[]
        y2 = []
        for key in self.Prob.DataBase.keys():
            if self.Prob(key)<=0: continue
            x2.append(key)
            y2.append(-2*log(self.Prob(key)/self.Pmax))
        self.chi2 = NF(x2,y2)
        
        #return 1

#w = MCObject(os.environ["HOME"] + "/vol5/ks/Bs2012_autum_2010_atlas_cms_cdf_SYST1job_all.dat")
#wb = MCObject(os.environ["HOME"] + "/vol5/ks/BsTH_2012_autum_2010_atlas_cms_cdf_SYST1job_all.dat")
#w = MCObject(os.environ["HOME"] + "/vol5/ks/2012_autum_all.dat")
#BREAK
##w = MCObject("MC8_CL_Bsmm.dat")
#BREAK

#c## df = MCObject("CDF_all.dat")
## BREAK

## atlas = MCObject("ATLAS2012b.dat")
## #atlas.simplify(5)
## cms = MCObject("CMS2012.dat")
## #cms.simplify(5)
## #lhcbcms = MCObject("LHCbCMS.dat")

## lhcb = MCObject(os.environ["HOME"] + "/vol5/ks/2012_autum_all.dat")
## lhc = MCObject("LHC.dat")

## cms.simplify(3)
## lhcb.simplify(5)
## w.simplify(5)
## cdfg = cdf.Prob.Draw(kBlue+3)
## atlasg = atlas.Prob.Draw(kCyan)
## cmsg = cms.Prob.Draw(kRed)
## #lhcbcmsg = lhcbcms.Prob.Draw(kYellow)
## lhcbg = lhcb.Prob.Draw(kAzure-2)
## wg = w.Prob.Draw(kGreen)
## #lhcg = lhc.Prob.Draw(kViolet)

## cdfg[1].SetMaximum(0.38)
## cdfg[1].GetXaxis().SetRange(0,80)

## cdfg[1].Draw("AL")
## cmsg[1].Draw("L")
## atlasg[1].Draw("L")
## lhcbg[1].Draw("L")
## wg[1].Draw("L")
## #lhcg[1].Draw("L")
## #lhcbcmsg[1].SetLineStyle(kDashed)
## #lhcbcmsg[1].Draw("L")





## cdfg = cdf.chi2.Draw(kBlue+3)
## atlasg = atlas.chi2.Draw(kCyan)
## cmsg = cms.chi2.Draw(kRed)
## #lhcbcmsg = lhcbcms.chi2.Draw(kYellow)
## lhcbg = lhcb.chi2.Draw(kAzure-2)
## wg = w.chi2.Draw(kGreen)
## lhcg = lhc.chi2.Draw(kViolet)

## cdfg[1].SetMaximum(9)
## cdfg[1].GetXaxis().SetRange(0,16)
## cdfg[1].GetXaxis().SetTitle("BR(B_{s}#rightarrow #mu#mu)[x10^{-9}]")
## cdfg[1].GetYaxis().SetTitle("#Delta #chi^{2}")
## cdfg[1].Draw("AL")
## cmsg[1].Draw("L")
## atlasg[1].Draw("L")
## lhcbg[1].Draw("L")
## wg[1].Draw("L")
## #lhcg[1].Draw("L")
## #lhcbcmsg[1].SetLineStyle(kDashed)
## #lhcbcmsg[1].Draw("L")
o = MCObject("BsTH_2012_autum_2010_atlas_cms_cdf_SYST1job_all.dat")
def MakeKeesFile(mc,name, divide =1):
    ch = []
    xr = mc.chi2.DataBase.keys()
    xr.sort()
    for key in xr:
        if divide:ch.append({"X":key/3.54, "DeltaChi2":mc.chi2(key)})
        else: ch.append({"X":key, "DeltaChi2":mc.chi2(key)})
    ch=channelData(ch)
    ch.save(name, typ = "X")
    
                  
    

MakeKeesFile(o, "Kees_2013")

ch13 = channelData("Kees_2013.dat", typ = "ASCII")
ch12 = channelData("/afs/cern.ch/user/d/diegoms/public/for_Kees/Kees_Bsmm_HCP.dat", typ = "ASCII")
x13 = ch13.takeKey("X")
y13 = ch13.takeKey("DeltaChi2")
g13 = NF(x13,y13)
x12 = ch12.takeKey("X")
y12 = ch12.takeKey("DeltaChi2")
g12 = NF(x12,y12)

a = g13.Draw(kPaula)
b = g12.Draw(kGreen)

a[1].Draw("AL")
b[1].Draw("L")
