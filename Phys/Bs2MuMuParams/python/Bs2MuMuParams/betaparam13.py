#------------------------------------------------------------
# Beta parameters: 
# Normalisation of exclusive backgrounds
# for the Bs->mu mu analysis 
# ------------------------------------------------------------
from errors import *
import alphaparam_spring13_2012 as a12
import alphaparam_summer13_2011 as a11
import alphaparam_summer13 as aComb
from texlper import * 

# Luminosity and cross-section used only as cross-check
luminosity = EVal(0.970,0.055)  # in 1/fb
sigma_bb   = EVal( 284e9, sqrt(20e9**2 + 49e9**2)) #in fb 

# b hadronisation fractions from PDG
# fd/fs is instead imported from alphaparam 
#f_lb  = EVal(0.093, 0.016)
#f_bs  = EVal(0.105, 0.096)
# f_bd  = EVal(0.401, 0.008)

factor2 = EVal(2.,0.) #just to simplify manipulation with EVal later
def fLoverfu(pt):
    ptdepa = EVal(0.404,sqrt(0.017**2 + 0.027**2+ 0.105**2))
    ptdepb = EVal(0.031, sqrt(0.004**2+ 0.003**2))
    flbr =  (ptdepa *(EVal(1,0.)-ptdepb* pt))
    return flbr
 
def flambdab(pt):
    # fu +fd +fs +fL = 1
    # input: measured fs/fd
    #        measured r = fL /(fu+fd) 
    #        fu = fd
    # => fLambda = 1/(1/r + (fs/fd)+1/(2r) +1)
    flbr = fLoverfu(pt)
    part1 = flbr.invert()
    part2 =  (flbr.invert()) / EVal(2.,0.)
    part3 =  a12.fsfd * part2
    flambdab = ( part3 + part1+EVal(1,0.)).invert()
    print "Using flambdab =", flambdab
    return flambdab

f_lb = flambdab(5)

def fu_fromdata():
    # fu +fd +fs +fL = 1
    # input: measured fs/fd
    #        measured r = fL /(fu+fd) 
    #        fu = fd
    # => fu= 1/(2+ fs/fd +2r)
    fsfd =  a12.fsfd
    # assume average pt of the Lambda at about 5 Gev
    flbr = fLoverfu(5)
    fu = EVal(2,0) + fsfd + EVal(2,0)*flbr
    fu = fu.invert()
    return fu

f_bu  = fu_fromdata()

def beta(mod):
    BuNcan =  mod.BuNcan
    BuE_recsel =  mod.BuE_recsel
    BuE_trg =  mod.BuE_trg
    BuBR =  mod.BuBR
    fsfd = mod.fsfd
    fu = fu_fromdata()
    ####
    # N = lumi * cross * 2 * f * BR * eff 
    ###
    # Total efficiency for B+ -> Jpsi K+ 
    BuE_tot = BuE_recsel * BuE_trg

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
    beta_lambda = beta *fLoverfu(5)*2  # directly from the measurement
    print "$\\beta_{baryon}$ " , tex(beta_lambda)
    print beta_lambda
    print "Beta bb i.e. beta/f_bu to be used for bc"
    beta_bb = beta/f_bu
    print "$\\beta_{bb}$ ", tex(beta_bb) 
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
    return beta, beta_s, beta_lambda, beta_bb


def betaComb():
    print " ======= Beta Combined ======== " 
    Bu11 =  a11.BuNcan / ( a11.BuE_recsel * a11.BuE_trg )
    print "Bu11 (eff corrected yield) = ", Bu11
    Bu12 =  a12.BuNcan / ( a12.BuE_recsel * a12.BuE_trg )
    print "Bu12 (eff corrected yield) = ", Bu12
    BuComb = Bu11 + Bu12
    print "BuComb = Bu11 + Bu12 = ", BuComb
    
    BuBR =  a12.BuBR
    fsfd = a12.fsfd
    fu = fu_fromdata()
    ####
    # N = lumi * cross * 2 * f * BR * eff 
    ###
    # Total efficiency for B+ -> Jpsi K+ 
  

    # Total corrected yield: beta 
    print " --------- Beta --------" 
    beta = (Bu11 + Bu12)/ BuBR 
    print "$\\beta$  = ", tex(beta)
    print beta
    beta_s = fsfd * beta
    print "$\\beta_s$ = ",  tex(beta_s)
    print beta_s
    beta_lambda = beta *fLoverfu(5)*2  # directly from the measurement
    print "$\\beta_{baryon}$ " , tex(beta_lambda)
    print beta_lambda
    print "Beta bb i.e. beta/f_bu to be used for bc"
    beta_bb = beta/f_bu
    print "$\\beta_{bb}$ ", tex(beta_bb) 
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
    return beta, beta_s, beta_lambda, beta_bb

def bkgNormNoBR():
    Bu11 =  a11.BuNcan / ( a11.BuE_recsel * a11.BuE_trg )
    Bu12 =  a12.BuNcan / ( a12.BuE_recsel * a12.BuE_trg )
    BuComb = Bu11 + Bu12
    return BuComb



def beta2012():
    print " ========= Beta 2012 ========= " 
    return beta(a12)

def beta2011():
    print " ========= Beta 2011 ========= " 
    return beta(a11)


def printBeta():
    outfile = open("BetaParameters13_2011.txt","w")
    beta, betas, beta_lambda, beta_bb = beta2011()
    outfile.write("beta        "+beta.__str__()+"\n")
    outfile.write("betas       "+betas.__str__()+"\n")
    outfile.write("betabaryon  "+beta_lambda.__str__()+"\n")
    outfile.write("betabb      "+beta_bb.__str__()+"\n")
    outfile.close()
    outfile = open("BetaParameters13_2012.txt","w")
    beta, betas, beta_lambda, beta_bb = beta2012()
    outfile.write("beta        "+beta.__str__()+"\n")
    outfile.write("betas       "+betas.__str__()+"\n")
    outfile.write("betabaryon  "+beta_lambda.__str__()+"\n")
    outfile.write("betabb      "+beta_bb.__str__()+"\n")
    outfile.close()
    outfile = open("BetaParameters13_Comb.txt","w")
    beta, betas, beta_lambda, beta_bb = betaComb()
    outfile.write("beta        "+beta.__str__()+"\n")
    outfile.write("betas       "+betas.__str__()+"\n")
    outfile.write("betabaryon  "+beta_lambda.__str__()+"\n")
    outfile.write("betabb      "+beta_bb.__str__()+"\n")
    outfile.close()
    

