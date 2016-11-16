#! /usr/bin/env python
ErrorBSA = 10*[[0.,0.]]
ErrorBSB = 10*[[0.,0.]]
ErrorBSTOSA = 10*[[0.,0.]]
ErrorBSTOSB = 10*[[0.,0.]]

from ROOT import *
from MCLimit import *
from Bs2MuMuParams import toytable_eps_bdt as TheTable
import sys, os
sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu/")
sys.path.append("/afs/cern.ch/user/m/mbettler/public/forDiego/")
from bkg_expectations_20120617 import *
from smartpyROOT import *
from array import array as afC
from XTuple import XTuple
from SomeUtils.dataManage import rms
from scipy import double
from scipy import random as rnd
#from BsMuMuPy.pyAna.CLclass import *
from SomeUtils.alyabar import *
import signalPDF 
import bkgPDF
from array import array as afC
from functions_for_finalanalysis import *
from fiducial import *
#from log_TIS import *
#from log_TOS import *

#from bkg_patch import *
#fmma = TFile("ksmumu1fbA.root")
#fmmb = TFile("ksmumu1fbB.root")
#BREAK
## fa = TFile("ks2pipi1fbA_TIS.root")
## fb = TFile("ks2pipi1fbB_TIS.root")
## ta = fa.Get("T")
## tb = fb.Get("T")
import cPickle
epsTIS = cPickle.load(file(os.environ["HOME"] + "/vol5/ks/eps_TIS"))
epsTOS = cPickle.load(file(os.environ["HOME"] + "/vol5/ks/eps_TOS"))
#fmb = TFile("minbias.root")
#tmb = fmb.Get("T")


TIS = 0
TOS = 1
SYST = 1
PROFBKG = 0*SYST

frac_A = 3./6.8
frac_B = 3.8/6.8



#Binning = afC('d', [492,494.4,496.8,499.2,501.6,504])
Binning = afC('d', [492,504])
mw = "&& Bmass> "+ str(Binning[0]) + "&& Bmass< "+ str(Binning[-1])
alphaA = []

alphaA.append( [8.1199999999999992, 0.39000000000000001] )
alphaA.append( [8.6799999999999997, 0.53000000000000003] )
alphaA.append( [8.1100000000000012, 0.54999999999999993] )
alphaA.append( [8.2599999999999998, 0.68000000000000005] )
alphaA.append( [8.1199999999999992, 0.80999999999999994] )
alphaA.append( [6.6300000000000008, 0.59999999999999998] )
alphaA.append( [8.4100000000000001, 0.97000000000000008] )
alphaA.append( [10.299999999999999, 1.7] )
alphaA.append( [11.500000000000002, 2.0] )
alphaA.append( [16.200000000000003, 1.5000000000000002] )

alphaB = []

alphaB.append( [7.4000000000000004, 0.47999999999999998] )
alphaB.append( [8.2100000000000009, 0.52000000000000002] )
alphaB.append( [7.4599999999999991, 0.45999999999999996] )
alphaB.append( [7.4099999999999993, 0.5] )
alphaB.append( [8.6500000000000004, 0.77000000000000013] )
alphaB.append( [7.7999999999999998, 1.0999999999999999] )
alphaB.append( [8.1799999999999997, 0.75000000000000011] )
alphaB.append( [7.5500000000000007, 0.89000000000000001] )
alphaB.append( [7.6000000000000005, 1.2] )
alphaB.append( [7.9800000000000004, 0.80999999999999994] )

alphaTOSA = []
## if first bin is O(0.7), then the sample splitting is not included
## otherwise it has to be about 1.5

alphaTOSA.append( [1.9440000000000002, 0.70199999999999996] )
alphaTOSA.append( [1.8360000000000001, 0.64799999999999991] )
alphaTOSA.append( [3.3479999999999999, 1.431] )
alphaTOSA.append( [5.5350000000000001, 2.214] )
alphaTOSA.append( [2.484, 1.026] )
alphaTOSA.append( [3.8609999999999998, 1.5930000000000002] )
alphaTOSA.append( [7.830000000000001, 4.8599999999999994] )
alphaTOSA.append( [2.403, 0.97200000000000009] )
alphaTOSA.append( [2.2949999999999999, 0.999] )
alphaTOSA.append( [0.94229999999999992, 0.216] )

