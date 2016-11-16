from ROOT import *
from math import *
from array import *
from Urania import PDG
from Urania.Helicity import *
from Urania import RooInterfaces as D
spins = [0,1]
## ### Generate the pdf using the tools in Urania.Helicity
A = doB2VX(spins, helicities = [1,-1], transAmp = 1)#0)
### masage a bit the expression to make it more suitable for fitting
pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())#H.values())
phys = 0
CSP_factors = []
DefineStrongPhases()
SpinMap = { v:k for k,v in TransAmplitudes.items()}

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

    
#BREAK


### change the free variables to cosines
x = Symbol("helcosthetaK",real = True)
y = Symbol("helcosthetaL", real = True)
z = Symbol("helphi", real = True)
CThL = Cos(ThetaL)
CThK = Cos(ThetaK)
def changeFreeVars(function):
    ### Phi now as in DTT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    function  = function.subs( Sin(2*ThetaK), 2*Sin(ThetaK)*Cos(ThetaK))
    function  = function.subs( Cos(2*ThetaK), 2*Cos(ThetaK)**2 - 1)
    function  = function.subs( Sin(ThetaK), Sqrt(1-Cos(ThetaK)**2))
    function  = function.subs( Sin(ThetaL), Sqrt(1-Cos(ThetaL)**2))
    function = function.subs([(CThK,x),(CThL,y), (Phi, -z)])

    return function

func = changeFreeVars(phys)

BREAK
### Replace amplitudes by more suitable fit parameters

s_As2 = Symbol("As2",positive = True)
s_fD = Symbol("fD", positive = True)

s_fL = Symbol("fL",positive = True)
#s_xpa = Symbol("xpa",positive = True)

s_f2L = Symbol("f2L",positive = True)
s_x2pa = Symbol("x2pa",positive = True)

Ad2 = 0.#(1-s_As2)*s_fD
Ap2 = 1-s_As2 - Ad2
s_fpa = Symbol("fpa",positive = True)#s_xpa*(1-s_fL)
fpe = 1-s_fL - s_fpa

s_f2pa = Symbol("f2pa",positive = True) #x2pa*(1-s_f2L)
f2pe = 1-s_f2L - s_f2pa

#func = func.subs( [ (TransAmpModuli["2_pe"], Sqrt(Ad2*f2pe)),(TransAmpModuli["2_pa"], Sqrt(Ad2*f2pa)),(TransAmpModuli["2_0"], Sqrt(Ad2*s_f2L))])
func = func.subs( [(TransAmpModuli["1_pa"], Sqrt(Ap2*s_fpa)),(TransAmpModuli["1_0"], Sqrt(Ap2*s_fL)),(TransAmpModuli["1_pe"], Sqrt(Ap2*fpe))] )
func = func.subs( TransAmpModuli["0_0"],Sqrt(s_As2))
#BREAK

c1_psi = Symbol("c1_psi",real = True)
c2_psi = Symbol("c2_psi",real = True)
c3_psi = Symbol("c3_psi",real = True)
c4_psi = Symbol("c4_psi",real = True)
y_acc = Symbol("y_acc", positive = True)
c2_theta = Symbol("c2_theta", real = True)

c5_psi = -1-c1_psi - c2_psi - c3_psi - c4_psi + y_acc
acc = (1. + c1_psi*x + c2_psi*x*x + c3_psi*x*x*x + c4_psi*x*x*x*x + c5_psi*x*x*x*x*x)*(1.  + c2_theta*y*y)

func = func*acc
### Figure out which variables the fit will depend on

# potential_list = [x,y,z]+TransAmpModuli.values()+TransAmpPhases.values()
potential_list = [x,y,z]+[ s_As2, s_fD, s_fL, s_fpa, s_f2L, s_f2pa ]+TransAmpPhases.values() + CSP_factors + [c1_psi,c2_psi,c3_psi,c4_psi,y_acc, c2_theta]

final_list = []
for thing in potential_list:
    if thing in func.atoms(): final_list.append(thing)
    

### Generate and compile a fitting class corresponding to "func"



op2 = D.RooClassGenerator(func, final_list,"ToyTestAccAngJpsiKpi_J" +str( max(spins)))

