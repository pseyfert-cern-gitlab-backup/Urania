#------------------------------------------------------------
# Alpha parameters:
# Normalisation for the combined sample
# for the Bs->mu mu analysis
#
# Changed to expose the normalisation BF for the sake of the
# combination with CMS
#
# ------------------------------------------------------------

from errors import *
import alphaparam_spring13_2012 as a12
import alphaparam_summer13_2011 as a11
import BRparams as BF

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
JpsiE_trg = EVal(0.870,[0.003,0.024])  # Justine 20130704
JpsiE_trg = JpsiE_trg.compress_errors()
BuE_trg = JpsiE_trg
# Trigger efficiency for Bsmumu
BmmE_trg = EVal(0.924,[0.002,0.018])   # Justine 20130704
BmmE_trg = BmmE_trg.compress_errors()
# Trigger efficiency ratio for BuKpi/Bsmumu
BuRatE_trg = EVal(0.942,[0.004,0.023]) # Justine 20130704
BuRatE_trg = BuRatE_trg.compress_errors()


# Normalisation with Bu 
#  2011 
BuA11 = (a11.BuRatE_recsel * a11.BuRatE_trg) / a11.BuNcan
BuA11_fit = BuA11 / a11.BmmE_49006000  #alpha for fit
BuA11_mw  = BuA11 / a11.BmmE_mw        #Alpha for toys
#  2012 
BuA12 = (a12.BuRatE_recsel * a12.BuRatE_trg) / a12.BuNcan
BuA12_fit = BuA12 / a12.BmmE_49006000  #alpha for fit
BuA12_mw  = BuA12 / a12.BmmE_mw        #Alpha for toys


BuComb_noBF   = BuA11.invert() + BuA12.invert()
BuComb_noBF   = BuComb_noBF.invert()
#BuasComb = fdfs * BuComb * BF.BuBR

BuComb_fit_noBF= BuA11_fit.invert() + BuA12_fit.invert()
BuComb_fit_noBF= BuComb_fit_noBF.invert()
BuComb_mw_noBF = BuA11_mw.invert()  + BuA12_mw.invert()
BuComb_mw_noBF = BuComb_mw_noBF.invert()


# Normalisation with Bu using combined trigger efficiencies
#  2011 
BuA11_forComb = (a11.BuRatE_recsel) / a11.BuNcan
BuA11_forComb_fit = BuA11_forComb / a11.BmmE_49006000  #alpha for fit
BuA11_forComb_mw  = BuA11_forComb / a11.BmmE_mw        #Alpha for toys         
#  2012 
BuA12_forComb = (a12.BuRatE_recsel) / a12.BuNcan
BuA12_forComb_fit = BuA12_forComb / a12.BmmE_49006000  #alpha for fit
BuA12_forComb_mw  = BuA12_forComb / a12.BmmE_mw        #Alpha for toys         

BuComb_forComb_noBF   = ( BuRatE_trg ) / ( BuA11_forComb.invert() + BuA12_forComb.invert() )
#BuasComb_forComb = fdfs * BuComb_forComb * BF.BuBR

BuComb_forComb_fit_noBF= ( BuRatE_trg ) / ( BuA11_forComb_fit.invert() + BuA12_forComb_fit.invert() )
BuComb_forComb_mw_noBF = ( BuRatE_trg ) / ( BuA11_forComb_mw.invert()  + BuA12_forComb_mw.invert() )

print "   Normalisation for BuJpsik "
print "alpha 2011 ", BuA11, "  for N events = ", a11.BuNcan
print "alpha 2012 ", BuA12, "  for N events = ", a12.BuNcan
print "alpha Comb ", BuComb_noBF*BF.BuBR, "  for N events = ",  a11.BuNcan + a12.BuNcan
print "alpha Comb from Comb ", BuComb_forComb_noBF*BF.BuBR, "  for N events = ",  a11.BuNcan + a12.BuNcan


# Normalisation with Bd
#  2011 
BdA11 = (a11.BdRatE_recsel * a11.BdRatE_trg ) / a11.BdNcan
BdA11_fit = BdA11 / a11.BmmE_49006000  #alpha for fit
BdA11_mw  = BdA11 / a11.BmmE_mw        #alpha for toys         
#  2012 
BdA12 = (a12.BdRatE_recsel * a12.BdRatE_trg ) / a12.BdNcan
BdA12_fit = BdA12 / a12.BmmE_49006000  #alpha for fit
BdA12_mw  = BdA12 / a12.BmmE_mw        #alpha for toys         

