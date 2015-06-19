from ROOT import *
from math import *
import scipy.special
from PDF_builder_self_v2_MCTruth import *

### Legendre polynomials: scipy.special.eval_legendre(n,x)   n>=0
### Associated Legendre polynomials: scipy.special.lpmn(m,n,x)[0][m][n]  n>=0, m<=n
### Normalized Spherical harm. : sqrt(2)*scipy.special.sph_harm(m,n,phi,theta).item().real   n>=0, m<=n, 0<=phi<=2pi,  0<=theta<=pi

def ass_legendre_n(n,x): return scipy.special.eval_legendre(n,x)
def sph_harm_nm(n,m,c1,ph):
    theta = acos(c1)
    return scipy.special.sph_harm(m,n,ph,theta).item().real


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

i_max = 2
j_max = 2 

n_max = 4
m_max = 2
l_max = 4

coeffs=[[[[[0 for m in range(m_max+1)] for n in range(n_max+1)] for l in range(l_max+1)] for j in range(j_max+1)] for i in range(i_max+1)]
ntot = 2014993#t.GetEntries()

for i in t:
    c1_ = i.CosTheta1
    c2_ = i.CosTheta2
    ph_ = i.Phi_pi
    m1_ = i.P1_mass
    m2_ = i.P2_mass

    CTh1.setVal(c1_)
    CTh2.setVal(c2_)
    Phi.setVal(ph_)
    m1.setVal(m1_)
    m2.setVal(c2_)

    g = PDF.sigmodel.getVal(RooArgSet(CTh1,CTh2,Phi,m1,m2))

    m1_red = (m1_ - 746)/(1046 - 746)*2. + (-1)
    m2_red = (m1_ - 746)/(1046 - 746)*2. + (-1)

    for i in range(i_max+1):
        for j in range(j_max+1):
            for l in range(l_max+1):
                for n in range(n_max+1):
                    for m in range(m_max+1):
                        if n<m: continue # n>m!!
                        if m==0: Y_nm = sph_harm_nm(n,m,c2_,ph_)
                        else: Y_nm = sqrt(2)*sph_harm_nm(n,m,c2_,ph_)
                        P_i = ass_legendre_n(i,m1_red)
                        P_j = ass_legendre_n(j,m2_red)
                        P_l = ass_legendre_n(l,c1_)

                        coeffs[i][j][l][n][m] += 1./ntot * (2*i+1)/2. * (2*j+1)/2. * (2*l+1)/2. * P_i*P_j*P_l*Y_nm/g



for i in range(i_max+1):
    for j in range(j_max+1):
        for l in range(l_max+1):
            for n in range(n_max+1):
                for m in range(m_max+1):

                    print "c_"+str(i)+str(j)+str(l)+str(n)+str(m)+" : ", coeffs[i][j][l][n][m]


import cPickle, os
cPickle.dump(coeffs,file(os.environ["BSKSTKSTROOT"] + "/options/Acceptance_5D/acceptance_coef_5D.dct",'w'))

# coef_file = open(os.environ["PWD"] + "/acceptance_v5.dct",'r')
# coef_list = cPickle.load(coef_file)



# func = TF1("func","3.*(1.-0.5*0.5)*sqrt(5./96./pi)*cos(2*x)",0.,2*pi)

# histo = TH1F("histo","histo",100,0.,2*pi)
# for i in range(100):
#     x=-1+2./100*(i+1/2)
#     histo.SetBinContent(i+1,ass_leg(histo.GetBinCenter(i+1)))

# histo.Draw()
# func.Draw("SAME")

# multipolyfile is a string containing the full file name.  The dimensions of the array are [3][5][3][3], so the integers l,i,k,j are


# l_max = 2
# m_max = 2 

# i_max = 4
# j_max = 2
# k_max = 2

# To apply correction do this for each event

# double Y_jk= 0.; double P_i= 0;
# double Q_l = 0.;
# Eff = 0.;
# double kstMass_mapped = (kstMass - 745.94)/(1045.94 - 745.94)*2. + (-1);
# for ( int l = 0; l < l_max+1; l++ )
# {
#     for ( int i = 0; i < i_max+1; i++ )
#           {
#             for ( int k = 0; k < k_max+1; k++)
#               {
#                 for ( int j = 0; j < j_max+1; j++ )
#                   {
#                     if (j < k) continue; // must have l >=k                                                                            
#                     Q_l  = gsl_sf_legendre_Pl     (l,    kstMass_mapped);
#                     P_i  = gsl_sf_legendre_Pl     (i,    cos_ThetaKpi);                                                                              
#                     if ( k == 0 ) Y_jk =           gsl_sf_legendre_sphPlm (j, k, cos_ThetaKK);
#                     else          Y_jk = sqrt(2) * gsl_sf_legendre_sphPlm (j, k, cos_ThetaKK) * cos(k*Phi);
#                     Eff += EffCoeff[l][i][k][j]*(Q_l * P_i * Y_jk);
#                   }
#               }
#           }
#       }



# double My_legendre_Pl  (int l, double x) {

#   if (l == 0) {
#     return 1.;
#   } else if (l == 1) {
#     return x;
#   } else if (l == 2) {
#     return 0.5*(3.*x*x-1.);
#   } else if (l == 3) {
#     return 0.5*(5.*x*x*x-3.*x);
#   } else if (l == 4) {
#     return 1./8.*(35.*x*x*x*x-30.*x*x+3.);
#   } else {
#     return 1.;
#   }

# }

# double My_legendre_sphPlm (double j, double k, double c1) {

#   if (j == 0 && k == 0) {
#     return 0.5*sqrt(1./TMath::Pi());
#   } else if (j == 1 && k == 0) {
#     return 0.5*sqrt(3./TMath::Pi())*c1;
#   } else if (j == 1 && k == 1) {
#     return -sqrt(1.-c1*c1)*sqrt(3./8./TMath::Pi());
#   } else if (j == 2 && k == 0) {
#     return 0.25*sqrt(5./TMath::Pi())*(3.*c1*c1-1.);
#   } else if (j == 2 && k == 1) {
#     return -3.*c1*sqrt(1.-c1*c1)*sqrt(5./24./TMath::Pi());
#   } else if (j == 2 && k == 2) {
#     return 3.*(1.-c1*c1)*sqrt(5./96./TMath::Pi());
#   } else {
#     return 1.;
#   }

# }
