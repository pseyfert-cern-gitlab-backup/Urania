###############################################################################
# Compute DeltaPhis = shift on phis due to penguin pollution
# and its experimental and theoretical uncertainties
# using Fleischer paper on penguins, arXiv:0810.4248
#   !!!!!!! MATHEMATICA IS MANDATORY for this program to work !!!!!!!!!!!!!
#
# Inputs = the 3 polarizations fraction (para, perp, zero)
#           for JpsiK* and JpsiPhi
#          gamma angle, epsilon= lambda**2/(1-lambda**2)
#          Af.  
#
# 1) First compute Hf with the following inputs:
#    BR and ploarization fractions for Bs->JpsiPhi and Bs->JpsiK*
# 2) Using Hf and Af, solve for thetaf, using mathematica (batch1.m)
# 3) Compute af = f(theta)
# 4) Compute tan Delta phis_f = f(af,thetaf)
#
# Everywhere, index f is for polarization fraction
# f = 1 means "zero" = longitudinal"
# f = 2 means "parallel"
# f = 3 means "perpendicular"
#   index f=0 is not used
# index i=1,2,3,4 is for the 4 mathematical solutions to the problem
#   index i=0 is not used
# index j =1,2 is for the 2 additional solutions for af. 
#
# Arbitrary choice: only display solutions where all 3 polarizations give
#  physical results. 
#
# TOBEDONE:
# - remove duplication of code: gamma and eps are here and in batch1.m
#
# Olivier Leroy, Walaa Kanso (CPPM), Jan 2013
###############################################################################


from math import *
import os
from penguin_inputs import * # gamma, eps constants
from Urania.Mathematica import *


###############################################################################
# Compute af  Eq 43 of Fleischer
#  returns two possible values
###############################################################################
def compute_a(Hf=0., thetaf=0.):
    Vf = (1-Hf)/(1-eps**2*Hf)
    Uf =  ((1+eps*Hf)/(1-eps**2*Hf))*cos(float(thetaf))*cos(gamma) 
    delta =  Uf**2-Vf
    a = [0,0,0]
    if delta>=0: a[1] = Uf + sqrt(delta);  a[2] = Uf - sqrt(delta) 
      # a = Uf - sqrt(delta)  
    #print "Here, U^2-V should be >0 ", Uf**2-Vf, a
    return a
###############################################################################



