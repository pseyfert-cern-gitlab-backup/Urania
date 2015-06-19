from GaudiPython import gbl
from operator import add
import ROOT

ROOT.gSystem.Load('libRooStats.so')

import sys
import getopt
    
def Plots_Strip17(DLLCutList, PartName = 'K', MagPolarity = None, Binning = None, Cuts = None, Plots = None):

    #======================================================================
    # Define MotherName given PartName
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

    #======================================================================
    # Declare default MagPolarity
    #======================================================================
    if MagPolarity is None:
        MagPolarity = 'MagUp'

    #======================================================================
    # Define nFiles given MagPolarity
    #======================================================================
    nFiles = None
    if MagPolarity is 'MagUp':
        nFiles = 7
    if MagPolarity is 'MagDown':
        nFiles = 9
    
    #======================================================================
    # Declare default binning
    #======================================================================
    if Binning is None:
        Binning = ROOT.RooBinning(2000,100000,'P')
        Binning.addUniform(40,2000,100000)

    #======================================================================
    # Declare default cuts
    #======================================================================
    if Cuts is None:
        Cuts = 'Charge==Charge::Positive && '+PartName+'_P<100000'
        
    #======================================================================
    # Declare default list of plots
    #======================================================================
    if Plots is None:
        Plots = []
    
    #======================================================================
    # Loop over all calibration subsamples
    #======================================================================
    for i in xrange(0,nFiles):

        f = ROOT.TFile.Open('$CALIBDATASTORE/Reco12_DATA/'+MagPolarity+'/'+MotherName+'_'+PartName+'_'+MagPolarity+'_Strip17_'+str(i)+'.root')
        ws = f.Get(WSName)
        Data = ws.data('data')
        
        #======================================================================
        # Declare Instance of EvtTrackDataSet for Calibration tracks
        #======================================================================
        DataSet = gbl.MUONTrackDataSet('Calib_Data'
                                       , ''
                                       , Data
                                       , Data.get()
                                       , PartName+'_P'
                                       , PartName+'_PT'
                                       , PartName+'_Eta'
                                       , 'nTracks'
                                       , PartName+'_CombDLLK'
                                       , PartName+'_CombDLLp'
                                       , PartName+'_CombDLLmu'
                                       , PartName+'_IsMuon'
                                       , PartName+'_IsMuonLoose'
                                       , PartName+'_nShared'
                                       , Cuts
                                       , 'nsig_sw'
                                       )
        del ws
        del Data
        DataSet.Print('v')
        f.Close()
        del f

        #======================================================================
        # Declare instances of PerfCalculator tool : (class)(instance of class)
        #======================================================================
        Calc = gbl.PerfCalculator(gbl.MUONTrackDataSet)(DataSet)                

        #======================================================================
        # Define array of lists, one for each DLL cut
        #======================================================================
        subPlots = [ [] for j in range(len(DLLCutList)) ]

        #======================================================================
        # Loop over DLL cuts, and append TH1F to appropriate subPlot-list
        #======================================================================
        for index, cut in enumerate(DLLCutList):
            Dummy = Calc.Perf(cut,Binning)
            Dummy.SetName(PartName+'_'+Binning.GetName()+'_'+Dummy.GetTitle().replace(' ', '')+'_'+str(i))
            subPlots[index].append(Dummy)
            #print PartName+'_'+Dummy.GetTitle().replace(' ', '')+'_'+str(i), len(Plots)
            #print 'subPlots: ', subPlots
        #======================================================================
        # Append subPlots to Plots, i.e.
        # Plots = [ [0,1,...]_DLLK>0, [0,1,...]_DLLK>5, ... ]
        #======================================================================
        Plots = map(add, Plots, subPlots) if Plots else subPlots
        #print 'Plots: ', i, Plots

        del DataSet
        del Calc
        
    return Plots

def AveragePlot(PartName, Plots, Binning = None):
    
    #======================================================================
    # Declare default binning
    #======================================================================
    if Binning is None:
        Binning = ROOT.RooBinning(2000,100000,'P')
        Binning.addUniform(40,2000,100000)

    #======================================================================
    # Loop over plots in subPlots and save to file
    #======================================================================
    CombPlot = None
    for plot in Plots:
        plot.SetBit(ROOT.TH1.kIsAverage)
        if CombPlot is None:
            CombPlot = plot.Clone(PartName+'_'+Binning.GetName()+'_'+plot.GetTitle().replace(' ', '')+'_All')
        else:
            CombPlot.Add(plot)
    Plots.append(CombPlot)
    
    
if '__main__' == __name__:

    #======================================================================
    # List of cuts
    #======================================================================
    MagPolarity = 'MagUp'

    #======================================================================
    # List of cuts
    #======================================================================
    DLLCuts_IsMuon = [ 'IsMuon==1',
                       'IsMuon==0',
                       'DLLmu > 0.0',
                       'DLLmu > 5.0'
                       ]
    
    #======================================================================
    # Binning to consider
    #======================================================================
    #PlotBinning = ROOT.RooBinning(10, 400, 'nTrack')
    #PlotBinning.addUniform(50, 0, 410)

    PlotBinning = ROOT.RooBinning(2000,100000,'P')
    PlotBinning.addUniform(30,  2000,  40000)
    PlotBinning.addUniform(17, 40000,  66000)
    PlotBinning.addUniform(2,  66000,  70000)
    PlotBinning.addUniform(2,  70000,  75000)
    PlotBinning.addUniform(4,  75000,  85000)
    PlotBinning.addUniform(2,  85000, 100000)
    
    #======================================================================
    # Final list of plots 
    #======================================================================
    Plots_Kaon_IsMuon  = Plots_Strip17(DLLCuts_IsMuon,
                                       'K',
                                       MagPolarity,
                                       #Binning=PlotBinning,
                                       Cuts='K_P<100000')
    Plots_Pion_IsMuon  = Plots_Strip17(DLLCuts_IsMuon,
                                       'Pi',
                                       MagPolarity,
                                       #Binning=PlotBinning,
                                       Cuts='Pi_P<100000')

    #======================================================================
    # Make Weighted Average
    #======================================================================
    
    for i in range(0, len(DLLCuts_IsMuon)):
        AveragePlot('K',
                    Plots_Kaon_IsMuon[i],
                    #Binning=PlotBinning
                    )
        AveragePlot('Pi',
                    Plots_Pion_IsMuon[i],
                    #Binning=PlotBinning
                    )
    
    
    #======================================================================
    # Open file to write TH1Fs to
    #======================================================================
    f_Out = ROOT.TFile('MUONPerf_'+MagPolarity+'.root',
                       'UPDATE')
    
    for i in range(0, len(DLLCuts_IsMuon)):
        for plot in Plots_Kaon_IsMuon[i]:
            plot.Write()
        for plot in Plots_Pion_IsMuon[i]:
            plot.Write()
    del Plots_Kaon_IsMuon
    del Plots_Pion_IsMuon
    
        
    #======================================================================
    # Close file
    #======================================================================
    f_Out.Close()
