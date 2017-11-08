################################################################################
##                                                                            ##
## Contact: rvazquez@cern.ch                                                  ##
##                                                                            ##
## Simplified tool to produce nTuples                                         ##
##                                                                            ##
## Usage: see the examples below                                              ##
##                                                                            ##
################################################################################

import os.path
import os
currentPath = os.getcwd()
PackagePath = '/'.join(s.strip('/') for s in currentPath.split('/')[:-1])
DirPath = '/'.join(s.strip('/') for s in currentPath.split('/')[:-3])
## PackagePath should end in Phys/BsDsMuNuForRDS

class TupleJob:
  def __init__(self
               ,  platform         = "x86_64-slc6-gcc49-opt"
               ,  year             = "2016"
               ,  stripVersion     = "28"
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

    ## ADDS r1 FOR 2011 STRIPPING
    if self._year == "2011":
      self._stripVersion += "r1"

    if jobName == None:
      jobName="RDS-Col{coll}-{pol}-S{strp}-{suf}".format(coll=self._collVersion, strp=self._stripVersion, suf=self._suffix, pol=self._magPol)
      if self.simulation:
         jobName="RDS-MC{coll}-{pol}-S{strp}-{suf}".format(coll=self._collVersion, strp=self._stripVersion, suf=self._suffix, pol=self._magPol)

    self._gangaJob = Job(
      name = jobName
      , application = GaudiExec()
      )

    j = self._gangaJob
    j.application.directory = DirPath
    j.application.options = self.optsfile 
    if self.simulation:
      j.application.options += [PackagePath+"/scripts/DsMuNuTuplerMC.py"]
    else:
      j.application.options += [PackagePath+"/scripts/DsMuNuTuplerData.py"]

    j.inputdata = self._getDatasetFromBK(bkkQuery)
    if self.backend == Local():
      j.outputfiles = [LocalFile(self._outputfilename)]
    else:
      j.outputfiles = [DiracFile(self._outputfilename)]

    #j.inputfiles = [LocalFile(PackagePath+"/utils/TMVA_7Dec.weights.xml"),
    #                LocalFile(PackagePath+"/utils/HflatBDTS_7Dec.root"),
    #                LocalFile(PackagePath+"/BDTfiles/600_2500_4_30_0.75_1_1_BDT.weights.xml"),
    #                LocalFile(PackagePath+"/BDTfiles/600_2500_4_30_0.75_1_8_BDT.weights.xml"),
    #                LocalFile(PackagePath+"/BDTfiles/600_2500_4_30_0.75_1_9_BDT.weights.xml"),
    #                LocalFile(PackagePath+"/BDTfiles/600_2500_4_30_0.75_1_4_BDT.weights.xml"),
    #                LocalFile(PackagePath+"/src/TMVAClassification_Bs2KmuNu.class.C"),
    #                LocalFile(PackagePath+"/src/IsoBDT_Bs.C"),
    #                ]
 
    j.backend = self.backend
    j.splitter = self.splitter

    j.parallel_submit = True

    self._gangaJob = j
    return j

  def submit(self, jobName = None, bkkQuery = None):
    if self._gangaJob == None:
      self._gangaJob = self.instanceJob(jobName = jobName, bkkQuery = bkkQuery)
    
    self._gangaJob.submit()

  def unprepare ( self ):
    self._gangaJob = None

################################################################################
###                                                                          ###
### Pre-defined jobs (also useful as examples)                               ###
###                                                                          ###
################################################################################

class TupleMaker:

#  test = TupleJob(
#                    year           = "2015"
#                 ,  stripVersion   = "24"
#                 ,  magPol         = "MagDown"
#                 ,  suffix         = "TestData"
#                 ,  maxFiles       = 1
#                 ,  filesPerJob    = 20
#                 ,  simulation     = False
#                 ,  EvtMax         = 1000
#            )

  BsDsstKUp = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "20"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "photonControl_BsDsstK"
                 ,  filesPerJob    = 3
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08e/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/13264231/ALLSTREAMS.DST'
                 ,  stream         = "AllStreams"
      )
  BsDsstKDown = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "20"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "photonControl_BsDsstK"
                 ,  filesPerJob    = 3
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08e/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/13264231/ALLSTREAMS.DST'
                 ,  stream         = "AllStreams"
      )

  BsDsstRhoUp = TupleJob(                                                                                                                                                year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "photonControl_BsDsstRho"
                 ,  filesPerJob    = 3
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08g/Digi13/Trig0x409f0045/Reco14c/Stripping21NoPrescalingFlagged/13264631/ALLSTREAMS.DST'
                 ,  stream         = "AllStreams"
      )
  BsDsstRhoDown = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "photonControl_BsDsstRho"
                 ,  filesPerJob    = 3
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08g/Digi13/Trig0x409f0045/Reco14c/Stripping21NoPrescalingFlagged/13264631/ALLSTREAMS.DST'
                 ,  stream         = "AllStreams"
      )

  BsDsKUp = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "photonControl_BsDsK"
                 ,  filesPerJob    = 3
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08g/Digi13/Trig0x409f0045/Reco14c/Stripping21NoPrescalingFlagged/13164012/ALLSTREAMS.DST'
                 ,  stream         = "AllStreams"
      )
  BsDsKDown = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "photonControl_BsDsK"
                 ,  filesPerJob    = 3
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08g/Digi13/Trig0x409f0045/Reco14c/Stripping21NoPrescalingFlagged/13164012/ALLSTREAMS.DST'
                 ,  stream         = "AllStreams"
      ) 

  BsDsRhoUp = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "photonControl_BsDsRho"
                 ,  filesPerJob    = 3
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08g/Digi13/Trig0x409f0045/Reco14c/Stripping21NoPrescalingFlagged/13264421/ALLSTREAMS.DST'
                 ,  stream         = "AllStreams"
      )
  BsDsRhoDown = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "photonControl_BsDsRho"
                 ,  filesPerJob    = 3
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08g/Digi13/Trig0x409f0045/Reco14c/Stripping21NoPrescalingFlagged/13264421/ALLSTREAMS.DST'
                 ,  stream         = "AllStreams"
      )

  BsDsstPiUp = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "photonControl_BsDsstPi"
                 ,  filesPerJob    = 3
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08g/Digi13/Trig0x409f0045/Reco14c/Stripping21NoPrescalingFlagged/13264221/ALLSTREAMS.DST'
                 ,  stream         = "AllStreams"
      ) 
  BsDsstPiDown = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "photonControl_BsDsstPi"
                 ,  filesPerJob    = 3
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08g/Digi13/Trig0x409f0045/Reco14c/Stripping21NoPrescalingFlagged/13264221/ALLSTREAMS.DST'
                 ,  stream         = "AllStreams"
      )

  photonControlDown16 = TupleJob(
                    year           = "2016"
                 ,  stripVersion   = "28"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "photonControl"
                 ,  filesPerJob    = 50
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco16/Stripping28/90000000/BHADRONCOMPLETEEVENT.DST'
                 ,  stream         = "BHADRONCOMPLETEEVENT"
      )

  photonControlUp16 = TupleJob(
                    year           = "2016"
                 ,  stripVersion   = "28"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "photonControl"
                 ,  filesPerJob    = 50
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco16/Stripping28/90000000/BHADRONCOMPLETEEVENT.DST'
                 ,  stream         = "BHADRONCOMPLETEEVENT"
      )

  photonControlDown15 = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "photonControl"
                 ,  filesPerJob    = 50
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco15a/Stripping24/90000000/BHADRONCOMPLETEEVENT.DST'
                 ,  stream         = "BHADRONCOMPLETEEVENT"
      )

  photonControlUp15 = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "photonControl"
                 ,  filesPerJob    = 50
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco15a/Stripping24/90000000/BHADRONCOMPLETEEVENT.DST'
                 ,  stream         = "BHADRONCOMPLETEEVENT"
      ) 

  down16 = TupleJob(
                    year           = "2016"
                 ,  stripVersion   = "28"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "Data"
                 ,  filesPerJob    = 10
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco16/Stripping28/90000000/SEMILEPTONIC.DST'
                 ,  stream         = "SEMILEPTONIC"
      )

  up16 = TupleJob(
                    year           = "2016"
                 ,  stripVersion   = "28"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "Data"
                 ,  filesPerJob    = 10
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco16/Stripping28/90000000/SEMILEPTONIC.DST'
                 ,  stream         = "SEMILEPTONIC"
      )

  photonCalibDown16 = TupleJob(
                    year           = "2016"
                 ,  stripVersion   = "28"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "photonCalib"
                 ,  filesPerJob    = 10
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco16/Stripping28/90000000/CHARMCOMPLETEEVENT.DST'
                 ,  stream         = "CHARMCOMPLETEEVENT"
      )

  photonCalibUp16 = TupleJob(
                    year           = "2016"
                 ,  stripVersion   = "28"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "photonCalib"
                 ,  filesPerJob    = 10
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco16/Stripping28/90000000/CHARMCOMPLETEEVENT.DST'
                 ,  stream         = "CHARMCOMPLETEEVENT"
      ) 

  photonCalibDown15 = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "photonCalib"
                 ,  filesPerJob    = 10
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco15a/Stripping24/90000000/CHARMCOMPLETEEVENT.DST'
                 ,  stream         = "CHARMCOMPLETEEVENT"
      )

  photonCalibUp15 = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "photonCalib"
                 ,  filesPerJob    = 10
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco15a/Stripping24/90000000/CHARMCOMPLETEEVENT.DST'
                 ,  stream         = "CHARMCOMPLETEEVENT"
      )


  down15 = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "Data"
                 ,  filesPerJob    = 10
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco15a/Stripping24/90000000/SEMILEPTONIC.DST'
                 ,  stream         = "SEMILEPTONIC"
      )

  up15 = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "Data"
                 ,  filesPerJob    = 10
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco15a/Stripping24/90000000/SEMILEPTONIC.DST'
                 ,  stream         = "SEMILEPTONIC"
      )

