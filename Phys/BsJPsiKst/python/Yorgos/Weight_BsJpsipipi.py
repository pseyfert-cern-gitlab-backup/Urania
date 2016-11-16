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
x=Symbol("x", real = True)
y=Symbol("y", real = True)
z=Symbol("z", real = True)
m=Symbol("m", positive = True)

####  Sum of norm weights in this script is 694  and the expected number is 623 ###
import yields as Carlos

year = 2012
yields = Carlos.Yields['Bs_Jpsipipi']

############################################################################
#                    Constants                                             #
############################################################################

particle_list=["kaons","pions"]

phi1500=0J
phi980=-2.4J
phi1790=-1.04J

f980=sqrt(70.3)*e**phi980
f1500=sqrt(10.1)*e**phi980
f1790=sqrt(2.4)*e**phi1790
f1=f980**2 *1./(f980**2 + f1500**2 + f1790**2)
f2=f1500**2 *1./(f980**2 + f1500**2 + f1790**2)
f3=f1790**2 *1./(f980**2 + f1500**2 + f1790**2)

I1 = (f1 * f1.conjugate()).real
I2 = (f2 * f2.conjugate()).real
I3 = (f3 * f3.conjugate()).real
I13 = (f1 * f3.conjugate()).real
I31 = (f3 * f1.conjugate()).real
I12 = (f1 * f2.conjugate()).real
I21 = (f2 * f1.conjugate()).real
I23 = (f2 * f3.conjugate()).real
I32 = (f3 * f2.conjugate()).real
    

Mmin = 2*PDG.piplus.mass
Mmax = PDG.Bs.mass-PDG.Jpsi.mass

def setmass(particle):
    if particle == particle_list[0]:
        return PDG.Kplus.mass**2
    elif particle == particle_list[1]:
        return PDG.piplus.mass**2
    else: raise Exception(" i dont know this particle")


###########################################################################
#           Breigth- Wigner, and flatte                                   #
###########################################################################

_MW3 = One/(m**2 - 1790.**2 - 270*1790*I)
_MW2= One /(m**2 - 1505**2 - 106*1505*I)
_MW1 = f0_Syr.subs(mass,m)
#def _MW1(Mpipi_):return 1./(Mpipi_**2 - pow(990,2) - 990 * 60J)
#_func=lambdify(mass,f0_Syr,("numpy"))
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
T_tot = MW1*f1 + MW2*f2 + MW3*f3
def DrawPropagators():
    g1,g2,g3, g4  = TGraph(), TGraph(), TGraph(), TGraph()
    l_MW1 = lambdify(m, MW1,("numpy"))
    l_MW2 = lambdify(m, MW2,("numpy"))
    l_MW3 = lambdify(m, MW3,("numpy"))
    T_tot_lamb = lambdify(m, T_tot, ("numpy"))
    c= TCanvas()
    for i in range(int(round(Mmin)+1),int(round(Mmax)-1)):
        g1.SetPoint(int(i-Mmin),i,re(l_MW1(i+0J)*l_MW1(i+0J).conjugate()))
        g2.SetPoint(int(i-Mmin),i,re(l_MW2(i+0J)*l_MW2(i+0J).conjugate()))
        g3.SetPoint(int(i-Mmin),i,re(l_MW3(i+0J)*l_MW3(i+0J).conjugate()))
        g4.SetPoint(int(i-Mmin),i,re(T_tot_lamb(i+0J)*T_tot_lamb(i+0J).conjugate()))
    g1.Draw("AL")
    g2.Draw("L")
    g3.Draw("L")
    g4.SetLineColor(kRed)
    g4.Draw("L")
    return c, g1,g2,g3, g4


# numerator of the old_pdf #

###########################################################################
#              PDF - Swave                                                #
###########################################################################
expr_ang = (1-y**2)
expr_mass = re(T_tot)*re(T_tot) + im(T_tot)*im(T_tot)
new_pdf = expr_ang* expr_mass
print "-_-"
ang_cte = float(integrate(expr_ang, (x,-1,1), (y,-1,1), (z,-Pi,Pi)))
print "Here"
#thing = lambdify(m,float(_thing)*expr_mass,("numpy"))

new_pdf = new_pdf/(ang_cte* getNormalization(T_tot))
new_pdf = lambdify((x,y,z,m),new_pdf,("numpy"))
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
    Norm_weight_Branch = f_MC_tree_1.Branch("wMC",Norm_weight_addr,"wMC/F")    
    #####################################################################
    #        MC expected event =  623                                   #
    #####################################################################
    W_exp= -yields[year]/f_MC_tree_1.GetEntries()
 
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
        if Carlos.PHSPWeight: w0 =  new_pdf(angles[0],angles[1],angles[2], Invariant_mass + 0J)/old_pdf(angles[0],angles[1],angles[2], Invariant_mass +0J)
        else: w0 = 1.0
        weight_addr[0] = w0
        Norm_weight_addr[0] = W_exp * w0
        weight_Branch.Fill()
        Norm_weight_Branch.Fill()
    f_MC_tree_1.Write("",TObject.kOverwrite)
    f_MC_data_1.Close()

fname = "~/NTuplesFast/MC/peaking/"+ str(year) + "/Bs_Jpsipipi_sel.root"
System_Mass(fname,"pions")
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
for entry in t:
    m =t.Kst_892_0_MM
    for i in range(4):
        if  m > Kpibins[i] and m < Kpibins[i+1]: N[i+1]+= -t.wMC
print N
print sum(N.values())



## 2015 numbers
#2011
#{1: 1.6181586865277495, 2: 2.2347492477856576, 3: 2.849341981811449, 4: 2.6423543263226748}
#9.34460424245

#2012
#{1: 3.8767055327625712, 2: 4.68394180021096, 3: 7.003198517020792, 4: 9.404357547638938}
#24.9682033976


### Plus one sigma
#2011
#{1: 1.9807603327790275, 2: 2.735518283676356, 3: 3.4878307186299935, 4: 3.2344606835395098}
#11.4385700186

#2012
#{1: 4.724440268284525, 2: 5.708198108519355, 3: 8.534615954849869, 4: 11.460845991969109}
#30.4281003236


## Minus one sigma

# 2011
#{1: 1.2555570394615643, 2: 1.7339802305214107, 3: 2.2108532799757086, 4: 2.050247995182872}
#7.25063854514
#2012
#{1: 3.028970810264582, 2: 3.6596855008065177, 3: 5.471781039843336, 4: 7.34786904376233}
#19.5083063947
