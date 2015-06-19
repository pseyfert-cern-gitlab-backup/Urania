'''An example weighting script which uses the P, PT, and ETA to calibrate an
Stripping13b B2DX signal TTree. The output is a RooDataSet with a per event weight
set.
'''
from GaudiPython import gbl

import ROOT

# This seems to be required to prevent seg faults, even on systems that load
# RooFit on demand. Worth experimenting with removing it.
ROOT.gSystem.Load('libRooStats.so')

if '__main__' == __name__:

    fileRoot = "/afs/cern.ch/lhcb/group/rich/vol1/RichPidCalib/CalibData/"

    #=============================================================================
    # Obtain Calibration Samples
    #=============================================================================

    f_Pion = ROOT.TFile.Open(fileRoot+'Reco10_DATA/MagUp/DSt_Pi_MagUp_Strip13b.root')
    wsPion = f_Pion.Get('RSDStCalib')
    Pion_Data = wsPion.data('data')

    f_Kaon = ROOT.TFile.Open(fileRoot+'Reco10_DATA/MagUp/DSt_K_MagUp_Strip13b.root')
    wsKaon = f_Kaon.Get('RSDStCalib')
    Kaon_Data = wsKaon.data('data')

    #=============================================================================
    # Obtain Signal Track Data
    #=============================================================================

    f_Sig = ROOT.TFile.Open(fileRoot+'Reco08_DATA/B2DPiFAV_Stripping10.root')
    t_Sig = f_Sig.Get('TTT')

    #=============================================================================
    # Declare Binning Schema (RooBinnings)
    #=============================================================================
    Mom_Bin = ROOT.RooBinning(5000,150000,'P')
    Pt_Bin  = ROOT.RooBinning(500,30000,'PT')
    Eta_Bin = ROOT.RooBinning(1.5,5,'ETA')

    Mom_Bin.addBoundary(9300) # R1 Kaon Threshold
    Mom_Bin.addBoundary(17675)# R1 Proton Threshold
    Mom_Bin.addBoundary(15600)# R2 Kaon Threshold
    Mom_Bin.addBoundary(20000)
    Mom_Bin.addBoundary(23000)
    Mom_Bin.addBoundary(26000)
    Mom_Bin.addBoundary(29650)# R2 Proton Threshold
    Mom_Bin.addUniform(24, 30000, 150000)
    Eta_Bin.addUniform(4, 1.5,5)

    BinSchema = gbl.std.vector('RooBinning*')()
    BinSchema.push_back(Mom_Bin)
    BinSchema.push_back(Pt_Bin)
    BinSchema.push_back(Eta_Bin)

    print('========== Binning Schema ==========')
    for binning in BinSchema:
        binning.Print()
    print('====================================')

    #===========================================================================
    # Create Instance of TrackDataSet for Signal tracks with which calibration
    # tracks will be weighted to
    #===========================================================================
    Mom = ROOT.RooRealVar('p3_P', '', Mom_Bin.lowBound(), Mom_Bin.highBound(), 'MeV/c')
    Pt = ROOT.RooRealVar('p3_PT', '', Pt_Bin.lowBound(), Pt_Bin.highBound(), 'MeV/c')
    Eta = ROOT.RooRealVar('p3_TRACK_Eta', '', Eta_Bin.lowBound(), Eta_Bin.highBound(), '')
    DLLK = ROOT.RooRealVar('p3_PIDK', '', -150, 150, '')
    DLLp = ROOT.RooRealVar('p3_PIDp', '', -150, 150, '')
    ID = ROOT.RooRealVar('p3_ID', '', 210, 212, '') # Select +ve Tracks
    BMass = ROOT.RooRealVar('Bu_M','',5279.15-50.0,5279.15+50.0)

    Sig_DataSet = gbl.TrackDataSet('B->DPi Pion'
                                   , 'Signal Track'
                                   , t_Sig
                                   , ROOT.RooArgSet(Mom
                                                    , Pt
                                                    , Eta
                                                    , DLLK
                                                    , DLLp
                                                    , ID
                                                    , BMass
                                                    )
                                   , 'p3_P'
                                   , 'p3_PT'
                                   , 'p3_TRACK_Eta'
                                   , 'p3_PIDK'
                                   , 'p3_PIDp'
                                   )
    Sig_DataSet.get(0)
    Sig_DataSet.Print('v')

    
    #===========================================================================
    # Declare Instance of TrackDataSet for Calibration tracks within BinSchema
    #===========================================================================
    Pion_DataSetAll = gbl.TrackDataSet('Calib. Pion'
                                       , ''
                                       , Pion_Data
                                       , Pion_Data.get()
                                       , 'Pi_P'
                                       , 'Pi_PT'
                                       , 'Pi_Eta'
                                       , 'Pi_CombDLLK'
                                       , 'Pi_CombDLLp'
                                       )
    del Pion_Data
    Pion_DataSet = Pion_DataSetAll.SetInBinSchema(BinSchema)
    del Pion_DataSetAll

    Kaon_DataSetAll = gbl.TrackDataSet('Calib. Kaon'
                                       , ''
                                       , Kaon_Data
                                       , Kaon_Data.get()
                                       , 'K_P'
                                       , 'K_PT'
                                       , 'K_Eta'
                                       , 'K_CombDLLK'
                                       , 'K_CombDLLp'
                                       )

    del Kaon_Data
    Kaon_DataSet = Kaon_DataSetAll.SetInBinSchema(BinSchema)
    del Kaon_DataSetAll

    Pion_DataSet.Print('v')
    Kaon_DataSet.Print('v')

    #===========================================================================
    # Make a Copy of the Signal DataSet with Events Only in those Bins that
    # Contained Calibration Pion Tracks
    #===========================================================================
    ANDPion_Sig_DataSet = Sig_DataSet.ANDInBins(Pion_DataSet
                                                , BinSchema
                                                , ''
                                                , 'nsig_sw'
                                                )

    ANDPion_Sig_DataSet.Print()# was printValue(cout). No cout in pyROOT?
    
    #===========================================================================
    # Create a 'Bin' Weigthed Copy of Pion_DataSet
    #===========================================================================
    Weighted_PionBin = Pion_DataSet.WeightInBins(Sig_DataSet
                                                 , 'Wgt'
                                                 , BinSchema
                                                 , True
                                                 , ''
                                                 , 'nsig_sw'
                                                 )
    
    #===========================================================================
    # Make a Copy of the Signal DataSet with Events Only in those Bins that 
    # Contained Calibration Kaon Tracks
    #===========================================================================
    ANDKaon_Sig_DataSet = Sig_DataSet.ANDInBins(Kaon_DataSet
                                                , BinSchema
                                                , ''
                                                , 'nsig_sw'
                                                )
    
    ANDKaon_Sig_DataSet.Print()# was printValue(cout)

    #===========================================================================
    # Create a 'Bin' Weigthed Copy of Kaon_DataSet
    #===========================================================================
    Weighted_KaonBin = Kaon_DataSet.WeightInBins(Sig_DataSet
                                                 , 'Wgt'
                                                 , BinSchema
                                                 , True
                                                 , ''
                                                 , 'nsig_sw'
                                                 )
    
    Weighted_PionBin.get(0)
    Weighted_PionBin.Print('v')
    Weighted_KaonBin.get(0)
    Weighted_KaonBin.Print('v')
    
    #===========================================================================
    # Weight with New Weight Variable
    #===========================================================================
    Weighted_PionBin_sw = gbl.TrackDataSet('Test'
                                           , ''
                                           , Weighted_PionBin
                                           , Weighted_PionBin.get()
                                           , ''
                                           , 'nsig_sw'
                                           )
    
    Weighted_KaonBin_sw = gbl.TrackDataSet('Test'
                                           , ''
                                           , Weighted_KaonBin
                                           , Weighted_KaonBin.get()
                                           , ''
                                           , 'nsig_sw'
                                       )
    
    print('{0}\t{1}'.format(Weighted_PionBin_sw.isWeighted()
                            , Weighted_KaonBin_sw.isWeighted()
                            )
          )
    Weighted_PionBin_sw.Print()# was printValue(cout)
    Weighted_KaonBin_sw.Print()# was printValue(cout)
    
    Weighted_PionBin_wgt = gbl.TrackDataSet('Test'
                                            , ''
                                            , Weighted_PionBin
                                            , Weighted_PionBin.get()
                                            , ''
                                            , 'Wgt'
                                            )

    Weighted_KaonBin_wgt = gbl.TrackDataSet('Test'
                                            , ''
                                            , Weighted_KaonBin
                                            , Weighted_KaonBin.get()
                                            , ''
                                            , 'Wgt'
                                            )
    
    print('{0}\t{1}'.format(Weighted_PionBin_wgt.isWeighted()
                            , Weighted_KaonBin_wgt.isWeighted()
                            )
          )
    Weighted_PionBin_wgt.Print()# was printValue(cout)
    Weighted_KaonBin_wgt.Print()# was printValue(cout)
    
    #===========================================================================
    # Write to File within a RooWorkspace
    #===========================================================================
    ws = ROOT.RooWorkspace('ws','')
    # import is a Python keyword and it is not allowed to be the name of a
    # function. Of course C++ has no such restriction and hence the workspace
    # import function can't be accessed via ws.import.
    ws_import = getattr(ws, 'import')
    ws_import(ANDPion_Sig_DataSet, ROOT.RooFit.Rename('ANDPion_Sig_Pion'))
    ws_import(ANDKaon_Sig_DataSet, ROOT.RooFit.Rename('ANDKaon_Sig_Pion'))
    ws_import(Weighted_PionBin, ROOT.RooFit.Rename('CalPion'))
    ws_import(Weighted_KaonBin, ROOT.RooFit.Rename('CalKaon'))
    ws.writeToFile('DataPion_32Momx4Eta.root')
# if '__name__'==__main__
