from ROOT import *
from hep_ml import reweight
import numpy as np
from random import randrange

gROOT.ProcessLine('.x /Users/jugarcia/Desktop/Software/Bs2KpiKpi/lxplus/src/TimeDependent/lhcbStyle.C')
gStyle.SetMarkerSize(0)

# ##################################################
# Input data

branches_data = [
	"B_s0_DTF_KST1_M",
	"B_s0_DTF_KST2_M",
	"B_s0_DTF_B_s0_CosTheta1",
	"B_s0_DTF_B_s0_CosTheta2",
	"B_s0_DTF_B_s0_PHI_TRY4",
	"B_s0_DTF_TAU"
	]

branches_full = [
	"B_s0_DTF_KST1_TRUE_M",
	"B_s0_DTF_KST2_TRUE_M",
	"B_s0_DTF_KST1_TRUE_COSTHETA",
	"B_s0_DTF_KST2_TRUE_COSTHETA",
	"B_s0_DTF_B_s0_PHI_TRUE_TRY4",
	"B_s0_TRUETAU"
	]

branches_gen = [
	"B_s0_DTF_KST1_TRUE_M",
	"B_s0_DTF_KST2_TRUE_M",
	"B_s0_DTF_KST1_TRUE_COSTHETA",
	"B_s0_DTF_KST2_TRUE_COSTHETA",
	"B_s0_DTF_B_s0_PHI_TRUE_TRY4",
	"B_s0_TRUETAU"
	]

mctype = "Comb"

fin_data = TFile("/Users/jugarcia/Desktop/Software/Bs2KpiKpi/lxplus/fast_ntuples/AnalysisOutWSWeightsSelectedAllBranchesUpdated.root")
tin_data = fin_data.Get("AnalysisTree")
tin_data.SetBranchStatus("*",0)
for br in branches_data: tin_data.SetBranchStatus(br,1)
for br in branches_full: tin_data.SetBranchStatus(br,1)
tin_data.SetBranchStatus("itype",1)
tin_data.SetBranchStatus("sweight",1)

fin_gen = TFile("/Users/jugarcia/Downloads/"+mctype+"MCGenLevel.root")
tin_gen = fin_gen.Get("MCDecayTree")
tin_gen.SetBranchStatus("*",0)
tin_gen.SetBranchStatus("weight",1)
for br in branches_gen: tin_gen.SetBranchStatus(br,1)

fout = TFile("/Users/jugarcia/Desktop/Software/Bs2KpiKpi/lxplus/fast_ntuples/MassPlaneMLAU.root","recreate")
tout_data = tin_data.CopyTree("B_s0_DTF_KST1_M>750 && B_s0_DTF_KST2_M>750 && B_s0_DTF_KST1_M<1600 && B_s0_DTF_KST2_M<1600 && itype>0 && B_s0_DTF_TAU>0.7 && B_s0_DTF_TAU<12")
tout_full = tin_data.CopyTree("B_s0_DTF_KST1_TRUE_M>750 && B_s0_DTF_KST2_TRUE_M>750 && B_s0_DTF_KST1_TRUE_M<1600 && B_s0_DTF_KST2_TRUE_M<1600 && (itype==-70 || itype==-80 || itype==-73 || itype==-83) && 1000*B_s0_TRUETAU>0.7 && 1000*B_s0_TRUETAU<12")
tout_gen = tin_gen.CopyTree("B_s0_DTF_KST1_TRUE_M>750 && B_s0_DTF_KST2_TRUE_M>750 && B_s0_DTF_KST1_TRUE_M<1600 && B_s0_DTF_KST2_TRUE_M<1600 && 1000*B_s0_TRUETAU>0.7 && 1000*B_s0_TRUETAU<12")

print tout_data.GetEntries()
print tout_full.GetEntries()
print tout_gen.GetEntries()

# ##################################################
# Transformation of samples into numpy array format

sample_data = []
sample_full = []
sample_gen = []
w_data = []
w_gen = []

print 'Filling datasets ...'
for ev in tout_data:
	br_values = []
	for br in branches_data: br_values.append(eval("ev."+br))
	sample_data.append(br_values)
	w_data.append(ev.sweight)

for ev in tout_full:
	br_values = []
	for br in branches_full: br_values.append(eval("ev."+br))
	sample_full.append(br_values)

for ev in tout_gen:
	br_values = []
	for br in branches_gen: br_values.append(eval("ev."+br))
	sample_gen.append(br_values)
	w_gen.append(ev.weight)
print 'Datasets filled.'

for iev in range(len(sample_full)): sample_full[iev][5] *= 1000.
for iev in range(len(sample_gen)): sample_gen[iev][5] *= 1000.

def randomize1(d_in):
   num = len(d_in)
   l_index = range(num)
   d_out = []
   for i in range(num):
      index = l_index.pop(randrange(len(l_index)))
      d_out.append(d_in[index])
   return d_out

