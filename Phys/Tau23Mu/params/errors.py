from math import *
import random

# 
# Class to deal with measurement (value, error)
#

def val(par): return par.get_value()
def err(par): return par.get_error()
def errpos(par): return par.get_error_up()
def errneg(par): return par.get_error_down()
def stat(par): return par.error[0]
def sys(par): return par.error[1]
def ran(par): return (par.random()).get_value()

def _error_check_len(a,b):
    if (len(a.error)!= len(b.error)):
        print " measurements with different number of errors",a,b
        raise ArithmeticError

def _error_make_list(error):
    if (type(error) != list): error = [error]
    return map(float,error)

class EVal:

    def __init__(self,value,error):
        self.value = float(value)
        self.error = _error_make_list(error)

    def __str__(self):
        s = str(self.value)+' +- '+str(self.error)
        if (len(self.error)==1):
            s = str(self.value)+' +- '+str(self.error[0])
        return s

    def __repr__(self):
        return str(self)

    def get_value(self):
        return self.value

    def get_error(self):
        v = self.compress_errors()
        return v.error[0]

    def add_error(self,err):
        self.error.append(err)

    def add_relative_error(self,rel):
        self.error.append(rel*self.value)


    def __abs__(self):
        v = abs(self.value)
        return EVal(v,self.error)

    def __add__(self,eval):
        if (not _is(eval,EVal)):
            return EVal( eval+self.get_value(), self.error)
        _error_check_len(self,eval)
        v = self.value + eval.value 
        def eadd(e1,e2): return sqrt(e1*e1+e2*e2)
        error = map(eadd,self.error,eval.error)
        return EVal(v,error)

    def __sub__(self,eval):
        if (not _is(eval,EVal)):
            return EVal( self.get_value()-eval, self.error)
        _error_check_len(self,eval)
        v = self.value - eval.value 
        def eadd(e1,e2): return sqrt(e1*e1+e2*e2)
        error = map(eadd,self.error,eval.error)
        return EVal(v,error)

    def __div__(self,eval):
        if (not _is(eval,EVal)):
            return EVal( self.get_value()/eval, map(lambda x : x/eval, self.error))
        if (not _is(eval,EVal)): return eval.__div__(self)
        _error_check_len(self,eval)
        deno = eval.value
        if (deno == 0.): return EVal(0.,0.)
        r = self.value/deno
        #print ' -- ', self, eval
        #print 'r', r
        #print 'deno', deno
        def ediv(e1,e2):
            #print 'deno', deno
            #print (1/deno)*sqrt(e1*e1+r*r*e2*e2)
            return (1/deno)*sqrt(e1*e1+r*r*e2*e2)
        
        error = map(ediv,self.error,eval.error)
        return EVal(r,error)

    def __mul__(self,eval):
        if (not _is(eval,EVal)):
            return EVal( eval*self.get_value(), map(lambda x: eval*x, self.error))
        _error_check_len(self,eval)
        f1 = self.value
        f2 = eval.value
        f = f1*f2
        def eprod(e1,e2): return sqrt(f2*f2*e1*e1+f1*f1*e2*e2)
        error = map(eprod,self.error,eval.error)
        return EVal(f,error)

    def random(self,compress = False):
        ee = self.error[0]
        if (compress):
            ee = self.compress_errors().error[0]
        v = EVal(random.gauss(self.value,ee),ee)
        return v

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

def _is(val,type):
    return (val.__class__ == type)

def _get_evalasym(val):
    if (_is(val,EValAsym)): return val
    val = EValAsym(val.value,val.error,val.error)
    return val

def _make_evalasym(evals):
    if (len(evals)!=2):
        print ' not able to make asysmetric measurement ',len(evals)
    return EValAsym(evals[0].value,evals[0].error,evals[1].error)

