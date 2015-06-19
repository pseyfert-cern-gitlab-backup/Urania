from math import *

er = .502/.245
s_er = sqrt( (.011/.245)**2 + (.013/.502)**2)

Nr = 19035./340129
sNr = sqrt( (158./19035)**2 + (4468./340129)**2)*Nr

BR_phi = .489
sBR_phi = .005
BRu= 1.013
sBRu = 0.034

fdfs = 3.75

BRs = BRu*er*Nr*fdfs/BR_phi
sBRs = sqrt( (sBRu/BRu)**2 + (sBR_phi/BR_phi)**2 + (sNr/Nr)**2 + (s_er/er)**2) *BRs

print BRs, sBRs, .29/fdfs*BRs