def randomize2(d_in,w_in):
   num = len(d_in)
   l_index = range(num)
   d_out = []
   w_out = []
   for i in range(num):
      index = l_index.pop(randrange(len(l_index)))
      d_out.append(d_in[index])
      w_out.append(w_in[index])
   return d_out, w_out

sample_full = randomize1(sample_full)
sample_gen, w_gen = randomize2(sample_gen, w_gen)

sample_data_array = np.array(sample_data,np.float64)
sample_full_array = np.array(sample_full,np.float64)
sample_gen_array = np.array(sample_gen,np.float64)
w_gen_array = np.array(w_gen,np.float64)

# ##################################################
# Computation of weights for real data

print 'Training method ...'
reweighter = reweight.GBReweighter(n_estimators=600, learning_rate=0.01, max_depth=4, loss_regularization=100.0, min_samples_leaf=600)
reweighter.fit(original = sample_gen_array, target = sample_full_array, original_weight = w_gen_array)
print 'Method trained.'

gb_weights_data = reweighter.predict_weights(sample_data_array)
sum_sw = 0.
sum_swsw = 0.
sum_w = 0.
sum_ww = 0.
for iw in range(len(gb_weights_data)):
	gb_weights_data[iw] = 1./gb_weights_data[iw]
	w_ = w_data[iw]*gb_weights_data[iw]
	sum_sw += w_data[iw]
	sum_swsw += w_data[iw]*w_data[iw]
	sum_w += w_
	sum_ww += w_*w_

gROOT.ProcessLine(\
	"struct MyStruct{\
	Float_t afloat;\
	};")

tout = TTree("AnalysisTree","AnalysisTree")
accweight = MyStruct()
br_accweight = tout.Branch('accweight', AddressOf(accweight,'afloat'), 'accweight/F')
sweight = MyStruct()
br_sweight = tout.Branch('sweight', AddressOf(sweight,'afloat'), 'sweight/F')
weight = MyStruct()
br_weight = tout.Branch('weight', AddressOf(weight,'afloat'), 'weight/F')
m1 = MyStruct()
br_m1 = tout.Branch('m1', AddressOf(m1,'afloat'), 'm1/F')
m2 = MyStruct()
br_m2 = tout.Branch('m2', AddressOf(m2,'afloat'), 'm2/F')
cos1 = MyStruct()
br_cos1 = tout.Branch('cos1', AddressOf(cos1,'afloat'), 'cos1/F')
cos2 = MyStruct()
br_cos2 = tout.Branch('cos2', AddressOf(cos2,'afloat'), 'cos2/F')
phi = MyStruct()
br_phi = tout.Branch('phi', AddressOf(phi,'afloat'), 'phi/F')
t = MyStruct()
br_t = tout.Branch('t', AddressOf(t,'afloat'), 't/F')

print 'Adding weights ...'

for i in range(len(sample_data_array)):
	accweight.afloat = gb_weights_data[i]
	sweight.afloat = w_data[i]*sum_sw/sum_swsw
	weight.afloat = w_data[i]*gb_weights_data[i]*sum_w/sum_ww
	sample = sample_data_array[i]
	m1_ = sample[0]
	m2_ = sample[1]
	m1.afloat = m1_
	m2.afloat = m2_
	#if (m1_>=m2_):
	#	m1.afloat = m1_
	#	m2.afloat = m2_
	#else:
	#	m1.afloat = m2_
	#	m2.afloat = m1_
	cos1.afloat = sample[2]
	cos2.afloat = sample[3]
	phi.afloat = sample[4]
	t.afloat = sample[5]
	tout.Fill()
	m1.afloat = m2_
	m2.afloat = m1_
	tout.Fill()

print 'Weights added.'

# ##################################################
# Check of the reweighting procedure in MC

gb_weights_full = reweighter.predict_weights(sample_full_array)

tout_check = TTree("Check","Check")
accweight_check = MyStruct()
br_check_accweight = tout_check.Branch('accweight', AddressOf(accweight_check,'afloat'), 'accweight/F')
evtype_check = MyStruct()
br_check_evtype = tout_check.Branch('evtype', AddressOf(evtype_check,'afloat'), 'evtype/F')
m1_check = MyStruct()
br_check_m1 = tout_check.Branch('m1', AddressOf(m1_check,'afloat'), 'm1/F')
m2_check = MyStruct()
br_check_m2 = tout_check.Branch('m2', AddressOf(m2_check,'afloat'), 'm2/F')
cos1_check = MyStruct()
br_check_cos1 = tout_check.Branch('cos1', AddressOf(cos1_check,'afloat'), 'cos1/F')
cos2_check = MyStruct()
br_check_cos2 = tout_check.Branch('cos2', AddressOf(cos2_check,'afloat'), 'cos2/F')
phi_check = MyStruct()
br_check_phi = tout_check.Branch('phi', AddressOf(phi_check,'afloat'), 'phi/F')
t_check = MyStruct()
br_check_t = tout_check.Branch('t', AddressOf(t_check,'afloat'), 't/F')

