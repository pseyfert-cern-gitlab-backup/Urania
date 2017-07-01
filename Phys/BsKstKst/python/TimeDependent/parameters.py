import ROOT, os, sys, time, random
from ROOT import gROOT, kBlue, kRed, kOrange, kGreen, kMagenta, kWhite, kGray, kTRUE, kFALSE
from math import pi, sqrt
from array import array
from TResCalib import *


# Environment locations.
currentpath = os.getcwd()
if '/afs/cern.ch/user/' in currentpath:
	NTUPLE_PATH = "/afs/cern.ch/work/j/jugarcia/public/FastNTuples/Bs2KpiKpi/"
	PYTHON_PATH = "/afs/cern.ch/user/j/jugarcia/cmtuser/Bs2KpiKpi/python/TimeDependent/"
	SOURCE_PATH = "/afs/cern.ch/user/j/jugarcia/cmtuser/Bs2KpiKpi/src/TimeDependent/"
	print '\nINFO: lxplus environment loaded.'
elif '/Users/jugarcia/' in currentpath:
	NTUPLE_PATH = "/Users/jugarcia/Desktop/Software/Bs2KpiKpi/lxplus/fast_ntuples/"
	PYTHON_PATH = '/Users/jugarcia/Desktop/Software/Bs2KpiKpi/lxplus/python/TimeDependent/'
	SOURCE_PATH = '/Users/jugarcia/Desktop/Software/Bs2KpiKpi/lxplus/src/TimeDependent/'
	print "\nINFO: Local environment loaded."
elif '/home3/' in currentpath:
	NTUPLE_PATH = "/scratch27/julian.garcia/Bs2KpiKpi/fast_ntuples/"
	PYTHON_PATH = '/home3/julian.garcia/UraniaDev_v6r2/Phys/BsKstKst/python/TimeDependent/'
	SOURCE_PATH = '/home3/julian.garcia/UraniaDev_v6r2/Phys/BsKstKst/src/TimeDependent/'
	print "\nINFO: USC node environment loaded."
else:
	NTUPLE_PATH = ""
	PYTHON_PATH = ""
	SOURCE_PATH = ""

# Blinding.
blindCat = ROOT.RooCategory("blindCat","blindCat")
blindCat.defineType("unblind",0)
blindCat.defineType("blind",1)
blindCat.setConstant(1)
blinding_scale = 20
blinding_strings = {}


# ################################################################
# V A R I A B L E S   O F   T H E   P D F
# ################################################################

# Names of the variables in the ntuples.
mKpiKpi_name = "B_s0_DTF_B_s0_M"
weight_name = "sweight"
m1_name = "B_s0_DTF_KST1_M"
m2_name = "B_s0_DTF_KST2_M"
cos1_name = "B_s0_DTF_B_s0_CosTheta1"
cos2_name = "B_s0_DTF_B_s0_CosTheta2"
phi_name = "B_s0_DTF_B_s0_PHI_TRY4"
t_name = "B_s0_DTF_TAU"
terror_name = "B_s0_DTF_TAUERR"
dec_SSK_name = "B_s0_SS_nnetKaon_DEC"
dec_OS_name = "B_s0_TAGDECISION_OS"
eta_SSK_name = "B_s0_SS_nnetKaon_PROB"
eta_OS_name = "B_s0_TAGOMEGA_OS"
L0TISline_name = "B_s0_L0Global_TIS"
L0TOSline_name = "B_s0_L0HadronDecision_TOS"

# Options.
wide_window_opt = ROOT.RooRealVar("wide_window_opt","wide_window_opt",1.)
year_opt = ROOT.RooRealVar("year_opt","year_opt",1.)
trig_opt = ROOT.RooRealVar("trig_opt","trig_opt",1.)
alt_fit = ROOT.RooRealVar("alt_fit","alt_fit",0.)
option = ROOT.RooRealVar("option","option",0.)
inftres = ROOT.RooRealVar("inftres","inftres",0)
acctype = ROOT.RooRealVar("acctype","acctype",0)
A_j1 = ROOT.RooRealVar("A_j1","A_j1",9)
A_j2 = ROOT.RooRealVar("A_j2","A_j2",9)
A_h = ROOT.RooRealVar("A_h","A_h",9)	
A_j1p = ROOT.RooRealVar("A_j1p","A_j1p",9)
A_j2p = ROOT.RooRealVar("A_j2p","A_j2p",9)
A_hp = ROOT.RooRealVar("A_hp","A_hp",9)
qcomp = ROOT.RooRealVar("qcomp","qcomp",9)

# Observables.
mHlimit = 1600
mKp1 = ROOT.RooRealVar(m1_name,"M(K^{+}#pi^{-}) ", 750., mHlimit,"MeV/c^{2}")
mKp2 = ROOT.RooRealVar(m2_name,"M(K^{-}#pi^{+}) ", 750., mHlimit,"MeV/c^{2}")
mKp1_narrowwin = ROOT.RooRealVar(m1_name,"M(K^{+}#pi^{-}) ",900.-150.,900.+150.,"MeV/c^{2}")
mKp2_narrowwin = ROOT.RooRealVar(m2_name,"M(K^{-}#pi^{+}) ",900.-150.,900.+150.,"MeV/c^{2}")
cos1 = ROOT.RooRealVar(cos1_name,"cos(#theta_{1})", -1., 1.,"")
cos2 = ROOT.RooRealVar(cos2_name,"cos(#theta_{2})", -1., 1.,"")
phi = ROOT.RooRealVar(phi_name,"#varphi",0.,2.*pi,"rad")
t = ROOT.RooRealVar(t_name,"t",0.,12.,"ps")
terror = ROOT.RooRealVar(terror_name,"#delta t",0.,0.1,"ps")
decision_SSK = ROOT.RooCategory(dec_SSK_name,"q^{SSK}")
decision_SSK.defineType("Bsbartagged",-1)
decision_SSK.defineType("untagged",0)
decision_SSK.defineType("Bstagged",1)
decision_OS = ROOT.RooCategory(dec_OS_name,"q^{OS}")
decision_OS.defineType("Bsbartagged",-1)
decision_OS.defineType("untagged",0)
decision_OS.defineType("Bstagged",1)
etamistag_SSK = ROOT.RooRealVar(eta_SSK_name,"#eta^{SSK}",0.,0.5)
etamistag_OS = ROOT.RooRealVar(eta_OS_name,"#eta^{OS}",0.,0.5)
FullArgSet = ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,terror)
FullArgSet.add(decision_SSK)
FullArgSet.add(decision_OS)
FullArgSet.add(etamistag_SSK)
FullArgSet.add(etamistag_OS)

# Real part of the amplitudes.
reA00 = ROOT.RooRealVar("reA00","Re(A^{SS})",0.,-10.,10.)
reA01 = ROOT.RooRealVar("reA01","Re(A^{SV})",0.,-10.,10.)
reA10 = ROOT.RooRealVar("reA10","Re(A^{VS})",0.,-10.,10.)
reA02 = ROOT.RooRealVar("reA02","Re(A^{ST})",0.,-10.,10.)
reA20 = ROOT.RooRealVar("reA20","Re(A^{TS})",0.,-10.,10.)
reA110 = ROOT.RooRealVar("reA110","Re(A^{VV}_{L})",1.) # Fixed.
reA11par = ROOT.RooRealVar("reA11par","Re(A^{VV}_{#parallel})",0.,-10.,10.)
reA11perp = ROOT.RooRealVar("reA11perp","Re(A^{VV}_{#perp})",0.,-10.,10.)
reA120 = ROOT.RooRealVar("reA120","Re(A^{VT}_{L})",0.,-10.,10.)
reA12par = ROOT.RooRealVar("reA12par","Re(A^{VT}_{#parallel})",0.,-10.,10.)
reA12perp = ROOT.RooRealVar("reA12perp","Re(A^{VT}_{#perp})",0.,-10.,10.)
reA210 = ROOT.RooRealVar("reA210","Re(A^{TV}_{L})",0.,-10.,10.)
reA21par = ROOT.RooRealVar("reA21par","Re(A^{TV}_{#parallel})",0.,-10.,10.)
reA21perp = ROOT.RooRealVar("reA21perp","Re(A^{TV}_{#perp})",0.,-10.,10.)
reA220 = ROOT.RooRealVar("reA220","Re(A^{TT}_{L})",0.,-10.,10.)
reA22par = ROOT.RooRealVar("reA22par","Re(A^{TT}_{#parallel1})",0.,-10.,10.)
reA22perp = ROOT.RooRealVar("reA22perp","Re(A^{TT}_{#perp1})",0.,-10.,10.)
reA22par2 = ROOT.RooRealVar("reA22par2","Re(A^{TT}_{#parallel2})",0.,-10.,10.)
reA22perp2 = ROOT.RooRealVar("reA22perp2","Re(A^{TT}_{#perp2})",0.,-10.,10.)

# Direct CP violation asymmetries.
DCP = ROOT.RooRealVar("DCP","#Delta^{CP}",0.,-1.,1.)
DCP_SS = ROOT.RooRealVar("DCP_SS","#Delta^{CP}_{SS}",0.,-1.,1.)
DCP_SV = ROOT.RooRealVar("DCP_SV","#Delta^{CP}_{SV}",0.,-1.,1.)
DCP_VS = ROOT.RooRealVar("DCP_VS","#Delta^{CP}_{VS}",0.,-1.,1.)
DCP_ST = ROOT.RooRealVar("DCP_ST","#Delta^{CP}_{ST}",0.,-1.,1.)
DCP_TS = ROOT.RooRealVar("DCP_TS","#Delta^{CP}_{TS}",0.,-1.,1.)
DCP_VT = ROOT.RooRealVar("DCP_VT","#Delta^{CP}_{VT}",0.,-1.,1.)
DCP_TV = ROOT.RooRealVar("DCP_TV","#Delta^{CP}_{TV}",0.,-1.,1.)
DCP_TT = ROOT.RooRealVar("DCP_TT","#Delta^{CP}_{TT}",0.,-1.,1.)
DCP_withBlinding = ROOT.RooUnblindPrecision("DCP_withBlinding","#Delta^{CP}","DCP_Blind",0.,blinding_scale,DCP,blindCat)
DCP_SS_withBlinding = ROOT.RooUnblindPrecision("DCP_SS_withBlinding","#Delta^{CP}_{SS}","DCP_SS_Blind",0.,blinding_scale,DCP_SS,blindCat)
DCP_SV_withBlinding = ROOT.RooUnblindPrecision("DCP_SV_withBlinding","#Delta^{CP}_{SV}","DCP_SV_Blind",0.,blinding_scale,DCP_SV,blindCat)
DCP_VS_withBlinding = ROOT.RooUnblindPrecision("DCP_VS_withBlinding","#Delta^{CP}_{VS}","DCP_VS_Blind",0.,blinding_scale,DCP_VS,blindCat)
DCP_ST_withBlinding = ROOT.RooUnblindPrecision("DCP_ST_withBlinding","#Delta^{CP}_{ST}","DCP_ST_Blind",0.,blinding_scale,DCP_ST,blindCat)
DCP_TS_withBlinding = ROOT.RooUnblindPrecision("DCP_TS_withBlinding","#Delta^{CP}_{TS}","DCP_TS_Blind",0.,blinding_scale,DCP_TS,blindCat)
DCP_VT_withBlinding = ROOT.RooUnblindPrecision("DCP_VT_withBlinding","#Delta^{CP}_{VT}","DCP_VT_Blind",0.,blinding_scale,DCP_VT,blindCat)
DCP_TV_withBlinding = ROOT.RooUnblindPrecision("DCP_TV_withBlinding","#Delta^{CP}_{TV}","DCP_TV_Blind",0.,blinding_scale,DCP_TV,blindCat)
DCP_TT_withBlinding = ROOT.RooUnblindPrecision("DCP_TT_withBlinding","#Delta^{CP}_{TT}","DCP_TT_Blind",0.,blinding_scale,DCP_TT,blindCat)

# Imaginary part of the amplitudes.
imA00 = ROOT.RooRealVar("imA00","Im(A^{SS})",0.,-10.,10.)
imA01 = ROOT.RooRealVar("imA01","Im(A^{SV})",0.,-10.,10.)
imA10 = ROOT.RooRealVar("imA10","Im(A^{VS})",0.,-10.,10.)
imA02 = ROOT.RooRealVar("imA02","Im(A^{ST})",0.,-10.,10.)
imA20 = ROOT.RooRealVar("imA20","Im(A^{TS})",0.,-10.,10.)
imA110 = ROOT.RooRealVar("imA110","Im(A^{VV}_{L})",0.) # Fixed.
imA11par = ROOT.RooRealVar("imA11par","Im(A^{VV}_{#parallel})",0.,-10.,10.)
imA11perp = ROOT.RooRealVar("imA11perp","Im(A^{VV}_{#perp})",0.,-10.,10.)
imA120 = ROOT.RooRealVar("imA120","Im(A^{VT}_{L})",0.,-10.,10.)
imA12par = ROOT.RooRealVar("imA12par","Im(A^{VT}_{#parallel})",0.,-10.,10.)
imA12perp = ROOT.RooRealVar("imA12perp","Im(A^{VT}_{#perp})",0.,-10.,10.)
imA210 = ROOT.RooRealVar("imA210","Im(A^{TV}_{L})",0.,-10.,10.)
imA21par = ROOT.RooRealVar("imA21par","Im(A^{TV}_{#parallel})",0.,-10.,10.)
imA21perp = ROOT.RooRealVar("imA21perp","Im(A^{TV}_{#perp})",0.,-10.,10.)
imA220 = ROOT.RooRealVar("imA220","Im(A^{TT}_{L})",0.,-10.,10.)
imA22par = ROOT.RooRealVar("imA22par","Im(A^{TT}_{#parallel1})",0.,-10.,10.)
imA22perp = ROOT.RooRealVar("imA22perp","Im(A^{TT}_{#perp1})",0.,-10.,10.)
imA22par2 = ROOT.RooRealVar("imA22par2","Im(A^{TT}_{#parallel2})",0.,-10.,10.)
imA22perp2 = ROOT.RooRealVar("imA22perp2","Im(A^{TT}_{#perp2})",0.,-10.,10.)

# Weak phases.
phis = ROOT.RooRealVar("phis","#phi_{s}",0.,-pi,pi)
dphi_SS = ROOT.RooRealVar("dphi_SS","#Delta#phi_{SS}",0.,-pi,pi)
dphi_SV = ROOT.RooRealVar("dphi_SV","#Delta#phi_{SV}",0.,-pi,pi)
dphi_VS = ROOT.RooRealVar("dphi_VS","#Delta#phi_{VS}",0.,-pi,pi)
dphi_ST = ROOT.RooRealVar("dphi_ST","#Delta#phi_{ST}",0.,-pi,pi)
dphi_TS = ROOT.RooRealVar("dphi_TS","#Delta#phi_{TS}",0.,-pi,pi)
dphi_VT = ROOT.RooRealVar("dphi_VT","#Delta#phi_{VT}",0.,-pi,pi)
dphi_TV = ROOT.RooRealVar("dphi_TV","#Delta#phi_{TV}",0.,-pi,pi)
dphi_TT = ROOT.RooRealVar("dphi_TT","#Delta#phi_{TT}",0.,-pi,pi)
phis_withBlinding = ROOT.RooUnblindPrecision("phis_withBlinding","#phi_{s}","phis_Blind",0.,blinding_scale,phis,blindCat)
dphi_SS_withBlinding = ROOT.RooUnblindPrecision("dphi_SS_withBlinding","#Delta#phi_{SS}","dphi_SS_Blind",0.,blinding_scale,dphi_SS,blindCat)
dphi_SV_withBlinding = ROOT.RooUnblindPrecision("dphi_SV_withBlinding","#Delta#phi_{SV}","dphi_SV_Blind",0.,blinding_scale,dphi_SV,blindCat)
dphi_VS_withBlinding = ROOT.RooUnblindPrecision("dphi_VS_withBlinding","#Delta#phi_{VS}","dphi_VS_Blind",0.,blinding_scale,dphi_VS,blindCat)
dphi_ST_withBlinding = ROOT.RooUnblindPrecision("dphi_ST_withBlinding","#Delta#phi_{ST}","dphi_ST_Blind",0.,blinding_scale,dphi_ST,blindCat)
dphi_TS_withBlinding = ROOT.RooUnblindPrecision("dphi_TS_withBlinding","#Delta#phi_{TS}","dphi_TS_Blind",0.,blinding_scale,dphi_TS,blindCat)
dphi_VT_withBlinding = ROOT.RooUnblindPrecision("dphi_VT_withBlinding","#Delta#phi_{VT}","dphi_VT_Blind",0.,blinding_scale,dphi_VT,blindCat)
dphi_TV_withBlinding = ROOT.RooUnblindPrecision("dphi_TV_withBlinding","#Delta#phi_{TV}","dphi_TV_Blind",0.,blinding_scale,dphi_TV,blindCat)
dphi_TT_withBlinding = ROOT.RooUnblindPrecision("dphi_TT_withBlinding","#Delta#phi_{TT}","dphi_TT_Blind",0.,blinding_scale,dphi_TT,blindCat)

