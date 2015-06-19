import numpy as np
import pickle
import sys
import getopt
from ROOT import TFile, TTree, TCut, gDirectory, TObject

def usage():
    print ' ------------------------------------------------------------------------------------------------------'
    print ' Andrew Powell (a.powell1@physics.ox.ac.uk) November 22, 2012                                          '
    print '                                                                                                       '
    print ' chopTrees.py - Run over a given ganga job output produced using PIDCalib/CalibDataSel and split it    '
    print '                into subsamples defined by the run limits within a pickle file produced using          '
    print '                $CALIBDATASCRIPTSROOT/scripts/getRunLumi.py                                            '
    print ' Typical usage:                                                                                        '
    print " python chopTrees.py --jobID=107                                                                       "
    print "                     --runPickleFile=up_runLimits_h.pkl                                                  "
    print "                     --minSubJob=0                                                                     "
    print "                     --maxSubJob=26                                                                    "
    print "                     --treeList='[DSt2D0Pi_D02RSKPiTuple/CalibPID,Lam02PPi_LoPTuple/CalibPID,          "
    print "                                       Lam02PPi_HiPTuple/CalibPID,JpsiFromBNoPIDNoMipTuple/CalibPID]'  " 
    print "                     --gangadir=/afs/cern.ch/user/a/apowell/gangadir/workspace/apowell/LocalXML        "
    print "                     --fileSuffix=h                                                                    "
    print ' ------------------------------------------------------------------------------------------------------'
    sys.exit(' ')

def chopTrees(in_file, tree_list, run_pickle_file, fileSuffix, out_path=''):
    #==================================================
    # Un-pickle the numpy arrays
    #==================================================
    runLims   = pickle.load( open( run_pickle_file, "rb" ) )
    print runLims
    
    #==================================================
    # Open TFile
    #==================================================
    f_in   = TFile(in_file,'read')

    #==================================================
    # Create list of TTrees to access
    #==================================================
    _trees = []
    for tree in tree_list:
        if gDirectory.Get(tree)!=None:
            _trees.append(gDirectory.Get(tree))
        else:
            print 'TTree \'{ttree}\' can not be found' .format(ttree=tree)
            sys.exit()
    
    #==================================================
    # Loop over array of run sets
    #==================================================
    for i, run_set in enumerate(runLims):
        
        #==================================================
        # Create TFile for candidates in run range
        #==================================================
        if out_path!='':
            out_path +='/'
        f_out = TFile( '%sPID_%d_%s.root' %(out_path,i,fileSuffix), 'recreate' )

        #==================================================
        # Create TCut for this run range
        #==================================================
        cut = str(run_set[0]) +' <= runNumber'
        cut += ' && '
        cut += 'runNumber <= ' + str(run_set[1])
        print cut 

        #==================================================
        # Make directories
        #==================================================
        for tree in tree_list:
            f_out.mkdir(tree.split('/')[0])

        #==================================================
        # Copy Tree
        #==================================================
        for i, tree in enumerate(tree_list):
            f_out.cd(tree.split('/')[0])
            tree_cpy = _trees[i].CopyTree(cut)
            tree_cpy.Write(tree_cpy.GetName(), TObject.kWriteDelete)
        
        #==================================================
        # Close TFile
        #==================================================
        f_out.Close()

def chopTreesLoop(in_file_list, tree_list, run_pickle_file, fileSuffix='h'):

    #==================================================
    # Loop over list of input files
    #==================================================
    for i, file in enumerate(in_file_list):

        #==================================================
        # Determine path of file
        #==================================================
        file_name = file.split('/')[len(file.split('/'))-1]
        replace_str = '/'+file_name if len(file.split('/'))>1 else file_name
        path = file.replace(replace_str,'')
        #==================================================
        # If no file continue
        #==================================================
        f_in   = TFile(file,'read')
        if f_in.IsZombie() :
          print 'File ' + file + ' Not Found'
          continue
        f_in.Close()
        #==================================================
        # Run chopTrees function
        #==================================================
        chopTrees(file, tree_list, run_pickle_file, fileSuffix, path)
        print 'Processed {ii} of {nn} files requested to be chopped.'.format(ii=i+1,nn=len(in_file_list))
        
def chopTreesGanga(tree_list,
                   run_pickle_file,
                   job_id,
                   min_subjob,
                   max_subjob,
                   ganga_dir='$DATADISK/gangadir_calib/workspace/powell/LocalXML',
                   fileSuffix='h',
                   nTuple_name='PID_Modes.root'):

    file_list = []
    for subjob in xrange(min_subjob, max_subjob+1):
        file_list.append(ganga_dir+'/'+str(job_id)+'/'+str(subjob)+'/output/'+nTuple_name)
    print file_list
    
    chopTreesLoop(file_list,
                  tree_list,
                  run_pickle_file,
                  fileSuffix)
    

if __name__ == '__main__':
    
    #======================================================================
    # Run the makeCurves function if run by the python interpretator
    #======================================================================
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'r:j:x:y:t:g:f', 
                                      ['runPickleFile=', 'jobID=', 'minSubJob=','maxSubJob=','treeList=','gangadir=', 'fileSuffix='])
    except getopt.GetoptError as err:
        print "**** ERROR: %s ****" %str(err)
        usage()
    if len(opts) != 7:
        print "**** ERROR: expected seven arguments, got %d ****" %len(opts)
        usage()
    for o,p in opts:
        if o in   ['-x', '--minSubJob']:
            subjob_min = int(p)
        elif o in ['-y', '--maxSubJob']:
            subjob_max = int(p)
        elif o in ['-j', '--jobID']:
            job_id = int(p)
        elif o in ['-r', '--runPickleFile']:
            run_file = p
        elif o in ['-t', '--treeList']:
            tree_list = p[1:-1].split(',')
        elif o in ['-g', '--gangadir']:
            gangadir = p
        elif o in ['-f', '--fileSuffix']:
            fileSuffix = p
    print '    job_id   :', job_id,     type(job_id)
    print '  run_file   :', run_file,   type(run_file)
    print 'subjob_min   :', subjob_min, type(subjob_min)
    print 'subjob_max   :', subjob_max, type(subjob_max)
    print ' tree_list   :', tree_list,  type(tree_list)
    print '  gangadir   :', gangadir,   type(gangadir)
    print 'file suffix  :', fileSuffix, type(fileSuffix)  
    chopTreesGanga(tree_list, run_file, job_id, subjob_min, subjob_max, gangadir, fileSuffix)
    
    print 'Done'
