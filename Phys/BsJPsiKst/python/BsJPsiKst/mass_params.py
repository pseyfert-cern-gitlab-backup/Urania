debug = True#False#

paramsMC={}
paramsMCError={}
for name in ("Bs","Bd","Combi","Lb2JpsipK","Lb2JpsipPi"):
    paramsMC[name]={}
    paramsMCError[name]={}

# ---- Bs and Bd Ipatia parameters as extracted from following MC samples:
#
# - Bd: 2012-4000GeV-MagUpAndDown-Nu2.5-Pythia8_Sim08a_Digi13_Trig0x409f0045_Reco14a_s20_dv33r4_WideLine_BDTG_wCosines.root
#       2011-3500GeV-MagUpAndDown-Nu2-Pythia8_Sim08b_Digi13_Trig0x40760037_Reco14a_s20r1_dv33r4_WideLine_BDTG_wCosines.root
#
# - Bs: 2012-4000GeV-MagUpAndDown-Nu2.5-Pythia8_Sim08a_Digi13_Trig0x409f0045_Reco14a_s20_dv33r4_WideLine_BDTG_Loose_wCosines.root
#       2011-3500GeV-MagUpAndDown-Nu2-Pythia8_Sim08c_Digi13_Trig0x40760037_Reco14a_s20r1_dv33r4_WideLine_BDTG_Loose_wCosines.root
# 
# -- with the following additional selection cuts applied:
#
## abs(B0_TRUEID) == 531 (or 511) && Kst_892_0_MM > binMin && Kst_892_0_MM < binMax && muplus_MINIPCHI2 > 16. && muminus_MINIPCHI2 > 16. && Kplus_MINIPCHI2 > 2. && piminus_MINIPCHI2 > 2. && B0_LOKI_DTF_CTAU > 0. && Kplus_PT > 500. && piminus_PT > 500. && (1>0) && abs(Mjpsik-5279) > 60. && B0_MM > 5150. && B0_MM < 5650. && piminus_ProbNNk<0.01 && Kplus_ProbNNk>0.21 && Kplus_ProbNNk/Kplus_ProbNNp>0.99 && piminus_ProbNNpi/piminus_ProbNNp>21.9 && BDTG>0.12

paramsMC["Bd"][0] = {'a': 2.2656433009857984, 'ipa_s': 7.62746024703638, 'l': -3.085637324450487, 'n': 0.8908863795254369, 'a2': 2.4487313780020497, 'ipa_m': 5279.869887390607, 'n2': 2.990092370113172}
paramsMC["Bd"][1] = {'a': 2.1254569691891243, 'ipa_s': 7.71017394392028, 'l': -2.871233448995821, 'n': 1.7675800875599095, 'a2': 2.480158856374114, 'ipa_m': 5279.818411049405, 'n2': 3.254510293218858}
paramsMC["Bd"][2] = {'a': 2.3410624063802983, 'ipa_s': 7.630607000118516, 'l': -3.2616532019149416, 'n': 2.1477830808908127, 'a2': 2.2264600120873768, 'ipa_m': 5280.263188385204, 'n2': 2.771527880977625}
paramsMC["Bd"][3] = {'a': 2.6188546441814253, 'ipa_s': 7.806525945564924, 'l': -2.787375581932504, 'n': 1.7273205540408685, 'a2': 2.304206375821028, 'ipa_m': 5280.306383329055, 'n2': 2.324700056250909}

paramsMC["Bs"][0] = {'a': 2.2141480428901987, 'ipa_s': 8.217926252360915, 'l': -2.5620079704573104, 'n': 0.9862222020806874, 'a2': 2.88480260306435, 'ipa_m': 5366.820946319278, 'n2': 3.0889594728801093}
paramsMC["Bs"][1] = {'a': 2.0983920018250783, 'ipa_s': 7.961961000329913, 'l': -3.3781634133703315, 'n': 1.8906639473137046, 'a2': 2.502863310444651, 'ipa_m': 5367.05856290582, 'n2': 3.123405380653052}
paramsMC["Bs"][2] = {'a': 3.0697864083495827, 'ipa_s': 8.115405643476851, 'l': -2.696182501266957, 'n': 1.5927603790224767, 'a2': 2.532489547349151, 'ipa_m': 5367.437071813083, 'n2': 2.3902301300178492}
paramsMC["Bs"][3] = {'a': 2.401743783959021, 'ipa_s': 8.043742972801681, 'l': -2.8433999511847254, 'n': 1.8386626703319662, 'a2': 2.636607231390629, 'ipa_m': 5367.501927613275, 'n2': 1.91074025907047}

