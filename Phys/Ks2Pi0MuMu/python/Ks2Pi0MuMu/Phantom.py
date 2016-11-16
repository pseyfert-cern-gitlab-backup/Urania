from Urania.SympyBasic import *
from Urania import PDG
from SomeUtils.alyabar import * 

### I start with the components in the plane transverse to the flight
## the one we use for constraining the mss

pmmx = USymbol("pmmx", "p^{\\mu\\mu}_x", real = True)
pmmy = USymbol("pmmy", "p^{\\mu\\mu}_y", real = True)
pmmz = USymbol("pmmz", "p^{\\mu\\mu}_z", positive = True)
Mmumu = USymbol("Mmumu", "M_{\\mu\\mu}", positive = True)
Mpi0 = USymbol("mpi0", "M_{\pi^0}", positive = True)


#pi0x = USymbol("pi0x", "p^{\\pi^0}_x", real = True) ### x, and y will be fixed from the dimuon
#pi0y = USymbol("pi0y", "p^{\\pi^0}_y", real = True)

pi0z = USymbol("pi0z", "p^{\\pi^0}_z", positive = True)

pdm = vector(pmmx,pmmy,pmmz)
ppi0 = vector(-pmmx,-pmmy,pi0z)

Mas2 = Mmumu**2 +  Mpi0**2 +2*(Sqrt( ( vdot(pdm,pdm) + Mmumu**2) * ( vdot(ppi0,ppi0)+ Mpi0**2) ) - vdot(ppi0,pdm))

dependency = Mas2.diff(pi0z)


### Let's see how does this behave. To simplify a bit, lets say px ~py since both are of the same order
## and subdominant w.r.t pz

dep = dependency.subs(pmmy,pmmx)
from sympy import pprint
pprint(dep)

