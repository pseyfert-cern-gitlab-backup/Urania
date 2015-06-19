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
 name = 'B2DX_EvtData_B2DPi_D2KPi_MagDown_Perf_Strip17' ,
 outputsandbox = ['*.root', '*.txt'] ,
 info = JobInfo (
    ) ,
 inputdata = None ,
 merger = None ,
 inputsandbox = [] ,
 application = Executable (
    exe = File('/home/powell/cmtuser/Erasmus_v6r0/PIDCalib/PIDPerfScripts/jobs/B2DX/JobPerf.sh'),
    args = ['Down', 'kpi', '26', '9'] 
    ) ,
 outputdata = None ,
 splitter = None ,
 backend = bck
)

j.submit()
