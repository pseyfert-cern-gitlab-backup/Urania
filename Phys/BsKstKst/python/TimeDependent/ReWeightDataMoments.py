
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

fout = TFile("/Users/jugarcia/Desktop/Software/Bs2KpiKpi/lxplus/fast_ntuples/DataMoments.root","recreate")
tout_data = tin_data.CopyTree("B_s0_DTF_KST1_M>750 && B_s0_DTF_KST2_M>750 && B_s0_DTF_KST1_M<1600 && B_s0_DTF_KST2_M<1600 && itype>0 && B_s0_DTF_TAU>0.5 && B_s0_DTF_TAU<12")
tout_full = tin_data.CopyTree("B_s0_DTF_KST1_TRUE_M>750 && B_s0_DTF_KST2_TRUE_M>750 && B_s0_DTF_KST1_TRUE_M<1600 && B_s0_DTF_KST2_TRUE_M<1600 && (itype==-70 || itype==-80 || itype==-73 || itype==-83) && 1000*B_s0_TRUETAU>0.5 && 1000*B_s0_TRUETAU<12")
tout_gen = tin_gen.CopyTree("B_s0_DTF_KST1_TRUE_M>750 && B_s0_DTF_KST2_TRUE_M>750 && B_s0_DTF_KST1_TRUE_M<1600 && B_s0_DTF_KST2_TRUE_M<1600 && 1000*B_s0_TRUETAU>0.5 && 1000*B_s0_TRUETAU<12")

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

def LegPol(x,i):
    if i==0: return 1.
    elif i==1: return x
    elif i==2: return 0.5*(3.*x*x-1.)
    elif i==3: return 0.5*(5.*x*x*x-3.*x)
    elif i==4: return 1./8.*(35.*x*x*x*x-30.*x*x+3.)
    elif i==5: return 1./8.*(63.*x*x*x*x*x-70.*x*x*x+15.*x)
    elif i==6: return 1./16.*(231.*x*x*x*x*x*x-315.*x*x*x*x+105.*x*x-5.)

gb_weights_data = reweighter.predict_weights(sample_data_array)
weights_M0_m1 = []
weights_M1_m1 = []
weights_M2_m1 = []
weights_M3_m1 = []
weights_M4_m1 = []
weights_M5_m1 = []
weights_M6_m1 = []
weights_M0_m2 = []
weights_M1_m2 = []
weights_M2_m2 = []
weights_M3_m2 = []
weights_M4_m2 = []
weights_M5_m2 = []
weights_M6_m2 = []

sum_w = 0.
N_eff = 6220.

for iw in range(len(gb_weights_data)):
    w_ = w_data[iw]/gb_weights_data[iw]
    x1_ = sample_data_array[iw][2]
    x2_ = sample_data_array[iw][3]
    weights_M0_m1.append(w_*LegPol(x1_,0))
    weights_M1_m1.append(w_*LegPol(x1_,1))
    weights_M2_m1.append(w_*LegPol(x1_,2))
    weights_M3_m1.append(w_*LegPol(x1_,3))
    weights_M4_m1.append(w_*LegPol(x1_,4))
    weights_M5_m1.append(w_*LegPol(x1_,5))
    weights_M6_m1.append(w_*LegPol(x1_,6))
    weights_M0_m2.append(w_*LegPol(x2_,0))
    weights_M1_m2.append(w_*LegPol(x2_,1))
    weights_M2_m2.append(w_*LegPol(x2_,2))
    weights_M3_m2.append(w_*LegPol(x2_,3))
    weights_M4_m2.append(w_*LegPol(x2_,4))
    weights_M5_m2.append(w_*LegPol(x2_,5))
    weights_M6_m2.append(w_*LegPol(x2_,6))
    sum_w += w_

for w_list in [weights_M0_m1,weights_M1_m1,weights_M2_m1,weights_M3_m1,weights_M4_m1,weights_M5_m1,weights_M6_m1,weights_M0_m2,weights_M1_m2,weights_M2_m2,weights_M3_m2,weights_M4_m2,weights_M5_m2,weights_M6_m2]:
    for iw in range(len(w_list)): w_list[iw] *= N_eff/sum_w

gROOT.ProcessLine(\
	"struct MyStruct{\
	Float_t afloat;\
	};")

