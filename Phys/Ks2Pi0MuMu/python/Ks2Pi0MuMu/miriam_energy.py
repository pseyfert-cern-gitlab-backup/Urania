from ROOT import *
from Urania import *
AccesPackage("Bs2MuMu")
AccesPackage("Urania")
import sys
sys.path.append("..")
from smartpyROOT import *
f = TFile("Tuple_MC_Petnica.root")
t = f.Get("T")

"""
Update from test_mlucio_old.py, changing the order in which de constraints are applied
"""

#f = TFile("bkgMini.root")
#t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
#BREAK
from SomeUtils.alyabar import *
from Urania import PDG
from numpy import roots,isreal,random
#from random import random as rnd

def pg_mod(p1,p2,mpi0): 
    """returns the 2 photons momenta (forcing IM2=m_pi_0**2, keeping the modulus of the momenta as constant)"""
    p1x_old = p1[0]
    p1y_old = p1[1]
    p1z_old = p1[2]
    p2x_old = p2[0]
    p2y_old = p2[1]
    p2z_old = p2[2]
    p2mod = vmod(p2)
    p1mod = vmod(p1)

    k = 0.5*mpi0**2 + p1x_old*p2x_old + p1y_old*p2y_old
    A = p2mod**2 - p2z_old**2
    B = -2*k*p2z_old
    C = p2mod**2*(p1x_old**2 + p1y_old**2) - k**2
    
    """
    k_pz = 0.5*IM**2 + p1x*p2x + p1y*p2y - p2z**2
    A_pz = p2mod**2 - p2z**2
    B_pz = -2*p2z*p2mod**2 - 2*k_pz*p2z
    C_pz = (p1x**2 + p1y**2 + p2z**2)*p2mod**2 - k_pz**2"""

    
    """
    --> pz = p1z+p2z, as problematic as p1z
    """
    """
    Modify pz, when there is a problem => do a scan => throw a random number around p1z,p2z,...etc
    I would prefer not to modify px and py stuff --> it's a pain in the ass (px,py have to remain the same)
    """
    nattempts = 0
        #print "complex values fory the momenta!!"
    p1_new = vector(p1x_old,p1y_old,p1z_old)
    p2_new = vector(p2x_old,p2y_old,p2z_old)
    im = sqrt(IM2(p1_new,p2_new,0.,0.))
    while(abs(im-mpi0)>0.10*mpi0): #reconstructed mass from the photon momenta further from mpi0 more than 10% the value of mpi0 itself
        #print "using numeric scan..."
        p1y = p1y_old - 0.3*p1y_old*random.random()
        p2y = p2y_old - 0.3*p2y_old*random.random()
        #p1z = random.normal(p1z_old,abs(0.5*p1z_old),1)
        #p2z = random.normal(p2z_old,abs(0.5*p1z_old),1)
        #p1x = random.normal(p1x_old,abs(0.3*p1x_old),1)
        #p2x = random.normal(p1x_old,abs(0.3*p1x_old),1)
        p1x = p1x_old - 0.3*p1x_old*random.random()
        p2x = p2x_old - 0.3*p2x_old*random.random()
        p1z = sqrt(p1mod**2 - (p1x**2 + p1y**2))
        p2z = sqrt(p2mod**2 - (p2x**2 + p2y**2))
        p1_new = vector(p1x,p1y,p1z)
        p2_new = vector(p2x,p2y,p2z)
        im = sqrt(IM2(p1_new,p2_new,0.,0.))
        nattempts += 1
        #print "natetmpts=",nattempts
        if(nattempts>100000): BREAK 
    return p1_new,p2_new

h = TH1F("A","A", 100,400, 600)
hb = TH1F("B","B", 100,400, 600)
hnewb = TH1F("B","B",100,400,600)
href = TH1F("A","A", 100, 400, 600)
hpi0 = TH1F("pi0", "pi0", 100, 100, 170)
hpi0_corrected = TH1F("corrected pi0","corrected pi0",100,0,170)
hpi0_new = TH1F("new pi0","new pi0",100,0,170)
total_events = 0
wrong_events = 0
hs = TH1F("resolution","resolution",100,-20000,20000)
hs_other = TH1F("other resolution","other resolution",100,-1000,1000)
hshit = TH1F("shit","shit",100,0,1000)
hmceg1 = TH1F("energy","energy",100,0,30000)
hprofile = TH1F("profile","profile histo",100,0,30000)
hcheck = TH2F("check","check",100,0,30000,100,-20000,20000);
hcheck_other = TH2F("other check","other check",100,-1000,1000,100,-1000,1000)
gs = TGraph()
gVC = TGraph()
gc = TGraph()
gs_other = TGraph()
ie = 0

