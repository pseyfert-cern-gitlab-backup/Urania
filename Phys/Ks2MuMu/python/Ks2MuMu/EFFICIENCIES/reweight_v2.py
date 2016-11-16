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

histos = ROOT.TFile.Open("histosEfficiencies_v2.root")
hdict = {}

histoData=None

for tkey in histos.GetListOfKeys():
    #print tkey.GetName()
    if tkey.GetName()=='hDataTot':
        histoData=tkey.ReadObj()
    else:
        hdict[tkey.GetName()] = {}
        obj = tkey.ReadObj()
        for key2 in obj.GetListOfKeys():
            hdict[tkey.GetName()][key2.GetName()] = key2.ReadObj()

def doEfficiencies(hdict,histoData,error):
    
    if error == 'correlated':
        for i in range(hdict['Bin0']['effTrigMuMu'].GetNbinsX()):
            for j in range(hdict['Bin0']['effTrigMuMu'].GetNbinsY()):
                hdict['Bin0']['effTrigMuMu'].SetBinError(i+1,j+1, 0)
                hdict['Bin0']['effFidMuMu'].SetBinError(i+1,j+1, 0)
                hdict['Bin0']['effStripMuMu'].SetBinError(i+1,j+1, 0)
                hdict['Bin0']['effStripMB'].SetBinError(i+1,j+1, 0)
                histoData.SetBinError(i+1,j+1, 0)

    if error == 'uncorrelated':
        for binID in hdict:
            for i in range(hdict[binID]['effBDTMuMu'].GetNbinsX()):
                for j in range(hdict[binID]['effBDTMuMu'].GetNbinsY()):
                    hdict[binID]['effBDTMuMu'].SetBinError(i+1,j+1, 0)
    
                    

    for binID in hdict:

        #        effBinMuMu.SetName('effBinMuMu'+binID)
        effBinMuMu = K.rec_product2(hdict['Bin0']['effTrigMuMu'],hdict[binID]['effBDTMuMu'],hdict['Bin0']['effFidMuMu'],hdict['Bin0']['effStripMuMu'])
        effBinMuMu.SetName('effBinMuMu'+binID)
        norm = K.hratio2(effBinMuMu,hdict['Bin0']['effStripMB'],0)
        norm.SetName('norm'+binID)
        normFin  = K.rec_product2(norm,histoData)
        normFin.SetName('normFin'+binID)
        
        effTot, effTot_err = K.sumHisto(effBinMuMu)
        alpha, alpha_err = K.sumHisto(normFin)
        
        print 'BIN ',binID
        print 'eff not reweighted: ',effTot,' \pm ' ,effTot_err 
        print 'alpha: ', alpha,' \pm ' ,alpha_err
        print ''
        print ''


    return 

doEfficiencies(hdict,histoData,'')




