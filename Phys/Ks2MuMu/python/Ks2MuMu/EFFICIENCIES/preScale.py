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

#fPiPi = ROOT.TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/NEW/FAKE/DATA/Ksmumu_Data2012_Stripped.root")
#fMB = ROOT.TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/wg/RD/K0SMuMu/NEW/FAKE/DATA/MB_Data2012_Stripped.root")



#tMB = fMB.Get("KsMBTuple/DecayTree")
#tPiPi = fPiPi.Get("KsPiPiTuple/DecayTree")

#n_MB = tMB.GetEntries("KS0_M>490&&KS0_M<505  && KS0_L0Global_Dec && KS0_Hlt1Phys_Dec && KS0_Hlt2Phys_Dec")
#n_PiPi = tPiPi.GetEntries("KS0_M>490&&KS0_M<505  &&  KS0_L0Global_Dec && KS0_Hlt1Phys_Dec && KS0_Hlt2Phys_Dec")


n_MB = 4.04752e+02
n_PiPi = 1.29395e+06

#n_PiPi = 932686.
#n_MB = 87.
print n_MB , n_PiPi


prescale = n_MB/(n_PiPi*1000)
err_n_MB = 2.06915e+01 #sqrt(n_MB)
err_n_PiPi = 2.75191e+03 #sqrt(n_PiPi)

#err_n_MB =9.
#err_n_PiPi = 101.
err = sqrt((err_n_MB*err_n_MB)/(n_MB*n_MB)+(err_n_PiPi*err_n_PiPi)/(n_PiPi*n_PiPi))*prescale



print prescale, '  \pm  ',err

#######################################
######################################

#TOSTOS1TOS
#old
alpha=[166.24989801909487, 132.6635450325486, 117.91065344156873, 102.16625780415451, 103.16515482482203, 82.89403323323761, 78.86775092534484, 61.105050707532996, 48.08080223145693, 41.236904467198926]

#new
#err_alpha_corr=[2.753469093169831, 2.5842128490400644, 2.506873703688295, 2.318370711447433, 2.2220627780111246, 1.973544483850779, 1.8741648601255267, 1.6275332108131555, 1.27323460663112, 0.9148687233842633]

#err_alpha_uncorr=[3.21563790124438, 3.08544025106672, 2.984994731571149, 2.9043851243172094, 2.782880178719934, 2.7080276476548844, 2.584425846238628, 2.466360800365648, 2.235277707986709, 1.9019194323196638]

#alpha=[124.50487108981083, 113.08666876845174, 106.05809674732349, 99.12137020276451, 90.6800668350199, 85.13101136573346, 76.99408578055495, 68.73848346444697, 56.047285830694605, 39.823881502955714]

#TOSTOS2TOS

#alpha=[20.415258414587402, 16.92858432030758, 16.562453157134023, 12.825871754484751, 10.467632983023796, 10.954270401998446, 10.308079839926922, 10.800863730823336, 9.613773858088528, 6.453778502512598]
err_alpha_corr =[0.45284419292313577, 0.3764449661578344, 0.3647479623257575, 0.2849589816162861, 0.23920103763592881, 0.2495016495423672, 0.24171542879860702, 0.2553395782472939, 0.22897110601877615, 0.16260789626297698]
err_alpha_uncorr =[1.298107295393286, 1.185390036957674, 1.178236643071511, 1.04507832608623, 0.9542102405058065, 0.9744096415644818, 0.9427840205142133, 0.9731768875757905, 0.9193204142834975, 0.760406307559788]

#Tististos

#alpha=[9.239111066453816, 8.817365867734383, 8.228502824343769, 8.216250886456516, 7.768170134537416, 7.710769492001914, 6.919430458689655, 6.720053164310185, 5.997290091437021, 5.036430206277053]
#err_alpha_corr =[0.3996515459768511, 0.39390797425629104, 0.38215136398778293, 0.3949383542635862, 0.3846985077608619, 0.3854980001264132, 0.35699679425440517, 0.35223031857762827, 0.31866608027450216, 0.2850643361312437]
#err_alpha_uncorr =[0.08632620922211992, 0.08561486299760458, 0.08401815363208316, 0.08477125277457623, 0.08308848048965674, 0.08309602708879292, 0.07953632259442936, 0.07877515213610983, 0.0751929877973807, 0.07027982812198667]

presc=prescale 
err_presc =err

#(e_geom,reco_mumu/ (e_reco_MB*mult_MB)) * (e_mumu/e_pipi) * (1/prescale)  *  N_MB_DATA 

e_geom_mumu= 1#0.393*0.5
err_e_geom_mumu =0# 9.31832196385e-05

e_reco_mumu= 1.
err_e_reco_mumu = 0.

e_reco_MB=1.
err_e_reco_MB=0.
 
mult_MB=1.
err_mult_MB = 0.

BF_pipi = 0.6920
err_BF_pipi = 0.0005
#for i in range (1,10):
#    n_sel.append(tMB.GetEntries(fiducial.notrig + '&& Bin == %d' % i))
#    n_selAndTISTIS.append(tMB.GetEntries(fiducial.tistis + '&& Bin == %d' % i))

lista =[]
lista_corr=[]
lista_uncorr=[]

for i in range (0,10):
    print 'Bin', i+1
    #norm = BF_pipi /((e_geom_mumu*e_reco_mumu)/(e_reco_MB*mult_MB)*(1/presc)*alpha[i])  
    norm = (BF_pipi * presc)/(e_geom_mumu*alpha[i]) 


    err_corr_norm = sqrt((err_alpha_corr[i]*err_alpha_corr[i])/(alpha[i]*alpha[i])) * norm

    err_uncorr_norm =  sqrt((err_e_geom_mumu*err_e_geom_mumu)/(e_geom_mumu*e_geom_mumu) +(err_presc*err_presc)/(presc*presc)+(err_alpha_uncorr[i]*err_alpha_uncorr[i])/(alpha[i]*alpha[i])+ (err_BF_pipi*err_BF_pipi)/(BF_pipi*BF_pipi)) * norm


    lista.append(norm)
    lista_corr.append(err_corr_norm)
    lista_uncorr.append(err_uncorr_norm)
    print norm, ' +- ',err_corr_norm,' +- ', err_uncorr_norm
print 'alpha: ', lista
print  'alpha corr err:  ', lista_corr
print 'alpha uncorr err:  ', lista_uncorr
#apply mass cut (or make a fit) - rm stripping for n_MB - add 1K




