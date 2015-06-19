import ROOT
from PIDPerfScripts.RunRangeFuncs import *
from GaudiPython import gbl
import sys

def GetDataSetNameDictionary(PartName):
    #======================================================================
    # Define Mother and Workspace name given Particle name
    #======================================================================
    MotherName = None
    WSName = None
    if PartName == 'K':
        MotherName = 'DSt'
        WSName = 'RSDStCalib'
    elif PartName == 'Pi':
        MotherName = 'DSt'
        WSName = 'RSDStCalib'
    elif PartName == 'P':
        MotherName = 'Lam0'
        WSName = 'Lam0Calib'
    elif PartName == 'Mu':
        MotherName = 'Jpsi'
        WSName = 'JpsiCalib'
    else:
        print "**** ERROR: Invalid particle name: %s" %PartName
        sys.exit(1)
        
    ret = {'MotherName'    : MotherName,
           'WorkspaceName' : WSName
           }
        
    return ret


def GetPerfPlotList( PerfFunc,
                     StripVer,
                     MagPolarity,
                     PartName,
                     DLLCutList,
                     TrackCuts,
                     BinningScheme=None,
                     runMin=None,
                     runMax=None,
                     IsMuon=False,
                  verbose=True):

    if PartName not in ("K", "Pi", "P", "Mu"):
        print "**** ERROR: Invalid particle name: %s" %PartName
        sys.exit(1)
        
    MotherNamePostFix=''
    if IsMuon and PartName in ("K", "Pi", "P"):
        MotherNamePostFix = '_MuonUnBiased'
    
    #======================================================================
    # Create dictionary holding:
    # - Reconstruction version    ['RecoVer']
    # - np.array of:
    #        - MagUp run limits   ['UpRuns']
    #        - MagDown run limits ['DownRuns']
    #======================================================================
    DataDict = GetRunDictionary(StripVer, PartName, IsMuon)

    #======================================================================
    # Determine min and max file indicies 
    #======================================================================
    IndexDict = GetMinMaxFileDictionary(DataDict, MagPolarity,
                                        runMin, runMax)

    #======================================================================
    # Append runNumber limits to TrackCuts
    #======================================================================
    if None not in (runMin, runMax):
        if TrackCuts!='':
            TrackCuts+=' && '
        TrackCuts+='runNumber>='+runMin+' && runNumber<='+runMax
    if verbose:
        print 'Track Cuts: ', TrackCuts

    #======================================================================
    # Determine Mother and Workspace names
    #======================================================================
    DataSetNameDict = GetDataSetNameDictionary(PartName)

    #======================================================================
    # Declare default list of PID plots
    #======================================================================
    Plots = []
    
    #======================================================================
    # Loop over all calibration subsamples
    #======================================================================
    for i in xrange(IndexDict['minIndex'], IndexDict['maxIndex']+1):
        
        ##      fname='$CALIBDATASTORE/Reco'+str(DataDict['RecoVer'])+'_DATA/'+MagPolarity+'/'+ \ 
        ##                DataSetNameDict['MotherName']+'_'+PartName+'_'+MagPolarity+'_Strip'+StripVer+'_'+str(i)+'.root'
        fname_head = "$CALIBDATASTORE" if not IsMuon else "$MUONCALIBDATASTORE"
        fname = "%s/Reco%d_DATA/%s/%s%s_%s_%s_Strip%s_%d.root" %(fname_head, DataDict['RecoVer'], MagPolarity, 
                                                               DataSetNameDict['MotherName'], MotherNamePostFix, PartName, MagPolarity,
                                                               StripVer, i)
        f = ROOT.TFile.Open(fname)
        ws = f.Get(DataSetNameDict['WorkspaceName'])
        Data = ws.data('data')

        #======================================================================
        # Declare Instance of RICHTrackDataSet for Calibration tracks
        #======================================================================
        
        DataSet = gbl.PIDTrackDataSet('Calib_Data'
                                      , ''
                                      , Data
                                      , Data.get()
                                      , PartName+'_P'
                                      , PartName+'_PT'
                                      , PartName+'_Eta'
                                      , 'nTracks'
                                      , PartName+'_CombDLLK'
                                      , PartName+'_CombDLLp'
                                      , PartName+'_CombDLLe'
                                      , PartName+'_CombDLLmu'
                                      , PartName+'_IsMuon'
                                      , PartName+'_IsMuonLoose'
                                      , PartName+'_nShared'
                                      , PartName+'_ProbNNK'
                                      , PartName+'_ProbNNpi'
                                      , PartName+'_ProbNNp'
                                      , TrackCuts
                                      , 'nsig_sw'
                                      )
        ws.Delete()
        f.Close()
        if verbose:
            print DataSet, type(DataSet)
        
        #======================================================================
        # Sanity test: do we have a dataset, and is it empty?
        #======================================================================
        if DataSet is None:
            print '**** ERROR: No DataSet found ****'
            sys.exit(1)
        
        if DataSet.sumEntries()==0:
            print '**** ERROR: Zero events selected within this dataset ****'
            sys.exit(1)

        if verbose:
            DataSet.Print('v')

        #======================================================================
        # Reduce dataset to only those events within binning limits
        #======================================================================
        #DataSet = None
        #if BinningScheme is not None:
        #    DataSet = AllDataSet.SetInBinSchema(BinningScheme)
        #    AllDataSet.Delete()
        #else:
        #    DataSet = AllDataSet
            
        #======================================================================
        # Veto ranges with insufficient statistics
        #======================================================================
        if DataSet.sumEntries()<1000:
            print '**** Insufficient events in dataset ({nEvt})'.format(nEvt=DataSet.sumEntries())
            continue

        #======================================================================
        # Run Specific implementation of PerfCalculator
        #======================================================================
        Plots = PerfFunc(PartName, DataSet, DLLCutList, BinningScheme, Plots,
                         verbose)

        #======================================================================
        # Delete DataSet
        #======================================================================
        DataSet.Delete()

    #======================================================================
    # Return list of plots
    #======================================================================
    return Plots