###############################################################################
# Compute uncertainties on a, theta, Delta(phis) and other
# See CheckDerivative.nb and CheckDerivative2.nb for details
# Take into account correlation between a and theta
#  assumes zero correlation between H and A
# Inputs = a
#          f = ploarization index
#          i = solution index 1-4
#          j = index solution 1,2 (a)
###############################################################################
def compute_err(f,i,j):
    # Simplify the notation:
    a = af[f][i][j]
    # Compute all partial derivatives:
    dHda[f][i] = -(((1 + a**2 - 2*a* cosg*cos(thetaf[f][i]))*(2*a*eps**2 + 2*cosg*eps*cos(thetaf[f][i])))/ \
                   (1 + a**2 * eps**2 + 2*a*cosg*eps*cos(thetaf[f][i]))**2) + \
                   (2*a - 2*cosg*cos(thetaf[f][i]))/(1 + a**2 * eps**2 + 2*a*cosg*eps*cos(thetaf[f][i]))
    
    dHdtheta[f][i] = (2*a*cosg* eps* (1 + a**2 - 2 *a *cosg *cos(thetaf[f][i])) *sin(thetaf[f][i]))/ \
                     (1 + a**2 * eps**2 + 2 *a *cosg *eps *cos(thetaf[f][i]))**2 + \
                     (2*a*cosg*sin(thetaf[f][i]))/(1 + a**2 * eps**2 + 2*a *cosg *eps*cos(thetaf[f][i]))
    
    dAda[f][i] = -(2 *a *sing *(2 *a - 2 *cosg *cos(thetaf[f][i])) *sin(thetaf[f][i]))/ \
                 (1 + a**2 - 2*a *cosg *cos(thetaf[f][i]))**2 + \
                 (2 *sing *sin(thetaf[f][i]))/(1 + a**2 - 2 *a *cosg *cos(thetaf[f][i]))


    dAdtheta[f][i] = (2 *a *sing *cos(thetaf[f][i]))/(1 + a**2 - 2* a *cosg *cos(thetaf[f][i])) \
                     - (4 *a**2 *cosg *sing *sin(thetaf[f][i])**2)/(1 + a**2 - 2 *a *cosg *cos(thetaf[f][i]))**2


    # First experimental uncertainties
    # See mathematica macro checkDerivative2.nb
    denom = abs(dAdtheta[f][i] * dHda[f][i] - dAda[f][i] * dHdtheta[f][i])
    aux1  = dAda[f][i]**2     * dH[f][i]**2 + dA[f][i]**2 * dHda[f][i]**2      
    aux2  = dAdtheta[f][i]**2 * dH[f][i]**2 + dA[f][i]**2 * dHdtheta[f][i]**2  
    aux3  = dAda[f][i]*dAdtheta[f][i] * dH[f][i]**2 + dA[f][i]**2 * dHda[f][i]*dHdtheta[f][i]  

    Vatheta_exp = 0.

    if denom!=0:
      dtheta[f][i][j] =  sqrt(aux1)/denom
      da[f][i][j] =  sqrt(aux2)/denom 
      # covariance between a and theta
      Vatheta_exp = aux3/(denom**2)
    
    print "Exp error on a = ", f,i,j, da[f][i][j]
    print "Exp error on theta = ", f,i,j, dtheta[f][i][j]
    print "Vatheta_exp = ", Vatheta_exp

    print "debug dHda = ", f,i,j, dHda[f][i]
    print "debug dHdtheta = ", f,i,j, dHdtheta[f][i]
    print "debug dAda = ", f,i,j, dAda[f][i]
    print "debug dAdtheta = ", f,i,j, dAdtheta[f][i]
    print "aux1  = ",  aux1
    print "denom = ",  denom

    # Now compute exp uncertainty on tan(DeltaPhi):

    dPHIda[f][i] = (2* a *eps**2 *sin2g + 2* eps *sing *cos(thetaf[f][i]))/( 1 + a**2 *cos2g *eps**2 +   2 *a *cosg *eps* cos(thetaf[f][i])) - ((2 *a* cos2g *eps**2 +     2* cosg* eps* cos(thetaf[f][i]))* (a**2 *eps**2 *sin2g +     2 *a *eps *sing* cos(thetaf[f][i])))/(1 + a**2* cos2g* eps**2 +    2 *a *cosg* eps* cos(thetaf[f][i]))**2

    dPHIdtheta[f][i] = -((2* a *eps *sing *sin(thetaf[f][i]))/(  1 + a**2* cos2g* eps**2 + 2 *a *cosg *eps* cos(thetaf[f][i]))) + ( 2 *a *cosg *eps *(a**2 *eps**2 *sin2g + 2 *a *eps *sing* cos(thetaf[f][i])) *sin(thetaf[f][i]))/(1 + a**2 *cos2g *eps**2 + 2 *a *cosg* eps *cos(thetaf[f][i]))**2
    
    print "debug dDeltathanPhi/da = ", f,i,j,dPHIda[f][i]
    print "debug dDeltathanPhi/dtheta = ", f,i,j, dPHIdtheta[f][i]

    # Simple error propagation:
#bug until 26 april 2013:
#    e_dphi[f][i][j] = sqrt(dPHIda[f][i]**2*dtheta[f][i][j]**2 + dPHIdtheta[f][i]**2*da[f][i][j]**2 \
    e_dphi[f][i][j] = sqrt(dPHIda[f][i]**2*da[f][i][j]**2 + dPHIdtheta[f][i]**2*dtheta[f][i][j]**2 \
                           +2*dPHIda[f][i]*dPHIdtheta[f][i]*Vatheta_exp )
    # for polarization f and solution i: 
    print "Exp error on Delta phi_s = ", f,i,j, e_dphi[f][i][j]


    # Second, theoretical uncertainties
    # See mathematica macro checkDerivative2.nb
    auxt1 = dAda[f][i]**2     * e_H_theo[f]**2 + e_A_theo[f]**2 * dHda[f][i]**2
    auxt2 = dAdtheta[f][i]**2 * e_H_theo[f]**2 + e_A_theo[f]**2 * dHdtheta[f][i]**2
    auxt3 = dAda[f][i]*dAdtheta[f][i] * e_H_theo[f]**2 + e_A_theo[f]**2 * dHda[f][i]*dHdtheta[f][i]  

    Vatheta_theo = 0.

    if denom!=0:
      dthetat[f][i][j] =  sqrt(auxt1)/denom
      dat[f][i][j] =  sqrt(auxt2)/denom 
      # covariance between a and theta
      Vatheta_theo = auxt3/(denom**2)

    print " DDDDDDDDDDDDDEBUG a, theta = ", a, thetaf[f][i]
    print "Theo  error on a = ", f,i, j,dat[f][i][j]
    print "Theo error on theta = ", f,i, j, dthetat[f][i][j]
    print "  Vatheta_theo = ", Vatheta_theo
    print " dH theo = ",  e_H_theo[f]
    print " dA theo = ",  e_A_theo[f]
    print " auxt1 = ",  auxt1

    
    # Now compute theo uncertainty on tan(DeltaPhi):

