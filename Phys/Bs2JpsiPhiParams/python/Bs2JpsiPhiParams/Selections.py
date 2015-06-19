
### Some BKK of Bs ->JpsiPhi selection cuts


selection = 'time>0.3 && time<14. && mass>5200. && mass<5550. && abs(mdau1-3090.)<60.  && sigmat<0.12 ' 
chi2Selection = ' && muplus_track_chi2ndof<4. && muminus_track_chi2ndof<4. && Kplus_track_chi2ndof<4. && Kminus_track_chi2ndof<4.'
cuts = selection + chi2Selection
cuts += "&&"  +"runNumber > 0 && sel==1 && (hlt1_biased==1 || hlt1_unbiased_dec==1) && hlt2_biased==1 && muplus_track_chi2ndof < 4.000000 && muminus_track_chi2ndof < 4.000000 && Kplus_track_chi2ndof < 4.000000 && Kminus_track_chi2ndof < 4.000000"
cutswide = cuts
cutsphitight =cuts + "&& abs(mdau2-1020.)<12."

## cutswide : all cuts but phimass
## cutsphitight: 12 MeV around 1020
