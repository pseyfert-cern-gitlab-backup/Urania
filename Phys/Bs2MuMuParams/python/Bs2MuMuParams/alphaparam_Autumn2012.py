#--------------------------------------
#
# Parameters of the BsMuMu analysis
#
#--------------------------------------

from math import *
from errors import *

#===============================================
# 2012 - analysis of the 2012 dataset
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
    print ' ->  alpha_d for toys (w. masswin)  ',sval('ad_mw')
    print ' alpha_s ',sval('as')
    print ' ->  alpha_s for toys (w. masswin) ',sval('as_mw')
    print ' cpar_toys ',sval('b')

#------------------------------------------------
# Parameters for the alpha table
#------------------------------------------------

# BRs for Bsmumu and Bdmumu in SM :
#http://arxiv.org/abs/1208.0934
#http://arxiv.org/abs/1204.1737
Bsmumu_BR = EVal( 3.23e-9, 0.27e-9 )*EVal(1.096, 0.016)
Bdmumu_BR = EVal( 1.07e-10, 0.1e-10)

# ratio of production fractions (still valid):
# this is what we quoted in the last paper:
#fsfd = EVal(0.267,0.021) # LHCb 120711 (upper error)
fsfd = EVal(0.256,0.020) # LHCb October 2012
fdfs = fsfd.invert()
fsfs = EVal(1.,0.)
fdfd = EVal(1.,0.)

# factor to covert TIS Bhhin TIS Bkpi (still valid) (?)
# efficiency of the TIS-Bhh cleaning cuts is =1 (no cleaning cuts):
Bhh_fkp = EVal(0.605,0.027)  # factor to convert TIS Bhh in TIS Bkpi
#BhhE_Clean = EVal(0.64,0.02) # Efficiency of the TIS-Bhh cleaning cuts
BhhE_Clean = EVal(1.00,0.00) # Efficiency of the TIS-Bhh cleaning cuts

# trigger efficiency estimated for the JPsi
# number used for 0.37 fb-1 but in the note 078 we had: (82.3 +-0.2 +-3.8)%
#JpsiE_trg = EVal(0.823,0.002) # Justine 090911 - 
# this is the new number evaluated on 981 pb-1:
#JpsiE_trg = EVal(0.859,0.004) # Justine's email 11/12 - 
#JpsiE_trg = EVal(0.872,0.004) # Justine 200112
JpsiE_trg = EVal(0.848,0.004) # Justine 280912
#BmmE_trg = EVal(0.914,0.004)#Justine 200112
BmmE_trg = EVal(0.910,0.004) #Justine 280912

# trigger efficiency estimated for the BsMuMu
# number used for 0.37 fb-1 but in the note we had: (5.3 +-0.1 +-0.4)$
#TISE_trg = EVal(0.051,0.001) # Johannes 090911
# number for 1 fb-1  (Johannes, 13/01/2012, 981 pb-1):
#TISE_trg = EVal(0.0513,0.0009) # Johannes 130112
TISE_trg = EVal(0.0577,0.0004) # Siim
TISE_trg.add_relative_error(0.004) # Johannes 190711 (We keep the same) 
TISE_trg= TISE_trg.compress_errors()# Johannes 190711


# MC HLT2 trigger efficiency in Bhh L0xHLT1-TIS (estimated from MC+TCK):
# number used in 0.37 fb-1, to be updated with stripping 17.
BhhE_HLT2MC = EVal(0.836,0.) # Justine 220611
BhhE_HLT2MC.add_relative_error(0.06) # Johannes 120711
BhhE_HLT2MC = BhhE_HLT2MC.compress_errors()

# PID efficiency of the cut of the K of the Phi for the BsJPsiPhi selection
# number used in 0.37 fb-1:
#KPIDE = EVal(0.904,0.026) # Johannes 140711 - update error 031011 
# number for 1 fb-1:

KPIDE = EVal(0.914,0.009) # Johannes 130112
KPIDE.add_relative_error(0.01) # Johannes 240112 additional syst
KPIDE=KPIDE.compress_errors()

# reco and sele for Bmumu:
BsmmBR = EVal(0.32e-8,0.02e-8)
BdmmBR = EVal(0.01e-8,0.001e-8)
BmmE_rec = EVal(0.127149,0.001267)     # Francesco 21092012
BmmE_tracking = EVal(0.99157, 0.00280) # Francesco 21092012
BmmE_rec=BmmE_rec*BmmE_tracking

