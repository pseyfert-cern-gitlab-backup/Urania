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
from sympy import integrate

m=Symbol("m", positive = True)
#Mmin = 1014
Mmin = 2*PDG.Kplus.mass
#Mmax = 2120.2
Mmax = PDG.Bd.mass-PDG.Jpsi.mass
my_spins = [0,1,2]
year = 2012
import yields as Carlos
yields = Carlos.Yields['Bs_JpsiKK']

#yields = 
ffphis = { 2011: 710./925, 2012: 510./657 }
fphi = ffphis[year]
#########################################################################      
#              Cosntant values                                          #      
#########################################################################       
A_2pe =sqrt(2.55) * e**0.0J
A_2pa = sqrt(2.55)* e**0.0J
A_20 = sqrt(9.9) * e**0.0J
A_pe = sqrt(17.3) * e**0.0J
A_pa = sqrt(17.3) * e**0.0J
A_0 = sqrt(32.1) * e**0.0J
A_S =  sqrt(12.0) * e**-4.6J

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
_MW1 = f0_Syr.subs(mass,m)
_MW2 = One/(m**2 - 1019.**2 - 1019.445*4.26*I)
_MW3 = One/(m**2 - 1525.**2 - 76*1525.*I)

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
MW3 = _MW3*cte3                                                                                                                          
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
phi_amp_subs = [(TransAmplitudes['0_0'],0),(TransAmplitudes['1_0'], A_0),(TransAmplitudes['1_pa'], A_pa), (TransAmplitudes['1_pe'], A_pe)]
phi_amp_subs += [(TransAmplitudes['2_0'], 0), (TransAmplitudes['2_pa'],0),(TransAmplitudes['2_pe'] ,0)]

big_integral = iter_integrate(A,(x,-1,1),(y,-1,1),(z,-Pi,Pi))
ang_cte = re(big_integral.subs(my_amp_subs).n())
phi_cte = re(big_integral.subs(phi_amp_subs).n())

Aprime=A.subs([(TransAmplitudes['0_0'],TransAmplitudes['0_0'] * MW1), (TransAmplitudes['1_0'],TransAmplitudes['1_0']*MW2), (TransAmplitudes['1_pa'],TransAmplitudes['1_pa']*MW2),(TransAmplitudes['1_pe'],TransAmplitudes['1_pe']*MW2),(TransAmplitudes['2_0'],TransAmplitudes['2_0']*MW3),(TransAmplitudes['2_pa'],TransAmplitudes['2_pa']*MW3),(TransAmplitudes['2_pe'],TransAmplitudes['2_pe']*MW3)])

Aphi=A.subs([(TransAmplitudes['0_0'],0), (TransAmplitudes['1_0'],TransAmplitudes['1_0']*MW2), (TransAmplitudes['1_pa'],TransAmplitudes['1_pa']*MW2),(TransAmplitudes['1_pe'],TransAmplitudes['1_pe']*MW2),(TransAmplitudes['2_0'],0),(TransAmplitudes['2_pa'],0),(TransAmplitudes['2_pe'],0)])

Aprime = Aprime.subs(my_amp_subs)*1./ang_cte
Aphi = Aphi.subs(phi_amp_subs)*1./phi_cte

new_pdf = lambdify( (x,y,z,m),Aprime , ("numpy"))
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


def checkIntegral(pdf, NbinsX = 10, NbinsY = 10, NbinsZ = 10, NbinsM = 400):
    Sum = 0
    dx = 2./NbinsX
    dy = 2./NbinsY
    dz = 2*pi/NbinsZ
    dm = (Mmax-Mmin)*1./NbinsM
    print "0000"
    print dx,dy,dz,dm
    print "****"
    for i in range(NbinsX+1):
        x = -1. + i*dx
        for j in range(NbinsY+1):
            y = -1 + j*dx
            for k in range(NbinsZ+1):
                z = -pi + k*dz
                for l in range(NbinsM+1):
                    m = Mmin + l*dm + 0J
                    #print "---"
                    #print x, y, z , m
                    H = pdf(x,y,z,m)
                    #print H
                    Sum += dm*dx*dy*dz*H
                    #print Sum
    return Sum
#BREAK
phi_pdf = lambdify( (x,y,z,m),Aphi , ("numpy"))
#BREAK
flat_pdf_cte = float(1./integrate(One,(x,-1,1),(y,-1,1),(z,-Pi,Pi),(m,Mmin,Mmax)).n())
def flat_pdf(x,y,z,m): return 1*flat_pdf_cte

def old_pdf(x,y,z,m): return fphi * phi_pdf(x,y,z,m) + (1-fphi)*flat_pdf(x,y,z,m)

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
    Norm_weight_Branch = f_MC_tree_1.Branch("wMC",Norm_weight_addr,"wMC/F")

    W_exp= -yields[year]/f_MC_tree_1.GetEntries()
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
        if Carlos.PHSPWeight: w0 =  new_pdf(angles[0],angles[1],angles[2], Invariant_mass + 0J).real/old_pdf(angles[0],angles[1],angles[2], Invariant_mass +0J)
        else: w0 = 1.0
        weight_addr[0] = w0
        Norm_weight_addr[0] = W_exp * w0
        weight_Branch.Fill()
        Norm_weight_Branch.Fill()
    f_MC_tree_1.Write("",TObject.kOverwrite)
    f_MC_data_1.Close()


fname = "~/NTuplesFast/MC/peaking/"+ str(year) + "/Bs_JpsiKK_parche.root"
System_Mass(fname,"kaons")
weights(fname)

def make_plot():
    f = TFile(fname)
    t = f.Get("DecayTree")
    c = TCanvas()
    #if weight: w = "-wMC"
    #else: w = "(1>0)"
    
    c.Divide(2,1)
    c.cd(1)
    t.Draw("Inv_mass")
    c.cd(2)
    t.Draw("Inv_mass", "-wMC")
    return c

N = {1:0,2:0,3:0,4:0}
f = TFile(fname)
t = f.Get("DecayTree")
from Urania import *
AccessPackage("BsJPsiKst")
from parameters import KpiBins4 as Kpibins
Nw = 0
for entry in t:
    Nw += -t.wMC
    mval =t.Kst_892_0_MM
    for i in range(4):
        if  mval > Kpibins[i] and mval < Kpibins[i+1]: N[i+1]+= -t.wMC
print N
print sum(N.values())
print "In full mass range", Nw


## 2015 numbers

#2011
#{1: 5.864953614771366, 2: 2.9751679822802544, 3: 0.834964070469141, 4: 0.39982900209724903}
#10.0749146696

#2012
#{1: 11.63592690974474, 2: 3.9236329048871994, 3: 2.8936074897646904, 4: 0.7397264242172241}
#19.1928937286

##Plus one sigma

#2011
#{1: 7.135585347190499, 2: 3.6197327580302954, 3: 1.0158575475215912, 4: 0.48645124211907387}
#12.2576268949
#In full mass range 86.310833465

#2012
#{1: 14.057680271565914, 2: 4.740247666835785, 3: 3.4958460181951523, 4: 0.893683671951294}
#23.1874576285
#In full mass range 172.270654948

## Minus one sigma
#2011
#{1: 4.594321893528104, 2: 2.330603159032762, 3: 0.6540706008672714, 4: 0.3132067583501339}
#7.89220241178
#In full mass range 55.5721403657

#2012
#{1: 9.21417373791337, 2: 3.1070180162787437, 3: 2.2913689613342285, 4: 0.5857692360877991}
#15.1983299516
#In full mass range 112.915624335