paramsMCError["Bd"][0] = {'a': 0.07880885194237042, 'ipa_s': 0.1823557919446781, 'l': 0.41818149659250325, 'n': 0.08105439781969187, 'a2': 0.2581896432454218, 'ipa_m': 0.07556238679444505, 'n2': 0.4638956759351185}
paramsMCError["Bd"][1] = {'a': 0.064228522053009, 'ipa_s': 0.10441124608330021, 'l': 0.1921375530428029, 'n': 0.0961894677575329, 'a2': 0.15276640798883667, 'ipa_m': 0.03799005333576133, 'n2': 0.2662428416486704}
paramsMCError["Bd"][2] = {'a': 0.07253842078479966, 'ipa_s': 0.08633067183061849, 'l': 0.23172443199476866, 'n': 0.1334422016503325, 'a2': 0.07167489071122435, 'ipa_m': 0.038316713668791635, 'n2': 0.14303548212203943}
paramsMCError["Bd"][3] = {'a': 0.21418043764758998, 'ipa_s': 0.18454249618788632, 'l': 0.31111793805552335, 'n': 0.2624470528043995, 'a2': 0.16143456823092928, 'ipa_m': 0.0677289058162387, 'n2': 0.2097669873448651}

paramsMCError["Bs"][0] = {'a': 0.10876207647071712, 'ipa_s': 0.266945074634958, 'l': 0.34812870202465973, 'n': 0.09479608118501115, 'a2': 0.6653344696413319, 'ipa_m': 0.10430952550177608, 'n2': 0.8941261700434464}
paramsMCError["Bs"][1] = {'a': 0.05887145070107924, 'ipa_s': 0.11937279513431687, 'l': 0.332534577880899, 'n': 0.09431982186694632, 'a2': 0.1784096543126923, 'ipa_m': 0.05348424952126152, 'n2': 0.3486416311923928}
paramsMCError["Bs"][2] = {'a': 0.1746830652311382, 'ipa_s': 0.12549073462882188, 'l': 0.19107632597831037, 'n': 0.16984100393310575, 'a2': 0.22402818013409354, 'ipa_m': 0.05316551868600072, 'n2': 0.2658032030510511}
paramsMCError["Bs"][3] = {'a': 0.2069215823457604, 'ipa_s': 0.2519475310123296, 'l': 0.4408091293200127, 'n': 0.24777606584221123, 'a2': 0.29207518508686836, 'ipa_m': 0.094475259225419, 'n2': 0.2977038948971409}

print "Warning: Ipatia parameters for high Kpi mass bins not yet calculated. Using those of Bin4!!!"
for name in ("Bs","Bd"):
    for i in range(4,23):  
        paramsMC[name][i] = paramsMC[name][3]
        paramsMCError[name][i] = paramsMCError[name][3]

# -- Copy MC params to DATA, except for the sigma and mean Bd
paramsDATA={}
paramsDATAError={}
for name in ("Bs","Bd","Combi"):
    paramsDATA[name]={}
    paramsDATAError[name]={}
    if name != "Combi":
        for i in range(0,23):  
            paramsDATA[name][i]={}
            paramsDATAError[name][i]={}


# ---- Sigma Ipatia 
paramsDATA["Bd"][0]['ipa_s']= 8.42151e+00
paramsDATA["Bd"][1]['ipa_s']= 8.72087e+00
paramsDATA["Bd"][2]['ipa_s']= 8.55726e+00
paramsDATA["Bd"][3]['ipa_s']= 8.51278e+00

