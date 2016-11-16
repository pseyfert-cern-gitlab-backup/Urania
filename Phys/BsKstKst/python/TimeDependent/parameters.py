from ROOT import *
from math import *
import os


# Environment locations.
currentpath = os.getcwd()
if currentpath == '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent':
	NTUPLE_PATH = "/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/fast_ntuples/"
	SOURCE_PATH = '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/'
	print '\nINFO: lxplus environment loaded.'
elif currentpath == '/home/galaceos/Escritorio/DATA_Analysis/Software/Bs2KpiKpi/lxplus/python/TimeDependent':
	NTUPLE_PATH = "/home/galaceos/Escritorio/DATA_Analysis/Software/Bs2KpiKpi/lxplus/fast_ntuples/"
	SOURCE_PATH = '/home/galaceos/Escritorio/DATA_Analysis/Software/Bs2KpiKpi/lxplus/src/TimeDependent/'
	print "\nINFO: Local environment loaded."


# Blinding.
blindCat = RooCategory("blindCat","blindCat")
blindCat.defineType("unblind",0)
blindCat.defineType("blind",1)
blindCat.setConstant(1)
blinding_scale = 0.02


# ################################################################
# V A R I A B L E S   O F   T H E   P D F
# ################################################################

# Names of the variables in the ntuples.
mKpiKpi_name = "B_s0_DTF_B_s0_M"
weight_name = "bs2kstkst_y_sw"
m1_name = "B_s0_DTF_KST1_M"
m2_name = "B_s0_DTF_KST2_M"
cos1_name = "B_s0_DTF_B_s0_CosTheta1"
cos2_name = "B_s0_DTF_B_s0_CosTheta2"
phi_name = "B_s0_DTF_B_s0_Phi1"
t_name = "B_s0_DTF_TAU"
terror_name = "B_s0_DTF_TAUERR"
dec_SSK_name = "B_s0_SS_nnetKaon_DEC"
dec_OS_name = "B_s0_TAGDECISION_OS"
eta_SSK_name = "B_s0_SS_nnetKaon_PROB"
eta_OS_name = "B_s0_TAGOMEGA_OS"

# Options.
wide_window_opt = RooRealVar("wide_window_opt","wide_window_opt",1.)
year_opt = RooRealVar("year_opt","year_opt",1.)
alt_fit = RooRealVar("alt_fit","alt_fit",0.)
option = RooRealVar("option","option",0.)
flatacc = RooRealVar("flatacc","flatacc",0)
nwacc = RooRealVar("nwacc","nwacc",1)
inftres = RooRealVar("inftres","inftres",0)
A_j1 = RooRealVar("A_j1","A_j1",9)
A_j2 = RooRealVar("A_j2","A_j2",9)
A_h = RooRealVar("A_h","A_h",9)	
A_j1p = RooRealVar("A_j1p","A_j1p",9)
A_j2p = RooRealVar("A_j2p","A_j2p",9)
A_hp = RooRealVar("A_hp","A_hp",9)
qcomp = RooRealVar("qcomp","qcomp",9)

# Observables.
mKp1 = RooRealVar(m1_name,"M(K^{+}#pi^{-}) ", 750., 1700.,"MeV/c^{2}")
mKp2 = RooRealVar(m2_name,"M(K^{-}#pi^{+}) ", 750., 1700.,"MeV/c^{2}")
mKp1_narrowwin = RooRealVar(m1_name,"M(K^{+}#pi^{-}) ",900.-150.,900.+150.,"MeV/c^{2}")
mKp2_narrowwin = RooRealVar(m2_name,"M(K^{-}#pi^{+}) ",900.-150.,900.+150.,"MeV/c^{2}")
cos1 = RooRealVar(cos1_name,"cos(#theta_{1})", -1., 1.,"")
cos2 = RooRealVar(cos2_name,"cos(#theta_{2})", -1., 1.,"")
phi = RooRealVar(phi_name,"#varphi",-pi,pi,"rad")
t = RooRealVar(t_name,"t",0.,12.,"ps")
terror = RooRealVar(terror_name,"#delta t",0.,0.1,"ps")
decision_SSK = RooCategory(dec_SSK_name,"q^{SSK}")
decision_SSK.defineType("Bsbartagged",-1)
decision_SSK.defineType("untagged",0)
decision_SSK.defineType("Bstagged",1)
decision_OS = RooCategory(dec_OS_name,"q^{OS}")
decision_OS.defineType("Bsbartagged",-1)
decision_OS.defineType("untagged",0)
decision_OS.defineType("Bstagged",1)
etamistag_SSK = RooRealVar(eta_SSK_name,"#eta^{SSK}",0.,0.5)
etamistag_OS = RooRealVar(eta_OS_name,"#eta^{OS}",0.,0.5)
FullArgSet = RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,terror)
FullArgSet.add(decision_SSK)
FullArgSet.add(decision_OS)
FullArgSet.add(etamistag_SSK)
FullArgSet.add(etamistag_OS)

