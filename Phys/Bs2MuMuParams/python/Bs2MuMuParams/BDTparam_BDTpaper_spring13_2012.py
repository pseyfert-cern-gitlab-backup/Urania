#--------------------------------------
#
# Parameters of the BDT BsMuMu analysis
#
#--------------------------------------

#DONE
# justine factor
# misID numbers
# mass reso
# mass mean
# CBTrans
# CBExpo

#to update on 20130606
# BDT calib

#TODO
# new implementation bdt pdf
## TOCHECK BdRatE_trg
 

from math import *
from errors import *
import code

from alphaparam_spring13_2012 import *

#===============================================
# 2012 dataset - spring 2013 analysis
#
# Input from the 2012 dataset for the spring 2013 analysis
# with OLD BDT (1+1fb paper BDT)
#
#===============================================

#------------------------------------------------
# Parameters for the toys
#------------------------------------------------

BDT_binning_8 = [0., 0.25, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.]
BDT_binning = BDT_binning_8
#BDT_binning = [0., 0.25, 0.4, 0.5, 0.6, 0.7, 0.8,  1.]      # merging bins 7 and 8

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

#https://indico.cern.ch/materialDisplay.py?contribId=3&materialId=slides&confId=250103 slide 20

DLLCor1 = 0.9760 # Barbara 20130608
DLLCor2 = 0.9764 # Barbara 20130608
DLLCor3 = 0.9768 # Barbara 20130608
DLLCor4 = 0.9782 # Barbara 20130608
DLLCor5 = 0.9802 # Barbara 20130608
DLLCor6 = 0.9835 # Barbara 20130608
DLLCor7 = 0.9859 # Barbara 20130608
DLLCor8 = 0.9895 # Barbara 20130608


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

# from the note
# 
ZFrac1 = EVal(0.2847,[0.0099,0.0176])  # CHE 20130610
ZFrac2 = EVal(0.1379,[0.0029,0.0143])  # CHE 20130610
ZFrac3 = EVal(0.0988,[0.0047,0.0132])  # CHE 20130610
ZFrac4 = EVal(0.0901,[0.0035,0.0091])  # CHE 20130610
ZFrac5 = EVal(0.0967,[0.0023,0.0059])  # CHE 20130610
ZFrac6 = EVal(0.0944,[0.0041,0.0043])  # CHE 20130610
ZFrac7 = EVal(0.0962,[0.0037,0.0057])  # CHE 20130610
ZFrac8 = EVal(0.1012,[0.0035,0.0048])  # CHE 20130610

[ZFrac1, ZFrac2, ZFrac3, ZFrac4, ZFrac5, ZFrac6, ZFrac7, ZFrac8] = map(lambda x: x.compress_errors(), [ZFrac1, ZFrac2, ZFrac3, ZFrac4, ZFrac5, ZFrac6, ZFrac7, ZFrac8])


#------------------------------------------------------
# time-dependant acceptance correction 'Mathieu'
#------------------------------------------------------

# https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2Fcorrections%20and%20BR&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
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

#https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2fgroup%2fbsmumu-authors%2fLists%2fArchive%2fUpdated%20justine%20factors%20for%202012%20data&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5

Justine1 = EVal(6.1, 0.1) # Justine 20130604
Justine2 = EVal(5.5, 0.1) # Justine 20130604
Justine3 = EVal(5.7, 0.2) # Justine 20130604
Justine4 = EVal(5.5, 0.2) # Justine 20130604
Justine5 = EVal(5.7, 0.2) # Justine 20130604
Justine6 = EVal(6.3, 0.2) # Justine 20130604
Justine7 = EVal(6.8, 0.2) # Justine 20130604
Justine8 = EVal(6.9, 0.2) # Justine 20130604

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

#https://indico.cern.ch/materialDisplay.py?contribId=0&materialId=slides&confId=250106
MassMeanBs = EVal(5371.96,[0.22,0.22])   # Christian 20130606
MassMeanBd = EVal(5284.89,[0.12,0.22])   # Christian 20130606

#https://indico.cern.ch/materialDisplay.py?contribId=0&materialId=slides&confId=250106
MassResoBs = EVal(23.24,[0.09,0.43])     # Christian 20130606
MassResoBd = EVal(22.83,[0.08,0.43])     # Christian 20130606

#https://indico.cern.ch/materialDisplay.py?contribId=0&materialId=slides&confId=250106
CBTrans    = EVal(2.065,[0.005,0.010])    # Christian 20130606 for Bs 
CBExpo     = EVal(1.117,[0.013,0.038])   # Christian 20130606 for Bs 

