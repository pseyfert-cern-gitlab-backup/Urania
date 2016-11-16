##############################################
## ***** Branching Ratio Calculations ***** ##
##############################################

### Macro written by Kristof De Bruyn for LHCb Bs->JpsiK* ANA note
# - Calculations involving Branching Ratios && Form Factors
#   |-> H Observables


################################
## ***** Import Classes ***** ##
################################
import math
from Inputs import *


################################################
## ***** Corrections && Transformations ***** ##
################################################

### Exp -> Theo Conversion ###
def ADG_Conv(pol, aPar, thetaPar, gamPar):
    if (pol=="Long" or pol=="Para"):
      eta = 1
    else:
      eta = -1
    Norm = (1 - 2 * aPar[0] * math.cos(thetaPar[0]) * math.cos(gamPar[0]) + pow(aPar[0],2))
    Val = -eta * (math.cos(Phis_SM[0]) - 2 * aPar[0] * math.cos(thetaPar[0]) * math.cos(Phis_SM[0] + gamPar[0])\
          + pow(aPar[0],2) * math.cos(Phis_SM[0] + 2*gamPar[0]))/Norm
    Err = math.sqrt(\
            # theta
            pow(thetaPar[1]\
                * 2 * aPar[0] * math.sin(gamPar[0]) * math.sin(thetaPar[0])\
                * (pow(aPar[0],2) * math.sin(Phis_SM[0] + 2*gamPar[0]) - math.sin(Phis_SM[0]))/pow(Norm,2),2)\
            # a
            + pow(aPar[1]\
                  * 2 * math.sin(gamPar[0]) * (-2 * aPar[0] * math.sin(Phis_SM[0] + gamPar[0]) + math.cos(thetaPar[0])\
                  * (math.sin(Phis_SM[0]) + pow(aPar[0],2) * math.sin(Phis_SM[0] + 2*gamPar[0])))/pow(Norm,2),2)\
            # phi
            + pow(Phis_SM[1]\
                  * (math.sin(Phis_SM[0]) + aPar[0] * (-2 * math.cos(thetaPar[0]) * math.sin(Phis_SM[0] + gamPar[0])\
                  + aPar[0] * math.sin(Phis_SM[0] + 2*gamPar[0])))/Norm,2)\
            )
    return [Val, Err]

def ExptoTheo(pol, aPar, thetaPar, gamPar):
    ADG = ADG_Conv(pol, aPar, thetaPar, gamPar)
    Val = (1 - pow(ys[0],2))/(1 + ADG[0] * ys[0])
    Err = math.sqrt(  pow(ys[1] * (ADG[0] + 2 * ys[0] + ADG[0] * pow(ys[0],2))/pow(1 + ADG[0] * ys[0],2),2)\
                    + pow(ADG[1] * ys[0] *(1 - pow(ys[0],2))/pow(1 + ADG[0] * ys[0],2),2)\
                   )
    return [Val, addSyst * Err]

def ExptoTheoFromADG(ADG):
    Val = (1 - pow(ys[0],2))/(1 + ADG[0] * ys[0])
    Err = math.sqrt(  pow(ys[1] * (ADG[0] + 2 * ys[0] + ADG[0] * pow(ys[0],2))/pow(1 + ADG[0] * ys[0],2),2)\
                    + pow(ADG[1] * ys[0] *(1 - pow(ys[0],2))/pow(1 + ADG[0] * ys[0],2),2)\
                   )
    return [Val, addSyst * Err]

# Bd->JpsiRho: No corrections needed
BRBd2JpsiRho = BRBd2JpsiRho_LHCb
BRBd2JpsiRho_Long = XtimesY(BRBd2JpsiRho_LHCb, PolBd2JpsiRho_Long_LHCb)
BRBd2JpsiRho_Para = XtimesY(BRBd2JpsiRho_LHCb, PolBd2JpsiRho_Para_LHCb)
BRBd2JpsiRho_Perp = XtimesY(BRBd2JpsiRho_LHCb, PolBd2JpsiRho_Perp_LHCb)

# Bs->JpsiPhi: Assume no penguins
ExptoTheo_Bs2JpsiPhi_even = ExptoTheo("Long", [0,0], [0,0], gamma)
ExptoTheo_Bs2JpsiPhi_odd = ExptoTheo("Perp", [0,0], [0,0], gamma)
ExptoTheo_Bs2JpsiPhi_Long = XtimesY(ExptoTheo("Long", [0,0], [0,0], gamma), PolBs2JpsiPhi_Long_LHCb)
ExptoTheo_Bs2JpsiPhi_Para = XtimesY(ExptoTheo("Para", [0,0], [0,0], gamma), PolBs2JpsiPhi_Para_LHCb)
ExptoTheo_Bs2JpsiPhi_Perp = XtimesY(ExptoTheo("Perp", [0,0], [0,0], gamma), PolBs2JpsiPhi_Perp_LHCb)
ExptoTheo_Bs2JpsiPhi_av = XplusY([ExptoTheo_Bs2JpsiPhi_Long, ExptoTheo_Bs2JpsiPhi_Para, ExptoTheo_Bs2JpsiPhi_Perp])