paramsDATA["Bs"][0]['ipa_s']= 6.97442e+00
paramsDATA["Bs"][1]['ipa_s']= 7.70024e+00
paramsDATA["Bs"][2]['ipa_s']= 7.50222e+00
paramsDATA["Bs"][3]['ipa_s']= 8.63392e+00

paramsDATAError["Bd"][0]['ipa_s']= 1.42936e-01
paramsDATAError["Bd"][1]['ipa_s']= 7.21010e-02
paramsDATAError["Bd"][2]['ipa_s']= 7.36043e-02
paramsDATAError["Bd"][3]['ipa_s']= 1.29598e-01

paramsDATAError["Bs"][0]['ipa_s']= 2.75475e+00
paramsDATAError["Bs"][1]['ipa_s']= 8.68026e-01
paramsDATAError["Bs"][2]['ipa_s']= 7.91073e-01
paramsDATAError["Bs"][3]['ipa_s']= 1.91148e+00


for name in ("Bs","Bd"):
    for i in range(0,4):
        paramsDATA[name][i] = paramsMC[name][i]
        paramsDATAError[name][i] = paramsMCError[name][i]
            #         for key in paramsMC[name][i].keys():
            #             if key != 'ipa_s': 
            #                 paramsDATA[name][i][key] = paramsMC[name][i][key]
            #                 paramsDATAError[name][i][key] = paramsMCError[name][i][key]
    for i in range(4,23):
        paramsDATA[name][i] = paramsMC[name][3]
        paramsDATAError[name][i] = paramsMCError[name][3]

# -- Combinatorial background exponential parmaeters as extracted from a fit to data (including Bs, Bd, Lb_pKn Lb_pPi, subtracted Bs and Bd peaking bkgs.)
# 
paramsDATA["Combi"][0] = {'k': -3.9e-03}
paramsDATA["Combi"][1] = {'k': -3.9e-03}
paramsDATA["Combi"][2] = {'k': -3.9e-03}
paramsDATA["Combi"][3] = {'k': -3.9e-03}

paramsDATAError["Combi"][0] = {'k': 9.0e-04}
paramsDATAError["Combi"][1] = {'k': 9.0e-04}
paramsDATAError["Combi"][2] = {'k': 9.0e-04}
paramsDATAError["Combi"][3] = {'k': 9.0e-04}

