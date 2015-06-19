#--------------------------------------
#
# Parameters of the BDT BsMuMu analysis
#
#--------------------------------------



### TODO Confim the direction of the DLL cut correctio!
### GetBarbara to confim the numbers!         



from math import *
from errors import *

from alphaparam_1fb import *

#===============================================
# 2011 - 1fb-1 Analysis
#
# Modification of the input for the 1fb-1 analysis of 2011
# with Ale numbers
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
#https://indico.cern.ch/getFile.py/access?contribId=5&resId=0&materialId=slides&confId=173406
DLLCor1 = 0.9686 #  Barbara  230112
DLLCor2 = 0.9686 #  Barbara  230112
DLLCor3 = 0.9693 #  Barbara  230112
DLLCor4 = 0.9710 #  Barbara  230112
DLLCor5 = 0.9740 #  Barbara  230112
DLLCor6 = 0.9776 #  Barbara  230112
DLLCor7 = 0.9812 #  Barbara  230112
DLLCor8 = 0.9854 #  Barbara  230112
DLLCor = [DLLCor1, DLLCor2, DLLCor3, DLLCor4, DLLCor5, DLLCor6, DLLCor7, DLLCor8]
DLLCor = map(lambda x : EVal(x,0.),DLLCor)
DLLCor_ave = average_bybinsize( DLLCor )


#------------------------------------------------------
#
# PDF signal calibration
#
#------------------------------------------------------


#------------------------------------------------------
# Diegos numbers
#------------------------------------------------------

## DTisClean = EVal(3824.,367.) # Diego 140711
## DTisClean = EVal(4123.,290.) # Diego 210911
## DTis2 = EVal(1251.,111.)# Diego 140711
## DTis3 = EVal(1114.,46.) # Diego 140711
## DTis4 = EVal(1436.,47.) # Diego 140711
## DTis2 = EVal(1373.,135.)# Diego 210911
## DTis3 = EVal(1455.,71.) # Diego 210911
## DTis4 = EVal(1801.,55.) # Diego 210911

#https://indico.cern.ch/getFile.py/access?contribId=9&resId=0&materialId=slides&confId=171141
DTisTot= EVal(17041.,717.)# Xabier  230112
DTis2  = EVal(2141.,76. ) # Xabier  230112
DTis3  = EVal(1663.,89. ) # Xabier  230112
DTis4  = EVal(1510.,54. ) # Xabier  230112
DTis5  = EVal(1703.,54. ) # Xabier  230112
DTis6  = EVal(1834.,56. ) # Xabier  230112
DTis7  = EVal(2078.,60. ) # Xabier  230112
DTis8  = EVal(1958.,85. ) # Xabier  230112

DTis1 = DTisTot-DTis2-DTis3-DTis4-DTis5-DTis6-DTis7-DTis8  


#------------------------------------------------------
# Justine Calibration
#------------------------------------------------------

## JTisClean = EVal(3421.,129.) # Justine 140711
## JTisClean = EVal(3900.,148.) # Justine 090911 (@tocheck)
## JTisClean = EVal(3857.,144.) # Justine 210911
## JTisClean = EVal(3823.,142.) # Justine 220911
## JTis1 = EVal(1527.,227.)# Justine 140711
## JTis2 = EVal(1167.,72.) # Justine 140711
## JTis3 = EVal(1181.,57.) # Justine 140711
## JTis4 = EVal(1470.,46.) # Justine 140711
## JTis2 = EVal(1223.,84.) # Justine 090911
## JTis3 = EVal(1423.,62.) # Justine 090911
## JTis4 = EVal(1882.,56.) # Justine 090911
## JTis2 = EVal(1302.,90.) # Justine 210911
## JTis3 = EVal(1476.,67.) # Justine 210911
## JTis4 = EVal(1815.,54.) # Justine 210911
## JTis2 = EVal(1304.,89.) # Justine 220911
## JTis3 = EVal(1473.,67.) # Justine 220911
## JTis4 = EVal(1805.,53.) # Justine 220911

## https://groups.cern.ch/group/bsmumu-authors/Lists/Archive/DispForm.aspx?ID=144 updated

