_USE_GRID_ =  True #False#
_DRY_RUN_ = False#True #

import os
import sys

print sys.argv

iExpMin       = int(sys.argv[1]) # int to tag the pesudoExp ID min
iExpMax       = int(sys.argv[2]) # int to tag the pesudoExp ID max
iExpStep      = int(sys.argv[3]) # int to tag the number of pseudoExp per job
OutPutTag     = str(sys.argv[4]) # string to tag the name of the OutPutFile
doPeakingBkgs = int(sys.argv[5]) # int to enable peaking bkgs generation
simultaneous  = int(sys.argv[6]) # int to enable simultaneous parameters in generation
nonZeroACPs   = int(sys.argv[7]) # int to flag if we generate the ACPs with non zero values
if nonZeroACPs:
    ACPset    = str(sys.argv[8]) # string to tag the set of ACPs


nJobs  = ((iExpMax-iExpMin)/float(iExpStep))
nJobsR = int(round((iExpMax-iExpMin)/iExpStep))
if nJobsR < nJobs: nJobsR += 1

nameID = 'akar'

OutPutTagAddOn = ""
if doPeakingBkgs:
    OutPutTagAddOn += "_withPeakingBkgs"
if nonZeroACPs:
    OutPutTagAddOn += "_ACPs_%s"%ACPset

for iJob in range(0,int(nJobsR)):

    # PseudoExp ids in this job
    iexpMin = iJob*iExpStep + iExpMin
    iexpMax = (iJob+1)*iExpStep + iExpMin
    if iexpMax > iExpMax: iexpMax = iExpMax
        
    # Script
    # ------
    ScriptName  = 'sendGeneratePseudoExperiments.py'            # Name of GaudiPython application
    # ApplicationGaudiPath = '/lhcb/users/akar/cmtuser/Urania_v2r1/Phys/BsJPsiKst/python'  # Path to the Gaudi application modules
    # ApplicationGaudiMainModule = 'BsJPsiKst'                                                         # Main module name 
    # ApplicationGaudiOtherModules = []                                                        # Other modules list
    Script = [ 'sendGeneratePseudoExperiments.py' ] # Full script name
    for script in Script:
        if not os.path.exists(script):
            raise Exception("Script : %s does'nt exist, abort"%(script))
    Args  = []
    Args += [str(iexpMin)]
    Args += [str(iexpMax)]
    Args += [str(OutPutTag)]
    Args += [str(int(_USE_GRID_))]
    Args += [str(doPeakingBkgs)]
    Args += [str(simultaneous)]
    Args += [str(nonZeroACPs)]
    if nonZeroACPs:
        Args += [str(ACPset)]

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

    codeAddOn = ""
    if simultaneous:
        codeAddOn = "_Simultaneous"
    # - put python modules in input sandbox (addPythonModule is defined in ~/.ganga.py)
    Inputsandbox += [ 
        '/lhcb/users/%s/cmtuser/%s_%s/Phys/BsJPsiKst/python/BsJPsiKst/generatePseudoExperiments%s.py'%(nameID,Project,Version,codeAddOn),

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

    # - put output ntuple in output sandbox
    l_ntupleName = []
    #print "%s %s"%(iexpMin,iexpMax)
    for iexp in range(iexpMin,iexpMax):
        l_ntupleName.append("genData_%s%s_Exp%i.root"%(OutPutTag,OutPutTagAddOn,iexp))
        #print "genData_%s_%s_Exp%i.root"%(OutPutTag,OutPutTagAddOn,iexp)
    Outputsandbox = l_ntupleName


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

    if _USE_GRID_:
        # --- To get access to large files which cannot go to the inputsandbox
        lf = LogicalFile('LFN:/lhcb/user/s/sakar/MC/JpsiKst/Bd2JpsiKst/AllPeakingBkgs_KstRange.root')
        j.backend.inputSandboxLFNs=[lf]

    # Submit
    if _DRY_RUN_:
        print j
    else:
        j.submit()
