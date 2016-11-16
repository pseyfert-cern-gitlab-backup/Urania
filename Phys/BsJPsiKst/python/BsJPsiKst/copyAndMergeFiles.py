from ROOT import *
from math import *
import os
import sys

Kpibins = [826, 861, 896, 931, 966]

debug = False#True#

nameID = "sakar"

fileTag        = str(sys.argv[1]) # str to tag the file name (e.g. noPeakingBkgsGoodYieldsSimultaneous)
fileIDMin      = int(sys.argv[2]) # int to tag the JobID ID min
fileIDMax      = int(sys.argv[3]) # int to tag the JobID ID max
genOriginal    = int(sys.argv[4]) # int to tag if the files are generated for the first time
copy           = int(sys.argv[5]) # int to merge or not files
merge          = int(sys.argv[6]) # int to merge or not files
angRes         = int(sys.argv[7]) # int to tag angular fit results

zfsLoc = "/zfs_lhcb/Bs2JpsiKst/Toys"

plotsLoc = "%s/fitResults/%s/massPlots"%(zfsLoc, fileTag)

splitDataLoc = "%s/splitTuples/%s"%(zfsLoc, fileTag)

fitResultsLoc = "%s/fitResults/%s/fitResults"%(zfsLoc, fileTag)

anglesFitResultsLoc_root = "%s/fitResults/%s"%(zfsLoc, fileTag)
anglesFitResultsLoc = "%s/fitResults/%s/AngFitResults"%(zfsLoc, fileTag)

genDataLoc = "%s/Tuples/%s"%(zfsLoc, fileTag)

if not angRes:
	if genOriginal:
		os.system("mkdir %s"%genDataLoc)
	else:
		os.system("mkdir %s"%splitDataLoc)
		os.system("mkdir %s"%fitResultsLoc)
		os.system("mkdir %s"%plotsLoc)
else:
	os.system("mkdir %s"%anglesFitResultsLoc_root)
	os.system("mkdir %s"%anglesFitResultsLoc)

l_years = ["2011","2012"]
l_signs = ["n","p"]
l_bins = []
for ibin in range(len(Kpibins)-1):
	l_bins.append(ibin)

chains = {}
nExps = {}
for ibin in l_bins:
	chains[ibin] = TChain("rfr")
	nExps[ibin] = 0

if copy and not angRes:
	for iJob in range(fileIDMin,fileIDMax):
		print "Job ID:",iJob
		gangaLoc = "/zfs_lhcb/users/%s/gangadir/workspace/%s/LocalXML/%s/output"%(nameID,nameID,iJob)

		if genOriginal:
			# -- Move gen datasets in sub-directory corresponding to the generated configuration (fileTag)
			os.system("mv %s/genData*.root %s/."%(gangaLoc, genDataLoc))
		else:
			# -- Move massPlots and fitResults in sub-directories corresponding to the fitting configuration (fileTag)
			os.system("mv %s/massPlot*.root %s/."%(gangaLoc, plotsLoc))
			os.system("mv %s/massFitResults*.root %s/."%(gangaLoc, fitResultsLoc))
			# -- Move gen datasets and sWeights added results in sub-directory corresponding to the fitting configuration (fileTag)
			os.system("mv %s/*AddedsWeights*.root %s/."%(gangaLoc, splitDataLoc))

			if merge:
				for ibin in l_bins:
					# - Chain the fit results for each fitting category separately
					fileName = ("%s/massFitResults_Toys_%s_Exp*_AllYearsSigns_%s_%s.root"%(fitResultsLoc, fileTag, Kpibins[ibin], Kpibins[ibin+1]))
					flag = chains[ibin].Add("%s"%fileName)

	if not genOriginal and merge:
		chain = TChain("rfr") 
		for ibin in l_bins:
			# - Chain the fit results for all fitting category
			chain.Add(chains[ibin])
			# - Save fit results in root files for each fitting category separately
			fileRes = TFile("%s/massFitResults_Toys_%s_AllExps_AllYearsSigns_%s_%s.root"%(fitResultsLoc, fileTag, Kpibins[ibin], Kpibins[ibin+1]), "recreate");
			print "Copying fit results trees for %s_%s..."%(Kpibins[ibin], Kpibins[ibin+1])
			treeRes = chains[ibin].CopyTree("")
			treeRes.Write()
			fileRes.Close()

		# - Save fit results in a root file for all fitting category
		file = TFile("%s/massFitResults_Toys_%s_AllExps_AllCats.root"%(fitResultsLoc, fileTag), "recreate");
		print "Copying fit results trees for all categories..."
		tree = chain.CopyTree("")
		tree.Write()
		file.Close()

