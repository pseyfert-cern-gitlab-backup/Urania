#------------------------------------------------------------
# Alpha parameters:
# Normalisation for the combined sample
# for the Bs->mu mu analysis
#
# scaled to 2 fb-1
#
# ------------------------------------------------------------
from errors import *
import alphaparam_spring13_2012_scaled2 as a12
import alphaparam_spring13_2011 as a11
fdfs = a12.fdfs
Bdmumu_BR = a12.Bdmumu_BR
Bsmumu_BR = a12.Bsmumu_BR

TimeAcceptanceCorrBd = a12.TimeAcceptanceCorrBd
TimeAcceptanceCorrBs = a12.TimeAcceptanceCorrBs

from texlper import *
#For the formula explanation see
# F. Dettori at Bsmumu 13/06/2013


# https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2Ftrigger%20eff%20and%20justine%20factors&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
# Common inputs
# from Justine
# all the systematics from additional lines, and TISTOS are already in.
# The systematics on the ratio is the TISTOS contribution only

# Trigger efficiency estimated for the JPsi
JpsiE_trg = EVal(0.871,[0.003,0.024])  # Justine 20130625
JpsiE_trg = JpsiE_trg.compress_errors()
BuE_trg = JpsiE_trg
# Trigger efficiency for Bsmumu
BmmE_trg = EVal(0.924,[0.002,0.018])   # Justine 20130625
BmmE_trg = BmmE_trg.compress_errors()
# Trigger efficiency ratio for BuKpi/Bsmumu
BuRatE_trg = EVal(0.943,[0.004,0.023]) # Justine 20130625
BuRatE_trg = BuRatE_trg.compress_errors()


# Normalisation with Bu 
#  2011 
BuA11 = (a11.BuRatE_recsel * a11.BuRatE_trg) / a11.BuNcan
BuA11_fit = BuA11 / a11.BmmE_49006000  #alpha for fit
BuA11_mw  = BuA11 / a11.BmmE_mw       #Alpha for toys
#  2012 
BuA12 = (a12.BuRatE_recsel * a12.BuRatE_trg) / a12.BuNcan
BuA12_fit = BuA12 / a12.BmmE_49006000  #alpha for fit
BuA12_mw  = BuA12 / a12.BmmE_mw       #Alpha for toys


BuComb   = ( a11.BuBR ) / ( BuA11.invert() + BuA12.invert() )
BuasComb = fdfs * BuComb

BuComb_fit= ( a11.BuBR ) / ( BuA11_fit.invert() + BuA12_fit.invert() )
BuComb_mw = ( a11.BuBR ) / ( BuA11_mw.invert()  + BuA12_mw.invert() )


# Normalisation with Bu using combined trigger efficiencies
#  2011 
BuA11_forComb = (a11.BuRatE_recsel) / a11.BuNcan
BuA11_forComb_fit = BuA11_forComb / a11.BmmE_49006000  #alpha for fit
BuA11_forComb_mw  = BuA11_forComb / a11.BmmE_mw       #Alpha for toys         
#  2012 
BuA12_forComb = (a12.BuRatE_recsel) / a12.BuNcan
BuA12_forComb_fit = BuA12_forComb / a12.BmmE_49006000  #alpha for fit
BuA12_forComb_mw  = BuA12_forComb / a12.BmmE_mw       #Alpha for toys         

BuComb_forComb   = ( a11.BuBR * BuRatE_trg ) / ( BuA11_forComb.invert() + BuA12_forComb.invert() )
BuasComb_forComb = fdfs * BuComb_forComb

BuComb_forComb_fit= ( a11.BuBR * BuRatE_trg ) / ( BuA11_forComb_fit.invert() + BuA12_forComb_fit.invert() )
BuComb_forComb_mw = ( a11.BuBR * BuRatE_trg ) / ( BuA11_forComb_mw.invert()  + BuA12_forComb_mw.invert() )

print "   Normalisation for BuJpsik "
print "alpha 2011 ", BuA11, "  for N events = ", a11.BuNcan
print "alpha 2012 ", BuA12, "  for N events = ", a12.BuNcan
print "alpha Comb ", BuComb, "  for N events = ",  a11.BuNcan + a12.BuNcan
print "alpha Comb from Comb ", BuComb_forComb, "  for N events = ",  a11.BuNcan + a12.BuNcan


