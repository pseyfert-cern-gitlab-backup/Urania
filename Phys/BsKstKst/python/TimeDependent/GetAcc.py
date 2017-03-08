#********************************************************************
#
# DESCRIPTION: script used to compute the 5-D normalization weights,
# the time integrals and the parametric 6-D acceptance used for
# visualization, corresponding to the Bs->(K+pi-)(K-pi+) decay.
# AUTHOR: Julian Garcia Pardinhas, julian.garcia.pardinas@rai.usc.es
# UNIVERSITY: Universidade de Santiago de Compostela
# DATE: 11/2014
#
#********************************************************************

from GetAccInterface import *


# ################################################################
# G L O B A L   O P T I O N S
# ################################################################

# Data used to obtain the acceptance.
data_file = 'AnalysisOutWSWeightsSelectedAllBranchesNew.root'#'AnalysisOutWithCuts_AllBranches_PHIstudy.root'
data_tree = 'AnalysisTree'
MC_datatype = 2 # 0 for PhSp only, 1 for VV only, 2 for both
evnum_limit = 0

# NW computation options.
compute_cov_matrix = 0

# Time acceptance histograms.
tacc_nbins = 20
tacc_plot_outtag = 'TAcc_histos'


# ################################################################
# N O R M A L I Z A T I O N   W E I G H T S
# ################################################################

def GetNW():

	# Data importation.
	datalist = LoadDataNW(data_file,data_tree,MC_datatype,evnum_limit)

	# Construction of the physical PDF.
	pdflist = CreatePhysPDF()

	# Computation of the normalization weights.
	ComputeNW(compute_cov_matrix,*(pdflist+datalist))

	# Print of the normalization weights.
	PrintNW()


# ################################################################
# T I M E   A C C E P T A N C E   S P L I N E S
# ################################################################

def GetSplines():

	# Data importation.
	datalist = LoadDataTime(data_file,data_tree,MC_datatype,evnum_limit)

	# Obtaintion of the knots.
	knots = getKnots(6,*datalist)

	# Computation of the spline coefficients.
	getSplineCoeffs(knots,*datalist)


# ################################################################
# T I M E   A C C E P T A N C E   H I S T O G R A M S
# ################################################################

def GetTimeAccHistos():

	# Data importation.
	datalist = LoadDataTime(data_file,data_tree,MC_datatype,evnum_limit)

	# Obtaintion of the binning scheme (from 2012 L0TIS wide window data).
	bounds = adaptiveBinning(t_MC,tacc_nbins,1,datalist[1])

	# Creation of the histograms.
	tacchistosclass, tacchistosplot = createTimeAccHistos(bounds,*datalist)

	# Print out of the C++ class containing the histograms.
	printTimeAccHistos(bounds,tacchistosclass)

	# Plot of the histograms.
	plotTimeAccHistos(bounds,tacchistosplot,tacc_plot_outtag)


# ################################################################
# T I M E   I N T E G R A L S
# ################################################################

def GetTimeInts():

	# Data importation.
	datalist = LoadDataTime(data_file,data_tree,MC_datatype,evnum_limit)

	# Construction of the physical PDF.
	pdflist = CreatePhysPDF()

	# Computation of the time integrals.
	ComputeTimeIntegrals(*(pdflist+datalist))

	# Print of the time integrals.
	PrintTimeInts()


# ################################################################
# V I S U A L I Z A T I O N   A C C E P T A N C E
# ################################################################

def GetVisAcc():

	# Data importation.
	datalist = LoadDataVis(data_file,data_tree,MC_datatype,evnum_limit)

	# Construction of the acceptance model.
	auxlist,pdflist = CreateAccPDF()

	# Fit and plot of the 6-D acceptance.
	c_vis_2011_L0TIS_wide,c_vis_2012_L0TIS_wide,c_vis_2011_L0TIS_narrow,c_vis_2012_L0TIS_narrow,\
c_vis_2011_L0noTIS_wide,c_vis_2012_L0noTIS_wide,c_vis_2011_L0noTIS_narrow,c_vis_2012_L0noTIS_narrow = FitnPlotVisAcc(*(pdflist+datalist))
	c_vis_2011_L0TIS_wide.Print("Vis_Acc_2011_L0TIS_wide.pdf")
	c_vis_2012_L0TIS_wide.Print("Vis_Acc_2012_L0TIS_wide.pdf")
	c_vis_2011_L0TIS_narrow.Print("Vis_Acc_2011_L0TIS_narrow.pdf")
	c_vis_2012_L0TIS_narrow.Print("Vis_Acc_2012_L0TIS_narrow.pdf")
	c_vis_2011_L0noTIS_wide.Print("Vis_Acc_2011_L0noTIS_wide.pdf")
	c_vis_2012_L0noTIS_wide.Print("Vis_Acc_2012_L0noTIS_wide.pdf")
	c_vis_2011_L0noTIS_narrow.Print("Vis_Acc_2011_L0noTIS_narrow.pdf")
	c_vis_2012_L0noTIS_narrow.Print("Vis_Acc_2012_L0noTIS_narrow.pdf")

	# Print of the resulting parameters.
	PrintVisAccPars()


# ################################################################
# T O Y   M C   G E N E R A T I O N   A C C E P T A N C E
# ################################################################

def GetGenAcc():

	# Data importation.
	datalist = LoadDataGen2012(data_file,data_tree,MC_datatype,evnum_limit)

	# Construction of the acceptance model.
	auxlist,pdflist = CreateAccPDFGen()

	# Fit and plot of the 5-D acceptance.
	FitnPlotGenAcc(*(pdflist+datalist))

	# Print of the resulting parameters.
	PrintGenAccPars(*pdflist)


# ################################################################
# A C T I O N S
# ################################################################

if (len(sys.argv) > 1):
	if (sys.argv[1] == "nw"): GetNW()
	elif (sys.argv[1] == "splines"): GetSplines()
	elif (sys.argv[1] == "timehistos"): GetTimeAccHistos()
	elif (sys.argv[1] == "timeints"): GetTimeInts()
	elif (sys.argv[1] == "visacc"): GetVisAcc()
	elif (sys.argv[1] == "genacc"): GetGenAcc()
