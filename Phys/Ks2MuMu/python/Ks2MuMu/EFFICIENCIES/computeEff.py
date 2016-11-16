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
fPiPiData = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/DATA/DATA_Kspipi_TosTos1Tos.root")   #KS->pipi DATA

#MC WITHOUT STRIPPING SELECTION
#fMuMuNoCut = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_Ksmumu_TosTos1Tos.root")
fMuMuNoCut = ROOT.TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/NEW/MC/Ksmumu_MC2012_NoStripping.root")  #KS->mumu MC no stripping
fMBNoCut = ROOT.TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/NEW/MC/MB08ac_MC2012_NoStripping.root")    # MB MC no stripping
#set_trace()
#KSMUMU NEW IS STRIPPING FILTERED
if TRIGG_CAT == 'TosTos1Tos':

    #fpipi= ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_KspipiNEW_TosTos1Tos.root")
    fmumu = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_KsmumuNEW_TosTos1Tos.root")            #Ks->mumu stripped
    fmb= ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_MB_TosTos1Tos.root")                      #Ks->pipi stripped

    
elif TRIGG_CAT == 'TosTos2Tos':

    #fpipi= ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_KspipiNEW_XXX.root")
    fmumu = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_KsmumuNEW_XXX.root")                      #Ks->mumu stripped 
    fmb= ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_MB_XXX.root")                                 #Ks->pipi stripped  

elif TRIGG_CAT == 'TisTisTos':

    #fpipi= ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_KspipiNEW_XXX.root")
    fmumu = ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_KsmumuNEW_XXX.root")                   #Ks->mumu stripped  
    fmb= ROOT.TFile.Open("/afs/cern.ch/work/j/jpriscia/KSMUMU/MC/MC_MB_CCC.root")                               #Ks->pipi stripped 


tMuMu = fmumu.Get("KsMuMuTuple/DecayTree")
tMuMuNoCut = fMuMuNoCut.Get("KsmumumcMatch/DecayTree")
tMBNoCut = fMBNoCut.Get("KspipimcMatch/DecayTree")
#tPiPi = fpipi.Get("KsPiPiTuple/DecayTree")
tMB = fmb.Get("KsMBTuple/DecayTree")
tData = fPiPiData.Get("KsPiPiTuple/DecayTree")

#make list of tuple string->cut
def make_binned(name, cut):
    return [(name+'Bin%d' % (i+1), AND(cut, j)) for i, j in enumerate(bins)]


#HISTOS (PT AND ETA BINS): NO CUTS -  STRIPPING 
histoMuMuNoCut= fillHisto(tMuMuNoCut,[('hMuMuNoCutTot',noCuts)]+[('hMuMuNoCutStrip',strippingMuMu)])
print 'histoMuMuNoCut2D Filled'

#HISTOS (PT AND ETA BINS): NO CUTS -  STRIPPING  - CUTSC (STRIPPING + GLOBAL_TRIGG: TO CORRECT THE WEIGHTS) 
histoMBNoCut= fillHisto(tMBNoCut,[('hMBNoCutTot',noCuts)]+[('hMBNoCutStrip',strippingMB)]+[('hMBCorrection',cutsC)])
print 'histoMBNoCut2D Filled'

#HISTOS (PT AND ETA BINS):  STRIPPING - FIDUCIAL -TRIGGER - BDT 
if TRIGG_CAT == 'TosTos1Tos':
    histoMuMu = fillHisto(tMuMu,[('hMuMuStrip',strippingMuMu)]+[('hMuMuFid',fiducial)]+[('hMuMuTrig',AND(fiducial,tostos1tos))] +make_binned('hMuMuSel',AND(fiducial,tostos1tos)))
    print 'histoMuMu filled'

    #HISTOS (PT AND ETA BINS):  STRIPPING - FIDUCIAL -TRIGGER(=FIDUCIAL) - BDT
    histoMB = fillHisto(tMB,[('hMBStrip',strippingMB)]+[('hMBFid',fiducial)] +[('hMBTrig',fiducial)] +make_binned('hMBSel',fiducial))
    print 'histoMB filled'

