import os
import sys
Kpibins = [826, 861, 896, 931, 966]

debug = False#True#

GRIDLoc   = str(sys.argv[1]) # str to tag the location on GRID (MC/JpsiKst/Bd2JpsiKst)
fileLoc   = str(sys.argv[2]) # str to tag the local location of file (/zfs_lhcb/Bs2JpsiKst/Toys/Tuples)
fileTag   = str(sys.argv[3]) # str to tag the file name noPeakingBkgsGoodYieldsSimultaneous
fileIDMin = int(sys.argv[4]) # int to tag the JobID ID min
fileIDMax = int(sys.argv[5]) # int to tag the JobID ID max
sWeights  = int(sys.argv[6]) # int to flag if we want to copy sWeighted files
splitFiles= int(sys.argv[7]) # int to flag if split files

tagSweights = ""
if sWeights:
	tagSweights = "_AddedsWeights"

for fileID in range(fileIDMin,fileIDMax):
	if not splitFiles:
		command = "dirac-dms-add-file /lhcb/user/s/sakar/%s/%s%s%s.root %s/%s%s%s.root CERN-USER"%(GRIDLoc,fileTag,fileID,tagSweights, fileLoc,fileTag,fileID,tagSweights)
		if debug:
			print "Going to perform the command:"
			print "  ",command
		else:
			os.system(command)
	else:
		for year in ("2011","2012"):
			for sign in ("n","p"):
				for ibin in range(len(Kpibins)-1):
					command = "dirac-dms-add-file /lhcb/user/s/sakar/%s/%s%s_%s%s_%s_%s_AddedsWeights.root %s/%s%s_%s%s_%s_%s_AddedsWeights.root CERN-USER"%(GRIDLoc,fileTag,fileID,year,sign,Kpibins[ibin],Kpibins[ibin+1], fileLoc,fileTag,fileID,year,sign,Kpibins[ibin],Kpibins[ibin+1])
					if debug:
						print "Going to perform the command:"
						print "  ",command
					else:
						os.system(command)
		
# command = "dirac-dms-add-file /lhcb/user/s/sakar/%s/%s%s_AddedsWeights.root %s/%s%s_AddedsWeights.root CERN-USER"%(GRIDLoc,fileTag[:len(fileTag)-4]+"_Good"+fileTag[len(fileTag)-4:],fileID, fileLoc,fileTag,fileID)