# Wave and polarisation fractions.
sqmodA00 = ROOT.RooFormulaVar("sqmodA00","sqmodA00","reA00*reA00+imA00*imA00",ROOT.RooArgList(reA00,imA00))
sqmodA01 = ROOT.RooFormulaVar("sqmodA01","sqmodA01","reA01*reA01+imA01*imA01",ROOT.RooArgList(reA01,imA01))
sqmodA10 = ROOT.RooFormulaVar("sqmodA10","sqmodA10","reA10*reA10+imA10*imA10",ROOT.RooArgList(reA10,imA10))
sqmodA02 = ROOT.RooFormulaVar("sqmodA02","sqmodA02","reA02*reA02+imA02*imA02",ROOT.RooArgList(reA02,imA02))
sqmodA20 = ROOT.RooFormulaVar("sqmodA20","sqmodA20","reA20*reA20+imA20*imA20",ROOT.RooArgList(reA20,imA20))
sqmodA110 = ROOT.RooFormulaVar("sqmodA110","sqmodA110","reA110*reA110+imA110*imA110",ROOT.RooArgList(reA110,imA110))
sqmodA11par = ROOT.RooFormulaVar("sqmodA11par","sqmodA11par","reA11par*reA11par+imA11par*imA11par",ROOT.RooArgList(reA11par,imA11par))
sqmodA11perp = ROOT.RooFormulaVar("sqmodA11perp","sqmodA11perp","reA11perp*reA11perp+imA11perp*imA11perp",ROOT.RooArgList(reA11perp,imA11perp))
sqmodA120 = ROOT.RooFormulaVar("sqmodA120","sqmodA120","reA120*reA120+imA120*imA120",ROOT.RooArgList(reA120,imA120))
sqmodA12par = ROOT.RooFormulaVar("sqmodA12par","sqmodA12par","reA12par*reA12par+imA12par*imA12par",ROOT.RooArgList(reA12par,imA12par))
sqmodA12perp = ROOT.RooFormulaVar("sqmodA12perp","sqmodA12perp","reA12perp*reA12perp+imA12perp*imA12perp",ROOT.RooArgList(reA12perp,imA12perp))
sqmodA210 = ROOT.RooFormulaVar("sqmodA210","sqmodA210","reA210*reA210+imA210*imA210",ROOT.RooArgList(reA210,imA210))
sqmodA21par = ROOT.RooFormulaVar("sqmodA21par","sqmodA21par","reA21par*reA21par+imA21par*imA21par",ROOT.RooArgList(reA21par,imA21par))
sqmodA21perp = ROOT.RooFormulaVar("sqmodA21perp","sqmodA21perp","reA21perp*reA21perp+imA21perp*imA21perp",ROOT.RooArgList(reA21perp,imA21perp))
sqmodA220 = ROOT.RooFormulaVar("sqmodA220","sqmodA220","reA220*reA220+imA220*imA220",ROOT.RooArgList(reA220,imA220))
sqmodA22par = ROOT.RooFormulaVar("sqmodA22par","sqmodA22par","reA22par*reA22par+imA22par*imA22par",ROOT.RooArgList(reA22par,imA22par))
sqmodA22perp = ROOT.RooFormulaVar("sqmodA22perp","sqmodA22perp","reA22perp*reA22perp+imA22perp*imA22perp",ROOT.RooArgList(reA22perp,imA22perp))
sqmodA22par2 = ROOT.RooFormulaVar("sqmodA22par2","sqmodA22par2","reA22par2*reA22par2+imA22par2*imA22par2",ROOT.RooArgList(reA22par2,imA22par2))
sqmodA22perp2 = ROOT.RooFormulaVar("sqmodA22perp2","sqmodA22perp2","reA22perp2*reA22perp2+imA22perp2*imA22perp2",ROOT.RooArgList(reA22perp2,imA22perp2))
sqmodA11 = ROOT.RooFormulaVar("sqmodA11","sqmodA11","sqmodA110+sqmodA11par+sqmodA11perp",ROOT.RooArgList(sqmodA110,sqmodA11par,sqmodA11perp))
sqmodA12 = ROOT.RooFormulaVar("sqmodA12","sqmodA12","sqmodA120+sqmodA12par+sqmodA12perp",ROOT.RooArgList(sqmodA120,sqmodA12par,sqmodA12perp))
sqmodA21 = ROOT.RooFormulaVar("sqmodA21","sqmodA21","sqmodA210+sqmodA21par+sqmodA21perp",ROOT.RooArgList(sqmodA210,sqmodA21par,sqmodA21perp))
sqmodA22 = ROOT.RooFormulaVar("sqmodA22","sqmodA22","sqmodA220+sqmodA22par+sqmodA22perp+sqmodA22par2+sqmodA22perp2",ROOT.RooArgList(sqmodA220,sqmodA22par,sqmodA22perp,sqmodA22par2,sqmodA22perp2))
sqmodA = ROOT.RooFormulaVar("sqmodA","sqmodA","sqmodA00+sqmodA01+sqmodA10+sqmodA02+sqmodA20+sqmodA11+sqmodA12+sqmodA21+sqmodA22",ROOT.RooArgList(sqmodA00,sqmodA01,sqmodA10,sqmodA02,sqmodA20,sqmodA11,sqmodA12,sqmodA21,sqmodA22))
sqmodA00norm = ROOT.RooFormulaVar("sqmodA00norm","f_{SS}","sqmodA00/sqmodA",ROOT.RooArgList(sqmodA00,sqmodA))
sqmodA01norm = ROOT.RooFormulaVar("sqmodA01norm","f_{SV}","sqmodA01/sqmodA",ROOT.RooArgList(sqmodA01,sqmodA))
sqmodA10norm = ROOT.RooFormulaVar("sqmodA10norm","f_{VS}","sqmodA10/sqmodA",ROOT.RooArgList(sqmodA10,sqmodA))
sqmodA02norm = ROOT.RooFormulaVar("sqmodA02norm","f_{ST}","sqmodA02/sqmodA",ROOT.RooArgList(sqmodA02,sqmodA))
sqmodA20norm = ROOT.RooFormulaVar("sqmodA20norm","f_{TS}","sqmodA20/sqmodA",ROOT.RooArgList(sqmodA20,sqmodA))
sqmodA11norm = ROOT.RooFormulaVar("sqmodA11norm","f_{VV}","sqmodA11/sqmodA",ROOT.RooArgList(sqmodA11,sqmodA))
sqmodA12norm = ROOT.RooFormulaVar("sqmodA12norm","f_{VT}","sqmodA12/sqmodA",ROOT.RooArgList(sqmodA12,sqmodA))
sqmodA21norm = ROOT.RooFormulaVar("sqmodA21norm","f_{TV}","sqmodA21/sqmodA",ROOT.RooArgList(sqmodA21,sqmodA))
sqmodA22norm = ROOT.RooFormulaVar("sqmodA22norm","f_{TT}","sqmodA22/sqmodA",ROOT.RooArgList(sqmodA22,sqmodA))
fL11 = ROOT.RooFormulaVar("fL11","f_L^{VV}","sqmodA110/sqmodA11",ROOT.RooArgList(sqmodA110,sqmodA11))
fL12 = ROOT.RooFormulaVar("fL12","f_L^{VT}","sqmodA120/sqmodA12",ROOT.RooArgList(sqmodA120,sqmodA12))
fL21 = ROOT.RooFormulaVar("fL21","f_L^{TV}","sqmodA210/sqmodA21",ROOT.RooArgList(sqmodA210,sqmodA21))
fL22 = ROOT.RooFormulaVar("fL22","f_L^{TT}","sqmodA220/sqmodA22",ROOT.RooArgList(sqmodA220,sqmodA22))
fpar11 = ROOT.RooFormulaVar("fpar11","f_{#parallel}^{VV}","sqmodA11par/sqmodA11",ROOT.RooArgList(sqmodA11par,sqmodA11))
fpar12 = ROOT.RooFormulaVar("fpar12","f_{#parallel}^{VT}","sqmodA12par/sqmodA12",ROOT.RooArgList(sqmodA12par,sqmodA12))
fpar21 = ROOT.RooFormulaVar("fpar21","f_{#parallel}^{TV}","sqmodA21par/sqmodA21",ROOT.RooArgList(sqmodA21par,sqmodA21))
fpar22 = ROOT.RooFormulaVar("fpar22","f_{#parallel1}^{TT}","sqmodA22par/sqmodA22",ROOT.RooArgList(sqmodA22par,sqmodA22))
fperp11 = ROOT.RooFormulaVar("fperp11","f_{#perp}^{VV}","sqmodA11perp/sqmodA11",ROOT.RooArgList(sqmodA11perp,sqmodA11))
fperp12 = ROOT.RooFormulaVar("fperp12","f_{#perp}^{VT}","sqmodA12perp/sqmodA12",ROOT.RooArgList(sqmodA12perp,sqmodA12))
fperp21 = ROOT.RooFormulaVar("fperp21","f_{#perp}^{TV}","sqmodA21perp/sqmodA21",ROOT.RooArgList(sqmodA21perp,sqmodA21))
fperp22 = ROOT.RooFormulaVar("fperp22","f_{#perp1}^{TT}","sqmodA22perp/sqmodA22",ROOT.RooArgList(sqmodA22perp,sqmodA22))
fpar222 = ROOT.RooFormulaVar("fpar222","f_{#parallel2}^{TT}","sqmodA22par2/sqmodA22",ROOT.RooArgList(sqmodA22par2,sqmodA22))
fperp222 = ROOT.RooFormulaVar("fperp222","f_{#perp2}^{TT}","sqmodA22perp2/sqmodA22",ROOT.RooArgList(sqmodA22perp2,sqmodA22))

# Strong phases.
deltaA00 = ROOT.RooFormulaVar("deltaA00","#delta^{SS}","atan2(imA00,reA00)",ROOT.RooArgList(imA00,reA00))
deltaA01 = ROOT.RooFormulaVar("deltaA01","#delta^{SV}","atan2(imA01,reA01)",ROOT.RooArgList(imA01,reA01))
deltaA10 = ROOT.RooFormulaVar("deltaA10","#delta^{VS}","atan2(imA10,reA10)",ROOT.RooArgList(imA10,reA10))
deltaA02 = ROOT.RooFormulaVar("deltaA02","#delta^{ST}","atan2(imA02,reA02)",ROOT.RooArgList(imA02,reA02))
deltaA20 = ROOT.RooFormulaVar("deltaA20","#delta^{TS}","atan2(imA20,reA20)",ROOT.RooArgList(imA20,reA20))
deltaA110 = ROOT.RooFormulaVar("deltaA110","#delta^{VV}_{0}","atan2(imA110,reA110)",ROOT.RooArgList(imA110,reA110))
deltaA11par = ROOT.RooFormulaVar("deltaA11par","#delta^{VV}_{#parallel}","atan2(imA11par,reA11par)",ROOT.RooArgList(imA11par,reA11par))
deltaA11perp = ROOT.RooFormulaVar("deltaA11perp","#delta^{VV}_{#perp}","atan2(imA11perp,reA11perp)",ROOT.RooArgList(imA11perp,reA11perp))
deltaA120 = ROOT.RooFormulaVar("deltaA120","#delta^{VT}_{0}","atan2(imA120,reA120)",ROOT.RooArgList(imA120,reA120))
deltaA12par = ROOT.RooFormulaVar("deltaA12par","#delta^{VT}_{#parallel}","atan2(imA12par,reA12par)",ROOT.RooArgList(imA12par,reA12par))
deltaA12perp = ROOT.RooFormulaVar("deltaA12perp","#delta^{VT}_{#perp}","atan2(imA12perp,reA12perp)",ROOT.RooArgList(imA12perp,reA12perp))
deltaA210 = ROOT.RooFormulaVar("deltaA210","#delta^{TV}_{0}","atan2(imA210,reA210)",ROOT.RooArgList(imA210,reA210))
deltaA21par = ROOT.RooFormulaVar("deltaA21par","#delta^{TV}_{#parallel}","atan2(imA21par,reA21par)",ROOT.RooArgList(imA21par,reA21par))
deltaA21perp = ROOT.RooFormulaVar("deltaA21perp","#delta^{TV}_{#perp}","atan2(imA21perp,reA21perp)",ROOT.RooArgList(imA21perp,reA21perp))
deltaA220 = ROOT.RooFormulaVar("deltaA220","#delta^{TT}_{0}","atan2(imA220,reA220)",ROOT.RooArgList(imA220,reA220))
deltaA22par = ROOT.RooFormulaVar("deltaA22par","#delta^{TT}_{#parallel1}","atan2(imA22par,reA22par)",ROOT.RooArgList(imA22par,reA22par))
deltaA22perp = ROOT.RooFormulaVar("deltaA22perp","#delta^{TT}_{#perp1}","atan2(imA22perp,reA22perp)",ROOT.RooArgList(imA22perp,reA22perp))
deltaA22par2 = ROOT.RooFormulaVar("deltaA22par2","#delta^{TT}_{#parallel2}","atan2(imA22par2,reA22par2)",ROOT.RooArgList(imA22par2,reA22par2))
deltaA22perp2 = ROOT.RooFormulaVar("deltaA22perp2","#delta^{TT}_{#perp2}","atan2(imA22perp2,reA22perp2)",ROOT.RooArgList(imA22perp2,reA22perp2))

# SV CP-eigenstate parameters.
reAsplus = ROOT.RooFormulaVar("reAsplus","reAsplus","1./sqrt(2.)*(reA10+reA01)",ROOT.RooArgList(reA10,reA01))
imAsplus = ROOT.RooFormulaVar("imAsplus","imAsplus","1./sqrt(2.)*(imA10+imA01)",ROOT.RooArgList(imA10,imA01))
reAsminus = ROOT.RooFormulaVar("reAsminus","reAsminus","1./sqrt(2.)*(reA10-reA01)",ROOT.RooArgList(reA10,reA01))
imAsminus = ROOT.RooFormulaVar("imAsminus","imAsminus","1./sqrt(2.)*(imA10-imA01)",ROOT.RooArgList(imA10,imA01))
sqmodAsplus = ROOT.RooFormulaVar("sqmodAsplus","sqmodAsplus","reAsplus*reAsplus+imAsplus*imAsplus",ROOT.RooArgList(reAsplus,imAsplus))
sqmodAsminus = ROOT.RooFormulaVar("sqmodAsminus","sqmodAsminus","reAsminus*reAsminus+imAsminus*imAsminus",ROOT.RooArgList(reAsminus,imAsminus))
sqmodAsplusnorm = ROOT.RooFormulaVar("sqmodAsplusnorm","f_{S+}","sqmodAsplus/sqmodA",ROOT.RooArgList(sqmodAsplus,sqmodA))
sqmodAsminusnorm = ROOT.RooFormulaVar("sqmodAsminusnorm","f_{S-}","sqmodAsminus/sqmodA",ROOT.RooArgList(sqmodAsminus,sqmodA))
deltaAsplus = ROOT.RooFormulaVar("deltaAsplus","deltaAsplus","atan2(imAsplus,reAsplus)",ROOT.RooArgList(imAsplus,reAsplus))
deltaAsminus = ROOT.RooFormulaVar("deltaAsminus","#delta^{S-}","atan2(imAsminus,reAsminus)",ROOT.RooArgList(imAsminus,reAsminus))
deltaA11perpAsplus = ROOT.RooFormulaVar("deltaA11perpAsplus","#delta^{VV}_{#perp}-#delta^{S+}","deltaA11perp-deltaAsplus",ROOT.RooArgList(deltaA11perp,deltaAsplus))

# Mixing parameters.
delta_m_Bs = ROOT.RooRealVar("delta_m_Bs","#Delta m_{B_{s}^{0}}",17.7575,16.5,20.)
gamma_Bs = ROOT.RooRealVar("gamma_Bs","#Gamma_{B_{s}^{0}}",0.6628,0.6428,0.6828)
delta_gamma_Bs = ROOT.RooRealVar("delta_gamma_Bs","#Delta #Gamma_{B_{s}^{0}}",0.09,0.06,0.12)

# Gaussian constraints of the mixing parameters.
parvector_gamma_Bs_delta_gamma_Bs = ROOT.RooArgList(gamma_Bs,delta_gamma_Bs)
mu_gamma_Bs = ROOT.RooConstVar("mu_gamma_Bs","mu_gamma_Bs",0.6643)
mu_delta_gamma_Bs = ROOT.RooConstVar("mu_delta_gamma_Bs","mu_delta_gamma_Bs",0.083)
muvector_gamma_Bs_delta_gamma_Bs = ROOT.RooArgList(mu_gamma_Bs,mu_delta_gamma_Bs)
err_gamma_Bs = 0.0020
err_delta_gamma_Bs = 0.006
rho_gamma_Bs_delta_gamma_Bs = -0.217
cov_gamma_Bs_delta_gamma_Bs = ROOT.TMatrixDSym(2)
cov_gamma_Bs_delta_gamma_Bs[0][0] = err_gamma_Bs*err_gamma_Bs
cov_gamma_Bs_delta_gamma_Bs[0][1] = rho_gamma_Bs_delta_gamma_Bs*err_gamma_Bs*err_delta_gamma_Bs
cov_gamma_Bs_delta_gamma_Bs[1][0] = cov_gamma_Bs_delta_gamma_Bs[0][1]
cov_gamma_Bs_delta_gamma_Bs[1][1] = err_delta_gamma_Bs*err_delta_gamma_Bs
ctrt_gamma_Bs_delta_gamma_Bs = ROOT.RooMultiVarGaussian("ctrt_gamma_Bs_delta_gamma_Bs","ctrt_gamma_Bs_delta_gamma_Bs",parvector_gamma_Bs_delta_gamma_Bs,muvector_gamma_Bs_delta_gamma_Bs,cov_gamma_Bs_delta_gamma_Bs)

