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
        Ptcle = 'mu'
        if SIMULATION:
            if STRIPSEL:
                inputPtcls = StdLooseMuons
            else:
                inputPtcls = StdAllNoPIDsMuons
        stripLine  = 'KS02MuMuLine'
    else:
        Ptcle = 'pi'
        if SIMULATION or 'MB' in MODE:
            if STRIPSEL:
                inputPtcls = StdNoPIDsPions
            else:
                inputPtcls = StdAllNoPIDsPions
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
    KsCombPart.ReFitPVs  = False
    
    dc = {}
    cc = False

    if 'mcMatch' in MODE:
        KsCombPart.Preambulo = [ 'from LoKiPhysMC.decorators import *',
                                 'from LoKiPhysMC.functions import mcMatch' ]
        for ptcle in ( Ptcle_P, Ptcle_M ):
            dc[ ptcle ] = 'mcMatch("' + ptcle + '")'
        mc = "mcMatch('" + decayDesc.replace('->','=>') + "')"
    else:
        dc = { Ptcle_P: '(PT > 0)', Ptcle_M: '(PT > 0)' }
        mc = '(PT > 0)'
        
    # This is a copy of the KS02MuMuNoMuID line without prescales
    if 'MB' in MODE and STRIPSEL:
        for d in dc:
            dc[d] += " & (MIPCHI2DV(PRIMARY)> 100.)&(TRCHI2DOF < 5 ) & (PT > 0 * MeV )"
        cc  = "(ADAMASS('KS0')<100*MeV) & (AMAXDOCA('')<0.3*mm)"
        mc += " & ((BPVDIRA>0) & ((BPVVDSIGN*M/P) > 0.1*89.53*2.9979e-01) & (MIPDV(PRIMARY)<0.4*mm)"\
            " & (M>400) & (M<600) & (PT > 0 * MeV))"
    
    # Set the cuts
    KsCombPart.DaughtersCuts = dc
    KsCombPart.MotherCut     = mc
    if cc:
        KsCombPart.CombinationCut = cc

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

    # Extra trigger definitions for MB check
    if 'MB' in MODE:
        KsmumuTuple.addTupleTool('LoKi::Hybrid::EvtTupleTool/HltVariables')
        KsmumuTuple.HltVariables.HLT_Variables = {
            "Hlt1PhysAlt1": "switch(HLT_PASS_RE('Hlt1(?!ODIN)(?!L0)(?!Lumi)(?!Tell1)(?!MB)(?!NZS)(?!Velo)(?!BeamGas)(?!Incident)(?!CharmCalibration).*Decision'), 1, 0)",
            "Hlt1PhysAlt2": "switch(HLT_PASS_RE('Hlt1(?!ODIN)(?!L0)(?!Lumi)(?!Tell1)(?!MB)(?!NZS)(?!Velo)(?!BeamGas)(?!Incident).*Decision & Hlt1.*(?!Calibration)(?!NoBias).*Decision'), 1, 0)"
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
    '''
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
            
            # To test the MB
            , 'Hlt1CharmCalibrationNoBiasDecision'
            ])
            '''
    TisTosTT.TriggerList = [ 'Hlt1BeamGasBeam1Decision'
                             ,'Hlt1BeamGasBeam2Decision'
                             ,'Hlt1BeamGasCrossingEnhancedBeam1Decision'
                             ,'Hlt1BeamGasCrossingEnhancedBeam2Decision'
                             ,'Hlt1BeamGasCrossingForcedRecoDecision'
                             ,'Hlt1BeamGasCrossingForcedRecoFullZDecision'
                             ,'Hlt1BeamGasCrossingParasiticDecision'
                             ,'Hlt1BeamGasHighRhoVerticesDecision'
                             ,'Hlt1BeamGasNoBeamBeam1Decision'
                             ,'Hlt1BeamGasNoBeamBeam2Decision'
                             ,'Hlt1CharmCalibrationNoBiasDecision'
                             ,'Hlt1CharmCalibrationNoBiasDecision'
                             ,'Hlt1DiMuonHighMassDecision'
                             ,'Hlt1DiMuonHighMassDecision'
                             ,'Hlt1DiMuonLowMassDecision'
                             ,'Hlt1DiMuonLowMassDecision'
                             ,'Hlt1DiProtonDecision'
                             ,'Hlt1DiProtonDecision'
                             ,'Hlt1DiProtonLowMultDecision'
                             ,'Hlt1DiProtonLowMultDecision'
                             ,'Hlt1ErrorEventDecision'
                             ,'Hlt1GlobalDecision'
                             ,'Hlt1L0AnyDecision'
                             ,'Hlt1L0AnyNoSPDDecision'
                             ,'Hlt1L0AnyNoSPDRateLimitedDecision'
                             ,'Hlt1L0AnyRateLimitedDecision'
                             ,'Hlt1L0HighSumETJetDecision'
                             ,'Hlt1LumiDecision'
                             ,'Hlt1LumiMidBeamCrossingDecision'
                             ,'Hlt1MBMicroBiasTStationDecision'
                             ,'Hlt1MBMicroBiasTStationRateLimitedDecision'
                             ,'Hlt1MBMicroBiasVeloDecision'
                             ,'Hlt1MBMicroBiasVeloRateLimitedDecision'
                             ,'Hlt1MBNoBiasDecision'
                             ,'Hlt1NoPVPassThroughDecision'
                             ,'Hlt1ODINTechnicalDecision'
                             ,'Hlt1SingleElectronNoIPDecision'
                             ,'Hlt1SingleElectronNoIPDecision'
                             ,'Hlt1SingleMuonHighPTDecision'
                             ,'Hlt1SingleMuonHighPTDecision'
                             ,'Hlt1SingleMuonNoIPDecision'
                             ,'Hlt1SingleMuonNoIPDecision'
                             ,'Hlt1Tell1ErrorDecision'
                             ,'Hlt1TrackAllL0Decision'
                             ,'Hlt1TrackAllL0Decision'
                             ,'Hlt1TrackAllL0TightDecision'
                             ,'Hlt1TrackAllL0TightDecision'
                             ,'Hlt1TrackForwardPassThroughDecision'
                             ,'Hlt1TrackForwardPassThroughLooseDecision'
                             ,'Hlt1TrackMuonDecision'
                             ,'Hlt1TrackMuonDecision'
                             ,'Hlt1TrackPhotonDecision'
                             ,'Hlt1TrackPhotonDecision'
                             ,'Hlt1VeloClosingMicroBiasDecision'
                             ,'Hlt1VertexDisplVertexDecision'
                             ,'Hlt1VertexDisplVertexDecision'
                             ,'Hlt2B2HHDecision'
                             ,'Hlt2B2HHLTUnbiasedDecision'
                             ,'Hlt2B2HHLTUnbiasedDetachedDecision'
                             ,'Hlt2B2HHPi0_MergedDecision'
                             ,'Hlt2Bd2KstGammaDecision'
                             ,'Hlt2Bd2KstGammaWideBMassDecision'
                             ,'Hlt2Bd2KstGammaWideKMassDecision'
                             ,'Hlt2Bs2PhiGammaDecision'
                             ,'Hlt2Bs2PhiGammaWideBMassDecision'
                             ,'Hlt2CharmHadD02HHHHDecision'
                             ,'Hlt2CharmHadD02HHHHDst_2K2piDecision'
                             ,'Hlt2CharmHadD02HHHHDst_2K2piWideMassDecision'
                             ,'Hlt2CharmHadD02HHHHDst_3KpiDecision'
                             ,'Hlt2CharmHadD02HHHHDst_3KpiWideMassDecision'
                             ,'Hlt2CharmHadD02HHHHDst_4piDecision'
                             ,'Hlt2CharmHadD02HHHHDst_4piWideMassDecision'
                             ,'Hlt2CharmHadD02HHHHDst_K3piDecision'
                             ,'Hlt2CharmHadD02HHHHDst_K3piWideMassDecision'
                             ,'Hlt2CharmHadD02HHHHDst_KKpipiDecision'
                             ,'Hlt2CharmHadD02HHHHDst_KKpipiWideMassDecision'
                             ,'Hlt2CharmHadD02HHHHWideMassDecision'
                             ,'Hlt2CharmHadD02HHHH_2K2piDecision'
                             ,'Hlt2CharmHadD02HHHH_2K2piWideMassDecision'
                             ,'Hlt2CharmHadD02HHHH_3KpiDecision'
                             ,'Hlt2CharmHadD02HHHH_3KpiWideMassDecision'
                             ,'Hlt2CharmHadD02HHHH_4piDecision'
                             ,'Hlt2CharmHadD02HHHH_4piWideMassDecision'
                             ,'Hlt2CharmHadD02HHHH_K3piDecision'
                             ,'Hlt2CharmHadD02HHHH_K3piWideMassDecision'
                             ,'Hlt2CharmHadD02HHHH_KKpipiDecision'
                             ,'Hlt2CharmHadD02HHHH_KKpipiWideMassDecision'
                             ,'Hlt2CharmHadD02HHKsDDDecision'
                             ,'Hlt2CharmHadD02HHKsLLDecision'
                             ,'Hlt2CharmHadD02HHKsLLDecision'
                             ,'Hlt2CharmHadD02HHXDst_hhXDecision'
                             ,'Hlt2CharmHadD02HHXDst_hhXWideMassDecision'
                             ,'Hlt2CharmHadD02HH_D02KKDecision'
                             ,'Hlt2CharmHadD02HH_D02KKWideMassDecision'
                             ,'Hlt2CharmHadD02HH_D02KPiDecision'
                             ,'Hlt2CharmHadD02HH_D02KPiWideMassDecision'
                             ,'Hlt2CharmHadD02HH_D02PiPiDecision'
                             ,'Hlt2CharmHadD02HH_D02PiPiWideMassDecision'
                             ,'Hlt2CharmHadD2HHHDecision'
                             ,'Hlt2CharmHadD2HHHWideMassDecision'
                             ,'Hlt2CharmHadD2KS0H_D2KS0DDKDecision'
                             ,'Hlt2CharmHadD2KS0H_D2KS0DDKDecision'
                             ,'Hlt2CharmHadD2KS0H_D2KS0DDPiDecision'
                             ,'Hlt2CharmHadD2KS0H_D2KS0DDPiDecision'
                             ,'Hlt2CharmHadD2KS0H_D2KS0KDecision'
                             ,'Hlt2CharmHadD2KS0H_D2KS0KDecision'
                             ,'Hlt2CharmHadD2KS0H_D2KS0PiDecision'
                             ,'Hlt2CharmHadD2KS0H_D2KS0PiDecision'
                             ,'Hlt2CharmHadD2KS0KS0Decision'
                             ,'Hlt2CharmHadD2KS0KS0WideMassDecision'
                             ,'Hlt2CharmHadLambdaC2KPKDecision'
                             ,'Hlt2CharmHadLambdaC2KPKWideMassDecision'
                             ,'Hlt2CharmHadLambdaC2KPPiDecision'
                             ,'Hlt2CharmHadLambdaC2KPPiWideMassDecision'
                             ,'Hlt2CharmHadLambdaC2PiPKDecision'
                             ,'Hlt2CharmHadLambdaC2PiPKWideMassDecision'
                             ,'Hlt2CharmHadLambdaC2PiPPiDecision'
                             ,'Hlt2CharmHadLambdaC2PiPPiWideMassDecision'
                             ,'Hlt2CharmHadMinBiasD02KKDecision'
                             ,'Hlt2CharmHadMinBiasD02KPiDecision'
                             ,'Hlt2CharmHadMinBiasDplus2hhhDecision'
                             ,'Hlt2CharmHadMinBiasLambdaC2KPPiDecision'
                             ,'Hlt2CharmHadMinBiasLambdaC2LambdaPiDecision'
                             ,'Hlt2CharmRareDecayD02MuMuDecision'
                             ,'Hlt2CharmSemilep3bodyD2KMuMuDecision'
                             ,'Hlt2CharmSemilep3bodyD2KMuMuSSDecision'
                             ,'Hlt2CharmSemilep3bodyD2PiMuMuDecision'
                             ,'Hlt2CharmSemilep3bodyD2PiMuMuSSDecision'
                             ,'Hlt2CharmSemilep3bodyLambdac2PMuMuDecision'
                             ,'Hlt2CharmSemilep3bodyLambdac2PMuMuSSDecision'
                             ,'Hlt2CharmSemilepD02HHMuMuDecision'
                             ,'Hlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsDecision'
                             ,'Hlt2CharmSemilepD02HHMuMuHardHadronsAndMuonsWideMassDecision'
                             ,'Hlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsDecision'
                             ,'Hlt2CharmSemilepD02HHMuMuHardHadronsSoftMuonsWideMassDecision'
                             ,'Hlt2CharmSemilepD02HHMuMuWideMassDecision'
                             ,'Hlt2CharmSemilepD02HMuNu_D02KMuNuDecision'
                             ,'Hlt2CharmSemilepD02HMuNu_D02KMuNuTightDecision'
                             ,'Hlt2CharmSemilepD02HMuNu_D02KMuNuWSDecision'
                             ,'Hlt2CharmSemilepD02HMuNu_D02PiMuNuDecision'
                             ,'Hlt2CharmSemilepD02HMuNu_D02PiMuNuWSDecision'
                             ,'Hlt2CharmSemilepD02KKMuMuDecision'
                             ,'Hlt2CharmSemilepD02KPiMuMuDecision'
                             ,'Hlt2CharmSemilepD02PiPiMuMuDecision'
                             ,'Hlt2CharmSemilepD2HMuMuDecision'
                             ,'Hlt2CharmSemilepD2HMuMuWideMassDecision'
                             ,'Hlt2CharmSemilepcD02HMuNu_D02KMuNuDecision'
                             ,'Hlt2CharmSemilepcD02HMuNu_D02KMuNuThightDecision'
                             ,'Hlt2CharmSemilepcD02HMuNu_D02KMuNuWSDecision'
                             ,'Hlt2CharmSemilepcD02HMuNu_D02PiMuNUWSDecision'
                             ,'Hlt2CharmSemilepcD02HMuNu_D02PiMuNuDecision'
                             ,'Hlt2CharmSemilepcD02KMuNuWSDecision'
                             ,'Hlt2CharmSemilepcD02PiMuNuWSDecision'
                             ,'Hlt2DebugEventDecision'
                             ,'Hlt2DiElectronBDecision'
                             ,'Hlt2DiElectronHighMassDecision'
                             ,'Hlt2DiMuonAndD0Decision'
                             ,'Hlt2DiMuonAndDpDecision'
                             ,'Hlt2DiMuonAndDsDecision'
                             ,'Hlt2DiMuonAndGammaDecision'
                             ,'Hlt2DiMuonAndLcDecision'
                             ,'Hlt2DiMuonAndMuonDecision'
                             ,'Hlt2DiMuonBDecision'
                             ,'Hlt2DiMuonDY1Decision'
                             ,'Hlt2DiMuonDY2Decision'
                             ,'Hlt2DiMuonDY3Decision'
                             ,'Hlt2DiMuonDY4Decision'
                             ,'Hlt2DiMuonDecision'
                             ,'Hlt2DiMuonDetachedDecision'
                             ,'Hlt2DiMuonDetachedDecision'
                             ,'Hlt2DiMuonDetachedHeavyDecision'
                             ,'Hlt2DiMuonDetachedJPsiDecision'
                             ,'Hlt2DiMuonDetachedPsi2SDecision'
                             ,'Hlt2DiMuonJPsiDecision'
                             ,'Hlt2DiMuonJPsiHighPTDecision'
                             ,'Hlt2DiMuonLowMassDecision'
                             ,'Hlt2DiMuonPsi2SDecision'
                             ,'Hlt2DiMuonPsi2SHighPTDecision'
                             ,'Hlt2DiMuonZDecision'
                             ,'Hlt2DiPhiDecision'
                             ,'Hlt2DiProtonDecision'
                             ,'Hlt2DiProtonLowMultDecision'
                             ,'Hlt2DiProtonLowMultTFDecision'
                             ,'Hlt2DiProtonTFDecision'
                             ,'Hlt2DisplVerticesDoubleDecision'
                             ,'Hlt2DisplVerticesDoublePSDecision'
                             ,'Hlt2DisplVerticesDoublePostScaledDecision'
                             ,'Hlt2DisplVerticesHighFDSingleDecision'
                             ,'Hlt2DisplVerticesHighMassSingleDecision'
                             ,'Hlt2DisplVerticesLowMassSingleDecision'
                             ,'Hlt2DisplVerticesSingleDecision'
                             ,'Hlt2DisplVerticesSingleDownDecision'
                             ,'Hlt2DisplVerticesSingleHighFDDecision'
                             ,'Hlt2DisplVerticesSingleHighFDPostScaledDecision'
                             ,'Hlt2DisplVerticesSingleHighMassDecision'
                             ,'Hlt2DisplVerticesSingleHighMassPostScaledDecision'
                             ,'Hlt2DisplVerticesSingleLoosePSDecision'
                             ,'Hlt2DisplVerticesSingleLoosePSDecision'
                             ,'Hlt2DisplVerticesSingleMVPostScaledDecision'
                             ,'Hlt2DisplVerticesSinglePSDecision'
                             ,'Hlt2DisplVerticesSinglePostScaledDecision'
                             ,'Hlt2DisplVerticesSingleVeryHighFDDecision'
                             ,'Hlt2DoubleDiMuonDecision'
                             ,'Hlt2Dst2PiD02KMuDecision'
                             ,'Hlt2Dst2PiD02KPiDecision'
                             ,'Hlt2Dst2PiD02MuMuDecision'
                             ,'Hlt2Dst2PiD02PiPiDecision'
                             ,'Hlt2ErrorEventDecision'
                             ,'Hlt2ExpressBeamHaloDecision'
                             ,'Hlt2ExpressD02KPiDecision'
                             ,'Hlt2ExpressDStar2D0PiDecision'
                             ,'Hlt2ExpressDs2PhiPiDecision'
                             ,'Hlt2ExpressHLT1PhysicsDecision'
                             ,'Hlt2ExpressJPsiDecision'
                             ,'Hlt2ExpressJPsiTagProbeDecision'
                             ,'Hlt2ExpressKSDecision'
                             ,'Hlt2ExpressLambdaDecision'
                             ,'Hlt2ForwardDecision'
                             ,'Hlt2GlobalDecision'
                             ,'Hlt2IncPhiDecision'
                             ,'Hlt2IncPhiSidebandsDecision'
                             ,'Hlt2LambdaC_LambdaC2Lambda0DDKDecision'
                             ,'Hlt2LambdaC_LambdaC2Lambda0DDPiDecision'
                             ,'Hlt2LambdaC_LambdaC2Lambda0LLKDecision'
                             ,'Hlt2LambdaC_LambdaC2Lambda0LLPiDecision'
                             ,'Hlt2LowMultChiC2HHDecision'
                             ,'Hlt2LowMultChiC2HHHHDecision'
                             ,'Hlt2LowMultChiC2HHHHWSDecision'
                             ,'Hlt2LowMultChiC2HHWSDecision'
                             ,'Hlt2LowMultD2K3PiDecision'
                             ,'Hlt2LowMultD2K3PiWSDecision'
                             ,'Hlt2LowMultD2KPiDecision'
                             ,'Hlt2LowMultD2KPiPiDecision'
                             ,'Hlt2LowMultD2KPiPiWSDecision'
                             ,'Hlt2LowMultD2KPiWSDecision'
                             ,'Hlt2LowMultDDIncDecision'
                             ,'Hlt2LowMultElectronDecision'
                             ,'Hlt2LowMultElectron_nofilterDecision'
                             ,'Hlt2LowMultHadronDecision'
                             ,'Hlt2LowMultHadron_nofilterDecision'
                             ,'Hlt2LowMultMuonDecision'
                             ,'Hlt2LowMultPhotonDecision'
                             ,'Hlt2LumiDecision'
                             ,'Hlt2MuonFromHLT1Decision'
                             ,'Hlt2PassThroughDecision'
                             ,'Hlt2RadiativeTopoPhotonDecision'
                             ,'Hlt2RadiativeTopoPhotonL0Decision'
                             ,'Hlt2RadiativeTopoTrackDecision'
                             ,'Hlt2RadiativeTopoTrackTOSDecision'
                             ,'Hlt2SingleElectronTFHighPtDecision'
                             ,'Hlt2SingleElectronTFLowPtDecision'
                             ,'Hlt2SingleMuonDecision'
                             ,'Hlt2SingleMuonDecision'
                             ,'Hlt2SingleMuonHighPTDecision'
                             ,'Hlt2SingleMuonHighPTDecision'
                             ,'Hlt2SingleMuonLowPTDecision'
                             ,'Hlt2SingleMuonLowPTDecision'
                             ,'Hlt2SingleMuonVHighPTDecision'
                             ,'Hlt2SingleTFElectronDecision'
                             ,'Hlt2SingleTFVHighPtElectronDecision'
                             ,'Hlt2TFBc2JpsiMuXDecision'
                             ,'Hlt2TFBc2JpsiMuXSignalDecision'
                             ,'Hlt2Topo2BodyBBDTDecision'
                             ,'Hlt2Topo2BodySimpleDecision'
                             ,'Hlt2Topo3BodyBBDTDecision'
                             ,'Hlt2Topo3BodySimpleDecision'
                             ,'Hlt2Topo4BodyBBDTDecision'
                             ,'Hlt2Topo4BodySimpleDecision'
                             ,'Hlt2TopoE2BodyBBDTDecision'
                             ,'Hlt2TopoE3BodyBBDTDecision'
                             ,'Hlt2TopoE4BodyBBDTDecision'
                             ,'Hlt2TopoMu2BodyBBDTDecision'
                             ,'Hlt2TopoMu3BodyBBDTDecision'
                             ,'Hlt2TopoMu4BodyBBDTDecision'
                             ,'Hlt2TopoRad2BodyBBDTDecision'
                             ,'Hlt2TopoRad2plus1BodyBBDTDecision'
                             ,'Hlt2TransparentDecision'
                             ,'Hlt2TriMuonDetachedDecision'
                             ,'Hlt2TriMuonTauDecision'
                             ,'Hlt2diPhotonDiMuonDecision'
                             ,'L0DiMuonDecision'
                             ,'L0ElectronDecision'
                             ,'L0HadronDecision'
                             ,'L0MuonDecision'
                             ,'L0PhotonDecision'
                             ]

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
