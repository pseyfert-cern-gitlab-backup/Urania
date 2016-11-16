from ROOT import *
from ROOT import AddressOf
gROOT.SetBatch(True)
from valAndErr import *
from readData import *



def plot_Vars_VS_VeloTr(nTuple, channel = 'Bu'):

        print ' o) Read in data'
        #tree = readData('2012_Strip19abc_BadITRuns')
        tree = readData(nTuple).get('tree')
        dire = 'VeloTrStudy/'
        c = TCanvas('canv','canv')
        print ' o) Get histogram for nVeloTracks'

        c.SetLogy(0)
        tree.Draw('nVeloTracks','','E1')
        c.SaveAs(dire+'nVeloTracks_'+nTuple+'.ps')

        variables = ['nVeloClusters','nPVs','nSPDHits',
                        'nUpstreamTracks','nDownstreamTracks','nTTracks','nLongTracks','nBackTracks','nMuonTracks',
                        'nITClusters','nOTClusters',
                        'Bplus_M','Bplus_BDTS_BIP','Bplus_eta','Bplus_phi','Bplus_PT']

        for var in variables:
                print ' o) Get histogram for: ', var
                tree.Draw(var+':nVeloTracks','','colz')
                c.SaveAs(dire+var+'_VS_Tr_'+nTuple+'.ps')

       #plot_ClperTr_VS_Tr(tree,dire)


def plot_ClperTr_VS_Tr(tree,dire):
        print ' o) Fill in Tracksn/Clusters VS nVeloTracks as a Branch:'

        # Create a struct
        gROOT.ProcessLine(\
                        "struct MyStruct{\
                        Double_t ratio;\
                        Int_t nVeloTracks;\
                           };")
        from ROOT import MyStruct

        #Add branch
        s = MyStruct()

        f = TFile("addBranch.root","RECREATE")
        newTree = TTree('newTree','Tree with the ratio')

        newTree.Branch('nVeloClustersPerTrack',AddressOf(s,'ratio'),'nVeloClustersPerTrack/D')
        newTree.Branch('nVeloTracks',AddressOf(s,'nVeloTracks'),'nVeloTracks/I')

        nEntries_tree = tree.GetEntries()
        for i,event in enumerate(tree):
                #Progress
                if i%2500 is 0: print ' Progress : (' , 100*i/nEntries_tree , '%)'
                s.nVeloTracks= event.nVeloTracks
                s.ratio = event.nVeloClusters / event.nVeloTracks
                newTree.Fill()

        newTree.Draw('nVeloClustersPerTrack:nVeloTracks','','colz')
        c.SaveAs(dire+'nVeloClperTr_VS_Tr_'+nTuple+'.ps')

        f.Write()
        f.Close()

        #print ' o) Dividing thw nVeloClusters by nVeloTracks per bin'
        #c.SaveAs('veloTracks_5.ps')

        #Vars:
        #nVeloTraks_All
        #nVeloTracks
        #nVeloClusters




