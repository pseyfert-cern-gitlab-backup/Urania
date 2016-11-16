#********************************************************************
#
# DESCRIPTION: script used to obtain a parametrization for the decay
# time resolution.
# AUTHOR: Julian Garcia Pardinhas, julian.garcia.pardinas@rai.usc.es
# UNIVERSITY: Universidade de Santiago de Compostela
# DATE: 02/2015
#
#********************************************************************

from ROOT import *
from math import *
import sys
from GetResInterface import *


# ################################################################
# G L O B A L   O P T I O N S
# ################################################################

# MC data used to obtain the decay time error distributions.
data_file = 'AnalysisOutWithCuts_AllBranches.root'
data_tree = 'AnalysisTree'
MC_datatype = 2 # 0 for PhSp only, 1 for VV only, 2 for both
evnum_limit = 0

# Binning of t_err for the parametrization study.
bin_sim = 10

# Parametrization of the time resolution as a function of the decay time error.
pol_order = 1
q0_term = 1
mean_offset = 0

# Plots of the decay time resolution.
nbins_difft = 20
nbins_deltat = 20


# ################################################################
# D E C A Y   T I M E   E R R O R   F I T
# ################################################################

def Fit1DRes():

	# Data importation.
	LoadData_1D(data_file,data_tree,MC_datatype,evnum_limit)

	# Fit of the 1D effective PDF to data.
	fit_list = Fit1DPDF(mean_offset)

	# Plot the 1D model and data distributions.
	Make1DPlot(nbins_difft)

	# Print the resulting sigma_eff.
	printSigmaEff(*fit_list)

	# Print the resulting parameters.
	PrintTReseffPars()

"""def FitSim():

	# Defining different parameters for each bin.
	sim_pars = DefineParams(bin_sim)

	# Created separated datasets per bin.
	#FitMargPDF()
	binning_2011, binning_2012 = GetBinning(bin_sim)
	CreateDatasets(bin_sim)
	LoadData_sim(data_file,data_tree,MC_datatype,evnum_limit,binning_2011,binning_2012)"""

def Fit2DRes():

	# Data importation.
	LoadData_2D(data_file,data_tree,MC_datatype,evnum_limit)
	
	# Creation of a marginal PDF for the decay time error.
	FitMargPDF()

	# Fit of the 2D PDF to data.
	fit_list = Fit2DPDF(pol_order,q0_term,mean_offset)

	# Plot of the 2D model and data distributions.
	Make2DPlot(nbins_difft,nbins_deltat)

	# Print out of the resulting parameters.
	PrintTResPars()


# ################################################################
# A C T I O N S
# ################################################################

if (len(sys.argv) > 1):
	if (sys.argv[1] == "fit1d"): Fit1DRes()
	elif (sys.argv[1] == "fit2d"): Fit2DRes()