# Calibration parameters.
etac_SSK = ROOT.RooRealVar("etac_SSK","<#eta^{SSK}>",0.43463934069)
p0metac_SSK = ROOT.RooRealVar("p0metac_SSK","p_{0}^{SSK}-<#eta^{SSK}>",0.0067,-0.019,0.033)
Dp0half_SSK = ROOT.RooRealVar("Dp0half_SSK","1/2 #Delta p_{0}^{SSK}",-0.0079,-0.015,-0.0009)
p1_SSK = ROOT.RooRealVar("p1_SSK","p_{1}^{SSK}",0.925,0.5,1.35)
Dp1half_SSK = ROOT.RooRealVar("Dp1half_SSK","1/2 #Delta p_{1}^{SSK}",-0.022,-0.14,0.093)
etac_OS = ROOT.RooRealVar("etac_OS","<#eta^{OS}>",0.373332073286)
p0metac_OS = ROOT.RooRealVar("p0metac_OS","p_{0}^{OS}-<#eta^{OS}>",0.0098,-0.02,0.04)
Dp0half_OS = ROOT.RooRealVar("Dp0half_OS","1/2 #Delta p_{0}^{OS}",0.007,0.,0.05)
p1_OS = ROOT.RooRealVar("p1_OS","p_{1}^{OS}",0.9727,0.8,1.2)
Dp1half_OS = ROOT.RooRealVar("Dp1half_OS","1/2 #Delta p_{1}^{OS}",0.0328,0.,0.1)
tres_deltatmean_2011 = ROOT.RooRealVar("tres_deltatmean_2011","#langle #delta_{t} #rangle",0.029)
tres_p0_2011 = ROOT.RooRealVar("tres_p0_2011","p_{0}^{#sigma_{t}}",0.036,0.03,0.06)
tres_p1_2011 = ROOT.RooRealVar("tres_p1_2011","p_{1}^{#sigma_{t}}",1.2,0.8,1.6)
#tres_p0_2011 = ROOT.RooRealVar("tres_p0_2011","p_{0}^{#sigma_{t}}",1.2,0.8,1.5)
#tres_p1_2011 = ROOT.RooRealVar("tres_p1_2011","p_{1}^{#sigma_{t}}",-3.,-5.,0.)
tres_deltatmean_2012 = ROOT.RooRealVar("tres_deltatmean_2012","#langle #delta_{t} #rangle",0.029)
tres_p0_2012 = ROOT.RooRealVar("tres_p0_2012","p_{0}^{#sigma_{t}}",0.036,0.03,0.06)
tres_p1_2012 = ROOT.RooRealVar("tres_p1_2012","p_{1}^{#sigma_{t}}",1.2,0.8,1.6)
#tres_p0_2012 = ROOT.RooRealVar("tres_p0_2012","p_{0}^{#sigma_{t}}",1.2,0.8,1.5)
#tres_p1_2012 = ROOT.RooRealVar("tres_p1_2012","p_{1}^{#sigma_{t}}",-3.,-5.,0.)
mS = ROOT.RooRealVar("mS","mS",1.46297e+03)
gammaS = ROOT.RooRealVar("gammaS","gammaS",3.48114e+02)
mV = ROOT.RooRealVar("mV","mV",895.81,890,902)
gammaV = ROOT.RooRealVar("gammaV","gammaV",47.4,42,54)
mT = ROOT.RooRealVar("mT","mT",1432.4,1410,1450)
gammaT = ROOT.RooRealVar("gammaT","gammaT",109.,80,140)
c1_mass_swave = ROOT.RooRealVar("c1_mass_swave","c1_mass_swave",0.,-10.,10.)
c2_mass_swave = ROOT.RooRealVar("c2_mass_swave","c2_mass_swave",0.,-10.,10.)
c3_mass_swave = ROOT.RooRealVar("c3_mass_swave","c3_mass_swave",0.,-10.,10.)
c4_mass_swave = ROOT.RooRealVar("c4_mass_swave","c4_mass_swave",0.,-10.,10.)
#c1_mass_swave = ROOT.RooRealVar("c1_mass_swave","c1_mass_swave",0.001,0.,1000.)
#c2_mass_swave = ROOT.RooRealVar("c2_mass_swave","c2_mass_swave",0.001,0.,1.)
#c3_mass_swave = ROOT.RooRealVar("c3_mass_swave","c3_mass_swave",1430.,1100.,1600.)
#c4_mass_swave = ROOT.RooRealVar("c4_mass_swave","c4_mass_swave",300.,100.,600.)
c5_mass_swave = ROOT.RooRealVar("c5_mass_swave","c5_mass_swave",0.,-10.,10.)
#c5_mass_swave = ROOT.RooRealVar("c5_mass_swave","c5_mass_swave",0.0016,0.00001,0.01)
c6_mass_swave = ROOT.RooRealVar("c6_mass_swave","c6_mass_swave",0.,-10.,10.)
c7_mass_swave = ROOT.RooRealVar("c7_mass_swave","c7_mass_swave",0.,-10.,10.)
c8_mass_swave = ROOT.RooRealVar("c8_mass_swave","c8_mass_swave",0.,-10.,10.)
c9_mass_swave = ROOT.RooRealVar("c9_mass_swave","c9_mass_swave",0.,-10.,10.)
res_mass = ROOT.RooRealVar("res_mass","res_mass",0.)

#for par in [mV,gammaV,mT,gammaT,c9_mass_swave]: par.setConstant(1)
for par in [mV,gammaV,mT,gammaT,c5_mass_swave,c6_mass_swave,c7_mass_swave,c8_mass_swave,c9_mass_swave]: par.setConstant(1)

# Gaussian constraints of the calibration parameters.
parvector_p0metac_SSK_p1_SSK = ROOT.RooArgList(p0metac_SSK,p1_SSK)
mu_p0metac_SSK = ROOT.RooConstVar("mu_p0metac_SSK","mu_p0metac_SSK",0.0070)
mu_p1_SSK = ROOT.RooConstVar("mu_p1_SSK","mu_p1_SSK",0.925)
muvector_p0metac_SSK_p1_SSK = ROOT.RooArgList(mu_p0metac_SSK,mu_p1_SSK)
err_p0metac_SSK = 0.0052
err_p1_SSK = 0.085
rho_p0metac_SSK_p1_SSK = 0.
cov_p0metac_SSK_p1_SSK = ROOT.TMatrixDSym(2)
cov_p0metac_SSK_p1_SSK[0][0] = err_p0metac_SSK*err_p0metac_SSK
cov_p0metac_SSK_p1_SSK[0][1] = rho_p0metac_SSK_p1_SSK*err_p0metac_SSK*err_p1_SSK
cov_p0metac_SSK_p1_SSK[1][0] = cov_p0metac_SSK_p1_SSK[0][1]
cov_p0metac_SSK_p1_SSK[1][1] = err_p1_SSK*err_p1_SSK
ctrt_p0metac_SSK_p1_SSK = ROOT.RooMultiVarGaussian("ctrt_p0metac_SSK_p1_SSK","ctrt_p0metac_SSK_p1_SSK",parvector_p0metac_SSK_p1_SSK,muvector_p0metac_SSK_p1_SSK,cov_p0metac_SSK_p1_SSK)

parvector_p0metac_OS_p1_OS = ROOT.RooArgList(p0metac_OS,p1_OS)
mu_p0metac_OS = ROOT.RooConstVar("mu_p0metac_OS","mu_p0metac_OS",0.0062)
mu_p1_OS = ROOT.RooConstVar("mu_p1_OS","mu_p1_OS",0.982)
muvector_p0metac_OS_p1_OS = ROOT.RooArgList(mu_p0metac_OS,mu_p1_OS)
err_p0metac_OS = 0.0044
err_p1_OS = 0.035
rho_p0metac_OS_p1_OS = 0.14
cov_p0metac_OS_p1_OS = ROOT.TMatrixDSym(2)
cov_p0metac_OS_p1_OS[0][0] = err_p0metac_OS*err_p0metac_OS
cov_p0metac_OS_p1_OS[0][1] = rho_p0metac_OS_p1_OS*err_p0metac_OS*err_p1_OS
cov_p0metac_OS_p1_OS[1][0] = cov_p0metac_OS_p1_OS[0][1]
cov_p0metac_OS_p1_OS[1][1] = err_p1_OS*err_p1_OS
ctrt_p0metac_OS_p1_OS = ROOT.RooMultiVarGaussian("ctrt_p0metac_OS_p1_OS","ctrt_p0metac_OS_p1_OS",parvector_p0metac_OS_p1_OS,muvector_p0metac_OS_p1_OS,cov_p0metac_OS_p1_OS)

ctrt_Dp0half_SSK = ROOT.RooGaussian("ctrt_Dp0half_SSK","ctrt_Dp0half_SSK",Dp0half_SSK,ROOT.RooFit.RooConst(-0.0082),ROOT.RooFit.RooConst(0.0019))
ctrt_Dp1half_SSK = ROOT.RooGaussian("ctrt_Dp1half_SSK","ctrt_Dp1half_SSK",Dp1half_SSK,ROOT.RooFit.RooConst(-0.016),ROOT.RooFit.RooConst(0.026))
ctrt_Dp0half_OS = ROOT.RooGaussian("ctrt_Dp0half_OS","ctrt_Dp0half_OS",Dp0half_OS,ROOT.RooFit.RooConst(0.007),ROOT.RooFit.RooConst(0.0006))
ctrt_Dp1half_OS = ROOT.RooGaussian("ctrt_Dp1half_OS","ctrt_Dp1half_OS",Dp1half_OS,ROOT.RooFit.RooConst(0.033),ROOT.RooFit.RooConst(0.006))

parvector_tres_p0_tres_p1_2011 = ROOT.RooArgList(tres_p0_2011,tres_p1_2011)
parvector_tres_p0_tres_p1_2012 = ROOT.RooArgList(tres_p0_2012,tres_p1_2012)
ctrt_tres_p0_tres_p1_2011_wide = ROOT.RooMultiVarGaussian("ctrt_tres_p0_tres_p1_2011_wide","ctrt_tres_p0_tres_p1_2011_wide",parvector_tres_p0_tres_p1_2011,muvector_tres_p0_tres_p1_2011_wide,cov_tres_p0_tres_p1_2011_wide)
ctrt_tres_p0_tres_p1_2012_wide = ROOT.RooMultiVarGaussian("ctrt_tres_p0_tres_p1_2012_wide","ctrt_tres_p0_tres_p1_2012_wide",parvector_tres_p0_tres_p1_2012,muvector_tres_p0_tres_p1_2012_wide,cov_tres_p0_tres_p1_2012_wide)
ctrt_tres_p0_tres_p1_2011_narrow = ROOT.RooMultiVarGaussian("ctrt_tres_p0_tres_p1_2011_narrow","ctrt_tres_p0_tres_p1_2011_narrow",parvector_tres_p0_tres_p1_2011,muvector_tres_p0_tres_p1_2011_narrow,cov_tres_p0_tres_p1_2011_narrow)
ctrt_tres_p0_tres_p1_2012_narrow = ROOT.RooMultiVarGaussian("ctrt_tres_p0_tres_p1_2012_narrow","ctrt_tres_p0_tres_p1_2012_narrow",parvector_tres_p0_tres_p1_2012,muvector_tres_p0_tres_p1_2012_narrow,cov_tres_p0_tres_p1_2012_narrow)

# Parameters of the conditional variable spectra.
tag_eff_SSK = ROOT.RooRealVar("tag_eff_SSK","tag_eff_SSK",0.6334)
mu1_SSK = ROOT.RooRealVar("mu1_SSK","mu1_SSK",6.99783e-01,0.3,0.9)
sigma1_SSK = ROOT.RooRealVar("sigma1_SSK","sigma1_SSK",1.16940e-01,0.05,0.5)
c_SSK = ROOT.RooRealVar("c_SSK","c_SSK",9.91397e-01,0.8,1.)
mu2_SSK = ROOT.RooRealVar("mu2_SSK","mu2_SSK",2.92211e-01,0.1,0.5)
sigma2_SSK = ROOT.RooRealVar("sigma2_SSK","sigma2_SSK",5.92591e-02,0.01,0.1)
tag_eff_OS = ROOT.RooRealVar("tag_eff_OS","tag_eff_OS",0.3783)
mu1_OS = ROOT.RooRealVar("mu1_OS","mu1_OS",4.26408e-01,0.2,0.6)
sigma1_OS = ROOT.RooRealVar("sigma1_OS","sigma1_OS",1.05074e-01,0.01,0.2)
c_OS = ROOT.RooRealVar("c_OS","c_OS",8.63185e-01,0.5,1.)
mu2_OS = ROOT.RooRealVar("mu2_OS","mu2_OS",1.88977e-01,0.1,0.3)
sigma2_OS = ROOT.RooRealVar("sigma2_OS","sigma2_OS",4.69965e-02,0.01,0.1)
gamma1_dt = ROOT.RooRealVar("gamma1_dt","gamma1_dt",1.50471e+01,10,20)
beta1_dt = ROOT.RooRealVar("beta1_dt","beta1_dt",1.84541e-03,0.0001,0.01)
c_dt = ROOT.RooRealVar("c_dt","c_dt",0.)#20,15,25)
gamma2_dt = ROOT.RooRealVar("gamma2_dt","gamma2_dt",1.)#1.47627e+01,10,20)
beta2_dt = ROOT.RooRealVar("beta2_dt","beta2_dt",1.)#1.85669e-03,0.0001,0.01)

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
pw_mass_altmodel = ROOT.RooRealVar("pw_mass_altmodel","pw_mass_altmodel",0)
f_1410_rel2_892 = ROOT.RooRealVar("f_1410_rel2_892","f_1410_rel2_892",0.)
delta_1410_rel2_892 = ROOT.RooRealVar("delta_1410_rel2_892","delta_1410_rel2_892",0.)
f_1680_rel2_892 = ROOT.RooRealVar("f_1680_rel2_892","f_1680_rel2_892",0.)
delta_1680_rel2_892 = ROOT.RooRealVar("delta_1680_rel2_892","delta_1680_rel2_892",0.)