for entry in t:
    if entry.mo1 != 310 : continue
    if entry.mo2 != 310 : continue
    if not entry.mc_pi0_px : continue
    pmu1 = vector(entry.mu1p1, entry.mu1p2, entry.mu1p3)
    pmu2 = vector(entry.mu2p1, entry.mu2p2, entry.mu2p3)
    pg1 = vector(entry.g1p1, entry.g1p2, entry.g1p3)
    pg2 = vector(entry.g2p1, entry.g2p2, entry.g2p3)
    Mpizero = sqrt(IM2(pg1,pg2, 0, 0)) ## IM2 = invariant mass squared
    Mmumu = sqrt(IM2(pmu1,pmu2, PDG.muon.mass, PDG.muon.mass)) ## IM2 = invariant mass squared
    MKs = sqrt(IM2 ( pmu1+pmu2,  pg1 + pg2, Mmumu, PDG.pi0.mass))# Mpizero))
    
    h.Fill(MKs)
    href.Fill(entry.KSmass)
    hpi0.Fill( Mpizero)


    SV = vector(entry.SV1,entry.SV2,entry.SV3) #Secondary vertex point

    eg1 = vmod(pg1) #Gamma energies
    eg2 = vmod(pg2)
    
    g1_pos = vector(entry.g1e1, entry.g1e2, entry.g1e3) #Gamma cluster positions
    g2_pos = vector(entry.g2e1, entry.g2e2, entry.g2e3)

    pg1_Ks_vtx = eg1*vunit(g1_pos-SV) #Modify gamma momenta so that gammas originate from the secondary vtx
    pg2_Ks_vtx = eg2*vunit(g2_pos-SV) 
 
    pg1_new,pg2_new = pg_mod(pg1_Ks_vtx,pg2_Ks_vtx,PDG.pi0.mass)
    Mpizero_new = sqrt(IM2(pg1_new,pg2_new,0,0))
    hpi0_new.Fill(Mpizero_new)

    Eg1 = vmod(pg1_Ks_vtx) #should be the same as eg1 (only changes in the direction)
    Eg2 = vmod(pg2_Ks_vtx) #should be the same as eg2
    Eg = Eg1 + Eg2	

    MKs_new = sqrt(IM2 ( pmu1+pmu2,  pg1_new + pg2_new, Mmumu, PDG.pi0.mass))

    PV = vector(entry.PV1,entry.PV2,entry.PV3)
    SV = vector(entry.SV1,entry.SV2,entry.SV3)
    flight = vunit(SV-PV)
    pdm = pmu1 + pmu2
    xu = vcross(vector(0,1,0),flight)
    yu = vcross(flight,xu)
    pdmx_prime = vdot(pdm, xu)
    pdmy_prime = vdot(pdm, yu)
    pdmz_prime = vdot(pdm, flight)

    p0z_prime = vdot(pg1 + pg2, flight)
    p0z_new_prime = vdot(pg2_new + pg2_new, flight)	
    	
    pm_prime = vector(pdmx_prime, pdmy_prime, pdmz_prime)
    p0_new_prime = vector(-pdmx_prime, -pdmy_prime, p0z_new_prime)	
    p0_prime = vector(-pdmx_prime, -pdmy_prime, p0z_prime)
    MKsnewb = sqrt(IM2 (pm_prime, p0_new_prime, Mmumu, PDG.pi0.mass))
    MKsb = sqrt(IM2 ( pm_prime,  p0_prime, Mmumu, PDG.pi0.mass))# Mpizero))
    hb.Fill(MKsb)
    hnewb.Fill(MKsnewb)

    #Resolution as a function of the energy (uncertainty law):
    
    mc_p1x = entry.mc_Gamma_px*(abs(entry.g1p1 - entry.mc_Gamma_px) < abs(entry.g1p1 - entry.mc_gamma_px)) + entry.mc_gamma_px*(abs(entry.g1p1 - entry.mc_Gamma_px) > abs(entry.g1p1 - entry.mc_gamma_px))
    mc_p1y = entry.mc_Gamma_py*(abs(entry.g1p2 - entry.mc_Gamma_py) < abs(entry.g1p2 - entry.mc_gamma_py)) + entry.mc_gamma_py*(abs(entry.g1p2 - entry.mc_Gamma_py) > abs(entry.g1p2 - entry.mc_gamma_py))    
    mc_p1z = entry.mc_Gamma_pz*(abs(entry.g1p3 - entry.mc_Gamma_pz) < abs(entry.g1p3 - entry.mc_gamma_pz)) + entry.mc_gamma_pz*(abs(entry.g1p3 - entry.mc_Gamma_pz) > abs(entry.g1p3 - entry.mc_gamma_pz))

    mc_p2x = entry.mc_Gamma_px*(abs(entry.g2p1 - entry.mc_Gamma_px) < abs(entry.g2p1 - entry.mc_gamma_px)) + entry.mc_gamma_px*(abs(entry.g2p1 - entry.mc_Gamma_px) > abs(entry.g2p1 - entry.mc_gamma_px))
    mc_p2y = entry.mc_Gamma_py*(abs(entry.g2p2 - entry.mc_Gamma_py) < abs(entry.g2p2 - entry.mc_gamma_py)) + entry.mc_gamma_py*(abs(entry.g2p2 - entry.mc_Gamma_py) > abs(entry.g2p2 - entry.mc_gamma_py))
    mc_p2z = entry.mc_Gamma_pz*(abs(entry.g2p3 - entry.mc_Gamma_pz) < abs(entry.g2p3 - entry.mc_gamma_pz)) + entry.mc_gamma_pz*(abs(entry.g2p3 - entry.mc_Gamma_pz) > abs(entry.g2p3 - entry.mc_gamma_pz))


    mc_p1 =  vector(mc_p1x,mc_p1y,mc_p1z)
    mc_eg1 = vmod(mc_p1)
    mc_p2 = vector(mc_p2x,mc_p2y,mc_p2z)
    mc_eg2 = vmod(mc_p2)   


    sigma = Eg1 - mc_eg1;
    other_sigma = (pg1_Ks_vtx[0] - mc_p1x)
    hs.Fill(sigma)
    hs_other.Fill(other_sigma)    
    
    mtog = 1e-03 #MeV to GeV conversion
    sigma_unclaw = sqrt((0.1*sqrt(mc_eg1*mtog))**2 + (0.015)**2)/mtog #computed according to the uncertainty law

    gVC.SetPoint(ie,mc_eg1, sigma_unclaw)
    #gc.SetPoint(ie,mc_eg1,sigma/sigma_unclaw)
    ie += 1
 
    hmceg1.Fill(mc_eg1)
    hcheck.Fill(mc_eg1,sigma)
    hcheck_other.Fill(abs(mc_p1x),other_sigma)
