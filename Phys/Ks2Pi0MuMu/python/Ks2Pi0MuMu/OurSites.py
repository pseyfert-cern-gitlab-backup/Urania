import os
home = os.environ["HOME"]

tuple_paths ={"USC": {}, "CERN": {}, "DMSLAP": {}}

if "/afs/cern.ch/" in home: SITE = "CERN"
if "home3" in home: SITE = "USC"
if "/home/diegoms/" in home: SITE = "DMSLAP"
if "diego.santos" in home or "diegoms" in home: USER = "Diego"
if "veronika.chobanova" in home or "vchobano" in home: USER = "Veronika"
if "miriam.lucio" in home or "mlucioma" in home: USER = "Miriam"

tuple_paths["USC"]["Diego"] = "/scratch19/Kspi0/"
tuple_paths["DMSLAP"]["Diego"] = home + "/w7folder/Kspi0/"
tuple_paths["USCVC"]["Veronika"] = "/home3/veronika.chobanova/Kspi0/"

MY_TUPLE_PATH = tuple_paths[SITE][USER]
