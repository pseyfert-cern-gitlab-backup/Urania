aa = "&&"

selection = "(KS0_TAU < 0.13 && KS0_TAU > 0. && muplus_IP_OWNPV > 0.5 && muminus_IP_OWNPV > 0.5 && KS0_ENDVERTEX_CHI2 < 25. && muplus_P < 100.e3 && muminus_P < 100.e3 && muminus_MC12TuneV3_ProbNNk < 0.85 && muplus_MC12TuneV3_ProbNNk < 0.85 && muminus_MC12TuneV3_ProbNNghost < 0.4 && muplus_MC12TuneV3_ProbNNghost < 0.4)"

armenteros =  "(abs(Mass_ProtonplusPiminus - 1115.683)>50 && abs(Mass_PiplusProtonminus - 1115.683)>50) "

gec = "(nVeloClusters < 10000 && nITClusters < 10000 && nOTClusters < 15000 && nVeloTracks < 350 && nSPDHits < 900)"


tostos1tos = "((KS0_L0MuonDecision_TOS==1) && (KS0_Hlt1TrackMuonDecision_TOS==1) &&  (KS0_Hlt2DiMuonDetachedDecision_TOS==1))"

tostos2tos = "((KS0_L0MuonDecision_TOS==1) && (KS0_Hlt1DiMuonLowMassDecision_TOS==1) &&  (KS0_Hlt2DiMuonDetachedDecision_TOS==1))"

tististos = "((KS0_L0MuonDecision_TIS==1 || KS0_L0DiMuonDecision_TIS==1 || KS0_L0HadronDecision_TIS==1 || KS0_L0ElectronDecision_TIS==1 || KS0_L0PhotonDecision_TIS==1) && (KS0_Hlt1Phys_TIS==1) && (KS0_Hlt2DiMuonDetachedDecision_TOS==1)) "

tistis = "((KS0_L0MuonDecision_TIS==1 || KS0_L0DiMuonDecision_TIS==1 || KS0_L0HadronDecision_TIS==1 || KS0_L0ElectronDecision_TIS==1 || KS0_L0PhotonDecision_TIS==1) && (KS0_H\
lt1Phys_TIS==1)) "

cat1 = "(" + selection + aa + armenteros + aa + gec + aa+ tostos1tos + aa+ "!"+ tististos + ")"

cat2 = "("+ selection + aa + armenteros+ aa + gec + aa + tostos2tos + aa +"!" + tostos1tos + aa + "!"+ tististos + ")"

cat3 = "(" + selection + aa+ armenteros + aa+ gec + aa+ tististos + ")"

tistis =  "(" + selection + aa+ armenteros + aa+ gec + aa+ tistis + ")"

notrig = "(" + selection + aa+ armenteros + aa+ gec +  ")"

#print cat1

#print cat2

#print cat3