elif TRIGG_CAT == 'TosTos2Tos':
    histoMuMu = fillHisto(tMuMu,[('hMuMuStrip',strippingMuMu)]+[('hMuMuFid',fiducial)]+[('hMuMuTrig',AND(fiducial,tostos2tos))]+make_binned('hMuMuSel',AND(fiducial,tostos2tos)))
    histoMB= fillHisto(tMB,[('hMBStrip',strippingMB)]+[('hMBFid',fiducial)] + [('hMBTrig',fiducial)]+ make_binned('hMBSel',fiducial))

elif TRIGG_CAT == 'TisTisTos':
    histoMuMu = fillHisto(tMuMu,[('hMuMuStrip',strippingMuMu)]+[('hMuMuFid',fiducial)]+ [('hMuMuTrig',AND(fiducial,tististos))]+make_binned('hMuMuSel',AND(fiducial,tististos)))
    histoMB = fillHisto(tMB,[('hMBStrip',stripping)]+[('hMBFid',fiducial)]+[('hMBTrig',AND(fiducial,tistis))]+make_binned('hMBSel',AND(fiducial,tistis)))


# HISTO DATA FOR REWEIGH (= NO CUTS)
histoData = fillHisto(tData,[('hDataTot',noCuts)])
print 'histoData filled'

#PUT ALL THE BDT BINS HISTOS IN A DICTIONARY 
hdict = {}
for h in chain(histoMuMu,histoMB):
  name = h.GetName()
  if 'Bin' not in name: continue
  binId = 'Bin%s' % name.split('Bin')[1]
  htype = name.split('Bin')[0]
  if binId not in hdict:
    hdict[binId] = {}
  hdict[binId][htype] = h
  print binId

 #FILL Bin0: IT CONTAINS ALL THE EVENTS THAT PASSED THE BDT SELECTION AND ADDS IT TO THE DICT
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
histoMBTrig = [i for i in histoMB if i.GetName().startswith('hMBTrig')]
histoMuMuFid = [i for i in histoMuMu if i.GetName().startswith('hMuMuFid')]
histoMBFid = [i for i in histoMB if i.GetName().startswith('hMBFid')]
histoMuMuStrip = [i for i in histoMuMu if i.GetName().startswith('hMuMuStrip')]
histoMBStrip = [i for i in histoMB if i.GetName().startswith('hMBStrip')]
histoMuMuNoCutStrip = [i for i in histoMuMuNoCut if i.GetName().startswith('hMuMuNoCutStrip')]
histoMBNoCutStrip = [i for i in histoMBNoCut if i.GetName().startswith('hMBNoCutStrip')]
histoMuMuNoCutTot = [i for i in histoMuMuNoCut if i.GetName().startswith('hMuMuNoCutTot')]
histoMBNoCutTot = [i for i in histoMBNoCut if i.GetName().startswith('hMBNoCutTot')]
histoMBCorrection = [i for i in histoMBNoCut if i.GetName().startswith('hMBCorrection')]
#
#if len(histoMuMuFid) !=1 or len(histoMBFid) !=1 or  len(histoMuMuStrip) !=1 or len(histoMBStrip) !=1 or len(histoMuMuNoCutStrip) !=1 or len(histoMBNoCutStrip) !=1 or len(histoMuMuNoCutTot) !=1  or len(histoMBNoCutTot) !=1 or  len(histoMBCorrection) !=1:
#    raise RuntimeError('ambiguity in histoMuMuTot or histoMBTot')

hdict['Bin0']['hMuMuFid'] = histoMuMuFid[0]
hdict['Bin0']['hMBFid'] = histoMBFid[0]
hdict['Bin0']['hMuMuStrip'] = histoMuMuStrip[0]
hdict['Bin0']['hMBStrip'] = histoMBStrip[0]
hdict['Bin0']['hMuMuNoCutStrip'] = histoMuMuNoCutStrip[0]
hdict['Bin0']['hMBNoCutStrip'] = histoMBNoCutStrip[0]
hdict['Bin0']['hMuMuNoCutTot'] = histoMuMuNoCutTot [0]
hdict['Bin0']['hMBNoCutTot'] = histoMBNoCutTot[0]
hdict['Bin0']['hMBCorrection'] = histoMBCorrection[0]

