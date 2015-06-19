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
basedir = '/home/'+uname+'/cmtuser/Erasmus_'+ErasmusVersion+'/PIDCalib/PIDPerfScripts'

j = Job(
    name = 'PerfCurves_Hamish_Pos_92000_94999',
    application= GaudiPython(
    project='Erasmus',
    version=ErasmusVersion,
    script = [basedir+'/python/ChrgAsym/PerfCurvesChrgAsym.py'],
    args = ['--recoVersion=12',
            '--minRun=92000',
            '--maxRun=94999',
            '--minDLLCut=-2',
            '--maxDLLCut=30',
            '--KaonCuts=Charge==Charge::Positive && K_P<100000',
            '--PionCuts=Charge==Charge::Positive && Pi_P<100000'],
    user_release_area = '/home/'+uname+'/cmtuser'
    ),
    backend=bck,
    outputsandbox=['*.root']
    )
j.submit()
