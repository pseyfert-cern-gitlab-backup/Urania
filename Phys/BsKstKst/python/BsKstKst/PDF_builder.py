from ROOT import *
from math import *
from graph_tools import *

gROOT.ProcessLine(".L AngAbsFunc.cxx+")
gROOT.ProcessLine(".x AngF1.cxx+")
gROOT.ProcessLine(".x AngF2.cxx+")
gROOT.ProcessLine(".x AngF3.cxx+")
gROOT.ProcessLine(".x AngF5.cxx+")
gROOT.ProcessLine(".x AngF7.cxx+")
gROOT.ProcessLine(".x AngF7_int.cxx+")
gROOT.ProcessLine(".x AngF8.cxx+")
gROOT.ProcessLine(".x AngF9.cxx+")
gROOT.ProcessLine(".x AngF10.cxx+")
gROOT.ProcessLine(".x AngF11.cxx+")
gROOT.ProcessLine(".x AngF13.cxx+")
gROOT.ProcessLine(".x AngF14.cxx+")
gROOT.ProcessLine(".x AngF15.cxx+")
gROOT.ProcessLine(".L MassAbsFunc.cxx+")
gROOT.ProcessLine(".x MassK1.cxx+")
gROOT.ProcessLine(".x MassK7.cxx++")
gROOT.ProcessLine(".x MassK7_int.cxx+")
gROOT.ProcessLine(".x MassK8.cxx+")
gROOT.ProcessLine(".x MassK9.cxx+")
gROOT.ProcessLine(".x MassK10.cxx+")
gROOT.ProcessLine(".x MassK11.cxx+")
gROOT.ProcessLine(".x MassK13.cxx+")
gROOT.ProcessLine(".x MassK14.cxx+")
gROOT.ProcessLine(".x MassK15.cxx+")


gROOT.ProcessLine(".x FourB.cxx+")
gROOT.ProcessLine(".x FourB_Mass.cxx+")



## Variables
CTh1 = RooRealVar("CosTheta1","CosTheta1",-1.,1.)
CTh2 = RooRealVar("CosTheta2","CosTheta2",-1.,1.)
Phi = RooRealVar("Phi","Phi",0,2*pi)#2*pi*(1.-0.1))
m1 = RooRealVar("P1_mass","P1_mass",896-150,896+150)
m2 = RooRealVar("P2_mass","P2_mass",896-150,896+150)



## Constants
MBs = RooRealVar("MBs","MBs",5366.3)
DGs = RooRealVar("DGs","DGs",0.062)
Gs = RooRealVar("Gs","Gs",0.6793)
GL = RooFormulaVar("GL","GL","Gs + DGs/2.",RooArgList(Gs,DGs))
GH = RooFormulaVar("GH","GH","Gs - DGs/2.",RooArgList(Gs,DGs))


# m_kst.setVal(8.97538e+02)
# g_kst.setVal(5.04266e+01)

s=10

m_kst = RooRealVar("m_kst","m_kst",890.,910.)
m_kst0 = RooRealVar("m_kst0","m_kst0",1435.)#-50*s, 1425.+50*s)
g_kst = RooRealVar("g_kst","g_kst",48.7-0.8*s, 48.7+0.8*s)
g_kst0 = RooRealVar("g_kst0","g_kst0",279)#270,320)#-80.*s, 270.+80*s)


# Mass acceptance

c1_m = RooRealVar("c1_m","c1_m",1.)#-0.766546)#-1.31998)#-0.766546)
c2_m = RooRealVar("c2_m","c2_m",0.)#0.00196787)#0.00257292)#0.00196787)


## Parameters of interest
        
d0 = RooRealVar("d0","d0",0)
dpa = RooRealVar("dpa","dpa",5,0,2*pi)
dpe = RooRealVar("dpe","dpe",3,0.,2*pi)


Asp2 = RooRealVar("Asp2","Asp2",0.2,0.,1.)
Asm2 = RooRealVar("Asm2","Asm2",0.4,0.,1.)
dsp = RooRealVar("dsp","dsp",2.5,0.,2*pi)#-pi,pi)
dsm = RooRealVar("dsm","dsm",2.,0.,2*pi)

