#--------------------------------------
#
# Parameters of the BDT BsMuMu analysis
#
#--------------------------------------

#DONE
#mass
#mass reso
#Zuri fit
#justine numbers
#barbara numbers
#misid
# new implementation bdt pdf 

#TODO
# check merging justine



from math import *
from errors import *
import code

from alphaparam_Autumn2012 import *

#===============================================
# 2012 - analysis of the 2012 dataset
#===============================================

#------------------------------------------------
# Parameters for the toys
#------------------------------------------------

BDT_binning_8 = [0., 0.25, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.]
BDT_binning = [0., 0.25, 0.4, 0.5, 0.6, 0.7, 0.8,  1.]      # merging bins 7 and 8

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


#https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FBDT%20shape%20from%20PID%20cut&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
DLLCor1 = 0.9628 #  Barbara 21120925
DLLCor2 = 0.9628 #  Barbara 21120925
DLLCor3 = 0.9637 #  Barbara 21120925
DLLCor4 = 0.9657 #  Barbara 21120925
DLLCor5 = 0.9689 #  Barbara 21120925
DLLCor6 = 0.9728 #  Barbara 21120925
DLLCor7 = 0.9766 #  Barbara 21120925
DLLCor8 = 0.9810 #  Barbara 21120925


DLLCor = [DLLCor1, DLLCor2, DLLCor3, DLLCor4, DLLCor5, DLLCor6, (DLLCor7+DLLCor8)/2.]
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

#
ZFrac1=  EVal(0.291, [0.007, 0.031]).compress_errors()     # 
ZFrac2 = EVal(0.149, [0.003, 0.017]).compress_errors()     # 
ZFrac3 = EVal(0.092, [0.002, 0.009]).compress_errors()     #
ZFrac4 = EVal(0.092, [0.003, 0.005]).compress_errors()     #
ZFrac5 = EVal(0.090, [0.002, 0.006]).compress_errors()     #
ZFrac6 = EVal(0.096, [0.002, 0.009]).compress_errors()     #
ZFrac7 = EVal(0.087, [0.002, 0.007]).compress_errors()     #
ZFrac8 = EVal(0.103, [0.002, 0.012]).compress_errors()     #
ZFrac7 = ZFrac7 + ZFrac8                                   #  merging bins 7 and 8


#------------------------------------------------------
# trigger bias correction on the GL or 'Justine' correction
#------------------------------------------------------

#https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FJustine%27s%20factor&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
Justine1 = EVal(5.31,  0.09) # Justine 20120922
Justine2 = EVal(4.69,  0.11) # Justine 20120922
Justine3 = EVal(5.17,  0.13) # Justine 20120922
Justine4 = EVal(5.38,  0.14) # Justine 20120922
Justine5 = EVal(5.23,  0.13) # Justine 20120922
Justine6 = EVal(5.67,  0.14) # Justine 20120922
Justine7 = EVal(6.15,  0.14) # Justine 20120922
Justine8 = EVal(6.09,  0.14) # Justine 20120922


Justine = [Justine1, Justine2, Justine3, Justine4, Justine5, Justine6, (Justine7+Justine8)/2.]  # merging last 2 bins



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
#J_ave8 = J[7] #                             

#code.interact(local=locals())

#------------------------------------------------------
# Mass measurements
#------------------------------------------------------

#for 2012 
#svn+ssh://svn.cern.ch/reps/lhcbdocs/Notes/ANA/2012/081/latest/latex
#rev 26040
MassMeanBs = EVal(5371.55,[0.41,0.16])   # Christian                
MassMeanBd = EVal(5284.36,[0.26,0.13])   # Christian      #corrected version  26873         
MassResoBs = EVal(25.04,[0.18,0.36])     # Christian# (eq) 33 and 34 in r26933
MassResoBd = EVal(24.63,[0.13,0.36])     # Christian           
#CBTrans    = EVal(2.110,[0.043,0.005])   # for Bs Christian         
CBTrans    = EVal(2.094,[0.024,0.015])   # Christian 220112 took same as 2011 so that full correlation 

#------------------------------------------------------
# PDF for the bgk: k-coeficient of the exp fit
#------------------------------------------------------
 
