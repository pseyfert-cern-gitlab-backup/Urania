#********************************************************************
#
# DESCRIPTION: script used to fit or generate events corresponding
# to the Bs->(K+pi-)(K-pi+) decay.
# AUTHOR: Julian Garcia Pardinhas, julian.garcia.pardinas@rai.usc.es
# UNIVERSITY: Universidade de Santiago de Compostela
# DATE: 11/2014
#
#********************************************************************

from FitnGenInterface import *


# ################################################################
# G L O B A L   O P T I O N S
# ################################################################

# Observables to fit.
TD_fit = 1
# 0 -> flavour averaged, time integrated, amplitude fit (SM approach, ideal time acceptance and resolution)
# 1 -> flavour tagged, time dependent, amplitude fit

# Wide Window.
wide_window = 1

# Acceptance description.
acc_type = 2
# 0 -> flat acceptance
# 1 -> parametric accetance + splines for fitting and plotting
# 2 -> normalization weights + splines for fitting and parametric accetance + splines for plotting
# 3 -> toy MC generation acceptance

# Time resolution model.
inf_t_res = 0 # 1 for ideal model / 0 for gaussian like resolution

# CP violation in the model.
Blinding = 1
No_CP_Switch = 0
No_dirCP_Switch = 0
Same_CP_Switch = 1

# Fixed params.
fix_re_amps = 0
fix_dirCP_asyms = 0
fix_im_amps = 0
fix_weak_phases = 0
fix_mixing_params = 0
fix_calib_params = 0

# Systematic studies.
pw_alternative_model = 0
f_Kst1410_rel2_Kst892 = 0.2
delta_Kst1410_rel2_Kst892 = 0.
f_Kst1680_rel2_Kst892 = 0.2
delta_Kst1680_rel2_Kst892 = 0.

# Data used in the fit.
data_file = 'AnalysisOutWSWeightsSelectedAllBranchesReduced.root'#'AnalysisOutWSWeightsSelected_PHIstudy.root'
data_tree = 'AnalysisTree'
MC_file = 'AnalysisOutWSWeightsSelectedAllBranchesReduced.root'#'AnalysisOutWithCuts_AllBranches_PHIstudy.root'
MC_tree = 'AnalysisTree'
MC_type = 1 # 0 for Toy MC / 1 for VV.
data_type = "real" # "real" for real data from 2011 and 2012 / "MC" for Monte Carlo simulation.
sweighted = 1
extra_cuts = ""#"abs(B_s0_MM-5366.)<30."#"abs(B_s0_MM-5366.)<25. && bdtoutput>0.05 && Kplus_ProbNNk>0.5 && Kminus_ProbNNk>0.5 && Kplus_ProbNNpi<0.5 && Kminus_ProbNNpi<0.5"

evnum_limit = 0

# Fit options.
num_CPU = 16
activ_minos = 0
fit_strategy = 1

# Plotting options.
m_binning = 30
cos_binning = 12
phi_binning = 12
t_binning = 30

# Generation options.
nexperiments = 5
nevents = 1700
njobs = 1
use_GRID = 0
exp_output_tag = "NarrowWindow"
fit_CondVarDistr = 0
recompute_maxima = 0
maxima_computation_num_points = 1E7


# ################################################################
# F I T   F U N C T I O N S
# ################################################################

