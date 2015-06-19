import ROOT
from operator import add
from math import sqrt
import warnings

def MakePerfPlotsList(PartName, DataSet, DLLCutList, BinningScheme,
                      Plots=None, verbose=True):

    #======================================================================
    # Declare instances of PerfCalculator tool : (class)(instance of class)
    #======================================================================
    ROOT.gSystem.Load('libRooStats.so')
    ROOT.gSystem.Load('libCintex.so')
    cintex=ROOT.Cintex
    cintex.Enable()
    ROOT.gSystem.Load('libPIDPerfToolsLib.so')
    ROOT.gSystem.Load('libPIDPerfToolsDict.so')
    Calc = ROOT.PerfCalculator(ROOT.EvtTrackDataSet)(DataSet)                
       
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
        parsed_cut = cut.strip().replace("/", "_div_")
        histname = "%s_%s_%d" %(PartName, parsed_cut, dataset_index)
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

    ROOT.gSystem.Load('libRooStats.so')
    ROOT.gSystem.Load('libCintex.so')
    cintex=ROOT.Cintex
    cintex.Enable()
    ROOT.gSystem.Load('libPIDPerfToolsLib.so')
    ROOT.gSystem.Load('libPIDPerfToolsDict.so')
    
    Calc = ROOT.PerfCalculator(ROOT.EvtTrackDataSet)(DataSet)                
    
    #======================================================================
    # Calculate Efficiency
    #======================================================================
    Dummy = Calc.Perf(DLLCutList,False) #, verbose)
    PIDResults.append(Dummy)

    print PIDResults

def WeightedAveragePIDResults(PIDResults, verbose=False):
    #======================================================================
    # Loop over list of PIDResult::Container (i.e. vector<PIDResult>) and
    # perform weighted average for each index, returning a list of
    # [[Eff_0, Err_0], [Eff_1, Err_1], ... , [Eff_n, Err_n]]
    #======================================================================
    nresults=PIDResults[0].size()
    CombPIDResult = []
    if nresults==0:
        msg=("Failed to perform weighted average of PID results. "
             "No results in PIDResult::Container.")
        warnings.warn(msg)
        return CombPIDResult
    
    for result in PIDResults:
        if result.size()!=nresults:
            raise ValueError('PIDResult::Container objects are of differing size')

    for ieff in range(0, nresults):
        #print eff
        Eff_Num = 0.0
        Eff_Denom = 0.0
        ##Err_InSq = 0.0
        for iresult, result in enumerate(PIDResults):
            eff=result[ieff].Eff
            err=result[ieff].Err_Lo
            if err==0.:
                msg=("Got PIDResult::Container result (index {0:d}, result {1:d}) "
                     "with zero error. This result will be excluded from the "
                     "weighted average").format(ieff, iresult)
                warnings.warn(msg)
                continue
            Eff_Num += (1.0*eff)/(err*err)
            Eff_Denom += 1.0/(err*err)
            ##Err_InSq += 1.0/(err*err)
        if Eff_Denom==0.0:
            msg=("Got PIDResult::Container element (index {0:d}) "
                 "with zero error. This index will be excluded from the list of "
                 "averaged PID results").format(ieff)
            warnings.warn(msg)
            continue
        CombPIDResult.append([Eff_Num/Eff_Denom,sqrt(1.0/Eff_Denom)])
        if verbose:
            msg=("PIDResult::Container index {idx:d}"
                 ", weighted efficiency=({eff:.3f}+/-{err:.3f})%").format(
                idx=ieff, eff=eff*100.0, err=err*100.0)
            print msg
            ##sqrt(1/Err_InSq)])
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


def makeTGraph(PIDResults, MisIDResults, name, title=None):
    #======================================================================
    # Create TGraph
    #======================================================================
    x, x_err = [t for t in zip(*PIDResults)]
    y, y_err = [t for t in zip(*MisIDResults)]
    ## x     = [list(t) for t in zip(*KaonResults)][0]
    ## x_err = [list(t) for t in zip(*KaonResults)][1]
    ## y     = [list(t) for t in zip(*PionResults)][0]
    ## y_err = [list(t) for t in zip(*PionResults)][1]
    
    from array import array
    graph = ROOT.TGraphErrors(len(x), array('f',x), array('f',y),
                              array('f',x_err), array('f',y_err))
    graph.SetName(name)
    if title is not None:
        graph.SetTitle(title)
    return graph