# bug (until 26 april)
#    e_dphit[f][i][j] = sqrt(dPHIda[f][i]**2*dthetat[f][i][j]**2 + dPHIdtheta[f][i]**2*dat[f][i][j]**2 +\
    e_dphit[f][i][j] = sqrt(dPHIda[f][i]**2*dat[f][i][j]**2 + dPHIdtheta[f][i]**2*dthetat[f][i][j]**2 +\
                           +2*dPHIda[f][i]*dPHIdtheta[f][i]*Vatheta_theo )
    # for polarization f and solution i: 
    print "Theo error on Delta phi_s = ", f,i, e_dphit[f][i][j]


    return   
###############################################################################





###############################################
# Global variables
###############################################
# constant now taken in seprate file: penguin_inputs.py
# !!! WARNING gamma is also hard-coded in batch1.m !!!
#gamma = 67.1*pi/180. # world average, CKMfitter
cosg  = cos(gamma)
sing  = sin(gamma)
cos2g = cos(2*gamma)
sin2g = sin(2*gamma)
# !!! WARNING eps is also hard-coded in batch1.m !!!
#eps   = 0.053 # = lambda**2/(1-lambda**2)

#Diego:
#gamma =  1.1344640137963142
#eps = 0.053424463819589013


########################################
#  SU3 breaking factors
########################################
#AprimeOverApar=0.70  # Eq 56
#AprimeOverApar=0.53  # Eq 56, the true value is 0.70. choose 0.53 in order to finds real value for A. (shifted by half a sigma)

# SU3 breaking factors index 0 is not used
# order is          0, parallel, perp
AprimeOverA = [0, 0.42, 0.53, 0.38]
AprimeOverA = [0, 0.42, 0.70, 0.38]  # historical values by Fleischer leads to unphysical results for f=2
e_AprimeOverA = [0, 0.27, 0.29, 0.16] 

# Perfect SU3:
#AprimeOverA = [0., 1., 1., 1.]
#e_AprimeOverA = [0., 0., 0., 0.] 



###################### Bs->JpsiPhi polarization fractions
# |A0(0)|^2
#fJpsiPhi0 = .523  # LHCb-CONF-2012-002, JpsiPhi Moriond 2012
#e_fJpsiPhi0 = .025  # sqrt(.007**2+.024**2) syst included

# |Aper(0)|^2
#fJpsiPhiper = .246  # LHCb-CONF-2012-002, JpsiPhi Moriond 2012
#e_fJpsiPhiper = .0164  # sqrt(.01**2+0.013**2) syst included

# |Apar(0)|^2
#fJpsiPhipar = 1-fJpsiPhi0-fJpsiPhiper # = 0.231 normalization checked: OK
#e_fJpsiPhipar = 0.03 # sqrt(.025**2+.0164**2) assumming no correl
#e_fJpsiPhipar = 0.0086 # sqrt(.025**2+.0164**2-2*e_fJpsiPhi0*e_fJpsiPhiper) assuming 100% correl
#e_fJpsiPhipar = 0.0214 # sqrt(.025**2+.0164**2-2*0.53*e_fJpsiPhi0*e_fJpsiPhiper) correl given in the note=-0.53

# relative uncertainties:
# f0   0.0478
# fper 0.0667
# fpar 0.0926


