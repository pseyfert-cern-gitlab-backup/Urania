#--------------------------------------
#
# Parameters of the BsMuMu analysis
#
#--------------------------------------

from math import *
from errors import *

#===============================================
# 2013 - analysis of the 2012 dataset
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
    print ' Eff rec&sel raw ',sval('E_recsel_raw')
    print ' Eff recsel corr ',sval('E_recsel')
    print ' Eff trg ',sval('E_trg')
    print ' Eff (Bmm) recsel raw ',BmmE_recsel_raw
    print ' Eff (Bmm) recsel corr ',BmmE_recsel
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
#...
# Which one to use depends on the normalisation convention
#...
#CP Averaged * correction (correction to be removed in case of LHCb-INT-2013-012)
#http://arxiv.org/abs/1208.0934
#http://arxiv.org/abs/1204.1737
#Bsmumu_BR = EVal( 3.23e-9, 0.27e-9 )*EVal(1.096, 0.016)

#Already corrected from new paper
#http://arxiv.org/abs/1303.3820
#Bsmumu_BR = EVal( 3.56e-9, 0.18e-9 )
Bdmumu_BR = EVal( 1.07e-10, 0.1e-10)

# including new tau_Bs value

Bsmumu_BR = EVal( 3.56e-9, 0.29e-9 )      

# ratio of production fractions:
#https://groups.cern.ch/group/lhcb-review-RD-Bsmumu/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Flhcb-review-RD-Bsmumu%2FLists%2FArchive%2FCONF-2013-011%20approved%20for%20circulation&FolderCTID=0x01200200F2F403BF20C82042A5BB3755C8965726
fsfd = EVal(0.259,0.015)
fdfs = fsfd.invert()
fsfs = EVal(1.,0.)
fdfd = EVal(1.,0.)

# factor to covert TIS Bhhin TIS Bkpi (still valid) (?)
# efficiency of the TIS-Bhh cleaning cuts is =1 (no cleaning cuts):
Bhh_fkp = EVal(0.605,0.027)  # factor to convert TIS Bhh in TIS Bkpi
#BhhE_Clean = EVal(0.64,0.02) # Efficiency of the TIS-Bhh cleaning cuts
BhhE_Clean = EVal(1.00,0.00) # Efficiency of the TIS-Bhh cleaning cuts


# trigger efficiency estimated for the JPsi
#https://indico.cern.ch/getFile.py/access?contribId=6&resId=0&materialId=slides&confId=250103
JpsiE_trg = EVal(0.866,[0.003,0.023]) # Justine 20130516
JpsiE_trg = JpsiE_trg.compress_errors()
BuE_trg = JpsiE_trg

# Trigger efficiency for Bsmumu
#https://indico.cern.ch/getFile.py/access?contribId=6&resId=0&materialId=slides&confId=250103
BmmE_trg = EVal(0.924,[0.003,0.019]) # Justine 20130516
BmmE_trg = BmmE_trg.compress_errors()

# Trigger efficiency ratio for BuKpi/Bsmumu
#https://indico.cern.ch/getFile.py/access?contribId=6&resId=0&materialId=slides&confId=250103
BuRatE_trg = EVal(0.937,[0.005,0.025]) # Justine 20130516
BuRatE_trg = BuRatE_trg.compress_errors()

# TIS trigger efficiency
#TISE_trg = EVal(0.0577,0.0004) # Siim
TISE_trg = EVal(0.0592, 0.0003) # Siim 20130611
TISE_trg.add_error(0.004) # Johannes 190711 (We keep the same) # Marco make it abs
TISE_trg= TISE_trg.compress_errors()# Johannes 190711

# MC HLT2 trigger efficiency in Bhh L0xHLT1-TIS (estimated from MC+TCK):
# number used in 0.37 fb-1, to be updated with stripping 17.
BhhE_HLT2MC = EVal(0.836,0.) # Justine 220611
BhhE_HLT2MC.add_relative_error(0.06) # Johannes 120711
BhhE_HLT2MC = BhhE_HLT2MC.compress_errors()

