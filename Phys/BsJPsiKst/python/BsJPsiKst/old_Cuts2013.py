## Carlos Vazquez Sierra, 09 Dec 2013
## carlos.vazquez@cern.ch

## Strings: cuts_loose_2011, cuts_loose_2012,
##          cuts_tightcode_2011, cuts_tightcode_2012,
##          cuts_tightnote_2011, cuts_tightnote_2012.

## Rectangular cuts (loose):
rect_cuts_loose = "muplus_MINIPCHI2 > 16. && muminus_MINIPCHI2 > 16. && Kplus_MINIPCHI2 > 2. && piminus_MINIPCHI2 > 2."
rect_cuts_loose += " && B0_LOKI_DTF_CTAU > 0."
rect_cuts_loose += " && Kplus_PT > 500. && piminus_PT > 500."
rect_cuts_loose += " && abs(Kst_892_0_MM-896) < 70."
rect_cuts_loose += " && abs(Mjpsik-5279) > 60."
cuts_loose = rect_cuts_loose + " && piminus_PIDK<-6 && Kplus_PIDK>6"
cuts_loose_2011 = cuts_loose + " && BDTG>0.2"
cuts_loose_2012 = cuts_loose + " && BDTG>-0.24"

## Rectangular cuts (tight, from the fit code used during the first months of 2013):
rect_cuts_tightcode = "muplus_MINIPCHI2 > 25 && muminus_MINIPCHI2 > 25 && Kplus_MINIPCHI2 > 4 && piminus_MINIPCHI2 > 4  && "
rect_cuts_tightcode += "Kplus_PT > 500 && piminus_PT>500 && "
rect_cuts_tightcode += "J_psi_1S_FDCHI2_TOPPV > 169 && J_psi_1S_LOKI_DOCA_1_2<0.3 && "
rect_cuts_tightcode += "J_psi_1S_ENDVERTEX_CHI2 < 9 && B0_IPCHI2_OWNPV < 25 && "
rect_cuts_tightcode += "abs(Mjpsik-5279)>60 && "
rect_cuts_tightcode += "abs(Kst_892_0_MM-896)<70"
cuts_tightcode = rect_cuts_tightcode + " && piminus_PIDK<-6 && Kplus_PIDK>6"
cuts_tightcode_2011 = cuts_tightcode + " && BDTG>0.2"
cuts_tightcode_2012 = cuts_tightcode + " && BDTG>-0.24"

## Rectangular cuts (tight, from LHCb-ANA-2011-071):
rect_cuts_tightnote = "muplus_TRACK_CHI2NDOF < 5. && muminus_TRACK_CHI2NDOF < 5."
rect_cuts_tightnote += " && piminus_TRACK_CHI2NDOF < 5. && Kplus_TRACK_CHI2NDOF < 5."
rect_cuts_tightnote += " && muplus_isMuon > 0. && muminus_isMuon > 0."
rect_cuts_tightnote += " && muplus_MINIPCHI2 > 25. && muminus_MINIPCHI2 > 25."
rect_cuts_tightnote += " && Kplus_MINIPCHI2 > 4. && piminus_MINIPCHI2 > 4."
rect_cuts_tightnote += " && B0_LOKI_DTF_CTAU > 0."
rect_cuts_tightnote += " && Kplus_PT > 500. && piminus_PT > 500."
rect_cuts_tightnote += " && J_psi_1S_ENDVERTEX_CHI2 < 9. && abs(J_psi_1S_MM-3096.9) < 60."
rect_cuts_tightnote += " && J_psi_1S_FDCHI2_TOPPV > 169. && J_psi_1S_LOKI_DOCA_1_2 < 0.3"
rect_cuts_tightnote += " && Kst_892_0_ENDVERTEX_CHI2 < 9. && abs(Kst_892_0_MM-896) < 70."
rect_cuts_tightnote += " && B0_ENDVERTEX_CHI2 < 25. && B0_IPCHI2_OWNPV < 25. && abs(Mjpsik-5279) > 60."
cuts_tightnote = rect_cuts_tightnote + " && piminus_PIDK<-6 && Kplus_PIDK>6"
cuts_tightnote_2011 = cuts_tightnote + " && BDTG>0.2"
cuts_tightnote_2012 = cuts_tightnote + " && BDTG>-0.24"
