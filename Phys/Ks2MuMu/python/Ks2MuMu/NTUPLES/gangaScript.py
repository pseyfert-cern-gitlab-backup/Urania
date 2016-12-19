#############################################################
#
# Ganga script to send the Ks -> mu+ mu- analysis jobs
# 
# @author: Miguel Ramos Pernas
#

##################################################
### If the test option is not enabled, one must
### specify the following variables:
# MODE     = 'MCKsmumu'
# MAGNET   = 'Up'
# MCMATCH  = True
# STRIPSEL = False

###########################################################
### Configuration options to run the code. Between the two,
### it always executes it on local
LocalTest = False
DiracTest = False
test = LocalTest or DiracTest
if test:
    MAGNET   = 'Up'
    STRIPSEL = False
    MCMATCH  = True
    if LocalTest:
        MODE   = 'MCMB08a'
        fpath  = '/afs/cern.ch/user/m/mramospe/work/public/TestDSTs/'\
            'MinBias_Pythia8_Sim08a_Digi13_Trig0x409f0045_Reco14a_'\
            'Stripping20NoPrescalingFlagged_MagnetUp.dst'
    else:
        MODE  = 'MCKsmumu'
        fpath = 'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00031732/0000/00031732_00000001_1.allstreams.dst'

#########################################################
### Application
Application = DaVinci()
Application.version = 'v36r4p1'

#########################################################
### Defines the option file and the MuID BDT weights file
Application.optsfile = ['./OptsFile.py']

Inputfiles = [LocalFile('/home3/miguel.ramos/cmtuser/DaVinci_v36r4p1/Phys/Ks2MuMuTuples/tmva/BDTontop/MuonTMVA_BDTv3.weights.xml')]

#########################################################
### DSTs and tag definition for each mode
bookmark = { 'dataKsmumu'  : '/LHCb/Collision12/Beam4000GeV-VeloClosed-MagDown/Real Data/Reco14/Stripping20r0p3/90000000/DIMUON.DST',
             'dataKspipi'  : '/LHCb/Collision12/Beam4000GeV-VeloClosed-MagDown/Real Data/Reco14/Stripping20r0p3/90000000/DIMUON.DST',
             'dataMB'      :   '/LHCb/Collision12/Beam4000GeV-VeloClosed-MagDown/Real Data/Reco14/Stripping20/90000000/MINIBIAS.DST',
             'MCMB08a'     : '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08a/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/30000000/ALLSTREAMS.DST',
             'MCMB08c'     : '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08c/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/30000000/ALLSTREAMS.DST',
             'MCKsmumu'    : '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08c/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/34112104/ALLSTREAMS.DST',
             'MCKsmumuNEW' : '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08i/Digi13/Trig0x409f0045/Reco14c/Stripping20NoPrescalingFlagged/34112106/ALLSTREAMS.DST',
             'MCKspipi'    : '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08c/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/34102105/ALLSTREAMS.DST',
             'MCKspimunu'  : '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08e/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/34512105/ALLSTREAMS.DST',
             'MCBJpsiK'    : '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08e/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/12143001/ALLSTREAMS.DST',
             'MCKsmumu0'   : '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08c/Digi13/Trig0x409f0045/Reco14a/Stripping20NoPrescalingFlagged/34112100/ALLSTREAMS.DST',
             'MCKspipiLDST': '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08h/Digi13/Trig0x409f0045/Reco14c/Stripping20r0p3Filtered/34102107/KSMM.STRIP.DST',
             'MCKsmumuLDST': '/MC/2012/Beam4000GeV-2012-MagDown-Nu2.5-Pythia8/Sim08h/Digi13/Trig0x409f0045/Reco14c/Stripping20r0p3Filtered/34112106/KSMM.STRIP.DST'
             }

dddbTag = { 'dataKsmumu'  : '',
            'dataKspipi'  : '',
            'dataMB'      : '',
            'MCMB08a'     : 'Sim08-20130503-1',
            'MCMB08c'     : 'dddb-20130929-1',
            'MCKsmumu'    : 'dddb-20130929-1',
            'MCKsmumuNEW' : 'dddb-20130929-1',
            'MCKspipi'    : 'dddb-20130929-1',
            'MCKspimunu'  : 'dddb-20130929-1',
            'MCBJpsiK'    : 'dddb-20130929-1',
            'MCKsmumu0'   : 'dddb-20130929-1',
            'MCKspipiLDST': 'dddb-20150703',
            'MCKsmumuLDST': 'dddb-20150703'
            }

