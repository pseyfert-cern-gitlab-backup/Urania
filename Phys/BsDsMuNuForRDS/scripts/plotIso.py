#!/usr/bin/env python

from ROOT import *

f = TFile('../src/histosNeutralIso.root')
parts = ['Ds','Dsst','Ds0','Ds1','Dspr']
legName = ['D_{s}^{+}','D_{s}^{*+}','D_{s0}(2317)^{+}','D_{s1}(2460)^{+}',"D_{s1}(2536)^{+}"]
leptons = ['Tau','Mu']
radius = ['0.1','0.2','0.3','0.4','0.5']

def getHistos():

    histos = {} 
    for part in parts:
      for lepton in leptons:
        for rad in radius:
          histos[part+lepton+'NeutralMult'+rad] = f.Get(part+lepton+'NeutralMult'+rad)

    return histos

def producePlot(histo,l,kind,r,title):

    ''' Produce regular histograms '''
    c = TCanvas()
    leg = TLegend(0.4,0.75,0.6,0.9)
    for part in parts:
      for lepton in leptons:
        if l == lepton:
          for rad in radius:
            if r == rad:
              if histo[part+l+kind+r].GetEntries() > 0:
                histo[part+l+kind+r].GetXaxis().SetTitle(title)
                histo[part+l+kind+r].SetLineColor(parts.index(part)+1)
                histo[part+l+kind+r].SetLineWidth(2)
                histo[part+l+kind+r].DrawNormalized('same')
                leg.AddEntry(histo[part+l+kind+r],legName[parts.index(part)],'l')
                leg.Draw()
    c.SaveAs('../plots/'+kind+l+r+'.pdf')

def produceStack(histo,l,kind,r,title):
  ''' Produce stack plots '''
  c = TCanvas()
  leg = TLegend(0.4,0.75,0.6,0.9)
  hs = THStack()
  for part in parts:
    for lepton in leptons:
      if l == lepton:
        for rad in radius:
          if r == rad:
            if histo[part+l+kind+r].GetEntries() > 0:
              histo[part+l+kind+r].SetFillColor(parts.index(part)+1)
              histo[part+l+kind+r].SetLineColor(parts.index(part)+1)
              hs.Add(histo[part+l+kind+r])
              hs.Draw()
              hs.GetXaxis().SetTitle(title)
              leg.AddEntry(histo[part+l+kind+r],legName[parts.index(part)],'f')
              leg.Draw()
  c.SaveAs('../plots/'+kind+l+r+'_stack.pdf')


histo = getHistos()
for lept in leptons:
  for rad in radius:
    producePlot(histo,lept,'NeutralMult',rad,'Neutral multiplicity')
    produceStack(histo,lept,'NeutralMult',rad,'Neutral multiplicity')
