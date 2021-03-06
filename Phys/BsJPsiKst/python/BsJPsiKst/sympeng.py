## Diego Martinez Santos, 

from penguin_inputs import *
from sympy import Symbol, solve, nsolve, mpmath
from sympy import sin as Sin, cos as Cos, sqrt as Sqrt, atan as Atan
from math import sin, cos, pi

mpmath.mp.dps = 15
from math import sin, cos, pi 

af = Symbol("af")   ## amplitude of the penguins
thf = Symbol("thf")  ## phase of the penguin
 
st, ct =  Sin(thf), Cos(thf)

sg, cg = sin(gamma), cos(gamma)

Hf = (1 - 2*af*ct*cg + af*af)*1./(1+2*eps*af*ct*cg+eps*eps*af*af)
Af = (2*af*st*sg)*1./(1-2*af*ct*cg+af*af)
tg = (2*eps*af*ct*sg+eps*eps*af*af*sin(2*gamma))*1./(1+2*eps*af*ct*cg+eps*eps*af*af*cos(2*gamma))
dphi = Atan(tg)

### Search for solutions

def Penguins(Hf_exp, Af_exp, guessAmpls = [0.01,0.2, 0.4,0.6,0.8], guessPhases = [0.,pi/2,pi,3*pi/2,2*pi]):
    dphis = []
    for amplitude in guessAmpls:
        for phase in guessPhases:
            solutions = nsolve( (Hf-Hf_exp, Af - Af_exp),(af,thf),(amplitude,phase))
            if solutions[0] < 0: continue
            if abs(solutions[1]) > 7 : continue
            dphi_ = dphi.subs( [ (af, solutions[0]), (thf, solutions[1])])
            if dphi_ in dphis: continue
            else: dphis.append(dphi_)
    return dphis
Kstpol_f = [0.484, 0.181, 1- .484-.181]
Phipol_f =  [0.5241, 1- 0.5241-.2504 , 0.2504]
BR_r = 3.61e-02
Hf_exp = 3*[0.]
for i in range(3): Hf_exp[i] = BR_r*Kstpol_f[i]/Phipol_f[i] * 1./eps #for i in range(3)

ACP_exp = [0.,0.,0.]

#s = Penguins(1.996,-0.022)

def doPenguins(i) : print Penguins(Hf_exp[i], ACP_exp[i])
