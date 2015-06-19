#--------------------------------------
#
# Parameters of the BsMuMu analysis
#
#--------------------------------------

from math import *
from errors import *

def alpha(vals,f=(1.,0.)):
    """ compute alpha parameter
    it assumes that the last entry in vals is  the number of candidates of the control channels
    f is the fdfs hadronization fraction
    """
    xvals = vals[:-1]
    ncans = vals[-1]
    xvals.append(invert(ncans))
    xvals.append(f)
    x = map(lambda x: x[0],xvals)
    ex = map(lambda x: x[1],xvals)
    al = reduce(lambda xi,xj:xi*xj,x)
    yy = map(lambda xi,exi: (al/xi)*(al/xi)*exi*exi,x,ex)
    #print ' alpha contributions ',x
    #print ' alpha error contributions ',map(sqrt,yy)
    eal = sqrt(reduce(lambda x,y:x+y,yy))
    return al,eal


#===============================================
# 2010 - Analysis note
#===============================================

#------------------------------------------------
# Parameters for the apha table
#------------------------------------------------

#fdfs = (3.71,0.47) # fdfs ration HFAG
#fsfd = invert(fdfs)
#fsfs = (1.,0.)
#fdfd = (1.,0.)

#fkp = (0.605,0.027)  # factor to convert TIS Bhh in TIS Bkpi
#E_BhhClean = (0.64,0.02) # Efficiency of the TIS-Bhh cleaning cuts
#E_BhhMCHLT2 = (0.934,0.)  # MC HLT2 efficiency on Bhh(L0HLT1-TIS)  2010

#BuBR = (5.98e-5,0.22e-5) # Br(B+->JPsiK+)
#BuRatE_recsel = (0.49,0.02) # ratio of rec&sel efficiencies (B+/Bsmumu)
#BuRatE_trg = (0.956,0.05) # ratio of trig efficiencies (B+/Bsmumu
#BuNcan = (12366.,403.) # Number of B+ candidates

#BsBR = (3.4e-5,0.9e-5)
#BsRatE_recsel = (0.25,0.02) 
#BsRatE_trg = (0.956,0.05)
#BsNcan = (760.,71.)

#BdBR = (1.948e-5,0.06e-5)
#BdRatE_recsel = (0.82,0.06) 
#BdRatE_trg = (0.072,0.01)
#BdNcan = (578,74)

#NBhhTisClean = (611.,76.) #  (37 pb-1)
#NBhhTis =  prod([invert(E_BhhClean),NBhhTisClean])
#BdNcan =  prod([invert(E_BhhClean),fkp,NBhhTisClean])

#Bu = [BuBR,BuRatE_recsel,BuRatE_trg,BuNcan]
#Bs = [BsBR,BsRatE_recsel,BsRatE_trg,BsNcan]
#Bd = [BdBR,BdRatE_recsel,BdRatE_trg,BdNcan]
# this is the coefficient to be used in the toys
#Bdp = [BdBR,BdRatE_recsel,BdRatE_trg,invert(fkp)]

# alpha parambers for Bs
#asBu = alpha(Bu,fdfs)
#asBs = alpha(Bs,fsfs)
#asBd = alpha(Bd,fdfs)

# alpha parambers for Bd
#adBu = alpha(Bu,fdfd)
#adBs = alpha(Bs,fsfd)
#adBd = alpha(Bd,fdfd)

# c parameters
#cBu = alpha(Bu,fdfd)
#cBs = alpha(Bs,fsfs)
#bBd = prod(Bdp)

#===============================================
#  Edinburg 2011
#===============================================

def check(chname='Bu'):
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
# Parameters for the alpha table
#------------------------------------------------

#fdfs = EVal(3.71,0.47) # fdfs ration HFAG
# fsfd = EVal(0.265,0.022,0.019) # fsfd LHCb
# fsfs = EVal(0.262,0.19) #0.262+0.19-0.18 LHCb average
fsfd = EVal(0.267,0.020) # LHCb 120711 (low error)
#fsfd = Eval(0.267,0.021) # LHCb 120711 (upper error)
fdfs = fsfd.invert()
fsfs = EVal(1.,0.)
fdfd = EVal(1.,0.)

Bhh_fkp = EVal(0.605,0.027)  # factor to convert TIS Bhh in TIS Bkpi
BhhE_Clean = EVal(0.64,0.02) # Efficiency of the TIS-Bhh cleaning cuts

