#BR_s/BR_d = fd/fs *Ns/Nd * eps_d/eps_s * kappa_d/kappa_s

from Urania.SympyBasic import *

#f = Symbol("fdfs", positive = True)
eps = Symbol("eps_d_eps_s", positive = True)
NS = Symbol("NS", positive = True)
Nphi = Symbol("Nphi", positive = True)
kS = Symbol("kS", positive = True)
kphi = Symbol("kphi", positive = True)
phikk = Symbol("phikk", positive = True)
#betaS = Symbol("betaS", positive = True)
#betaphi = Symbol("betaphi", positive = True)

##BR_R = eps*kphi/kS*NS/Nphi*betaS/betaphi*.5*3./2
#BR_R = eps*kphi/kS*NS/Nphi*.5*3./2
BR_R = eps*kphi/kS*NS/Nphi*phikk*3./2
phikk_val = 0.495
phikk_stat = 0.
phikk_syst = 0.005
eps_val =  1./3*1.991 + 2./3*1.986
eps_stat = 0.
eps_syst = 1./3*0.025 + 2./3*0.027
NS_val = 1808
NS_stat = 51
NS_syst = 35.5
Nphi_val = 58091
Nphi_stat = 243
Nphi_syst = 319
kS_val = 1.149
kS_stat = 0.044
kS_syst = 0.018
kphi_val = 1.013
kphi_stat =0.002
kphi_syst = 0.0074
#betaS_val = 0.9963
#betaS_stat = 0
#betaS_syst = 0.0005
#betaphi_val = 1.033
#betaphi_stat = 0.
#betaphi_syst = 0.022

## now set values
Xi = [  (eps,eps_val), (NS, NS_val), (Nphi,Nphi_val), (kS,kS_val), (kphi, kphi_val), (phikk, phikk_val) ]#, (betaS, betaS_val),(betaphi,betaphi_val)]
sXi_stat = [eps_stat, NS_stat, Nphi_stat, kS_stat,kphi_stat,phikk_stat]#,betaS_stat,betaphi_stat]
sXi_syst =  [eps_syst, NS_syst, Nphi_syst,kS_syst, kphi_syst,phikk_syst]#,betaS_syst, betaphi_syst]

sXi_BR = 6*[0.]

print "Ratio of BR's"
print "Central value:", BR_R.subs(Xi)*100
print "Stat", GaussErrorPropagator(BR_R, Xi, sXi_stat)*100
print "Syst", GaussErrorPropagator(BR_R, Xi, sXi_syst)*100

BRphi = Symbol("BRphi", positive = True)
BR = BRphi*BR_R
BRphi_val = 10.38e-04
BRphi_stat = 0
BRphi_syst = sqrt(.13**2+.63**2+.60**2)*1e-04

Xi += [(BRphi,BRphi_val)]
sXi_stat += [BRphi_stat]
sXi_nonBR = sXi_syst + [0.]
sXi_syst += [BRphi_syst]

sXi_BR += [BRphi_syst]#+= [0.]


print "-----"
print "BRANCHING FRACTION"
print "Central value:", BR.subs(Xi)
print "Stat", GaussErrorPropagator(BR, Xi, sXi_stat)
print "Syst", GaussErrorPropagator(BR, Xi, sXi_syst)
print "BR only", GaussErrorPropagator(BR, Xi, sXi_BR)

print "All syst but BR",GaussErrorPropagator(BR, Xi, sXi_nonBR)
