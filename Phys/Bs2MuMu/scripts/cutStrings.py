# Cuts for trigger efficiency calculation in massFit.py
#Trigger lines for Bu
Bu_L0_Dec = '&&BplusL0Global_Dec==1'
Bu_L0_TIS = '&&BplusL0Global_TIS==1'
Bu_L0_TOS = '&&BplusL0Global_TOS==1'
Bu_Hlt1_Dec = '&&BplusHlt1Phys_Dec==1'
Bu_Hlt1_TIS = '&&BplusHlt1Phys_TIS==1'
Bu_Hlt1_TOS = '&&BplusHlt1Phys_TOS==1'
Bu_Hlt2_Dec = '&&BplusHlt2Phys_Dec==1'
Bu_Hlt2_TIS = '&&BplusHlt2Phys_TIS==1'
Bu_Hlt2_TOS = '&&BplusHlt2Phys_TOS==1'


L0_Dec = '&&(BplusL0MuonDecision_Dec==1||BplusL0DiMuonDecision_Dec==1||BplusL0HadronDecision_Dec==1||BplusL0ElectronDecision_Dec==1||BplusL0ElectronHiDecision_Dec==1||BplusL0PhotonDecision_Dec==1||BplusL0PhotonHiDecision_Dec==1)'	
L0_TIS = '&&(BplusL0MuonDecision_TIS==1||BplusL0DiMuonDecision_TIS==1||BplusL0HadronDecision_TIS==1||BplusL0ElectronDecision_TIS==1||BplusL0ElectronHiDecision_TIS==1||BplusL0PhotonDecision_TIS==1||BplusL0PhotonHiDecision_TIS==1)'	
L0_TOS = '&&(BplusL0MuonDecision_TOS==1||BplusL0DiMuonDecision_TOS==1||BplusL0HadronDecision_TOS==1||BplusL0ElectronDecision_TOS==1||BplusL0ElectronHiDecision_TOS==1||BplusL0PhotonDecision_TOS==1||BplusL0PhotonHiDecision_TOS==1)'	

Hlt1_Dec = '&&(BplusHlt1SingleMuonHighPTDecision_Dec==1||BplusHlt1SingleElectronNoIPDecision_Dec==1||BplusHlt1TrackAllL0Decision_Dec==1||BplusHlt1TrackMuonDecision_Dec==1||BplusHlt1TrackPhotonDecision_Dec==1||BplusHlt1DiMuonLowMassDecision_Dec==1||BplusHlt1DiMuonHighMassDecision_Dec==1)'
Hlt1_TIS = '&&(BplusHlt1SingleMuonHighPTDecision_TIS==1||BplusHlt1SingleElectronNoIPDecision_TIS==1||BplusHlt1TrackAllL0Decision_TIS==1||BplusHlt1TrackMuonDecision_TIS==1||BplusHlt1TrackPhotonDecision_TIS==1||BplusHlt1DiMuonLowMassDecision_TIS==1||BplusHlt1DiMuonHighMassDecision_TIS==1)'
Hlt1_TOS = '&&(BplusHlt1SingleMuonHighPTDecision_TOS==1||BplusHlt1SingleElectronNoIPDecision_TOS==1||BplusHlt1TrackAllL0Decision_TOS==1||BplusHlt1TrackMuonDecision_TOS==1||BplusHlt1TrackPhotonDecision_TOS==1||BplusHlt1DiMuonLowMassDecision_TOS==1||BplusHlt1DiMuonHighMassDecision_TOS==1)'

