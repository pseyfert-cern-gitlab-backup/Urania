from Urania import *
AccessPackage("Bs2MuMu")
from triggerclass import *
from ROOT import *
from smartpyROOT import *
from OurSites import MY_TUPLE_PATH as PATH
EVT = 0
EVTpipi = 0
ch = []
chpipi = []
DO_SIGNAL = 1
DO_NORM = 1 * (not DO_SIGNAL)
MAGNET = "_Down_"
Numer = {"_Up_":634, "_Down_":572}
conf = "merge_data_jobs"
#conf = "merge_MC_jobs"
#conf = "hostia"
if conf == "merge_data_jobs":
    for i in range(Numer[MAGNET]):
        f = TFile(PATH + "kspi0mumu_ntupleData12" + MAGNET + str(i) + ".root")
        if not f:
            print "SHIT, you deleted the file, malaka"
            continue
        t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
        tpipi = f.Get("Ks2pipi/Ks2pipi")
        if t and DO_SIGNAL:
            chi = channelData(fromRootToListDic(t))
            for j in range(len(chi)):
                chi[j]["evt"] += EVT
            ch += chi
            EVT = max(chi.takeKey("evt")) + 1
        if tpipi and DO_NORM:
            chipipi = channelData(fromRootToListDic(tpipi))
            for j in range(len(chipipi)):
                chipipi[j]["evt"] += EVTpipi
            chpipi += chipipi
            EVTpipi = max(chipipi.takeKey("evt")) + 1
        print i
    
    ch = channelData(ch)
    if ch: ch.save(PATH + "KsPi0MM_data" + MAGNET)
    if chpipi:
        chpipi = channelData(chpipi)
        chpipi.save(PATH + "KsPiPi_data" + MAGNET)
    
elif conf == "merge_MC_jobs":
    ch1 = channelData(PATH + "kspi0mm_DTFMC12_Strip_Up", name2 = "BenderKspi0mumuSignal/BenderKspi0mumuSignal")
    ch2 = channelData(PATH + "kspi0mm_DTFMC12_Strip_Down", name2 = "BenderKspi0mumuSignal/BenderKspi0mumuSignal")
    EVT = max(ch1.takeKey("evt")) + 1
    for i in range(len(ch2)):
        ch2[i]["evt"] += EVT

    ch = ch1+ ch2
    ch = channelData(ch)
    ch.save("Tuple_MC")

else:
    name1 = "Data12_Down__TIS"*DO_SIGNAL + "KsPiPi_data_Down_"*DO_NORM
    name2 = "Data12_Up__TIS"*DO_SIGNAL + "KsPiPi_data_Up_"*DO_NORM
    ch1 = channelData(PATH+ name1)
    ch2 = channelData(PATH + name2)
    EVT = max(ch1.takeKey("evt")) + 1
    for i in range(len(ch2)):
        ch2[i]["evt"] += EVT

    ch = ch1+ ch2
    ch = channelData(ch)
    ch.save(PATH + "TIS"*DO_SIGNAL + "PiPi"*DO_NORM + "_merged")

    