Ass2 = RooRealVar("Ass2","Ass2",0.001,0.,0.5)       
dss = RooRealVar("dss","dss",-pi,pi)#0.,2*pi)


Af2 = RooFormulaVar("Af2","Af2","0.5*(Asp2 + Asm2 + 2*sqrt(Asp2)*sqrt(Asm2)*cos(dsp-dsm))",RooArgList(Asp2,Asm2,dsp,dsm))
Ag2 = RooFormulaVar("Ag2","Ag2","0.5*(Asp2 + Asm2 - 2*sqrt(Asp2)*sqrt(Asm2)*cos(dsp-dsm))",RooArgList(Asp2,Asm2,dsp,dsm))
df = RooFormulaVar("df","df","atan((sqrt(Asp2)*sin(dsp) + sqrt(Asm2)*sin(dsm))/(sqrt(Asp2)*cos(dsp) + sqrt(Asm2)*cos(dsm)))",RooArgList(Asp2,Asm2,dsp,dsm))
dg = RooFormulaVar("dg","dg","atan((sqrt(Asp2)*sin(dsp) - sqrt(Asm2)*sin(dsm))/(sqrt(Asp2)*cos(dsp) - sqrt(Asm2)*cos(dsm)))",RooArgList(Asp2,Asm2,dsp,dsm))

Bs2 = RooRealVar("Bs2","Bs2",.05,0.,0.5)
        

fL = RooRealVar("fL","fL",0.2,0.,0.8)
fpa = RooRealVar("fpa","fpa",0.3,0.,0.8)

A02 = RooFormulaVar("A02","A02","fL*(1-Asp2-Asm2-Ass2-Bs2)",RooArgList(fL, Asp2, Asm2, Ass2, Bs2))
Apa2 = RooFormulaVar("Apa2","Apa2","fpa*(1-Asp2-Asm2-Ass2-Bs2)",RooArgList(fpa, Asp2, Asm2, Ass2, Bs2))        
Ape = RooFormulaVar("Ape","Ape","sqrt(1-A02-Apa2-Asp2-Asm2-Ass2-Bs2)",RooArgList(A02,Apa2,Asp2,Asm2,Ass2, Bs2))

A0 = RooFormulaVar("A0","A0","sqrt(A02)",RooArgList(A02))
Apa = RooFormulaVar("Apa","Apa","sqrt(Apa2)",RooArgList(Apa2))
Asp = RooFormulaVar("Asp","Asp","sqrt(Asp2)",RooArgList(Asp2))
Asm = RooFormulaVar("Asm","Asm","sqrt(Asm2)",RooArgList(Asm2))
Ape2 = RooFormulaVar("Ape2","Ape2","Ape*Ape",RooArgList(Ape))
Ass = RooFormulaVar("Ass","Ass","sqrt(Ass2)",RooArgList(Ass2))

Bs = RooFormulaVar("Bs","Bs","sqrt(Bs2)",RooArgList(Bs2))


massAcc_coefList = RooArgList(c1_m,c2_m)
norm = RooRealVar("norm","norm",1.)
normP = RooRealVar("normP","normP",1./17760466023.4)
normS = RooRealVar("normS","normS",1./18883218420.4)
norm_ss = RooRealVar("normSS","normSS",1./20076879120.8)
norm_int = RooFormulaVar("norm_int","sqrt(normP*normS)",RooArgList(normP,normS))
norm_int_ss = RooFormulaVar("norm_int_ss","sqrt(normP*normSS)",RooArgList(normP,norm_ss))
norm_int_sv_ss = RooFormulaVar("norm_int_sv_ss","sqrt(normS*normSS)",RooArgList(normS,norm_ss))
norm_fb = RooRealVar("norm_fb","norm_fb",1.)
 
