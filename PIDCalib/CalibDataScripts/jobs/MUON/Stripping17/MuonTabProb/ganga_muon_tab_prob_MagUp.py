# Choose local backend
bck = Local()

ErasmusVersion = "v9r0"

basedir = '/afs/cern.ch/user/j/jotalora/w0/newcmtuser/Erasmus_'+ErasmusVersion+'/PIDCalib/CalibDataScripts'
inputdir ='/tmp/jotalora/Collision11-Reco12-Stripping17-MagUp_CalibSel'
gangadir_calib ='/afs/cern.ch/work/j/jotalora/PID_Calib/gangadir/workspace/jotalora/LocalXML'

j = Job(
    name = 'MuonProbTag_Strip17_MagUp',
    application= GaudiPython(
    script = [basedir+'/scripts/python/MuonProbTagTriggerProcess.py'],
    args = ['--ganga_dir='+gangadir_calib,
            '--input_dir='+inputdir,
            '--inputJobID=132',
            '--outputJobID=132',
            '--minSubJob=0',
            '--maxSubJob=123']
    ),
    backend=bck
    )
j.submit()