#  testMC = TupleJob(
#                    year          = "2012"
#                 ,  stripVersion  = "20r0p3"
#                 ,  magPol        = "MagDown"
#                 ,  maxFiles      = 1
#                 ,  filesPerJob   = 1
#                 ,  simulation    = True
#                 ,  EvtMax        = 1000
#                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08h/Digi13/Trig0x409f0045/Reco14c/Stripping20r0p3Filtered/13774002/B2DMUX.TRIGSTRIP.DST'
#                 ,  stream        = "Turbo"
#      )

  MC15SigUp09bDsMuNu = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "Signal_DsMuNu_Sim09b"
                 ,  filesPerJob   = 10
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24Filtered/13774000/B2DMUNUXANDTAU.DST'
                 ,  stream        = "B2DMUNUXANDTAU"
      )

  MC15SigDown09bDsMuNu = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "Signal_DsMuNu_Sim09b"
                 ,  filesPerJob   = 10
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24Filtered/13774000/B2DMUNUXANDTAU.DST'
                 ,  stream        = "B2DMUNUXANDTAU"
      )

       
#  MCSigUp09DsMuNu = TupleJob(
#                    year          = "2015"
#                 ,  stripVersion  = "24"
#                 ,  magPol        = "MagUp"
#                 ,  suffix        = "Signal_DsMuNu"
#                 ,  filesPerJob   = 10
#                 ,  simulation    = True
#                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/13774000/ALLSTREAMS.DST'
#                 ,  stream        = "AllStreams"
#      )

