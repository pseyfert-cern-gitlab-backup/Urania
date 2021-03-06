from ROOT import *
from math import *
from graph_tools import *

gROOT.ProcessLine(".x AngularPDFAcc_v3.cxx+")
gROOT.ProcessLine(".x AngularPDFNoAcc.cxx+")


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
    def __init__(self,name,acceptance = 0):

        self.name = name

        self.acc = acceptance
        
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

        
        self.c1_th1 = RooRealVar("c1_th1_"+name,"c1_th1_"+name,-1.15214e-01,-0.5,0.5)
        self.c2_th1 = RooRealVar("c2_th1_"+name,"c2_th1_"+name,-3.79288e-01,-2.,1.)
        self.c3_th1 = RooRealVar("c3_th1_"+name,"c3_th1_"+name,-5.65808e-01,-1.,1.)
        self.c4_th1 = RooRealVar("c4_th1_"+name,"c4_th1_"+name,-1.37544e-01,-0.5,1.)
        self.y_th1 = RooRealVar("y_th1_"+name,"y_th1_"+name,1.71127e-03,0.,1.)

        self.c1_th2 = RooRealVar("c1_th2_"+name,"c1_th2_"+name,-1.15214e-01,-0.5,0.5)
        self.c2_th2 = RooRealVar("c2_th2_"+name,"c2_th2_"+name,-3.79288e-01,-2.,1.)
        self.c3_th2 = RooRealVar("c3_th2_"+name,"c3_th2_"+name,-5.65808e-01,-1.,1.)
        self.c4_th2 = RooRealVar("c4_th2_"+name,"c4_th2_"+name,-1.37544e-01,-0.5,1.)
        self.y_th2 = RooRealVar("y_th2_"+name,"y_th2_"+name,1.71127e-03,0.,1.)
        
        self.c1_ph = RooRealVar("c1_ph_"+name,"c1_ph_"+name,0.,1.)#2.43356e-02)
        self.c2_ph = RooRealVar("c2_ph_"+name,"c2_ph_"+name,1.5,0.1,3)#1.67186e+00)  ### This constant cannot be 0 or 1, it appears in the denominator of the integrals!!
        self.c3_ph = RooRealVar("c3_ph_"+name,"c3_ph_"+name,0.,2*pi)
        
        self.c1_m = RooRealVar("c1_m_"+name,"c1_m_"+name,1.)
        self.c2_m = RooRealVar("c2_m_"+name,"c2_m_"+name,0.)


        # Normalization
                
        self.normname = "norm_"+self.name
        self.normPname = "normP_"+self.name
        self.normSname = "normS_"+self.name
        self.normSSname = "normSS_"+self.name
        self.normFBname = "normFB_"+self.name
        self.norm_int_name = "norm_int_"+self.name
        self.norm_int_ss_name = "norm_int_ss_"+self.name
        self.norm_int_sv_ss_name = "norm_int_sv_ss_"+self.name
        self.GLname = "GL_"+self.name
        self.GHname = "GH_"+self.name
        

        self.norm = RooRealVar("norm_"+name,"norm_"+name,1)
        self.normP = RooRealVar(self.normPname,self.normPname,1e-10/ 1.77453790754)
        self.normS = RooRealVar(self.normSname,self.normSname,1e-10/1.88751963995)
        self.normSS = RooRealVar(self.normSSname,self.normSSname,1e-10/2.00768791208)
        self.norm_fb = RooRealVar(self.normFBname,self.normFBname,1)
        self.norm_int = RooRealVar(self.norm_int_name,self.norm_int_name,sqrt(1e-10/ 1.77453790754*1e-10/1.88751963995))
        self.norm_int_ss = RooRealVar(self.norm_int_ss_name,self.norm_int_ss_name,sqrt(1e-10/ 1.77453790754*1e-10/2.00768791208))
        self.norm_int_sv_ss = RooRealVar(self.norm_int_sv_ss_name,self.norm_int_sv_ss_name,sqrt(1e-10/1.88751963995*1e-10/2.00768791208))
        



    def OwnPhys(self):
        
        self.fL = RooRealVar("fL_"+self.name,"fL_"+self.name,0.6,0.,1)#0.507,0.1, .65)
        self.fpax = RooRealVar("fpax_"+self.name,"fpax_"+self.name,0.3,0.,1.)#0.172,0.07, .45)
        self.Ap2 = RooRealVar("Ap2_"+self.name,"Ap2_"+self.name,0.1,0.,1.)#0.2,0.,1.)
        self.Ad02 = RooRealVar("Ad02_"+self.name,"Ad02_"+self.name,0.05,0.,1.)
        self.Adpa2 = RooRealVar("Adpa2_"+self.name,"Adpa2_"+self.name,0.05,0.,1.)
        self.Adpe2 = RooRealVar("Adpe2_"+self.name,"Adpe2_"+self.name,0.05,0.,1.)
        self.dpa = RooRealVar("dpa_"+self.name,"dpa_" + self.name,-2*pi,0.)
        self.dpe = RooRealVar("dpe_"+self.name,"dpe_" + self.name, 0.)#,2*pi)
        self.d0 = RooRealVar("d0_"+self.name,"d0_"+self.name,0.)
        self.ds = RooRealVar("ds_"+self.name,"ds_"+self.name, 2.24,0.,2*pi)#2.5, 1.5 , 3.5)
        self.dd0 = RooRealVar("dd0_"+self.name,"dd0_"+self.name, -0.4 ,-2*pi , 0.)
        self.ddpa = RooRealVar("ddpa_"+self.name,"ddpa_"+self.name, -0.4 ,-pi , pi)
        self.ddpe = RooRealVar("ddpe_"+self.name,"ddpe_"+self.name, -0.4 ,-pi,pi)
        self.CreateAmplitudes()


    def CopyNorm(self,other):
        self.norm = other.norm
        self.normP = other.normP
        self.normS = other.normS
        self.normSS = other.normSS
        self.norm_fb = other.norm_fb
        self.norm_int = other.norm_int
        self.norm_int_ss = other.norm_int_ss
        self.norm_int_sv_ss = other.norm_int_sv_ss

        self.normname = self.norm.GetName()
        self.normPname = self.normP.GetName()
        self.normSname = self.normS.GetName()
        self.normSSname = self.normSS.GetName()
        self.normFBname = self.norm_fb.GetName()
        self.norm_int_name = other.norm_int_name 
        self.norm_int_ss_name = other.norm_int_ss_name
        self.norm_int_sv_ss_name = other.norm_int_sv_ss_name
                
 

    def CopyAcceptance(self,other):
        self.c1_th1 = other.c1_th1
        self.c2_th1 = other.c2_th1
        self.c3_th1 = other.c3_th1
        self.c4_th1 = other.c4_th1
        self.y_th1 = other.y_th1
        self.c1_th2 = other.c1_th2
        self.c2_th2 = other.c2_th2
        self.c3_th2 = other.c3_th2
        self.c4_th2 = other.c4_th2
        self.y_th2 = other.y_th2
        self.c1_ph = other.c1_ph
        self.c2_ph = other.c2_ph
        self.c3_ph = other.c3_ph
        


    def CopySwave(self,other):
        
        self.fL = RooRealVar("fL_"+self.name,"fL_"+self.name,0.507,0.1, .65)
        self.fpax = RooRealVar("fpax_"+self.name,"fpax_"+self.name,0.172,0.07, .45)
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
        self.Asname = "As_"+self.name
        self.Ad0name = "Ad0_"+self.name
        self.Adpaname = "Adpa_"+self.name
        self.Adpename = "Adpe_"+self.name
        self.dsname = self.ds.GetName()
        self.dd0name = self.dd0.GetName()
        self.dpaname = self.dpa.GetName()
        self.dpename = self.dpe.GetName()
        self.ddpaname = self.ddpa.GetName
        self.ddpename = self.ddpe.GetName