BRBs2JpsiPhi = XtimesY(BRBs2JpsiPhi_LHCb, ExptoTheo_Bs2JpsiPhi_even)
BRBs2JpsiPhi_Long = XtimesY(BRBs2JpsiPhi_LHCb, ExptoTheo_Bs2JpsiPhi_Long)
BRBs2JpsiPhi_Para = XtimesY(BRBs2JpsiPhi_LHCb, ExptoTheo_Bs2JpsiPhi_Para)
BRBs2JpsiPhi_Perp = XtimesY(BRBs2JpsiPhi_LHCb, ExptoTheo_Bs2JpsiPhi_Perp)

# Bs->JpsiKstar: Flavour Specific final state
ExptoTheo_Bs2JpsiKstar = ExptoTheoFromADG([0,0])
ExptoTheo_Bs2JpsiKstar_Long = XtimesY(ExptoTheoFromADG([0,0]), PolBs2JpsiKstar_Long_LHCb)
ExptoTheo_Bs2JpsiKstar_Para = XtimesY(ExptoTheoFromADG([0,0]), PolBs2JpsiKstar_Para_LHCb)
ExptoTheo_Bs2JpsiKstar_Perp = XtimesY(ExptoTheoFromADG([0,0]), PolBs2JpsiKstar_Perp_LHCb)

BRBs2JpsiKstarPhi = XtimesY(BRBs2JpsiKstarPhi_LHCb, XoverY(ExptoTheo_Bs2JpsiKstar, ExptoTheo_Bs2JpsiPhi_av))
BRBs2JpsiKstarPhi_Long = XtimesY(BRBs2JpsiKstarPhi_LHCb, XoverY(ExptoTheo_Bs2JpsiKstar_Long, ExptoTheo_Bs2JpsiPhi_Long))
BRBs2JpsiKstarPhi_Para = XtimesY(BRBs2JpsiKstarPhi_LHCb, XoverY(ExptoTheo_Bs2JpsiKstar_Para, ExptoTheo_Bs2JpsiPhi_Para))
BRBs2JpsiKstarPhi_Perp = XtimesY(BRBs2JpsiKstarPhi_LHCb, XoverY(ExptoTheo_Bs2JpsiKstar_Perp, ExptoTheo_Bs2JpsiPhi_Perp))


### Results ###
if (doPrint==1):
  print "### Branching Fractions: Vector -- Vector ###"
  print "BR(Bd->JpsiRho) = (%.3f +/- %.3f)x10^{-5}" % (BRBd2JpsiRho[0] * pow(10,5), BRBd2JpsiRho[1] * pow(10,5))
  print "|-> Long (%.3f) = (%.3f +/- %.3f)x10^{-5}" % (PolBd2JpsiRho_Long_LHCb[0],
    BRBd2JpsiRho_Long[0] * pow(10,5), BRBd2JpsiRho_Long[1] * pow(10,5))
  print "|-> Para (%.3f) = (%.3f +/- %.3f)x10^{-5}" % (PolBd2JpsiRho_Para_LHCb[0],
    BRBd2JpsiRho_Para[0] * pow(10,5), BRBd2JpsiRho_Para[1] * pow(10,5))
  print "|-> Perp (%.3f) = (%.3f +/- %.3f)x10^{-5}" % (PolBd2JpsiRho_Perp_LHCb[0],
    BRBd2JpsiRho_Perp[0] * pow(10,5), BRBd2JpsiRho_Perp[1] * pow(10,5))
  print ""
  print "BR(Bs->JpsiPhi) = (%.2f +/- %.2f)x10^{-3}" % (BRBs2JpsiPhi[0] * pow(10,3), BRBs2JpsiPhi[1] * pow(10,3))
  print "|-> Conv (+1) = %.4f +/- %.4f" % (ExptoTheo_Bs2JpsiPhi_even[0], ExptoTheo_Bs2JpsiPhi_even[1])
  print "|-> Conv (-1) = %.4f +/- %.4f" % (ExptoTheo_Bs2JpsiPhi_odd[0], ExptoTheo_Bs2JpsiPhi_odd[1])
  print "|-> Conv (av) = %.4f +/- %.4f" % (ExptoTheo_Bs2JpsiPhi_av[0], ExptoTheo_Bs2JpsiPhi_av[1])
  print "|-> Long (%.3f) = (%.2f +/- %.2f)x10^{-3}" % (PolBs2JpsiPhi_Long_LHCb[0],
    BRBs2JpsiPhi_Long[0] * pow(10,3), BRBs2JpsiPhi_Long[1] * pow(10,3))
  print "|-> Para (%.3f) = (%.2f +/- %.2f)x10^{-3}" % (PolBs2JpsiPhi_Para_LHCb[0],
    BRBs2JpsiPhi_Para[0] * pow(10,3), BRBs2JpsiPhi_Para[1] * pow(10,3))
  print "|-> Perp (%.3f) = (%.2f +/- %.2f)x10^{-3}" % (PolBs2JpsiPhi_Perp_LHCb[0],
    BRBs2JpsiPhi_Perp[0] * pow(10,3), BRBs2JpsiPhi_Perp[1] * pow(10,3))
  print ""
  print "BR(Bs->JpsiK*)/BR(Bs->JpsiPhi) = %.4f +/- %.4f" % (BRBs2JpsiKstarPhi[0], BRBs2JpsiKstarPhi[1])
  print "|-> Conv (Bs->JpsiK*) = %.4f +/- %.4f" % (ExptoTheo_Bs2JpsiKstar[0], ExptoTheo_Bs2JpsiKstar[1])
  print "|-> Long = (%.4f +/- %.4f)" % (BRBs2JpsiKstarPhi_Long[0], BRBs2JpsiKstarPhi_Long[1])
  print "|-> Para = (%.4f +/- %.4f)" % (BRBs2JpsiKstarPhi_Para[0], BRBs2JpsiKstarPhi_Para[1])
  print "|-> Perp = (%.4f +/- %.4f)" % (BRBs2JpsiKstarPhi_Perp[0], BRBs2JpsiKstarPhi_Perp[1])
  print ""
  print "Note: For the total t=0 BR you get an admixture of correction factors because Long + Para are CP even and Perp is CP odd. At the moment, I therefore make the weighted sum, based on the polarisation fractions. But I'm not sure whether that is the correct thing to do. For the fit, these numbers are not needed."
  print ""