# -- Lb peaking backgrounds amoroso parmaeters as extracted from a fit to MC
# 
print "Warning: Lb ->Jpsi pK parameters obtained w/o cut in proton id because of statistics"
paramsMC["Lb2JpsipK"][0] = {'theta': -46.82772451084395, 'beta': 0.7973132340109821, 'mean': 5450.000002764214, 'alpha': 3.175407998579255}
paramsMC["Lb2JpsipK"][1] = {'theta': -4.425201762700567, 'beta': 0.43804182134083547,'mean': 5450.000004878752, 'alpha': 5.812870735869939}
paramsMC["Lb2JpsipK"][2] = {'theta': -4.653087430047549, 'beta': 0.586773206371161,  'mean': 5450.002678522607, 'alpha': 6.810612049257865}
paramsMC["Lb2JpsipK"][3] = {'theta': -245.84211636840246,'beta': 6.624930762109297,  'mean': 5450.000001794229, 'alpha': 0.22235521613816464}
paramsMC["Lb2JpsipK"][4] = {'theta': -8.048750268388517, 'beta': 0.5630648434653676, 'mean': 5489.814007575656, 'alpha': 6.370814287602278}
paramsMC["Lb2JpsipK"][5] = {'theta': -186.9270227055722, 'beta': 1.9657194137902465, 'mean': 5450.000001779561, 'alpha': 0.745696958248146}
paramsMC["Lb2JpsipK"][6] = {'theta': -223.84672062083632,'beta': 0.6868158148636425, 'mean': 5458.972755106203, 'alpha': 1.8757460402194843}
paramsMC["Lb2JpsipK"][7] = {'theta': -170.16841542192458,'beta': 0.8649389942346657, 'mean': 5460.693823214737, 'alpha': 1.5115444593117635}
paramsMC["Lb2JpsipK"][8] = {'theta': -264.63251778270376,'beta': 6.99996934942668,   'mean': 5457.862968757576, 'alpha': 0.16737533118784836}
paramsMC["Lb2JpsipK"][9] = {'theta': -274.7035144391857, 'beta': 2.4601622526943405, 'mean': 5478.034339880869, 'alpha': 0.5576630983338124}
paramsMC["Lb2JpsipK"][10] ={'theta': -1.003303145422251, 'beta': 0.4498935638810524, 'mean': 5463.9748386791525,'alpha': 9.05881469337755}
paramsMC["Lb2JpsipK"][11] ={'theta': -173.61746548474957,'beta': 1.230723721663061,  'mean': 5498.856571256128, 'alpha': 1.5923084626654034}
paramsMC["Lb2JpsipK"][12] ={'theta': -147.63470510238994,'beta': 1.0895572413290626, 'mean': 5457.959230933363, 'alpha': 1.1861270999745404}
paramsMC["Lb2JpsipK"][13] ={'theta': -265.4779252996334, 'beta': 1.2520287144092794, 'mean': 5461.199500743955, 'alpha': 1.0163909205766835}
paramsMC["Lb2JpsipK"][14] ={'theta': -144.66269702888758,'beta': 1.2388282494722578, 'mean': 5481.833325791209, 'alpha': 1.4131783024575646}
paramsMC["Lb2JpsipK"][15] ={'theta': -146.2464005509139, 'beta': 0.9540149944171397, 'mean': 5461.123484268863, 'alpha': 1.3322936121111024}
paramsMC["Lb2JpsipK"][16] ={'theta': -8.36725320507071,  'beta': 0.5741254142123386, 'mean': 5488.101214721536, 'alpha': 6.010087465271697}
paramsMC["Lb2JpsipK"][17] ={'theta': -86.31272456856516, 'beta': 0.9383448915470805, 'mean': 5479.7343003252545,'alpha': 2.286391641206691}
paramsMC["Lb2JpsipK"][18] ={'theta': -137.7846477554633, 'beta': 1.6835115391548374, 'mean': 5471.337747473818, 'alpha': 1.2459801175590153}
paramsMC["Lb2JpsipK"][19] ={'theta': -4.653296973296392, 'beta': 0.6275954402113966, 'mean': 5507.4445507443825,'alpha': 9.94967850289285}
paramsMC["Lb2JpsipK"][20] ={'theta': -2.2538797948479896,'beta': 0.5373827306799246, 'mean': 5489.448924168769, 'alpha': 9.996882838662687}
paramsMC["Lb2JpsipK"][21] ={'theta': -2.7963297610289146,'beta': 0.5427935521356124, 'mean': 5514.951702982295, 'alpha': 9.958559127874688}
paramsMC["Lb2JpsipK"][22] ={'theta': -9.290239199196321, 'beta': 0.6139934520365067, 'mean': 5489.324457241515, 'alpha': 6.659810723290944}

