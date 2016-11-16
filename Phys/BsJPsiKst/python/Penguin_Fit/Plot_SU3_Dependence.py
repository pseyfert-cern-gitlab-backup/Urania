##############################################################
## ***** About SU(3)-Breaking for Bs->JpsiK* Analysis ***** ##
##############################################################

### Macro written by Kristof De Bruyn for LHCb Bs->JpsiK* ANA note
# - Plots the uncertainty on DeltaPhis versus the uncertainty on xi


################################
## ***** Import Classes ***** ##
################################
import math
import numpy
import matplotlib
matplotlib.use('PDF')
#matplotlib.use('PS')
import matplotlib.pyplot as pyplot

##################################
## ***** General Settings ***** ##
##################################

### For latex text ###
from matplotlib import rc
rc('text', usetex=True)

### Plot Settings ###
plotXMin = 0 # plot range
plotXMax = 50 # plot range
plotYMin = -0.10 # plot range
plotYMax = 0.15 # plot range
xtick = 5 # tick separation
ytick = 0.05 # tick separation

smallfont = 26 # fontsize small text
largefont = 30 # fontsize large text


#######################
## ***** Input ***** ##
#######################

import Inputs
from Inputs import *

### Load Fit Results ###
import shelve


#############################
## ***** Make Figure ***** ##
#############################