# Bs->JpsiPhi polarization fractions, LHCb-PAPER-2013-002
# order is          0, parallel, perp
fJpsiPhi =  [0, 0.521, 0,      0.249]
e_fJpsiPhi = [0, 0.012, 0.0214, 0.011]
# err_R0 = sqrt(0.006**2+0.010**2) # = 0.0116619
# err_Rperp = sqrt(0.009**2+0.006**2) # = 0.011
# old CONF-2012 moriond below:

#fJpsiPhi =  [0, 0.523, 0,      0.246]
#e_fJpsiPhi = [0, 0.025, 0.0214, 0.0164]
fJpsiPhi[2] = 1-fJpsiPhi[1]-fJpsiPhi[3]




######################  Bs->JpsiK* polarization fractions
# Diego, 6 dec 2012, stat only, 1fb-1 2011 + 1fb-1 2012
#fJpsiKst0 = .57  # 
#e_fJpsiKst0 = 0.03 # 

#fJpsiKstpar = .15  # 
#e_fJpsiKstpar = 0.03 # 

#fJpsiKstper = 1.-fJpsiKst0-fJpsiKstpar # = 0.31
#e_fJpsiKstper = 0.086464 # = sqrt(0.07933**2+0.092164**2-2*0.5*e_fJpsiKst0*e_fJpsiKstpar)  # assuming 50% correlation, like in JpsiPhi... value NOT given in the paper. 
#e_fJpsiKstper = sqrt(e_fJpsiKst0**2+e_fJpsiKstpar**2-2*corelA0Apar*e_fJpsiKst0*e_fJpsiKstpar)  # private com Juan CDS corel = 0.439 = excat diego 370invpb paper
# = 0.003

# 25 2013 value 3fb-1, Walaa:
fJpsiKst = [0, 0.55, 0.18, 0]
e_fJpsiKst = [0, 0.025, 0.027, 0]
fJpsiKst[3] = 1.-fJpsiKst[1]-fJpsiKst[2]
corelA0Apar = 0.147 #  corel between coeff 18 and 19 (A0 and Appar), taken from 2012 fit OL
e_fJpsiKst[3] = sqrt(e_fJpsiKst[1]**2+e_fJpsiKst[2]**2-2*corelA0Apar*e_fJpsiKst[1]*e_fJpsiKst[2]) 

# relative uncertainties:
# f0   0.158
# fper 0.279
# fpar 0.493

# M2 values:
# ----------
## fJpsiKst =   [0, 0.503,   0.187, 0]
## e_fJpsiKst = [0, 0.05107, 0.05874, 0]
## fJpsiKst[3] = 1.-fJpsiKst[1]-fJpsiKst[2]
## corelA0Apar = 0.439 #  corel between coeff 18 and 19 (A0 and Appar), taken from 2012 fit OL
## e_fJpsiKst[3] = sqrt(e_fJpsiKst[1]**2+e_fJpsiKst[2]**2-2*corelA0Apar*e_fJpsiKst[1]*e_fJpsiKst[2]) 



################ Branching ratios
BRJpsiPhi = 1.09e-3 # PDG online Dec 2012
e_BRJpsiPhi = 0.255e-3

BRJpsiKst = 4.42e-5  # LHCb-PAPER-2012-014 
#e_BRJpsiKst = 0.918e-5  # sqrt(.45**2+.8**2) syst included = exact Diego
e_BRJpsiKst = 0.84558e-5  # sqrt((.45/sqrt(5.4))**2+.8**2) syst included. stat scaled to 2fb-1  (2000/370=5.4)

# M2 values:
# ----------
## BRJpsiPhi = 1.4e-3 # PDG online Dec 2012
## e_BRJpsiPhi = 0.5e-3



########################################
# AD = direct CPV
########################################
#A0 = -0.031  # Diego, dec 2012
#e_A0 = 0.042


# Direct CP violation! 
# fev 2013 values: 
# order is      0, parallel, perp
A        = [0, -0.032, -0.082, 0.030]
e_A      = [0, 0.055, 0.154, 0.110]

# Zero theoretical uncertainty on ACP: 
e_A_theo = [0,0,0,0]

# M2 values: 
# ----------           
## A        = [0, 0.16, 0.16, 0.16]
## e_A      = [0, 0.12, 0.12, 0.12]




