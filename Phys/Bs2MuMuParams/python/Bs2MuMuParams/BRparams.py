# Collection of branching fraction values
from errors import *

LbPMuNuBR = EVal(4.94e-4, 2.19e-4)
PiMuNuBR    = EVal(1.44e-4, 0.05e-4)
KMuNuBR     = EVal(1.27e-4, 0.49e-4)
KMuNuBR2 = EValAsym(1.27e-4, 0.46e-4, -0.26e-4)*EValAsym(1,0.34,-0.30)*EValAsym(1,0.14,-0.13)*EValAsym(1,0.10,-0.09)# from PhysRevD86 114025 (2012)
KMuNuBR = KMuNuBR2.get_eval()


PiMuMuBR    = EVal(2.3e-8, 0.6e-8)*EVal(1.47, 0.20)    #this includes also Bd-> pi0 mu mu 

# Bu -> Jpsi(->mumu)K+
BuBR = EVal(1.028e-3,0.031e-3)*EVal(5.93e-2,0.06e-2)  #Updated to livePDG 10/2013
# was BuBR = EVal(1.016e-3,0.033e-3)*EVal(0.0593,0.0006) #Updated to PDG 2012 04/04/2013
# was BuBR = EVal(6.01e-5,0.21e-5) # Latest PDG 140711

# Bd -> K pi
BdBR = EVal(1.96e-5,0.05e-5) #Updated to livePDG 10/2013
# was BdBR = EVal(1.94e-5,0.06e-5)
