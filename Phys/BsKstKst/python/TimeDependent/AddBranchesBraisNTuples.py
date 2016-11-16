from ROOT import *
from SetupDataInterface import *
from math import pi

f2DPIDkaon = TFile(NTUPLE_PATH + "PerfHists_K_Strip20_MagUp_BSKPIKPI_KAON_P_ETA.root")
h2DPIDkaon = f2DPIDkaon.Get("K_DLLK>2. && (V2ProbNNK*(1.-V2ProbNNpi)>0.3)_All")
f2DPIDpion = TFile(NTUPLE_PATH + "PerfHists_Pi_Strip20_MagUp_BSKPIKPI_PION_P_ETA.root")
h2DPIDpion = f2DPIDpion.Get("Pi_DLLK<0._All")

def dataMCcorrweight(entry):

	wPIDkaon1 = h2DPIDkaon.GetBinContent(h2DPIDkaon.FindBin(entry.Kplus_P,0.5*log((entry.Kplus_P+entry.Kplus_PZ)/(entry.Kplus_P-entry.Kplus_PZ))))
	wPIDkaon2 = h2DPIDkaon.GetBinContent(h2DPIDkaon.FindBin(entry.Kminus_P,0.5*log((entry.Kminus_P+entry.Kminus_PZ)/(entry.Kminus_P-entry.Kminus_PZ))))
	wPIDpion1 = h2DPIDpion.GetBinContent(h2DPIDpion.FindBin(entry.piplus_P,0.5*log((entry.piplus_P+entry.piplus_PZ)/(entry.piplus_P-entry.piplus_PZ))))
	wPIDpion2 = h2DPIDpion.GetBinContent(h2DPIDpion.FindBin(entry.piminus_P,0.5*log((entry.piminus_P+entry.piminus_PZ)/(entry.piminus_P-entry.piminus_PZ))))

	return wPIDkaon1*wPIDkaon2*wPIDpion1*wPIDpion2

f1 = TFile(NTUPLE_PATH + "Bs2KstKst_MCnoPID_2011.root")
t1 = f1.Get("nTuple/DecayTree")
f2 = TFile(NTUPLE_PATH + "Bs2KstKst_MCnoPID_2012.root")
t2 = f2.Get("nTuple/DecayTree")
fout = TFile(NTUPLE_PATH + "Bs2KstKst_MCnoPID_2.root","RECREATE")
print "Copying the original trees ..."
t1c = t1.CopyTree("")
t2c = t2.CopyTree("")
print "Trees copied."

"""kpeta = MyStruct()
newBranchkpeta = tout.Branch('Kplus_ETA', AddressOf(kpeta,'afloat'), 'Kplus_ETA/F')
kmeta = MyStruct()
newBranchkmeta = tout.Branch('Kminus_ETA', AddressOf(kmeta,'afloat'), 'Kminus_ETA/F')
pipeta = MyStruct()
newBranchpipeta = tout.Branch('piplus_ETA', AddressOf(pipeta,'afloat'), 'piplus_ETA/F')
pimeta = MyStruct()
newBranchpimeta = tout.Branch('piminus_ETA', AddressOf(pimeta,'afloat'), 'piminus_ETA/F')
mkpi1 = MyStruct()
newBranchmkpi1 = tout.Branch('B_s0_DTF_KST1_M', AddressOf(mkpi1,'afloat'), 'B_s0_DTF_KST1_M/F')
mkpi2 = MyStruct()
newBranchmkpi2 = tout.Branch('B_s0_DTF_KST2_M', AddressOf(mkpi2,'afloat'), 'B_s0_DTF_KST2_M/F')
cos1 = MyStruct()
newBranchcos1 = tout.Branch('B_s0_DTF_B_s0_CosTheta1', AddressOf(cos1,'afloat'), 'B_s0_DTF_B_s0_CosTheta1/F')
cos2 = MyStruct()
newBranchcos2 = tout.Branch('B_s0_DTF_B_s0_CosTheta2', AddressOf(cos2,'afloat'), 'B_s0_DTF_B_s0_CosTheta2/F')
phi = MyStruct()
newBranchphi = tout.Branch('B_s0_DTF_B_s0_Phi1', AddressOf(phi,'afloat'), 'B_s0_DTF_B_s0_Phi1/F')
tau = MyStruct()
newBranchtau = tout.Branch('B_s0_DTF_TAU', AddressOf(tau,'afloat'), 'B_s0_DTF_TAU/F')
year = MyStruct()
newBranchyear = tout.Branch('itype', AddressOf(year,'afloat'), 'itype/F')
weight = MyStruct()
newBranchweight = tout.Branch('PIDweight', AddressOf(weight,'afloat'), 'PIDweight/F')
weightcorr = MyStruct()
newBranchweightcorr = tout.Branch('PIDweightcorrected', AddressOf(weightcorr,'afloat'), 'PIDweightcorrected/F')"""