########################################
## ***** Individual Phase Space ***** ##
########################################

### Formulae ###
def PhSp(mB, mHeavy, mLight):
    Val = math.sqrt((1 - pow(mHeavy[0]/mB[0] + mLight[0]/mB[0],2)) * (1 - pow(mHeavy[0]/mB[0] - mLight[0]/mB[0],2)))
    sQrT = math.sqrt((mB[0] - mHeavy[0] - mLight[0]) * (mB[0] + mHeavy[0] - mLight[0]) *\
                     (mB[0] - mHeavy[0] + mLight[0]) * (mB[0] + mHeavy[0] + mLight[0]))
    Err = math.sqrt(\
              pow(mB[1] * (-2*pow(pow(mHeavy[0],2) - pow(mLight[0],2),2) + 2*pow(mB[0],2) * (pow(mHeavy[0],2) + pow(mLight[0],2)))/\
                (pow(mB[0],3) * sQrT),2)
            + pow(mHeavy[1] * 2 * mHeavy[0] * (pow(mB[0],2) - pow(mHeavy[0],2) + pow(mLight[0],2))/(pow(mB[0],2) * sQrT),2)
            + pow(mLight[1] * 2 * mLight[0] * (pow(mB[0],2) + pow(mHeavy[0],2) - pow(mLight[0],2))/(pow(mB[0],2) * sQrT),2)
          )
    return [Val, Err]


def VVPhSpBF(mB, mHeavy, mLight, tauB, BR):
    PhSpVal = PhSp(mB, mHeavy, mLight)
    Val = tauB[0] * PhSpVal[0]/(16 * math.pi * mB[0] * BR[0])
    Err = math.sqrt(\
              pow(BR[1] *  tauB[0] * PhSpVal[0]/(16 * math.pi * mB[0] * pow(BR[0],2)),2)
            + pow(tauB[1] * PhSpVal[0]/(16 * math.pi * mB[0] * BR[0]),2)
            + pow(PhSpVal[1] * tauB[0]/(16 * math.pi * mB[0] * BR[0]),2)
            + pow(mB[1] * tauB[0] * PhSpVal[0]/(16 * math.pi * pow(mB[0],2) * BR[0]),2)
          )
    return [Val, Err]

def VVPhSpBR(mBx, mBy, mHx, mHy, mLx, mLy, tauBx, tauBy, BR):
    PhSpx = PhSp(mBx, mHx, mLx)
    PhSpy = PhSp(mBy, mHy, mLy)
    Val = BR[0] * tauBx[0] * PhSpx[0] * mBy[0]/(tauBy[0] * PhSpy[0] * mBx[0])
    fullErr = 1
    if (mBx[0]==mBy[0]):
      fullErr = 0
    Err = math.sqrt(\
              pow(BR[1] * tauBx[0] * PhSpx[0] * mBy[0]/(tauBy[0] * PhSpy[0] * mBx[0]),2)
            + fullErr * pow(tauBx[1] * BR[0] * PhSpx[0] * mBy[0]/(tauBy[0] * PhSpy[0] * mBx[0]),2)
            + fullErr * pow(tauBy[1] * BR[0] * tauBx[0] * PhSpx[0] * mBy[0]/(pow(tauBy[0],2) * PhSpy[0] * mBx[0]),2)
            + pow(PhSpx[1] * BR[0] * tauBx[0] * mBy[0]/(tauBy[0] * PhSpy[0] * mBx[0]),2)
            + pow(PhSpy[1] * BR[0] * tauBx[0] * PhSpx[0] * mBy[0]/(tauBy[0] * pow(PhSpy[0],2) * mBx[0]),2)
            + fullErr * pow(mBx[1] * BR[0] * tauBx[0] * PhSpx[0] * mBy[0]/(tauBy[0] * PhSpy[0] * pow(mBx[0],2)),2)
            + fullErr * pow(mBy[1] * BR[0] * PhSpx[0] * tauBx[0]/(tauBy[0] * PhSpy[0] * mBx[0]),2)
            )
    return [Val, Err]


### Direct Measurements ###

