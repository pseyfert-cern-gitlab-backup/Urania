#######################################################
## ***** Plot Contours for Bs->JpsiK* Analysis ***** ##
#######################################################

### Macro written by Kristof De Bruyn for LHCb Bs->JpsiK* ANA note
# - Plots the contours from the CP observables in the Re[a] - Im[a] plane
# - Plots the contours from the CP observables in the theta - a plane
# - Overlay the fitted region


################################
## ***** Import Classes ***** ##
################################
import math
import numpy
import matplotlib
matplotlib.use('PDF')
import matplotlib.pyplot as pyplot

##################################
## ***** General Settings ***** ##
##################################

### For latex text ###
from matplotlib import rc
rc('text', usetex=True)

### Plot Settings ###
plotXMin = -1 # plot range
plotXMax = 1 # plot range
plotYMin = -1 # plot range
plotYMax = 1 # plot range
tick = 0.2 # tick separation

plotFMin = -180 # plot range
plotFMax = 180 # plot range
plotRMin = 0 # plot range
plotRMax = 1 # plot range
rtick = 0.1 # tick separation
ftick = 30 # tick separation

smallfont = 26 # fontsize small text
largefont = 30 # fontsize large text


#######################
## ***** Input ***** ##
#######################

import Inputs
from Inputs import *
import Branching_Ratio_Calculations
from Branching_Ratio_Calculations import * 
from Complex_Circle import *

### Load Fit Results ###
import shelve

#######################################
### Functions returning Coordinates ###
#######################################

def Calc_Input(mode, obs, sign, pol, phi = 0):
    # Calculate x0, y0 and radius for different inputs

    # STEP: Identify Inputs
    if (obs=="Adir"):
      if (mode=="Bs2JpsiKstar"):
        eps = 1
        shift = 0
        if (pol=="Long"):
          Adir = AdirBs2JpsiKstar_Long[0] + sign * AdirBs2JpsiKstar_Long[1]
        elif (pol=="Para"):
          Adir = AdirBs2JpsiKstar_Para[0] + sign * AdirBs2JpsiKstar_Para[1]
        else:
          Adir = AdirBs2JpsiKstar_Perp[0] + sign * AdirBs2JpsiKstar_Perp[1]
      else:
        print "ERROR:", obs, "not supported for mode", mode
        return []
      if (Adir==0):
        return [0, 0, 0]
      x0 = math.cos(shift) * math.cos(gamma[0])/eps
      y0 = math.cos(shift) * math.sin(gamma[0])/(eps * Adir)
      rad = math.fabs(math.sin(gamma[0]) * math.sqrt(1 - pow(Adir,2))/(eps * Adir))
    elif (obs=="Hobs"):
      if (mode=="Bs2JpsiKstar"):
        if (pol=="Long"):
          Hobs = HBsKstarBsPhi_Long[0] + sign * HBsKstarBsPhi_Long[1]
        elif (pol=="Para"):
          Hobs = HBsKstarBsPhi_Para[0] + sign * HBsKstarBsPhi_Para[1]
        else:
          Hobs = HBsKstarBsPhi_Perp[0] + sign * HBsKstarBsPhi_Perp[1]
      else:
        print "ERROR:", obs, "not supported for mode", mode
        return [] 
      x0 = -(epsilon[0] * Hobs + 1) * math.cos(gamma[0])/(pow(epsilon[0],2) * Hobs - 1)
      y0 = 0
      rad2 = (1 - Hobs)/(pow(epsilon[0],2) * Hobs - 1) + pow(x0,2)
      rad = 0 if (rad2 < 0) else math.sqrt(rad2)
    else:
      print "ERROR:", obs, "not supported"
    
    # STEP: Return
    #if (obs=="Amix"):
    #  print mode, obs, sign, "=>", x0, y0, rad
    return [x0, y0, rad]

