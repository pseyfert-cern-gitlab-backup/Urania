#--------------------------------------
#
# Parameters of the t23m analysis
#
#--------------------------------------

from math import *
from errors import *

#===============================================
# 2012 - analysis of 1 fb-1 dataset
#===============================================

#BR
#BR_DsPhiKKPi = EVal(2.32e-2,0.14e-2)

BR_DsKKPi= EVal(5.49e-2,0.27e-2) # marta, 20/03/12
f_Phi = EVal(0.414,0.008)
f_Phi.add_error(0.005)
f_Phi=f_Phi.compress_errors()

print "f_Phi: " , f_Phi

BR_DsPhiKKPi = BR_DsKKPi*f_Phi

print "BR_DsPhiKKPi: ",BR_DsPhiKKPi

BR_PhiKK = EVal(0.489,0.005)
BR_PhiMM = EVal(2.87e-4,0.19e-4)

BR_DsPhiMMPi = BR_DsPhiKKPi/BR_PhiKK*BR_PhiMM
BR_DsPhiMMPi=BR_DsPhiMMPi.compress_errors()

print "BR_DsPhiMMPi : ",BR_DsPhiMMPi


#fraction from Ds
f_tauFromDs=EVal(0.78,0.05)
BR_DsTauNu = EVal(0.0561,0.0024)

#eGen
eGen_Tau=EVal(0.18,0)
eGen_Ds=EVal(0.177,0)

#ErecSel
#eRecSel_Tau=EVal(0.0543,0.0006)
#eRecSel_Ds=EVal(0.044,0.0002)
#update for sm1 values by JH
#eRecSel_Tau=EVal(0.0517,0.0006)
eRecSel_Tau=EVal(0.0517,0.0022)
eRecSel_Ds=EVal(0.042,0.0002)


eTrRatio=EVal(0.997,0.012)#from tracking map
eTrRatio.add_relative_error(0.027)#hadronic IA 1 pion
eTrRatio=eTrRatio.compress_errors()

#eMuID=EVal(1,0)
eMuID=EVal(0.9732,0.0025)#from data/MC map
eMuID.add_relative_error(0.01)#data map cross check
eMuID=eMuID.compress_errors()

eSmear=EVal(1,0.01)#1% syst from ratio in sm0-sm1.5
#eSmear.compress_errors()

recSelRat_noGen=eRecSel_Ds/eRecSel_Tau*eTrRatio*eMuID* eSmear
recSelRat_noGen=recSelRat_noGen.compress_errors()


tot_Rat_RecSel = eGen_Ds/eGen_Tau* recSelRat_noGen


print "recSelRat_noGen: ",recSelRat_noGen
print "and"
print "tot_Rat_RecSel : ",tot_Rat_RecSel


#eTrg_Tau=EVal(0.461,0.0)#JA todo correct STAT
#eTrg_Ds=EVal(0.343,0.0)#JA todo correct STAT
# Update JH:
eTrg_Tau=EVal(0.461,0.006)
eTrg_Ds=EVal(0.343,0.002)

trgRat = eTrg_Ds/eTrg_Tau
#trgRat.add_relative_error(0.01)#JA FIXME fake stat from note
#trgRat.add_relative_error(0.005)#JA FIXME old syst
trgRat.add_relative_error(0.048)#JA FIXME old syst
trgRat=trgRat.compress_errors()

print "trgRat : ",trgRat

NCand_DsPhiPi = EVal(45672,423)
NCand_DsPhiPi.add_error(822)#syst from bkg substraction
NCand_DsPhiPi=NCand_DsPhiPi.compress_errors()

print "NCand_DsPhiPi : " ,NCand_DsPhiPi

beta = EVal(1.068,0.004)

#alpha = BR_DsPhiMMPi*f_tauFromDs/BR_DsTauNu*tot_Rat_RecSel*trgRat/NCand_DsPhiPi
# now with beta
alpha = BR_DsPhiMMPi*f_tauFromDs/BR_DsTauNu*tot_Rat_RecSel*trgRat/NCand_DsPhiPi*beta

print "*"
print "*"
print " alpha: ",alpha
print "*"
print "*"

#for the note
print BR_DsPhiMMPi*1e5,"& frac{",f_tauFromDs,"}{",BR_DsTauNu,"}&",tot_Rat_RecSel,"&",trgRat,"&",NCand_DsPhiPi,"&",alpha*1e9
