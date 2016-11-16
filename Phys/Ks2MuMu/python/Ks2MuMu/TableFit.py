### everything is in the format [[centralValue, minRange, maxRange]]
### n is the paramter of the Cryrstal B
### cheb is the paramter of the 1st order chebychev used for combinatorial:  ChebK = RooChebychev("ChebK", "ChebK", kMass, RooArgList(slopeK))

from ipa_params import *

mass, sigma, alpha, n, exp, nSig, nBkg = {}, {}, {}, {}, {}, {}
# alpha is normalization factor, s_alpha is its error


mass_TOS1=[[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490]]
sigma_TOS1=[[3.7,1,10],[3.7,1,10],[3.7,1,10],[4,1,10],[4,1,10],[4,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10]]
alpha_TOS1=[[-0.8],[-0.8],[-0.8],[-1.2,-5,-0.5],[-1.2,-5,-0.5],[-1.2,-5,-0.5],[-0.8],[-0.44,-3,-0.1],[-1.],[-1.]]
n_TOS1=[[15,0.01,100],[15,0.01,100],[15,0.01,100],[15,0.01,100],[15,0.01,100],[15,0.01,100],[15,0.01,100],[90,1,100],[15,0.01,100],[15,0.01,100]]
cheb_TOS1=[[0.5,-0.9, 0.8],[0.5,-0.9, 0.8],[0.5,-0.9, 0.8],[0.5,-0.6, 0.8],[0.5,-0.9, 0.8],[0.5,-0.9, 0.8],[0.5,-0.9, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8]]
nSig_TOS1=[[3700,0,10000],[3700,0,10000],[3700,0,10000],[3700,0,10000],[3700,0,10000],[3700,0,10000],[3700,0,10000],[3700,1000,10000],[3700,0,10000],[3700,0,10000]]
nBkg_TOS1=[[400,20,2500],[400,20,2500],[400,20,2500],[400,100,2500],[400,100,2500],[400,100,2500],[400,20,2500],[20,0,2500],[0,20,2500],[0,20,2500]]



mass_TOS2=[[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490]]
sigma_TOS2=[[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10]]
alpha_TOS2=[[-0.8],[-1.],[-0.8],[-1.],[-0.8],[-1.2],[-1.],[-1.2],[-1.2],[-1.2]]
n_TOS2=[[15,0.01,100],[15,0.01,100],[15,0.01,100],[15,0.01,100],[15,0.01,100],[90,1,100],[15,0.01,100],[90,1,100],[90,1,100],[90,1,100]]
cheb_TOS2=[[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[ -0.95,-1.001, 0.8],[0.5,-0.999999, 0.8],[ -0.95,-1.001, 0.8],[ -0.95,-1.001, 0.8],[ -0.95,-1.001, 0.8]]
nSig_TOS2=[[3700,0,10000],[3700,0,10000],[3700,0,10000],[3700,0,10000],[3700,0,10000],[3700,1000,10000],[3700,0,10000],[3700,1000,10000],[3700,1000,10000],[3700,1000,10000]]
nBkg_TOS2=[[100,20,2500],[0,20,2500],[100,20,2500],[0,20,2500],[100,20,2500],[20,0,2500],[0,20,2500],[20,0,2500],[20,0,2500],[20,0,2500]]

mass_TIS=[[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490],[461,440,490]]
sigma_TIS=[[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10],[3.7,1,10]]
alpha_TIS=[[-0.4],[-0.4],[-0.4],[-1.2],[-1.2],[-0.4],[-1.2],[-1.2],[-1.2],[-0.45]]
n_TIS=[[90,1,100],[90,1,100],[90,1,100],[90,1,100],[90,1,100],[90,1,100],[90,1,100],[90,1,100],[90,1,100],[90,1,100]]
cheb_TIS=[[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8],[0.5,-0.999999, 0.8]]
nSig_TIS=[[3700,1000,10000],[3700,1000,10000],[3700,1000,10000],[3700,1000,10000],[3700,1000,10000],[3700,1000,10000],[3700,1000,10000],[3700,1000,10000],[3700,1000,10000],[3700,1000,10000]]
nBkg_TIS=[[20,0,2500],[20,0,2500],[20,0,2500],[20,0,2500],[20,0,2500],[20,0,2500],[20,0,2500],[20,0,2500],[20,0,2500],[20,0,2500]]



## Now dummy numbers
for i in range(10):
    ix = str(i)
    mass["TIS_" + ix] = mass_TIS[i]
    sigma["TIS_" + ix] =sigma_TIS[i]
    alpha["TIS_" + ix ]= alpha_TIS[i]
    n["TIS_" + ix ]= n_TIS[i]
    cheb["TIS_" + ix ]= cheb_TIS[i]
    nSig["TIS_" + ix ]= nSig_TIS[i]
    nBkg["TIS_" + ix ]= nBkg_TIS[i]


    mass["TOS1_" + ix] = mass_TOS1[i]
    sigma["TOS1_" + ix] =sigma_TOS1[i]
    alpha["TOS1_" + ix ]= alpha_TOS1[i]
    n["TOS1_" + ix ]= n_TOS1[i]
    cheb["TOS1_" + ix ]= cheb_TOS1[i]
    nSig["TOS1_" + ix ]= nSig_TOS1[i]
    nBkg["TOS1_" + ix ]= nBkg_TOS1[i]

    mass["TOS2_" + ix] = mass_TOS2[i]
    sigma["TOS2_" + ix] =sigma_TOS2[i]
    alpha["TOS2_" + ix ]= alpha_TOS2[i]
    n["TOS2_" + ix ]= n_TOS2[i]
    cheb["TOS2_" + ix ]= cheb_TOS2[i]
    nSig["TOS2_" + ix ]= nSig_TOS2[i]
    nBkg["TOS2_" + ix ]= nBkg_TOS2[i]