# Wave fractions.
f_SS = RooRealVar("f_SS","f_{SS}",1.38189e-01,0.,1.)
f_Swave = RooRealVar("f_Swave","f_{S-wave}",0.7,0.,1.)
f_TT = RooRealVar("f_TT","f_{TT}",0.4,0.,1.)
f_VTTV = RooRealVar("f_VTTV","f_{VTTV}",0.7,0.,1.)
f_VV = RooRealVar("f_VV","f_{VV}",2.96226e-01,0.,1.)
D_STTS = RooRealVar("D_STTS","#Delta^{isospin}_{STTS}",-0.9,-1.,1.)
D_SVVS = RooRealVar("D_SVVS","#Delta^{isospin}_{SVVS}",-2.49599e-01,-1.,1.)
D_VTTV = RooRealVar("D_VTTV","#Delta^{isospin}_{VTTV}",0.2,-1.,1.)
fL_TT = RooRealVar("fL_TT","f_{L}^{TT}",0.2,0.,1.)
fL_TV = RooRealVar("fL_TV","f_{L}^{TV}",0.8,0.,1.)
fL_VT = RooRealVar("fL_VT","f_{L}^{VT}",0.7,0.,1.)
fL_VV = RooRealVar("fL_VV","f_{L}^{VV}",2.74709e-01,0.,1.)
xpar1_TT = RooRealVar("xpar1_TT","x_{#parallel1}^{TT}",0.3,0.,1.)
xpar2_TT = RooRealVar("xpar2_TT","x_{#parallel2}^{TT}",0.4,0.,1.)
xpar_TV = RooRealVar("xpar_TV","x_{#parallel}^{TV}",0.1,0.,1.)
xpar_VT = RooRealVar("xpar_VT","x_{#parallel}^{VT}",0.6,0.,1.)
xpar_VV = RooRealVar("xpar_VV","x_{#parallel}^{VV}",3.40255e-01,0.,1.)
xperp1_TT = RooRealVar("xperp1_TT","x_{#perp1}^{TT}",0.4,0.,1.)

# Direct CP violation asymmetries.
DCP = RooRealVar("DCP","#Delta^{CP}",0.,-1.,1.)
DCP_SS = RooRealVar("DCP_SS","#Delta^{CP}_{SS}",0.,-1.,1.)
DCP_SV = RooRealVar("DCP_SV","#Delta^{CP}_{SV}",0.,-1.,1.)
DCP_VS = RooRealVar("DCP_VS","#Delta^{CP}_{VS}",0.,-1.,1.)
DCP_ST = RooRealVar("DCP_ST","#Delta^{CP}_{ST}",0.,-1.,1.)
DCP_TS = RooRealVar("DCP_TS","#Delta^{CP}_{TS}",0.,-1.,1.)
DCP_VV = RooRealVar("DCP_VV","#Delta^{CP}_{VV}",0.,-1.,1.)
DCP_VT = RooRealVar("DCP_VT","#Delta^{CP}_{VT}",0.,-1.,1.)
DCP_TV = RooRealVar("DCP_TV","#Delta^{CP}_{TV}",0.,-1.,1.)
DCP_TT = RooRealVar("DCP_TT","#Delta^{CP}_{TT}",0.,-1.,1.)
DCP_withBlinding = RooUnblindPrecision("DCP_withBlinding","#Delta^{CP}","DCP_Blind",0.,blinding_scale,DCP,blindCat)
DCP_SS_withBlinding = RooUnblindPrecision("DCP_SS_withBlinding","#Delta^{CP}_{SS}","DCP_SS_Blind",0.,blinding_scale,DCP_SS,blindCat)
DCP_SV_withBlinding = RooUnblindPrecision("DCP_SV_withBlinding","#Delta^{CP}_{SV}","DCP_SV_Blind",0.,blinding_scale,DCP_SV,blindCat)
DCP_VS_withBlinding = RooUnblindPrecision("DCP_VS_withBlinding","#Delta^{CP}_{VS}","DCP_VS_Blind",0.,blinding_scale,DCP_VS,blindCat)
DCP_ST_withBlinding = RooUnblindPrecision("DCP_ST_withBlinding","#Delta^{CP}_{ST}","DCP_ST_Blind",0.,blinding_scale,DCP_ST,blindCat)
DCP_TS_withBlinding = RooUnblindPrecision("DCP_TS_withBlinding","#Delta^{CP}_{TS}","DCP_TS_Blind",0.,blinding_scale,DCP_TS,blindCat)
DCP_VV_withBlinding = RooUnblindPrecision("DCP_VV_withBlinding","#Delta^{CP}_{VV}","DCP_VV_Blind",0.,blinding_scale,DCP_VV,blindCat)
DCP_VT_withBlinding = RooUnblindPrecision("DCP_VT_withBlinding","#Delta^{CP}_{VT}","DCP_VT_Blind",0.,blinding_scale,DCP_VT,blindCat)
DCP_TV_withBlinding = RooUnblindPrecision("DCP_TV_withBlinding","#Delta^{CP}_{TV}","DCP_TV_Blind",0.,blinding_scale,DCP_TV,blindCat)
DCP_TT_withBlinding = RooUnblindPrecision("DCP_TT_withBlinding","#Delta^{CP}_{TT}","DCP_TT_Blind",0.,blinding_scale,DCP_TT,blindCat)

