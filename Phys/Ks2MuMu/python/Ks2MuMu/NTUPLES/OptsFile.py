####################################################################
# Code to generate the Ks -> mumu, Ks -> pi+ pi- and MB samples for
# the Ks -> mu+ mu- analysis.
# 
# @author: Miguel Ramos Pernas
#

import cppyy
cppyy.gbl.gSystem.Load('libLHCbKernelDict.so')

from Gaudi.Configuration import *
from PhysSelPython.Wrappers import ( Selection, AutomaticData, MergedSelection,
                                     SelectionSequence, DataOnDemand )
from Configurables import ( DaVinci,
                            LoKi__Hybrid__TupleTool,
                            LoKi__Hybrid__EvtTupleTool,
                            ReadHltReport, TrackMasterFitter )
from StandardParticles import ( StdLooseMuons,
                                StdNoPIDsMuons, StdNoPIDsPions,
                                StdAllNoPIDsMuons, StdAllNoPIDsPions )
from Configurables import DecayTreeTuple
from DecayTreeTuple.Configuration import *

#--------------------------------------------------------
# These are global variables used in the script
#MODE       = 'MCKsmumu_mcMatch'
#SIMULATION = True
#BKG        = True
#STRIPSEL   = False
#--------------------------------------------------------

# Function to add the < ^ > symbol to the particles names
def addHat( name, ptcle ):
    return name.replace( ptcle, '^' + ptcle )

# Configures the tuples to book the MCmatch info
def configureMCmatch():
    from Configurables import MCDecayTreeTuple
    if BKG:
        tupleGen = MCDecayTreeTuple( 'MCtruthKspipi' )
        tupleGen.Decay = 'KS0 => ^pi+ ^pi-'
    else:
        tupleGen = MCDecayTreeTuple( 'MCtruthKsmumu' )
        tupleGen.Decay = 'KS0 => ^mu+ ^mu-'
    tupleGen.ToolList = [ 'MCTupleToolKinematic',
                          'MCTupleToolPrompt',
                          'MCTupleToolHierarchy',
                          'MCTupleToolPID' ]
    mcrec = tupleGen.addTupleTool('MCTupleToolReconstructed')
    mcrec.Associate = False
    mcrec.FillPID   = False
    return [tupleGen]