elif copy and angRes:
	if merge:
		chain = TChain("rfr") 
	for iJob in range(fileIDMin,fileIDMax):
		print "Job ID:",iJob
		gangaLoc = "/zfs_lhcb/users/%s/gangadir/workspace/%s/LocalXML/%s/output"%(nameID,nameID,iJob)

		# -- Move gen datasets in sub-directory corresponding to the generated configuration (fileTag)
		os.system("mv %s/AngFitResults*.root %s/."%(gangaLoc, anglesFitResultsLoc))
		if merge:
			# - Chain the fit results for each fitting category separately
			fileName = ("%s/AngFitResults_Toys_%s_Exp*.root"%(anglesFitResultsLoc, fileTag))
			chain.Add("%s"%fileName)
	if merge:
		# - Save fit results in a root file for all fitting category
		file = TFile("%s/AngFitResults_Toys_%s_AllExps.root"%(anglesFitResultsLoc, fileTag), "recreate");
		print "Copying fit results trees for all categories..."
		tree = chain.CopyTree("")
		tree.Write()
		file.Close()
		

if merge and not copy and not angRes:
	for iExp in range(fileIDMin,fileIDMax):
		for ibin in l_bins:
			# - Chain the fit results for each fitting category separately
			fileName = ("%s/massFitResults_Toys_%s_Exp%s_AllYearsSigns_%s_%s.root"%(fitResultsLoc, fileTag, iExp, Kpibins[ibin], Kpibins[ibin+1]))
			if debug: print fileName
			chains[ibin].Add("%s"%fileName)
	
	chain = TChain("rfr") 
	for ibin in l_bins:
		# - Chain the fit results for all fitting category
		chain.Add(chains[ibin])
		# - Save fit results in root files for each fitting category separately
		fileRes = TFile("%s/massFitResults_Toys_%s_AllExps_AllYearsSigns_%s_%s.root"%(fitResultsLoc, fileTag, Kpibins[ibin], Kpibins[ibin+1]), "recreate");
		print "Copying fit results trees for %s_%s..."%(Kpibins[ibin], Kpibins[ibin+1])
		treeRes = chains[ibin].CopyTree("")
		treeRes.Write()
		fileRes.Close()

	# - Save fit results in a root file for all fitting category
	file = TFile("%s/massFitResults_Toys_%s_AllExps_AllCats.root"%(fitResultsLoc, fileTag), "recreate");
	print "Copying fit results trees for all categories..."
	tree = chain.CopyTree("")
	tree.Write()
	file.Close()

if merge and not copy and angRes:
	chain = TChain("rfr") 
	for iExp in range(fileIDMin,fileIDMax):
		fileName = ("%s/AngFitResults_Toys_%s_Exp%s.root"%(anglesFitResultsLoc, fileTag, iExp))
		if debug: print fileName
		chain.Add("%s"%fileName)
	# - Save fit results in a root file for all fitting category
	file = TFile("%s/AngFitResults_Toys_%s_AllExps.root"%(anglesFitResultsLoc, fileTag), "recreate");
	print "Copying fit results trees for all categories..."
	tree = chain.CopyTree("")
	tree.Write()
	file.Close()
