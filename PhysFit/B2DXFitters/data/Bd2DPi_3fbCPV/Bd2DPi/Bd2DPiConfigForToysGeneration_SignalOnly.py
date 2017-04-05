"""configuration file for toy generation for signal only toys"""
def getconfig():

    configdict = {}

    ############################################################
    # List of observables for all the PDFs.
    # The content of this dictionary determines the observables
    # to generate for and how may taggers are present.
    ############################################################

    configdict["Observables"] = {}
    configdict["Observables"] = {"BeautyMass": {"Type": "RooRealVar",
                                                "Title": "B mass (MeV/c^2)",
                                                "Range": [5090, 6000]},
                                 "BeautyTime": {"Type": "RooRealVar",
                                                "Title": "B decay time (ps)",
                                                "Range": [0.4, 15.0]},
                                 "BacCharge": {"Type": "RooCategory",
                                               "Title": "Bachelor charge",
                                               "Categories": {"h+": +1}},
                                 "BacCharge": {"Type": "RooCategory",
                                               "Title": "Bachelor charge",
                                               "Categories": {"h+": +1,
                                                              "h-": -1}},
                                 "MistagOS": {"Type": "RooRealVar",
                                              "Title": "#eta_{OS}",
                                              "Range": [0.0, 0.5]},
                                 "MistagSS": {"Type": "RooRealVar",
                                              "Title": "#eta_{SS}",
                                              "Range": [0.0, 0.5]},
                                 "TrueID": {"Type": "RooRealVar",
                                            "Title": "True component ID",
                                            "Range": [0.0, 1500.0]},
                                 "TagDecOS": {"Type": "RooCategory",
                                              "Title": "q_{t}^{OS}",
                                              "Categories": {"B": +1,
                                                             "Untagged": 0,
                                                             "Bbar": -1}},
                                 "TagDecSS": {"Type": "RooCategory",
                                              "Title": "q_{t}^{SS}",
                                              "Categories": {"B": +1,
                                                             "Untagged": 0,
                                                             "Bbar": -1}}
                                 }

    ############################################################
    # List of mass hypotheses for bachelor
    # The content of this dictionary determines how many
    # bachelor PID bins the final dataset is splitted into
    ############################################################

    configdict["Hypothesys"] = ["Bd2DPi"]

    ############################################################
    # Signal decay and Charm decay mode
    ############################################################

    configdict["Decay"] = "Bd2DPi"
    configdict["CharmModes"] = ["KPiPi"]
    configdict["Years"] = ["2011", "2012"]
    configdict["MergedYears"] = True

    ############################################################
    # Luminosity for splitting yields and other parameters
    ############################################################

    configdict["IntegratedLuminosity"] = {"2011": {"Down": 0.50, "Up": 0.50}, "2012": {"Down": 1.000, "Up": 1.000}}
    lum2011 = configdict["IntegratedLuminosity"]["2011"]["Up"] + configdict["IntegratedLuminosity"]["2011"]["Down"]
    lum2012 = configdict["IntegratedLuminosity"]["2012"]["Up"] + configdict["IntegratedLuminosity"]["2012"]["Down"]
    fracRun1 = lum2011 / (lum2011 + lum2012)
    DRho_to_DKst_KHypo = 8.5000e-01
    eff_Bd2DK_DK = 6.29009e-01
    eff_Bd2DPi_DPi = 9.78927e-01

    ############################################################
    # List of components with yields to generate.
    # The content of this dictionary determines, for each
    # PID bin, how many PDF components are generated.
    # If there is only signal, a TTree ready for sFit is
    # generated directly, without need for doing a (useless)
    # mass fit.
    ############################################################

    # number of events for Bd2Dpi: 5.2848e+05
    # number of events for Bd2JpsieeKS: 10628

    configdict["Components"] = {}
    configdict["Components"] = {"Signal": {"Bd2DPi": {"2011": {"KPiPi": [5.2848e+05 * fracRun1]},
                                                      "2012": {"KPiPi": [5.2848e+05 * (1 - fracRun1)]}}}
                                }

    ############################################################
    # "Code" to identify the True ID for each component
    ############################################################

    configdict["TrueID"] = {}
    configdict["TrueID"] = {"Signal": 100}

    ############################################################
    # List of PDFs for "time-independent" observables
    # Dictionary structure: observable->component->bachelor hypo->year->D mode
    ############################################################

    Pipeak = 5.27849e+03

    configdict["PDFList"] = {}
    configdict["PDFList"]["BeautyMass"] = {}

    # Signal
    configdict["PDFList"]["BeautyMass"]["Signal"] = {}
    configdict["PDFList"]["BeautyMass"]["Signal"]["Bd2DPi"] = {}
    configdict["PDFList"]["BeautyMass"]["Signal"]["Bd2DPi"]["2011"] = {}
    configdict["PDFList"]["BeautyMass"]["Signal"]["Bd2DPi"]["2011"]["KPiPi"] = {"Type": "Ipatia",
                                                                                "mean": [Pipeak],
                                                                                "sigma": [1.96756e+01],
                                                                                "zeta": [0.0],
                                                                                "fb": [0.0],
                                                                                "l": [-3.14504e+00],
                                                                                "a1": [1.56363e+00],  # left
                                                                                "a2": [1.77887e+00],  # right
                                                                                "n1": [4.04491e+00],  # left
                                                                                "n2": [6.62043e+00]}  # right
    configdict["PDFList"]["BeautyMass"]["Signal"]["Bd2DPi"]["2012"] = configdict["PDFList"]["BeautyMass"]["Signal"]["Bd2DPi"]["2011"]

    ############################################################
    # Tagging calibration and mistag PDF. If "MistagPDF" : None,
    # then a average mistag is used
    ############################################################

    configdict["Taggers"] = {}
    for comp in configdict["Components"].iterkeys():
        configdict["Taggers"][comp] = {}
        configdict["Taggers"][comp] = {"OS":
                                       {"Calibration":
                                        {"p0": [0.3737056],
                                         "p1": [1.028621],
                                         "deltap0": [0.11819],  # 0.011819
                                         "deltap1": [0.143134],  # 0.043134
                                         "avgeta": [0.347742],
                                         "tageff": [0.371],
                                         "tagasymm": [0.0]
                                         },
                                        "MistagPDF":
                                        {"Type": "FromWorkspace",  # options: Gauss, FromWorkspace
                                         "File": "/fhgfs/users/abirnkraut/MistagTemplates/MistagTemplates_Dpi_OSuncut.root",
                                         "Workspace": "workspace",
                                         "Name": "sigMistagPdf_2"
                                         # "mean": [0.32, 0.25, 0.5],
                                         # "sigma": [0.04, 0.0, 0.2]
                                         }
                                        },
                                       "SS":
                                       {"Calibration":
                                        {"p0": [0.4424049],
                                         "p1": [0.81302],
                                         "deltap0": [0.162332],  # 00062332
                                         "deltap1": [-0.1066248],  # 0.0066248
                                         "avgeta": [0.435],
                                         "tageff": [0.816],
                                         "tagasymm": [0.0]
                                         },
                                        "MistagPDF":
                                        {"Type": "FromWorkspace",  # options: Gauss, FromWorkspace
                                         "File": "/fhgfs/users/abirnkraut/MistagTemplates/MistagTemplates_Dpi.root",
                                         "Workspace": "workspace",
                                         "Name": "sigMistagPdf_1"
                                         # "mean": [0.47, 0.25, 0.5],
                                         # "sigma": [0.02, 0.0, 0.2]
                                         }
                                        }
                                       }

    ############################################################
    # Time resolution and acceptance (there is a single dict because
    # they are strongly connected in the way they are built).
    # If "TimeErrorPDF" : None, then an average resolution model
    # is used.
    ############################################################

    configdict["ResolutionAcceptance"] = {}
    for comp in configdict["Components"].iterkeys():
        configdict["ResolutionAcceptance"][comp] = {}
        configdict["ResolutionAcceptance"][comp] = {"TimeErrorPDF": None,
                                                    "Acceptance":  # From ANA note v2
                                                    {"Type": "Spline",
                                                     "KnotPositions": [0.5, 1.0, 1.5, 2.0, 3.0, 12.0],
                                                     "KnotCoefficients": [0.3889, 0.5754, 0.8515, 1.0649, 1.2373, 1.4149]},
                                                    "Resolution":  # From ANA note v2
                                                    {"Type": "AverageModel",
                                                     "Parameters": {'sigmas': [0.05491], 'fractions': []},
                                                     "Bias": [0.0],
                                                     "ScaleFactor": [1.0]}
                                                    }

    ############################################################
    # Production and detection asymmetries
    ############################################################

    configdict["ProductionAsymmetry"] = {}
    configdict["DetectionAsymmetry"] = {}
    configdict["ProductionAsymmetry"]["Signal"] = {}
    configdict["DetectionAsymmetry"]["Signal"] = {}
    configdict["ProductionAsymmetry"]["Signal"] = [-0.0124]  # from ANA note v2
    configdict["DetectionAsymmetry"]["Signal"] = [0.0086]  # from arXiv:1408.0275v2 (OPPOSITE SIGN!!!)
    # configdict["DetectionAsymmetry"]["Signal"] = [0.0]  # sin2beta with only one bacCharge category

    ############################################################
    # Time PDF parameters
    ############################################################

    configdict["ACP"] = {}

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

    # Signal (use more convenient interface with ArgLf_d, ArgLbarfbar_d and ModLf_d)
    configdict["ACP"]["Signal"] = {"Gamma": [1.0 / 1.520],  # Inverse lifetime from HFAG (http://www.slac.stanford.edu/xorg/hfag/osc/summer_2016/)
                                   "DeltaGamma": [0.0],
                                   "DeltaM": [0.5050],  # semileptonic measurement HFAG (http://www.slac.stanford.edu/xorg/hfag/osc/summer_2016/)
                                   "ArgLf": [ArgqOverp_d + ArgAbarf_d - ArgAf_d],
                                   "ArgLbarfbar": [ArgpOverq_d + ArgAfbar_d - ArgAbarfbar_d],  # ArgpOverq_d = -ArgqOverp_d
                                   "ModLf": [ModAbarf_d / ModAf_d],
                                   # "C": [0.0],  # sin2beta
                                   # "S": [0.7],  # sin2beta
                                   # "Sbar": [0.0],  # sin2beta
                                   # "C": [1.0], #we neglect r^2 terms
                                   # "S": [-0.031], #from decfile
                                   # "Sbar": [0.029], #from decfile
                                   "D": [0],  # from DeltaGamma=0
                                   "Dbar": [0],  # from DeltaGamma=0
                                   "ParameteriseIntegral": True,
                                   "NBinsAcceptance": 0}  # keep at zero if using spline acceptance!

    for comp in configdict["Components"].iterkeys():
        if comp != "Signal":
            # Use other interface with C, S, Sbar, D, Dbar
            # We build trivial PDFs since we don't care about background shapes in time if we use sWeights
            configdict["ACP"][comp] = {"Gamma": [1.0],
                                       "DeltaGamma": [0.0],
                                       "DeltaM": [0.0],
                                       "C": [0.0],
                                       "S": [0.0],
                                       "Sbar": [0.0],
                                       "D": [0.0],
                                       "Dbar": [0.0],
                                       "ParameteriseIntegral": True,
                                       "NBinsAcceptance": 0}

    return configdict
