from math import *
from alyabar import *
from random import random

def pointingNuMu(rSV, p1, p2):
    p = p1 + p2
    vd = vunit(rSV)
    pok = vdot(vd,p)
    P = vmod(p)
    pmiss = sqrt(P*P-pok*pok)
    pok1 = vdot(vd,p1)
    P1 = vmod(p1)
    pmiss1 = sqrt(P1*P1- pok1*pok1)
    pok2 = vdot(vd,p2)
    P2 = vmod(p2)
    pmiss2 = sqrt(P2*P2-pok2*pok2)

    return pmiss/(pmiss +pmiss1 + pmiss2), pmiss1/(pmiss + pmiss1 + pmiss2)
    

def pointingPhi(rSV,p1,p2):
    vd = vunit(rSV)
    if vd[0] == 0 and vd[1] == 0 :
        vp1 = vector(1.,0.,0.)
    elif vd[0] == 0 and vd[2] == 0 :
        vp1 = vector(1.,0.,0.)
    elif vd[2] == 0 and vd[1] == 0 :
        vp1 = vector(0.,1.,0.)
    else:
        vp1 = vector(-vd[1],vd[0],0.)
    vp1 = vunit(vp1)
    vp2 = vcross(vd,vp1)
    vp2 = vunit(vp2)

    p1t = vector(0.,vdot(p1,vp1),vdot(p1,vp2))
    p2t = vector(0.,vdot(p2,vp1),vdot(p2,vp2))

    print p1t
    print p2t
    return ACO(p1t,p2t)
def componenteZ(v):
    return v[2]

def suma(a,b):
    return a + b
def resta(a,b):
    return a-b

def by(a,b):
    return a*b
def divide(a,b):
    return 1.*a/(1.*b)

def relativePos(v1,v2):
    return v2-v1
def hipo(n1,n2):
    return sqrt(n1*n1+n2*n2)

def hipo3D(n1,n2,n3):
    return sqrt(n1*n1+n2*n2+n3*n3)

def lifetime(mass,p,flight):
    cnv = 1./(2.9979e-01)
    cnv = cnv /1.493
    return cnv*flight*mass/(vmod(p))

def salvavidas(x):
    return x

def decayPlane(v1,v2):
    r = v1 - v2
    s = v1 + v2
    return ACO(r,s) # Non fai falta dividir, mira que es sunormal

mumass = 105.658357                           
def decayPlane2(p1,p2,m1 =mumass,m2 = mumass,info = 0):
    mom1 = vmod(p1)
    mom2 = vmod(p2)
    E1 = sqrt(m1*m1+mom1*mom1)
    E2 = sqrt(m2*m2+mom2*mom2)
    
    v1 = p1/E1
    v2 = p2/E2
    p = p1+p2
    v = p*(1./(E1+E2))
    if info:
        print "Momenta: ",p1,p2
        print "Energy: ",E1,E2
        print "Velocities: ",v1,v2
        print "Velocity: ",v
        

    u1 = vunit(v) # B direction of flight. Taking it as X (!!) axis
    u2 = vunit(vcross(v1,v2))
    u3 = vunit(vcross(u1,u2))

    x = vdot(v1,u1)
    y = vdot(v1,u2)
    z = vdot(v1,u3)

    v1 = vector(x,y,z)

    x = vdot(v2,u1)
    y = vdot(v2,u2)
    z = vdot(v2,u3)

    v2 = vector(x,y,z)

    V = vmod(v)

    v = vector(V,0.,0.)
    if info:
        print "Rotated Velocities: ",v1,v2
        print "Rotated Velocity : ",v

    v1px = (v1[0] - V)*(1./(1-V*v1[0]))
    v2px = (v2[0] - V)*(1./(1-V*v2[0]))

    v1 = vector(v1px,v1[1],v1[2])
    v2 = vector(v2px,v2[1],v2[2])

    if info:
        print "Boosted Velocities : ",v1,v2
    sinT = abs(ACO(v1-v2,v))
    sinT1 = abs(ACO(v1,v))
    sinT2 = abs(ACO(v2,v))

    #if sinT != sinT1 or sinT != sinT2: print "Algo fixeches mal, ganhan !!!"
    if info: print sinT,sinT1, sinT2

    return asin(sinT)
def bringmass(a0,slope): 
    #stripping a0 = 450 slope = -0.07
    #bmubmu a0 = 1050 slope = -0.16 ## seems diferent distributions, but really are almost the same (more slope because more events)
    delta = 120*(random() - 0.5)
    mass = 5371 + delta
    x = random()*a0
    
    if x > a0 -slope*mass:
        mass = bringmass(a0,slope)
    return mass



def logfactor(number):
    out = 0
    number = int(round(number))
    for i in range(1,number + 1):
        out += log(i)
    return out

def ComputeMultinomial(ni,pi):
    N = sum(ni)
    n0 = logfactor(N)
    n2 = map(logfactor,ni)
    s = len(ni)
    for i in range(s):
        delta = -n2[i]
        if pi[i]!= 0: delta += ni[i]*log(pi[i])
        elif ni[i] != 0 : return 0.
        n0 += delta
    #print n0
    return exp(n0)
    