#------------------------------------------------------
# PDF for the bgk: k-coeficient of the exp fit
#------------------------------------------------------

                      
# exponents           
BkgMassk1 = EValAsym( -7.0078e-04, +1.67e-05, -1.67e-05)  #  Ale 20130612
BkgMassk2 = EValAsym( -5.5272e-04, +1.08e-04, -1.07e-04)  #  Ale 20130612
BkgMassk3 = EValAsym( -4.1427e-04, +2.67e-04, -2.63e-04)  #  Ale 20130612
BkgMassk4 = EValAsym( -5.1963e-04, +3.84e-04, -3.72e-04)  #  Ale 20130612
BkgMassk5 = EValAsym( -7.6893e-04, +7.01e-04, -6.46e-04)  #  Ale 20130612
BkgMassk6 = EValAsym( +1.6626e-05, +1.56e-03, -1.16e-03)  #  Ale 20130612
BkgMassk7 = EValAsym( -2.2141e-04, +1.78e-03, -1.49e-03)  #  Ale 20130612
BkgMassk8 = EValAsym( -2.2141e-04, +1.78e-03, -1.49e-03)  #  Ale 20130612


# total number of events in the (used to fit) bkg sidebands
SbGL1 = 30054. # Ale 20130610
SbGL2 = 776.   # Ale 20130610
SbGL3 = 148.   # Ale 20130610
SbGL4 = 80.    # Ale 20130610
SbGL5 = 37.    # Ale 20130610
SbGL6 = 20.    # Ale 20130610
SbGL7 = 8.     # Ale 20130610
SbGL8 = 4.     # Ale 20130610

#SbGL1 = 16686. # Ale 06102012   
#SbGL2 = 412.   # Ale 06102012
#SbGL3 = 98.    # Ale 06102012
#SbGL4 = 35.    # Ale 06102012
#SbGL5 = 19.    # Ale 06102012
#SbGL6 = 10.    # Ale 06102012
#SbGL7 = 5.     # Ale 06102012
#SbGL8 = 0.     # Ale 06102012


FracCombBin1 = EValAsym(1.2493  , 0.0018506 , -0.0017287 )  #  Ale 20130612
FracCombBin2 = EValAsym(1.2133  , 0.017358  , -0.014014  )  #  Ale 20130612
FracCombBin3 = EValAsym(1.1511  , 0.05599   , -0.043173  )  #  Ale 20130612
FracCombBin4 = EValAsym(1.1276  , 0.088174  , -0.06719   )  #  Ale 20130612
FracCombBin5 = EValAsym(0.91922 , 0.16813   , -0.13417   )  #  Ale 20130612
FracCombBin6 = EValAsym(0.67269 , 0.26934   , -0.19862   )  #  Ale 20130612
FracCombBin7 = EValAsym(0.61905 , 0.39414   , -0.21251   )  #  Ale 20130612
FracCombBin8 = EValAsym(0.45047 , 0.59757   , -0.24643   )  #  Ale 20130612

#FracCombBin1 = EValAsym(1.2491  ,+0.00093 ,-0.00062 )  #  Ale 20121019
#FracCombBin2 = EValAsym(1.2184  ,+0.0181  ,-0.0088  )  #  Ale 20121019
#FracCombBin3 = EValAsym(1.171   ,+0.057   ,-0.032   )  #  Ale 20121019
#FracCombBin4 = EValAsym(1.096   ,+0.126   ,-0.075   )  #  Ale 20121019
#FracCombBin5 = EValAsym(0.983   ,+0.206   ,-0.127   )  #  Ale 20121019
#FracCombBin6 = EValAsym(0.697   ,+0.332   ,-0.232   )  #  Ale 20121019
#FracCombBin7 = EValAsym(0.560   ,+0.478   ,-0.215   )  #  Ale 20121019
#FracCombBin8 = EValAsym(0.560   ,+0.478   ,-0.215   )  #  Ale 20121019

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


BhhYield = EVal(49653., 507.)  # CHE mail subject B->hh yields 

# old #https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FBDT%20distribution%20of%20the%20misid%20components&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5

#https://indico.cern.ch/materialDisplay.py?contribId=2&materialId=slides&confId=250106
BhhMisID_DLL = EVal(1.8e-5, 0.057e-5)  # Fatima 20130606
MisIDGlobalFactor = BhhMisID_DLL/BdRatE_trg

#https://indico.cern.ch/materialDisplay.py?contribId=2&materialId=slides&confId=250106
probs = [EVal(0.20e-4, 0.0072e-4), # Fatima 20130606
         EVal(0.20e-4, 0.0069e-4), # Fatima 20130606
         EVal(0.19e-4, 0.0060e-4), # Fatima 20130606
         EVal(0.19e-4, 0.0056e-4), # Fatima 20130606
         EVal(0.17e-4, 0.0046e-4), # Fatima 20130606
         EVal(0.16e-4, 0.0042e-4), # Fatima 20130606
         EVal(0.15e-4, 0.0040e-4), # Fatima 20130606
         EVal(0.14e-4, 0.0036e-4)] # Fatima 20130606
BhhMisID_DLL_factors = map(lambda x: x/BhhMisID_DLL, probs)

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

compute_nbhh_misid(BhhYield, BmmE_trg, TISE_trg, BdE_HLT2MC, BhhMisID_DLL, MisIDGlobalFactor, BhhMisID_DLL_factors_corr, [ZFrac1, ZFrac2, ZFrac3, ZFrac4, ZFrac5, ZFrac6, ZFrac7, ZFrac8])

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