# Bd->JpsiRho
PhSpBd2JpsiRho_Long = VVPhSpBF(M_Bd, M_Jpsi, M_Rhoz, tau_Bd, [x*2 for x in BRBd2JpsiRho_Long])
PhSpBd2JpsiRho_Para = VVPhSpBF(M_Bd, M_Jpsi, M_Rhoz, tau_Bd, [x*2 for x in BRBd2JpsiRho_Para])
PhSpBd2JpsiRho_Perp = VVPhSpBF(M_Bd, M_Jpsi, M_Rhoz, tau_Bd, [x*2 for x in BRBd2JpsiRho_Perp])

# Bs->JpsiPhi
PhSpBs2JpsiPhi_Long = VVPhSpBF(M_Bs, M_Jpsi, M_Phi, tau_Bs, BRBs2JpsiPhi_Long)
PhSpBs2JpsiPhi_Para = VVPhSpBF(M_Bs, M_Jpsi, M_Phi, tau_Bs, BRBs2JpsiPhi_Para)
PhSpBs2JpsiPhi_Perp = VVPhSpBF(M_Bs, M_Jpsi, M_Phi, tau_Bs, BRBs2JpsiPhi_Perp)

### Ratios ###
# PhSp(Bs->JpsiPhi) * BR(Bs->JpsiK*)/(PhSp(Bs->JpsiK*) * BR(Bs->JpsiPhi))
PhSpBs2JpsiKstarPhi_Long = VVPhSpBR(M_Bs, M_Bs, M_Jpsi, M_Jpsi, M_Phi, M_Kstarz, tau_Bs, tau_Bs, BRBs2JpsiKstarPhi_Long)
PhSpBs2JpsiKstarPhi_Para = VVPhSpBR(M_Bs, M_Bs, M_Jpsi, M_Jpsi, M_Phi, M_Kstarz, tau_Bs, tau_Bs, BRBs2JpsiKstarPhi_Para)
PhSpBs2JpsiKstarPhi_Perp = VVPhSpBR(M_Bs, M_Bs, M_Jpsi, M_Jpsi, M_Phi, M_Kstarz, tau_Bs, tau_Bs, BRBs2JpsiKstarPhi_Perp)

PhSpBs2JpsiKstarPhi_Long_forCorr = VVPhSpBR(M_Bs, M_Bs, M_Jpsi, M_Jpsi, M_Phi, M_Kstarz, tau_Bs, tau_Bs, XoverY(ExptoTheo_Bs2JpsiKstar, ExptoTheo_Bs2JpsiPhi_even))
PhSpBs2JpsiKstarPhi_Para_forCorr = VVPhSpBR(M_Bs, M_Bs, M_Jpsi, M_Jpsi, M_Phi, M_Kstarz, tau_Bs, tau_Bs, XoverY(ExptoTheo_Bs2JpsiKstar, ExptoTheo_Bs2JpsiPhi_even))
PhSpBs2JpsiKstarPhi_Perp_forCorr = VVPhSpBR(M_Bs, M_Bs, M_Jpsi, M_Jpsi, M_Phi, M_Kstarz, tau_Bs, tau_Bs, XoverY(ExptoTheo_Bs2JpsiKstar, ExptoTheo_Bs2JpsiPhi_odd))


########################################
## ***** B->Vector Form Factors ***** ##
########################################

def calcCorrErr(diff, a0, a1, a2, corr):
    weights = [1, diff, pow(diff,2)]
    sigma = [a0, a1, a2]
    sum = 0
    for i in range(0,3):
      for j in range(0,3):
        sum = sum + weights[i] * corr[i][j] * sigma[i] * sigma[j] * weights[j]
    return math.sqrt(sum)

def FFVzPar(mH, mL, qq):
    tzero = (mH[0] + mL[0]) * pow(math.sqrt(mH[0]) - math.sqrt(mL[0]),2)
    Val = (math.sqrt(pow(mH[0] + mL[0],2) - pow(qq[0],2)) - math.sqrt(pow(mH[0] + mL[0],2) - tzero))/\
          (math.sqrt(pow(mH[0] + mL[0],2) - pow(qq[0],2)) + math.sqrt(pow(mH[0] + mL[0],2) - tzero))
    Err = 0
    return [Val, Err]

def FFVrun(mH, mL, qq, a0, a1, a2, corr, mRes):
    zdiff = FFVzPar(mH, mL, qq)[0] - FFVzPar(mH, mL, [0,0])[0]
    pref = 1 - pow(qq[0]/mRes,2)
    Val = (a0[0] + a1[0] * zdiff + a2[0] * pow(zdiff,2))/pref
    Err = calcCorrErr(zdiff, a0[1], a1[1], a2[1], corr)/pref
    return [Val, Err]

A1Bd2Rho_Run  = FFVrun(M_Bd, M_Rhoz, M_Jpsi,  A1_a0_Bd2Rho,  A1_a1_Bd2Rho,  A1_a2_Bd2Rho,  A1_Bd2Rho_corr, mRes_Bd_A)
A12Bd2Rho_Run = FFVrun(M_Bd, M_Rhoz, M_Jpsi, A12_a0_Bd2Rho, A12_a1_Bd2Rho, A12_a2_Bd2Rho, A12_Bd2Rho_corr, mRes_Bd_A)
VBd2Rho_Run   = FFVrun(M_Bd, M_Rhoz, M_Jpsi,   V_a0_Bd2Rho,   V_a1_Bd2Rho,   V_a2_Bd2Rho,   V_Bd2Rho_corr, mRes_Bd_V)

