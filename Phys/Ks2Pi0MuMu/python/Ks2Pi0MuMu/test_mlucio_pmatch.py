from ROOT import *
from Urania import PDG
from SomeUtils.alyabar import *
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from triggerclass import *
from Urania import PDG
from numpy import roots,isreal,random

f = TFile("Tuple_MC_Frankfurt.root")
t = f.Get("T")
Etop = 25000.0
nbins = 400
hmcrec = TH2F("E_MC vs E_REC","E_MC vs E_REC",nbins,0,Etop,nbins,0,Etop)#200,0,22000,200,0,22000)
hmcrec_pmatched = TH2F("E_MC vs E_REC (pmatched)","E_MC vs E_REC (pmatched)",nbins,0,Etop,nbins,0,Etop)#200,0,22000,200,0,22000)
hmcrec_ematched = TH2F("E_MC vs E_REC (ematched)","E_MC vs E_REC (ematched)",nbins,0,Etop,nbins,0,Etop)#200,0,22000,200,0,22000)
hmcrec_matched = TH2F("E_MC vs E_REC (matched)","E_MC vs E_REC (matched)",nbins,0,Etop,nbins,0,Etop)#200,0,22000,200,0,22000)
total_events = 0
pmatched_events = 0
ematched_events = 0
ematched1_events = 0
ematched2_events = 0
matched_events = 0
matched2_events = 0

L1 = 40.4 #inner part of ecal cell size (mm)
L2 = 60.6 #middle part of ecal cell size (mm)
L3 = 121.2 #outer part of ecal cell size (mm)
c1 = 8*L1 
c2 = 16*L2
c3 = 32*L3
sf = sqrt(2.)
DR1 = sf*L1
DR2 = sf*L2
DR3 = sf*L3
CUT = 1.0
pCUT = 1.0
def ECALRegion(maxe):
    """according to the coordinates of the gammas, searchs for the position in the ECAL (inner, middle, outer) and returns the maximum distance between MC and REC allowed, given the size of the corresponding cell (assuming both have to be detected in the same cell)"""
    if maxe <= c1: return 1
    elif maxe <= c2: return 2
    elif maxe <= c3: return 3
    else : return 4

ECALRegionLimit = { 1: DR1, 2:DR2, 3:DR3, 4: DR3}
out = []
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
    total_events += 1

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

    p0z_prime = vdot(pg1 + pg2, flight)
    pm_prime = vector(pdmx_prime, pdmy_prime, pdmz_prime)	
    p0_prime = vector(-pdmx_prime, -pdmy_prime, p0z_prime)
    MKsb = sqrt(IM2 ( pm_prime,  p0_prime, Mmumu, PDG.pi0.mass))# Mpizero))

