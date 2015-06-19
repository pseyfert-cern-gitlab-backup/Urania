#! /usr/bin/env python

import ROOT
import sys
import subprocess

local_path = '/data/lhcb/users/powell'
lfn_path   = '/lhcb/user/p/powell'
mag_pol    = 'Up'
dir        = 'CalibData/Reco14_DATA/Mag%s' %mag_pol
strip_ver  = '20'
#pream      = 'DSt_K_Mag'
#pream      = 'DSt_Pi_Mag'
pream      = 'Lam0_P_Mag'

imax=7 #32
maxtries = 5

if __name__=='__main__':
    for i in range(0,imax):
        local_file = "%s/%s/%s%s_Strip%s_%d.root" %(local_path, dir, pream, mag_pol, strip_ver, i)
        lfn_file   = "%s/%s/%s%s_Strip%s_%d.root" %(lfn_path, dir, pream, mag_pol, strip_ver, i)
    
        TF = ROOT.TFile.Open(local_file)
        guID = TF.GetUUID()
        
        successful = False
        ntries = 0

        cmd = 'dirac-dms-add-files %s %s CERN-USER %s' % (lfn_file, local_file, guID.AsString())
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
    sys.exit(0)