#  MCSigDown09DsMuNu = TupleJob(
#                    year          = "2015"
#                 ,  stripVersion  = "24"
#                 ,  magPol        = "MagDown"
#                 ,  suffix        = "Signal_DsMuNu"
#                 ,  filesPerJob   = 10
#                 ,  simulation    = True
#                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/13774000/ALLSTREAMS.DST'
#                 ,  stream        = "AllStreams"
#      )

  MC16SigUp09bDsMuNu = TupleJob(
                     year          = "2016"
                  ,  stripVersion  = "26"
                  ,  magPol        = "MagUp"
                  ,  suffix        = "Signal_DsMuNu_Sim09b"
                  ,  filesPerJob   = 10
                  ,  simulation    = True
                  ,  bkkQuery      = '/MC/2016/Beam6500GeV-2016-MagUp-Nu1.6-25ns-Pythia8/Sim09b/Trig0x6138160F/Reco16/Turbo03/Stripping26NoPrescalingFlagged/13774004/ALLSTREAMS.DST'
                  ,  stream        = "AllStreams"
       )

  MC16SigDown09bDsMuNu = TupleJob(
                     year          = "2016"
                  ,  stripVersion  = "26"
                  ,  magPol        = "MagDown"
                  ,  suffix        = "Signal_DsMuNu_Sim09b"
                  ,  filesPerJob   = 10
                  ,  simulation    = True
                  ,  bkkQuery      = '/MC/2016/Beam6500GeV-2016-MagDown-Nu1.6-25ns-Pythia8/Sim09b/Trig0x6138160F/Reco16/Turbo03/Stripping26NoPrescalingFlagged/13774004/ALLSTREAMS.DST'
                  ,  stream        = "AllStreams"
      )


  MC15SigUp09bDsTauNu = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "Signal_DsTauNu_Sim09b"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24Filtered/13774060/B2DMUNUXANDTAU.DST'
                 ,  stream        = "B2DMUNUXANDTAU"                 
      )

  MC15SigDown09bDsTauNu = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "Signal_DsTauNu_Sim09b"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24Filtered/13774060/B2DMUNUXANDTAU.DST'
                 ,  stream        = "B2DMUNUXANDTAU"
      )


  MCInclDsUp = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "InclDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08f/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/23263020/ALLSTREAMS.DST'
                 ,  stream        = "AllStreams"
      )

  MCInclDsDown = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "InclDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08f/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/23263020/ALLSTREAMS.DST'
                 ,  stream        = "AllStreams"
      )

  MCInclDsUpFromB = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "InclDsFromB"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia6/Sim08c/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/23103003/ALLSTREAMS.DST'
                 ,  stream        = "AllStreams"
      )

  MCInclDsDownFromB = TupleJob(
                    year          = "2012"
                 ,  stripVersion  = "20"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "InclDsFromB"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia6/Sim08c/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/23103003/ALLSTREAMS.DST'
                 ,  stream        = "AllStreams"
      )
