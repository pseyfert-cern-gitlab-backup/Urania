
# ----------------------------------------------------------------
# Definition of the cuts used in the analysis
aa = "&&"

selection = "((KS0_TAU < 0.13 && KS0_TAU > 0. && muplus_IP_OWNPV > 0.5 && muminus_IP_OWNPV > 0.5 && KS0_ENDVERTEX_CHI2 < 25. && muplus_P < 100.e3 && muminus_P < 100.e3 && muminus_MC12TuneV3_ProbNNk < 0.85 && muplus_MC12TuneV3_ProbNNk < 0.85 && muminus_MC12TuneV3_ProbNNghost < 0.4 && muplus_MC12TuneV3_ProbNNghost < 0.4))"

armenteros = "abs((((min(abs(mumu_APalpha-0.6916),abs(mumu_APalpha+0.6916)))*557.84*KS0_P/sqrt(KS0_P**2+1115.683**2) )**2+ mumu_APqt**2 )/10116.11 -1.) >0.2"

gec = "(nVeloClusters < 10000 && nITClusters < 10000 && nOTClusters < 15000 && nVeloTracks < 350 && nSPDHits < 900)"


tostos1tos = "((KS0_L0MuonDecision_TOS==1) && (KS0_Hlt1TrackMuonDecision_TOS==1) &&  (KS0_Hlt2DiMuonDetachedDecision_TOS==1))"

tostos2tos = "((KS0_L0MuonDecision_TOS==1) && (KS0_Hlt1DiMuonLowMassDecision_TOS==1) &&  (KS0_Hlt2DiMuonDetachedDecision_TOS==1))"

tististos = "(((KS0_L0MuonDecision_TIS==1 || KS0_L0DiMuonDecision_TIS==1 || KS0_L0HadronDecision_TIS==1 || KS0_L0ElectronDecision_TIS==1 || KS0_L0PhotonDecision_TIS==1) && (KS0_Hlt1Phys_TIS==1) && (KS0_Hlt2DiMuonDetachedDecision_TOS==1))) "

fullsel = selection + aa + armenteros + aa + gec
minsel = selection + aa + gec

# ----------------------------------------------------------------
# Names for the BDT and the MuID
bdtname = {}
bdtname['TIS_'] = 'BDTb025de4nt1000M1_TisTisTos'
bdtname['TOS1_'] = 'BDTTosTos1Tos'
bdtname['TOS2_'] = 'BDTTosTos2Tos'
MuIDname = 'muonIDPlusBDT'

# ----------------------------------------------------------------
# Functions to get dictionaries with the BDT and MuID cuts per bin
def BDT_cuts(trigcat):
    bdt = bdtname[trigcat]
    if trigcat == 'TIS_':
        Binning = binTIS
    elif trigcat == 'TOS1_':
        Binning = binTOS1
    else:
        Binning = binTOS2
    BDT = {}
    for i  in range(len(Binning)-1):
        BDT[i] =  " && "+bdt+">=" + str(Binning[i]) +" && "+bdt+"<" + str(Binning[i+1])
    return BDT

def MuID_cuts(trigcat):
    if trigcat == 'TIS_':
        Binning = MuID_TIS
    elif trigcat == 'TOS1_':
        Binning = MuID_TOS1
    else:
        Binning = MuID_TOS2
    MuID = {}
    for i in xrange(len(Binning)):
        ct = str(Binning[i])
        MuID[i] = " && muplus_" + MuIDname + ">=" + ct + " && muminus_" + MuIDname + ">=" + ct
    return MuID

def BDTplusMuID_cuts(trigcat):
    MuID = MuID_cuts(trigcat)
    BDT  = BDT_cuts(trigcat)
    cuts = {}
    for kw in BDT:
        cuts[kw] = BDT[kw] + MuID[kw]
    return cuts

# ----------------------------------------------------------------
# Selections for each trigger category
SEL = {}
SEL["TOS1_"] = "(" + fullsel + aa+ tostos1tos  + ")"

SEL["TOS2_"] = "("+ fullsel + aa + tostos2tos + aa + "!" + tostos1tos +  ")"

SEL["TIS_"] = "(" + fullsel + aa+ tististos + ")"

fSEL = {}
fSEL["TOS1_"] = "(" + minsel + aa+ tostos1tos +  ")"

fSEL["TOS2_"] = "("+ minsel + aa + tostos2tos + aa + "!" + tostos1tos + ")"

fSEL["TIS_"] = "(" + minsel + aa+ tististos + ")"

# ----------------------------------------------------------------
# Definition of the cuts to make the proxies
ProxyL0TOS1 = '(muplus_L0match || muminus_L0match)'
ProxyL0TOS2 = '( muplus_L0match || muminus_L0match ) && muplus_PT < 1000 && muminus_PT < 1000'
ProxyHlt2   = 'KS0_PT > 600'

#ProxyBase = fullsel + aa + 'KS0_M > 492. && KS0_M < 504.' + aa + ProxyHlt2
ProxyBase = fullsel + aa + 'KS0_M > 492. && KS0_M < 504.' 

PROXIES = {}
#PROXIES['TIS_']  = ProxyBase + aa + '(muplus_PT>300 && muminus_PT>300) && (muplus_P>4500 && muminus_P>4500)'
#PROXIES['TOS1_'] = ProxyBase + aa + ProxyL0TOS1 + '(KS0_PT>1000) && (MaxMu_PT>1250) && (MaxMu_P>8000) && (MinMu_P>4000)'
#PROXIES['TOS2_'] = ProxyBase + aa + ProxyL0TOS2 + '(muplus_PT>490 && muminus_PT>490) && (muplus_P>5500 && muminus_P>5500)'
#PROXIES['BKG_']  = fullsel + aa + '(KS0_M>600 && KS0_M<950)'

PROXIES['TIS_']  = ProxyBase 
PROXIES['TOS1_'] = ProxyBase 
PROXIES['TOS2_'] = ProxyBase
PROXIES['BKG_']  = fullsel + aa + '(KS0_M>520 && KS0_M<600)'


# ----------------------------------------------------------------
# Definition of the low edges for the BDT bins in each trigger category

#binTIS  = [ 0.1495, 0.1852, 0.2168, 0.2462, 0.2757, 0.3048, 0.3362, 0.3681, 0.4056, 0.4535, 1.0000 ]
binTOS1 = [0.8195487856864929, 0.8804354667663574, 0.9205635786056519, 0.9448309540748596, 0.9615616202354431, 0.9743636250495911, 0.9824355244636536, 0.9885149598121643, 0.9927492141723633, 0.9959631562232971, 1.0]
binTOS2 = [0.7841112613677979, 0.8204695582389832, 0.8530916571617126, 0.8825569152832031, 0.9108163714408875, 0.9323615431785583, 0.9466038346290588, 0.9609434604644775, 0.9732581973075867, 0.983737587928772, 1.0]


# ----------------------------------------------------------------
# Definition of the MuID cuts for each bin and category
MuID_TIS  = 10*[ +0.07 ]

MuID_TOS1 = 10*[ -0.01 ]

MuID_TOS2 = 10*[ +0.02 ]
