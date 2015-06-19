from math import *

# 
# Class to deal with measurement (value, error)
#

def val(par): return par.value
def err(par): return par.error[0]
def sys(par): return par.error[1]

class EVal:

    def __init__(self,value,error):
        self.value = value
        if (type(error) != list): error = [error]
        self.error = error

    def __str__(self):
        s = str(self.value)+' +- '+str(self.error)
        if (len(self.error)==1):
            s = str(self.value)+' +- '+str(self.error[0])
        return s

    def get_error(self):
        v = self.compress_errors()
        return v.error[0]

    def add_error(self,err):
        self.error.append(err)

    def add_relative_error(self,rel):
        self.error.append(rel*self.value)

    def __add__(self,eval):
        v = self.value + eval.value 
        def eadd(e1,e2): return sqrt(e1*e1+e2*e2)
        error = map(eadd,self.error,eval.error)
        return EVal(v,error)

    def __sub__(self,eval):
        v = self.value - eval.value 
        def eadd(e1,e2): return sqrt(e1*e1+e2*e2)
        error = map(eadd,self.error,eval.error)
        return EVal(v,error)

    def __div__(self,eval):
        deno = eval.value
        r = self.value/eval.value 
        def ediv(e1,e2): return (1/deno)*sqrt(e1*e1+r*r*e2*e2)
        error = map(ediv,self.error,eval.error)
        return EVal(r,error)

    def __mul__(self,eval):
        f1 = self.value
        f2 = eval.value
        f = f1*f2
        def eprod(e1,e2): return sqrt(f2*f2*e1*e1+f1*f1*e2*e2)
        error = map(eprod,self.error,eval.error)
        return EVal(f,error)

    def compress_errors(self):
        v = self.value
        e2 = map(lambda ie: ie*ie,self.error)
        e = sqrt(sum(e2))
        return EVal(v,e)

    def compress_sys_errors(self):
        v = self.value
        e2 = map(lambda ie: ie*ie,self.error[1:])
        e = sqrt(sum(e2))
        return EVal(v,[self.error[0],e])
        
    def scale(self,norma=1):
        v = self.value*norma
        e = map(lambda ie: norma*ie,self.error)
        return EVal(v,e)
                  
    def invert(self):
        y = 1./self.value
        def einvert(ei): return ei*y*y
        e = map(einvert,self.error)
        return EVal(y,e)        

def check(a = EVal(2.,0.2),b = EVal(3.,0.3)):
    print ' a ',a,' 1/a ',a.invert()
    print ' a ',a,' 5*a ',a.scale(5.)
    print ' a ',a,' b ',b,'a+b',a+b
    print ' a ',a,' b ',b,'a-b',a-b
    print ' a ',a,' b ',b,'a*b',a*b
    print ' a ',a,' b ',b,'a/b',a/b
