from ROOT import *
from math import sqrt

f = TFile('FitPlots_TOS1_TOS2.root')
#f = TFile('FitPlots_BkgSyst_TOS1_TOS2.root')
#f = TFile('FitPlots_BkgSyst_FixExpo_TOS1_TOS2.root')
key_lst = f.GetListOfKeys()
nkeys = len(key_lst)
r = int(sqrt(nkeys))
s = nkeys/r + nkeys % r
print '--- Create histogram of size %i, %i' %(r, s)
c = TCanvas('all', 'all', 1500, 1000)
c.Divide(r, s)
key_lst = [k.GetName() for k in key_lst]
for i, k in enumerate(key_lst):
    print '--- Draw: ', k
    obj = f.Get(k)
    c.cd(i+1)
    obj.DrawClonePad()
    c.GetPad(i+1)
c.Update()
raw_input()
