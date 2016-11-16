#BR_s/BR_d = fd/fs *Ns/Nd * eps_d/eps_s * kappa_d/kappa_s

from Urania.SympyBasic import *

f = Symbol("fdfs", positive = True)
eps = Symbol("eps_d_eps_s", postive = True)
yields = Symbol("R", postive = True)
kds = Symbol("kds", positive = True)
#beta = Symbol("beta", positive = True)

BR_R = f*eps*kds*yields#*beta
eps_val =  1./3*(2*.927 + .929)
eps_err = 2./3*.012 + 1./3*0.012
fdfs_val = 3.86
fdfs_err = 0.05792* fdfs_val
kds_val = 0.963
kds_stat = 0.036
kds_syst = 0.031
#beta_val = .9963
#beta_stat = 0
#beta_syst = 0.0005
yields_val = 8.65e-03
yields_stat = .24e-03
yields_syst = 0.17e-03

## now set values
Xi = [ (f, 3.86), (eps,eps_val), (yields, yields_val), (kds, kds_val) ]#, (beta,beta_val )]
sXi_stat = [0., 0., yields_stat, kds_stat]#,beta_stat]
sXi_syst =  [fdfs_err,eps_err , yields_syst, kds_syst]#,beta_syst]
sXi_fdfs = [fdfs_err, 0., 0., 0.]#,0.]
sXi_nonfdfs = [0, eps_err, yields_syst, kds_syst]#,beta_syst]
sXi_BR = [0, 0., 0., 0.]#,0.]
sXi_nonfdfsBR = [0, eps_err, yields_syst, kds_syst]#,beta_syst]
print "Ratio of BR's"
print "Central value:", BR_R.subs(Xi)*100
print "Stat", GaussErrorPropagator(BR_R, Xi, sXi_stat)*100
print "Syst", GaussErrorPropagator(BR_R, Xi, sXi_syst)*100
print "fdfs only", GaussErrorPropagator(BR_R, Xi, sXi_fdfs)*100
print "All syst but fdfs",GaussErrorPropagator(BR_R, Xi, sXi_nonfdfs)*100

BRd = Symbol("BRd", positive = True)
BR = BRd*BR_R

cFactor = [1.029, 0.012] # correction factor for B+/B0 production

BRBd = [cFactor[0]*1.29e-03]
BRBd.append( BRBd[0]*sqrt( (sqrt(.05**2+.13**2)/1.29)**2 + (cFactor[1]/cFactor[0])**2 ) )

#Xi += [(BRd,1.29e-03)]
#Xi += [(BRd,1.32741e-03)]
Xi += [(BRd,BRBd[0])]
sXi_stat += [0]
#sXi_syst += [sqrt(.05**2+.13**2)*1e-03]
#sXi_syst += [1.4415667102149658e-04]
sXi_syst += [BRBd[1]]
sXi_fdfs += [0]#sqrt(.05**2+.13)**2 e-03]
#sXi_nonfdfs += [sqrt(.05**2+.13**2)*1e-03]
#sXi_nonfdfs += [1.4415667102149658e-04]
sXi_nonfdfs += [BRBd[1]]
#sXi_BR += [sqrt(.05**2+.13**2)*1e-03]#+= [0.]
#sXi_BR += [1.4415667102149658e-04]#+= [0.]
sXi_BR += [BRBd[1]]
sXi_nonfdfsBR += [0.]

print "-----"
print "BRANCHING FRACTION"
print "Central value:", BR.subs(Xi)
print "Stat", GaussErrorPropagator(BR, Xi, sXi_stat)
print "Syst", GaussErrorPropagator(BR, Xi, sXi_syst)
print "fdfs only", GaussErrorPropagator(BR, Xi, sXi_fdfs)
print "BR only", GaussErrorPropagator(BR, Xi, sXi_BR)

print "All syst but fdfs and BR",GaussErrorPropagator(BR, Xi, sXi_nonfdfsBR)