### Simple Sorting of Fit Contours ###
def circle_sort(data):
    # Determine middle of circle
    xAv = sum(x[0] for x in data)/len(data)
    yAv = sum(x[1] for x in data)/len(data)

    # Sort Key
    def algo(x):
      ang = math.atan2(x[1] - yAv, x[0] - xAv)
      if (ang<0):
        ang = ang + 2 * math.pi
      return ang

    # Sort
    sortdata = sorted(data, key=algo)
    return sortdata

def mirror_circle_sort(data, xAv = 999, yAv = 999):
    # Determine middle of circle
    if (xAv==999):
      xAv = sum(x[0] for x in data)/len(data)
    if (yAv==999):
      yAv = sum(x[1] for x in data)/len(data)

    # Sort Key
    def algo(x):
      ang = math.pi + math.atan2(x[1] - yAv, x[0] - xAv)
      if (ang<0):
        ang = ang + 2 * math.pi
      return ang

    # Sort
    sortdata = sorted(data, key=algo)
    return sortdata

def split(data):
    xAv = sum(x[0] for x in data)/len(data)
    data1 = []
    data2 = []

    for x in data:
      if (x[0]<xAv):
        data1.append(x)
      else:
        data2.append(x)
    return data1, data2

###############################
## ***** Fix Artefacts ***** ##
###############################

def getLower(xData, yData, lbin, deg):
    # split in degrees
    xdegbin = [[] for x in range(deg)]
    ydegbin = [[] for x in range(deg)]
    for i in range(0, len(xData)):
      bin = int(math.floor((xData[i]-lbin)))
      xdegbin[bin].append(xData[i])
      ydegbin[bin].append(yData[i])
    
    # get lowest point
    lxData = []
    lyData = []
    for n in range(0, len(ydegbin)):
      y = ydegbin[n]
      x = xdegbin[n]
      if (len(y)>0):
        best = 0
        for i in range(0, len(y)):
          if (y[i]<y[best]):
            best = i
        lyData.append(y[best])
        lxData.append(x[best])

    return lxData, lyData

def fixArtefact(xData, yData):
    rxData = []
    ryData = []
    txData = []
    tyData = []
    fxData = []
    fyData = []

    # Split data
    for i in range(0, len(xData)):
      if (xData[i]<50 and i<len(xData)-10):
        rxData.append(xData[i])
        ryData.append(yData[i])
      elif (xData[i]>50 and xData[i]<105):
        fxData.append(xData[i])
        fyData.append(yData[i])
      else:
        txData.append(xData[i])
        tyData.append(yData[i])

    # fix middle section
    fxData, fyData = getLower(fxData, fyData, 50, 55)

    # glue
    rxData.extend(fxData)
    rxData.extend(txData)
    ryData.extend(fyData)
    ryData.extend(tyData)

    return rxData, ryData

###############################
## ***** Uncertainties ***** ##
###############################

def getExtrema(data):
    min = data[0]
    max = data[0]

    for x in data:
      if (x<min):
        min = x
      if (x>max):
        max = x
    return min, max

#############################
## ***** Make Figure ***** ##
#############################

