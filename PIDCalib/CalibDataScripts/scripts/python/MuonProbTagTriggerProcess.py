import numpy as np
import pickle
import sys
import getopt
from ROOT import TFile, TTree, TCut, gSystem, gDirectory, TObject, gROOT
gROOT.LoadMacro( 'MuonProbTagTrigger.C+' )
from ROOT import MuonProbTagTrigger

def usage():
    print ' --------------------------------------------------------------------------------------------------'
    print ' Juan Otalora (jotalo@if.ufrj.br) Feb 26, 2013'
    print ' '
    print ' MuonProbTagTriggerProcess.py - Run over a given ganga job output  produced  using '
    print ' PIDCalib/CalibDataSel (Muon Version) and select prob and tag Muons. Perform a TIS '
    print ' cut over Muon0 and Muon1 and reduze the number of columns to a decent value.  Put '
    print ' results are allocated in /afs/cern.ch/work/j/jotalora/PID_Calib/gangadir'
    print ' Typical usage:'
    print ' python MuonProbTagTriggerProcess.py                                               '
    print '            --ganga_dir=/afs/cern.ch/work/j/jotalora/PID_Calib/gangadir/workspace/jotalora/LocalXML'
    print '            --input_dir=/tmp/jotalora/Collision12-Reco13a-Stripping19a-MagUp_CalibSel              '
    print '            --inputJobID=5                                                                         '
    print '            --outputJobID=5                                                                        '
    print '            --minSubJob=0                                                                          '
    print '            --maxSubJob=90                                                                         '
    print
    
def MuonProbTagTriggerProcess(input_job_id, 
                              output_job_id, 
                              subjob_min, 
                              subjob_max,
                              ganga_dir='/afs/cern.ch/work/j/jotalora/PID_Calib/gangadir/workspace/jotalora/LocalXML',
                              input_dir='/tmp/jotalora/Collision12-Reco13a-Stripping19a-MagUp_CalibSel',
                              nTuple_name='PID_Modes.root'):
    nTuple_name='PID_Modes.root'
    for subjob in xrange(subjob_min, subjob_max+1):
        file_name_in  = input_dir+'/'+input_job_id+'/'+str(subjob)+'/output/'+nTuple_name

        f_in   = TFile.Open(file_name_in,'read')
        if not f_in:
          print 'File ' + file_name_in + ' Not Found'
          continue
        f_in.Close()
        # change the output filename if the input and output directories are the same
        nTuple_name_out = nTuple_name
        if ganga_dir==input_dir:
            s = nTuple_name.rpartition('.')
            if len(s[0])==0: s = s[::1]
            nTuple_name_out = '%s_MuonUnBiased%s%s' %(s[0], s[1], s[2])
        file_name_out = ganga_dir+'/'+output_job_id+'/'+str(subjob)+'/output/'+nTuple_name_out
        gSystem.Exec('mkdir -p ' + ganga_dir+'/'+output_job_id+'/'+str(subjob)+'/output')
        MuonProbTagTrigger(file_name_in,file_name_out)

if __name__ == '__main__':
    
    #======================================================================
    # Run the makeCurves function if run by the python interpretator
    #======================================================================
    opts = None
    args = None
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'g:t:i:o:x:y', ['ganga_dir=', 'input_dir=', 'inputJobID=', 'outputJobID=', 'minSubJob=','maxSubJob='])
    except getopt.GetoptError:
        usage()
        sys.exit(0)
    if len(opts) != 6:
        usage()
        sys.exit(0)
    for o,p in opts:
        if o in   ['x', '--minSubJob']:
            subjob_min = int(p)
        elif o in ['y', '--maxSubJob']:
            subjob_max = int(p)
        elif o in ['-i', '--inputJobID']:
            input_job_id = p
        elif o in ['-o', '--outputJobID']:
            output_job_id = p
        elif o in ['-t', '--input_dir']:
            input_dir = p
        elif o in ['-g', '--ganga_dir']:
            ganga_dir = p
            
    print "Ganga directory: ", ganga_dir, type(ganga_dir)
    print "Input directory: ", input_dir, type(input_dir)
    print "Input ID: ", input_job_id, type(input_job_id)
    print "Output ID: ", output_job_id, type(output_job_id)
    print "Min subjob: ", subjob_min, type(subjob_min)
    print "Max subjob: ", subjob_max, type(subjob_max)
    
    MuonProbTagTriggerProcess(input_job_id, output_job_id, subjob_min, subjob_max, ganga_dir, input_dir)

    print 'Done'