class EValAsym():

    def __init__(self,value,erup,erdown): 
        errs = map(_error_make_list,[erup,erdown])
        self.evals = map(lambda er: EVal(value,er),[erup,erdown])

    def get_value(self):
        return self.evals[0].get_value()

    def get_error_up(self):
        return self.evals[0].get_error()

    def get_error_down(self):
        return self.evals[1].get_error()

    def __str__(self):
        s = str(self.evals[0].value)+' + '
        if (len(self.evals[0].error) ==1): s = s + str(self.evals[0].error[0])
        else: s = s+str(self.evals[0].error)
        s = s + ' - '
        if (len(self.evals[1].error) ==1): s = s + str(self.evals[1].error[0])
        else: s = s+str(self.evals[1].error)
        return s

    def __repr__(self):
        return str(self)

    def __add__(self,eval):
        asval = _get_evalasym(eval)
        evals = map(lambda x,y: x+y,self.evals,asval.evals)
        return _make_evalasym(evals)

    def __radd__(self,eval):
        asval = _get_evalasym(eval)
        evals = map(lambda x,y: x+y,self.evals,asval.evals)
        return _make_evalasym(evals)

    def __sub__(self,eval):
        asval = _get_evalasym(eval)
        evals = map(lambda x,y: x-y,self.evals,asval.evals)
        return _make_evalasym(evals)

    def __rsub__(self,eval):
        asval = _get_evalasym(eval)
        evals = map(lambda x,y: x-y,self.evals,asval.evals)
        return _make_evalasym(evals)

    def __div__(self,eval):
        asval = _get_evalasym(eval)
        evals = map(lambda x,y: x/y,self.evals,asval.evals)
        return _make_evalasym(evals)

    def __rdiv__(self,eval):
        asval = _get_evalasym(eval)
        evals = map(lambda x,y: x/y,self.evals,asval.evals)
        return _make_evalasym(evals)

    def __mul__(self,eval):
        asval = _get_evalasym(eval)
        evals = map(lambda x,y: x*y,self.evals,asval.evals)
        return _make_evalasym(evals)

    def __rmul__(self,eval):
        asval = _get_evalasym(eval)
        evals = map(lambda x,y: x*y,self.evals,asval.evals)
        return _make_evalasym(evals)

    def random(self):
        i = int(random.uniform(0.,1.)>=0.5)
        xx = abs(random.gauss(0.,self.evals[i].get_error()))
        value = self.get_value() 
        if (i==0): value = value + xx
        else: value = value - xx
        return EValAsym(value,self.evals[0].error,self.evals[1].error)

    def scale(self,norma=1):
        evals = map(lambda x: x.scale(norma),self.evals)
        return _make_evalasym(evals)
                  
    def invert(self):
        evals = map(lambda x: x.invert(),self.evals)
        return _make_evalasym(evals)

    def compress_errors(self):
        evals = map(lambda x: x.compress_errors(),self.evals)
        return _make_evalasym(evals)

    def compress_sys_errors(self):
        evals = map(lambda x: x.compress_sys_errors(),self.evals)
        return _make_evalasym(evals)

    def add_error(self,errs):
        evals = map(lambda ev,er:ev.add_error(er),self.evals,errs)
        return _make_evalasym(evals)

    def add_relative_error(self,rel):
        evals = map(lambda x: x.add_relative_error(rel),self.evals)
        return _make_evalasym(evals)

#--- operations

def weight(x):
    vals = map(lambda xi: xi.value, x)
    ers = map(lambda xi: err(xi),x)
    if (len(filter(lambda er: er<=0.,ers))>0): return EVal(0.,0.)
    iers = map(lambda xi: 1./err(xi),x)
    sg2 = 1./sum(map(lambda ei:ei*ei,iers))
    ww = map(lambda ier:ier*ier*sg2,iers)
    xval = sum(map(lambda x,y:x*y,ww,vals))
    return EVal(xval,sqrt(sg2))

def check(a = EVal(2.,0.2),b = EVal(3.,0.3)):
    print ' a ',a,' 1/a ',a.invert()
    print ' a ',a,' 5*a ',a.scale(5.)
    print ' a ',a,' b ',b,'a+b',a+b
    print ' a ',a,' b ',b,'a-b',a-b
    print ' a ',a,' b ',b,'a*b',a*b
    print ' a ',a,' b ',b,'a/b',a/b

def checkAsys(a = EValAsym(1.,2.,1.),b = EVal(2.,1.)):
        print ' a ',a,' 1/a ',a.invert()
        print ' a ',a,' 5*a ',a.scale(5.)
        print ' a ',a,' b ',b,'a+b',a+b
        print ' a ',a,' b ',b,'a-b',a-b
        print ' a ',a,' b ',b,'a*b',a*b
        print ' a ',a,' b ',b,'a/b',a/b


def checkAsysSyt(a = EValAsym(1.,2.,1.),b = EVal(2.,[1.,5.])):
        print ' a ',a,' 1/a ',a.invert()
        print ' a ',a,' 5*a ',a.scale(5.)
        print ' a ',a,' b ',b,'a+b',a+b
        print ' a ',a,' b ',b,'a-b',a-b
        print ' a ',a,' b ',b,'a*b',a*b
        print ' a ',a,' b ',b,'a/b',a/b
