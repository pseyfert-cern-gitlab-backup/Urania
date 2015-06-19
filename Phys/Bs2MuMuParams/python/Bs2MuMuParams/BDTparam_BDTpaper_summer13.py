#--------------------------------------
#
# Parameters of the BDT BsMuMu analysis
#
#--------------------------------------

#DONE
# mass reso
# mass mean
# CBTrans
# CBExpo
# signal BDT
# justine factor
# misID numbers

from math import *
from errors import *
import code

import alphaparam_summer13_2011 as alpha11
import alphaparam_spring13_2012 as alpha12
from alphaparam_summer13 import *
import BDTparam_BDTpaper_spring13_2011 as bdt2011
import BDTparam_BDTpaper_spring13_2012 as bdt2012

#===============================================
#
# 2011+2012 datasets as one dataset - summer 2013 analysis
# with BDT12
# 
#===============================================

lumi_S20r1 = 1018. #970.7
lumi_S20   = 2028.2

#------------------------------------------------
# Parameters for the toys
#------------------------------------------------

BDT_binning_8 = [0., 0.25, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.]
BDT_binning = BDT_binning_8

def average_bybinsize( list, binning = BDT_binning ):
    """
    """
    if len(list) != len(binning)-1:
        raise ValueError
    bin_size = []
    for i in range(len(binning)-1):
        bin_size.append( float(binning[i+1]-binning[i]) )
    list = map(lambda x,y : x*y, list, bin_size )
    list = map(lambda x : x.get_value(), list)
    #print bin_size
    #print list
    #print float(binning[-1]-binning[0])
    return sum( list ) / float(binning[-1]-binning[0])


#------------------------------------------------------
# DLL cut correction
# Barbara
#------------------------------------------------------

# https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FBDT%20corrections%20for%20PID%20cut&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
DLLCor1 = ((bdt2011.DLLCor1*lumi_S20r1)+(bdt2012.DLLCor1*lumi_S20)) / ( lumi_S20r1 + lumi_S20 )
DLLCor2 = ((bdt2011.DLLCor2*lumi_S20r1)+(bdt2012.DLLCor2*lumi_S20)) / ( lumi_S20r1 + lumi_S20 )
DLLCor3 = ((bdt2011.DLLCor3*lumi_S20r1)+(bdt2012.DLLCor3*lumi_S20)) / ( lumi_S20r1 + lumi_S20 )
DLLCor4 = ((bdt2011.DLLCor4*lumi_S20r1)+(bdt2012.DLLCor4*lumi_S20)) / ( lumi_S20r1 + lumi_S20 )
DLLCor5 = ((bdt2011.DLLCor5*lumi_S20r1)+(bdt2012.DLLCor5*lumi_S20)) / ( lumi_S20r1 + lumi_S20 )
DLLCor6 = ((bdt2011.DLLCor6*lumi_S20r1)+(bdt2012.DLLCor6*lumi_S20)) / ( lumi_S20r1 + lumi_S20 )
DLLCor7 = ((bdt2011.DLLCor7*lumi_S20r1)+(bdt2012.DLLCor7*lumi_S20)) / ( lumi_S20r1 + lumi_S20 )
DLLCor8 = ((bdt2011.DLLCor8*lumi_S20r1)+(bdt2012.DLLCor8*lumi_S20)) / ( lumi_S20r1 + lumi_S20 )



DLLCor = [DLLCor1, DLLCor2, DLLCor3, DLLCor4, DLLCor5, DLLCor6, DLLCor7, DLLCor8]
DLLCor = map(lambda x : EVal(x,0.),DLLCor)
DLLCor_ave = average_bybinsize( DLLCor )

#------------------------------------------------------
#
# PDF signal calibration
#
#------------------------------------------------------

# Diegos numbers
# not used anymore

# Justine Calibration
# not used anymore

# LNF calibration
# not used anymore


#------------------------------------------------------
# Zueri calibration
#------------------------------------------------------


