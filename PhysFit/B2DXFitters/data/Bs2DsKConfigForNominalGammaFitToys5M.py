def getconfig() :

    configdict = {}
    
    from math import pi

    # PHYSICAL PARAMETERS
    configdict["Gammas"]      =  0.661   # in ps^{-1}
    configdict["DeltaGammas"] = -0.105
    configdict["DeltaMs"]     =  17.768   # in ps^{-1}
    configdict["TagEffSig"]   = 0.403 #392 #403
    configdict["TagOmegaSig"] = 0.391
    configdict["StrongPhase"] = 30. / 180. * pi
    configdict["WeakPhase"]   = 70. / 180. * pi
    configdict["ArgLf"]       = configdict["StrongPhase"] - configdict["WeakPhase"]
    configdict["ArgLbarfbar"] = configdict["StrongPhase"] + configdict["WeakPhase"]
    configdict["ModLf"]       = 0.372
    
    configdict["calibration_p0"]  = [0.3927, 0.4244]
    configdict["calibration_p1"]  = [0.9818, 1.2550]
    configdict["calibration_av"]  = [0.3919, 0.4097]
                    
    configdict["resolutionScaleFactor"] = 1.37 
    configdict["resolutionMeanBias"]    = 0.
    
    configdict["resolutionSigma1"] = 2.21465e-02
    configdict["resolutionSigma2"] = 3.72057e-02
    configdict["resolutionSigma3"] = 6.37859e-02
    configdict["resolutionFrac1"]  = 3.62689e-01
    configdict["resolutionFrac2"]  = 5.65100e-01

    configdict["tacc_size"]   = 6
    configdict["tacc_knots"]  = [0.25, 0.5, 1.0, 2.0, 3.0, 12.0]
    configdict["tacc_values"] = [1.86413e-01, 2.83214e-01, 7.24952e-01, 1.18847e+00, 1.33798e+00, 1.32593e+00]

    configdict["tagEff_OS"] = 0.387
    configdict["tagEff_SS"] = 0.4772
    
    configdict["TagEffSig"]    = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                  configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                  configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    
    configdict["aTagEffSig"]    = [0.0, 0.0, 0.0]
                
    configdict["MistagFile"]     = "../data/workspace/MDFitter/template_Data_Mistag_BsDsPi.root"
    configdict["MistagWork"]     = "workspace"
    configdict["MistagTempName"] = ["sigMistagPdf_1", "sigMistagPdf_2", "sigMistagPdf_3"]
    
    configdict["TerrFile"]     = "../data/workspace/MDFitter/template_Data_Terr_BsDsK.root"
    configdict["TerrWork"]     = "workspace"
    configdict["TerrTempName"] = "TimeErrorPdf_Bs2DsK"

    configdict["constParams"] = []
    configdict["constParams"].append('Gammas')
    configdict["constParams"].append('deltaGammas')
    configdict["constParams"].append('deltaMs')
    #configdict["constParams"].append('tagEffSig')
    configdict["constParams"].append('tacc_exponent')
    configdict["constParams"].append('tacc_offset')
    configdict["constParams"].append('tacc_beta')
    configdict["constParams"].append('tacc_turnon')

    return configdict