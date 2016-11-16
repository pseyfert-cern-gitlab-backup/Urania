from PIDPerfScripts.Definitions import *
from PIDPerfScripts.Binning import *
from PIDPerfScripts.DataFuncs import *
from PIDPerfScripts.PerfCalcFuncs import *
from PIDPerfScripts.RunDictFuncs import *
from PIDPerfScripts.PlotFuncs import *

import ROOT
from ROOT import RooFit

def CalcAveragePerfPlotsAndWriteToFile(TrackDict,
                                       StripVer,
                                       MagPolarity,
                                       runMin,
                                       runMax,
                                       outputDir=None,
                                       verbose=True,
                                       allowMissingDataSets=False,
                                       schemeName=None,
                                       maxFiles=-1,
                                       triggerList=[]
                                       ):

    for k, d in TrackDict.items():
        #print "in calcaverage"
        Plots = GetPerfPlotList(MakePerfPlotsListPyth,
                                StripVer,
                                MagPolarity,
                                d['TrackType'],
                                d['DLLCuts'],
                                d['TrackCuts'],
                                d['Binning'],
                                runMin,
                                runMax,
                                verbose,
                                allowMissingDataSets,
                                maxFiles,
                                triggerList
                                )

        #======================================================================
        # Make Weighted Average
        #======================================================================
        MakeAveragePlotList(Plots)
        print 'Plots:', Plots

        #======================================================================
        # Write TH1Fs to file
        #======================================================================
        fileSuffix=""
        if schemeName is not None:
            fileSuffix+='_{0}'.format(schemeName)
        fileSuffix+='_{0}'.format((d['Binning'][0]).GetName())
        fname="PubPlots_{plotType}_Strip{strp}_{pol}{suf}.root".format(
            plotType=k, strp=StripVer, pol=MagPolarity, suf=fileSuffix)
        if outputDir is not None:
            fname="{0}/{1}".format(outputDir, fname)

        f_Out = ROOT.TFile.Open(fname, 'UPDATE')
        if not f_Out:
            raise IOError("Failed to open file {0} for writing".format(fname))

        for subPlots in Plots:
            for plot in subPlots:
                if len(plot)==1:
                    plot.Write()
                else:   
                    for uberplot in plot:
                        uberplot.Write()

 # plot.Write()

         #for subPlots in Plots:
         #    print 'subPlots:' subPlots
        #for i in range(0, len(Plots)):
        #    for plot in Plots[i]:
        #        plot.SetDirectory(f_Out)
        #        plot.Write()

        f_Out.Close()

        #======================================================================
        # Delete plots
        #======================================================================
        del Plots



def CalcAveragePerfPlotsAndReturn(TrackDict,
                                  StripVer,
                                  MagPolarity,
                                  runMin,
                                  runMax,
                                  verbose=True,
                                  allowMissingDataSets=False,
                                  maxFiles=-1,
                                  triggerList=[]
                                  ):

    AveragedPlots = {}

    for k, d in TrackDict.items():

        Plots = GetPerfPlotList(MakePerfPlotsListPyth,
                                StripVer,
                                MagPolarity,
                                d['TrackType'],
                                d['DLLCuts'],
                                d['TrackCuts'],
                                d['Binning'],
                                runMin,
                                runMax,
                                verbose,
                                allowMissingDataSets,
                                maxFiles,
                                triggerList
                                )

        #======================================================================
        # Make Weighted Average
        #======================================================================
        MakeAveragePlotList(Plots)
        print 'Plots:', Plots

        AveragedPlots[k] = Plots

    return AveragedPlots


def PlotVarsAndReturn( PartName, PlotVars, StripVer, MagPolarity,
                      runMin, runMax, TrackCuts="", verbose=True,
                      allowMissingDataSets=False, schemeName=None,
                      maxFiles=-1, triggerList=[]
                      ):

    CheckStripVer(StripVer)
    CheckMagPol(MagPolarity)
    CheckPartType(PartName)

    #======================================================================
    # Append runNumber limits to TrackCuts
    #======================================================================
    if None not in (runMin, runMax):
        if TrackCuts!='':
            TrackCuts+=' && '
        TrackCuts+='runNumber>='+runMin+' && runNumber<='+runMax
    if verbose:
        print 'Track Cuts: ', TrackCuts

    minEntries=0
    SummedPlots = {}

    for PlotVar in PlotVars:
        SummedPlots[PlotVar] = []

    #======================================================================
    # Loop over all calibration files
    #======================================================================
    files = GetFiles(StripVer,MagPolarity,PartName,runMin,runMax,maxFiles,verbose)

    index = 0;
    for file in files:
        index+=1
        DataSet = GetDataSet(StripVer, MagPolarity, PartName, TrackCuts, file, verbose,
                            allowMissingDataSets, minEntries, triggerList)
        for PlotVar in PlotVars:
            BinSchema = GetBinScheme(PartName, PlotVar, schemeName)
            if DataSet is not None:
                histname = "%s_%s_%d" %(PartName, PlotVar, index)

                RawHist = ROOT.TH1D(histname, histname, BinSchema.numBins(), BinSchema.array())
                VarList = ROOT.RooArgList(DataSet.Get_Param(BinSchema.GetName()))
                DataSet.fillHistogram(RawHist, VarList)

                SummedPlots[PlotVar].append(RawHist.Clone(histname))
        DataSet.Delete()

    #======================================================================
    # Sum plots
    #======================================================================

    print 'Plots:', SummedPlots

    for PlotVar in PlotVars:
        MakeSumPlot(SummedPlots[PlotVar])

    print 'SummedPlots:', SummedPlots

    return SummedPlots




