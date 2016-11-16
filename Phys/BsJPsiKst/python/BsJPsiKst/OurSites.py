import os
SITE = "None"
if "cern.ch" in os.environ["HOME"]: SITE = "CERN"
if (0>1) : SITE = "USC" ### Write here appropriate condition
if "/lhcb/users/" in os.environ["HOME"] and not "cern.ch" in os.environ["HOME"] : SITE = "CPPM" ## """
if "/lhcb/users/akar" in os.environ["HOME"] and not "cern.ch" in os.environ["HOME"] : SITE = "SAKAR" ## """
if os.path.exists("/project/bfys"): SITE = "NIKHEF"
if "/home/diegoms" in os.environ["HOME"]: SITE = "DMSLAP"
#if (0>1) : SITE = "Russia" 
print"SITE:",SITE

if SITE == "None":
    print"ERROR: No NtuplePath specified"
    exit(0)

NtuplePaths = {}
NtuplePaths["CERN"] = "/afs/cern.ch/user/d/diegoms/vol5/WG_sign_off/"
NtuplePaths["CPPM"] = "/zfs_lhcb/users/kanso/realData/for_jpsiK/"
NtuplePaths["SAKAR"] = "/zfs_lhcb/users/sakar/realData/JpsiKst/"
NtuplePaths["DMSLAP"] = "~/w7folder/NTuples/"
NTUPLE_PATH = NtuplePaths[SITE]
