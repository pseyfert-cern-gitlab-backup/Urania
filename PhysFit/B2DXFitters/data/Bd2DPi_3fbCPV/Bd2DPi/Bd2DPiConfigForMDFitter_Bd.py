from ROOT import *

def getconfig( samplemodeyear ) :

    configdict = {}
    
    from math import pi
    from math import log

    import ROOT
        
    # basic variables
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5090,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_FitDaughtersConst_M_flat"}

    configdict["BasicVariables"]["CharmMass"]     = { "Range"                  : [1830,    1904    ],
                                                      "Name"                   : "CharmMass",
                                                      "InputName"              : "lab0_FitwithoutConst_Dplus_M_flat"}

    configdict["BasicVariables"]["BeautyTime"]    = { "Range"                  : [0.4,     15.0    ],
                                                      "Bins"                   : 40,
                                                      "Name"                   : "BeautyTime",
                                                      "InputName"              : "lab0_FitDaughtersPVConst_ctau_flat"}
    
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

    configdict["BasicVariables"]["BeautyTimeErr"] = { "Range"                  : [0.01,    0.1     ],
                                                      "Name"                   : "BeautyTimeErr",
                                                      "InputName"              : "lab0_FitDaughtersPVConst_ctauErr_flat"}
    
    configdict["BasicVariables"]["BacCharge"]     = { "Range"                  : [-1000.0, 1000.0  ],
                                                      "Name"                   : "BacCharge",
                                                      "InputName"              : "lab1_ID"}
    
    configdict["BasicVariables"]["TagDecOSComb"]      = { "Range"                  : [-1.0,    1.0     ],
                                                          "Name"                   : "TagDecOSComb",
                                                          "InputName"              : "obsTagOS"}

    configdict["BasicVariables"]["TagDecOSCharm"]      = { "Range"                  : [-1.0,    1.0     ],
                                                           "Name"                   : "TagDecOSCharm",
                                                           "InputName"              : "obsTagOSCharm"}

    configdict["BasicVariables"]["TagDecOSKaon"]      = { "Range"                  : [-1.0,    1.0     ],
                                                          "Name"                   : "TagDecOSKaon",
                                                          "InputName"              : "obsTagOSKaon"}

    configdict["BasicVariables"]["TagDecOSElectron"]      = { "Range"                  : [-1.0,    1.0     ],
                                                              "Name"                   : "TagDecOSElectron",
                                                              "InputName"              : "obsTagOSElectron"}

    configdict["BasicVariables"]["TagDecOSMuon"]      = { "Range"                  : [-1.0,    1.0     ],
                                                          "Name"                   : "TagDecOSMuon",
                                                          "InputName"              : "obsTagOSMuon"}

    configdict["BasicVariables"]["TagDecVtxCharge"]      = { "Range"                  : [-1.0,    1.0     ],
                                                             "Name"                   : "TagDecVtxCharge",
                                                             "InputName"              : "obsTagVtxQ"}

    configdict["BasicVariables"]["TagDecSS"]      = { "Range"                  : [-1.0,    1.0     ],
                                                      "Name"                   : "TagDecSS",
                                                      "InputName"              : "obsTagSS_PionInvBoost_ProtonInvBoost"}

    configdict["BasicVariables"]["TagDecSSPionBDT"]      = { "Range"                  : [-1.0,    1.0     ],
                                                             "Name"                   : "TagDecSSPionBDT",
                                                             "InputName"              : "obsTagSSPionBDT_InvBoost"}

    configdict["BasicVariables"]["TagDecSSProton"]      = { "Range"                  : [-1.0,    1.0     ],
                                                            "Name"                   : "TagDecSSProton",
                                                            "InputName"              : "obsTagSSProton_InvBoost"}

    configdict["BasicVariables"]["MistagOSComb"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                          "Name"                   : "MistagOSComb",
                                                          "InputName"              : "obsEtaOS"}

    configdict["BasicVariables"]["MistagOSCharm"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                           "Name"                   : "MistagOSCharm",
                                                           "InputName"              : "obsEtaOSCharm"}

    configdict["BasicVariables"]["MistagOSKaon"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                          "Name"                   : "MistagOSKaon",
                                                          "InputName"              : "obsEtaOSKaon"}

    configdict["BasicVariables"]["MistagOSElectron"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                              "Name"                   : "MistagOSElectron",
                                                              "InputName"              : "obsEtaOSElectron"}

    configdict["BasicVariables"]["MistagOSMuon"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                          "Name"                   : "MistagOSMuon",
                                                          "InputName"              : "obsEtaOSMuon"}

    configdict["BasicVariables"]["MistagVtxCharge"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                             "Name"                   : "MistagVtxCharge",
                                                             "InputName"              : "obsEtaVtxQ"}

    configdict["BasicVariables"]["MistagSS"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                      "Name"                   : "MistagSS",
                                                      "InputName"              : "obsEtaSS_PionInvBoost_ProtonInvBoost"}

    configdict["BasicVariables"]["MistagSSPionBDT"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                             "Name"                   : "MistagSSPionBDT",
                                                             "InputName"              : "obsEtaSSPionBDT_InvBoost"}

    configdict["BasicVariables"]["MistagSSProton"]      = { "Range"                  : [ 0.0,    0.5     ],
                                                            "Name"                   : "MistagSSProton",
                                                            "InputName"              : "obsEtaSSProton_InvBoost"}

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
    
    configdict["AdditionalVariables"]["nPV"]      = { "Range"                  : [ 0.0,    10     ],
                                                      "Name"                   : "nPV",
                                                      "InputName"              : "nPV"}

    #Useful constants
    Pipeak = 5.2797e+03
    Kpeak = 5.28008e+03

    #Global variables (shared by different PDFs)
    configdict["GlobalVariables"] = {}
    configdict["GlobalVariables"]["eff_Bd2DPi_DPi"] = {}
    configdict["GlobalVariables"]["eff_Bd2DPi_DPi"] = {"Type": "RooRealVar",
                                                       "Title": r"\epsilon_{\rm PID}(\Bz\to D\pi)_{\pi}",
                                                       "Range": [0.979017227005, 0.8, 1.0],
                                                       "Error": 0.00399911250625
                                                       }
    configdict["GlobalVariables"]["eff_Bd2DK_DK"] = {}
    configdict["GlobalVariables"]["eff_Bd2DK_DK"] = {"Type": "RooRealVar",
                                                     "Title": r"\epsilon_{\rm PID}(\Bz\to DK)_{K}",
                                                     "Range": [0.63099930914, 0.5, 0.8],
                                                     "Error": 0.00646713602668
                                                     }
    configdict["GlobalVariables"]["Signal_BeautyMass_mean_"+samplemodeyear+"_Bd2DPiHypo"] = {}
    configdict["GlobalVariables"]["Signal_BeautyMass_mean_"+samplemodeyear+"_Bd2DPiHypo"] = {"Type": "RooRealVar",
                                                                                             "Title": r"\mu^{\pi}_{\Bz\to D\pi}",
                                                                                             "Range": [Pipeak, 5.2e+03, 5.35e+03]
                                                                                             }
    configdict["GlobalVariables"]["Signal_BeautyMass_mean_"+samplemodeyear+"_Bd2DKHypo"] = {}
    configdict["GlobalVariables"]["Signal_BeautyMass_mean_"+samplemodeyear+"_Bd2DKHypo"] = {"Type": "RooRealVar",
                                                                                            "Title": r"\mu^{K}_{\Bz\to D\pi}",
                                                                                            "Range": [Kpeak, 5.2e+03, 5.35e+03]
                                                                                            }
    configdict["GlobalVariables"]["nSig_"+samplemodeyear+"_Bd2DPiHypo_Evts"] = {"Type": "RooRealVar",
                                                                                "Title": r"N^{\pi}_{\Bz\to D\pi}",
                                                                                "Range": [500000,100000,900000]
                                                                                }
    configdict["GlobalVariables"]["nSig_"+samplemodeyear+"_Bd2DKHypo_Evts"] = {"Type": "RooFormulaVar",
                                                                               "Title": r"N^{K}_{\Bz\to D\pi}",
                                                                               "Formula": "((1-@0)/@0)*@1",
                                                                               "Dependents": ["eff_Bd2DPi_DPi", "nSig_"+samplemodeyear+"_Bd2DPiHypo_Evts"]
                                                                               }
    configdict["GlobalVariables"]["nBd2DK_"+samplemodeyear+"_Bd2DKHypo_Evts"] = {"Type": "RooRealVar",
                                                                                 "Title": r"N^{K}_{\Bz\to DK}",
                                                                                 "Range": [30000,1000,50000]
                                                                                 }
    configdict["GlobalVariables"]["nBd2DK_"+samplemodeyear+"_Bd2DPiHypo_Evts"] = {"Type": "RooFormulaVar",
                                                                                  "Title": r"N^{\pi}_{\Bz\to DK}",
                                                                                  "Formula": "((1-@0)/@0)*@1",
                                                                                  "Dependents": ["eff_Bd2DK_DK", "nBd2DK_"+samplemodeyear+"_Bd2DKHypo_Evts"]
                                                                                  }
    configdict["GlobalVariables"]["nBd2DKst_"+samplemodeyear+"_Bd2DKHypo_Evts"] = {"Type": "RooRealVar",
                                                                                   "Title": r"N^{K}_{\Bz\to D\Kst}",
                                                                                   "Range": [5000, 100, 10000],
                                                                                   }
    configdict["GlobalVariables"]["DRho_to_DKst_KHypo"] = {"Type": "RooRealVar",
                                                           "Title": "DRho_to_DKst_KHypo",
                                                           "Range": [0.92],
                                                           "Error": 0.21
                                                           }
    configdict["GlobalVariables"]["nBd2DRho_"+samplemodeyear+"_Bd2DKHypo_Evts"] = {"Type": "RooFormulaVar",
                                                                                   "Title": r"N^{K}_{\Bz\to D\rho}",
                                                                                   "Formula": "@0*@1",
                                                                                   "Dependents": ["nBd2DKst_"+samplemodeyear+"_Bd2DKHypo_Evts","DRho_to_DKst_KHypo"] 
                                                                                   }

    #configdict["GlobalVariables"]["DsPi_to_DPi_PiHypo"] = {"Type": "RooRealVar",
    #                                                       "Title": "DsPi_to_DPi_PiHypo",
    #                                                       "Range": [0.019],
    #                                                       "Error": 0.013
    #                                                       }
    #configdict["GlobalVariables"]["nBs2DsPi_"+samplemodeyear+"_Bd2DPiHypo_Evts"] = {"Type": "RooFormulaVar",
    #                                                                                "Title": "nBs2DsPi_"+samplemodeyear+"_Bd2DPiHypo_Evts",
    #                                                                                "Formula": "@0*@1",
    #                                                                                "Dependents": ["nSig_"+samplemodeyear+"_Bd2DPiHypo_Evts","DsPi_to_DPi_PiHypo"]
    #                                                                                }
    
    configdict["GlobalVariables"]["Signal_IpatiaPlusJohnsonSU_BeautyMass_a1_"+samplemodeyear+"_Bd2DPiHypo"] = {"Type": "RooRealVar",
                                                                                                           "Title": r"a1^{\pi}_{\Bz\to D\pi}",
                                                                                                           "Range": [1.3927e+00],
                                                                                                           }
    configdict["GlobalVariables"]["Signal_IpatiaPlusJohnsonSU_BeautyMass_a2_"+samplemodeyear+"_Bd2DPiHypo"] = {"Type": "RooRealVar",
                                                                                                           "Title": r"a2^{\pi}_{\Bz\to D\pi}",
                                                                                                           "Range": [1.4374e+00],
                                                                                                           }
    configdict["GlobalVariables"]["Signal_IpatiaPlusJohnsonSU_BeautyMass_n1_"+samplemodeyear+"_Bd2DPiHypo"] = {"Type": "RooRealVar",
                                                                                                           "Title": r"n1^{\pi}_{\Bz\to D\pi}",
                                                                                                           "Range": [1.9948e+00],
                                                                                                           }
    configdict["GlobalVariables"]["Signal_IpatiaPlusJohnsonSU_BeautyMass_n2_"+samplemodeyear+"_Bd2DPiHypo"] = {"Type": "RooRealVar",
                                                                                                           "Title": r"n2^{\pi}_{\Bz\to D\pi}",
                                                                                                           "Range": [4.4764e+00],
                                                                                                           }
    configdict["GlobalVariables"]["Signal_IpatiaPlusJohnsonSU_BeautyMass_ascale_"+samplemodeyear+"_Bd2DPiHypo"] = {"Type": "RooRealVar",
                                                                                                               "Title": r"sa^{\pi}_{\Bz\to D\pi}",
                                                                                                               "Range": [1.0, 0.1, 1.9],
                                                                                                               }
    configdict["GlobalVariables"]["Signal_IpatiaPlusJohnsonSU_BeautyMass_nscale_"+samplemodeyear+"_Bd2DPiHypo"] = {"Type": "RooRealVar",
                                                                                                               "Title": r"sn^{\pi}_{\Bz\to D\pi}",
                                                                                                               "Range": [1.0, 0.1, 1.9],
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
    configdict["pdfList"]["Signal"]["Title"] = "B_{d}#rightarrowD#pi"
    configdict["pdfList"]["Signal"]["Color"] = kRed
    configdict["pdfList"]["Signal"]["Style"] = kDashed
    configdict["pdfList"]["Signal"]["Bd2DPi"] = {}
    configdict["pdfList"]["Signal"]["Bd2DPi"]["BeautyMass"] = { "PDF"        : "IpatiaPlusJohnsonSU",
                                                                "shiftMean"  : False,
                                                                "scaleTails" : True,
                                                                "mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bd2DPiHypo",
                                                                "sigmaI"     : {"par": [2.4114e+01, 1.5e+01, 3.5e+01],
                                                                                "title": r"\sigmaI^{\pi}_{\Bz\to D\pi}"},
                                                                "sigmaJ"     : {"par": [1.8326e+01, 1.2e+01, 3.4e+01],
                                                                                "title": r"\sigmaJ^{\pi}_{\Bz\to D\pi}"},
                                                                "zeta"       : {"par": [0.0],
                                                                                "title": r"\zeta^{\pi}_{\Bz\to D\pi}"},
                                                                "fb"         : {"par": [0.0],
                                                                                "title": r"\beta^{\pi}_{\Bz\to D\pi}"},
                                                                "l"          : {"par": [-2.0282e+00],
                                                                                "title" : "\lambda^{\pi}_{\Bz\to D\pi}"},
                                                                "a1"         : "Signal_IpatiaPlusJohnsonSU_BeautyMass_a1_"+samplemodeyear+"_Bd2DPiHypo", #left
                                                                "a2"         : "Signal_IpatiaPlusJohnsonSU_BeautyMass_a2_"+samplemodeyear+"_Bd2DPiHypo", #right
                                                                "n1"         : "Signal_IpatiaPlusJohnsonSU_BeautyMass_n1_"+samplemodeyear+"_Bd2DPiHypo", #left
                                                                "n2"         : "Signal_IpatiaPlusJohnsonSU_BeautyMass_n2_"+samplemodeyear+"_Bd2DPiHypo",#right,
                                                                "nu"         : {"par": [-7.9229e-01],
                                                                                "title": r"\nu^{\pi}_{\Bz\to D\pi}"},
                                                                "tau"        : {"par": [3.7118e-01],
                                                                                "title": r"\tau^{\pi}_{\Bz\to D\pi}"},
                                                                "fracI"      : {"par": [7.5688e-01],
                                                                                "title": r"f^{\pi}_{\Bz\to D\pi}"}}
    
    configdict["pdfList"]["Signal"]["Bd2DK"] = {}
    configdict["pdfList"]["Signal"]["Bd2DK"]["BeautyMass"] = { "PDF"        : "Ipatia",
                                                               "shiftMean"  : False,
                                                               "scaleTails" : False,
                                                               "mean"       : {"par": [5.32545e+03,5.25e+03,5.45e+03],
                                                                               "title" : r"\mu^{K}_{\Bz\to D\pi}"},
                                                               "sigma"      : {"par": [2.40558e+01],
                                                                               "title" : r"\sigma^{K}_{\Bz\to D\pi}"},
                                                               "zeta"       : {"par": [0.0],
                                                                               "title" : r"\zeta^{K}_{\Bz\to D\pi}"},
                                                               "fb"         : {"par": [0.0],
                                                                               "title" : r"\beta^{K}_{\Bz\to D\pi}"},
                                                               "l"          : {"par": [-4.83138e+00],
                                                                               "title" : r"\lambda^{K}_{\Bz\to D\pi}"},
                                                               "a1"         : {"par": [3.17596e+00],
                                                                               "title" : r"a1^{K}_{\Bz\to D\pi}"},
                                                               "a2"         : {"par": [7.34724e-01],
                                                                               "title" : r"a2^{K}_{\Bz\to D\pi}"},
                                                               "n1"         : {"par": [1.77019e-02],
                                                                               "title" : r"n1^{K}_{\Bz\to D\pi}"},
                                                               "n2"         : {"par": [2.12031e+00],
                                                                               "title": r"n2^{K}_{\Bz\to D\pi}"}}
    #
    configdict["pdfList"]["Bd2DK"] = {}
    configdict["pdfList"]["Bd2DK"]["Title"] = "B_{d}#rightarrowDK"
    configdict["pdfList"]["Bd2DK"]["Color"] = kBlack
    configdict["pdfList"]["Bd2DK"]["Style"] = kDotted
    configdict["pdfList"]["Bd2DK"]["Bd2DPi"] = {}
    configdict["pdfList"]["Bd2DK"]["Bd2DPi"]["BeautyMass"] = { "PDF"        : "Ipatia",
                                                               "shiftMean"  : False,
                                                               "scaleTails" : False,
                                                               "mean"       : {"par": [5.24015e+03,5.15e+03,5.35e+03],
                                                                               "title" : r"\mu^{\pi}_{\Bz\to DK}"},
                                                               "sigma"      : {"par": [2.33280e+01],
                                                                               "title" : r"\sigma^{\pi}_{\Bz\to DK}"},
                                                               "zeta"       : {"par": [0.0],
                                                                               "title" : r"\zeta^{\pi}_{\Bz\to DK}"},
                                                               "fb"         : {"par": [0.0],
                                                                               "title" : r"\beta^{\pi}_{\Bz\to DK}"},
                                                               "l"          : {"par": [-2.56353e+01],
                                                                               "title" : r"\lambda^{\pi}_{\Bz\to DK}"},
                                                               "a1"         : {"par": [8.72252e-01],
                                                                               "title" : r"a1^{\pi}_{\Bz\to DK}"},
                                                               "a2"         : {"par": [1.12019e+00],
                                                                               "title" : r"a2^{\pi}_{\Bz\to DK}"},
                                                               "n1"         : {"par": [6.26499e+00],
                                                                               "title" : r"n1^{\pi}_{\Bz\to DK}"},
                                                               "n2"         : {"par": [1.33240e+01],
                                                                               "title" : r"n2^{\pi}_{\Bz\to DK}"}}
    configdict["pdfList"]["Bd2DK"]["Bd2DK"] = {}
    configdict["pdfList"]["Bd2DK"]["Bd2DK"]["BeautyMass"] = {"PDF"        : "Ipatia",
                                                             "shiftMean"  : False,
                                                             "scaleTails" : False,
                                                             "mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bd2DKHypo",
                                                             "sigma"      : {"par": [1.69154e+01, 1.5e+01, 1.9e+01],
                                                                             "title": r"\sigma^{K}_{\Bz\to DK}"},
                                                             "zeta"       : {"par": [0.0],
                                                                             "title" : r"\zeta^{K}_{\Bz\to DK}"},
                                                             "fb"         : {"par": [0.0],
                                                                             "title" : r"\beta^{K}_{\Bz\to DK}"},
                                                             "l"          : {"par": [-4.30775e+00],
                                                                             "title" : r"\lambda^{K}_{\Bz\to DK}"},
                                                             "a1"         : {"par": [2.79678e+00],
                                                                             "title" : r"a1^{K}_{\Bz\to DK}"},
                                                             "a2"         : {"par": [1.0e+09],
                                                                             "title" : r"a2^{K}_{\Bz\to DK}"},
                                                             "n1"         : {"par": [8.36542e-01],
                                                                             "title" : r"n1^{K}_{\Bz\to DK}"},
                                                             "n2"         : {"par": [0.0],
                                                                             "title" : r"n2^{K}_{\Bz\to DK}"}}
    #
    configdict["pdfList"]["Bd2DRho"] = {}
    configdict["pdfList"]["Bd2DRho"]["Title"] = "B_{d}#rightarrowD#rho"
    configdict["pdfList"]["Bd2DRho"]["Color"] = kMagenta
    configdict["pdfList"]["Bd2DRho"]["Style"] = kDotted
    configdict["pdfList"]["Bd2DRho"]["Bd2DPi"] = {}
    configdict["pdfList"]["Bd2DRho"]["Bd2DPi"]["BeautyMass"] = {"PDF"        : "JohnsonSU",
                                                                "shiftMean" : True,
                                                                "mean"      : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bd2DPiHypo",
                                                                "shift"     : {"par": [4.70048e+03-Pipeak],
                                                                               "title" : r"\Delta\mu^{\pi}_{\Bz\to D\rho}"},
                                                                "sigma"     : {"par": [8.80692e+02],
                                                                               "title" : r"\sigma^{\pi}_{\Bz\to D\rho}"},
                                                                "nu"        : {"par": [-2.10246e+00],
                                                                               "title" : r"\nu^{\pi}_{\Bz\to D\rho}"},
                                                                "tau"       : {"par": [1.25143e+00],
                                                                               "title" : r"\tau^{\pi}_{\Bz\to D\rho}"}}
    configdict["pdfList"]["Bd2DRho"]["Bd2DK"] = {}
    configdict["pdfList"]["Bd2DRho"]["Bd2DK"]["BeautyMass"] = {"PDF"        : "DoubleGaussian",
                                                               "shiftMean"  : True,
                                                               "sameMean"   : True,
                                                               "mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bd2DKHypo",
                                                               "shift"      : {"par": [5.12543e+03-Kpeak],
                                                                               "title" : r"\Delta\mu^{K}_{\Bz\to D\rho}"},
                                                               "sigma1"     : {"par": [1.06979e+02],
                                                                               "title" : r"\sigma 1\mu^{K}_{\Bz\to D\rho}"},
                                                               "sigma2"     : {"par": [3.16122e+01],
                                                                               "title" : r"\sigma 2^{K}_{\Bz\to D\rho}"},
                                                               "frac"       : {"par": [5.53831e-01],
                                                                               "title" : r"f^{K}_{\Bz\to D\rho}"}}
    #
    configdict["pdfList"]["Bd2DstPi"] = {}
    configdict["pdfList"]["Bd2DstPi"]["Title"] = "B_{d}#rightarrowD^{*}#pi"
    configdict["pdfList"]["Bd2DstPi"]["Color"] = kGreen
    configdict["pdfList"]["Bd2DstPi"]["Style"] = kDotted
    configdict["pdfList"]["Bd2DstPi"]["Bd2DPi"] = {}
    configdict["pdfList"]["Bd2DstPi"]["Bd2DPi"]["BeautyMass"] = {"PDF"         : "CrystalBallPlusGaussian",
                                                                 "shiftMean"   : True,
                                                                 "scaleWidths" : False,
                                                                 "mean"        : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bd2DPiHypo",
                                                                 "shift"       : {"par": [5.10109e+03-Pipeak],
                                                                                  "title" : r"\Delta\mu^{\pi}_{\Bz\to \Dst\pi}"},
                                                                 "alpha"       : {"par": [-1.50868e+00],
                                                                                  "title" : r"\alpha^{\pi}_{\Bz\to \Dst\pi}"},
                                                                 "n"           : {"par": [5.11308e+00],
                                                                                  "title" : r"n^{\pi}_{\Bz\to \Dst\pi}"},
                                                                 "sigmaCB"     : {"par": [2.93177e+01],
                                                                                  "title" : r"\sigma CB^{\pi}_{\Bz\to \Dst\pi}"},
                                                                 "sigmaG"      : {"par": [1.64921e+01],
                                                                                  "title" : r"\sigma G^{\pi}_{\Bz\to \Dst\pi}"},
                                                                 "fracG"       : {"par": [2.58197e-01],
                                                                                  "title" : r"f^{\pi}_{\Bz\to \Dst\pi}"}}
    configdict["pdfList"]["Bd2DstPi"]["Bd2DK"] = {}
    configdict["pdfList"]["Bd2DstPi"]["Bd2DK"]["BeautyMass"] = {"PDF"        : "None"}
    #
    configdict["pdfList"]["Bs2DsPi"] = {}
    configdict["pdfList"]["Bs2DsPi"]["Title"] = "B_{s}#rightarrowD_{s}#pi"
    configdict["pdfList"]["Bs2DsPi"]["Color"] = kCyan
    configdict["pdfList"]["Bs2DsPi"]["Style"] = kDotted
    configdict["pdfList"]["Bs2DsPi"]["Bd2DPi"] = {}
    configdict["pdfList"]["Bs2DsPi"]["Bd2DPi"]["BeautyMass"] = {"PDF"        : "None"}#{"PDF"        : "Ipatia",
                                                                #"shiftMean"  : True,
                                                                #"scaleTails" : False,
                                                                #"mean"       : "Signal_BeautyMass_mean_"+samplemodeyear+"_Bd2DPiHypo",
                                                                #"shift"      : {"par": [5312.13-Pipeak],
                                                                #                "title": r"\Delta\mu^{\pi}_{B_{s}\to D_{s}\pi}"},
                                                                #"sigma"      : {"par": [25.6861],
                                                                #                "title": r"\sigma^{\pi}_{B_{s}\to D_{s}\pi}"},
                                                                #"zeta"       : {"par": [0.0],
                                                                #                "title": r"\zeta\mu^{\pi}_{B_{s}\to D_{s}\pi}"},
                                                                #"fb"         : {"par": [0.0],
                                                                #                "title": r"\beta^{\pi}_{B_{s}\to D_{s}\pi}"},
                                                                #"l"          : {"par": [-9.99936],
                                                                #                "title": r"l^{\pi}_{B_{s}\to D_{s}\pi}"},
                                                                #"a1"         : {"par": [0.888263],
                                                                #                "title": r"a1^{\pi}_{B_{s}\to D_{s}\pi}"},
                                                                #"a2"         : {"par": [3.03441],
                                                                #                "title": r"a2^{\pi}_{B_{s}\to D_{s}\pi}"},
                                                                #"n1"         : {"par": [5.26049],
                                                                #                "title": r"n1^{\pi}_{B_{s}\to D_{s}\pi}"},
                                                                #"n2"         : {"par": [1.22319],
                                                                #                "title": r"n2^{\pi}_{B_{s}\to D_{s}\pi}"}}
    
    configdict["pdfList"]["Bs2DsPi"]["Bd2DK"] = {}
    configdict["pdfList"]["Bs2DsPi"]["Bd2DK"]["BeautyMass"] = {"PDF"        : "None"}
    #
    configdict["pdfList"]["Bd2DKst"] = {}
    configdict["pdfList"]["Bd2DKst"]["Title"] = "B_{d}#rightarrowDK^{*}"
    configdict["pdfList"]["Bd2DKst"]["Color"] = kGreen
    configdict["pdfList"]["Bd2DKst"]["Style"] = kDotted
    configdict["pdfList"]["Bd2DKst"]["Bd2DPi"] = {}
    configdict["pdfList"]["Bd2DKst"]["Bd2DPi"]["BeautyMass"] = {"PDF"       : "None"} 
    configdict["pdfList"]["Bd2DKst"]["Bd2DK"] = {}
    configdict["pdfList"]["Bd2DKst"]["Bd2DK"]["BeautyMass"] = {"PDF"        : "Gaussian",
                                                               "shiftMean"  : False,
                                                               "mean"       : {"par": [5.11244e+03, 4.9e+03, 5.2e+03],
                                                                               "title" : r"\mu^{K}_{\Bz\to D\Kst}"},
                                                               "sigma"      : {"par": [2.50193e+01, 1e+01, 6e+01],
                                                                               "title" : r"\sigma^{K}_{\Bz\to D\Kst}"}}
    #
    configdict["pdfList"]["Comb"] = {}
    configdict["pdfList"]["Comb"]["Title"] = "Combinatorial"
    configdict["pdfList"]["Comb"]["Color"] = kBlue
    configdict["pdfList"]["Comb"]["Style"] = kDotted
    configdict["pdfList"]["Comb"]["Bd2DPi"] = {}
    #configdict["pdfList"]["Comb"]["Bd2DPi"]["BeautyMass"] = { "PDF"          : "ExponentialPlusConstant",
                                                            #  "Title"        : "Combinatorial",
                                                            #  "cB"           : {"par": [-1.72409e-03, -15.0e-03, -1.0e-03],
                                                            #                    "title" : r"c^{\pi}_{\rm comb}"},
                                                            #  "fracExpo"     : {"par": [7.0e-01 ,0.3,1.0],
                                                            #                    "title" : r"f^{\pi}_{\rm comb}"}}
    configdict["pdfList"]["Comb"]["Bd2DPi"]["BeautyMass"] = { "PDF"          : "DoubleExponential",
                                                              "Title"        : "Combinatorial",
                                                              "cB1"          : {"par": [-1.72409e-03, -15.0e-03, -1.0e-03],
                                                                                "title" : r"c1^{\pi}_{\rm comb}"},
                                                              "cB2"          : {"par": [-1.72409e-03, -15.0e-03, -1.0e-03],
                                                                                "title" : r"c2^{\pi}_{\rm comb}"},
                                                              "frac"         : {"par": [7.0e-01,0.01,1.0],
                                                                                "title" : r"f^{\pi}_{\rm comb}"}}
    
    configdict["pdfList"]["Comb"]["Bd2DK"] = {}
    #configdict["pdfList"]["Comb"]["Bd2DK"]["BeautyMass"] = { "PDF"          : "ExponentialPlusConstant",
    #                                                         "Title"        : "Combinatorial",
    #                                                         "cB"           : {"par": [-6.56407e-03, -8.0e-03, -2.0e-03],
    #                                                                           "title" : r"c^{K}_{\rm comb}"},
    #                                                         "fracExpo"     : {"par": [5.42995e-01,0.3,1.0],
    #                                                                           "title" : r"f^{K}_{\rm comb}"}}
    configdict["pdfList"]["Comb"]["Bd2DK"]["BeautyMass"] = { "PDF"          : "DoubleExponential",
                                                             "Title"        : "Combinatorial",
                                                             "cB1"          : {"par": [-1.72409e-03, -15.0e-03, -1.0e-03],
                                                                               "title" : r"c1^{K}_{\rm comb}"},
                                                             "cB2"          : {"par": [-1.72409e-03, -15.0e-03, -1.0e-03],
                                                                               "title" : r"c2^{K}_{\rm comb}"},
                                                             "frac"         : {"par": [7.0e-01 ,0.01,1.0],
                                                                               "title" : r"f^{\pi}_{\rm comb}"}}

    #Axes titles
    configdict["AxisTitle"] = {"BeautyMass": {"Bd2DPi":"D#pi mass [MeV/c^{2}]",
                                              "Bd2DK":"DK mass [MeV/c^{2}]"}}

    #Range
    configdict["Range"] = {"BeautyMass": {"Range": [configdict["BasicVariables"]["BeautyMass"]["Range"][0],
                                                    configdict["BasicVariables"]["BeautyMass"]["Range"][1]],
                                          "Bins": 227}}#455}}

    #Range and sample for sWeights
    configdict["sWeights"] = {"Hypo" : "Bd2DPi",
                              "Range" : {"BeautyMass" : [5220.0, 5600.0] },
                              "Bins"  : 190
                              }

    #Log scale
    configdict["LogScale"] = {"BeautyMass": {"Bd2DPi" : [1e-03, 1e+05], "Bd2DK" : [1e-01, 1e+04] } }

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
    configdict["Yields"] = {"Signal"   : {"Bd2DPi"  : "nSig_"+samplemodeyear+"_Bd2DPiHypo_Evts",
                                          "Bd2DK": "nSig_"+samplemodeyear+"_Bd2DKHypo_Evts"},
                            "Bd2DK"    : {"Bd2DPi"  :
                                          "nBd2DK_"+samplemodeyear+"_Bd2DPiHypo_Evts",
                                          "Bd2DK": "nBd2DK_"+samplemodeyear+"_Bd2DKHypo_Evts"},
                            "Bd2DRho"  : {"Bd2DPi"  : {"par": [9.1417e+04,0,500000],
                                                       "title" : r"N^{\pi}_{\Bz\to D\rho}"},
                                          "Bd2DK": "nBd2DRho_"+samplemodeyear+"_Bd2DKHypo_Evts"},
                            "Bd2DstPi" : {"Bd2DPi"  : {"par": [6.2575e+04,0,500000],
                                                       "title" : r"N^{\pi}_{\Bz\to \Dst\pi}"},
                                          "Bd2DK": {"par": [0],
                                                    "title" : "N^{K}_{\Bz\to \Dst\pi}"}},
                            "Bs2DsPi"  : {"Bd2DPi"  : {"par": [0],
                                                       "title" : r"N^{\pi}_{B_{s}\to D_{s}\pi}"},
                                          "Bd2DK": {"par": [0],
                                                    "title" : r"N^{K}_{B_{s}\to D_{s}\pi}"}},
                            "Bd2DKst"  : {"Bd2DPi"  : {"par": [0],
                                                       "title" : r"N^{\pi}_{\Bz\to D\Kst}"},
                                          "Bd2DK": "nBd2DKst_"+samplemodeyear+"_Bd2DKHypo_Evts"},
                            "Comb"     : {"Bd2DPi"  : {"par": [30000,0,500000],
                                                       "title" : r"N^{\pi}_{\rm comb}"},
                                          "Bd2DK": {"par": [2000,0,100000],
                                                    "title" : r"N^{K}_{\rm comb}"}
                                          }
                            }

    #Gaussian constraints
    configdict["GaussianConstraints"] = {}
    configdict["GaussianConstraints"]["Eff_Bd2DPi_DPi"] = {"Parameters" : ["eff_Bd2DPi_DPi"],
                                                           "Mean"       : [configdict["GlobalVariables"]["eff_Bd2DPi_DPi"]["Range"][0]],
                                                           "Covariance" : [configdict["GlobalVariables"]["eff_Bd2DPi_DPi"]["Error"]]}
    configdict["GaussianConstraints"]["Eff_Bd2DK_DK"] = {"Parameters" : ["eff_Bd2DK_DK"],
                                                         "Mean"       : [configdict["GlobalVariables"]["eff_Bd2DK_DK"]["Range"][0]],
                                                         "Covariance" : [configdict["GlobalVariables"]["eff_Bd2DK_DK"]["Error"]]}
    #configdict["GaussianConstraints"]["nDRho_to_DKst_KHypo"] = {"Parameters" : ["DRho_to_DKst_KHypo"],
    #                                                            "Mean"       : [configdict["GlobalVariables"]["DRho_to_DKst_KHypo"]["Range"][0]],
    #                                                            "Covariance" : [configdict["GlobalVariables"]["DRho_to_DKst_KHypo"]["Error"]]}

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
    configdict["plotsWeights"] = {"BeautyTime" : "#tau(B_{d}#rightarrow D#pi) (ps)",
                                  "CharmMass"  : "K#pi#pi mass (MeV/c^{2})"
                                  }
    
    return configdict
