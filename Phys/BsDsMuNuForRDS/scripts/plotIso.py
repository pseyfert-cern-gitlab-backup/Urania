#!/usr/bin/env python

from ROOT import *

f = TFile('../src/histosNeutralIso_Sim08a.root')
#parts = ['Ds','Dsst','Ds0','Ds1','Dspr']
#parts = ['Ds','Dsst','Ds0']
parts = ['Ds','Dsst']
#legName = ['D_{s}^{+}','D_{s}^{*+}','D_{s0}(2317)^{+}','D_{s1}(2460)^{+}',"D_{s1}(2536)^{+}"]
legName = ['D_{s}^{+}','D_{s}^{*+}']
#legName = ['D_{s}^{+}','D_{s}^{*+}','D_{s0}(2317)^{+}']
leptons = ['Tau','Mu']
#radius = ['15','12','09','06','03']
radius = ['06','03']

def getHistos():

    histos = {} 
    for part in parts:
      for lepton in leptons:
        histos[part+lepton+'MaxCone'] = f.Get(part+lepton+'MaxCone')
        for rad in radius:
          histos[part+lepton+'NeutralMult'+rad] = f.Get(part+lepton+'NeutralMult'+rad)
          histos[part+lepton+'PCone'+rad] = f.Get(part+lepton+'PCone'+rad)
          histos[part+lepton+'Asym'+rad] = f.Get(part+lepton+'Asym'+rad)
          histos[part+lepton+'MassWithG'+rad] = f.Get(part+lepton+'MassWithG'+rad)
          histos[part+lepton+'MaxPtP'+rad] = f.Get(part+lepton+'MaxPtP'+rad)
          histos[part+lepton+'RightPtP'+rad] = f.Get(part+lepton+'RightPtP'+rad)
          histos[part+lepton+'MaxPtPt'+rad] = f.Get(part+lepton+'MaxPtPt'+rad)
          histos[part+lepton+'RightPtPt'+rad] = f.Get(part+lepton+'RightPtPt'+rad)

    return histos

def producePlot(histo,l,kind,title,r=''):

    ''' Produce regular histograms '''
    c = TCanvas()
    leg = TLegend(0.4,0.75,0.6,0.9)
    for part in parts:
      for lepton in leptons:
        if l == lepton:
          if r == '':
            if histo[part+l+kind].GetEntries() > 0:
              histo[part+l+kind].GetXaxis().SetTitle(title)
              histo[part+l+kind].SetLineColor(parts.index(part)+1)
              histo[part+l+kind].SetLineWidth(2)
              histo[part+l+kind].DrawNormalized('same')
              leg.AddEntry(histo[part+l+kind],legName[parts.index(part)],'l')
              leg.Draw()
          else:
            if histo[part+l+kind+r].GetEntries() > 0:
              for rad in radius:
                if r == rad:
                  histo[part+l+kind+r].GetXaxis().SetTitle(title)
                  histo[part+l+kind+r].SetLineColor(parts.index(part)+1)
                  histo[part+l+kind+r].SetLineWidth(2)
                  histo[part+l+kind+r].DrawNormalized('same')
                  leg.AddEntry(histo[part+l+kind+r],legName[parts.index(part)],'l')
                  leg.Draw()
    c.SaveAs('../plots/'+kind+l+r+'.pdf')
    c.SaveAs('../plots/'+kind+l+r+'.png')

def produceStack(histo,l,kind,title,r=''):
  ''' Produce stack plots '''
  c = TCanvas()
  leg = TLegend(0.4,0.75,0.6,0.9)
  hs = THStack()
  for part in parts:
    for lepton in leptons:
      if l == lepton:
        if r == '':
          if histo[part+l+kind].GetEntries() > 0:
            histo[part+l+kind].SetFillColor(parts.index(part)+1)
            histo[part+l+kind].SetLineColor(parts.index(part)+1)
            hs.Add(histo[part+l+kind])
            hs.Draw()
            hs.GetXaxis().SetTitle(title)
            leg.AddEntry(histo[part+l+kind],legName[parts.index(part)],'f')
            leg.Draw()
        else:
          if histo[part+l+kind+r].GetEntries() > 0:
            for rad in radius:
              if r == rad:
                histo[part+l+kind+r].SetFillColor(parts.index(part)+1)
                histo[part+l+kind+r].SetLineColor(parts.index(part)+1)
                hs.Add(histo[part+l+kind+r])
                hs.Draw()
                hs.GetXaxis().SetTitle(title)
                leg.AddEntry(histo[part+l+kind+r],legName[parts.index(part)],'f')
                leg.Draw()
  c.SaveAs('../plots/'+kind+l+r+'_stack.pdf')
  c.SaveAs('../plots/'+kind+l+r+'_stack.png')

histo = getHistos()
for lept in leptons:
  #producePlot(histo,lept,'MaxCone','Maximum radius of cone')
  #produceStack(histo,lept,'MaxCone','Maximum radius of cone')
  for rad in radius:
    #producePlot(histo,lept,'MassWithG','Mass of Ds + photon (MeV)',rad)
    producePlot(histo,lept,'MaxPtP','Energy of the maximum pT photon in the cone (MeV)',rad)
    producePlot(histo,lept,'RightPtP','Energy of the photon that makes the Ds*',rad)
    producePlot(histo,lept,'MaxPtPt','ET of the maximum pT photon in the cone (MeV)',rad)
    producePlot(histo,lept,'RightPtPt','ET of the photon that makes the Ds*',rad)
    #producePlot(histo,lept,'PCone','Momentum of the cone (MeV)',rad)
    #producePlot(histo,lept,'Asym','Momentum asymmetry of the cone',rad)
    #produceStack(histo,lept,'PCone','Momentum of the cone (MeV)',rad)
    #producePlot(histo,lept,'NeutralMult','Neutral multiplicity',rad)
#    produceStack(histo,lept,'NeutralMult','Neutral multiplicity',rad)
