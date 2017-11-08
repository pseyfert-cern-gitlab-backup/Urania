from ROOT import *

def getconfig() :

    configdict = {}
    
    from math import pi
    from math import log

    import ROOT
    from ROOT import *

    happystar = "#lower[-0.65]{#scale[0.6]{*}}"

    configdict["Decay"] = "Bd2DPi"
        
    # basic variables
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5000,    6000    ],
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
                                                      "InputName"              : "lab1_PIDKcorr"}

    configdict["BasicVariables"]["nTracks"]       = { "Range"                  : [15.0,    1000.0  ],
                                                      "Name"                   : "nTracks",
                                                      "InputName"              : "nTracks"}

    configdict["BasicVariables"]["BeautyTimeErr"] = { "Range"                  : [0.01,    0.1     ],
                                                      "Name"                   : "BeautyTimeErr",
                                                      "InputName"              : "lab0_FitDaughtersPVConst_ctauErr_flat"}

    configdict["BasicVariables"]["BacCharge"]     = { "Range"                  : [-1000.0, 1000.0  ],
                                                      "Name"                   : "BacCharge",
                                                      "InputName"              : "lab1_ID"}

    configdict["BasicVariables"]["BDTG"]           = { "Range"                  : [0.0, 1],
                                                       "Name"                   : "BDTG",
                                                       "InputName"              : "BDT_classifier"}
    
    
    # children prefixes used in MCID, MCTRUEID, BKGCAT cuts   
    # order of particles: KPiPi 
    configdict["DsChildrenPrefix"] = {"Child1":"lab3","Child2":"lab4","Child3": "lab5"}
    
    configdict["constParams"] = []

    #PDF for each fitted component
    #Structure: decay->hypo->observable
    configdict["pdfList"] = {}
    #
    configdict["pdfList"]["Signal"] = {}
    configdict["pdfList"]["Signal"]["Bd2DPi"] = {}
    #configdict["pdfList"]["Signal"]["Bd2DPi"]["BeautyMass"] = { "PDF"        : "Ipatia",
    #                                                            "Title"      : "B_{d}#rightarrowD#pi",
    #                                                            "Bins"       : 175,
    #                                                            "Min"        : 5150.0,
    #                                                            "Max"        : 5500.0,
    #                                                            "Unit"       : "MeV/c^{2}",
    #                                                            "mean"       : [5280,5200,5350],
    #                                                            "sigma"      : [25.0,1.0,100.0],
    #                                                            "zeta"       : [0.0],
    #                                                            "fb"         : [0.0],
    #                                                            "l"          : [-2.0,-5.0,-0.01],
    #                                                            "a1"         : [3.0,0.01,6.0],
    #                                                            "a2"         : [3.0,0.01,6.0],
    #                                                            "n1"         : [3.0,0.01,6.0],
    #                                                            "n2"         : [3.0,0.01,6.0]}
    configdict["pdfList"]["Signal"]["Bd2DPi"]["BeautyMass"] = { "PDF"        : "IpatiaPlusJohnsonSU",
                                                                "Title"      : "B_{d}#rightarrowD#pi",
                                                                "Bins"       : 125,
                                                                "Min"        : 5150.0,
                                                                "Max"        : 5500.0,
                                                                "Unit"       : "MeV/c^{2}",
                                                                "mean"       : [5280,5200,5350],
                                                                "sigmaI"     : [25.0, 1.0,100.0],
                                                                "sigmaJ"     : [25.0, 1.0, 100.0],
                                                                "zeta"       : [0.0],
                                                                "fb"         : [0.0],
                                                                "l"          : [-2.0,-5.0,-0.0],
                                                                "a1"         : [3.0,0.01,6.0],
                                                                "a2"         : [3.0,0.01,6.0],
                                                                "n1"         : [3.0,0.01,6.0],
                                                                "n2"         : [3.0,0.01,6.0],
                                                                "nu"         : [1.0,-30.0,30.0],
                                                                "tau"        : [1.0,-30.0,30.0],
                                                                "fracI"      : [0.7, 0.1, 0.9]}
    
    configdict["pdfList"]["Signal"]["Bd2DK"] = {}
    configdict["pdfList"]["Signal"]["Bd2DK"]["BeautyMass"] = { "PDF"        : "Ipatia",
                                                               "Title"      : "B_{d}#rightarrowD#pi",
                                                               "Bins"       : 100,
                                                               "Min"        : 5200.0,
                                                               "Max"        : 5600.0,
                                                               "Unit"       : "MeV/c^{2}",
                                                               "mean"       : [5388.7,5300.0,5400.0],
                                                               "sigma"      : [100.0,10.0,500.0],
                                                               "zeta"       : [0.0],
                                                               "fb"         : [0.0],
                                                               "l"          : [-2.0,-7.0,-0.01],
                                                               "a1"         : [3.0,0.01,6.0],
                                                               "a2"         : [3.0,0.01,6.0],
                                                               "n1"         : [3.0,0.01,6.0],
                                                               "n2"         : [3.0,0.01,6.0]}
    #
    configdict["pdfList"]["Bd2DK"] = {}
    configdict["pdfList"]["Bd2DK"]["Bd2DPi"] = {}
    configdict["pdfList"]["Bd2DK"]["Bd2DPi"]["BeautyMass"] = { "PDF"        : "Ipatia",
                                                               "Title"      : "B_{d}#rightarrowDK",
                                                               "Bins"       : 82,
                                                               "Min"        : 5090.0,
                                                               "Max"        : 5500.0,
                                                               "Unit"       : "MeV/c^{2}",
                                                               "mean"       : [5239.0,5200.0,5250.0],
                                                               "sigma"      : [26.3,10.0,50.0],
                                                               "zeta"       : [0.0],
                                                               "fb"         : [0.0],
                                                               "l"          : [-28.0,-35.0,-25.0],
                                                               "a1"         : [0.96,0.01,5.0],
                                                               "a2"         : [1.23,0.01,5.0],
                                                               "n1"         : [3.5,0.01,15.0],
                                                               "n2"         : [10.0,0.01,15.0]}
    configdict["pdfList"]["Bd2DK"]["Bd2DK"] = {}
    configdict["pdfList"]["Bd2DK"]["Bd2DK"]["BeautyMass"] = { "PDF"        : "Ipatia",
                                                              "Title"      : "B_{d}#rightarrowDK",
                                                              "Bins"       : 80,
                                                              "Min"        : 5100.0,#5200.0,
                                                              "Max"        : 5500.0,#5380.0,
                                                              "Unit"       : "MeV/c^{2}",
                                                              "mean"       : [5280.0,5200.0,5350.0],
                                                              "sigma"      : [17.0,5.0,50.0],
                                                              "zeta"       : [0.0],
                                                              "fb"         : [0.0],
                                                              "l"          : [-3.6,-15.0,-0.01],
                                                              "a1"         : [2.6,1.0,10.0],
                                                              "a2"         : [1e+09],
                                                              "n1"         : [0.95,0.001,15.0],
                                                              "n2"         : [0.0]}
    #
    configdict["pdfList"]["Bd2DRho"] = {}
    configdict["pdfList"]["Bd2DRho"]["Bd2DPi"] = {}
    configdict["pdfList"]["Bd2DRho"]["Bd2DPi"]["BeautyMass"] = {"PDF"        : "JohnsonSU",
                                                                "Title"      : "B_{d}#rightarrowD#rho",
                                                                "Bins"       : 100,
                                                                "Min"        : 5090.0,
                                                                "Max"        : 5250.0,
                                                                "Unit"       : "MeV/c^{2}",
                                                                "mean"       : [4.89304e+03,4700.0,4910.0],
                                                                "sigma"      : [600, 400.0, 1000.0],
                                                                "nu"         : [-1.9084e+00, -2.8, -1.3],
                                                                "tau"        : [1.3406e+00, 0.7, 1.8]}
    configdict["pdfList"]["Bd2DRho"]["Bd2DK"] = {}
    configdict["pdfList"]["Bd2DRho"]["Bd2DK"]["BeautyMass"] = {"PDF"        : "DoubleGaussian",
                                                               "Title"      : "B_{d}#rightarrowD#rho",
                                                               "Bins"       : 30,
                                                               "Min"        : 5080.0,
                                                               "Max"        : 5450.0,
                                                               "Unit"       : "MeV/c^{2}",
                                                               "sameMean"   : False,
                                                               "mean"       : [5100.0,5000.0,5500.0],
                                                               "sigma1"     : [1.1754e+02, 90.0, 140.0],
                                                               "sigma2"     : [2.73259e+02, 10.0, 400.0],
                                                               "frac"       : [0.690345, 0.1, 0.99]}
    #
    configdict["pdfList"]["Bd2DstPi"] = {}
    configdict["pdfList"]["Bd2DstPi"]["Bd2DPi"] = {}
    configdict["pdfList"]["Bd2DstPi"]["Bd2DPi"]["BeautyMass"] = {"PDF"        : "CrystalBallPlusGaussian",
                                                                 "Title"      : "B_{d}#rightarrowD"+happystar+"#pi",
                                                                 "Bins"       : 100,
                                                                 "Min"        : 5090.0,
                                                                 "Max"        : 6000.0,
                                                                 "Unit"       : "MeV/c^{2}",
                                                                 "shiftMean"  : False,
                                                                 "mean"       : [5100.92,5000.0,5200.0],
                                                                 "alpha"      : [-2.181,-10.0,10.0],
                                                                 "n"          : [1.08,0.0,10.0],
                                                                 "sigmaCB"    : [26.59,1.0,100.0],
                                                                 "sigmaG"     : [25.0,1.0,100.0],
                                                                 "fracG"      : [0.5,0.1,0.9]}
    configdict["pdfList"]["Bd2DstPi"]["Bd2DK"] = {}
    configdict["pdfList"]["Bd2DstPi"]["Bd2DK"]["BeautyMass"] = {"PDF"        : "DoubleGaussian",
                                                                "Title"      : "B_{d}#rightarrowD"+happystar+"#pi",
                                                                "Bins"       : 100,#50,
                                                                "Min"        : 5090.0,#5100.0,
                                                                "Max"        : 5600.0,#5350.0,
                                                                "Unit"       : "MeV/c^{2}",
                                                                "sameMean"   : False,
                                                                "mean"       : [5150,4900.0,5500.0],
                                                                "sigma1"     : [26.59,1.0,100.0],
                                                                "sigma2"     : [26.59,1.0,500.0], 
                                                                "frac"       : [0.5,0.1,0.9]}
    #
    configdict["pdfList"]["Bd2DKst"] = {}
    configdict["pdfList"]["Bd2DKst"]["Bd2DPi"] = {}
    configdict["pdfList"]["Bd2DKst"]["Bd2DPi"]["BeautyMass"] = {"PDF"        : "Gaussian",
                                                                "Title"      : "B_{d}#rightarrowDK"+happystar,
                                                                "Bins"       : 50,#20,
                                                                "Min"        : 5000.0,
                                                                "Max"        : 5600.0,#5200.0,
                                                                "Unit"       : "MeV/c^{2}",
                                                                "shiftMean"  : False,
                                                                "mean"       : [5100.92,4000.0,5200.0],
                                                                "sigma"      : [26.59,1.0,100.0]}
    configdict["pdfList"]["Bd2DKst"]["Bd2DK"] = {}
    configdict["pdfList"]["Bd2DKst"]["Bd2DK"]["BeautyMass"] = {"PDF"        : "Gaussian",
                                                               "Title"      : "B_{d}#rightarrowDK"+happystar,
                                                               "Bins"       : 20,
                                                               "Min"        : 5090.0,
                                                               "Max"        : 5250.0,
                                                               "Unit"       : "MeV/c^{2}",
                                                               "shiftMean"  : False,
                                                               "mean"       : [5150,4900.0,5500.0],
                                                               "sigma"      : [26.59,1.0,100.0]}
    #
    configdict["pdfList"]["Bs2DsPi"] = {}
    configdict["pdfList"]["Bs2DsPi"]["Bd2DPi"] = {}
    configdict["pdfList"]["Bs2DsPi"]["Bd2DPi"]["BeautyMass"] = { "PDF"        : "Ipatia",
                                                                 "Title"      : "B_{s}#rightarrowD_{s}#pi",
                                                                 "Bins"       : 100,#50,
                                                                 "Min"        : 5090.0,#5150.0,
                                                                 "Max"        : 5600.0,#5450.0,
                                                                 "Unit"       : "MeV/c^{2}",
                                                                 "mean"       : [5310.0,5200.0,5400.0],
                                                                 "sigma"      : [30.0,1.0,100.0],
                                                                 "zeta"       : [0.01,0.0,0.1],
                                                                 "fb"         : [0.0],
                                                                 "l"          : [-2.0,-10.0,-0.01],
                                                                 "a1"         : [3.0,0.01,10.0],
                                                                 "a2"         : [3.0,0.01,10.0],
                                                                 "n1"         : [3.0,0.01,10.0],
                                                                 "n2"         : [3.0,0.01,10.0]}
    configdict["pdfList"]["Bs2DsPi"]["Bd2DK"] = {}
    configdict["pdfList"]["Bs2DsPi"]["Bd2DK"]["BeautyMass"] = { "PDF"        : "Ipatia",
                                                                "Title"      : "B_{s}#rightarrowD_{s}#pi",
                                                                "Bins"       : 50,#25,
                                                                "Min"        : 5090.0,#5150.0,
                                                                "Max"        : 5600.0,#5700.0,
                                                                "Unit"       : "MeV/c^{2}",
                                                                "mean"       : [5350.0,5000.0,6000.0],
                                                                "sigma"      : [125.0,1.0,1000.0],
                                                                "zeta"       : [0.0],
                                                                "fb"         : [0.0],
                                                                "l"          : [-2.0,-10.0,-0.01],
                                                                "a1"         : [3.0,0.01,10.0],
                                                                "a2"         : [3.0,0.01,10.0],
                                                                "n1"         : [3.0,0.01,10.0],
                                                                "n2"         : [3.0,0.01,10.0]}
    #
    configdict["pdfList"]["Comb"] = {}
    configdict["pdfList"]["Comb"]["Bd2DPi"] = {}
    configdict["pdfList"]["Comb"]["Bd2DPi"]["BeautyMass"] = { "PDF"          : "ExponentialPlusConstant",
                                                              "Title"        : "Combinatorial",
                                                              "Bins"         : 50,
                                                              "Min"          : 5600.0,
                                                              "Max"          : 6000.0,
                                                              "Unit"         : "MeV/c^{2}",
                                                              "cB"           : [-2.5e-03, -5.0, -1e-06],
                                                              "fracExpo"     : [0.8,0.01,0.99]}
    configdict["pdfList"]["Comb"]["Bd2DK"] = {}
    configdict["pdfList"]["Comb"]["Bd2DK"]["BeautyMass"] = { "PDF"          : "ExponentialPlusConstant",
                                                             "Title"        : "Combinatorial",
                                                             "Bins"         : 50,
                                                             "Min"          : 5600.0,
                                                             "Max"          : 6000.0,
                                                             "Unit"         : "MeV/c^{2}",
                                                             "cB"           : [-2.5e-03, -5.0, -1e-06],
                                                             "fracExpo"     : [0.8,0.01,0.99]}

    #Dataset prefix
    configdict["dataSetPrefix"] = {"Signal"   : "dataSetMC_Bd2DPi_",
                                   "Bd2DK"    : "dataSetMC_Bd2DK_",
                                   "Bd2DRho"  : "dataSetMC_Bd2DRho_",
                                   "Bd2DstPi" : "dataSetMC_Bd2DstPi_",
                                   "Bd2DKst"  : "dataSetMC_Bd2DKst_",
                                   "Bs2DsPi"  : "dataSetMC_Bs2DsPi_",
                                   "Comb"     : "dataSetCombPi_"}
    #Axes titles
    configdict["AxisTitle"] = {"BeautyMass": {"Bd2DPi":"D#pi mass (MeV/c^{2})","Bd2DK":"DK mass (MeV/c^{2})"}}
    
    return configdict