# trigger efficiency estimated for the JPsi
JpsiE_trg = EVal(0.83,0.004) # Justine 170611
JpsiE_trg = EVal(0.843,0.002) # Justine 120711
# trigger efficiency estimated for the BsMuMu
BmmE_trg = EVal(0.887,0.005) # Justine 170611
BmmE_trg = EVal(0.897,0.003) # Justine 120711
TISE_trg = EVal(0.054,0.01) # Johannes 170611
TISE_trg = EVal(0.053,0.01) # Johannes 120711
#E_trgTIS = (0.054,0.007) # Justine 220611

# MC HLT2 trigger efficiency in Bhh L0xHLT1-TIS (estimated from MC+TCK)
BhhE_HLT2MC = EVal(0.836,0.) # Justine 220611
BhhE_HLT2MC.add_relative_error(0.06) # Johannes 120711 TOCHECK
BhhE_HLT2MC = BhhE_HLT2MC.compress_errors()

# PID efficiency of the cut of the K of the Phi for the BsJPsiPhi selection
KPIDE = EVal(0.95,0.1) # Johannes 230611 (to check! - large error)
KPIDE = EVal(0.903,0.015) # Johannes 070711 (to checck!)
KPIDE = EVal(0.904,0.010) # Johannes 120711 (to checck!)

BsmmBR = EVal(0.32e-8,0.02e-8)
BdmmBR = EVal(0.01e-8,0.001e-8)
BmmE_rec = EVal(0.102,0.001) # Analysis note 2010 (Johannes 070711)
BmmE_sel = EVal(0.518,0.001) # Johannes 070711
BmmE_sel = EVal(0.523,0.001) # Johannes 120711
BmmE_sel = EVal(0.523,0.001)*EVal(0.972,0.) # Johannes 130711
BmmE_recsel = BmmE_sel*BmmE_rec

BuBR = EVal(5.98e-5,0.22e-5) # Br(B+->JPsiK+)
BuE_rec = EVal(0.059,0.001) # Analysis note 2010 (Johannes 070711)
BuE_sel = EVal(0.431,0.001) # Johannes 070711
BuE_sel = EVal(0.432,0.001) # Johannes 120711
BuE_sel = EVal(0.432,0.001)*EVal(0.981,0.) # Johannes 130711
BuE_recsel = BuE_rec*BuE_sel
BuRatE_recsel = EVal(0.49,0.02) # Johannes 170611
BuRatE_recsel = BuE_recsel/BmmE_recsel
BuRatE_recsel.add_relative_error(0.04) # sys extra track 120711
BuRatE_recsel.add_relative_error(0.006) # muonID acceptance 120711 
BuRatE_recsel.add_relative_error(0.001) # muID efficiency 170611
BuRatE_recsel.compress_errors()
BuRatE_recsel = BuRatE_recsel.compress_errors()
#BuRatE_recsel = EVal(BuRatE_recsel.value,0.02) # Set the errors to  070711
BuE_trg = JpsiE_trg
BuRatE_trg = BuE_trg/BmmE_trg
BuRatE_trg.add_relative_error(0.02) # Justine 170711
BuRatE_trg.compress_errors()
BuNcan = EVal(53770.,240.) # Johannes 170611
BuNcan = EVal(52371.,321.) # Johannes 070711
BuNcan = EVal(110361.,376.) # Johannes 120711
BuNcan = EVal(109506.,376.) # Johannes 120711 - Bpt>500
#BuNcan.add_relative_error(0.013) #KL cut sys 070711
#BuNcan.add_relative_error(0.02) #bkg substraction 070711
BuNcan.add_relative_error(0.016) #bkg substraction
BuNcan = BuNcan.compress_errors()