ZFrac1 = ((bdt2011.ZFrac1*lumi_S20r1)+(bdt2012.ZFrac1*lumi_S20))/(lumi_S20r1+lumi_S20)
ZFrac2 = ((bdt2011.ZFrac2*lumi_S20r1)+(bdt2012.ZFrac2*lumi_S20))/(lumi_S20r1+lumi_S20)
ZFrac3 = ((bdt2011.ZFrac3*lumi_S20r1)+(bdt2012.ZFrac3*lumi_S20))/(lumi_S20r1+lumi_S20)
ZFrac4 = ((bdt2011.ZFrac4*lumi_S20r1)+(bdt2012.ZFrac4*lumi_S20))/(lumi_S20r1+lumi_S20)
ZFrac5 = ((bdt2011.ZFrac5*lumi_S20r1)+(bdt2012.ZFrac5*lumi_S20))/(lumi_S20r1+lumi_S20)
ZFrac6 = ((bdt2011.ZFrac6*lumi_S20r1)+(bdt2012.ZFrac6*lumi_S20))/(lumi_S20r1+lumi_S20)
ZFrac7 = ((bdt2011.ZFrac7*lumi_S20r1)+(bdt2012.ZFrac7*lumi_S20))/(lumi_S20r1+lumi_S20)
ZFrac8 = ((bdt2011.ZFrac8*lumi_S20r1)+(bdt2012.ZFrac8*lumi_S20))/(lumi_S20r1+lumi_S20)


[ZFrac1, ZFrac2, ZFrac3, ZFrac4, ZFrac5, ZFrac6, ZFrac7, ZFrac8] = map(lambda x: x.compress_errors(), [ZFrac1, ZFrac2, ZFrac3, ZFrac4, ZFrac5, ZFrac6, ZFrac7, ZFrac8])


#------------------------------------------------------
# time-dependant acceptance correction 'Mathieu'
#------------------------------------------------------


TimeAccbin1 = EVal( 0.967734301051, 0.000264372373692) # Mathieu 20130610
TimeAccbin2 = EVal( 0.98105170664 , 0.000348119031836) # Mathieu 20130610
TimeAccbin3 = EVal( 0.988194423339, 0.000431279272493) # Mathieu 20130610
TimeAccbin4 = EVal( 0.994875378244, 0.000491803785874) # Mathieu 20130610
TimeAccbin5 = EVal( 1.0007148427  , 0.000526551225211) # Mathieu 20130610
TimeAccbin6 = EVal( 1.00967244812 , 0.000567601916876) # Mathieu 20130610
TimeAccbin7 = EVal( 1.02838141777 , 0.000658379806371) # Mathieu 20130610
TimeAccbin8 = EVal( 1.08063251538 , 0.000897922729864) # Mathieu 20130610


TimeAcc = [TimeAccbin1, TimeAccbin2, TimeAccbin3, TimeAccbin4, TimeAccbin5, TimeAccbin6, TimeAccbin7, TimeAccbin8]

# average by bin size
TimeAcc_ave  = average_bybinsize( TimeAcc )
#print 'TimeAcc_ave', TimeAcc_ave
TimeAcc_corr = map(lambda x: x/TimeAcc_ave, TimeAcc )

TimeAcc1 = TimeAcc_corr[0] 
TimeAcc2 = TimeAcc_corr[1]                             
TimeAcc3 = TimeAcc_corr[2]                             
TimeAcc4 = TimeAcc_corr[3]                             
TimeAcc5 = TimeAcc_corr[4]                             
TimeAcc6 = TimeAcc_corr[5]                             
TimeAcc7 = TimeAcc_corr[6]                             
TimeAcc8 = TimeAcc_corr[7]    


#------------------------------------------------------
# trigger bias correction on the GL or 'Justine' correction
#------------------------------------------------------


