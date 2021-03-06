#********************************************************************
#
# DESCRIPTION: script used to setup real and MC data ntuples for a
# background subtracted tagged time-dependent analysis of the decay
# Bs->(K+pi-)(K-pi+).
# AUTHOR: Julian Garcia Pardinhas, julian.garcia.pardinas@rai.usc.es
# UNIVERSITY: Universidade de Santiago de Compostela
# DATE: 11/2014
#
#********************************************************************

from ROOT import *
from math import *
import sys
from SetupDataInterface import *


# ################################################################
# G L O B A L   O P T I O N S
# ################################################################

# Options for the addition of new branches to the ntuple.
cos_input_file_name = 'AnalysisOutWSWeights'
cos_input_file_extradir = 0 # 1 if an extra directory exists in the file containing the 'DecayTree', 0 if not.
cos_input_file_extradir_name = 'MCDecayTreeTuple'
cos_output_file_name = 'AnalysisOutWSWeights_AllBranches'
tps_input_file_name = 'Bs2Kst0Kst0_wide_MC2012_magnetUp_Job1528_WithCosines'
tps_output_file_name = 'Bs2Kst0Kst0_wide_MC2012_magnetUp_Job1528_WithCosines_TAU'

# Options for the candidate selection.
Selection_input_file_name = 'Bs2KpiKpi_PhaseSpace_MC2012_WithCosines_TAUinps'
Selection_output_file_name = 'Bs2KpiKpi_PhaseSpace_MC2012_WithCosines_TAUinps_WithCuts'


# ################################################################
# A D D I T I O N   O F   N E W   B R A N C H E S
# ################################################################

def AddBranches():	

	# Add cos(theta_1), cos(theta_2) and phi.
	AddAngles(cos_input_file_name,cos_input_file_extradir,\
cos_input_file_extradir_name,cos_output_file_name)

	# Add t and t_error.
	#ns2ps(tps_input_file_name,tps_output_file_name)
	

# ################################################################
# M O N T E C A R L O   R E W E I G H T
# ################################################################

def MCReweight():
	return


# ################################################################
# S E L E C T I O N
# ################################################################

def Selection():
	ApplyCuts(Selection_input_file_name,Selection_output_file_name)


# ################################################################
# S W E I G H T   C A L C U L A T I O N
# ################################################################

def ComputeSWeights():
	return


# ################################################################
# A C T I O N S
# ################################################################

if (len(sys.argv) > 1):
	if (sys.argv[1] == "AddBranches"): AddBranches()
	elif (sys.argv[1] == "MCReweight"): MCReweight()
	elif (sys.argv[1] == "Selection"): Selection()
	elif (sys.argv[1] == "ComputeSWeights"): ComputeSWeights()