# Strong phases.
delta00 = RooRealVar("delta00","#delta^{SS}",7.37662e-01,-pi,pi)
delta01 = RooRealVar("delta01","#delta^{SV}",2.89533e+00,-pi,pi)
delta10 = RooRealVar("delta10","#delta^{VS}",-1.04654e+00,-pi,pi)
delta02 = RooRealVar("delta02","#delta^{ST}",5.64700e+00,0.,2.*pi)
delta20 = RooRealVar("delta20","#delta^{TS}",-0.15412530717958628,-pi,pi)
delta11par = RooRealVar("delta11par","#delta^{VV}_{#parallel}",-2.21036e+00,-pi,pi)
delta11perp = RooRealVar("delta11perp","#delta^{VV}_{#perp}",1.93028e+00,-pi,pi)
delta120 = RooRealVar("delta120","#delta^{VT}_{L}",4.60488e+00,0.,2.*pi)
delta12par = RooRealVar("delta12par","#delta^{VT}_{#parallel}",4.83277e+00,0.,2.*pi)
delta12perp = RooRealVar("delta12perp","#delta^{VT}_{#perp}",3.24728e+00,0.,2.*pi)
delta210 = RooRealVar("delta210","#delta^{TV}_{L}",2.22031e+00,0.,2.*pi)
delta21par = RooRealVar("delta21par","#delta^{TV}_{#parallel}",2.30346e+00,0.,2.*pi)
delta21perp = RooRealVar("delta21perp","#delta^{TV}_{#perp}",2.64967e-01,-pi,pi)
delta220 = RooRealVar("delta220","#delta^{TT}_{L}",2.82074e+00,0.,2.*pi)
delta22par = RooRealVar("delta22par","#delta^{TT}_{#parallel1}",5.00864e+00,0.,2.*pi)
delta22perp = RooRealVar("delta22perp","#delta^{TT}_{#perp1}",8.41216e-01,-pi,pi)
delta22par2 = RooRealVar("delta22par2","#delta^{TT}_{#parallel2}",1.45376e+00,-pi,pi)
delta22perp2 = RooRealVar("delta22perp2","#delta^{TT}_{#perp2}",5.38925e+00,0.,2.*pi)

# Weak phases.
phis = RooRealVar("phis","#phi_{s}",0.,-pi,pi)
dphi_SS = RooRealVar("dphi_SS","#Delta#phi_{SS}",0.,-pi,pi)
dphi_SV = RooRealVar("dphi_SV","#Delta#phi_{SV}",0.,-pi,pi)
dphi_VS = RooRealVar("dphi_VS","#Delta#phi_{VS}",0.,-pi,pi)
dphi_ST = RooRealVar("dphi_ST","#Delta#phi_{ST}",0.,-pi,pi)
dphi_TS = RooRealVar("dphi_TS","#Delta#phi_{TS}",0.,-pi,pi)
dphi_VT = RooRealVar("dphi_VT","#Delta#phi_{VT}",0.,-pi,pi)
dphi_TV = RooRealVar("dphi_TV","#Delta#phi_{TV}",0.,-pi,pi)
dphi_TT = RooRealVar("dphi_TT","#Delta#phi_{TT}",0.,-pi,pi)
phis_withBlinding = RooUnblindPrecision("phis_withBlinding","#phi_{s}","phis_Blind",0.,blinding_scale,phis,blindCat)
dphi_SS_withBlinding = RooUnblindPrecision("dphi_SS_withBlinding","#Delta#phi_{SS}","dphi_SS_Blind",0.,blinding_scale,dphi_SS,blindCat)
dphi_SV_withBlinding = RooUnblindPrecision("dphi_SV_withBlinding","#Delta#phi_{SV}","dphi_SV_Blind",0.,blinding_scale,dphi_SV,blindCat)
dphi_VS_withBlinding = RooUnblindPrecision("dphi_VS_withBlinding","#Delta#phi_{VS}","dphi_VS_Blind",0.,blinding_scale,dphi_VS,blindCat)
dphi_ST_withBlinding = RooUnblindPrecision("dphi_ST_withBlinding","#Delta#phi_{ST}","dphi_ST_Blind",0.,blinding_scale,dphi_ST,blindCat)
dphi_TS_withBlinding = RooUnblindPrecision("dphi_TS_withBlinding","#Delta#phi_{TS}","dphi_TS_Blind",0.,blinding_scale,dphi_TS,blindCat)
dphi_VT_withBlinding = RooUnblindPrecision("dphi_VT_withBlinding","#Delta#phi_{VT}","dphi_VT_Blind",0.,blinding_scale,dphi_VT,blindCat)
dphi_TV_withBlinding = RooUnblindPrecision("dphi_TV_withBlinding","#Delta#phi_{TV}","dphi_TV_Blind",0.,blinding_scale,dphi_TV,blindCat)
dphi_TT_withBlinding = RooUnblindPrecision("dphi_TT_withBlinding","#Delta#phi_{TT}","dphi_TT_Blind",0.,blinding_scale,dphi_TT,blindCat)

