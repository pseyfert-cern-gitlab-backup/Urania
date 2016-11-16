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
    

class geometryDescriptor:
    def __init__(self,a,b,sa = 0,sb = 0):
        self.a = a
        self.b = b
        self.sa = sa
        self.sb = sb
    def fractionInRange(self,x1,x2):
        g1 = min(x1,x2)
        g2 = max(x1,x2)
        a = self.a
        b = self.b
        sa = self.sa
        sb = self.sb

        cte0 = 1./(a+0.5*b)
        f = cte0 * (a*(g2-g1) + 0.5*b*(g2*g2-g1*g1))

        t1 = (g2-g1)*cte0 - cte0*f
        t2 = 0.5*cte0*(g2*g2-g1*g1) - 0.5*cte0*f

        return f, sqrt(t1*t1*sa*sa + t2*t2*sb*sb)
    def __call__(self, x1, x2):
        return self.fractionInRange(x1,x2)
        
class massDescriptor:
    def __init__(self, mean, sigma, a , n = 1, s_m = 0, s_s = 0 , s_a = 0, s_n = 0,limits = [5309.6, 5429.6]):
        a = abs(a)
        self.mean = mean
        self.sigma = sigma
        self.a = a
        self.n = n
        self.s_m = s_m
        self.s_s = s_s
        self.s_a = s_a
        self.s_n = s_n
        def y(x):
            return (x - mean )/ sigma
        self.T = mean - a*sigma
        self.y = y
        self.ym = y(limits[0])
        self.yM = y(limits[1])
        er_a = erf(a*_s2i)
        def I(y):
            return _spi*(erf(y*_s2i) + er_a)
        self.I = I
        #if (-a )!= y(self.T): print "CANCER:", -a ,"!=",y(self.T)
        ia = 1./a
        if n == 1:
            def F(y):
                return -ln(abs(ia - a - y))*ia*exp(-0.5*a*a)
        else:
            print "WARNING:  Only tested for n = 1. Be careful "
            def F(x):
                return -((n*ia)**n) *exp(-0.5*a*a)/((n-1)*(n*ia-a-y)**(n-1))
        self.F = F
        #self.C = 1./(_spi*(erf(self.yM)-erf(-a)) + (F(-a) - F(self.ym)))
        
        self.C = 1./(I(self.yM) + (F(-a) - F(self.ym)))
        

    def fractionInRange(self, x1, x2):
        C = self.C
        w = "The error is Unknown. But Hoppefully small"
        if x2 < self.T:
            return C*(self.F(self.y(x2)) - self.F(self.y(x1))), w
        if x1 < self.T < x2 :
            #return C*(_spi*(erf(self.y(x2))-erf(-self.a)) + self.F(-self.a)- self.F(self.y(x1)))
            return C*(self.I(self.y(x2)) + self.F(-self.a)- self.F(self.y(x1))), w

        if x1 > self.T :
            return C*(self.I(self.y(x2)) - self.I(self.y(x1))), w
    def __call__(self, x1, x2):
        return self.fractionInRange(x1,x2)
    
class pidDescriptor:
    def __init__(self):
        pass
    def fractionInRange(self,x1,x2):
        return x2 - x1, 0
    def __call__(self, x1, x2):
        return self.fractionInRange(x1,x2)
        