A1Bs2Kstar_Run  = FFVrun(M_Bd, M_Kstarz, M_Jpsi,  A1_a0_Bs2Kstar,  A1_a1_Bs2Kstar,  A1_a2_Bs2Kstar,  A1_Bs2Kstar_corr, mRes_Bs_A)
A12Bs2Kstar_Run = FFVrun(M_Bd, M_Kstarz, M_Jpsi, A12_a0_Bs2Kstar, A12_a1_Bs2Kstar, A12_a2_Bs2Kstar, A12_Bs2Kstar_corr, mRes_Bs_A)
VBs2Kstar_Run   = FFVrun(M_Bd, M_Kstarz, M_Jpsi,   V_a0_Bs2Kstar,   V_a1_Bs2Kstar,   V_a2_Bs2Kstar,   V_Bs2Kstar_corr, mRes_Bs_V)

A1Bs2Phi_Run  = FFVrun(M_Bd, M_Phi, M_Jpsi,  A1_a0_Bs2Phi,  A1_a1_Bs2Phi,  A1_a2_Bs2Phi,  A1_Bs2Phi_corr, mRes_Bs_A)
A12Bs2Phi_Run = FFVrun(M_Bd, M_Phi, M_Jpsi, A12_a0_Bs2Phi, A12_a1_Bs2Phi, A12_a2_Bs2Phi, A12_Bs2Phi_corr, mRes_Bs_A)
VBs2Phi_Run   = FFVrun(M_Bd, M_Phi, M_Jpsi,   V_a0_Bs2Phi,   V_a1_Bs2Phi,   V_a2_Bs2Phi,   V_Bs2Phi_corr, mRes_Bs_V)

### Results ###
if (doPrint==1):
  print "### B->Vector Form Factors ###"
  print " A1(Bd->rho)(0) = %.3f +/- %.3f ->  A1(Bd->rho)(mJpsi) = %.3f +/- %.3f" % (A1_a0_Bd2Rho[0], A1_a0_Bd2Rho[1], A1Bd2Rho_Run[0], A1Bd2Rho_Run[1])
  print "A12(Bd->rho)(0) = %.3f +/- %.3f -> A12(Bd->rho)(mJpsi) = %.3f +/- %.3f" % (A12_a0_Bd2Rho[0], A12_a0_Bd2Rho[1], A12Bd2Rho_Run[0], A12Bd2Rho_Run[1])
  print "  V(Bd->rho)(0) = %.3f +/- %.3f ->   V(Bd->rho)(mJpsi) = %.3f +/- %.3f" % (V_a0_Bd2Rho[0], V_a0_Bd2Rho[1], VBd2Rho_Run[0], VBd2Rho_Run[1])
  print ""
  print " A1(Bs->K*)(0) = %.3f +/- %.3f ->  A1(Bs->K*)(mJpsi) = %.3f +/- %.3f" % (A1_a0_Bs2Kstar[0], A1_a0_Bs2Kstar[1], A1Bs2Kstar_Run[0], A1Bs2Kstar_Run[1])
  print "A12(Bs->K*)(0) = %.3f +/- %.3f -> A12(Bs->K*)(mJpsi) = %.3f +/- %.3f" % (A12_a0_Bs2Kstar[0], A12_a0_Bs2Kstar[1], A12Bs2Kstar_Run[0], A12Bs2Kstar_Run[1])
  print "  V(Bs->K*)(0) = %.3f +/- %.3f ->   V(Bs->K*)(mJpsi) = %.3f +/- %.3f" % (V_a0_Bs2Kstar[0], V_a0_Bs2Kstar[1], VBs2Kstar_Run[0], VBs2Kstar_Run[1])
  print ""
  print " A1(Bs->phi)(0) = %.3f +/- %.3f ->  A1(Bs->phi)(mJpsi) = %.3f +/- %.3f" % (A1_a0_Bs2Phi[0], A1_a0_Bs2Phi[1], A1Bs2Phi_Run[0], A1Bs2Phi_Run[1])
  print "A12(Bs->phi)(0) = %.3f +/- %.3f -> A12(Bs->phi)(mJpsi) = %.3f +/- %.3f" % (A12_a0_Bs2Phi[0], A12_a0_Bs2Phi[1], A12Bs2Phi_Run[0], A12Bs2Phi_Run[1])
  print "  V(Bs->phi)(0) = %.3f +/- %.3f ->   V(Bs->phi)(mJpsi) = %.3f +/- %.3f" % (V_a0_Bs2Phi[0], V_a0_Bs2Phi[1], VBs2Phi_Run[0], VBs2Phi_Run[1])
  print ""


###########################################
## ***** B->Vector Matrix Elements ***** ##
###########################################
# Omit the common prefactor

