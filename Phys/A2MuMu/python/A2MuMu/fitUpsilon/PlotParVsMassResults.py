from ROOT import *
import math
gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
#gROOT.SetBatch()
import simplejson as json

from PlotPerEvMassErr_DY import *

import numpy as np
massbins = np.linspace(5,14,9)
percentage = 0.01
DYgraph = PlotDYMassErr(massbins, percentage)

#nsamples = ['Y1MC2011', 'Y1MC2012','Y2MC2011', 'Y2MC2012', 'Y3MC2011', 'Y3MC2012', 'A8MC2011', 'A8MC2012', 'A10MC2011', 'A10MC2012', 'A12MC2011', 'A12MC2012']
#nsamples = ['Y1MC2011','Y2MC2011', 'Y3MC2011', 'A8MC2011', 'A10MC2011','A12MC2011', ]
nsamples = ['Y1MC2012','Y2MC2012', 'Y3MC2012', 'A8MC2012', 'A10MC2012','A12MC2012', ]
#nsamples = ['Y1MC2011', 'Y1MC2012','Y2MC2011', 'Y3MC2011', 'Y3MC2012']
option = 'Allpt'
outfiletag = "YnSMC"



def importResultFile(nsample, option):
    resultfile = open('./FIT_RESULTS/fitParResults_{0}_{1}.py'.format(nsample, option),'r')
    sample = json.load(resultfile)
    return sample

samples = {}
for nsample in nsamples:
    samples[nsample]=importResultFile(nsample, option)

print samples

gexplist = {}
val = {}
err = {}
gexp = {}

for nsample, sample in samples.items():
       i = 0
       for (min, max,
               val['a'], err['a'],
               val['a2'], err['a2'],
               val['n'], err['n'],
               val['n2'], err['n2'],
               val['l'], err['l'],
               val['zeta'], err['zeta'],
               val['beta'], err['beta'],
               val['ipa_s'], err['ipa_s'],
               val['ipa_m'], err['ipa_m'],
               val['sigma0'], err['sigma0'],
               chi2) in sample:

            val['chi2'] = chi2
            err['chi2'] = 0.
            x = val['ipa_m']
            print nsample, x, val['ipa_s'], err['ipa_s']
            for par in val.keys():
                if i==0:
                    gexp[(nsample, par)] = TGraphAsymmErrors()
                    gexp[(nsample, par)].GetXaxis().SetLimits(4000,14000)
                gexp[(nsample, par)].SetPoint(i,x, val[par])
                gexp[(nsample, par)].SetPointError(i, 0, 0, err[par], err[par])
            i = i+1
       #gexplist[nsample] = gexp

def setDrawOptions(tgraph, title, varname, color=1):
    tgraph.SetTitle(title)
    tgraph.SetMarkerColor(color)
    tgraph.SetLineColor(color)
    tgraph.SetMarkerStyle(22)
    tgraph.GetXaxis().SetTitle('m(#mu#mu) MeV/c^{2}')
    tgraph.GetYaxis().SetTitle('parameter ' + varname)
    tgraph.GetXaxis().SetLimits(4000, 14000)
    if varname=='ipa_s':
        tgraph.GetYaxis().SetRangeUser(30., 80.)
    if varname=='l':
        tgraph.GetYaxis().SetRangeUser(-1.5, -0.8)
    if varname=='ipa_m':
        tgraph.GetYaxis().SetRangeUser(9450., 9500.)
    if varname=='sigma0':
        tgraph.GetYaxis().SetRangeUser(20., 30.)
    if varname=='n':
        tgraph.GetYaxis().SetRangeUser(1., 1.4)
    if varname=='beta':
        tgraph.GetYaxis().SetRangeUser(-0.01, 0.)

"""
canv = TCanvas()
for varname in val.keys():
    isFirst=1
    leg = TLegend(0.2,0.7,0.48,0.9);
    for nsample in samples.keys():
        tgraph=gexp[(nsample, varname)]
        if "2011" in nsample: ncolor=2
        if "2012" in nsample: ncolor=4
        setDrawOptions(tgraph, nsample, varname, ncolor)
        if isFirst:
            tgraph.Draw('AP')
            isFirst=0
        else:
            tgraph.Draw('P')
        leg.AddEntry(tgraph, nsample, 'lep')
    leg.Draw();
    #canv.BuildLegend()
    canv.Print('./PLOTPARS/Plot_'+ outfiletag+ "_"+ option +'_' +varname+'.pdf')
"""
varname='sigma0'
leg = TLegend(0.2,0.7,0.4,0.9);
DYgraph.GetXaxis().SetTitle('m(#mu#mu) MeV/c^{2}')
DYgraph.GetYaxis().SetTitle('MeV/c^{2}')
DYgraph.Draw('AP')
for nsample in samples.keys():
        tgraph=gexp[(nsample, varname)]
        if "Y" in nsample: ncolor=2
        if "A" in nsample: ncolor=4
        setDrawOptions(tgraph, nsample, varname, ncolor)
        tgraph.Draw('P')
leg.AddEntry(gexp[('Y1MC2012',varname)], '#Upsilon(nS) fitted #sigma_{0}', 'lep')
leg.AddEntry(gexp[('A10MC2012',varname)], 'A_{1}^{0} fitted #sigma_{0}', 'lep')
leg.AddEntry(DYgraph, 'DY per-ev mass err rampup', 'p')
leg.Draw();
#canv.BuildLegend()
canv.Print('./PLOTPARS/Plot_'+ outfiletag+ "_"+ option +'_' +varname+'_withDY.pdf')







#gexp['d11'].SetTitle('2011 data')
#gexp['d12'].SetTitle('2012 data')
#gexp['mc11']['ipa_s'].SetTitle('2011 MC')
#gexp['mc12'].SetTitle('2012 MC')

#gexp['d11'].SetMarkerColor(9)
#gexp['d12'].SetMarkerColor(46)
#gexp['mc11']['ipa_s'].SetMarkerColor(4)
#gexp['mc12'].SetMarkerColor(2)

#gexp['d11'].SetLineColor(9)
#gexp['d12'].SetLineColor(46)
#gexp['mc11']['ipa_s'].SetLineColor(4)
#gexp['mc12'].SetLineColor(2)


#gexp['d11'].SetFillColorAlpha(0, 0.2)
#gexp['d12'].SetFillColorAlpha(0, 0.2)
#gexp['mc11']['ipa_s'].SetFillColorAlpha(0, 0.2)
#gexp['mc12'].SetFillColorAlpha(0, 0.2)

#gexp['d11'].SetMarkerStyle(20)
#gexp['d12'].SetMarkerStyle(20)
#gexp['mc11']['ipa_s'].SetMarkerStyle(22)
#gexp['mc12'].SetMarkerStyle(22)

#gexp['d11'].GetXaxis().SetTitle('log_{10}(p_{T}/MeV)')
#gexp['d11'].GetYaxis().SetTitle('parameter l')

#gexp['d11'].Draw('AP')
#gexp['d12'].Draw('P')
#gexp['mc11']['ipa_s'].Draw('AP')
#gexp['mc12'].Draw('P')

#canv.BuildLegend()
#canv.Print('test.pdf')


