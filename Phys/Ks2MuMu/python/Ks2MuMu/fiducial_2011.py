aa = "&&"

selection = "mu1pt>250 && mu2pt> 250 && mu1_track_Chi2DoF <5 && mu2_track_Chi2DoF<5 && DOCA < 0.3 && (SV3-PV3)>0 && Blife_ps_r > 8.95 && Bip_r <0.4 && lessIPSmu > 10"
armenteros = "(((4*AP_pt^2/1115.683^2 + (AP_alpha-0.69169)^2) > 4.7*100.7^2/(1115.683^2) || (4*AP_pt^2/1115.683^2 + (AP_alpha-0.69169)^2) < 3.5*100.7^2/(1115.683^2)) && ((4*AP_pt^2/1115.683^2 + (AP_alpha+0.69169)^2) > 4.7*100.7^2/(1115.683^2) || (4*AP_pt^2/1115.683^2 + (AP_alpha+0.69169)^2) < 3.5*100.7^2/(1115.683^2)))"
fiducial = "(" + selection + aa+ "mu1ip>0.5 && mu2ip>0.5 && Blife_ps_r <130 && mu1ptot < 1e05 && mu2ptot < 1e05 && Vchi2 < 25 &&" + armenteros +")"

tis = "(L0Tis && Hlt1Tis && Hlt2Tis)"
tos = "(L0MuonTos && Hlt1TrackMuonTos && Hlt2SingleMuonTos)"
xtos = tos + "&& " + "!" + tis
tob = "!" + tos + "&& " + "!" + tis

dll = "(PIDmu1>-4 && PIDmu2>-4)"
gec = "(nSPD<600&&nVelo<10000&&nIT<3000&&nOT<15000)"
fiducialtos = fiducial + aa + "(max(mu1pt,mu2pt) >1300 ) && " + gec
traintos =  "(PIDmu1>-1 && PIDmu2>-1 && mu1_nShared<2 && mu2_nShared<2 && mu1_track_Chi2DoF<2.5 && mu2_track_Chi2DoF<2.5" + aa + fiducial + aa + tos + ")"

pseudoprompt = " abs(mc_myv_z) <100 && abs(mc_myv_x)<.05 && abs(mc_myv_y)<.05"

mW = "Bmass>492 && Bmass<504"
