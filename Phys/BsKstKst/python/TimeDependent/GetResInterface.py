from ROOT import *
from math import *
import time
import os
from parameters import *
gROOT.ProcessLine('.x ../src/lhcbStyle.C')


# ################################################################
# V A R I A B L E S
# ################################################################

t_name_res = "B_s0_DTF_B_s0_TAU"
ttrue_name_res = "B_s0_DTF_B_s0_TRUETAU"
terr_name_res = "B_s0_DTF_B_s0_TAUERR"

# Observables.
difft = RooRealVar("difft","t_{rec}-t_{gen} (ps)",-0.2,0.2)
deltat = RooRealVar("deltat","t_{err} (ps)",0.,0.08)

# Data.
data_difft_2011 = RooDataSet("data_difft_2011","data_difft_2011",RooArgSet(difft))
data_difft_2012 = RooDataSet("data_difft_2012","data_difft_2012",RooArgSet(difft))
data_2011 = RooDataSet("data_2011","data_2011",RooArgSet(difft,deltat))
data_2012 = RooDataSet("data_2012","data_2012",RooArgSet(difft,deltat))
data_difft_sim_2011_list = []
data_difft_sim_2012_list = []

# 1D time resolution parametrization.
sigma1_eff_2011 = RooRealVar("sigma1_eff_2011","sigma1_eff_2011",0.03,0.01,0.06)
sigma2_eff_2011 = RooRealVar("sigma2_eff_2011","sigma2_eff_2011",0.06,0.04,0.2)
f1_eff_2011 = RooRealVar("f1_eff_2011","f1_eff_2011",0.6,0.5,1.)
sigma1_eff_2012 = RooRealVar("sigma1_eff_2012","sigma1_eff_2012",0.03,0.01,0.06)
sigma2_eff_2012 = RooRealVar("sigma2_eff_2012","sigma2_eff_2012",0.06,0.04,0.2)
f1_eff_2012 = RooRealVar("f1_eff_2012","f1_eff_2012",0.6,0.5,1.)
sigma_eff_2011 = RooFormulaVar("sigma_eff_2011","sigma_eff_2011","sqrt(-2.*log(@0*exp(-17.69*17.69*@1*@1/2.)+(1.-@0)*exp(-17.69*17.69*@2*@2/2.)))/17.69",RooArgList(f1_eff_2011,sigma1_eff_2011,sigma2_eff_2011))
sigma_eff_2012 = RooFormulaVar("sigma_eff_2012","sigma_eff_2012","sqrt(-2.*log(@0*exp(-17.69*17.69*@1*@1/2.)+(1.-@0)*exp(-17.69*17.69*@2*@2/2.)))/17.69",RooArgList(f1_eff_2012,sigma1_eff_2012,sigma2_eff_2012))

# Simultaneous fit resolution parametrization.
sigma1_sim_2011_list = []
sigma2_sim_2011_list = []
sigma1_sim_2012_list = []
sigma2_sim_2012_list = []

