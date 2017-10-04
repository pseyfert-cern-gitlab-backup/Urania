from ROOT import *

def getconfig( samplemodeyear ) :

    configdict = {}
    
    from math import pi
    from math import log

    import ROOT
    
     # basic variables
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5130,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_MM"}

    configdict["BasicVariables"]["BeautyTime"]    = { "Range"                  : [0.0002,     0.015    ],
                                                      "Bins"                   : 40,
                                                      "Name"                   : "BeautyTime",
                                                      "InputName"              : "lab0_TAU"}
    configdict["BasicVariables"]["BacPIDK"]       = { "Range"                  : [-999.0,    999.0     ],
                                                      "Name"                   : "BacPIDK",
                                                      "InputName"              : "lab1_PIDK"}

    configdict["BasicVariables"]["nTracks"]       = { "Range"                  : [15.0,    1000.0  ],
                                                      "Name"                   : "nTracks",
                                                      "InputName"              : "nTracks"}

    configdict["BasicVariables"]["BacCharge"]     = { "Range"                  : [-1000.0, 1000.0  ],
                                                      "Name"                   : "BacCharge",
                                                      "InputName"              : "lab1_ID"}

    configdict["BasicVariables"]["TagDecOSComb"]      = { "Range"                  : [-1.0,    1.0     ],
                                                          "Name"                   : "TagDecOSCharm",
                                                          "InputName"              : "lab0_TAGDECISION_OS"}

    configdict["BasicVariables"]["TagDecOSCharm"]      = { "Range"                  : [-1.0,    1.0     ],
                                                           "Name"                   : "TagDecOSCharm",
                                                           "InputName"              : "lab0_OS_Charm_DEC"}
    configdict["BasicVariables"]["TagDecOSKaon"]      = { "Range"                  : [-1.0,    1.0     ],
                                                          "Name"                   : "TagDecOSKaon",
                                                          "InputName"              : "lab0_OS_Kaon_DEC"}

    configdict["BasicVariables"]["TagDecOSElectron"]      = { "Range"                  : [-1.0,    1.0     ],
                                                              "Name"                   : "TagDecOSElectron",
                                                              "InputName"              : "lab0_OS_Electron_DEC"}

    configdict["BasicVariables"]["TagDecOSMuon"]      = { "Range"                  : [-1.0,    1.0     ],
                                                          "Name"                   : "TagDecOSMuon",
                                                          "InputName"              : "lab0_OS_Muon_DEC"}

    configdict["BasicVariables"]["TagDecVtxCharge"]      = { "Range"                  : [-1.0,    1.0     ],
                                                             "Name"                   : "TagDecVtxCharge",
                                                             "InputName"              : "lab0_VtxCharge_DEC"}

    configdict["BasicVariables"]["MistagOSComb"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                          "Name"                   : "MistagOSComb",
                                                          "InputName"              : "lab0_TAGOMEGA_OS"}

    configdict["BasicVariables"]["MistagOSCharm"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                           "Name"                   : "MistagOSCharm",
                                                           "InputName"              : "lab0_OS_Charm_PROB"}

    configdict["BasicVariables"]["MistagOSKaon"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                          "Name"                   : "MistagOSKaon",
                                                          "InputName"              : "lab0_OS_Kaon_PROB"}

    configdict["BasicVariables"]["MistagOSElectron"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                              "Name"                   : "MistagOSElectron",
                                                              "InputName"              : "lab0_OS_Electron_PROB"}

    configdict["BasicVariables"]["MistagOSMuon"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                          "Name"                   : "MistagOSMuon",
                                                          "InputName"              : "lab0_OS_Muon_PROB"}

    configdict["BasicVariables"]["MistagVtxCharge"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                             "Name"                   : "MistagVtxCharge",
                                                             "InputName"              : "lab0_VtxCharge_PROB"}

    #Additional variables not foreseen before
    configdict["AdditionalVariables"] = {}

    configdict["AdditionalVariables"]["BeautyID"]      = { "Range"                  : [ -1000.,    1000.     ],
                                                           "Name"                   : "BeautyID",
                                                           "InputName"              : "lab0_ID"}
    
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

    #Useful constants
    Pipeak = 5280.42
    Kpeak = 5.28024e+03

    #Global variables (shared by different PDFs)
    configdict["GlobalVariables"] = {}
    configdict["GlobalVariables"]["eff_Bu2D0Pi_D0Pi"] = {}
    configdict["GlobalVariables"]["eff_Bu2D0Pi_D0Pi"] = {"Type": "RooRealVar",
                                                         "Title": r"\epsilon_{\rm PID}(B^{+}\to D^{0}\pi)_{\pi}",
                                                         "Range": [0.977220574243, 0.8, 1.0],
                                                         "Error": 0.00424543716599
                                                         }
    configdict["GlobalVariables"]["eff_Bu2D0K_D0K"] = {}
    configdict["GlobalVariables"]["eff_Bu2D0K_D0K"] = {"Type": "RooRealVar",
                                                       "Title": r"\epsilon_{\rm PID}(B^{+}\to D^{0}K)_{K}",
                                                       "Range": [0.660474584897, 0.4, 0.9],
                                                       "Error": 0.00590631651609
                                                       }
    configdict["GlobalVariables"]["Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0PiHypo"] = {}
    configdict["GlobalVariables"]["Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0PiHypo"] = {"Type": "RooRealVar",
                                                                                              "Title": r"\mu^{\pi}_{B^{+}\to D^{0}\pi}",
                                                                                              "Range": [Pipeak, 5.2e+03, 5.35e+03]
                                                                                              }
    configdict["GlobalVariables"]["Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0KHypo"] = {}
    configdict["GlobalVariables"]["Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0KHypo"] = {"Type": "RooRealVar",
                                                                                             "Title": r"\mu^{K}_{B^{+}\to D^{0}\pi}",
                                                                                             "Range": [Kpeak, 5.2e+03, 5.35e+03]
                                                                                             }
    configdict["GlobalVariables"]["nSig_"+samplemodeyear+"_Bu2D0PiHypo_Evts"] = {"Type": "RooRealVar",
                                                                                 "Title": r"N^{\pi}_{B^{+}\to D\pi}",
                                                                                 "Range": [8.8726e+05,100000,1200000]
                                                                                 }
    configdict["GlobalVariables"]["nSig_"+samplemodeyear+"_Bu2D0KHypo_Evts"] = {"Type": "RooFormulaVar",
                                                                                "Title": r"N^{K}_{B^{+}\to D^{0}\pi}",
                                                                                "Formula": "((1-@0)/@0)*@1",
                                                                                "Dependents": ["eff_Bu2D0Pi_D0Pi", "nSig_"+samplemodeyear+"_Bu2D0PiHypo_Evts"]
                                                                                }
    configdict["GlobalVariables"]["nBu2D0K_"+samplemodeyear+"_Bu2D0KHypo_Evts"] = {"Type": "RooRealVar",
                                                                                   "Title": r"N^{K}_{B^{+}\to D^{0}K}",
                                                                                   "Range": [4.9426e+04,10000,100000]
                                                                                   }
    configdict["GlobalVariables"]["nBu2D0K_"+samplemodeyear+"_Bu2D0PiHypo_Evts"] = {"Type": "RooFormulaVar",
                                                                                    "Title": r"N^{\pi}_{B^{+}\to D^{0}K}",
                                                                                    "Formula": "((1-@0)/@0)*@1",
                                                                                    "Dependents": ["eff_Bu2D0K_D0K", "nBu2D0K_"+samplemodeyear+"_Bu2D0KHypo_Evts"]
                                                                                    }
    
    configdict["GlobalVariables"]["Signal_Ipatia_BeautyMass_a1_"+samplemodeyear+"_Bu2D0PiHypo"] = {"Type": "RooRealVar",
                                                                                                   "Title": r"a1^{\pi}_{B^{+}\to D^{0}\pi}",
                                                                                                   "Range": [1.73581],# 0.1, 20.0],
                                                                                                   }
    configdict["GlobalVariables"]["Signal_Ipatia_BeautyMass_a2_"+samplemodeyear+"_Bu2D0PiHypo"] = {"Type": "RooRealVar",
                                                                                                   "Title": r"a2^{\pi}_{B^{+}\to D^{0}\pi}",
                                                                                                   "Range": [1.73581],# 0.1, 20.0],
                                                                                                   }
    configdict["GlobalVariables"]["Signal_Ipatia_BeautyMass_n1_"+samplemodeyear+"_Bu2D0PiHypo"] = {"Type": "RooRealVar",
                                                                                                   "Title": r"n1^{\pi}_{B^{+}\to D^{0}\pi}",
                                                                                                   "Range": [2.89926],# 0.1, 20.0],
                                                                                                   }
    configdict["GlobalVariables"]["Signal_Ipatia_BeautyMass_n2_"+samplemodeyear+"_Bu2D0PiHypo"] = {"Type": "RooRealVar",
                                                                                                   "Title": r"n2^{\pi}_{B^{+}\to D^{0}\pi}",
                                                                                                   "Range": [2.94754],# 0.1, 20.0],
                                                                                                   }
    configdict["GlobalVariables"]["Signal_Ipatia_BeautyMass_ascale_"+samplemodeyear+"_Bu2D0PiHypo"] = {"Type": "RooRealVar",
                                                                                                       "Title": r"sa^{\pi}_{B^{+}\to D^{0}\pi}",
                                                                                                       "Range": [1.0, 0.01, 10.0],
                                                                                                       }
    configdict["GlobalVariables"]["Signal_Ipatia_BeautyMass_nscale_"+samplemodeyear+"_Bu2D0PiHypo"] = {"Type": "RooRealVar",
                                                                                                       "Title": r"sn^{\pi}_{B^{+}\to D^{0}\pi}",
                                                                                                       "Range": [1.0, 0.01, 10.0],
                                                                                                       }
    configdict["GlobalVariables"]["Bd2D0PiPi_CBplusG_BeautyMass_sigmaCB_"+samplemodeyear+"_Bu2D0PiHypo"] = {"Type": "RooRealVar",
                                                                                                            "Title": r"\sigmaCB^{\pi}_{\Bz\to D#pi#pi}",
                                                                                                            "Range": [18.6794],
                                                                                                            }
    configdict["GlobalVariables"]["Bd2D0PiPi_CBplusG_BeautyMass_sigmaG_"+samplemodeyear+"_Bu2D0PiHypo"] = {"Type": "RooRealVar",
                                                                                                           "Title": r"\sigmaG^{\pi}_{\Bz\to D#pi#pi}",
                                                                                                           "Range": [29.2967],
                                                                                                           }
    
    #PDF for each fitted component
    #Structure: decay->hypo->observable
    configdict["pdfList"] = {}
    #
    configdict["pdfList"]["Total"] = {}
    configdict["pdfList"]["Total"]["Title"] = "Total"
    configdict["pdfList"]["Total"]["Color"] = kBlue
    configdict["pdfList"]["Total"]["Style"] = kSolid
    #
    configdict["pdfList"]["Signal"] = {}
    configdict["pdfList"]["Signal"]["Title"] = "B_{u}#rightarrowD^{0}#pi"
    configdict["pdfList"]["Signal"]["Color"] = kRed
    configdict["pdfList"]["Signal"]["Style"] = kDashed
    configdict["pdfList"]["Signal"]["Bu2D0Pi"] = {}
    configdict["pdfList"]["Signal"]["Bu2D0Pi"]["BeautyMass"] = { "PDF"        : "Ipatia",
                                                                 "shiftMean"  : False,
                                                                 "scaleTails" : True,
                                                                 "mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0PiHypo",
                                                                 "sigma"      : {"par": [20.111, 1.5e+01, 3.5e+01],
                                                                                 "title": r"\sigma^{\pi}_{B^{+}\to D^{0}\pi}"},
                                                                 "zeta"       : {"par": [0.0],
                                                                                 "title": r"\zeta^{\pi}_{B^{+}\to D^{0}\pi}"},
                                                                 "fb"         : {"par": [0.0],
                                                                                 "title": r"\beta^{\pi}_{B^{+}\to D^{0}\pi}"},
                                                                 "l"          : {"par": [-3.85119],
                                                                                 "title" : "\lambda^{\pi}_{B^{+}\to D^{0}\pi}"},
                                                                 "a1"         : "Signal_Ipatia_BeautyMass_a1_"+samplemodeyear+"_Bu2D0PiHypo", #left
                                                                 "a2"         : "Signal_Ipatia_BeautyMass_a2_"+samplemodeyear+"_Bu2D0PiHypo", #right
                                                                 "n1"         : "Signal_Ipatia_BeautyMass_n1_"+samplemodeyear+"_Bu2D0PiHypo", #left
                                                                 "n2"         : "Signal_Ipatia_BeautyMass_a1_"+samplemodeyear+"_Bu2D0PiHypo"}#right
    
    configdict["pdfList"]["Signal"]["Bu2D0K"] = {}
    configdict["pdfList"]["Signal"]["Bu2D0K"]["BeautyMass"] = { "PDF"        : "Ipatia",
                                                                "shiftMean"  : True,
                                                                "scaleTails" : False,
                                                                #"mean"       : {"par": [5.32185e+03,5.25e+03,5.45e+03],
                                                                #                "title" : r"\mu^{K}_{B^{+}\to D^{0}\pi}"},
                                                                "mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0KHypo",
                                                                "shift"      : {"par": [5321.84-Kpeak],
                                                                                "title" : r"\Delta\mu^{K}_{B^{+}\to D^{0}\pi}"},
                                                                "sigma"      : {"par": [18.9176],
                                                                                "title" : r"\sigma^{K}_{B^{+}\to D^{0}\pi}"},
                                                                "zeta"       : {"par": [0.0],
                                                                                "title" : r"\zeta^{K}_{B^{+}\to D^{0}\pi}"},
                                                                "fb"         : {"par": [0.0],
                                                                                "title" : r"\beta^{K}_{B^{+}\to D^{0}\pi}"},
                                                                "l"          : {"par": [-8.99985],
                                                                                "title" : r"\lambda^{K}_{B^{+}\to D^{0}\pi}"},
                                                                "a1"         : {"par": [2.85692],
                                                                                "title" : r"a1^{K}_{B^{+}\to D^{0}\pi}"},
                                                                "a2"         : {"par": [0.507082],
                                                                                "title" : r"a2^{K}_{B^{+}\to D^{0}\pi}"},
                                                                "n1"         : {"par": [0.109448],
                                                                                "title" : r"n1^{K}_{B^{+}\to D^{0}\pi}"},
                                                                "n2"         : {"par": [2.52514],
                                                                                "title": r"n2^{K}_{B^{+}\to D^{0}\pi}"}}
    #
    configdict["pdfList"]["Bu2D0K"] = {}
    configdict["pdfList"]["Bu2D0K"]["Title"] = "B_{u}#rightarrowD^{0}K"
    configdict["pdfList"]["Bu2D0K"]["Color"] = kBlack
    configdict["pdfList"]["Bu2D0K"]["Style"] = kDotted
    configdict["pdfList"]["Bu2D0K"]["Bu2D0Pi"] = {}
    configdict["pdfList"]["Bu2D0K"]["Bu2D0Pi"]["BeautyMass"] = { "PDF"        : "Ipatia",
                                                                 "shiftMean"  : False,#True,
                                                                 "scaleTails" : False,
                                                                 "mean"       : {"par": [5242.88, 5.15e+03,5.35e+03],
                                                                                 "title" : r"\mu^{\pi}_{B^{+}\to D^{0}K}"},
                                                                 #"mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0PiHypo",
                                                                 #"shift"      : {"par": [5242.88-Kpeak],
                                                                 #                "title" : r"\Delta\mu^{\pi}_{B^{+}\to D^{0}K}"},
                                                                 "sigma"      : {"par": [23.1246],
                                                                                 "title" : r"\sigma^{\pi}_{B^{+}\to D^{0}K}"},
                                                                 "zeta"       : {"par" : [0.0],
                                                                                 "title" : r"\zeta^{\pi}_{B^{+}\to D^{0}K}"},
                                                                 "fb"         : {"par" : [0.0],
                                                                                 "title" : r"\beta^{\pi}_{B^{+}\to D^{0}K}"},
                                                                 "l"          : {"par": [-34.903],
                                                                                 "title" : r"\lambda^{\pi}_{B^{+}\to D^{0}K}"},
                                                                 "a1"         : {"par": [0.869232],
                                                                                 "title" : r"a1^{\pi}_{B^{+}\to D^{0}K}"},
                                                                 "a2"         : {"par": [2.14093],
                                                                                 "title" : r"a2^{\pi}_{B^{+}\to D^{0}K}"},
                                                                 "n1"         : {"par": [7.1034],
                                                                                 "title" : r"n1^{\pi}_{B^{+}\to D^{0}K}"},
                                                                 "n2"         : {"par": [3.51003],
                                                                                 "title" : r"n2^{\pi}_{B^{+}\to D^{0}K}"}}
    configdict["pdfList"]["Bu2D0K"]["Bu2D0K"] = {}
    configdict["pdfList"]["Bu2D0K"]["Bu2D0K"]["BeautyMass"] = {"PDF"        : "Ipatia",
                                                               "shiftMean"  : False,
                                                               "scaleTails" : False,
                                                               "mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0KHypo",
                                                               "sigma"      : {"par": [16.1498, 1.5e+01, 2.5e+01],
                                                                               "title" : r"\sigma^{K}_{B^{+}\to D^{0}K}"},
                                                               "zeta"       : {"par": [0.0],
                                                                               "title" : r"\zeta^{K}_{B^{+}\to D^{0}K}"},
                                                               "fb"         : {"par": [0.0],
                                                                               "title" : r"\beta^{K}_{B^{+}\to D^{0}K}"},
                                                               "l"          : {"par": [-2.95378],
                                                                               "title" : r"\lambda^{K}_{B^{+}\to D^{0}K}"},
                                                               "a1"         : {"par": [2.71239],
                                                                               "title" : r"a1^{K}_{B^{+}\to D^{0}K}"},
                                                               "a2"         : {"par": [1.0e+09],
                                                                               "title" : r"a2^{K}_{B^{+}\to D^{0}K}"},
                                                               "n1"         : {"par": [1.36534],
                                                                               "title" : r"n1^{K}_{B^{+}\to D^{0}K}"},
                                                               "n2"         : {"par": [0.0],
                                                                               "title" : r"n2^{K}_{B^{+}\to D^{0}K}"}}
    #
    configdict["pdfList"]["Bd2D0PiPi"] = {}
    configdict["pdfList"]["Bd2D0PiPi"]["Title"] = "B_{d}#rightarrowD^{0}#pi#pi"
    configdict["pdfList"]["Bd2D0PiPi"]["Color"] = kMagenta
    configdict["pdfList"]["Bd2D0PiPi"]["Style"] = kDotted
    configdict["pdfList"]["Bd2D0PiPi"]["Bu2D0Pi"] = {}
    configdict["pdfList"]["Bd2D0PiPi"]["Bu2D0Pi"]["BeautyMass"] = {"PDF"        : "CrystalBallPlusGaussian",
                                                                   "shiftMean"   : False,
                                                                   "scaleWidths" : True,
                                                                   "mean"       : {"par": [5126.42, 4900, 5200],
                                                                                   "title": r"\mu^{\pi}_{\Bz\to D#pi#pi}"},
                                                                   #"mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0PiHypo",
                                                                   #"shift"      : {"par": [5.12657e+03-Pipeak],
                                                                   #                "title": r"\Delta\mu^{\pi}_{\Bz\to D#pi#pi}"},
                                                                   "alpha"      : {"par": [-2.53195],
                                                                                   "title": r"\alpha^{\pi}_{\Bz\to D#pi#pi}"},
                                                                   "n"          : {"par": [1.09018],
                                                                                   "title": r"n^{\pi}_{\Bz\to D#pi#pi}"},
                                                                   "sigmaCB"    : "Bd2D0PiPi_CBplusG_BeautyMass_sigmaCB_"+samplemodeyear+"_Bu2D0PiHypo",
                                                                   "sigmaG"     : "Bd2D0PiPi_CBplusG_BeautyMass_sigmaG_"+samplemodeyear+"_Bu2D0PiHypo",
                                                                   "scaleSigma" : {"par": [1.0, 0.1, 10.0],
                                                                                   "title": r"s\sigma^{\pi}_{\Bz\to D#pi#pi"},
                                                                   #"sigmaCB"    : {"par": [1.87014e+01, 5, 50],
                                                                   #                "title": r"\sigmaCB^{\pi}_{\Bz\to D#pi#pi}"},
                                                                   #"sigmaG"     : {"par": [2.93595e+01, 1, 60],
                                                                   #                "title": r"\sigmaG^{\pi}_{\Bz\to D#pi#pi}"},
                                                                   "fracG"      : {"par": [0.840982],
                                                                                   "title": r"f^{\pi}_{\Bz\to D#pi#pi}"}}
    configdict["pdfList"]["Bd2D0PiPi"]["Bu2D0K"] = {}
    configdict["pdfList"]["Bd2D0PiPi"]["Bu2D0K"]["BeautyMass"] = {"PDF"        : "None"}
    '''
    configdict["pdfList"]["Bd2D0PiPi"]["Bu2D0K"]["BeautyMass"] = {"PDF"        : "CrystalBallPlusExponential",
                                                                  "shiftMean"  : True,
                                                                  "mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0KHypo",
                                                                  "shift"      : {"par": [5.15747e+03-Kpeak],
                                                                                  "title": r"\Delta\mu^{K}_{\Bz\to D#pi#pi}"},
                                                                  "alpha"      : {"par": [5.01769e-01],
                                                                                  "title": r"\alpha^{K}_{\Bz\to D#pi#pi}"},
                                                                  "n"          : {"par": [3.09581e-01],
                                                                                  "title": r"n^{K}_{\Bz\to D#pi#pi}"},
                                                                  "sigmaCB"    : {"par": [3.96301e+01],
                                                                                  "title": r"\sigmaCB^{K}_{\Bz\to D#pi#pi}"},
                                                                  "cB"         : {"par": [-6.49602e-03],
                                                                                  "title": r"c^{K}_{\Bz\to D#pi#pi}"},
                                                                  "fracExpo"   : {"par": [3.99999e-01],
                                                                                  "title": r"f^{K}_{\Bz\to D#pi#pi}"}}
    '''
    #
    configdict["pdfList"]["Bu2Dst0Pi"] = {}
    configdict["pdfList"]["Bu2Dst0Pi"]["Title"] = "B_{u}#rightarrowD^{*0}#pi"
    configdict["pdfList"]["Bu2Dst0Pi"]["Color"] = kOrange
    configdict["pdfList"]["Bu2Dst0Pi"]["Style"] = kDotted
    configdict["pdfList"]["Bu2Dst0Pi"]["Bu2D0Pi"] = {}
    configdict["pdfList"]["Bu2Dst0Pi"]["Bu2D0Pi"]["BeautyMass"] = {"PDF"        : "JohnsonSUPlusGaussian",
                                                                   "sameMean"   : False,
                                                                   "shiftMean"  : True,
                                                                   "meanJ"      : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0PiHypo",
                                                                   "shift"      : {"par": [5022.57-Pipeak],
                                                                                   "title": r"\Delta\mu^{\pi}_{B^{+}\to D^{*0}\pi}"},
                                                                   "sigmaJ"     : {"par": [274.256],
                                                                                   "title": r"\sigmaJ^{\pi}_{B^{+}\to D^{*0}\pi}"},
                                                                   "nuJ"        : {"par": [-1.88227],
                                                                                   "title": r"\nu^{\pi}_{B^{+}\to D^{*0}\pi}"},
                                                                   "tauJ"       : {"par": [1.02022],
                                                                                   "title": r"\tauJ^{\pi}_{B^{+}\to D^{*0}\pi}"},
                                                                   "meanGshift" : {"par": [101.712],
                                                                                   "title": r"\delta\mu^{\pi}_{B^{+}\to D^{*0}\pi}"},
                                                                   "sigmaG"     : {"par": [36.8633],
                                                                                   "title": r"\sigmaG^{\pi}_{B^{+}\to D^{*0}\pi}"},
                                                                   "frac"       : {"par": [0.418512],
                                                                                   "title": r"f^{\pi}_{B^{+}\to D^{*0}\pi}"}
                                                                   }
    configdict["pdfList"]["Bu2Dst0Pi"]["Bu2D0K"] = {}
    configdict["pdfList"]["Bu2Dst0Pi"]["Bu2D0K"]["BeautyMass"] = {"PDF"        : "CrystalBallPlusExponential",
                                                                  "shiftMean"  : True,
                                                                  "mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0KHypo",
                                                                  "shift"      : {"par": [5178.45-Kpeak],
                                                                                  "title": r"\Delta\mu^{K}_{B^{+}\to D^{*0}\pi}"},
                                                                  "alpha"      : {"par": [-5.5],
                                                                                  "title": r"\alpha^{K}_{B^{+}\to D^{*0}\pi}"},
                                                                  "n"          : {"par": [0.499655],
                                                                                  "title": r"n^{K}_{B^{+}\to D^{*0}\pi}"},
                                                                  "sigmaCB"    : {"par": [65.6027],
                                                                                  "title": r"\sigmaCB^{K}_{B^{+}\to D^{*0}\pi}"},
                                                                  "cB"         : {"par": [-0.00718437],
                                                                                  "title": r"c^{K}_{B^{+}\to D^{*0}\pi}"},
                                                                  "fracExpo"   : {"par": [0.349834],
                                                                                  "title": r"f^{K}_{B^{+}\to D^{*0}\pi}"}}
    #
    '''
    configdict["pdfList"]["Bs2D0KPi"] = {}
    configdict["pdfList"]["Bs2D0KPi"]["Title"] = "B_{s}#rightarrowD^{0}K#pi"
    configdict["pdfList"]["Bs2D0KPi"]["Color"] = kGreen+3
    configdict["pdfList"]["Bs2D0KPi"]["Style"] = kDotted
    configdict["pdfList"]["Bs2D0KPi"]["Bu2D0Pi"] = {}
    configdict["pdfList"]["Bs2D0KPi"]["Bu2D0Pi"]["BeautyMass"] = {"PDF"        : "JohnsonSU",
                                                                  "shiftMean"  : True,
                                                                  "mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0PiHypo",
                                                                  "shift"      : {"par": [5.11599e+03-Pipeak],
                                                                                  "title": r"\Delta\mu^{\pi}_{B^{0}_{s}\to D^{0}K\pi}"},
                                                                  "sigma"      : {"par": [8.66345e+01],
                                                                                  "title": r"\sigma^{\pi}_{B^{0}_{s}\to D^{0}K\pi}"},
                                                                  "nu"         : {"par": [-1.85383e+00],
                                                                                  "title": r"\nu^{\pi}_{B^{0}_{s}\to D^{0}K\pi}"},
                                                                  "tau"        : {"par": [7.07216e-01],
                                                                                  "title": r"\tau^{\pi}_{B^{0}_{s}\to D^{0}K\pi}"}}
    configdict["pdfList"]["Bs2D0KPi"]["Bu2D0K"] = {}
    configdict["pdfList"]["Bs2D0KPi"]["Bu2D0K"]["BeautyMass"] = {"PDF"        : "JohnsonSU",
                                                                 "shiftMean"  : True,
                                                                 "mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bu2D0KHypo",
                                                                 "shift"      : {"par": [5.05141e+03 -Pipeak],
                                                                                 "title": r"\Delta\mu^{K}_{B^{0}_{s}\to D^{0}K\pi}"},
                                                                 "sigma"      : {"par": [3.49927e+02],
                                                                                 "title": r"\sigma^{K}_{B^{0}_{s}\to D^{0}K\pi}"},
                                                                 "nu"         : {"par": [-1.86089e+00],
                                                                                 "title": r"\nu^{K}_{B^{0}_{s}\to D^{0}K\pi}"},
                                                                 "tau"        : {"par": [1.22910e+00],
                                                                                  "title": r"\tau^{K}_{B^{0}_{s}\to D^{0}K\pi}"}}
    '''
    #
    configdict["pdfList"]["Bu2DKst"] = {}
    configdict["pdfList"]["Bu2DKst"]["Title"] = "B_{u}#rightarrowD^{0}K^{*}"
    configdict["pdfList"]["Bu2DKst"]["Color"] = kPink
    configdict["pdfList"]["Bu2DKst"]["Style"] = kDotted
    configdict["pdfList"]["Bu2DKst"]["Bu2D0Pi"] = {}
    configdict["pdfList"]["Bu2DKst"]["Bu2D0Pi"]["BeautyMass"] = {"PDF"      : "None"}
    configdict["pdfList"]["Bu2DKst"]["Bu2D0K"] = {}
    configdict["pdfList"]["Bu2DKst"]["Bu2D0K"]["BeautyMass"] = {"PDF"        : "Gaussian",
                                                                "shiftMean"  : False,
                                                                "mean"       : {"par": [4.8549e+03, 4600, 5200],
                                                                                "title": "\mu^{K}_{B^{+}\to D^{0}K^{*}}"},
                                                                "sigma"      : {"par": [1.0126e+02, 50, 200],
                                                                                "title": "\sigma^{K}_{B^{+}\to D^{0}K^{*}}"}}
    #
    configdict["pdfList"]["Comb"] = {}
    configdict["pdfList"]["Comb"]["Title"] = "Combinatorial"
    configdict["pdfList"]["Comb"]["Color"] = kBlue
    configdict["pdfList"]["Comb"]["Style"] = kDotted
    configdict["pdfList"]["Comb"]["Bu2D0Pi"] = {}
    #configdict["pdfList"]["Comb"]["Bu2D0Pi"]["BeautyMass"] = { "PDF"          : "DoubleExponential",
    #                                                           "Title"        : "Combinatorial",
    #                                                           "cB1"          : {"par": [-1.72409e-03, -15.0e-03, -1.0e-03],
    #                                                                             "title" : r"c1^{\pi}_{\rm comb}"},
    #                                                           "cB2"          : {"par": [-1.72409e-03, -15.0e-03, -1.0e-03],
    #                                                                             "title" : r"c2^{\pi}_{\rm comb}"},
    #                                                           "frac"         : {"par": [7.0e-01,0.01,1.0],
    #                                                                             "title" : r"f^{\pi}_{\rm comb}"}}
    configdict["pdfList"]["Comb"]["Bu2D0Pi"]["BeautyMass"] = { "PDF"          : "Exponential",
                                                               "Title"        : "Combinatorial",
                                                               "cB"           : {"par": [-1.72409e-03, -15.0e-03, -1.0e-03],
                                                                                 "title" : r"c1^{\pi}_{\rm comb}"}}
    
    configdict["pdfList"]["Comb"]["Bu2D0K"] = {}
    configdict["pdfList"]["Comb"]["Bu2D0K"]["BeautyMass"] = { "PDF"          : "Exponential",
                                                              "Title"        : "Combinatorial",
                                                              "cB"           : {"par": [-2.0e-03, -15.0e-03, -1.0e-03],
                                                                                "title" : r"c^{K}_{\rm comb}"}}
    #Axes titles
    configdict["AxisTitle"] = {"BeautyMass": {"Bu2D0Pi":"D^{0}#pi mass (MeV/c^{2})",
                                              "Bu2D0K":"D^{0}K mass (MeV/c^{2})"}}

    #Range
    configdict["Range"] = {"BeautyMass": {"Range": [configdict["BasicVariables"]["BeautyMass"]["Range"][0],
                                                    configdict["BasicVariables"]["BeautyMass"]["Range"][1]],
                                          "Bins": 300}}#227}}#455}}

    #Range and sample for sWeights
    configdict["sWeights"] = {"Hypo" : "Bu2D0Pi",
                              "Range" : {"BeautyMass" : [5220.0, 5600.0] },
                              "Bins"  : 190
                              }

    #Log scale
    configdict["LogScale"] = {"BeautyMass": {"Bu2D0Pi" : [1e-03, 1e+05], "Bu2D0K" : [1e-01, 1e+04] } }

    #Some coordinates
    configdict["Legend"] = {"Xmin" : 0.6,
                            "Ymin" : 0.2,
                            "Xmax" : 0.89,
                            "Ymax" : 0.6}
    configdict["LHCbText"] = {"X"    : 0.89,
                              "Y"    : 0.8,
                              "Text" : "LHCb Preliminary"}
    configdict["Chi2"] = {"X"    : 0.6,
                          "Y"    : 0.7}

    #Yields
    configdict["Yields"] = {"Signal"   : {"Bu2D0Pi"  : "nSig_"+samplemodeyear+"_Bu2D0PiHypo_Evts",
                                          "Bu2D0K": "nSig_"+samplemodeyear+"_Bu2D0KHypo_Evts"},
                            "Bu2D0K"    : {"Bu2D0Pi"  : "nBu2D0K_"+samplemodeyear+"_Bu2D0PiHypo_Evts",
                                           "Bu2D0K": "nBu2D0K_"+samplemodeyear+"_Bu2D0KHypo_Evts"},
                            "Bu2Dst0Pi"    : {"Bu2D0Pi"  : {"par": [1.0000e+05,50000,300000],
                                                            "title": r"N^{\pi}_{B^{+}\to D^{*0}\pi}"},
                                              "Bu2D0K": {"par": [1.3533e+04,1000,50000],
                                                         "title": r"N^{K}_{B^{+}\to D^{*0}\pi}"}},
                            "Bd2D0PiPi" : {"Bu2D0Pi"  : {"par": [7.4791e+04,1000,100000],
                                                         "title": r"N^{\pi}_{\Bz\to D^{0}\pi\pi}"},
                                           "Bu2D0K": {"par": [0],#[18000,0,100000],
                                                      "title": r"N^{K}_{\Bz\to D^{0}\pi\pi}"}},
                            #"Bs2D0KPi" : {"Bu2D0Pi"  : {"par": [20000,0,100000],
                            #                            "title": r"N^{\pi}_{B^{0}_{s}\to D^{0}K\pi}"},
                            #              "Bu2D0K": {"par": [5000,0,50000],
                            #                         "title": r"N^{K}_{B^{0}_{s}\to D^{0}K\pi}"}},
                            "Bu2DKst" : {"Bu2D0Pi"  : {"par": [0],
                                                       "title": r"N^{\pi}_{LM}"},
                                         "Bu2D0K": {"par": [1.0948e+04,1000,50000],
                                                    "title": r"N^{K}_{LM}"}},
                            "Comb"     : {"Bu2D0Pi"  : {"par": [4.7142e+05,100000,600000],
                                                        "title" : r"N^{\pi}_{\rm comb}"},
                                          "Bu2D0K": {"par": [2.2488e+05,50000,500000],
                                                     "title" : r"N^{K}_{\rm comb}"},}}

    #Gaussian constraints
    configdict["GaussianConstraints"] = {}
    configdict["GaussianConstraints"]["Eff_Bu2D0Pi_D0Pi"] = {"Parameters" : ["eff_Bu2D0Pi_D0Pi"],
                                                             "Mean"       : [configdict["GlobalVariables"]["eff_Bu2D0Pi_D0Pi"]["Range"][0]],
                                                             "Covariance" : [configdict["GlobalVariables"]["eff_Bu2D0Pi_D0Pi"]["Error"]]}
    configdict["GaussianConstraints"]["Eff_Bu2D0K_D0K"] = {"Parameters" : ["eff_Bu2D0K_D0K"],
                                                           "Mean"       : [configdict["GlobalVariables"]["eff_Bu2D0K_D0K"]["Range"][0]],
                                                           "Covariance" : [configdict["GlobalVariables"]["eff_Bu2D0K_D0K"]["Error"]]}

    #Plot of the fit to compute sWeights
    configdict["sWeightsFitPlot"] = {}
    configdict["sWeightsFitPlot"]["Total"] = {"Color" : kBlue,
                                              "Style" : kSolid,
                                              "Title" : "Total"}
    configdict["sWeightsFitPlot"]["Signal"] = {"Color" : kRed,
                                               "Style" : kDashed,
                                               "Title" : "Signal"}
    configdict["sWeightsFitPlot"]["Background"] = {"Color" : kBlack,
                                                   "Style" : kDotted,
                                                   "Title" : "Background"}
    
    #sWeight plot
    configdict["plotsWeights"] = {"CharmMass"  : "K#pi#pi mass (MeV/c^{2})"}
    
    return configdict
