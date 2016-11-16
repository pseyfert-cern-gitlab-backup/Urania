from ROOT import *
import sys
sys.path.append("..")
import math
gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
#gROOT.SetBatch()
import OurSites
import CutsList
import simplejson as json

def PlotDYMassErr(massbins, percentage):
       inputTuples = {
        'DYMC2012': OurSites.MY_TUPLE_PATH + "DrellYan_MC_2012.root",
        'DYMC2012': OurSites.MY_TUPLE_PATH + "DrellYan_MC_2011.root",
        }

       histos = {}
       hEta = {}
       hlogpT = {}

       canv = TCanvas()
       canvEta = TCanvas()
       canvpT = TCanvas()

       for year, tup in inputTuples.items():
           t2 = TChain('A1/A1')
           t2.Add(tup)


       graph = TGraph()

       for nbin in range(len(massbins)-1):
           cut = CutsList.PreSelection
           masscut = 'Bmass > {0} && Bmass < {1}'.format(massbins[nbin]*1000., massbins[nbin+1]*1000.)
           cut = cut +'&&' + masscut
           step = 0.1 #MeV
           totentries = t2.GetEntries(masscut)
           rampup = 0
           for i in range(1000):
                  entries = t2.GetEntries(masscut +'&&'+ 'B_MMass_Err<{0}'.format(i*step))
                  if float(entries)/float(totentries)>percentage:
                         rampup = i*step
                         break
           massval = (massbins[nbin]+massbins[nbin+1])/2.0
           graph.SetPoint(nbin, massval*1000., rampup)


       return graph
       #graph.Draw('AP')

"""

    histos[nbin] = TH1F('h'+str(nbin), masscut, 200,0.,200.)
    t2.Draw('B_MMass_Err>>{0}'.format('h'+str(nbin)), cut)
    #hEta[nbin] = TH1F('eta'+nbin, nbin, 200,2.,5.)
    #t2.Draw('B_eta>>{0}'.format('eta'+nbin), cut)
    #hlogpT[nbin] = TH1F('pt'+nbin, nbin, 200,3.8,5)
    #t2.Draw('log10(Bpt)>>{0}'.format('pt'+nbin), cut)

i=0
for nbin in range(len(massbins)-1):
    #histos[nbin].SetLineColor(kAzure-4+nbin)
    histos[nbin].SetLineColor(nbin+2)
    if i==0:
        option = ''
    else:
        option = 'same'
    canv.cd()
    histos[nbin].GetXaxis().SetRangeUser(10,60)
    histos[nbin].GetXaxis().SetTitle('per-event mass error [MeV/c^{2}]')
    histos[nbin].DrawNormalized(option)
    i = i+1

    #canvEta.cd()
    #hEta[sample].DrawNormalized(option)

    #canvpT.cd()
    #hlogpT[sample].DrawNormalized(option)

canv.BuildLegend()
canv.Print('PlotPerEvMassErr_DY.pdf')
#canvEta.Print('PlotEta.pdf')
#canvpT.Print('PlotLogpt.pdf')
"""