#Get the montecarlo components of the momenta for the photons:
       
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
    dp1x = abs((mc_p1x - pg1[0])/(mc_p1x+0.01)) #+0.01 so that it doesn't raise an error when mc_p1x (I assume 0.01 is a negligible quantity to add)
    dp1y = abs((mc_p1y - pg1[1])/(mc_p1y+0.01))
    dp2x = abs((mc_p2x - pg2[0])/(mc_p2x+0.01))
    dp2y = abs((mc_p2y - pg2[1])/(mc_p2y+0.01))

    #Get the montecarlo components of the clusters:
    DeltaG1e = (entry.g1e1 - entry.mc_Gamma_ex)**2 + (entry.g1e2 - entry.mc_Gamma_ey)**2
    DeltaG2e = (entry.g2e1 - entry.mc_Gamma_ex)**2 + (entry.g2e2 - entry.mc_Gamma_ey)**2

    G_is_1e =   DeltaG1e < DeltaG2e
    G_is_2e = not G_is_1e
    mc_e1x = entry.mc_Gamma_ex*G_is_1e + entry.mc_gamma_ex*G_is_2e
    mc_e1y = entry.mc_Gamma_ey*G_is_1e + entry.mc_gamma_ey*G_is_2e
    mc_e1z = entry.mc_Gamma_ez**G_is_1e + entry.mc_gamma_ez*G_is_2e

    mc_e2x = entry.mc_Gamma_ex*G_is_2e + entry.mc_gamma_ex*G_is_1e
    mc_e2y = entry.mc_Gamma_ey*G_is_2e + entry.mc_gamma_ey*G_is_1e
    mc_e2z = entry.mc_Gamma_ez**G_is_2e + entry.mc_gamma_ez*G_is_1e 

    de1x = (mc_e1x - g1_pos[0])
    de1y = (mc_e1y - g1_pos[1])
    de2x = (mc_e2x - g2_pos[0])
    de2y = (mc_e2y - g2_pos[1])

    mc_p1 =  vector(mc_p1x,mc_p1y,mc_p1z)
    mc_eg1 = vmod(mc_p1)
    mc_p2 = vector(mc_p2x,mc_p2y,mc_p2z)
    mc_eg2 = vmod(mc_p2)   
    mc_e1 = vector(mc_e1x,mc_e1y,mc_e1z)
    mc_e2 = vector(mc_e2x,mc_e2y,mc_e2z)

    maxe1 = max(abs(mc_e1y),abs(mc_e1x))
    maxe2 = max(abs(mc_e2y),abs(mc_e2x))
    maxdp = max([dp1x,dp1y,dp2x,dp2y])
  
    p1mod = eg1
    p2mod = eg2

    mydic = {}
    mydic["p1mod"] = p1mod
    mydic["p2mod"] = p2mod
    mydic["p1x"] = pg1[0]
    mydic["p1y"] = pg1[1]
    mydic["p1z"] = pg1[2]
    mydic["p2x"] = pg2[0]
    mydic["p2y"] = pg2[1]
    mydic["p2z"] = pg2[2]
    mydic["mc_p1"] = mc_eg1
    mydic["mc_p2"] = mc_eg2
    mydic["mc_p1x"] = mc_p1x
    mydic["mc_p1y"] = mc_p1y
    mydic["mc_p1z"] = mc_p1z
    mydic["mc_p2x"] = mc_p2x
    mydic["mc_p2y"] = mc_p2y
    mydic["mc_p2z"] = mc_p2z
    mydic["ct_rec"] = cos(ACO(pg1,pg2))
    mydic["ct_mc"] = cos(ACO(mc_p1,mc_p2))
    mydic["ct_mc_check"] = cos(ACO(mc_p2,mc_p1))
    mydic["sqrt_2E1E2_rec"] = sqrt(2*p1mod*p2mod)
    mydic["sqrt_2E1E2_tr"] = sqrt(2*mc_eg2*mc_eg1)
    mydic["sqrt_E1E2_rec"] = sqrt(p1mod*p2mod)
    mydic["sqrt_E1E2_tr"] = sqrt(mc_eg2*mc_eg1)
    mydic["sqrt_1mct_rec"] = sqrt(1-cos(ACO(pg1,pg2)))
    mydic["sqrt_1mct_tr"] = sqrt(1-cos(ACO(mc_p2,mc_p1)))   
    mydic["d2E"] = (sqrt(2*p1mod*p2mod) - sqrt(2*mc_eg2*mc_eg1))#/sqrt(2*mc_eg2*mc_eg1)
    mydic["dE"] = (sqrt(p1mod*p2mod) - sqrt(mc_eg2*mc_eg1))#/sqrt(mc_eg2*mc_eg1)
    mydic["dct"] = (sqrt(1-cos(ACO(pg1,pg2))) - sqrt(1-cos(ACO(mc_p2,mc_p1))))#/sqrt(1-cos(ACO(mc_p2,mc_p1)))       
    mydic["de1x"] = de1x
    mydic["de1y"] = de1y
    mydic["de2x"] = de2x
    mydic["de2y"] = de2y
    mydic["dp1x"] = dp1x
    mydic["dp1y"] = dp1y
    mydic["dp2x"] = dp2x
    mydic["dp2y"] = dp2y
    mydic["mc_e2y"] = mc_e2y
    mydic["mc_e2x"] = mc_e2x
    mydic["mc_e1x"] = mc_e1x
    mydic["mc_e1y"] = mc_e1y  
    mydic["maxe1"] = maxe1
    mydic["maxe2"] = maxe2
   
    #no matching
    hmcrec.Fill(p1mod,mc_eg1)
    g1R = ECALRegion(maxe1) #returns either 1, 2 or 3
    g2R = ECALRegion(maxe2)
    mydic["R1"] = g1R
    mydic["R2"] = g2R
    Limit1 = ECALRegionLimit[g1R]
    Limit2 = ECALRegionLimit[g2R]
    de1xS = mydic["de1x"]*1./Limit1 #escala, idealmente se veria __| |__
    de1yS = mydic["de1y"]*1./Limit1
    de2xS = mydic["de2x"]*1./Limit2
    de2yS = mydic["de2y"]*1./Limit2
    mydic["de1xS"] = de1xS
    mydic["de1yS"] = de1yS
    mydic["de2xS"] = de2xS
    mydic["de2yS"] = de2yS
    maxde1S = max([abs(de1xS),abs(de1yS)])
    maxde2S = max([abs(de2xS),abs(de2yS)])

    
    #e-matching
    #if max(abs(de1x),abs(de1y)) <= Limit1:
    if max(maxde1S,maxde2S) <= CUT:
        mydic["de1x_ematched"] = de1x
        mydic["de1y_ematched"] = de1y
        mydic["de2x_ematched"] = de2x
        mydic["de2y_ematched"] = de2y

    else:
        mydic["de1x_ematched"] = 5.e08
        mydic["de1y_ematched"] = 5.e08
        mydic["de2x_ematched"] = 5.e08
        mydic["de2y_ematched"] = 5.e08
        
    """if maxde1S <= CUT:
        ematched1_events += 1
        mydic["de1x_ematched"] = de1x
        mydic["de1y_ematched"] = de1y
    else:
        mydic["de1x_ematched"] = 5.e08
        mydic["de1y_ematched"] = 5.e08
    #if max(abs(de2x),abs(de2y)) <= Limit2:
    if maxde2S <= CUT:
        ematched2_events += 1
        mydic["de2x_ematched"] = de2x
        mydic["de2y_ematched"] = de2y
    else:
        mydic["de2x_ematched"] = 5.e08
        mydic["de2y_ematched"] = 5.e08
    """    
    if (max(maxde1S,maxde2S) <= CUT): ematched_events += 1
    
    #p-matching
    if(maxdp <= pCUT):
        pmatched_events += 1
        hmcrec_pmatched.Fill(p1mod,mc_eg1)
        mydic["de1x_pmatched"] = (de1x)
        mydic["de1y_pmatched"] = (de1y)
        mydic["de2x_pmatched"] = (de2x)
        mydic["de2y_pmatched"] = (de2y)
    else:
        mydic["de1x_pmatched"] = 5.e08
        mydic["de1y_pmatched"] = 5.e08
        mydic["de2x_pmatched"] = 5.e08
        mydic["de2y_pmatched"] = 5.e08
        
    #pe-matching
    #if(maxdp <= 1.0 and max(abs(de1x),abs(de1y)) <= Limit1 and max(abs(de2x),abs(de2y)) <= Limit2):
    if(maxdp <= pCUT and maxde1S <= CUT and maxde2S <=CUT ):
        mydic["de1x_pe_matched"] = de1x
        mydic["de1y_pe_matched"] = de1y
        mydic["de2x_pe_matched"] = de2x
        mydic["de2y_pe_matched"] = de2y
        mydic["MKsb_notmatched"] = 5.e08
        mydic["MKs_notmatched"] = 5.e08
        matched_events += 1
        hmcrec_matched.Fill(p1mod,mc_eg1)
    else:
        mydic["de1x_pe_matched"] = 5.e08
        mydic["de1y_pe_matched"] = 5.e08
        mydic["de2x_pe_matched"] = 5.e08
        mydic["de2y_pe_matched"] = 5.e08
        mydic["MKsb_notmatched"] = MKsb
        mydic["MKs_notmatched"] = MKs

    out.append(mydic)

