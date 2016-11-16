from ROOT import *
#f = TFile("~/w7folder/kspi0/Tuple_MC_Frankfurt.root")
f = TFile("kspi0mm_DTFMC12_Strip_Down.root")
t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
kPaula = TColor.GetColor("#ff99cc")
#f = TFile("bkgMini.root")
#t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
#BREAK
from SomeUtils.alyabar import *
from Urania import PDG
#import Sym_constr_IP as IP_formulae
from sympy import nsolve, solve, mpmath,lambdify,Symbol
from sympy import exp as Exp
from sympy import log as Log
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from triggerclass import *
from math import *
One = 1.
h = TH1F("A","A", 100,0,1 )
hb = TH1F("B","B", 100, 0,1)
href = TH1F("ref","ref",100, 0,1)
mpmath.mp.dps = 10 #set precision
EM = Symbol("E_M", positive = True)
E1 = Symbol("E_1", positive = True)
E2 = Symbol("E_2", positive = True)
am = Symbol('a_m')
bm = Symbol('b_m')
asigma = Symbol('a_sigma')
bsigma = Symbol('b_sigma')
cTheta = Symbol("ctheta", real = True)
def mean(E): return am + bm*E #mean parametrization
def sigma(E): return asigma + bsigma*E #sigma parametrization (?)
#a_m, b_m, a_B, b_B need to be defined
def lam(E): return -0.85
def nu(E): return -lam(E)/2.
## PFormula = (EM -m(EM) **2 + B)** (lam(E) - 0.5) #t-Student
PFormula = (1 + ((EM - mean(EM))/sigma(EM))**2)**(lam(EM) - 0.5)
## TO BE CHECKED

f1 = open('fittingresults1.txt','r')
x1 = []
for line in f1:
    line = line.strip()
    x1.append(float(line))

as1 = x1[2]
bs1 = x1[3]
am1 = x1[0]
bm1 = x1[1]

f2 = open('fittingresults2.txt','r')
x2 = []
for line in f2:
    line = line.strip()
    x2.append(float(line))

as2 = x2[2]
bs2 = x2[3]
am2 = x2[0]
bm2 = x2[1]


P1 = PFormula.subs([(EM,E1),(asigma,as1),(bsigma,bs1),(am,am1),(bm,bm1)])
P2 = PFormula.subs([(EM,E2),(asigma,as2),(bsigma,bs2),(am,am2),(bm,bm2)])
"""
P1 = PFormula.subs([(EM,E1),(asigma,1101.579),(bsigma,0.0299),(am,407.73),(bm,0.947)]) #to be implemented nicely
P2 = PFormula.subs([(EM,E2),(asigma,938.74),(bsigma,0.06),(am,388.61),(bm,0.916)])
"""
def Mgg(E1,E2, cTheta): return (2*E1*E2*(1-cTheta))**(0.5)

sigma_mpi0 = One#0.0006 #from the PDG (MeV)
Pmass = e**( -One/2*( (( Mgg(E1,E2, cTheta) - PDG.pi0.mass)/sigma_mpi0)**2))
lnPmass = Log(Pmass)
PTOT = P1*P2*Pmass
#total pdf. mass part of the pion as a gaussian. sigma_mpi0 either a tiny number or the PDG value
lnPTOT = Log(PTOT)

## eq1 = PTOT.diff(E1)
## eq2 = PTOT.diff(E2)
eq1 = PTOT.diff(E1)
eq2 = PTOT.diff(E2)
myeqs = [eq1,eq2] #to maximize the partial derivatives of the pdf

def P(EM): #t-Student, not as a symbolic expression but as a function of the energy
    return (1 + ((EM - mean(EM))/sigma(EM))**2)**(lam(EM) - 0.5)

def dummyf(E1,E2,cTheta):
    return E1+E2+cTheta

