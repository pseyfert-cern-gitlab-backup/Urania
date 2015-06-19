from triggerclass import *
from SomeUtils.alyabar import *
from SomeUtils.someFunctions import *

def addthings(ch):
    ch.addVariable("mu1pVec",["mu1p1","mu1p2","mu1p3"],vector)
    ch.addVariable("mu2pVec",["mu2p1","mu2p2","mu2p3"],vector)
    ch.addVariable("svVec",["SV1","SV2","SV3"],vector)
    ch.addVariable("pvVec",["PV1","PV2","PV3"],vector)
    ch.addVariable("rSV",["svVec","pvVec"],resta)
    ch.kill("svVec")
    ch.kill("pvVec")
    ch.addVariable("Bdis",["rSV"],vmod)
    ch.kill("rSV")
    ch.addVariable("DZ",["SV3","PV3"],resta)
  
    ch.addVariable("mu1pt",["mu1pVec"],vtmod)
    ch.addVariable("mu2pt",["mu2pVec"],vtmod)
    ch.kill("mu1pVec")
    ch.kill("mu2pVec")
    ch.addVariable("maxptmu",["mu1pt","mu2pt"],max)
    ch.addVariable("maxIPSmu",["mu1ips","mu2ips"],max)
    ch.addVariable("maxip",["mu1ip","mu2ip"],max)
    
    
def addKstMass(ch):
    ch.desagrupate()
    for entry in ch:
        kp = vector(entry["k1p1"],entry["k1p2"],entry["k1p3"])
        pip = vector(entry["pip1"],entry["pip2"],entry["pip3"])
        entry["KstMass"] = sqrt(IM2(kp,pip, 493.677,139.57018))
    
ptcuts = trigger()
ptcuts.addCut("mu1pt>700")
ptcuts.addCut("mu2pt>700")
ptcuts.addCut("maxptmu>2400")

marcoc, marco = trigger(), trigger()
marcoc.addCut("Bmass>5000")
marcoc.addCut("Bmass<5800")

marcoc.addCut("DOCA<0.08")
marcoc.addCut("mu1mip>0.1")
marcoc.addCut("mu2mip>0.1")

marcoc.addCut("Bip<0.06")
marcoc.addCut("Bdis>1.8")
marcoc.addCut("DZ>0")
marco.addCut(marcoc)
marco.addCut(ptcuts)
marco.addCut("maxip>0.2")

oldhh = trigger() ## but with new pt cuts

oldhh.addCut("Bmass>4679")
oldhh.addCut("Bmass<5879")
oldhh.addCut(ptcuts)
oldhh.addCut("Vchi2<14")
oldhh.addCut("lessIPSmu>3.5")
oldhh.addCut("Bdissig>12")
oldhh.addCut("maxIPSmu>5.5")
oldhh.addCut("Bips<6")
oldhh.addCut("Bpt>700")

buc, bu = trigger(), trigger()
jpm = trigger()
jpm.addCut("JPsiMass>3037")
jpm.addCut("JPsiMass<3157")


burc, bur = trigger(), trigger()

burc.addCut("Bmass>4779")
burc.addCut("Bmass<5779")
burc.addCut("JPsi_dis>1.8")
burc.addCut("Bip<0.1")
burc.addCut("DOCA<0.08")
burc.addCut("kip>0.06")
#burc.addCut("Bpt>700")

bur.addCut(burc)
bur.addCut(jpm)
#bur.addCut("JPsiMass<3157")
bdc, bd = trigger(), trigger()
kstm = trigger()
kstm.addCut("KstMass>855.5")
kstm.addCut("KstMass<935.5")


bdc.addCut("Bmass>4779")
bdc.addCut("Bmass<5779")
bdc.addCut("dDsig>12")
bdc.addCut("Bips<6")
bdc.addCut("JPsiChi2<14")
bdc.addCut("kstips>3.5")
bdc.addCut("Bpt>700")
bd.addCut(bdc)
bd.addCut(jpm)
bd.addCut(kstm)

