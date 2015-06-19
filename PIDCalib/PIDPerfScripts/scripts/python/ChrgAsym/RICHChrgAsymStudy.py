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
    print ' Andrew Powell (a.powell1@physics.ox.ac.uk) January 29, 2013'
    print ' '
    print ' MakePerfCurvesRunRange - Make performance curves for a given:'
    print ' a) Stripping version (17/20)'
    print ' b) Run Range (If full run range is desired, pass --minRun=None and --maxRun=None)'
    print ' c) Min and Max DLLK cut values (Must be integers)'
    print ' d) Set of kaon and pion track cuts'
    print ' Typical usage:'
    print " python RICHChrgAsymStudy.py --stripVersion=17                                    "
    print "                             --minRun=85000                                       "
    print "                             --maxRun=91999                                       "
    print "                             --minDLLCut=-15                                      "
    print "                             --maxDLLCut=15                                       "
    print "                             --kaonCuts='Charge==Charge::Positive && K_P<100000'  "
    print "                             --pionCuts='Charge==Charge::Positive && Pi_P<100000' "
    print ' --------------------------------------------------------------------------------------------------'
    sys.exit(' ')

def main(StripVersion, DLLCutList, RunMin, RunMax, Kaoncut, Pioncut):
    #======================================================================
    # Define the main function that will be run for every run range
    #======================================================================
    KaonPIDResults_Up = GetPerfResultList(MakePIDResultList, 
                                          StripVersion,
                                          'MagUp',
                                          'K',
                                          DLLCutList,
                                          Kaoncut,
                                          RunMin,
                                          RunMax)

    KaonPIDResults_Down = GetPerfResultList(MakePIDResultList, 
                                            StripVersion,
                                            'MagDown',
                                            'K',
                                            DLLCutList,
                                            Kaoncut,
                                            RunMin,
                                            RunMax)

    PionPIDResults_Up = GetPerfResultList(MakePIDResultList, 
                                          StripVersion,
                                          'MagUp',
                                          'Pi',
                                          DLLCutList,
                                          Pioncut,
                                          RunMin,
                                          RunMax)

    PionPIDResults_Down = GetPerfResultList(MakePIDResultList, 
                                            StripVersion,
                                            'MagDown',
                                            'Pi',
                                            DLLCutList,
                                            Pioncut,
                                            RunMin,
                                            RunMax)

    #======================================================================
    # Make Weighted Average
    #======================================================================
    KaonUp_AvResult = WeightedAveragePIDResults(KaonPIDResults_Up)
    PionUp_AvResult = WeightedAveragePIDResults(PionPIDResults_Up)
    KaonDown_AvResult = WeightedAveragePIDResults(KaonPIDResults_Down)
    PionDown_AvResult = WeightedAveragePIDResults(PionPIDResults_Down)

    #======================================================================
    # Make Simple Average of field Polarity results
    #======================================================================
    Kaon_AvResult = SimpleAveragePIDResults(KaonUp_AvResult, KaonDown_AvResult)
    Pion_AvResult = SimpleAveragePIDResults(PionUp_AvResult, PionDown_AvResult)

    #======================================================================
    # Make TGraph
    #======================================================================
    graph_up   = makeTGraph(KaonUp_AvResult,   PionUp_AvResult,   'MagUp')
    graph_down = makeTGraph(KaonDown_AvResult, PionDown_AvResult, 'MagDown')
    graph_av   = makeTGraph(Kaon_AvResult,     Pion_AvResult,     'SimpleAverage')
    
    #======================================================================
    # Open file to write TH1Fs to
    #======================================================================
    f_Out = ROOT.TFile('RICHPerfCurves_'+'Strip'+StripVersion+'_'+RunMin+'_'+RunMax+'.root',
                       'RECREATE')
    graph_up.Write()
    graph_down.Write()
    graph_av.Write()
    
    #======================================================================
    # Close file
    #======================================================================
    f_Out.Close()
    

if '__main__' == __name__:

    start()

    try:
        opts, args = getopt.getopt(sys.argv[1:], 'v:x:y:a:b:m:n',
                                   ['stripVersion=', 'minRun=', 'maxRun=', 'minDLLCut=', 'maxDLLCut=', 'kaonCuts=', 'pionCuts='])
    except getopt.GetoptError:
        usage()
    if len(opts) != 7:
        print len(opts)
        usage()
    for o,p in opts:
        if o in ['-v',  '--stripVersion']:
            StripVersion = p
        elif o in ['x', '--minRun']:
            runMin = (p if p!='None' else None)
        elif o in ['y', '--maxRun']:
            runMax = (p if p!='None' else None)
        elif o in ['-a', '--minDLLCut']:
            MinDLLCut = int(p)
        elif o in ['-b', '--maxDLLCut']:
            MaxDLLCut = int(p)
        elif o in ['-m', '--kaonCuts']:
            Kaoncut = p
        elif o in ['-n', '--pionCuts']:
            Pioncut = p

    #======================================================================
    # Confirm DLL cuts are integers
    #======================================================================
    if not isinstance(MinDLLCut, int) or not isinstance(MaxDLLCut, int):
        print 'minDLLCut = {min}, maxDLLCut = {max}'.format(min=MinDLLCut,max=MaxDLLCut)
        print '**** DLL values must be integers, not {min_type} and {max_type} ****'.format(min_type=type(MinDLLCut),
                                                                                            max_type=type(MaxDLLCut))
        sys.exit(1)

    #======================================================================
    # List of cuts
    #======================================================================
    DLLRange = range(MinDLLCut,MaxDLLCut+1) 
    DLLCutList = gbl.std.list('string')()
    for i in DLLRange:
        DLLCutList.push_back('DLLK > ' +str(i))
        print 'DLLK > ' +str(i)

    #======================================================================
    # Loop over field-flip dictionary
    #======================================================================
    main(StripVersion, DLLCutList, runMin, runMax, Kaoncut, Pioncut)
        
