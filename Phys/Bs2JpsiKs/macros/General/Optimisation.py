################################################################
## ***** Overview of Different Neural Net Optimisations ***** ##
################################################################

### Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb ###
# - Plots the numerical value of the different Yield Ratios


################################
## ***** Import Classes ***** ##
################################

import sys, os
import numpy
import sympy
import math
import matplotlib
matplotlib.use('PDF')
import matplotlib.pyplot as pyplot
from matplotlib.ticker import MultipleLocator

try:
    import minuit
except ImportError:
    import minuit2 as minuit
    
# file descriptors for logging Minuit output and switching back to stdout
fdLogErr = os.open( "minuit_err.log", os.O_RDWR|os.O_CREAT )
fdStdErr = os.dup(2)

# flags
logActive = False # True # toggle whether to log stderr outputs

##################################
## ***** System Functions ***** ##
##################################

def log_syserr(logActive) : 
    """ Switch stderr to log files, if the input is True """
    if logActive :
        #os.dup2(fd1, 1) # stdout
        os.dup2(fdLogErr, 2)    # stderr
    return

def print_syserr() :
    """ Switch stderr back to system defaults"""
    #os.dup2(fdSaved[0], 1) # stdout
    os.dup2(fdStdErr, 2) # stderr
    return


##################################
## ***** General Settings ***** ##
##################################

### For latex text ###
from matplotlib import rc
rc('text', usetex=True)

### Plot Settings ###
NumMeas = 30 # number of measurements
good = 25 # best measurement
plotYMin = -0.1 # plot range
plotYMax = (NumMeas-1)*0.2+0.1 # plot range
Offset  = 0.00015 # left alignment of text
tick = 0.0005 # tick separation
tinyfont = 14 # fontsize tiny text
smallfont = 16 # fontsize small text
largefont = 24 # fontsize large text


#######################
## ***** Input ***** ##
#######################

Yield_LL_Val = numpy.arange(0.,NumMeas)
Yield_LL_Err = numpy.arange(0.,NumMeas)
Yield_DD_Val = numpy.arange(0.,NumMeas)
Yield_DD_Err = numpy.arange(0.,NumMeas)
Yield_Val = numpy.arange(0.,NumMeas)
Yield_Err = numpy.arange(0.,NumMeas)
Punzi_Val = numpy.arange(0.,NumMeas)
Punzi_Err = numpy.arange(0.,NumMeas)
Yield_Flag = []

Yield_Flag.append("1") 
Yield_LL_Val[0] = 0.0128 
Yield_LL_Err[0] = 0.0015 
Yield_DD_Val[0] = 0.0103 
Yield_DD_Err[0] = 0.0010 
Yield_Val[0] = 0.01109
Yield_Err[0] = 0.00084
Punzi_Val[0] = 15.59
Punzi_Err[0] = 0.20

Yield_Flag.append("2") 
Yield_LL_Val[1] = 0.0128 
Yield_LL_Err[1] = 0.0015 
Yield_DD_Val[1] = 0.0107
Yield_DD_Err[1] = 0.0011 
Yield_Val[1] = 0.01142
Yield_Err[1] = 0.00086
Punzi_Val[1] = 16.16
Punzi_Err[1] = 0.23

Yield_Flag.append("3") 
Yield_LL_Val[2] = 0.0123 
Yield_LL_Err[2] = 0.0015 
Yield_DD_Val[2] = 0.0107 
Yield_DD_Err[2] = 0.0010 
Yield_Val[2] = 0.01123
Yield_Err[2] = 0.00086
Punzi_Val[2] = 15.83
Punzi_Err[2] = 0.22

Yield_Flag.append("4") 
Yield_LL_Val[3] = 0.0123
Yield_LL_Err[3] = 0.0015 
Yield_DD_Val[3] = 0.0107 
Yield_DD_Err[3] = 0.0010 
Yield_Val[3] = 0.01123 
Yield_Err[3] = 0.00086
Punzi_Val[3] = 15.83
Punzi_Err[3] = 0.22