Justine1 = ((bdt2011.Justine1*lumi_S20r1)+(bdt2012.Justine1*lumi_S20))/(lumi_S20r1+lumi_S20)
Justine2 = ((bdt2011.Justine2*lumi_S20r1)+(bdt2012.Justine2*lumi_S20))/(lumi_S20r1+lumi_S20)
Justine3 = ((bdt2011.Justine3*lumi_S20r1)+(bdt2012.Justine3*lumi_S20))/(lumi_S20r1+lumi_S20)
Justine4 = ((bdt2011.Justine4*lumi_S20r1)+(bdt2012.Justine4*lumi_S20))/(lumi_S20r1+lumi_S20)
Justine5 = ((bdt2011.Justine5*lumi_S20r1)+(bdt2012.Justine5*lumi_S20))/(lumi_S20r1+lumi_S20)
Justine6 = ((bdt2011.Justine6*lumi_S20r1)+(bdt2012.Justine6*lumi_S20))/(lumi_S20r1+lumi_S20)
Justine7 = ((bdt2011.Justine7*lumi_S20r1)+(bdt2012.Justine7*lumi_S20))/(lumi_S20r1+lumi_S20)
Justine8 = ((bdt2011.Justine8*lumi_S20r1)+(bdt2012.Justine8*lumi_S20))/(lumi_S20r1+lumi_S20)

Justine = [Justine1, Justine2, Justine3, Justine4, Justine5, Justine6, Justine7, Justine8]


# Jose- Compute the Justine average by bin size, and the correction factor
Justine_ave  = average_bybinsize( Justine )
Justine_corr = map(lambda x: x/Justine_ave, Justine )

# Jose- Compute the Justine average by bin size, and the correction factor with DLL cuts
Justine_DLL      = map(lambda x,y: x/y, Justine, DLLCor)
Justine_DLL_ave  = average_bybinsize( Justine_DLL )

Justine_DLL_corr = map(lambda x: x/Justine_DLL_ave, Justine_DLL )

J = Justine_DLL_corr


J_ave1 = J[0] # EVal(-9999.,-9999.)  # requirementn of the toys  ##DIEGO::CHECK   And that's what will be passed to the toys under the JUSTINE labels
J_ave2 = J[1] #                             
J_ave3 = J[2] #                             
J_ave4 = J[3] #                             
J_ave5 = J[4] #                             
J_ave6 = J[5] #                             
J_ave7 = J[6] #                             
J_ave8 = J[7] #                             

#code.interact(local=locals())

#------------------------------------------------------
# Mass measurements
#------------------------------------------------------


#https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FMass%20average&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
MassMeanBs = EVal(5371.85,[0.17, 0.19]) # Christian 20130624
MassMeanBd = EVal(5284.90,[0.10, 0.20]) # Christian 20130624

#https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FMass%20average&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
MassResoBs = EVal(23.24,[0.08,0.44])     # Christian 20130624
MassResoBd = EVal(22.83,[0.07,0.42])     # Christian 20130624

#https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FMass%20average&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
CBTrans    = EVal(2.065,[0.005,0.010])   # Christian 20130624 
CBExpo     = EVal(1.118,[0.013,0.038])   # Christian 20130624


#------------------------------------------------------
# PDF for the bgk: k-coeficient of the exp fit
#------------------------------------------------------

# https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2Freference%20blind%20fit%20input%20for%20toys%20reference%20values&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5            
# exponents
BkgMassk1 = EValAsym( -6.9394e-04, +1.38e-05,-1.38e-05)  # Ale 20130705
BkgMassk2 = EValAsym( -4.8992e-04, +1.00e-04,-9.98e-05)  # Ale 20130705
BkgMassk3 = EValAsym( -4.7006e-04, +2.15e-04,-2.13e-04)  # Ale 20130705
BkgMassk4 = EValAsym( -8.6918e-04, +3.48e-04,-3.43e-04)  # Ale 20130705
BkgMassk5 = EValAsym( -3.3349e-04, +7.10e-04,-6.20e-04)  # Ale 20130705
BkgMassk6 = EValAsym( +6.0893e-05, +1.12e-03,-9.28e-04)  # Ale 20130705
BkgMassk7 = EValAsym( -4.1794e-04, +1.61e-03,-1.37e-03)  # Ale 20130705
BkgMassk8 = EValAsym( -4.1794e-04, +1.61e-03,-1.37e-03)  # Ale 20130705

# total number of events in the (used to fit) bkg sidebands
SbGL1 = 43244
SbGL2 = 1104 
SbGL3 = 226  
SbGL4 = 113  
SbGL5 = 58   
SbGL6 = 28   
SbGL7 = 13   
SbGL8 = 8    

