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
    configdict["YearOfDataTaking"] = {"2012"} 
    # file name with paths to MC/data samples
    configdict["dataName"]   = "/afs/cern.ch/user/v/vibattis/cmtuser/Urania_v5r0/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/config_Bd2DPi.txt"
        
    # basic variables
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5090,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_FitDaughtersConst_M_flat"}

    configdict["BasicVariables"]["CharmMass"]     = { "Range"                  : [1830,    1904    ],
                                                      "Name"                   : "CharmMass",
                                                      "InputName"              : "lab0_FitwithoutConst_Dplus_M_flat"}

    configdict["BasicVariables"]["BeautyTime"]    = { "Range"                  : [0.2,     15.0    ],
                                                      "Bins"                   : 40,
                                                      "Name"                   : "BeautyTime",
                                                      "InputName"              : "lab0_FitDaughtersPVConst_ctau_flat"}
    
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

    configdict["BasicVariables"]["BeautyTimeErr"] = { "Range"                  : [0.01,    0.1     ],
                                                      "Name"                   : "BeautyTimeErr",
                                                      "InputName"              : "lab0_FitDaughtersPVConst_ctauErr_flat"}

    configdict["BasicVariables"]["BacCharge"]     = { "Range"                  : [-1000.0, 1000.0  ],
                                                      "Name"                   : "BacCharge",
                                                      "InputName"              : "lab1_ID"}

    configdict["BasicVariables"]["TagDecOSComb"]      = { "Range"                  : [-1.0,    1.0     ],
                                                          "Name"                   : "TagDecOSComb",
                                                          "InputName"              : "obsTagOS"}

    configdict["BasicVariables"]["TagDecOSCharm"]      = { "Range"                  : [-1.0,    1.0     ],
                                                           "Name"                   : "TagDecOSCharm",
                                                           "InputName"              : "obsTagOSCharm"}

    configdict["BasicVariables"]["TagDecOSKaon"]      = { "Range"                  : [-1.0,    1.0     ],
                                                          "Name"                   : "TagDecOSKaon",
                                                          "InputName"              : "obsTagOSKaon"}

    configdict["BasicVariables"]["TagDecOSElectron"]      = { "Range"                  : [-1.0,    1.0     ],
                                                              "Name"                   : "TagDecOSElectron",
                                                              "InputName"              : "obsTagOSElectron"}

    configdict["BasicVariables"]["TagDecOSMuon"]      = { "Range"                  : [-1.0,    1.0     ],
                                                          "Name"                   : "TagDecOSMuon",
                                                          "InputName"              : "obsTagOSMuon"}

    configdict["BasicVariables"]["TagDecVtxCharge"]      = { "Range"                  : [-1.0,    1.0     ],
                                                             "Name"                   : "TagDecVtxCharge",
                                                             "InputName"              : "obsTagVtxQ"}

    configdict["BasicVariables"]["TagDecSSPionBDT"]      = { "Range"                  : [-1.0,    1.0     ],
                                                             "Name"                   : "TagDecSSPionBDT",
                                                             "InputName"              : "obsTagSSPionBDT"}
    
    configdict["BasicVariables"]["TagDecSSProton"]      = { "Range"                  : [-1.0,    1.0     ],
                                                            "Name"                   : "TagDecSSProton",
                                                            "InputName"              : "obsTagSSProton"}

    configdict["BasicVariables"]["MistagOSComb"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                          "Name"                   : "MistagOSComb",
                                                          "InputName"              : "obsEtaOS"}

    configdict["BasicVariables"]["MistagOSCharm"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                           "Name"                   : "MistagOSCharm",
                                                           "InputName"              : "obsEtaOSCharm"}

    configdict["BasicVariables"]["MistagOSKaon"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                          "Name"                   : "MistagOSKaon",
                                                          "InputName"              : "obsEtaOSKaon"}

    configdict["BasicVariables"]["MistagOSElectron"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                              "Name"                   : "MistagOSElectron",
                                                              "InputName"              : "obsEtaOSElectron"}

    configdict["BasicVariables"]["MistagOSMuon"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                          "Name"                   : "MistagOSMuon",
                                                          "InputName"              : "obsEtaOSMuon"}

    configdict["BasicVariables"]["MistagVtxCharge"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                             "Name"                   : "MistagVtxCharge",
                                                             "InputName"              : "obsEtaVtxQ"}
    
    configdict["BasicVariables"]["MistagSSPionBDT"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                             "Name"                   : "MistagSSPionBDT",
                                                             "InputName"              : "obsEtaSSPionBDT"}

    configdict["BasicVariables"]["MistagSSProton"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                            "Name"                   : "MistagSSProton",
                                                            "InputName"              : "obsEtaSSProton"}
    
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
    
    configdict["AdditionalVariables"]["nPV"]      = { "Range"                  : [ 0.0,    10     ],
                                                      "Name"                   : "nPV",
                                                      "InputName"              : "nPV"}

    # PIDK bin
    configdict["AdditionalCuts"] = {}
    configdict["AdditionalCuts"]["All"] = {"Data": "lab1_PIDK<5.0", "MC": "lab1_PIDKcorr<5.0&&lab0_BKGCAT<60"}

    
    return configdict