Yield_Flag.append("5a") 
Yield_LL_Val[4] = 0.0000 
Yield_LL_Err[4] = 0.0000 
Yield_DD_Val[4] = 0.0000 
Yield_DD_Err[4] = 0.0000 
Yield_Val[4] = 0.01083 
Yield_Err[4] = 0.00085
Punzi_Val[4] = 15.47
Punzi_Err[4] = 0.21

Yield_Flag.append("5b") 
Yield_LL_Val[5] = 0.0119 
Yield_LL_Err[5] = 0.0015 
Yield_DD_Val[5] = 0.0103 
Yield_DD_Err[5] = 0.0010 
Yield_Val[5] = 0.01082 
Yield_Err[5] = 0.00084
Punzi_Val[5] = 15.47
Punzi_Err[5] = 0.21

Yield_Flag.append("6") 
Yield_LL_Val[6] = 0.0135 
Yield_LL_Err[6] = 0.0015 
Yield_DD_Val[6] = 0.0105
Yield_DD_Err[6] = 0.0010 
Yield_Val[6] = 0.01149
Yield_Err[6] = 0.00085
Punzi_Val[6] = 15.38
Punzi_Err[6] = 0.20

Yield_Flag.append("7") 
Yield_LL_Val[7] = 0.0135 
Yield_LL_Err[7] = 0.0015 
Yield_DD_Val[7] = 0.0107
Yield_DD_Err[7] = 0.0011 
Yield_Val[7] = 0.01161
Yield_Err[7] = 0.00086
Punzi_Val[7] = 15.86
Punzi_Err[7] = 0.20

Yield_Flag.append("8") 
Yield_LL_Val[8] = 0.0131
Yield_LL_Err[8] = 0.0015 
Yield_DD_Val[8] = 0.0099 
Yield_DD_Err[8] = 0.0010 
Yield_Val[8] = 0.01088
Yield_Err[8] = 0.00084
Punzi_Val[8] = 15.55
Punzi_Err[8] = 0.21

Yield_Flag.append("9") 
Yield_LL_Val[9] = 0.0127
Yield_LL_Err[9] = 0.0015 
Yield_DD_Val[9] = 0.0097 
Yield_DD_Err[9] = 0.0010 
Yield_Val[9] = 0.01059
Yield_Err[9] = 0.00083
Punzi_Val[9] = 15.72
Punzi_Err[9] = 0.22

Yield_Flag.append("10a") 
Yield_LL_Val[10] = 0.0000 
Yield_LL_Err[10] = 0.0000 
Yield_DD_Val[10] = 0.0000 
Yield_DD_Err[10] = 0.0000 
Yield_Val[10] = 0.01091
Yield_Err[10] = 0.00084
Punzi_Val[10] = 15.60
Punzi_Err[10] = 0.21

Yield_Flag.append("10b") 
Yield_LL_Val[11] = 0.0127
Yield_LL_Err[11] = 0.0015 
Yield_DD_Val[11] = 0.0100 
Yield_DD_Err[11] = 0.0010 
Yield_Val[11] = 0.01078
Yield_Err[11] = 0.00084
Punzi_Val[11] = 15.60
Punzi_Err[11] = 0.21

Yield_Flag.append("11") 
Yield_LL_Val[12] = 0.0117 
Yield_LL_Err[12] = 0.0016 
Yield_DD_Val[12] = 0.0101 
Yield_DD_Err[12] = 0.0011 
Yield_Val[12] = 0.01061
Yield_Err[12] = 0.00090
Punzi_Val[12] = 13.89
Punzi_Err[12] = 0.19

Yield_Flag.append("12") 
Yield_LL_Val[13] = 0.0115
Yield_LL_Err[13] = 0.0016 
Yield_DD_Val[13] = 0.0101 
Yield_DD_Err[13] = 0.0011 
Yield_Val[13] = 0.01054
Yield_Err[13] = 0.00090
Punzi_Val[13] = 13.79
Punzi_Err[13] = 0.19

Yield_Flag.append("13") 
Yield_LL_Val[14] = 0.0106
Yield_LL_Err[14] = 0.0016 
Yield_DD_Val[14] = 0.0097
Yield_DD_Err[14] = 0.0011 
Yield_Val[14] = 0.00995
Yield_Err[14] = 0.00090
Punzi_Val[14] = 13.04
Punzi_Err[14] = 0.18

