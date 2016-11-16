###################################
## ***** Re[a] - Im[a] Fit ***** ##
###################################

### Macro written by Kristof De Bruyn for LHCb Bs->JpsiK* ANA note
# - Nominal Fit for Re[a] and Im[a] from the CP & H observables in Bd->JpsiRho & Bs->JpsiK*


################################
## ***** Import Classes ***** ##
################################

import sys, os
import math
import numpy
import shelve

try:
    import minuit
except ImportError:
    print "ERROR: Unable to locate Minuit"


#######################
## ***** Input ***** ##
#######################

import Inputs
from Inputs import *
import Branching_Ratio_Calculations
from Branching_Ratio_Calculations import *


##################################
## ***** General Settings ***** ##
##################################

filename = "B2VVFit.shelve"

# file descriptors for logging Minuit output and switching back to stdout
fdLogErr = os.open( "minuit_err.log", os.O_RDWR|os.O_CREAT )
fdStdErr = os.dup(2)

# flags
logActive = False # True # toggle whether to log stderr outputs

# Confidence level values for MINUIT
n1cl90 = math.sqrt(2.71)
n1cl68 = math.sqrt(1.00)
n2cl95 = math.sqrt(5.99)
n2cl90 = math.sqrt(4.61)
n2cl68 = math.sqrt(2.30)
n2cl39 = math.sqrt(1.00)


###############################
## ***** Fit Functions ***** ##
###############################

def Norm(RePar, ImPar, GPar):
    return (1 - 2 * RePar * math.cos(GPar) + pow(RePar,2) + pow(ImPar,2))

def theoAdir(RePar, ImPar, GPar):
    return (2 * ImPar * math.sin(GPar))/Norm(RePar, ImPar, GPar)

def theoAmix(RePar, ImPar, GPar, FPar, eta):
    return eta * (math.sin(FPar) - 2 * RePar * math.sin(FPar + GPar)\
           + (pow(RePar,2) + pow(ImPar,2)) * math.sin(FPar + 2 * GPar))/Norm(RePar, ImPar, GPar)

def theoHobs(RePar, ImPar, GPar):
    return Norm(RePar, ImPar, GPar)/Norm(-epsilon[0] * RePar, -epsilon[0] * ImPar, GPar)

def theoBRinfo(RePar, ImPar, GPar, HadPar):
    return theoHobs(RePar, ImPar, GPar)/pow(HadPar,2)

# Easy accessors
def theoAdirCA(RePar, ImPar, GPar):
    return theoAdir(RePar, ImPar, GPar)

def theoAdirCS(RePar, ImPar, GPar):
    return theoAdir(-epsilon[0] * RePar, -epsilon[0] * ImPar, GPar)

def theoAmixCA(RePar, ImPar, GPar, FPar, eta):
    return theoAmix(RePar, ImPar, GPar, FPar, eta)

def theoAmixCS(RePar, ImPar, GPar, FPar, eta):
    return theoAmix(-epsilon[0] * RePar, -epsilon[0] * ImPar, GPar, FPar, eta)

