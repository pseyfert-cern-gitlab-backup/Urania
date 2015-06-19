#--------------------------------------
#
# Parameters of the BDT BsMuMu analysis
#
#--------------------------------------

#Done
# misID numbers
# mass reso
# mass mean
# CBTrans
# CBExpo

#to check
# BDT calib

# to be updated
# Justine factors

#TODO
## TOCHECK BdRatE_trg


from math import *
from errors import *

from alphaparam_spring13_2011 import *

#===============================================
# 2011 dataset - spring 2013 Analysis
#
# Input from the 2011 dataset for the spring 2013 analysis
# with OLD BDT (1+1fb paper BDT)
#
#===============================================

#------------------------------------------------
# Parameters for the toys
#------------------------------------------------

BDT_binning = [0., 0.25, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.]

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
    return sum( list ) / float(binning[-1]-binning[0])


#------------------------------------------------------
# DLL cut correction
# Barbara
#------------------------------------------------------

Use_DLLCor = True
#https://indico.cern.ch/materialDisplay.py?contribId=3&materialId=slides&confId=250103 slide 20

DLLCor1 = 0.9698 # Barbara 20130516
DLLCor2 = 0.9703 # Barbara 20130516
DLLCor3 = 0.9709 # Barbara 20130516
DLLCor4 = 0.9728 # Barbara 20130516
DLLCor5 = 0.9755 # Barbara 20130516
DLLCor6 = 0.9797 # Barbara 20130516
DLLCor7 = 0.9830 # Barbara 20130516
DLLCor8 = 0.9879 # Barbara 20130516

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
ZFrac1 = EVal(0.3040,[0.0167,0.0155])   # CHE 20130610
ZFrac2 = EVal(0.1254,[0.0118,0.0101])   # CHE 20130610
ZFrac3 = EVal(0.0898,[0.0084,0.0086])   # CHE 20130610
ZFrac4 = EVal(0.0936,[0.0085,0.0106])   # CHE 20130610
ZFrac5 = EVal(0.0902,[0.0034,0.0065])   # CHE 20130610
ZFrac6 = EVal(0.0988,[0.0077,0.0037])   # CHE 20130610
ZFrac7 = EVal(0.0930,[0.0053,0.0053])   # CHE 20130610
ZFrac8 = EVal(0.1052,[0.0071,0.0080])   # CHE 20130610

[ZFrac1, ZFrac2, ZFrac3, ZFrac4, ZFrac5, ZFrac6, ZFrac7, ZFrac8] = map(lambda x: x.compress_errors(), [ZFrac1, ZFrac2, ZFrac3, ZFrac4, ZFrac5, ZFrac6, ZFrac7, ZFrac8])


## def sys_tistot(A,D,J):
##     """ systematic error for the total Bhh tis """
##     da,ja = D-A,J-A
##     da,ja = val(da), val(ja)
##     d = max(abs(da),abs(ja))
##     rel = d/val(A)
##     # print da,ja,d
##     print ' Bhh ',A,' Sys (maximum difference) ',d,' relative ',rel,'%'
##     #print ' Bhh ',A,' Sys (maximum difference) ',val(d),' relative ',val(rel),'%'
##     return rel

## def sys_fractis():
##     # the sys error, enters as the sys error of the ratio, 
##     # then as relative in the number (140711)
##     d = [DTis1,DTis2,DTis3,DTis4,DTis5,DTis6,DTis7,DTis8]
##     j = [JTis1,JTis2,JTis3,JTis4,JTis5,JTis6,JTis7,JTis8]
##     a = [ATis1,ATis2,ATis3,ATis4,ATis5,ATis6,ATis7,ATis8]
##     d = map(val,d)
##     j = map(val,j)
##     a = map(val,a)
##     print 'Diego TIS \t ',d
##     print 'Justine TIS \t ',j
##     print 'Alessio TIS \t',a
##     fd = map(lambda i: i/val(DTisTot),d)
##     fj = map(lambda i: i/val(JTisTot),j)
##     fa = map(lambda i: i/val(ATisTot),a)
##     print 'Diego pdf \t',fd
##     print 'Justine pdf \t',fj
##     print 'Alessio pdf \t',fa
##     dfda = map(lambda i,j: i-j,fd,fa)
##     dfja = map(lambda i,j: i-j,fj,fa)
##     ss = map(lambda i,j:max(abs(i),abs(j)),dfda,dfja)
##     print ' sys: delta of maximum diff fraction \t ',ss #map(val,ss)
##     ss = map(lambda i,j:i/j,ss,fa)
##     print ' sys: delta of maximum diff fraction (%) \t',ss #map(val,ss)
##     return ss

