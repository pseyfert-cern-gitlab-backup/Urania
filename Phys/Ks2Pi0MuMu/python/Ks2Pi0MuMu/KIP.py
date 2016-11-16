from ROOT import *
kPaula = TColor.GetColor("#ff99cc")
#t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
from SomeUtils.alyabar import *
from Urania import PDG
import Sym_constr_IP as IP_formulae
from sympy import nsolve, solve, mpmath,lambdify
import optparse
from OurSites import *

gROOT.ProcessLine(
"struct MyStruct {\
    Float_t     structKIP;\
};" );

def getfunction(lamb, Mmumu, pi0,pdm,d):
    def out(px,py,pz):
        return lamb(Mmumu, vmod(pi0),pdm[0],pdm[1],pdm[2], d[0],d[1],d[2], px,py,pz)
    return out

def KIP(filename, treename):                   
    f = TFile(MY_TUPLE_PATH + filename, "update")
    t = f.Get(treename)

    struct = MyStruct()

    branch_KIP = t.Branch("KIP", AddressOf(struct, "structKIP"), "KIP/F")

    mpmath.mp.dps = 10

    MKs = PDG.K0.mass
    mysubs = [(IP_formulae.mK0, MKs), (IP_formulae.mpi0, PDG.pi0.mass)]
    myeqs = []
    for equation in IP_formulae.eqset: myeqs.append(equation.subs(mysubs))

    ## Create lambdified versions
    mylambs = []
    for eq in myeqs:
        mylambs.append(lambdify( (IP_formulae.Mmumu,IP_formulae.ppi0,IP_formulae.pmmx,IP_formulae.pmmy,IP_formulae.pmmz,IP_formulae.x,IP_formulae.y,IP_formulae.z,IP_formulae.pi0x,IP_formulae.pi0y,IP_formulae.pi0z), eq, ('numpy')))
        
    Ni = 0
    N0inverse = 1./t.GetEntries()
    #BREAK
    for entry in t:
        Ni+=1
        if(Ni%1000 == 0):
            print Ni
            print Ni*N0inverse

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

        pmu1 = vector(entry.mu1p1, entry.mu1p2, entry.mu1p3)
        pmu2 = vector(entry.mu2p1, entry.mu2p2, entry.mu2p3)
        pg1 = vector(entry.g1p1, entry.g1p2, entry.g1p3)
        pg2 = vector(entry.g2p1, entry.g2p2, entry.g2p3)
        Mpizero = sqrt(IM2(pg1,pg2, 0, 0)) ## IM2 = invariant mass squared
        Mmumu = sqrt(IM2(pmu1,pmu2, PDG.muon.mass, PDG.muon.mass)) ## IM2 = invariant mass squared
    
        PV = vector(entry.PV1,entry.PV2,entry.PV3)
        SV = vector(entry.SV1,entry.SV2,entry.SV3)
        flight = vunit(SV-PV)
        pdm = pmu1 + pmu2
        ppi0 = pg1 + pg2
        BigPi = vcross(pdm, ppi0)

        event_eqs = []
        for eq in mylambs:#myeqs:
            event_eqs.append(getfunction(eq,Mmumu, ppi0, pdm,flight))
        try:
            rot = mpmath.findroot(event_eqs, (ppi0[0],ppi0[1],ppi0[2]))#,tol = 1e14)    
        except ValueError:
            ##print "Warning: No precise solution found, increasing the tolerance"
            rot = mpmath.findroot(event_eqs, (ppi0[0],ppi0[1],ppi0[2]),tol = 1e14)
        except ZeroDivisionError:
            ##print "ZeroDivision Error. Momenta left uncorrected"
            rot = vector(ppi0[0],ppi0[1],ppi0[2])


        xi = ACO(flight, BigPi)
        ppi0 = vector(float(rot[0]), float(rot[1]),float(rot[2]))
        struct.structKIP = dpr(PV, SV, ppi0 + pdm)
        branch_KIP.Fill()

         #       if Ni > 150: break
    
    t.Write("",TObject.kOverwrite)

    f.Write()
    f.Close()

def main():
    parser = optparse.OptionParser()
    parser.add_option('-i', '--input', dest='input', help='input root file', default='./kspi0mm_DTFMC12_Strip_1.root')
    parser.add_option('-t', '--tree', dest='tree', help='name of the ROOT tree inside the ROOT file', default='BenderKspi0mumuSignal')
    
    (options, args) = parser.parse_args()

    KIP(options.input, options.tree)


if __name__ == "__main__":
    main()
                                    
