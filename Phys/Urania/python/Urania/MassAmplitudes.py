from math import *
from Urania.SympyBasic import *
from Urania import PDG

mass = Symbol("mu", positive = True)
m0 = Symbol("m0", positive = True)
Mmom = Symbol("Mmom", positive = True)
Msister = Symbol("Msister", positive = True)
Mdau1 = Symbol("mdau1", positive = True)
Mdau2 = Symbol("mdau2", positive = True)
J = Symbol("J", natural = True)
kappa = Symbol("kappa", real = True)

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

def get_rho(mu, m0): return Sqrt(1 - 4*m0*m0/(mu*mu))

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
gpipi = Symbol("gpipi",positive = True)
gKK = Symbol("gKK", positive = True)
Flatte_0 = 1/(m0*m0 - mass*mass - I*m0*(gpipi*(2./3*get_rho(mass,PDG.piplus.mass)+ 1./3*get_rho(mass,PDG.pi0.mass)) + gKK*(1./2*get_rho(mass,PDG.Kplus.mass) + 1./2*get_rho(mass,PDG.K0.mass))))
Flatte_Y = 1/(m0*m0 - mass*mass - I*m0*(gpipi*get_rho(mass, 139.57) + gKK*get_rho(mass,493.677)))

FlatSwave = Sqrt(1/(muh-mul))
NoRelBW = 1/(mass - m0 + I*0.5*Gamma0)
EvtGen = K0h / (1-I*K0)
Kmatrix_ResPlusFlat = (K0h + kappa)/( 1 - I*(K0+kappa*2*Pow(get_q(mass,Mdau1,Mdau2)/mass,2*J+1)))

f0_BES = Flatte_0.subs([(m0, 965), (gKK,4.21*gpipi)])
f0_BES = f0_BES.subs(gpipi,165)

f0_Syr = Flatte_0.subs([(m0, 939.9), (gKK,3.0*gpipi)])
f0_Syr = f0_Syr.subs(gpipi,199.)

f0_BESY = Flatte_Y.subs([(m0, 965), (gKK,4.21*gpipi)])
f0_BESY = f0_BESY.subs(gpipi,165)

### End Generic propagators

### Some hack for testing

 ### PDG.phi.mass = 1020
 #### PDG.phi.width = 4.26
### Channel specific phase space factors, with examples of massaging

B2JpsiKK_ps = y_ps.subs([(Mmom,PDG.Bd.mass),(Msister,PDG.Jpsi.mass),(Mdau1,Mdau2)]) ## Step by step. First we tell her the two daughters are the same
B2JpsiKK_ps = simplify(B2JpsiKK_ps.subs(Mdau2,PDG.Kplus.mass)) ## Now substitute the daughter by a number, and simplify

Bs2JpsiKK_ps = y_ps.subs([(Mmom,PDG.Bs.mass),(Msister,PDG.Jpsi.mass),(Mdau1,Mdau2)]) ## Step by step. First we tell her the two daughters are the same
Bs2JpsiKK_ps = simplify(Bs2JpsiKK_ps.subs(Mdau2,PDG.Kplus.mass)) ## Now substitute the daughter by a number

B2JpsiKpi_ps = y_ps.subs([(Mmom,PDG.Bd.mass),(Msister,PDG.Jpsi.mass),(Mdau1,PDG.Kplus.mass),(Mdau2,PDG.piplus.mass)]) 

### Channel specific propagators

phi_noRel = NoRelBW.subs( [(m0,PDG.phi.mass), (Gamma0,PDG.phi.width)])
phi2KK_EvtGen = EvtGen.subs( [(m0,PDG.phi.mass), (Gamma0,PDG.phi.width),(Mdau1,Mdau2)])## Step by step. First we tell her the two daughters are the same
phi2KK_EvtGen = phi2KK_EvtGen.subs(Mdau2,PDG.Kplus.mass)## Now substitute the daughter by a number

Kst02Kpi_EvtGen = EvtGen.subs( [(m0,PDG.Kst0.mass), (Gamma0,PDG.Kst0.width),(Mdau1,PDG.Kplus.mass),(Mdau2,PDG.piplus.mass)])#
Kmatrix_KpiSwave = Kmatrix_ResPlusFlat.subs([ (m0,PDG.ParticleData(10321).mass),(Gamma0,PDG.ParticleData(10321).width),(kappa, 2.23802e-03 ), (Mdau1,PDG.Kplus.mass), (Mdau2,PDG.piplus.mass)])