def xpol(mH, mL):
    Val = (pow(mH[0],2) - pow(M_Jpsi[0],2) - pow(mL[0],2))/(2 * M_Jpsi[0] * mL[0])
    Err = math.sqrt(\
              pow(mH[1] * mH[0]/(M_Jpsi[0] * mL[0]),2)\
            + pow(M_Jpsi[1] * (pow(mH[0],2) + pow(M_Jpsi[0],2) - pow(mL[0],2))/(2 * pow(M_Jpsi[0],2) * mL[0]),2)\
            + pow(mL[1] * (pow(mH[0],2) - pow(M_Jpsi[0],2) + pow(mL[0],2))/(2 * M_Jpsi[0] * pow(mL[0],2)),2)\
          )
    return [Val, Err]

def ALong(mH, mL, A12):
    Val = 8 * mH[0] * mL[0] * A12[0]/M_Jpsi[0]
    Err = math.sqrt(\
              pow(8 * mH[1] * mL[0] * A12[0]/M_Jpsi[0],2)\
            + pow(8 * mH[0] * mL[1] * A12[0]/M_Jpsi[0],2)\
            + pow(8 * mH[0] * mL[0] * A12[1]/M_Jpsi[0],2)\
            + pow(8 * mH[0] * mL[0] * A12[0] * M_Jpsi[1]/pow(M_Jpsi[0],2),2)\
          )
    return [Val, Err]

def APara(mH, mL, A1):
    Val = - math.sqrt(2) * (mH[0] + mL[0]) * A1[0]
    Err = math.sqrt(2) * math.sqrt(pow(mH[1] * A1[0],2) + pow(mL[1] * A1[0],2) + pow(A1[1] * (mH[0] + mL[0]),2))
    return [Val, Err]

def APerp(mH, mL, V):
    xPar = xpol(mH, mL)
    Val = math.sqrt(2 * (pow(xPar[0],2) - 1)) * 2 * (M_Jpsi[0] * mL[0]) * V[0]/(mH[0] + mL[0])
    Err = math.sqrt(2) * 2 *\
      math.sqrt(\
          pow(xPar[1] * xPar[0] * (M_Jpsi[0] * mL[0]) * V[0]/((mH[0] + mL[0]) * math.sqrt(pow(xPar[0],2) - 1)),2)\
        + pow(M_Jpsi[1] * math.sqrt(pow(xPar[0],2) - 1) * mL[0] * V[0]/(mH[0] + mL[0]),2)\
        + pow(mL[1] * math.sqrt(pow(xPar[0],2) - 1) * (M_Jpsi[0] * mH[0]) * V[0]/pow(mH[0] + mL[0],2),2)\
        + pow(V[1] * math.sqrt(pow(xPar[0],2) - 1) * (M_Jpsi[0] * mL[0])/(mH[0] + mL[0]),2)\
        + pow(mH[1] * math.sqrt(pow(xPar[0],2) - 1) * (M_Jpsi[0] * mL[0]) * V[0]/pow(mH[0] + mL[0],2),2)\
      )
    return [Val, Err]

### Pure Matrix Elements ###
ALong_Bd2JpsiRho = ALong(M_Bd, M_Rhoz, A12Bd2Rho_Run)
APara_Bd2JpsiRho = APara(M_Bd, M_Rhoz, A1Bd2Rho_Run)
APerp_Bd2JpsiRho = APerp(M_Bd, M_Rhoz, VBd2Rho_Run)

ALong_Bs2JpsiKstar = ALong(M_Bs, M_Kstarz, A12Bs2Kstar_Run)
APara_Bs2JpsiKstar = APara(M_Bs, M_Kstarz, A1Bs2Kstar_Run)
APerp_Bs2JpsiKstar = APerp(M_Bs, M_Kstarz, VBs2Kstar_Run)

ALong_Bs2JpsiPhi = ALong(M_Bs, M_Phi, A12Bs2Phi_Run)
APara_Bs2JpsiPhi = APara(M_Bs, M_Phi, A1Bs2Phi_Run)
APerp_Bs2JpsiPhi = APerp(M_Bs, M_Phi, VBs2Phi_Run)

### Ratio of Matrix Elements ###
ALong_BsBs2JpsiKstar = XoverY(ALong_Bs2JpsiPhi, ALong_Bs2JpsiKstar)
APara_BsBs2JpsiKstar = XoverY(APara_Bs2JpsiPhi, APara_Bs2JpsiKstar)
APerp_BsBs2JpsiKstar = XoverY(APerp_Bs2JpsiPhi, APerp_Bs2JpsiKstar)

ALong_BsBd2JpsiRho = XoverY(ALong_Bs2JpsiPhi,   ALong_Bd2JpsiRho)
APara_BsBd2JpsiRho = XoverY(APara_Bs2JpsiPhi,   APara_Bd2JpsiRho)
APerp_BsBd2JpsiRho = XoverY(APerp_Bs2JpsiPhi,   APerp_Bd2JpsiRho)