Hlt2_Dec = '&&(BplusHlt2SingleMuonDecision_Dec==1||BplusHlt2SingleMuonHighPTDecision_Dec==1||BplusHlt2DiMuonJPsiDecision_Dec==1||BplusHlt2DiMuonJPsiHighPTDecision_Dec==1||BplusHlt2DiMuonPsi2SDecision_Dec==1||BplusHlt2DiMuonDetachedDecision_Dec==1||BplusHlt2DiMuonDetachedJPsiDecision_Dec==1||BplusHlt2DiMuonDetachedHeavyDecision_Dec==1||BplusHlt2TriMuonTauDecision_Dec==1||BplusHlt2B2HHDecision_Dec==1||BplusHlt2DiMuonBDecision_Dec==1||BplusHlt2DiMuonZDecision_Dec==1||BplusHlt2TopoMu2BodyBBDTDecision_Dec==1||BplusHlt2TopoMu3BodyBBDTDecision_Dec==1||BplusHlt2TopoMu4BodyBBDTDecision_Dec==1||BplusHlt2Topo2BodyBBDTDecision_Dec==1||BplusHlt2Topo3BodyBBDTDecision_Dec==1||BplusHlt2Topo4BodyBBDTDecision_Dec==1||BplusHlt2Topo2BodySimpleDecision_Dec==1||BplusHlt2Topo3BodySimpleDecision_Dec==1||BplusHlt2IncPhiDecision_Dec==1||BplusHlt2TopoE__Decision_Dec==1||BplusHlt2Topo__Decision_Dec==1||BplusHlt2Charm__Decision_Dec==1||BplusHlt2DiElectron__Decision_Dec==1||BplusHlt2__GammaDecision_Dec==1)'

Hlt2_TIS = '&&(BplusHlt2SingleMuonDecision_TIS==1||BplusHlt2SingleMuonHighPTDecision_TIS==1||BplusHlt2DiMuonJPsiDecision_TIS==1||BplusHlt2DiMuonJPsiHighPTDecision_TIS==1||BplusHlt2DiMuonPsi2SDecision_TIS==1||BplusHlt2DiMuonDetachedDecision_TIS==1||BplusHlt2DiMuonDetachedJPsiDecision_TIS==1||BplusHlt2DiMuonDetachedHeavyDecision_TIS==1||BplusHlt2TriMuonTauDecision_TIS==1||BplusHlt2B2HHDecision_TIS==1||BplusHlt2DiMuonBDecision_TIS==1||BplusHlt2DiMuonZDecision_TIS==1||BplusHlt2TopoMu2BodyBBDTDecision_TIS==1||BplusHlt2TopoMu3BodyBBDTDecision_TIS==1||BplusHlt2TopoMu4BodyBBDTDecision_TIS==1||BplusHlt2Topo2BodyBBDTDecision_TIS==1||BplusHlt2Topo3BodyBBDTDecision_TIS==1||BplusHlt2Topo4BodyBBDTDecision_TIS==1||BplusHlt2Topo2BodySimpleDecision_TIS==1||BplusHlt2Topo3BodySimpleDecision_TIS==1||BplusHlt2IncPhiDecision_TIS==1||BplusHlt2TopoE__Decision_TIS==1||BplusHlt2Topo__Decision_TIS==1||BplusHlt2Charm__Decision_TIS==1||BplusHlt2DiElectron__Decision_TIS==1||BplusHlt2__GammaDecision_TIS==1)'

Hlt2_TOS = '&&(BplusHlt2SingleMuonDecision_TOS==1||BplusHlt2SingleMuonHighPTDecision_TOS==1||BplusHlt2DiMuonJPsiDecision_TOS==1||BplusHlt2DiMuonJPsiHighPTDecision_TOS==1||BplusHlt2DiMuonPsi2SDecision_TOS==1||BplusHlt2DiMuonDetachedDecision_TOS==1||BplusHlt2DiMuonDetachedJPsiDecision_TOS==1||BplusHlt2DiMuonDetachedHeavyDecision_TOS==1||BplusHlt2TriMuonTauDecision_TOS==1||BplusHlt2B2HHDecision_TOS==1||BplusHlt2DiMuonBDecision_TOS==1||BplusHlt2DiMuonZDecision_TOS==1||BplusHlt2TopoMu2BodyBBDTDecision_TOS==1||BplusHlt2TopoMu3BodyBBDTDecision_TOS==1||BplusHlt2TopoMu4BodyBBDTDecision_TOS==1||BplusHlt2Topo2BodyBBDTDecision_TOS==1||BplusHlt2Topo3BodyBBDTDecision_TOS==1||BplusHlt2Topo4BodyBBDTDecision_TOS==1||BplusHlt2Topo2BodySimpleDecision_TOS==1||BplusHlt2Topo3BodySimpleDecision_TOS==1||BplusHlt2IncPhiDecision_TOS==1||BplusHlt2TopoE__Decision_TOS==1||BplusHlt2Topo__Decision_TOS==1||BplusHlt2Charm__Decision_TOS==1||BplusHlt2DiElectron__Decision_TOS==1||BplusHlt2__GammaDecision_TOS==1)'


