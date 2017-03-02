def getconfig() :

    configdict = {}

    configdict["Time"] = { "Name": "obsTime",
                           "Range": [0.4, 15.0]
                           }

    # "Observables" has to contain the variables used in the "preselection" string, if any! 
    configdict["Observables"] = { "lab0_BKGCAT" : {"Range": [-10.0, 10.0] },
                                  "TagDecOS": {"Range": [-1.0, 1.0] },
                                  "obsTagSS_PionInvBoost_ProtonInvBoost": {"Range": [-1.0, 1.0] },
                                  "lab0_Hlt2Topo2BodyBBDTDecision_TOS" : {"Range": [0.0, 1.0] },
                                  "lab0_Hlt2Topo3BodyBBDTDecision_TOS" : {"Range": [0.0, 1.0] },
                                  "lab0_Hlt2Topo4BodyBBDTDecision_TOS" : {"Range": [0.0, 1.0] } }

    configdict["Weight"] = "TMath::Exp(obsTime/1.519068)"

    #Knots from DsK
    configdict["Acceptance"] = {"Knots": [ 0.5, 1.0, 1.5, 2.0, 3.0, 12.0 ],
                                "Coefficients": [0.3889, 0.5754, 0.8515, 1.0649, 1.2373, 1.4149]}

    #New knots
    #configdict["Acceptance"] = {"Knots": [ 0.5, 1.0, 1.5, 2.0, 3.0, 4.0, 6.5, 12.0 ],
    #                            "Coefficients" : [0.3889, 0.5754, 0.8515, 1.0649, 1.2373, 1.3, 1.35, 1.4149] }

    configdict["LHCbText"] = { "X": 0.75, "Y": 0.45}

    configdict["Chi2Text"] = { "X": 0.35, "Y": 0.37}

    return configdict