# 2D time resolution parametrization.
q0A_2011 = RooRealVar("q0A_2011","q0A_2011",0.,0.,0.01)
q1A_2011 = RooRealVar("q1A_2011","q1A_2011",1.,0.8,1.2)
q2A_2011 = RooRealVar("q2A_2011","q2A_2011",-25.,-32.,0.)
q0B_2011 = RooRealVar("q0B_2011","q0B_2011",0.,0.,0.01)
q1B_2011 = RooRealVar("q1B_2011","q1B_2011",0.,0.,0.5)
q2B_2011 = RooRealVar("q2B_2011","q2B_2011",-11.,-20.,-6.)
q0A_2012 = RooRealVar("q0A_2012","q0A_2012",0.,0.,0.01)
q1A_2012 = RooRealVar("q1A_2012","q1A_2012",1.,0.8,1.2)
q2A_2012 = RooRealVar("q2A_2012","q2A_2012",-25.,-32.,0.)
q0B_2012 = RooRealVar("q0B_2012","q0B_2012",0.,0.,0.01)
q1B_2012 = RooRealVar("q1B_2012","q1B_2012",0.,0.,0.5)
q2B_2012 = RooRealVar("q2B_2012","q2B_2012",-11.,-20.,-6.)
deltat_mean_2011 = RooRealVar("deltat_mean_2011","deltat_mean_2011",0.,0.08)
deltat_mean_2012 = RooRealVar("deltat_mean_2012","deltat_mean_2012",0.,0.08)
off_2011 = RooRealVar("off_2011","off_2011",0.,-0.1,0.1)
off_2012 = RooRealVar("off_2012","off_2012",0.,-0.1,0.1)
f1_2011 = RooRealVar("f1_2011","f1_2011",0.69,0.5,0.9)
f1_2012 = RooRealVar("f1_2012","f1_2012",0.69,0.5,0.9)
sigmaA_2011 = RooFormulaVar("sigmaA_2011","sigmaA_2011","@0+(@1+@2*(@3-@4))*@3",RooArgList(q0A_2011,q1A_2011,q2A_2011,deltat,deltat_mean_2011))
sigmaB_2011 = RooFormulaVar("sigmaB_2011","sigmaB_2011","@0+(@1+@2*(@3-@4))*@3",RooArgList(q0B_2011,q1B_2011,q2B_2011,deltat,deltat_mean_2011))
sigmaA_2012 = RooFormulaVar("sigmaA_2012","sigmaA_2012","@0+(@1+@2*(@3-@4))*@3",RooArgList(q0A_2012,q1A_2012,q2A_2012,deltat,deltat_mean_2012))
sigmaB_2012 = RooFormulaVar("sigmaB_2012","sigmaB_2012","@0+(@1+@2*(@3-@4))*@3",RooArgList(q0B_2012,q1B_2012,q2B_2012,deltat,deltat_mean_2012))
sigma1_2011 = RooFormulaVar("sigma1_2011","sigma1_2011","@0-sqrt(@1/(1.-@1))*@2",RooArgList(sigmaA_2011,f1_2011,sigmaB_2011))
sigma2_2011 = RooFormulaVar("sigma2_2011","sigma2_2011","@0+sqrt((1.-@1)/@1)*@2",RooArgList(sigmaA_2011,f1_2011,sigmaB_2011))
sigma1_2012 = RooFormulaVar("sigma1_2012","sigma1_2012","@0-sqrt(@1/(1.-@1))*@2",RooArgList(sigmaA_2012,f1_2012,sigmaB_2012))
sigma2_2012 = RooFormulaVar("sigma2_2012","sigma2_2012","@0+sqrt((1.-@1)/@1)*@2",RooArgList(sigmaA_2012,f1_2012,sigmaB_2012))

# Marginal PDF parametrization.
gamma_2011_A = RooRealVar("gamma_2011_A","gamma_2011_A",1.40444e+01,10.,20.)
beta_2011_A = RooRealVar("beta_2011_A","beta_2011_A",2.20383e-03,0.001,0.01)
gamma_2011_B = RooRealVar("gamma_2011_B","gamma_2011_B",2.90042e+00,1.,10.)
beta_2011_B = RooRealVar("beta_2011_B","beta_2011_B",1.14178e-02,0.005,0.02)
gamma_2012_A = RooRealVar("gamma_2012_A","gamma_2012_A",1.43411e+01,10.,20.)
beta_2012_A = RooRealVar("beta_2012_A","beta_2012_A",2.17901e-03,0.0005,0.01)
gamma_2012_B = RooRealVar("gamma_2012_B","gamma_2012_B",3.32812e+00,1.,10.)
beta_2012_B = RooRealVar("beta_2012_B","beta_2012_B",9.99999e-03,0.0005,0.012)
f_marg_2011_A = RooRealVar("f_marg_2011_A","f_marg_2011_A",8.83992e-01,0.5,1.)
f_marg_2012_A = RooRealVar("f_marg_2012_A","f_marg_2012_A",8.41554e-01,0.5,1.)
gamma_2011_A.setConstant(1)
beta_2011_A.setConstant(1)
gamma_2012_A.setConstant(1)
beta_2012_A.setConstant(1)
gamma_2011_B.setConstant(1)
beta_2011_B.setConstant(1)
gamma_2012_B.setConstant(1)
beta_2012_B.setConstant(1)
f_marg_2011_A.setConstant(1)
f_marg_2012_A.setConstant(1)

