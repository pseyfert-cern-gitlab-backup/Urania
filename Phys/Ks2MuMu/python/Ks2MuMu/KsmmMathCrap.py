from ROOT import *
from array import array as afC
from SomeUtils.alyabar import *

def ratio(a,b, sa = -1, sb=-1):
    if sa < 0: sa = sqrt(a)
    if sb < 0: sb = sqrt(b)
    if (b*a)!= 0: return a*1./b, sqrt( (sa*1./a)**2 + (sb*1./b)**2)*a*1./b
    return 0,0

def hratio(a,b):
    h = a.Clone()
    for i in range(a.GetNbinsX()):
        x = a.GetBinContent(i+1)
        y = b.GetBinContent(i+1)
        r,sr = ratio(x,y)
        h.SetBinContent(i+1, r)
        h.SetBinError(i+1, sr)
    return h

def hratio2(a,b):
    h = a.Clone()
    for i in range(a.GetNbinsX()):
        for j in range(a.GetNbinsY()):
            x = a.GetBinContent(i+1,j+1)
            y = b.GetBinContent(i+1,j+1)
            r,sr = ratio(x,y,a.GetBinError(i+1,j+1),b.GetBinError(i+1,j+1))
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
        print "warning"
        x = 1
    if not y:
        print "warning"
        y = 1
        
    
    sr = sqrt( (sx*1./x)**2 + (sy*1./y)**2)*r
    return r,sr

def product2(a,b):
    h = a.Clone()
    for i in range(a.GetNbinsX()):
        for j in range(a.GetNbinsY()):
            x = a.GetBinContent(i+1,j+1)
            y = b.GetBinContent(i+1,j+1)
            r,sr = product(x,y, a.GetBinError(i+1,j+1),b.GetBinError(i+1,j+1))
            h.SetBinContent(i+1,j+1, r)
            h.SetBinError(i+1,j+1, sr)
    return h

def sumHisto(h):
    N, sN = 0, 0
    for i in range(h.GetNbinsX()):
        for j in range(h.GetNbinsY()):
            N+= h.GetBinContent(i+1,j+1)
            sN += h.GetBinError(i+1,j+1)**2
    return N, sqrt(sN )
