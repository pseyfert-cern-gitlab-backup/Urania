import os
import sys

jobIDmin      = int(sys.argv[1]) # int to tag the job ID min
jobIDmax      = int(sys.argv[2]) # int to tag the job ID max

counters = {}
for status in ["running", "completing", "completed", "failed"]:
    counters[status] = 0

for jobID in range(jobIDmin,jobIDmax):    
    j = jobs(jobID)
    if j.status == "failed":
        print "Job with ID %s has status failed. Trying to recover the OutputSandbox now..."%jobID
        flag = j.backend.getOutputSandbox()
        if flag:
            print "  OutputSandbox succesfully retreived! Forcing job status to 'completed'."
            j.force_status("completed")
    else:
        print "Job with ID %s has status %s. Going to next job..."%(jobID,j.status)
    counters[j.status] += 1
    
print ""
print "Looped over a total of %s jobs, from which:"%(sum(counters.values()))
for key in counters.keys():
    print "%s jobs with status %s"%(counters[key],key)