## Create lambdified versions if slow
#myeqs = [E1,E1]
p = -0.5*2**0.5*E1**0.5*E2**0.5*(1 + (0.0529999999998836*E1 - 407.730000000447)**2/(0.0298999999999978*E1 + 1101.57899999619)**2)**-1.35000000000582*(1 + (0.0840000000025611*E2 - 388.609999999404)**2/(0.0599999999999454*E2 + 938.740000002086)**2)**-1.35000000000582*(-cTheta + 1)**0.5*(1.0*2**0.5*E1**0.5*E2**0.5*(-cTheta + 1)**0.5 - 134.976999999955)*e**(-0.5*(1.0*2**0.5*E1**0.5))#*E2**0.5*(-cTheta + 1)**0.5 - 134.976999999955)**2)/E1 + (1 + (0.0529999999998836*E1 - 407.730000000447)**2/(0.0298999999999978*E1 + 1101.57899999619)**2)**-1.35000000000582*(1 + (0.0840000000025611*E2 - 388.609999999404)**2/(0.0599999999999454*E2 + 938.740000002086)**2)**-1.35000000000582*(-1.35000000000582*(0.00561799999997532*E1 - 43.2193799999525)/(0.0298999999999978*E1 + 1101.57899999619)**2 + 0.0807300000003422*(0.0529999999998836*E1 - 407.730000000447)**2/(0.0298999999999978*E1 + 1101.57899999619)**3)*Exp(-0.5*(1.0*2**0.5*E1**0.5*E2**0.5*(-cTheta + 1)**0.5 - 134.976999999955)**2)/(1 + (0.0529999999998836*E1 - 407.730000000447)**2/(0.0298999999999978*E1 + 1101.57899999619)**2)
q = -0.5*2**0.5*E1**0.5*E2**0.5*(1 + (0.0529999999998836*E1 - 407.730000000447)**2/(0.0298999999999978*E1 + 1101.57899999619)**2)**-1.35000000000582*(1 + (0.0840000000025611*E2 - 388.609999999404)**2/(0.0599999999999454*E2 + 938.740000002086)**2)**-1.35000000000582*(-cTheta + 1)**0.5*(1.0*2**0.5*E1**0.5*E2**0.5*(-cTheta + 1)**0.5 - 134.976999999955)*Exp(-0.5*(1.0*2**0.5*E1**0.5*E2**0.5*(-cTheta + 1)**0.5 - 134.976999999955)**2)/E2 + (1 + (0.0529999999998836*E1 - 407.730000000447)**2/(0.0298999999999978*E1 + 1101.57899999619)**2)**-1.35000000000582*(1 + (0.0840000000025611*E2 - 388.609999999404)**2/(0.0599999999999454*E2 + 938.740000002086)**2)**-1.35000000000582*(-1.35000000000582*(0.0141120000008605*E2 - 65.2864800018904)/(0.0599999999999454*E2 + 938.740000002086)**2 + 0.162000000000551*(0.0840000000025611*E2 - 388.609999999404)**2/(0.0599999999999454*E2 + 938.740000002086)**3)*Exp(-0.5*(1.0*2**0.5*E1**0.5*E2**0.5*(-cTheta + 1)**0.5 - 134.976999999955)**2)/(1 + (0.0840000000025611*E2 - 388.609999999404)**2/(0.0599999999999454*E2 + 938.740000002086)**2)
#myeqs = [p,p]
mylambs = []
for eq in myeqs:
    mylambs.append(lambdify( (E1,E2,cTheta), eq, ('numpy'))) #create functions
#funciona a partir de aqui con funciones normales
#con otra expresion simbolica tambien funciona

def getfunction(lamb,cTheta): #get a function with arguments only energies, not cTheta
    ## print "I'm getting out function"
    def caca(x,y): #problem is here: takes exactly 2 arguments (1 given)
        return lamb(x,y,cTheta)
    return caca

diff1_list = []
diff0_list = []
CUTOFF = 1e-100 #impose a cutoff on the value of the gaussian (aka dirac delta pretending to be nicer than it actually is)

