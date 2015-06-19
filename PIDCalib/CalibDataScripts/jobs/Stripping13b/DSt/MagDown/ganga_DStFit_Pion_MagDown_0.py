#Ganga# File created by Ganga - Tue Sep  9 13:56:10 2008
#Ganga#
#Ganga# Object properties may be freely edited before reloading into Ganga
#Ganga#
#Ganga# Lines beginning #Ganga# are used to divide object definitions,
#Ganga# and must not be deleted

#Ganga# Job object (category: jobs)

# Choose local backend
#bck = Local()
# Choose PBS backend and specify walltime
bck = PBS()
bck.extraopts = "-l cput=47:58:00,mem=16G"

j = Job (
 name = 'DStFit_Pion_MagDown_Strip13b_0' ,
 outputsandbox = ['*.root', '*.eps'] ,
 info = JobInfo (
    ) ,
 inputdata = None ,
 merger = None ,
 inputsandbox = [] ,
 application = Executable (
    exe = File('/home/powell/cmtuser/Erasmus_v5r1/PIDCalib/CalibDataScripts/jobs/DStJob.csh'),
    args = '848 Pi Down 13b 0 149'
    ) ,
 outputdata = None ,
 splitter = None ,
 backend = bck
)

j.submit()
