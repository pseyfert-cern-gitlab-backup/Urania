from ROOT import *
MY_PATH = "/scratch19/Kspi0/"
#f = TFile("~/w7folder/kspi0/Tuple_MC_Frankfurt.root")
f = TFile(MY_PATH + "kspi0mm_DTFMC12_Strip_Down.root")
t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
kPaula = TColor.GetColor("#ff99cc")
#f = TFile("bkgMini.root")
#t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
#BREAK
from SomeUtils.alyabar import *
from Urania import PDG
#import Sym_constr_IP as IP_formulae
from Urania.SympyBasic import *
from sympy import mpmath, lambdify, simplify

mpmath.mp.dps = 10
EM = Symbol("E_M", positive = True)
E1 = Symbol("E_1", positive = True)
E2 = Symbol("E_2", positive = True)
am = Symbol('a_m')
bm = Symbol('b_m')
aB = Symbol('a_B')
bB = Symbol('b_B')
cTheta = Symbol("ctheta", real = True)
def mean(E): return am + bm*E #mean parametrization
def sigma(E): return aB + bB*E #sigma parametrization (?)
#a_m, b_m, a_B, b_B need to be defined
def lam(E): return -0.85
def nu(E): return -lam(E)/2.
## PFormula = (EM -m(EM) **2 + B)** (lam(E) - 0.5) #t-Student
PFormula = (1 + ((EM - mean(EM))/sigma(EM))**2)**(lam(EM) - 0.5)
## TO BE CHECKED

P1 = PFormula.subs([(EM,E1),(aB,1101.579),(bB,0.0299),(am,407.73),(bm,0.947)]) #to be implemented nicely
P2 = P1.subs(E1,E2)#,(aB,938.74),(bB,0.06),(am,388.61),(bm,0.916)])

def Mgg(E1,E2, cTheta): return (2*E1*E2*(1-cTheta))**(0.5)

sigma_mpi0 = One# 0.0006 #from the PDG (MeV)
Pmass = Exp( -One/2*( (( Mgg(E1,E2, cTheta) - PDG.pi0.mass)/sigma_mpi0)**2))
#lnPmass = Log(Pmass)
PTOT = P1*P2*Pmass
#total pdf. mass part of the pion as a gaussian. sigma_mpi0 either a tiny number or the PDG value
lnPTOT = simplify(Log(PTOT))

eq1 = PTOT.diff(E1)
eq2 = PTOT.diff(E2)
#eq1 = lnPTOT.diff(E1)
#eq2 = lnPTOT.diff(E2)
myeqs = [eq1,eq2] #to maximize the partial derivatives of the pdf

def P(EM): #t-Student, not as a symbolic expression but as a function of the energy
    return (1 + ((EM - mean(EM))/sigma(EM))**2)**(lam(EM) - 0.5)

## Create lambdified versions if slow
mylambs = [] 
for eq in myeqs:
    mylambs.append(lambdify( (E1,E2,cTheta), eq, ('numpy'))) #create functions

def getfunction(lamb, cTheta): #get a function with arguments only energies, not cTheta
    ## print "I'm getting out function"
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
        event_eqs.append(getfunction(eq,cTh)) #append equations as a function of the 2 energies

    print "Initial values: ", e1, e2, "==>", event_eqs[0](e1,e2), event_eqs[1](e1,e2)
    try:
        rot = mpmath.findroot(event_eqs, (e1,e2))#,tol = 1e14)
        
    except ValueError:
        print "Warning: No precise solution found, increasing the tolerance"
        rot = mpmath.findroot(event_eqs, (e1,e2),tol = 1e14) #e1,e2 as starting points
        #tolerance so big so that python does his best
    except ZeroDivisionError:
        print "ZeroDivision Error. Momenta left uncorrected"
        rot = [e1,e2]
    except TypeError:
        print "Something is fucked up. mpmath returned a TypeError: out() takes exactly 2 arguments (1 given)"
        rot = [e1,e2]

    e_corr_1 = rot[0]
    e_corr_2 = rot[1]

    return e_corr_1, e_corr_2

for entry in t:
    print getCorrectedEnergies(entry)
     
