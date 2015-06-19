#--------------------------------------
#
# Parameters of the Peakking backgrounds for BsMuMu analysis
#
#--------------------------------------

from math import *
from errors import *
import code
import betaparam13 as beta

#===============================================
#
# Inputs for the 2011+2012 datasets as 1 dataset
# Autumn 2013
# with BDT12
#
#===============================================


#===============================================
# Normalisation parameters (imported from betaparams)
BkgNorm = beta.bkgNormNoBR()
# --> Note beta = BkgNorm / BuBR
# For each exclusive background:
# XYield = XEff * (fx/fd) * BkgNorm / BuBR
# Exception is made for Lambda for which fLambda/fd is already included in eff
#------------------------------------------------------

#------------------------------------------------------
# Peaking background  Bd -> pi mu nu   evttype 11512012
#------------------------------------------------------

# Efficiency 
PiMuNuEff = EVal(9.69255e-07 , 1.36042e-08) # Fra 20131113
# BDT distribution
PiMuNuFrac1 = EVal(0.375795 , 0.00201952)      # fraction of bin 1
PiMuNuFrac2 = EVal(0.18871 , 0.00141381)       # fraction of bin 2
PiMuNuFrac3 = EVal(0.108028 , 0.00105513)      # fraction of bin 3
PiMuNuFrac4 = EVal(0.0937695 , 0.00095977)     # fraction of bin 4
PiMuNuFrac5 = EVal(0.0826438 , 0.000884386)    # fraction of bin 5
PiMuNuFrac6 = EVal(0.0716231 , 0.000776908)    # fraction of bin 6
PiMuNuFrac7 = EVal(0.0526704 , 0.000642686)    # fraction of bin 7
PiMuNuFrac8 = EVal(0.0267601 , 0.000416164)    # fraction of bin 8
PiMuNuFrac78 = EVal(0.0794305 , 0.000765662)   # fraction of bin 8

# Fra 20131210
PiMuNuMean1 = EVal(5143.13 , 1.43205) 	 # Mean for bin 1
PiMuNuShc1 = EVal(1.00001e-07 , 7.35815e-06) 	 # Shc for bin 1
PiMuNuSigma1 = EVal(74.9862 , 0.914541) 	 # Sigma for bin 1
PiMuNuMean2 = EVal(5178.63 , 1.51378) 	 # Mean for bin 2
PiMuNuShc2 = EVal(1e-07 , 1.18848e-05) 	 # Shc for bin 2
PiMuNuSigma2 = EVal(59.7152 , 1.14967) 	 # Sigma for bin 2
PiMuNuMean3 = EVal(5200.61 , 1.57786) 	 # Mean for bin 3
PiMuNuShc3 = EVal(1e-07 , 2.35808e-05) 	 # Shc for bin 3
PiMuNuSigma3 = EVal(47.6316 , 1.37917) 	 # Sigma for bin 3
PiMuNuMean4 = EVal(5194.37 , 29.636) 	 # Mean for bin 4
PiMuNuShc4 = EVal(1.57456e-07 , 5.87224e-13) 	 # Shc for bin 4
PiMuNuSigma4 = EVal(51.4528 , 1.90716e-06) 	 # Sigma for bin 4
PiMuNuMean5 = EVal(5203.96 , 0.903004) 	 # Mean for bin 5
PiMuNuShc5 = EVal(0.000433232 , 9.5371e-05) 	 # Shc for bin 5
PiMuNuSigma5 = EVal(48.1293 , 1.09355) 	 # Sigma for bin 5
PiMuNuMean6 = EVal(5218.46 , 3.27551) 	 # Mean for bin 6
PiMuNuShc6 = EVal(0.000204279 , 0.000163831) 	 # Shc for bin 6
PiMuNuSigma6 = EVal(40.2174 , 2.02297) 	 # Sigma for bin 6
PiMuNuMean7 = EVal(5202.75 , 6.33142) 	 # Mean for bin 7
PiMuNuShc7 = EVal(0.0019656 , 0.000336902) 	 # Shc for bin 7
PiMuNuSigma7 = EVal(51.7638 , 3.24218) 	 # Sigma for bin 7
PiMuNuMean8 = EVal(5224.42 , 4.29211) 	 # Mean for bin 8
PiMuNuShc8 = EVal(0.00324343 , 0.0002708) 	 # Shc for bin 8
PiMuNuSigma8 = EVal(40.4187 , 2.70356) 	 # Sigma for bin 8
PiMuNuMean78 = EVal(5214.62 , 3.32317) 	 # Mean for bin 78
PiMuNuShc78 = EVal(0.00220095 , 0.000187501) 	 # Shc for bin 78
PiMuNuSigma78 = EVal(46.181 , 1.91159) 	 # Sigma for bin 78

