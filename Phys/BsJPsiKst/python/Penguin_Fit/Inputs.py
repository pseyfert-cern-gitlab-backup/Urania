##################################################
## ***** Input for Bs->JpsiKstar Analysis ***** ##
##################################################

### Macro written by Kristof De Bruyn for LHCb Bs->JpsiK* ANA note
# - List of inputs: Experimental Measurements && Theoretical results (Lattice, LCSR)
# - Source is PDG 2014, unless stated otherwise


################################
## ***** Import Classes ***** ##
################################
import math
import shelve


##################################
## ***** General Settings ***** ##
##################################
doPrint = 0
pdgScale = 0
addStat = 1
addSyst = 1
addHad = 1

D2R = (math.pi/180.)
R2D = (180./math.pi)


##################################
## ***** General Formulae ***** ##
##################################

def average(list):
    # Weighted Average
    mean = 0
    var = 0
    chi2 = 0
    for i in range(0, len(list)):
      mean = mean + list[i][0]/pow(list[i][1],2)
      var  = var  + 1/pow(list[i][1],2)
    Val = mean/var
    Err = math.sqrt(1/var)
    # Scale factor
    ndof = 0
    limit = 3 * math.sqrt(len(list)) * Err
    for i in range(0, len(list)):
      if (list[i][1] <= limit):
        chi2 = chi2 + pow(list[i][0] - Val,2)/pow(list[i][1],2)
        ndof = ndof + 1
    if (ndof>1):
      chi2ndof = chi2/(ndof-1)
      if (chi2ndof<=1):
        scale = 1
      else:
        scale = math.sqrt(chi2ndof)
    else:
      scale = 1
    if (pdgScale==1):
      Err = Err * scale
    return [Val, Err, scale]

def XtimesY(x, y):
    return [x[0] * y[0], math.sqrt(pow(x[1] * y[0],2) + pow(x[0] * y[1],2))]

def XoverY(x, y):
    return [x[0]/y[0], math.sqrt(pow(x[1]/y[0],2) + pow(x[0] * y[1]/pow(y[0],2),2))]

def XplusY(list):
    Val = 0
    Err = 0
    for i in range(0, len(list)):
      Val = Val + list[i][0]
      Err = Err + pow(list[i][1],2)
    return [Val, math.sqrt(Err)]

def Xsquared(x):
    return [pow(x[0],2), 2 * x[0] * x[1]]

def XdiffY(x, y):
    Val = x[0] - y[0]
    Err = math.sqrt(pow(x[1],2) + pow(y[1],2))
    Sig = Val/Err
    return [Val, Err, Sig]

###########################
## ***** Constants ***** ##
###########################

### Lifetimes ###
tau_Bd = [1.520, 0.004] # HFAG Fall 2014
Gamma_Bs = [0.6628, 0.0019] # HFAG Fall 2014
tau_Bs = XoverY([1,0], Gamma_Bs)
DeltaGamma_Bs = [0.0806, 0.0060] # HFAG Fall 2014
ys = XoverY(DeltaGamma_Bs, [x * 2 for x in Gamma_Bs])

if (doPrint==1):
  print "### Lifetimes ###"
  print "tau_Bs = %.3f +/- %.3f" % (tau_Bs[0], tau_Bs[1])
  print "ys = %.4f +/- %.4f" % (ys[0], ys[1])
  print ""

### Masses ###
M_Rhoz   = [775.26, 0.25]
M_Kstarz = [895.81, 0.19]
M_Phi    = [1019.455, 0.022]
M_Jpsi   = [3096.916, 0.011]
M_Bd     = [5279.58, 0.17]
M_Bs     = [5366.77, 0.24]

### CKM Triangle ###
gamma = [x * D2R for x in [73.2, 7.0, 6.3]] # CKMfitter CKM 2014 (Dir. Meas.)
Phid_wpen = [0.767, 0.029] # Penguin analysis documented in my Thesis
Phis_SM = [-0.0365, 0.0013] # CKMfitter CKM 2014
Phis_LHCb = [-0.015, 0.036] # HFAG Fall 2014

