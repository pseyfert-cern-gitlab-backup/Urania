from ROOT import *
from math import *
from Urania.Helicity import *
from sympy import lambdify
from SomeUtils.alyabar import HelicityAngles
from array import array
from Urania.MassAmplitudes import *
from sympy import re
from sympy import pprint
from math import pi


########################################################################
#           In this script i have delete the term (1-y**2) of the old pdf
#           the sum of the normalized weighst are 681
#######################################################################


############################################################################
#                    Constants                                             #
############################################################################

particle_list=["kaons","pions"]


######## the phases i guess are wrong as numbers   #############
phi1500=0J
phi980=-2.4J
phi1790=-1.04J

f980=sqrt(70.3)*e**phi980
f1500=sqrt(10.1)*e**phi980
f1790=sqrt(2.4)*e**phi1790
f1=f980**2 *1./(f980**2 + f1500**2 + f1790**2)
f2=f1500**2 *1./(f980**2 + f1500**2 + f1790**2)
f3=f1790**2 *1./(f980**2 + f1500**2 + f1790**2)

Mmin = 250
Mmax = 1850

def setmass(particle):
    if particle == particle_list[0]:
        return pow(493.667,2)
    elif particle == particle_list[1]:
        return pow(139.570,2)
    else: raise Exception(" i dont know this particle")


###########################################################################
#           Breigth- Wigner, and flatte                                   #
###########################################################################

def MW3(Mpipi_):return 1./(Mpipi_**2 - pow(1790,2) - 270*1790J)
def MW2(Mpipi_):return 1./(Mpipi_**2 - pow(1505,2) - 106*1505J)
def MW1(Mpipi_):return 1./(Mpipi_**2 - pow(990,2) - 990 * 60J)
func=lambdify(mass,f0_Syr,("numpy"))

# numerator of the old_pdf #
def s_pdf_old(x):
    r =(1 - x**2)
    return r

###########################################################################
#              PDF - Swave                                                #
###########################################################################

def s_pdf(x,M):
    k =(1 - x**2)* ((func(M)*f1 + MW2(M)*f2 + MW3(M)*f3)*(func(M)*f1 + MW2(M)*f2 + MW3(M)*f3).conjugate()).real * 1./(4*pi)
    return k

###########################################################################                                                                                                                                           
#           Invariant mass of the system X                                #
###########################################################################

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
        Invariant_mass=pow(2*m + 2*pow(m + p_minus_power_2,0.5)*pow(m+p_kplus_power_2,0.5)-2*p_minus_p_kplus,0.5)
        M_addr[0]=Invariant_mass
        MBranch_M.Fill()
    f_MC_tree_1.Write("",TObject.kOverwrite)
    f_MC_data_1.Close()

############################################################################
#                   Weights and Normalized - Weights                       #
############################################################################                                                                                                                                                                                                               
def weights(filename):
    f_MC_data_1 = TFile(filename,"update")
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