BsBR = EVal(3.4e-5,0.9e-5)
BsE_rec = EVal(0.04,0.001) # Analysis note 2010 (Johannes 070711)
BsE_sel = EVal(0.336,0.001) # Johannes 070711
BsE_sel = EVal(0.340,0.001) # Johannes 120711
BsE_sel = EVal(0.340,0.001)*EVal(0.981,0.) # Johannes 130711
BsE_recsel = BsE_sel*BsE_rec*KPIDE
BsRatE_recsel = BsE_recsel/BmmE_recsel
BsRatE_recsel.add_relative_error(0.08) # track eff 120711
BsRatE_recsel.add_relative_error(0.006) # muonID acceptance 120711 
BsRatE_recsel.add_relative_error(0.001) # muID efficiency 170611
BsRatE_recsel = BsRatE_recsel.compress_errors()
#print ' Errors forced in the rat E_recsel Bs'
#BsRatE_recsel = EVal(val(BsRatE_recsel),0.03) # Set the errors to  070711
BsE_trg = JpsiE_trg
BsRatE_trg = BsE_trg/BmmE_trg
BsRatE_trg.add_relative_error(0.02) # Justine 170711
BsRatE_trg = BsRatE_trg.compress_errors()
BsNcan = EVal(2862.,55.) # Johannes 170611
BsNcan = EVal(2906.,56.) # Johannes 070711
BsNcan = EVal(6041.,80.) # Johannes 120711
BsNcan = EVal(5996.,80.) # Johannes 120711 pBpt>500.
BsNcan.add_relative_error(0.005) # KL cut sys 090711
#BsNcan.add_relative_error(0.022) # KL cut sys 090711
#BsNcan.add_relative_error(0.05) # bkg substraction 000711
BsNcan = BsNcan.compress_errors()

BdBR = EVal(1.948e-5,0.06e-5)
BdE_rec = EVal(0.079,0.001) # Analysis note 2010 (Johannes 070711)
BdE_sel = EVal(0.557,0.001) # Johannes 070711
BdE_sel = EVal(0.581,0.001) # Johannes 120711
BdE_sel = EVal(0.581,0.001)*EVal(0.972,0.) # Johannes 130711
BdE_trg = BhhE_HLT2MC*TISE_trg
BdE_recsel = BdE_sel*BdE_rec
#BdRatE_recsel = EVal(0.82,0.06) # Johannes 170611
BdRatE_recsel = BdE_recsel/BmmE_recsel
BdRatE_recsel.add_relative_error(0.01*sqrt(2.)) # sys hadrons interaction 
BdRatE_recsel.add_relative_error(0.001) # muonID acceptance 170611
BdRatE_recsel.add_relative_error(0.001) # muID efficiency 170611
BdRatE_recsel = BdRatE_recsel.compress_errors()
print ' Errors forced in the rat E_recsel Bd'
BdRatE_recsel = EVal(val(BdRatE_recsel),0.06) # Set the errors to  070711
# TOCHECK 100711
BdRatE_trg = (BhhE_HLT2MC*TISE_trg)/BmmE_trg
BdRatE_trg.add_relative_error(0.07) # Justine 120711
BdRatE_trg.compress_errors()
# NBhhTisClean = (1713,131) # Diego 210611 (150 pb-1)
BhhNcanTisClean = EVal(1947.,110.) # Alessio 240611 (150 pb-1)
BhhNCanTisClean = EVal(3824,367) # Diego 120711 (300 pb-1)
#BhhNCanTisClean.add_error() # Diego 120711 (300 pb-1)
BhhNCanTisClean.add_error(230.) # Systematic between methods 140711 
BhhNcanTisClean = EVal(2201./0.6,107./0.6) # Alessio 120611 (60% of 300 pb-1)
#BhhNcanTisClean.add_relative_error(0.08) # fit modes TOCHECK 100711
BhhNcanTisClean.add_relative_error(0.05) # fitTOCHECK 130711 (Diego humbers)
BhhNcanTisClean = BhhNcanTisClean.compress_errors()
BhhNcanTis =  BhhNcanTisClean/BhhE_Clean
BdNcan =  BhhNcanTis
BdKpiNcan = Bhh_fkp*BdNcan

Bu = (BuBR*BuRatE_recsel*BuRatE_trg)/BuNcan
Bs = (BsBR*BsRatE_recsel*BsRatE_trg)/BsNcan
Bd = (BdBR*BdRatE_recsel*BdRatE_trg)/(Bhh_fkp*BdNcan)
# this is the coefficient to be used in the toys
Bdp = (BdBR*BdRatE_recsel*BdRatE_trg)/Bhh_fkp

# alpha parambers for Bs
Buas = Bu*fdfs
Bsas = Bs
Bdas = Bd*fdfs

# alpha parambers for Bd
Buad = Bu
Bsad = Bs*fsfd
Bdad = Bd

# b parameters - for the toys
Bub = Bu
Bsb = Bs
Bdb = Bdp

