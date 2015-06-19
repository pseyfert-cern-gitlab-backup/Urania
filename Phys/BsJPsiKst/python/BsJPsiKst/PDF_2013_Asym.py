from ROOT import *
from math import *
import os

if not "BSJPSIKSTROOT" in os.environ.keys(): os.environ["BSJPSIKSTROOT"] = "../../"
gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/AccAngJpsiKpi_J1.cxx++")
gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/RooPhiBkg.cxx++")

#gROOT.ProcessLine(".x ./AngJpsiKst_Swave_Asym.cxx++")

#gROOT.ProcessLine(".L $URANIAROOT/src/RooApollonios.cxx++")

mvar = "B0_MM"# "B_s0_LOKI_MASS_JpsiConstr"

#gROOT.ProcessLine(".x AngJpsiKst_Swave_Asym.cxx++")
#gSystem.Load("AngJPsiKst_cxx")

#Kcharge = RooRealVar("Kcharge","Kcharge",-1.)
SFIT = 2
CPsi = RooRealVar("helcosthetaK","helcosthetaK",-1.,1.)
CTheta = RooRealVar("helcosthetaL","helcosthetaL",-1.,1.)
Phi = RooRealVar("B0_Phi","B0_Phi",-1.*pi,pi)

Mass = RooRealVar(mvar,mvar,5150, 5450.)

sWeights_Bd =  RooRealVar("sWeights_Bd","sWeights_Bd",-3.,3.)
sWeights_Bs =  RooRealVar("sWeights_Bs","sWeights_Bs",-3.,3.)


cor_sWeights_Bd =  RooRealVar("cor_sWeights_Bd","cor_sWeights_Bd",-3.,3.)
cor_sWeights_Bs =  RooRealVar("cor_sWeights_Bs","cor_sWeights_Bs",-3.,3.)

a1_cb = RooRealVar("a1_cb","a1_cb",2.8)#, 0.5,3.5)
a2_cb = RooRealVar("a2_cb","a2_cb",2.3)#, 0.5,3.5)
a2r_cb = RooRealVar("a2r_cb","a2_cb",-1.79)#, -6,-0.5)
ncb2 = RooRealVar("ncb2","ncb2",3.1)#)
delta_m = RooRealVar("delta_m", "delta_m", 5366.3-5279)
ncb = RooRealVar("ncb","ncb",1)
f05 = RooRealVar("f05","f05",0.5)#, 0., 1.)
fBs = RooRealVar("fBs","fBs", 1e-02,1e-03,.1)
Aprod_s = RooRealVar("A_prod_s","A_prod_s", -0.00132)#wk 
Aprod_d = RooRealVar("A_prod_d","A_prod_d", 0.00030)#wk 

A_D = RooRealVar("A_D","A_D", -0.01185)# ok  


