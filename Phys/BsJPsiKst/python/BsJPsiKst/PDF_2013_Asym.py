from ROOT import *
from math import *
from parameters import BlindingString, WeightsBd
import os
LAMBDA = 0
if not "BSJPSIKSTROOT" in os.environ.keys(): os.environ["BSJPSIKSTROOT"] = "../../"
gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/AccAngJpsiKpi_J1.cxx++")
gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/TristanJpsiKpi_J1.cxx++")
gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/RooPhiBkg.cxx++")
gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx+")

#gROOT.ProcessLine(".x ./AngJpsiKst_Swave_Asym.cxx++")

#gROOT.ProcessLine(".L $URANIAROOT/src/RooApollonios.cxx++")

mvar = "B0_MM"# "B_s0_LOKI_MASS_JpsiConstr"

#gROOT.ProcessLine(".x AngJpsiKst_Swave_Asym.cxx++")
#gSystem.Load("AngJPsiKst_cxx")

#Kcharge = RooRealVar("Kcharge","Kcharge",-1.)
SFIT = 2
#cKname, cLname, phName = "cK", "cL", "ph" ## kozyulin MCT tuple
cKname, cLname, phName = "helcosthetaK", "helcosthetaL", "B0_Phi" ## other

CPsi = RooRealVar(cKname,cKname,-1.,1.)
CTheta = RooRealVar(cLname,cLname,-1.,1.)
Phi = RooRealVar(phName,phName,-1.*pi,pi)

Mass = RooRealVar(mvar,mvar,5150, 5650.)

sWeights_Bd =  RooRealVar("sWeights_" + LAMBDA*"Lb" + "Bd","sWeights_" + LAMBDA*"Lb" +"Bd",-3.,3.)
sWeights_Bs =  RooRealVar("sWeights_" + LAMBDA*"Lb" + "Bs","sWeights_" + LAMBDA*"Lb" + "Bs",-3.,3.)

cor_sWeights_Bd =  RooRealVar("cor_sWeights_" + LAMBDA*"Lb" + "Bd","cor_sWeights_" + LAMBDA*"Lb" + "Bd",-3.,3.)
cor_sWeights_Bs =  RooRealVar("cor_sWeights_" + LAMBDA*"Lb" + "Bs","cor_sWeights_" + LAMBDA*"Lb" + "Bs",-3.,3.)


ipa_beta = RooRealVar("ipatia_beta" ,"ipatia_beta", 0.)
ipa_zeta = RooRealVar("ipatia_zeta" ,"ipatia_zeta", 0.)

delta_m = RooRealVar("delta_m", "delta_m", 5366.3-5279)
ncb = RooRealVar("ncb","ncb",1)
f05 = RooRealVar("f05","f05",0.5)#, 0., 1.)
fBs = RooRealVar("fBs","fBs", 1e-02,1e-03,.1)
Aprod_s = RooRealVar("A_prod_s","A_prod_s", -0.00132)#wk 
Aprod_d = RooRealVar("A_prod_d","A_prod_d", 0.00030)#wk 

A_D = RooRealVar("A_D","A_D", -0.01185)# ok  

NormWeights = WeightsBd
BLIND = 1

if not BLIND:
    print ""
    print ""
    print ""
    print "0o0   0o0    0o0   0o0   0o0  0o0  0o0  0o0"
    print " ALARM!, ALARM!, YOU ARE UNBLINDING!!!"
    print "0o0   0o0    0o0   0o0   0o0  0o0  0o0  0o0"
    print ""
    print ""
    print ""
