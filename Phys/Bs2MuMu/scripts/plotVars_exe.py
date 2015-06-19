from plotRunNr import *
from plotVars import *


#This file just hold the call command from the Strip20 validation study

#Plot the run numbers
#plotAllRuns('Bu',['2011_Strip17','2011_Strip20r1_71pb'],'2011_Strip17_20_')
#plotAllRuns('Bu',['2012_Strip20','2012_Strip19abc','2012_Strip19a', '2012_Strip19b', '2012_Strip19c'],'2012_Strip19_20_')

#Do the variable comparison
p = plotVars({	'includeMC10':0, 'includeMC12':False, 
		'include2011_Strip17':1, 'include2011_Strip20r1_71pb':1,
		'include2012_Strip19a':0, 'include2012_Strip19abc':1, 'include2012_Strip20':1,
		'channel':'Bu',
		'JpsiTrig':False,
		'selectRuns_2011_Strip20r1':1, 
		'selectRuns_2012_Strip19': 1,
		'plotBVars':0,  'plotJpsiVars':0, 'plotMuonVars':0, 'plotKaonVars':0, 
		'plotBDT':0, 'plotBDTSVars':0, 'plotBDTVars':0, 
		'plotMuonGhostProb':0, 'plotKaonGhostProb':0,
		'plotMultVars_forAll':False, 
		'plotMultVars_Trks':False, 
		'plotMultVars_Tracks':0, 
		'plotMultData':0, 
		'plotIsolationVars':0,
		'plotUpstreamTracks':1
		})

p.compareVars()

