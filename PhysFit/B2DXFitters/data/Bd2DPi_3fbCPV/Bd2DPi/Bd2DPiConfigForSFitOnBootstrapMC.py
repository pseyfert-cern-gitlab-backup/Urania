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

    #configdict["BasicVariables"]["TagDecTrue"]      = {"Range": [-1.0, 1.0],
    #                                                   "Name": "TagDecOS",
    #                                                   "InputName": "TagDecTrue"}

    configdict["BasicVariables"]["TagDecOS"]      = {"Range": [-1.0, 1.0],
                                                     "Name": "TagDecOS",
                                                     "InputName": "TagDecOS"}

    #configdict["BasicVariables"]["TagDecCheat"]      = {"Range": [-1.0, 1.0],
    #                                                    "Name": "TagDecCheat",
    #                                                    "InputName": "TagDecCheat"}

    #configdict["BasicVariables"]["TagDecSS"]      = {"Range": [-1.0, 1.0],
    #                                                 "Name": "TagDecSS",
    #                                                 "InputName": "TagDecSS"}  # available via mdSet->GetTagVar(i)
    # the original specifier is available via mdSet->GetTagVarOutName(i)
    # this name + "_idx" is used in the inputtree/dataset - so no flexibility in the beginning of the name as "TagDec" is used when checking for
    # tagging variables in general at the beginning

    configdict["BasicVariables"]["MistagOS"]      = {"Range": [0.0, 0.5],  # 0.4619
                                                     "Name": "MistagOS",
                                                     "InputName": "MistagOS"}

    #configdict["BasicVariables"]["MistagCheat"]      = {"Range": [0.0, 0.5],
    #                                                    "Name": "MistagCheat",
    #                                                    "InputName": "MistagCheat"}

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
    configdict["ACP"]["Signal"] = {"Gamma": [1.0 / 1.519068, 0.1, 2.0],
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
                                                    "Acceptance": # From ANA note v2
                                                    {"Type": "Spline",
                                                     "Float": True,
                                                     "Extrapolate": True,
                                                     #"ToFix": [3],
                                                     #"KnotPositions" : [0.45, 1.0, 2.0, 2.5, 7.0, 12.0],
                                                     #"KnotCoefficients": [0.5, 0.7, 1.0, 0.9, 0.85, 0.7, 0.7]},
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

    ############################################
    # Define taggers and their calibration
    ############################################

    configdict["Taggers"] = {}
    configdict["Taggers"]["Signal"] = {}
    configdict["Taggers"]["Signal"] = {"OS":  # From Bu MC, stat and syst combined
                                       {"Calibration":
                                        {"Type": "GLM",
                                         #"XML": ["/afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bd2DPi_rlogitLink_NoProdAsymm_useBubasis_broadTrigBDTAUWeight/OS_Combination_Calibration.xml"],
                                         "XML": ["/afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bu2D0Pi_rlogitLink_NoProdAsymm_broadTrigBDTAUWeight/OS_Combination_Calibration.xml"],
                                         "tageff": [1.0],#[0.371, 0.01, 0.99],  # float in the fit
                                         "tagasymm": [0.0]
                                         },
                                        "MistagPDF":
                                        {"Type": "BuildTemplate"}
                                        }}#,
    #configdict["Taggers"]["Signal"] = {"OS":  #Cheated tagger
    #                                   {"Calibration":
    #                                    {"Type"     : "Linear",
    #                                     "p0"       : [0.370029],
    #                                     "p1"       : [1.0],
    #                                     "deltap0"  : [0.0],
    #                                     "deltap1"  : [0.0],
    #                                     "avgeta"   : [0.370029],
    #                                     "tageff"   : [1.0],
    #                                     "tagasymm" : [0.0]
    #                                     },
    #                                    "MistagPDF":
    #                                    {"Type": "BuildTemplate"}
    #                                    }
    #                                   }
    #configdict["Taggers"]["Signal"] = {"SS":  # From JpsiKst MC (EPM basis)
    #                                   {"Calibration":
    #                                    {"Type"     : "Linear",
    #                                     "p0"       : [0.00032999],
    #                                     "p1"       : [0.011431],
    #                                     "deltap0"  : [0.0023665],
    #                                     "deltap1"  : [-0.021455],
    #                                     "avgeta"   : [0.4386],
    #                                     "tageff"   : [1.0],
    #                                     "tagasymm" : [0.0]
    #                                     },
    #                                    "MistagPDF":
    #                                    {"Type": "BuildTemplate"}
    #                                    }
    #                                   }
                                       

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
    configdict["gaussCons"]["Gamma"] = (0.004 / 1.519068) * (1.0 / 1.519068)  # 0.0017313
    # Multivariate constraint for OS combination
    ospedix='_OS_Combination_Calibration'
    #From /afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bu2D0Pi_rlogitLink_NoProdAsymm_broadTrigBDTAUWeight/
    configdict["gaussCons"]["multivarOSCalib"] = [['p_0'+ospedix, 'p_1'+ospedix, 'p_2'+ospedix, 'p_3'+ospedix, 'p_4'+ospedix,
                                                   'dp_0'+ospedix, 'dp_1'+ospedix, 'dp_2'+ospedix, 'dp_3'+ospedix, 'dp_4'+ospedix],  # parname
                                                  [0.012765, 0.014155, 0.0049352, 0.063306, 0.34322, 0.025531, 0.02831, 0.0098703, 0.12661, 0.68643],  # errors
                                                  [ [1,       0.0093893,        -0.16252,       -0.018463,        0.023935,        0.015107,       -0.041721,        0.031072,
                                                     0.03324,        0.005107],  # correlation matrix from EPM (upper-right triangle)
                                                    [1,        0.072851,        -0.30607,        -0.20523,       -0.041721,         0.07414,       -0.028533,      -0.022481,  0.0063663],
                                                    [1,         0.14817,        -0.20439,        0.031072,       -0.028533,        0.081493,        0.028518,      -0.0044623],
                                                    [1,         0.52983,         0.03324,       -0.022481,        0.028518,         0.17986,       -0.042929],
                                                    [1,        0.005107,       0.0063663,      -0.0044623,       -0.042929,         0.34316],
                                                    [1,       0.0093893,        -0.16252,       -0.018463,        0.023935],
                                                    [1,        0.072851,        -0.30607,        -0.20523],
                                                    [1,         0.14817,        -0.20439],
                                                    [1,         0.52983],
                                                    [1] ] ]
    # Multivariate constraint for SS combination
    #sspedix='_SS_PionBDT_Calibration_Poly_LogitLink'
    #configdict["gaussCons"]["multivarSSCalib"] = [['p_0'+sspedix, 'p_1'+sspedix, 'dp_0'+sspedix, 'dp_1'+sspedix],  # parname
    #                                              [0.0018216, 0.0062959, 0.0036432, 0.012592],  # errors
    #                                              [[1,       -0.037697,       -0.016192,      0.00080237],  # correlation matrix from EPM
    #                                               [-0.037697,        1,      0.00080237,       -0.011958],
    #                                               [-0.016192,        0.00080237,      1,       -0.037697],
    #                                               [0.00080237,       -0.011958,  -0.037697,    1]]]

    ############################################
    # Resample fixed parameters
    ############################################

    #configdict["resampleParams"] = {}
    #ospedix='_OS_Combination_Calibration'
    #From /afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bu2D0Pi_rlogitLink_NoProdAsymm_broadTrigBDTAUWeight/
    #configdict["resampleParams"]["multivarOSCalib"] = [['p_0'+ospedix, 'p_1'+ospedix, 'p_2'+ospedix, 'p_3'+ospedix, 'p_4'+ospedix,
    #                                                    'dp_0'+ospedix, 'dp_1'+ospedix, 'dp_2'+ospedix, 'dp_3'+ospedix, 'dp_4'+ospedix],  # parname
    #                                                   [0.012765, 0.014155, 0.0049352, 0.063306, 0.34322, 0.025531, 0.02831, 0.0098703, 0.12661, 0.68643],  # errors
     #                                                  [ [1,       0.0093893,        -0.16252,       -0.018463,        0.023935,        0.015107,       -0.041721,        0.031072,         0.03324,        0.005107],  # correlation matrix from EPM (upper-right triangle)
      #                                                   [1,        0.072851,        -0.30607,        -0.20523,       -0.041721,         0.07414,       -0.028533,       -0.022481,       0.0063663],
       #                                                  [1,         0.14817,        -0.20439,        0.031072,       -0.028533,        0.081493,        0.028518,      -0.0044623],
        #                                                 [1,         0.52983,         0.03324,       -0.022481,        0.028518,         0.17986,       -0.042929],
         #                                                [1,        0.005107,       0.0063663,      -0.0044623,       -0.042929,         0.34316],
          #                                               [1,       0.0093893,        -0.16252,       -0.018463,        0.023935],
           #                                              [1,        0.072851,        -0.30607,        -0.20523],
            #                                             [1,         0.14817,        -0.20439],
             #                                            [1,         0.52983],
              #                                           [1] ] ]
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

    ############################################
    # Change FT basis from "EPM" to "standard"
    ############################################
    #configdict["changeFTbasis"] = {}
    #configdict["changeFTbasis"] = {"p0_OS"       : configdict["Taggers"]["Signal"]["OS"]["Calibration"]["avgeta"], #p0 = p0EPM + <eta>
    #                               "p1_OS"       : [1.0] } #p1 = p1EPM + 1 
    #configdict["changeFTbasis"] = {"p0_SS"       : configdict["Taggers"]["Signal"]["SS"]["Calibration"]["avgeta"], #p0 = p0EPM + <eta>
    #                               "p1_SS"       : [1.0] } #p1 = p1EPM + 1 

    return configdict