cut_TRIG_noHlt2 = L0_Dec + Hlt1_Dec
cut_TRIG 	= cut_TRIG_noHlt2 + Hlt2_Dec
cut_TIS_noHlt2 	= L0_TIS + Hlt1_TIS
cut_TIS 	= cut_TIS_noHlt2 + Hlt2_TIS
cut_TOS_noHlt2 	= L0_TOS + Hlt1_TOS
cut_TOS 	= cut_TOS_noHlt2 + Hlt2_TOS


#THOSE WILL BE USED IN getTrigEff in massFits:

Bu_cut_Dec = Bu_L0_Dec + Bu_Hlt1_Dec + Bu_Hlt2_Dec
Bu_cut_TIS = Bu_L0_TIS + Bu_Hlt1_TIS + Bu_Hlt2_TIS
Bu_cut_TOS = Bu_L0_TOS + Bu_Hlt1_TOS + Bu_Hlt2_TOS

#Bu_cut_Dec = cut_TRIG
#Bu_cut_TIS = cut_TIS
#Bu_cut_TOS = cut_TOS

#Bu_cut_Dec = cut_TRIG_noHlt2
#Bu_cut_TIS = cut_TIS_noHlt2
#Bu_cut_TOS = cut_TOS_noHlt2

#Test the LoHlt1 TIS efficiency bias on data when all the trigger levels are required by default

#Bu_cut_Dec = cut_TRIG 
#Bu_cut_TIS = cut_TRIG + cut_TIS_noHlt2
#Bu_cut_TOS = cut_TRIG + cut_TOS_noHlt2
#Bu_cut_TIS = cut_TRIG + cut_TIS
#Bu_cut_TOS = cut_TRIG + cut_TOS

#Bu_cut_TIS = Bu_L0_TIS + Bu_Hlt1_TIS 
#Bu_cut_TOS = Bu_L0_TOS + Bu_Hlt1_TOS 

#Trigger lines for Bs
Bs_L0_TIS = '&&B_s0L0Global_TIS==1'
Bs_L0_TOS = '&&B_s0L0Global_TOS==1'
Bs_Hlt1_TIS = '&&B_s0Hlt1Phys_TIS==1'
Bs_Hlt1_TOS = '&&B_s0Hlt1Phys_TOS==1'
Bs_Hlt2_TIS = '&&B_s0Hlt2Phys_TIS==1'
Bs_Hlt2_TOS = '&&B_s0Hlt2Phys_TOS==1'

Bs_cut_TIS = Bs_L0_TIS + Bs_Hlt1_TIS + Bs_Hlt2_TIS
Bs_cut_TOS = Bs_L0_TOS + Bs_Hlt1_TOS + Bs_Hlt2_TOS
#-------------------------------------------#

#The Jpsi trigger decision
Bu_Jpsi_L0 = '&&BplusL0MuonDecision_TOS==1'
Bs_Jpsi_L0 = '&&B_s0L0MuonDecision_TOS==1'
  
