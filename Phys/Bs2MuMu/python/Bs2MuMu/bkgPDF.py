from math import *
from ROOT import TMath
erf = TMath.Erf
ln = log
_spi = sqrt(pi/2)
_s2i = 1./sqrt(2)

def Cut05eff(a,b,sa,sb):
    #Stright line Fit from B hh in MSR
    #   pdf = 1/(a+b/2) ( a + b G)
    r38 = 3./8
    #cte0 = (0.5*a + r38*b)
    cte0 = 1./(a + 0.5*b)
    
    eff = cte0*(0.5*a + r38*b)
    t1 = 0.5*cte0 - cte0*eff
    t2 = r38*cte0 - 0.5*cte0*eff
    return eff, sqrt(t1*t1*sa*sa + t2*t2*sb*sb)
    

class massDescriptor:
    def __init__(self,a,b,sa = 0,sb = 0, MIN = 5369.6 - 600, MAX= 5369.6+600):
        self.a = a
        self.b = b
        self.sa = sa
        self.sb = sb
        
        self.C1 = MAX-MIN
        self.C2 = .5*(MAX**2-MIN**2)
        self.cte0 = 1./(a*self.C1 + b*self.C2)
    def fractionInRange(self,x1,x2):
        g1 = min(x1,x2)
        g2 = max(x1,x2)
        a = self.a
        b = self.b
        sa = self.sa
        sb = self.sb
        C1 = self.C1
        C2  = self.C2
        cte0 = self.cte0
        C3 = g2 - g1
        C4 = .5*(g2*g2-g1*g1)
        f = cte0 * (a*C3 + b*C4)
        cte0_f = cte0*f
        t1 = C3*cte0 - cte0_f*C1
        t2 = C4*cte0 - cte0_f*C2

        return f, sqrt(t1*t1*sa*sa + t2*t2*sb*sb)
    def __call__(self, x1, x2):
        return self.fractionInRange(x1,x2)
        
class massDescriptorExpo:
    def __init__(self,b,sb=0, MIN = 5369.6 - 600, MAX= 5369.6+600):
        self.b = b
        self.sb = sb
        ### n ~ a*exp(b*m)
        self.MAX = MAX
        self.MIN = MIN
        self.C1 = exp(b*MAX)
        self.C2 = exp(b*MIN)
        self.cte0 = 1./(self.C1-self.C2)
    def fractionInRange(self,x1,x2):
        g1 = min(x1,x2)
        g2 = max(x1,x2)
       
        b = self.b
        sb = self.sb
        C1 = self.C1
        C2 = self.C2
        cte0 = self.cte0
        C3 = exp(b*g2)
        C4 = exp(b*g1)
        
        f = cte0 * (C3-C4)
        sf = cte0*(g2*C3-g1*C4)-cte0*f*(self.MAX*self.C1-self.MIN*self.C2)

        return f, sf
    def __call__(self, x1, x2):
        return self.fractionInRange(x1,x2)
        

## class pidDescriptor:
##     def __init__(self):
##         pass
##     def fractionInRange(self,x1,x2):
##         return x2 - x1, 0
##     def __call__(self, x1, x2):
##         return self.fractionInRange(x1,x2)
        
