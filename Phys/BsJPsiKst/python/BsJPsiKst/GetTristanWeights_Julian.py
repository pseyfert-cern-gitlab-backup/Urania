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

spins = [0,1,2]
## ### Generate the pdf using the tools in Urania.Helicity
A = doB2VX(spins, helicities = [1,-1], transAmp = 1)#0)
### masage a bit the expression to make it more suitable for fitting
pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())#H.values())

def TristanWeightsCalculator(charge,bin_min,bin_max):

    TristanIntegral = 0
    TristanWeights = {}
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
        if pdf_split[key]:
            lam_pdf_split[key] = lambdify((x,y,z), pdf_split[key], ("numpy"))   ### Lambdify it to make it faster.
            TristanWeights[key] = 0

    if (charge > 0): charge_name = "p"
    else: charge_name = "n"
    bin_name = str(bin_min) + "_" + str(bin_max)

    #t,fp = getTuple("/afs/cern.ch/user/j/jugarcia/cmtuser/Bs2JPsiKst/MC_ntuples/BdJpsiKpi_MC_BDTG_2012" + charge_name + "_" + bin_name, thing = "DecayTree")
    fp = TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/user/j/jugarcia/MC_ntuples/BdJpsiKpi_MC_BDTG_2012" + charge_name + "_" + bin_name + ".root")
    t = fp.Get("DecayTree")

    t.GetEntry(1)
    charge = t.Kplus_ID

    N = 0.
    for i in range(t.GetEntries()):
        t.GetEntry(i)
        ck, cl, ph = t.helcosthetaK, t.helcosthetaL, t.B0_Phi
        for key in TristanWeights:  TristanWeights[key] += lam_pdf_split[key](ck,cl,ph) ### Note that the generated spectrum of the MC is flat in ck, cl and ph.
        N+=1

    out = {}

    for key in TristanWeights.keys():
	if (str(key)=="Abs(A_S)**2"): norm = 1./TristanWeights[key] ### Normalization to the weight of the |A_S|^2 term.

    for key in TristanWeights.keys():
    	if "Abs" in str(key): out[str(key).replace("Abs(A_","").replace(")**2","")+str(key).replace("Abs(A_","").replace(")**2","")]=TristanWeights[key]*norm
	else: out[str(key).replace("re(","").replace("im(","").replace("A_","").replace("*conjugate(","").replace("))","")]=TristanWeights[key]*norm

    return 'WeightsBdKpi["2012' + charge_name + "_" + bin_name + '"] = ' + str(out)

limits = [826, 861, 896, 931, 966, 1001, 1036, 1071, 1106, 1141, 1176, 1211, 1246, 1281, 1316, 1351, 1386, 1421, 1456, 1491, 1526, 1561, 1596, 1631]

printout = ""

for i in range(23): printout += TristanWeightsCalculator(1,limits[i],limits[i+1]) + "\n\n"
for i in range(23): printout += TristanWeightsCalculator(-1,limits[i],limits[i+1]) + "\n\n"

f_out = file("TristanWeightValues.dat","w")
f_out.write(printout)
f_out.close()
