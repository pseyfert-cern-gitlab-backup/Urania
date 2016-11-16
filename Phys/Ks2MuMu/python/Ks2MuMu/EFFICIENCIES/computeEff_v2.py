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


TRIGG_CAT = 'TosTos1Tos' #'TosTos2Tos' and 'TisTisTos'

MISID = 0

##############################################################################
############################# NTuples ##################################
##############################################################################

#DATA FOR REWEIGH
fData = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/DATA/DATA_Kspipi_TosTos1Tos.root")   # Ks->pipi TISTISTIS or MB

#MC WITHOUT STRIPPING SELECTION

fMuMuNoCut = ROOT.TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/NEW/MC/Ksmumu_MC2012_NoStripping.root")  #KS->mumu MC no stripping
fMBNoCut = ROOT.TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/NEW/MC/MB08ac_MC2012_NoStripping.root")    # MB MC no stripping

#KSMUMU NEW IS STRIPPING FILTERED
if TRIGG_CAT == 'TosTos1Tos':
    fmumu = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_KsmumuNEW_TosTos1Tos.root")      #Ks->mumu MC stripped with BDT binning
    
elif TRIGG_CAT == 'TosTos2Tos':
    fmumu = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_KsmumuNEW_XXX.root")             #Ks->mumu MC stripped with BDT binning  

elif TRIGG_CAT == 'TisTisTos':
    fmumu = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_KsmumuNEW_XXX.root")             #Ks->mumu MC stripped with BDT binning  


tMuMu = fmumu.Get("KsMuMuTuple/DecayTree")
tMuMuNoCut = fMuMuNoCut.Get("KsmumumcMatch/DecayTree")
tMBNoCut = fMBNoCut.Get("KspipimcMatch/DecayTree")
tData = fData.Get("KsPiPiTuple/DecayTree")

#make list of tuple string->cut
def make_binned(name, cut):
    return [(name+'Bin%d' % (i+1), AND(cut, j)) for i, j in enumerate(bins)]


#HISTOS (PT AND ETA BINS): NO CUTS -  STRIPPING 
histoMuMuNoCut= fillHisto(tMuMuNoCut,[('hMuMuNoCutTot',noCuts)]+[('hMuMuNoCutStrip',strippingMuMu)])
print 'histoMuMuNoCut2D Filled'

#HISTOS (PT AND ETA BINS): NO CUTS -  STRIPPING  - CUTSC (STRIPPING + GLOBAL_TRIGG: TO CORRECT THE WEIGHTS) 
histoMBNoCut= fillHisto(tMBNoCut,[('hMBNoCutTot',noCuts)]+[('hMBNoCutStrip',strippingMB)])
print 'histoMBNoCut2D Filled'

#HISTOS (PT AND ETA BINS):  STRIPPING - FIDUCIAL -TRIGGER - BDT 
if TRIGG_CAT == 'TosTos1Tos':
    histoMuMu = fillHisto(tMuMu,[('hMuMuStrip',strippingMuMu)]+[('hMuMuFid',fiducial)]+[('hMuMuTrig',AND(fiducial,tostos1tos))] +make_binned('hMuMuSel',AND(fiducial,tostos1tos)))
    print 'histoMuMu filled'

elif TRIGG_CAT == 'TosTos2Tos':
    histoMuMu = fillHisto(tMuMu,[('hMuMuStrip',strippingMuMu)]+[('hMuMuFid',fiducial)]+[('hMuMuTrig',AND(fiducial,tostos2tos))]+make_binned('hMuMuSel',AND(fiducial,tostos2tos)))

elif TRIGG_CAT == 'TisTisTos':
    histoMuMu = fillHisto(tMuMu,[('hMuMuStrip',strippingMuMu)]+[('hMuMuFid',fiducial)]+ [('hMuMuTrig',AND(fiducial,tististos))]+make_binned('hMuMuSel',AND(fiducial,tististos)))

# HISTO DATA FOR REWEIGH (= NO CUTS)
histoData = fillHisto(tData,[('hDataTot',noCuts)])
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


if len(histoMuMuFid) !=1  or  len(histoMuMuStrip) !=1  or len(histoMuMuNoCutStrip) !=1 or len(histoMBNoCutStrip) !=1 or len(histoMuMuNoCutTot) !=1  or len(histoMBNoCutTot) !=1:
    raise RuntimeError('ambiguity in histoMuMuTot or histoMBTot')

hdict['Bin0']['hMuMuFid'] = histoMuMuFid[0]
hdict['Bin0']['hMuMuStrip'] = histoMuMuStrip[0]
hdict['Bin0']['hMuMuNoCutStrip'] = histoMuMuNoCutStrip[0]
hdict['Bin0']['hMBNoCutStrip'] = histoMBNoCutStrip[0]
hdict['Bin0']['hMuMuNoCutTot'] = histoMuMuNoCutTot [0]
hdict['Bin0']['hMBNoCutTot'] = histoMBNoCutTot[0]

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
        ]:
        h = K.hratio2(hdict['Bin0'][num],hdict['Bin0'][den],1)
        h.SetName(new+'Bin0')
        h.SetTitle(new+'Bin0')
        hdict['Bin0'][new] = h

    return hdict

hdict = doEffHistos(hdict)

#SAVE EVERYTHING
tfile = ROOT.TFile.Open('histosEfficiencies_v2.root', 'recreate')
for key1, info in hdict.iteritems():
    d1 = tfile.mkdir(key1)
    for key2, histo in info.iteritems():
        d1.WriteTObject(histo, key2)
tfile.WriteTObject(histoData[0], histoData[0].GetName())        


def doEfficiencies(hdict,histoData):

    
    for binID in hdict:
        #PRODUCT OF ALL THE EFFICIENCIES AND REWEIGHT (+ CORRECTION)
        effBinMuMu = K.rec_product2(hdict['Bin0']['effTrigMuMu'],hdict[binID]['effBDTMuMu'],hdict['Bin0']['effFidMuMu'],hdict['Bin0']['effStripMuMu'])
        norm = K.hratio2(effBinMuMu,hdict['Bin0']['effStripMB'],0)
        normFin  = K.rec_product2(norm,histoData[0])


        effTot, effTot_err = K.sumHisto(norm)
        alpha, alpha_err = K.sumHisto(normFin)
        
        print 'BIN ',binID
        print alpha,' \pm ' ,alpha_err
        #print effTot,' \pm ' ,effTot_err



    #for i in hdict:
    #    for j in hdict[i]:
    #        h = hdict[i][j].Clone()
    #        print 'histo: ', h.GetName()
    #        for pt in range(h.GetNbinsX()):
    #            for eta in range(h.GetNbinsY()):
    #                x = h.GetBinContent(pt+1,eta+1)
    #                y = h.GetBinError(pt+1,eta+1)
    #                print 'pt:  ', pt, '   eta:  ', eta, ' bin Content:  ', x, ' \pm ', y 


    return 

doEfficiencies(hdict,histoData)



#same selection efficiency fot the TISTIS case too. but you have to dived then! (normalize to Kspipi MB & TISTIS)
