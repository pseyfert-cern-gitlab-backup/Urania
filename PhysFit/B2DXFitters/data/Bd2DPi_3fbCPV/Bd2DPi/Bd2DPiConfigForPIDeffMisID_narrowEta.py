from ROOT import *

def getconfig() :

    configdict = {}

    from math import pi
    from math import log

    configdict["Calibration"] = {"Pi":
                                 {"FileMU"   : "root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/PIDeff/PerfHists_Pi_Strip21_MagUp_Bd2DPi_narrow_P_ETA.root",
                                  "FileMD"   : "root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/PIDeff/PerfHists_Pi_Strip21_MagDown_Bd2DPi_narrow_P_ETA.root",
                                  "PassedDLLK<5.0" : "PassedHist_Pi_DLLK<5.0_All__Pi_P_Pi_Eta;1",
                                  "TotalDLLK<5.0"  : "TotalHist_Pi_DLLK<5.0_All__Pi_P_Pi_Eta;1",
                                  "PassedDLLK>5.0" : "PassedHist_Pi_DLLK>5.0_All__Pi_P_Pi_Eta;1",
                                  "TotalDLLK>5.0"  : "TotalHist_Pi_DLLK>5.0_All__Pi_P_Pi_Eta;1",
                                  "PassedDLLK<8.0" : "PassedHist_Pi_DLLK<8.0_All__Pi_P_Pi_Eta;1",
                                  "TotalDLLK<8.0"  : "TotalHist_Pi_DLLK<8.0_All__Pi_P_Pi_Eta;1",
                                  "PassedDLLK>-2.0" : "PassedHist_Pi_DLLK>-2.0_All__Pi_P_Pi_Eta;1",
                                  "TotalDLLK>-2.0"  : "TotalHist_Pi_DLLK>-2.0_All__Pi_P_Pi_Eta;1"},
                                 "K":
                                 {"FileMU"   : "root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/PIDeff/PerfHists_K_Strip21_MagUp_Bd2DPi_narrow_P_ETA.root",
                                  "FileMD"   : "root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/PIDeff/PerfHists_K_Strip21_MagDown_Bd2DPi_narrow_P_ETA.root",
                                  "PassedDLLK<5.0" : "PassedHist_K_DLLK<5.0_All__K_P_K_Eta;1",
                                  "TotalDLLK<5.0"  : "TotalHist_K_DLLK<5.0_All__K_P_K_Eta;1",
                                  "PassedDLLK>5.0" : "PassedHist_K_DLLK>5.0_All__K_P_K_Eta;1",
                                  "TotalDLLK>5.0"  : "TotalHist_K_DLLK>5.0_All__K_P_K_Eta;1",
                                  "PassedDLLK<8.0" : "PassedHist_K_DLLK<8.0_All__K_P_K_Eta;1",
                                  "TotalDLLK<8.0"  : "TotalHist_K_DLLK<8.0_All__K_P_K_Eta;1",
                                  "PassedDLLK>-2.0" : "PassedHist_K_DLLK>-2.0_All__K_P_K_Eta;1",
                                  "TotalDLLK>-2.0"  : "TotalHist_K_DLLK>-2.0_All__K_P_K_Eta;1"}
                                 }

    configdict["Tuple"] = {"Pi":
                           {"FileMU"  : "root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MC_Bd2DPi_Bd2DPiHypo_magUp_S21_beforeSelection.root",
                            "FileMD"  : "root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MC_Bd2DPi_Bd2DPiHypo_magDown_S21_beforeSelection.root",
                            "Tree"    : "B2Dpi/DecayTree"},
                           "K":
                           {"FileMU"  : "root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MC_Bd2DK_Bd2DPiHypo_magUp_S21_beforeSelection.root",
                            "FileMD"  : "root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MC_Bd2DK_Bd2DPiHypo_magDown_S21_beforeSelection.root",
                            "Tree"    : "B2Dpi/DecayTree"}
                           }

    configdict["PIDleafPrefix"] = { "DLLK" : "PIDK" }

    configdict["Variables"] = { "P":
                                {"Suffix"        : "P",
                                 "Title"         : "Momentum [MeV/c]",
                                 "Type"          : "F",
                                 "Min"           : 3980,
                                 "Max"           : 200000,
                                 "Binning"       : [2000] + [i for i in range(3980,200001,1980)] + [250000, 300000]
                                 },
                                "ETA":
                                {"Suffix"       : "LOKI_ETA",
                                 "Title"        : "Pseudorapidity",
                                 "Type"         : "D",
                                 "Min"          : 1.7,
                                 "Max"          : 5.0,
                                 "Binning"      : [ x*0.01 for x in range(150,505,5) ]
                                 }
                                }
    
    return configdict
