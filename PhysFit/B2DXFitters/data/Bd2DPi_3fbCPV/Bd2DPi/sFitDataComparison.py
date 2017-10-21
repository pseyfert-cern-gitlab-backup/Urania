def getconfig():

    configdict = {}

    dir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/"
    configdict["Inputs"] = {}
    configdict["Inputs"] = {
        "OSExlusive": { "FileName"    : dir+"SSbarAccAsymmFloatingDMGammaConstrOSExclusiveBlinded_Nov2016/workResults.root",
                        "Workspace"   : "workspace",
                        "FitResult"   : "fitresult_time_signal_TimePdf_dataSet_time_weighted"},
        "SSExlusive": { "FileName"    : dir+"SSbarAccAsymmFloatingDMGammaConstrSSExclusiveBlinded_Nov2016/workResults.root",
                        "Workspace"   : "workspace",
                        "FitResult"   : "fitresult_time_signal_TimePdf_dataSet_time_weighted"},
        "SSOSOverlap": { "FileName"   : dir+"SSbarAccAsymmFloatingDMGammaConstrSSOSOverlapBlinded_Nov2016/workResults.root",
                         "Workspace"  : "workspace",
                         "FitResult"  : "fitresult_time_signal_TimePdf_dataSet_time_weighted"}
        }
    
    #Temporary workaround
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5090,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_FitDaughtersConst_M_flat"}

    return configdict
