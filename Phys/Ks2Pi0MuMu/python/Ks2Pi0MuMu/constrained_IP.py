from ROOT import *
MY_PATH = "/scratch19/Kspi0/"
#f = TFile("~/w7folder/kspi0/Tuple_MC_Frankfurt.root")
f = TFile(MY_PATH + "KsPi0MM_dataL0Tis_1.root")
t = f.Get("T")
kPaula = TColor.GetColor("#ff99cc")
#f = TFile("bkgMini.root")
#t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
#BREAK
from SomeUtils.alyabar import *
from Urania import PDG
import Sym_constr_IP as IP_formulae
from sympy import nsolve, solve, mpmath,lambdify
h = TH1F("A","A", 100,0,1 )
hb = TH1F("B","B", 100, 0,1)
href = TH1F("ref","ref",100, 0,1)
mpmath.mp.dps = 10

MKs = PDG.K0.mass
mysubs = [(IP_formulae.mK0, MKs), (IP_formulae.mpi0, PDG.pi0.mass)]
myeqs = []
for equation in IP_formulae.eqset: myeqs.append(equation.subs(mysubs))
#CUT = 0

## Create lambdified versions
mylambs = []
for eq in myeqs:
    mylambs.append(lambdify( (IP_formulae.Mmumu,IP_formulae.ppi0,IP_formulae.pmmx,IP_formulae.pmmy,IP_formulae.pmmz,IP_formulae.x,IP_formulae.y,IP_formulae.z,IP_formulae.pi0x,IP_formulae.pi0y,IP_formulae.pi0z), eq, ('numpy')))

def getfunction(lamb, Mmumu, pi0,pdm,d):
    def out(px,py,pz):
        return lamb(Mmumu, vmod(pi0),pdm[0],pdm[1],pdm[2], d[0],d[1],d[2], px,py,pz)
    return out

                   

f2 = TFile("eraseme.root", "recreate")
t2 = t.CopyTree("(mu1_hitsInTT > 0.1) && (mu2_hitsInTT > 0.1) && (LF_time > 1)")
Ni = 0
N0inverse = 1./t2.GetEntries()
#BREAK
for entry in t2:
    Ni+=1
    print Ni
    print Ni*N0inverse
   # if entry.mo1 != 310 : continue
   # if entry.mo2 != 310 : continue
   # if not entry.mc_pi0_px: continue
   # if entry.mc_pi0_pz <0: continue
    #if 0:#CUT in [1,2, 12,13,26,33,34,35,43,50,63, 69, 70, 74] :
     #   CUT+=1 
      #  continue
#    print CUT
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
    #eventsubs = [(IP_formulae.Mmumu, Mmumu), (IP_formulae.ppi0, vmod(ppi0))]
    #eventsubs += [(IP_formulae.pmmx, pdm[0]) ,(IP_formulae.pmmy, pdm[1]), (IP_formulae.pmmz, pdm[2])]
    #eventsubs += [(IP_formulae.x, flight[0]) ,(IP_formulae.y, flight[1]), (IP_formulae.z, flight[2])]
    event_eqs = []
    for eq in mylambs:#myeqs:
        #event_eqs.append(eq.subs(eventsubs))
        event_eqs.append(getfunction(eq,Mmumu, ppi0, pdm,flight))
    try:
        #rot = nsolve(event_eqs, (IP_formulae.pi0x,IP_formulae.pi0y,IP_formulae.pi0z), (ppi0[0],ppi0[1],ppi0[2]))#,tol = 1e14)
        rot = mpmath.findroot(event_eqs, (ppi0[0],ppi0[1],ppi0[2]))#,tol = 1e14)
        
    except ValueError:
        print "Warning: No precise solution found, increasing the tolerance"
        rot = mpmath.findroot(event_eqs, (ppi0[0],ppi0[1],ppi0[2]),tol = 1e14)
        #rot = nsolve(event_eqs, (IP_formulae.pi0x,IP_formulae.pi0y,IP_formulae.pi0z), (ppi0[0],ppi0[1],ppi0[2]),tol = 1e14)
    except ZeroDivisionError:
        print "ZeroDivision Error. Momenta left uncorrected"
        rot = vector(ppi0[0],ppi0[1],ppi0[2])
    #rot = solve(event_eqs, [IP_formulae.pi0x,IP_formulae.pi0y,IP_formulae.pi0z])#, (ppi0[0],ppi0[1],ppi0[2]))
    #print "-------"
    #print ppi0
    #print rot
    h.Fill(dpr(PV, SV, ppi0 + pdm))
    href.Fill(entry.KS_IP)
    xi = ACO(flight, BigPi)
    #sinxi = sin(xi)
    ppi0 = vector(float(rot[0]), float(rot[1]),float(rot[2]))
    hb.Fill(dpr(PV, SV, ppi0 + pdm))
#    CUT+=1
    if Ni > 15000: break
hb.SetLineColor(kBlack)
hb.SetLineWidth(3)
hb.Draw()

h.SetLineColor(kRed)
h.Draw("same")
href.Draw("same")



   

    
 # [405.5089867]
#[ 428.698487]
#[8107.222907]  
    
#[405.8337805]
#[ 429.690889]
#[8107.175694]
