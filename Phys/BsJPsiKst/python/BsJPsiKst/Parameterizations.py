from ROOT import *
from Urania.SympyBasic import *
from sympy import Eq, solve

############################
## SYMBOLS                ##
############################

### Define the polarization dependent phis's and C's

fL = Symbol("f_L",positive = True)
fpa = USymbol("f_pa","f_{||}", positive = True)
fpe = USymbol("f_pe","f_{\\perp}", positive = True)

fs = Symbol("f_S",positive = True)
N = Symbol("N", positive = True)
Nbar = USymbol("Nbar","\\bar{N}", positive = True)
Np = Symbol("N_P",positive = True)
Npbar = USymbol("Npbar","\\bar{N_P}",positive = True)
fLbar = USymbol("fLbar","\\bar{f_L}",positive = True)
fpabar = USymbol("fpabar","\\bar{f_{||}}", positive = True)
fpebar = USymbol("fpebar", "\\bar{f_{\\perp}}", positive = True)

fsbar= USymbol("fsbar","\\bar{f_S}",positive = True)
ACPL = USymbol("ACPL","\\Delta_L",real = True)
ACPpa = USymbol("ACPpa","\\Delta_{||}",real = True)
ACPpe = USymbol("ACPpe","\\Delta_{\\perp}",real = True)
ACPS = USymbol("ACPS","\\Delta_S",real = True)

fLhat = USymbol("fLhat", "\\hat{f_L}",positive = True)
fpahat = USymbol("fpahat", "\\hat{f_{||}}", positive = True)
fshat = USymbol("fshat","\\hat{f_S}", positive = True)

###########################
##  TRANSFORM EQUATIONS  ##
###########################



eq1 = Eq( fLhat, (Np*fL + Npbar*fLbar)/(Np+Npbar))
eq2 = Eq( fpahat, (Np*fpa + Npbar*fpabar)/(Np+Npbar))
eq3 = Eq( fshat, (N*fs + Nbar*fsbar)/(N+Nbar))
eq4 = Eq( ACPL , (Np*fL - Npbar*fLbar)/(Np+Npbar))
eq5 = Eq( ACPpa , (Np*fpa - Npbar*fpabar)/(Np+Npbar))
eq6 = Eq( ACPpe , (Np*fpe - Npbar*fpebar)/(Np+Npbar))
eq7 = Eq( ACPS , (N*fs - Nbar*fsbar)/(N+Nbar))
eq8 = Eq( One, fpa + fpe + fL )
eq9 = Eq( Np, N*(1-fs))
eq10 = Eq(Npbar,Nbar*(1-fsbar))

#eqsetC = [eq1,eq2, eq4,eq5,eq3,eq7]
#rotC = solve(eqsetC, [fL, fLbar,fpa,fpabar,fs,fsbar])
eqsetC = [eq1,eq2, eq4,eq5,eq3,eq7,eq9]
rotC = solve(eqsetC, [fL, fLbar,fpa,fpabar,fs,fsbar,ACPS])
