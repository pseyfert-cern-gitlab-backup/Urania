from PIDPerfScripts.DataFuncs import *
from PIDPerfScripts.PerfCalcFuncs import *
from PIDPerfScripts.startscreen import *

import numpy as np
import ROOT
ROOT.gSystem.Load('libRooStats.so')

import sys
import getopt

def drange(start, stop, step):
    r = start
    while r < stop:
       yield r
       r += step
   
def usage():
    print ' --------------------------------------------------------------------------------------------------'
    print ' Andrew Powell (a.powell1@physics.ox.ac.uk) January 28, 2013'
    print ' '
    print ' MakePerfCurvesStudy - Make performance curves for a given:'
    print ' a)Min and Max DLLK cut values (Must be integers)'
    print ' Typical usage:'
    print " python MUONPerfCurvesStudy.py --minDLLCut=-10                    "
    print "                               --maxDLLCut=3                      "
    print ' --------------------------------------------------------------------------------------------------'
    sys.exit(' ')

      
def getFieldFlipDictionary():    
    #======================================================================
    # Define dictionary with list of runs for specified magnetic field pol
    # Determined referring to the following webpage:
    # http://lbtriggerreport.cern.ch/reports/
    #======================================================================
    Strip2FieldFlip = { '17' : {'RecoV'   : '12',
                                'UpRuns'   : np.array([[ 89933,  90207], [ 93398,  97028], [ 98900, 101862],
                                                       [102499, 102907], [103954, 104414]]),
                                'DownRuns' : np.array([[ 87665,  87977], [ 90256,  93282], [ 97114,  98882],
                                                       [101891, 102452], [103049, 103686]])
                                },
                        '20' : {'RecoV'   : '14',
                                'UpRuns'   : np.array([[114205, 114287], [115518, 117103], [118326, 123803],
                                                       [125566, 126680], [128411, 129978], [130911, 131940],
                                                       [133624, 133785]]),
                                'DownRuns' : np.array([[111761, 113146], [114316, 115464], [117192, 118286],
                                                       [123910, 125115], [126824, 128110], [130316, 130861],
                                                       [131973, 133587]])
                                }
                        }
    
    return Strip2FieldFlip


def main(StripVersion, MagPolarity, DLLCutList, RunMin, RunMax):
    #======================================================================
    # Define the main function that will be run for every run range
    #======================================================================
    print 'Kaon'
    KaonPIDResults = GetPerfResultList(MakePIDResultList, 
                                       StripVersion,
                                       MagPolarity,
                                       'K',
                                       DLLCutList,
                                       'K_P < 100000', #'Charge==Charge::Positive && K_P<100000',
                                       RunMin,
                                       RunMax,
                                       True)

    print 'Pion'
    PionPIDResults = GetPerfResultList(MakePIDResultList, 
                                       StripVersion,
                                       MagPolarity,
                                       'Pi',
                                       DLLCutList,
                                       'Pi_P < 100000', #'Charge==Charge::Positive && Pi_P<100000',
                                       RunMin,
                                       RunMax,
                                       True)
    
    print 'Proton'
    ProtonPIDResults = GetPerfResultList(MakePIDResultList, 
                                       StripVersion,
                                       MagPolarity,
                                       'P',
                                       DLLCutList,
                                       'P_P < 100000', #'Charge==Charge::Positive && P_P<100000',
                                       RunMin,
                                       RunMax,
                                       True)

    print 'Muon'
    MuonPIDResults = GetPerfResultList(MakePIDResultList, 
                                       StripVersion,
                                       MagPolarity,
                                       'Mu',
                                       DLLCutList,
                                       'Mu_P < 100000', #'Charge==Charge::Positive && Mu_P<100000',
                                       RunMin,
                                       RunMax,
                                       True)


    #======================================================================
    # Make Weighted Average
    #======================================================================
    print 'AvResult'
    Kaon_AvResult = WeightedAveragePIDResults(KaonPIDResults)
    Pion_AvResult = WeightedAveragePIDResults(PionPIDResults)
    Proton_AvResult = WeightedAveragePIDResults(ProtonPIDResults)
    Muon_AvResult = WeightedAveragePIDResults(MuonPIDResults)

    #======================================================================
    # Make TGraph
    #======================================================================
    print 'Make TGraph'
    graphMuVvsPi = makeTGraph(Muon_AvResult, Pion_AvResult, 'MuonVsPion')
    graphPiVvsMu = makeTGraph(Pion_AvResult, Muon_AvResult, 'PionVsMuon')
    
    graphMuVsK = makeTGraph(Muon_AvResult, Kaon_AvResult, 'MuonVsKaon')
    graphKVsMu = makeTGraph(Kaon_AvResult, Muon_AvResult, 'KaonVsMuon')
     
    graphMuVsP = makeTGraph(Muon_AvResult, Proton_AvResult, 'MuonVsProton')
    graphPVsMu = makeTGraph(Proton_AvResult, Muon_AvResult, 'ProtonVsMuon')

    #======================================================================
    # Open file to write TH1Fs to
    #======================================================================
    f_Out = ROOT.TFile('MUONPerfCurves_'+'Strip'+StripVersion+'_'+MagPolarity+'_'+RunMin+'_'+RunMax+'.root',
                       'RECREATE')

    graphMuVvsPi.Write()
    graphPiVvsMu.Write()
    
    graphMuVsK.Write()
    graphKVsMu.Write()
     
    graphMuVsP.Write()
    graphPVsMu.Write()

    #======================================================================
    # Close file
    #======================================================================
    f_Out.Close()
    

if '__main__' == __name__:

    start()

    try:
        opts, args = getopt.getopt(sys.argv[1:],'m:n',
                                   ['minDLLCut=',
                                    'maxDLLCut='])
    except getopt.GetoptError:
        usage()
    if len(opts) != 2:
        usage()
    for o,p in opts:
        if o in ['-m', '--minDLLCut']:
            minDLLCut = int(p)
            print 'minDLLCut      :',minDLLCut
        elif o in ['-n', '--maxDLLCut']:
            maxDLLCut = int(p)
            print 'maxDLLCut      :',maxDLLCut

    #======================================================================
    # Confirm DLL cuts are integers
    #======================================================================
    if not isinstance(minDLLCut, int) or not isinstance(maxDLLCut, int):
        print 'minDLLCut = {min}, maxDLLCut = {max}'.format(min=minDLLCut,max=maxDLLCut)
        print '**** DLL values must be integers, not {min_type} and {max_type} ****'.format(min_type=type(minDLLCut),
                                                                                            max_type=type(maxDLLCut))
        sys.exit(1)

    #======================================================================
    # List of cuts
    #======================================================================
    DLLRange = drange(minDLLCut,maxDLLCut+1, 0.25) 
    DLLCutList = gbl.std.list('string')()
    DLLCutList.push_back('IsMuon == 1')
    for i in DLLRange:
        DLLCutList.push_back('IsMuon == 1 && DLLmu > ' +str(i))
        print 'IsMuon == 1 && DLLmu > ' +str(i)

    #======================================================================
    # Loop over field-flip dictionary
    #======================================================================
    for StripVersion, dict in getFieldFlipDictionary().items():
        for runRange in dict['UpRuns']:
            print runRange, runRange[0], runRange[1]
            main(StripVersion, 'MagUp', DLLCutList, str(runRange[0]), str(runRange[1]))
        for runRange in dict['DownRuns']:
            print runRange, runRange[0], runRange[1]
            main(StripVersion, 'MagDown', DLLCutList, str(runRange[0]), str(runRange[1]))
        
