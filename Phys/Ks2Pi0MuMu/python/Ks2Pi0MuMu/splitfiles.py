from ROOT import *
from SomeUtils.alyabar import *
from Urania import PDG                    
from random import *
from OurSites import *
import optparse
import sys

##MY_TUPLE_PATH = '~/cmtuser/local_Ks2Pi0MuMu/'
def split(filename, treename,mc):

    f = TFile(filename, "update")
    #f.ls()
    #dir = gFile.GetDirectory("BenderKspi0mumuSignal")
    #dir.ls()
    t = f.Get(treename)
    
    f1_name = filename.replace('.root', '_1.root')
    f2_name = filename.replace('.root', '_2.root')
    
    f1 = TFile(f1_name, "recreate")
    t1 = t.CloneTree(0)
    
    f2 = TFile(f2_name, "recreate")
    t2 = t.CloneTree(0)
    
    for entry in t:
        if int(mc) == 1:
            if entry.mo1 != 310 : continue
            if entry.mo2 != 310 : continue
            ## if not entry.mc_pi0_px : continue
            ## if not entry.mc_Gamma_px : continue
            ## if not entry.mc_gamma_px : continue
            ##if entry.mc_gamma_pz < 0: continue
            if(entry.mc_gamma_ez < 0): continue
            if(entry.mc_Gamma_ez < 0): continue
            ## if(entry.mc_g1_ez != entry.mc_gamma_ez and entry.mc_g1_ez != entry.mc_Gamma_ez): continue
            ## if(entry.mc_g2_ez != entry.mc_gamma_ez and entry.mc_g2_ez != entry.mc_Gamma_ez): continue

            pg1 = vector(entry.g1p1, entry.g1p2, entry.g1p3)
            pg2 = vector(entry.g2p1, entry.g2p2, entry.g2p3)    

            mc_p1x = entry.mc_Gamma_px*(abs(entry.g1p1 - entry.mc_Gamma_px) < abs(entry.g1p1 - entry.mc_gamma_px)) + entry.mc_gamma_px*(abs(entry.g1p1 - entry.mc_Gamma_px) > abs(entry.g1p1 - entry.mc_gamma_px))
            mc_p1y = entry.mc_Gamma_py*(abs(entry.g1p2 - entry.mc_Gamma_py) < abs(entry.g1p2 - entry.mc_gamma_py)) + entry.mc_gamma_py*(abs(entry.g1p2 - entry.mc_Gamma_py) > abs(entry.g1p2 - entry.mc_gamma_py))
            mc_p1z = entry.mc_Gamma_pz*(abs(entry.g1p3 - entry.mc_Gamma_pz) < abs(entry.g1p3 - entry.mc_gamma_pz)) + entry.mc_gamma_pz*(abs(entry.g1p3 - entry.mc_Gamma_pz) > abs(entry.g1p3 - entry.mc_gamma_pz))

            mc_p2x = entry.mc_Gamma_px*(abs(entry.g2p1 - entry.mc_Gamma_px) < abs(entry.g2p1 - entry.mc_gamma_px)) + entry.mc_gamma_px*(abs(entry.g2p1 - entry.mc_Gamma_px) > abs(entry.g2p1 - entry.mc_gamma_px))
            mc_p2y = entry.mc_Gamma_py*(abs(entry.g2p2 - entry.mc_Gamma_py) < abs(entry.g2p2 - entry.mc_gamma_py)) + entry.mc_gamma_py*(abs(entry.g2p2 - entry.mc_Gamma_py) > abs(entry.g2p2 - entry.mc_gamma_py))
            mc_p2z = entry.mc_Gamma_pz*(abs(entry.g2p3 - entry.mc_Gamma_pz) < abs(entry.g2p3 - entry.mc_gamma_pz)) + entry.mc_gamma_pz*(abs(entry.g2p3 - entry.mc_Gamma_pz) > abs(entry.g2p3 - entry.mc_gamma_pz))

        #Differences montecarlo truth - reconstructed momenta
            dp1x = abs((mc_p1x - pg1[0])/(mc_p1x+0.01)) #+0.01 so that it doesn't give error when mc_p1x (I assume 0.01 is a negligible quantity to add)
            dp1y = abs((mc_p1y - pg1[1])/(mc_p1y+0.01))
            dp2x = abs((mc_p2x - pg2[0])/(mc_p2x+0.01))
            dp2y = abs((mc_p2y - pg2[1])/(mc_p2y+0.01))

            ##if (max(dp1x,max(dp1y,max(dp2x,dp2y))) > 1.0): continue                                        

        rand = randint(0,1)
        if rand == 0:
            t1.Fill()
        
        else:
            t2.Fill()

    #t.Write("",TObject.kOverwrite)
    f1.Write()
    f2.Write()

    f1.Close()
    f2.Close()
    f.Close()

def main():
    parser = optparse.OptionParser()
    parser.add_option('-i', '--input', dest='input', help='input root file', default= MY_TUPLE_PATH+'kspi0mm_DTFMC12_Strip.root')
    parser.add_option('-t', '--tree', dest='tree', help='name of the ROOT tree inside the ROOT file', default='BenderKspi0mumuSignal/BenderKspi0mumuSignal')
    parser.add_option('-m', '--mc', dest='mc', help='mc = 0 for BG, mc = 1 for signal MC', default=1)

    (options, args) = parser.parse_args()

    split(options.input, options.tree, options.mc)


if __name__ == "__main__":
    main()
                                
