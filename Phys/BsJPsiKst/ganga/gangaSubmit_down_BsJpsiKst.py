print "Create job"
job=Job(application=DaVinci(version='v33r0p1') ,  name ='downMCBsJpsiKst' )

print "Specify option files"

job.application.optsfile = ['/lhcb/users/oleroy/public/walaa/code/20121201-MCtuple/BuBdBs_NTUPLE_maker_MC.py']
job.outputsandbox = ['DTT.root'] # Use
#job.outputdata = ['DTT.root'] # if no enough space on lxplus !

print "Specify input data : superseeds what is in option files"
job.inputdata =  DaVinci().readInputData('/lhcb/users/oleroy/public/walaa/code/20121201-MCtuple/MCMC11a13444001Beam3500GeV-2011-MagDown-Nu2-EmNoCutsSim05Trig0x40760037FlaggedReco12Stripping17NoPrescalingFlaggedSTREAMSDST.py')


print "Calls Dirac splitter"
job.splitter = DiracSplitter(filesPerJob = 20, maxFiles = -1 , ignoremissing = True)

# ol adds:
# SmartMerger - Able to handle various file formats (including root files)
#               See help( SmartMerger ) for more details  
job.merger = SmartMerger( files = ['DTT.root'], ignorefailed = True )

# for LSF :
print "Finally submit the job"
job.backend    = Dirac()
job.submit()


