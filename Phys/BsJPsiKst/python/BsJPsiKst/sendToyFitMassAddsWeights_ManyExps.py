_USE_GRID_ =  True #False#
_DRY_RUN_ = False

import os
import sys
Kpibins = [826, 861, 896, 931, 966]

NTUPLE_PATH = "/zfs_lhcb/Bs2JpsiKst/Toys/Tuples/"

print sys.argv

iExpMin      = int(sys.argv[1]) # int to tag the pesudoExp ID min
iExpMax      = int(sys.argv[2]) # int to tag the pesudoExp ID max
iExpStep     = int(sys.argv[3]) # int to tag the number of pseudoExp per job
InPutTag     = str(sys.argv[4]) # string to tag the name of the OutPutFile
OutPutTag    = str(sys.argv[5]) # string to tag the name of the OutPutFile
include_Lb   = str(sys.argv[6]) # str to tag Lb bkg is included: 'Lb' or 'noLb'
tupleSource  = str(sys.argv[7]) # string to tag the source of ntuples: 'Toys' or 'Data' 
largeFiles   = int(sys.argv[8]) # int to tag the source of input files (GRID loc or local copy): 1 or 0
simultaneous = int(sys.argv[9]) # int to enable simultaneous parameters in fit
fractions    = int(sys.argv[10]) # int to enable fraction yields parameters in fit

nJobs  = ((iExpMax-iExpMin)/float(iExpStep))
nJobsR = int(round((iExpMax-iExpMin)/iExpStep))
if nJobsR < nJobs: nJobsR += 1

nameID = 'akar'

for iJob in range(0,int(nJobsR)):

    # PseudoExp ids in this job
    iexpMin = iJob*iExpStep + iExpMin
    iexpMax = (iJob+1)*iExpStep + iExpMin
    if iexpMax > iExpMax: iexpMax = iExpMax

    # Script
    # ------
    ScriptName  = 'sendFits_MassAddsWeights.py' # Name of GaudiPython application
    Script = [ 'sendFits_MassAddsWeights.py' ]  # Full script name
    for script in Script:
        if not os.path.exists(script):
            raise Exception("Script : %s does'nt exist, abort"%(script))
    Args  = []
    Args += [tupleSource]
    Args += [str(int(_USE_GRID_))]
    Args += [include_Lb]
    Args += [InPutTag]
    Args += [OutPutTag]
    Args += [str(iexpMin)]
    Args += [str(iexpMax)]
    Args += [str(simultaneous)]
    Args += [str(fractions)]

    # Gaudi
    # -----
    if 'User_release_area' in os.environ.keys():
        User_release_area = os.environ['User_release_area']
    else:
        User_release_area = '/lhcb/users/%s/cmtuser/'%(nameID)
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
    Application.masterpackage = "Phys/BsJPsiKst"
    Application.package = "Phys/BsJPsiKst"
    Application.args += Args
    Application.user_release_area = User_release_area
    Application.project = Project
    Application.platform = Platform
    Application.version = Version
    Application.setupProjectOptions = '--use Phys/BsJPsiKst'

    # I/O
    # ---
    Inputsandbox  =[]
    Inputdata     =[]
    Outputsandbox =[]
    Outputdata    =[]
    
    # - put python modules in input sandbox (addPythonModule is defined in ~/.ganga.py)
    if not largeFiles:
        Inputsandbox += [ '%s/genData_%s_Exp%s.root'%(NTUPLE_PATH,InPutTag,iexp)]

    codeAddOn = ""
    if simultaneous:
        codeAddOn = "Simultaneous"
    if fractions:
        codeAddOn = "Fractions"
    Inputsandbox += [ 
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/fitMassAddsWeights_OneExp%s.py'%(nameID,Project,Version,codeAddOn),
        
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/lhcbStyle.C'%(nameID,Project,Version),

        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/PDF_2013_Asym_toys.py'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/mass_params.py'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/angular_params.py'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/parameters_toys.py'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/Lb_yields.py'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/parameters.py'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/weights_dms.py'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/Cuts2013.py'%(nameID,Project,Version),
        
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/AccAngJpsiKpi_J1.cxx'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/AccAngJpsiKpi_J1.h'%(nameID,Project,Version),

        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/TristanJpsiKpi_J1.cxx'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/TristanJpsiKpi_J1.h'%(nameID,Project,Version),

        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/RooPhiBkg.cxx'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/RooPhiBkg.h'%(nameID,Project,Version),

        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/RooIpatia2.cxx'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/RooIpatia2.h'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/RooIpatia2_cxx.so'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/RooIpatia2_cxx.d'%(nameID,Project,Version),

        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/RooAmorosoPdf.cxx'%(nameID,Project,Version),
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/RooAmorosoPdf.h'%(nameID,Project,Version)
        ]

    codeAddOnOutFiles = ""
    if simultaneous:
        codeAddOnOutFiles = "_Simultaneous"
    if fractions:
        codeAddOnOutFiles = "_Fractions"

    # - put output ntuple in output sandbox
    l_ntupleName = []
    l_plotName = []
    l_fitResName = []
    for iexp in range(iexpMin,iexpMax):
        if simultaneous:
            l_fitResName.append("massFitResults_Toys_%s_%s_Exp%s%s.root"%(InPutTag,OutPutTag,iexp,codeAddOnOutFiles))
        for ibin in range(len(Kpibins)-1):
            l_ntupleName.append("genData_%s_%s_Exp%s_AllYearsSigns_%s_%s_AddedsWeights%s.root"%(InPutTag,OutPutTag,iexp,Kpibins[ibin],Kpibins[ibin+1],codeAddOnOutFiles))
            l_plotName.append("massPlot_Toys_%s_%s_Exp%s_AllYearsSigns_%s_%s%s.root"%(InPutTag,OutPutTag,iexp,Kpibins[ibin],Kpibins[ibin+1],codeAddOnOutFiles))
            if not simultaneous:
                l_fitResName.append("massFitResults_Toys_%s_%s_Exp%s_AllYearsSigns_%s_%s%s.root"%(InPutTag,OutPutTag,iexp,Kpibins[ibin],Kpibins[ibin+1],codeAddOnOutFiles))

    Outputsandbox = l_ntupleName + l_plotName + l_fitResName
    
    # Backend
    # -------
    if _USE_GRID_:
        Backend = Dirac()
    else:
        Backend = Local()

    # =============================================================================================================
    # Prepare and submit job
    # =============================================================================================================
    
    # Instanciate
    j=Job(name         = ScriptName,\
          application  = Application,\
          splitter     = None,\
          merger       = None,\
          inputdata    = None,\
          inputsandbox = Inputsandbox,\
          outputdata   = None,\
          outputfiles  = Outputsandbox,\
          backend      = Backend,\
          )

    # --- To get access to large files which cannot go to the inputsandbox (limited to 10 MO)
    if largeFiles and _USE_GRID_:
        l_inputFiles = []
        for iexp in range(iexpMin,iexpMax):
            lf = LogicalFile('LFN:/lhcb/user/s/sakar/MC/JpsiKst/Bd2JpsiKst/genData_%s_Exp%s.root'%(InPutTag,iexp))
            l_inputFiles.append(lf)
        j.backend.inputSandboxLFNs = l_inputFiles
    else:
        print "ERROR: trying to run on files located on the GRID, whith Local() backend..."
        exit(1)

    # Submit
    if _DRY_RUN_:
        print j
    else:
        j.submit()

