from ROOT import *
from math import *
from graph_tools import *


gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegratedAcc2D/AngMassTerm.cxx+")
gROOT.ProcessLine(".x $BSKSTKSTROOT/src/BkgAngPDF.cxx+")

## Variables
# CTh1 = RooRealVar("CosTheta1","CosTheta1",-1.,1.)
# CTh2 = RooRealVar("CosTheta2","CosTheta2",-1.,1.)
# Phi = RooRealVar("Phi","Phi",0,2*pi)#2*pi*(1.-0.1))
# m1 = RooRealVar("P1_mass","P1_mass",896-150,896+150)
# m2 = RooRealVar("P2_mass","P2_mass",896-150,896+150)
CTh1 = RooRealVar("cos_ThetaK","cos_ThetaK",-1.,1.)
CTh2 = RooRealVar("cos_ThetaL","cos_ThetaL",-1.,1.)
Phi = RooRealVar("B_s0_Phi","Phi",0,2*pi)
m1 = RooRealVar("Kst_M","Kst_M",896-150,896+150)
m2 = RooRealVar("Kstb_M","Kstb_M",896-150,896+150)



 
class AngularPDF:
    def __init__(self,name,filename,acc_name):
#     def __init__(self,name,acc_tree,acc_name):

        self.name = name

        ## Constants
        self.MBs = RooRealVar("MBs_"+name,"MBs_"+name,5366.3)
        self.DGs = RooRealVar("DGs_"+name,"DGs_"+name,0.062)
        self.Gs = RooRealVar("Gs_"+name,"Gs_"+name,0.6793)
        self.GL = RooFormulaVar("GL_"+name,"GL_"+name,"Gs_"+name+" + DGs_"+name+"/2.",RooArgList(self.Gs,self.DGs))
        self.GH = RooFormulaVar("GH_"+name,"GH_"+name,"Gs_"+name+" - DGs_"+name+"/2.",RooArgList(self.Gs,self.DGs))
        self.m_kst = RooRealVar("m_kst_"+name,"m_kst_"+name,896-5,896+5)
        self.m_kst0 = RooRealVar("m_kst0_"+name,"m_kst0_"+name,1430.)
        self.g_kst = RooRealVar("g_kst_"+name,"g_kst_"+name,50-10,50+10)
        self.g_kst0 = RooRealVar("g_kst0_"+name,"g_kst0_"+name,279.)
        
        # Acceptances
