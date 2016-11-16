import os
import subprocess
import re

def updateEnvFromShellScript(fname):
    """Read a bash script (fname) containing various exported variables, """
    """and export these to the current environment."""
    command = ['bash', '-c', 'source %s && env' %fname]

    proc = subprocess.Popen(command, stdout = subprocess.PIPE)

    for line in proc.stdout:
        (key, _, value) = line.partition("=")
        os.environ[key] = value

    proc.communicate()

def getNumChoppedTrees(gangadir, jobID, fileSuffix):
    """Get the number of 'chopped' TTrees from the requested ganga """
    """directory, job ID and file suffix.
    NB. This method assumes the job contains subjobs."""
    jobIDdirname = '{topdir}/{jid}'.format(
        topdir=os.path.expandvars(os.path.expanduser(gangadir)),
        jid=jobID)
    print jobIDdirname
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
        outfiles = os.listdir('{topdir}/{sid}/output'.format(
            topdir=jobIDdirname,
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
    print 'reached end of getNumChopTrees'
    return nfiles
    
def getSplitSubJobIDs(jobID, nSubIDsPerJob, maxSubID=None):
    """For a given ganga job, returns a list of the first and last """
    """subjob IDs, given the requested number of subjobs per list entry.
    This method is used by the 'ChopTrees' job scripts to split up """
    """the 'chopping' of the PID calibration TTrees.
    If maxSubID is set, then it should correspond to the maximum number """
    """of subjobs to process."""
    from Ganga.GPI import jobs
    j=jobs(jobID)
    nSubJobs = len(j.subjobs)
    if maxSubID is not None:
        s = int(maxSubID)
        if s<0:
            raise ValueError('Invalid maximum subjob ID {0:d}'.format(
                s))
        if s>nSubJobs:
            raise ValueError(('Maximum subjob ID to process ({0:d})'
                              ' is larger than the largest subjob ID '
                              '({1:d})').format(s, maxID))
        nSubJobs=maxSubID

    splitSize = int(nSubIDsPerJob)
    firstIDs = range(0, nSubJobs, splitSize)
    splitIDs = []
    for firstID in firstIDs:
        lastID = firstID+(splitSize-1)
        if lastID>(nSubJobs-1):
            lastID=nSubJobs-1
        splitIDs.append( (firstID, lastID) )

    return splitIDs
