from PIDPerfScripts.PerfResults import *
from PIDPerfScripts.startscreen import *

import ROOT
ROOT.gSystem.Load('libRooStats.so')

import sys
import getopt
   
def usage():
    print ' --------------------------------------------------------------------------------------------------'
    print ' Andrew Powell (a.powell1@physics.ox.ac.uk) January 24, 2013'
    print ' '
    print ' MakePerfHistsRunRange - Make performance histograms for a given:'
    print ' a) Field polarity (MagUp/MagDown)'
    print ' b) Stripping version (19/20/etc)'
    print ' c) Run range (If full run range is desired, pass --minRun=None and --maxRun=None) '
    print ' d) Kaon enhancing PID cut '
    print ' e) Proton enhancing PID cut'
    print ' Typical usage:'
    print " python MakeRICHPublicationPlots.py --magPolarity=MagUp                  "
    print "                                    --stripVersion=20                    "
    print "                                    --minRun=None                        "
    print "                                    --maxRun=None                        "
    print "                                    --kPIDCuts='[DLLK > 0.0, DLLK > 5.0, DLLpK > 0.0, DLLpK > 5.0]'"
    print "                                    --pPIDCuts='[DLLp > 0.0, DLLp > 5.0, DLLpK > 0.0, DLLpK > 5.0]'"
    print ' --------------------------------------------------------------------------------------------------'
    sys.exit(' ')
      
if '__main__' == __name__:

    start()

    try:
        opts, args = getopt.getopt(sys.argv[1:],'v:p:x:y:a:b',
                                   ['stripVersion=',
                                    'magPolarity=',
                                    'minRun=',
                                    'maxRun=',
                                    'kPIDCuts=',
                                    'pPIDCuts='])
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
        elif o in ['-a', '--kPIDCuts']:
            DLLCuts_Kpi = p[1:-1].split(',')
            print 'DLLCuts_Kpi  :',DLLCuts_Kpi
        elif o in ['-b', '--pPIDCuts']:
            DLLCuts_Ppi = p[1:-1].split(',')
            print 'DLLCuts_Ppi  :',DLLCuts_Ppi
            
    #======================================================================
    # Check DLL Cuts
    #======================================================================
    for cut in DLLCuts_Kpi:
        print cut

    for cut in DLLCuts_Ppi:
        print cut

    #=============================================================================
    # Declare Binning Schema (RooBinnings)
    #=============================================================================
    Mom_Bin_A = ROOT.RooBinning(2000,100000,'P')
    #Mom_Bin_A.addUniform(38,5000,100000)
    Mom_Bin_A.addUniform(40,2000,100000)
    BinSchema_A = gbl.std.vector('RooBinning*')()
    BinSchema_A.push_back(Mom_Bin_A)

    Mom_Bin_B = ROOT.RooBinning(5000,100000,'P')
    Mom_Bin_B.addUniform(38,5000,100000);
    #Mom_Bin_B.addUniform(28,5000,40000);
    #Mom_Bin_B.addUniform(17,40000,66000);
    #Mom_Bin_B.addUniform(2,66000, 70000);
    #Mom_Bin_B.addUniform(2,70000, 75000);
    #Mom_Bin_B.addUniform(6,75000, 90000);
    #Mom_Bin_B.addUniform(2,90000, 100000);
    BinSchema_B = gbl.std.vector('RooBinning*')()
    BinSchema_B.push_back(Mom_Bin_B)

    #======================================================================
    # Define dictionary to loop over
    #======================================================================    
    trackDict = {'K_as_K' : {'TrackType': 'K',
                             'DLLCuts'  : DLLCuts_Kpi,
                             'Binning'  : BinSchema_A,
                             'TrackCuts': 'Charge==Charge::Positive && K_P<100000',
                             'IsMuon'    : False
                             },
                'Pi_as_K' : {'TrackType': 'Pi',
                             'DLLCuts'  : DLLCuts_Kpi,
                             'Binning' : BinSchema_A,
                             'TrackCuts': 'Charge==Charge::Positive && Pi_P<100000',
                             'IsMuon'    : False
                             },
                 'P_as_P' : {'TrackType': 'P',
                             'DLLCuts'  : DLLCuts_Ppi,
                             'Binning'  : BinSchema_B,
                             'TrackCuts': 'Charge==Charge::Positive && P_P<100000',
                             'IsMuon'    : False
                             },
                'Pi_as_P' : {'TrackType': 'Pi',
                             'DLLCuts'  : DLLCuts_Ppi,
                             'Binning'  : BinSchema_A,
                             'TrackCuts': 'Charge==Charge::Positive && Pi_P<100000',
                             'IsMuon'    : False
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

    
            
    
