#------------------------#
#This code prints all the 
#branch names of an nTuple 
#------------------------#


from readData import *


def getListOfBranches(nTupleName,channel, lookFor=''):

	t = readData(nTupleName, {'channel':channel}).get('tree')
	totBrList = t.GetListOfBranches()
	found = 0


	print '  The lines containing: ', lookFor
	for br in totBrList:
		name = br.GetName()
		if name.find(lookFor)>-1 or lookFor=='fullList': 
			print name	
			found+=1


	print '  Found ', found, ' lines.'
	return '-- THE END --'


