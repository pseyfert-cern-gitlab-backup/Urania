from Urania.Helicity import *
from Urania.MassAmplitudes import *

A = doB2VX([0,1], helicities = [1,-1], transAng = 0)

pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())#H.values())
phys = 0
for key in pdf_split: phys += StrongPhases(key)*pdf_split[key]

#BREAK


### change the free variables to cosines
x = Symbol("helcosthetaK",real = True)
y = Symbol("helcosthetaL", real = True)
z = Symbol("helphi", real = True)
CThL = Cos(ThetaL)
CThK = Cos(ThetaK)
def changeFreeVars(function):
    function  = function.subs( Sin(2*ThetaK), 2*Sin(ThetaK)*Cos(ThetaK))
    function  = function.subs( Cos(2*ThetaK), 2*Cos(ThetaK)**2 - 1)
    function  = function.subs( Sin(ThetaK), Sqrt(1-Cos(ThetaK)**2))
    function  = function.subs( Sin(ThetaL), Sqrt(1-Cos(ThetaL)**2))
    function = function.subs([(CThK,x),(CThL,y), (Phi,z)])

    return function

func = changeFreeVars(phys)
func2 = func.subs(delta_peC,Pi + delta_peC)
func += func2
func = simplify(func)

## Mass part
#from Urania.MassAmplitudes import *
#funcT = func.subs(

MassMod = {1: Kst02Kpi_EvtGen, 0: Kmatrix_KpiSwave}
substitutions = []
for key in TransAmplitudes.keys():
    J = int(key[0])
    substitutions.append((TransAmplitudes[key],MassMod[J]))
#A4 = A.subs(substitutions)
#pdf_split4 = DecomposeAmplitudes(A4,TransAmplitudes.values())#H.values())
phys4 = 0
for key in pdf_split:
    phys4 += StrongPhases(key)*pdf_split[key]*key.subs(substitutions)

func4 = changeFreeVars(phys4)
#func42 = func4.subs(delta_peC,Pi + delta_peC)
func4 = func4.subs(Sin(delta_peC,0))
#func4 = simplify(func4)
                         