FracCombBin1 = EValAsym(1.2484  ,0.00052911 ,-0.0002264 )  #  Ale 20130705
FracCombBin2 = EValAsym(1.2074  ,0.012774   ,-0.0092682 )  #  Ale 20130705
FracCombBin3 = EValAsym(1.1542  ,0.038088   ,-0.028229  )  #  Ale 20130705
FracCombBin4 = EValAsym(1.0731  ,0.074398   ,-0.058035  )  #  Ale 20130705
FracCombBin5 = EValAsym(0.86539 ,0.14557    ,-0.12325   )  #  Ale 20130705
FracCombBin6 = EValAsym(0.72936 ,0.20483    ,-0.15522   )  #  Ale 20130705
FracCombBin7 = EValAsym(0.64307 ,0.32284    ,-0.1993    )  #  Ale 20130705
FracCombBin8 = EValAsym(0.31486 ,0.46038    ,-0.2083    )  #  Ale 20130705

# additional systematics
SystBkgBin1 = 0.  # Marco 150212
SystBkgBin2 = 0.  # Marco 250112
SystBkgBin3 = 0.  # Marco 250112
SystBkgBin4 = 0.  # Marco 250112
SystBkgBin5 = 0.  # Marco 250112
SystBkgBin6 = 0.  # Marco 250112
SystBkgBin7 = 0.  # Marco 250112
SystBkgBin8 = 0.  # Marco 250112


#------------------------------------------------------
# MisID Bkg
#------------------------------------------------------

def compute_nbhh_misid(dmisid,factors,justines):
    #factors = map(lambda x: EVal(x,0.),factors)
    bin_TIS = [TisTot,Tis2,Tis3,Tis4,Tis5,Tis6,Tis7,Tis8]
    bin_Justine = justines[:]
    bin_Justine[0] = EVal(1.,0.)
    bin_bhhmm = map(lambda ntis,jus: ntis/(BdRatE_trg*jus),bin_TIS,bin_Justine)
    Ntot = bin_bhhmm[0]
    Nsum = reduce(lambda x,y:x+y,bin_bhhmm[1:])
    bin_bhhmm[0] = Ntot-Nsum
    bin_bhhmm_id = map(lambda f,n:f*n*dmisid,bin_bhhmm,factors)
    Nbhh_id = reduce(lambda x,y:x+y,bin_bhhmm_id)
    Nbhh_id2 = Ntot*dmisid
    def format(eval):
        return '%4.3f'%val(eval)+'+- %4.3f'%err(eval)
    print ' NBhh misid total ',format(Nbhh_id),' in ave ',format(Nbhh_id2)
    print ' NBhh misid bins ',str(map(lambda x:format(x),bin_bhhmm_id))
    return Nbhh_id,bin_bhhmm_id


    
#------------------------------------------------------
# values if NO DLL cut
#------------------------------------------------------
# NOT USED ANYMORE

#------------------------------------------------------
# values WITH DLL cut
#------------------------------------------------------

BhhYield_S20r1 = EVal(20143., 572.)  #EVal(19264., 550.)  # CHE mail subject B->hh yields 
BhhYield_S20   = EVal(49653., 507.)  # CHE mail subject B->hh yields 

#
BhhMisID_DLL_S20r1 = EVal(1.1e-5,[0.037e-5])  # Fatima 20130626
BhhMisID_DLL_S20r1.add_error(0.1e-5)          # diff with no DeltaM cut
BhhMisID_DLL_S20r1.add_relative_error(1/17.)  # trigger on probe
BhhMisID_DLL_S20r1= BhhMisID_DLL_S20r1.compress_errors()
BhhMisID_DLL_S20  = EVal(1.2e-5,0.036e-5)      # Fatima 20130626
BhhMisID_DLL_S20   .add_error(0.1e-5)          # diff with no DeltaM cut
BhhMisID_DLL_S20  = BhhMisID_DLL_S20.compress_errors()

MisIDGlobalFactor_S20r1 = BhhMisID_DLL_S20r1 / alpha11.BdRatE_trg
MisIDGlobalFactor_S20   = BhhMisID_DLL_S20   / alpha12.BdRatE_trg

# to be passed to table
MisIDTotalYield = MisIDGlobalFactor_S20r1*BhhYield_S20r1 + MisIDGlobalFactor_S20 * BhhYield_S20
print MisIDTotalYield 

