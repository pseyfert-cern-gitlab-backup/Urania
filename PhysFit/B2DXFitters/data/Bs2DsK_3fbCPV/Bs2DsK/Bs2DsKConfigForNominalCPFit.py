def getconfig() :

    from Bs2DsKConfigForNominalMassFit import getconfig as getconfig_nominal
    configdict = getconfig_nominal()

    from math import pi

    # PHYSICAL PARAMETERS
    configdict["Gammas"]        =  0.6643   # in ps^{-1}                                                                            
    configdict["DeltaGammas"]   =  0.083
    configdict["DeltaMs"]       = 17.757   # in ps^{-1}                                                                                                       
    configdict["StrongPhase"]   = 20. / 180. * pi
    configdict["WeakPhase"]     = 70./180.*pi
    configdict["ModLf"]         = 0.372
    configdict["CPlimit"]       = {"upper":4.0, "lower":-4.0}
    #configdict["BachelorHypo"] = "Bs2DsK"

    configdict["Asymmetries"] = {"Detection":1.0/100.0,
                                 "Production":1.1/100.0}

    configdict["ConstrainsForTaggingCalib"] = True

    configdict["UsedResolution"] = "Nominal"

    if configdict["UsedResolution"] == "Nominal":
        configdict["Resolution"] = { "scaleFactor":{"p0":0.010262, "p1":1.280, "p2":0.0},
                                     "meanBias":0.0,
                                     "shape": { "sigma1":2.14946e-02, "sigma2":3.67643e-02, "sigma3":6.32869e-02,
                                                "frac1":3.72147e-01, "frac2":5.65150e-01},
                                     "templates": { "fileName":"../data/workspace/MDFitter/template_Data_Terr_Bs2DsPi_BDTGA.root",
                                                    "workName":"workspace",
                                                    "templateName":"TimeErrorPdf_Bs2DsK"} }
#new nominal tagging with tag flip class AND asymmetries (paper)
        configdict["TaggingCalibration"]["OS"] = {"p0": 0.37400, "dp0": 1.3833e-02, "p1": 1.0941, "dp1": 1.2581e-01,
                                                  "cov": [ [3.715e-05, -6.122e-07, 7.059e-06, 1.01e-06],
                                                           [-6.122e-07, 3.505e-05, 3.037e-06, -2.222e-05],
                                                           [7.059e-06, 3.037e-06, 0.004018, -6.486e-05],
                                                           [1.01e-06, -2.222e-05, -6.486e-05, 0.003787]],
                                                  "average": 0.36980, "tagEff":0.37146, "aTagEff":-1.1380e-02, "use":True}
        configdict["TaggingCalibration"]["SS"] = {"p0": 0.44141, "dp0": -1.7967e-02, "p1": 1.0837, "dp1": 1.3408e-01,
                                                  "cov": [ [2.167e-05, 5.119e-07, 1.708e-05, 4.157e-06],
                                                           [5.119e-07, 1.858e-05, 4.93e-06, -2.372e-06],
                                                           [1.708e-05, 4.93e-06, 0.004593, 1.507e-05],
                                                           [4.157e-06, -2.372e-06, 1.507e-05, 0.004531]],
                                                  "average": 0.43744, "tagEff":0.63900, "aTagEff":8.1941e-03, "use":True}


#new nominal tagging with tag flip class (paper)
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.37501, "dp0": 0.0, "p1": 1.0982, "dp1": 0.0,
#                                                  "cov": [ [3.728e-05, 0.0, 6.656e-06, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [0.0002286, 0.0, 0.00404, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.369798, "tagEff":0.37153, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.44137, "dp0": 0.0, "p1": 1.0856, "dp1": 0.0,
#                                                  "cov": [ [2.186e-05, 0.0, 1.777e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [1.777e-05, 0.0, 0.004624, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.43744, "tagEff":0.63916, "aTagEff":0.0, "use":True}



