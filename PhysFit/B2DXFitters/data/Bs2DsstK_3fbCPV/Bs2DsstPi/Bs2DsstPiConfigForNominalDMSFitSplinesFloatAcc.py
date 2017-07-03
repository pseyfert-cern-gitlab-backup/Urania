def getconfig() :

    from Bs2DsstPiConfigForNominalMassFit import getconfig as getconfig_nominal
    configdict = getconfig_nominal()

    from math import pi

    # PHYSICAL PARAMETERS
    configdict["Gammas"]        =  0.6643 #0.0020   # in ps^{-1}
    configdict["DeltaGammas"]   =  -0.083 #-0.006
    configdict["DeltaMs"]       = 17.757   # in ps^{-1}
    configdict["TagEffSig"]     = 0.403
    configdict["TagOmegaSig"]   = 0.391
    configdict["StrongPhase"]   = 20. / 180. * pi
    configdict["WeakPhase"]     = 70./180.*pi
    configdict["ModLf"]         = 0.372
    configdict["CPlimit"]       = {"upper":4.0, "lower":-4.0} 


    configdict["Asymmetries"] = {"Detection":1.0/100.0,
                                 "Production":1.1/100.0}
    configdict["TaggingCalibration"] = {}

    configdict["FixAcceptance"] = False
    configdict["ConstrainsForTaggingCalib"] = True

    configdict["UsedResolution"] = "Nominal"

    # Nominal Resolution and corresponding tagging parameters
    configdict["Resolution"] = { "scaleFactor":{"p0":0.010262, "p1":1.280, "p2":0.0},
                                 "meanBias":0.0,
                                 "shape": { "sigma1":2.14946e-02, "sigma2":3.67643e-02, "sigma3":6.32869e-02,
                                            "frac1":3.72147e-01, "frac2":5.65150e-01},
                                 "templates": { "fileName":"work_templates_dspi.root",
                                                "workName":"work",
                                                "templateName":"TimeErrorPdf_Bs2DsPi"} }
    configdict["TaggingCalibration"]["SS"] = {"p0": 0.44119, "dp0": 0.0, "p1": 1.0868, "dp1": 0.0,
                                              "cov": [ [2.903e-05, 0.0, 0.0001613, 0.0],
                                                       [0.0, 1.0, 0.0, 0.0],
                                                       [0.0001613, 0.0, 0.006101, 0.0],
                                                       [0.0, 0.0, 0.0, 1.0]],
                                              "average": 0.43744, "tagEff":0.63926, "aTagEff":0.0, "use":True}
    configdict["TaggingCalibration"]["OS"] = {"p0": 0.37718, "dp0": 0.0, "p1": 1.1244, "dp1": 0.0,
                                              "cov": [ [5.212e-05, 0.0, 0.0002286, 0.0],
                                                       [0.0, 1.0, 0.0, 0.0],
                                                       [0.0002286, 0.0, 0.006685, 0.0],
                                                       [0.0, 0.0, 0.0, 1.0]],
                                              "average": 0.369798, "tagEff":0.37151, "aTagEff":0.0, "use":True}

    configdict["Acceptance"] = { "knots": [0.50, 1.0,  1.5, 2.0, 3.0, 10.0],
                                 "values": [3.774e-01,5.793e-01,7.752e-01,1.0043e+00,1.0937e+00,1.1872e+00] }

    configdict["constParams"] = []
    configdict["constParams"].append('Gammas_Bs2DsstPi')
    configdict["constParams"].append('deltaGammas_Bs2DsstPi')
    configdict["constParams"].append('C_Bs2DsstPi')
    configdict["constParams"].append('Cbar_Bs2DsstPi')
    configdict["constParams"].append('S_Bs2DsstPi')
    configdict["constParams"].append('Sbar_Bs2DsstPi')
    configdict["constParams"].append('D_Bs2DsstPi')
    configdict["constParams"].append('Dbar_Bs2DsstPi')
    configdict["constParams"].append('tagEff_OS')
    configdict["constParams"].append('tagEff_SS')
    configdict["constParams"].append('tagEff_Both')
    configdict["constParams"].append('aTagEff_OS')
    configdict["constParams"].append('aTagEff_SS')
    configdict["constParams"].append('aTagEff_Both')
    if configdict["FixAcceptance"] == True:
        configdict["constParams"].append('var1')
        configdict["constParams"].append('var2')
        configdict["constParams"].append('var3')
        configdict["constParams"].append('var4')
        configdict["constParams"].append('var5')
        configdict["constParams"].append('var6')
        configdict["constParams"].append('var7')
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
#    configdict["constParams"].append('DeltaMs_Bs2DsPi')

    return configdict
