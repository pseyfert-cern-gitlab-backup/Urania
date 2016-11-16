##TO DO:
## -change trigger category and output file name
## - histoMBNoCut and histoData: add fiducial cuts  NOT FOR NOW
## - for TISTISTOS : add trigger selection to histoData
import ROOT
from array import array as afC
from SomeUtils.alyabar import *
from fiducial import *
import KsmmMathCrap as K
import cPickle
from fillHisto import *
from itertools import *
from pdb import set_trace

tfile = ROOT.TFile.Open('Efficiencies_TOSTOS1TOS_NEW.root', 'recreate')
TRIGG_CAT = 'TosTos1Tos' #'TosTos2Tos' and 'TisTisTos'

MISID = 0

##############################################################################
############################# NTuples ##################################
##############################################################################

#DATA FOR REWEIGH
fData = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/FIT/KsMB_Data2012_MVA_small.root")   # MB 

#MC WITHOUT STRIPPING SELECTION

fMuMuNoCut = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/FIT/KsMuMu_MC_RightAcceptance.root")  #KS->mumu MC no stripping
fMBNoCut = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/FIT/MB08ac_MC2012_mcMatch_MVA_SMALL.root")    # MB MC no stripping
fMuMuGen = ROOT.TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/NEW/MC/Ksmumu_LastMC2012_mcMatch.root") # this is in the right phase space!  
fMBGen = ROOT.TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/NEW/MC/MB08ac_MC2012_mcMatch.root") 
#fmumu = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/FIT/Ksmumu_StrippedMC2012_mcMatch_MVA_SMALL.root")  
fmumu = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/FIT/Ksmumu_StrippedMC2012_mcMatch_MVA_SMALL.root")

tMuMuGen = fMuMuGen.Get("MCtruthKsmumu/MCDecayTree")
tMBGen = fMBGen.Get("MCtruthKspipi/MCDecayTree")
tMuMuNoCut = fMuMuNoCut.Get("DecayTree")
tMBNoCut = fMBNoCut.Get("DecayTree")
tMuMu = fmumu.Get("DecayTree")
tData = fData.Get("DecayTree")

#make list of tuple string->cut
def make_binned(name, cut):
    return [(name+'Bin%d' % (i+1), AND(cut, j)) for i, j in enumerate(bins)]



#HISTOS (PT AND ETA BINS): NO CUTS -  STRIPPING 
histoMuMuGen= fillHistoGen(tMuMuGen,[('hMuMuGen',noCut)])
histoMuMuNoCut= fillHisto(tMuMuNoCut,[('hMuMuNoCutTot',noCut)]+[('hMuMuNoCutStrip',strippingMuMu)])
print 'histoMuMuNoCut2D Filled'

#HISTOS (PT AND ETA BINS): NO CUTS -  STRIPPING  - CUTSC (STRIPPING + GLOBAL_TRIGG: TO CORRECT THE WEIGHTS) 

histoMBGen= fillHistoGen(tMBGen,[('hMBGen',noCut)])
histoMBNoCut= fillHisto(tMBNoCut,[('hMBNoCutTot',noCut)]+[('hMBNoCutStrip',AND(strippingMB,fiducial))])
print 'histoMBNoCut2D Filled'

#HISTOS (PT AND ETA BINS):  STRIPPING - FIDUCIAL -TRIGGER - BDT 
if TRIGG_CAT == 'TosTos1Tos':
   
    histoMuMu = fillHisto(tMuMu,[('hMuMuStrip',strippingMuMu)]+[('hMuMuFid',AND(strippingMuMu,fiducial))]+[('hMuMuTrig',AND(strippingMuMu,fiducial,trigA))] +make_binned('hMuMuSel',AND(strippingMuMu,fiducial,trigA)))
    histoData = fillHisto(tData,[('hDataTot',fiducial)])
    print 'histoMuMu filled'

elif TRIGG_CAT == 'TosTos2Tos':

    histoMuMu = fillHisto(tMuMu,[('hMuMuStrip',strippingMuMu)]+[('hMuMuFid',AND(strippingMuMu,fiducial))]+[('hMuMuTrig',AND(strippingMuMu,fiducial,trigB))]+make_binned('hMuMuSel',AND(strippingMuMu,fiducial,trigB)))
    histoData = fillHisto(tData,[('hDataTot',fiducial)])

elif TRIGG_CAT == 'TisTisTos':
    histoMuMu = fillHisto(tMuMu,[('hMuMuStrip',strippingMuMu)]+[('hMuMuFid',AND(strippingMuMu,fiducial))]+ [('hMuMuTrig',AND(strippingMuMu,fiducial,tosHLT2))]+make_binned('hMuMuSel',AND(strippingMuMu,fiducial,tosHLT2)))
    histoData = fillHisto(tData,[('hDataTot',AND(fiducial,tistis))])

print 'histoData filled'

#PUT ALL THE BDT BINS HISTOS IN A DICTIONARY (BIN from 1 to 9?)
hdict = {}
for h in histoMuMu:
  name = h.GetName()
  if 'Bin' not in name: continue
  binId = 'Bin%s' % name.split('Bin')[1]
  htype = name.split('Bin')[0]
  if binId not in hdict:
    hdict[binId] = {}
  hdict[binId][htype] = h
  print binId

 #FILL BIN0: IT CONTAINS ALL THE EVENTS THAT PASSED THE BDT SELECTION 
