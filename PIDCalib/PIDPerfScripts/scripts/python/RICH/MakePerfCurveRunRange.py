from PIDPerfScripts.DataFuncs import *
from PIDPerfScripts.PerfCalcFuncs import *
from PIDPerfScripts.startscreen import *

import ROOT
ROOT.gSystem.Load('libRooStats.so')

import sys
import getopt
   
def usage():
    print ' --------------------------------------------------------------------------------------------------'
    print ' Andrew Powell (a.powell1@physics.ox.ac.uk) January 28, 2013'
    print ' '
    print ' MakePerfCurvesRunRange - Make performance curves for a given:'
    print ' a) Field polarity (MagUp/MagDown)'
    print ' b) Stripping version (19/20/etc)'
    print ' c) Run range (If full run range is desired, pass --minRun=None and --maxRun=None) '
    print ' d) Min and Max DLLK cut values (Must be integers)'
    print ' Typical usage:'
    print " python MakePerfCurvesRunRange.py --magPolarity=MagUp                 "
    print "                                  --stripVersion=20                   "
    print "                                  --minRun=114205                     "
    print "                                  --maxRun=114287                     "
    print "                                  --minDLLCut=-15                     "
    print "                                  --maxDLLCut=15                      "
    print ' --------------------------------------------------------------------------------------------------'
    sys.exit(' ')

      
if '__main__' == __name__:

    start()

    try:
        opts, args = getopt.getopt(sys.argv[1:],'v:p:x:y:m:n',
                                   ['stripVersion=',
                                    'magPolarity=',
                                    'minRun=',
                                    'maxRun=',
                                    'minDLLCut=',
                                    'maxDLLCut='])
    except getopt.GetoptError:
        usage()
    if len(opts) != 6:
        usage()
    for o,p in opts:
        if o in ['-v', '--stripVersion']:
            StripVersion = p
            print 'StripVersion :',StripVersion
        elif o in ['-p', '--magPolarity']:
            MagPolarity = p
            print 'MagPolarity  :',MagPolarity
        elif o in ['-x', '--minRun']:
            RunMin = (p if p!='None' else None)
            print 'RunMin       :',RunMin
        elif o in ['-y', '--maxRun']:
            RunMax = (p if p!='None' else None)
            print 'RunMax       :',RunMax
        elif o in ['-m', '--minDLLCut']:
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
