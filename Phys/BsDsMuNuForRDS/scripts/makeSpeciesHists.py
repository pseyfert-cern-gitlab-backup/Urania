from ROOT import *
gROOT.SetBatch(True)
gROOT.ProcessLine('.x ~/lhcbStyle.C')
from truthCuts import cutDict, cutComponentDict
polarity = 'Down'

# Get the files and tuples.
fName = '/afs/cern.ch/work/s/sogilvy/RDs/RDS_DiMuon_%s.root' %polarity
tName = 'B2DsMuNuTuple/DecayTree'
f = TFile(fName)
t = f.Get(tName)

fNameBsRF = 'BsRestVars_Mag%s.root' %polarity
tNameBsRF = 'BsRestVars'
f2 = TFile(fNameBsRF)
t2 = f2.Get(tNameBsRF)

print 'Got files, making friends.'
t.AddFriend(t2)

numBins = 30

histDict = {
    'q2'        : { 'range'  : [0.0, 12.0]
                    ,'units' : 'GeV^{2}/c^{4}'
                    ,'label' : 'q^{2}' }
    ,'q2True'    : { 'range'  : [0.0, 12.0]
                    ,'units' : 'GeV^{2}/c^{4}'
                    ,'label' : 'TRUE q^{2}' }
    
    ,'Emu'      : { 'range'  : [0.0, 2.5]
                    ,'units' : 'GeV/c^{2}'
                    ,'label' : 'E_{#mu}^{*}' }
    ,'EmuTrue'  : { 'range'  : [0.0, 2.5]
                    ,'units' : 'GeV/c^{2}'
                    ,'label' : 'TRUE E_{#mu}^{*}' }
    
    ,'MM2'      : { 'range'  : [0.0, 10.0]
                    ,'units' : 'GeV^{2}/c^{4}'
                    ,'label' : 'm_{miss}^{2}' }
    ,'MM2True'  : { 'range'  : [0.0, 10.0]
                    ,'units' : 'GeV^{2}/c^{4}'
                    ,'label' : 'TRUE m_{miss}^{2}' }
    }

labelMap = {
    'Dsmu'         : 'D_{s}^{+} #mu^{-}'
    ,'Dstau'       : 'D_{s}^{+} #tau^{-}'
    ,'DsStarmu'    : 'D_{s}^{*+} #mu^{-}'
    ,'DsStartau'   : 'D_{s}^{*+} #tau^{-}'
    ,'Ds2460mu'    : 'D_{s1}(2460)^{+} #mu^{-}'
    ,'Ds2460tau'   : 'D_{s1}(2460)^{+} #tau^{-}'
    ,'Ds2536mu'    : 'D_{s1}(2536)^{+} #mu^{-}'
    ,'Ds2536tau'   : 'D_{s1}(2536)^{+} #tau^{-}'
    ,'Ds0Starmu'   : 'D_{s0}(2317)^{+} #mu^{-}'
    ,'Ds0Startau'  : 'D_{s0}(2317)^{+} #tau^{-}'
    }

hList = []

# Now make some hists for each species.
for label, cut in cutDict.iteritems():

    print 'Processing', label
    numEvents = t.GetEntries(cut)
    print '\t Found %i events.' %numEvents
    if numEvents == 0:
        print '\t Skipping this mode.'
        continue
    print '\t Making histograms.'

    for branchName, settings in histDict.iteritems():

        histName = '%s_%s_hist' %(label, branchName)
        #histName = histName = '%s%sHist' %(label, branchName)
        #print histName
        histSettingsString = '%s(%i, %f, %f)' %(histName, numBins,
                                                settings['range'][0],
                                                settings['range'][1])
        #print histSettingsString
        drawString = '%s>>%s' %(branchName, histSettingsString)
        print 'drawString says:', drawString
        # Now make the histogram
        t.Draw(drawString, cut)

        # Get it from memory
        h = gDirectory.Get(histName)

        # Format it
        h.SetTitle('Hist')
        xAxisString = '%s [%s]' %(settings['label'], settings['units'])
        h.GetXaxis().SetTitle(xAxisString)
        h.GetXaxis().SetRangeUser(settings['range'][0], settings['range'][1])
        binWidth = (settings['range'][1] - settings['range'][0]) / numBins
        yAxisString = 'Entries per %0.1f %s' %(binWidth, settings['units'])
        h.GetYaxis().SetTitle(yAxisString)

        # Now make a clone which is normalised to unity.
        h2 = h.Clone(histName + '_normalised')
        h2.Sumw2()
        h2.Scale(1/h2.Integral())
        yAxisString = '1/N dN (%0.1f [%s])' %(binWidth, settings['units'])
        h2.GetYaxis().SetTitle(yAxisString)
                
        # Add to the list.
        hList.append(h)
        hList.append(h2)

for h in hList:
    c = TCanvas(h.GetName(), 'hist', 800, 600)
    c.cd()
    h.Draw('e')

    # Make a label from the first part of the name.
    label = h.GetName().split('_')[0]
    print 'XXX', label
    l = TLegend(0.73, 0.8, 0.88, 0.9)
    l.AddEntry(h, labelMap[label], 'L')
    l.Draw()
    c.SaveAs('Canvas_%s.eps' %h.GetName())
    c.SaveAs('Canvas_%s.pdf' %h.GetName())
    
outFileName = 'Hists_BsRestFrame_Mag%s.root' %polarity
outFile = TFile(outFileName, 'recreate')
for h in hList:
    h.Write()
outFile.Close()    

