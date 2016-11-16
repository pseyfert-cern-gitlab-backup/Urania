from ROOT import *
from GetAcc import *

f0 = TFile("../../fast_ntuples/AnalysisOutWSWeights_Selected_WMC.root")
t0 = f0.Get("AnalysisTree")
f = TFile('thrash.root','recreate')
t = t0.CopyTree("")

P_var_kaon = RooRealVar("P_var_kaon","P_var_kaon",0,250000)
P_var_pion = RooRealVar("P_var_pion","P_var_pion",0,550000)
ETA_var_kaon = RooRealVar("ETA_var_kaon","ETA_var_kaon",0,5.5)
ETA_var_pion = RooRealVar("ETA_var_pion","ETA_var_pion",0,5.5)

data_P_var_kaon = RooDataSet("data_P_var_kaon","data_P_var_kaon",RooArgSet(P_var_kaon))
data_P_var_pion = RooDataSet("data_P_var_pion","data_P_var_pion",RooArgSet(P_var_pion))
data_ETA_var_kaon = RooDataSet("data_ETA_var_kaon","data_ETA_var_kaon",RooArgSet(ETA_var_kaon))
data_ETA_var_pion = RooDataSet("data_ETA_var_pion","data_ETA_var_pion",RooArgSet(ETA_var_pion))

print 'Loading events ...'
for ev in t:
	if ev.itype<0:
		P_var_kaon.setVal(ev.Kplus_P)
		data_P_var_kaon.add(RooArgSet(P_var_kaon))
		P_var_kaon.setVal(ev.Kminus_P)
		data_P_var_kaon.add(RooArgSet(P_var_kaon))
		P_var_pion.setVal(ev.Piplus_P)
		data_P_var_pion.add(RooArgSet(P_var_pion))
		P_var_pion.setVal(ev.Piminus_P)
		data_P_var_pion.add(RooArgSet(P_var_pion))
		ETA_var_kaon.setVal(ev.Kplus_ETA)
		data_ETA_var_kaon.add(RooArgSet(ETA_var_kaon))
		ETA_var_kaon.setVal(ev.Kminus_ETA)
		data_ETA_var_kaon.add(RooArgSet(ETA_var_kaon))
		ETA_var_pion.setVal(ev.Piplus_ETA)
		data_ETA_var_pion.add(RooArgSet(ETA_var_pion))
		ETA_var_pion.setVal(ev.Piminus_ETA)
		data_ETA_var_pion.add(RooArgSet(ETA_var_pion))
print 'Events loaded.'

fr_P_kaon = P_var_kaon.frame()
fr_P_pion = P_var_pion.frame()
fr_ETA_kaon = ETA_var_kaon.frame()
fr_ETA_pion = ETA_var_pion.frame()

data_P_var_kaon.plotOn(fr_P_kaon)
data_P_var_pion.plotOn(fr_P_pion)
data_ETA_var_kaon.plotOn(fr_ETA_kaon)
data_ETA_var_pion.plotOn(fr_ETA_pion)

c = TCanvas("c","c")
c.Divide(2,2)
c.cd(1)
fr_P_kaon.Draw()
c.cd(2)
fr_P_pion.Draw()
c.cd(3)
fr_ETA_kaon.Draw()
c.cd(4)
fr_ETA_pion.Draw()

bins_P_kaon = adaptiveBinning(P_var_kaon,15,0,data_P_var_kaon)
bins_P_pion = adaptiveBinning(P_var_pion,15,0,data_P_var_pion)
bins_ETA_kaon = adaptiveBinning(ETA_var_kaon,8,0,data_ETA_var_kaon)
bins_ETA_pion = adaptiveBinning(ETA_var_pion,8,0,data_ETA_var_pion)
