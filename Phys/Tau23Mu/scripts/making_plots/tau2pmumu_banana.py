#!/usr/bin/env python
import re, sys
if len(sys.argv) < 2:
  print "Usage:"
  print "python -i " + sys.argv[0] + " <filename>"
  print "where filename is the (relative or absolute) path to the .dat file"
  print "produced by the limit calculation scripts in Phys/Tau23Mu/math."
  print "Example:"
  print "   python -i "+sys.argv[0] + " ../../math/Tau2PMuMuOS_unblinded_withSystematics.dat"
  print ""
  print "NB: * if the filename contains \"OS\" it assumes the OS mode,"
  print "      otherwise the SS mode is assumed"
  print "    * the ROOT label #mp only exists from Erasmus v7r0p1 onwards"
  sys.exit()

from ROOT import *
import os
os.sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu/")
from SomeUtils.numericFunctionClass import *
#from dev_channelclass import *
from triggerclass import *


if re.match(".*OS.*",sys.argv[1]):
   mode = "OS"
else:
   mode = "SS"

def getOutput(filename):
    ch = channelData(filename, typ="ASCII")
    #ts = ch.takeKey("ts")
    #ts0 = min(ts)
    for i in range(len(ch)):
        ch[i]["evt"] = i
        ch[i]["oCLsb"] = 1-ch[i]["clsb"]
        ch[i]["oCLs"] = 1-ch[i]["cls"]
        #ch[i]["ets"] = exp(-(ch[i]["ts"]-ts0))
    x = ch.takeKey("br")
    y0 = ch.takeKey("oCLsb")
    y1 = ch.takeKey("oCLs")
    #y = ch.takeKey("ets")
    f1 = NF(x,y0)
    #f2 = NF(x,y)
    f3 = NF(x,y1)
    return f1.derivativeF(), f3.derivativeF(),ch


def prepare_banana(f):
    w = getOutput(f)
    ch = w[-1]
    g0,g1 = TGraph(), TGraph()
    banana1,banana2 = TGraph(),TGraph()
    N = len(ch)
    i = 0
    for entry in ch:
        g0.SetPoint(i,1e8*entry["br"], entry["CLs_exp_b_med"])
        g1.SetPoint(i,1e8*entry["br"], entry["cls"])
        
        banana1.SetPoint(i,1e8*entry["br"], entry["CLs_exp_b_p1"])
        banana1.SetPoint(2*N-i-1,1e8*entry["br"], entry["CLs_exp_b_m1"])
        banana2.SetPoint(i,1e8*entry["br"], entry["CLs_exp_b_p2"])
        banana2.SetPoint(2*N-i-1,1e8*entry["br"], entry["CLs_exp_b_m2"])
        i +=1
    banana2.SetFillColor(kGreen)
    if "OS" == mode:
       banana2.GetXaxis().SetTitle("BR(#tau^{#font[122]{-}}#rightarrow #bar{#font[12]{p}} #mu^{#font[122]{+}} #mu^{#font[122]{-}}) [#times 10^{-8}]")
    else:
       banana2.GetXaxis().SetTitle("BR(#tau^{#font[122]{-}}#rightarrow #font[12]{p} #mu^{#font[122]{-}} #mu^{#font[122]{-}}) [#times 10^{-8}]")
    banana2.GetYaxis().SetTitle("CL_{s}")
    banana2.GetXaxis().SetRangeUser(11,73)
    banana2.SetFillStyle(1001)
    banana1.SetFillColor(kYellow)
    banana1.SetFillStyle(1001)#3013)
    g0.SetLineStyle(9)
    if "OS" == mode:
      lat2 = TLatex(55,0.7,"(b)")
    else:
      lat2 = TLatex(55,0.7,"(c)")
    
    c = TCanvas()
    banana2.Draw("ALF")
    banana1.Draw("LF")
    lat = TLatex(55,0.8,"LHCb")
    lat.SetTextSize(1.5 * lat.GetTextSize())
    lat.Draw()
    lat2.Draw()
    g1.Draw("L")
    g0.SetLineColor(kBlue)
    g0.Draw("L")
    banana2.GetYaxis().SetRangeUser(0,1)
    c.RedrawAxis()
    import re
    c.SaveAs(re.sub(".*\/","",re.sub("\.dat",".eps",sys.argv[1])))
    return g0, g1, banana1, banana2, c


g0,g1,b1,b2,c = prepare_banana(sys.argv[1])