Bu_Jpsi_Hlt1 = '&&(BplusHlt1DiMuonHighMassDecision_TOS==1||BplusHlt1TrackMuonDecision_TOS==1)'
Bs_Jpsi_Hlt1 = '&&(B_s0Hlt1DiMuonHighMassDecision_TOS==1||B_s0Hlt1TrackMuonDecision_TOS==1)'

Bu_Jpsi_Hlt2 = '&&BplusHlt2DiMuonDetachedJPsiDecision_TOS==1'
Bs_Jpsi_Hlt2 = '&&B_s0Hlt2DiMuonDetachedJPsiDecision_TOS==1'

#-------------------------------------------#
# Ghost Probability cuts
Bu_GhostProb2011 = '&&Kplus_TRACK_GhostProb<0.3&&muminus_TRACK_GhostProb<0.3&&muplus_TRACK_GhostProb<0.3'
Bu_GhostProb = '&&Kplus_TRACK_GhostProb<0.4373&&muminus_TRACK_GhostProb<0.4373&&muplus_TRACK_GhostProb<0.4373'
MuMu_GhostProb = '&&muminus_TRACK_GhostProb<0.4373&&muplus_TRACK_GhostProb<0.4373'

Bs_GhostProb2011 = Bu_GhostProb2011 + '&&Kminus_TRACK_GhostProb<0.3'
Bs_GhostProb = Bu_GhostProb + '&&Kminus_TRACK_GhostProb<0.4373'

#-------------------------------------------#
# Remove bad runs in Strip 19b

cutBadRuns = '&&(runNumber<124272||runNumber>124505)'
#-------------------------------------------#






#from PDG
mBs = 5366.3
mBu = 5279.17
mBd = 5279.5
mJPsi = 3096.916
mPhi = 1019.455

commonCuts="mu1ips>5&&mu2ips>5&&mu1_track_Chi2DoF<4&&mu2_track_Chi2DoF<4&&DOCA<0.3"
JPsiCuts = "&&JPsiChi2<9&&fabs(3096.916-JPsiMass)<60&&dDsig_r>15"
BuCuts = "&&k1ips>5&&kaon_track_Chi2DoF<4&&Bips_r<5&&fabs(Bmass_JC-5279.17)<400&&Vchi2<45"
BdCuts = "&&k1ips>5&&mu1_kaon_Chi2DoF<5&&Bips<5&&fabs(Bmass-5279.5)<150&&dDsig_r>25&&Vchi2<75&&Bmass<5350&&Kstips>5 &&k1ips>2&&p1ips>1"
trackingStudyCuts= "&&PIDk>15&&dDsig_r>25"

########
#
# fiducial cuts
#

fiducialBu2011="&&Bpt>500&&Blife_ps<7.36&&mu1pt<1000000&&mu2pt<1000000"#FIXME P, K 
fiducialBu="&&Bpt>500&&Blife_ps<13.248&&mu1pt<500000&&mu2pt<500000"#FIXME P, K 
fiducialBs2011="&&Bpt>500&&Blife_ps<7.36&&sqrt(mu1p1*mu1p1+mu1p2*mu1p2)<1000000&&sqrt(mu2p1*mu2p1+mu2p2*mu2p2)<1000000&&sqrt(k1p1*k1p1+k1p2*k1p2)<1000000&&sqrt(k2p1*k2p1+k2p2*k2p2)<1000000"
fiducialBs="&&Bpt>500&&Blife_ps<13.24&&sqrt(mu1p1*mu1p1+mu1p2*mu1p2)<500000&&sqrt(mu2p1*mu2p1+mu2p2*mu2p2)<500000"#&&sqrt(k1p1*k1p1+k1p2*k1p2)<1000000&&sqrt(k2p1*k2p1+k2p2*k2p2)<1000000"
fiducialBu2012="&&Bpt>500&&Blife_ps<13.248 &&sqrt(mu1p1*mu1p1+mu1p2*mu1p2)<40000&&sqrt(mu2p1*mu2p1+mu2p2*mu2p2)<40000 &&sqrt(k1p1*k1p1+k1p2*k1p2)<40000  &&sqrt(mu1p1*mu1p1+mu1p2*mu1p2+mu1p3*mu1p3)<500000&&sqrt(mu2p1*mu2p1+mu2p2*mu2p2+mu2p3*mu2p3)<500000 &&sqrt(k1p1*k1p1+k1p2*k1p2+k1p3*k1p3)<500000"
fiducialBs2012="&&Bpt>500&&Blife_ps<13.248 &&sqrt(mu1p1*mu1p1+mu1p2*mu1p2)<40000&&sqrt(mu2p1*mu2p1+mu2p2*mu2p2)<40000 &&sqrt(k1p1*k1p1+k1p2*k1p2)<40000  &&sqrt(mu1p1*mu1p1+mu1p2*mu1p2+mu1p3*mu1p3)<500000&&sqrt(mu2p1*mu2p1+mu2p2*mu2p2+mu2p3*mu2p3)<500000 &&sqrt(k1p1*k1p1+k1p2*k1p2+k1p3*k1p3)<500000 &&sqrt(k2p1*k2p1+k2p2*k2p2)<40000 &&sqrt(k2p1*k2p1+k2p2*k2p2+k2p3*k2p3)<500000 "


