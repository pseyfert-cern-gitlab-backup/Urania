from ROOT import *
from SomeUtils.alyabar import *
from Urania import PDG                    
import optparse
from OurSites import *

PARSER = 0

gROOT.ProcessLine(
"struct MyStruct {\
   Float_t     structcTh1;\
   Float_t     structcTh2;\
   Float_t     structPhi;\
   Float_t     structK_dec_angle;\
   Float_t     structXi;\
   Float_t     structAlpha;\
};" );

def angles(filename, treename, sample):
    SAMPLE = int(float(sample))

    f = TFile(MY_TUPLE_PATH + filename, "update")
 
    t = f.Get(treename)

    h = TH1F("A","A", 100, 400, 600)
    hb = TH1F("B","B", 100, 400, 600)
    hbVC = TH1F("BVC","BVC", 100, 400, 600)

    href = TH1F("A","A", 100, 400, 600)
    hpi0 = TH1F("pi0", "pi0", 100, 100, 170)
    hTh1 = TH1F("c1","c1", 100, -1,1)
    hTh2 = TH1F("c2","c2", 100, -1,1)
    hPhi = TH1F("phi","phi", 100, -pi,pi)

    mystruct = MyStruct()
    
    branch_cTh1 = t.Branch("cTh1", AddressOf(mystruct, "structcTh1"), "cTh1/F")
    branch_cTh2 = t.Branch("cTh2", AddressOf(mystruct, "structcTh2"), "cTh2/F")
    branch_Phi = t.Branch("Phi", AddressOf(mystruct, "structPhi"), "Phi/F")
    branch_K_dec_angle = t.Branch("K_dec_angle", AddressOf(mystruct, "structK_dec_angle"), "K_dec_angle/F")
    branch_Xi = t.Branch("Xi", AddressOf(mystruct, "structXi"), "Xi/F")
    branch_Alpha = t.Branch("Alpha", AddressOf(mystruct, "structAlpha"), "Alpha/F")

    for entry in t:
        if entry.mo1 != 310 : continue
        if entry.mo2 != 310 : continue
        ## if not entry.mc_pi0_px : continue
        ## if not entry.mc_Gamma_px : continue
        ## if not entry.mc_gamma_px : continue
        ## if entry.mc_gamma_pz < 0: continue
        if(entry.mc_gamma_ez < 0): continue
        if(entry.mc_Gamma_ez < 0): continue
        ## if(entry.mc_g1_ez != entry.mc_gamma_ez and entry.mc_g1_ez != entry.mc_Gamma_ez): continue
        ## if(entry.mc_g2_ez != entry.mc_gamma_ez and entry.mc_g2_ez != entry.mc_Gamma_ez): continue
        
        print "entry"

        pmu1 = vector(entry.mu1p1, entry.mu1p2, entry.mu1p3)
        pmu2 = vector(entry.mu2p1, entry.mu2p2, entry.mu2p3)
        pg1 = vector(entry.g1p1, entry.g1p2, entry.g1p3)
        pg2 = vector(entry.g2p1, entry.g2p2, entry.g2p3)
        Mpizero = sqrt(IM2(pg1,pg2, 0, 0)) ## IM2 = invariant mass squared
        Mmumu = sqrt(IM2(pmu1,pmu2, PDG.muon.mass, PDG.muon.mass)) ## IM2 = invariant mass squared
        MKs = sqrt(IM2 ( pmu1+pmu2,  pg1 + pg2, Mmumu, PDG.pi0.mass))# Mpizero))
        
        h.Fill(MKs)
        href.Fill(entry.KSmass)
        hpi0.Fill( Mpizero)
        
        PV = vector(entry.PV1,entry.PV2,entry.PV3)
        SV = vector(entry.SV1,entry.SV2,entry.SV3)
        flight = vunit(SV-PV)
        pdm = pmu1 + pmu2
        
        xu = vcross(vector(0,1,0),flight)
        yu = vcross(flight,xu)
        pdmx_prime = vdot(pdm, xu)
        pdmy_prime = vdot(pdm, yu)
        pdmz_prime = vdot(pdm, flight)
        
        p0 = pg1 + pg2
  
        PG1 = TLorentzVector(pg1[0],pg1[1],pg1[2], vmod(pg1))
        PG2 = TLorentzVector(pg2[0],pg2[1],pg2[2], vmod(pg2))
         
        PM1 = TLorentzVector(pmu1[0],pmu1[1],pmu1[2], sqrt(vdot(pmu1,pmu1) + PDG.muon.mass**2))
        PM2 = TLorentzVector(pmu2[0],pmu2[1],pmu2[2], sqrt(vdot(pmu2,pmu2) + PDG.muon.mass**2))
        
        cTh1_evt, cTh2_evt, Phi_evt = HelicityAngles(PG1,PG2,PM1,PM2)
        
        mystruct.structcTh1 = cTh1_evt
        mystruct.structcTh2 = cTh2_evt
        mystruct.structPhi = Phi_evt
        
        v1 = [vmod(p0), p0]
        v2 = [sqrt(Mmumu**2+vdot(pdm,pdm)), pdm]
        mystruct.structK_dec_angle = angleToflight(v1,v2)
        
        BigPi = vcross(pdm, p0)
        mystruct.structXi = ACO(flight, BigPi)
        
        mystruct.structAlpha = ACO(flight, pdm+p0)
        
        hTh1.Fill(cTh1_evt)
        hTh2.Fill(cTh2_evt)
        hPhi.Fill(Phi_evt)
        
        branch_cTh1.Fill()
        branch_cTh2.Fill()
        branch_Phi.Fill()
        branch_K_dec_angle.Fill()
        branch_Xi.Fill()
        branch_Alpha.Fill()
        
    t.Write("",TObject.kOverwrite)
        
    f.Write()
    f.Close()

def main():
    parser = optparse.OptionParser()
    parser.add_option('-i', '--input', dest='input', help='input root file', default='./kspi0mm_DTFMC12_Strip_2.root')
    parser.add_option('-t', '--tree', dest='tree', help='name of the ROOT tree inside the ROOT file', default='BenderKspi0mumuSignal')
    parser.add_option('-s', '--sample', dest="sample", help='input sample - 0 with pi0, 1 without pi0 (V0)', default=1)    
                        
    (options, args) = parser.parse_args()

if PARSER:
    def main():
        parser = optparse.OptionParser()
        parser.add_option('-i', '--input', dest='input', help='input root file', default='./Tuple_MC_Frankfurt.root')
        parser.add_option('-t', '--tree', dest='tree', help='name of the ROOT tree inside the ROOT file', default='T')
        parser.add_option('-s', '--sample', dest="sample", help='input sample - 0 with pi0, 1 without pi0 (V0)', default=1)
        
        (options, args) = parser.parse_args()

        angles(options.input, options.tree)    


    if __name__ == "__main__":
        main()

else:
    angles("TIS_merged_december.root","BenderKspi0mumuSignal")
