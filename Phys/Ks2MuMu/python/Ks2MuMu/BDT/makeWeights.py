from ROOT import *
from array import array as afC
import KsmmMathCrap as K
import math 
from pdb import set_trace 

fData = TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/NEW/DATA/KsMB_Data2012_MVA.root")
tData = fData.Get("DecayTree")

fMC_MB = TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/NEW/MC/MB08ac_MC2012_Stripped.root")
tMC_MB = fMC_MB.Get("KsMBTuple/DecayTree")

#fMC_MuMu = TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/NEW/MC/Ksmumu_StrippedMC2012_mcMatch_MVA.root")
#tMC_MuMu = fMC_MuMu.Get("DecayTree")

binsETA = afC('d', [0,40])
binsPT = afC('d', [0,475,543,598,648,695,742,788,839,889,943,999,1063,1128,1205,1398,1726,2038,10000]) 

def fill(tree,name):
    histo = TH2D(name, name,len(binsETA)-1, binsETA,len(binsPT)-1, binsPT)
    tree.Draw("KS0_PT:sqrt(KS0_ENDVERTEX_X**2+KS0_ENDVERTEX_Y**2)>>%s" % name,"muplus_PT>250 && muminus_PT>250","NORM")
    return histo

#set_trace()
histoData=fill(tData,"hData")
print 'draw histo Data'
histoMC_MB=fill(tMC_MB,"hMC_MB")
print 'draw histo MC MB'
#histoMC_MuMu=fill(tMC_MuMu,"hMC_MuMu")
#print 'draw histo MC MuMu'

#hCorr_MC = K.hratio2(histoMC_MB,histoMC_MuMu,0)
hCorr_Data = K.hratio2(histoData,histoMC_MB,0)

output = TFile('weights.root','RECREATE')
hCorr_Data.Write()
output.Close()