out = channelData(out)
out.save("my_tree")
tmir,fmir = getTuple("my_tree")

gROOT.ProcessLine('.L RooIpatia2.cxx+')

#tmir.Draw("de1x:de1y", "de1x_ematched > 1000 && abs(de1x)<1000 && abs(de1y)<1000 && de1x_pmatched<1e7") #not e-matched, but p-matched
#fsave = TFile("hmcrec_10slices_Emax20GeV_400bins.root","recreate")
"""a2 = RooRealVar("a2","a2",200)
a = RooRealVar("a","a" , 200)
n = RooRealVar("n","n",1.)
n2 = RooRealVar("n2","n2",1)"""
beta = RooRealVar("beta","beta",0)
zeta = RooRealVar("zeta","zeta",3e-03)#0,2)
#zeta.setVal(1e-05) #to be checked
#l = RooRealVar("l","l",-1,-10,10)
l = RooRealVar('l','l',-0.85)
s_list = [] #ipa_s
m_list = [] #ipa_m
z_list = [] #zeta
l_list = [] #l
en_list = [] #energy
a_list = []
a2_list = []
n_list = []
n2_list = []

fsave = TFile("mirimola3.root","recreate")

for k in range(1,10):
    print "#################################k=",k,"################################"
    Emin = 32*k*Etop/nbins
    Emax = (32 + 32*k)*Etop/nbins
    xmin = Emin - 6000
    xmax = Emax + 6000
    if(xmin<0): xmin = 0
    if(xmax>Etop): xmax = Etop
    bmax = int(xmax*nbins/Etop)
    bmin = int(xmin*nbins/Etop)
    print "xmin=",xmin
    print "xmax=",xmax
    print "bmin=",bmin
    print "bmax=",bmax
    hf = hmcrec.ProjectionY('h'+str(k),32*k,32 + 32*k)
    hf_pmatched = hmcrec_pmatched.ProjectionY('hpmatched'+str(k),32*k,32 + 32*k)#bmin,bmax)
    hf.Write()
    hf_pmatched.Write()
    hf_pmatched.Fit("gaus")
    start_mean = hf_pmatched.GetFunction("gaus").GetParameter(1)
    start_sigma = hf_pmatched.GetFunction("gaus").GetParameter(2)
    x = RooRealVar("x","x",0,Etop) #to be done: check the limits
    hf2 = RooDataHist('h2'+str(k),'h2'+str(k),RooArgList(x),hf)
    hf2_pmatched = RooDataHist('h2_pmatched'+str(k),'h2_pmatched'+str(k),RooArgList(x),hf_pmatched)
    fr = x.frame()
    hf2_pmatched.plotOn(fr,RooFit.Binning(200))
    a2 = RooRealVar("a2","a2",100,1000)##200)
    a = RooRealVar("a","a" , 100,1000)#200)
    n = RooRealVar("n","n",0.5,5)#1.)
    n2 = RooRealVar("n2","n2",0.5,5)#1)
    ipa_s = RooRealVar("ipa_s","ipa_s",1000,50000)#start_sigma,0,7000)#Etop)#0.5*start_sigma, 2*start_sigma) #sigma
    ipa_m = RooRealVar("ipa_m","ipa_m",xmin,xmax)#start_mean,0,xmax)#0,Etop)#0.75*start_mean, 1.5*start_mean) #mean: lower limit to be corrected
    ipatia = RooIpatia2("ipatia","resolution",x,l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)
    ipatia.fitTo(hf2_pmatched,RooFit.Minos(1),RooFit.Range(xmin,xmax))
    ipatia.plotOn(fr,RooFit.LineColor(kMagenta))
    s_list.append(ipa_s.getVal())
    m_list.append(ipa_m.getVal())
    #z_list.append(zeta.getVal())
    l_list.append(l.getVal())
    a_list.append(a.getVal())
    a2_list.append(a2.getVal())
    n_list.append(n.getVal())
    n2_list.append(n2.getVal())
    en_list.append((16 + 32*k)*Etop/nbins)
    fr.Write()

