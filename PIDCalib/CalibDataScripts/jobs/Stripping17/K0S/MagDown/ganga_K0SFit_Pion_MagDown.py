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
bck.extraopts = "-l cput=11:58:00,mem=16G"

j = Job (
 name = 'K0SFit_Pion_MagDown_Strip15' ,
 outputsandbox = ['*.root', '*.eps'] ,
 info = JobInfo (
    ) ,
 inputdata = None ,
 merger = None ,
 inputsandbox = [] ,
 application = Executable (
    exe = File('/home/powell/cmtuser/Erasmus_v5r3/PIDCalib/CalibDataScripts/jobs/K0SJob.sh'),
    args = ['1034', 'Down', '15', '110', '543']  
    ) ,
 outputdata = None ,
 splitter = None ,
 backend = bck
)

j.submit()