clonesBu="&&mu1_track_CloneDist>5000&&mu2_track_CloneDist>5000&&kaon_track_CloneDist>5000"
tightMBd="&&fabs(Bmass_JC-5279.17)<100"
missingBu="fabs(3096.916-JPsiMass)<60&&dDsig_r>15&&kaon_track_Chi2DoF<4"

phiCuts = "&&fabs(PhiMass-1019.455)<10"#BsCuts = "&&kaon1_track_Chi2DoF<10&&kaon1_track_Chi2DoF<10&&PIDkp1>-5&&PIDkp2>-5&&fabs(Bmass-5379)<200"
#BsCuts = "&&kaon1_track_Chi2DoF<5&&kaon1_track_Chi2DoF<5&&PIDk1>0&&PIDk2>0&&fabs(Bmass-5366.3)<200"
BsCuts = "&&kaon1_track_Chi2DoF<5&&kaon2_track_Chi2DoF<5&&fabs(Bmass_JC-5366.3)<200&&Bips_r<5"
extraCuts="&&Phiips>5&&k1ips>2&&k2ips>1"
pidCuts="&&PIDk1>5"#&&PIDk2>5"
loosePID="&&PIDk1>0&&PIDk2>0"
tightM="&&fabs(Bmass_JC-"+str(mBs)+")<100"
#### !!!! put in correct masses

clonesBs="&&mu1_track_CloneDist>5000&&mu2_track_CloneDist>5000&&kaon1_track_CloneDist>5000&&kaon2_track_CloneDist>5000"


bsCleanup="&&Blife_ps>1&&Vchi2<25"
bsCleanup2="&&Bdissig>25&&mu1ips>9&&mu2ips>9&&k1ips>9&&k2ips>9"


BDTS_05="&&BDTS_cx>0.05"
fullNormBu2012=commonCuts+JPsiCuts+BuCuts+clonesBu+tightMBd+fiducialBu2012+BDTS_05
minimalNormBu=missingBu+tightMBd+fiducialBu2012+BDTS_05

minimalNormBu_nofid=missingBu+tightMBd

###
# lnf stuff
#
fcuts="&&Bplus_PT>500&&Bplus_TAU*1000.<13.248&&muminus_P<500e03&&muplus_P<500e03&&muminus_PT<40e03&&muplus_PT<40e03&&Kplus_PT<40e03&&Kplus_P<500e03"
moreCuts="&&Kplus_TRACK_CHI2NDOF<4"
#moreCuts="&&Kplus_TRACK_CHI2NDOF<3" #in 2012
bdts="&&Bplus_BDTS>0.05"

