from ROOT import *
from OurSites import *
from Cuts2013 import cuts11noKpi as cuts11, cuts12noKpi as cuts12
from parameters import * 
def createTTrees(KpiBins = []):
    #f11 = TFile(NTUPLE_PATH + "/MagUpAndDown3500GeVReco14s20r1dv33r4_1019pb_StrippingBetaSBs2JpsiKstarWideLine_2011_BDTG_Loose_wCosines.root")
    f11 = TFile("~/vol5/Tuple_BsJPsiKst2011.root")
    t2_11 = f11.Get("DecayTree")#/DecayTree")
    f12 = TFile(NTUPLE_PATH + "/MagUpAndDown4000GeVReco14s20r0p1dv33r4_2062pb_StrippingBetaSBs2JpsiKstarWideLine_2012_BDTG_Loose_wCosines.root")
    f12 = TFile("~/vol5/Tuple_BsJPsiKst2012.root")
    t2_12 = f12.Get("DecayTree")#/DecayTree")

    if not KpiBins: ### OLD STYLE
         
        f12p=TFile(NTUPLE_PATH + "/2012p.root","recreate")
        t12p=t2_12.CopyTree(cuts12+" && Kplus_ID > 0")
        t12p.Write()
        f12p.Close()
        f12n=TFile(NTUPLE_PATH+ "/2012n.root","recreate")
        t12n=t2_12.CopyTree(cuts12+" && Kplus_ID < 0")
        t12n.Write()
        f12n.Close()
        f11p=TFile(NTUPLE_PATH + "/2011p.root","recreate")
        t11p=t2_11.CopyTree(cuts11+" && Kplus_ID > 0")
        t11p.Write()
        f11p.Close()
        f11n=TFile(NTUPLE_PATH + "/2011n.root","recreate")
        t11n=t2_11.CopyTree(cuts11+" && Kplus_ID < 0")
        t11n.Write()
        f11n.Close()
        return 1
    myfiles = {}
    mytrees = {}
    for i in range(len(KpiBins)-1):
        m0 = KpiBins[i]
        m1 = KpiBins[i+1]
        myfiles["11p"+str(i)] = TFile(NTUPLE_PATH + "/2011p_" + str(m0) + "_" + str(m1) +".root", "recreate")
        mytrees["11p"+str(i)] = t2_11.CopyTree(cuts11+" && Kplus_ID > 0 && Kst_892_0_MM >=" + str(m0) + "&& Kst_892_0_MM <" + str(m1))
        mytrees["11p"+str(i)].Write()
        myfiles["11p"+str(i)].Close()
        
        myfiles["11n"+str(i)] = TFile(NTUPLE_PATH + "/2011n_" + str(m0) + "_" + str(m1) +".root", "recreate")
        mytrees["11n"+str(i)] = t2_11.CopyTree(cuts11+" && Kplus_ID < 0 && Kst_892_0_MM >=" + str(m0) + "&& Kst_892_0_MM <" + str(m1))
        mytrees["11n"+str(i)].Write()
        myfiles["11n"+str(i)].Close()
       
        myfiles["12p"+str(i)] = TFile(NTUPLE_PATH + "/2012p_" + str(m0) + "_" + str(m1) +".root", "recreate")
        mytrees["12p"+str(i)] = t2_12.CopyTree(cuts12+" && Kplus_ID > 0 && Kst_892_0_MM >=" + str(m0) + "&& Kst_892_0_MM <" + str(m1)) 
        mytrees["12p"+str(i)].Write()
        myfiles["12p"+str(i)].Close()
       
        myfiles["12n"+str(i)] = TFile(NTUPLE_PATH + "/2012n_" + str(m0) + "_" + str(m1) +".root", "recreate")
        mytrees["12n"+str(i)] = t2_12.CopyTree(cuts12+" && Kplus_ID < 0 && Kst_892_0_MM >=" + str(m0) + "&& Kst_892_0_MM <" + str(m1)) 
        mytrees["12n"+str(i)].Write()
        myfiles["12n"+str(i)].Close()
       
  
createTTrees(KpiBins23)
