from ROOT import *
from os import system as shell, environ
from Urania import *
AccessPackage("Bs2MuMu")
from merger import *
from smartpyROOT import *
from Urania import PDG
from Bs2JpsiPhiParams.Selections import KKbins, trig_biased, trig_unbiased
from Bs2JpsiPhiParams import ConfigBdJpsiKstBkg4D as PhysBd, peaking as Dianne
from scipy import random as rnd
from SomeUtils.alyabar import *
#from  vasilis import HelicityAngles

tempf = "/tmp/" + user + "/"
shell("mkdir " + tempf)

Bdtuple11 = "~diegoms/vol5/BsJpsiPhi/MC/2011/Bd11_tupleB.root"
Lbtuple11 = "~diegoms/vol5/BsJpsiPhi/MC/2011/Lb11_tupleB.root"

Bdtuple12 = "~diegoms/vol5/BsJpsiPhi/MC/2012/Bd12_tupleB.root"
Lbtuple12 = "~diegoms/vol5/BsJpsiPhi/MC/2012/Lb12_tupleB.root"

#BREAK
jcuts = "&& sel == 1 && sel_cleantail == 1 && time>0.3 && time<14. && sigmat<0.12 && mass>5200. && mass<5550. && abs(mdau1-3090.)<60. && abs(mdau2-1020.)<30. && muplus_track_chi2ndof < 4. && muminus_track_chi2ndof < 4. && Kplus_track_chi2ndof < 4. && Kminus_track_chi2ndof < 4. && (hlt1_excl_biased_dec==1 || hlt1_unbiased_dec==1) && (hlt2_biased==1 || hlt2_unbiased==1)"
#BREAK   
### Use only trueid filtered events
shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsCutApplier.exe " +Bdtuple11 + " DecayTree " + " 'abs(trueid)==511"+jcuts+"'  " + tempf + "Bd_mct11.root")
shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsCutApplier.exe " +Lbtuple11 + " DecayTree " + " 'abs(trueid)==" + str(PDG.Lambda_b0.Tpar.PdgCode()) +jcuts+"' " + tempf + "Lb_mct11.root")
shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsCutApplier.exe " +Bdtuple12 + " DecayTree " + " 'abs(trueid)==511"+jcuts+"'  "  + tempf + "Bd_mct12.root")
shell(environ["SIMPLETOOLSROOT"] +"/"+ environ["CMTCONFIG"] + "/SimpleToolsCutApplier.exe " +Lbtuple12 + " DecayTree " + " 'abs(trueid)==" + str(PDG.Lambda_b0.Tpar.PdgCode())+jcuts +"' " + tempf + "Lb_mct12.root")

gROOT.ProcessLine(\
    "struct m_true{\
     Double_t mass;\
    };")

gROOT.ProcessLine(\
    "struct w_phys{\
     Double_t w;\
    };")
gROOT.ProcessLine(\
    "struct phsp_true{\
     Double_t mass;\
     Double_t cthetaK;\
     Double_t cthetaL;\
     Double_t phi;\
    };")

def add_mass(name1, name2):
    f = TFile(name1)
    t = f.Get("DecayTree/DecayTree")
    f2 = TFile(name2, "recreate")
    t2 = t.CopyTree("(1>0)")
    thingie = m_true()
    branch = t2.Branch("mhh_true", AddressOf(thingie,'mass'), "mhh_true/D")
    for entry in t2:
        p1 = vector(entry.Kplus_TRUEP_X,entry.Kplus_TRUEP_Y, entry.Kplus_TRUEP_Z)
        p2 = vector(entry.Kminus_TRUEP_X,entry.Kminus_TRUEP_Y, entry.Kminus_TRUEP_Z)
        id1 = entry.Kplus_TRUEID
        id2 = entry.Kminus_TRUEID
        if not id1 or not id2:
            thingie.mass = entry.mdau2
            branch.Fill()
            continue
        par1 = PDG.ParticleData(id1)
        par2 = PDG.ParticleData(id2)

        thingie.mass = sqrt(IM2(p1,p2,par1.mass,par2.mass))
        branch.Fill()
    t2.Write("",TObject.kOverwrite)
    f2.Close()

