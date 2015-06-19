from math import *

MD ={"mu": 105.658, "tau": 1777, "B0s":5369.6, "B0d":5279.0, "k":493.68}
alpha = 1./128 ## Alpha(Mz)
alphaS = 0.1176 ## AlphaS(Mz)
pi = acos(-1)
sin2TW = 0.2397
Gf = 1.16637e-11 ## MeV -2
VVs = 0.9991*0.042
mt_ = 163800.
muScale = mt_
mW = 80493. #MeV
C10 = -4.6242
fBs = 240 #MeV
gTot = (1.055e-34)/(1.466e-012 * 1.602e-19)*1.e-06 ## MeV ## gTot = h_Bar/Tau

def gm2(x,r):
    p1 = sqrt(1-4*r/(1-x))
    return (2+ (4*r-2)/x - x) *log ((1+p1)/(1-p1))+2/x*(1-x)*p1

def Igm2(delta, r, tope = None,dx = .00001):
    if not tope: tope = 1-4*r
    np = int((tope-delta)/dx) + 1
    I = 0
    for i in range(np):
        x = delta + i*dx
        if x > tope: break
        I += gm2(x,r)*dx
    return I

def fsrfraction(delta, tope = None, dx = .00001, l = "mu", b = "B0s"):
    ml = MD[l]
    mB = MD[b]
    r = (ml/mB)**2
    #sin4 = sin2TW**2
    cte = alpha/(pi)
    um4r = 1-4*r
    #if not tope: tope = um4r
    return -cte*Igm2(delta,r,tope,dx)#/sqrt(um4r)  ### Este termino deberia aparecer ...

def br2(delta, tope = None,l="mu", b = "B0s"):
    c =((alpha*Gf*VVs*fBs*C10/(2*sqrt(2)*pi))**2)*(alpha/(2*pi)**3)*(MD[b]**3)*pi*(-4)
    r = (MD[l]/MD[b])**2
    print "BR ll segun Geng:" , ((alpha*Gf*fBs*VVs*C10)**2/(16*pi**3)*r*MD[b]**3)/gTot
    CA = Y(mt_)
    print "BR ll segun Buras:" , ((alpha*Gf*fBs*VVs*CA)**2/(16*pi**3)*r*MD[b]**3)*sqrt(1-4*r)/(gTot*(sin2TW**2))
    return c*r*Igm2(delta,r,tope)/gTot

#print 
    #return c*
def gplusminus(E, h = "k", b = "B0s"):
    eps = MD[h]/MD[b]
    logeps = log(eps)
    #print logeps
    return 1.0 - alpha/pi*((2*logeps+1)*log(4*E*E/(MD[b]*MD[b]))-4*logeps+pi*pi/3+1)   

def L2(x, dx = 0.0001):
    tope = 1-x
    np = int((tope-1)/dx) + 1
    I = -1*dx ## lim (x-->1) log(x)/(1-x)
    for i in range(np):
        x = 1 + (i+1)*dx
        if x > tope: break
        I += log(x)/(1-x)*dx
    return I
    
    
def Y(mt, debug = False):
    x = (mt/mW)**2
    x2 = x*x
    x3 = x2*x
    x4 = x3*x
    logx = log(x)
    umx = 1-x
    umx2 = umx*umx
    umx3 = umx2*umx
    lnMu = 2*log(muScale/mW)
    
    t1 =(10*x+10*x2+4*x3)/(3*umx2) - (2*x-8*x2-x3-x4)*logx/umx3
    t2 = (2*x - 14*x2+x3-x4)*logx*logx/(2*umx3) + (2*x+x3)*L2(1-x)/umx2
    t3 = x*((4-x)/umx+3*x*logx/umx2)
    t4 = (-1/umx + (4-x)/umx2 + 3*(logx+1)/umx2 + 6*x*logx/umx3)

    Y0 = t3/8.
    Y1 = t1 + t2 + lnMu*(t3 + x**2*t4)
    if debug:
        print "In practice Y1 does ~anything, you can use Y = 1.012*Y0 ..."
        print Y0, Y1
    return Y0 + alphaS/(4*pi)*Y1
    
