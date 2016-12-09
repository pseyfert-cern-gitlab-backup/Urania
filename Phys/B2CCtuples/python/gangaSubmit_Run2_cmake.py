# C. Vazquez Sierra, Oct 2016
# Sevda Esen, Dec 2016, added possibility to run Turbo

isTurbo    =  True
dv_version = "v41r3"
maker_path = 'Bs2JpsiPhi_MAKER_RealData_Run2.py'
if isTurbo is True:
   maker_path = 'Bs2JpsiPhi_MAKER_RealData_Run2_Turbo.py'
NumberOfFiles = 1 #-1

def create_job(Name, OptsFile, input_path, NFilePerJob, MaxFiles, OutputTuple = "DTT.root"):
   print input_path

   #prepareGaudiExec(DaVinci(),dv_version, ".", "") 
   application          = GaudiExec()
   application.directory="/afs/cern.ch/lhcb/software/releases/DAVINCI/DAVINCI_v41r3/"
   application.options  = [OptsFile]
   dataSet              = BKQuery(input_path, type = "Path", dqflag=['OK']).getDataset()
   print dataSet
   job                = Job()
   job.name           = Name
   job.application    = application 
   job.splitter       = SplitByFiles(filesPerJob = NFilePerJob, maxFiles = MaxFiles, ignoremissing = True)
   job.postprocessors = RootMerger(files = [OutputTuple], overwrite=True, ignorefailed=True)
   job.outputfiles    = [LocalFile(namePattern = "*.root")],
   #job.inputdata      = DaVinci(version = dv_version).readInputData(input_path), # If using datacards, instead.
   job.inputdata      = dataSet
   job.backend        = Dirac()
   job.do_auto_resubmit  = True
   job.parallel_submit   = True
   job.submit(keep_going = True)

input_paths = { 'MagnetDown_2015'  : '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco15a/Stripping24/90000000/DIMUON.DST'
                , 'MagnetUp_2015'  : '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco15a/Stripping24/90000000/DIMUON.DST' 
                , 'MagnetDown_2016': '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco16/Stripping26/90000000/DIMUON.DST'
                , 'MagnetUp_2016'  : '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco16/Stripping26/90000000/DIMUON.DST' }

if isTurbo: 
   input_paths = { 'MagnetDown_2015'  : '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo03/94000000/LEPTONS.MDST' 
                   , 'MagnetUp_2015'  : '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Turbo03/94000000/LEPTONS.MDST' 
                   , 'MagnetDown_2016': '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo03/94000000/LEPTONS.MDST' 
                   , 'MagnetUp_2016'  : '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Turbo03/94000000/LEPTONS.MDST' }
   



keys = [ 'MagnetDown_2015', 'MagnetUp_2015' ]
#keys = [ 'MagnetDown_2016', 'MagnetUp_2016' ]

for key in keys: create_job(key, maker_path, input_paths[key], 1, NumberOfFiles)
