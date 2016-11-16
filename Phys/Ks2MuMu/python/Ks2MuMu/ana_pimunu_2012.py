from ROOT import *
gROOT.ProcessLine(".x /cvmfs/lhcb.cern.ch/lib/lhcb/URANIA/URANIA_v1r1/RootTools/LHCbStyle/src/lhcbStyle.C")
aa = "&&"

HOME = "/scratch02/xabier/KsMuMu/"

## MC KSPIMUNU
f1 = TFile(HOME+"Kspimunu_MC2012_Stripped.root")
t1 = f1.Get("KsMuMuTuple/DecayTree")
t2 = f1.Get("KsPiPiTuple/DecayTree")
########
## MC KSPIPI
f3 = TFile(HOME+"MB08ac_MC2012_NoStripping.root")
t3 = f3.Get("KspipimcMatch/DecayTree")
########
## MC KSMUMU
f4 = TFile(HOME+"Ksmumu_MC2012_Stripped.root")
t4 = f4.Get("KsMuMuTuple/DecayTree")
#####
## DATA
f5 = TFile(HOME+"KsMBdata.root")
tdmb = f5.Get("KsMBTuple/DecayTree")
f6 = TFile(HOME+"Kspipidata.root")
tdst = f6.Get("KsPiPiTuple/DecayTree")

####
MASS = "KS0_massMM>492&&KS0_massMM<504"

#####
## FIDUCIAL

SEL = "(KS0_TAU < 0.13) && (KS0_TAU > 0.) && (muplus_IP_OWNPV > 0.5) && (muminus_IP_OWNPV > 0.5) && (KS0_ENDVERTEX_CHI2 < 25.) && (muplus_P < 100.e3) && (muminus_P < 100.e3)  && (muminus_MC12TuneV3_ProbNNk < 0.85) && (muplus_MC12TuneV3_ProbNNk < 0.85) && (muminus_MC12TuneV3_ProbNNghost < 0.4) && (muplus_MC12TuneV3_ProbNNghost < 0.4)"
GEC = "(nVeloClusters < 10000) && (nITClusters < 10000) && (nOTClusters < 15000) && (nVeloTracks < 350) && (nSPDHits < 900)"

ARMENTEROS = "abs(Mass_ProtonplusPiminus - 1115.683)>50 && abs(Mass_PiplusProtonminus - 1115.683)>50"

#FIDUCIAL = "("+SEL+aa+GEC+aa+ARMENTEROS+")"
FIDUCIAL = "1"
#####
## MCTRUTH
TRUECOND_PIMUNU = "( ( abs(muplus_TRUEID)==211 && abs(muminus_TRUEID)==13 ) || ( abs(muplus_TRUEID)==13 && abs(muminus_TRUEID)==211) ) && abs(muminus_MC_MOTHER_ID)==310 && muminus_MC_MOTHER_KEY==muplus_MC_MOTHER_KEY"

TRUECOND_PIPI = "abs(muplus_TRUEID)==211 && abs(muminus_TRUEID)==211 && abs(muminus_MC_MOTHER_ID)==310 && muminus_MC_MOTHER_KEY==muplus_MC_MOTHER_KEY"

TRUECOND_MUMU = "abs(muplus_TRUEID)==13 && abs(muminus_TRUEID)==13 && abs(muminus_MC_MOTHER_ID)==310 && muminus_MC_MOTHER_KEY==muplus_MC_MOTHER_KEY"

#####
## TRIGGER 

HLT2TOS = "KS0_Hlt2DiMuonDetachedDecision_TOS"
TOSTOS1TOS = "KS0_L0MuonDecision_TOS && KS0_Hlt1TrackMuonDecision_TOS"+aa+HLT2TOS
TOSTOS2TOS = "KS0_L0MuonDecision_TOS && KS0_Hlt1DiMuonLowMassDecision_TOS"+aa+HLT2TOS

###########
## GET SIGNAL EFFICIENCIES

def draw_mass():
    c1 = TCanvas()
    h1 = TH1F("a","a",20,450,500)
    t2.Project("a","KS0_massMM",TRUECOND_PIMUNU)
    h1.GetXaxis().SetTitle("m_{#mu^{+} #mu^{-}} (MeV/c^{2})")
    h1.GetYaxis().SetTitle("Number of candidates / 2.5 MeV/c^{2}");h1.Draw()
    c1.SetWindowSize(1000,900)
    return c1,h1

NPIMUNU0 = 775457+ 753900 ## DOWN+UP
EGEN_PIMUNU = 0.16801

## GET MASS FROM NOMUIDLINE
EMASS_PIMUNU = float(t2.GetEntries(TRUECOND_PIMUNU+aa+FIDUCIAL+aa+MASS))/float(t2.GetEntries(TRUECOND_PIMUNU+aa+FIDUCIAL))
print "EGEN_PIMUNU",EGEN_PIMUNU*100,"%"
print "EMASS_PIMUNU",EMASS_PIMUNU*100,"%"

