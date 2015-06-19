#!/bin/env python
from PIDPerfScripts.startscreen import *
from PIDPerfScripts.RunRangeFuncs import GetRealPartTypes
from PIDPerfScripts.RunRangeFuncs import CheckRealPartType

import math
import sys
import os
#import optparse
import argparse
import exceptions
import ROOT

class TFileError(exceptions.Exception):
    pass

class TTreeError(exceptions.Exception):
    pass


def covar(i, j, varList, var2ErrMap):
    ivar = varList[i]
    ierr = var2ErrMap[ivar]
    if i==j:
        return ierr*ierr
    else:
        jvar = varList[j]
        # not sure whether I should treat
        # tracks of same type as 100% correlated,
        # or tracks of the same type residing in
        # the same calibration bin
        #
        # for the moment, I'll do the former
        if ivar.type==jvar.type:
            jerr = var2ErrMap[jvar]
            return ierr*jerr
    return 0


def getEvtEff(trackBinList, eff_trackBinMap):
    eff=1
    for trBin in trackBinList:
        eff_tr = eff_trackBinMap[trBin]
        eff *= eff_tr
    return eff


def getEvtErr(trackBinList, eff_trackBinMap, err_trackBinMap):
    var=0
    rtracks = range(len(trackBinList))
    totaleff=1
    for i in rtracks:
        eff_i = eff_trackBinMap[trackBinList[i]]
        totaleff*=eff_i
        for j in rtracks:
            trVar = covar(i, j, trackBinList, err_trackBinMap);
            eff_j = eff_trackBinMap[trackBinList[j]]
            if eff_i==0 or eff_j==0:
                var+=0
            else:
                var+= trVar / (eff_i*eff_j)
    return totaleff*math.sqrt(var)

def getBranch(tt, brName):
    if not tt:
        raise TTreeError("Cannot get branch. No TTree specified")
    br = tt.GetBranch(brName)
    if not br:
        raise TTreeError("Failed to retrieve branch %s from tree %s" %(
            brName, tt.GetName()))
    return br


def getLeafVal(br, ientry):
    if not br:
        raise TTreeError("Cannot get leaf value. No TBranch specified")
    nb = br.GetEntry(ientry)
    if nb<=0:
        msg=("Got invalid number of bytes ({nb:d}) for entry {entry:d}, "
             "branch {br}").format(nb=nb, entry=ientry, br=br.GetName())
        raise TTreeError(msg)
    return br.GetLeaf(br.GetName()).GetValue()
            

# class speficying the track type and bin number
class TrackBin(object):
    def __init__(self, trType, bin):
        CheckRealPartType(trType)
        self._trType=trType
        try:
            self._bin=int(bin)
        except ValueError:
            msg=("Invalid bin number '{0}' - bin number must "
                 "be an integer").format(bin)
            raise TTreeError(msg)

    def type(self):
        return self._trType

    def bin(self):
        return self._bin
    
    def __str__(self):
        s="track type = '{0}', bin number = {1:d}".format(
            self._trType, self._bin)
        return s
    def __repr__(self):
        s="TrackBin({0}, {1:d})".format(self._trType, self._bin)
        return s
    
    # comparison operators
    def __eq__(self, other):
        if self._trType!=other._trType: return False
        if self._bin!=other._bin: return False 
        return True
    def __ne__(self, other):
        if self._trType==other._trType: return False
        if self._bin==other._bin: return False
        return True

    def __lt__(self, other):
        # compare track type first
        if self._trType < other._trType: return True
        else:
            # now compare bin number
            if self._bin < other._bin: return True
        return False

    def __gt__(self, other):
        # compare track type first
        if self._trType > other._trType: return True
        else:
            # now compare bin number
            if self._bin > other._bin: return True
        return False

    def __le__(self, other):
        # compare track type first
        if self._trType <= other._trType: return True
        else:
            # now compare bin number
            if self._bin <= other._bin: return True
        return False

    def __ge__(self, other):
        # compare track type first
        if self._trType >= other._trType: return True
        else:
            # now compare bin number
            if self._bin >= other._bin: return True
        return False
        
