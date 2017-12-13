def getconfig():

    configdict = {}

    configdict["Inputs"] = {}
    configdict["Inputs"] = {
        "FloatFT":
        {"FileName" : "/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/SSbarAccAsymmFTFloatingDMGammaConstrAllSamplesBlinded_SSrlogit/workResults.root",
         "FitResult" : "fitresult_time_signal_TimePdf_dataSet_time_weighted",
         "Workspace" : "workspace",
         "Parameters" : ["Acceptance_SplineAccCoeff"+str(i) for i in range(0,9)],
         "Positions" : range(0,9)
         },
        "ConstrFT":
        {"FileName" : "/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/SSbarAccAsymmFloatingDMGammaFTConstrAllSamplesBlinded_SSrlogit/workResults.root",
         "FitResult" : "fitresult_time_signal_TimePdf_dataSet_time_weighted",
         "Workspace" : "workspace",
         "Parameters" : ["Acceptance_SplineAccCoeff"+str(i) for i in range(0,9)],
         "Positions" : range(0,9)
         }
        }
    
    configdict["Parameters"] = {}
    configdict["Parameters"] = [r"v_{"+str(i)+"}" for i in range(1,10)]
    
    #Temporary workaround
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5090,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_FitDaughtersConst_M_flat"}

    return configdict
