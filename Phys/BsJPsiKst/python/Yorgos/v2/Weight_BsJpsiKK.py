from ROOT import *
from math import *
from Urania.Helicity import *
from sympy import lambdify
from SomeUtils.alyabar import HelicityAngles
from array import array
from Urania.MassAmplitudes import *
from sympy import re


##############################################################################
#      This script does not containt the term (1-Y**2) in the old pdf
#      The sum of the normalized weigths in this script is:660 the expected is 1284
#
##############################################################################




################################################################################
#                 Constant Values                                              #
################################################################################

particle_list=["kaons","pions"]

As2 = { 'A_2pe':sqrt(2.55) * e**0.0J , 'A_2pa':sqrt(2.55)* e**0.0J , 'A_20':sqrt(9.9) * e**0.0J }
As1 = { 'A_pe':sqrt(17.3) * e**0.0J , 'A_pa':sqrt(17.3) * e**0.0J , 'A_0':sqrt(32.1) * e**0.0J }
As0 = { 'A_S' :sqrt(12.0) * e**-4.6J }


Mmin = 2*PDG.Kplus.mass
Mmax = PDG.Bs.mass - PDG.Jpsi.mass


my_spins = [0,1,2]
A = doB2VX(my_spins,[1,-1])
M=Symbol('M', positive = True)

def setmass(particle):
    if particle == particle_list[0]:
        return pow(493.667,2)
    elif particle == particle_list[1]:
        return pow(139.570,2)
    else: raise Exception(" i dont know this particle")


################################################################################
#             Breight - Wigner and Flatte                                      #
################################################################################

def MW1(m):return 1./(m**2 - pow(1019.445,2) - 1019.445 * 4.26J)
def MW2(m):return 1./(m**2 - pow(1525,2) - 1525 * 76J)
func=lambdify(mass,f0_Syr,("numpy"))

################################################################################
#             PDF for Spin 0,1,2                                               #
################################################################################

Aprime=A.subs([(TransAmplitudes['0_0'],TransAmplitudes['0_0'] * func(M)),(TransAmplitudes['1_0'],TransAmplitudes['1_0']*MW1(M)), (TransAmplitudes['1_pa'],TransAmplitudes['1_pa']*MW1(M)),(TransAmplitudes['1_pe'],\
TransAmplitudes['1_pe']*MW1(M)),(TransAmplitudes['2_0'],TransAmplitudes['2_0']*MW2(M)),(TransAmplitudes['2_pa'],TransAmplitudes['2_pa']*MW2(M)),(TransAmplitudes['2_pe'],TransAmplitudes['2_pe']*MW2(M))])


x = Symbol("helcosthetaK",real = True)
y = Symbol("helcosthetaL", real = True)
z = Symbol("helphi", real = True)
CThL = Cos(ThetaL)
CThK = Cos(ThetaK)
def changeFreeVars(function):
    function  = function.subs( Sin(2*ThetaK), 2*Sin(ThetaK)*Cos(ThetaK))
    function  = function.subs( Cos(2*ThetaK), 2*Cos(ThetaK)**2 - 1)
    function  = function.subs( Sin(ThetaK), Sqrt(1-Cos(ThetaK)**2))
    function  = function.subs( Sin(ThetaL), Sqrt(1-Cos(ThetaL)**2))
    function = function.subs([(CThK,x),(CThL,y), (Phi, -Pi -z)])
    return function


def add_stuff( tuple, *l): return tuple+l
Aprime = changeFreeVars(Aprime)
l = TransAmplitudes.values()
Afunc = lambdify( add_stuff((x,y,z,M), *l), Aprime , ("numpy"))

