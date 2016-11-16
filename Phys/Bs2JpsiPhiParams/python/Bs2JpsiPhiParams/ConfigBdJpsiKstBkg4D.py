from Urania.Helicity import *
from Urania.MassAmplitudes import *

A = doB2VX([0,1], helicities = [1,-1], transAng = 0)

pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())#H.values())

MassMod = {1: Kst02Kpi_EvtGen, 0: Kmatrix_KpiSwave}
substitutions = []
for key in TransAmplitudes.keys():
    J = int(key[0])
    substitutions.append((TransAmplitudes[key],MassMod[J]))
phys4 = 0
for key in pdf_split:
    phys4 += StrongPhases(key)*pdf_split[key]*key.subs(substitutions)

x = Symbol("helcosthetaK",real = True)
y = Symbol("helcosthetaL", real = True)
z = Symbol("helphi", real = True)
time = Symbol("helphi", positive = True)

CThL = Cos(ThetaL)
CThK = Cos(ThetaK)

### change the free variables to cosines
def changeFreeVars(function):
    function  = function.subs( Sin(2*ThetaK), 2*Sin(ThetaK)*Cos(ThetaK))
    function  = function.subs( Cos(2*ThetaK), 2*Cos(ThetaK)**2 - 1)
    function  = function.subs( Sin(ThetaK), Sqrt(1-Cos(ThetaK)**2))
    function  = function.subs( Sin(ThetaL), Sqrt(1-Cos(ThetaL)**2))
    function = function.subs([(CThK,x),(CThL,y), (Phi,z)])

    return function

func4 = changeFreeVars(phys4)
func4 = func4.subs(Sin(delta_peC),0)
                         
###############################
# Define Parameter values   ###
###############################

BdMC = func4.subs([(TransAmpModuli['1_pa'], 0.241),(TransAmpModuli['1_pe'],0.160),(TransAmpModuli['1_0'],1-0.241-0.160),(TransAmpModuli['0_0'],0.0),(delta_paC,2.503),(delta_peC,-0.168),(delta_sC,0.0)])

Bd_Apa2_ = 0.227
Bd_Ape2_ = 0.201
Bd_A02_ = 1- Bd_Apa2_ - Bd_Ape2_
Bd_As2_ = 0.1
Bd_Asum = Bd_A02_ + Bd_Apa2_ + Bd_Ape2_ + Bd_As2_
Bd_A02 = Bd_A02_/Bd_Asum
Bd_Apa2 = Bd_Apa2_/Bd_Asum
Bd_Ape2 = Bd_Ape2_/Bd_Asum
Bd_As2 = Bd_As2_/Bd_Asum


BdDat = func4.subs([(TransAmpModuli['1_pa'], Bd_Apa2 ),(TransAmpModuli['1_pe'],Bd_Ape2),(TransAmpModuli['1_0'],Bd_A02),(TransAmpModuli['0_0'],Bd_As2),(delta_paC,-2.94),(delta_peC,2.94),(delta_sC,0.0)])
BdS = func4.subs([(TransAmpModuli['1_pa'], 0.0 ),(TransAmpModuli['1_pe'],0.0),(TransAmpModuli['1_0'],0.0),(TransAmpModuli['0_0'],1.0),(delta_paC,-2.94),(delta_peC,2.94),(delta_sC,0.0)])
BdP = func4.subs([(TransAmpModuli['1_pa'], Bd_Apa2 ),(TransAmpModuli['1_pe'],Bd_Ape2),(TransAmpModuli['1_0'],Bd_A02),(TransAmpModuli['0_0'],0.0),(delta_paC,-2.94),(delta_peC,2.94),(delta_sC,0.0)])

def LookAtMass(x_ =0, y_ = 0, z_= 0):
    from ROOT import TGraph, kGreen, kRed
    fDat = BdDat.subs([(x,x_),(y,y_),(z,z_)])
    fMC = BdMC.subs([(x,x_),(y,y_),(z,z_)])
    gDat = TGraph()
    gMC = TGraph()
    for i in range(100):
        m_ = PDG.Kplus.mass + PDG.piplus.mass + 1 + i*10
        gDat.SetPoint(i,m_,re(fDat.subs(mass,m_).n()).n())
        gMC.SetPoint(i,m_,re(fMC.subs(mass,m_).n()).n())
    gDat.SetLineColor(kGreen)
    gMC.SetLineColor(kRed)
    gDat.SetMinimum(0)
    gMC.SetMinimum(0)
    return gDat,gMC

                      
        
