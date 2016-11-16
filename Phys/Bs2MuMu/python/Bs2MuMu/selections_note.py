from triggerclass import *

sphi = trigger()
sphi.addCut("mu1_track_Chi2DoF<5")
sphi.addCut("mu2_track_Chi2DoF<5")
sphi.addCut("mu1_kaon_Chi2DoF<5")
sphi.addCut("pion_track_Chi2DoF<5")

sphi.addCut("mu1ips>5")
sphi.addCut("mu2ips>5")
sphi.addCut("k1ips>2")
sphi.addCut("pips>1")


sphi.addCut("DOCA<0.3")
sphi.addCut("JPsiChi2<9")
sphi.addCut("JPsiMass>3036.916")
sphi.addCut("JPsiMass<3126.916")

sphi.addCut("dDsig>15")
sphi.addCut("PhiMass>1009.455")
sphi.addCut("PhiMass<1029.455")
sphi.addCut("phiips>5")
sphi.addCut("Bips<5")
sphi.addCut("Bmass>5166.3")
sphi.addCut("Bmass<5566.3")
sphi.addCut("Vchi2<75")



su = trigger()
su.addCut("mu1_track_Chi2DoF<5")
su.addCut("mu2_track_Chi2DoF<5")
su.addCut("mu1_kaon_Chi2DoF<5")
#sphi.addCut("pion_track_Chi2DoF<5")

su.addCut("mu1ips>5")
su.addCut("mu2ips>5")


su.addCut("DOCA<0.3")
su.addCut("JPsiChi2<9")
su.addCut("JPsiMass>3036.916")
su.addCut("JPsiMass<3126.916")

su.addCut("dDsig>15")
#sphi.addCut("PhiMass>999.455")
#sphi.addCut("PhiMass<1049.455")
su.addCut("Bips<5")
su.addCut("Bmass>4877.5")
su.addCut("Bmass<5677.5")

### Vchi2?

sd = trigger()
sd.addCut("mu1_track_Chi2DoF<5")
sd.addCut("mu2_track_Chi2DoF<5")
sd.addCut("mu1_kaon_Chi2DoF<5")
sd.addCut("pion_track_Chi2DoF<5")
su.addCut("Kstips>5")
sd.addCut("mu1ips>5")
sd.addCut("mu2ips>5")
sd.addCut("k1ips>2")
sd.addCut("pips>1")

sd.addCut("DOCA<0.3")
sd.addCut("JPsiChi2<9")
sd.addCut("JPsiMass>3036.916")
sd.addCut("JPsiMass<3126.916")

sd.addCut("dDsig>25")
sd.addCut("KstMass>695.94")
sd.addCut("KstMass<1095.94")
sd.addCut("Bips<5")
sd.addCut("Bmass>5127.5")
sd.addCut("Bmass<57.5")

## ses.sysfrach = nps_high[i];
##        if (lowshape[i] !=0)
## 	 {
##            ses.lowshape = (TH1*) lowshape[i]->Clone();
## 	   printf("%s %s %lf\n",s, ses.lowshape->GetName(),ses.lowshape->GetBinContent(3,3) );// Diego, debug info