JTisTot= EVal(15911.,708.) #EVal(17535.,769.) # Justine 220112 
JTis2  = EVal( 1993.,121.) #EVal( 2211.,135.) # Justine 220112
JTis3  = EVal( 1517., 90.) #EVal( 1711., 98.) # Justine 220112
JTis4  = EVal( 1444., 67.) #EVal( 1567., 70.) # Justine 220112
JTis5  = EVal( 1563., 53.) #EVal( 1700., 55.) # Justine 220112
JTis6  = EVal( 1764., 56.) #EVal( 1878., 59.) # Justine 220112
JTis7  = EVal( 2018., 57.) #EVal( 2155., 58.) # Justine 220112
JTis8  = EVal( 2255., 54.) #EVal( 2356., 55.) # Justine 220112
JTis1  = JTisTot-JTis2-JTis3-JTis4-JTis5-JTis6-JTis7-JTis8

#------------------------------------------------------
# LNF calibration
#------------------------------------------------------

## ATisClean =EVal(2201./0.6,107./0.6) # Alessio 140711 
## ATisClean =EVal(1529.*1.72/0.6,71.5*1.72/0.6) # Flavio 090911
## ATisClean =EVal(4466,201) # Flavio 210911 
## ATisClean =EVal(4386,198) # Flatteo 220911
## ATis2 = EVal(1005.,76.) # Alessio, Flavio 140711
## ATis3 = EVal(1186.,58.) #  Alessio, Flavio 140711
## ATis4 = EVal(1451.,60.) # Alessio, Flavio 140711
## ATis2 = EVal(1490.,93.) # Alessio, Flavio 090911
## ATis3 = EVal(1535.,66.) #  Alessio, Flavio 090911
## ATis4 = EVal(1990.,69.) # Alessio, Flavio 090911
## ATis2 = EVal(1224.,95.) # Alessio, Flavio 090911
## ATis3 = EVal(1700.,66.) #  Alessio, Flavio 090911
## ATis4 = EVal(1990.,69.) # Alessio, Flavio 090911
## ATis2 = EVal(1224.,95.) # Alessio, Flavio 210911
## ATis3 = EVal(1716.,72.) #  Alessio, Flavio 210911
## ATis4 = EVal(1822.,69.) # Alessio, Flavio 210911
## ATis2 = EVal(1193.,92.) # Flatteo 220911
## ATis3 = EVal(1697.,72.) # Flatteo 220911
## ATis4 = EVal(1803.,63.) # Flatteo 220911

#https://indico.cern.ch/getFile.py/access?contribId=6&resId=0&materialId=slides&confId=173406
ATisTot=EVal(16734.,1312.) # Flatteo  210112 757_stat, added syst
ATis2 = EVal(1877.,88.)    # Flatteo  210112 
ATis3 = EVal(1486.,57.)    # Flatteo  210112
ATis4 = EVal(1447.,53.)    # Flatteo  210112
ATis5 = EVal(1729.,52.)    # Flatteo  210112
ATis6 = EVal(1846.,52.)    # Flatteo  210112
ATis7 = EVal(2133.,53.)    # Flatteo  210112
ATis8 = EVal(2245.,53.)    # Flatteo  210112

ATis1 = ATisTot-ATis2-ATis3-ATis4-ATis5-ATis6-ATis7-ATis8  

def sys_tistot(A,D,J):
    """ systematic error for the total Bhh tis """
    da,ja = D-A,J-A
    da,ja = val(da), val(ja)
    d = max(abs(da),abs(ja))
    rel = d/val(A)
    # print da,ja,d
    print ' Bhh ',A,' Sys (maximum difference) ',d,' relative ',rel,'%'
    #print ' Bhh ',A,' Sys (maximum difference) ',val(d),' relative ',val(rel),'%'
    return rel

