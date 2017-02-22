def getconfig() :

    configdict = {}
    
    from math import pi
    from math import log

    # considered decay mode                                                       
    configdict["Decay"] = "Bd2DPi"
    configdict["CharmModes"] = {"KPiPi"}
    # year of data taking                                                                                                                          
    configdict["YearOfDataTaking"] = {"2011", "2012"}
    # stripping (necessary in case of PIDK shapes)                                                                                              
    configdict["Stripping"] = {"2012":"21", "2011":"21r1"}
    # integrated luminosity in each year of data taking (necessary in case of PIDK shapes)                                                                  
    configdict["IntegratedLuminosity"] = {"2011": {"Down":  0.56, "Up": 0.42}, "2012":{"Down": 0.9912, "Up": 0.9988}}
    # file name with paths to MC/data samples                                                                                                       
    configdict["dataName"]   = "../data/fsfd_5fb/Bd2DPi/config_Bd2DPi.txt" 
    #settings for control plots
    configdict["ControlPlots"] = {}
    configdict["ControlPlots"] = { "Directory": "PlotBd2DPi", "Extension":"pdf"}

    # basic variables                                                                                        
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range" : [5000,    6000    ], "InputName" : "lab0_MassFitConsD_M"}
    configdict["BasicVariables"]["CharmMass"]     = { "Range" : [1830,    1920    ], "InputName" : "lab2_MM"}
    configdict["BasicVariables"]["BacPIDK"]       = { "Range" : [-7.0,    6.0     ], "InputName" : "lab1_PIDK"}
    configdict["BasicVariables"]["BDTG"]          = { "Range" : [0.1,     1.0     ], "InputName" : "BDTGResponse_3"} 

    # additional cuts applied to data sets                                                                                    
    HLTcut = "(lab0_Hlt1TrackAllL0Decision_TOS == 1 && (lab0_Hlt2IncPhiDecision_TOS ==1 || lab0_Hlt2Topo2BodyBBDTDecision_TOS == 1 || lab0_Hlt2Topo3BodyBBDTDecision_TOS == 1))";
    configdict["AdditionalCuts"] = {}
    configdict["AdditionalCuts"]["All"]    = { "Data": "lab2_TAU>0&&lab1_PIDmu<2&&" + HLTcut, "MC" : "lab2_TAU>0&&lab1_M<200&&lab1_PIDmu<2&&" + HLTcut, "MCID":True, "MCTRUEID":True, "BKGCAT":True, "DsHypo":True}
    configdict["AdditionalCuts"]["KPiPi"]  = { "Data": "lab2_FDCHI2_ORIVX > 9", "MC" : "lab2_FDCHI2_ORIVX > 9"}

    # children prefixes used in MCID, MCTRUEID, BKGCAT cuts                                                                                                              
    # order of particles: KKPi, KPiPi, PiPiPi                                                                                                         
    configdict["DsChildrenPrefix"] = {"Child1":"lab3","Child2":"lab4","Child3": "lab5"} #lab3 = K, lab4, lab5 = pi

    # weighting templates by PID eff/misID, apply shifts to templates
    configdict["WeightingMassTemplates"] = {"PIDBachEff":    { "FileLabel": { "2011":"#PIDK Pion 2011", "2012":"#PIDK Pion 2012"},
                                                               "Var":["nTracks","lab1_P"], "HistName":"MyPionEff_0_mu2"},
                                            "PIDBachMisID":  { "FileLabel": { "2011":"#PIDK Kaon 2011", "2012":"#PIDK Kaon 2012"},
                                                               "Var":["nTracks","lab1_P"], "HistName":"MyKaonMisID_0_mu2"},
                                            "RatioDataMC":   { "FileLabel": {"2011":"#RatioDataMC 2011 PNTr", "2012": "#RatioDataMC 2011 PNTr"},
                                                               "Var":["lab1_P","nTracks"], "HistName":"histRatio"},
                                            "Shift":{ "BeautyMass": -2.0, "CharmMass": 0.0} }


    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#
    ###                                                               MDfit fitting settings
    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#
    # Bs signal shapes 
    configdict["BsSignalShape"] = {} 
    configdict["BsSignalShape"]["type"]    = "DoubleCrystalBallWithWidthRatio"
    configdict["BsSignalShape"]["mean"]    = {"Run1": {"All":5280.0},    "Fixed": False}
    configdict["BsSignalShape"]["sigma1"]  = {"Run1": {"KPiPi":12.812},  "Fixed": True} 
    configdict["BsSignalShape"]["sigma2"]  = {"Run1": {"KPiPi":21.587},  "Fixed": True} 
    configdict["BsSignalShape"]["alpha1"]  = {"Run1": {"KPiPi":2.0051},  "Fixed": True}
    configdict["BsSignalShape"]["alpha2"]  = {"Run1": {"KPiPi":-2.1356}, "Fixed": True}
    configdict["BsSignalShape"]["n1"]      = {"Run1": {"KPiPi":1.1071},  "Fixed": True}
    configdict["BsSignalShape"]["n2"]      = {"Run1": {"KPiPi":2.5920},  "Fixed": True}
    configdict["BsSignalShape"]["frac"]    = {"Run1": {"KPiPi":0.69420}, "Fixed": True}
    configdict["BsSignalShape"]["R"]       = {"Run1": {"KPiPi":1.0},     "Fixed": False}

    # Ds signal shapes  
    configdict["DsSignalShape"] = {}
    configdict["DsSignalShape"]["type"]    = "DoubleCrystalBallWithWidthRatio"
    configdict["DsSignalShape"]["mean"]    = {"Run1": {"All":1869.8},       "Fixed": False}
    configdict["DsSignalShape"]["sigma1"]  = {"Run1": {"KPiPi":11.501},     "Fixed": True}
    configdict["DsSignalShape"]["sigma2"]  = {"Run1": {"KPiPi":6.1237},     "Fixed": True}
    configdict["DsSignalShape"]["alpha1"]  = {"Run1": {"KPiPi":1.6382},     "Fixed": True}
    configdict["DsSignalShape"]["alpha2"]  = {"Run1": {"KPiPi":-3.4683},    "Fixed": True}
    configdict["DsSignalShape"]["n1"]      = {"Run1": {"KPiPi":4.8678},     "Fixed": True}
    configdict["DsSignalShape"]["n2"]      = {"Run1": {"KPiPi":4.3285e-06}, "Fixed": True}
    configdict["DsSignalShape"]["frac"]    = {"Run1": {"KPiPi":0.38916},    "Fixed": True}
    configdict["DsSignalShape"]["R"]       = {"Run1": {"KPiPi":1.0 },       "Fixed": False}

    # combinatorial background                                                                                                                              
    configdict["BsCombinatorialShape"] = {}
    configdict["BsCombinatorialShape"]["type"]  = "DoubleExponential"
    configdict["BsCombinatorialShape"]["cB1"]   = {"Run1": {"KPiPi":-1.0361e-03}, "Fixed": False}
    configdict["BsCombinatorialShape"]["cB2"]   = {"Run1": {"KPiPi":-0.01},       "Fixed": False}
    configdict["BsCombinatorialShape"]["frac"]  = {"Run1": {"KPiPi":0.5},         "Fixed": False}

    configdict["DsCombinatorialShape"] = {}
    configdict["DsCombinatorialShape"] = {}
    configdict["DsCombinatorialShape"]["type"]  = "ExponentialPlusDoubleCrystalBallWithWidthRatioSharedMean"
    configdict["DsCombinatorialShape"]["sigma1"]  = {"Run1": {"KPiPi":11.501},          "Fixed":True}
    configdict["DsCombinatorialShape"]["sigma2"]  = {"Run1": {"KPiPi":6.1237},          "Fixed":True}
    configdict["DsCombinatorialShape"]["alpha1"]  = {"Run1": {"KPiPi":1.6382},          "Fixed":True}
    configdict["DsCombinatorialShape"]["alpha2"]  = {"Run1": {"KPiPi":-3.4683},         "Fixed":True}
    configdict["DsCombinatorialShape"]["n1"]      = {"Run1": {"KPiPi":4.8678},          "Fixed":True}
    configdict["DsCombinatorialShape"]["n2"]      = {"Run1": {"KPiPi":4.3285e-06},      "Fixed":True}
    configdict["DsCombinatorialShape"]["frac"]    = {"Run1": {"KPiPi":0.38916},         "Fixed":True}
    configdict["DsCombinatorialShape"]["R"]       = {"Run1": {"KPiPi":1.5},             "Fixed":False}
    configdict["DsCombinatorialShape"]["cB"]      = {"Run1": {"KPiPi":-1.9193e-03},     "Fixed":False}
    configdict["DsCombinatorialShape"]["fracD"]   = {"Run1": {"KPiPi":0.5},             "Fixed":False}


    configdict["AdditionalParameters"] = {}
    configdict["AdditionalParameters"]["g1_f1_frac"] = {"Run1":{"All":{"Both":{"CentralValue":0.5, "Range":[0.0,1.0]}}}, "Fixed": False} 
    configdict["AdditionalParameters"]["g1_f2_frac"] = {"Run1":{"All":{"Both":{"CentralValue":0.5, "Range":[0.0,1.0]}}}, "Fixed": False}

    # expected yields (Bs2DsPi & Lb2LcPi fixed)
    configdict["Yields"] = {}
    configdict["Yields"]["Bd2DK"]     = {"2011": {"KPiPi":15000.0},  "2012": {"KPiPi":30000.0},  "Fixed": False} 
    configdict["Yields"]["Bd2DRho"]   = {"2011": {"KPiPi":80000.0},  "2012": {"KPiPi":160000.0}, "Fixed": False}
    configdict["Yields"]["Bd2DstPi"]  = {"2011": {"KPiPi":60000.0},  "2012": {"KPiPi":120000.0}, "Fixed": False}
    configdict["Yields"]["Bs2DsPi"]   = {"2011": {"KPiPi":1000.0},   "2012": {"KPiPi":2000.0},   "Fixed": True}
    configdict["Yields"]["Lb2LcPi"]   = {"2011": {"KPiPi":250.0},    "2012": {"KPiPi":500.0},    "Fixed": True}
    configdict["Yields"]["CombBkg"]   = {"2011": {"KPiPi":30000.0},  "2012": {"KPiPi":60000.0},  "Fixed": False}
    configdict["Yields"]["Signal"]    = {"2011": {"KPiPi":150000.0}, "2012": {"KPiPi":300000.0}, "Fixed": False}


    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#    
    ###                                                               MDfit plotting settings                                                             
    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#               
    from ROOT import *
    configdict["PlotSettings"] = {}
    configdict["PlotSettings"]["components"] = ["Sig", "CombBkg", "Bd2DK", "Lb2LcPi", "Bs2DsPi", "Bd2DRho", "Bd2DstPi"] 
    configdict["PlotSettings"]["colors"] = [kRed-7, kBlue-6, kOrange, kRed, kBlue-10, kYellow, kBlue+2]

    configdict["LegendSettings"] = {}
    configdict["LegendSettings"]["BeautyMass"] = {"Position":[0.53, 0.55, 0.90, 0.91], "TextSize": 0.04, "LHCbText":[0.35,0.9], "ScaleYSize":1.2}
    configdict["LegendSettings"]["CharmMass"]  = {"Position":[0.20, 0.69, 0.93, 0.93], "TextSize": 0.05, "LHCbText":[0.8,0.66],
                                                  "ScaleYSize":1.7, "SetLegendColumns":2, "LHCbTextSize":0.075 }
    configdict["LegendSettings"]["BacPIDK"]    = {"Position":[0.53, 0.45, 0.90, 0.91], "TextSize": 0.05, "LHCbText":[0.35,0.9], "ScaleYSize":1.2}

    return configdict