### Results ###
if (doPrint==1):
  print "### B->Vector Matrix Element Ratios ###"
  print "ALong(Bs->JpsiPhi)/ALong(Bs->JpsiK*) = (%.2f +/- %.2f)" % (ALong_BsBs2JpsiKstar[0], ALong_BsBs2JpsiKstar[1])
  print "APara(Bs->JpsiPhi)/APara(Bs->JpsiK*) = (%.2f +/- %.2f)" % (APara_BsBs2JpsiKstar[0], APara_BsBs2JpsiKstar[1])
  print "APerp(Bs->JpsiPhi)/APerp(Bs->JpsiK*) = (%.2f +/- %.2f)" % (APerp_BsBs2JpsiKstar[0], APerp_BsBs2JpsiKstar[1])
  print ""
  print "ALong(Bs->JpsiPhi)/ALong(Bd->JpsiRho) = (%.2f +/- %.2f)" % (ALong_BsBd2JpsiRho[0], ALong_BsBd2JpsiRho[1])
  print "APara(Bs->JpsiPhi)/APara(Bd->JpsiRho) = (%.2f +/- %.2f)" % (APara_BsBd2JpsiRho[0], APara_BsBd2JpsiRho[1])
  print "APerp(Bs->JpsiPhi)/APerp(Bd->JpsiRho) = (%.2f +/- %.2f)" % (APerp_BsBd2JpsiRho[0], APerp_BsBd2JpsiRho[1])
  print ""

if (doPrint==1):
  SALong_BsBs2JpsiKstar = Xsquared(ALong_BsBs2JpsiKstar)
  SAPara_BsBs2JpsiKstar = Xsquared(APara_BsBs2JpsiKstar)
  SAPerp_BsBs2JpsiKstar = Xsquared(APerp_BsBs2JpsiKstar)
  print "### B->Vector Matrix Element Ratios [Squared] ###"
  print "|ALong(Bs->JpsiPhi)/ALong(Bs->JpsiK*)|^2 = (%.2f +/- %.2f)" % (SALong_BsBs2JpsiKstar[0], SALong_BsBs2JpsiKstar[1])
  print "|APara(Bs->JpsiPhi)/APara(Bs->JpsiK*)|^2 = (%.2f +/- %.2f)" % (SAPara_BsBs2JpsiKstar[0], SAPara_BsBs2JpsiKstar[1])
  print "|APerp(Bs->JpsiPhi)/APerp(Bs->JpsiK*)|^2 = (%.2f +/- %.2f)" % (SAPerp_BsBs2JpsiKstar[0], SAPerp_BsBs2JpsiKstar[1])
  print ""

##############################
## ***** H Observable ***** ##
##############################

def VHobs(ME, PhSpx, PhSpy):
    PhSp = XoverY(PhSpx, PhSpy)
    Val = (1/epsilon[0]) * ME[0] * PhSp[0]
    ErrST = ME[0] * math.sqrt(pow((1/epsilon[0]) * PhSp[1],2) + pow((epsilon[1]/pow(epsilon[0],2)) * PhSp[0],2))
    ErrFF = ME[1] * (1/epsilon[0]) * PhSp[0]
    Err = math.sqrt(pow(ErrST,2) + addHad * pow(ErrFF,2))
    return [Val, Err, ErrST, ErrFF]

def VHobsR(ME, PhSp):
    Val = (1/epsilon[0]) * ME[0] * PhSp[0]
    ErrST = ME[0] * math.sqrt(pow((1/epsilon[0]) * PhSp[1],2) + pow((epsilon[1]/pow(epsilon[0],2)) * PhSp[0],2))
    ErrFF = ME[1] * (1/epsilon[0]) * PhSp[0]
    Err = math.sqrt(pow(ErrST,2) + addHad * pow(ErrFF,2))
    return [Val, Err, ErrST, ErrFF]

### Excluding Amplitude Ratios (for extended fit) ###
HextBsKstarBsPhi_Long = VHobsR([1,0], PhSpBs2JpsiKstarPhi_Long)
HextBsKstarBsPhi_Para = VHobsR([1,0], PhSpBs2JpsiKstarPhi_Para)
HextBsKstarBsPhi_Perp = VHobsR([1,0], PhSpBs2JpsiKstarPhi_Perp)

HextBdRhoBsPhi_Long = VHobs([1,0], PhSpBs2JpsiPhi_Long, PhSpBd2JpsiRho_Long)
HextBdRhoBsPhi_Para = VHobs([1,0], PhSpBs2JpsiPhi_Para, PhSpBd2JpsiRho_Para)
HextBdRhoBsPhi_Perp = VHobs([1,0], PhSpBs2JpsiPhi_Perp, PhSpBd2JpsiRho_Perp)

### Individual ###
HBsKstarBsPhi_Long = VHobsR(Xsquared(ALong_BsBs2JpsiKstar), PhSpBs2JpsiKstarPhi_Long)
HBsKstarBsPhi_Para = VHobsR(Xsquared(APara_BsBs2JpsiKstar), PhSpBs2JpsiKstarPhi_Para)
HBsKstarBsPhi_Perp = VHobsR(Xsquared(APerp_BsBs2JpsiKstar), PhSpBs2JpsiKstarPhi_Perp)

HBdRhoBsPhi_Long = VHobs(Xsquared(ALong_BsBd2JpsiRho), PhSpBs2JpsiPhi_Long, PhSpBd2JpsiRho_Long)
HBdRhoBsPhi_Para = VHobs(Xsquared(APara_BsBd2JpsiRho), PhSpBs2JpsiPhi_Para, PhSpBd2JpsiRho_Para)
HBdRhoBsPhi_Perp = VHobs(Xsquared(APerp_BsBd2JpsiRho), PhSpBs2JpsiPhi_Perp, PhSpBd2JpsiRho_Perp)

