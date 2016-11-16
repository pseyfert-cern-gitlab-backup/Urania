from ROOT import *
from math import *
from array import *
from Urania import PDG
from Urania.Helicity import *
from Urania import RooInterfaces as D
from Urania import *
from Urania.Time import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from sympy.utilities.lambdify import lambdify
from Urania.LatexFunctions import *
from os import system
from Urania import RooInterfaces as D

### Substitute by Jpsi Phi MC tuple

spins = [0,1]
## ### Generate the pdf using the tools in Urania.Helicity
A = doB2VX(spins, helicities = [1,-1], transAmp = 1)#0)
### masage a bit the expression to make it more suitable for fitting
pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())#H.values())
def DefineWeakPhases(free_delta0 = 0):
    for key in TransAmplitudes:
        amp = str(TransAmplitudes[key])
        #name = str(amp)
        if key not in Lambdas.keys(): Lambdas[key] = One#USymbol("landa" + amp.replace("A",""), "\\|\\lambda\\|" + amp.replace("A",""),positive = True)
        if key not in WeakPhases.keys(): WeakPhases[key] = USymbol("phi"+ amp.replace("A",""), "\\Phi" + amp.replace("A",""),real = True)
    #if not free_delta0: TransAmpPhases.pop("1_0")

free_delta0 = 0
DefineStrongPhases(free_delta0)
DefineWeakPhases(free_delta0)

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
time_mod_list = defineTimeModList(TransAmpModuli,TransAmpPhases,Lambdas,WeakPhases)

print "I am here"

my_time_exp = {}
for key in pdf_split:
    pdf_split[key] = changeFreeVars(pdf_split[key])
    if not pdf_split[key] : continue
    my_time_exp[key] = timeExpression(key, time_mod_list)*StrongPhases(key)
    if pdf_split[key]: TristanWeights[key] = 0#
                
print "Now I am here"
#
keys = TristanWeights.keys()
for i in range(len(keys)):
    key = keys[i]
    if "Abs"in str(key) : TristanWeights[key]=1
    else : TristanWeights[key]=0
    print key, TristanWeights[key]


Nexp = 0
for key in TristanWeights.keys():  
    Nexp += TristanWeights[key]*my_time_exp[key]
print  Nexp

f = file("changeTweight_Nexp", "w")
import cPickle
cPickle.dump(Nexp, f)
f.close()

 #this is to examine if this program is right by set Tweight[00]=1,[11]=1,[01]=[10]=0. results used in calc_effi.py
