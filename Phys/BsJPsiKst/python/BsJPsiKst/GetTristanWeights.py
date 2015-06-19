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

#neim = sys.argv[1]
#neim = "2011p_826_861"
#t,fp = getTuple("~/w7folder/NTuples/Bs_Jpsi_Kst_2013/MC/Carlos_newsel_Bd/" + neim, thing = "DecayTree")

spins = [0,1,2]
## ### Generate the pdf using the tools in Urania.Helicity
A = doB2VX(spins, helicities = [1,-1], transAmp = 1)#0)
### masage a bit the expression to make it more suitable for fitting
pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())#H.values())

def TristanWeightsCalculator(charge,bin_min,bin_max):

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

    #
    #phys = changeFreeVars(phys)


    #BREAK
    T = TransAmpModuli
    P = TransAmpPhases
    #MCApa2 = 0.239642556091464
    #MCApe2 = 0.160002603586681
    #MCA02 = 1.-MCApa2-MCApe2
    #MCdpa = 2.50094515356931
    #MCdpe = -0.170317122058993
    MCApa2 = 0.
    MCApe2 = 0.
    MCA02 = 0.
    MCApa22 = 0.
    MCApe22 = 0.
    MCA022 = 0.
    MCdpa = 0.
    MCdpe = 0.
    MCd02 = 0.
    MCdpa2 = 0.
    MCdpe2 = 0.

    if (charge > 0): charge_name = "p"
    else: charge_name = "n"
    bin_name = str(bin_min) + "_" + str(bin_max)

    t,fp = getTuple("/home/galaceos/cmtuser/URANIA/URANIA_HEAD/Phys/BsJPsiKst/ntuples/BdJpsiKpi_MC_BDTG_2012" + charge_name + "_" + bin_name, thing = "DecayTree")

    t.GetEntry(1)
    charge = t.Kplus_ID

    phys = phys.subs([(T["0_0"],1.),(T["1_pa"], sqrt(MCApa2)),(T["1_pe"],sqrt(MCApe2)),(T["1_0"],sqrt(MCA02)),(T["2_pa"], sqrt(MCApa22)),(T["2_pe"],sqrt(MCApe22)),(T["2_0"],sqrt(MCA022)),(P["0_0"],0),(P["1_pa"],MCdpa),(P["1_pe"],MCdpe + pi *( charge < 0)),(P["2_0"],MCd02),(P["2_pa"],MCdpa2),(P["2_pe"],MCdpe2 + pi *( charge < 0))])### Set PDF to MC-T parameters
    func = lambdify( (x,y,z), phys, ("numpy"))### Lambdify it to make it faster.

    #else: t,fp = getTuple(NTUPLE_PATH + "/MC/Bd_2012n", thing = "DecayTree")
    #t,fp = getTuple(NTUPLE_PATH + "/MC/Bd_MCT_p")


    N = 0.
    for i in range(t.GetEntries()): ### This is f[..]king suboptimal in terms of speed
        t.GetEntry(i)
        #sublist = [(x,t.helcosthetaK), (y,t.helcosthetaL),(z,t.B0_Phi)]
        #ck, cl, ph = t.cK, t.cL, t.ph
        ck, cl, ph = t.helcosthetaK, t.helcosthetaL, t.B0_Phi
        val = func(ck,cl,ph)
        for key in TristanWeights:  TristanWeights[key] += lam_pdf_split[key](ck,cl,ph)*1./val
        N+=1
        #print N*1./t.GetEntries()
    #print "-_-"

    out = {}
    #trans = {0:"pe2", 1:"SS",2:"0pe",3:"Spe",4:"pape",5:"pa2",6:"Spa",7:"0pa",8:"S0",9:"00"}
    #keys = TristanWeights.keys()
    #out2 = {}
    #for i in range(10):
    #    key = keys[i]
    #    TristanWeights[key] =  TristanWeights[key]*1./N
    #    out[trans[i]] = TristanWeights[key]

    #out2[key] = TristanWeights[key]
    #    print key, trans[i]

    for key in TristanWeights.keys():
    	if "Abs" in str(key): out[str(key).replace("Abs(A_","").replace(")**2","")+str(key).replace("Abs(A_","").replace(")**2","")]=TristanWeights[key]*1./N
	else: out[str(key).replace("re(","").replace("im(","").replace("A_","").replace("*conjugate(","").replace("))","")]=TristanWeights[key]*1./N

    return 'WeightsBdKpi["2012' + charge_name + "_" + bin_name + '"] = ' + str(out)

limits = [826, 861, 896, 931, 966, 1001, 1036, 1071, 1106, 1141, 1176, 1211, 1246, 1281, 1316, 1351, 1386, 1421, 1456, 1491, 1526, 1561, 1596, 1631]

printout = ""

for i in range(23): printout += TristanWeightsCalculator(1,limits[i],limits[i+1]) + "\n\n"
for i in range(23): printout += TristanWeightsCalculator(-1,limits[i],limits[i+1]) + "\n\n"

f_out = file("TristanWeightValues.dat","w")
f_out.write(printout)
f_out.close()

#print "CHARGE: " , charge
#print out2
## -_-
## Abs(A_pe)**2 1.24115524992
## Abs(A_S)**2 1.08084712382
## im(A_pe*conjugate(A_0)) 0.0354274550029
## im(A_pe*conjugate(A_S)) -0.0103549953064
## im(A_pa*conjugate(A_pe)) -0.228343837674
## Abs(A_pa)**2 1.23202826064
## re(A_pa*conjugate(A_S)) -0.0344646385104
## re(A_pa*conjugate(A_0)) -0.0121409333661
## re(A_S*conjugate(A_0)) -0.843000710897
## Abs(A_0)**2 0.873259568729
## >>>
