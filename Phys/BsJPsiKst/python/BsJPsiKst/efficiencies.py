from ROOT import *



cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 "
cuts += "&& kaon_pt>500 && pion_pt>500"
cuts += "&& abs(Mjpsik-5279)>60"
cuts += "&& abs(KstMass-896)<40"


f = TFile("/afs/cern.ch/user/d/diegoms/vol5/BdJpsiKstMU.root")
t = f.Get("Bd2JPsiKstar/Bd2JPsiKstar")
f2 = TFile("eraseme","recreate")
t2 = t.CopyTree(cuts)

import cPickle
import sys, os
sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu")
from triggerclass import *
from smartpyROOT import *
gl = cPickle.load(file(os.environ["BSJPSIKSTROOT"] + "/operators/GL_JPsiKst_Sept5"))
ch = channelData(fromRootToListDic(t2))
gl(ch,"GL11")

dumi = Cut("GL11sb.>0.2")(ch)
print len(dumi)

dumi = Cut("Hlt1Decision>0")(dumi)
dumi = Cut("Hlt2Decision>0")(dumi)
dumi = Cut("L0Decision>0")(dumi)

print len(dumi)