# Mixing parameters.
delta_m_Bs = RooRealVar("delta_m_Bs","#Delta m_{B_{s}^{0}}",17.761,17.651,17.871)
gamma_Bs = RooRealVar("gamma_Bs","#Gamma_{B_{s}^{0}}",0.6614,0.6459,0.6769)
delta_gamma_Bs = RooRealVar("delta_gamma_Bs","#Delta #Gamma_{B_{s}^{0}}",0.091,0.051,0.131)

# Gaussian constraints of the mixing parameters.
ctrt_delta_m_Bs = RooGaussian("ctrt_delta_m_Bs","ctrt_delta_m_Bs",delta_m_Bs,RooFit.RooConst(17.761),RooFit.RooConst(0.022))
ctrt_gamma_Bs = RooGaussian("ctrt_gamma_Bs","ctrt_gamma_Bs",gamma_Bs,RooFit.RooConst(0.6614),RooFit.RooConst(0.0031))
ctrt_delta_gamma_Bs = RooGaussian("ctrt_delta_gamma_Bs","ctrt_delta_gamma_Bs",delta_gamma_Bs,RooFit.RooConst(0.091),RooFit.RooConst(0.008))

# Calibration parameters.
etac_SSK = RooRealVar("etac_SSK","<#eta^{SSK}>",0.4638)
p0metac_SSK = RooRealVar("p0metac_SSK","p_{0}^{SSK}-<#eta^{SSK}>",0.005,-0.02,0.04)
Dp0half_SSK = RooRealVar("Dp0half_SSK","1/2 #Delta p_{0}^{SSK}",-0.0079,-0.05,0.)
p1_SSK = RooRealVar("p1_SSK","p_{1}^{SSK}",0.976,0.8,1.2)
Dp1half_SSK = RooRealVar("Dp1half_SSK","1/2 #Delta p_{1}^{SSK}",0.0035,-0.05,0.05)
etac_OS = RooRealVar("etac_OS","<#eta^{OS}>",0.4551)
p0metac_OS = RooRealVar("p0metac_OS","p_{0}^{OS}-<#eta^{OS}>",0.0062,-0.02,0.04)
Dp0half_OS = RooRealVar("Dp0half_OS","1/2 #Delta p_{0}^{OS}",0.007,0.,0.05)
p1_OS = RooRealVar("p1_OS","p_{1}^{OS}",0.982,0.8,1.2)
Dp1half_OS = RooRealVar("Dp1half_OS","1/2 #Delta p_{1}^{OS}",0.033,0.,0.1)
mS = RooRealVar("mS","mS",1425.)
gammaS = RooRealVar("gammaS","gammaS",270.)
mV = RooRealVar("mV","mV",900.)
gammaV = RooRealVar("gammaV","gammaV",47.4)
mT = RooRealVar("mT","mT",1432.4)
gammaT = RooRealVar("gammaT","gammaT",109.)
res_mass = RooRealVar("res_mass","res_mass",0.)

# Gaussian constraints of the calibration parameters.
ctrt_p0metac_SSK = RooGaussian("ctrt_p0metac_SSK","ctrt_p0metac_SSK",p0metac_SSK,RooFit.RooConst(0.005),RooFit.RooConst(0.005))
ctrt_Dp0half_SSK = RooGaussian("ctrt_Dp0half_SSK","ctrt_Dp0half_SSK",Dp0half_SSK,RooFit.RooConst(-0.0079),RooFit.RooConst(0.0007))
ctrt_p1_SSK = RooGaussian("ctrt_p1_SSK","ctrt_p1_SSK",p1_SSK,RooFit.RooConst(0.976),RooFit.RooConst(0.091))
ctrt_Dp1half_SSK = RooGaussian("ctrt_Dp1half_SSK","ctrt_Dp1half_SSK",Dp1half_SSK,RooFit.RooConst(0.0035),RooFit.RooConst(0.011))
ctrt_p0metac_OS = RooGaussian("ctrt_p0metac_OS","ctrt_p0metac_OS",p0metac_OS,RooFit.RooConst(0.0062),RooFit.RooConst(0.0044))
ctrt_Dp0half_OS = RooGaussian("ctrt_Dp0half_OS","ctrt_Dp0half_OS",Dp0half_OS,RooFit.RooConst(0.007),RooFit.RooConst(0.0006))
ctrt_p1_OS = RooGaussian("ctrt_p1_OS","ctrt_p1_OS",p1_OS,RooFit.RooConst(0.982),RooFit.RooConst(0.035))
ctrt_Dp1half_OS = RooGaussian("ctrt_Dp1half_OS","ctrt_Dp1half_OS",Dp1half_OS,RooFit.RooConst(0.033),RooFit.RooConst(0.006))

