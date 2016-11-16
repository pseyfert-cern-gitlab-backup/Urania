from ROOT import *
from math import *
import time
import os
from parameters import *
gROOT.ProcessLine('.x ../../src/TimeDependent/KpiKpiSpectrumNW.cxx++')
gROOT.ProcessLine('.x ../../src/TimeDependent/ComputeIntegrals.cxx++')
gROOT.ProcessLine('.x ../../src/TimeDependent/accpdf.cxx++')
gROOT.ProcessLine('.x ../../src/TimeDependent/MCGenPHSP.cxx++')
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
mKp1_MC = RooRealVar(m1_name_MC,"M(K^{+}#pi^{-}) ", 750., 1700.,"MeV/c^{2}")
mKp2_MC = RooRealVar(m2_name_MC,"M(K^{-}#pi^{+}) ", 750., 1700.,"MeV/c^{2}")
mKp1_narrow_MC = RooRealVar(m1_name_MC,"M(K^{+}#pi^{-}) ",900.-150.,900.+150.,"MeV/c^{2}")
mKp2_narrow_MC = RooRealVar(m2_name_MC,"M(K^{-}#pi^{+}) ",900.-150.,900.+150.,"MeV/c^{2}")
cos1_MC = RooRealVar(cos1_name_MC,"cos(#theta_{1})", -1., 1.,"")
cos2_MC = RooRealVar(cos2_name_MC,"cos(#theta_{2})", -1., 1.,"")
phi_MC = RooRealVar(phi_name_MC,"#varphi",-pi,pi,"rad")
t_MC = RooRealVar(t_name_MC,"t_true",0.,12.,"ps")

# Parameters of the fit.
k1_2011_wide = RooRealVar("k1_2011_wide","k1_2011_wide",-0.363950428984,-1.,0.)
k2_2011_wide = RooRealVar("k2_2011_wide","k2_2011_wide",-0.591233116346,-1.,0.)
k3_2011_wide = RooRealVar("k3_2011_wide","k3_2011_wide",-0.000162287437021,-0.1,0.)
k4_2011_wide = RooRealVar("k4_2011_wide","k4_2011_wide",-0.00617497226242,-0.1,0.)
p1_2011_wide = RooRealVar("p1_2011_wide","p1_2011_wide",-0.000257416963069,-0.1,0.)
a_acc_2011_wide = RooRealVar("a_acc_2011_wide","a_acc_2011_wide",1.393,0.,2.)
b_acc_2011_wide = RooRealVar("b_acc_2011_wide","b_acc_2011_wide",0.0473,0.,0.1)
k1_2012_wide = RooRealVar("k1_2012_wide","k1_2012_wide",-0.359076822721,-1.,0.)
k2_2012_wide = RooRealVar("k2_2012_wide","k2_2012_wide",-0.585882892127,-1.,0.)
k3_2012_wide = RooRealVar("k3_2012_wide","k3_2012_wide",-0.000253018793601,-0.1,0.)
k4_2012_wide = RooRealVar("k4_2012_wide","k4_2012_wide",-0.00614023211683,-0.1,0.)
p1_2012_wide = RooRealVar("p1_2012_wide","p1_2012_wide",-0.000217681826821,-0.1,0.)
a_acc_2012_wide = RooRealVar("a_acc_2012_wide","a_acc_2012_wide",1.393,0.,2.)
b_acc_2012_wide = RooRealVar("b_acc_2012_wide","b_acc_2012_wide",0.0473,0.,0.1)
k1_2011_narrow = RooRealVar("k1_2011_narrow","k1_2011_narrow",-0.631741307569,-1.,0.)
k2_2011_narrow = RooRealVar("k2_2011_narrow","k2_2011_narrow",-0.404112585196,-1.,0.)
k3_2011_narrow = RooRealVar("k3_2011_narrow","k3_2011_narrow",-0.000874674740211,-0.1,0.)
k4_2011_narrow = RooRealVar("k4_2011_narrow","k4_2011_narrow",-0.000119319291944,-0.1,0.)
p1_2011_narrow = RooRealVar("p1_2011_narrow","p1_2011_narrow",-0.000331437635605,-0.1,0.)
a_acc_2011_narrow = RooRealVar("a_acc_2011_narrow","a_acc_2011_narrow",1.393,0.,2.)
b_acc_2011_narrow = RooRealVar("b_acc_2011_narrow","b_acc_2011_narrow",0.0473,0.,0.1)
k1_2012_narrow = RooRealVar("k1_2012_narrow","k1_2012_narrow",-0.617734228841,-1.,0.)
k2_2012_narrow = RooRealVar("k2_2012_narrow","k2_2012_narrow",-0.440024563998,-1.,0.)
k3_2012_narrow = RooRealVar("k3_2012_narrow","k3_2012_narrow",-0.000319014825644,-0.1,0.)
k4_2012_narrow = RooRealVar("k4_2012_narrow","k4_2012_narrow",-8.05845755325e-06,-0.1,0.)
p1_2012_narrow = RooRealVar("p1_2012_narrow","p1_2012_narrow",-0.000118168898876,-0.1,0.)
a_acc_2012_narrow = RooRealVar("a_acc_2012_narrow","a_acc_2012_narrow",1.393,0.,2.)
b_acc_2012_narrow = RooRealVar("b_acc_2012_narrow","b_acc_2012_narrow",0.0473,0.,0.1)

# Accurate time integrals.
IT_cosh_accu_2011_wide = RooRealVar("IT_cosh_accu_2011_wide","IT_cosh_accu_2011_wide",1.)
IT_sinh_accu_2011_wide = RooRealVar("IT_sinh_accu_2011_wide","IT_sinh_accu_2011_wide",1.)
IT_cos_accu_2011_wide = RooRealVar("IT_cos_accu_2011_wide","IT_cos_accu_2011_wide",1.)
IT_sin_accu_2011_wide = RooRealVar("IT_sin_accu_2011_wide","IT_sin_accu_2011_wide",1.)
IT_cosh_accu_2012_wide = RooRealVar("IT_cosh_accu_2012_wide","IT_cosh_accu_2012_wide",1.)
IT_sinh_accu_2012_wide = RooRealVar("IT_sinh_accu_2012_wide","IT_sinh_accu_2012_wide",1.)
IT_cos_accu_2012_wide = RooRealVar("IT_cos_accu_2012_wide","IT_cos_accu_2012_wide",1.)
IT_sin_accu_2012_wide = RooRealVar("IT_sin_accu_2012_wide","IT_sin_accu_2012_wide",1.)
IT_cosh_accu_2011_narrow = RooRealVar("IT_cosh_accu_2011_narrow","IT_cosh_accu_2011_narrow",1.)
IT_sinh_accu_2011_narrow = RooRealVar("IT_sinh_accu_2011_narrow","IT_sinh_accu_2011_narrow",1.)
IT_cos_accu_2011_narrow = RooRealVar("IT_cos_accu_2011_narrow","IT_cos_accu_2011_narrow",1.)
IT_sin_accu_2011_narrow = RooRealVar("IT_sin_accu_2011_narrow","IT_sin_accu_2011_narrow",1.)
IT_cosh_accu_2012_narrow = RooRealVar("IT_cosh_accu_2012_narrow","IT_cosh_accu_2012_narrow",1.)
IT_sinh_accu_2012_narrow = RooRealVar("IT_sinh_accu_2012_narrow","IT_sinh_accu_2012_narrow",1.)
IT_cos_accu_2012_narrow = RooRealVar("IT_cos_accu_2012_narrow","IT_cos_accu_2012_narrow",1.)
IT_sin_accu_2012_narrow = RooRealVar("IT_sin_accu_2012_narrow","IT_sin_accu_2012_narrow",1.)

# More variables.
opt_acc = RooRealVar("opt_acc","opt_acc",1)
wide_window_MC = RooRealVar("wide_window_MC","wide_window_MC",1)
opt_genmodel = RooRealVar("opt_genmodel","opt_genmodel",0)
MCweight0 = RooRealVar("MCweight0","MCweight0",1.)
MCweight1 = RooRealVar("MCweight1","MCweight1",1.)
MCweight2 = RooRealVar("MCweight2","MCweight2",1.)
MCweight3 = RooRealVar("MCweight3","MCweight3",1.)
MCweight4 = RooRealVar("MCweight4","MCweight4",1.)

# Datasets.
data1_2011_wide_ = RooDataSet("data1_2011_wide_","data1_2011_wide_",RooArgSet(mKp1_MC,mKp2_MC,MCweight1))
data1_2012_wide_ = RooDataSet("data1_2012_wide_","data1_2012_wide_",RooArgSet(mKp1_MC,mKp2_MC,MCweight1))
data2_2011_wide_ = RooDataSet("data2_2011_wide_","data2_2011_wide_",RooArgSet(cos1_MC,cos2_MC,MCweight2))
data2_2012_wide_ = RooDataSet("data2_2012_wide_","data2_2012_wide_",RooArgSet(cos1_MC,cos2_MC,MCweight2))
data3_2011_wide_ = RooDataSet("data3_2011_wide_","data3_2011_wide_",RooArgSet(phi_MC,MCweight3))
data3_2012_wide_ = RooDataSet("data3_2012_wide_","data3_2012_wide_",RooArgSet(phi_MC,MCweight3))
data4_2011_wide_ = RooDataSet("data4_2011_wide_","data4_2011_wide_",RooArgSet(t_MC,MCweight4))
data4_2012_wide_ = RooDataSet("data4_2012_wide_","data4_2012_wide_",RooArgSet(t_MC,MCweight4))
data1_2011_narrow_ = RooDataSet("data1_2011_narrow_","data1_2011_narrow_",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,MCweight1))
data1_2012_narrow_ = RooDataSet("data1_2012_narrow_","data1_2012_narrow_",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,MCweight1))
data2_2011_narrow_ = RooDataSet("data2_2011_narrow_","data2_2011_narrow_",RooArgSet(cos1_MC,cos2_MC,MCweight2))
data2_2012_narrow_ = RooDataSet("data2_2012_narrow_","data2_2012_narrow_",RooArgSet(cos1_MC,cos2_MC,MCweight2))
data3_2011_narrow_ = RooDataSet("data3_2011_narrow_","data3_2011_narrow_",RooArgSet(phi_MC,MCweight3))
data3_2012_narrow_ = RooDataSet("data3_2012_narrow_","data3_2012_narrow_",RooArgSet(phi_MC,MCweight3))
data4_2011_narrow_ = RooDataSet("data4_2011_narrow_","data4_2011_narrow_",RooArgSet(t_MC,MCweight4))
data4_2012_narrow_ = RooDataSet("data4_2012_narrow_","data4_2012_narrow_",RooArgSet(t_MC,MCweight4))