# Adds the mcMatch cut, only if required
def configureTuple():

    from Configurables import GaudiSequencer
    gaudiSeq = GaudiSequencer('Ana' + MODE + 'Seq')

    # Here the name of the particles (and so the mass) are defined, as well as the
    # background condition
    if 'mumu' in MODE:
        Ptcle      = 'mu'
        if SIMULATION:
            inputPtcls = StdLooseMuons
        stripLine  = 'KS02MuMuLine'
    else:
        Ptcle      = 'pi'
        if SIMULATION:
            inputPtcls = StdNoPIDsPions
        if 'MB' in MODE:
            stripLine = 'MBNoBias'
        else:
            stripLine = 'KS02MuMuNoMuIDLine'
    Ptcle_P = Ptcle + '+'
    Ptcle_M = Ptcle + '-'

    # Decay descriptor, constructed from the input particles
    decayDesc = 'KS0 -> ' + Ptcle_P + ' ' + Ptcle_M

    # Defines the name of the folder to store the tree
    if 'mumu' in MODE:
        tupleName = 'Ksmumu'
    elif 'pipi' in MODE:
        tupleName = 'Kspipi'
    else:
        tupleName = 'KsMB'
    tupleName += 'Tuple'

    KsmumuTuple = DecayTreeTuple(tupleName)
    KsmumuTuple.Decay = addHat( decayDesc, Ptcle )

    # Defines the names of the branches for each particle
    KsmumuTuple.addBranches  ({
            'KS0'    : '^(' + decayDesc + ')',
            'muplus' : addHat( decayDesc, Ptcle_P ),
            'muminus': addHat( decayDesc, Ptcle_M )
            })

    KsmumuTuple.ToolList = [ 'TupleToolKinematic',
                             'TupleToolPid',
                             'TupleToolANNPID',
                             'TupleToolGeometry' ]

    # Cuts to be performed together with the stripping
    from Configurables import CombineParticles
    KsCombPart = CombineParticles('KsCombPart', DecayDescriptor = decayDesc)
    
    if 'mcMatch' in MODE:
        KsCombPart.Preambulo = [ 'from LoKiPhysMC.decorators import *',
                                 'from LoKiPhysMC.functions import mcMatch' ]
        dc = {}
        for ptcle in ( Ptcle_P, Ptcle_M ):
            dc[ ptcle ] = 'mcMatch("' + ptcle + '")'
        KsCombPart.DaughtersCuts = dc
        KsCombPart.MotherCut = "mcMatch('" + decayDesc.replace('->','=>') + "')"
        KsCombPart.ReFitPVs  = False
    else:
        # This is a copy of the KS02MuMuNoMuID line without prescales
        if 'MB' in MODE:
            KsCombPart.DaughtersCuts = { Ptcle_P : "(MIPCHI2DV(PRIMARY)> 100.)&(TRCHI2DOF < 5 ) & (PT > 0 * MeV )",
                                         Ptcle_M : "(MIPCHI2DV(PRIMARY)> 100.)&(TRCHI2DOF < 5 ) & (PT > 0 * MeV )" }
            KsCombPart.CombinationCut = "(ADAMASS('KS0')<100*MeV) & (AMAXDOCA('')<0.3*mm)"
            KsCombPart.MotherCut = "((BPVDIRA>0) & ((BPVVDSIGN*M/P) > 0.1*89.53*2.9979e-01) & (MIPDV(PRIMARY)<0.4*mm) & (M>400) & (M<600) & (PT > 0 * MeV))"
        else:
            # Some non-effect cuts
            KsCombPart.DaughtersCuts = { Ptcle_P: 'PT > 0',
                                         Ptcle_M: 'PT > 0' }
            KsCombPart.MotherCut = 'PT > 0'

    # Definition of the stripping requirements
    if SIMULATION:
        from Configurables import TupleToolParticleStripped
        particleStripped = TupleToolParticleStripped('IsReallyStripped')
        particleStripped.StrippingLocation = '/Event/AllStreams/Phys/KS02MuMuNoMuIDLine/Particles'
        particleStripped.StrippingName = 'REALLY_'
        
        particleStrippedMM = TupleToolParticleStripped('IsReallyStrippedMM')
        particleStrippedMM.StrippingLocation = '/Event/AllStreams/Phys/KS02MuMuLine/Particles'
        particleStrippedMM.StrippingName = 'REALLY_MM_'
        
        KsmumuTuple.ToolList += ['TupleToolParticleStripped/IsReallyStripped']
        KsmumuTuple.addTool(particleStripped)
        
        KsmumuTuple.ToolList += ['TupleToolParticleStripped/IsReallyStrippedMM']
        KsmumuTuple.addTool(particleStrippedMM)
        
        KsmumuTuple.addTupleTool('LoKi::Hybrid::EvtTupleTool/IsStripped')
        KsmumuTuple.addTupleTool('LoKi::Hybrid::EvtTupleTool/IsStrippedMuMu')
        KsmumuTuple.IsStripped.VOID_Variables = {'ISSTRIPPED': "CONTAINS ('/Event/AllStreams/Phys/KS02MuMuNoMuIDLine/Particles')"}
        KsmumuTuple.IsStrippedMuMu.VOID_Variables = {'ISSTRIPPED_MUMU': "CONTAINS ('/Event/AllStreams/Phys/KS02MuMuLine/Particles')"}

        requiredSel = [inputPtcls]
        stream = 'AllStreams'
    else:
        if 'MB' in MODE:
            stream   = 'MinBias'
        else:
            stream   = 'Dimuon'
        
        stripSel = "HLT_PASS('Stripping" + stripLine + "Decision')"
        
        if STRIPSEL:
            # If the stripping is being applied, the output is set as an input to the CombineParticles class
            from Configurables import LoKi__HDRFilter as StripFilter
            sf = StripFilter( 'StripPassFilter' + MODE,
                              Code = stripSel,
                              Location = '/Event/Strip/Phys/DecReports' )
            # If it is the MB sample the output is taken from the CombineParticles class
            if 'MB' in MODE:
                requiredSel = [inputPtcls]
            else:
                requiredSel = False
            gaudiSeq.Members += [sf]
    
    if requiredSel:
        # Only the events with at least one primary vertex are being taken
        from Configurables import LoKi__VoidFilter
        vf = LoKi__VoidFilter( 'AtLeastOnePV', Code = "CONTAINS('Rec/Vertex/Primary')>0" )
        KsSel = Selection('KsSel', Algorithm = KsCombPart, RequiredSelections = requiredSel)
        KsSelSeq = SelectionSequence('KsSelSeq', TopSelection = KsSel, EventPreSelector = [vf] )
        KsmumuTuple.Inputs = [KsSelSeq.outputLocation()]
        gaudiSeq.Members += [KsSelSeq.sequence()]
    else:
        KsmumuTuple.Inputs = [AutomaticData('/Event/' + stream + '/Phys/' + stripLine + '/Particles').outputLocation()]
    
    # Adds the MCtruth information in a new tree if it is a MC sample
    if SIMULATION:

        KsmumuTuple.addTupleTool('TupleToolMCBackgroundInfo')
        mctt = KsmumuTuple.addTupleTool('TupleToolMCTruth')
        mctt.ToolList = ['MCTupleToolKinematic',
                         'MCTupleToolHierarchy',
                         'MCTupleToolReconstructed']
        mcdif = KsmumuTuple.addTupleTool('TupleToolMCDecayInFlight')
        mcdif.OutputLevel = 4

    # Adds the TupleTools
    LoKi_Kaon = KsmumuTuple.KS0.addTupleTool('LoKi::Hybrid::TupleTool/LoKi_Kaon')
    LoKi_Kaon.Variables= {
        'DOCA'        : "PFUNA(AMAXDOCA('LoKi::DistanceCalculator',False))" ,
        'DOCA_LOKI'   : "LoKi.Particles.PFunA(AMAXDOCA('LoKi::TrgDistanceCalculator',False))",
        'DOCA_NEW'    : "DOCAMAX",
        'DOCACHI2_NEW': "DOCACHI2MAX",
        'ADAMASS'     : "ADMASS('KS0')",
        'AMAXDOCA'    : "PFUNA(AMAXDOCA(''))",
        'LV0'         : "LV0(1)"
        }

    from Configurables import TupleToolEventInfo
    EventInfo = KsmumuTuple.addTupleTool('TupleToolEventInfo')
    EventInfo.Verbose = True
    from Configurables import TupleToolRecoStats
    RecoTT = KsmumuTuple.addTupleTool('TupleToolRecoStats')
    RecoTT.Verbose = True
    from Configurables import TupleToolPropertime
    PropTimeTT = KsmumuTuple.addTupleTool('TupleToolPropertime')
    from Configurables import TupleToolTrackInfo
    TrackInfoTT = KsmumuTuple.addTupleTool('TupleToolTrackInfo')
    TrackInfoTT.Verbose = True
    from Configurables import TupleToolAngles
    AngleTT = KsmumuTuple.addTupleTool('TupleToolAngles')
    AngleTT.Verbose = True

    KsmumuTuple.addTupleTool('TupleToolVeloHits') 
    KsmumuTuple.addTupleTool('TupleToolMatterVeto')
    KsmumuTuple.addTupleTool('TupleToolMuonPid')
    KsmumuTuple.addTupleTool('TupleToolIsolationTwoBody')
    KsmumuTuple.addTupleTool('TupleToolVtxIsoln')

    muidPlus = KsmumuTuple.addTupleTool('TupleToolMuonPidPlus')
    muidPlus.addTool(TrackMasterFitter())
    muidPlus.OutputLevel = 4
    muidPlus.TrackMasterFitter.ErrorQoP = [ 0 , 1e-9 ]
    muidPlus.TrackMasterFitter.OutputLevel = 4
    muidPlus.Verbose   = False
    muidPlus.RunOnGrid = True

    from Configurables import TupleToolStripping
    tts = KsmumuTuple.addTupleTool('TupleToolStripping')
    tts.StrippingList = ['StrippingKS02MuMuLineDecision', 'StrippingKS02MuMuNoMuIDLineDecision']
    
    # Definition of the trigger lines
    from Configurables import TupleToolTISTOS
    TisTosTT = KsmumuTuple.addTupleTool('TupleToolTISTOS')
    TisTosTT.VerboseL0   = True
    TisTosTT.VerboseHlt1 = True
    TisTosTT.VerboseHlt2 = True
    TisTosTT.TriggerList = ([
            'L0HadronDecision'
            , 'L0ElectronDecision'
            , 'L0PhotonDecision'
            , 'L0MuonDecision'
            , 'L0DiMuonDecision'
            , 'Hlt1DiMuonHighMassDecision'
            , 'Hlt1DiMuonLowMassDecision'
            , 'Hlt1DiProtonDecision'
            , 'Hlt1DiProtonLowMultDecision'
            , 'Hlt1SingleElectronNoIPDecision'
            , 'Hlt1SingleMuonHighPTDecision'
            , 'Hlt1SingleMuonNoIPDecision'
            , 'Hlt1TrackAllL0Decision'
            , 'Hlt1TrackAllL0TightDecision'
            , 'Hlt1TrackMuonDecision'
            , 'Hlt1TrackPhotonDecision'
            , 'Hlt1VertexDisplVertexDecision'
            , 'Hlt2SingleMuonDecision'
            , 'Hlt2SingleMuonHighPTDecision'
            , 'Hlt2SingleMuonLowPTDecision'
            , 'Hlt2DiMuonDetachedDecision'
            , 'Hlt2CharmSemilepcD02KMuNuWSDecision'
            , 'Hlt2CharmSemilepcD02PiMuNuWSDecision'
            , 'Hlt2CharmSemilepcD02HMuNu_D02KMuNuWSDecision'
            , 'Hlt2CharmSemilepcD02HMuNu_D02PiMuNUWSDecision'
            , 'Hlt2CharmSemilepcD02HMuNu_D02KMuNuDecision'
            , 'Hlt2CharmSemilepcD02HMuNu_D02KMuNuThightDecision'
            , 'Hlt2CharmSemilepcD02HMuNu_D02PiMuNuDecision'
            , 'Hlt2DisplVerticesSingleLoosePSDecision'
            , 'Hlt2CharmHadD02HHKsLLDecision'
            , 'Hlt2CharmHadD2KS0H_D2KS0DDKDecision'
            , 'Hlt2CharmHadD2KS0H_D2KS0DDPiDecision'
            , 'Hlt2CharmHadD2KS0H_D2KS0KDecision'
            , 'Hlt2CharmHadD2KS0H_D2KS0PiDecision'
            ])

    from Configurables import TupleToolTrigger
    ttt = KsmumuTuple.addTupleTool('TupleToolTrigger')
    ttt.Verbose = True
    gaudiSeq.Members += [KsmumuTuple]
    
    return [gaudiSeq]
    