# Chi2 Minimizer
def chi2(RePar, ImPar, HadPar, GPar, FPar, model):
    chi2 = 0
    # Gamma Constraint
    if (GPar>=gamma[0]):
      chi2 = pow(GPar - gamma[0],2)/pow(gamma[2],2)
    else:
      chi2 = pow(GPar - gamma[0],2)/pow(gamma[1],2)
    # Phi Constraint
    chi2 = chi2 + pow(FPar - Phid_wpen[0],2)/pow(Phid_wpen[1],2)
    # Longitudinal Polarisation
    if (model=="Long"):
      chi2 = chi2 + pow(theoAdirCA(RePar, ImPar, GPar) - AdirBd2JpsiRho_Long[0],2)/pow(AdirBd2JpsiRho_Long[1],2)\
             + pow(theoAmixCA(RePar, ImPar, GPar, FPar, 1) - AmixBd2JpsiRho_Long[0],2)/pow(AmixBd2JpsiRho_Long[1],2)\
             + pow(theoAdirCA(RePar, ImPar, GPar) - AdirBs2JpsiKstar_Long[0],2)/pow(AdirBs2JpsiKstar_Long[1],2)\
             + pow(theoBRinfo(RePar, ImPar, GPar, HadPar) - HextBsKstarBsPhi_Long[0],2)/pow(HextBsKstarBsPhi_Long[1],2)\
             + pow(theoBRinfo(RePar, ImPar, GPar, HadPar) - HextBdRhoBsPhi_Long[0],2)/pow(HextBdRhoBsPhi_Long[1],2)
    # Parallel Polarisation
    elif (model=="Para"):
      chi2 = chi2 + pow(theoAdirCA(RePar, ImPar, GPar) - AdirBd2JpsiRho_Para[0],2)/pow(AdirBd2JpsiRho_Para[1],2)\
             + pow(theoAmixCA(RePar, ImPar, GPar, FPar, 1) - AmixBd2JpsiRho_Para[0],2)/pow(AmixBd2JpsiRho_Para[1],2)\
             + pow(theoAdirCA(RePar, ImPar, GPar) - AdirBs2JpsiKstar_Para[0],2)/pow(AdirBs2JpsiKstar_Para[1],2)\
             + pow(theoBRinfo(RePar, ImPar, GPar, HadPar) - HextBsKstarBsPhi_Para[0],2)/pow(HextBsKstarBsPhi_Para[1],2)\
             + pow(theoBRinfo(RePar, ImPar, GPar, HadPar) - HextBdRhoBsPhi_Para[0],2)/pow(HextBdRhoBsPhi_Para[1],2)
    # Perpendicular Polarisation
    elif (model=="Perp"):
      chi2 = chi2 + pow(theoAdirCA(RePar, ImPar, GPar) - AdirBd2JpsiRho_Perp[0],2)/pow(AdirBd2JpsiRho_Perp[1],2)\
             + pow(theoAmixCA(RePar, ImPar, GPar, FPar, 1) - AmixBd2JpsiRho_Perp[0],2)/pow(AmixBd2JpsiRho_Perp[1],2)\
             + pow(theoAdirCA(RePar, ImPar, GPar) - AdirBs2JpsiKstar_Perp[0],2)/pow(AdirBs2JpsiKstar_Perp[1],2)\
             + pow(theoBRinfo(RePar, ImPar, GPar, HadPar) - HextBsKstarBsPhi_Perp[0],2)/pow(HextBsKstarBsPhi_Perp[1],2)\
             + pow(theoBRinfo(RePar, ImPar, GPar, HadPar) - HextBdRhoBsPhi_Perp[0],2)/pow(HextBdRhoBsPhi_Perp[1],2)
    return chi2

##################################
## ***** System Functions ***** ##
##################################

def log_syserr(logActive) : 
    """ Switch stderr to log files, if the input is True """
    if logActive :
        os.dup2(fdLogErr, 2)    # stderr
    return

def print_syserr() :
    """ Switch stderr back to system defaults"""
    os.dup2(fdStdErr, 2) # stderr
    return


############################
## ***** Minuit Fit ***** ##
############################

log_syserr(logActive)