#TLorentzVector::TLorentzVector(Double_t x = 0.0, Double_t y = 0.0, Double_t z = 0.0, Double_t t = 0.0)
def add_wphys_m(name1, name2, weighter):
    from sympy import re
    f = TFile(name1)
    t = f.Get("DecayTree/DecayTree")
    f2 = TFile(name2, "recreate")
    t2 = t.CopyTree("(1>0)")
    thingie = m_true()
    wght = w_phys()
    ws = []
    branch = t2.Branch("mhh_true", AddressOf(thingie,'mass'), "mhh_true/D")
    wph_branch = t2.Branch("wphys", AddressOf(wght,'w'), "wphys/D")
    for entry in t2:
        p1 = vector(entry.Kplus_TRUEP_X,entry.Kplus_TRUEP_Y, entry.Kplus_TRUEP_Z)
        p2 = vector(entry.Kminus_TRUEP_X,entry.Kminus_TRUEP_Y, entry.Kminus_TRUEP_Z)
        id1 = entry.Kplus_TRUEID
        id2 = entry.Kminus_TRUEID
        if not id1 or not id2:
            thingie.mass = entry.mdau2
            branch.Fill()
        else:
            par1 = PDG.ParticleData(id1)
            par2 = PDG.ParticleData(id2)
            thingie.mass = sqrt(IM2(p1,p2,par1.mass,par2.mass))
        branch.Fill()
        ws.append(re(weighter.subs(mass, entry.mhh_true).n()).n())
    sw = sum(ws)
    for i in range(len(ws)):
        wght.w = ws[i]*1./sw*t2.GetEntries()
        wph_branch.Fill()
    t2.Write("",TObject.kOverwrite)
    f2.Close()

def add_wphys(name1, name2, sym_weighter, dc_weighter):
    from sympy import re
    weighter = sym_weighter
    DC = dc_weighter
    f = TFile(name1)
    t = f.Get("DecayTree/DecayTree")
    f2 = TFile(name2, "recreate")
    t2 = t.CopyTree("(1>0)")
    thingie = phsp_true()
    wght = w_phys()
    ws = []
    branch_m = t2.Branch("mhh_true", AddressOf(thingie,'mass'), "mhh_true/D")
    branch_K = t2.Branch("cthetaK_true", AddressOf(thingie,'cthetaK'), "cthetaK_true/D")
    branch_L = t2.Branch("cthetaL_true", AddressOf(thingie,'cthetaL'), "cthetaL_true/D")
    branch_phi = t2.Branch("phi_true", AddressOf(thingie,'phi'), "phi_true/D")
    wph_branch = t2.Branch("wphys", AddressOf(wght,'w'), "wphys/D")
    for entry in t2:
        p1 = vector(entry.Kplus_TRUEP_X,entry.Kplus_TRUEP_Y, entry.Kplus_TRUEP_Z)
        p2 = vector(entry.Kminus_TRUEP_X,entry.Kminus_TRUEP_Y, entry.Kminus_TRUEP_Z)
        p3 = vector(entry.muplus_TRUEP_X,entry.muplus_TRUEP_Y, entry.muplus_TRUEP_Z)
        p4 = vector(entry.muminus_TRUEP_X,entry.muminus_TRUEP_Y, entry.muminus_TRUEP_Z)
       
        id1 = entry.Kplus_TRUEID
        id2 = entry.Kminus_TRUEID
        id3 = entry.muplus_TRUEID
        id4 = entry.muminus_TRUEID
        
        if not (id1 and id2 and id3 and id4):
            thingie.mass = entry.mdau2
            thingie.cthetaK = entry.helcosthetaK
            thingie.cthetaL = entry.helcosthetaL
            thingie.phi = entry.helphi
            #branch_m.Fill()
        else:
            par1 = PDG.ParticleData(id1)
            par2 = PDG.ParticleData(id2)
            par3 = PDG.ParticleData(id3)
            par4 = PDG.ParticleData(id4)
            thingie.mass = sqrt(IM2(p1,p2,par1.mass,par2.mass))
            E1 = sqrt(par1.mass**2 + vmod(p1)**2)
            E2 = sqrt(par2.mass**2 + vmod(p2)**2)
            E3 = sqrt(par3.mass**2 + vmod(p3)**2)
            E4 = sqrt(par4.mass**2 + vmod(p4)**2)
            l1 = TLorentzVector(p1[0],p1[1],p1[2],E1)
            l2 = TLorentzVector(p2[0],p2[1],p2[2],E2)
            l3 = TLorentzVector(p3[0],p3[1],p3[2],E3)
            l4 = TLorentzVector(p4[0],p4[1],p4[2],E4)
            angles = HelicityAngles(l1,l2,l3,l4)
            thingie.cthetaK = angles[0]
            thingie.cthetaL = angles[1]
            thingie.phi = angles[2]
            
        branch_m.Fill(), branch_K.Fill(), branch_L.Fill(), branch_phi.Fill()
        sym_w = re(weighter.subs([(mass, entry.mhh_true),(PhysBd.x,entry.cthetaK_true),(PhysBd.y,entry.cthetaL_true),(PhysBd.z,entry.phi_true)]).n()).n()
        dc_w = 1.0
        for key in DC.keys(): dc_w = dc_w * DC[key](getattr(entry,key))
        ws.append(sym_w*dc_w)
    sw = sum(ws)
    for i in range(len(ws)):
        wght.w = ws[i]*1./sw*t2.GetEntries()
        wph_branch.Fill()
    t2.Write("",TObject.kOverwrite)
    f2.Close()



