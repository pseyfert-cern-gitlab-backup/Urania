def getconfig():

    configdict = {}

    configdict["Inputs"] = {}
    configdict["Inputs"] = {
        "BuCalibRLOGITbroadTrigWeightNo4body":
        {"XML": "/afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bu2D0Pi_rlogitLink_NoProdAsymm_broadTrigBDTAUWeight/OS_Combination_Calibration.xml"},
        "BdCalibNo4bodyBubasisRLOGITbroadTrigWeight":
        {"XML": "/afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bd2DPi_rlogitLink_NoProdAsymm_useBubasis_broadTrigBDTAUWeight/OS_Combination_Calibration.xml"},
        }

    configdict["Parameters"] = {}
    configdict["Parameters"] = [r"p_0", r"p_1", r"p_2", r"p_3", r"p_4", r"\Delta p_0", r"\Delta p_1", r"\Delta p_2", r"\Delta p_3", r"\Delta p_4"]
    
    #Temporary workaround
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5090,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_FitDaughtersConst_M_flat"}

    return configdict