#------------------------------------------------------
# Peaking background  Bs -> K mu nu   evttype 13512011
#------------------------------------------------------
KMuNuEff = EVal(3.79923e-07, 9.12909e-09)    # Total Yield of the component 13512011
# BDT distribution
KMuNuFrac1 = EVal(0.317194 , 0.00173252)      # fraction of bin 1
KMuNuFrac2 = EVal(0.168825 , 0.00125924)      # fraction of bin 2
KMuNuFrac3 = EVal(0.104746 , 0.000985416)     # fraction of bin 3
KMuNuFrac4 = EVal(0.102397 , 0.000971286)     # fraction of bin 4
KMuNuFrac5 = EVal(0.100798 , 0.000961143)     # fraction of bin 5
KMuNuFrac6 = EVal(0.0954037 , 0.000932054)    # fraction of bin 6
KMuNuFrac7 = EVal(0.0728699 , 0.00080375)     # fraction of bin 7
KMuNuFrac8 = EVal(0.0377668 , 0.000565983)    # fraction of bin 8
KMuNuFrac78 = EVal(0.110637 , 0.000983031)    # fraction of bin 78
# Fra 20131210
KMuNuMean1 = EVal(5169.57 , 1.75907) 	 # Mean for bin 1
KMuNuShc1 = EVal(1.00002e-07 , 8.7634e-06) 	 # Shc for bin 1
KMuNuSigma1 = EVal(91.8522 , 1.06738) 	 # Sigma for bin 1
KMuNuMean2 = EVal(5206.79 , 0.0092893) 	 # Mean for bin 2
KMuNuShc2 = EVal(1.08859e-07 , 2.29125e-09) 	 # Shc for bin 2
KMuNuSigma2 = EVal(77.2575 , 0.000224814) 	 # Sigma for bin 2
KMuNuMean3 = EVal(5215.26 , 1.26729) 	 # Mean for bin 3
KMuNuShc3 = EVal(1.00219e-07 , 0.000353268) 	 # Shc for bin 3
KMuNuSigma3 = EVal(73.1085 , 5.75622) 	 # Sigma for bin 3
KMuNuMean4 = EVal(5224.52 , 2.21346) 	 # Mean for bin 4
KMuNuShc4 = EVal(1.00001e-07 , 3.46317e-05) 	 # Shc for bin 4
KMuNuSigma4 = EVal(66.8504 , 1.70672) 	 # Sigma for bin 4
KMuNuMean5 = EVal(5230.87 , 0.145842) 	 # Mean for bin 5
KMuNuShc5 = EVal(6.52078e-05 , 2.6144e-05) 	 # Shc for bin 5
KMuNuSigma5 = EVal(64.8907 , 52.5518) 	 # Sigma for bin 5
KMuNuMean6 = EVal(5224.82 , 5.27864) 	 # Mean for bin 6
KMuNuShc6 = EVal(0.00106659 , 0.000215696) 	 # Shc for bin 6
KMuNuSigma6 = EVal(65.6887 , 2.47405) 	 # Sigma for bin 6
KMuNuMean7 = EVal(5269.86 , 0.00172839) 	 # Mean for bin 7
KMuNuShc7 = EVal(0.000609588 , 1.15881e-08) 	 # Shc for bin 7
KMuNuSigma7 = EVal(47.8005 , 8.68364e-05) 	 # Sigma for bin 7
KMuNuMean8 = EVal(5268.9 , 3.61877) 	 # Mean for bin 8
KMuNuShc8 = EVal(0.00329488 , 0.000186864) 	 # Shc for bin 8
KMuNuSigma8 = EVal(42.6779 , 2.36592) 	 # Sigma for bin 8
KMuNuMean78 = EVal(5279.99 , 4.73427e-05) 	 # Mean for bin 78
KMuNuShc78 = EVal(0.00101073 , 3.04322e-12) 	 # Shc for bin 78
KMuNuSigma78 = EVal(40.0311 , 1.43756e-08) 	 # Sigma for bin 78

