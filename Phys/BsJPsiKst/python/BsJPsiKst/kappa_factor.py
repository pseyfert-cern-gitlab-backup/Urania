from Urania.Helicity import *
from math import sqrt,pi


c1_psi = Symbol("c1_psi", real = True)
c2_psi = Symbol("c2_psi", real = True)
c3_psi = Symbol("c3_psi", real = True)
c4_psi = Symbol("c4_psi", real = True)
c5_psi = Symbol("c5_psi", real = True)
c1_phi = Symbol("c1_phi", real = True)
c2_phi = Symbol("c2_phi", real = True)
c3_phi = Symbol("c3_phi", real = True)

c2_theta = Symbol("c2_theta", real = True)

CThL = Cos(ThetaL)
CThK = Cos(ThetaK)

acc_psi = 1. + c1_psi*CThK + c2_psi*CThK**2 + c3_psi*CThK**3 
acc_theta = 1. +  c2_theta*CThL;
acc_phi = 1. + c1_phi*Cos( c2_phi*Phi + c3_phi)

Acc = acc_psi*acc_theta*acc_phi

A = doB2VX([0,1], helicities = [1,-1])
pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())

pdf = 0


for key in pdf_split: pdf += ExplicitStrongPhases(key)*pdf_split[key]

As2val, Apa2val, Ape2val = 0.123, 0.2,0.4
A02val = 1 - Apa2val-Ape2val-As2val
ds, dpa, dpe = 3.,3.,3.
#BREA
x = Symbol("x",real = True)
y = Symbol("y", real = True)
z = Symbol("z", real = True)
def changeFreeVars(function):
    function  = function.subs( Sin(ThetaK), Sqrt(1-Cos(ThetaK)**2))
    function  = function.subs( Sin(ThetaL), Sqrt(1-Cos(ThetaL)**2))
    function = function.subs([(CThK,x),(CThL,y), (Phi,z)])

    return function


pdf = pdf * Acc

pdf = pdf.subs([(c1_psi,-1.), (c2_psi,0),(c3_psi,0),(c2_theta,0),(c1_phi,0),(c2_phi,0) ])   #### Substitute acceptance coeefs values.
pdf = changeFreeVars(pdf)
pdfTot = pdf.subs( [(A02,A02val),(AS2,As2val),(Apa2,Apa2val), (Ape2,Ape2val),(delta_s,ds),(delta_pa,dpa),(delta_pe,dpe)])
pdf_S = pdf.subs( [(A02,0),(AS2,As2val),(Apa2,0), (Ape2,0),(delta_s,ds),(delta_pa,dpa),(delta_pe,dpe)])
pdf_P = pdf.subs( [(A02,A02val),(AS2,0),(Apa2,Apa2val), (Ape2,Ape2val),(delta_s,ds),(delta_pa,dpa),(delta_pe,dpe)])



def plotPdf(zz):
    v = zz[0]
    fr = v[0].frame()
    zz[-1].plotOn(fr)
    fr.Draw()
    return fr

def rectInt(function, tuple):
     return Integral(function,tuple).as_sum(500)

def AngularIntegral( function ):
    """ Integrates over the angles in an analytical way. May not work if the acceptance is such that the total pdf is not integrable
    """
    return integrate(function,(z,-Pi,Pi),(x,-1,1), (y,-1,1))

def NumericAngularIntegral( function , name):
    """ Uses RooFit to calculate the numeric integral over the angles
    """
    from Urania import RooInterfaces
    zz = RooInterfaces.RooGenericfy(function,[(x,-1,1),(y,-1,1),(z,-pi,pi)], name)
    g = zz[-1].createIntegral(zz[-1].getVariables())
    return g.getVal()
    
print NumericAngularIntegral( pdf_S,"SwavePDF") *1/NumericAngularIntegral(pdfTot,"FullPDF")

## print AngularIntegral(pdf_S)*1./AngularIntegral(pdfTot)  ## Make the integrals analyticaly. But might not work for some acceptance functions.



