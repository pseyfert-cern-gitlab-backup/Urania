# O. Leroy, Nov 2013
from os import system
tuplehere = ("BdJpsiKst_upMC2012_Sim08c_pythia6_DTT.root", "BdJpsiKst_upMC2012_Sim08c_pythia8_DTT.root", "BdJpsiKst_downMC2012_Sim08c_pythia6_DTT.root", "BdJpsiKst_downMC2012_Sim08c_pythia8_DTT.root")


for i in range(4):
 origin = "/zfs_lhcb/users/oleroy/2012-MC-Sim08a/BdJpsiKst_Sim08c/%s" % (tuplehere[i])
 target = "/lhcb/user/o/ooleroy/MC/2012/%s" % (tuplehere[i])
 print "Copying to castor ", origin, target
 system("dirac-dms-add-file %s %s CERN-USER" % (target, origin)) 