###############################################################################
#              Invariant mass of the system X                                 #
###############################################################################                                                                                                                                                                                                  
def System_Mass(filename,particle):
    f_MC_data_1 = TFile(filename,"update")
    f_MC_tree_1 = f_MC_data_1.Get("DecayTree")

    M_addr=array('f',[0])
    MBranch_M=f_MC_tree_1.Branch("Inv_mass", M_addr,"Inv_mass/F")
    mass_sqrt = setmass(particle)
    print "X system--> " + particle
    print "particle mass = ", sqrt(mass_sqrt)," MeV"
    for entry in range(int(f_MC_tree_1.GetEntries())):
        f_MC_tree_1.GetEntry(entry)
        px_minus_power_2=pow(f_MC_tree_1.piminus_PX,2)
        py_minus_power_2=pow(f_MC_tree_1.piminus_PY,2)
        pZ_minus_power_2=pow(f_MC_tree_1.piminus_PZ,2)
        p_minus_power_2=px_minus_power_2 +  py_minus_power_2 + pZ_minus_power_2
        px_kplus_power_2=pow(f_MC_tree_1.Kplus_PX,2)
        py_kplus_power_2=pow(f_MC_tree_1.Kplus_PY,2)
        pZ_kplus_power_2=pow(f_MC_tree_1.Kplus_PZ,2)
        p_kplus_power_2=px_kplus_power_2 +  py_kplus_power_2 + pZ_kplus_power_2
        p_minus_p_kplus=f_MC_tree_1.piminus_PX*f_MC_tree_1.Kplus_PX + f_MC_tree_1.piminus_PY*f_MC_tree_1.Kplus_PY + f_MC_tree_1.piminus_PZ*f_MC_tree_1.Kplus_PZ
        m = mass_sqrt
        Invariant_Mass=pow(2*m + 2*pow(m + p_minus_power_2,0.5)*pow(m + p_kplus_power_2,0.5)-2*p_minus_p_kplus,0.5)
        M_addr[0]=Invariant_Mass
        MBranch_M.Fill()
    f_MC_tree_1.Write("",TObject.kOverwrite)
    f_MC_data_1.Close()

################################################################################
#             weights and Normalized weights                                   #
################################################################################
                                                                                                                                                                                                             
def weights(filename):
    f_MC_data_1 = TFile(filename , "update")
    f_MC_tree_1 = f_MC_data_1.Get("DecayTree")
    
    tha1_addr= array('f',[0])
    tha1_Branch = f_MC_tree_1.Branch("thita_1", tha1_addr,"thita_1/F")
    
    tha2_addr= array('f',[0])
    tha2_Branch = f_MC_tree_1.Branch("thita_2", tha2_addr,"thita_2/F")
    
    tha3_addr= array('f',[0])
    tha3_Branch = f_MC_tree_1.Branch("thita_3", tha3_addr,"thita_3/F")
    
    weight_addr= array('f',[0])
    weight_Branch = f_MC_tree_1.Branch("weights", weight_addr,"weights/F")
    
    Norm_weight_addr = array('f',[0])
    Norm_weight_Branch = f_MC_tree_1.Branch("Norm_weights",Norm_weight_addr,"Norm_weights/F")

################################################################################
#                    Normalization Constant                                    #
################################################################################

    def norm_BW():
        Sum=0
        Nbins = 1000
        dm = (Mmax - Mmin)*1./Nbins
        for i in range(Nbins):
            m = Mmin + i*dm
            thingie = func(m + 0J)
            Number=(thingie*thingie.conjugate()).real
            Sum=Sum+Number*dm
        return Sum
    B0=norm_BW()
    NB_0=pow(B0,-0.5)

    def norm_BW1():
        Sum=0
        Nbins = 1000
        dm = (Mmax - Mmin)*1./Nbins
        for i in range(Nbins):
            m = Mmin + i*dm
            thingie = MW1(m)
            Number=(thingie*thingie.conjugate()).real
            Sum=Sum+Number*dm
        return Sum
    B1=norm_BW1()
    NB_1=pow(B1, -0.5)

    def norm_BW2():
        Sum=0
        Nbins = 1000
        dm = (Mmax - Mmin)*1./Nbins
        for i in range(Nbins):
            m = Mmin + i*dm
            thingie = MW2(m)
            Number=(thingie*thingie.conjugate()).real
            Sum=Sum+Number*dm
        return Sum
    B2=norm_BW2()
    NB_2=pow(B2, -0.5)

    term1 = ((As2['A_2pe']*As2['A_2pe'].conjugate())).real
    term2 = ((As2['A_2pa']*As2['A_2pa'].conjugate())).real
    term3 = ((As2['A_20']*As2['A_20'].conjugate())).real
    term4 = ((As1['A_pa']*As1['A_pa'].conjugate())).real
    term5 = ((As1['A_pe']*As1['A_pe'].conjugate())).real
    term6 = ((As1['A_0']*As1['A_0'].conjugate())).real
    term7 = ((As0['A_S']*As0['A_S'].conjugate())).real

    x=Symbol("x")
    y=Symbol("y")
    z=Symbol("z")
    m=Symbol("m")
   
    const_old_pdf = integrate(1,(y,-1,1),(x,-1,1),(z,-pi,pi),(m,Mmin,Mmax))
    cc = simplify(const_old_pdf).n()
    
    final = (term1  + term2  + term3  + term4  + term5  + term6  + term7) * 1.3
    Norm_Const =pow(final,-1) *cc

