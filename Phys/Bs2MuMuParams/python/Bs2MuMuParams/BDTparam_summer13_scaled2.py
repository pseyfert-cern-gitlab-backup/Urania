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

import alphaparam_spring13_2011 as alpha11
import alphaparam_spring13_2012_scaled2 as alpha12

from alphaparam_summer13_scaled2 import *

#===============================================
#
# 2011+2012 datasets as one dataset - summer 2013 analysis
# with BDT12
# Test with scaling to 2 fb-1
# 
#===============================================

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
DLLCor1 = 0.9755 # Barbara 20130626
DLLCor2 = 0.9757 # Barbara 20130626
DLLCor3 = 0.9762 # Barbara 20130626
DLLCor4 = 0.9763 # Barbara 20130626
DLLCor5 = 0.9781 # Barbara 20130626
DLLCor6 = 0.9812 # Barbara 20130626
DLLCor7 = 0.9827 # Barbara 20130626
DLLCor8 = 0.9873 # Barbara 20130626


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

# https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FBDT%20signal%20calibration&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
#



ZFrac1 = EVal( 0.2437,[ 0.0095, 0.0105])   # CHE 20130701
ZFrac2 = EVal( 0.1425,[ 0.0038, 0.0115])   # CHE 20130701
ZFrac3 = EVal( 0.0935,[ 0.0028, 0.0050])   # CHE 20130701
ZFrac4 = EVal( 0.1006,[ 0.0034, 0.0040])   # CHE 20130701
ZFrac5 = EVal( 0.1018,[ 0.0033, 0.0039])   # CHE 20130701
ZFrac6 = EVal( 0.1033,[ 0.0031, 0.0054])   # CHE 20130701
ZFrac7 = EVal( 0.1072,[ 0.0029, 0.0046])   # CHE 20130701
ZFrac8 = EVal( 0.1074,[ 0.0027, 0.0037])   # CHE 20130701


## ZFrac1 = EVal(0.2434,[0.0090,0.0105])  # CHE 20130624
## ZFrac2 = EVal(0.1415,[0.0036,0.0115])  # CHE 20130624
## ZFrac3 = EVal(0.0937,[0.0018,0.0050])  # CHE 20130624
## ZFrac4 = EVal(0.1010,[0.0022,0.0040])  # CHE 20130624
## ZFrac5 = EVal(0.1016,[0.0022,0.0039])  # CHE 20130624
## ZFrac6 = EVal(0.1037,[0.0018,0.0054])  # CHE 20130624
## ZFrac7 = EVal(0.1077,[0.0019,0.0046])  # CHE 20130624
## ZFrac8 = EVal(0.1074,[0.0019,0.0037])  # CHE 20130624

[ZFrac1, ZFrac2, ZFrac3, ZFrac4, ZFrac5, ZFrac6, ZFrac7, ZFrac8] = map(lambda x: x.compress_errors(), [ZFrac1, ZFrac2, ZFrac3, ZFrac4, ZFrac5, ZFrac6, ZFrac7, ZFrac8])


#------------------------------------------------------
# time-dependant acceptance correction 'Mathieu'
#------------------------------------------------------

# https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FBDT%20correction%20time%20acceptance&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
TimeAccbin1 = EVal( 0.968938971592, 0.) # Mathieu 20130626
TimeAccbin2 = EVal( 0.986221782647, 0.) # Mathieu 20130626
TimeAccbin3 = EVal( 0.996113118885, 0.) # Mathieu 20130626
TimeAccbin4 = EVal( 1.00270114781 , 0.) # Mathieu 20130626
TimeAccbin5 = EVal( 1.00719296002 , 0.) # Mathieu 20130626
TimeAccbin6 = EVal( 1.01364951327 , 0.) # Mathieu 20130626
TimeAccbin7 = EVal( 1.02542328411 , 0.) # Mathieu 20130626
TimeAccbin8 = EVal( 1.04736487104 , 0.) # Mathieu 20130626

## TimeAccbin1 = EVal( 0.967734301051, 0.000264372373692) # Mathieu 20130610
## TimeAccbin2 = EVal( 0.98105170664 , 0.000348119031836) # Mathieu 20130610
## TimeAccbin3 = EVal( 0.988194423339, 0.000431279272493) # Mathieu 20130610
## TimeAccbin4 = EVal( 0.994875378244, 0.000491803785874) # Mathieu 20130610
## TimeAccbin5 = EVal( 1.0007148427  , 0.000526551225211) # Mathieu 20130610
## TimeAccbin6 = EVal( 1.00967244812 , 0.000567601916876) # Mathieu 20130610
## TimeAccbin7 = EVal( 1.02838141777 , 0.000658379806371) # Mathieu 20130610
## TimeAccbin8 = EVal( 1.08063251538 , 0.000897922729864) # Mathieu 20130610

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

#https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2Ftrigger%20eff%20and%20justine%20factors&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5