#------------------------------------------------------
# Peaking background  B -> pi mu mu 
#------------------------------------------------------

# Fra 20131113
PiMuMuEff  = EVal(0.00101107, 1.60763e-05)       # Total Yield of the component 12113023
# BDT distribution
PiMuMuFrac1 = EVal(0.380326 , 0.00962312)      # fraction of bin 1
PiMuMuFrac2 = EVal(0.184563 , 0.00670363)      # fraction of bin 2
PiMuMuFrac3 = EVal(0.104212 , 0.00503729)      # fraction of bin 3
PiMuMuFrac4 = EVal(0.103969 , 0.0050314)       # fraction of bin 4
PiMuMuFrac5 = EVal(0.0754809 , 0.00428703)     # fraction of bin 5
PiMuMuFrac6 = EVal(0.0742635 , 0.00425231)     # fraction of bin 6
PiMuMuFrac7 = EVal(0.0501583 , 0.00349469)     # fraction of bin 7
PiMuMuFrac8 = EVal(0.027027 , 0.00256529)      # fraction of bin 8
PiMuMuFrac78 = EVal(0.0771853 , 0.00433516)    # fraction of bin 78

PiMuMuMean1 = EVal(5118.08 , 12.1071) 	 # Mean for bin 1
PiMuMuShc1 = EVal(0.000806868 , 0.00114104) 	 # Shc for bin 1
PiMuMuSigma1 = EVal(36.1658 , 6.65195) 	 # Sigma for bin 1
PiMuMuMean2 = EVal(5119.35 , 17.7467) 	 # Mean for bin 2
PiMuMuShc2 = EVal(0.00390066 , 0.00203037) 	 # Shc for bin 2
PiMuMuSigma2 = EVal(33.1131 , 10.1877) 	 # Sigma for bin 2
PiMuMuMean3 = EVal(5112.45 , 18.9962) 	 # Mean for bin 3
PiMuMuShc3 = EVal(0.00480734 , 0.00250257) 	 # Shc for bin 3
PiMuMuSigma3 = EVal(35.2328 , 9.8867) 	 # Sigma for bin 3
PiMuMuMean4 = EVal(5145.89 , 16.5276) 	 # Mean for bin 4
PiMuMuShc4 = EVal(0.00241315 , 0.00184086) 	 # Shc for bin 4
PiMuMuSigma4 = EVal(14.9779 , 13.1006) 	 # Sigma for bin 4
PiMuMuMean5 = EVal(5132.29 , 23.2474) 	 # Mean for bin 5
PiMuMuShc5 = EVal(0.00316622 , 0.00243435) 	 # Shc for bin 5
PiMuMuSigma5 = EVal(35.4681 , 12.8674) 	 # Sigma for bin 5
PiMuMuMean6 = EVal(5151.14 , 14.7124) 	 # Mean for bin 6
PiMuMuShc6 = EVal(0.00295458 , 0.00162205) 	 # Shc for bin 6
PiMuMuSigma6 = EVal(20.0806 , 11.4512) 	 # Sigma for bin 6
PiMuMuMean7 = EVal(5134.73 , 19.535) 	 # Mean for bin 7
PiMuMuShc7 = EVal(0.00632799 , 0.00267593) 	 # Shc for bin 7
PiMuMuSigma7 = EVal(25.6898 , 12.9713) 	 # Sigma for bin 7
PiMuMuMean8 = EVal(5139.98 , 19.6439) 	 # Mean for bin 8
PiMuMuShc8 = EVal(0.0106327 , 0.00345633) 	 # Shc for bin 8
PiMuMuSigma8 = EVal(34.3729 , 11.1542) 	 # Sigma for bin 8
PiMuMuMean78 = EVal(5135.58 , 13.6) 	 # Mean for bin 78
PiMuMuShc78 = EVal(0.00789491 , 0.00205462) 	 # Shc for bin 78
PiMuMuSigma78 = EVal(31.7355 , 8.07924) 	 # Sigma for bin 78



#------------------------------------------------------
# Peaking background  Lb -> p mu nu   evttype 15512012
#------------------------------------------------------
# Fra 20131113

