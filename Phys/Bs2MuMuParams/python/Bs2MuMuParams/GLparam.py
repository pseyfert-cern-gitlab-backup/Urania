#--------------------------------------
#
# Parameters of the GL BsMuMu analysis
#
#--------------------------------------

from math import *
from errors import *

from alphaparam import *

#===============================================
# 2010 - Analysis note
#===============================================

#------------------------------------------------
# Parameters for the toys
#------------------------------------------------

# PDF signal calibration

# Bhh TIS events in bins
TisTot = NBhhTis # They shoud match with the alphaparam file
Tis2 = (766.,66.,0.) # Alessio 240611
Tis3 = (577.,33.,0.) #  Alessio 240611
Tis4 = (908.,44.,0.) # Alessio 240611
# TisTot = NBhhTis # corrected by the clean cuts! 
# Tis2 = (589.,76.,0.) # Diego 210611
# Tis3 = (651.,46.,0.) #  Diego 210611
# Tis4 = (799.,131.,0.) # Diego 210611
# Tis1 = (693,192) Justine 210611
# Tis2 = (617.,66.,0.) # Justine 210611
# Tis3 = (684.,34.,0.) # Justine 210611
# Tis4 = (810.,35.,0.) # Justine 210611

# trigger bias correction on the GL or 'Justine' correction
Jave =5.35 # Average of the Justine numbers for the 4th bins
Justine1 = (4.8/Jave,0.1/Jave) # Justine, Marco 230611
Justine1 = (-9999.,-9999.)  # requirementn of the toys
Justine2 = (5.0/Jave,0.1/Jave) # Justine, Marco 230611
Justine3 = (5.3/Jave,0.1/Jave) # Justine, Marco 230611
Justine4 = (6.3/Jave,0.1/Jave) # Justine, Marco 230611

# Mass measurements
MassMeanBs = (5358.0,1.0) # Diego 170611
MassMeanBd = (5272.0,1.0) # Diego 170611
MassReso = (24.02,0.1,0.8) # Christian 170611 (Bs mass resolution)
MassReso = combine_errors([MassReso])[0]
CBTrans = (2.11,0.05)

# PDF for the bgk: k-coeficient of the exp fit
BkgMassk1 = (-7.4e-4,2.4e-5) # Marco 230611
BkgMassk2 = (-9.3e-4,1.7e-4) # Marco 230611
BkgMassk3 = (-1.2e-3,4.0e-4) # Marco 230611
BkgMassk4 = (-1.3e-3,1.4e-3) # Marco 230611

# total number of events in the bkg sidebands
SbGL1 = (11869.0,) # Marco 230611
SbGL2 = (220.0,) # Marco 230611
SbGL3 = (44.0,) # Marco 230611
SbGL4 = (4.0,) # Marco 230611

# with of the sidebands
BlindWidth = 60
BsMassPDG = 5366.3
BMassL0 = BsMassPDG-1200.
BMassL1 = BsMassPDG+1200.
BMassT0 = BsMassPDG-600.
BMassT1 = BsMassPDG+600.
# BMassBlind0 = val(MassMeanBd)-BlindWidth # 2010
# BMassBlind1 = val(MassMeanBs)+BlindWidth # 2010
BMassBlind0 = 5179. # Justine 240611 (till Edinburg) 
BMassBlind1 = 5466. # Justine 240611 (till Edinburg) 
# BMassB0 = 5207. # Marco 240611 (for EPS) 
# BMassB1 = 5423. # Marco 240611 (for EPS) 

GL1MassSb1 = BMassT0
GL1MassSb2 = BMassBlind0
GL1MassSb3 = BMassBlind1
GL1MassSb4 = BMassT1
GL2MassSb1 = BMassT0
GL2MassSb2 = BMassBlind0
GL2MassSb3 = BMassBlind1
GL2MassSb4 = BMassT1
GL3MassSb1 = BMassT0
GL3MassSb2 = BMassBlind0
GL3MassSb3 = BMassBlind1
GL3MassSb4 = BMassT1
GL4MassSb1 = BMassT0
GL4MassSb2 = BMassBlind0
GL4MassSb3 = BMassBlind1
GL4MassSb4 = BMassT1

#===============================================
#  Edinburg 2011
#===============================================