probs_S20r1 = bdt2011.probs
probs_S20 = bdt2012.probs

BhhMisID_DLL_factors_S20r1 = map(lambda x: x/BhhMisID_DLL_S20r1, probs_S20r1)
BhhMisID_DLL_factors_S20   = map(lambda x: x/BhhMisID_DLL_S20  , probs_S20)

BhhMisID_DLL_factors = map(lambda p11, p12: ((p11 * lumi_S20r1) + (p12 * lumi_S20)) / ( lumi_S20r1 + lumi_S20 ), BhhMisID_DLL_factors_S20r1, BhhMisID_DLL_factors_S20)

print BhhMisID_DLL_factors

#BhhMisID_DLL_factors = map(lambda x: x/BhhMisID_DLL, probs)

BhhMisID_DLL_factors_ave = average_bybinsize( BhhMisID_DLL_factors )
BhhMisID_DLL_factors_corr = map( lambda x  : x/BhhMisID_DLL_factors_ave, BhhMisID_DLL_factors ) 
BhhMisID_DLL_factors_corr = map( lambda x,y: x/y, Justine_corr, BhhMisID_DLL_factors_corr )
BhhMisID_DLL_factors_corr_ave = average_bybinsize( BhhMisID_DLL_factors_corr )
BhhMisID_DLL_factors_corr = map( lambda x  : x/BhhMisID_DLL_factors_corr_ave, BhhMisID_DLL_factors_corr ) 

def compute_nbhh_misid(BhhYield, BmmE_trg, TISE_trg, BdE_HLT2MC, BhhMisID_DLL, MisIDGlobalFactor, BhhMisID_DLL_factors_corr, BDT_frac):
    print 'inputs:'
    print 'BhhYield', BhhYield
    print 'BmmE_trg', BmmE_trg
    print 'TISE_trg', TISE_trg
    print 'BdE_HLT2MC', BdE_HLT2MC
    print 'BhhMisID_DLL', BhhMisID_DLL
    print 'MisIDGlobalFactor', MisIDGlobalFactor, '=', BmmE_trg * BhhMisID_DLL/ (TISE_trg*BdE_HLT2MC), '(BmmE_trg * BhhMisID_DLL/ (TISE_trg*BdE_HLT2MC)'
    print ' NBhh misid total ', BhhYield * MisIDGlobalFactor
    print ' should be equal to ', BhhYield *BmmE_trg * BhhMisID_DLL/ (TISE_trg*BdE_HLT2MC)
    BDT_frac_corr = map(lambda bdt, misIDcorr: bdt/misIDcorr, BDT_frac, BhhMisID_DLL_factors_corr)
    for i in range(len(BDT_frac)):
        print 'bin', i+1, ': ', BhhYield *BmmE_trg * BhhMisID_DLL/ (TISE_trg*BdE_HLT2MC) *  BDT_frac_corr[i]
    print 'BDT>0.8 : ', BhhYield *BmmE_trg * BhhMisID_DLL/ (TISE_trg*BdE_HLT2MC) * (BDT_frac_corr[-2] + BDT_frac_corr[-1])

def compute_nbhh_misid_combdataset(MisIDTotalYield, BhhMisID_DLL_factors_corr, BDT_frac):
    print 'inputs:'
    print 'MisIDTotalYield', MisIDTotalYield
    BDT_frac_corr = map(lambda bdt, misIDcorr: bdt/misIDcorr, BDT_frac, BhhMisID_DLL_factors_corr)
    for i in range(len(BDT_frac)):
        print 'bin', i+1, ': ', MisIDTotalYield *  BDT_frac_corr[i]
    print 'BDT>0.8 : ', MisIDTotalYield  * (BDT_frac_corr[-2] + BDT_frac_corr[-1])

compute_nbhh_misid_combdataset(MisIDTotalYield,  BhhMisID_DLL_factors_corr, [ZFrac1, ZFrac2, ZFrac3, ZFrac4, ZFrac5, ZFrac6, ZFrac7, ZFrac8])



## Mis_ave = average_bybinsize( BhhMisID_DLL_factors_corr )
## BhhMisID_DLL_factors_corr = map(lambda x  : x/Mis_ave, BhhMisID_DLL_factors_corr)