# Effective 1D PDF.
gaus1_eff_2011 = RooGaussian("gaus1_eff_2011","gaus1_eff_2011",difft,off_2011,sigma1_eff_2011)
gaus2_eff_2011 = RooGaussian("gaus2_eff_2011","gaus2_eff_2011",difft,off_2011,sigma2_eff_2011)
gaus1_eff_2012 = RooGaussian("gaus1_eff_2012","gaus1_eff_2012",difft,off_2012,sigma1_eff_2012)
gaus2_eff_2012 = RooGaussian("gaus2_eff_2012","gaus2_eff_2012",difft,off_2012,sigma2_eff_2012)
res_eff_2011 = RooAddPdf("res_eff_2011","res_eff_2011",gaus1_eff_2011,gaus2_eff_2011,f1_eff_2011)
res_eff_2012 = RooAddPdf("res_eff_2012","res_eff_2012",gaus1_eff_2012,gaus2_eff_2012,f1_eff_2012)

# Full 2D PDF.
marg_pdf_2011_A = RooGamma("marg_pdf_2011_A","marg_pdf_2011_A",deltat,gamma_2011_A,beta_2011_A,zero)
marg_pdf_2012_A = RooGamma("marg_pdf_2012_A","marg_pdf_2012_A",deltat,gamma_2012_A,beta_2012_A,zero)
marg_pdf_2011_B = RooGamma("marg_pdf_2011_B","marg_pdf_2011_B",deltat,gamma_2011_B,beta_2011_B,zero)
marg_pdf_2012_B = RooGamma("marg_pdf_2012_B","marg_pdf_2012_B",deltat,gamma_2012_B,beta_2012_B,zero)
marg_pdf_2011 = RooAddPdf("marg_pdf_2011","marg_pdf_2011",marg_pdf_2011_A,marg_pdf_2011_B,f_marg_2011_A)
marg_pdf_2012 = RooAddPdf("marg_pdf_2012","marg_pdf_2012",marg_pdf_2012_A,marg_pdf_2012_B,f_marg_2012_A)
gaus1_2011 = RooGaussian("gaus1_2011","gaus1_2011",difft,off_2011,sigma1_2011)
gaus2_2011 = RooGaussian("gaus2_2011","gaus2_2011",difft,off_2011,sigma2_2011)
gaus1_2012 = RooGaussian("gaus1_2012","gaus1_2012",difft,off_2012,sigma1_2012)
gaus2_2012 = RooGaussian("gaus2_2012","gaus2_2012",difft,off_2012,sigma2_2012)
res_2011 = RooAddPdf("res_2011","res_2011",gaus1_2011,gaus2_2011,f1_2011)
res_2012 = RooAddPdf("res_2012","res_2012",gaus1_2012,gaus2_2012,f1_2012)
full_pdf_2011 = RooProdPdf("full_pdf_2011","full_pdf_2011",RooArgSet(res_2011),RooFit.Conditional(RooArgSet(marg_pdf_2011),RooArgSet(deltat)))
full_pdf_2012 = RooProdPdf("full_pdf_2012","full_pdf_2012",RooArgSet(res_2012),RooFit.Conditional(RooArgSet(marg_pdf_2012),RooArgSet(deltat)))


# ################################################################
# F U N C T I O N S
# ################################################################

def DefineParams(bin_sim):

	r = range(bin_sim)
	sigma1_2011_l = map(RooRealVar,map(lambda x:"sigma1_"+str(x)+"_sim_2011",r),map(lambda x:"sigma1_"+str(x)+"_sim_2011",r),map(lambda x:0.03,r),map(lambda x:0.01,r),map(lambda x:0.06,r))
	sigma2_2011_l = map(RooRealVar,map(lambda x:"sigma2_"+str(x)+"_sim_2011",r),map(lambda x:"sigma2_"+str(x)+"_sim_2011",r),map(lambda x:0.06,r),map(lambda x:0.04,r),map(lambda x:0.1,r))
	sigma1_2012_l = map(RooRealVar,map(lambda x:"sigma1_"+str(x)+"_sim_2012",r),map(lambda x:"sigma1_"+str(x)+"_sim_2012",r),map(lambda x:0.03,r),map(lambda x:0.01,r),map(lambda x:0.06,r))
	sigma2_2012_l = map(RooRealVar,map(lambda x:"sigma2_"+str(x)+"_sim_2012",r),map(lambda x:"sigma2_"+str(x)+"_sim_2012",r),map(lambda x:0.06,r),map(lambda x:0.04,r),map(lambda x:0.1,r))
	for i in sigma1_2011_l: sigma1_sim_2011_list.append(i)
	for i in sigma2_2011_l: sigma2_sim_2011_list.append(i)
	for i in sigma1_2012_l: sigma1_sim_2012_list.append(i)
	for i in sigma2_2012_l: sigma2_sim_2012_list.append(i)

