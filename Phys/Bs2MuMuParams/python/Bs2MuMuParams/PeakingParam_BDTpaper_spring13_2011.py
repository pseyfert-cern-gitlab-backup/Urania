#--------------------------------------
#
# Parameters of the BDT BsMuMu analysis
#
#--------------------------------------

from math import *
from errors import *
import code


#===============================================
#
# Input from the 2011 dataset for the spring 2013 analysis
# with OLD BDT (1+1fb paper BDT)
#
#===============================================


#------------------------------------------------------
# Peaking background  Bd -> pi mu nu   evttype 11512012
#------------------------------------------------------

PiMuNuTot = EVal( 37.909, 4.09004)   # Fra 20130608

# BDT distribution
PiMuNuFrac1 = EVal(0.351835  ,  0.00185328  )    # Fra 20130608
PiMuNuFrac2 = EVal(0.183302  ,  0.00135869  )    # Fra 20130608
PiMuNuFrac3 = EVal(0.109348  ,  0.00104016  )    # Fra 20130608
PiMuNuFrac4 = EVal(0.0947249 ,  0.000954899 )    # Fra 20130608
PiMuNuFrac5 = EVal(0.0854256 ,  0.000867114 )    # Fra 20130608
PiMuNuFrac6 = EVal(0.0761897 ,  0.000763057 )    # Fra 20130608
PiMuNuFrac7 = EVal(0.0626599 ,  0.000656953 )    # Fra 20130608
PiMuNuFrac8 = EVal(0.0365143 ,  0.000460036 )    # Fra 20130608


# mass distribution
PiMuNuMean1 = EVal(4908.82	,   2.28785	 ) # Fra 20130608
PiMuNuMean2 = EVal(4937.05	,   2.26698	 ) # Fra 20130608
PiMuNuMean3 = EVal(4942.91	,   2.74816	 ) # Fra 20130608
PiMuNuMean4 = EVal(4943.14	,   3.13883	 ) # Fra 20130608
PiMuNuMean5 = EVal(4949.26	,   3.0764	 ) # Fra 20130608
PiMuNuMean6 = EVal(4956.94	,   2.75361	 ) # Fra 20130608
PiMuNuMean7 = EVal(4961.1	,   3.06138	 ) # Fra 20130608
PiMuNuMean8 = EVal(4996.79	,   2.83329	 ) # Fra 20130608


PiMuNuSigma1 = EVal(113.365	,  0.819661 )  # Fra 20130608
PiMuNuSigma2 = EVal(102.273	,  0.846865 )  # Fra 20130608
PiMuNuSigma3 = EVal(102.834	,  1.02327  )  # Fra 20130608
PiMuNuSigma4 = EVal(105.425	,  1.1668   )  # Fra 20130608
PiMuNuSigma5 = EVal(104.611	,  1.21352  )  # Fra 20130608
PiMuNuSigma6 = EVal(102.73	,  1.14223  )  # Fra 20130608
PiMuNuSigma7 = EVal(107.849	,  1.35107  )  # Fra 20130608
PiMuNuSigma8 = EVal(107.899	,  1.60405  )  # Fra 20130608




#------------------------------------------------------
# Peaking background  B -> pi mu mu 
#------------------------------------------------------

## TO BE CHECKED 
PiMuMuTot = EVal( 9.16722, 2.78453) # Max 20130607

# BDT distribution
PiMuMuFrac1 = EVal( 0.368175	, 0.00926833 ) # Max 20130607
PiMuMuFrac2 = EVal( 0.178021	, 0.00644481 ) # Max 20130607
PiMuMuFrac3 = EVal( 0.101727	, 0.00487182 ) # Max 20130607
PiMuMuFrac4 = EVal( 0.0865609	, 0.00449402 ) # Max 20130607
PiMuMuFrac5 = EVal( 0.0839944	, 0.00442689 ) # Max 20130607
PiMuMuFrac6 = EVal( 0.070462	, 0.00405463 ) # Max 20130607
PiMuMuFrac7 = EVal( 0.0671955	, 0.00395953 ) # Max 20130607
PiMuMuFrac8 = EVal( 0.0438637	, 0.00319909 ) # Max 20130607


# mass distribution
PiMuMuMean1 = EVal( 4947.68	, 5.12753 )  # Max 20130607
PiMuMuMean2 = EVal( 4952.88	, 8.51139 )  # Max 20130607
PiMuMuMean3 = EVal( 4959.69	, 9.04759 )  # Max 20130607
PiMuMuMean4 = EVal( 4948.07	, 15.2097 )  # Max 20130607
PiMuMuMean5 = EVal( 4975.33	, 8.46358 )  # Max 20130607
PiMuMuMean6 = EVal( 4969.47	, 10.1906 )  # Max 20130607
PiMuMuMean7 = EVal( 4968.57	, 11.7258 )  # Max 20130607
PiMuMuMean8 = EVal( 4979.46	, 15.5745 )  # Max 20130607

PiMuMuSigma1 = EVal( 75.1968	, 2.34721 )  # Max 20130607
PiMuMuSigma2 = EVal( 84.4319	, 4.4954  )  # Max 20130607
PiMuMuSigma3 = EVal( 77.6875	, 5.54683 )  # Max 20130607
PiMuMuSigma4 = EVal( 88.0605	, 7.60866 )  # Max 20130607
PiMuMuSigma5 = EVal( 78.2174	, 6.77755 )  # Max 20130607
PiMuMuSigma6 = EVal( 78.56  	, 6.23228 )  # Max 20130607
PiMuMuSigma7 = EVal( 82.0558	, 6.93355 )  # Max 20130607
PiMuMuSigma8 = EVal( 88.41  	, 9.98732 )  # Max 20130607