SmixBd2JpsiK_HFAG  = [0.665, 0.022] # HFAG Fall 2014
SmixBd2JpsiK_CDF   = [0.79, 0.44] # hep-ex/9909003 (CDF)
SmixBd2JpsiK_Belle = [0.57, math.sqrt(pow(0.58,2) + pow(0.06,2))] # 1201.3502 (Belle)
SmixBd2JpsiK_LHCb  = [0.731, math.sqrt(pow(0.035,2) + pow(0.020,2))] # 1503.07089 (LHCb)
SmixBd2JpsiK_Exp   = average([SmixBd2JpsiK_HFAG, SmixBd2JpsiK_CDF, SmixBd2JpsiK_Belle, SmixBd2JpsiK_LHCb])
Phid_JpsiK = [math.asin(SmixBd2JpsiK_Exp[0]), SmixBd2JpsiK_Exp[1]/math.sqrt(1-pow(SmixBd2JpsiK_Exp[0],2))]

Vus = [0.22548, 0.00068] # CKMfitter CKM 2014 (fit)
epsilon =  [pow(Vus[0],2)/(1 - pow(Vus[0],2)), 2 * Vus[0] * Vus[1]/pow(1 - pow(Vus[0],2),2)]

if (doPrint==1):
  print "### CKM Observables ###"
  print "gamma = [%.1f +/- %.1f]" % (gamma[0] * R2D, gamma[1] * R2D)
  print "phi_d = [%.1f +/- %.1f]" % (Phid_wpen[0] * R2D, Phid_wpen[1] * R2D)
  print "phi_s = [%.3f +/- %.3f]" % (Phis_SM[0] * R2D, Phis_SM[1] * R2D)
  print "epsilon = %.4f +/- %.4f" % (epsilon[0], epsilon[1])
  print ""

##################################
## ***** Branching Ratios ***** ##
##################################

### Branching Fractions: Direct Measurements ###
# Bd - Cabibbo Allowed Penguins
BRBd2JpsiRho_LHCb = [x * pow(10,-5) for x in [2.50, math.sqrt(addStat * pow(0.10,2) + addSyst * pow(0.18,2))]] # 1404.5673 (LHCb)

# Bs - Cabibbo Suppressed Penguins
BRBs2JpsiPhi_LHCb = [x * pow(10,-3) for x in [1.038, math.sqrt(addStat * pow(0.013,2) + addSyst * pow(0.063,2) + addSyst * pow(0.060,2))]] # 1302.1213 (LHCb)

### Branching Fractions: Ratios ###
# Preliminary LHCb analysis (internal)
BRBs2JpsiKstarPhi_LHCb = [0.040497, math.sqrt(addStat * pow(0.001935,2) + addSyst * pow(0.001275,2))]


########################################
## ***** Polarisation Fractions ***** ##
########################################

### Bd->JpsiRho ###
# 1404.5673 (LHCb)
PolBd2JpsiRho_Long_LHCb = [0.574, math.sqrt(addStat * pow(0.020,2) + addSyst * pow(0.031,2))]
PolBd2JpsiRho_Para_LHCb = [0.234, math.sqrt(addStat * pow(0.017,2) + addSyst * pow(0.013,2))]
PolBd2JpsiRho_Perp_LHCb = [0.192, math.sqrt(addStat * pow(0.017,2) + addSyst * pow(0.038,2))]

### Bs->JpsiKstar ###
# Preliminary LHCb analysis (internal)
PolBs2JpsiKstar_Long_LHCb = [0.497, math.sqrt(addStat * pow(0.025,2) + addSyst * pow(0.025,2))]
PolBs2JpsiKstar_Para_LHCb = [0.179, math.sqrt(addStat * pow(0.027,2) + addSyst * pow(0.013,2))]
PolBs2JpsiKstar_corr_LHCb = -0.51
PolBs2JpsiKstar_Perp_LHCb = [1-PolBs2JpsiKstar_Long_LHCb[0]-PolBs2JpsiKstar_Para_LHCb[0],
                             math.sqrt(pow(PolBs2JpsiKstar_Long_LHCb[1],2)
                             + pow(PolBs2JpsiKstar_Para_LHCb[1],2)
                             + 2 * PolBs2JpsiKstar_corr_LHCb * PolBs2JpsiKstar_Long_LHCb[1] * PolBs2JpsiKstar_Para_LHCb[1])]

