from ROOT import *
from Urania.Helicity import *
from Urania.Time import *
from Urania.LatexFunctions import *
from os import system
from Urania import RooInterfaces as D
#ta = Symbol("t_a", real = True)
#tb = Symbol("t_b", real = True)
#tc = Symbol("t_c", real = True)
#td = Symbol("t_d", real = True)


A = doB2VX([0,1], helicities = [1,-1], transAng = 0)
pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())#H.values())
phys = 0

def DefineWeakPhases(free_delta0 = 0):
    for key in TransAmplitudes:
        amp = str(TransAmplitudes[key])
        #name = str(amp)
        if key not in Lambdas.keys(): Lambdas[key] = One#USymbol("landa" + amp.replace("A",""), "\\|\\lambda\\|" + amp.replace("A",""),positive = True)
        if key not in WeakPhases.keys(): WeakPhases[key] = USymbol("phi"+ amp.replace("A",""), "\\Phi" + amp.replace("A",""),real = True)
    #if not free_delta0: TransAmpPhases.pop("1_0")

free_delta0 = 1
DefineStrongPhases(free_delta0)
DefineWeakPhases(free_delta0)
#### Rotate CP = -1 phases for consistency with Note's notation
#WeakPhases["0_0"] += Pi 
#WeakPhases["1_pe"] += Pi

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
    function = function.subs([(CThK,x),(CThL,y), (Phi,z)])

    return function
  
TristanWeights = {}
phys = 0
reco = 0
print "(0_0)"
#BREAK
integral = 0
for key in pdf_split:
    if not pdf_split[key] : continue
    Amp1 = list(key.atoms())[0]
    Amp2 = list(key.atoms())[1]
    wname = "w_" + str(Amp1) + str(Amp2)
    wname = wname.replace("A_","")
    TristanWeights[key] =  Symbol(wname, positive = True)
    phys +=  timeExpressionBbar(key)* pdf_split[key]
    integral += timeExpressionBbar(key) *  TristanWeights[key]
     
    #phys +=  timeExpression(key,ta,tb,tc,td)* pdf_split[key]
    #integral += timeExpression(key,ta,tb,tc,td) *  TristanWeights[key]
    #phys +=  timeExpressionBbar(key)* pdf_split[key]
    #integral += timeExpressionBbar(key) *  TristanWeights[key]

#reco = changeFreeVars(reco)
phys = changeFreeVars(phys)

#sublist += [(gplus,gplus_eq), (gminus,gminus_eq)]
#phys = phys.subs(sublist)
#reco = reco.subs(sublist)

#timesubs = [( GL, Gamma+One/2*DG), ( GH, Gamma-One/2*DG), ( mH, mB+One/2*DM), ( mL, mB-One/2*DM)]
print "-_-"
#reco = simplify(reco.subs(timesubs))
#phys = phys.subs(timesubs)

potential_list = [x,y,z,time]  +  TransAmpModuli.values() + TransAmpPhases.values() + WeakPhases.values() +[ Gamma , DG ,DM] + TristanWeights.values()  #+ Lambdas.values()
final_list = []
#BREAK
for thing in potential_list:
    if (thing in phys.atoms() or thing in integral.atoms()) and thing not in final_list: final_list.append(thing)

op = D.RooClassGenerator(phys, final_list, "NewTristanPhisFitBbar")
op.addSubstitutions([(x**2, "x2"), (y**2,"y2"), (Exp(-Gamma*time), "exp_G_t"), (Cos(DM*time), "cdmt"), (Sin(DM*time),"sdmt"), (Cosh(DG*time/2), "cosh_term"),(Sinh(DG*time/2), "sinh_term") ])
op.makePdf( integrable = kTRUE )
print "I am here"
#zz = iter_integrate(phys,(z,-Pi,Pi),(x,-1,1),(y,-1,1))
print "Now there"
kappa = iter_integrate(integral, (time,Symbol("t_0",positive = True), Symbol("t_1",positive = True)))
op.forceIntegral(1,[x,y,z,time],kappa)
#op.doIntegral(1, (time, Symbol("t_0",positive = True), Symbol("t_1",positive = True)), (z,-Pi,Pi),(x,-1,1),(y,-1,1))

op.forceIntegral(2,[x,y,z],integral)


#op.doIntegral(2, (z,-Pi,Pi),(x,-1,1),(y,-1,1))
op.overwrite()
from os import system as shell
shell ("cp New* ~/vol5/")



op.invoke()
           
###free_delta0 = 1