class AngularPDF:
    def __init__(self,name,acc2D):

        self.name = name


        # Factores "temporales"

        self.K1 = RooFormulaVar("K1_"+name,"A0*A0",RooArgList(A0)) 
        self.K2 = RooFormulaVar("K2_"+name,"Apa*Apa",RooArgList(Apa)) 
        self.K3 = RooFormulaVar("K3_"+name,"Ape*Ape*GL/GH",RooArgList(Ape,GH,GL)) 
        self.K5 = RooFormulaVar("K5_"+name,"A0*Apa*cos(dpa)",RooArgList(A0,Apa,dpa))
        
        ## K4 & K6 & K16 are zero if no CPV is assumed

        self.K7 = RooFormulaVar("K7_"+name,"1.*GL/GH",RooArgList(GH,GL))
        self.K7b = RooFormulaVar("K7b_"+name,"1.*GL/GH",RooArgList(GH,GL))
        self.K7_int = RooFormulaVar("K7_int_"+name,"1.*GL/GH",RooArgList(GH,GL))

        self.K8 = RooFormulaVar("K8_"+name,"1.",RooArgList())
        self.K8b = RooFormulaVar("K8b_"+name,"1.",RooArgList())
        
        self.K9 = RooFormulaVar("K9_"+name,"1.",RooArgList())
        self.K9b = RooFormulaVar("K9b_"+name,"1.",RooArgList())

        self.K10 = RooFormulaVar("K10_"+name,"1.*GL/GH",RooArgList(GH,GL))
        self.K10b = RooFormulaVar("K10b_"+name,"-1.*GL/GH",RooArgList(GH,GL))

        self.K11 = RooFormulaVar("K11_"+name,"1.",RooArgList())
        self.K11b = RooFormulaVar("K11b_"+name,"1.",RooArgList())

        self.K13 = RooFormulaVar("K13_"+name,"Ass2",RooArgList(Ass2))

        self.K14 = RooFormulaVar("K14_"+name,"1.",RooArgList())

        self.K15 = RooFormulaVar("K15_"+name,"1.",RooArgList())


        self.KFB = RooFormulaVar("KFB_"+name,"Bs2",RooArgList(Bs2))




        # Mass amplitudes

        
        self.M1 = MassK1("M1_"+name,"M1_"+name,m1,m2,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,normP)

        self.M7s    = MassK7(    "M7s_"+name   ,"M7s_"+name   ,m1,m2,Asp,dsp,Asm,dsm
                                 ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,normS)
        
        self.M7sbar = MassK7(    "M7sbar_"+name,"M7sbar_"+name,m2,m1,Asp,dsp,Asm,dsm
                                 ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,normS)
        
        self.M7_int = MassK7_int("M7_int_"+name,"M7_int_"+name,m1,m2,Asp,dsp,Asm,dsm
                                 ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,normS)

        self.M8s    = MassK8("M8s_"+name    ,"M8s_"+name    ,m1,m2,Asp,dsp,Asm,dsm,A0,d0
                             ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,norm_int)
        
        self.M8sbar = MassK8("M8sbar_"+name ,"M8sbar_"+name ,m2,m1,Asp,dsp,Asm,dsm,A0,d0
                             ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,norm_int)

        self.M9s    = MassK9("M9s_"+name   ,"M9s_"+name   ,m1,m2,Asp,dsp,Asm,dsm,Apa,dpa
                             ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,norm_int)
        
        self.M9sbar = MassK9("M9sbar_"+name,"M9sbar_"+name,m2,m1,Asp,dsp,Asm,dsm,Apa,dpa
                             ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,norm_int)

        self.M10s    = MassK10("M10s_"+name   ,"M10s_"+name   ,m1,m2,Asp,dsp,Asm,dsm,Ape,dpe
                               ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,norm_int)
        
        self.M10sbar = MassK10("M10sbar_"+name,"M10sbar_"+name,m2,m1,Asp,dsp,Asm,dsm,Ape,dpe
                               ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,norm_int)

        self.M11s    = MassK11("M11s_"+name   ,"M11s_"+name   ,m1,m2,Asp,dsp,Asm,dsm,Ass,dss
                               ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,norm_int_sv_ss)
        
        self.M11sbar = MassK11("M11sbar_"+name,"M11sbar_"+name,m2,m1,Asp,dsp,Asm,dsm,Ass,dss
                               ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,norm_int_sv_ss)

        self.M13    = MassK13("M13_"+name   ,"M13_"+name   ,m1,m2,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,norm_ss)

        self.M14    = MassK14("M14_"+name   ,"M14_"+name   ,m1,m2,Ass,dss,A0,d0 ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,norm_int_ss)

        self.M15    = MassK15("M15_"+name   ,"M15_"+name   ,m1,m2,Ass,dss,Apa,dpa ,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,norm_int_ss)


        self.MFB = FourB_Mass("MFB_"+name, "MFB_"+name, m1,m2,m_kst,m_kst0,g_kst,g_kst0,massAcc_coefList,norm_fb,MBs)


        
        # Angular amplitudes

        
        self.f1 = AngF1("f1_"+name,"f1_"+name,CTh1,CTh2,Phi,acc2D)
        self.f2 = AngF2("f2_"+name,"f2_"+name,CTh1,CTh2,Phi,acc2D)
        self.f3 = AngF3("f3_"+name,"f3_"+name,CTh1,CTh2,Phi,acc2D)
        self.f5 = AngF5("f5_"+name,"f5_"+name,CTh1,CTh2,Phi,acc2D)
        
        self.f7s    = AngF7(    "f7s_"+name   ,"f7s_"+name   ,CTh1,CTh2,Phi,acc2D)
        self.f7sbar = AngF7(    "f7sbar_"+name,"f7sbar_"+name,CTh2,CTh1,Phi,acc2D)#self.acc2D_rot)
        self.f7_int = AngF7_int("f7_int_"+name,"f7_int_"+name,CTh1,CTh2,Phi,acc2D)

        self.f8s    = AngF8("f8s_"+name   ,"f8s_"+name   ,CTh1,CTh2,Phi,acc2D)
        self.f8sbar = AngF8("f8sbar_"+name,"f8sbar_"+name,CTh2,CTh1,Phi,acc2D)#self.acc2D_rot)

        self.f9s    = AngF9("f9s_"+name   ,"f9s_"+name   ,CTh1,CTh2,Phi,acc2D)
        self.f9sbar = AngF9("f9sbar_"+name,"f9sbar_"+name,CTh2,CTh1,Phi,acc2D)#self.acc2D_rot)

        self.f10s    = AngF10("f10s_"+name   ,"f10s_"+name   ,CTh1,CTh2,Phi,acc2D)
        self.f10sbar = AngF10("f10sbar_"+name,"f10sbar_"+name,CTh2,CTh1,Phi,acc2D)#self.acc2D_rot)

        self.f11s    = AngF11("f11s_"+name   ,"f11s_"+name   ,CTh1,CTh2,Phi,acc2D)
        self.f11sbar    = AngF11("f11sbar_"+name   ,"f11sbar_"+name   ,CTh2,CTh1,Phi,acc2D)


        self.f13    = AngF13("f13_"+name   ,"f13_"+name   ,CTh1,CTh2,Phi,acc2D)

        self.f14    = AngF14("f14_"+name   ,"f14_"+name   ,CTh1,CTh2,Phi,acc2D)

        self.f15    = AngF15("f15_"+name   ,"f15_"+name   ,CTh1,CTh2,Phi,acc2D)

        
        self.fFB = FourB("fFB_"+name, "fFB_"+name,CTh1,CTh2,Phi,acc2D)

