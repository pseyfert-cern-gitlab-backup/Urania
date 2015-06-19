from ROOT import *
from Cuts2013 import cuts_loose_2011 as cuts11, cuts_loose_2012 as cuts12
import os
def createTTrees():
    f11 = TFile(os.environ["HOME"] + "/vol5/Bs_Jpsi_Kst_2013/MagUpAndDown3500GeVReco14s20r1dv33r4_1019pb_StrippingBetaSBs2JpsiKstarWideLine_2011_BDTG_Loose_wCosines.root")
    
    t2_11 = f11.Get("DecayTree/DecayTree")
    
    f12 = TFile(os.environ["HOME"] + "/vol5/Bs_Jpsi_Kst_2013/MagUpAndDown4000GeVReco14s20r0p1dv33r4_2062pb_StrippingBetaSBs2JpsiKstarWideLine_2012_BDTG_Loose_wCosines.root")
    t2_12 = f12.Get("DecayTree/DecayTree")
    
    
    f12p=TFile(os.environ["HOME"] + "/vol5/Bs_Jpsi_Kst_2013/2012p.root","recreate")
    t12p=t2_12.CopyTree(cuts12+" && Kplus_ID > 0")
    t12p.Write()
    f12p.Close()
    f12n=TFile(os.environ["HOME"] + "/vol5/Bs_Jpsi_Kst_2013/2012n.root","recreate")
    t12n=t2_12.CopyTree(cuts12+" && Kplus_ID < 0")
    t12n.Write()
    f12n.Close()
    f11p=TFile(os.environ["HOME"] + "/vol5/Bs_Jpsi_Kst_2013/2011p.root","recreate")
    t11p=t2_11.CopyTree(cuts11+" && Kplus_ID > 0")
    t11p.Write()
    f11p.Close()
    f11n=TFile(os.environ["HOME"] + "/vol5/Bs_Jpsi_Kst_2013/2011n.root","recreate")
    t11n=t2_11.CopyTree(cuts11+" && Kplus_ID < 0")
    t11n.Write()
    f11n.Close()