#BmmE_BDTS_005=EVal(0.9210,0.0007)#Flavio 200112

#BmmE_fiducial=EVal(0.981,0.)#johannes 230112

# No additional error on mw efficiency as it's contained in sel eff
BmmE_massCorr = EVal(0.987479, 0.002)# Francesco 21092012
BmmE_mw =EVal(0.389659/0.427547,0.000001)*BmmE_massCorr  # Francesco 28092012

BmmE_49006000 = 0.9928  #efficiency of mass window [4900,6000]

BmmE_ghostProb = EVal(0.9944, 0.0001) #Siim 
BmmE_sel =EVal(0.427547,0.0014) * BmmE_ghostProb  # Francesco 28092012  without mass window
BmmE_recsel = BmmE_sel*BmmE_rec

# =========================
# BuJpsiK normalization :
# =========================
# reco and sele for BuJpsiK:
#BuBR = EVal(6.01,0.21) # Br(B+->JPsiK+) Latest PDG 140711
BuBR = EVal(6.01e-5,0.21e-5) # Br(B+->JPsiK+) Latest PDG 140711
# rec = 0.500811    gen = 0.1567
BuE_rec = EVal(0.0784771,0.0014) # Francesco 21092012
BuE_tracking = EVal(0.98638,0.00410) #Francesco 21092012
BuE_rec=BuE_rec*BuE_tracking

#BuE_BDTS_005=EVal(0.9228,0.0006)#Flavio 200112

#BuE_fiducial=EVal(0.988,0.)#johannes 230112
BuE_massCorr = EVal(0.999999, 0.000001) #Francesco 21092012 (could be removed...) 
#   recsel = 0.1624 +- 0.0010
BuE_sel = EVal(0.32427402752735063, 0.001 )*BuE_massCorr #Francesco 28092012


# number for 0.37 fb-1 (error added below)
# Bu_MuId = EVal(0.997,0.) # Barbara 041011
# number for 1.0 fb-1:
#Bu_MuId = EVal(1.010,0.) # Barbara 091211
Bu_MuId = EVal(1.054,0.)  # Barbara 250912

 
BuE_sel=BuE_sel*Bu_MuId
BuE_recsel = BuE_rec*BuE_sel
BuRatE_recsel = BuE_recsel/BmmE_recsel
# I separate the mass correction as it is not needed for the alpha for the fit 
BuRatE_massCorr = BuE_massCorr/BmmE_massCorr

##BuRatE_recsel.add_relative_error(1.002-1.001)#Flavio, 230112, BDTS max diff between ratio sm0-sm1-sm15
## Remove as this is now included in the selection eff (Francesco)

#BuRatE_recsel.add_relative_error(0.013) # Johannes  sys extra track material 200112
BuRatE_recsel.add_relative_error(0.013) # Francesco sys extra track material 250912
BuRatE_recsel.add_relative_error(0.004) # Johannes sys extra track correlated 200112 (unchanged) Francesco 25092012
#BuRatE_recsel.add_relative_error(0.004) # Johannes sys diff stp13b-stp17 200112 (removed) Francesco 25092012
# number for 0.37 fb-1 (Barbara)
# BuRatE_recsel.add_relative_error(0.013) # muID acceptance and efficiency Barbara 041011
# number for 1.0 fb-1 (Barbara)
#BuRatE_recsel.add_relative_error(0.007) # muID acceptance and efficiency Barbara 091211
#BuRatE_recsel.add_relative_error(0.007) # muID acceptance and efficiency Barbara 240112
BuRatE_recsel.add_relative_error(0.021) # muID acceptance and efficiency Barbara 250912



BuRatE_recsel = BuRatE_recsel.compress_errors()
BuE_trg = JpsiE_trg
BuRatE_trg = BuE_trg/BmmE_trg

