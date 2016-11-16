from ROOT import *
import math
gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
gROOT.SetBatch()
import simplejson as json

fptbinsc = open('./logptBinsCentres.json','r')
meanDict = json.load(fptbinsc)

nsamples = ['fitA12_YnSscaled', 'fitA8_YnSscaled']
#nsamples = ['fitA8']
outfiletag = "Simultaneous_study"



def importResultFile(nsample):
    resultfile = open('./FIT_RESULTS/fitParResults__{0}.py'.format(nsample),'r')
    sample = json.load(resultfile)
    return sample

samples = {}
for nsample in nsamples:
    samples[nsample]=importResultFile(nsample)

print samples

gexplist = {}
val = {}
err = {}
gexp = {}

for nsample, sample in samples.items():
       i = 0
       #mean = meanDict[nsample]
       mean = meanDict['Y1MC2012'] #taking the same for every sample...
       for (min, max,
               val['a'], err['a'],
               val['a2'], err['a2'],
               val['n'], err['n'],
               val['n2'], err['n2'],
               val['l_slope'], err['l_slope'],
               val['zeta'], err['zeta'],
               val['beta'], err['beta'],
               val['ipa_s'], err['ipa_s'],
               val['gscale_m'], err['gscale_m'],
               val['nA'], err['nA'],
               val['nY1'], err['nY1'],
               chi2) in sample:

            val['chi2'] = chi2
            err['chi2'] = 0.
            for m in mean:
                if (m>min and m<max): x=m
            print nsample, x, val['ipa_s'], err['ipa_s']
            for par in val.keys():
                if i==0: gexp[(nsample, par)] = TGraphAsymmErrors()
                gexp[(nsample, par)].SetPoint(i,x, val[par])
                gexp[(nsample, par)].SetPointError(i, x-min, max-x, err[par], err[par])
            i = i+1
       #gexplist[nsample] = gexp

def setDrawOptions(tgraph, title, varname, color=1, style=1):
    tgraph.SetTitle(title)
    tgraph.SetMarkerColor(color)
    tgraph.SetLineColor(color)
    tgraph.SetFillColor(kWhite)
    tgraph.SetMarkerStyle(21+style)
    tgraph.GetXaxis().SetTitle('log_{10}(p_{T}/MeV)')
    ytitle = 'parameter'+varname
    if varname=='nA': ytitle='fitted/injected A_{0} yield'
    if varname=='nY1': ytitle='fitted/injected #Upsilon(nS) yield'
    tgraph.GetYaxis().SetTitle(ytitle)
    tgraph.GetXaxis().SetRangeUser(3.8, 4.6)
    if varname=='ipa_s':
        tgraph.GetYaxis().SetRangeUser(0., 100.)
    if varname=='nA':
        tgraph.GetYaxis().SetRangeUser(0, 2.)
    if varname=='l_slope':
        tgraph.GetYaxis().SetRangeUser(-1.6e-4, -1.1e-4)
    if varname=='gscale_m':
        tgraph.GetYaxis().SetRangeUser(0.99, 1.01)
    if varname=='n':
        tgraph.GetYaxis().SetRangeUser(0., 2.)
    if varname=='nA':
        tgraph.GetYaxis().SetRangeUser(0., 2.)
    if varname=='nY1':
        tgraph.GetYaxis().SetRangeUser(0., 2.)
    if varname=='chi2':
        tgraph.GetYaxis().SetRangeUser(0., 2.)

canv = TCanvas()
for varname in val.keys():
    isFirst=1
    leg = TLegend(0.2,0.7,0.48,0.9);
    for nsample in samples.keys():
        tgraph=gexp[(nsample, varname)]
        if "A12" in nsample: ncolor=2
        if "A8" in nsample: ncolor=4
        if "2011" in nsample: ncolor=2
        if "2012" in nsample: ncolor=4
        style = 1
        if 'Y1' in nsample: style=1
        if 'Y2' in nsample: style=2
        if 'Y3' in nsample: style=3

        setDrawOptions(tgraph, nsample, varname, ncolor, style)
        if isFirst:
            tgraph.Draw('AP')
            isFirst=0
        else:
            tgraph.Draw('P')
        title=''
        if 'A8' in nsample: title='A1 at 8 GeV '
        if 'A12' in nsample: title='A1 at 12 GeV '
        if 'Y1' in nsample: title='Y(1S) MC '
        if 'Y2' in nsample: title='Y(2S) MC '
        if 'Y3' in nsample: title='Y(3S) MC '
        if '2011' in nsample: title = title + '2011'
        if '2012' in nsample: title = title + '2012'
        leg.AddEntry(tgraph, title, 'lep')
    leg.Draw();
    canv.Print('./PLOTPARS/Plot_'+ outfiletag+ "_"+ nsample +'_' +varname+'.pdf')




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


