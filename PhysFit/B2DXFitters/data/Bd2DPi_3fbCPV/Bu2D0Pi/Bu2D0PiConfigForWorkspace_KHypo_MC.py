from ROOT import *

def getconfig() :

    configdict = {}
    
    from math import pi
    from math import log
    
    # considered decay mode
    configdict["Decay"] = "Bu2D0Pi"
    # PIDK for bachelor
    configdict["BachelorHypo"] = "Bu2D0K"
    configdict["CharmModes"] = {"KPi"} 
    # year of data taking
    configdict["YearOfDataTaking"] = {"2011","2012"} 
    # file name with paths to MC/data samples
    configdict["dataName"]   = "/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bu2D0Pi/config_Bu2D0Pi.txt"
        
    # basic variables
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5130,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_MM"}

    configdict["BasicVariables"]["CharmMass"]     = { "Range"                  : [1830,    1904    ],
                                                      "Name"                   : "CharmMass",
                                                      "InputName"              : "lab2_MM"}

    configdict["BasicVariables"]["BeautyTime"]    = { "Range"                  : [0.0004,     0.012    ],
                                                      "Bins"                   : 40,
                                                      "Name"                   : "BeautyTime",
                                                      "InputName"              : "lab0_TAU"}
    
    configdict["BasicVariables"]["BacP"]          = { "Range"                  : [2000.0,  650000.0],
                                                      "Name"                   : "BacP",
                                                      "InputName"              : "lab1_P"}

    configdict["BasicVariables"]["BacPT"]         = { "Range"                  : [400.0,   45000.0 ],
                                                      "Name"                   : "BacPT",
                                                      "InputName"              : "lab1_PT"}

    configdict["BasicVariables"]["BacPIDK"]       = { "Range"                  : [-999.0,    999.0     ],
                                                      "Name"                   : "BacPIDK",
                                                      "InputName"              : "lab1_PIDKcorr"}

    configdict["BasicVariables"]["nTracks"]       = { "Range"                  : [15.0,    1000.0  ],
                                                      "Name"                   : "nTracks",
                                                      "InputName"              : "nTracks"}

    configdict["BasicVariables"]["BacCharge"]     = { "Range"                  : [-1000.0, 1000.0  ],
                                                      "Name"                   : "BacCharge",
                                                      "InputName"              : "lab1_TRUEID"}

    configdict["BasicVariables"]["TagDecOSComb"]      = { "Range"                  : [-1.0,    1.0     ],
                                                          "Name"                   : "TagDecOSCharm",
                                                          "InputName"              : "lab0_TAGDECISION_OS"}

    configdict["BasicVariables"]["TagDecOSCharm"]      = { "Range"                  : [-1.0,    1.0     ],
                                                           "Name"                   : "TagDecOSCharm",
                                                           "InputName"              : "lab0_OS_Charm_DEC"}

    configdict["BasicVariables"]["MistagOSComb"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                          "Name"                   : "MistagOSComb",
                                                          "InputName"              : "lab0_TAGOMEGA_OS"}

    configdict["BasicVariables"]["MistagOSCharm"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                           "Name"                   : "MistagOSCharm",
                                                           "InputName"              : "lab0_OS_Charm_PROB"}

    #Additional variables not foreseen before
    configdict["AdditionalVariables"] = {}

    configdict["AdditionalVariables"]["BeautyID"]      = { "Range"                  : [ -1000.,    1000.     ],
                                                           "Name"                   : "BeautyID",
                                                           "InputName"              : "lab0_TRUEID"}
    
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

    configdict["AdditionalVariables"]["Hlt2Topo4BodyBBDTDecision_TOS"]      = { "Range"                  : [ 0.0,    1.0    ],
                                                                                "Name"                   : "Hlt2Topo4BodyBBDTDecision_TOS",
                                                                                "InputName"              : "lab0_Hlt2Topo4BodyBBDTDecision_TOS"}

    # PIDK bin
    configdict["AdditionalCuts"] = {}
    configdict["AdditionalCuts"]["All"] = {"MC": "lab1_PIDKcorr>5.0&&lab0_BKGCAT<60 && (lab0_TAGDECISION_OS!=0 || lab0_OS_Charm_DEC!=0) && lab0_TAU>=0.0004 && lab0_TAU<=0.012 && lab0_MM>5130 && lab0_MM<6000 && nTracks>15 && nTracks<1000 && lab2_MM>1830 && lab2_MM<1904 && lab1_P>2000 && lab1_P<650000 && lab1_PT>400 && lab1_PT<45000 && lab0_LOKI_PHI>-10 && lab0_LOKI_PHI<10 && lab0_LOKI_ETA>1.5 && lab0_LOKI_ETA<10 && lab0_P>0 && lab0_P<3000000 && lab0_PT>0 && lab0_PT<100000 && (lab0_Hlt2Topo2BodyBBDTDecision_TOS!=0 || lab0_Hlt2Topo3BodyBBDTDecision_TOS!=0 || lab0_Hlt2Topo4BodyBBDTDecision_TOS!=0)"}

    
    return configdict
