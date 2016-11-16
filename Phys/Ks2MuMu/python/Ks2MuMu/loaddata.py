from ROOT import *
from fiducial import *
from SomeUtils.alyabar import *
import KsmmMathCrap as K

fmb = TFile("minbias.root")
tmb = fmb.Get("T")

fpipiTISA = TFile("ks2pipi1fbA_TIS.root")
tpipiTISA = fpipiTISA.Get("T")

fmumuTOSA = TFile("ksmumu1fbA_TOS.root")
tmmTOSA = fmumuTOSA.Get("T")

fpipiTISB = TFile("ks2pipi1fbB_TIS.root")
tpipiTISB = fpipiTISB.Get("T")

fmumuTOSB = TFile("ksmumu1fbB_TOS.root")
tmmTOSB = fmumuTOSB.Get("T")

#tmmTOSA.Draw("runNum>>rTOSA(100,0,97500)", "("+ fiducial + aa + tos +aa +traintos +  "&& Bmass<500 )")

mydec = '((L0DiMuonDecision||L0ElectronDecision||L0ElectronHiDecision||L0HadronDecision||L0MuonDecision||L0PhotonDecision||'
mydec +='L0PhotonHiDecision)&&(Hlt1DiMuonHighMassDecision||Hlt1DiMuonLowMassDecision||Hlt1SingleElectronNoIPDecision||Hlt1SingleMuonHighPTDecision||'
mydec += 'Hlt1SingleMuonNoIPDecision||Hlt1TrackAllL0Decision||Hlt1TrackMuonDecision||Hlt1TrackPhotonDecision)&&(Hlt2B2HHDecision||Hlt2Charm__st__Decision||Hlt2DiElectron__st__Decision|'
#mydec += 'Hlt1SingleMuonNoIPDecision||Hlt1TrackAllL0Decision||Hlt1TrackMuonDecision||Hlt1TrackPhotonDecision)&&(Hlt2B2HHDecision||Hlt2DiElectron__st__Decision|'
mydec += '|Hlt2DiMuonBDecision||Hlt2DiMuonDY__st__Decision||Hlt2DiMuonDecision||'
mydec +='Hlt2DiMuonDetachedDecision||Hlt2DiMuonDetachedHeavyDecision||Hlt2DiMuonDetachedJPsiDecision||Hlt2DiMuonJPsiDecision||Hlt2DiMuonJPsiHighPTDecision||'
mydec += 'Hlt2DiMuonLowMassDecision||Hlt2DiMuonPsi2SDecision||Hlt2DiMuonZDecision||Hlt2IncPhiDecision||Hlt2SingleMuonDecision||Hlt2SingleMuonHighPTDecision||'
mydec += 'Hlt2SingleMuonLowPTDecision||Hlt2Topo2BodyBBDTDecision||Hlt2Topo2BodySimpleDecision||Hlt2Topo3BodyBBDTDecision||Hlt2Topo3BodySimpleDecision||Hlt2Topo4BodyBBDTDecision||'
mydec += 'Hlt2Topo4BodySimpleDecision||Hlt2TopoE__st__Decision||Hlt2TopoMu2BodyBBDTDecision||Hlt2TopoMu3BodyBBDTDecision||Hlt2TopoMu4BodyBBDTDecision||Hlt2Topo__st__Decision||Hlt2TriMuonTauDecision||'
mydec += 'Hlt2__st__Gamma__st__Decision))'