#Fit first slice separately:

k = 0
a2 = RooRealVar("a2","a2",100,1000)#200)
a = RooRealVar("a","a" , 100,1000)#200)
n = RooRealVar("n","n",0.5,5)#1.)
n2 = RooRealVar("n2","n2",0.5,5)#1)
hf = hmcrec.ProjectionY('h10',32*k,32 + 32*k)
hf_pmatched = hmcrec_pmatched.ProjectionY('hpmatched10',32*k,32 + 32*k)
hf.Write()
hf_pmatched.Write()
Emin = 32*k*Etop/nbins
Emax = (32 + 32*k)*Etop/nbins
xmin = Emin - 6000
xmax = Emax + 6000
if(xmin<0): xmin = 0
if(xmax>Etop): xmax = Etop
x = RooRealVar("x","x",0,Etop)
hf2 = RooDataHist('h2'+str(k),'h2'+str(k),RooArgList(x),hf)
hf2_pmatched = RooDataHist('h2_pmatched'+str(k),'h2_pmatched'+str(k),RooArgList(x),hf_pmatched)
fr = x.frame()
hf2_pmatched.plotOn(fr,RooFit.Binning(200))
ipa_s = RooRealVar("ipa_s","ipa_s",1000,50000)#Etop)#0.5*start_sigma, 2*start_sigma) #sigma
ipa_m = RooRealVar("ipa_m","ipa_m",1000,1800)#0,Etop)#0.75*start_mean, 1.5*start_mean) #mean: lower limit to be corrected
ipatia = RooIpatia2("ipatia","resolution",x,l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)
ipatia.fitTo(hf2_pmatched,RooFit.Minos(1),RooFit.Range(0,5000))
ipatia.plotOn(fr,RooFit.LineColor(kMagenta))
fr.Write()
s_list.append(ipa_s.getVal())
m_list.append(ipa_m.getVal())
z_list.append(zeta.getVal())
l_list.append(l.getVal())
a_list.append(a.getVal())
a2_list.append(a2.getVal())
n_list.append(n.getVal())
n2_list.append(n2.getVal())
en_list.append((16 + 32*k)*Etop/nbins)

