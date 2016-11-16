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

import argparse
parser = argparse.ArgumentParser(description='fit')
parser.add_argument('inputfile')
parser.add_argument('errors', choices=['uncorrelated','correlated','all'],
                   help='error can be uncorrelated,correlated,all')

args = parser.parse_args()
histos = ROOT.TFile.Open(args.inputfile)
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
    
    if error == 'uncorrelated':
        for i in range(hdict['Bin0']['effTrigMuMu'].GetNbinsX()):
            for j in range(hdict['Bin0']['effTrigMuMu'].GetNbinsY()):
                hdict['Bin0']['effTrigMuMu'].SetBinError(i+1,j+1, 0)
                hdict['Bin0']['effFidMuMu'].SetBinError(i+1,j+1, 0)
                hdict['Bin0']['effStripMuMu'].SetBinError(i+1,j+1, 0)
                hdict['Bin0']['effStripMB'].SetBinError(i+1,j+1, 0)
                hdict['Bin0']['effRecoMuMu'].SetBinError(i+1,j+1, 0)
                hdict['Bin0']['effRecoMB'].SetBinError(i+1,j+1, 0)
                histoData.SetBinError(i+1,j+1, 0)

    if error == 'correlated':
        for binID in hdict:
            for i in range(hdict[binID]['effBDTMuMu'].GetNbinsX()):
                for j in range(hdict[binID]['effBDTMuMu'].GetNbinsY()):
                    hdict[binID]['effBDTMuMu'].SetBinError(i+1,j+1, 0)
    
                  
    if error =='all': 
        print 'you are not specifing the error'
    
    list_eff=[]
    list_err_eff=[]
    for binID in hdict:
        
        
        effBinMuMu = K.rec_product2(hdict['Bin0']['effTrigMuMu'],hdict[binID]['effBDTMuMu'],hdict['Bin0']['effFidMuMu'],hdict['Bin0']['effStripMuMu'],hdict['Bin0']['effRecoMuMu'])
        effBinMuMu.SetName('effBinMuMu'+binID)
        
        effMB = K.rec_product2(hdict['Bin0']['effStripMB'],hdict['Bin0']['effRecoMB'])
        effMB.SetName('effMB'+binID)
        
        ratio = K.hratio2(effBinMuMu,effMB,0)
        ratio.SetName('ratio'+binID)
        ratioW  = K.rec_product2(ratio,histoData)
        ratioW.SetName('ratioW'+binID)
        
        effTot, effTot_err = K.sumHisto(ratio)
        alpha, alpha_err = K.sumHisto(ratioW)
        #alpha, alpha_err = K.sumHisto(hdict[binID]['effBDTMuMu']) 
        #      print 'BIN ',binID
        #        print 'eff not reweighted: ',effTot,' \pm ' ,effTot_err
        #     print 'alpha: ', alpha,' \pm ' ,alpha_err
        #        print ''
        #        print ''

        list_eff.append((binID,alpha))
        list_err_eff.append((binID,alpha_err))  
        

    sort_list_eff= sorted(list_eff,key=lambda x: int(x[0].replace('Bin','')))
    sort_list_err_eff= sorted(list_err_eff,key=lambda x: int(x[0].replace('Bin','')))

    print "alpha"
    print [i for _, i in sort_list_eff[1:]]
    print ""
    print "alpha err"
    print [i for _, i in sort_list_err_eff[1:]]

#    for i in hdict:
#        for j in hdict[i]:
#            h = hdict[i][j].Clone()
#            print 'histo: ', h.GetName()
#            for pt in range(h.GetNbinsX()):
#                for eta in range(h.GetNbinsY()):
#                    x = h.GetBinContent(pt+1,eta+1)
#                    y = h.GetBinError(pt+1,eta+1)
#                    print 'pt:  ', pt, '   eta:  ', eta, ' bin Content:  ', x, ' \pm ', y 
                     
                       #
    
   # print "HISTO DATA"
   # print " "
   # for pt in range(histoData.GetNbinsX()):
   #     for eta in range(histoData.GetNbinsY()):
   #         x = histoData.GetBinContent(pt+1,eta+1)
   #         y = histoData.GetBinError(pt+1,eta+1)
   #         print 'pt:  ', pt, '   eta:  ', eta, ' bin Content:  ', x, ' \pm ', y
           
    return 

doEfficiencies(hdict,histoData,args.errors)