# PID efficiency of the cut of the K of the Phi for the BsJPsiPhi selection
# NOT Used anymore
#KPIDE = EVal(0.914,0.009) # Johannes 130112
#KPIDE.add_relative_error(0.01) # Johannes 240112 additional syst
#KPIDE=KPIDE.compress_errors()

# reco and sele for Bmumu:
BmmE_recsel_raw = EVal( 0.0557719 , 0.000306695 ) #Francesco 23052013

BmmE_tracking = EVal(0.98520, 0.00376) # Francesco 23052013

# No additional error on mw efficiency as it's contained in sel eff
BmmE_massCorr = EVal(0.99260 ,0.000580)# Francesco 21062013 
BmmE_mw =EVal(0.919366,0.000001)*BmmE_massCorr  # Francesco 12062013
BmmE_49006000 = 0.992122  #efficiency of mass window [4900,6000] #Francesco 12062013

BmmE_ghostProb = EVal(0.9959, 0.0001) #Siim 30052013
BmmE_ghostProb.add_relative_error(0.0009) # Barbara 30052013
BmmE_ghostProb = BmmE_ghostProb.compress_errors()

BmmE_recsel = BmmE_recsel_raw * BmmE_tracking *BmmE_ghostProb  


# Mathieu 20130626
# https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FBDT%20correction%20time%20acceptance&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5

TimeAcceptanceCorrBs = EVal( 1.04566319935, 0.000213126985336 )
TimeAcceptanceCorrBd = EVal( 1.01504863807, 6.49317574833e-05 )

# =========================
# BuJpsiK normalization :
# =========================
# reco and sele for BuJpsiK:
BuBR = EVal(1.016e-3,0.033e-3)*EVal(0.0593,0.0006)  # Updated to PDG 2012  04/04/2013
### WAS BuBR = EVal(6.01e-5,0.21e-5) # Br(B+->JPsiK+) Latest PDG 140711

BuE_recsel_raw = EVal( 0.026057 , 0.000158657 ) #Francesco 23052013

BuE_tracking = EVal( 0.97675 , 0.00596 ) #Francesco 23052013

BuE_massCorr = EVal(0.999999, 0.000001) #Francesco 21092012 (could be removed...)

#Bu_MuId = EVal(1.054,0.)  # Barbara 250912
#Bu_MuId = EVal(1.024,0.) # Barbara 140513
Bu_MuId = EVal(1.017,0.) # Barbara 090613

BuE_recsel = BuE_recsel_raw * Bu_MuId * BuE_tracking

BuRatE_recsel = BuE_recsel/BmmE_recsel
# I separate the mass correction as it is not needed for the alpha for the fit
BuRatE_massCorr = BuE_massCorr/BmmE_massCorr

BuRatE_recsel.add_relative_error(0.013) # Francesco sys extra track material  23052013
BuRatE_recsel.add_relative_error(0.004) # Francesco sys extra track correlated 23052013
BuRatE_recsel.add_relative_error(0.015) # Francesco sys fit model 23052013

#BuRatE_recsel.add_relative_error(0.021) # muID acceptance and efficiency Barbara 250912
#BuRatE_recsel.add_relative_error(0.015) # muID acceptance and efficiency, PID, Barbara 140513
BuRatE_recsel.add_relative_error(0.014) # muID acceptance and efficiency, PID, Barbara 090613

BuRatE_recsel = BuRatE_recsel.compress_errors()

# BuRatE_trg  is computed by Justine and provided as input above

#BuNcan = EVal(424222.5,699.9)# Siim 18092012
#BuNcan = EVal(761772.3,891.4)# Siim 04042013 2012 S20 20 (2028.24pb)
BuNcan = EVal(761122.2,891.1)# Siim 09052013 2012 S20 20 (2028.24pb) new model!

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
BdE_recsel_raw = EVal(0.0466382, 0.000186042) # Francesco 12062013
BdE_tracking = EVal(0.98478, 0.00438) # Francesco 23052013