tout = TTree("AnalysisTree","AnalysisTree")
w_M0_m1 = MyStruct()
br_w_M0_m1 = tout.Branch('w_M0_m1', AddressOf(w_M0_m1,'afloat'), 'w_M0_m1/F')
w_M1_m1 = MyStruct()
br_w_M1_m1 = tout.Branch('w_M1_m1', AddressOf(w_M1_m1,'afloat'), 'w_M1_m1/F')
w_M2_m1 = MyStruct()
br_w_M2_m1 = tout.Branch('w_M2_m1', AddressOf(w_M2_m1,'afloat'), 'w_M2_m1/F')
w_M3_m1 = MyStruct()
br_w_M3_m1 = tout.Branch('w_M3_m1', AddressOf(w_M3_m1,'afloat'), 'w_M3_m1/F')
w_M4_m1 = MyStruct()
br_w_M4_m1 = tout.Branch('w_M4_m1', AddressOf(w_M4_m1,'afloat'), 'w_M4_m1/F')
w_M5_m1 = MyStruct()
br_w_M5_m1 = tout.Branch('w_M5_m1', AddressOf(w_M5_m1,'afloat'), 'w_M5_m1/F')
w_M6_m1 = MyStruct()
br_w_M6_m1 = tout.Branch('w_M6_m1', AddressOf(w_M6_m1,'afloat'), 'w_M6_m1/F')
w_M0_m2 = MyStruct()
br_w_M0_m2 = tout.Branch('w_M0_m2', AddressOf(w_M0_m2,'afloat'), 'w_M0_m2/F')
w_M1_m2 = MyStruct()
br_w_M1_m2 = tout.Branch('w_M1_m2', AddressOf(w_M1_m2,'afloat'), 'w_M1_m2/F')
w_M2_m2 = MyStruct()
br_w_M2_m2 = tout.Branch('w_M2_m2', AddressOf(w_M2_m2,'afloat'), 'w_M2_m2/F')
w_M3_m2 = MyStruct()
br_w_M3_m2 = tout.Branch('w_M3_m2', AddressOf(w_M3_m2,'afloat'), 'w_M3_m2/F')
w_M4_m2 = MyStruct()
br_w_M4_m2 = tout.Branch('w_M4_m2', AddressOf(w_M4_m2,'afloat'), 'w_M4_m2/F')
w_M5_m2 = MyStruct()
br_w_M5_m2 = tout.Branch('w_M5_m2', AddressOf(w_M5_m2,'afloat'), 'w_M5_m2/F')
w_M6_m2 = MyStruct()
br_w_M6_m2 = tout.Branch('w_M6_m2', AddressOf(w_M6_m2,'afloat'), 'w_M6_m2/F')
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
    w_M0_m1.afloat = weights_M0_m1[i]
    w_M1_m1.afloat = weights_M1_m1[i]
    w_M2_m1.afloat = weights_M2_m1[i]
    w_M3_m1.afloat = weights_M3_m1[i]
    w_M4_m1.afloat = weights_M4_m1[i]
    w_M5_m1.afloat = weights_M5_m1[i]
    w_M6_m1.afloat = weights_M6_m1[i]
    w_M0_m2.afloat = weights_M0_m2[i]
    w_M1_m2.afloat = weights_M1_m2[i]
    w_M2_m2.afloat = weights_M2_m2[i]
    w_M3_m2.afloat = weights_M3_m2[i]
    w_M4_m2.afloat = weights_M4_m2[i]
    w_M5_m2.afloat = weights_M5_m2[i]
    w_M6_m2.afloat = weights_M6_m2[i]
    sample = sample_data_array[i]
    m1.afloat = sample[0]
    m2.afloat = sample[1]
    cos1.afloat = sample[2]
    cos2.afloat = sample[3]
    phi.afloat = sample[4]
    t.afloat = sample[5]
    tout.Fill()

print 'Weights added.'

c = TCanvas("c","c",1800,600)
c.Divide(3,2)

line = TLine(750,0,1600,0)
line.SetLineWidth(1)
line.SetLineStyle(2)

c.cd(1)
tout.SetLineColorAlpha(kRed,0.5)
tout.SetFillColorAlpha(kRed,0.5)
tout.Draw("m1","w_M1_m1","e3")
c.cd(1).FindObject("htemp").Sumw2()
c.cd(1).FindObject("htemp").Rebin(4)
c.cd(1).FindObject("htemp").GetXaxis().SetTitle("M(K#pi) (MeV/c^{2})")
c.cd(1).FindObject("htemp").GetXaxis().SetRangeUser(750,1600)
c.cd(1).FindObject("htemp").GetYaxis().SetRangeUser(-270,270)
c.cd(1).FindObject("htemp").GetYaxis().SetTitle("P1")
tout.SetLineColorAlpha(kBlue,0.5)
tout.SetFillColorAlpha(kBlue,0.5)
tout.Draw("m2","w_M1_m2","e3same")
line.Draw()