mytis = '((L0DiMuonTis||L0ElectronTis||L0ElectronHiTis||L0HadronTis||L0MuonTis||L0PhotonTis||L0PhotonHiTis)&&(Hlt1DiMuonHighMassTis'
mytis += '||Hlt1DiMuonLowMassTis||Hlt1SingleElectronNoIPTis||Hlt1SingleMuonHighPTTis'
mytis += '||Hlt1SingleMuonNoIPTis||Hlt1TrackAllL0Tis||Hlt1TrackMuonTis||Hlt1TrackPhotonTis)&&(Hlt2B2HHTis||Hlt2Charm__st__Tis||'
#mytis += '||Hlt1SingleMuonNoIPTis||Hlt1TrackAllL0Tis||Hlt1TrackMuonTis||Hlt1TrackPhotonTis)&&(Hlt2B2HHTis||'
mytis += 'Hlt2DiElectron__st__Tis||Hlt2DiMuonBTis||Hlt2DiMuonDY__st__Tis||Hlt2DiMuonTis||Hlt2DiMuonDetachedTis'
mytis += '||Hlt2DiMuonDetachedHeavyTis||Hlt2DiMuonDetachedJPsiTis||Hlt2DiMuonJPsiTis||Hlt2DiMuonJPsiHighPTTis||Hlt2DiMuonLowMassTis||'
mytis += 'Hlt2DiMuonPsi2STis||Hlt2DiMuonZTis||Hlt2IncPhiTis||Hlt2SingleMuonTis||Hlt2SingleMuonHighPTTis||Hlt2SingleMuonLowPTTis||'
mytis += 'Hlt2Topo2BodyBBDTTis||Hlt2Topo2BodySimpleTis||Hlt2Topo3BodyBBDTTis||Hlt2Topo3BodySimpleTis||Hlt2Topo4BodyBBDTTis||Hlt2Topo4BodySimpleTis||'
mytis += 'Hlt2TopoE__st__Tis||Hlt2TopoMu2BodyBBDTTis||Hlt2TopoMu3BodyBBDTTis||Hlt2TopoMu4BodyBBDTTis||Hlt2Topo__st__Tis||Hlt2TriMuonTauTis||Hlt2__st__Gamma__st__Tis))'

f1 = TFile("ksmumu_ntuple_240212_1000pb.root")
t1 = f1.Get("Ks2mumu")
f2 = TFile("kspipi_ntuple_240212_1000pb.root")
t2 = f2.Get("Ks2pipi")

tcks = []
for entry in t2:
    if entry.TCK not in tcks: tcks.append(entry.TCK)

## ## #BREAK
Presc, Lumi = {}, {}
Presc[ 0 ]=11.0
Presc[ 1 ]=11.0
Presc[ 2 ]=97
Presc[ 3 ]= 97
Presc[ 4 ]= 97.
Presc[ 5 ]=97
Presc[ 6 ]= 97
Presc[ 7 ]= 97
Presc[ 8 ]= 97
Presc[ 9 ]=97
Presc[ 10 ]=11
Presc[ 11 ]=97
Presc[ 12 ]=11
Presc[ 13 ]=97
#TCKs Integrated Luminosity Magnet Polarity
Lumi[0x5a0032] = 39 
Lumi[0x5a0032] = 29 
Lumi[0x6d0032] = 100 
Lumi[0x730035] = 196 
Lumi[0x740036] = 5.2  
Lumi[0x760037] = 298.7
Lumi[0x790037] = 39.3 
Lumi[0x790038] = 363.4


X = 0
for i in range(len(tcks)):
    tck = tcks[i]
    if tck not in Lumi.keys(): continue
    X +=Presc[i]*Lumi[tck] *1./20e06
        

tmmTOSB.Draw("SV1:SV3", "Bmass>500 && SV3 < 600 && abs(SV1) < 20 && SV3>0", "COL2")
BREAK

def doTcks(tcut = "(1>0)", ocut = "(!mu1ismu && !mu2ismu)" + aa + gec):
    trig = {}
    mbtrig = {}
    mb = {}
    mumu = {}
    for tck in tcks:
        trig[tck] = t2.GetEntries(fiducial + aa + ocut + aa  + tcut + aa + mydec + "&& TCK == "+str(tck))
        mbtrig[tck] = tmb.GetEntries(fiducial + aa + ocut + aa  + tcut + aa +mydec+" && TCK == "+str(tck))
        mb[tck] = tmb.GetEntries(fiducial + aa + ocut + aa + "TCK == "+str(tck))
        mumu[tck] = t1.GetEntries(fiducial + aa + traintos + aa + "TCK == "+str(tck))

    N = 0
    sN2 = 0
    Nt = 0
    Nmu = 0
    for key in mumu.keys():
        if mbtrig[key] < 20 :continue
        eff, seff = K.ratio(mbtrig[key], mb[key])
        print eff, seff
        d,sd = K.ratio(trig[key], eff, -1, seff)
        Nt += trig[key]
        Nmu += mumu[key]
        N+= d
        sN2 += sd*sd
    print Nt*1./sum(trig.values())   
    sN = sqrt(sN2)
    print Nmu * 1./ sum(mumu.values())
    print N, Nt*1./sum(trig.values())
    print N * 1./ (Nmu * 1./ sum(mumu.values()))

    return trig, mbtrig, mb, mumu