# Integrals of the invariant mass dependent terms.
Im00 = ROOT.RooRealVar("Im00","Im00", 1.)
Im01 = ROOT.RooRealVar("Im01","Im01", 1.)
Im10 = ROOT.RooRealVar("Im10","Im10", 1.)
Im02 = ROOT.RooRealVar("Im02","Im02", 1.)
Im20 = ROOT.RooRealVar("Im20","Im20", 1.)
Im11 = ROOT.RooRealVar("Im11","Im11", 1.)
Im12 = ROOT.RooRealVar("Im12","Im12", 1.)
Im21 = ROOT.RooRealVar("Im21","Im21", 1.)
Im22 = ROOT.RooRealVar("Im22","Im22", 1.)
Im00_narrowwin = ROOT.RooRealVar("Im00_narrowwin","Im00_narrowwin", 1.)
Im01_narrowwin = ROOT.RooRealVar("Im01_narrowwin","Im01_narrowwin", 1.)
Im10_narrowwin = ROOT.RooRealVar("Im10_narrowwin","Im10_narrowwin", 1.)
Im02_narrowwin = ROOT.RooRealVar("Im02_narrowwin","Im02_narrowwin", 1.)
Im20_narrowwin = ROOT.RooRealVar("Im20_narrowwin","Im20_narrowwin", 1.)
Im11_narrowwin = ROOT.RooRealVar("Im11_narrowwin","Im11_narrowwin", 1.)
Im12_narrowwin = ROOT.RooRealVar("Im12_narrowwin","Im12_narrowwin", 1.)
Im21_narrowwin = ROOT.RooRealVar("Im21_narrowwin","Im21_narrowwin", 1.)
Im22_narrowwin = ROOT.RooRealVar("Im22_narrowwin","Im22_narrowwin", 1.)
Ih1Re = ROOT.RooRealVar("Ih1Re","Ih1Re", 1.)
Ih2Re = ROOT.RooRealVar("Ih2Re","Ih2Re", 1.)
Ih3Re = ROOT.RooRealVar("Ih3Re","Ih3Re", 1.)
Ih4Re = ROOT.RooRealVar("Ih4Re","Ih4Re", 1.)
Ih5Re = ROOT.RooRealVar("Ih5Re","Ih5Re", 1.)
Ih6Re = ROOT.RooRealVar("Ih6Re","Ih6Re", 1.)
Ih7Re = ROOT.RooRealVar("Ih7Re","Ih7Re", 1.)
Ih8Re = ROOT.RooRealVar("Ih8Re","Ih8Re", 1.)
Ih9Re = ROOT.RooRealVar("Ih9Re","Ih9Re", 1.)
Ih10Re = ROOT.RooRealVar("Ih10Re","Ih10Re", 1.)
Ih11Re = ROOT.RooRealVar("Ih11Re","Ih11Re", 1.)
Ih12Re = ROOT.RooRealVar("Ih12Re","Ih12Re", 1.)
Ih13Re = ROOT.RooRealVar("Ih13Re","Ih13Re", 1.)
Ih14Re = ROOT.RooRealVar("Ih14Re","Ih14Re", 1.)
Ih15Re = ROOT.RooRealVar("Ih15Re","Ih15Re", 1.)
Ih16Re = ROOT.RooRealVar("Ih16Re","Ih16Re", 1.)
Ih17Re = ROOT.RooRealVar("Ih17Re","Ih17Re", 1.)
Ih18Re = ROOT.RooRealVar("Ih18Re","Ih18Re", 1.)
Ih19Re = ROOT.RooRealVar("Ih19Re","Ih19Re", 1.)
Ih20Re = ROOT.RooRealVar("Ih20Re","Ih20Re", 1.)
Ih21Re = ROOT.RooRealVar("Ih21Re","Ih21Re", 1.)
Ih22Re = ROOT.RooRealVar("Ih22Re","Ih22Re", 1.)
Ih23Re = ROOT.RooRealVar("Ih23Re","Ih23Re", 1.)
Ih24Re = ROOT.RooRealVar("Ih24Re","Ih24Re", 1.)
Ih25Re = ROOT.RooRealVar("Ih25Re","Ih25Re", 1.)
Ih26Re = ROOT.RooRealVar("Ih26Re","Ih26Re", 1.)
Ih27Re = ROOT.RooRealVar("Ih27Re","Ih27Re", 1.)
Ih28Re = ROOT.RooRealVar("Ih28Re","Ih28Re", 1.)
Ih29Re = ROOT.RooRealVar("Ih29Re","Ih29Re", 1.)
Ih30Re = ROOT.RooRealVar("Ih30Re","Ih30Re", 1.)
Ih1Im = ROOT.RooRealVar("Ih1Im","Ih1Im", 1.)
Ih2Im = ROOT.RooRealVar("Ih2Im","Ih2Im", 1.)
Ih3Im = ROOT.RooRealVar("Ih3Im","Ih3Im", 1.)
Ih4Im = ROOT.RooRealVar("Ih4Im","Ih4Im", 1.)
Ih5Im = ROOT.RooRealVar("Ih5Im","Ih5Im", 1.)
Ih6Im = ROOT.RooRealVar("Ih6Im","Ih6Im", 1.)
Ih7Im = ROOT.RooRealVar("Ih7Im","Ih7Im", 1.)
Ih8Im = ROOT.RooRealVar("Ih8Im","Ih8Im", 1.)
Ih9Im = ROOT.RooRealVar("Ih9Im","Ih9Im", 1.)
Ih10Im = ROOT.RooRealVar("Ih10Im","Ih10Im", 1.)
Ih11Im = ROOT.RooRealVar("Ih11Im","Ih11Im", 1.)
Ih12Im = ROOT.RooRealVar("Ih12Im","Ih12Im", 1.)
Ih13Im = ROOT.RooRealVar("Ih13Im","Ih13Im", 1.)
Ih14Im = ROOT.RooRealVar("Ih14Im","Ih14Im", 1.)
Ih15Im = ROOT.RooRealVar("Ih15Im","Ih15Im", 1.)
Ih16Im = ROOT.RooRealVar("Ih16Im","Ih16Im", 1.)
Ih17Im = ROOT.RooRealVar("Ih17Im","Ih17Im", 1.)
Ih18Im = ROOT.RooRealVar("Ih18Im","Ih18Im", 1.)
Ih19Im = ROOT.RooRealVar("Ih19Im","Ih19Im", 1.)
Ih20Im = ROOT.RooRealVar("Ih20Im","Ih20Im", 1.)
Ih21Im = ROOT.RooRealVar("Ih21Im","Ih21Im", 1.)
Im_11L0TIS_00 = ROOT.RooRealVar("Im_11L0TIS_00","Im_11L0TIS_00", 1.)
Im_11L0TIS_01 = ROOT.RooRealVar("Im_11L0TIS_01","Im_11L0TIS_01", 1.)
Im_11L0TIS_10 = ROOT.RooRealVar("Im_11L0TIS_10","Im_11L0TIS_10", 1.)
Im_11L0TIS_02 = ROOT.RooRealVar("Im_11L0TIS_02","Im_11L0TIS_02", 1.)
Im_11L0TIS_20 = ROOT.RooRealVar("Im_11L0TIS_20","Im_11L0TIS_20", 1.)
Im_11L0TIS_11 = ROOT.RooRealVar("Im_11L0TIS_11","Im_11L0TIS_11", 1.)
Im_11L0TIS_12 = ROOT.RooRealVar("Im_11L0TIS_12","Im_11L0TIS_12", 1.)
Im_11L0TIS_21 = ROOT.RooRealVar("Im_11L0TIS_21","Im_11L0TIS_21", 1.)
Im_11L0TIS_22 = ROOT.RooRealVar("Im_11L0TIS_22","Im_11L0TIS_22", 1.)
Im_11L0TIS_00_narrowwin = ROOT.RooRealVar("Im_11L0TIS_00_narrowwin","Im_11L0TIS_00_narrowwin", 1.)
Im_11L0TIS_01_narrowwin = ROOT.RooRealVar("Im_11L0TIS_01_narrowwin","Im_11L0TIS_01_narrowwin", 1.)
Im_11L0TIS_10_narrowwin = ROOT.RooRealVar("Im_11L0TIS_10_narrowwin","Im_11L0TIS_10_narrowwin", 1.)
Im_11L0TIS_02_narrowwin = ROOT.RooRealVar("Im_11L0TIS_02_narrowwin","Im_11L0TIS_02_narrowwin", 1.)
Im_11L0TIS_20_narrowwin = ROOT.RooRealVar("Im_11L0TIS_20_narrowwin","Im_11L0TIS_20_narrowwin", 1.)
Im_11L0TIS_11_narrowwin = ROOT.RooRealVar("Im_11L0TIS_11_narrowwin","Im_11L0TIS_11_narrowwin", 1.)
Im_11L0TIS_12_narrowwin = ROOT.RooRealVar("Im_11L0TIS_12_narrowwin","Im_11L0TIS_12_narrowwin", 1.)
Im_11L0TIS_21_narrowwin = ROOT.RooRealVar("Im_11L0TIS_21_narrowwin","Im_11L0TIS_21_narrowwin", 1.)
Im_11L0TIS_22_narrowwin = ROOT.RooRealVar("Im_11L0TIS_22_narrowwin","Im_11L0TIS_22_narrowwin", 1.)
Ih_11L0TIS_1Re = ROOT.RooRealVar("Ih_11L0TIS_1Re","Ih_11L0TIS_1Re", 1.)
Ih_11L0TIS_2Re = ROOT.RooRealVar("Ih_11L0TIS_2Re","Ih_11L0TIS_2Re", 1.)
Ih_11L0TIS_3Re = ROOT.RooRealVar("Ih_11L0TIS_3Re","Ih_11L0TIS_3Re", 1.)
Ih_11L0TIS_4Re = ROOT.RooRealVar("Ih_11L0TIS_4Re","Ih_11L0TIS_4Re", 1.)
Ih_11L0TIS_5Re = ROOT.RooRealVar("Ih_11L0TIS_5Re","Ih_11L0TIS_5Re", 1.)
Ih_11L0TIS_6Re = ROOT.RooRealVar("Ih_11L0TIS_6Re","Ih_11L0TIS_6Re", 1.)
Ih_11L0TIS_7Re = ROOT.RooRealVar("Ih_11L0TIS_7Re","Ih_11L0TIS_7Re", 1.)
Ih_11L0TIS_8Re = ROOT.RooRealVar("Ih_11L0TIS_8Re","Ih_11L0TIS_8Re", 1.)
Ih_11L0TIS_9Re = ROOT.RooRealVar("Ih_11L0TIS_9Re","Ih_11L0TIS_9Re", 1.)
Ih_11L0TIS_10Re = ROOT.RooRealVar("Ih_11L0TIS_10Re","Ih_11L0TIS_10Re", 1.)
Ih_11L0TIS_11Re = ROOT.RooRealVar("Ih_11L0TIS_11Re","Ih_11L0TIS_11Re", 1.)
Ih_11L0TIS_12Re = ROOT.RooRealVar("Ih_11L0TIS_12Re","Ih_11L0TIS_12Re", 1.)
Ih_11L0TIS_13Re = ROOT.RooRealVar("Ih_11L0TIS_13Re","Ih_11L0TIS_13Re", 1.)
Ih_11L0TIS_14Re = ROOT.RooRealVar("Ih_11L0TIS_14Re","Ih_11L0TIS_14Re", 1.)
Ih_11L0TIS_15Re = ROOT.RooRealVar("Ih_11L0TIS_15Re","Ih_11L0TIS_15Re", 1.)
Ih_11L0TIS_16Re = ROOT.RooRealVar("Ih_11L0TIS_16Re","Ih_11L0TIS_16Re", 1.)
Ih_11L0TIS_17Re = ROOT.RooRealVar("Ih_11L0TIS_17Re","Ih_11L0TIS_17Re", 1.)
Ih_11L0TIS_18Re = ROOT.RooRealVar("Ih_11L0TIS_18Re","Ih_11L0TIS_18Re", 1.)
Ih_11L0TIS_19Re = ROOT.RooRealVar("Ih_11L0TIS_19Re","Ih_11L0TIS_19Re", 1.)
Ih_11L0TIS_20Re = ROOT.RooRealVar("Ih_11L0TIS_20Re","Ih_11L0TIS_20Re", 1.)
Ih_11L0TIS_21Re = ROOT.RooRealVar("Ih_11L0TIS_21Re","Ih_11L0TIS_21Re", 1.)
Ih_11L0TIS_22Re = ROOT.RooRealVar("Ih_11L0TIS_22Re","Ih_11L0TIS_22Re", 1.)
Ih_11L0TIS_23Re = ROOT.RooRealVar("Ih_11L0TIS_23Re","Ih_11L0TIS_23Re", 1.)
Ih_11L0TIS_24Re = ROOT.RooRealVar("Ih_11L0TIS_24Re","Ih_11L0TIS_24Re", 1.)
Ih_11L0TIS_25Re = ROOT.RooRealVar("Ih_11L0TIS_25Re","Ih_11L0TIS_25Re", 1.)
Ih_11L0TIS_26Re = ROOT.RooRealVar("Ih_11L0TIS_26Re","Ih_11L0TIS_26Re", 1.)
Ih_11L0TIS_27Re = ROOT.RooRealVar("Ih_11L0TIS_27Re","Ih_11L0TIS_27Re", 1.)
Ih_11L0TIS_28Re = ROOT.RooRealVar("Ih_11L0TIS_28Re","Ih_11L0TIS_28Re", 1.)
Ih_11L0TIS_29Re = ROOT.RooRealVar("Ih_11L0TIS_29Re","Ih_11L0TIS_29Re", 1.)
Ih_11L0TIS_30Re = ROOT.RooRealVar("Ih_11L0TIS_30Re","Ih_11L0TIS_30Re", 1.)
Ih_11L0TIS_1Im = ROOT.RooRealVar("Ih_11L0TIS_1Im","Ih_11L0TIS_1Im", 1.)
Ih_11L0TIS_2Im = ROOT.RooRealVar("Ih_11L0TIS_2Im","Ih_11L0TIS_2Im", 1.)
Ih_11L0TIS_3Im = ROOT.RooRealVar("Ih_11L0TIS_3Im","Ih_11L0TIS_3Im", 1.)
Ih_11L0TIS_4Im = ROOT.RooRealVar("Ih_11L0TIS_4Im","Ih_11L0TIS_4Im", 1.)
Ih_11L0TIS_5Im = ROOT.RooRealVar("Ih_11L0TIS_5Im","Ih_11L0TIS_5Im", 1.)
Ih_11L0TIS_6Im = ROOT.RooRealVar("Ih_11L0TIS_6Im","Ih_11L0TIS_6Im", 1.)
Ih_11L0TIS_7Im = ROOT.RooRealVar("Ih_11L0TIS_7Im","Ih_11L0TIS_7Im", 1.)
Ih_11L0TIS_8Im = ROOT.RooRealVar("Ih_11L0TIS_8Im","Ih_11L0TIS_8Im", 1.)
Ih_11L0TIS_9Im = ROOT.RooRealVar("Ih_11L0TIS_9Im","Ih_11L0TIS_9Im", 1.)
Ih_11L0TIS_10Im = ROOT.RooRealVar("Ih_11L0TIS_10Im","Ih_11L0TIS_10Im", 1.)
Ih_11L0TIS_11Im = ROOT.RooRealVar("Ih_11L0TIS_11Im","Ih_11L0TIS_11Im", 1.)
Ih_11L0TIS_12Im = ROOT.RooRealVar("Ih_11L0TIS_12Im","Ih_11L0TIS_12Im", 1.)
Ih_11L0TIS_13Im = ROOT.RooRealVar("Ih_11L0TIS_13Im","Ih_11L0TIS_13Im", 1.)
Ih_11L0TIS_14Im = ROOT.RooRealVar("Ih_11L0TIS_14Im","Ih_11L0TIS_14Im", 1.)
Ih_11L0TIS_15Im = ROOT.RooRealVar("Ih_11L0TIS_15Im","Ih_11L0TIS_15Im", 1.)
Ih_11L0TIS_16Im = ROOT.RooRealVar("Ih_11L0TIS_16Im","Ih_11L0TIS_16Im", 1.)
Ih_11L0TIS_17Im = ROOT.RooRealVar("Ih_11L0TIS_17Im","Ih_11L0TIS_17Im", 1.)
Ih_11L0TIS_18Im = ROOT.RooRealVar("Ih_11L0TIS_18Im","Ih_11L0TIS_18Im", 1.)
Ih_11L0TIS_19Im = ROOT.RooRealVar("Ih_11L0TIS_19Im","Ih_11L0TIS_19Im", 1.)
Ih_11L0TIS_20Im = ROOT.RooRealVar("Ih_11L0TIS_20Im","Ih_11L0TIS_20Im", 1.)
Ih_11L0TIS_21Im = ROOT.RooRealVar("Ih_11L0TIS_21Im","Ih_11L0TIS_21Im", 1.)
Im_11L0noTIS_00 = ROOT.RooRealVar("Im_11L0noTIS_00","Im_11L0noTIS_00", 1.)
Im_11L0noTIS_01 = ROOT.RooRealVar("Im_11L0noTIS_01","Im_11L0noTIS_01", 1.)
Im_11L0noTIS_10 = ROOT.RooRealVar("Im_11L0noTIS_10","Im_11L0noTIS_10", 1.)
Im_11L0noTIS_02 = ROOT.RooRealVar("Im_11L0noTIS_02","Im_11L0noTIS_02", 1.)
Im_11L0noTIS_20 = ROOT.RooRealVar("Im_11L0noTIS_20","Im_11L0noTIS_20", 1.)
Im_11L0noTIS_11 = ROOT.RooRealVar("Im_11L0noTIS_11","Im_11L0noTIS_11", 1.)
Im_11L0noTIS_12 = ROOT.RooRealVar("Im_11L0noTIS_12","Im_11L0noTIS_12", 1.)
Im_11L0noTIS_21 = ROOT.RooRealVar("Im_11L0noTIS_21","Im_11L0noTIS_21", 1.)
Im_11L0noTIS_22 = ROOT.RooRealVar("Im_11L0noTIS_22","Im_11L0noTIS_22", 1.)
Im_11L0noTIS_00_narrowwin = ROOT.RooRealVar("Im_11L0noTIS_00_narrowwin","Im_11L0noTIS_00_narrowwin", 1.)
Im_11L0noTIS_01_narrowwin = ROOT.RooRealVar("Im_11L0noTIS_01_narrowwin","Im_11L0noTIS_01_narrowwin", 1.)
Im_11L0noTIS_10_narrowwin = ROOT.RooRealVar("Im_11L0noTIS_10_narrowwin","Im_11L0noTIS_10_narrowwin", 1.)
Im_11L0noTIS_02_narrowwin = ROOT.RooRealVar("Im_11L0noTIS_02_narrowwin","Im_11L0noTIS_02_narrowwin", 1.)
Im_11L0noTIS_20_narrowwin = ROOT.RooRealVar("Im_11L0noTIS_20_narrowwin","Im_11L0noTIS_20_narrowwin", 1.)
Im_11L0noTIS_11_narrowwin = ROOT.RooRealVar("Im_11L0noTIS_11_narrowwin","Im_11L0noTIS_11_narrowwin", 1.)
Im_11L0noTIS_12_narrowwin = ROOT.RooRealVar("Im_11L0noTIS_12_narrowwin","Im_11L0noTIS_12_narrowwin", 1.)
Im_11L0noTIS_21_narrowwin = ROOT.RooRealVar("Im_11L0noTIS_21_narrowwin","Im_11L0noTIS_21_narrowwin", 1.)
Im_11L0noTIS_22_narrowwin = ROOT.RooRealVar("Im_11L0noTIS_22_narrowwin","Im_11L0noTIS_22_narrowwin", 1.)
Ih_11L0noTIS_1Re = ROOT.RooRealVar("Ih_11L0noTIS_1Re","Ih_11L0noTIS_1Re", 1.)
Ih_11L0noTIS_2Re = ROOT.RooRealVar("Ih_11L0noTIS_2Re","Ih_11L0noTIS_2Re", 1.)
Ih_11L0noTIS_3Re = ROOT.RooRealVar("Ih_11L0noTIS_3Re","Ih_11L0noTIS_3Re", 1.)
Ih_11L0noTIS_4Re = ROOT.RooRealVar("Ih_11L0noTIS_4Re","Ih_11L0noTIS_4Re", 1.)
Ih_11L0noTIS_5Re = ROOT.RooRealVar("Ih_11L0noTIS_5Re","Ih_11L0noTIS_5Re", 1.)
Ih_11L0noTIS_6Re = ROOT.RooRealVar("Ih_11L0noTIS_6Re","Ih_11L0noTIS_6Re", 1.)
Ih_11L0noTIS_7Re = ROOT.RooRealVar("Ih_11L0noTIS_7Re","Ih_11L0noTIS_7Re", 1.)
Ih_11L0noTIS_8Re = ROOT.RooRealVar("Ih_11L0noTIS_8Re","Ih_11L0noTIS_8Re", 1.)
Ih_11L0noTIS_9Re = ROOT.RooRealVar("Ih_11L0noTIS_9Re","Ih_11L0noTIS_9Re", 1.)
Ih_11L0noTIS_10Re = ROOT.RooRealVar("Ih_11L0noTIS_10Re","Ih_11L0noTIS_10Re", 1.)
Ih_11L0noTIS_11Re = ROOT.RooRealVar("Ih_11L0noTIS_11Re","Ih_11L0noTIS_11Re", 1.)
Ih_11L0noTIS_12Re = ROOT.RooRealVar("Ih_11L0noTIS_12Re","Ih_11L0noTIS_12Re", 1.)
Ih_11L0noTIS_13Re = ROOT.RooRealVar("Ih_11L0noTIS_13Re","Ih_11L0noTIS_13Re", 1.)
Ih_11L0noTIS_14Re = ROOT.RooRealVar("Ih_11L0noTIS_14Re","Ih_11L0noTIS_14Re", 1.)
Ih_11L0noTIS_15Re = ROOT.RooRealVar("Ih_11L0noTIS_15Re","Ih_11L0noTIS_15Re", 1.)
Ih_11L0noTIS_16Re = ROOT.RooRealVar("Ih_11L0noTIS_16Re","Ih_11L0noTIS_16Re", 1.)
Ih_11L0noTIS_17Re = ROOT.RooRealVar("Ih_11L0noTIS_17Re","Ih_11L0noTIS_17Re", 1.)
Ih_11L0noTIS_18Re = ROOT.RooRealVar("Ih_11L0noTIS_18Re","Ih_11L0noTIS_18Re", 1.)
Ih_11L0noTIS_19Re = ROOT.RooRealVar("Ih_11L0noTIS_19Re","Ih_11L0noTIS_19Re", 1.)
Ih_11L0noTIS_20Re = ROOT.RooRealVar("Ih_11L0noTIS_20Re","Ih_11L0noTIS_20Re", 1.)
Ih_11L0noTIS_21Re = ROOT.RooRealVar("Ih_11L0noTIS_21Re","Ih_11L0noTIS_21Re", 1.)
Ih_11L0noTIS_22Re = ROOT.RooRealVar("Ih_11L0noTIS_22Re","Ih_11L0noTIS_22Re", 1.)
Ih_11L0noTIS_23Re = ROOT.RooRealVar("Ih_11L0noTIS_23Re","Ih_11L0noTIS_23Re", 1.)
Ih_11L0noTIS_24Re = ROOT.RooRealVar("Ih_11L0noTIS_24Re","Ih_11L0noTIS_24Re", 1.)
Ih_11L0noTIS_25Re = ROOT.RooRealVar("Ih_11L0noTIS_25Re","Ih_11L0noTIS_25Re", 1.)
Ih_11L0noTIS_26Re = ROOT.RooRealVar("Ih_11L0noTIS_26Re","Ih_11L0noTIS_26Re", 1.)
Ih_11L0noTIS_27Re = ROOT.RooRealVar("Ih_11L0noTIS_27Re","Ih_11L0noTIS_27Re", 1.)
Ih_11L0noTIS_28Re = ROOT.RooRealVar("Ih_11L0noTIS_28Re","Ih_11L0noTIS_28Re", 1.)
Ih_11L0noTIS_29Re = ROOT.RooRealVar("Ih_11L0noTIS_29Re","Ih_11L0noTIS_29Re", 1.)
Ih_11L0noTIS_30Re = ROOT.RooRealVar("Ih_11L0noTIS_30Re","Ih_11L0noTIS_30Re", 1.)
Ih_11L0noTIS_1Im = ROOT.RooRealVar("Ih_11L0noTIS_1Im","Ih_11L0noTIS_1Im", 1.)
Ih_11L0noTIS_2Im = ROOT.RooRealVar("Ih_11L0noTIS_2Im","Ih_11L0noTIS_2Im", 1.)
Ih_11L0noTIS_3Im = ROOT.RooRealVar("Ih_11L0noTIS_3Im","Ih_11L0noTIS_3Im", 1.)
Ih_11L0noTIS_4Im = ROOT.RooRealVar("Ih_11L0noTIS_4Im","Ih_11L0noTIS_4Im", 1.)
Ih_11L0noTIS_5Im = ROOT.RooRealVar("Ih_11L0noTIS_5Im","Ih_11L0noTIS_5Im", 1.)
Ih_11L0noTIS_6Im = ROOT.RooRealVar("Ih_11L0noTIS_6Im","Ih_11L0noTIS_6Im", 1.)
Ih_11L0noTIS_7Im = ROOT.RooRealVar("Ih_11L0noTIS_7Im","Ih_11L0noTIS_7Im", 1.)
Ih_11L0noTIS_8Im = ROOT.RooRealVar("Ih_11L0noTIS_8Im","Ih_11L0noTIS_8Im", 1.)
Ih_11L0noTIS_9Im = ROOT.RooRealVar("Ih_11L0noTIS_9Im","Ih_11L0noTIS_9Im", 1.)
Ih_11L0noTIS_10Im = ROOT.RooRealVar("Ih_11L0noTIS_10Im","Ih_11L0noTIS_10Im", 1.)
Ih_11L0noTIS_11Im = ROOT.RooRealVar("Ih_11L0noTIS_11Im","Ih_11L0noTIS_11Im", 1.)
Ih_11L0noTIS_12Im = ROOT.RooRealVar("Ih_11L0noTIS_12Im","Ih_11L0noTIS_12Im", 1.)
Ih_11L0noTIS_13Im = ROOT.RooRealVar("Ih_11L0noTIS_13Im","Ih_11L0noTIS_13Im", 1.)
Ih_11L0noTIS_14Im = ROOT.RooRealVar("Ih_11L0noTIS_14Im","Ih_11L0noTIS_14Im", 1.)
Ih_11L0noTIS_15Im = ROOT.RooRealVar("Ih_11L0noTIS_15Im","Ih_11L0noTIS_15Im", 1.)
Ih_11L0noTIS_16Im = ROOT.RooRealVar("Ih_11L0noTIS_16Im","Ih_11L0noTIS_16Im", 1.)
Ih_11L0noTIS_17Im = ROOT.RooRealVar("Ih_11L0noTIS_17Im","Ih_11L0noTIS_17Im", 1.)
Ih_11L0noTIS_18Im = ROOT.RooRealVar("Ih_11L0noTIS_18Im","Ih_11L0noTIS_18Im", 1.)
Ih_11L0noTIS_19Im = ROOT.RooRealVar("Ih_11L0noTIS_19Im","Ih_11L0noTIS_19Im", 1.)
Ih_11L0noTIS_20Im = ROOT.RooRealVar("Ih_11L0noTIS_20Im","Ih_11L0noTIS_20Im", 1.)
Ih_11L0noTIS_21Im = ROOT.RooRealVar("Ih_11L0noTIS_21Im","Ih_11L0noTIS_21Im", 1.)
Im_12L0TIS_00 = ROOT.RooRealVar("Im_12L0TIS_00","Im_12L0TIS_00", 1.)
Im_12L0TIS_01 = ROOT.RooRealVar("Im_12L0TIS_01","Im_12L0TIS_01", 1.)
Im_12L0TIS_10 = ROOT.RooRealVar("Im_12L0TIS_10","Im_12L0TIS_10", 1.)
Im_12L0TIS_02 = ROOT.RooRealVar("Im_12L0TIS_02","Im_12L0TIS_02", 1.)
Im_12L0TIS_20 = ROOT.RooRealVar("Im_12L0TIS_20","Im_12L0TIS_20", 1.)
Im_12L0TIS_11 = ROOT.RooRealVar("Im_12L0TIS_11","Im_12L0TIS_11", 1.)
Im_12L0TIS_12 = ROOT.RooRealVar("Im_12L0TIS_12","Im_12L0TIS_12", 1.)
Im_12L0TIS_21 = ROOT.RooRealVar("Im_12L0TIS_21","Im_12L0TIS_21", 1.)
Im_12L0TIS_22 = ROOT.RooRealVar("Im_12L0TIS_22","Im_12L0TIS_22", 1.)
Im_12L0TIS_00_narrowwin = ROOT.RooRealVar("Im_12L0TIS_00_narrowwin","Im_12L0TIS_00_narrowwin", 1.)
Im_12L0TIS_01_narrowwin = ROOT.RooRealVar("Im_12L0TIS_01_narrowwin","Im_12L0TIS_01_narrowwin", 1.)
Im_12L0TIS_10_narrowwin = ROOT.RooRealVar("Im_12L0TIS_10_narrowwin","Im_12L0TIS_10_narrowwin", 1.)
Im_12L0TIS_02_narrowwin = ROOT.RooRealVar("Im_12L0TIS_02_narrowwin","Im_12L0TIS_02_narrowwin", 1.)
Im_12L0TIS_20_narrowwin = ROOT.RooRealVar("Im_12L0TIS_20_narrowwin","Im_12L0TIS_20_narrowwin", 1.)
Im_12L0TIS_11_narrowwin = ROOT.RooRealVar("Im_12L0TIS_11_narrowwin","Im_12L0TIS_11_narrowwin", 1.)
Im_12L0TIS_12_narrowwin = ROOT.RooRealVar("Im_12L0TIS_12_narrowwin","Im_12L0TIS_12_narrowwin", 1.)
Im_12L0TIS_21_narrowwin = ROOT.RooRealVar("Im_12L0TIS_21_narrowwin","Im_12L0TIS_21_narrowwin", 1.)
Im_12L0TIS_22_narrowwin = ROOT.RooRealVar("Im_12L0TIS_22_narrowwin","Im_12L0TIS_22_narrowwin", 1.)
Ih_12L0TIS_1Re = ROOT.RooRealVar("Ih_12L0TIS_1Re","Ih_12L0TIS_1Re", 1.)
Ih_12L0TIS_2Re = ROOT.RooRealVar("Ih_12L0TIS_2Re","Ih_12L0TIS_2Re", 1.)
Ih_12L0TIS_3Re = ROOT.RooRealVar("Ih_12L0TIS_3Re","Ih_12L0TIS_3Re", 1.)
Ih_12L0TIS_4Re = ROOT.RooRealVar("Ih_12L0TIS_4Re","Ih_12L0TIS_4Re", 1.)
Ih_12L0TIS_5Re = ROOT.RooRealVar("Ih_12L0TIS_5Re","Ih_12L0TIS_5Re", 1.)
Ih_12L0TIS_6Re = ROOT.RooRealVar("Ih_12L0TIS_6Re","Ih_12L0TIS_6Re", 1.)
Ih_12L0TIS_7Re = ROOT.RooRealVar("Ih_12L0TIS_7Re","Ih_12L0TIS_7Re", 1.)
Ih_12L0TIS_8Re = ROOT.RooRealVar("Ih_12L0TIS_8Re","Ih_12L0TIS_8Re", 1.)
Ih_12L0TIS_9Re = ROOT.RooRealVar("Ih_12L0TIS_9Re","Ih_12L0TIS_9Re", 1.)
Ih_12L0TIS_10Re = ROOT.RooRealVar("Ih_12L0TIS_10Re","Ih_12L0TIS_10Re", 1.)
Ih_12L0TIS_11Re = ROOT.RooRealVar("Ih_12L0TIS_11Re","Ih_12L0TIS_11Re", 1.)
Ih_12L0TIS_12Re = ROOT.RooRealVar("Ih_12L0TIS_12Re","Ih_12L0TIS_12Re", 1.)
Ih_12L0TIS_13Re = ROOT.RooRealVar("Ih_12L0TIS_13Re","Ih_12L0TIS_13Re", 1.)
Ih_12L0TIS_14Re = ROOT.RooRealVar("Ih_12L0TIS_14Re","Ih_12L0TIS_14Re", 1.)
Ih_12L0TIS_15Re = ROOT.RooRealVar("Ih_12L0TIS_15Re","Ih_12L0TIS_15Re", 1.)
Ih_12L0TIS_16Re = ROOT.RooRealVar("Ih_12L0TIS_16Re","Ih_12L0TIS_16Re", 1.)
Ih_12L0TIS_17Re = ROOT.RooRealVar("Ih_12L0TIS_17Re","Ih_12L0TIS_17Re", 1.)
Ih_12L0TIS_18Re = ROOT.RooRealVar("Ih_12L0TIS_18Re","Ih_12L0TIS_18Re", 1.)
Ih_12L0TIS_19Re = ROOT.RooRealVar("Ih_12L0TIS_19Re","Ih_12L0TIS_19Re", 1.)
Ih_12L0TIS_20Re = ROOT.RooRealVar("Ih_12L0TIS_20Re","Ih_12L0TIS_20Re", 1.)
Ih_12L0TIS_21Re = ROOT.RooRealVar("Ih_12L0TIS_21Re","Ih_12L0TIS_21Re", 1.)
Ih_12L0TIS_22Re = ROOT.RooRealVar("Ih_12L0TIS_22Re","Ih_12L0TIS_22Re", 1.)
Ih_12L0TIS_23Re = ROOT.RooRealVar("Ih_12L0TIS_23Re","Ih_12L0TIS_23Re", 1.)
Ih_12L0TIS_24Re = ROOT.RooRealVar("Ih_12L0TIS_24Re","Ih_12L0TIS_24Re", 1.)
Ih_12L0TIS_25Re = ROOT.RooRealVar("Ih_12L0TIS_25Re","Ih_12L0TIS_25Re", 1.)
Ih_12L0TIS_26Re = ROOT.RooRealVar("Ih_12L0TIS_26Re","Ih_12L0TIS_26Re", 1.)
Ih_12L0TIS_27Re = ROOT.RooRealVar("Ih_12L0TIS_27Re","Ih_12L0TIS_27Re", 1.)
Ih_12L0TIS_28Re = ROOT.RooRealVar("Ih_12L0TIS_28Re","Ih_12L0TIS_28Re", 1.)
Ih_12L0TIS_29Re = ROOT.RooRealVar("Ih_12L0TIS_29Re","Ih_12L0TIS_29Re", 1.)
Ih_12L0TIS_30Re = ROOT.RooRealVar("Ih_12L0TIS_30Re","Ih_12L0TIS_30Re", 1.)
Ih_12L0TIS_1Im = ROOT.RooRealVar("Ih_12L0TIS_1Im","Ih_12L0TIS_1Im", 1.)
Ih_12L0TIS_2Im = ROOT.RooRealVar("Ih_12L0TIS_2Im","Ih_12L0TIS_2Im", 1.)
Ih_12L0TIS_3Im = ROOT.RooRealVar("Ih_12L0TIS_3Im","Ih_12L0TIS_3Im", 1.)
Ih_12L0TIS_4Im = ROOT.RooRealVar("Ih_12L0TIS_4Im","Ih_12L0TIS_4Im", 1.)
Ih_12L0TIS_5Im = ROOT.RooRealVar("Ih_12L0TIS_5Im","Ih_12L0TIS_5Im", 1.)
Ih_12L0TIS_6Im = ROOT.RooRealVar("Ih_12L0TIS_6Im","Ih_12L0TIS_6Im", 1.)
Ih_12L0TIS_7Im = ROOT.RooRealVar("Ih_12L0TIS_7Im","Ih_12L0TIS_7Im", 1.)
Ih_12L0TIS_8Im = ROOT.RooRealVar("Ih_12L0TIS_8Im","Ih_12L0TIS_8Im", 1.)
Ih_12L0TIS_9Im = ROOT.RooRealVar("Ih_12L0TIS_9Im","Ih_12L0TIS_9Im", 1.)
Ih_12L0TIS_10Im = ROOT.RooRealVar("Ih_12L0TIS_10Im","Ih_12L0TIS_10Im", 1.)
Ih_12L0TIS_11Im = ROOT.RooRealVar("Ih_12L0TIS_11Im","Ih_12L0TIS_11Im", 1.)
Ih_12L0TIS_12Im = ROOT.RooRealVar("Ih_12L0TIS_12Im","Ih_12L0TIS_12Im", 1.)
Ih_12L0TIS_13Im = ROOT.RooRealVar("Ih_12L0TIS_13Im","Ih_12L0TIS_13Im", 1.)
Ih_12L0TIS_14Im = ROOT.RooRealVar("Ih_12L0TIS_14Im","Ih_12L0TIS_14Im", 1.)
Ih_12L0TIS_15Im = ROOT.RooRealVar("Ih_12L0TIS_15Im","Ih_12L0TIS_15Im", 1.)
Ih_12L0TIS_16Im = ROOT.RooRealVar("Ih_12L0TIS_16Im","Ih_12L0TIS_16Im", 1.)
Ih_12L0TIS_17Im = ROOT.RooRealVar("Ih_12L0TIS_17Im","Ih_12L0TIS_17Im", 1.)
Ih_12L0TIS_18Im = ROOT.RooRealVar("Ih_12L0TIS_18Im","Ih_12L0TIS_18Im", 1.)
Ih_12L0TIS_19Im = ROOT.RooRealVar("Ih_12L0TIS_19Im","Ih_12L0TIS_19Im", 1.)
Ih_12L0TIS_20Im = ROOT.RooRealVar("Ih_12L0TIS_20Im","Ih_12L0TIS_20Im", 1.)
Ih_12L0TIS_21Im = ROOT.RooRealVar("Ih_12L0TIS_21Im","Ih_12L0TIS_21Im", 1.)
Im_12L0noTIS_00 = ROOT.RooRealVar("Im_12L0noTIS_00","Im_12L0noTIS_00", 1.)
Im_12L0noTIS_01 = ROOT.RooRealVar("Im_12L0noTIS_01","Im_12L0noTIS_01", 1.)
Im_12L0noTIS_10 = ROOT.RooRealVar("Im_12L0noTIS_10","Im_12L0noTIS_10", 1.)
Im_12L0noTIS_02 = ROOT.RooRealVar("Im_12L0noTIS_02","Im_12L0noTIS_02", 1.)
Im_12L0noTIS_20 = ROOT.RooRealVar("Im_12L0noTIS_20","Im_12L0noTIS_20", 1.)
Im_12L0noTIS_11 = ROOT.RooRealVar("Im_12L0noTIS_11","Im_12L0noTIS_11", 1.)
Im_12L0noTIS_12 = ROOT.RooRealVar("Im_12L0noTIS_12","Im_12L0noTIS_12", 1.)
Im_12L0noTIS_21 = ROOT.RooRealVar("Im_12L0noTIS_21","Im_12L0noTIS_21", 1.)
Im_12L0noTIS_22 = ROOT.RooRealVar("Im_12L0noTIS_22","Im_12L0noTIS_22", 1.)
Im_12L0noTIS_00_narrowwin = ROOT.RooRealVar("Im_12L0noTIS_00_narrowwin","Im_12L0noTIS_00_narrowwin", 1.)
Im_12L0noTIS_01_narrowwin = ROOT.RooRealVar("Im_12L0noTIS_01_narrowwin","Im_12L0noTIS_01_narrowwin", 1.)
Im_12L0noTIS_10_narrowwin = ROOT.RooRealVar("Im_12L0noTIS_10_narrowwin","Im_12L0noTIS_10_narrowwin", 1.)
Im_12L0noTIS_02_narrowwin = ROOT.RooRealVar("Im_12L0noTIS_02_narrowwin","Im_12L0noTIS_02_narrowwin", 1.)
Im_12L0noTIS_20_narrowwin = ROOT.RooRealVar("Im_12L0noTIS_20_narrowwin","Im_12L0noTIS_20_narrowwin", 1.)
Im_12L0noTIS_11_narrowwin = ROOT.RooRealVar("Im_12L0noTIS_11_narrowwin","Im_12L0noTIS_11_narrowwin", 1.)
Im_12L0noTIS_12_narrowwin = ROOT.RooRealVar("Im_12L0noTIS_12_narrowwin","Im_12L0noTIS_12_narrowwin", 1.)
Im_12L0noTIS_21_narrowwin = ROOT.RooRealVar("Im_12L0noTIS_21_narrowwin","Im_12L0noTIS_21_narrowwin", 1.)
Im_12L0noTIS_22_narrowwin = ROOT.RooRealVar("Im_12L0noTIS_22_narrowwin","Im_12L0noTIS_22_narrowwin", 1.)
Ih_12L0noTIS_1Re = ROOT.RooRealVar("Ih_12L0noTIS_1Re","Ih_12L0noTIS_1Re", 1.)
Ih_12L0noTIS_2Re = ROOT.RooRealVar("Ih_12L0noTIS_2Re","Ih_12L0noTIS_2Re", 1.)
Ih_12L0noTIS_3Re = ROOT.RooRealVar("Ih_12L0noTIS_3Re","Ih_12L0noTIS_3Re", 1.)
Ih_12L0noTIS_4Re = ROOT.RooRealVar("Ih_12L0noTIS_4Re","Ih_12L0noTIS_4Re", 1.)
Ih_12L0noTIS_5Re = ROOT.RooRealVar("Ih_12L0noTIS_5Re","Ih_12L0noTIS_5Re", 1.)
Ih_12L0noTIS_6Re = ROOT.RooRealVar("Ih_12L0noTIS_6Re","Ih_12L0noTIS_6Re", 1.)
Ih_12L0noTIS_7Re = ROOT.RooRealVar("Ih_12L0noTIS_7Re","Ih_12L0noTIS_7Re", 1.)
Ih_12L0noTIS_8Re = ROOT.RooRealVar("Ih_12L0noTIS_8Re","Ih_12L0noTIS_8Re", 1.)
Ih_12L0noTIS_9Re = ROOT.RooRealVar("Ih_12L0noTIS_9Re","Ih_12L0noTIS_9Re", 1.)
Ih_12L0noTIS_10Re = ROOT.RooRealVar("Ih_12L0noTIS_10Re","Ih_12L0noTIS_10Re", 1.)
Ih_12L0noTIS_11Re = ROOT.RooRealVar("Ih_12L0noTIS_11Re","Ih_12L0noTIS_11Re", 1.)
Ih_12L0noTIS_12Re = ROOT.RooRealVar("Ih_12L0noTIS_12Re","Ih_12L0noTIS_12Re", 1.)
Ih_12L0noTIS_13Re = ROOT.RooRealVar("Ih_12L0noTIS_13Re","Ih_12L0noTIS_13Re", 1.)
Ih_12L0noTIS_14Re = ROOT.RooRealVar("Ih_12L0noTIS_14Re","Ih_12L0noTIS_14Re", 1.)
Ih_12L0noTIS_15Re = ROOT.RooRealVar("Ih_12L0noTIS_15Re","Ih_12L0noTIS_15Re", 1.)
Ih_12L0noTIS_16Re = ROOT.RooRealVar("Ih_12L0noTIS_16Re","Ih_12L0noTIS_16Re", 1.)
Ih_12L0noTIS_17Re = ROOT.RooRealVar("Ih_12L0noTIS_17Re","Ih_12L0noTIS_17Re", 1.)
Ih_12L0noTIS_18Re = ROOT.RooRealVar("Ih_12L0noTIS_18Re","Ih_12L0noTIS_18Re", 1.)
Ih_12L0noTIS_19Re = ROOT.RooRealVar("Ih_12L0noTIS_19Re","Ih_12L0noTIS_19Re", 1.)
Ih_12L0noTIS_20Re = ROOT.RooRealVar("Ih_12L0noTIS_20Re","Ih_12L0noTIS_20Re", 1.)
Ih_12L0noTIS_21Re = ROOT.RooRealVar("Ih_12L0noTIS_21Re","Ih_12L0noTIS_21Re", 1.)
Ih_12L0noTIS_22Re = ROOT.RooRealVar("Ih_12L0noTIS_22Re","Ih_12L0noTIS_22Re", 1.)
Ih_12L0noTIS_23Re = ROOT.RooRealVar("Ih_12L0noTIS_23Re","Ih_12L0noTIS_23Re", 1.)
Ih_12L0noTIS_24Re = ROOT.RooRealVar("Ih_12L0noTIS_24Re","Ih_12L0noTIS_24Re", 1.)
Ih_12L0noTIS_25Re = ROOT.RooRealVar("Ih_12L0noTIS_25Re","Ih_12L0noTIS_25Re", 1.)
Ih_12L0noTIS_26Re = ROOT.RooRealVar("Ih_12L0noTIS_26Re","Ih_12L0noTIS_26Re", 1.)
Ih_12L0noTIS_27Re = ROOT.RooRealVar("Ih_12L0noTIS_27Re","Ih_12L0noTIS_27Re", 1.)
Ih_12L0noTIS_28Re = ROOT.RooRealVar("Ih_12L0noTIS_28Re","Ih_12L0noTIS_28Re", 1.)
Ih_12L0noTIS_29Re = ROOT.RooRealVar("Ih_12L0noTIS_29Re","Ih_12L0noTIS_29Re", 1.)
Ih_12L0noTIS_30Re = ROOT.RooRealVar("Ih_12L0noTIS_30Re","Ih_12L0noTIS_30Re", 1.)
Ih_12L0noTIS_1Im = ROOT.RooRealVar("Ih_12L0noTIS_1Im","Ih_12L0noTIS_1Im", 1.)
Ih_12L0noTIS_2Im = ROOT.RooRealVar("Ih_12L0noTIS_2Im","Ih_12L0noTIS_2Im", 1.)
Ih_12L0noTIS_3Im = ROOT.RooRealVar("Ih_12L0noTIS_3Im","Ih_12L0noTIS_3Im", 1.)
Ih_12L0noTIS_4Im = ROOT.RooRealVar("Ih_12L0noTIS_4Im","Ih_12L0noTIS_4Im", 1.)
Ih_12L0noTIS_5Im = ROOT.RooRealVar("Ih_12L0noTIS_5Im","Ih_12L0noTIS_5Im", 1.)
Ih_12L0noTIS_6Im = ROOT.RooRealVar("Ih_12L0noTIS_6Im","Ih_12L0noTIS_6Im", 1.)
Ih_12L0noTIS_7Im = ROOT.RooRealVar("Ih_12L0noTIS_7Im","Ih_12L0noTIS_7Im", 1.)
Ih_12L0noTIS_8Im = ROOT.RooRealVar("Ih_12L0noTIS_8Im","Ih_12L0noTIS_8Im", 1.)
Ih_12L0noTIS_9Im = ROOT.RooRealVar("Ih_12L0noTIS_9Im","Ih_12L0noTIS_9Im", 1.)
Ih_12L0noTIS_10Im = ROOT.RooRealVar("Ih_12L0noTIS_10Im","Ih_12L0noTIS_10Im", 1.)
Ih_12L0noTIS_11Im = ROOT.RooRealVar("Ih_12L0noTIS_11Im","Ih_12L0noTIS_11Im", 1.)
Ih_12L0noTIS_12Im = ROOT.RooRealVar("Ih_12L0noTIS_12Im","Ih_12L0noTIS_12Im", 1.)
Ih_12L0noTIS_13Im = ROOT.RooRealVar("Ih_12L0noTIS_13Im","Ih_12L0noTIS_13Im", 1.)
Ih_12L0noTIS_14Im = ROOT.RooRealVar("Ih_12L0noTIS_14Im","Ih_12L0noTIS_14Im", 1.)
Ih_12L0noTIS_15Im = ROOT.RooRealVar("Ih_12L0noTIS_15Im","Ih_12L0noTIS_15Im", 1.)
Ih_12L0noTIS_16Im = ROOT.RooRealVar("Ih_12L0noTIS_16Im","Ih_12L0noTIS_16Im", 1.)
Ih_12L0noTIS_17Im = ROOT.RooRealVar("Ih_12L0noTIS_17Im","Ih_12L0noTIS_17Im", 1.)
Ih_12L0noTIS_18Im = ROOT.RooRealVar("Ih_12L0noTIS_18Im","Ih_12L0noTIS_18Im", 1.)
Ih_12L0noTIS_19Im = ROOT.RooRealVar("Ih_12L0noTIS_19Im","Ih_12L0noTIS_19Im", 1.)
Ih_12L0noTIS_20Im = ROOT.RooRealVar("Ih_12L0noTIS_20Im","Ih_12L0noTIS_20Im", 1.)
Ih_12L0noTIS_21Im = ROOT.RooRealVar("Ih_12L0noTIS_21Im","Ih_12L0noTIS_21Im", 1.)