Yield_Flag.append("14") 
Yield_LL_Val[15] = 0.0114
Yield_LL_Err[15] = 0.0017 
Yield_DD_Val[15] = 0.0103 
Yield_DD_Err[15] = 0.0011 
Yield_Val[15] = 0.01068
Yield_Err[15] = 0.00092
Punzi_Val[15] = 13.23
Punzi_Err[15] = 0.19

Yield_Flag.append("15a") 
Yield_LL_Val[16] = 0.0000 
Yield_LL_Err[16] = 0.0000 
Yield_DD_Val[16] = 0.0000 
Yield_DD_Err[16] = 0.0000 
Yield_Val[16] = 0.01096
Yield_Err[16] = 0.00095
Punzi_Val[16] = 13.08
Punzi_Err[16] = 0.20

Yield_Flag.append("15b") 
Yield_LL_Val[17] = 0.0123 
Yield_LL_Err[17] = 0.0018 
Yield_DD_Val[17] = 0.0103 
Yield_DD_Err[17] = 0.0011 
Yield_Val[17] = 0.01087
Yield_Err[17] = 0.00095
Punzi_Val[17] = 13.08
Punzi_Err[17] = 0.20

Yield_Flag.append("16") 
Yield_LL_Val[18] = 0.0136 
Yield_LL_Err[18] = 0.0014 
Yield_DD_Val[18] = 0.0105 
Yield_DD_Err[18] = 0.0011 
Yield_Val[18] = 0.01169
Yield_Err[18] = 0.00088
Punzi_Val[18] = 15.05
Punzi_Err[18] = 0.20

Yield_Flag.append("17") 
Yield_LL_Val[19] = 0.0135 
Yield_LL_Err[19] = 0.0014 
Yield_DD_Val[19] = 0.0111
Yield_DD_Err[19] = 0.0012 
Yield_Val[19] = 0.01212
Yield_Err[19] = 0.00092
Punzi_Val[19] = 15.21
Punzi_Err[19] = 0.22

Yield_Flag.append("18") 
Yield_LL_Val[20] = 0.0140
Yield_LL_Err[20] = 0.0016 
Yield_DD_Val[20] = 0.0100
Yield_DD_Err[20] = 0.0011 
Yield_Val[20] = 0.01132
Yield_Err[20] = 0.00090
Punzi_Val[20] = 14.21
Punzi_Err[20] = 0.19

Yield_Flag.append("19") 
Yield_LL_Val[21] = 0.0142 
Yield_LL_Err[21] = 0.0016 
Yield_DD_Val[21] = 0.0110 
Yield_DD_Err[21] = 0.0012 
Yield_Val[21] = 0.01232
Yield_Err[21] = 0.00097
Punzi_Val[21] = 14.69
Punzi_Err[21] = 0.22

Yield_Flag.append("20a") 
Yield_LL_Val[22] = 0.0000 
Yield_LL_Err[22] = 0.0000 
Yield_DD_Val[22] = 0.0000 
Yield_DD_Err[22] = 0.0000 
Yield_Val[22] = 0.01112 
Yield_Err[22] = 0.00091
Punzi_Val[22] = 13.92
Punzi_Err[22] = 0.19

Yield_Flag.append("20b") 
Yield_LL_Val[23] = 0.0137
Yield_LL_Err[23] = 0.0016 
Yield_DD_Val[23] = 0.0100 
Yield_DD_Err[23] = 0.0011 
Yield_Val[23] = 0.01121
Yield_Err[23] = 0.00090
Punzi_Val[23] = 13.92
Punzi_Err[23] = 0.19

Yield_Flag.append("21") 
Yield_LL_Val[24] = 0.0133
Yield_LL_Err[24] = 0.0014 
Yield_DD_Val[24] = 0.0109 
Yield_DD_Err[24] = 0.0010 
Yield_Val[24] = 0.01168
Yield_Err[24] = 0.00083
Punzi_Val[24] = 16.91
Punzi_Err[24] = 0.22