BuRatE_trg.add_relative_error(0.01) # Justine 200112, syst from map ratio
BuRatE_trg.add_relative_error(0.02) # Justine 200112, syst from restricted triggers
BuRatE_trg=BuRatE_trg.compress_errors()
# number for 0.37 fb-1
#BuNcan = EVal(124518.,364.) # Johannes 020911 - 341pb - Bpt>500, tau<7.36, Pt < 1TeV
# number for 1.0 fb-1
#BuNcan = EVal(367256.,873.) # Johannes 130112
BuNcan = EVal(424222.5,699.9)# Siim 18092012 
#EVal(340129,640)#johannes 230112, 1025pb lnf, fiducial, BDTS 0.05

#BuNcan.add_relative_error(0.013) #Johannes, 230112 bkg substraction
BuNcan.add_relative_error(0.003) #Siim, 18092012 bkg substraction
BuNcan = BuNcan.compress_errors()

## # =========================
## # BsJpsiPhi normalization :
## # =========================

## BsBR = EVal(3.4e-5,0.9e-5)
## BsE_rec = EVal(0.040,0.001) # Analysis note 2010 (Johannes 070711)

## BsE_tracking = EVal(1.020,0.005)#Johannes 200112
## BsE_rec=BsE_rec*BsE_tracking


## BsE_BDTS_005=EVal(0.9170,0.0007)#Flavio 200112

## BsE_fiducial=EVal(0.987,0.)#johannes 230112

## BsE_sel = EVal(0.340*0.988,0.001)*BsE_fiducial*BsE_BDTS_005 # Johannes 230112, stp13b*extra cut eff stp17
## # number for 0.37 fb-1 
## #Bs_MuId = EVal(0.997,0.) # Barbara 041011
## # number for 1 fb-1:
## #Bs_MuId = EVal(1.010,0.) # Barbara 091211
## #Bs_MuId = EVal(1.038,0.) # Barbara 240112
## #Bs_MuId = EVal(1.038,0.) # Barbara 240112
## Bs_MuId = EVal(1.054,0.) # Barbara 250912

## BsE_sel=BsE_sel*Bs_MuId
## BsE_recsel = BsE_sel*BsE_rec*KPIDE
## BsRatE_recsel = BsE_recsel/BmmE_recsel

## # check if these numbers are still valid:
## BsRatE_recsel.add_relative_error(0.027) # Johannes track eff material 200112
## BsRatE_recsel.add_relative_error(0.004*2) # Johannes track eff syst correlated 200112
## BsRatE_recsel.add_relative_error(0.004*2) # Johannes track eff stp13b-stp17 200112
## BsRatE_recsel.add_relative_error(0.999-0.992)#Flavio, 230112, BDTS max diff between ratio sm0-sm1-sm15
## # number for 0.37 fb-1
## #BsRatE_recsel.add_relative_error(0.013) # muID acceptance and efficiency Barbara 041011
## # number for 1 fb-1
## #BsRatE_recsel.add_relative_error(0.007) # muID acceptance and efficiency Barbara 091211
## #BsRatE_recsel.add_relative_error(0.007) # muID acceptance and efficiency Barbara 240112
## BsRatE_recsel.add_relative_error(0.021) # muID acceptance and efficiency Barbara 250912
## BsRatE_recsel = BsRatE_recsel.compress_errors()
## #print ' Errors forced in the rat E_recsel Bs'
## #BsRatE_recsel = EVal(val(BsRatE_recsel),0.03) # Set the errors to  070711
## BsE_trg = JpsiE_trg
## BsRatE_trg = BsE_trg/BmmE_trg

## BsRatE_trg.add_relative_error(0.01) # Justine 200112, syst from map ratio
## BsRatE_trg.add_relative_error(0.02) # Justine 200112, syst from restricted triggers

## BsRatE_trg = BsRatE_trg.compress_errors()
## # number for 0.37 fb-1
## #BsNcan = EVal(6940.,86.) # Johannes 020911 341pb - pBpt>500, tau<7.36, PT<1TeV
## # number for 1.0 fb-1
## #BsNcan = EVal(20854.,146.) # Johannes 130112
## BsNcan = EVal(19035.,139.) #johannes 230112, 1025pb lnf, fiducial, BDTS 0.05
## BsNcan.add_relative_error(0.004) #Johannes 230112  bkg subtr
## BsNcan = BsNcan.compress_errors()