#################################################################################
#              MC expected events  = 400                                        #
#################################################################################

    W_exp= -1284./f_MC_tree_1.GetEntries()
    for entry in range(int(f_MC_tree_1.GetEntries())):
        f_MC_tree_1.GetEntry(entry)
        
        px_pminus=f_MC_tree_1.piminus_PX
        py_pminus=f_MC_tree_1.piminus_PY
        pz_pminus=f_MC_tree_1.piminus_PZ
        pe_pminus=f_MC_tree_1.piminus_PE

        px_kplus=f_MC_tree_1.Kplus_PX
        py_kplus=f_MC_tree_1.Kplus_PY
        pz_kplus=f_MC_tree_1.Kplus_PZ
        pe_kplus=f_MC_tree_1.Kplus_PE

        px_muminus=f_MC_tree_1.muminus_PX
        py_muminus=f_MC_tree_1.muminus_PY
        pz_muminus=f_MC_tree_1.muminus_PZ
        pe_muminus=f_MC_tree_1.muminus_PE

        px_muplus=f_MC_tree_1.muplus_PX
        py_muplus=f_MC_tree_1.muplus_PY
        pz_muplus=f_MC_tree_1.muplus_PZ
        pe_muplus=f_MC_tree_1.muplus_PE
        
        V_pminus=TLorentzVector()
        V_pminus.SetPxPyPzE(px_pminus,py_pminus,pz_pminus,pe_pminus)

        V_Kplus=TLorentzVector()
        V_Kplus.SetPxPyPzE(px_kplus,py_kplus,pz_kplus,pe_kplus)

        V_muminus=TLorentzVector()
        V_muminus.SetPxPyPzE(px_muminus,py_muminus,pz_muminus,pe_muminus)

        V_muplus=TLorentzVector()
        V_muplus.SetPxPyPzE(px_muplus,py_muplus,pz_muplus,pe_muplus)
        
        angles=HelicityAngles(V_Kplus,V_pminus,V_muplus,V_muminus)
        tha1_addr[0]=angles[0]
        tha2_addr[0]=angles[1]
        tha3_addr[0]=angles[2]
        tha1_Branch.Fill()
        tha2_Branch.Fill()
        tha3_Branch.Fill()
        Invariant_mass=f_MC_tree_1.Inv_mass
        weight_addr[0]= W_exp* Afunc(angles[0],angles[1],angles[2],Invariant_mass + 0J,As2['A_2pe'],As2['A_2pa'],As2['A_20'],As1['A_0'],As1['A_pa'],As1['A_pe'],As0['A_S']).real
        Norm_weight_addr[0] =W_exp*Norm_Const*Afunc(angles[0],angles[1],angles[2],Invariant_mass + 0J,As2['A_2pe']*NB_2,As2['A_2pa']*NB_2,As2['A_20']*NB_2,As1['A_0']*NB_1,As1['A_pa']*NB_1 ,As1['A_pe']*NB_1,As0['A_S']*NB_0).real
        weight_Branch.Fill()
        Norm_weight_Branch.Fill()
    f_MC_tree_1.Write("",TObject.kOverwrite)
    f_MC_data_1.Close()




System_Mass("BsJpsiKK_MC_BDTG_2012_selected.root","kaons")
weights("BsJpsiKK_MC_BDTG_2012_selected.root")