binIds = hdict.keys()
hdict['Bin0'] = {}
newbin = 'Bin0' 
for binId in binIds:
    info = hdict[binId]
    for htype, histo in info.iteritems():
        if htype in hdict[newbin]:
            hdict[newbin][htype].Add(histo)
        else:
            hdict[newbin][htype]  = histo.Clone('%s%s' % (htype, newbin))
        print histo.GetName(), newbin, htype, histo.Integral(), hdict[newbin][htype].Integral()


#ADD ALL THE OTHER HISTOS TO THE DICT

histoMuMuTrig = [i for i in histoMuMu if i.GetName().startswith('hMuMuTrig')]
histoMuMuFid = [i for i in histoMuMu if i.GetName().startswith('hMuMuFid')]
histoMuMuStrip = [i for i in histoMuMu if i.GetName().startswith('hMuMuStrip')]

histoMuMuNoCutStrip = [i for i in histoMuMuNoCut if i.GetName().startswith('hMuMuNoCutStrip')]
histoMBNoCutStrip = [i for i in histoMBNoCut if i.GetName().startswith('hMBNoCutStrip')]
histoMuMuNoCutTot = [i for i in histoMuMuNoCut if i.GetName().startswith('hMuMuNoCutTot')]
histoMBNoCutTot = [i for i in histoMBNoCut if i.GetName().startswith('hMBNoCutTot')]

histoMuMuGen = [i for i in histoMuMuGen if i.GetName().startswith('hMuMuGen')]
histoMBGen = [i for i in histoMBGen if i.GetName().startswith('hMBGen')]


if len(histoMuMuFid) !=1  or  len(histoMuMuStrip) !=1  or len(histoMuMuNoCutStrip) !=1 or len(histoMBNoCutStrip) !=1 or len(histoMuMuNoCutTot) !=1  or len(histoMBNoCutTot) !=1:
    raise RuntimeError('ambiguity in histoMuMuTot or histoMBTot')

hdict['Bin0']['hMuMuFid'] = histoMuMuFid[0]
hdict['Bin0']['hMuMuStrip'] = histoMuMuStrip[0]
hdict['Bin0']['hMuMuNoCutStrip'] = histoMuMuNoCutStrip[0]
hdict['Bin0']['hMBNoCutStrip'] = histoMBNoCutStrip[0]
hdict['Bin0']['hMuMuNoCutTot'] = histoMuMuNoCutTot [0]
hdict['Bin0']['hMBNoCutTot'] = histoMBNoCutTot[0]
hdict['Bin0']['hMuMuGen'] = histoMuMuGen[0]
hdict['Bin0']['hMBGen'] = histoMBGen[0]

for binId in hdict: 
    hdict[binId]['hMuMuTrig'] = histoMuMuTrig[0]


###################################################################################
############################EFFICIENCY HISTOS#################################### 
################################################################################# 

def doEffHistos(hdict):
    #BDT EFFICIENCY IN BINS - ADDED TO THE DICT
    for key1, infos in hdict.iteritems():
        for num, den, new in [
            ('hMuMuSel', 'hMuMuTrig', 'effBDTMuMu'),
            ]:
            h = K.hratio2(infos[num],infos[den],1)
            h.SetName(new+key1)
            h.SetTitle(new+key1)
            hdict[key1][new] = h

    #ADD ALL THE OTHER EFFICIENCIES TO THE DICT
    for num, den, new in [
        ('hMuMuTrig', 'hMuMuFid', 'effTrigMuMu'),
        ('hMuMuFid', 'hMuMuStrip', 'effFidMuMu'),
        ('hMuMuNoCutStrip', 'hMuMuNoCutTot', 'effStripMuMu'),
        ('hMBNoCutStrip', 'hMBNoCutTot', 'effStripMB'),
        ('hMuMuNoCutTot','hMuMuGen','effRecoMuMu'),
        ('hMBNoCutTot','hMBGen','effRecoMB')
        ]:
        print num, den, new
        h = K.hratio2(hdict['Bin0'][num],hdict['Bin0'][den],1)
        h.SetName(new+'Bin0')
        h.SetTitle(new+'Bin0')
        hdict['Bin0'][new] = h

    return hdict

hdict = doEffHistos(hdict)

#SAVE EVERYTHING

for key1, info in hdict.iteritems():
    d1 = tfile.mkdir(key1)
    for key2, histo in info.iteritems():
        d1.WriteTObject(histo, key2)
tfile.WriteTObject(histoData[0], histoData[0].GetName())        


def doEfficiencies(hdict,histoData):

    
    for binID in hdict:
        #PRODUCT OF ALL THE EFFICIENCIES AND REWEIGHT (+ CORRECTION)
        effBinMuMu = K.rec_product2(hdict['Bin0']['effTrigMuMu'],hdict[binID]['effBDTMuMu'],hdict['Bin0']['effFidMuMu'],hdict['Bin0']['effStripMuMu'],hdict['Bin0']['effRecoMuMu'])
        
        effMB = K.rec_product2(hdict['Bin0']['effStripMB'],hdict['Bin0']['effRecoMB'])
        

        ratio = K.hratio2(effBinMuMu,effMB,0)
        ratioW  = K.rec_product2(ratio,histoData[0])


        effTot, effTot_err = K.sumHisto(ratio)
        alpha, alpha_err = K.sumHisto(ratioW)
        
        print 'BIN ',binID
        print alpha,' \pm ' ,alpha_err
        print effTot,' \pm ' ,effTot_err


    return 

doEfficiencies(hdict,histoData)

