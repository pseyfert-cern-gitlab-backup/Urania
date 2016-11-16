#********************************************************************
#
# DESCRIPTION: script used to fit or generate events corresponding
# to the Bs->(K+pi-)(K-pi+) decay.
# AUTHOR: Julian Garcia Pardinhas, julian.garcia.pardinas@rai.usc.es
# UNIVERSITY: Universidade de Santiago de Compostela
# DATE: 11/2014
#
#********************************************************************

from ROOT import *
from math import *
from FitnGenInterface import *
import time
import sys


# ################################################################
# G L O B A L   O P T I O N S
# ################################################################

# Wide Window.
wide_window = 0

# Acceptance description.
flat_acc = 0
nw_acc = 1 # 0 for parametric factorized acceptance / 1 for normalization weights.

# Time resolution model.
inf_t_res = 0 # 1 for ideal model / 0 for gaussian like resolution

# CP violation in the model.
Blinding = 1
No_CP_Switch = 0
No_dirCP_Switch = 0
Same_CP_Switch = 1

# Fixed parameters.
fix_wave_fractions = 0
fix_dirCP_asyms = 0
fix_strong_phases = 0
fix_weak_phases = 0
fix_mixing_params = 1
fix_calib_params = 1

# Systematic studies.
pw_alternative_model = 0
f_Kst1410_rel2_Kst892 = 0.2
delta_Kst1410_rel2_Kst892 = 0.
f_Kst1680_rel2_Kst892 = 0.2
delta_Kst1680_rel2_Kst892 = 0.

# Data used in the fit.
data_file = 'InvariantMassFitOut.root'
data_tree = 'trees/Data_wsweights'
MC_file = 'NarrowWindow_200000ev.root'
data_type = "real" # "real" for real data from 2011 and 2012 / "MC" for Monte Carlo simulation.
sweighted = 1
evnum_limit = 0

# Fit options.
num_CPU = 8
activ_minos = 0
fit_strategy = 0

# Plotting options.
m_binning = 40
cos_binning = 20
phi_binning = 20
t_binning = 40

# Generation options.
nexperiments = 2
nevents = 2
njobs = 2
use_GRID = 1
exp_output_tag = "NarrowWindow"
fit_CondVarDistr = 0
recompute_maxima = 0


# ################################################################
# F I T   F U N C T I O N S
# ################################################################

