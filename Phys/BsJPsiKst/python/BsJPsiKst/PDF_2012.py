from ROOT import *
from math import *
import os
if not "BSJPSIKSTROOT" in os.environ.keys(): os.environ["BSJPSIKSTROOT"] = "../../"
gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/AngJpsiKst_Swave.cxx++")
#gSystem.Load("AngJPsiKst_cxx")
f11 = TFile("~/vol5/OL_2011_GL.root")
t = f11.Get("T")
Mmax = t.GetMaximum("B0_MM")
f11.Close()

CPsi = RooRealVar("CPsi","CPsi",-1.,1.)
CTheta = RooRealVar("CTheta","CTheta",-1.,1.)
Phi = RooRealVar("B0_PhiTr","B0_PhiTr",-1.*pi,pi)
Mass = RooRealVar("B0_MM","B0_MM",5150, Mmax)

a1_cb = RooRealVar("a1_cb","a1_cb",2.8)#, 0.5,3.5)
a2_cb = RooRealVar("a2_cb","a2_cb",2.3)#, 0.5,3.5)
a2r_cb = RooRealVar("a2r_cb","a2_cb",-1.79)#, -6,-0.5)
ncb2 = RooRealVar("ncb2","ncb2",3.1)#)
delta_m = RooRealVar("delta_m", "delta_m", 5366.3-5279)
ncb = RooRealVar("ncb","ncb",1)
f05 = RooRealVar("f05","f05",0.5)#, 0., 1.)
fBs = RooRealVar("fBs","fBs", 1e-02,1e-03,.1)
s_a = 5
class AngularPDFMOD:
    def __init__(self, namephys = "Bd", namesample = "2011"):

        ## Parameters of interest
        self.namephys = namephys
        self.namesample = namesample
        
    def OwnPhys(self):
        namephys = self.namephys
        
        self.fL = RooRealVar("fL"+namephys,"fL"+namephys,0.507,0.2, .65)
        self.fpa = RooRealVar("fpa"+namephys,"fpa"+namephys,0.172,0.07, .35)
        self.As2 = RooRealVar("As2"+namephys,"As2"+namephys,0.05, 0,0.3)
        self.dpa = RooRealVar("dpa"+namephys,"dpa" + namephys, -pi,0)
        self.ds = RooRealVar("ds"+namephys,"ds"+namephys,0 , pi)

        
        self.A02 = RooFormulaVar("A02"+namephys,"A02"+namephys,"fL"+namephys+"*(1-As2"+namephys+")",RooArgList(self.fL,self.As2))
        self.Apa2 = RooFormulaVar("Apa2"+namephys,"Apa2"+namephys,"fpa"+namephys+"*(1-As2"+namephys+")",RooArgList(self.fpa,self.As2))#RooRealVar("As2","As2", 0.,.1)
        self.Ape2 = RooFormulaVar("Ape2"+namephys,"Ape2"+namephys,"(1-A02"+namephys+"-Apa2"+namephys+" - As2" + namephys + ")",RooArgList(self.As2,self.A02,self.Apa2))#RooRealVar("As2","As2", 0.,.1)

        self.As = RooFormulaVar("As"+namephys,"As"+namephys,"sqrt(As2"+namephys+")",RooArgList(self.As2))        
        self.A0 = RooFormulaVar("A0"+namephys,"A0"+namephys,"sqrt(A02"+namephys+")",RooArgList(self.A02))
        self.Apa = RooFormulaVar("Apa"+namephys,"Apa"+namephys,"sqrt(Apa2"+namephys+")",RooArgList(self.Apa2))
        self.Ape = RooFormulaVar("Ape"+namephys,"Ape"+namephys,"sqrt(Ape2"+namephys+")",RooArgList(self.Ape2))
        

    def CopyPhys(self, other):
        self.A0 = other.A0
        self.Apa = other.Apa
        self.Ape = other.Ape
        self.As = other.As
        self.dpa = other.dpa
        self.ds = other.ds
        return 1
        
        
    def OwnAcc(self):
        name = self.namephys + self.namesample
        self.c1_psi = RooRealVar("c1_psi" + name,"c1_psi" + name,-0.522,-0.522-s_a*0.014,-0.522+s_a*.014)
        self.c2_psi = RooRealVar("c2_psi" + name,"c2_psi" + name,-0.723,-0.723-s_a*0.022,-0.723+s_a*0.022)
        self.c3_psi = RooRealVar("c3_psi" + name,"c3_psi" + name,-0.190,-0.190-3*s_a,0.190+3*s_a)
        self.c4_psi = RooRealVar("c4_psi" + name,"c4_psi" + name,0.208,0.208-s_a*0.023,0.208+s_a*0.023) 
        self.y = RooRealVar("y" + name,"y" + name,0.)#,0.,s_a*1.6e-04)
        self.c5_psi = RooFormulaVar("c5_psi" + name,"c5_psi" + name,"y" + name + " + (-1.-c1_psi"+ name + "-c2_psi" + name + "-c3_psi" + name + "-c4_psi" + name + ")",RooArgList(self.y,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
       
        self.c1_theta = RooRealVar("c1_theta" + name,"c1_theta" + name,0.)
        self.c2_theta = RooRealVar("c2_theta" + name,"c2_theta" + name,-0.1783,-0.1783-s_a*0.0075,-0.1783+s_a*0.0075)

        self.c1_phi = RooRealVar("c1_phi" + name,"c1_phi" + name,0.090,0.0784-s_a*0.0039,0.0784+s_a*0.0039)
        self.c2_phi = RooRealVar("c2_phi" + name,"c2_phi" + name,2.019,2.019-s_a*0.029,2.109+s_a*0.029)
        self.c3_phi = RooRealVar("c3_phi" + name,"c3_phi" + name,.33,.33-s_a*0.048,.33+s_a*0.048)
        self.c4_phi = RooRealVar("c4_phi" + name,"c4_phi" + name,0)#.090,0.0784-s_a*0.0039,0.0784+s_a*0.0039)
        self.c5_phi = RooRealVar("c5_phi" + name,"c5_phi" + name,0)#2.019,2.019-s_a*0.029,2.109+s_a*0.029)
        self.c6_phi = RooRealVar("c6_phi" + name,"c6_phi" + name,0)#.33,.33-s_a*0.048,.33+s_a*0.048)
        
    def CopyAcc(self, other):
        self.c1_psi = other.c1_psi
        self.c2_psi = other.c2_psi
        self.c3_psi = other.c3_psi
        self.c4_psi = other.c4_psi
        self.c5_psi = other.c5_psi
        self.c1_theta = other.c1_theta
        self.c2_theta = other.c2_theta
        self.c1_phi = other.c1_phi
        self.c2_phi = other.c2_phi
        self.c3_phi = other.c3_phi
        self.c4_phi = other.c4_phi
        self.c5_phi = other.c5_phi
        self.c6_phi = other.c6_phi
        
    def modParamAsym(self, name, v0, v1,v2, cte = 0):
        getattr(self, name).setVal(v0)
        getattr(self, name).setMin(v0-v1)
        getattr(self, name).setMax(v0+v2)
        getattr(self, name).setConstant(cte)
        return 1
    def modParam(self, name, v0, v1, cte = 0):
        return self.modParamAsym(name, v0, v1, v1, cte)
    def make(self):
        name = self.namephys + self.namesample
        self.model = AngJpsiKst_Swave("angular " + name,"angular " + name,CPsi,CTheta,Phi,self.A0,self.Apa,self.Ape,self.As,self.dpa,self.ds,
                                   self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi,self.c5_psi,self.c1_theta,self.c2_theta,self.c1_phi,self.c2_phi,self.c3_phi,self.c4_phi,self.c5_phi,self.c6_phi)

# Background
class FullBackground:
    def __init__(self, name = "Bkg"):
        self.name  = name
        self.c1_phi_bkg = RooRealVar("c1_phi"+name,"c1_phi"+name,-4.38046e-01, -1,1)
        self.c2_phi_bkg = RooRealVar("c2_phi"+name,"c2_phi"+name,1.24342e-01,0.,.3)
        self.c3_phi_bkg = RooRealVar("c3_phi"+name,"c3_phi"+name,4.63368e-02,-0.1,.1)
        self.phibkg = RooGenericPdf("phibkg" + name,"phibkg" + name,"1+c1_phi"+name+ "*B0_PhiTr + c2_phi"+name+"*B0_PhiTr*B0_PhiTr + c3_phi"+name+"*B0_PhiTr*B0_PhiTr*B0_PhiTr",RooArgList(Phi,self.c1_phi_bkg,self.c2_phi_bkg,self.c3_phi_bkg))
        self.kbkg = RooRealVar("k"+name,"k"+name,-1e-03,-1,0)
        self.massbkg = RooExponential("Mass" + name, "Mass" + name, Mass, self.kbkg)

    def thetaFromAcc(self, other):
        name = self.name
        self.c1_psi = other.c1_psi
        self.c2_psi = other.c2_psi
        self.c3_psi = other.c3_psi
        self.c4_psi = other.c4_psi
        self.c5_psi = other.c5_psi
        self.c1_theta = other.c1_theta
        self.c2_theta = other.c2_theta
        self.psibkg = RooPolynomial("psi" + name ,"psi" + name,CPsi,RooArgList(self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi,self.c5_psi))
        self.thetabkg = RooPolynomial("theta" + name,"theta" + name,CTheta,RooArgList(self.c1_theta,self.c2_theta))

    def modParamAsym(self, name, v0, v1,v2):
        getattr(self, name).setVal(v0)
        getattr(self, name).setMin(v0-v1)
        getattr(self, name).setMax(v0+v2)
        return 1
    def modParam(self, name, v0, v1):
        return self.modParamAsym(name, v0, v1, v1)
    def make(self):
        name = self.name
        self.model = RooProdPdf("model"+name,"model"+name,RooArgList(self.psibkg,self.thetabkg,self.phibkg,self.massbkg))
        

    
class SignalMass:
    def __init__(self, samplename):

        self.mean1 = RooRealVar("mean1"+samplename,"mean1"+samplename,5279, 5276,5300)
        self.sigma1 = RooRealVar("sigma1"+samplename,"sigma1"+samplename, 6.,10.)
    
        self.delta_s = RooRealVar("delta_s"+samplename, "delta_s"+samplename, 2.,1.,15.)
    
        self.sigma2 = RooFormulaVar("sigma2"+samplename,"sigma2"+samplename, "sigma1"+samplename+" + delta_s"+samplename ,RooArgList(self.sigma1,self.delta_s) )
        self.mean2 = RooFormulaVar("mean2"+samplename,"mean2"+samplename, "mean1"+samplename+" + delta_m" ,RooArgList(self.mean1,delta_m) )
        self.sigb11  = RooCBShape("SigmodelB11"+samplename,"SigmodelB11"+samplename, Mass, self.mean1, self.sigma1, a1_cb, ncb)
    
        self.sigb12l  = RooCBShape("SigmodelB12l"+samplename,"SigmodelB12l"+samplename, Mass, self.mean1, self.sigma2, a2_cb, ncb)
        self.sigb12r  = RooCBShape("SigmodelB12r"+samplename,"SigmodelB12r"+samplename, Mass, self.mean1, self.sigma2, a2r_cb, ncb2)
        self.sigb12  = RooAddPdf("SigmodelB12"+samplename,"SigmodelB12"+samplename, self.sigb12l, self.sigb12r, f05)
        self.sigb21  = RooCBShape("SigmodelB21"+samplename,"SigmodelB21"+samplename, Mass, self.mean2, self.sigma1, a1_cb, ncb)
        self.sigb22l  = RooCBShape("SigmodelB22l"+samplename,"SigmodelB22l"+samplename, Mass, self.mean2, self.sigma2, a2_cb, ncb)
        self.sigb22r  = RooCBShape("SigmodelB22r"+samplename,"SigmodelB22r"+samplename, Mass, self.mean2, self.sigma2, a2r_cb, ncb2)
        self.sigb22  = RooAddPdf("SigmodelB22"+samplename,"SigmodelB22"+samplename, self.sigb22l, self.sigb22r, f05)
        
        self.fsmres = RooRealVar("f small res"+samplename,"f small res"+samplename,0.8, 0., 1.)
        self.sigBd  = RooAddPdf("SigmodelB1"+samplename,"SigmodelB1"+samplename, self.sigb11, self.sigb12, self.fsmres)
        self.sigBs  = RooAddPdf("SigmodelB2"+samplename,"SigmodelB2"+samplename, self.sigb21, self.sigb22, self.fsmres)

##     self.SigBs = RooProdPdf("Bs pdf"+samplename, "Bs pdf",RooArgList(AngBs.sigmodel,sigB2))
##     self.SigBd = RooProdPdf("Bd pdf", "Bd pdf",RooArgList(AngBd.sigmodel,sigB1))

##     self.nd = RooRealVar("nBd","nBd", 0.5*t.GetEntries(),t.GetEntries())
##     self.ns = RooFormulaVar("nBs","nBs", "fBs*nBd",RooArgList(fBs,nd))
##     self.nbkg = RooRealVar("n nbkg","n bkg", 0.,0.1*t.GetEntries())
##     self.just_mass_model = RooAddPdf("jmmodel","jmmodel",RooArgList(sigB2,sigB1,massbkg),RooArgList(ns,nd,nbkg))
    
        
