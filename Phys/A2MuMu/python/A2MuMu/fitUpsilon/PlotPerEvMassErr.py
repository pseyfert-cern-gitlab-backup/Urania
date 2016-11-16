from ROOT import *
import sys
sys.path.append("..")
import math
gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
#gROOT.SetBatch()
import OurSites
import CutsList
import simplejson as json

inputTuples = {
        #'DATA2011': OurSites.MY_TUPLE_PATH + "RealData_2011_s21r1_Erasmus_v10r3_976pb.root",
        #'DATA2012': OurSites.MY_TUPLE_PATH + "RealData_2012_s21_Erasmus_v10r3_1991pb.root",
        'Y1MC2011': OurSites.MY_TUPLE_PATH + "Upsilon_1S_MC_2011.root",
        #'Y1MC2012': OurSites.MY_TUPLE_PATH + "Upsilon_1S_MC_2012.root",
        'Y2MC2011': OurSites.MY_TUPLE_PATH + "Upsilon_2S_MC_2011.root",
        #'Y2MC2012': OurSites.MY_TUPLE_PATH + "Upsilon_2S_MC_2012.root",
        'Y3MC2011': OurSites.MY_TUPLE_PATH + "Upsilon_3S_MC_2011.root",
        #'Y3MC2012': OurSites.MY_TUPLE_PATH + "Upsilon_3S_MC_2012.root",
        }

histos = {}
hEta = {}
hlogpT = {}

canv = TCanvas()
canvEta = TCanvas()
canvpT = TCanvas()

for sample, tup in inputTuples.items():
    cut = CutsList.PreSelection
    if "Y1" in sample: cut = cut + "&&" + CutsList.truthMatching['Y']
    if "Y2" in sample: cut = cut + "&&" + CutsList.truthMatching['Y2']
    if "Y3" in sample: cut = cut + "&&" + CutsList.truthMatching['Y3']
    tupleName = 'A1/A1'
    t2 = TChain(tupleName)
    t2.Add(tup)
    histos[sample] = TH1F(sample, sample, 800,0.,200.)
    t2.Draw('B_MMass_Err>>{0}'.format(sample), cut)
    hEta[sample] = TH1F('eta'+sample, sample, 200,2.,5.)
    t2.Draw('B_eta>>{0}'.format('eta'+sample), cut)
    hlogpT[sample] = TH1F('pt'+sample, sample, 200,3.8,5)
    t2.Draw('log10(Bpt)>>{0}'.format('pt'+sample), cut)

    lineColor = {'Y1':2, 'Y2':3, 'Y3':4}
for i, sample in enumerate(inputTuples.keys()):
    if 'Y1' in sample:
        histos[sample].SetLineColor(2)
        hEta[sample].SetLineColor(2)
        hlogpT[sample].SetLineColor(2)
    if 'Y2' in sample:
        histos[sample].SetLineColor(3)
        hEta[sample].SetLineColor(3)
        hlogpT[sample].SetLineColor(3)
    if 'Y3' in sample:
        histos[sample].SetLineColor(4)
        hEta[sample].SetLineColor(4)
        hlogpT[sample].SetLineColor(4)
    if '2011' in sample:
        histos[sample].SetLineStyle(2)
        hEta[sample].SetLineStyle(2)
        hlogpT[sample].SetLineStyle(2)
    if i==0:
        option = ''
    else:
        option = 'same'
    canv.cd()
    histos[sample].GetXaxis().SetRangeUser(20,30)
    histos[sample].GetXaxis().SetTitle('per-event mass error [MeV/c^{2}]')
    histos[sample].DrawNormalized(option)

    canvEta.cd()
    hEta[sample].DrawNormalized(option)

    canvpT.cd()
    hlogpT[sample].DrawNormalized(option)

canv.BuildLegend()
canv.Print('PlotPerEvMassErr.pdf')
canv.Update()
#canvEta.Print('PlotEta.pdf')
#canvpT.Print('PlotLogpt.pdf')