## GET THE REST OF EFFICIENCIES FROM THE MUIDLINE
ESELREC_PIMUNU = EGEN_PIMUNU*float(t1.GetEntries(TRUECOND_PIMUNU+aa+FIDUCIAL))/float(NPIMUNU0)*EMASS_PIMUNU
print "ESELREC_PIMUNU",ESELREC_PIMUNU

###########
## GET NORMALIZATION EFFICIENCIES

na = 11038979 + 11057978 ## SIM8a DOWN+UP
nc = 10004988 + 10020984    ## SIM8c DOWN+UP
NPIPI0 = na+nc
EGEN_PIPI = 1
#ESELREC_PIPI = EGEN_PIPI*float(t3.GetEntries("StrippingKS02MuMuNoMuIDLineDecision"+aa+FIDUCIAL+aa+TRUECOND_PIPI))/float(NPIPI0)
MULT_KSPIPI = 6.5
ESELREC_PIPI = EGEN_PIPI*float(t3.GetEntries("StrippingKS02MuMuNoMuIDLineDecision"+aa+FIDUCIAL))/float(NPIPI0*MULT_KSPIPI)
print "EGEN_PIPI",ESELREC_PIPI
##########
## GET TOS EFFICIENCIES FROM KsMuMu (CONSERVATIVE)
ETOSTOS1TOS = float(t4.GetEntries("StrippingKS02MuMuNoMuIDLineDecision"+aa+FIDUCIAL+aa+TRUECOND_MUMU+aa+TOSTOS1TOS))/float(t4.GetEntries("StrippingKS02MuMuNoMuIDLineDecision"+aa+FIDUCIAL+aa+TRUECOND_MUMU))
ETOSTOS2TOS = float(t4.GetEntries("StrippingKS02MuMuNoMuIDLineDecision"+aa+FIDUCIAL+aa+TRUECOND_MUMU+aa+TOSTOS2TOS+aa+"(!("+TOSTOS1TOS+"))"))/float(t4.GetEntries("StrippingKS02MuMuNoMuIDLineDecision"+aa+FIDUCIAL+aa+TRUECOND_MUMU))
EHLT2TOS = float(t4.GetEntries("StrippingKS02MuMuNoMuIDLineDecision"+aa+FIDUCIAL+aa+TRUECOND_MUMU+aa+HLT2TOS))/float(t4.GetEntries("StrippingKS02MuMuNoMuIDLineDecision"+aa+FIDUCIAL+aa+TRUECOND_MUMU))

print "ETOSTOS1TOS",ETOSTOS1TOS
print "ETOSTOS2TOS",ETOSTOS2TOS
print "EHLT2TOS",EHLT2TOS

##########
## NOW GET S_MB FROM DATA
TIGHT_MASS = "KS0_M>490&&KS0_M<505"
TRIG_DEC = "KS0_L0Global_Dec&&KS0_Hlt1Phys_Dec&&KS0_Hlt2Phys_Dec"
S_MB = tdmb.GetEntries(TIGHT_MASS+aa+TRIG_DEC+aa+FIDUCIAL)/(1000.*tdst.GetEntries(TIGHT_MASS+aa+TRIG_DEC+aa+FIDUCIAL))

N_MB = tdmb.GetEntries("KS0_MM>485&&KS0_MM<510"+aa+FIDUCIAL)
N_MB_TISTIS = tdmb.GetEntries("KS0_MM>485&&KS0_MM<510"+aa+FIDUCIAL+aa+"KS0_L0Global_TIS&&KS0_Hlt1Phys_TIS")

ETOT_PIPI = S_MB*ESELREC_PIPI
print "CROSSCHECK, KSPIPI IN 2fb-1",N_MB/(ETOT_PIPI)
##

## FINAL NUMBER
BR_pimunu = 4.69e-4
BR_pipi = 0.692
Npimunu_TOSTOS1TOS = BR_pimunu/BR_pipi * ESELREC_PIMUNU/ETOT_PIPI * N_MB * ETOSTOS1TOS
Npimunu_TOSTOS2TOS = BR_pimunu/BR_pipi * ESELREC_PIMUNU/ETOT_PIPI * N_MB * ETOSTOS2TOS
Npimunu_TISTISTOS =  BR_pimunu/BR_pipi * ESELREC_PIMUNU/ETOT_PIPI * N_MB_TISTIS * EHLT2TOS

print "Npimunu_TOSTOS1TOS",Npimunu_TOSTOS1TOS
print "Npimunu_TOSTOS2TOS",Npimunu_TOSTOS2TOS
print "Npimunu_TISTISTOS",Npimunu_TISTISTOS
