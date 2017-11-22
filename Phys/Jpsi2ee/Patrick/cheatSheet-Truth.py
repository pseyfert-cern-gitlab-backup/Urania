from AllMacroes import *
from ROOT import *

def CutEff(T,cut,den):
    """
    Cut eff returns events and efficiency
    """
    num = 1.0*T.GetEntries(cut)
    return [int(num), efficiency(num,den)]

def printLine(var,nMu,nE):
#    print var,nMu,nE
    print var, " & ", nMu[0], " & ",
    # printVal(nMu[1])
    print "{:.1f}".format(100*nMu[1][0]),
    print "\% & ", nE[0], " & ", 
    # printVal(nE[1])
    print "{:.1f}".format(100*nE[1][0]),
    print "\% &",
    printVal(ratio(nE[1],nMu[1]))
    print " \\\\"

def theTable(M,E,myvars,nstart):
    muCut = "1"
    eCut = "1"
    if (myvars[0][0]=="Selected"): # selection tuple
        nMu = [nstart[0],0]
        nE = [nstart[1],0]
#        print "nMu and nE ", nMu, nE
    else:
        nMu = CutEff(M,muCut,nstart[0])
        nE  = CutEff(E,eCut,nstart[1])
    print "All & ", nstart[0], " &  & ", nstart[1], " &  & \\\\" 
    for var in myvars:
        if ("Mass range"==var): muCut = muCut+" && (Psi_M>2946.916 && Psi_M<3246.916)"
        else: muCut = muCut+" && ("+var[1]+")"
        eCut = eCut+" && ("+var[1].replace("mu","e")+")"
#        print "Getting cuteff vs", nMu[0], nE[0]
        nMu = CutEff(M,muCut,nMu[0])
        nE  = CutEff(E,eCut,nE[0])
        printLine(var[0],nMu,nE)
    nMu = CutEff(M,muCut,nstart[0])
    nE  = CutEff(E,eCut,nstart[1])
    print " \\hline"
    printLine("Overall", nMu,nE)
    print " \\hline\\hline"
    return [ nMu[0], nE[0] ]

dir = "root://eoslhcb.cern.ch//eos/lhcb/user/p/pkoppenb/Jpsi2ee/" # CERN
dir = "/project/bfys/pkoppenb/Jpsi2ee/"                           # Nikhef
_ee = TFile.Open(dir+"Jpsi2ee-MC-2016-1536.root")
_mm = TFile.Open(dir+"Jpsi2mumu-MC-2016-1545.root")
_ee.ls()
mcE = _ee.Get("MCTuplePsi/MCDecayTree")
mcM = _mm.Get("MCTuplePsi/MCDecayTree")
rE = _ee.Get("EmulatedTrigger_Tuple/DecayTree")
rM = _mm.Get("EmulatedTrigger_Tuple/DecayTree")

#mcE.Draw("eminus_Reconstructible")
#mcE.Draw("eminus_Reconstructed")
nstart = [mcM.GetEntries(), mcE.GetEntries() ] 
# I want a sorted dictionary, actually
myvars = [[ "Reconstuctible" ,  "muplus_Reconstructible==2 && muminus_Reconstructible==2"],
          [ "Reconstructed" ,  "muplus_Reconstructed==1 && muminus_Reconstructed==1"],
          [ "$\\ell$ $\\pt>500\\mev$", "muminus_TRUEPT>500 && muplus_TRUEPT>500" ],
          [ "\\jpsi $\\pt>2500\\mevc$", "J_psi_1S_TRUEPT>2500"],
            ]
print 
n2=theTable(mcM,mcE,myvars,nstart)
rapidity = "0.5*log((Psi_PE+Psi_PZ)/(Psi_PE-Psi_PZ))"
myvars3 = [
    [ "Selected", "Psi_BKGCAT==0 || Psi_BKGCAT==50 || Psi_BKGCAT==60"],
    [ "Rapidity range" ,  "2<"+rapidity+" && "+rapidity+"<4.5"],
    [ "\\pt range" ,  "Psi_PT<14000 && Psi_PT>2500"],
    [ "Mass range", "Psi_M>1996.916 && Psi_M<4196.916"],
    [ "$\\ell$ $\\pt>900\\gevc$" ,  "(muplus_PT>900 || muminus_PT>900)"],
    [ "$\\ell$ $\\pt>700\\gevc$" ,  "(muplus_PT>700 && muminus_PT>700)"],
    [ "$\\ell$ $p>3\\gevc$" ,  "(muplus_PE>3000 && muminus_PE>3000)"],
    [ "$\\ell$ $p<500\\gevc$" ,  "(muplus_PE<500000 && muminus_PE<500000)"],
    ]   
print "% ", # to comment out next line
r=theTable(rM,rE,myvars3,n2)
printLine("Total",[r[0],efficiency(r[0],nstart[0])],[r[1],efficiency(r[1],nstart[1])])