#         self.acc_tree = acc_tree
        self.filename = filename
        self.acc_name = acc_name

        # Normalization
                
        self.normname = "norm_"+self.name
        self.normPname = "normP_"+self.name
        self.normSname = "normS_"+self.name
        self.normSSname = "normSS_"+self.name
        self.normFBname = "normFB_"+self.name
        self.GLname = "GL_"+self.name
        self.GHname = "GH_"+self.name


        self.norm = RooRealVar("norm_"+name,"norm_"+name,1)
        self.normP = RooRealVar(self.normPname,self.normPname,1e-10/ 1.77453790754)
        self.normS = RooRealVar(self.normSname,self.normSname,1e-10/1.88751963995)
        self.normSS = RooRealVar(self.normSSname,self.normSSname,1e-10/2.00768791208)
        self.norm_fb = RooRealVar(self.normFBname,self.normFBname,1)

        # Background fraction
        self.fbkg = RooRealVar("fbkg_"+self.name,"fbkg_"+self.name,0.062)



    def OwnPhys(self):
        
        self.fL = RooRealVar("fL_"+self.name,"fL_"+self.name,0.6,0.,1)#0.507,0.1, .65)
        self.fpax = RooRealVar("fpax_"+self.name,"fpax_"+self.name,0.3,0.,1.)#0.172,0.07, .45)
        self.Asm2 = RooRealVar("Asm2_"+self.name,"Asm2_"+self.name,0.2,1e-17,1.)
        self.Asp2x = RooRealVar("Asp2x_"+self.name,"Asp2x_"+self.name,0.05,0.,1.)#0.2,0.,1.)
        self.Ass2x = RooRealVar("Ass2x_"+self.name,"Ass2x_"+self.name,0.0001,0.,1)       
        self.Bs2 = RooRealVar("Bs2_"+self.name,"Bs2_"+self.name,.05,0.,0.5)
        self.dpa = RooRealVar("dpa_"+self.name,"dpa_" + self.name,-2.*pi,2*pi)
        self.dpe = RooRealVar("dpe_"+self.name,"dpe_" + self.name, 0.4, 0., 2.*pi)
        self.d0 = RooRealVar("d0_"+self.name,"d0_"+self.name,0.)
        self.dsp = RooRealVar("dsp_"+self.name,"dsp_"+self.name, 2.24,0.,2*pi)#2.5, 1.5 , 3.5)
        self.dsm = RooRealVar("dsm_"+self.name,"dsm_"+self.name, 0.,2*pi)
        self.dss = RooRealVar("dss_"+self.name,"dss_"+self.name,-pi,pi)

        self.CreateAmplitudes()

    def CopyPhys(self,other):
        
        self.fL = other.fL
        self.fpax = other.fpax
        self.Asm2 = other.Asm2
        self.Asp2x = other.Asp2x
        self.Ass2x = other.Ass2x
        self.Bs2 = other.Bs2
        self.dpa = other.dpa
        self.dpe = other.dpe
        self.d0 = other.d0
        self.dsp = other.dsp
        self.dsm = other.dsm
        self.dss = other.dss
        self.m_kst = other.m_kst
        self.g_kst = other.g_kst

        self.CreateAmplitudes()


    def CopyNorm(self,other):
        self.norm = other.norm
        self.normP = other.normP
        self.normS = other.normS
        self.normSS = other.normSS
        self.norm_fb = other.norm_fb

        self.normname = self.norm.GetName()
        self.normPname = self.normP.GetName()
        self.normSname = self.normS.GetName()
        self.normSSname = self.normSS.GetName()
        self.normFBname = self.norm_fb.GetName()
 

    def CopyAcceptance(self,other):
        self.c1_th = other.c1_th
        self.c2_th = other.c2_th
        self.c3_th = other.c3_th
        self.c4_th = other.c4_th
        self.y = other.y
        self.c1_ph = other.c1_ph
        self.c2_ph = other.c2_ph
        self.c3_ph = other.c3_ph
        


    def CopySwave(self,other):
        
        self.fL = RooRealVar("fL_"+self.name,"fL_"+self.name,0.507,0.1, .65)
        self.fpa = RooRealVar("fpa_"+self.name,"fpa_"+self.name,0.172,0.07, .45)
        self.Asp2 = other.Asp2
        self.Asm2 = other.Asm2
        self.Ass2 = other.Ass2
        self.Bs2 = other.Bs2
        self.dpa = RooRealVar("dpa_"+self.name,"dpa_" + self.name,  -0.8,-1.8,0.2)
        self.dpe = RooRealVar("dpe_"+self.name,"dpe_" + self.name, 0.4, -1., 2.)
        self.d0 = RooRealVar("d0_"+self.name,"d0_"+self.name,0.)
        self.dsp = other.dsp
        self.dsm = other.dsm
        self.dss = other.dss

        self.CreateAmplitudes()



    def CreateAmplitudes(self):

        ## Parameters of interest
        
        self.A0name = "A0_"+self.name
        self.Apaname = "Apa_"+self.name
        self.Apename = "Ape_"+self.name
        self.Aspname = "Asp_"+self.name
        self.Asmname = "Asm_"+self.name
        self.Bsname = "Bs_"+self.name
        self.Assname = "Ass_"+self.name
        self.dspname = self.dsp.GetName()
        self.dsmname = self.dsm.GetName()
        self.dpaname = self.dpa.GetName()
        self.dpename = self.dpe.GetName()
        self.dssname = self.dss.GetName()

        name = self.name
        fL_name = self.fL.GetName()
        fpax_name = self.fpax.GetName()
        Asm2_name = self.Asm2.GetName()
        Asp2x_name = self.Asp2x.GetName()
        Ass2x_name = self.Ass2x.GetName()

        self.fpa = RooFormulaVar("fpa_"+name,"fpa_"+name,fpax_name+"*(1-"+fL_name+")",RooArgList(self.fL,self.fpax))
        self.fpe = RooFormulaVar("fpe_"+name,"fpe_"+name,"1-fpa_"+name+"-"+fL_name,RooArgList(self.fL,self.fpa))
        self.Asp2 = RooFormulaVar("Asp2_"+name,"Asp2_"+name,Asp2x_name+"*(1-"+Asm2_name+")",RooArgList(self.Asp2x,self.Asm2))
        self.Ass2 = RooFormulaVar("Ass2_"+name,"Ass2_"+name,Ass2x_name+"*(1-"+Asm2_name+"-Asp2_"+name+")",RooArgList(self.Asm2,self.Asp2,self.Ass2x))
        self.Ap2 = RooFormulaVar("Ap2_"+name,"Ap2_"+name,"1-Asp2_"+name+"-"+Asm2_name+"-Ass2_"+name,RooArgList(self.Asp2,self.Asm2,self.Ass2))


    def modParamAsym(self, name, v0, v1,v2, cte = 0):
        getattr(self, name).setVal(v0)
        getattr(self, name).setMin(v0-v1)
        getattr(self, name).setMax(v0+v2)
        getattr(self, name).setConstant(cte)
        return 1

    def modParam(self, name, v0, v1, cte = 0):
        return self.modParamAsym(name, v0, v1, v1, cte)



    def make(self):

        #Define all (18) terms

        name = self.name

        self.indices = [1,2,3,5,7,71,12,8,81,9,91,10,101,11,111,13,14,15]

        self.een = RooRealVar("een_"+name,"een_"+name,1)

        self.products = []

        self.dummyParamList = RooArgList() ## 18 times 1
        self.finalFuncList = RooArgList()
        self.finalFuncSet = RooArgSet()
        
        for index in self.indices:

            self.term_index = AngMassTerm("KFM"+str(index)+"_"+name,"KFM"+str(index)+"_"+name,index,CTh1,CTh2,Phi,m1,m2,
                                     self.fL,self.fpa,self.Asp2,self.Asm2,self.Ass2,
                                     self.dpa,self.dpe,self.dsp,self.dsm,self.dss,
                                     self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,
                                     self.Gs,self.DGs,self.norm,self.normP,self.normS,self.normSS,self.filename,self.acc_name)
                               
                               

            #self.term_index.forceNumInt(1)
            self.products.append(self.term_index)

            self.dummyParamList.add(self.een)
            self.finalFuncList.add(self.term_index)
            self.finalFuncSet.add(self.term_index)
            
                               
        self.sigmodel = RooRealSumPdf("sigmodel_"+self.name, "sigmodel_"+self.name, self.finalFuncList,self.dummyParamList)

        self.signalforFB = RooAddition("signalforFB_"+self.name,"signalforFB_"+self.name,self.finalFuncList)
        self.Nps = []
        self.Nms = []
        self.Ntots = []
        self.Asyms = []

        
        self.PWFuncList = RooArgList(self.products[0],self.products[1],self.products[2],self.products[3])
        self.SWFuncList = RooArgList(self.products[4],self.products[5],self.products[6])
        self.SW_intFuncList = RooArgList(self.products[7],self.products[8],self.products[9],self.products[10],self.products[11],self.products[12])

        self.Pwave = RooAddition("Pwave_"+name, "Pwave_"+name,self.PWFuncList)
        self.Swave = RooAddition("Swave_"+name, "Swave_"+name,self.SWFuncList)
        self.Swave_int = RooAddition("Swave_int_"+name, "Swave_int_"+name,self.SW_intFuncList)


        self.Background("right",self.name)
        

        self.model = RooAddPdf("model_"+self.name,"model_"+self.name,RooArgList(self.modelBKG,self.sigmodel),RooArgList(self.fbkg))

    def Background(self,sideband,name):

        # CTh1 = CTh1
        # CTh2 = self.CTh2
        # Phi = self.Phi
        # m1 = self.m1
        # m2 = self.m2

        if sideband=="both":

            self.mean = RooRealVar("mean_"+name,"mean_"+name,8.95848e+02)
            self.width = RooRealVar("width_"+name,"width_"+name,5.61015e-07)
            
            self.k1_m = RooRealVar("k1_m_"+name,"k1_m_"+name,-2.27977e-04)
            self.k2_m = RooRealVar("k2_m_"+name,"k2_m_"+name,0.,1.)
            
            self.fBW = RooRealVar("fBW_"+name,"Breit Wigner fraction "+name,1.80822e-01)
            
            self.c1_th_bkg = RooRealVar("c1_th_bkg_"+name,"c1_th_bkg_"+name,1.56903e-01)
            self.c2_th_bkg = RooRealVar("c2_th_bkg_"+name,"c2_th_bkg_"+name,-4.37597e-01)
            self.c3_th_bkg = RooRealVar("c3_th_bkg_"+name,"c3_th_bkg_"+name,-2.80726e+00)
            self.c4_th_bkg = RooRealVar("c4_th_bkg_"+name,"c4_th_bkg_"+name,3.72988e-01)
            self.y = RooRealVar("y_"+name,"y_"+name,5.61015e-07)
            
            self.phic1 = RooRealVar("phic1_"+name,"phic1_"+name,0.)
            self.phic2 = RooRealVar("phic2_"+name,"phic2_"+name,0.)
            

            self.c5_th_bkg = RooFormulaVar("c5_th_bkg_"+name,"c5_th_bkg_"+name, "y_"+name+"-(1+c1_th_bkg_"+name+"+c2_th_bkg_"+name+"+c3_th_bkg_"+name+"+c4_th_bkg_"+name+")",RooArgList(self.y,self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg))


            self.CTh1bkg = RooPolynomial("CTh1bkg_"+name,"CTh1bkg_"+name,CTh1,RooArgList(self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg,self.c5_th_bkg))
            self.CTh2bkg = RooPolynomial("CTh2bkg_"+name,"CTh2bkg_"+name,CTh2,RooArgList(self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg,self.c5_th_bkg))

            self.phibkgmodel = RooPolynomial("PhiBkg_"+name,"PhiBkg_"+name,Phi,RooArgList(self.phic1,self.phic2))

            self.Angbkg = RooProdPdf("Angbkg_"+name,"Angbkg_"+name,RooArgList(self.CTh1bkg,self.CTh2bkg,self.phibkgmodel))


        elif sideband=="old":

            self.mean = RooRealVar("mean_"+name,"mean_"+name,9.05997e+02)
            self.width = RooRealVar("width_"+name,"width_"+name,4.00000e+01)

            self.k1_m = RooRealVar("k1_m_"+name,"k1_m_"+name,-2.04199e-04)#1.86814e-03)
            self.k2_m = RooRealVar("k2_m_"+name,"k2_m_"+name,0.)

            self.fBW = RooRealVar("fBW_"+name,"Breit Wigner fraction 1 "+name,2.12592e-01)
            
            self.c1_th_bkg = RooRealVar("c1_th_bkg_"+name,"c1_th_bkg_"+name,-2.98053e-01)
            self.c2_th_bkg = RooRealVar("c2_th_bkg_"+name,"c2_th_bkg_"+name,-5.14457e-01)
            self.c3_th_bkg = RooRealVar("c3_th_bkg_"+name,"c3_th_bkg_"+name,-2.56461e-01)
            self.c4_th_bkg = RooRealVar("c4_th_bkg_"+name,"c4_th_bkg_"+name,8.41426e-01)
            self.y = RooRealVar("y_"+name,"y_"+name,9.62981e-08 )
            
            self.phic1 = RooRealVar("phic1_"+name,"phic1_"+name,0.)#-0.5,0.5)#-3.70642e-01)#0.)#-0.30774747327984547)
            self.phic2 = RooRealVar("phic2_"+name,"phic2_"+name,0.)#-0.5,0.5)#4.78659e-02)#0.)#0.048849572361207537)#chi2/NODF = 3.822/7
            
            self.c5_th_bkg = RooFormulaVar("c5_th_bkg_"+name,"c5_th_bkg_"+name, "y_"+name+"-(1+c1_th_bkg_"+name+"+c2_th_bkg_"+name+"+c3_th_bkg_"+name+"+c4_th_bkg_"+name+")",RooArgList(self.y,self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg))

            self.CTh1bkg = RooPolynomial("CTh1bkg_"+name,"CTh1bkg_"+name,CTh1,RooArgList(self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg,self.c5_th_bkg))
            self.CTh2bkg = RooPolynomial("CTh2bkg_"+name,"CTh2bkg_"+name,CTh2,RooArgList(self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg,self.c5_th_bkg))

            self.phibkgmodel = RooPolynomial("PhiBkg_"+name,"PhiBkg_"+name,Phi,RooArgList(self.phic1,self.phic2))

            self.Angbkg = RooProdPdf("Angbkg_"+name,"Angbkg_"+name,RooArgList(self.CTh1bkg,self.CTh2bkg,self.phibkgmodel))



        else:


            self.mean = RooRealVar("mean_"+name,"mean_"+name,8.96660e+02)
            self.width = RooRealVar("width_"+name,"width_"+name,5.97821e+01)

            self.k1_m = RooRealVar("k1_m_"+name,"k1_m_"+name,-3.72256e-05)
            self.k2_m = RooRealVar("k2_m_"+name,"k2_m_"+name,0.)

            self.fBW = RooRealVar("fBW_"+name,"Breit Wigner fraction 1 "+name,1.82290e-01)
            
            self.c1_th_bkg = RooRealVar("c1_th_bkg_"+name,"c1_th_bkg_"+name,1.82648e-01)
            self.c2_th_bkg = RooRealVar("c2_th_bkg_"+name,"c2_th_bkg_"+name,-1.04548e+00)
            self.c3_th_bkg = RooRealVar("c3_th_bkg_"+name,"c3_th_bkg_"+name,-2.29547e+00)
            self.c4_th_bkg = RooRealVar("c4_th_bkg_"+name,"c4_th_bkg_"+name,6.78624e-01)
            self.y = RooRealVar("y_"+name,"y_"+name,4.37650e-13)

            self.c5_th_bkg = RooFormulaVar("c5_th_bkg_"+name,"c5_th_bkg_"+name, "y_"+name+"-(1+0.8*c1_th_bkg_"+name+"+pow(0.8,2)*c2_th_bkg_"+name+"+pow(0.8,3)*c3_th_bkg_"+name+"+pow(0.8,4)*c4_th_bkg_"+name+")/pow(0.8,5)",RooArgList(self.y,self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg))

            
            self.phic1 = RooRealVar("phic1_"+name,"phic1_"+name,0.)#-0.5,0.5)#-3.70642e-01)#0.)#-0.30774747327984547)
            self.phic2 = RooRealVar("phic2_"+name,"phic2_"+name,0.)#-0.5,0.5)#4.78659e-02)#0.)#0.048849572361207537)#chi2/NODF = 3.822/7

            self.upper = RooRealVar("upper_"+name,"upper_"+name,0.8)

            self.Angbkg = BkgAngPDF("Angbkg_"+name,"Angbkg_"+name,CTh1,CTh2,Phi,self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg,self.c5_th_bkg,self.upper)
            

            
        self.BW_m1 = RooBreitWigner("BW_m1_"+name,"BW_m1_"+name,m1,self.mean,self.width)
        self.BW_m2 = RooBreitWigner("BW_m2_"+name,"BW_m2_"+name,m2,self.mean,self.width)

        #same Kst number
        
        self.P11_mass = RooRealVar("P11_mass_"+name,"P11_mass_"+name,493.667)
        self.P12_mass = RooRealVar("P12_mass_"+name,"P12_mass_"+name,139.57018)

        self.lin_m1 = RooGenericPdf("lin_m1_"+name,"exp(k1_m_"+name+" *"+m1.GetName()+")*(1./(8.*pi)*sqrt(1.-2.*(P11_mass_"+name+"**2. + P12_mass_"+name+"**2.)/"+m1.GetName()+"**2. + (P11_mass_"+name+"**2. - P12_mass_"+name+"**2.)**2./"+m1.GetName()+"**4.))", RooArgList(self.k1_m , m1, self.P11_mass, self.P12_mass))
        self.lin_m2 = RooGenericPdf("lin_m2_"+name,"exp(k1_m_"+name+" *"+m2.GetName()+")*(1./(8.*pi)*sqrt(1.-2.*(P11_mass_"+name+"**2. + P12_mass_"+name+"**2.)/"+m2.GetName()+"**2. + (P11_mass_"+name+"**2. - P12_mass_"+name+"**2.)**2./"+m2.GetName()+"**4.))", RooArgList(self.k1_m, m2, self.P11_mass, self.P12_mass))
        

        self.modelBKG_m1 = RooAddPdf("modelBKG_m1_"+name,"Mass modelBKG m1 "+name,self.BW_m1,self.lin_m1,self.fBW)
        self.modelBKG_m2 = RooAddPdf("modelBKG_m2_"+name,"Mass modelBKG m2 "+name,self.BW_m2,self.lin_m2,self.fBW)


        self.modelBKG = RooProdPdf("modelBKG_"+name,"modelBKG_"+name,RooArgList(self.Angbkg,self.modelBKG_m1,self.modelBKG_m2))



    def ForceAngNumInt(self):


        self.f1.forceNumInt(1)
        self.f2.forceNumInt(1)
        self.f3.forceNumInt(1)
        self.f5.forceNumInt(1)
        self.f7s.forceNumInt(1)
        self.f7sbar.forceNumInt(1)
        self.f7_int.forceNumInt(1)
        self.f8s.forceNumInt(1)
        self.f8sbar.forceNumInt(1)
        self.f9s.forceNumInt(1)
        self.f9sbar.forceNumInt(1)
        self.f10s.forceNumInt(1)
        self.f10sbar.forceNumInt(1)
        self.f11s.forceNumInt(1)
        self.f11sbar.forceNumInt(1)
        self.f13.forceNumInt(1)
        self.f14.forceNumInt(1)
        self.f15.forceNumInt(1)
        self.fFB.forceNumInt(1)


        

    def getFBasymmetry(self,var="CosTheta1", corrAcc=1):


        name = self.name

        if corrAcc:
            self.f1.useAcc(0)
            self.f2.useAcc(0)
            self.f3.useAcc(0)
            self.f5.useAcc(0)
            self.f7s.useAcc(0)
            self.f7sbar.useAcc(0)
            self.f7_int.useAcc(0)
            self.f8s.useAcc(0)
            self.f8sbar.useAcc(0)
            self.f9s.useAcc(0)
            self.f9sbar.useAcc(0)
            self.f10s.useAcc(0)
            self.f10sbar.useAcc(0)
            self.f11s.useAcc(0)
            self.f11sbar.useAcc(0)
            self.f13.useAcc(0)
            self.f14.useAcc(0)
            self.f15.useAcc(0)
            self.fFB.useAcc(0)
            
            self.c1_m.setVal(1)
            self.c2_m.setVal(0)