#         self.Ap = RooFormulaVar("Ap_"+self.name,"Ap_"+self.name,"sqrt(1-"+self.As2.GetName()+"-"+self.Ad02.GetName()+"-"+self.Adpa2.GetName()+"-"+self.Adpe2.GetName()+")",RooArgList(self.As2,self.Ad02,self.Adpa2,self.Adpe2))

        self.Ap = RooFormulaVar("Ap_"+self.name,"Ap_"+self.name,"sqrt(Ap2_"+self.name+")",RooArgList(self.Ap2))

        self.A02 = RooFormulaVar("A02_"+self.name,"A02_"+self.name,"fL_"+self.name+"*Ap_"+self.name+"*Ap_"+self.name,RooArgList(self.fL,self.Ap))

        self.fpa = RooFormulaVar("fpa_"+self.name,"fpa_"+self.name,"(1-fL_"+self.name+")*fpax_"+self.name,RooArgList(self.fL,self.fpax))

        self.Apa2 = RooFormulaVar("Apa2_"+self.name,"Apa2_"+self.name,"fpa_"+self.name+"*Ap_"+self.name+"*Ap_"+self.name,RooArgList(self.fpa,self.Ap))


        self.fpe = RooFormulaVar("fpe_"+self.name,"fpe_"+self.name,"1-fL_"+self.name+"-fpa_"+self.name,RooArgList(self.fL,self.fpa))
       
        
        self.Ape2 = RooFormulaVar("Ape2_"+self.name,"Ape2_"+self.name,"fpe_"+self.name+"*Ap_"+self.name+"*Ap_"+self.name,RooArgList(self.fpe,self.Ap))


        
