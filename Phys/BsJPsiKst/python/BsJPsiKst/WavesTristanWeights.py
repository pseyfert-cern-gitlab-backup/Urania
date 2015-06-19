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

### Replace amplitudes by more suitable fit parameters
#BREAK

#s_xpa = Symbol("xpa",positive = True)
#s_x2pa = Symbol("x2pa",positive = True)

# S-wave amplitude.
s_As2 = USymbol("As2","F_S",positive = True)

# D-wave amplitudes.
s_fD = Symbol("fD", positive = True)
Ad2 = (1-s_As2)*s_fD
s_f2L = Symbol("f2L",positive = True)
s_f2pa = Symbol("f2pa",positive = True)#x2pa*(1-s_f2L)
f2pe = 1-s_f2L - s_f2pa

# P-wave amplitudes.
Ap2 = 1-s_As2 - Ad2
s_fL = USymbol("fL","f_L",positive = True)
s_fpa = USymbol("fpa","f_{||}",positive = True)#s_xpa*(1-s_fL)
fpe = 1-s_fL - s_fpa

func = func.subs( [ (TransAmpModuli["2_pe"], Sqrt(Ad2*f2pe)),(TransAmpModuli["2_pa"], Sqrt(Ad2*s_f2pa)),(TransAmpModuli["2_0"], Sqrt(Ad2*s_f2L))])
func = func.subs( [(TransAmpModuli["1_pa"], Sqrt(Ap2*s_fpa)),(TransAmpModuli["1_0"], Sqrt(Ap2*s_fL)),(TransAmpModuli["1_pe"], Sqrt(Ap2*fpe))] )
func = func.subs( TransAmpModuli["0_0"],Sqrt(s_As2))

TristanIntegral = TristanIntegral.subs( [ (TransAmpModuli["2_pe"], Sqrt(Ad2*f2pe)),(TransAmpModuli["2_pa"], Sqrt(Ad2*s_f2pa)),(TransAmpModuli["2_0"], Sqrt(Ad2*s_f2L))])
TristanIntegral = TristanIntegral.subs( [(TransAmpModuli["1_pa"], Sqrt(Ap2*s_fpa)),(TransAmpModuli["1_0"], Sqrt(Ap2*s_fL)),(TransAmpModuli["1_pe"], Sqrt(Ap2*fpe))] )
TristanIntegral = TristanIntegral.subs( TransAmpModuli["0_0"],Sqrt(s_As2))

### Figure out which variables the fit will depend on

potential_list = [x,y,z]+[ s_As2, s_fD, s_fL, s_fpa, s_f2L, s_f2pa ]+TransAmpPhases.values() + CSP_factors +  TristanWeights.values() 

final_list = []
for thing in potential_list:
    if thing in func.atoms() or thing in TristanIntegral.atoms(): final_list.append(thing)
    

### Generate and compile a fitting class corresponding to "func"

#BREAK
class_name = "TristanJpsiKpi_J" +str( max(spins))
op2 = D.RooClassGenerator(func, final_list,class_name)
op2.PrintToLatex()
BREAK
op2.addSubstitutions([(Sqrt(-x**2+1),"sthk"),(Sqrt(-y**2+1),"sthl"),((-x**2+1),"sthk2"),((-y**2+1),"sthl2")])

op2.addSubstitutions([(x**2,"cthk2"),(y**2,"cthl2"),(Cos(z)**2,"cosphi2"),(Sin(z)**2,"sinphi2"),(Cos(z),"cosphi"),(Sin(z),"sinphi")])
op2.addSubstitutions([(Sqrt(s_As2),"As"),(Sqrt(s_fD),"sqfD")])
op2.addSubstitutions([(Sqrt(s_fL),"sqfL"),(Sqrt(s_fpa),"sqfpa")])
op2.addSubstitutions([(Sqrt(s_f2L),"sqf2L"),(Sqrt(s_f2pa),"sqf2pa")])
#op2.addSubstitutions([(Sqrt(s_f2L),"sqf2L"),(Sqrt(s_x2pa),"sqx2pa")])
op2.addSubstitutions([(Cos(TransAmpPhases["2_0"]), "cdelta20"),(Cos(TransAmpPhases["2_pa"]), "cdelta2pa"),(Cos(TransAmpPhases["2_pe"]), "cdelta2pe")])
op2.addSubstitutions([(Sin(TransAmpPhases["2_0"]), "sdelta20"),(Sin(TransAmpPhases["2_pa"]), "sdelta2pa"),(Sin(TransAmpPhases["2_pe"]), "sdelta2pe")])
op2.addSubstitutions([(Cos(TransAmpPhases["1_pa"]), "cdelta_pa"),(Cos(TransAmpPhases["1_pe"]), "cdelta_pe")])
op2.addSubstitutions([(Sin(TransAmpPhases["1_pa"]), "sdelta_pa"),(Sin(TransAmpPhases["1_pe"]), "sdelta_pe")])
op2.addSubstitutions([(Sin(TransAmpPhases["0_0"]), "sdelta_s"),(Cos(TransAmpPhases["0_0"]), "cdelta_s")])

op2.addSubstitutions([(Sqrt(2),"sq2"),(Sqrt(3),"sq3"),(Sqrt(5),"sq5")])

#op2.addSubstitutions([((-x**2+1),"sthk2"),((-y**2+1),"sthl2"),(x**2,"cthk2"),(y**2,"cthl2"),(Cos(z),"cosphi"),(Sin(z),"sinphi"),(Sqrt(2),"sq2"),(Sqrt(5),"sq5")])
op2.makePdf(integrable = kTRUE)
op2.forceIntegral(1,[x,y,z], TristanIntegral)

op2.overwrite()
#op2.invoke()

gROOT.ProcessLine(".L "+class_name + ".cxx++")
#op2.printToLatex()
