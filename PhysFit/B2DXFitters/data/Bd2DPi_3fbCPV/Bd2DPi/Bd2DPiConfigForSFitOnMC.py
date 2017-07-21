"""configuration file for decaytime fit on signal bootstrapped MC"""
def getconfig():

    import math
    from math import pi

    configdict = {}

    configdict["Decay"] = "Bd2DPi"

    ############################################
    # Define all basic variables
    ############################################

    configdict["BasicVariables"] = {}

    configdict["BasicVariables"]["BeautyTime"]    = {"Range": [0.4, 12.0],
                                                     "Bins": 40,
                                                     "Name": "BeautyTime",  # the name is not used by the MDFitterSettings/Translator etc.
                                                     "InputName": "obsTime"}
    # if one wants to cut on the dataset the easiest way is to add a preselection in addition to the range defined here (preselection added
    # by option --preselection on command line)

    configdict["BasicVariables"]["BacCharge"]     = {"Range": [-1000.0, 1000.0],
                                                     "Name": "BacCharge",
                                                     "InputName": "BacCharge"}

    configdict["BasicVariables"]["TagDecOS"]      = {"Range": [-1.0, 1.0],
                                                     "Name": "TagDecOS",
                                                     "InputName": "TagDecOS"}

    #configdict["BasicVariables"]["TagDecSS"]      = {"Range": [-1.0, 1.0],
    #                                                 "Name": "TagDecSS",
    #                                                 "InputName": "TagDecSS"}  # available via mdSet->GetTagVar(i)
    # the original specifier is available via mdSet->GetTagVarOutName(i)
    # this name + "_idx" is used in the inputtree/dataset - so no flexibility in the beginning of the name as "TagDec" is used when checking for
    # tagging variables in general at the beginning

    configdict["BasicVariables"]["MistagOS"]      = {"Range": [0.0, 0.5],  # 0.4619
                                                     "Name": "MistagOS",
                                                     "InputName": "MistagOS"}

    #configdict["BasicVariables"]["MistagSS"]      = {"Range": [0.0, 0.5],  # 0.492
    #                                                 "Name": "MistagSS",
    #                                                 "InputName": "MistagSS"}

    configdict["AdditionalVariables"] = {}
    #configdict["AdditionalVariables"]["TrueID"]   = {"Range": [0.0, 1500.0],
    #                                                 "InputName": "TrueID"}

    ############################################
    # Define all CPV and decay rate parameters
    ############################################

    # Parameters from https://svnweb.cern.ch/trac/lhcb/browser/DBASE/tags/Gen/DecFiles/v27r42/dkfiles/Bd_D-pi+,Kpipi=CPVDDalitz,DecProdCut.dec)
    ModqOverp_d     = 1
    ArgqOverp_d     = -0.746
    ModpOverq_d     = 1
    ArgpOverq_d     = 0.746
    ModAf_d         = 0.0849
    ArgAf_d         = 0.002278
    ModAbarf_d      = 0.00137
    ArgAbarf_d      = -1.128958
    ModAfbar_d      = 0.00137
    ArgAfbar_d      = 1.3145
    ModAbarfbar_d   = 0.0849
    ArgAbarfbar_d   = 0.002278

    configdict["ACP"] = {}
    configdict["ACP"]["Signal"] = {"Gamma": [1.0 / 1.520, 0.1, 2.0],
                                   "DeltaGamma": [0.0],
                                   "DeltaM": [0.510, 0.01, 5.0],
                                   "ArgLf": [ArgqOverp_d + ArgAbarf_d - ArgAf_d],
                                   "ArgLbarfbar": [ArgpOverq_d + ArgAfbar_d - ArgAbarfbar_d],
                                   "ModLf": [ModAbarf_d / ModAf_d],
                                   # "C": [0.0],  # sin2beta
                                   # "S": [0.7],  # sin2beta
                                   # "Sbar": [0.0],  # sin2beta
                                   # "C": [1.0],  # we neglect r^2 terms
                                   # "S": [-0.031],  # from decfile
                                   # "Sbar": [0.029],  # from decfile
                                   #"D": [0],  # from DeltaGamma=0
                                   #"Dbar": [0],  # from DeltaGamma=0
                                   "ParameteriseIntegral": True,
                                   "CPlimit": {"upper": 2.0, "lower": -2.0},
                                   "NBinsAcceptance": 0}  # keep at zero if using spline acceptance!

    ############################################
    # Define resolution and acceptance models
    ############################################

    configdict["ResolutionAcceptance"] = {}
    configdict["ResolutionAcceptance"]["Signal"] = {}
    configdict["ResolutionAcceptance"]["Signal"] = {"TimeErrorPDF": None,
                                                    "Acceptance":  # From ANA note v2
                                                    {"Type": "Spline",
                                                     "Float": True,
                                                     "KnotPositions": [0.5, 1.0, 1.5, 2.0, 2.3, 2.6, 3.0, 4.0, 10.0],
                                                     "KnotCoefficients": [1.9440e-01, 3.3275e-01, 6.1444e-01, 8.6628e-01, 9.9600e-01, 1.0745e+00, 1.1083e+00,  1.1565e+00, 1.1946e+00]},
                                                    "Resolution":  # From ANA note v2
                                                    {"Type": "AverageModel",
                                                     "Parameters": {'sigmas': [0.05491], 'fractions': []},
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
    configdict["ProductionAsymmetry"]["Signal"] = [-0.0124, -1.0, 1.0]  # from ANA note v2
    configdict["DetectionAsymmetry"]["Signal"] = [0.0086, -1.0, 1.0]  # from arXiv:1408.0275v2 (OPPOSITE SIGN!!!)
    # configdict["DetectionAsymmetry"]["Signal"] = [0.0, -1.5, 1.5]  # sin2beta

    ############################################
    # Define taggers and their calibration
    ############################################

    configdict["Taggers"] = {}
    configdict["Taggers"]["Signal"] = {}
    configdict["Taggers"]["Signal"] = {"OS":  # From Bu, stat and syst combined
                                       {"Calibration":
                                        {"Type": "GLM",
                                         "XML": ["/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/OS_Combination_Bu2D0Pi_MC_logitLink.xml"],
                                         "tageff": [1.0],#[0.371, 0.01, 0.99],  # float in the fit
                                         "tagasymm": [0.0]
                                         },
                                        "MistagPDF":
                                        {"Type": "BuildTemplate"}
                                        }}#,
                                       #"SS":  # From JpsiKst, stat and syst combined
                                       #{"Calibration":
                                       # {"Type": "GLM",
                                       #  "XML": ["/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/tutorial/SS_PionBDT_Calibration_Poly_LogitLink.xml"],
                                       #  "tageff": [0.77, 0.01, 0.99],  # float in the fit
                                       #  "tagasymm": [0.0]
                                       #  },
                                       # "MistagPDF":
                                       # {"Type": "BuildTemplate"}
                                       # }
                                       #}

    ############################################
    # Choose parameters to fix
    ############################################

    configdict["constParams"] = []
    configdict["constParams"].append('Cf')
    configdict["constParams"].append('Cfbar')
    #configdict["constParams"].append('Sf')
    #configdict["constParams"].append('Sfbar')
    configdict["constParams"].append('Df')
    configdict["constParams"].append('Dfbar')
    configdict["constParams"].append('.*scalefactor')

    configdict["constParams"].append('resmodel00_sigma')

    ############################################
    # Build gaussian constraints
    # See B2DXFitters/GaussianConstraintBuilder.py for documentation
    ############################################

    configdict["gaussCons"] = {}
    # Constraint on DeltaM
    configdict["gaussCons"]["deltaM"] = math.sqrt(0.0021 * 0.0021 + 0.0010 * 0.0010)  # 0.0023259
    # Constraint on Gamma (error on gamma = rel. error on lifetime * gamma)
    configdict["gaussCons"]["Gamma"] = (0.004 / 1.520) * (1.0 / 1.520)  # 0.0017313
    # Multivariate constraint for OS combination
    #ospedix='_OS_Combination_Calibration_NSpline_RLogitLink'
    #configdict["gaussCons"]["multivarOSCalib"] = [['p_0'+ospedix, 'p_1'+ospedix, 'p_2'+ospedix, 'p_3'+ospedix, 'p_4'+ospedix,
    #                                               'dp_0'+ospedix, 'dp_1'+ospedix, 'dp_2'+ospedix, 'dp_3'+ospedix, 'dp_4'+ospedix],  # parname
    #                                              [0.019695,0.021343,0.0074792,0.1171,0.79469,0.03939,0.042687,0.014958,0.2342,1.5894],  # errors
    #                                              [[1, -0.21732, -0.07802, 0.086702, 0.035155, 0.074186, -0.076022, 0.0067162, 0.032523, 0.0075709],  # correlation matrix from EPM
    #                                               [-0.21732, 1, -0.18847, -0.25706, -0.012079, -0.076022, 0.089704, -0.067287, -0.027743, 0.027762],
    #                                               [-0.07802, -0.18847, 1, -0.092168, -0.37105, 0.0067162, -0.067287, 0.10788, -0.018591, -0.061417],
    #                                               [0.086702, -0.25706, -0.092168, 1, 0.15012, 0.032523, -0.027743, -0.018591, 0.081919, 0.053567],
    #                                               [0.035155, -0.012079, -0.37105, 0.15012, 1, 0.0075709, 0.027762, -0.061417, 0.053567, 0.082966],
    #                                               [0.074186, -0.076022, 0.0067162, 0.032523, 0.0075709, 1, -0.21732, -0.07802, 0.086702, 0.035155],
    #                                               [-0.076022, 0.089704, -0.067287, -0.027743, 0.027762, -0.21732, 1, -0.18847, -0.25706, -0.012079],
    #                                               [0.0067162, -0.067287, 0.10788, -0.018591, -0.061417, -0.07802, -0.18847, 1, -0.092168, -0.3710],
    #                                               [0.032523, -0.027743, -0.018591, 0.081919, 0.053567, 0.086702, -0.25706, -0.092168, 1, 0.15012],
    #                                               [0.0075709, 0.027762, -0.061417, 0.053567, 0.082966, 0.035155, -0.012079, -0.3710, 0.15012, 1]]]
    # Multivariate constraint for SS combination
    #sspedix='_SS_PionBDT_Calibration_Poly_LogitLink'
    #configdict["gaussCons"]["multivarSSCalib"] = [['p_0'+sspedix, 'p_1'+sspedix, 'dp_0'+sspedix, 'dp_1'+sspedix],  # parname
    #                                              [0.0018216, 0.0062959, 0.0036432, 0.012592],  # errors
    #                                              [[1,       -0.037697,       -0.016192,      0.00080237],  # correlation matrix from EPM
    #                                               [-0.037697,        1,      0.00080237,       -0.011958],
    #                                               [-0.016192,        0.00080237,      1,       -0.037697],
    #                                               [0.00080237,       -0.011958,  -0.037697,    1]]]

    ############################################
    # Choose parameters to perform the
    # likelihood scan for
    ############################################

    #configdict["LikelihoodScan"] = []
    #configdict["LikelihoodScan"].append("Sf")
    #configdict["LikelihoodScan"].append("Sfbar")

    ############################################
    # Choose initial free parameters to randomise
    ############################################

    #configdict["randomiseParams"] = {}
    #configdict["randomiseParams"] = {'Sf': {'min': -0.04, 'max': -0.02},
    #                                 'Sfbar': {'min': 0.02, 'max': 0.04}
    #                                 }

    return configdict
