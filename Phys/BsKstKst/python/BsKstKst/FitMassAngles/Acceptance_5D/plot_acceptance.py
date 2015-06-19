from ROOT import *
from math import *
import scipy.special
from PDF_builder_self_v2_MCTruth import *
from BsKstKst.python_utils import *


gROOT.ProcessLine(".x ${BSKSTKSTROOT}/src/Acceptance_5D/Acceptance.cxx++")

import os
import cPickle
coef_file = open(os.environ["BSKSTKSTROOT"] + "/options/Acceptance_5D/acceptance_coef_5D.dct",'r')
coef_list = cPickle.load(coef_file)

coef_list = [[1.,1.],[2.,2.]]#,[[1.,2.],[2.,3.],[3.,4.]]]
coeffs = list_to_matrix(coef_list)
orders = arr_to_vect([len(coeffs),len(coeffs[0]) ])#    ,len(coeffs[0][0])       , len(coeffs[0][0][0]),len(coeffs[0][0][0][0])])

eff = Acceptance("acceptance","acceptance",CTh1,CTh2,Phi,m1,m2,orders,coeffs)

BREAK

### Legendre polynomials: scipy.special.eval_legendre(n,x)   n>=0
### Associated Legendre polynomials: scipy.special.lpmn(m,n,x)[0][m][n]  n>=0, m<=n
### Normalized Spherical harm. : sqrt(2)*scipy.special.sph_harm(m,n,phi,theta).item().real   n>=0, m<=n, 0<=phi<=2pi,  0<=theta<=pi

# def ass_legendre_n(n,x): return scipy.special.eval_legendre(n,x)
# def sph_harm_nm(n,m,c1,ph):
#     theta = acos(c1)
#     return scipy.special.sph_harm(m,n,ph,theta).item().real

# def acceptance(c1,c2,ph,m1,m2,coeffs):
#     i_max = len(coeffs)-1
#     j_max = len(coeffs[0])-1
#     l_max = len(coeffs[0][0])-1
#     n_max = len(coeffs[0][0][0])-1
#     m_max = len(coeffs[0][0][0][0])-1

#     eff_val = 

#     for i in range(i_max+1):
#         for j in range(j_max+1):
#             for l in range(l_max+1):
#                 for n in range(n_max+1):
#                     for m in range(m_max+1):

                        


f = TFile("${WHOME}/NTuples_Bs2KstKst_strip17/public/Bs2KstKst_Real2011_strip17_MC11a_cuts_v4r2_GL_2012_pi.root")
t2 = f.Get("T")
# fgen = TFile("/scratch08/NTuples_Bs2KstKst_strip17_Brais/public/Bs2Kst0Kst0_MC11.root")                                                                                                 
# t2 = fgen.Get("BsKst0Kst0")                                                                                                                                                             


cuts = "B_IPS<5 "
cuts += "&& P21_richPID_k>10 && P11_richPID_k>10 &&P22_richPID_k<0 && P12_richPID_k<0 "
cuts += "&& SV_chi2<25"
cuts += "&& P11_TrChi2DoF<5 && P12_TrChi2DoF<5 && P21_TrChi2Dof<5 && P22_TrChi2Dof<5 "
cuts += "&& P1_pt>900 && P2_pt>900 "
cuts += "&& P11_pt>500 && P12_pt>500 && P21_pt>500 && P22_pt>500 "
cuts += "&& max(P1V_chi2,P2V_chi2)<9 "
cuts += "&& B_dissig>15"
cuts += "&& (P11_richPID_p-P11_richPID_k)<15 && (P21_richPID_p-P21_richPID_k)<15"
cuts += "&& (abs(B_mass-5366.3)<30)"
cuts += "&& ! ( (abs(M_prpiKpi-5620)<40 && P11_richPID_p-P11_richPID_k>0 ) || (abs(M_Kpiprpi-5620)<40 && P21_richPID_p-P21_richPID_k>0 ) ) "
# signalcuts += "& abs(P1_mass-896)<100 & abs(P2_mass-896)<100"                                                                                                                           
cuts += "&& !(P11_muonPID_isMuonLoose || P12_muonPID_isMuonLoose || P21_muonPID_isMuonLoose || P22_muonPID_isMuonLoose)"


trigger = "L0Decision && Hlt1Decision && Hlt2Decision"

cuts_tos = " & (L0Tos) & (Hlt1Tos) & (Hlt2Tos)"
cuts_notos =  " & !((L0Tos) & (Hlt1Tos) & (Hlt2Tos))"# & P12_pt>1500 && P22_pt>1500"                                                                                                      

#trigger = "B_Decision==1"                                                                                                                                                                

gl = "&& GLKsb.>0.24 "#&& B_tos==1" ## GLKsb. is the GLK2012sb. in real data!!!                                                                                                           

cuts += gl + " && "+ trigger + cuts_notos


f2=TFile("nada.root","recreate")
t=t2.CopyTree(cuts)


Apa_Bs = 0.5
Ape_Bs = 0.33
A0_Bs  = 0.8
dpa_Bs = 3.14
dpe_Bs = 0.#3.14                                                                                                                                                                          

a02_Bs = A0_Bs*A0_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)
apa2_Bs = Apa_Bs*Apa_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)
ape2_Bs = Ape_Bs*Ape_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)

PDF = AngularPDF("Bs")
PDF.OwnPhys()
PDF.modParam("m_kst",8.95279e+02 , 1, kTRUE)
PDF.modParam("g_kst",5.01156e+01 , 1, kTRUE)
PDF.modParam("Bs2",0.,0.,kTRUE)
PDF.modParam("MBs",5366.3,0.,kTRUE)
PDF.modParam("Asm2",0.,0.,kTRUE)
PDF.modParam("dsm",0.,0.,kTRUE)
PDF.modParam("Asp2",0.,0.,kTRUE)
PDF.modParam("dsp",0.,0.,kTRUE)
PDF.modParam("Ass2",0.,0.,kTRUE)
PDF.modParam("dss",0.,0.,kTRUE)
PDF.modParam("dpe",0.,0.,kTRUE)
PDF.modParam("dpe",dpe_Bs,0.,kTRUE)
PDF.modParam("dpa",dpa_Bs,0.,kTRUE)
PDF.modParam("fL",a02_Bs,0.,kTRUE)
PDF.modParam("fpax",apa2_Bs/(1-a02_Bs),0.,kTRUE)


PDF.modParam("normP",1./8.82332476508e+13,0,kTRUE)#1./433923.65279,0,kTRUE)
PDF.modParam("normS",1./1.60399738894e+14,0,kTRUE)#1./771976.068198,0,kTRUE)
PDF.modParam("normSS",1./2.91590686297e+14,0,kTRUE)#1./1373391.4871,0,kTRUE)

PDF.make()

ntot = 2014993#t.GetEntries()