### For correlated Fit ###
HBsKstarBsPhi_Long_forCorr = VHobsR(Xsquared(ALong_BsBs2JpsiKstar), PhSpBs2JpsiKstarPhi_Long_forCorr)
HBsKstarBsPhi_Para_forCorr = VHobsR(Xsquared(APara_BsBs2JpsiKstar), PhSpBs2JpsiKstarPhi_Para_forCorr)
HBsKstarBsPhi_Perp_forCorr = VHobsR(Xsquared(APerp_BsBs2JpsiKstar), PhSpBs2JpsiKstarPhi_Perp_forCorr)

### Results ###
if (doPrint==1):
  print "### H Observables: B->JpsiV ###"
  print "H(Bs->JpsiK*/Bs->JpsiPhi)|Long = (%.2f +/- %.2f +/- %.2f) = %.2f +/- %.2f" % (HBsKstarBsPhi_Long[0],
    HBsKstarBsPhi_Long[2], HBsKstarBsPhi_Long[3], HBsKstarBsPhi_Long[0], HBsKstarBsPhi_Long[1])
  print "H(Bs->JpsiK*/Bs->JpsiPhi)|Para = (%.2f +/- %.2f +/- %.2f) = %.2f +/- %.2f" % (HBsKstarBsPhi_Para[0],
    HBsKstarBsPhi_Para[2], HBsKstarBsPhi_Para[3], HBsKstarBsPhi_Para[0], HBsKstarBsPhi_Para[1])
  print "H(Bs->JpsiK*/Bs->JpsiPhi)|Perp = (%.2f +/- %.2f +/- %.2f) = %.2f +/- %.2f" % (HBsKstarBsPhi_Perp[0],
    HBsKstarBsPhi_Perp[2], HBsKstarBsPhi_Perp[3], HBsKstarBsPhi_Perp[0], HBsKstarBsPhi_Perp[1])
  print ""
  print "H(Bd->JpsiRho/Bs->JpsiPhi)|Long = (%.2f +/- %.2f +/- %.2f) = %.2f +/- %.2f" % (HBdRhoBsPhi_Long[0],
    HBdRhoBsPhi_Long[2], HBdRhoBsPhi_Long[3], HBdRhoBsPhi_Long[0], HBdRhoBsPhi_Long[1])
  print "H(Bd->JpsiRho/Bs->JpsiPhi)|Para = (%.2f +/- %.2f +/- %.2f) = %.2f +/- %.2f" % (HBdRhoBsPhi_Para[0],
    HBdRhoBsPhi_Para[2], HBdRhoBsPhi_Para[3], HBdRhoBsPhi_Para[0], HBdRhoBsPhi_Para[1])
  print "H(Bd->JpsiRho/Bs->JpsiPhi)|Perp = (%.2f +/- %.2f +/- %.2f) = %.2f +/- %.2f" % (HBdRhoBsPhi_Perp[0],
    HBdRhoBsPhi_Perp[2], HBdRhoBsPhi_Perp[3], HBdRhoBsPhi_Perp[0], HBdRhoBsPhi_Perp[1])
  print ""

### Results ###
if (doPrint==1):
  print "### H Observables: B->JpsiV (no FF) ###"
  print "H(Bs->JpsiK*/Bs->JpsiPhi)|Long = %.2f +/- %.2f" % (HextBsKstarBsPhi_Long[0], HextBsKstarBsPhi_Long[1])
  print "H(Bs->JpsiK*/Bs->JpsiPhi)|Para = %.2f +/- %.2f" % (HextBsKstarBsPhi_Para[0], HextBsKstarBsPhi_Para[1])
  print "H(Bs->JpsiK*/Bs->JpsiPhi)|Perp = %.2f +/- %.2f" % (HextBsKstarBsPhi_Perp[0], HextBsKstarBsPhi_Perp[1])
  print ""
  print "H(Bd->JpsiRho/Bs->JpsiPhi)|Long = %.2f +/- %.2f" % (HextBdRhoBsPhi_Long[0], HextBdRhoBsPhi_Long[1])
  print "H(Bd->JpsiRho/Bs->JpsiPhi)|Para = %.2f +/- %.2f" % (HextBdRhoBsPhi_Para[0], HextBdRhoBsPhi_Para[1])
  print "H(Bd->JpsiRho/Bs->JpsiPhi)|Perp = %.2f +/- %.2f" % (HextBdRhoBsPhi_Perp[0], HextBdRhoBsPhi_Perp[1])
  print ""
  diffLong = XdiffY(HextBdRhoBsPhi_Long, HextBsKstarBsPhi_Long)
  diffPara = XdiffY(HextBdRhoBsPhi_Para, HextBsKstarBsPhi_Para)
  diffPerp = XdiffY(HextBdRhoBsPhi_Perp, HextBsKstarBsPhi_Perp)
  print "Delta(rho-K*)_Long = %.3f +/- %.3f (%.1f)" % (diffLong[0], diffLong[1], diffLong[2])
  print "Delta(rho-K*)_Para = %.3f +/- %.3f (%.1f)" % (diffPara[0], diffPara[1], diffPara[2])
  print "Delta(rho-K*)_Perp = %.3f +/- %.3f (%.1f)" % (diffPerp[0], diffPerp[1], diffPerp[2])
  print ""
