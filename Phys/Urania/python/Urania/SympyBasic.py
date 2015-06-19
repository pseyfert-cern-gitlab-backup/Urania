### Define some usual sympy stuff
## from sympy import * would overwrite functions like  sin, cos or sqrt, which
# you may want to take from math , numpy, scipy ...

from sympy import sin as Sin, cos as Cos, sqrt as Sqrt, exp as Exp, pi as Pi, log as Log
from sympy import Symbol, I, re, im, simplify, integrate, Pow, Integral, Abs
from sympy import latex
from itertools import permutations
from Mathematica import *
# from sympy.parsing.mathematica import mathematica
import os

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

    print "I'll try using Mathematica..."
    out_math = math_integrate(func, *args)
    if out_math!="zero":
        return out_math

    print "I failed miserably. Sorry"
    return out




def math_integrate(func, *args):

    mp = MathematicaPrinter()
    args_math = ""
    
    for arg in args:
        var = arg[0]
        lo = arg[1]
        hi = arg[2]
        args_math += "{"+mp(var)+","+mp(lo)+","+mp(hi)+"}"+","

    func_math = mp(func)
    
    ftmo = open("int_tmp.nb","w")
    ftmo.write("Put[Integrate["+func_math+","+args_math[:-1]+"],\"int_tmp.txt\"]\n")
    ftmo.close()

    mathematica_script("int_tmp.nb");

    if not os.path.isfile("int_tmp.txt"):
        print "Mathematica failed executing. Returning zero"
        return "zero"
    
    ftin = open("int_tmp.txt","r")
    line = ""
    while True:
        line_ = ftin.readline()
        if not line_: break
        line += line_[:-1]

    if not line:
        print "Something weird happened... Returning zero"
        return "zero"

    if "Integrate" in line:
        print "Mathematica failed calculating integral. Returning zero."
        return "zero"

#     os.remove("int_tmp.nb")
#     os.remove("int_tmp.txt")

    return MathematicaToSympy(line)
