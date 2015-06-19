# ------------------------------ #
# This code loops over the entries
# and counts the number of
# different events.
# ------------------------------ #
from ROOT import *
import cutStrings as cs
import os

from readData import *


def getNumOfDuplicates(nTupleName, channel, add_cut = ''):

        #data = readData(nTupleName, {'channel':channel, 'applyCut':True})
        data = readData(nTupleName, {'channel':channel, 'applyCut':False})
        t = data.get('tree')

        #Add the fiducial cut
        sw = 100
        sigWin_Bs = '&&fabs(B_s0_JCMass-5366.3)<'+str(sw)
        sigWin_Bu = '&&fabs(Bplus_JCMass-5279.17)<'+str(sw)

        datacut = str(data.get('cut'))

        cut = cs.minimalNormBu_lnf + sigWin_Bu + '&&' + datacut
        #cut = cs.minimalNormBu_lnf + cs.K_GhostProb + sigWin_Bu + '&&' + datacut
        cut = cs.minimalNormBu_lnf + cs.K_GhostProb2011 + sigWin_Bu + '&&' + datacut

        #cut = cs.minimalNormBu_lnf + cs.Bu_GhostProb2011 + sigWin_Bu + '&&' + datacut
        #cut = cs.minimalNormBu_lnf + cs.Bu_GhostProb + sigWin_Bu + '&&' + datacut

        if channel == 'Bs':
            cut = cs.normBs_lnf+ sigWin_Bs + '&&' + datacut
            #cut = cs.normBs_lnf + cs.KK_GhostProb + sigWin_Bs + '&&' + datacut
            cut = cs.normBs_lnf + cs.KK_GhostProb2011 + sigWin_Bs + '&&' + datacut

            #cut = cs.normBs_lnf + cs.Bs_GhostProb2011 + sigWin_Bs + '&&' + datacut
            #cut = cs.normBs_lnf + cs.Bs_GhostProb + sigWin_Bs + '&&' + datacut

        #User defined cut
        cut += add_cut


        print ' Apply a cut to the tree...'
        print cut
        f = TFile("cutDataNumOfDup.root","recreate")
        tree = t.CopyTree(cut)
        nEntries = tree.GetEntries()
        eventNumbers = []

        #For every entry get the event nr, and count the different event numbers (there can be multible entries for the same event nr!)
        print ' Looping through the entries and reading their eventNumbers..be patient..'
        i=0
        for entry in range(nEntries):
                #Progress
                if i%25000 is 0: print ' Progress : (' , 100*i/nEntries , '% of entries read)'
                i+=1

                tree.GetEntry(entry)
		eventNr = getattr(tree,'eventNumber')
	#	print 'Added eventNr: ', eventNr
		eventNumbers.append(eventNr)


        print 'Remove dublicate entries..'
        events = removeDuplicates(eventNumbers)
        nrEvents = len(events)
        print 'Done!'

        #Save the results in a file
        dire = 'NumOfDuplicateEntries'
        if not os.path.exists(dire): os.makedirs(dire)
        f = open(dire+'/NumOfDuplicates_'+nTupleName+'_'+channel+'.txt','w')

        print >>f,  ' ------------------------------ '
        print >>f,  'Ntuple:',nTupleName,' channel: ', channel, ' has:'
        print >>f,  '    ', nrEvents, ' events out of'
        print >>f,  '    ', nEntries, ' entries'
        if nrEvents>0: print >>f,  '    ', float(nEntries)/float(nrEvents), ' entries per event'
        else: print >> f, '    No events found! nrEvents=0!'
        print >>f,  '       Cut : ', cut
        print >>f,  ' ------------------------------ '
        f.close()

        print ' Print the results on screen: '
        f = open(dire+'/NumOfDuplicates_'+nTupleName+'_'+channel+'.txt')
        #Print the file content
        for line in f: print line
        f.close()
        print ' o) Result saved in file: ', dire+'/NumOfDuplicates_'+nTupleName+'_'+channel+'.txt'
        return nrEvents

def removeDuplicates(seq):
    #Duplicates are removed when converting to a set
	return list(set(seq))