Yield_Flag.append("22") 
Yield_LL_Val[25] = 0.0131 
Yield_LL_Err[25] = 0.0014 
Yield_DD_Val[25] = 0.0108 
Yield_DD_Err[25] = 0.0010 
Yield_Val[25] = 0.01160
Yield_Err[25] = 0.00084
Punzi_Val[25] = 17.39
Punzi_Err[25] = 0.24

Yield_Flag.append("23") 
Yield_LL_Val[26] = 0.0121 
Yield_LL_Err[26] = 0.0014 
Yield_DD_Val[26] = 0.0103 
Yield_DD_Err[26] = 0.0011 
Yield_Val[26] = 0.01096 
Yield_Err[26] = 0.00085
Punzi_Val[26] = 16.90
Punzi_Err[26] = 0.24

Yield_Flag.append("24") 
Yield_LL_Val[27] = 0.0120 
Yield_LL_Err[27] = 0.0014 
Yield_DD_Val[27] = 0.0103 
Yield_DD_Err[27] = 0.0011 
Yield_Val[27] = 0.01092
Yield_Err[27] = 0.00085
Punzi_Val[27] = 16.73
Punzi_Err[27] = 0.24

Yield_Flag.append("25a") 
Yield_LL_Val[28] = 0.0000 
Yield_LL_Err[28] = 0.0000 
Yield_DD_Val[28] = 0.0000 
Yield_DD_Err[28] = 0.0000 
Yield_Val[28] = 0.01113
Yield_Err[28] = 0.00090
Punzi_Val[28] = 16.58
Punzi_Err[28] = 0.26

Yield_Flag.append("25b") 
Yield_LL_Val[29] = 0.0130 
Yield_LL_Err[29] = 0.0016 
Yield_DD_Val[29] = 0.0103 
Yield_DD_Err[29] = 0.0011 
Yield_Val[29] = 0.01111
Yield_Err[29] = 0.00090
Punzi_Val[29] = 16.58
Punzi_Err[29] = 0.26



#######################################
### Functions returning Coordinates ###
#######################################

helpline = numpy.arange(0.,2.)
helpline[0] = -10
helpline[1] = +20

helpbox = numpy.arange(0.,4.)
helpbox[0] = plotYMin
helpbox[1] = plotYMax
helpbox[2] = plotYMax
helpbox[3] = plotYMin

def line(xval):
  rule = numpy.arange(0.,2.)
  rule[0] = xval
  rule[1] = xval
  return rule

def band(xval,xerr):
  box = numpy.arange(0.,4.)
  box[0] = xval-xerr
  box[1] = xval-xerr
  box[2] = xval+xerr
  box[3] = xval+xerr
  return box



######################################
## ***** Make Figure: Average ***** ##
######################################

plotXMin = 0.008 # plot range
plotXMax = 0.0145 # plot range
textMax = 0.0095
textMin  = 0.013 # right alignment of text

### Define ###
theFig = pyplot.figure(figsize=(10*1.3,10*1.3),facecolor='white')

### Curves ###
pyplot.fill(band(Yield_Val[good],Yield_Err[good]),helpbox,color='salmon',edgecolor='firebrick')
pyplot.plot(line(Yield_Val[good]),helpline,'-',lw=1,color='firebrick')
pyplot.plot(line(Yield_Val[good]+Yield_Err[good]),helpline,'-',lw=1,color='firebrick')
pyplot.plot(line(Yield_Val[good]-Yield_Err[good]),helpline,'-',lw=1,color='firebrick')


### Error Bars ###
for i in range(0,NumMeas):
  yposition = plotYMax - 0.1 - i*0.2
  pyplot.text(plotXMin+Offset,yposition,r"$\mathrm{Optimisation~"+Yield_Flag[i]+"}$",fontsize=smallfont,horizontalalignment='left',verticalalignment='center')
  pyplot.errorbar(Yield_Val[i],yposition, xerr=Yield_Err[i], marker='.',color='black',capsize=5)
  result = "$%.5f \pm %.5f$"%(Yield_Val[i],Yield_Err[i])
  pyplot.text(textMin,yposition,result,fontsize=smallfont,horizontalalignment='left',verticalalignment='center')
  if(i%6==5):
    pyplot.plot(helpline,line(yposition-0.1),'-',lw=1,color='black')


