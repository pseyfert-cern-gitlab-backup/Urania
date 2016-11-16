from ROOT import *
from math import *
from array import *
from Urania import PDG
from Urania.Helicity import *
from Urania import RooInterfaces as D
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from OurSites import *
from sympy.utilities.lambdify import lambdify
from parameters import KpiBins4 as Kpibins
#neim = sys.argv[1]
#neim = "2011p_826_861"

spins = [0,1]
## ### Generate the pdf using the tools in Urania.Helicity
A = doB2VX(spins, helicities = [1,-1], transAmp = 1)#0)
### masage a bit the expression to make it more suitable for fitting
pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())#H.values())
phys = 0

TristanIntegral = 0
TristanWeights = {}
#BREAK
x = Symbol("helcosthetaK",real = True)
y = Symbol("helcosthetaL", real = True)
z = Symbol("helphi", real = True)
CThL = Cos(ThetaL)
CThK = Cos(ThetaK)
def changeFreeVars(function):
    function = function.subs( Sin(2*ThetaK), 2*Sin(ThetaK)*Cos(ThetaK))
    function = function.subs( Cos(2*ThetaK), 2*Cos(ThetaK)**2 - 1)
    function = function.subs( Sin(ThetaK), Sqrt(1-Cos(ThetaK)**2))
    function = function.subs( Sin(ThetaL), Sqrt(1-Cos(ThetaL)**2))
    function = function.subs([(CThK,x),(CThL,y), (Phi,-z)])

    return function

lam_pdf_split = {}
for key in pdf_split:
    pdf_split[key] = changeFreeVars(pdf_split[key])
    phys += StrongPhases(key)*pdf_split[key]
    if pdf_split[key]:
        lam_pdf_split[key] = lambdify((x,y,z), pdf_split[key], ("numpy"))   ### Lambdify it to make it faster.
        TristanWeights[key] = 0#  Symbol("w_" + str(list(key.atoms())[0]) + str(list(key.atoms())[1]), positive = True)
        #TristanIntegral += StrongPhases(key) *  TristanWeights[key]

T = TransAmpModuli
P = TransAmpPhases


##c1_psi = Symbol("c1_psi",real = True)
##c2_psi = Symbol("c2_psi",real = True)
##c3_psi = Symbol("c3_psi",real = True)
##c4_psi = Symbol("c4_psi",real = True)
##y_acc = Symbol("y_acc", positive = True)
##c2_theta = Symbol("c2_theta", real = True)

##c5_psi = -1-c1_psi - c2_psi - c3_psi - c4_psi + y_acc
##acc = (1. + c1_psi*x + c2_psi*x*x + c3_psi*x*x*x + c4_psi*x*x*x*x + c5_psi*x*x*x*x*x)*(1.  + c2_theta*y*y)
##acc = acc.subs([( c1_psi, -5.20101e-01),(c2_psi, -7.33299e-01), (c3_psi, -2.90606e-01), (c4_psi, 2.69475e-01), (c2_theta, 2.76201e-01), (y_acc,0)])
def CalculateWeights(acc):
    
    out = {}

    for key in TristanWeights.keys():
        TristanWeights[key] = iter_integrate(acc*pdf_split[key],(z,-Pi,Pi),(x,-1,1), (y, -1,1)).n()
        
        if "Abs" in str(key): out[str(key).replace("Abs(A_","").replace(")**2","")+str(key).replace("Abs(A_","").replace(")**2","")]=TristanWeights[key]
        else: out[str(key).replace("re(","").replace("im(","").replace("A_","").replace("*conjugate(","").replace("))","")]=TristanWeights[key]
    den = out['00']
    for key in out.keys(): out[key] = out[key]/den
    return out

