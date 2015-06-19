from PIDPerfScripts.DataFuncs import *
from PIDPerfScripts.PerfCalcFuncs import *

def CalcAveragePerfPlotsAndWriteToFile(TrackDict,
                                       StripVer,
                                       MagPolarity,
                                       runMin,
                                       runMax
                                       ):

    for key, dict in TrackDict.items():    
        
        Plots = GetPerfPlotList(MakePerfPlotsList,
                                StripVer,
                                MagPolarity,
                                dict['TrackType'],
                                dict['DLLCuts'],
                                dict['TrackCuts'],
                                dict['Binning'],
                                runMin,
                                runMax,
                                dict['IsMuon'])

        #======================================================================
        # Make Weighted Average
        #======================================================================
        MakeAveragePlotList(Plots)
        print 'Plots:', Plots
    
        #======================================================================
        # Write TH1Fs to file
        #======================================================================    
        f_Out = ROOT.TFile(key+'_Strip'+StripVer+'_'+MagPolarity+'.root','RECREATE')
        for i in range(0, len(Plots)):
            for plot in Plots[i]:
                plot.SetDirectory(f_Out)
                plot.Write()
        f_Out.Close()
        
        #======================================================================
        # Delete plots 
        #======================================================================    
        del Plots