#add_mass(tempf + "Lb_mct11.root","Lb11_for_tupleC.root")
#add_mass(tempf + "Lb_mct12.root","Lb12_for_tupleC.root")
#add_mass(tempf + "Bd_mct11.root","Bd11_for_tupleC.root")
#add_mass(tempf + "Bd_mct12.root","Bd12_for_tupleC.root")

# Reweight mhh
from Urania.MassAmplitudes import *
#from Urania.RooInterfaces import strCPP
L_res =  EvtGen.subs( [(m0,1519.5), (Gamma0,15.6),(Mdau1,PDG.Kplus.mass),(Mdau2,PDG.proton.mass)]) + 2*EvtGen.subs( [(m0,1580), (Gamma0,100),(Mdau1,PDG.Kplus.mass),(Mdau2,PDG.proton.mass)]) + 2*EvtGen.subs( [(m0,1665), (Gamma0,30),(Mdau1,PDG.Kplus.mass),(Mdau2,PDG.proton.mass)]) +  2*EvtGen.subs( [(m0,1690), (Gamma0,60),(Mdau1,PDG.Kplus.mass),(Mdau2,PDG.proton.mass)]) + 3*EvtGen.subs( [(m0,1800), (Gamma0,250),(Mdau1,PDG.Kplus.mass),(Mdau2,PDG.proton.mass)]) #+ .001
Lw = One #L_res*L_res.conjugate()

Kw = PhysBd.BdDat/PhysBd.BdMC


add_wphys(tempf + "Bd_mct11.root","Bd11_for_tupleC.root",Kw, Dianne.DCBd11)
add_wphys(tempf + "Bd_mct12.root","Bd12_for_tupleC.root",Kw, Dianne.DCBd12)

add_wphys(tempf + "Lb_mct11.root","Lb11_for_tupleC.root",Lw, Dianne.DCLb11)
add_wphys(tempf + "Lb_mct12.root","Lb12_for_tupleC.root",Lw, Dianne.DCLb12)

c = TCanvas()
c.Divide(2,2)
c.cd(1)
f = TFile("Bd11_for_tupleC.root")
t = f.Get("DecayTree")
t.Draw("wphys>>h1(100,0,3)")
c.cd(2)
f2 = TFile("Bd12_for_tupleC.root")
t2 = f2.Get("DecayTree")
t2.Draw("wphys>>h2(100,0,3)")
c.cd(3)
f3 = TFile("Lb11_for_tupleC.root")
t3 = f3.Get("DecayTree")
t3.Draw("wphys>>h3(100,0,3)")
c.cd(4)
f4 = TFile("Lb12_for_tupleC.root")
t4 = f4.Get("DecayTree")
t4.Draw("wphys>>h4(100,0,3)")
