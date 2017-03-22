def getconfig():

    configdict = {}

    configdict["BasicVariables"] = {}
    configdict["BasicVariables"]["BeautyTime"]    = { "Range"                  : [0.4,     15.0    ],
                                                      "Bins"                   : 40,
                                                      "Name"                   : "BeautyTime",
                                                      "InputName"              : "lab0_FitDaughtersPVConst_ctau_flat"}
    configdict["BasicVariables"]["TagDecTrue"]      = { "Range"                  : [-1.0,    1.0     ],
                                                        "Name"                   : "TagDecTrue",
                                                        "InputName"              : "TrueTag"}
    configdict["BasicVariables"]["BacCharge"]     = { "Range"                  : [-1000.0, 1000.0  ],
                                                      "Name"                   : "BacCharge",
                                                      "InputName"              : "lab1_TRUEID"}
    configdict["BasicVariables"]["TagDecOS"]      = { "Range"                  : [-1.0,    1.0     ],
                                                      "Name"                   : "TagDecOS",
                                                      "InputName"              : "TagDecOS"}
    configdict["BasicVariables"]["TagDecSS"]      = { "Range"                  : [-1.0,    1.0     ],
                                                      "Name"                   : "TagDecSS",
                                                      "InputName"              : "TagDecSS"}

    configdict["Samples"] = {}
    configdict["Functions"] = {}

    #Original MC
    configdict["Samples"]["MC"] = { "File" : "/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/work_dpi_mc_large_shorttime.root",
                                    "Workspace" : "workspace",
                                    "Dataprefix" : "dataSetMC_",
                                    "Decay" : "Bd2DPi",
                                    "Sample" : "both",
                                    "Mode" : "kpipi",
                                    "Year" : "run1",
                                    "Hypo" : "Bd2DPi",
                                    "Merge" : "both",
                                    "Observable" : "BeautyTime",
                                    "Category1" : "(TagDecOS_idx!=0||TagDecSS_idx!=0) && TagDecTrue_idx==-1",
                                    "Category2" : "(TagDecOS_idx!=0||TagDecSS_idx!=0) && TagDecTrue_idx==1",
                                    "Color" : 1,
                                    "Width" : 2,
                                    "Legend" : "Monte Carlo"}

    #Bootstrapped MC
    configdict["Samples"]["BootstrappedMC"] = { "File" : "/eos/lhcb/wg/b2oc/TD_DPi_3fb/MCBootstrap/Bd2DPiMCFilteredS21RunIBothTaggedOnlyShortTime/Generator/BootstrapMC_Bd2DPiMCFilteredS21RunIBothTaggedOnlyShortTime_0.root",
                                                "Workspace" : "workspace",
                                                "Dataset" : "combData",
                                                "Observable" : "BeautyTime",
                                                "Category1" : "(TagDecOS_idx!=0||TagDecSS_idx!=0) && TagDecTrue_idx==-1",
                                                "Category2" : "(TagDecOS_idx!=0||TagDecSS_idx!=0) && TagDecTrue_idx==1",
                                                "Color" : 6,
                                                "Width" : 2,
                                                "Legend" : "Resampled Monte Carlo"}

    #Toy generated using values fitted in original MC
    configdict["Samples"]["Toy"] = { "File" : "/eos/lhcb/wg/b2oc/TD_DPi_3fb/Toys/FromMCFitSgnOnlyTrueTagProdDetAsymmAccMeanResTime04to12/Generator/GenToyWorkspace_FromMCFitSgnOnlyTrueTagProdDetAsymmAccMeanResTime04to12_0.root",
                                     "Workspace" : "workspace",
                                     "Dataprefix" : "dataSet",
                                     "Decay" : "Bd2DPi",
                                     "Sample" : "both",
                                     "Mode" : "kpipi",
                                     "Year" : "run1",
                                     "Hypo" : "Bd2DPi",
                                     "Merge" : "alreadyboth",
                                     "Observable" : "BeautyTime",
                                     "Category1" : "TagDecOS_idx==-1",
                                     "Category2" : "TagDecOS_idx==1",
                                     "Color" : 2,
                                     "Width" : 2,
                                     "Legend" : "Pseudoexperiment"}

    #Analytical shape using parameters from fit to total MC
    configdict["Functions"]["Fit"] = { "Expression" : "155.943+(806651.0-(1.1724e-13)*cos(0.51037*x))/(-5172.94+0.142483*cos(0.51037*x)+sin(0.51037*x))",
                                       "Color" : 4,
                                       "Width" : 2,
                                       "Legend" : "Decay time fit to MC"}
    
    configdict["Plot"] = { "Bins" : [0.4,0.8,1.2,1.6,2.0,2.4,2.8,3.2,3.6,4.0,
                                     4.5,5.0,5.5,6.0,7.0,8.0,9.0,10.0,12.0],
                           "Range" : [0.4,12.0],
                           "TitleX" : "#tau [ps]",
                           "TitleY" : "A_{#font[12]{CP}}",
                           "Legend" : [0.2,0.7,0.4,0.9]
                           }

    configdict["Label"] = {"X" : 0.55,
                           "Y" : 0.875,
                           "Text" : "LHCb Preliminary"}

    return configdict
