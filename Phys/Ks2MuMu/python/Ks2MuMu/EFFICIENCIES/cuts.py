#DEFINING ALL THE CUTS TO APPLY IN computeEff.py  CHECK EVERYTHING BEFORE RUNNING

def AND(*fcns):
    def fcnAND_(entry):
        return all(fcn(entry) for fcn in fcns)
    return fcnAND_

def selection(entry):
    return (entry.KS0_TAU < 0.13) and (entry.KS0_TAU > 0.) and (entry.muplus_IP_OWNPV > 0.5) and (entry.muminus_IP_OWNPV > 0.5) and (entry.KS0_ENDVERTEX_CHI2 < 25.) and (entry.muplus_P < 100.e3) and (entry.muminus_P < 100.e3)  and (entry.muminus_MC12TuneV3_ProbNNk < 0.85) and (entry.muplus_MC12TuneV3_ProbNNk < 0.85) and (entry.muminus_MC12TuneV3_ProbNNghost < 0.4) and (entry.muplus_MC12TuneV3_ProbNNghost < 0.4) 

def gec(entry):
    return (entry.nVeloClusters < 10000) and (entry.nITClusters < 10000) and (entry.nOTClusters < 15000) and (entry.nVeloTracks < 350) and (entry.nSPDHits < 900)


def armenteros(entry):
    return True
    #return   abs(entry.Mass_ProtonplusPiminus - 1115.683)>50 and abs(entry.Mass_PiplusProtonminus - 1115.683)>50 

def noCuts(entry):
    return True

def strippingMuMu(entry):
    return (entry.StrippingKS02MuMuLineDecision==1)

def strippingMB(entry):
    return (entry.StrippingKS02MuMuNoMuIDLineDecision==1)

def cutsC(entry):
    return (entry.StrippingKS02MuMuNoMuIDLineDecision==1) and (entry.KS0_L0Global_Dec==1) and (entry.KS0_Hlt1Global_Dec ==1) and (entry.KS0_Hlt2Global_Dec ==1)


fiducial = AND(selection, gec, armenteros)

def tostos1tos(entry):
    return (entry.KS0_L0MuonDecision_TOS==1) and (entry.KS0_Hlt1TrackMuonDecision_TOS==1) and (entry.KS0_Hlt2DiMuonDetachedDecision_TOS==1)

def tostos2tos(entry):
    return (entry.KS0_L0MuonDecision_TOS==1) and (entry.KS0_Hlt1DiMuonLowMassDecision_TOS==1) and (entry.KS0_Hlt2DiMuonDetachedDecision_TOS==1)

def tististos(entry):
    return (entry.KS0_L0MuonDecision_TIS==1 or entry.KS0_L0DiMuonDecision_TIS==1 or entry.KS0_L0HadronDecision_TIS==1 or entry.KS0_L0ElectronDecision_TIS==1 or entry.KS0_L0PhotonDecision_TIS==1)  and (entry.KS0_Hlt1Phys_TIS==1) and (entry.KS0_Hlt2DiMuonDetachedDecision_TOS==1)

def tistis(entry):
    return (entry.KS0_L0MuonDecision_TIS==1 or entry.KS0_L0DiMuonDecision_TIS==1 or entry.KS0_L0HadronDecision_TIS==1 or entry.KS0_L0ElectronDecision_TIS==1 or entry.KS0_L0PhotonDecision_TIS==1) and (entry.KS0_Hlt1Phys_TIS==1) and (entry.KS0_Hlt2DiMuonDetachedDecision_TOS==1)  

def binCut(idx):
    def fcn_(entry):
        return entry.Bin == idx
    return fcn_
bins = [binCut(i) for i in range(1, 10)]