#tagging conf note
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.37718, "dp0": 0.0, "p1": 1.1244, "dp1": 0.0,
#                                                  "cov": [ [5.212e-05, 0.0, 0.0002286, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [0.0002286, 0.0, 0.006685, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.369798, "tagEff":0.37151, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.44119, "dp0": 0.0, "p1": 1.0868, "dp1": 0.0,
#                                                  "cov": [ [2.903e-05, 0.0, 0.0001613, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [0.0001613, 0.0, 0.006101, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.43744, "tagEff":0.63926, "aTagEff":0.0, "use":True}
#non-zero dp0 dp1
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.37718, "dp0": 0.014, "p1": 1.1244, "dp1": 0.066,
#                                                  "cov": [ [5.212e-05, 0.0, 0.0002286, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [0.0002286, 0.0, 0.006685, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.369798, "tagEff":0.37151, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.44119, "dp0":-0.0163, "p1": 1.0868, "dp1": -0.031,
#                                                  "cov": [ [2.903e-05, 0.0, 0.0001613, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [0.0001613, 0.0, 0.006101, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.43744, "tagEff":0.63926, "aTagEff":0.0, "use":True}
# for running with constrained dp0 dp1
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.37718, "dp0": 0.014, "p1": 1.1244, "dp1": 0.066,
#                                                  "cov": [ [5.212e-05, 0.0, 0.0002286, 0.0],
#                                                           [0.0, 1.44e-6, 0.0, 7.488e-6],
#                                                           [0.0002286, 0.0, 0.006685, 0.0],
#                                                           [0.0, 7.488e-6, 0.0, 1.44e-4]],
#                                                  "average": 0.369798, "tagEff":0.37151, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.44119, "dp0":-0.0163, "p1": 1.0868, "dp1": -0.031,
#                                                  "cov": [ [2.903e-05, 0.0, 0.0001613, 0.0],
#                                                           [0.0, 1.369e-05, 0.0, 1.03896e-4],
#                                                           [0.0001613, 0.0, 0.006101, 0.0],
#                                                           [0.0, 1.03896e-4, 0.0, 2.704e-3]],
#                                                  "average": 0.43744, "tagEff":0.63926, "aTagEff":0.0, "use":True}




    if configdict["UsedResolution"] == "SingleGaussian":
    # Single Gaussian Resolution and corresponding Tagging Parameter                                                                                                                              
        configdict["Resolution"] = { "scaleFactor":{"p0":0.0, "p1":1.772, 
                                                    "p2":0.0},
                                     "meanBias":0.0,
                                     "shape": { "sigma1":2.14946e-02, "sigma2":3.67643e-02, "sigma3":6.32869e-02,
                                                "frac1":3.72147e-01, "frac2":5.65150e-01},
                                     "templates": { "fileName":"../data/workspace/MDFitter/template_Data_Terr_Bs2DsPi_BDTGA.root",
                                                    "workName":"workspace",
                                                    "templateName":"TimeErrorPdf_Bs2DsPi"} }
        configdict["TaggingCalibration"]["OS"] = {"p0": 0.36446, "dp0": 1.4134e-02, "p1": 1.1648, "dp1": 1.2440e-01,
                                                  "cov": [ [4.277e-05, -6.898e-07, 6.848e-06, 3.891e-07],
                                                           [-6.898e-07, 3.665e-05, 2.941e-06, -3.579e-05],
                                                           [6.848e-06, 2.941e-06, 0.004535, -6.633e-05],
                                                           [3.891e-07, -3.579e-05, -6.633e-05, 0.003904]],
                                                  "average": 0.36980, "tagEff":0.37146, "aTagEff":-1.2152e-02, "use":True}
        configdict["TaggingCalibration"]["SS"] = {"p0": 0.43752, "dp0": -1.8207e-02, "p1": 1.1325, "dp1": 1.3732e-01,
                                                  "cov": [ [2.496e-05, 6.523e-07, 2.592e-05, 5.272e-06],
                                                           [6.523e-07, 1.869e-05, 5.828e-06, -3.81e-06],
                                                           [2.592e-05, 5.828e-06, 0.004951, -1.833e-05],
                                                           [5.272e-06, -3.81e-06, -1.833e-05, 0.00455]],
                                                  "average": 0.43744, "tagEff":0.63899, "aTagEff":9.0887e-03, "use":True}


    if configdict["UsedResolution"] == "SecondApproach":
    # Resolution for second approach to check systematics and corresponding Tagging Parameter                                                                                                      
        configdict["Resolution"] = { "scaleFactor":{"p0":-0.000568, "p1":1.243, "p2":0.0},
                                     "meanBias":0.0,
                                     "shape": { "sigma1":2.14946e-02, "sigma2":3.67643e-02, "sigma3":6.32869e-02,
                                                "frac1":3.72147e-01, "frac2":5.65150e-01},
                                     "templates": { "fileName":"../data/workspace/MDFitter/template_Data_Terr_Bs2DsPi_BDTGA.root",
                                                    "workName":"workspace",
                                                    "templateName":"TimeErrorPdf_Bs2DsPi"} }
        configdict["TaggingCalibration"]["OS"] = {"p0": 0.39301, "dp0": 1.3292e-02, "p1": 0.93361, "dp1": 1.3032e-01,
                                                  "cov": [ [2.708e-05, -4.288e-07, 6.1e-06, 1.316e-06],
                                                           [-4.288e-07, 3.294e-05, 2.473e-06, -3.893e-06],
                                                           [6.1e-06, 2.473e-06, 0.003022, -4.517e-05],
                                                           [1.316e-06, -3.893e-06, -4.517e-05, 0.003625]],
                                                  "average": 0.36980, "tagEff":0.37144, "aTagEff":-9.7373e-03, "use":True}
        configdict["TaggingCalibration"]["SS"] = {"p0": 0.44998, "dp0": -1.7491e-02, "p1": 0.93644, "dp1": 1.2591e-01,
                                                  "cov": [ [1.578e-05, 2.916e-07, 1.056e-05, 3.694e-06],
                                                           [2.916e-07, 1.842e-05, 4.05e-06, 2.116e-07],
                                                           [1.056e-05, 4.05e-06, 0.003583, -2.522e-05],
                                                           [3.694e-06, 2.116e-07, -2.522e-05, 0.0045]],
                                                  "average": 0.43744, "tagEff":0.63900, "aTagEff":6.8522e-03, "use":True}



    configdict["Acceptance"] = { "knots": [0.50, 1.0,  1.5, 2.0, 3.0, 12.0],
                                 #"values":[0.347572901037, 0.538426860119, 0.742737602096, 0.919403303754, 1.01804016908, 1.07936031317]
                                 "values":[0.3664407781, 0.566982983334, 0.779405394092, 0.966060333357, 1.0695450788, 1.15319484969]
                                 #"values": [0.403856324129, 0.624609402267, 0.851615407148, 1.06363262672, 1.16936200757, 1.27135676682] 
                                 }

