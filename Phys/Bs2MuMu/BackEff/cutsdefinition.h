#ifndef EFFICIENCY_MYUTILS_H 
#define EFFICIENCY_MYUTILS_H 1

#include "TString.h" 

/* 
The bug was the following: 
in the stripping, for the B there is BPVIPCHI2 which corresponds to IPCHI2_OWNPV and not MINIPCHI2
*/


// TString bsmumu_stripping_10 = "muplus_MINIPCHI2>25 && muminus_MINIPCHI2>25 &&\ // changed to use with MC11! ///> 2013-06-06
TString bsmumu_stripping_10 = "muplus_IPCHI2_OWNPV>25 && muminus_IPCHI2_OWNPV>25 &&\
muplus_PT>250 && muminus_PT>250 && \
 B_s0_doca<0.3 && B_s0_DIRA_OWNPV>0 && B_s0_ENDVERTEX_CHI2<9 && B_s0_IPCHI2_OWNPV<25\
 && B_s0_FDCHI2_OWNPV>225 && muplus_isMuon==1 && muminus_isMuon==1\
 && muplus_TRACK_CHI2NDOF<4 && muminus_TRACK_CHI2NDOF<4 && (abs(B_s0_M - 5366.3) < 1200)";

TString bsmumu_stripping_12 = "(muplus_MINIPCHI2>25 && muminus_MINIPCHI2>25 &&\
muplus_PT>250 && muminus_PT>250 && \
 B_s0_doca<0.3 && B_s0_DIRA_OWNPV>0 && B_s0_ENDVERTEX_CHI2<9 && B_s0_IPCHI2_OWNPV<25\
 && B_s0_FDCHI2_OWNPV>225 && muplus_isMuon==1 && muminus_isMuon==1\
 && muplus_TRACK_CHI2NDOF<3 && muminus_TRACK_CHI2NDOF<3 && (abs(B_s0_M - 5366.3) < 1200))";

TString bsmumu_stripping_12_mod = "(muplus_IPCHI2_OWNPV>25 && muminus_IPCHI2_OWNPV>25 &&\
muplus_PT>250 && muminus_PT>250 && \
 B_s0_doca<0.3 && B_s0_DIRA_OWNPV>0 && B_s0_ENDVERTEX_CHI2<9 && B_s0_IPCHI2_OWNPV<25\
 && B_s0_FDCHI2_OWNPV>225 && muplus_isMuon==1 && muminus_isMuon==1\
 && muplus_TRACK_CHI2NDOF<3 && muminus_TRACK_CHI2NDOF<3 && (abs(B_s0_M - 5366.3) < 1200))";

TString bsmumu_cuts = "B_s0_PT>500 &&B_s0_TAU*1000.<13.248\
&&muminus_P<500e03 &&muplus_P<500e03&&muminus_PT<40e03&&muplus_PT<40e03 && muplus_PT > 250 && \
muminus_PT > 250  && \
 muplus_PIDmu>-5 && muplus_PIDK<10&& muminus_PIDmu>-5 && muminus_PIDK<10 && B_s0_BDTS>0.05";
TString bsmumu_fidcuts = "B_s0_PT>500 &&B_s0_TAU*1000.<13.248\
&&muminus_P<500e03 &&muplus_P<500e03&&muminus_PT<40e03&&muplus_PT<40e03 && muplus_PT > 250 && \
muminus_PT > 250  && B_s0_BDTS>0.05";
TString bsmumu_ghost = "((muplus_TRACK_GhostProb<0.437300) && (muminus_TRACK_GhostProb<0.437300))";
TString bsmumu_ghost_13 = "((muplus_TRACK_GhostProb<0.3) && (muminus_TRACK_GhostProb<0.3))";



TString bsmumu_masscut = "B_s0_M > 4900 && B_s0_M< 6000";
TString bsmumu_masswin = "(abs(B_s0_M - 5366.3) < 60)";
TString bdmumu_masswin = "(abs(B_s0_M - 5279.53) < 60)";

TString bsmumu_mcmatch = "abs(muplus_MC_MOTHER_ID)==531 && abs(muminus_MC_MOTHER_ID)==531";


TString bsmumu_l0 = "(B_s0L0MuonDecision_Dec||B_s0L0DiMuonDecision_Dec)";
TString bsmumu_hlt1 = "(B_s0Hlt1DiMuonLowMassDecision_Dec || B_s0Hlt1DiMuonHighMassDecision_Dec ||\
                     B_s0Hlt1TrackMuonDecision_Dec || B_s0Hlt1SingleMuonNoIPDecision_Dec  || \
    B_s0Hlt1SingleMuonHighPTDecision_Dec || B_s0Hlt1TrackAllL0Decision_Dec)";
TString bsmumu_hlt2 = "(B_s0Hlt2DiMuonBDecision_Dec || B_s0Hlt2DiMuonDecision_Dec || \
B_s0Hlt2DiMuonDetachedDecision_Dec || B_s0Hlt2DiMuonDetachedJPsiDecision_Dec || \
B_s0Hlt2DiMuonDetachedHeavyDecision_Dec || B_s0Hlt2SingleMuonDecision_Dec  ||\
B_s0Hlt2SingleMuonHighPTDecision_Dec || B_s0Hlt2TopoMu2BodyBBDTDecision_Dec || \
B_s0Hlt2TopoMu3BodyBBDTDecision_Dec || B_s0Hlt2TopoMu4BodyBBDTDecision_Dec || \
B_s0Hlt2DiMuonJPsiDecision_Dec)";