def InvCdf(x,cdf):

	step = (deltat.getMax()-deltat.getMin())/10000.
	for i in range(10000):
		deltat.setVal(i*step)
		if cdf.getVal() >= x: return i*step
	return deltat.getMax()

def GetBinning(nbins):

	cdf_marg_2011 = marg_pdf_2011.createCdf(RooArgSet(deltat))
	cdf_marg_2012 = marg_pdf_2012.createCdf(RooArgSet(deltat))
	bin_step = 1./nbins
	binning_2011 = [0.]
	binning_2012 = [0.]
	for i in range(nbins):
		binning_2011.append(InvCdf((i+1.)*bin_step,cdf_marg_2011))
		binning_2012.append(InvCdf((i+1.)*bin_step,cdf_marg_2012))
	return binning_2011, binning_2012

def CreateDatasets(bin_sim):

	r = range(bin_sim)
	data_2011_l = map(RooDataSet,map(lambda x:"data_difft_"+str(x)+"_sim_2011",r),map(lambda x:"data_difft_"+str(x)+"_sim_2011",r),map(lambda x:RooArgSet(difft),r))
	data_2012_l = map(RooDataSet,map(lambda x:"data_difft_"+str(x)+"_sim_2012",r),map(lambda x:"data_difft_"+str(x)+"_sim_2012",r),map(lambda x:RooArgSet(difft),r))
	for i in data_2011_l: data_difft_sim_2011_list.append(i)
	for i in data_2012_l: data_difft_sim_2012_list.append(i)

def LoadData_1D(name_2011,name_2012):

	print "Creating the dataset for 2011 ..."
	f_2011 = TFile(NTUPLE_PATH + name_2011 + ".root")
	t_2011 = f_2011.Get("DecayTree")
	for i in t_2011:
		if (eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.):
			difft.setVal(eval("i."+t_name_res)-eval("i."+ttrue_name_res))
			data_difft_2011.add(RooArgSet(difft))
	print "Dataset created."

	print "Creating the dataset for 2012 ..."
	f_2012 = TFile(NTUPLE_PATH + name_2012 + ".root")
	t_2012 = f_2012.Get("DecayTree")
	for i in t_2012:
		if (eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.):
			difft.setVal(eval("i."+t_name_res)-eval("i."+ttrue_name_res))
			data_difft_2012.add(RooArgSet(difft))
	print "Dataset created."

	return

def LoadData_sim(name_2011,name_2012,binning_2011,binning_2012):

	print "Creating the datasets for 2011 ..."
	f_2011 = TFile(NTUPLE_PATH + name_2011 + ".root")
	t_2011 = f_2011.Get("DecayTree")
	for i in t_2011:
		if (eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.):
			difft.setVal(eval("i."+t_name_res)-eval("i."+ttrue_name_res))
			for j in range(len(binning_2011)-1):
				if (eval("i."+terr_name_res) >= binning_2011[j] and eval("i."+terr_name_res) < binning_2011[j+1]): data_difft_sim_2011_list[j].add(RooArgSet(difft))
	print "Datasets created."

	print "Creatings the dataset for 2012 ..."
	f_2012 = TFile(NTUPLE_PATH + name_2012 + ".root")
	t_2012 = f_2012.Get("DecayTree")
	for i in t_2012:
		if (eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.):
			difft.setVal(eval("i."+t_name_res)-eval("i."+ttrue_name_res))
			for j in range(len(binning_2012)-1):
				if (eval("i."+terr_name_res) >= binning_2012[j] and eval("i."+terr_name_res) < binning_2012[j+1]): data_difft_sim_2012_list[j].add(RooArgSet(difft))
	print "Datasets created."

	return

