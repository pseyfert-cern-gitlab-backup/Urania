# O. Leroy, Nov 2013
myname = ("Bd_upMC2012_pythia6","Bd_upMC2012_pythia8","Bd_downMC2012_pythia6","Bd_downMC2012_pythia8")

mytupleMaker = ("/zfs_lhcb/users/oleroy/2012-MC-Sim08a/upMC2012_pythia6.py","/zfs_lhcb/users/oleroy/2012-MC-Sim08a/upMC2012_pythia8.py","/zfs_lhcb/users/oleroy/2012-MC-Sim08a/downMC2012_pythia6.py","/zfs_lhcb/users/oleroy/2012-MC-Sim08a/downMC2012_pythia8.py")

myinputdata = ("/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia6/Sim08c/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/11144001/ALLSTREAMS.DST", "/MC/2012/Beam4000GeV-2012-MagUp-Nu2.5-Pythia8/Sim08c/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/11144001/ALLSTREAMS.DST", "/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia6/Sim08c/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/11144001/ALLSTREAMS.DST", "/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08c/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/11144001/ALLSTREAMS.DST")

for i in range(4):
  print "Create job"
  job=Job(application=DaVinci(version='v33r8') ,  name = myname[i])

  print "Specify option files"

  job.application.optsfile = [mytupleMaker[i]]
  job.outputfiles = ['DTT.root'] # 

  print "Specify input data : superseeds what is in option files"
  job.inputdata =  BKQuery(myinputdata[i], dqflag=['OK']).getDataset()

  # split job. Carefully choose filesPerJob 
  job.splitter = SplitByFiles(filesPerJob = 10, maxFiles = -1 , ignoremissing = True)
  
  print "Finally submit the job"
  job.backend    = Dirac()
  job.submit()


