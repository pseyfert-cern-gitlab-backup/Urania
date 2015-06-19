from ROOT import *
from math import *
from ROOT import *
from math import *
from Urania.Helicity import *
from Urania import PDG
from sympy import lambdify
from SomeUtils.alyabar import HelicityAngles
from array import array
from sympy import re
from sympy import integrate
m=Symbol('m', positive = True)
Mmin = 2*PDG.piplus.mass
Mmax = PDG.Bd.mass-PDG.Jpsi.mass
my_spins = [0,1,2]


#### in this script the sum of the worm weights 1240 and the expected number is 537 ####


#########################################################################
#              Cosntant values                                          #
#########################################################################

A_2pe =sqrt(2.0) * e**2.87J
A_2pa = sqrt(0.9)* e**5.82J
A_20 = sqrt(4.7) * e**3.6J
A_pe = sqrt(12.1) * e**0.0J
A_pa = sqrt(14.7) * e**3.29J
A_0 = sqrt(36.2) * e**0.0J
A_S =  sqrt(22.2) * e**5.86J

particle_list=["kaons","pions"]
A = doB2VX(my_spins,[1,-1])

def setmass(particle):
    if particle == particle_list[0]:
        return PDG.Kplus.mass**2
    elif particle == particle_list[1]:
        return PDG.piplus.mass**2
    else: raise Exception(" i dont know this particle")


#########################################################################
#            Breight - Wigner                                           #
#########################################################################

_MW1 = One/(m**2 - 513.**2 - 335*513*I)
_MW2 = One/(m**2 - 775.**2 - 149*775*I)
_MW3 = One/(m**2 - 1275.**2 - 185*1275*I)


def getNormalization(T_sym):
    Sum=0
    Nbins = 1000
    dm = (Mmax - Mmin)*1./Nbins
    T = lambdify(m, T_sym, ("numpy"))
    for i in range(Nbins):
        mval = Mmin + i*dm
        thingie =T(mval + 0J)
        RR = re(thingie).n()
        II = im(thingie).n()
        Number= RR**2 + II**2
        Sum += Number*dm
    return Sum
#### Define normalized propagators
cte1, cte2, cte3 = sqrt(1./getNormalization(_MW1)),sqrt(1./getNormalization(_MW2)),sqrt(1./getNormalization(_MW3))

MW1 = _MW1*cte1
MW2 = _MW2*cte2
MW3= _MW3*cte3
def DrawPropagators():
    g1,g2,g3, g4  = TGraph(), TGraph(), TGraph(), TGraph()
    l_MW1 = lambdify(m, MW1,("numpy"))
    l_MW2 = lambdify(m, MW2,("numpy"))
    l_MW3 = lambdify(m, MW3,("numpy"))
    #T_tot_lamb = lambdify(m, T_tot, ("numpy"))
    c= TCanvas()
    for i in range(int(round(Mmin)+1),int(round(Mmax)-1)):
        g1.SetPoint(int(i-Mmin),i,re(l_MW1(i+0J)*l_MW1(i+0J).conjugate()))
        g2.SetPoint(int(i-Mmin),i,re(l_MW2(i+0J)*l_MW2(i+0J).conjugate()))
        g3.SetPoint(int(i-Mmin),i,re(l_MW3(i+0J)*l_MW3(i+0J).conjugate()))
        #g4.SetPoint(int(i-Mmin),i,re(T_tot_lamb(i+0J)*T_tot_lamb(i+0J).conjugate()))
    g1.Draw("AL")
    g2.Draw("L")
    g3.Draw("L")
    g4.SetLineColor(kRed)
    #g4.Draw("L")
    return c, g1,g2,g3#, g4


#########################################################################
#             PDF for 0,1,2                                             #
#########################################################################


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
A = changeFreeVars(A)
my_amp_subs = [(TransAmplitudes['0_0'],A_S),(TransAmplitudes['1_0'], A_0),(TransAmplitudes['1_pa'], A_pa), (TransAmplitudes['1_pe'], A_pe)]
my_amp_subs += [(TransAmplitudes['2_0'], A_20), (TransAmplitudes['2_pa'],A_2pa),(TransAmplitudes['2_pe'] ,A_2pe)]

