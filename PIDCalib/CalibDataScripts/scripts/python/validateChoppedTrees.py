#/bin/env python

########################################################
### 
### validateChopTrees.py
###
### Author: Philip Hunt
### Created: November 28, 2013
########################################################
import numpy as np
import pickle
import sys
import os.path
import shutil
import warnings
import imp
import glob
import argparse
import ROOT

# ROOT should not parse the command-line options
ROOT.PyConfig.IgnoreCommandLineOptions=True

# ROOT should not start the Gui
ROOT.PyConfig.StartGuiThread = 0

import imp
packageRoot=os.getenv('CALIBDATASCRIPTSROOT').rstrip('\n')
gangaJobFuncs = imp.load_source(
    'gangaJobFuncs',
    '{0}/scripts/python/gangaJobFuncs.py'.format(packageRoot)
    )
    
class ShowArgumentsParser(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write('error: {0}\n\n'.format(message))
        parser.print_usage(sys.stderr)
        sys.stderr.write('\n'+self.description)
        sys.exit(2)

# For the given input directory (generally the ganga directory),
# stripping version, magnet polarity, nTuple name and file suffix,
# check that the chopped TTrees were created correctly.
# If 'cuts' is specified (e.g. for 'MuonUnBiased' samples), then
# these cuts will be applied prior to performing the checks.
#
# This function checks that:
# 1) The number of chopped trees is as expected;
# 2) The number of entries in the chopped trees are as expected.
# 3) The run ranges in the chopped trees are as expected (in that
#    there is no difference in the number of entries with/without
#    imposing the run-range cuts);
def validateChoppedTrees(inputDir, stripVersion, magPol, ntpname,
                         fileSuffix, cuts=''):
                         
    # get the list of job IDs from the ganga configuration script
    gangaJobFuncs.updateEnvFromShellScript( ('{bdir}/jobs/Stripping{strp}'
                                             '/configureGangaJobs.sh').format(
        bdir=packageRoot,strp=stripVersion) )

    # get the list of jobIDs for the given magnet polarity
    jidVar = ''
    if magPol=='Down':
        jidVar='CALIBDATA_JIDS_DOWN'
    elif magPol=='Up':
        jidVar='CALIBDATA_JIDS_UP'
    else:
        raise NameError("Unknown magnet polarity '{0}'".format(magPol))
    jids_str=os.getenv(jidVar)
    if len(jids_str)==0:
        raise NameError("Environmental variable '{0}' is not set".format(
            jidVar))
    jobIDs=[int(jid) for jid in jids_str.split()]

    # open the pickle file, and get the run-range list and list of
    # expected entries
    pklName = ('{bdir}/jobs/Stripping{strp}/ChopTrees/'
               '{pol}_runLimits_{suf}.pkl').format(
        bdir=packageRoot, strp=stripVersion,
        pol = magPol.lower(), suf=fileSuffix)

    pklFile = open(pklName, 'rb') # will raise IOError if file not found
    
    runRangeList = pickle.load(pklFile)
    runEntriesList = pickle.load(pklFile)
    assert len(runRangeList)==len(runEntriesList)
    
    # get the number of chopped trees
    for jid in jobIDs:
        nChoppedTrees = gangaJobFuncs.getNumChoppedTrees(inputDir, jid,
                                                         fileSuffix)
        passed = nChoppedTrees==len(runRangeList)
        print 'Test of number of chopped trees for job {0:d}: {1}'.format(
            jid, 'PASSED' if passed else 'FAILED')
        if not passed:
            raise ValueError( ('JobID {jid:d}: Expected {n_exp:d} '
                               'chopped trees, got {n:d}').format(
                jid=jid, n_exp=len(runRangeList), n=nChoppedTrees) )

    # loop over chopped tree indices, get the input TChain and check
    # the number of entries and the run ranges are correct
    for i in range(nChoppedTrees):
        
        # get the list of input filenames
        fnames = ROOT.vector('std::string')()
        for jid in jobIDs:
            gb_fname = ('{bdir}/{jid}/*/output/PID_{idx}_{suf}.root').format(
                bdir=inputDir, jid=jid, idx=i, suf=fileSuffix)
            fnames_jid = glob.glob(gb_fname)
            for fname in fnames_jid:
                fnames.push_back(fname)

        # NB. We need to convert the numpy types to regular python types
        # so they can be converted to C types
        nEntries_exp = long(runEntriesList[i])
        runMin = int(runRangeList[i][0])
        runMax = int(runRangeList[i][1])
        passed = ROOT.ValidateChoppedTrees(ntpname, fnames, i, nEntries_exp,
                                           runMin, runMax, cuts)
        if not passed:
            exit(1)
        
    print 'Passed all tests!'


# For the given input directory (generally the ganga directory),
# stripping version, magnet polarity, loP and hiP Lambda0 nTuple names
# and file suffix, check that the chopped TTrees were created correctly.
# If 'cuts' is specified (e.g. for 'MuonUnBiased' samples), then
# these cuts will be applied prior to performing the checks.
#
# This function checks (for each job ID) that:
# 1) The number of chopped trees is as expected;
# 2) The number of entries in the chopped trees are as expected.
# 3) The run ranges in the chopped trees are as expected (in that
#    there is no difference in the number of entries with/without
#    imposing the run-range cuts);
def validateChoppedTrees_Lam0(inputDir, stripVersion, magPol,
                              ntpname_lop, ntpname_hip,
                              fileSuffix, cuts='', partName='P'):

    # get the list of job IDs from the ganga configuration script
    gangaJobFuncs.updateEnvFromShellScript( ('{bdir}/jobs/Stripping{strp}'
                                             '/configureGangaJobs.sh').format(
        bdir=packageRoot,strp=stripVersion) )

    # get the list of jobIDs for the given magnet polarity
    jidVar = ''
    if magPol=='Down':
        jidVar='CALIBDATA_JIDS_DOWN'
    elif magPol=='Up':
        jidVar='CALIBDATA_JIDS_UP'
    else:
        raise NameError("Unknown magnet polarity '{0}'".format(magPol))
    jids_str=os.getenv(jidVar)
    if len(jids_str)==0:
        raise NameError("Environmental variable '{0}' is not set".format(
            jidVar))
    jobIDs=[int(jid) for jid in jids_str.split()]

    # open the pickle file, and get the run-range list and list of
    # expected entries
    pklName = ('{bdir}/jobs/Stripping{strp}/ChopTrees/'
               '{pol}_runLimits_{suf}.pkl').format(
        bdir=packageRoot, strp=stripVersion,
        pol = magPol.lower(), suf=fileSuffix)

    pklFile = open(pklName, 'rb') # will raise IOError if file not found
    
    runRangeList = pickle.load(pklFile)
    runEntriesList = pickle.load(pklFile)
    assert len(runRangeList)==len(runEntriesList)
    
    # get the number of chopped trees
    for jid in jobIDs:
        nChoppedTrees = gangaJobFuncs.getNumChoppedTrees(inputDir, jid,
                                                         fileSuffix)
        passed = nChoppedTrees==len(runRangeList)
        print 'Test of number of chopped trees for job {0:d}: {1}'.format(
            jid, 'PASSED' if passed else 'FAILED')
        if not passed:
            raise ValueError( ('JobID {jid:d}: Expected {n_exp:d} '
                               'chopped trees, got {n:d}').format(
                jid=jid, n_exp=len(runRangeList), n=nChoppedTrees) )

                
    # loop over chopped tree indices, get the input TChain and check
    # the number of entries and the run ranges are correct
    for i in range(nChoppedTrees):
        
        # get the list of input filenames
        fnames = ROOT.vector('std::string')()
        for jid in jobIDs:
            gb_fname = ('{bdir}/{jid}/*/output/PID_{idx}_{suf}.root').format(
                bdir=inputDir, jid=jid, idx=i, suf=fileSuffix)
            fnames_jid = glob.glob(gb_fname)
            for fname in fnames_jid:
                fnames.push_back(fname)

        nEntries_exp = long(runEntriesList[i])
        runMin = int(runRangeList[i][0])
        runMax = int(runRangeList[i][1])
        
        passed = ROOT.ValidateChoppedTrees(ntpname_lop, ntpname_hip,
                                           fnames, i, nEntries_exp,
                                           runMin, runMax, cuts, partName)
        if not passed:
            exit(1)
        
    print 'Passed all tests!'

if __name__=='__main__':
    
    parser = ShowArgumentsParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        prog=os.path.basename(sys.argv[0]),
        description=("""Validates that the nTuples split by run range, """
                     """produced by """
                     """$CALIBDATASCRIPTSROOT/scripts/python/chopTrees.py """
                     """are consistent with the pickle files produced by """
                     """$CALIBDATASCRIPTSROOT/scripts/python/getRunRanges.py.

For a full list of arguments, do: 'python {0} -h'""".format(
        os.path.basename(sys.argv[0]))),
        )

    # add the positional arguments
    parser.add_argument('stripVersion', metavar='<stripVersion>',
                        help="The stripping version (e.g. '20')")
    parser.add_argument('magPol', metavar='<magPol>',
                        help="The magnet polarity ('Up' or 'Down')")
    parser.add_argument('inputDir', metavar='<inputDir>',
                        help=("The top-level directory of the input "
                              "files, usually the ganga directory."))
    # add the optional arguments
    parser.add_argument('-t', '--tupleName', dest='tupleName',
                        metavar='NAME', default='CalibPID',
                        help=("The name of the nTuple, exlc. the "
                              "directory (default: '%(default)s')."))
    opts = parser.parse_args()

    ROOT.gROOT.SetBatch(True)
    ROOT.gROOT.LoadMacro("ValidateChoppedTrees.C+")
    
    # map of nTuple directory (excl. tuple name) to
    # file suffix
    suffixMap = {}
    suffixMap['DSt2D0Pi_D02RSKPiTuple'] =  'dst_k_and_pi'
    suffixMap['JpsiFromBNoPIDNoMipTuple'] = 'jpsi_mu'
    suffixMap['DSt2D0Pi_D02RSKPi_MuonUnBiasedTuple'] = \
        'dst_k_and_pi_muonUnBiased'
        
    # map of nTuple directory (excl. tuple name) to
    # selection cuts (if any)
    muCut='{0}_MuonTisTagged==1&&{0}_Probe==1&&{1}_Tag==1'
    hCut='{0}_MuonTisTagged==1'
    
    jpsiCut='({0})||({1})'.format(muCut.format('Mu0', 'Mu1'), 
                                  muCut.format('Mu1', 'Mu0'))
    dstCut='({0})||({1})'.format(hCut.format('K'), 
                                 hCut.format('Pi'))                          
    cutsMap={}
    cutsMap['DSt2D0Pi_D02RSKPiTuple'] = ''
    cutsMap['JpsiFromBNoPIDNoMipTuple'] = jpsiCut
    cutsMap['DSt2D0Pi_D02RSKPi_MuonUnBiasedTuple'] = dstCut
    
    # map of Lambda0 LoP and hiP nTuple directories 
    # (excl. tuple name) to file suffix
    suffixMap_lam0={}
    suffixMap_lam0[('Lam02PPi_LoPTuple','Lam02PPi_HiPTuple')] = \
        'lam0_p'
    suffixMap_lam0[('Lam02PPi_LoP_MuonUnBiasedTuple',
                     'Lam02PPi_HiP_MuonUnBiasedTuple')] = \
        'lam0_p_muonUnBiased'

    # map of Lambda0 LoP and hiP nTuple directories 
    # (excl. tuple name) to selection cuts (if any)
    lam0Cut = hCut.format('P')
    cutsMap_lam0={}
    cutsMap_lam0[('Lam02PPi_LoPTuple','Lam02PPi_HiPTuple')] = ''
    cutsMap_lam0[('Lam02PPi_LoP_MuonUnBiasedTuple',
                 'Lam02PPi_HiP_MuonUnBiasedTuple')] = lam0Cut
        
    # validate the calibration samples in nTupleList
    for ntpdir, fileSuffix in suffixMap.items():
        print 80*"*"
        print "Validating '{0}' sample".format(ntpdir)
        cuts = cutsMap[ntpdir]
        ntpname='{0}/{1}'.format(ntpdir, opts.tupleName)
        validateChoppedTrees(opts.inputDir, opts.stripVersion, 
                             opts.magPol, ntpname,
                             fileSuffix, cuts)  
                 
    # validate the Lambda0 calibration samples in nTupleList_loP and
    # nTupleList_hiP
    for ntpdirs, fileSuffix in suffixMap_lam0.items():
        print 80*"*"
        print "Validating '{0}' samples".format(str(ntpdirs))
        cuts = cutsMap_lam0[ntpdirs]
        ntpname_loP='{0}/{1}'.format(ntpdirs[0], opts.tupleName)
        ntpname_hiP='{0}/{1}'.format(ntpdirs[1], opts.tupleName)
        validateChoppedTrees_Lam0(opts.inputDir, opts.stripVersion, 
                                  opts.magPol, ntpname_loP,
                                  ntpname_hiP, fileSuffix,
                                  cuts, 'P') 