paramsMC["Lb2JpsipPi"][0] = {'theta': -112.45802406925861,'beta': 1.495785041150814, 'mean': 5767.958586951101, 'alpha': 8.935018443650058}
paramsMC["Lb2JpsipPi"][1] = {'theta': -281.8570541253787, 'beta': 2.2179133173824876,'mean': 5812.641203886989, 'alpha': 4.417973124798739}
paramsMC["Lb2JpsipPi"][2] = {'theta': -36.335328637022144,'beta': 0.8590717803323935,'mean': 5654.45376978495,  'alpha': 9.077479982264112}
paramsMC["Lb2JpsipPi"][3] = {'theta': -5.91445927387133,  'beta': 0.5576247756499013,'mean': 5544.964349096593, 'alpha': 9.960319461986177}
paramsMC["Lb2JpsipPi"][4] = {'theta': -40.60956592954403, 'beta': 0.9418982970568957,'mean': 5652.778007262554, 'alpha': 9.509104515766241}
paramsMC["Lb2JpsipPi"][5] = {'theta': -65.4716279479511,  'beta': 0.801692839554943, 'mean': 5534.560973322047, 'alpha': 4.0545195940806735}
paramsMC["Lb2JpsipPi"][6] = {'theta': -313.98155345913665,'beta': 5.16882708478024,  'mean': 5469.792948689196, 'alpha': 0.3282764361405077}
paramsMC["Lb2JpsipPi"][7] = {'theta': -217.688899793504,  'beta': 1.7236087568822551,'mean': 5658.2223944495645,'alpha': 3.3998067104568874}
paramsMC["Lb2JpsipPi"][8] = {'theta': -226.39188188412925,'beta': 1.6686703866358634,'mean': 5743.290617505931, 'alpha': 4.252970477482758}
paramsMC["Lb2JpsipPi"][9] = {'theta': -417.0091078011286, 'beta': 6.999594265979637, 'mean': 5596.786486126804, 'alpha': 0.36113123180278817}
paramsMC["Lb2JpsipPi"][10] ={'theta': -225.27170560360275,'beta': 1.6700518606055006,'mean': 5684.411333986952, 'alpha': 3.4257387592259114}
paramsMC["Lb2JpsipPi"][11] ={'theta': -318.3644264224238, 'beta': 2.2911456997867106,'mean': 6115.809937144358, 'alpha': 9.744881447173327}
paramsMC["Lb2JpsipPi"][12] ={'theta': -71.84237480715728, 'beta': 0.888629485440223, 'mean': 5726.064669702867, 'alpha': 7.049804373356001}
paramsMC["Lb2JpsipPi"][13] ={'theta': -548.5124076725021, 'beta': 6.999931966853595, 'mean': 5754.154150647429, 'alpha': 0.7040488219784737}
paramsMC["Lb2JpsipPi"][14] ={'theta': -28.16268492539666, 'beta': 0.788396860104986, 'mean': 5598.112956073126, 'alpha': 8.17787270045919}
paramsMC["Lb2JpsipPi"][15] ={'theta': -873.7967029152536, 'beta': 6.981957646381556, 'mean': 6071.603030202682, 'alpha': 0.9370826249309984}
paramsMC["Lb2JpsipPi"][16] ={'theta': -232.42587323268958,'beta': 1.8225530548577886,'mean': 5789.449062127197, 'alpha': 4.90046345367024}
paramsMC["Lb2JpsipPi"][17] ={'theta': -234.0252805442576, 'beta': 1.7009021555793975,'mean': 5843.8273786986,   'alpha': 5.6171612018059465}
paramsMC["Lb2JpsipPi"][18] ={'theta': -219.1571831831386, 'beta': 0.7915127312326637,'mean': 5528.18170093701,  'alpha': 2.535196608476309}
paramsMC["Lb2JpsipPi"][19] ={'theta': -580.3590275738372, 'beta': 3.619252978698775, 'mean': 6088.328094452663, 'alpha': 4.108597691234666}
paramsMC["Lb2JpsipPi"][20] ={'theta': -987.8326591865728, 'beta': 3.4541819041622794,'mean': 7086.549791190948, 'alpha': 9.66599421595111}
paramsMC["Lb2JpsipPi"][21] ={'theta': -320.2087276668648, 'beta': 2.2099944110960017,'mean': 6163.157182184773, 'alpha': 9.798194074998632}
paramsMC["Lb2JpsipPi"][22] ={'theta': -999.8516956336223, 'beta': 0.9242730241056183,'mean': 5509.845537968803, 'alpha': 1.7570774294220322}

print"Warning: same Lb2JpsipK and Lb2JpsipPi parameters for 2011 and 2012!!!"
for name in ("Lb2JpsipK","Lb2JpsipPi"):
    for i in range(0,23):  
        paramsMCError[name][i] = 0.

if debug:
    for name in ("Bs","Bd","Combi"):
        for key in paramsDATA[name][0].keys():
            for i in range(0,4):  
                print "DATA %s: %10f +/-%10f (%s bin%s)"%(key,paramsDATA[name][i][key],paramsDATAError[name][i][key],name,i)