### Few tools
def doEvtGen(m,g):
    out = EvtGen.subs( [(m0,m), (Gamma0,g),(Mdau1,Mdau2)])## Step by step. First we tell her the two daughters are the same
    out = out.subs(Mdau2,PDG.Kplus.mass)## Now substitute the daughter by a number
    return out


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
    if theta < 0 : theta = theta+2*pi
    

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
    
    
def histogramResonance(res, lo, hi, N= 100, PS=1):
    from ROOT import TH1F
    from sympy import simplify
    pdf = PS*res*res.conjugate()
    h = TH1F("A","A", N,lo,hi)
    stp = (hi-lo)*1./N
    for i in range(N):
        x = lo + i*stp
        y = float( simplify(Abs(1./pdf.subs(mass,x))) )  ## if we invert the complex number we make her life easier
        if y !=0: y = 1./y  ### now re-invert it to get the correct pdf
        else: print "Warning, pdf seems to explode at ", x
        h.SetBinContent(i+1,y)
    h.SetLineWidth(3)
    return h


    
def Csp_res(sw, pw, sigma, stp,  phys_min, phys_max, lo, hi, PS = Bs2JpsiKK_ps):
    true_mass = Symbol("m_true",real = True)
    def smearedIntegral(expr):
        thingie = expr.subs(mass,true_mass)
        thingie = thingie.subs([(mul,phys_min),(muh,phys_max)])
        pdf = Integral(thingie*Exp(-One/2*((mass-true_mass)/sigma)**2),(true_mass,phys_min,phys_max))
        stepsize = stp
        nsteps = int(round((hi-lo)/stepsize))
        stepsize = (hi-lo)*1./nsteps
        out = 0
        for i in range(nsteps):
            print i, nsteps
            m = lo + i*stepsize
            out += pdf.subs(mass,m).n()*stepsize
        return out

    pwconj = pw.conjugate()
    pwconj= pwconj.subs( mass, mass.conjugate()) ## mass is real, let's make life easier
    c = smearedIntegral(pw*pwconj*PS)
    c = c.n()
    #print 1
    d = smearedIntegral(sw*sw.conjugate()*PS)
    d = d.n()
    #print 2
    cte = 1/Sqrt(d*c)
    csp = smearedIntegral(sw.conjugate()*cte*pw*PS)
    csp = csp.n()
    #print 3
    x = re(csp)
    y = im(csp)
    print cte
    print csp
    print x, y
    CSP = sqrt(x.n()**2 + y.n()**2)
    theta = -atan(y/x)
    if theta < 0 : theta = theta+2*pi
    

    return CSP, theta

def Csp_stt(sw, pw, sigma, l, stp, phys_min, phys_max, lo, hi, PS = Bs2JpsiKK_ps):
    true_mass = Symbol("m_true",real = True)
    
    def smearedIntegral(expr):
        thingie = expr.subs(mass,true_mass)
        thingie = thingie.subs([(mul,lo),(muh,hi)])
        pdf = Integral(thingie*(1 + ((mass-true_mass)/sigma)**2)**(l-0.5),(true_mass,phys_min,phys_max))
        stepsize = stp
        nsteps = int(round((hi-lo)/stepsize))
        stepsize = (hi-lo)*1./nsteps
        out = 0
        for i in range(nsteps):
            print i, nsteps
            m = lo + i*stepsize
            out += pdf.subs(mass,m).n()*stepsize
        return out

    pwconj = pw.conjugate()
    pwconj= pwconj.subs( mass, mass.conjugate()) ## mass is real, let's make life easier
    c = smearedIntegral(pw*pwconj*PS)
    c = c.n()
    #print 1
    d = smearedIntegral(sw*sw.conjugate()*PS)
    d = d.n()
    #print 2
    cte = 1/Sqrt(d*c)
    csp = smearedIntegral(sw.conjugate()*cte*pw*PS)
    csp = csp.n()
    #print 3
    x = re(csp)
    y = im(csp)
    print x, y
    CSP = sqrt(x.n()**2 + y.n()**2)
    theta = -atan(y/x)
    if theta < 0 : theta = theta+2*pi
    

    return CSP, theta

def test_res():
    print Csp_res(FlatSwave,phi2KK_EvtGen,1.5,.1,2*PDG.Kplus.mass+1, PDG.Bs.mass - PDG.Jpsi.mass - 1, 990.,1008. )
## 0.481157765369525 0.487612851380907
## (0.6850394791595695, 2.34953141601191)
## >>> Csp(FlatSwave,phi2KK_EvtGen,3., 1008,1020 )
## Tr

def test_stt():
    print Csp_stt(FlatSwave,.1,phi2KK_EvtGen,1.5,-2,.1,2*PDG.Kplus.mass+1, PDG.Bs.mass - PDG.Jpsi.mass - 1, 990.,1008. )
