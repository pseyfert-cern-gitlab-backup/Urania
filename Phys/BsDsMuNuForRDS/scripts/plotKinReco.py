#!/usr/bin/env python

from ROOT import *

f = TFile('../src/histosKinReco.root')
parts = ['Ds','Dsst','Ds0','Ds1','Dspr']
legName = ['D_{s}^{+}','D_{s}^{*+}','D_{s0}(2317)^{+}','D_{s1}(2460)^{+}',"D_{s1}(2536)^{+}"]
leptons = ['Tau','Mu']

def getHistos():

    histos = {} 
    for part in parts:
      for lepton in leptons:
        histos[part+lepton+'CorrMass'] = f.Get(part+lepton+'CorrMass')
        histos[part+lepton+'CorrMassErr'] = f.Get(part+lepton+'CorrMassErr')
        histos[part+lepton+'BP'] = f.Get(part+lepton+'BP')
        histos[part+lepton+'BPT'] = f.Get(part+lepton+'BPT')
        histos[part+lepton+'VChi2'] = f.Get(part+lepton+'VChi2')
        histos[part+lepton+'DsVChi2'] = f.Get(part+lepton+'DsVChi2')
        histos[part+lepton+'DOCA'] = f.Get(part+lepton+'DOCA')
        histos[part+lepton+'DsMass'] = f.Get(part+lepton+'DsMass')        
        histos[part+lepton+'DIRA'] = f.Get(part+lepton+'DIRA')
        histos[part+lepton+'FD'] = f.Get(part+lepton+'FD')
        histos[part+lepton+'IP'] = f.Get(part+lepton+'IP')
        histos[part+lepton+'MuP'] = f.Get(part+lepton+'MuP')
        histos[part+lepton+'MuPT'] = f.Get(part+lepton+'MuPT')
        histos[part+lepton+'DsP'] = f.Get(part+lepton+'DsP')
        histos[part+lepton+'DsPT'] = f.Get(part+lepton+'DsPT') 

    return histos

def producePlot(histo,l,kind,title):

    ''' Produce regular histograms '''
    c = TCanvas()
    leg = TLegend(0.1,0.75,0.3,0.9)
    for part in parts:
      for lepton in leptons:
        if l == lepton:
          print part+l+kind
          if histo[part+l+kind].GetEntries() > 0:
            histo[part+l+kind].GetXaxis().SetTitle(title)
            histo[part+l+kind].SetLineColor(parts.index(part)+1)
            histo[part+l+kind].SetLineWidth(2)
            histo[part+l+kind].DrawNormalized('same')
            leg.AddEntry(histo[part+l+kind],legName[parts.index(part)],'l')
            leg.Draw()
    c.SaveAs('../plots/'+kind+l+'.pdf')

def produceStack(histo,l,kind,title):
  ''' Produce stack plots '''
  c = TCanvas()
  leg = TLegend(0.1,0.75,0.3,0.9)
  hs = THStack()
  for part in parts:
    for lepton in leptons:
      if l == lepton:
        if histo[part+l+kind].GetEntries() > 0:
          histo[part+l+kind].SetFillColor(parts.index(part)+1)
          histo[part+l+kind].SetLineColor(parts.index(part)+1)
          hs.Add(histo[part+l+kind])
          hs.Draw()
          hs.GetXaxis().SetTitle(title)
          leg.AddEntry(histo[part+l+kind],legName[parts.index(part)],'f')
          leg.Draw()
  c.SaveAs('../plots/'+kind+l+'_stack.pdf')


histo = getHistos()
for lept in leptons:
  producePlot(histo,lept,'CorrMass','Bs Corrected Mass (MeV)')
  producePlot(histo,lept,'CorrMassErr','Bs Corrected Mass Error (MeV)')
  producePlot(histo,lept,'BP','Bs P (MeV)')
  producePlot(histo,lept,'BPT','Bs pT (MeV)')
  producePlot(histo,lept,'VChi2','Bs vertex #chi^{2}')
  producePlot(histo,lept,'DsVChi2','Ds vertex #chi^{2}')
  producePlot(histo,lept,'DOCA','Bs DOCA')
  producePlot(histo,lept,'DsMass','Ds Mass (MeV)')
  producePlot(histo,lept,'DIRA','Bs DIRA')
  producePlot(histo,lept,'FD','Bs FD #chi^{2}')
  producePlot(histo,lept,'IP','Bs IP #chi^{2}')
  producePlot(histo,lept,'MuP','Mu P (MeV)')
  producePlot(histo,lept,'MuPT','Mu pT (MeV)')
  producePlot(histo,lept,'DsP','Ds P (MeV)')
  producePlot(histo,lept,'DsPT','Ds pT (MeV)')
#  produceStack(histo,lept,'CorrMass','Bs Corrected Mass (MeV)')
#  produceStack(histo,lept,'CorrMassErr','Bs Corrected Mass Error (MeV)')
#  produceStack(histo,lept,'BP','Bs P (MeV)')
#  produceStack(histo,lept,'BPT','Bs pT (MeV)')
#  produceStack(histo,lept,'VChi2','Bs vertex #chi^{2}')
#  produceStack(histo,lept,'DsVChi2','Ds vertex #chi^{2}')
#  produceStack(histo,lept,'DOCA','Bs DOCA')
#  produceStack(histo,lept,'DsMass','Ds Mass (MeV)')
#  produceStack(histo,lept,'DIRA','Bs DIRA')
#  produceStack(histo,lept,'FD','Bs FD #chi^{2}')
#  produceStack(histo,lept,'IP','Bs IP #chi^{2}') 
#  produceStack(histo,lept,'MuP','Mu P (MeV)')
#  produceStack(histo,lept,'MuPT','Mu pT (MeV)')
#  produceStack(histo,lept,'DsP','Ds P (MeV)')
#  produceStack(histo,lept,'DsPT','Ds pT (MeV)')