#         self.A02 = RooFormulaVar("A02_"+self.name,"A02_"+self.name,"fL_"+self.name+"*(1-"+self.As2.GetName()+"-"+self.Ad02.GetName()+"-"+self.Adpa2.GetName()+"-"+self.Adpe2.GetName()+")",
#                                  RooArgList(self.fL, self.As2, self.Ad02, self.Adpa2, self.Adpe2))

#         self.Apa2 = RooFormulaVar("Apa2_"+self.name,"Apa2_"+self.name,"fpa_"+self.name+"*(1-"+self.As2.GetName()+"-"+self.Ad02.GetName()+"-"+self.Adpa2.GetName()+"-"+self.Adpe2.GetName()+")",
#                                   RooArgList(self.fpa,self.As2, self.Ad02, self.Adpa2, self.Adpe2))
        
#         self.Ape = RooFormulaVar("Ape_"+self.name,"Ape_"+self.name,"sqrt(1-A02_"+self.name+"-Apa2_"+self.name+"-"+self.As2.GetName()+"-"+self.Ad02.GetName()+"-"+self.Adpa2.GetName()+"-"+self.Adpe2.GetName()+")",RooArgList(self.A02,self.Apa2,self.As2,self.Ad02,self.Adpa2, self.Adpe2))


        self.As2 = RooFormulaVar("As2_"+self.name,"As2_"+self.name,"1-"+self.Ap2.GetName()+"-"+self.Ad02.GetName()+"-"+self.Adpa2.GetName()+"-"+self.Adpe2.GetName(),RooArgList(self.Ap2,self.Ad02,self.Adpa2,self.Adpe2))

        
        self.A0 = RooFormulaVar(self.A0name,self.A0name,"sqrt(A02_"+self.name+")",RooArgList(self.A02))
        self.Apa = RooFormulaVar(self.Apaname,self.Apaname,"sqrt(Apa2_"+self.name+")",RooArgList(self.Apa2))
