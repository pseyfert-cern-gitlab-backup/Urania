#/bin/env python

########################################################
### 
### chopTrees.py
###
### Author: Andrew Powell (a.powell1@physics.ox.ac.uk)
### Created: November 22, 2012
########################################################

import numpy as np
import pickle
import sys
import os.path
import warnings
import argparse
import ROOT

# ROOT should not parse the command-line options
ROOT.PyConfig.IgnoreCommandLineOptions=True
# ROOT should not start the Gui
ROOT.PyConfig.StartGuiThread = 0
  
class ShowArgumentsParser(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write('error: {0}\n\n'.format(message))
        parser.print_usage(sys.stderr)
        sys.stderr.write('\n'+self.description)
        sys.exit(2)

def chopTrees(fname_in, ntpname_list, fname_pkl, fileSuffix, out_path=''):
    #==================================================
    # Un-pickle the numpy array
    #==================================================
    runLims   = pickle.load( open( fname_pkl, "rb" ) )
    print "Got {0:d} run ranges".format(len(runLims))

    print ''
    print 'Run ranges:'
    print runLims
    
    #==================================================
    # Open TFile
    #==================================================
    f_in   = ROOT.TFile.Open(fname_in,'read')
    if not f_in:
        sys.stderr.write(("Failed to open file '{0}' "
                          "for reading").format(
            fname_in))
        sys.exit(1)
        
    #==================================================
    # Create list of TTrees to access
    #==================================================
    _trees = []
    for ntpname in ntpname_list:
        tree = ROOT.gDirectory.Get(ntpname)
        if not tree:
            sys.stderr.write(("Failed to retrieve TTree '{0}' "
                              "from file {1}").format(
                ntpname, fname_in))
            #sys.exit(1)
        else:
            _trees.append(tree)
        
    #==================================================
    # Skip if no events in this file
    #==================================================
    if len(_trees) == 0:
      return

    #==================================================
    # Loop over array of run ranges
    #==================================================
    nentries=0
    nentries_tree={ ntpname:0 for ntpname in ntpname_list }
    
    for i, runRange in enumerate(runLims):
        
        #==================================================
        # Create TFile for candidates in run range
        #==================================================
        if out_path=='':
            out_path='.'

        fname_out = '{dir}/PID_{idx}_{suf}.root'.format(
            dir=out_path, idx=i, suf=fileSuffix)
        print 'Creating output file {0}'.format(fname_out)
        f_out = ROOT.TFile.Open( fname_out, 'recreate' )
        if not f_out:
            sys.stderr.write(("Failed to open file '{0}' "
                              "for writing").format(
            fname_out))
            sys.exit(1)
            
        #==================================================
        # Create cut for this run range
        #==================================================
        cut = '(runNumber >= {runMin:d}) && (runNumber <= {runMax:d})'.format(
            runMin=runRange[0], runMax=runRange[1])
        print 'Run range cut: {0}'.format(cut)

        #==================================================
        # Make directories and copy trees
        #==================================================
        for itree, ntpname in enumerate(ntpname_list):
            d = f_out.mkdir(ntpname.split('/')[0])
            d.cd()
            tree_cpy = _trees[itree].CopyTree(cut)
            n_tree = tree_cpy.GetEntries()
            nentries += n_tree
            nentries_tree[ntpname] += n_tree
            
        #==================================================
        # Write and close TFile
        #==================================================
        f_out.Write()
        f_out.Close()

    for ntpname, n_tree in nentries_tree.items():
        print 'Processed {0:d} entries in tree {1}'.format(
            n_tree, ntpname)
    print 'Processed {0:d} total entries'.format(nentries)
        
def chopTreesLoop(in_fname_list, ntpname_list, fname_pkl, fileSuffix):

    #==================================================
    # Loop over list of input files
    #==================================================
    for i, fname in enumerate(in_fname_list):

        #==================================================
        # Determine path of file
        #==================================================
        import os
        path = os.path.dirname(fname)
        #==================================================
        # If no file continue
        #==================================================
        f_in  = ROOT.TFile.Open(fname,'read')
        if not f_in :
          warnings.warn("Input file '{0}' not found".format(fname))
          continue
        f_in.Close()
        #==================================================
        # Run chopTrees function
        #==================================================
        chopTrees(fname, ntpname_list, fname_pkl, fileSuffix, path)
        print 'Processed {ii} of {nn} files requested to be chopped.'.format(
            ii = i+1, nn = len(in_fname_list))
        
def chopTreesGanga(ntpname_list,
                   fname_pkl,
                   job_id,
                   min_subjob,
                   max_subjob,
                   ganga_dir,
                   fileSuffix,
                   nTuple_name):

    fname_list = []
    for subjob_id in range(min_subjob, max_subjob+1):
        fname_list.append('{dir}/{jid:d}/{sid:d}/output/{fname}'.format(
            dir=ganga_dir, jid=job_id, sid=subjob_id, fname=nTuple_name))

    print 'Input files:'
    print fname_list
    
    chopTreesLoop(fname_list,
                  ntpname_list,
                  fname_pkl,
                  fileSuffix)

if __name__ == '__main__':
    parser = ShowArgumentsParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        prog=os.path.basename(sys.argv[0]),
        description=("""Run over the output nTuples of a given ganga job """
                     """produced using PIDCalib/CalibDataSel and split it """
                     """into subsamples defined by the run limits contained """
                     """within a pickle file produced using """
                     """$CALIBDATASCRIPTSROOT/scripts/python/getRunRanges.py.       

For a full list of arguments, do: 'python {0} -h'""".format(
        os.path.basename(sys.argv[0]))),
        )

    # add the positional arguments
    parser.add_argument('jobID', metavar='<jobID>', type=int,
                        help=("The ganga job ID to process."))
    parser.add_argument('pklName', metavar='<pklName>',
                        help=("Name of the pickle file (including the path) "
                              "that contains the list of run ranges."))
    parser.add_argument('minSubJobID', metavar='<minSubJobID>', type=int,
                        help=("The minimum subjob ID to process."))
    parser.add_argument('maxSubJobID', metavar='<maxSubJobID>', type=int,
                        help=("The maximum subjob ID to process."))
    parser.add_argument('tupleDir', metavar='<tupleDir>', 
                        help=("Name of the directory in the input "
                              "file(s) containing the nTuple(s) to process. "
                              "Multiple directories can be specified as a "
                              "comma-separated list."))
    parser.add_argument('inputDir', metavar='<inputDir>',
                        help=("The top-level directory of the input files, "
                              "usually the ganga directory."))
    parser.add_argument('fileSuffix', metavar='<fileSuffix>',
                        help=("The suffix to append to the chopped "
                              "file names. N.B. The output files will be "
                              "named '{dir}/PID_{idx}_{suf}.root', where "
                              "{dir} is the same directory as the input file, "
                              "{idx} is the index (0 = 1st run range, "
                              "1 = 2nd run range etc.) and {suf} is the "
                              "file suffix."))
    
    # add the optional arguments
    parser.add_argument('-t', '--tupleName', dest='tupleName',
                        metavar='NAME', default='DecayTree',
                        help=("The name of the nTuple, exlc. the "
                              "directory (default: '%(default)s')."))
    parser.add_argument('-f', '--fileName', dest='inputFilename',
                        metavar='NAME', default='PIDCalib.root',
                        help=("The name of the input file, excl. the "
                              "path (default: '%(default)s')."))
    opts = parser.parse_args()

    treeList = [ '{0}/{1}'.format(tupleDir, opts.tupleName) \
                 for tupleDir in opts.tupleDir.split(',') ]
    
    print 'Job ID               : {0:d}'.format(opts.jobID)
    print 'Pickle filename      : {0}'.format(opts.pklName)
    print 'Min subjob           : {0:d}'.format(opts.minSubJobID)
    print 'Max subjob           : {0:d}'.format(opts.maxSubJobID)
    print 'nTuple list          : {0}'.format(str(treeList))
    print 'Input directory      : {0}'.format(opts.inputDir)
    print 'Input filename       : {0}'.format(opts.inputFilename)
    print 'File suffix          : {0}'.format(opts.fileSuffix)
    chopTreesGanga(treeList, opts.pklName, opts.jobID,
                   opts.minSubJobID, opts.maxSubJobID,
                   opts.inputDir, opts.fileSuffix,
                   opts.inputFilename)
    
