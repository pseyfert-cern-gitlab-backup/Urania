from GaudiPython import gbl
from operator import add
import ROOT

ROOT.gSystem.Load('libRooStats.so')

import sys
import getopt
    
def Get_DataSet(PartName = 'Mu', MagPolarity = 'MagUp', i = 0):

    #======================================================================
    # Define MotherName given PartName
    #======================================================================
    MotherName = None
    WSName = None
    if PartName == 'K':
        MotherName = 'DSt_MuonUnBiased'
        WSName = 'RSDStCalib'
    elif PartName == 'Pi':
        MotherName = 'DSt_MuonUnBiased'
        WSName = 'RSDStCalib'
    elif PartName == 'P':
        MotherName = 'Lam0_MuonUnBiased'
        WSName = 'Lam0Calib'
    elif PartName == 'Mu':
        MotherName = 'Jpsi'
        WSName = 'JpsiCalib'

    f = ROOT.TFile.Open('$CALIBDATASTORE/Reco13_DATA/'+MagPolarity+'/'+MotherName+'_'+PartName+'_'+MagPolarity+'_Strip19_'+str(i)+'.root')

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
                                       , ''
                                       , 'nsig_sw'
                                       )
    del ws
    del Data
    DataSet.Print('v')
    f.Close()
    del f

    return DataSet


def MakePrefix(prefix):
    prefix = prefix.replace(' ', '');
    prefix = prefix.replace('(', '');
    prefix = prefix.replace(')', '');
    prefix = prefix.replace('<', '_LT_');
    prefix = prefix.replace('>', '_GT_');
    prefix = prefix.replace('>=', '_GE_');
    prefix = prefix.replace('<=', '_LE_');
    prefix = prefix.replace('==', '_EQ_');
    prefix = prefix.replace('&&', '_AND_');
    prefix = prefix.replace('||', '_OR_');
    prefix = prefix.replace('-', 'NEG');
    prefix = prefix.replace('.', 'POINT');
    return prefix

def EffTables(DLLCutList, PartName, FirstBinning, SecondBinning, CalcList):

    print 'Performing tables for' + PartName 

    output = sys.stdout
    Plots = []

    for i, Calc in enumerate(CalcList):
        PIDCuts = gbl.std.list('string')()
        for index, cut in enumerate(DLLCutList):
           PIDCuts.push_back(cut)

        subPlots = [ [] for j in range(len(DLLCutList)) ]

        for index, cut in enumerate(DLLCutList):
            Table = Calc.Table(cut,FirstBinning, SecondBinning)
            #Table.PrintTable(std::cout, kFALSE);
            #Table.PrintTable(output, False);
            Table.PrintTable();
            Dummy = Table.GetPerfHist2D()
            Dummy.SetName("Table_"+PartName+'_'+FirstBinning.GetName()+'_'+Dummy.GetTitle().replace(' ', '')+'_'+str(i))
            prefix = Dummy.GetTitle();
            prefix = MakePrefix(prefix)
            subPlots[index].append(Dummy)
            #print PartName+'_'+Dummy.GetTitle().replace(' ', '')+'_'+str(i), len(Plots)
            #print 'subPlots: ', subPlots
        #======================================================================
        # Append subPlots to Plots, i.e.
        # Plots = [ [0,1,...]_DLLK>0, [0,1,...]_DLLK>5, ... ]
        #======================================================================
        Plots = map(add, Plots, subPlots) if Plots else subPlots
        #print 'Plots: ', i, Plots

    #======================================================================
    # Average Plot
    #======================================================================

    for index in range(len(DLLCutList)):
      CombPlot = None
      prefix = None
      for plot in Plots[index]:
          plot.SetBit(ROOT.TH1.kIsAverage)
          if CombPlot is None:
            prefix = plot.GetTitle();
            prefix = MakePrefix(prefix)
            CombPlot = plot.Clone("Table_"+PartName+'_'+FirstBinning.GetName()+'_'+plot.GetTitle().replace(' ', '')+'_All')
          else:
            CombPlot.Add(plot)
      Plots[index].append(CombPlot)
    return Plots
    



