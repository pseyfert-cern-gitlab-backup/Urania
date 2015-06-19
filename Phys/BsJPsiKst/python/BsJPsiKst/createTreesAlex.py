from ROOT import *
from OurSites import *
from Cuts2013 import cuts_loose_2011 as cuts11, cuts_loose_2012 as cuts12
NTUPLE_PATH = "~/NTuplesFast/"
def createTTrees(KpiBins = []):
    f11 = TFile("~/w7folder/NTuples/Bs_Jpsi_Kst_2013/Bd2JpsiKstar_biased_Selected_20120202_sw.root")
    t2_11 = f11.Get("merged")
    
    
    myfiles = {}
    mytrees = {}
    for i in range(len(KpiBins)-1):
        m0 = KpiBins[i]
        m1 = KpiBins[i+1]
        myfiles["11p"+str(i)] = TFile(NTUPLE_PATH + "/Alex2011p_" + str(m0) + "_" + str(m1) +".root", "recreate")
        mytrees["11p"+str(i)] = t2_11.CopyTree("KstarFlavour > 0 && mdau2 >=" + str(m0) + "&& mdau2 <" + str(m1))
        mytrees["11p"+str(i)].Write()
        myfiles["11p"+str(i)].Close()
        
        myfiles["11n"+str(i)] = TFile(NTUPLE_PATH + "/Alex2011n_" + str(m0) + "_" + str(m1) +".root", "recreate")
        mytrees["11n"+str(i)] = t2_11.CopyTree("KstarFlavour < 0 && mdau2 >=" + str(m0) + "&& mdau2 <" + str(m1))
        mytrees["11n"+str(i)].Write()
        myfiles["11n"+str(i)].Close()
       
        
