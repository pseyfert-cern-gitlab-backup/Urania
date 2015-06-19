from PIDPerfScripts.DataFuncs import *
from PIDPerfScripts.PerfCalcFuncs import *

def CalcAveragePerfPlotsAndWriteToFile(TrackDict,
                                       StripVer,
                                       MagPolarity,
                                       runMin,
                                       runMax,
                                       outputDir=None,
                                       verbose=True,
                                       allowMissingDataSets=False,
                                       schemeName=None
                                       ):

    for k, d in TrackDict.items():    
        
        Plots = GetPerfPlotList(MakePerfPlotsList,
                                StripVer,
                                MagPolarity,
                                d['TrackType'],
                                d['DLLCuts'],
                                d['TrackCuts'],
                                d['Binning'],
                                runMin,
                                runMax,
                                verbose,
                                allowMissingDataSets
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
            
        f_Out = ROOT.TFile.Open(fname, 'RECREATE')
        if not f_Out:
            raise IOError("Failed to open file {0} for writing".format(fname))
                          
        for subPlots in Plots:
            for plot in subPlots:
                plot.Write()
                
        ##  for i in range(0, len(Plots)):
        ##             for plot in Plots[i]:
        ##                 plot.SetDirectory(f_Out)
        ##                 plot.Write()
                
        f_Out.Close()
        
        #======================================================================
        # Delete plots 
        #======================================================================    
        del Plots
