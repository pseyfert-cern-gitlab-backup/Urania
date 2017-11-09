def getconfig() :

    configdict = {}

    ############################################################
    #List of observables for all the PDFs.
    #The content of this dictionary determines the observables
    #to generate for and how may taggers are present.
    ############################################################

    configdict["Observables"] = {}
    configdict["Observables"] = {"BeautyTime":    {"Type" : "RooRealVar",
                                                   "Title" : "B decay time (ps)",
                                                   "Range" : [0.4, 12.0]},
                                 "BacCharge":     {"Type"  : "RooCategory",
                                                   "Title" : "Bachelor charge",
                                                   "Categories": { "h+" : +1,
                                                                   "h-" : -1}},
                                 "MistagOS":      {"Type" : "RooRealVar",
                                                   "Title" : "#eta_{OS}",
                                                   "Range" : [0.0, 0.5]},
                                 "MistagSS":      {"Type" : "RooRealVar",
                                                   "Title" : "#eta_{SS}",
                                                   "Range" : [0.0,0.5]},
                                 "TagDecOS":      {"Type"  : "RooCategory",
                                                   "Title" : "q_{t}^{OS}",
                                                   "Categories": { "B+"       : +1,
                                                                   "Untagged" : 0,
                                                                   "B-"       : -1}},
                                 "TagDecSS":      {"Type"  : "RooCategory",
                                                   "Title" : "q_{t}^{SS}",
                                                   "Categories": { "B+"       : +1,
                                                                   "Untagged" : 0,
                                                                   "B-"       : -1}}
                                 }

    ############################################################
    #List of mass hypotheses for bachelor
    #The content of this dictionary determines how many
    #bachelor PID bins the final dataset is splitted into
    ############################################################

    configdict["Hypothesys"] = ["Bd2DPi"]

    ############################################################
    #Signal decay and Charm decay mode
    ############################################################

    configdict["Decay"] = "Bd2DPi"
    configdict["CharmModes"] = ["KPiPi"]
    configdict["Years"] = ["2011","2012"]
    configdict["MergedYears"] = True

    ############################################################
    #Luminosity for splitting yields and other parameters
    ############################################################

    configdict["IntegratedLuminosity"] = {"2011": {"Down":  0.50, "Up": 0.50}, "2012":{"Down": 1.000, "Up": 1.000}}
    lum2011 =  configdict["IntegratedLuminosity"]["2011"]["Up"] + configdict["IntegratedLuminosity"]["2011"]["Down"]
    lum2012 =  configdict["IntegratedLuminosity"]["2012"]["Up"] + configdict["IntegratedLuminosity"]["2012"]["Down"]
    fracRun1 = lum2011/(lum2011 + lum2012)

    ############################################################
    #List of components with yields to generate.
    #The content of this dictionary determines, for each
    #PID bin, how many PDF components are generated.
    #If there is only signal, a TTree ready for sFit is
    #generated directly, without need for doing a (useless)
    #mass fit.
    ############################################################

    configdict["Components"] = {}
    configdict["Components"] = {"Signal"        : {"Bd2DPi": {"2011" : {"KPiPi": [600000.0*fracRun1] },
                                                              "2012" : {"KPiPi": [600000.0*(1-fracRun1)]
                                                                        }
                                                              }
                                                   }
                                }

    ############################################################
    #"Code" to identify the True ID for each component
    ############################################################

    configdict["TrueID"] = {}
    configdict["TrueID"] = {"Signal"          : 100}
    
    ############################################################
    #Tagging calibration and mistag PDF. If "MistagPDF" : None,
    #then an average mistag is used
    ############################################################

    configdict["Taggers"] = {}
    for comp in configdict["Components"].iterkeys():
        configdict["Taggers"][comp] = {}
        configdict["Taggers"][comp] = {"OS" :
                                       {"Calibration":
                                        { "Type": "GLM",
                                          "XML": ["/eos/lhcb/wg/b2oc/TD_DPi_3fb/calibrations/RLogisticCalibration_Bu2D0Pi_OS_20171109.xml"],
                                          "tageff"   : [0.371],
                                          "tagasymm" : [0.0]
                                          },
                                        "MistagPDF" :
                                        {"Type"       : "FromWorkspace",
                                         "File"       : "/eos/lhcb/wg/b2oc/TD_DPi_3fb/MistagTemplates/Bd2DPiDataTemplates.root",
                                         "Workspace"  : "workspace",
                                         "Name"       : "TemplateOS"
                                         }
                                        },
                                       "SS":
                                       {"Calibration":
                                        { "Type": "GLM",
                                          "XML": ["/eos/lhcb/wg/b2oc/TD_DPi_3fb/calibrations/RLogisticCalibration_Bd2JpsiKst_SS_20171101.xml"],
                                          "tageff"   : [0.80],
                                          "tagasymm" : [0.0]
                                          },
                                        "MistagPDF" :
                                        {"Type"       : "FromWorkspace",
                                         "File"       : "/eos/lhcb/wg/b2oc/TD_DPi_3fb/MistagTemplates/Bd2DPiDataTemplates.root",
                                         "Workspace"  : "workspace",
                                         "Name"       : "TemplateSS"
                                         }
                                        }
                                       }

    ############################################################
    #Time resolution and acceptance (there is a single dict because
    #they are strongly connected in the way they are built).
    #If "TimeErrorPDF" : None, then an average resolution model
    #is used.
    ############################################################

    configdict["ResolutionAcceptance"] = {}
    for comp in configdict["Components"].iterkeys():
        configdict["ResolutionAcceptance"][comp] = {}
        configdict["ResolutionAcceptance"][comp] = {"TimeErrorPDF": None,
                                                    "Acceptance":  #From ANA note v2
                                                    {"Type": "Spline",
                                                     "KnotPositions" : [0.5, 1.0, 1.5, 2.0, 2.3, 2.6, 3.0, 4.0, 10.0],
                                                     "KnotCoefficients" : [1.9440e-01, 3.3275e-01, 6.1444e-01, 8.6628e-01, 9.9600e-01, 1.0745e+00, 1.1083e+00, 1.1565e+00, 1.1946e+00]},
                                                    "Resolution": #From ANA note v2
                                                    {"Type": "AverageModel",
                                                     "Parameters": { 'sigmas': [ 0.05491 ], 'fractions': [] },
                                                     "Bias": [0.0],
                                                     "ScaleFactor": [1.0]}
                                                    }

    ############################################################
    #Production and detection asymmetries
    ############################################################

    configdict["ProductionAsymmetry"] = {}
    configdict["DetectionAsymmetry"] = {}
    configdict["ProductionAsymmetry"]["Signal"] = {}
    configdict["DetectionAsymmetry"]["Signal"] = {}
    configdict["ProductionAsymmetry"]["Signal"] = [-0.0124] #from ANA note v2
    configdict["DetectionAsymmetry"]["Signal"] = [0.0086] #from arXiv:1408.0275v2 (OPPOSITE SIGN!!!)

    ############################################################
    #Time PDF parameters
    ############################################################

    configdict["ACP"] = {}

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

    #Signal (use more convenient interface with ArgLf_d, ArgLbarfbar_d and ModLf_d)
    configdict["ACP"]["Signal"] = { "Gamma"                : [1.0 / 1.518], #Inverse lifetime from HFAG (http://www.slac.stanford.edu/xorg/hfag/osc/summer_2016/)
                                    "DeltaGamma"           : [0.0],
                                    "DeltaM"               : [0.5050], #semileptonic measurement HFAG (http://www.slac.stanford.edu/xorg/hfag/osc/summer_2016/)
                                    "ArgLf"                : [ArgqOverp_d + ArgAbarf_d - ArgAf_d],
                                    "ArgLbarfbar"          : [ArgpOverq_d + ArgAfbar_d - ArgAbarfbar_d],
                                    "ModLf"                : [ModAbarf_d/ModAf_d],
                                    "ParameteriseIntegral" : True,
                                    "NBinsAcceptance"      : 0} #keep at zero if using spline acceptance!

    return configdict
