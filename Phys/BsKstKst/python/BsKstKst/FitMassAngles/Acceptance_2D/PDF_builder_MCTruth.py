from ROOT import *
from math import *
from graph_tools import *

gROOT.ProcessLine(".L ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngAbsFunc.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF1.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF2.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF3.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF5.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF7.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF7_int.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF8.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF9.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF10.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF11.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF13.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF14.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/AngF15.cxx+")
gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegrated_MCTruth/MassK1.cxx+")



gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/TimeIntegratedRephase/FourB.cxx+")




## Variables
# CTh1 = RooRealVar("CosTheta1","CosTheta1",-1.,1.)
# CTh2 = RooRealVar("CosTheta2","CosTheta2",-1.,1.)
# Phi = RooRealVar("Phi","Phi",0,2*pi)#2*pi*(1.-0.1))
# m1 = RooRealVar("P1_mass","P1_mass",896-150,896+150)
# m2 = RooRealVar("P2_mass","P2_mass",896-150,896+150)
CTh1 = RooRealVar("cos_ThetaK","cos_ThetaK",-1.,1.)
CTh2 = RooRealVar("cos_ThetaL","cos_ThetaL",-1.,1.)
Phi = RooRealVar("B_s0_Phi","Phi",-pi,pi)
m1 = RooRealVar("Kst_M","Kst_M",896-150,896+150)
m2 = RooRealVar("Kstb_M","Kstb_M",896-150,896+150)



 
class AngularPDF:
    def __init__(self,name):

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

        
        self.c1_th = RooRealVar("c1_th_"+name,"c1_th_"+name,-1.15214e-01,-0.5,0.5)
        self.c2_th = RooRealVar("c2_th_"+name,"c2_th_"+name,-3.79288e-01,-2.,1.)
        self.c3_th = RooRealVar("c3_th_"+name,"c3_th_"+name,-5.65808e-01,-1.,1.)
        self.c4_th = RooRealVar("c4_th_"+name,"c4_th_"+name,-1.37544e-01,-0.5,1.)

        
        self.y = RooRealVar("y_"+name,"y_"+name,1.71127e-03,0.,1.)
        
        self.c1_ph = RooRealVar("c1_ph_"+name,"c1_ph_"+name,0.,1.)#2.43356e-02)
        self.c2_ph = RooRealVar("c2_ph_"+name,"c2_ph_"+name,1.5,0.1,3)#1.67186e+00)  ### This constant cannot be 0 or 1, it appears in the denominator of the integrals!!
        self.c3_ph = RooRealVar("c3_ph_"+name,"c3_ph_"+name,0.,2*pi)
        
        self.c1_m = RooRealVar("c1_m_"+name,"c1_m_"+name,1.)
        self.c2_m = RooRealVar("c2_m_"+name,"c2_m_"+name,0.)


        self.massAcc_coefList = RooArgList(self.c1_m,self.c2_m)

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



        # Stuff to calculate integrals
        self.one = RooRealVar("one","one",1)
        self.zero = RooRealVar("zero","zero",0)
       
        self.PP_massfunc = MassK1("PP_massfunc_"+name,"PP_massfunc",m1,m2,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,
                                  self.MBs,self.massAcc_coefList,self.one)
       



    def OwnPhys(self):
        
        self.fL = RooRealVar("fL_"+self.name,"fL_"+self.name,0.6,0.,1)#0.507,0.1, .65)
        self.fpax = RooRealVar("fpax_"+self.name,"fpax_"+self.name,0.3,0.,1.)#0.172,0.07, .45)
        self.Asp2 = RooRealVar("Asp2_"+self.name,"Asp2_"+self.name,0.05,0.,0.5)#0.2,0.,1.)
        self.Asm2 = RooRealVar("Asm2_"+self.name,"Asm2_"+self.name,0.2,0.,1.)
        self.Ass2 = RooRealVar("Ass2_"+self.name,"Ass2_"+self.name,0.0001,0.,0.20)       
        self.Bs2 = RooRealVar("Bs2_"+self.name,"Bs2_"+self.name,.05,0.,0.5)
        self.dpa = RooRealVar("dpa_"+self.name,"dpa_" + self.name,-2.*pi,2*pi)
        self.dpe = RooRealVar("dpe_"+self.name,"dpe_" + self.name, 0.4, 0., 2.*pi)
        self.d0 = RooRealVar("d0_"+self.name,"d0_"+self.name,0.)
        self.dsp = RooRealVar("dsp_"+self.name,"dsp_"+self.name, 2.24,0.,2*pi)#2.5, 1.5 , 3.5)
        self.dsm = RooRealVar("dsm_"+self.name,"dsm_"+self.name, 0.,2*pi)
        self.dss = RooRealVar("dss_"+self.name,"dss_"+self.name,-pi,pi)

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
        self.dssname = self.dss.GetName

        name = self.name

