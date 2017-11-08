#!/usr/bin/env python
from ROOT import *
from math import *

def P_2bodykinematic(M, m1, m2):
  return pow( ( (pow(M,2)-pow((m1+m2),2) )*(pow(M,2)-pow((m1-m2),2))),0.5)/(2*M)

def P_2bodykinematicL(M, m1, m2, ANGLE):
  return pow( ( (pow(M,2)-pow((m1+m2),2) )*(pow(M,2)-pow((m1-m2),2))),0.5)/(2*M) * cos(ANGLE)

def P_2bodykinematicT(M, m1, m2, ANGLE):
  return pow( ( (pow(M,2)-pow((m1+m2),2) )*(pow(M,2)-pow((m1-m2),2))),0.5)/(2*M) * sin(ANGLE)

def E_kinematic(p, m):
  return pow(pow(m,2)+pow(p,2),0.5);

def MissingMass(B, N, Pneutral):
  return pow( ( pow((B - pow(pow(N,2)+pow(Pneutral,2),0.5)),2) - pow(Pneutral,2)),0.5)

def Plongitudinalprime(MOMlongitudinal, MOMtransversal, mass, p_1RF, DSTAR):
  #*********************************************************************************************************
  #The particle I am boosting is identified with (MOMlongitudinal,mass) -> like the neutral (secodary decay)
  #The boost is identified with a beta from (p_1RF,DSTAR)
  #**********************************************************************************************************/

  gamma = E_kinematic(p_1RF,DSTAR)/DSTAR
  beta  = pow((1-pow(gamma,-2)),0.5)

  return gamma*(MOMlongitudinal - beta*pow(pow(mass,2)+pow(MOMlongitudinal,2)+pow(MOMtransversal,2),0.5))

def Plongitudinalprimeprime(MOMlongitudinal, MOMtransversal, mass, p_1RF, DSTAR):
  #********************************************************************************************************
  #The particle I am boosting is identified with (MOMlongitudinal,mass) -> like the neutral (secodary decay)
  #The boost is identified with a beta from (p_1RF,DSTAR)
  #**********************************************************************************************************/

  gamma = E_kinematic(p_1RF,DSTAR)/DSTAR
  beta  = pow((1-pow(gamma,-2)),0.5)
  beta = -beta

  return gamma*(MOMlongitudinal - beta*pow(pow(mass,2)+pow(MOMlongitudinal,2)+pow(MOMtransversal,2),0.5))
