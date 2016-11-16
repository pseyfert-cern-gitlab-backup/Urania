from ROOT import *
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from triggerclass import *

fname1 = "/home3/veronika.chobanova/Kspi0/Data_2011_FULL_MagUp_1"#.root" ## DMS: Ks2pipi. OK
fname2 = "/home3/veronika.chobanova/Kspi0/Data_2011_FULL_MagUp_2"#.root" ## DMS : Ks2pipi. OK
fname3 = "/scratch18/Kspi0/Data_2012_FULL_MagDown"#.root" ## DMS: Ks2pipi. OK
fname4 = "/scratch18/Kspi0/Data_2012_FULL_MagUp"#.root" ## DMS: Ks2pipi. OK

#f = TFile("/scratch18/Kspi0/" + fname)
#t = f.Get("BenderKspi0mumuSignal/BenderKspi0mumuSignal")
#t = f.Get("Ks2pipi/Ks2pipi")
ch1 = channelData(fname1, name2 = "BenderKspi0mumuSignal", labels = ["evt","evtNum","runNum"])
ch2 = channelData(fname2, name2 = "BenderKspi0mumuSignal", labels = ["evt","evtNum","runNum"])
ch3 = channelData(fname3, name2 = "Ks2pipi/Ks2pipi", labels = ["evt","evtNum","runNum"])
ch4 = channelData(fname4, name2 = "Ks2pipi/Ks2pipi", labels = ["evt","evtNum","runNum"])

#ch = channelData(ch1+ch2+ch3+ch4)
ch = channelData(ch1+ch2)


def candidates_per_event(ch):
    ch.desagrupate()
    N0 = len(ch)
    ch.agrupateInEvents()
    return N0*1./len(ch)

def check_duplicates(ch):
    d , d2 = {},  {}
    l = []
    out = []
    out_ = []
    ch.desagrupate()
    N0 = len(ch)
    for entry in ch:
        run, evt, evt_ = entry["runNum"], entry["evtNum"], entry["evt"]
        if run not in d.keys(): d[run], d2[run] = [], []
        if evt not in d[run]: 
            d[run].append(evt)
            out.append(entry)
        if evt_ not in d2[run]:
            d2[run].append(evt_)
            out_.append(entry)
    out = channelData(out)
    out_ = channelData(out_)
    #N0 = len(ch)
    print "Candidates per event", N0*1./len(out)#*1./len(ch)
    print "Candidates per event (xcheck)", N0*1./len(out_)#*1./len(ch)
    
    #ch.agrupateInEvents()
    print "Expected was ", candidates_per_event(ch)
    #return out
        #else:
         #   d2[run].append(evt)
    #for entry in t:
     #   run, evt = entry.runNum, entry.evtNum
     #   if evt in d2[run]:
      #      l.append([run, evt, entry.evt, getattr(entry,"Bmass")])
    #l.sort()
    #for x in l: print x
        
check_duplicates(ch)
