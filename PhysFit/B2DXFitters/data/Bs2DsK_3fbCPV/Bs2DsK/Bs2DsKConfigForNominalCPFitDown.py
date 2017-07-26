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
        configdict["TaggingCalibration"]["SS"] = {"p0": 0.43888, "dp0": -3.2376e-02, "p1": 1.0234, "dp1": 1.5758e-01,
                                                  "cov": [ [4.032e-05, -1.347e-07, 3.843e-05, 1.577e-05],
                                                           [-1.347e-07, 3.494e-05, 1.734e-05, -4.516e-06],
                                                           [3.843e-05, 1.734e-05, 0.008425, -0.0006357],
                                                           [1.577e-05, -4.516e-06, -0.0006357, 0.008482]],
                                                  "average": 0.43744, "tagEff":0.63992, "aTagEff":-5.5608e-03, "use":True}
        configdict["TaggingCalibration"]["OS"] = {"p0": 0.38108, "dp0": 1.8278e-02, "p1": 1.1897, "dp1": 6.8307e-02,
                                                  "cov": [ [6.925e-05, -2.004e-07, 2.583e-05, -1.085e-05],
                                                           [-2.004e-07, 6.544e-05, -1.039e-05, -3.396e-05],
                                                           [2.583e-05, -1.039e-05, 0.00708, 0.0001336],
                                                           [-1.085e-05, -3.396e-05, 0.0001336, 0.007114]],
                                                  "average": 0.36980, "tagEff":0.37044, "aTagEff":-6.9113e-03, "use":True}

    configdict["Acceptance"] = { "knots": [0.50, 1.0,  1.5, 2.0, 3.0, 12.0],
                                 #"values":[0.347572901037, 0.538426860119, 0.742737602096, 0.919403303754, 1.01804016908, 1.07936031317]
                                 "values":[0.33894503623, 0.528050576502, 0.728988973363, 0.892475430769, 1.00602417104, 1.07955888495]
                                 #"values": [0.403856324129, 0.624609402267, 0.851615407148, 1.06363262672, 1.16936200757, 1.27135676682] 
                                 }


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