#         self.Ape2 = RooFormulaVar(self.Apename,self.Apename,"Ape_"+self.name+"*Ape_"+self.name,RooArgList(self.Ape))
        self.Ape = RooFormulaVar("Ape_"+self.name,"Ape_"+self.name,"sqrt(Ape2_"+self.name+")",RooArgList(self.Ape2))
        self.As = RooFormulaVar(self.Asname,self.Asname,"sqrt("+self.As2.GetName()+")",RooArgList(self.As2))
        self.Ad0 = RooFormulaVar(self.Ad0name,self.Ad0name,"sqrt("+self.Ad02.GetName()+")",RooArgList(self.Ad02))
        self.Adpa = RooFormulaVar(self.Adpaname,self.Adpaname,"sqrt("+self.Adpa2.GetName()+")",RooArgList(self.Adpa2))
        self.Adpe = RooFormulaVar(self.Adpename,self.Adpename,"sqrt("+self.Adpe2.GetName()+")",RooArgList(self.Adpe2))
        

    def modParamAsym(self, name, v0, v1,v2, cte = 0):
        getattr(self, name).setVal(v0)
        getattr(self, name).setMin(v0-v1)
        getattr(self, name).setMax(v0+v2)
        getattr(self, name).setConstant(cte)
        return 1

    def modParam(self, name, v0, v1, cte = 0):
        return self.modParamAsym(name, v0, v1, v1, cte)



    def make(self):


        neim = self.name


        if self.acc:

            self.sigmodel = AngularPDFAcc_v3("sigmodel"+neim,"sigmodel"+neim,CTh2,CTh1,Phi,self.Adpe,self.Adpa,self.Ad0,self.A0,self.Apa,self.Ape,self.As,self.ddpe,self.ddpa,self.dd0,self.dpa,self.dpe,self.ds,self.c1_th1,self.c2_th1,self.c3_th1,self.c4_th1,self.y_th1,self.c1_th2,self.c2_th2,self.c3_th2,self.c4_th2,self.y_th2 )

#             self.sigmodel.forceNumInt(1)
        else:

            self.sigmodel = AngularPDFNoAcc("sigmodel"+neim,"sigmodel"+neim,CTh2,CTh1,Phi,self.Adpe,self.Adpa,self.Ad0,self.A0,self.Apa,self.Ape,self.As,self.ddpe,self.ddpa,self.dd0,self.dpa,self.dpe,self.ds)




        
#         self.c5_th = RooFormulaVar("c5_th_"+neim,"c5_th_"+neim,self.y.GetName()+" + (-1.-"+self.c1_th.GetName()+"-"+self.c2_th.GetName()+"-"+self.c3_th.GetName()+"-"+self.c4_th.GetName()+")",RooArgList(self.y,self.c1_th,self.c2_th,self.c3_th,self.c4_th))

#         accTH_coefList = RooArgList(self.c1_th, self.c2_th, self.c3_th, self.c4_th, self.c5_th)
#         accPH_coefList = RooArgList(self.c1_ph, self.c2_ph, self.c3_ph)


#         # Time integrated amplitudes
#         self.K1 = RooFormulaVar("K1_"+neim,self.normname+"*"+self.A0name+"*"+self.A0name,RooArgList(self.A0,self.norm)) 
#         self.K2 = RooFormulaVar("K2_"+neim,self.normname+"*"+self.Apaname+"*"+self.Apaname,RooArgList(self.Apa,self.norm)) 
#         self.K3 = RooFormulaVar("K3_"+neim,self.normname+"*"+self.Apename+"*"+self.Apename+"*"+self.GLname+"/"+self.GHname,RooArgList(self.Ape,self.GL,self.GH,self.norm)) 
#         self.K5 = RooFormulaVar("K5_"+neim,self.normname+"*"+self.A0name+"*"+self.Apaname+"*cos("+self.dpaname+")",RooArgList(self.A0,self.Apa,self.dpa,self.norm))         
        
#         ## K4 & K6 & K16 are zero if no CPV is assumed