# Normalisation with Bd
#  2011 
BdA11 = (a11.BdRatE_recsel * a11.BdRatE_trg ) / a11.BdNcan
BdA11_fit = BdA11 / a11.BmmE_49006000  #alpha for fit
BdA11_mw  = BdA11 / a11.BmmE_mw       #Alpha for toys         
#  2012 
BdA12 = (a12.BdRatE_recsel * a12.BdRatE_trg ) / a12.BdNcan
BdA12_fit = BdA12 / a12.BmmE_49006000  #alpha for fit
BdA12_mw  = BdA12 / a12.BmmE_mw       #Alpha for toys         

BdComb   = a11.BdBR / ( BdA11.invert() + BdA12.invert() )
BdasComb = fdfs * BdComb

BdComb_mw = a11.BdBR / ( BdA11_mw.invert()  + BdA12_mw.invert() )
BdComb_fit= a11.BdBR / ( BdA11_fit.invert() + BdA12_fit.invert() )

# Normalisation with Bd using combined trigger efficiencies
#  2011 
BdA11_forComb = (a11.BdRatE_recsel * a11.BdE_trg / BmmE_trg) / a11.BdNcan
BdA11_forComb_fit = BdA11_forComb / a11.BmmE_49006000  #alpha for fit
BdA11_forComb_mw  = BdA11_forComb / a11.BmmE_mw       #Alpha for toys         
#  2012 
BdA12_forComb = (a12.BdRatE_recsel * a12.BdE_trg / BmmE_trg) / a12.BdNcan
BdA12_forComb_fit = BdA12_forComb / a12.BmmE_49006000  #alpha for fit
BdA12_forComb_mw  = BdA12_forComb / a12.BmmE_mw       #Alpha for toys         

BdComb_forComb   = a11.BdBR / ( BdA11_forComb.invert() + BdA12_forComb.invert() )
BdasComb_forComb = fdfs * BdComb_forComb

BdComb_forComb_mw = a11.BdBR / ( BdA11_forComb_mw.invert()  + BdA12_forComb_mw.invert() )
BdComb_forComb_fit= a11.BdBR / ( BdA11_forComb_fit.invert() + BdA12_forComb_fit.invert() )


print "   Normalisation for BdJpsik "
print "alpha 2011 ", BdA11, "  for N events = ", a11.BdNcan
print "alpha 2012 ", BdA12, "  for N events = ", a12.BdNcan
print "alpha Comb ", BdComb, "  for N events = ",  a11.BdNcan + a12.BdNcan
print "alpha Comb forComb", BdComb_forComb, "  for N events = ",  a11.BdNcan + a12.BdNcan

print '\n'*10

def averagealpha():
    print "Normalisation for the fit "
    print " from Bu ", BuComb
    print " from Bd ", BdComb
    alpha = BuComb.average(BdComb)
    alphas = alpha * fdfs
    print " Average alpha   = ", alpha
    alpha =     alpha / TimeAcceptanceCorrBd
    print " Corrected for Bd time acc = " , alpha
    print " Expected Bd events " , Bdmumu_BR/alpha
    print " Average alpha_s = ", alphas
    alphas = alphas / TimeAcceptanceCorrBs
    print " Corrected for Bs time acc = " , alphas
    print " Expected Bs events " , Bsmumu_BR/alphas
    print "Normalisation for the toys "
    print " from Bu ", BuComb_mw
    print " from Bd ", BdComb_mw
    alpha_mw = BuComb_mw.average(BdComb_mw)
    alphas_mw = fdfs* alpha_mw
    print " Average alpha (mw)  = ", alpha_mw
    print " Average alphas (mw)  = ", alphas_mw
    print " Corrected for time acceptance "
    alpha_mw = alpha_mw / TimeAcceptanceCorrBd
    alphas_mw = alphas_mw / TimeAcceptanceCorrBs
    print " Average alpha (mw)  = ", alpha_mw
    print " Average alphas (mw)  = ", alphas_mw
    return alpha, alphas, alpha_mw, alphas_mw

averagealpha()
