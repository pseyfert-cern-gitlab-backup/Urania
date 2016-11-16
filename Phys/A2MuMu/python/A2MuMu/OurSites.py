import os
home = os.environ["HOME"]

tuple_paths ={"USC": {}, "CERN": {}, "DMSLAP": {}}

if "/afs/cern.ch/" in home: SITE = "CERN"
if "home3" in home: SITE = "USC"
#if "/home/diegoms" in home: SITE = "DMSLAP"
if "martino.borsato" in home or "mborsato" in home: USER = "Martino"
#if "diego.santos" in home or "diegoms" in home: USER = "Diego"

tuple_paths["USC"]["Martino"] = "/scratch19/Martino/A1MuMu/TUPLES/"
tuple_paths["CERN"]["Martino"] = "/eos/lhcb/user/c/cvazquez/A1MuMu/no_top_tagging_ntuples/"
#tuple_paths["DMSLAP"]["Diego"] = home + "/w7folder/Kspi0/"

MY_TUPLE_PATH = tuple_paths[SITE][USER]