## rel = sys_tistot(ATisTot,DTisTot,JTisTot) # JOSE the *Clean value do not exist anymore 
## print ' Tis Clean relative error \t',rel#val(rel)
## ATisTot.add_relative_error(rel)#val(rel))
## print ' Tis Clean \t',ATisTot
## ATisTot = ATisTot.compress_errors()                   #JOSE here the compress_errors has been change!!
## print ' Tis Clean (+sys) \t',ATisTot
## #ATisTot = ATisClean/BhhE_Clean
## print ' TisTot ',ATisTot
## TisTot = BhhNcanTis # TODO! They shoud match with the alphaparam file
## print 'TisTot, TisTot(alpha) (should be identical!) \t',ATisTot,TisTot
## if (ATisTot.value !=BhhNcanTis.value):
##     print 'ERROR, the number of Bhh TIS candidates does not match between alpha and BDT param'
    
## print ATisTot
## ss = sys_fractis()
## print ' TIS sys fractions ',ss #map(val,ss)
## TisS = [ATis2,ATis3,ATis4,ATis5,ATis6,ATis7,ATis8]
## for i in range(7):
##     TisS[i].add_relative_error(ss[i+1]) #val(ss[i+1]))
##     TisS[i] = TisS[i].compress_errors()

## ## #this is now applied merged with the Justine factors
## ## if Use_DLLCor:
## ##     print '\nApplying correction of DLL cut:'
## ##     tmp = map(EVal, DLLCor[1:], [0.]*(len(DLLCor)-1))
## ##     TisS = map(lambda t,c: t*c , TisS, tmp)
## ##     print 'TisS', TisS, '\n'

## Tis2,Tis3,Tis4,Tis5,Tis6,Tis7,Tis8 = TisS
## Tis1 = TisTot - reduce(lambda x,y:x+y,TisS)



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

#https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/Flat.aspx?RootFolder=%2Fgroup%2Fbsmumu-authors%2FLists%2FArchive%2FJustine%20Factors%20for%202011&FolderCTID=0x01200200FDDA4DAA3D364E4F8BB386765CF56DC5
Justine1 = EVal(6.2 , 0.2) # Justine 20130611
Justine2 = EVal(6.0 , 0.2) # Justine 20130611
Justine3 = EVal(5.9 , 0.2) # Justine 20130611
Justine4 = EVal(5.9 , 0.2) # Justine 20130611
Justine5 = EVal(6.3 , 0.2) # Justine 20130611
Justine6 = EVal(6.6 , 0.2) # Justine 20130611
Justine7 = EVal(7.0 , 0.2) # Justine 20130611
Justine8 = EVal(7.2 , 0.2) # Justine 20130611
Justine = [Justine1, Justine2, Justine3, Justine4, Justine5, Justine6, Justine7, Justine8]

# Jose- Compute the Justine average by bin size, and the correction factor
Justine_ave  = average_bybinsize( Justine )
Justine_corr = map(lambda x: x/Justine_ave, Justine )

# Jose- Compute the Justine average by bin size, and the correction factor with DLL cuts
Justine_DLL      = map(lambda x,y: x/y, Justine, DLLCor)
Justine_DLL_ave  = average_bybinsize( Justine_DLL )
Justine_DLL_corr = map(lambda x: x/Justine_DLL_ave, Justine_DLL )

