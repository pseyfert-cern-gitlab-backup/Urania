#! /usr/bin/env python

import ROOT
import sys
import subprocess

local_path = '/data/lhcb/users/hunt'
lfn_path   = '/lhcb/user/p/phunt'
prefixes = ('K', 'Pi', 'P')
##mag_pols = ('Up' 'Down')

#dir        = 'CalibData/Reco14_DATA/Mag%s' %mag_pol
#strip_ver  = '20'
#pream      = 'DSt_K_Mag'
#pream      = 'DSt_Pi_Mag'
#pream      = 'Lam0_P_Mag'

#imax=7 #32

def copyFile(fname, maxtries):
    local_fname = "%s/%s" %(local_path, fname)
    lfn_fname = "%s/%s" %(lfn_path, fname)
    TF = ROOT.TFile.Open(local_fname)
    guID = TF.GetUUID()
       
    successful = False
    ntries = 0

    cmd = 'dirac-dms-add-file %s %s CERN-USER %s' % (lfn_fname, local_fname, guID.AsString())
    print cmd

    successful = False
    while not successful:
        p = subprocess.Popen(cmd, shell=True)
        p.wait()
        if(p.returncode==0):
            successful = True
            print 'Success'
        elif ntries < maxtries:
            print 'Trying again...'
            ntries+=1
        else:
            print "Giving up after %d tries" %maxtries
            sys.exit(1)

if __name__=='__main__':
    args=sys.argv[1:]
    if len(args)<2 or len(args)>3:
      print "Usage: %s <recoVersion> <stripVersion> (<ntries=5>)"
      print "<nFiles_magdown> and <nFiles_magup> are the number of subsamples (produced by ChopTrees) for magnet down and magnet up data respectively"
      print "<ntries> is the number of times the script will attempt to upload the file"
      sys.exit(101)
    reco_ver = args[0]
    strip_ver = args[1]
    maxtries = 5
    if len(args)==3:
      maxtries = int(args[4])

    for prefix in prefixes:
        # copy magnet down data
        dir = "CalibData/Reco%s_DATA/MagDown" %reco_ver
        fname = "%s/Ref_%s_MagDown_Strip%s.root" %(dir, prefix, strip_ver)
        copyFile(fname, maxtries)

        # copy magnet up data
        dir = "CalibData/Reco%s_DATA/MagUp" %reco_ver
        fname = "%s/Ref_%s_MagUp_Strip%s.root" %(dir, prefix, strip_ver)
        copyFile(fname, maxtries)

    sys.exit(0)
