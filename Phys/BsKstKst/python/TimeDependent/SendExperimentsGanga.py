import sys
import os
sys.path += ['/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent','/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent']

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
    Args  = ["mcsjob",str(ijob+1),str(nev),str(nexpjob[ijob]),output_tag,str(USE_GRID)]
    User_release_area = '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent'
    Project = 'Urania'
    Platform = 'x86_64-slc6-gcc48-opt'
    Version = 'v2r4'

    # =============================================================================================================
    # Job properties
    # =============================================================================================================

    # Application
    # -----------
    Application = GaudiPython()
    Application.script = Script
    Application.masterpackage = "Phys/BsKstKst"
    Application.package = "Phys/BsKstKst"
    Application.args += Args
    Application.user_release_area = User_release_area
    Application.project = Project
    Application.platform = Platform
    Application.version = Version
    Application.setupProjectOptions = '--use Phys/BsKstKst'

    # I/O
    # ---
    Inputsandbox  =[]
    Outputsandbox =[]

    Inputsandbox += [
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent/FitnGen.py',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent/FitnGenInterface.py',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent/parameters.py',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/KpiKpiSpectrumNW.cxx',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/KpiKpiSpectrumNW.h',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/KpiKpiSpectrumNW_cxx.so',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/ComputeIntegrals.cxx',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/ComputeIntegrals.h',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/ComputeIntegrals_cxx.so',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/integrals.C',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/NWclass.h',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/ITclass.h',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/accparclass.h',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/TResclass.h',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/TReseffclass.h',
        '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/lhcbStyle.C'
        ]

    if USE_GRID: Inputdata = LHCbDataset('LFN:/lhcb/user/j/jugarcia/NTuples/Bs2KpiKpi_Data1112_withCuts_sWeighted.root')
    else: Inputdata = None

    # - put output ntuple in output sandbox
    l_ntupleName = ["/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/ganga/" + output_tag + "/MCS_" + output_tag + "_Job" + str(ijob) + "_" + str(nexpjob[ijob]) + "exp_" + str(nev) +"ev.root"]
    Outputsandbox = l_ntupleName

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


#if USE_GRID:
#    lf = LogicalFile('LFN:/lhcb/user/j/jugarcia/NTuples/Bs2KpiKpi_Data1112_withCuts_sWeighted.root')
#    for j in listofjobs: j.backend.inputSandboxLFNs=[lf]

print '\nSubmitting the jobs ...\n'
for j in listofjobs:
        j.submit()
print '\nJobs submitted.\n'
print '####################################\n'

print jobs
