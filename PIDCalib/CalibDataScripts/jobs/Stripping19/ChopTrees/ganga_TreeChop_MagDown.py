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
bck.extraopts = "-l cput=11:58:00"

ErasmusVersion = "v8r1"

#Get username and create base directory
import subprocess
getName = subprocess.Popen("whoami", stdout=subprocess.PIPE)
uname = getName.communicate()[0].rstrip()
basedir = '/home/'+uname+'/cmtuser/Erasmus_'+ErasmusVersion+'/PIDCalib/CalibDataScripts'

#Explicit paths to files
script2Run = basedir+'/jobs/ChopTheTreesJob.sh'
runList = basedir+'/jobs/Stripping19/ChopTrees/RUNNUMBERS_DOWN.txt'

j = Job (
 name = 'MagDOWN_Strip19_TreeChop' ,
 outputsandbox = [] ,
 info = JobInfo (
    ) ,
 inputdata = None ,
 merger = None ,
 inputsandbox = [] ,
 application = Executable (
    exe = File(script2Run),
    args = [runList, 'PID_Modes_', '93', '0', '46']  
    ) ,
 outputdata = None ,
 splitter = None ,
 backend = bck
)

j.submit()
