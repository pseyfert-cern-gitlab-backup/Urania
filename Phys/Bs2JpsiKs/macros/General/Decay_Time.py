#################################################
## ***** Signal Decay Time Distributions ***** ##
#################################################

### Macro written by Kristof De Bruyn for the effective lifetime measurement of Bs->JpsiKs at LHCb ###
# - Simple Plots


################################
## ***** Import Classes ***** ##
################################
import math
import numpy
import matplotlib
matplotlib.use('PDF')
import matplotlib.pyplot as pyplot
from matplotlib.ticker import MultipleLocator


##################################
## ***** General Settings ***** ##
##################################

### For latex text ###
from matplotlib import rc
rc('text', usetex=True)

### Plot Settings ###
plotXMin = 0. # plot range
plotXMax = 15. # plot range
plotYMin = 0. # plot range
plotYMax = 1.5 # plot range
Offset  = 0.00025 # left alignment of text
xtick = 0.25 # tick separation
ytick = 0.05 # tick separation
smallfont = 26 # fontsize small text
largefont = 30 # fontsize large text
npoints = 1000 # number of points on the curves


#######################
## ***** Input ***** ##
#######################

tauBd = 1.519
tauBs = 1.503
SMADG = 0.944
ysObs = 0.075

yLL = 1.52
zLL = 2.33
betaLL = -0.025

yDD = 2.024
zDD = 1.112
betaDD = 0.031


#######################################
### Functions returning Coordinates ###
#######################################

### General ###
def theline():
  xstep = (plotXMax-plotXMin)/(npoints-1)
  xline = numpy.arange(0.,npoints)
  for i in range(0,npoints):
    xline[i] = plotXMin + i*xstep
  return xline

def Acc(yVal,zVal,betaVal,xline):
  points = len(xline)
  yline = numpy.arange(0.,points)
  for i in range(0,points):
    if(xline[i]>0):
      yline[i] = (1+betaVal*xline[i])/(1+pow(zVal*xline[i],-yVal))
    else:
      yline[i] = 0
  return yline
  
def BdDecay(tau,xline):
  points = len(xline)
  yline = numpy.arange(0.,points)
  for i in range(0,points):
    yline[i] = math.exp(-xline[i]/tau)/tau
  return yline
  
def BsDecay(tau,ADG,ys,xline):
  points = len(xline)
  yline = numpy.arange(0.,points)
  for i in range(0,points):
    yline[i] = (1-pow(ys,2))*math.exp(-xline[i]/tau)*(math.cosh(ys*xline[i]/tau)+ADG*math.sinh(ys*xline[i]/tau))/(tau*(1+ADG*ys))
  return yline

def BAccDecay(accline,Bline):
  points = len(Bline)
  yline = numpy.arange(0.,points)
  for i in range(0,points):
    yline[i] = accline[i] * Bline[i]
  return yline


#############################
## ***** Make Figure ***** ##
#############################

### Define ###
theFig = pyplot.figure(figsize=(10*1.3,6*1.3),facecolor='white')

### Curves ###
pyplot.plot(theline(),Acc(yLL,zLL,betaLL,theline()),'-',lw=1,color='firebrick')
pyplot.plot(theline(),Acc(yDD,zDD,betaDD,theline()),'-',lw=1,color='blue')


### Legend ###
leg_Blue = matplotlib.lines.Line2D([0,1],[0,1],linestyle='-',linewidth=2,color='blue')
leg_Red = matplotlib.lines.Line2D([0,1],[0,1],linestyle='-',linewidth=2,color='firebrick')

leg = pyplot.legend([leg_Red,leg_Blue],[r'$\mathrm{Long~}K_{\mathrm S}^0$',r'$\mathrm{Downstream~}K_{\mathrm S}^0$'],loc=2)
for t in leg.get_texts():
  t.set_fontsize(largefont)

### Axes ###
pyplot.xticks(numpy.arange(plotXMin,plotXMax+xtick,4*xtick),fontsize=smallfont)
pyplot.yticks(numpy.arange(plotYMin,plotYMax+ytick,5*ytick),fontsize=smallfont)
pyplot.subplot(111).xaxis.set_minor_locator(MultipleLocator(xtick))
pyplot.subplot(111).yaxis.set_minor_locator(MultipleLocator(ytick))
pyplot.axis([plotXMin, plotXMax, plotYMin, plotYMax])
pyplot.ylabel(r'$\mathrm{Acceptance}$',fontsize=largefont)
pyplot.xlabel(r'$\mathrm{True~B~decay~time~(ps)}$',fontsize=largefont)


