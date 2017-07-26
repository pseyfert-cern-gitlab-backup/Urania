def getconfig() :

    from Bs2DsPiConfigForNominalMassFit import getconfig as getconfig_nominal
    configdict = getconfig_nominal()

    from math import pi

    # PHYSICAL PARAMETERS
    configdict["Gammas"]        =  0.6643 #0.0020   # in ps^{-1}
    configdict["DeltaGammas"]   =  0.083 #-0.006
    configdict["DeltaMs"]       = 17.757   # in ps^{-1}
    configdict["TagEffSig"]     = 0.403
    configdict["TagOmegaSig"]   = 0.391
    configdict["StrongPhase"]   = 20. / 180. * pi
    configdict["WeakPhase"]     = 70./180.*pi
    configdict["ModLf"]         = 0.372
    configdict["CPlimit"]       = {"upper":4.0, "lower":-4.0} 


    configdict["Asymmetries"] = {"Detection":1.0/100.0,
                                 "Production":1.1/100.0}
#    configdict["Asymmetries"] = {"Detection":0.0,
#                                 "Production":0.0}


    configdict["TaggingCalibration"] = {}

    configdict["FixAcceptance"] = False
    configdict["ConstrainsForTaggingCalib"] = True

    configdict["UsedResolution"] = "SecondApproach"

    if configdict["UsedResolution"] == "Nominal":
    # Nominal Resolution and corresponding tagging parameters
        configdict["Resolution"] = { "scaleFactor":{"p0":0.010262, "p1":1.280, "p2":0.0},
                                     "meanBias":0.0,
                                     "shape": { "sigma1":2.14946e-02, "sigma2":3.67643e-02, "sigma3":6.32869e-02,
                                                "frac1":3.72147e-01, "frac2":5.65150e-01},
                                     "templates": { "fileName":"work_templates_dspi.root",
                                                    "workName":"work",
                                                    "templateName":"TimeErrorPdf_Bs2DsPi"} }
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.44141, "dp0": 0.0, "p1": 1.0837, "dp1": 0.0,
#                                                  "cov": [ [2.167e-05, 0.0, 1.708e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [1.708e-05, 0.0, 0.004593, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.43744, "tagEff":0.63926, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.37400, "dp0": 0.0, "p1": 1.0941, "dp1": 0.0,
#                                                  "cov": [ [3.715e-05, 0.0, 7.059e-06, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [7.059e-06, 0.0, 0.004018, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.36980, "tagEff":0.37146, "aTagEff":0.0, "use":True}
#2011
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.43557, "dp0": 0.0, "p1": 1.0915, "dp1": 0.0,
#                                                  "cov": [ [7.357e-05, 0.0, 1.599e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [1.599e-05, 0.0, 0.01565, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.43744, "tagEff":0.64772, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.37129, "dp0": 0.0, "p1": 1.2627, "dp1": 0.0,
#                                                  "cov": [ [0.0001261, 0.0, -4.72e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [-4.72e-05, 0.0, 0.01376, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.36980, "tagEff":0.36619, "aTagEff":0.0, "use":True}
#2012
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.44390, "dp0": 0.0, "p1": 1.0828, "dp1": 0.0,
#                                                  "cov": [ [3.061e-05, 0.0, 3.127e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [3.127e-05, 0.0, 0.006489, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.43744, "tagEff":0.63541, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.37533, "dp0": 0.0, "p1": 1.0240, "dp1": 0.0,
#                                                  "cov": [ [5.263e-05, 0.0, 5.056e-07, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [5.056e-07, 0.0, 0.005774, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.36980, "tagEff":0.37373, "aTagEff":0.0, "use":True}
#BDTG1
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.44342, "dp0": 0.0, "p1": 1.0016, "dp1": 0.0,
#                                                  "cov": [ [4.63e-05, 0.0, -9.891e-08, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [-9.891e-08, 0.0, 0.01127, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.43744, "tagEff":0.62850, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.38619, "dp0": 0.0, "p1": 1.1536, "dp1": 0.0,
#                                                  "cov": [ [7.913e-05, 0.0, 1.718e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [1.718e-05, 0.0, 0.007995, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.36980, "tagEff":0.37206, "aTagEff":0.0, "use":True}
#BDTG2
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.43815, "dp0": 0.0, "p1": 1.1339, "dp1": 0.0,
#                                                  "cov": [ [4.272e-05, 0.0, 6.045e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [6.045e-05, 0.0, 0.00839, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.43744, "tagEff":0.65150, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.36038, "dp0": 0.0, "p1": 1.0295, "dp1": 0.0,
#                                                  "cov": [ [7.355e-05, 0.0, 2.61e-06, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [2.61e-06, 0.0, 0.00832, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.36980, "tagEff":0.37184, "aTagEff":0.0, "use":True}
#Bsp1
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.45307, "dp0": 0.0, "p1": 0.95250, "dp1": 0.0,
#                                                  "cov": [ [4.05e-05, 0.0, -5.74e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [-5.74e-05, 0.0, 0.01187, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.43744, "tagEff":0.60052, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.37144, "dp0": 0.0, "p1": 1.1117, "dp1": 0.0,
#                                                  "cov": [ [6.622e-05, 0.0, 1.089e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [1.089e-05, 0.0, 0.006828, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.36980, "tagEff":0.36141, "aTagEff":0.0, "use":True}
#Bsp2
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.42892, "dp0": 0.0, "p1": 1.1379, "dp1": 0.0,
#                                                  "cov": [ [4.695e-05, 0.0, 0.0001046, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [0.0001046, 0.0, 0.007508, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.43744, "tagEff":0.70009, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.37834, "dp0": 0.0, "p1": 1.0750, "dp1": 0.0,
#                                                  "cov": [ [8.377e-05, 0.0, 1.083e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [1.083e-05, 0.0, 0.009593, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.36980, "tagEff":0.38755, "aTagEff":0.0, "use":True}
#down
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.43888, "dp0": 0.0, "p1": 1.0234, "dp1": 0.0,
#                                                  "cov": [ [4.032e-05, 0.0, 3.843e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [3.843e-05, 0.0, 0.008425, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.43744, "tagEff":0.63992, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.38108, "dp0": 0.0, "p1": 1.1897, "dp1": 0.0,
#                                                  "cov": [ [6.925e-05, 0.0, 2.583e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [2.583e-05, 0.0, 0.00708, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.36980, "tagEff":0.37044, "aTagEff":0.0, "use":True}
#up
#        configdict["TaggingCalibration"]["SS"] = {"p0": 0.44452, "dp0": 0.0, "p1": 1.1491, "dp1": 0.0,
#                                                  "cov": [ [4.678e-05, 0.0, 2.555e-05, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [2.555e-05, 0.0, 0.01015, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.43744, "tagEff":0.63794, "aTagEff":0.0, "use":True}
#        configdict["TaggingCalibration"]["OS"] = {"p0": 0.36658, "dp0": 0.0, "p1": 0.97952, "dp1": 0.0,
#                                                  "cov": [ [7.989e-05, 0.0, -2.343e-06, 0.0],
#                                                           [0.0, 1.0, 0.0, 0.0],
#                                                           [-2.343e-06, 0.0, 0.009214, 0.0],
#                                                           [0.0, 0.0, 0.0, 1.0]],
#                                                  "average": 0.36980, "tagEff":0.37263, "aTagEff":0.0, "use":True}


    if configdict["UsedResolution"] == "SingleGaussian":
    # Single Gaussian Resolution and corresponding Tagging Parameter
        configdict["Resolution"] = { "scaleFactor":{"p0":0.0, "p1":1.772, "p2":0.0},
                                     "meanBias":0.0,
                                     "shape": { "sigma1":2.14946e-02, "sigma2":3.67643e-02, "sigma3":6.32869e-02,
                                                "frac1":3.72147e-01, "frac2":5.65150e-01},
                                     "templates": { "fileName":"../data/workspace/MDFitter/template_Data_Terr_Bs2DsPi_BDTGA.root",
                                                    "workName":"workspace",
                                                    "templateName":"TimeErrorPdf_Bs2DsPi"} }
        configdict["TaggingCalibration"]["SS"] = {"p0": 0.43752, "dp0": 0.0, "p1": 1.1325, "dp1": 0.0,
                                                  "cov": [ [2.496e-05, 0.0, 2.592e-05, 0.0],
                                                           [0.0, 1.0, 0.0, 0.0],
                                                           [2.592e-05, 0.0, 0.004951, 0.0],
                                                           [0.0, 0.0, 0.0, 1.0]],
                                                  "average": 0.43744, "tagEff":0.63899, "aTagEff":0.0, "use":True}
        configdict["TaggingCalibration"]["OS"] = {"p0": 0.36446, "dp0": 0.0, "p1": 1.1648, "dp1": 0.0,
                                                  "cov": [ [4.277e-05, 0.0, 6.848e-06, 0.0],
                                                           [0.0, 1.0, 0.0, 0.0],
                                                           [6.848e-06, 0.0, 0.004535, 0.0],
                                                           [0.0, 0.0, 0.0, 1.0]],
                                                  "average": 0.369798, "tagEff":0.37146, "aTagEff":0.0, "use":True}
        
    if configdict["UsedResolution"] == "SecondApproach":
    # Resolution for second approach to check systematics and corresponding Tagging Parameter
        configdict["Resolution"] = { "scaleFactor":{"p0":-0.000568, "p1":1.243, "p2":0.0},
                                     "meanBias":0.0,
                                     "shape": { "sigma1":2.14946e-02, "sigma2":3.67643e-02, "sigma3":6.32869e-02,
                                                "frac1":3.72147e-01, "frac2":5.65150e-01},
                                     "templates": { "fileName":"../data/workspace/MDFitter/template_Data_Terr_Bs2DsPi_BDTGA.root",
                                                    "workName":"workspace",
                                                    "templateName":"TimeErrorPdf_Bs2DsPi"} }
        configdict["TaggingCalibration"]["SS"] = {"p0": 0.44907, "dp0": 0.0, "p1": 0.95005, "dp1": 0.0,
                                                  "cov": [ [2.263e-05, 0.0, 0.0001461, 0.0],
                                                           [0.0, 1.0, 0.0, 0.0],
                                                           [0.0001461, 0.0, 0.005204, 0.0],
                                                           [0.0, 0.0, 0.0, 1.0]],
                                                  "average": 0.43744, "tagEff":0.63926, "aTagEff":0.0, "use":True}
        configdict["TaggingCalibration"]["OS"] = {"p0": 0.39432, "dp0": 0.0, "p1": 0.97298, "dp1": 0.0,
                                                  "cov": [ [4.122e-05, 0.0, 0.0002132, 0.0],
                                                           [0.0, 1.0, 0.0, 0.0],
                                                           [0.0002132, 0.0, 0.005549, 0.0],
                                                           [0.0, 0.0, 0.0, 1.0]],
                                                  "average": 0.369798, "tagEff":0.37151, "aTagEff":0.0, "use":True}

    configdict["Acceptance"] = { "knots": [0.50, 1.0,  1.5, 2.0, 3.0, 12.0],
                                 "values": [3.774e-01,5.793e-01,7.752e-01,1.0043e+00,1.0937e+00,1.1872e+00] }
