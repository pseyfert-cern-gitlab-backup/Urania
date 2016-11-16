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
               ,  davinciVersion   = "v38r1p1"
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
    self._outputfilename = "BsMuMu_ntuples.root"
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

    if jobName == None:
      jobName="BsMuMu-Col{coll}-{pol}-S{strp}-{suf}".format(
         coll=self._collVersion, rec=self._recoVersion,
         strp=self._stripVersion, suf=self._suffix, pol=self._magPol)
      if self.simulation:
         jobName="BsMuMu-MC{coll}-{pol}-S{strp}-{suf}".format(
            coll=self._collVersion, rec=self._recoVersion,
            strp=self._stripVersion, suf=self._suffix, pol=self._magPol)

    self._gangaJob = Job(
      name = jobName
      , application = DaVinci(version = self._davinciVersion)
    )

    j = self._gangaJob
    j.application.optsfile = self.optsfile
    if self.simulation:
      j.application.optsfile += ["Bs2MuMu_ntuples_MC.py"]
    else:
      j.application.optsfile += ["Bs2MuMu_ntuples_data.py"]

    j.inputdata = self._getDatasetFromBK(bkkQuery)
    if self.backend == Local():
      j.outputfiles = [LocalFile(self._outputfilename)]
    else:
      j.outputfiles = [DiracFile(self._outputfilename)]

    j.inputfiles = [LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r1p1/Phys/Bs2MuMu/options/600_2500_4_30_0.75_1_1_BDT.weights.xml"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r1p1/Phys/Bs2MuMu/options/600_2500_4_30_0.75_1_4_BDT.weights.xml"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r1p1/Phys/Bs2MuMu/options/600_2500_4_30_0.75_1_8_BDT.weights.xml"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r1p1/Phys/Bs2MuMu/options/600_2500_4_30_0.75_1_9_BDT.weights.xml"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r1p1/Phys/Bs2MuMu/options/TMVA_7Dec.weights.xml"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r1p1/Phys/Bs2MuMu/operators/weights/HflatBDTS_7Dec.root"),
                    LocalFile("/afs/cern.ch/user/r/rvazquez/cmtuser/DaVinci_v38r1p1/Phys/Bs2MuMu/options/ZVisoBDTG_BsMuMu.weights.xml") 
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

  MC_2012BdRhoMuNuDown = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "BdRhoMuNu"
                 ,  filesPerJob    = 5
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08h/Digi13/Trig0x409f0045/Reco14c/Stripping21NoPrescalingFlagged/11512400/ALLSTREAMS.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "AllStreams"
                 ,  backend        = Dirac()
      )

  MC_2012BdRhoMuNuUp = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "BdRhoMuNu"
                 ,  filesPerJob    = 5
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08h/Digi13/Trig0x409f0045/Reco14c/Stripping21NoPrescalingFlagged/11512400/ALLSTREAMS.DST' 
                 ,  bkkFlag        = "All"
                 ,  stream         = "AllStreams"
                 ,  backend        = Dirac()
      ) 

  MC2015BdKPiDown = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "BdKpi"
                 ,  filesPerJob    = 5
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/11102003/ALLSTREAMS.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "AllStreams"
                 ,  backend        = Dirac()
      )

  MC2015BdKPiUp = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "BdKpi"
                 ,  filesPerJob    = 5
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/11102003/ALLSTREAMS.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "AllStreams"
                 ,  backend        = Dirac()
      )

  MC2015BsJpsiPhiDown = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "BsJpsiPhi"
                 ,  filesPerJob    = 5
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/13144002/ALLSTREAMS.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "AllStreams"
                 ,  backend        = Dirac()
      )

  MC2015BsJpsiPhiUp = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "BsJpsiPhi"
                 ,  filesPerJob    = 5
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/13144002/ALLSTREAMS.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "AllStreams"
                 ,  backend        = Dirac()
      )


  MC2015BuJpsiKDown = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "BuJpsiK"
                 ,  filesPerJob    = 5
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/12143001/ALLSTREAMS.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "AllStreams"                 
                 ,  backend        = Dirac()
      )

  MC2015BuJpsiKUp = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "BuJpsiK"
                 ,  filesPerJob    = 5
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/12143001/ALLSTREAMS.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "AllStreams"                 
                 ,  backend        = Dirac()
      ) 

  MC2015BsKMuNuDown = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "BsKMuNu"
                 ,  filesPerJob    = 5
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/13512011/ALLSTREAMS.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "AllStreams"
                 ,  backend        = Dirac()
      )

  MC2015BsKMuNuUp = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "BsKMuNu"
                 ,  filesPerJob    = 5
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/13512011/ALLSTREAMS.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "AllStreams"
                 ,  backend        = Dirac()
      )

  MC2015BsMuMuDown = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "BsMuMu"
                 ,  filesPerJob    = 5
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2015/Beam6500GeV-2015-MagDown-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/13112001/ALLSTREAMS.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "AllStreams"
                 ,  backend        = Dirac()
      )

  MC2015BsMuMuUp = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "BsMuMu"
                 ,  filesPerJob    = 5
                 ,  simulation     = True
                 ,  bkkQuery       = '/MC/2015/Beam6500GeV-2015-MagUp-Nu1.6-25ns-Pythia8/Sim09a/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/13112001/ALLSTREAMS.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "AllStreams"
                 ,  backend        = Dirac()
      )

  down11Lep = TupleJob(
                    year           = "2011"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "DataLeptonic"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision11/Beam3500GeV-VeloClosed-MagDown/Real Data/Reco14/Stripping21r1/90000000/LEPTONIC.MDST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "DIMUON"
                 ,  backend        = Dirac()
      )

  up11Lep = TupleJob(
                    year           = "2011"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "DataLeptonic"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision11/Beam3500GeV-VeloClosed-MagUp/Real Data/Reco14/Stripping21r1/90000000/LEPTONIC.MDST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "DIMUON"
                 ,  backend        = Dirac()
      )
 
  
  down11Dimuon = TupleJob(
                    year           = "2011"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "DataDimuon"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision11/Beam3500GeV-VeloClosed-MagDown/Real Data/Reco14/Stripping21r1/90000000/DIMUON.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "DIMUON"
                 ,  backend        = Dirac()
      )

  up11Dimuon = TupleJob(
                    year           = "2011"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "DataDimuon"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision11/Beam3500GeV-VeloClosed-MagUp/Real Data/Reco14/Stripping21r1/90000000/DIMUON.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "DIMUON"
                 ,  backend        = Dirac()
      )

  down12Lep = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "DataLeptonic"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision12/Beam4000GeV-VeloClosed-MagDown/Real Data/Reco14/Stripping21/90000000/LEPTONIC.MDST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "LEPTONIC"
                 ,  backend        = Dirac()
      )

  up12Lep = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "DataLeptonic"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision12/Beam4000GeV-VeloClosed-MagUp/Real Data/Reco14/Stripping21/90000000/LEPTONIC.MDST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "LEPTONIC"
                 ,  backend        = Dirac()
      )


  down12Dimuon = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "DataDimuon"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision12/Beam4000GeV-VeloClosed-MagDown/Real Data/Reco14/Stripping21/90000000/DIMUON.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "DIMUON"
                 ,  backend        = Dirac() 
      )

  up12Dimuon = TupleJob(
                    year           = "2012"
                 ,  stripVersion   = "21"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "DataDimuon"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision12/Beam4000GeV-VeloClosed-MagUp/Real Data/Reco14/Stripping21/90000000/DIMUON.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "DIMUON"
                 ,  backend        = Dirac()
      )

  down15Dimuon = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "DataDimuon"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco15a/Stripping24/90000000/DIMUON.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "DIMUON"
                 ,  backend        = Dirac()
      )

  up15Dimuon = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "DataDimuon"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco15a/Stripping24/90000000/DIMUON.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "DIMUON"
                 ,  backend        = Dirac()
      )

  down15Lep = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "DataLeptonic"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco15a/Stripping24/90000000/LEPTONIC.MDST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "LEPTONIC"
                 ,  backend        = Dirac()
      )

  up15Lep = TupleJob(
                    year           = "2015"
                 ,  stripVersion   = "24"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "DataLeptonic"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco15a/Stripping24/90000000/LEPTONIC.MDST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "LEPTONIC"
                 ,  backend        = Dirac()
      )

  down16Dimuon = TupleJob(
                    year           = "2016"
                 ,  stripVersion   = "26"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "DataDimuon"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco16/Stripping26/90000000/DIMUON.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "DIMUON"
                 ,  backend        = Dirac()
      )

  up16Dimuon = TupleJob(
                    year           = "2016"
                 ,  stripVersion   = "26"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "DataDimuon"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco16/Stripping26/90000000/DIMUON.DST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "DIMUON"
                 ,  backend        = Dirac()
      )

  down16Lep = TupleJob(
                    year           = "2016"
                 ,  stripVersion   = "26"
                 ,  magPol         = "MagDown"
                 ,  suffix         = "DataLeptonic"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco16/Stripping26/90000000/LEPTONIC.MDST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "LEPTONIC"
                 ,  backend        = Dirac()
      )

  up16Lep = TupleJob(
                    year           = "2016"
                 ,  stripVersion   = "26"
                 ,  magPol         = "MagUp"
                 ,  suffix         = "DataLeptonic"
                 ,  filesPerJob    = 20
                 ,  simulation     = False
                 ,  bkkQuery       = '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco16/Stripping26/90000000/LEPTONIC.MDST'
                 ,  bkkFlag        = "All"
                 ,  stream         = "LEPTONIC"
                 ,  backend        = Dirac()
      )

print "Preconfigured jobs you can just submit: "
for pidjob in TupleMaker.__dict__:
  if "__" not in pidjob:
    print ". TupleMaker." + pidjob + ".submit()"
print "---------------------"