Bu_PID = "&&Kplus_PIDK>0"

minimalNormBu_lnf="fabs(Bplus_JCMass-5279.17)<100&&fabs(J_psi_1S_M-3096.916)<60&&Jpsi_dist_chi2_r>15"+fcuts+moreCuts+bdts
minimalNormBu_rawM_lnf="fabs(Bplus_M-5279.17)<100&&fabs(J_psi_1S_M-3096.916)<60&&Jpsi_dist_chi2_r>15"+fcuts+moreCuts+bdts


minimalNormBu_noFid_lnf="fabs(Bplus_JCMass-5279.17)<100&&fabs(J_psi_1S_M-3096.916)<60&&Jpsi_dist_chi2_r>15&&Kplus_TRACK_CHI2NDOF<4"

fullNormBs=commonCuts+JPsiCuts+BsCuts+phiCuts+extraCuts+"&&Vchi2<75"+clonesBs+tightM+fiducialBs2012+loosePID+BDTS_05

nojp_bs=commonCuts+BsCuts+phiCuts+extraCuts+"&&Vchi2<75"+clonesBs+tightM+fiducialBs2012+loosePID+BDTS_05+"&&JPsiChi2<9&&dDsig_r>15"

fcuts_lnf_bs="&&B_s0_PT>500&&B_s0_TAU*1000.<13.248&&muminus_P<500e03&&muplus_P<500e03&&muminus_PT<40e03&&muplus_PT<40e03&&Kplus_PT<40e03&&Kplus_P<500e03&&Kminus_PT<40e03&&Kminus_P<500e03"

moreCuts_lnf_bs="&&Kplus_TRACK_CHI2NDOF<4&&Kminus_TRACK_CHI2NDOF<4&&B_s0_BDTS>0.05"

Bs_PID = "&&Kplus_PIDK>0&&Kminus_PIDK>0"

normBsPID_lnf="fabs(B_s0_JCMass-5366.3)<100"+Bs_PID+"&&fabs(J_psi_1S_M-3096.916)<60&&fabs(phi_1020_M-1019.455)<10&&Jpsi_dist_chi2_r>15"+fcuts_lnf_bs+moreCuts_lnf_bs
normBs_lnf="fabs(B_s0_JCMass-5366.3)<100&&fabs(J_psi_1S_M-3096.916)<60&&fabs(phi_1020_M-1019.455)<10&&Jpsi_dist_chi2_r>15"+fcuts_lnf_bs+moreCuts_lnf_bs


trigger="&&L0Decision&&Hlt1Decision&&Hlt2Decision"
JPsiRecoCuts = "&&dDsig_r>25&&sqrt(mu1p1*mu1p1+mu1p2*mu1p2)>250&&sqrt(mu2p1*mu2p1+mu2p2*mu2p2)>250&&sqrt(k1p1*k1p1+k1p2*k1p2)>250"#&&JPsi_Dsig>13"
BuCuts = "&&k1ips>5&&kaon_track_Chi2DoF<4&&Bips<5&&fabs(Bmass_JC-5279.17)<400&&Vchi2<45"
   

recoBu=commonCuts+JPsiCuts+BuCuts+clonesBu+tightMBd+fiducialBu2012+JPsiRecoCuts+trigger+"&Bmass_JC>5200"+"&&PIDk>0"



###################################
#
# some technical cuts
#
tightMBd_noJC="&&fabs(Bmass-5279.17)<100"
pvCuts="&&NPV==1"
runNum1="&&runNum<88000"
runNum2="&&runNum>88000&&runNum<89800"
runNum3="&&runNum>89800&&runNum<91000"
runNum4="&&runNum>91000&&runNum<92400"
runNum5="&&runNum>92400&&runNum<93200"
#300->341 pb
runNum7="&&runNum>93200&&runNum<93650"
runNum8="&&runNum>93650&&runNum<94060"
runNum9="runNum>94060&&runNum<94500"

