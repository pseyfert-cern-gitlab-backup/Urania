from ROOT import *

nentries = 0
for cat in [ 'TOS1_', 'TOS2_', 'TIS_' ]:
    for i in xrange(3, 10):
        f = TFile( 'prof_mm' + cat + str(i) + '.root' )
        t = f.Get('DecayTree')
        nentries += t.GetEntries()
print '-- Total entries:', nentries
