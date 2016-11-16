import sys
import os
import Ganga.GPI
Job = Ganga.GPI.Job
Dirac = Ganga.GPI.Dirac
Local = Ganga.GPI.Local
Executable = Ganga.GPI.Executable
GaudiPython = Ganga.GPI.GaudiPython
LHCbDataset = Ganga.GPI.LHCbDataset

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
	PYTHON_PATH = '/home3/julian.garcia/cmtuser/Bs2KpiKpi/python/TimeDependent/'
	SOURCE_PATH = '/home3/julian.garcia/cmtuser/Bs2KpiKpi/src/TimeDependent/'
	print "\nINFO: USC node environment loaded."

sys.path += [PYTHON_PATH,SOURCE_PATH]

Jobname  = 'TDFit'
Script = [ 'FitnGen.py' ]
Args  = ["fitnplot"]
User_release_area = PYTHON_PATH
Project = 'DaVinci'
#Version = 'v5r0'

# =============================================================================================================
# Job properties
# =============================================================================================================

# Application
# -----------
Application = GaudiPython()
Application.script = Script
Application.args += Args
Application.user_release_area = User_release_area
Application.project = Project
#Application.version = Version

# I/O
# ---
Inputsandbox  =[]
Outputsandbox =[]

Inputsandbox += [
    PYTHON_PATH + 'FitnGen.py',
    PYTHON_PATH + 'FitnGenInterface.py',
    PYTHON_PATH + 'parameters.py',
    PYTHON_PATH + 'TResCalib.py',
    SOURCE_PATH + 'KpiKpiSpectrumNW.cxx',
    SOURCE_PATH + 'KpiKpiSpectrumNW.h',
    SOURCE_PATH + 'KpiKpiSpectrumNW_cxx.so',
    SOURCE_PATH + 'ComputeIntegrals.cxx',
    SOURCE_PATH + 'ComputeIntegrals.h',
    SOURCE_PATH + 'ComputeIntegrals_cxx.so',
    SOURCE_PATH + 'NWclass.h',
    SOURCE_PATH + 'Splineclass.h',
    SOURCE_PATH + 'TAccclass.h',
    SOURCE_PATH + 'accparclass.h',
    SOURCE_PATH + 'genaccparclass.h',
    SOURCE_PATH + 'TResclass.h',
    SOURCE_PATH + 'TReseffclass.h',
    SOURCE_PATH + 'lhcbStyle.C',
    NTUPLE_PATH + 'AnalysisOutWSWeightsSelectedAllBranchesReduced.root'
    ]

Inputdata = []

Outputsandbox = [
    "integrals_4cats.C",
    "plot61D.root",
    "plot61D.pdf",
    "TDFitPlot_B_s0_DTF_B_s0_CosTheta1.pdf",
    "TDFitPlot_B_s0_DTF_B_s0_CosTheta1.root",
    "TDFitPlot_B_s0_DTF_B_s0_CosTheta2.pdf",
    "TDFitPlot_B_s0_DTF_B_s0_CosTheta2.root",
    "TDFitPlot_B_s0_DTF_B_s0_Phi1.pdf",
    "TDFitPlot_B_s0_DTF_B_s0_Phi1.root",
    "TDFitPlot_B_s0_DTF_KST1_M.pdf",
    "TDFitPlot_B_s0_DTF_KST1_M.root",
    "TDFitPlot_B_s0_DTF_KST2_M.pdf",
    "TDFitPlot_B_s0_DTF_KST2_M.root",
    "TDFitPlot_B_s0_DTF_TAU.pdf",
    "TDFitPlot_B_s0_DTF_TAU.root",
    "FitCorrMatrix.pdf",
    "FitCorrMatrix.root",
    "FitParams_OldStyle.tex",
    "FitParams_Polar.tex",
    "FitParams_ReAImA.tex"
    ]

# Backend
# -------
Backend = Dirac()

# =============================================================================================================
# Prepare and submit job
# =============================================================================================================

# Instanciate
fit_job = Job(name = Jobname,\
      application  = Application,\
      inputdata    = Inputdata,\
      inputfiles   = Inputsandbox,\
      outputfiles  = Outputsandbox,\
      backend      = Backend,\
      )

#fit_job.backend.settings['CPUTime'] = 12*24*60*60

print '\nSubmitting the job ...\n'
fit_job.submit()
print '\nJob submitted.\n'