#         else:
#             self.f1.forceNumInt(1)
#             self.f2.forceNumInt(1)
#             self.f3.forceNumInt(1)
#             self.f5.forceNumInt(1)
#             self.f7s.forceNumInt(1)
#             self.f7sbar.forceNumInt(1)
#             self.f7_int.forceNumInt(1)
#             self.f8s.forceNumInt(1)
#             self.f8sbar.forceNumInt(1)
#             self.f9s.forceNumInt(1)
#             self.f9sbar.forceNumInt(1)

        

        if var=="CosTheta1":

            integ_vars = RooArgSet(CTh1,CTh2,Phi,m2)
            CTh1.setRange("RangeNm"+var+name,-1.,0.)
            CTh1.setRange("RangeNp"+var+name,0.,1.)


        elif var=="CosTheta2":

            integ_vars = RooArgSet(CTh1,CTh2,Phi,m1)
            CTh2.setRange("RangeNm"+var+name,-1.,0.)
            CTh2.setRange("RangeNp"+var+name,0.,1.)


        else:
            print "Cannot calculate FB asymmetry for the variable: ",var
            return 0

        
        Np = self.signalforFB.createIntegral(integ_vars,"RangeNp"+var+name)
        Np.SetNameTitle("Np_"+var+name,"Np_"+var+name)
        Nm = self.signalforFB.createIntegral(integ_vars,"RangeNm"+var+name)
        Nm.SetNameTitle("Nm_"+var+name,"Nm_"+var+name)
        Ntot = self.signalforFB.createIntegral(integ_vars,"FULL")
        Ntot.SetNameTitle("Ntot_"+var+name,"Ntot_"+var+name)

        self.Nps.append(Np)
        self.Nms.append(Nm)
        self.Ntots.append(Ntot)
        
        Asym = RooFormulaVar("FBAsym_"+var+name,"FBAsym_"+var+name,"(Np_"+var+name+"-Nm_"+var+name+")/Ntot_"+var+name,RooArgList(Np,Nm,Ntot))

        self.Asyms.append(Asym)
        
        return Asym