# Frames.
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


# ################################################################
# F U N C T I O N S
# ################################################################

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
sumi = [[[],[]],[[],[]]]
sumij = [[[],[]],[[],[]]]
NWi = [[[],[]],[[],[]]]
eNWi = [[[],[]],[[],[]]]
covij = [[[],[]],[[],[]]]
addzero = lambda x: x.append(0)
addlist = lambda x: x.append([])
for year in range(2):
	for window in range(2):
		for i in range(380):
			map(addzero,[sumi[year][window],NWi[year][window],eNWi[year][window]])
			map(addlist,[sumij[year][window],covij[year][window]])
			for j in range(380): map(addzero,[sumij[year][window][i],covij[year][window][i]])


def CreateGenPDF():

	PDF_gen = MCGenPHSP("PDF_gen","PDF_gen",wide_window_MC,mKp1_MC,mKp2_MC,t_MC,opt_genmodel)
	model_gen = RooRealSumPdf("model_gen","model_gen",RooArgList(PDF_gen),RooArgList(one))

	return PDF_gen, model_gen


def CreateAccPDF():

	PDF_acc_2011_wide = accpdf("PDF_acc_2011_wide","PDF_acc_2011_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_wide,k2_2011_wide,k3_2011_wide,k4_2011_wide,p1_2011_wide,a_acc_2011_wide,b_acc_2011_wide,opt_acc)
	model_acc_2011_wide = RooRealSumPdf("model_acc_2011_wide","model_acc_2011_wide",RooArgList(PDF_acc_2011_wide),RooArgList(one))
	PDF_acc_2012_wide = accpdf("PDF_acc_2012_wide","PDF_acc_2012_wide",mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_wide,k2_2012_wide,k3_2012_wide,k4_2012_wide,p1_2012_wide,a_acc_2012_wide,b_acc_2012_wide,opt_acc)
	model_acc_2012_wide = RooRealSumPdf("model_acc_2012_wide","model_acc_2012_wide",RooArgList(PDF_acc_2012_wide),RooArgList(one))
	PDF_acc_2011_narrow = accpdf("PDF_acc_2011_narrow","PDF_acc_2011_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_narrow,k2_2011_narrow,k3_2011_narrow,k4_2011_narrow,p1_2011_narrow,a_acc_2011_narrow,b_acc_2011_narrow,opt_acc)
	model_acc_2011_narrow = RooRealSumPdf("model_acc_2011_narrow","model_acc_2011_narrow",RooArgList(PDF_acc_2011_narrow),RooArgList(one))
	PDF_acc_2012_narrow = accpdf("PDF_acc_2012_narrow","PDF_acc_2012_narrow",mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,k1_2012_narrow,k2_2012_narrow,k3_2012_narrow,k4_2012_narrow,p1_2012_narrow,a_acc_2012_narrow,b_acc_2012_narrow,opt_acc)
	model_acc_2012_narrow = RooRealSumPdf("model_acc_2012_narrow","model_acc_2012_narrow",RooArgList(PDF_acc_2012_narrow),RooArgList(one))

	return PDF_acc_2011_wide, PDF_acc_2012_wide, model_acc_2011_wide, model_acc_2012_wide, PDF_acc_2011_narrow, PDF_acc_2012_narrow, model_acc_2011_narrow, model_acc_2012_narrow


def CreatePhysPDF():

	flatacc.setVal(1)
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


def LoadDataVis(data_file, data_tree, evnum_limit = 0):

	# Information.
	print 'Loading data file ' + data_file + ' ...'
	if (evnum_limit == 0): print 'All events selected.'
	else: print str(evnum_limit)+' events selected.'

	# Input data.
	file_in = TFile(NTUPLE_PATH + data_file)
	tree_full = file_in.Get(data_tree)
	file_out = TFile(NTUPLE_PATH + "trash.root","RECREATE")
	tree_2011_wide = tree_full.CopyTree(t_name_MC+">=0. && "+t_name_MC+"<=12. && itype==-73")
	tree_2012_wide = tree_full.CopyTree(t_name_MC+">=0. && "+t_name_MC+"<=12. && itype==-83")
	tree_2011_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && itype==-73")
	tree_2012_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && itype==-83")

	PDF_gen,model_gen = CreateGenPDF()

	invN_2011_wide = 1./tree_2011_wide.GetEntries()
	invN_2012_wide = 1./tree_2012_wide.GetEntries()
	invN_2011_narrow = 1./tree_2011_narrow.GetEntries()
	invN_2012_narrow = 1./tree_2012_narrow.GetEntries()

	wide_window_MC.setVal(1)
	ev_counter = 0
	for i in tree_2011_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			mKp1_MC.setVal(eval("i."+m1_name_MC))
			mKp2_MC.setVal(eval("i."+m2_name_MC))
			cos1_MC.setVal(eval("i."+cos1_name_MC))
			cos2_MC.setVal(eval("i."+cos2_name_MC))
			phi_MC.setVal(eval("i."+phi_name_MC))
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight1.setVal(invN_2011_wide/PDF_gen.phasespace(eval("i."+m1_name_MC),eval("i."+m2_name_MC)))
			MCweight2.setVal(invN_2011_wide)
			MCweight3.setVal(invN_2011_wide)
			MCweight4.setVal(invN_2011_wide/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_2011_wide_.add(RooArgSet(mKp1_MC,mKp2_MC,MCweight1))
			data2_2011_wide_.add(RooArgSet(cos1_MC,cos2_MC,MCweight2))
			data3_2011_wide_.add(RooArgSet(phi_MC,MCweight3))
			data4_2011_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	ev_counter = 0
	for i in tree_2012_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			mKp1_MC.setVal(eval("i."+m1_name_MC))
			mKp2_MC.setVal(eval("i."+m2_name_MC))
			cos1_MC.setVal(eval("i."+cos1_name_MC))
			cos2_MC.setVal(eval("i."+cos2_name_MC))
			phi_MC.setVal(eval("i."+phi_name_MC))
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight1.setVal(invN_2012_wide/PDF_gen.phasespace(eval("i."+m1_name_MC),eval("i."+m2_name_MC)))
			MCweight2.setVal(invN_2012_wide)
			MCweight3.setVal(invN_2012_wide)
			MCweight4.setVal(invN_2012_wide/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_2012_wide_.add(RooArgSet(mKp1_MC,mKp2_MC,MCweight1))
			data2_2012_wide_.add(RooArgSet(cos1_MC,cos2_MC,MCweight2))
			data3_2012_wide_.add(RooArgSet(phi_MC,MCweight3))
			data4_2012_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	wide_window_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
			mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
			cos1_MC.setVal(eval("i."+cos1_name_MC))
			cos2_MC.setVal(eval("i."+cos2_name_MC))
			phi_MC.setVal(eval("i."+phi_name_MC))
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight1.setVal(invN_2011_narrow/PDF_gen.phasespace(eval("i."+m1_name_MC),eval("i."+m2_name_MC)))
			MCweight2.setVal(invN_2011_narrow)
			MCweight3.setVal(invN_2011_narrow)
			MCweight4.setVal(invN_2011_narrow/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_2011_narrow_.add(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,MCweight1))
			data2_2011_narrow_.add(RooArgSet(cos1_MC,cos2_MC,MCweight2))
			data3_2011_narrow_.add(RooArgSet(phi_MC,MCweight3))
			data4_2011_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	ev_counter = 0
	for i in tree_2012_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
			mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
			cos1_MC.setVal(eval("i."+cos1_name_MC))
			cos2_MC.setVal(eval("i."+cos2_name_MC))
			phi_MC.setVal(eval("i."+phi_name_MC))
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight1.setVal(invN_2012_narrow/PDF_gen.phasespace(eval("i."+m1_name_MC),eval("i."+m2_name_MC)))
			MCweight2.setVal(invN_2012_narrow)
			MCweight3.setVal(invN_2012_narrow)
			MCweight4.setVal(invN_2012_narrow/PDF_gen.timemodel(eval("i."+t_name_MC)))
			data1_2012_narrow_.add(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,MCweight1))
			data2_2012_narrow_.add(RooArgSet(cos1_MC,cos2_MC,MCweight2))
			data3_2012_narrow_.add(RooArgSet(phi_MC,MCweight3))
			data4_2012_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1

	data1_2011_wide = RooDataSet("data1_2011_wide","data1_2011_wide",data1_2011_wide_,data1_2011_wide_.get(),"","MCweight1")
	data2_2011_wide = RooDataSet("data2_2011_wide","data2_2011_wide",data2_2011_wide_,data2_2011_wide_.get(),"","MCweight2")
	data3_2011_wide = RooDataSet("data3_2011_wide","data3_2011_wide",data3_2011_wide_,data3_2011_wide_.get(),"","MCweight3")
	data4_2011_wide = RooDataSet("data4_2011_wide","data4_2011_wide",data4_2011_wide_,data4_2011_wide_.get(),"","MCweight4")
	data1_2012_wide = RooDataSet("data1_2012_wide","data1_2012_wide",data1_2012_wide_,data1_2012_wide_.get(),"","MCweight1")
	data2_2012_wide = RooDataSet("data2_2012_wide","data2_2012_wide",data2_2012_wide_,data2_2012_wide_.get(),"","MCweight2")
	data3_2012_wide = RooDataSet("data3_2012_wide","data3_2012_wide",data3_2012_wide_,data3_2012_wide_.get(),"","MCweight3")
	data4_2012_wide = RooDataSet("data4_2012_wide","data4_2012_wide",data4_2012_wide_,data4_2012_wide_.get(),"","MCweight4")
	data1_2011_narrow = RooDataSet("data1_2011_narrow","data1_2011_narrow",data1_2011_narrow_,data1_2011_narrow_.get(),"","MCweight1")
	data2_2011_narrow = RooDataSet("data2_2011_narrow","data2_2011_narrow",data2_2011_narrow_,data2_2011_narrow_.get(),"","MCweight2")
	data3_2011_narrow = RooDataSet("data3_2011_narrow","data3_2011_narrow",data3_2011_narrow_,data3_2011_narrow_.get(),"","MCweight3")
	data4_2011_narrow = RooDataSet("data4_2011_narrow","data4_2011_narrow",data4_2011_narrow_,data4_2011_narrow_.get(),"","MCweight4")
	data1_2012_narrow = RooDataSet("data1_2012_narrow","data1_2012_narrow",data1_2012_narrow_,data1_2012_narrow_.get(),"","MCweight1")
	data2_2012_narrow = RooDataSet("data2_2012_narrow","data2_2012_narrow",data2_2012_narrow_,data2_2012_narrow_.get(),"","MCweight2")
	data3_2012_narrow = RooDataSet("data3_2012_narrow","data3_2012_narrow",data3_2012_narrow_,data3_2012_narrow_.get(),"","MCweight3")
	data4_2012_narrow = RooDataSet("data4_2012_narrow","data4_2012_narrow",data4_2012_narrow_,data4_2012_narrow_.get(),"","MCweight4")

	print 'Data loaded.'

	return data1_2011_wide, data1_2012_wide, data2_2011_wide, data2_2012_wide, data3_2011_wide, data3_2012_wide, data4_2011_wide, data4_2012_wide,\
data1_2011_narrow, data1_2012_narrow, data2_2011_narrow, data2_2012_narrow, data3_2011_narrow, data3_2012_narrow, data4_2011_narrow, data4_2012_narrow


def FitnPlotVisAcc(model_acc_2011_wide,model_acc_2012_wide,model_acc_2011_narrow,model_acc_2012_narrow,\
data1_2011_wide,data1_2012_wide,data2_2011_wide,data2_2012_wide,data3_2011_wide,data3_2012_wide,data4_2011_wide,data4_2012_wide,\
data1_2011_narrow,data1_2012_narrow,data2_2011_narrow,data2_2012_narrow,data3_2011_narrow,data3_2012_narrow,data4_2011_narrow,data4_2012_narrow):

	# Fitting.
	opt_acc.setVal(1)
	map(lambda x:x.setConstant(1),[cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_wide,k2_2011_wide,k3_2011_wide,k4_2011_wide,a_acc_2011_wide,b_acc_2011_wide,k1_2012_wide,k2_2012_wide,k3_2012_wide,k4_2012_wide,a_acc_2012_wide,b_acc_2012_wide,k1_2011_narrow,k2_2011_narrow,k3_2011_narrow,k4_2011_narrow,a_acc_2011_narrow,b_acc_2011_narrow,k1_2012_narrow,k2_2012_narrow,k3_2012_narrow,k4_2012_narrow,a_acc_2012_narrow,b_acc_2012_narrow])
	model_acc_2011_wide.fitTo(data1_2011_wide,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_wide.fitTo(data1_2012_wide,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2011_narrow.fitTo(data1_2011_narrow,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_narrow.fitTo(data1_2012_narrow,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	map(lambda x:x.setConstant(0),[cos1_MC,cos2_MC,phi_MC,t_MC,k1_2011_wide,k2_2011_wide,k3_2011_wide,k4_2011_wide,a_acc_2011_wide,b_acc_2011_wide,k1_2012_wide,k2_2012_wide,k3_2012_wide,k4_2012_wide,a_acc_2012_wide,b_acc_2012_wide,k1_2011_narrow,k2_2011_narrow,k3_2011_narrow,k4_2011_narrow,a_acc_2011_narrow,b_acc_2011_narrow,k1_2012_narrow,k2_2012_narrow,k3_2012_narrow,k4_2012_narrow,a_acc_2012_narrow,b_acc_2012_narrow])
	opt_acc.setVal(2)
	map(lambda x:x.setConstant(1),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,phi_MC,t_MC,p1_2011_wide,a_acc_2011_wide,b_acc_2011_wide,p1_2012_wide,a_acc_2012_wide,b_acc_2012_wide,p1_2011_narrow,a_acc_2011_narrow,b_acc_2011_narrow,p1_2012_narrow,a_acc_2012_narrow,b_acc_2012_narrow])
	model_acc_2011_wide.fitTo(data2_2011_wide,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_wide.fitTo(data2_2012_wide,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2011_narrow.fitTo(data2_2011_narrow,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_narrow.fitTo(data2_2012_narrow,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	map(lambda x:x.setConstant(0),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,phi_MC,t_MC,p1_2011_wide,a_acc_2011_wide,b_acc_2011_wide,p1_2012_wide,a_acc_2012_wide,b_acc_2012_wide,p1_2011_narrow,a_acc_2011_narrow,b_acc_2011_narrow,p1_2012_narrow,a_acc_2012_narrow,b_acc_2012_narrow])
	opt_acc.setVal(3)
	map(lambda x:x.setConstant(1),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,t_MC,p1_2011_wide,k1_2011_wide,k2_2011_wide,k3_2011_wide,k4_2011_wide,a_acc_2011_wide,b_acc_2011_wide,p1_2012_wide,k1_2012_wide,k2_2012_wide,k3_2012_wide,k4_2012_wide,a_acc_2012_wide,b_acc_2012_wide,p1_2011_narrow,k1_2011_narrow,k2_2011_narrow,k3_2011_narrow,k4_2011_narrow,a_acc_2011_narrow,b_acc_2011_narrow,p1_2012_narrow,k1_2012_narrow,k2_2012_narrow,k3_2012_narrow,k4_2012_narrow,a_acc_2012_narrow,b_acc_2012_narrow])
	model_acc_2011_wide.fitTo(data3_2011_wide,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_wide.fitTo(data3_2012_wide,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2011_narrow.fitTo(data3_2011_narrow,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_narrow.fitTo(data3_2012_narrow,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	map(lambda x:x.setConstant(0),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,t_MC,p1_2011_wide,k1_2011_wide,k2_2011_wide,k3_2011_wide,k4_2011_wide,a_acc_2011_wide,b_acc_2011_wide,p1_2012_wide,k1_2012_wide,k2_2012_wide,k3_2012_wide,k4_2012_wide,a_acc_2012_wide,b_acc_2012_wide,p1_2011_narrow,k1_2011_narrow,k2_2011_narrow,k3_2011_narrow,k4_2011_narrow,a_acc_2011_narrow,b_acc_2011_narrow,p1_2012_narrow,k1_2012_narrow,k2_2012_narrow,k3_2012_narrow,k4_2012_narrow,a_acc_2012_narrow,b_acc_2012_narrow])
	opt_acc.setVal(4)
	map(lambda x:x.setConstant(1),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,p1_2011_wide,k1_2011_wide,k2_2011_wide,k3_2011_wide,k4_2011_wide,p1_2012_wide,k1_2012_wide,k2_2012_wide,k3_2012_wide,k4_2012_wide,p1_2011_narrow,k1_2011_narrow,k2_2011_narrow,k3_2011_narrow,k4_2011_narrow,p1_2012_narrow,k1_2012_narrow,k2_2012_narrow,k3_2012_narrow,k4_2012_narrow])
	model_acc_2011_wide.fitTo(data4_2011_wide,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_wide.fitTo(data4_2012_wide,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2011_narrow.fitTo(data4_2011_narrow,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	model_acc_2012_narrow.fitTo(data4_2012_narrow,RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
	map(lambda x:x.setConstant(0),[mKp1_MC,mKp2_MC,mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,p1_2011_wide,k1_2011_wide,k2_2011_wide,k3_2011_wide,k4_2011_wide,p1_2012_wide,k1_2012_wide,k2_2012_wide,k3_2012_wide,k4_2012_wide,p1_2011_narrow,k1_2011_narrow,k2_2011_narrow,k3_2011_narrow,k4_2011_narrow,p1_2012_narrow,k1_2012_narrow,k2_2012_narrow,k3_2012_narrow,k4_2012_narrow])

	# Plotting.
	data1_2011_wide.plotOn(frame_m1_MC_2011_wide,RooFit.Binning(40))
	data1_2011_wide.plotOn(frame_m2_MC_2011_wide,RooFit.Binning(40))
	data2_2011_wide.plotOn(frame_cos1_MC_2011_wide,RooFit.Binning(40))
	data2_2011_wide.plotOn(frame_cos2_MC_2011_wide,RooFit.Binning(40))
	data3_2011_wide.plotOn(frame_phi_MC_2011_wide,RooFit.Binning(40))
	data4_2011_wide.plotOn(frame_t_MC_2011_wide,RooFit.Binning(40))
	data1_2012_wide.plotOn(frame_m1_MC_2012_wide,RooFit.Binning(40))
	data1_2012_wide.plotOn(frame_m2_MC_2012_wide,RooFit.Binning(40))
	data2_2012_wide.plotOn(frame_cos1_MC_2012_wide,RooFit.Binning(40))
	data2_2012_wide.plotOn(frame_cos2_MC_2012_wide,RooFit.Binning(40))
	data3_2012_wide.plotOn(frame_phi_MC_2012_wide,RooFit.Binning(40))
	data4_2012_wide.plotOn(frame_t_MC_2012_wide,RooFit.Binning(40))
	data1_2011_narrow.plotOn(frame_m1_MC_2011_narrow,RooFit.Binning(40))
	data1_2011_narrow.plotOn(frame_m2_MC_2011_narrow,RooFit.Binning(40))
	data2_2011_narrow.plotOn(frame_cos1_MC_2011_narrow,RooFit.Binning(40))
	data2_2011_narrow.plotOn(frame_cos2_MC_2011_narrow,RooFit.Binning(40))
	data3_2011_narrow.plotOn(frame_phi_MC_2011_narrow,RooFit.Binning(40))
	data4_2011_narrow.plotOn(frame_t_MC_2011_narrow,RooFit.Binning(40))
	data1_2012_narrow.plotOn(frame_m1_MC_2012_narrow,RooFit.Binning(40))
	data1_2012_narrow.plotOn(frame_m2_MC_2012_narrow,RooFit.Binning(40))
	data2_2012_narrow.plotOn(frame_cos1_MC_2012_narrow,RooFit.Binning(40))
	data2_2012_narrow.plotOn(frame_cos2_MC_2012_narrow,RooFit.Binning(40))
	data3_2012_narrow.plotOn(frame_phi_MC_2012_narrow,RooFit.Binning(40))
	data4_2012_narrow.plotOn(frame_t_MC_2012_narrow,RooFit.Binning(40))
	opt_acc.setVal(1)
	model_acc_2011_wide.plotOn(frame_m1_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_wide.plotOn(frame_m2_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_wide.plotOn(frame_m1_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_wide.plotOn(frame_m2_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_narrow.plotOn(frame_m1_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_narrow.plotOn(frame_m2_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_narrow.plotOn(frame_m1_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_narrow.plotOn(frame_m2_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(2)
	model_acc_2011_wide.plotOn(frame_cos1_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_wide.plotOn(frame_cos2_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_wide.plotOn(frame_cos1_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_wide.plotOn(frame_cos2_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_narrow.plotOn(frame_cos1_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_narrow.plotOn(frame_cos2_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_narrow.plotOn(frame_cos1_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_narrow.plotOn(frame_cos2_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(3)
	model_acc_2011_wide.plotOn(frame_phi_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_wide.plotOn(frame_phi_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_narrow.plotOn(frame_phi_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_narrow.plotOn(frame_phi_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	opt_acc.setVal(4)
	model_acc_2011_wide.plotOn(frame_t_MC_2011_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_wide.plotOn(frame_t_MC_2012_wide,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2011_narrow.plotOn(frame_t_MC_2011_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	model_acc_2012_narrow.plotOn(frame_t_MC_2012_narrow,RooFit.DrawOption("c"),RooFit.LineColor(kBlue))
	cvis_2011_wide = TCanvas("cvis_2011_wide","cvis_2011_wide",1200,600)
	cvis_2011_wide.Divide(3,2)
	cvis_2011_wide.cd(1)
	frame_cos1_MC_2011_wide.Draw()
	cvis_2011_wide.cd(2)
	frame_cos2_MC_2011_wide.Draw()
	cvis_2011_wide.cd(3)
	frame_phi_MC_2011_wide.Draw()
	cvis_2011_wide.cd(4)
	frame_m1_MC_2011_wide.Draw()
	cvis_2011_wide.cd(5)
	frame_m2_MC_2011_wide.Draw()
	cvis_2011_wide.cd(6)
	frame_t_MC_2011_wide.Draw()
	cvis_2012_wide = TCanvas("cvis_2012_wide","cvis_2012_wide",1200,600)
	cvis_2012_wide.Divide(3,2)
	cvis_2012_wide.cd(1)
	frame_cos1_MC_2012_wide.Draw()
	cvis_2012_wide.cd(2)
	frame_cos2_MC_2012_wide.Draw()
	cvis_2012_wide.cd(3)
	frame_phi_MC_2012_wide.Draw()
	cvis_2012_wide.cd(4)
	frame_m1_MC_2012_wide.Draw()
	cvis_2012_wide.cd(5)
	frame_m2_MC_2012_wide.Draw()
	cvis_2012_wide.cd(6)
	frame_t_MC_2012_wide.Draw()
	cvis_2011_narrow = TCanvas("cvis_2011_narrow","cvis_2011_narrow",1200,600)
	cvis_2011_narrow.Divide(3,2)
	cvis_2011_narrow.cd(1)
	frame_cos1_MC_2011_narrow.Draw()
	cvis_2011_narrow.cd(2)
	frame_cos2_MC_2011_narrow.Draw()
	cvis_2011_narrow.cd(3)
	frame_phi_MC_2011_narrow.Draw()
	cvis_2011_narrow.cd(4)
	frame_m1_MC_2011_narrow.Draw()
	cvis_2011_narrow.cd(5)
	frame_m2_MC_2011_narrow.Draw()
	cvis_2011_narrow.cd(6)
	frame_t_MC_2011_narrow.Draw()
	cvis_2012_narrow = TCanvas("cvis_2012_narrow","cvis_2012_narrow",1200,600)
	cvis_2012_narrow.Divide(3,2)
	cvis_2012_narrow.cd(1)
	frame_cos1_MC_2012_narrow.Draw()
	cvis_2012_narrow.cd(2)
	frame_cos2_MC_2012_narrow.Draw()
	cvis_2012_narrow.cd(3)
	frame_phi_MC_2012_narrow.Draw()
	cvis_2012_narrow.cd(4)
	frame_m1_MC_2012_narrow.Draw()
	cvis_2012_narrow.cd(5)
	frame_m2_MC_2012_narrow.Draw()
	cvis_2012_narrow.cd(6)
	frame_t_MC_2012_narrow.Draw()

	return cvis_2011_wide, cvis_2012_wide, cvis_2011_narrow, cvis_2012_narrow


def PrintVisAccPars():

	accpars = 'class accparclass {\n\n  public:\n\n  Double_t k1(Int_t year_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (wide_window == 1)) {return '+str(k1_2011_wide.getVal())+';}\n    else if ((year_opt == 0) && (wide_window == 0)) {return '+str(k1_2011_narrow.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 1)) {return '+str(k1_2012_wide.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 0)) {return '+str(k1_2012_narrow.getVal())+';}\n    return 0.;\n    };\n\n  Double_t k2(Int_t year_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (wide_window == 1)) {return '+str(k2_2011_wide.getVal())+';}\n    else if ((year_opt == 0) && (wide_window == 0)) {return '+str(k2_2011_narrow.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 1)) {return '+str(k2_2012_wide.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 0)) {return '+str(k2_2012_narrow.getVal())+';}\n    return 0.;\n    };\n\n  Double_t k3(Int_t year_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (wide_window == 1)) {return '+str(k3_2011_wide.getVal())+';}\n    else if ((year_opt == 0) && (wide_window == 0)) {return '+str(k3_2011_narrow.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 1)) {return '+str(k3_2012_wide.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 0)) {return '+str(k3_2012_narrow.getVal())+';}\n    return 0.;\n    };\n\n  Double_t k4(Int_t year_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (wide_window == 1)) {return '+str(k4_2011_wide.getVal())+';}\n    else if ((year_opt == 0) && (wide_window == 0)) {return '+str(k4_2011_narrow.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 1)) {return '+str(k4_2012_wide.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 0)) {return '+str(k4_2012_narrow.getVal())+';}\n    return 0.;\n    };\n\n  Double_t p1(Int_t year_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (wide_window == 1)) {return '+str(p1_2011_wide.getVal())+';}\n    else if ((year_opt == 0) && (wide_window == 0)) {return '+str(p1_2011_narrow.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 1)) {return '+str(p1_2012_wide.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 0)) {return '+str(p1_2012_narrow.getVal())+';}\n    return 0.;\n    };\n\n  Double_t a_acc(Int_t year_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (wide_window == 1)) {return '+str(a_acc_2011_wide.getVal())+';}\n    else if ((year_opt == 0) && (wide_window == 0)) {return '+str(a_acc_2011_narrow.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 1)) {return '+str(a_acc_2012_wide.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 0)) {return '+str(a_acc_2012_narrow.getVal())+';}\n    return 0.;\n    };\n\n  Double_t b_acc(Int_t year_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (wide_window == 1)) {return '+str(b_acc_2011_wide.getVal())+';}\n    else if ((year_opt == 0) && (wide_window == 0)) {return '+str(b_acc_2011_narrow.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 1)) {return '+str(b_acc_2012_wide.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 0)) {return '+str(b_acc_2012_narrow.getVal())+';}\n    return 0.;\n    };\n\n};'

	fpar = open('../../src/TimeDependent/accparclass.h','w')
	fpar.write(accpars)
	fpar.close()


def LoadDataNW(data_file, data_tree, evnum_limit = 0):

	# Information.
	print 'Loading data file ' + data_file + ' ...'
	if (evnum_limit == 0): print 'All events selected.'
	else: print str(evnum_limit)+' events selected.'

	# Input data.
	file_in = TFile(NTUPLE_PATH + data_file)
	tree_full = file_in.Get(data_tree)
	file_out = TFile(NTUPLE_PATH + "trash.root","RECREATE")
	tree_2011_wide = tree_full.CopyTree(t_name_MC+">=0. && "+t_name_MC+"<=12. && itype==-73")
	tree_2012_wide = tree_full.CopyTree(t_name_MC+">=0. && "+t_name_MC+"<=12. && itype==-83")
	tree_2011_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && itype==-73")
	tree_2012_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && itype==-83")

	PDF_gen,model_gen = CreateGenPDF()

	data0_2011_wide = RooDataSet("data0_2011_wide","data0_2011_wide",RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
	data0_2012_wide = RooDataSet("data0_2012_wide","data0_2012_wide",RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
	data0_2011_narrow = RooDataSet("data0_2011_narrow","data0_2011_narrow",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
	data0_2012_narrow = RooDataSet("data0_2012_narrow","data0_2012_narrow",RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))

	wide_window_MC.setVal(1)
	ev_counter = 0
	for i in tree_2011_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			mKp1_MC.setVal(eval("i."+m1_name_MC))
			mKp2_MC.setVal(eval("i."+m2_name_MC))
			cos1_MC.setVal(eval("i."+cos1_name_MC))
			cos2_MC.setVal(eval("i."+cos2_name_MC))
			phi_MC.setVal(eval("i."+phi_name_MC))
			MCweight0.setVal(1./PDF_gen.phasespace(eval("i."+m1_name_MC),eval("i."+m2_name_MC)))
			data0_2011_wide.add(RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
			ev_counter += 1
	ev_counter = 0
	for i in tree_2012_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			mKp1_MC.setVal(eval("i."+m1_name_MC))
			mKp2_MC.setVal(eval("i."+m2_name_MC))
			cos1_MC.setVal(eval("i."+cos1_name_MC))
			cos2_MC.setVal(eval("i."+cos2_name_MC))
			phi_MC.setVal(eval("i."+phi_name_MC))
			MCweight0.setVal(1./PDF_gen.phasespace(eval("i."+m1_name_MC),eval("i."+m2_name_MC)))
			data0_2012_wide.add(RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
			ev_counter += 1
	wide_window_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
			mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
			cos1_MC.setVal(eval("i."+cos1_name_MC))
			cos2_MC.setVal(eval("i."+cos2_name_MC))
			phi_MC.setVal(eval("i."+phi_name_MC))
			MCweight0.setVal(1./PDF_gen.phasespace(eval("i."+m1_name_MC),eval("i."+m2_name_MC)))
			data0_2011_narrow.add(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
			ev_counter += 1
	ev_counter = 0
	for i in tree_2012_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
			mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
			cos1_MC.setVal(eval("i."+cos1_name_MC))
			cos2_MC.setVal(eval("i."+cos2_name_MC))
			phi_MC.setVal(eval("i."+phi_name_MC))
			MCweight0.setVal(1./PDF_gen.phasespace(eval("i."+m1_name_MC),eval("i."+m2_name_MC)))
			data0_2012_narrow.add(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
			ev_counter += 1

	print 'Data loaded.'

	return data0_2011_wide, data0_2012_wide, data0_2011_narrow, data0_2012_narrow


def ComputeNW(comp_cov_matrix,PDF_phys_wide,PDF_phys_narrow,data0_2011_wide,data0_2012_wide,data0_2011_narrow,data0_2012_narrow):

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

	N_11_wide = data0_2011_wide.numEntries()
	N_12_wide = data0_2012_wide.numEntries()
	N_11_narrow = data0_2011_narrow.numEntries()
	N_12_narrow = data0_2012_narrow.numEntries()
	N_total = N_11_wide+N_12_wide+N_11_narrow+N_12_narrow

	print 'Analizing '+str(N_total)+' events ...'
	start = time.time()
	counter = 0

	# Loop over the events to compute the needed sums.

	for ev in range(N_11_wide):
		m1_var = data0_2011_wide.get(ev).getRealValue(m1_name_MC)
		m2_var =  data0_2011_wide.get(ev).getRealValue(m2_name_MC)
		cos1_var =  data0_2011_wide.get(ev).getRealValue(cos1_name_MC)
		cos2_var =  data0_2011_wide.get(ev).getRealValue(cos2_name_MC)
		phi_var =  data0_2011_wide.get(ev).getRealValue(phi_name_MC)
		norm =  data0_2011_wide.get(ev).getRealValue("MCweight0")
		for i in range(380):
			sumi[0][1][i] += norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			sumij[0][1][i][i] += norm*norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			if comp_cov_matrix:
				for j in range(380):
					if j<i: sumij[0][1][i][j] += norm*norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(1,j,m1_var,m2_var,cos1_var,cos2_var,phi_var)
		counter += 1
		if (counter%100 == 0): print str(counter)+' events analyzed (of '+str(N_total)+').'

	for ev in range(N_12_wide):
		m1_var = data0_2012_wide.get(ev).getRealValue(m1_name_MC)
		m2_var =  data0_2012_wide.get(ev).getRealValue(m2_name_MC)
		cos1_var =  data0_2012_wide.get(ev).getRealValue(cos1_name_MC)
		cos2_var =  data0_2012_wide.get(ev).getRealValue(cos2_name_MC)
		phi_var =  data0_2012_wide.get(ev).getRealValue(phi_name_MC)
		norm =  data0_2012_wide.get(ev).getRealValue("MCweight0")
		for i in range(380):
			sumi[1][1][i] += norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			sumij[1][1][i][i] += norm*norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			if comp_cov_matrix:
				for j in range(380):
					if j<i: sumij[1][1][i][j] += norm*norm*PDF_fi(1,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(1,j,m1_var,m2_var,cos1_var,cos2_var,phi_var)
		counter += 1
		if (counter%100 == 0): print str(counter)+' events analyzed (of '+str(N_total)+').'

	for ev in range(N_11_narrow):
		m1_var = data0_2011_narrow.get(ev).getRealValue(m1_name_MC)
		m2_var =  data0_2011_narrow.get(ev).getRealValue(m2_name_MC)
		cos1_var =  data0_2011_narrow.get(ev).getRealValue(cos1_name_MC)
		cos2_var =  data0_2011_narrow.get(ev).getRealValue(cos2_name_MC)
		phi_var =  data0_2011_narrow.get(ev).getRealValue(phi_name_MC)
		norm =  data0_2011_narrow.get(ev).getRealValue("MCweight0")
		for i in range(380):
			sumi[0][0][i] += norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			sumij[0][0][i][i] += norm*norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			if comp_cov_matrix:
				for j in range(380):
					if j<i: sumij[0][0][i][j] += norm*norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(0,j,m1_var,m2_var,cos1_var,cos2_var,phi_var)
		counter += 1
		if (counter%100 == 0): print str(counter)+' events analyzed (of '+str(N_total)+').'

	for ev in range(N_12_narrow):
		m1_var = data0_2012_narrow.get(ev).getRealValue(m1_name_MC)
		m2_var =  data0_2012_narrow.get(ev).getRealValue(m2_name_MC)
		cos1_var =  data0_2012_narrow.get(ev).getRealValue(cos1_name_MC)
		cos2_var =  data0_2012_narrow.get(ev).getRealValue(cos2_name_MC)
		phi_var =  data0_2012_narrow.get(ev).getRealValue(phi_name_MC)
		norm =  data0_2012_narrow.get(ev).getRealValue("MCweight0")
		for i in range(380):
			sumi[1][0][i] += norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			sumij[1][0][i][i] += norm*norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)
			if comp_cov_matrix:
				for j in range(380):
					if j<i: sumij[1][0][i][j] += norm*norm*PDF_fi(0,i,m1_var,m2_var,cos1_var,cos2_var,phi_var)*PDF_fi(0,j,m1_var,m2_var,cos1_var,cos2_var,phi_var)
		counter += 1
		if (counter%100 == 0): print str(counter)+' events analyzed (of '+str(N_total)+').'

	# Determination of the NW, their covariance matrix and their uncertainties from the sums above.

	for i in range(380):
		NWi[0][0][i] = sumi[0][0][i]/sumi[0][0][0]
		NWi[0][1][i] = sumi[0][1][i]/sumi[0][1][0]
		NWi[1][0][i] = sumi[1][0][i]/sumi[1][0][0]
		NWi[1][1][i] = sumi[1][1][i]/sumi[1][1][0]
		eNWi[0][0][i] = sqrt(sumij[0][0][i][i]-sumi[0][0][i]*sumi[0][0][i]/N_11_narrow)/sumi[0][0][0]
		eNWi[0][1][i] = sqrt(sumij[0][1][i][i]-sumi[0][1][i]*sumi[0][1][i]/N_11_wide)/sumi[0][1][0]
		eNWi[1][0][i] = sqrt(sumij[1][0][i][i]-sumi[1][0][i]*sumi[1][0][i]/N_12_narrow)/sumi[1][0][0]
		eNWi[1][1][i] = sqrt(sumij[1][1][i][i]-sumi[1][1][i]*sumi[1][1][i]/N_12_wide)/sumi[1][1][0]
		if comp_cov_matrix:
			for j in range(380):
				if j<=i:
					covij[0][0][i][j] = (sumij[0][0][i][j]-sumi[0][0][i]*sumi[0][0][j]/N_11_narrow)/sumi[0][0][0]/sumi[0][0][0]
					covij[0][1][i][j] = (sumij[0][1][i][j]-sumi[0][1][i]*sumi[0][1][j]/N_11_wide)/sumi[0][1][0]/sumi[0][1][0]
					covij[1][0][i][j] = (sumij[1][0][i][j]-sumi[1][0][i]*sumi[1][0][j]/N_12_narrow)/sumi[1][0][0]/sumi[1][0][0]
					covij[1][1][i][j] = (sumij[1][1][i][j]-sumi[1][1][i]*sumi[1][1][j]/N_12_wide)/sumi[1][1][0]/sumi[1][1][0]
				else:
					covij[0][0][i][j] = (sumij[0][0][j][i]-sumi[0][0][j]*sumi[0][0][i]/N_11_narrow)/sumi[0][0][0]/sumi[0][0][0]
					covij[0][1][i][j] = (sumij[0][1][j][i]-sumi[0][1][j]*sumi[0][1][i]/N_11_wide)/sumi[0][1][0]/sumi[0][1][0]
					covij[1][0][i][j] = (sumij[1][0][j][i]-sumi[1][0][j]*sumi[1][0][i]/N_12_narrow)/sumi[1][0][0]/sumi[1][0][0]
					covij[1][1][i][j] = (sumij[1][1][j][i]-sumi[1][1][j]*sumi[1][1][i]/N_12_wide)/sumi[1][1][0]/sumi[1][1][0]

	end = time.time()
	print 'Events analized in',(end - start)/60.,'min.'


def PrintNW():

	NWclass = 'class NWclass {\n\n  public:\n\n  Double_t comp(Int_t year_opt,Int_t wide_window,Int_t j1,Int_t j2,Int_t h,Int_t j1p,Int_t j2p,Int_t hp,Int_t part) {\n\n'
	NWclass += '    if ((year_opt == 0) && (wide_window == 1) && (j1 == 0) && (j2 == 0) && (h == 0) && (j1p == 0) && (j2p == 0) && (hp == 0) && (part == 0)) {return '+str(NWi[0][1][redindex(0,0,0,0,0,0,0)])+';}\n'
	NWclass += '    else if ((year_opt == 0) && (wide_window == 1) && (j1 == 0) && (j2 == 0) && (h == 0) && (j1p == 0) && (j2p == 0) && (hp == 0) && (part == 1)) {return '+str(NWi[0][1][redindex(0,0,0,0,0,0,1)])+';}\n'
	NWclass += '    else if ((year_opt == 1) && (wide_window == 1) && (j1 == 0) && (j2 == 0) && (h == 0) && (j1p == 0) && (j2p == 0) && (hp == 0) && (part == 0)) {return '+str(NWi[1][1][redindex(0,0,0,0,0,0,0)])+';}\n'
	NWclass += '    else if ((year_opt == 1) && (wide_window == 1) && (j1 == 0) && (j2 == 0) && (h == 0) && (j1p == 0) && (j2p == 0) && (hp == 0) && (part == 1)) {return '+str(NWi[1][1][redindex(0,0,0,0,0,0,1)])+';}\n'
	for j1 in range(3):
		for j2 in range(3):
			for h in range(5):
				for j1p in range(3):
					for j2p in range(3):
						for hp in range(5):
							if ((boolj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp) == 1) and not((j1 == 0) and (j2 == 0) and (h == 0) and (j1p == 0) and (j2p == 0) and (hp == 0)) and ((j1p+3*j2p+9*hp) <= (j1+3*j2+9*h))):
								NWclass += '    else if ((year_opt == 0) && (wide_window == 1) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 0)) {return '+str(NWi[0][1][redindex(j1,j2,h,j1p,j2p,hp,0)])+';}\n'
								NWclass += '    else if ((year_opt == 0) && (wide_window == 1) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 1)) {return '+str(NWi[0][1][redindex(j1,j2,h,j1p,j2p,hp,1)])+';}\n'
								NWclass += '    else if ((year_opt == 1) && (wide_window == 1) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 0)) {return '+str(NWi[1][1][redindex(j1,j2,h,j1p,j2p,hp,0)])+';}\n'
								NWclass += '    else if ((year_opt == 1) && (wide_window == 1) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 1)) {return '+str(NWi[1][1][redindex(j1,j2,h,j1p,j2p,hp,1)])+';}\n'
	for j1 in range(3):
		for j2 in range(3):
			for h in range(5):
				for j1p in range(3):
					for j2p in range(3):
						for hp in range(5):
							if ((boolj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp) == 1) and ((j1p+3*j2p+9*hp) <= (j1+3*j2+9*h))):
								NWclass += '    else if ((year_opt == 0) && (wide_window == 0) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 0)) {return '+str(NWi[0][0][redindex(j1,j2,h,j1p,j2p,hp,0)])+';}\n'
								NWclass += '    else if ((year_opt == 0) && (wide_window == 0) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 1)) {return '+str(NWi[0][0][redindex(j1,j2,h,j1p,j2p,hp,1)])+';}\n'
								NWclass += '    else if ((year_opt == 1) && (wide_window == 0) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 0)) {return '+str(NWi[1][0][redindex(j1,j2,h,j1p,j2p,hp,0)])+';}\n'
								NWclass += '    else if ((year_opt == 1) && (wide_window == 0) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 1)) {return '+str(NWi[1][0][redindex(j1,j2,h,j1p,j2p,hp,1)])+';}\n'
	NWclass += '\n    return 0.;\n\n    };\n\n  Double_t comp_err(Int_t year_opt,Int_t wide_window,Int_t j1,Int_t j2,Int_t h,Int_t j1p,Int_t j2p,Int_t hp,Int_t part) {\n\n'
	NWclass += '    if ((year_opt == 0) && (wide_window == 1) && (j1 == 0) && (j2 == 0) && (h == 0) && (j1p == 0) && (j2p == 0) && (hp == 0) && (part == 0)) {return '+str(eNWi[0][1][redindex(0,0,0,0,0,0,0)])+';}\n'
	NWclass += '    else if ((year_opt == 0) && (wide_window == 1) && (j1 == 0) && (j2 == 0) && (h == 0) && (j1p == 0) && (j2p == 0) && (hp == 0) && (part == 1)) {return '+str(eNWi[0][1][redindex(0,0,0,0,0,0,1)])+';}\n'
	NWclass += '    else if ((year_opt == 1) && (wide_window == 1) && (j1 == 0) && (j2 == 0) && (h == 0) && (j1p == 0) && (j2p == 0) && (hp == 0) && (part == 0)) {return '+str(eNWi[1][1][redindex(0,0,0,0,0,0,0)])+';}\n'
	NWclass += '    else if ((year_opt == 1) && (wide_window == 1) && (j1 == 0) && (j2 == 0) && (h == 0) && (j1p == 0) && (j2p == 0) && (hp == 0) && (part == 1)) {return '+str(eNWi[1][1][redindex(0,0,0,0,0,0,1)])+';}\n'
	for j1 in range(3):
		for j2 in range(3):
			for h in range(5):
				for j1p in range(3):
					for j2p in range(3):
						for hp in range(5):
							if ((boolj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp) == 1) and not((j1 == 0) and (j2 == 0) and (h == 0) and (j1p == 0) and (j2p == 0) and (hp == 0)) and ((j1p+3*j2p+9*hp) <= (j1+3*j2+9*h))):
								NWclass += '    else if ((year_opt == 0) && (wide_window == 1) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 0)) {return '+str(eNWi[0][1][redindex(j1,j2,h,j1p,j2p,hp,0)])+';}\n'
								NWclass += '    else if ((year_opt == 0) && (wide_window == 1) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 1)) {return '+str(eNWi[0][1][redindex(j1,j2,h,j1p,j2p,hp,1)])+';}\n'
								NWclass += '    else if ((year_opt == 1) && (wide_window == 1) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 0)) {return '+str(eNWi[1][1][redindex(j1,j2,h,j1p,j2p,hp,0)])+';}\n'
								NWclass += '    else if ((year_opt == 1) && (wide_window == 1) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 1)) {return '+str(eNWi[1][1][redindex(j1,j2,h,j1p,j2p,hp,1)])+';}\n'
	for j1 in range(3):
		for j2 in range(3):
			for h in range(5):
				for j1p in range(3):
					for j2p in range(3):
						for hp in range(5):
							if ((boolj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp) == 1) and ((j1p+3*j2p+9*hp) <= (j1+3*j2+9*h))):
								NWclass += '    else if ((year_opt == 0) && (wide_window == 0) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 0)) {return '+str(eNWi[0][0][redindex(j1,j2,h,j1p,j2p,hp,0)])+';}\n'
								NWclass += '    else if ((year_opt == 0) && (wide_window == 0) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 1)) {return '+str(eNWi[0][0][redindex(j1,j2,h,j1p,j2p,hp,1)])+';}\n'
								NWclass += '    else if ((year_opt == 1) && (wide_window == 0) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 0)) {return '+str(eNWi[1][0][redindex(j1,j2,h,j1p,j2p,hp,0)])+';}\n'
								NWclass += '    else if ((year_opt == 1) && (wide_window == 0) && (j1 == '+str(j1)+') && (j2 == '+str(j2)+') && (h == '+str(h)+') && (j1p == '+str(j1p)+') && (j2p == '+str(j2p)+') && (hp == '+str(hp)+') && (part == 1)) {return '+str(eNWi[1][0][redindex(j1,j2,h,j1p,j2p,hp,1)])+';}\n'
	NWclass += '\n    return 0.;\n\n    };\n\n};'

	fNWcxx = open('../../src/TimeDependent/NWclass.h','w')
	fNWcxx.write(NWclass)
	fNWcxx.close()


def LoadDataTime(data_file, data_tree, evnum_limit = 0):

	# Information.
	print 'Loading data file ' + data_file + ' ...'
	if (evnum_limit == 0): print 'All events selected.'
	else: print str(evnum_limit)+' events selected.'

	# Input data.
	file_in = TFile(NTUPLE_PATH + data_file)
	tree_full = file_in.Get(data_tree)
	file_out = TFile(NTUPLE_PATH + "trash.root","RECREATE")
	tree_2011_wide = tree_full.CopyTree(t_name_MC+">=0. && "+t_name_MC+"<=12. && itype==-73")
	tree_2012_wide = tree_full.CopyTree(t_name_MC+">=0. && "+t_name_MC+"<=12. && itype==-83")
	tree_2011_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && itype==-73")
	tree_2012_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && itype==-83")

	PDF_gen,model_gen = CreateGenPDF()

	wide_window_MC.setVal(1)
	ev_counter = 0
	for i in tree_2011_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight4.setVal(1./PDF_gen.timemodel(eval("i."+t_name_MC)))
			data4_2011_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	ev_counter = 0
	for i in tree_2012_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight4.setVal(1./PDF_gen.timemodel(eval("i."+t_name_MC)))
			data4_2012_wide_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	wide_window_MC.setVal(0)
	ev_counter = 0
	for i in tree_2011_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight4.setVal(1./PDF_gen.timemodel(eval("i."+t_name_MC)))
			data4_2011_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1
	ev_counter = 0
	for i in tree_2012_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			t_MC.setVal(eval("i."+t_name_MC))
			MCweight4.setVal(1./PDF_gen.timemodel(eval("i."+t_name_MC)))
			data4_2012_narrow_.add(RooArgSet(t_MC,MCweight4))
			ev_counter += 1

	data4_2011_wide = RooDataSet("data4_2011_wide","data4_2011_wide",data4_2011_wide_,data4_2011_wide_.get())
	data4_2012_wide = RooDataSet("data4_2012_wide","data4_2012_wide",data4_2012_wide_,data4_2012_wide_.get())
	data4_2011_narrow = RooDataSet("data4_2011_narrow","data4_2011_narrow",data4_2011_narrow_,data4_2011_narrow_.get())
	data4_2012_narrow = RooDataSet("data4_2012_narrow","data4_2012_narrow",data4_2012_narrow_,data4_2012_narrow_.get())

	print 'Data loaded.'

	return data4_2011_wide, data4_2012_wide, data4_2011_narrow, data4_2012_narrow


def adaptiveBinning(var,nbins,applyweights,data):

	print 'Finding the bounds for ' + str(nbins) + ' equal-sized bins ...'

	# Creation of a list with the pairs [var,weight], ordered increasingly in var value
	datalist = []
	for i in range(data.numEntries()):
		x = data.get(i).getRealValue(var.GetName())
		w = data.weight()
		datalist.append([x,w])
	datalistord = [datalist[0]]
	for i in range(1,len(datalist)):
		isplaced = 0
		for j in range(len(datalistord)):
			if datalist[i][0] <= datalistord[j][0]:
				datalistord.insert(j,datalist[i])
				isplaced += 1
				break
		if isplaced == 0: datalistord.append(datalist[i])

	# Obtaintion of the binning scheme.
	if applyweights: bincontent = data.sumEntries()/float(nbins)
	else: bincontent = data.numEntries()/float(nbins)
	binningscheme = [var.getMin()]
	scannedevs = 0
	evoffset = 0
	for i in range(nbins-1):
		bincounter = evoffset
		for j in range(scannedevs,len(datalistord)):
			if applyweights: bincounter += datalistord[j][1]
			else: bincounter += 1.
			scannedevs += 1
			if bincounter >= bincontent:
				binningscheme.append(datalistord[j][0])
				evoffset = bincounter-bincontent
				break
	binningscheme.append(var.getMax())

	print 'Bounds found.'

	return binningscheme


def getRooBinning(var,boundlist):

	binning = RooBinning(var.getMin(),var.getMax())
	for i in range(1,len(boundlist)-1): binning.addBoundary(boundlist[i])
	binning.SetName("adapt_binning")

	return binning


def createTimeAccHistos(binbounds,data11_wide,data12_wide,data11_narrow,data12_narrow):

	# Two kinds of histograms are created simultaneously (duplicated):
	# list-like for the C++ class and RooDataSet-like for plotting.

	print 'Filling histograms ...'

	# Declaration of the list-like histograms.
	histlist = [[[],[]],[[],[]]]
	for i in range(len(binbounds)-1):
		histlist[0][0].append(0.)
		histlist[0][1].append(0.)
		histlist[1][0].append(0.)
		histlist[1][1].append(0.)

	# Declaration of the RooDataSet-like histograms.
	RDH_11wide_ = RooDataSet("RDH_11wide_","RDH_11wide_",RooArgSet(t_MC,MCweight4))
	RDH_12wide_ = RooDataSet("RDH_12wide_","RDH_12wide_",RooArgSet(t_MC,MCweight4))
	RDH_11narrow_ = RooDataSet("RDH_11narrow_","RDH_11narrow_",RooArgSet(t_MC,MCweight4))
	RDH_12narrow_ = RooDataSet("RDH_12narrow_","RDH_12narrow_",RooArgSet(t_MC,MCweight4))

	# Computation of the normalization factors.
	normfactors = [[0,0],[0,0]]
	for i in range(data11_wide.numEntries()):
		if data11_wide.get(i).getRealValue(t_MC.GetName()) <= binbounds[1]: normfactors[0][1] += data11_wide.get(i).getRealValue(MCweight4.GetName())/binbounds[1]
	for i in range(data12_wide.numEntries()):
		if data12_wide.get(i).getRealValue(t_MC.GetName()) <= binbounds[1]: normfactors[1][1] += data12_wide.get(i).getRealValue(MCweight4.GetName())/binbounds[1]
	for i in range(data11_narrow.numEntries()):
		if data11_narrow.get(i).getRealValue(t_MC.GetName()) <= binbounds[1]: normfactors[0][0] += data11_narrow.get(i).getRealValue(MCweight4.GetName())/binbounds[1]
	for i in range(data12_narrow.numEntries()):
		if data12_narrow.get(i).getRealValue(t_MC.GetName()) <= binbounds[1]: normfactors[1][0] += data12_narrow.get(i).getRealValue(MCweight4.GetName())/binbounds[1]

	# Auxiliar function used to fill the list-like histograms.
	def fillhist(yearcase,windowcase,tau,evweight):
		for i in range(len(binbounds)-1):
			if (tau >= binbounds[i]) and (tau < binbounds[i+1]):
				histlist[yearcase][windowcase][i] += evweight/(binbounds[i+1]-binbounds[i])
				break

	# Filling of the two kinds of histograms.
	for i in range(data11_wide.numEntries()):
		ti = data11_wide.get(i).getRealValue(t_MC.GetName())
		wi = data11_wide.get(i).getRealValue(MCweight4.GetName())/normfactors[0][1]
		fillhist(0,1,ti,wi)
		t_MC.setVal(ti)
		MCweight4.setVal(wi)
		RDH_11wide_.add(RooArgSet(t_MC,MCweight4))
	for i in range(data12_wide.numEntries()):
		ti = data12_wide.get(i).getRealValue(t_MC.GetName())
		wi = data12_wide.get(i).getRealValue(MCweight4.GetName())/normfactors[1][1]
		fillhist(1,1,ti,wi)
		t_MC.setVal(ti)
		MCweight4.setVal(wi)
		RDH_12wide_.add(RooArgSet(t_MC,MCweight4))
	for i in range(data11_narrow.numEntries()):
		ti = data11_narrow.get(i).getRealValue(t_MC.GetName())
		wi = data11_narrow.get(i).getRealValue(MCweight4.GetName())/normfactors[0][0]
		fillhist(0,0,ti,wi)
		t_MC.setVal(ti)
		MCweight4.setVal(wi)
		RDH_11narrow_.add(RooArgSet(t_MC,MCweight4))
	for i in range(data12_narrow.numEntries()):
		ti = data12_narrow.get(i).getRealValue(t_MC.GetName())
		wi = data12_narrow.get(i).getRealValue(MCweight4.GetName())/normfactors[1][0]
		fillhist(1,0,ti,wi)
		t_MC.setVal(ti)
		MCweight4.setVal(wi)
		RDH_12narrow_.add(RooArgSet(t_MC,MCweight4))

	# Applying weights to the RooDataSet-like histograms.
	RDH_11wide = RooDataSet("RDH_11wide","RDH_11wide",RDH_11wide_,RDH_11wide_.get(),"",MCweight4.GetName())
	RDH_12wide = RooDataSet("RDH_12wide","RDH_12wide",RDH_12wide_,RDH_12wide_.get(),"",MCweight4.GetName())
	RDH_11narrow = RooDataSet("RDH_11narrow","RDH_11narrow",RDH_11narrow_,RDH_11narrow_.get(),"",MCweight4.GetName())
	RDH_12narrow = RooDataSet("RDH_12narrow","RDH_12narrow",RDH_12narrow_,RDH_12narrow_.get(),"",MCweight4.GetName())

	print 'Histograms filled.'

	return histlist, [RDH_11wide,RDH_12wide,RDH_11narrow,RDH_12narrow]


def printTimeAccHistos(binbounds,histlist):

	nbins = len(binbounds)-1

	histostext = "class TAccclass {\n\n  public:\n\n  Int_t nbins = " + str(nbins) + ";\n\n  Double_t bounds(Int_t ibound) {\n\n    if (ibound == 0) {return 0.;}\n"
	for i in range(1,nbins+1): histostext += "    else if (ibound == " + str(i) + ") {return " + str(binbounds[i]) + ";}\n"
	histostext += "\n    return 0.;\n\n    };\n\n  Double_t val(Int_t year_opt,Int_t wide_window,Int_t ibin) {\n\n    if ((year_opt == 0) && (wide_window == 0) && (ibin == 0)) {return " + str(histlist[0][0][0]) + ";}\n"
	for iyear in [0,1]:
		for iwindow in [0,1]:
			for ibin in range(nbins):
				if not (iyear == 0 and iwindow == 0 and ibin == 0): histostext += "    else if ((year_opt == " + str(iyear) + ") && (wide_window == " + str(iwindow) + ") && (ibin == " + str(ibin) + ")) {return " + str(histlist[iyear][iwindow][ibin]) + ";}\n"
	histostext += "\n    return 0.;\n\n    };\n\n};"

	fTAcch = open('../../src/TimeDependent/TAccclass.h','w')
	fTAcch.write(histostext)
	fTAcch.close()


def plotTimeAccHistos(binbounds,RDSlist,output_tag):

	fr_tacc_11_wide = t_MC.frame()
	fr_tacc_12_wide = t_MC.frame()
	fr_tacc_11_narrow = t_MC.frame()
	fr_tacc_12_narrow = t_MC.frame()

	tMCbinning = getRooBinning(t_MC,binbounds)

	RDSlist[0].plotOn(fr_tacc_11_wide,RooFit.Binning(tMCbinning),RooFit.LineColor(kRed))
	RDSlist[1].plotOn(fr_tacc_12_wide,RooFit.Binning(tMCbinning),RooFit.LineColor(kRed))
	RDSlist[2].plotOn(fr_tacc_11_narrow,RooFit.Binning(tMCbinning),RooFit.LineColor(kRed))
	RDSlist[3].plotOn(fr_tacc_12_narrow,RooFit.Binning(tMCbinning),RooFit.LineColor(kRed))
	map(lambda x: x.GetYaxis().SetTitle("Efficiency (a.u.)"),[fr_tacc_11_wide,fr_tacc_12_wide,fr_tacc_11_narrow,fr_tacc_12_narrow])
	map(lambda x: x.GetXaxis().SetTitle("Time (ps)"),[fr_tacc_11_wide,fr_tacc_12_wide,fr_tacc_11_narrow,fr_tacc_12_narrow])

	c_tacc = TCanvas("c_tacc","c_tacc")
	c_tacc.Divide(2,2)
	c_tacc.cd(1)
	fr_tacc_11_wide.Draw()
	c_tacc.cd(2)
	fr_tacc_12_wide.Draw()
	c_tacc.cd(3)
	fr_tacc_11_narrow.Draw()
	c_tacc.cd(4)
	fr_tacc_12_narrow.Draw()

	c_tacc.Print(output_tag + ".root")
	c_tacc.Print(output_tag + ".pdf")


def ComputeTimeIntegrals(PDF_phys_wide,PDF_phys_narrow,data4_2011_wide,data4_2012_wide,data4_2011_narrow,data4_2012_narrow):

	T_cosh_integral_2011_wide = 0.
	T_sinh_integral_2011_wide = 0.
	T_cos_integral_2011_wide = 0.
	T_sin_integral_2011_wide = 0.
	T_cosh_integral_2012_wide = 0.
	T_sinh_integral_2012_wide = 0.
	T_cos_integral_2012_wide = 0.
	T_sin_integral_2012_wide = 0.
	T_cosh_integral_2011_narrow = 0.
	T_sinh_integral_2011_narrow = 0.
	T_cos_integral_2011_narrow = 0.
	T_sin_integral_2011_narrow = 0.
	T_cosh_integral_2012_narrow = 0.
	T_sinh_integral_2012_narrow = 0.
	T_cos_integral_2012_narrow = 0.
	T_sin_integral_2012_narrow = 0.

	for i in range(data4_2011_wide.numEntries()):
		t_var = data4_2011_wide.get(i).getRealValue(t_name_MC)
		norm = data4_2011_wide.get(i).getRealValue("MCweight4")
		T_cosh_integral_2011_wide += norm*PDF_phys_wide.T_cosh_eff(t_var)
		T_sinh_integral_2011_wide += norm*PDF_phys_wide.T_sinh_eff(t_var)
		T_cos_integral_2011_wide += norm*PDF_phys_wide.T_cos_eff(t_var)
		T_sin_integral_2011_wide += norm*PDF_phys_wide.T_sin_eff(t_var)
	for i in range(data4_2012_wide.numEntries()):
		t_var = data4_2012_wide.get(i).getRealValue(t_name_MC)
		norm = data4_2012_wide.get(i).getRealValue("MCweight4")
		T_cosh_integral_2012_wide += norm*PDF_phys_wide.T_cosh_eff(t_var)
		T_sinh_integral_2012_wide += norm*PDF_phys_wide.T_sinh_eff(t_var)
		T_cos_integral_2012_wide += norm*PDF_phys_wide.T_cos_eff(t_var)
		T_sin_integral_2012_wide += norm*PDF_phys_wide.T_sin_eff(t_var)

	for i in range(data4_2011_narrow.numEntries()):
		t_var = data4_2011_narrow.get(i).getRealValue(t_name_MC)
		norm = data4_2011_narrow.get(i).getRealValue("MCweight4")
		T_cosh_integral_2011_narrow += norm*PDF_phys_narrow.T_cosh_eff(t_var)
		T_sinh_integral_2011_narrow += norm*PDF_phys_narrow.T_sinh_eff(t_var)
		T_cos_integral_2011_narrow += norm*PDF_phys_narrow.T_cos_eff(t_var)
		T_sin_integral_2011_narrow += norm*PDF_phys_narrow.T_sin_eff(t_var)
	for i in range(data4_2012_narrow.numEntries()):
		t_var = data4_2012_narrow.get(i).getRealValue(t_name_MC)
		norm = data4_2012_narrow.get(i).getRealValue("MCweight4")
		T_cosh_integral_2012_narrow += norm*PDF_phys_narrow.T_cosh_eff(t_var)
		T_sinh_integral_2012_narrow += norm*PDF_phys_narrow.T_sinh_eff(t_var)
		T_cos_integral_2012_narrow += norm*PDF_phys_narrow.T_cos_eff(t_var)
		T_sin_integral_2012_narrow += norm*PDF_phys_narrow.T_sin_eff(t_var)

	IT_cosh_accu_2011_wide.setVal(T_cosh_integral_2011_wide/T_cosh_integral_2011_wide)
	IT_sinh_accu_2011_wide.setVal(T_sinh_integral_2011_wide/T_cosh_integral_2011_wide)
	IT_cos_accu_2011_wide.setVal(T_cos_integral_2011_wide/T_cosh_integral_2011_wide)
	IT_sin_accu_2011_wide.setVal(T_sin_integral_2011_wide/T_cosh_integral_2011_wide)
	IT_cosh_accu_2012_wide.setVal(T_cosh_integral_2012_wide/T_cosh_integral_2012_wide)
	IT_sinh_accu_2012_wide.setVal(T_sinh_integral_2012_wide/T_cosh_integral_2012_wide)
	IT_cos_accu_2012_wide.setVal(T_cos_integral_2012_wide/T_cosh_integral_2012_wide)
	IT_sin_accu_2012_wide.setVal(T_sin_integral_2012_wide/T_cosh_integral_2012_wide)
	IT_cosh_accu_2011_narrow.setVal(T_cosh_integral_2011_narrow/T_cosh_integral_2011_narrow)
	IT_sinh_accu_2011_narrow.setVal(T_sinh_integral_2011_narrow/T_cosh_integral_2011_narrow)
	IT_cos_accu_2011_narrow.setVal(T_cos_integral_2011_narrow/T_cosh_integral_2011_narrow)
	IT_sin_accu_2011_narrow.setVal(T_sin_integral_2011_narrow/T_cosh_integral_2011_narrow)
	IT_cosh_accu_2012_narrow.setVal(T_cosh_integral_2012_narrow/T_cosh_integral_2012_narrow)
	IT_sinh_accu_2012_narrow.setVal(T_sinh_integral_2012_narrow/T_cosh_integral_2012_narrow)
	IT_cos_accu_2012_narrow.setVal(T_cos_integral_2012_narrow/T_cosh_integral_2012_narrow)
	IT_sin_accu_2012_narrow.setVal(T_sin_integral_2012_narrow/T_cosh_integral_2012_narrow)


def PrintTimeInts():

	ITclass = 'class ITclass {\n\n  public:\n\n  Double_t IT_cosh(Int_t year_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (wide_window == 1)) {return '+str(IT_cosh_accu_2011_wide.getVal())+';}\n    else if ((year_opt == 0) && (wide_window == 0)) {return '+str(IT_cosh_accu_2011_narrow.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 1)) {return '+str(IT_cosh_accu_2012_wide.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 0)) {return '+str(IT_cosh_accu_2012_narrow.getVal())+';}\n    return 0.;\n    };\n\n  Double_t IT_sinh(Int_t year_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (wide_window == 1)) {return '+str(IT_sinh_accu_2011_wide.getVal())+';}\n    else if ((year_opt == 0) && (wide_window == 0)) {return '+str(IT_sinh_accu_2011_narrow.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 1)) {return '+str(IT_sinh_accu_2012_wide.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 0)) {return '+str(IT_sinh_accu_2012_narrow.getVal())+';}\n    return 0.;\n    };\n\n  Double_t IT_cos(Int_t year_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (wide_window == 1)) {return '+str(IT_cos_accu_2011_wide.getVal())+';}\n    else if ((year_opt == 0) && (wide_window == 0)) {return '+str(IT_cos_accu_2011_narrow.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 1)) {return '+str(IT_cos_accu_2012_wide.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 0)) {return '+str(IT_cos_accu_2012_narrow.getVal())+';}\n    return 0.;\n    };\n  Double_t IT_sin(Int_t year_opt, Int_t wide_window) {\n    if ((year_opt == 0) && (wide_window == 1)) {return '+str(IT_sin_accu_2011_wide.getVal())+';}\n    else if ((year_opt == 0) && (wide_window == 0)) {return '+str(IT_sin_accu_2011_narrow.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 1)) {return '+str(IT_sin_accu_2012_wide.getVal())+';}\n    else if ((year_opt == 1) && (wide_window == 0)) {return '+str(IT_sin_accu_2012_narrow.getVal())+';}\n    return 0.;\n    };\n\n};'

	fTimecxx = open('../../src/TimeDependent/ITclass.h','w')
	fTimecxx.write(ITclass)
	fTimecxx.close()
