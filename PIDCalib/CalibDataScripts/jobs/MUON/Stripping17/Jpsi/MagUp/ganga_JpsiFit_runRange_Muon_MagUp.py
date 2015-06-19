#Ganga# File created by Ganga - Tue Sep  9 13:56:10 2008
#Ganga#
#Ganga# Object properties may be freely edited before reloading into Ganga
#Ganga#
#Ganga# Lines beginning #Ganga# are used to divide object definitions,
#Ganga# and must not be deleted

#Ganga# Job object (category: jobs)

# Choose local backend
bck = Local()

j = Job (
 name = 'JpsiFit_Muon_MagUp_Strip17' ,
 outputfiles = [SandboxFile('*.root'), '*.pdf'] , 
 info = JobInfo (
    ) ,
 inputdata = None ,
 merger = None ,   
 inputsandbox = [] ,
 application = Executable (
    exe = File('/afs/cern.ch/user/j/jotalora/w0/newcmtuser/Erasmus_v9r0/PIDCalib/CalibDataScripts/jobs/MUON/JpsiJob_runRange.sh'),
    args = ['Mu', 'Up', '17', '0', '3', '132', '2011', 'mu_and_p_muonUnBiased']
    ) ,
 outputdata = None ,
 splitter = None ,  
 backend = bck
)
 
j.submit()