if Use_DLLCor == True:
    J = Justine_DLL_corr
else:
    J = Justine_corr
 

J_ave1 = J[0] #  
J_ave2 = J[1] #  ##DIEGO::CHECK 
J_ave3 = J[2] #  ##DIEGO::CHECK 
J_ave4 = J[3] #  ##DIEGO::CHECK 
J_ave5 = J[4] #  ##DIEGO::CHECK 
J_ave6 = J[5] #  ##DIEGO::CHECK 
J_ave7 = J[6] #  ##DIEGO::CHECK 
J_ave8 = J[7] #  ##DIEGO::CHECK 

#------------------------------------------------------
# Mass measurements
#------------------------------------------------------

#https://indico.cern.ch/materialDisplay.py?contribId=0&materialId=slides&confId=250106
MassMeanBs = EVal(5371.70,[0.26,0.16])  # Christian 20130606
MassMeanBd = EVal(5284.91,[0.17,0.19])  # Christian 20130606

#https://indico.cern.ch/materialDisplay.py?contribId=0&materialId=slides&confId=250106
MassResoBs = EVal(23.22,[0.15,0.44])     # Christian 20130606
MassResoBd = EVal(22.84,[0.14,0.41])     # Christian 20130606

#https://indico.cern.ch/materialDisplay.py?contribId=0&materialId=slides&confId=250106
CBTrans    = EVal(2.065,[0.005,0.010])   # Christian 20130606
CBExpo     = EVal(1.117,[0.013,0.038])   # Christian 20130606

#------------------------------------------------------
# PDF for the bgk: k-coeficient of the exp fit
#------------------------------------------------------


# exponents
BkgMassk1 = EValAsym(-6.8971e-04, +2.58e-05, -2.58e-05) # Ale 20130612
BkgMassk2 = EValAsym(-3.4477e-04, +1.70e-04, -1.69e-04) # Ale 20130612
BkgMassk3 = EValAsym(-1.3775e-04, +3.71e-04, -3.60e-04) # Ale 20130612
BkgMassk4 = EValAsym(-1.7604e-04, +6.21e-04, -5.82e-04) # Ale 20130612
BkgMassk5 = EValAsym(-3.9408e-04, +8.77e-04, -7.89e-04) # Ale 20130612
BkgMassk6 = EValAsym(-7.3851e-04, +2.53e-03, -2.00e-03) # Ale 20130612
BkgMassk7 = EValAsym(-1.1609e-03, +2.16e-03, -1.71e-03) # Ale 20130612
BkgMassk8 = EValAsym(-1.1609e-03, +2.16e-03, -1.71e-03) # Ale 20130612


# total number of events in the (used to fit) bkg sidebands
SbGL1 = 12569.  # Ale 20130610
SbGL2 = 309.    # Ale 20130610
SbGL3 = 78.     # Ale 20130610
SbGL4 = 32.     # Ale 20130610
SbGL5 = 21.     # Ale 20130610
SbGL6 = 6.      # Ale 20130610
SbGL7 = 5.      # Ale 20130610
SbGL8 = 4.      # Ale 20130610

#SbGL1 = 13379.  #  Ale    
#SbGL2 = 399.    #  Ale 
#SbGL3 = 92.     #  Ale 
#SbGL4 = 33.     #  Ale 
#SbGL5 = 17.     #  Ale 
#SbGL6 = 10.     #  Ale 
#SbGL7 = 7.      #  Ale 
#SbGL8 = 6.      #  Ale 


