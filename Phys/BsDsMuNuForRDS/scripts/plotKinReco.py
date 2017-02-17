#!/usr/bin/env python

from ROOT import *
import sys

lepton = sys.argv[1]

f = TFile('../tuples/histosKinReco_MC09_'+lepton+'Nu.root')
#parts = ['Ds','Dsst','Ds0','Ds1','Dspr']
#legName = ['D_{s}^{+}','D_{s}^{*+}','D_{s0}(2317)^{+}','D_{s1}(2460)^{+}',"D_{s1}(2536)^{+}"]
#parts = ['Ds','Dsst','Ds0']
#legName = ['D_{s}^{+}','D_{s}^{*+}','D_{s0}(2317)^{+}']
parts = ['Dsst']
legName = ['D_{s}^{*+}']

def getHistos():
    histos = {} 
    for part in parts:
      histos[part+lepton+'CorrMass'] = f.Get(part+lepton+'CorrMass')
      histos[part+lepton+'CorrMassErr'] = f.Get(part+lepton+'CorrMassErr')
      histos[part+lepton+'Bvis'] = f.Get(part+lepton+'Bvis')
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
    leg = TLegend(0.55,0.70,0.75,0.9)
    for part in parts:
      print dir(histo[part+l+kind])
      if histo[part+l+kind].GetEntries() > 0:
        histo[part+l+kind].GetXaxis().SetTitle(title)
        histo[part+l+kind].SetLineColor(parts.index(part)+1)
        histo[part+l+kind].SetLineWidth(2)
        histo[part+l+kind].DrawNormalized('same')
        leg.AddEntry(histo[part+l+kind],legName[parts.index(part)],'l')
        leg.Draw()
    c.SaveAs('../plots/'+kind+l+'_MC09_'+l+'Nu.pdf')
    #c.SaveAs('../plots/'+kind+l+'_MC09_MuNu.png')

def produceStack(histo,l,kind,title):
  ''' Produce stack plots '''
  c = TCanvas()
  leg = TLegend(0.1,0.75,0.3,0.9)
  hs = THStack()
  for part in parts:
    if histo[part+l+kind].GetEntries() > 0:
      histo[part+l+kind].SetFillColor(parts.index(part)+1)
      histo[part+l+kind].SetLineColor(parts.index(part)+1)
      hs.Add(histo[part+l+kind])
      hs.Draw()
      hs.GetXaxis().SetTitle(title)
      leg.AddEntry(histo[part+l+kind],legName[parts.index(part)],'f')
      leg.Draw()
  c.SaveAs('../plots/'+kind+l+'_stack_MC09_'+l+'Nu.pdf')

histo = getHistos()
#producePlot(histo,lepton,'CorrMass','Bs Corrected Mass (MeV)')
#producePlot(histo,lepton,'CorrMassErr','Bs Corrected Mass Error (MeV)')
producePlot(histo,lepton,'Bvis','Bs visible mass (MeV)')
#producePlot(histo,lepton,'BP','Bs P (MeV)')
#producePlot(histo,lepton,'BPT','Bs pT (MeV)')
#producePlot(histo,lepton,'VChi2','Bs vertex #chi^{2}')
#producePlot(histo,lepton,'DsVChi2','Ds vertex #chi^{2}')
#producePlot(histo,lepton,'DOCA','Bs DOCA')
#producePlot(histo,lepton,'DsMass','Ds Mass (MeV)')
#producePlot(histo,lepton,'DIRA','Bs DIRA')
#producePlot(histo,lepton,'FD','Bs FD #chi^{2}')
#producePlot(histo,lepton,'IP','Bs IP #chi^{2}')
#producePlot(histo,lepton,'MuP','Mu P (MeV)')
#producePlot(histo,lepton,'MuPT','Mu pT (MeV)')
#producePlot(histo,lepton,'DsP','Ds P (MeV)')
#producePlot(histo,lepton,'DsPT','Ds pT (MeV)')
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

