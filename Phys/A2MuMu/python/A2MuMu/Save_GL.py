#!/usr/bin/env python
import CutsList
from ROOT import *
variables = TMVA_cut.variables_cont
from Urania import *
AccessPackage("Bs2MuMu")
import time   # time accounting
import getopt # command line parser
from smartpyROOT import *
from triggerclass import *
from SomeUtils.NewKarlen import *
from SomeUtils.someFunctions import *
from math import sqrt
from OurSites import MY_TUPLE_PATH as MY_PATH

signal_train, f1      = getTuple(MY_PATH + "kspi0mm_DTFMC12_Strip_1",thing = "BenderKspi0mumuSignal")
signal_test, f2      = getTuple(MY_PATH + "kspi0mm_DTFMC12_Strip_2",thing = "BenderKspi0mumuSignal")
bkg_train, f3      = getTuple(MY_PATH + "TIS_1", thing = "BenderKspi0mumuSignal")#getTuple("bkgMini", thing = "BenderKspi0mumuSignal/BenderKspi0mumuSignal")
bkg_test, f4     = getTuple(MY_PATH + "TIS_2", thing ="BenderKspi0mumuSignal" )#getTuple("bkgMini", thing = "BenderKspi0mumuSignal/BenderKspi0mumuSignal")

f_ = TFile(MY_PATH +"kspi0mm_DTFMC12_Strip_GL_1.root", "recreate")
t2 = signal_train.CopyTree(TMVA_cut.mycutSig)

s = channelData(fromRootToListDic(t2))#, labels = ["evt","B0_MM"] + variablesx))
f_.Close()
f_ = TFile(MY_PATH + "TIS_GL_1.root", "recreate")
t2 = bkg_train.CopyTree(TMVA_cut.mycutBkg)

b = channelData(fromRootToListDic(t2))#, labels = ["evt","B0_MM"] + variablesx))
f_.Close()
f_ = TFile(MY_PATH + "kspi0mm_DTFMC12_Strip_GL_2.root", "recreate")
t2 = signal_test.CopyTree(TMVA_cut.mycutSig)

s2 = channelData(fromRootToListDic(t2))#, labels = ["evt","B0_MM"] + variablesx))
f_.Close()
f_ = TFile(MY_PATH + "TIS_GL_2.root", "recreate")
t2 = bkg_test.CopyTree(TMVA_cut.mycutBkg)

b2 = channelData(fromRootToListDic(t2))#, labels = ["evt","B0_MM"] + variablesx))
f_.Close()
#BREAK

GL = NewKarlen(s,b,variables )
import cPickle
cPickle.dump(GL,file("./GL_data",'w'))

GL(b,"GLmva")
GL(s, "GLmva")

GL(b2,"GLmva")
GL(s2, "GLmva")

s.save(MY_PATH + "kspi0mm_DTFMC12_Strip_GL_1")
b.save(MY_PATH + "KsPi0MM_dataL0Tis_GL_1")
s2.save(MY_PATH + "kspi0mm_DTFMC12_Strip_GL_2")
b2.save(MY_PATH + "KsPi0MM_dataL0Tis_GL_2")