def Make_Fit(tag, which):

    print ""
    print "#################"
    print "### Model",tag,"###"
    print "#################"
    print ""
    global plotFMin
    global plotFMax
    if (tag=="Perp"):
      plotFMin = 0 # plot range
      plotFMax = 360
      print "WARNING: Don't forget to change 'plotSplit' in 'Complex_Circle.py'"
      print ""
    
    if tag=="Long": pol = "0"
    elif tag=="Para": pol = "\parallel"
    elif tag=="Perp": pol = "\perp"
    else: pol = "?"

    ### Load Fit Results ###
    filename = "Bs2JpsiKstarFit.shelve"
    shelf = shelve.open(filename)
    try :
      # Fit Points
      ReFit = shelf["ReFit_"+tag]
      ImFit = shelf["ImFit_"+tag]
      ReHigh = shelf["ReHigh_"+tag]
      ImHigh = shelf["ImHigh_"+tag]
      ReLow = shelf["ReLow_"+tag]
      ImLow = shelf["ImLow_"+tag]
      aFit = shelf["aFit_"+tag]
      aHigh = shelf["aHigh_"+tag]
      aLow = shelf["aLow_"+tag]
      thetaFit = shelf["thetaFit_"+tag]
      thetaHigh = shelf["thetaHigh_"+tag]
      thetaLow = shelf["thetaLow_"+tag]
      DeltaFit = shelf["DeltaFit_"+tag]
      DeltaHigh = shelf["DeltaHigh_"+tag]
      DeltaLow = shelf["DeltaLow_"+tag]
      print "SUCCESS: Fit data found on shelve"
    except :
      print "FAILED: Unable to find data on shelve"
      return
    if (thetaFit>plotFMax):
      thetaFit = thetaFit - 2*math.pi
    if (thetaFit<plotFMin):
      thetaFit = thetaFit + 2*math.pi
    
    try:
      # Contours
      if (1==1):
        print "Contour: Using own scan results"
        gReIm39 = shelf["gReIm39_"+tag]
        gReIm68 = shelf["gReIm68_"+tag]
        gReIm90 = shelf["gReIm90_"+tag]
        if (tag=="Perp"):
          gReIm39, ggReIm39 = split(gReIm39)
          cReIm39 = circle_sort(gReIm39)
          ccReIm39 = circle_sort(ggReIm39)

          gReIm68, ggReIm68 = split(gReIm68)
          cReIm68 = circle_sort(gReIm68)
          ccReIm68 = circle_sort(ggReIm68)
        
          data1, data2 = split(gReIm90)
          sdata1 = circle_sort(data1)
          sdata2 = mirror_circle_sort(data2)
          sdata2.extend(sdata1)
          cReIm90 = sdata2
        else :
          cReIm39 = circle_sort(gReIm39)
          cReIm68 = circle_sort(gReIm68)
          cReIm90 = circle_sort(gReIm90)
      else:
        print "Contour: Using default minuit results"
        cReIm39 = shelf["cReIm39_"+tag]
        cReIm68 = shelf["cReIm68_"+tag]
        cReIm90 = shelf["cReIm90_"+tag]        
      print "SUCCESS: Contours found on shelve"
    except :
      print "FAILED: Unable to find contours on shelve"
      return

    ### Contours ###
    # (1) Calculate contours for central, plus 1 sigma, minus 1 sigma
    # (2) Calculate Re vs Im error band
    # (3) Calculate Ang vs Abs error band
    # (4) Transform to DeltaPhid contours for central, plus 1 sigma, minus 1 sigma
    
    print "### Calculating Contour Coordinates ###"

    print "Adir(Bs->JpsiKstar)"
    Adir_BsK_xcoor_c, Adir_BsK_ycoor_c, Adir_BsK_rcoor_c, Adir_BsK_fcoor_c = Gen_Contour(Calc_Input("Bs2JpsiKstar","Adir", 0, tag))
    Adir_BsK_xcoor_p, Adir_BsK_ycoor_p, Adir_BsK_rcoor_p, Adir_BsK_fcoor_p = Gen_Contour(Calc_Input("Bs2JpsiKstar","Adir",+1, tag))
    Adir_BsK_xcoor_m, Adir_BsK_ycoor_m, Adir_BsK_rcoor_m, Adir_BsK_fcoor_m = Gen_Contour(Calc_Input("Bs2JpsiKstar","Adir",-1, tag))
    # Circles are non-concentric (in some cases)
    Adir_BsK_xcoor_p_inv, Adir_BsK_ycoor_p_inv = Morph_Invert(Adir_BsK_xcoor_p, Adir_BsK_ycoor_p)
    if (tag=="Para"):
      Adir_BsK_xband, Adir_BsK_yband = Gen_Circle(Adir_BsK_xcoor_m, Adir_BsK_ycoor_m, Adir_BsK_xcoor_p, Adir_BsK_ycoor_p)
      Adir_BsK_rband, Adir_BsK_fband = Gen_Band(Adir_BsK_rcoor_m, Adir_BsK_fcoor_m, "A", Adir_BsK_rcoor_p, Adir_BsK_fcoor_p, "A")
    else:
      Adir_BsK_xband, Adir_BsK_yband = Gen_Circle(Adir_BsK_xcoor_m, Adir_BsK_ycoor_m, Adir_BsK_xcoor_p_inv, Adir_BsK_ycoor_p_inv)
      Adir_BsK_rband, Adir_BsK_fband = Gen_Band(Adir_BsK_rcoor_m, Adir_BsK_fcoor_m, "G", Adir_BsK_rcoor_p, Adir_BsK_fcoor_p, "G")

    print "Hobs(Bs->JpsiKstar)"
    Hobs_BsK_xcoor_c, Hobs_BsK_ycoor_c, Hobs_BsK_rcoor_c, Hobs_BsK_fcoor_c = Gen_Contour(Calc_Input("Bs2JpsiKstar","Hobs", 0, tag))
    Hobs_BsK_xcoor_p, Hobs_BsK_ycoor_p, Hobs_BsK_rcoor_p, Hobs_BsK_fcoor_p = Gen_Contour(Calc_Input("Bs2JpsiKstar","Hobs",+1, tag))
    Hobs_BsK_xcoor_m, Hobs_BsK_ycoor_m, Hobs_BsK_rcoor_m, Hobs_BsK_fcoor_m = Gen_Contour(Calc_Input("Bs2JpsiKstar","Hobs",-1, tag))
    Hobs_BsK_xband, Hobs_BsK_yband = Gen_Circle(Hobs_BsK_xcoor_m, Hobs_BsK_ycoor_m, Hobs_BsK_xcoor_p, Hobs_BsK_ycoor_p)
    if (tag=="Perp"):
      Hobs_BsK_rband, Hobs_BsK_fband = Gen_Band(Hobs_BsK_rcoor_p, Hobs_BsK_fcoor_p, "A", Hobs_BsK_rcoor_m, Hobs_BsK_fcoor_m, "C")
    else:
      Hobs_BsK_rband, Hobs_BsK_fband = Gen_Band(Hobs_BsK_rcoor_p, Hobs_BsK_fcoor_p, "C", Hobs_BsK_rcoor_m, Hobs_BsK_fcoor_m, "Bup")

    print "Visual Radius"
    xref, yref, rref, fref = Gen_Contour([0,0,plotRad])
    dref = Morph_DeltaPhi(rref, fref, epsilon[0], gamma[0])

    ### Fit Contours ###
    ReIm39 = zip(*cReIm39)
    Re39 = list(ReIm39[0])
    Re39.append(Re39[0])
    Im39 = list(ReIm39[1])
    Im39.append(Im39[0])
    Abs39, Ang39 = Morph_Fit(Re39, Im39)

    if (tag=="Perp"):
      ReIm39II = zip(*ccReIm39)
      Re39II = list(ReIm39II[0])
      Re39II.append(Re39II[0])
      Im39II = list(ReIm39II[1])
      Im39II.append(Im39II[0])
      Abs39II, Ang39II = Morph_Fit(Re39II, Im39II, "Inverse")
      # Tweak: remove first two points
      Abs39II.pop(0)
      Abs39II.pop(0)
      Ang39II.pop(0)
      Ang39II.pop(0)

    ReIm68 = zip(*cReIm68)
    Re68 = list(ReIm68[0])
    Re68.append(Re68[0])
    Im68 = list(ReIm68[1])
    Im68.append(Im68[0])
    Abs68, Ang68 = Morph_Fit(Re68, Im68)

    if (tag=="Perp"):
      ReIm68II = zip(*ccReIm68)
      Re68II = list(ReIm68II[0])
      Re68II.append(Re68II[0])
      Im68II = list(ReIm68II[1])
      Im68II.append(Im68II[0])
      Abs68II, Ang68II = Morph_Fit(Re68II, Im68II, "Inverse")

    ReIm90 = zip(*cReIm90)
    Re90 = list(ReIm90[0])
    Re90.append(Re90[0])
    Im90 = list(ReIm90[1])
    Im90.append(Im90[0])
    Abs90, Ang90 = Morph_Fit(Re90, Im90)
    
    if (tag=="Perp"):
      Ang90, Abs90 = fixArtefact(Ang90, Abs90)

    ### Legend Entries ###
    leg_Adir_Bs2JpsiKstar = matplotlib.patches.Rectangle((0, 0), 1, 1, facecolor='lightblue',  edgecolor='blue')
    leg_Hobs_Bs2JpsiKstar = matplotlib.patches.Rectangle((0, 0), 1, 1, facecolor='khaki',      edgecolor='orange')

    legEntries = [leg_Adir_Bs2JpsiKstar, leg_Hobs_Bs2JpsiKstar]
    if tag=="Long":
      legText = [r"$A^{\mathrm{CP}}_{0}(B_s^0\rightarrow J/\psi \kern 0.18em\overline{\kern -0.18em K}^{*0})$",\
                 r"$H_{0}(B_s^0\rightarrow J/\psi \kern 0.18em\overline{\kern -0.18em K}^{*0})$"]
    elif tag=="Para":
      legText = [r"$A^{\mathrm{CP}}_{\parallel}(B_s^0\rightarrow J/\psi \kern 0.18em\overline{\kern -0.18em K}^{*0})$",\
                 r"$H_{\parallel}(B_s^0\rightarrow J/\psi \kern 0.18em\overline{\kern -0.18em K}^{*0})$"]
    elif tag=="Perp":
      legText = [r"$A^{\mathrm{CP}}_{\perp}(B_s^0\rightarrow J/\psi \kern 0.18em\overline{\kern -0.18em K}^{*0})$",\
                 r"$H_{\perp}(B_s^0\rightarrow J/\psi \kern 0.18em\overline{\kern -0.18em K}^{*0})$"]
    else:
      legText = [r"$A^{\mathrm{CP}}(B_s^0\rightarrow J/\psi \kern 0.18em\overline{\kern -0.18em K}^{*0})$",\
                 r"$H(B_s^0\rightarrow J/\psi \kern 0.18em\overline{\kern -0.18em K}^{*0})$"]

    ### Fit Results ###
    if (tag=="Para" or tag=="Perp"):
      tmin, tmax = getExtrema(Ang39)
      thetaLow = thetaFit - tmin * D2R
      thetaHigh = tmax * D2R - thetaFit
      print thetaFit, thetaHigh, thetaLow
      print thetaFit * R2D, thetaHigh * R2D, thetaLow * R2D


    leg_dummy = matplotlib.patches.Rectangle((0, 0), 1, 1, facecolor='white', edgecolor='white')
    leg_c39 = matplotlib.patches.Rectangle((0, 0), 1, 1, facecolor='white', edgecolor='black', hatch='xxx')
    leg_c68 = matplotlib.patches.Rectangle((0, 0), 1, 1, facecolor='white', edgecolor='black')
    leg_c90 = matplotlib.patches.Rectangle((0, 0), 1, 1, facecolor='white', edgecolor='black', linestyle='dashed')
    fitEntries = [leg_dummy, leg_dummy, leg_c39, leg_c68, leg_c90]
    
    if (math.fabs(ReHigh-ReLow)<0.01):
      reresult = "%.2f \pm %.2f" % (ReFit, ReHigh)
    else:
      reresult = "%.2f^{+%.2f}_{-%.2f}" % (ReFit, ReHigh, ReLow)
    if (math.fabs(ImHigh-ImLow)<0.001):
      imresult = "%.3f \pm %.3f" % (ImFit, ImHigh)
    else:
      imresult = "%.3f^{+%.3f}_{-%.3f}" % (ImFit, ImHigh, ImLow)
    if (math.fabs(aHigh-aLow)<0.01):
      aresult = "%.2f \pm %.2f" % (aFit, aHigh)
    else:
      aresult = "%.2f^{+%.2f}_{-%.2f}" % (aFit, aHigh, aLow)
    if (math.fabs(thetaHigh-thetaLow)*R2D<1.):
      if (thetaFit<0):
        thetaresult = "-(%.0f \pm %.0f" % (-thetaFit * R2D, thetaHigh * R2D)
      else:
        thetaresult = "(%.0f \pm %.0f" % (thetaFit * R2D, thetaHigh * R2D)
    else:
      if (thetaFit<0):
        thetaresult = "-(%.0f^{+%.0f}_{-%.0f}" % (-thetaFit * R2D, thetaLow * R2D, thetaHigh * R2D)
      else:
        thetaresult = "(%.0f^{+%.0f}_{-%.0f}" % (thetaFit * R2D, thetaHigh * R2D, thetaLow * R2D)
    if (math.fabs(DeltaHigh-DeltaLow)*R2D<0.01):
      deltaresult = "%.2f \pm %.2f" % (DeltaFit * R2D, DeltaHigh * R2D)
    else:
      deltaresult = "%.2f^{+%.2f}_{-%.2f}" % (DeltaFit * R2D, DeltaHigh * R2D, DeltaLow * R2D)
    AbsText = [r"$a_{"+pol+"}="+aresult+"$", r"$\theta_{"+pol+"} = "+thetaresult+")^{\circ}$",
               r"$\mathrm{39\:\%~C.L.}$", r"$\mathrm{68\:\%~C.L.}$", r"$\mathrm{90\:\%~C.L.}$"]
    ReImText = [r"$\mathcal{R}\mathrm{e}[a_{"+pol+"}] ="+reresult+"$", r"$\mathcal{I}\mathrm{m}[a_{"+pol+"}] = "+imresult+"$",
                r"$\mathrm{39\:\%~C.L.}$", r"$\mathrm{68\:\%~C.L.}$", r"$\mathrm{90\:\%~C.L.}$"]


    ### FIGURE 1 ###
    if 'Re' in which:
      print "=== Plotting Penguin Contribution: Re vs Im:", tag, "==="
      theFig = pyplot.figure(figsize=(12, 12), facecolor='white')

      ### Fill Regions ###
      pyplot.fill(Hobs_BsK_xband, Hobs_BsK_yband, color='khaki',       edgecolor='khaki')
      pyplot.fill(Adir_BsK_xband, Adir_BsK_yband, color='lightblue',   edgecolor='lightblue')

      ### Curves ###
      pyplot.plot(Adir_BsK_xcoor_c, Adir_BsK_ycoor_c, '-', lw=2, color='blue')
      pyplot.plot(Adir_BsK_xcoor_p, Adir_BsK_ycoor_p, '-', lw=1, color='blue')
      pyplot.plot(Adir_BsK_xcoor_m, Adir_BsK_ycoor_m, '-', lw=1, color='blue')

      pyplot.plot(Hobs_BsK_xcoor_c, Hobs_BsK_ycoor_c, '-', lw=2, color='orange')
      pyplot.plot(Hobs_BsK_xcoor_p, Hobs_BsK_ycoor_p, '-', lw=1, color='orange')
      pyplot.plot(Hobs_BsK_xcoor_m, Hobs_BsK_ycoor_m, '-', lw=1, color='orange')

      ### Fit Contours ###
      pyplot.plot(ReFit, ImFit, marker='o', markerfacecolor='black', markersize=5)
      pyplot.plot(Re39, Im39, '-',  lw=1.5, color='black',zorder=1)
      pyplot.fill(Re39, Im39, color='none', hatch='xx', edgecolor='black')
      if (tag=="Perp"):
        pyplot.plot(Re39II, Im39II, '-',  lw=1.5, color='black',zorder=1)
        pyplot.fill(Re39II, Im39II, color='none', hatch='xx', edgecolor='black')
      pyplot.plot(Re68, Im68, '-',  lw=1.5, color='black',zorder=1)
      if (tag=="Perp"):
        pyplot.plot(Re68II, Im68II, '-',  lw=1.5, color='black',zorder=1)
      pyplot.plot(Re90, Im90, '--', lw=1.5, color='black',zorder=1)
      xout = xref
      xout.extend([plotXMax, plotXMax, plotXMin, plotXMin, plotXMax, plotXMax])
      yout = yref
      yout.extend([0, plotYMin, plotYMin, plotYMax, plotYMax, 0])
      pyplot.fill(xout, yout, color='white', edgecolor='black',zorder=2)

      ### Axes ###
      pyplot.plot(xref, yref, '-', lw=1, color='black')
      pyplot.plot([plotXMin, plotXMax], [0, 0], '-', lw=1, color='black')
      pyplot.plot([0, 0], [plotYMin, plotYMax], '-', lw=1, color='black')
    
      ### Legend ###
      leg = pyplot.legend(legEntries, legText, loc=1)
      for t in leg.get_texts():
        t.set_fontsize(smallfont) 
    
      fit = pyplot.legend(fitEntries, ReImText, loc=2)
      for t in fit.get_texts():
        t.set_fontsize(smallfont)
      # get back the first legend
      pyplot.gca().add_artist(leg)

      pyplot.text(plotXMax-0.05, plotYMin+0.05, r'$\mathrm{LHCb}$',
        fontsize=largefont, horizontalalignment='right', verticalalignment='bottom')

      ### Axes ###
      pyplot.xticks(numpy.arange(plotXMin, plotXMax + tick, tick), fontsize=smallfont)
      pyplot.subplot(111).xaxis.set_ticks(numpy.arange(plotXMin, plotXMax + tick, 0.05), True)
      pyplot.subplot(111).xaxis.set_tick_params(which='major', length=10)
      pyplot.subplot(111).xaxis.set_tick_params(which='minor', length=6)
      pyplot.yticks(numpy.arange(plotYMin, plotYMax + tick, tick), fontsize=smallfont)
      pyplot.subplot(111).yaxis.set_ticks(numpy.arange(plotYMin, plotYMax + tick, 0.05), True)
      pyplot.subplot(111).yaxis.set_tick_params(which='major', length=10)
      pyplot.subplot(111).yaxis.set_tick_params(which='minor', length=6)
      pyplot.axis([plotXMin, plotXMax, plotYMin, plotYMax])
      pyplot.xlabel(r"$\mathcal{R}\mathrm{e}[a_{"+pol+"}]$",fontsize=largefont)
      pyplot.ylabel(r"$\mathcal{I}\mathrm{m}[a_{"+pol+"}]$",fontsize=largefont)

      ### Save ###
      savestring = "Plots/Penguin_Contribution_Re_vs_Im_Bs2JpsiKstar_"+tag
      pyplot.savefig(savestring, bbox_inches='tight')


    ### FIGURE 2 ###
    if 'Abs' in which:
      print "=== Plotting Penguin Contribution: Ang vs Abs:", tag, "==="
      theFig = pyplot.figure(figsize=(12, 8), facecolor='white')

      ### Fill Regions ###
      pyplot.fill(Hobs_BsK_fband, Hobs_BsK_rband, color='khaki',       edgecolor='khaki')
      pyplot.fill(Adir_BsK_fband, Adir_BsK_rband, color='lightblue',   edgecolor='lightblue')

      ### Curves ###
      pyplot.plot(Adir_BsK_fcoor_c, Adir_BsK_rcoor_c, '-', lw=2, color='blue')
      pyplot.plot(Adir_BsK_fcoor_p, Adir_BsK_rcoor_p, '-', lw=1, color='blue')
      pyplot.plot(Adir_BsK_fcoor_m, Adir_BsK_rcoor_m, '-', lw=1, color='blue')

      pyplot.plot(Hobs_BsK_fcoor_c, Hobs_BsK_rcoor_c, '-', lw=2, color='orange')
      pyplot.plot(Hobs_BsK_fcoor_p, Hobs_BsK_rcoor_p, '-', lw=1, color='orange')
      pyplot.plot(Hobs_BsK_fcoor_m, Hobs_BsK_rcoor_m, '-', lw=1, color='orange')

      ### Fit Contours ###
      pyplot.plot(thetaFit * R2D, aFit, marker='o', markerfacecolor='black', markersize=5)
      pyplot.plot(Ang39, Abs39, '-',  lw=1.5, color='black')
      pyplot.fill(Ang39, Abs39, color='none', hatch='xx', edgecolor='black')
      if (tag=="Perp"):
        pyplot.plot(Ang39II, Abs39II, '-',  lw=1.5, color='black')
        pyplot.fill(Ang39II, Abs39II, color='none', hatch='xx', edgecolor='black')
      pyplot.plot(Ang68, Abs68, '-',  lw=1.5, color='black')
      if (tag=="Perp"):
        pyplot.plot(Ang68II, Abs68II, '-',  lw=1.5, color='black')
      pyplot.plot(Ang90, Abs90, '--', lw=1.5, color='black')

      ### Legend ###
      leg = pyplot.legend(legEntries, legText, loc=1)
      for t in leg.get_texts():
        t.set_fontsize(smallfont)
    
      fit = pyplot.legend(fitEntries, AbsText, loc=2)
      for t in fit.get_texts():
        t.set_fontsize(smallfont)
      # get back the first legend
      pyplot.gca().add_artist(leg)

      pyplot.text(plotFMax-20, plotRMax-0.25, r'$\mathrm{LHCb}$',
        fontsize=largefont, horizontalalignment='right', verticalalignment='top')

      ### Axes ###
      pyplot.xticks(numpy.arange(plotFMin, plotFMax + ftick, ftick), fontsize=0.80*smallfont)
      pyplot.subplot(111).xaxis.set_ticks(numpy.arange(plotFMin, plotFMax + ftick, ftick/6), True)
      pyplot.subplot(111).xaxis.set_tick_params(which='major', length=10)
      pyplot.subplot(111).xaxis.set_tick_params(which='minor', length=6)
      pyplot.yticks(numpy.arange(plotRMin, plotRMax + rtick, rtick), fontsize=smallfont)
      pyplot.subplot(111).yaxis.set_ticks(numpy.arange(plotRMin, plotRMax + rtick, rtick/5), True)
      pyplot.subplot(111).yaxis.set_tick_params(which='major', length=10)
      pyplot.subplot(111).yaxis.set_tick_params(which='minor', length=6)
      pyplot.axis([plotFMin, plotFMax, plotRMin, plotRMax])
      pyplot.xlabel(r"$\theta_{"+pol+"}\:[\mathrm{deg}]$",fontsize=largefont)
      pyplot.ylabel(r"$a_{"+pol+"}$",fontsize=largefont)

      ### Save ###
      savestring = "Plots/Penguin_Contribution_Ang_vs_Abs_Bs2JpsiKstar_"+tag
      pyplot.savefig(savestring, bbox_inches='tight')


######################
## ***** Main ***** ##
######################

### Default ###
#Make_Fit("Long", "ReAbs")
#Make_Fit("Para", "ReAbs")
Make_Fit("Perp", "Abs")