## BkgPeakNcan,BkgPeakNcanlist = compute_nbhh_misid(BhhMisID_DLL,BhhMisID_DLL_factors,Justine_DLL_corr)
## print ' BkgPeakNcan ',BkgPeakNcan

## # MisIDfBDTBin = BhhMisID_factors_corr ## DIEGO,MARCO -CHECK

## Mis = map(lambda x,y: x/y, Justine,  )
## Mis_ave = average_bybinsize( Mis )
## BhhMisID_DLL_factors_corr = map(lambda x  : x/Mis_ave, Mis)

MisIDfBDTBin1 = BhhMisID_DLL_factors_corr[0] #EVal(-999.,-999.) 
MisIDfBDTBin2 = BhhMisID_DLL_factors_corr[1] #
MisIDfBDTBin3 = BhhMisID_DLL_factors_corr[2] #
MisIDfBDTBin4 = BhhMisID_DLL_factors_corr[3] #
MisIDfBDTBin5 = BhhMisID_DLL_factors_corr[4] #
MisIDfBDTBin6 = BhhMisID_DLL_factors_corr[5] #
MisIDfBDTBin7 = BhhMisID_DLL_factors_corr[6] #
MisIDfBDTBin8 = BhhMisID_DLL_factors_corr[7] #
    

# fraction of the peaking bkg in the Bd, Bs 60 MeV mass windows
fpeakBd = EValAsym(0.48 ,0.2 ,0.08 ) # Diego 270112
fpeakBs = EValAsym(0.088,0.03,0.021) # Diego 270112

# Measured Bs BR
BRMeasuredBs = EValAsym(0.8e-9,1.8e-9,1.3e-9)


#------------------------------------------------------
# Sidebands definition
#------------------------------------------------------

BlindWidth  = 60                         # Marco 210112
BMassT0     = 4900.                      # Marco 210112
BMassBlind0 = val(MassMeanBd)-BlindWidth # Marco 210112
BMassBlind1 = val(MassMeanBs)+BlindWidth # Marco 210112
BMassT1     = 6000.                      # Marco 210112

GL1MassSb1 = BMassT0          # Marco 210112
GL1MassSb2 = BMassBlind0      # Marco 210112
GL1MassSb3 = BMassBlind1      # Marco 210112
GL1MassSb4 = BMassT1          # Marco 210112
GL2MassSb1 = BMassT0          # Marco 210112
GL2MassSb2 = BMassBlind0      # Marco 210112
GL2MassSb3 = BMassBlind1      # Marco 210112
GL2MassSb4 = BMassT1          # Marco 210112
GL3MassSb1 = BMassT0          # Marco 210112
GL3MassSb2 = BMassBlind0      # Marco 210112
GL3MassSb3 = BMassBlind1      # Marco 210112
GL3MassSb4 = BMassT1          # Marco 210112
GL4MassSb1 = BMassT0          # Marco 210112
GL4MassSb2 = BMassBlind0      # Marco 210112
GL4MassSb3 = BMassBlind1      # Marco 210112
GL4MassSb4 = BMassT1          # Marco 210112
GL5MassSb1 = BMassT0          # Marco 210112
GL5MassSb2 = BMassBlind0      # Marco 210112
GL5MassSb3 = BMassBlind1      # Marco 210112
GL5MassSb4 = BMassT1          # Marco 210112
GL6MassSb1 = BMassT0          # Marco 210112
GL6MassSb2 = BMassBlind0      # Marco 210112
GL6MassSb3 = BMassBlind1      # Marco 210112
GL6MassSb4 = BMassT1          # Marco 210112
GL7MassSb1 = BMassT0          # Marco 210112
GL7MassSb2 = BMassBlind0      # Marco 210112
GL7MassSb3 = BMassBlind1      # Marco 210112
GL7MassSb4 = BMassT1          # Marco 210112
GL8MassSb1 = BMassT0          # Marco 210112
GL8MassSb2 = BMassBlind0      # Marco 210112
GL8MassSb3 = BMassBlind1      # Marco 210112
GL8MassSb4 = BMassT1          # Marco 210112
