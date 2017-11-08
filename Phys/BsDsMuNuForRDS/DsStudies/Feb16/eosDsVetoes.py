from Selections import cutStringDsVetoes
from BsDsMuNuForRDS.DataRetrieval import *
import sys, os
from ROOT import TFile, TTree, gROOT, gDirectory
gROOT.SetBatch(True)

#dataTags = ['BuD0Ds', 'InclDs', 'LbLcDs', 'BdDstDs']
#dataTags = ['MCSignal_Sim08a', 'MCSignal_Sim08h']
dataTags = ['ResolvedPi0v2']
polarities = ['MagDown']

for dataTag in dataTags:
    for pol in polarities:

        fNameEnd = outPutFileNameDict[dataTag][pol]

        # Get the filename with no vetoes.
        #fInName  = 'root://eoslhcb.cern.ch///eos/lhcb/user/r/rvazquez/RDS/' + fNameEnd
        #fOutName = '/afs/cern.ch/work/s/sogilvy/RDs/WithVetoes/' + fNameEnd
        fOutName = '/afs/cern.ch/work/r/rvazquez/RDS/WithVetoes/' + fNameEnd

        # Open the original file.
        #fIn = TFile.Open(fInName)
        #fIn.ls()

        # Add the Friend tree file.
        #fFriendName = '/afs/cern.ch/work/s/sogilvy/RDs/' + fNameEnd
        fFriendName = '/afs/cern.ch/work/r/rvazquez/RDS/' + fNameEnd
        fFriend = TFile.Open(fFriendName)

        # Make the new file.
        fOut = TFile(fOutName, 'recreate')

        for tName in fileNameDict[dataTag]['tNames']:

            # Get the original tuple.
            # c = #fIn.Get(tName)
            c = getChainWithTupleName(dataTag, pol, tName)
                
            # Get the friend and add it.
            tFriend = fFriend.Get(tName)
            tFriend.Print()
            #c.AddFriend(tFriend)

            # Make the TDirectory.
            dirName  = tName.split('/')[0]
            tNameEnd = tName.split('/')[1]
            
            theDir = fOut.mkdir(dirName)
            theDir.cd()

            #tNew = c.CopyTree(cutStringDsVetoes)
                        
            tNew = c.CloneTree(0)
            print cutStringDsVetoes
            tFriend.Draw('>>eList', cutStringDsVetoes)
            eList = gDirectory.Get('eList')
            print type(eList)
            
            # Loop over the tree.
            numEntries = c.GetEntries()
            for i in range(numEntries):
                
                if i%1000==0:
                    sys.stdout.write('\rProcessing event %i of %i...' %(i, numEntries) )
                    sys.stdout.flush()

                # If not accepted then continue.
                if not eList.Contains(i):
                    #print 'BONG'
                    continue
                c.GetEntry(i)
                tNew.Fill()

            tNew.Write()
            fOut.cd('..')

        fOut.Close()

        # now copy to eos.
        #eosdir = '/eos/lhcb/user/s/sogilvy/RDs/WithDsVetoes/'
        eosdir = '/eos/lhcb/user/r/rvazquez/RDS/WithDsVetoes'
        eoscommand = '/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select cp'
        os.system('%s %s %s' %(eoscommand, fOutName, eosdir))
        # Now delete the original.
        print 'Copied file to eos.'
        os.system('rm %s' %fOutName)
