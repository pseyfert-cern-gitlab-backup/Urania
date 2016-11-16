#dumb script to compute the  prescale factor

import ROOT
from fiducial import *
from array import array as afC
from SomeUtils.alyabar import *
from cuts import *
import KsmmMathCrap as K
import cPickle
from fillHisto import *
from itertools import *
from pdb import set_trace

fMB = ROOT.TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/xxxxxxxx")
fPiPi = ROOT.TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/xxxxxxx")

tMB = fMB.Get("xxxxx/DecayTree")
tPiPi = fPiPi.Get("xxxxxx/DecayTree")

n_MB = tMB.GetEntries("KS0_L0Global_Dec==1 && KS0_Hlt1Global_Dec==1 && KS0_Hlt2Global_Dec==1")
n_PiPi = tPiPi.GetEntries("StrippingKS02MuMuNoMuIDLineDecision==1")

prescale = n_MB/(n_PiPi*1000.)
err_n_MB = sqrt(n_MB)
err_n_PiPi = sqrt(n_PiPi)

err = sqrt((err_n_MB*err_n_MB)/(n_MB*n_MB)+(err_n_PiPi*err_n_PiPi)/(n_PiPi*n_PiPi))* prescale

print prescale, '  \pm  ',err

#######################################
######################################

alpha=[]
alpha_err_corr =[]
alpha_err_uncorr =[]
n_sel=[]
n_selAndTISTIS=[]

for i in range (1,10):
    n_sel.append(tMB.GetEntries(fiducial.notrig + '&& Bin == %d' % i))
    n_selAndTISTIS.append(tMB.GetEntries(fiducial.tistis + '&& Bin == %d' % i))


#apply mass cut (or make a fit) - rm stripping for n_MB - add 1K
