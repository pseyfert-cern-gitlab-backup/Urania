#!/bin/env python
import sys
import os.path
import argparse
import pickle
import numpy as np
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

# convert the output of GetRunRanges to numpy arrays
def GetRunRangesAsArray(runRangeVect):
    
    # first, contruct a list of two-tuples corresponding to the run ranges
    runRangeList = [ (r.first.first, r.first.second) for r in runRangeVect ]
    # get the list of entries (for printing purposes)
    runRangeEntries = [ r.second for r in runRangeVect ]

    print 'Got run range list (nRanges = {0:d}):'.format(len(runRangeList))
    print '['
    for i in range(len(runRangeList)):
        print '  ({runMin:d}, {runMax:d}), nEntries = {ev:d}'.format(
            runMin=runRangeList[i][0],
            runMax=runRangeList[i][1],
            ev=runRangeEntries[i]
            )
    print ']'
    
    # now, convert to a numpy array
    runRangeArr = np.asarray(runRangeList)
    entriesArr = np.asarray(runRangeEntries)
    return runRangeArr, entriesArr

if __name__=='__main__':

    parser = ShowArgumentsParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        prog=os.path.basename(sys.argv[0]),
        description=("""Create a pickle file that contains a numpy array """
                     """of (minRun,maxRun), where the the range of """
                     """runs spanned by minRun and maxRun corresponds """
                     """to approximately two million entries (this number """
                     """can be modified) in the input nTuples.

For a full list of arguments, do: 'python {0} -h'""".format(
        os.path.basename(sys.argv[0]))),
        )

    # add the positional arguments
    parser.add_argument('tupleDir_loP', metavar='<tupleDir_loP>', 
                        help=("Sets the name of the directory in the input "
                              "file(s) containing the low-momentum Lambda0 "
                              "nTuple(s) to process."))
    parser.add_argument('tupleDir_hiP', metavar='<tupleDir_hiP>', 
                        help=("Sets the name of the directory in the input "
                              "file(s) containing the high-momentum Lambda0 "
                              "nTuple(s) to process."))
    parser.add_argument('pklName', metavar='<pklName>',
                        help='Sets the name of the pickle file.')
    parser.add_argument('inputFiles', metavar='<inputFile>', nargs='+',
                        help=("Sets the name of the input file(s)."))

    # add the optional arguments
    parser.add_argument('-p', '--partName', dest='partName',
                        metavar='NAME', default='P',
                        help=("Sets the name of the proton particle "
                        "in the input nTuples (default: '%(default)s')."))
    parser.add_argument('-t', '--tupleName', dest='tupleName',
                        metavar='NAME', default='CalibPID',
                        help=("Sets the name of the nTuple, exlc. the "
                              "directory (default: '%(default)s')."))
    parser.add_argument('-c', '--cuts', dest='cuts', metavar='CUTS',
                        default='',
                        help=("Sets the list of cuts to apply to the "
                              "sample(s) prior to determine the run ranges "
                              "(default: '%(default)s')."))
    parser.add_argument('-m', '--maxEntries', dest='maxEntries',
                        metavar='NUM', type=int, default=2000000,
                        help=("Maximum number of events per run range, "
                              "maxEntries, (default: %(default)d)."))
    parser.add_argument('-s', '--stepFrac', dest='stepFrac',
                        metavar='FRAC', type=float, default=0.01,
                        help=("Fraction to reduce maxEntries by when "
                              "attempting to find a value of maxEntries "
                              "that minimises the difference between "
                              "maxEntries and the remainder after "
                              "dividing the number of entries by "
                              "maxEntries (default: %(default)f)."))
    parser.add_argument('-f', '--minFrac', dest='minFrac',
                        metavar='FRAC', type=float, default=0.9,
                        help=("Minimum fraction of maxEntries allowed "
                              "for the remainder after "
                              "dividing the number of entries by "
                              "maxEntries (default: %(default)f)."))
    parser.add_argument('-q', '--quiet', dest='verbose',
                        action='store_false', default=True,
                        help='Suppresses the printing of verbose messages')
    opts = parser.parse_args()

    ROOT.gROOT.SetBatch(True)

    ROOT.gROOT.LoadMacro('GetRunRanges.C+')
    ROOT.gInterpreter.GenerateDictionary('std::pair<unsigned int, unsigned int>',
                                         'utility')
    ROOT.gInterpreter.GenerateDictionary('std::pair< std::pair<unsigned int, '
                                         'unsigned int>, long long >',
                                         'utility')
    ROOT.gInterpreter.GenerateDictionary(('std::vector< std::pair< std::pair'
                                          '<unsigned int, unsigned int>,'
                                          'long long > >'),
                                         'vector;utility')
    
    if opts.verbose:
        print 'Tuple directory (loP):    {0}'.format(opts.tupleDir_loP)
        print 'Tuple directory (hiP):    {0}'.format(opts.tupleDir_hiP)
        print 'Tuple name:               {0}'.format(opts.tupleName)
        print 'Pickle filename:          {0}'.format(opts.pklName)
        if opts.cuts!='':
            print 'Cuts:                     {0}'.format(opts.cuts)
        print 'Initial maxEntries: {0}'.format(opts.maxEntries)
        print "maxEntries step fraction: {0:f}".format(opts.stepFrac)
        print "maxEntries minimum remainder fraction: {0:f}".format(
            opts.minFrac)
        print 'Input files:'
        
    # fill the vector of input filenames
    fnames = ROOT.vector('std::string')()
    for iname, fname in enumerate(opts.inputFiles):
        if opts.verbose:
            print '{0:d}:    {1}'.format(iname, fname)
        fnames.push_back(fname)
        
    runRanges = ROOT.GetRunRanges(opts.tupleDir_loP,
                                  opts.tupleDir_hiP,
                                  fnames,
                                  opts.cuts, opts.tupleName,
                                  opts.maxEntries,
                                  opts.partName,
                                  opts.verbose,
                                  opts.stepFrac,
                                  opts.minFrac)
  
    # convert the vector to a numpy array 
    runRangeArr, entriesArr = GetRunRangesAsArray(runRanges)
        
    # open the pickle file
    pklFile = open(opts.pklName, 'wb')
    pickle.dump(runRangeArr, pklFile)
    pickle.dump(entriesArr, pklFile)
    pklFile.close()
