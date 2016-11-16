#!/usr/bin/env python
from Urania import PDG

mdau = PDG.piplus.mass
MqqMax = 490.
mdau2 = str(mdau**2)
MqqMax2 = str(MqqMax**2)

variables_cont = ["DOCA", "mu1ips", "mu2ips", "Phi", "cTh1","cTh2","K_dec_angle", "KSips", "KS_pt", "pi0mass", "Xi", "mu1_probNNmu", "mu2_probNNmu", "Vchi2", "KS_IP","KSdissig","mu1_track_Chi2DoF","mu2_track_Chi2DoF"]#, "ProbNNghost1", "ProbNNghost2", "mu1GP", "mu2GP"]
variables_other = [ "mu1_hitsInOT", "mu2_hitsInOT", "mu1_hitsInIT", "mu2_hitsInIT", "mu1_hitsInTT", "mu2_hitsInTT", "mu1_hitsInV", "mu2_hitsInV", "SV1", "SV2", "SV3"]

variables_all = variables_cont + variables_other
variables_rot = []
for i in range(len(variables_cont)): variables_rot += ["GLmvas"+str(i) + ".","GLmvan"+str(i) + "."]

variables_BDT = variables_rot + variables_other #For each additional GL variable add GLmvanX. and GLmvasX.


mycutBkg = "(mu1_hitsInTT > 0.1) && (mu2_hitsInTT > 0.1) && (LF_time > 1) && ((2*" + mdau2 +" + 2*sqrt(" + mdau2 +" +mu1p1*mu1p1+mu1p2*mu1p2+mu1p3*mu1p3)*sqrt(" + mdau2 + "+mu2p1*mu2p1+mu2p2*mu2p2+mu2p3*mu2p3)- 2*(mu1p1*mu2p1+mu1p2*mu2p2+mu1p3*mu2p3)) < " + MqqMax2 + ")"

mycutSig = mycutBkg#+ "&& (mo1 == 310) && (mo2 == 310) && (mc_gamma_ez > 0) && (mc_Gamma_ez > 0)"