# Parameters of the conditional variable spectra.
tag_eff_SSK = RooRealVar("tag_eff_SSK","tag_eff_SSK",0.82453183441)
mu1_SSK = RooRealVar("mu1_SSK","mu1_SSK",6.21822e-01,0.,1.)
sigma1_SSK = RooRealVar("sigma1_SSK","sigma1_SSK",9.56659e-02,0.01,1.)
c_SSK = RooRealVar("c_SSK","c_SSK",9.78779e-01,0.5,1.)
mu2_SSK = RooRealVar("mu2_SSK","mu2_SSK",3.11438e-01,0.,1.)
sigma2_SSK = RooRealVar("sigma2_SSK","sigma2_SSK",6.65748e-02,0.01,1.)
tag_eff_OS = RooRealVar("tag_eff_OS","tag_eff_OS",0.489286888755)
mu1_OS = RooRealVar("mu1_OS","mu1_OS",4.29604e-01,0.2,0.6)
sigma1_OS = RooRealVar("sigma1_OS","sigma1_OS",9.78697e-02,0.01,0.2)
c_OS = RooRealVar("c_OS","c_OS",8.57782e-01,0.5,1.)
mu2_OS = RooRealVar("mu2_OS","mu2_OS",1.96149e-01,0.1,0.3)
sigma2_OS = RooRealVar("sigma2_OS","sigma2_OS",5.11082e-02,0.01,0.1)
gamma1_dt = RooRealVar("gamma1_dt","gamma1_dt",1.00397e+01,10,20)
beta1_dt = RooRealVar("beta1_dt","beta1_dt",3.50682e-03,0.0001,0.01)
c_dt = RooRealVar("c_dt","c_dt",9.99877e+00,0.01,10)
gamma2_dt = RooRealVar("gamma2_dt","gamma2_dt",1.43993e+01,1,50)
beta2_dt = RooRealVar("beta2_dt","beta2_dt",1.92568e-03,0.001,0.1)
mu1_SSK.setConstant(1)
sigma1_SSK.setConstant(1)
c_SSK.setConstant(1)
mu2_SSK.setConstant(1)
sigma2_SSK.setConstant(1)
mu1_OS.setConstant(1)
sigma1_OS.setConstant(1)
c_OS.setConstant(1)
mu2_OS.setConstant(1)
sigma2_OS.setConstant(1)
gamma1_dt.setConstant(1)
beta1_dt.setConstant(1)
c_dt.setConstant(1)
gamma2_dt.setConstant(1)
beta2_dt.setConstant(1)

# Parameters for studies on systematic uncertainties.
pw_mass_altmodel = RooRealVar("pw_mass_altmodel","pw_mass_altmodel",0)
f_1410_rel2_892 = RooRealVar("f_1410_rel2_892","f_1410_rel2_892",0.)
delta_1410_rel2_892 = RooRealVar("delta_1410_rel2_892","delta_1410_rel2_892",0.)
f_1680_rel2_892 = RooRealVar("f_1680_rel2_892","f_1680_rel2_892",0.)
delta_1680_rel2_892 = RooRealVar("delta_1680_rel2_892","delta_1680_rel2_892",0.)