TString bsmumu_trigger = bsmumu_l0 + "&&" + bsmumu_hlt1 + "&&" + bsmumu_hlt2;


TString bsmumu_fullsel_10 = bsmumu_stripping_10+"&&"+bsmumu_cuts;
TString bsmumu_fullsel_12 = bsmumu_stripping_12+"&&"+bsmumu_cuts;

TString bjpsik_stripping_10 = "muplus_isMuon==1 && muminus_isMuon==1 && \
muplus_PT>250 && muminus_PT>250 && \
muplus_TRACK_CHI2NDOF<4 && muminus_TRACK_CHI2NDOF<4 && muplus_MINIPCHI2>25 && muminus_MINIPCHI2>25 && \
J_psi_1S_doca<0.3 && J_psi_1S_DIRA_OWNPV>0 && J_psi_1S_ENDVERTEX_CHI2<9 && J_psi_1S_FDCHI2_OWNPV>225 && \
 abs(J_psi_1S_M - 3096.916) < 100 && Kplus_TRACK_CHI2NDOF<5 && Kplus_MINIPCHI2>25 && Kplus_PT>250 && \
 abs(Bplus_M-5279.15)<500 && Bplus_IPCHI2_OWNPV<25 && Bplus_ENDVERTEX_CHI2<45";

TString bjpsik_stripping_12 = "muplus_isMuon==1 && muminus_isMuon==1 && \
muplus_PT>250 && muminus_PT>250 && \
muplus_TRACK_CHI2NDOF<3 && muminus_TRACK_CHI2NDOF<3 && muplus_MINIPCHI2>25 && muminus_MINIPCHI2>25 && \
J_psi_1S_doca<0.3 && J_psi_1S_DIRA_OWNPV>0 && J_psi_1S_ENDVERTEX_CHI2<9 && J_psi_1S_FDCHI2_OWNPV>225 && \
 abs(J_psi_1S_M - 3096.916) < 100 && Kplus_TRACK_CHI2NDOF<3 && Kplus_MINIPCHI2>25 && Kplus_PT>250 && \
 abs(Bplus_M-5279.15)<500 && Bplus_IPCHI2_OWNPV<25 && Bplus_ENDVERTEX_CHI2<45";

TString bjpsik_bs_masswin = "abs(Bplus_JCMass-5279.15)<100" ;
TString bjpsik_jpsi_masswin = "abs(J_psi_1S_M - 3096.916) < 60" ;
TString bjpsik_masswin = bjpsik_bs_masswin +"&&"+bjpsik_jpsi_masswin;

TString bjpsik_cuts = "Bplus_PT>500 && muplus_PT > 250 && muminus_PT > 250 && muplus_PT<40000 &&\
 muminus_PT<40000 && Kplus_PT<40000 && muplus_P < 500000 && muminus_P < 500000 && Kplus_PT < 500000 && \
Bplus_TAU*1000<13.248 && Bplus_BDTS>0.05";

TString bjpsik_mcmatch ="muplus_MC_MOTHER_ID==443 && muminus_MC_MOTHER_ID==443 &&\
 abs(J_psi_1S_MC_MOTHER_ID) == 521 && abs(Kplus_MC_MOTHER_ID)==521 && abs(Bplus_TRUEID)==521" ;

TString bjpsik_fullsel_10 = bjpsik_stripping_10+"&&"+bjpsik_cuts+"&&"+bjpsik_masswin;
TString bjpsik_fullsel_12 = bjpsik_stripping_12+"&&"+bjpsik_cuts+"&&"+bjpsik_masswin;




TString bdkpi_mcmatch = "abs(muplus_MC_MOTHER_ID)==511 && abs(muminus_MC_MOTHER_ID)==511";
TString bdkpi_stripping_12 = "muplus_InMuonAcc>0.5 && muminus_InMuonAcc>0.5 \
&& muplus_MINIPCHI2>25 && muminus_MINIPCHI2>25 &&\
muplus_PT>250 && muminus_PT>250 &&  B_s0_doca<0.3 && B_s0_DIRA_OWNPV>0 &&\
 B_s0_ENDVERTEX_CHI2<9 && B_s0_IPCHI2_OWNPV<25  && B_s0_FDCHI2_OWNPV>225 \
 && muplus_TRACK_CHI2NDOF<3 && muminus_TRACK_CHI2NDOF<3 && (abs(B_s0_M - 5366.3) < 1200)";

TString bdkpi_cuts = "B_s0_PT>500 &&B_s0_TAU*1000.<13.248\
&&muminus_P<500e03 &&muplus_P<500e03&&muminus_PT<40e03&&muplus_PT<40e03 && muplus_PT > 250 && \
muminus_PT > 250  && B_s0_BDTS>0.05";
// Remove the ghostprob cut as it is calculated by Siim on data 

//TString bdkpi_masswin = "(abs(B_s0_M - 5366.3) < 60)";

TString bdkpi_fullsel_12 = bdkpi_stripping_12+"&&"+bdkpi_cuts;




#endif // EFFICIENCY_MYUTILS_H
