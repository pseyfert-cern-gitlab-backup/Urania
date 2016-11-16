from ROOT import *
f = TFile("KsKlMC11count.root")

tkl = f.Get("Kl_mct/Kl_mct")
tks = f.Get("Ks_mct/Ks_mct")

import os
os.sys.path.append(os.environ["BS2MUMUROOT"]+"/python/Bs2MuMu/")
from triggerclass import *
from smartpyROOT import *
ks = channelData(fromRootToListDic(tks))
kl = channelData(fromRootToListDic(tkl))
ks.addVariable("absid", ["mc_moth_mother"], abs)
kl.addVariable("absid", ["mc_moth_mother"], abs)
kl.addVariable("evt", ["mc_moth_mother"], abs)
ks.addVariable("evt", ["mc_moth_mother"], abs)


def do_KsKl(var,m,M,bins, decaytype = 0):
    if decaytype != 0:
        dc = trigger()
        dc.addCut("decayType>" + str(decaytype-0.1))
        dc.addCut("decayType<" + str(decaytype+0.1))

        dks = dc(ks)
        dkl = dc(kl)
    else:
        dks =ks
        dkl = kl
    hks = dks.histogram(var,m,M,bins)
    hkl = dkl.histogram(var,m,M,bins)

    return hratio(hks,hkl)


def ratio(a,b):
    if (b*a)!= 0: return a*1./b, sqrt( 1./a + 1./b)*a*1./b
    return 0,0
def hratio(a,b):
    h = a.Clone()
    for i in range(a.GetNbinsX()):
        x = a.GetBinContent(i+1)
        y = b.GetBinContent(i+1)
        r,sr = ratio(x,y)
        h.SetBinContent(i+1, r)
        h.SetBinError(i+1, sr)
    return h


        
#>>> ratio(tks.GetEntries("decayType==2"), tkl.GetEntries("decayType==2"))
#(1.018168335187245, 0.0065059655811022981)
#>>>
#>>> ratio(tks.GetEntries("decayType==100"), tkl.GetEntries("decayType==100"))
#(0.68935004740334982, 0.0078318252899764133)
#>>> 
#>>> ratio(tks.GetEntries("decayType==2 && abs(mc_moth_mother)>1e06"), tkl.GetEntries("decayType==2&& abs(mc_moth_mother)>1e06"))
#(1.0, 0.20851441405707477)
#>>> t.GetEntries()
#14173L
#>>> t.GetEntries("B_pvtype==2")
#14112L
#>>>
BREAK
#(with trigger: 20/20)

from ParticleTranslator import PTranslate as dc
mothKs, mothKl = {}, {}
for entry in ks:
    if entry["decayType"] == 2: continue
    moth = abs(entry["mc_moth_mother"])
    if abs(moth) not in mothKs.keys():
        mothKs[moth] = 1
    else:  mothKs[moth] += 1

for entry in kl:
    if entry["decayType"] == 2: continue
    moth = abs(entry["mc_moth_mother"])
    if abs(moth) not in mothKl.keys():
        mothKl[moth] = 1
    else:  mothKl[moth] += 1

for key in mothKl.keys():
    if key not in mothKs.keys():
        x, sx = -1, -1
        print key
    else: x,sx = ratio(mothKs[key],mothKl[key])
    #x = max(x,-1)
    print dc(key) , "&" + str(mothKl[key]) + " &", str(x) +" \\pm " +str(sx)+ " \\\ "





        
