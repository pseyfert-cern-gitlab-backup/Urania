from math import *

def get_q(M,m1,m2):
    M2 = M*M
    m12 = m1*m1
    m22 = m2*m2

    q2 = .25*( M2*M2 - 2*M2*(m12+m22) +(m12*m12+m22*m22)-2*m12*m22) /M2

    return sqrt(q2)

def f1(M,m1=139.57018,m2=493.677,M0=895.94, d = 3e-03):
    q = get_q(M,m1,m2)
    q0 = get_q(M0,m1,m2)
    
    z = (q*d)**2
    z0 = (q0*d)**2

    return sqrt((1+z0)/(1+z))

def f2(M,m1=139.57018,m2=493.677,M0=895.94, d = 1.5e-03):
    q = get_q(M,m1,m2)
    q0 = get_q(M0,m1,m2)
    
    z = (q*d)**2
    z0 = (q0*d)**2

    return sqrt(((z0-3)**2 + 9*z0) / ((z-3)**2 + 9*z))

from ROOT import *
gROOT.ProcessLine(".x $SOMEMASSMODELSROOT/src/BWtools.C++")
print sqrt(Blatt_Weisskopf_fM(8000, 1))
print f1(8000)
