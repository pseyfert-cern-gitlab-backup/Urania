import ROOT
from array import array as afC
from SomeUtils.alyabar import *
from cuts import *
#import histoTex as M
import KsmmMathCrap as K
import cPickle
from fillHisto import *
from itertools import *
from pdb import set_trace

histos = ROOT.TFile.Open("histosEfficiencies.root")
hdict = {}

histoData=None

for tkey in histos.GetListOfKeys():
    print tkey.GetName()
    if tkey.GetName()=='hDataTot':
        histoData=tkey.ReadObj()
    else:
        hdict[tkey.GetName()] = {}
        obj = tkey.ReadObj()
        for key2 in obj.GetListOfKeys():
            hdict[tkey.GetName()][key2.GetName()] = key2.ReadObj()

def doEfficiencies(hdict,histoData):
    
    for binID in hdict:
        #set_trace() 
        #PRODUCT OF ALL THE EFFICIENCIES AND REWEIGHT (+ CORRECTION)

        effProdMuMu = K.rec_product2(hdict['Bin0']['effTrigMuMu'],hdict[binID]['effBDTMuMu'],hdict['Bin0']['effFidMuMu'],hdict['Bin0']['effStripMuMu'])
        effProdMuMuWeighted  = K.rec_product2(effProdMuMu,histoData)#,hdict['Bin0']['effCorrMB'])

        #print [effProdMuMu.GetBinContent(i,1) for i in range(1,5)]
        #print [effProdMuMuWeighted.GetBinContent(i,1) for i in range(1,5)]
        
        #IDEM FOR MB
        effProdMB = K.rec_product2(hdict['Bin0']['effTrigMB'],hdict[binID]['effBDTMB'],hdict['Bin0']['effFidMB'],hdict['Bin0']['effStripMB'])
        effProdMBWeighted  = K.rec_product2(effProdMB,histoData)#,hdict['Bin0']['effCorrMB'])


        sumEffMuMu, errSumEffMuMu = K.sumHisto(effProdMuMu)
        sumEffMB, errSumEffMB = K.sumHisto(effProdMB)

        print  sumEffMuMu/4, sumEffMB/4

    
#    for i in hdict:
#        for j in hdict[i]:
#            h = hdict[i][j].Clone()
#            print 'histo: ', h.GetName()
#            for pt in range(h.GetNbinsX()):
#                for eta in range(h.GetNbinsY()):
#                    x = h.GetBinContent(pt+1,eta+1)
#                    y = h.GetBinError(pt+1,eta+1)
#                    print 'pt:  ', pt, '   eta:  ', eta, ' bin Content:  ', x, ' \pm ', y 


    return  #sumEffMuMu, errSumEffMuMu, sumEffMB, errSumEffMB

doEfficiencies(hdict,histoData)
#print sumEffMuMu, errSumEffMuMu, sumEffMB, errSumEffMB