### Axes ###
pyplot.xticks(numpy.arange(textMax,textMin,tick),fontsize=smallfont)
pyplot.yticks(numpy.arange(-5.,-1.,1),fontsize=smallfont)
pyplot.axis([plotXMin, plotXMax, plotYMin, plotYMax])
pyplot.xlabel(r'$N_{B_s^0\rightarrow J/\psi K_{\mathrm{S}}}/N_{B_d^0\rightarrow J/\psi K_{\mathrm{S}}}$',fontsize=largefont)


### Save ###
pyplot.savefig("Optimisation",bbox_inches='tight')



###################################
## ***** Make Figure: Long ***** ##
###################################

plotXMin = 0.007 # plot range
plotXMax = 0.0178 # plot range
textMax = 0.0085
textMin  = 0.0160 # right alignment of text

### Define ###
theFig = pyplot.figure(figsize=(10*1.3,10*1.3),facecolor='white')

### Curves ###
pyplot.fill(band(Yield_LL_Val[good],Yield_LL_Err[good]),helpbox,color='salmon',edgecolor='firebrick')
pyplot.plot(line(Yield_LL_Val[good]),helpline,'-',lw=1,color='firebrick')
pyplot.plot(line(Yield_LL_Val[good]+Yield_LL_Err[good]),helpline,'-',lw=1,color='firebrick')
pyplot.plot(line(Yield_LL_Val[good]-Yield_LL_Err[good]),helpline,'-',lw=1,color='firebrick')


### Error Bars ###
for i in range(0,NumMeas):
  yposition = plotYMax - 0.1 - i*0.2
  pyplot.text(plotXMin+Offset,yposition,r"$\mathrm{Optimisation~"+Yield_Flag[i]+"}$",fontsize=smallfont,horizontalalignment='left',verticalalignment='center')
  pyplot.errorbar(Yield_LL_Val[i],yposition, xerr=Yield_LL_Err[i], marker='.',color='black',capsize=5)
  if(Yield_LL_Val[i]>0):
    result = "$%.4f \pm %.4f$"%(Yield_LL_Val[i],Yield_LL_Err[i])
    pyplot.text(textMin,yposition,result,fontsize=smallfont,horizontalalignment='left',verticalalignment='center')
  if(i%6==5):
    pyplot.plot(helpline,line(yposition-0.1),'-',lw=1,color='black')


### Axes ###
pyplot.xticks(numpy.arange(textMax,textMin,2*tick),fontsize=smallfont)
pyplot.subplot(111).xaxis.set_minor_locator(MultipleLocator(tick))
pyplot.yticks(numpy.arange(-5.,-1.,1),fontsize=smallfont)
pyplot.axis([plotXMin, plotXMax, plotYMin, plotYMax])
pyplot.xlabel(r'$N_{B_s^0\rightarrow J/\psi K_{\mathrm{S}}}/N_{B_d^0\rightarrow J/\psi K_{\mathrm{S}}}$',fontsize=largefont)


### Save ###
pyplot.savefig("Optimisation_LL",bbox_inches='tight')



###################################
## ***** Make Figure: Down ***** ##
###################################

plotXMin = 0.007 # plot range
plotXMax = 0.0135 # plot range
textMax = 0.0085
textMin  = 0.0125 # right alignment of text

### Define ###
theFig = pyplot.figure(figsize=(10*1.3,10*1.3),facecolor='white')

### Curves ###
pyplot.fill(band(Yield_DD_Val[good],Yield_DD_Err[good]),helpbox,color='salmon',edgecolor='firebrick')
pyplot.plot(line(Yield_DD_Val[good]),helpline,'-',lw=1,color='firebrick')
pyplot.plot(line(Yield_DD_Val[good]+Yield_DD_Err[good]),helpline,'-',lw=1,color='firebrick')
pyplot.plot(line(Yield_DD_Val[good]-Yield_DD_Err[good]),helpline,'-',lw=1,color='firebrick')


