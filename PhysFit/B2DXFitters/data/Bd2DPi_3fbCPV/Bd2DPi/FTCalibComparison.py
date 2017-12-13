def getconfig():

    configdict = {}

    configdict["Inputs"] = {}
    configdict["Inputs"] = {
        "BuCalibRLOGITbroadTrigWeightNo4body":
        {"XML": "/eos/lhcb/wg/b2oc/TD_DPi_3fb/calibrations/RLogisticCalibration_Bd2JpsiKst_SS_20171101.xml"},
        "BdDataFitFloatFT":
        {"FileName" : "/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/SSbarAccAsymmFTFloatingDMGammaConstrAllSamplesBlinded_SSrlogit/workResults.root",
         "FitResult" : "fitresult_time_signal_TimePdf_dataSet_time_weighted",
         "Workspace" : "workspace",
         "Parameters" : ["p_0_RLogisticCalibration_Bd2JpsiKst_SS_20171101",
                         "p_1_RLogisticCalibration_Bd2JpsiKst_SS_20171101",
                         "dp_0_RLogisticCalibration_Bd2JpsiKst_SS_20171101",
                         "dp_1_RLogisticCalibration_Bd2JpsiKst_SS_20171101"],
         "Positions" : [22,24,15,17]
         }
        }
    #configdict["Inputs"] = {
    #    "BuCalibRLOGITbroadTrigWeightNo4body":
    #    {"XML": "/eos/lhcb/wg/b2oc/TD_DPi_3fb/calibrations/RLogisticCalibration_Bu2D0Pi_OS_20171109.xml"},
    #    "BdDataFitFloatFT":
    #    {"FileName" : "/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/SSbarAccAsymmFTFloatingDMGammaConstrAllSamplesBlinded_SSrlogit/workResults.root",
    #     "FitResult" : "fitresult_time_signal_TimePdf_dataSet_time_weighted",
    #     "Workspace" : "workspace",
    #     "Parameters" : ["p_0_RLogisticCalibration_Bu2D0Pi_OS_20171109",
    #                     "p_1_RLogisticCalibration_Bu2D0Pi_OS_20171109",
    #                     "p_2_RLogisticCalibration_Bu2D0Pi_OS_20171109",
    #                     "p_3_RLogisticCalibration_Bu2D0Pi_OS_20171109",
    #                     "p_4_RLogisticCalibration_Bu2D0Pi_OS_20171109",
    #                     "dp_0_RLogisticCalibration_Bu2D0Pi_OS_20171109",
    #                     "dp_1_RLogisticCalibration_Bu2D0Pi_OS_20171109",
    #                     "dp_2_RLogisticCalibration_Bu2D0Pi_OS_20171109",
    #                     "dp_3_RLogisticCalibration_Bu2D0Pi_OS_20171109",
    #                     "dp_4_RLogisticCalibration_Bu2D0Pi_OS_20171109"],
    #     "Positions" : [23,25,26,27,28,16,18,19,20,21]
    #     }
        #"BuCalibRLOGITbroadTrigWeightNo4body":
        #{"XML": "/afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bu2D0Pi_rlogitLink_NoProdAsymm_broadTrigBDTAUWeight/OS_Combination_Calibration.xml"},
        #"BdCalibNo4bodyBubasisRLOGITbroadTrigWeight":
        #{"XML": "/afs/cern.ch/user/v/vibattis/gitdev/Bd2Dpi_selection/flavourtagging/EspressoCalibration/OSCalibMC/Bd2DPi_rlogitLink_NoProdAsymm_useBubasis_broadTrigBDTAUWeight/OS_Combination_Calibration.xml"},
    #    }

    configdict["Parameters"] = {}
    configdict["Parameters"] = [r"p_0", r"p_1", r"p_2", r"p_3", r"p_4", r"\Delta p_0", r"\Delta p_1", r"\Delta p_2", r"\Delta p_3", r"\Delta p_4"]
    
    #Temporary workaround
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5090,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_FitDaughtersConst_M_flat"}

    return configdict
