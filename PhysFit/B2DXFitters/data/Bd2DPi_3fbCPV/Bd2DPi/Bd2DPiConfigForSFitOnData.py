def getconfig() :

    import math
    from math import pi

    configdict = {}

    configdict["Decay"] = "Bd2DPi"

    ############################################
    # Define all basic variables
    ############################################

    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5090,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_FitDaughtersConst_M_flat"}

    configdict["BasicVariables"]["CharmMass"]     = { "Range"                  : [1830,    1904    ],
                                                      "Name"                   : "CharmMass",
                                                      "InputName"              : "obsMassDminus"}

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

    configdict["BasicVariables"]["BacPIDK"]       = { "Range"                  : [-999.0, 999.0     ],
                                                      "Name"                   : "BacPIDK",
                                                      "InputName"              : "lab1_PIDK"}

    configdict["BasicVariables"]["nTracks"]       = { "Range"                  : [15.0,    1000.0  ],
                                                      "Name"                   : "nTracks",
                                                      "InputName"              : "nTracks"}

    configdict["BasicVariables"]["BacCharge"]     = { "Range"                  : [-1000.0, 1000.0  ],
                                                      "Name"                   : "BacCharge",
                                                      "InputName"              : "lab1_ID"}
    
    configdict["BasicVariables"]["TagDecOS"]      = { "Range"                  : [-1.0,    1.0     ],
                                                      "Name"                   : "TagDecOS",
                                                      "InputName"              : "TagDecOS"}
    
    configdict["BasicVariables"]["TagDecSS"]      = { "Range"                  : [-1.0,    1.0     ],
                                                      "Name"                   : "TagDecSS",
                                                      "InputName"              : "TagDecSS"}

    configdict["BasicVariables"]["MistagOS"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                      "Name"                   : "MistagOS",
                                                      "InputName"              : "MistagOS"}

    configdict["BasicVariables"]["MistagSS"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                      "Name"                   : "MistagSS",
                                                      "InputName"              : "MistagSS"}
    '''
    configdict["BasicVariables"]["TagDecOSExclusive"]      = { "Range"                  : [-1.0,    1.0     ],
                                                               "Name"                   : "TagDecOSExclusive",
                                                               "InputName"              : "TagDecOSExclusive"}
    
    configdict["BasicVariables"]["TagDecSSExclusive"]      = { "Range"                  : [-1.0,    1.0     ],
                                                               "Name"                   : "TagDecSSExclusive",
                                                               "InputName"              : "TagDecSSExclusive"}
    
    configdict["BasicVariables"]["MistagOSExclusive"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                               "Name"                   : "MistagOSExclusive",
                                                               "InputName"              : "MistagOSExclusive"}
    
    configdict["BasicVariables"]["MistagSSExclusive"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                               "Name"                   : "MistagSSExclusive",
                                                               "InputName"              : "MistagSSExclusive"}
    '''
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


    ############################################
    # Define all CPV and decay rate parameters
    ############################################

    #Parameters from https://svnweb.cern.ch/trac/lhcb/browser/DBASE/tags/Gen/DecFiles/v27r42/dkfiles/Bd_D-pi+,Kpipi=CPVDDalitz,DecProdCut.dec)
    ModqOverp_d     =  1
    ArgqOverp_d     =  -0.746
    ModpOverq_d     =  1
    ArgpOverq_d     =  0.746
    ModAf_d         =  0.0849
    ArgAf_d         =  0.002278
    ModAbarf_d      =  0.00137
    ArgAbarf_d      =  -1.128958
    ModAfbar_d      =  0.00137
    ArgAfbar_d      =  1.3145
    ModAbarfbar_d   =  0.0849
    ArgAbarfbar_d   =  0.002278

    configdict["ACP"] = {}
    configdict["ACP"]["Signal"] = { "Gamma"                : [1.0 / 1.518, 0.1, 2.0], #From HFLAV (http://www.slac.stanford.edu/xorg/hflav/osc/summer_2017/#TAU)
                                    "DeltaGamma"           : [0.0], # nominal
                                    #"DeltaGamma"           : [0.007], #for systematics. HFLAV: DG/G=-0.002+/-0.010 -> DG=-0.001+/-0.007
                                    "DeltaM"               : [0.505, 0.01, 2.0],  #From HFLAV (LHCb semileptonic): (http://www.slac.stanford.edu/xorg/hflav/osc/summer_2017/#DMD)
                                    #"ArgLf"                : [ArgqOverp_d + ArgAbarf_d - ArgAf_d],
                                    #"ArgLbarfbar"          : [ArgpOverq_d + ArgAfbar_d - ArgAbarfbar_d],
                                    #"ModLf"                : [ModAbarf_d/ModAf_d],
                                    "S"                   : [-0.031],
                                    "Sbar"                : [0.029],
                                    "C"                   : [1.0], #nominal (r->0)
                                    #"C"                   : [0.999402], #for systematics (r avg of BaBar, Belle = 0.0173)
                                    "D"                   : [0.0], #nominal (DG=0)
                                    "Dbar"                : [0.0], #nominal (DG=0)
                                    #"D"                   : [-0.00973321], #for systematics (DG != 0)
                                    #"Dbar"                : [-0.0151113], #for systematics (DG != 0)
                                    "ParameteriseIntegral" : True,
                                    "CPlimit"              : {"upper":1.0, "lower":-1.0},
                                    "NBinsAcceptance"      : 0} #keep at zero if using spline acceptance!

    ############################################
    # Define resolution and acceptance models
    ############################################

    configdict["ResolutionAcceptance"] = {}
    configdict["ResolutionAcceptance"]["Signal"] = {}
    configdict["ResolutionAcceptance"]["Signal"] = {"TimeErrorPDF": None,
                                                    "Acceptance":
                                                    {"Type": "Spline",
                                                     "Float": True,
                                                     "Extrapolate": True,
                                                     "KnotPositions": [0.5, 1.0, 1.5, 2.0, 2.3, 2.6, 3.0, 4.0, 10.0],
                                                     "KnotCoefficients": [1.9440e-01, 3.3275e-01, 6.1444e-01, 8.6628e-01, 9.9600e-01, 1.0745e+00, 1.1083e+00,1.1565e+00, 1.1946e+00]},
                                                    #"KnotCoefficients": [0.319338, 0.494221, 0.793542, 0.994526, 1.09258, 1.11702, 1.14026, 1.17504, 1.1541]}, #from full fit
                                                    "Resolution":
                                                    {"Type": "AverageModel",
                                                     "Parameters": { 'sigmas': [ 0.05491 ], 'fractions': [] }, #0.05491 +- 0.00038
                                                     "Bias": [0.0],
                                                     "ScaleFactor": [1.0]}
                                                    }

    ############################################
    # Define asymmetries
    ############################################

    configdict["ProductionAsymmetry"] = {}
    configdict["DetectionAsymmetry"] = {}
    configdict["ProductionAsymmetry"]["Signal"] = {}
    configdict["DetectionAsymmetry"]["Signal"] = {}
    configdict["ProductionAsymmetry"]["Signal"] = [-0.0124, -3.0, 3.0]
    configdict["DetectionAsymmetry"]["Signal"] = [0.0086, -3.0, 3.0]

    ############################################
    # Define taggers and their calibration
    ############################################

    configdict["Taggers"] = {}
    configdict["Taggers"]["Signal"] = {}
    configdict["Taggers"]["Signal"] = {"OS" :
                                       {"Calibration":  #from EPM on Bu->D0Pi data
                                        { "Type"    : "GLM",
                                          "XML"     : ["/eos/lhcb/wg/b2oc/TD_DPi_3fb/calibrations/RLogisticCalibration_Bu2D0Pi_OS_20171021.xml"],
                                          "tageff"  : [1.0],#[0.43, 0.0, 1.0],
                                          "tagasymm": [0.0]
                                          },
                                        "MistagPDF" :
                                        {"Type"     : "BuildTemplate"}
                                        },
                                       "SS": #from EPM on Bd->J/psiK* data
                                       {"Calibration":
                                        { "Type"   : "GLM",
                                          #"XML"    : ["/eos/lhcb/wg/b2oc/TD_DPi_3fb/calibrations/LinearCalibration_Bd2JpsiKst_SS_20171021.xml"],
                                          "XML"    : ["/eos/lhcb/wg/b2oc/TD_DPi_3fb/calibrations/RLogisticCalibration_Bd2JpsiKst_SS_20171101.xml"],
                                          "tageff"  : [1.0],#[0.93, 0.0, 1.0],
                                          "tagasymm": [0.0]
                                          },
                                        "MistagPDF" :
                                        {"Type"     : "BuildTemplate"}
                                        }
                                       }

    ############################################
    # Choose parameters to fix
    ############################################

    configdict["constParams"] = []
    configdict["constParams"].append('Cf')
    configdict["constParams"].append('Cfbar')
    configdict["constParams"].append('Df')
    configdict["constParams"].append('Dfbar')
    configdict["constParams"].append('.*scalefactor')
    configdict["constParams"].append('resmodel00_sigma')

    #configdict["constParams"].append('Sf')
    #configdict["constParams"].append('Sfbar')

    ############################################
    # Build gaussian constraints
    # See B2DXFitters/GaussianConstraintBuilder.py for documentation
    ############################################
    
    configdict["gaussCons"] = {}
    # Constraint on DeltaM
    configdict["gaussCons"]["deltaM"] = math.sqrt( 0.0021*0.0021 + 0.001*0.001 )
    # Constraint on Gamma (error on gamma = rel. error on lifetime * gamma)
    configdict["gaussCons"]["Gamma"] = (0.004/1.518) * (1.0/1.518)
    # Multivariate constraint for OS combination
    # from /eos/lhcb/wg/b2oc/TD_DPi_3fb/calibrations/RLogisticCalibration_Bu2D0Pi_OS_20171021.xml
    ospedix='_RLogisticCalibration_Bu2D0Pi_OS_20171021'
    configdict["gaussCons"]["multivarOSCalib"] = [['p_0'+ospedix, 'p_1'+ospedix, 'p_2'+ospedix, 'p_3'+ospedix, 'p_4'+ospedix,
                                                   'dp_0'+ospedix, 'dp_1'+ospedix, 'dp_2'+ospedix, 'dp_3'+ospedix, 'dp_4'+ospedix], #parname
                                                  [0.018861, 0.022383, 0.0083157, 0.10294, 0.46094, 0.037722, 0.044767, 0.016631, 0.20589, 0.92188], #errors
                                                  [[1,        -0.11138,       -0.060731,       0.0093798,        0.015918,        0.048798,       -0.047036,        0.039879,       -0.029968,        -0.04636],
                                                  [1,       -0.089066,        -0.18677,       -0.090617,       -0.047036,         0.10886,         -0.1467,        0.084428,         0.13518],
                                                  [1,        0.072716,        -0.26512,        0.039879,         -0.1467,          0.2937,        -0.14008,        -0.22835],
                                                  [1,         0.82552,       -0.029968,        0.084428,        -0.14008,         0.17805,         0.14321],
                                                  [1,        -0.04636,         0.13518,        -0.22835,         0.14321,         0.34926],
                                                  [1,        -0.11138,       -0.060731,       0.0093798,        0.015918],
                                                  [1,       -0.089066,        -0.18677,       -0.090617],
                                                  [1,        0.072716,        -0.26512],
                                                  [1,         0.82552],
                                                  [1]]]
    # Multivariate constraint for SS combination
    # from /eos/lhcb/wg/b2oc/TD_DPi_3fb/calibrations/LinearCalibration_Bd2JpsiKst_SS_20171021.xml
    #sspedix = '_LinearCalibration_Bd2JpsiKst_SS_20171021'
    #configdict["gaussCons"]["multivarSSCalib"] = [['p_0'+sspedix, 'p_1'+sspedix, 'dp_0'+sspedix, 'dp_1'+sspedix], #parname
    #                                              [0.0031913, 0.053317, 0.0044657, 0.077375], #errors
    #                                              [[1,      -0.0068779,       -0.005469,        0.011888],
    #                                              [1,        0.012911,       -0.069687],
    #                                              [1,       -0.031925],
    #                                              [1]]]
    #sspedix = '_RLogisticCalibration_Bd2JpsiKst_SS_20171101'
    #configdict["gaussCons"]["multivarSSCalib"] = [['p_0'+sspedix, 'p_1'+sspedix, 'dp_0'+sspedix, 'dp_1'+sspedix], #parname
    #                                              [0.059185, 0.065243, 0.084341, 0.093665], #errors
    #                                              [[1,        0.062456,       -0.028549,       -0.038885],
    #                                               [1,       -0.039147,       -0.044807],
    #                                               [1,         0.10574],
    #                                               [1]]]
    
    ############################################
    # Choose parameters to blind
    ############################################

    configdict["blindParams"] = []
    configdict["blindParams"].append('Sf')
    configdict["blindParams"].append('Sfbar')

    ############################################
    # Choose parameters to perform the
    # likelihood scan for
    ############################################

    configdict["LikelihoodScan"] = []
    configdict["LikelihoodScan"].append("Sf")
    configdict["LikelihoodScan"].append("DetAsymm")

    return configdict
