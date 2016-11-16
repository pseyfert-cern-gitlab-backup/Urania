## THIS IS JUST TO FILL THE HISTOS in BINS of PT and ETA
##TO DO:
## - change binning according to the trigger category

from ROOT import *
from array import array as afC
from SomeUtils.alyabar import *
from fiducial import *
import KsmmMathCrap as K
import cPickle
from pdb import set_trace

ptbins = afC('d', [0,1000000]) 
# define PT and ETA BINS
#binning TOSTOS1TOS
#ptbins = afC('d', [0,1623,1849,2074,2340,2705,100000])
#binning TOSTOS2TOS
#ptbins = afC('d', [0,1112,1236,1334,1438,1564,100000]) 
#binning TISTISTOS
#ptbins = afC('d', [0,742,873,1026,1225,1550,1000000])

#binning TOSTOS1TOS
#ybins = afC('d' , [0,2.76045328095,3.13072589356,3.52959311828,3.68156166192,3.87732214708, 50])  

#binning TOSTOS2TOS                                                                                                                               
#ybins = afC('d' , [0,3.23894299414,3.54760780322,3.70842344874,3.87077698432,4.08590687317, 50]) 

#binning TISTISTOS 
#ybins = afC('d' , [0,3.0099542258,3.37588593651, 3.58399877907, 3.76441038252,4.00754834566, 50])

ybins = afC('d' , [0, 50])
mK0 = 497.614


# FILL a 2D histos, needs the tree and the cuts you want to apply
def fillHistoGen(tree, cuts):
    'Fill gen histograms with TTree.Draw'
    histos = []
    for name, _ in cuts:
        histo = TH2F(name, name,len(ptbins)-1, ptbins, len(ybins)-1, ybins)
        tree.Draw("(0.5*log((KS0_TRUEP_E+KS0_TRUEP_Z)/(KS0_TRUEP_E-KS0_TRUEP_Z))):KS0_TRUEPT>>%s" % name)
        histos.append(histo)
    #set_trace()
    return histos


def fillHisto(tree, cuts):
    histos = []
    for name,cut in cuts:
        histo = TH2F(name, name,len(ptbins)-1, ptbins, len(ybins)-1, ybins)
        tree.Draw("(0.5*log((KS0_PE+KS0_PZ)/(KS0_PE-KS0_PZ))):KS0_PT>>%s" % name,cut)
        histos.append(histo)
    return histos


#def fillHisto(tree, cuts):
#    histos = []
#    for name,_ in cuts:
#        histos.append(TH2F(name,name,len(ptbins)-1, ptbins, len(ybins)-1,ybins))

#    for idx, entry in enumerate(tree):
#        if (idx%1000) == 0:
#            print idx
#        if idx>20000:
#            return histos#, histos1D
#        p = vector(entry.muplus_PX+entry.muminus_PX,entry.muplus_PY+entry.muminus_PY, entry.muplus_PZ+entry.muminus_PZ)
#        pt = vtmod(p)
#        E = sqrt(mK0**2 + vmod(p)**2)
#        pz = p[2]
#        if pz <0 : continue
#        y = 0.5*log( (E+pz)/(E-pz))
#        
#        for name_and_cut, h in zip(cuts, histos):
#            _, cut = name_and_cut
#           
#            if cut(entry): 
#                h.Fill(pt, y)
#                      
#    return histos




#THIS IS THE CROSS SECTION VALUES THEY USED FOR REWEIGHT IN 2011.. NEVER FOUND WHERE THESE NUMBERS COME FROM... WE ARE NOT USING THEM FOR 2012!
def refHisto():

## Magnet Up###
    hrefU = TH2F("spRU","spRU",len(ptbins)-1, ptbins, len(ybins)-1,ybins)

    hrefU.SetBinContent(1,1,4715) , hrefU.SetBinContent(1,2,4893), hrefU.SetBinContent(1,3,4603), hrefU.SetBinContent(1,4,4252), hrefU.SetBinContent(1,5,3906)
    hrefU.SetBinContent(2,1,2096), hrefU.SetBinContent(2,2,2040), hrefU.SetBinContent(2,3,1893), hrefU.SetBinContent(2,4,1717), hrefU.SetBinContent(2,5,1495)
    hrefU.SetBinContent(3,1,2040), hrefU.SetBinContent(3,2,1969), hrefU.SetBinContent(3,3,1798), hrefU.SetBinContent(3,4,1546), hrefU.SetBinContent(3,5,1306)
    
    hrefU.SetBinError(1,1,75) , hrefU.SetBinError(1,2,23), hrefU.SetBinError(1,3,13), hrefU.SetBinError(1,4,12), hrefU.SetBinError(1,5,20)
    hrefU.SetBinError(2,1,26), hrefU.SetBinError(2,2,11), hrefU.SetBinError(2,3,9), hrefU.SetBinError(2,4,8), hrefU.SetBinError(2,5,12)
    hrefU.SetBinError(3,1,19), hrefU.SetBinError(3,2,11), hrefU.SetBinError(3,3,12), hrefU.SetBinError(3,4,10), hrefU.SetBinError(3,5,14)
    
### Magnet Down ###
    hrefD = TH2F("spRD","spRD",len(ptbins)-1, ptbins, len(ybins)-1,ybins)

    hrefD.SetBinContent(1,1,2349), hrefD.SetBinContent(1,2,2465), hrefD.SetBinContent(1,3,2290), hrefD.SetBinContent(1,4,2104), hrefD.SetBinContent(1,5,1951)
    hrefD.SetBinContent(2,1,1044), hrefD.SetBinContent(2,2,1024), hrefD.SetBinContent(2,3,945), hrefD.SetBinContent(2,4,841), hrefD.SetBinContent(2,5,749)
    hrefD.SetBinContent(3,1,1002), hrefD.SetBinContent(3,2,984), hrefD.SetBinContent(3,3,889), hrefD.SetBinContent(3,4,743), hrefD.SetBinContent(3,5,621)

    hrefD.SetBinError(1,1,41), hrefD.SetBinError(1,2,13), hrefD.SetBinError(1,3,7), hrefD.SetBinError(1,4,7), hrefD.SetBinError(1,5,11)
    hrefD.SetBinError(2,1,14), hrefD.SetBinError(2,2,6), hrefD.SetBinError(2,3,6), hrefD.SetBinError(2,4,5), hrefD.SetBinError(2,5,7)
    hrefD.SetBinError(3,1,10), hrefD.SetBinError(3,2,6), hrefD.SetBinError(3,3,6), hrefD.SetBinError(3,4,5), hrefD.SetBinError(3,5,7)
    
    return  hrefU,  hrefD