# Integrals of the invariant mass dependent terms.
Im00 = RooRealVar("Im00","Im00", 1.)
Im01 = RooRealVar("Im01","Im01", 1.)
Im10 = RooRealVar("Im10","Im10", 1.)
Im02 = RooRealVar("Im02","Im02", 1.)
Im20 = RooRealVar("Im20","Im20", 1.)
Im11 = RooRealVar("Im11","Im11", 1.)
Im12 = RooRealVar("Im12","Im12", 1.)
Im21 = RooRealVar("Im21","Im21", 1.)
Im22 = RooRealVar("Im22","Im22", 1.)
Im00_narrowwin = RooRealVar("Im00_narrowwin","Im00_narrowwin", 1.)
Im01_narrowwin = RooRealVar("Im01_narrowwin","Im01_narrowwin", 1.)
Im10_narrowwin = RooRealVar("Im10_narrowwin","Im10_narrowwin", 1.)
Im02_narrowwin = RooRealVar("Im02_narrowwin","Im02_narrowwin", 1.)
Im20_narrowwin = RooRealVar("Im20_narrowwin","Im20_narrowwin", 1.)
Im11_narrowwin = RooRealVar("Im11_narrowwin","Im11_narrowwin", 1.)
Im12_narrowwin = RooRealVar("Im12_narrowwin","Im12_narrowwin", 1.)
Im21_narrowwin = RooRealVar("Im21_narrowwin","Im21_narrowwin", 1.)
Im22_narrowwin = RooRealVar("Im22_narrowwin","Im22_narrowwin", 1.)
Ih1Re = RooRealVar("Ih1Re","Ih1Re", 1.)
Ih2Re = RooRealVar("Ih2Re","Ih2Re", 1.)
Ih3Re = RooRealVar("Ih3Re","Ih3Re", 1.)
Ih4Re = RooRealVar("Ih4Re","Ih4Re", 1.)
Ih5Re = RooRealVar("Ih5Re","Ih5Re", 1.)
Ih6Re = RooRealVar("Ih6Re","Ih6Re", 1.)
Ih7Re = RooRealVar("Ih7Re","Ih7Re", 1.)
Ih8Re = RooRealVar("Ih8Re","Ih8Re", 1.)
Ih9Re = RooRealVar("Ih9Re","Ih9Re", 1.)
Ih10Re = RooRealVar("Ih10Re","Ih10Re", 1.)
Ih11Re = RooRealVar("Ih11Re","Ih11Re", 1.)
Ih12Re = RooRealVar("Ih12Re","Ih12Re", 1.)
Ih13Re = RooRealVar("Ih13Re","Ih13Re", 1.)
Ih14Re = RooRealVar("Ih14Re","Ih14Re", 1.)
Ih15Re = RooRealVar("Ih15Re","Ih15Re", 1.)
Ih16Re = RooRealVar("Ih16Re","Ih16Re", 1.)
Ih17Re = RooRealVar("Ih17Re","Ih17Re", 1.)
Ih18Re = RooRealVar("Ih18Re","Ih18Re", 1.)
Ih19Re = RooRealVar("Ih19Re","Ih19Re", 1.)
Ih20Re = RooRealVar("Ih20Re","Ih20Re", 1.)
Ih21Re = RooRealVar("Ih21Re","Ih21Re", 1.)
Ih22Re = RooRealVar("Ih22Re","Ih22Re", 1.)
Ih23Re = RooRealVar("Ih23Re","Ih23Re", 1.)
Ih24Re = RooRealVar("Ih24Re","Ih24Re", 1.)
Ih25Re = RooRealVar("Ih25Re","Ih25Re", 1.)
Ih26Re = RooRealVar("Ih26Re","Ih26Re", 1.)
Ih27Re = RooRealVar("Ih27Re","Ih27Re", 1.)
Ih28Re = RooRealVar("Ih28Re","Ih28Re", 1.)
Ih29Re = RooRealVar("Ih29Re","Ih29Re", 1.)
Ih30Re = RooRealVar("Ih30Re","Ih30Re", 1.)
Ih1Im = RooRealVar("Ih1Im","Ih1Im", 1.)
Ih2Im = RooRealVar("Ih2Im","Ih2Im", 1.)
Ih3Im = RooRealVar("Ih3Im","Ih3Im", 1.)
Ih4Im = RooRealVar("Ih4Im","Ih4Im", 1.)
Ih5Im = RooRealVar("Ih5Im","Ih5Im", 1.)
Ih6Im = RooRealVar("Ih6Im","Ih6Im", 1.)
Ih7Im = RooRealVar("Ih7Im","Ih7Im", 1.)
Ih8Im = RooRealVar("Ih8Im","Ih8Im", 1.)
Ih9Im = RooRealVar("Ih9Im","Ih9Im", 1.)
Ih10Im = RooRealVar("Ih10Im","Ih10Im", 1.)
Ih11Im = RooRealVar("Ih11Im","Ih11Im", 1.)
Ih12Im = RooRealVar("Ih12Im","Ih12Im", 1.)
Ih13Im = RooRealVar("Ih13Im","Ih13Im", 1.)
Ih14Im = RooRealVar("Ih14Im","Ih14Im", 1.)
Ih15Im = RooRealVar("Ih15Im","Ih15Im", 1.)
Ih16Im = RooRealVar("Ih16Im","Ih16Im", 1.)
Ih17Im = RooRealVar("Ih17Im","Ih17Im", 1.)
Ih18Im = RooRealVar("Ih18Im","Ih18Im", 1.)
Ih19Im = RooRealVar("Ih19Im","Ih19Im", 1.)
Ih20Im = RooRealVar("Ih20Im","Ih20Im", 1.)
Ih21Im = RooRealVar("Ih21Im","Ih21Im", 1.)

# Integrals of the angular terms.
If1 = RooRealVar("If1","If1", 1.)
If2 = RooRealVar("If2","If2", 1.)
If3 = RooRealVar("If3","If3", 1.)
If4 = RooRealVar("If4","If4", 1.)
If5 = RooRealVar("If5","If5", 1.)
If6 = RooRealVar("If6","If6", 1.)
If7 = RooRealVar("If7","If7", 1.)
If8 = RooRealVar("If8","If8", 1.)
If9 = RooRealVar("If9","If9", 1.)
If10 = RooRealVar("If10","If10", 1.)
If11 = RooRealVar("If11","If11", 1.)
If12 = RooRealVar("If12","If12", 1.)
If13 = RooRealVar("If13","If13", 1.)
If14 = RooRealVar("If14","If14", 1.)
If15 = RooRealVar("If15","If15", 1.)
If16 = RooRealVar("If16","If16", 1.)
If17 = RooRealVar("If17","If17", 1.)
If18 = RooRealVar("If18","If18", 1.)

# Integrals of the time dependent terms.
IT_cosh = RooRealVar("IT_cosh","IT_cosh", 1.)
IT_sinh = RooRealVar("IT_sinh","IT_sinh", 1.)
IT_cos = RooRealVar("IT_cos","IT_cos", 1.)
IT_sin = RooRealVar("IT_sin","IT_sin", 1.)


# ################################################################
# M O R E   V A R I A B L E S
# ################################################################

# Auxiliar variables.
zero = RooRealVar("zero","zero",0.)
one = RooRealVar("one","one",1.)

