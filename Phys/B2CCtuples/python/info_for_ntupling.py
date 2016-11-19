# Information to be compared with
# /afs/cern.ch/user/b/bdey/cmtuser/bs2JpsiKK/bs2JpsiKK_Data_2015.py
# and 
# https://gitlab.cern.ch/LHCb-SVN-mirrors/Urania/blob/master/Phys/B2CCtuples/python/Bs2JpsiPhi_MAKER_RealData_Run2.py

#############
### J/Psi ###
#############

## StdMassConstrainedJpsi2MuMu (for BetaSBs2JpsiPhi{Detached,Prescaled}Line):

StdMassConstrainedJpsi2MuMu.DecayDescriptor = "J/psi(1S) -> mu+ mu-"
StdMassConstrainedJpsi2MuMu.DaughtersCuts = { 'mu+' : '(PIDmu > 0) & (PT > 0.5*GeV)' }
StdMassConstrainedJpsi2MuMu.CombinationCut = "(ADAMASS('J/psi(1S)') < 150.*MeV) & (ADOCACHI2CUT(20, ''))"
StdMassConstrainedJpsi2MuMu.MotherCut = "(VFASPF(VCHI2) < 16.) & (MFIT)"

## StdLooseJpsi2MuMu (for FullDSTDiMuonJpsi2MuMuDetachedLine):

StdLooseJpsi2MuMu.DecayDescriptor = "J/psi(1S) -> mu+ mu-"
StdLooseJpsi2MuMu.CombinationCut = "(ADAMASS('J/psi(1S)') < 100.*MeV) & (ADOCACHI2CUT(30,''))"
StdLooseJpsi2MuMu.MotherCut = "(VFASPF(VCHI2) < 25.)"

## StdAllLooseMuons:

fltr = protoFilter ( algorithm , ProtoParticleMUONFilter, 'Muon' )
fltr.Selection = [ "RequiresDet='MUON' IsMuon=True" ]

#################
### Phi(1020) ###
#################

## PhiList: 

Cuts = "(in_range(980,M,1050))"\
       "& (PT > 500.*MeV)"\
       "& (VFASPF(VCHI2) < 25)"\
       "& (MAXTREE('K+'==ABSID, TRCHI2DOF) < 5 )"\
       "& (MINTREE('K+'==ABSID, PIDK) > 0)"

## StdLoosePhi2KK: 

StdLoosePhi2KK.DecayDescriptor = "phi(1020) -> K+ K-"
StdLoosePhi2KK.CombinationCut = "(AM < 1100.*MeV) & (ADOCACHI2CUT(30, ''))"
StdLoosePhi2KK.MotherCut = "(VFASPF(VCHI2) < 25.0)"

## StdAllLooseKaons:

fltr = protoFilter ( algorithm , ProtoParticleCALOFilter, 'Kaon' )
fltr.Selection = [ "RequiresDet='RICH' CombDLL(k-pi)>'-5.0'" ]

###############################################
### BetaSBs2JpsiPhi{Detached,Prescaled}Line ###
###############################################

PreVertexCuts = "in_range(5050,AM,5650)"
PostVertexCuts = "in_range(5150,M,5550) & (VFASPF(VCHI2PDOF) < 20)" 

## Prescaled line:

HLT2Cuts = Hlt2DiMuonJPsiDecision
Prescale = 1.0

### Hlt2DiMuonJPsiDecision:

'DiMuon' + 'JPsi' :        {'MinMass'    :  2900 * MeV,
                            'VertexChi2' :    25,
                            'MassWindow' :   120 * MeV}

## Detached line:      

Cuts = "(CHILD('Beauty -> ^J/psi(1S) X', PFUNA(ADAMASS('J/psi(1S)'))) < 80*MeV)"\
       "& (BPVLTIME() > 0.2*ps)"

##########################################
### FullDSTDiMuonJpsi2MuMuDetachedLine ###
##########################################

# https://gitlab.cern.ch/lhcb/Stripping/blob/master/Phys/StrippingSelections/python/StrippingSelections/StrippingBandQ/StrippingDiMuonInherit.py

"MuonPt"        : "MINTREE('mu+'==ABSID,PT) > 500.0 *MeV",
"Mass"          : "(MM > 2996.916) & (MM < 3196.916)",
"Detachement"   : "((BPVDLS>3) | (BPVDLS<-3))",
"MuonPIDmu"     : "MINTREE('mu+'==ABSID,PIDmu) > 0.0",
"JpsiVtx"       : "VFASPF(VCHI2PDOF)< 20.0"

