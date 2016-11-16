from math import sqrt
from operator import mul

def inv(a):
  val = 1./a[0]
  err1 = a[1]/(a[0]**2)
  err2 = a[2]/(a[0]**2)
  err3 = a[3]/(a[0]**2)
  return [val, err1, err2, err3]

def prodVal(a): # gaussian error propagation for a product
  valList = []
  relList1 = []
  relList2 = []
  relList3 = []
  for ii in range(len(a)):
    valList.append(a[ii][0])
    relList1.append((a[ii][1]/a[ii][0])**2)
    relList2.append((a[ii][2]/a[ii][0])**2)
    relList3.append((a[ii][3]/a[ii][0])**2)
  val = reduce(mul,valList,1)
  err1 = val*sqrt(sum(relList1))
  err2 = val*sqrt(sum(relList2))
  err3 = val*sqrt(sum(relList3))
  return [val, err1, err2, err3]

####################################################
###### Numbers, yields, and other input stuff ###### 
####################################################
## number = [central value, stat, syst, only fd/fs]

nBs             = [1808., 51., (38.+33.)/2., 0.] #1799 \pm 50 +38 -33
nBd             = [208656., 462., (78.+76.)/2., 0.] #208656 \pm 462 +78 -76
nPhi            = [58091., 243., 319., 0.]
fsfd            = [0.259, 0., 0., 0.015]
fdfs            = inv(fsfd)
#betaKst         = [0.9963, 0., 0.0005, 0.]
#betaPhi         = [1.033, 0., 0.022, 0.]
kappaKst        = [1.149, 0.044, 0.018, 0.]
kappaBd         = [1.107, 0.0028, 0.038, 0.]
kappaPhi        = [1.013, 0.002, 0.0074, 0.]
rKappaBdKst     = [0.963, 0.036, 0.031, 0.]
#kappaKst        = [1.165, 0.045, 0.018, 0.]
#kappaBd         = [1.117, 0.0028, 0.038, 0.]
#rKappaBdKst     = [0.959, 0.037, 0.032, 0.]
rKappaPhiKst    = prodVal([kappaPhi,inv(kappaKst)])
preBRBd         = [1.29E-3, 0., sqrt((0.05E-3)**2 + (0.13E-3)**2), 0.]
cFactor         = [1.029, 0., 0.012, 0.] # correction factor for B+/B0 production
BRBd            = prodVal( [preBRBd, cFactor] )
#BRBd             = [0.0013274099999999998, 0.0, 0.00014415667102149658, 0.0]
BRPhi           = [1.038E-3, 0.013E-3, 0.063E-3]
fsfdBRPhi       = [fsfd[0]*BRPhi[0], 0., sqrt((fsfd[0]*BRPhi[1])**2 + (fsfd[0]*BRPhi[2])**2), 0.]
### efficiency ratios with systematics:
eBdBs_11        = [0.929, 0.012]
eBdBs_12        = [0.927, 0.012]
ePhiKst_11      = [1.991, 0.025]
ePhiKst_12      = [1.986, 0.027]
eBdBs           = [(1/3.)*eBdBs_11[0] + (2/3.)*eBdBs_12[0], 0., (1/3.)*eBdBs_11[1] + (2/3.)*eBdBs_12[1], 0.] # 100% correlated*
ePhiKst         = [(1/3.)*ePhiKst_11[0] + (2/3.)*ePhiKst_12[0], 0., (1/3.)*ePhiKst_11[1] + (2/3.)*ePhiKst_12[1], 0.] # 100% correlated*
#* same PIDCalib sample.

#########################################################################
###### Calculate the weighted average with method of least squares ###### 
#########################################################################

## Split BR1 and BR2 in two parts:
# BR1 = alpha * x1
# BR2 = alpha * x2
# where alpha is a common part. Take into account correlations between x1 and x2.
## Calculate those parts separately:
alpha = prodVal( [nBs, fdfs] )#, betaKst] )
x1 = prodVal( [eBdBs, inv(nBd), BRBd, rKappaBdKst ] )
x2 = prodVal( [ePhiKst, inv(nPhi), fsfdBRPhi, rKappaPhiKst ] )#, inv(betaPhi) ] )
#x2[0] = (3./4.)*x2[0]
#x2[1] = (3./4.)*x2[1]
#x2[2] = (3./4.)*x2[2]
#x2[3] = (3./4.)*x2[3]
BKpi = [3./2., 0., 0., 0.]
BPhiKK = [0.495, 0, 0.005, 0.]
x2 = prodVal( [BKpi, BPhiKK, x2] )

