#--------------------------------------
#
# Parameters of the BDT BsMuMu analysis
#
#--------------------------------------

from math import *
from errors import *
import code


#===============================================
# 2012 - analysis of the 2011 1fb dataset
#===============================================


#------------------------------------------------------
# Peaking background  Bd -> pi mu nu 
#------------------------------------------------------

#https://indico.cern.ch/getFile.py/access?contribId=3&resId=0&materialId=slides&confId=209406
PiMuNuTot = EVal( 34.59, 2.056 ) # Ale 20121008

# BDT distribution
PiMuNuFrac1 = EVal( 0.344, 0.0066) # Ale 20121018
PiMuNuFrac2 = EVal( 0.179, 0.0054) # Ale 20121018
PiMuNuFrac3 = EVal( 0.112, 0.0044) # Ale 20121018
PiMuNuFrac4 = EVal( 0.0885, 0.0040) # Ale 20121018
PiMuNuFrac5 = EVal( 0.0905, 0.0040) # Ale 20121018
PiMuNuFrac6 = EVal( 0.0847, 0.0039) # Ale 20121018
PiMuNuFrac7 = EVal( 0.0651, 0.0035) # Ale 20121018
PiMuNuFrac8 = EVal( 0.0363, 0.0026) # Ale 20121018

# mass distribution
PiMuNuMean1 = EValAsym( 4897.6,  +8.9,  -9.9) # Ale 20121018
PiMuNuMean2 = EValAsym( 4910.4, +11.1, -12.5) # Ale 20121018
PiMuNuMean3 = EValAsym( 4941.4,  +8.8,  -9.8) # Ale 20121018
PiMuNuMean4 = EValAsym( 4940.8,  +8.9, -10.1) # Ale 20121018
PiMuNuMean5 = EValAsym( 4922.9, +12.8, -14.9) # Ale 20121018
PiMuNuMean6 = EValAsym( 4936.,  +13.1, -15.9) # Ale 20121018
PiMuNuMean7 = EValAsym( 4962.2,  +8.5,  -9.5) # Ale 20121018
PiMuNuMean8 = EValAsym( 5009.5,  +7.4,  -8.2) # Ale 20121018

PiMuNuSigma1 = EValAsym( 120.4, +3.9,  -3.6 ) # Ale 20121018
PiMuNuSigma2 = EValAsym( 119.3, +4.9,  -4.6 ) # Ale 20121018
PiMuNuSigma3 = EValAsym( 106.4, +3.9,  -3.7) # Ale 20121018
PiMuNuSigma4 = EValAsym( 103.2, +4.4,  -4.1) # Ale 20121018
PiMuNuSigma5 = EValAsym( 115.5, +5.7,  -5.1) # Ale 20121018
PiMuNuSigma6 = EValAsym( 118.9, +7.2,  -6.3 ) # Ale 20121018
PiMuNuSigma7 = EValAsym( 103.7, +4.2,  -3.9 ) # Ale 20121018
PiMuNuSigma8 = EValAsym( 102.4, +4.4,  -4.1 ) # Ale 20121018


#------------------------------------------------------
# Peaking background  B -> pi mu mu 
#------------------------------------------------------


#https://indico.cern.ch/getFile.py/access?contribId=7&resId=0&materialId=slides&confId=208195
#PiMuMuTot = EVal( 11.4, 4.9 ) # Serena 20120914
PiMuMuTot = EVal( 10.1, 3.05 ) # Ale 20121018

# BDT distribution
PiMuMuFrac1 = EVal( 0.368 , 0.0074 ) # Ale 20121018
PiMuMuFrac2 = EVal( 0.178 , 0.0058 ) # Ale 20121018
PiMuMuFrac3 = EVal( 0.102 , 0.0046 ) # Ale 20121018
PiMuMuFrac4 = EVal( 0.0866, 0.0043 ) # Ale 20121018
PiMuMuFrac5 = EVal( 0.0840, 0.0042 ) # Ale 20121018
PiMuMuFrac6 = EVal( 0.0705, 0.0039 ) # Ale 20121018
PiMuMuFrac7 = EVal( 0.0672, 0.0038 ) # Ale 20121018
PiMuMuFrac8 = EVal( 0.0439, 0.0031 ) # Ale 20121018

# mass distribution
#Fra email 17 oct 2012
PiMuMuMean1 = EVal( 4945.1,  5.6) # Ale 20121018
PiMuMuMean2 = EVal( 4952.5,  8.4) # Ale 20121018
PiMuMuMean3 = EVal( 4959.8,  9.2) # Ale 20121018
PiMuMuMean4 = EVal( 4951.8, 13.5) # Ale 20121018
PiMuMuMean5 = EVal( 4978.3,  6.9) # Ale 20121018
PiMuMuMean6 = EVal( 4964.3, 12.0) # Ale 20121018
PiMuMuMean7 = EVal( 4960.4, 17.2) # Ale 20121018
PiMuMuMean8 = EVal( 4987.8, 13.3) # Ale 20121018

PiMuMuSigma1 = EVal( 78.3 , 2.7 ) # Ale 20121018
PiMuMuSigma2 = EVal( 82.6 , 4.4 ) # Ale 20121018
PiMuMuSigma3 = EVal( 80.5 , 5.6 ) # Ale 20121018
PiMuMuSigma4 = EVal( 87.4 , 7.2 ) # Ale 20121018
PiMuMuSigma5 = EVal( 71.2 , 4.9 ) # Ale 20121018
PiMuMuSigma6 = EVal( 82.2 , 8.0 ) # Ale 20121018
PiMuMuSigma7 = EVal( 93.8 , 10.8) # Ale 20121018
PiMuMuSigma8 = EVal( 84.4 , 9.2 ) # Ale 20121018
