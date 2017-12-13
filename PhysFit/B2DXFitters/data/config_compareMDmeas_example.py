def getconfig():

    configdict = {}

    configdict["Inputs"] = {}
    configdict["Inputs"] = {
        "Fitted":
        {
        "Values":      [0.32, 0.34, 0.57],
        "Errors":      [0.03, 0.04, 0.05],
        "Correlation": [ [1, 0.015, -0.003],
                         [1, 0.04],
                         [1] ]
        },
        "Generated":
        {
        "Values":      [0.3, 0.4, 0.5],
        "Errors":      [0.01, 0.01, 0.01],
        "Correlation": [ [1, 0.01, 0.01],
                         [1, 0.01],
                         [1] ]
        }
        }
    
    configdict["Parameters"] = {}
    configdict["Parameters"] = ["A", "B", "C"]
    
    #Temporary workaround (leave as it is, not important)
    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyMass"]    = { "Range"                  : [5090,    6000    ],
                                                      "Name"                   : "BeautyMass",
                                                      "InputName"              : "lab0_FitDaughtersConst_M_flat"}

    return configdict