## Calculate correlations (separating statistical and systematics):
# Stat:
corr_rEff_stat = (2*eBdBs[1]*ePhiKst[1])/(eBdBs[0]*ePhiKst[0]) # Assuming 100% of correlation*
rhosx1sx2_stat = (x1[0]*x2[0]*(1/2.))*((kappaKst[1]/kappaKst[0])**2 - (kappaBd[1]/kappaBd[0])**2 + (rKappaBdKst[1]/rKappaBdKst[0])**2 + corr_rEff_stat)
rho_stat = rhosx1sx2_stat/(x1[1]*x2[1])
# Syst:
corr_rEff_syst = (2*eBdBs[2]*ePhiKst[2])/(eBdBs[0]*ePhiKst[0]) # Assuming 100% of correlation*
rhosx1sx2_syst = (x1[0]*x2[0]*(1/2.))*((kappaKst[2]/kappaKst[0])**2 - (kappaBd[2]/kappaBd[0])**2 + (rKappaBdKst[2]/rKappaBdKst[0])**2 + corr_rEff_syst)
rho_syst = rhosx1sx2_syst/(x1[2]*x2[2])


## Append a total error for some relevant parameters:
eBdBs.append(sqrt(eBdBs[1]**2+eBdBs[2]**2+eBdBs[3]**2))
ePhiKst.append(sqrt(ePhiKst[1]**2+ePhiKst[2]**2+ePhiKst[3]**2))
kappaKst.append(sqrt(kappaKst[1]**2+kappaKst[2]**2+kappaKst[3]**2))
kappaBd.append(sqrt(kappaBd[1]**2+kappaBd[2]**2+kappaBd[3]**2))
rKappaBdKst.append(sqrt(rKappaBdKst[1]**2+rKappaBdKst[2]**2+rKappaBdKst[3]**2))
x1.append(sqrt(x1[1]**2+x1[2]**2+x1[3]**2))
x2.append(sqrt(x2[1]**2+x2[2]**2+x2[3]**2))
## Obtain the gaussian weight and the central value using those total errors:
corr_rEff = (2*eBdBs[4]*ePhiKst[4])/(eBdBs[0]*ePhiKst[0]) # Assuming 100% of correlation*
rhosx1sx2 = (x1[0]*x2[0]*(1/2.))*((kappaKst[4]/kappaKst[0])**2 - (kappaBd[4]/kappaBd[0])**2 + (rKappaBdKst[4]/rKappaBdKst[0])**2 + corr_rEff)
weight = (x2[4]**2 - rhosx1sx2)/(x1[4]**2 + x2[4]**2 - 2*rhosx1sx2)
averagedB_val = (alpha[0]*x1[0])*weight + (alpha[0]*x2[0])*(1.-weight)
print weight

## Calculating the uncertainties taking into account the correlations:
# Stat:
averagedB_err_1_stat = (averagedB_val/alpha[0])*alpha[1]
averagedB_err_2_stat = alpha[0]*sqrt(((1.-rho_stat**2)*(x1[1]*x2[1])**2)/(x1[1]**2 + x2[1]**2 - 2*rhosx1sx2_stat))
averagedB_err_stat = sqrt(averagedB_err_1_stat**2 + averagedB_err_2_stat**2)
# Syst:
averagedB_err_1_syst = (averagedB_val/alpha[0])*alpha[2]
averagedB_err_2_syst = alpha[0]*sqrt(((1.-rho_syst**2)*(x1[2]*x2[2])**2)/(x1[2]**2 + x2[2]**2 - 2*rhosx1sx2_syst))
averagedB_err_syst = sqrt(averagedB_err_1_syst**2 + averagedB_err_2_syst**2)


## Final results:
averagedB = [averagedB_val, averagedB_err_stat, averagedB_err_syst, averagedB_val*(fdfs[3]/fdfs[0])]
print 'AVERAGED BRANCHING RATIO: '
print 'Central value: ', averagedB[0]
print 'Stat: ', averagedB[1]
print 'Syst: ', averagedB[2]
print 'Only fd/fs: ', averagedB[3]

