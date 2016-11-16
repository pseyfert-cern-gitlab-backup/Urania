from ROOT import *
#f = TFile("~/w7folder/kspi0/Tuple_MC_Frankfurt.root")
f = TFile("~/w7folder/kspi0/KsPi0MM_dataL0Tis_1.root")
t = f.Get("T")
kPaula = TColor.GetColor("#ff99cc")
#f = TFile("bkgMini.root")
#t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
#BREAK
from SomeUtils.alyabar import *
from Urania import PDG
#import Sym_constr_IP as IP_formulae
from sympy import nsolve, solve, mpmath,lambdify
h = TH1F("A","A", 100,0,1 )
hb = TH1F("B","B", 100, 0,1)
href = TH1F("ref","ref",100, 0,1)
mpmath.mp.dps = 10
EM = Symbol("E_M", positive = True)
E1 = Symbol("E_1", positive = True)
E2 = Symbol("E_2", positive = True)
cTheta = Symbol("ctheta", real = True)
def mean(E): return a_m + b_m*E
def B(E): return a_B + b_B*E
def lam(E): return -0.8

PFormula = (EM -m(EM) **2 + B)** (lam(E) - 0.5)

P1 = PFormula.subs(EM,EM1)
P2 = PFormula.subs(EM,EM2)

def Mgg(E1,E2, cTheta): return 2*E1*E2*(1-cTheta) #whatever, Miriam please check

PTOT = P1*P2* Exp( -One/2*( (( Mgg(E1,E2, cTheta) - PDF.pi0.mass)/sigma_mpi0)**2))

eq1 = PTOT.diff(E1)
eq2 = PTOT.diff(E2)
myeqs = [eq1,eq2]

def P(EM):
    return ( (EM -m(EM) **2 + B)** (lam(E) - 0.5))

## Create lambdified versions if slow
mylambs = []
for eq in myeqs:
    mylambs.append(lambdify( (E1,E2,cTheta), eq, ('numpy')))

def getfunction(lamb, cTheta):
    def out(E1,E2):
        return lamb(E1,E2, cTheta)
    return out


def getCorrectedEnergies(entry):
    pg1 = vector(entry.g1p1, entry.g1p2, entry.g1p3)
    pg2 = vector(entry.g2p1, entry.g2p2, entry.g2p3)
    e1 = vmod(pg1)
    e2 = vmod(pg2)
    cTh = cos(ACO(pg1,pg2)) ### Either this or the corrected cTh by using the SV position and the cluster positions
   
    event_eqs = []
    for eq in mylambs:
        event_eqs.append(getfunction(eq,cTh))
    try:
        rot = mpmath.findroot(event_eqs, (e1,e2))#,tol = 1e14)
        
    except ValueError:
        print "Warning: No precise solution found, increasing the tolerance"
        rot = mpmath.findroot(event_eqs, (e1,e2),tol = 1e14)
        
    except ZeroDivisionError:
        print "ZeroDivision Error. Momenta left uncorrected"
        rot = [e1,e2]
        
    ### Corrected energies

    e_corr_1 = rot[0]
    e_corr_2 = rot[1]

    return e_corr_1, e_corr_2
