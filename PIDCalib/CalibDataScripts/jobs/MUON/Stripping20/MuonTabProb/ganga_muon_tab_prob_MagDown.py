# Choose local backend
bck = Local()

ErasmusVersion = "v9r0"

basedir = '/afs/cern.ch/user/j/jotalora/w0/newcmtuser/Erasmus_'+ErasmusVersion+'/PIDCalib/CalibDataScripts'
inputdir ='/tmp/jotalora/Collision12-Reco14-Stripping20-MagDown_CalibSel'
gangadir_calib ='/afs/cern.ch/work/j/jotalora/PID_Calib/gangadir/workspace/jotalora/LocalXML'

j = Job(
    name = 'MuonProbTag_Strip20_MagDown',
    application= GaudiPython(
    script = [basedir+'/scripts/python/MuonProbTagTriggerProcess.py'],
    args = ['--ganga_dir='+gangadir_calib,
            '--input_dir='+inputdir,
            '--inputJobID=8',
            '--outputJobID=8',
            '--minSubJob=191',
            '--maxSubJob=350']
    ),
    backend=bck
    )
j.submit()