h_cos1 = TH1F("h_cos1","h_cos1",40,-1,1)
h_cos2 = TH1F("h_cos2","h_cos2",40,-1,1)
h_phi = TH1F("h_phi","h_phi",40,-pi,pi)
h_cos1_corr = TH1F("h_cos1_corr","h_cos1_corr",40,-1,1)
h_cos2_corr = TH1F("h_cos2_corr","h_cos2_corr",40,-1,1)
h_phi_corr = TH1F("h_phi_corr","h_phi_corr",40,-pi,pi)

for i in [h_cos1,h_cos2,h_phi,h_cos1_corr,h_cos2_corr,h_phi_corr]:
	i.Sumw2()

kp = TLorentzVector()
pim = TLorentzVector()
km = TLorentzVector()
pip = TLorentzVector()

print "Processing events ..."

counter = 0
for i in t1c:
	if counter<100000:
		kp.SetXYZM(i.Kplus_PX,i.Kplus_PY,i.Kplus_PZ,493.667)
		pim.SetXYZM(i.piminus_PX,i.piminus_PY,i.piminus_PZ,139.570)
		km.SetXYZM(i.Kminus_PX,i.Kminus_PY,i.Kminus_PZ,493.667)
		pip.SetXYZM(i.piplus_PX,i.piplus_PY,i.piplus_PZ,139.570)
		cos1,cos2,phi = get_Angles(kp,pim,km,pip)
		if (i.Kplus_PIDK>2 and i.Kminus_PIDK>2 and i.Kplus_ProbNNk*(1.-i.Kplus_ProbNNpi)>0.3 and i.Kminus_ProbNNk*(1.-i.Kminus_ProbNNpi)>0.3 and i.piplus_PIDK<0 and i.piminus_PIDK<0): weight = 1
		else: weight = 0
		weight_corr = dataMCcorrweight(i)
		if weight==1:
			h_cos1.Fill(cos1)
			h_cos2.Fill(cos2)
			h_phi.Fill(phi)
		h_cos1_corr.Fill(cos1,weight_corr)
		h_cos2_corr.Fill(cos2,weight_corr)
		h_phi_corr.Fill(phi,weight_corr)
		counter += 1

counter = 0
for i in t2c:
	if counter<100000:
		kp.SetXYZM(i.Kplus_PX,i.Kplus_PY,i.Kplus_PZ,493.667)
		pim.SetXYZM(i.piminus_PX,i.piminus_PY,i.piminus_PZ,139.570)
		km.SetXYZM(i.Kminus_PX,i.Kminus_PY,i.Kminus_PZ,493.667)
		pip.SetXYZM(i.piplus_PX,i.piplus_PY,i.piplus_PZ,139.570)
		cos1,cos2,phi = get_Angles(kp,pim,km,pip)
		if (i.Kplus_PIDK>2 and i.Kminus_PIDK>2 and i.Kplus_ProbNNk*(1.-i.Kplus_ProbNNpi)>0.3 and i.Kminus_ProbNNk*(1.-i.Kminus_ProbNNpi)>0.3 and i.piplus_PIDK<0 and i.piminus_PIDK<0): weight = 1
		else: weight = 0
		weight_corr = dataMCcorrweight(i)
		if weight==1:
			h_cos1.Fill(cos1)
			h_cos2.Fill(cos2)
			h_phi.Fill(phi)
		h_cos1_corr.Fill(cos1,weight_corr)
		h_cos2_corr.Fill(cos2,weight_corr)
		h_phi_corr.Fill(phi,weight_corr)
		counter += 1

