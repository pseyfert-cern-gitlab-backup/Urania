import sys
import os
import Ganga.GPI
Job = Ganga.GPI.Job
Dirac = Ganga.GPI.Dirac
Local = Ganga.GPI.Local
Executable = Ganga.GPI.Executable
GaudiPython = Ganga.GPI.GaudiPython
LHCbDataset = Ganga.GPI.LHCbDataset

sys.path += ['/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent','/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent']

Jobname  = 'FitnGenwidefast.py'
Script = [ 'FitnGenwidefast.py' ]
Args  = ["fitnplot"]
User_release_area = '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent'
Project = 'Erasmus'
Platform = 'x86_64-slc6-gcc48-opt'
Version = 'v10r2'

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
#Application.platform = Platform
Application.version = Version

# I/O
# ---
Inputsandbox  =[]
Outputsandbox =[]

Inputsandbox += [
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent/FitnGenwidefast.py',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent/FitnGenInterface.py',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent/parameters.py',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/KpiKpiSpectrumNW.cxx',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/KpiKpiSpectrumNW.h',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/KpiKpiSpectrumNW_cxx.so',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/ComputeIntegrals.cxx',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/ComputeIntegrals.h',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/ComputeIntegrals_cxx.so',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/NWclass.h',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/TAccclass.h',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/accparclass.h',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/TResclass.h',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/TReseffclass.h',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/src/TimeDependent/lhcbStyle.C',
    '/afs/cern.ch/user/j/jugarcia/cmtuser/Phys/BsKstKst/python/TimeDependent/InvariantMassFitOut.dat'
    ]

Inputdata = []#[DiracFile('LFN:/lhcb/user/j/jugarcia/NTuples/InvariantMassFitOut.root')]

Outputsandbox = ["plot61D.root","plot61D.pdf","FitParams.tex","FitResult.root"]

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

fit_job.backend.settings['CPUTime'] = 8*24*60*60

print '\nSubmitting the job ...\n'
fit_job.submit()
print '\nJob submitted.\n'