# Additional knot at 0.75
#    configdict["Acceptance"] = { "knots": [0.50, 0.75, 1.0,  1.5, 2.0, 3.0, 12.0],
#                                 "values":[0.370284829664, 0.483900633916, 0.596422133286, 0.831048197861, 0.958300794635, 1.07340198419, 1.14741387986]
#                                 }

# Additional knot at 6
#    configdict["Acceptance"] = { "knots": [0.50, 1.0,  1.5, 2.0, 3.0, 6.0, 12.0],
#                                 "values":[0.370710341594, 0.574252350639, 0.793247946774, 0.979409093234, 1.08868777487, 1.11518962111, 1.11620495781]
#                                 }

# Additional knots at 0.75 and 6
#    configdict["Acceptance"] = { "knots": [0.50, 0.75,  1.0,  1.5, 2.0, 3.0, 6.0, 12.0],
#                                 "values":[0.375781859886, 0.491211389496, 0.604395388273, 0.844577216222, 0.969644585897, 1.09378017785, 1.11186353652, 1.12116231304]
#                                 }



    configdict["constParams"] = []
    configdict["constParams"].append('Gammas_Bs2DsK')
    configdict["constParams"].append('deltaGammas_Bs2DsK')
    #configdict["constParams"].append('C_Bs2DsPi')
    #configdict["constParams"].append('Cbar_Bs2DsPi')
    #configdict["constParams"].append('S_Bs2DsPi')
    #configdict["constParams"].append('Sbar_Bs2DsPi')
    #configdict["constParams"].append('D_Bs2DsPi')
    #configdict["constParams"].append('Dbar_Bs2DsPi')
    configdict["constParams"].append('tagEffSig')
    configdict["constParams"].append('DeltaMs_Bs2DsK')
    configdict["constParams"].append('var1')
    configdict["constParams"].append('var2')
    configdict["constParams"].append('var3')
    configdict["constParams"].append('var4')
    configdict["constParams"].append('var5')
    configdict["constParams"].append('var6')
#    configdict["constParams"].append('var7')
#    configdict["constParams"].append('var8')
    configdict["constParams"].append('tagEff_OS')
    configdict["constParams"].append('tagEff_SS')
    configdict["constParams"].append('tagEff_Both')
    configdict["constParams"].append('aTagEff_OS')
    configdict["constParams"].append('aTagEff_SS')
    configdict["constParams"].append('aTagEff_Both')
    if configdict["ConstrainsForTaggingCalib"] == False:
        configdict["constParams"].append('p0_OS')
        configdict["constParams"].append('p0_SS')
        configdict["constParams"].append('p1_OS')
        configdict["constParams"].append('p1_SS')
        configdict["constParams"].append('dp0_OS')
        configdict["constParams"].append('dp0_SS')
        configdict["constParams"].append('dp1_OS')
        configdict["constParams"].append('dp1_SS')
    configdict["constParams"].append('p0_mean_OS')
    configdict["constParams"].append('p0_mean_SS')
    configdict["constParams"].append('p1_mean_OS')
    configdict["constParams"].append('p1_mean_SS')
    configdict["constParams"].append('dp0_mean_OS')
    configdict["constParams"].append('dp0_mean_SS')
    configdict["constParams"].append('dp1_mean_OS')
    configdict["constParams"].append('dp1_mean_SS')
    configdict["constParams"].append('average_OS')
    configdict["constParams"].append('average_SS')


    return configdict