# =========================
# BdKpi normalization :
# =========================
BdBR = EVal(1.94e-5,0.06e-5)
#BdE_rec = EVal(0.079,0.001) # Analysis note 2010 (Johannes 070711)
BdE_rec = EVal(0.0896058,0.001) # Francesco 29092012
#BdE_tracking = EVal(0.998,0.003) #Johannes 090911
BdE_tracking = EVal(1.000347,0.00425) # Francesco 26092012 
BdE_rec=BdE_rec*BdE_tracking

#BdE_BDTS_005=EVal(0.9224,0.0005)#Flavio 240112, in muonAcc 
#BdE_fiducial=EVal(0.979,0.)#Johannes 230112

BdE_massCorr = EVal(1., 0)# Francesco 27092012 (to simplify later calculations) 
#BdE_sel = EVal(0.581,0.001)*BdE_BDTS_005*BdE_fiducial # Johannes 130711, fiducial cuts
# Eff ghost prob = 0.995276 +- 0.00011   for one track 
BdE_ghostProb = EVal(0.99057, 0.00015) #Siim 29092012
BdE_sel = EVal(0.490179, 0.001)*BdE_ghostProb #Francesco 01102012
# number for 0.37 fb-1
# Bd_MuId = EVal(0.971,0.) # Barbara 041011
# number for 1.0 fb-1
#Bd_MuId = EVal(0.970,0.) # Barbara 091211
#Bd_MuId = EVal(0.997,0.) # Barbara 240112
Bd_MuId = EVal(1.006,0.) # Barbara 250912

BdE_sel=BdE_sel*Bd_MuId
BdE_HLT2MC = EVal(0.905, 0.004) #Justine 01102012
#BdE_trg = BhhE_HLT2MC*TISE_trg
BdE_trg = BdE_HLT2MC*TISE_trg
BdE_recsel = BdE_sel*BdE_rec
BdRatE_recsel = BdE_recsel/BmmE_recsel
BdRatE_massCor = BdE_massCorr / BmmE_massCorr
BdRatE_recsel.add_relative_error(0.0135*2.)#Johannes had IA from tracking map 200112 
#BdRatE_recsel.add_relative_error(0.019) # muID acceptance and efficiency Barbara 041011
#BdRatE_recsel.add_relative_error(0.005) # muID acceptance and efficiency Barbara 091211
#BdRatE_recsel.add_relative_error(0.005) # muID acceptance and efficiency Barbara 240112
BdRatE_recsel.add_relative_error(0.014) # muID acceptance and efficiency Barbara 250912
BdRatE_recsel.add_relative_error(1.0016-1.0007)#Flavio, 240112, BDTS max diff between ratio sm0-sm1-sm15, in muonACC

BdRatE_recsel = BdRatE_recsel.compress_errors()
BdRatE_recsel_mw = BdRatE_recsel/BmmE_mw #Not used, is just for the note

BdRatE_trg = BdE_trg/BmmE_trg
BdRatE_trg.add_relative_error(0.035) #Justine 200112, TISTOS error
BdRatE_trg.add_relative_error(0.01) #Justine 200112, extra lines Bsmm
BdRatE_trg=BdRatE_trg.compress_errors()

# ====================
# NBhh normalization
# ====================
# number for 0.37 fb-1
# BhhNcanTisClean = EVal(4386.,198.) # Flatteo220911
# BhhNcanTisClean.add_error(563.) # Systematic between methods 220911 Flatteo
# number for 1.0 fb-1
#BhhNcanTisClean = EVal(17490,860) # Flavio 130112
#BhhNcanTisClean = EVal(16734,757) #Matteo 200112 inside muon acceptance
#BhhNcanTisClean.add_error(1072.)#Matteo 200112 syst are 5% from the fit (we tried different beta parameterizations) and 4% from the difference btw all-Sum_bins
#BhhNcanTisClean = BhhNcanTisClean.compress_errors()

# directly from Christian
BhhNcanTis = EVal( 27036., 1376. )

#BdKpiNcan = Bhh_fkp*BdNcan
BdKpiNcan = EVal(14579 , 1110)  #Christian 

Bu = (BuBR*BuRatE_recsel*BuRatE_trg)/BuNcan 
Bu_fit = Bu / BmmE_49006000  #alpha for fit
Bu_mw  = Bu / BmmE_mw       #Alpha for toys 
#Bs = (BsBR*BsRatE_recsel*BsRatE_trg)/BsNcan
#Bs_mw = Bs/ BmmE_mw      #Alpha for toys 
Bd = (BdBR*BdRatE_recsel*BdRatE_trg)/BdKpiNcan
Bd_fit = Bd / BmmE_49006000  #alpha for fit
Bd_mw  = Bd / BmmE_mw       #Alpha for toys 