# Integrals of the angular terms.
If1 = ROOT.RooRealVar("If1","If1", 1.)
If2 = ROOT.RooRealVar("If2","If2", 1.)
If3 = ROOT.RooRealVar("If3","If3", 1.)
If4 = ROOT.RooRealVar("If4","If4", 1.)
If5 = ROOT.RooRealVar("If5","If5", 1.)
If6 = ROOT.RooRealVar("If6","If6", 1.)
If7 = ROOT.RooRealVar("If7","If7", 1.)
If8 = ROOT.RooRealVar("If8","If8", 1.)
If9 = ROOT.RooRealVar("If9","If9", 1.)
If10 = ROOT.RooRealVar("If10","If10", 1.)
If11 = ROOT.RooRealVar("If11","If11", 1.)
If12 = ROOT.RooRealVar("If12","If12", 1.)
If13 = ROOT.RooRealVar("If13","If13", 1.)
If14 = ROOT.RooRealVar("If14","If14", 1.)
If15 = ROOT.RooRealVar("If15","If15", 1.)
If16 = ROOT.RooRealVar("If16","If16", 1.)
If17 = ROOT.RooRealVar("If17","If17", 1.)
If18 = ROOT.RooRealVar("If18","If18", 1.)
If_11L0TIS_1 = ROOT.RooRealVar("If_11L0TIS_1","If_11L0TIS_1", 1.)
If_11L0TIS_2 = ROOT.RooRealVar("If_11L0TIS_2","If_11L0TIS_2", 1.)
If_11L0TIS_3 = ROOT.RooRealVar("If_11L0TIS_3","If_11L0TIS_3", 1.)
If_11L0TIS_4 = ROOT.RooRealVar("If_11L0TIS_4","If_11L0TIS_4", 1.)
If_11L0TIS_5 = ROOT.RooRealVar("If_11L0TIS_5","If_11L0TIS_5", 1.)
If_11L0TIS_6 = ROOT.RooRealVar("If_11L0TIS_6","If_11L0TIS_6", 1.)
If_11L0TIS_7 = ROOT.RooRealVar("If_11L0TIS_7","If_11L0TIS_7", 1.)
If_11L0TIS_8 = ROOT.RooRealVar("If_11L0TIS_8","If_11L0TIS_8", 1.)
If_11L0TIS_9 = ROOT.RooRealVar("If_11L0TIS_9","If_11L0TIS_9", 1.)
If_11L0TIS_10 = ROOT.RooRealVar("If_11L0TIS_10","If_11L0TIS_10", 1.)
If_11L0TIS_11 = ROOT.RooRealVar("If_11L0TIS_11","If_11L0TIS_11", 1.)
If_11L0TIS_12 = ROOT.RooRealVar("If_11L0TIS_12","If_11L0TIS_12", 1.)
If_11L0TIS_13 = ROOT.RooRealVar("If_11L0TIS_13","If_11L0TIS_13", 1.)
If_11L0TIS_14 = ROOT.RooRealVar("If_11L0TIS_14","If_11L0TIS_14", 1.)
If_11L0TIS_15 = ROOT.RooRealVar("If_11L0TIS_15","If_11L0TIS_15", 1.)
If_11L0TIS_16 = ROOT.RooRealVar("If_11L0TIS_16","If_11L0TIS_16", 1.)
If_11L0TIS_17 = ROOT.RooRealVar("If_11L0TIS_17","If_11L0TIS_17", 1.)
If_11L0TIS_18 = ROOT.RooRealVar("If_11L0TIS_18","If_11L0TIS_18", 1.)
If_11L0noTIS_1 = ROOT.RooRealVar("If_11L0noTIS_1","If_11L0noTIS_1", 1.)
If_11L0noTIS_2 = ROOT.RooRealVar("If_11L0noTIS_2","If_11L0noTIS_2", 1.)
If_11L0noTIS_3 = ROOT.RooRealVar("If_11L0noTIS_3","If_11L0noTIS_3", 1.)
If_11L0noTIS_4 = ROOT.RooRealVar("If_11L0noTIS_4","If_11L0noTIS_4", 1.)
If_11L0noTIS_5 = ROOT.RooRealVar("If_11L0noTIS_5","If_11L0noTIS_5", 1.)
If_11L0noTIS_6 = ROOT.RooRealVar("If_11L0noTIS_6","If_11L0noTIS_6", 1.)
If_11L0noTIS_7 = ROOT.RooRealVar("If_11L0noTIS_7","If_11L0noTIS_7", 1.)
If_11L0noTIS_8 = ROOT.RooRealVar("If_11L0noTIS_8","If_11L0noTIS_8", 1.)
If_11L0noTIS_9 = ROOT.RooRealVar("If_11L0noTIS_9","If_11L0noTIS_9", 1.)
If_11L0noTIS_10 = ROOT.RooRealVar("If_11L0noTIS_10","If_11L0noTIS_10", 1.)
If_11L0noTIS_11 = ROOT.RooRealVar("If_11L0noTIS_11","If_11L0noTIS_11", 1.)
If_11L0noTIS_12 = ROOT.RooRealVar("If_11L0noTIS_12","If_11L0noTIS_12", 1.)
If_11L0noTIS_13 = ROOT.RooRealVar("If_11L0noTIS_13","If_11L0noTIS_13", 1.)
If_11L0noTIS_14 = ROOT.RooRealVar("If_11L0noTIS_14","If_11L0noTIS_14", 1.)
If_11L0noTIS_15 = ROOT.RooRealVar("If_11L0noTIS_15","If_11L0noTIS_15", 1.)
If_11L0noTIS_16 = ROOT.RooRealVar("If_11L0noTIS_16","If_11L0noTIS_16", 1.)
If_11L0noTIS_17 = ROOT.RooRealVar("If_11L0noTIS_17","If_11L0noTIS_17", 1.)
If_11L0noTIS_18 = ROOT.RooRealVar("If_11L0noTIS_18","If_11L0noTIS_18", 1.)
If_12L0TIS_1 = ROOT.RooRealVar("If_12L0TIS_1","If_12L0TIS_1", 1.)
If_12L0TIS_2 = ROOT.RooRealVar("If_12L0TIS_2","If_12L0TIS_2", 1.)
If_12L0TIS_3 = ROOT.RooRealVar("If_12L0TIS_3","If_12L0TIS_3", 1.)
If_12L0TIS_4 = ROOT.RooRealVar("If_12L0TIS_4","If_12L0TIS_4", 1.)
If_12L0TIS_5 = ROOT.RooRealVar("If_12L0TIS_5","If_12L0TIS_5", 1.)
If_12L0TIS_6 = ROOT.RooRealVar("If_12L0TIS_6","If_12L0TIS_6", 1.)
If_12L0TIS_7 = ROOT.RooRealVar("If_12L0TIS_7","If_12L0TIS_7", 1.)
If_12L0TIS_8 = ROOT.RooRealVar("If_12L0TIS_8","If_12L0TIS_8", 1.)
If_12L0TIS_9 = ROOT.RooRealVar("If_12L0TIS_9","If_12L0TIS_9", 1.)
If_12L0TIS_10 = ROOT.RooRealVar("If_12L0TIS_10","If_12L0TIS_10", 1.)
If_12L0TIS_11 = ROOT.RooRealVar("If_12L0TIS_11","If_12L0TIS_11", 1.)
If_12L0TIS_12 = ROOT.RooRealVar("If_12L0TIS_12","If_12L0TIS_12", 1.)
If_12L0TIS_13 = ROOT.RooRealVar("If_12L0TIS_13","If_12L0TIS_13", 1.)
If_12L0TIS_14 = ROOT.RooRealVar("If_12L0TIS_14","If_12L0TIS_14", 1.)
If_12L0TIS_15 = ROOT.RooRealVar("If_12L0TIS_15","If_12L0TIS_15", 1.)
If_12L0TIS_16 = ROOT.RooRealVar("If_12L0TIS_16","If_12L0TIS_16", 1.)
If_12L0TIS_17 = ROOT.RooRealVar("If_12L0TIS_17","If_12L0TIS_17", 1.)
If_12L0TIS_18 = ROOT.RooRealVar("If_12L0TIS_18","If_12L0TIS_18", 1.)
If_12L0noTIS_1 = ROOT.RooRealVar("If_12L0noTIS_1","If_12L0noTIS_1", 1.)
If_12L0noTIS_2 = ROOT.RooRealVar("If_12L0noTIS_2","If_12L0noTIS_2", 1.)
If_12L0noTIS_3 = ROOT.RooRealVar("If_12L0noTIS_3","If_12L0noTIS_3", 1.)
If_12L0noTIS_4 = ROOT.RooRealVar("If_12L0noTIS_4","If_12L0noTIS_4", 1.)
If_12L0noTIS_5 = ROOT.RooRealVar("If_12L0noTIS_5","If_12L0noTIS_5", 1.)
If_12L0noTIS_6 = ROOT.RooRealVar("If_12L0noTIS_6","If_12L0noTIS_6", 1.)
If_12L0noTIS_7 = ROOT.RooRealVar("If_12L0noTIS_7","If_12L0noTIS_7", 1.)
If_12L0noTIS_8 = ROOT.RooRealVar("If_12L0noTIS_8","If_12L0noTIS_8", 1.)
If_12L0noTIS_9 = ROOT.RooRealVar("If_12L0noTIS_9","If_12L0noTIS_9", 1.)
If_12L0noTIS_10 = ROOT.RooRealVar("If_12L0noTIS_10","If_12L0noTIS_10", 1.)
If_12L0noTIS_11 = ROOT.RooRealVar("If_12L0noTIS_11","If_12L0noTIS_11", 1.)
If_12L0noTIS_12 = ROOT.RooRealVar("If_12L0noTIS_12","If_12L0noTIS_12", 1.)
If_12L0noTIS_13 = ROOT.RooRealVar("If_12L0noTIS_13","If_12L0noTIS_13", 1.)
If_12L0noTIS_14 = ROOT.RooRealVar("If_12L0noTIS_14","If_12L0noTIS_14", 1.)
If_12L0noTIS_15 = ROOT.RooRealVar("If_12L0noTIS_15","If_12L0noTIS_15", 1.)
If_12L0noTIS_16 = ROOT.RooRealVar("If_12L0noTIS_16","If_12L0noTIS_16", 1.)
If_12L0noTIS_17 = ROOT.RooRealVar("If_12L0noTIS_17","If_12L0noTIS_17", 1.)
If_12L0noTIS_18 = ROOT.RooRealVar("If_12L0noTIS_18","If_12L0noTIS_18", 1.)

