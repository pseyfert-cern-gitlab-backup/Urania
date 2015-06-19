
### Some BKK of Bs ->JpsiPhi selection cuts


selection = 'time>0.3 && time<14. && mass>5200. && mass<5550. && abs(mdau1-3090.)<60.  && sigmat<0.12 ' 
chi2Selection = ' && muplus_track_chi2ndof<4. && muminus_track_chi2ndof<4. && Kplus_track_chi2ndof<4. && Kminus_track_chi2ndof<4.'
cuts = selection + chi2Selection
cuts += "&&"  +"runNumber > 0 && sel==1 && (hlt1_biased==1 || hlt1_unbiased_dec==1) && hlt2_biased==1 && muplus_track_chi2ndof < 4.000000 && muminus_track_chi2ndof < 4.000000 && Kplus_track_chi2ndof < 4.000000 && Kminus_track_chi2ndof < 4.000000"
cutswide = cuts
cutsphitight =cuts + "&& abs(mdau2-1020.)<12."

## cutswide : all cuts but phimass
## cutsphitight: 12 MeV around 1020



sel_no_mass = 'time>0.3 && time<14. && sigmat<0.12 && Kplus_track_chi2ndof<4. && Kminus_track_chi2ndof<4 && muplus_track_chi2ndof < 4.000000 && muminus_track_chi2ndof < 4.000000 && phi_1020_pt>1000'
sel_no_mass += " && Kplus_pidK>0 && Kminus_pidK > 0 && B_s0_LOKI_DTF_VCHI2NDOF < 5 && sqrt( muplus_PX^2 + muplus_PY^2) > 500 && sqrt( muminus_PX^2 + muminus_PY^2)>500 && B_s0_IPCHI2_OWNPV < 25 && B_s0_ENDVERTEX_CHI2<50"

sidebands_training = "(B_s0_MM < 5320. || B_s0_MM > 5420.)"
sel_ntuple_big_no_mass = "B_s0_LOKI_DTF_CTAU/0.299792458 > 0.3 && B_s0_LOKI_DTF_CTAU/0.299792458 < 14 &&  B_s0_LOKI_DTF_CTAUERR/0.299792458 < 0.12 &&  Kminus_TRACK_CHI2NDOF < 4 &&  Kplus_TRACK_CHI2NDOF< 4 &&  muminus_TRACK_CHI2NDOF <4 &&  muplus_TRACK_CHI2NDOF <4"
sel_ntuple_big_no_mass += "&& B_s0_IPCHI2_OWNPV < 25 &&  Kplus_PIDK >0 && Kminus_PIDK > 0 && muplus_PT > 500 && muminus_PT >500 && B_s0_LOKI_DTF_CHI2NDOF <5 && phi_1020_PT>1000 && phi_1020_ENDVERTEX_CHI2<16"
sel_ntuple_big_no_mass += "&& J_psi_1S_ENDVERTEX_CHI2<16 && B_s0_ENDVERTEX_CHI2<50"
next_PV =  "&& (B_s0_MINIPCHI2NEXTBEST>50 || B_s0_MINIPCHI2NEXTBEST<0)"
#sel_ntuple_big_no_mass += "&& Kminus_TRACK_CloneDist > 5000 && Kplus_TRACK_CloneDist > 5000 && muminus_TRACK_CloneDist > 5000 && muplus_TRACK_CloneDist > 5000"


#trigger_train = "(B_s0L0Decision_TOS && B_s0Hlt1DiMuonHighMassDecision_TOS && B_s0Hlt2DiMuonDetachedJPsiDecision_TOS)"
trigger_train = "(B_s0L0Global_TOS && B_s0Hlt1DiMuonHighMassDecision_TOS && B_s0Hlt2DiMuonDetachedJPsiDecision_TOS)"



cuts_mass = "abs(mdau1-3090)<60 && abs(mdau2-1020.)<30.&& mass>5200. && mass<5550."
cuts_mass_big = "abs(J_psi_1S_MM-3090)<60 && abs(phi_1020_MM-1020.)<30.&& B_s0_MM>5200. && B_s0_MM<5550."

training_sel = cuts_mass_big + " && B_s0_LOKI_DTF_CTAU/0.299792458 > 0.3 && B_s0_LOKI_DTF_CTAU/0.299792458 < 14 &&  B_s0_LOKI_DTF_CTAUERR/0.299792458 < 0.12 &&  Kplus_PIDK>0 && Kminus_PIDK > 0 " + next_PV