# end of numerical inputs
##############################################################################################"




# For the 3 polarization f, define H, its theo and exp uncertainties: 
print " Using as inputs gamma, lambda, BR and polarizations fraction of JpsiPhi and JpsiK*, "
print " Compute H_f" 

H        = [0,0,0,0]
e_H_exp  = [0,0,0,0]
e_H_theo = [0,0,0,0]
for f in range(1,4):
    H[f] = (1/eps)*(1./AprimeOverA[f]) * fJpsiKst[f]*BRJpsiKst /(fJpsiPhi[f]*BRJpsiPhi)

    # Theoretical error on Hf:
    e_H_theo[f] = (fJpsiKst[f]*BRJpsiKst/(eps*fJpsiPhi[f]*BRJpsiPhi*AprimeOverA[f]**2))*e_AprimeOverA[f]

    # Experimental error on Hf: 
    e_H_exp[f] = sqrt( (BRJpsiKst/(eps*fJpsiPhi[f]*BRJpsiPhi*AprimeOverA[f]))**2*e_fJpsiKst[f]**2 + (fJpsiKst[f]/(eps*fJpsiPhi[f]*BRJpsiPhi*AprimeOverA[f]))**2*e_BRJpsiKst**2 + (fJpsiKst[f]*BRJpsiKst/(eps*fJpsiPhi[f]**2*BRJpsiPhi*AprimeOverA[f]))**2*e_fJpsiPhi[f]**2 + (fJpsiKst[f]*BRJpsiKst/(eps*fJpsiPhi[f]*BRJpsiPhi**2*AprimeOverA[f]))**2*e_BRJpsiPhi**2 )

    print " H_",f," = ", H[f], "+/-", e_H_exp[f], "(exp) +/-",e_H_theo[f], "(theo)"


    
# Overwrite all Hf to one unique value for debug: 
#H        = [0,0.92,0.92,0.92]
#e_H_exp  = [0,0,0,0]




######################################################################
# Now use mathematica to find theta value, with above H and A in input
#####################################################################

print " Experimental input for Af: "

for f in range(1,4):
  print " A_", f, " = ", A[f], "+/-", e_A[f]

print " Now use mathematica to find theta value, with above H and A in input "

# mathematica gives 4 values for theta, whether we solve:
# 1) NSolve[{U + Sqrt[U^2 - V] - (Uprime + Sqrt[Uprime^2 - Vprime]) == 0}
# or
# 2) NSolve[{U + Sqrt[U^2 - V] - (Uprime - Sqrt[Uprime^2 - Vprime]) == 0} 
# or
# 3) NSolve[{U - Sqrt[U^2 - V] - (Uprime + Sqrt[Uprime^2 - Vprime]) == 0} 
# or
# 4) NSolve[{U - Sqrt[U^2 - V] - (Uprime - Sqrt[Uprime^2 - Vprime]) == 0} 
#



# f is the polarization index, from 1 to 3
# i is the "solution index", from 1 to 4
# j is an extra solution index only for a, from 1 to 2
thetaf = [ [0 for i in range(5)] for f in range(4)]
af     = [ [[0 for j in range(3)] for i in range(5)] for f in range(4) ]


Uf  = [ [0 for i in range(5)] for f in range(4)]
Vf  = [0 for i in range(4)]

tanphi  = [ [[0 for j in range(3)] for i in range(5)] for f in range(4) ]


# flag un-physical solutions
flagf  = [ [ 0 for i in range(5)] for f in range(4) ]
flag1 = [ 0 for i in range(5)]
flag2 = [ 0 for i in range(5)]
flagn = [ [0 for j in range(3)]  for i in range(5)]
flagall  = [ [[0 for j in range(3)] for i in range(5)] for f in range(4) ]


# Transmit Hf and Af to mathematica, to solve for theta
for f in range(1,4):
    print " --------------- polarization = ", f 
    myoutfile = open("HandA.txt", "r+")
    myoutfile.write(str(H[f])+" ")
    myoutfile.write(str(A[f]))


    # Run mathematica and find theta
    mathematica_script("batch1.m")
    myfile = open("myOutput.txt","r")


    i=1
    for line in myfile.readlines():
        # flag immediately bad solutions:
        if len(line.rstrip())==0: print " flagf = 1 (f,i)   ",f,i ; flagf[f][i]=1; continue 
        thetaf[f][i] = float(line.rstrip())
        print "theta ",f,i," = ", thetaf[f][i] 
        i +=1