ang_cte = re(iter_integrate(A,(x,-1,1),(y,-1,1),(z,-Pi,Pi)).subs(my_amp_subs).n())

Aprime=A.subs([(TransAmplitudes['0_0'],TransAmplitudes['0_0'] * MW1), (TransAmplitudes['1_0'],TransAmplitudes['1_0']*MW2), (TransAmplitudes['1_pa'],TransAmplitudes['1_pa']*MW2),(TransAmplitudes['1_pe'],TransAmplitudes['1_pe']*MW2),(TransAmplitudes['2_0'],TransAmplitudes['2_0']*MW3),(TransAmplitudes['2_pa'],TransAmplitudes['2_pa']*MW3),(TransAmplitudes['2_pe'],TransAmplitudes['2_pe']*MW3)])

Aprime = Aprime.subs(my_amp_subs)*1./ang_cte
new_pdf = lambdify( (x,y,z,m),Aprime , ("numpy"))
def checkIntegral(pdf, NbinsD = 40):
    Sum = 0
    dx = 2./NbinsD
    dy = 2./NbinsD
    dz = 2*pi/NbinsD
    dm = (Mmax-Mmin)*1./NbinsD
    print "0000"
    print dx,dy,dz,dm
    print "****"
    for i in range(NbinsD+1):
        x = -1. + i*dx
        for j in range(NbinsD+1):
            y = -1 + j*dx
            for k in range(NbinsD+1):
                z = -pi + k*dz
                for l in range(NbinsD+1):
                    m = Mmin + l*dm + 0J
                    #print "---"
                    #print x, y, z , m
                    H = pdf(x,y,z,m)
                    #print H
                    Sum += dm*dx*dy*dz*H
                    #print Sum
    return Sum
old_pdf_cte = float(1./integrate(One,(x,-1,1),(y,-1,1),(z,-Pi,Pi),(m,Mmin,Mmax)).n())
def old_pdf(x,y,z,m): return 1*old_pdf_cte

##########################################################################
#            Invariant mass of the system X                              #
##########################################################################

def System_Mass(filename,particle):    
    f_MC_data_1 = TFile(filename,"update")
    f_MC_tree_1 = f_MC_data_1.Get("DecayTree")
    mass_sqrt = setmass(particle)
    M_addr=array('f',[0])
    MBranch_M=f_MC_tree_1.Branch("Inv_mass", M_addr,"Inv_mass/F")
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
        m= mass_sqrt
        Invariant_mass=pow(2*m + 2*pow(m + p_minus_power_2,0.5)*pow(m+p_kplus_power_2,0.5)-2*p_minus_p_kplus,0.5)
        M_addr[0]=Invariant_mass
        MBranch_M.Fill()
    f_MC_tree_1.Write("",TObject.kOverwrite)
    f_MC_data_1.Close()

###########################################################################
#             weights and Normalized weights                              #
###########################################################################
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

###########################################################################
#                  Normalization Constant                                 # 
###########################################################################

#########################################################################
#         MC expected events = 537                                     #
#########################################################################
   
    W_exp= -537./f_MC_tree_1.GetEntries()
    print "W_exp", W_exp
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
        w0 =  new_pdf(angles[0],angles[1],angles[2], Invariant_mass + 0J).real/old_pdf(angles[0],angles[1],angles[2], Invariant_mass +0J)
        weight_addr[0] = w0
        Norm_weight_addr[0] = W_exp * w0
        weight_Branch.Fill()
        Norm_weight_Branch.Fill()
    f_MC_tree_1.Write("",TObject.kOverwrite)
    f_MC_data_1.Close()


System_Mass("BdJpsipipi.root","pions")
weights("BdJpsipipi.root")