op2.addSubstitutions([(Sqrt(-x**2+1),"sthk"),(Sqrt(-y**2+1),"sthl"),((-x**2+1),"sthk2"),((-y**2+1),"sthl2")])

op2.addSubstitutions([(x**2,"cthk2"),(y**2,"cthl2"),(Cos(z)**2,"cosphi2"),(Sin(z)**2,"sinphi2"),(Cos(z),"cosphi"),(Sin(z),"sinphi")])
op2.addSubstitutions([(Sqrt(s_As2),"As")])#,(Sqrt(s_fD),"sqfD")])
op2.addSubstitutions([(Sqrt(s_fL),"sqfL"),(Sqrt(s_fpa),"sqfpa")])
#op2.addSubstitutions([(Sqrt(s_f2L),"sqf2L"),(Sqrt(s_x2pa),"sqx2pa")])
#op2.addSubstitutions([(Cos(TransAmpPhases["2_0"]), "cdelta20"),(Cos(TransAmpPhases["2_pa"]), "cdelta2pa"),(Cos(TransAmpPhases["2_pe"]), "cdelta2pe")])
#op2.addSubstitutions([(Sin(TransAmpPhases["2_0"]), "sdelta20"),(Sin(TransAmpPhases["2_pa"]), "sdelta2pa"),(Sin(TransAmpPhases["2_pe"]), "sdelta2pe")])
op2.addSubstitutions([(Cos(TransAmpPhases["1_pa"]), "cdelta_pa"),(Cos(TransAmpPhases["1_pe"]), "cdelta_pe")])
op2.addSubstitutions([(Sin(TransAmpPhases["1_pa"]), "sdelta_pa"),(Sin(TransAmpPhases["1_pe"]), "sdelta_pe")])
op2.addSubstitutions([(Sin(TransAmpPhases["0_0"]), "sdelta_s"),(Cos(TransAmpPhases["0_0"]), "cdelta_s")])

op2.addSubstitutions([(Sqrt(2),"sq2"),(Sqrt(3),"sq3"),(Sqrt(5),"sq5")])

#op2.addSubstitutions([((-x**2+1),"sthk2"),((-y**2+1),"sthl2"),(x**2,"cthk2"),(y**2,"cthl2"),(Cos(z),"cosphi"),(Sin(z),"sinphi"),(Sqrt(2),"sq2"),(Sqrt(5),"sq5")])
op2.makePdf(integrable = kTRUE)

#zz = integrate(func,(z,-Pi,Pi))

op2.doIntegral(1,(z,-Pi,Pi),(x,-1,1),(y,-1,1))
op2.doIntegralM(2,(x,-1,1),(y,-1,1))
#op2.doIntegralM(3,(z,-Pi,Pi),(x,-1,1))
#op2.doIntegralM(4,(z,-Pi,Pi),(y,-1,1))
#op2.doIntegralM(5,(x,-1,1))
#op2.doIntegralM(6,(y,-1,1))
#op2.doIntegralM(7,(z,-Pi,Pi))

op2.overwrite()
op2.invoke()


BREAK

##############  MAKING TREE


label = 'PLOT'
f=TFile("NewAngleTree.root")
tree=f.Get("T")
f1=TFile("/tmp/trash.root","recreate")
tree1 = tree.CopyTree("MC_k>0")
tree2 = tree.CopyTree("MC_k<0")

###################  CONSTRUCTING THE MODEL

As2 = RooRealVar("As2","As2",0.,1.)
#As = RooFormulaVar("As","As","sqrt(As2)",RooArgList(As2))
fD = RooRealVar("fD","fD",0.,1)

#Ad2 = RooFormulaVar("Ad2","Ad2", "fD*(1-As2)",RooArgList(As2,fD))
#Ap2 = RooFormulaVar("Ap2","Ap2", "(1-fD)*(1-As2)", RooArgList(As2,fD))

fL = RooRealVar("fL","fL",0.,1)
xpa = RooRealVar("xpa","xpa", 0.,1)
#fpa = RooFormulaVar("fpa","fpa","xpa*(1-fL)",RooArgList(xpa,fL))
#fpe = RooFormulaVar("fpe","fpe","(1-xpa)*(1-fL)",RooArgList(xpa,fL))