BdE_massCorr = EVal(1., 0)# Francesco (to simplify later calculations)
# Eff ghost prob = 0.995276 +- 0.00011   for one track
BdE_ghostProb = EVal(0.99057, 0.00015) #Siim 29092012 TOBEUP

#Bd_MuId = EVal(1.006,0.) # Barbara 250912
#Bd_MuId = EVal(1.017,0.) # Barbara 140513
Bd_MuId = EVal(1.010,0.) # Barbara 090613

#https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2F2012%20Hlt2%20efficiency%20with%20respect%20to%20TIS&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
BdE_HLT2MC = EVal(0.916, 0.002) #Justine 20130611

BdE_trg = BdE_HLT2MC*TISE_trg

BdE_recsel = BdE_recsel_raw * BdE_tracking * BdE_ghostProb *Bd_MuId

BdRatE_recsel = BdE_recsel/BmmE_recsel
BdRatE_massCor = BdE_massCorr / BmmE_massCorr
BdRatE_recsel.add_relative_error(0.0135*2.)# Francesco sys track material  23052013

#BdRatE_recsel.add_relative_error(0.014) # muID acceptance and efficiency Barbara 250912
#BdRatE_recsel.add_relative_error(0.014) # muID acceptance and efficiency, PID,  Barbara 140513
BdRatE_recsel.add_relative_error(0.013) # muID acceptance and efficiency, PID, Barbara 090613

BdRatE_recsel = BdRatE_recsel.compress_errors()
BdRatE_recsel_mw = BdRatE_recsel/BmmE_mw #Not used, is just for the note


BdRatE_trg = BdE_trg/BmmE_trg

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
#BdKpiNcan = EVal(14579 , 1110)  #Christian, 2012 nov ana.
#BdKpiNcan = EVal(28321, 1234)  #Christian 26042013
BdKpiNcan = EVal(26749, 447)  #Christian 04072013
BdNcan = BdKpiNcan

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
    #ejpsi_trg.add_relative_error(0.03) # TISTOS Justine 140711
    ejpsi_trg.add_relative_error(0.015) # TISTOS Justine 260413
    #ebsmm_trg.add_relative_error(0.02) # Extra lines Justine 140711  ??? why is this here, should be jpsi (Siim)
    #Extra lines are already accounted for in the JpsiE_trg, Siim

    ebsmm_trg = BmmE_trg
    #ebsmm_trg.add_relative_error(0.03) # TISTOS Justine 140711
    ebsmm_trg.add_relative_error(0.008) # TISTOS Justine 260413
    #ebsmm_trg.add_relative_error(0.025) # Extra lines Justine 120711
    #Extra lines are already accounted for in the JpsiE_trg, Siim

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

## #Bu = (BuBR*BuRatE_recsel*BuRatE_trg)/BuNcan   #alpha for fit
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
    alphas = fdfs*alpha
    print " Average alpha   = ", alpha
    alpha =     alpha / TimeAcceptanceCorrBd
    print " Corrected for Bd time acc = " , alpha
    print " Average alpha_s = ", alphas
    alphas = alphas / TimeAcceptanceCorrBs
    print " Corrected for Bs time acc = " , alphas
    print "Normalisation for the toys "
    print " from Bu ", Bu_mw
    print " from Bd ", Bd_mw
    alpha_mw = Bu_mw.average(Bd_mw)
    alphas_mw = fdfs* alpha_mw
    print " Average alpha (mw)  = ", alpha_mw
    print " Average alphas (mw)  = ", alphas_mw
    print " Corrected for time acceptance "
    alpha_mw = alpha_mw / TimeAcceptanceCorrBd
    alphas_mw = alphas_mw / TimeAcceptanceCorrBs
    print " Average alpha (mw)  = ", alpha_mw
    print " Average alphas (mw)  = ", alphas_mw
    return alpha, alphas, alpha_mw, alphas_mw