c.cd(2)
tout.SetLineColorAlpha(kRed,0.5)
tout.SetFillColorAlpha(kRed,0.5)
tout.Draw("m1","w_M2_m1","e3")
c.cd(2).FindObject("htemp").Sumw2()
c.cd(2).FindObject("htemp").Rebin(4)
c.cd(2).FindObject("htemp").GetXaxis().SetTitle("M(K#pi) (MeV/c^{2})")
c.cd(2).FindObject("htemp").GetXaxis().SetRangeUser(750,1600)
c.cd(2).FindObject("htemp").GetYaxis().SetRangeUser(-270,270)
c.cd(2).FindObject("htemp").GetYaxis().SetTitle("P2")
tout.SetLineColorAlpha(kBlue,0.5)
tout.SetFillColorAlpha(kBlue,0.5)
tout.Draw("m2","w_M2_m2","e3same")
line.Draw()

c.cd(3)
tout.SetLineColorAlpha(kRed,0.5)
tout.SetFillColorAlpha(kRed,0.5)
tout.Draw("m1","w_M3_m1","e3")
c.cd(3).FindObject("htemp").Sumw2()
c.cd(3).FindObject("htemp").Rebin(4)
c.cd(3).FindObject("htemp").GetXaxis().SetTitle("M(K#pi) (MeV/c^{2})")
c.cd(3).FindObject("htemp").GetXaxis().SetRangeUser(750,1600)
c.cd(3).FindObject("htemp").GetYaxis().SetRangeUser(-270,270)
c.cd(3).FindObject("htemp").GetYaxis().SetTitle("P3")
tout.SetLineColorAlpha(kBlue,0.5)
tout.SetFillColorAlpha(kBlue,0.5)
tout.Draw("m2","w_M3_m2","e3same")
line.Draw()

c.cd(4)
tout.SetLineColorAlpha(kRed,0.5)
tout.SetFillColorAlpha(kRed,0.5)
tout.Draw("m1","w_M4_m1","e3")
c.cd(4).FindObject("htemp").Sumw2()
c.cd(4).FindObject("htemp").Rebin(4)
c.cd(4).FindObject("htemp").GetXaxis().SetTitle("M(K#pi) (MeV/c^{2})")
c.cd(4).FindObject("htemp").GetXaxis().SetRangeUser(750,1600)
c.cd(4).FindObject("htemp").GetYaxis().SetRangeUser(-270,270)
c.cd(4).FindObject("htemp").GetYaxis().SetTitle("P4")
tout.SetLineColorAlpha(kBlue,0.5)
tout.SetFillColorAlpha(kBlue,0.5)
tout.Draw("m2","w_M4_m2","e3same")
line.Draw()

c.cd(5)
tout.SetLineColorAlpha(kRed,0.5)
tout.SetFillColorAlpha(kRed,0.5)
tout.Draw("m1","w_M5_m1","e3")
c.cd(5).FindObject("htemp").Sumw2()
c.cd(5).FindObject("htemp").Rebin(4)
c.cd(5).FindObject("htemp").GetXaxis().SetTitle("M(K#pi) (MeV/c^{2})")
c.cd(5).FindObject("htemp").GetXaxis().SetRangeUser(750,1600)
c.cd(5).FindObject("htemp").GetYaxis().SetRangeUser(-270,270)
c.cd(5).FindObject("htemp").GetYaxis().SetTitle("P5")
tout.SetLineColorAlpha(kBlue,0.5)
tout.SetFillColorAlpha(kBlue,0.5)
tout.Draw("m2","w_M5_m2","e3same")
line.Draw()

c.cd(6)
tout.SetLineColorAlpha(kRed,0.5)
tout.SetFillColorAlpha(kRed,0.5)
tout.Draw("m1","w_M6_m1","e3")
c.cd(6).FindObject("htemp").Sumw2()
c.cd(6).FindObject("htemp").Rebin(4)
c.cd(6).FindObject("htemp").GetXaxis().SetTitle("M(K#pi) (MeV/c^{2})")
c.cd(6).FindObject("htemp").GetXaxis().SetRangeUser(750,1600)
c.cd(6).FindObject("htemp").GetYaxis().SetRangeUser(-270,270)
c.cd(6).FindObject("htemp").GetYaxis().SetTitle("P6")
tout.SetLineColorAlpha(kBlue,0.5)
tout.SetFillColorAlpha(kBlue,0.5)
tout.Draw("m2","w_M6_m2","e3same")
line.Draw()

c.Print("DataMomentDistr.root")
c.Print("DataMomentDistr.pdf")

tout.Write()
fout.Close()