class FullBackground:
    def __init__(self, name = "Bkg",sideband="right"):

        self.name = name
        
        self.mean = RooRealVar("mean_"+name,"mean_"+name,896-50,896+50)
        self.width = RooRealVar("width_"+name,"width_"+name,50-30,50+30)
        
        self.k1_m = RooRealVar("k1_m_"+name,"k1_m_"+name,-0.5,0.)
        self.k2_m = RooRealVar("k2_m_"+name,"k2_m_"+name,0.,1.)
        
        self.fBW = RooRealVar("fBW_"+name,"Breit Wigner fraction "+name,0.,0.5)
            
        self.c1_th_bkg = RooRealVar("c1_th_bkg_"+name,"c1_th_bkg_"+name,1.56903e-01, -1,1)
        self.c2_th_bkg = RooRealVar("c2_th_bkg_"+name,"c2_th_bkg_"+name,-4.37597e-01, -1,1)
        self.c3_th_bkg = RooRealVar("c3_th_bkg_"+name,"c3_th_bkg_"+name,-2.80726e+00, -1,1)
        self.c4_th_bkg = RooRealVar("c4_th_bkg_"+name,"c4_th_bkg_"+name,3.72988e-01, -1,1)
        self.y = RooRealVar("y_"+name,"y_"+name,5.61015e-07, 0,1)
            
        self.phic1 = RooRealVar("phic1_"+name,"phic1_"+name,0.,1.)
        self.phic2 = RooRealVar("phic2_"+name,"phic2_"+name,0.,1.)

        self.P11_mass = RooRealVar("P11_mass_"+name,"P11_mass_"+name,493.667)
        self.P12_mass = RooRealVar("P12_mass_"+name,"P12_mass_"+name,139.57018)

        self.SetParameters(sideband)   



 
    def SetParameters(self,sideband):


        if sideband=="both":

            self.mean.setVal(8.95848e+02)
            self.width.setVal(5.61015e-07)
            
            self.k1_m.setVal(-2.27977e-04)
            self.k2_m.setVal(0.)
            
            self.fBW.setVal(1.80822e-01)
            
            self.c1_th_bkg.setVal(1.56903e-01)
            self.c2_th_bkg.setVal(-4.37597e-01)
            self.c3_th_bkg.setVal(-2.80726e+00)
            self.c4_th_bkg.setVal(3.72988e-01)
            self.y.setVal(5.61015e-07)
            
            self.phic1.setVal(0.)
            self.phic2.setVal(0.)

            


        else:

            self.mean.setVal(9.05997e+02)
            self.width.setVal(4.00000e+01)
            
            self.k1_m.setVal(-2.04199e-04)
            self.k2_m.setVal(0.)
            
            self.fBW.setVal(2.12592e-01)
            
            self.c1_th_bkg.setVal(-2.98053e-01)
            self.c2_th_bkg.setVal(-5.14457e-01)
            self.c3_th_bkg.setVal(-2.56461e-01)
            self.c4_th_bkg.setVal(8.41426e-01)
            self.y.setVal(9.62981e-08)
            
            self.phic1.setVal(0.)
            self.phic2.setVal(0.)




        self.mean.setConstant(1)
        self.width.setConstant(1)
        self.k1_m.setConstant(1)
        self.k2_m.setConstant(1)
        self.fBW.setConstant(1)
        self.c1_th_bkg.setConstant(1)
        self.c2_th_bkg.setConstant(1)
        self.c3_th_bkg.setConstant(1)
        self.c4_th_bkg.setConstant(1)
        self.y.setConstant(1)
        self.phic1.setConstant(1)
        self.phic2.setConstant(1)


    def modParamAsym(self, name, v0, v1,v2):
        getattr(self, name).setVal(v0)
        getattr(self, name).setMin(v0-v1)
        getattr(self, name).setMax(v0+v2)
        return 1

    def modParam(self, name, v0, v1):
        return self.modParamAsym(name, v0, v1, v1)

    def make(self):

        name = self.name

        self.BW_m1 = RooBreitWigner("BW_m1_"+name,"BW_m1_"+name,m1,self.mean,self.width)
        self.BW_m2 = RooBreitWigner("BW_m2_"+name,"BW_m2_"+name,m2,self.mean,self.width)

        #same Kst number
        

        self.lin_m1 = RooGenericPdf("lin_m1_"+name,"exp(k1_m_"+name+" *P1_mass)*(1./(8.*pi)*sqrt(1.-2.*(P11_mass_"+name+"**2. + P12_mass_"+name+"**2.)/P1_mass**2. + (P11_mass_"+name+"**2. - P12_mass_"+name+"**2.)**2./P1_mass**4.))", RooArgList(self.k1_m , m1, self.P11_mass, self.P12_mass))
        self.lin_m2 = RooGenericPdf("lin_m2_"+name,"exp(k1_m_"+name+" *P2_mass)*(1./(8.*pi)*sqrt(1.-2.*(P11_mass_"+name+"**2. + P12_mass_"+name+"**2.)/P2_mass**2. + (P11_mass_"+name+"**2. - P12_mass_"+name+"**2.)**2./P2_mass**4.))", RooArgList(self.k1_m, m2, self.P11_mass, self.P12_mass))
        

        self.modelBKG_m1 = RooAddPdf("modelBKG_m1_"+name,"Mass modelBKG m1 "+name,self.BW_m1,self.lin_m1,self.fBW)
        self.modelBKG_m2 = RooAddPdf("modelBKG_m2_"+name,"Mass modelBKG m2 "+name,self.BW_m2,self.lin_m2,self.fBW)


        self.c5_th_bkg = RooFormulaVar("c5_th_bkg_"+name,"c5_th_bkg_"+name, "y_"+name+"-(1+c1_th_bkg_"+name+"+c2_th_bkg_"+name+"+c3_th_bkg_"+name+"+c4_th_bkg_"+name+")",RooArgList(self.y,self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg))


        self.CTh1bkg = RooPolynomial("CTh1bkg_"+name,"CTh1bkg_"+name,CTh1,RooArgList(self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg,self.c5_th_bkg))
        self.CTh2bkg = RooPolynomial("CTh2bkg_"+name,"CTh2bkg_"+name,CTh2,RooArgList(self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg,self.c5_th_bkg))

        self.phibkgmodel = RooPolynomial("PhiBkg_"+name,"PhiBkg_"+name,Phi,RooArgList(self.phic1,self.phic2))


        self.modelBKG = RooProdPdf("modelBKG_"+name,"modelBKG_"+name,RooArgList(self.CTh1bkg,self.CTh2bkg,self.phibkgmodel,self.modelBKG_m1,self.modelBKG_m2))