sum_w_check = 0.
for w in gb_weights_full: sum_w_check += 1./w

sum_w_gen = 0.
for w in w_gen: sum_w_gen += w

for i in range(len(sample_gen_array)):
	accweight_check.afloat = 1./sum_w_gen
	evtype_check.afloat = 0.
	sample = sample_gen_array[i]
	m1_check.afloat = sample[0]
	m2_check.afloat = sample[1]
	cos1_check.afloat = sample[2]
	cos2_check.afloat = sample[3]
	phi_check.afloat = sample[4]
	t_check.afloat = sample[5]
	tout_check.Fill()

for i in range(len(sample_full_array)):
	accweight_check.afloat = 1./gb_weights_full[i]/sum_w_check
	evtype_check.afloat = 1.
	sample = sample_full_array[i]
	m1_check.afloat = sample[0]
	m2_check.afloat = sample[1]
	cos1_check.afloat = sample[2]
	cos2_check.afloat = sample[3]
	phi_check.afloat = sample[4]
	t_check.afloat = sample[5]
	tout_check.Fill()
	accweight_check.afloat = 1./float(tout_full.GetEntries())
	evtype_check.afloat = 2.
	tout_check.Fill()

c = TCanvas("c","c",1800,600)
c.Divide(3,2)
c.cd(1)
tout_check.SetLineColor(kRed)
tout_check.Draw("m1","accweight*(evtype==0)")
c.cd(1).FindObject("htemp").Rebin(4)
c.cd(1).FindObject("htemp").GetXaxis().SetTitle("M(K^{+}#pi^{-}) (MeV/c^{2})")
tout_check.SetLineColor(kBlue)
tout_check.Draw("m1","accweight*(evtype==1)","same")
tout_check.SetLineColor(kGreen+3)
tout_check.Draw("m1","accweight*(evtype==2)","same")
c.cd(2)
tout_check.SetLineColor(kRed)
tout_check.Draw("m2","accweight*(evtype==0)")
c.cd(2).FindObject("htemp").Rebin(4)
c.cd(2).FindObject("htemp").GetXaxis().SetTitle("M(K^{-}#pi^{+}) (MeV/c^{2})")
tout_check.SetLineColor(kBlue)
tout_check.Draw("m2","accweight*(evtype==1)","same")
tout_check.SetLineColor(kGreen+3)
tout_check.Draw("m2","accweight*(evtype==2)","same")
c.cd(3)
tout_check.SetLineColor(kRed)
tout_check.Draw("t","accweight*(evtype==0)")
c.cd(3).FindObject("htemp").Rebin(4)
c.cd(3).FindObject("htemp").GetXaxis().SetTitle("t (ps)")
tout_check.SetLineColor(kBlue)
tout_check.Draw("t","accweight*(evtype==1)","same")
tout_check.SetLineColor(kGreen+3)
tout_check.Draw("t","accweight*(evtype==2)","same")
c.cd(4)
tout_check.SetLineColor(kRed)
tout_check.Draw("cos1","accweight*(evtype==0)")
c.cd(4).FindObject("htemp").Rebin(4)
c.cd(4).FindObject("htemp").GetXaxis().SetTitle("cos(#theta_{1})")
tout_check.SetLineColor(kBlue)
tout_check.Draw("cos1","accweight*(evtype==1)","same")
tout_check.SetLineColor(kGreen+3)
tout_check.Draw("cos1","accweight*(evtype==2)","same")
c.cd(5)
tout_check.SetLineColor(kRed)
tout_check.Draw("cos2","accweight*(evtype==0)")
c.cd(5).FindObject("htemp").Rebin(4)
c.cd(5).FindObject("htemp").GetXaxis().SetTitle("cos(#theta_{2})")
tout_check.SetLineColor(kBlue)
tout_check.Draw("cos2","accweight*(evtype==1)","same")
tout_check.SetLineColor(kGreen+3)
tout_check.Draw("cos2","accweight*(evtype==2)","same")
c.cd(6)
tout_check.SetLineColor(kRed)
tout_check.Draw("phi","accweight*(evtype==0)")
c.cd(6).FindObject("htemp").Rebin(4)
c.cd(6).FindObject("htemp").GetXaxis().SetTitle("#varphi (rad)")
tout_check.SetLineColor(kBlue)
tout_check.Draw("phi","accweight*(evtype==1)","same")
tout_check.SetLineColor(kGreen+3)
tout_check.Draw("phi","accweight*(evtype==2)","same")

c.Print("MCReWeightingTest.root")
c.Print("MCReWeightingTest.pdf")

tout.Write()
fout.Close()