alphaTOSB = []

alphaTOSB.append( [0.92069999999999996, 0.23760000000000001] )
alphaTOSB.append( [2.3489999999999998, 1.026] )
alphaTOSB.append( [1.6199999999999999, 0.54000000000000004] )
alphaTOSB.append( [1.242, 0.48600000000000004] )
alphaTOSB.append( [2.5109999999999997, 1.1339999999999999] )
alphaTOSB.append( [4.5899999999999999, 3.2399999999999998] )
alphaTOSB.append( [1.998, 0.67500000000000004] )
alphaTOSB.append( [4.2389999999999999, 1.9170000000000003] )
alphaTOSB.append( [4.0499999999999998, 3.2399999999999998] )
alphaTOSB.append( [7.0199999999999996, 3.2399999999999998] )




alpha_ref = 0
for x in alphaA:
    alpha_ref+=1./x[0]
for x in alphaB:
    alpha_ref+=1./x[0]

for x in alphaTOSA:
    alpha_ref+=1./x[0]
for x in alphaTOSB:
    alpha_ref+=1./x[0]

print "alpha", 1./alpha_ref


def do_bdt_bin(x, binname = "b ksmm SA bin1", scale_to = 0., scale_by = 0.):
    h = TH1D(binname ,  binname,len(Binning)-1, Binning)
    for i in range(len(Binning)-1):
        h.SetBinContent(i+1, x[i])
    if scale_to: h.Scale(scale_to*1./h.GetSum())
    if scale_by: h.Scale(scale_by)
    return h
def do_mass_hsTIS(t,name):
    hlist = 10*[TH1F()]
    for i in range(10):
        hlist[i] = TH1F(name + "bin " + str(i+1), name + "bin " + str(i+1), len(Binning)-1, Binning)
        t2 = t.CopyTree(fiducial + mw+"&& L0Tis && Hlt1Tis && Hlt2Tis && " + name + ">"+str(epsTIS(1-0.1*i))+" && " + name +  "< " +str(epsTIS(0.9-0.1*i)))
        for entry in t2:
            hlist[i].Fill(entry.Bmass)
    return hlist

def do_mass_hsTOS(t,name):
    hlist = 10*[TH1F()]
    for i in range(10):
        hlist[i] = TH1F(name + "bin " + str(i+1), name + "bin " + str(i+1), len(Binning)-1, Binning)
        t2 = t.CopyTree(fiducialtos + mw+ aa + name + ">"+str(epsTOS(1-0.1*i))+" && " + name +  "< " +str(epsTOS(0.9-0.1*i)))
        for entry in t2:
            hlist[i].Fill(entry.Bmass)
    return hlist

NTISA = [8125L, 8629L, 9103L, 9579L, 9701L, 10111L, 9493L, 8586L, 7594L, 5124L]
#NB =[8868, 9154, 9316, 9471, 9629, 9873, 10030, 10096, 10136, 10157]
NTISB = [8807L, 9085L, 9234L, 9394L, 9559L, 9795L, 9956L, 9998L, 10043L, 10053L]

NTOSA = [1310L, 857L, 634L, 573L, 587L, 574L, 578L, 705L, 774L, 2306L]
NTOSB = [1694L, 1284L, 929L, 875L, 729L, 723L, 640L, 611L, 581L, 544L]


obsTISA =[0L, 3L, 1L, 0L, 1L, 0L, 0L, 1L, 0L, 0L]
obsTOSA =[1L, 2L, 0L, 0L, 0L, 0L, 0L, 0L, 0L, 1L]
obsTISB = [2L, 3L, 3L, 1L, 0L, 0L, 0L, 0L, 0L, 0L]
obsTOSB = [4L, 2L, 1L, 1L, 0L, 2L, 0L, 0L, 0L, 0L]

BSA = 10*[TH1F()]
BSB = 10*[TH1F()]
#SSA = do_mass_hsTIS(ta,"BDTDA")
#SSB = do_mass_hsTIS(tb,"BDTDB")
SSA = 10*[TH1F()]
SSB = 10*[TH1F()]
DSA = 10*[TH1F()]
DSB = 10*[TH1F()]

