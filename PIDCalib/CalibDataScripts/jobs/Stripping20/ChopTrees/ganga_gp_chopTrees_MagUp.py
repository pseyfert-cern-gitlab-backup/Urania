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
gangadir='$DATADISK/gangadir_calib/workspace/powell/LocalXML'

j = Job(
    name = 'Chop_Trees_Strip20_MagUp',
    application= GaudiPython(
    script = [basedir+'/scripts/python/chopTrees.py'],
    args = ['--jobID=246',
            '--runPickleFile='+basedir+'/jobs/Stripping20/ChopTrees/up_runLimits.pkl',
            '--minSubJob=0',
            '--maxSubJob=21',
            "--treeList=[DSt2D0Pi_D02RSKPiTuple/CalibPID,Lam02PPi_LoPTuple/CalibPID,Lam02PPi_HiPTuple/CalibPID]",
            '--gangadir='+gangadir]
    ),
    backend=bck
    )
j.submit()