def getCorrectedEnergies(entry):

    pg1 = vector(entry.g1p1, entry.g1p2, entry.g1p3)
    pg2 = vector(entry.g2p1, entry.g2p2, entry.g2p3)
    e1 = vmod(pg1)
    e2 = vmod(pg2)
    cTh = cos(ACO(pg1,pg2)) ### Either this or the corrected cTh by using the SV position and the cluster positions
   
    event_eqs = []
    for eq in mylambs:
        event_eqs.append(getfunction(eq,cTh)) #append equations as a function of the 2 energies
    ## print "getfunction(bastada1,cTh)",getfunction(bastada1,cTh)
    ## event_eqs = [getfunction(bastada1,cTh),getfunction(bastada2,cTh)]
    ## diff0 = event_eqs[0](e1,e2)
    ## diff1 = event_eqs[1](e1,e2)
    ## print "diff0=", diff0
    ## diff0_list.append(diff0)
    ## diff1_list.append(diff1)

    Ptotval = PTOT.subs(E1,e1).subs(E2,e2).subs(cTheta,cTh).n()

    #print "Ptotval=",Ptotval
    
    if(Ptotval<=1e-100):
        screwed_evts = 0
        good_evts = 0
        reg_evts = 0
        #print "already 0"
        rot = [e1,e2]

    else:
        good_evts = 1
        try:
            #print "trying..."
            rot = mpmath.findroot(event_eqs, (e1,e2))#,tol = 1e14)
            ## rot = fsolve(event_eqs,(e1,e2))
            screwed_evts = 0
            reg_evts = 0
        except ValueError:
            print "Warning: No precise solution found, increasing the tolerance"
            rot = mpmath.findroot(event_eqs, (e1,e2),tol = 1e14) #e1,e2 as starting points
            #tolerance so big so that python does his best
            screwed_evts = 0
            reg_evts = 1
        except ZeroDivisionError:
            print "ZeroDivision Error. Momenta left uncorrected"
            rot = [e1,e2]
            screwed_evts = 1
            reg_evts = 0
        ## except TypeError:
        ##     #print "Something is fucked up. mpmath returned a TypeError: out() takes exactly 2 arguments (1 given)"
        ##     screwed_evts = 1
        ##     rot = [e1,e2]
            
    ### Corrected energies
            
    e_corr_1 = rot[0]
    e_corr_2 = rot[1]
    
    if(e_corr_1 != e1 or e_corr_2 != e2): solved_evts = 1
    else: solved_evts = 0
    
    return e_corr_1, e_corr_2,reg_evts,screwed_evts
    ## return good_evts,screwed_evts,solved_evts

