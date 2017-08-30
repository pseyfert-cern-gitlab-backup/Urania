def getconfig():

    configdict = {}

    configdict["Inputs"] = {}
    configdict["Inputs"] = {
        #"BuCalibRLOGIT":
        #{"XML": "/afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bu2D0Pi_rlogitLink_NoProdAsymm/OS_Combination_Calibration.xml"},
        #"BdCalibBubasisRLOGIT":
        #{"XML": "/afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bd2DPi_rlogitLink_NoProdAsymm_useBubasis/OS_Combination_Calibration.xml"},
        #"BdLinearCalibBubasis":
        #{"XML": "/afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bd2DPi_rlogitLink_NoProdAsymm_applyBuCalib/linearCalib_useBubasis/OS_Combination_Calibration.xml"},
        "BuLinearSelfCalib":
        {"XML": "/afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bu2D0Pi_rlogitLink_NoProdAsymm_selfCalib/linearCalib/OS_Combination_Calibration.xml"},
        "BdLinearSelfCalibBubasis":
        {"XML": "/afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bd2DPi_rlogitLink_NoProdAsymm_selfCalib/linearCalib_useBubasis/OS_Combination_Calibration.xml"},        
        #"StraightLine":
        #{"Values": [0.0, 0.0],
        # "Errors": None,
        # "Correlation": None
        # }
        }

    configdict["Parameters"] = {}
    #configdict["Parameters"] = [r"p_0", r"p_1", r"p_2", r"p_3", r"p_4", r"\Delta p_0", r"\Delta p_1", r"\Delta p_2", r"\Delta p_3", r"\Delta p_4"]
    configdict["Parameters"] = [r"p_0", r"p_1", r"\Delta p_0", r"\Delta p_1"]
    
    #Temporary workaround
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5090,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_FitDaughtersConst_M_flat"}

    return configdict
