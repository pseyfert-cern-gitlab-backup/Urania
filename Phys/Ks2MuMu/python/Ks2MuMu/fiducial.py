aa = "&&"

selection = "((KS0_TAU < 0.13 && KS0_TAU > 0. && muplus_IP_OWNPV > 0.5 && muminus_IP_OWNPV > 0.5 && KS0_ENDVERTEX_CHI2 < 25. && muplus_P < 100.e3 && muminus_P < 100.e3 && muminus_MC12TuneV3_ProbNNk < 0.85 && muplus_MC12TuneV3_ProbNNk < 0.85 && muminus_MC12TuneV3_ProbNNghost < 0.4 && muplus_MC12TuneV3_ProbNNghost < 0.4))"

armenteros =  "(abs(Mass_ProtonplusPiminus - 1115.683)>50 && abs(Mass_PiplusProtonminus - 1115.683)>50) "

gec = "(nVeloClusters < 10000 && nITClusters < 10000 && nOTClusters < 15000 && nVeloTracks < 350 && nSPDHits < 900)"


tostos1tos = "((KS0_L0MuonDecision_TOS==1) && (KS0_Hlt1TrackMuonDecision_TOS==1) &&  (KS0_Hlt2DiMuonDetachedDecision_TOS==1))"

tostos2tos = "((KS0_L0MuonDecision_TOS==1) && (KS0_Hlt1DiMuonLowMassDecision_TOS==1) &&  (KS0_Hlt2DiMuonDetachedDecision_TOS==1))"

tististos = "(((KS0_L0MuonDecision_TIS==1 || KS0_L0DiMuonDecision_TIS==1 || KS0_L0HadronDecision_TIS==1 || KS0_L0ElectronDecision_TIS==1 || KS0_L0PhotonDecision_TIS==1) && (KS0_Hlt1Phys_TIS==1) && (KS0_Hlt2DiMuonDetachedDecision_TOS==1))) "

muonPID = "(muplus_muonIDPlusBDT>0. && muminus_muonIDPlusBDT>0.)"

fullsel = selection + aa + armenteros + aa + gec
minsel = selection + aa + gec

def BDT_cuts(bdtname, Binning):
    BDT = {}
    for i  in range(len(Binning)-1):
        BDT[i] =  "&& "+bdtname+">=" + str(Binning[i]) +" && "+bdtname+"<" + str(Binning[i+1])
    
    return BDT



SEL = {}
SEL["TOS1_"] = "(" + fullsel + aa+ tostos1tos + aa + "!"+ tististos + ")"

SEL["TOS2_"] = "("+ fullsel + aa + tostos2tos + aa + "!" + tostos1tos + aa + "!"+ tististos + ")"

SEL["TIS_"] = "(" + fullsel + aa+ tististos + ")"

fSEL = {}
fSEL["TOS1_"] = "(" + minsel + aa+ tostos1tos + aa + "!"+ tististos + ")"

fSEL["TOS2_"] = "("+ minsel + aa + tostos2tos + aa + "!" + tostos1tos + aa + "!"+ tististos + ")"

fSEL["TIS_"] = "(" + minsel + aa+ tististos + ")"

SEL_FIT = {}

SEL_FIT["TOS1_"] = "(" + fullsel + aa+ tostos1tos + aa + "!"+ tististos + aa + muonPID + ")"

SEL_FIT["TOS2_"] = "("+ fullsel + aa + tostos2tos + aa + "!" + tostos1tos + aa + "!"+ tististos + aa + muonPID + ")"

SEL_FIT["TIS_"] = "(" + fullsel + aa+ tististos + aa + muonPID + ")"


binTIS = [-0.47770596071637, 0.07971142340475432, 0.14026170461797557, 0.18444871603585514, 0.22225635309191752, 0.2580670613406256, 0.2941205180849224, 0.33306522164617797, 0.3796568282758258, 0.4413369648554482, 1.]

# [-0.19063514226519926, 0.17908014817790685, 0.22811067108431074, 0.2629873191115029, 0.29274459835877703, 0.3177759860603811, 0.3436338808406099, 0.373655807124543, 0.4096373667079955, 0.4672752346623939, 0.6159642644258067]

binTOS1 = [-0.5312869817266488, -0.1266664594344026, -0.018057598024261365, 0.05645428551488561, 0.1144174592588098, 0.1641042598190453, 0.2107112817081271, 0.2579244810661749, 0.3083928063263968, 0.369437934415055, 1.]

binTOS2 = [-0.29663451166129434, 0.08271595580229936, 0.1425903605906138, 0.18821173949006376, 0.23086137292504383, 0.2672261002814406, 0.30348300632055697, 0.33827234947509255, 0.3816746510051476, 0.43741757427171485, 1.]
