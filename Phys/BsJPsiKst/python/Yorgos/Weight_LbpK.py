from ROOT import *
from math import *
from Urania.Helicity import *
from sympy import lambdify
from SomeUtils.alyabar import vector, IM2#, HelicityAngles
from array import array
from Urania.MassAmplitudes import *
from sympy import re
from sympy import pprint
from math import pi

####  Sum of norm weights in this script is 694  and the expected number is 623 ###
import yields as Carlos

year = 2012
yields = Carlos.Yields['Lb_JpsipK']

############################################################################
#                    Constants                                             #
############################################################################
Mmin = PDG.Kplus.mass + PDG.proton.mass
Mmax = PDG.Lambda_b0.mass-PDG.Jpsi.mass

Lw = EvtGen.subs( [(m0,1519.5), (Gamma0,15.6),(Mdau1,PDG.Kplus.mass),(Mdau2,PDG.proton.mass)])
m = Symbol("m", positive = True)
_MW1 = Lw.subs(mass, m)
def getNormalization(T_sym):
    Sum=0
    Nbins = 10000
    dm = (Mmax - Mmin)*1./Nbins
    T = lambdify(m, T_sym, ("numpy"))
    for i in range(Nbins):
        mval = Mmin + i*dm
        thingie =T(mval + 0J)
        RR = re(thingie).n()
        II = im(thingie).n()
        Number= RR**2 + II**2
        #print Number
        Sum += Number*dm
    return Sum
#### Define normalized propagators
cte1 = sqrt(1./getNormalization(_MW1))
MW1 = _MW1*cte1

T_tot = MW1#*f1 + MW2*f2 + MW3*f3
def DrawPropagators():
    g4  = TGraph()#, TGraph(), TGraph(), TGraph()
    
    T_tot_lamb = lambdify(m, T_tot, ("numpy"))
    c= TCanvas()
    for i in range(int(round(Mmin)+1),int(round(Mmax)-1)):
        
        g4.SetPoint(int(i-Mmin),i,re(T_tot_lamb(i+0J)*T_tot_lamb(i+0J).conjugate()))
    
    g4.SetLineColor(kRed)
    g4.Draw("AL")
    return c, g4#,g2,g3, g4



###########################################################################
#              PDF - Swave                                                #
###########################################################################
expr_ang = 1
expr_mass = re(T_tot)*re(T_tot) + im(T_tot)*im(T_tot)
new_pdf = expr_ang* expr_mass
print "-_-"

print "Here"
#thing = lambdify(m,float(_thing)*expr_mass,("numpy"))

new_pdf = new_pdf/(getNormalization(T_tot))
new_pdf = lambdify(m,new_pdf,("numpy"))
old_pdf = 1./(Mmax-Mmin)

############################################################################
#                   Weights and Normalized - Weights                       #
############################################################################                                                                                                                                                                                                               
def weights(filename):
    f_MC_data_1 = TFile(filename,"update")
    f_MC_tree_1 = f_MC_data_1.Get("DecayTree")
    
    pK_addr= array('f',[0])
    pK_Branch = f_MC_tree_1.Branch("mpK", pK_addr,"mpK/F")
    
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
        
        if abs(f_MC_tree_1.Kplus_TRUEID) == 2212:
            p = vector(f_MC_tree_1.Kplus_PX, f_MC_tree_1.Kplus_PY, f_MC_tree_1.Kplus_PZ)
        elif abs(f_MC_tree_1.Kplus_TRUEID) == 321: k = vector(f_MC_tree_1.Kplus_PX, f_MC_tree_1.Kplus_PY, f_MC_tree_1.Kplus_PZ)

        else: p, k = -1,-1

        if abs(f_MC_tree_1.piminus_TRUEID) == 2212:
            p = vector(f_MC_tree_1.piminus_PX, f_MC_tree_1.piminus_PY, f_MC_tree_1.piminus_PZ)
        elif abs(f_MC_tree_1.piminus_TRUEID) == 321: k = vector(f_MC_tree_1.piminus_PX, f_MC_tree_1.piminus_PY, f_MC_tree_1.piminus_PZ)

        else: p, k = -1,-1
        
        #if Carlos.PHSPWeight and p!= -1 and k!= -1:
        Invariant_mass= sqrt(IM2(p,k,PDG.proton.mass, PDG.Kplus.mass))
        #    w0 =  new_pdf(Invariant_mass + 0J)/old_pdf
        #else:
        #    w0 = 0.0
        #    Invariant_mass = -1
        pK_addr[0] = Invariant_mass
        pK_Branch.Fill()
        w0 =  f_MC_tree_1.wdp
        weight_addr[0] = w0
        Norm_weight_addr[0] = W_exp * w0
        weight_Branch.Fill()
        Norm_weight_Branch.Fill()
    f_MC_tree_1.Write("",TObject.kOverwrite)
    f_MC_data_1.Close()

fname = "~/NTuplesFast/MC/peaking/"+ str(year) + "/Lb_JpsipK_sel.root"

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
N0 = 0
for entry in t:
    N0+= -t.wMC
    m_ =t.Kst_892_0_MM
    for i in range(4):
        if  m_ > Kpibins[i] and m_ < Kpibins[i+1]: N[i+1]+= -t.wMC
print N
print sum(N.values())

## 2015 numbers
# 2011

#{1: 7.302165240980685, 2: 8.38404970895499, 3: 10.514548292383552, 4: 9.909921614453197}
#36.1106848568

#{1: 18.90076543390751, 2: 21.70188862271607, 3: 23.935453606769443, 4: 25.52576224692166}
#90.0638699103

## Plus One sigma

# 2011
#{1: 10.861600920557976, 2: 12.470849273726344, 3: 15.639857985079288, 4: 14.740506397560239}
#53.7128145769

#2012
#{1: 28.095994621515274, 2: 32.259865045547485, 3: 35.58006040006876, 4: 37.944054674357176}
#133.879974741


## Minus one sigma

#2011

#{1: 3.742729568388313, 2: 4.2972501632757485, 3: 5.389238608069718, 4: 5.079336792230606}
#18.508555132

#2012
#{1: 9.705536298453808, 2: 11.143911997787654, 3: 12.290846841409802, 4: 13.10746980831027}
#46.247764946
