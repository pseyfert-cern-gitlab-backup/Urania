###########################################################################################################################################
## script settings ##
#####################
import sys
sys.argv.append( '-b' )


nTupleFilePath   = '/afs/cern.ch/user/k/kklimasz/workspace/data/Bs2JPsieePhi/RD_NEW/M_Bs_Fits/data/DVNtuples_Bs2JpsieePhiStrip21_TupleBsDetached_RDfull_Bu2JpsieeK_Bs2DsPi_sWeight_tupleB_best.root'
nTupleName       = 'DecayTree'
dataSetsFilePath = 'out.root'
dataSetsFilePath2 = 'out2.root'
appendToFile     = False
savedObjects     = [ 'sigSWeight' ]
plotsFilePath    = 'plots.pdf'

simulation       = False
runPeriods       = [ 2011, 2012 ]
triggerSel       = 'SigmaSel' # 'noSelection' # 'paper2012' # 'HLT1Unbiased' # 'paper2012'
dataCuts         = 'TimeSel' #_BspT' #'TimeSel_CosThetae' #'TimeSel' # 'noSelection' # 'nominal2011'
#dataSample       = '(bkgcat==0 || bkgcat==50)' if simulation else ''
sWeightName      = 'sigWeight_2KKBins'
addSWeights      = True
addKKMassCat     = True
addTrackMomenta  = False
addTaggingObs    = ( )#( 0, 0 ) # ( 2, 2 )
createRangeData  = False
createNTuple     = False
splitDataSet     = [ ] #[ 'tagCatP2VVOS', 'tagCatP2VVSS' ]
KKMassBinBounds  = [990., 1050]#[ 990., 1020. - 12., 1020., 1020. + 12., 1050. ] # [ 990., 1020. - 12., 1020. - 4., 1020., 1020. + 4., 1020. + 12., 1050. ] # [ 1008., 1020., 1032. ]

eventFracs       = [  dict( N_sigMass = 0.7, N_cbkgMass = 0.01, N_cbkg2Mass = 0.1, N_cbkg3Mass = 0.1, N_cbkg4Mass = None )
                    #, dict( N_sigMass = 0.11,  N_cbkgMass = None )
                    #, dict( N_sigMass = 0.70,  N_cbkgMass = None )
                    #, dict( N_sigMass = 0.64,  N_cbkgMass = None )
                    #, dict( N_sigMass = 0.18,  N_cbkgMass = None )
                   ]
sigMassModel     = ''
cbkgMassModel    = ''
SWeightsType     = 'simultaneousFreeCBkg'
#numMassBins      = [ 70, 40, 20, 20, 20 ]
numMassBins      = [ 80, 80, 80, 80, 80 ]
massLogPlotRange = ( 1.e0, 1.e4 ) # ( 1.9e2, 1.2e4 ) # ( 8.e2, 2.5e4 )

fitOpts = dict(  NumCPU    = 6
               , Optimize  = 2
               , Timer     = True
#               , Verbose   = True
#               , Minos     = True
#               , Hesse     = False
               , Minimizer = 'Minuit2'
               , Offset    = True
              )

from math import pi
from ROOT import RooNumber
RooInf  = RooNumber.infinity()
KKMMin  = KKMassBinBounds[0]
KKMMax  = KKMassBinBounds[-1]

obsKeys = [  'runPeriod'
           , 'eventNumber', 'runNumber'
           , 'mass', 'mass_std', 'KKMass', 'eeMass'
           , 'sigmam', 'sigmam_std', 'sigma_KKMass', 'sigma_eeMass'
           , 'time', 'timeRes'
           , 'ctk', 'ctl', 'phih'
           , 'cpsi', 'cttr', 'phitr'
           , 'wTagOS_CB', 'tagDecOS_CB'
           , 'wTagSS_NN', 'tagDecSS_NN'
           , 'wTagOS_CB_calib', 'tagDecOS_CB_calib'
           , 'wTagSS_NN_calib', 'tagDecSS_NN_calib'
           , 'sel'#, 'bkgcat'#, 'selA', 'selB'
           , 'hlt1B', 'hlt2B', 'l0UB'#, 'hlt1B', 'hlt1UB'
	   , 'L0GDec', 'L0GTIS', 'L0GTOS', 'L0EDec', 'L0ETIS', 'L0ETOS'
	   , 'L0HDec', 'L0HTIS', 'L0HTOS', 'L0PDec', 'L0PTIS', 'L0PTOS', 'L0MDec', 'L0MTIS', 'L0MTOS'
	   , 'Hlt1Dec', 'Hlt1TIS', 'Hlt1TOS'
	   , 'Hlt2Topo2Dec', 'Hlt2Topo2TIS', 'Hlt2Topo2TOS', 'Hlt2Topo3Dec', 'Hlt2Topo3TIS', 'Hlt2Topo3TOS', 'Hlt2Topo4Dec', 'Hlt2Topo4TIS', 'Hlt2Topo4TOS'
	   , 'Hlt2TopoE2Dec', 'Hlt2TopoE2TIS', 'Hlt2TopoE2TOS', 'Hlt2TopoE3Dec', 'Hlt2TopoE3TIS', 'Hlt2TopoE3TOS', 'Hlt2TopoE4Dec', 'Hlt2TopoE4TIS', 'Hlt2TopoE4TOS'
           , 'Hlt2IncPhiDec', 'Hlt2IncPhiTIS', 'Hlt2IncPhiTOS'
           , 'pid'#,'trueid'#, 'trigDecUnb', 'trigDecB'
	   , 'B_P', 'Kplus_P', 'Kplus_PT', 'Kminus_P', 'Kminus_PT'
	   , 'eplus_P', 'eplus_PT', 'eminus_P', 'eminus_PT'
	   , 'B_Pt', 'B_eta', 'B_phi', 'nPV', 'nTracks' 
	   , 'B_ip_ownpv', 'B_fdchi2_ownpv', 'Bs_endvertex_chi2', 'phi_pt', 'jpsi_pt', 'mass_chi2'
	   , 'eplus_pide', 'eminus_pide', 'Kplus_pidK', 'Kminus_pidK', 'Kplus_pidp', 'Kminus_pidp'
	   , 'Kplus_probnnk', 'Kminus_probnnk', 'Kplus_probnnp', 'Kminus_probnnp'
	   , 'eplus_ipchi2_ownpv', 'eminus_ipchi2_ownpv'
          ]

if simulation :
    obsKeys += [ 'truetime', 'bkgcat' ]
if addTrackMomenta :
    obsKeys += [ '%s_P%s' % ( part, comp ) for part in [ 'Kplus', 'Kminus', 'eplus', 'eminus' ] for comp in ( 'X', 'Y', 'Z' ) ]

