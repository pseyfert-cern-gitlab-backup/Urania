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

    configdict["BasicVariables"]["BeautyTime"]    = { "Range"                  : [0.4,     15.0    ],
                                                      "Bins"                   : 40,
                                                      "Name"                   : "BeautyTime",
                                                      "InputName"              : "lab0_FitDaughtersPCConst_ctau_flat"}

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

    configdict["BasicVariables"]["MistagOS"]      = { "Range"                  : [ 0.0,    0.48     ],
                                                      "Name"                   : "MistagOS",
                                                      "InputName"              : "MistagOS"}

    configdict["BasicVariables"]["MistagSS"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                      "Name"                   : "MistagSS",
                                                      "InputName"              : "MistagSS"}

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
                                    "DeltaM"               : [0.5065, 0.01, 2.0],  #From HFLAV: (http://www.slac.stanford.edu/xorg/hflav/osc/summer_2017/#DMD)
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
                                                     "KnotPositions": [0.5, 1.0, 1.5, 2.0, 3.0, 12.0],
                                                     "KnotCoefficients": [1.9440e-01, 3.3275e-01, 6.1444e-01, 8.6628e-01, 9.9600e-01, 1.0745e+00]},
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
    configdict["Taggers"]["Signal"] = {"OS" : #From https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2OCTD_B2Dpi_3fb/LHCb-ANA-2016-064_v5.pdf
                                       {"Calibration":
                                        { "Type"   : "Linear",
                                          "p0"       : [0.3775],# 0.0, 1.0],
                                          "p1"       : [1.028],# 0.5, 1.5],
                                          "deltap0"  : [0.0111],# -1.0, 1.0],
                                          "deltap1"  : [0.022],# -1.0, 1.0],
                                          "avgeta"   : [0.349980],#<eta> on Bu->D0Pi
                                          "tageff"   : [0.35, 0.0, 1.0],
                                          "tagasymm" : [0.0]
                                          },
                                        "MistagPDF" :
                                        {"Type"     : "BuildTemplate"}
                                        },
                                       "SS": #From https://twiki.cern.ch/twiki/pub/LHCbPhysics/B2OCTD_B2Dpi_3fb/LHCb-ANA-2016-064_v5.pdf
                                       {"Calibration":
                                        { "Type"   : "Linear",
                                          "p0"       : [0.4424],# 0.0, 1.0],
                                          "p1"       : [0.813],# 0.5, 1.5],
                                          "deltap0"  : [0.0006],# -1.0, 1.0],
                                          "deltap1"  : [0.007],# -1.0, 1.0],
                                          "avgeta"   : [0.435], #<eta> on Bd->J/psiK*
                                          "tageff"   : [0.816, 0.0, 1.0],
                                          "tagasymm" : [0.0]
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
    # Constraint on resolution
    #configdict["gaussCons"]["resmodel00_sigma"] = 0.00038
    # Constraint on DeltaM
    configdict["gaussCons"]["deltaM"] = 0.0019
    # Constraint on Gamma (error on gamma = rel. error on lifetime * gamma)
    configdict["gaussCons"]["Gamma"] = (0.004/1.518) * (1.0/1.518)
    
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
    #configdict["LikelihoodScan"].append("Sf")
    #configdict["LikelihoodScan"].append("Sfbar")

    return configdict
