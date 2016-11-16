# set the stripping version
stripVersion = "21"

print stripVersion

# magnet 'Up' or 'Down'?
magPol='Up'

# file suffix:
#
# dst_k_and_pi: Kaons and pions from D*
# lam0_p: Protons from Lambda0
# jpsi_mu: Muons from J/psi
# dst_k_and_pi_muonUnBiased: 'MuonUnBiased' kaons + pions from D*
# lam0_p_muonUnBiased: 'MuonUnBiased' protons from Lambda0
fileSuffix='jpsi_e'

# set the pbs options (e.g. CPU/walltime)
pbsopts = "-l cput=5:59:00,walltime=12:00:00"

# particle type (e.g. DSt, Lam0, Jpsi)
partType="Jpsiee"

# the platform to run on
# if this is not set, it will default to the value of CMTCONFIG
platform=''

# the job name (which will be appended with the stripping version, magnet polarity etc)
jobname="JpsiFit_e"

# is this a test job?
isTest=False

##########################################################################################################
# The following lines should not need to be changed in most cases, as they are autoconfigured from the
# above options
##########################################################################################################

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

# location of the executable
exeFile = '%s/scripts/sh/%sJob_runRange.sh' %(basedir, partType)

# read the configuration script
import imp
gangaJobFuncs=imp.load_source('gangaJobFuncs',
                              '%s/scripts/python/gangaJobFuncs.py' %basedir)
gangaJobFuncs.updateEnvFromShellScript( ('{bdir}/jobs/Stripping{strp}'
                                         '/configureGangaJobs.sh').format(
    bdir=basedir,strp=stripVersion))
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

subIDString="*"

##  configure the jobs
if isTest:
    jobname='Test'+jobname

for jid in jobIDs:
    # configure the job comment
    jobcomment='Input from Job ID %d' %jid
    if isTest:
        jobcomment='TEST - '+jobcomment

    # get the number of chopped tree
    nChoppedTrees = gangaJobFuncs.getNumChoppedTrees(gangadir, jid,
                                                     fileSuffix)
    if isTest:
        # run over ~10% of all events,
        # and only process one "chopped tree" (index 0)
        nChoppedTrees = 1
        nSubJobs = len(jobs(jid).subjobs)
        subIDString = "{"+",".join([str(s) for s in range(nSubJobs/10)])+"}"

    # Make the lists of arguments used by the ArgSplitter
    #
    # Arguments are:
    #
    # 1) top-level input directory (usually the ganga repository)
    # 2) Urania version
    # 3) platform (e.g. 'x86_64-slc6-gcc46-opt')
    # 4) magnet polarity
    # 5) stripping version
    # 6) index
    # 7) file suffix (e.g. 'dst_k_and_pi')
    # 8) verbose flag (0 = no verbose info, 1 = verbose info)
    # 9) exit on bad fit flag ( 0 = don't exit, 1 = do exit (
    # 10) subjobID string ('*' for all subjobs, '{0,1,2}' for first 3
    #    subjobs etc.)

    argLists = [ [ gangadir,
                   UraniaVersion,
                   platform,
                   "e",
                   magPol,
                   stripVersion,
                   str(idx),
                   fileSuffix,
                   str(int(isTest)),
                   '1',
                   subIDString ] for idx in range(nChoppedTrees) ]

    splitter = ArgSplitter(args=argLists)
    
    # configure the application
    app= Executable(
        exe = File(exeFile),
        )

    j = Job(
        name = '{jname}_S{strp}_Mag{pol}_{suf}'.format(jname=jobname,
            strp=stripVersion, pol=magPol, suf=fileSuffix),
        comment = jobcomment,
        outputfiles = ['*.pdf'] ,
        application=app,
        backend=bck,
        splitter=splitter
    )
    j.submit()
