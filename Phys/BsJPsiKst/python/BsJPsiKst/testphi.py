from ROOT import *
from SomeUtils.alyabar import *
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from OurSites import *
from Urania import PDG
from triggerclass import *

KZFILE ="/MC/Bd_MCT_n"
t11p,f11p = getTuple(NTUPLE_PATH + "/2011p", thing = "DecayTree")
tp,fp = getTuple(NTUPLE_PATH + KZFILE)# + "_dev")#, thing = "DecayTree")

#BREAK
## g = TGraph()
## i = 0
## for entry in t11p:
##     muplus_P = TLorentzVector(entry.muplus_PX,entry.muplus_PY,entry.muplus_PZ,entry.muplus_PE)
##     muminus_P = TLorentzVector(entry.muminus_PX,entry.muminus_PY,entry.muminus_PZ,entry.muminus_PE)
##     Kplus_P = TLorentzVector(entry.Kplus_PX,entry.Kplus_PY,entry.Kplus_PZ,entry.Kplus_PE)
##     piminus_P = TLorentzVector(entry.piminus_PX,entry.piminus_PY,entry.piminus_PZ,entry.piminus_PE)
##     angs =  HelicityAngles(Kplus_P, piminus_P, muplus_P, muminus_P )

##     g.SetPoint(i,entry.B0_Phi,angs[2])
##     i+=1

ch = channelData(fromRootToListDic(tp))

## g2 = TGraph()
## g3 = TGraph()
i = 0
for entry in tp:
    muplus_P = TLorentzVector(entry.mu1p1,entry.mu1p2,entry.mu1p3,sqrt( entry.mu1p1**2 + entry.mu1p2**2 + entry.mu1p3**2 + PDG.Muon.mass**2))
    muminus_P = TLorentzVector(entry.mu2p1,entry.mu2p2,entry.mu2p3,sqrt(entry. mu2p1**2 + entry.mu2p2**2 + entry.mu2p3**2 + PDG.Muon.mass**2))
    Kplus_P = TLorentzVector(entry.k1p1,entry.k1p2,entry.k1p3,sqrt( entry.k1p1**2 + entry.k1p2**2 + entry.k1p3**2 + PDG.Kplus.mass**2))
    piminus_P = TLorentzVector(entry.p1p1,entry.p1p2,entry.p1p3,sqrt( entry.p1p1**2 + entry.p1p2**2 + entry.p1p3**2 + PDG.piplus.mass**2))
    angs =  HelicityAngles(Kplus_P, piminus_P, muplus_P, muminus_P )
    ch[i]["ph_old"] = ch[i]["ph"] * 1.0
    ch[i]["ph"] = angs[2]
    i += 1
ch.save(NTUPLE_PATH + KZFILE + "_dev")
   ##  g2.SetPoint(i,entry.ph,angs[2])
##     g3.SetPoint(i,entry.ph,-pi - angs[2])
##     i+=1
