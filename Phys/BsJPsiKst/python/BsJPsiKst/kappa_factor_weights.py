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
from parameters import *
KpiBins = KpiBins4
#neim = sys.argv[1]
#neim = "2011p_826_861"
CHANNEL = "Bd"
ACC = "DAT"
spins = [0,1]
charge = -1
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
        TristanWeights[key] = Symbol("w_" + str(list(key.atoms())[0]) + str(list(key.atoms())[1]), positive = True)
        TristanIntegral += StrongPhases(key) *  TristanWeights[key]
#BREAK


############################# Average Weights over mKpi#########
from parameters import YieldsBs, YieldsBd

if CHANNEL == "Bs":
    Yields = YieldsBs
    Results = ResultsBs
    from GenParamsBs import *
    W_dat = W70Bs_dat
    W_MC = W70Bs_MC
    CSP70 = 0.6820597803105456
    
if CHANNEL == "Bd":
    Yields = YieldsBd
    Results = ResultsBd
    from GenParamsBd import *
    W_dat = W70Bs_dat
    W_MC = W70Bs_MC
    CSP70 = 0.6818119097667422
if charge > 0 :
    W_dat = W_dat["pos"]
    W_MC = W_MC["pos"]
if charge < 0 :
    W_dat = W_dat["neg"]
    W_MC = W_MC["neg"]

def solve_keys_mess(dic):
    amps = ["0","pa","pe", "S"]
    for i in range(len(amps)):
        a1 = amps[i]
        for j in range(i+1, len(amps)):
            a2 = amps[j]
            if a1+a2 not in dic.keys(): dic[a1+a2] = dic[a2+a1]
            if a2+a1 not in dic.keys(): dic[a2+a1] = dic[a1+a2]
solve_keys_mess(W_dat)
solve_keys_mess(W_MC)
#CSP70 = 1.
W_dat["0S"] = W_dat["0S"] * CSP70
W_dat["S0"] = W_dat["0S"]
W_dat["0pa"] = W_dat["0pa"] * CSP70
W_dat["pa0"] = W_dat["0pa"]
W_dat["0pe"] = W_dat["0pe"] * CSP70
W_dat["pe0"] = W_dat["0pe"]

W_MC["0S"] = W_MC["0S"] * CSP70
W_MC["S0"] = W_MC["0S"] 
W_MC["0pa"] = W_MC["0pa"] * CSP70
W_MC["pa0"] = W_MC["0pa"]
W_MC["0pe"] = W_MC["0pe"] * CSP70
W_MC["pe0"] = W_MC["0pe"]

Apa2 = Results["fpa"]
A02 = Results["fL"]
Ape2 = 1- Results["fL"] - Results["fpa"]
dpa = Results["dpa"]
dpe = Results["dpe"]
Fs = Results["Fs_av"]
dS = Results["ds_av"]



weights_d_dat = []
weights_d_MC = []
for key in TristanWeights.keys():
    if "Abs" in str(key): key2 = str(key).replace("Abs(A_","").replace(")**2","")+str(key).replace("Abs(A_","").replace(")**2","")#]=TristanWeights[key]
    else: key2 = str(key).replace("re(","").replace("im(","").replace("A_","").replace("*conjugate(","").replace("))","")#]=TristanWeights[key]
    print
    ##if "2" in str(key):
##        weights_d_dat.append((TristanWeights[key], 1))
##        weights_d_MC.append((TristanWeights[key], 1))

##    else:
##        weights_d_dat.append((TristanWeights[key], 0))
##        weights_d_MC.append((TristanWeights[key], 0))
    weights_d_dat .append( (TristanWeights[key], W_dat[key2]))
    weights_d_MC .append( (TristanWeights[key], W_MC[key2]))

#>>> eps_dat/eps_MC
#1.01355329165346
#>>> eps_dat/eps_MC
#1.01218366828123


T = TransAmpModuli
P = TransAmpPhases
TristanIntegral_d_dat = TristanIntegral.subs(weights_d_dat)
TristanIntegral_d_MC = TristanIntegral.subs(weights_d_MC)

