import ROOT
from GaudiPython import gbl
from operator import add
from math import sqrt


def MakePerfPlotsList(PartName, DataSet, DLLCutList, BinningScheme,
                      Plots=None, verbose=True):

    #======================================================================
    # Declare instances of PerfCalculator tool : (class)(instance of class)
    #======================================================================
    Calc = gbl.PerfCalculator(gbl.PIDTrackDataSet)(DataSet)                
    #Calc = gbl.PerfCalculator(gbl.RICHTrackDataSet)(DataSet)                
    
    #======================================================================
    # Define array of lists, one for each DLL cut
    #======================================================================
    subPlots = [ [] for j in range(len(DLLCutList)) ]

    #======================================================================
    # Loop over DLL cuts, and append TH1F to appropriate subPlot-list
    #======================================================================
    ROOT.TH1.SetDefaultSumw2(True)
    dataset_index = len(Plots[0]) if Plots else 0
    for index, cut in enumerate(DLLCutList):
        histname = "%s_%s_%d" %(PartName, cut.strip(), dataset_index)
        Dummy = Calc.Perf_Hist(histname,
                               cut,
                               BinningScheme,
                               False,
                               5,
                               verbose)
        subPlots[index].append(Dummy)
        #Dummy.Delete()
    if verbose:
        print 'subPlots: ', subPlots
    del Calc

    #======================================================================
    # Append subPlots to Plots, i.e.
    # Plots = [ [0,1,...]_DLLK>A, [0,1,...]_DLLK>B, ... ]
    #======================================================================
    # Need to resolve the following line....
    NewPlots = map(add, Plots, subPlots) if Plots else subPlots
    if verbose:
        print 'NewPlots: ', dataset_index, NewPlots
    del Plots

    return NewPlots
    
def MakeAveragePlot(Plots):
    #======================================================================
    # Loop over plots in subPlots and append average plot
    #======================================================================
    CombPlot = None
    for plot in Plots:
        plot.SetBit(ROOT.TH1.kIsAverage)
        if CombPlot is None:
            #print plot.GetName()
            CombPlot = plot.Clone(plot.GetName().replace('_0', '_All'))
        else:
            CombPlot.Add(plot)
    Plots.append(CombPlot)
    #print Plots

def MakeAveragePlotList(Plots):
    #======================================================================
    # Loop over all subPlots and run MakeAveragePlot()
    #======================================================================
    for i in range(0, len(Plots)):
        MakeAveragePlot(Plots[i])


def MakePIDResultList(DataSet, DLLCutList, PIDResults, verbose=True):
    print PIDResults
    #======================================================================
    # Declare instances of PerfCalculator tool : (class)(instance of class)
    #======================================================================
    Calc = gbl.PerfCalculator(gbl.EvtTrackDataSet)(DataSet)                
    
    #======================================================================
    # Calculate Efficiency
    #======================================================================
    Dummy = Calc.Perf(DLLCutList,False) #, verbose)
    PIDResults.append(Dummy)

    print PIDResults

def WeightedAveragePIDResults(PIDResults):
    #======================================================================
    # Loop over list of PIDResult::Container (i.e. vector<PIDResult>) and
    # perform weighted average for each index, returning a list of
    # [[Eff_0, Err_0], [Eff_1, Err_1], ... , [Eff_n, Err_n]]
    #======================================================================
    for result in PIDResults:
        if result.size()!=PIDResults[0].size():
            print '**** PIDResult::Container objects are of differing size ****'
            sys.exit(1)

    CombPIDResult = []
    for eff in range(0,PIDResults[0].size() ):
        #print eff
        Eff_Num = 0
        Eff_Denom = 0
        Err_InSq = 0
        for result in PIDResults:
            Eff_Num += result[eff].Eff/pow(result[eff].Err_Lo,2)
            Eff_Denom += 1/pow(result[eff].Err_Lo,2)
            Err_InSq += 1/pow(result[eff].Err_Lo,2)
        CombPIDResult.append([Eff_Num/Eff_Denom,sqrt(1/Err_InSq)])
    #print CombPIDResult

    return CombPIDResult

def SimpleAveragePIDResults(CombPIDResults_a, CombPIDResults_b):
    #======================================================================
    # Perform the simple average of CombPIDResults_a[i] with
    # CombPIDResults_b[i] and return another list of type 
    # [[Eff_0, Err_0], [Eff_1, Err_1], ... , [Eff_n, Err_n]]
    #======================================================================
    if len(CombPIDResults_a)!=len(CombPIDResults_b):
        print '**** Efficiency lists of differing size ****'
        sys.exit(1)
        
    CombPIDResult = []
    for i in range(0, len(CombPIDResults_a)):
        Eff = (CombPIDResults_a[i][0] + CombPIDResults_b[i][0])/2
        Err_Sq = pow(CombPIDResults_a[i][1]/2,2) + pow(CombPIDResults_b[i][1]/2,2)
        CombPIDResult.append([Eff, sqrt(Err_Sq)])

    return CombPIDResult


def makeTGraph(KaonResults, PionResults, name):
    #======================================================================
    # Create TGraph
    #======================================================================
    x     = [list(t) for t in zip(*KaonResults)][0]
    x_err = [list(t) for t in zip(*KaonResults)][1]
    y     = [list(t) for t in zip(*PionResults)][0]
    y_err = [list(t) for t in zip(*PionResults)][1]
    
    from array import array
    graph = ROOT.TGraphErrors(len(x), array('f',x), array('f',y), array('f',x_err), array('f',y_err))
    graph.SetName(name)
    return graph
