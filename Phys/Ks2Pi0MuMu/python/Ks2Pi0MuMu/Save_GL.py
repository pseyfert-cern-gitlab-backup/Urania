#!/usr/bin/env python
import TMVA_cut
from ROOT import *
import os, sys
#variables = ["DOCA", "mu1ips", "mu2ips", "Phi", "cTh1", "K_dec_angle", "KSips", "LF_time", "KS_pt", "pi0mass", "Alpha", "Xi", "KIP", "mu1_probNNmu", "mu2_probNNmu"]
SAMPLE = int(float(sys.argv[1]))
if SAMPLE == 1:
    variables = TMVA_cut.variables_cont_nopi0
    sig_cut = TMVA_cut.mycutSig_nopi0
    bkg_cut = TMVA_cut.mycutBkg_nopi0
else:
    variables = TMVA_cut.variables_cont
    sig_cut = TMVA_cut.mycutSig
    bkg_cut = TMVA_cut.mycutBkg
    
from Urania import *
AccessPackage("Bs2MuMu")
import time   # time accounting
import getopt # command line parser
from smartpyROOT import *
from triggerclass import *
from SomeUtils.NewKarlen import *
from SomeUtils.someFunctions import *
from math import sqrt
from OurSites import MY_TUPLE_PATH
import cPickle

f1_name = MY_TUPLE_PATH + "kspi0mumu_ntupleMC12_Up_V0_1"
f2_name = MY_TUPLE_PATH + "kspi0mumu_ntupleMC12_Up_V0_2"
f3_name = MY_TUPLE_PATH + "kspi0mumu_ntupleData15_TIS_1"
f4_name = MY_TUPLE_PATH + "kspi0mumu_ntupleData15_TIS_2"

signal_train, f1      = getTuple(f1_name,thing = "Ks2pizeromm_as_V0")
signal_test, f2      = getTuple(f2_name,thing = "Ks2pizeromm_as_V0")
bkg_train, f3      = getTuple(f3_name, thing = "Ks2pizeromm_as_V0")
bkg_test, f4     = getTuple(f4_name, thing = "Ks2pizeromm_as_V0")

f_ = TFile("/tmp/dummy.root", "recreate")
t2 = signal_train.CopyTree(sig_cut)

s = channelData(fromRootToListDic(t2))#, labels = ["evt","B0_MM"] + variablesx))
f_.Close()
f_ = TFile("/tmp/dummy.root", "recreate")
t2 = bkg_train.CopyTree(bkg_cut)

b = channelData(fromRootToListDic(t2))#, labels = ["evt","B0_MM"] + variablesx))
f_.Close()
f_ = TFile("/tmp/dummy.root", "recreate")
t2 = signal_test.CopyTree(sig_cut)

s2 = channelData(fromRootToListDic(t2))#, labels = ["evt","B0_MM"] + variablesx))
f_.Close()
f_ = TFile("/tmp/dummy.root", "recreate")
t2 = bkg_test.CopyTree(bkg_cut)

b2 = channelData(fromRootToListDic(t2))#, labels = ["evt","B0_MM"] + variablesx))
f_.Close()

GL = NewKarlen(s,b,variables )
if SAMPLE == 1:
    cPickle.dump(GL,file("./GL_data_nopi0",'w'))
else:
    cPickle.dump(GL,file("./GL_data",'w'))

GL(b,"GLmva")
GL(s,"GLmva")

GL(b2,"GLmva")
GL(s2,"GLmva")

s.save(f1_name+"_GL") ##to be changed
b.save(f3_name+"_GL")
s2.save(f2_name+"_GL")
b2.save(f4_name+"_GL")