def EffPlots(DLLCutList, PartName, Binning, CalcList):

    print 'Performing plots1 for' + PartName 

    Plots = []

    for i, Calc in enumerate(CalcList):
        PIDCuts = gbl.std.list('string')()
        for index, cut in enumerate(DLLCutList):
           PIDCuts.push_back(cut)

        subPlots = [ [] for j in range(len(DLLCutList)) ]

        for index, cut in enumerate(DLLCutList):
            Dummy = Calc.Perf(cut,Binning)
            Dummy.SetName(PartName+'_'+Binning.GetName()+'_'+Dummy.GetTitle().replace(' ', '')+'_'+str(i))
            canvas = ROOT.TCanvas()
            prefix = Dummy.GetTitle();
            prefix = MakePrefix(prefix)
            Dummy.Draw();
            canvas.SaveAs(PartName+'_'+Binning.GetName()+'_'+prefix+'_'+str(i) + '.pdf')
            subPlots[index].append(Dummy)
            #print PartName+'_'+Dummy.GetTitle().replace(' ', '')+'_'+str(i), len(Plots)
            #print 'subPlots: ', subPlots
        #======================================================================
        # Append subPlots to Plots, i.e.
        # Plots = [ [0,1,...]_DLLK>0, [0,1,...]_DLLK>5, ... ]
        #======================================================================
        Plots = map(add, Plots, subPlots) if Plots else subPlots
        #print 'Plots: ', i, Plots

    #======================================================================
    # Average Plot
    #======================================================================

    for index in range(len(DLLCutList)):
      CombPlot = None
      prefix = None
      for plot in Plots[index]:
          plot.SetBit(ROOT.TH1.kIsAverage)
          if CombPlot is None:
            prefix = plot.GetTitle();
            prefix = MakePrefix(prefix)
            CombPlot = plot.Clone(PartName+'_'+Binning.GetName()+'_'+plot.GetTitle().replace(' ', '')+'_All')
          else:
            CombPlot.Add(plot)
      canvas = ROOT.TCanvas()
      CombPlot.Draw()
      canvas.SaveAs(PartName+'_'+Binning.GetName()+'_'+prefix+'_All.pdf')
      Plots[index].append(CombPlot)
    return Plots
    

def EffVsMisIDPlots(DLLCutList, PartName, Binning, CalcList, CalcMuList):

    print 'Performing plots2 for' + PartName 
    Plots = []
    
    #======================================================================
    # Loop over all calibration subsamples
    #======================================================================
    for i, Calc in enumerate(CalcList):

        CalcMu = CalcMuList[i]

        PIDCuts = gbl.std.list('string')()
        for index, cut in enumerate(DLLCutList):
           PIDCuts.push_back(cut)

        Muon_eff = CalcMu.Perf(PIDCuts, False);
        Dummy = Calc.Perf_Scan(Muon_eff, PIDCuts, False)
        Dummy.SetName('Mu_eff_vs_' + PartName+'_eff_'+str(i))
        Dummy.SetTitle('Muon ID vs ' + PartName + ' MissID Efficiency' )
        Dummy.GetXaxis().SetTitle(PartName + " Miss-ID Efficiency")
        Dummy.GetYaxis().SetTitle("Muon ID Efficiency")

        canvas = ROOT.TCanvas()
        Dummy.Draw()
        canvas.SaveAs('Mu_eff_vs_' + PartName+'_eff_'+str(i) + '.pdf')

        Plots.append(Dummy)
    return Plots

    
