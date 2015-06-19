#! /usr/bin/env python

import sys
import ROOT
import subprocess

local_path = '/data/lhcb/users/hunt'
lfn_path   = '/lhcb/user/p/phunt'
mag_pol    = 'Down'
dir        = 'CalibData/Reco14_DATA/Mag%s' %mag_pol
strip_ver  = '20'
partName   = 'P'

maxtries = 5

if __name__=='__main__':

    local_file = "%s/%s/Ref_%s_Mag%s_Strip%s.root" %(local_path, dir, partName, mag_pol, strip_ver)
    lfn_file   = "%s/%s/Ref_%s_Mag%s_Strip%s.root" %(lfn_path, dir, partName, mag_pol, strip_ver)

    TF = ROOT.TFile.Open(local_file)
    guID = TF.GetUUID()

    successful = False
    ntries = 0

    cmd = 'dirac-dms-add-file %s %s CERN-USER %s' % (lfn_file, local_file, guID.AsString())
    print cmd
        
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
    sys.exit(0)