if ACC == "MC":    
    eps_MC = TristanIntegral_d_MC.subs( [(T["0_0"],0.),(T["1_pa"], sqrt(MCApa2)),(T["1_pe"],sqrt(MCApe2)),(T["1_0"],sqrt(MCA02)),(P["0_0"],0),(P["1_pa"],MCdpa),(P["1_pe"],MCdpe + pi *( charge < 0))])#,(T["2_pa"], 0),(T["2_pe"],0),(T["2_0"],0)])
    eps_dat = TristanIntegral_d_MC.subs( [(T["0_0"],0.),(T["1_pa"], sqrt(Apa2)),(T["1_pe"],sqrt(Ape2)),(T["1_0"],sqrt(A02)),(P["0_0"],0),(P["1_pa"],dpa),(P["1_pe"],dpe + pi *( charge < 0))])#,(T["2_pa"], 0),(T["2_pe"],0),(T["2_0"],0)])
elif ACC == "MCnDAT":
     eps_MC = TristanIntegral_d_MC.subs( [(T["0_0"],0.),(T["1_pa"], sqrt(MCApa2)),(T["1_pe"],sqrt(MCApe2)),(T["1_0"],sqrt(MCA02)),(P["0_0"],0),(P["1_pa"],MCdpa),(P["1_pe"],MCdpe + pi *( charge < 0))])#,(T["2_pa"], 0),(T["2_pe"],0),(T["2_0"],0)])
     eps_dat = TristanIntegral_d_dat.subs( [(T["0_0"],0.),(T["1_pa"], sqrt(Apa2)),(T["1_pe"],sqrt(Ape2)),(T["1_0"],sqrt(A02)),(P["0_0"],0),(P["1_pa"],dpa),(P["1_pe"],dpe + pi *( charge < 0))])#,(T["2_pa"], 0),(T["2_pe"],0),(T["2_0"],0)])

else: 
    eps_dat = TristanIntegral_d_dat.subs( [(T["0_0"],0.),(T["1_pa"], sqrt(Apa2)),(T["1_pe"],sqrt(Ape2)),(T["1_0"],sqrt(A02)),(P["0_0"],0),(P["1_pa"],dpa),(P["1_pe"],dpe + pi *( charge < 0))])#,(T["2_pa"], 0),(T["2_pe"],0),(T["2_0"],0)])
    eps_MC = TristanIntegral_d_dat.subs( [(T["0_0"],0.),(T["1_pa"], sqrt(MCApa2)),(T["1_pe"],sqrt(MCApe2)),(T["1_0"],sqrt(MCA02)),(P["0_0"],0),(P["1_pa"],MCdpa),(P["1_pe"],MCdpe + pi *( charge < 0))])#,(T["2_pa"], 0),(T["2_pe"],0),(T["2_0"],0)])

    
swc_den= TristanIntegral_d_dat.subs( [(T["0_0"],sqrt(Fs)),(T["1_pa"], sqrt((1-Fs)*Apa2)),(T["1_pe"],sqrt((1-Fs)*Ape2)),(T["1_0"],sqrt((1-Fs)*A02)),(P["0_0"],dS),(P["1_pa"],dpa),(P["1_pe"],dpe + pi *( charge < 0))])#,(T["2_pa"], 0),(T["2_pe"],0),(T["2_0"],0)])
#Fs = 0 
swc_num = TristanIntegral_d_dat.subs( [(T["0_0"],sqrt(0)),(T["1_pa"], sqrt((1-Fs)*Apa2)),(T["1_pe"],sqrt((1-Fs)*Ape2)),(T["1_0"],sqrt((1-Fs)*A02)),(P["0_0"],dS),(P["1_pa"],dpa),(P["1_pe"],dpe + pi *( charge < 0))])#,(T["2_pa"], 0),(T["2_pe"],0),(T["2_0"],0)])

swc = swc_num/swc_den#swc_num = (1-Fs)*eps_dat

#kappa= swc/((1-Fs)*eps)   ### As defined in 2015!!!! 

kappa = eps_dat/eps_MC * 1./swc

### Bd, positive
#1.12300928505347

## Bd negative
# 1.14044859007760 --> average 1.11542903805832

#Bs positive
#1.18592652922641

# Bs negative
#1.19110344707963 ---> 1.18851498815302
print kappa 