def LoadData_2D(name_2011,name_2012):

	print "Creating the dataset for 2011 ..."
	f_2011 = TFile(NTUPLE_PATH + name_2011 + ".root")
	t_2011 = f_2011.Get("DecayTree")
	for i in t_2011:
		if (eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.):
			difft.setVal(eval("i."+t_name_res)-eval("i."+ttrue_name_res))
			deltat.setVal(eval("i."+terr_name_res))
			data_2011.add(RooArgSet(difft,deltat))
	print "Dataset created."

	print "Creating the dataset for 2012 ..."
	f_2012 = TFile(NTUPLE_PATH + name_2012 + ".root")
	t_2012 = f_2012.Get("DecayTree")
	for i in t_2012:
		if (eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.):
			difft.setVal(eval("i."+t_name_res)-eval("i."+ttrue_name_res))
			deltat.setVal(eval("i."+terr_name_res))
			data_2012.add(RooArgSet(difft,deltat))
	print "Dataset created."

	deltat_mean_2011.setVal(data_2011.mean(deltat))
	deltat_mean_2011.setConstant(1)
	deltat_mean_2012.setVal(data_2012.mean(deltat))
	deltat_mean_2012.setConstant(1)

	return

def Fit1DPDF(offset):

	if offset == 0:
		off_2011.setConstant(1)
		off_2012.setConstant(1)
		print "\n*** INFO: Mean offset set to 0. ***"
	elif offset == 1: print "\n*** INFO: Mean offset floated during fitting. ***"
	else:
		print "ERROR: wrong value for the mean offset parameter."
		return

	fit_2011 = res_eff_2011.fitTo(data_difft_2011,RooFit.Minos(1),RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.Save(kTRUE))
	fit_2012 = res_eff_2012.fitTo(data_difft_2012,RooFit.Minos(1),RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.Save(kTRUE))

	return fit_2011, fit_2012

