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
 name = 'DStMuonUnbiasedFit_Pion_MagUp_Strip20' ,
 outputfiles = [SandboxFile('*.root'), '*.pdf'] , 
 info = JobInfo (
    ) ,
 inputdata = None ,
 merger = None ,   
 inputsandbox = [] ,
 application = Executable (
    exe = File('/afs/cern.ch/user/j/jotalora/w0/newcmtuser/Erasmus_v9r0/PIDCalib/CalibDataScripts/jobs/MUON/DStMuonUnbiasedJob_runRange.sh'),
    args = ['Pi', 'Up', '20', '0', '5', '7', '2012', 'h_muonUnBiased']
    ) ,
 outputdata = None ,
 splitter = None ,  
 backend = bck
)
 
j.submit()