#A0 = RooFormulaVar("A0","A0","sqrt(Ap2*fL)",RooArgList(Ap2,fL))
#Apa = RooFormulaVar("Apa","Apa","sqrt(Ap2*fpa)",RooArgList(Ap2,fpa))
#Ape = RooFormulaVar("Ape","Ape","sqrt(Ap2*fpe)",RooArgList(Ap2,fpe))

### D-wave polarization fractions

f2L = RooRealVar("f2L","f2L",0.,1)
x2pa = RooRealVar("x2pa","x2pa", 0.,1)
#f2pa = RooFormulaVar("f2pa","f2pa","x2pa*(1-f2L)",RooArgList(x2pa,f2L))
#f2pe = RooFormulaVar("f2pe","f2pe","(1-x2pa)*(1-f2L)",RooArgList(x2pa,f2L))

#A20 = RooFormulaVar("A20","A20","sqrt(Ad2*f2L)",RooArgList(Ad2,f2L))
#A2pa = RooFormulaVar("A2pa","A2pa","sqrt(Ad2*f2pa)",RooArgList(Ad2,f2pa))
#A2pe = RooFormulaVar("A2pe","A2pe","sqrt(Ad2*f2pe)",RooArgList(Ad2,f2pe))


CThetaL = RooRealVar("cL","cos(ThetaL) ", -1,1)
CThetaK = RooRealVar("cK","cos(ThetaK) ", -1,1)
Phi = RooRealVar("ph","Phi", -pi,pi)
#A0 = RooRealVar("A0","A0",0.77,0.5,1.)
#Apa = RooRealVar("Apa","Apa",0.5,0.3,1.)
#Ape  = RooRealVar("Ape" ,"Ape" ,1/2,0.,1.)

#Ape = RooFormulaVar("Ape","Ape","sqrt(1-As*As-Apa*Apa-A0*A0)",RooArgList(A0,As,Apa))
deltaPa = RooRealVar("deltaPa","deltaPa",2.501,2.,2*pi)
deltaPe = RooRealVar("deltaPe","deltaPe",1,  -pi,pi)
deltaS  = RooRealVar("deltaS" ,"deltaS" ,0.9,0.,2*pi)

#A20 = RooRealVar("A0","A0",0.77,0.,1.)
#A2pa = RooRealVar("A2pa","A2pa",0.5,0.,1.)
#A2pe = RooRealVar("A2pe","A2pe",0.5,0.,1.)

#As  = RooRealVar("As" ,"As" ,1/2,0.,1.)

#As = RooFormulaVar("As","As","sqrt(1-Ape*Ape-Apa*Apa-A0*A0-A2pe*A2pe-A2pa*A2pa-A20*A20)",RooArgList(A0,Ape,Apa,A20,A2pa,A2pe))
delta2Pa = RooRealVar("delta2Pa","delta2Pa",2.501,2.,2*pi)
delta2Pe = RooRealVar("delta2Pe","delta2Pe",1,  -pi,pi)
delta20  = RooRealVar("delta20" ,"delta20" ,0.9,0.,2*pi)

#model=RooFirst("model","model",CThetaK,CThetaL,Phi,As2,
model2=AngJpsiKpi_J1("model2","model2",CThetaK,CThetaL,Phi,As2,fL,xpa,deltaPa,deltaPe,deltaS)
## As2.setVal(1)
## fr = CThetaK.frame()
## model2.plotOn(fr)
## fr.Draw()

## BREAK
###################  FITTING DATA

  ### tree - mix of B & Bbar
  ### tree1 - K+
  ### tree2 - K-

data = RooDataSet(label, label,tree1,RooArgSet(CThetaL,CThetaK,Phi))
#data = model.generate(RooArgSet(CThetaL,CThetaK,Phi),100000) ;

#As.setVal(0)
#As.setConstant(kTRUE)
#deltaS.setConstant(kTRUE)
#deltaPe.setConstant(kTRUE)


def test(model):
    res = model.fitTo(data,RooFit.Minos(kTRUE))#, RooFit.Range("REDUCED"))
    Angframe = CThetaK.frame()
    data.plotOn(Angframe)
    model.plotOn(Angframe)
    Angframe.Draw()
    return res, Angframe

#w_1 = test(model)
w_2 = test(model2)

################ DRAWING 
