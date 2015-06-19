#--------------------------------------
#
# Parameters of the BDT BsMuMu analysis
#
#--------------------------------------

from math import *
from errors import *

from alphaparam import *

#===============================================
# 2010 - Analysis note
#===============================================

#------------------------------------------------
# Parameters for the toys
#------------------------------------------------

# PDF signal calibration

# Bhh TIS events in bins
Tis2 = EVal(669.,75.) # Alessio 240611
Tis3 = EVal(687.,44.) #  Alessio 240611
Tis4 = EVal(724.,37.) # Alessio 240611

# Diegos numbers
DTisClean = EVal(3824.,367.) # Diego 140711
DTisClean = EVal(4123.,290.) # Diego 210911
DTis2 = EVal(1251.,111.)# Diego 140711
DTis3 = EVal(1114.,46.) # Diego 140711
DTis4 = EVal(1436.,47.) # Diego 140711
DTis2 = EVal(1373.,135.)# Diego 210911
DTis3 = EVal(1455.,71.) # Diego 210911
DTis4 = EVal(1801.,55.) # Diego 210911
DTisTot = DTisClean/BhhE_Clean 
DTis1 = DTisTot-DTis2-DTis3-DTis4 

# Justine Calibration
JTisClean = EVal(3421.,129.) # Justine 140711
JTisClean = EVal(3900.,148.) # Justine 090911 (@tocheck)
JTisClean = EVal(3857.,144.) # Justine 210911
JTisClean = EVal(3823.,142.) # Justine 220911
JTis1 = EVal(1527.,227.)# Justine 140711
JTis2 = EVal(1167.,72.) # Justine 140711
JTis3 = EVal(1181.,57.) # Justine 140711
JTis4 = EVal(1470.,46.) # Justine 140711
JTis2 = EVal(1223.,84.) # Justine 090911
JTis3 = EVal(1423.,62.) # Justine 090911
JTis4 = EVal(1882.,56.) # Justine 090911
JTis2 = EVal(1302.,90.) # Justine 210911
JTis3 = EVal(1476.,67.) # Justine 210911
JTis4 = EVal(1815.,54.) # Justine 210911
JTis2 = EVal(1304.,89.) # Justine 220911
JTis3 = EVal(1473.,67.) # Justine 220911
JTis4 = EVal(1805.,53.) # Justine 220911
JTisTot = JTisClean/BhhE_Clean
JTis1 = JTisTot-JTis2-JTis3-JTis4

# LNF calibratio
ATisClean =EVal(2201./0.6,107./0.6) # Alessio 140711 
ATisClean =EVal(1529.*1.72/0.6,71.5*1.72/0.6) # Flavio 090911
ATisClean =EVal(4466,201) # Flavio 210911 
ATisClean =EVal(4386,198) # Flatteo 220911 
ATis2 = EVal(1005.,76.) # Alessio, Flavio 140711
ATis3 = EVal(1186.,58.) #  Alessio, Flavio 140711
ATis4 = EVal(1451.,60.) # Alessio, Flavio 140711
ATis2 = EVal(1490.,93.) # Alessio, Flavio 090911
ATis3 = EVal(1535.,66.) #  Alessio, Flavio 090911
ATis4 = EVal(1990.,69.) # Alessio, Flavio 090911
ATis2 = EVal(1224.,95.) # Alessio, Flavio 090911
ATis3 = EVal(1700.,66.) #  Alessio, Flavio 090911
ATis4 = EVal(1990.,69.) # Alessio, Flavio 090911
ATis2 = EVal(1224.,95.) # Alessio, Flavio 210911
ATis3 = EVal(1716.,72.) #  Alessio, Flavio 210911
ATis4 = EVal(1822.,69.) # Alessio, Flavio 210911
ATis2 = EVal(1193.,92.) # Flatteo 220911
ATis3 = EVal(1697.,72.) # Flatteo 220911
ATis4 = EVal(1803.,63.) # Flatteo 220911
ATisTot = ATisClean/BhhE_Clean # CHECK: Same number in alphaparam file!!
ATis1 = ATisTot-ATis2-ATis3-ATis4 


def sys_tistot(A,D,J):
    """ systematic error for the total Bhh tis """
    da,ja = D-A,J-A
    d = max(abs(da),abs(ja))
    rel = d/A
    # print da,ja,d
    print ' Bhh ',A,' Sys (maximum difference) ',val(d),' relative ',val(rel),'%'
    return rel

