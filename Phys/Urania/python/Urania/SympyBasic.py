### Define some usual sympy stuff
## from sympy import * would overwrite functions like  sin, cos or sqrt, which
# you may want to take from math , numpy, scipy ...

from sympy import sin as Sin, cos as Cos, sqrt as Sqrt, exp as Exp, pi as Pi, log as Log, sinh as Sinh, cosh as Cosh
from sympy import Symbol, I, re, im, simplify, integrate, Pow, Integral, Abs, Matrix, eye as Eye
from sympy import latex
from itertools import permutations
from sympy.core.singleton import SingletonRegistry
from Mathematica import *
# from sympy.parsing.mathematica import mathematica
import os
UraniaSR = SingletonRegistry() ### instantiate the singleton registry
One = UraniaSR(1)

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
def math_limit(func, *args):

    mp = MathematicaPrinter()
    args_math = ""
    
    for arg in args:
        var = arg[0]
        var_lim = arg[1]
        args_math += mp(var)+"->"+mp(var_lim)

    func_math = mp(func)
    
    ftmo = open("int_tmp.nb","w")
    ftmo.write("Put[FullSimplify[Limit["+func_math+","+args_math+"]],\"int_tmp.txt\"]\n")
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

    if "Limit" in line:
        print "Mathematica failed calculating limit. Returning zero."
        return "zero"

#     os.remove("int_tmp.nb")
#     os.remove("int_tmp.txt")
    line = line.replace("/ ", "/")
    return MathematicaToSympy(line)

class USymbol(Symbol):

    def __init__(self, name, texname,commutative=True, **assumptions):
        Symbol.__init__(self, name, commutative=True, **assumptions)
        self.first_name = name
        self.texname = texname
    def useLatexName(self): self.name = self.texname
    def useFirstName(self): self.name = self.first_name

class UMatrix(Matrix):
    def __init__(self,*args):
        Matrix.__init__(self,*args)

    def RowMultiply(self, i, no):
        for j in range(self.cols):self[i,j]*=no
    def RowAdd(self, i, l):
        #for j in range(self.cols):self[i,j] = simplify(self[i,j]+ l[j])
        for j in range(self.cols):self[i,j]+= l[j]
    def RowSelfAdd(self,i1,i2, sf = 1):
        l = self[i2*self.cols:(i2+1)*self.cols]
        if sf !=1:
            for k in range(len(l)):
                l[k]*=sf
        self.RowAdd(i1,l)
    def SubstituteRow(self,i,l):
        for j in range(self.cols):self[i,j] = l[j]
    
    def SwapRows(self,i1,i2):
        l1, l2 = self.cols*[0.], self.cols*[0.]
        for j in range(self.cols):
            l1[j] = self[i1,j]
            l2[j] = self[i2,j]
        self.SubstituteRow(i1,l2)
        self.SubstituteRow(i2,l1)

    def DoSwaps(self,i):
        #if self[i,i] == 0:
        for i2 in range(self.rows):
            if self[i,i2] != 0 and self[i2,i] != 0: self.SwapRows(i,i2)

    def DoTriangle2(self):
        w_bk = 0
        for xi in range(self.rows):
            i = self.rows - xi -1
            for xi2 in range(0,xi):
                 i2 = self.rows - xi2 - 1
                 self.RowSelfAdd(i, i2,-self[i,i2]*1./self[i2,i2])       
            if self[i,i] == 0:
                 w_bk =1
                 break
            self.RowMultiply(i,1./self[i,i])
        if w_bk:   
            self.DoSwaps(i)
            self.DoTriangle2()
            
    def DoTriangle1(self):
        w_bk = 0
        for i in range(self.rows):         
            for i2 in range(0,i):
                self.RowSelfAdd(i, i2,-self[i,i2]*1./self[i2,i2])       
            if self[i,i] == 0:
                w_bk =1
                break
            self.RowMultiply(i,1./self[i,i])
        if w_bk:   
            self.DoSwaps(i)
            self.DoTriangle1()
        
    def InvChickenStyle(self):
         MI = Eye(self.rows)
         zz = {}
         for i in range(self.rows):
             zz[i] = []
             for j in range(self.rows): zz[i].append(self[i,j])
             for j in range(self.rows): zz[i].append(MI[i,j])
         ZZ = UMatrix(zz.values())
         
         for i in range(self.rows):
             if ZZ[i,i] == 0: ZZ.DoSwaps(i)

         ZZ.DoTriangle1()
         ZZ.DoTriangle2()
         #return ZZ
         out = {}
         for i in range(self.rows):
             out[i] = []
             for j in range(self.cols, 2*self.cols): out[i].append(ZZ[i,j])
             
         
         return UMatrix(out.values())         

def getThing(A,thing): return simplify(A.collect(thing,evaluate = False) [thing])

from math import sqrt
def GaussErrorPropagator(expr, xi, sxi):
    s = 0
    for i in range(len(xi)):
        duo = xi[i] ## symbol, value
        s+= (sxi[i]*expr.diff(duo[0]).subs(xi))**2
    return sqrt(s)


        
    

## A = UMatrix([[1,2,3],[1,0,0],[1,1,1])
## x = {}
## for i in range(5):
##     x[i] = []
##     for j in range(5):
##         x[i].append(Symbol("x" + str(i)+str(j), real = True))
        
        
## A = UMatrix(list(x.values()))
## #C = A.InvChickenStyle()
