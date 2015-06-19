# set the stripping version
stripVersion = "20"

# magnet 'Up' or 'Down'?
magPol='Up'

# set the pbs options (e.g. CPU/walltime)
pbsopts = "-l cput=0:20:00,walltime=0:40:00"

# the platform to run on
# if this is not set, it will default to the value of CMTCONFIG
platform=''

# the job name (which will be appended with the
# stripping version, magnet polarity etc)
jobname="ValidateChopTrees"

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
                                                     
# assume the user's ganga directory is the input directory
gangadir='%s/workspace/%s/%s' %(config['Configuration']['gangadir'],
                                config['Configuration']['user'],
                                config['Configuration']['repositorytype'])

# uncomment to use a different input directory
#gangadir='$DATADISK/gangadir_calib/workspace/powell/LocalXML'

# use the PBS backend and set the CPU/walltime etc.
bck = PBS()
bck.extraopts = pbsopts

# Uncomment to use the local backend
#bck = Local()


##  configure the job
# configure the application
app= Executable(
    exe = basedir+'/scripts/sh/ValidateChoppedTrees.sh',
    args = [ stripVersion, magPol, gangadir ]
)

# add the macro to the input sandbox
infiles = [ '{0}/scripts/root/ValidateChoppedTrees.C'.format(basedir) ]

j = Job(
    name = '{jname}_S{strp}_Mag{pol}'.format( jname=jobname,
                                              strp=stripVersion,
                                              pol=magPol ),
    application=app,
    backend=bck,
    inputfiles=infiles
)
j.submit()
