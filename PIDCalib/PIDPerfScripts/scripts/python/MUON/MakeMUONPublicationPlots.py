from PIDPerfScripts.PerfResults import *
from PIDPerfScripts.startscreen import *

import ROOT
ROOT.gSystem.Load('libRooStats.so')

import sys
import getopt
   
def usage():
    print ' --------------------------------------------------------------------------------------------------'
    print ' Juan Martin Otalora Goicochea (jotalo@if.ufrj.br) March 15, 2013'
    print ' '
    print ' MakeMuonPublicationPlots - Make efficiency histograms for a given:'
    print ' a) Field polarity (MagUp/MagDown)'
    print ' b) Stripping version (19/20/etc)'
    print ' c) Run range (If full run range is desired, pass --minRun=None and --maxRun=None) '
    print ' d) Muon enhancing PID cut'
    print ' Typical usage:'
    print " python MakeMUONPublicationPlots.py --magPolarity=MagUp                  "
    print "                                    --stripVersion=20                    "
    print "                                    --minRun=None                        "
    print "                                    --maxRun=None                        "
    print "                                    --PIDCuts='[IsMuon==1, IsMuon==1 && DLLmu > -4.0, IsMuon==1 && DLLmu > -2.0, IsMuon==1 && DLLmu > 0.0, IsMuon==1 && DLLmu > 1.0, IsMuon==1 && DLLmu > 2.0, IsMuon==1 && DLLmu > 3.0]'"
    print ' --------------------------------------------------------------------------------------------------'
    sys.exit(' ')
      
if '__main__' == __name__:

    start()

    try:
        opts, args = getopt.getopt(sys.argv[1:],'v:p:x:y:a',
                                   ['stripVersion=',
                                    'magPolarity=',
                                    'minRun=',
                                    'maxRun=',
                                    'PIDCuts=',
                                    'pPIDCuts='])
    except getopt.GetoptError:
        usage()
    if len(opts) != 5:
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
        elif o in ['-a', '--PIDCuts']:
            DLLCuts = p[1:-1].split(',')
            print 'DLLCuts   :',DLLCuts
            
    #======================================================================
    # Check DLL Cuts
    #======================================================================
    for cut in DLLCuts:
        print cut

    #=============================================================================
    # Declare Binning Schema (RooBinnings)
    #=============================================================================
    Mom_Bin = ROOT.RooBinning(3000,100000,'P')
    Mom_Bin.addBoundary(6000);
    Mom_Bin.addBoundary(8000);
    Mom_Bin.addBoundary(10000);
    Mom_Bin.addBoundary(12000);
    Mom_Bin.addBoundary(14500);
    Mom_Bin.addBoundary(17500);
    Mom_Bin.addBoundary(21500);
    Mom_Bin.addBoundary(27000);
    Mom_Bin.addBoundary(32000);
    Mom_Bin.addBoundary(40000);
    Mom_Bin.addBoundary(60000);
    Mom_Bin.addBoundary(70000);

    BinSchema = gbl.std.vector('RooBinning*')()
    BinSchema.push_back(Mom_Bin)


    #======================================================================
    # Define dictionary to loop over
    #======================================================================    
    trackDict = {
                 'Mu_as_Mu' : {'TrackType': 'Mu',
                             'DLLCuts'  : DLLCuts,
                             'Binning'  : BinSchema,
                             'TrackCuts': 'Mu_P<100000',
                             'IsMuon': True
                             },
                 'Pi_as_Mu' : {'TrackType': 'Pi',
                              'DLLCuts'  : DLLCuts,
                              'Binning' : BinSchema,
                              'TrackCuts': 'Pi_P<100000',
                              'IsMuon': True
                              },
                 'P_as_Mu' : {'TrackType': 'P',
                             'DLLCuts'  : DLLCuts,
                             'Binning'  : BinSchema,
                             'TrackCuts': 'P_P<100000',
                             'IsMuon': True
                             },
                 'K_as_Mu' : {'TrackType': 'K',
                              'DLLCuts'  : DLLCuts,
                              'Binning'  : BinSchema,
                              'TrackCuts': 'K_P<100000',
                              'IsMuon': True
                              }
                 }                       

    #======================================================================
    # Make Performance Plots
    #======================================================================
    CalcAveragePerfPlotsAndWriteToFile(trackDict,
                                       StripVersion,
                                       MagPolarity,
                                       RunMin,
                                       RunMax)

    
            
    