BSTOSA = 10*[TH1F()]
BSTOSB = 10*[TH1F()]
#SSTOSA = do_mass_hsTOS(tmb,"BDTDTOSA")
#SSTOSB = do_mass_hsTOS(tmb,"BDTDTOSB")
SSTOSA = 10*[TH1F()]
SSTOSB = 10*[TH1F()]
DSTOSA = 10*[TH1F()]
DSTOSB = 10*[TH1F()]

def xabs(x):
    if not x: return 0
    return abs(x)

def takeBerrors( marcothing):
    sn_stat = marcothing[1]
    sp_stat = marcothing[2]
    sn_syst = max( xabs(marcothing[3]), xabs(marcothing[4]))
    sp_syst = max( xabs(marcothing[3]), xabs(marcothing[5]))
    sn = min(sqrt( sn_stat**2 + sn_syst**2), marcothing[0])
    return [-abs(sn), sqrt(sp_stat**2 + sp_syst**2)]


dcBkgKSMM = {}
for i in range(10):
    ErrorBSA[i] = takeBerrors(vars()["ATISbin" + str(i+1)])
    ErrorBSB[i] = takeBerrors(vars()["BTISbin" + str(i+1)])
    ErrorBSTOSA[i] = takeBerrors(vars()["ATOSbin" + str(i+1)])
    ErrorBSTOSB[i] = takeBerrors(vars()["BTOSbin" + str(i+1)])
    
    BSA[i] = do_bdt_bin(vars()["ATISbin" + str(i+1)], "b ksmm SA bin" + str(i+1))
    BSB[i] = do_bdt_bin(vars()["BTISbin" + str(i+1)], "b ksmm SB bin" + str(i+1))
    BSTOSA[i] = do_bdt_bin(vars()["ATOSbin" + str(i+1)], "b ksmm STOSA bin" + str(i+1))
    BSTOSB[i] = do_bdt_bin(vars()["BTOSbin" + str(i+1)], "b ksmm STOSB bin" + str(i+1))

    SSA[i] = do_bdt_bin( [NTISA[i]], "s ksmm SA bin" + str(i+1))
    SSB[i] = do_bdt_bin( [NTISB[i]], "s ksmm SB bin" + str(i+1))
    SSTOSA[i] = do_bdt_bin( [NTOSA[i]], "s ksmm STOSA bin" + str(i+1))
    SSTOSB[i] = do_bdt_bin( [NTOSB[i]], "s ksmm STOSB bin" + str(i+1))
    ## Data
    
    DSA[i] = do_bdt_bin([obsTISA[i]], "D ksmm SA bin" + str(i+1))
    DSB[i] = do_bdt_bin([obsTISB[i]], "D ksmm SB bin" + str(i+1))
    DSTOSA[i] = do_bdt_bin([obsTOSA[i]], "D ksmm STOSA bin" + str(i+1))
    DSTOSB[i] = do_bdt_bin([obsTOSB[i]], "D ksmm STOSB bin" + str(i+1))
    ### Below you substitute data by a toy

    #DSA[i] = do_bdt_bin([int(rnd.poisson(  vars()["ATISbin" + str(i+1)] [0]))], "D ksmm SA bin" + str(i+1))
    #DSB[i] = do_bdt_bin([int(rnd.poisson(  vars()["BTISbin" + str(i+1)] [0]))], "D ksmm SB bin" + str(i+1))
    #DSTOSA[i] = do_bdt_bin([int(rnd.poisson(  vars()["ATOSbin" + str(i+1)] [0]))], "D ksmm STOSA bin" + str(i+1))
    #DSTOSB[i] = do_bdt_bin([int(rnd.poisson(  vars()["BTOSbin" + str(i+1)] [0]))], "D ksmm STOSB bin" + str(i+1))
    
    ### SYST 
    
    dcBkgKSMM["bkg KSMM SA B" + str(i+1)] = csm_template(1)
    dcBkgKSMM["bkg KSMM SA B" + str(i+1)].set_np("KSMM BKG SA ERR " + str(i+1),-abs(ErrorBSA[i][0])/BSA[i].GetSumOfWeights(), ErrorBSA[i][1]/BSA[i].GetSumOfWeights(),NULL,1., NULL, -1.)
    dcBkgKSMM["bkg KSMM SB B" + str(i+1)] = csm_template(1)
    dcBkgKSMM["bkg KSMM SB B" + str(i+1)].set_np("KSMM BKG SB ERR " + str(i+1),-abs(ErrorBSB[i][0])/BSB[i].GetSumOfWeights(), ErrorBSB[i][1]/BSB[i].GetSumOfWeights(),NULL,1., NULL, -1.)
    dcBkgKSMM["bkg KSMM STOSA B" + str(i+1)] = csm_template(1)
    dcBkgKSMM["bkg KSMM STOSA B" + str(i+1)].set_np("KSMM BKG STOSA ERR " + str(i+1),-abs(ErrorBSTOSA[i][0])/BSTOSA[i].GetSumOfWeights(), ErrorBSTOSA[i][1]/BSTOSA[i].GetSumOfWeights(),NULL,1., NULL, -1.)
    dcBkgKSMM["bkg KSMM STOSB B" + str(i+1)] = csm_template(1)
    dcBkgKSMM["bkg KSMM STOSB B" + str(i+1)].set_np("KSMM BKG STOSB ERR " + str(i+1),-abs(ErrorBSTOSB[i][0])/BSTOSB[i].GetSumOfWeights(), ErrorBSTOSB[i][1]/BSTOSB[i].GetSumOfWeights(),NULL,1., NULL, -1.)


    ## NO SYST
    dcBkgKSMM["bkg KSMM SA B" + str(i+1) + "no_syst"] = csm_template(0)  
    dcBkgKSMM["bkg KSMM SB B" + str(i+1) + "no_syst"] = csm_template(0)
    dcBkgKSMM["bkg KSMM STOSA B" + str(i+1) + "no_syst"] = csm_template(0)
    dcBkgKSMM["bkg KSMM STOSB B" + str(i+1) + "no_syst"] = csm_template(0)

    ### MAKE
    dcBkgKSMM["bkg KSMM SA B" + str(i+1)].make(BSA[i],1.,0,0,"KSMM SA B" + str(i+1))
    dcBkgKSMM["bkg KSMM SA B" + str(i+1) + "no_syst"].make(BSA[i],1.,0,0,"KSMM SA B" + str(i+1))
    dcBkgKSMM["bkg KSMM SB B" + str(i+1)].make(BSB[i],1,0,0,"KSMM SB B" + str(i+1))
    dcBkgKSMM["bkg KSMM SB B" + str(i+1) + "no_syst"].make(BSB[i],1.,0,0,"KSMM SB B" + str(i+1))
    dcBkgKSMM["bkg KSMM STOSA B" + str(i+1)].make(BSTOSA[i],1.,0,0,"KSMM STOSA B" + str(i+1))
    dcBkgKSMM["bkg KSMM STOSA B" + str(i+1) + "no_syst"].make(BSTOSA[i],1.,0,0,"KSMM STOSA B" + str(i+1))
    dcBkgKSMM["bkg KSMM STOSB B" + str(i+1)].make(BSTOSB[i],1,0,0,"KSMM STOSB B" + str(i+1))
    dcBkgKSMM["bkg KSMM STOSB B" + str(i+1) + "no_syst"].make(BSTOSB[i],1.,0,0,"KSMM STOSB B" + str(i+1))
    
