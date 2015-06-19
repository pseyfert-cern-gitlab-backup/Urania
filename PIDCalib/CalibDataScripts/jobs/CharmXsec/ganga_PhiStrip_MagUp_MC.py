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
 name = 'Charm14nb_PhiStrip_MagUp_MC' ,
 outputsandbox = ['*.root'] ,
 info = JobInfo (
    ) ,
 inputdata = None ,
 merger = None ,
 inputsandbox = [] ,
 application = Executable (
    exe = File('/home/powell/cmtuser/Erasmus_v5r3/PIDCalib/CalibDataScripts/jobs/Charm14nb_PhiStrip.csh'),
    args = ['633']  
    ) ,
 outputdata = None ,
 splitter = None ,
 backend = bck
)

j.submit()
