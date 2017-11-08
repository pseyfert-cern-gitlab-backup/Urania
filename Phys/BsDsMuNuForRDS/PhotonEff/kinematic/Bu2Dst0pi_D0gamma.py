#!/usr/bin/env python

from ROOT import *
from math import *
from P_DstarKinematic import *
from P_VectorPlot  import *


BuPDG=5279.15
BdPDG=5279.58
BsPDG=5366.89
D0PDG=1864.84
DSTAR0=2006.98
DSTARplus=2010.28
DSPDG=1968.28
DSSTAR=2112.1
PiPDG=139.57018
P0PDG=134.9766
KPDG= 493.677
B=BsPDG
Dstar=DSSTAR
D0=DSPDG
bach=PiPDG
neutral=P0PDG

t=0
nstep=0;
maximum = 360./180*pi
nstep = 10000
GraphPNeutral = TGraph(nstep);
GraphPNeutral_Cos = TGraph(nstep);
GraphMissingMass  = TGraph(nstep);
GraphMissingMass_Cos = TGraph(nstep);

for i in range(nstep):

  step = maximum/nstep
  ANGLE = i*step
  Neutral_L = Plongitudinalprime( P_2bodykinematicL(Dstar,D0,neutral,ANGLE), P_2bodykinematicT(Dstar,D0,neutral,ANGLE), neutral, P_2bodykinematic(B,Dstar,bach), Dstar)
  Neutral_T = P_2bodykinematicT(Dstar,D0,neutral,ANGLE)
  D0_L      = Plongitudinalprime(-P_2bodykinematicL(Dstar,D0,neutral,ANGLE),-P_2bodykinematicT(Dstar,D0,neutral,ANGLE), D0, P_2bodykinematic(B,Dstar,bach), Dstar)
  D0_T      =-P_2bodykinematicT(Dstar,D0,neutral,ANGLE)

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
Neutral_L = Plongitudinalprime( P_2bodykinematicL(Dstar,D0,neutral,ANGLE), P_2bodykinematicT(Dstar,D0,neutral,ANGLE), neutral, P_2bodykinematic(B,Dstar,bach), Dstar)
Neutral_T = P_2bodykinematicT(Dstar,D0,neutral,ANGLE)
D0_L      = Plongitudinalprime(-P_2bodykinematicL(Dstar,D0,neutral,ANGLE),-P_2bodykinematicT(Dstar,D0,neutral,ANGLE), D0, P_2bodykinematic(B,Dstar,bach), Dstar)
D0_T      =-P_2bodykinematicT(Dstar,D0,neutral,ANGLE)
value_PNeutral = pow( pow(Neutral_L,2) + pow(Neutral_T,2) , 0.5)
MMass    = MissingMass(B, neutral, value_PNeutral)
print "Max = ", MMass

ANGLE = pi
Neutral_L = Plongitudinalprime( P_2bodykinematicL(Dstar,D0,neutral,ANGLE), P_2bodykinematicT(Dstar,D0,neutral,ANGLE), neutral, P_2bodykinematic(B,Dstar,bach), Dstar)
Neutral_T = P_2bodykinematicT(Dstar,D0,neutral,ANGLE)
D0_L      = Plongitudinalprime(-P_2bodykinematicL(Dstar,D0,neutral,ANGLE),-P_2bodykinematicT(Dstar,D0,neutral,ANGLE), D0, P_2bodykinematic(B,Dstar,bach), Dstar)
D0_T      =-P_2bodykinematicT(Dstar,D0,neutral,ANGLE)
value_PNeutral = pow( pow(Neutral_L,2) + pow(Neutral_T,2) , 0.5)
MMass    = MissingMass(B, neutral, value_PNeutral)
print "Min = ", MMass