# Function to be called by the ganga script
def configure():
    global BKG
    if 'mumu' in MODE:
        BKG = False
    else:
        BKG = True
    DaVinci().UserAlgorithms += configureTuple()
    if SIMULATION and 'mcMatch' in MODE:
        DaVinci().UserAlgorithms += configureMCmatch()


#----------------------------------------------------------------
# To run it completely on local

RUNLOCAL = False
if RUNLOCAL:
    #MODE = 'dataKsmumu'
    #MODE = 'dataKspipi'
    MODE = 'dataMB'
    #MODE = 'MCKspipi_mcMatch'
    #MODE = 'MCKspipiLDST_mcMatch'
    #MODE = 'MCMB08a_mcMatch'
    
    # Be careful changing these numbers, since not all the dst files are on EOS
    dstfiles = {
        'dataKsmumu'           : ['/lhcb/LHCb/Collision12/DIMUON.DST/00041836/0000/%s' % line[:-1] for line in open('datacards.txt')],
        'dataKspipi'           : ['/lhcb/LHCb/Collision12/DIMUON.DST/00041836/0000/%s' % line[:-1] for line in open('datacards.txt')],
        'dataMB'               : ['/lhcb/LHCb/Collision12/MINIBIAS.DST/00041836/0000/%s' % line[:-1] for line in open('dataMBcards.txt')],
        'MCKspipi_mcMatch'     : ['/lhcb/MC/2012/ALLSTREAMS.DST/00031736/0000/00031736_0000000%i_1.allstreams.dst' % tpid for tpid in xrange( 1, 2 )],#6
        'MCKspipiLDST_mcMatch' : ['/lhcb/MC/2012/KSMM.STRIP.DST/00047101/0000/00047101_000000%i_1.ksmm.strip.dst' % tpid for tpid in xrange( 21, 22 )],#26
        'MCMB08a_mcMatch'      : ['/lhcb/MC/2012/ALLSTREAMS.DST/00026814/0000/00026814_0000000%i_1.allstreams.dst' % tpid for tpid in xrange( 1, 2 )]#6
        }

    DaVinci().Input = [ 'PFN:root://eoslhcb.cern.ch//eos/lhcb/grid/prod' + ifile for ifile in dstfiles[ MODE ] ]

    SIMULATION = ( 'MC' in MODE )
    STRIPSEL   = ( 'data' in MODE )

    from Configurables import CondDB
    if 'data' in MODE:
        DaVinci().DDDBtag = 'dddb-20150928'
        DaVinci().CondDBtag = 'cond-20150409-1'
    elif 'MC' in MODE and 'MB08a' in MODE:
        DaVinci().DDDBtag = 'Sim08-20130503-1'
        DaVinci().CondDBtag = 'Sim08-20130503-1-vc-md100'
    elif 'LDST' in MODE:
        DaVinci().DDDBtag = 'dddb-20150703'
        DaVinci().CondDBtag = 'sim-20150703-vc-md100'
    else:
        DaVinci().DDDBtag = 'dddb-20130929-1'
        DaVinci().CondDBtag = 'sim-20130522-1-vc-md100'

    DaVinci().TupleFile = 'Ksmumu_' + MODE + '_MagnetDown_mcMatch.root'
    DaVinci().InputType = 'DST'
    DaVinci().Simulation = SIMULATION
    DaVinci().Lumi = not SIMULATION
    DaVinci().PrintFreq = 3000
    DaVinci().EvtMax = -1
    DaVinci().DataType = "2012"
    DaVinci().SkipEvents = 0
    configure()
    
    import GaudiPython
    gaudi = GaudiPython.AppMgr( outputlevel = 3 )
    gaudi.initialize()
    gaudi.run( int(2e4) )
    gaudi.stop()
    gaudi.finalize()
#----------------------------------------------------------------

#EOF
