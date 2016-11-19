################################################################################
##                                                                            ##
## Contact: rvazquez@cern.ch                                                  ##
##                                                                            ##
## Simplified tool to produce nTuples                                         ##
##                                                                            ##
## Usage: see the examples below                                              ##
##                                                                            ##
################################################################################

import ntpath
import os.path

class TupleJob:
  def __init__(self
               ,  platform         = "x86_64-slc6-gcc48-opt"
               ,  davinciVersion   = "v38r0"
               ,  year             = "2015"
               ,  stripVersion     = "24"
               ,  suffix           = "" 
               ,  magPol           = "MagUp"
               ,  backend          = Dirac()
               ,  maxFiles         = -1
               ,  filesPerJob      = 8
               ,  autoresubmit     = False
               ,  simulation       = False
               ,  EvtMax           = -1
               ,  InputType        = None
               ,  inputfiles       = None
               ,  bkkQuery         = None
               ,  bkkFlag          = "OK"
               ,  stream           = "AllStreams"
               ,  optsfile         = None
              ):

    ## STORES THE VARIABLES IN AN ACCESSIBLE BUT HIDDEN WAY    
    self._platform       = platform      
    self._davinciVersion = davinciVersion
    self._year           = year          
    self._stripVersion   = stripVersion  
    self._suffix         = suffix        
    self._magPol         = magPol        
    self.backend         = backend
    self.splitter        = SplitByFiles(maxFiles = maxFiles, filesPerJob = filesPerJob, ignoremissing = True)
    self._autoresubmit   = autoresubmit  
    self._gangaJob       = None
    self.simulation      = simulation
    self.luminosity      = not simulation
    self.EvtMax          = EvtMax
    self._outputfilename = "TupleRDS.root"
    self.stream          = stream
    if simulation:
      self.stream        = "AllStreams"

    self._inputType = InputType
    if self._inputType == None:
      if self.stream in ['PID', 'LEPTONIC', 'BHADRON', 'CHARM']:
        self._inputType = 'MDST'
      else:
        self._inputType = 'DST'

    self._inputfiles = inputfiles
    if inputfiles == None: self.inputfiles = []

    self.bkkQuery         = bkkQuery
    self.bkkFlag          = bkkFlag
    self.optsfile         = optsfile 
    if optsfile == None: self.optsfile = []


  def _getDatasetFromBK(self, query = None):
    if query == None:
      if self.bkkQuery == None:
        query=('LHCb/Collision{col}/Beam{energy}-VeloClosed-{pol}/Real '
                           'Data/Reco{rec}/Stripping{strp}/90000000/SEMILEPTONIC.DST'.format(
           col      =   self._collVersion, 
           energy   =   self._beamEnergy, 
           pol      =   self._magPol,
           rec      =   self._recoVersion, 
           strp     =   self._stripVersion
          ))
      else:
        query = self.bkkQuery

    bk = BKQuery(path = query, dqflag = self.bkkFlag)
    print "Getting input data according to BK path {0}".format(bk.path)
    dsAll = bk.getDataset()
    print "Selected " + str(len(dsAll.files) ) + " files."

    return dsAll;
 
  def instanceJob(self, 
                  jobName = None,
                  bkkQuery = None
                 ):

    ## PARSE YEAR OF DATATAKING
    if self._year == "2012":
      self._collVersion = "12"; self._beamEnergy = "4000GeV"   
    elif self._year == "2011":
      self._collVersion = "11"; self._beamEnergy = "3500GeV"   
    elif self._year == "2015":
      self._collVersion = "15"; self._beamEnergy = "6500GeV"   
    elif self._year == "2016":
      self._collVersion = "16"; self._beamEnergy = "6500GeV"

    ## PARSE STRIPPING TO RECONSTRUCTION
    if self._stripVersion in ["20", "20r0p3", "21"]:
      self._recoVersion = "14"
    if self._stripVersion in ["23r1", "24"]:
      self._recoVersion = "15a"
    if self._stripVersion in ["26"]:
      self._recoVersion = "16"
    
    ## ADDS r1 FOR 2011 STRIPPING
    if self._year == "2011":
      self._stripVersion += "r1"
#      self._recoVersion += "a"

    if jobName == None:
      jobName="RDS-Col{coll}-{pol}-S{strp}-{suf}".format(
         coll=self._collVersion, rec=self._recoVersion, 
         strp=self._stripVersion, suf=self._suffix, pol=self._magPol)
      if self.simulation:
         jobName="RDS-MC{coll}-{pol}-S{strp}-{suf}".format(
            coll=self._collVersion, rec=self._recoVersion,
            strp=self._stripVersion, suf=self._suffix, pol=self._magPol)

    self._gangaJob = Job(
      name = jobName
      , application = DaVinci(version = self._davinciVersion)
    )

    j = self._gangaJob
    j.application.optsfile = self.optsfile 
    if self.simulation:
      j.application.optsfile += ["../scripts/DsMuNuTuplerMC.py"]
    else:
      j.application.optsfile += ["../scripts/DsMuNuTuplerData.py"]

    j.inputdata = self._getDatasetFromBK(bkkQuery)
    if self.backend == Local():
      j.outputfiles = [LocalFile(self._outputfilename)]
    else:
      j.outputfiles = [DiracFile(self._outputfilename)]

    j.inputfiles = [LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/utils/TMVA_7Dec.weights.xml"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/utils/HflatBDTS_7Dec.root"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/BDTfiles/600_2500_4_30_0.75_1_1_BDT.weights.xml"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/BDTfiles/600_2500_4_30_0.75_1_8_BDT.weights.xml"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/BDTfiles/600_2500_4_30_0.75_1_9_BDT.weights.xml"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/BDTfiles/600_2500_4_30_0.75_1_4_BDT.weights.xml"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/src/TMVAClassification_Bs2KmuNu.class.C"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r0/Phys/BsDsMuNuForRDS/src/IsoBDT_Bs.C"),
                    ]
 
    j.backend = self.backend
    j.splitter = self.splitter

    self._gangaJob = j
    return j


  def submit   (  self, 
                  jobName  = None,
                  bkkQuery = None
                 ):
    if self._gangaJob == None:
      self._gangaJob = self.instanceJob(jobName = jobName, bkkQuery = bkkQuery)
    
    self._gangaJob . submit()


  def unprepare ( self ):
    self._gangaJob = None