def PlotVarAndWriteToFile(
                            PartName,
                            PlotVar,
                            StripVer,
                            MagPolarity,
                            runMin,
                            runMax,
                            TrackCuts="",
                            outputDir=None,
                            verbose=True,
                            allowMissingDataSets=False,
                            schemeName=None,
                            maxFiles=-1,
                            triggerList=[]
                          ):

    Plots = PlotVarsAndReturn( PartName, [PlotVar], StripVer, MagPolarity,
                                runMin, runMax, TrackCuts, verbose,
                                allowMissingDataSets,schemeName, maxFiles,
                                triggerList
                              )

    #======================================================================
    # Construct file name
    #======================================================================
    
    fileSuffix=""
    if schemeName is not None:
        fileSuffix+='_{0}'.format(schemeName)
    #fileSuffix+='_{0}'.format(BinSchema.GetName())
    #fname="PlotCalibDistribution_{particle}_{var}_Strip{strp}_{pol}{suf}.root".format(
    #    particle=PartName, var=PlotVar, strp=StripVer, pol=MagPolarity, suf=fileSuffix)
    fname="PlotCalibDistribution_{particle}_{var}_Strip{strp}_{pol}.root".format(
        particle=PartName, var=PlotVar, strp=StripVer, pol=MagPolarity)
    if outputDir is not None:
        fname="{0}/{1}".format(outputDir, fname)

    f_Out = ROOT.TFile.Open(fname, 'UPDATE')
    if not f_Out:
        raise IOError("Failed to open file {0} for writing".format(fname))

    for plot in Plots[PlotVar]:
        plot.Write()

    f_Out.Close()

    del Plots


def GetPerfPlotList( PerfFunc,
                     StripVer,
                     MagPolarity,
                     PartName,
                     DLLCutList,
                     TrackCuts,
                     BinningScheme=None,
                     runMin=None,
                     runMax=None,
                     verbose=True,
                     allowMissingDataSets=False,
                     maxFiles=-1,
                     triggerList=[]):


    #print " IN getperfplotlist"
    #**********************************************************************
    CheckStripVer(StripVer)
    CheckMagPol(MagPolarity)
    CheckPartType(PartName)
    print BinningScheme.size()
    print BinningScheme.at(0)
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
    # Declare default list of PID plots
    #======================================================================
    Plots = []
    minEntries=0

    #======================================================================
    # Loop over all calibration subsamples
    #======================================================================

    files = GetFiles(StripVer,MagPolarity,PartName,runMin,runMax,maxFiles,verbose)
    for file in files:
        DataSet = GetDataSet(StripVer, MagPolarity, PartName, TrackCuts, file, verbose,
                             allowMissingDataSets, minEntries, triggerList)
        if DataSet is not None:
            #======================================================================
            # Run Specific implementation of PerfCalculator
            #======================================================================
    
            print "printing the size again"
            print BinningScheme.size()
            Plots = PerfFunc(PartName, DataSet, DLLCutList, BinningScheme, Plots,
                                verbose=verbose)
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
                      verbose=True,
                      allowMissingDataSets=False,
                      maxFiles=-1,
                      triggerList=[] ):
 #**********************************************************************
    CheckStripVer(StripVer)
    CheckMagPol(MagPolarity)
    CheckPartType(PartName)

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
    # Declare default list of PID results
    #======================================================================
    PIDResults = []
    minEntries = 0

    #======================================================================
    # Loop over all calibration subsamples
    #======================================================================
  #  for DataSet in GetDataSets(StripVer, MagPolarity, PartName, TrackCuts,
  #                             runMin, runMax, verbose, allowMissingDataSets):
    files = GetFiles(StripVer,MagPolarity,PartName,runMin,runMax,maxFiles,verbose)
    for file in files:
        DataSet = GetDataSet(StripVer,MagPolarity,PartName,TrackCuts,file,verbose,allowMissingDataSets, 1000, triggerList)
        if DataSet is not None:

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



