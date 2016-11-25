# prepare options for DaVinci job
def make_options(name,opts,data):
    APP = DaVinci()
    APP.version = 'v41r3'
    APP.optsfile=opts
    j = Job(
        name             = "%s" %name,
        application      = APP,
        inputdata        = data,
        splitter         = SplitByFiles(filesPerJob = 20, maxFiles = 100),
        outputfiles      = [DiracFile("DTT.root")],
        do_auto_resubmit = True,
        backend          = Dirac()
        )
    print data
    j.backend.settings["CPUTime"] = j.backend.settings["CPUTime"]*1000
    j.submit()

'''
data_2011_MU = BKQuery(path="/LHCb/Collision11/Beam3500GeV-VeloClosed-MagUp/Real Data/Reco14/Stripping21r1/90000000/DIMUON.DST", dqflag=['OK']).getDataset()
data_2011_MD = BKQuery(path="/LHCb/Collision11/Beam3500GeV-VeloClosed-MagDown/Real Data/Reco14/Stripping21r1/90000000/DIMUON.DST", dqflag=['OK']).getDataset()
data_2012_MU = BKQuery(path="/LHCb/Collision12/Beam4000GeV-VeloClosed-MagUp/Real Data/Reco14/Stripping21/90000000/DIMUON.DST", dqflag=['OK']).getDataset()
data_2012_MD = BKQuery(path="/LHCb/Collision12/Beam4000GeV-VeloClosed-MagDown/Real Data/Reco14/Stripping21/90000000/DIMUON.DST", dqflag=['OK']).getDataset()
'''
data_2015_MU = BKQuery(path="/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco15a/Stripping24/90000000/DIMUON.DST", dqflag=['OK']).getDataset()
'''
data_2015_MD = BKQuery(path="/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco15a/Stripping24/90000000/DIMUON.DST", dqflag=['OK']).getDataset()
data_2016_MU = BKQuery(path="/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco16/Stripping26/90000000/DIMUON.DST", dqflag=['OK']).getDataset()
data_2016_MD = BKQuery(path="/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco16/Stripping26/90000000/DIMUON.DST", dqflag=['OK']).getDataset()
#data_2015_MU_L = BKQuery(path="/LHCb/Collision15/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco15a/Stripping24/90000000/LEPTONIC.MDST", dqflag=['OK']).getDataset()
data_2015_MD_L = BKQuery(path="/LHCb/Collision15/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco15a/Stripping24/90000000/LEPTONIC.MDST", dqflag=['OK']).getDataset()
data_2016_MU_L = BKQuery(path="/LHCb/Collision16/Beam6500GeV-VeloClosed-MagUp/Real Data/Reco16/Stripping26/90000000/LEPTONIC.MDST", dqflag=['OK']).getDataset()
data_2016_MD_L = BKQuery(path="/LHCb/Collision16/Beam6500GeV-VeloClosed-MagDown/Real Data/Reco16/Stripping26/90000000/LEPTONIC.MDST", dqflag=['OK']).getDataset()
'''


#make_options("1UD_bs2JpsiKK",["/afs/cern.ch/user/b/bdey/cmtuser/bs2JpsiKK/bs2JpsiKK_Data_2011_LooseJpsi.py"],data_2011_MU)
#make_options("2UD_bs2JpsiKK",["/afs/cern.ch/user/b/bdey/cmtuser/bs2JpsiKK/bs2JpsiKK_Data_2012_LooseJpsi.py"],data_2012_MU)
#make_options("1DD_bs2JpsiKK",["/afs/cern.ch/user/b/bdey/cmtuser/bs2JpsiKK/bs2JpsiKK_Data_2011_LooseJpsi.py"],data_2011_MD)
#make_options("2DD_bs2JpsiKK",["/afs/cern.ch/user/b/bdey/cmtuser/bs2JpsiKK/bs2JpsiKK_Data_2012_LooseJpsi.py"],data_2012_MD)

#make_options("5UD_bs2JpsiKK_Carlos",["/afs/cern.ch/user/b/bdey/cmtuser/bs2JpsiKK/Bs2JpsiPhi_MAKER_RealData_Run2.py"],data_2015_MU)
make_options("5UD_bs2JpsiKK_JPhi",["/afs/cern.ch/user/b/bdey/cmtuser/bs2JpsiKK/bs2JpsiKK_Data_2015_JPhi.py"],data_2015_MU)
make_options("5UD_bs2JpsiKK",["/afs/cern.ch/user/b/bdey/cmtuser/bs2JpsiKK/bs2JpsiKK_Data_2015.py"],data_2015_MU)
#make_options("5UD_bs2JpsiKK_B2XMuMu_LokiDTF",["/afs/cern.ch/user/b/bdey/cmtuser/bs2JpsiKK/bs2JpsiKK_Data_2015_B2XMuMu.py"],data_2015_MU_L)
#make_options("6UD_bs2JpsiKK",["/afs/cern.ch/user/b/bdey/cmtuser/bs2JpsiKK/bs2JpsiKK_Data_2016_LooseJpsi.py"],data_2016_MU)
#make_options("5DD_bs2JpsiKK",["/afs/cern.ch/user/b/bdey/cmtuser/bs2JpsiKK/bs2JpsiKK_Data_2015_LooseJpsi.py"],data_2015_MD)
#make_options("6DD_bs2JpsiKK",["/afs/cern.ch/user/b/bdey/cmtuser/bs2JpsiKK/bs2JpsiKK_Data_2016_LooseJpsi.py"],data_2016_MD)


