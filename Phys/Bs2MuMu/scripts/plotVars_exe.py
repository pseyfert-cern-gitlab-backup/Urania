from plotRunNr import *
from plotVars import *


#This file just hold the call command from the Strip20 validation study

#Plot the run numbers
#plotAllRuns('Bu',['2011_Strip17','2011_Strip20r1_71pb'],'2011_Strip17_20_')
#plotAllRuns('Bu',['20.3_Strip20','20.3_Strip19abc','20.3_Strip19a', '20.3_Strip19b', '20.3_Strip19c'],'20.3_Strip19_20_')

#Do the variable comparison

def runComparison(x):

	p=0
	# Compare MC12_S17 to MC12_S20
	# Channel: Bhh
	# Cut: no cuts
	if x is 1:
		p = plotVars({	'includeMC12_S17':1, 'includeMC12_S20':1,
				'includeMC10':0, 'includeMC12':0,
				'include2011_Strip17':0, 'include2011_Strip20r1_71pb':0,
				'include20.3_Strip19a':0, 'include20.3_Strip19abc':0, 'include20.3_Strip20':0,
				'channel':'Bhh',
				'JpsiTrig':False,
				'selectRuns_2011_Strip20r1':0,
				'selectRuns_20.3_Strip19': 0,
				'BhhMassCut':False,
				'mu_GhostProb<':False,
				'plotBVars':1,  'plotJpsiVars':0, 'plotMuonVars':1, 'plotKaonVars':0,
				'plotBDT':1, 'plotBDTSVars':1, 'plotBDTVars':1,
				'plotMuonGhostProb':1, 'plotKaonGhostProb':0,
				'plotMultVars_forAll':False,
				'plotMultVars_Trks':False,
				'plotMultVars_Tracks':1,
				'plotMultData':1,
				'plotIsolationVars':1,
				'plotUpstreamTracks':0,
				'rootFileDir':'VarPlots/rootFiles/',
				'plotDir':'VarPlots/MC12S20_Bhh_noCuts/',
				'doSBsubtraction':False
				})

	# Compare MC12_S17 to MC12_S20
	# Channel: Bhh
	# Cut: Mass cut and GhostProb on muon
	if x is 2:
		p = plotVars({	'includeMC12_S17':1, 'includeMC12_S20':1,
				'includeMC10':0, 'includeMC12':0,
				'include2011_Strip17':0, 'include2011_Strip20r1_71pb':0,
				'include20.3_Strip19a':0, 'include20.3_Strip19abc':0, 'include20.3_Strip20':0,
				'channel':'Bhh',
				'JpsiTrig':False,
				'selectRuns_2011_Strip20r1':0,
				'selectRuns_20.3_Strip19': 0,
				'BhhMassCut':True,
				'mu_GhostProb<':0.3,
				'plotBVars':1,  'plotJpsiVars':0, 'plotMuonVars':1, 'plotKaonVars':0,
				'plotBDT':1, 'plotBDTSVars':1, 'plotBDTVars':1,
				'plotMuonGhostProb':1, 'plotKaonGhostProb':0,
				'plotMultVars_forAll':False,
				'plotMultVars_Trks':False,
				'plotMultVars_Tracks':1,
				'plotMultData':1,
				'plotIsolationVars':1,
				'plotUpstreamTracks':0,
				'rootFileDir':'VarPlots/rootFiles/',
				'plotDir':'VarPlots/MC12S20_Bhh_mass_GPcut/',
				'doSBsubtraction':False
				})

	# Compare MC12_S17 to MC12_S20
	# Channel: Bmumu
	# Cut: no cuts
	if x is 3:
		p = plotVars({	'includeMC12_S17':1, 'includeMC12_S20':1,
				'includeMC10':0, 'includeMC12':0,
				'include2011_Strip17':0, 'include2011_Strip20r1_71pb':0,
				'include20.3_Strip19a':0, 'include20.3_Strip19abc':0, 'include20.3_Strip20':0,
				'channel':'Bmumu',
				'JpsiTrig':False,
				'selectRuns_2011_Strip20r1':0,
				'selectRuns_20.3_Strip19': 0,
				'BhhMassCut':False,
				'mu_GhostProb<':False,
				'plotBVars':1,  'plotJpsiVars':0, 'plotMuonVars':1, 'plotKaonVars':0,
				'plotBDT':1, 'plotBDTSVars':1, 'plotBDTVars':1,
				'plotMuonGhostProb':1, 'plotKaonGhostProb':0,
				'plotMultVars_forAll':False,
				'plotMultVars_Trks':False,
				'plotMultVars_Tracks':1,
				'plotMultData':1,
				'plotIsolationVars':1,
				'plotUpstreamTracks':0,
				'rootFileDir':'VarPlots/rootFiles/',
				'plotDir':'VarPlots/MC12S20_Bmumu_noCuts/',
				'doSBsubtraction':False
				})

	# Compare MC12_S17 to MC12_S20
	# Channel: Bmumu
	# Cut: GhpstProb
	if x is 4:
		p = plotVars({	'includeMC12_S17':1, 'includeMC12_S20':1,
				'includeMC10':0, 'includeMC12':0,
				'include2011_Strip17':0, 'include2011_Strip20r1_71pb':0,
				'include20.3_Strip19a':0, 'include20.3_Strip19abc':0, 'include20.3_Strip20':0,
				'channel':'Bmumu',
				'JpsiTrig':False,
				'selectRuns_2011_Strip20r1':0,
				'selectRuns_20.3_Strip19': 0,
				'BhhMassCut':False,
				'mu_GhostProb<':0.3,
				'plotBVars':1,  'plotJpsiVars':0, 'plotMuonVars':1, 'plotKaonVars':0,
				'plotBDT':1, 'plotBDTSVars':1, 'plotBDTVars':1,
				'plotMuonGhostProb':1, 'plotKaonGhostProb':0,
				'plotMultVars_forAll':False,
				'plotMultVars_Trks':False,
				'plotMultVars_Tracks':1,
				'plotMultData':1,
				'plotIsolationVars':1,
				'plotUpstreamTracks':0,
				'rootFileDir':'VarPlots/rootFiles/',
				'plotDir':'VarPlots/MC12S20_Bmumu_GP/',
				'doSBsubtraction':False
				})

	# Study the GoodITAlignedRuns to the Bad ones
	# Channel: Bmumu
	# Cut
	if x is 5:
		p = plotVars({	'includeMC12_S17':0, 'includeMC12_S20':0,
				'includeMC10':0, 'includeMC12':0,
				'include2011_Strip17':0, 'include2011_Strip20r1_71pb':0,
				'include2012_Strip19a':0, 'include2012_Strip19abc':0, 'include2012_Strip20':0,
				#'include2012_Strip19abc_GoodBadITRuns':True,
				'include2012_Strip20_GoodBadITRuns':True,
				'channel':'Bu',
				'JpsiTrig':False,
				'selectRuns_2011_Strip20r1':0,
				'selectRuns_20.3_Strip19': 0,
				'BhhMassCut':False,
				'mu_GhostProb<':0.3,
				'plotBVars':1,  'plotJpsiVars':0, 'plotMuonVars':1, 'plotKaonVars':0,
				'plotBDT':1, 'plotBDTSVars':1, 'plotBDTVars':1,
				'plotMuonGhostProb':1, 'plotKaonGhostProb':0,
				'plotMultVars_forAll':False,
				'plotMultVars_Trks':False,
				'plotMultVars_Tracks':1,
				'plotMultData':1,
				'plotIsolationVars':1,
				'plotUpstreamTracks':0,
				'rootFileDir':'VarPlots/rootFiles/',
				#'plotDir':'VarPlots/BadGoodITRuns_2012_Strip19abc/',
				'plotDir':'VarPlots/BadGoodITRuns_2012_Strip20/',
				'doSBsubtraction':False
				})

        # Compare: 2011 S17, S20r1 and 2012 S19abc, S20
	# Channel: BuJpsiKplus
	# Cut: no cuts
	if x is 6:
		p = plotVars({	'includeMC12_S17':0, 'includeMC12_S20':0,
				'includeMC10':0, 'includeMC12':0,
				'include2011_Strip17':1, 'include2011_Strip20r1':1,
				'include2012_Strip19a':0, 'include2012_Strip19abc':1, 'include2012_Strip20':1,
				'channel':'Bu',
				'JpsiTrig':False,
				'selectRuns_2011_Strip20r1':0,
				'selectRuns_2012_Strip19': 0,
				'BhhMassCut':False,
				'mu_GhostProb<':False,
				'plotBVars':1,  'plotJpsiVars':1, 'plotMuonVars':1, 'plotKaonVars':1,
				'plotBDT':0, 'plotBDTSVars':1, 'plotBDTVars':1,
				'plotMuonGhostProb':1, 'plotKaonGhostProb':0,
				'plotMultVars_forAll':False,
				'plotMultVars_Trks':False,
				'plotMultVars_Tracks':1,
				'plotMultData':1,
				'plotIsolationVars':1,
				'plotUpstreamTracks':1,
				'rootFileDir':'VarPlots/rootFiles/',
				'plotDir':'VarPlots/ReproData_BuJpsiKplus_fid/',
				#'plotDir':'VarPlots/ReproData_BuJpsiKplus_fid_SbSubtracted/',
				'doSBsubtraction':False
				#'doSBsubtraction':True
				})



	#Compare the variables and sabe plots
	p.compareVars()