### Bs->JpsiPhi ###
# 1411.3104 (LHCb)
PolBs2JpsiPhi_Long_LHCb = [0.5241, math.sqrt(addStat * pow(0.0034,2) + addSyst * pow(0.0067,2))]
PolBs2JpsiPhi_Perp_LHCb = [0.2504, math.sqrt(addStat * pow(0.0049,2) + addSyst * pow(0.0063,2))]
PolBs2JpsiPhi_corr_LHCb = -0.59 # ANA Note
PolBs2JpsiPhi_Para_LHCb = [1-PolBs2JpsiPhi_Long_LHCb[0]-PolBs2JpsiPhi_Perp_LHCb[0],
                           math.sqrt(pow(PolBs2JpsiPhi_Long_LHCb[1],2)
                           + pow(PolBs2JpsiPhi_Perp_LHCb[1],2)
                           + 2 * PolBs2JpsiPhi_corr_LHCb * PolBs2JpsiPhi_Long_LHCb[1] * PolBs2JpsiPhi_Perp_LHCb[1])]

if (doPrint==1):
  print "### Comparison: Polarisation Fractions ###"
  print PolBd2JpsiRho_Long_LHCb
  print PolBd2JpsiRho_Para_LHCb
  print PolBd2JpsiRho_Perp_LHCb
  print PolBs2JpsiKstar_Long_LHCb
  print PolBs2JpsiKstar_Para_LHCb
  print PolBs2JpsiKstar_Perp_LHCb
  diffLong = XdiffY(PolBd2JpsiRho_Long_LHCb, PolBs2JpsiKstar_Long_LHCb)
  diffPara = XdiffY(PolBd2JpsiRho_Para_LHCb, PolBs2JpsiKstar_Para_LHCb)
  diffPerp = XdiffY(PolBd2JpsiRho_Perp_LHCb, PolBs2JpsiKstar_Perp_LHCb)
  print "Delta(rho-K*)_Long = %.3f +/- %.3f (%.1f)" % (diffLong[0], diffLong[1], diffLong[2])
  print "Delta(rho-K*)_Para = %.3f +/- %.3f (%.1f)" % (diffPara[0], diffPara[1], diffPara[2])
  print "Delta(rho-K*)_Perp = %.3f +/- %.3f (%.1f)" % (diffPerp[0], diffPerp[1], diffPerp[2])
  print ""

################################
## ***** CP Observables ***** ##
################################

### Convention ###
# aCP = (B - Bbar)/(B + Bbar) = (Adir Cos + Amix Sin)/(Cosh + ADG Sinh)
# Adir = (1-l^2)/(1+l^2)
# Amix = 2 Im[l]/(1+l^2)

def CdirRho(alpha):
    Val = 2*alpha[0]/(1+pow(alpha[0],2))
    Err = 2*(1-pow(alpha[0],2))*alpha[1]/pow(1+pow(alpha[0],2),2)
    return [Val, Err]

def SmixRho(alpha, beff):
    Val = (1-pow(alpha[0],2))*math.sin(beff[0])/(1+pow(alpha[0],2))
    ErrA = 4*alpha[0]*math.sin(beff[0])*alpha[1]/pow(1+pow(alpha[0],2),2)
    ErrB = (1-pow(alpha[0],2))*math.cos(beff[0])*beff[1]/(1+pow(alpha[0],2))
    return [Val, math.sqrt(pow(ErrA,2)+pow(ErrB,2))]