### Save ###
pyplot.savefig("TheoCorr_Acceptance",bbox_inches='tight')



#############################
## ***** Make Figure ***** ##
#############################
plotXMax = 10 # plot range
plotYMax = 0.3 # plot range
ytick = 0.01 # tick separation

### Define ###
theFig = pyplot.figure(figsize=(10*1.3,6*1.3),facecolor='white')

### Curves ###
pyplot.plot(theline(),BAccDecay(Acc(yLL,zLL,betaLL,theline()),BdDecay(tauBd,theline())),'-',lw=1,color='firebrick')
pyplot.plot(theline(),BAccDecay(Acc(yLL,zLL,betaLL,theline()),BsDecay(tauBs,SMADG,ysObs,theline())),'-',lw=1,color='blue')


### Legend ###
leg_Blue = matplotlib.lines.Line2D([0,1],[0,1],linestyle='-',linewidth=2,color='blue')
leg_Red = matplotlib.lines.Line2D([0,1],[0,1],linestyle='-',linewidth=2,color='firebrick')

leg = pyplot.legend([leg_Red,leg_Blue],[r'$B_d^0\rightarrow J/\psi K_{\mathrm S}^0$',r'$B_s^0\rightarrow J/\psi K_{\mathrm S}^0$'],loc=1)
for t in leg.get_texts():
  t.set_fontsize(largefont)

### Axes ###
pyplot.xticks(numpy.arange(plotXMin,plotXMax+xtick,4*xtick),fontsize=smallfont)
pyplot.yticks(numpy.arange(plotYMin,plotYMax+ytick,5*ytick),fontsize=smallfont)
pyplot.subplot(111).xaxis.set_minor_locator(MultipleLocator(xtick))
pyplot.subplot(111).yaxis.set_minor_locator(MultipleLocator(ytick))
pyplot.axis([plotXMin, plotXMax, plotYMin, plotYMax])
pyplot.ylabel(r'$\mathrm{PDF}$',fontsize=largefont)
pyplot.xlabel(r'$\mathrm{True~B~decay~time~(ps)}$',fontsize=largefont)


### Save ###
pyplot.savefig("TheoCorr_PDF_LL",bbox_inches='tight')



#############################
## ***** Make Figure ***** ##
#############################

### Define ###
theFig = pyplot.figure(figsize=(10*1.3,6*1.3),facecolor='white')

### Curves ###
pyplot.plot(theline(),BAccDecay(Acc(yDD,zDD,betaDD,theline()),BdDecay(tauBd,theline())),'-',lw=1,color='firebrick')
pyplot.plot(theline(),BAccDecay(Acc(yDD,zDD,betaDD,theline()),BsDecay(tauBs,SMADG,ysObs,theline())),'-',lw=1,color='blue')


### Legend ###
leg_Blue = matplotlib.lines.Line2D([0,1],[0,1],linestyle='-',linewidth=2,color='blue')
leg_Red = matplotlib.lines.Line2D([0,1],[0,1],linestyle='-',linewidth=2,color='firebrick')

leg = pyplot.legend([leg_Red,leg_Blue],[r'$B_d^0\rightarrow J/\psi K_{\mathrm S}^0$',r'$B_s^0\rightarrow J/\psi K_{\mathrm S}^0$'],loc=1)
for t in leg.get_texts():
  t.set_fontsize(largefont)

### Axes ###
pyplot.xticks(numpy.arange(plotXMin,plotXMax+xtick,4*xtick),fontsize=smallfont)
pyplot.yticks(numpy.arange(plotYMin,plotYMax+ytick,5*ytick),fontsize=smallfont)
pyplot.subplot(111).xaxis.set_minor_locator(MultipleLocator(xtick))
pyplot.subplot(111).yaxis.set_minor_locator(MultipleLocator(ytick))
pyplot.axis([plotXMin, plotXMax, plotYMin, plotYMax])
pyplot.ylabel(r'$\mathrm{PDF}$',fontsize=largefont)
pyplot.xlabel(r'$\mathrm{True~B~decay~time~(ps)}$',fontsize=largefont)


### Save ###
pyplot.savefig("TheoCorr_PDF_DD",bbox_inches='tight')
