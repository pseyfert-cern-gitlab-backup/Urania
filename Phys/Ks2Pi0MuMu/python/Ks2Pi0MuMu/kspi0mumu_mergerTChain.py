from Urania import *
AccessPackage("Bs2MuMu")
from triggerclass import *
from ROOT import *
from smartpyROOT import *
from OurSites import MY_TUPLE_PATH as PATH

Numer = {"_Up_":634, "_Down_":572}

ch = TChain("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
chpipi = TChain("Ks2pipi/Ks2pipi")
def do(fname):
    f = TFile(fname)
    if not f:
        print "SHIT, you deleted the file, malaka"
        return
    ch.Add(fname)
    chpipi.Add(fname)

for MAGNET in Numer.keys():
    for i in range(Numer[MAGNET]):
        fname = PATH + "kspi0mumu_ntupleData12" + MAGNET + str(i) + ".root"
        do(fname)


ch.Merge(PATH + "Sig_merged.root")
chpipi.Merge(PATH + "Kspipi_merged.root")
