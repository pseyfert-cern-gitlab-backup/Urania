from ROOT import *
from DoChecksInterface import *


# ################################################################
# G L O B A L   O P T I O N S
# ################################################################

# Wide Window.
wide_window = 1

# Data.
data_file = 'AnalysisOutWithCuts_AllBranches.root'
data_tree = 'AnalysisTree'
MC_datatype = 2 # 0 for PhSp only, 1 for VV only, 2 for both
evnum_limit = 0

# Output.
output_CorrAcc = 'AccCorrTable'
rotated_table = 0
plotbinnum = 12
apply_weights_for_binning = 0
output_TimeAccCorr = 'TimeAccCorrPlot'
cutbinnum = 5
output_YearAcc = 'AccYearPlot'
output_TrigAcc = 'AccTriggerPlot'


# ################################################################
# F U N C T I O N S
# ################################################################

def CorrAcc():

	data = loadDataAccCheck(data_file,data_tree,wide_window,MC_datatype,evnum_limit)
	corr_table_2D(data,[mKp1,mKp2,cos1,cos2,phi,t],1,output_CorrAcc,rotated_table)
	makeTimeAccCorrPlot(data,output_TimeAccCorr,plotbinnum,cutbinnum,apply_weights_for_binning,wide_window)


def YearAcc():

	data = loadDataAccCheck(data_file,data_tree,wide_window,MC_datatype,evnum_limit)
	makeYearAccPlot(data,output_YearAcc,plotbinnum,apply_weights_for_binning,wide_window)


def TrigAcc():

	data = loadDataAccCheck(data_file,data_tree,wide_window,MC_datatype,evnum_limit)
	makeTrigAccPlot(data,output_TrigAcc,plotbinnum,apply_weights_for_binning,wide_window)


# ################################################################
# A C T I O N S
# ################################################################

if (len(sys.argv) > 1):
	if (sys.argv[1] == "corracc"): CorrAcc()
	elif (sys.argv[1] == "yearacc"): YearAcc()
	elif (sys.argv[1] == "trigacc"): TrigAcc()