################################################################################
###                                                                          ###
### Pre-defined jobs (also useful as examples)                               ###
###                                                                          ###
################################################################################

class TupleMaker:

  test = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "TestData"
                 ,  maxFiles       = 1
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  EvtMax         = 1000
            )

  down16 = TupleJob(
                    year           = "2016"
                 ,  stripVersion   = "26"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "Data"
                 ,  filesPerJob    = 10
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco16/Stripping26/90000000/SEMILEPTONIC.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "SEMILEPTONIC"
                 ,  backend        = Dirac()
      )

  up16 = TupleJob(
                    year           = "2016"
                 ,  stripVersion   = "26"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "Data"
                 ,  filesPerJob    = 10
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco16/Stripping26/90000000/SEMILEPTONIC.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "SEMILEPTONIC"
                 ,  backend        = Dirac()
      )


  down15 = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "Data"
                 ,  filesPerJob    = 10
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco15a/Stripping24/90000000/SEMILEPTONIC.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "SEMILEPTONIC"
                 ,  backend        = Dirac()
      )

  up15 = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "Data"
                 ,  filesPerJob    = 10
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco15a/Stripping24/90000000/SEMILEPTONIC.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "SEMILEPTONIC"
                 ,  backend        = Dirac()
      )

  testMC = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20r0p3"
                 ,  magPol        = "MagDown"
                 ,  maxFiles      = 1
                 ,  filesPerJob   = 1
                 ,  simulation    = True
                 ,  EvtMax        = 1000
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08h/Digi13/Trig0x409f0045/Reco14c/Stripping20r0p3Filtered/13774002/B2DMUX.TRIGSTRIP.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "Turbo"
                 ,  backend       = Dirac()
      )
       
  MCSigUp09DsMuNu = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "Signal_DsMuNu"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/13774000/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCSigDown09DsMuNu = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "Signal_DsMuNu"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/13774000/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCSigUp09DsTauNu = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "Signal_DsTauNu"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/13774060/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"                 
                 ,  backend       = Dirac()
      )

  MCSigDown09DsTauNu = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "Signal_DsTauNu"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/13774060/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )


  MCSigUp08h = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20r0p3"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "Signal"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08h/Digi13/Trig0x409f0045/Reco14c/Stripping20r0p3Filtered/13774002/B2DMUX.TRIGSTRIP.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )
                  
  MCSigDown08h = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20r0p3"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "Signal"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08h/Digi13/Trig0x409f0045/Reco14c/Stripping20r0p3Filtered/13774002/B2DMUX.TRIGSTRIP.DST' 
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCSigUp08a = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "Signal"
                 ,  filesPerJob   = 10
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08a/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/13774002/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )
                  
  MCSigDown08a = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "Signal"
                 ,  filesPerJob   = 10
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08a/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/13774002/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCInclDsUp = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "InclDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08f/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/23263020/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCInclDsDown = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "InclDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08f/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/23263020/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCInclDsUpP6 = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "InclDsP6"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia6/Sim08f/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/23263020/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCInclDsDownP6 = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "InclDsP6"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia6/Sim08f/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/23263020/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      ) 

  MCInclDsUpFromB = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "InclDsFromB"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia6/Sim08c/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/23103003/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCInclDsDownFromB = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "InclDsFromB"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia6/Sim08c/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/23103003/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCBsDsDsUp = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "BsDsDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08a/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/13873201/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCBsDsDsDown = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "BsDsDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08a/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/13873201/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      ) 

  MCBuD0DsUp = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "BuD0Ds"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08a/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/12875601/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCBuD0DsDown = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "BuD0Ds"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08a/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/12875601/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCBdDstDsUp = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "BdDstDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08a/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/11876001/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCBdDstDsDown = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "BdDstDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08a/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/11876001/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCLbLcDsUp = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "LbLcDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08a/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/15894301/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )

  MCLbLcDsDown = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "LbLcDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08a/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/15894301/ALLSTREAMS.DST'
                 ,  bkkFlag       = "All"
                 ,  stream        = "AllStreams"
                 ,  backend       = Dirac()
      )


print "Preconfigured jobs you can just submit: "
for pidjob in TupleMaker.__dict__:
  if "__" not in pidjob:
    print ". TupleMaker." + pidjob + ".submit()"
print "---------------------"
