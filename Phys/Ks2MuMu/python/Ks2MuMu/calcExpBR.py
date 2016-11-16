from TheTable import *

NORMFCTR = 1e-8
def extNorm( cat ):
    return [ el/NORMFCTR for kw, el in alpha.iteritems() if cat in kw ]
def invSumInv( lst ):
    return 1./sum( 1./el for el in lst )

alphaTOS1 = extNorm( 'TOS1' )
alphaTOS2 = extNorm( 'TOS2' )
alphaTIS  = extNorm( 'TIS' )

alphaTIS_2011A = [8.12, 8.68, 8.11, 8.26, 8.12, 6.63, 8.41, 10.3, 11.5, 16.2]
alphaTIS_2011B = [7.4, 8.21, 7.46, 7.41, 8.65, 7.8, 8.18, 7.55, 7.6, 7.98]
alphaTOS_2011A = [1.94, 1.84, 3.4, 5.5, 2.5, 3.9, 7.8, 2.41, 2.3, 0.94]
alphaTOS_2011B = [0.92, 2.4, 1.61, 1.24, 2.5, 4.6, 2.01, 4.2, 4.2, 7.1]

alphaTIS_2011  = invSumInv(alphaTIS_2011A + alphaTIS_2011B)
alphaTOS_2011  = invSumInv(alphaTOS_2011A + alphaTOS_2011B)
alphaTOS1_2012 = invSumInv(alphaTOS1)
alphaTOS2_2012 = invSumInv(alphaTOS2)
alphaTIS_2012  = invSumInv(alphaTIS)

BRTOS_2011 = 15.4
BRTIS_2011 = 25.5

BR_2011 = 11.
alpha_2011 = invSumInv( [alphaTOS_2011, alphaTIS_2011] )
alpha_2012 = invSumInv( [alphaTOS1_2012,alphaTOS2_2012,alphaTIS_2012])

from math import sqrt
print '*** In units of 10^-9 ***'
print 'alphaTOS1_2012:', alphaTOS1_2012
print 'alphaTOS2_2012:', alphaTOS2_2012
print 'alphaTIS_2012:', alphaTIS_2012
print 'alphaTIS_2011:', alphaTIS_2011
print 'alphaTOS_2011:', alphaTOS_2011

print '-- Expected BR for TOS1:', BRTOS_2011*sqrt(alphaTOS1_2012/alphaTOS_2011)
print '-- Expected BR for TOS2:', BRTOS_2011*sqrt(alphaTOS2_2012/alphaTOS_2011)
print '-- Expected BR for TIS:', BRTOS_2011*sqrt(alphaTIS_2012/alphaTOS_2011)
print '-- Expected BR:', BR_2011*sqrt(alpha_2012/alpha_2011)
