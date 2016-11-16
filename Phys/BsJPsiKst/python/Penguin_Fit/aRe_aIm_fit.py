###################################
## ***** Re[a] - Im[a] Fit ***** ##
###################################

### Macro written by Kristof De Bruyn for LHCb Bs->JpsiK* ANA note
# - Nominal Fit for Re[a] and Im[a] from the CP & H observables in Bs->JpsiK*


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

filename = "Bs2JpsiKstarFit.shelve"

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
def chi2(RePar, ImPar, GPar, model):
    chi2 = 0
    # Gamma Constraint
    if (GPar>=gamma[0]):
      chi2 = pow(GPar - gamma[0],2)/pow(gamma[2],2)
    else:
      chi2 = pow(GPar - gamma[0],2)/pow(gamma[1],2)
    # Longitudinal Polarisation
    if (model=="Long"):
      chi2 = chi2 + pow(theoAdirCA(RePar, ImPar, GPar) - AdirBs2JpsiKstar_Long[0],2)/pow(AdirBs2JpsiKstar_Long[1],2)\
             + pow(theoHobs(RePar, ImPar, GPar) - HBsKstarBsPhi_Long[0],2)/pow(HBsKstarBsPhi_Long[1],2)
    # Parallel Polarisation
    elif (model=="Para"):
      chi2 = chi2 + pow(theoAdirCA(RePar, ImPar, GPar) - AdirBs2JpsiKstar_Para[0],2)/pow(AdirBs2JpsiKstar_Para[1],2)\
             + pow(theoHobs(RePar, ImPar, GPar) - HBsKstarBsPhi_Para[0],2)/pow(HBsKstarBsPhi_Para[1],2)
    # Perpendicular Polarisation
    elif (model=="Perp"):
      chi2 = chi2 + pow(theoAdirCA(RePar, ImPar, GPar) - AdirBs2JpsiKstar_Perp[0],2)/pow(AdirBs2JpsiKstar_Perp[1],2)\
             + pow(theoHobs(RePar, ImPar, GPar) - HBsKstarBsPhi_Perp[0],2)/pow(HBsKstarBsPhi_Perp[1],2)
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
  m.values["RePar"] = 0.1
  m.values["ImPar"] = 0.02
  m.values["GPar"] = gamma[0]

  m.errors["RePar"] = 0.25
  m.errors["ImPar"] = 0.25
  m.errors["GPar"] = gamma[1]

  ### MIGRAD ###
  m.migrad()
  m.hesse()
  ReFit  = m.values["RePar"]
  ReSym  = m.errors["RePar"]
  ImFit  = m.values["ImPar"]
  ImSym  = m.errors["ImPar"]
  GamFit = m.values["GPar"]
  GamSym = m.errors["GPar"]
  bestchi2 = m.fval

  print "### MIGRAD results ###"
  print "  Re[a] = %.3f +/- %.3f" % (ReFit, ReSym)
  print "  Im[a] = %.3f +/- %.3f" % (ImFit, ImSym)
  print ""
  print "Init: gamma = [%.3f +/- %.3f] Rad" % (gamma[0],  gamma[1])
  print "      gamma = [%.3f +/- %.3f] Rad" % (GamFit,  GamSym)
  print "      gamma = [%.3f +/- %.3f] Deg" % (GamFit * R2D,  GamSym * R2D)
  print "fit info:", bestchi2, "(chi2)", m.ncalls, "(calls)", m.edm, "(edm)"
  print ""

  ### MINOS: Asymmetric Errors ###
  ReHigh = 0
  ReLow = 0
  ImHigh = 0
  ImLow = 0
  GamHigh = 0
  GamLow = 0
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
  except:
    print "FAILED: Extracting asymmetric errors"
    failed = True

  print "### MINOS results (CL 68.3%) ###"
  print "  Re[a] = %.3f + %.3f - %.3f" % (ReFit, ReHigh, ReLow)
  print "  Im[a] = %.3f + %.3f - %.3f" % (ImFit, ImHigh, ImLow)
  print "  gamma = [%.3f + %.3f - %.3f] Rad" % (GamFit, GamHigh, GamLow)
  print "  gamma = [%.3f + %.3f - %.3f] Deg" % (GamFit * R2D, GamHigh * R2D, GamLow * R2D)
  print ""
  print "### Converted MINOS results (CL 68.3%) ###"
  aPar, thetaPar = Abs_vs_Ang([ReFit, ReHigh, ReLow], [ImFit, ImHigh, ImLow], False)
  if (tag=="Long"):
    # This is a tweak: theta is unconstrained in these cases
    print "WARNING: Careful ... I'm cheating a bit here"
    thetaPar = [thetaPar[0], math.pi-thetaPar[0], thetaPar[0]+math.pi]
  print "      a = %.3f + %.3f - %.3f" % (aPar[0], aPar[1], aPar[2])
  print "  theta = [%.3f + %.3f - %.3f] Deg" % (thetaPar[0] * R2D, thetaPar[1] * R2D, thetaPar[2] * R2D)
  print "  theta = [%.3f + %.3f - %.3f] Rad" % (thetaPar[0], thetaPar[1], thetaPar[2])
  print ""
  print "### Transformed MINOS results (CL 68.3%) ###"
  if (failed==False):
    deltad = DeltaShiftCA([ReFit, ReHigh, ReLow], [ImFit, ImHigh, ImLow], [GamFit, GamHigh, GamLow])
  else:
    deltad = DeltaShiftCA([ReFit, ReSym, ReSym], [ImFit, ImSym, ImSym], [GamFit, GamSym, GamSym])
  print "  Delta_s (K*) = [%.3f + %.3f - %.3f] Deg" % (deltad[0] * R2D, deltad[1] * R2D, deltad[2] * R2D)
  print "  Delta_s (K*) = [%.3f + %.3f - %.3f] Rad" % (deltad[0], deltad[1], deltad[2])
  print ""
  if (failed==False):
    delta = DeltaShiftCS([ReFit, ReHigh, ReLow], [ImFit, ImHigh, ImLow], [GamFit, GamHigh, GamLow])
  else:
    delta = DeltaShiftCS([ReFit, ReSym, ReSym], [ImFit, ImSym, ImSym], [GamFit, GamSym, GamSym])
  print "  Delta_s = [%.3f + %.3f - %.3f] Deg" % (delta[0] * R2D, delta[1] * R2D, delta[2] * R2D)
  print "  Delta_s = [%.4f + %.4f - %.4f] Rad" % (delta[0], delta[1], delta[2])
  print ""

  shelf["ReFit_"+tag]  = ReFit
  shelf["ReSym_"+tag]  = ReSym
  shelf["ReHigh_"+tag] = ReHigh
  shelf["ReLow_"+tag]  = ReLow
  shelf["ImFit_"+tag]  = ImFit
  shelf["ImSym_"+tag]  = ImSym
  shelf["ImHigh_"+tag] = ImHigh
  shelf["ImLow_"+tag]  = ImLow
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
      numx = 1651
      numy = 801
    elif (tag=="Para"):
      numx = 1601
      numy = 901
    else:
      numx = 2001
      numy = 801
    for x in range(0, numx):
      for y in range(0, numy):
        if (tag=="Long"):
          ImScan = -0.05 + 0.00025 * y # range: -0.05 -> 0.15 = 0.2
          ReScan = -0.55 + 0.001 * x # range: -0.55 -> 1.1 = 1.65
        elif (tag=="Para"):
          ImScan = -0.35 + 0.0005 * y # range: -0.35 -> 0.10 = 0.45
          ReScan = -0.50 + 0.001 * x # range: -0.50 -> 1.1 = 1.60
        else:
          ImScan = -0.15 + 0.0005 * y # range: -0.15 -> 0.25 = 0.4
          ReScan = -0.9 + 0.001 * x # range: -0.9 -> 1.1 = 2.0
        if ((x%50==0) and (y==0)):
          print "Point", x, y
        # Calculate minimum wrt other parameters
        def chi2Grid(GScan):
          return myChi2(ReScan, ImScan, GScan)
        gr = minuit.Minuit(chi2Grid)
        gr.values["GScan"] = gamma[0]
        gr.errors["GScan"] = gamma[1]
        gr.migrad()
        GGrid = gr.values["GScan"]
        theChi2 = myChi2(ReScan,ImScan, GGrid)

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
for model in ["Long"]:
  #for model in ["Long", "Para", "Perp"]:
  print ""
  print "#################"
  print "### Model",model,"###"
  print "#################"
  print ""
  
  def myChi2(RePar, ImPar, GPar):
    return chi2(RePar, ImPar, GPar, model)
  doMinuit(myChi2, model, not test)

##########################
## ***** Finalise ***** ##
##########################
print_syserr()

# Close the file descriptors
os.close(fdLogErr)
