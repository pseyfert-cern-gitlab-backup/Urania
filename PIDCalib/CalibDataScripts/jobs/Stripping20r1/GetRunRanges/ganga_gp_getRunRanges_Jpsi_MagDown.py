# Set the stripping version
stripVersion = '20r1'

# Set the magnet polarity ('Up' or 'Down')
magPol='Down'

# Set the file suffix:
#
# dst_k_and_pi: Kaons and pions from D*
# lam0_p: Protons from Lambda0
# jpsi_mu: Muons from J/psi
# dst_k_and_pi_muonUnBiased: 'MuonUnBiased' kaons + pions from D*
# lam0_p_muonUnBiased: 'MuonUnBiased' protons from Lambda0
fileSuffix='jpsi_mu'

# Set the pbs options (e.g. CPU/walltime)
pbsopts = "-l cput=0:05:00,walltime=0:15:00"

# Set the name of the directory in the input file(s) containing
# the 'CalibPID' nTuple
tupleDir = "JpsiFromBNoPIDNoMipTuple"

# Set the selection cuts, e.g. 'MuonUnBiased' cuts
#
# N.B. The run-range splitting is determined after application of
# the selection cuts
partCuts='{0}_MuonTisTagged==1&&{0}_Probe==1&&{1}_Tag==1'
cuts='({0}) || ({1})'.format( partCuts.format('Mu0', 'Mu1'),
                              partCuts.format('Mu1', 'Mu0') )

# Set the maximum number of entries per subsample (maxEntries)
#
# N.B. The GetRunRanges script adjusts maxEntries to minimise the
# difference between maxEntries and the remainder after dividing
# the total number of entries by maxEntries. By default, the
# remainder must be within 90% of maxEntries. This amount can be
# adjusted by changing the value of 'minFrac' below.
#
# The amount by which maxEntries is decremented in each step is
# by default 1% of the initial maxEntries. This amount can be
# adjusted by changing the value of 'stepFrac' below.
maxEntries=int(1e6) # N.B. python treats numbers with exponents as floats
minFrac=0.8
stepFrac=0.01

# the platform to run on
# if this is not set, it will default to the value of CMTCONFIG
platform=''

# the job name (which will be appended with the
# stripping version, magnet polarity etc)
jobname="GetRunRanges"

# is this a test job?
isTest=False

##########################################################################################################
# The following lines should not need to be changed in most cases, as they are autoconfigured from the
# above options
##########################################################################################################

import os
import errno
import re
import sys

# get the Urania version from the script path
abspath = os.path.abspath(os.path.dirname(sys.argv[0]))
rematch = re.search('.Urania_(?P<ver>v\d+r\d+p?\d?).', abspath)
UraniaVersion=rematch.group('ver')

# uncomment to set the Urania version manually
#UraniaVersion="v1r1"

# get the User_release_area (i.e. top-level CMT directory, which defaults to $HOME/cmtuser)
User_release_area = os.getenv('User_release_area')
if len(User_release_area)==0: 
    User_release_area="{0}/cmtuser".format(os.getenv('HOME'))

# uncomment to set the User_release_area manually
#User_release_area="/home/huntp/cmtuser"

# get the package directory
basedir='{dir}/Urania_{ver}/PIDCalib/CalibDataScripts'.format(
    dir=User_release_area, ver=UraniaVersion)

# uncomment to set the input job IDs manually
#jobIDs=[7,9]

# assume the user's ganga directory is the input directory
gangadir='%s/workspace/%s/%s' %(config['Configuration']['gangadir'],
                                config['Configuration']['user'],
                                config['Configuration']['repositorytype'])

# uncomment to use a different input directory
#gangadir='$DATADISK/gangadir_calib/workspace/powell/LocalXML'

# make the 'ChopTrees' directory (if it doesn't already exist)
outputdir='{dir}/jobs/Stripping{strp}/ChopTrees'.format(
    dir=basedir, strp=stripVersion)
try:
    os.mkdir(outputdir)
except OSError as exc:
    if exc.errno == errno.EEXIST and os.path.isdir(outputdir):
        pass
    else: raise
    
# use the PBS backend and set the CPU/walltime etc.
bck = PBS()
bck.extraopts = pbsopts
if isTest:
    bck.queue = 'testing'

# Uncomment to use the local backend
#bck = Local()

# we need to add the ROOT macro to the input sandbox
infiles=['{dir}/scripts/root/GetRunRanges.C'.format(dir=basedir)]

# Uncomment to use the local backend
#bck = Local()

# configure the application
app=Executable(
    exe=basedir+'/scripts/sh/GetRunRanges.sh',
    # arguments are:
    # 1) ganga directory
    # 2) Urania version
    # 3) platform
    # 4) magnet polarity
    # 5) stripping version
    # 6) file suffix
    # 7) nTuple directory
    # 8) selection cuts (if applicable)
    # 9) starting value of 'maxEntries'
    #    (the maximum number of entries per subsample)
    # 10) step fraction for maxEntries
    # 11) minimum fraction of maxEntries allowed after
    #     dividing the number of entries by maxEntries
    args = [ gangadir,
             UraniaVersion,
             platform,
             magPol,
             stripVersion,            
             fileSuffix,
             tupleDir,
             cuts,
             '{0:d}'.format(maxEntries),
             '{0:f}'.format(stepFrac),
             '{0:f}'.format(minFrac) ]
    )

# configure the job
if isTest:
    jobname='Test'+jobname
        
j = Job( name='{jname}_S{strp}_Mag{pol}_{suf}'.format( jname=jobname,
                                                        strp=stripVersion,
                                                        pol=magPol,
                                                        suf=fileSuffix ),
         application=app,
         backend=bck,
         inputfiles=infiles
         )
j.submit()

