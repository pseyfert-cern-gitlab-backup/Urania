from GetTristanWeights_paramAc import *
eff_moms_bin1_pos = dict(
c_100 = -3.5379502,
c_020 = 0.1451399,
c_040 = -0.086963169,
c_600 = 0.05172497,
c_400 = 0.20759803,
c_200 = 0.19773166,
c_220 = -0.20364827,
c_300 = -0.81847401,
)

eff_moms_bin1_neg = dict(
c_100 = -3.8445075,
c_020 = 0.20901386,
c_040 = 0.12759797,
c_600 = -0.058553996,
c_400 = 0.54738838,
c_200 = 0.795874,
c_220 = -0.30759718,
c_300 = -1.7317347,
)

eff_moms_bin2_pos = dict(
c_100 = -2.8383674,
c_020 = 0.3270738,
c_040 = 0.13890706,
c_600 = 0.2143177,
c_400 = -0.19608506,
c_200 = -1.2329763,
c_220 = -0.23571704,
c_300 = 0.36925867,
)

eff_moms_bin2_neg = dict(
c_100 = -2.3816569,
c_020 = 0.3120106,
c_040 = 0.19846035,
c_600 = 0.092437082,
c_400 = 0.31610756,
c_200 = -1.8517321,
c_220 = -0.24812763,
c_300 = -0.34702673,
)

eff_moms_bin3_pos = dict(
c_100 = -2.0734129,
c_020 = 0.32651781,
c_040 = 0.09335132,
c_600 = 0.12587325,
c_400 = 0.2508527,
c_200 = -1.8639219,
c_220 = -0.27041409,
c_300 = -0.41328752,
)

eff_moms_bin3_neg = dict(
c_100 = -1.3483922,
c_020 = 0.20284113,
c_040 = 0.053334646,
c_600 = 0.26896006,
c_400 = 0.030861565,
c_200 = -2.1806444,
c_220 = -0.22873021,
c_300 = -0.65558934,
)

eff_moms_bin4_pos = dict(
c_100 = -1.0648702,
c_020 = 0.57189482,
c_040 = 0.10343641,
c_600 = -0.11067945,
c_400 = 0.55897555,
c_200 = -3.5663357,
c_220 = -0.59851648,
c_300 = -0.43053571,
)

eff_moms_bin4_neg = dict(
c_100 = 1.1556259,
c_020 = 1.0749463,
c_040 = 0.062263844,
c_600 = 2.1401893,
c_400 = -5.77706,
c_200 = -2.8515326,
c_220 = -2.322615,
c_300 = -4.5143589,
)

eff_moms_coefs = dict( bin1_neg = eff_moms_bin1_neg, bin2_neg = eff_moms_bin2_neg, bin3_neg = eff_moms_bin3_neg, bin4_neg = eff_moms_bin4_neg,
                       bin1_pos = eff_moms_bin1_pos, bin2_pos = eff_moms_bin2_pos, bin3_pos = eff_moms_bin3_pos, bin4_pos = eff_moms_bin4_pos )

k1 = eff_moms_coefs[eff_moms_coefs.keys()[0]]
k2 = eff_moms_coefs[eff_moms_coefs.keys()[1]]
common_csss = all( map(lambda k: k in k2, k1) )

# Dump eff func as as a string.
print '\n\nP depends on cos(thK). Y depends on cos(thL),Phi'
for moms_key, eff_moms in eff_moms_coefs.iteritems():
    
    # build list with eff func terms
    func = []

    # build normal eff term. c_ijk * P_i * Y_jk
    for mom_key, mom_val in eff_moms.iteritems():
        i,j,k = mom_key.split('_')[1][0],mom_key.split('_')[1][1],mom_key.split('_')[1][2]
        func += [ '+ %s * P_%s * Y_%s%s'%(mom_key,i,j,k)]

    # build constrain term eff term. c_ijk * P_i(cosThK = 0) * Y_j0
    for mom_key, mom_val in eff_moms.iteritems():
        j,k = mom_key.split('_')[1][1],mom_key.split('_')[1][2]
        func += [ '- %s * Y_%s%s'%(mom_key,j,k)]
    
    print 'epsilon(Omega)_%s = '%(moms_key)
    for term in func: print term 
    print
    print
    if common_csss: break  # c_ijk are the same in all categories. So print only once.


# convert to sympy
from sympy.functions.special.spherical_harmonics import Zlm as Ylm
from sympy.functions import legendre as Pl
from sympy import Symbol, cos as Cos 

#from Urania.Helicity import *
#ThetaK = Symbol('thetaK',real = True)
#ThetaL = Symbol('thetaL',real = True)
#Phi    = Symbol('Phi',real = True)
#cThK = Cos(ThetaK)

funcs = {}
for moms_key, eff_moms in eff_moms_coefs.iteritems():
    
    # build list with eff func terms
    funcs[moms_key] = 0.

    # build normal eff term. c_ijk * P_i * Y_jk
    for mom_key, mom_val in eff_moms.iteritems():
        i,j,k = int(mom_key.split('_')[1][0]),int(mom_key.split('_')[1][1]),int(mom_key.split('_')[1][2])
        
        funcs[moms_key] += mom_val * Pl(i,CThK) * Ylm(j,k,ThetaL,Phi)
    
    # build constrain term eff term. c_ijk * P_i(cosThK = 0) * Y_j0
    for mom_key, mom_val in eff_moms.iteritems():
        j,k = int(mom_key.split('_')[1][1]),int(mom_key.split('_')[1][2])
        funcs[moms_key] += - mom_val * Ylm(j,k,ThetaL,Phi)
    
for k,f in funcs.iteritems():
    print '\n\n %s\n%s'%(k,f)


print " Calculating weights, malaka"
print "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
for key in funcs.keys():
    print key + "\n"
    print CalculateWeights(changeFreeVars(funcs[key]))

    