#         self.K7 = RooFormulaVar("K7_"+neim,self.normname+"*"+self.GLname,RooArgList(self.norm,self.GL))         
#         self.K8 = RooFormulaVar("K8_"+neim,self.normname,RooArgList(self.norm))
#         self.K9 = RooFormulaVar("K9_"+neim,self.normname,RooArgList(self.norm))
#         self.K10 = RooFormulaVar("K10_"+neim,self.normname+"*"+self.GLname+"/"+self.GHname,RooArgList(self.GL,self.GH,self.norm))
#         self.K10b = RooFormulaVar("K10b_"+neim,self.normname+"*(-1.)"+"*"+self.GLname+"/"+self.GHname,RooArgList(self.GL,self.GH,self.norm))
#         self.K11 = RooFormulaVar("K11_"+neim,self.normname,RooArgList(self.norm))
#         self.K13 = RooFormulaVar("K13_"+neim,self.normname+"*"+self.Assname+"*"+self.Assname,RooArgList(self.norm,self.Ass))
#         self.K14 = RooFormulaVar("K14_"+neim,self.normname,RooArgList(self.norm))
#         self.K15 = RooFormulaVar("K15_"+neim,self.normname,RooArgList(self.norm))
#         self.KFB = RooFormulaVar("KFB_"+neim,self.normname+"*"+self.Bsname+"*"+self.Bsname,RooArgList(self.norm,self.Bs))


#         self.massAcc_coefList = RooArgList(self.c1_m,self.c2_m)


#         # Mass amplitudes


#         self.M1 = RooFormulaVar("M1_"+neim,"M1_"+neim,self.normP.GetName()
#                                 ,RooArgList(self.normP))

#         self.M7 = RooFormulaVar("M7_"+neim,"M7_"+neim,self.normS.GetName()+"*0.5*("+self.Asp2.GetName()+"/"+self.GHname+"+"+self.Asm2.GetName()+"/"+self.GLname+")"
#                                 ,RooArgList(self.normS,self.Asp2,self.Asm2,self.GH,self.GL))

#         self.M7_int = RooFormulaVar("M7_int_"+neim,"M7_int_"+neim,self.normS.GetName()+"*0.5*("+self.Asp2.GetName()+"/"+self.GHname+"-"+self.Asm2.GetName()+"/"+self.GLname+")"
#                                     ,RooArgList(self.normS,self.Asp2,self.Asm2,self.GH,self.GL))

#         self.M8 = RooFormulaVar("M8_"+neim,"M8_"+neim,self.norm_int.GetName()+"*"+self.A0name+"*"+self.Asmname+"*cos("+self.dsm.GetName()+")"
#                                 ,RooArgList(self.norm_int,self.A0,self.Asm,self.dsm))

#         self.M9 = RooFormulaVar("M9_"+neim,"M9_"+neim,self.norm_int.GetName()+"*"+self.Apaname+"*"+self.Asmname+"*cos("+self.dsm.GetName()+"-"+self.dpa.GetName()+")"
#                                 ,RooArgList(self.norm_int,self.Apa,self.Asm,self.dsm,self.dpa))

#         self.M10 = RooFormulaVar("M10_"+neim,"M10_"+neim,self.norm_int.GetName()+"*"+self.Apename+"*"+self.Aspname+"*sin("+self.dsp.GetName()+"-"+self.dpe.GetName()+")"
#                                  ,RooArgList(self.norm_int,self.Ape,self.Asp,self.dsp,self.dpe))


#         self.M11 = RooFormulaVar("M11_"+neim,"M11_"+neim,self.norm_int_sv_ss.GetName()+"*"+self.Assname+"*"+self.Asmname+"*cos("+self.dsm.GetName()+"-"+self.dss.GetName()+")"
#                                  ,RooArgList(self.norm_int_sv_ss,self.Ass,self.Asm,self.dsm,self.dss))


#         self.M13 = RooFormulaVar("M13_"+neim,"M13_"+neim,self.normSS.GetName()
#                                  ,RooArgList(self.normSS))
        
#         self.M14 = RooFormulaVar("M14_"+neim,"M14_"+neim,self.norm_int_ss.GetName()+"*"+self.Assname+"*"+self.A0name+"*cos("+self.dss.GetName()+")"
#                                  ,RooArgList(self.norm_int_ss,self.Ass,self.A0,self.dss))

