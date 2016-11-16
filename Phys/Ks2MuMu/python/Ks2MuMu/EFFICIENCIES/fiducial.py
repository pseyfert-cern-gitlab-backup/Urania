#remember to change BIN category!!!!!!!
aa = "&&"

genCut="(sqrt(KS0_ENDVERTEX_X**2+KS0_ENDVERTEX_Y**2)<38 && KS0_ENDVERTEX_Z<800 && KS0_P_Z>0)"

selection = "((KS0_TAU < 0.13 && KS0_TAU > 0. && muplus_IP_OWNPV > 0.5 && muminus_IP_OWNPV > 0.5 && KS0_ENDVERTEX_CHI2 < 25. && muplus_P < 100.e3 && muminus_P < 100.e3 && muminus_MC12TuneV3_ProbNNk < 0.85 && muplus_MC12TuneV3_ProbNNk < 0.85 && muminus_MC12TuneV3_ProbNNghost < 0.4 && muplus_MC12TuneV3_ProbNNghost < 0.4)) "
#add in selection  KS0_M>460 && KS0_M<530
armenteros = "abs((((min(abs(mumu_APalpha-0.6916),abs(mumu_APalpha+0.6916)))*557.84*KS0_P/sqrt(KS0_P^2+1115.683^2) )^2+ mumu_APqt^2 )/10116.11 -1.) >0.2"

gec = "(nVeloClusters < 10000 && nITClusters < 10000 && nOTClusters < 15000 && nVeloTracks < 350 && nSPDHits < 900)"

noCut=""

strippingMuMu="(StrippingKS02MuMuLineDecision==1)" 

strippingMB="(StrippingKS02MuMuNoMuIDLineDecision==1)"

fiducial= selection + aa + armenteros + aa + gec

tististos="((KS0_L0MuonDecision_TIS==1 || KS0_L0DiMuonDecision_TIS==1 || KS0_L0HadronDecision_TIS==1 || KS0_L0ElectronDecision_TIS==1 || KS0_L0PhotonDecision_TIS==1)  && ((KS0_Hlt1DiMuonHighMassDecision_TIS || KS0_Hlt1DiMuonLowMassDecision_TIS || KS0_Hlt1SingleMuonNoIPDecision_TIS || KS0_Hlt1TrackMuonDecision_TIS ||KS0_Hlt1SingleMuonHighPTDecision_TIS || KS0_Hlt1TrackAllL0Decision_TIS || KS0_Hlt1TrackAllL0TightDecision_TIS ||KS0_Hlt1DiProtonDecision_TIS ||KS0_Hlt1DiProtonLowMultDecision_TIS ||KS0_Hlt1SingleElectronNoIPDecision_TIS || KS0_Hlt1TrackPhotonDecision_TIS || KS0_Hlt1VertexDisplVertexDecision_TIS)) && (KS0_Hlt2DiMuonDetachedDecision_TOS==1))"

tostos1tos="((KS0_L0MuonDecision_TOS==1) && (KS0_Hlt1TrackMuonDecision_TOS==1) && (KS0_Hlt2DiMuonDetachedDecision_TOS==1))"

tostos2tos="((KS0_L0MuonDecision_TOS==1) && (KS0_Hlt1DiMuonLowMassDecision_TOS==1) && (KS0_Hlt2DiMuonDetachedDecision_TOS==1))"

trigA = "(" + tostos1tos + ")" 

trigB = "(" + tostos2tos + aa + "!" + tostos1tos + ")"

trigC = " "

tistis="((KS0_L0MuonDecision_TIS==1 || KS0_L0DiMuonDecision_TIS==1 || KS0_L0HadronDecision_TIS==1 || KS0_L0ElectronDecision_TIS==1 || KS0_L0PhotonDecision_TIS==1) && (KS0_Hlt1Phys_TIS==1))"

tosHLT2="(KS0_Hlt2DiMuonDetachedDecision_TOS==1)"



fullsel = selection + aa + armenteros + aa + gec



def AND(*cuts):
    return " && ".join(cuts)

#bins = ["BDTb025de4nt1000M1_TosTos1Tos_AdBin == %i" % i for i in range(0, 10)]

#OLD BINNING
#cutsTOS1 = [0.0754, 0.1296, 0.1708, 0.2055, 0.2353, 0.2655, 0.2943, 0.3259, 0.3601, 0.4070, 1.0000]
#cutsTOS2 =  [0.1468, 0.1859, 0.2194, 0.2518, 0.2804, 0.3087, 0.3397, 0.3736, 0.4137, 0.4584, 1.0000]
#cutsTIS = [0.1495, 0.1852, 0.2168, 0.2462, 0.2757, 0.3048, 0.3362, 0.3681, 0.4056, 0.4535, 1.0000]


#NEW BINNING
#cutsTOS1 = [0.8195487856864929, 0.8804354667663574, 0.9205635786056519, 0.9448309540748596, 0.9615616202354431, 0.9743636250495911, 0.9824355244636536, 0.9885149598121643, 0.9927492141723633, 0.9959631562232971, 1.0]
cutsTOS2 = [0.7841112613677979, 0.8204695582389832, 0.8530916571617126, 0.8825569152832031, 0.9108163714408875, 0.9323615431785583, 0.9466038346290588, 0.9609434604644775, 0.9732581973075867, 0.983737587928772, 1.0]

#bins = ['%f <= BDTTosTos1Tos && BDTTosTos1Tos < %f' % i for i in zip(cutsTOS1[:-1], cutsTOS1[1:])]
bins = ['%f <= BDTTosTos2Tos && BDTTosTos2Tos < %f' % i for i in zip(cutsTOS2[:-1], cutsTOS2[1:])]


#binTIS = [-0.47770596071637, 0.07971142340475432, 0.14026170461797557, 0.18444871603585514, 0.22225635309191752, 0.2580670613406256, 0.2941205180849224, 0.33306522164617797, 0.3796568282758258, 0.4413369648554482, 1.]

#binTOS1 = [-0.5312869817266488, -0.1266664594344026, -0.018057598024261365, 0.05645428551488561, 0.1144174592588098, 0.1641042598190453, 0.2107112817081271, 0.2579244810661749, 0.3083928063263968, 0.369437934415055, 1.]

#binTOS2 = [-0.29663451166129434, 0.08271595580229936, 0.1425903605906138, 0.18821173949006376, 0.23086137292504383, 0.2672261002814406, 0.30348300632055697, 0.33827234947509255, 0.3816746510051476, 0.43741757427171485, 1.]

#bins=["(BDTb025de4nt1000M1_TosTos2Tos> %i && BDTb025de4nt1000M1_TosTos2Tos< %j)" ]