### PDG Averages ###
# Bd - Cabibbo Allowed Penguins
# 1411.1634 (LHCb)
alphaBd2JpsiRho_Exp  = [x * pow(10,-3) for x in [-32, math.sqrt(addStat * pow(28,2) + addSyst * pow(9,2))]]
beffBd2JpsiRho_Exp   = [x * D2R for x in [41.7, math.sqrt(addStat * pow(9.6,2) + addSyst * pow(6.3,2))]]
AdirBd2JpsiRho_Exp   = CdirRho(alphaBd2JpsiRho_Exp)
AmixBd2JpsiRho_Exp   = SmixRho(alphaBd2JpsiRho_Exp, beffBd2JpsiRho_Exp)
#
alphaBd2JpsiRho_Long  = [x * pow(10,-3) for x in [-47, math.sqrt(addStat * pow(34,2) + addSyst * pow(11,2))]]
beffBd2JpsiRho_Long   = [x * D2R for x in [44.1, math.sqrt(addStat * pow(10.2,2) + addSyst * pow(6.9,2))]]
AdirBd2JpsiRho_Long   = CdirRho(alphaBd2JpsiRho_Long)
AmixBd2JpsiRho_Long   = SmixRho(alphaBd2JpsiRho_Long, beffBd2JpsiRho_Long)
#
alphaBd2JpsiRho_Para  = [x * pow(10,-3) for x in [-61, math.sqrt(addStat * pow(60,2) + addSyst * pow(8,2))]]
bdiffBd2JpsiRho_Para  = [x * D2R for x in [-0.8, math.sqrt(addStat * pow(6.5,2) + addSyst * pow(1.9,2))]]
beffBd2JpsiRho_Para   = XplusY([bdiffBd2JpsiRho_Para, beffBd2JpsiRho_Long])
AdirBd2JpsiRho_Para   = CdirRho(alphaBd2JpsiRho_Para)
AmixBd2JpsiRho_Para   = SmixRho(alphaBd2JpsiRho_Para, beffBd2JpsiRho_Para)
#
alphaBd2JpsiRho_Perp  = [x * pow(10,-3) for x in [17, math.sqrt(addStat * pow(109,2) + addSyst * pow(22,2))]]
bdiffBd2JpsiRho_Perp  = [x * D2R for x in [-3.6, math.sqrt(addStat * pow(7.2,2) + addSyst * pow(2.0,2))]]
beffBd2JpsiRho_Perp   = XplusY([bdiffBd2JpsiRho_Perp, beffBd2JpsiRho_Long])
AdirBd2JpsiRho_Perp   = CdirRho(alphaBd2JpsiRho_Perp)
AmixBd2JpsiRho_Perp   = SmixRho(alphaBd2JpsiRho_Perp, beffBd2JpsiRho_Perp)

# Bs - Cabibbo Allowed Penguins
# Preliminary LHCb analysis (internal)
# [LHCb quotes ACP = - Adir]
AdirBs2JpsiKstar_Long = [0.048, math.sqrt(addStat * pow(0.057,2) + addSyst * pow(0.020,2))]
AdirBs2JpsiKstar_Para = [-0.171, math.sqrt(addStat * pow(0.152,2) + addSyst * pow(0.028,2))]
AdirBs2JpsiKstar_Perp = [0.049, math.sqrt(addStat * pow(0.096,2) + addSyst * pow(0.025,2))]
# correlations
AdirRho_LongPara = -0.11
AdirRho_LongPerp = -0.17
AdirRho_ParaPerp = -0.49

### Results ###
if (doPrint==1):
  print "### CP Observables ###"
  print ""
  print "Adir(Bd->JpsiRho) = %.3f +/- %.3f" % (AdirBd2JpsiRho_Exp[0], AdirBd2JpsiRho_Exp[1])
  print "Amix(Bd->JpsiRho) = %.2f +/- %.2f" % (AmixBd2JpsiRho_Exp[0], AmixBd2JpsiRho_Exp[1])
  print ""
  print "Adir(Bd->JpsiRho)_Long = %.3f +/- %.3f" % (AdirBd2JpsiRho_Long[0], AdirBd2JpsiRho_Long[1])
  print "Amix(Bd->JpsiRho)_Long = %.2f +/- %.2f" % (AmixBd2JpsiRho_Long[0], AmixBd2JpsiRho_Long[1])
  print "Adir(Bs->JpsiK* )_Long = %.3f +/- %.3f" % (AdirBs2JpsiKstar_Long[0], AdirBs2JpsiKstar_Long[1])
  print "Adir(Bd->JpsiRho)_Para = %.3f +/- %.3f" % (AdirBd2JpsiRho_Para[0], AdirBd2JpsiRho_Para[1])
  print "Amix(Bd->JpsiRho)_Para = %.2f +/- %.2f" % (AmixBd2JpsiRho_Para[0], AmixBd2JpsiRho_Para[1])
  print "Adir(Bs->JpsiK* )_Para = %.3f +/- %.3f" % (AdirBs2JpsiKstar_Para[0], AdirBs2JpsiKstar_Para[1])
  print "Adir(Bd->JpsiRho)_Perp = %.3f +/- %.3f" % (AdirBd2JpsiRho_Perp[0], AdirBd2JpsiRho_Perp[1])
  print "Amix(Bd->JpsiRho)_Perp = %.2f +/- %.2f" % (AmixBd2JpsiRho_Perp[0], AmixBd2JpsiRho_Perp[1])
  print "Adir(Bs->JpsiK* )_Perp = %.3f +/- %.3f" % (AdirBs2JpsiKstar_Perp[0], AdirBs2JpsiKstar_Perp[1])
  print ""