class ShowArgumentsParser(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write('error: %s\n\n' %message)
        parser.print_usage(sys.stderr)
        sys.stderr.write('\n'+self.description)
        sys.exit(2)

if '__main__'==__name__:
    start()
    
    parser = ShowArgumentsParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        prog=os.path.basename(sys.argv[0]),
        description=("""Recalculates the statistical uncertainty of the """
                     """average PID efficiency, accounting for the """
                     """statistical uncertainty of the reference sample, """
                     """ for a given:
                     a) <inputFilename>, as produced by the """
                     """'PerformMultiTrackCalib' script

The efficiency is also recalculated and compared to the efficiency """
                     """(and error) from the 'naive' average """
                     """determined by MultiTrackCalibTool.

The final argument, <track>, specifies the reference track, and takes """
                     """the form [<trackName>, <trackType>], where """
                     """<trackName> is the name of the track in the """
                     """reference TTree and <trackType> is the type """
                     """of track.

If the reference sample contains multiple final-state tracks, the remaining
tracks can be specified as additional arguments.

Reference tracks of the same type are treated as 100% statistically correlated.

NB. It is assumed that the TTree is named 'CalibTool_PIDCalibTree'

Valid track types are \"K\", \"P\", \"Pi\" or \"Mu\".

For a full list of arguments, do: 'python {0} -h'

e.g. python {0} \"$HOME/PIDResults.root\" \"[Kaon, K]\" \"[Pion, Pi]\"
""").format(os.path.basename(sys.argv[0]))
    )
       
    ## add the positional arguments
    parser.add_argument('inputFilename', metavar='<inputFilename>',
                        help="Sets the input filename")
    parser.add_argument('tracks', metavar='<track>', nargs='+',
                        help="Sets the name of the reference "
                        "track(s) and its track type")

    ## add the optional arguments
    addGroup = parser.add_argument_group("further options")
    addGroup.add_argument("-q", "--quiet", dest="verbose",
                          action="store_false", default=True,
                          help="suppresses the printing of verbose information")
    addGroup.add_argument("-d", "--debug", dest="debug",
                          action="store_true", default=False,
                          help="add extra debugging information")
    addGroup.add_argument("-p", "--printFreq", dest="printFreq",
                          type=long, default=-1,
                          help="sets the print frequency of "
                          "verbose event information, where 0 "
                          "and 1 will print out on every event "
                          "and <0 will disable the printing "
                          "(default: %(default)s)")
    expGroup = parser.add_argument_group("EXPERIMENTAL options",
                                         "The options are experimental, and "
                                         "are still being tested."
                                         "Use at your own risk!")
    expGroup.add_argument("-w", "--isWeighted", dest="isWeighted",
                        action="store_true", default=False,
                        help="use the reference sample event "
                        "weights when calculating the average "
                        "efficiency and uncertainty")    
    opts = parser.parse_args()
        
    fname = opts.inputFilename
    
    trackArgs = opts.tracks

    trackMap = {} # map of track name to type
    #trackTypes = []
    for arg in trackArgs:
        trackName = None
        trackType = None
        if not arg.startswith("[") or not arg.endswith("]"):
            parser.error("Invalid track variable string '%s'" %arg)
        trackInfo=arg[1:-1].split(",")
        if len(trackInfo) != 2:
            parser.error("Invalid track variable string '%s'" %arg)
        trackName = trackInfo[0].strip()
        trackType = trackInfo[1].strip()
        validTrTypes=GetRealPartTypes()
        if trackType not in validTrTypes:
            msg=("Invalid track type '{0}' in track variable "
                 "string '{1}. Valid track types are {2}'").format(
                trackType, arg, str(validTrTypes))
            parser.error(msg)
        #if trackType not in trackTypes:
        #    trackTypes.append(trackType)
        trackMap[trackName]=trackType

    tname='CalibTool_PIDCalibTree'
        
    print '===================================='
    print "Input filename: {0}".format(fname)
    for i, v in trackMap.items():
        print "Track name and type (track {0}): {0}".format(i, str(v))
    print "Weighted reference sample? {0}".format(opts.isWeighted)
    print '===================================='
        
    f = ROOT.TFile.Open(fname)
    if not f:
        msg=("Failed to open file '{0}' for reading").format(fname)
        raise TFileError(msg)
    
    tt = f.Get(tname)
    if not tt:
        msg=("Failed to retrieve TTree '{tt}' from file '{tf}'").format(
            tt=tname, tf=fname)
        raise TFileError(msg)

    print "Total entries: {0:d}".format(tt.GetEntries())

    
    # Get branches for each track
    # Store track name to TBranch pointer
    branches_eff={} # PID calib. efficiency for each track
    branches_err={} # PID calib. eff. error for each track
    branches_bin={} # Bin number for each track
    
    for trackName in trackMap.keys():
        # get calibration efficiency and uncertainty branches
        branches_eff[trackName]=getBranch(tt, '%s_PIDCalibEff' %trackName)
        branches_err[trackName]=getBranch(tt, '%s_PIDCalibEffError' %trackName)
            
        # get bin number branch      
        branches_bin[trackName]=getBranch(tt,
                                          '%s_PIDCalibBinNumber' %trackName)
            

    # get the 'naive' average efficiency and uncertainty branches
    br_eff = getBranch(tt, 'Event_PIDCalibEff')
    br_err = getBranch(tt, 'Event_PIDCalibErr')
    br_eff_weighted = getBranch(tt, 'Event_PIDCalibEffWeight')
    br_err_weighted = getBranch(tt, 'Event_PIDCalibErrWeight')

    # event weight branch (if applicable)
    br_weight = None
    if opts.isWeighted:
        br_weight = getBranch(tt, 'Event_Weight')
     
    # floats to store the 'naive' average efficiencies and errors
    naiveAvgEff=0.
    naiveAvgErrSq=0. # sigma^2
    naiveAvgEffWeighted=0.
    naiveAvgErrSqWeighted=0.
   
    # We need the following information to obtain the efficiencies/errors:
    #
    # 1) For each event, we need to get the list of TrackBins, where each
    # element in the list corresponds to the particle type and bin number
    # we need to know both the type and bin so that we can check if the
    # tracks are statistically correlated (we treat tracks of the same
    # type and in the same bin as 100% correlated)
    #
    # 2) Globally, we need maps of (sorted) TrackBin list to:
    #    a) efficiency
    #    b) statistical uncertainty on the efficiency (incl. correlations)
    #
    # 3) Globally, we need a map of TrackBin list to the number of
    # entries in the reference sample corresponding to this TrackBin list
    
    effMap={} # map of track bin list to efficiency
    errMap={} # map of track bin list to efficiency uncertainty
    sumwMap={} # map of track bin list to sum of weights
    
    # loop over events and get the above information
    nentries = tt.GetEntries()
    nentriesSq = nentries*nentries
    sumEntries=0
    for ientry in xrange(0,nentries):
        printEntry = False
        if opts.verbose and opts.printFreq>=0:
            if opts.printFreq==0 or (ientry % opts.printFreq == 0):
                printEntry=True

        if printEntry:
            print 70*"*"
            print "Entry number {0:d}".format(ientry)
        
        # get the naive efficiency and uncertainty
        naiveEff = getLeafVal(br_eff, ientry)
        naiveErr = getLeafVal(br_err, ientry)
        naiveEffWeighted = getLeafVal(br_eff_weighted, ientry)
        naiveErrWeighted = getLeafVal(br_err_weighted, ientry)

        if printEntry:
            msg=("'Naive' event efficiency = "
                 "({eff:.3f}+/-{err:.3f})%").format(
                eff=100.*naiveEff, err=100.*naiveErr)
            print msg
            msg=("'Naive' weighted event efficiency = "
                 "({eff:.3f}+/-{err:.3f})%").format(
                eff=100.*naiveEffWeighted,
                err=100.*naiveErrWeighted)
            print msg
                    
        trackBinList = []

        # maps of track bin to efficiency and uncertainty
        eff_trackBinMap={}
        err_trackBinMap={}
        
        # loop over tracks and fill track bin list
        iTr = 0
        for trackName, trackType in trackMap.iteritems():
            # get track efficiency and uncertainty
            eff_tr = getLeafVal(branches_eff[trackName], ientry)
            err_tr = getLeafVal(branches_err[trackName], ientry)

            # get track bin number
            bin_tr = int(getLeafVal(branches_bin[trackName], ientry))
                
            # create the track bin
            trBin=TrackBin(trackType, bin_tr)

            if printEntry:
                msg=("Track {itr}, {trbin}, efficiency = "
                     "({eff:.3f}+/-{err:.3f})%").format(
                    itr=iTr, trbin=trBin, eff=100*eff_tr, err=100*err_tr)
                print msg
                    
            # add the track bin to the list of track bins
            # for the current event
            trackBinList.append(trBin)

            # add the track bin to the maps of track bin to
            # efficiency/uncertainty
            eff_trackBinMap[trBin]=eff_tr
            err_trackBinMap[trBin]=err_tr
            
            iTr+=1
            
        # end loop over tracks
        
        # convert the track bin list to a tuple
        trackBinTuple = tuple(trackBinList)
        if printEntry:
            print "Track bin tuple: {0}".format(str(trackBinTuple))
            
        # get the event efficiency and error
        eff_evt = getEvtEff(trackBinTuple, eff_trackBinMap)
        err_evt = getEvtErr(trackBinTuple, eff_trackBinMap, err_trackBinMap)

        if printEntry:
            print "Event efficiency = ({eff:.3f}+/-{err:.3f})%".format(
                eff=100.*eff_evt, err=100.*err_evt)
                
        effMap[trackBinTuple]=eff_evt
        errMap[trackBinTuple]=err_evt

        # add the event weight to the sum of weights for this track bin list
        # if the data are unweighted, then the event weight is unity
        weight=1
        #evtWeight=1
        if opts.isWeighted:
            weight = getLeafVal(br_weight, ientry)
            #evtWeight = math.pow(weight, len(trackBinTuple))
        if printEntry:
            print "Event weight = {0:.3f}".format(weight)
            #print "Total efficiency weight = %.3f" %evtWeight
            
        sumwMap[trackBinTuple]=sumwMap.setdefault(trackBinTuple,0)+weight

        sumEntries+=weight
        
        # naive weighted error is wrong - no weight applied
        naiveErrWeighted*=weight
        
        # increment to 'naive' average efficency + uncertainty
        naiveAvgEff += naiveEff/nentries
        naiveAvgErrSq += (naiveErr*naiveErr)/nentriesSq
        naiveAvgEffWeighted += naiveEffWeighted/nentries
        naiveAvgErrSqWeighted += (naiveErrWeighted*naiveErrWeighted)/nentriesSq

    # end loop over entries 
    if opts.debug:
        print "Number of entries = {0:d}".format(nentries)
        print "Sum of entries = {0:d}".format(sumEntries)
        
    # finally, calculate the average efficiency and error

    # first, the 'naive' values
    naiveAvgErr = math.sqrt(naiveAvgErrSq)
    naiveAvgErrWeighted = math.sqrt(naiveAvgErrSqWeighted)
                
    # now, the 'correct' values
    iBin=0
    weightList=[]
    weightedEffList=[]
    effList=[]
    errList=[]
    for trackBinTuple, sumw in sumwMap.iteritems():
        eff = effMap[trackBinTuple]
        err = errMap[trackBinTuple]
        if opts.debug:
            msg=("Efficiency of bin {bin:d} = ({bineff:.3f}+/-{binerr:.3f})%, "
                 "nentries = {weight:.3f}").format(
                bin=iBin, bineff=100*eff, binerr=100*err, weight=sumw)
            print msg
            #      if eff!=0:
            #         harmEffInv += (sumw/eff)/sumEntries
        effList.append(eff)
        weightList.append(sumw)
        weightedEffList.append(eff*sumw)
        errList.append(err)
        iBin+=1

    avgEff = sum(weightedEffList)/sumEntries
    
    avgErrNumList=[ ( (eff-avgEff)*(eff-avgEff)*weight ) + (weight*weight*err*err) \
                    for eff, err, weight in zip(effList, errList, weightList) ]
    avgErr = math.sqrt( sum(avgErrNumList) ) / sumEntries

    print 70*'*'
    print "Naive average efficiency = ({eff:.3f}+/-{err:.3f})%".format(
        eff=naiveAvgEff*100, err=naiveAvgErr*100)
    print "Naive weighted average efficiency = ({eff:.3f}+/-{err:.3f})%".format(
        eff=naiveAvgEffWeighted*100, err=naiveAvgErrWeighted*100)
    print "Weighted average efficiency = ({eff:.3f}+/-{err:.3f})%".format(
        eff=avgEff*100, err=avgErr*100)