LbPMuNuEff = EVal(2.07564e-07, 8.44661e-09) # Total Yield of the component 15512012

# BDT distribution
LbPMuNuFrac1 = EVal(0.4533 , 0.00481905)	 # fraction of bin 1
LbPMuNuFrac2 = EVal(0.187775 , 0.00284099)	 # fraction of bin 2
LbPMuNuFrac3 = EVal(0.100942 , 0.00199211)	 # fraction of bin 3
LbPMuNuFrac4 = EVal(0.0810074 , 0.0016595)	 # fraction of bin 4
LbPMuNuFrac5 = EVal(0.0674677 , 0.00143599)	 # fraction of bin 5
LbPMuNuFrac6 = EVal(0.0546789 , 0.00120317)	 # fraction of bin 6
LbPMuNuFrac7 = EVal(0.0368227 , 0.000889477)	 # fraction of bin 7
LbPMuNuFrac8 = EVal(0.0180068 , 0.000567792)	 # fraction of bin 8
LbPMuNuFrac78 = EVal(0.0548295 , 0.00105525)	 # fraction of bin 8


# Fra 20131210
LbPMuNuMean1 = EVal(5450.39 , 2.99819) 	 # Mean for bin 1
LbPMuNuShc1 = EVal(1e-07 , 1.37669e-05) 	 # Shc for bin 1
LbPMuNuSigma1 = EVal(63.9219 , 3.05254) 	 # Sigma for bin 1
LbPMuNuMean2 = EVal(5467.66 , 6.16017) 	 # Mean for bin 2
LbPMuNuShc2 = EVal(0.00049086 , 0.00011498) 	 # Shc for bin 2
LbPMuNuSigma2 = EVal(50.0685 , 4.60724) 	 # Sigma for bin 2
LbPMuNuMean3 = EVal(5449.2 , 8.35147) 	 # Mean for bin 3
LbPMuNuShc3 = EVal(0.0012684 , 0.00017439) 	 # Shc for bin 3
LbPMuNuSigma3 = EVal(55.2365 , 5.89399) 	 # Sigma for bin 3
LbPMuNuMean4 = EVal(5472.49 , 3.84353) 	 # Mean for bin 4
LbPMuNuShc4 = EVal(0.00122549 , 0.000116626) 	 # Shc for bin 4
LbPMuNuSigma4 = EVal(40 , 3.91871) 	 # Sigma for bin 4
LbPMuNuMean5 = EVal(5478.62 , 8.20401) 	 # Mean for bin 5
LbPMuNuShc5 = EVal(0.00122138 , 0.000169329) 	 # Shc for bin 5
LbPMuNuSigma5 = EVal(40.706 , 24.7339) 	 # Sigma for bin 5
LbPMuNuMean6 = EVal(5462.84 , 1.40257) 	 # Mean for bin 6
LbPMuNuShc6 = EVal(0.00181621 , 0.000105454) 	 # Shc for bin 6
LbPMuNuSigma6 = EVal(51.5312 , 3.51393) 	 # Sigma for bin 6
LbPMuNuMean7 = EVal(5458.62 , 10.8554) 	 # Mean for bin 7
LbPMuNuShc7 = EVal(0.00302524 , 0.000278487) 	 # Shc for bin 7
LbPMuNuSigma7 = EVal(58.839 , 7.69287) 	 # Sigma for bin 7
LbPMuNuMean8 = EVal(5475.84 , 7.92761) 	 # Mean for bin 8
LbPMuNuShc8 = EVal(0.00424519 , 0.000273534) 	 # Shc for bin 8
LbPMuNuSigma8 = EVal(46.0698 , 5.82237) 	 # Sigma for bin 8
LbPMuNuMean78 = EVal(5471.72 , 32.1116) 	 # Mean for bin 78
LbPMuNuShc78 = EVal(0.00327671 , 0.000233875) 	 # Shc for bin 78
LbPMuNuSigma78 = EVal(49.9403 , 24.5407) 	 # Sigma for bin 78



#------------------------------------------------------
# Peaking background  Lb -> p mu nu   evttype 14543009
#------------------------------------------------------
#BcJpsiMuNuEff = EVal(2.08798e-07, 5.01756e-09)




