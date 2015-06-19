#! /usr/bin/env python

#import ROOT
import subprocess

#local_path = '/afs/cern.ch/work/j/jotalora/PID_Calib/CalibData_2011/MagDown/Mu/'
#local_path = '/afs/cern.ch/work/j/jotalora/PID_Calib/CalibData_2011/MagDown/P/'
#local_path = '/afs/cern.ch/work/j/jotalora/PID_Calib/CalibData_2011/MagDown/Pi/'
local_path = '/afs/cern.ch/work/j/jotalora/PID_Calib/CalibData_2011/MagDown/K/'
pfn_path   = '/castor/cern.ch/grid/lhcb/user/j/jotalora/'
#dir        = 'CalibData/Reco14_DATA/MagUp/'
#dir        = 'CalibData/Reco14_DATA/MagDown/'
#dir        = 'CalibData/Reco12_DATA/MagUp/'
dir        = 'CalibData/Reco12_DATA/MagDown/'
#mag_pol    = 'Up'
mag_pol    = 'Down'
#strip_ver  = '20'
strip_ver   = '17'
#pream      = 'DSt_K_Mag'+mag_pol+'_Strip'+strip_ver+'_'
#pream      = 'DSt_Pi_Mag'+mag_pol+'_Strip'+strip_ver+'_'
#pream      = 'Lam0_P_Mag'+mag_pol+'_Strip'+strip_ver+'_'
#pream      = 'DSt_MuonUnBiased_K_Mag'+mag_pol+'_Strip'+strip_ver+'_'
#pream      = 'Lam0_MuonUnBiased_P_Mag'+mag_pol+'_Strip'+strip_ver+'_'
#pream      = 'Jpsi_Mu_Mag'+mag_pol+'_Strip'+strip_ver+'_'
#pream      = 'DSt_MuonUnBiased_Pi_Mag'+mag_pol+'_Strip'+strip_ver+'_'
pream      = 'DSt_MuonUnBiased_K_Mag'+mag_pol+'_Strip'+strip_ver+'_'
#pream      = 'Lam0_MuonUnBiased_P_Mag'+mag_pol+'_Strip'+strip_ver+'_'

for i in range(0,1+1):#um a mais do tamanho
    #local_file = local_path+dir+pream+str(i)+'.root'
    local_file = local_path+pream+str(i)+'.root'
    #lfn_file   = lfn_path+dir+pream+str(i)+'.root'
    pfn_file   = pfn_path+dir+pream+str(i)+'.root'
    
    cmd = 'rfcp %s %s' % (local_file, pfn_file)
    print cmd

    successful = False
    while(successful!=True):
        p = subprocess.Popen(cmd, shell=True)
        p.wait()
        if(p.returncode==0):
            successful = True
            print 'Success'
        else:
            print 'Trying again...'
