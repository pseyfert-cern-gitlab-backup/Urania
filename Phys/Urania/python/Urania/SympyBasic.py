### Define some usual sympy stuff
## from sympy import * would overwrite functions like  sin, cos or sqrt, which
# you may want to take from math , numpy, scipy ...

from sympy import sin as Sin, cos as Cos, sqrt as Sqrt, exp as Exp, pi as Pi, log as Log
from sympy import Symbol, I, re, im, simplify, integrate, Pow, Integral, Abs
from sympy import latex
from itertools import permutations

def didIntegralWork(integral): return not ("ntegral" in str(integral.__class__))
def iter_integrate(func, *args):
    out = integrate(func, *args)
    if didIntegralWork(out): return out
    
    print "Warning: I don't know how to do it as it is (sorry)."
    L0 = list(permutations(list(args)))
    if len(L0)<2:
        print "Don't know what else to do"
        return out 
    print "I'll try permutations of the different dimensions"
    for trial in L0[1:]:
        out = integrate(func,*trial)
        if didIntegralWork(out):
            print "I made it, I think."
            return out
    print "I failed miserably. Sorry"
    return out



