def getconfig() :

    configdict = {}
    
    from math import pi
    from math import log

    # considered decay mode                                                       
    configdict["Decay"] = "Bd2DPi"
    configdict["CharmModes"] = {"KPiPi"}
    # year of data taking                                                                                                                          
    configdict["YearOfDataTaking"] = {"2012"}
    # stripping (necessary in case of PIDK shapes)                                                                                              
    configdict["Stripping"] = {"2011":"21r1", "2012":"21"}  # , "2011":"21r1"}
    # integrated luminosity in each year of data taking (necessary in case of PIDK shapes)                                                                  
    configdict["IntegratedLuminosity"] = {"2011": {"Down":  0.56, "Up": 0.42}, "2012":{"Down": 0.9912, "Up": 0.9988}}  #"2011": {"Down":  0.56, "Up": 0.42}
    # file name with paths to MC/data samples                                                                                                       
    configdict["dataName"]   = "../data/fsfd_5fb/Bd2DPi/config_Bd2DPi.txt" 
    #settings for control plots
    configdict["ControlPlots"] = {}
    configdict["ControlPlots"] = { "Directory": "PlotBd2DPi", "Extension":"pdf"}

    # basic variables                                                                                        
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range" : [5000,    5800    ], "InputName" : "lab0_MassFitConsD_M"} #data 5000-5800, then you can change to whatever you want 
    configdict["BasicVariables"]["CharmMass"]     = { "Range" : [1830,    1920    ], "InputName" : "lab2_MM"}  # data 1830 - 1920, 
    configdict["BasicVariables"]["BacPIDK"]       = { "Range" : [-7.0,    6.0     ], "InputName" : "lab1_PIDK"}
    configdict["BasicVariables"]["BDTG"]          = { "Range" : [0.1,     1.0     ], "InputName" : "BDTGResponse_3"} 

    #additional cuts applied to data sets
    lab = "&& lab1_M<200 && lab3_M > 200 && lab4_M < 200 && lab5_M <200" 
    mDKPi = "&&(lab2_MM-lab34_MM > 200) && (lab2_MM-lab35_MM > 200)"
    D0Kpi1 = "&&!(abs(sqrt(pow(sqrt(pow(493.67,2)+pow(lab1_P,2))+sqrt(pow(lab5_M,2)+pow(lab5_P,2)),2)-pow(lab1_PX+lab5_PX,2)-pow(lab1_PY+lab5_PY,2)-pow(lab1_PZ+lab5_PZ,2))-1870)<20)"
    D0Kpi2 = "&&!(abs(sqrt(pow(sqrt(pow(493.67,2)+pow(lab1_P,2))+sqrt(pow(lab4_M,2)+pow(lab4_P,2)),2)-pow(lab1_PX+lab4_PX,2)-pow(lab1_PY+lab4_PY,2)-pow(lab1_PZ+lab4_PZ,2))-1870)<20)"
    life = "&&lab2_TAU>0&&lab2_FD_ORIVX > 0."
    veto_lb1 = "&&!(fabs(lab2_MassHypo_Lambda_pi1 - 2286.4) < 30. && lab4_PIDp > 0)"
    veto_lb2 = "&&!(fabs(lab2_MassHypo_Lambda_pi2 - 2286.4) < 30. && lab5_PIDp > 0)"
    veto_dspi1 = "&&((lab2_MassHypo_Ds_pi1 < 1949. || lab2_MassHypo_Ds_pi1 > 2029. || lab4_PIDK < 0.))"
    veto_dspi2 = "&&((lab2_MassHypo_Ds_pi2 < 1949. || lab2_MassHypo_Ds_pi2 > 2029. || lab5_PIDK < 0.))"
    # additional cuts applied to data sets                                                                                    
    HLTcut = "(lab0_Hlt1TrackAllL0Decision_TOS == 1 && (lab0_Hlt2Topo2BodyBBDTDecision_TOS == 1 || lab0_Hlt2Topo3BodyBBDTDecision_TOS == 1 || lab0_Hlt2Topo4BodyBBDTDecision_TOS == 1) && (lab0_L0HadronDecision_TOS || lab0_L0Global_TIS ==1))";

    configdict["AdditionalCuts"] = {}
    configdict["AdditionalCuts"]["All"]    = { "Data": "lab1_PIDK<0&&lab2_TAU>0&&lab1_PIDmu<2" +mDKPi+D0Kpi1+D0Kpi2+life+veto_lb1+veto_lb2+veto_dspi1+veto_dspi2+lab, 
						"MC" : "lab2_TAU>0&&lab1_M<200" +mDKPi+D0Kpi1+D0Kpi2+life+lab, 
						"MCID":True, "MCTRUEID":True, "BKGCAT":True, "DsHypo":True}
    configdict["AdditionalCuts"]["KPiPi"]  = { "Data": "lab2_FDCHI2_ORIVX > 9", "MC" : "lab2_FDCHI2_ORIVX > 9"}
    
    #configdict["AdditionalCuts"]["TransverseMomentum"] = {"Data": "lab0_PT> 1500 && lab0_PT<40000", "MC" : "lab0_PT>1500 && lab0_PT<40000"}
    #configdict["AdditionalCuts"]["MomentumBachelor"] = {"Data": "lab1_P<150000", "MC" : "lab1_P<150000"}
    #configdict["AdditionalCuts"]["Eta"] = {"Data": "lab0_ETA>2 && lab0_ETA>2", "MC" : "lab0_ETA>2 && lab0_ETA<5"}

    # children prefixes used in MCID, MCTRUEID, BKGCAT cuts                                                                                                              
    # order of particles: KKPi, KPiPi, PiPiPi                                                                                                         
    configdict["DsChildrenPrefix"] = {"Child1":"lab3","Child2":"lab4","Child3": "lab5"} #lab3 = K, lab4, lab5 = pi

    # weighting templates by PID eff/misID, apply shifts to templates
    configdict["WeightingMassTemplates"] = {"PIDBachEff":    { "FileLabel": { "2011":"#PIDK Pion 2011", "2012":"#PIDK Pion 2012"},
                                                               "Var":["nTracks","lab1_P"], "HistName":"MyPionEff_0_mu2"},
                                            "PIDBachMisID":  { "FileLabel": { "2011":"#PIDK Kaon 2011", "2012":"#PIDK Kaon 2012"},
                                                               "Var":["nTracks","lab1_P"], "HistName":"MyKaonMisID_0_mu2"},
                                            "RatioDataMC":   { "FileLabel": {"2011":"#RatioDataMC 2011 PNTr", 
                                                                             "2012":"#RatioDataMC 2012 PNTr"}, #filtered for signal!, not filtered for bkg
                                                               "Var":["lab1_P","nTracks"], "HistName":"histRatio"},
                                            "Shift":{ "BeautyMass": 2.5, "CharmMass": 0.0} }


    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#
    ###                                                               MDfit fitting settings
    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#
    # Bs signal shapes 
    #configdict["BsSignalShape"] = {} 
    #configdict["BsSignalShape"]["type"]    = "DoubleCrystalBallWithWidthRatio"
    #configdict["BsSignalShape"]["mean"]    = {"Run1": {"All":5280.0},    "Fixed": False}
    #configdict["BsSignalShape"]["sigma1"]  = {"Run1": {"KPiPi":17.918},  "Fixed": True} 
    #configdict["BsSignalShape"]["sigma2"]  = {"Run1": {"KPiPi":11.882},  "Fixed": True} 
    #configdict["BsSignalShape"]["alpha1"]  = {"Run1": {"KPiPi":-2.0221},  "Fixed": True}
    #configdict["BsSignalShape"]["alpha2"]  = {"Run1": {"KPiPi":1.6922}, "Fixed": True}
    #configdict["BsSignalShape"]["n1"]      = {"Run1": {"KPiPi":3.2641},  "Fixed": True}
    #configdict["BsSignalShape"]["n2"]      = {"Run1": {"KPiPi":1.2653},  "Fixed": True}
    #configdict["BsSignalShape"]["frac"]    = {"Run1": {"KPiPi":0.5}, "Fixed": True}
    #configdict["BsSignalShape"]["R"]       = {"Run1": {"KPiPi":1.0},     "Fixed": False}

    # Bd signal shape Ipatia+JohnsonSU
    configdict["BsSignalShape"] = {} 
    configdict["BsSignalShape"]["type"]         = "IpatiaPlusJohnsonSU"
    configdict["BsSignalShape"]["mean"]         = {"Run1": {"All":5280.0},     "Fixed": False}
    configdict["BsSignalShape"]["l"]            = {"Run1": {"KPiPi":-0.9997},  "Fixed": True} 
    configdict["BsSignalShape"]["zeta"]         = {"Run1": {"KPiPi":0.0},      "Fixed": True} 
    configdict["BsSignalShape"]["fb"]           = {"Run1": {"KPiPi":0.0},      "Fixed": True}
    configdict["BsSignalShape"]["nu"]           = {"Run1": {"KPiPi":-0.12999}, "Fixed": True}
    configdict["BsSignalShape"]["tau"]          = {"Run1": {"KPiPi":0.4273},   "Fixed": True}
   # configdict["BsSignalShape"]["shift"]        = {"Run1": {"KPiPi":1.2653},  "Fixed": True}
   # configdict["BsSignalShape"]["meanShift"]    = {"Run1": {"KPiPi":0.5},     "Fixed": False}
    configdict["BsSignalShape"]["sigmaI"]       = {"Run1": {"KPiPi":22.355},    "Fixed": True}
    configdict["BsSignalShape"]["sigmaJ"]       = {"Run1": {"KPiPi":15.695},    "Fixed": True}
    configdict["BsSignalShape"]["a1"]           = {"Run1": {"KPiPi":0.5586},    "Fixed": True}    
    configdict["BsSignalShape"]["a2"]           = {"Run1": {"KPiPi":5.6699},    "Fixed": True}
    configdict["BsSignalShape"]["n1"]           = {"Run1": {"KPiPi":1.5866},    "Fixed": True}
    configdict["BsSignalShape"]["n2"]           = {"Run1": {"KPiPi":1.7686},    "Fixed": True}
   # configdict["BsSignalShape"]["scalea"]       = {"Run1": {"KPiPi":1.0},      "Fixed": True}    
   # configdict["BsSignalShape"]["scalen"]       = {"Run1": {"KPiPi":1.0},      "Fixed": True}
    configdict["BsSignalShape"]["frac"]         = {"Run1": {"KPiPi":0.16119},   "Fixed": True}





    # Ds signal shapes  
    configdict["DsSignalShape"] = {}
    configdict["DsSignalShape"]["type"]    = "DoubleCrystalBallWithWidthRatio"
    configdict["DsSignalShape"]["mean"]    = {"Run1": {"All":1869.8},       "Fixed": False}
    configdict["DsSignalShape"]["sigma1"]  = {"Run1": {"KPiPi":11.501},     "Fixed": False}
    configdict["DsSignalShape"]["sigma2"]  = {"Run1": {"KPiPi":6.1237},     "Fixed": False}
    configdict["DsSignalShape"]["alpha1"]  = {"Run1": {"KPiPi":1.6382},     "Fixed": False}
    configdict["DsSignalShape"]["alpha2"]  = {"Run1": {"KPiPi":-3.4683},    "Fixed": False}
    configdict["DsSignalShape"]["n1"]      = {"Run1": {"KPiPi":4.8678},     "Fixed": False}
    configdict["DsSignalShape"]["n2"]      = {"Run1": {"KPiPi":4.3285e-06}, "Fixed": False}
    configdict["DsSignalShape"]["frac"]    = {"Run1": {"KPiPi":0.38916},    "Fixed": False}
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
    configdict["DsCombinatorialShape"]["sigma1"]  = {"Run1": {"KPiPi":11.501},          "Fixed":False}
    configdict["DsCombinatorialShape"]["sigma2"]  = {"Run1": {"KPiPi":6.1237},          "Fixed":False}
    configdict["DsCombinatorialShape"]["alpha1"]  = {"Run1": {"KPiPi":1.6382},          "Fixed":False}
    configdict["DsCombinatorialShape"]["alpha2"]  = {"Run1": {"KPiPi":-3.4683},         "Fixed":False}
    configdict["DsCombinatorialShape"]["n1"]      = {"Run1": {"KPiPi":4.8678},          "Fixed":False}
    configdict["DsCombinatorialShape"]["n2"]      = {"Run1": {"KPiPi":4.3285e-06},      "Fixed":False}
    configdict["DsCombinatorialShape"]["frac"]    = {"Run1": {"KPiPi":0.38916},         "Fixed":False}
    configdict["DsCombinatorialShape"]["R"]       = {"Run1": {"KPiPi":1.5},             "Fixed":False}
    configdict["DsCombinatorialShape"]["cB"]      = {"Run1": {"KPiPi":-1.9193e-03},     "Fixed":False}
    configdict["DsCombinatorialShape"]["fracD"]   = {"Run1": {"KPiPi":0.5},             "Fixed":False}

    #modelling two-horned shape 
    #configdict["BeautyMassBd2DstPiShape"] = {}
    #configdict["BeautyMassBd2DstPiShape"]["type"]  = "DoubleGaussianSeparatedMean"
    #configdict["BeautyMassBd2DstPiShape"]["sigma1"]  = {"Run1": {"KPiPi":15.0},          "Fixed":False}
    #configdict["BeautyMassBd2DstPiShape"]["sigma2"]  = {"Run1": {"KPiPi":15.0},          "Fixed":False}
    #configdict["BeautyMassBd2DstPiShape"]["mean"]    = {"Run1": {"KPiPi":5030.0},        "Fixed":False}
    #configdict["BeautyMassBd2DstPiShape"]["mean2"]   = {"Run1": {"KPiPi":5110.0},        "Fixed":False}
    #configdict["BeautyMassBd2DstPiShape"]["frac"]   = {"Run1": {"KPiPi":0.5},        "Fixed":False} 

    configdict["AdditionalParameters"] = {}
    configdict["AdditionalParameters"]["g1_f1_frac"] = {"Run1":{"All":{"Both":{"CentralValue":0.5, "Range":[0.0,1.0]}}}, "Fixed": False} 
    configdict["AdditionalParameters"]["g1_f2_frac"] = {"Run1":{"All":{"Both":{"CentralValue":0.5, "Range":[0.0,1.0]}}}, "Fixed": False}

    #expected yields (Bs2DsPi & Lb2LcPi fixed)
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
