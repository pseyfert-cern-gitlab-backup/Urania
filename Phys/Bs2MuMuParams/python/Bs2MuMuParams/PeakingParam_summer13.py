#--------------------------------------
#
# Parameters of the Peakking backgrounds for BsMuMu analysis
#
#--------------------------------------

from math import *
from errors import *
import code

#===============================================
#
# Inputs for the 2011+2012 datasets as 1 dataset
# summer 2013
# with BDT12
#
#===============================================


#------------------------------------------------------
# Peaking background  Bd -> pi mu nu   evttype 11512012
#------------------------------------------------------

PiMuNuTot = EVal( 91.6413, 9.89294) # Fra 20130608
#PiMuNuTot = EVal( 37.8064, 4.08131) # Fra 20130607

# BDT distribution
PiMuNuFrac1 = EVal(0.359845   ,  0.00189116 ) # Fra 20130608
PiMuNuFrac2 = EVal(0.183973   ,  0.0013561  ) # Fra 20130608
PiMuNuFrac3 = EVal(0.109103   ,  0.00103675 ) # Fra 20130608
PiMuNuFrac4 = EVal(0.0937113  ,  0.00094049 ) # Fra 20130608
PiMuNuFrac5 = EVal(0.0841516  ,  0.00086407 ) # Fra 20130608
PiMuNuFrac6 = EVal(0.0744114  ,  0.00075496 ) # Fra 20130608
PiMuNuFrac7 = EVal(0.0600769  ,  0.00064288 ) # Fra 20130608
PiMuNuFrac8 = EVal(0.0347283  ,  0.00044770 ) # Fra 20130608
PiMuNuFrac78 =EVal(0.0948053  ,  0.00078341 ) # Fra 20130608


# mass distribution
PiMuNuMean1 = EVal(4909.14  ,   2.26393	) # Fra 20130608
PiMuNuMean2 = EVal(4935.55  ,   2.33816	) # Fra 20130608
PiMuNuMean3 = EVal(4942.07  ,   2.78238	) # Fra 20130608
PiMuNuMean4 = EVal(4938.86  ,   3.54018	) # Fra 20130608
PiMuNuMean5 = EVal(4946.5   ,   3.32481	) # Fra 20130608
PiMuNuMean6 = EVal(4954.62  ,   2.9519	) # Fra 20130608
PiMuNuMean7 = EVal(4963.4   ,   3.02133	) # Fra 20130608
PiMuNuMean8 = EVal(4997.8   ,   2.8645	) # Fra 20130608
PiMuNuMean78 =EVal(4974.05  ,   2.2781	) # Fra 20130608
        
PiMuNuSigma1 = EVal(112.963   ,   0.807301  ) # Fra 20130608
PiMuNuSigma2 = EVal(103.827   ,   0.880178  ) # Fra 20130608
PiMuNuSigma3 = EVal(103.089   ,   1.02783   ) # Fra 20130608
PiMuNuSigma4 = EVal(110.954   ,   1.40844   ) # Fra 20130608
PiMuNuSigma5 = EVal(107.206   ,   1.36293   ) # Fra 20130608
PiMuNuSigma6 = EVal(105.741   ,   1.28758   ) # Fra 20130608
PiMuNuSigma7 = EVal(106.489   ,   1.3182    ) # Fra 20130608
PiMuNuSigma8 = EVal(107.633   ,   1.62351   ) # Fra 20130608
PiMuNuSigma78 =EVal(109.684   ,   1.11209   ) # Fra 20130608


#------------------------------------------------------
# Peaking background  B -> pi mu mu 
#------------------------------------------------------

#with new betas
PiMuMuTot = EVal( 19.1341, 5.81253)	 # Max 20130607


# BDT distribution
PiMuMuFrac1 = EVal(0.385683    ,  0.00969065 )   # Max 20130607
PiMuMuFrac2 = EVal(0.177258    ,  0.00656963 )   # Max 20130607
PiMuMuFrac3 = EVal(0.108108    ,  0.00513058 )   # Max 20130607
PiMuMuFrac4 = EVal(0.0886292   ,  0.00464543 )   # Max 20130607
PiMuMuFrac5 = EVal(0.0827855   ,  0.00448967 )   # Max 20130607
PiMuMuFrac6 = EVal(0.0696372   ,  0.00411773 )   # Max 20130607
PiMuMuFrac7 = EVal(0.0484539   ,  0.0034348  )   # Max 20130607
PiMuMuFrac8 = EVal(0.0394449   ,  0.00309908 )   # Max 20130607
PiMuMuFrac78= EVal(0.0878987   ,  0.00462625 )   # Max 20130607


# mass distribution
PiMuMuMean1 = EVal(4929.86   ,	   7.09215   )   # Max 20130607
PiMuMuMean2 = EVal(4959.99   ,     7.04701   )   # Max 20130607
PiMuMuMean3 = EVal(4951.26   ,     10.5187   )   # Max 20130607
PiMuMuMean4 = EVal(4947.68   ,     13.1185   )   # Max 20130607
PiMuMuMean5 = EVal(4954.84   ,     13.7751   )   # Max 20130607
PiMuMuMean6 = EVal(4967.61   ,     13.6778   )   # Max 20130607
PiMuMuMean7 = EVal(4971.33   ,     14.2859   )   # Max 20130607
PiMuMuMean8 = EVal(4987.7    ,     13.7244   )   # Max 20130607
PiMuMuMean78= EVal(4979.23   ,     9.99327   )   # Max 20130607

PiMuMuSigma1 = EVal(78.6312  ,   4.12245  )   # Max 20130607
PiMuMuSigma2 = EVal(82.9943  ,   3.13368  )   # Max 20130607
PiMuMuSigma3 = EVal(81.5251  ,   5.96555  )   # Max 20130607
PiMuMuSigma4 = EVal(82.6155  ,   6.5539	  )   # Max 20130607
PiMuMuSigma5 = EVal(88.0004  ,   7.96315  )   # Max 20130607
PiMuMuSigma6 = EVal(88.6838  ,   9.08997  )   # Max 20130607
PiMuMuSigma7 = EVal(77.5482  ,   8.64539  )   # Max 20130607
PiMuMuSigma8 = EVal(81.2671  ,   9.23633  )   # Max 20130607
PiMuMuSigma78= EVal(83.3689  ,   6.15213  )   # Max 20130607