# Now recompute a (even if already done in mathematica)
# We can have two a [j=1,2] for a unique theta: \pm \sqrt(Uf**2-Vf)

for f in range(1,4):
    for i in range(1,5):
        for j in range(1,3):
          # Ignore non-physical solutions
          if flagf[f][i]!=0: continue 
          af[f][i][j] = compute_a(H[f], thetaf[f][i])[j]
          # Flag bad solutions: 
          if af[f][i][j]<=0: flagall[f][i][j]=1
          print " af, thetaf f, i, j,        ", f,i,j, " = ", af[f][i][j], thetaf[f][i], flagall[f][i][j]





# check whether the discriminant is positive. If not, flag a bad solution, i.e. flag = 1
#  could also be done above, in compute_a function. 
#for f in range(1,4):
#    for i in range(1,5):
#        Uf[f][i] = ((1+eps*H[f])/(1-eps**2*H[f]))*cos(thetaf[f][i])*cos(gamma)
#        Vf = (1-H[f])/(1-eps**2*H[f])
#        test =  Uf[f][i]**2-Vf**2
#        print "U^2-V should be >0 ", f,i, test
#        if test<0: flag[i]=1




# Eq 38 of Fleischer's paper
# 2*4 solutions for each tan Delta phi_f (i from 1 to 4, j from 1 to 2):
print " tan Delta phi_f solutions "

for f in range(1,4):
    for i in range(1,5):
        for j in range(1,3):
            if flagall[f][i][j]==0: 
              tanphi[f][i][j]   = (2*eps*af[f][i][j]*cos(thetaf[f][i])*sin(gamma)+eps**2*af[f][i][j]**2*sin(2*gamma))/ \
                                  (1+2*eps*af[f][i][j]*cos(thetaf[f][i])*cos(gamma)+eps**2*af[f][i][j]**2*cos(2*gamma))
              print "per ploarization Delta phis (f,i,j) = ", f, i, j, atan(tanphi[f][i][j])


# Naive average over the 3 JpsiK* polarization fractions 
# OK, only if there exist a physical solution for the 3 f
dphi = [ [0 for j in range(3)]  for i in range(5)] 

i=0
for i in range(1,5):
    for j in range(1,3):
        # all 3 polarizations should be available to average them:
        if flagall[1][i][j]+flagall[2][i][j]+flagall[3][i][j] == 0: 
            dphi[i][j] = fJpsiKst[1]*atan(tanphi[1][i][j]) + \
                         fJpsiKst[2]*atan(tanphi[2][i][j]) + \
                         fJpsiKst[3]*atan(tanphi[3][i][j])
            print " Averaged Delta phis (i,j)  = ", i, j, dphi[i][j],  flagall[1][i][j],flagall[2][i][j],flagall[3][i][j]


    

######################################################################
# Now compute errors on a and theta.
# using checkDerivative.nb
######################################################################


# experimental uncertainties
dH         = [ [e_H_exp[f] for i in range(5)] for f in range(4)]
dA         = [ [e_A[f]     for i in range(5)] for f in range(4)]
dHda       = [ [0 for i in range(5)] for f in range(4)]
dAda       = [ [0 for i in range(5)] for f in range(4)]
dHdtheta   = [ [0 for i in range(5)] for f in range(4)]
dAdtheta   = [ [0 for i in range(5)] for f in range(4)]
dPHIda     = [ [0 for i in range(5)] for f in range(4)]
dPHIdtheta = [ [0 for i in range(5)] for f in range(4)]

da          = [ [[0 for j in range(3)] for i in range(5)] for f in range(4) ]
dtheta      = [ [[0 for j in range(3)] for i in range(5)] for f in range(4) ]
e_dphi      = [ [[0 for j in range(3)] for i in range(5)] for f in range(4) ]

# theoretical uncertainties
dat          = [ [[0 for j in range(3)] for i in range(5)] for f in range(4) ]
dthetat      = [ [[0 for j in range(3)] for i in range(5)] for f in range(4) ]
e_dphit      = [ [[0 for j in range(3)] for i in range(5)] for f in range(4) ]


