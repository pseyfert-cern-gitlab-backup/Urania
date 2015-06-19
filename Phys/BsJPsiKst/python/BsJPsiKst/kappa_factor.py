from Urania.SymP2VVTrans import *

c1_psi = Symbol("c1_psi")
c2_psi = Symbol("c2_psi")
c3_psi = Symbol("c3_psi")
c4_psi = Symbol("c4_psi")
c5_psi = Symbol("c5_psi")

c1_phi = Symbol("c1_phi")
c2_phi = Symbol("c2_phi")
c3_phi = Symbol("c3_phi")

c2_theta = Symbol("c2_theta")

acc_psi = 1. + c1_psi*CPsi + c2_psi*CPsi2 + c3_psi*CPsi2*CPsi + c4_psi*CPsi2*CPsi2 + c5_psi*CPsi2*CPsi2*CPsi;
acc_theta = 1. +  c2_theta*CTheta2;
acc_phi = 1. + c1_phi*cos( c2_phi*Phi + c3_phi)#+c4_phi*cos(c5_phi*Phi + c6_phi);

Acc = acc_psi*acc_theta*acc_phi