#BREAK
dcKSMM = {}
#BREAK
BR_rel_err = 0.05/69.2
TIS_rel_err = .18
prsc = 2.7e-06
s_prsc = sqrt(0.7**2 + .3**2)*1e-06
prs_rel_er = s_prsc/prsc

def DoSigModel(BR, dc = dcKSMM):
    for i in range(10):
        nsA = BR*1e08/alphaA[i][0]
        nsB = BR*1e08/alphaB[i][0]

        nsTOSA = BR*1e08/alphaTOSA[i][0]
        nsTOSB = BR*1e08/alphaTOSB[i][0]

        nsTOSA = nsTOSA
        nsTOSB = nsTOSB

        ### TIS (SYST)
        
        dc[str(BR) + "KSMM SA B" + str(i+1)] = csm_template(3) 
        dc[str(BR) + "KSMM SA B" + str(i+1)].set_np("KSMM UNCORR ERR " + str(i+1),-alphaA[i][1]/alphaA[i][0], alphaA[i][1]/alphaA[i][0] ,NULL,1., NULL, -1.)
        dc[str(BR) + "KSMM SA B" + str(i+1)].set_np("Kspipi BR",-BR_rel_err , BR_rel_err  ,NULL,1., NULL, -1.)
        dc[str(BR) + "KSMM SA B" + str(i+1)].set_np("TisEff",-TIS_rel_err, TIS_rel_err ,NULL,1., NULL, -1.)
     
        
        dc[str(BR) + "KSMM SB B" + str(i+1)] = csm_template(3) 
        dc[str(BR) + "KSMM SB B" + str(i+1)].set_np("KSMM UNCORR ERR "+str(i+1),-alphaB[i][1]/alphaB[i][0], alphaB[i][1]/alphaB[i][0] ,NULL,1., NULL, -1.)
        dc[str(BR) + "KSMM SB B" + str(i+1)].set_np("Kspipi BR",-BR_rel_err , BR_rel_err  ,NULL,1., NULL, -1.)
        dc[str(BR) + "KSMM SB B" + str(i+1)].set_np("TisEff",-TIS_rel_err, TIS_rel_err ,NULL,1., NULL, -1.)

        ### TOS (SYST)
        
        dc[str(BR) + "KSMM STOSA B" + str(i+1)] = csm_template(3) 
        dc[str(BR) + "KSMM STOSA B" + str(i+1)].set_np("KSMM TOSA UNCORR ERR " + str(i+1),-alphaTOSA[i][1]/alphaTOSA[i][0], alphaTOSA[i][1]/alphaTOSA[i][0] ,NULL,1., NULL, -1.)
        dc[str(BR) + "KSMM STOSA B" + str(i+1)].set_np("Kspipi BR",-BR_rel_err , BR_rel_err  ,NULL,1., NULL, -1.)
        dc[str(BR) + "KSMM STOSA B" + str(i+1)].set_np("MB PRESCALE",-prs_rel_er, prs_rel_er ,NULL,1., NULL, -1.)
        
        dc[str(BR) + "KSMM STOSB B" + str(i+1)] = csm_template(3) 
        dc[str(BR) + "KSMM STOSB B" + str(i+1)].set_np("KSMM TOSB UNCORR ERR "+str(i+1),-alphaTOSB[i][1]/alphaTOSB[i][0], alphaB[i][1]/alphaB[i][0] ,NULL,1., NULL, -1.)
        dc[str(BR) + "KSMM STOSB B" + str(i+1)].set_np("Kspipi BR",-BR_rel_err , BR_rel_err  ,NULL,1., NULL, -1.)
        dc[str(BR) + "KSMM STOSB B" + str(i+1)].set_np("MB PRESCALE",-prs_rel_er, prs_rel_er ,NULL,1., NULL, -1.)

        ## NO SYST
        dc[str(BR) + "KSMM SA B" + str(i+1) +"no_syst"] = csm_template(0)
        dc[str(BR) + "KSMM SB B" + str(i+1) +"no_syst"] = csm_template(0)
        dc[str(BR) + "KSMM STOSA B" + str(i+1) +"no_syst"] = csm_template(0)
        dc[str(BR) + "KSMM STOSB B" + str(i+1) +"no_syst"] = csm_template(0)


        ## MAKES !!
        dc[str(BR) + "KSMM SA B" + str(i+1)].make(SSA[i], nsA*1./SSA[i].GetSumOfWeights(), 1, 1, "KSMM SA B"+str(i+1))
        dc[str(BR) + "KSMM SA B" + str(i+1) +"no_syst"].make(SSA[i], nsA*1./SSA[i].GetSumOfWeights(), 1, 1, "KSMM SA B"+str(i+1))
        
        dc[str(BR) + "KSMM SB B" + str(i+1)].make(SSB[i], nsB*1./SSB[i].GetSumOfWeights(), 1, 1, "KSMM SB B"+str(i+1))
        dc[str(BR) + "KSMM SB B" + str(i+1) +"no_syst"].make(SSB[i], nsB*1./SSB[i].GetSumOfWeights(), 1, 1, "KSMM SB B"+str(i+1))
        
        dc[str(BR) + "KSMM STOSA B" + str(i+1)].make(SSTOSA[i], nsTOSA*1./SSTOSA[i].GetSumOfWeights(), 1, 1, "KSMM STOSA B"+str(i+1))
        dc[str(BR) + "KSMM STOSA B" + str(i+1) +"no_syst"].make(SSTOSA[i], nsTOSA*1./SSTOSA[i].GetSumOfWeights(), 1, 1, "KSMM STOSA B"+str(i+1))
        
        dc[str(BR) + "KSMM STOSB B" + str(i+1)].make(SSTOSB[i], nsTOSB*1./SSTOSB[i].GetSumOfWeights(), 1, 1, "KSMM STOSB B"+str(i+1))
        dc[str(BR) + "KSMM STOSB B" + str(i+1) +"no_syst"].make(SSTOSB[i], nsTOSB*1./(SSTOSB[i].GetSumOfWeights()), 1, 1, "KSMM STOSB B"+str(i+1))
    
    return dc

