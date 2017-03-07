def getconfig() :

    configdict = {}
    
    from math import pi
    from math import log

    # considered decay mode                                                       
    configdict["Decay"] = "Bs2DsPi"
    configdict["CharmModes"] = {"KstK","NonRes","PhiPi"}
    # year of data taking                                                                                                                          
    configdict["YearOfDataTaking"] = {"2011","2012"}
    # stripping (necessary in case of PIDK shapes)                                                                                              
    configdict["Stripping"] = {"2012":"21", "2011":"21r1"}
    # integrated luminosity in each year of data taking (necessary in case of PIDK shapes)                                                                 
    configdict["IntegratedLuminosity"] = {"2011": {"Down":  0.56, "Up": 0.42}, "2012":{"Down": 0.9912, "Up": 0.9988}}
    # file name with paths to MC/data samples                                                                                                       
    configdict["dataName"]   = "../data/fsfd_5fb/Bs2DsPi/config_Bs2DsPi_newBDTG.txt"
    #settings for control plots                                                                                                                                                           
    configdict["ControlPlots"] = {}
    configdict["ControlPlots"] = { "Directory": "PlotBs2DsPi_Nominal", "Extension":"pdf"}

    # basic variables                                                                                        
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range" : [5100,    5800    ], "InputName" : "lab0_MassFitConsD_M"}
    configdict["BasicVariables"]["CharmMass"]     = { "Range" : [1930,    2015    ], "InputName" : "lab2_MM"}
    configdict["BasicVariables"]["BacPIDK"]       = { "Range" : [-7.0,    5.0     ], "InputName" : "lab1_PIDK"} #-7.0,6.0
    configdict["BasicVariables"]["BDTG"]          = { "Range" : [ 0.1,    1.0     ], "InputName" : "BDTGResponse_3"}


    HLTcut = "&&(lab0_Hlt1TrackAllL0Decision_TOS && (lab0_Hlt2IncPhiDecision_TOS ==1 || lab0_Hlt2Topo2BodyBBDTDecision_TOS == 1 || lab0_Hlt2Topo3BodyBBDTDecision_TOS == 1))"
    # additional cuts applied to data sets                                                                                    
    configdict["AdditionalCuts"] = {}
    configdict["AdditionalCuts"]["All"]    = { "Data": "lab2_TAU>0&&lab1_PIDmu<2"+HLTcut,        
                                               "MC" : "lab2_TAU>0&&lab1_M<200&&lab1_PIDK !=-1000.0"+HLTcut, "MCID":True, "MCTRUEID":True, "BKGCAT":True, "DsHypo":True}
    configdict["AdditionalCuts"]["KKPi"]   = { "Data": "lab2_FDCHI2_ORIVX > 2", "MC" : "lab2_FDCHI2_ORIVX > 2"}
    configdict["AdditionalCuts"]["KPiPi"]  = { "Data": "lab2_FDCHI2_ORIVX > 9", "MC" : "lab2_FDCHI2_ORIVX > 9"}
    configdict["AdditionalCuts"]["PiPiPi"] = { "Data": "lab2_FDCHI2_ORIVX > 9", "MC" : "lab2_FDCHI2_ORIVX > 9"}

    # children prefixes used in MCID, MCTRUEID, BKGCAT cuts                                                                                                              
    # order of particles: KKPi, KPiPi, PiPiPi                                                                                                         
    configdict["DsChildrenPrefix"] = {"Child1":"lab3","Child2":"lab4","Child3": "lab5"}

    #weighting templates by PID eff/misID                                                                                                                                                 
    configdict["WeightingMassTemplates"]= { "PIDBachEff":            { "FileLabel": { "2011":"#PIDK Pion 2011", "2012":"#PIDK Pion 2012"}, 
                                                                       "Var":["nTracks","lab1_P"], "HistName":"MyPionEff_0_mu2"},
                                            "PIDBachMisID":          { "FileLabel": { "2011":"#PIDK Kaon 2011", "2012":"#PIDK Kaon 2012"}, 
                                                                       "Var":["nTracks","lab1_P"], "HistName":"MyKaonMisID_0_mu2"},
                                            "PIDChildKaonPionMisID": { "FileLabel": { "2011":"#PIDK Pion 2011", "2012":"#PIDK Pion 2012"}, 
                                                                       "Var":["nTracks","lab3_P"], "HistName":"MyPionMisID_0"}, 
                                            "PIDChildProtonMisID":   { "FileLabel": { "2011":"#PIDK Proton 2011", "2012":"#PIDK Proton 2012"}, 
                                                                       "Var":["nTracks","lab4_P"], "HistName":"MyProtonMisID_pKm5_KPi5"}, 
                                            "RatioDataMC":{ "FileLabel": {"2011":"#RatioDataMC 2011 PNTr", "2012": "#RatioDataMC 2011 PNTr"}, 
                                                            "Var":["lab1_P","nTracks"], "HistName":"histRatio"},   
                                            "Shift":{ "BeautyMass": -2.0, "CharmMass": 0.0} }


    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#
    ###                                                               MDfit fitting settings
    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#
    
    # Bs signal shapes                                                                                                                                   
    configdict["BsSignalShape"] = {}
    configdict["BsSignalShape"]["type"]    = "DoubleCrystalBallWithWidthRatio"
    configdict["BsSignalShape"]["mean"]    = {"Run1": {"All":5367.51}, "Fixed":False}
    configdict["BsSignalShape"]["sigma1"]  = {"Run1": {"NonRes" : 17.4755,   "PhiPi" : 18.3892,   "KstK" : 12.392,    },  "Fixed" : True}
    configdict["BsSignalShape"]["sigma2"]  = {"Run1": {"NonRes" : 11.5424,   "PhiPi" : 11.4315,   "KstK" : 16.0298,   },  "Fixed" : True}
    configdict["BsSignalShape"]["alpha1"]  = {"Run1": {"NonRes" : -2.18147,  "PhiPi" : -2.18571,  "KstK" : -1.83432,  },  "Fixed" : True}
    configdict["BsSignalShape"]["alpha2"]  = {"Run1": {"NonRes" : 2.15494,   "PhiPi" : 2.24804,   "KstK" : 1.25656,   },  "Fixed" : True}
    configdict["BsSignalShape"]["n1"]      = {"Run1": {"NonRes" : 2.53609,   "PhiPi" : 2.36718,   "KstK" : 2.82347,   },  "Fixed" : True}
    configdict["BsSignalShape"]["n2"]      = {"Run1": {"NonRes" : 0.518479,  "PhiPi" : 0.410215,  "KstK" : 5.16839,   },  "Fixed" : True}
    configdict["BsSignalShape"]["frac"]    = {"Run1": {"NonRes":0.5,         "PhiPi":0.5,         "KstK":0.5,         },  "Fixed" : True}
    configdict["BsSignalShape"]["R"]       = {"Run1": {"NonRes":1.00,        "PhiPi":1.0,          "Kstk":1.0,        },  "Fixed" : False}

    #Ds signal shapes                                                                                                                                       
    configdict["DsSignalShape"] = {}
    configdict["DsSignalShape"]["type"]    = "DoubleCrystalBallWithWidthRatio"
    configdict["DsSignalShape"]["mean"]    = {"Run1": {"All":1968.49}, "Fixed":False} 
    configdict["DsSignalShape"]["sigma1"]  = {"Run1": {"NonRes" : 5.94251,   "PhiPi" : 5.37138,   "KstK" : 5.63019,   },  "Fixed" : True}
    configdict["DsSignalShape"]["sigma2"]  = {"Run1": {"NonRes" : 5.50472,   "PhiPi" : 5.89377,   "KstK" : 6.17574,   },  "Fixed" : True}
    configdict["DsSignalShape"]["alpha1"]  = {"Run1": {"NonRes" : -1.1612,   "PhiPi" : -1.1131,   "KstK" : -1.18225,  },  "Fixed" : True}
    configdict["DsSignalShape"]["alpha2"]  = {"Run1": {"NonRes" : 1.2832,    "PhiPi" : 1.14251,   "KstK" : 1.26344,   },  "Fixed" : True}
    configdict["DsSignalShape"]["n1"]      = {"Run1": {"NonRes" : 16.048,    "PhiPi" : 8.68961,   "KstK" : 11.378,    },  "Fixed" : True}
    configdict["DsSignalShape"]["n2"]      = {"Run1": {"NonRes" : 3.68624,   "PhiPi" : 5.8552,    "KstK" : 5.88566,   },  "Fixed" : True}
    configdict["DsSignalShape"]["frac"]    = {"Run1": {"NonRes":0.50,        "PhiPi":0.50,        "KstK":0.50,        },  "Fixed" : True}
    configdict["DsSignalShape"]["R"]       = {"Run1": {"NonRes":1.00,        "PhiPi":1.00,        "KstK":1.00,        },  "Fixed" : False}

    # combinatorial background                                                                                                                              
    configdict["BsCombinatorialShape"] = {}
    configdict["BsCombinatorialShape"]["type"]  = "DoubleExponential"
    configdict["BsCombinatorialShape"]["cB1"]   = {"Run1": {"NonRes":-3.5211e-02,  "PhiPi":-3.0873e-02,  "KstK":-2.3392e-02 }, "Fixed": False}
    configdict["BsCombinatorialShape"]["cB2"]   = {"Run1": {"NonRes":0.0,          "PhiPi":0.0,          "KstK":0.0},          "Fixed": True }
    configdict["BsCombinatorialShape"]["frac"]  = {"Run1": {"NonRes":4.3067e-01,   "PhiPi":6.5400e-01,   "KstK":3.7409e-01,},  "Fixed": False}
    
    configdict["DsCombinatorialShape"] = {}
    configdict["DsCombinatorialShape"]["type"]  = "ExponentialPlusSignal" #"ExponentialPlusDoubleCrystalBallWithWidthRatioSharedMean"
    configdict["DsCombinatorialShape"]["sigma1"]  = {"Run1": {"NonRes":5.2639e+00,  "PhiPi":5.7789e+00,  "KstK":5.5277e+00},  "Fixed":True}
    configdict["DsCombinatorialShape"]["sigma2"]  = {"Run1": {"NonRes":5.7588e+00,  "PhiPi":5.3142e+00,  "KstK":5.9173e+00},  "Fixed":True}
    configdict["DsCombinatorialShape"]["alpha1"]  = {"Run1": {"NonRes":-1.1429e+00, "PhiPi":-1.0496e+00, "KstK":-1.1662e+00}, "Fixed":True}
    configdict["DsCombinatorialShape"]["alpha2"]  = {"Run1": {"NonRes":1.1400e+00,  "PhiPi":1.1819e+00,  "KstK":1.1958e+00},  "Fixed":True}
    configdict["DsCombinatorialShape"]["n1"]      = {"Run1": {"NonRes":1.1892e+01,  "PhiPi":4.9291e+01,  "KstK":1.7661e+01},  "Fixed":True}
    configdict["DsCombinatorialShape"]["n2"]      = {"Run1": {"NonRes":7.6655e+00,  "PhiPi":4.9162e+00,  "KstK":9.4543e+00},  "Fixed":True}
    configdict["DsCombinatorialShape"]["frac"]    = {"Run1": {"NonRes":0.50,        "PhiPi":0.50,        "KstK":0.50},        "Fixed":True}
    configdict["DsCombinatorialShape"]["R"]       = {"Run1": {"NonRes":1.00,        "PhiPi":1.5,         "Kstk":1.5},         "Fixed":False}
    configdict["DsCombinatorialShape"]["cD"]      = {"Run1": {"NonRes":-5.7520e-03, "PhiPi":-5.7273e-03, "KstK":-8.3967e-03}, "Fixed":False}
    configdict["DsCombinatorialShape"]["fracD"]   = {"Run1": {"NonRes":0.88620,      "PhiPi":0.37379,    "KstK":0.59093},     "Fixed":False}

    configdict["PIDKCombinatorialShape"] = {}
    configdict["PIDKCombinatorialShape"]["type"] = "Fixed"
    configdict["PIDKCombinatorialShape"]["components"] = { "Kaon":True, "Pion":True, "Proton":False }
    configdict["PIDKCombinatorialShape"]["fracPIDK1"]   = { "Run1":{"NonRes":0.9, "PhiPi":0.9, "KstK":0.9, "KPiPi":0.8, "PiPiPi":0.8 }, "Fixed":False }
    configdict["PIDKCombinatorialShape"]["fracPIDK2"]   = { "Run1":{"NonRes":0.9, "PhiPi":0.9, "KstK":0.9, "KPiPi":0.8, "PiPiPi":0.8 }, "Fixed":False }


    #Bd2Dsh background
    #shape for BeautyMass, for CharmMass as well as BacPIDK taken by default the same as signal 
    configdict["Bd2Ds(st)XShape"] = {}
    configdict["Bd2Ds(st)XShape"]["type"]    = "ShiftedSignal"
    configdict["Bd2Ds(st)XShape"]["decay"]   = "Bd2DsPi"
    configdict["Bd2Ds(st)XShape"]["shift"]   = {"Run1": {"All": 86.8}, "Fixed":True}
    configdict["Bd2Ds(st)XShape"]["scale1"]  = {"Run1": {"All": 1.00808721452}, "Fixed":True}
    configdict["Bd2Ds(st)XShape"]["scale2"]  = {"Run1": {"All": 1.03868673310}, "Fixed":True}

    #
    configdict["AdditionalParameters"] = {}
    configdict["AdditionalParameters"]["g1_f1_frac"] = {"Run1":{"All":{"Both":{"CentralValue":0.5, "Range":[0.0,1.0]}}}, "Fixed":False}
    configdict["AdditionalParameters"]["g1_f2_frac"] = {"Run1":{"All":{"Both":{"CentralValue":0.5, "Range":[0.0,1.0]}}}, "Fixed":False}


    #expected yields                                                                                                                                                       
    configdict["Yields"] = {}
    configdict["Yields"]["Bd2DsPi"]         = {"2011": { "NonRes":400.0,   "PhiPi":500.0,   "KstK":500.0},
                                               "2012": { "NonRes":400.0,   "PhiPi":500.0,   "KstK":500.0},  "Fixed":False}
    configdict["Yields"]["Bd2DPi"]          = {"2011": { "NonRes":50.4,    "PhiPi":3.5,     "KstK":10.3},
                                               "2012": { "NonRes":100.5,   "PhiPi":7.8,     "KstK":21.4},  "Fixed":True}
    configdict["Yields"]["Lb2LcPi"]         = {"2011": { "NonRes":140.4,   "PhiPi":30.7,    "KstK":46.2},
                                               "2012": { "NonRes":342.0,   "PhiPi":64.7,    "KstK":108.0},  "Fixed":True}
    configdict["Yields"]["Bs2DsK"]          = {"2011": { "NonRes":30.5,    "PhiPi":77.8,    "KstK":41.6},
                                               "2012": { "NonRes":85.7,    "PhiPi":184.1,   "KstK":121.0}, "Fixed":True}
    configdict["Yields"]["Bs2DsDsstPiRho"]  = {"2011": { "NonRes":10000.0, "PhiPi":10000.0, "KstK":10000.0},
                                               "2012": { "NonRes":20000.0, "PhiPi":20000.0, "KstK":20000.0}, "Fixed":False}
    configdict["Yields"]["CombBkg"]         = {"2011": { "NonRes":10000.0, "PhiPi":10000.0, "KstK":10000.0},
                                               "2012": { "NonRes":20000.0, "PhiPi":20000.0, "KstK":20000.0},"Fixed":False}
    configdict["Yields"]["Signal"]          = {"2011": { "NonRes":10000.0, "PhiPi":10000.0, "KstK":10000.0},
                                               "2012": { "NonRes":20000.0, "PhiPi":20000.0, "KstK":20000.0},"Fixed":False}


    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#    
    ###                                                               MDfit plotting settings                                                             
    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#               
    from ROOT import *
    configdict["PlotSettings"] = {}
    configdict["PlotSettings"]["components"] = ["Sig", "CombBkg", "Bd2DPi", "Lb2LcPi", "Bs2DsDsstPiRho", "Bs2DsK", "Bd2DsPi"] 
    configdict["PlotSettings"]["colors"] = [kRed-7, kBlue-6, kOrange, kRed, kBlue-10, kGreen+3, kMagenta+2]

    configdict["LegendSettings"] = {}
    configdict["LegendSettings"]["BeautyMass"] = {"Position":[0.53, 0.45, 0.90, 0.91], "TextSize": 0.05, "LHCbText":[0.35,0.9], "ScaleYSize":1.2}
    configdict["LegendSettings"]["CharmMass"]  = {"Position":[0.20, 0.69, 0.93, 0.93], "TextSize": 0.05, "LHCbText":[0.8,0.66],
                                                  "ScaleYSize":1.7, "SetLegendColumns":2, "LHCbTextSize":0.075 }
    configdict["LegendSettings"]["BacPIDK"]    = {"Position":[0.53, 0.45, 0.90, 0.91], "TextSize": 0.05, "LHCbText":[0.20,0.9], "ScaleYSize":1.2}

    return configdict
