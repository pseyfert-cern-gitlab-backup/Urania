# C. Vazquez Sierra, Oct 2016

isTurbo    = True
dv_version = "v41r3"
maker_path = 'Bs2JpsiPhi_MAKER_RealData_Run2.py'
if isTurbo:
   maker_path = 'Bs2JpsiPhi_MAKER_RealData_Run2_Turbo.py'
NumberOfFiles = 1 #-1




def create_job(Name, OptsFile, input_path, NFilePerJob, MaxFiles, OutputTuple = "DTT.root"):
   print input_path
   Application = DaVinci()
   Application.version = dv_version
   Application.optsfile = [File(OptsFile)]
   dataSet = BKQuery(input_path, type = "Path", dqflag=['OK']).getDataset()
   print dataSet
   job = Job(name           = Name,
             application    = Application,
             splitter       = SplitByFiles(filesPerJob = NFilePerJob, maxFiles = MaxFiles, ignoremissing = True),
             postprocessors = RootMerger(files = [OutputTuple], overwrite=True, ignorefailed=True),
             outputfiles    = [LocalFile(namePattern = "*.root")],
             #inputdata      = DaVinci(version = dv_version).readInputData(input_path), # If using datacards, instead.
             inputdata      = dataSet,
             backend        = Dirac())
   job.do_auto_resubmit  = True
   job.parallel_submit   = True
   job.submit(keep_going = True)

input_paths = { 'MagnetDown_2015': '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco15a/Stripping24/90000000/DIMUON.DST'
              , 'MagnetUp_2015'  : '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco15a/Stripping24/90000000/DIMUON.DST' 
              , 'MagnetDown_2016': '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco16/Stripping26/90000000/DIMUON.DST'
              , 'MagnetUp_2016'  : '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco16/Stripping26/90000000/DIMUON.DST' }


if isTurbo:
   input_paths = { 'MagnetDown_2015'  : '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo02/94000000/TURBO.MDST'
                   , 'MagnetUp_2015'  : '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Turbo02/94000000/TURBO.MDST'
                   , 'MagnetDown_2016': '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Turbo03/94000000/LEPTONS.MDST'
                   , 'MagnetUp_2016'  : '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Turbo03/94000000/LEPTONS.MDST' }



#keys = [ 'MagnetDown_2015', 'MagnetUp_2015' ]
keys = [ 'MagnetDown_2016', 'MagnetUp_2016' ]

for key in keys: create_job(key, maker_path, input_paths[key], 10, NumberOfFiles)
