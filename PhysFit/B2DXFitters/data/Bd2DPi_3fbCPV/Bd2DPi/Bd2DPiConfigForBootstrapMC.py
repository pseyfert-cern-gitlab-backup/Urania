from ROOT import *

def getconfig() :

    configdict = {}
    
    # basic variables
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5090,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_FitDaughtersConst_M_flat"}
    
    configdict["BasicVariables"]["BeautyTime"]    = { "Range"                  : [0.4,     12.0    ],
                                                      "Bins"                   : 40,
                                                      "Name"                   : "BeautyTime",
                                                      "InputName"              : "obsTime"
                                                      }
    
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
                                                      "InputName"              : "obeEtaSS"}
    
    configdict["BasicVariables"]["BDTG"]           = { "Range"                  : [0.0, 1],
                                                       "Name"                   : "BDTG",
                                                       "InputName"              : "BDT_classifier"}
    
    #Additional variables not foreseen before
    configdict["AdditionalVariables"] = {}
    
    configdict["AdditionalVariables"]["BeautyEta"]      = { "Range"                  : [ 1.5,    10.0     ],
                                                            "Name"                   : "BeautyEta",
                                                            "InputName"              : "lab0_LOKI_ETA"}
    
    configdict["AdditionalVariables"]["BeautyPT"]      = { "Range"        : [ 0.0,    10     ],
                                                           "Name"                   : "nPV",
                                                           "InputName"              : "nPV"}

    configdict["AdditionalVariables"]["BeautyP"]      = { "Range"                  : [ 0.0,    3000000     ],
                                                          "Name"                   : "BeautyP",
                                                          "InputName"              : "lab0_P"}

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


    
    return configdict
                        