############################################################################
#            Normalization Constant                                        #
############################################################################
   
    def BW1():
        Sum=0
        Nbins = 1000
        dm = (Mmax - Mmin)*1./Nbins
        for i in range(Nbins):
            m = Mmin + i*dm
            thingie =func(m + 0J)
            Number=re(thingie*thingie.conjugate()).n()
            Sum=Sum+Number*dm
        return Sum
    
    def BW2():
        Sum=0
        Nbins = 1000
        dm = (Mmax - Mmin)*1./Nbins
        for i in range(Nbins):
            m = Mmin + i*dm
            thingie =MW2(m + 0J)
            Number=re(thingie*thingie.conjugate()).n()
            Sum=Sum+Number*dm
        return Sum

    def BW3():
        Sum=0
        Nbins = 1000
        dm = (Mmax - Mmin)*1./Nbins
        for i in range(Nbins):
            m = Mmin + i*dm
            thingie =MW3(m + 0J)
            Number=re(thingie*thingie.conjugate()).n()
            Sum=Sum+Number*dm
        return Sum

    def BW12():
        Sum=0
        Nbins = 1000
        dm = (Mmax - Mmin)*1./Nbins
        for i in range(Nbins):
            m = Mmin + i*dm
            thingie1 =func(m + 0J)
            thingie2 =MW2(m + 0J).conjugate()
            Number=re(thingie1*thingie2).n()
            Sum=Sum+Number*dm
        return Sum

    def BW21():
        Sum=0
        Nbins = 1000
        dm = (Mmax - Mmin)*1./Nbins
        for i in range(Nbins):
            m = Mmin + i*dm
            thingie2 =MW2(m + 0J)
            thingie1 =func(m + 0J).conjugate()
            Number=re(thingie2*thingie1).n()
            Sum=Sum+Number*dm
        return Sum

    def BW13():
        Sum=0
        Nbins = 1000
        dm = (Mmax - Mmin)*1./Nbins
        for i in range(Nbins):
            m = Mmin + i*dm
            thingie1 =func(m + 0J)
            thingie3 =MW3(m + 0J).conjugate()
            Number=re(thingie1*thingie3).n()
            Sum=Sum+Number*dm
        return Sum

    def BW31():
        Sum=0
        Nbins = 1000
        dm = (Mmax - Mmin)*1./Nbins
        for i in range(Nbins):
            m = Mmin + i*dm
            thingie3 =MW3(m + 0J)
            thingie1 =func(m + 0J).conjugate()
            Number=re(thingie3*thingie1).n()
            Sum=Sum+Number*dm
        return Sum

    def BW23():
        Sum=0
        Nbins = 1000
        dm = (Mmax - Mmin)*1./Nbins
        for i in range(Nbins):
            m = Mmin + i*dm
            thingie2 =MW2(m + 0J)
            thingie3 =MW3(m + 0J).conjugate()
            Number=re(thingie2*thingie3).n()
            Sum=Sum+Number*dm
        return Sum

    def BW32():
        Sum=0
        Nbins = 1000
        dm = (Mmax - Mmin)*1./Nbins
        for i in range(Nbins):
            m = Mmin + i*dm
            thingie3 =MW3(m + 0J)
            thingie2 =MW2(m + 0J).conjugate()
            Number=re(thingie3*thingie2).n()
            Sum=Sum+Number*dm
        return Sum
   

    I1 = (f1 * f1.conjugate()).real
    I2 = (f2 * f2.conjugate()).real
    I3 = (f3 * f3.conjugate()).real
    I13 = (f1 * f3.conjugate()).real
    I31 = (f3 * f1.conjugate()).real
    I12 = (f1 * f2.conjugate()).real
    I21 = (f2 * f1.conjugate()).real
    I23 = (f2 * f3.conjugate()).real
    I32 = (f3 * f2.conjugate()).real
    
    x=Symbol("x")
    y=Symbol("y")
    z=Symbol("z")
    m=Symbol("m")
    
    expr = (1-y**2)
    
    const_old_pdf = integrate(1,(x,-1,1),(y,-1,1),(z,-pi,pi),(m,Mmin,Mmax))#normalization of the old pdf
    cc = simplify(const_old_pdf).n()
    
    thita_integral = integrate(expr,(y,-1,1),(x,-1,1),(z,-pi,pi)) # is the normalization of the numerator of the simple angular pdf that we have for the sWaves
    
    const_new_pdf = (BW1()*I1 + BW2()*I2 + BW3()*I3 + BW12()*I12 + BW21()*I21 + BW13()*I13 + BW31()*I31 + BW23()*I23 + BW32()*I32) * thita_integral*1./(4*pi)                
    Norm_Const = pow(const_new_pdf , -1) * cc
    #####################################################################
    #        MC expected event =  623                                   #
    #####################################################################
    W_exp= -623./f_MC_tree_1.GetEntries()
 
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
        weight_addr[0] = W_exp * s_pdf(x=angles[1] , M=Invariant_mass + 0J)
        Norm_weight_addr[0] = W_exp * Norm_Const * s_pdf(x=angles[1] , M=Invariant_mass + 0J)
        weight_Branch.Fill()
        Norm_weight_Branch.Fill()
    f_MC_tree_1.Write("",TObject.kOverwrite)
    f_MC_data_1.Close()


System_Mass("BsJpsipipi.root","pions")
weights("BsJpsipipi.root")