if (doPrint==1):
  print "### Comparison: CP Observables ###"
  diffLong = XdiffY(AdirBd2JpsiRho_Long, AdirBs2JpsiKstar_Long)
  diffPara = XdiffY(AdirBd2JpsiRho_Para, AdirBs2JpsiKstar_Para)
  diffPerp = XdiffY(AdirBd2JpsiRho_Perp, AdirBs2JpsiKstar_Perp)
  print "Delta(rho-K*)_Long = %.3f +/- %.3f (%.1f)" % (diffLong[0], diffLong[1], diffLong[2])
  print "Delta(rho-K*)_Para = %.3f +/- %.3f (%.1f)" % (diffPara[0], diffPara[1], diffPara[2])
  print "Delta(rho-K*)_Perp = %.3f +/- %.3f (%.1f)" % (diffPerp[0], diffPerp[1], diffPerp[2])
  print ""

########################################
## ***** B->Vector Form Factors ***** ##
########################################
# 1503.05534

### q^2 Dependence ###
mRes_Bd_A = 5724
mRes_Bd_V = 5325
mRes_Bs_A = 5829
mRes_Bs_V = 5415

A1_a0_Bd2Rho = [0.2667, 0.0245]
A1_a1_Bd2Rho = [0.362, 0.132]
A1_a2_Bd2Rho = [0.553, 0.347]
A1_Bd2Rho_corr = [[1.0,0.484734,0.350769],[0.484734,1.0,0.769212],[0.350769,0.769212,1.0]]

A12_a0_Bd2Rho = [0.3071, 0.0283]
A12_a1_Bd2Rho = [0.672, 0.203]
A12_a2_Bd2Rho = [0.332, 0.751]
A12_Bd2Rho_corr = [[1.0,0.585399,0.524749],[0.585399,1.0,0.93703],[0.524749,0.93703,1.0]]

V_a0_Bd2Rho = [0.3331, 0.0320]
V_a1_Bd2Rho = [-0.890, 0.180]
V_a2_Bd2Rho = [1.737, 1.128]
V_Bd2Rho_corr = [[1.0,0.496438,-0.215184],[0.496438,1.0,-0.405493],[-0.215184,-0.405493,1.0]]

A1_a0_Bs2Kstar = [0.2462, 0.0225]
A1_a1_Bs2Kstar = [0.256, 0.190]
A1_a2_Bs2Kstar = [0.855, 0.701]
A1_Bs2Kstar_corr = [[1.0,0.431789,0.216978],[0.431789,1.0,0.79379],[0.216978,0.79379,1.0]]

A12_a0_Bs2Kstar = [0.2458, 0.0232]
A12_a1_Bs2Kstar = [0.554, 0.182]
A12_a2_Bs2Kstar = [0.681, 0.953]
A12_Bs2Kstar_corr = [[1.0,0.463953,0.12919],[0.463953,1.0,0.723051],[0.12919,0.723051,1.0]]

V_a0_Bs2Kstar = [0.3113, 0.0295]
V_a1_Bs2Kstar = [-0.926, 0.335]
V_a2_Bs2Kstar = [2.888, 1.843]
V_Bs2Kstar_corr = [[1.0,0.260658,-0.353116],[0.260658,1.0,0.112502],[-0.353116,0.112502,1.0]]

A1_a0_Bs2Phi = [0.3153, 0.0272]
A1_a1_Bs2Phi = [0.464, 0.219]
A1_a2_Bs2Phi = [1.703, 0.834]
A1_Bs2Phi_corr = [[1.0,0.51148,0.266973],[0.51148,1.0,0.836096],[0.266973,0.836096,1.0]]

