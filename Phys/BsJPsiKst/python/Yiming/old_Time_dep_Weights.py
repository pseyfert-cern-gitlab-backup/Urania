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

#t,fp = getTuple("~/w7folder/NTuples/Bs_Jpsi_Kst_2013/MC/Carlos_newsel_Bd/" + neim, thing = "DecayTree")

fp = TFile("~diegoms/vol5/BsJpsiPhi/MC/Bs2JpsiPhi_MC2012_ntupleB_20130904_smeared_sel.root")
t_1 = fp.Get("DecayTree")
### TRUEID !
### Substitute by Jpsi Phi MC tuple
fnew = TFile("~/newforMCtureid.root","recreate")
t= t_1.CopyTree("((mdau2-1020)<20)&&((mdau2-1020)>-20)&&trueid==531")
t.GetEntry(1)
spins = [0,1]
## ### Generate the pdf using the tools in Urania.Helicity
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

### Need values for the weak phases --> ask me
MCA02 = 0.5213
MCApe2 = 0.249
MCApa2 = 1-MCA02-MCApe2
MCAs2 =0
MCGamma = 0.6653
MCphi = 0.07
MCDG = 0.0917 ### Delta Gamma ### 0.08 -- 0.1
MCDMS = 17.8 ### Delta MS
MCdpa = 3.30
MCdpe = 3.07
MCdeltaS = 0
WP = WeakPhases

print "I am here"
lam_pdf_split = {}

### MC True values of the parameters
T = TransAmpModuli
P = TransAmpPhases

my_sublist = [(T["0_0"],0.),(T["1_pa"], sqrt(MCApa2)),(T["1_pe"],sqrt(MCApe2)),(T["1_0"],sqrt(MCA02)),(P["0_0"],0),(P["1_pa"],MCdpa),(P["1_pe"],MCdpe),(DM,MCDMS),(DG,MCDG),(Gamma,MCGamma),(WP["1_0"],MCphi),(WP["1_pa"],MCphi), (WP["1_pe"],MCphi - pi),(WP["0_0"],0)]

my_time_exp = {}
for key in pdf_split:
    pdf_split[key] = changeFreeVars(pdf_split[key])
    if not pdf_split[key] : continue
    my_time_exp[key] = timeExpression(key, time_mod_list)*StrongPhases(key)
    phys += my_time_exp[key]*pdf_split[key] ### will need to make it time dependdent
    if pdf_split[key]:
        lam_pdf_split[key] = lambdify((x,y,z,time), pdf_split[key], ("numpy"))   ### Lambdify the 10 f_i's it to make it faster. ## Check in bibliography if the f_i (pdf_split[key]) are evaluated as time dependent, or is only the ful pdf in the denominator
        TristanWeights[key] = 0#  Symbol("w_" + str(list(key.atoms())[0]) + str(list(key.atoms())[1]), positive = True)
        #TristanIntegral += StrongPhases(key) *  TristanWeights[key]
        
        
print "Now I am here"
#
#phys = changeFreeVars(phys)


BREAK


phys = phys.subs(my_sublist)### Set PDF to MC-T parameters
func = lambdify( (x,y,z,time), phys, ("numpy"))### Lambdify it to make it faster.

#else: t,fp = getTuple(NTUPLE_PATH + "/MC/Bd_2012n", thing = "DecayTree")
#t,fp = getTuple(NTUPLE_PATH + "/MC/Bd_MCT_p")


N = 0.
for i in range(t.GetEntries()): ### This is f[..]king suboptimal in terms of speed
    t.GetEntry(i)
    #sublist = [(x,t.helcosthetaK), (y,t.helcosthetaL),(z,t.B0_Phi)]
    #ck, cl, ph = t.cK, t.cL, t.ph
    ck, cl, ph, ct = t.helcosthetaK, t.helcosthetaL, t.B_phi, t.time
    val = func(ck,cl,ph,ct)
    for key in TristanWeights:  TristanWeights[key] += lam_pdf_split[key](ck,cl,ph,ct)*1./val
    N+=1
    print N*1./t.GetEntries()
print "-_-"
out = {}
trans = {0:"pe2", 1:"SS",2:"0pe",3:"Spe",4:"pape",5:"pa2",6:"Spa",7:"0pa",8:"S0",9:"00"}
keys = TristanWeights.keys()
out2 = {}
for i in range(len(keys)):
    key = keys[i]
    TristanWeights[key] =  TristanWeights[key]*1./N
    
    #out2[key] = TristanWeights[key]
    print key, TristanWeights[key]


#Nexp = 0
#for key in TristanWeights.keys():  
#    Nexp += TristanWeights[key]*my_time_exp[key]
#print  Nexp
#f = file("Nexp_formula2", "w")
#import cPickle
#cPickle.dump(Nexp, f)
#f.close()

#Nchange = Nexp.subs(my_sublist)
#f3 = file("N_changevalues","w")
#import cPickle
#cPickle.dump(Nchange, f3)
#f3.close
