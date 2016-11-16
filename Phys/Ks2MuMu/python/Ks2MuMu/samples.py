from ROOT import *
from fiducial import *
f = TFile("kspipi_ntuple_251111_1000pb.root")
tp = f.Get("Ks2pipi")

f2 = TFile("TrainS.root","recreate")
t2 = tp.CopyTree("mu1ptot<100000 && mu2ptot<100000 && Blife_ps_r<140 && runNum<97500 && Vchi2<25 && L0Tis && Hlt1Tis && Hlt2Tis")
t2.Write()
f2.Close()


f2 = TFile("TestS.root","recreate")
t2 = tp.CopyTree("mu1ptot<100000 && mu2ptot<100000 && Blife_ps_r<140 && runNum>=97500 && Vchi2<25 && L0Tis && Hlt1Tis && Hlt2Tis")
t2.Write()
f2.Close()


f = TFile("ksmumu_ntuple_251111_1000pb.root")
tp = f.Get("Ks2mumu")

f2 = TFile("TrainB.root","recreate")
t2 = tp.CopyTree("mu1ptot<100000 && mu2ptot<100000 && Blife_ps_r<140 && runNum<97500 && Vchi2<25 && Bmass>1100")
t2.Write()
f2.Close()


f2 = TFile("TestB.root","recreate")
t2 = tp.CopyTree("mu1ptot<100000 && mu2ptot<100000 && Blife_ps_r<140 && runNum>=97500 && Vchi2<25 && Bmass>1100")
t2.Write()
f2.Close()