# error on tan Delpha phi
err_exp  = [ [0 for j in range(3)]  for i in range(5)] 
err_theo = [ [0 for j in range(3)]  for i in range(5)] 



print " Averaged over the 3 polarizations "
for i in range(1,5):
    for j in range(1,3):

    #if (flag1[i]==0 and  af1[f][i]>0):
    #if flag1[i]==0:
        for f in range(1,4):
            compute_err(f, i, j)
        print " DDDDDDDEBUG1      f,i,j, af = ", f, i,j,  af[f][i][j]
        err_exp[i][j] = sqrt( atan(tanphi[1][i][j])**2*e_fJpsiKst[1]**2 + \
                              fJpsiKst[1]**2*e_dphi[1][i][1]**2+atan(tanphi[2][i][j])**2*e_fJpsiKst[2]**2 + \
                              fJpsiKst[2]**2*e_dphi[2][i][1]**2+atan(tanphi[3][i][j])**2*e_fJpsiKst[3]**2 + \
                              fJpsiKst[3]**2*e_dphi[3][i][1]**2)
        err_theo[i][j] = sqrt( atan(tanphi[1][i][j])**2*e_fJpsiKst[1]**2 + \
                               fJpsiKst[1]**2*e_dphit[1][i][1]**2+atan(tanphi[2][i][j])**2*e_fJpsiKst[2]**2 + \
                               fJpsiKst[2]**2*e_dphit[2][i][1]**2+atan(tanphi[3][i][j])**2*e_fJpsiKst[3]**2 + \
                               fJpsiKst[3]**2*e_dphit[3][i][1]**2)
        print "Uncertainties on Delta phis all averaged i, j, exp, theo", i, j, err_exp[i][j], err_theo[i][j]

    


print " =============================================================== "
print " " 
print " Removing solution with a<0 and negative sqrt:" 
print " " 
print " =============================================================== "
# Now compute theo uncertainty, using SU3 breaking factors


#e_phi0_theo = 0.058
#e_phipar_theo = 0.09
#e_phiper_theo = 0.04

# approximate correlation between polarization fractions to ~ 0.5
# err_theo =
#sqrt(
#  atan(tanphi0_1)**2*e_fJpsiKst0**2 + fJpsiKst0**2*e_phi0_theo**2
# +atan(tanphipar_1)**2*e_fJpsiKstpar**2 + fJpsiKstpar**2*e_phipar_theo**2
# +atan(tanphiper_1)**2*e_fJpsiKstper**2 + fJpsiKstper**2*e_phiper_theo**2
# +2*atan(tanphi0_1)*atan(tanphiper_1)*0.5
# +2*atan(tanphi0_1)*atan(tanphipar_1)*0.5
# +2*atan(tanphipar_1)*atan(tanphiper_1)*0.5)


print "flagf = ", flagf
print "flagall = ", flagall
#print da


print " =============================================================== "
print " Summary of solutions for each individual polarizations " 
print " WARNING: display only solution with 3 pol available !!! " 
print " =============================================================== "

print " =============================================================== "
print " For LaTeX " 
print " =============================================================== "

myindex = ("0", "0", "\parallel", "\perp")

