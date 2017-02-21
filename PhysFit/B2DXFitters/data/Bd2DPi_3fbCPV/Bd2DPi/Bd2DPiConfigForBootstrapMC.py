from ROOT import *

def getconfig() :

    configdict = {}
    
    # basic variables
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5090,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_FitDaughtersConst_M_flat"}
    
    configdict["BasicVariables"]["BeautyTime"]    = { "Range"                  : [0.2,     15.0    ],
                                                      "Bins"                   : 40,
                                                      "Name"                   : "BeautyTime",
                                                      "InputName"              : "lab0_FitDaughtersPVConst_ctau_flat"\
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

    configdict["BasicVariables"]["TagDecOSCharm"]      = { "Range"                  : [-1.0,    1.0     ],
                                                           "Name"                   : "TagDecOSCharm",
                                                           "InputName"              : "obsTagOSCharm"}

    configdict["BasicVariables"]["TagDecOSComb"]      = { "Range"                  : [-1.0,    1.0     ],
                                                          "Name"                   : "TagDecOSComb",
                                                          "InputName"              : "obsTagOS"}
    
    configdict["BasicVariables"]["TagDecSS"]      = { "Range"                  : [-1.0,    1.0     ],
                                                      "Name"                   : "TagDecSS",
                                                      "InputName"              : "TagDecSS"}

    configdict["BasicVariables"]["TagDecSSPionBDT"]      = { "Range"                  : [-1.0,    1.0     ],
                                                             "Name"                   : "TagDecSSPionBDT",
                                                             "InputName"              : "obsTagSSPionBDT_InvBoost"}

    configdict["BasicVariables"]["TagDecSSProton"]      = { "Range"                  : [-1.0,    1.0     ],
                                                            "Name"                   : "TagDecSSProton",
                                                            "InputName"              : "obsTagSSProton_InvBoost"}
    
    configdict["BasicVariables"]["MistagOS"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                      "Name"                   : "MistagOS",
                                                      "InputName"              : "MistagOS"}

    configdict["BasicVariables"]["MistagOSCharm"]      = { "Range"                  : [0.0,    0.5     ],
                                                           "Name"                   : "MistagOSCharm",
                                                           "InputName"              : "obsEtaOSCharm"}

    configdict["BasicVariables"]["MistagOSComb"]      = { "Range"                  : [0.0,    0.5     ],
                                                          "Name"                   : "MistagOSComb",
                                                          "InputName"              : "obsEtaOS"}
    
    configdict["BasicVariables"]["MistagSS"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                      "Name"                   : "MistagSS",
                                                      "InputName"              : "MistagSS"}

    configdict["BasicVariables"]["MistagSSPionBDT"]      = { "Range"                  : [0.0,    0.5     ],
                                                             "Name"                   : "MistagSSPionBDT",
                                                             "InputName"              : "obsEtaSSPionBDT_InvBoost"}

    configdict["BasicVariables"]["MistagSSProton"]      = { "Range"                  : [0.0,    0.5     ],
                                                            "Name"                   : "MistagSSProton",
                                                            "InputName"              : "obsEtaSSProton_InvBoost"}
    
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
    
    return configdict
                        
