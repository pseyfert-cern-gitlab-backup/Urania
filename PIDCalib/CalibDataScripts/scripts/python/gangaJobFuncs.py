import os
import subprocess
import re

# read a bash script containing various exported variables
# and export these to the current environment
def updateEnvFromShellScript(fname):

    command = ['bash', '-c', 'source %s && env' %fname]

    proc = subprocess.Popen(command, stdout = subprocess.PIPE)

    for line in proc.stdout:
        (key, _, value) = line.partition("=")
        os.environ[key] = value

    proc.communicate()

# get the number of 'chopped' TTrees from the requested ganga
# directory, job ID and file suffix
# NB. This method assumes the job contains subjobs
def getNumChoppedTrees(gangadir, jobID, fileSuffix):
    jobIDdirname = '{topdir}/{jid}'.format(
        topdir=os.path.expandvars(os.path.expanduser(gangadir)),
        jid=jobID)
    subIDDirs = os.listdir(jobIDdirname)
    #print "Got subdirectories : ", subIDDirs
    # regular expression for the chopped files
    validfile = re.compile('^PID_\d+_%s.root$' %fileSuffix)
    nfiles = None
    for sid in subIDDirs:
        subID=None
        # if this directory is not a subjob ID directory, then continue
        try:
            subID=int(sid)
        except ValueError:
            continue
        outfiles = os.listdir('{topdir}/{sid}/output'.format(topdir=jobIDdirname,
				sid=sid))
        #print "Got output files: ", outfiles
        # ignore empty subjobs
        if len(outfiles)==0:
            continue
        choppedfiles = [f for f in outfiles if validfile.match(f)]
        if len(choppedfiles)==0:
            continue
        nfiles = len(choppedfiles)
        break
    if nfiles==None:
        raise ValueError("Failed to find any chopped trees!")
    return nfiles
    