#         self.M15 = RooFormulaVar("M15_"+neim,"M15_"+neim,self.norm_int_ss.GetName()+"*"+self.Assname+"*"+self.Apaname+"*cos("+self.dss.GetName()+"-"+self.dpa.GetName()+")"
#                                  ,RooArgList(self.norm_int_ss,self.Ass,self.Apa,self.dss,self.dpa))


#         self.MFB = RooFormulaVar("MFB_"+neim,"MFB_"+neim,self.norm_fb.GetName(),RooArgList(self.norm_fb))




# #         self.M1 = MassK1("M1_"+neim,"M1_"+neim,m1,m2,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.normP)

# #         self.M7s    = MassK7(    "M7s_"+neim   ,"M7s_"+neim   ,m1,m2,self.Asp,self.dsp,self.Asm,self.dsm,self.Gs,self.DGs
# #                                  ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.normS)
        
# #         self.M7sbar = MassK7(    "M7sbar_"+neim,"M7sbar_"+neim,m2,m1,self.Asp,self.dsp,self.Asm,self.dsm,self.Gs,self.DGs
# #                                  ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.normS)
        
# #         self.M7_int = MassK7_int("M7_int_"+neim,"M7_int_"+neim,m1,m2,self.Asp,self.dsp,self.Asm,self.dsm,self.Gs,self.DGs
# #                                  ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.normS)

# #         self.M8s    = MassK8("M8s_"+neim    ,"M8s_"+neim    ,m1,m2,self.Asp,self.dsp,self.Asm,self.dsm,self.A0,self.d0
# #                              ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.norm_int)
        
# #         self.M8sbar = MassK8("M8sbar_"+neim ,"M8sbar_"+neim ,m2,m1,self.Asp,self.dsp,self.Asm,self.dsm,self.A0,self.d0
# #                              ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.norm_int)

# #         self.M9s    = MassK9("M9s_"+neim   ,"M9s_"+neim   ,m1,m2,self.Asp,self.dsp,self.Asm,self.dsm,self.Apa,self.dpa
# #                              ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.norm_int)
        
# #         self.M9sbar = MassK9("M9sbar_"+neim,"M9sbar_"+neim,m2,m1,self.Asp,self.dsp,self.Asm,self.dsm,self.Apa,self.dpa
# #                              ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.norm_int)

# #         self.M10s    = MassK10("M10s_"+neim   ,"M10s_"+neim   ,m1,m2,self.Asp,self.dsp,self.Asm,self.dsm,self.Ape,self.dpe
# #                                ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.norm_int)
        
# #         self.M10sbar = MassK10("M10sbar_"+neim,"M10sbar_"+neim,m2,m1,self.Asp,self.dsp,self.Asm,self.dsm,self.Ape,self.dpe
# #                                ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.norm_int)


# #         self.M11s    = MassK11("M11s_"+neim   ,"M11s_"+neim   ,m1,m2,self.Asp,self.dsp,self.Asm,self.dsm,self.Ass,self.dss
# #                                ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.norm_int_sv_ss)
        
# #         self.M11sbar = MassK11("M11sbar_"+neim,"M11sbar_"+neim,m2,m1,self.Asp,self.dsp,self.Asm,self.dsm,self.Ass,self.dss
# #                                ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.norm_int_sv_ss)

# #         self.M13    = MassK13("M13_"+neim   ,"M13_"+neim   ,m1,m2,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.normSS)

# #         self.M14    = MassK14("M14_"+neim   ,"M14_"+neim   ,m1,m2,self.Ass,self.dss,self.A0,self.d0 ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.norm_int_ss)

# #         self.M15    = MassK15("M15_"+neim   ,"M15_"+neim   ,m1,m2,self.Ass,self.dss,self.Apa,self.dpa ,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.norm_int_ss)


# #         self.MFB = FourB_Mass("MFB_"+neim, "MFB_"+neim,m1,m2,self.m_kst,self.m_kst0,self.g_kst,self.g_kst0,self.MBs,self.massAcc_coefList,self.norm_fb,self.MBs)




       
#         # Angular amplitudes

        
#         self.f1 = AngF1("f1_"+neim,"f1_"+neim,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
#         self.f2 = AngF2("f2_"+neim,"f2_"+neim,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
#         self.f3 = AngF3("f3_"+neim,"f3_"+neim,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
#         self.f5 = AngF5("f5_"+neim,"f5_"+neim,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
        
