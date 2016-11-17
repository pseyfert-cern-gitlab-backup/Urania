from ROOT import *
from fiducial import *
TUPLE_PATH = "/scratch18/diego/Ksmm/"

fs = TFile("/scratch18/MC_KsmumuNew_TisTisTos_TosTos1Tos_TosTos2Tos.root")
ts = fs.Get("DecayTree")
f, t = {}, {}
f["TIS_"] = TFile(TUPLE_PATH +"Ks0mumu_Data2012_Splitted_Res20_MuPtCutOff2500_TisTisTos_MVA.root")
t["TIS_"] = f["TIS_"].Get("KS0mumu")
f["TOS1_"] = TFile(TUPLE_PATH + "Ks0mumu_Data2012_Splitted_Res20_MuPtCutOff2500_TosTos1Tos_MVA.root")
t["TOS1_"] = f["TOS1_"].Get("KS0mumu")
f["TOS2_"] = TFile(TUPLE_PATH + "Ks0mumu_Data2012_Splitted_Res20_MuPtCutOff2500_TosTos2Tos_MVA.root")
t["TOS2_"] = f["TOS2_"].Get("KS0mumu")
f2 = TFile("./crap.root", "recreate")
ts2 = ts.CopyTree(fSEL["TIS_"])
from SomeUtils.NewKarlen import *
l = []
for entry in ts2: l.append(entry.TisTisTos_BDTb025de4nt1000M1)
ufv = UniFunc(l)
binTIS = [ufv.inverse(0.1*i) for i in range(11)]
ts2 = ts.CopyTree(fSEL["TOS1_"])
#from SomeUtils.NewKarlen import *
l = []
for entry in ts2: l.append(entry.TosTos1Tos_BDTb025de4nt1000M1)
ufv = UniFunc(l)
binTOS1 = [ufv.inverse(0.1*i) for i in range(11)]

ts2 = ts.CopyTree(fSEL["TOS2_"])
#from SomeUtils.NewKarlen import *
l = []
for entry in ts2: l.append(entry.TosTos2Tos_BDTb025de4nt1000M1)
ufv = UniFunc(l)
binTOS2 = [ufv.inverse(0.1*i) for i in range(11)]

bdtname = {}
bdtname["TIS_"] = "BDTb025de4nt1000M1_TisTisTos"
bdtname["TOS1_"] =  "BDTb025de4nt1000M1_TosTos1Tos"
bdtname["TOS2_"] = "BDTb025de4nt1000M1_TosTos2Tos"
######  Prepare files
from bisect import *
Binning = {}
Binning["TIS_"] =  binTIS#[bisect(binTIS,0.32):]
Binning["TOS1_"] =  binTOS1#[bisect(binTOS1,0.2):]
Binning["TOS2_"] =  binTOS2#[bisect(binTOS2,0.3):]

Binning["TIS_"][-1] = 1
Binning["TOS1_"][-1] = 1
Binning["TOS2_"][-1] = 1


name = f2.GetName()

def diagnose(key):
    f2 = TFile(name, "recreate")
    t2 = ts.CopyTree(fSEL[key])
    bins = Binning[key]
    bdt = bdtname[key]
    for i in range(len(bins)-1):
        print i, t2.GetEntries(bdt +">"+str(bins[i]) + aa + bdt +"<" + str(bins[i+1]))
        
diagnose('TIS_')
diagnose('TOS1_')
diagnose('TOS2_')
