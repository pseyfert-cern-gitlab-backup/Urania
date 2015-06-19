#! /usr/bin/env python

import ROOT
import sys
import subprocess
import glob

local_path = '/data/lhcb/users/hunt'
lfn_path   = '/lhcb/user/p/phunt'
prefixes = ('DSt_K', 'DSt_Pi', 'Lam0_P')
## script will only work if in the above line the prefix with the most files goes first.

##mag_pols = ('Up' 'Down')

#dir        = 'CalibData/Reco14_DATA/Mag%s' %mag_pol
#strip_ver  = '20'
#pream      = 'DSt_K_Mag'
#pream      = 'DSt_Pi_Mag'
#pream      = 'Lam0_P_Mag'

#imax=7 #32
exitOnFailure=False

def copyFile(fname, maxtries):
    local_fname = "%s/%s" %(local_path, fname)
    lfn_fname = "%s/%s" %(lfn_path, fname)
    TF = ROOT.TFile.Open(local_fname)
    if not TF:
      print "ERROR: Failed to open file %s for reading" %local_fname
      if exitOnFailure:
        sys.exit(1)
      else:
        return
    guID = TF.GetUUID()
       
    successful = False
    ntries = 0

    cmd = 'dirac-dms-add-file %s %s CERN-USER %s' % (lfn_fname, local_fname, guID.AsString())
    print cmd

    while True:
        p = subprocess.Popen(cmd, shell=True)
        p.wait()
        if(p.returncode==0):
            successful = True
            print 'Success'
            return
        elif ntries < maxtries:
            print 'Trying again...'
            ntries+=1
        else:
            print "Giving up after %d tries" %maxtries
            if exitOnFailure:
              sys.exit(1)
            else:
	      return
if __name__=='__main__':
    args=sys.argv[1:]
    if len(args)<2 or len(args)>5:
      print "Usage: %s <recoVersion> <stripVersion> (<nFiles_magdown=-1> <nFiles_magup=-1> (<ntries=5>)" %os.path.basename(sys.argv[0])
      print "<nFiles_magdown> and <nFiles_magup> are the number of subsamples (produced by ChopTrees) for magnet down and magnet up data respectively"
      print "If 'nFiles' is less than zero (default) then all subsamples will be be processed"
      print "<ntries> is the number of times the script will attempt to upload the file"
      sys.exit(101)
    reco_ver = args[0]
    strip_ver = args[1]
    nFiles_down = -1
    if len(args)>=3:
      nFiles_down = int(args[2])
    nFiles_up = -1 
    if len(args)>=4:
      nFiles_up = int(args[3])
    maxtries = 5
    if len(args)==5:
      maxtries = int(args[4])

    print 'Reco version: %s' %reco_ver
    print 'Strip version: %s' %strip_ver
    print '# files (mag down): %d' %nFiles_down
    print '# files (mag up): %d' %nFiles_up
    print 'Max tries: %d' %maxtries

    # copy magnet down data
    if (nFiles_down<0):
	dir = "%s/CalibData/Reco%s_DATA/MagDown" %(local_path,reco_ver)
        fname = "%s/%s_MagDown_Strip%s_*.root" %(dir, prefixes[0], strip_ver)
        nFiles_down= len(glob.glob(fname))
    for i in range(0, nFiles_down):
        for prefix in prefixes:
            dir = "CalibData/Reco%s_DATA/MagDown" %reco_ver
            fname = "%s/%s_MagDown_Strip%s_%d.root" %(dir, prefix, strip_ver, i)
            copyFile(fname, maxtries)

    # copy magnet up data
    if (nFiles_up<0):
	dir = "%s/CalibData/Reco%s_DATA/MagUp" %(local_path,reco_ver)
        fname = "%s/%s_MagUp_Strip%s_*.root" %(dir, prefixes[0], strip_ver)
        nFiles_up = len(glob.glob(fname))
    for i in range(0, nFiles_up):
        for prefix in prefixes:
            dir = "CalibData/Reco%s_DATA/MagUp" %reco_ver
            fname = "%s/%s_MagUp_Strip%s_%d.root" %(dir, prefix, strip_ver, i)
            copyFile(fname, maxtries)

    sys.exit(0)
