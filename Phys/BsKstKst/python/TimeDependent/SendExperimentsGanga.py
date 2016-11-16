import sys
import os
import Ganga.GPI
Job = Ganga.GPI.Job
Dirac = Ganga.GPI.Dirac
Local = Ganga.GPI.Local
Executable = Ganga.GPI.Executable
GaudiPython = Ganga.GPI.GaudiPython
LHCbDataset = Ganga.GPI.LHCbDataset

currentpath = os.getcwd()
if currentpath == '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent':
    pythonpath = '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent'
    srcpath = '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent'
elif currentpath == '/home/galaceos/Escritorio/DATA_Analysis/Software/Bs2KpiKpi/lxplus/python/TimeDependent':
    pythonpath = '/home/galaceos/Escritorio/DATA_Analysis/Software/Bs2KpiKpi/lxplus/python/TimeDependent'
    srcpath = '/home/galaceos/Escritorio/DATA_Analysis/Software/Bs2KpiKpi/lxplus/src/TimeDependent'

sys.path += [pythonpath,srcpath]

nev = int(sys.argv[1])
nexp = int(sys.argv[2])
njob = int(sys.argv[3])
output_tag = str(sys.argv[4])
USE_GRID = int(sys.argv[5])

nexpi = int(nexp/njob)
if nexp%njob == 0:
   nexpf = nexpi
else:
   nexpf = nexp-nexpi*(njob-1)
nexpjob = []
for i in range(njob-1): nexpjob.append(nexpi)
nexpjob.append(nexpf)

print '\n####################################\n'
print 'Preparing the following jobs to be submitted:'
for ijob in range(njob): print 'Job' + str(ijob+1) + ': ' + str(nexpjob[ijob]) + ' experiments with ' + str(nev) + ' events each.'

listofjobs = []

for ijob in range(njob):

    ScriptName  = 'FitnGen.py'
    Script = [ 'FitnGen.py' ]
    for script in Script:
        if not os.path.exists(script):
            raise Exception("Script : %s does'nt exist, abort"%(script))
    Args = ["mcsjob",str(ijob+1),str(nev),str(nexpjob[ijob]),output_tag,str(USE_GRID)]
    User_release_area = pythonpath
    Project = 'Erasmus'
    Platform = 'x86_64-slc6-gcc48-opt'
    Version = 'v10r3'

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
    Application.version = Version

    # I/O
    # ---
    Inputsandbox = [
        pythonpath + '/FitnGen.py',
        pythonpath + '/FitnGenInterface.py',
        pythonpath + '/parameters.py',
        srcpath + '/KpiKpiSpectrumNW.cxx',
        srcpath + '/KpiKpiSpectrumNW.h',
        srcpath + '/KpiKpiSpectrumNW_cxx.so',
        srcpath + '/ComputeIntegrals.cxx',
        srcpath + '/ComputeIntegrals.h',
        srcpath + '/ComputeIntegrals_cxx.so',
        srcpath + '/NWclass.h',
        srcpath + '/TAccclass.h',
        srcpath + '/accparclass.h',
        srcpath + '/genaccparclass.h',
        srcpath + '/Splineclass.h',
        srcpath + '/TResclass.h',
        srcpath + '/TReseffclass.h',
        srcpath + '/lhcbStyle.C',
        pythonpath + '/InvariantMassFitOut.dat'
        ]

    Inputdata = []

    Outputsandbox = ["MCS_" + output_tag + "_Job" + str(ijob) + "_" + str(nexpjob[ijob]) + "exp_" + str(nev) +"ev.root"]

    # Backend
    # -------
    if USE_GRID:
        Backend = Dirac()
    else:
        Backend = Local()

    # =============================================================================================================
    # Prepare and submit job
    # =============================================================================================================
    
    # Instanciate
    listofjobs.append(Job(name         = ScriptName,\
          application  = Application,\
          inputdata    = Inputdata,\
          inputfiles   = Inputsandbox,\
          outputfiles  = Outputsandbox,\
          backend      = Backend,\
          ))


print '\nSubmitting the jobs ...\n'
for j in listofjobs:
        j.submit()
print '\nJobs submitted.\n'
print '####################################\n'

print jobs