def sys_fractis():
    # the sys error, enters as the sys error of the ratio, 
    # then as relative in the number (140711)
    d = [DTis1,DTis2,DTis3,DTis4]
    j = [JTis1,JTis2,JTis3,JTis4]
    a = [ATis1,ATis2,ATis3,ATis4]
    print 'Diego TIS \t ',d
    print 'Justine TIS \t ',j
    print 'Alessio TIS \t',a
    fd = map(lambda i: i/DTisTot,d)
    fj = map(lambda i: i/JTisTot,j)
    fa = map(lambda i: i/ATisTot,a)
    print 'Diego pdf \t',fd
    print 'Justine pdf \t',fj
    print 'Alessio pdf \t',fa
    dfda = map(lambda i,j: i-j,fd,fa)
    dfja = map(lambda i,j: i-j,fj,fa)
    ss = map(lambda i,j:max(abs(i),abs(j)),dfda,dfja)
    print ' sys: delta of maximum diff fraction \t ',map(val,ss)
    ss = map(lambda i,j:i/j,ss,fa)
    print ' sys: delta of maximum diff fraction (%) \t',map(val,ss)
    return ss

rel = sys_tistot(ATisClean,DTisClean,JTisClean)
print ' Tis Clean relative error \t',val(rel)
ATisClean.add_relative_error(val(rel))
print ' Tis Clean \t',ATisClean
ATisClean.compress_errors()
print ' Tis Clean (+sys) \t',ATisClean
ATisTot = ATisClean/BhhE_Clean
print ' TisTot ',ATisTot
TisTot = BhhNcanTis # TODO! They shoud match with the alphaparam file
print 'TisTot, TisTot(alpha) (should be identical!) \t',ATisTot,TisTot

ss = sys_fractis()
print ' TIS sys fractions ',map(val,ss)
Tis2 = ATis2 
Tis2.add_relative_error(val(ss[1]))
print ' Tis2 ',Tis2
Tis2.compress_errors()
Tis3 = ATis3 
Tis3.add_relative_error(val(ss[2]))
print ' Tis3 ',Tis3
Tis3.compress_errors()
Tis4 = ATis4 
Tis4.add_relative_error(val(ss[3]))
print ' Tis4 ',Tis4
Tis4.compress_errors()

# trigger bias correction on the GL or 'Justine' correction
Jave = 5.4 # Average of the Justine numbers for the 4th bins
Justine1 = EVal(5.3/Jave,0.1/Jave) # Justine, Marco 230611
Justine1 = EVal(-9999.,-9999.)  # requirementn of the toys
Justine2 = EVal(5.5/Jave,0.1/Jave) # Justine, Marco 230611
Justine3 = EVal(5.4/Jave,0.1/Jave) # Justine, Marco 230611
Justine4 = EVal(5.4/Jave,0.1/Jave) # Justine, Marco 230611
Jave = 5.35 # Average of the Justine numbers for the 4th bins140711
Justine1 = EVal(4.9/Jave,0.1/Jave) # Justine, Marco 140711
Justine1 = EVal(-9999.,-9999.)  # requirementn of the toys
Justine2 = EVal(5.0/Jave,0.1/Jave) # Justine, Marco 140711
Justine3 = EVal(5.4/Jave,0.1/Jave) # Justine, Marco 140711
Justine4 = EVal(6.1/Jave,0.1/Jave) # Justine, Marco 140711
Jave = 5.325 # Average of the Justine numbers for the 4th bins 210911
Justine1 = EVal(4.8/Jave,0.1/Jave) # Justine,  210911
Justine1 = EVal(-9999.,-9999.)  # requirementn of the toys
Justine2 = EVal(4.9/Jave,0.1/Jave) # Justine 210911
Justine3 = EVal(5.6/Jave,0.1/Jave) # Justine 210911
Justine4 = EVal(6.0/Jave,0.1/Jave) # Justine 210911


# Mass measurements
MassMeanBs = EVal(5358.0,1.0) # Diego 170611 (valid for EPS based on 150pb-1)
#MassMeanBs = EVal(5362.0, 0.) # check - Flavio 090911
MassMeanBd = EVal(5272.0,1.0) # Diego 170611 (Valid for EPS based on 150pb-1)
#MassReso = EVal(24.02,0.1,0.8) # Christian 170611 (Bs mass resolution)
MassReso = EVal(24.6,0.2) # Christian 140711 (Bs mass resolution, interpolation only)
MassReso.add_error(1.) # Christian 140711 (Bs mass resolution, interpolation only)
MassReso.compress_errors()
# other methods are used for xcheck
CBTrans = EVal(2.11,0.05)

# PDF for the bgk: k-coeficient of the exp fit
BkgMassk1 = EVal(-7.8e-4, 2.4e-5) # Marco 150711
BkgMassk2 = EVal(-7.5e-4, 2.6e-4) # Marco 150711
BkgMassk3 = EVal(-2.6e-4, [8.1e-4,-7.4e-4]) # Marco 150711
BkgMassk4 = EVal(-1.35e-3, [1.7e-3,-1.6e-03]) # Marco 150711

