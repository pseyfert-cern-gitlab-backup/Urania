from PIDPerfScripts.DataFuncs import *
from PIDPerfScripts.PerfCalcFuncs import *
from PIDPerfScripts.startscreen import *

import numpy as np
import ROOT
ROOT.gSystem.Load('libRooStats.so')

import sys
import getopt
   
def usage():
    print ' --------------------------------------------------------------------------------------------------'
    print ' Andrew Powell (a.powell1@physics.ox.ac.uk) January 28, 2013'
    print ' '
    print ' MakePerfCurvesRunRange - Make performance curves for a given:'
    print ' a)Min and Max DLLK cut values (Must be integers)'
    print ' Typical usage:'
    print " python MakePerfCurvesRunRange.py --minDLLCut=-15                     "
    print "                                  --maxDLLCut=15                      "
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
    KaonPIDResults = GetPerfResultList(MakePIDResultList, 
                                       StripVersion,
                                       MagPolarity,
                                       'K',
                                       DLLCutList,
                                       'Charge==Charge::Positive && K_P<100000',
                                       RunMin,
                                       RunMax)

    PionPIDResults = GetPerfResultList(MakePIDResultList, 
                                       StripVersion,
                                       MagPolarity,
                                       'Pi',
                                       DLLCutList,
                                       'Charge==Charge::Positive && Pi_P<100000',
                                       RunMin,
                                       RunMax)

    #======================================================================
    # Make Weighted Average
    #======================================================================
    Kaon_AvResult = WeightedAveragePIDResults(KaonPIDResults)
    Pion_AvResult = WeightedAveragePIDResults(PionPIDResults)

    #======================================================================
    # Make TGraph
    #======================================================================
    graph = makeTGraph(Kaon_AvResult, Pion_AvResult, 'KaonVsPion')

    #======================================================================
    # Open file to write TH1Fs to
    #======================================================================
    f_Out = ROOT.TFile('RICHPerfCurves_'+'Strip'+StripVersion+'_'+RunMin+'_'+RunMax+'.root',
                       'RECREATE')
    graph.Write()
    
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
    DLLRange = range(minDLLCut,maxDLLCut+1) 
    DLLCutList = gbl.std.list('string')()
    for i in DLLRange:
        DLLCutList.push_back('DLLK > ' +str(i))
        print 'DLLK > ' +str(i)

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
        
