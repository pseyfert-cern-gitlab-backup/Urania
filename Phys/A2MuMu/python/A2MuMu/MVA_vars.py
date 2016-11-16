#!/usr/bin/env python

variables_cont = [
              "DOCA",
              #"mu1pt", "mu2pt",
              #"mu1ptot", "mu2ptot",
              "mu1ips", "mu2ips",
              "mu1ip", "mu2ip",
              #"lessIPSmu",
              "mu1_track_Chi2DoF", "mu2_track_Chi2DoF",
              "mu1_probNNmu", "mu2_probNNmu",
              "Bip",
              "C_angle",
              "Blife_ps",
              ]
variables_other = [
              "mu1iso5", "mu2iso5",
              #"SV1", "SV2", "SV3",
              #"mu1_hitsInOT", "mu2_hitsInOT",
              #"mu1_hitsInIT", "mu2_hitsInIT",
              #"mu1_hitsInTT", "mu2_hitsInTT",
              #"mu1_hitsInV", "mu2_hitsInV",
              ]

variables_all = variables_cont + variables_other
variables_rot = []
for i in range(len(variables_cont)-1): variables_rot += ["GLmvas"+str(i) + ".","GLmvan"+str(i) + "."]

variables_BDT = variables_rot + variables_other #For each additional GL variable add GLmvanX. and GLmvasX.
