#!/usr/bin/env python
import re, sys
if len(sys.argv) < 2:
  print "Usage:"
  print "python -i " + sys.argv[0] + " <filename>"
  print "where filename is the (relative or absolute) path to the .dat file"
  print "produced by the limit calculation scripts in Phys/Tau23Mu/math."
  print "Example:"
  print "   python -i "+sys.argv[0] + " ../../math/something.dat"
  print ""
  sys.exit()

from ROOT import *
import os
os.sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu/")
from SomeUtils.numericFunctionClass import *
#from dev_channelclass import *
from triggerclass import *


def getOutput(filename):
    ch = channelData(filename, typ="ASCII")
    #ts = ch.takeKey("ts")
    #ts0 = min(ts)
    for i in range(len(ch)):
        ch[i]["evt"] = i
        ch[i]["oCLsb"] = 1-ch[i]["CLsb"]
        ch[i]["oCLs"] = 1-ch[i]["CLs"]
        #ch[i]["ets"] = exp(-(ch[i]["ts"]-ts0))
    x = ch.takeKey("BR")
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
        g0.SetPoint(i,1e8*entry["BR"], entry["CLs_exp_b_med"])
        g1.SetPoint(i,1e8*entry["BR"], entry["CLs"])
        
        banana1.SetPoint(i,1e8*entry["BR"], entry["CLs_exp_b_p1"])
        banana1.SetPoint(2*N-i-1,1e8*entry["BR"], entry["CLs_exp_b_m1"])
        banana2.SetPoint(i,1e8*entry["BR"], entry["CLs_exp_b_p2"])
        banana2.SetPoint(2*N-i-1,1e8*entry["BR"], entry["CLs_exp_b_m2"])
        i +=1
    banana2.SetFillColor(kGreen)
    banana2.GetXaxis().SetTitle("BR(#tau^{#font[122]{-}} #rightarrow #mu^{#font[122]{+}} #mu^{#font[122]{-}} #mu^{#font[122]{-}}) [#times 10^{-8}]")
    banana2.GetXaxis().SetRangeUser(1.1,9.4)
    banana2.GetYaxis().SetTitle("CL_{s}")
    banana2.SetFillStyle(1001)
    banana1.SetFillColor(kYellow)
    banana1.SetFillStyle(1001)#3013)
    g0.SetLineStyle(9)
    lat2 = TLatex(11.5,0.7,"(a)")
    
    c = TCanvas()
    banana2.Draw("ALF")
    banana1.Draw("LF")
    lat = TLatex(11.5,0.8,"LHCb")
    lat.SetTextSize(1.5 * lat.GetTextSize())
    lat.Draw()
    lat2.Draw()
    g1.Draw("L")
    g0.SetLineColor(kBlue)
    g0.Draw("L")
    c.RedrawAxis()
    import re
    banana2.GetYaxis().SetRangeUser(0,1)
    c.SaveAs(re.sub(".*\/","",re.sub("\.dat",".eps",sys.argv[1])))
    return g0, g1, banana1, banana2, c


g0,g1,b1,b2,c = prepare_banana(sys.argv[1])