## 2015 Double charm
  MCBsDsDsUp = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "BsDsDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24Filtered/13574600/B2DMUNUXANDTAU.DST'
                 ,  stream        = "B2DMUNUXANDTAU"
      )

  MCBsDsDsDown = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "BsDsDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24Filtered/13574600/B2DMUNUXANDTAU.DST'
                 ,  stream        = "B2DMUNUXANDTAU"
      ) 

  MCBuD0DsUp = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "BuD0Ds"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24Filtered/12875600/B2DMUNUXANDTAU.DST'
                 ,  stream        = "B2DMUNUXANDTAU"
      )

  MCBuD0DsDown = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "BuD0Ds"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24Filtered/12875600/B2DMUNUXANDTAU.DST'
                 ,  stream        = "B2DMUNUXANDTAU"
      )

  MCBdDstDsUp = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "BdDstDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24Filtered/11876000/B2DMUNUXANDTAU.DST'
                 ,  stream        = "B2DMUNUXANDTAU"
      )

  MCBdDstDsDown = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "BdDstDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24Filtered/11876000/B2DMUNUXANDTAU.DST'
                 ,  stream        = "B2DMUNUXANDTAU"
      )

  MCLbLcDsUp = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagUp"
                 ,  suffix        = "LbLcDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24Filtered/15674300/B2DMUNUXANDTAU.DST'
                 ,  stream        = "B2DMUNUXANDTAU"
      )

  MCLbLcDsDown = TupleJob(
                    year          = "2015"
                 ,  stripVersion  = "24"
                 ,  magPol        = "MagDown"
                 ,  suffix        = "LbLcDs"
                 ,  filesPerJob   = 20
                 ,  simulation    = True
                 ,  bkkQuery      = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24Filtered/15674300/B2DMUNUXANDTAU.DST'
                 ,  stream        = "B2DMUNUXANDTAU"
      )


print "Preconfigured jobs you can just submit: "
for pidjob in TupleMaker.__dict__:
  if "__" not in pidjob:
    print ". TupleMaker." + pidjob + ".submit()"
print "---------------------"
