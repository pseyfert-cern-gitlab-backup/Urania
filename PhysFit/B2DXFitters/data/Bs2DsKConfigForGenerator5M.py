def getconfig() :

    configdict = {}
    
    from math import pi

    # PHYSICAL PARAMETERS
    configdict["Gammas"]      =  0.661   # in ps^{-1}
    configdict["DeltaGammas"] = -0.105

    configdict["Gammad"]      =  0.656   # in ps^{-1}
    configdict["DeltaGammad"] =  0.

    configdict["DeltaMs"]     =  17.768    # in ps^{-1}
    configdict["DeltaMd"]     =  0.507   # in ps^{-1}

    configdict["GammaLb"]    =  0.700    # in ps^{-1}
    configdict["GammaCombo"] =  0.800
       
    configdict["StrongPhase_d"] = 20. / 180. * pi
    configdict["StrongPhase_s"] = 30. / 180. * pi
    configdict["WeakPhase"]     = 70. / 180. * pi

    configdict["ArgLf_d"]       = configdict["StrongPhase_d"] - configdict["WeakPhase"]
    configdict["ArgLbarfbar_d"] = configdict["StrongPhase_d"] + configdict["WeakPhase"]
    configdict["ModLf_d"]       = 0.015
    
    configdict["ArgLf_s"]       = configdict["StrongPhase_s"] - configdict["WeakPhase"]
    configdict["ArgLbarfbar_s"] = configdict["StrongPhase_s"] + configdict["WeakPhase"]
    configdict["ModLf_s"]       = 0.372

    configdict["calibration_p0"]  = [0.3927, 0.4244]
    configdict["calibration_p1"]  = [0.9818, 1.2550]
    configdict["calibration_av"]  = [0.3919, 0.4097]
       
    configdict["resolutionScaleFactor"] = 1.37
    configdict["resolutionMeanBias"]    = 0.0
    
    configdict["nBinsMistag"]   = 50
    configdict["nBinsProperTimeErr"]   = 50
    configdict["nBinsAcceptance"]   = 740
    
    configdict["lumRatioDown"] =  0.59
    configdict["lumRatioUp"] =  0.44
    configdict["lumRatio"] =  configdict["lumRatioUp"]/(configdict["lumRatioDown"]+configdict["lumRatioUp"])
            
    configdict["timeRange"] = [0.2, 15]

    configdict["tacc_size"]   = 6
    configdict["tacc_knots"]  = [0.25, 0.5, 1.0, 2.0, 3.0, 12.0]
    configdict["tacc_values"] = [1.77520e-01, 2.89603e-01, 6.79455e-01, 1.11726e+00, 1.23189e+00, 1.26661e+00] 

    configdict["tagEff_OS"] = 0.387
    configdict["tagEff_SS"] = 0.4772

    configdict["tagEff_signal"]    = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    configdict["tagEff_dk"]        = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    configdict["tagEff_dpi"]        = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    configdict["tagEff_dsk"]       = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    configdict["tagEff_dspi"]      = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    configdict["tagEff_lck"]       = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    configdict["tagEff_lcpi"]       = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    configdict["tagEff_combo"]     = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    configdict["tagEff_dsp"]       = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    configdict["tagEff_dsstp"]     = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    
    configdict["tagEff_lm1"]       = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    configdict["tagEff_dsstpi"]    = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    configdict["tagEff_dsrho"]     = [configdict["tagEff_OS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_SS"] - configdict["tagEff_OS"]*configdict["tagEff_SS"],
                                      configdict["tagEff_OS"]*configdict["tagEff_SS"]]
    

    configdict["aprod_signal"]    = 0.0 #0.03
    configdict["aprod_dk"]        = 0.0 #0.03
    configdict["aprod_dpi"]       = 0.0 #0.03 
    configdict["aprod_dsk"]       = 0.0 #3
    configdict["aprod_dspi"]      = 0.0 # 3
    configdict["aprod_lck"]       = 0.0 # 3
    configdict["aprod_lcpi"]      = 0.0 # 3
    configdict["aprod_combo"]     = 0.0 #3
    configdict["aprod_dsp"]       = 0.0 #3
    configdict["aprod_dsstp"]     = 0.0 #3
    configdict["aprod_lm1"]       = 0.0 #3
    configdict["aprod_dsstpi"]    = 0.0 #3
    configdict["aprod_dsrho"]     = 0.0 #3
                                    
    configdict["atageff_signal"]    = [0.0, 0.0, 0.0]
    configdict["atageff_dk"]        = [0.0, 0.0, 0.0]
    configdict["atageff_dpi"]       = [0.0, 0.0, 0.0]
    configdict["atageff_dsk"]       = [0.0, 0.0, 0.0]
    configdict["atageff_dspi"]      = [0.0, 0.0, 0.0]
    configdict["atageff_lck"]       = [0.0, 0.0, 0.0]
    configdict["atageff_lcpi"]      = [0.0, 0.0, 0.0]
    configdict["atageff_combo"]     = [0.0, 0.0, 0.0]
    configdict["atageff_dsp"]       = [0.0, 0.0, 0.0]
    configdict["atageff_dsstp"]     = [0.0, 0.0, 0.0]
    configdict["atageff_lm1"]       = [0.0, 0.0, 0.0]
    configdict["atageff_dsstpi"]    = [0.0, 0.0, 0.0]
    configdict["atageff_dsrho"]     = [0.0, 0.0, 0.0]

    configdict["adet_signal"]    = 0.0
    configdict["adet_dk"]        = 0.0
    configdict["adet_dpi"]       = 0.0
    configdict["adet_dsk"]       = 0.0
    configdict["adet_dspi"]      = 0.0
    configdict["adet_lck"]       = 0.0
    configdict["adet_lcpi"]      = 0.0
    configdict["adet_combo"]     = 0.0
    configdict["adet_dsp"]       = 0.0
    configdict["adet_dsstp"]     = 0.0
    configdict["adet_lm1"]       = 0.0
    configdict["adet_dsstpi"]    = 0.0
    configdict["adet_dsrho"]     = 0.0
    
    configdict["num_signal"]    = [308, 591, 487, 109,  314]
    configdict["num_dk"]        = [17,    0,   5,   0,    0]
    configdict["num_dpi"]       = [14,    3,   3,   0,    0]
    configdict["num_dsk"]       = [18,   35,  42,  11,   32]
    configdict["num_dspi"]      = [231*0.979*0.653, 514*0.979*0.653, 342*0.979*0.653, 90*0.979*0.653, 258*0.979*0.653]
    configdict["num_lck"]       = [15,    2,   4,   0,    0]
    configdict["num_lcpi"]      = [11,    1,   3,   0,    0]
    configdict["num_combo"]     = [664, 439, 327, 619, 1702]
    configdict["num_dsp"]       = [231*0.021*0.75, 514*0.021*0.75, 342*0.021*0.75, 90*0.021*0.75, 258*0.021*0.75]
    configdict["num_dsstp"]     = [231*0.021*0.25, 514*0.021*0.25, 342*0.021*0.25, 90*0.021*0.25, 258*0.021*0.25]
    configdict["num_lm1"]       = [0,     0,   0,   0,    0]
    configdict["num_dsstpi"]    = [231*0.979*0.347*0.5, 514*0.979*0.347*0.5, 342*0.979*0.347*0.5, 90*0.979*0.347*0.5, 258*0.979*0.347*0.5]
    configdict["num_dsrho"]     = [231*0.979*0.347*0.5, 514*0.979*0.347*0.5, 342*0.979*0.347*0.5, 90*0.979*0.347*0.5, 258*0.979*0.347*0.5]

    #----------------------------Signal----------------------------#

    configdict["mean"]    = [5367.51, 5367.51, 5367.51, 5367.51, 5367.51]

    configdict["sigma1"]  = [1.0717e+01*1.28,  1.1235e+01*1.28,  1.0772e+01*1.28,  1.1268e+01*1.28,  1.1391e+01*1.28 ]
    configdict["sigma2"]  = [1.6005e+01*1.22,  1.7031e+01*1.22,  1.5339e+01*1.22,  1.9408e+01*1.22,  1.7647e+01*1.22 ]
    configdict["alpha1"]  = [2.2118e+00,       2.2144e+00,       2.0480e+00,       2.3954e+00,       2.0930e+00 ]
    configdict["alpha2"]  = [-2.4185e+00,      -2.1918e+00,      -2.0291e+00,      -3.4196e+00,      -2.3295e+00]
    configdict["n1"]      = [1.0019e+00,       1.1193e+00,       1.2137e+00,       9.8202e-01,       1.2674e+00 ]
    configdict["n2"]      = [3.1469e+00,       3.6097e+00,       6.5735e+00,       5.2237e-01,       4.0195e+00 ]
    configdict["frac"]    = [6.1755e-01,       7.0166e-01,       5.8012e-01,       7.8103e-01,       7.0398e-01]


    configdict["ratio1"]  = 0.998944636665
    configdict["ratio2"]  = 1.00022181515

    configdict["meanDs"]    = [1968.49, 1968.49, 1968.49, 1968.49, 1968.49]

    configdict["sigma1Ds"]  = [5.3468e+00*1.16,  8.2412e+00*1.16,  6.0845e+00*1.16,  8.8531e+00*1.16,  8.0860e+00*1.16 ]
    configdict["sigma2Ds"]  = [5.1848e+00*1.19,  4.4944e+00*1.19,  5.1266e+00*1.19,  5.2073e+00*1.19,  7.3773e+00*1.19 ]
    configdict["alpha1Ds"]  = [1.2252e+00,       1.9827e+00,       1.1316e+00,       1.7131e+00,       9.0639e-01 ]
    configdict["alpha2Ds"]  = [-1.1167e+00,      -3.0525e+00,      -1.3760e+00,      -2.5276e+00,      -1.1122e+00]
    configdict["n1Ds"]      = [4.6625e+00,       1.4867e+00,       1.3280e+01,       2.0239e+00,       1.1486e+01 ]
    configdict["n2Ds"]      = [6.9989e+01,       6.1022e-01,       1.1017e+01,       1.0860e+00,       4.0001e+01 ]
    configdict["fracDs"]    = [4.7565e-01,       3.9628e-01 ,      4.0048e-01,       5.5084e-01,       4.8729e-01 ]

           
    configdict["cB"] = [-3.2717e-03, -2.0784e-03, -3.0429e-03, -1.5052e-03, -2.2054e-03]
    configdict["cD"] = [-2.7157e-03, -2.4707e-03, -5.1842e-03, -3.3044e-04, -3.7356e-03]
    configdict["fracDsComb"] = [9.4614e-01, 5.3355e-01, 7.7153e-01,  1.0, 1.0]

    configdict["fracPIDKComb1"] = 6.2485e-01
    configdict["fracPIDKComb2"] = 5.4107e-01
       
    return configdict
