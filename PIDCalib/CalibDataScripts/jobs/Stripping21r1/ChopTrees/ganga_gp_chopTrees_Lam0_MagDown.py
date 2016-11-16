# set the stripping version
stripVersion = "21r1"

# magnet 'Up' or 'Down'?
magPol='Down'

# file suffix:
#
# dst_k_and_pi: Kaons and pions from D*
# lam0_p: Protons from Lambda0
# jpsi_mu: Muons from J/psi
# dst_k_and_pi_muonUnBiased: 'MuonUnBiased' kaons + pions from D*
# lam0_p_muonUnBiased: 'MuonUnBiased' protons from Lambda0
fileSuffix='lam0_p'

# set the pbs options (e.g. CPU/walltime)
pbsopts = "-l cput=11:00:00,walltime=2:00:00"

# list of input directories (as a comma-separated list)
treeList='Lam02PPi_LoPTuple,Lam02PPi_hiPTuple'

# the platform to run on
# if this is not set, it will default to the value of CMTCONFIG
platform=''

# the job name (which will be appended with the
# stripping version, magnet polarity etc)
jobname="ChopTrees"

# the maximum number of input files to process per subjob
filesPerJob=20

# is this a test job?
isTest=False

############################################################################
# The following lines should not need to be changed in most cases, as they
# are autoconfigured from the above options
############################################################################

import os
import re
import sys

# set the platform (if not already specified)
if len(platform)==0:
    platform=os.getenv('CMTCONFIG')

# get the Urania version from the script path
abspath = os.path.abspath(os.path.dirname(sys.argv[0]))
rematch = re.search('.Urania_(?P<ver>v\d+r\d+p?\d?).', abspath)
UraniaVersion=rematch.group('ver')

# uncomment to set the Urania version manually
#UraniaVersion="v1r1"

# get the User_release_area (i.e. top-level CMT directory,
# which defaults to $HOME/cmtuser)
User_release_area = os.getenv('User_release_area')
if len(User_release_area)==0: 
    User_release_area="%s/cmtuser" %os.getenv('HOME')

# uncomment to set the User_release_area manually
#User_release_area="/home/huntp/cmtuser"

# base directory of $CALIBDATASCRIPTSROOT 
basedir = '%s/Urania_%s/PIDCalib/CalibDataScripts' %(User_release_area,
                                                     UraniaVersion)

# read the configuration script
import imp
gangaJobFuncs=imp.load_source('gangaJobFuncs',
                              '%s/scripts/python/gangaJobFuncs.py' %basedir)
gangaJobFuncs.updateEnvFromShellScript( ('{bdir}/jobs/Stripping{strp}'
                                         '/configureGangaJobs.sh').format(
    bdir=basedir,strp=stripVersion) )
jidVar = ''
if magPol=='Down':
    jidVar='CALIBDATA_JIDS_DOWN'
elif magPol=='Up':
    jidVar='CALIBDATA_JIDS_UP'
else:
    raise NameError('Unknown magnet polarity %s' %magPol)
jids_str=os.getenv(jidVar)
if len(jids_str)==0:
    raise NameError('Environmental variable %s is not set' %jidVar)
jobIDs=[int(jid) for jid in jids_str.split()]

# uncomment to set the input job IDs manually
#jobIDs=[7,9]

# assume the user's ganga directory is the input directory
gangadir='%s/workspace/%s/%s' %(config['Configuration']['gangadir'],
                                config['Configuration']['user'],
                                config['Configuration']['repositorytype'])

# uncomment to use a different input directory
#gangadir='$DATADISK/gangadir_calib/workspace/powell/LocalXML'

# use the PBS backend and set the CPU/walltime etc.
bck = PBS()
bck.extraopts = pbsopts
if isTest:
    bck.queue = 'testing'

# Uncomment to use the local backend
#bck = Local()


##  configure the jobs
if isTest:
    jobname='Test'+jobname
        
for jid in jobIDs:
    # get the input jobID (if it exists)

    # configure the job comment
    jobcomment='Input from Job ID %d' %jid
    if isTest:
        jobcomment='TEST - '+jobcomment

    # the maximum number of subjobs to process
    maxSubJobs = 5 if isTest else None

    # the name of the pickle file
    pklFile=('{bdir}/jobs/Stripping{strp}/ChopTrees/'
             '{pol}_runLimits_{suf}.pkl').format( bdir=basedir,
                                                  strp=stripVersion,
                                                  pol=magPol.lower(),
                                                  suf=fileSuffix )

    # Make the lists of arguments used by the ArgSplitter
    #
    # Arguments are:
    #
    # 1) Urania version
    # 2) platform (e.g. 'x86_64-slc6-gcc46-opt')
    # 3) input jobID
    # 4) pickle file
    # 5) minimum subjob ID
    # 6) maximum subjob ID
    # 7) list of input TTrees
    # 8) top-level input directory (usually the ganga repository)
    # 9) file suffix (e.g. 'dst_k_and_pi')

    splitIDs = gangaJobFuncs.getSplitSubJobIDs(jid, filesPerJob, maxSubJobs)
    argLists = [ [ UraniaVersion,
                   platform,
                   jid,
                   pklFile,
                   minID,
                   maxID,
                   treeList,
                   gangadir,
                   fileSuffix] for minID, maxID in splitIDs ]

    splitter = ArgSplitter(args=argLists)
    
    # configure the application
    app= Executable(
        exe = basedir+'/scripts/sh/ChopTrees.sh',
        )

    j = Job(
        name = '{jname}_S{strp}_Mag{pol}_{suf}'.format( jname=jobname,
                                                        strp=stripVersion,
                                                        pol=magPol,
                                                        suf=fileSuffix ),
        comment = jobcomment,
        application=app,
        backend=bck,
        splitter=splitter
        )
    j.submit()