#         self.f7s    = AngF7(    "f7s_"+neim   ,"f7s_"+neim   ,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
#         self.f7sbar = AngF7(    "f7sbar_"+neim,"f7sbar_"+neim,CTh2,CTh1,Phi,accTH_coefList,accPH_coefList)
#         self.f7_int = AngF7_int("f7_int_"+neim,"f7_int_"+neim,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)

#         self.f8s    = AngF8("f8s_"+neim   ,"f8s_"+neim   ,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
#         self.f8sbar = AngF8("f8sbar_"+neim,"f8sbar_"+neim,CTh2,CTh1,Phi,accTH_coefList,accPH_coefList)

#         self.f9s    = AngF9("f9s_"+neim   ,"f9s_"+neim   ,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
#         self.f9sbar = AngF9("f9sbar_"+neim,"f9sbar_"+neim,CTh2,CTh1,Phi,accTH_coefList,accPH_coefList)

#         self.f10s    = AngF10("f10s_"+neim   ,"f10s_"+neim   ,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
#         self.f10sbar = AngF10("f10sbar_"+neim,"f10sbar_"+neim,CTh2,CTh1,Phi,accTH_coefList,accPH_coefList)

#         self.f11s    = AngF11("f11s_"+neim   ,"f11s_"+neim   ,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)
#         self.f11sbar    = AngF11("f11sbar_"+neim   ,"f11sbar_"+neim   ,CTh2,CTh1,Phi,accTH_coefList,accPH_coefList)


#         self.f13    = AngF13("f13_"+neim   ,"f13_"+neim   ,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)

#         self.f14    = AngF14("f14_"+neim   ,"f14_"+neim   ,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)

#         self.f15    = AngF15("f15_"+neim   ,"f15_"+neim   ,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)

        
#         self.fFB = FourB("fFB_"+neim, "fFB_"+neim,CTh1,CTh2,Phi,accTH_coefList,accPH_coefList)


# #         self.f1.forceNumInt(1)
# #         self.f2.forceNumInt(1)
# #         self.f3.forceNumInt(1)
# #         self.f5.forceNumInt(1)
# #         self.f7s.forceNumInt(1)
# #         self.f7sbar.forceNumInt(1)
# #         self.f7_int.forceNumInt(1)
# #         self.f8s.forceNumInt(1)
# #         self.f8sbar.forceNumInt(1)
# #         self.f9s.forceNumInt(1)
# #         self.f9sbar.forceNumInt(1)
# #         self.f10s.forceNumInt(1)
# #         self.f10sbar.forceNumInt(1)
# #         self.f11s.forceNumInt(1)
# #         self.f11sbar.forceNumInt(1)
# #         self.f13.forceNumInt(1)
# #         self.f14.forceNumInt(1)
# #         self.f15.forceNumInt(1)
# #         self.fFB.forceNumInt(1)



#         self.products = [0]*19

#         self.products[0] = RooProduct("K1M1f1_"+neim,"K1M1f1_"+neim,RooArgList(self.K1,self.M1,self.f1))
#         self.products[1] = RooProduct("K2M2f2_"+neim,"K2M2f2_"+neim,RooArgList(self.K2,self.M1,self.f2))
#         self.products[2] = RooProduct("K3M3f3_"+neim,"K3M3f3_"+neim,RooArgList(self.K3,self.M1,self.f3))
#         self.products[3] = RooProduct("K5M5f5_"+neim,"K5M5f5_"+neim,RooArgList(self.K5,self.M1,self.f5))
        