# alpha parambers for Bs

Buas = fdfs*Bu
## Bsas =      Bs
Bdas = fdfs*Bd

Buas_mw = fdfs*Bu_mw
## Bsas_mw =      Bs_mw
Bdas_mw = fdfs*Bd_mw

# alpha parambers for Bd
Buad =      Bu
## Bsad = fsfd*Bs
Bdad =      Bd

Buad_mw =      Bu_mw
## Bsad_mw = fsfd*Bs_mw
Bdad_mw =      Bd_mw

# b parameters - for the toys
Bub = Bu_mw 
## Bsb = Bs_mw
Bdb = Bd_mw 

# mis-id B->hh misidentified as B->mumu

#number expected for Bd search win, for 150/pb
#MisIDBdNorm = EVal(1.21, 0) # Xabier 240611
#MisIDBsNorm = EVal(0.14, 0) # Xabier 240611 

def muontrg_efficiencies():
# to be updated with new numbers:
    """ Return the error on the total trig efficiencies
    """
    ejpsi_trg = JpsiE_trg
    ejpsi_trg.add_relative_error(0.03) # TISTOS Justine 140711
    ebsmm_trg.add_relative_error(0.02) # Extra lines Justine 140711
    ebsmm_trg = BmmE_trg
    ebsmm_trg.add_relative_error(0.03) # TISTOS Justine 140711
    ebsmm_trg.add_relative_error(0.025) # Extra lines Justine 120711
    return ejpsi_trg,ebsmm_trg
    

# get the peaking background, consider the conservative option Jose 140711
#BkgPeak1, BkgPeak2 = bkgpeak()
#BkgPeakNcan = BkgPeak2 

# fraction of the peaking bkg in the Bd, Bs 60 MeV mass windows
fpeakBd = EVal(0.53,0.035) # Diego 140711 
fpeakBs = EVal(0.11,0.035) # Diego 140711

# Measured Bs BR
BRMeasuredBs = EValAsym(4.3e-9,4.9e-9,3.4e-9)

# cross-check:  ratio of banching fractions Bd/Bu

#Bu = (BuBR*BuRatE_recsel*BuRatE_trg)/BuNcan   #alpha for fit
BdBuRatE_recsel = BuE_recsel/BdE_recsel
BuRatE_recsel_mw = BuRatE_recsel/BmmE_mw #Not used, is just for the note

BdBuRatE_trg = BuE_trg / BdE_trg
BdBuBRRatio = (BdKpiNcan/BuNcan)*(BdBuRatE_recsel * BdBuRatE_trg)
BdBuBRRatio_theo = BdBR / BuBR
def checkBRRatio():
    print " Checking ratio of BR of Bd->Kpi/Bu->Jpsi(mm)K"
    print " Ratio of recsel eff ", BdBuRatE_recsel
    print " Ratio of trig eff ", BdBuRatE_trg
    print " Ratio of BR ", BdBuBRRatio
    print " Ratio of BR pdg ", BdBuBRRatio_theo 



def verbose():
    print '-- Normalization Bu -- '
    check('Bu')
    print '-- Normalization Bs -- '
    check('Bs')
    print '-- Normalization Bd -- '
    check('Bd')
    print ' Mesured Bs BR to use in the cross-feed ', BRMeasuredBs

def averagealpha2012():
    # use only Bu and Bd
    print "Normalisation for the fit "
    print " from Bu ", Bu
    print " from Bd ", Bd
    alpha = Bu.average(Bd)
    print " Average alpha   = ", alpha
    alphas = fdfs*alpha
    print " Average alpha_s = ", alphas
    print "Normalisation for the toys "
    print " from Bu ", Bu_mw
    print " from Bd ", Bd_mw
    alpha_mw = Bu_mw.average(Bd_mw)
    alphas_mw = fdfs* alpha_mw
    print " Average alpha (mw)  = ", alpha_mw
    print " Average alphas (mw)  = ", alphas_mw
    return alpha, alphas, alpha_mw, alphas_mw
