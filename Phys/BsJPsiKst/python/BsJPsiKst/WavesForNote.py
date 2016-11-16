from ROOT import *
from math import *
from array import *
from Urania import PDG
from Urania.Helicity import *
from Urania import RooInterfaces as D
spins = [0,1,2]
## ### Generate the pdf using the tools in Urania.Helicity
A = doB2VX(spins, helicities = [1,-1], transAmp = 1)#0)
### masage a bit the expression to make it more suitable for fitting
pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())#H.values())
#pdf_split = DecomposeAmplitudes_withCSP(A,TransAmplitudes)#H.values())

phys = 0
TristanIntegral = 0
TristanWeights = {}

### CSP factors
DefineStrongPhases()
SpinMap = { v:k for k,v in TransAmplitudes.items()}
CSP_factors = []

for key in pdf_split:
    Amp1 = list(key.atoms())[0]
    Amp2 = list(key.atoms())[1]
    cte = One
    if Amp2 != 2 and Amp1 !=2:
        J1 = max( SpinMap[Amp1][0],  SpinMap[Amp2][0])
        J2 = min( SpinMap[Amp1][0],  SpinMap[Amp2][0])
        if J1 != J2 :
            cte = USymbol("Cfact_" + J1 + J2 , "C_{" + J1 + "," + J2 + "}", real = True)
            if cte not in CSP_factors: CSP_factors.append(cte)
        
    phys += StrongPhases(key)*pdf_split[key]*cte
    if pdf_split[key]:
        TristanWeights[key] =  Symbol("w_" + str(Amp1) + str(Amp2), positive = True)
        TristanIntegral += StrongPhases(key) *  TristanWeights[key]*cte


#BREAK


### change the free variables to cosines
x = USymbol("helcosthetaK","c\\theta_K",real = True)
y = USymbol("helcosthetaL","c\\theta_l",  real = True)
z = USymbol("helphi","\\phi",  real = True)
CThL = Cos(ThetaL)
CThK = Cos(ThetaK)
def changeFreeVars(function):
    function  = function.subs( Sin(2*ThetaK), 2*Sin(ThetaK)*Cos(ThetaK))
    function  = function.subs( Cos(2*ThetaK), 2*Cos(ThetaK)**2 - 1)
    function  = function.subs( Sin(ThetaK), Sqrt(1-Cos(ThetaK)**2))
    function  = function.subs( Sin(ThetaL), Sqrt(1-Cos(ThetaL)**2))
    #function = function.subs([(CThK,x),(CThL,y), (Phi,-Pi-z)])
    function = function.subs([(CThK,x),(CThL,y), (Phi,-z)])
    return function

func = changeFreeVars(phys)


potential_list = [x,y,z]+TransAmplitudes.values()+TransAmpPhases.values() + CSP_factors

final_list = []
for thing in potential_list:
    if thing in func.atoms() : final_list.append(thing)
    

### Generate and compile a fitting class corresponding to "func"

#BREAK
class_name = "NoteJpsiKpi_J" +str( max(spins))
op2 = D.RooClassGenerator(func, final_list,class_name)
op2.printToLatex()