def sys_fractis():
    # the sys error, enters as the sys error of the ratio, 
    # then as relative in the number (140711)
    d = [DTis1,DTis2,DTis3,DTis4,DTis5,DTis6,DTis7,DTis8]
    j = [JTis1,JTis2,JTis3,JTis4,JTis5,JTis6,JTis7,JTis8]
    a = [ATis1,ATis2,ATis3,ATis4,ATis5,ATis6,ATis7,ATis8]
    d = map(val,d)
    j = map(val,j)
    a = map(val,a)
    print 'Diego TIS \t ',d
    print 'Justine TIS \t ',j
    print 'Alessio TIS \t',a
    fd = map(lambda i: i/val(DTisTot),d)
    fj = map(lambda i: i/val(JTisTot),j)
    fa = map(lambda i: i/val(ATisTot),a)
    print 'Diego pdf \t',fd
    print 'Justine pdf \t',fj
    print 'Alessio pdf \t',fa
    dfda = map(lambda i,j: i-j,fd,fa)
    dfja = map(lambda i,j: i-j,fj,fa)
    ss = map(lambda i,j:max(abs(i),abs(j)),dfda,dfja)
    print ' sys: delta of maximum diff fraction \t ',ss #map(val,ss)
    ss = map(lambda i,j:i/j,ss,fa)
    print ' sys: delta of maximum diff fraction (%) \t',ss #map(val,ss)
    return ss

rel = sys_tistot(ATisTot,DTisTot,JTisTot) # JOSE the *Clean value do not exist anymore 
print ' Tis Clean relative error \t',rel#val(rel)
ATisTot.add_relative_error(rel)#val(rel))
print ' Tis Clean \t',ATisTot
ATisTot = ATisTot.compress_errors()                   #JOSE here the compress_errors has been change!!
print ' Tis Clean (+sys) \t',ATisTot
#ATisTot = ATisClean/BhhE_Clean
print ' TisTot ',ATisTot
TisTot = BhhNcanTis # TODO! They shoud match with the alphaparam file
print 'TisTot, TisTot(alpha) (should be identical!) \t',ATisTot,TisTot
if (ATisTot.value !=BhhNcanTis.value):
    print 'ERROR, the number of Bhh TIS candidates does not match between alpha and BDT param'
    
print ATisTot
ss = sys_fractis()
print ' TIS sys fractions ',ss #map(val,ss)
TisS = [ATis2,ATis3,ATis4,ATis5,ATis6,ATis7,ATis8]
for i in range(7):
    TisS[i].add_relative_error(ss[i+1]) #val(ss[i+1]))
    TisS[i] = TisS[i].compress_errors()

## #this is now applied merged with the Justine factors
## if Use_DLLCor:
##     print '\nApplying correction of DLL cut:'
##     tmp = map(EVal, DLLCor[1:], [0.]*(len(DLLCor)-1))
##     TisS = map(lambda t,c: t*c , TisS, tmp)
##     print 'TisS', TisS, '\n'

Tis2,Tis3,Tis4,Tis5,Tis6,Tis7,Tis8 = TisS
Tis1 = TisTot - reduce(lambda x,y:x+y,TisS)

#------------------------------------------------------
# trigger bias correction on the GL or 'Justine' correction
#------------------------------------------------------

## Jave = 5.4 # Average of the Justine numbers for the 4th bins
## Justine1 = EVal(5.3/Jave,0.1/Jave) # Justine, Marco 230611
## Justine1 = EVal(-9999.,-9999.)  # requirementn of the toys
## Justine2 = EVal(5.5/Jave,0.1/Jave) # Justine, Marco 230611
## Justine3 = EVal(5.4/Jave,0.1/Jave) # Justine, Marco 230611
## Justine4 = EVal(5.4/Jave,0.1/Jave) # Justine, Marco 230611
## Jave = 5.35 # Average of the Justine numbers for the 4th bins140711
## Justine1 = EVal(4.9/Jave,0.1/Jave) # Justine, Marco 140711
## Justine1 = EVal(-9999.,-9999.)  # requirementn of the toys
## Justine2 = EVal(5.0/Jave,0.1/Jave) # Justine, Marco 140711
## Justine3 = EVal(5.4/Jave,0.1/Jave) # Justine, Marco 140711
## Justine4 = EVal(6.1/Jave,0.1/Jave) # Justine, Marco 140711
## Jave = 5.325 # Average of the Justine numbers for the 4th bins 210911
## Justine1 = EVal(4.8/Jave,0.1/Jave) # Justine,  210911
## Justine1 = EVal(-9999.,-9999.)  # requirementn of the toys
## Justine2 = EVal(4.9/Jave,0.1/Jave) # Justine 210911
## Justine3 = EVal(5.6/Jave,0.1/Jave) # Justine 210911
## Justine4 = EVal(6.0/Jave,0.1/Jave) # Justine 210911