# Integrals of the time dependent terms.
IT_cosh = ROOT.RooRealVar("IT_cosh","IT_cosh", 1.)
IT_sinh = ROOT.RooRealVar("IT_sinh","IT_sinh", 1.)
IT_cos = ROOT.RooRealVar("IT_cos","IT_cos", 1.)
IT_sin = ROOT.RooRealVar("IT_sin","IT_sin", 1.)
IT_11L0TIS_cosh = ROOT.RooRealVar("IT_11L0TIS_cosh","IT_11L0TIS_cosh", 1.)
IT_11L0TIS_sinh = ROOT.RooRealVar("IT_11L0TIS_sinh","IT_11L0TIS_sinh", 1.)
IT_11L0TIS_cos = ROOT.RooRealVar("IT_11L0TIS_cos","IT_11L0TIS_cos", 1.)
IT_11L0TIS_sin = ROOT.RooRealVar("IT_11L0TIS_sin","IT_11L0TIS_sin", 1.)
IT_11L0noTIS_cosh = ROOT.RooRealVar("IT_11L0noTIS_cosh","IT_11L0noTIS_cosh", 1.)
IT_11L0noTIS_sinh = ROOT.RooRealVar("IT_11L0noTIS_sinh","IT_11L0noTIS_sinh", 1.)
IT_11L0noTIS_cos = ROOT.RooRealVar("IT_11L0noTIS_cos","IT_11L0noTIS_cos", 1.)
IT_11L0noTIS_sin = ROOT.RooRealVar("IT_11L0noTIS_sin","IT_11L0noTIS_sin", 1.)
IT_12L0TIS_cosh = ROOT.RooRealVar("IT_12L0TIS_cosh","IT_12L0TIS_cosh", 1.)
IT_12L0TIS_sinh = ROOT.RooRealVar("IT_12L0TIS_sinh","IT_12L0TIS_sinh", 1.)
IT_12L0TIS_cos = ROOT.RooRealVar("IT_12L0TIS_cos","IT_12L0TIS_cos", 1.)
IT_12L0TIS_sin = ROOT.RooRealVar("IT_12L0TIS_sin","IT_12L0TIS_sin", 1.)
IT_12L0noTIS_cosh = ROOT.RooRealVar("IT_12L0noTIS_cosh","IT_12L0noTIS_cosh", 1.)
IT_12L0noTIS_sinh = ROOT.RooRealVar("IT_12L0noTIS_sinh","IT_12L0noTIS_sinh", 1.)
IT_12L0noTIS_cos = ROOT.RooRealVar("IT_12L0noTIS_cos","IT_12L0noTIS_cos", 1.)
IT_12L0noTIS_sin = ROOT.RooRealVar("IT_12L0noTIS_sin","IT_12L0noTIS_sin", 1.)

