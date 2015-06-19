# Choose local backend
bck = Local()

ErasmusVersion = "v9r0"

basedir = '/afs/cern.ch/user/j/jotalora/w0/newcmtuser/Erasmus_'+ErasmusVersion+'/PIDCalib/CalibDataScripts'
inputdir ='/tmp/jotalora/Collision11-Reco12-Stripping17-MagDown_CalibSel'
gangadir_calib ='/afs/cern.ch/work/j/jotalora/PID_Calib/gangadir/workspace/jotalora/LocalXML'

j = Job(
    name = 'MuonProbTag_Strip17_MagDown',
    application= GaudiPython(
    script = [basedir+'/scripts/python/MuonProbTagTriggerProcess.py'],
    args = ['--ganga_dir='+gangadir_calib,
            '--input_dir='+inputdir,
            '--inputJobID=184',
            '--outputJobID=184',
            '--minSubJob=41',
            '--maxSubJob=41']
    ),
    backend=bck
    )
j.submit()