if '__main__' == __name__:

    #======================================================================
    # List of cuts
    #======================================================================
    MagPolarity = 'MagUp'
    #MagPolarity = 'MagDown'


    #======================================================================
    # Studies
    #======================================================================
    MuStudy = True
    PiStudy = False
    KStudy  = False
    PStudy  = False

    #======================================================================
    # List of cuts
    #======================================================================
    #DLLCuts        = [ 'IsMuon == 1 ', 
    #                   'IsMuon == 1 && DLLmu > -5 ',
    #                   'IsMuon == 1 && DLLmu > -4 ',
    #                   'IsMuon == 1 && DLLmu > -2 ',
    #                   'IsMuon == 1 && DLLmu > 0 ',
    #                   'IsMuon == 1 && DLLmu > 1 ',
    #                   'IsMuon == 1 && DLLmu > 1.74 ',
    #                   'IsMuon == 1 && DLLmu > 2 ',
    #                   'IsMuon == 1 && DLLmu > 2.25 ',
    #                   'IsMuon == 1 && DLLmu > 3 ']
    DLLCuts        = [ 'IsMuon == 1 ']
    
    #======================================================================
    # Binning to consider
    #======================================================================
    PlotBinning = ROOT.RooBinning(3000,100000,'P')
    PlotBinning.addBoundary(6000);
    PlotBinning.addBoundary(8000);
    PlotBinning.addBoundary(10000);
    PlotBinning.addBoundary(12000);
    PlotBinning.addBoundary(14500);
    PlotBinning.addBoundary(17500);
    PlotBinning.addBoundary(21500);
    PlotBinning.addBoundary(27000);
    PlotBinning.addBoundary(32000);
    PlotBinning.addBoundary(40000);
    PlotBinning.addBoundary(60000);
    PlotBinning.addBoundary(70000);

    SecondBinning  = ROOT.RooBinning(200.,100000.,'PT')

    nFiles = 1

    #======================================================================
    # Final list of plots 
    # ======================================================================

    CalcMuList    = []
    CalcPiList    = []
    CalcKList     = []
    CalcPList     = []
    for i in xrange(0,nFiles):
        if MuStudy:
          DataSetMu    = Get_DataSet('Mu', MagPolarity, i)
          CalcMu       = gbl.PerfCalculator(gbl.MUONTrackDataSet)(DataSetMu)
          CalcMuList.append(CalcMu)
        if PiStudy:
          DataSetPi    = Get_DataSet('Pi', MagPolarity, i)
          CalcPi       = gbl.PerfCalculator(gbl.MUONTrackDataSet)(DataSetPi)
          CalcPiList.append(CalcPi)
        if KStudy:
          DataSetK     = Get_DataSet('K',  MagPolarity, i)
          CalcK        = gbl.PerfCalculator(gbl.MUONTrackDataSet)(DataSetK)
          CalcKList.append(CalcK)
        if PStudy:
          DataSetP     = Get_DataSet('P',  MagPolarity, i)
          CalcP        = gbl.PerfCalculator(gbl.MUONTrackDataSet)(DataSetP)
          CalcPList.append(CalcP)

    makeEffPlots = True
    makeMisIDPlots = True
    makeEffTables = True

    #======================================================================
    # Efficiency Tables
    # ======================================================================
    if makeEffTables:
        if MuStudy:
            Tables_Muon =   EffTables(DLLCuts,
                          'Mu',
                           PlotBinning,
                           SecondBinning,
                           CalcMuList)

        if PiStudy:
            Tables_Pion =   EffTables(DLLCuts,
                          'Pi',
                           PlotBinning,
                           SecondBinning,
                           CalcPiList)
  
        if KStudy:
            Tables_Kaon =   EffTables(DLLCuts,
                          'K',
                           PlotBinning,
                           SecondBinning,
                           CalcKList)

        if PStudy:
            Tables_Proton = EffTables(DLLCuts,
                          'P',
                           PlotBinning,
                           SecondBinning,
                           CalcPList)

    #======================================================================
    # Efficiency and MisId plots 
    # ======================================================================
    if makeEffPlots:
        if MuStudy:
            Plots_Muon =   EffPlots(DLLCuts,
                          'Mu',
                           PlotBinning,
                           CalcMuList)

        if PiStudy:
            Plots_Pion =   EffPlots(DLLCuts,
                          'Pi',
                           PlotBinning,
                           CalcPiList)
  
        if KStudy:
            Plots_Kaon =   EffPlots(DLLCuts,
                          'K',
                           PlotBinning,
                           CalcKList)

        if PStudy:
            Plots_Proton = EffPlots(DLLCuts,
                          'P',
                           PlotBinning,
                           CalcPList)

    #======================================================================
    # Muon Efficiency Vs MisId plots 
    # ======================================================================
    if makeMisIDPlots:
        if (MuStudy and PiStudy):
            Plots_Pion_Muon = EffVsMisIDPlots(DLLCuts,
                              'Pi',
                              PlotBinning,
                              CalcPiList,
                              CalcMuList)

        if (MuStudy and KStudy):
            Plots_Kaon_Muon = EffVsMisIDPlots(DLLCuts,
                              'K',
                              PlotBinning,
                              CalcKList,
                              CalcMuList)

        if (MuStudy and PStudy):
            Plots_Proton_Muon=EffVsMisIDPlots(DLLCuts,
                              'P',
                              PlotBinning,
                              CalcPList,
                              CalcMuList)

    #======================================================================
    # Open file to write TH1Fs to
    #======================================================================
    f_Out = ROOT.TFile('MUONPerf_Strip19_'+MagPolarity+'.root',
                            'UPDATE')
         
    if makeEffTables:
        for i in range(0, len(DLLCuts)):
          if MuStudy:
            for plot in Tables_Muon[i]:
                     plot.Write()
          if KStudy:
            for plot in Tables_Kaon[i]:
                     plot.Write()
          if PiStudy:
            for plot in Tables_Pion[i]:
                     plot.Write()
          if PStudy:
            for plot in Tables_Proton[i]:
                     plot.Write()
    
    if makeEffPlots:
        for i in range(0, len(DLLCuts)):
          if MuStudy:
            for plot in Plots_Muon[i]:
                     plot.Write()
          if KStudy:
            for plot in Plots_Kaon[i]:
                     plot.Write()
          if PiStudy:
            for plot in Plots_Pion[i]:
                     plot.Write()
          if PStudy:
            for plot in Plots_Proton[i]:
                     plot.Write()
    
    if makeMisIDPlots:
        if (MuStudy and PiStudy):
            for plot in Plots_Pion_Muon:
                  plot.Write()

        if (MuStudy and KStudy):
            for plot in Plots_Kaon_Muon:
                  plot.Write()

        if (MuStudy and PStudy):
            for plot in Plots_Proton_Muon:
                  plot.Write()

    if makeEffTables:
        if MuStudy:
          del Tables_Muon
        if PiStudy:
          del Tables_Pion
        if KStudy:
          del Tables_Kaon
        if PStudy:
          del Tables_Proton

    if makeEffPlots:
        if MuStudy:
          del Plots_Muon
        if PiStudy:
          del Plots_Pion
        if KStudy:
          del Plots_Kaon
        if PStudy:
          del Plots_Proton

    if makeMisIDPlots:
        if (MuStudy and PiStudy):
          del Plots_Pion_Muon
        if (MuStudy and KStudy):
          del Plots_Kaon_Muon
        if (MuStudy and PStudy):
          del Plots_Proton_Muon
    ##======================================================================
    # Close file
    #======================================================================
    
    f_Out.Close()

