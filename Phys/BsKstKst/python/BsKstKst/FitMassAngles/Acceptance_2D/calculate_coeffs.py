from ROOT import *
from math import *
from PDF_builder_MCTruth import *

TOS = 1

gSystem.Load("libMathMore")

f = TFile("${WHOME}/NTuples_Bs2KstKst_strip17/public/Bs2KstKst_Real2011_strip17_MC11a_cuts_v4r2_GL_2012_pi.root")
t2 = f.Get("T")

import cPickle, os
cuts_file = open(os.environ["BSKSTKSTROOT"]+"/options/cuts.txt")
cuts = cPickle.load(cuts_file)

cuts_tos = " ((L0Tos) & (Hlt1Tos) & (Hlt2Tos))"
if not TOS: cuts_tos = "!"+cuts_tos

gl = "&& GLKsb.>0.14  && abs(B_mass-5366.3)<30"

cuts += gl + " && "+ cuts_tos


f2=TFile("nada.root","recreate")
t=t2.CopyTree(cuts)


Apa_Bs = 0.5
Ape_Bs = 0.33
A0_Bs  = 0.8
dpa_Bs = 0#3.14
dpe_Bs = 0.#3.14                                                                                                                                                                          

a02_Bs = A0_Bs*A0_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)
apa2_Bs = Apa_Bs*Apa_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)
ape2_Bs = Ape_Bs*Ape_Bs / (A0_Bs*A0_Bs + Apa_Bs*Apa_Bs + Ape_Bs*Ape_Bs)

PDF = AngularPDF("Bs")
PDF.OwnPhys()
PDF.modParam("m_kst",896.1,1,kTRUE)#895.81 , 1, kTRUE)
PDF.modParam("g_kst",50.5,1,kTRUE)#47.4 , 1, kTRUE)
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


PDF.modParam("c1_th",0.,kTRUE)
PDF.modParam("c2_th",0.,kTRUE)
PDF.modParam("c3_th",0.,kTRUE)
PDF.modParam("c4_th",0.,kTRUE)
PDF.modParam("y",1.,kTRUE)

PDF.modParam("c1_ph",0.,kTRUE)
PDF.modParam("c2_ph",1.5,kTRUE)
PDF.modParam("c3_ph",0.,kTRUE)

PDF.CalcNorm()

PDF.make()

Phi.setMin(-pi)
Phi.setMax(pi)


CTh1.SetNameTitle("CosTheta1","CosTheta1")
CTh2.SetNameTitle("CosTheta2","CosTheta2")
Phi.SetNameTitle("Phi","Phi")
m1.SetNameTitle("P1_mass","P1_mass")
m2.SetNameTitle("P2_mass","P2_mass")
i_max = 2
j_max = 4 

# PDF.DGs.setVal(0)


coeffs=[[0 for j in range(j_max+1)] for i in range(i_max+1)]
coeffs2=[[0 for j in range(j_max+1)] for i in range(i_max+1)]
ntot = t.GetEntries()#2014993e6

model2d = PDF.sigmodel.createProjection(RooArgSet(CTh2,Phi,m2))
model2d_b = PDF.sigmodel.createProjection(RooArgSet(CTh1,Phi,m1))

massmin = 896-150.
massmax = 896+150.

m1.setMin(massmin)
m1.setMax(massmax)
m2.setMin(massmin)
m2.setMax(massmax)

sumw = 0
for i in t:
    if (i.P1_mass<massmin or i.P1_mass>massmax or i.P2_mass<massmin or i.P2_mass>massmax): continue
    c1_ = i.CosTheta1
    c2_ = i.CosTheta2
    ph_ = i.Phi
    m1_ = i.P1_mass
    m2_ = i.P2_mass

#     CTh1.setVal(c1_)
#     m1.setVal(m1_)
#     g1 = model2d.getVal(RooArgSet(CTh1,m1))

#     CTh1.setVal(c2_)
#     m1.setVal(m2_)
#     g2 = model2d.getVal(RooArgSet(CTh1,m1))


    CTh1.setVal(c1_)
    CTh2.setVal(c2_)
    Phi.setVal(ph_)
    m1.setVal(m1_)
    m2.setVal(m2_)

    g = PDF.sigmodel.getVal(RooArgSet(CTh1,CTh2,Phi,m1,m2))
    #g = model2d.getVal(RooArgSet(CTh1,m1))
    g_b = model2d_b.getVal(RooArgSet(CTh2,m2))

    sumw += 1./g
    sumw += 1./g
    
