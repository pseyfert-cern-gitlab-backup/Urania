# Choose local backend
bck = Local()

ErasmusVersion = "v9r0"

basedir = '/afs/cern.ch/user/j/jotalora/w0/newcmtuser/Erasmus_'+ErasmusVersion+'/PIDCalib/CalibDataScripts'
gangadir ='/afs/cern.ch/work/j/jotalora/PID_Calib/gangadir/workspace/jotalora/LocalXML'

j = Job(
    name = 'Chop_Trees_Strip17_MagDown',
    application= GaudiPython(
    script = [basedir+'/scripts/python/chopTrees.py'],
    args = ['--jobID=184',
            '--runPickleFile='+basedir+'/jobs/MUON/Stripping17/ChopTrees/down_runLimits_mu_and_p_muonUnBiased.pkl',
            '--minSubJob=41',
            '--maxSubJob=41',
            "--treeList=[JpsiFromBNoPIDNoMipTuple/CalibPID,DSt2D0Pi_D02RSKPiTuple/CalibPID,Lam02PPi_LoPTuple/CalibPID,Lam02PPi_HiPTuple/CalibPID]",
            '--gangadir='+gangadir,
            '--fileSuffix=mu_and_p_muonUnBiased']
    ),
    backend=bck
    )
j.submit()