tests, testpes = {}, {}
  
nulpe = csm_model()     #### This must contain ALL syst
nul = csm_model()

for i in range(10):
    if TIS: 
        dcBkgKSMM["bkg KSMM SA B" + str(i+1)].add_to(nulpe)
        dcBkgKSMM["bkg KSMM SB B" + str(i+1)].add_to(nulpe)
        if PROFBKG:
            dcBkgKSMM["bkg KSMM SA B" + str(i+1)].add_to(nul)
            dcBkgKSMM["bkg KSMM SB B" + str(i+1)].add_to(nul)
        else:
            dcBkgKSMM["bkg KSMM SA B" + str(i+1) +"no_syst"].add_to(nul)
            dcBkgKSMM["bkg KSMM SB B" + str(i+1) +"no_syst"].add_to(nul)
    if TOS:
        dcBkgKSMM["bkg KSMM STOSA B" + str(i+1)].add_to(nulpe)
        dcBkgKSMM["bkg KSMM STOSB B" + str(i+1)].add_to(nulpe)
        dcBkgKSMM["bkg KSMM STOSA B" + str(i+1) +"no_syst"].add_to(nul)
        dcBkgKSMM["bkg KSMM STOSB B" + str(i+1) +"no_syst"].add_to(nul)
print "here A"