A12_a0_Bs2Phi = [0.2743, 0.0222]
A12_a1_Bs2Phi = [0.768, 0.175]
A12_a2_Bs2Phi = [0.914, 1.000]
A12_Bs2Phi_corr = [[1.0,0.254855,0.158672],[0.254855,1.0,0.891034],[0.158672,0.891034,1.0]]

V_a0_Bs2Phi = [0.4067, 0.0327]
V_a1_Bs2Phi = [-1.058, 0.300]
V_a2_Bs2Phi = [3.660, 1.538]
V_Bs2Phi_corr = [[1.0,0.485459,-0.346193],[0.485459,1.0,-0.210947],[-0.346193,-0.210947,1.0]]


##########################
## ***** Penguins ***** ##
##########################

### SU3-breaking ###
xi_su3 = [1, 0.20]
delta_su3 = [0, 20 * D2R]

### Transformations ###
def Abs_vs_Ang(Re, Im, makePos = False):
    # Make sure errors work in correct direction
    if (Re[0] < 0):
      ReP = Re[2] # ReLow will increase a
      ReM = Re[1] # ReHigh will decrease a
    else:
      ReP = Re[1]
      ReM = Re[2]
    if (Im[0] < 0):
      ImP = Im[2] # ImLow will increase a
      ImM = Im[1] # ImHigh will decrease a
    else:
      ImP = Im[1]
      ImM = Im[2]
    # Propagate Errors (Derivative Method)
    aVal = math.sqrt(pow(Re[0],2) + pow(Im[0],2))
    aHigh = math.sqrt(pow(Re[0] * ReP,2) + pow(Im[0] * ReP,2))/aVal
    aLow  = min(math.sqrt(pow(Re[0] * ReM,2) + pow(Im[0] * ImM,2))/aVal, aVal)
    thetaVal = math.atan2(Im[0], Re[0])
    thetaHigh = math.sqrt(pow(Im[0] * ReP,2) + pow(Re[0] * ImP,2))/pow(aVal,2)
    thetaLow  = math.sqrt(pow(Im[0] * ReM,2) + pow(Re[0] * ImM,2))/pow(aVal,2)
    if (thetaVal < 0 and makePos):
      thetaVal = thetaVal + 2 * math.pi
    return [aVal, aHigh, aLow], [thetaVal, thetaHigh, thetaLow]
    
def Re_vs_Im(aPar, thetaPar):
    ReVal = aPar[0] * math.cos(thetaPar[0])
    Re1 = math.sqrt(pow(aPar[1] * math.cos(thetaPar[0]),2) + pow(thetaPar[1] * aPar[0] * math.sin(thetaPar[0]),2))
    Re2 = math.sqrt(pow(aPar[2] * math.cos(thetaPar[0]),2) + pow(thetaPar[2] * aPar[0] * math.sin(thetaPar[0]),2))
    if ((thetaPar[0] > -90*D2R and thetaPar[0] < 90*D2R) or (thetaPar[0] > 270*D2R)):
      ReHigh = Re1
      ReLow = Re2
    else:
      ReHigh = Re2
      ReLow = Re1
    ImVal = aPar[0] * math.sin(thetaPar[0])
    Im1 = math.sqrt(pow(aPar[1] * math.sin(thetaPar[0]),2) + pow(thetaPar[1] * aPar[0] * math.cos(thetaPar[0]),2))
    Im2 = math.sqrt(pow(aPar[2] * math.sin(thetaPar[0]),2) + pow(thetaPar[2] * aPar[0] * math.cos(thetaPar[0]),2))
    if (thetaPar[0] > 0 and thetaPar[0] < 180*D2R):
      ImHigh = Im1
      ImLow = Im2
    else:
      ImHigh = Im2
      ImLow = Im1
    return [ReVal, ReHigh, ReLow], [ImVal, ImHigh, ImLow]

