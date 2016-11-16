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

spins = [0,1]
A = doB2VX(spins, helicities = [1,-1], transAmp = 1)#0)
### masage a bit the expression to make it more suitable for fitting
pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())#H.values())
phys = 0
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

### MC amplitudes values are same as in these Time_dep_Weights.py and s-wave values are a paper. Data amplitudes values are from results of data_fit.py.
#MC:Fs = 0.016
#MC:Fs=0.227

A02 =  0.491 # MC: 0.521
Ape2 = 0.277 # MC :0.249
Apa2 = 1-A02-Ape2
As2_pwave =0
As2_total = 0.00234 #MC:Fs/(1-Fs)
dataGamma = 0.560 #MC: 0.663
#phi =   # use phi0 not phiS   MC:0.07
phi0= -0.228  #new
phiS= 0.582   # new
dataDG = 0.0516 #MC: 0.100 ### Delta Gamma
DMS = 18.47 #MC: 17.70 ### Delta MS
dpa = 3.24 #MC: 3.30
dpe = -2.67  #MC:3.07
deltaS_pwave = 0
deltaS_total = -1.23  #MC:dpe - 0.51 
WP = WeakPhases

T = TransAmpModuli
P = TransAmpPhases

pwave_sublist = [(T["0_0"],sqrt(As2_pwave)),(T["1_pa"], sqrt(Apa2)),(T["1_pe"],sqrt(Ape2)),(T["1_0"],sqrt(A02)),(P["0_0"],deltaS_pwave),(P["1_pa"],dpa),(P["1_pe"],dpe),(DM,DMS),(DG,dataDG),(Gamma,dataGamma),(WP["1_0"],phi0),(WP["1_pa"],phi0), (WP["1_pe"],phi0-pi),(WP["0_0"],0)]

total_sublist= [(T["0_0"],sqrt(As2_total)),(T["1_pa"], sqrt(Apa2)),(T["1_pe"],sqrt(Ape2)),(T["1_0"],sqrt(A02)),(P["0_0"],deltaS_total),(P["1_pa"],dpa),(P["1_pe"],dpe),(DM,DMS),(DG,dataDG),(Gamma,dataGamma),(WP["1_0"],phi0),(WP["1_pa"],phi0), (WP["1_pe"],phi0-pi),(WP["0_0"],phi0)] 

import cPickle
f = file("Nexp_formula")
#f2 = file("changeTweight_Nexp")  #this is using the result of change_Tweight_examine.py to examine if this program is right by set Tweight[00]=1,[11]=1,[01]=[10]=0
N_exp=cPickle.load(f)

a= 1.41575e-01
b= 6.92361e-01
c= 5.64767e+03
#sigma_value=c*x^a/(1+b*x^a)

sigma_value= TF1("sigma_value","[2]*x^[0]/(1+[1]*x^[0])",0.3,14)
sigma_value.SetParameters(a,b,c)

N_pwave = N_exp.subs(pwave_sublist)
N_total = N_exp.subs(total_sublist)

inte_pwave =0
inte_total =0

for i in range(3,140):
    t_ = 0.1*i+0.05
    inte_pwave += N_pwave.subs(time,t_)*sigma_value(t_)*0.1
    inte_total += N_total.subs(time,t_)*sigma_value(t_)*0.1

print "inte_pwave="
print inte_pwave
print "inte_total="
print inte_total

frac_N = inte_pwave/inte_total

print "frac_N"
print frac_N

f2.close()