Justine1 = EVal(5.9, 0.1) # Justine 20130625
Justine2 = EVal(5.7, 0.1) # Justine 20130625
Justine3 = EVal(5.8, 0.1) # Justine 20130625
Justine4 = EVal(5.9, 0.1) # Justine 20130625
Justine5 = EVal(6.0, 0.2) # Justine 20130625
Justine6 = EVal(6.4, 0.2) # Justine 20130625
Justine7 = EVal(6.6, 0.2) # Justine 20130625
Justine8 = EVal(6.6, 0.2) # Justine 20130625

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

#  mail Jul 01    
# exponents


BkgMassk1 = EValAsym( -6.8777e-04, +1.62e-05,-1.62e-05)
BkgMassk2 = EValAsym( -5.0336e-04, +1.20e-04,-1.20e-04)
BkgMassk3 = EValAsym( -7.0845e-04, +2.46e-04,-2.44e-04)
BkgMassk4 = EValAsym( -1.0127e-03, +4.35e-04,-4.28e-04)
BkgMassk5 = EValAsym( -2.3485e-04, +8.21e-04,-7.00e-04)
BkgMassk6 = EValAsym( +7.5030e-05, +1.66e-03,-1.35e-03)
BkgMassk7 = EValAsym( -7.4961e-04, +1.71e-03,-1.44e-03)
BkgMassk8 = EValAsym( -7.4961e-04, +1.71e-03,-1.44e-03)


# total number of events in the (used to fit) bkg sidebands
SbGL1 =  31809
SbGL2 =  626
SbGL3 =  164
SbGL4 =  66
SbGL5 =  39
SbGL6 =  16
SbGL7 =  9
SbGL8 =  5

FracCombBin1 = EValAsym( 1.2482  ,0.00064023 ,-0.0002041)
FracCombBin2 = EValAsym( 1.2037  ,0.016023   ,-0.011116 )
FracCombBin3 = EValAsym( 1.1581  ,0.044093   ,-0.030754 )
FracCombBin4 = EValAsym( 1.0491  ,0.096209   ,-0.07299  )
FracCombBin5 = EValAsym( 0.86603 ,0.16527    ,-0.13608  )
FracCombBin6 = EValAsym( 0.60778 ,0.27691    ,-0.18031  )
FracCombBin7 = EValAsym( 0.64568 ,0.36947    ,-0.22252  )
FracCombBin8 = EValAsym( 0.4088  ,0.54035    ,-0.25331  )

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

lumi_S20r1 =  970.7
lumi_S20   = 2028.2/2.

BhhYield_S20r1 = EVal(19264., 550.)  # CHE mail subject B->hh yields 
BhhYield_S20   = EVal(49653., 507.)  # CHE mail subject B->hh yields 
BhhYield_S20   = BhhYield_S20/2.
#
BhhMisID_DLL_S20r1= EVal(1.6e-5,[0.046e-5,0.1e-5]) # Fatima 20130626
BhhMisID_DLL_S20r1= BhhMisID_DLL_S20r1.compress_errors()
BhhMisID_DLL_S20  = EVal(1.7e-5,0.044e-5)          # Fatima 20130626

MisIDGlobalFactor_S20r1 = BhhMisID_DLL_S20r1 / alpha11.BdRatE_trg
MisIDGlobalFactor_S20   = BhhMisID_DLL_S20   / alpha12.BdRatE_trg

# to be passed to table
MisIDTotalYield = MisIDGlobalFactor_S20r1*BhhYield_S20r1 + MisIDGlobalFactor_S20 * BhhYield_S20
print MisIDTotalYield 

#https://indico.cern.ch/materialDisplay.py?contribId=2&materialId=slides&confId=250106
probs_S20r1 = [
         EVal(0.16e-4, 0.0051e-4), # Fatima 20130624
         EVal(0.17e-4, 0.0054e-4), # Fatima 20130624
         EVal(0.17e-4, 0.0053e-4), # Fatima 20130624
         EVal(0.17e-4, 0.0049e-4), # Fatima 20130624
         EVal(0.17e-4, 0.0047e-4), # Fatima 20130624
         EVal(0.16e-4, 0.0046e-4), # Fatima 20130624
         EVal(0.15e-4, 0.0041e-4), # Fatima 20130624
         EVal(0.14e-4, 0.0037e-4)] # Fatima 20130624
probs_S20 = [
         EVal(0.18e-4, 0.0056e-4), # Fatima 20130624
         EVal(0.18e-4, 0.0053e-4), # Fatima 20130624
         EVal(0.19e-4, 0.0055e-4), # Fatima 20130624
         EVal(0.18e-4, 0.0045e-4), # Fatima 20130624
         EVal(0.18e-4, 0.0046e-4), # Fatima 20130624
         EVal(0.18e-4, 0.0043e-4), # Fatima 20130624
         EVal(0.16e-4, 0.0035e-4), # Fatima 20130624
         EVal(0.14e-4, 0.0031e-4)] # Fatima 20130624

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