BdComb_noBF   = BdA11.invert() + BdA12.invert()
BdComb_noBF   = BdComb_noBF.invert()
#BdasComb_noBF = fdfs * BdComb

BdComb_mw_noBF = BdA11_mw.invert()  + BdA12_mw.invert() 
BdComb_mw_noBF = BdComb_mw_noBF.invert() 
BdComb_fit_noBF= BdA11_fit.invert() + BdA12_fit.invert()
BdComb_fit_noBF= BdComb_fit_noBF.invert()

# Normalisation with Bd using combined trigger efficiencies
#  2011 
BdA11_forComb = (a11.BdRatE_recsel * a11.BdE_trg / BmmE_trg) / a11.BdNcan
BdA11_forComb_fit = BdA11_forComb / a11.BmmE_49006000  #alpha for fit
BdA11_forComb_mw  = BdA11_forComb / a11.BmmE_mw        #alpha for toys         
#  2012 
BdA12_forComb = (a12.BdRatE_recsel * a12.BdE_trg / BmmE_trg) / a12.BdNcan
BdA12_forComb_fit = BdA12_forComb / a12.BmmE_49006000  #alpha for fit
BdA12_forComb_mw  = BdA12_forComb / a12.BmmE_mw        #alpha for toys         

BdComb_forComb_noBF = BdA11_forComb.invert() + BdA12_forComb.invert()
BdComb_forComb_noBF = BdComb_forComb_noBF.invert()
#BdasComb_forComb = fdfs * BdComb_forComb

BdComb_forComb_mw_noBF = BdA11_forComb_mw.invert()  + BdA12_forComb_mw.invert() 
BdComb_forComb_mw_noBF = BdComb_forComb_mw_noBF.invert() 
BdComb_forComb_fit_noBF= BdA11_forComb_fit.invert() + BdA12_forComb_fit.invert()
BdComb_forComb_fit_noBF= BdComb_forComb_fit_noBF.invert()


print "   Normalisation for BdJpsik "
print "alpha 2011 ", BdA11, "  for N events = ", a11.BdNcan
print "alpha 2012 ", BdA12, "  for N events = ", a12.BdNcan
print "alpha Comb ", BdComb_noBF*BF.BdBR, "  for N events = ",  a11.BdNcan + a12.BdNcan
print "alpha Comb forComb", BdComb_forComb_noBF*BF.BdBR, "  for N events = ",  a11.BdNcan + a12.BdNcan

print '\n'*10

def averagealpha():
    print "Normalisation in the full mass range "
    BuComb = BuComb_noBF * BF.BuBR
    BdComb = BdComb_noBF * BF.BdBR
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
    print " Expected Bd events " , Bdmumu_BR/alpha
    print ''
    
    print "Normalisation for the fit "
    BuComb_fit = BuComb_fit_noBF * BF.BuBR
    BdComb_fit = BdComb_fit_noBF * BF.BdBR
    print " from Bu ", BuComb_fit
    print " from Bd ", BdComb_fit
    alpha_fit = BuComb_fit.average(BdComb_fit)
    alphas_fit = alpha_fit * fdfs
    print " Average alpha   = ", alpha_fit
    alpha_fit =     alpha_fit / TimeAcceptanceCorrBd
    print " Corrected for Bd time acc = " , alpha_fit
    print " Expected Bd events " , Bdmumu_BR/alpha_fit
    print " Average alpha_s = ", alphas_fit
    alphas_fit = alphas_fit / TimeAcceptanceCorrBs
    print " Corrected for Bs time acc = " , alphas_fit
    print " Expected Bs events " , Bsmumu_BR/alphas_fit
    print " Expected Bd events " , Bdmumu_BR/alpha_fit
    print ''
    
    print "Normalisation for the toys "
    BuComb_mw = BuComb_mw_noBF * BF.BuBR
    BdComb_mw = BdComb_mw_noBF * BF.BdBR
    print " from Bu ", BuComb_mw
    print " from Bd ", BdComb_mw
    alpha_mw = BuComb_mw.average(BdComb_mw)
    alphas_mw = fdfs* alpha_mw
    print " Average alpha (mw)  = ", alpha_mw
    print " Average alphas (mw)  = ", alphas_mw
    print " Corrected for time acceptance :"
    alpha_mw = alpha_mw / TimeAcceptanceCorrBd
    alphas_mw = alphas_mw / TimeAcceptanceCorrBs
    print " Average alpha (mw)  = ", alpha_mw
    print " Average alphas (mw)  = ", alphas_mw
    print " Expected Bs events " , Bsmumu_BR/alphas_mw
    print " Expected Bd events " , Bdmumu_BR/alpha_mw
    return alpha, alphas, alpha_mw, alphas_mw