#         self.A02 = RooFormulaVar("A02_"+self.name,"A02_"+self.name,"fL_"+self.name+"*(1-"+self.Asp2.GetName()+"-"+self.Asm2.GetName()+"-"+self.Bs2.GetName()+"-"+self.Ass2.GetName()+")",
#                                  RooArgList(self.fL, self.Asp2, self.Asm2, self.Bs2, self.Ass2))

#         self.Apa2 = RooFormulaVar("Apa2_"+self.name,"Apa2_"+self.name,"fpa_"+self.name+"*(1-"+self.Asp2.GetName()+"-"+self.Asm2.GetName()+"-"+self.Bs2.GetName()+"-"+self.Ass2.GetName()+")",
#                                   RooArgList(self.fpa, self.Asp2, self.Asm2, self.Bs2, self.Ass2))
        
#         self.Ape = RooFormulaVar("Ape_"+self.name,"Ape_"+self.name,"sqrt(1-A02_"+self.name+"-Apa2_"+self.name+"-"+self.Asp2.GetName()+"-"+self.Asm2.GetName()+"-"+self.Bs2.GetName()+"-"+self.Ass2.GetName()+")",RooArgList(self.A02,self.Apa2,self.Asp2,self.Asm2,self.Bs2, self.Ass2))


        self.fpa = RooFormulaVar("fpa_"+name,"fpa_"+name,"fpax_"+name+"*(1-fL_"+name+")",RooArgList(self.fL,self.fpax))
        self.fpe = RooFormulaVar("fpe_"+name,"fpe_"+name,"1-fpa_"+name+"-fL_"+name,RooArgList(self.fL,self.fpa))
        self.Ap2 = RooFormulaVar("Ap2_"+name,"Ap2_"+name,"1-Asp2_"+name+"-Asm2_"+name+"-Ass2_"+name,RooArgList(self.Asp2,self.Asm2,self.Ass2))

        self.A02 = RooFormulaVar("A02_"+self.name,"A02_"+self.name,"fL_"+name+"*Ap2_"+name,RooArgList(self.fL,self.Ap2))
        self.Apa2 = RooFormulaVar("Apa2_"+self.name,"Apa2_"+self.name,"fpa_"+name+"*Ap2_"+name,RooArgList(self.fpa,self.Ap2))
        self.Ape2 = RooFormulaVar("Ape2_"+self.name,"Ape2_"+self.name,"fpe_"+name+"*Ap2_"+name,RooArgList(self.fpe,self.Ap2))
        
        
        self.A0 = RooFormulaVar(self.A0name,self.A0name,"sqrt(A02_"+self.name+")",RooArgList(self.A02))
        self.Apa = RooFormulaVar(self.Apaname,self.Apaname,"sqrt(Apa2_"+self.name+")",RooArgList(self.Apa2))
        self.Ape = RooFormulaVar(self.Apename,self.Apename,"sqrt(Ape2_"+self.name+")",RooArgList(self.Ape2))
        self.Asp = RooFormulaVar(self.Aspname,self.Aspname,"sqrt("+self.Asp2.GetName()+")",RooArgList(self.Asp2))
        self.Asm = RooFormulaVar(self.Asmname,self.Asmname,"sqrt("+self.Asm2.GetName()+")",RooArgList(self.Asm2))
        self.Bs = RooFormulaVar(self.Bsname,self.Bsname,"sqrt("+self.Bs2.GetName()+")",RooArgList(self.Bs2))
        self.Ass = RooFormulaVar(self.Assname,self.Assname,"sqrt("+self.Ass2.GetName()+")",RooArgList(self.Ass2))
        


    def modParamAsym(self, name, v0, v1,v2, cte = 0):
        getattr(self, name).setVal(v0)
        getattr(self, name).setMin(v0-v1)
        getattr(self, name).setMax(v0+v2)
        getattr(self, name).setConstant(cte)
        return 1

    def modParam(self, name, v0, v1, cte = 0):
        return self.modParamAsym(name, v0, v1, v1, cte)


    def CalcNorm(self):

        normP_val = self.PP_massfunc.createIntegral(RooArgSet(m1,m2)).getVal()        
        self.modParam("normP",1./normP_val,0.,kTRUE)
        
                                                        
    def make(self):


        neim = self.name

        self.norm_int = RooFormulaVar("norm_int_"+neim,"sqrt("+self.normPname+" * "+self.normSname+")",RooArgList(self.normP,self.normS))
        self.norm_int_ss = RooFormulaVar("norm_int_ss"+neim,"sqrt("+self.normPname+"*"+self.normSSname+")",RooArgList(self.normP,self.normSS))
        self.norm_int_sv_ss = RooFormulaVar("norm_int_sv_ss"+neim,"sqrt("+self.normSname+"*"+self.normSSname+")",RooArgList(self.normS,self.normSS))
        
        self.c5_th = RooFormulaVar("c5_th_"+neim,"c5_th_"+neim,self.y.GetName()+" + (-1.-"+self.c1_th.GetName()+"-"+self.c2_th.GetName()+"-"+self.c3_th.GetName()+"-"+self.c4_th.GetName()+")",RooArgList(self.y,self.c1_th,self.c2_th,self.c3_th,self.c4_th))

        accTH_coefList = RooArgList(self.c1_th, self.c2_th, self.c3_th, self.c4_th, self.c5_th)
        accPH_coefList = RooArgList(self.c1_ph, self.c2_ph, self.c3_ph)


        # Time integrated amplitudes
        self.K1 = RooFormulaVar("K1_"+neim,self.normname+"*"+self.A0name+"*"+self.A0name,RooArgList(self.A0,self.norm)) 
        self.K2 = RooFormulaVar("K2_"+neim,self.normname+"*"+self.Apaname+"*"+self.Apaname,RooArgList(self.Apa,self.norm)) 
        self.K3 = RooFormulaVar("K3_"+neim,self.normname+"*"+self.Apename+"*"+self.Apename+"*"+self.GLname+"/"+self.GHname,RooArgList(self.Ape,self.GL,self.GH,self.norm)) 
        self.K5 = RooFormulaVar("K5_"+neim,self.normname+"*"+self.A0name+"*"+self.Apaname+"*cos("+self.dpaname+")",RooArgList(self.A0,self.Apa,self.dpa,self.norm))         
        



        # Mass amplitudes

        self.M1 = MassK1("M1_"+neim,"M1_"+neim,m1,m2,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.normP)


        self.M1.forceNumInt(kTRUE)

       
        # Angular amplitudes

        
        self.f1 = AngF1("f1_"+neim,"f1_"+neim,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
        self.f2 = AngF2("f2_"+neim,"f2_"+neim,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
        self.f3 = AngF3("f3_"+neim,"f3_"+neim,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
        self.f5 = AngF5("f5_"+neim,"f5_"+neim,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
   



        self.products = [0]*4
        self.products[0] = RooProduct("K1M1f1_"+neim,"K1M1f1_"+neim,RooArgList(self.K1,self.M1,self.f1))
        self.products[1] = RooProduct("K2M2f2_"+neim,"K2M2f2_"+neim,RooArgList(self.K2,self.M1,self.f2))
        self.products[2] = RooProduct("K3M3f3_"+neim,"K3M3f3_"+neim,RooArgList(self.K3,self.M1,self.f3))
        self.products[3] = RooProduct("K5M5f5_"+neim,"K5M5f5_"+neim,RooArgList(self.K5,self.M1,self.f5))



        # Make the sum
        self.dummyParamList = RooArgList() ## 11 times 1
        self.een = RooRealVar("een","een",1.)
        for i in range(len(self.products)):
            self.dummyParamList.add(self.een)

        self.finalFuncList = RooArgList()
        self.finalFuncSet = RooArgSet()
        for i in range(len(self.products)):
            self.finalFuncList.add(self.products[i])
            self.finalFuncSet.add(self.products[i])
        

        
        #//*********************//
        #//***   Total PDF   ***//
        #//*********************//



        self.sigmodel = RooRealSumPdf("sigmodel_"+self.name, "sigmodel_"+self.name, self.finalFuncList,self.dummyParamList)




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



