# Set the config version (e.g. "Collision12")
configVersion='Collision12'

# Set the reconstruction version
recoVersion = '14'

# Set the stripping version
stripVersion = '20'

# Set the file suffix:
#
# dst_k_and_pi: Kaons and pions from D*
# lam0_p: Protons from Lambda0
# jpsi_mu: Muons from J/psi
# dst_k_and_pi_muonUnBiased: 'MuonUnBiased' kaons + pions from D*
# lam0_p_muonUnBiased: 'MuonUnBiased' protons from Lambda0
fileSuffix='jpsi_mu'

# Set the magnet down and magnet up luminosity-block sizes (in pb-1)
lumiBlock_magdown=23
lumiBlock_magup=23

# set the pbs options (e.g. CPU/walltime)
pbsopts = "-l cput=1:0:00 -l walltime=2:0:00"

# set the pbs queue (should only be set for test jobs)
pbsqueue = ''

# the job name (which will be appended with the config, reconstruction and
# stripping versions and the file suffix)
jobname="GetRunLumi"

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

# make the 'ChopTrees' directory (if it doesn't already exist)
outputdir='{0}/../ChopTrees'.format(os.getenv('PWD'))
try:
    os.mkdir(outputdir)
except OSError as exc:
    if exc.errno == errno.EEXIST and os.path.isdir(outputdir):
        pass
    else: raise
    
# use the PBS backend and set the CPU/walltime etc.
bck = PBS()
bck.extraopts = pbsopts
if pbsqueue!='':
    bck.queue = pbsqueue

# Uncomment to use the local backend
#bck = Local()

# configure the application
app=Executable(
    exe=basedir+'/scripts/sh/GetRunLumi.sh',
    # arguments are:
    # 1) script path
    # 2) config version
    # 3) recoVersion
    # 4) stripVersion
    # 5) luminoisty-block size for magnet down data (pb-1)
    # 6) luminoisty-block size for magnet up data (pb-1)
    # 7) suffix used for the pickle files
    # 8) directory where the pickle files should be stored
    args = [ '{0}/scripts/python/getRunLumi.py'.format(basedir),
             configVersion,
             recoVersion,
             stripVersion,
             '{0:f}'.format(lumiBlock_magdown),
             '{0:f}'.format(lumiBlock_magup),
             fileSuffix,
             outputdir ],
             env={'X509_USER_PROXY':os.getenv('X509_USER_PROXY')}
    )

j=Job(name='{jname}_{cnf}_R{reco}S{strp}_{suf}'.format(
    jname=jobname, cnf=configVersion, reco=recoVersion,
    strp=stripVersion, suf=fileSuffix),
      application=app,
      backend=bck
      )
j.submit()
    
             
