fName = 'Hists_BsRestFrame_MagDown.root'

from ROOT import *
gROOT.SetBatch(True)
gROOT.ProcessLine('.x ~/lhcbStyle.C')
#from makeSpeciesHists import labelMap

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

s = '''
Dsmu_q2_hist;1Hist
KEY: TH1FDsmu_q2_hist_normalised;1Hist
KEY: TH1FDsmu_MM2_hist;1Hist
KEY: TH1FDsmu_MM2_hist_normalised;1Hist
KEY: TH1FDsmu_Emu_hist;1Hist
KEY: TH1FDsmu_Emu_hist_normalised;1Hist
KEY: TH1FDsmu_q2True_hist;1Hist
KEY: TH1FDsmu_q2True_hist_normalised;1Hist
KEY: TH1FDsmu_MM2True_hist;1Hist
KEY: TH1FDsmu_MM2True_hist_normalised;1Hist
KEY: TH1FDsmu_EmuTrue_hist;1Hist
KEY: TH1FDsmu_EmuTrue_hist_normalised;1Hist
'''

f = TFile(fName, 'read')
#f.ls()

leptonList = ['tau', 'mu']
#for lepton in leptonList:

for var in histDict.keys():
    
    tauHist = f.Get('Dstau_%s_hist_normalised' %var)
    #print tauHist
    muHist  = f.Get('Dsmu_%s_hist_normalised' %var)
    muHist.SetLineColor(2)
    c = TCanvas('c%s' %var, 'c', 800, 600)
    c.cd()

    if muHist.GetMaximum() > tauHist.GetMaximum():
        muHist.Draw('HIST')
        tauHist.Draw('HIST SAME')
    else:
        tauHist.Draw('HIST')
        muHist.Draw('HIST SAME')
                        
    # Now the legend.
    l = TLegend(0.8, 0.77, 0.9, 0.92)
    l.AddEntry(muHist, labelMap['Dsmu'], 'L')
    l.AddEntry(tauHist, labelMap['Dstau'], 'L')
    l.Draw()

    c.SaveAs('RDs_VarComparison_%s.eps' %var)
    c.SaveAs('RDs_VarComparison_%s.pdf' %var)