for binId in hdict: 
    hdict[binId]['hMuMuTrig'] = histoMuMuTrig[0]
    hdict[binId]['hMBTrig'] = histoMBTrig[0] 

###################################################################################
############################EFFICIENCY HISTOS#################################### 
################################################################################# 

def doEffHistos(hdict):
    #BDT EFFICIENCY IN BINS - ADDED TO THE DICT
    for key1, infos in hdict.iteritems():
        for num, den, new in [
            ('hMuMuSel', 'hMuMuTrig', 'effBDTMuMu'),
            ('hMBSel', 'hMBTrig', 'effBDTMB'),
            ]:
            h = K.hratio2(infos[num],infos[den])
            h.SetName(new+key1)
            h.SetTitle(new+key1)
            hdict[key1][new] = h

    #ADD ALL THE OTHER EFFICIENCIES TO THE DICT
    for num, den, new in [
        ('hMuMuTrig', 'hMuMuFid', 'effTrigMuMu'),
        ('hMBTrig', 'hMBFid', 'effTrigMB'),
        ('hMuMuFid', 'hMuMuStrip', 'effFidMuMu'),
        ('hMBFid', 'hMBStrip', 'effFidMB'),
        ('hMuMuNoCutStrip', 'hMuMuNoCutTot', 'effStripMuMu'),
        ('hMBNoCutStrip', 'hMBNoCutTot', 'effStripMB'),
        ('hMBCorrection', 'hMBNoCutTot', 'effCorrMB'), #this has to be Tot/Corr
        ]:
        h = K.hratio2(hdict['Bin0'][num],hdict['Bin0'][den])
        h.SetName(new+'Bin0')
        h.SetTitle(new+'Bin0')
        hdict['Bin0'][new] = h

    return hdict

hdict = doEffHistos(hdict)

#SAVE EVERYTHING
tfile = ROOT.TFile.Open('histosEfficiencies.root', 'recreate')
for key1, info in hdict.iteritems():
    d1 = tfile.mkdir(key1)
    for key2, histo in info.iteritems():
        d1.WriteTObject(histo, key2)
tfile.WriteTObject(histoData[0], histoData[0].GetName())        

#c = ROOT.TCanvas()
#hdict['qualcosa']['qualcosaltro'].Draw('text')




def doEfficiencies(hdict,histoData,histoMuMu,histoMB,histoMuMuNoCut):
    
    for binID in hdict:
        #set_trace()
        #PRODUCT OF ALL THE EFFICIENCIES AND REWEIGHT (+ CORRECTION)
        effProdMuMu = K.rec_product2(hdict['Bin0']['effTrigMuMu'],hdict[binID]['effBDTMuMu'],hdict['Bin0']['effFidMuMu'],hdict['Bin0']['effStripMuMu'])
        effProdMuMuWeighted  = K.rec_product2(effProdMuMu,histoData[0])#,hdict['Bin0']['effCorrMB'])

        #IDEM FOR MB
        effProdMB = K.rec_product2(hdict['Bin0']['effTrigMB'],hdict[binID]['effBDTMB'],hdict['Bin0']['effFidMB'],hdict['Bin0']['effStripMB'])
        effProdMBWeighted  = K.rec_product2(effProdMB,histoData[0])#,hdict['Bin0']['effCorrMB'])

        sumEffMuMu, errSumEffMuMu = K.sumHisto(effProdMuMuWeighted)
        sumEffMB, errSumEffMB = K.sumHisto(effProdMBWeighted)


        print  sumEffMuMu, errSumEffMuMu, sumEffMB, errSumEffMB

    
    for i in hdict:
        for j in hdict[i]:
            h = hdict[i][j].Clone()
            print 'histo: ', h.GetName()
            for pt in range(h.GetNbinsX()):
                for eta in range(h.GetNbinsY()):
                    x = h.GetBinContent(pt+1,eta+1)
                    y = h.GetBinError(pt+1,eta+1)
                    print 'pt:  ', pt, '   eta:  ', eta, ' bin Content:  ', x, ' \pm ', y 


    return  #sumEffMuMu, errSumEffMuMu, sumEffMB, errSumEffMB



doEfficiencies(hdict,histoData,histoMuMu,histoMB,histoMuMuNoCut)