total_good_evts = 0
screwed_evts = 0
solved_evts = 0
reg_evts = 0
ie = 0
pCUT = 1.0
out = []
pbmatched_evts = 0
for entry in t:
    if entry.mo1 != 310 : continue
    if entry.mo2 != 310 : continue  
    if not entry.mc_pi0_px : continue    
    if not entry.mc_Gamma_px : continue
    #if not entry.mc_Gamma_py : continue
    #if not entry.mc_Gamma_pz : continue
    if not entry.mc_gamma_px : continue
    #if not entry.mc_gamma_py : continue
    if entry.mc_gamma_pz < 0: continue
    if(entry.mc_gamma_ez < 0): continue
    if(entry.mc_Gamma_ez < 0): continue
    if not (entry.mc_g1_ID == 22): continue #Bender matching
    if not (entry.mc_g2_ID == 22): continue #Bender matching

    print "ie=",ie
    ie += 1

    pmu1 = vector(entry.mu1p1, entry.mu1p2, entry.mu1p3)
    pmu2 = vector(entry.mu2p1, entry.mu2p2, entry.mu2p3)
    pg1 = vector(entry.g1p1, entry.g1p2, entry.g1p3)
    pg2 = vector(entry.g2p1, entry.g2p2, entry.g2p3)
    Mpizero = sqrt(IM2(pg1,pg2, 0, 0)) ## IM2 = invariant mass squared
    Mmumu = sqrt(IM2(pmu1,pmu2, PDG.muon.mass, PDG.muon.mass)) ## IM2 = invariant mass squared
    MKs = sqrt(IM2 ( pmu1+pmu2,  pg1 + pg2, Mmumu, PDG.pi0.mass))# Mpizero))

    SV = vector(entry.SV1,entry.SV2,entry.SV3) #Secondary vertex point

    eg1 = vmod(pg1) #Gamma energies
    eg2 = vmod(pg2)

    g1_pos = vector(entry.g1e1, entry.g1e2, entry.g1e3) #Gamma cluster positions
    g2_pos = vector(entry.g2e1, entry.g2e2, entry.g2e3)

    pg1_Ks_vtx = eg1*vunit(g1_pos-SV) #Modify gamma momenta so that gammas originate from the secondary vtx
    pg2_Ks_vtx = eg2*vunit(g2_pos-SV)
    MpizeroVC = sqrt(IM2(pg1_Ks_vtx,pg2_Ks_vtx,0,0))

    Eg1 = vmod(pg1_Ks_vtx) #should be the same as eg1 (only changes in the direction)
    Eg2 = vmod(pg2_Ks_vtx) #should be the same as eg2
    Eg = Eg1 + Eg2

    PV = vector(entry.PV1,entry.PV2,entry.PV3)
    SV = vector(entry.SV1,entry.SV2,entry.SV3)
    flight = vunit(SV-PV)
    pdm = pmu1 + pmu2
    xu = vcross(vector(0,1,0),flight)
    yu = vcross(flight,xu)
    pdmx_prime = vdot(pdm, xu)
    pdmy_prime = vdot(pdm, yu)
    pdmz_prime = vdot(pdm, flight)

    #p0z_prime = vdot(pg1 + pg2, flight)
    p0z_prime = vdot(pg1_Ks_vtx + pg2_Ks_vtx, flight)
    pm_prime = vector(pdmx_prime, pdmy_prime, pdmz_prime)
    p0_prime = vector(-pdmx_prime, -pdmy_prime, p0z_prime)
    MKsb = sqrt(IM2 ( pm_prime,  p0_prime, Mmumu, PDG.pi0.mass))# Mpizero))

    ## p0z_prime_check = vdot(pg1 + pg2, flight) #dont understand why not pg1_Ks_vtx in previous scripts
    ## pm_prime = vector(pdmx_prime, pdmy_prime, pdmz_prime)
    ## p0_prime_check = vector(-pdmx_prime, -pdmy_prime, p0z_prime_check)
    ## MKsb_check = sqrt(IM2 ( pm_prime,  p0_prime_check, Mmumu, PDG.pi0.mass))# Mpizero))
    ## #same thing as MKsb

    DeltaG1p = (entry.g1p1 - entry.mc_Gamma_px)**2 +  (entry.g1p2 - entry.mc_Gamma_py)**2
    DeltaG2p = (entry.g2p1 - entry.mc_Gamma_px)**2 +  (entry.g2p2 - entry.mc_Gamma_py)**2

    G_is_1p =   DeltaG1p < DeltaG2p
    G_is_2p = not G_is_1p
    mc_p1x = entry.mc_Gamma_px*G_is_1p + entry.mc_gamma_px*G_is_2p
    mc_p1y = entry.mc_Gamma_py*G_is_1p + entry.mc_gamma_py*G_is_2p
    mc_p1z = entry.mc_Gamma_pz**G_is_1p + entry.mc_gamma_pz*G_is_2p

    mc_p2x = entry.mc_Gamma_px*G_is_2p + entry.mc_gamma_px*G_is_1p
    mc_p2y = entry.mc_Gamma_py*G_is_2p + entry.mc_gamma_py*G_is_1p
    mc_p2z = entry.mc_Gamma_pz**G_is_2p + entry.mc_gamma_pz*G_is_1p

    #Differences     montecarlo truth - reconstructed momenta
    if(mc_p1x!=0):
        dp1x = abs((mc_p1x - pg1[0])/(mc_p1x))#+0.01)) #+0.01 so that it doesn't raise an error when mc_p1x (I assume 0.01 is a negligible quantity to add)
    else:
        dp1x = (pg1[0] == mc_p1y) #1 when True, 0 when False. Valid because pCUT is 1, if pCUT is bigger still OK because it falls withing the allowed range
    if(mc_p1y != 0):
        dp1y = abs((mc_p1y - pg1[1])/(mc_p1y))#+0.01))
    else:
        dp1y = pg1[1] == mc_p1y
    if(mc_p2x != 0):
        dp2x = abs((mc_p2x - pg2[0])/(mc_p2x))#+0.01))
    else:
        dp2x = pg2[0] == mc_p2x
    if(mc_p2y != 0):
        print "mcp2y",mc_p2y
        dp2y = abs((mc_p2y - pg2[1])/(mc_p2y))#+0.01))
    else:
        dp2y = pg2[1] == mc_p2y

    maxdp = max([dp1x,dp1y,dp2x,dp2y])

    mydic = {}
    #p-matching:
    
    if(maxdp <= pCUT):
        pbmatched_evts += 1
        eg1corr, eg2corr,p,q = getCorrectedEnergies(entry) #my correction
        reg_evts += p
        screwed_evts += q
        pg1corr = eg1corr*vunit(pg1)
        pg2corr = eg2corr*vunit(pg2)
        Mpizerocorr = sqrt(IM2(pg1corr,pg2corr, 0, 0))
        pg1_Ks_vtx_mir = eg1corr*vunit(g1_pos-SV) #Modify gamma momenta so that gammas originate from the secondary vtx
        pg2_Ks_vtx_mir = eg2corr*vunit(g2_pos-SV)
        MpizeroVCmir = sqrt(IM2(pg1_Ks_vtx_mir,pg2_Ks_vtx_mir, 0, 0)) #my constraint + VC one
        
        Eg1_mir = vmod(pg1_Ks_vtx_mir) #should be the same as eg1corr (only changes in the direction)
        Eg2_mir = vmod(pg2_Ks_vtx_mir) #should be the same as eg2corr
        Eg_mir = Eg1_mir + Eg2_mir

        p0z_prime_mir = vdot(pg1_Ks_vtx_mir + pg2_Ks_vtx_mir, flight)
        pm_prime = vector(pdmx_prime, pdmy_prime, pdmz_prime)
        p0_prime_mir = vector(-pdmx_prime, -pdmy_prime, p0z_prime_mir)
        MKsb_mir = sqrt(IM2 ( pm_prime,  p0_prime_mir, Mmumu, PDG.pi0.mass))# Mpizero))
        
        mydic["eg1"] = eg1
        mydic["Mpizero"] = Mpizero #no constraint
        mydic["MpizeroVC"] = MpizeroVC #imposing that gammas come from sv
        mydic["MpizeroVCmir"] = MpizeroVCmir #my constraint + VC one
        mydic["MKs"] = MKs #no constraint
        mydic["MKsb"] = MKsb #dm + vc correction (the same with and without vc correction, checked)
        mydic["MKsb_mir"] = MKsb_mir #dm + vc+ ml correction
        
    else:
        eg1corr = 5.e08
        mydic["eg1"] = 5.e08
        mydic["Mpizero"] = 5.e08
        mydic["MpizeroVC"] = 5.e08
        mydic["MpizeroVCmir"] = 5.e08 #my constraint + VC one
        mydic["MKs"] = 5.e08 #no constraint
        mydic["MKsb"] = 5.e08 #dm + vc correction
        mydic["MKsb_mir"] = 5.e08 #dm + vc + ml correction
        MKsb_mir = 5.e08
        MpizeroVCmir = 5.e08
        MKsb_pmatch = 5.e08
    
    mydic["eg1corr"] = eg1corr
    out.append(mydic)

out = channelData(out)
out.save("my_tree")
tmir,fmir = getTuple("my_tree")

## Get momenta of the photons
## Correction of Veronika with it
## Reconstruction of MKs with it

## TODO
## pmatching at first?
## checkear que tuplas uso, dond ey con que matching