# Four body invariant mass.
mKpKp = RooRealVar(mKpiKpi_name,"M(K^{+}#pi^{-}K^{-}#pi^{+}) ",5365-450,5365+450,"MeV/c^{2}")

# s-Weights.
weight = RooRealVar(weight_name,"weight",-1.,1.,"")

# Frames.
frame_m1 = mKp1.frame(RooFit.Title("m1"))
frame_m2 = mKp2.frame(RooFit.Title("m2"))
frame_m1_narrowwin = mKp1_narrowwin.frame(RooFit.Title("m1"))
frame_m2_narrowwin = mKp2_narrowwin.frame(RooFit.Title("m2"))
frame_cos1 = cos1.frame(RooFit.Title("cos1"))
frame_cos2 = cos2.frame(RooFit.Title("cos2"))
frame_phi = phi.frame(RooFit.Title("phi"))
frame_t = t.frame(RooFit.Title("t"))
frame_terr = terror.frame(RooFit.Title("terr"))
frame_eta_SSK = etamistag_SSK.frame(RooFit.Title("eta_SSK"))
frame_eta_OS = etamistag_OS.frame(RooFit.Title("eta_OS"))


# ################################################################
# L I S T S   O F   A R G U M E N T S
# ################################################################

options = [wide_window_opt,year_opt,alt_fit,option,inftres,flatacc,nwacc,A_j1,A_j2,A_h,A_j1p,A_j2p,A_hp,qcomp]

observables = [decision_SSK,decision_OS,etamistag_SSK,etamistag_OS,mKp1,mKp2,cos1,cos2,phi,t,terror]
observables_narrowwin = [decision_SSK,decision_OS,etamistag_SSK,etamistag_OS,mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,terror]

wave_fractions = [f_VV,f_Swave,f_SS,f_VTTV,f_TT,D_SVVS,D_VTTV,D_STTS,fL_VV,xpar_VV,fL_VT,xpar_VT,fL_TV,xpar_TV,\
fL_TT,xpar1_TT,xperp1_TT,xpar2_TT]

dirCP_asyms = [DCP_SS_withBlinding,DCP_SV_withBlinding,DCP_VS_withBlinding,DCP_ST_withBlinding,DCP_TS_withBlinding,\
DCP_VV_withBlinding,DCP_VT_withBlinding,DCP_TV_withBlinding,DCP_TT_withBlinding]
dirCP_asyms_unblinded = [DCP_SS,DCP_SV,DCP_VS,DCP_ST,DCP_TS,DCP_VV,DCP_VT,DCP_TV,DCP_TT]
dirCP_asyms_narrowwin = [DCP_SS_withBlinding,DCP_SV_withBlinding,DCP_VS_withBlinding,zero,zero,DCP_VV_withBlinding,zero,zero,zero]
dirCP_asyms_narrowwin_unblinded = [DCP_SS,DCP_SV,DCP_VS,zero,zero,DCP_VV,zero,zero,zero]
dirCP_asyms_noCP = [zero,zero,zero,zero,zero,zero,zero,zero,zero]
dirCP_asyms_sameCP = [DCP_withBlinding,DCP_withBlinding,DCP_withBlinding,DCP_withBlinding,DCP_withBlinding,DCP_withBlinding,\
DCP_withBlinding,DCP_withBlinding,DCP_withBlinding]
dirCP_asyms_sameCP_unblinded = [DCP,DCP,DCP,DCP,DCP,DCP,DCP,DCP,DCP]
dirCP_asyms_sameCP_narrowwin = [DCP_withBlinding,DCP_withBlinding,DCP_withBlinding,zero,zero,DCP_withBlinding,zero,zero,zero]
dirCP_asyms_sameCP_narrowwin_unblinded = [DCP,DCP,DCP,zero,zero,DCP,zero,zero,zero]

strong_phases = [delta00,delta01,delta10,delta02,delta20,delta11par,delta11perp,delta120,delta12par,delta12perp,\
delta210,delta21par,delta21perp,delta220,delta22par,delta22perp,delta22par2,delta22perp2]

weak_phases = [phis_withBlinding,dphi_SS_withBlinding,dphi_SV_withBlinding,dphi_VS_withBlinding,dphi_ST_withBlinding,\
dphi_TS_withBlinding,dphi_VT_withBlinding,dphi_TV_withBlinding,dphi_TT_withBlinding]
weak_phases_unblinded = [phis,dphi_SS,dphi_SV,dphi_VS,dphi_ST,dphi_TS,dphi_VT,dphi_TV,dphi_TT]
weak_phases_narrowwin = [phis_withBlinding,dphi_SS_withBlinding,dphi_SV_withBlinding,dphi_VS_withBlinding,zero,zero,zero,zero,zero]
weak_phases_narrowwin_unblinded = [phis,dphi_SS,dphi_SV,dphi_VS,zero,zero,zero,zero,zero]
weak_phases_noCP = [zero,zero,zero,zero,zero,zero,zero,zero,zero]
weak_phases_sameCP = [phis_withBlinding,zero,zero,zero,zero,zero,zero,zero,zero]
weak_phases_sameCP_unblinded = [phis,zero,zero,zero,zero,zero,zero,zero,zero]

