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
        configdict["TaggingCalibration"]["SS"] = {"p0": 0.44342, "dp0": -2.2981e-02, "p1": 1.0016, "dp1": 1.6327e-01,
                                                  "cov": [ [4.63e-05, 1.91e-06, -9.891e-08, 9.06e-06],
                                                           [1.91e-06, 3.697e-05, 8.637e-06, -3.258e-05],
                                                           [-9.891e-08, 8.637e-06, 0.01127, 0.0003397],
                                                           [9.06e-06, -3.258e-05, 0.0003397, 0.01003]],
                                                  "average": 0.43744, "tagEff":0.62850, "aTagEff":1.8537e-02, "use":True}
        configdict["TaggingCalibration"]["OS"] = {"p0": 0.38619, "dp0": 1.1922e-02, "p1": 1.1536, "dp1": 1.5441e-01,
                                                  "cov": [ [7.913e-05, -3.997e-06, 1.718e-05, 1.459e-05],
                                                           [-3.997e-06, 6.82e-05, 1.783e-05, -4.521e-05],
                                                           [1.718e-05, 1.783e-05, 0.007995, -0.0004398],
                                                           [1.459e-05, -4.521e-05, -0.0004398, 0.007388]],
                                                  "average": 0.36980, "tagEff":0.37206, "aTagEff":-2.2768e-02, "use":True}

    configdict["Acceptance"] = { "knots": [0.50, 1.0,  1.5, 2.0, 3.0, 12.0],
                                 #"values":[0.347572901037, 0.538426860119, 0.742737602096, 0.919403303754, 1.01804016908, 1.07936031317]
                                 "values":[1.21014219432, 1.746017854, 2.17640163012, 2.23297973945, 2.03303589062, 0.930136229619]
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