def GetPerfResultList(PerfFunc,
                      StripVer,
                      MagPolarity,
                      PartName,
                      DLLCutList,
                      TrackCuts,
                      runMin=None,
                      runMax=None,
                      IsMuon=False,
                      verbose=True):

    MotherNamePostFix=''
    if IsMuon and PartName in ("K", "Pi", "P") : MotherNamePostFix = '_MuonUnBiased'
    
    #======================================================================
    # Create dictionary holding:
    # - Reconstruction version    ['RecoVer']
    # - np.array of:
    #        - MagUp run limits   ['UpRuns']
    #        - MagDown run limits ['DownRuns']
    #======================================================================
    DataDict = GetRunDictionary(StripVer, PartName, IsMuon)

    #======================================================================
    # Determine min and max file indicies 
    #======================================================================
    IndexDict = GetMinMaxFileDictionary(DataDict, MagPolarity,
                                        runMin, runMax)

    #======================================================================
    # Append runNumber limits to TrackCuts
    #======================================================================
    if TrackCuts is not None:
        TrackCuts+=' && '
    TrackCuts+='runNumber>='+runMin+' && runNumber<='+runMax
    if verbose:
        print TrackCuts

    #======================================================================
    # Determine Mother and Workspace names
    #======================================================================
    DataSetNameDict = GetDataSetNameDictionary(PartName)

    #======================================================================
    # Declare default list of PID results
    #======================================================================
    PIDResults = []

    #======================================================================
    # Loop over all calibration subsamples
    #======================================================================
    for i in xrange(IndexDict['minIndex'], IndexDict['maxIndex']+1):

        ## fname = '$CALIBDATASTORE/Reco'+str(DataDict['RecoVer'])+'_DATA/'+MagPolarity+'/'+ \
        ##        DataSetNameDict['MotherName']+'_'+PartName+'_'+MagPolarity+'_Strip'+StripVer+'_'+str(i)+'.root'
                            
        fname_head = "$CALIBDATASTORE" if not IsMuon else "$MUONCALIBDATASTORE"
        fname = "%s/Reco%d_DATA/%s/%s%s_%s_%s_Strip%s_%d.root" %(fname_head, DataDict['RecoVer'], MagPolarity,
                                                               DataSetNameDict['MotherName'], MotherNamePostFix, PartName, MagPolarity,
                                                               StripVer, i)

        f = ROOT.TFile.Open(fname)
        ws = f.Get(DataSetNameDict['WorkspaceName'])
        Data = ws.data('data')

        #======================================================================
        # Declare Instance of RICHTrackDataSet for Calibration tracks
        #======================================================================
        DataSet = gbl.PIDTrackDataSet('Calib_Data'
                                      , ''
                                      , Data
                                      , Data.get()
                                      , PartName+'_P'
                                      , PartName+'_PT'
                                      , PartName+'_Eta'
                                      , 'nTracks'
                                      , PartName+'_CombDLLK'
                                      , PartName+'_CombDLLp'
                                      , PartName+'_CombDLLe'
                                      , PartName+'_CombDLLmu'
                                      , PartName+'_IsMuon'
                                      , PartName+'_IsMuonLoose'
                                      , PartName+'_nShared'
                                      , PartName+'_ProbNNK'
                                      , PartName+'_ProbNNpi'
                                      , PartName+'_ProbNNp'
                                      , TrackCuts
                                      , 'nsig_sw'
                                      )
        #DataSet = gbl.EvtTrackDataSet('Calib_Data'
        #                              , ''
        #                              , Data
        #                              , Data.get()
        #                              , PartName+'_P'
        #                              , PartName+'_PT'
        #                              , PartName+'_Eta'
        #                              , 'nTracks'
        #                              , PartName+'_CombDLLK'
        #                              , PartName+'_CombDLLp'
        #                              , TrackCuts
        #                              , 'nsig_sw'
        #                              )
        if verbose:
            DataSet.Print('v')
        ws.Delete()
        f.Close()
        
        #======================================================================
        # Sanity test: do we have a dataset, and is it empty?
        #======================================================================
        if DataSet is None:
            continue
        
        if DataSet.sumEntries()==0:
            print '**** Zero events selected within this dataset ****'
            sys.exit(1)

        #======================================================================
        # Veto ranges with insufficient statistics
        #======================================================================
        if DataSet.sumEntries()<1000:
            print '**** Insufficient events in dataset ({nEvt})'.format(nEvt=DataSet.sumEntries())
            continue
        
        #======================================================================
        # Run Specific implementation of PerfCalculator
        #======================================================================
        PerfFunc(DataSet, DLLCutList, PIDResults, verbose)
        if verbose:
            print PIDResults
        
        #======================================================================
        # Delete DataSet
        #======================================================================
        DataSet.Delete()

    #======================================================================
    # Return list PIDResults
    #======================================================================
    return PIDResults
