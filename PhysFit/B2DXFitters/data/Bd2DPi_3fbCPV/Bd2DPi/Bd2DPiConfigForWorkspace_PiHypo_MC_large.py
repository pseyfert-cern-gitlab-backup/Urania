from ROOT import *

def getconfig() :

    configdict = {}
    
    from math import pi
    from math import log
    
    # considered decay mode
    configdict["Decay"] = "Bd2DPi"
    # PIDK for bachelor
    configdict["BachelorHypo"] = "Bd2DPi"
    configdict["CharmModes"] = {"KPiPi"} 
    # year of data taking
    configdict["YearOfDataTaking"] = {"2011","2012"} 
    # file name with paths to MC/data samples
    configdict["dataName"]   = "/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/config_Bd2DPi_MC_large.txt"
    # basic variables
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5220,    5600    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_FitDaughtersConst_M_flat"}

    configdict["BasicVariables"]["CharmMass"]     = { "Range"                  : [1830,    1904    ],
                                                      "Name"                   : "CharmMass",
                                                      "InputName"              : "lab0_FitwithoutConst_Dplus_M_flat"}

    configdict["BasicVariables"]["BeautyTime"]    = { "Range"                  : [0.4,     12.0    ],
                                                      "Bins"                   : 40,
                                                      "Name"                   : "BeautyTime",
                                                      "InputName"              : "obsTime"}

    configdict["BasicVariables"]["BacP"]          = { "Range"                  : [2000.0,  650000.0],
                                                      "Name"                   : "BacP",
                                                      "InputName"              : "lab0_FitDaughtersConst_P0_P_flat"}

    configdict["BasicVariables"]["BacPT"]         = { "Range"                  : [400.0,   45000.0 ],
                                                      "Name"                   : "BacPT",
                                                      "InputName"              : "lab0_FitDaughtersConst_P0_PT_flat"}

    configdict["BasicVariables"]["BacPIDK"]       = { "Range"                  : [-999.0,    999.0     ],
                                                      "Name"                   : "BacPIDK",
                                                      "InputName"              : "lab1_PIDKcorr"}

    configdict["BasicVariables"]["nTracks"]       = { "Range"                  : [15.0,    1000.0  ],
                                                      "Name"                   : "nTracks",
                                                      "InputName"              : "nTracks"}

    configdict["BasicVariables"]["BacCharge"]     = { "Range"                  : [-1000.0, 1000.0  ],
                                                      "Name"                   : "BacCharge",
                                                      "InputName"              : "lab1_TRUEID"}

    configdict["BasicVariables"]["TagDecTrue"]      = { "Range"                  : [-1.0,    1.0     ],
                                                        "Name"                   : "TagDecTrue",
                                                        "InputName"              : "TrueTag"}

    configdict["BasicVariables"]["TagDecOS"]      = { "Range"                  : [-1.0,    1.0     ],
                                                      "Name"                   : "TagDecOS",
                                                      "InputName"              : "TagDecOS"}

    configdict["BasicVariables"]["TagDecSS"]      = { "Range"                  : [-1.0,    1.0     ],
                                                      "Name"                   : "TagDecSS",
                                                      "InputName"              : "obsTagSS"}
    
    configdict["BasicVariables"]["MistagOS"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                      "Name"                   : "MistagOS",
                                                      "InputName"              : "MistagOS"}

    configdict["BasicVariables"]["MistagSS"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                      "Name"                   : "MistagSS",
                                                      "InputName"              : "obsEtaSS"}
    
    configdict["BasicVariables"]["BDTG"]           = { "Range"                  : [0.0, 1],
                                                       "Name"                   : "BDTG",
                                                       "InputName"              : "BDT_classifier"}

    #Additional variables not foreseen before
    configdict["AdditionalVariables"] = {}

    configdict["AdditionalVariables"]["BeautyPhi"]      = { "Range"                  : [ -10.,    10.     ],
                                                            "Name"                   : "BeautyPhi",
                                                            "InputName"              : "lab0_LOKI_PHI"}
    
    configdict["AdditionalVariables"]["BeautyEta"]      = { "Range"                  : [ 1.5,    10.0     ],
                                                            "Name"                   : "BeautyEta",
                                                            "InputName"              : "lab0_LOKI_ETA"}
    
    configdict["AdditionalVariables"]["BeautyPT"]      = { "Range"                  : [ 0.0,    100000     ],
                                                           "Name"                   : "BeautyPT",
                                                           "InputName"              : "lab0_PT"}

    configdict["AdditionalVariables"]["BeautyP"]      = { "Range"                  : [ 0.0,    3000000     ],
                                                          "Name"                   : "BeautyP",
                                                          "InputName"              : "lab0_P"}

    configdict["AdditionalVariables"]["CharmTime"]    = { "Range"                  : [-10,     10    ],
                                                          "Name"                   : "CharmTime",
                                                          "InputName"              : "lab2_TAU"}
    
    configdict["AdditionalVariables"]["nPV"]      = { "Range"                  : [ 0.0,    10     ],
                                                      "Name"                   : "nPV",
                                                      "InputName"              : "nPV"}

    configdict["AdditionalVariables"]["Hlt2Topo2BodyBBDTDecision_TOS"]      = { "Range"                  : [ 0.0,    1.0     ],
                                                                                "Name"                   : "Hlt2Topo2BodyBBDTDecision_TOS",
                                                                                "InputName"              : "lab0_Hlt2Topo2BodyBBDTDecision_TOS"}

    configdict["AdditionalVariables"]["Hlt2Topo3BodyBBDTDecision_TOS"]      = { "Range"                  : [ 0.0,    1.0     ],
                                                                                "Name"                   : "Hlt2Topo3BodyBBDTDecision_TOS",
                                                                                "InputName"              : "lab0_Hlt2Topo3BodyBBDTDecision_TOS"}

    configdict["AdditionalVariables"]["Hlt2Topo4BodyBBDTDecision_TOS"]      = { "Range"                  : [ 0.0,    1.0     ],
                                                                                "Name"                   : "Hlt2Topo4BodyBBDTDecision_TOS",
                                                                                "InputName"              : "lab0_Hlt2Topo4BodyBBDTDecision_TOS"}

    configdict["AdditionalVariables"]["TriggerCategoryBroad"]      = { "Range"                  : [ 0.0,    10     ],
                                                                       "Name"                   : "TriggerCategoryBroad",
                                                                       "InputName"              : "TriggerCategoryBroad"}

    # PIDK bin
    configdict["AdditionalCuts"] = {}
    configdict["AdditionalCuts"]["All"] = {"MC": "lab0_BKGCAT==0 && (obsTagOS!=0 || obsTagOSCharm!=0 || obsTagSSPionBDT!=0 || obsTagSSProton!=0) && BDT_classifier>0.0 && obsTime>0.4 && obsTime<12.0 && lab1_PIDKcorr<5.0 && lab0_FitDaughtersConst_M_flat>5220.0 && lab0_FitDaughtersConst_M_flat<5600.0 && nTracks>15 && nTracks<1000 && lab0_FitwithoutConst_Dplus_M_flat>1830 && lab0_FitwithoutConst_Dplus_M_flat<1904 && lab0_FitDaughtersConst_P0_P_flat>2000 && lab0_FitDaughtersConst_P0_P_flat<650000 && lab0_FitDaughtersConst_P0_PT_flat>400 && lab0_FitDaughtersConst_P0_PT_flat<45000 && lab0_LOKI_PHI>-10 && lab0_LOKI_PHI<10 && lab0_LOKI_ETA>1.5 && lab0_LOKI_ETA<10 && lab0_P>0 && lab0_P<3000000 && lab0_PT>0 && lab0_PT<100000"}
    
    return configdict