s_a = 5
class AngularPDFMOD:
    def __init__(self, namephys = "Bd", namesample = "2011", Kcharge = 0. ):

        ## Parameters of interest
        self.namephys = namephys
        self.namesample = namesample
        self.Kcharge =RooRealVar("Kcharge" + self.namephys + self.namesample,"Kcharge"+ self.namephys + self.namesample,Kcharge)
        
    def OwnPhys(self, equalAsym = 0):
        namephys = self.namephys
        
        self.fL = RooRealVar("fL"+namephys,"fL"+namephys,0.507,0.2, .65)
        self.fpa = RooRealVar("fpa"+namephys,"fpa"+namephys,0.172,0.07, .35)
        self.As2 = RooRealVar("As2"+namephys,"As2"+namephys,0.05, 0,0.3)
        self.dpa = RooRealVar("dpa"+namephys,"dpa" + namephys, -pi,0)
        
        if self.Kcharge.getVal() >= 0:
            self.dpe = RooRealVar("dpe"+namephys,"dpe" + namephys, -pi,0)
        else :
            self.dpe_ = RooRealVar("_dpe"+namephys,"_dpe" + namephys, -pi,0)
            self.dpe = RooFormulaVar("dpe"+namephys,"dpe" + namephys,"_dpe"+namephys + " + "+str(pi),RooArgList(self.dpe_))
        self.ds = RooRealVar("ds"+namephys,"ds"+namephys,0 , pi)
        self.ACPL = RooRealVar("ACPL"+namephys,"ACPL"+namephys,0.,-0.5, 0.5)
        if equalAsym:
            self.ACPpa = RooFormulaVar("ACPpa"+namephys,"ACPpa"+namephys, self.ACPL.GetName(), RooArgList(self.ACPL))
            self.ACPpe = RooFormulaVar("ACPpe"+namephys,"ACPpe"+namephys, self.ACPL.GetName(), RooArgList(self.ACPL))
        else:
            self.ACPpa = RooRealVar("ACPpa"+namephys,"ACPpa"+namephys,0.,-0.5, 0.5)
            self.ACPpe = RooRealVar("ACPpe"+namephys,"ACPpe"+namephys,0.,-0.5, 0.5)
        self.psACP = RooFormulaVar("psACP" + namephys, "psACP" + namephys, " 1/( 1+ fL" + namephys + "*ACPL"+namephys + " + fpa"+namephys + "*ACPpa"+namephys + " + (1-fL"+namephys +"-fpa"+namephys+")*ACPpe"+namephys + ")",
                                   RooArgList(self.fL, self.fpa, self.ACPL, self.ACPpa, self.ACPpe))
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
        self.ACPL = other.ACPL
        self.ACPpe = other.ACPpe
        self.ACPpa = other.ACPpa
        self.psACP = other.psACP
        self.CopyStrongPhases(other)
        self.CreateAmplitudes()

    def CopyPhys(self, other):
        self.fL_ = other.fL_
        self.fpa_ = other.fpa_
        #self.Ape = other.Ape
        self.As2 = other.As2
        self.CopyStrongPhases(other)
        
        return 1

    def CreateAmplitudes(self):
        namephys = self.namephys
        name = self.namephys + self.namesample
        
        if self.Kcharge.getVal() == 0:
            self.fpa_ = RooFormulaVar("fpa"+name,"fpa" + name, "fpa"+namephys,  RooArgList(self.fpa))
            self.fL_ = RooFormulaVar("fL"+name,"fL" + name, " fL"+namephys, RooArgList(self.fL))
            
        
        if self.Kcharge.getVal()> 0:
            self.fpa_ = RooFormulaVar("fpa"+name,"fpa" + name, " ( 1 + ACPpa" + namephys+")*fpa"+namephys + "*psACP"+namephys, RooArgList( self.ACPpa, self.fpa, self.psACP))
            self.fL_ = RooFormulaVar("fL"+name,"fL" + name, " ( 1 + ACPL" + namephys+")*fL"+namephys + "*psACP"+namephys, RooArgList( self.ACPL, self.fL, self.psACP))
            
        if self.Kcharge.getVal()< 0:
            self.fpa_ = RooFormulaVar("fpa"+name,"fpa" + name, " ( 1 - ACPpa" + namephys+")*fpa"+namephys + "*psACP"+namephys + "*1./( -1 + 2*psACP"+namephys + ")", RooArgList( self.ACPpa, self.fpa, self.psACP))
            self.fL_ = RooFormulaVar("fL"+name,"fL" + name, " ( 1 - ACPL" + namephys+")*fL"+namephys + "*psACP"+namephys + "*1./( -1 + 2*psACP"+namephys + ")", RooArgList( self.ACPL, self.fL, self.psACP))
        
        #wk if not "As2" in dir(self):
            #print "Warning, nothing said about As2 for sample ", name , ". Creating it now as a free parameter"
        if namephys== "Bd":
           self.As2 = RooRealVar("As2"+namephys,"As2"+namephys,1.60099e-02)#0.05, 0,0.3)#wk changed name ->namephys
        else:
           self.As2 = RooRealVar("As2"+namephys,"As2"+namephys,0.05, 0,0.3)# check
           #self.As2 = RooRealVar("As2"+namephys,"As2"+namephys,0.053)
        #As2.setConstant(1.60099e-02)
        #self.A02 = RooFormulaVar("A02"+name,"A02"+name,"fL"+name+"*(1-"+self.As2.GetName()+")",RooArgList(self.fL_,self.As2))
        #self.Apa2 = RooFormulaVar("Apa2"+name,"Apa2"+name,"fpa"+name+"*(1-"+self.As2.GetName()+")",RooArgList(self.fpa_,self.As2))#RooRealVar("As2","As2", 0.,.1)
        #self.Ape2 = RooFormulaVar("Ape2"+name,"Ape2"+name,"(1-A02"+name+"-Apa2"+name+" - "+self.As2.GetName()+ ")",RooArgList(self.As2,self.A02,self.Apa2))#RooRealVar("As2","As2", 0.,.1)
        #self.As = RooFormulaVar("As"+name,"As"+name,"sqrt("+self.As2.GetName()+")",RooArgList(self.As2))       
         
        #self.A0 = RooFormulaVar("A0"+name,"A0"+name,"sqrt(A02"+name+")",RooArgList(self.A02))
        #self.Apa = RooFormulaVar("Apa"+name,"Apa"+name,"sqrt(Apa2"+name+")",RooArgList(self.Apa2))
        #self.Ape = RooFormulaVar("Ape"+name,"Ape"+name,"sqrt(Ape2"+name+")",RooArgList(self.Ape2))
            
    def OwnAcc(self):
        name = self.namephys + self.namesample
        self.c1_psi = RooRealVar("c1_psi" + name,"c1_psi" + name,-0.522,-0.522-s_a*0.014,-0.522+s_a*.014)
        self.c2_psi = RooRealVar("c2_psi" + name,"c2_psi" + name,-0.723,-0.723-s_a*0.022,-0.723+s_a*0.022)
        self.c3_psi = RooRealVar("c3_psi" + name,"c3_psi" + name,-0.190,-0.190-3*s_a,0.190+3*s_a)
        self.c4_psi = RooRealVar("c4_psi" + name,"c4_psi" + name,0.208,0.208-s_a*0.023,0.208+s_a*0.023) 
        self.y_acc = RooRealVar("y" + name,"y" + name,0.)#,0.,s_a*1.6e-04)
        self.c5_psi = RooFormulaVar("c5_psi" + name,"c5_psi" + name,"y" + name + " + (-1.-c1_psi"+ name + "-c2_psi" + name + "-c3_psi" + name + "-c4_psi" + name + ")",RooArgList(self.y_acc,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
       
        #self.c1_theta = RooRealVar("c1_theta" + name,"c1_theta" + name,0.)
        self.c2_theta = RooRealVar("c2_theta" + name,"c2_theta" + name,0,-0.5,0.5)

        #self.c1_phi = RooRealVar("c1_phi" + name,"c1_phi" + name,0.090,0.0784-s_a*0.0039,0.0784+s_a*0.0039)
        #self.c2_phi = RooRealVar("c2_phi" + name,"c2_phi" + name,2.019,2.019-s_a*0.029,2.109+s_a*0.029)
        #self.c3_phi = RooRealVar("c3_phi" + name,"c3_phi" + name,.33,.33-s_a*0.048,.33+s_a*0.048)
        #self.c4_phi = RooRealVar("c4_phi" + name,"c4_phi" + name,0)#.090,0.0784-s_a*0.0039,0.0784+s_a*0.0039)
        #self.c5_phi = RooRealVar("c5_phi" + name,"c5_phi" + name,0)#2.019,2.019-s_a*0.029,2.109+s_a*0.029)
        #self.c6_phi = RooRealVar("c6_phi" + name,"c6_phi" + name,0)#.33,.33-s_a*0.048,.33+s_a*0.048)
    def FlatAcc(self):
        name = self.namephys + self.namesample
        self.c1_psi = RooRealVar("c1_psi" + name,"c1_psi" + name,0)#-0.522,-0.522-s_a*0.014,-0.522+s_a*.014)
        self.c2_psi = RooRealVar("c2_psi" + name,"c2_psi" + name,0)#-0.723,-0.723-s_a*0.022,-0.723+s_a*0.022)
        self.c3_psi = RooRealVar("c3_psi" + name,"c3_psi" + name,0)#-0.190,-0.190-3*s_a,0.190+3*s_a)
        self.c4_psi = RooRealVar("c4_psi" + name,"c4_psi" + name,0)#0.208,0.208-s_a*0.023,0.208+s_a*0.023) 
        self.y_acc = RooRealVar("y" + name,"y" + name,1.)#,0.,s_a*1.6e-04)
        #self.c5_psi = RooFormulaVar("c5_psi" + name,"c5_psi" + name,"y" + name + " + (-1.-c1_psi"+ name + "-c2_psi" + name + "-c3_psi" + name + "-c4_psi" + name + ")",RooArgList(self.y,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
       
        #self.c1_theta = RooRealVar("c1_theta" + name,"c1_theta" + name,0.)
        self.c2_theta = RooRealVar("c2_theta" + name,"c2_theta" + name,0)#-0.1783,-0.1783-s_a*0.0075,-0.1783+s_a*0.0075)

        #self.c1_phi = RooRealVar("c1_phi" + name,"c1_phi" + name,0)#0.090,0.0784-s_a*0.0039,0.0784+s_a*0.0039)
        #self.c2_phi = RooRealVar("c2_phi" + name,"c2_phi" + name,0)#2.019,2.019-s_a*0.029,2.109+s_a*0.029)
        #self.c3_phi = RooRealVar("c3_phi" + name,"c3_phi" + name,0)#.33,.33-s_a*0.048,.33+s_a*0.048)
        #self.c4_phi = RooRealVar("c4_phi" + name,"c4_phi" + name,0)#.090,0.0784-s_a*0.0039,0.0784+s_a*0.0039)
        #self.c5_phi = RooRealVar("c5_phi" + name,"c5_phi" + name,0)#2.019,2.019-s_a*0.029,2.109+s_a*0.029)
        #self.c6_phi = RooRealVar("c6_phi" + name,"c6_phi" + name,0)#.33,.33-s_a*0.048,.33+s_a*0.048)
        
    def CopyAcc(self, other):
        self.c1_psi = other.c1_psi
        self.c2_psi = other.c2_psi
        self.c3_psi = other.c3_psi
        self.c4_psi = other.c4_psi
        self.c5_psi = other.c5_psi
        self.y_acc = other.y_acc
        #self.c1_theta = other.c1_theta
        self.c2_theta = other.c2_theta
        #self.c1_phi = other.c1_phi
        #self.c2_phi = other.c2_phi
        #self.c3_phi = other.c3_phi
        #self.c4_phi = other.c4_phi
        #self.c5_phi = other.c5_phi
        #self.c6_phi = other.c6_phi
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
    
        self.model = AccAngJpsiKpi_J1("angular " + name,"angular " + name, CPsi, CTheta, Phi, self.As2, self.fL_, self.fpa_, \
                                          self.dpa, self.dpe, self.ds, self.c1_psi, self.c2_psi, self.c3_psi, self.c4_psi, self.y_acc, self.c2_theta)#, self.c1_phi, self.c2_phi, self.c3_phi, self.c4_phi, self.c5_phi, self.c6_phi)
    
# Background
class FullBackground:
    def __init__(self, name = "Bkg"):
        self.name  = name
        if (SFIT==0 or SFIT==2):
            self.c1_phi_bkg = RooRealVar("c1_phi"+name,"c1_phi"+name,-4.38046e-01, -1,1)
            self.c2_phi_bkg = RooRealVar("c2_phi"+name,"c2_phi"+name,1.24342e-01,0.,.3)
            self.c3_phi_bkg = RooRealVar("c3_phi"+name,"c3_phi"+name,4.63368e-02,-0.1,.1)
            self.phibkg = RooPhiBkg("phibkg" + name,"phibkg" + name,Phi,self.c1_phi_bkg,self.c2_phi_bkg,self.c3_phi_bkg)
        else:
            print 'no bkg angular fit'
        self.kbkg = RooRealVar("k"+name,"k"+name,-1e-03,-1e-02,0)
        self.massbkg = RooExponential("Mass" + name, "Mass" + name, Mass, self.kbkg)

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
        if (SFIT==0 or SFIT==2):
         self.model = RooProdPdf("model"+name,"model"+name,RooArgList(self.psibkg,self.thetabkg,self.phibkg,self.massbkg))
        else:
         self.model = RooProdPdf("model"+name,"model"+name,RooArgList(self.massbkg))

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
        


def InitSignalPdfs(namephys, namesample ):
    sp =  AngularPDFMOD( namephys, namesample + "_pos_", 1)
    sn =  AngularPDFMOD( namephys, namesample + "_neg_", -1)
    return sp, sn
    
    
