from SomeUtils.NewKarlen import *
from Bs2MuMu.triggerclass import *
from ROOT import *
from math import *
from PDF_builder_self_v2_MCTruth import *


filename = "Bs2KstKst_Real2011_strip17_MC11a_cuts_v4r2_GL_2012_pi"# filename = "Bs2KstKst_MC11a_ISOr1_cuts_GL_2012_pi"

cuts_tos = " (L0Tos) & (Hlt1Tos) & (Hlt2Tos)"
cuts_notos =  " !((L0Tos) & (Hlt1Tos) & (Hlt2Tos))"# & P12_pt>1500 && P22_pt>1500"



fout = TFile(filename+"_cuts_weighted.root")
tout = fout.Get("T")

nbins = 10


ftrash = TFile("trash.root","recreate")
tout_tos = tout.CopyTree(cuts_tos)
tout_notos = tout.CopyTree(cuts_notos)



hc1acc_tos = TH1F("hc1acc_tos","hc1acc_tos",nbins,-1.,1.)
hc2acc_tos = TH1F("hc2acc_tos","hc2acc_tos",nbins,-1.,1.)
hphacc_tos = TH1F("hphacc_tos","hphacc_tos",nbins,-pi,pi)
hm1acc_tos = TH1F("hm1acc_tos","hm1acc_tos",nbins,896-150,896+150)
hm2acc_tos = TH1F("hm2acc_tos","hm2acc_tos",nbins,896-150,896+150)

# hc1acc_tos.Sumw2()
# hc2acc_tos.Sumw2()
# hphacc_tos.Sumw2()
# hm1acc_tos.Sumw2()
# hm2acc_tos.Sumw2()


hc1acc_notos = TH1F("hc1acc_notos","hc1acc_notos",nbins-2,-1.,1.)
hc2acc_notos = TH1F("hc2acc_notos","hc2acc_notos",nbins -2,-1.,1.)
hphacc_notos = TH1F("hphacc_notos","hphacc_notos",nbins -2,-pi,pi)
hm1acc_notos = TH1F("hm1acc_notos","hm1acc_notos",nbins -2,896-150,896+150)
hm2acc_notos = TH1F("hm2acc_notos","hm2acc_notos",nbins -2,896-150,896+150)

hc1acc_notos.Sumw2()
hc2acc_notos.Sumw2()
hphacc_notos.Sumw2()
hm1acc_notos.Sumw2()
hm2acc_notos.Sumw2()

cv1 = TCanvas()
cv1.Divide(3,2)
cv1.cd(1)
tout_tos.Draw("CosTheta1>>hc1acc_tos","weight")
cv1.cd(2)
tout_tos.Draw("CosTheta2>>hc2acc_tos","weight")
cv1.cd(3)
tout_tos.Draw("Phi>>hphacc_tos","weight")
cv1.cd(4)
tout_tos.Draw("P1_mass>>hm1acc_tos","weight")
cv1.cd(5)
tout_tos.Draw("P2_mass>>hm2acc_tos","weight")


hc1acc_tos.Scale(1./(hc1acc_tos.GetSum()*0.1))
hc2acc_tos.Scale(1./(hc2acc_tos.GetSum()*0.1))
hphacc_tos.Scale(1./(hphacc_tos.GetSum()*0.1))
hm1acc_tos.Scale(1./(hm1acc_tos.GetSum()*0.1))
hm2acc_tos.Scale(1./(hm2acc_tos.GetSum()*0.1))


cv2 = TCanvas()
cv2.Divide(3,2)
cv2.cd(1)
tout_notos.Draw("CosTheta1>>hc1acc_notos","weight")
cv2.cd(2)
tout_notos.Draw("CosTheta2>>hc2acc_notos","weight")
cv2.cd(3)
tout_notos.Draw("Phi>>hphacc_notos","weight")
cv2.cd(4)
tout_notos.Draw("P1_mass>>hm1acc_notos","weight")
cv2.cd(5)
tout_notos.Draw("P2_mass>>hm2acc_notos","weight")


hc1acc_notos.Scale(1./(hc1acc_notos.GetSum()*0.1))
hc2acc_notos.Scale(1./(hc2acc_notos.GetSum()*0.1))
hphacc_notos.Scale(1./(hphacc_notos.GetSum()*0.1))
hm1acc_notos.Scale(1./(hm1acc_notos.GetSum()*0.1))
hm2acc_notos.Scale(1./(hm2acc_notos.GetSum()*0.1))


# for i in range(nbins):
#     hc1acc.SetBinError(i+1,hc1acc.GetBinContent(i+1)*rel_errs["c1"][i])
#     hc2acc.SetBinError(i+1,hc2acc.GetBinContent(i+1)*rel_errs["c2"][i])
#     hphacc.SetBinError(i+1,hphacc.GetBinContent(i+1)*rel_errs["ph"][i])
#     hm1acc.SetBinError(i+1,hm1acc.GetBinContent(i+1)*rel_errs["m1"][i])
#     hm2acc.SetBinError(i+1,hm2acc.GetBinContent(i+1)*rel_errs["m2"][i])


hc1acc_tos.GetYaxis().SetRangeUser(0.,2.)
hc2acc_tos.GetYaxis().SetRangeUser(0.,2.)
hphacc_tos.GetYaxis().SetRangeUser(0.,2.)
hm1acc_tos.GetYaxis().SetRangeUser(0.,2.)
hm2acc_tos.GetYaxis().SetRangeUser(0.,2.)

hc1acc_notos.GetYaxis().SetRangeUser(0.,2.)
hc2acc_notos.GetYaxis().SetRangeUser(0.,2.)
hphacc_notos.GetYaxis().SetRangeUser(0.,2.)
hm1acc_notos.GetYaxis().SetRangeUser(0.,2.)
hm2acc_notos.GetYaxis().SetRangeUser(0.,2.)

cv1.cd(1)
hc1acc_tos.Draw()
cv1.cd(2)
hc2acc_tos.Draw()
cv1.cd(3)
hphacc_tos.Draw()
cv1.cd(4)
hm1acc_tos.Draw()
cv1.cd(5)
hm2acc_tos.Draw()

cv2.cd(1)
hc1acc_notos.Draw()
cv2.cd(2)
hc2acc_notos.Draw()
cv2.cd(3)
hphacc_notos.Draw()
cv2.cd(4)
hm1acc_notos.Draw()
cv2.cd(5)
hm2acc_notos.Draw()

# foutacc = TFile("acceptances_from_MC_TISTOS.root","recreate")
# hc1acc_tos.Write()
# hc2acc_tos.Write()
# hphacc_tos.Write()
# hm1acc_tos.Write()
# hm2acc_tos.Write()
# hc1acc_notos.Write()
# hc2acc_notos.Write()
# hphacc_notos.Write()
# hm1acc_notos.Write()
# hm2acc_notos.Write()
# foutacc.Save()
# foutacc.Close()