# mis-id B->hh misidentified as B->mumu

#number expected for Bd search win, for 150/pb
MisIDBdNorm = EVal(1.21, 0) # Xabier 240611
MisIDBsNorm = EVal(0.14, 0) # Xabier 240611 

def muontrg_efficiencies():
    ejpsi_trg = Jpsi_trg
    ejpsi_trg.add_relative_error(0.05) # TISTOS Justine 120711
    ebsmm_trg = BmmE_trg
    ebsmm_trg.add_relative_error(0.07) # TISTOS Justine 120711
    ebsmm_trg.add_relative_error(0.03) # Extra lines Justine 120711
    return ejpsi_trg,ebsmm_trg
    
def bkgpeak():
    #ejpsi,ebsmm = muontrg_efficiencies()
    #print ' ejpsi, ebsmm',ejpsi,ebsmm
    ehm = EVal(0.5e-2,0.06e-2) # single muon  Xabier 130711
    ehm.add_error(0.08e-2) # single muon  Xabier 130711
    ehm.compress_errors()
    bhhmm = BdNcan/BdRatE_trg
    print ' bhhmm ',bhhmm
    ehm.compress_errors()
    nbkg = bhhmm*ehm*ehm
    ehm2 = EVal(0.48e-4,0.34e-4)*EVal(0.9,0.) # double muon eff * acc^2 Jose 130711
    nbkg2 = BdNcan*ehm2
    print ' nbkg1 ',nbkg
    print ' nbkg2 ',nbkg2
    return bhhmm,nbkg,nbkg2

#pdfs # Xabier 240611 
MisIDBdGL1M1 = 0.0645552709311 
MisIDBdGL1M2 = 0.0743298728995 
MisIDBdGL1M3 = 0.0640098542696 
MisIDBdGL1M4 = 0.0435291522141 
MisIDBdGL1M5 = 0.0223804679552 
MisIDBdGL1M6 = 0.0109818725563 
MisIDBdGL2M1 = 0.0598242410129 
MisIDBdGL2M2 = 0.067349765287  
MisIDBdGL2M3 = 0.0580225275466 
MisIDBdGL2M4 = 0.0381791663092 
MisIDBdGL2M5 = 0.0199659267793 
MisIDBdGL2M6 = 0.0103016337987 
MisIDBdGL3M1 = 0.0564107906703 
MisIDBdGL3M2 = 0.0638321342338 
MisIDBdGL3M3 = 0.0550932110946 
MisIDBdGL3M4 = 0.0367941756854 
MisIDBdGL3M5 = 0.0185135251076 
MisIDBdGL3M6 = 0.00984201301646
MisIDBdGL4M1 = 0.0536837073625 
MisIDBdGL4M2 = 0.0597261885793 
MisIDBdGL4M3 = 0.0515817083185 
MisIDBdGL4M4 = 0.0350721298214 
MisIDBdGL4M5 = 0.0172204586403 
MisIDBdGL4M6 = 0.00877569280173

MisIDBsGL1M1 = 0.15075582885    
MisIDBsGL1M2 = 0.0748142454522  
MisIDBsGL1M3 = 0.0370996669229  
MisIDBsGL1M4 = 0.0139892390469  
MisIDBsGL1M5 = 0.00609787343069 
MisIDBsGL1M6 = 0.00327952856777 
MisIDBsGL2M1 = 0.138201383551   
MisIDBsGL2M2 = 0.0692287983602  
MisIDBsGL2M3 = 0.0325390725083  
MisIDBsGL2M4 = 0.0121445042275  
MisIDBsGL2M5 = 0.00425313861132 
MisIDBsGL2M6 = 0.00292083013067 
MisIDBsGL3M1 = 0.126313092493   
MisIDBsGL3M2 = 0.0666666666667  
MisIDBsGL3M3 = 0.0311555213938  
MisIDBsGL3M4 = 0.0110684089162  
MisIDBsGL3M5 = 0.00363822700487 
MisIDBsGL3M6 = 0.00153727901614 
MisIDBsGL4M1 = 0.116115808353   
MisIDBsGL4M2 = 0.0595951831924  
MisIDBsGL4M3 = 0.0273635664873  
MisIDBsGL4M4 = 0.00871124775813 
MisIDBsGL4M5 = 0.00184473481937 
MisIDBsGL4M6 = 0.000666154240328
