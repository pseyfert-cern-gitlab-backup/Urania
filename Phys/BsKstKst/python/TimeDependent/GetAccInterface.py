from ROOT import *
from math import *
import time
import os
from parameters import *
gROOT.ProcessLine('.x ../../src/TimeDependent/KpiKpiSpectrumNW.cxx++')
gROOT.ProcessLine('.x ../../src/TimeDependent/ComputeIntegrals.cxx++')
gROOT.ProcessLine('.x ../../src/TimeDependent/accpdf.cxx++')
gROOT.ProcessLine('.x ../../src/TimeDependent/MCGenComb.cxx++')
gROOT.ProcessLine('.x ../../src/TimeDependent/SplineTAcc.cxx++')
gROOT.ProcessLine('.x ../../src/TimeDependent/lhcbStyle.C')
gROOT.Reset()


# ################################################################
# V A R I A B L E S
# ################################################################

# Names of the variables in the ntuples.
m1_name_MC = "B_s0_DTF_KST1_M"
m2_name_MC = "B_s0_DTF_KST2_M"
cos1_name_MC = "B_s0_DTF_KST1_COSTHETA"
cos2_name_MC = "B_s0_DTF_KST2_COSTHETA"
phi_name_MC = "B_s0_DTF_B_s0_PHI"
t_name_MC = "B_s0_DTF_B_s0_TAU"

# Observables.
mKp1_MC = RooRealVar(m1_name_MC,"M(K^{+}#pi^{-}) ", 750., 1500.,"MeV/c^{2}")
mKp2_MC = RooRealVar(m2_name_MC,"M(K^{-}#pi^{+}) ", 750., 1500.,"MeV/c^{2}")
mKp1_narrow_MC = RooRealVar(m1_name_MC,"M(K^{+}#pi^{-}) ",900.-150.,900.+150.,"MeV/c^{2}")
mKp2_narrow_MC = RooRealVar(m2_name_MC,"M(K^{-}#pi^{+}) ",900.-150.,900.+150.,"MeV/c^{2}")
cos1_MC = RooRealVar(cos1_name_MC,"cos(#theta_{1})", -1., 1.,"")
cos2_MC = RooRealVar(cos2_name_MC,"cos(#theta_{2})", -1., 1.,"")
phi_MC = RooRealVar(phi_name_MC,"#varphi",-pi,pi,"rad")
t_MC = RooRealVar(t_name_MC,"t_{true}",0.,12.,"ps")

# K+pi-/K-pi+ mass and costheta simultaneous fit categories.
kpipaircat = RooCategory("kpipaircat","kpipaircat")
kpipaircat.defineType("kpi1")
kpipaircat.defineType("kpi2")

# Parameters of the visualization acceptance.
k1_2011_L0TIS_wide = RooRealVar("k1_2011_L0TIS_wide","k1_2011_L0TIS_wide",-0.407189518759,-1.,1.)
k2_2011_L0TIS_wide = RooRealVar("k2_2011_L0TIS_wide","k2_2011_L0TIS_wide",-0.447514109157,-1.,1.)
k3_2011_L0TIS_wide = RooRealVar("k3_2011_L0TIS_wide","k3_2011_L0TIS_wide",-0.00934734637454,-1.,1.)
k4_2011_L0TIS_wide = RooRealVar("k4_2011_L0TIS_wide","k4_2011_L0TIS_wide",-0.0223113853263,-1.,1.)
k5_2011_L0TIS_wide = RooRealVar("k5_2011_L0TIS_wide","k5_2011_L0TIS_wide",0.0309083133084,-1.,1.)
p1_2011_L0TIS_wide = RooRealVar("p1_2011_L0TIS_wide","p1_2011_L0TIS_wide",-0.000136056558122,-1.,1.)
a_acc_2011_L0TIS_wide = RooRealVar("a_acc_2011_L0TIS_wide","a_acc_2011_L0TIS_wide",0.306699906284,0.,1.)
b_acc_2011_L0TIS_wide = RooRealVar("b_acc_2011_L0TIS_wide","b_acc_2011_L0TIS_wide",0.00161205498045,-1.,1.)
c_acc_2011_L0TIS_wide = RooRealVar("c_acc_2011_L0TIS_wide","c_acc_2011_L0TIS_wide",-0.00166511447598,-1.,1.)
k1_2012_L0TIS_wide = RooRealVar("k1_2012_L0TIS_wide","k1_2012_L0TIS_wide",-0.398559161033,-1.,1.)
k2_2012_L0TIS_wide = RooRealVar("k2_2012_L0TIS_wide","k2_2012_L0TIS_wide",-0.443862130939,-1.,1.)
k3_2012_L0TIS_wide = RooRealVar("k3_2012_L0TIS_wide","k3_2012_L0TIS_wide",0.00642183905325,-1.,1.)
k4_2012_L0TIS_wide = RooRealVar("k4_2012_L0TIS_wide","k4_2012_L0TIS_wide",-0.0316535792738,-1.,1.)
k5_2012_L0TIS_wide = RooRealVar("k5_2012_L0TIS_wide","k5_2012_L0TIS_wide",0.0265194645971,-1.,1.)
p1_2012_L0TIS_wide = RooRealVar("p1_2012_L0TIS_wide","p1_2012_L0TIS_wide",-0.000146866255065,-1.,1.)
a_acc_2012_L0TIS_wide = RooRealVar("a_acc_2012_L0TIS_wide","a_acc_2012_L0TIS_wide",0.282617761238,0.,1.)
b_acc_2012_L0TIS_wide = RooRealVar("b_acc_2012_L0TIS_wide","b_acc_2012_L0TIS_wide",0.0201594947247,-1.,1.)
c_acc_2012_L0TIS_wide = RooRealVar("c_acc_2012_L0TIS_wide","c_acc_2012_L0TIS_wide",-0.0025320315317,-1.,1.)
k1_2011_L0TIS_narrow = RooRealVar("k1_2011_L0TIS_narrow","k1_2011_L0TIS_narrow",-0.587898897347,-1.,1.)
k2_2011_L0TIS_narrow = RooRealVar("k2_2011_L0TIS_narrow","k2_2011_L0TIS_narrow",-0.384417371494,-1.,1.)
k3_2011_L0TIS_narrow = RooRealVar("k3_2011_L0TIS_narrow","k3_2011_L0TIS_narrow",-0.0495894022243,-1.,1.)
k4_2011_L0TIS_narrow = RooRealVar("k4_2011_L0TIS_narrow","k4_2011_L0TIS_narrow",-0.00545987029864,-1.,1.)
k5_2011_L0TIS_narrow = RooRealVar("k5_2011_L0TIS_narrow","k5_2011_L0TIS_narrow",0.0576283825768,-1.,1.)
p1_2011_L0TIS_narrow = RooRealVar("p1_2011_L0TIS_narrow","p1_2011_L0TIS_narrow",0.00042394835386,-1.,1.)
a_acc_2011_L0TIS_narrow = RooRealVar("a_acc_2011_L0TIS_narrow","a_acc_2011_L0TIS_narrow",0.256930119934,0.,1.)
b_acc_2011_L0TIS_narrow = RooRealVar("b_acc_2011_L0TIS_narrow","b_acc_2011_L0TIS_narrow",0.00210056808734,-1.,1.)
c_acc_2011_L0TIS_narrow = RooRealVar("c_acc_2011_L0TIS_narrow","c_acc_2011_L0TIS_narrow",-0.00115315019855,-1.,1.)
k1_2012_L0TIS_narrow = RooRealVar("k1_2012_L0TIS_narrow","k1_2012_L0TIS_narrow",-0.565733274592,-1.,1.)
k2_2012_L0TIS_narrow = RooRealVar("k2_2012_L0TIS_narrow","k2_2012_L0TIS_narrow",-0.392151805394,-1.,1.)
k3_2012_L0TIS_narrow = RooRealVar("k3_2012_L0TIS_narrow","k3_2012_L0TIS_narrow",-0.0251228380474,-1.,1.)
k4_2012_L0TIS_narrow = RooRealVar("k4_2012_L0TIS_narrow","k4_2012_L0TIS_narrow",0.0316224687878,-1.,1.)
k5_2012_L0TIS_narrow = RooRealVar("k5_2012_L0TIS_narrow","k5_2012_L0TIS_narrow",0.0238529427506,-1.,1.)
p1_2012_L0TIS_narrow = RooRealVar("p1_2012_L0TIS_narrow","p1_2012_L0TIS_narrow",-0.000199723627464,-1.,1.)
a_acc_2012_L0TIS_narrow = RooRealVar("a_acc_2012_L0TIS_narrow","a_acc_2012_L0TIS_narrow",0.200307004499,0.,1.)
b_acc_2012_L0TIS_narrow = RooRealVar("b_acc_2012_L0TIS_narrow","b_acc_2012_L0TIS_narrow",0.132379462681,-1.,1.)
c_acc_2012_L0TIS_narrow = RooRealVar("c_acc_2012_L0TIS_narrow","c_acc_2012_L0TIS_narrow",-0.0141441130199,-1.,1.)
k1_2011_L0noTIS_wide = RooRealVar("k1_2011_L0noTIS_wide","k1_2011_L0noTIS_wide",-0.321238524991,-1.,1.)
k2_2011_L0noTIS_wide = RooRealVar("k2_2011_L0noTIS_wide","k2_2011_L0noTIS_wide",-0.303981763929,-1.,1.)
k3_2011_L0noTIS_wide = RooRealVar("k3_2011_L0noTIS_wide","k3_2011_L0noTIS_wide",-0.0722102817233,-1.,1.)
k4_2011_L0noTIS_wide = RooRealVar("k4_2011_L0noTIS_wide","k4_2011_L0noTIS_wide",-0.0871702637649,-1.,1.)
k5_2011_L0noTIS_wide = RooRealVar("k5_2011_L0noTIS_wide","k5_2011_L0noTIS_wide",0.00542609949497,-1.,1.)
p1_2011_L0noTIS_wide = RooRealVar("p1_2011_L0noTIS_wide","p1_2011_L0noTIS_wide",-7.48154538164e-05,-1.,1.)
a_acc_2011_L0noTIS_wide = RooRealVar("a_acc_2011_L0noTIS_wide","a_acc_2011_L0noTIS_wide",0.204623747062,0.,1.)
b_acc_2011_L0noTIS_wide = RooRealVar("b_acc_2011_L0noTIS_wide","b_acc_2011_L0noTIS_wide",0.0476314077729,-1.,1.)
c_acc_2011_L0noTIS_wide = RooRealVar("c_acc_2011_L0noTIS_wide","c_acc_2011_L0noTIS_wide",-0.00505491024814,-1.,1.)
k1_2012_L0noTIS_wide = RooRealVar("k1_2012_L0noTIS_wide","k1_2012_L0noTIS_wide",-0.332780048339,-1.,1.)
k2_2012_L0noTIS_wide = RooRealVar("k2_2012_L0noTIS_wide","k2_2012_L0noTIS_wide",-0.281905586145,-1.,1.)
k3_2012_L0noTIS_wide = RooRealVar("k3_2012_L0noTIS_wide","k3_2012_L0noTIS_wide",-0.0609785924202,-1.,1.)
k4_2012_L0noTIS_wide = RooRealVar("k4_2012_L0noTIS_wide","k4_2012_L0noTIS_wide",-0.0871249564397,-1.,1.)
k5_2012_L0noTIS_wide = RooRealVar("k5_2012_L0noTIS_wide","k5_2012_L0noTIS_wide",0.024948046655,-1.,1.)
p1_2012_L0noTIS_wide = RooRealVar("p1_2012_L0noTIS_wide","p1_2012_L0noTIS_wide",5.03530100948e-07,-1.,1.)
a_acc_2012_L0noTIS_wide = RooRealVar("a_acc_2012_L0noTIS_wide","a_acc_2012_L0noTIS_wide",0.198766603064,0.,1.)
b_acc_2012_L0noTIS_wide = RooRealVar("b_acc_2012_L0noTIS_wide","b_acc_2012_L0noTIS_wide",0.0580878785672,-1.,1.)
c_acc_2012_L0noTIS_wide = RooRealVar("c_acc_2012_L0noTIS_wide","c_acc_2012_L0noTIS_wide",-0.00811491350386,-1.,1.)
k1_2011_L0noTIS_narrow = RooRealVar("k1_2011_L0noTIS_narrow","k1_2011_L0noTIS_narrow",-0.433346828587,-1.,1.)
k2_2011_L0noTIS_narrow = RooRealVar("k2_2011_L0noTIS_narrow","k2_2011_L0noTIS_narrow",-0.302483466397,-1.,1.)
k3_2011_L0noTIS_narrow = RooRealVar("k3_2011_L0noTIS_narrow","k3_2011_L0noTIS_narrow",-0.104606114087,-1.,1.)
k4_2011_L0noTIS_narrow = RooRealVar("k4_2011_L0noTIS_narrow","k4_2011_L0noTIS_narrow",-0.10987218843,-1.,1.)
k5_2011_L0noTIS_narrow = RooRealVar("k5_2011_L0noTIS_narrow","k5_2011_L0noTIS_narrow",-0.0377129513096,-1.,1.)
p1_2011_L0noTIS_narrow = RooRealVar("p1_2011_L0noTIS_narrow","p1_2011_L0noTIS_narrow",-0.000353244271559,-1.,1.)
a_acc_2011_L0noTIS_narrow = RooRealVar("a_acc_2011_L0noTIS_narrow","a_acc_2011_L0noTIS_narrow",0.19086074794,0.,1.)
b_acc_2011_L0noTIS_narrow = RooRealVar("b_acc_2011_L0noTIS_narrow","b_acc_2011_L0noTIS_narrow",0.0285414056039,-1.,1.)
c_acc_2011_L0noTIS_narrow = RooRealVar("c_acc_2011_L0noTIS_narrow","c_acc_2011_L0noTIS_narrow",-0.00320159957361,-1.,1.)
k1_2012_L0noTIS_narrow = RooRealVar("k1_2012_L0noTIS_narrow","k1_2012_L0noTIS_narrow",-0.329505489254,-1.,1.)
k2_2012_L0noTIS_narrow = RooRealVar("k2_2012_L0noTIS_narrow","k2_2012_L0noTIS_narrow",-0.316061150279,-1.,1.)
k3_2012_L0noTIS_narrow = RooRealVar("k3_2012_L0noTIS_narrow","k3_2012_L0noTIS_narrow",-0.0923325443943,-1.,1.)
k4_2012_L0noTIS_narrow = RooRealVar("k4_2012_L0noTIS_narrow","k4_2012_L0noTIS_narrow",-0.0482187886119,-1.,1.)
k5_2012_L0noTIS_narrow = RooRealVar("k5_2012_L0noTIS_narrow","k5_2012_L0noTIS_narrow",0.0255909373431,-1.,1.)
p1_2012_L0noTIS_narrow = RooRealVar("p1_2012_L0noTIS_narrow","p1_2012_L0noTIS_narrow",0.000790107359973,-1.,1.)
a_acc_2012_L0noTIS_narrow = RooRealVar("a_acc_2012_L0noTIS_narrow","a_acc_2012_L0noTIS_narrow",0.204945455175,0.,1.)
b_acc_2012_L0noTIS_narrow = RooRealVar("b_acc_2012_L0noTIS_narrow","b_acc_2012_L0noTIS_narrow",0.0192585617916,-1.,1.)
c_acc_2012_L0noTIS_narrow = RooRealVar("c_acc_2012_L0noTIS_narrow","c_acc_2012_L0noTIS_narrow",-0.00433396118915,-1.,1.)

# Parameters of the splines.
t0_wide = RooRealVar("t0_wide","t0_wide",0.)
t1_wide = RooRealVar("t1_wide","t1_wide",0.)
t2_wide = RooRealVar("t2_wide","t2_wide",0.)
t3_wide = RooRealVar("t3_wide","t3_wide",0.)
t4_wide = RooRealVar("t4_wide","t4_wide",0.)
t5_wide = RooRealVar("t5_wide","t5_wide",0.)
t0_narrow = RooRealVar("t0_narrow","t0_narrow",0.)
t1_narrow = RooRealVar("t1_narrow","t1_narrow",0.)
t2_narrow = RooRealVar("t2_narrow","t2_narrow",0.)
t3_narrow = RooRealVar("t3_narrow","t3_narrow",0.)
t4_narrow = RooRealVar("t4_narrow","t4_narrow",0.)
t5_narrow = RooRealVar("t5_narrow","t5_narrow",0.)
spl_c0_2011_L0TIS_wide = RooRealVar("spl_c0_2011_L0TIS_wide","spl_c0_2011_L0TIS_wide",0.)
spl_c1_2011_L0TIS_wide = RooRealVar("spl_c1_2011_L0TIS_wide","spl_c1_2011_L0TIS_wide",-8.04292e-04,-1.,1.)
spl_c2_2011_L0TIS_wide = RooRealVar("spl_c2_2011_L0TIS_wide","spl_c2_2011_L0TIS_wide",1.54376e+00,0.,5.)
spl_c3_2011_L0TIS_wide = RooRealVar("spl_c3_2011_L0TIS_wide","spl_c3_2011_L0TIS_wide",1.83198e+00,0.,5.)
spl_c4_2011_L0TIS_wide = RooRealVar("spl_c4_2011_L0TIS_wide","spl_c4_2011_L0TIS_wide",1.99918e+00,0.,5.)
spl_c5_2011_L0TIS_wide = RooRealVar("spl_c5_2011_L0TIS_wide","spl_c5_2011_L0TIS_wide",1.56178e+00,0.,5.)
spl_c6_2011_L0TIS_wide = RooRealVar("spl_c6_2011_L0TIS_wide","spl_c6_2011_L0TIS_wide",2.00961e+00,0.,5.)
spl_c7_2011_L0TIS_wide = RooRealVar("spl_c7_2011_L0TIS_wide","spl_c7_2011_L0TIS_wide",1.)
spl_c0_2012_L0TIS_wide = RooRealVar("spl_c0_2012_L0TIS_wide","spl_c0_2012_L0TIS_wide",0.)
spl_c1_2012_L0TIS_wide = RooRealVar("spl_c1_2012_L0TIS_wide","spl_c1_2012_L0TIS_wide",-8.04292e-04,-1.,1.)
spl_c2_2012_L0TIS_wide = RooRealVar("spl_c2_2012_L0TIS_wide","spl_c2_2012_L0TIS_wide",1.54376e+00,0.,5.)
spl_c3_2012_L0TIS_wide = RooRealVar("spl_c3_2012_L0TIS_wide","spl_c3_2012_L0TIS_wide",1.83198e+00,0.,5.)
spl_c4_2012_L0TIS_wide = RooRealVar("spl_c4_2012_L0TIS_wide","spl_c4_2012_L0TIS_wide",1.99918e+00,0.,5.)
spl_c5_2012_L0TIS_wide = RooRealVar("spl_c5_2012_L0TIS_wide","spl_c5_2012_L0TIS_wide",1.56178e+00,0.,5.)
spl_c6_2012_L0TIS_wide = RooRealVar("spl_c6_2012_L0TIS_wide","spl_c6_2012_L0TIS_wide",2.00961e+00,0.,5.)
spl_c7_2012_L0TIS_wide = RooRealVar("spl_c7_2012_L0TIS_wide","spl_c7_2012_L0TIS_wide",1.)
spl_c0_2011_L0noTIS_wide = RooRealVar("spl_c0_2011_L0noTIS_wide","spl_c0_2011_L0noTIS_wide",0.)
spl_c1_2011_L0noTIS_wide = RooRealVar("spl_c1_2011_L0noTIS_wide","spl_c1_2011_L0noTIS_wide",-7.27954e-04,-1.,1.)
spl_c2_2011_L0noTIS_wide = RooRealVar("spl_c2_2011_L0noTIS_wide","spl_c2_2011_L0noTIS_wide",1.39946e+00,0.,5.)
spl_c3_2011_L0noTIS_wide = RooRealVar("spl_c3_2011_L0noTIS_wide","spl_c3_2011_L0noTIS_wide",1.50541e+00,0.,5.)
spl_c4_2011_L0noTIS_wide = RooRealVar("spl_c4_2011_L0noTIS_wide","spl_c4_2011_L0noTIS_wide",1.71193e+00,0.,5.)
spl_c5_2011_L0noTIS_wide = RooRealVar("spl_c5_2011_L0noTIS_wide","spl_c5_2011_L0noTIS_wide",1.74520e+00,0.,5.)
spl_c6_2011_L0noTIS_wide = RooRealVar("spl_c6_2011_L0noTIS_wide","spl_c6_2011_L0noTIS_wide",1.63529e+00,0.,5.)
spl_c7_2011_L0noTIS_wide = RooRealVar("spl_c7_2011_L0noTIS_wide","spl_c7_2011_L0noTIS_wide",1.)
spl_c0_2012_L0noTIS_wide = RooRealVar("spl_c0_2012_L0noTIS_wide","spl_c0_2012_L0noTIS_wide",0.)
spl_c1_2012_L0noTIS_wide = RooRealVar("spl_c1_2012_L0noTIS_wide","spl_c1_2012_L0noTIS_wide",-8.04292e-04,-1.,1.)
spl_c2_2012_L0noTIS_wide = RooRealVar("spl_c2_2012_L0noTIS_wide","spl_c2_2012_L0noTIS_wide",1.54376e+00,0.,5.)
spl_c3_2012_L0noTIS_wide = RooRealVar("spl_c3_2012_L0noTIS_wide","spl_c3_2012_L0noTIS_wide",1.83198e+00,0.,5.)
spl_c4_2012_L0noTIS_wide = RooRealVar("spl_c4_2012_L0noTIS_wide","spl_c4_2012_L0noTIS_wide",1.99918e+00,0.,5.)
spl_c5_2012_L0noTIS_wide = RooRealVar("spl_c5_2012_L0noTIS_wide","spl_c5_2012_L0noTIS_wide",1.56178e+00,0.,5.)
spl_c6_2012_L0noTIS_wide = RooRealVar("spl_c6_2012_L0noTIS_wide","spl_c6_2012_L0noTIS_wide",2.00961e+00,0.,5.)
spl_c7_2012_L0noTIS_wide = RooRealVar("spl_c7_2012_L0noTIS_wide","spl_c7_2012_L0noTIS_wide",1.)
spl_c0_2011_L0TIS_narrow = RooRealVar("spl_c0_2011_L0TIS_narrow","spl_c0_2011_L0TIS_narrow",0.)
spl_c1_2011_L0TIS_narrow = RooRealVar("spl_c1_2011_L0TIS_narrow","spl_c1_2011_L0TIS_narrow",-8.04292e-04,-1.,1.)
spl_c2_2011_L0TIS_narrow = RooRealVar("spl_c2_2011_L0TIS_narrow","spl_c2_2011_L0TIS_narrow",1.54376e+00,0.,5.)
spl_c3_2011_L0TIS_narrow = RooRealVar("spl_c3_2011_L0TIS_narrow","spl_c3_2011_L0TIS_narrow",1.83198e+00,0.,5.)
spl_c4_2011_L0TIS_narrow = RooRealVar("spl_c4_2011_L0TIS_narrow","spl_c4_2011_L0TIS_narrow",1.99918e+00,0.,5.)
spl_c5_2011_L0TIS_narrow = RooRealVar("spl_c5_2011_L0TIS_narrow","spl_c5_2011_L0TIS_narrow",1.56178e+00,0.,5.)
spl_c6_2011_L0TIS_narrow = RooRealVar("spl_c6_2011_L0TIS_narrow","spl_c6_2011_L0TIS_narrow",2.00961e+00,0.,5.)
spl_c7_2011_L0TIS_narrow = RooRealVar("spl_c7_2011_L0TIS_narrow","spl_c7_2011_L0TIS_narrow",1.)
spl_c0_2012_L0TIS_narrow = RooRealVar("spl_c0_2012_L0TIS_narrow","spl_c0_2012_L0TIS_narrow",0.)
spl_c1_2012_L0TIS_narrow = RooRealVar("spl_c1_2012_L0TIS_narrow","spl_c1_2012_L0TIS_narrow",-8.04292e-04,-1.,1.)
spl_c2_2012_L0TIS_narrow = RooRealVar("spl_c2_2012_L0TIS_narrow","spl_c2_2012_L0TIS_narrow",1.54376e+00,0.,5.)
spl_c3_2012_L0TIS_narrow = RooRealVar("spl_c3_2012_L0TIS_narrow","spl_c3_2012_L0TIS_narrow",1.83198e+00,0.,5.)
spl_c4_2012_L0TIS_narrow = RooRealVar("spl_c4_2012_L0TIS_narrow","spl_c4_2012_L0TIS_narrow",1.99918e+00,0.,5.)
spl_c5_2012_L0TIS_narrow = RooRealVar("spl_c5_2012_L0TIS_narrow","spl_c5_2012_L0TIS_narrow",1.56178e+00,0.,5.)
spl_c6_2012_L0TIS_narrow = RooRealVar("spl_c6_2012_L0TIS_narrow","spl_c6_2012_L0TIS_narrow",2.00961e+00,0.,5.)
spl_c7_2012_L0TIS_narrow = RooRealVar("spl_c7_2012_L0TIS_narrow","spl_c7_2012_L0TIS_narrow",1.)
spl_c0_2011_L0noTIS_narrow = RooRealVar("spl_c0_2011_L0noTIS_narrow","spl_c0_2011_L0noTIS_narrow",0.)
spl_c1_2011_L0noTIS_narrow = RooRealVar("spl_c1_2011_L0noTIS_narrow","spl_c1_2011_L0noTIS_narrow",-8.04292e-04,-1.,1.)
spl_c2_2011_L0noTIS_narrow = RooRealVar("spl_c2_2011_L0noTIS_narrow","spl_c2_2011_L0noTIS_narrow",1.54376e+00,0.,5.)
spl_c3_2011_L0noTIS_narrow = RooRealVar("spl_c3_2011_L0noTIS_narrow","spl_c3_2011_L0noTIS_narrow",1.83198e+00,0.,5.)
spl_c4_2011_L0noTIS_narrow = RooRealVar("spl_c4_2011_L0noTIS_narrow","spl_c4_2011_L0noTIS_narrow",1.99918e+00,0.,5.)
spl_c5_2011_L0noTIS_narrow = RooRealVar("spl_c5_2011_L0noTIS_narrow","spl_c5_2011_L0noTIS_narrow",1.56178e+00,0.,5.)
spl_c6_2011_L0noTIS_narrow = RooRealVar("spl_c6_2011_L0noTIS_narrow","spl_c6_2011_L0noTIS_narrow",2.00961e+00,0.,5.)
spl_c7_2011_L0noTIS_narrow = RooRealVar("spl_c7_2011_L0noTIS_narrow","spl_c7_2011_L0noTIS_narrow",1.)
spl_c0_2012_L0noTIS_narrow = RooRealVar("spl_c0_2012_L0noTIS_narrow","spl_c0_2012_L0noTIS_narrow",0.)
spl_c1_2012_L0noTIS_narrow = RooRealVar("spl_c1_2012_L0noTIS_narrow","spl_c1_2012_L0noTIS_narrow",-8.04292e-04,-1.,1.)
spl_c2_2012_L0noTIS_narrow = RooRealVar("spl_c2_2012_L0noTIS_narrow","spl_c2_2012_L0noTIS_narrow",1.54376e+00,0.,5.)
spl_c3_2012_L0noTIS_narrow = RooRealVar("spl_c3_2012_L0noTIS_narrow","spl_c3_2012_L0noTIS_narrow",1.83198e+00,0.,5.)
spl_c4_2012_L0noTIS_narrow = RooRealVar("spl_c4_2012_L0noTIS_narrow","spl_c4_2012_L0noTIS_narrow",1.99918e+00,0.,5.)
spl_c5_2012_L0noTIS_narrow = RooRealVar("spl_c5_2012_L0noTIS_narrow","spl_c5_2012_L0noTIS_narrow",1.56178e+00,0.,5.)
spl_c6_2012_L0noTIS_narrow = RooRealVar("spl_c6_2012_L0noTIS_narrow","spl_c6_2012_L0noTIS_narrow",2.00961e+00,0.,5.)
spl_c7_2012_L0noTIS_narrow = RooRealVar("spl_c7_2012_L0noTIS_narrow","spl_c7_2012_L0noTIS_narrow",1.)

# Parameters of the effective acceptance used in toy MC generation.
k1_gen_wide = RooRealVar("k1_gen_wide","k1_gen_wide",-0.407189518759,-1.,1.)
k2_gen_wide = RooRealVar("k2_gen_wide","k2_gen_wide",-0.447514109157,-1.,1.)
k3_gen_wide = RooRealVar("k3_gen_wide","k3_gen_wide",-0.00934734637454,-1.,1.)
k4_gen_wide = RooRealVar("k4_gen_wide","k4_gen_wide",-0.0223113853263,-1.,1.)
k5_gen_wide = RooRealVar("k5_gen_wide","k5_gen_wide",0.0309083133084,-1.,1.)
p1_gen_wide = RooRealVar("p1_gen_wide","p1_gen_wide",-0.000136056558122,-1.,1.)
k1_gen_narrow = RooRealVar("k1_gen_narrow","k1_gen_narrow",-0.407189518759,-1.,1.)
k2_gen_narrow = RooRealVar("k2_gen_narrow","k2_gen_narrow",-0.447514109157,-1.,1.)
k3_gen_narrow = RooRealVar("k3_gen_narrow","k3_gen_narrow",-0.00934734637454,-1.,1.)
k4_gen_narrow = RooRealVar("k4_gen_narrow","k4_gen_narrow",-0.0223113853263,-1.,1.)
k5_gen_narrow = RooRealVar("k5_gen_narrow","k5_gen_narrow",0.0309083133084,-1.,1.)
p1_gen_narrow = RooRealVar("p1_gen_narrow","p1_gen_narrow",-0.000136056558122,-1.,1.)
spl_c0_gen_wide = RooRealVar("spl_c0_gen_wide","spl_c0_gen_wide",0.)
spl_c1_gen_wide = RooRealVar("spl_c1_gen_wide","spl_c1_gen_wide",-3.82452e-04,-1.,1.)
spl_c2_gen_wide = RooRealVar("spl_c2_gen_wide","spl_c2_gen_wide",9.88543e-01,0.,5.)
spl_c3_gen_wide = RooRealVar("spl_c3_gen_wide","spl_c3_gen_wide",1.28150e+00,0.,5.)
spl_c4_gen_wide = RooRealVar("spl_c4_gen_wide","spl_c4_gen_wide",1.38465e+00,0.,5.)
spl_c5_gen_wide = RooRealVar("spl_c5_gen_wide","spl_c5_gen_wide",1.38230e+00,0.,5.)
spl_c6_gen_wide = RooRealVar("spl_c6_gen_wide","spl_c6_gen_wide",1.36101e+00,0.,5.)
spl_c7_gen_wide = RooRealVar("spl_c7_gen_wide","spl_c7_gen_wide",1.)
spl_c0_gen_narrow = RooRealVar("spl_c0_gen_narrow","spl_c0_gen_narrow",0.)
spl_c1_gen_narrow = RooRealVar("spl_c1_gen_narrow","spl_c1_gen_narrow",-5.22921e-04,-1.,1.)
spl_c2_gen_narrow = RooRealVar("spl_c2_gen_narrow","spl_c2_gen_narrow",1.38881e+00,0.,5.)
spl_c3_gen_narrow = RooRealVar("spl_c3_gen_narrow","spl_c3_gen_narrow",1.67103e+00,0.,5.)
spl_c4_gen_narrow = RooRealVar("spl_c4_gen_narrow","spl_c4_gen_narrow",1.91227e+00,0.,5.)
spl_c5_gen_narrow = RooRealVar("spl_c5_gen_narrow","spl_c5_gen_narrow",1.53550e+00,0.,5.)
spl_c6_gen_narrow = RooRealVar("spl_c6_gen_narrow","spl_c6_gen_narrow",2.13463e+00,0.,5.)
spl_c7_gen_narrow = RooRealVar("spl_c7_gen_narrow","spl_c7_gen_narrow",1.)

# Accurate time integrals.
IT_cosh_accu_2011_L0TIS_wide = RooRealVar("IT_cosh_accu_2011_L0TIS_wide","IT_cosh_accu_2011_L0TIS_wide",1.)
IT_sinh_accu_2011_L0TIS_wide = RooRealVar("IT_sinh_accu_2011_L0TIS_wide","IT_sinh_accu_2011_L0TIS_wide",1.)
IT_cos_accu_2011_L0TIS_wide = RooRealVar("IT_cos_accu_2011_L0TIS_wide","IT_cos_accu_2011_L0TIS_wide",1.)
IT_sin_accu_2011_L0TIS_wide = RooRealVar("IT_sin_accu_2011_L0TIS_wide","IT_sin_accu_2011_L0TIS_wide",1.)
IT_cosh_accu_2012_L0TIS_wide = RooRealVar("IT_cosh_accu_2012_L0TIS_wide","IT_cosh_accu_2012_L0TIS_wide",1.)
IT_sinh_accu_2012_L0TIS_wide = RooRealVar("IT_sinh_accu_2012_L0TIS_wide","IT_sinh_accu_2012_L0TIS_wide",1.)
IT_cos_accu_2012_L0TIS_wide = RooRealVar("IT_cos_accu_2012_L0TIS_wide","IT_cos_accu_2012_L0TIS_wide",1.)
IT_sin_accu_2012_L0TIS_wide = RooRealVar("IT_sin_accu_2012_L0TIS_wide","IT_sin_accu_2012_L0TIS_wide",1.)
IT_cosh_accu_2011_L0TIS_narrow = RooRealVar("IT_cosh_accu_2011_L0TIS_narrow","IT_cosh_accu_2011_L0TIS_narrow",1.)
IT_sinh_accu_2011_L0TIS_narrow = RooRealVar("IT_sinh_accu_2011_L0TIS_narrow","IT_sinh_accu_2011_L0TIS_narrow",1.)
IT_cos_accu_2011_L0TIS_narrow = RooRealVar("IT_cos_accu_2011_L0TIS_narrow","IT_cos_accu_2011_L0TIS_narrow",1.)
IT_sin_accu_2011_L0TIS_narrow = RooRealVar("IT_sin_accu_2011_L0TIS_narrow","IT_sin_accu_2011_L0TIS_narrow",1.)
IT_cosh_accu_2012_L0TIS_narrow = RooRealVar("IT_cosh_accu_2012_L0TIS_narrow","IT_cosh_accu_2012_L0TIS_narrow",1.)
IT_sinh_accu_2012_L0TIS_narrow = RooRealVar("IT_sinh_accu_2012_L0TIS_narrow","IT_sinh_accu_2012_L0TIS_narrow",1.)
IT_cos_accu_2012_L0TIS_narrow = RooRealVar("IT_cos_accu_2012_L0TIS_narrow","IT_cos_accu_2012_L0TIS_narrow",1.)
IT_sin_accu_2012_L0TIS_narrow = RooRealVar("IT_sin_accu_2012_L0TIS_narrow","IT_sin_accu_2012_L0TIS_narrow",1.)
IT_cosh_accu_2011_L0noTIS_wide = RooRealVar("IT_cosh_accu_2011_L0noTIS_wide","IT_cosh_accu_2011_L0noTIS_wide",1.)
IT_sinh_accu_2011_L0noTIS_wide = RooRealVar("IT_sinh_accu_2011_L0noTIS_wide","IT_sinh_accu_2011_L0noTIS_wide",1.)
IT_cos_accu_2011_L0noTIS_wide = RooRealVar("IT_cos_accu_2011_L0noTIS_wide","IT_cos_accu_2011_L0noTIS_wide",1.)
IT_sin_accu_2011_L0noTIS_wide = RooRealVar("IT_sin_accu_2011_L0noTIS_wide","IT_sin_accu_2011_L0noTIS_wide",1.)
IT_cosh_accu_2012_L0noTIS_wide = RooRealVar("IT_cosh_accu_2012_L0noTIS_wide","IT_cosh_accu_2012_L0noTIS_wide",1.)
IT_sinh_accu_2012_L0noTIS_wide = RooRealVar("IT_sinh_accu_2012_L0noTIS_wide","IT_sinh_accu_2012_L0noTIS_wide",1.)
IT_cos_accu_2012_L0noTIS_wide = RooRealVar("IT_cos_accu_2012_L0noTIS_wide","IT_cos_accu_2012_L0noTIS_wide",1.)
IT_sin_accu_2012_L0noTIS_wide = RooRealVar("IT_sin_accu_2012_L0noTIS_wide","IT_sin_accu_2012_L0noTIS_wide",1.)
IT_cosh_accu_2011_L0noTIS_narrow = RooRealVar("IT_cosh_accu_2011_L0noTIS_narrow","IT_cosh_accu_2011_L0noTIS_narrow",1.)
IT_sinh_accu_2011_L0noTIS_narrow = RooRealVar("IT_sinh_accu_2011_L0noTIS_narrow","IT_sinh_accu_2011_L0noTIS_narrow",1.)
IT_cos_accu_2011_L0noTIS_narrow = RooRealVar("IT_cos_accu_2011_L0noTIS_narrow","IT_cos_accu_2011_L0noTIS_narrow",1.)
IT_sin_accu_2011_L0noTIS_narrow = RooRealVar("IT_sin_accu_2011_L0noTIS_narrow","IT_sin_accu_2011_L0noTIS_narrow",1.)
IT_cosh_accu_2012_L0noTIS_narrow = RooRealVar("IT_cosh_accu_2012_L0noTIS_narrow","IT_cosh_accu_2012_L0noTIS_narrow",1.)
IT_sinh_accu_2012_L0noTIS_narrow = RooRealVar("IT_sinh_accu_2012_L0noTIS_narrow","IT_sinh_accu_2012_L0noTIS_narrow",1.)
IT_cos_accu_2012_L0noTIS_narrow = RooRealVar("IT_cos_accu_2012_L0noTIS_narrow","IT_cos_accu_2012_L0noTIS_narrow",1.)
IT_sin_accu_2012_L0noTIS_narrow = RooRealVar("IT_sin_accu_2012_L0noTIS_narrow","IT_sin_accu_2012_L0noTIS_narrow",1.)

# More variables.
opt_acc = RooRealVar("opt_acc","opt_acc",1)
wide_window_MC = RooRealVar("wide_window_MC","wide_window_MC",1)
year_MC = RooRealVar("year_MC","year_MC",1)
opt_genmodel = RooRealVar("opt_genmodel","opt_genmodel",0)
opt_genvars = RooRealVar("opt_genvars","opt_genvars",1)
MCweight0 = RooRealVar("MCweight0","MCweight0",1.)
MCweight1 = RooRealVar("MCweight1","MCweight1",1.)
MCweight2 = RooRealVar("MCweight2","MCweight2",1.)
MCweight3 = RooRealVar("MCweight3","MCweight3",1.)
MCweight4 = RooRealVar("MCweight4","MCweight4",1.)

# Datasets.
data1_kpi1_2011_L0TIS_wide_ = RooDataSet("data1_kpi1_2011_L0TIS_wide_","data1_kpi1_2011_L0TIS_wide_",RooArgSet(mKp1_MC,MCweight1))
data1_kpi1_2012_L0TIS_wide_ = RooDataSet("data1_kpi1_2012_L0TIS_wide_","data1_kpi1_2012_L0TIS_wide_",RooArgSet(mKp1_MC,MCweight1))
data2_kpi1_2011_L0TIS_wide_ = RooDataSet("data2_kpi1_2011_L0TIS_wide_","data2_kpi1_2011_L0TIS_wide_",RooArgSet(cos1_MC,MCweight2))
data2_kpi1_2012_L0TIS_wide_ = RooDataSet("data2_kpi1_2012_L0TIS_wide_","data2_kpi1_2012_L0TIS_wide_",RooArgSet(cos1_MC,MCweight2))
data1_kpi2_2011_L0TIS_wide_ = RooDataSet("data1_kpi2_2011_L0TIS_wide_","data1_kpi2_2011_L0TIS_wide_",RooArgSet(mKp2_MC,MCweight1))
data1_kpi2_2012_L0TIS_wide_ = RooDataSet("data1_kpi2_2012_L0TIS_wide_","data1_kpi2_2012_L0TIS_wide_",RooArgSet(mKp2_MC,MCweight1))
data2_kpi2_2011_L0TIS_wide_ = RooDataSet("data2_kpi2_2011_L0TIS_wide_","data2_kpi2_2011_L0TIS_wide_",RooArgSet(cos2_MC,MCweight2))
data2_kpi2_2012_L0TIS_wide_ = RooDataSet("data2_kpi2_2012_L0TIS_wide_","data2_kpi2_2012_L0TIS_wide_",RooArgSet(cos2_MC,MCweight2))
data3_2011_L0TIS_wide_ = RooDataSet("data3_2011_L0TIS_wide_","data3_2011_L0TIS_wide_",RooArgSet(phi_MC,MCweight3))
data3_2012_L0TIS_wide_ = RooDataSet("data3_2012_L0TIS_wide_","data3_2012_L0TIS_wide_",RooArgSet(phi_MC,MCweight3))
data4_2011_L0TIS_wide_ = RooDataSet("data4_2011_L0TIS_wide_","data4_2011_L0TIS_wide_",RooArgSet(t_MC,MCweight4))
data4_2012_L0TIS_wide_ = RooDataSet("data4_2012_L0TIS_wide_","data4_2012_L0TIS_wide_",RooArgSet(t_MC,MCweight4))
data1_kpi1_2011_L0TIS_narrow_ = RooDataSet("data1_kpi1_2011_L0TIS_narrow_","data1_kpi1_2011_L0TIS_narrow_",RooArgSet(mKp1_narrow_MC,MCweight1))
data1_kpi1_2012_L0TIS_narrow_ = RooDataSet("data1_kpi1_2012_L0TIS_narrow_","data1_kpi1_2012_L0TIS_narrow_",RooArgSet(mKp1_narrow_MC,MCweight1))
data2_kpi1_2011_L0TIS_narrow_ = RooDataSet("data2_kpi1_2011_L0TIS_narrow_","data2_kpi1_2011_L0TIS_narrow_",RooArgSet(cos1_MC,MCweight2))
data2_kpi1_2012_L0TIS_narrow_ = RooDataSet("data2_kpi1_2012_L0TIS_narrow_","data2_kpi1_2012_L0TIS_narrow_",RooArgSet(cos1_MC,MCweight2))
data1_kpi2_2011_L0TIS_narrow_ = RooDataSet("data1_kpi2_2011_L0TIS_narrow_","data1_kpi2_2011_L0TIS_narrow_",RooArgSet(mKp2_narrow_MC,MCweight1))
data1_kpi2_2012_L0TIS_narrow_ = RooDataSet("data1_kpi2_2012_L0TIS_narrow_","data1_kpi2_2012_L0TIS_narrow_",RooArgSet(mKp2_narrow_MC,MCweight1))
data2_kpi2_2011_L0TIS_narrow_ = RooDataSet("data2_kpi2_2011_L0TIS_narrow_","data2_kpi2_2011_L0TIS_narrow_",RooArgSet(cos2_MC,MCweight2))
data2_kpi2_2012_L0TIS_narrow_ = RooDataSet("data2_kpi2_2012_L0TIS_narrow_","data2_kpi2_2012_L0TIS_narrow_",RooArgSet(cos2_MC,MCweight2))
data3_2011_L0TIS_narrow_ = RooDataSet("data3_2011_L0TIS_narrow_","data3_2011_L0TIS_narrow_",RooArgSet(phi_MC,MCweight3))
data3_2012_L0TIS_narrow_ = RooDataSet("data3_2012_L0TIS_narrow_","data3_2012_L0TIS_narrow_",RooArgSet(phi_MC,MCweight3))
data4_2011_L0TIS_narrow_ = RooDataSet("data4_2011_L0TIS_narrow_","data4_2011_L0TIS_narrow_",RooArgSet(t_MC,MCweight4))
data4_2012_L0TIS_narrow_ = RooDataSet("data4_2012_L0TIS_narrow_","data4_2012_L0TIS_narrow_",RooArgSet(t_MC,MCweight4))
data1_kpi1_2011_L0noTIS_wide_ = RooDataSet("data1_kpi1_2011_L0noTIS_wide_","data1_kpi1_2011_L0noTIS_wide_",RooArgSet(mKp1_MC,MCweight1))
data1_kpi1_2012_L0noTIS_wide_ = RooDataSet("data1_kpi1_2012_L0noTIS_wide_","data1_kpi1_2012_L0noTIS_wide_",RooArgSet(mKp1_MC,MCweight1))
data2_kpi1_2011_L0noTIS_wide_ = RooDataSet("data2_kpi1_2011_L0noTIS_wide_","data2_kpi1_2011_L0noTIS_wide_",RooArgSet(cos1_MC,MCweight2))
data2_kpi1_2012_L0noTIS_wide_ = RooDataSet("data2_kpi1_2012_L0noTIS_wide_","data2_kpi1_2012_L0noTIS_wide_",RooArgSet(cos1_MC,MCweight2))
data1_kpi2_2011_L0noTIS_wide_ = RooDataSet("data1_kpi2_2011_L0noTIS_wide_","data1_kpi2_2011_L0noTIS_wide_",RooArgSet(mKp2_MC,MCweight1))
data1_kpi2_2012_L0noTIS_wide_ = RooDataSet("data1_kpi2_2012_L0noTIS_wide_","data1_kpi2_2012_L0noTIS_wide_",RooArgSet(mKp2_MC,MCweight1))
data2_kpi2_2011_L0noTIS_wide_ = RooDataSet("data2_kpi2_2011_L0noTIS_wide_","data2_kpi2_2011_L0noTIS_wide_",RooArgSet(cos2_MC,MCweight2))
data2_kpi2_2012_L0noTIS_wide_ = RooDataSet("data2_kpi2_2012_L0noTIS_wide_","data2_kpi2_2012_L0noTIS_wide_",RooArgSet(cos2_MC,MCweight2))
data3_2011_L0noTIS_wide_ = RooDataSet("data3_2011_L0noTIS_wide_","data3_2011_L0noTIS_wide_",RooArgSet(phi_MC,MCweight3))
data3_2012_L0noTIS_wide_ = RooDataSet("data3_2012_L0noTIS_wide_","data3_2012_L0noTIS_wide_",RooArgSet(phi_MC,MCweight3))
data4_2011_L0noTIS_wide_ = RooDataSet("data4_2011_L0noTIS_wide_","data4_2011_L0noTIS_wide_",RooArgSet(t_MC,MCweight4))
data4_2012_L0noTIS_wide_ = RooDataSet("data4_2012_L0noTIS_wide_","data4_2012_L0noTIS_wide_",RooArgSet(t_MC,MCweight4))
data1_kpi1_2011_L0noTIS_narrow_ = RooDataSet("data1_kpi1_2011_L0noTIS_narrow_","data1_kpi1_2011_L0noTIS_narrow_",RooArgSet(mKp1_narrow_MC,MCweight1))
data1_kpi1_2012_L0noTIS_narrow_ = RooDataSet("data1_kpi1_2012_L0noTIS_narrow_","data1_kpi1_2012_L0noTIS_narrow_",RooArgSet(mKp1_narrow_MC,MCweight1))
data2_kpi1_2011_L0noTIS_narrow_ = RooDataSet("data2_kpi1_2011_L0noTIS_narrow_","data2_kpi1_2011_L0noTIS_narrow_",RooArgSet(cos1_MC,MCweight2))
data2_kpi1_2012_L0noTIS_narrow_ = RooDataSet("data2_kpi1_2012_L0noTIS_narrow_","data2_kpi1_2012_L0noTIS_narrow_",RooArgSet(cos1_MC,MCweight2))
data1_kpi2_2011_L0noTIS_narrow_ = RooDataSet("data1_kpi2_2011_L0noTIS_narrow_","data1_kpi2_2011_L0noTIS_narrow_",RooArgSet(mKp2_narrow_MC,MCweight1))
data1_kpi2_2012_L0noTIS_narrow_ = RooDataSet("data1_kpi2_2012_L0noTIS_narrow_","data1_kpi2_2012_L0noTIS_narrow_",RooArgSet(mKp2_narrow_MC,MCweight1))
data2_kpi2_2011_L0noTIS_narrow_ = RooDataSet("data2_kpi2_2011_L0noTIS_narrow_","data2_kpi2_2011_L0noTIS_narrow_",RooArgSet(cos2_MC,MCweight2))
data2_kpi2_2012_L0noTIS_narrow_ = RooDataSet("data2_kpi2_2012_L0noTIS_narrow_","data2_kpi2_2012_L0noTIS_narrow_",RooArgSet(cos2_MC,MCweight2))
data3_2011_L0noTIS_narrow_ = RooDataSet("data3_2011_L0noTIS_narrow_","data3_2011_L0noTIS_narrow_",RooArgSet(phi_MC,MCweight3))
data3_2012_L0noTIS_narrow_ = RooDataSet("data3_2012_L0noTIS_narrow_","data3_2012_L0noTIS_narrow_",RooArgSet(phi_MC,MCweight3))
data4_2011_L0noTIS_narrow_ = RooDataSet("data4_2011_L0noTIS_narrow_","data4_2011_L0noTIS_narrow_",RooArgSet(t_MC,MCweight4))
data4_2012_L0noTIS_narrow_ = RooDataSet("data4_2012_L0noTIS_narrow_","data4_2012_L0noTIS_narrow_",RooArgSet(t_MC,MCweight4))
data1_kpi1_gen_wide_ = RooDataSet("data1_kpi1_gen_wide_","data1_kpi1_gen_wide_",RooArgSet(mKp1_MC,MCweight1))
data1_kpi2_gen_wide_ = RooDataSet("data1_kpi2_gen_wide_","data1_kpi2_gen_wide_",RooArgSet(mKp2_MC,MCweight1))
data2_kpi1_gen_wide_ = RooDataSet("data2_kpi1_gen_wide_","data2_kpi1_gen_wide_",RooArgSet(cos1_MC,MCweight2))
data2_kpi2_gen_wide_ = RooDataSet("data2_kpi2_gen_wide_","data2_kpi2_gen_wide_",RooArgSet(cos2_MC,MCweight2))
data4_gen_wide_ = RooDataSet("data4_gen_wide_","data4_gen_wide_",RooArgSet(t_MC,MCweight4))
data1_kpi1_gen_narrow_ = RooDataSet("data1_kpi1_gen_narrow_","data1_kpi1_gen_narrow_",RooArgSet(mKp1_narrow_MC,MCweight1))
data1_kpi2_gen_narrow_ = RooDataSet("data1_kpi2_gen_narrow_","data1_kpi2_gen_narrow_",RooArgSet(mKp2_narrow_MC,MCweight1))
data2_kpi1_gen_narrow_ = RooDataSet("data2_kpi1_gen_narrow_","data2_kpi1_gen_narrow_",RooArgSet(cos1_MC,MCweight2))
data2_kpi2_gen_narrow_ = RooDataSet("data2_kpi2_gen_narrow_","data2_kpi2_gen_narrow_",RooArgSet(cos2_MC,MCweight2))
data4_gen_narrow_ = RooDataSet("data4_gen_narrow_","data4_gen_narrow_",RooArgSet(t_MC,MCweight4))

# Frames.
frame_m1_MC_2011_L0TIS_wide = mKp1_MC.frame(RooFit.Title("m1_2011_L0TIS_wide"))
frame_m2_MC_2011_L0TIS_wide = mKp2_MC.frame(RooFit.Title("m2_2011_L0TIS_wide"))
frame_cos1_MC_2011_L0TIS_wide = cos1_MC.frame(RooFit.Title("cos1_2011_L0TIS_wide"))
frame_cos2_MC_2011_L0TIS_wide = cos2_MC.frame(RooFit.Title("cos2_2011_L0TIS_wide"))
frame_phi_MC_2011_L0TIS_wide = phi_MC.frame(RooFit.Title("phi_2011_L0TIS_wide"))
frame_t_MC_2011_L0TIS_wide = t_MC.frame(RooFit.Title("t_2011_L0TIS_wide"))
frame_m1_MC_2012_L0TIS_wide = mKp1_MC.frame(RooFit.Title("m1_2012_L0TIS_wide"))
frame_m2_MC_2012_L0TIS_wide = mKp2_MC.frame(RooFit.Title("m2_2012_L0TIS_wide"))
frame_cos1_MC_2012_L0TIS_wide = cos1_MC.frame(RooFit.Title("cos1_2012_L0TIS_wide"))
frame_cos2_MC_2012_L0TIS_wide = cos2_MC.frame(RooFit.Title("cos2_2012_L0TIS_wide"))
frame_phi_MC_2012_L0TIS_wide = phi_MC.frame(RooFit.Title("phi_2012_L0TIS_wide"))
frame_t_MC_2012_L0TIS_wide = t_MC.frame(RooFit.Title("t_2012_L0TIS_wide"))
frame_m1_MC_2011_L0TIS_narrow = mKp1_narrow_MC.frame(RooFit.Title("m1_2011_L0TIS_narrow"))
frame_m2_MC_2011_L0TIS_narrow = mKp2_narrow_MC.frame(RooFit.Title("m2_2011_L0TIS_narrow"))
frame_cos1_MC_2011_L0TIS_narrow = cos1_MC.frame(RooFit.Title("cos1_2011_L0TIS_narrow"))
frame_cos2_MC_2011_L0TIS_narrow = cos2_MC.frame(RooFit.Title("cos2_2011_L0TIS_narrow"))
frame_phi_MC_2011_L0TIS_narrow = phi_MC.frame(RooFit.Title("phi_2011_L0TIS_narrow"))
frame_t_MC_2011_L0TIS_narrow = t_MC.frame(RooFit.Title("t_2011_L0TIS_narrow"))
frame_m1_MC_2012_L0TIS_narrow = mKp1_narrow_MC.frame(RooFit.Title("m1_2012_L0TIS_narrow"))
frame_m2_MC_2012_L0TIS_narrow = mKp2_narrow_MC.frame(RooFit.Title("m2_2012_L0TIS_narrow"))
frame_cos1_MC_2012_L0TIS_narrow = cos1_MC.frame(RooFit.Title("cos1_2012_L0TIS_narrow"))
frame_cos2_MC_2012_L0TIS_narrow = cos2_MC.frame(RooFit.Title("cos2_2012_L0TIS_narrow"))
frame_phi_MC_2012_L0TIS_narrow = phi_MC.frame(RooFit.Title("phi_2012_L0TIS_narrow"))
frame_t_MC_2012_L0TIS_narrow = t_MC.frame(RooFit.Title("t_2012_L0TIS_narrow"))
frame_m1_MC_2011_L0noTIS_wide = mKp1_MC.frame(RooFit.Title("m1_2011_L0noTIS_wide"))
frame_m2_MC_2011_L0noTIS_wide = mKp2_MC.frame(RooFit.Title("m2_2011_L0noTIS_wide"))
frame_cos1_MC_2011_L0noTIS_wide = cos1_MC.frame(RooFit.Title("cos1_2011_L0noTIS_wide"))
frame_cos2_MC_2011_L0noTIS_wide = cos2_MC.frame(RooFit.Title("cos2_2011_L0noTIS_wide"))
frame_phi_MC_2011_L0noTIS_wide = phi_MC.frame(RooFit.Title("phi_2011_L0noTIS_wide"))
frame_t_MC_2011_L0noTIS_wide = t_MC.frame(RooFit.Title("t_2011_L0noTIS_wide"))
frame_m1_MC_2012_L0noTIS_wide = mKp1_MC.frame(RooFit.Title("m1_2012_L0noTIS_wide"))
frame_m2_MC_2012_L0noTIS_wide = mKp2_MC.frame(RooFit.Title("m2_2012_L0noTIS_wide"))
frame_cos1_MC_2012_L0noTIS_wide = cos1_MC.frame(RooFit.Title("cos1_2012_L0noTIS_wide"))
frame_cos2_MC_2012_L0noTIS_wide = cos2_MC.frame(RooFit.Title("cos2_2012_L0noTIS_wide"))
frame_phi_MC_2012_L0noTIS_wide = phi_MC.frame(RooFit.Title("phi_2012_L0noTIS_wide"))
frame_t_MC_2012_L0noTIS_wide = t_MC.frame(RooFit.Title("t_2012_L0noTIS_wide"))
frame_m1_MC_2011_L0noTIS_narrow = mKp1_narrow_MC.frame(RooFit.Title("m1_2011_L0noTIS_narrow"))
frame_m2_MC_2011_L0noTIS_narrow = mKp2_narrow_MC.frame(RooFit.Title("m2_2011_L0noTIS_narrow"))
frame_cos1_MC_2011_L0noTIS_narrow = cos1_MC.frame(RooFit.Title("cos1_2011_L0noTIS_narrow"))
frame_cos2_MC_2011_L0noTIS_narrow = cos2_MC.frame(RooFit.Title("cos2_2011_L0noTIS_narrow"))
frame_phi_MC_2011_L0noTIS_narrow = phi_MC.frame(RooFit.Title("phi_2011_L0noTIS_narrow"))
frame_t_MC_2011_L0noTIS_narrow = t_MC.frame(RooFit.Title("t_2011_L0noTIS_narrow"))
frame_m1_MC_2012_L0noTIS_narrow = mKp1_narrow_MC.frame(RooFit.Title("m1_2012_L0noTIS_narrow"))
frame_m2_MC_2012_L0noTIS_narrow = mKp2_narrow_MC.frame(RooFit.Title("m2_2012_L0noTIS_narrow"))
frame_cos1_MC_2012_L0noTIS_narrow = cos1_MC.frame(RooFit.Title("cos1_2012_L0noTIS_narrow"))
frame_cos2_MC_2012_L0noTIS_narrow = cos2_MC.frame(RooFit.Title("cos2_2012_L0noTIS_narrow"))
frame_phi_MC_2012_L0noTIS_narrow = phi_MC.frame(RooFit.Title("phi_2012_L0noTIS_narrow"))
frame_t_MC_2012_L0noTIS_narrow = t_MC.frame(RooFit.Title("t_2012_L0noTIS_narrow"))
frame_m1_MC_gen_wide = mKp1_MC.frame(RooFit.Title("m1_gen_wide"))
frame_m2_MC_gen_wide = mKp2_MC.frame(RooFit.Title("m2_gen_wide"))
frame_cos1_MC_gen_wide = cos1_MC.frame(RooFit.Title("cos1_gen_wide"))
frame_cos2_MC_gen_wide = cos2_MC.frame(RooFit.Title("cos2_gen_wide"))
frame_t_MC_gen_wide = t_MC.frame(RooFit.Title("t_gen_wide"))
frame_m1_MC_gen_narrow = mKp1_narrow_MC.frame(RooFit.Title("m1_gen_narrow"))
frame_m2_MC_gen_narrow = mKp2_narrow_MC.frame(RooFit.Title("m2_gen_narrow"))
frame_cos1_MC_gen_narrow = cos1_MC.frame(RooFit.Title("cos1_gen_narrow"))
frame_cos2_MC_gen_narrow = cos2_MC.frame(RooFit.Title("cos2_gen_narrow"))
frame_t_MC_gen_narrow = t_MC.frame(RooFit.Title("t_gen_narrow"))


# ################################################################
# F U N C T I O N S
# ################################################################


def MCsetcut(year_aux,trig_aux,set_aux):
	if trig_aux == 0: cut_aux = "B_s0_L0Global_TIS==1 && "
	else: cut_aux = "B_s0_L0Global_TIS==0 && B_s0_L0HadronDecision_TOS==1 && "
	if year_aux == 0:
		if set_aux == 0: cut_aux += "itype==-73"
		elif set_aux == 1: cut_aux += "itype==-70"
		else: cut_aux += "(itype==-73 || itype==-70)"
	else:
		if set_aux == 0: cut_aux += "itype==-83"
		elif set_aux == 1: cut_aux += "itype==-80"
		else: cut_aux += "(itype==-83 || itype==-80)"
	return cut_aux


def MC2012settype(set_aux):
	if set_aux == 0: return "itype==-83"
	elif set_aux == 1: return "itype==-80"
	else: return "(itype==-83 || itype==-80)"


def MCtruth(ev):
	if abs(ev.B_s0_TRUEID) == 531:
		if ev.Kplus_TRUEID == 321:
			if ev.Kminus_TRUEID == -321:
				if ev.Piplus_TRUEID == 211:
					if ev.Piminus_TRUEID == -211: return 1
	return 0


def boolj1j2h(j1,j2,h):

	if ((j1 == 0) and (j2 == 0) and (h == 0)): return 1
	if ((j1 == 0) and (j2 == 1) and (h == 0)): return 1
	if ((j1 == 0) and (j2 == 2) and (h == 0)): return 1
	if ((j1 == 1) and (j2 == 0) and (h == 0)): return 1
	if ((j1 == 1) and (j2 == 1) and (h == 0)): return 1
	if ((j1 == 1) and (j2 == 1) and (h == 1)): return 1
	if ((j1 == 1) and (j2 == 1) and (h == 2)): return 1
	if ((j1 == 1) and (j2 == 2) and (h == 0)): return 1
	if ((j1 == 1) and (j2 == 2) and (h == 1)): return 1
	if ((j1 == 1) and (j2 == 2) and (h == 2)): return 1
	if ((j1 == 2) and (j2 == 0) and (h == 0)): return 1
	if ((j1 == 2) and (j2 == 1) and (h == 0)): return 1
	if ((j1 == 2) and (j2 == 1) and (h == 1)): return 1
	if ((j1 == 2) and (j2 == 1) and (h == 2)): return 1
	if ((j1 == 2) and (j2 == 2) and (h == 0)): return 1
	if ((j1 == 2) and (j2 == 2) and (h == 1)): return 1
	if ((j1 == 2) and (j2 == 2) and (h == 2)): return 1
	if ((j1 == 2) and (j2 == 2) and (h == 3)): return 1
	if ((j1 == 2) and (j2 == 2) and (h == 4)): return 1
	return 0


def boolj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp): 
	 return boolj1j2h(j1,j2,h)*boolj1j2h(j1p,j2p,hp)


# Structure to translate between extended index j1j2hj1pj2phppart and reduced index i.
indexdictextred = {}
indexdictredext = {}
index = 0
for j1 in range(3):
	for j2 in range(3):
		for h in range(5):
			for j1p in range(3):
				for j2p in range(3):
					for hp in range(5):
						for part in range(2):
							if ((boolj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp) == 1) and ((j1p+3*j2p+9*hp) <= (j1+3*j2+9*h))):
								indexdictextred[str(j1)+str(j2)+str(h)+str(j1p)+str(j2p)+str(hp)+str(part)] = index
								indexdictredext[index] = str(j1)+str(j2)+str(h)+str(j1p)+str(j2p)+str(hp)+str(part)
								index += 1
def redindex(j1,j2,h,j1p,j2p,hp,part):
	return indexdictextred[str(j1)+str(j2)+str(h)+str(j1p)+str(j2p)+str(hp)+str(part)]
def extindex(i):
	stringlist = list(indexdictredext[i])
	intlist = []
	for s in stringlist: intlist.append(eval(s))
	return intlist


# Matrix structure for the computation of the normalization weights.
sumi = [[[[],[]],[[],[]]],[[[],[]],[[],[]]]]
sumij = [[[[],[]],[[],[]]],[[[],[]],[[],[]]]]
NWi = [[[[],[]],[[],[]]],[[[],[]],[[],[]]]]
eNWi = [[[[],[]],[[],[]]],[[[],[]],[[],[]]]]
covij = [[[[],[]],[[],[]]],[[[],[]],[[],[]]]]
addzero = lambda x: x.append(0)
addlist = lambda x: x.append([])
for year in range(2):
	for trigger in range(2):
		for window in range(2):
			for i in range(380):
				map(addzero,[sumi[year][trigger][window],NWi[year][trigger][window],eNWi[year][trigger][window]])
				map(addlist,[sumij[year][trigger][window],covij[year][trigger][window]])
				for j in range(380): map(addzero,[sumij[year][trigger][window][i],covij[year][trigger][window][i]])


def CreateGenPDF():

	PDF_gen = MCGenComb("PDF_gen","PDF_gen",opt_genmodel,year_MC,wide_window_MC,mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,opt_genvars)

	return PDF_gen


def CreateAccPDF():

	PDF_acc_2011_L0TIS_wide = accpdf("PDF_acc_2011_L0TIS_wide","PDF_acc_2011_L0TIS_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0TIS_wide,k2_2011_L0TIS_wide,k3_2011_L0TIS_wide,k4_2011_L0TIS_wide,k5_2011_L0TIS_wide,p1_2011_L0TIS_wide,a_acc_2011_L0TIS_wide,b_acc_2011_L0TIS_wide,c_acc_2011_L0TIS_wide,RooFit.RooConst(0),opt_acc)
	model_acc_2011_L0TIS_wide = RooRealSumPdf("model_acc_2011_L0TIS_wide","model_acc_2011_L0TIS_wide",RooArgList(PDF_acc_2011_L0TIS_wide),RooArgList(one))
	PDF_acc_2012_L0TIS_wide = accpdf("PDF_acc_2012_L0TIS_wide","PDF_acc_2012_L0TIS_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_L0TIS_wide,k2_2012_L0TIS_wide,k3_2012_L0TIS_wide,k4_2012_L0TIS_wide,k5_2012_L0TIS_wide,p1_2012_L0TIS_wide,a_acc_2012_L0TIS_wide,b_acc_2012_L0TIS_wide,c_acc_2012_L0TIS_wide,RooFit.RooConst(0),opt_acc)
	model_acc_2012_L0TIS_wide = RooRealSumPdf("model_acc_2012_L0TIS_wide","model_acc_2012_L0TIS_wide",RooArgList(PDF_acc_2012_L0TIS_wide),RooArgList(one))
	PDF_acc_2011_L0TIS_narrow = accpdf("PDF_acc_2011_L0TIS_narrow","PDF_acc_2011_L0TIS_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0TIS_narrow,k2_2011_L0TIS_narrow,k3_2011_L0TIS_narrow,k4_2011_L0TIS_narrow,k5_2011_L0TIS_narrow,p1_2011_L0TIS_narrow,a_acc_2011_L0TIS_narrow,b_acc_2011_L0TIS_narrow,c_acc_2011_L0TIS_narrow,RooFit.RooConst(0),opt_acc)
	model_acc_2011_L0TIS_narrow = RooRealSumPdf("model_acc_2011_L0TIS_narrow","model_acc_2011_L0TIS_narrow",RooArgList(PDF_acc_2011_L0TIS_narrow),RooArgList(one))
	PDF_acc_2012_L0TIS_narrow = accpdf("PDF_acc_2012_L0TIS_narrow","PDF_acc_2012_L0TIS_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_L0TIS_narrow,k2_2012_L0TIS_narrow,k3_2012_L0TIS_narrow,k4_2012_L0TIS_narrow,k5_2012_L0TIS_narrow,p1_2012_L0TIS_narrow,a_acc_2012_L0TIS_narrow,b_acc_2012_L0TIS_narrow,c_acc_2012_L0TIS_narrow,RooFit.RooConst(0),opt_acc)
	model_acc_2012_L0TIS_narrow = RooRealSumPdf("model_acc_2012_L0TIS_narrow","model_acc_2012_L0TIS_narrow",RooArgList(PDF_acc_2012_L0TIS_narrow),RooArgList(one))
	PDF_acc_2011_L0noTIS_wide = accpdf("PDF_acc_2011_L0noTIS_wide","PDF_acc_2011_L0noTIS_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0noTIS_wide,k2_2011_L0noTIS_wide,k3_2011_L0noTIS_wide,k4_2011_L0noTIS_wide,k5_2011_L0noTIS_wide,p1_2011_L0noTIS_wide,a_acc_2011_L0noTIS_wide,b_acc_2011_L0noTIS_wide,c_acc_2011_L0noTIS_wide,RooFit.RooConst(0),opt_acc)
	model_acc_2011_L0noTIS_wide = RooRealSumPdf("model_acc_2011_L0noTIS_wide","model_acc_2011_L0noTIS_wide",RooArgList(PDF_acc_2011_L0noTIS_wide),RooArgList(one))
	PDF_acc_2012_L0noTIS_wide = accpdf("PDF_acc_2012_L0noTIS_wide","PDF_acc_2012_L0noTIS_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_L0noTIS_wide,k2_2012_L0noTIS_wide,k3_2012_L0noTIS_wide,k4_2012_L0noTIS_wide,k5_2012_L0noTIS_wide,p1_2012_L0noTIS_wide,a_acc_2012_L0noTIS_wide,b_acc_2012_L0noTIS_wide,c_acc_2012_L0noTIS_wide,RooFit.RooConst(0),opt_acc)
	model_acc_2012_L0noTIS_wide = RooRealSumPdf("model_acc_2012_L0noTIS_wide","model_acc_2012_L0noTIS_wide",RooArgList(PDF_acc_2012_L0noTIS_wide),RooArgList(one))
	PDF_acc_2011_L0noTIS_narrow = accpdf("PDF_acc_2011_L0noTIS_narrow","PDF_acc_2011_L0noTIS_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0noTIS_narrow,k2_2011_L0noTIS_narrow,k3_2011_L0noTIS_narrow,k4_2011_L0noTIS_narrow,k5_2011_L0noTIS_narrow,p1_2011_L0noTIS_narrow,a_acc_2011_L0noTIS_narrow,b_acc_2011_L0noTIS_narrow,c_acc_2011_L0noTIS_narrow,RooFit.RooConst(0),opt_acc)
	model_acc_2011_L0noTIS_narrow = RooRealSumPdf("model_acc_2011_L0noTIS_narrow","model_acc_2011_L0noTIS_narrow",RooArgList(PDF_acc_2011_L0noTIS_narrow),RooArgList(one))
	PDF_acc_2012_L0noTIS_narrow = accpdf("PDF_acc_2012_L0noTIS_narrow","PDF_acc_2012_L0noTIS_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_L0noTIS_narrow,k2_2012_L0noTIS_narrow,k3_2012_L0noTIS_narrow,k4_2012_L0noTIS_narrow,k5_2012_L0noTIS_narrow,p1_2012_L0noTIS_narrow,a_acc_2012_L0noTIS_narrow,b_acc_2012_L0noTIS_narrow,c_acc_2012_L0noTIS_narrow,RooFit.RooConst(0),opt_acc)
	model_acc_2012_L0noTIS_narrow = RooRealSumPdf("model_acc_2012_L0noTIS_narrow","model_acc_2012_L0noTIS_narrow",RooArgList(PDF_acc_2012_L0noTIS_narrow),RooArgList(one))
	PDF_acc_kpi1_2011_L0TIS_wide = accpdf("PDF_acc_kpi1_2011_L0TIS_wide","PDF_acc_kpi1_2011_L0TIS_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0TIS_wide,k2_2011_L0TIS_wide,k3_2011_L0TIS_wide,k4_2011_L0TIS_wide,k5_2011_L0TIS_wide,p1_2011_L0TIS_wide,a_acc_2011_L0TIS_wide,b_acc_2011_L0TIS_wide,c_acc_2011_L0TIS_wide,RooFit.RooConst(1),opt_acc)
	model_acc_kpi1_2011_L0TIS_wide = RooRealSumPdf("model_acc_kpi1_2011_L0TIS_wide","model_acc_kpi1_2011_L0TIS_wide",RooArgList(PDF_acc_kpi1_2011_L0TIS_wide),RooArgList(one))
	PDF_acc_kpi1_2012_L0TIS_wide = accpdf("PDF_acc_kpi1_2012_L0TIS_wide","PDF_acc_kpi1_2012_L0TIS_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_L0TIS_wide,k2_2012_L0TIS_wide,k3_2012_L0TIS_wide,k4_2012_L0TIS_wide,k5_2012_L0TIS_wide,p1_2012_L0TIS_wide,a_acc_2012_L0TIS_wide,b_acc_2012_L0TIS_wide,c_acc_2012_L0TIS_wide,RooFit.RooConst(1),opt_acc)
	model_acc_kpi1_2012_L0TIS_wide = RooRealSumPdf("model_acc_kpi1_2012_L0TIS_wide","model_acc_kpi1_2012_L0TIS_wide",RooArgList(PDF_acc_kpi1_2012_L0TIS_wide),RooArgList(one))
	PDF_acc_kpi1_2011_L0TIS_narrow = accpdf("PDF_acc_kpi1_2011_L0TIS_narrow","PDF_acc_kpi1_2011_L0TIS_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0TIS_narrow,k2_2011_L0TIS_narrow,k3_2011_L0TIS_narrow,k4_2011_L0TIS_narrow,k5_2011_L0TIS_narrow,p1_2011_L0TIS_narrow,a_acc_2011_L0TIS_narrow,b_acc_2011_L0TIS_narrow,c_acc_2011_L0TIS_narrow,RooFit.RooConst(1),opt_acc)
	model_acc_kpi1_2011_L0TIS_narrow = RooRealSumPdf("model_acc_kpi1_2011_L0TIS_narrow","model_acc_kpi1_2011_L0TIS_narrow",RooArgList(PDF_acc_kpi1_2011_L0TIS_narrow),RooArgList(one))
	PDF_acc_kpi1_2012_L0TIS_narrow = accpdf("PDF_acc_kpi1_2012_L0TIS_narrow","PDF_acc_kpi1_2012_L0TIS_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_L0TIS_narrow,k2_2012_L0TIS_narrow,k3_2012_L0TIS_narrow,k4_2012_L0TIS_narrow,k5_2012_L0TIS_narrow,p1_2012_L0TIS_narrow,a_acc_2012_L0TIS_narrow,b_acc_2012_L0TIS_narrow,c_acc_2012_L0TIS_narrow,RooFit.RooConst(1),opt_acc)
	model_acc_kpi1_2012_L0TIS_narrow = RooRealSumPdf("model_acc_kpi1_2012_L0TIS_narrow","model_acc_kpi1_2012_L0TIS_narrow",RooArgList(PDF_acc_kpi1_2012_L0TIS_narrow),RooArgList(one))
	PDF_acc_kpi1_2011_L0noTIS_wide = accpdf("PDF_acc_kpi1_2011_L0noTIS_wide","PDF_acc_kpi1_2011_L0noTIS_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0noTIS_wide,k2_2011_L0noTIS_wide,k3_2011_L0noTIS_wide,k4_2011_L0noTIS_wide,k5_2011_L0noTIS_wide,p1_2011_L0noTIS_wide,a_acc_2011_L0noTIS_wide,b_acc_2011_L0noTIS_wide,c_acc_2011_L0noTIS_wide,RooFit.RooConst(1),opt_acc)
	model_acc_kpi1_2011_L0noTIS_wide = RooRealSumPdf("model_acc_kpi1_2011_L0noTIS_wide","model_acc_kpi1_2011_L0noTIS_wide",RooArgList(PDF_acc_kpi1_2011_L0noTIS_wide),RooArgList(one))
	PDF_acc_kpi1_2012_L0noTIS_wide = accpdf("PDF_acc_kpi1_2012_L0noTIS_wide","PDF_acc_kpi1_2012_L0noTIS_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_L0noTIS_wide,k2_2012_L0noTIS_wide,k3_2012_L0noTIS_wide,k4_2012_L0noTIS_wide,k5_2012_L0noTIS_wide,p1_2012_L0noTIS_wide,a_acc_2012_L0noTIS_wide,b_acc_2012_L0noTIS_wide,c_acc_2012_L0noTIS_wide,RooFit.RooConst(1),opt_acc)
	model_acc_kpi1_2012_L0noTIS_wide = RooRealSumPdf("model_acc_kpi1_2012_L0noTIS_wide","model_acc_kpi1_2012_L0noTIS_wide",RooArgList(PDF_acc_kpi1_2012_L0noTIS_wide),RooArgList(one))
	PDF_acc_kpi1_2011_L0noTIS_narrow = accpdf("PDF_acc_kpi1_2011_L0noTIS_narrow","PDF_acc_kpi1_2011_L0noTIS_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0noTIS_narrow,k2_2011_L0noTIS_narrow,k3_2011_L0noTIS_narrow,k4_2011_L0noTIS_narrow,k5_2011_L0noTIS_narrow,p1_2011_L0noTIS_narrow,a_acc_2011_L0noTIS_narrow,b_acc_2011_L0noTIS_narrow,c_acc_2011_L0noTIS_narrow,RooFit.RooConst(1),opt_acc)
	model_acc_kpi1_2011_L0noTIS_narrow = RooRealSumPdf("model_acc_kpi1_2011_L0noTIS_narrow","model_acc_kpi1_2011_L0noTIS_narrow",RooArgList(PDF_acc_kpi1_2011_L0noTIS_narrow),RooArgList(one))
	PDF_acc_kpi1_2012_L0noTIS_narrow = accpdf("PDF_acc_kpi1_2012_L0noTIS_narrow","PDF_acc_kpi1_2012_L0noTIS_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_L0noTIS_narrow,k2_2012_L0noTIS_narrow,k3_2012_L0noTIS_narrow,k4_2012_L0noTIS_narrow,k5_2012_L0noTIS_narrow,p1_2012_L0noTIS_narrow,a_acc_2012_L0noTIS_narrow,b_acc_2012_L0noTIS_narrow,c_acc_2012_L0noTIS_narrow,RooFit.RooConst(1),opt_acc)
	model_acc_kpi1_2012_L0noTIS_narrow = RooRealSumPdf("model_acc_kpi1_2012_L0noTIS_narrow","model_acc_kpi1_2012_L0noTIS_narrow",RooArgList(PDF_acc_kpi1_2012_L0noTIS_narrow),RooArgList(one))
	PDF_acc_kpi2_2011_L0TIS_wide = accpdf("PDF_acc_kpi2_2011_L0TIS_wide","PDF_acc_kpi2_2011_L0TIS_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0TIS_wide,k2_2011_L0TIS_wide,k3_2011_L0TIS_wide,k4_2011_L0TIS_wide,k5_2011_L0TIS_wide,p1_2011_L0TIS_wide,a_acc_2011_L0TIS_wide,b_acc_2011_L0TIS_wide,c_acc_2011_L0TIS_wide,RooFit.RooConst(2),opt_acc)
	model_acc_kpi2_2011_L0TIS_wide = RooRealSumPdf("model_acc_kpi2_2011_L0TIS_wide","model_acc_kpi2_2011_L0TIS_wide",RooArgList(PDF_acc_kpi2_2011_L0TIS_wide),RooArgList(one))
	PDF_acc_kpi2_2012_L0TIS_wide = accpdf("PDF_acc_kpi2_2012_L0TIS_wide","PDF_acc_kpi2_2012_L0TIS_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_L0TIS_wide,k2_2012_L0TIS_wide,k3_2012_L0TIS_wide,k4_2012_L0TIS_wide,k5_2012_L0TIS_wide,p1_2012_L0TIS_wide,a_acc_2012_L0TIS_wide,b_acc_2012_L0TIS_wide,c_acc_2012_L0TIS_wide,RooFit.RooConst(2),opt_acc)
	model_acc_kpi2_2012_L0TIS_wide = RooRealSumPdf("model_acc_kpi2_2012_L0TIS_wide","model_acc_kpi2_2012_L0TIS_wide",RooArgList(PDF_acc_kpi2_2012_L0TIS_wide),RooArgList(one))
	PDF_acc_kpi2_2011_L0TIS_narrow = accpdf("PDF_acc_kpi2_2011_L0TIS_narrow","PDF_acc_kpi2_2011_L0TIS_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0TIS_narrow,k2_2011_L0TIS_narrow,k3_2011_L0TIS_narrow,k4_2011_L0TIS_narrow,k5_2011_L0TIS_narrow,p1_2011_L0TIS_narrow,a_acc_2011_L0TIS_narrow,b_acc_2011_L0TIS_narrow,c_acc_2011_L0TIS_narrow,RooFit.RooConst(2),opt_acc)
	model_acc_kpi2_2011_L0TIS_narrow = RooRealSumPdf("model_acc_kpi2_2011_L0TIS_narrow","model_acc_kpi2_2011_L0TIS_narrow",RooArgList(PDF_acc_kpi2_2011_L0TIS_narrow),RooArgList(one))
	PDF_acc_kpi2_2012_L0TIS_narrow = accpdf("PDF_acc_kpi2_2012_L0TIS_narrow","PDF_acc_kpi2_2012_L0TIS_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_L0TIS_narrow,k2_2012_L0TIS_narrow,k3_2012_L0TIS_narrow,k4_2012_L0TIS_narrow,k5_2012_L0TIS_narrow,p1_2012_L0TIS_narrow,a_acc_2012_L0TIS_narrow,b_acc_2012_L0TIS_narrow,c_acc_2012_L0TIS_narrow,RooFit.RooConst(2),opt_acc)
	model_acc_kpi2_2012_L0TIS_narrow = RooRealSumPdf("model_acc_kpi2_2012_L0TIS_narrow","model_acc_kpi2_2012_L0TIS_narrow",RooArgList(PDF_acc_kpi2_2012_L0TIS_narrow),RooArgList(one))
	PDF_acc_kpi2_2011_L0noTIS_wide = accpdf("PDF_acc_kpi2_2011_L0noTIS_wide","PDF_acc_kpi2_2011_L0noTIS_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0noTIS_wide,k2_2011_L0noTIS_wide,k3_2011_L0noTIS_wide,k4_2011_L0noTIS_wide,k5_2011_L0noTIS_wide,p1_2011_L0noTIS_wide,a_acc_2011_L0noTIS_wide,b_acc_2011_L0noTIS_wide,c_acc_2011_L0noTIS_wide,RooFit.RooConst(2),opt_acc)
	model_acc_kpi2_2011_L0noTIS_wide = RooRealSumPdf("model_acc_kpi2_2011_L0noTIS_wide","model_acc_kpi2_2011_L0noTIS_wide",RooArgList(PDF_acc_kpi2_2011_L0noTIS_wide),RooArgList(one))
	PDF_acc_kpi2_2012_L0noTIS_wide = accpdf("PDF_acc_kpi2_2012_L0noTIS_wide","PDF_acc_kpi2_2012_L0noTIS_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_L0noTIS_wide,k2_2012_L0noTIS_wide,k3_2012_L0noTIS_wide,k4_2012_L0noTIS_wide,k5_2012_L0noTIS_wide,p1_2012_L0noTIS_wide,a_acc_2012_L0noTIS_wide,b_acc_2012_L0noTIS_wide,c_acc_2012_L0noTIS_wide,RooFit.RooConst(2),opt_acc)
	model_acc_kpi2_2012_L0noTIS_wide = RooRealSumPdf("model_acc_kpi2_2012_L0noTIS_wide","model_acc_kpi2_2012_L0noTIS_wide",RooArgList(PDF_acc_kpi2_2012_L0noTIS_wide),RooArgList(one))
	PDF_acc_kpi2_2011_L0noTIS_narrow = accpdf("PDF_acc_kpi2_2011_L0noTIS_narrow","PDF_acc_kpi2_2011_L0noTIS_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0noTIS_narrow,k2_2011_L0noTIS_narrow,k3_2011_L0noTIS_narrow,k4_2011_L0noTIS_narrow,k5_2011_L0noTIS_narrow,p1_2011_L0noTIS_narrow,a_acc_2011_L0noTIS_narrow,b_acc_2011_L0noTIS_narrow,c_acc_2011_L0noTIS_narrow,RooFit.RooConst(2),opt_acc)
	model_acc_kpi2_2011_L0noTIS_narrow = RooRealSumPdf("model_acc_kpi2_2011_L0noTIS_narrow","model_acc_kpi2_2011_L0noTIS_narrow",RooArgList(PDF_acc_kpi2_2011_L0noTIS_narrow),RooArgList(one))
	PDF_acc_kpi2_2012_L0noTIS_narrow = accpdf("PDF_acc_kpi2_2012_L0noTIS_narrow","PDF_acc_kpi2_2012_L0noTIS_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_L0noTIS_narrow,k2_2012_L0noTIS_narrow,k3_2012_L0noTIS_narrow,k4_2012_L0noTIS_narrow,k5_2012_L0noTIS_narrow,p1_2012_L0noTIS_narrow,a_acc_2012_L0noTIS_narrow,b_acc_2012_L0noTIS_narrow,c_acc_2012_L0noTIS_narrow,RooFit.RooConst(2),opt_acc)
	model_acc_kpi2_2012_L0noTIS_narrow = RooRealSumPdf("model_acc_kpi2_2012_L0noTIS_narrow","model_acc_kpi2_2012_L0noTIS_narrow",RooArgList(PDF_acc_kpi2_2012_L0noTIS_narrow),RooArgList(one))
	model_acc_sim_2011_L0TIS_wide = RooSimultaneous("model_acc_sim_2011_L0TIS_wide","model_acc_sim_2011_L0TIS_wide",kpipaircat)
	model_acc_sim_2012_L0TIS_wide = RooSimultaneous("model_acc_sim_2012_L0TIS_wide","model_acc_sim_2012_L0TIS_wide",kpipaircat)
	model_acc_sim_2011_L0TIS_narrow = RooSimultaneous("model_acc_sim_2011_L0TIS_narrow","model_acc_sim_2011_L0TIS_narrow",kpipaircat)
	model_acc_sim_2012_L0TIS_narrow = RooSimultaneous("model_acc_sim_2012_L0TIS_narrow","model_acc_sim_2012_L0TIS_narrow",kpipaircat)
	model_acc_sim_2011_L0noTIS_wide = RooSimultaneous("model_acc_sim_2011_L0noTIS_wide","model_acc_sim_2011_L0noTIS_wide",kpipaircat)
	model_acc_sim_2012_L0noTIS_wide = RooSimultaneous("model_acc_sim_2012_L0noTIS_wide","model_acc_sim_2012_L0noTIS_wide",kpipaircat)
	model_acc_sim_2011_L0noTIS_narrow = RooSimultaneous("model_acc_sim_2011_L0noTIS_narrow","model_acc_sim_2011_L0noTIS_narrow",kpipaircat)
	model_acc_sim_2012_L0noTIS_narrow = RooSimultaneous("model_acc_sim_2012_L0noTIS_narrow","model_acc_sim_2012_L0noTIS_narrow",kpipaircat)
	model_acc_sim_2011_L0TIS_wide.addPdf(model_acc_kpi1_2011_L0TIS_wide,"kpi1")
	model_acc_sim_2011_L0TIS_wide.addPdf(model_acc_kpi2_2011_L0TIS_wide,"kpi2")
	model_acc_sim_2012_L0TIS_wide.addPdf(model_acc_kpi1_2012_L0TIS_wide,"kpi1")
	model_acc_sim_2012_L0TIS_wide.addPdf(model_acc_kpi2_2012_L0TIS_wide,"kpi2")
	model_acc_sim_2011_L0TIS_narrow.addPdf(model_acc_kpi1_2011_L0TIS_narrow,"kpi1")
	model_acc_sim_2011_L0TIS_narrow.addPdf(model_acc_kpi2_2011_L0TIS_narrow,"kpi2")
	model_acc_sim_2012_L0TIS_narrow.addPdf(model_acc_kpi1_2012_L0TIS_narrow,"kpi1")
	model_acc_sim_2012_L0TIS_narrow.addPdf(model_acc_kpi2_2012_L0TIS_narrow,"kpi2")
	model_acc_sim_2011_L0noTIS_wide.addPdf(model_acc_kpi1_2011_L0noTIS_wide,"kpi1")
	model_acc_sim_2011_L0noTIS_wide.addPdf(model_acc_kpi2_2011_L0noTIS_wide,"kpi2")
	model_acc_sim_2012_L0noTIS_wide.addPdf(model_acc_kpi1_2012_L0noTIS_wide,"kpi1")
	model_acc_sim_2012_L0noTIS_wide.addPdf(model_acc_kpi2_2012_L0noTIS_wide,"kpi2")
	model_acc_sim_2011_L0noTIS_narrow.addPdf(model_acc_kpi1_2011_L0noTIS_narrow,"kpi1")
	model_acc_sim_2011_L0noTIS_narrow.addPdf(model_acc_kpi2_2011_L0noTIS_narrow,"kpi2")
	model_acc_sim_2012_L0noTIS_narrow.addPdf(model_acc_kpi1_2012_L0noTIS_narrow,"kpi1")
	model_acc_sim_2012_L0noTIS_narrow.addPdf(model_acc_kpi2_2012_L0noTIS_narrow,"kpi2")

	return [PDF_acc_2011_L0TIS_wide, PDF_acc_2012_L0TIS_wide, PDF_acc_2011_L0TIS_narrow, PDF_acc_2012_L0TIS_narrow, PDF_acc_2011_L0noTIS_wide, PDF_acc_2012_L0noTIS_wide, PDF_acc_2011_L0noTIS_narrow, PDF_acc_2012_L0noTIS_narrow, PDF_acc_kpi1_2011_L0TIS_wide, PDF_acc_kpi1_2012_L0TIS_wide, PDF_acc_kpi1_2011_L0TIS_narrow, PDF_acc_kpi1_2012_L0TIS_narrow, PDF_acc_kpi1_2011_L0noTIS_wide, PDF_acc_kpi1_2012_L0noTIS_wide, PDF_acc_kpi1_2011_L0noTIS_narrow, PDF_acc_kpi1_2012_L0noTIS_narrow, PDF_acc_kpi2_2011_L0TIS_wide, PDF_acc_kpi2_2012_L0TIS_wide, PDF_acc_kpi2_2011_L0TIS_narrow, PDF_acc_kpi2_2012_L0TIS_narrow, PDF_acc_kpi2_2011_L0noTIS_wide, PDF_acc_kpi2_2012_L0noTIS_wide, PDF_acc_kpi2_2011_L0noTIS_narrow, PDF_acc_kpi2_2012_L0noTIS_narrow], [model_acc_kpi1_2011_L0TIS_wide, model_acc_kpi1_2012_L0TIS_wide, model_acc_kpi1_2011_L0TIS_narrow, model_acc_kpi1_2012_L0TIS_narrow, model_acc_kpi1_2011_L0noTIS_wide, model_acc_kpi1_2012_L0noTIS_wide, model_acc_kpi1_2011_L0noTIS_narrow, model_acc_kpi1_2012_L0noTIS_narrow, model_acc_kpi2_2011_L0TIS_wide, model_acc_kpi2_2012_L0TIS_wide, model_acc_kpi2_2011_L0TIS_narrow, model_acc_kpi2_2012_L0TIS_narrow, model_acc_kpi2_2011_L0noTIS_wide, model_acc_kpi2_2012_L0noTIS_wide, model_acc_kpi2_2011_L0noTIS_narrow, model_acc_kpi2_2012_L0noTIS_narrow, model_acc_2011_L0TIS_wide, model_acc_2012_L0TIS_wide, model_acc_2011_L0TIS_narrow, model_acc_2012_L0TIS_narrow, model_acc_2011_L0noTIS_wide, model_acc_2012_L0noTIS_wide, model_acc_2011_L0noTIS_narrow, model_acc_2012_L0noTIS_narrow, model_acc_sim_2011_L0TIS_wide, model_acc_sim_2012_L0TIS_wide, model_acc_sim_2011_L0TIS_narrow, model_acc_sim_2012_L0TIS_narrow, model_acc_sim_2011_L0noTIS_wide, model_acc_sim_2012_L0noTIS_wide, model_acc_sim_2011_L0noTIS_narrow, model_acc_sim_2012_L0noTIS_narrow]


def CreateAccPDFGen():

	PDF_acc_kpi1_gen_wide = accpdf("PDF_acc_kpi1_gen_wide","PDF_acc_kpi1_gen_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_gen_wide,k2_gen_wide,k3_gen_wide,k4_gen_wide,k5_gen_wide,p1_gen_wide,one,one,one,RooFit.RooConst(1),opt_acc)
	model_acc_kpi1_gen_wide = RooRealSumPdf("model_acc_kpi1_gen_wide","model_acc_kpi1_gen_wide",RooArgList(PDF_acc_kpi1_gen_wide),RooArgList(one))

	PDF_acc_kpi1_gen_narrow = accpdf("PDF_acc_kpi1_gen_narrow","PDF_acc_kpi1_gen_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_gen_narrow,k2_gen_narrow,k3_gen_narrow,k4_gen_narrow,k5_gen_narrow,p1_gen_narrow,one,one,one,RooFit.RooConst(1),opt_acc)
	model_acc_kpi1_gen_narrow = RooRealSumPdf("model_acc_kpi1_gen_narrow","model_acc_kpi1_gen_narrow",RooArgList(PDF_acc_kpi1_gen_narrow),RooArgList(one))

	PDF_acc_kpi2_gen_wide = accpdf("PDF_acc_kpi2_gen_wide","PDF_acc_kpi2_gen_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_gen_wide,k2_gen_wide,k3_gen_wide,k4_gen_wide,k5_gen_wide,p1_gen_wide,one,one,one,RooFit.RooConst(2),opt_acc)
	model_acc_kpi2_gen_wide = RooRealSumPdf("model_acc_kpi2_gen_wide","model_acc_kpi2_gen_wide",RooArgList(PDF_acc_kpi2_gen_wide),RooArgList(one))

	PDF_acc_kpi2_gen_narrow = accpdf("PDF_acc_kpi2_gen_narrow","PDF_acc_kpi2_gen_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_gen_narrow,k2_gen_narrow,k3_gen_narrow,k4_gen_narrow,k5_gen_narrow,p1_gen_narrow,one,one,one,RooFit.RooConst(2),opt_acc)
	model_acc_kpi2_gen_narrow = RooRealSumPdf("model_acc_kpi2_gen_narrow","model_acc_kpi2_gen_narrow",RooArgList(PDF_acc_kpi2_gen_narrow),RooArgList(one))

	model_acc_sim_gen_wide = RooSimultaneous("model_acc_sim_gen_wide","model_acc_sim_gen_wide",kpipaircat)
	model_acc_sim_gen_narrow = RooSimultaneous("model_acc_sim_gen_narrow","model_acc_sim_gen_narrow",kpipaircat)
	model_acc_sim_gen_wide.addPdf(model_acc_kpi1_gen_wide,"kpi1")
	model_acc_sim_gen_wide.addPdf(model_acc_kpi2_gen_wide,"kpi2")
	model_acc_sim_gen_narrow.addPdf(model_acc_kpi1_gen_narrow,"kpi1")
	model_acc_sim_gen_narrow.addPdf(model_acc_kpi2_gen_narrow,"kpi2")

	spl_pdf_gen_wide = SplineTAcc("spl_pdf_gen_wide","spl_pdf_gen_wide",t_MC,t0_wide,t1_wide,t2_wide,t3_wide,t4_wide,t5_wide,\
spl_c0_gen_wide,spl_c1_gen_wide,spl_c2_gen_wide,spl_c3_gen_wide,spl_c4_gen_wide,spl_c5_gen_wide,spl_c6_gen_wide,spl_c7_gen_wide)
	spl_pdf_gen_narrow = SplineTAcc("spl_pdf_gen_narrow","spl_pdf_gen_narrow",t_MC,t0_narrow,t1_narrow,t2_narrow,t3_narrow,t4_narrow,t5_narrow,\
spl_c0_gen_narrow,spl_c1_gen_narrow,spl_c2_gen_narrow,spl_c3_gen_narrow,spl_c4_gen_narrow,spl_c5_gen_narrow,spl_c6_gen_narrow,spl_c7_gen_narrow)

	return [PDF_acc_kpi1_gen_wide,PDF_acc_kpi1_gen_narrow,PDF_acc_kpi2_gen_wide,PDF_acc_kpi2_gen_narrow],\
[model_acc_kpi1_gen_wide,model_acc_kpi1_gen_narrow,model_acc_kpi2_gen_wide,model_acc_kpi2_gen_narrow,model_acc_sim_gen_wide,model_acc_sim_gen_narrow,spl_pdf_gen_wide,spl_pdf_gen_narrow]


def CreatePhysPDF():

	acctype.setVal(0)
	for argument in options: options_list_aux.add(argument)
	for argument in observables: observables_list_aux.add(argument)
	for argument in observables_narrowwin: observables_list_narrowwin_aux.add(argument)
	for argument in wave_fractions: wave_fractions_list_aux.add(argument)
	for argument in dirCP_asyms: dirCP_asyms_list_aux.add(argument)
	for argument in strong_phases: strong_phases_list_aux.add(argument)
	for argument in weak_phases: weak_phases_list_aux.add(argument)
	for argument in mixing_params: mixing_params_list_aux.add(argument)
	for argument in calib_params_aux: calib_params_list_aux.add(argument)
	for argument in cond_distr_params: cond_distr_params_list_aux.add(argument)
	for argument in sys_studies: sys_studies_list_aux.add(argument)
	for argument in mass_integrals: mass_integrals_list_aux.add(argument)
	for argument in mass_integrals_narrowwin: mass_integrals_list_narrowwin_aux.add(argument)
	for argument in ang_integrals: ang_integrals_list_aux.add(argument)
	for argument in time_integrals: time_integrals_list_aux.add(argument)

	RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)
	Integrator_wide = ComputeIntegrals("Integrator_wide","Integrator_wide",options_list_aux,observables_list_aux,mixing_params_list_aux,calib_params_list_aux,mass_integrals_list_aux)
	Integrator_narrow = ComputeIntegrals("Integrator_narrow","Integrator_narrow",options_list_aux,observables_list_narrowwin_aux,mixing_params_list_aux,calib_params_list_aux,mass_integrals_list_narrowwin_aux)

	option.setVal(100)
	integral100_wide = Integrator_wide.createIntegral(RooArgSet(mKp1_MC,mKp2_MC))
	Im00.setVal(integral100_wide.getVal())
	option.setVal(101)
	integral101_wide = Integrator_wide.createIntegral(RooArgSet(mKp1_MC,mKp2_MC))
	Im01.setVal(integral101_wide.getVal())
	option.setVal(110)
	integral110_wide = Integrator_wide.createIntegral(RooArgSet(mKp1_MC,mKp2_MC))
	Im10.setVal(integral110_wide.getVal())
	option.setVal(102)
	integral102_wide = Integrator_wide.createIntegral(RooArgSet(mKp1_MC,mKp2_MC))
	Im02.setVal(integral102_wide.getVal())
	option.setVal(120)
	integral120_wide = Integrator_wide.createIntegral(RooArgSet(mKp1_MC,mKp2_MC))
	Im20.setVal(integral120_wide.getVal())
	option.setVal(111)
	integral111_wide = Integrator_wide.createIntegral(RooArgSet(mKp1_MC,mKp2_MC))
	Im11.setVal(integral111_wide.getVal())
	option.setVal(112)
	integral112_wide = Integrator_wide.createIntegral(RooArgSet(mKp1_MC,mKp2_MC))
	Im12.setVal(integral112_wide.getVal())
	option.setVal(121)
	integral121_wide = Integrator_wide.createIntegral(RooArgSet(mKp1_MC,mKp2_MC))
	Im21.setVal(integral121_wide.getVal())
	option.setVal(122)
	integral122_wide = Integrator_wide.createIntegral(RooArgSet(mKp1_MC,mKp2_MC))
	Im22.setVal(integral122_wide.getVal())

	option.setVal(100)
	integral100_narrow = Integrator_narrow.createIntegral(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC))
	Im00_narrowwin.setVal(integral100_narrow.getVal())
	option.setVal(101)
	integral101_narrow = Integrator_narrow.createIntegral(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC))
	Im01_narrowwin.setVal(integral101_narrow.getVal())
	option.setVal(110)
	integral110_narrow = Integrator_narrow.createIntegral(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC))
	Im10_narrowwin.setVal(integral110_narrow.getVal())
	option.setVal(102)
	integral102_narrow = Integrator_narrow.createIntegral(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC))
	Im02_narrowwin.setVal(integral102_narrow.getVal())
	option.setVal(120)
	integral120_narrow = Integrator_narrow.createIntegral(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC))
	Im20_narrowwin.setVal(integral120_narrow.getVal())
	option.setVal(111)
	integral111_narrow = Integrator_narrow.createIntegral(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC))
	Im11_narrowwin.setVal(integral111_narrow.getVal())
	option.setVal(112)
	integral112_narrow = Integrator_narrow.createIntegral(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC))
	Im12_narrowwin.setVal(integral112_narrow.getVal())
	option.setVal(121)
	integral121_narrow = Integrator_narrow.createIntegral(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC))
	Im21_narrowwin.setVal(integral121_narrow.getVal())
	option.setVal(122)
	integral122_narrow = Integrator_narrow.createIntegral(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC))
	Im22_narrowwin.setVal(integral122_narrow.getVal())

	RooMsgService.instance().setGlobalKillBelow(RooFit.INFO)
	option.setVal(0)

	PDF_phys_wide = KpiKpiSpectrumNW("PDF_phys_wide","PDF_phys_wide",options_list_aux,observables_list_aux,wave_fractions_list_aux,dirCP_asyms_list_aux,strong_phases_list_aux,weak_phases_list_aux,mixing_params_list_aux,\
calib_params_list_aux,cond_distr_params_list_aux,sys_studies_list_aux,mass_integrals_list_aux,ang_integrals_list_aux,time_integrals_list_aux)

	PDF_phys_narrow = KpiKpiSpectrumNW("PDF_phys_narrow","PDF_phys_narrow",options_list_aux,observables_list_narrowwin_aux,wave_fractions_list_aux,dirCP_asyms_list_aux,strong_phases_list_aux,weak_phases_list_aux,mixing_params_list_aux,\
calib_params_list_aux,cond_distr_params_list_aux,sys_studies_list_aux,mass_integrals_list_narrowwin_aux,ang_integrals_list_aux,time_integrals_list_aux)

	return PDF_phys_wide, PDF_phys_narrow


def LoadDataVis(data_file, data_tree, datatype, evnum_limit = 0):

	# Information.
	print 'Loading data file ' + data_file + ' ...'
	if datatype == 0: print 'MC sample: PhSp.'
	elif datatype == 1: print 'MC sample: VV.'
	else: print 'MC sample: PhSp + VV.'
	if (evnum_limit == 0): print 'All events selected.'
	else: print 'Maximum of '+str(evnum_limit)+' events selected per data sample.'

	# Input data.
	file_in = TFile(NTUPLE_PATH + data_file)
	tree_full = file_in.Get(data_tree)
	file_out = TFile(NTUPLE_PATH + "trash.root","RECREATE")
	tree_2011_L0TIS_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,0,datatype))
	tree_2012_L0TIS_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,0,datatype))
	tree_2011_L0TIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,0,datatype))
	tree_2012_L0TIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,0,datatype))
	tree_2011_L0noTIS_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,1,datatype))
	tree_2012_L0noTIS_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,1,datatype))
	tree_2011_L0noTIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,1,datatype))
	tree_2012_L0noTIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,1,datatype))

	PDF_gen = CreateGenPDF()

	invN_2011_L0TIS_wide = 1./tree_2011_L0TIS_wide.GetEntries()
	invN_2012_L0TIS_wide = 1./tree_2012_L0TIS_wide.GetEntries()
	invN_2011_L0TIS_narrow = 1./tree_2011_L0TIS_narrow.GetEntries()
	invN_2012_L0TIS_narrow = 1./tree_2012_L0TIS_narrow.GetEntries()
	invN_2011_L0noTIS_wide = 1./tree_2011_L0noTIS_wide.GetEntries()
	invN_2012_L0noTIS_wide = 1./tree_2012_L0noTIS_wide.GetEntries()
	invN_2011_L0noTIS_narrow = 1./tree_2011_L0noTIS_narrow.GetEntries()
	invN_2012_L0noTIS_narrow = 1./tree_2012_L0noTIS_narrow.GetEntries()

	def setvarvals(entry):
		mKp1_MC.setVal(eval("entry."+m1_name_MC))
		mKp2_MC.setVal(eval("entry."+m2_name_MC))
		cos1_MC.setVal(eval("entry."+cos1_name_MC))
		cos2_MC.setVal(eval("entry."+cos2_name_MC))
		phi_MC.setVal(eval("entry."+phi_name_MC))
		t_MC.setVal(eval("entry."+t_name_MC))

	opt_genmodel.setVal(datatype)

	wide_window_MC.setVal(1)
	year_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_L0TIS_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			setvarvals(i)
			MCweight1.setVal(invN_2011_L0TIS_wide/PDF_gen.evaluate())
			MCweight2.setVal(invN_2011_L0TIS_wide/PDF_gen.evaluate())
			MCweight3.setVal(invN_2011_L0TIS_wide/PDF_gen.evaluate())
			MCweight4.setVal(invN_2011_L0TIS_wide/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_kpi1_2011_L0TIS_wide_.add(RooArgSet(mKp1_MC,MCweight1))
			data1_kpi2_2011_L0TIS_wide_.add(RooArgSet(mKp2_MC,MCweight1))
			data2_kpi1_2011_L0TIS_wide_.add(RooArgSet(cos1_MC,MCweight2))
			data2_kpi2_2011_L0TIS_wide_.add(RooArgSet(cos2_MC,MCweight2))
			data3_2011_L0TIS_wide_.add(RooArgSet(phi_MC,MCweight3))
			data4_2011_L0TIS_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	year_MC.setVal(1)
	ev_counter = 0
	for i in tree_2012_L0TIS_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			setvarvals(i)
			MCweight1.setVal(invN_2012_L0TIS_wide/PDF_gen.evaluate())
			MCweight2.setVal(invN_2012_L0TIS_wide/PDF_gen.evaluate())
			MCweight3.setVal(invN_2012_L0TIS_wide/PDF_gen.evaluate())
			MCweight4.setVal(invN_2012_L0TIS_wide/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_kpi1_2012_L0TIS_wide_.add(RooArgSet(mKp1_MC,MCweight1))
			data1_kpi2_2012_L0TIS_wide_.add(RooArgSet(mKp2_MC,MCweight1))
			data2_kpi1_2012_L0TIS_wide_.add(RooArgSet(cos1_MC,MCweight2))
			data2_kpi2_2012_L0TIS_wide_.add(RooArgSet(cos2_MC,MCweight2))
			data3_2012_L0TIS_wide_.add(RooArgSet(phi_MC,MCweight3))
			data4_2012_L0TIS_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	wide_window_MC.setVal(0)
	year_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_L0TIS_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
			mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
			setvarvals(i)
			MCweight1.setVal(invN_2011_L0TIS_narrow/PDF_gen.evaluate())
			MCweight2.setVal(invN_2011_L0TIS_narrow/PDF_gen.evaluate())
			MCweight3.setVal(invN_2011_L0TIS_narrow/PDF_gen.evaluate())
			MCweight4.setVal(invN_2011_L0TIS_narrow/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_kpi1_2011_L0TIS_narrow_.add(RooArgSet(mKp1_narrow_MC,MCweight1))
			data1_kpi2_2011_L0TIS_narrow_.add(RooArgSet(mKp2_narrow_MC,MCweight1))
			data2_kpi1_2011_L0TIS_narrow_.add(RooArgSet(cos1_MC,MCweight2))
			data2_kpi2_2011_L0TIS_narrow_.add(RooArgSet(cos2_MC,MCweight2))
			data3_2011_L0TIS_narrow_.add(RooArgSet(phi_MC,MCweight3))
			data4_2011_L0TIS_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	year_MC.setVal(1)
	ev_counter = 0
	for i in tree_2012_L0TIS_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
			mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
			setvarvals(i)
			MCweight1.setVal(invN_2012_L0TIS_narrow/PDF_gen.evaluate())
			MCweight2.setVal(invN_2012_L0TIS_narrow/PDF_gen.evaluate())
			MCweight3.setVal(invN_2012_L0TIS_narrow/PDF_gen.evaluate())
			MCweight4.setVal(invN_2012_L0TIS_narrow/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_kpi1_2012_L0TIS_narrow_.add(RooArgSet(mKp1_narrow_MC,MCweight1))
			data1_kpi2_2012_L0TIS_narrow_.add(RooArgSet(mKp2_narrow_MC,MCweight1))
			data2_kpi1_2012_L0TIS_narrow_.add(RooArgSet(cos1_MC,MCweight2))
			data2_kpi2_2012_L0TIS_narrow_.add(RooArgSet(cos2_MC,MCweight2))
			data3_2012_L0TIS_narrow_.add(RooArgSet(phi_MC,MCweight3))
			data4_2012_L0TIS_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	wide_window_MC.setVal(1)
	year_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_L0noTIS_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			setvarvals(i)
			MCweight1.setVal(invN_2011_L0noTIS_wide/PDF_gen.evaluate())
			MCweight2.setVal(invN_2011_L0noTIS_wide/PDF_gen.evaluate())
			MCweight3.setVal(invN_2011_L0noTIS_wide/PDF_gen.evaluate())
			MCweight4.setVal(invN_2011_L0noTIS_wide/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_kpi1_2011_L0noTIS_wide_.add(RooArgSet(mKp1_MC,MCweight1))
			data1_kpi2_2011_L0noTIS_wide_.add(RooArgSet(mKp2_MC,MCweight1))
			data2_kpi1_2011_L0noTIS_wide_.add(RooArgSet(cos1_MC,MCweight2))
			data2_kpi2_2011_L0noTIS_wide_.add(RooArgSet(cos2_MC,MCweight2))
			data3_2011_L0noTIS_wide_.add(RooArgSet(phi_MC,MCweight3))
			data4_2011_L0noTIS_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	year_MC.setVal(1)
	ev_counter = 0
	for i in tree_2012_L0noTIS_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			setvarvals(i)
			MCweight1.setVal(invN_2012_L0noTIS_wide/PDF_gen.evaluate())
			MCweight2.setVal(invN_2012_L0noTIS_wide/PDF_gen.evaluate())
			MCweight3.setVal(invN_2012_L0noTIS_wide/PDF_gen.evaluate())
			MCweight4.setVal(invN_2012_L0noTIS_wide/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_kpi1_2012_L0noTIS_wide_.add(RooArgSet(mKp1_MC,MCweight1))
			data1_kpi2_2012_L0noTIS_wide_.add(RooArgSet(mKp2_MC,MCweight1))
			data2_kpi1_2012_L0noTIS_wide_.add(RooArgSet(cos1_MC,MCweight2))
			data2_kpi2_2012_L0noTIS_wide_.add(RooArgSet(cos2_MC,MCweight2))
			data3_2012_L0noTIS_wide_.add(RooArgSet(phi_MC,MCweight3))
			data4_2012_L0noTIS_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	wide_window_MC.setVal(0)
	year_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_L0noTIS_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
			mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
			setvarvals(i)
			MCweight1.setVal(invN_2011_L0noTIS_narrow/PDF_gen.evaluate())
			MCweight2.setVal(invN_2011_L0noTIS_narrow/PDF_gen.evaluate())
			MCweight3.setVal(invN_2011_L0noTIS_narrow/PDF_gen.evaluate())
			MCweight4.setVal(invN_2011_L0noTIS_narrow/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_kpi1_2011_L0noTIS_narrow_.add(RooArgSet(mKp1_narrow_MC,MCweight1))
			data1_kpi2_2011_L0noTIS_narrow_.add(RooArgSet(mKp2_narrow_MC,MCweight1))
			data2_kpi1_2011_L0noTIS_narrow_.add(RooArgSet(cos1_MC,MCweight2))
			data2_kpi2_2011_L0noTIS_narrow_.add(RooArgSet(cos2_MC,MCweight2))
			data3_2011_L0noTIS_narrow_.add(RooArgSet(phi_MC,MCweight3))
			data4_2011_L0noTIS_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	year_MC.setVal(1)
	ev_counter = 0
	for i in tree_2012_L0noTIS_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
			mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
			setvarvals(i)
			MCweight1.setVal(invN_2012_L0noTIS_narrow/PDF_gen.evaluate())
			MCweight2.setVal(invN_2012_L0noTIS_narrow/PDF_gen.evaluate())
			MCweight3.setVal(invN_2012_L0noTIS_narrow/PDF_gen.evaluate())
			MCweight4.setVal(invN_2012_L0noTIS_narrow/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_kpi1_2012_L0noTIS_narrow_.add(RooArgSet(mKp1_narrow_MC,MCweight1))
			data1_kpi2_2012_L0noTIS_narrow_.add(RooArgSet(mKp2_narrow_MC,MCweight1))
			data2_kpi1_2012_L0noTIS_narrow_.add(RooArgSet(cos1_MC,MCweight2))
			data2_kpi2_2012_L0noTIS_narrow_.add(RooArgSet(cos2_MC,MCweight2))
			data3_2012_L0noTIS_narrow_.add(RooArgSet(phi_MC,MCweight3))
			data4_2012_L0noTIS_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1

	data1_2011_L0TIS_wide_ = RooDataSet("data1_2011_L0TIS_wide_","data1_2011_L0TIS_wide_",RooArgSet(mKp1_MC,mKp2_MC,MCweight1),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data1_kpi1_2011_L0TIS_wide_),RooFit.Import("kpi2",data1_kpi2_2011_L0TIS_wide_))
	data1_2012_L0TIS_wide_ = RooDataSet("data1_2012_L0TIS_wide_","data1_2012_L0TIS_wide_",RooArgSet(mKp1_MC,mKp2_MC,MCweight1),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data1_kpi1_2012_L0TIS_wide_),RooFit.Import("kpi2",data1_kpi2_2012_L0TIS_wide_))
	data2_2011_L0TIS_wide_ = RooDataSet("data2_2011_L0TIS_wide_","data2_2011_L0TIS_wide_",RooArgSet(cos1_MC,cos2_MC,MCweight2),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data2_kpi1_2011_L0TIS_wide_),RooFit.Import("kpi2",data2_kpi2_2011_L0TIS_wide_))
	data2_2012_L0TIS_wide_ = RooDataSet("data2_2012_L0TIS_wide_","data2_2012_L0TIS_wide_",RooArgSet(cos1_MC,cos2_MC,MCweight2),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data2_kpi1_2012_L0TIS_wide_),RooFit.Import("kpi2",data2_kpi2_2012_L0TIS_wide_))
	data1_2011_L0TIS_narrow_ = RooDataSet("data1_2011_L0TIS_narrow_","data1_2011_L0TIS_narrow_",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,MCweight1),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data1_kpi1_2011_L0TIS_narrow_),RooFit.Import("kpi2",data1_kpi2_2011_L0TIS_narrow_))
	data1_2012_L0TIS_narrow_ = RooDataSet("data1_2012_L0TIS_narrow_","data1_2012_L0TIS_narrow_",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,MCweight1),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data1_kpi1_2012_L0TIS_narrow_),RooFit.Import("kpi2",data1_kpi2_2012_L0TIS_narrow_))
	data2_2011_L0TIS_narrow_ = RooDataSet("data2_2011_L0TIS_narrow_","data2_2011_L0TIS_narrow_",RooArgSet(cos1_MC,cos2_MC,MCweight2),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data2_kpi1_2011_L0TIS_narrow_),RooFit.Import("kpi2",data2_kpi2_2011_L0TIS_narrow_))
	data2_2012_L0TIS_narrow_ = RooDataSet("data2_2012_L0TIS_narrow_","data2_2012_L0TIS_narrow_",RooArgSet(cos1_MC,cos2_MC,MCweight2),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data2_kpi1_2012_L0TIS_narrow_),RooFit.Import("kpi2",data2_kpi2_2012_L0TIS_narrow_))
	data1_2011_L0noTIS_wide_ = RooDataSet("data1_2011_L0noTIS_wide_","data1_2011_L0noTIS_wide_",RooArgSet(mKp1_MC,mKp2_MC,MCweight1),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data1_kpi1_2011_L0noTIS_wide_),RooFit.Import("kpi2",data1_kpi2_2011_L0noTIS_wide_))
	data1_2012_L0noTIS_wide_ = RooDataSet("data1_2012_L0noTIS_wide_","data1_2012_L0noTIS_wide_",RooArgSet(mKp1_MC,mKp2_MC,MCweight1),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data1_kpi1_2012_L0noTIS_wide_),RooFit.Import("kpi2",data1_kpi2_2012_L0noTIS_wide_))
	data2_2011_L0noTIS_wide_ = RooDataSet("data2_2011_L0noTIS_wide_","data2_2011_L0noTIS_wide_",RooArgSet(cos1_MC,cos2_MC,MCweight2),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data2_kpi1_2011_L0noTIS_wide_),RooFit.Import("kpi2",data2_kpi2_2011_L0noTIS_wide_))
	data2_2012_L0noTIS_wide_ = RooDataSet("data2_2012_L0noTIS_wide_","data2_2012_L0noTIS_wide_",RooArgSet(cos1_MC,cos2_MC,MCweight2),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data2_kpi1_2012_L0noTIS_wide_),RooFit.Import("kpi2",data2_kpi2_2012_L0noTIS_wide_))
	data1_2011_L0noTIS_narrow_ = RooDataSet("data1_2011_L0noTIS_narrow_","data1_2011_L0noTIS_narrow_",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,MCweight1),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data1_kpi1_2011_L0noTIS_narrow_),RooFit.Import("kpi2",data1_kpi2_2011_L0noTIS_narrow_))
	data1_2012_L0noTIS_narrow_ = RooDataSet("data1_2012_L0noTIS_narrow_","data1_2012_L0noTIS_narrow_",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,MCweight1),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data1_kpi1_2012_L0noTIS_narrow_),RooFit.Import("kpi2",data1_kpi2_2012_L0noTIS_narrow_))
	data2_2011_L0noTIS_narrow_ = RooDataSet("data2_2011_L0noTIS_narrow_","data2_2011_L0noTIS_narrow_",RooArgSet(cos1_MC,cos2_MC,MCweight2),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data2_kpi1_2011_L0noTIS_narrow_),RooFit.Import("kpi2",data2_kpi2_2011_L0noTIS_narrow_))
	data2_2012_L0noTIS_narrow_ = RooDataSet("data2_2012_L0noTIS_narrow_","data2_2012_L0noTIS_narrow_",RooArgSet(cos1_MC,cos2_MC,MCweight2),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data2_kpi1_2012_L0noTIS_narrow_),RooFit.Import("kpi2",data2_kpi2_2012_L0noTIS_narrow_))

	data1_2011_L0TIS_wide = RooDataSet("data1_2011_L0TIS_wide","data1_2011_L0TIS_wide",data1_2011_L0TIS_wide_,data1_2011_L0TIS_wide_.get(),"","MCweight1")
	data2_2011_L0TIS_wide = RooDataSet("data2_2011_L0TIS_wide","data2_2011_L0TIS_wide",data2_2011_L0TIS_wide_,data2_2011_L0TIS_wide_.get(),"","MCweight2")
	data3_2011_L0TIS_wide = RooDataSet("data3_2011_L0TIS_wide","data3_2011_L0TIS_wide",data3_2011_L0TIS_wide_,data3_2011_L0TIS_wide_.get(),"","MCweight3")
	data4_2011_L0TIS_wide = RooDataSet("data4_2011_L0TIS_wide","data4_2011_L0TIS_wide",data4_2011_L0TIS_wide_,data4_2011_L0TIS_wide_.get(),"","MCweight4")
	data1_2012_L0TIS_wide = RooDataSet("data1_2012_L0TIS_wide","data1_2012_L0TIS_wide",data1_2012_L0TIS_wide_,data1_2012_L0TIS_wide_.get(),"","MCweight1")
	data2_2012_L0TIS_wide = RooDataSet("data2_2012_L0TIS_wide","data2_2012_L0TIS_wide",data2_2012_L0TIS_wide_,data2_2012_L0TIS_wide_.get(),"","MCweight2")
	data3_2012_L0TIS_wide = RooDataSet("data3_2012_L0TIS_wide","data3_2012_L0TIS_wide",data3_2012_L0TIS_wide_,data3_2012_L0TIS_wide_.get(),"","MCweight3")
	data4_2012_L0TIS_wide = RooDataSet("data4_2012_L0TIS_wide","data4_2012_L0TIS_wide",data4_2012_L0TIS_wide_,data4_2012_L0TIS_wide_.get(),"","MCweight4")
	data1_2011_L0TIS_narrow = RooDataSet("data1_2011_L0TIS_narrow","data1_2011_L0TIS_narrow",data1_2011_L0TIS_narrow_,data1_2011_L0TIS_narrow_.get(),"","MCweight1")
	data2_2011_L0TIS_narrow = RooDataSet("data2_2011_L0TIS_narrow","data2_2011_L0TIS_narrow",data2_2011_L0TIS_narrow_,data2_2011_L0TIS_narrow_.get(),"","MCweight2")
	data3_2011_L0TIS_narrow = RooDataSet("data3_2011_L0TIS_narrow","data3_2011_L0TIS_narrow",data3_2011_L0TIS_narrow_,data3_2011_L0TIS_narrow_.get(),"","MCweight3")
	data4_2011_L0TIS_narrow = RooDataSet("data4_2011_L0TIS_narrow","data4_2011_L0TIS_narrow",data4_2011_L0TIS_narrow_,data4_2011_L0TIS_narrow_.get(),"","MCweight4")
	data1_2012_L0TIS_narrow = RooDataSet("data1_2012_L0TIS_narrow","data1_2012_L0TIS_narrow",data1_2012_L0TIS_narrow_,data1_2012_L0TIS_narrow_.get(),"","MCweight1")
	data2_2012_L0TIS_narrow = RooDataSet("data2_2012_L0TIS_narrow","data2_2012_L0TIS_narrow",data2_2012_L0TIS_narrow_,data2_2012_L0TIS_narrow_.get(),"","MCweight2")
	data3_2012_L0TIS_narrow = RooDataSet("data3_2012_L0TIS_narrow","data3_2012_L0TIS_narrow",data3_2012_L0TIS_narrow_,data3_2012_L0TIS_narrow_.get(),"","MCweight3")
	data4_2012_L0TIS_narrow = RooDataSet("data4_2012_L0TIS_narrow","data4_2012_L0TIS_narrow",data4_2012_L0TIS_narrow_,data4_2012_L0TIS_narrow_.get(),"","MCweight4")
	data1_2011_L0noTIS_wide = RooDataSet("data1_2011_L0noTIS_wide","data1_2011_L0noTIS_wide",data1_2011_L0noTIS_wide_,data1_2011_L0noTIS_wide_.get(),"","MCweight1")
	data2_2011_L0noTIS_wide = RooDataSet("data2_2011_L0noTIS_wide","data2_2011_L0noTIS_wide",data2_2011_L0noTIS_wide_,data2_2011_L0noTIS_wide_.get(),"","MCweight2")
	data3_2011_L0noTIS_wide = RooDataSet("data3_2011_L0noTIS_wide","data3_2011_L0noTIS_wide",data3_2011_L0noTIS_wide_,data3_2011_L0noTIS_wide_.get(),"","MCweight3")
	data4_2011_L0noTIS_wide = RooDataSet("data4_2011_L0noTIS_wide","data4_2011_L0noTIS_wide",data4_2011_L0noTIS_wide_,data4_2011_L0noTIS_wide_.get(),"","MCweight4")
	data1_2012_L0noTIS_wide = RooDataSet("data1_2012_L0noTIS_wide","data1_2012_L0noTIS_wide",data1_2012_L0noTIS_wide_,data1_2012_L0noTIS_wide_.get(),"","MCweight1")
	data2_2012_L0noTIS_wide = RooDataSet("data2_2012_L0noTIS_wide","data2_2012_L0noTIS_wide",data2_2012_L0noTIS_wide_,data2_2012_L0noTIS_wide_.get(),"","MCweight2")
	data3_2012_L0noTIS_wide = RooDataSet("data3_2012_L0noTIS_wide","data3_2012_L0noTIS_wide",data3_2012_L0noTIS_wide_,data3_2012_L0noTIS_wide_.get(),"","MCweight3")
	data4_2012_L0noTIS_wide = RooDataSet("data4_2012_L0noTIS_wide","data4_2012_L0noTIS_wide",data4_2012_L0noTIS_wide_,data4_2012_L0noTIS_wide_.get(),"","MCweight4")
	data1_2011_L0noTIS_narrow = RooDataSet("data1_2011_L0noTIS_narrow","data1_2011_L0noTIS_narrow",data1_2011_L0noTIS_narrow_,data1_2011_L0noTIS_narrow_.get(),"","MCweight1")
	data2_2011_L0noTIS_narrow = RooDataSet("data2_2011_L0noTIS_narrow","data2_2011_L0noTIS_narrow",data2_2011_L0noTIS_narrow_,data2_2011_L0noTIS_narrow_.get(),"","MCweight2")
	data3_2011_L0noTIS_narrow = RooDataSet("data3_2011_L0noTIS_narrow","data3_2011_L0noTIS_narrow",data3_2011_L0noTIS_narrow_,data3_2011_L0noTIS_narrow_.get(),"","MCweight3")
	data4_2011_L0noTIS_narrow = RooDataSet("data4_2011_L0noTIS_narrow","data4_2011_L0noTIS_narrow",data4_2011_L0noTIS_narrow_,data4_2011_L0noTIS_narrow_.get(),"","MCweight4")
	data1_2012_L0noTIS_narrow = RooDataSet("data1_2012_L0noTIS_narrow","data1_2012_L0noTIS_narrow",data1_2012_L0noTIS_narrow_,data1_2012_L0noTIS_narrow_.get(),"","MCweight1")
	data2_2012_L0noTIS_narrow = RooDataSet("data2_2012_L0noTIS_narrow","data2_2012_L0noTIS_narrow",data2_2012_L0noTIS_narrow_,data2_2012_L0noTIS_narrow_.get(),"","MCweight2")
	data3_2012_L0noTIS_narrow = RooDataSet("data3_2012_L0noTIS_narrow","data3_2012_L0noTIS_narrow",data3_2012_L0noTIS_narrow_,data3_2012_L0noTIS_narrow_.get(),"","MCweight3")
	data4_2012_L0noTIS_narrow = RooDataSet("data4_2012_L0noTIS_narrow","data4_2012_L0noTIS_narrow",data4_2012_L0noTIS_narrow_,data4_2012_L0noTIS_narrow_.get(),"","MCweight4")
	data1_kpi1_2011_L0TIS_wide = RooDataSet("data1_kpi1_2011_L0TIS_wide","data1_kpi1_2011_L0TIS_wide",data1_kpi1_2011_L0TIS_wide_,data1_kpi1_2011_L0TIS_wide_.get(),"","MCweight1")
	data2_kpi1_2011_L0TIS_wide = RooDataSet("data2_kpi1_2011_L0TIS_wide","data2_kpi1_2011_L0TIS_wide",data2_kpi1_2011_L0TIS_wide_,data2_kpi1_2011_L0TIS_wide_.get(),"","MCweight2")
	data1_kpi1_2012_L0TIS_wide = RooDataSet("data1_kpi1_2012_L0TIS_wide","data1_kpi1_2012_L0TIS_wide",data1_kpi1_2012_L0TIS_wide_,data1_kpi1_2012_L0TIS_wide_.get(),"","MCweight1")
	data2_kpi1_2012_L0TIS_wide = RooDataSet("data2_kpi1_2012_L0TIS_wide","data2_kpi1_2012_L0TIS_wide",data2_kpi1_2012_L0TIS_wide_,data2_kpi1_2012_L0TIS_wide_.get(),"","MCweight2")
	data1_kpi1_2011_L0TIS_narrow = RooDataSet("data1_kpi1_2011_L0TIS_narrow","data1_kpi1_2011_L0TIS_narrow",data1_kpi1_2011_L0TIS_narrow_,data1_kpi1_2011_L0TIS_narrow_.get(),"","MCweight1")
	data2_kpi1_2011_L0TIS_narrow = RooDataSet("data2_kpi1_2011_L0TIS_narrow","data2_kpi1_2011_L0TIS_narrow",data2_kpi1_2011_L0TIS_narrow_,data2_kpi1_2011_L0TIS_narrow_.get(),"","MCweight2")
	data1_kpi1_2012_L0TIS_narrow = RooDataSet("data1_kpi1_2012_L0TIS_narrow","data1_kpi1_2012_L0TIS_narrow",data1_kpi1_2012_L0TIS_narrow_,data1_kpi1_2012_L0TIS_narrow_.get(),"","MCweight1")
	data2_kpi1_2012_L0TIS_narrow = RooDataSet("data2_kpi1_2012_L0TIS_narrow","data2_kpi1_2012_L0TIS_narrow",data2_kpi1_2012_L0TIS_narrow_,data2_kpi1_2012_L0TIS_narrow_.get(),"","MCweight2")
	data1_kpi1_2011_L0noTIS_wide = RooDataSet("data1_kpi1_2011_L0noTIS_wide","data1_kpi1_2011_L0noTIS_wide",data1_kpi1_2011_L0noTIS_wide_,data1_kpi1_2011_L0noTIS_wide_.get(),"","MCweight1")
	data2_kpi1_2011_L0noTIS_wide = RooDataSet("data2_kpi1_2011_L0noTIS_wide","data2_kpi1_2011_L0noTIS_wide",data2_kpi1_2011_L0noTIS_wide_,data2_kpi1_2011_L0noTIS_wide_.get(),"","MCweight2")
	data1_kpi1_2012_L0noTIS_wide = RooDataSet("data1_kpi1_2012_L0noTIS_wide","data1_kpi1_2012_L0noTIS_wide",data1_kpi1_2012_L0noTIS_wide_,data1_kpi1_2012_L0noTIS_wide_.get(),"","MCweight1")
	data2_kpi1_2012_L0noTIS_wide = RooDataSet("data2_kpi1_2012_L0noTIS_wide","data2_kpi1_2012_L0noTIS_wide",data2_kpi1_2012_L0noTIS_wide_,data2_kpi1_2012_L0noTIS_wide_.get(),"","MCweight2")
	data1_kpi1_2011_L0noTIS_narrow = RooDataSet("data1_kpi1_2011_L0noTIS_narrow","data1_kpi1_2011_L0noTIS_narrow",data1_kpi1_2011_L0noTIS_narrow_,data1_kpi1_2011_L0noTIS_narrow_.get(),"","MCweight1")
	data2_kpi1_2011_L0noTIS_narrow = RooDataSet("data2_kpi1_2011_L0noTIS_narrow","data2_kpi1_2011_L0noTIS_narrow",data2_kpi1_2011_L0noTIS_narrow_,data2_kpi1_2011_L0noTIS_narrow_.get(),"","MCweight2")
	data1_kpi1_2012_L0noTIS_narrow = RooDataSet("data1_kpi1_2012_L0noTIS_narrow","data1_kpi1_2012_L0noTIS_narrow",data1_kpi1_2012_L0noTIS_narrow_,data1_kpi1_2012_L0noTIS_narrow_.get(),"","MCweight1")
	data2_kpi1_2012_L0noTIS_narrow = RooDataSet("data2_kpi1_2012_L0noTIS_narrow","data2_kpi1_2012_L0noTIS_narrow",data2_kpi1_2012_L0noTIS_narrow_,data2_kpi1_2012_L0noTIS_narrow_.get(),"","MCweight2")
	data1_kpi2_2011_L0TIS_wide = RooDataSet("data1_kpi2_2011_L0TIS_wide","data1_kpi2_2011_L0TIS_wide",data1_kpi2_2011_L0TIS_wide_,data1_kpi2_2011_L0TIS_wide_.get(),"","MCweight1")
	data2_kpi2_2011_L0TIS_wide = RooDataSet("data2_kpi2_2011_L0TIS_wide","data2_kpi2_2011_L0TIS_wide",data2_kpi2_2011_L0TIS_wide_,data2_kpi2_2011_L0TIS_wide_.get(),"","MCweight2")
	data1_kpi2_2012_L0TIS_wide = RooDataSet("data1_kpi2_2012_L0TIS_wide","data1_kpi2_2012_L0TIS_wide",data1_kpi2_2012_L0TIS_wide_,data1_kpi2_2012_L0TIS_wide_.get(),"","MCweight1")
	data2_kpi2_2012_L0TIS_wide = RooDataSet("data2_kpi2_2012_L0TIS_wide","data2_kpi2_2012_L0TIS_wide",data2_kpi2_2012_L0TIS_wide_,data2_kpi2_2012_L0TIS_wide_.get(),"","MCweight2")
	data1_kpi2_2011_L0TIS_narrow = RooDataSet("data1_kpi2_2011_L0TIS_narrow","data1_kpi2_2011_L0TIS_narrow",data1_kpi2_2011_L0TIS_narrow_,data1_kpi2_2011_L0TIS_narrow_.get(),"","MCweight1")
	data2_kpi2_2011_L0TIS_narrow = RooDataSet("data2_kpi2_2011_L0TIS_narrow","data2_kpi2_2011_L0TIS_narrow",data2_kpi2_2011_L0TIS_narrow_,data2_kpi2_2011_L0TIS_narrow_.get(),"","MCweight2")
	data1_kpi2_2012_L0TIS_narrow = RooDataSet("data1_kpi2_2012_L0TIS_narrow","data1_kpi2_2012_L0TIS_narrow",data1_kpi2_2012_L0TIS_narrow_,data1_kpi2_2012_L0TIS_narrow_.get(),"","MCweight1")
	data2_kpi2_2012_L0TIS_narrow = RooDataSet("data2_kpi2_2012_L0TIS_narrow","data2_kpi2_2012_L0TIS_narrow",data2_kpi2_2012_L0TIS_narrow_,data2_kpi2_2012_L0TIS_narrow_.get(),"","MCweight2")
	data1_kpi2_2011_L0noTIS_wide = RooDataSet("data1_kpi2_2011_L0noTIS_wide","data1_kpi2_2011_L0noTIS_wide",data1_kpi2_2011_L0noTIS_wide_,data1_kpi2_2011_L0noTIS_wide_.get(),"","MCweight1")
	data2_kpi2_2011_L0noTIS_wide = RooDataSet("data2_kpi2_2011_L0noTIS_wide","data2_kpi2_2011_L0noTIS_wide",data2_kpi2_2011_L0noTIS_wide_,data2_kpi2_2011_L0noTIS_wide_.get(),"","MCweight2")
	data1_kpi2_2012_L0noTIS_wide = RooDataSet("data1_kpi2_2012_L0noTIS_wide","data1_kpi2_2012_L0noTIS_wide",data1_kpi2_2012_L0noTIS_wide_,data1_kpi2_2012_L0noTIS_wide_.get(),"","MCweight1")
	data2_kpi2_2012_L0noTIS_wide = RooDataSet("data2_kpi2_2012_L0noTIS_wide","data2_kpi2_2012_L0noTIS_wide",data2_kpi2_2012_L0noTIS_wide_,data2_kpi2_2012_L0noTIS_wide_.get(),"","MCweight2")
	data1_kpi2_2011_L0noTIS_narrow = RooDataSet("data1_kpi2_2011_L0noTIS_narrow","data1_kpi2_2011_L0noTIS_narrow",data1_kpi2_2011_L0noTIS_narrow_,data1_kpi2_2011_L0noTIS_narrow_.get(),"","MCweight1")
	data2_kpi2_2011_L0noTIS_narrow = RooDataSet("data2_kpi2_2011_L0noTIS_narrow","data2_kpi2_2011_L0noTIS_narrow",data2_kpi2_2011_L0noTIS_narrow_,data2_kpi2_2011_L0noTIS_narrow_.get(),"","MCweight2")
	data1_kpi2_2012_L0noTIS_narrow = RooDataSet("data1_kpi2_2012_L0noTIS_narrow","data1_kpi2_2012_L0noTIS_narrow",data1_kpi2_2012_L0noTIS_narrow_,data1_kpi2_2012_L0noTIS_narrow_.get(),"","MCweight1")
	data2_kpi2_2012_L0noTIS_narrow = RooDataSet("data2_kpi2_2012_L0noTIS_narrow","data2_kpi2_2012_L0noTIS_narrow",data2_kpi2_2012_L0noTIS_narrow_,data2_kpi2_2012_L0noTIS_narrow_.get(),"","MCweight2")

	print 'Data loaded.'
	file_in.Close()
	file_out.Close()

	return [data1_2011_L0TIS_wide, data1_2012_L0TIS_wide, data2_2011_L0TIS_wide, data2_2012_L0TIS_wide, data3_2011_L0TIS_wide, data3_2012_L0TIS_wide, data4_2011_L0TIS_wide, data4_2012_L0TIS_wide,\
data1_2011_L0TIS_narrow, data1_2012_L0TIS_narrow, data2_2011_L0TIS_narrow, data2_2012_L0TIS_narrow, data3_2011_L0TIS_narrow, data3_2012_L0TIS_narrow, data4_2011_L0TIS_narrow, data4_2012_L0TIS_narrow,\
data1_2011_L0noTIS_wide, data1_2012_L0noTIS_wide, data2_2011_L0noTIS_wide, data2_2012_L0noTIS_wide, data3_2011_L0noTIS_wide, data3_2012_L0noTIS_wide, data4_2011_L0noTIS_wide, data4_2012_L0noTIS_wide,\
data1_2011_L0noTIS_narrow, data1_2012_L0noTIS_narrow, data2_2011_L0noTIS_narrow, data2_2012_L0noTIS_narrow, data3_2011_L0noTIS_narrow, data3_2012_L0noTIS_narrow, data4_2011_L0noTIS_narrow, data4_2012_L0noTIS_narrow, data1_kpi1_2011_L0TIS_wide, data1_kpi1_2012_L0TIS_wide, data2_kpi1_2011_L0TIS_wide, data2_kpi1_2012_L0TIS_wide, data1_kpi1_2011_L0TIS_narrow, data1_kpi1_2012_L0TIS_narrow, data2_kpi1_2011_L0TIS_narrow, data2_kpi1_2012_L0TIS_narrow, data1_kpi1_2011_L0noTIS_wide, data1_kpi1_2012_L0noTIS_wide, data2_kpi1_2011_L0noTIS_wide, data2_kpi1_2012_L0noTIS_wide, data1_kpi1_2011_L0noTIS_narrow, data1_kpi1_2012_L0noTIS_narrow, data2_kpi1_2011_L0noTIS_narrow, data2_kpi1_2012_L0noTIS_narrow, data1_kpi2_2011_L0TIS_wide, data1_kpi2_2012_L0TIS_wide, data2_kpi2_2011_L0TIS_wide, data2_kpi2_2012_L0TIS_wide, data1_kpi2_2011_L0TIS_narrow, data1_kpi2_2012_L0TIS_narrow, data2_kpi2_2011_L0TIS_narrow, data2_kpi2_2012_L0TIS_narrow, data1_kpi2_2011_L0noTIS_wide, data1_kpi2_2012_L0noTIS_wide, data2_kpi2_2011_L0noTIS_wide, data2_kpi2_2012_L0noTIS_wide, data1_kpi2_2011_L0noTIS_narrow, data1_kpi2_2012_L0noTIS_narrow, data2_kpi2_2011_L0noTIS_narrow, data2_kpi2_2012_L0noTIS_narrow]


def LoadDataGen2012(data_file, data_tree, datatype, evnum_limit = 0):

	# Information.
	print 'Loading data file ' + data_file + ' ...'
	if datatype == 0: print 'MC sample: PhSp.'
	elif datatype == 1: print 'MC sample: VV.'
	else: print 'MC sample: PhSp + VV.'
	if (evnum_limit == 0): print 'All events selected.'
	else: print 'Maximum of '+str(evnum_limit)+' events selected per data sample.'
	print 'IMPORTANT: Using 2012 data only.'

	# Input data.
	file_in = TFile(NTUPLE_PATH + data_file)
	tree_full = file_in.Get(data_tree)
	file_out = TFile(NTUPLE_PATH + "trash.root","RECREATE")
	tree_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MC2012settype(datatype))
	tree_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MC2012settype(datatype))

	PDF_gen = CreateGenPDF()

	invN_wide = 1./tree_wide.GetEntries()
	invN_narrow = 1./tree_narrow.GetEntries()

	def setvarvals(entry):
		mKp1_MC.setVal(eval("entry."+m1_name_MC))
		mKp2_MC.setVal(eval("entry."+m2_name_MC))
		mKp1_narrow_MC.setVal(eval("entry."+m1_name_MC))
		mKp2_narrow_MC.setVal(eval("entry."+m2_name_MC))
		cos1_MC.setVal(eval("entry."+cos1_name_MC))
		cos2_MC.setVal(eval("entry."+cos2_name_MC))
		phi_MC.setVal(eval("entry."+phi_name_MC))
		t_MC.setVal(eval("entry."+t_name_MC))

	opt_genmodel.setVal(datatype)

	wide_window_MC.setVal(1)
	ev_counter = 0
	for i in tree_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			setvarvals(i)
			MCweight1.setVal(invN_wide/PDF_gen.evaluate())
			MCweight2.setVal(invN_wide/PDF_gen.evaluate())
			MCweight4.setVal(invN_wide/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_kpi1_gen_wide_.add(RooArgSet(mKp1_MC,MCweight1))
			data1_kpi2_gen_wide_.add(RooArgSet(mKp2_MC,MCweight1))
			data2_kpi1_gen_wide_.add(RooArgSet(cos1_MC,MCweight2))
			data2_kpi2_gen_wide_.add(RooArgSet(cos2_MC,MCweight2))
			data4_gen_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	wide_window_MC.setVal(0)
	ev_counter = 0
	for i in tree_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			setvarvals(i)
			MCweight1.setVal(invN_narrow/PDF_gen.evaluate())
			MCweight2.setVal(invN_narrow/PDF_gen.evaluate())
			MCweight4.setVal(invN_narrow/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_kpi1_gen_narrow_.add(RooArgSet(mKp1_narrow_MC,MCweight1))
			data1_kpi2_gen_narrow_.add(RooArgSet(mKp2_narrow_MC,MCweight1))
			data2_kpi1_gen_narrow_.add(RooArgSet(cos1_MC,MCweight2))
			data2_kpi2_gen_narrow_.add(RooArgSet(cos2_MC,MCweight2))
			data4_gen_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1

	data1_gen_wide_ = RooDataSet("data1_gen_wide_","data1_gen_wide_",RooArgSet(mKp1_MC,mKp2_MC,MCweight1),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data1_kpi1_gen_wide_),RooFit.Import("kpi2",data1_kpi2_gen_wide_))
	data2_gen_wide_ = RooDataSet("data2_gen_wide_","data2_gen_wide_",RooArgSet(cos1_MC,cos2_MC,MCweight2),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data2_kpi1_gen_wide_),RooFit.Import("kpi2",data2_kpi2_gen_wide_))
	data1_gen_narrow_ = RooDataSet("data1_gen_narrow_","data1_gen_narrow_",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,MCweight1),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data1_kpi1_gen_narrow_),RooFit.Import("kpi2",data1_kpi2_gen_narrow_))
	data2_gen_narrow_ = RooDataSet("data2_gen_narrow_","data2_gen_narrow_",RooArgSet(cos1_MC,cos2_MC,MCweight2),RooFit.Index(kpipaircat),RooFit.Import("kpi1",data2_kpi1_gen_narrow_),RooFit.Import("kpi2",data2_kpi2_gen_narrow_))

	data1_gen_wide = RooDataSet("data1_gen_wide","data1_gen_wide",data1_gen_wide_,data1_gen_wide_.get(),"","MCweight1")
	data2_gen_wide = RooDataSet("data2_gen_wide","data2_gen_wide",data2_gen_wide_,data2_gen_wide_.get(),"","MCweight2")
	data4_gen_wide = RooDataSet("data4_gen_wide","data4_gen_wide",data4_gen_wide_,data4_gen_wide_.get(),"","MCweight4")
	data1_gen_narrow = RooDataSet("data1_gen_narrow","data1_gen_narrow",data1_gen_narrow_,data1_gen_narrow_.get(),"","MCweight1")
	data2_gen_narrow = RooDataSet("data2_gen_narrow","data2_gen_narrow",data2_gen_narrow_,data2_gen_narrow_.get(),"","MCweight2")
	data4_gen_narrow = RooDataSet("data4_gen_narrow","data4_gen_narrow",data4_gen_narrow_,data4_gen_narrow_.get(),"","MCweight4")
	data1_kpi1_gen_wide = RooDataSet("data1_kpi1_gen_wide","data1_kpi1_gen_wide",data1_kpi1_gen_wide_,data1_kpi1_gen_wide_.get(),"","MCweight1")
	data1_kpi2_gen_wide = RooDataSet("data1_kpi2_gen_wide","data1_kpi2_gen_wide",data1_kpi2_gen_wide_,data1_kpi2_gen_wide_.get(),"","MCweight1")
	data2_kpi1_gen_wide = RooDataSet("data2_kpi1_gen_wide","data2_kpi1_gen_wide",data2_kpi1_gen_wide_,data2_kpi1_gen_wide_.get(),"","MCweight2")
	data2_kpi2_gen_wide = RooDataSet("data2_kpi2_gen_wide","data2_kpi2_gen_wide",data2_kpi2_gen_wide_,data2_kpi2_gen_wide_.get(),"","MCweight2")
	data1_kpi1_gen_narrow = RooDataSet("data1_kpi1_gen_narrow","data1_kpi1_gen_narrow",data1_kpi1_gen_narrow_,data1_kpi1_gen_narrow_.get(),"","MCweight1")
	data1_kpi2_gen_narrow = RooDataSet("data1_kpi2_gen_narrow","data1_kpi2_gen_narrow",data1_kpi2_gen_narrow_,data1_kpi2_gen_narrow_.get(),"","MCweight1")
	data2_kpi1_gen_narrow = RooDataSet("data2_kpi1_gen_narrow","data2_kpi1_gen_narrow",data2_kpi1_gen_narrow_,data2_kpi1_gen_narrow_.get(),"","MCweight2")
	data2_kpi2_gen_narrow = RooDataSet("data2_kpi2_gen_narrow","data2_kpi2_gen_narrow",data2_kpi2_gen_narrow_,data2_kpi2_gen_narrow_.get(),"","MCweight2")

	print 'Data loaded.'
	file_in.Close()
	file_out.Close()

	return [data1_gen_wide,data2_gen_wide,data4_gen_wide,data1_gen_narrow,data2_gen_narrow,data4_gen_narrow,data1_kpi1_gen_wide,data1_kpi2_gen_wide,\
data2_kpi1_gen_wide,data2_kpi2_gen_wide,data1_kpi1_gen_narrow,data1_kpi2_gen_narrow,data2_kpi1_gen_narrow,data2_kpi2_gen_narrow]


def FitnPlotVisAcc(model_acc_kpi1_2011_L0TIS_wide,model_acc_kpi1_2012_L0TIS_wide,model_acc_kpi1_2011_L0TIS_narrow,model_acc_kpi1_2012_L0TIS_narrow,\
model_acc_kpi1_2011_L0noTIS_wide,model_acc_kpi1_2012_L0noTIS_wide,model_acc_kpi1_2011_L0noTIS_narrow,model_acc_kpi1_2012_L0noTIS_narrow,model_acc_kpi2_2011_L0TIS_wide,\
model_acc_kpi2_2012_L0TIS_wide,model_acc_kpi2_2011_L0TIS_narrow,model_acc_kpi2_2012_L0TIS_narrow,model_acc_kpi2_2011_L0noTIS_wide,model_acc_kpi2_2012_L0noTIS_wide,\
model_acc_kpi2_2011_L0noTIS_narrow,model_acc_kpi2_2012_L0noTIS_narrow,model_acc_2011_L0TIS_wide,model_acc_2012_L0TIS_wide,model_acc_2011_L0TIS_narrow,model_acc_2012_L0TIS_narrow,\
model_acc_2011_L0noTIS_wide,model_acc_2012_L0noTIS_wide,model_acc_2011_L0noTIS_narrow,model_acc_2012_L0noTIS_narrow,model_acc_sim_2011_L0TIS_wide,model_acc_sim_2012_L0TIS_wide,\
model_acc_sim_2011_L0TIS_narrow,model_acc_sim_2012_L0TIS_narrow,model_acc_sim_2011_L0noTIS_wide,model_acc_sim_2012_L0noTIS_wide,model_acc_sim_2011_L0noTIS_narrow,model_acc_sim_2012_L0noTIS_narrow,\
data1_2011_L0TIS_wide,data1_2012_L0TIS_wide,data2_2011_L0TIS_wide,data2_2012_L0TIS_wide,data3_2011_L0TIS_wide,data3_2012_L0TIS_wide,data4_2011_L0TIS_wide,data4_2012_L0TIS_wide,\
data1_2011_L0TIS_narrow,data1_2012_L0TIS_narrow,data2_2011_L0TIS_narrow,data2_2012_L0TIS_narrow,data3_2011_L0TIS_narrow,data3_2012_L0TIS_narrow,data4_2011_L0TIS_narrow,data4_2012_L0TIS_narrow,\
data1_2011_L0noTIS_wide,data1_2012_L0noTIS_wide,data2_2011_L0noTIS_wide,data2_2012_L0noTIS_wide,data3_2011_L0noTIS_wide,data3_2012_L0noTIS_wide,data4_2011_L0noTIS_wide,data4_2012_L0noTIS_wide,\
data1_2011_L0noTIS_narrow,data1_2012_L0noTIS_narrow,data2_2011_L0noTIS_narrow,data2_2012_L0noTIS_narrow,data3_2011_L0noTIS_narrow,data3_2012_L0noTIS_narrow,data4_2011_L0noTIS_narrow,data4_2012_L0noTIS_narrow,\
data1_kpi1_2011_L0TIS_wide,data1_kpi1_2012_L0TIS_wide,data2_kpi1_2011_L0TIS_wide,data2_kpi1_2012_L0TIS_wide,data1_kpi1_2011_L0TIS_narrow,data1_kpi1_2012_L0TIS_narrow,data2_kpi1_2011_L0TIS_narrow,\
data2_kpi1_2012_L0TIS_narrow,data1_kpi1_2011_L0noTIS_wide,data1_kpi1_2012_L0noTIS_wide,data2_kpi1_2011_L0noTIS_wide,data2_kpi1_2012_L0noTIS_wide,data1_kpi1_2011_L0noTIS_narrow,data1_kpi1_2012_L0noTIS_narrow,\
data2_kpi1_2011_L0noTIS_narrow,data2_kpi1_2012_L0noTIS_narrow,data1_kpi2_2011_L0TIS_wide,data1_kpi2_2012_L0TIS_wide,data2_kpi2_2011_L0TIS_wide,data2_kpi2_2012_L0TIS_wide,data1_kpi2_2011_L0TIS_narrow,\
data1_kpi2_2012_L0TIS_narrow,data2_kpi2_2011_L0TIS_narrow,data2_kpi2_2012_L0TIS_narrow,data1_kpi2_2011_L0noTIS_wide,data1_kpi2_2012_L0noTIS_wide,data2_kpi2_2011_L0noTIS_wide,data2_kpi2_2012_L0noTIS_wide,\
data1_kpi2_2011_L0noTIS_narrow,data1_kpi2_2012_L0noTIS_narrow,data2_kpi2_2011_L0noTIS_narrow,data2_kpi2_2012_L0noTIS_narrow):

	# Fitting

	opt_acc.setVal(1)
	map(lambda x:x.setConstant(1),[cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0TIS_wide,k2_2011_L0TIS_wide,k3_2011_L0TIS_wide,k4_2011_L0TIS_wide,k5_2011_L0TIS_wide,a_acc_2011_L0TIS_wide,b_acc_2011_L0TIS_wide,c_acc_2011_L0TIS_wide,\
k1_2012_L0TIS_wide,k2_2012_L0TIS_wide,k3_2012_L0TIS_wide,k4_2012_L0TIS_wide,k5_2012_L0TIS_wide,a_acc_2012_L0TIS_wide,b_acc_2012_L0TIS_wide,c_acc_2012_L0TIS_wide,\
k1_2011_L0TIS_narrow,k2_2011_L0TIS_narrow,k3_2011_L0TIS_narrow,k4_2011_L0TIS_narrow,k5_2011_L0TIS_narrow,a_acc_2011_L0TIS_narrow,b_acc_2011_L0TIS_narrow,c_acc_2011_L0TIS_narrow,\
k1_2012_L0TIS_narrow,k2_2012_L0TIS_narrow,k3_2012_L0TIS_narrow,k4_2012_L0TIS_narrow,k5_2012_L0TIS_narrow,a_acc_2012_L0TIS_narrow,b_acc_2012_L0TIS_narrow,c_acc_2012_L0TIS_narrow,\
k1_2011_L0noTIS_wide,k2_2011_L0noTIS_wide,k3_2011_L0noTIS_wide,k4_2011_L0noTIS_wide,k5_2011_L0noTIS_wide,a_acc_2011_L0noTIS_wide,b_acc_2011_L0noTIS_wide,c_acc_2011_L0noTIS_wide,\
k1_2012_L0noTIS_wide,k2_2012_L0noTIS_wide,k3_2012_L0noTIS_wide,k4_2012_L0noTIS_wide,k5_2012_L0noTIS_wide,a_acc_2012_L0noTIS_wide,b_acc_2012_L0noTIS_wide,c_acc_2012_L0noTIS_wide,\
k1_2011_L0noTIS_narrow,k2_2011_L0noTIS_narrow,k3_2011_L0noTIS_narrow,k4_2011_L0noTIS_narrow,k5_2011_L0noTIS_narrow,a_acc_2011_L0noTIS_narrow,b_acc_2011_L0noTIS_narrow,c_acc_2011_L0noTIS_narrow,\
k1_2012_L0noTIS_narrow,k2_2012_L0noTIS_narrow,k3_2012_L0noTIS_narrow,k4_2012_L0noTIS_narrow,k5_2012_L0noTIS_narrow,a_acc_2012_L0noTIS_narrow,b_acc_2012_L0noTIS_narrow,c_acc_2012_L0noTIS_narrow])
	model_acc_sim_2011_L0TIS_wide.fitTo(data1_2011_L0TIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2012_L0TIS_wide.fitTo(data1_2012_L0TIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2011_L0TIS_narrow.fitTo(data1_2011_L0TIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2012_L0TIS_narrow.fitTo(data1_2012_L0TIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2011_L0noTIS_wide.fitTo(data1_2011_L0noTIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2012_L0noTIS_wide.fitTo(data1_2012_L0noTIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2011_L0noTIS_narrow.fitTo(data1_2011_L0noTIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2012_L0noTIS_narrow.fitTo(data1_2012_L0noTIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	map(lambda x:x.setConstant(0),[cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_L0TIS_wide,k2_2011_L0TIS_wide,k3_2011_L0TIS_wide,k4_2011_L0TIS_wide,k5_2011_L0TIS_wide,a_acc_2011_L0TIS_wide,b_acc_2011_L0TIS_wide,c_acc_2011_L0TIS_wide,\
k1_2012_L0TIS_wide,k2_2012_L0TIS_wide,k3_2012_L0TIS_wide,k4_2012_L0TIS_wide,k5_2012_L0TIS_wide,a_acc_2012_L0TIS_wide,b_acc_2012_L0TIS_wide,c_acc_2012_L0TIS_wide,\
k1_2011_L0TIS_narrow,k2_2011_L0TIS_narrow,k3_2011_L0TIS_narrow,k4_2011_L0TIS_narrow,k5_2011_L0TIS_narrow,a_acc_2011_L0TIS_narrow,b_acc_2011_L0TIS_narrow,c_acc_2011_L0TIS_narrow,\
k1_2012_L0TIS_narrow,k2_2012_L0TIS_narrow,k3_2012_L0TIS_narrow,k4_2012_L0TIS_narrow,k5_2012_L0TIS_narrow,a_acc_2012_L0TIS_narrow,b_acc_2012_L0TIS_narrow,c_acc_2012_L0TIS_narrow,\
k1_2011_L0noTIS_wide,k2_2011_L0noTIS_wide,k3_2011_L0noTIS_wide,k4_2011_L0noTIS_wide,k5_2011_L0noTIS_wide,a_acc_2011_L0noTIS_wide,b_acc_2011_L0noTIS_wide,c_acc_2011_L0noTIS_wide,\
k1_2012_L0noTIS_wide,k2_2012_L0noTIS_wide,k3_2012_L0noTIS_wide,k4_2012_L0noTIS_wide,k5_2012_L0noTIS_wide,a_acc_2012_L0noTIS_wide,b_acc_2012_L0noTIS_wide,c_acc_2012_L0noTIS_wide,\
k1_2011_L0noTIS_narrow,k2_2011_L0noTIS_narrow,k3_2011_L0noTIS_narrow,k4_2011_L0noTIS_narrow,k5_2011_L0noTIS_narrow,a_acc_2011_L0noTIS_narrow,b_acc_2011_L0noTIS_narrow,c_acc_2011_L0noTIS_narrow,\
k1_2012_L0noTIS_narrow,k2_2012_L0noTIS_narrow,k3_2012_L0noTIS_narrow,k4_2012_L0noTIS_narrow,k5_2012_L0noTIS_narrow,a_acc_2012_L0noTIS_narrow,b_acc_2012_L0noTIS_narrow,c_acc_2012_L0noTIS_narrow])
	opt_acc.setVal(2)
	map(lambda x:x.setConstant(1),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,phi_MC,t_MC,p1_2011_L0TIS_wide,a_acc_2011_L0TIS_wide,b_acc_2011_L0TIS_wide,c_acc_2011_L0TIS_wide,p1_2012_L0TIS_wide,a_acc_2012_L0TIS_wide,b_acc_2012_L0TIS_wide,c_acc_2012_L0TIS_wide,\
p1_2011_L0TIS_narrow,a_acc_2011_L0TIS_narrow,b_acc_2011_L0TIS_narrow,c_acc_2011_L0TIS_narrow,p1_2012_L0TIS_narrow,a_acc_2012_L0TIS_narrow,b_acc_2012_L0TIS_narrow,c_acc_2012_L0TIS_narrow,\
p1_2011_L0noTIS_wide,a_acc_2011_L0noTIS_wide,b_acc_2011_L0noTIS_wide,c_acc_2011_L0noTIS_wide,p1_2012_L0noTIS_wide,a_acc_2012_L0noTIS_wide,b_acc_2012_L0noTIS_wide,c_acc_2012_L0noTIS_wide,\
p1_2011_L0noTIS_narrow,a_acc_2011_L0noTIS_narrow,b_acc_2011_L0noTIS_narrow,c_acc_2011_L0noTIS_narrow,p1_2012_L0noTIS_narrow,a_acc_2012_L0noTIS_narrow,b_acc_2012_L0noTIS_narrow,c_acc_2012_L0noTIS_narrow])
	model_acc_sim_2011_L0TIS_wide.fitTo(data2_2011_L0TIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2012_L0TIS_wide.fitTo(data2_2012_L0TIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2011_L0TIS_narrow.fitTo(data2_2011_L0TIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2012_L0TIS_narrow.fitTo(data2_2012_L0TIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2011_L0noTIS_wide.fitTo(data2_2011_L0noTIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2012_L0noTIS_wide.fitTo(data2_2012_L0noTIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2011_L0noTIS_narrow.fitTo(data2_2011_L0noTIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_2012_L0noTIS_narrow.fitTo(data2_2012_L0noTIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	map(lambda x:x.setConstant(0),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,phi_MC,t_MC,p1_2011_L0TIS_wide,a_acc_2011_L0TIS_wide,b_acc_2011_L0TIS_wide,c_acc_2011_L0TIS_wide,p1_2012_L0TIS_wide,a_acc_2012_L0TIS_wide,b_acc_2012_L0TIS_wide,c_acc_2012_L0TIS_wide,\
p1_2011_L0TIS_narrow,a_acc_2011_L0TIS_narrow,b_acc_2011_L0TIS_narrow,c_acc_2011_L0TIS_narrow,p1_2012_L0TIS_narrow,a_acc_2012_L0TIS_narrow,b_acc_2012_L0TIS_narrow,c_acc_2012_L0TIS_narrow,\
p1_2011_L0noTIS_wide,a_acc_2011_L0noTIS_wide,b_acc_2011_L0noTIS_wide,c_acc_2011_L0noTIS_wide,p1_2012_L0noTIS_wide,a_acc_2012_L0noTIS_wide,b_acc_2012_L0noTIS_wide,c_acc_2012_L0noTIS_wide,\
p1_2011_L0noTIS_narrow,a_acc_2011_L0noTIS_narrow,b_acc_2011_L0noTIS_narrow,c_acc_2011_L0noTIS_narrow,p1_2012_L0noTIS_narrow,a_acc_2012_L0noTIS_narrow,b_acc_2012_L0noTIS_narrow,c_acc_2012_L0noTIS_narrow])
	opt_acc.setVal(3)
	map(lambda x:x.setConstant(1),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,t_MC,p1_2011_L0TIS_wide,k1_2011_L0TIS_wide,k2_2011_L0TIS_wide,k3_2011_L0TIS_wide,k4_2011_L0TIS_wide,k5_2011_L0TIS_wide,a_acc_2011_L0TIS_wide,b_acc_2011_L0TIS_wide,c_acc_2011_L0TIS_wide,\
p1_2012_L0TIS_wide,k1_2012_L0TIS_wide,k2_2012_L0TIS_wide,k3_2012_L0TIS_wide,k4_2012_L0TIS_wide,k5_2012_L0TIS_wide,a_acc_2012_L0TIS_wide,b_acc_2012_L0TIS_wide,c_acc_2012_L0TIS_wide,\
p1_2011_L0TIS_narrow,k1_2011_L0TIS_narrow,k2_2011_L0TIS_narrow,k3_2011_L0TIS_narrow,k4_2011_L0TIS_narrow,k5_2011_L0TIS_narrow,a_acc_2011_L0TIS_narrow,b_acc_2011_L0TIS_narrow,c_acc_2011_L0TIS_narrow,\
p1_2012_L0TIS_narrow,k1_2012_L0TIS_narrow,k2_2012_L0TIS_narrow,k3_2012_L0TIS_narrow,k4_2012_L0TIS_narrow,k5_2012_L0TIS_narrow,a_acc_2012_L0TIS_narrow,b_acc_2012_L0TIS_narrow,c_acc_2012_L0TIS_narrow,\
p1_2011_L0noTIS_wide,k1_2011_L0noTIS_wide,k2_2011_L0noTIS_wide,k3_2011_L0noTIS_wide,k4_2011_L0noTIS_wide,k5_2011_L0noTIS_wide,a_acc_2011_L0noTIS_wide,b_acc_2011_L0noTIS_wide,c_acc_2011_L0noTIS_wide,\
p1_2012_L0noTIS_wide,k1_2012_L0noTIS_wide,k2_2012_L0noTIS_wide,k3_2012_L0noTIS_wide,k4_2012_L0noTIS_wide,k5_2012_L0noTIS_wide,a_acc_2012_L0noTIS_wide,b_acc_2012_L0noTIS_wide,c_acc_2012_L0noTIS_wide,\
p1_2011_L0noTIS_narrow,k1_2011_L0noTIS_narrow,k2_2011_L0noTIS_narrow,k3_2011_L0noTIS_narrow,k4_2011_L0noTIS_narrow,k5_2011_L0noTIS_narrow,a_acc_2011_L0noTIS_narrow,b_acc_2011_L0noTIS_narrow,c_acc_2011_L0noTIS_narrow,\
p1_2012_L0noTIS_narrow,k1_2012_L0noTIS_narrow,k2_2012_L0noTIS_narrow,k3_2012_L0noTIS_narrow,k4_2012_L0noTIS_narrow,k5_2012_L0noTIS_narrow,a_acc_2012_L0noTIS_narrow,b_acc_2012_L0noTIS_narrow,c_acc_2012_L0noTIS_narrow])
	model_acc_2011_L0TIS_wide.fitTo(data3_2011_L0TIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_L0TIS_wide.fitTo(data3_2012_L0TIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2011_L0TIS_narrow.fitTo(data3_2011_L0TIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_L0TIS_narrow.fitTo(data3_2012_L0TIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2011_L0noTIS_wide.fitTo(data3_2011_L0noTIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_L0noTIS_wide.fitTo(data3_2012_L0noTIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2011_L0noTIS_narrow.fitTo(data3_2011_L0noTIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_L0noTIS_narrow.fitTo(data3_2012_L0noTIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	map(lambda x:x.setConstant(0),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,t_MC,p1_2011_L0TIS_wide,k1_2011_L0TIS_wide,k2_2011_L0TIS_wide,k3_2011_L0TIS_wide,k4_2011_L0TIS_wide,k5_2011_L0TIS_wide,a_acc_2011_L0TIS_wide,b_acc_2011_L0TIS_wide,c_acc_2011_L0TIS_wide,\
p1_2012_L0TIS_wide,k1_2012_L0TIS_wide,k2_2012_L0TIS_wide,k3_2012_L0TIS_wide,k4_2012_L0TIS_wide,k5_2012_L0TIS_wide,a_acc_2012_L0TIS_wide,b_acc_2012_L0TIS_wide,c_acc_2012_L0TIS_wide,\
p1_2011_L0TIS_narrow,k1_2011_L0TIS_narrow,k2_2011_L0TIS_narrow,k3_2011_L0TIS_narrow,k4_2011_L0TIS_narrow,k5_2011_L0TIS_narrow,a_acc_2011_L0TIS_narrow,b_acc_2011_L0TIS_narrow,c_acc_2011_L0TIS_narrow,\
p1_2012_L0TIS_narrow,k1_2012_L0TIS_narrow,k2_2012_L0TIS_narrow,k3_2012_L0TIS_narrow,k4_2012_L0TIS_narrow,k5_2012_L0TIS_narrow,a_acc_2012_L0TIS_narrow,b_acc_2012_L0TIS_narrow,c_acc_2012_L0TIS_narrow,\
p1_2011_L0noTIS_wide,k1_2011_L0noTIS_wide,k2_2011_L0noTIS_wide,k3_2011_L0noTIS_wide,k4_2011_L0noTIS_wide,k5_2011_L0noTIS_wide,a_acc_2011_L0noTIS_wide,b_acc_2011_L0noTIS_wide,c_acc_2011_L0noTIS_wide,\
p1_2012_L0noTIS_wide,k1_2012_L0noTIS_wide,k2_2012_L0noTIS_wide,k3_2012_L0noTIS_wide,k4_2012_L0noTIS_wide,k5_2012_L0noTIS_wide,a_acc_2012_L0noTIS_wide,b_acc_2012_L0noTIS_wide,c_acc_2012_L0noTIS_wide,\
p1_2011_L0noTIS_narrow,k1_2011_L0noTIS_narrow,k2_2011_L0noTIS_narrow,k3_2011_L0noTIS_narrow,k4_2011_L0noTIS_narrow,k5_2011_L0noTIS_narrow,a_acc_2011_L0noTIS_narrow,b_acc_2011_L0noTIS_narrow,c_acc_2011_L0noTIS_narrow,\
p1_2012_L0noTIS_narrow,k1_2012_L0noTIS_narrow,k2_2012_L0noTIS_narrow,k3_2012_L0noTIS_narrow,k4_2012_L0noTIS_narrow,k5_2012_L0noTIS_narrow,a_acc_2012_L0noTIS_narrow,b_acc_2012_L0noTIS_narrow,c_acc_2012_L0noTIS_narrow])
	opt_acc.setVal(4)
	map(lambda x:x.setConstant(1),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,p1_2011_L0TIS_wide,k1_2011_L0TIS_wide,k2_2011_L0TIS_wide,k3_2011_L0TIS_wide,k4_2011_L0TIS_wide,k5_2011_L0TIS_wide,\
p1_2012_L0TIS_wide,k1_2012_L0TIS_wide,k2_2012_L0TIS_wide,k3_2012_L0TIS_wide,k4_2012_L0TIS_wide,k5_2012_L0TIS_wide,\
p1_2011_L0TIS_narrow,k1_2011_L0TIS_narrow,k2_2011_L0TIS_narrow,k3_2011_L0TIS_narrow,k4_2011_L0TIS_narrow,k5_2011_L0TIS_narrow,\
p1_2012_L0TIS_narrow,k1_2012_L0TIS_narrow,k2_2012_L0TIS_narrow,k3_2012_L0TIS_narrow,k4_2012_L0TIS_narrow,k5_2012_L0TIS_narrow,\
p1_2011_L0noTIS_wide,k1_2011_L0noTIS_wide,k2_2011_L0noTIS_wide,k3_2011_L0noTIS_wide,k4_2011_L0noTIS_wide,k5_2011_L0noTIS_wide,\
p1_2012_L0noTIS_wide,k1_2012_L0noTIS_wide,k2_2012_L0noTIS_wide,k3_2012_L0noTIS_wide,k4_2012_L0noTIS_wide,k5_2012_L0noTIS_wide,\
p1_2011_L0noTIS_narrow,k1_2011_L0noTIS_narrow,k2_2011_L0noTIS_narrow,k3_2011_L0noTIS_narrow,k4_2011_L0noTIS_narrow,k5_2011_L0noTIS_narrow,\
p1_2012_L0noTIS_narrow,k1_2012_L0noTIS_narrow,k2_2012_L0noTIS_narrow,k3_2012_L0noTIS_narrow,k4_2012_L0noTIS_narrow,k5_2012_L0noTIS_narrow])
	model_acc_2011_L0TIS_wide.fitTo(data4_2011_L0TIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_L0TIS_wide.fitTo(data4_2012_L0TIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2011_L0TIS_narrow.fitTo(data4_2011_L0TIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_L0TIS_narrow.fitTo(data4_2012_L0TIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2011_L0noTIS_wide.fitTo(data4_2011_L0noTIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_L0noTIS_wide.fitTo(data4_2012_L0noTIS_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2011_L0noTIS_narrow.fitTo(data4_2011_L0noTIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_L0noTIS_narrow.fitTo(data4_2012_L0noTIS_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	map(lambda x:x.setConstant(0),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,p1_2011_L0TIS_wide,k1_2011_L0TIS_wide,k2_2011_L0TIS_wide,k3_2011_L0TIS_wide,k4_2011_L0TIS_wide,k5_2011_L0TIS_wide,\
p1_2012_L0TIS_wide,k1_2012_L0TIS_wide,k2_2012_L0TIS_wide,k3_2012_L0TIS_wide,k4_2012_L0TIS_wide,k5_2012_L0TIS_wide,\
p1_2011_L0TIS_narrow,k1_2011_L0TIS_narrow,k2_2011_L0TIS_narrow,k3_2011_L0TIS_narrow,k4_2011_L0TIS_narrow,k5_2011_L0TIS_narrow,\
p1_2012_L0TIS_narrow,k1_2012_L0TIS_narrow,k2_2012_L0TIS_narrow,k3_2012_L0TIS_narrow,k4_2012_L0TIS_narrow,k5_2012_L0TIS_narrow,\
p1_2011_L0noTIS_wide,k1_2011_L0noTIS_wide,k2_2011_L0noTIS_wide,k3_2011_L0noTIS_wide,k4_2011_L0noTIS_wide,k5_2011_L0noTIS_wide,\
p1_2012_L0noTIS_wide,k1_2012_L0noTIS_wide,k2_2012_L0noTIS_wide,k3_2012_L0noTIS_wide,k4_2012_L0noTIS_wide,k5_2012_L0noTIS_wide,\
p1_2011_L0noTIS_narrow,k1_2011_L0noTIS_narrow,k2_2011_L0noTIS_narrow,k3_2011_L0noTIS_narrow,k4_2011_L0noTIS_narrow,k5_2011_L0noTIS_narrow,\
p1_2012_L0noTIS_narrow,k1_2012_L0noTIS_narrow,k2_2012_L0noTIS_narrow,k3_2012_L0noTIS_narrow,k4_2012_L0noTIS_narrow,k5_2012_L0noTIS_narrow])

	# Plotting

	data1_kpi1_2011_L0TIS_wide.plotOn(frame_m1_MC_2011_L0TIS_wide,RooFit.Binning(20))
	data1_kpi2_2011_L0TIS_wide.plotOn(frame_m2_MC_2011_L0TIS_wide,RooFit.Binning(20))
	data2_kpi1_2011_L0TIS_wide.plotOn(frame_cos1_MC_2011_L0TIS_wide,RooFit.Binning(20))
	data2_kpi2_2011_L0TIS_wide.plotOn(frame_cos2_MC_2011_L0TIS_wide,RooFit.Binning(20))
	data3_2011_L0TIS_wide.plotOn(frame_phi_MC_2011_L0TIS_wide,RooFit.Binning(20))
	data4_2011_L0TIS_wide.plotOn(frame_t_MC_2011_L0TIS_wide,RooFit.Binning(20))
	data1_kpi1_2012_L0TIS_wide.plotOn(frame_m1_MC_2012_L0TIS_wide,RooFit.Binning(20))
	data1_kpi2_2012_L0TIS_wide.plotOn(frame_m2_MC_2012_L0TIS_wide,RooFit.Binning(20))
	data2_kpi1_2012_L0TIS_wide.plotOn(frame_cos1_MC_2012_L0TIS_wide,RooFit.Binning(20))
	data2_kpi2_2012_L0TIS_wide.plotOn(frame_cos2_MC_2012_L0TIS_wide,RooFit.Binning(20))
	data3_2012_L0TIS_wide.plotOn(frame_phi_MC_2012_L0TIS_wide,RooFit.Binning(20))
	data4_2012_L0TIS_wide.plotOn(frame_t_MC_2012_L0TIS_wide,RooFit.Binning(20))
	data1_kpi1_2011_L0TIS_narrow.plotOn(frame_m1_MC_2011_L0TIS_narrow,RooFit.Binning(12))
	data1_kpi2_2011_L0TIS_narrow.plotOn(frame_m2_MC_2011_L0TIS_narrow,RooFit.Binning(12))
	data2_kpi1_2011_L0TIS_narrow.plotOn(frame_cos1_MC_2011_L0TIS_narrow,RooFit.Binning(12))
	data2_kpi2_2011_L0TIS_narrow.plotOn(frame_cos2_MC_2011_L0TIS_narrow,RooFit.Binning(12))
	data3_2011_L0TIS_narrow.plotOn(frame_phi_MC_2011_L0TIS_narrow,RooFit.Binning(12))
	data4_2011_L0TIS_narrow.plotOn(frame_t_MC_2011_L0TIS_narrow,RooFit.Binning(12))
	data1_kpi1_2012_L0TIS_narrow.plotOn(frame_m1_MC_2012_L0TIS_narrow,RooFit.Binning(12))
	data1_kpi2_2012_L0TIS_narrow.plotOn(frame_m2_MC_2012_L0TIS_narrow,RooFit.Binning(12))
	data2_kpi1_2012_L0TIS_narrow.plotOn(frame_cos1_MC_2012_L0TIS_narrow,RooFit.Binning(12))
	data2_kpi2_2012_L0TIS_narrow.plotOn(frame_cos2_MC_2012_L0TIS_narrow,RooFit.Binning(12))
	data3_2012_L0TIS_narrow.plotOn(frame_phi_MC_2012_L0TIS_narrow,RooFit.Binning(12))
	data4_2012_L0TIS_narrow.plotOn(frame_t_MC_2012_L0TIS_narrow,RooFit.Binning(12))
	data1_kpi1_2011_L0noTIS_wide.plotOn(frame_m1_MC_2011_L0noTIS_wide,RooFit.Binning(20))
	data1_kpi2_2011_L0noTIS_wide.plotOn(frame_m2_MC_2011_L0noTIS_wide,RooFit.Binning(20))
	data2_kpi1_2011_L0noTIS_wide.plotOn(frame_cos1_MC_2011_L0noTIS_wide,RooFit.Binning(20))
	data2_kpi2_2011_L0noTIS_wide.plotOn(frame_cos2_MC_2011_L0noTIS_wide,RooFit.Binning(20))
	data3_2011_L0noTIS_wide.plotOn(frame_phi_MC_2011_L0noTIS_wide,RooFit.Binning(20))
	data4_2011_L0noTIS_wide.plotOn(frame_t_MC_2011_L0noTIS_wide,RooFit.Binning(20))
	data1_kpi1_2012_L0noTIS_wide.plotOn(frame_m1_MC_2012_L0noTIS_wide,RooFit.Binning(20))
	data1_kpi2_2012_L0noTIS_wide.plotOn(frame_m2_MC_2012_L0noTIS_wide,RooFit.Binning(20))
	data2_kpi1_2012_L0noTIS_wide.plotOn(frame_cos1_MC_2012_L0noTIS_wide,RooFit.Binning(20))
	data2_kpi2_2012_L0noTIS_wide.plotOn(frame_cos2_MC_2012_L0noTIS_wide,RooFit.Binning(20))
	data3_2012_L0noTIS_wide.plotOn(frame_phi_MC_2012_L0noTIS_wide,RooFit.Binning(20))
	data4_2012_L0noTIS_wide.plotOn(frame_t_MC_2012_L0noTIS_wide,RooFit.Binning(20))
	data1_kpi1_2011_L0noTIS_narrow.plotOn(frame_m1_MC_2011_L0noTIS_narrow,RooFit.Binning(12))
	data1_kpi2_2011_L0noTIS_narrow.plotOn(frame_m2_MC_2011_L0noTIS_narrow,RooFit.Binning(12))
	data2_kpi1_2011_L0noTIS_narrow.plotOn(frame_cos1_MC_2011_L0noTIS_narrow,RooFit.Binning(12))
	data2_kpi2_2011_L0noTIS_narrow.plotOn(frame_cos2_MC_2011_L0noTIS_narrow,RooFit.Binning(12))
	data3_2011_L0noTIS_narrow.plotOn(frame_phi_MC_2011_L0noTIS_narrow,RooFit.Binning(12))
	data4_2011_L0noTIS_narrow.plotOn(frame_t_MC_2011_L0noTIS_narrow,RooFit.Binning(12))
	data1_kpi1_2012_L0noTIS_narrow.plotOn(frame_m1_MC_2012_L0noTIS_narrow,RooFit.Binning(12))
	data1_kpi2_2012_L0noTIS_narrow.plotOn(frame_m2_MC_2012_L0noTIS_narrow,RooFit.Binning(12))
	data2_kpi1_2012_L0noTIS_narrow.plotOn(frame_cos1_MC_2012_L0noTIS_narrow,RooFit.Binning(12))
	data2_kpi2_2012_L0noTIS_narrow.plotOn(frame_cos2_MC_2012_L0noTIS_narrow,RooFit.Binning(12))
	data3_2012_L0noTIS_narrow.plotOn(frame_phi_MC_2012_L0noTIS_narrow,RooFit.Binning(12))
	data4_2012_L0noTIS_narrow.plotOn(frame_t_MC_2012_L0noTIS_narrow,RooFit.Binning(12))
	opt_acc.setVal(1)
	model_acc_kpi1_2011_L0TIS_wide.plotOn(frame_m1_MC_2011_L0TIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2011_L0TIS_wide.plotOn(frame_m2_MC_2011_L0TIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2012_L0TIS_wide.plotOn(frame_m1_MC_2012_L0TIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2012_L0TIS_wide.plotOn(frame_m2_MC_2012_L0TIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2011_L0TIS_narrow.plotOn(frame_m1_MC_2011_L0TIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2011_L0TIS_narrow.plotOn(frame_m2_MC_2011_L0TIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2012_L0TIS_narrow.plotOn(frame_m1_MC_2012_L0TIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2012_L0TIS_narrow.plotOn(frame_m2_MC_2012_L0TIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2011_L0noTIS_wide.plotOn(frame_m1_MC_2011_L0noTIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2011_L0noTIS_wide.plotOn(frame_m2_MC_2011_L0noTIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2012_L0noTIS_wide.plotOn(frame_m1_MC_2012_L0noTIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2012_L0noTIS_wide.plotOn(frame_m2_MC_2012_L0noTIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2011_L0noTIS_narrow.plotOn(frame_m1_MC_2011_L0noTIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2011_L0noTIS_narrow.plotOn(frame_m2_MC_2011_L0noTIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2012_L0noTIS_narrow.plotOn(frame_m1_MC_2012_L0noTIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2012_L0noTIS_narrow.plotOn(frame_m2_MC_2012_L0noTIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(2)
	model_acc_kpi1_2011_L0TIS_wide.plotOn(frame_cos1_MC_2011_L0TIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2011_L0TIS_wide.plotOn(frame_cos2_MC_2011_L0TIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2012_L0TIS_wide.plotOn(frame_cos1_MC_2012_L0TIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2012_L0TIS_wide.plotOn(frame_cos2_MC_2012_L0TIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2011_L0TIS_narrow.plotOn(frame_cos1_MC_2011_L0TIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2011_L0TIS_narrow.plotOn(frame_cos2_MC_2011_L0TIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2012_L0TIS_narrow.plotOn(frame_cos1_MC_2012_L0TIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2012_L0TIS_narrow.plotOn(frame_cos2_MC_2012_L0TIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2011_L0noTIS_wide.plotOn(frame_cos1_MC_2011_L0noTIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2011_L0noTIS_wide.plotOn(frame_cos2_MC_2011_L0noTIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2012_L0noTIS_wide.plotOn(frame_cos1_MC_2012_L0noTIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2012_L0noTIS_wide.plotOn(frame_cos2_MC_2012_L0noTIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2011_L0noTIS_narrow.plotOn(frame_cos1_MC_2011_L0noTIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2011_L0noTIS_narrow.plotOn(frame_cos2_MC_2011_L0noTIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2012_L0noTIS_narrow.plotOn(frame_cos1_MC_2012_L0noTIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2012_L0noTIS_narrow.plotOn(frame_cos2_MC_2012_L0noTIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(3)
	model_acc_2011_L0TIS_wide.plotOn(frame_phi_MC_2011_L0TIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_L0TIS_wide.plotOn(frame_phi_MC_2012_L0TIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_L0TIS_narrow.plotOn(frame_phi_MC_2011_L0TIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_L0TIS_narrow.plotOn(frame_phi_MC_2012_L0TIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_L0noTIS_wide.plotOn(frame_phi_MC_2011_L0noTIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_L0noTIS_wide.plotOn(frame_phi_MC_2012_L0noTIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_L0noTIS_narrow.plotOn(frame_phi_MC_2011_L0noTIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_L0noTIS_narrow.plotOn(frame_phi_MC_2012_L0noTIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(4)
	model_acc_2011_L0TIS_wide.plotOn(frame_t_MC_2011_L0TIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_L0TIS_wide.plotOn(frame_t_MC_2012_L0TIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_L0TIS_narrow.plotOn(frame_t_MC_2011_L0TIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_L0TIS_narrow.plotOn(frame_t_MC_2012_L0TIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_L0noTIS_wide.plotOn(frame_t_MC_2011_L0noTIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_L0noTIS_wide.plotOn(frame_t_MC_2012_L0noTIS_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_L0noTIS_narrow.plotOn(frame_t_MC_2011_L0noTIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_L0noTIS_narrow.plotOn(frame_t_MC_2012_L0noTIS_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))

	cvis_2011_L0TIS_wide = TCanvas("cvis_2011_L0TIS_wide","cvis_2011_L0TIS_wide",1200,600)
	cvis_2011_L0TIS_wide.Divide(3,2)
	cvis_2011_L0TIS_wide.cd(1)
	frame_cos1_MC_2011_L0TIS_wide.Draw()
	cvis_2011_L0TIS_wide.cd(2)
	frame_cos2_MC_2011_L0TIS_wide.Draw()
	cvis_2011_L0TIS_wide.cd(3)
	frame_phi_MC_2011_L0TIS_wide.Draw()
	cvis_2011_L0TIS_wide.cd(4)
	frame_m1_MC_2011_L0TIS_wide.Draw()
	cvis_2011_L0TIS_wide.cd(5)
	frame_m2_MC_2011_L0TIS_wide.Draw()
	cvis_2011_L0TIS_wide.cd(6)
	frame_t_MC_2011_L0TIS_wide.Draw()
	cvis_2012_L0TIS_wide = TCanvas("cvis_2012_L0TIS_wide","cvis_2012_L0TIS_wide",1200,600)
	cvis_2012_L0TIS_wide.Divide(3,2)
	cvis_2012_L0TIS_wide.cd(1)
	frame_cos1_MC_2012_L0TIS_wide.Draw()
	cvis_2012_L0TIS_wide.cd(2)
	frame_cos2_MC_2012_L0TIS_wide.Draw()
	cvis_2012_L0TIS_wide.cd(3)
	frame_phi_MC_2012_L0TIS_wide.Draw()
	cvis_2012_L0TIS_wide.cd(4)
	frame_m1_MC_2012_L0TIS_wide.Draw()
	cvis_2012_L0TIS_wide.cd(5)
	frame_m2_MC_2012_L0TIS_wide.Draw()
	cvis_2012_L0TIS_wide.cd(6)
	frame_t_MC_2012_L0TIS_wide.Draw()
	cvis_2011_L0TIS_narrow = TCanvas("cvis_2011_L0TIS_narrow","cvis_2011_L0TIS_narrow",1200,600)
	cvis_2011_L0TIS_narrow.Divide(3,2)
	cvis_2011_L0TIS_narrow.cd(1)
	frame_cos1_MC_2011_L0TIS_narrow.Draw()
	cvis_2011_L0TIS_narrow.cd(2)
	frame_cos2_MC_2011_L0TIS_narrow.Draw()
	cvis_2011_L0TIS_narrow.cd(3)
	frame_phi_MC_2011_L0TIS_narrow.Draw()
	cvis_2011_L0TIS_narrow.cd(4)
	frame_m1_MC_2011_L0TIS_narrow.Draw()
	cvis_2011_L0TIS_narrow.cd(5)
	frame_m2_MC_2011_L0TIS_narrow.Draw()
	cvis_2011_L0TIS_narrow.cd(6)
	frame_t_MC_2011_L0TIS_narrow.Draw()
	cvis_2012_L0TIS_narrow = TCanvas("cvis_2012_L0TIS_narrow","cvis_2012_L0TIS_narrow",1200,600)
	cvis_2012_L0TIS_narrow.Divide(3,2)
	cvis_2012_L0TIS_narrow.cd(1)
	frame_cos1_MC_2012_L0TIS_narrow.Draw()
	cvis_2012_L0TIS_narrow.cd(2)
	frame_cos2_MC_2012_L0TIS_narrow.Draw()
	cvis_2012_L0TIS_narrow.cd(3)
	frame_phi_MC_2012_L0TIS_narrow.Draw()
	cvis_2012_L0TIS_narrow.cd(4)
	frame_m1_MC_2012_L0TIS_narrow.Draw()
	cvis_2012_L0TIS_narrow.cd(5)
	frame_m2_MC_2012_L0TIS_narrow.Draw()
	cvis_2012_L0TIS_narrow.cd(6)
	frame_t_MC_2012_L0TIS_narrow.Draw()
	cvis_2011_L0noTIS_wide = TCanvas("cvis_2011_L0noTIS_wide","cvis_2011_L0noTIS_wide",1200,600)
	cvis_2011_L0noTIS_wide.Divide(3,2)
	cvis_2011_L0noTIS_wide.cd(1)
	frame_cos1_MC_2011_L0noTIS_wide.Draw()
	cvis_2011_L0noTIS_wide.cd(2)
	frame_cos2_MC_2011_L0noTIS_wide.Draw()
	cvis_2011_L0noTIS_wide.cd(3)
	frame_phi_MC_2011_L0noTIS_wide.Draw()
	cvis_2011_L0noTIS_wide.cd(4)
	frame_m1_MC_2011_L0noTIS_wide.Draw()
	cvis_2011_L0noTIS_wide.cd(5)
	frame_m2_MC_2011_L0noTIS_wide.Draw()
	cvis_2011_L0noTIS_wide.cd(6)
	frame_t_MC_2011_L0noTIS_wide.Draw()
	cvis_2012_L0noTIS_wide = TCanvas("cvis_2012_L0noTIS_wide","cvis_2012_L0noTIS_wide",1200,600)
	cvis_2012_L0noTIS_wide.Divide(3,2)
	cvis_2012_L0noTIS_wide.cd(1)
	frame_cos1_MC_2012_L0noTIS_wide.Draw()
	cvis_2012_L0noTIS_wide.cd(2)
	frame_cos2_MC_2012_L0noTIS_wide.Draw()
	cvis_2012_L0noTIS_wide.cd(3)
	frame_phi_MC_2012_L0noTIS_wide.Draw()
	cvis_2012_L0noTIS_wide.cd(4)
	frame_m1_MC_2012_L0noTIS_wide.Draw()
	cvis_2012_L0noTIS_wide.cd(5)
	frame_m2_MC_2012_L0noTIS_wide.Draw()
	cvis_2012_L0noTIS_wide.cd(6)
	frame_t_MC_2012_L0noTIS_wide.Draw()
	cvis_2011_L0noTIS_narrow = TCanvas("cvis_2011_L0noTIS_narrow","cvis_2011_L0noTIS_narrow",1200,600)
	cvis_2011_L0noTIS_narrow.Divide(3,2)
	cvis_2011_L0noTIS_narrow.cd(1)
	frame_cos1_MC_2011_L0noTIS_narrow.Draw()
	cvis_2011_L0noTIS_narrow.cd(2)
	frame_cos2_MC_2011_L0noTIS_narrow.Draw()
	cvis_2011_L0noTIS_narrow.cd(3)
	frame_phi_MC_2011_L0noTIS_narrow.Draw()
	cvis_2011_L0noTIS_narrow.cd(4)
	frame_m1_MC_2011_L0noTIS_narrow.Draw()
	cvis_2011_L0noTIS_narrow.cd(5)
	frame_m2_MC_2011_L0noTIS_narrow.Draw()
	cvis_2011_L0noTIS_narrow.cd(6)
	frame_t_MC_2011_L0noTIS_narrow.Draw()
	cvis_2012_L0noTIS_narrow = TCanvas("cvis_2012_L0noTIS_narrow","cvis_2012_L0noTIS_narrow",1200,600)
	cvis_2012_L0noTIS_narrow.Divide(3,2)
	cvis_2012_L0noTIS_narrow.cd(1)
	frame_cos1_MC_2012_L0noTIS_narrow.Draw()
	cvis_2012_L0noTIS_narrow.cd(2)
	frame_cos2_MC_2012_L0noTIS_narrow.Draw()
	cvis_2012_L0noTIS_narrow.cd(3)
	frame_phi_MC_2012_L0noTIS_narrow.Draw()
	cvis_2012_L0noTIS_narrow.cd(4)
	frame_m1_MC_2012_L0noTIS_narrow.Draw()
	cvis_2012_L0noTIS_narrow.cd(5)
	frame_m2_MC_2012_L0noTIS_narrow.Draw()
	cvis_2012_L0noTIS_narrow.cd(6)
	frame_t_MC_2012_L0noTIS_narrow.Draw()

	frame_m1_MC_2011_wide = mKp1_MC.frame(RooFit.Title("m1_2011_wide"))
	frame_m2_MC_2011_wide = mKp2_MC.frame(RooFit.Title("m2_2011_wide"))
	frame_cos1_MC_2011_wide = cos1_MC.frame(RooFit.Title("cos1_2011_wide"))
	frame_cos2_MC_2011_wide = cos2_MC.frame(RooFit.Title("cos2_2011_wide"))
	frame_phi_MC_2011_wide = phi_MC.frame(RooFit.Title("phi_2011_wide"))
	frame_t_MC_2011_wide = t_MC.frame(RooFit.Title("t_2011_wide"))
	frame_m1_MC_2012_wide = mKp1_MC.frame(RooFit.Title("m1_2012_wide"))
	frame_m2_MC_2012_wide = mKp2_MC.frame(RooFit.Title("m2_2012_wide"))
	frame_cos1_MC_2012_wide = cos1_MC.frame(RooFit.Title("cos1_2012_wide"))
	frame_cos2_MC_2012_wide = cos2_MC.frame(RooFit.Title("cos2_2012_wide"))
	frame_phi_MC_2012_wide = phi_MC.frame(RooFit.Title("phi_2012_wide"))
	frame_t_MC_2012_wide = t_MC.frame(RooFit.Title("t_2012_wide"))

	data1_kpi1_2011_L0TIS_wide.plotOn(frame_m1_MC_2011_wide,RooFit.Binning(20),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data1_kpi2_2011_L0TIS_wide.plotOn(frame_m2_MC_2011_wide,RooFit.Binning(20),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data2_kpi1_2011_L0TIS_wide.plotOn(frame_cos1_MC_2011_wide,RooFit.Binning(20),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data2_kpi2_2011_L0TIS_wide.plotOn(frame_cos2_MC_2011_wide,RooFit.Binning(20),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data3_2011_L0TIS_wide.plotOn(frame_phi_MC_2011_wide,RooFit.Binning(20),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data4_2011_L0TIS_wide.plotOn(frame_t_MC_2011_wide,RooFit.Binning(20),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data1_kpi1_2012_L0TIS_wide.plotOn(frame_m1_MC_2012_wide,RooFit.Binning(20),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data1_kpi2_2012_L0TIS_wide.plotOn(frame_m2_MC_2012_wide,RooFit.Binning(20),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data2_kpi1_2012_L0TIS_wide.plotOn(frame_cos1_MC_2012_wide,RooFit.Binning(20),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data2_kpi2_2012_L0TIS_wide.plotOn(frame_cos2_MC_2012_wide,RooFit.Binning(20),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data3_2012_L0TIS_wide.plotOn(frame_phi_MC_2012_wide,RooFit.Binning(20),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data4_2012_L0TIS_wide.plotOn(frame_t_MC_2012_wide,RooFit.Binning(20),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	opt_acc.setVal(1)
	model_acc_kpi1_2011_L0TIS_wide.plotOn(frame_m1_MC_2011_wide,RooFit.Name("L0TIS_instance"),RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2011_L0TIS_wide.plotOn(frame_m2_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2012_L0TIS_wide.plotOn(frame_m1_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2012_L0TIS_wide.plotOn(frame_m2_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(2)
	model_acc_kpi1_2011_L0TIS_wide.plotOn(frame_cos1_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2011_L0TIS_wide.plotOn(frame_cos2_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2012_L0TIS_wide.plotOn(frame_cos1_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2012_L0TIS_wide.plotOn(frame_cos2_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(3)
	model_acc_2011_L0TIS_wide.plotOn(frame_phi_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_L0TIS_wide.plotOn(frame_phi_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(4)
	model_acc_2011_L0TIS_wide.plotOn(frame_t_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_L0TIS_wide.plotOn(frame_t_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))

	data1_kpi1_2011_L0noTIS_wide.plotOn(frame_m1_MC_2011_wide,RooFit.Binning(20),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data1_kpi2_2011_L0noTIS_wide.plotOn(frame_m2_MC_2011_wide,RooFit.Binning(20),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data2_kpi1_2011_L0noTIS_wide.plotOn(frame_cos1_MC_2011_wide,RooFit.Binning(20),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data2_kpi2_2011_L0noTIS_wide.plotOn(frame_cos2_MC_2011_wide,RooFit.Binning(20),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data3_2011_L0noTIS_wide.plotOn(frame_phi_MC_2011_wide,RooFit.Binning(20),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data4_2011_L0noTIS_wide.plotOn(frame_t_MC_2011_wide,RooFit.Binning(20),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data1_kpi1_2012_L0noTIS_wide.plotOn(frame_m1_MC_2012_wide,RooFit.Binning(20),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data1_kpi2_2012_L0noTIS_wide.plotOn(frame_m2_MC_2012_wide,RooFit.Binning(20),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data2_kpi1_2012_L0noTIS_wide.plotOn(frame_cos1_MC_2012_wide,RooFit.Binning(20),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data2_kpi2_2012_L0noTIS_wide.plotOn(frame_cos2_MC_2012_wide,RooFit.Binning(20),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data3_2012_L0noTIS_wide.plotOn(frame_phi_MC_2012_wide,RooFit.Binning(20),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data4_2012_L0noTIS_wide.plotOn(frame_t_MC_2012_wide,RooFit.Binning(20),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	opt_acc.setVal(1)
	model_acc_kpi1_2011_L0noTIS_wide.plotOn(frame_m1_MC_2011_wide,RooFit.Name("L0noTIS_instance"),RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_kpi2_2011_L0noTIS_wide.plotOn(frame_m2_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_kpi1_2012_L0noTIS_wide.plotOn(frame_m1_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_kpi2_2012_L0noTIS_wide.plotOn(frame_m2_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	opt_acc.setVal(2)
	model_acc_kpi1_2011_L0noTIS_wide.plotOn(frame_cos1_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_kpi2_2011_L0noTIS_wide.plotOn(frame_cos2_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_kpi1_2012_L0noTIS_wide.plotOn(frame_cos1_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_kpi2_2012_L0noTIS_wide.plotOn(frame_cos2_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	opt_acc.setVal(3)
	model_acc_2011_L0noTIS_wide.plotOn(frame_phi_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_2012_L0noTIS_wide.plotOn(frame_phi_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	opt_acc.setVal(4)
	model_acc_2011_L0noTIS_wide.plotOn(frame_t_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_2012_L0noTIS_wide.plotOn(frame_t_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kRed))

	frame_m1_MC_2011_narrow = mKp1_narrow_MC.frame(RooFit.Title("m1_2011_narrow"))
	frame_m2_MC_2011_narrow = mKp2_narrow_MC.frame(RooFit.Title("m2_2011_narrow"))
	frame_cos1_MC_2011_narrow = cos1_MC.frame(RooFit.Title("cos1_2011_narrow"))
	frame_cos2_MC_2011_narrow = cos2_MC.frame(RooFit.Title("cos2_2011_narrow"))
	frame_phi_MC_2011_narrow = phi_MC.frame(RooFit.Title("phi_2011_narrow"))
	frame_t_MC_2011_narrow = t_MC.frame(RooFit.Title("t_2011_narrow"))
	frame_m1_MC_2012_narrow = mKp1_narrow_MC.frame(RooFit.Title("m1_2012_narrow"))
	frame_m2_MC_2012_narrow = mKp2_narrow_MC.frame(RooFit.Title("m2_2012_narrow"))
	frame_cos1_MC_2012_narrow = cos1_MC.frame(RooFit.Title("cos1_2012_narrow"))
	frame_cos2_MC_2012_narrow = cos2_MC.frame(RooFit.Title("cos2_2012_narrow"))
	frame_phi_MC_2012_narrow = phi_MC.frame(RooFit.Title("phi_2012_narrow"))
	frame_t_MC_2012_narrow = t_MC.frame(RooFit.Title("t_2012_narrow"))

	data1_kpi1_2011_L0TIS_narrow.plotOn(frame_m1_MC_2011_narrow,RooFit.Binning(12),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data1_kpi2_2011_L0TIS_narrow.plotOn(frame_m2_MC_2011_narrow,RooFit.Binning(12),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data2_kpi1_2011_L0TIS_narrow.plotOn(frame_cos1_MC_2011_narrow,RooFit.Binning(12),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data2_kpi2_2011_L0TIS_narrow.plotOn(frame_cos2_MC_2011_narrow,RooFit.Binning(12),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data3_2011_L0TIS_narrow.plotOn(frame_phi_MC_2011_narrow,RooFit.Binning(12),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data4_2011_L0TIS_narrow.plotOn(frame_t_MC_2011_narrow,RooFit.Binning(12),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data1_kpi1_2012_L0TIS_narrow.plotOn(frame_m1_MC_2012_narrow,RooFit.Binning(12),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data1_kpi2_2012_L0TIS_narrow.plotOn(frame_m2_MC_2012_narrow,RooFit.Binning(12),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data2_kpi1_2012_L0TIS_narrow.plotOn(frame_cos1_MC_2012_narrow,RooFit.Binning(12),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data2_kpi2_2012_L0TIS_narrow.plotOn(frame_cos2_MC_2012_narrow,RooFit.Binning(12),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data3_2012_L0TIS_narrow.plotOn(frame_phi_MC_2012_narrow,RooFit.Binning(12),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	data4_2012_L0TIS_narrow.plotOn(frame_t_MC_2012_narrow,RooFit.Binning(12),RooFit.MarkerColor(kBlue),RooFit.LineColor(kBlue))
	opt_acc.setVal(1)
	model_acc_kpi1_2011_L0TIS_narrow.plotOn(frame_m1_MC_2011_narrow,RooFit.Name("L0TIS_instance"),RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2011_L0TIS_narrow.plotOn(frame_m2_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2012_L0TIS_narrow.plotOn(frame_m1_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2012_L0TIS_narrow.plotOn(frame_m2_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(2)
	model_acc_kpi1_2011_L0TIS_narrow.plotOn(frame_cos1_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2011_L0TIS_narrow.plotOn(frame_cos2_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_2012_L0TIS_narrow.plotOn(frame_cos1_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_2012_L0TIS_narrow.plotOn(frame_cos2_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(3)
	model_acc_2011_L0TIS_narrow.plotOn(frame_phi_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_L0TIS_narrow.plotOn(frame_phi_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(4)
	model_acc_2011_L0TIS_narrow.plotOn(frame_t_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_L0TIS_narrow.plotOn(frame_t_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))

	data1_kpi1_2011_L0noTIS_narrow.plotOn(frame_m1_MC_2011_narrow,RooFit.Binning(12),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data1_kpi2_2011_L0noTIS_narrow.plotOn(frame_m2_MC_2011_narrow,RooFit.Binning(12),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data2_kpi1_2011_L0noTIS_narrow.plotOn(frame_cos1_MC_2011_narrow,RooFit.Binning(12),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data2_kpi2_2011_L0noTIS_narrow.plotOn(frame_cos2_MC_2011_narrow,RooFit.Binning(12),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data3_2011_L0noTIS_narrow.plotOn(frame_phi_MC_2011_narrow,RooFit.Binning(12),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data4_2011_L0noTIS_narrow.plotOn(frame_t_MC_2011_narrow,RooFit.Binning(12),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data1_kpi1_2012_L0noTIS_narrow.plotOn(frame_m1_MC_2012_narrow,RooFit.Binning(12),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data1_kpi2_2012_L0noTIS_narrow.plotOn(frame_m2_MC_2012_narrow,RooFit.Binning(12),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data2_kpi1_2012_L0noTIS_narrow.plotOn(frame_cos1_MC_2012_narrow,RooFit.Binning(12),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data2_kpi2_2012_L0noTIS_narrow.plotOn(frame_cos2_MC_2012_narrow,RooFit.Binning(12),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data3_2012_L0noTIS_narrow.plotOn(frame_phi_MC_2012_narrow,RooFit.Binning(12),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	data4_2012_L0noTIS_narrow.plotOn(frame_t_MC_2012_narrow,RooFit.Binning(12),RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
	opt_acc.setVal(1)
	model_acc_kpi1_2011_L0noTIS_narrow.plotOn(frame_m1_MC_2011_narrow,RooFit.Name("L0noTIS_instance"),RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_kpi2_2011_L0noTIS_narrow.plotOn(frame_m2_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_kpi1_2012_L0noTIS_narrow.plotOn(frame_m1_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_kpi2_2012_L0noTIS_narrow.plotOn(frame_m2_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	opt_acc.setVal(2)
	model_acc_kpi1_2011_L0noTIS_narrow.plotOn(frame_cos1_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_kpi2_2011_L0noTIS_narrow.plotOn(frame_cos2_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_kpi1_2012_L0noTIS_narrow.plotOn(frame_cos1_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_kpi2_2012_L0noTIS_narrow.plotOn(frame_cos2_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	opt_acc.setVal(3)
	model_acc_2011_L0noTIS_narrow.plotOn(frame_phi_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_2012_L0noTIS_narrow.plotOn(frame_phi_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	opt_acc.setVal(4)
	model_acc_2011_L0noTIS_narrow.plotOn(frame_t_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kRed))
	model_acc_2012_L0noTIS_narrow.plotOn(frame_t_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kRed))

	hL0TIS = TH1F("hL0TIS","",10,0,10)
	hL0noTIS = TH1F("hL0noTIS","",10,0,10)
	hL0TIS.SetLineColor(kBlue)
	hL0TIS.SetMarkerColor(kBlue)
	hL0noTIS.SetLineColor(kRed)
	hL0noTIS.SetMarkerColor(kRed)
	leg = TLegend(0.2,0.2,0.5,0.4)
	leg.SetHeader("L0 Trigger Decision")
	leg.AddEntry("hL0TIS","TIS","elp")
	leg.AddEntry("hL0noTIS","not TIS","elp")

	cvis_2011_wide = TCanvas("cvis_2011_wide","cvis_2011_wide",1200,600)
	cvis_2011_wide.Divide(3,2)
	cvis_2011_wide.cd(1)
	frame_cos1_MC_2011_wide.Draw()
	cvis_2011_wide.cd(2)
	frame_cos2_MC_2011_wide.Draw()
	leg.Draw()
	cvis_2011_wide.cd(3)
	frame_phi_MC_2011_wide.Draw()
	cvis_2011_wide.cd(4)
	frame_m1_MC_2011_wide.Draw()
	cvis_2011_wide.cd(5)
	frame_m2_MC_2011_wide.Draw()
	cvis_2012_wide = TCanvas("cvis_2012_wide","cvis_2012_wide",1200,600)
	cvis_2012_wide.Divide(3,2)
	cvis_2012_wide.cd(1)
	frame_cos1_MC_2012_wide.Draw()
	cvis_2012_wide.cd(2)
	frame_cos2_MC_2012_wide.Draw()
	leg.Draw()		
	cvis_2012_wide.cd(3)
	frame_phi_MC_2012_wide.Draw()
	cvis_2012_wide.cd(4)
	frame_m1_MC_2012_wide.Draw()
	cvis_2012_wide.cd(5)
	frame_m2_MC_2012_wide.Draw()

	cvis_2011_wide.Print('Vis_Acc_2011_wide.pdf')
	cvis_2011_wide.Print('Vis_Acc_2011_wide.root')
	cvis_2012_wide.Print('Vis_Acc_2012_wide.pdf')
	cvis_2012_wide.Print('Vis_Acc_2012_wide.root')

	cvis_2011_narrow = TCanvas("cvis_2011_narrow","cvis_2011_narrow",1200,600)
	cvis_2011_narrow.Divide(3,2)
	cvis_2011_narrow.cd(1)
	frame_cos1_MC_2011_narrow.Draw()
	cvis_2011_narrow.cd(2)
	frame_cos2_MC_2011_narrow.Draw()
	leg.Draw()
	cvis_2011_narrow.cd(3)
	frame_phi_MC_2011_narrow.Draw()
	cvis_2011_narrow.cd(4)
	frame_m1_MC_2011_narrow.Draw()
	cvis_2011_narrow.cd(5)
	frame_m2_MC_2011_narrow.Draw()
	cvis_2012_narrow = TCanvas("cvis_2012_narrow","cvis_2012_narrow",1200,600)
	cvis_2012_narrow.Divide(3,2)
	cvis_2012_narrow.cd(1)
	frame_cos1_MC_2012_narrow.Draw()
	cvis_2012_narrow.cd(2)
	frame_cos2_MC_2012_narrow.Draw()
	leg.Draw()		
	cvis_2012_narrow.cd(3)
	frame_phi_MC_2012_narrow.Draw()
	cvis_2012_narrow.cd(4)
	frame_m1_MC_2012_narrow.Draw()
	cvis_2012_narrow.cd(5)
	frame_m2_MC_2012_narrow.Draw()

	cvis_2011_narrow.Print('Vis_Acc_2011_narrow.pdf')
	cvis_2011_narrow.Print('Vis_Acc_2011_narrow.root')
	cvis_2012_narrow.Print('Vis_Acc_2012_narrow.pdf')
	cvis_2012_narrow.Print('Vis_Acc_2012_narrow.root')

	return cvis_2011_L0TIS_wide, cvis_2012_L0TIS_wide, cvis_2011_L0TIS_narrow, cvis_2012_L0TIS_narrow, cvis_2011_L0noTIS_wide, cvis_2012_L0noTIS_wide, cvis_2011_L0noTIS_narrow, cvis_2012_L0noTIS_narrow


def PrintVisAccPars():

	accpars = 'class accparclass {\n\n  public:\n\n  Double_t k1(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(k1_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(k1_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(k1_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(k1_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(k1_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(k1_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(k1_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(k1_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n  Double_t k2(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(k2_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(k2_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(k2_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(k2_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(k2_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(k2_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(k2_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(k2_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n  Double_t k3(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(k3_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(k3_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(k3_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(k3_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(k3_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(k3_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(k3_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(k3_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n  Double_t k4(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(k4_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(k4_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(k4_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(k4_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(k4_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(k4_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(k4_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(k4_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n  Double_t k5(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(k5_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(k5_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(k5_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(k5_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(k5_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(k5_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(k5_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(k5_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n  Double_t p1(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(p1_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(p1_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(p1_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(p1_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(p1_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(p1_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(p1_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(p1_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n  Double_t a_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(a_acc_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(a_acc_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(a_acc_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(a_acc_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(a_acc_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(a_acc_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(a_acc_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(a_acc_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n  Double_t b_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(b_acc_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(b_acc_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(b_acc_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(b_acc_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(b_acc_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(b_acc_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(b_acc_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(b_acc_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n  Double_t c_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(c_acc_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(c_acc_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(c_acc_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(c_acc_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(c_acc_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(c_acc_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(c_acc_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(c_acc_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n};'

	fpar = open('../../src/TimeDependent/accparclass.h','w')
	fpar.write(accpars)
	fpar.close()


def PrintGenAccPars(model_acc_kpi1_gen_wide,model_acc_kpi1_gen_narrow,model_acc_kpi2_gen_wide,model_acc_kpi2_gen_narrow,\
model_acc_sim_gen_wide,model_acc_sim_gen_narrow,spl_pdf_gen_wide,spl_pdf_gen_narrow):

	accpars = 'Double_t knots_gen_wide[6] = {'+str(t0_wide.getVal())+','+str(t1_wide.getVal())+','+str(t2_wide.getVal())+','+str(t3_wide.getVal())+','+str(t4_wide.getVal())+','+str(t5_wide.getVal())+'};\nDouble_t knots_gen_narrow[6] = {'+str(t0_narrow.getVal())+','+str(t1_narrow.getVal())+','+str(t2_narrow.getVal())+','+str(t3_narrow.getVal())+','+str(t4_narrow.getVal())+','+str(t5_narrow.getVal())+'};\n\nDouble_t a_gen_wide[5][4] = {{'+str(spl_pdf_gen_wide.a_bin_deg(0,0))+','+str(spl_pdf_gen_wide.a_bin_deg(0,1))+','+str(spl_pdf_gen_wide.a_bin_deg(0,2))+','+str(spl_pdf_gen_wide.a_bin_deg(0,3))+'},\n{'+str(spl_pdf_gen_wide.a_bin_deg(1,0))+','+str(spl_pdf_gen_wide.a_bin_deg(1,1))+','+str(spl_pdf_gen_wide.a_bin_deg(1,2))+','+str(spl_pdf_gen_wide.a_bin_deg(1,3))+'},\n{'+str(spl_pdf_gen_wide.a_bin_deg(2,0))+','+str(spl_pdf_gen_wide.a_bin_deg(2,1))+','+str(spl_pdf_gen_wide.a_bin_deg(2,2))+','+str(spl_pdf_gen_wide.a_bin_deg(2,3))+'},\n{'+str(spl_pdf_gen_wide.a_bin_deg(3,0))+','+str(spl_pdf_gen_wide.a_bin_deg(3,1))+','+str(spl_pdf_gen_wide.a_bin_deg(3,2))+','+str(spl_pdf_gen_wide.a_bin_deg(3,3))+'},\n{'+str(spl_pdf_gen_wide.a_bin_deg(4,0))+','+str(spl_pdf_gen_wide.a_bin_deg(4,1))+','+str(spl_pdf_gen_wide.a_bin_deg(4,2))+','+str(spl_pdf_gen_wide.a_bin_deg(4,3))+'}};\n\nDouble_t a_gen_narrow[5][4] = {{'+str(spl_pdf_gen_narrow.a_bin_deg(0,0))+','+str(spl_pdf_gen_narrow.a_bin_deg(0,1))+','+str(spl_pdf_gen_narrow.a_bin_deg(0,2))+','+str(spl_pdf_gen_narrow.a_bin_deg(0,3))+'},\n{'+str(spl_pdf_gen_narrow.a_bin_deg(1,0))+','+str(spl_pdf_gen_narrow.a_bin_deg(1,1))+','+str(spl_pdf_gen_narrow.a_bin_deg(1,2))+','+str(spl_pdf_gen_narrow.a_bin_deg(1,3))+'},\n{'+str(spl_pdf_gen_narrow.a_bin_deg(2,0))+','+str(spl_pdf_gen_narrow.a_bin_deg(2,1))+','+str(spl_pdf_gen_narrow.a_bin_deg(2,2))+','+str(spl_pdf_gen_narrow.a_bin_deg(2,3))+'},\n{'+str(spl_pdf_gen_narrow.a_bin_deg(3,0))+','+str(spl_pdf_gen_narrow.a_bin_deg(3,1))+','+str(spl_pdf_gen_narrow.a_bin_deg(3,2))+','+str(spl_pdf_gen_narrow.a_bin_deg(3,3))+'},\n{'+str(spl_pdf_gen_narrow.a_bin_deg(4,0))+','+str(spl_pdf_gen_narrow.a_bin_deg(4,1))+','+str(spl_pdf_gen_narrow.a_bin_deg(4,2))+','+str(spl_pdf_gen_narrow.a_bin_deg(4,3))+'}};\n\nclass genaccparclass {\n\n  public:\n\n  Double_t k1_gen(Int_t wide_window) {\n    if (wide_window) {return '+str(k1_gen_wide.getVal())+';}\n    else {return '+str(k1_gen_narrow.getVal())+';}\n    };\n\n  Double_t k2_gen(Int_t wide_window) {\n    if (wide_window) {return '+str(k2_gen_wide.getVal())+';}\n    else {return '+str(k2_gen_narrow.getVal())+';}\n    };\n\n  Double_t k3_gen(Int_t wide_window) {\n    if (wide_window) {return '+str(k3_gen_wide.getVal())+';}\n    else {return '+str(k3_gen_narrow.getVal())+';}\n    };\n\n  Double_t k4_gen(Int_t wide_window) {\n    if (wide_window) {return '+str(k4_gen_wide.getVal())+';}\n    else {return '+str(k4_gen_narrow.getVal())+';}\n    };\n\n  Double_t k5_gen(Int_t wide_window) {\n    if (wide_window) {return '+str(k5_gen_wide.getVal())+';}\n    else {return '+str(k5_gen_narrow.getVal())+';}\n    };\n\n  Double_t p1_gen(Int_t wide_window) {\n    if (wide_window) {return '+str(p1_gen_wide.getVal())+';}\n    else {return '+str(p1_gen_narrow.getVal())+';}\n    };\n\n  Double_t knot_gen(Int_t wide_window,Int_t i) {\n    if (wide_window == 0) {return knots_gen_narrow[i];}\n    else {return knots_gen_wide[i];}\n    }\n\n  Double_t coef_gen(Int_t wide_window,Int_t ibin,Int_t deg) {\n    if (wide_window == 0) {return a_gen_narrow[ibin][deg];}\n    else {return a_gen_wide[ibin][deg];}\n    }\n\n};'

	fpar = open('../../src/TimeDependent/genaccparclass.h','w')
	fpar.write(accpars)
	fpar.close()


def LoadDataNW(data_file, data_tree, datatype, evnum_limit = 0):

	# Information.
	print 'Loading data file ' + data_file + ' ...'
	if datatype == 0: print 'MC sample: PhSp.'
	elif datatype == 1: print 'MC sample: VV.'
	else: print 'MC sample: PhSp + VV.'
	if (evnum_limit == 0): print 'All events selected.'
	else: print 'Maximum of '+str(evnum_limit)+' events selected per data sample.'

	# Input data.
	file_in = TFile(NTUPLE_PATH + data_file)
	tree_full = file_in.Get(data_tree)
	file_out = TFile(NTUPLE_PATH + "trash.root","RECREATE")
	tree_2011_L0TIS_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,0,datatype))
	tree_2012_L0TIS_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,0,datatype))
	tree_2011_L0TIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,0,datatype))
	tree_2012_L0TIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,0,datatype))
	tree_2011_L0noTIS_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,1,datatype))
	tree_2012_L0noTIS_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,1,datatype))
	tree_2011_L0noTIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,1,datatype))
	tree_2012_L0noTIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,1,datatype))

	PDF_gen = CreateGenPDF()

	data0_2011_L0TIS_wide = RooDataSet("data0_2011_L0TIS_wide","data0_2011_L0TIS_wide",RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
	data0_2012_L0TIS_wide = RooDataSet("data0_2012_L0TIS_wide","data0_2012_L0TIS_wide",RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
	data0_2011_L0TIS_narrow = RooDataSet("data0_2011_L0TIS_narrow","data0_2011_L0TIS_narrow",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
	data0_2012_L0TIS_narrow = RooDataSet("data0_2012_L0TIS_narrow","data0_2012_L0TIS_narrow",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
	data0_2011_L0noTIS_wide = RooDataSet("data0_2011_L0noTIS_wide","data0_2011_L0noTIS_wide",RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
	data0_2012_L0noTIS_wide = RooDataSet("data0_2012_L0noTIS_wide","data0_2012_L0noTIS_wide",RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
	data0_2011_L0noTIS_narrow = RooDataSet("data0_2011_L0noTIS_narrow","data0_2011_L0noTIS_narrow",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
	data0_2012_L0noTIS_narrow = RooDataSet("data0_2012_L0noTIS_narrow","data0_2012_L0noTIS_narrow",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))

	def setvarvals(entry):
		mKp1_MC.setVal(eval("entry."+m1_name_MC))
		mKp2_MC.setVal(eval("entry."+m2_name_MC))
		cos1_MC.setVal(eval("entry."+cos1_name_MC))
		cos2_MC.setVal(eval("entry."+cos2_name_MC))
		phi_MC.setVal(eval("entry."+phi_name_MC))

	opt_genmodel.setVal(datatype)

	wide_window_MC.setVal(1)
	year_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_L0TIS_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			setvarvals(i)
			MCweight0.setVal(1./PDF_gen.evaluate())
			data0_2011_L0TIS_wide.add(RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
			ev_counter += 1
	year_MC.setVal(1)
	ev_counter = 0
	for i in tree_2012_L0TIS_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			setvarvals(i)
			MCweight0.setVal(1./PDF_gen.evaluate())
			data0_2012_L0TIS_wide.add(RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
			ev_counter += 1
	wide_window_MC.setVal(0)
	year_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_L0TIS_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
			mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
			setvarvals(i)
			MCweight0.setVal(1./PDF_gen.evaluate())
			data0_2011_L0TIS_narrow.add(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
			ev_counter += 1
	year_MC.setVal(1)
	ev_counter = 0
	for i in tree_2012_L0TIS_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
			mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
			setvarvals(i)
			MCweight0.setVal(1./PDF_gen.evaluate())
			data0_2012_L0TIS_narrow.add(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
			ev_counter += 1
	wide_window_MC.setVal(1)
	year_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_L0noTIS_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			setvarvals(i)
			MCweight0.setVal(1./PDF_gen.evaluate())
			data0_2011_L0noTIS_wide.add(RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
			ev_counter += 1
	year_MC.setVal(1)
	ev_counter = 0
	for i in tree_2012_L0noTIS_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			setvarvals(i)
			MCweight0.setVal(1./PDF_gen.evaluate())
			data0_2012_L0noTIS_wide.add(RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
			ev_counter += 1
	wide_window_MC.setVal(0)
	year_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_L0noTIS_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
			mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
			setvarvals(i)
			MCweight0.setVal(1./PDF_gen.evaluate())
			data0_2011_L0noTIS_narrow.add(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
			ev_counter += 1
	year_MC.setVal(1)
	ev_counter = 0
	for i in tree_2012_L0noTIS_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
			mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
			setvarvals(i)
			MCweight0.setVal(1./PDF_gen.evaluate())
			data0_2012_L0noTIS_narrow.add(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
			ev_counter += 1

	print 'Data loaded.'
	file_in.Close()
	file_out.Close()

	return data0_2011_L0TIS_wide, data0_2012_L0TIS_wide, data0_2011_L0TIS_narrow, data0_2012_L0TIS_narrow, data0_2011_L0noTIS_wide, data0_2012_L0noTIS_wide, data0_2011_L0noTIS_narrow, data0_2012_L0noTIS_narrow


def ComputeNW(comp_cov_matrix,PDF_phys_wide,PDF_phys_narrow,data0_2011_L0TIS_wide,data0_2012_L0TIS_wide,data0_2011_L0TIS_narrow,data0_2012_L0TIS_narrow,data0_2011_L0noTIS_wide,data0_2012_L0noTIS_wide,data0_2011_L0noTIS_narrow,data0_2012_L0noTIS_narrow):

	if comp_cov_matrix: print 'The covariance matrix will be computed.'
	else: print 'The covariance matrix will NOT be computed.'

	# Angular and mass PDF components used to compute the NW.
	def PDF_fi(widewindow_aux,i_aux,m1_aux,m2_aux,cos1_aux,cos2_aux,phi_aux):
		j1_aux,j2_aux,h_aux,j1p_aux,j2p_aux,hp_aux,part_aux = extindex(i_aux)
		if widewindow_aux == 0:
			if part_aux == 0: return PDF_phys_narrow.getReCompVal(m1_aux,m2_aux,cos1_aux,cos2_aux,phi_aux,j1_aux,j2_aux,h_aux,j1p_aux,j2p_aux,hp_aux)
			else: return PDF_phys_narrow.getImCompVal(m1_aux,m2_aux,cos1_aux,cos2_aux,phi_aux,j1_aux,j2_aux,h_aux,j1p_aux,j2p_aux,hp_aux)
		else:
			if part_aux == 0: return PDF_phys_wide.getReCompVal(m1_aux,m2_aux,cos1_aux,cos2_aux,phi_aux,j1_aux,j2_aux,h_aux,j1p_aux,j2p_aux,hp_aux)
			else: return PDF_phys_wide.getImCompVal(m1_aux,m2_aux,cos1_aux,cos2_aux,phi_aux,j1_aux,j2_aux,h_aux,j1p_aux,j2p_aux,hp_aux)

	N_11_L0TIS_wide = data0_2011_L0TIS_wide.numEntries()
	N_12_L0TIS_wide = data0_2012_L0TIS_wide.numEntries()
	N_11_L0TIS_narrow = data0_2011_L0TIS_narrow.numEntries()
	N_12_L0TIS_narrow = data0_2012_L0TIS_narrow.numEntries()
	N_11_L0noTIS_wide = data0_2011_L0noTIS_wide.numEntries()
	N_12_L0noTIS_wide = data0_2012_L0noTIS_wide.numEntries()
	N_11_L0noTIS_narrow = data0_2011_L0noTIS_narrow.numEntries()
	N_12_L0noTIS_narrow = data0_2012_L0noTIS_narrow.numEntries()

	N_total = N_11_L0TIS_wide+N_12_L0TIS_wide+N_11_L0TIS_narrow+N_12_L0TIS_narrow+N_11_L0noTIS_wide+N_12_L0noTIS_wide+N_11_L0noTIS_narrow+N_12_L0noTIS_narrow

	print 'Analizing '+str(N_total)+' events ...'
	start = time.time()
	counter = 0

	# Loop over the events to compute the needed sums.

	for ev in range(N_11_L0TIS_wide):
		m1_var = data0_2011_L0TIS_wide.get(ev).getRealValue(m1_name_MC)
		m2_var =  data0_2011_L0TIS_wide.get(ev).getRealValue(m2_name_MC)
		cos1_var =  data0_2011_L0TIS_wide.get(ev).getRealValue(cos1_name_MC)
		cos2_var =  data0_2011_L0TIS_wide.get(ev).getRealValue(cos2_name_MC)
		phi_var =  data0_2011_L0TIS_wide.get(ev).getRealValue(phi_name_MC)
		norm =  data0_2011_L0TIS_wide.get(ev).getRealValue("MCweight0")
		for i in range(380):
			sumi[0][1][0][i] += norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			sumij[0][1][0][i][i] += norm*norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			if comp_cov_matrix:
				for j in range(380):
					if j<i: sumij[0][1][0][i][j] += norm*norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(1,j,m1_var,m2_var,cos1_var,cos2_var,phi_var)
		counter += 1
		if (counter%100 == 0): print str(counter)+' events analyzed (of '+str(N_total)+').'

	for ev in range(N_12_L0TIS_wide):
		m1_var = data0_2012_L0TIS_wide.get(ev).getRealValue(m1_name_MC)
		m2_var =  data0_2012_L0TIS_wide.get(ev).getRealValue(m2_name_MC)
		cos1_var =  data0_2012_L0TIS_wide.get(ev).getRealValue(cos1_name_MC)
		cos2_var =  data0_2012_L0TIS_wide.get(ev).getRealValue(cos2_name_MC)
		phi_var =  data0_2012_L0TIS_wide.get(ev).getRealValue(phi_name_MC)
		norm =  data0_2012_L0TIS_wide.get(ev).getRealValue("MCweight0")
		for i in range(380):
			sumi[1][1][0][i] += norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			sumij[1][1][0][i][i] += norm*norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			if comp_cov_matrix:
				for j in range(380):
					if j<i: sumij[1][1][0][i][j] += norm*norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(1,j,m1_var,m2_var,cos1_var,cos2_var,phi_var)
		counter += 1
		if (counter%100 == 0): print str(counter)+' events analyzed (of '+str(N_total)+').'

	for ev in range(N_11_L0TIS_narrow):
		m1_var = data0_2011_L0TIS_narrow.get(ev).getRealValue(m1_name_MC)
		m2_var =  data0_2011_L0TIS_narrow.get(ev).getRealValue(m2_name_MC)
		cos1_var =  data0_2011_L0TIS_narrow.get(ev).getRealValue(cos1_name_MC)
		cos2_var =  data0_2011_L0TIS_narrow.get(ev).getRealValue(cos2_name_MC)
		phi_var =  data0_2011_L0TIS_narrow.get(ev).getRealValue(phi_name_MC)
		norm =  data0_2011_L0TIS_narrow.get(ev).getRealValue("MCweight0")
		for i in range(380):
			sumi[0][0][0][i] += norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			sumij[0][0][0][i][i] += norm*norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			if comp_cov_matrix:
				for j in range(380):
					if j<i: sumij[0][0][0][i][j] += norm*norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(0,j,m1_var,m2_var,cos1_var,cos2_var,phi_var)
		counter += 1
		if (counter%100 == 0): print str(counter)+' events analyzed (of '+str(N_total)+').'

	for ev in range(N_12_L0TIS_narrow):
		m1_var = data0_2012_L0TIS_narrow.get(ev).getRealValue(m1_name_MC)
		m2_var =  data0_2012_L0TIS_narrow.get(ev).getRealValue(m2_name_MC)
		cos1_var =  data0_2012_L0TIS_narrow.get(ev).getRealValue(cos1_name_MC)
		cos2_var =  data0_2012_L0TIS_narrow.get(ev).getRealValue(cos2_name_MC)
		phi_var =  data0_2012_L0TIS_narrow.get(ev).getRealValue(phi_name_MC)
		norm =  data0_2012_L0TIS_narrow.get(ev).getRealValue("MCweight0")
		for i in range(380):
			sumi[1][0][0][i] += norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			sumij[1][0][0][i][i] += norm*norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			if comp_cov_matrix:
				for j in range(380):
					if j<i: sumij[1][0][0][i][j] += norm*norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(0,j,m1_var,m2_var,cos1_var,cos2_var,phi_var)
		counter += 1
		if (counter%100 == 0): print str(counter)+' events analyzed (of '+str(N_total)+').'

	for ev in range(N_11_L0noTIS_wide):
		m1_var = data0_2011_L0noTIS_wide.get(ev).getRealValue(m1_name_MC)
		m2_var =  data0_2011_L0noTIS_wide.get(ev).getRealValue(m2_name_MC)
		cos1_var =  data0_2011_L0noTIS_wide.get(ev).getRealValue(cos1_name_MC)
		cos2_var =  data0_2011_L0noTIS_wide.get(ev).getRealValue(cos2_name_MC)
		phi_var =  data0_2011_L0noTIS_wide.get(ev).getRealValue(phi_name_MC)
		norm =  data0_2011_L0noTIS_wide.get(ev).getRealValue("MCweight0")
		for i in range(380):
			sumi[0][1][1][i] += norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			sumij[0][1][1][i][i] += norm*norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			if comp_cov_matrix:
				for j in range(380):
					if j<i: sumij[0][1][1][i][j] += norm*norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(1,j,m1_var,m2_var,cos1_var,cos2_var,phi_var)
		counter += 1
		if (counter%100 == 0): print str(counter)+' events analyzed (of '+str(N_total)+').'

	for ev in range(N_12_L0noTIS_wide):
		m1_var = data0_2012_L0noTIS_wide.get(ev).getRealValue(m1_name_MC)
		m2_var =  data0_2012_L0noTIS_wide.get(ev).getRealValue(m2_name_MC)
		cos1_var =  data0_2012_L0noTIS_wide.get(ev).getRealValue(cos1_name_MC)
		cos2_var =  data0_2012_L0noTIS_wide.get(ev).getRealValue(cos2_name_MC)
		phi_var =  data0_2012_L0noTIS_wide.get(ev).getRealValue(phi_name_MC)
		norm =  data0_2012_L0noTIS_wide.get(ev).getRealValue("MCweight0")
		for i in range(380):
			sumi[1][1][1][i] += norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			sumij[1][1][1][i][i] += norm*norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			if comp_cov_matrix:
				for j in range(380):
					if j<i: sumij[1][1][1][i][j] += norm*norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(1,j,m1_var,m2_var,cos1_var,cos2_var,phi_var)
		counter += 1
		if (counter%100 == 0): print str(counter)+' events analyzed (of '+str(N_total)+').'

	for ev in range(N_11_L0noTIS_narrow):
		m1_var = data0_2011_L0noTIS_narrow.get(ev).getRealValue(m1_name_MC)
		m2_var =  data0_2011_L0noTIS_narrow.get(ev).getRealValue(m2_name_MC)
		cos1_var =  data0_2011_L0noTIS_narrow.get(ev).getRealValue(cos1_name_MC)
		cos2_var =  data0_2011_L0noTIS_narrow.get(ev).getRealValue(cos2_name_MC)
		phi_var =  data0_2011_L0noTIS_narrow.get(ev).getRealValue(phi_name_MC)
		norm =  data0_2011_L0noTIS_narrow.get(ev).getRealValue("MCweight0")
		for i in range(380):
			sumi[0][0][1][i] += norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			sumij[0][0][1][i][i] += norm*norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			if comp_cov_matrix:
				for j in range(380):
					if j<i: sumij[0][0][1][i][j] += norm*norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(0,j,m1_var,m2_var,cos1_var,cos2_var,phi_var)
		counter += 1
		if (counter%100 == 0): print str(counter)+' events analyzed (of '+str(N_total)+').'

	for ev in range(N_12_L0noTIS_narrow):
		m1_var = data0_2012_L0noTIS_narrow.get(ev).getRealValue(m1_name_MC)
		m2_var =  data0_2012_L0noTIS_narrow.get(ev).getRealValue(m2_name_MC)
		cos1_var =  data0_2012_L0noTIS_narrow.get(ev).getRealValue(cos1_name_MC)
		cos2_var =  data0_2012_L0noTIS_narrow.get(ev).getRealValue(cos2_name_MC)
		phi_var =  data0_2012_L0noTIS_narrow.get(ev).getRealValue(phi_name_MC)
		norm =  data0_2012_L0noTIS_narrow.get(ev).getRealValue("MCweight0")
		for i in range(380):
			sumi[1][0][1][i] += norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			sumij[1][0][1][i][i] += norm*norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			if comp_cov_matrix:
				for j in range(380):
					if j<i: sumij[1][0][1][i][j] += norm*norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(0,j,m1_var,m2_var,cos1_var,cos2_var,phi_var)
		counter += 1
		if (counter%100 == 0): print str(counter)+' events analyzed (of '+str(N_total)+').'

	# Determination of the NW, their covariance matrix and their uncertainties from the sums above.

	for i in range(380):
		NWi[0][0][0][i] = sumi[0][0][0][i]/sumi[0][0][0][0]
		NWi[0][1][0][i] = sumi[0][1][0][i]/sumi[0][1][0][0]
		NWi[1][0][0][i] = sumi[1][0][0][i]/sumi[1][0][0][0]
		NWi[1][1][0][i] = sumi[1][1][0][i]/sumi[1][1][0][0]
		NWi[0][0][1][i] = sumi[0][0][1][i]/sumi[0][0][1][0]
		NWi[0][1][1][i] = sumi[0][1][1][i]/sumi[0][1][1][0]
		NWi[1][0][1][i] = sumi[1][0][1][i]/sumi[1][0][1][0]
		NWi[1][1][1][i] = sumi[1][1][1][i]/sumi[1][1][1][0]
		eNWi[0][0][0][i] = sqrt(sumij[0][0][0][i][i]-sumi[0][0][0][i]*sumi[0][0][0][i]/N_11_L0TIS_narrow)/sumi[0][0][0][0]
		eNWi[0][1][0][i] = sqrt(sumij[0][1][0][i][i]-sumi[0][1][0][i]*sumi[0][1][0][i]/N_11_L0TIS_wide)/sumi[0][1][0][0]
		eNWi[1][0][0][i] = sqrt(sumij[1][0][0][i][i]-sumi[1][0][0][i]*sumi[1][0][0][i]/N_12_L0TIS_narrow)/sumi[1][0][0][0]
		eNWi[1][1][0][i] = sqrt(sumij[1][1][0][i][i]-sumi[1][1][0][i]*sumi[1][1][0][i]/N_12_L0TIS_wide)/sumi[1][1][0][0]
		eNWi[0][0][1][i] = sqrt(sumij[0][0][1][i][i]-sumi[0][0][1][i]*sumi[0][0][1][i]/N_11_L0noTIS_narrow)/sumi[0][0][1][0]
		eNWi[0][1][1][i] = sqrt(sumij[0][1][1][i][i]-sumi[0][1][1][i]*sumi[0][1][1][i]/N_11_L0noTIS_wide)/sumi[0][1][1][0]
		eNWi[1][0][1][i] = sqrt(sumij[1][0][1][i][i]-sumi[1][0][1][i]*sumi[1][0][1][i]/N_12_L0noTIS_narrow)/sumi[1][0][1][0]
		eNWi[1][1][1][i] = sqrt(sumij[1][1][1][i][i]-sumi[1][1][1][i]*sumi[1][1][1][i]/N_12_L0noTIS_wide)/sumi[1][1][1][0]
		if comp_cov_matrix:
			for j in range(380):
				if j<=i:
					covij[0][0][0][i][j] = (sumij[0][0][0][i][j]-sumi[0][0][0][i]*sumi[0][0][0][j]/N_11_L0TIS_narrow)/sumi[0][0][0][0]/sumi[0][0][0][0]
					covij[0][1][0][i][j] = (sumij[0][1][0][i][j]-sumi[0][1][0][i]*sumi[0][1][0][j]/N_11_L0TIS_wide)/sumi[0][1][0][0]/sumi[0][1][0][0]
					covij[1][0][0][i][j] = (sumij[1][0][0][i][j]-sumi[1][0][0][i]*sumi[1][0][0][j]/N_12_L0TIS_narrow)/sumi[1][0][0][0]/sumi[1][0][0][0]
					covij[1][1][0][i][j] = (sumij[1][1][0][i][j]-sumi[1][1][0][i]*sumi[1][1][0][j]/N_12_L0TIS_wide)/sumi[1][1][0][0]/sumi[1][1][0][0]
					covij[0][0][1][i][j] = (sumij[0][0][1][i][j]-sumi[0][0][1][i]*sumi[0][0][1][j]/N_11_L0noTIS_narrow)/sumi[0][0][1][0]/sumi[0][0][1][0]
					covij[0][1][1][i][j] = (sumij[0][1][1][i][j]-sumi[0][1][1][i]*sumi[0][1][1][j]/N_11_L0noTIS_wide)/sumi[0][1][1][0]/sumi[0][1][1][0]
					covij[1][0][1][i][j] = (sumij[1][0][1][i][j]-sumi[1][0][1][i]*sumi[1][0][1][j]/N_12_L0noTIS_narrow)/sumi[1][0][1][0]/sumi[1][0][1][0]
					covij[1][1][1][i][j] = (sumij[1][1][1][i][j]-sumi[1][1][1][i]*sumi[1][1][1][j]/N_12_L0noTIS_wide)/sumi[1][1][1][0]/sumi[1][1][1][0]
				else:
					covij[0][0][0][i][j] = (sumij[0][0][0][j][i]-sumi[0][0][0][j]*sumi[0][0][0][i]/N_11_L0TIS_narrow)/sumi[0][0][0][0]/sumi[0][0][0][0]
					covij[0][1][0][i][j] = (sumij[0][1][0][j][i]-sumi[0][1][0][j]*sumi[0][1][0][i]/N_11_L0TIS_wide)/sumi[0][1][0][0]/sumi[0][1][0][0]
					covij[1][0][0][i][j] = (sumij[1][0][0][j][i]-sumi[1][0][0][j]*sumi[1][0][0][i]/N_12_L0TIS_narrow)/sumi[1][0][0][0]/sumi[1][0][0][0]
					covij[1][1][0][i][j] = (sumij[1][1][0][j][i]-sumi[1][1][0][j]*sumi[1][1][0][i]/N_12_L0TIS_wide)/sumi[1][1][0][0]/sumi[1][1][0][0]
					covij[0][0][1][i][j] = (sumij[0][0][1][j][i]-sumi[0][0][1][j]*sumi[0][0][1][i]/N_11_L0noTIS_narrow)/sumi[0][0][1][0]/sumi[0][0][1][0]
					covij[0][1][1][i][j] = (sumij[0][1][1][j][i]-sumi[0][1][1][j]*sumi[0][1][1][i]/N_11_L0noTIS_wide)/sumi[0][1][1][0]/sumi[0][1][1][0]
					covij[1][0][1][i][j] = (sumij[1][0][1][j][i]-sumi[1][0][1][j]*sumi[1][0][1][i]/N_12_L0noTIS_narrow)/sumi[1][0][1][0]/sumi[1][0][1][0]
					covij[1][1][1][i][j] = (sumij[1][1][1][j][i]-sumi[1][1][1][j]*sumi[1][1][1][i]/N_12_L0noTIS_wide)/sumi[1][1][1][0]/sumi[1][1][1][0]

	end = time.time()
	print 'Events analized in',(end - start)/60.,'min.'
	print covij


def PrintNW():

	NWclass = 'Int_t indexdictcpp[4050] = {0,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,\n\
3,-1,-1,-1,-1,-1,-1,-1,-1,4,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,6,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,8,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,10,\n\
11,-1,-1,-1,-1,-1,-1,-1,-1,12,13,-1,-1,-1,-1,-1,-1,-1,-1,14,15,-1,-1,-1,-1,-1,-1,-1,-1,16,17,-1,-1,-1,-1,-1,-1,-1,-1,18,19,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,20,21,-1,-1,-1,-1,-1,-1,-1,-1,22,23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,24,\n\
25,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,26,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,\n\
29,-1,-1,-1,-1,-1,-1,-1,-1,30,31,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,32,33,-1,-1,-1,-1,-1,-1,-1,-1,34,35,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,36,37,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,38,39,-1,-1,-1,-1,-1,-1,-1,-1,40,\n\
41,-1,-1,-1,-1,-1,-1,-1,-1,42,43,-1,-1,-1,-1,-1,-1,-1,-1,44,45,-1,-1,-1,-1,-1,-1,-1,-1,46,47,48,49,-1,-1,-1,-1,-1,-1,50,51,-1,-1,-1,-1,-1,-1,-1,-1,52,\n\
53,-1,-1,-1,-1,-1,-1,-1,-1,54,55,-1,-1,-1,-1,-1,-1,-1,-1,56,57,-1,-1,-1,-1,-1,-1,-1,-1,58,59,-1,-1,-1,-1,-1,-1,-1,-1,60,61,-1,-1,-1,-1,-1,-1,-1,-1,62,\n\
63,-1,-1,-1,-1,-1,-1,-1,-1,64,65,-1,-1,-1,-1,-1,-1,-1,-1,66,67,68,69,70,71,-1,-1,-1,-1,72,73,74,75,-1,-1,-1,-1,-1,-1,76,77,-1,-1,-1,-1,-1,-1,-1,-1,78,\n\
79,80,81,-1,-1,-1,-1,-1,-1,82,83,84,85,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,86,\n\
87,-1,-1,-1,-1,-1,-1,-1,-1,88,89,-1,-1,-1,-1,-1,-1,-1,-1,90,91,-1,-1,-1,-1,-1,-1,-1,-1,92,93,-1,-1,-1,-1,-1,-1,-1,-1,94,95,-1,-1,-1,-1,-1,-1,-1,-1,96,\n\
97,-1,-1,-1,-1,-1,-1,-1,-1,98,99,-1,-1,-1,-1,-1,-1,-1,-1,100,101,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,102,103,-1,-1,-1,-1,-1,-1,-1,-1,104,\n\
105,-1,-1,-1,-1,-1,-1,-1,-1,106,107,-1,-1,-1,-1,-1,-1,-1,-1,108,109,-1,-1,-1,-1,-1,-1,-1,-1,110,111,112,113,-1,-1,-1,-1,-1,-1,114,115,116,117,-1,-1,-1,-1,-1,-1,118,\n\
119,-1,-1,-1,-1,-1,-1,-1,-1,120,121,122,123,-1,-1,-1,-1,-1,-1,124,125,-1,-1,-1,-1,-1,-1,-1,-1,126,127,-1,-1,-1,-1,-1,-1,-1,-1,128,129,-1,-1,-1,-1,-1,-1,-1,-1,130,\n\
131,-1,-1,-1,-1,-1,-1,-1,-1,132,133,-1,-1,-1,-1,-1,-1,-1,-1,134,135,136,137,138,139,-1,-1,-1,-1,140,141,142,143,144,145,-1,-1,-1,-1,146,147,-1,-1,-1,-1,-1,-1,-1,-1,148,\n\
149,150,151,152,153,-1,-1,-1,-1,154,155,156,157,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,158,\n\
159,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,160,161,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,162,163,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,164,\n\
165,-1,-1,-1,-1,-1,-1,-1,-1,166,167,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,168,169,-1,-1,-1,-1,-1,-1,-1,-1,170,171,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,172,173,-1,-1,-1,-1,-1,-1,-1,-1,174,175,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,176,177,-1,-1,-1,-1,-1,-1,-1,-1,178,\n\
179,-1,-1,-1,-1,-1,-1,-1,-1,180,181,-1,-1,-1,-1,-1,-1,-1,-1,182,183,-1,-1,-1,-1,-1,-1,-1,-1,184,185,186,187,-1,-1,-1,-1,-1,-1,188,189,-1,-1,-1,-1,-1,-1,-1,-1,190,\n\
191,-1,-1,-1,-1,-1,-1,-1,-1,192,193,194,195,-1,-1,-1,-1,-1,-1,196,197,-1,-1,-1,-1,-1,-1,-1,-1,198,199,-1,-1,-1,-1,-1,-1,-1,-1,200,201,-1,-1,-1,-1,-1,-1,-1,-1,202,\n\
203,-1,-1,-1,-1,-1,-1,-1,-1,204,205,-1,-1,-1,-1,-1,-1,-1,-1,206,207,208,209,210,211,-1,-1,-1,-1,212,213,214,215,-1,-1,-1,-1,-1,-1,216,217,-1,-1,-1,-1,-1,-1,-1,-1,218,\n\
219,220,221,222,223,-1,-1,-1,-1,224,225,226,227,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,\n\
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,228,\n\
229,-1,-1,-1,-1,-1,-1,-1,-1,230,231,-1,-1,-1,-1,-1,-1,-1,-1,232,233,-1,-1,-1,-1,-1,-1,-1,-1,234,235,-1,-1,-1,-1,-1,-1,-1,-1,236,237,-1,-1,-1,-1,-1,-1,-1,-1,238,\n\
239,-1,-1,-1,-1,-1,-1,-1,-1,240,241,-1,-1,-1,-1,-1,-1,-1,-1,242,243,-1,-1,-1,-1,-1,-1,-1,-1,244,245,-1,-1,-1,-1,-1,-1,-1,-1,246,247,-1,-1,-1,-1,-1,-1,-1,-1,248,\n\
249,-1,-1,-1,-1,-1,-1,-1,-1,250,251,-1,-1,-1,-1,-1,-1,-1,-1,252,253,-1,-1,-1,-1,-1,-1,-1,-1,254,255,256,257,-1,-1,-1,-1,-1,-1,258,259,260,261,-1,-1,-1,-1,-1,-1,262,\n\
263,-1,-1,-1,-1,-1,-1,-1,-1,264,265,266,267,-1,-1,-1,-1,-1,-1,268,269,270,271,-1,-1,-1,-1,-1,-1,272,273,-1,-1,-1,-1,-1,-1,-1,-1,274,275,-1,-1,-1,-1,-1,-1,-1,-1,276,\n\
277,-1,-1,-1,-1,-1,-1,-1,-1,278,279,-1,-1,-1,-1,-1,-1,-1,-1,280,281,282,283,284,285,-1,-1,-1,-1,286,287,288,289,290,291,-1,-1,-1,-1,292,293,-1,-1,-1,-1,-1,-1,-1,-1,294,\n\
295,296,297,298,299,-1,-1,-1,-1,300,301,302,303,304,305,-1,-1,-1,-1,306,307,-1,-1,-1,-1,-1,-1,-1,-1,308,309,-1,-1,-1,-1,-1,-1,-1,-1,310,311,-1,-1,-1,-1,-1,-1,-1,-1,312,\n\
313,-1,-1,-1,-1,-1,-1,-1,-1,314,315,316,317,318,319,-1,-1,-1,-1,320,321,322,323,324,325,-1,-1,-1,-1,326,327,-1,-1,-1,-1,-1,-1,-1,-1,328,329,330,331,332,333,-1,-1,-1,-1,334,\n\
335,336,337,338,339,340,341,-1,-1,342,343,-1,-1,-1,-1,-1,-1,-1,-1,344,345,-1,-1,-1,-1,-1,-1,-1,-1,346,347,-1,-1,-1,-1,-1,-1,-1,-1,348,349,-1,-1,-1,-1,-1,-1,-1,-1,350,\n\
351,352,353,354,355,-1,-1,-1,-1,356,357,358,359,360,361,-1,-1,-1,-1,362,363,-1,-1,-1,-1,-1,-1,-1,-1,364,365,366,367,368,369,-1,-1,-1,-1,370,371,372,373,374,375,376,377,378,379};\n\nInt_t redindexcpp(Int_t j1, Int_t j2, Int_t h, Int_t j1p, Int_t j2p, Int_t hp, Int_t part) {\n  return indexdictcpp[part+2*hp+10*j2p+30*j1p+90*h+450*j2+1350*j1];\n}\n\nDouble_t comp_matrix[][2][2][380] = {{{{'
	NWclass += str(NWi[0][0][0][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(NWi[0][0][0][i])
	NWclass += '},\n{'
	NWclass += str(NWi[0][0][1][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(NWi[0][0][1][i])
	NWclass += '}},\n{{'
	NWclass += str(NWi[0][1][0][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(NWi[0][1][0][i])
	NWclass += '},\n{'
	NWclass += str(NWi[0][1][1][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(NWi[0][1][1][i])
	NWclass += '}}},\n{{{'
	NWclass += str(NWi[1][0][0][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(NWi[1][0][0][i])
	NWclass += '},\n{'
	NWclass += str(NWi[1][0][1][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(NWi[1][0][1][i])
	NWclass += '}},\n{{'
	NWclass += str(NWi[1][1][0][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(NWi[1][1][0][i])
	NWclass += '},\n{'
	NWclass += str(NWi[1][1][1][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(NWi[1][1][1][i])
	NWclass += '}}}};\n\nDouble_t comp_err_matrix[][2][2][380] = {{{{'
	NWclass += str(eNWi[0][0][0][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(eNWi[0][0][0][i])
	NWclass += '},\n{'
	NWclass += str(eNWi[0][0][1][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(eNWi[0][0][1][i])
	NWclass += '}},\n{{'
	NWclass += str(eNWi[0][1][0][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(eNWi[0][1][0][i])
	NWclass += '},\n{'
	NWclass += str(eNWi[0][1][1][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(eNWi[0][1][1][i])
	NWclass += '}}},\n{{{'
	NWclass += str(eNWi[1][0][0][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(eNWi[1][0][0][i])
	NWclass += '},\n{'
	NWclass += str(eNWi[1][0][1][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(eNWi[1][0][1][i])
	NWclass += '}},\n{{'
	NWclass += str(eNWi[1][1][0][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(eNWi[1][1][0][i])
	NWclass += '},\n{'
	NWclass += str(eNWi[1][1][1][0])
	for i in range(1,380):
		NWclass += ','
		if i%20==0: NWclass += '\n'
		NWclass += str(eNWi[1][1][1][i])
	NWclass += '}}}};\n\nclass NWclass {\n\n  public:\n\n  Double_t comp(Int_t year_opt,Int_t trig_opt,Int_t wide_window,Int_t j1,Int_t j2,Int_t h,Int_t j1p,Int_t j2p,Int_t hp,Int_t part) {\n    return comp_matrix[year_opt][trig_opt][wide_window][redindexcpp(j1,j2,h,j1p,j2p,hp,part)];\n    };\n\n  Double_t comp_err(Int_t year_opt,Int_t trig_opt,Int_t wide_window,Int_t j1,Int_t j2,Int_t h,Int_t j1p,Int_t j2p,Int_t hp,Int_t part) {\n    return comp_err_matrix[year_opt][trig_opt][wide_window][redindexcpp(j1,j2,h,j1p,j2p,hp,part)];\n    };\n\n};'

	fNWcxx = open('../../src/TimeDependent/NWclass.h','w')
	fNWcxx.write(NWclass)
	fNWcxx.close()


def LoadDataTime(data_file, data_tree, datatype, evnum_limit = 0):

	# Information.
	print 'Loading data file ' + data_file + ' ...'
	if datatype == 0: print 'MC sample: PhSp.'
	elif datatype == 1: print 'MC sample: VV.'
	else: print 'MC sample: PhSp + VV.'
	if (evnum_limit == 0): print 'All events selected.'
	else: print 'Maximum of '+str(evnum_limit)+' events selected per data sample.'

	# Input data.
	file_in = TFile(NTUPLE_PATH + data_file)
	tree_full = file_in.Get(data_tree)
	file_out = TFile(NTUPLE_PATH + "trash.root","RECREATE")
	tree_2011_L0TIS_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,0,datatype))
	tree_2012_L0TIS_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,0,datatype))
	tree_2011_L0TIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,0,datatype))
	tree_2012_L0TIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,0,datatype))
	tree_2011_L0noTIS_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,1,datatype))
	tree_2012_L0noTIS_wide = tree_full.CopyTree(m1_name_MC+"<=1500. && "+m2_name_MC+"<=1500. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,1,datatype))
	tree_2011_L0noTIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,1,datatype))
	tree_2012_L0noTIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,1,datatype))

	PDF_gen = CreateGenPDF()

	opt_genmodel.setVal(datatype)

	wide_window_MC.setVal(1)
	year_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_L0TIS_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight4.setVal(1./PDF_gen.timemodel(eval("i."+t_name_MC)))
			data4_2011_L0TIS_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	year_MC.setVal(1)
	ev_counter = 0
	for i in tree_2012_L0TIS_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight4.setVal(1./PDF_gen.timemodel(eval("i."+t_name_MC)))
			data4_2012_L0TIS_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	wide_window_MC.setVal(0)
	year_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_L0TIS_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight4.setVal(1./PDF_gen.timemodel(eval("i."+t_name_MC)))
			data4_2011_L0TIS_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	year_MC.setVal(1)
	ev_counter = 0
	for i in tree_2012_L0TIS_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight4.setVal(1./PDF_gen.timemodel(eval("i."+t_name_MC)))
			data4_2012_L0TIS_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	wide_window_MC.setVal(1)
	year_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_L0noTIS_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight4.setVal(1./PDF_gen.timemodel(eval("i."+t_name_MC)))
			data4_2011_L0noTIS_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	year_MC.setVal(1)
	ev_counter = 0
	for i in tree_2012_L0noTIS_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight4.setVal(1./PDF_gen.timemodel(eval("i."+t_name_MC)))
			data4_2012_L0noTIS_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	wide_window_MC.setVal(0)
	year_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_L0noTIS_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight4.setVal(1./PDF_gen.timemodel(eval("i."+t_name_MC)))
			data4_2011_L0noTIS_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	year_MC.setVal(1)
	ev_counter = 0
	for i in tree_2012_L0noTIS_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i):
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight4.setVal(1./PDF_gen.timemodel(eval("i."+t_name_MC)))
			data4_2012_L0noTIS_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1

	data4_2011_L0TIS_wide = RooDataSet("data4_2011_L0TIS_wide","data4_2011_L0TIS_wide",data4_2011_L0TIS_wide_,data4_2011_L0TIS_wide_.get())
	data4_2012_L0TIS_wide = RooDataSet("data4_2012_L0TIS_wide","data4_2012_L0TIS_wide",data4_2012_L0TIS_wide_,data4_2012_L0TIS_wide_.get())
	data4_2011_L0TIS_narrow = RooDataSet("data4_2011_L0TIS_narrow","data4_2011_L0TIS_narrow",data4_2011_L0TIS_narrow_,data4_2011_L0TIS_narrow_.get())
	data4_2012_L0TIS_narrow = RooDataSet("data4_2012_L0TIS_narrow","data4_2012_L0TIS_narrow",data4_2012_L0TIS_narrow_,data4_2012_L0TIS_narrow_.get())
	data4_2011_L0noTIS_wide = RooDataSet("data4_2011_L0noTIS_wide","data4_2011_L0noTIS_wide",data4_2011_L0noTIS_wide_,data4_2011_L0noTIS_wide_.get())
	data4_2012_L0noTIS_wide = RooDataSet("data4_2012_L0noTIS_wide","data4_2012_L0noTIS_wide",data4_2012_L0noTIS_wide_,data4_2012_L0noTIS_wide_.get())
	data4_2011_L0noTIS_narrow = RooDataSet("data4_2011_L0noTIS_narrow","data4_2011_L0noTIS_narrow",data4_2011_L0noTIS_narrow_,data4_2011_L0noTIS_narrow_.get())
	data4_2012_L0noTIS_narrow = RooDataSet("data4_2012_L0noTIS_narrow","data4_2012_L0noTIS_narrow",data4_2012_L0noTIS_narrow_,data4_2012_L0noTIS_narrow_.get())

	print 'Data loaded.'
	file_in.Close()
	file_out.Close()

	return data4_2011_L0TIS_wide, data4_2012_L0TIS_wide, data4_2011_L0TIS_narrow, data4_2012_L0TIS_narrow, data4_2011_L0noTIS_wide, data4_2012_L0noTIS_wide, data4_2011_L0noTIS_narrow, data4_2012_L0noTIS_narrow


def adaptiveBinning(var,nbins,applyweights,data):

	histo_aux = TH1F("histo_aux","histo_aux",200,var.getMin(),var.getMax())
	for i in range(data.numEntries()):
		x = data.get(i).getRealValue(var.GetName())
		w = data.weight()
		if applyweights: histo_aux.Fill(x,w)
		else: histo_aux.Fill(x)
	histo_aux.Smooth()
	bincontent = histo_aux.Integral()/float(nbins)
	cumulative = 0
	for i in range(200):
		cumulative += histo_aux.GetBinContent(i+1)
		Ni = cumulative
		while Ni>bincontent: Ni -= bincontent
		histo_aux.SetBinContent(i+1,Ni)
	histo_aux.SetBinContent(200,bincontent)

	binningscheme = [var.getMin()]
	for i in range(199):
		if histo_aux.GetBinContent(i+1)>histo_aux.GetBinContent(i+2): binningscheme.append(histo_aux.GetBinCenter(i+1))
	binningscheme.append(var.getMax())

	return binningscheme


def getRooBinning(var,boundlist):

	binning = RooBinning(var.getMin(),var.getMax())
	for i in range(1,len(boundlist)-1): binning.addBoundary(boundlist[i])
	binning.SetName("adapt_binning")

	return binning


def getKnots(numknots,data_2011_L0TIS_wide,data_2012_L0TIS_wide,data_2011_L0TIS_narrow,data_2012_L0TIS_narrow,data_2011_L0noTIS_wide,data_2012_L0noTIS_wide,data_2011_L0noTIS_narrow,data_2012_L0noTIS_narrow):

	data_aux_wide_ = RooDataSet("data_aux_wide_","data_aux_wide_",data_2011_L0TIS_wide.get())
	data_aux_wide_.append(data_2011_L0TIS_wide)
	data_aux_wide_.append(data_2012_L0TIS_wide)
	data_aux_wide_.append(data_2011_L0noTIS_wide)
	data_aux_wide_.append(data_2012_L0noTIS_wide)

	data_aux_narrow_ = RooDataSet("data_aux_narrow_","data_aux_narrow_",data_2011_L0TIS_narrow.get())
	data_aux_narrow_.append(data_2011_L0TIS_narrow)
	data_aux_narrow_.append(data_2012_L0TIS_narrow)
	data_aux_narrow_.append(data_2011_L0noTIS_narrow)
	data_aux_narrow_.append(data_2012_L0noTIS_narrow)

	data_aux_wide = RooDataSet("data_aux_wide","data_aux_wide",data_aux_wide_,data_aux_wide_.get(),"",MCweight4.GetName())
	data_aux_narrow = RooDataSet("data_aux_narrow","data_aux_narrow",data_aux_narrow_,data_aux_narrow_.get(),"",MCweight4.GetName())

	knots_wide = adaptiveBinning(t_MC,numknots-1,0,data_aux_wide)
	knots_narrow = adaptiveBinning(t_MC,numknots-1,0,data_aux_narrow)
	for i in range(numknots):
		knots_wide[i] = round(knots_wide[i],1)
		knots_narrow[i] = round(knots_narrow[i],1)

	return knots_wide, knots_narrow


def getSplineCoeffs(knots_pair,data_2011_L0TIS_wide,data_2012_L0TIS_wide,data_2011_L0TIS_narrow,data_2012_L0TIS_narrow,data_2011_L0noTIS_wide,data_2012_L0noTIS_wide,data_2011_L0noTIS_narrow,data_2012_L0noTIS_narrow):

	data_2011_L0TIS_wide_weighted = RooDataSet("data_2011_L0TIS_wide_weighted","data_2011_L0TIS_wide_weighted",data_2011_L0TIS_wide,data_2011_L0TIS_wide.get(),"",MCweight4.GetName())
	data_2012_L0TIS_wide_weighted = RooDataSet("data_2012_L0TIS_wide_weighted","data_2012_L0TIS_wide_weighted",data_2012_L0TIS_wide,data_2012_L0TIS_wide.get(),"",MCweight4.GetName())
	data_2011_L0TIS_narrow_weighted = RooDataSet("data_2011_L0TIS_narrow_weighted","data_2011_L0TIS_narrow_weighted",data_2011_L0TIS_narrow,data_2011_L0TIS_narrow.get(),"",MCweight4.GetName())
	data_2012_L0TIS_narrow_weighted = RooDataSet("data_2012_L0TIS_narrow_weighted","data_2012_L0TIS_narrow_weighted",data_2012_L0TIS_narrow,data_2012_L0TIS_narrow.get(),"",MCweight4.GetName())
	data_2011_L0noTIS_wide_weighted = RooDataSet("data_2011_L0noTIS_wide_weighted","data_2011_L0noTIS_wide_weighted",data_2011_L0noTIS_wide,data_2011_L0noTIS_wide.get(),"",MCweight4.GetName())
	data_2012_L0noTIS_wide_weighted = RooDataSet("data_2012_L0noTIS_wide_weighted","data_2012_L0noTIS_wide_weighted",data_2012_L0noTIS_wide,data_2012_L0noTIS_wide.get(),"",MCweight4.GetName())
	data_2011_L0noTIS_narrow_weighted = RooDataSet("data_2011_L0noTIS_narrow_weighted","data_2011_L0noTIS_narrow_weighted",data_2011_L0noTIS_narrow,data_2011_L0noTIS_narrow.get(),"",MCweight4.GetName())
	data_2012_L0noTIS_narrow_weighted = RooDataSet("data_2012_L0noTIS_narrow_weighted","data_2012_L0noTIS_narrow_weighted",data_2012_L0noTIS_narrow,data_2012_L0noTIS_narrow.get(),"",MCweight4.GetName())

	knots_wide = knots_pair[0]
	knots_narrow = knots_pair[1]
	ti_wide = [t0_wide,t1_wide,t2_wide,t3_wide,t4_wide,t5_wide]
	ti_narrow = [t0_narrow,t1_narrow,t2_narrow,t3_narrow,t4_narrow,t5_narrow]
	for i in range(len(ti_wide)):
		ti_wide[i].setVal(knots_wide[i])
		ti_narrow[i].setVal(knots_narrow[i])

	spl_pdf_2011_L0TIS_wide = SplineTAcc("spl_pdf_2011_L0TIS_wide","spl_pdf_2011_L0TIS_wide",t_MC,t0_wide,t1_wide,t2_wide,t3_wide,t4_wide,t5_wide,\
spl_c0_2011_L0TIS_wide,spl_c1_2011_L0TIS_wide,spl_c2_2011_L0TIS_wide,spl_c3_2011_L0TIS_wide,spl_c4_2011_L0TIS_wide,spl_c5_2011_L0TIS_wide,spl_c6_2011_L0TIS_wide,spl_c7_2011_L0TIS_wide)
	spl_pdf_2012_L0TIS_wide = SplineTAcc("spl_pdf_2012_L0TIS_wide","spl_pdf_2012_L0TIS_wide",t_MC,t0_wide,t1_wide,t2_wide,t3_wide,t4_wide,t5_wide,\
spl_c0_2012_L0TIS_wide,spl_c1_2012_L0TIS_wide,spl_c2_2012_L0TIS_wide,spl_c3_2012_L0TIS_wide,spl_c4_2012_L0TIS_wide,spl_c5_2012_L0TIS_wide,spl_c6_2012_L0TIS_wide,spl_c7_2012_L0TIS_wide)
	spl_pdf_2011_L0noTIS_wide = SplineTAcc("spl_pdf_2011_L0noTIS_wide","spl_pdf_2011_L0noTIS_wide",t_MC,t0_wide,t1_wide,t2_wide,t3_wide,t4_wide,t5_wide,\
spl_c0_2011_L0noTIS_wide,spl_c1_2011_L0noTIS_wide,spl_c2_2011_L0noTIS_wide,spl_c3_2011_L0noTIS_wide,spl_c4_2011_L0noTIS_wide,spl_c5_2011_L0noTIS_wide,spl_c6_2011_L0noTIS_wide,spl_c7_2011_L0noTIS_wide)
	spl_pdf_2012_L0noTIS_wide = SplineTAcc("spl_pdf_2012_L0noTIS_wide","spl_pdf_2012_L0noTIS_wide",t_MC,t0_wide,t1_wide,t2_wide,t3_wide,t4_wide,t5_wide,\
spl_c0_2012_L0noTIS_wide,spl_c1_2012_L0noTIS_wide,spl_c2_2012_L0noTIS_wide,spl_c3_2012_L0noTIS_wide,spl_c4_2012_L0noTIS_wide,spl_c5_2012_L0noTIS_wide,spl_c6_2012_L0noTIS_wide,spl_c7_2012_L0noTIS_wide)
	spl_pdf_2011_L0TIS_narrow = SplineTAcc("spl_pdf_2011_L0TIS_narrow","spl_pdf_2011_L0TIS_narrow",t_MC,t0_narrow,t1_narrow,t2_narrow,t3_narrow,t4_narrow,t5_narrow,\
spl_c0_2011_L0TIS_narrow,spl_c1_2011_L0TIS_narrow,spl_c2_2011_L0TIS_narrow,spl_c3_2011_L0TIS_narrow,spl_c4_2011_L0TIS_narrow,spl_c5_2011_L0TIS_narrow,spl_c6_2011_L0TIS_narrow,spl_c7_2011_L0TIS_narrow)
	spl_pdf_2012_L0TIS_narrow = SplineTAcc("spl_pdf_2012_L0TIS_narrow","spl_pdf_2012_L0TIS_narrow",t_MC,t0_narrow,t1_narrow,t2_narrow,t3_narrow,t4_narrow,t5_narrow,\
spl_c0_2012_L0TIS_narrow,spl_c1_2012_L0TIS_narrow,spl_c2_2012_L0TIS_narrow,spl_c3_2012_L0TIS_narrow,spl_c4_2012_L0TIS_narrow,spl_c5_2012_L0TIS_narrow,spl_c6_2012_L0TIS_narrow,spl_c7_2012_L0TIS_narrow)
	spl_pdf_2011_L0noTIS_narrow = SplineTAcc("spl_pdf_2011_L0noTIS_narrow","spl_pdf_2011_L0noTIS_narrow",t_MC,t0_narrow,t1_narrow,t2_narrow,t3_narrow,t4_narrow,t5_narrow,\
spl_c0_2011_L0noTIS_narrow,spl_c1_2011_L0noTIS_narrow,spl_c2_2011_L0noTIS_narrow,spl_c3_2011_L0noTIS_narrow,spl_c4_2011_L0noTIS_narrow,spl_c5_2011_L0noTIS_narrow,spl_c6_2011_L0noTIS_narrow,spl_c7_2011_L0noTIS_narrow)
	spl_pdf_2012_L0noTIS_narrow = SplineTAcc("spl_pdf_2012_L0noTIS_narrow","spl_pdf_2012_L0noTIS_narrow",t_MC,t0_narrow,t1_narrow,t2_narrow,t3_narrow,t4_narrow,t5_narrow,\
spl_c0_2012_L0noTIS_narrow,spl_c1_2012_L0noTIS_narrow,spl_c2_2012_L0noTIS_narrow,spl_c3_2012_L0noTIS_narrow,spl_c4_2012_L0noTIS_narrow,spl_c5_2012_L0noTIS_narrow,spl_c6_2012_L0noTIS_narrow,spl_c7_2012_L0noTIS_narrow)

	spl_pdf_2011_L0TIS_wide.fitTo(data_2011_L0TIS_wide_weighted,RooFit.NumCPU(6),RooFit.Strategy(1),RooFit.Minos(0))
	spl_pdf_2012_L0TIS_wide.fitTo(data_2012_L0TIS_wide_weighted,RooFit.NumCPU(6),RooFit.Strategy(1),RooFit.Minos(0))
	spl_pdf_2011_L0noTIS_wide.fitTo(data_2011_L0noTIS_wide_weighted,RooFit.NumCPU(6),RooFit.Strategy(1),RooFit.Minos(0))
	spl_pdf_2012_L0noTIS_wide.fitTo(data_2012_L0noTIS_wide_weighted,RooFit.NumCPU(6),RooFit.Strategy(1),RooFit.Minos(0))
	spl_pdf_2011_L0TIS_narrow.fitTo(data_2011_L0TIS_narrow_weighted,RooFit.NumCPU(6),RooFit.Strategy(1),RooFit.Minos(0))
	spl_pdf_2012_L0TIS_narrow.fitTo(data_2012_L0TIS_narrow_weighted,RooFit.NumCPU(6),RooFit.Strategy(1),RooFit.Minos(0))
	spl_pdf_2011_L0noTIS_narrow.fitTo(data_2011_L0noTIS_narrow_weighted,RooFit.NumCPU(6),RooFit.Strategy(1),RooFit.Minos(0))
	spl_pdf_2012_L0noTIS_narrow.fitTo(data_2012_L0noTIS_narrow_weighted,RooFit.NumCPU(6),RooFit.Strategy(1),RooFit.Minos(0))

	spl_frame_t_2011_L0TIS_wide = t_MC.frame()
	data_2011_L0TIS_wide_weighted.plotOn(spl_frame_t_2011_L0TIS_wide,RooFit.Binning(30),RooFit.MarkerSize(0.5))
	spl_pdf_2011_L0TIS_wide.plotOn(spl_frame_t_2011_L0TIS_wide,RooFit.LineColor(kRed))
	spl_frame_t_2012_L0TIS_wide = t_MC.frame()
	data_2012_L0TIS_wide_weighted.plotOn(spl_frame_t_2012_L0TIS_wide,RooFit.Binning(30),RooFit.MarkerSize(0.5))
	spl_pdf_2012_L0TIS_wide.plotOn(spl_frame_t_2012_L0TIS_wide,RooFit.LineColor(kRed))
	spl_frame_t_2011_L0noTIS_wide = t_MC.frame()
	data_2011_L0noTIS_wide_weighted.plotOn(spl_frame_t_2011_L0noTIS_wide,RooFit.Binning(30),RooFit.MarkerSize(0.5))
	spl_pdf_2011_L0noTIS_wide.plotOn(spl_frame_t_2011_L0noTIS_wide,RooFit.LineColor(kRed))
	spl_frame_t_2012_L0noTIS_wide = t_MC.frame()
	data_2012_L0noTIS_wide_weighted.plotOn(spl_frame_t_2012_L0noTIS_wide,RooFit.Binning(30),RooFit.MarkerSize(0.5))
	spl_pdf_2012_L0noTIS_wide.plotOn(spl_frame_t_2012_L0noTIS_wide,RooFit.LineColor(kRed))
	spl_frame_t_2011_L0TIS_narrow = t_MC.frame()
	data_2011_L0TIS_narrow_weighted.plotOn(spl_frame_t_2011_L0TIS_narrow,RooFit.Binning(30),RooFit.MarkerSize(0.5))
	spl_pdf_2011_L0TIS_narrow.plotOn(spl_frame_t_2011_L0TIS_narrow,RooFit.LineColor(kRed))
	spl_frame_t_2012_L0TIS_narrow = t_MC.frame()
	data_2012_L0TIS_narrow_weighted.plotOn(spl_frame_t_2012_L0TIS_narrow,RooFit.Binning(30),RooFit.MarkerSize(0.5))
	spl_pdf_2012_L0TIS_narrow.plotOn(spl_frame_t_2012_L0TIS_narrow,RooFit.LineColor(kRed))
	spl_frame_t_2011_L0noTIS_narrow = t_MC.frame()
	data_2011_L0noTIS_narrow_weighted.plotOn(spl_frame_t_2011_L0noTIS_narrow,RooFit.Binning(30),RooFit.MarkerSize(0.5))
	spl_pdf_2011_L0noTIS_narrow.plotOn(spl_frame_t_2011_L0noTIS_narrow,RooFit.LineColor(kRed))
	spl_frame_t_2012_L0noTIS_narrow = t_MC.frame()
	data_2012_L0noTIS_narrow_weighted.plotOn(spl_frame_t_2012_L0noTIS_narrow,RooFit.Binning(30),RooFit.MarkerSize(0.5))
	spl_pdf_2012_L0noTIS_narrow.plotOn(spl_frame_t_2012_L0noTIS_narrow,RooFit.LineColor(kRed))

	label_cat = TText()
	label_cat.SetNDC()
	tl1_wide = 0.14+knots_wide[1]/12.*0.81
	tl2_wide = 0.14+knots_wide[2]/12.*0.81
	tl3_wide = 0.14+knots_wide[3]/12.*0.81
	tl4_wide = 0.14+knots_wide[4]/12.*0.81
	tl1_narrow = 0.14+knots_narrow[1]/12.*0.81
	tl2_narrow = 0.14+knots_narrow[2]/12.*0.81
	tl3_narrow = 0.14+knots_narrow[3]/12.*0.81
	tl4_narrow = 0.14+knots_narrow[4]/12.*0.81
	l1_wide = TLine(tl1_wide,0.16,tl1_wide,0.95)
	l1_wide.SetNDC()
	l1_wide.SetLineStyle(2)
	l2_wide = TLine(tl2_wide,0.16,tl2_wide,0.95)
	l2_wide.SetNDC()
	l2_wide.SetLineStyle(2)
	l3_wide = TLine(tl3_wide,0.16,tl3_wide,0.95)
	l3_wide.SetNDC()
	l3_wide.SetLineStyle(2)
	l4_wide = TLine(tl4_wide,0.16,tl4_wide,0.95)
	l4_wide.SetNDC()
	l4_wide.SetLineStyle(2)
	l1_narrow = TLine(tl1_narrow,0.16,tl1_narrow,0.95)
	l1_narrow.SetNDC()
	l1_narrow.SetLineStyle(2)
	l2_narrow = TLine(tl2_narrow,0.16,tl2_narrow,0.95)
	l2_narrow.SetNDC()
	l2_narrow.SetLineStyle(2)
	l3_narrow = TLine(tl3_narrow,0.16,tl3_narrow,0.95)
	l3_narrow.SetNDC()
	l3_narrow.SetLineStyle(2)
	l4_narrow = TLine(tl4_narrow,0.16,tl4_narrow,0.95)
	l4_narrow.SetNDC()
	l4_narrow.SetLineStyle(2)

	c_spl_wide = TCanvas("c_spl_wide","c_spl_wide")
	c_spl_wide.Divide(2,2)
	c_spl_wide.cd(1)
	spl_frame_t_2011_L0TIS_wide.Draw()
	map(lambda x: x.Draw(),[l1_wide,l2_wide,l3_wide,l4_wide])
	label_cat.DrawText(0.45,0.23,"2011, L0 TIS")
	c_spl_wide.cd(2)
	spl_frame_t_2011_L0noTIS_wide.Draw()
	map(lambda x: x.Draw(),[l1_wide,l2_wide,l3_wide,l4_wide])
	label_cat.DrawText(0.45,0.23,"2011, L0 noTIS")
	c_spl_wide.cd(3)
	spl_frame_t_2012_L0TIS_wide.Draw()
	map(lambda x: x.Draw(),[l1_wide,l2_wide,l3_wide,l4_wide])
	label_cat.DrawText(0.45,0.23,"2012, L0 TIS")
	c_spl_wide.cd(4)
	spl_frame_t_2012_L0noTIS_wide.Draw()
	map(lambda x: x.Draw(),[l1_wide,l2_wide,l3_wide,l4_wide])
	label_cat.DrawText(0.45,0.23,"2012, L0 noTIS")
	c_spl_narrow = TCanvas("c_spl_narrow","c_spl_narrow")
	c_spl_narrow.Divide(2,2)
	c_spl_narrow.cd(1)
	spl_frame_t_2011_L0TIS_narrow.Draw()
	map(lambda x: x.Draw(),[l1_narrow,l2_narrow,l3_narrow,l4_narrow])
	label_cat.DrawText(0.45,0.23,"2011, L0 TIS")
	c_spl_narrow.cd(2)
	spl_frame_t_2011_L0noTIS_narrow.Draw()
	map(lambda x: x.Draw(),[l1_narrow,l2_narrow,l3_narrow,l4_narrow])
	label_cat.DrawText(0.45,0.23,"2011, L0 noTIS")
	c_spl_narrow.cd(3)
	spl_frame_t_2012_L0TIS_narrow.Draw()
	map(lambda x: x.Draw(),[l1_narrow,l2_narrow,l3_narrow,l4_narrow])
	label_cat.DrawText(0.45,0.23,"2012, L0 TIS")
	c_spl_narrow.cd(4)
	spl_frame_t_2012_L0noTIS_narrow.Draw()
	map(lambda x: x.Draw(),[l1_narrow,l2_narrow,l3_narrow,l4_narrow])
	label_cat.DrawText(0.45,0.23,"2012, L0 noTIS")

	c_spl_wide.Print("spline_fit_timeacc_wide.root")
	c_spl_wide.Print("spline_fit_timeacc_wide.pdf")
	c_spl_narrow.Print("spline_fit_timeacc_narrow.root")
	c_spl_narrow.Print("spline_fit_timeacc_narrow.pdf")

	splclasstext = 'Double_t knots_wide[6] = {'+str(t0_wide.getVal())+','+str(t1_wide.getVal())+','+str(t2_wide.getVal())+','+str(t3_wide.getVal())+','+str(t4_wide.getVal())+','+str(t5_wide.getVal())+'};\nDouble_t knots_narrow[6] = {'+str(t0_narrow.getVal())+','+str(t1_narrow.getVal())+','+str(t2_narrow.getVal())+','+str(t3_narrow.getVal())+','+str(t4_narrow.getVal())+','+str(t5_narrow.getVal())+'};\n\n'

	splclasstext += 'Double_t a_2011_L0TIS_wide[5][4] = {{'+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(0,0))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(0,1))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(0,2))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(0,3))+'},\n{'+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(1,0))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(1,1))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(1,2))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(1,3))+'},\n{'+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(2,0))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(2,1))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(2,2))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(2,3))+'},\n{'+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(3,0))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(3,1))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(3,2))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(3,3))+'},\n{'+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(4,0))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(4,1))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(4,2))+','+str(spl_pdf_2011_L0TIS_wide.a_bin_deg(4,3))+'}};\nDouble_t a_2012_L0TIS_wide[5][4] = {{'+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(0,0))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(0,1))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(0,2))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(0,3))+'},\n{'+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(1,0))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(1,1))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(1,2))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(1,3))+'},\n{'+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(2,0))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(2,1))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(2,2))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(2,3))+'},\n{'+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(3,0))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(3,1))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(3,2))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(3,3))+'},\n{'+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(4,0))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(4,1))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(4,2))+','+str(spl_pdf_2012_L0TIS_wide.a_bin_deg(4,3))+'}};\nDouble_t a_2011_L0noTIS_wide[5][4] = {{'+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(0,0))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(0,1))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(0,2))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(0,3))+'},\n{'+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(1,0))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(1,1))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(1,2))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(1,3))+'},\n{'+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(2,0))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(2,1))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(2,2))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(2,3))+'},\n{'+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(3,0))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(3,1))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(3,2))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(3,3))+'},\n{'+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(4,0))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(4,1))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(4,2))+','+str(spl_pdf_2011_L0noTIS_wide.a_bin_deg(4,3))+'}};\nDouble_t a_2012_L0noTIS_wide[5][4] = {{'+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(0,0))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(0,1))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(0,2))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(0,3))+'},\n{'+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(1,0))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(1,1))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(1,2))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(1,3))+'},\n{'+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(2,0))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(2,1))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(2,2))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(2,3))+'},\n{'+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(3,0))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(3,1))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(3,2))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(3,3))+'},\n{'+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(4,0))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(4,1))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(4,2))+','+str(spl_pdf_2012_L0noTIS_wide.a_bin_deg(4,3))+'}};\nDouble_t a_2011_L0TIS_narrow[5][4] = {{'+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(0,0))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(0,1))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(0,2))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(0,3))+'},\n{'+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(1,0))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(1,1))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(1,2))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(1,3))+'},\n{'+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(2,0))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(2,1))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(2,2))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(2,3))+'},\n{'+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(3,0))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(3,1))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(3,2))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(3,3))+'},\n{'+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(4,0))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(4,1))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(4,2))+','+str(spl_pdf_2011_L0TIS_narrow.a_bin_deg(4,3))+'}};\nDouble_t a_2012_L0TIS_narrow[5][4] = {{'+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(0,0))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(0,1))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(0,2))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(0,3))+'},\n{'+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(1,0))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(1,1))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(1,2))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(1,3))+'},\n{'+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(2,0))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(2,1))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(2,2))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(2,3))+'},\n{'+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(3,0))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(3,1))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(3,2))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(3,3))+'},\n{'+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(4,0))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(4,1))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(4,2))+','+str(spl_pdf_2012_L0TIS_narrow.a_bin_deg(4,3))+'}};\nDouble_t a_2011_L0noTIS_narrow[5][4] = {{'+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(0,0))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(0,1))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(0,2))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(0,3))+'},\n{'+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(1,0))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(1,1))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(1,2))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(1,3))+'},\n{'+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(2,0))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(2,1))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(2,2))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(2,3))+'},\n{'+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(3,0))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(3,1))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(3,2))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(3,3))+'},\n{'+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(4,0))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(4,1))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(4,2))+','+str(spl_pdf_2011_L0noTIS_narrow.a_bin_deg(4,3))+'}};\nDouble_t a_2012_L0noTIS_narrow[5][4] = {{'+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(0,0))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(0,1))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(0,2))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(0,3))+'},\n{'+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(1,0))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(1,1))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(1,2))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(1,3))+'},\n{'+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(2,0))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(2,1))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(2,2))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(2,3))+'},\n{'+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(3,0))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(3,1))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(3,2))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(3,3))+'},\n{'+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(4,0))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(4,1))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(4,2))+','+str(spl_pdf_2012_L0noTIS_narrow.a_bin_deg(4,3))+'}};\n\n'

	splclasstext += 'class Splineclass {\n\n  public:\n\n  Double_t knot(Int_t wide_window,Int_t i) {\n    if (wide_window == 0) {return knots_narrow[i];}\n    else {return knots_wide[i];}\n    }\n\n  Double_t coef(Int_t year_opt,Int_t trig_opt,Int_t wide_window,Int_t ibin,Int_t deg) {\n    if (year_opt == 0) {\n      if (trig_opt == 0) {\n        if (wide_window == 0) {return a_2011_L0TIS_narrow[ibin][deg];}\n        else {return a_2011_L0TIS_wide[ibin][deg];}\n      }\n      else {\n        if (wide_window == 0) {return a_2011_L0noTIS_narrow[ibin][deg];}\n        else {return a_2011_L0noTIS_wide[ibin][deg];}\n      }\n    }\n    else {\n      if (trig_opt == 0) {\n        if (wide_window == 0) {return a_2012_L0TIS_narrow[ibin][deg];}\n        else {return a_2012_L0TIS_wide[ibin][deg];}\n      }\n      else {\n        if (wide_window == 0) {return a_2012_L0noTIS_narrow[ibin][deg];}\n        else {return a_2012_L0noTIS_wide[ibin][deg];}\n      }\n    }\n  }\n\n};'

	fsplh = open('../../src/TimeDependent/Splineclass.h','w')
	fsplh.write(splclasstext)
	fsplh.close()


def createTimeAccHistos(binbounds,data11_L0TIS_wide,data12_L0TIS_wide,data11_L0TIS_narrow,data12_L0TIS_narrow,data11_L0noTIS_wide,data12_L0noTIS_wide,data11_L0noTIS_narrow,data12_L0noTIS_narrow):

	# Two kinds of histograms are created simultaneously (duplicated):
	# list-like for the C++ class and RooDataSet-like for plotting.

	print 'Filling histograms ...'

	# Declaration of the list-like histograms.
	histlist = [[[[],[]],[[],[]]],[[[],[]],[[],[]]]]
	for i in range(len(binbounds)-1):
		histlist[0][0][0].append(0.)
		histlist[0][0][1].append(0.)
		histlist[0][1][0].append(0.)
		histlist[0][1][1].append(0.)
		histlist[1][0][0].append(0.)
		histlist[1][0][1].append(0.)
		histlist[1][1][0].append(0.)
		histlist[1][1][1].append(0.)

	# Declaration of the RooDataSet-like histograms.
	RDH_11L0TISwide_ = RooDataSet("RDH_11L0TISwide_","RDH_11L0TISwide_",RooArgSet(t_MC,MCweight4))
	RDH_12L0TISwide_ = RooDataSet("RDH_12L0TISwide_","RDH_12L0TISwide_",RooArgSet(t_MC,MCweight4))
	RDH_11L0TISnarrow_ = RooDataSet("RDH_11L0TISnarrow_","RDH_11L0TISnarrow_",RooArgSet(t_MC,MCweight4))
	RDH_12L0TISnarrow_ = RooDataSet("RDH_12L0TISnarrow_","RDH_12L0TISnarrow_",RooArgSet(t_MC,MCweight4))
	RDH_11L0noTISwide_ = RooDataSet("RDH_11L0noTISwide_","RDH_11L0noTISwide_",RooArgSet(t_MC,MCweight4))
	RDH_12L0noTISwide_ = RooDataSet("RDH_12L0noTISwide_","RDH_12L0noTISwide_",RooArgSet(t_MC,MCweight4))
	RDH_11L0noTISnarrow_ = RooDataSet("RDH_11L0noTISnarrow_","RDH_11L0noTISnarrow_",RooArgSet(t_MC,MCweight4))
	RDH_12L0noTISnarrow_ = RooDataSet("RDH_12L0noTISnarrow_","RDH_12L0noTISnarrow_",RooArgSet(t_MC,MCweight4))

	# Computation of the normalization factors.
	normfactors = [[[0,0],[0,0]],[[0,0],[0,0]]]
	for i in range(data11_L0TIS_wide.numEntries()):
		if data11_L0TIS_wide.get(i).getRealValue(t_MC.GetName()) < binbounds[1]: normfactors[0][0][1] += data11_L0TIS_wide.get(i).getRealValue(MCweight4.GetName())/binbounds[1]
	for i in range(data12_L0TIS_wide.numEntries()):
		if data12_L0TIS_wide.get(i).getRealValue(t_MC.GetName()) < binbounds[1]: normfactors[1][0][1] += data12_L0TIS_wide.get(i).getRealValue(MCweight4.GetName())/binbounds[1]
	for i in range(data11_L0TIS_narrow.numEntries()):
		if data11_L0TIS_narrow.get(i).getRealValue(t_MC.GetName()) < binbounds[1]: normfactors[0][0][0] += data11_L0TIS_narrow.get(i).getRealValue(MCweight4.GetName())/binbounds[1]
	for i in range(data12_L0TIS_narrow.numEntries()):
		if data12_L0TIS_narrow.get(i).getRealValue(t_MC.GetName()) < binbounds[1]: normfactors[1][0][0] += data12_L0TIS_narrow.get(i).getRealValue(MCweight4.GetName())/binbounds[1]
	for i in range(data11_L0noTIS_wide.numEntries()):
		if data11_L0noTIS_wide.get(i).getRealValue(t_MC.GetName()) < binbounds[1]: normfactors[0][1][1] += data11_L0noTIS_wide.get(i).getRealValue(MCweight4.GetName())/binbounds[1]
	for i in range(data12_L0noTIS_wide.numEntries()):
		if data12_L0noTIS_wide.get(i).getRealValue(t_MC.GetName()) < binbounds[1]: normfactors[1][1][1] += data12_L0noTIS_wide.get(i).getRealValue(MCweight4.GetName())/binbounds[1]
	for i in range(data11_L0noTIS_narrow.numEntries()):
		if data11_L0noTIS_narrow.get(i).getRealValue(t_MC.GetName()) < binbounds[1]: normfactors[0][1][0] += data11_L0noTIS_narrow.get(i).getRealValue(MCweight4.GetName())/binbounds[1]
	for i in range(data12_L0noTIS_narrow.numEntries()):
		if data12_L0noTIS_narrow.get(i).getRealValue(t_MC.GetName()) < binbounds[1]: normfactors[1][1][0] += data12_L0noTIS_narrow.get(i).getRealValue(MCweight4.GetName())/binbounds[1]

	# Auxiliar function used to fill the list-like histograms.
	def fillhist(yearcase,trigcase,windowcase,tau,evweight):
		for i in range(len(binbounds)-1):
			if (tau >= binbounds[i]) and (tau < binbounds[i+1]):
				histlist[yearcase][trigcase][windowcase][i] += evweight/(binbounds[i+1]-binbounds[i])
				break

	# Filling of the two kinds of histograms.
	for i in range(data11_L0TIS_wide.numEntries()):
		ti = data11_L0TIS_wide.get(i).getRealValue(t_MC.GetName())
		wi = data11_L0TIS_wide.get(i).getRealValue(MCweight4.GetName())/normfactors[0][0][1]
		fillhist(0,0,1,ti,wi)
		t_MC.setVal(ti)
		MCweight4.setVal(wi)
		RDH_11L0TISwide_.add(RooArgSet(t_MC,MCweight4))
	for i in range(data12_L0TIS_wide.numEntries()):
		ti = data12_L0TIS_wide.get(i).getRealValue(t_MC.GetName())
		wi = data12_L0TIS_wide.get(i).getRealValue(MCweight4.GetName())/normfactors[1][0][1]
		fillhist(1,0,1,ti,wi)
		t_MC.setVal(ti)
		MCweight4.setVal(wi)
		RDH_12L0TISwide_.add(RooArgSet(t_MC,MCweight4))
	for i in range(data11_L0TIS_narrow.numEntries()):
		ti = data11_L0TIS_narrow.get(i).getRealValue(t_MC.GetName())
		wi = data11_L0TIS_narrow.get(i).getRealValue(MCweight4.GetName())/normfactors[0][0][0]
		fillhist(0,0,0,ti,wi)
		t_MC.setVal(ti)
		MCweight4.setVal(wi)
		RDH_11L0TISnarrow_.add(RooArgSet(t_MC,MCweight4))
	for i in range(data12_L0TIS_narrow.numEntries()):
		ti = data12_L0TIS_narrow.get(i).getRealValue(t_MC.GetName())
		wi = data12_L0TIS_narrow.get(i).getRealValue(MCweight4.GetName())/normfactors[1][0][0]
		fillhist(1,0,0,ti,wi)
		t_MC.setVal(ti)
		MCweight4.setVal(wi)
		RDH_12L0TISnarrow_.add(RooArgSet(t_MC,MCweight4))
	for i in range(data11_L0noTIS_wide.numEntries()):
		ti = data11_L0noTIS_wide.get(i).getRealValue(t_MC.GetName())
		wi = data11_L0noTIS_wide.get(i).getRealValue(MCweight4.GetName())/normfactors[0][1][1]
		fillhist(0,1,1,ti,wi)
		t_MC.setVal(ti)
		MCweight4.setVal(wi)
		RDH_11L0noTISwide_.add(RooArgSet(t_MC,MCweight4))
	for i in range(data12_L0noTIS_wide.numEntries()):
		ti = data12_L0noTIS_wide.get(i).getRealValue(t_MC.GetName())
		wi = data12_L0noTIS_wide.get(i).getRealValue(MCweight4.GetName())/normfactors[1][1][1]
		fillhist(1,1,1,ti,wi)
		t_MC.setVal(ti)
		MCweight4.setVal(wi)
		RDH_12L0noTISwide_.add(RooArgSet(t_MC,MCweight4))
	for i in range(data11_L0noTIS_narrow.numEntries()):
		ti = data11_L0noTIS_narrow.get(i).getRealValue(t_MC.GetName())
		wi = data11_L0noTIS_narrow.get(i).getRealValue(MCweight4.GetName())/normfactors[0][1][0]
		fillhist(0,1,0,ti,wi)
		t_MC.setVal(ti)
		MCweight4.setVal(wi)
		RDH_11L0noTISnarrow_.add(RooArgSet(t_MC,MCweight4))
	for i in range(data12_L0noTIS_narrow.numEntries()):
		ti = data12_L0noTIS_narrow.get(i).getRealValue(t_MC.GetName())
		wi = data12_L0noTIS_narrow.get(i).getRealValue(MCweight4.GetName())/normfactors[1][1][0]
		fillhist(1,1,0,ti,wi)
		t_MC.setVal(ti)
		MCweight4.setVal(wi)
		RDH_12L0noTISnarrow_.add(RooArgSet(t_MC,MCweight4))

	# Applying weights to the RooDataSet-like histograms.
	RDH_11L0TISwide = RooDataSet("RDH_11L0TISwide","RDH_11L0TISwide",RDH_11L0TISwide_,RDH_11L0TISwide_.get(),"",MCweight4.GetName())
	RDH_12L0TISwide = RooDataSet("RDH_12L0TISwide","RDH_12L0TISwide",RDH_12L0TISwide_,RDH_12L0TISwide_.get(),"",MCweight4.GetName())
	RDH_11L0TISnarrow = RooDataSet("RDH_11L0TISnarrow","RDH_11L0TISnarrow",RDH_11L0TISnarrow_,RDH_11L0TISnarrow_.get(),"",MCweight4.GetName())
	RDH_12L0TISnarrow = RooDataSet("RDH_12L0TISnarrow","RDH_12L0TISnarrow",RDH_12L0TISnarrow_,RDH_12L0TISnarrow_.get(),"",MCweight4.GetName())
	RDH_11L0noTISwide = RooDataSet("RDH_11L0noTISwide","RDH_11L0noTISwide",RDH_11L0noTISwide_,RDH_11L0noTISwide_.get(),"",MCweight4.GetName())
	RDH_12L0noTISwide = RooDataSet("RDH_12L0noTISwide","RDH_12L0noTISwide",RDH_12L0noTISwide_,RDH_12L0noTISwide_.get(),"",MCweight4.GetName())
	RDH_11L0noTISnarrow = RooDataSet("RDH_11L0noTISnarrow","RDH_11L0noTISnarrow",RDH_11L0noTISnarrow_,RDH_11L0noTISnarrow_.get(),"",MCweight4.GetName())
	RDH_12L0noTISnarrow = RooDataSet("RDH_12L0noTISnarrow","RDH_12L0noTISnarrow",RDH_12L0noTISnarrow_,RDH_12L0noTISnarrow_.get(),"",MCweight4.GetName())

	print 'Histograms filled.'

	return histlist, [RDH_11L0TISwide,RDH_12L0TISwide,RDH_11L0TISnarrow,RDH_12L0TISnarrow,RDH_11L0noTISwide,RDH_12L0noTISwide,RDH_11L0noTISnarrow,RDH_12L0noTISnarrow]


def printTimeAccHistos(binbounds,histlist):

	nbins = len(binbounds)-1

	histostext = 'Double_t bounds_matrix['+str(nbins+1)+'] = {'
	histostext += str(binbounds[0])
	for i in range(1,len(binbounds)):
		histostext += ','
		if i%10==0: histostext += '\n'
		histostext += str(binbounds[i])
	histostext += '};\n\nDouble_t val_matrix[][2][2]['+str(nbins)+'] = {{{{'
	histostext += str(histlist[0][0][0][0])
	for i in range(1,nbins):
		histostext += ','
		if i%10==0: histostext += '\n'
		histostext += str(histlist[0][0][0][i])
	histostext += '},\n{'
	histostext += str(histlist[0][0][1][0])
	for i in range(1,nbins):
		histostext += ','
		if i%10==0: histostext += '\n'
		histostext += str(histlist[0][0][1][i])
	histostext += '}},\n{{'
	histostext += str(histlist[0][1][0][0])
	for i in range(1,nbins):
		histostext += ','
		if i%10==0: histostext += '\n'
		histostext += str(histlist[0][1][0][i])
	histostext += '},\n{'
	histostext += str(histlist[0][1][1][0])
	for i in range(1,nbins):
		histostext += ','
		if i%10==0: histostext += '\n'
		histostext += str(histlist[0][1][1][i])
	histostext += '}}},\n{{{'
	histostext += str(histlist[1][0][0][0])
	for i in range(1,nbins):
		histostext += ','
		if i%10==0: histostext += '\n'
		histostext += str(histlist[1][0][0][i])
	histostext += '},\n{'
	histostext += str(histlist[1][0][1][0])
	for i in range(1,nbins):
		histostext += ','
		if i%10==0: histostext += '\n'
		histostext += str(histlist[1][0][1][i])
	histostext += '}},\n{{'
	histostext += str(histlist[1][1][0][0])
	for i in range(1,nbins):
		histostext += ','
		if i%10==0: histostext += '\n'
		histostext += str(histlist[1][1][0][i])
	histostext += '},\n{'
	histostext += str(histlist[1][1][1][0])
	for i in range(1,nbins):
		histostext += ','
		if i%10==0: histostext += '\n'
		histostext += str(histlist[1][1][1][i])
	histostext += '}}}};\n\nclass TAccclass {\n\n  public:\n\n  Int_t nbins = '+str(nbins)+';\n\n  Double_t bounds(Int_t ibound) {\n    return bounds_matrix[ibound];\n    };\n\n  Double_t val(Int_t year_opt,Int_t trig_opt,Int_t wide_window,Int_t ibin) {\n    return val_matrix[year_opt][trig_opt][wide_window][ibin];\n    };\n\n};'

	fTAcch = open('../../src/TimeDependent/TAccclass.h','w')
	fTAcch.write(histostext)
	fTAcch.close()


def plotTimeAccHistos(binbounds,RDSlist,output_tag):

	fr_tacc_11_L0TIS_wide = t_MC.frame()
	fr_tacc_12_L0TIS_wide = t_MC.frame()
	fr_tacc_11_L0TIS_narrow = t_MC.frame()
	fr_tacc_12_L0TIS_narrow = t_MC.frame()
	fr_tacc_11_L0noTIS_wide = t_MC.frame()
	fr_tacc_12_L0noTIS_wide = t_MC.frame()
	fr_tacc_11_L0noTIS_narrow = t_MC.frame()
	fr_tacc_12_L0noTIS_narrow = t_MC.frame()

	tMCbinning = getRooBinning(t_MC,binbounds)

	RDSlist[0].plotOn(fr_tacc_11_L0TIS_wide,RooFit.Binning(tMCbinning),RooFit.LineColor(kRed))
	RDSlist[1].plotOn(fr_tacc_12_L0TIS_wide,RooFit.Binning(tMCbinning),RooFit.LineColor(kRed))
	RDSlist[2].plotOn(fr_tacc_11_L0TIS_narrow,RooFit.Binning(tMCbinning),RooFit.LineColor(kRed))
	RDSlist[3].plotOn(fr_tacc_12_L0TIS_narrow,RooFit.Binning(tMCbinning),RooFit.LineColor(kRed))
	RDSlist[4].plotOn(fr_tacc_11_L0noTIS_wide,RooFit.Binning(tMCbinning),RooFit.LineColor(kRed))
	RDSlist[5].plotOn(fr_tacc_12_L0noTIS_wide,RooFit.Binning(tMCbinning),RooFit.LineColor(kRed))
	RDSlist[6].plotOn(fr_tacc_11_L0noTIS_narrow,RooFit.Binning(tMCbinning),RooFit.LineColor(kRed))
	RDSlist[7].plotOn(fr_tacc_12_L0noTIS_narrow,RooFit.Binning(tMCbinning),RooFit.LineColor(kRed))
	map(lambda x: x.GetYaxis().SetTitle("Efficiency (a.u.)"),[fr_tacc_11_L0TIS_wide,fr_tacc_12_L0TIS_wide,fr_tacc_11_L0TIS_narrow,fr_tacc_12_L0TIS_narrow,fr_tacc_11_L0noTIS_wide,fr_tacc_12_L0noTIS_wide,fr_tacc_11_L0noTIS_narrow,fr_tacc_12_L0noTIS_narrow])
	map(lambda x: x.GetXaxis().SetTitle("Time (ps)"),[fr_tacc_11_L0TIS_wide,fr_tacc_12_L0TIS_wide,fr_tacc_11_L0TIS_narrow,fr_tacc_12_L0TIS_narrow,fr_tacc_11_L0noTIS_wide,fr_tacc_12_L0noTIS_wide,fr_tacc_11_L0noTIS_narrow,fr_tacc_12_L0noTIS_narrow])

	c_tacc_wide = TCanvas("c_tacc_wide","c_tacc_wide")
	c_tacc_wide.Divide(2,2)
	c_tacc_wide.cd(1)
	fr_tacc_11_L0TIS_wide.Draw()
	c_tacc_wide.cd(2)
	fr_tacc_11_L0noTIS_wide.Draw()
	c_tacc_wide.cd(3)
	fr_tacc_12_L0TIS_wide.Draw()
	c_tacc_wide.cd(4)
	fr_tacc_12_L0noTIS_wide.Draw()
	c_tacc_narrow = TCanvas("c_tacc_narrow","c_tacc_narrow")
	c_tacc_narrow.Divide(2,2)
	c_tacc_narrow.cd(1)
	fr_tacc_11_L0TIS_narrow.Draw()
	c_tacc_narrow.cd(2)
	fr_tacc_11_L0noTIS_narrow.Draw()
	c_tacc_narrow.cd(3)
	fr_tacc_12_L0TIS_narrow.Draw()
	c_tacc_narrow.cd(4)
	fr_tacc_12_L0noTIS_narrow.Draw()

	c_tacc_wide.Print(output_tag + "_wide.root")
	c_tacc_wide.Print(output_tag + "_wide.pdf")
	c_tacc_narrow.Print(output_tag + "_narrow.root")
	c_tacc_narrow.Print(output_tag + "_narrow.pdf")


def ComputeTimeIntegrals(PDF_phys_wide,PDF_phys_narrow,data4_2011_L0TIS_wide,data4_2012_L0TIS_wide,data4_2011_L0TIS_narrow,data4_2012_L0TIS_narrow,data4_2011_L0noTIS_wide,data4_2012_L0noTIS_wide,data4_2011_L0noTIS_narrow,data4_2012_L0noTIS_narrow):

	T_cosh_integral_2011_L0TIS_wide = 0.
	T_sinh_integral_2011_L0TIS_wide = 0.
	T_cos_integral_2011_L0TIS_wide = 0.
	T_sin_integral_2011_L0TIS_wide = 0.
	T_cosh_integral_2012_L0TIS_wide = 0.
	T_sinh_integral_2012_L0TIS_wide = 0.
	T_cos_integral_2012_L0TIS_wide = 0.
	T_sin_integral_2012_L0TIS_wide = 0.
	T_cosh_integral_2011_L0TIS_narrow = 0.
	T_sinh_integral_2011_L0TIS_narrow = 0.
	T_cos_integral_2011_L0TIS_narrow = 0.
	T_sin_integral_2011_L0TIS_narrow = 0.
	T_cosh_integral_2012_L0TIS_narrow = 0.
	T_sinh_integral_2012_L0TIS_narrow = 0.
	T_cos_integral_2012_L0TIS_narrow = 0.
	T_sin_integral_2012_L0TIS_narrow = 0.
	T_cosh_integral_2011_L0noTIS_wide = 0.
	T_sinh_integral_2011_L0noTIS_wide = 0.
	T_cos_integral_2011_L0noTIS_wide = 0.
	T_sin_integral_2011_L0noTIS_wide = 0.
	T_cosh_integral_2012_L0noTIS_wide = 0.
	T_sinh_integral_2012_L0noTIS_wide = 0.
	T_cos_integral_2012_L0noTIS_wide = 0.
	T_sin_integral_2012_L0noTIS_wide = 0.
	T_cosh_integral_2011_L0noTIS_narrow = 0.
	T_sinh_integral_2011_L0noTIS_narrow = 0.
	T_cos_integral_2011_L0noTIS_narrow = 0.
	T_sin_integral_2011_L0noTIS_narrow = 0.
	T_cosh_integral_2012_L0noTIS_narrow = 0.
	T_sinh_integral_2012_L0noTIS_narrow = 0.
	T_cos_integral_2012_L0noTIS_narrow = 0.
	T_sin_integral_2012_L0noTIS_narrow = 0.

	for i in range(data4_2011_L0TIS_wide.numEntries()):
		t_var = data4_2011_L0TIS_wide.get(i).getRealValue(t_name_MC)
		norm = data4_2011_L0TIS_wide.get(i).getRealValue("MCweight4")
		T_cosh_integral_2011_L0TIS_wide += norm*PDF_phys_wide.T_cosh_eff(t_var)
		T_sinh_integral_2011_L0TIS_wide += norm*PDF_phys_wide.T_sinh_eff(t_var)
		T_cos_integral_2011_L0TIS_wide += norm*PDF_phys_wide.T_cos_eff(t_var)
		T_sin_integral_2011_L0TIS_wide += norm*PDF_phys_wide.T_sin_eff(t_var)
	for i in range(data4_2012_L0TIS_wide.numEntries()):
		t_var = data4_2012_L0TIS_wide.get(i).getRealValue(t_name_MC)
		norm = data4_2012_L0TIS_wide.get(i).getRealValue("MCweight4")
		T_cosh_integral_2012_L0TIS_wide += norm*PDF_phys_wide.T_cosh_eff(t_var)
		T_sinh_integral_2012_L0TIS_wide += norm*PDF_phys_wide.T_sinh_eff(t_var)
		T_cos_integral_2012_L0TIS_wide += norm*PDF_phys_wide.T_cos_eff(t_var)
		T_sin_integral_2012_L0TIS_wide += norm*PDF_phys_wide.T_sin_eff(t_var)
	for i in range(data4_2011_L0TIS_narrow.numEntries()):
		t_var = data4_2011_L0TIS_narrow.get(i).getRealValue(t_name_MC)
		norm = data4_2011_L0TIS_narrow.get(i).getRealValue("MCweight4")
		T_cosh_integral_2011_L0TIS_narrow += norm*PDF_phys_narrow.T_cosh_eff(t_var)
		T_sinh_integral_2011_L0TIS_narrow += norm*PDF_phys_narrow.T_sinh_eff(t_var)
		T_cos_integral_2011_L0TIS_narrow += norm*PDF_phys_narrow.T_cos_eff(t_var)
		T_sin_integral_2011_L0TIS_narrow += norm*PDF_phys_narrow.T_sin_eff(t_var)
	for i in range(data4_2012_L0TIS_narrow.numEntries()):
		t_var = data4_2012_L0TIS_narrow.get(i).getRealValue(t_name_MC)
		norm = data4_2012_L0TIS_narrow.get(i).getRealValue("MCweight4")
		T_cosh_integral_2012_L0TIS_narrow += norm*PDF_phys_narrow.T_cosh_eff(t_var)
		T_sinh_integral_2012_L0TIS_narrow += norm*PDF_phys_narrow.T_sinh_eff(t_var)
		T_cos_integral_2012_L0TIS_narrow += norm*PDF_phys_narrow.T_cos_eff(t_var)
		T_sin_integral_2012_L0TIS_narrow += norm*PDF_phys_narrow.T_sin_eff(t_var)
	for i in range(data4_2011_L0noTIS_wide.numEntries()):
		t_var = data4_2011_L0noTIS_wide.get(i).getRealValue(t_name_MC)
		norm = data4_2011_L0noTIS_wide.get(i).getRealValue("MCweight4")
		T_cosh_integral_2011_L0noTIS_wide += norm*PDF_phys_wide.T_cosh_eff(t_var)
		T_sinh_integral_2011_L0noTIS_wide += norm*PDF_phys_wide.T_sinh_eff(t_var)
		T_cos_integral_2011_L0noTIS_wide += norm*PDF_phys_wide.T_cos_eff(t_var)
		T_sin_integral_2011_L0noTIS_wide += norm*PDF_phys_wide.T_sin_eff(t_var)
	for i in range(data4_2012_L0noTIS_wide.numEntries()):
		t_var = data4_2012_L0noTIS_wide.get(i).getRealValue(t_name_MC)
		norm = data4_2012_L0noTIS_wide.get(i).getRealValue("MCweight4")
		T_cosh_integral_2012_L0noTIS_wide += norm*PDF_phys_wide.T_cosh_eff(t_var)
		T_sinh_integral_2012_L0noTIS_wide += norm*PDF_phys_wide.T_sinh_eff(t_var)
		T_cos_integral_2012_L0noTIS_wide += norm*PDF_phys_wide.T_cos_eff(t_var)
		T_sin_integral_2012_L0noTIS_wide += norm*PDF_phys_wide.T_sin_eff(t_var)
	for i in range(data4_2011_L0noTIS_narrow.numEntries()):
		t_var = data4_2011_L0noTIS_narrow.get(i).getRealValue(t_name_MC)
		norm = data4_2011_L0noTIS_narrow.get(i).getRealValue("MCweight4")
		T_cosh_integral_2011_L0noTIS_narrow += norm*PDF_phys_narrow.T_cosh_eff(t_var)
		T_sinh_integral_2011_L0noTIS_narrow += norm*PDF_phys_narrow.T_sinh_eff(t_var)
		T_cos_integral_2011_L0noTIS_narrow += norm*PDF_phys_narrow.T_cos_eff(t_var)
		T_sin_integral_2011_L0noTIS_narrow += norm*PDF_phys_narrow.T_sin_eff(t_var)
	for i in range(data4_2012_L0noTIS_narrow.numEntries()):
		t_var = data4_2012_L0noTIS_narrow.get(i).getRealValue(t_name_MC)
		norm = data4_2012_L0noTIS_narrow.get(i).getRealValue("MCweight4")
		T_cosh_integral_2012_L0noTIS_narrow += norm*PDF_phys_narrow.T_cosh_eff(t_var)
		T_sinh_integral_2012_L0noTIS_narrow += norm*PDF_phys_narrow.T_sinh_eff(t_var)
		T_cos_integral_2012_L0noTIS_narrow += norm*PDF_phys_narrow.T_cos_eff(t_var)
		T_sin_integral_2012_L0noTIS_narrow += norm*PDF_phys_narrow.T_sin_eff(t_var)

	IT_cosh_accu_2011_L0TIS_wide.setVal(T_cosh_integral_2011_L0TIS_wide/T_cosh_integral_2011_L0TIS_wide)
	IT_sinh_accu_2011_L0TIS_wide.setVal(T_sinh_integral_2011_L0TIS_wide/T_cosh_integral_2011_L0TIS_wide)
	IT_cos_accu_2011_L0TIS_wide.setVal(T_cos_integral_2011_L0TIS_wide/T_cosh_integral_2011_L0TIS_wide)
	IT_sin_accu_2011_L0TIS_wide.setVal(T_sin_integral_2011_L0TIS_wide/T_cosh_integral_2011_L0TIS_wide)
	IT_cosh_accu_2012_L0TIS_wide.setVal(T_cosh_integral_2012_L0TIS_wide/T_cosh_integral_2012_L0TIS_wide)
	IT_sinh_accu_2012_L0TIS_wide.setVal(T_sinh_integral_2012_L0TIS_wide/T_cosh_integral_2012_L0TIS_wide)
	IT_cos_accu_2012_L0TIS_wide.setVal(T_cos_integral_2012_L0TIS_wide/T_cosh_integral_2012_L0TIS_wide)
	IT_sin_accu_2012_L0TIS_wide.setVal(T_sin_integral_2012_L0TIS_wide/T_cosh_integral_2012_L0TIS_wide)
	IT_cosh_accu_2011_L0TIS_narrow.setVal(T_cosh_integral_2011_L0TIS_narrow/T_cosh_integral_2011_L0TIS_narrow)
	IT_sinh_accu_2011_L0TIS_narrow.setVal(T_sinh_integral_2011_L0TIS_narrow/T_cosh_integral_2011_L0TIS_narrow)
	IT_cos_accu_2011_L0TIS_narrow.setVal(T_cos_integral_2011_L0TIS_narrow/T_cosh_integral_2011_L0TIS_narrow)
	IT_sin_accu_2011_L0TIS_narrow.setVal(T_sin_integral_2011_L0TIS_narrow/T_cosh_integral_2011_L0TIS_narrow)
	IT_cosh_accu_2012_L0TIS_narrow.setVal(T_cosh_integral_2012_L0TIS_narrow/T_cosh_integral_2012_L0TIS_narrow)
	IT_sinh_accu_2012_L0TIS_narrow.setVal(T_sinh_integral_2012_L0TIS_narrow/T_cosh_integral_2012_L0TIS_narrow)
	IT_cos_accu_2012_L0TIS_narrow.setVal(T_cos_integral_2012_L0TIS_narrow/T_cosh_integral_2012_L0TIS_narrow)
	IT_sin_accu_2012_L0TIS_narrow.setVal(T_sin_integral_2012_L0TIS_narrow/T_cosh_integral_2012_L0TIS_narrow)
	IT_cosh_accu_2011_L0noTIS_wide.setVal(T_cosh_integral_2011_L0noTIS_wide/T_cosh_integral_2011_L0noTIS_wide)
	IT_sinh_accu_2011_L0noTIS_wide.setVal(T_sinh_integral_2011_L0noTIS_wide/T_cosh_integral_2011_L0noTIS_wide)
	IT_cos_accu_2011_L0noTIS_wide.setVal(T_cos_integral_2011_L0noTIS_wide/T_cosh_integral_2011_L0noTIS_wide)
	IT_sin_accu_2011_L0noTIS_wide.setVal(T_sin_integral_2011_L0noTIS_wide/T_cosh_integral_2011_L0noTIS_wide)
	IT_cosh_accu_2012_L0noTIS_wide.setVal(T_cosh_integral_2012_L0noTIS_wide/T_cosh_integral_2012_L0noTIS_wide)
	IT_sinh_accu_2012_L0noTIS_wide.setVal(T_sinh_integral_2012_L0noTIS_wide/T_cosh_integral_2012_L0noTIS_wide)
	IT_cos_accu_2012_L0noTIS_wide.setVal(T_cos_integral_2012_L0noTIS_wide/T_cosh_integral_2012_L0noTIS_wide)
	IT_sin_accu_2012_L0noTIS_wide.setVal(T_sin_integral_2012_L0noTIS_wide/T_cosh_integral_2012_L0noTIS_wide)
	IT_cosh_accu_2011_L0noTIS_narrow.setVal(T_cosh_integral_2011_L0noTIS_narrow/T_cosh_integral_2011_L0noTIS_narrow)
	IT_sinh_accu_2011_L0noTIS_narrow.setVal(T_sinh_integral_2011_L0noTIS_narrow/T_cosh_integral_2011_L0noTIS_narrow)
	IT_cos_accu_2011_L0noTIS_narrow.setVal(T_cos_integral_2011_L0noTIS_narrow/T_cosh_integral_2011_L0noTIS_narrow)
	IT_sin_accu_2011_L0noTIS_narrow.setVal(T_sin_integral_2011_L0noTIS_narrow/T_cosh_integral_2011_L0noTIS_narrow)
	IT_cosh_accu_2012_L0noTIS_narrow.setVal(T_cosh_integral_2012_L0noTIS_narrow/T_cosh_integral_2012_L0noTIS_narrow)
	IT_sinh_accu_2012_L0noTIS_narrow.setVal(T_sinh_integral_2012_L0noTIS_narrow/T_cosh_integral_2012_L0noTIS_narrow)
	IT_cos_accu_2012_L0noTIS_narrow.setVal(T_cos_integral_2012_L0noTIS_narrow/T_cosh_integral_2012_L0noTIS_narrow)
	IT_sin_accu_2012_L0noTIS_narrow.setVal(T_sin_integral_2012_L0noTIS_narrow/T_cosh_integral_2012_L0noTIS_narrow)


def PrintTimeInts():

	ITclass = 'class ITclass {\n\n  public:\n\n  Double_t IT_cosh(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(IT_cosh_accu_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(IT_cosh_accu_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(IT_cosh_accu_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(IT_cosh_accu_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(IT_cosh_accu_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(IT_cosh_accu_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(IT_cosh_accu_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(IT_cosh_accu_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n  Double_t IT_sinh(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(IT_sinh_accu_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(IT_sinh_accu_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(IT_sinh_accu_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(IT_sinh_accu_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(IT_sinh_accu_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(IT_sinh_accu_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(IT_sinh_accu_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(IT_sinh_accu_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n  Double_t IT_cos(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(IT_cos_accu_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(IT_cos_accu_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(IT_cos_accu_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(IT_cos_accu_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(IT_cos_accu_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(IT_cos_accu_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(IT_cos_accu_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(IT_cos_accu_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n  Double_t IT_sin(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return '+str(IT_sin_accu_2011_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return '+str(IT_sin_accu_2011_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return '+str(IT_sin_accu_2011_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return '+str(IT_sin_accu_2011_L0noTIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return '+str(IT_sin_accu_2012_L0TIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return '+str(IT_sin_accu_2012_L0TIS_wide.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return '+str(IT_sin_accu_2012_L0noTIS_narrow.getVal())+';}\n    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return '+str(IT_sin_accu_2012_L0noTIS_wide.getVal())+';}\n    return 0.;\n    };\n\n};'

	fTimecxx = open('../../src/TimeDependent/ITclass.h','w')
	fTimecxx.write(ITclass)
	fTimecxx.close()


def FitnPlotGenAcc(model_acc_kpi1_gen_wide,model_acc_kpi1_gen_narrow,model_acc_kpi2_gen_wide,model_acc_kpi2_gen_narrow,\
model_acc_sim_gen_wide,model_acc_sim_gen_narrow,spl_pdf_gen_wide,spl_pdf_gen_narrow,\
data1_gen_wide,data2_gen_wide,data4_gen_wide,data1_gen_narrow,data2_gen_narrow,data4_gen_narrow,data1_kpi1_gen_wide,data1_kpi2_gen_wide,\
data2_kpi1_gen_wide,data2_kpi2_gen_wide,data1_kpi1_gen_narrow,data1_kpi2_gen_narrow,data2_kpi1_gen_narrow,data2_kpi2_gen_narrow):

	# Mass and angular acceptance fit (polynomials)

	opt_acc.setVal(1)
	map(lambda x:x.setConstant(1),[cos1_MC,cos2_MC,phi_MC,t_MC,k1_gen_wide,k2_gen_wide,k3_gen_wide,k4_gen_wide,k5_gen_wide,k1_gen_narrow,k2_gen_narrow,k3_gen_narrow,k4_gen_narrow,k5_gen_narrow])
	model_acc_sim_gen_wide.fitTo(data1_gen_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_gen_narrow.fitTo(data1_gen_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	map(lambda x:x.setConstant(0),[cos1_MC,cos2_MC,phi_MC,t_MC,k1_gen_wide,k2_gen_wide,k3_gen_wide,k4_gen_wide,k5_gen_wide,k1_gen_narrow,k2_gen_narrow,k3_gen_narrow,k4_gen_narrow,k5_gen_narrow])
	opt_acc.setVal(2)
	map(lambda x:x.setConstant(1),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,phi_MC,t_MC,p1_gen_wide,p1_gen_narrow])
	model_acc_sim_gen_wide.fitTo(data2_gen_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_sim_gen_narrow.fitTo(data2_gen_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	map(lambda x:x.setConstant(0),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,phi_MC,t_MC,p1_gen_wide,p1_gen_narrow])

	# Time acceptance fit (splines)

	numknots = 6
	knots_wide = adaptiveBinning(t_MC,numknots-1,0,data4_gen_wide)
	knots_narrow = adaptiveBinning(t_MC,numknots-1,0,data4_gen_narrow)
	for i in range(numknots):
		knots_wide[i] = round(knots_wide[i],1)
		knots_narrow[i] = round(knots_narrow[i],1)
	ti_wide = [t0_wide,t1_wide,t2_wide,t3_wide,t4_wide,t5_wide]
	ti_narrow = [t0_narrow,t1_narrow,t2_narrow,t3_narrow,t4_narrow,t5_narrow]
	for i in range(numknots):
		ti_wide[i].setVal(knots_wide[i])
		ti_narrow[i].setVal(knots_narrow[i])

	spl_pdf_gen_wide.fitTo(data4_gen_wide,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	spl_pdf_gen_narrow.fitTo(data4_gen_narrow,RooFit.NumCPU(8),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))

	# Plotting

	data1_kpi1_gen_wide.plotOn(frame_m1_MC_gen_wide,RooFit.Binning(20),RooFit.MarkerSize(0.5))
	data1_kpi2_gen_wide.plotOn(frame_m2_MC_gen_wide,RooFit.Binning(20),RooFit.MarkerSize(0.5))
	data2_kpi1_gen_wide.plotOn(frame_cos1_MC_gen_wide,RooFit.Binning(20),RooFit.MarkerSize(0.5))
	data2_kpi2_gen_wide.plotOn(frame_cos2_MC_gen_wide,RooFit.Binning(20),RooFit.MarkerSize(0.5))
	data1_kpi1_gen_narrow.plotOn(frame_m1_MC_gen_narrow,RooFit.Binning(12),RooFit.MarkerSize(0.5))
	data1_kpi2_gen_narrow.plotOn(frame_m2_MC_gen_narrow,RooFit.Binning(12),RooFit.MarkerSize(0.5))
	data2_kpi1_gen_narrow.plotOn(frame_cos1_MC_gen_narrow,RooFit.Binning(12),RooFit.MarkerSize(0.5))
	data2_kpi2_gen_narrow.plotOn(frame_cos2_MC_gen_narrow,RooFit.Binning(12),RooFit.MarkerSize(0.5))
	opt_acc.setVal(1)
	model_acc_kpi1_gen_wide.plotOn(frame_m1_MC_gen_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_gen_wide.plotOn(frame_m2_MC_gen_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_gen_narrow.plotOn(frame_m1_MC_gen_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_gen_narrow.plotOn(frame_m2_MC_gen_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(2)
	model_acc_kpi1_gen_wide.plotOn(frame_cos1_MC_gen_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_gen_wide.plotOn(frame_cos2_MC_gen_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi1_gen_narrow.plotOn(frame_cos1_MC_gen_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_kpi2_gen_narrow.plotOn(frame_cos2_MC_gen_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))

	data4_gen_wide.plotOn(frame_t_MC_gen_wide,RooFit.Binning(30),RooFit.MarkerSize(0.5))
	spl_pdf_gen_wide.plotOn(frame_t_MC_gen_wide,RooFit.LineColor(kBlue))
	data4_gen_narrow.plotOn(frame_t_MC_gen_narrow,RooFit.Binning(30),RooFit.MarkerSize(0.5))
	spl_pdf_gen_narrow.plotOn(frame_t_MC_gen_narrow,RooFit.LineColor(kBlue))

	label_cat = TText()
	label_cat.SetNDC()
	tl1_wide = 0.14+knots_wide[1]/12.*0.81
	tl2_wide = 0.14+knots_wide[2]/12.*0.81
	tl3_wide = 0.14+knots_wide[3]/12.*0.81
	tl4_wide = 0.14+knots_wide[4]/12.*0.81
	tl1_narrow = 0.14+knots_narrow[1]/12.*0.81
	tl2_narrow = 0.14+knots_narrow[2]/12.*0.81
	tl3_narrow = 0.14+knots_narrow[3]/12.*0.81
	tl4_narrow = 0.14+knots_narrow[4]/12.*0.81
	l1_wide = TLine(tl1_wide,0.16,tl1_wide,0.95)
	l1_wide.SetNDC()
	l1_wide.SetLineStyle(2)
	l2_wide = TLine(tl2_wide,0.16,tl2_wide,0.95)
	l2_wide.SetNDC()
	l2_wide.SetLineStyle(2)
	l3_wide = TLine(tl3_wide,0.16,tl3_wide,0.95)
	l3_wide.SetNDC()
	l3_wide.SetLineStyle(2)
	l4_wide = TLine(tl4_wide,0.16,tl4_wide,0.95)
	l4_wide.SetNDC()
	l4_wide.SetLineStyle(2)
	l1_narrow = TLine(tl1_narrow,0.16,tl1_narrow,0.95)
	l1_narrow.SetNDC()
	l1_narrow.SetLineStyle(2)
	l2_narrow = TLine(tl2_narrow,0.16,tl2_narrow,0.95)
	l2_narrow.SetNDC()
	l2_narrow.SetLineStyle(2)
	l3_narrow = TLine(tl3_narrow,0.16,tl3_narrow,0.95)
	l3_narrow.SetNDC()
	l3_narrow.SetLineStyle(2)
	l4_narrow = TLine(tl4_narrow,0.16,tl4_narrow,0.95)
	l4_narrow.SetNDC()
	l4_narrow.SetLineStyle(2)

	cgen_wide = TCanvas("cgen_wide","cgen_wide",1200,600)
	cgen_wide.Divide(3,2)
	cgen_wide.cd(1)
	frame_cos1_MC_gen_wide.Draw()
	cgen_wide.cd(2)
	frame_cos2_MC_gen_wide.Draw()
	cgen_wide.cd(3)
	frame_t_MC_gen_wide.Draw()
	map(lambda x: x.Draw(),[l1_wide,l2_wide,l3_wide,l4_wide])
	cgen_wide.cd(4)
	frame_m1_MC_gen_wide.Draw()
	cgen_wide.cd(5)
	frame_m2_MC_gen_wide.Draw()

	cgen_narrow = TCanvas("cgen_narrow","cgen_narrow",1200,600)
	cgen_narrow.Divide(3,2)
	cgen_narrow.cd(1)
	frame_cos1_MC_gen_narrow.Draw()
	cgen_narrow.cd(2)
	frame_cos2_MC_gen_narrow.Draw()
	cgen_narrow.cd(3)
	frame_t_MC_gen_narrow.Draw()
	map(lambda x: x.Draw(),[l1_narrow,l2_narrow,l3_narrow,l4_narrow])
	cgen_narrow.cd(4)
	frame_m1_MC_gen_narrow.Draw()
	cgen_narrow.cd(5)
	frame_m2_MC_gen_narrow.Draw()

	cgen_wide.Print("genacc_wide.pdf")
	cgen_narrow.Print("genacc_narrow.pdf")

	return
