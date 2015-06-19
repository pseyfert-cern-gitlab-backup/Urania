# Choose local backend
bck = Local()

ErasmusVersion = "v9r0"

basedir = '/afs/cern.ch/user/j/jotalora/w0/newcmtuser/Erasmus_'+ErasmusVersion+'/PIDCalib/CalibDataScripts'
inputdir ='/tmp/jotalora/Collision12-Reco14-Stripping20-MagUp_CalibSel'
gangadir_calib ='/afs/cern.ch/work/j/jotalora/PID_Calib/gangadir/workspace/jotalora/LocalXML'

j = Job(
    name = 'MuonProbTag_Strip20_MagUp',
    application= GaudiPython(
    script = [basedir+'/scripts/python/MuonProbTagTriggerProcess.py'],
    args = ['--ganga_dir='+gangadir_calib,
            '--input_dir='+inputdir,
            '--inputJobID=7',
            '--outputJobID=7',
            '--minSubJob=166',
            '--maxSubJob=238']
    ),
    backend=bck
    )
j.submit()