# Simultaneous fit categories.
yeartrigcat = ROOT.RooCategory("YearTrigCat","YearTrigCat")
yeartrigcat.defineType("2011_L0TIS")
yeartrigcat.defineType("2011_L0noTIS")
yeartrigcat.defineType("2012_L0TIS")
yeartrigcat.defineType("2012_L0noTIS")


# ################################################################
# M O R E   V A R I A B L E S
# ################################################################

# Auxiliar variables.
zero = ROOT.RooRealVar("zero","zero",0.)
one = ROOT.RooRealVar("one","one",1.)

# Four body invariant mass.
mKpKp = ROOT.RooRealVar(mKpiKpi_name,"M(K^{+}#pi^{-}K^{-}#pi^{+}) ",5365-450,5365+450,"MeV/c^{2}")

# s-Weights.
weight_fit = ROOT.RooRealVar(weight_name+"_fit","weight_fit",-100.,100.,"")
weight_plot = ROOT.RooRealVar(weight_name+"_plot","weight_plot",-100.,100.,"")
FullArgSetFitWide = ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,yeartrigcat,weight_fit)
FullArgSetPlotWide = ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,yeartrigcat,weight_plot)
FullArgSetFitNarrow = ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,yeartrigcat,weight_fit)
FullArgSetPlotNarrow = ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,yeartrigcat,weight_plot)

# Frames.
frame_m1 = mKp1.frame(ROOT.RooFit.Title("m1"))
frame_m2 = mKp2.frame(ROOT.RooFit.Title("m2"))
frame_m1_narrowwin = mKp1_narrowwin.frame(ROOT.RooFit.Title("m1"))
frame_m2_narrowwin = mKp2_narrowwin.frame(ROOT.RooFit.Title("m2"))
frame_cos1 = cos1.frame(ROOT.RooFit.Title("cos1"))
frame_cos2 = cos2.frame(ROOT.RooFit.Title("cos2"))
frame_phi = phi.frame(ROOT.RooFit.Title("phi"))
frame_t = t.frame(ROOT.RooFit.Title("t"))
frame_terr = terror.frame(ROOT.RooFit.Title("terr"))
frame_eta_SSK = etamistag_SSK.frame(ROOT.RooFit.Title("eta_SSK"))
frame_eta_OS = etamistag_OS.frame(ROOT.RooFit.Title("eta_OS"))
for fr in [frame_m1,frame_m2,frame_m1_narrowwin,frame_m2_narrowwin,frame_cos1,frame_cos2,frame_phi,frame_t]:
	fr.GetXaxis().SetTitleSize(0.06)
	fr.GetYaxis().SetTitleSize(0.06)
	fr.GetXaxis().SetLabelSize(0.06)
	fr.GetYaxis().SetLabelSize(0.06)


# ################################################################
# L I S T S   O F   A R G U M E N T S
# ################################################################

options = [wide_window_opt,year_opt,trig_opt,alt_fit,option,inftres,acctype,A_j1,A_j2,A_h,A_j1p,A_j2p,A_hp,qcomp]
options_11L0TIS = [wide_window_opt,zero,zero,alt_fit,option,inftres,acctype,A_j1,A_j2,A_h,A_j1p,A_j2p,A_hp,qcomp]
options_11L0noTIS = [wide_window_opt,zero,one,alt_fit,option,inftres,acctype,A_j1,A_j2,A_h,A_j1p,A_j2p,A_hp,qcomp]
options_12L0TIS = [wide_window_opt,one,zero,alt_fit,option,inftres,acctype,A_j1,A_j2,A_h,A_j1p,A_j2p,A_hp,qcomp]
options_12L0noTIS = [wide_window_opt,one,one,alt_fit,option,inftres,acctype,A_j1,A_j2,A_h,A_j1p,A_j2p,A_hp,qcomp]

observables = [decision_SSK,decision_OS,etamistag_SSK,etamistag_OS,mKp1,mKp2,cos1,cos2,phi,t,terror]
observables_narrowwin = [decision_SSK,decision_OS,etamistag_SSK,etamistag_OS,mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,terror]

re_amps = [reA00,reA01,reA10,reA02,reA20,reA110,reA11par,reA11perp,reA120,reA12par,reA12perp,\
reA210,reA21par,reA21perp,reA220,reA22par,reA22perp,reA22par2,reA22perp2]

dirCP_asyms = [DCP_SS_withBlinding,DCP_SV_withBlinding,DCP_VS_withBlinding,DCP_ST_withBlinding,DCP_TS_withBlinding,\
DCP_withBlinding,DCP_VT_withBlinding,DCP_TV_withBlinding,DCP_TT_withBlinding]
dirCP_asyms_unblinded = [DCP_SS,DCP_SV,DCP_VS,DCP_ST,DCP_TS,DCP,DCP_VT,DCP_TV,DCP_TT]
dirCP_asyms_narrowwin = [DCP_SS_withBlinding,DCP_SV_withBlinding,DCP_VS_withBlinding,zero,zero,DCP_withBlinding,zero,zero,zero]
dirCP_asyms_narrowwin_unblinded = [DCP_SS,DCP_SV,DCP_VS,zero,zero,DCP,zero,zero,zero]
dirCP_asyms_noCP = [zero,zero,zero,zero,zero,zero,zero,zero,zero]
dirCP_asyms_sameCP = [zero,zero,zero,zero,zero,DCP_withBlinding,zero,zero,zero]
dirCP_asyms_sameCP_unblinded = [zero,zero,zero,zero,zero,DCP,zero,zero,zero]
dirCP_asyms_sameCP_narrowwin = [zero,zero,zero,zero,zero,DCP_withBlinding,zero,zero,zero]
dirCP_asyms_sameCP_narrowwin_unblinded = [zero,zero,zero,zero,zero,DCP,zero,zero,zero]

im_amps = [imA00,imA01,imA10,imA02,imA20,imA110,imA11par,imA11perp,imA120,imA12par,imA12perp,\
imA210,imA21par,imA21perp,imA220,imA22par,imA22perp,imA22par2,imA22perp2]

weak_phases = [phis_withBlinding,dphi_SS_withBlinding,dphi_SV_withBlinding,dphi_VS_withBlinding,dphi_ST_withBlinding,\
dphi_TS_withBlinding,dphi_VT_withBlinding,dphi_TV_withBlinding,dphi_TT_withBlinding]
weak_phases_unblinded = [phis,dphi_SS,dphi_SV,dphi_VS,dphi_ST,dphi_TS,dphi_VT,dphi_TV,dphi_TT]
weak_phases_narrowwin = [phis_withBlinding,dphi_SS_withBlinding,dphi_SV_withBlinding,dphi_VS_withBlinding,zero,zero,zero,zero,zero]
weak_phases_narrowwin_unblinded = [phis,dphi_SS,dphi_SV,dphi_VS,zero,zero,zero,zero,zero]
weak_phases_noCP = [zero,zero,zero,zero,zero,zero,zero,zero,zero]
weak_phases_sameCP = [phis_withBlinding,zero,zero,zero,zero,zero,zero,zero,zero]
weak_phases_sameCP_unblinded = [phis,zero,zero,zero,zero,zero,zero,zero,zero]

mixing_params = [delta_m_Bs,gamma_Bs,delta_gamma_Bs]

calib_params = [p0metac_SSK,p0metac_OS,Dp0half_SSK,Dp0half_OS,p1_SSK,p1_OS,Dp1half_SSK,Dp1half_OS,etac_SSK,etac_OS,tres_deltatmean_2011,tres_p0_2011,tres_p1_2011,tres_deltatmean_2012,tres_p0_2012,tres_p1_2012,mV,mS,mT,\
gammaV,gammaS,gammaT,c1_mass_swave,c2_mass_swave,c3_mass_swave,c4_mass_swave,c5_mass_swave,c6_mass_swave,c7_mass_swave,c8_mass_swave,c9_mass_swave,res_mass]
calib_params_aux = [p0metac_SSK,p0metac_OS,Dp0half_SSK,Dp0half_OS,p1_SSK,p1_OS,Dp1half_SSK,Dp1half_OS,etac_SSK,etac_OS,tres_deltatmean_2011,tres_p0_2011,tres_p1_2011,tres_deltatmean_2012,tres_p0_2012,tres_p1_2012,mV,mS,mT,\
gammaV,gammaS,gammaT,c1_mass_swave,c2_mass_swave,c3_mass_swave,c4_mass_swave,c5_mass_swave,c6_mass_swave,c7_mass_swave,c8_mass_swave,c9_mass_swave,res_mass]

cond_distr_params = [tag_eff_SSK,mu1_SSK,sigma1_SSK,c_SSK,mu2_SSK,sigma2_SSK,tag_eff_OS,mu1_OS,sigma1_OS,c_OS,mu2_OS,sigma2_OS,gamma1_dt,beta1_dt,c_dt,gamma2_dt,beta2_dt]

sys_studies = [pw_mass_altmodel,f_1410_rel2_892,delta_1410_rel2_892,f_1680_rel2_892,delta_1680_rel2_892]

