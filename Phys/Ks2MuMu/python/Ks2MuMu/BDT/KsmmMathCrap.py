from ROOT import *
from array import array as afC
from SomeUtils.alyabar import *
from pdb import set_trace

def ratioBinomial(a,b, sa = -1, sb=-1):
    if sa < 0: sa = sqrt(a)
    if sb < 0: sb = sqrt(b)
    print a, b
    if a>b: 
        a=b 
        print "NUMERATOR LARGER THAN DENOMINATOR"
    if (b*a)!= 0: return a*1./b, sqrt((a*1./b)*(1-(a*1./b))/b)     #( (sa*1./a)**2 + (sb*1./b)**2)*a*1./b
    return 0,0

def ratio(a,b, sa = -1, sb=-1):
    if sa < 0: sa = sqrt(a)
    if sb < 0: sb = sqrt(b)
    #print a, b
    if (b*a)!= 0: return a*1./b,  sqrt( (sa*1./a)**2 + (sb*1./b)**2)*a*1./b 
    return 0,0


def hratio(a,b,Binomial):
    h = a.Clone()
    for i in range(a.GetNbinsX()):
        x = a.GetBinContent(i+1)
        y = b.GetBinContent(i+1)
        print 'x/y', x , y
        if Binomial==1:
            r,sr = ratioBinomial(x,y)
        elif Binomial==0:
            r,sr = ratio(x,y)
        else:
            raise RuntimeError('define error in ratio [1: Binomial, 0: Standard]')
        h.SetBinContent(i+1, r)
        h.SetBinError(i+1, sr)
    return h

def hratio2(a,b,Binomial):
    h = a.Clone()
    for i in range(a.GetNbinsX()):
        for j in range(a.GetNbinsY()):
            x = a.GetBinContent(i+1,j+1)
            y = b.GetBinContent(i+1,j+1)
            if Binomial==1:
                r,sr = ratioBinomial(x,y,a.GetBinError(i+1,j+1),b.GetBinError(i+1,j+1)) 
            elif Binomial==0:
                r,sr = ratio(x,y,a.GetBinError(i+1,j+1),b.GetBinError(i+1,j+1))
            else:
                raise RuntimeError('define error in ratio [1: Binomial, 0: Standard]')
            h.SetBinContent(i+1,j+1, r)
            h.SetBinError(i+1,j+1, sr)
    return h

#FIX THE ERRORS
def hNratio(a,N,Binomial):
    h = a.Clone()
    for i in range(a.GetNbinsX()):
        for j in range(a.GetNbinsY()):
            x = a.GetBinContent(i+1,j+1)
            if Binomial==1:
                r,sr = ratioBinomial(x,N,a.GetBinError(i+1,j+1),1)
            elif Binomial==0:
                r,sr = ratio(x,N,a.GetBinError(i+1,j+1),1)
            else:
                raise RuntimeError('define error in ratio [1: Binomial, 0: Standard]')
            h.SetBinContent(i+1,j+1, r)
            h.SetBinError(i+1,j+1, sr)
    return h

def product(x,y, sx=-1, sy=-1):
    r = x*y
    if sx < 0 :
        print "sqrt"
        sx = sqrt(x)
    if sy < 0 :
        print "sqrt"
        sy = sqrt(y)
    if not x:
        #print "warning"
        x = 1
    if not y:
        #print "warning"
        y = 1
            
    sr = sqrt( (sx*1./x)**2 + (sy*1./y)**2)*r
    return r,sr

def product2(a,b):
    #set_trace()
    h = a.Clone()
    for i in range(a.GetNbinsX()):
        for j in range(a.GetNbinsY()):
            x = a.GetBinContent(i+1,j+1)
            y = b.GetBinContent(i+1,j+1)
            r,sr = product(x,y, a.GetBinError(i+1,j+1),b.GetBinError(i+1,j+1))
            h.SetBinContent(i+1,j+1, r)
            h.SetBinError(i+1,j+1, sr)
    return h


def rec_product2(*args):
    if len(args) == 0:
        raise ValueError('there are no histos!!!')
    elif len(args) == 1:
        return args[0]
    elif len(args) == 2:
        return product2(args[0], args[1])
    else:
        return product2(rec_product2(*args[:-1]), args[-1])


def sumHisto(h):
    N, sN = 0, 0
    for i in range(h.GetNbinsX()):
        for j in range(h.GetNbinsY()):
            N+= h.GetBinContent(i+1,j+1)
            sN += h.GetBinError(i+1,j+1)**2
    return N, sqrt(sN )