#         self.products[4] = RooProduct("K7M7sf7s_"+neim,"K7sM7sf7s_"+neim,RooArgList(self.K7,self.M7,self.f7s))
#         self.products[5] = RooProduct("K7M7sbf7sb_"+neim,"K7M7sbf7sb_"+neim,RooArgList(self.K7,self.M7,self.f7sbar))
#         self.products[6] = RooProduct("K7M7intf7int_"+neim,"K7M7intf7int_"+neim,RooArgList(self.K7,self.M7_int,self.f7_int))

#         self.products[7] = RooProduct("K8M8sf8s_"+neim,"K8M8sf8s_"+neim,RooArgList(self.K8,self.M8,self.f8s))
#         self.products[8] = RooProduct("K8M8sbf8sb_"+neim,"K8M8sbf8sb_"+neim,RooArgList(self.K8,self.M8,self.f8sbar))


#         self.products[9] = RooProduct("K9M9sf9s_"+neim,"K9M9sf9s_"+neim,RooArgList(self.K9,self.M9,self.f9s))
#         self.products[10] = RooProduct("K9M9sbf9sb_"+neim,"K9M9sbf9sb_"+neim,RooArgList(self.K9,self.M9,self.f9sbar))

#         self.products[11] = RooProduct("K10M10sf10s_"+neim,"K10M10sf10s_"+neim,RooArgList(self.K10,self.M10,self.f10s))
#         self.products[12] = RooProduct("K10M10sbf10sb_"+neim,"K10M10sbf10sb_"+neim,RooArgList(self.K10b,self.M10,self.f10sbar))

#         self.products[13] = RooProduct("K11M11sf11s_"+neim,"K11M11sf11s_"+neim,RooArgList(self.K11,self.M11,self.f11s))
#         self.products[14] = RooProduct("K11M11sbf11sb_"+neim,"K11M11sbf11sb_"+neim,RooArgList(self.K11,self.M11,self.f11sbar))


#         self.products[15] = RooProduct("K13M13f13_"+neim,"K13M13f13_"+neim,RooArgList(self.K13,self.M13,self.f13))

#         self.products[16] = RooProduct("K14M14f14_"+neim,"K14M14f14_"+neim,RooArgList(self.K14,self.M14,self.f7_int))

#         self.products[17] = RooProduct("K15M15f15_"+neim,"K15M15f15_"+neim,RooArgList(self.K15,self.M15,self.f15))


#         self.products[18] = RooProduct("KFBMFBfFB_"+neim,"KFBMFBfFB_"+neim,RooArgList(self.KFB,self.MFB,self.fFB))


#         # Make the sum
#         self.dummyParamList = RooArgList() ## 11 times 1
#         self.een = RooRealVar("een","een",1.)
#         for i in range(len(self.products)):
#             self.dummyParamList.add(self.een)

#         self.finalFuncList = RooArgList()
#         self.finalFuncSet = RooArgSet()
#         for i in range(len(self.products)):
#             self.finalFuncList.add(self.products[i])
#             self.finalFuncSet.add(self.products[i])
        

        
#         #//*********************//
#         #//***   Total PDF   ***//
#         #//*********************//



#         self.sigmodel = RooRealSumPdf("sigmodel_"+self.name, "sigmodel_"+self.name, self.finalFuncList,self.dummyParamList)

#         self.signalforFB = RooAddition("signalforFB_"+self.name,"signalforFB_"+self.name,self.finalFuncList)
#         self.Nps = []
#         self.Nms = []
#         self.Ntots = []
#         self.Asyms = []

        
#         self.PWFuncList = RooArgList(self.products[0],self.products[1],self.products[2],self.products[3])
#         self.SWFuncList = RooArgList(self.products[4],self.products[5],self.products[6])
#         self.SW_intFuncList = RooArgList(self.products[7],self.products[8],self.products[9],self.products[10],self.products[11],self.products[12])

#         self.Pwave = RooAddition("Pwave_"+neim, "Pwave_"+neim,self.PWFuncList)
#         self.Swave = RooAddition("Swave_"+neim, "Swave_"+neim,self.SWFuncList)
#         self.Swave_int = RooAddition("Swave_int_"+neim, "Swave_int_"+neim,self.SW_intFuncList)



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



