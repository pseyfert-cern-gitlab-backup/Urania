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
        configdict["TaggingCalibration"]["SS"] = {"p0": 0.43815, "dp0": -1.2134e-02, "p1": 1.1339, "dp1": 4.9223e-02,
                                                  "cov": [ [4.272e-05, 3.16e-09, 6.045e-05, 7.944e-06],
                                                           [3.16e-09, 3.972e-05, 9.776e-06, 2.387e-05],
                                                           [6.045e-05, 9.776e-06, 0.00839, -0.0003623],
                                                           [7.944e-06, 2.387e-05, -0.0003623, 0.008737]],
                                                  "average": 0.43744, "tagEff":0.65150, "aTagEff":-5.1041e-03, "use":True}
        configdict["TaggingCalibration"]["OS"] = {"p0": 0.36038, "dp0": 1.1615e-02, "p1": 1.0295, "dp1": 7.2551e-02,
                                                  "cov": [ [7.355e-05, 2.358e-06, 2.61e-06, -1.282e-05],
                                                           [2.358e-06, 7.613e-05, -9.591e-06, -5.436e-05],
                                                           [2.61e-06, -9.591e-06, 0.00832, 0.0002854],
                                                           [-1.282e-05, -5.436e-05, 0.0002854, 0.008224]],
                                                  "average": 0.36980, "tagEff":0.37184, "aTagEff":4.2696e-03, "use":True}

    configdict["Acceptance"] = { "knots": [0.50, 1.0,  1.5, 2.0, 3.0, 12.0],
                                 #"values":[0.347572901037, 0.538426860119, 0.742737602096, 0.919403303754, 1.01804016908, 1.07936031317]
                                 "values":[0.0888728672246, 0.181390063104, 0.325672719884, 0.554897556739, 0.761608013327, 1.21036554934]
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
