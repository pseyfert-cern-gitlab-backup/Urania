#!/usr/bin/env python

from ROOT import *
from P_DstarKinematic import *
from P_VectorPlot  import *
from math import *

BuPDG=5279.15
BdPDG=5279.58
BsPDG=5366.89
D0PDG=1864.84
DSPDG=1968.28
RHO0=775.49
KSTAR0=895.94
RHOplus=775.11
KSTARplus=891.66
DSTAR0=2006.98
DSTARplus=2010.28
PiPDG=139.57018
P0PDG=134.9766
KPDG= 493.677
#Switch the IDs and treat the D* like the K*, and the bach like the D0
B=BsPDG
Dstar=RHOplus
bach=DSPDG
neutral=P0PDG
ANGLE= 60./180*pi
print "---------------------"
print "B     = ", B
print "Dstar = ", Dstar
print "bach  = ", bach
print "p_1RF = ", P_2bodykinematic(B,Dstar,bach)
print"---------------------"
print"ANGLE   = ", ANGLE
print"-----"
print"Dstar   = ", KSTAR0
print"D0PDG   = ", KPDG
print"neutral = ", neutral
print"p_2RF      = ", P_2bodykinematic(Dstar,KPDG,neutral)
print"p_2RF_long = ", P_2bodykinematicL(Dstar,KPDG,neutral,ANGLE)
print"p_2RF_tran = ", P_2bodykinematicT(Dstar,KPDG,neutral,ANGLE)
print"---------------------"

t=0
nstep=0
maximum = 360./180*pi
step = 0.01
#for (ANGLE = 0.; ANGLE < maximum; ANGLE = ANGLE + step):
#  nstep++;
nstep = 10000
GraphPNeutral = TGraph(nstep);
GraphPNeutral_Cos = TGraph(nstep);
GraphMissingMass  = TGraph(nstep);
GraphMissingMass_Cos = TGraph(nstep);

ANGLE = 0.
for i in range(nstep):
#for(ANGLE = 0.; ANGLE < maximum; ANGLE = ANGLE + step):
  step = maximum/nstep 
  ANGLE = i*step
  Neutral_L = Plongitudinalprime( P_2bodykinematicL(Dstar,PiPDG,neutral,ANGLE), P_2bodykinematicT(Dstar,PiPDG,neutral,ANGLE), neutral, P_2bodykinematic(B,Dstar,bach), Dstar)
  Neutral_T = P_2bodykinematicT(Dstar,PiPDG,neutral,ANGLE)
  D0_L      = Plongitudinalprime(-P_2bodykinematicL(Dstar,PiPDG,neutral,ANGLE),-P_2bodykinematicT(Dstar,PiPDG,neutral,ANGLE), PiPDG, P_2bodykinematic(B,Dstar,bach), Dstar)
  D0_T      =-P_2bodykinematicT(Dstar,PiPDG,neutral,ANGLE)

  #cout<<"Sum of Longitudinal components = "<<Neutral_L+D0_L+P_2bodykinematic(B,Dstar,bach)<<endl;
  value_PNeutral = pow( pow(Neutral_L,2) + pow(Neutral_T,2) , 0.5)
  MMass    = MissingMass(B, neutral, value_PNeutral)
  GraphPNeutral.SetPoint(t, ANGLE, value_PNeutral)
  GraphPNeutral_Cos.SetPoint(t, cos(ANGLE), value_PNeutral)
  GraphMissingMass.SetPoint(t, ANGLE, MMass)
  GraphMissingMass_Cos.SetPoint(t, cos(ANGLE), MMass)
  t+=1

GraphPNeutral.GetYaxis().SetTitle("Momentum of Neutral (MeV)")
GraphPNeutral.GetXaxis().SetTitle("#theta Angle")
GraphPNeutral.SetTitle("")
GraphPNeutral_Cos.GetYaxis().SetTitle("Momentum of Neutral (MeV)")
GraphPNeutral_Cos.GetXaxis().SetTitle("Cos(#theta) Angle")
GraphPNeutral_Cos.SetTitle("")
GraphMissingMass.GetYaxis().SetTitle("Reconstructed Invariant Mass (MeV)")
GraphMissingMass.GetXaxis().SetTitle("#theta Angle")
GraphMissingMass.SetTitle("")
GraphMissingMass_Cos.GetYaxis().SetTitle("Reconstructed Invariant Mass  (MeV)")
GraphMissingMass_Cos.GetXaxis().SetTitle("Cos(#theta) Angle")
GraphMissingMass_Cos.SetTitle("")

g = TCanvas("g","g",0,0,1000,500)
g.Divide(2)

g.cd(1)  
GraphPNeutral.Draw("ALp")
g.cd(2)  
GraphPNeutral_Cos.Draw("ALp")

g2 = TCanvas("g2","g2",0,0,1000,500)
g2.Divide(2)

g2.cd(1)  
GraphMissingMass.Draw("ALp")
g2.cd(2)  
GraphMissingMass_Cos.Draw("ALp")

ANGLE = 0.
Neutral_L = Plongitudinalprime( P_2bodykinematicL(Dstar,PiPDG,neutral,ANGLE), P_2bodykinematicT(Dstar,PiPDG,neutral,ANGLE), neutral, P_2bodykinematic(B,Dstar,bach), Dstar)
Neutral_T = P_2bodykinematicT(Dstar,PiPDG,neutral,ANGLE)
D0_L      = Plongitudinalprime(-P_2bodykinematicL(Dstar,PiPDG,neutral,ANGLE),-P_2bodykinematicT(Dstar,PiPDG,neutral,ANGLE), PiPDG, P_2bodykinematic(B,Dstar,bach), Dstar)
D0_T      =-P_2bodykinematicT(Dstar,PiPDG,neutral,ANGLE)
value_PNeutral = pow( pow(Neutral_L,2) + pow(Neutral_T,2) , 0.5)
MMass    = MissingMass(B, neutral, value_PNeutral)
print "Max = ", MMass

ANGLE = pi
Neutral_L = Plongitudinalprime( P_2bodykinematicL(Dstar,PiPDG,neutral,ANGLE), P_2bodykinematicT(Dstar,PiPDG,neutral,ANGLE), neutral, P_2bodykinematic(B,Dstar,bach), Dstar)
Neutral_T = P_2bodykinematicT(Dstar,PiPDG,neutral,ANGLE)
D0_L      = Plongitudinalprime(-P_2bodykinematicL(Dstar,PiPDG,neutral,ANGLE),-P_2bodykinematicT(Dstar,PiPDG,neutral,ANGLE), PiPDG, P_2bodykinematic(B,Dstar,bach), Dstar)
D0_T      =-P_2bodykinematicT(Dstar,PiPDG,neutral,ANGLE)
value_PNeutral = pow( pow(Neutral_L,2) + pow(Neutral_T,2) , 0.5)
MMass    = MissingMass(B, neutral, value_PNeutral)
print "Min = ", MMass