s_a = 5.0
class AngularPDFMOD:
    def __init__(self, namephys = "Bd", namesample = "2011", Kcharge = 0. , acc_type = 1):

        ## Parameters of interest
        self.namephys = namephys
        self.namesample = namesample
        self.Kcharge =RooRealVar("Kcharge" + self.namephys + self.namesample,"Kcharge"+ self.namephys + self.namesample,Kcharge)
        self.acc_type = acc_type
    def OwnPhys(self, equalAsym = 0):
        namephys = self.namephys
        
        self.fL = RooRealVar("fL"+namephys,"fL"+namephys,0.507,0.2, .65)
        self.fpa = RooRealVar("fpa"+namephys,"fpa"+namephys,0.172,0.07, .35)
        self.As2 = RooRealVar("As2"+namephys,"As2"+namephys,0.05, 0,0.8)
        self.dpa = RooRealVar("dpa"+namephys,"dpa" + namephys, 0., -2*pi, 2*pi)
        self.CSP = RooRealVar("CSP"+namephys,"CSP" + namephys, 0, 1)
        
        if self.Kcharge.getVal() >= 0:
            self.dpe = RooRealVar("dpe"+namephys,"dpe" + namephys, 0, -2*pi, 2*pi)
        else :
            self.dpe_ = RooRealVar("_dpe"+namephys,"_dpe" + namephys, 0,-2*pi,2*pi)
            self.dpe = RooFormulaVar("dpe"+namephys,"dpe" + namephys,"_dpe"+namephys + " + "+str(pi),RooArgList(self.dpe_))
        self.ds = RooRealVar("ds"+namephys,"ds"+namephys,0 , -2*pi,2*pi)
        self.ACPL_ = RooRealVar("ACPL"+namephys,"ACPL"+namephys,0.,-0.5, 0.5)
        if equalAsym:
            self.ACPpa_ = RooFormulaVar("ACPpa"+namephys,"ACPpa"+namephys, self.ACPL_.GetName(), RooArgList(self.ACPL_))
            self.ACPpe_ = RooFormulaVar("ACPpe"+namephys,"ACPpe"+namephys, self.ACPL_.GetName(), RooArgList(self.ACPL_))
            
        else:
            self.ACPpa_ = RooRealVar("ACPpa"+namephys,"ACPpa"+namephys,0.,-0.5, 0.5)
            self.ACPpe_ = RooRealVar("ACPpe"+namephys,"ACPpe"+namephys,0.,-0.5, 0.5)
           

        
        if BLIND:
            self.ACPL = RooUnblindPrecision("ACPL"+namephys + "_UNB", "ACPL"+namephys + "_UNB", BlindingString + "L", 0,0.2, self.ACPL_)
            if not equalAsym:
                self.ACPpa = RooUnblindPrecision("ACPpa"+namephys + "_UNB", "ACPpa"+namephys + "_UNB", BlindingString + "pa", 0,0.2,self.ACPpa_)
                self.ACPpe= RooUnblindPrecision("ACPpe"+namephys + "_UNB", "ACPpe"+namephys + "_UNB", BlindingString +"pe",  0,0.2, self.ACPpe_)
        else: self.ACPL = self.ACPL_
        if equalAsym or not BLIND:
            self.ACPpa = self.ACPpa_
            self.ACPpe = self.ACPpe_
        
        self.psACP = RooFormulaVar("psACP" + namephys, "psACP" + namephys, " 1/( 1+ fL" + namephys + "*"+self.ACPL.GetName() + " + fpa"+namephys + "*"+self.ACPpa.GetName() + " + (1-fL"+namephys +"-fpa"+namephys+")*"+self.ACPpe.GetName() + ")", RooArgList(self.fL, self.fpa, self.ACPL, self.ACPpa, self.ACPpe))
            
        self.CreateAmplitudes()

  

    def CopyStrongPhases(self, other):
        self.dpa = other.dpa
        
        if self.Kcharge.getVal() != other.Kcharge.getVal():
            namephys = self.namephys
            self.dpe = RooFormulaVar("_dpe"+namephys,"_dpe" + namephys,"dpe"+namephys + " + "+str(pi),RooArgList(other.dpe))
        else: self.dpe = other.dpe
        self.ds = other.ds
        
    def CopyFreeParams(self, other):
        self.fL = other.fL
        self.fpa = other.fpa
        self.As2 = other.As2
        self.ACPL = other.ACPL
        self.ACPpe = other.ACPpe
        self.ACPpa = other.ACPpa
        self.psACP = other.psACP
        self.ACPL_ = other.ACPL_
        self.ACPpe_ = other.ACPpe_
        self.ACPpa_ = other.ACPpa_
        self.CSP = other.CSP
        self.CopyStrongPhases(other)
        self.CreateAmplitudes()

    def CopyPhys(self, other):
        self.fL_ = other.fL_
        self.fpa_ = other.fpa_
        #self.Ape = other.Ape
        self.As2 = other.As2
        self.CSP = other.CSP
        self.CopyStrongPhases(other)
        
        return 1

    def CreateAmplitudes(self):
        namephys = self.namephys
        name = self.namephys + self.namesample
        
        if self.Kcharge.getVal() == 0:
            self.fpa_ = RooFormulaVar("fpa"+name,"fpa" + name, "fpa"+namephys,  RooArgList(self.fpa))
            self.fL_ = RooFormulaVar("fL"+name,"fL" + name, " fL"+namephys, RooArgList(self.fL))
            
        
        if self.Kcharge.getVal()> 0:
            self.fpa_ = RooFormulaVar("fpa"+name,"fpa" + name, " ( 1 + " + self.ACPpa.GetName()+")*fpa"+namephys + "*psACP"+namephys, RooArgList( self.ACPpa, self.fpa, self.psACP))
            self.fL_ = RooFormulaVar("fL"+name,"fL" + name, " ( 1 + " + self.ACPL.GetName()+")*fL"+namephys + "*psACP"+namephys, RooArgList( self.ACPL, self.fL, self.psACP))
            
        if self.Kcharge.getVal()< 0:
            self.fpa_ = RooFormulaVar("fpa"+name,"fpa" + name, " ( 1 - " + self.ACPpa.GetName() + ")*fpa"+namephys + "*psACP"+namephys + "*1./( -1 + 2*psACP"+namephys + ")", RooArgList( self.ACPpa, self.fpa, self.psACP))
            self.fL_ = RooFormulaVar("fL"+name,"fL" + name, " ( 1 - " +self.ACPL.GetName() + ")*fL"+namephys + "*psACP"+namephys + "*1./( -1 + 2*psACP"+namephys + ")", RooArgList( self.ACPL, self.fL, self.psACP))
        
            
    def OwnAcc(self):
        name = self.namephys + self.namesample
        if self.acc_type == 1:
            self.c1_psi = RooRealVar("c1_psi" + name,"c1_psi" + name,-0.522,-0.522-s_a*0.014,-0.522+s_a*.014)
            self.c2_psi = RooRealVar("c2_psi" + name,"c2_psi" + name,-0.723,-0.723-s_a*0.022,-0.723+s_a*0.022)
            self.c3_psi = RooRealVar("c3_psi" + name,"c3_psi" + name,-0.190,-0.190-3*s_a,0.190+3*s_a)
            self.c4_psi = RooRealVar("c4_psi" + name,"c4_psi" + name,0.208,0.208-s_a*0.023,0.208+s_a*0.023) 
            self.y_acc = RooRealVar("y" + name,"y" + name,0.)#,0.,s_a*1.6e-04)
            self.c5_psi = RooFormulaVar("c5_psi" + name,"c5_psi" + name,"y" + name + " + (-1.-c1_psi"+ name + "-c2_psi" + name + "-c3_psi" + name + "-c4_psi" + name + ")",RooArgList(self.y_acc,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
            self.c2_theta = RooRealVar("c2_theta" + name,"c2_theta" + name,0,-0.5,0.5)
        else:
            if self.Kcharge.getVal() > 0: wdict = NormWeights["2012p_896_931"]
            else: wdict = NormWeights["2012n_896_931"] 
            
            self.w_pe2 = RooRealVar("w_pepe" + name, "w_pepe", wdict["pe2"])
            self.w_S2 = RooRealVar("w_SS" + name, "w_SS", wdict["SS"])
            self.w_0pe = RooRealVar("w_0pe" + name, "w_0pe",wdict["0pe"])
            self.w_Spe = RooRealVar("w_Spe" + name, "w_Spe", wdict["Spe"])
            self.w_pape = RooRealVar("w_pape" + name, "w_pape",wdict["pape"])
            self.w_pa2 = RooRealVar("w_papa" + name, "w_papa", wdict["pa2"])
            self.w_Spa  = RooRealVar("w_Spa" + name, "w_Spa", wdict["Spa"])
            self.w_0pa  = RooRealVar("w_0pa" + name, "w_0pa", wdict["0pa"])
            self.w_S0  = RooRealVar("w_S0" + name, "w_S0", wdict["S0"])
            self.w_00 = RooRealVar("w_00" + name, "w_00", wdict["00"])
            self.Tristan_weights = (self.w_pe2, self.w_S2, self.w_0pe, self.w_Spe, self.w_pape, self.w_pa2, self.w_Spa, self.w_0pa, self.w_S0, self.w_00)
    def GetNormWeightString(self):
        out = ""
        for thing in self.Tristan_weights: out+= ","+thing.GetName()
        return out

    def FlatAcc(self):
        if self.acc_type == 1:
            name = self.namephys + self.namesample
            self.c1_psi = RooRealVar("c1_psi" + name,"c1_psi" + name,0)#-0.522,-0.522-s_a*0.014,-0.522+s_a*.014)
            self.c2_psi = RooRealVar("c2_psi" + name,"c2_psi" + name,0)#-0.723,-0.723-s_a*0.022,-0.723+s_a*0.022)
            self.c3_psi = RooRealVar("c3_psi" + name,"c3_psi" + name,0)#-0.190,-0.190-3*s_a,0.190+3*s_a)
            self.c4_psi = RooRealVar("c4_psi" + name,"c4_psi" + name,0)#0.208,0.208-s_a*0.023,0.208+s_a*0.023) 
            self.y_acc = RooRealVar("y" + name,"y" + name,1.)#,0.,s_a*1.6e-04)
        
            self.c2_theta = RooRealVar("c2_theta" + name,"c2_theta" + name,0)#-0.1783,-0.1783-s_a*0.0075,-0.1783+s_a*0.0075)
        else:
            for w in self.Tristan_weights:
                wname = w.GetName()
                if "00" in wname or "SS" in wname or "papa" in wname or "pepe" in wname: w.setVal(1.)#16.*pi/9)
                else: w.setVal(0.) 
                w.setConstant(kTRUE)
                print w.GetName(), w.getVal()
        
    def CopyAcc(self, other):
        if self.acc_type == 1:
            self.c1_psi = other.c1_psi
            self.c2_psi = other.c2_psi
            self.c3_psi = other.c3_psi
            self.c4_psi = other.c4_psi
            self.c5_psi = other.c5_psi
            self.y_acc = other.y_acc
            #self.c1_theta = other.c1_theta
            self.c2_theta = other.c2_theta
        else: self.Tristan_weights = other.Tristan_weights
    def modParamAsym(self, name, v0, v1,v2, cte):
        _min = v0 - v1
        _max = v0 + v2
        if _max <= getattr(self, name).getMin():
            #print "A"
            getattr(self, name).setMin(v0-v1)
            getattr(self, name).setMax(v0+v2)
            getattr(self, name).setVal(v0)
        else:
            #print "B"
            getattr(self, name).setMax(v0+v2)
            getattr(self, name).setMin(v0-v1)
            getattr(self, name).setVal(v0)
        getattr(self, name).setConstant(cte)
        return 1
    
    def modParam(self, name, v0, v1, cte = 0):
        return self.modParamAsym(name, v0, v1, v1, cte)
    
    def make(self):
        name = self.namephys + self.namesample
    
        if self.acc_type == 1: self.model = AccAngJpsiKpi_J1("angular " + name,"angular " + name, CPsi, CTheta, Phi, self.As2, self.fL_, self.fpa_, \
                                          self.dpa, self.dpe, self.ds, self.CSP, self.c1_psi, self.c2_psi, self.c3_psi, self.c4_psi, self.y_acc, self.c2_theta)#, self.c1_phi, self.c2_phi, self.c3_phi, self.c4_phi, self.c5_phi, self.c6_phi)
        else: self.model = TristanJpsiKpi_J1("angular " + name,"angular " + name, CPsi, CTheta, Phi, self.As2, self.fL_, self.fpa_, \
                                          self.dpa, self.dpe, self.ds, self.CSP, *self.Tristan_weights)
# Background
class FullBackground:
    def __init__(self, name = "Bkg"):
        self.name  = name
        
        self.c1_phi_bkg = RooRealVar("c1_phi"+name,"c1_phi"+name,-4.38046e-01, -1,1)
        self.c2_phi_bkg = RooRealVar("c2_phi"+name,"c2_phi"+name,1.24342e-01,0.,.3)
        self.c3_phi_bkg = RooRealVar("c3_phi"+name,"c3_phi"+name,4.63368e-02,-0.1,.1)
        self.phibkg = RooPhiBkg("phibkg" + name,"phibkg" + name,Phi,self.c1_phi_bkg,self.c2_phi_bkg,self.c3_phi_bkg)
        
        self.kbkg = RooRealVar("k"+name,"k"+name,-1e-03,-1e-02,0)
        self.massbkg = RooExponential("Mass" + name, "Mass" + name, Mass, self.kbkg)

    def OwnTheta(self):
        name = self.name
        self.c1_psi = RooRealVar("c1_psi" + name,"c1_psi" + name,-5.20101e-01)#-0.522,-0.522-s_a*0.014,-0.522+s_a*.014)
        self.c2_psi = RooRealVar("c2_psi" + name,"c2_psi" + name,-7.33299e-01)#,-0.723-s_a*0.022,-0.723+s_a*0.022)
        self.c3_psi = RooRealVar("c3_psi" + name,"c3_psi" + name,-2.90606e-01)#-0.190,-0.190-3*s_a,0.190+3*s_a)
        self.c4_psi = RooRealVar("c4_psi" + name,"c4_psi" + name,2.69475e-01 )#0.208,0.208-s_a*0.023,0.208+s_a*0.023) 
        self.y_acc = RooRealVar("y" + name,"y" + name,0.)#,0.,s_a*1.6e-04)
        self.c5_psi = RooFormulaVar("c5_psi" + name,"c5_psi" + name,"y" + name + " + (-1.-c1_psi"+ name + "-c2_psi" + name + "-c3_psi" + name + "-c4_psi" + name + ")",RooArgList(self.y_acc,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
        self.c1_theta = RooRealVar("c1_theta" + name,"c1_theta" + name,0)
        self.c2_theta = RooRealVar("c2_theta" + name,"c2_theta" + name,2.76201e-01)
        self.psibkg = RooPolynomial("psi" + name ,"psi" + name,CPsi,RooArgList(self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi,self.c5_psi))
        self.thetabkg = RooPolynomial("theta" + name,"theta" + name,CTheta,RooArgList(self.c1_theta,self.c2_theta))


    def thetaFromAcc(self, other):
        name = self.name
        self.c1_psi = other.c1_psi
        self.c2_psi = other.c2_psi
        self.c3_psi = other.c3_psi
        self.c4_psi = other.c4_psi
        self.c5_psi = other.c5_psi#RooFormulaVar("c5_psi" + name,"c5_psi" + name,"y" + name + " + (-1.-c1_psi"+ name + "-c2_psi" + name + "-c3_psi" + name + "-c4_psi" + name + ")",RooArgList(other.y_acc,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
        self.c1_theta = RooRealVar("c1_theta" + name,"c1_theta" + name,0)
        self.c2_theta = other.c2_theta
        self.psibkg = RooPolynomial("psi" + name ,"psi" + name,CPsi,RooArgList(self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi,self.c5_psi))
        self.thetabkg = RooPolynomial("theta" + name,"theta" + name,CTheta,RooArgList(self.c1_theta,self.c2_theta))

    def modParamAsym(self, name, v0, v1,v2):
        _min = v0 - v1
        _max = v0 + v2
        if _max <= getattr(self, name).getMin():
            #print "A"
            getattr(self, name).setMin(v0-v1)
            getattr(self, name).setMax(v0+v2)
            getattr(self, name).setVal(v0)
        else:
            #print "B"
            getattr(self, name).setMax(v0+v2)
            getattr(self, name).setMin(v0-v1)
            getattr(self, name).setVal(v0)
        return 1
    def modParam(self, name, v0, v1):
        return self.modParamAsym(name, v0, v1, v1)
    def make(self):
        name = self.name
        self.model = RooProdPdf("model"+name,"model"+name,RooArgList(self.psibkg,self.thetabkg,self.phibkg,self.massbkg))
       
class SignalMass:
    def __init__(self, samplename):

        self.mean1 = RooRealVar("mean1"+samplename,"mean1"+samplename,5279, 5276,5300)
        self.sigma1 = RooRealVar("sigma1"+samplename,"sigma1"+samplename, 6.,15.)
       
        self.mean2 = RooFormulaVar("mean2"+samplename,"mean2"+samplename, "mean1"+samplename+" + delta_m" ,RooArgList(self.mean1,delta_m) )
        self.ipa_lambda = RooRealVar("ipatia_lambda" , "ipatia_lambda" + samplename, -4,-1.1)
        self.a1_cb = RooRealVar("a1_cb"+samplename,"a1_cb"+samplename,2.8)#, 0.5,3.5)
        self.a2_cb = RooRealVar("a2_cb"+samplename,"a2_cb"+samplename,2.3)#, 0.5,3.5)
        self.ncb1 = RooRealVar("ncb1"+samplename,"ncb1"+samplename,3.1)#)
        self.ncb2 = RooRealVar("ncb2"+samplename,"ncb2"+samplename,3.1)#)
        
        self.sigBd  = RooIpatia2("SigmodelBd"+samplename,"SigmodelBd"+samplename, Mass,self.ipa_lambda,ipa_zeta,ipa_beta,self.sigma1,self.mean1,self.a1_cb,self.ncb1,self.a2_cb,self.ncb2)
        self.sigBs  = RooIpatia2("SigmodelBs"+samplename,"SigmodelBs"+samplename, Mass,self.ipa_lambda,ipa_zeta,ipa_beta,self.sigma1,self.mean2,self.a1_cb,self.ncb1,self.a2_cb,self.ncb2)
        

# class SignalMass:
#     def __init__(self, samplename):

#         self.meanBd = RooRealVar("meanBd"+samplename,"meanBd"+samplename,5279, 5276,5300)
#         self.sigma1 = RooRealVar("sigma1"+samplename,"sigma1"+samplename, 5.,20.)
#         self.d_sigma = RooRealVar("d_sigma"+samplename,"d_sigma"+samplename, 24.6)
#         self.sigma2 = RooFormulaVar("sigma2"+samplename,"sigma2"+samplename, "sigma1"+samplename + " + d_sigma"+samplename, RooArgList(self.sigma1,self.d_sigma))
    
#         self.coef = RooRealVar("coef"+samplename, "coef"+samplename, 2.,1.,15.)
#         self.meanBs = RooFormulaVar("meanBs"+samplename,"meanBs"+samplename, "meanBd"+samplename+" + delta_m" ,RooArgList(self.meanBd,delta_m) )
#         self.f1 = RooRealVar("f_Apo_1"+samplename,"f_Apo_1"+samplename, 0.93)
#         self.trans = RooRealVar("trans" + samplename,"trans" + samplename,2.2)
#         self.sigBd1  = RooApollonios("SigmodelBd1_"+samplename,"SigmodelBd1_"+samplename, Mass, self.meanBd, self.sigma1, self.coef, self.trans, ncb)
#         self.sigBs1  = RooApollonios("SigmodelBs1_"+samplename,"SigmodelBs1_"+samplename, Mass, self.meanBs, self.sigma1, self.coef, self.trans, ncb)
#         self.sigBd2  = RooApollonios("SigmodelBd2_"+samplename,"SigmodelBd2_"+samplename, Mass, self.meanBd, self.sigma2, self.coef, self.trans, ncb)
#         self.sigBs2  = RooApollonios("SigmodelBs2_"+samplename,"SigmodelBs2_"+samplename, Mass, self.meanBs, self.sigma2, self.coef, self.trans, ncb)
#         self.sigBd = RooAddPdf("SigmodelBd_"+samplename,"SigmodelBd_"+samplename, self.sigBd1, self.sigBd2, self.f1)
#         self.sigBs = RooAddPdf("SigmodelBs_"+samplename,"SigmodelBs_"+samplename, self.sigBs1, self.sigBs2, self.f1)
        


def InitSignalPdfs(namephys, namesample, acc_type = 1 ):
    sp =  AngularPDFMOD( namephys, namesample + "_pos_", 1, acc_type = acc_type)
    sn =  AngularPDFMOD( namephys, namesample + "_neg_", -1, acc_type = acc_type)
    return sp, sn
    
    