condDBTag = {'dataKsmumu'  : '',
             'dataKspipi'  : '',
             'dataMB'      : '',
             'MCMB08a'     : 'Sim08-20130503-1-vc-md100',
             'MCMB08c'     : 'sim-20130522-1-vc-md100',
             'MCKsmumu'    : 'sim-20130522-1-vc-md100',
             'MCKsmumuNEW' : 'sim-20130522-1-vc-md100',
             'MCKspipi'    : 'sim-20130522-1-vc-md100',
             'MCKspimunu'  : 'sim-20130522-1-vc-md100',
             'MCBJpsiK'    : 'sim-20130522-1-vc-md100',
             'MCKsmumu0'   : 'sim-20130522-1-vc-md100',
             'MCKspipiLDST': 'sim-20150703-vc-md100',
             'MCKsmumuLDST': 'sim-20150703-vc-md100'
             }

### Modifies the input files and the condDB tags depending on the polarity
bkOpt = bookmark[MODE]
cdOpt = condDBTag[MODE]
if MAGNET ==  'Up':
    bkOpt = bkOpt.replace('Down','Up')
    cdOpt = cdOpt.replace('md100','mu100')

### Defines the input data
Data = LHCbDataset()
if test:
    if LocalTest:
        Data.files += [LocalFile(fpath)]
    else:
        Data.files += [DiracFile(fpath)]
else:
    Data.files += BKQuery(bkOpt).getDataset().files

### Defines the backend and the splitter of the job
if test:
    Splitter = ''
else:
    if 'MC' in MODE:
        filesPerJob = 10
    else:
        filesPerJob = 50
    Splitter = SplitByFiles(filesPerJob = filesPerJob, maxFiles = -1, ignoremissing = True)

if LocalTest:
    Backend = Local()
else:
    Backend = Dirac()

### Job name
JobName = 'Ksmumu_' + MODE
if 'data' in MODE:
    if not STRIPSEL:
        print 'WARNING: < STRIPSEL > option has been set to True: data sample as an input'
        STRIPSEL = True

if STRIPSEL:
    JobName += '_Stripped'
JobName += '_Magnet' + MAGNET

if MCMATCH:
    if 'MC' in MODE:
        JobName += '_mcMatch'
    else:
        print 'WARNING: < MCMATCH > option not allowed for a non-MC sample; set to False'
        MCMATCH = False

### Output file name
filename = JobName + '.root'

### Defines the extra options for the application (DO NOT CHANGE THE ORDER)
Simulation = ( 'MC' in MODE )
extraopts = ''
if MCMATCH:
    extraopts += 'MODE = "' + MODE + '_mcMatch' + '"\n'
else:
    extraopts += 'MODE = "' + MODE + '"\n'
extraopts += 'SIMULATION = ' + str(Simulation) + '\n'
extraopts += 'STRIPSEL = ' + str(STRIPSEL) + '\n'
extraopts += 'from Configurables import CondDB\n'
if Simulation:
    extraopts += 'DaVinci().DDDBtag = "' + dddbTag[MODE] + '"\n'
    extraopts += 'DaVinci().CondDBtag = "' + cdOpt + '"\n'
else:
    # This didn't work these days, so they are specified manually.
    #extraopts += 'CondDB().UseLatestTags = ["2012"]\n'
    extraopts += 'DaVinci().DDDBtag = "dddb-20150928"\n'
    extraopts += 'DaVinci().CondDBtag = "cond-20150409-1"\n'    

extraopts += 'DaVinci().TupleFile = "' + filename + '"\n'
extraopts += 'DaVinci().InputType = "DST"\n'
extraopts += 'DaVinci().Simulation = SIMULATION\n'
extraopts += 'DaVinci().Lumi = not SIMULATION\n'
extraopts += 'DaVinci().EvtMax = -1\n'
extraopts += 'DaVinci().PrintFreq = 3000\n'
extraopts += 'DaVinci().DataType = "2012"\n'
extraopts += 'DaVinci().SkipEvents = 0\n'
extraopts += 'configure()'

Application.extraopts = extraopts

print '#######################################################'
print 'These are the extra options passed to the DaVinci code:'
print extraopts
print '#######################################################'

#########################################################   
### Sandbox (output files)
Outputfiles = [filename]

#########################################################
### Creates and submits the job
j = Job (
    name           = JobName,
    application    = Application,
    splitter       = Splitter,
    inputfiles     = Inputfiles,
    outputfiles    = Outputfiles,
    backend        = Backend,
    inputdata      = Data
    )
j.application.prepare()
j.submit()