#https://indico.cern.ch/getFile.py/access?contribId=3&resId=0&materialId=slides&confId=173406 
Justine1 = EVal(5.4,0.1) # Justine 220112  used only in the computation of Jave but ont directly 
Justine2 = EVal(5.2,0.1) # Justine 220112 
Justine3 = EVal(5.2,0.1) # Justine 220112
Justine4 = EVal(5.7,0.2) # Justine 220112
Justine5 = EVal(5.9,0.2) # Justine 220112
Justine6 = EVal(6.1,0.2) # Justine 220112
Justine7 = EVal(6.2,0.2) # Justine 220112
Justine8 = EVal(6.3,0.2) # Justine 220112
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
 

J_ave1 = EVal(-9999.,-9999.)  # requirementn of the toys  ##DIEGO::CHECK   And that's what will be passed to the toys under the JUSTINE labels
J_ave2 = J[1] #                             ##DIEGO::CHECK 
J_ave3 = J[2] #                             ##DIEGO::CHECK 
J_ave4 = J[3] #                             ##DIEGO::CHECK 
J_ave5 = J[4] #                             ##DIEGO::CHECK 
J_ave6 = J[5] #                             ##DIEGO::CHECK 
J_ave7 = J[6] #                             ##DIEGO::CHECK 
J_ave8 = J[7] #                             ##DIEGO::CHECK 

#------------------------------------------------------
# Mass measurements
#------------------------------------------------------

#MassMeanBs = EVal(5358.0,1.0) # Diego 170611 (valid for EPS based on 150pb-1)
#MassMeanBs = EVal(5362.0, 0.) # check - Flavio 090911
#MassMeanBd = EVal(5272.0,1.0) # Diego 170611 (Valid for EPS based on 150pb-1)
#MassReso = EVal(24.02,0.1,0.8) # Christian 170611 (Bs mass resolution)
#MassReso.add_error(1.)    # Christian 140711 (Bs mass resolution, interpolation only)
#CBTrans = EVal(2.11,0.05)

#https://indico.cern.ch/materialDisplay.py?contribId=8&materialId=slides&confId=171141
MassMeanBs = EVal(5372.96, [0.32,0.28])  # Christian 220112
MassMeanBd = EVal(5284.63,[0.20,0.27])   # Christian 220112 
MassResoBs = EVal(24.8,[0.2,0.6])        # Christian 220112 
MassResoBd = EVal(24.2,[0.1,0.5])        # Christian 220112 
#MassReso.add_error(1.)                  # Christian 220112 Not needed anymore as not anymore using linear interpolation  
CBTrans    = EVal(2.094,[0.024,0.015])   # Christian 220112 (for Bs !)

#------------------------------------------------------
# PDF for the bgk: k-coeficient of the exp fit
#------------------------------------------------------

# exponents
BkgMassk1 = EValAsym( -6.8506e-04, +2.90e-05, -2.91e-05 ) # Ale 20123009
BkgMassk2 = EValAsym( -5.0993e-04, +1.68e-04, -1.68e-04 ) # Ale 20123009 
BkgMassk3 = EValAsym( -1.0039e-03, +3.62e-04, -3.67e-04 ) # Ale 20123009 
BkgMassk4 = EValAsym( -2.3167e-04, +5.86e-04, -5.90e-04 ) # Ale 20123009 
BkgMassk5 = EValAsym( -7.0666e-04, +6.66e-04, -6.80e-04 ) # Ale 20123009 
BkgMassk6 = EValAsym( -1.5353e-03, +1.85e-03, -2.06e-03 ) # Ale 20123009 
BkgMassk7 = EValAsym( -5.8944e-04, +1.39e-03, -1.44e-03 ) # Ale 20123009 
BkgMassk8 = EValAsym( -5.8944e-04, +1.39e-03, -1.44e-03 ) # Ale 20123009 