for i in range(1,5):
  for j in range(1,3):
    #if ( flagall[1][i][j]+flagall[2][i][j]+flagall[3][i][j] == 0):
      print " --------------------------------------------------  SOLUTION = ", i,j
      print " " 
      for f in range(1,4):
        print " --------------------------------------------------  "
        # if (flagall[f][i][j]==0  and  af[f][i][j]>0):
        #print " H_",f,"           = ", H[f], "                +/-", e_H_exp[f],       "(exp) +/-",e_H_theo[f],    "(theo)"
        #print " A_",f,"           = ", A[f], "                +/-", e_A[f],           "(exp) +/-",e_A_theo[f],    "(theo)"
        #print " a_",f,"           = ", af[f][i][j], "           +/-", da[f][i][j] ,     "(exp) +/-",dat[f][i][j],      "(theo)"
        #print " theta_",f,"       = ", thetaf[f][i], "        +/-", dtheta[f][i][j] , "(exp) +/-",dthetat[f][i][j],  "(theo)"
        #print " Delta(phis)_",f," = ", atan(tanphi[f][i][j]) ," +/- ", e_dphi[f][i][j], "(exp) +/- ", e_dphit[f][i][j],"" 

        print " $H_%s$           & $%7.3f$ & $\pm$ & $%7.3f$ & $\pm$ & $%7.3f$ \\\ " % \
              (myindex[f], H[f], e_H_exp[f], e_H_theo[f])
        print " $A_%s$           & $%7.3f$ & $\pm$ & $%7.3f$ & $\pm$ & $%7.3f$ \\\ " % \
              (myindex[f], A[f], e_A[f], e_A_theo[f])
        print " $a_%s$           & $%7.3f$ & $\pm$ & $%7.3f$ & $\pm$ & $%7.3f$ \\\ " % \
              (myindex[f], af[f][i][j], da[f][i][j], dat[f][i][j])
        print " $\\theta_%s$       & $%7.3f$ & $\pm$ & $%7.3f$  & $\pm$ & $%7.3f$ \\\ " % \
              (myindex[f], thetaf[f][i], dtheta[f][i][j], dthetat[f][i][j])
        print " $\Delta\phis^%s$ & $%7.3f$ & $\pm$ & $%7.3f$ & $\pm$ & $%7.3f$ \\\ " % \
              (myindex[f], atan(tanphi[f][i][j]), e_dphi[f][i][j], e_dphit[f][i][j])


print " =============================================================== "
print " =============================================================== "


for i in range(1,5):
  for j in range(1,3):
    #if ( flagall[1][i][j]+flagall[2][i][j]+flagall[3][i][j] == 0):
      print " --------------------------------------------------  SOLUTION = ", i,j
      print " " 
      for f in range(1,4):
        print " --------------------------------------------------  "
        # if (flagall[f][i][j]==0  and  af[f][i][j]>0):
        if (af[f][i][j]>0):
        #print " H_",f,"           = ", H[f], "                +/-", e_H_exp[f],       "(exp) +/-",e_H_theo[f],    "(theo)"
        #print " A_",f,"           = ", A[f], "                +/-", e_A[f],           "(exp) +/-",e_A_theo[f],    "(theo)"
        #print " a_",f,"           = ", af[f][i][j], "           +/-", da[f][i][j] ,     "(exp) +/-",dat[f][i][j],      "(theo)"
        #print " theta_",f,"       = ", thetaf[f][i], "        +/-", dtheta[f][i][j] , "(exp) +/-",dthetat[f][i][j],  "(theo)"
        #print " Delta(phis)_",f," = ", atan(tanphi[f][i][j]) ," +/- ", e_dphi[f][i][j], "(exp) +/- ", e_dphit[f][i][j],"(theo)" 

         print " H_%i           = %7.3f +/- %7.3f (exp) +/- %7.3f (theo)" % \
              (f, H[f], e_H_exp[f], e_H_theo[f])
         print " A_%i           = %7.3f +/- %7.3f (exp) +/- %7.3f (theo)" % \
              (f, A[f], e_A[f], e_A_theo[f])
         print " a_%i           = %7.3f +/- %7.3f (exp) +/- %7.3f (theo)" % \
              (f, af[f][i][j], da[f][i][j], dat[f][i][j])
         print " theta_%i       = %7.3f +/- %7.3f (exp) +/- %7.3f (theo)" % \
              (f, thetaf[f][i], dtheta[f][i][j], dthetat[f][i][j])
         print " Delta(phis)_%i = %7.3f +/- %7.3f (exp) +/- %7.3f (theo)" % \
              (f, atan(tanphi[f][i][j]), e_dphi[f][i][j], e_dphit[f][i][j])



print " =============================================================== "
print " Averaging the 3 polarizations:" 
print " =============================================================== "

for i in range(1,5):
  for j in range(1,3):
    if (dphi[i][j]!=0) and (flagall[1][i][j]+flagall[2][i][j]+flagall[3][i][j] == 0): 
    # also choosing only solution with af<=1
    # if ((af[1][j]<=1) and  (af[2][i][j]<=1) and  (af[3][i][j]<=1)):
        print " For solution (i,j) =  ", i, j, " Delta Phis FINAL = ", \
              dphi[i][j]," +/- ", err_exp[i][j], "(exp) +/- ", err_theo[i][j]," (theo)" 