def fit():

	# Compile and load the C++ libraries.
	if use_GRID: CompileLibsGRID()
	else: ForceCompileLibs()

	# Summary of the fit options.
	information(data_type,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,flat_acc,nw_acc,\
inf_t_res,wide_window,fix_wave_fractions,fix_dirCP_asyms,fix_strong_phases,fix_weak_phases,fix_mixing_params,fix_calib_params,pw_alternative_model)

	# Data importation.
	if use_GRID: data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData('',data_type,data_file,data_tree,MC_file,sweighted,flat_acc,wide_window,evnum_limit)
	else: data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,sweighted,flat_acc,wide_window,evnum_limit)

	# Construction of the model.
	model, parameters = createSimPDF(Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,flat_acc,\
nw_acc,inf_t_res,wide_window,data_file,fix_wave_fractions,fix_dirCP_asyms,fix_strong_phases,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

	# Performance of the fit.
	result = DoFit(model[0],data[0],num_CPU,activ_minos,fit_strategy,fix_mixing_params,fix_calib_params)

	# Print out of the measured parameters.
	fitprint2LaTeX('FitParams',parameters,wide_window,No_CP_Switch,Blinding,fix_mixing_params,fix_calib_params)

	# Save fit result in a root file.
	fres = TFile("FitResult.root","recreate")
	result.Write("FitResult")
	fres.Close()

def fitnplot():

	# Compile and load the C++ libraries.
	if use_GRID: CompileLibsGRID()
	else: ForceCompileLibs()

	# Summary of the fit options.
	information(data_type,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,flat_acc,nw_acc,\
inf_t_res,wide_window,fix_wave_fractions,fix_dirCP_asyms,fix_strong_phases,fix_weak_phases,fix_mixing_params,fix_calib_params)

	# Data importation.
	if use_GRID: data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData('',data_type,data_file,data_tree,MC_file,sweighted,flat_acc,wide_window,evnum_limit)
	else: data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,sweighted,flat_acc,wide_window,evnum_limit)

	# Construction of the model.
	model, parameters = createSimPDF(Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,flat_acc,\
nw_acc,inf_t_res,wide_window,data_file,fix_wave_fractions,fix_dirCP_asyms,fix_strong_phases,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

	# Performance of the fit.
	result = DoFit(model[0],data[0],num_CPU,activ_minos,fit_strategy,fix_mixing_params,fix_calib_params)

	# Print out of the measured parameters.
	fitprint2LaTeX('FitParams',parameters,wide_window,No_CP_Switch,Blinding,fix_mixing_params,fix_calib_params)

	# Plot of the the 6 1D proyections corresponding to the 2 masses, 3 angles and decay time.
	map(lambda x:x.setDenPlotVarVal(),model[1:5])
	plot61Ddata(data[0], wide_window, m_binning, cos_binning, phi_binning, t_binning) # Plotting the dataset.
	plot61Dmodel(model[0], data[0], wide_window) # Plotting the full model.
	plot61Dcomponent(model[0], data[0], wide_window) # Plotting the KstKst component.
	c1 = create61Dcanvas(wide_window) # Drawing the plots in a canvas.
	c1.Print("plot61D.root") # Printing the canvas in a root file.
	c1.Print("plot61D.pdf") # Printing the canvas in a pdf file.

	# Save fit result in a root file.
	fres = TFile("FitResult.root","recreate")
	result.Write("FitResult")
	fres.Close()

def plot():

	# Compile and load the C++ libraries.
	if use_GRID: CompileLibsGRID()
	else: ForceCompileLibs()

	# Data importation.
	if use_GRID: data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData('',data_type,data_file,data_tree,MC_file,sweighted,flat_acc,wide_window,evnum_limit)
	else: data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,sweighted,flat_acc,wide_window,evnum_limit)

	# Construction of the model.
	model, parameters = createSimPDF(Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,flat_acc,\
nw_acc,inf_t_res,wide_window,data_file,fix_wave_fractions,fix_dirCP_asyms,fix_strong_phases,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

	# Plot of the the 6 1D proyections corresponding to the 2 masses, 3 angles and decay time.
	map(lambda x:x.setDenPlotVarVal(),model[1:5])
	plot61Ddata(data[0], wide_window, m_binning, cos_binning, phi_binning, t_binning) # Plotting the dataset.
	plot61Dmodel(model[0], data[0], wide_window) # Plotting the full model.
	plot61Dcomponent(model[0], data[0], wide_window) # Plotting the KstKst component.
	c1 = create61Dcanvas(wide_window) # Drawing the plots in a canvas.
	c1.Print("plot61D.root") # Printing the canvas in a root file.
	c1.Print("plot61D.pdf") # Printing the canvas in a pdf file.


# ################################################################
# M O N T E   C A R L O   G E N E R A T I O N   F U N C T I O N
# ################################################################

def gen(exp_name):

	# Compile and load the C++ libraries.
	ForceCompileLibs()

	# Data importation.
	data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,sweighted,flat_acc,wide_window,evnum_limit)

	# Construction of the model.
	model, parameters = createPDF(Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,flat_acc,\
nw_acc,inf_t_res,wide_window,data_file,fix_wave_fractions,fix_dirCP_asyms,fix_strong_phases,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

	# Fit of the conditional variable profiles.
	CondVarStudy(fit_CondVarDistr,model,parameters,data,hist_mistag_SSK,hist_mistag_OS,hist_deltat)

	# Configuration of the generator.
	model.SetGenerator(wide_window,recompute_maxima)

	# Event generation.
	genTree(nevents,model,exp_output_tag+'_exp'+exp_name)

def MCSJob(job_ID,nevs,nexps,outtag,GRID):

	# Compile and load the C++ libraries.
	if GRID: CompileLibsGRID()
	else: CompileLibs()

	# Data importation.
	if GRID: data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData('',data_type,data_file,data_tree,MC_file,sweighted,flat_acc,wide_window,evnum_limit)
	else: data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,sweighted,flat_acc,wide_window,evnum_limit)

	# Construction of the model.
	model, parameters = createPDF(Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,flat_acc,\
nw_acc,inf_t_res,wide_window,data_file,fix_wave_fractions,fix_dirCP_asyms,fix_strong_phases,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

	# Fit of the conditional variable profiles.
	CondVarStudy(fit_CondVarDistr,model,parameters,data,hist_mistag_SSK,hist_mistag_OS,hist_deltat)

	# Configuration of the generator.
	model.SetGenerator(wide_window,recompute_maxima)

	# Event generation and fitting.
	doToyMCStudy(nexps,nevs,model,outtag,job_ID,GRID,num_CPU,activ_minos,fit_strategy)

def MCSManyExp():

	# Configure and submit the jobs to Ganga.
	MCSGrid(nexperiments,nevents,njobs,exp_output_tag,use_GRID)


# ################################################################
# L O G   L I K E L I H O O D   S C A N
# ################################################################

def profile(parameter):

	# Compile and load the C++ libraries.
	ForceCompileLibs()

	# Data importation.
	data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,sweighted,flat_acc,wide_window,evnum_limit)

	# Construction of the model.
	model, parameters = createPDF(Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,flat_acc,\
nw_acc,inf_t_res,wide_window,data_file,fix_wave_fractions,fix_dirCP_asyms,fix_strong_phases,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)
	
	# Plot of the likelihood profile.
	c_ll = llprofile(parameter,model,data,num_CPU)
	c_ll.Print("plotllprofile_" + parameter.GetName() + ".pdf")


# ################################################################
# A C T I O N S
# ################################################################

if (len(sys.argv) > 1):
	if (sys.argv[1] == "fit"): fit()
	elif (sys.argv[1] == "fitnplot"): fitnplot()
	elif (sys.argv[1] == "plot"): plot()
	elif (sys.argv[1] == "gen"): gen(str(sys.argv[2]))
	elif (sys.argv[1] == "mcsjob"): MCSJob(sys.argv[2],int(sys.argv[3]),int(sys.argv[4]),sys.argv[5],int(sys.argv[6]))
	elif (sys.argv[1] == "mcsmany"): MCSManyExp()
	elif (sys.argv[1] == "profile"): profile(eval(sys.argv[2]))
