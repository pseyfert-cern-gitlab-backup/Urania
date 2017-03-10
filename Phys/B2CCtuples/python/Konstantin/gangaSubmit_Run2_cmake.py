# C. Vazquez Sierra, Oct 2016
# Sevda Esen, Dec 2016, added possibility to run Turbo
# Sevda Esen, Mar 2017, added MC bkk paths
import os

dv_version = "v42r1"

simulation=False
year ="2016"
dtype="DST" 
evtype="24142001" ##incl jpsi
#evtype="13144011" ##Bs2jpsiphi, 2016 update

NumberOfFiles = 1

maker_path = 'Bs2JpsiPhi_2016_Data.py' ##this should be selected based on event type and dsta type
if simulation:
   if evtype is "24142001":
      maker_path = 'Bs2JpsiPhi_2016_MC_prompt.py' ##this should be selected based on event type and dsta type
   if evtype is "13144011":
      maker_path = 'Bs2JpsiPhi_2016_MC.py' ##this should be selected based on event type and dsta type
      dtype="MDST" ##for now, this file turns of the PV refit


print "your setup is "
print "year: " + year
if simulation:
   print "simulation " 
   print "event type: " + evtype


def create_job(Name, OptsFile, input_path,  NFilePerJob, MaxFiles,extraOpts,  OutputTuple = "DTT.root"):
   print input_path


   if os.path.isdir("DaVinciDev_"+dv_version):
      application          = GaudiExec()
      application.directory="./DaVinciDev_"+dv_version
   else:
      application          = prepareGaudiExec("DaVinci",dv_version,myPath='.')

   application.options  = [OptsFile]
   application.extraOpts  = extraOpts

   dataSet              = BKQuery(input_path, type = "Path", dqflag=['OK']).getDataset()
   print dataSet
   
   job                = Job()
   job.name           = Name
   job.application    = application 
   job.splitter       = SplitByFiles(filesPerJob = NFilePerJob, maxFiles = MaxFiles, bulksubmit = False)
   job.outputfiles    = [LocalFile(namePattern = "*.root")]
   job.inputdata      = dataSet
   job.backend        = Dirac()
   job.do_auto_resubmit  = True
   job.parallel_submit   = True
   job.submit(keep_going = True)




if simulation: 
   
   input_paths = { 'MagnetUp_2015'    : '/MC/'+year+'/Beam6500GeV-'+year+'-MagUp-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/'+evtype+'/ALLSTREAMS.'+dtype
                   ,'MagnetDown_2015' : '/MC/'+year+'/Beam6500GeV-'+year+'-MagDown-Nu1.6-25ns-Pythia8/Sim09b/Trig0x411400a2/Reco15a/Turbo02/Stripping24NoPrescalingFlagged/'+evtype+'/ALLSTREAMS.'+dtype
                   ,'MagnetUp_2016'    : '/MC/'+year+'/Beam6500GeV-'+year+'-MagUp-Nu1.6-25ns-Pythia8/Sim09b/Trig0x6138160F/Reco16/Turbo03/Stripping26NoPrescalingFlagged/'+evtype+'/ALLSTREAMS.'+dtype
                   ,'MagnetDown_2016' : '/MC/'+year+'/Beam6500GeV-'+year+'-MagDown-Nu1.6-25ns-Pythia8/Sim09b/Trig0x6138160F/Reco16/Turbo03/Stripping26NoPrescalingFlagged/'+evtype+'/ALLSTREAMS.'+dtype
                   }


else:
   input_paths = { 'MagnetDown_2015'  : '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco15a/Stripping24/90000000/DIMUON.DST'
                   , 'MagnetUp_2015'  : '/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco15a/Stripping24/90000000/DIMUON.DST'
                   , 'MagnetDown_2016': '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco16/Stripping26/90000000/DIMUON.DST'
                   , 'MagnetUp_2016'  : '/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco16/Stripping26/90000000/DIMUON.DST' }

extraopts='from Configurables import DaVinci'
extraopts= extraopts+';DaVinci().DataType       = "'+year+'"'
extraopts= extraopts+';DaVinci().EvtMax         = -1 '                 
extraopts= extraopts+';DaVinci().InputType      = "'+dtype+'"'                                                                              

if simulation:
   extraopts= extraopts+';DaVinci().Simulation     = True'
   extraopts= extraopts+';DaVinci().Lumi           = False'
   extraopts= extraopts+';DaVinci().DDDBtag        = "dddb-20150724"'   # Sim09b
else:
   extraopts= extraopts+';DaVinci().Simulation     = False'
   extraopts= extraopts+';DaVinci().Lumi           = True'


keys = [ 'MagnetUp_2016', 'MagnetDown_2016' ] 


for key in keys: 
   name=key+evtype
   
   if simulation:
      if 'Down' in key:
         extraopts= extraopts+';DaVinci().CondDBtag  ="sim-20161124-2-vc-md100"'
      if 'Up' in key:
         extraopts= extraopts+';DaVinci().CondDBtag  ="sim-20161124-2-vc-mu100"'
      
   create_job(name, maker_path, input_paths[key], 10, NumberOfFiles, extraopts)


   