"""for i in t1c:
	kpeta.afloat = 0.5*log((i.Kplus_P+i.Kplus_PZ)/(i.Kplus_P-i.Kplus_PZ))
	kmeta.afloat = 0.5*log((i.Kminus_P+i.Kminus_PZ)/(i.Kminus_P-i.Kminus_PZ))
	pipeta.afloat = 0.5*log((i.piplus_P+i.piplus_PZ)/(i.piplus_P-i.piplus_PZ))
	pimeta.afloat = 0.5*log((i.piminus_P+i.piminus_PZ)/(i.piminus_P-i.piminus_PZ))
	mkpi1.afloat = i.Kst_M
	mkpi2.afloat = i.Kstb_M
	kp.SetXYZM(i.Kplus_PX,i.Kplus_PY,i.Kplus_PZ,493.667)
	pim.SetXYZM(i.piminus_PX,i.piminus_PY,i.piminus_PZ,139.570)
	km.SetXYZM(i.Kminus_PX,i.Kminus_PY,i.Kminus_PZ,493.667)
	pip.SetXYZM(i.piplus_PX,i.piplus_PY,i.piplus_PZ,139.570)
	angles = get_Angles(kp,pim,km,pip)
	cos1.afloat = angles[0]
	cos2.afloat = angles[1]
	phi.afloat = angles[2]
	tau.afloat = i.B_DTF_TAU*1000.
	year.afloat = -70.
	if (i.Kplus_PIDK>2 and i.Kminus_PIDK>2 and i.Kplus_ProbNNk*(1.-i.Kplus_ProbNNpi)>0.3 and i.Kminus_ProbNNk*(1.-i.Kminus_ProbNNpi)>0.3 and i.piplus_PIDK<0 and i.piminus_PIDK<0): weight.afloat = 1
	else: weight.afloat = 0
	weightcorr.afloat = dataMCcorrweight(i)
	newBranchkpeta.Fill()
	newBranchkmeta.Fill()
	newBranchpipeta.Fill()
	newBranchpimeta.Fill()
	newBranchmkpi1.Fill()
	newBranchmkpi2.Fill()
	newBranchcos1.Fill()
	newBranchcos2.Fill()
	newBranchphi.Fill()
	newBranchtau.Fill()
	newBranchyear.Fill()
	newBranchweight.Fill()
	newBranchweightcorr.Fill()

counter = 0
for i in t2c:
	if counter < 50:
		kpeta.afloat = 0.5*log((i.Kplus_P+i.Kplus_PZ)/(i.Kplus_P-i.Kplus_PZ))
		kmeta.afloat = 0.5*log((i.Kminus_P+i.Kminus_PZ)/(i.Kminus_P-i.Kminus_PZ))
		pipeta.afloat = 0.5*log((i.piplus_P+i.piplus_PZ)/(i.piplus_P-i.piplus_PZ))
		pimeta.afloat = 0.5*log((i.piminus_P+i.piminus_PZ)/(i.piminus_P-i.piminus_PZ))
		mkpi1.afloat = i.Kst_M
		mkpi2.afloat = i.Kstb_M
		kp.SetXYZM(i.Kplus_PX,i.Kplus_PY,i.Kplus_PZ,493.667)
		pim.SetXYZM(i.piminus_PX,i.piminus_PY,i.piminus_PZ,139.570)
		km.SetXYZM(i.Kminus_PX,i.Kminus_PY,i.Kminus_PZ,493.667)
		pip.SetXYZM(i.piplus_PX,i.piplus_PY,i.piplus_PZ,139.570)
		angles = get_Angles(kp,pim,km,pip)
		cos1.afloat = angles[0]
		cos2.afloat = angles[1]
		phi.afloat = angles[2]
		tau.afloat = i.B_DTF_TAU*1000.
		year.afloat = -80.
		if (i.Kplus_PIDK>2 and i.Kminus_PIDK>2 and i.Kplus_ProbNNk*(1.-i.Kplus_ProbNNpi)>0.3 and i.Kminus_ProbNNk*(1.-i.Kminus_ProbNNpi)>0.3 and i.piplus_PIDK<0 and i.piminus_PIDK<0): weight.afloat = 1
		else: weight.afloat = 0
		weightcorr.afloat = dataMCcorrweight(i)
		tout.Fill()
		counter += 1
		newBranchkpeta.Fill()
		newBranchkmeta.Fill()
		newBranchpipeta.Fill()
		newBranchpimeta.Fill()
		newBranchmkpi1.Fill()
		newBranchmkpi2.Fill()
		newBranchcos1.Fill()
		newBranchcos2.Fill()
		newBranchphi.Fill()
		newBranchtau.Fill()
		newBranchyear.Fill()
		newBranchweight.Fill()
		newBranchweightcorr.Fill()"""

print "All events processed."

for i in [h_cos1,h_cos2,h_phi,h_cos1_corr,h_cos2_corr,h_phi_corr]:
	i.Scale(1./i.Integral())

h_cos1_ratio = h_cos1_corr.Clone()
h_cos2_ratio = h_cos2_corr.Clone()
h_phi_ratio = h_phi_corr.Clone()
h_cos1_ratio.Divide(h_cos1)
h_cos2_ratio.Divide(h_cos2)
h_phi_ratio.Divide(h_phi)
h_cos1_ratio.SetTitle("h_cos1_ratio")
h_cos2_ratio.SetTitle("h_cos2_ratio")
h_phi_ratio.SetTitle("h_phi_ratio")

for i in [h_cos1_corr,h_cos2_corr,h_phi_corr]:
	i.SetLineColor(kRed)

c = TCanvas("c","c",1200,800)
c.Divide(3,2)
c.cd(1)
h_cos1.Draw()
h_cos1_corr.Draw("same")
c.cd(2)
h_cos2.Draw()
h_cos2_corr.Draw("same")
c.cd(3)
h_phi.Draw()
h_phi_corr.Draw("same")
c.cd(4)
h_cos1_ratio.Draw()
c.cd(5)
h_cos2_ratio.Draw()
c.cd(6)
h_phi_ratio.Draw()

c.Print("PIDReweight.pdf")
c.Print("PIDReweight.root")

#tout.Write()
#fout.Close()
