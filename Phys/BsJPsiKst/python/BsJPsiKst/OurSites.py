import os
SITE = "None"
if "cern.ch" in os.environ["HOME"]: SITE = "CERN"
if (0>1) : SITE = "USC" ### Write here appropriate condition
if (0>1) : SITE = "CPPM" ## """
if os.path.exists("/project/bfys"): SITE = "NIKHEF"
#if (0>1) : SITE = "Russia" 

NtuplePaths = {}
NtuplePaths["CERN"] = "/afs/cern.ch/user/d/diegoms/vol5/Bs_Jpsi_Kst_2013/"


NTUPLE_PATH = NtuplePaths[SITE]
