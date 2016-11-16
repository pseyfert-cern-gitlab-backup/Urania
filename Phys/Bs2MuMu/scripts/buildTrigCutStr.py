#This file provides functions to easily build trigger cut strings
#from a given list of trigger line names

############################################################
#Here are listed the trigger lines used for the BplusJpsiKplus, Bs mumu, Bs2JpsiPhi
#Add or commet out the lines you want to include/exclude

#BplusL0Phys_Dec consists of:
L0_lines = [	'BplusL0MuonDecision_',
		'BplusL0DiMuonDecision_',
		'BplusL0HadronDecision_',
		'BplusL0ElectronDecision_',
		'BplusL0ElectronHiDecision_',
		'BplusL0PhotonDecision_',
		'BplusL0PhotonHiDecision_']


#BplusHlt1Phys_Dec consists of:
Hlt1_lines = [	'BplusHlt1SingleMuonNoIPDecision_',
		'BplusHlt1SingleMuonHighPTDecision_',
		'BplusHlt1SingleElectronNoIPDecision_',
		'BplusHlt1TrackAllL0Decision_',
		'BplusHlt1TrackMuonDecision_',
		'BplusHlt1TrackPhotonDecision_',
		'BplusHlt1DiMuonLowMassDecision_',
		'BplusHlt1DiMuonHighMassDecision_',
		'BplusHlt1MB__Decision_']

#BplusHlt2Phys_Dec consists of:
Hlt2_lines = [ 	'BplusHlt2SingleMuonDecision_',
		'BplusHlt2SingleMuonLowPTDecision_',
		'BplusHlt2SingleMuonHighPTDecision_',
		'BplusHlt2DiMuonDecision_',
		'BplusHlt2DiMuonLowMassDecision_',
		'BplusHlt2DiMuonJPsiDecision_',
		'BplusHlt2DiMuonJPsiHighPTDecision_',
		'BplusHlt2DiMuonPsi2SDecision_',
		'BplusHlt2DiMuonDetachedDecision_',
		'BplusHlt2DiMuonDetachedJPsiDecision_',
		'BplusHlt2DiMuonDetachedHeavyDecision_',
		'BplusHlt2TriMuonTauDecision_',
		'BplusHlt2B2HHDecision_',
		'BplusHlt2DiMuonBDecision_',
		'BplusHlt2DiMuonZDecision_',
		'BplusHlt2TopoMu2BodyBBDTDecision_',
		'BplusHlt2TopoMu3BodyBBDTDecision_',
		'BplusHlt2TopoMu4BodyBBDTDecision_',
		'BplusHlt2Topo2BodyBBDTDecision_',
		'BplusHlt2Topo3BodyBBDTDecision_',
		'BplusHlt2Topo4BodyBBDTDecision_',
		'BplusHlt2Topo2BodySimpleDecision_',
		'BplusHlt2Topo3BodySimpleDecision_',
		'BplusHlt2PassThroughDecision_',
		'BplusHlt2TransparentDecision_',
		'BplusHlt2IncPhiDecision_',
		'BplusHlt2DiMuonDY__Decision_',
		'BplusHlt2TopoE__Decision_',
		'BplusHlt2Topo__Decision_',
		'BplusHlt2Charm__Decision_',
		'BplusHlt2DiElectron__Decision_',
		'BplusHlt2__GammaDecision_']
############################################################

#Functions for building cut strings
def addSuf(suf,list):
	#For adding TIS TOS and Dec endings to the lines	
	newList = []	
	for line in list: newList.append(line + str(suf))
	return newList

def listToStr(list, logic):
	#Add all the lines in the list to one string	
	string = '&&('	
	for i,line in enumerate(list): 
		if i < len(list)-1 :string += str(line)+'==1'+str(logic)
		else: string += str(line)+'==1)'
	return string

############################################################
#BUILD THE CUTSTRINGS
#########
#L0	#
#########
cut_L0_Dec = listToStr(addSuf('Dec',L0_lines),'||')
cut_L0_TIS = listToStr(addSuf('TIS',L0_lines),'||')
cut_L0_TOS = listToStr(addSuf('TOS',L0_lines),'||')

#########
#Hlt1	#
#########
cut_Hlt1_Dec = listToStr(addSuf('Dec',Hlt1_lines),'||')
cut_Hlt1_TIS = listToStr(addSuf('TIS',Hlt1_lines),'||')
cut_Hlt1_TOS = listToStr(addSuf('TOS',Hlt1_lines),'||')

#########
#Hlt2	#
#########
cut_Hlt2_Dec = listToStr(addSuf('Dec',Hlt2_lines),'||')
cut_Hlt2_TIS = listToStr(addSuf('TIS',Hlt2_lines),'||')
cut_Hlt2_TOS = listToStr(addSuf('TOS',Hlt2_lines),'||')

############################################################