def fit():

	# Compile and load the C++ libraries.
	if use_GRID: CompileLibsGRID()
	else: ForceCompileLibs()

	# Summary of the model options.
	information(TD_fit,data_type,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,acc_type,\
inf_t_res,wide_window,fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params,pw_alternative_model)

	# Data importation.
	data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,MC_tree,MC_type,TD_fit,sweighted,wide_window,extra_cuts,evnum_limit,use_GRID)

	# Construction of the model.
	setParamVals(wide_window)

	# Uncomment below for VV only fit, when in narrow window.
	#for par in [reA00,reA01,reA10,imA00,imA01,imA10]:
	#	par.setVal(0.)
	#	par.setConstant(1)

	model, params = createSimPDF(TD_fit,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,acc_type,\
inf_t_res,wide_window,data_file,fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

	# Performance of the fit.
	result = DoFit(model[0],data[0],wide_window,TD_fit,num_CPU,activ_minos,fit_strategy,fix_mixing_params,fix_calib_params)

	# Print out of the measured parameters.
	printresultoldformat(result)
	for i in params: print i.GetName()+'.setVal('+str(i.getVal())+')'
	fitprint2LaTeX_ReAImA('FitParams',params,wide_window,No_CP_Switch,Blinding,fix_mixing_params,fix_calib_params)
	fitprint2LaTeX_Polar(result,'FitParams',params,wide_window,No_CP_Switch,Blinding,fix_mixing_params,fix_calib_params)
	fitprint2LaTeX_OldStyle(result,'FitParams')
	printCorrMatrix(result)

	return result

def fitnplot():

	# Compile and load the C++ libraries.
	if use_GRID: CompileLibsGRID()
	else: ForceCompileLibs()

	# Summary of the model options.
	information(TD_fit,data_type,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,acc_type,\
inf_t_res,wide_window,fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params,pw_alternative_model)

	# Data importation.
	data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,MC_tree,MC_type,TD_fit,sweighted,wide_window,extra_cuts,evnum_limit,use_GRID)

	# Construction of the model.
	setParamVals(wide_window)

	# Uncomment below for VV only fit, when in narrow window.
	#for par in [reA00,reA01,reA10,imA00,imA01,imA10]:
	#	par.setVal(0.)
	#	par.setConstant(1)

	model, params = createSimPDF(TD_fit,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,acc_type,\
inf_t_res,wide_window,data_file,fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

	# Performance of the fit.
	result = DoFit(model[0],data[0],wide_window,TD_fit,num_CPU,activ_minos,fit_strategy,fix_mixing_params,fix_calib_params)

	# Print out of the measured parameters.
	printresultoldformat(result)
	for i in params: print i.GetName()+'.setVal('+str(i.getVal())+')'
	fitprint2LaTeX_ReAImA('FitParams',params,wide_window,No_CP_Switch,Blinding,fix_mixing_params,fix_calib_params)
	fitprint2LaTeX_Polar(result,'FitParams',params,wide_window,No_CP_Switch,Blinding,fix_mixing_params,fix_calib_params)
	fitprint2LaTeX_OldStyle(result,'FitParams')
	printCorrMatrix(result)

	# Plot of the the 6 1D proyections corresponding to the 2 masses, 3 angles and decay time.
	map(lambda x:x.setDenPlotVarVal(),model[1:5])
	plot61Ddata(data[0], 0, wide_window, m_binning, cos_binning, phi_binning, t_binning) # Plotting the dataset.
	plot61Dmodel(model[0], data[0], wide_window) # Plotting the full model.
	plot61Dcomponent(model[0], data[0], wide_window, 'SS', kOrange, 1)
	plot61Dcomponent(model[0], data[0], wide_window, 'SV', kOrange+2, 1)
	plot61Dcomponent(model[0], data[0], wide_window, 'VS', kOrange+2, 2)
	plot61Dcomponent(model[0], data[0], wide_window, 'VV', kRed, 1)
	if wide_window:
		plot61Dcomponent(model[0], data[0], wide_window, 'ST', kGreen+3, 1)
		plot61Dcomponent(model[0], data[0], wide_window, 'TS', kGreen+3, 2)
		plot61Dcomponent(model[0], data[0], wide_window, 'VT', kMagenta+1, 1)
		plot61Dcomponent(model[0], data[0], wide_window, 'TV', kMagenta+1, 2)
		plot61Dcomponent(model[0], data[0], wide_window, 'TT', kBlue-6, 1)
	plot61Ddata(data[0], 1, wide_window, m_binning, cos_binning, phi_binning, t_binning) # Overlaying the data points.
	leg61D = ROOT.TLegend(0.5,0.3,0.9,0.9)
	c1 = create61Dcanvas(wide_window,leg61D) # Drawing the plots in a canvas.
	c1.Print("plot61D.pdf") # Printing the canvas in a pdf file.
	c1.Print("plot61D.root") # Printing the canvas in a root file.

	return result

def plot():

	# Compile and load the C++ libraries.
	if use_GRID: CompileLibsGRID()
	else: ForceCompileLibs()

	# Summary of the model options.
	information(TD_fit,data_type,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,acc_type,\
inf_t_res,wide_window,fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params,pw_alternative_model)

	# Data importation.
	data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,MC_tree,MC_type,TD_fit,sweighted,wide_window,extra_cuts,evnum_limit,use_GRID)

	# Construction of the model.
	setParamVals(wide_window)

	model, params = createSimPDF(TD_fit,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,acc_type,\
inf_t_res,wide_window,data_file,fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

	# Plot of the the 6 1D proyections corresponding to the 2 masses, 3 angles and decay time.
	map(lambda x:x.setDenPlotVarVal(),model[1:5])
	plot61Ddata(data[0], 0, wide_window, m_binning, cos_binning, phi_binning, t_binning) # Plotting the dataset.
	plot61Dmodel(model[0], data[0], wide_window) # Plotting the full model.
	plot61Dcomponent(model[0], data[0], wide_window, 'SS', kOrange, 1)
	plot61Dcomponent(model[0], data[0], wide_window, 'SV', kOrange+2, 1)
	plot61Dcomponent(model[0], data[0], wide_window, 'VS', kOrange+2, 2)
	plot61Dcomponent(model[0], data[0], wide_window, 'VV', kRed, 1)
	if wide_window:
		plot61Dcomponent(model[0], data[0], wide_window, 'ST', kGreen+3, 1)
		plot61Dcomponent(model[0], data[0], wide_window, 'TS', kGreen+3, 2)
		plot61Dcomponent(model[0], data[0], wide_window, 'VT', kMagenta+1, 1)
		plot61Dcomponent(model[0], data[0], wide_window, 'TV', kMagenta+1, 2)
		plot61Dcomponent(model[0], data[0], wide_window, 'TT', kBlue-6, 1)
	plot61Ddata(data[0], 1, wide_window, m_binning, cos_binning, phi_binning, t_binning) # Overlaying the data points.
	leg61D = ROOT.TLegend(0.5,0.3,0.9,0.9)
	c1 = create61Dcanvas(wide_window,leg61D) # Drawing the plots in a canvas.
	c1.Print("plot61D.pdf") # Printing the canvas in a pdf file.
	c1.Print("plot61D.root") # Printing the canvas in a root file.


# ################################################################
# M O N T E   C A R L O   G E N E R A T I O N   F U N C T I O N
# ################################################################

def gen(exp_name):

	# Compile and load the C++ libraries.
	ForceCompileLibs()

	# Data importation.
	data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,MC_tree,MC_type,TD_fit,sweighted,wide_window,extra_cuts,evnum_limit,use_GRID)

	# Construction of the model.
	setParamVals(wide_window)
	model, params = createPDF(Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,3,\
inf_t_res,wide_window,data_file,fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

	# Fit of the conditional variable profiles.
	CondVarStudy(fit_CondVarDistr,model,params,data,hist_mistag_SSK,hist_mistag_OS,hist_deltat)

	# Configuration of the generator.
	model.SetGenerator(wide_window,recompute_maxima,int(maxima_computation_num_points))

	# Event generation.
	genTree(nevents,model,exp_output_tag+'_exp'+exp_name)

def MCSJob(job_ID,nevs,nexps,outtag,GRID):

	# Compile and load the C++ libraries.
	if GRID: CompileLibsGRID()
	else: CompileLibs()

	# Data importation.
	if GRID: data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData('',data_type,data_file,data_tree,MC_file,MC_tree,MC_type,TD_fit,sweighted,wide_window,extra_cuts,evnum_limit,use_GRID)
	else: data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,MC_tree,MC_type,TD_fit,sweighted,wide_window,extra_cuts,evnum_limit,use_GRID)

	# Construction of the model.
	setParamVals(wide_window)
	model, params = createPDF(Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,3,\
inf_t_res,wide_window,data_file,fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

	# Fit of the conditional variable profiles.
	CondVarStudy(fit_CondVarDistr,model,params,data,hist_mistag_SSK,hist_mistag_OS,hist_deltat)

	# Configuration of the generator.
	model.SetGenerator(wide_window,recompute_maxima,int(maxima_computation_num_points))

	# Event generation and fitting.
	doToyMCStudy(nexps,nevs,model,outtag,job_ID,GRID,num_CPU,activ_minos,fit_strategy,wide_window,fix_mixing_params,fix_calib_params)

def MCSManyExp():

	# Configure and submit the jobs to Ganga.
	MCSGrid(nexperiments,nevents,njobs,exp_output_tag,use_GRID)


# ################################################################
# L O G   L I K E L I H O O D   S C A N
# ################################################################

def profiles():

	# Compile and load the C++ libraries.
	ForceCompileLibs()

	# Data importation.
	data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,MC_tree,MC_type,TD_fit,sweighted,wide_window,extra_cuts,evnum_limit,use_GRID)

	# Construction of the model.
	setParamVals(wide_window)

	f_VV.setVal(1.)
	for par in [f_VV,f_SS,D_SVVS,delta00,delta01,delta10]: par.setConstant(1)

	model, params = createSimPDF(TD_fit,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,acc_type,\
inf_t_res,wide_window,data_file,fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)
	
	# Plot of the likelihood profile.
	nll = ROOT.RooNLLVar("nll","nll",model[0],data[0],ROOT.RooFit.NumCPU(num_CPU))
	for par in [phis]:#params:
		print 'Plotting likelyhood profile for '+par.GetName()+' ...'
		printllprofile(par,nll)
		print 'Likelyhood profile plotted.'


# ################################################################
# A C T I O N S
# ################################################################

if (len(sys.argv) > 1):
	if (sys.argv[1] == "fit"): fit()
	elif (sys.argv[1] == "fitnplot"): fitnplot()
	elif (sys.argv[1] == "plot"): plot()
	elif (sys.argv[1] == "gen"): gen(str(sys.argv[2]))
	elif (sys.argv[1] == "mcsjob"): MCSJob(sys.argv[2],int(sys.argv[3]),int(sys.argv[4]),sys.argv[5],int(sys.argv[6]))
	elif (sys.argv[1] == "mcs"): MCSManyExp()
	elif (sys.argv[1] == "profiles"): profiles()