def DoTestHyp(BR):
   
    DoSigModel(BR)
   
    test = csm_model()
    testpe = csm_model()

    for i in range(10):
        if TIS:
            dcBkgKSMM["bkg KSMM SA B" + str(i+1)].add_to(testpe)
            dcBkgKSMM["bkg KSMM SB B" + str(i+1)].add_to(testpe)
            if PROFBKG:
                dcBkgKSMM["bkg KSMM SA B" + str(i+1)].add_to(test)
                dcBkgKSMM["bkg KSMM SB B" + str(i+1)].add_to(test)
            else: 
                dcBkgKSMM["bkg KSMM SA B" + str(i+1) +"no_syst"].add_to(test)
                dcBkgKSMM["bkg KSMM SB B" + str(i+1) +"no_syst"].add_to(test)
            dcKSMM[str(BR) + "KSMM SA B" + str(i+1)].add_to(testpe)
            dcKSMM[str(BR) + "KSMM SB B" + str(i+1)].add_to(testpe)
            dcKSMM[str(BR) + "KSMM SA B" + str(i+1) +"no_syst"].add_to(test)
            dcKSMM[str(BR) + "KSMM SB B" + str(i+1) +"no_syst"].add_to(test)
            
            
        if TOS: 
            dcBkgKSMM["bkg KSMM STOSA B" + str(i+1)].add_to(testpe)
            dcBkgKSMM["bkg KSMM STOSB B" + str(i+1)].add_to(testpe)
            
            if PROFBKG:
                dcBkgKSMM["bkg KSMM STOSA B" + str(i+1)].add_to(test)
                dcBkgKSMM["bkg KSMM STOSB B" + str(i+1)].add_to(test)
            else:
                dcBkgKSMM["bkg KSMM STOSA B" + str(i+1) +"no_syst"].add_to(test)
                dcBkgKSMM["bkg KSMM STOSB B" + str(i+1) +"no_syst"].add_to(test)

            dcKSMM[str(BR) + "KSMM STOSA B" + str(i+1)].add_to(testpe)
            dcKSMM[str(BR) + "KSMM STOSB B" + str(i+1)].add_to(testpe)
            dcKSMM[str(BR) + "KSMM STOSA B" + str(i+1) +"no_syst"].add_to(test)
            dcKSMM[str(BR) + "KSMM STOSB B" + str(i+1) +"no_syst"].add_to(test)

        
    
    return testpe, test