averagealpha()


#creating the string for Ale

BF1   = [0, val(BF.BdBR), 'BdKpi_BF']
sBF1  = [1, err(BF.BdBR), 'BdKpi_BF_Err']
BF2   = [2, val(BF.BuBR), 'BuJpsiK_BF']
sBF2  = [3, err(BF.BuBR), 'BuJpsiK_BFErr']

N1  =   [4, val(BdComb_fit_noBF), 'NormKPi_fullmass_noBF']
sN1 =   [5, err(BdComb_fit_noBF), 'NormKPi_fullmass_noBFErr']
N2  =   [6, val(BuComb_fit_noBF), 'NormBu_fullmass_noBF']
sN2 =   [7, err(BuComb_fit_noBF), 'NormBu_fullmass_noBFErr']

fdfs  = [8, val(fdfs), 'fsfd']
TimeCorrBd = [9, val(TimeAcceptanceCorrBd), 'TimeAcceptanceCorrBd']
TimeCorrBs = [9, val(TimeAcceptanceCorrBs), 'TimeAcceptanceCorrBs']

inputs = {
'BF1'   : BF1,
'sBF1'  : sBF1,
'BF2'   : BF2,
'sBF2'  : sBF2,
'N1'  : N1,
'sN1' : sN1,
'N2'  : N2,
'sN2' : sN2,
'fdfs': fdfs,
'TimeCorrBd' : TimeCorrBd,
'TimeCorrBs' : TimeCorrBs
}
    

def replacing(string_, inputs):
    
    TFormula = string_
    roo_arg = ''
    eval_string = string_
    
    for key in inputs.keys():
        TFormula = TFormula.replace(' '+key+' ',' @'+str(inputs[key][0])+' ')
    for key in inputs.keys():
        eval_string = eval_string.replace(' '+key+' ',' '+str(inputs[key][1])+' ')
    for key in inputs.keys():
        if ' '+key+' ' in string_:
            roo_arg += '@'+str(inputs[key][0])+' : '+inputs[key][2]+'\n'
    return TFormula, roo_arg, eval_string


def compute_and_print(inputs, channel='Bs'):

    if channel == 'Bs':
        string_  = '( N1 * BF1 * ( BF2 * BF2 * sN2 * sN2 + N2 * N2 * sBF2 * sBF2 ) '
        string_ += '+ N2 * BF2 * ( BF1 * BF1 * sN1 * sN1 + N1 * N1 * sBF1 * sBF1 ) ) '
        string_ += ' / '
        string_ += '( BF1 * BF1 * sN1 * sN1 + N1 * N1 * sBF1 * sBF1 '
        string_ += '+ BF2 * BF2 * sN2 * sN2 + N2 * N2 * sBF2 * sBF2 )'
        string_ += ' * fdfs / TimeCorrBs '
    elif channel == 'Bd':
        string_  = '( N1 * BF1 * ( BF2 * BF2 * sN2 * sN2 + N2 * N2 * sBF2 * sBF2 ) '
        string_ += '+ N2 * BF2 * ( BF1 * BF1 * sN1 * sN1 + N1 * N1 * sBF1 * sBF1 ) ) '
        string_ += ' / '
        string_ += '( BF1 * BF1 * sN1 * sN1 + N1 * N1 * sBF1 * sBF1 '
        string_ += '+ BF2 * BF2 * sN2 * sN2 + N2 * N2 * sBF2 * sBF2 ) '
        string_ += ' / TimeCorrBd '

    
    TFormula, roo_arg, eval_string = replacing(string_, inputs)

    print ''
    print 'Channel ', channel
    print 'The TFormula is:'
    print TFormula
    print 'with the following arguemnts:'
    print roo_arg
    print 'testing:'
    print eval_string + ' = ', eval(eval_string)
    print ''

compute_and_print(inputs, channel='Bs')
compute_and_print(inputs, channel='Bd')
