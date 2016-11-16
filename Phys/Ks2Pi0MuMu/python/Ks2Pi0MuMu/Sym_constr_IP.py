from Urania.SympyBasic import *
from sympy import Derivative
from sympy import Eq, solve
from SomeUtils.alyabar import *

### Pi0 three -momenta
pi0x = USymbol("pi0x", "p^{\\pi^0}_x", real = True)
pi0y = USymbol("pi0y", "p^{\\pi^0}_y", real = True)
pi0z = USymbol("pi0z", "p^{\\pi^0}_z", positive = True)

## |p_{\pi0}|
ppi0 = USymbol("ppi0","p^{\\pi^0}", positive = True)

pmmx = USymbol("pimmx", "p^{\\mu\\mu}_x", real = True)
pmmy = USymbol("pimmy", "p^{\\mu\\mu}_y", real = True)
pmmz = USymbol("pimmz", "p^{\\mu\\mu}_z", positive = True)

mpi0 = USymbol("mpi0", "m_{\\pi^0}", positive = True)
Mmumu = USymbol("Mmumu", "m_{\\mu\\mu}", positive = True)
mK0 = USymbol("mK0", "m_{\\K^0}", positive = True)

## Decay vertex position relative to the PV
x = Symbol("x", real = True)
y = Symbol("y", real = True)
z = Symbol("z", positive = True)

r = vector(x, y, z) 
pi0 = vector(pi0x,pi0y,pi0z)
pmu = vector(pmmx,pmmy,pmmz)
BigPi = vcross(pi0,pmu) ### Vector defining the plane of the decay

dp = vdot(r,BigPi)

#eq1 = Eq(0, dp)
#eq2 = Eq(ppi0**2, vdot(pi0,pi0))
#eq3 = Eq(mK0**2, mpi0**2 + Mmumu**2 -2*vdot(pi0,pmu) +2*Sqrt((mpi0**2 + ppi0**2)*(Mmumu**2 + vdot(pmu,pmu))))
#BREAK
#Change the equations so that they are in a format suitable for numeric solving:

eq1 = dp
eq2 = vdot(pi0,pi0) - ppi0**2
eq3 = mpi0**2 + Mmumu**2 -2*vdot(pi0,pmu) +2*Sqrt((mpi0**2 + ppi0**2)*(Mmumu**2 + vdot(pmu,pmu))) - mK0**2
eqset = [eq1,eq2,eq3]
#def do(ppi0val, Mmumuval, mpi0val = PDG.pi0.mass, mK0val = PDG.K0.mass)
#rot = solve(eqset, [pi0x,pi0y,pi0z])


         