# total number of events in the (used to fit) bkg sidebands
SbGL1 = 11717.  #  Ale 20123009   
SbGL2 = 346.    #  Ale 20123009
SbGL3 = 77.     #  Ale 20123009
SbGL4 = 28.     #  Ale 20123009
SbGL5 = 22.     #  Ale 20123009
SbGL6 = 3.      #  Ale 20123009
SbGL7 = 4.      #  Ale 20123009
SbGL8 = 1.      #  Ale 20123009


FracCombBin1 = EValAsym( 1., 0., 0. )  #  Ale 20123009
FracCombBin2 = EValAsym( 1., 0., 0. )  #  Ale 20123009
FracCombBin3 = EValAsym( 1., 0., 0. )  #  Ale 20123009
FracCombBin4 = EValAsym( 1., 0., 0. )  #  Ale 20123009
FracCombBin5 = EValAsym( 1., 0., 0. )  #  Ale 20123009
FracCombBin6 = EValAsym( 1., 0., 0. )  #  Ale 20123009
FracCombBin7 = EValAsym( 1., 0., 0. )  #  Ale 20123009
FracCombBin8 = EValAsym( 1., 0., 0. )  #  Ale 20123009


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
BhhMisID = EVal(8.6e-5,[0.34e-5,0.30e-5]) # Jose/Fatima 240112                         
BhhMisID = BhhMisID.compress_errors()                                                  
BhhMisID_factors = [1.17,1.15,1.12,1.07,0.99,0.86,0.74,0.66] # Jose/Fatima 240112      
#NBhhMisID,NBhhMisIDlist = compute_nbhh_misid(BhhMisID,BhhMisID_factors,Justine_corr)


#------------------------------------------------------
# values WITH DLL cut
#------------------------------------------------------   

BhhMisID_DLL = EVal(1.52e-5,[0.07e-5,0.07e-5]) # Jose/Fatima 240112
BhhMisID_DLL = BhhMisID_DLL.compress_errors()
MisIDGlobalFactor = BhhMisID_DLL/BdRatE_trg

BhhMisID_DLL_factors = [1.04,1.07,1.06,1.07,1.04,0.95,0.87,0.81] # Jose/Fatima 240112
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

MisIDfBDTBin1 = EVal(-999.,-999.) #BhhMisID_factors[0]  ##DIEGO::CHECK
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
BMassT0     = 0.                         # NEW
BMassBlind0 = 0.                         # NEW
BMassBlind1 = val(MassMeanBs)+BlindWidth # Marco 210112
BMassT1     = 6550.                      # NEW

GL1MassSb1 = BMassT0          # 
GL1MassSb2 = BMassBlind0      # 
GL1MassSb3 = BMassBlind1      # 
GL1MassSb4 = BMassT1          # 
GL2MassSb1 = BMassT0          # 
GL2MassSb2 = BMassBlind0      # 
GL2MassSb3 = BMassBlind1      # 
GL2MassSb4 = BMassT1          # 
GL3MassSb1 = BMassT0          # 
GL3MassSb2 = BMassBlind0      # 
GL3MassSb3 = BMassBlind1      # 
GL3MassSb4 = BMassT1          # 
GL4MassSb1 = BMassT0          # 
GL4MassSb2 = BMassBlind0      # 
GL4MassSb3 = BMassBlind1      # 
GL4MassSb4 = BMassT1          # 
GL5MassSb1 = BMassT0          # 
GL5MassSb2 = BMassBlind0      # 
GL5MassSb3 = BMassBlind1      # 
GL5MassSb4 = BMassT1          # 
GL6MassSb1 = BMassT0          # 
GL6MassSb2 = BMassBlind0      # 
GL6MassSb3 = BMassBlind1      # 
GL6MassSb4 = BMassT1          # 
GL7MassSb1 = BMassT0          # 
GL7MassSb2 = BMassBlind0      # 
GL7MassSb3 = BMassBlind1      # 
GL7MassSb4 = BMassT1          # 
GL8MassSb1 = BMassT0          # 
GL8MassSb2 = BMassBlind0      # 
GL8MassSb3 = BMassBlind1      # 
GL8MassSb4 = BMassT1          # 

