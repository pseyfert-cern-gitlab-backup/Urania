# O. Leroy, Nov 2013
from os import system
myjob = (44, 45, 46, 37)
target = ("BdJpsiKst_upMC2012_Sim08c_pythia6_DTT.root", "BdJpsiKst_upMC2012_Sim08c_pythia8_DTT.root", "BdJpsiKst_downMC2012_Sim08c_pythia6_DTT.root", "BdJpsiKst_downMC2012_Sim08c_pythia8_DTT.root")


for i in range(4):
 tobemerge = "/zfs_lhcb/users/oleroy/gangadir/workspace/oleroy/LocalXML/%s/*/output/DTT.root" % (myjob[i])
 print "merging root file from job = ", myjob[i], tobemerge, target[i]
 system("hadd %s %s" % (target[i], tobemerge)) 
