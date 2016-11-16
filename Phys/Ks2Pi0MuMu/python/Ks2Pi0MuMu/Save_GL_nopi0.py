#!/usr/bin/env python
#import TMVA_cut_conf4 as TMVA_cut
import TMVA_cut
from ROOT import *
variables = TMVA_cut.variables_cont_nopi0
from Urania import *
AccessPackage("Bs2MuMu")
import time   # time accounting
import getopt # command line parser
from smartpyROOT import *
from triggerclass import *
from SomeUtils.NewKarlen import *
from SomeUtils.someFunctions import *
from math import sqrt

REMOVEMULT = 0
#mylabels =  []#["evt","M_VC", "evtNum","runNum", "KS_l0phys_tis", "KS_l1phys_tis","KS_l2phys_tis"] + variables + TMVA_cut_ml.variables_other

#signal_train, f1      = getTuple("/scratch19/Kspi0/MC_FULL_1")#,thing = "BenderKspi0mumuSignal") ##to be changed
#signal_test, f2      = getTuple("/scratch19/Kspi0/MC_FULL_2")#,thing = "BenderKspi0mumuSignal")
#bkg_train, f3      = getTuple("/scratch19/Kspi0/TIS_FULL_1")#, thing = "BenderKspi0mumuSignal") 
#bkg_test, f4     = getTuple("/scratch19/Kspi0/TIS_FULL_2")#, thing = "BenderKspi0mumuSignal")

signal_train, f1      = getTuple("./MC15_Sim09_PARTIAL_1",thing = "Ks2pizeromm_as_V0") ##to be changed
signal_test, f2       = getTuple("./MC15_Sim09_PARTIAL_2",thing = "Ks2pizeromm_as_V0")
bkg_train, f3         = getTuple("./Data_2016_PARTIAL_1", thing = "Ks2pizeromm_as_V0") 
bkg_test, f4          = getTuple("./Data_2016_PARTIAL_2", thing = "Ks2pizeromm_as_V0")
#BREAK
def remove_duplicates(ch):
    d  = {}
    l = []
    out = []
    for entry in ch:
        run, evt = entry["runNum"], entry["evtNum"]
        if run not in d.keys(): d[run]= []#, []
        if evt not in d[run]:
            d[run].append(evt)
            out.append(entry)
    out = channelData(out)
    N0 = len(ch)
    print "Kept ", len(out)*1./len(ch)
    ch.agrupateInEvents()
    print "Expected was ", len(ch)*1./N0
    return out
        #else:
         #   d2[run].append(evt)
    #for entry in t:
     #   run, evt = entry.runNum, entry.evtNum
     #   if evt in d2[run]:
      #      l.append([run, evt, entry.evt, getattr(entry,"Bmass")])
    #l.sort()
    #for x in l: print x
        
            
#    return d, d2,l
f_ = TFile("./dummy.root", "recreate")
t2 = bkg_train.CopyTree(TMVA_cut.mycutBkg_nopi0)
b = channelData(fromRootToListDic(t2))##,labels = mylabels))# labels = ["evt","B0_MM"] + variablesx))
if REMOVEMULT: b = remove_duplicates(b)
f_.Close()
f_ = TFile("./dummy.root", "recreate")
t2 = signal_train.CopyTree(TMVA_cut.mycutSig_nopi0)
s = channelData(fromRootToListDic(t2))#, labels = mylabels))
if REMOVEMULT: s = remove_duplicates(s)
f_.Close()

f_ = TFile("./dummy.root", "recreate")
t2 = signal_test.CopyTree(TMVA_cut.mycutSig_nopi0)

s2 = channelData(fromRootToListDic(t2))#,labels = mylabels))# labels = ["evt","B0_MM"] + variablesx))
if REMOVEMULT: s2 = remove_duplicates(s2)
f_.Close()
f_ = TFile("./dummy.root", "recreate")
t2 = bkg_test.CopyTree(TMVA_cut.mycutBkg_nopi0)

b2 = channelData(fromRootToListDic(t2))#,labels = mylabels))# labels = ["evt","B0_MM"] + variablesx))
if REMOVEMULT: b2 = remove_duplicates(b2)
f_.Close()

Ns = len(s2)
Nb = len(b2)
tis = trigger()
#tis.addCut("V0_l0phys_tis>0")
#tis.addCut("V0_l1phys_tis>0")
#tis.addCut("V0_l2phys_tis>0")
GL = NewKarlen(s,b,variables )
print "after training the GL"
import cPickle
cPickle.dump(GL,file("./GL_data",'w'))

GL(b,"GLmva")
print "after first GL"
b.save("Data16_PARTIAL_GL_1")
GL(s, "GLmva")
print "after second GL"
s.save("MC15_Sim09_PARTIAL_GL_1") ##to be changed
#b2 = tis(b2)
#b2.desagrupate()

GL(b2,"GLmva")
b2.save("Data16_PARTIAL_GL_2")
print "after third GL"
GL(s2, "GLmva")
s2.save("MC15_Sim09_PARTIAL_GL_2")

#print "after fourth GL"
#print "before saving"