#    configdict["Acceptance"] = { "knots": [0.50, 1.0,  1.5, 2.0, 3.0, 12.0],
#                                 "values": [0.4382, 0.6840, 0.8382, 1.1381, 1.2230, 1.3113] }
#    configdict["Acceptance"] = { "knots": [0.50, 0.75, 1.0,  1.5, 2.0, 3.0, 12.0],
#                                 "values": [0.4382, 0.500, 0.6840, 0.8382, 1.1381, 1.2230, 1.3113] }
#    configdict["Acceptance"] = { "knots": [0.50, 1.0,  1.5, 2.0, 3.0, 6.0, 12.0],
#                                 "values": [0.4382, 0.6840, 0.8382, 1.1381, 1.2230, 1.2500, 1.3113] }
#    configdict["Acceptance"] = { "knots": [0.50, 0.75, 1.0,  1.5, 2.0, 3.0, 6.0, 12.0],
#                                 "values": [0.4382, 0.500, 0.6840, 0.8382, 1.1381, 1.2230, 1.2500, 1.3113] }

    configdict["constParams"] = []
    configdict["constParams"].append('Gammas_Bs2DsPi')
    configdict["constParams"].append('deltaGammas_Bs2DsPi')
    configdict["constParams"].append('C_Bs2DsPi')
    configdict["constParams"].append('Cbar_Bs2DsPi')
    configdict["constParams"].append('S_Bs2DsPi')
    configdict["constParams"].append('Sbar_Bs2DsPi')
    configdict["constParams"].append('D_Bs2DsPi')
    configdict["constParams"].append('Dbar_Bs2DsPi')
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
