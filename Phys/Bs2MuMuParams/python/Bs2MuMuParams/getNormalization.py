from Bs2MuMu.functions_for_finalanalysis import *
from alphaparam_1fb import *

print "imported alpha for Bu2JPsiK   for Bsmm: ", Buas,"and for Bd2mm: ",Buad
print "imported alpha for Bs2JPsiPhi for Bs2mm ", Bsas,"and for Bd2mm: ",Bsad
print "imported alpha for Bd2Kpi     for Bs2mm ", Bdas,"and for Bd2mm: ",Bdad


#channel Bs or Bd
def averageAlpha(CHANNEL="Bs"):

    c_phi = val(Bs)
    sc_phi = err(Bs)    

    c_bu = val(Bu)
    sc_bu = err(Bu)

    b_kpi  =val(Bdp)
    sb_kpi =err(Bdp)

    Ntis_hh = val(BhhNcanTis)
    sNtis_hh = err(BhhNcanTis)

    _fdfs = val(fdfs)
    s_fdfs = err(fdfs)

    c_kpi, sc_kpi = do_kpi_coef(b_kpi,sb_kpi,Ntis_hh, sNtis_hh)
    
    print CHANNEL
    alpha, s_alpha = calculateNormalizationFactor( c_bu, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, _fdfs, s_fdfs, channel = CHANNEL)
    
    return alpha, s_alpha