### Error Bars ###
for i in range(0,NumMeas):
  yposition = plotYMax - 0.1 - i*0.2
  pyplot.text(plotXMin+Offset,yposition,r"$\mathrm{Optimisation~"+Yield_Flag[i]+"}$",fontsize=smallfont,horizontalalignment='left',verticalalignment='center')
  pyplot.errorbar(Yield_DD_Val[i],yposition, xerr=Yield_DD_Err[i], marker='.',color='black',capsize=5)
  if(Yield_DD_Val[i]>0):
    result = "$%.4f \pm %.4f$"%(Yield_DD_Val[i],Yield_DD_Err[i])
    pyplot.text(textMin,yposition,result,fontsize=smallfont,horizontalalignment='left',verticalalignment='center')
  if(i%6==5):
    pyplot.plot(helpline,line(yposition-0.1),'-',lw=1,color='black')


### Axes ###
pyplot.xticks(numpy.arange(textMax,textMin,tick),fontsize=smallfont)
pyplot.yticks(numpy.arange(-5.,-1.,1),fontsize=smallfont)
pyplot.axis([plotXMin, plotXMax, plotYMin, plotYMax])
pyplot.xlabel(r'$N_{B_s^0\rightarrow J/\psi K_{\mathrm{S}}}/N_{B_d^0\rightarrow J/\psi K_{\mathrm{S}}}$',fontsize=largefont)


### Save ###
pyplot.savefig("Optimisation_DD",bbox_inches='tight')



##################################
## ***** Make Figure: All ***** ##
##################################

plotXMin = 0.006 # plot range
plotXMax = 0.0182 # plot range
textMax = 0.0085
textMin  = 0.0160 # right alignment of text
plotYMin = -0.25 # plot range
plotYMax = (NumMeas-1)*0.5+0.25 # plot range

helpbox = numpy.arange(0.,4.)
helpbox[0] = plotYMin
helpbox[1] = plotYMax
helpbox[2] = plotYMax
helpbox[3] = plotYMin

### Define ###
theFig = pyplot.figure(figsize=(10*1.3,10*1.3),facecolor='white')

### Curves ###
pyplot.fill([plotXMin,plotXMax,plotXMax,plotXMin],band(plotYMax-0.25-good*0.5,0.25),color='gainsboro')
pyplot.fill(band(Yield_Val[good],Yield_Err[good]),helpbox,color='salmon',edgecolor='firebrick')
pyplot.plot(line(Yield_Val[good]),helpline,'-',lw=1,color='firebrick')
pyplot.plot(line(Yield_Val[good]+Yield_Err[good]),helpline,'-',lw=1,color='firebrick')
pyplot.plot(line(Yield_Val[good]-Yield_Err[good]),helpline,'-',lw=1,color='firebrick')


### Error Bars ###
for i in range(0,NumMeas):
  yposition = plotYMax - 0.25 - i*0.5
  pyplot.text(plotXMin+Offset,yposition,r"$\mathrm{Optimisation~"+Yield_Flag[i]+"}$",fontsize=smallfont,horizontalalignment='left',verticalalignment='center')
  pyplot.errorbar(Yield_LL_Val[i],yposition-0.1, xerr=Yield_LL_Err[i], marker='.',mfc='blue',ecolor='blue',capsize=5)
  pyplot.errorbar(Yield_DD_Val[i],yposition+0.1, xerr=Yield_DD_Err[i], marker='.',mfc='green',ecolor='green',capsize=5)
  pyplot.errorbar(Yield_Val[i],yposition, xerr=Yield_Err[i], marker='.',color='black',capsize=5)
  result = "$%.5f \pm %.5f$"%(Yield_Val[i],Yield_Err[i])
  pyplot.text(textMin,yposition,result,fontsize=smallfont,horizontalalignment='left',verticalalignment='center')
  if(i%6==5):
    pyplot.plot(helpline,line(yposition-0.25),'-',lw=1,color='black')


### Axes ###
pyplot.xticks(numpy.arange(textMax,textMin,2*tick),fontsize=smallfont)
pyplot.subplot(111).xaxis.set_minor_locator(MultipleLocator(tick))
pyplot.yticks(numpy.arange(-5.,-1.,1),fontsize=smallfont)
pyplot.axis([plotXMin, plotXMax, plotYMin, plotYMax])
pyplot.xlabel(r'$N_{B_s^0\rightarrow J/\psi K_{\mathrm{S}}}/N_{B_d^0\rightarrow J/\psi K_{\mathrm{S}}}$',fontsize=largefont)