def doMinuit(myChi2, tag, scan):
    
  ### Initialise ###
  shelf = shelve.open(filename)
  
  m = minuit.Minuit(myChi2)
  m.strategy = 2
  m.printMode = 0
  
  ### Set Initial Guess ###
  m.values["RePar"] = 0.05
  m.values["ImPar"] = -0.05
  m.values["GPar"] = gamma[0]
  m.values["FPar"] = Phid_wpen[0]
  m.values["HadPar"] = 1.07

  m.errors["RePar"] = 0.1
  m.errors["ImPar"] = 0.05
  m.errors["GPar"] = gamma[1]
  m.errors["FPar"] = Phid_wpen[1]
  m.errors["HadPar"] = 0.08

  ### MIGRAD ###
  m.migrad()
  m.hesse()
  ReFit  = m.values["RePar"]
  ReSym  = m.errors["RePar"]
  ImFit  = m.values["ImPar"]
  ImSym  = m.errors["ImPar"]
  GamFit = m.values["GPar"]
  GamSym = m.errors["GPar"]
  PhiFit = m.values["FPar"]
  PhiSym = m.errors["FPar"]
  HadFit = m.values["HadPar"]
  HadSym = m.errors["HadPar"]
  bestchi2 = m.fval

  print "### MIGRAD results ###"
  print "  Re[a] = %.3f +/- %.3f" % (ReFit, ReSym)
  print "  Im[a] = %.3f +/- %.3f" % (ImFit, ImSym)
  print " |A'/A| = %.3f +/- %.3f" % (HadFit, HadSym)
  print ""
  print "Init: gamma = [%.3f +/- %.3f] Rad" % (gamma[0],  gamma[1])
  print "      gamma = [%.3f +/- %.3f] Rad" % (GamFit,  GamSym)
  print "      gamma = [%.3f +/- %.3f] Deg" % (GamFit * R2D,  GamSym * R2D)
  print ""
  print "Init: phi = [%.3f +/- %.3f] Rad" % (Phid_wpen[0],  Phid_wpen[1])
  print "      phi = [%.3f +/- %.3f] Rad" % (PhiFit,  PhiSym)
  print "      phi = [%.3f +/- %.3f] Deg" % (PhiFit * R2D,  PhiSym * R2D)
  print "fit info:", bestchi2, "(chi2)", m.ncalls, "(calls)", m.edm, "(edm)"
  print ""

  ### MINOS: Asymmetric Errors ###
  ReHigh = 0
  ReLow = 0
  ImHigh = 0
  ImLow = 0
  GamHigh = 0
  GamLow = 0
  PhiHigh = 0
  PhiLow = 0
  HadHigh = 0
  HadLow = 0
  failed = False

  try:
    m.minos("RePar", n1cl68)
    ReHigh = m.merrors["RePar", n1cl68]
    m.minos("RePar", -n1cl68)
    ReLow = abs(m.merrors["RePar", -n1cl68])
    m.minos("ImPar", n1cl68)
    ImHigh = m.merrors["ImPar", n1cl68]
    m.minos("ImPar", -n1cl68)
    ImLow = abs(m.merrors["ImPar", -n1cl68])
    m.minos("GPar", n1cl68)
    GamHigh = m.merrors["GPar", n1cl68]
    m.minos("GPar", -n1cl68)
    GamLow = abs(m.merrors["GPar", -n1cl68])
    m.minos("FPar", n1cl68)
    PhiHigh = m.merrors["FPar", n1cl68]
    m.minos("FPar", -n1cl68)
    PhiLow = abs(m.merrors["FPar", -n1cl68])
    m.minos("HadPar", n1cl68)
    HadHigh = m.merrors["HadPar", n1cl68]
    m.minos("HadPar", -n1cl68)
    HadLow = abs(m.merrors["HadPar", -n1cl68])
  except:
    print "FAILED: Extracting asymmetric errors"
    failed = True

  print "### MINOS results (CL 68.3%) ###"
  print "  Re[a] = %.3f + %.3f - %.3f" % (ReFit, ReHigh, ReLow)
  print "  Im[a] = %.3f + %.3f - %.3f" % (ImFit, ImHigh, ImLow)
  print " |A'/A| = %.3f + %.3f - %.3f" % (HadFit, HadHigh, HadLow)
  print "  gamma = [%.3f + %.3f - %.3f] Rad" % (GamFit, GamHigh, GamLow)
  print "  gamma = [%.3f + %.3f - %.3f] Deg" % (GamFit * R2D, GamHigh * R2D, GamLow * R2D)
  print "    phi = [%.3f + %.3f - %.3f] Rad" % (PhiFit, PhiHigh, PhiLow)
  print "    phi = [%.3f + %.3f - %.3f] Deg" % (PhiFit * R2D, PhiHigh * R2D, PhiLow * R2D)
  print ""
  print "### Converted MINOS results (CL 68.3%) ###"
  aPar, thetaPar = Abs_vs_Ang([ReFit, ReHigh, ReLow], [ImFit, ImHigh, ImLow], False)
  if (tag=="Long" or tag=="Perp"):
    # This is a tweak: theta is unconstrained in these cases
    print "WARNING: Careful ... I'm cheating a bit here"
    thetaPar = [thetaPar[0], math.pi-thetaPar[0], thetaPar[0]+math.pi]
  print "      a = %.3f + %.3f - %.3f" % (aPar[0], aPar[1], aPar[2])
  print "  theta = [%.3f + %.3f - %.3f] Deg" % (thetaPar[0] * R2D, thetaPar[1] * R2D, thetaPar[2] * R2D)
  print "  theta = [%.3f + %.3f - %.3f] Rad" % (thetaPar[0], thetaPar[1], thetaPar[2])
  print ""
  print "### Transformed MINOS results (CL 68.3%) ###"
  if (failed==False):
    delta = DeltaShiftCS([ReFit, ReHigh, ReLow], [ImFit, ImHigh, ImLow], [GamFit, GamHigh, GamLow])
  else:
    delta = DeltaShiftCS([ReFit, ReSym, ReSym], [ImFit, ImSym, ImSym], [GamFit, GamSym, GamSym])
  print "  Delta = [%.3f + %.3f - %.3f] Deg" % (delta[0] * R2D, delta[1] * R2D, delta[2] * R2D)
  print "  Delta = [%.3f + %.3f - %.3f] Rad" % (delta[0], delta[1], delta[2])
  print ""

  shelf["ReFit_"+tag]  = ReFit
  shelf["ReSym_"+tag]  = ReSym
  shelf["ReHigh_"+tag] = ReHigh
  shelf["ReLow_"+tag]  = ReLow
  shelf["ImFit_"+tag]  = ImFit
  shelf["ImSym_"+tag]  = ImSym
  shelf["ImHigh_"+tag] = ImHigh
  shelf["ImLow_"+tag]  = ImLow
  shelf["HadFit_"+tag]  = HadFit
  shelf["HadSym_"+tag]  = HadSym
  shelf["HadHigh_"+tag] = HadHigh
  shelf["HadLow_"+tag]  = HadLow
  shelf["aFit_"+tag]  = aPar[0]
  shelf["aHigh_"+tag] = aPar[1]
  shelf["aLow_"+tag]  = aPar[2]
  shelf["thetaFit_"+tag]  = thetaPar[0]
  shelf["thetaHigh_"+tag] = thetaPar[1]
  shelf["thetaLow_"+tag]  = thetaPar[2]
  shelf["DeltaFit_"+tag]  = delta[0]
  shelf["DeltaHigh_"+tag] = delta[1]
  shelf["DeltaLow_"+tag]  = delta[2]
  shelf["GamFit_"+tag]  = GamFit
  shelf["GamSym_"+tag]  = GamSym
  shelf["GamHigh_"+tag] = GamHigh
  shelf["GamLow_"+tag]  = GamLow
  shelf["PhidFit_"+tag]  = PhiFit
  shelf["PhidSym_"+tag]  = PhiSym
  shelf["PhidHigh_"+tag] = PhiHigh
  shelf["PhidLow_"+tag]  = PhiLow
  
  m.printMode = 0
  if scan:
    ### Fit Contours ###
    try:
      shelf["cReIm39_"+tag] = m.contour("RePar", "ImPar", n2cl39, 100)
      shelf["cReIm68_"+tag] = m.contour("RePar", "ImPar", n2cl68, 100)
      shelf["cReIm90_"+tag] = m.contour("RePar", "ImPar", n2cl90, 100)
    except:
      print "FAILED: Determining Confidence Contours"
  
    print "The Grid"
    print ""
    gReIm39 = []
    gReIm68 = []
    gReIm90 = []
    accur = 1 * pow(10,-2)
    if (tag=="Long"):
      numx = 1301
      numy = 601
    elif (tag=="Para"):
      numx = 1351
      numy = 1001
    else:
      numx = 1401
      numy = 1001
    for x in range(0, numx):
      for y in range(0, numy):
        if ((x%50==0) and (y==0)):
          print "Point", x, y
        if (tag=="Long"):
          ImScan = -0.15 + 0.0005 * y # range: -0.15 -> 0.15 = 0.30
          ReScan = -1.1 + 0.001 * x # range: -1.1 -> 0.2 = 1.3
          if ((ImScan<-0.10 or ImScan>0.10) and ReScan>-0.8):
            continue
        elif (tag=="Perp"):
          ImScan = -0.2 + 0.0005 * y # range: -0.2 -> 0.3 = 0.5
          ReScan = -1.1 + 0.001 * x # range: -1.1 -> 0.3 = 1.4
          if (ImScan>0.2 and ReScan>-0.7):
            continue
        else:
          ImScan = -0.45 + 0.0005 * y # range: -0.45 -> 0.05 = 0.50
          ReScan = -1.1 + 0.001 * x # range: -1.1 -> 0.25 = 1.35
          if (ImScan<-0.35 and ReScan>-0.6):
            continue
          if (ImScan<-0.30 and ReScan>-0.4):
            continue
        # Calculate minimum wrt other parameters
        def chi2Grid(HScan, GScan, FScan):
          return myChi2(ReScan, ImScan, HScan, GScan, FScan)
        gr = minuit.Minuit(chi2Grid)
        gr.values["GScan"] = gamma[0]
        gr.errors["GScan"] = gamma[1]
        gr.values["FScan"] = Phid_wpen[0]
        gr.errors["FScan"] = Phid_wpen[1]
        gr.values["HScan"] = 1.07
        gr.errors["HScan"] = 0.08
        gr.migrad()
        GGrid = gr.values["GScan"]
        FGrid = gr.values["FScan"]
        HGrid = gr.values["HScan"]
        theChi2 = myChi2(ReScan,ImScan, HGrid, GGrid, FGrid)

        if (math.fabs(theChi2 - bestchi2 - pow(n2cl39,2)) < accur):
          gReIm39.append((ReScan, ImScan))
        if (math.fabs(theChi2 - bestchi2 - pow(n2cl68,2)) < accur):
          gReIm68.append((ReScan, ImScan))
        if (math.fabs(theChi2 - bestchi2 - pow(n2cl90,2)) < accur):
          gReIm90.append((ReScan, ImScan))

    shelf["gReIm39_"+tag] = gReIm39
    shelf["gReIm68_"+tag] = gReIm68
    shelf["gReIm90_"+tag] = gReIm90

  shelf.close()
  return

######################
## ***** Main ***** ##
######################

test = False

#for model in ["Long", "Para", "Perp"]:
for model in ["Long", "Para"]:
  print ""
  print "#################"
  print "### Model",model,"###"
  print "#################"
  print ""

  def myChi2(RePar, ImPar, HadPar, GPar, FPar):
    return chi2(RePar, ImPar, HadPar, GPar, FPar, model)
  doMinuit(myChi2, model, not test)

##########################
## ***** Finalise ***** ##
##########################
print_syserr()

# Close the file descriptors
os.close(fdLogErr)