def PrintTReseffPars():

	trespars = "class TReseffclass {\n\n  public:\n\n  Double_t f1(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(f1_eff_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(f1_eff_2012.getVal())+";}\n    return 0.;\n    };\n\n  Double_t sigma1(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(sigma1_eff_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(sigma1_eff_2012.getVal())+";}\n    return 0.;\n    };\n\n  Double_t sigma2(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(sigma2_eff_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(sigma2_eff_2012.getVal())+";}\n    return 0.;\n    };\n\n  Double_t off(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(off_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(off_2012.getVal())+";}\n    return 0.;\n    };\n\n};"

	fpar = open('../../src/TimeDependent/TReseffclass.h','w')
	fpar.write(trespars)
	fpar.close()

def FitMargPDF():

	gamma_2011_A.setConstant(0)
	beta_2011_A.setConstant(0)
	gamma_2012_A.setConstant(0)
	beta_2012_A.setConstant(0)
	gamma_2011_B.setConstant(0)
	beta_2011_B.setConstant(0)
	gamma_2012_B.setConstant(0)
	beta_2012_B.setConstant(0)
	f_marg_2011_A.setConstant(0)
	f_marg_2012_A.setConstant(0)

	marg_pdf_2011.fitTo(data_2011)
	marg_pdf_2012.fitTo(data_2012)

	gamma_2011_A.setConstant(1)
	beta_2011_A.setConstant(1)
	gamma_2012_A.setConstant(1)
	beta_2012_A.setConstant(1)
	gamma_2011_B.setConstant(1)
	beta_2011_B.setConstant(1)
	gamma_2012_B.setConstant(1)
	beta_2012_B.setConstant(1)
	f_marg_2011_A.setConstant(1)
	f_marg_2012_A.setConstant(1)

def Fit2DPDF(pol_order,q0_term,offset):

	if pol_order == 0:
		q1A_2011.setVal(0.)
		q1B_2011.setVal(0.)
		q1A_2012.setVal(0.)
		q1B_2012.setVal(0.)
		q2A_2011.setVal(0.)
		q2B_2011.setVal(0.)
		q2A_2012.setVal(0.)
		q2B_2012.setVal(0.)
		q1A_2011.setConstant(1)
		q1B_2011.setConstant(1)
		q1A_2012.setConstant(1)
		q1B_2012.setConstant(1)
		q2A_2011.setConstant(1)
		q2B_2011.setConstant(1)
		q2A_2012.setConstant(1)
		q2B_2012.setConstant(1)
		print "\n*** INFO: Constant parametrization for sigma_eff(t_error). ***"
	elif pol_order == 1:
		q2A_2011.setVal(0.)
		q2B_2011.setVal(0.)
		q2A_2012.setVal(0.)
		q2B_2012.setVal(0.)
		q2A_2011.setConstant(1)
		q2B_2011.setConstant(1)
		q2A_2012.setConstant(1)
		q2B_2012.setConstant(1)
		print "\n*** INFO: Linear parametrization for sigma_eff(t_error). ***"
	elif pol_order == 2: print "\n*** INFO: Quadratic parametrization for sigma_eff(t_error). ***"
	else:
		print "ERROR: wrong order of the polinomial."
		return

	if q0_term == 0:
		q0A_2011.setVal(0.)
		q0B_2011.setVal(0.)
		q0A_2012.setVal(0.)
		q0B_2012.setVal(0.)
		q0A_2011.setConstant(1)
		q0B_2011.setConstant(1)
		q0A_2012.setConstant(1)
		q0B_2012.setConstant(1)
		print "\n*** INFO: Order-0 in the width parametrization set to 0. ***"
	elif q0_term == 1: print "\n*** INFO: Order-0 in the width parametrization floated during fitting. ***"
	else:
		print "ERROR: wrong value for the order-0 parameter."
		return

	if offset == 0:
		off_2011.setConstant(1)
		off_2012.setConstant(1)
		print "\n*** INFO: Mean offset set to 0. ***"
	elif offset == 1: print "\n*** INFO: Mean offset floated during fitting. ***"
	else:
		print "ERROR: wrong value for the mean offset parameter."
		return

	fit_2011 = full_pdf_2011.fitTo(data_2011,RooFit.Minos(0),RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.Save(kTRUE))
	fit_2012 = full_pdf_2012.fitTo(data_2012,RooFit.Minos(0),RooFit.NumCPU(8),RooFit.Timer(kTRUE),RooFit.Save(kTRUE))

	return fit_2011, fit_2012

def PrintTResPars():

	trespars = "class TResclass {\n\n  public:\n\n  Double_t f1(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(f1_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(f1_2012.getVal())+";}\n    return 0.;\n    };\n\n  Double_t mean(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(deltat_mean_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(deltat_mean_2012.getVal())+";}\n    return 0.;\n    };\n\n  Double_t q0A(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(q0A_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(q0A_2012.getVal())+";}\n    return 0.;\n    };\n\n  Double_t q0B(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(q0B_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(q0B_2012.getVal())+";}\n    return 0.;\n    };\n\n  Double_t q1A(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(q1A_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(q1A_2012.getVal())+";}\n    return 0.;\n    };\n\n  Double_t q1B(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(q1B_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(q1B_2012.getVal())+";}\n    return 0.;\n    };\n\n  Double_t q2A(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(q2A_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(q2A_2012.getVal())+";}\n    return 0.;\n    };\n\n  Double_t q2B(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(q2B_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(q2B_2012.getVal())+";}\n    return 0.;\n    };\n\n  Double_t off(Int_t year_opt) {\n    if (year_opt == 0) {return "+str(off_2011.getVal())+";}\n    else if (year_opt == 1) {return "+str(off_2012.getVal())+";}\n    return 0.;\n    };\n\n};"

	fpar = open('../../src/TimeDependent/TResclass.h','w')
	fpar.write(trespars)
	fpar.close()

def Make1DPlot(nbins_difft):

	fdifft11 = difft.frame()
	fdifft12 = difft.frame()
	data_difft_2011.plotOn(fdifft11,RooFit.Binning(nbins_difft),RooFit.LineColor(kBlue))
	res_eff_2011.plotOn(fdifft11,RooFit.LineColor(kRed))
	data_difft_2012.plotOn(fdifft12,RooFit.Binning(nbins_difft),RooFit.LineColor(kBlue))
	res_eff_2012.plotOn(fdifft12,RooFit.LineColor(kRed))

	leg11 = TLegend(0.6,0.7,0.95,0.9)
	leg11.SetFillColor(kWhite)
	leg11.SetBorderSize(0)
	leg11.SetHeader("2011 MC data")
	leg11.AddEntry(fdifft11.findObject("h_data_difft_2011"),"Data","epl")
	leg11.AddEntry(fdifft11.findObject("res_eff_2011_Norm[difft]"),"2-Gaussian fit","epl")
	leg12 = TLegend(0.6,0.7,0.95,0.9)
	leg12.SetFillColor(kWhite)
	leg12.SetBorderSize(0)
	leg12.SetHeader("2012 MC data")
	leg12.AddEntry(fdifft12.findObject("h_data_difft_2012"),"Data","epl")
	leg12.AddEntry(fdifft12.findObject("res_eff_2012_Norm[difft]"),"2-Gaussian fit","epl")

	c1D = TCanvas("c1D","c1D",1400,600)
	c1D.Divide(2)
	c1D.cd(1)
	fdifft11.Draw()
	leg11.Draw()
	c1D.cd(2)
	fdifft12.Draw()
	leg12.Draw()
	c1D.Print("TimeRes1Dplot.root")
	c1D.Print("TimeRes1Dplot.pdf")

def printSigmaEff(fit_2011,fit_2012):

	print '********************************'
	print 'Year 2011:'
	print 'sigma_eff = %.2f' % (1000.*sigma_eff_2011.getVal())+' +- %.2f' % (1000.*sigma_eff_2011.getPropagatedError(fit_2011))+' fs'
	print '--------------------------------'
	print 'Year 2012:'
	print 'sigma_eff = %.2f' % (1000.*sigma_eff_2012.getVal())+' +- %.2f' % (1000.*sigma_eff_2012.getPropagatedError(fit_2012))+' fs'
	print '********************************'

def Make2DPlot(nbins_difft,nbins_deltat):

	h11data = data_2011.createHistogram(difft,deltat,nbins_difft,nbins_deltat)
	h12data = data_2012.createHistogram(difft,deltat,nbins_difft,nbins_deltat)
	h11pdf = full_pdf_2011.createHistogram("h_pdf_2011",difft,RooFit.Binning(nbins_difft),RooFit.YVar(deltat,RooFit.Binning(nbins_deltat)))
	h12pdf = full_pdf_2012.createHistogram("h_pdf_2012",difft,RooFit.Binning(nbins_difft),RooFit.YVar(deltat,RooFit.Binning(nbins_deltat)))
	h11pdf.SetLineColor(kRed)
	h12pdf.SetLineColor(kRed)
	h11data.GetXaxis().SetTitle("t_{rec}-t_{gen} (ps)")
	h12data.GetXaxis().SetTitle("t_{rec}-t_{gen} (ps)")
	h11data.GetYaxis().SetTitle("t_{err} (ps)")
	h12data.GetYaxis().SetTitle("t_{err} (ps)")

	fdifft11 = difft.frame()
	fdifft12 = difft.frame()
	data_2011.plotOn(fdifft11,RooFit.Binning(nbins_difft),RooFit.LineColor(kBlue))
	full_pdf_2011.plotOn(fdifft11,RooFit.LineColor(kRed))
	data_2012.plotOn(fdifft12,RooFit.Binning(nbins_difft),RooFit.LineColor(kBlue))
	full_pdf_2012.plotOn(fdifft12,RooFit.LineColor(kRed))

	fdeltat11 = deltat.frame()
	fdeltat12 = deltat.frame()
	data_2011.plotOn(fdeltat11,RooFit.Binning(nbins_deltat),RooFit.LineColor(kBlue))
	full_pdf_2011.plotOn(fdeltat11,RooFit.LineColor(kRed))
	data_2012.plotOn(fdeltat12,RooFit.Binning(nbins_deltat),RooFit.LineColor(kBlue))
	full_pdf_2012.plotOn(fdeltat12,RooFit.LineColor(kRed))

	c2D = TCanvas("c2D","c2D",1200,800)
	c2D.Divide(3,2)
	c2D.cd(1)
	h11data.Draw("lego")
	h11pdf.Draw("surfsame")
	c2D.cd(2)
	fdifft11.Draw()
	c2D.cd(3)
	fdeltat11.Draw()
	c2D.cd(4)
	h12data.Draw("lego")
	h12pdf.Draw("surfsame")
	c2D.cd(5)
	fdifft12.Draw()
	c2D.cd(6)
	fdeltat12.Draw()
	c2D.Print("TimeRes2Dplot.root")
	c2D.Print("TimeRes2Dplot.pdf")