#         self.f1.forceNumInt(1)
#         self.f2.forceNumInt(1)
#         self.f3.forceNumInt(1)
#         self.f5.forceNumInt(1)
#         self.f7s.forceNumInt(1)
#         self.f7sbar.forceNumInt(1)
#         self.f7_int.forceNumInt(1)
#         self.f8s.forceNumInt(1)
#         self.f8sbar.forceNumInt(1)
#         self.f9s.forceNumInt(1)
#         self.f9sbar.forceNumInt(1)
#         self.f10s.forceNumInt(1)
#         self.f10sbar.forceNumInt(1)
#         self.f11s.forceNumInt(1)
#         self.f11sbar.forceNumInt(1)
#         self.f13.forceNumInt(1)
#         self.f14.forceNumInt(1)
#         self.f15.forceNumInt(1)
#         self.fFB.forceNumInt(1)




        self.products = [0]*19

        self.products[0] = RooProduct("K1M1f1_"+name,"K1M1f1_"+name,RooArgList(self.K1,self.M1,self.f1))
        self.products[1] = RooProduct("K2M2f2_"+name,"K2M2f2_"+name,RooArgList(self.K2,self.M1,self.f2))
        self.products[2] = RooProduct("K3M3f3_"+name,"K3M3f3_"+name,RooArgList(self.K3,self.M1,self.f3))
        self.products[3] = RooProduct("K5M5f5_"+name,"K5M5f5_"+name,RooArgList(self.K5,self.M1,self.f5))
        
        self.products[4] = RooProduct("K7M7sf7s_"+name,"K7sM7sf7s_"+name,RooArgList(self.K7,self.M7s,self.f7s))
        self.products[5] = RooProduct("K7M7sbf7sb_"+name,"K7M7sbf7sb_"+name,RooArgList(self.K7b,self.M7sbar,self.f7sbar))
        self.products[6] = RooProduct("K7M7intf7int_"+name,"K7M7intf7int_"+name,RooArgList(self.K7_int,self.M7_int,self.f7_int))

        self.products[7] = RooProduct("K8M8sf8s_"+name,"K8M8sf8s_"+name,RooArgList(self.K8,self.M8s,self.f8s))
        self.products[8] = RooProduct("K8M8sbf8sb_"+name,"K8M8sbf8sb_"+name,RooArgList(self.K8b,self.M8sbar,self.f8sbar))


        self.products[9] = RooProduct("K9M9sf9s_"+name,"K9M9sf9s_"+name,RooArgList(self.K9,self.M9s,self.f9s))
        self.products[10] = RooProduct("K9M9sbf9sb_"+name,"K9M9sbf9sb_"+name,RooArgList(self.K9b,self.M9sbar,self.f9sbar))

        self.products[11] = RooProduct("K10M10sf10s_"+name,"K10M10sf10s_"+name,RooArgList(self.K10,self.M10s,self.f10s))
        self.products[12] = RooProduct("K10M10sbf10sb_"+name,"K10M10sbf10sb_"+name,RooArgList(self.K10b,self.M10sbar,self.f10sbar))

        self.products[13] = RooProduct("K11M11sf11s_"+name,"K11M11sf11s_"+name,RooArgList(self.K11,self.M11s,self.f11s))
        self.products[14] = RooProduct("K11M11sbf11sb_"+name,"K11M11sbf11sb_"+name,RooArgList(self.K11b,self.M11sbar,self.f11sbar))


        self.products[15] = RooProduct("K13M13f13_"+name,"K13M13f13_"+name,RooArgList(self.K13,self.M13,self.f13))

        self.products[16] = RooProduct("K14M14f14_"+name,"K14M14f14_"+name,RooArgList(self.K14,self.M14,self.f7_int))

        self.products[17] = RooProduct("K15M15f15_"+name,"K15M15f15_"+name,RooArgList(self.K15,self.M15,self.f15))


        self.products[18] = RooProduct("KFBMFBfFB_"+name,"KFBMFBfFB_"+name,RooArgList(self.KFB,self.MFB,self.fFB))



        # Make the sum
        self.dummyParamList = RooArgList() ## 11 times 1
        self.een = RooRealVar("een_"+name,"een_"+name,1.)
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



        self.sigmodel = RooRealSumPdf("sigmodel_"+name, "sigmodel_"+name, self.finalFuncList,self.dummyParamList)

                
        #self.acc_histo = RooDataHist("acc_histo_" + neim,"acc_histo_" + neim,RooArgList(self.CTh1,self.CTh2),acc2D)

        #self.acceptance = RooHistPdf("acceptance_" + neim,"acceptance_" + neim,RooArgSet(self.CTh1,self.CTh2),self.acc_histo)

        #self.acceptance = RooHistFunc("acceptance_" + neim,"acceptance_" + neim,RooArgSet(self.CTh1,self.CTh2),self.acc_histo)

        #self.sigmodel = RooProdPdf("angular " + neim,"angular " + neim,self.sigmodel_phys, self.acceptance)

        #self.sigmodel = RooEffProd("angular " + neim,"angular " + neim,self.sigmodel_phys, self.acceptance)


        #self.Background_Brais()
        self.Background("right",name)
        
        self.fbkg = RooRealVar("fbkg_"+name,"fbkg_"+name,0.062)

        self.model = RooAddPdf("model_"+name,"model_"+name,RooArgList(self.modelBKG,self.sigmodel),RooArgList(self.fbkg))

        
        self.signalforFB = RooAddition("signalforFB_"+name,"signalforFB_"+name,self.finalFuncList)
        self.Nps = []
        self.Nms = []
        self.Ntots = []
        self.Asyms = []

 
    def Background(self,sideband,name):


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
            


        else:

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

        self.BW_m1 = RooBreitWigner("BW_m1_"+name,"BW_m1_"+name,m1,self.mean,self.width)
        self.BW_m2 = RooBreitWigner("BW_m2_"+name,"BW_m2_"+name,m2,self.mean,self.width)

        #same Kst number
        
        self.P11_mass = RooRealVar("P11_mass_"+name,"P11_mass_"+name,493.667)
        self.P12_mass = RooRealVar("P12_mass_"+name,"P12_mass_"+name,139.57018)

        self.lin_m1 = RooGenericPdf("lin_m1_"+name,"exp(k1_m_"+name+" *P1_mass)*(1./(8.*pi)*sqrt(1.-2.*(P11_mass_"+name+"**2. + P12_mass_"+name+"**2.)/P1_mass**2. + (P11_mass_"+name+"**2. - P12_mass_"+name+"**2.)**2./P1_mass**4.))", RooArgList(self.k1_m , m1, self.P11_mass, self.P12_mass))
        self.lin_m2 = RooGenericPdf("lin_m2_"+name,"exp(k1_m_"+name+" *P2_mass)*(1./(8.*pi)*sqrt(1.-2.*(P11_mass_"+name+"**2. + P12_mass_"+name+"**2.)/P2_mass**2. + (P11_mass_"+name+"**2. - P12_mass_"+name+"**2.)**2./P2_mass**4.))", RooArgList(self.k1_m, m2, self.P11_mass, self.P12_mass))
        

        self.modelBKG_m1 = RooAddPdf("modelBKG_m1_"+name,"Mass modelBKG m1 "+name,self.BW_m1,self.lin_m1,self.fBW)
        self.modelBKG_m2 = RooAddPdf("modelBKG_m2_"+name,"Mass modelBKG m2 "+name,self.BW_m2,self.lin_m2,self.fBW)


        self.c5_th_bkg = RooFormulaVar("c5_th_bkg_"+name,"c5_th_bkg_"+name, "y_"+name+"-(1+c1_th_bkg_"+name+"+c2_th_bkg_"+name+"+c3_th_bkg_"+name+"+c4_th_bkg_"+name+")",RooArgList(self.y,self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg))


        self.CTh1bkg = RooPolynomial("CTh1bkg_"+name,"CTh1bkg_"+name,CTh1,RooArgList(self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg,self.c5_th_bkg))
        self.CTh2bkg = RooPolynomial("CTh2bkg_"+name,"CTh2bkg_"+name,CTh2,RooArgList(self.c1_th_bkg,self.c2_th_bkg,self.c3_th_bkg,self.c4_th_bkg,self.c5_th_bkg))

        self.phibkgmodel = RooPolynomial("PhiBkg_"+name,"PhiBkg_"+name,Phi,RooArgList(self.phic1,self.phic2))


        self.modelBKG = RooProdPdf("modelBKG_"+name,"modelBKG_"+name,RooArgList(self.CTh1bkg,self.CTh2bkg,self.phibkgmodel,self.modelBKG_m1,self.modelBKG_m2))


    

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

