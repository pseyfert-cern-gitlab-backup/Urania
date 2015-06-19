import os
SITE = "None"
if "cern.ch" in os.environ["HOME"]: SITE = "CERN"
if (0>1) : SITE = "USC" ### Write here appropriate condition
if (0>1) : SITE = "CPPM" ## """
if os.path.exists("/project/bfys"): SITE = "NIKHEF"
if os.path.exists("/home/diegoms/w7folder/NTuples/Bs_Jpsi_Kst_2013/"): SITE = "MyLaptop"
#if os.path.exists("/home/galaceos/cmtuser/URANIA/URANIA_HEAD/Phys/BsJPsiKst/ntuples/"): SITE = "MyLaptop"
#if (0>1) : SITE = "Russia" 

NtuplePaths = {}
NtuplePaths["CERN"] = "/afs/cern.ch/user/d/diegoms/vol5/Bs_Jpsi_Kst_2013/"
#NtuplePaths["MyLaptop"] = "/home/diegoms/w7folder/NTuples/Bs_Jpsi_Kst_2013/"
NtuplePaths["MyLaptop"] = "/home/galaceos/cmtuser/URANIA/URANIA_HEAD/Phys/BsJPsiKst/ntuples/"

NTUPLE_PATH = NtuplePaths[SITE]
