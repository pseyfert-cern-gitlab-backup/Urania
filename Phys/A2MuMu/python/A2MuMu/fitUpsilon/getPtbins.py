from ROOT import *
import numpy as np

input2011 ="/scratch19/cvazquez/NTuples_A1MuMu/no_top_tagging_ntuples/Upsilon_1S_MC_2011.root"
input2012 ="/scratch19/cvazquez/NTuples_A1MuMu/no_top_tagging_ntuples/Upsilon_1S_MC_2012.root"
tupleName = "A1/A1"
t2 = TChain(tupleName)
t2.Add(input2011)
t2.Add(input2012)
mvar = "Bmass"

nbins = 12
totentries = t2.GetEntries()
binentry = float(totentries)/float(nbins)
logptmin = 3.8
bins = [logptmin]
sumentries = 0

for logpt in np.arange(logptmin, 5., 0.001):
       entries = t2.GetEntries("log10(Bpt)>={0} && log10(Bpt)<{1}".format(logptmin, logpt))
       if entries>binentry:
              bins.append(logpt)
              print logptmin, logpt
              print entries
              sumentries = sumentries+entries
              logptmin = logpt

print "totentries = ", totentries
print "sumentries = ", sumentries

print bins