def DoCL(BR, npe =0, syst = 1 ):
    testpes[BR], tests[BR] = DoTestHyp(BR)
  
    CL = mclimit_csm()
    CL.set_null_hypothesis(nul)
    CL.set_test_hypothesis(tests[BR])

    if syst:
        CL.set_null_hypothesis_pe(nulpe)
        CL.set_test_hypothesis_pe(testpes[BR])
    else:
        CL.set_null_hypothesis_pe(nul) #### no syst
        CL.set_test_hypothesis_pe(tests[BR])
    for i in range(10):
        if TIS:
            CL.set_datahist(DSA[i], "KSMM SA B" + str(i+1))
            CL.set_datahist(DSB[i], "KSMM SB B" + str(i+1))

        if TOS:
            CL.set_datahist(DSTOSA[i], "KSMM STOSA B" + str(i+1))
            CL.set_datahist(DSTOSB[i], "KSMM STOSB B" + str(i+1))
 
    if npe: CL.set_npe(npe)
    
    return CL

#st0 = float(sys.argv[1])

def do_scan(filename, stop_95 = False):
    tup = XTuple(filename, labels = ["BR/F","ts/F", "chi2/F", "CLs/F","CLb/F", "CLsb/F","CLs_exp_b_med/F" , "CLs_exp_b_p1/F", "CLs_exp_b_p2/F","CLs_exp_b_m1/F" ,"CLs_exp_b_m2/F","CLb_exp_s_med/F" , "CLb_exp_s_p1/F", "CLb_exp_s_p2/F","CLb_exp_s_m1/F" ,"CLb_exp_s_m2/F"])
   
    #print a2012.CHANNEL
    c90, c95 = 0.,0
    for j in range(10):
        i = 15.0 + 0.1*j
        print "ps for BR:", i
        CL = DoCL(i*1e-9 ,200000, syst=SYST)
        #CL.setpxprintflag(1)
        CL.run_pseudoexperiments()
        cl = CL.cls()
        clb = CL.clb()
        clsb = CL.clsb()
        print i,cl, clb, clsb
        tup.fillItem("BR", i)
        tup.fillItem("ts", CL.ts())
        #@tup.fillItem("chi2", CL.calc_chi2(testpes[i*1e-9],a2012.DataHist))
        tup.fillItem("CLs",cl)
        tup.fillItem("CLb",clb)
        tup.fillItem("CLsb",clsb)
        tup.fillItem("CLs_exp_b_med",CL.clsexpbmed())
        tup.fillItem("CLs_exp_b_p1",CL.clsexpbp1())
        tup.fillItem("CLs_exp_b_p2",CL.clsexpbp2())
        tup.fillItem("CLs_exp_b_m1",CL.clsexpbm1())
        tup.fillItem("CLs_exp_b_m2",CL.clsexpbm2())

        tup.fillItem("CLb_exp_s_med",CL.clbexpsmed())
        tup.fillItem("CLb_exp_s_p1",CL.clbexpsp1())
        tup.fillItem("CLb_exp_s_p2",CL.clbexpsp2())
        tup.fillItem("CLb_exp_s_m1",CL.clbexpsm1())
        tup.fillItem("CLb_exp_s_m2",CL.clbexpsm2())
        
        tup.fill()
        if cl < 0.1 and not c90: c90 = i
        if cl<0.05:
            print "C90:",c90
            print "c95:",i
            if stop_95:
                tup.close()
                return c90, i
    tup.close()



do_scan(os.environ["HOME"] + "/vol5/ks/KSMM_TOS15.0")#, stop_95 = True)
