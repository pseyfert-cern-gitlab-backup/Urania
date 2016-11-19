#!/usr/bin/env python

from ROOT import *

f = TFile('../src/Hists_BsRestFrame_MagDown.root')
#parts = ['Ds','Dsst','Ds0','Ds1','Dspr']
parts = ['Ds','Ds0Star']
#legName = ['D_{s}^{+}','D_{s}^{*+}','D_{s0}(2317)^{+}','D_{s1}(2460)^{+}',"D_{s1}(2536)^{+}"]
legName = ['D_{s}^{*+}#mu','D_{s}^{+}#tau']
#legName = ['D_{s}^{*+}#tau','D_{s}^{+}#mu']
leptons = ['tau','mu']
#decays = ['Ds0Startau','Dsmu']
decays = ['Ds0Starmu','Dstau']

def getHistos():

    histos = {} 
    for part in parts:
      for lepton in leptons:
        histos[part+lepton+'Emu'] = f.Get(part+lepton+'_Emu_hist_normalised')
        histos[part+lepton+'q2'] = f.Get(part+lepton+'_q2_hist_normalised')
        histos[part+lepton+'MM2'] = f.Get(part+lepton+'_MM2_hist_normalised')

    return histos

def producePlot(histo,kind,title):

    ''' Produce regular histograms '''
    c = TCanvas()
    leg = TLegend(0.7,0.75,0.9,0.9)
    for decay in decays:
      if histo[decay+kind].GetEntries() > 0:
        histo[decay+kind].GetXaxis().SetTitle(title)
        if 'mu' in decay:
          color = 1
        if 'tau' in decay:
          color = 2
        print "%s, %s" %(color, decay)
        histo[decay+kind].SetMarkerColor(color)
        histo[decay+kind].SetLineColor(color)
        histo[decay+kind].SetLineWidth(2)
        histo[decay+kind].DrawNormalized('same')
        leg.AddEntry(histo[decay+kind],legName[decays.index(decay)],'l')
        leg.Draw()
    c.SaveAs('../plots/DsTau_vs_DsstMu_'+kind+'.pdf')

histo = getHistos()
#producePlot(histo,'Emu','E^{*}_{#mu} (GeV)')
#producePlot(histo,'q2','q^{2} (GeV^{2})')
producePlot(histo,'MM2','Missing mass squared (GeV^{2})')
