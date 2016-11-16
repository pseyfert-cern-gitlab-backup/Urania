from Urania import *
AccessPackage("Bs2MuMu")
from SomeUtils.Generator import *
from triggerclass import *
from ROOT import *
from smartpyROOT import *


folder ="~/vol5/new_LB/"
year = "2012"
main_source = folder + year +"/MC_forInjection" ### Root fle (w/o extension) to be used as a source. Files available in ~diegoms/vol5/
treename = "DecayTree/DecayTree"

t,f = getTuple(main_source,thing = treename)
f2 = TFile("/tmp/eraseme.root","recreate")
keys_ = ["helcosthetaK","helcosthetaL","B0_Phi","wMC", "B0_MM", "Kst_892_0_MM", "Kplus_ID"] ### Variables that we want to generate

### Create different source samples for positive and negative kaons (perhaps unnecesary, but doesn't harm)

ch1 = channelData(fromRootToListDic(t.CopyTree("Kplus_ID>0"),keys_ ))#+ catvars)) 
ch2 = channelData(fromRootToListDic(t.CopyTree("Kplus_ID<0"),keys_))#+ catvars))

chlist = [ch1,ch2]

G = Cat(chlist, keys_)#,catvars)

import cPickle
cPickle.dump(G,file("../../generators/generator_" + year,"w"))

