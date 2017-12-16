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
 

def check(chname='Bu'):  
    """ print the relevant normalization factor for Bu,Bs,Bd 
    """
    def sval(vname):
        sname = chname+str(vname)
        v = eval(sname)
        return v
    print ' value fdfs ',fdfs
    print ' value for: ',chname
    print ' BR ',sval('BR')
    print ' Eff rec ',sval('E_rec')
    print ' Eff sel ',sval('E_sel')
    print ' Eff recsel ',sval('E_recsel')
    print ' Eff trg ',sval('E_trg')
    print ' Eff (Bmm) recsel ',BmmE_recsel
    print ' Eff (Bmm) trg ',BmmE_trg
    print ' Rat E recsel ',sval('RatE_recsel')
    print ' Rat E trg ',sval('RatE_trg')
    print ' Ncan ',sval('Ncan')
    print ' alpha-nude ',sval('')
    print ' alpha_d ',sval('ad')
    print ' alpha_s ',sval('as')
    print ' cpar_toys ',sval('b')

#------------------------------------------------
# Parameters for the absolute alpha table
#------------------------------------------------

#Total number of taus produced
N_Tau = EVal(7.95e10, 0.83e10)
print "N_Tau : ",N_Tau

#eGen
eGen_Tau=EVal(0.18,0.001)

#ErecSel
eRecSel_Tau=EVal(0.0517,0.0067)

#Etr
#eTr_Tau=EVal(1,0.012)
# Jon: new values
eTr_Tau=EVal(1.05,0.01)
eTr_Tau.add_relative_error(0.028)
eTr_Tau=eTr_Tau.compress_errors()

#EmuID
eMuID_Tau=EVal(1.085,0.011)
eMuID_Tau.add_relative_error(0.11)
eMuID_Tau=eMuID_Tau.compress_errors()

eTrMu_Tau=eTr_Tau*eMuID_Tau
eTrMu_Tau=eTr_Tau*eMuID_Tau.compress_errors()
print "eTrMu_Tau: ",eTrMu_Tau

#EselTrig
eSelTrig_Tau=EVal(0.461,0.023)

#eGenRecSel = eGen_Tau*eRecSel_Tau
#eGenRecSel=eGenRecSel.compress_errors()
#New: add tracking and muonID
eGenRecSel = eGen_Tau*eRecSel_Tau*eTr_Tau*eMuID_Tau
eGenRecSel=eGenRecSel.compress_errors()

eGenRecSelTrig = eGenRecSel*eSelTrig_Tau
eGenRecSelTrig=eGenRecSelTrig.compress_errors()

print "eGenRecSel: ",eGenRecSel
print "and"
print "eGenRecSelTrig : ",eGenRecSelTrig

N_Tau_Sel = N_Tau*eGenRecSelTrig
N_Tau_Sel=N_Tau_Sel.compress_errors()

print "N_Tau_Sel : ",N_Tau_Sel

numerator = EVal(1, 0)

alpha = numerator/N_Tau_Sel

print "*"
print "*"
print " alpha: ",alpha
print "*"
print "*"

#for the note
#print BR_DsPhiMMPi*1e5,"& frac{",f_tauFromDs,"}{",BR_DsTauNu,"}&",tot_Rat_RecSel,"&",trgRat,"&",NCand_DsPhiPi,"&",alpha*1e9