def DeltaShiftCS(Re, Im, Gam):
    # Make sure errors work in correct direction
    if (Re[0] < 0):
      ReP = Re[2] # ReLow will increase a
      ReM = Re[1] # ReHigh will decrease a
    else:
      ReP = Re[1]
      ReM = Re[2]
    if (Im[0] < 0):
      ImP = Im[2] # ImLow will increase a
      ImM = Im[1] # ImHigh will decrease a
    else:
      ImP = Im[1]
      ImM = Im[2]
    # Propagate Errors (Derivative Method)
    Norm = (1 + 2 * epsilon[0] * Re[0] * math.cos(Gam[0])\
            + pow(epsilon[0],2) * (pow(Re[0],2) + pow(Im[0],2)) * math.cos(2 * Gam[0]))
    Val = math.atan(\
            (2 * epsilon[0] * Re[0] * math.sin(Gam[0])\
            + pow(epsilon[0],2) * (pow(Re[0],2) + pow(Im[0],2)) * math.sin(2 * Gam[0]))/Norm)
    ReErr = 1 + (pow(Re[0],2) - pow(Im[0],2)) * pow(epsilon[0],2) + 2 * Re[0] * epsilon[0] * math.cos(Gam[0])
    ImErr = 2 * epsilon[0] * Im[0] * (Re[0] * epsilon[0] + math.cos(Gam[0]))
    EpsErr = Re[0]/epsilon[0] +  (pow(Re[0],2) + pow(Im[0],2)) * (Re[0] * epsilon[0] + math.cos(Gam[0]))
    GErr = (2 * epsilon[0] * pow(Re[0],2) + pow(pow(Re[0],2) + pow(Im[0],2),2) * pow(epsilon[0],3) + Re[0] * math.cos(Gam[0]) * (1\
           + 3 * (pow(Re[0],2) + pow(Im[0],2)) * pow(epsilon[0],2))\
           + epsilon[0] * math.cos(2 * Gam[0]) * (pow(Re[0],2) + pow(Im[0],2)))/math.sin(Gam[0])
    ErrHigh = 2 * epsilon[0] * math.sin(Gam[0]) * math.sqrt(pow(ReErr * ReP,2) + pow(ImErr * ImP,2)\
              + pow(EpsErr * epsilon[1],2) + pow(GErr * Gam[1],2))/pow(Norm,2)
    ErrLow  = 2 * epsilon[0] * math.sin(Gam[0]) * math.sqrt(pow(ReErr * ReM,2) + pow(ImErr * ImM,2)\
              + pow(EpsErr * epsilon[1],2) + pow(GErr * Gam[2],2))/pow(Norm,2)
    return [Val, ErrHigh, ErrLow]

def DeltaShiftCA(Re, Im, Gam):
    # Make sure errors work in correct direction
    if (Re[0] < 0):
      ReP = Re[2] # ReLow will increase a
      ReM = Re[1] # ReHigh will decrease a
    else:
      ReP = Re[1]
      ReM = Re[2]
    if (Im[0] < 0):
      ImP = Im[2] # ImLow will increase a
      ImM = Im[1] # ImHigh will decrease a
    else:
      ImP = Im[1]
      ImM = Im[2]
    # Propagate Errors (Derivative Method)
    Norm = (1 - 2 * Re[0] * math.cos(Gam[0]) + (pow(Re[0],2) + pow(Im[0],2)) * math.cos(2 * Gam[0]))
    Val = math.atan(\
            (-2 * Re[0] * math.sin(Gam[0]) + (pow(Re[0],2) + pow(Im[0],2)) * math.sin(2 * Gam[0]))/Norm)
    ReErr = 1 + (pow(Re[0],2) - pow(Im[0],2)) - 2 * Re[0] * math.cos(Gam[0])
    ImErr = 2 * Im[0] * (Re[0] - math.cos(Gam[0]))
    GErr = (-2 * pow(Re[0],2) - pow(pow(Re[0],2) + pow(Im[0],2),2) + Re[0] * math.cos(Gam[0]) * (1\
           + 3 * (pow(Re[0],2) + pow(Im[0],2)))\
           - math.cos(2 * Gam[0]) * (pow(Re[0],2) + pow(Im[0],2)))/math.sin(Gam[0])
    ErrHigh = 2 * math.sin(Gam[0]) * math.sqrt(pow(ReErr * ReP,2) + pow(ImErr * ImP,2)\
              + pow(GErr * Gam[1],2))/pow(Norm,2)
    ErrLow  = 2 * math.sin(Gam[0]) * math.sqrt(pow(ReErr * ReM,2) + pow(ImErr * ImM,2)\
              + pow(GErr * Gam[2],2))/pow(Norm,2)
    return [Val, ErrHigh, ErrLow]
