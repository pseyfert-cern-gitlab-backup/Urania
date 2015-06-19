#------------------------------------------------------------
# Beta parameters: 
# Normalisation of exclusive backgrounds
# for the Bs->mu mu analysis 
# ------------------------------------------------------------
from errors import *
import alphaparam_Autumn2012
import alphaparam_1fb
from texlper import * 

# Luminosity and cross-section used only as cross-check
luminosity = EVal(1.109,0.055)  # in 1/fb
sigma_bb   = EVal( 284e9, sqrt(20e9**2 + 49e9**2)) #in fb 

# b hadronisation fractions from PDG
# fd/fs is instead imported from alphaparam 
#f_lb  = EVal(0.093, 0.016)
f_bs  = EVal(0.105, 0.096)
f_bd  = EVal(0.401, 0.008)
f_bu  = f_bd
factor2 = EVal(2.,0.) #just to simplify manipulation with EVal later

def flambdab(pt):
    ptdepa = EVal(0.404,sqrt(0.017**2 + 0.027**2+ 0.105**2))
    ptdepb = EVal(0.031, sqrt(0.004**2+ 0.003**2))
    flbr =  (ptdepa *(EVal(1,0.)-ptdepb* pt))
    part1 = flbr.invert()
    part2 =  (flbr.invert()) / EVal(2.,0.)
    part3 =  alphaparam_Autumn2012.fsfd * part2
    flambdab = ( part3 + part1+EVal(1,0.)).invert()
#    print "Using flambdab =", flambdab
    return flambdab

f_lb = flambdab(5)

def beta(mod):
    BuNcan =  mod.BuNcan
    BuE_rec =  mod.BuE_rec
    BuE_sel =  mod.BuE_sel
    BuE_trg =  mod.BuE_trg
    BuBR =  mod.BuBR
    fsfd = mod.fsfd
    ####
    # N = lumi * cross * 2 * f * BR * eff 
    ###
    # Total efficiency for B+ -> Jpsi K+ 
    BuE_tot = BuE_rec * BuE_sel * BuE_trg

    # Total corrected yield: beta 
    print " --------- Beta --------" 
    print "Bu yield " , BuNcan 
    print "Bu total efficiency ", BuE_tot
    print "Bu total BR ", BuBR
    beta = BuNcan / ( BuBR * BuE_tot)
    print "$\\beta$  = ", tex(beta)
    print beta
    beta_s = fsfd * beta
    print "$\\beta_s$ = ",  tex(beta_s)
    print beta_s
    beta_lambda = f_lb* beta /f_bu
    print "$\\beta_{baryon}$ " , tex(beta_lambda)
    print beta_lambda
    
    print " -------- Cross-checks ----------" 
    # First cross-check 
    print " Beta from external measurements " 
    print "Luminosity " ,luminosity
    print "Cross-section ", sigma_bb 
    print "f_bu ", f_bu 
    betaold = luminosity * sigma_bb * factor2 * f_bu 
    print "old beta ", betaold 
    print "    ---    " 
    print "Ext. lumi assuming 7TeV cross-section " 
    print "cross (fb)  = ", sigma_bb
    print "lumi  (fb^-1) = ", beta / (factor2 * sigma_bb * f_bu ) 
    print "    --- " 
    print "Ext. cross-ection assuming lumi " 
    print "lumi (fb^-1)  = ", luminosity
    print "cross (fb) = ", beta / (factor2* luminosity *f_bu)  
    return beta, beta_s, beta_lambda


def beta2012():
    return beta(alphaparam_Autumn2012)

def beta2011():
    return beta(alphaparam_1fb)