FracCombBin1 = EValAsym( 1.2544 , 0.0028176, -0.0025142  )  #  Ale 20130612
FracCombBin2 = EValAsym( 1.2287 , 0.027789 , -0.018753   )  #  Ale 20130612
FracCombBin3 = EValAsym( 1.1365 , 0.076964 , -0.051522   )  #  Ale 20130612
FracCombBin4 = EValAsym( 1.1291 , 0.1463   , -0.091224   )  #  Ale 20130612
FracCombBin5 = EValAsym( 0.99077, 0.21434  , -0.14722    )  #  Ale 20130612
FracCombBin6 = EValAsym( 0.65263, 0.51288  , -0.26803    )  #  Ale 20130612
FracCombBin7 = EValAsym( 0.60749, 0.58407  , -0.30813    )  #  Ale 20130612
FracCombBin8 = EValAsym( 0.56998, 0.59124  , -0.26654    )  #  Ale 20130612


# additional systematics
SystBkgBin1 = 0.     # Marco 150212
SystBkgBin2 = 0.     # Marco 250112
SystBkgBin3 = 0.     # Marco 250112
SystBkgBin4 = 0.     # Marco 250112
SystBkgBin5 = 0.     # Marco 250112
SystBkgBin6 = 0.     # Marco 250112
SystBkgBin7 = 0.     # Marco 250112
SystBkgBin8 = 0.     # Marco 250112


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

#------------------------------------------------------
# values WITH DLL cut
#------------------------------------------------------   

BhhYield = EVal(19264., 550.)  # CHE mail subject B->hh yields 

#https://indico.cern.ch/materialDisplay.py?contribId=2&materialId=slides&confId=250106

BhhMisID_DLL = EVal(1.7e-5,0.055e-5) #EVal(1.52e-5,[0.07e-5,0.07e-5]) # Fatima 20130606
BhhMisID_DLL = BhhMisID_DLL.compress_errors()
MisIDGlobalFactor = BhhMisID_DLL/BdRatE_trg  ## TOCHECK BdRatE_trg

#https://indico.cern.ch/materialDisplay.py?contribId=2&materialId=slides&confId=250106
probs = [EVal(0.18e-4, 0.0069e-4), # Fatima 20130606
         EVal(0.18e-4, 0.0063e-4), # Fatima 20130606
         EVal(0.18e-4, 0.0061e-4), # Fatima 20130606
         EVal(0.17e-4, 0.0053e-4), # Fatima 20130606
         EVal(0.16e-4, 0.0051e-4), # Fatima 20130606
         EVal(0.15e-4, 0.0043e-4), # Fatima 20130606
         EVal(0.14e-4, 0.0043e-4), # Fatima 20130606
         EVal(0.13e-4, 0.0040e-4)] # Fatima 20130606
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

MisIDfBDTBin1 = BhhMisID_DLL_factors_corr[0] #
MisIDfBDTBin2 = BhhMisID_DLL_factors_corr[1] #
MisIDfBDTBin3 = BhhMisID_DLL_factors_corr[2] #
MisIDfBDTBin4 = BhhMisID_DLL_factors_corr[3] #
MisIDfBDTBin5 = BhhMisID_DLL_factors_corr[4] #
MisIDfBDTBin6 = BhhMisID_DLL_factors_corr[5] #
MisIDfBDTBin7 = BhhMisID_DLL_factors_corr[6] #
MisIDfBDTBin8 = BhhMisID_DLL_factors_corr[7] #
    

# fraction of the peaking bkg in the Bd, Bs 60 MeV mass windows
## fpeakBd = EVal(0.53,0.035) # Diego 140711 
## fpeakBs = EVal(0.11,0.035) # Diego 140711
fpeakBd = EValAsym(0.48 ,0.2 ,0.08 ) # Diego 270112
fpeakBs = EValAsym(0.088,0.03,0.021) # Diego 270112

# Measured Bs BR
BRMeasuredBs = EValAsym(4.3e-9,4.9e-9,3.4e-9)


#------------------------------------------------------
# Sidebands definition
#------------------------------------------------------

BlindWidth  = 60                         # Marco 210112
BMassT0     = 4900.                      # Marco 210112
BMassBlind0 = val(MassMeanBd)-BlindWidth # NEW
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