## trig, mbtrig, mb, mumu = doTcks(ocut = gec )

## N = 0
## sN2 = 0
## Nt = 0
## Nmu = 0
## for key in mumu.keys():
##     if mbtrig[key] < 20 :continue
##     eff, seff = K.ratio(mbtrig[key], mb[key])
##     print eff, seff
##     d,sd = K.ratio(trig[key], eff, -1, seff)
##     Nt += trig[key]
##     Nmu += mumu[key]
##     N+= d
##     sN2 += sd*sd
    
## sN = sqrt(sN2)
## print Nmu * 1./ sum(mumu.values())
## print N, Nt*1./sum(trig.values())
## print N * 1./ (Nmu * 1./ sum(mumu.values()))

## Ncorr = N*sum(mumu.values())*1./Nmu*1000
## prsc = tmb.GetEntries("!mu1ismu && !mu2ismu")*1./Ncorr
## print prsc
## gec = "(!mu1ismu &&!mu2ismu) "
## tos = "(L0Tos && Hlt1Tos && Hlt2Tos)"
## for tck in tcks:
##     print "TCK:",tck
##     a = tmb.GetEntries(mydec + aa + "(!mu1ismu && !mu2ismu) && TCK == "+str(tck))
##     b = tmb.GetEntries(mytis+ aa + "(!mu1ismu && !mu2ismu)  && TCK == "+str(tck))
##     c = tmb.GetEntries("TCK == "+str(tck))
##     print b,a , b*1./(max(a,1))
    

##     a = t2.GetEntries("( " + tis + "||" + tos +")"+ "&& TCK == "+str(tck))
##     b = t2.GetEntries(tis + " && TCK == "+str(tck))

##     print b,a , b*1./max(a,1)
##     print "0-0-0-0-0-0-0-"

    
## #'Hlt1L0AnyRateLimitedDecision'


## #122670313.121

## # 0.0033566719569211719

## #Sample A ~ 30 K
## #Sample B ~ 38 K

## ## import cPickle
## ## eps = cPickle.load(file("eps_TIS"))

## ## #for i in range(10):
## ## bdt = "BDTDTOSB"
## ## for i in range(10):
## ##     x = 0.1*i
## ##     print tmb.GetEntries(fiducialtos + aa +"Bmass>492 && Bmass<504&& " + bdt + ">" + str(eps(1-x)) + aa + bdt + "<" + str(eps(1-x-0.1)))
   
## for tck in tcks:
##     print "TCK:",tck
##     a = tmb.GetEntries(gec +aa +"L0Decision && Hlt1Decision &&Hlt2Decision && TCK == "+str(tck))
##     b = tmb.GetEntries(fiducial + aa  + gec + aa + tis + aa + "L0Decision &&Hlt1Decision &&Hlt2Decision && TCK == "+str(tck))
##     c = tmb.GetEntries(fiducial + aa+ gec+ "&& TCK == "+str(tck))
##     print b,a , b*1./(max(a,1))
    

##     a = t2.GetEntries(fiducial + aa  +  gec + aa +"L0Decision && Hlt1Decision &&Hlt2Decision && TCK == "+str(tck))
##     b = t2.GetEntries(fiducial + aa  + gec + aa + tis + aa + "L0Decision && Hlt1Decision &&Hlt2Decision  && TCK == "+str(tck))

##     print b,a , b*1./max(a,1)
##     print "0-0-0-0-0-0-0-"

    
## >>> sN/N
## 0.08029758552321925
## >>> (t2.GetEntries()*1./Ncorr*1000)
## 2.1836695435824369e-06
## >>> (t2.GetEntries(tis)*1./Ncorr*1000)
## 0.0021836695435824369
## >>> (t2.GetEntries(tis)*1./Ncorr*1000)
## 0.001472635896704824
## >>> ## working on region in file /tmp/diegoms/python-11440JSZ...
## >>> prsc
## 2.2869557824506344e-06
## >>> 