### Save ###
pyplot.savefig("Optimisation_All",bbox_inches='tight')



############################
## ***** Minuit Fit ***** ##
############################

def linear(aPar, bPar, xVal):
    return aPar + bPar * xVal

def chi2_lin(aPar,bPar):
    chi2 = 0
    for i in range(0,NumMeas):
      if(i==0 or (i>0 and Yield_Val[i]!=Yield_Val[i-1])):
        chi2 = chi2 + pow(linear(aPar,bPar,Punzi_Val[i]) - Yield_Val[i],2)/pow(Yield_Err[good],2)
    return chi2
    
def chi2_flat(aPar):
    chi2 = 0
    for i in range(0,NumMeas):
      if(i==0 or (i>0 and Yield_Val[i]!=Yield_Val[i-1])):
        chi2 = chi2 + pow(linear(aPar,0,Punzi_Val[i]) - Yield_Val[i],2)/pow(Yield_Err[good],2)
    return chi2

log_syserr(logActive)

def doMinuit_lin(myChi2):
      
  m = minuit.Minuit(myChi2)
  m.strategy = 2
  m.printMode = 0
  
  ### Set Initial Guess ###
  m.values["aPar"] = 0.011
  m.values["bPar"] = 0

  m.errors["aPar"] = 0.005
  m.errors["bPar"] = 0.1

  ### MIGRAD ###
  m.migrad()
  print "### MIGRAD results : "
  print "  a = %.4f +/- %.4f"%(m.values["aPar"],m.errors["aPar"])
  print "  b = %.4f +/- %.4f"%(m.values["bPar"],m.errors["bPar"])
  print "fit info:", m.fval, m.ncalls, m.edm
  
  return m.values["aPar"], m.values["bPar"]
  
def doMinuit_flat(myChi2):
      
  m = minuit.Minuit(myChi2)
  m.strategy = 2
  m.printMode = 0
  
  ### Set Initial Guess ###
  m.values["aPar"] = 0.011

  m.errors["aPar"] = 0.005

  ### MIGRAD ###
  m.migrad()
  print "### MIGRAD results : "
  print "  a = %.4f +/- %.4f"%(m.values["aPar"],m.errors["aPar"])
  print "fit info:", m.fval, m.ncalls, m.edm
  
  return m.values["aPar"]


####################################
## ***** Make Figure: Punzi ***** ##
####################################

plotXMin = 12 # plot range
plotXMax = 18 # plot range
plotYMin = 0.0090 # plot range
plotYMax = 0.0130 # plot range

### Define ###
theFig = pyplot.figure(figsize=(10*1.3,6*1.3),facecolor='white')

### Curves ###
aVal, bVal = doMinuit_lin(chi2_lin)
pyplot.plot([plotXMin,plotXMax],[aVal+bVal*plotXMin,aVal+bVal*plotXMax],'-',lw=2,color='firebrick')
cVal = doMinuit_flat(chi2_flat)
pyplot.plot([plotXMin,plotXMax],[cVal,cVal],'-',lw=2,color='blue')

### Error Bars ###
for i in range(0,NumMeas):
  pyplot.errorbar(Punzi_Val[i],Yield_Val[i],xerr=Punzi_Err[i],yerr=Yield_Err[i], marker='.',color='black',capsize=5)


### Axes ###
pyplot.xticks(numpy.arange(plotXMin,plotXMax+1,1),fontsize=smallfont)
pyplot.yticks(numpy.arange(plotYMin,plotYMax+tick,tick),fontsize=smallfont)
pyplot.axis([plotXMin, plotXMax, plotYMin, plotYMax])
pyplot.xlabel(r'$\mathrm{Punzi~FoM}$',fontsize=largefont)
pyplot.ylabel(r'$N_{B_s^0\rightarrow J/\psi K_{\mathrm{S}}}/N_{B_d^0\rightarrow J/\psi K_{\mathrm{S}}}$',fontsize=largefont)


### Save ###
pyplot.savefig("Punzi_correlation",bbox_inches='tight')



##########################
## ***** Finalise ***** ##
##########################
print_syserr()

# Close the file descriptors
os.close(fdLogErr)