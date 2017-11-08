#!/usr/bin/env python

from ROOT import *
from P_DstarKinematic import *

def P_Plot2BodyDecay(M, m1, m2):
  twoPlot = TCanvas("twoPlot","2Body Kinematic",0,0,400,400)
  twoPlot.cd()

  momentum  = P_2bodykinematic(M,m1,m2)
  TOT = TGraph(2)
  TOT.SetPoint(0,-1*momentum,-1*momentum)
  TOT.SetPoint(1, 1*momentum, 1*momentum)
  TOT.SetLineColor(0)
  TOT.Draw("AL")

  TOTL = TGraph(2)
  TOTL.SetPoint(0, 0, 0)  
  TOTL.SetPoint(1, -1*momentum, 0)
  TOTL.Draw("Lsame")

  TOTR = TGraph(2)
  TOTR.SetPoint(0, 0, 0)
  TOTR.SetPoint(1, +1*momentum, 0)
  TOTR.Draw("Lsame")

  M0 = TMarker(0, 0, 20)           
  M0.SetMarkerColor(kBlack)   
  M0.Draw("")
  ML = TMarker(-1*momentum, 0, 20)
  ML.SetMarkerColor(kGreen)
  ML.Draw("")
  MR = TMarker( 1*momentum, 0, 20) 
  MR.SetMarkerColor(kBlue)    
  MR.Draw("")

  twoPlot.Update()
  return twoPlot

def P_Plot2BodyDecayAngle(M, m1, m2, ANGLE):
  twoPlot2 = TCanvas("twoPlot2","2Body Kinematic",400,0,400,400)
  twoPlot2.cd()

  momentum = P_2bodykinematic(M,m1,m2)
  sinANGLE = sin(ANGLE)
  cosANGLE = cos(ANGLE)

  TOT2 = TGraph(2)
  TOT2.SetPoint(0,-1*momentum,-1*momentum)
  TOT2.SetPoint(1, 1*momentum, 1*momentum)
  TOT2.SetLineColor(0)
  TOT2.Draw("AL")

  TOT2h = TGraph(2)
  TOT2h.SetPoint(0,-1*momentum, 0)
  TOT2h.SetPoint(1, 1*momentum, 0)
  TOT2h.SetLineColor(1)
  TOT2h.Draw("Lsame")

  TOTL2 = TGraph(2)
  TOTL2.SetPoint(0, 0, 0)
  TOTL2.SetPoint(1, -cosANGLE*momentum, -sinANGLE*momentum)
  TOTL2.Draw("Lsame")

  TOTR2 = TGraph(2)
  TOTR2.SetPoint(0, 0, 0)
  TOTR2.SetPoint(1, +cosANGLE*momentum, +sinANGLE*momentum)
  TOTR2.Draw("Lsame")

  M02 = TMarker(0, 0, 20)
  M02.SetMarkerColor(kGreen) 
  M02.Draw("")
  ML2 = TMarker(-cosANGLE*momentum, -sinANGLE*momentum, 20) 
  ML2.SetMarkerColor(kRed)
  ML2.Draw("")
  MR2 = TMarker(+cosANGLE*momentum, +sinANGLE*momentum, 20) 
  MR2.SetMarkerColor(kGray)   
  MR2.Draw("")

  twoPlot2.Update()
  return twoPlot2
  
def P_Plot3BodyDecayBoosted(M, m1, m2, ANGLE, D0, Neutral):

  twoPlot3 = TCanvas("twoPlot3","3Body Kinematic",800,0,400,400)
  twoPlot3.cd()
  
  momentum1 = P_2bodykinematic(M,m1,m2)
  momentum2 = P_2bodykinematic(m1,D0,Neutral)
  Neutral_L = Plongitudinalprime( P_2bodykinematicL(m1,D0,Neutral,ANGLE), P_2bodykinematicT(m1,D0,Neutral,ANGLE), Neutral, momentum1, m1)
  Neutral_T = P_2bodykinematicT(m1,D0,Neutral,ANGLE)
  D0_L      = Plongitudinalprime(-P_2bodykinematicL(m1,D0,Neutral,ANGLE),-P_2bodykinematicT(m1,D0,Neutral,ANGLE), D0, momentum1, m1)
  D0_T      =-P_2bodykinematicT(m1,D0,Neutral,ANGLE)
  
  TOT3Body = TGraph(2)
  TOT3Body.SetPoint(0,  momentum1,  momentum2)
  TOT3Body.SetPoint(1, -momentum1, -momentum2)
  TOT3Body.SetLineColor(0)
  TOT3Body.Draw("AL")
  
  TOTRt = TGraph(2)
  TOTRt.SetPoint(0, 0, 0)
  TOTRt.SetPoint(1, momentum1, 0)
  TOTRt.Draw("Lsame")
  
  TOTneutral = TGraph(2)
  TOTneutral.SetPoint(0, 0, 0)
  TOTneutral.SetPoint(1, Neutral_L, Neutral_T)
  TOTneutral.Draw("Lsame")
  
  TOTD0 = TGraph(2)
  TOTD0.SetPoint(0, 0, 0)
  TOTD0.SetPoint(1, D0_L, D0_T)
  TOTD0.Draw("Lsame")
  
  M02 = TMarker(0, 0, 20)
  M02.SetMarkerColor(kBlack) 
  M02.Draw("")
  Mleft = TMarker(momentum1, 0, 20) 
  Mleft.SetMarkerColor(kBlue) 
  Mleft.Draw("")
  Mneut = TMarker(Neutral_L, Neutral_T, 20)
  Mneut.SetMarkerColor(kGray) 
  Mneut.Draw("")
  MD0   = TMarker(D0_L, D0_T, 20)
  MD0.SetMarkerColor(kRed)
  MD0.Draw("")
  
  twoPlot3.Update()
  return twoPlot3

