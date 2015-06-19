from math import *
from Urania.SympyBasic import *
from Urania import PDG

mass = Symbol("mu", positive = True)
m0 = Symbol("m0", positive = True)
Mmom = Symbol("Mmom", positive = True)
Msister = Symbol("Msister", positive = True)
Mdau1 = Symbol("mdau1", positive = True)
Mdau2 = Symbol("mdau2", positive = True)

muh = Symbol("muh", positive = True)
mul = Symbol("mul", positive = True)
Gamma0 = Symbol("Gamma0", positive = True)



def PConjugate(a,b, simp = 0):
    from sympy import together, expand
    aprime = a
    bprime = b.conjugate()
      
    y = 1./(aprime*bprime)
    y = together(y)
    y = expand(y)
    y = together(y)
    if simp: y = simplify(y)
    return 1/y


def  Blatt_Weisskopf( q,  q0, L = 1) :
    if (L<1.): return 1.

    d = 3.e-03/L
    z = q*d*q*d
    z0 = q0*d*q0*d
    if (L==1): return (1+z0)/(1+z)
    if (L==2): return ((z0-3)*(z0-3) + 9*z0) / ((z-3)*(z-3) + 9*z)
    if (L==3): return (z0*(z0-15)*(z0-15) + 9*(z0-5)) / (z*(z-15)*(z-15) + 9*(z-5))
    return ( Pow(z0*z0 -45*z0+105,2) +25*z0*(2*z0-21)*(2*z0-21)) /(Pow(z*z -45*z+105,2) +25*z*(2*z-21)*(2*z-21))


def get_q(  M,  m1,  m2 ) :
    M2 = M*M
    m12 = m1*m1
    m22 = m2*m2
    q2 = .25*( M2*M2 - 2*M2*(m12+m22) +(m12*m12+m22*m22)-2*m12*m22) /M2
    if q2<0 : return 0.

    return Sqrt(q2)

def get_K( M,  M0,  Gamma0,  m1,  m2,  J = 1):
    q = get_q(M,m1,m2)
    q0 = get_q(M0,m1,m2)
    Gamma = Gamma0*Pow(q/q0,2*J+1)*M0/M*Blatt_Weisskopf(q,q0,J)
    return M0*Gamma/(M0*M0-M*M)



def  get_K_hat( M,  M0,  Gamma0,  m1,  m2,  J = 1):
    q = get_q(M,m1,m2)
    q0 = get_q(M0,m1,m2)
    Gamma = Gamma0*Pow(q/q0,2*J+1)*M0/M*Blatt_Weisskopf(q,q0,J)
    return Sqrt(M0*Gamma0)/(M0*M0-M*M)

q = get_q(mass,Mdau1, Mdau2)
q0 = get_q(m0, Mdau1, Mdau2)
p = get_q(Mmom,Msister,mass)
p0 = get_q(Mmom,Msister,m0)

y_ps = q*p/mass**2 ## Yuehong's phase space factor

J = 1.
K0 = get_K(mass,m0,Gamma0,Mdau1,Mdau2,J)
K0h = get_K_hat(mass,m0,Gamma0,Mdau1,Mdau2,J)

### Generic Propagators:

FlatSwave = Sqrt(1/(muh-mul))
NoRelBW = 1/(mass - m0 + I*0.5*Gamma0)
EvtGen = K0h / (1-I*K0)

### End Generic propagators

### Some hack for testing

 ### PDG.phi.mass = 1020
 #### PDG.phi.width = 4.26
### Channel specific phase space factors, with examples of massaging

B2JpsiKK_ps = y_ps.subs([(Mmom,PDG.Bd.mass),(Msister,PDG.Jpsi.mass),(Mdau1,Mdau2)]) ## Step by step. First we tell her the two daughters are the same
B2JpsiKK_ps = simplify(B2JpsiKK_ps.subs(Mdau2,PDG.Kplus.mass)) ## Now substitute the daughter by a number, and simplify

Bs2JpsiKK_ps = y_ps.subs([(Mmom,PDG.Bs.mass),(Msister,PDG.Jpsi.mass),(Mdau1,Mdau2)]) ## Step by step. First we tell her the two daughters are the same
Bs2JpsiKK_ps = simplify(Bs2JpsiKK_ps.subs(Mdau2,PDG.Kplus.mass)) ## Now substitute the daughter by a number

### Channel specific propagators

phi_noRel = NoRelBW.subs( [(m0,PDG.phi.mass), (Gamma0,PDG.phi.width)])
phi2KK_EvtGen = EvtGen.subs( [(m0,PDG.phi.mass), (Gamma0,PDG.phi.width),(Mdau1,Mdau2)])## Step by step. First we tell her the two daughters are the same
phi2KK_EvtGen = phi2KK_EvtGen.subs(Mdau2,PDG.Kplus.mass)## Now substitute the daughter by a number



### Few tools

def Csp(sw, pw, lo, hi, PS = Bs2JpsiKK_ps):
    pwconj = pw.conjugate()
    pwconj= pwconj.subs( mass, mass.conjugate()) ## mass is real, let's make life easier
    c = Integral(pw*pwconj*PS,(mass,mul,muh))
    c = c.subs([(mul,lo),(muh,hi)])
    c = c.n()
    #print 1
    d = Integral(sw*sw.conjugate()*PS,(mass,mul,muh))
    d = d.subs([(mul,lo),(muh,hi)])
    d = d.n()
    #print 2
    cte = 1/Sqrt(d*c)
    csp = Integral(sw.conjugate()*cte*pw*PS,(mass,mul,muh))
    csp = csp.subs([(mul,lo),(muh,hi)])
    csp = csp.n()
    #print 3
    x = re(csp)
    y = im(csp)

    CSP = sqrt(x**2 + y**2)
    theta = -atan(y/x)
    if theta < 0 : theta = theta+pi
    

    return CSP, theta


def test(lo, hi):   ### Test for the Jpsi Phi paper. Calculated CSP for different phi(1020) descriptions
    print " MKK in [ " , lo, ",", hi ,"]"
    print "------------------------------"
    print "S: Flat, P: No Rel, PhasSpa: N "
    print  Csp(FlatSwave,phi_noRel, lo,hi, PS = 1.0)
    print "S: Flat, P: No Rel, PhasSpa: Y "
    print  Csp(FlatSwave,phi_noRel, lo,hi)
    print "S: Flat, P: EvtGen, PhasSpa: N "
    print  Csp(FlatSwave,phi2KK_EvtGen, lo,hi, PS =1.0)
    print "S: Flat, P: EvtGen, PhasSpa: Y "
    print  Csp(FlatSwave,phi2KK_EvtGen, lo,hi, )
    
    
def histogramResonance(res, lo, hi, N= 100):
    from ROOT import TH1F
    from sympy import simplify
    pdf = PS*res*res.conjugate()
    h = TH1F("A","A", N,lo,hi)
    stp = (hi-lo)*1./N
    for i in range(N):
        x = lo + i*stp
        y = float( simplify(Abs(1./pdf.subs(mass,x))) )  ## if we invert the complex number we make her life easier
        y = 1./y  ### now re-invert it to get the correct pdf
        h.SetBinContent(i+1,y)
    h.SetLineWidth(3)
    return h

    