bdrc, bdr = trigger(), trigger()

bdrc.addCut("Bmass>4779")
bdrc.addCut("Bmass<5779")
bdrc.addCut("JPsi_dis>1.8")
bdrc.addCut("Bip<0.1")
bdrc.addCut("DOCA<0.08")
bdrc.addCut("kstip>0.06")
#bdrc.addCut("Bpt>700")
bdr.addCut(bdrc)
bdr.addCut(jpm)
bdr.addCut(kstm)

def checkOverlaps(l):
    out = []
    for channel in l:
        channel.agrupateInEvents()
        for event in channel:
            name = [event[0]["evtNum"],event[0]["runNum"]]
            if name not in out: out.append(name)
    return out
            
    
c4s = trigger()
c4s.addCut("lessIPSmu>5")
c4s.addCut("Bdissig>15")
c4s.addCut("Bips<5")
c4s.addCut("Vchi2<9")

c4u = trigger()
c4u.addCut("k1ips>5")
c4u.addCut("dDsig>15")
c4u.addCut("Bips<5")
c4u.addCut("JPsiChi2<9")

##c2s = trigger()
##c2s.addCut("mu1ip>0.1")
##c2s.addCut("mu2ip>0.1")
##c2s.addCut("Bip<0.06")

c2u = trigger()
c2u.addCut("kip>0.1")
#c2s.addCut("mu2ip>0.1")
c2u.addCut("Bip<0.06")

cd1 = trigger()
cd1.addCut("Bips<5")
cd1.addCut("JPsiChi2<9")
cd1.addCut("dDsig>15")
cd1.addCut("k1ips>2")
cd1.addCut("pips>2")

cd2 = trigger()
cd2.addCut("Bip<0.06")
#cd2.addCut("JPsiChi2<9")
#cd2.addCut("dDsig>15")
cd2.addCut("kip>0.07")
cd2.addCut("pip>0.07")

ng = Cut("L0MuonNoGlob_d>0")
hlt = Cut("HLT1_d>0")
ngh = trigger()
ngh.addCut(ng)
ngh.addCut(hlt)

bdjpsi1 = trigger()
bdjpsi1.addCut("Bmass>4779")
bdjpsi1.addCut("Bmass<5779")
bdjpsi1.addCut("JPsiChi2<9")
bdjpsi1.addCut("Bips<5")
#bdjpsi.addCut("Bpt>700")
bdjpsi1.addCut("dDsig>25")

kstm = trigger()
kstm.addCut("KstMass>851.66")
kstm.addCut("KstMass<931.66")
#

bdjpsi2 = trigger()
bdjpsi2.addCut("kstips>5")
bdjpsi2.addCut(jpm)
bdjpsi2.addCut(kstm)
bdjpsi2.addCut("k1ips>2")
bdjpsi2.addCut("pips>1")

bdjpsi = trigger()
bdjpsi.addCut(bdjpsi1)
bdjpsi.addCut(bdjpsi2)


bu2 = trigger()
bu2.addCut(bdjpsi1)
bu2.addCut("k1ips>5")
bu2.addCut(jpm)


bu.addCut("Bmass>4779")
bu.addCut("Bmass<5779")
bu.addCut("JPsiChi2<9")
bu.addCut("Bips<5")
#bdjpsi.addCut("Bpt>700")
bu.addCut("dDsig>15")
bu.addCut("k1ips>5")
bu.addCut(jpm)



bhh = trigger() ## but with new pt cuts

bhh.addCut("Bmass>4779")
bhh.addCut("Bmass<5779")
bhh.addCut("Vchi2<9")
bhh.addCut("Bips<5")
bhh.addCut("Bdissig>15")
bhh.addCut("lessIPSmu>5")



sel = trigger() ## but with new pt cuts

sel.addCut("Bmass>4769.6")
sel.addCut("Bmass<5969.6")
sel.addCut("Vchi2<9")
sel.addCut("Bips<5")
sel.addCut("Bdissig>15")
sel.addCut("lessIPSmu>5")







    
    
    