#     m1_red = (m1_ - 746)/(1046 - 746)*2. + (-1)
#     m2_red = (m2_ - 746)/(1046 - 746)*2. + (-1)
    m1_red = (m1_ - massmin)/(massmax - massmin)*2. + (-1)
    m2_red = (m2_ - massmin)/(massmax - massmin)*2. + (-1)

    for i in range(i_max+1):
        for j in range(j_max+1):
            P_i1 =  Math.legendre(i,m1_red)
            Y_j1 = Math.legendre(j,c1_)

            P_i2 =  Math.legendre(i,m2_red)
            Y_j2 = Math.legendre(j,c2_)

            coeffs[i][j] +=  (2*i+1)/2. * (2*j+1)/2. * P_i1*Y_j1/g
            coeffs[i][j] +=  (2*i+1)/2. * (2*j+1)/2. * P_i2*Y_j2/g

for i in t:
    if (i.P1_mass<massmin or i.P1_mass>massmax or i.P2_mass<massmin or i.P2_mass>massmax): continue
    c1_ = i.CosTheta1
    c2_ = i.CosTheta2
    ph_ = i.Phi
    m1_ = i.P1_mass
    m2_ = i.P2_mass

#     CTh1.setVal(c1_)
#     m1.setVal(m1_)
#     g1 = model2d.getVal(RooArgSet(CTh1,m1))

#     CTh1.setVal(c2_)
#     m1.setVal(m2_)
#     g2 = model2d.getVal(RooArgSet(CTh1,m1))


    CTh1.setVal(c1_)
    CTh2.setVal(c2_)
    Phi.setVal(ph_)
    m1.setVal(m1_)
    m2.setVal(m2_)

    g = PDF.sigmodel.getVal(RooArgSet(CTh1,CTh2,Phi,m1,m2))
    #g = model2d.getVal(RooArgSet(CTh1,m1))
    g_b = model2d_b.getVal(RooArgSet(CTh2,m2))

    
    
#     m1_red = (m1_ - 746)/(1046 - 746)*2. + (-1)
#     m2_red = (m2_ - 746)/(1046 - 746)*2. + (-1)
    m1_red = (m1_ - massmin)/(massmax - massmin)*2. + (-1)
    m2_red = (m2_ - massmin)/(massmax - massmin)*2. + (-1)

    for i in range(i_max+1):
        for j in range(j_max+1):
            P_i1 =  Math.legendre(i,m1_red)
            Y_j1 = Math.legendre(j,c1_)

            P_i2 =  Math.legendre(i,m2_red)
            Y_j2 = Math.legendre(j,c2_)

            coeffs2[i][j] += pow( (2*i+1)/2. * (2*j+1)/2. * P_i1*Y_j1 - coeffs[i][j]/sumw,2)/pow(g,2)
            coeffs2[i][j] += pow( (2*i+1)/2. * (2*j+1)/2. * P_i2*Y_j2 - coeffs[i][j]/sumw,2)/pow(g,2)


coeffs_corr=[[0 for j in range(j_max+1)] for i in range(i_max+1)]
coeffs_err=[[0 for j in range(j_max+1)] for i in range(i_max+1)]

for i in range(i_max+1):
    for j in range(j_max+1):
        coeffs_corr[i][j] = coeffs[i][j]/sumw
        coeffs_err[i][j] = sqrt(coeffs2[i][j]/(pow(sumw,2)))
        print "c_"+str(i)+str(j)+" : ", coeffs[i][j]/sumw, " +/- ", sqrt(coeffs2[i][j]/(pow(sumw,2)))


import cPickle, os
coeffs_dict = {"coeffs_val": coeffs_corr, "coeffs_err": coeffs_err}

tosname = "TOS"
if not TOS: tosname = "NO"+tosname

cPickle.dump(coeffs_dict,file("acceptance_coef_2D_"+tosname+".dct",'w'))
list_to_tree(coeffs_corr,fname="acceptance_coef_2D_"+tosname,tname="acc5D",bname="coeffs")