mass_integrals = [Im00,Im01,Im10,Im02,Im20,Im11,Im12,Im21,Im22,Ih1Re,Ih2Re,Ih3Re,Ih4Re,Ih5Re,Ih6Re,Ih7Re,Ih8Re,Ih9Re,\
Ih10Re,Ih11Re,Ih12Re,Ih13Re,Ih14Re,Ih15Re,Ih16Re,Ih17Re,Ih18Re,Ih19Re,Ih20Re,Ih21Re,Ih22Re,Ih23Re,Ih24Re,Ih25Re,Ih26Re,Ih27Re,Ih28Re,Ih29Re,Ih30Re,Ih1Im,Ih2Im,Ih3Im,Ih4Im,Ih5Im,\
Ih6Im,Ih7Im,Ih8Im,Ih9Im,Ih10Im,Ih11Im,Ih12Im,Ih13Im,Ih14Im,Ih15Im,Ih16Im,Ih17Im,Ih18Im,Ih19Im,Ih20Im,Ih21Im]
mass_integrals_narrowwin = [Im00_narrowwin,Im01_narrowwin,Im10_narrowwin,Im02_narrowwin,Im20_narrowwin,Im11_narrowwin,Im12_narrowwin,Im21_narrowwin,Im22_narrowwin,Ih1Re,Ih2Re,Ih3Re,Ih4Re,Ih5Re,Ih6Re,Ih7Re,Ih8Re,Ih9Re,\
Ih10Re,Ih11Re,Ih12Re,Ih13Re,Ih14Re,Ih15Re,Ih16Re,Ih17Re,Ih18Re,Ih19Re,Ih20Re,Ih21Re,Ih22Re,Ih23Re,Ih24Re,Ih25Re,Ih26Re,Ih27Re,Ih28Re,Ih29Re,Ih30Re,Ih1Im,Ih2Im,Ih3Im,Ih4Im,Ih5Im,\
Ih6Im,Ih7Im,Ih8Im,Ih9Im,Ih10Im,Ih11Im,Ih12Im,Ih13Im,Ih14Im,Ih15Im,Ih16Im,Ih17Im,Ih18Im,Ih19Im,Ih20Im,Ih21Im]
mass_integrals_11L0TIS = [Im_11L0TIS_00,Im_11L0TIS_01,Im_11L0TIS_10,Im_11L0TIS_02,Im_11L0TIS_20,Im_11L0TIS_11,Im_11L0TIS_12,Im_11L0TIS_21,Im_11L0TIS_22,Ih_11L0TIS_1Re,Ih_11L0TIS_2Re,\
Ih_11L0TIS_3Re,Ih_11L0TIS_4Re,Ih_11L0TIS_5Re,Ih_11L0TIS_6Re,Ih_11L0TIS_7Re,Ih_11L0TIS_8Re,Ih_11L0TIS_9Re,\
Ih_11L0TIS_10Re,Ih_11L0TIS_11Re,Ih_11L0TIS_12Re,Ih_11L0TIS_13Re,Ih_11L0TIS_14Re,Ih_11L0TIS_15Re,Ih_11L0TIS_16Re,Ih_11L0TIS_17Re,Ih_11L0TIS_18Re,Ih_11L0TIS_19Re,Ih_11L0TIS_20Re,\
Ih_11L0TIS_21Re,Ih_11L0TIS_22Re,Ih_11L0TIS_23Re,Ih_11L0TIS_24Re,Ih_11L0TIS_25Re,Ih_11L0TIS_26Re,Ih_11L0TIS_27Re,Ih_11L0TIS_28Re,Ih_11L0TIS_29Re,Ih_11L0TIS_30Re,Ih_11L0TIS_1Im,Ih_11L0TIS_2Im,\
Ih_11L0TIS_3Im,Ih_11L0TIS_4Im,Ih_11L0TIS_5Im,Ih_11L0TIS_6Im,Ih_11L0TIS_7Im,Ih_11L0TIS_8Im,Ih_11L0TIS_9Im,Ih_11L0TIS_10Im,Ih_11L0TIS_11Im,Ih_11L0TIS_12Im,Ih_11L0TIS_13Im,\
Ih_11L0TIS_14Im,Ih_11L0TIS_15Im,Ih_11L0TIS_16Im,Ih_11L0TIS_17Im,Ih_11L0TIS_18Im,Ih_11L0TIS_19Im,Ih_11L0TIS_20Im,Ih_11L0TIS_21Im]
mass_integrals_narrowwin_11L0TIS = [Im_11L0TIS_00_narrowwin,Im_11L0TIS_01_narrowwin,Im_11L0TIS_10_narrowwin,Im_11L0TIS_02_narrowwin,Im_11L0TIS_20_narrowwin,Im_11L0TIS_11_narrowwin,Im_11L0TIS_12_narrowwin,\
Im_11L0TIS_21_narrowwin,Im_11L0TIS_22_narrowwin,Ih_11L0TIS_1Re,Ih_11L0TIS_2Re,Ih_11L0TIS_3Re,Ih_11L0TIS_4Re,Ih_11L0TIS_5Re,Ih_11L0TIS_6Re,Ih_11L0TIS_7Re,Ih_11L0TIS_8Re,Ih_11L0TIS_9Re,\
Ih_11L0TIS_10Re,Ih_11L0TIS_11Re,Ih_11L0TIS_12Re,Ih_11L0TIS_13Re,Ih_11L0TIS_14Re,Ih_11L0TIS_15Re,Ih_11L0TIS_16Re,Ih_11L0TIS_17Re,Ih_11L0TIS_18Re,Ih_11L0TIS_19Re,Ih_11L0TIS_20Re,\
Ih_11L0TIS_21Re,Ih_11L0TIS_22Re,Ih_11L0TIS_23Re,Ih_11L0TIS_24Re,Ih_11L0TIS_25Re,Ih_11L0TIS_26Re,Ih_11L0TIS_27Re,Ih_11L0TIS_28Re,Ih_11L0TIS_29Re,Ih_11L0TIS_30Re,Ih_11L0TIS_1Im,Ih_11L0TIS_2Im,\
Ih_11L0TIS_3Im,Ih_11L0TIS_4Im,Ih_11L0TIS_5Im,Ih_11L0TIS_6Im,Ih_11L0TIS_7Im,Ih_11L0TIS_8Im,Ih_11L0TIS_9Im,Ih_11L0TIS_10Im,Ih_11L0TIS_11Im,Ih_11L0TIS_12Im,Ih_11L0TIS_13Im,\
Ih_11L0TIS_14Im,Ih_11L0TIS_15Im,Ih_11L0TIS_16Im,Ih_11L0TIS_17Im,Ih_11L0TIS_18Im,Ih_11L0TIS_19Im,Ih_11L0TIS_20Im,Ih_11L0TIS_21Im]
mass_integrals_11L0noTIS = [Im_11L0noTIS_00,Im_11L0noTIS_01,Im_11L0noTIS_10,Im_11L0noTIS_02,Im_11L0noTIS_20,Im_11L0noTIS_11,Im_11L0noTIS_12,Im_11L0noTIS_21,Im_11L0noTIS_22,Ih_11L0noTIS_1Re,Ih_11L0noTIS_2Re,\
Ih_11L0noTIS_3Re,Ih_11L0noTIS_4Re,Ih_11L0noTIS_5Re,Ih_11L0noTIS_6Re,Ih_11L0noTIS_7Re,Ih_11L0noTIS_8Re,Ih_11L0noTIS_9Re,\
Ih_11L0noTIS_10Re,Ih_11L0noTIS_11Re,Ih_11L0noTIS_12Re,Ih_11L0noTIS_13Re,Ih_11L0noTIS_14Re,Ih_11L0noTIS_15Re,Ih_11L0noTIS_16Re,Ih_11L0noTIS_17Re,Ih_11L0noTIS_18Re,Ih_11L0noTIS_19Re,Ih_11L0noTIS_20Re,\
Ih_11L0noTIS_21Re,Ih_11L0noTIS_22Re,Ih_11L0noTIS_23Re,Ih_11L0noTIS_24Re,Ih_11L0noTIS_25Re,Ih_11L0noTIS_26Re,Ih_11L0noTIS_27Re,Ih_11L0noTIS_28Re,Ih_11L0noTIS_29Re,Ih_11L0noTIS_30Re,Ih_11L0noTIS_1Im,Ih_11L0noTIS_2Im,\
Ih_11L0noTIS_3Im,Ih_11L0noTIS_4Im,Ih_11L0noTIS_5Im,Ih_11L0noTIS_6Im,Ih_11L0noTIS_7Im,Ih_11L0noTIS_8Im,Ih_11L0noTIS_9Im,Ih_11L0noTIS_10Im,Ih_11L0noTIS_11Im,Ih_11L0noTIS_12Im,Ih_11L0noTIS_13Im,\
Ih_11L0noTIS_14Im,Ih_11L0noTIS_15Im,Ih_11L0noTIS_16Im,Ih_11L0noTIS_17Im,Ih_11L0noTIS_18Im,Ih_11L0noTIS_19Im,Ih_11L0noTIS_20Im,Ih_11L0noTIS_21Im]
mass_integrals_narrowwin_11L0noTIS = [Im_11L0noTIS_00_narrowwin,Im_11L0noTIS_01_narrowwin,Im_11L0noTIS_10_narrowwin,Im_11L0noTIS_02_narrowwin,Im_11L0noTIS_20_narrowwin,Im_11L0noTIS_11_narrowwin,Im_11L0noTIS_12_narrowwin,\
Im_11L0noTIS_21_narrowwin,Im_11L0noTIS_22_narrowwin,Ih_11L0noTIS_1Re,Ih_11L0noTIS_2Re,Ih_11L0noTIS_3Re,Ih_11L0noTIS_4Re,Ih_11L0noTIS_5Re,Ih_11L0noTIS_6Re,Ih_11L0noTIS_7Re,Ih_11L0noTIS_8Re,Ih_11L0noTIS_9Re,\
Ih_11L0noTIS_10Re,Ih_11L0noTIS_11Re,Ih_11L0noTIS_12Re,Ih_11L0noTIS_13Re,Ih_11L0noTIS_14Re,Ih_11L0noTIS_15Re,Ih_11L0noTIS_16Re,Ih_11L0noTIS_17Re,Ih_11L0noTIS_18Re,Ih_11L0noTIS_19Re,Ih_11L0noTIS_20Re,\
Ih_11L0noTIS_21Re,Ih_11L0noTIS_22Re,Ih_11L0noTIS_23Re,Ih_11L0noTIS_24Re,Ih_11L0noTIS_25Re,Ih_11L0noTIS_26Re,Ih_11L0noTIS_27Re,Ih_11L0noTIS_28Re,Ih_11L0noTIS_29Re,Ih_11L0noTIS_30Re,Ih_11L0noTIS_1Im,Ih_11L0noTIS_2Im,\
Ih_11L0noTIS_3Im,Ih_11L0noTIS_4Im,Ih_11L0noTIS_5Im,Ih_11L0noTIS_6Im,Ih_11L0noTIS_7Im,Ih_11L0noTIS_8Im,Ih_11L0noTIS_9Im,Ih_11L0noTIS_10Im,Ih_11L0noTIS_11Im,Ih_11L0noTIS_12Im,Ih_11L0noTIS_13Im,\
Ih_11L0noTIS_14Im,Ih_11L0noTIS_15Im,Ih_11L0noTIS_16Im,Ih_11L0noTIS_17Im,Ih_11L0noTIS_18Im,Ih_11L0noTIS_19Im,Ih_11L0noTIS_20Im,Ih_11L0noTIS_21Im]
mass_integrals_12L0TIS = [Im_12L0TIS_00,Im_12L0TIS_01,Im_12L0TIS_10,Im_12L0TIS_02,Im_12L0TIS_20,Im_12L0TIS_11,Im_12L0TIS_12,Im_12L0TIS_21,Im_12L0TIS_22,Ih_12L0TIS_1Re,Ih_12L0TIS_2Re,\
Ih_12L0TIS_3Re,Ih_12L0TIS_4Re,Ih_12L0TIS_5Re,Ih_12L0TIS_6Re,Ih_12L0TIS_7Re,Ih_12L0TIS_8Re,Ih_12L0TIS_9Re,\
Ih_12L0TIS_10Re,Ih_12L0TIS_11Re,Ih_12L0TIS_12Re,Ih_12L0TIS_13Re,Ih_12L0TIS_14Re,Ih_12L0TIS_15Re,Ih_12L0TIS_16Re,Ih_12L0TIS_17Re,Ih_12L0TIS_18Re,Ih_12L0TIS_19Re,Ih_12L0TIS_20Re,\
Ih_12L0TIS_21Re,Ih_12L0TIS_22Re,Ih_12L0TIS_23Re,Ih_12L0TIS_24Re,Ih_12L0TIS_25Re,Ih_12L0TIS_26Re,Ih_12L0TIS_27Re,Ih_12L0TIS_28Re,Ih_12L0TIS_29Re,Ih_12L0TIS_30Re,Ih_12L0TIS_1Im,Ih_12L0TIS_2Im,\
Ih_12L0TIS_3Im,Ih_12L0TIS_4Im,Ih_12L0TIS_5Im,Ih_12L0TIS_6Im,Ih_12L0TIS_7Im,Ih_12L0TIS_8Im,Ih_12L0TIS_9Im,Ih_12L0TIS_10Im,Ih_12L0TIS_11Im,Ih_12L0TIS_12Im,Ih_12L0TIS_13Im,\
Ih_12L0TIS_14Im,Ih_12L0TIS_15Im,Ih_12L0TIS_16Im,Ih_12L0TIS_17Im,Ih_12L0TIS_18Im,Ih_12L0TIS_19Im,Ih_12L0TIS_20Im,Ih_12L0TIS_21Im]
mass_integrals_narrowwin_12L0TIS = [Im_12L0TIS_00_narrowwin,Im_12L0TIS_01_narrowwin,Im_12L0TIS_10_narrowwin,Im_12L0TIS_02_narrowwin,Im_12L0TIS_20_narrowwin,Im_12L0TIS_11_narrowwin,Im_12L0TIS_12_narrowwin,\
Im_12L0TIS_21_narrowwin,Im_12L0TIS_22_narrowwin,Ih_12L0TIS_1Re,Ih_12L0TIS_2Re,Ih_12L0TIS_3Re,Ih_12L0TIS_4Re,Ih_12L0TIS_5Re,Ih_12L0TIS_6Re,Ih_12L0TIS_7Re,Ih_12L0TIS_8Re,Ih_12L0TIS_9Re,\
Ih_12L0TIS_10Re,Ih_12L0TIS_11Re,Ih_12L0TIS_12Re,Ih_12L0TIS_13Re,Ih_12L0TIS_14Re,Ih_12L0TIS_15Re,Ih_12L0TIS_16Re,Ih_12L0TIS_17Re,Ih_12L0TIS_18Re,Ih_12L0TIS_19Re,Ih_12L0TIS_20Re,\
Ih_12L0TIS_21Re,Ih_12L0TIS_22Re,Ih_12L0TIS_23Re,Ih_12L0TIS_24Re,Ih_12L0TIS_25Re,Ih_12L0TIS_26Re,Ih_12L0TIS_27Re,Ih_12L0TIS_28Re,Ih_12L0TIS_29Re,Ih_12L0TIS_30Re,Ih_12L0TIS_1Im,Ih_12L0TIS_2Im,\
Ih_12L0TIS_3Im,Ih_12L0TIS_4Im,Ih_12L0TIS_5Im,Ih_12L0TIS_6Im,Ih_12L0TIS_7Im,Ih_12L0TIS_8Im,Ih_12L0TIS_9Im,Ih_12L0TIS_10Im,Ih_12L0TIS_11Im,Ih_12L0TIS_12Im,Ih_12L0TIS_13Im,\
Ih_12L0TIS_14Im,Ih_12L0TIS_15Im,Ih_12L0TIS_16Im,Ih_12L0TIS_17Im,Ih_12L0TIS_18Im,Ih_12L0TIS_19Im,Ih_12L0TIS_20Im,Ih_12L0TIS_21Im]
mass_integrals_12L0noTIS = [Im_12L0noTIS_00,Im_12L0noTIS_01,Im_12L0noTIS_10,Im_12L0noTIS_02,Im_12L0noTIS_20,Im_12L0noTIS_11,Im_12L0noTIS_12,Im_12L0noTIS_21,Im_12L0noTIS_22,Ih_12L0noTIS_1Re,Ih_12L0noTIS_2Re,\
Ih_12L0noTIS_3Re,Ih_12L0noTIS_4Re,Ih_12L0noTIS_5Re,Ih_12L0noTIS_6Re,Ih_12L0noTIS_7Re,Ih_12L0noTIS_8Re,Ih_12L0noTIS_9Re,\
Ih_12L0noTIS_10Re,Ih_12L0noTIS_11Re,Ih_12L0noTIS_12Re,Ih_12L0noTIS_13Re,Ih_12L0noTIS_14Re,Ih_12L0noTIS_15Re,Ih_12L0noTIS_16Re,Ih_12L0noTIS_17Re,Ih_12L0noTIS_18Re,Ih_12L0noTIS_19Re,Ih_12L0noTIS_20Re,\
Ih_12L0noTIS_21Re,Ih_12L0noTIS_22Re,Ih_12L0noTIS_23Re,Ih_12L0noTIS_24Re,Ih_12L0noTIS_25Re,Ih_12L0noTIS_26Re,Ih_12L0noTIS_27Re,Ih_12L0noTIS_28Re,Ih_12L0noTIS_29Re,Ih_12L0noTIS_30Re,Ih_12L0noTIS_1Im,Ih_12L0noTIS_2Im,\
Ih_12L0noTIS_3Im,Ih_12L0noTIS_4Im,Ih_12L0noTIS_5Im,Ih_12L0noTIS_6Im,Ih_12L0noTIS_7Im,Ih_12L0noTIS_8Im,Ih_12L0noTIS_9Im,Ih_12L0noTIS_10Im,Ih_12L0noTIS_11Im,Ih_12L0noTIS_12Im,Ih_12L0noTIS_13Im,\
Ih_12L0noTIS_14Im,Ih_12L0noTIS_15Im,Ih_12L0noTIS_16Im,Ih_12L0noTIS_17Im,Ih_12L0noTIS_18Im,Ih_12L0noTIS_19Im,Ih_12L0noTIS_20Im,Ih_12L0noTIS_21Im]
mass_integrals_narrowwin_12L0noTIS = [Im_12L0noTIS_00_narrowwin,Im_12L0noTIS_01_narrowwin,Im_12L0noTIS_10_narrowwin,Im_12L0noTIS_02_narrowwin,Im_12L0noTIS_20_narrowwin,Im_12L0noTIS_11_narrowwin,Im_12L0noTIS_12_narrowwin,\
Im_12L0noTIS_21_narrowwin,Im_12L0noTIS_22_narrowwin,Ih_12L0noTIS_1Re,Ih_12L0noTIS_2Re,Ih_12L0noTIS_3Re,Ih_12L0noTIS_4Re,Ih_12L0noTIS_5Re,Ih_12L0noTIS_6Re,Ih_12L0noTIS_7Re,Ih_12L0noTIS_8Re,Ih_12L0noTIS_9Re,\
Ih_12L0noTIS_10Re,Ih_12L0noTIS_11Re,Ih_12L0noTIS_12Re,Ih_12L0noTIS_13Re,Ih_12L0noTIS_14Re,Ih_12L0noTIS_15Re,Ih_12L0noTIS_16Re,Ih_12L0noTIS_17Re,Ih_12L0noTIS_18Re,Ih_12L0noTIS_19Re,Ih_12L0noTIS_20Re,\
Ih_12L0noTIS_21Re,Ih_12L0noTIS_22Re,Ih_12L0noTIS_23Re,Ih_12L0noTIS_24Re,Ih_12L0noTIS_25Re,Ih_12L0noTIS_26Re,Ih_12L0noTIS_27Re,Ih_12L0noTIS_28Re,Ih_12L0noTIS_29Re,Ih_12L0noTIS_30Re,Ih_12L0noTIS_1Im,Ih_12L0noTIS_2Im,\
Ih_12L0noTIS_3Im,Ih_12L0noTIS_4Im,Ih_12L0noTIS_5Im,Ih_12L0noTIS_6Im,Ih_12L0noTIS_7Im,Ih_12L0noTIS_8Im,Ih_12L0noTIS_9Im,Ih_12L0noTIS_10Im,Ih_12L0noTIS_11Im,Ih_12L0noTIS_12Im,Ih_12L0noTIS_13Im,\
Ih_12L0noTIS_14Im,Ih_12L0noTIS_15Im,Ih_12L0noTIS_16Im,Ih_12L0noTIS_17Im,Ih_12L0noTIS_18Im,Ih_12L0noTIS_19Im,Ih_12L0noTIS_20Im,Ih_12L0noTIS_21Im]

ang_integrals = [If1,If2,If3,If4,If5,If6,If7,If8,If9,If10,If11,If12,If13,If14,If15,If16,If17,If18]
ang_integrals_11L0TIS = [If_11L0TIS_1,If_11L0TIS_2,If_11L0TIS_3,If_11L0TIS_4,If_11L0TIS_5,If_11L0TIS_6,If_11L0TIS_7,If_11L0TIS_8,If_11L0TIS_9,If_11L0TIS_10,If_11L0TIS_11,If_11L0TIS_12,If_11L0TIS_13,\
If_11L0TIS_14,If_11L0TIS_15,If_11L0TIS_16,If_11L0TIS_17,If_11L0TIS_18]
ang_integrals_11L0noTIS = [If_11L0noTIS_1,If_11L0noTIS_2,If_11L0noTIS_3,If_11L0noTIS_4,If_11L0noTIS_5,If_11L0noTIS_6,If_11L0noTIS_7,If_11L0noTIS_8,If_11L0noTIS_9,If_11L0noTIS_10,If_11L0noTIS_11,If_11L0noTIS_12,If_11L0noTIS_13,\
If_11L0noTIS_14,If_11L0noTIS_15,If_11L0noTIS_16,If_11L0noTIS_17,If_11L0noTIS_18]
ang_integrals_12L0TIS = [If_12L0TIS_1,If_12L0TIS_2,If_12L0TIS_3,If_12L0TIS_4,If_12L0TIS_5,If_12L0TIS_6,If_12L0TIS_7,If_12L0TIS_8,If_12L0TIS_9,If_12L0TIS_10,If_12L0TIS_11,If_12L0TIS_12,If_12L0TIS_13,\
If_12L0TIS_14,If_12L0TIS_15,If_12L0TIS_16,If_12L0TIS_17,If_12L0TIS_18]
ang_integrals_12L0noTIS = [If_12L0noTIS_1,If_12L0noTIS_2,If_12L0noTIS_3,If_12L0noTIS_4,If_12L0noTIS_5,If_12L0noTIS_6,If_12L0noTIS_7,If_12L0noTIS_8,If_12L0noTIS_9,If_12L0noTIS_10,If_12L0noTIS_11,If_12L0noTIS_12,If_12L0noTIS_13,\
If_12L0noTIS_14,If_12L0noTIS_15,If_12L0noTIS_16,If_12L0noTIS_17,If_12L0noTIS_18]

time_integrals = [IT_cosh,IT_sinh,IT_cos,IT_sin]
time_integrals_11L0TIS = [IT_11L0TIS_cosh,IT_11L0TIS_sinh,IT_11L0TIS_cos,IT_11L0TIS_sin]
time_integrals_11L0noTIS = [IT_11L0noTIS_cosh,IT_11L0noTIS_sinh,IT_11L0noTIS_cos,IT_11L0noTIS_sin]
time_integrals_12L0TIS = [IT_12L0TIS_cosh,IT_12L0TIS_sinh,IT_12L0TIS_cos,IT_12L0TIS_sin]
time_integrals_12L0noTIS = [IT_12L0noTIS_cosh,IT_12L0noTIS_sinh,IT_12L0noTIS_cos,IT_12L0noTIS_sin]

options_list = ROOT.RooArgList()
options_11L0TIS_list = ROOT.RooArgList()
options_11L0noTIS_list = ROOT.RooArgList()
options_12L0TIS_list = ROOT.RooArgList()
options_12L0noTIS_list = ROOT.RooArgList()
observables_list = ROOT.RooArgList()
re_amps_list = ROOT.RooArgList()
dirCP_asyms_list = ROOT.RooArgList()
dirCP_asyms_unblinded_list = ROOT.RooArgList()
im_amps_list = ROOT.RooArgList()
weak_phases_list = ROOT.RooArgList()
weak_phases_unblinded_list = ROOT.RooArgList()
mixing_params_list = ROOT.RooArgList()
calib_params_list = ROOT.RooArgList()
cond_distr_params_list = ROOT.RooArgList()
sys_studies_list = ROOT.RooArgList()
mass_integrals_list = ROOT.RooArgList()
ang_integrals_list = ROOT.RooArgList()
time_integrals_list = ROOT.RooArgList()
mass_integrals_11L0TIS_list = ROOT.RooArgList()
ang_integrals_11L0TIS_list = ROOT.RooArgList()
time_integrals_11L0TIS_list = ROOT.RooArgList()
mass_integrals_11L0noTIS_list = ROOT.RooArgList()
ang_integrals_11L0noTIS_list = ROOT.RooArgList()
time_integrals_11L0noTIS_list = ROOT.RooArgList()
mass_integrals_12L0TIS_list = ROOT.RooArgList()
ang_integrals_12L0TIS_list = ROOT.RooArgList()
time_integrals_12L0TIS_list = ROOT.RooArgList()
mass_integrals_12L0noTIS_list = ROOT.RooArgList()
ang_integrals_12L0noTIS_list = ROOT.RooArgList()
time_integrals_12L0noTIS_list = ROOT.RooArgList()

options_list_aux = ROOT.RooArgList()
observables_list_aux = ROOT.RooArgList()
observables_list_narrowwin_aux = ROOT.RooArgList()
re_amps_list_aux = ROOT.RooArgList()
dirCP_asyms_list_aux = ROOT.RooArgList()
im_amps_list_aux = ROOT.RooArgList()
weak_phases_list_aux = ROOT.RooArgList()
mixing_params_list_aux = ROOT.RooArgList()
calib_params_list_aux = ROOT.RooArgList()
cond_distr_params_list_aux = ROOT.RooArgList()
sys_studies_list_aux = ROOT.RooArgList()
mass_integrals_list_aux = ROOT.RooArgList()
mass_integrals_list_narrowwin_aux = ROOT.RooArgList()
ang_integrals_list_aux = ROOT.RooArgList()
time_integrals_list_aux = ROOT.RooArgList()

for argument in mass_integrals: mass_integrals_list.add(argument)
for argument in ang_integrals: ang_integrals_list.add(argument)
for argument in time_integrals: time_integrals_list.add(argument)
for argument in mass_integrals_11L0TIS: mass_integrals_11L0TIS_list.add(argument)
for argument in ang_integrals_11L0TIS: ang_integrals_11L0TIS_list.add(argument)
for argument in time_integrals_11L0TIS: time_integrals_11L0TIS_list.add(argument)
for argument in mass_integrals_11L0noTIS: mass_integrals_11L0noTIS_list.add(argument)
for argument in ang_integrals_11L0noTIS: ang_integrals_11L0noTIS_list.add(argument)
for argument in time_integrals_11L0noTIS: time_integrals_11L0noTIS_list.add(argument)
for argument in mass_integrals_12L0TIS: mass_integrals_12L0TIS_list.add(argument)
for argument in ang_integrals_12L0TIS: ang_integrals_12L0TIS_list.add(argument)
for argument in time_integrals_12L0TIS: time_integrals_12L0TIS_list.add(argument)
for argument in mass_integrals_12L0noTIS: mass_integrals_12L0noTIS_list.add(argument)
for argument in ang_integrals_12L0noTIS: ang_integrals_12L0noTIS_list.add(argument)
for argument in time_integrals_12L0noTIS: time_integrals_12L0noTIS_list.add(argument)
