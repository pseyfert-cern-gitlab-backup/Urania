def getconfig() :

    configdict = {}
    
    from math import pi
    from math import log

    # considered decay mode                                                       
    configdict["Decay"] = "CombPi_BeautyMass"
    configdict["CharmModes"] = {"NonRes", "PhiPi", "KstK", "KPiPi", "PiPiPi"}
    # year of data taking                                                                                 
    configdict["YearOfDataTaking"] = {"2012", "2011"}
    # stripping (necessary in case of PIDK shapes)                               
    configdict["Stripping"] = {"2012":"21", "2011":"21r1"}
    # integrated luminosity in each year of data taking (necessary in case of PIDK shapes)
    configdict["IntegratedLuminosity"] = {"2011":{"Down": 0.5584, "Up": 0.4167}, "2012":{"Down": 0.9894, "Up": 0.9985}}
    # file name with paths to MC/data samples                                     
    configdict["dataName"] = "../data/Bs2DsstK_3fbCPV/Bs2DsstPi/config_Bs2DsstPi.txt"

    configdict["ControlPlots"] = {}
    configdict["ControlPlots"] = { "Directory": "PlotBs2DsstPi", "Extension":"pdf"}

    # basic variables                                                                                        
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range" : [5000,    6000    ], "InputName" : "FBs_DeltaM_M"}
    configdict["BasicVariables"]["CharmMass"]     = { "Range" : [2080,    2150    ], "InputName" : "FDsst_DeltaM_M"}
    configdict["BasicVariables"]["BeautyTime"]    = { "Range" : [0.4,     12.0    ], "InputName" : "FBs_LF_ctau"}
    configdict["BasicVariables"]["BacP"]          = { "Range" : [1000.,   650000.0], "InputName" : "FBac_P"}
    configdict["BasicVariables"]["BacPT"]         = { "Range" : [500.,    45000.0 ], "InputName" : "FBac_Ptr"}
    configdict["BasicVariables"]["BacPIDK"]       = { "Range" : [-7.0,    5.0     ], "InputName" : "FBac_PIDK"}
    configdict["BasicVariables"]["nTracks"]       = { "Range" : [15.,     1000.0  ], "InputName" : "FnTracks"}
    configdict["BasicVariables"]["BeautyTimeErr"] = { "Range" : [0.01,    0.1     ], "InputName" : "FBs_LF_ctauErr"}
    configdict["BasicVariables"]["BacCharge"]     = { "Range" : [-1000.0, 1000.0  ], "InputName" : "FBac_ID"}
    configdict["BasicVariables"]["BDTG"]          = { "Range" : [-1.,     1.0     ], "InputName" : "FBDT_Var"}
    configdict["BasicVariables"]["TagDecOS"]      = { "Range" : [-1.0,    1.0     ], "InputName" : "FBs_TAGDECISION_OS"}
    configdict["BasicVariables"]["TagDecSS"]      = { "Range" : [-1.0,    1.0     ], "InputName" : "FBs_SS_nnetKaon_DEC"}
    configdict["BasicVariables"]["MistagOS"]      = { "Range" : [0.0,     0.5     ], "InputName" : "FBs_TAGOMEGA_OS"}
    configdict["BasicVariables"]["MistagSS"]      = { "Range" : [0.0,     0.5     ], "InputName" : "FBs_SS_nnetKaon_PROB"}
    
     #----------------------------------------------------------------------------------------------------------------------------------------------------------------#
    ###                                                               MDfit fitting settings
    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#
    
    # Bs signal shapes
    configdict["BsSignalShape"] = {}
    configdict["BsSignalShape"]["type"]    = "RooHILLidni"
    configdict["BsSignalShape"]["a"]       = {"Run1": {"All": 5200.0}, "Fixed":False}
    configdict["BsSignalShape"]["b"]       = {"Run1": {"All": 5400.0}, "Fixed":False}
    configdict["BsSignalShape"]["csi"]     = {"Run1": {"All": 1.0},    "Fixed":False}
    configdict["BsSignalShape"]["shift"]   = {"Run1": {"All": 0.0},    "Fixed":True}
    configdict["BsSignalShape"]["sigma"]   = {"Run1": {"All": 20.0},   "Fixed":False}
    configdict["BsSignalShape"]["R"]       = {"Run1": {"All": 5.0},    "Fixed":False}
    configdict["BsSignalShape"]["frac"]    = {"Run1": {"All": 0.95},    "Fixed":False}
    
    
    #expected yields
    configdict["Yields"] = {}
    configdict["Yields"]["Signal"]     = {"2012": {"NonRes":10000.0, "PhiPi":10000.0, "KstK":10000.0, "KPiPi":5000.0, "PiPiPi":5000.0},
                                          "2011": {"NonRes":5000.0, "PhiPi":5000.0, "KstK":5000.0, "KPiPi":2500.0, "PiPiPi":2500.0}, "Fixed":False}


    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#    
    ###                                                               MDfit plotting settings
    #----------------------------------------------------------------------------------------------------------------------------------------------------------------#

    from ROOT import *
    configdict["PlotSettings"] = {}
    configdict["PlotSettings"] = {}
    configdict["PlotSettings"]["components"] = ["Sig"] #, "CombBkg", "Bd2DsstPi", "Bs2DsRho", "Bs2DsstRho"]
    configdict["PlotSettings"]["colors"] = [kRed-7] #, kBlue-6, kOrange, kBlue-10, kGreen+3]
    #configdict["PlotSettings"]["components"] = ["Sig", "CombBkg", "Bs2DsRho", "Bs2DsstRho"]
    #configdict["PlotSettings"]["colors"] = [kRed-7, kBlue-6, kBlue-10, kGreen+3]

    configdict["LegendSettings"] = {}
    configdict["LegendSettings"]["BeautyMass"] = {"Position":[0.53, 0.45, 0.90, 0.91], "TextSize": 0.05, "LHCbText":[0.35,0.9]}
    configdict["LegendSettings"]["CharmMass"]  = {"Position":[0.20, 0.69, 0.93, 0.93], "TextSize": 0.05, "LHCbText":[0.8,0.66],
                                                  "ScaleYSize":1.75, "SetLegendColumns":2, "LHCbTextSize":0.075 }
    configdict["LegendSettings"]["BacPIDK"]    = {"Position":[0.20, 0.69, 0.93, 0.93], "TextSize": 0.05, "LHCbText":[0.2,0.9], 
                                                  "ScaleYSize":1.5, "SetLegendColumns":2, "LHCbTextSize":0.075}

    return configdict
