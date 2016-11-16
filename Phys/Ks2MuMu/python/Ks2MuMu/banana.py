from ROOT import *
import os
os.sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu/")
gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
from SomeUtils.numericFunctionClass import *
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


def prepare_banana(f,reduce = 1):
    w = getOutput(f)
    ch = w[-1]
    g0,g1 = TGraph(), TGraph()
    banana1,banana2 = TGraph(),TGraph()
    N = 0# len(ch)
    i,j = 0,0
    for k in range(len(ch)):
        if not (k%reduce): N += 1
            #continue
        
    print N, len(ch)
    for entry in ch:
        if j%reduce:
            j+=1
            continue
        g0.SetPoint(i,entry["BR"], entry["CLs_exp_b_med"])
        g1.SetPoint(i,entry["BR"], entry["CLs"])
        
        banana1.SetPoint(i,entry["BR"], entry["CLs_exp_b_p1"])
        banana1.SetPoint(2*N-i-1,entry["BR"], entry["CLs_exp_b_m1"])
        banana2.SetPoint(i,entry["BR"], entry["CLs_exp_b_p2"])
        banana2.SetPoint(2*N-i-1,entry["BR"], entry["CLs_exp_b_m2"])
        i +=1
        j +=1
    banana2.SetFillColor(kYellow)
    #banana2.GetXaxis().SetTitle("BR(K_{S}^{0}#rightarrow #mu^{+} #mu^{-})[#times 10^{-9}]")
    banana2.GetXaxis().SetTitle("BR(B_{s}^{0}#rightarrow #mu^{+} #mu^{-})[#times 10^{-9}]")
    banana2.GetYaxis().SetTitle("CL_{s}")
    banana2.SetFillStyle(1001)
    banana1.SetFillColor(kGreen)
    banana1.SetFillStyle(1001)#3013)
    g0.SetLineStyle(9)
    
    c = TCanvas()
    banana2.Draw("ALF")
    banana1.Draw("LF")
    g1.Draw("L")
    g0.SetLineColor(kBlue)
    g0.Draw("L")
    return g0, g1, banana1, banana2, c
#a = prepare_banana("Bs2012_all.dat")#"SMB_SYST1_MISID0.47703316959_sBk5.0_sB5.0_shh5.0_BG_Istyle1_ATLAS_PROF0_Bs.dat")
#a = prepare_banana(os.environ["BS2MUMUROOT"]#+"/python/Bs2MuMu/Bd_SYST1_MISID2.60199910685_sBk5.0_sB5.0_shh5.0_BG_Istyle1_ATLAS_PROF0_Bd.dat")
#                   + "/python/Bs2MuMu/SMB_SYST1_MISID0.47703316959_sBk5.0_sB5.0_shh5.0_BG_Istyle1_ATLAS_PROF0_Bs.dat")

ch = channelData("Bs2012_autum_2010_atlas_cms_cdf_SYST1job_all.dat",typ = "ASCII")
x = ch.takeKey("CLs")
x2 = ch.takeKey("CLs_exp_b_med")
clsb = ch.takeKey("CLsb")
#clbexp = ch.takeKey("CLb_exp_s_med")

y =  ch.takeKey("BR")
q = NF(x,y)
q2 = NF(x2,y)
clsb = NF(clsb,y)
p = NF(y, ch.takeKey("CLb"))
pexp = NF(y, ch.takeKey("CLb_exp_s_med"))