hs_other.Draw()

for k in range(10):
    print "k=",k
    ypoint = hcheck.ProjectionY("",0+k*10,10 + k*10).GetRMS() #slices of 10 bins each
    xpoint = hcheck.GetXaxis().GetBinCenter(k*10 + 5)
    ypoint_other = hcheck_other.ProjectionY("",0+k*10,10+k*10).GetRMS() #slices of 10 bins each
    xpoint_other = hcheck_other.GetXaxis().GetBinCenter(k*10+5)	
    #print "ypoint_other=",ypoint_other
    gs.SetPoint(k,xpoint,ypoint)
    gs_other.SetPoint(k,xpoint_other,ypoint_other)

#gs.Draw("A*")
#gs_other.Draw("A*")

"""Fitting of the x_REC-x_MC (hereafter dx) curve to a Ipatia distribution:"""

dvar = "dE"
dx = RooRealVar(dvar,dvar,-400,400) 
gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx+")
# IPATIA
a2 = RooRealVar("a2","a2",3,1,200)
a = RooRealVar("a","a" , 3,1,200)
n = RooRealVar("n","n",2,1,6)
n2 = RooRealVar("n2","n2",2, 1, 6)
ipa_s = RooRealVar("ipa_s","ipa_s", 20,5., 100) #sigma, TO BE CORRECTED
ipa_m = RooRealVar("ipa_m","ipa_m",-100,100) #mean
beta = RooRealVar("beta","beta",0)
zeta = RooRealVar("zeta","zeta",0.47,0,2)#0,1
zeta.setVal(1e-05)
l = RooRealVar("l","l",-2,-10,-1)

ipatia = RooIpatia2("resolution","resolution",dx,l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2) #mass --> dx
h2s = RooDataHist(dx.GetName(),dx.GetName(),RooArgList(dx), hs_other)
#beta.setVal(0)

fr = dx.frame()
h2s.plotOn(fr, RooFit.Binning(200))
fr.Draw()
ipatia.fitTo(h2s,RooFit.Minos(0),RooFit.Offset(kTRUE))
#ipatia.plotOn(fr,RooFit.LineColor(TColor.GetColor(kBlue)))
#fr.Draw()




    
    
    