fsave.Close()

fsavep = TFile("my_graphs3.root","recreate")
gm,gs1,gl1 = TGraph(),TGraph(),TGraph()
gs2,gl2 = TGraph(),TGraph()
gs3,gl3 = TGraph(),TGraph()

for i in range(len(m_list)):
    gm.SetPoint(i,en_list[i],m_list[i])
    gs1.SetPoint(i,en_list[i],s_list[i])
    gl1.SetPoint(i,en_list[i],l_list[i])
    gs2.SetPoint(i,en_list[i]**2,s_list[i])
    gl2.SetPoint(i,en_list[i]**2,l_list[i])
    gs3.SetPoint(i,sqrt(en_list[i]),s_list[i])
    gl3.SetPoint(i,sqrt(en_list[i]),l_list[i])
    print "i=",i

#gm.Fit('pol1')
gm.Write('mean vs energy')
gs1.Write('sigma vs energy')
gl1.Write('l vs energy')
gs2.Write('sigma vs energy squared')
gl2.Write('l vs energy squared')
gs3.Write('sigma vs square root of energy')
gl3.Write('l vs square root of energy')

gm.Fit('pol1')
mean_constant = gm.GetFunction('pol1').GetParameter(0)
mean_slope = gm.GetFunction('pol1').GetParameter(1)
gs1.Fit('pol1')
sigma_constant = gs1.GetFunction('pol1').GetParameter(0)
sigma_slope = gs1.GetFunction('pol1').GetParameter(1)

fsavep.Close()

## def Ipatia function :
## energy as an argument
## for each energy you have well defined all the Ipatia parameters
## -->thus, it is possible to get the Ipatia PDF value 

## 1. construct the function
## 2. optimize it

def Ipatia(Erecval,xval):
    Erec = RooRealVar('Erec','Erec',Erecval)
    x = RooRealVar('x','x',xval)
    mean_p0 = RooRealVar('mean_p0','mean_p0',mean_constant)
    mean_p1 = RooRealVar('mean_p1','mean_p1',mean_slope)
    ipa_m = RooFormulaVar('ipa_m','ipa_m','mean_p0 + mean_p1*Erec',RooArgList(mean_p0,mean_p1,Erec))
    sigma_p0 = RooRealVar('sigma_p0','sigma_p0',sigma_constant)
    sigma_p1 = RooRealVar('sigma_p1','sigma_p1',sigma_slope)
    ipa_s = RooFormulaVar('ipa_s','ipa_s','sigma_p0 + sigma_p1*Erec',RooArgList(sigma_p0,sigma_p1,Erec))    
    ipatia = RooIpatia2("ipatia","resolution",x,l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)
    return ipatia.getVal()

Erecval = 3000
gmir = TGraph()
for b in range(100):
    print "estoy harta ya ",b
    #wanna do between Erecval-10000 and Erecval+10000 => Erecval + m, m between -10000 and 10000
    m = -10000 + 200*b
    xval = Erecval + m
    gmir.SetPoint(b,xval,Ipatia(Erecval,xval))