# exponents
BkgMassk1 = EValAsym( -6.9239e-04 ,+2.23e-05,-2.23e-05)  #  Ale 20121019
BkgMassk2 = EValAsym( -5.6321e-04 ,+1.46e-04,-1.46e-04)  #  Ale 20121019
BkgMassk3 = EValAsym( -6.7238e-04 ,+3.14e-04,-3.12e-04)  #  Ale 20121019
BkgMassk4 = EValAsym( -8.0640e-04 ,+5.73e-04,-5.61e-04)  #  Ale 20121019
BkgMassk5 = EValAsym( -8.0884e-05 ,+9.06e-04,-8.23e-04)  #  Ale 20121019
BkgMassk6 = EValAsym( -4.9718e-03 ,+2.27e-03,-3.17e-03)  #  Ale 20121019
BkgMassk7 = EValAsym(  2.7919e-04 ,+2.68e-03,-2.11e-03)  #  Ale 20121019

# total number of events in the (used to fit) bkg sidebands
SbGL1 = 16686. # Ale 06102012   
SbGL2 = 412.   # Ale 06102012
SbGL3 = 98.    # Ale 06102012
SbGL4 = 35.    # Ale 06102012
SbGL5 = 19.    # Ale 06102012
SbGL6 = 10.    # Ale 06102012
SbGL7 = 5.     # Ale 06102012
       
FracCombBin1 = EValAsym(1.2491  ,+0.00093 ,-0.00062 )  #  Ale 20121019
FracCombBin2 = EValAsym(1.2184  ,+0.0181  ,-0.0088  )  #  Ale 20121019
FracCombBin3 = EValAsym(1.171   ,+0.057   ,-0.032   )  #  Ale 20121019
FracCombBin4 = EValAsym(1.096   ,+0.126   ,-0.075   )  #  Ale 20121019
FracCombBin5 = EValAsym(0.983   ,+0.206   ,-0.127   )  #  Ale 20121019
FracCombBin6 = EValAsym(0.697   ,+0.332   ,-0.232   )  #  Ale 20121019
FracCombBin7 = EValAsym(0.560   ,+0.478   ,-0.215   )  #  Ale 20121019

# additional systematics
SystBkgBin1 = 0.  # Marco 150212
SystBkgBin2 = 0.  # Marco 250112
SystBkgBin3 = 0.  # Marco 250112
SystBkgBin4 = 0.  # Marco 250112
SystBkgBin5 = 0.  # Marco 250112
SystBkgBin6 = 0.  # Marco 250112
SystBkgBin7 = 0.  # Marco 250112

#------------------------------------------------------
# Peaking Bkg
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
#BhhMisID = EVal(8.6e-5,[0.34e-5,0.30e-5]) # Jose/Fatima 240112                         
#BhhMisID = BhhMisID.compress_errors()                                                  
#BhhMisID_factors = [1.17,1.15,1.12,1.07,0.99,0.86,0.74,0.66] # Jose/Fatima 240112      
#NBhhMisID,NBhhMisIDlist = compute_nbhh_misid(BhhMisID,BhhMisID_factors,Justine_corr)


#------------------------------------------------------
# values WITH DLL cut
#------------------------------------------------------   

#https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FBDT%20distribution%20of%20the%20misid%20components&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
BhhMisID_DLL = EVal(1.8e-5,[0.07e-5,0.1e-5]) 
BhhMisID_DLL = BhhMisID_DLL.compress_errors()
MisIDGlobalFactor = BhhMisID_DLL/BdRatE_trg

#https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FBDT%20distribution%20of%20the%20misid%20components&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
BhhMisID_DLL_factors = [1.11, 1.11, 1.11, 1.06, 1.0, 0.89, 0.81]  #0.83, 0.78] # 

BhhMisID_DLL_factors = map(lambda x: EVal(x,0.),BhhMisID_DLL_factors)

BhhMisID_DLL_factors_ave = average_bybinsize( BhhMisID_DLL_factors )
BhhMisID_DLL_factors_corr = map( lambda x  : x/BhhMisID_DLL_factors_ave, BhhMisID_DLL_factors ) 
BhhMisID_DLL_factors_corr = map( lambda x,y: x/y, Justine_corr, BhhMisID_DLL_factors_corr )
BhhMisID_DLL_factors_corr_ave = average_bybinsize( BhhMisID_DLL_factors_corr )
BhhMisID_DLL_factors_corr = map( lambda x  : x/BhhMisID_DLL_factors_corr_ave, BhhMisID_DLL_factors_corr ) 


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
#MisIDfBDTBin8 = BhhMisID_DLL_factors_corr[7] #
    

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
#GL8MassSb1 = BMassT0          # Marco 210112
#GL8MassSb2 = BMassBlind0      # Marco 210112
#GL8MassSb3 = BMassBlind1      # Marco 210112
#GL8MassSb4 = BMassT1          # Marco 210112
