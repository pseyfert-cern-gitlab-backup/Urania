# ------------------------------ #
# This code loops over the entries 
# and counts the number of 
# different events. 
# ------------------------------ #
import cutStrings as cs


from readData import *


def getNumOfEvents(nTupleName, channel):


	t = readData(nTupleName, {'channel':channel}).get('tree')

	#Add the fiducial cut
	sw = 35	
	sigWin_Bs = '&&fabs(B_s0_JCMass-5366.3)<'+str(sw)
	sigWin_Bu = '&&fabs(Bplus_JCMass-5279.17)<'+str(sw)

	cut = cs.minimalNormBu_lnf + sigWin_Bu 
	if channel == 'Bs':
		cut = cs.normBs_lnf+ sigWin_Bs

	tree = t.CopyTree(cut)
	nEntries = tree.GetEntries()
	eventNumbers = []	
	for entry in range(nEntries):
		tree.GetEntry(entry)	
		eventNr = getattr(tree,'eventNumber')
		print 'Added eventNr: ', eventNr	
		eventNumbers.append(eventNr) 


	print 'Remove dublicate entries..'

	events = removeDublicates(eventNumbers)
	nrEvents = len(events)
	print 'Done!'
	print ' ------------------------------ '	
	print 'Ntuple:',nTupleName,' channel: ', channel, ' has:'
	print '    ', nrEvents, ' events out of'
	print '    ', nEntries, ' entries'
	print '    ', float(nEntries)/float(nrEvents), ' entries per event'
	print ' ------------------------------ '	
	return nrEvents


def removeDublicates(seq): 
	# Remove dublicate entries	
	# order preserving
	#checked = []
	#for e in seq:
	#	if e not in checked:
	#		checked.append(e)
	#return checked

	#if mylist:
	#	mylist.sort()
	#	last = mylist[-1]
	#	for i in range(len(mylist)-2, -1, -1):
	#		if last == mylist[i]:
	#			del mylist[i]
	#		else:
	#			last = mylist[i]
	
	#Dublicates are removed when converting to a set	
	return list(set(seq))