mixing_params = [delta_m_Bs,gamma_Bs,delta_gamma_Bs]

calib_params = [p0metac_SSK,p0metac_OS,Dp0half_SSK,Dp0half_OS,p1_SSK,p1_OS,Dp1half_SSK,Dp1half_OS,etac_SSK,etac_OS,mV,mS,mT,\
gammaV,gammaS,gammaT,res_mass]
calib_params_aux = [one,one,one,one,one,one,one,one,one,one,mV,mS,mT,gammaV,gammaS,gammaT,res_mass]

cond_distr_params = [tag_eff_SSK,mu1_SSK,sigma1_SSK,c_SSK,mu2_SSK,sigma2_SSK,tag_eff_OS,mu1_OS,sigma1_OS,c_OS,mu2_OS,sigma2_OS,gamma1_dt,beta1_dt,c_dt,gamma2_dt,beta2_dt]

sys_studies = [pw_mass_altmodel,f_1410_rel2_892,delta_1410_rel2_892,f_1680_rel2_892,delta_1680_rel2_892]

mass_integrals = [Im00,Im01,Im10,Im02,Im20,Im11,Im12,Im21,Im22,Ih1Re,Ih2Re,Ih3Re,Ih4Re,Ih5Re,Ih6Re,Ih7Re,Ih8Re,Ih9Re,\
Ih10Re,Ih11Re,Ih12Re,Ih13Re,Ih14Re,Ih15Re,Ih16Re,Ih17Re,Ih18Re,Ih19Re,Ih20Re,Ih21Re,Ih22Re,Ih23Re,Ih24Re,Ih25Re,Ih26Re,Ih27Re,Ih28Re,Ih29Re,Ih30Re,Ih1Im,Ih2Im,Ih3Im,Ih4Im,Ih5Im,\
Ih6Im,Ih7Im,Ih8Im,Ih9Im,Ih10Im,Ih11Im,Ih12Im,Ih13Im,Ih14Im,Ih15Im,Ih16Im,Ih17Im,Ih18Im,Ih19Im,Ih20Im,Ih21Im]
mass_integrals_narrowwin = [Im00_narrowwin,Im01_narrowwin,Im10_narrowwin,Im02_narrowwin,Im20_narrowwin,Im11_narrowwin,Im12_narrowwin,Im21_narrowwin,Im22_narrowwin,Ih1Re,Ih2Re,Ih3Re,Ih4Re,Ih5Re,Ih6Re,Ih7Re,Ih8Re,Ih9Re,\
Ih10Re,Ih11Re,Ih12Re,Ih13Re,Ih14Re,Ih15Re,Ih16Re,Ih17Re,Ih18Re,Ih19Re,Ih20Re,Ih21Re,Ih22Re,Ih23Re,Ih24Re,Ih25Re,Ih26Re,Ih27Re,Ih28Re,Ih29Re,Ih30Re,Ih1Im,Ih2Im,Ih3Im,Ih4Im,Ih5Im,\
Ih6Im,Ih7Im,Ih8Im,Ih9Im,Ih10Im,Ih11Im,Ih12Im,Ih13Im,Ih14Im,Ih15Im,Ih16Im,Ih17Im,Ih18Im,Ih19Im,Ih20Im,Ih21Im]

ang_integrals = [If1,If2,If3,If4,If5,If6,If7,If8,If9,If10,If11,If12,If13,If14,If15,If16,If17,If18]

time_integrals = [IT_cosh,IT_sinh,IT_cos,IT_sin]

options_list = RooArgList()
observables_list = RooArgList()
wave_fractions_list = RooArgList()
dirCP_asyms_list = RooArgList()
dirCP_asyms_unblinded_list = RooArgList()
strong_phases_list = RooArgList()
weak_phases_list = RooArgList()
weak_phases_unblinded_list = RooArgList()
mixing_params_list = RooArgList()
calib_params_list = RooArgList()
cond_distr_params_list = RooArgList()
sys_studies_list = RooArgList()
mass_integrals_list = RooArgList()
ang_integrals_list = RooArgList()
time_integrals_list = RooArgList()

options_list_aux = RooArgList()
observables_list_aux = RooArgList()
observables_list_narrowwin_aux = RooArgList()
wave_fractions_list_aux = RooArgList()
dirCP_asyms_list_aux = RooArgList()
strong_phases_list_aux = RooArgList()
weak_phases_list_aux = RooArgList()
mixing_params_list_aux = RooArgList()
calib_params_list_aux = RooArgList()
cond_distr_params_list_aux = RooArgList()
sys_studies_list_aux = RooArgList()
mass_integrals_list_aux = RooArgList()
mass_integrals_list_narrowwin_aux = RooArgList()
ang_integrals_list_aux = RooArgList()
time_integrals_list_aux = RooArgList()

for argument in mass_integrals: mass_integrals_list.add(argument)
for argument in ang_integrals: ang_integrals_list.add(argument)
for argument in time_integrals: time_integrals_list.add(argument)