obsDict = dict(  runPeriod = ( 'runPeriod',            'run period', dict( [ ( 'p%d' % period, period ) for period in runPeriods ] ) )
               , eventNumber = ( 'eventNumber',            'event number', '', 1.215e9, 0., 4.8e9 )#dict( [ ( 'p%d' % number, number ) for number in eventNumbers ] ))#'', 1.215e9, 0., 4.8e9 ) 
               , runNumber = ( 'runNumber',            'run number',  '', 1.162e5, 0., 1.36e5 )#dict( [ ( 'p%x' % number, number ) for number in runNumbers ] ))#'', 1.162e5, 0., 1.36e5 ) 
               , mass	   = ( 'mass',                 'm(e^{+}e^{-} K^{+}K^{-})',    'MeV/c^{2}', 5366.,  4600.,   6000.	)
               , sigmam    = ( 'sigmam',               '#sigma(m)',               'MeV/c^{2}',        6.81,   0.,  100.        )
               , mass_chi2   = ( 'mass_chi2',          '#chi^{2}(m(e^{+}e^{-} K^{+}K^{-}))',    ' ', 0.,  -RooInf,   +RooInf	)
               , mass_std  = ( 'mass_std',             'm(e^{+}e^{-} K^{+}K^{-})',    'MeV/c^{2}', 5366.,  4600.,   6000.	)
               , sigmam_std    = ( 'sigmam_std',               '#sigma(m_std)',               'MeV/c^{2}',        40.12,   0.,  250.        )
               , eeMass    = ( 'mdau1',                'm(e^{+}e^{-})',       'MeV/c^{2}', 3096.,  2500.,   3300.	)
               , sigma_eeMass    = ( 'sigmadau1',               '#sigma(m(e^{+}e^{-}))',               'MeV/c^{2}',        35.75,   0.,  180.        )
               , KKMass    = ( 'mdau2',                'm(K^{+}K^{-})',           'MeV/c^{2}', 1020.,  KKMMin,  KKMMax      )
               , sigma_KKMass    = ( 'sigmamdau2',               '#sigma(m(K^{+}K^{-}))',               'MeV/c^{2}',        1.026,   0.,  4.        )
               , time	   = ( 'time',                 'Decay time',              'ps',        1.5,    0.3,     14.         )
               , truetime  = ( 'truetime',             'true time',               'ps',        0.,     0.,	30.         )
               , timeRes   = ( 'sigmat',               '#sigma(t)',               'ps',        0.01,   0.0001,  0.12        )
               , ctk	   = ( 'helcosthetaK',         'cos(#theta_{K})',         '',          0.,    -1.,     +1.          )
               , ctl	   = ( 'helcosthetaL',         'cos(#theta_{#mu})',       '',          0.,    -1.,     +1.          )
               , phih	   = ( 'helphi',               '#phi_{h}',                'rad',       0.,    -pi,     +pi          )
               , cpsi	   = ( 'trcospsi',             'cos(#psi_{tr})',          '',          0.,    -1.,     +1.          )
               , cttr	   = ( 'trcostheta',           'cos(#theta_{tr})',        '',          0.,    -1.,     +1.          )
               , phitr     = ( 'trphi',                '#phi_{tr}',               'rad',       0.,    -pi,     +pi          )
               , wTagOS_CB	= ( 'tagomega_os_cb',          'OS CB est. wrong-tag prob.',    '',	  0.25,   0.,	   0.50001     )
               , wTagOS_CBCh    = ( 'tagomega_os_cbch',        'OS CBCh est. wrong-tag prob.', '',        0.25,   0.,	   0.50001     )
               , wTagOS_NN	= ( 'tagomega_os_nn',          'OS NN est. wrong-tag prob.', '',          0.25,   0.,	   0.50001     )
               , wTagOS_NNCh    = ( 'tagomega_os_nnch',        'OS NNCh est. wrong-tag prob.', '',        0.25,   0.,	   0.50001     )
               , wTagSS_CB	= ( 'tagomega_ss_cb',          'SS CB est. wrong-tag prob.', '',          0.25,   0.,	   0.50001     )
               , wTagSS_NN	= ( 'tagomega_ss_nn',          'SS NN est. wrong-tag prob.', '',          0.25,   0.,	   0.50001     )
               , tagDecOS_CB    = ( 'tagdecision_os_cb',       'OS CB tag decision',    { 'B' : +1, 'Bbar' : -1, 'Untagged' : 0 }         )
               , tagDecOS_CBCh  = ( 'tagdecision_os_cbch',     'OS CBCh tag decision',  { 'B' : +1, 'Bbar' : -1, 'Untagged' : 0 }         )
               , tagDecOS_NN    = ( 'tagdecision_os_nn',       'OS NN tag decision',    { 'B' : +1, 'Bbar' : -1, 'Untagged' : 0 }         )
               , tagDecOS_NNCh  = ( 'tagdecision_os_nnch',     'OS NNCh tag decision',  { 'B' : +1, 'Bbar' : -1, 'Untagged' : 0 }         )
               , tagDecSS_CB    = ( 'tagdecision_ss_cb',       'SS CB tag decision',    { 'B' : +1, 'Bbar' : -1, 'Untagged' : 0 }         )
               , tagDecSS_NN    = ( 'tagdecision_ss_nn',       'SS NN tag decision',    { 'B' : +1, 'Bbar' : -1, 'Untagged' : 0 }         )
               , wTagOS_CB_calib	= ( 'tagomega_os_cb_calib',          'OS CB est. wrong-tag prob.',    '',	  0.25,   0.,	   0.50001     )
               , wTagOS_CBCh_calib    = ( 'tagomega_os_cbch_calib',        'OS CBCh est. wrong-tag prob.', '',        0.25,   0.,	   0.50001     )
               , wTagOS_NN_calib	= ( 'tagomega_os_nn_calib',          'OS NN est. wrong-tag prob.', '',          0.25,   0.,	   0.50001     )
               , wTagOS_NNCh_calib    = ( 'tagomega_os_nnch_calib',        'OS NNCh est. wrong-tag prob.', '',        0.25,   0.,	   0.50001     )
               , wTagSS_CB_calib	= ( 'tagomega_ss_cb_calib',          'SS CB est. wrong-tag prob.', '',          0.25,   0.,	   0.50001     )
               , wTagSS_NN_calib	= ( 'tagomega_ss_nn_calib',          'SS NN est. wrong-tag prob.', '',          0.25,   0.,	   0.50001     )
               , tagDecOS_CB_calib    = ( 'tagdecision_os_cb_calib',       'OS CB tag decision',    { 'B' : +1, 'Bbar' : -1, 'Untagged' : 0 }         )
               , tagDecOS_CBCh_calib  = ( 'tagdecision_os_cbch_calib',     'OS CBCh tag decision',  { 'B' : +1, 'Bbar' : -1, 'Untagged' : 0 }         )
               , tagDecOS_NN_calib    = ( 'tagdecision_os_nn_calib',       'OS NN tag decision',    { 'B' : +1, 'Bbar' : -1, 'Untagged' : 0 }         )
               , tagDecOS_NNCh_calib  = ( 'tagdecision_os_nnch_calib',     'OS NNCh tag decision',  { 'B' : +1, 'Bbar' : -1, 'Untagged' : 0 }         )
               , tagDecSS_CB_calib    = ( 'tagdecision_ss_cb_calib',       'SS CB tag decision',    { 'B' : +1, 'Bbar' : -1, 'Untagged' : 0 }         )
               , tagDecSS_NN_calib    = ( 'tagdecision_ss_nn_calib',       'SS NN tag decision',    { 'B' : +1, 'Bbar' : -1, 'Untagged' : 0 }         )
               , tagCatOS  = ( 'tagcat_os',            'OS tag category', [ 'unt' ] + [ 'cat%d' % c for c in range(1, 6) ]  )
               , bkgcat    = ( 'bkgcat',               'background cat',  { 'signal' : 0, 'PartRec' : 40, 'lowMass' : 50 }                  )
               , sel	   = ( 'sel',                  'selection',	  { 'sel'   : 1, 'notSel'   : 0 }                   )
               , hlt1B     = ( 'hlt1_biased',          'HLT1 B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , hlt2B     = ( 'hlt2_biased',          'HLT2 B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , l0UB	   = ( 'l0_unbiased',        'L0 UB.',         { 'UB'    : 1, 'notUB'    : 0 }                  )
               , L0GDec     = ( 'Bs_L0Global_Dec',          'L0Global_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0GTIS     = ( 'Bs_L0Global_TIS',          'L0Global_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0GTOS     = ( 'Bs_L0Global_TOS',          'L0Global_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0EDec     = ( 'Bs_L0ElectronDecision_Dec',          'L0Electron_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0ETIS     = ( 'Bs_L0ElectronDecision_TIS',          'L0Electron_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0ETOS     = ( 'Bs_L0ElectronDecision_TOS',          'L0Electron_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0HDec     = ( 'Bs_L0HadronDecision_Dec',          'L0Hadron_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0HTIS     = ( 'Bs_L0HadronDecision_TIS',          'L0Hadron_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0HTOS     = ( 'Bs_L0HadronDecision_TOS',          'L0Hadron_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0PDec     = ( 'Bs_L0PhotonDecision_Dec',          'L0Photon_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0PTIS     = ( 'Bs_L0PhotonDecision_TIS',          'L0Photon_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0PTOS     = ( 'Bs_L0PhotonDecision_TOS',          'L0Photon_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0MDec     = ( 'Bs_L0MuonDecision_Dec',          'L0Muon_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0MTIS     = ( 'Bs_L0MuonDecision_TIS',          'L0Muon_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , L0MTOS     = ( 'Bs_L0MuonDecision_TOS',          'L0Muon_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt1Dec     = ( 'Bs_Hlt1TrackAllL0Decision_Dec',          'Hlt1TrackAllL0_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt1TIS     = ( 'Bs_Hlt1TrackAllL0Decision_TIS',          'Hlt1TrackAllL0_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt1TOS     = ( 'Bs_Hlt1TrackAllL0Decision_TOS',          'Hlt1TrackAllL0_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2Topo2Dec     = ( 'Bs_Hlt2Topo2BodyBBDTDecision_Dec',          'Hlt2Topo2BodyBBDT_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2Topo2TIS     = ( 'Bs_Hlt2Topo2BodyBBDTDecision_TIS',          'Hlt2Topo2BodyBBDT_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2Topo2TOS     = ( 'Bs_Hlt2Topo2BodyBBDTDecision_TOS',          'Hlt2Topo2BodyBBDT_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2Topo3Dec     = ( 'Bs_Hlt2Topo3BodyBBDTDecision_Dec',          'Hlt2Topo3BodyBBDT_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2Topo3TIS     = ( 'Bs_Hlt2Topo3BodyBBDTDecision_TIS',          'Hlt2Topo3BodyBBDT_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2Topo3TOS     = ( 'Bs_Hlt2Topo3BodyBBDTDecision_TOS',          'Hlt2Topo3BodyBBDT_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2Topo4Dec     = ( 'Bs_Hlt2Topo4BodyBBDTDecision_Dec',          'Hlt2Topo4BodyBBDT_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2Topo4TIS     = ( 'Bs_Hlt2Topo4BodyBBDTDecision_TIS',          'Hlt2Topo4BodyBBDT_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2Topo4TOS     = ( 'Bs_Hlt2Topo4BodyBBDTDecision_TOS',          'Hlt2Topo4BodyBBDT_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2TopoE2Dec     = ( 'Bs_Hlt2TopoE2BodyBBDTDecision_Dec',          'Hlt2TopoE2BodyBBDT_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2TopoE2TIS     = ( 'Bs_Hlt2TopoE2BodyBBDTDecision_TIS',          'Hlt2TopoE2BodyBBDT_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2TopoE2TOS     = ( 'Bs_Hlt2TopoE2BodyBBDTDecision_TOS',          'Hlt2TopoE2BodyBBDT_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2TopoE3Dec     = ( 'Bs_Hlt2TopoE3BodyBBDTDecision_Dec',          'Hlt2TopoE3BodyBBDT_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2TopoE3TIS     = ( 'Bs_Hlt2TopoE3BodyBBDTDecision_TIS',          'Hlt2TopoE3BodyBBDT_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2TopoE3TOS     = ( 'Bs_Hlt2TopoE3BodyBBDTDecision_TOS',          'Hlt2TopoE3BodyBBDT_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2TopoE4Dec     = ( 'Bs_Hlt2TopoE4BodyBBDTDecision_Dec',          'Hlt2TopoE4BodyBBDT_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2TopoE4TIS     = ( 'Bs_Hlt2TopoE4BodyBBDTDecision_TIS',          'Hlt2TopoE4BodyBBDT_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2TopoE4TOS     = ( 'Bs_Hlt2TopoE4BodyBBDTDecision_TOS',          'Hlt2TopoE4BodyBBDT_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2IncPhiDec     = ( 'Bs_Hlt2IncPhiDecision_Dec',          'Hlt2IncPhi_Dec B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2IncPhiTIS     = ( 'Bs_Hlt2IncPhiDecision_TIS',          'Hlt2IncPhi_TIS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , Hlt2IncPhiTOS     = ( 'Bs_Hlt2IncPhiDecision_TOS',          'Hlt2IncPhi_TOS B.',          { 'B'     : 1, 'notB'     : 0 }                  )
               , sel_onecand                = ( 'sel_onecand',                { 'sel' : 1, 'notSel' : 0 }              )
               , ePTrChi2                   = ( 'eplus_track_chi2ndof',       'e+ chi^2/#dof', 1.,    0.,      4.     )
               , eMTrChi2                   = ( 'eminus_track_chi2ndof',      'e- chi^2/#dof', 1.,    0.,      4.     )
               , KPTrChi2                   = ( 'Kplus_track_chi2ndof',       'K+ chi^2/#dof',  1.,    0.,      4.     )
               , KMTrChi2                   = ( 'Kminus_track_chi2ndof',      'K- chi^2/#dof',  1.,    0.,      4.     )
               , eplus_pide                 = ( 'eplus_pide',                 'eplus_PIDe',   ' ', 0.,   -RooInf, +RooInf )
               , eminus_pide                = ( 'eminus_pide',                'eminus_PIDe',  ' ', 0.,   -RooInf, +RooInf )
               , Kplus_pidK                 = ( 'Kplus_pidK',                 'Kplus_pidK',     ' ', 0.,    0.,     +RooInf )
               , Kminus_pidK                = ( 'Kminus_pidK',                'Kminus_pidK',    ' ', 0.,    0.,     +RooInf )
               , Kplus_pidp                 = ( 'Kplus_pidp',                 'Kplus_pidp',     ' ', 0.,    -RooInf,     +RooInf )
               , Kminus_pidp                = ( 'Kminus_pidp',                'Kminus_pidp',    ' ', 0.,    -RooInf,     +RooInf )
               , Kplus_probnnk              = ( 'Kplus_probnnk',              'Kplus_probnnK',     ' ', 0.,    0.,     +RooInf )
               , Kminus_probnnk             = ( 'Kminus_probnnk',             'Kminus_probnnK',    ' ', 0.,    0.,     +RooInf )
               , Kplus_probnnp              = ( 'Kplus_probnnp',              'Kplus_probnnp',     ' ', 0.,    0.,     +RooInf )
               , Kminus_probnnp             = ( 'Kminus_probnnp',             'Kminus_probnnp',    ' ', 0.,    0.,     +RooInf )
               , eplus_P                    = ( 'eplus_P',                    'eplus_P',     'MeV/c', 0.,   -RooInf, +RooInf )
               , eplus_PT                   = ( 'eplus_PT',                   'eplus_PT',     'MeV/c', 0.,   -RooInf, +RooInf )
               , eplus_PX                   = ( 'eplus_PX',                   'eplus_PX',     'MeV/c', 0.,   -RooInf, +RooInf )
               , eplus_PY                   = ( 'eplus_PY',                   'eplus_PY',      'MeV/c', 0.,   -RooInf, +RooInf )
               , eplus_PZ                   = ( 'eplus_PZ',                   'eplus_PZ',      'MeV/c', 0.,   -RooInf, +RooInf )
               , eminus_P                   = ( 'eminus_P',                   'eminus_P',     'MeV/c', 0.,   -RooInf, +RooInf )
               , eminus_PT                  = ( 'eminus_PT',                  'eminus_PT',     'MeV/c', 0.,   -RooInf, +RooInf )
               , eminus_PX                  = ( 'eminus_PX',                  'eminus_PX',     'MeV/c', 0.,   -RooInf, +RooInf )
               , eminus_PY                  = ( 'eminus_PY',                  'eminus_PY',     'MeV/c', 0.,   -RooInf, +RooInf )
               , eminus_PZ                  = ( 'eminus_PZ',                  'eminus_PZ',     'MeV/c', 0.,   -RooInf, +RooInf )
               , Kplus_P                    = ( 'Kplus_P',                    'Kplus_P',	'MeV/c', 0.,   -RooInf, +RooInf )
               , Kplus_PT                   = ( 'Kplus_PT',                   'Kplus_PT',	'MeV/c', 0.,   -RooInf, +RooInf )
               , Kplus_PX                   = ( 'Kplus_PX',                   'Kplus_PX',	'MeV/c', 0.,   -RooInf, +RooInf )
               , Kplus_PY                   = ( 'Kplus_PY',                   'Kplus_PY',	'MeV/c', 0.,   -RooInf, +RooInf )
               , Kplus_PZ                   = ( 'Kplus_PZ',                   'Kplus_PZ',	'MeV/c', 0.,   -RooInf, +RooInf )
               , Kminus_P                   = ( 'Kminus_P',                   'Kminus_P',	'MeV/c', 0.,   -RooInf, +RooInf )
               , Kminus_PT                  = ( 'Kminus_PT',                  'Kminus_PT',	'MeV/c', 0.,   -RooInf, +RooInf )
               , Kminus_PX                  = ( 'Kminus_PX',                  'Kminus_PX',	'MeV/c', 0.,   -RooInf, +RooInf )
               , Kminus_PY                  = ( 'Kminus_PY',                  'Kminus_PY',	'MeV/c', 0.,   -RooInf, +RooInf )
               , Kminus_PZ                  = ( 'Kminus_PZ',                  'Kminus_PZ',	'MeV/c', 0.,   -RooInf, +RooInf )
               , eplus_ipchi2_ownpv         = ( 'eplus_ipchi2_ownpv',         'eplus_ipchi2_ownpv',      ' ', 0.,    0., +RooInf )
               , eminus_ipchi2_ownpv        = ( 'eminus_ipchi2_ownpv',        'eminus_ipchi2_ownpv',     ' ', 0.,    0., +RooInf )
               , B_Pt                       = ( 'B_Pt',                       'B_Pt',           'MeV/c', 0.,    0.,	+RooInf )
               , B_eta                      = ( 'B_eta',                      'B_eta',          ' ', 3.,    1.,	 7. )
               , B_phi                      = ( 'B_phi',                      'B_phi',          'rad', 0.,    -pi,	 +pi )
               , B_ip_ownpv                 = ( 'B_ip_ownpv',                 'B_ip_ownpv',      ' ', 0.025,    -RooInf, +RooInf )
               , B_fdchi2_ownpv             = ( 'B_fdchi2_ownpv',             'B_fdchi2_ownpv',  ' ', 0.,    0.,	 +RooInf )
               , nTracks                    = ( 'nTracks',                    'nTracks',        ' ', 150.,    0.,	 900. )
               , nPV	                    = ( 'nPV', 		              'nPV',        ' ', 1.,    0.,	 9. )
               , B_P                        = ( 'B_P',                        'B_P',            'MeV/c', 0.,    0.,	 RooInf )
               , phi_pt                     = ( 'phi_pt',                     'phi_pt',    'MeV/c', 500.,  500.,    +RooInf )
               , jpsi_pt                    = ( 'jpsi_pt',                    'jpsi_pt',    'MeV/c', 0.,  0.,    +RooInf )
               , Bs_LOKI_CosPolAngle_Dau1   = ( 'Bs_LOKI_CosPolAngle_Dau1',   'ee cos(th)',   0.,   -1.,     +1.     )
               , Bs_IPCHI2_OWNPV            = ( 'Bs_IPCHI2_OWNPV',            'IP chi2 PV',     0.,   -RooInf, +RooInf )
               , Bs_MINIPCHI2NEXTBEST       = ( 'Bs_MINIPCHI2NEXTBEST',       'IP chi2 next',   0.,   -RooInf, +RooInf )
               , Bs_LOKI_DTF_VCHI2NDOF      = ( 'Bs_LOKI_DTF_VCHI2NDOF',      'DTF chi2/#dof',  0.,   -RooInf, +RooInf )
               , Bs_endvertex_chi2          = ( 'Bs_endvertex_chi2',           'Bs vert chi2',  ' ', 0.,   0.,       50.    )
               , phi_ENDVERTEX_CHI2         = ( 'phi_ENDVERTEX_CHI2',         'ee vert chi2', 0.,   0.,       16.    )
               , Jpsi_ENDVERTEX_CHI2        = ( 'Jpsi_ENDVERTEX_CHI2',        'KK vert chi2',   0.,   0.,	16.    )
               , pid                        = ( 'pid',                 'Bs true ID',   { 'Bs' : +531}	   )
              )

# For sWeight from B0s(DTF) mass
massRanges = dict(  LeftSideBand  = ( 4600., 5150. )
                  , Signal        = ( 5000., 5700. )
                  , RightSideBand = ( 5600., 6000. )
#                  , PeakBkg       = ( 5390., 5440. )
                 )

#if addTaggingObs and addTaggingObs[0] == 2 :
#    tagCatsOS = [  ( 'Untagged', 0, 0.5000001 )
#                 , ( 'Tagged',   1, 0.4999999 )
#                ]
#elif addTaggingObs and addTaggingObs[0] > 2 :
#    tagCatsOS = [  ( 'Untagged', 0, 0.5000001 )
#                 , ( 'TagCat1',  1, 0.4999999 )
#                 , ( 'TagCat2',  2, 0.38      )
#                 , ( 'TagCat3',  3, 0.31      )
#                 , ( 'TagCat4',  4, 0.24      )
#                 , ( 'TagCat5',  5, 0.17      )
#                ]
#else :
#    tagCatsOS = [ ]

#if addTaggingObs and addTaggingObs[1] == 2 :
#    tagCatsSS = [  ( 'Untagged', 0, 0.5000001 )
#                 , ( 'Tagged',   1, 0.4999999 )
#                ]
#elif addTaggingObs and addTaggingObs[1] > 2 :
#    tagCatsSS = [  ( 'Untagged', 0, 0.5000001 )
#                 , ( 'TagCat1',  1, 0.4999999 )
#                 , ( 'TagCat2',  2, 0.32      )
#                 , ( 'TagCat3',  3, 0.25      )
#                ]
#else :
#    tagCatsSS = [ ]


###########################################################################################################################################
## read data ##
###############

from P2VV.Load import RooFitOutput, LHCbStyle

# create list of required observables
reqObsList = [ 'index', 'mass', 'KKMass', 'tagDecOS_CB_calib', 'tagDecSS_NN_calib', 'wTagOS_CB_calib', 'wTagSS_NN_calib' ]
reqObsList += ['runPeriod'] if runPeriods else [ ]
reqObsList += ['hlt1B'] if triggerSel == 'paper2012' else [ 'hlt1B', 'hlt2B' ] if triggerSel == 'timeEffFit' else [ ]

# create workspace
from P2VV.RooFitWrappers import RooObject
ws = RooObject(workspace = 'JpsiphiWorkspace').ws()

# create observables
from P2VV.RooFitWrappers import RealVar, Category
observables  = { }
observables['index'] = RealVar( 'index', Title = 'event index', Observable = True, Value = 0., MinMax = ( -RooInf, +RooInf ) )
obsSetPreDS  = [ observables['index'] ]
obsSetNTuple = [ ]
for obs in obsKeys + reqObsList :
    if obs in observables : continue

    if obs.startswith('sigWeight') :
        observables[obs] = RealVar( obs, Title = 'signal sWeight', Observable = True, Value = 1. )

    elif type( obsDict[obs][2] ) == dict or type( obsDict[obs][2] ) == list :
        observables[obs] = Category( obsDict[obs][0], Title = obsDict[obs][1], Observable = True, States = obsDict[obs][2] )

    else :
#       print obs
        observables[obs] = RealVar( obsDict[obs][0], Title = obsDict[obs][1], Unit = obsDict[obs][2], Observable = True
                                   , Value = obsDict[obs][3], MinMax = ( obsDict[obs][4], obsDict[obs][5] ) )

    if obs in obsKeys    : obsSetNTuple.append( observables[obs] )
    if obs in reqObsList : obsSetPreDS.append(  observables[obs] )

# add mass ranges
observables['mass'].setRanges(massRanges)

# build cuts string
from P2VV.Imports import cutSelStrings, triggerSelStrings
ntupleCuts = cutSelStrings[dataCuts]
ntupleCuts += ( ' && ' if ntupleCuts else '' ) + triggerSelStrings[triggerSel]

# read n-tuple file(s)
print 'P2VV - INFO: createB2CCDataSet: reading n-tuple "%s" from file "%s"' % ( nTupleName, nTupleFilePath )
print 'P2VV - INFO: createB2CCDataSet: selection cuts:\n    %s' % ntupleCuts
from ROOT import TFile, TTree
dataTreeFile = TFile.Open(nTupleFilePath)
assert dataTreeFile, 'P2VV - ERROR: createB2CCDataSet: could not open file "%s"' % nTupleFilePath
dataTree = dataTreeFile.Get(nTupleName)
assert dataTree, 'P2VV - ERROR: createB2CCDataSet: could not locate tree "%s" in file "%s"' % ( nTupleName, nTupleFilePath )

# create data set from n-tuple
dataSets = dict( pre = ( dataTree.buildDataSet( Observables = obsSetPreDS, Name = 'JpsiKK', Title = 'JpsiKK', Cuts = ntupleCuts
                       	, IndexName = 'index' ), [ ] ) )

print 'P2VV - INFO: createB2CCDataSet: data set from n-tuple:\n' + ' ' * 13,
dataSets['pre'][0].Print()
print

# create KK mass binning
from array import array
KKMassBinsArray = array( 'd', KKMassBinBounds )

from ROOT import RooBinning
KKMassBinning = RooBinning( len(KKMassBinBounds) - 1, KKMassBinsArray, 'KKMassBinning' )
observables['KKMass'].setBinning( KKMassBinning, 'KKMassBinning' )

# add KK mass split category to data
from P2VV.RooFitWrappers import BinningCategory
observables['KKMassCat'] = BinningCategory( 'KKMassCat'
                                           , Observable = observables['KKMass']
                                           , Binning = KKMassBinning
                                           , Fundamental = True
                                           , Data = [ dataSets['pre'][0] ]
                                           , CatTypeName = 'bin'
                                          )
if addKKMassCat : obsSetNTuple.append( observables['KKMassCat'] )


###########################################################################################################################################
## build J/psiKK mass PDFs ##
#############################

if not simulation :
    # initialize PDF components
    sigFrac     = eventFracs[0]['N_sigMass'] if eventFracs[0]['N_sigMass'] else 1. - sum(val for val in eventFracs[0].itervalues() if val)
    bkgFrac     = eventFracs[0]['N_cbkgMass'] if eventFracs[0]['N_cbkgMass'] else 1. - sum(val for val in eventFracs[1].itervalues() if val)
    bkg2Frac     = eventFracs[0]['N_cbkg2Mass'] if eventFracs[0]['N_cbkg2Mass'] else 1. - sum(val for val in eventFracs[2].itervalues() if val)
    bkg3Frac     = eventFracs[0]['N_cbkg3Mass'] if eventFracs[0]['N_cbkg3Mass'] else 1. - sum(val for val in eventFracs[3].itervalues() if val)
    nEvents     = dataSets['pre'][0].sumEntries()
    nSignal     = nEvents * sigFrac
    nBackground = nEvents * bkgFrac
    nBackground2 = nEvents * bkg2Frac
    nBackground3 = nEvents * bkg3Frac
    nBackground4 = nEvents * ( 1. - sigFrac - bkgFrac - bkg2Frac - bkg3Frac)

    from P2VV.RooFitWrappers import Component
    sigMassComps  = Component( 'sigMass',  [ ], Yield = ( nSignal,     0., nEvents ) )  # signal
    cbkgMassComps = Component( 'cbkgMass', [ ], Yield = ( nBackground, 0., nEvents ) )  # combinatorial background
    cbkg2MassComps = Component( 'cbkg2Mass', [ ], Yield = ( nBackground2, 0., nEvents ) )  # part. recons. background 2
    cbkg3MassComps = Component( 'cbkg3Mass', [ ], Yield = ( nBackground3, 0., nEvents ) )  # part. recons. background 3
    cbkg4MassComps = Component( 'cbkg4Mass', [ ], Yield = ( nBackground4, 0., nEvents ) )  # part. recons. background 4

    massComps  = [ sigMassComps, cbkgMassComps, cbkg2MassComps, cbkg3MassComps, cbkg4MassComps ]
    yieldNames = [ comp.getYield().GetName() for comp in massComps ]

    # build the signal mass PDF
## Triple Gauss
#    sigMassArgs = dict( Name = 'sig_m', mass = observables['mass'] )
#    from P2VV.Parameterizations.MassPDFs import Bs2JpsieePhi_Signal_Mass as SignalBMass
    sigMassArgs = dict( Name = 'sig_m', mass = observables['mass'], Mean = 5300 )
## Double Cristal Ball
#    from P2VV.Parameterizations.MassPDFs import DoubleCB_Mass as SignalBMass
## Double Cristal Ball + Gauss
#    from P2VV.Parameterizations.MassPDFs import DoubleCB_Gauss_Mass as SignalBMass
## Ipatia2
#    from P2VV.Parameterizations.MassPDFs import Ipatia2_Mass as SignalBMass
## Ipatia2 + Gauss
#    from P2VV.Parameterizations.MassPDFs import Ipatia2_Gauss_Mass as SignalBMass
## Voigtian + Gauss
    from P2VV.Parameterizations.MassPDFs import Voigtian_Gauss_Mass as SignalBMass
    signalBMass = SignalBMass( **sigMassArgs )

    # build the combinatorial background mass PDF
    cbkgMassArgs = dict( Name = 'cbkg_m', mass = observables['mass'] )
    from P2VV.Parameterizations.MassPDFs import Bs2JpsieePhi_Background_Mass as BackgroundBMass
#    from P2VV.Parameterizations.MassPDFs import Bs2JpsieePhi_BkgChebychev_Mass as BackgroundBMass
    backgroundBMass = BackgroundBMass( **cbkgMassArgs )

    # build the partially reconstructed background 2 and 3 mass PDF
## Double Cristal Ball
#    from P2VV.Parameterizations.MassPDFs import DoubleCB_Mass as BackgroundMass
## Double Gauss
#    from P2VV.Parameterizations.MassPDFs import DoubleGauss_Mass as BackgroundMass
## Single Gauss
    from P2VV.Parameterizations.MassPDFs import Gauss_Mass as BackgroundMass
    cbkg2MassArgs = dict( Name = 'cbkg2_m', mass = observables['mass'], Mean = 4700., Max = 4900. )
    background2BMass = BackgroundMass( **cbkg2MassArgs )
    cbkg3MassArgs = dict( Name = 'cbkg3_m', mass = observables['mass'], Mean = 5100., Max = 5200. )
    background3BMass = BackgroundMass( **cbkg3MassArgs )
    cbkg4MassArgs = dict( Name = 'cbkg4_m', mass = observables['mass'], Mean = 5500. )
    background4BMass = BackgroundMass( **cbkg4MassArgs )

    # build mass PDF
    from P2VV.RooFitWrappers import buildPdf
    sigMassComps  += signalBMass.pdf()
    cbkgMassComps += backgroundBMass.pdf()
    cbkg2MassComps += background2BMass.pdf()
    cbkg3MassComps += background3BMass.pdf()
    cbkg4MassComps += background4BMass.pdf()
    massPdf = buildPdf( massComps, Observables = [ observables['mass'] ], Name = 'JpsiKKMass' )

###########################################################################################################################################
## fit J/psiKK mass distributions ##
####################################

if not simulation :
    # determine mass parameters with a fit
    print 120 * '='
    print 'P2VV - INFO: createB2CCDataSet: fitting with mass PDF'
    massFitResult = massPdf.fitTo( dataSets['pre'][0], Save = True, **fitOpts )

    from P2VV.Imports import parNames
    massFitResult.PrintSpecial( text = True, LaTeX = True, normal = True, ParNames = parNames )
    massFitResult.covarianceMatrix().Print()
    massFitResult.correlationMatrix().Print()

    splitCats = [ ]
    if SWeightsType.startswith('simultaneous') and (runPeriods or triggerSel in ['paper2012', 'timeEffFit'] or len(KKMassBinBounds) > 2) :
        # get splitting categories and parameters
        splitCats = { }
        yieldNames = [ par.GetName() for par in massPdf.Parameters() if par.getAttribute('Yield') ]
        if runPeriods :
            splitCats[observables['runPeriod'].GetName()] = set([ par.GetName() for par in massPdf.Parameters() if not par.isConstant() ])
        if len(KKMassBinBounds) > 2 :
            splitCats[ observables['KKMassCat'].GetName() ] = set(yieldNames)
            if 'FreeCBkg' in SWeightsType :
                for par in backgroundBMass.parameters() :
                    if not par.isConstant() : splitCats[ observables['KKMassCat'].GetName() ].add( par.GetName() )
        if triggerSel == 'paper2012' or triggerSel == 'timeEffFit' :
            splitCats[ observables['hlt1B'].GetName() ] = set(yieldNames)
        if triggerSel == 'timeEffFit' :
            splitCats[ observables['hlt2B'].GetName() ] = set(yieldNames)

        splitParsDict = { }
        pdfVars = massPdf.getVariables()
        for cat, params in splitCats.iteritems() :
            assert ws.cat(cat), 'P2VV - ERROR: createB2CCDataSet: category "%s" not in workspace' % cat
            for par in params :
                assert ws.var(par), 'P2VV - ERROR: createB2CCDataSet: no variable "%s" in workspace' % par
                assert pdfVars.find(par), 'P2VV - ERROR: createB2CCDataSet: variable "%s" not in PDF' % par
                if ws[par] not in splitParsDict :
                    splitParsDict[ ws[par] ] = set( [ ws[cat] ] )
                else :
                    splitParsDict[ ws[par] ].add( ws[cat] )

        # create lists of split categories and parameters
        pars = splitParsDict.keys()
        splitCats = [ ]
        splitPars = [ ]
        for par in pars :
            if par not in splitParsDict : continue
            splitPars.append( set( [par] ) )
            splitCats.append( splitParsDict.pop(par) )
            for par1 in pars :
                if par1 not in splitParsDict : continue
                if splitParsDict[par1] == splitCats[-1] :
                    splitPars[-1].add(par1)
                    splitParsDict.pop(par1)

        # build simultaneous mass PDF
        print 'P2VV - INFO: createB2CCDataSet: building simultaneous PDF "%s":' % ( massPdf.GetName() + '_simul' )
        print 13 * ' ' + 'splitting categories: [ %s ]' % ' ], [ '.join(', '.join(cat.GetName() for cat in cats) for cats in splitCats)
        print 13 * ' ' + 'split parameters:     [ %s ]' % ' ], [ '.join(', '.join(par.GetName() for par in pars) for pars in splitPars)
        from P2VV.RooFitWrappers import SimultaneousPdf
        sWeightMassPdf = SimultaneousPdf(  massPdf.GetName() + '_simul'
                                         , MasterPdf       = massPdf
                                         , SplitCategories = splitCats
                                         , SplitParameters = splitPars
                                        )

        # set yields for categories
        splitCat      = sWeightMassPdf.indexCat()
        splitCatIter  = splitCat.typeIterator()
        splitCatState = splitCatIter.Next()
        massPdfPars   = sWeightMassPdf.getVariables()
        from P2VV.Utilities.General import getSplitPar
        from math import sqrt
        while splitCatState :
            KKMassState = -1
            if splitCat.isFundamental() :
                selStr = '!(%s-%d)' % ( splitCat.GetName(), splitCatState.getVal() )
                if splitCat.GetName() == observables['KKMassCat'].GetName() : KKMassState = splitCatState.getVal()
            else :
                splitCat.setLabel( splitCatState.GetName() )
                selStr = ' && '.join( '!(%s-%d)' % ( cat.GetName(), cat.getIndex() ) for cat in splitCat.inputCatList() )
                if observables['KKMassCat'] in splitCats[0] :
                    for cat in splitCat.inputCatList() :
                        if cat.GetName() == observables['KKMassCat'].GetName() : KKMassState = cat.getIndex()

            nEv    = dataSets['pre'][0].sumEntries()
            nEvBin = dataSets['pre'][0].sumEntries(selStr)
            for yName in yieldNames :
                stateName = splitCatState.GetName()
                yieldVar = getSplitPar( yName, stateName, massPdfPars )

                if len(eventFracs) > 1 and KKMassState >= 0 :
                    sigFrac = eventFracs[ KKMassState + 1 ][yName] if eventFracs[ KKMassState + 1 ][yName]\
                              else 1. - sum( val for val in eventFracs[ KKMassState + 1 ].itervalues() if val )
                    yieldVar.setVal( sigFrac * nEvBin )
                else :
                    yieldVar.setVal( yieldVar.getVal() * nEvBin / nEv )

                yieldVar.setError( sqrt( yieldVar.getVal() ) )
                yieldVar.setMin(0.)
                yieldVar.setMax(nEvBin)

            splitCatState = splitCatIter.Next()

        if SWeightsType.endswith( 'Fixed' ) :
            # fix mass shape parameters for fit
            fixedMassPars = [ par for par in sWeightMassPdf.Parameters()\
                              if not ( par.getAttribute('Yield') or par.isConstant() or 'Category' in par.ClassName() ) ]
            #from P2VV.Imports import parValues
            #parVals = {  'm_cbkg_exp_bin0'  : -2.1814e-03
            #           , 'm_cbkg_exp_bin1'  : -4.6151e-03
            #           , 'm_cbkg_exp_bin2'  : -1.4166e-03
            #           , 'm_cbkg_exp_bin3'  : -2.5203e-03
            #           , 'm_cbkg_exp_bin4'  : -1.3963e-03
            #           , 'm_cbkg_exp_bin5'  : -2.0610e-03
            #           , 'm_sig_frac'      :  7.4479e-01
            #           , 'm_sig_mean'      :  5.36809e+03
            #           , 'm_sig_sigma_1'   :  6.1690e+00
            #           , 'm_sig_sigma_sf'  :  2.0769e+00
            #          }
            for par in fixedMassPars :
                #par.setVal( parValues[ par.GetName() ][0]\
                #            + ( 3. * parValues[ par.GetName() ][1] if par.GetName().startswith('m_cbkg_exp') else 0. ) )
                #par.setError( parValues[ par.GetName() ][1] )
                #par.setVal( parVals[ par.GetName() ] )
                par.setConstant(True)

        # hack to do fit with fixed shape parameters first
        fixedShapeFit = False
        if fixedShapeFit :
            from P2VV.Imports import parNames, parValues
            fixedMassPars = [ par for par in sWeightMassPdf.Parameters()\
                              if not ( par.getAttribute('Yield') or par.isConstant() or 'Category' in par.ClassName() ) ]
            #parValues = {  'm_sig_mean'      : (  5368.236,    5.47e-02, -1.       )
            #             , 'm_sig_frac'      : (  8.0283e-01,  2.73e-02, -1.       )
            #             , 'm_sig_sigma_1'   : (  6.2728,      1.19e-01, -1.       )
            #             , 'm_sig_sigma_sf'  : (  2.2479,      1.24e-01, -1.       )
            #             , 'm_cbkg_exp'      : ( -1.6249e-03,  9.67e-05, -1.       )
            #            }

            #fixedMassParVals = { }
            for par in fixedMassPars :
                par.setConstant(True)
                #fixedMassParVals[par.GetName()] = ( par.getVal(), par.getError() )
                par.setVal( parValues[par.GetName()][0] )
                par.setError( parValues[par.GetName()][1] )

            massNLL = sWeightMassPdf.createNLL( dataSets['pre'][0] )
            simMassFitResult = sWeightMassPdf.fitTo( dataSets['pre'][0], Save = True, **fitOpts )
            simMassFitResult.PrintSpecial( text = True, LaTeX = True, normal = True, ParNames = parNames )
            massNLLValNom = massNLL.getVal()
            for par in fixedMassPars :
                par.setConstant(False)
                #par.setVal( fixedMassParVals[par.GetName()][0] )
                #par.setError( fixedMassParVals[par.GetName()][1] )

        # determine mass parameters in each subsample with a fit
        print 120 * '='
        print 'P2VV - INFO: createB2CCDataSet: fitting with simultaneous mass PDF'
        simMassFitResult = sWeightMassPdf.fitTo( dataSets['pre'][0], Save = True, **fitOpts )

        from P2VV.Imports import parValues
        simMassFitResult.PrintSpecial( text = True, LaTeX = True, normal = True, ParNames = parNames, ParValues = parValues )
        simMassFitResult.covarianceMatrix().Print()
        simMassFitResult.correlationMatrix().Print()

        # hack to do fit with fixed shape parameters first
        if fixedShapeFit :
            massNLLValThis = massNLL.getVal()
            print '  mass NLL values:'
            print '  nominal: %f;  this: %f; 2*DeltaNLL = %f'\
                  % ( massNLLValNom, massNLLValThis, 2. * ( massNLLValNom - massNLLValThis ) )

        if SWeightsType.endswith( 'Fixed' ) :
            # free parameters that were fixed for mass fit
            print 'P2VV - INFO: createB2CCDataSet: constant parameters in mass fit:'
            for par in fixedMassPars :
                par.Print()
                par.setConstant(False)

    else :
        massPdfPars    = massPdf.getVariables()
        sWeightMassPdf = massPdf


###########################################################################################################################################
## compute sWeights ##
######################

if not simulation :
    print 'P2VV - INFO: createB2CCDataSet: computing sWeights'

    # compute sWeights
    from P2VV.Utilities.SWeights import SData
    sWeightsBuilder = SData( Pdf = sWeightMassPdf, Data = dataSets['pre'][0], Name = 'JpsiKK' )
    dataSets['preS'] = ( sWeightsBuilder.data(), [ ] )

    # import sWeight variables
    weightVars = [ ]
    for wName in [ 'N_sigMass_sw', 'N_cbkgMass_sw', 'N_cbkg2Mass_sw', 'N_cbkg3Mass_sw', 'N_cbkg4Mass_sw' ] :
        ws.put( dataSets['preS'][0].get().find(wName) )
        weightVars.append( RealVar(wName) )

else :
    dataSets['preS'] = ( dataSets['pre'][0], [ ] )


###################################################################################################################################
## add tagging observables to data sets ##
##########################################

if addTaggingObs :
    print 120 * '='
    print 'P2VV - INFO: createB2CCDataSet: building tagging categories'

    # tagging observable names
    wTagOSName   = obsDict['wTagOS_CB_calib'][0]
    wTagSSName   = obsDict['wTagSS_NN_calib'][0]
    tagDecOSName = obsDict['tagDecOS_CB_calib'][0]
    tagDecSSName = obsDict['tagDecSS_NN_calib'][0]

    # get tagging category bins
    from P2VV.Parameterizations.FlavourTagging import getTagCatParamsFromData as getTagParams
    tagBinsOS = getTagParams( dataSets['preS'][0], estWTagName = wTagOSName, tagCats = tagCatsOS, numSigmas = 1., SameSide = False
                             , WeightVarName = '' if simulation else weightVars[0].GetName() )
    tagBinsSS = getTagParams( dataSets['preS'][0], estWTagName = wTagSSName, tagCats = tagCatsSS, numSigmas = 1., SameSide = True
                             , WeightVarName = '' if simulation else weightVars[0].GetName() )

    # add tagging categories to data sets
    from P2VV.Utilities.DataHandling import addTaggingObservables
    addTaggingObservables( dataSets['preS'][0], 'iTagOS', 'tagCatP2VVOS', tagDecOSName, wTagOSName, tagBinsOS )
    addTaggingObservables( dataSets['preS'][0], 'iTagSS', 'tagCatP2VVSS', tagDecSSName, wTagSSName, tagBinsSS )

    observables['iTagOS']       = Category( ws.put( dataSets['preS'][0].get().find('iTagOS')       ).GetName() )
    observables['iTagSS']       = Category( ws.put( dataSets['preS'][0].get().find('iTagSS')       ).GetName() )
    observables['tagCatP2VVOS'] = Category( ws.put( dataSets['preS'][0].get().find('tagCatP2VVOS') ).GetName() )
    observables['tagCatP2VVSS'] = Category( ws.put( dataSets['preS'][0].get().find('tagCatP2VVSS') ).GetName() )
    obsSetNTuple += [ observables['iTagOS'], observables['iTagSS'], observables['tagCatP2VVOS'], observables['tagCatP2VVSS'] ]


###################################################################################################################################
## add track and B momenta to data set ##
#########################################

if addTrackMomenta :
    # add K+, K-, mu+ and mu- momentum magnitudes to data set
    from P2VV.Utilities.DataHandling import addTrackMomenta
    addTrackMomenta( dataSets['preS'][0] )

    observables['Kplus_P']   = RealVar( ws.put( dataSets['preS'][0].get().find('Kplus_P')   ).GetName() )
    observables['Kminus_P']  = RealVar( ws.put( dataSets['preS'][0].get().find('Kminus_P')  ).GetName() )
    observables['eplus_P']  = RealVar( ws.put( dataSets['preS'][0].get().find('eplus_P')  ).GetName() )
    observables['eminus_P'] = RealVar( ws.put( dataSets['preS'][0].get().find('eminus_P') ).GetName() )
    obsSetNTuple += [ observables['Kplus_P'], observables['Kminus_P'], observables['eplus_P'], observables['eminus_P'] ]


###########################################################################################################################################
## create signal and background data sets and print event yields ##
###################################################################

print 120 * '='
print 'P2VV - INFO: createB2CCDataSet: creating data set'

# create data sets with final columns
mainDSList = [ ]
samples = [ ]
obsSetMain = obsSetNTuple + [ var for var in weightVars ]
if splitDataSet :
    # get category states for splitting data set
    states = tuple( [ [ ( cat, observables[cat].GetName(), state.getVal() ) for state in observables[cat] ] for cat in splitDataSet ] )
    from itertools import product
    for state in product(*states) :
        nameStr = '_'.join(  '%s%d'   % ( cState[0], cState[2] ) for cState in state ).replace( '-', 'm' )
        selStr  = '&&'.join( '%s==%d' % ( cState[1], cState[2] ) for cState in state )
        samples.append( ( nameStr, selStr ) )

    # create splitted data sets
    from ROOT import RooDataSet, RooArgSet
    obsSet = RooArgSet( obs._var for obs in obsSetMain )
    mainDS = RooDataSet( 'JpsiKK', 'JpsiKK', obsSet )
    for sample in samples :
        preDS = dataSets['preS'][0].reduce( Cut = sample[1] )
        mainDSList.append( dataTree.buildDataSet( Observables = obsSetMain, Name = 'JpsiKK_' + sample[0], Title = 'JpsiKK'
                                                 , IndexName = 'index', OrigDataSet = preDS ) )
        preDS.IsA().Destructor(preDS)
        mainDS.append( mainDSList[-1] )

else :
    # create data set without splitting
    mainDS = dataTree.buildDataSet( Observables = obsSetMain, Name = 'JpsiKK', Title = 'JpsiKK', IndexName = 'index'
                                , OrigDataSet = dataSets['preS'][0] )

dataSets['main'] = ( mainDS, mainDSList )

if dataSets['preS'][0] : dataSets['preS'][0].IsA().Destructor(dataSets['preS'][0])
if dataSets['pre'][0]  : dataSets['pre'][0].IsA().Destructor(dataSets['pre'][0])
if dataTree            : dataTree.IsA().Destructor(dataTree)
dataSets.pop('pre')
dataSets.pop('preS')
dataTreeFile.Close()
from ROOT import gROOT
gROOT.cd('PyROOT:/')

print 'P2VV - INFO: createB2CCDataSet: produced data set:\n' + ' ' * 13,
dataSets['main'][0].Print()
print

if not simulation :
    # create weighted data sets
    from ROOT import RooArgSet
    obsSets = dict( [ ( var.GetName(), RooArgSet( dataSets['main'][0].get() ) ) for var in weightVars ] )
    if not addSWeights :
        for varName, obsSet in obsSets.iteritems() :
            for var in weightVars :
                if var.GetName() == varName : continue
                obsSet.remove( obsSet.find( var.GetName() ) )

    from ROOT import RooDataSet
    dataSets['sigSWeight']  = ( RooDataSet( 'JpsiKK_sigSWeight',  'JpsiKK_sigSWeight', obsSets['N_sigMass_sw']
                                           , Import = dataSets['main'][0], WeightVar = ( weightVars[0].GetName(), True ) ), [ ] )
    dataSets['cbkgSWeight'] = ( RooDataSet( 'JpsiKK_cbkgSWeight', 'JpsiKK_cbkgSWeight', obsSets['N_cbkgMass_sw']
                                           , Import = dataSets['main'][0], WeightVar = ( weightVars[1].GetName(), True ) ), [ ] )
    dataSets['cbkg2SWeight'] = ( RooDataSet( 'JpsiKK_cbkg2SWeight', 'JpsiKK_cbkg2SWeight', obsSets['N_cbkg2Mass_sw']
                                           , Import = dataSets['main'][0], WeightVar = ( weightVars[2].GetName(), True ) ), [ ] )
    dataSets['cbkg3SWeight'] = ( RooDataSet( 'JpsiKK_cbkg3SWeight', 'JpsiKK_cbkg3SWeight', obsSets['N_cbkg3Mass_sw']
                                           , Import = dataSets['main'][0], WeightVar = ( weightVars[3].GetName(), True ) ), [ ] )
    dataSets['cbkg4SWeight'] = ( RooDataSet( 'JpsiKK_cbkg4SWeight', 'JpsiKK_cbkg4SWeight', obsSets['N_cbkg4Mass_sw']
                                           , Import = dataSets['main'][0], WeightVar = ( weightVars[4].GetName(), True ) ), [ ] )
    for sample, data in zip( samples, dataSets['main'][1] ) :
        dataSets['sigSWeight'][1].append(  RooDataSet( 'JpsiKK_sigSWeight_'  + sample[0], 'JpsiKK_sigSWeight', obsSets['N_sigMass_sw']
                                                      , Import = data, WeightVar = ( weightVars[0].GetName(), True ) ) )
        dataSets['cbkgSWeight'][1].append( RooDataSet( 'JpsiKK_cbkgSWeight_' + sample[0], 'JpsiKK_cbkgSWeight', obsSets['N_cbkgMass_sw']
                                                      , Import = data, WeightVar = ( weightVars[1].GetName(), True ) ) )
        dataSets['cbkg2SWeight'][1].append( RooDataSet( 'JpsiKK_cbkg2SWeight_' + sample[0], 'JpsiKK_cbkg2SWeight', obsSets['N_cbkg2Mass_sw']
                                                      , Import = data, WeightVar = ( weightVars[2].GetName(), True ) ) )
        dataSets['cbkg3SWeight'][1].append( RooDataSet( 'JpsiKK_cbkg3SWeight_' + sample[0], 'JpsiKK_cbkg3SWeight', obsSets['N_cbkg3Mass_sw']
                                                      , Import = data, WeightVar = ( weightVars[3].GetName(), True ) ) )
        dataSets['cbkg4SWeight'][1].append( RooDataSet( 'JpsiKK_cbkg4SWeight_' + sample[0], 'JpsiKK_cbkg4SWeight', obsSets['N_cbkg4Mass_sw']
                                                      , Import = data, WeightVar = ( weightVars[4].GetName(), True ) ) )


    print 'P2VV - INFO: createB2CCDataSet: signal data set:\n' + ' ' * 13,
    dataSets['sigSWeight'][0].Print()
    print
    print 'P2VV - INFO: createB2CCDataSet: combinatorial background data set:\n' + ' ' * 13,
    dataSets['cbkgSWeight'][0].Print()
    print
    print 'P2VV - INFO: createB2CCFitNTuple: partially reconstructed background 2 data set:\n' + ' ' * 13,
    dataSets['cbkg2SWeight'][0].Print()
    print
    print 'P2VV - INFO: createB2CCFitNTuple: partially reconstructed background 3 data set:\n' + ' ' * 13,
    dataSets['cbkg3SWeight'][0].Print()
    print

    # print yields
    print 'P2VV - INFO: createB2CCDataSet: event yields:'
    allCats = [ dataSets['main'][0].get().find( obsDict['runPeriod'][0] ) ] if runPeriods else [ ]
    allCats += [  dataSets['main'][0].get().find( obsDict['hlt1B'][0] )
                , dataSets['main'][0].get().find( obsDict['hlt2B'][0] )
               ]
    if len(KKMassBinBounds) > 2 : allCats.append( dataSets['main'][0].get().find( observables['KKMassCat'].GetName() ) )
    allCats = [ cat for cat in allCats if cat ]

    from P2VV.Utilities.DataHandling import printEventYields, printEventYieldsData
    printEventYields(  ParameterSet        = massPdfPars
                     , YieldNames          = yieldNames
                     , SplittingCategories = [ cat for catList in splitCats for cat in catList ]
                    )
    printEventYieldsData(  FullDataSet         = dataSets['main'][0]
                         , WeightedDataSets    = [ dataSets[name][0] for name in [ 'sigSWeight', 'cbkgSWeight', 'cbkg2SWeight', 'cbkg3SWeight' ] ]
                         , DataSetNames        = [ 'Signal', 'Comb background', 'Part reconst background 2', 'Part reconst background 3' ]
                         , SplittingCategories = allCats
                        )

if addTaggingObs :
    # print tagging categories distributions for signal and background
    sigDataName = 'main' if simulation else 'sigSWeight'
    from P2VV.RooFitWrappers import ArgSet
    print 'P2VV - INFO: createB2CCDataSet: distribution in opposite side tagging category for signal:'
    dataSets[sigDataName][0].table(  ArgSet( 'sigOSTagSet',  [ observables['tagCatP2VVOS'], observables['iTagOS'] ] ) ).Print('v')
    if not simulation and 'cbkgSWeight' in savedObjects :
        print 'P2VV - INFO: createB2CCDataSet: distribution in opposite side tagging category for combinatorial background:'
        dataSets['cbkgSWeight'][0].table( ArgSet( 'cbkgOSTagSet', [ observables['tagCatP2VVOS'], observables['iTagOS'] ] ) ).Print('v')
    if not simulation and 'cbkg2SWeight' in savedObjects :
        print 'P2VV - INFO: createB2CCDataSet: distribution in opposite side tagging category for part reconst background 2:'
        dataSets['cbkg2SWeight'][0].table( ArgSet( 'cbkg2OSTagSet', [ observables['tagCatP2VVOS'], observables['iTagOS'] ] ) ).Print('v')
    if not simulation and 'cbkg3SWeight' in savedObjects :
        print 'P2VV - INFO: createB2CCDataSet: distribution in opposite side tagging category for part reconst background 3:'
        dataSets['cbkg3SWeight'][0].table( ArgSet( 'cbkg3OSTagSet', [ observables['tagCatP2VVOS'], observables['iTagOS'] ] ) ).Print('v')
    print 'P2VV - INFO: createB2CCDataSet: distribution in same side tagging category for signal:'
    dataSets[sigDataName][0].table(  ArgSet( 'sigSSTagSet',  [ observables['tagCatP2VVSS'], observables['iTagSS'] ] ) ).Print('v')
    if not simulation and 'cbkgSWeight' in savedObjects :
        print 'P2VV - INFO: createB2CCDataSet: distribution in same side tagging category for combinatorial background:'
        dataSets['cbkgSWeight'][0].table( ArgSet( 'cbkgSSTagSet', [ observables['tagCatP2VVSS'], observables['iTagSS'] ] ) ).Print('v')
    if not simulation and 'cbkg2SWeight' in savedObjects :
        print 'P2VV - INFO: createB2CCDataSet: distribution in same side tagging category for part reconst background 2:'
        dataSets['cbkg2SWeight'][0].table( ArgSet( 'cbkg2SSTagSet', [ observables['tagCatP2VVSS'], observables['iTagSS'] ] ) ).Print('v')
    if not simulation and 'cbkg3SWeight' in savedObjects :
        print 'P2VV - INFO: createB2CCDataSet: distribution in same side tagging category for part reconst background 3:'
        dataSets['cbkg3SWeight'][0].table( ArgSet( 'cbkg3SSTagSet', [ observables['tagCatP2VVSS'], observables['iTagSS'] ] ) ).Print('v')


###########################################################################################################################################
## make J/psiKK mass plots ##
#############################

if not simulation and plotsFilePath :
    print 120 * '='
    print 'P2VV - INFO: createB2CCDataSet: plotting J/psiKK invariant mass distribution'

    # import plotting tools
    from P2VV.Utilities.Plotting import plot
    from ROOT import TCanvas, kBlue, kRed, kGreen, kMagenta, kViolet, kOrange, kFullDotLarge, TPaveText
    from P2VV.Utilities.Plotting import _P2VVPlotStash

    LHCbLabel = TPaveText( 0.24, 0.81, 0.37, 0.89, 'BRNDC' )
    LHCbLabel.AddText('LHCb')
    LHCbLabel.SetFillColor(0)
    LHCbLabel.SetTextAlign(12)
    LHCbLabel.SetTextSize(0.072)
    LHCbLabel.SetBorderSize(0)
    _P2VVPlotStash.append(LHCbLabel)

    if SWeightsType.startswith('simultaneous') and (runPeriods or triggerSel in ['paper2012', 'timeEffFit'] or len(KKMassBinBounds) > 2) :
        # create projection data set
        indexCat = sWeightMassPdf.indexCat()
        if indexCat.isFundamental() :
            projWDataSet = [ indexCat ]
        else :
            projWDataSet = [ cat for cat in indexCat.getObservables( dataSets['main'][0] ) ]

        projWData = dict( ProjWData = ( dataSets['main'][0].reduce( ArgSet = projWDataSet ), False ) )
        print 'P2VV - INFO: createB2CCDataSet: projection data set for J/psiKK mass plots:'
        projWData['ProjWData'][0].Print()

    else :
        # don't use projection data set
        projWData = dict()

    # plot J/psiKK mass distributions
    massCanvs = [  TCanvas( 'massCanvLog',     'B mass logarithmic scale'  )
                 , TCanvas( 'massCanvSig',     'B mass signal range'       )
                 , TCanvas( 'massCanvLeft',    'B mass left side band'     )
                 , TCanvas( 'massCanvRight',   'B mass right side band'    )
                 , TCanvas( 'massCanvPeakBkg', 'B mass peaking background' )
                ]
    for index, ( pad, frameRange, nBins, plotTitle, plotName, logy, scale, yTitleOffset, markSize, markLineWidth )\
          in enumerate ( zip(  massCanvs
                             , [ '', 'Signal', 'LeftSideBand', 'RightSideBand', 'PeakBkg' ]
                             , numMassBins
                             , [  obsDict['mass'][1]
                                , obsDict['mass'][1] + ' mass fit - signal'
                                , obsDict['mass'][1] + ' mass fit - left side band'
                                , obsDict['mass'][1] + ' mass fit - right side band'
                                , obsDict['mass'][1] + ' mass fit - peaking background'
                               ]
                             , [  obsDict['mass'][0]
                                , obsDict['mass'][0] + ' fit - signal'
                                , obsDict['mass'][0] + ' fit - left side band'
                                , obsDict['mass'][0] + ' fit - right side band'
                                , obsDict['mass'][0] + ' fit - peaking background'
                               ]
                             , [ True, False, False, False, False ]
                             , [ massLogPlotRange, ( None, None ), ( None, None ), ( None, None ), ( None, None ) ]
                             , [ 1.00, 1.20, 1.15, 1.15, 1.15 ]
                             , [ 0.6,  0.7,  0.8,  0.8,  0.8  ]
                             , [ 2,    3,    3,    3,    3    ]
                       ) ) :
        pad.SetLeftMargin(0.18)
        pad.SetRightMargin(0.05)
        pad.SetBottomMargin(0.18)
        pad.SetTopMargin(0.05)

        binWidth = ( observables['mass'].getMax(frameRange) - observables['mass'].getMin(frameRange) ) / float(nBins)
        plot(  pad, observables['mass'], dataSets['main'][0], sWeightMassPdf, logy = logy, yScale = scale
             , xTitle = 'm(J/#psi K^{+}K^{-}) [MeV/c^{2}]', yTitle = 'Candidates / (%.1f MeV/c^{2})' % binWidth
             , xTitleOffset = 1.10, yTitleOffset = yTitleOffset
             , plotResidHist = 'E3', normalize = True, symmetrize = True
             , frameOpts  = dict( Range = frameRange, Bins = nBins, Title = plotTitle, Name = plotName )
             , dataOpts   = dict( MarkerStyle = kFullDotLarge, MarkerSize = markSize, LineWidth = markLineWidth )
             , pdfOpts    = dict( list( projWData.items() ), LineColor = kBlue, LineWidth = 3, Precision = 1.e-4 )
             , components = {  'sig*'  : dict( LineColor = kRed,       LineStyle = 7, LineWidth = 3 )
                             , 'cbkg*' : dict( LineColor = kGreen + 3, LineStyle = 9, LineWidth = 3 )
                             , 'cbkg2*' : dict( LineColor = kMagenta, LineStyle = 4, LineWidth = 3 )
                             , 'cbkg3*' : dict( LineColor = kViolet - 3, LineStyle = 5, LineWidth = 3 )
                             , 'cbkg4*' : dict( LineColor = kOrange - 3, LineStyle = 6, LineWidth = 3 )
                            }
            )
        if index < 2 :
            pad.cd()
            LHCbLabel.Draw()

    if SWeightsType.startswith('simultaneous') and ( triggerSel in ['paper2012', 'timeEffFit'] or len(KKMassBinBounds) > 2 ) :
        # get simultaneous PDFs
        indexCatIter  = indexCat.typeIterator()
        indexCatState = indexCatIter.Next()
        bins = [ ]
        pdfs = [ ]
        while indexCatState :
            indexCat.setIndex( indexCatState.getVal() )
            bins.append( [ ( indexCat.GetName(), indexCatState.getVal(), indexCatState.GetName() ) ] )
            if indexCat.isFundamental() :
                bins[-1].append( bins[-1][0] )
            else :
                for cat in indexCat.getObservables( dataSets['main'][0] ) :
                    bins[-1].append( ( cat.GetName(), cat.getIndex(), cat.getLabel() ) )

            pdfs.append( sWeightMassPdf.getPdf( indexCatState.GetName() ) )
            indexCatState = indexCatIter.Next()

        # plot mumuKK mass distributions in KK mass bins
        if   len(bins) <= 4 : nPads = ( 2, 2 )
        elif len(bins) <= 6 : nPads = ( 3, 2 )
        elif len(bins) <= 9 : nPads = ( 3, 3 )
        else :                nPads = ( 4, 3 )
        massCanvs.append( TCanvas( 'massCanvSigBins', 'B mass signal range bins' ) )
        for ( pad, pdf, plotTitle, dataCuts, norm )\
                in zip(  massCanvs[-1].pads( nPads[0], nPads[1] )
                       , pdfs
                       , [ observables['mass'].GetTitle() + ' bin %d - signal' % bin[0][1] for bin in bins ]
                       , [ dict( Cut = ' && '.join( '%s==%d' % ( c[0], c[1] ) for c in bin[ 1 : ] ) ) for bin in bins ]
                       , [ dataSets['main'][0].sumEntries( ' && '.join( '%s==%d' % ( c[0], c[1] ) for c in bin[ 1 : ] ) )\
                           / dataSets['main'][0].sumEntries() for bin in bins ]
                      ) :
            plot(  pad, observables['mass'], dataSets['main'][0], pdf#, logy = True, yScale = ( 1., None )
                 , frameOpts  = dict( Range = 'Signal', Bins = numMassBins[0], Title = plotTitle )
                 , dataOpts   = dict( MarkerStyle = kFullDotLarge, MarkerSize = 0.4, **dataCuts  )
                 , pdfOpts    = dict( LineColor = kBlue, LineWidth = 3, Normalization = norm     )
                 , components = {  'sig*'  : dict( LineColor = kRed,       LineStyle = 7 )
                                 , 'cbkg*' : dict( LineColor = kGreen + 3, LineStyle = 9 )
                                 , 'cbkg2*' : dict( LineColor = kMagenta, LineStyle = 4 )
                                 , 'cbkg3*' : dict( LineColor = kViolet - 3, LineStyle = 5 )
                                 , 'cbkg4*' : dict( LineColor = kOrange - 3, LineStyle = 6 )
                                }
                )

        massCanvs.append( TCanvas( 'massCanvLeftBins', 'B mass left side band bins' ) )
        for ( pad, pdf, plotTitle, dataCuts, norm )\
                in zip(  massCanvs[-1].pads( nPads[0], nPads[1] )
                       , pdfs
                       , [ observables['mass'].GetTitle() + ' bin %d - left side band' % bin[0][1] for bin in bins ]
                       , [ dict( Cut = ' && '.join( '%s==%d' % ( c[0], c[1] ) for c in bin[ 1 : ] ) ) for bin in bins ]
                       , [ dataSets['main'][0].sumEntries( ' && '.join( '%s==%d' % ( c[0], c[1] ) for c in bin[ 1 : ] ) )\
                           / dataSets['main'][0].sumEntries() for bin in bins ]
                      ) :
            plot(  pad, observables['mass'], dataSets['main'][0], pdf#, logy = True, yScale = ( 1., None )
                 , frameOpts  = dict( Range = 'LeftSideBand', Bins = numMassBins[1], Title = plotTitle )
                 , dataOpts   = dict( MarkerStyle = kFullDotLarge, MarkerSize = 0.4, **dataCuts        )
                 , pdfOpts    = dict( LineColor = kBlue, LineWidth = 3, Normalization = norm      )
                 , components = {  'sig*'  : dict( LineColor = kRed,       LineStyle = 7 )
                                 , 'cbkg*' : dict( LineColor = kGreen + 3, LineStyle = 9 )
                                 , 'cbkg2*' : dict( LineColor = kMagenta, LineStyle = 4 )
                                 , 'cbkg3*' : dict( LineColor = kViolet - 3, LineStyle = 5 )
                                 , 'cbkg4*' : dict( LineColor = kOrange - 3, LineStyle = 6 )
                                }
                )

        massCanvs.append( TCanvas( 'massCanvRightBins', 'B mass right side band bins' ) )
        for ( pad, pdf, plotTitle, dataCuts, norm )\
                in zip(  massCanvs[-1].pads( nPads[0], nPads[1] )
                       , pdfs
                       , [ observables['mass'].GetTitle() + ' bin %d - right side band' % bin[0][1] for bin in bins ]
                       , [ dict( Cut = ' && '.join( '%s==%d' % ( c[0], c[1] ) for c in bin[ 1 : ] ) ) for bin in bins ]
                       , [ dataSets['main'][0].sumEntries( ' && '.join( '%s==%d' % ( c[0], c[1] ) for c in bin[ 1 : ] ) )\
                           / dataSets['main'][0].sumEntries() for bin in bins ]
                      ) :
            plot(  pad, observables['mass'], dataSets['main'][0], pdf#, logy = True, yScale = ( 1., None )
                 , frameOpts  = dict( Range = 'RightSideBand', Bins = numMassBins[2], Title = plotTitle )
                 , dataOpts   = dict( MarkerStyle = kFullDotLarge, MarkerSize = 0.4, **dataCuts         )
                 , pdfOpts    = dict( LineColor = kBlue, LineWidth = 3, Normalization = norm      )
                 , components = {  'sig*'  : dict( LineColor = kRed,       LineStyle = 7 )
                                 , 'cbkg*' : dict( LineColor = kGreen + 3, LineStyle = 9 )
                                 , 'cbkg2*' : dict( LineColor = kMagenta, LineStyle = 4 )
                                 , 'cbkg3*' : dict( LineColor = kViolet - 3, LineStyle = 5 )
                                }
                )

    # plot sWeights
    massCanvs += [ TCanvas('sWeightsAll'), TCanvas('sWeightsSignal') ]
    for canv in massCanvs[ -2 : ] :
        canv.SetLeftMargin(0.18)
        canv.SetRightMargin(0.05)
        canv.SetBottomMargin(0.18)
        canv.SetTopMargin(0.05)

    allMassVals = [ ]
    sigMassVals = [ ]
    allSWeights = [ ]
    sigSWeights = [ ]
    for obsSet in dataSets['main'][0] :
        allMassVals.append( obsSet.getRealValue( obsDict['mass'][0] ) )
        allSWeights.append( obsSet.getRealValue( weightVars[0].GetName() ) )
        if obsSet.find( obsDict['mass'][0] ).inRange('Signal') :
            sigMassVals.append( obsSet.getRealValue( obsDict['mass'][0] ) )
            sigSWeights.append( obsSet.getRealValue( weightVars[0].GetName() ) )

    from array import array
    allMassArr = array( 'd', allMassVals )
    sigMassArr = array( 'd', sigMassVals )
    allSWArr   = array( 'd', allSWeights )
    sigSWArr   = array( 'd', sigSWeights )

    from ROOT import TGraph
    allSWeights = TGraph( len(allMassArr), allMassArr, allSWArr )
    sigSWeights = TGraph( len(sigMassArr), sigMassArr, sigSWArr )
    for graph, range in zip( [ allSWeights, sigSWeights ], [ '', 'Signal' ] ) :
        graph.SetMarkerStyle(kFullDotLarge)
        graph.SetMarkerSize(0.2)
        graph.SetMarkerColor(kBlue)
#    for graph, range in zip( [ allSWeights], [ '' ] ) :
#        graph.SetMarkerStyle(kFullDotLarge)
#        graph.SetMarkerSize(0.2)
#        graph.SetMarkerColor(kBlue)
#    for graph2, range in zip( [ sigSWeights ], [ 'Signal' ] ) :
#        graph2.SetMarkerStyle(kFullDotLarge)
#        graph2.SetMarkerSize(0.2)
#        graph2.SetMarkerColor(kRed)

        #graph.SetMinimum(-0.55)
        #graph.SetMaximum(1.15)
        graph.GetXaxis().SetLimits( observables['mass'].getMin(range), observables['mass'].getMax(range) )
        graph.GetXaxis().SetTitle('m(J/#psi K^{+}K^{-}) [MeV/c^{2}]')
        graph.GetYaxis().SetTitle('sWeight')
        graph.GetXaxis().SetTitleOffset(1.1)
        graph.GetYaxis().SetTitleOffset(1.0)

    from ROOT import TLine
    allZeroLine = TLine( allSWeights.GetXaxis().GetXmin(), 0., allSWeights.GetXaxis().GetXmax(), 0. )
    sigZeroLine = TLine( sigSWeights.GetXaxis().GetXmin(), 0., sigSWeights.GetXaxis().GetXmax(), 0. )

    massCanvs[-2].cd()
    allSWeights.Draw('AP')
    allZeroLine.Draw()
    massCanvs[-1].cd()
    sigSWeights.Draw('AP')
    sigZeroLine.Draw()

    for it, canv in enumerate(massCanvs) :
        canv.Print( plotsFilePath + ( '(' if it == 0 else ')' if it == len(massCanvs) - 1 else '' ) )


###########################################################################################################################################
## store data sets in ROOT file ##
##################################

if createRangeData :
    # create signal and background data sets with side band ranges
    dataSets['sigRange']  = dataSets['main'][0].reduce( Name = 'JpsiKK_sigRange',  Title = 'JpsiKK_sigRange',  CutRange = 'Signal'       )
    dataSets['cbkgRange'] = dataSets['main'][0].reduce( Name = 'JpsiKK_cbkgRange', Title = 'JpsiKK_cbkgRange', CutRange = 'LeftSideBand' )
    dataSets['cbkgRange'].append( dataSets['main'][0].reduce( CutRange = 'RightSideBand' ) )
    dataSets['cbkg2Range'] = dataSets['main'][0].reduce( Name = 'JpsiKK_cbkg2Range', Title = 'JpsiKK_cbkg2Range', CutRange = 'LeftSideBand' )
    dataSets['cbkg3Range'] = dataSets['main'][0].reduce( Name = 'JpsiKK_cbkg3Range', Title = 'JpsiKK_cbkg3Range', CutRange = 'LeftSideBand' )
    savedObjects += [ 'sigRange', 'cbkgRange', 'cbkg2Range', 'cbkg3Range' ]

if createNTuple :
    # create n-tuple containing signal and background weights
    dataSets['sigTree'] = dataSets['sigSWeight'][0].buildTree( Name = nTupleName, Title = nTupleName, WeightName = sWeightName
                                                              , RooFitFormat = False )
    savedObjects += [ 'sigTree' ]

# save data sets to file
print 120 * '='
print 'P2VV - INFO: createB2CCDataSet: saving data sets to ROOT file %s:' % dataSetsFilePath
from ROOT import TFile
dataSetsFile = TFile.Open( dataSetsFilePath, 'UPDATE' if appendToFile else 'RECREATE' )

for dataKey, data in dataSets.iteritems() :
    print
    if hasattr( data, 'ClassName' ) and data.ClassName() == 'TTree' :
        # data in TTree
        print 'TTree::%s[%s] = %d entries'\
              % (  data.GetName(), ','.join( br.GetName() for br in data.GetListOfBranches() ), data.GetEntries() )
        if dataKey in savedObjects : dataSetsFile.Append(data)

    else :
        # data in RooDataSet(s)
        if not data[1] :
            data[0].Print()
            if dataKey in savedObjects :
                if data[0].numEntries() > 0 :
                    dataSetsFile.Append(data[0])
                else :
                    print 'P2VV - INFO: createB2CCDataSet: no entries in "%s", not saving data set' % data[0].GetName()
        for subData in data[1] :
            print
            subData.Print()
            if dataKey in savedObjects :
                if subData.numEntries() > 0 :
                    dataSetsFile.Append(subData)
                else :
                    print 'P2VV - INFO: createB2CCDataSet: no entries in "%s", not saving data set' % subData.GetName()

dataSetsFile.Write()
dataSetsFile.Close()

###########################################################################################################################################
## store n-tuple in ROOT file ##
################################

print 120 * '='

# create n-tuple containing signal and background weights
sigTree = dataSets['sigSWeight'][0].buildTree( Name = nTupleName, Title = nTupleName, WeightName = sWeightName, RooFitFormat = False )
print 'P2VV - INFO: createB2CCFitNTuple: n-tuple:'
print 'TTree::%s[%s] = %d entries'\
      % (  sigTree.GetName(), ','.join( br.GetName() for br in sigTree.GetListOfBranches() ), sigTree.GetEntries() )

# save n-tuple to file
print 'P2VV - INFO: createB2CCFitNTuple: saving n-tuple to ROOT file %s' % dataSetsFilePath2
from ROOT import TFile
dataSetsFile2 = TFile.Open( dataSetsFilePath2, 'UPDATE' if appendToFile else 'RECREATE' )
dataSetsFile2.Append(sigTree)
dataSetsFile2.Write()
dataSetsFile2.Close()