def Make_Fit(tag):
  
    print "### Plotting for", tag, "###"
  
    if tag=="Long": pol = "0"
    elif tag=="Para": pol = "\parallel"
    elif tag=="Perp": pol = "\perp"
    else: pol = "?"

    ### Load Fit Results ###
    xcoor = []

    hcoor_delta10 = []
    ccoor_delta10 = []
    lcoor_delta10 = []

    hcoor_delta20 = []
    ccoor_delta20 = []
    lcoor_delta20 = []

    hcoor_delta30 = []
    ccoor_delta30 = []
    lcoor_delta30 = []

    shelf = shelve.open("Bs2JpsiKstarFit_wSU3.shelve")
    
    prev = 0
    for x in range(0,51):
      xi_err = 0.01 * x
      xcoor.append(100*xi_err)
      
      fittag = tag+"_xi"+str(int(100*xi_err))+"_delta10"
      DeltaFit = shelf["DeltaFit_"+fittag]
      DeltaHigh = shelf["DeltaHigh_"+fittag]
      DeltaLow = shelf["DeltaLow_"+fittag]
      hcoor_delta10.append(DeltaFit+DeltaHigh)
      ccoor_delta10.append(DeltaFit)
      lcoor_delta10.append(DeltaFit-DeltaLow)

      fittag = tag+"_xi"+str(int(100*xi_err))+"_delta20"
      DeltaFit = shelf["DeltaFit_"+fittag]
      DeltaHigh = max(prev,shelf["DeltaHigh_"+fittag]) # cheating
      prev = DeltaHigh
      DeltaLow = shelf["DeltaLow_"+fittag]
      hcoor_delta20.append(DeltaFit+DeltaHigh)
      ccoor_delta20.append(DeltaFit)
      lcoor_delta20.append(DeltaFit-DeltaLow)

      fittag = tag+"_xi"+str(int(100*xi_err))+"_delta30"
      DeltaFit = shelf["DeltaFit_"+fittag]
      DeltaHigh = shelf["DeltaHigh_"+fittag]
      DeltaLow = shelf["DeltaLow_"+fittag]
      hcoor_delta30.append(DeltaFit+DeltaHigh)
      ccoor_delta30.append(DeltaFit)
      lcoor_delta30.append(DeltaFit-DeltaLow)


    ### Bands ###
    xband = list(xcoor)
    yband_delta10 = list(hcoor_delta10)
    yband_delta20 = list(hcoor_delta20)
    yband_delta30 = list(hcoor_delta30)
    for x in range(0, len(xcoor)):
      i = len(xcoor) - 1 - x
      xband.append(xcoor[i])
      yband_delta10.append(lcoor_delta10[i])
      yband_delta20.append(lcoor_delta20[i])
      yband_delta30.append(lcoor_delta30[i])

 
    ### FIGURE ###
    theFig = pyplot.figure(figsize=(12, 8), facecolor='white')

    ### Fill Regions ###
    #pyplot.fill(xband, yband_delta30, color='lightgreen', edgecolor='lightgreen')
    if (tag=="Para"):
      pyplot.fill(xband, yband_delta30, color='lightblue',  edgecolor='lightblue')
    else:
      pyplot.fill(xband, yband_delta20, color='lightblue',  edgecolor='lightblue')
    #pyplot.fill(xband, yband_delta10, color='coral',      edgecolor='coral')

    ### Fit Curves ###
    #pyplot.plot(xcoor, hcoor_delta30, '-', lw=1, color='green')
    #pyplot.plot(xcoor, ccoor_delta30, '-', lw=2, color='green')
    #pyplot.plot(xcoor, lcoor_delta30, '-', lw=1, color='green')
    if (tag=="Para"):
      pyplot.plot(xcoor, hcoor_delta30, '-', lw=1, color='blue')
      pyplot.plot(xcoor, ccoor_delta30, '-', lw=2, color='blue')
      pyplot.plot(xcoor, lcoor_delta30, '-', lw=1, color='blue')
    else:
      pyplot.plot(xcoor, hcoor_delta20, '-', lw=1, color='blue')
      pyplot.plot(xcoor, ccoor_delta20, '-', lw=2, color='blue')
      pyplot.plot(xcoor, lcoor_delta20, '-', lw=1, color='blue')
    #pyplot.plot(xcoor, hcoor_delta10, '-', lw=1, color='firebrick')
    #pyplot.plot(xcoor, ccoor_delta10, '-', lw=2, color='firebrick')
    #pyplot.plot(xcoor, lcoor_delta10, '-', lw=1, color='firebrick')

    ### Axes ###
    pyplot.plot([plotXMin, plotXMax], [0, 0], '-', lw=1, color='black')

    ### Legend ###
    pyplot.text(plotXMin+2, plotYMax-0.03, r'$\mathrm{LHCb}$',
      fontsize=largefont, horizontalalignment='left', verticalalignment='top')

    legBlue = matplotlib.patches.Rectangle((0, 0), 1, 1, facecolor='lightblue',  edgecolor='blue')
    leg = pyplot.legend([legBlue], [r"$\mathrm{68\:\%~C.L.}$"], loc=2)
    for t in leg.get_texts():
      t.set_fontsize(smallfont)

    ### Axes ###
    pyplot.xticks(numpy.arange(plotXMin, plotXMax + xtick, xtick), fontsize=smallfont)
    pyplot.subplot(111).xaxis.set_ticks(numpy.arange(plotXMin, plotXMax + xtick, 1), True)
    pyplot.subplot(111).xaxis.set_tick_params(which='major', length=10)
    pyplot.subplot(111).xaxis.set_tick_params(which='minor', length=6)
    pyplot.yticks(numpy.arange(plotYMin, plotYMax + ytick, ytick), fontsize=smallfont)
    pyplot.subplot(111).yaxis.set_ticks(numpy.arange(plotYMin, plotYMax + ytick, 0.01), True)
    pyplot.subplot(111).yaxis.set_tick_params(which='major', length=10)
    pyplot.subplot(111).yaxis.set_tick_params(which='minor', length=6)
    pyplot.axis([plotXMin, plotXMax, plotYMin, plotYMax])
    pyplot.xlabel(r"$\mathrm{Uncertainty~on~}\xi\mathrm{~[\%]}$",fontsize=largefont)
    pyplot.ylabel(r"$\Delta\phi_{s,"+pol+"}^{J/\psi\phi}~[\mathrm{rad}]$",fontsize=largefont)

    ### Save ###
    savestring = "Plots/SU3_Breaking_Bs2JpsiKstar_"+tag
    pyplot.savefig(savestring, bbox_inches='tight')


######################
## ***** Main ***** ##
######################

### Default ###
Make_Fit("Long")
#Make_Fit("Para")
#Make_Fit("Perp")