BkgMassk1 = EVal(-7.67e-4, 2.2e-5) # Justine,Flavio 090911
BkgMassk2 = EVal(-4.05e-4, 2.05e-4) # Justine,Flavio 090911
BkgMassk3 = EVal(-13.13e-4, [5.19e-4,-5.07e-4]) # Justine,Flavio 090911
BkgMassk4 = EVal(5.72e-4, [33.95e-4,-20.25e-04]) # Justine,Flavio 090911 TOCHECK!!
BkgMassk4 = EVal(5.89e-4, [44.77e-4,-30.52e-04]) # Justine email 120911

BkgMassk1 = EVal(-7.59e-4, 2.3e-5) # Marco 220911
BkgMassk2 = EVal(-4.50e-4, 2.1e-4) # Marco 220911
BkgMassk3 = EVal(-11.3e-4, [5.0e-4,-4.9e-4]) # Marco 220911
BkgMassk4 = EVal(-12.e-4, [17.e-4,-16.e-04]) # Marco 220911

# total number of events in the (used to fit) bkg sidebands
SbGL1 = EVal(14444.0,0) # Marco 150711
SbGL2 = EVal(122.0,0) # Marco 150711
SbGL3 = EVal(16.0,0) # Marco 150711
SbGL4 = EVal(3.0,0) # Marco 150711

SbGL1 = EVal(16731.0,0) # Justine 090911
SbGL2 = EVal(215.0,0) # Justine 090911
SbGL3 = EVal(29.0,0) # Justine 090911
SbGL4 = EVal(1.0,0) # Justine 150711

SbGL1 = EVal(16718.0,0) # Marco 210911
SbGL2 = EVal(216.0,0) # Marco 210911
SbGL3 = EVal(32.0,0) # Marco 210911
SbGL4 = EVal(3.0,0) # Marco 210711

SbGL1 = EVal(16230.0,0) # Marco 220911 applying clonedist
SbGL2 = EVal(211.0,0)   # Marco 220911 applying clonedist
SbGL3 = EVal(32.0,0)    # Marco 220911 applying clonedist
SbGL4 = EVal(3.0,0)     # Marco 220711 applying clonedist

#SystBkgBin1 = 0.021 #2.1%relative DMS. from comp with 2 expo. 150711
#SystBkgBin1 = 0.    #0 % relative DMS. from comp with 2 expo. Marco 220911
SystBkgBin1 = 0.0059     #0 % relative DMS. from comp with 2 expo. Marco 061011
#SystBkgBin2 = 0.    #0 % relative DMS. from comp with 2 expo. Marco 220911
SystBkgBin2 = 0.018    #0 % relative DMS. from comp with 2 expo. Marco 061011
#SystBkgBin3 = 0.    #0 % relative DMS. from comp with 2 expo. Marco 220911 
SystBkgBin3 = 0.24    #0 % relative DMS. from comp with 2 expo. Marco 061011
SystBkgBin4 = 0.     #0 % relative DMS. from comp with 2 expo. Marco 220911 061011

# with of the sidebands
BlindWidth = 60
#BsMassPDG = 5366.3
#BMassL0 = BsMassPDG-1200.
#BMassL1 = BsMassPDG+1200.
BMassT0 = 4900.
BMassT1 = 6000.
# BMassBlind0 = val(MassMeanBd)-BlindWidth # 2010
# BMassBlind1 = val(MassMeanBs)+BlindWidth # 2010
BMassBlind0 = 5000 #val(MassMeanBd)-BlindWidth # Justine 240611 (till Edinburg) 
BMassBlind1 =  val(MassMeanBs)+BlindWidth  # Justine 240611 (till Edinburg) 
# BMassB0 = 5207. # Marco 240611 (for EPS) 
# BMassB1 = 5423. # Marco 240611 (for EPS) 

GL1MassSb1 = BMassT0
GL1MassSb2 = BMassBlind0
GL1MassSb3 = BMassBlind1
GL1MassSb4 = BMassT1
GL2MassSb1 = BMassT0
GL2MassSb2 = BMassBlind0
GL2MassSb3 = BMassBlind1
GL2MassSb4 = BMassT1
GL3MassSb1 = BMassT0
GL3MassSb2 = BMassBlind0
GL3MassSb3 = BMassBlind1
GL3MassSb4 = BMassT1
GL4MassSb1 = BMassT0
GL4MassSb2 = BMassBlind0
GL4MassSb3 = BMassBlind1
GL4MassSb4 = BMassT1
