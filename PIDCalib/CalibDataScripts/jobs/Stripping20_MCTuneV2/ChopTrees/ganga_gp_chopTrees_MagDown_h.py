# set the stripping version
stripVersion = "20_MCTuneV2"

# magnet 'Up' or 'Down'?
magPol='Down'

# file suffix (e.g. 'h' for RICH PID calibration samples)
fileSuffix='h'

# set the pbs options (e.g. CPU/walltime)
pbsopts = "-V -l cput=8:00:00 -l walltime=12:00:00"

# set the pbs queue (should only be set for test jobs)
pbsqueue = ''

# list of input directories (as a stringified list)
treeList='[DSt2D0Pi_D02RSKPiTuple/CalibPID,Lam02PPi_LoPTuple/CalibPID,Lam02PPi_HiPTuple/CalibPID]'

# the platform to run on
# if this is not set, it will default to the value of CMTCONFIG
platform=''

# the job name (which will be appended with the stripping version, magnet polarity etc)
jobname="ChopTrees"

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

# get the User_release_area (i.e. top-level CMT directory, which defaults to $HOME/cmtuser)
User_release_area = os.getenv('User_release_area')
if len(User_release_area)==0: 
    User_release_area="%s/cmtuser" %os.getenv('HOME')

# uncomment to set the User_release_area manually
#User_release_area="/home/huntp/cmtuser"

# base directory of $CALIBDATASCRIPTSROOT 
basedir = '%s/Urania_%s/PIDCalib/CalibDataScripts' %(User_release_area, UraniaVersion)

# read the configuration script
import imp
gangaJobFuncs=imp.load_source('gangaJobFuncs', '%s/scripts/python/gangaJobFuncs.py' %basedir)
gangaJobFuncs.updateEnvFromShellScript('{bdir}/jobs/Stripping{strp}/configureGangaJobs.sh'.format(bdir=basedir,strp=stripVersion))
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
gangadir='%s/workspace/%s/%s' %(config['Configuration']['gangadir'], config['Configuration']['user'],
                                config['Configuration']['repositorytype'])

# uncomment to use a different input directory
#gangadir='$DATADISK/gangadir_calib/workspace/powell/LocalXML'

# use the PBS backend and set the CPU/walltime etc.
bck = PBS()
bck.extraopts = pbsopts
if pbsqueue!='':
    bck.queue = pbsqueue

# Uncomment to use the local backend
#bck = Local()

for jid in jobIDs:
    # configure the application
    app= GaudiPython(
        project='Urania',
        platform=platform,
        version=UraniaVersion,
        script = [basedir+'/scripts/python/chopTrees.py'],
        args = ['--jobID=%d' %jid,
                '--runPickleFile={bdir}/jobs/Stripping{strp}/ChopTrees/{pol}_runLimits_{suf}.pkl'.format(
                    bdir=basedir, strp=stripVersion, pol=magPol.lower(), suf=fileSuffix),
                '--minSubJob=0',
                '--maxSubJob=%d' %(len(jobs(jid).subjobs)-1),
                '--treeList=%s' %treeList,
                '--gangadir=%s' %gangadir,
                '--fileSuffix=%s' %fileSuffix]
    )

    j = Job(
         name = '{jname}_S{strp}_Mag{pol}_{suf}'.format(jname=jobname,strp=stripVersion, pol=magPol, suf=fileSuffix),
         comment = 'Input from Job ID %d' %jid,
        application=app,
        backend=bck
    )
    j.submit()
