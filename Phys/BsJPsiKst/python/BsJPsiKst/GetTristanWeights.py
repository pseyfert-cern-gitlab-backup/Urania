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
from parameters import KpiBins4 as Kpibins
#neim = sys.argv[1]
#neim = "2011p_826_861"

spins = [0,1,2]
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
        TristanWeights[key] = 0#  Symbol("w_" + str(list(key.atoms())[0]) + str(list(key.atoms())[1]), positive = True)
        #TristanIntegral += StrongPhases(key) *  TristanWeights[key]

T = TransAmpModuli
P = TransAmpPhases
MCApa2 = 0.239642556091464
MCApe2 = 0.160002603586681
MCA02 = 1.-MCApa2-MCApe2
MCdpa = 2.50094515356931
MCdpe = -0.170317122058993

def CalculateWeights(neim):
    t,fp = getTuple("~/NTuplesFast/carlosNewSel/2011" + neim, thing = "DecayTree")
    t2,fp2 = getTuple("~/NTuplesFast/carlosNewSel/2012" + neim, thing = "DecayTree")
    t.GetEntry(1)
    charge = t.Kplus_ID
    if charge < 0 and "p" in neim: cancer
    if charge > 0 and "n" in neim: cancer
    my_phys = phys.subs([(T["0_0"],0.),(T["1_pa"], sqrt(MCApa2)),(T["1_pe"],sqrt(MCApe2)),(T["1_0"],sqrt(MCA02)),(P["0_0"],0),(P["1_pa"],MCdpa),(P["1_pe"],MCdpe + pi *( charge < 0)),(T["2_pa"], 0),(T["2_pe"],0),(T["2_0"],0)])### Set PDF to MC-T parameters
    
    func = lambdify( (x,y,z), my_phys, ("numpy"))### Lambdify it to make it faster.
    N, N2  = 0., 0.
    for i in range(t.GetEntries()): ### This is f[..]king suboptimal in terms of speed
        t.GetEntry(i)
        ck, cl, ph = t.helcosthetaK, t.helcosthetaL, t.B0_Phi
        val = func(ck,cl,ph)
        for key in TristanWeights:  TristanWeights[key] += lam_pdf_split[key](ck,cl,ph)*1./val
        N+=1
        print (N + N2)*1./(t.GetEntries() + t2.GetEntries())
    for i in range(t2.GetEntries()): ### This is f[..]king suboptimal in terms of speed
        t2.GetEntry(i)
        ck, cl, ph = t2.helcosthetaK, t2.helcosthetaL, t2.B0_Phi
        val = func(ck,cl,ph)
        for key in TristanWeights:  TristanWeights[key] += lam_pdf_split[key](ck,cl,ph)*1./val
        N2+=1
        print (N + N2)*1./(t.GetEntries() + t2.GetEntries())
    print "-_-"
    out = {}

    for key in TristanWeights.keys():
        TristanWeights[key] *=1./N
        if "Abs" in str(key): out[str(key).replace("Abs(A_","").replace(")**2","")+str(key).replace("Abs(A_","").replace(")**2","")]=TristanWeights[key]
        else: out[str(key).replace("re(","").replace("im(","").replace("A_","").replace("*conjugate(","").replace("))","")]=TristanWeights[key]
    NF = out['00']
    for key in out.keys(): out[key] *= 1./NF
    print "CHARGE: " , charge
    return out

f = file("weights_dms.py","w")
f.write("WeightsBd = {}\n")
for i in range(len(Kpibins)-1):
    neim = "p_"  + str(Kpibins[i]) + "_" + str(Kpibins[i+1])
    out = CalculateWeights(neim)
    f.write("WeightsBd['2011"+neim + "'] = " + str(out) + "\n")
    f.write("WeightsBd['2012"+neim + "'] = " + str(out) + "\n")
    neim = "n_"  + str(Kpibins[i]) + "_" + str(Kpibins[i+1])
    out = CalculateWeights(neim)
    f.write("WeightsBd['2011"+neim + "'] = " + str(out) + "\n")
    f.write("WeightsBd['2012"+neim + "'] = " + str(out) + "\n")
    
f.close()

                           
    
