#! /usr/bin/env python

###########################
## Example script for tau->3mu limits
### For more complicated cases look at $BS2MUMUROOT/python/Bs2MuMu:
###                                   2010 analysis: analysis2010_for_Combb
###                                   2011 analysis: analysis2011_for_Comb
###                                   limit calculation: combinelimits.py
from Urania import *
AccessPackage("Bs2MuMu")

from ROOT import *
from MCLimit import *

alpha = 1.1e-08
s_alpha = 0.2e-08

SYST = 0 ## Set to 1 to run the code with systematics
######  bkg pdf (TH1D or TH2D)
#  Asmue flat in mass, 4 bins between -30 and 30 around tau mass
#  Content per BDT bin (mass integrated): 40, 8.3, 2.6  (invented numbers. Just took the sidebands and divide by 10)
######################################################################################################################

bkgpdf = TH2D("bkg pdf", "bkg pdf", 3, 0,1, 4, -30,30)

## Fill BDT bin 1,2,3 looping on mass bins

for i in range(4):
    bkgpdf.SetBinContent(1,i+1, 40 *1./4)
    bkgpdf.SetBinContent(2,i+1, 8.3 *1./4)
    bkgpdf.SetBinContent(3,i+1, 2.6 *1./4)


## Normalize

bkgpdf.Scale(1./bkgpdf.GetSum())

### Some systematics, let's assume all bins well known, but bin 3, which has 25% error.
## Make the corresponding pdf's to +- X sigmas (X ~ 2,3 if possible)


bkgpdf_u = TH2D("bkg pdf up", "bkg pdf up", 3, 0,1, 4, -30,30)
bkgpdf_d = TH2D("bkg pdf down", "bkg pdf down", 3, 0,1, 4, -30,30)

## Fill BDT bin 1,2,3 looping on mass bins

for i in range(4):
    bkgpdf_u.SetBinContent(1,i+1, 40 *1./4)
    bkgpdf_u.SetBinContent(2,i+1, 8.3 *1./4)
    bkgpdf_u.SetBinContent(3,i+1, 2.6 *1./4 *1.25)
    bkgpdf_d.SetBinContent(1,i+1, 40 *1./4)
    bkgpdf_d.SetBinContent(2,i+1, 8.3 *1./4)
    bkgpdf_d.SetBinContent(3,i+1, 2.6 *1./4 *0.75)

bkgpdf_u.Scale(1./bkgpdf_u.GetSum())
bkgpdf_d.Scale(1./bkgpdf_d.GetSum())

######## Signal pdf (TH1D or TH2D)###########################################
## Asumed flat in BDT
## Assumed symetryc peak, 10% in each 'tail' bin, 40% in each 'core' bin
#############################################################################


sigpdf = TH2D("bkg pdf", "bkg pdf", 3, 0,1, 4, -30,30)

## Loop on BDT bins
for i in range(3):
    sigpdf.SetBinContent(i+1,1,0.1)
    sigpdf.SetBinContent(i+1,2,0.4)
    sigpdf.SetBinContent(i+1,3,0.4)
    sigpdf.SetBinContent(i+1,4,0.1)


## Normalize (I always use normalized pdf's, and then give the expectation as the scale factor)
sigpdf.Scale(1./sigpdf.GetSum())

c = TCanvas()
c.Divide(2,2)
c.cd(1)
bkgpdf.Draw("TEXTBOX")
c.cd(2)
sigpdf.Draw("TEXTBOX")

## Assume signal pdf perfectly well calibrated

### Set the bkg model

bkg_no_syst = csm_template(0)   ### No systematics (used for the test statistic)
bkg = csm_template(2)   ### 2 systematics 

bkg.set_np("error pdf bin 3", 0, 0, bkgpdf_u, 3., bkgpdf_d,-3.)    ### Works as follows:  Normalization impact at +-1 sigma, pdf impact at _X_ sigma, where X is specified (here 3 and -3)
bkg.set_np("nomlization of bkg", .1, -0.1, NULL,1,NULL,-1)    ### Asume 10% overal normalization error on the bkgd.



## "make" the models
Nb = 45
bkg.make(bkgpdf, Nb ,0,0, "2011") ### Suppose 45 total events, "2011" indicates the 'channel'. Can be used for combinations
bkg_no_syst.make(bkgpdf, Nb ,0,0, "2011") ### Suppose 45 total events, "2011" indicates the 'channel'. Can be used for combinations

## make the "null" hypothesis. Typically bkg-alone, but can be SM, for example.

nul = csm_model()
nul_no_syst = csm_model()
bkg.add_to(nul)
bkg_no_syst.add_to(nul_no_syst)

##### Some dictionaries used to store models
dc = {}
dc_no_syst = {}  
test = {}
test_no_syst = {}

## Function to make a signal model for a given br hypothesis

def doSignalHyp(br, DataHist):
    """  Function to make a signal model for a given br hypothesis
    """
    
    dc_no_syst[br] = csm_template(0)
    dc[br] = csm_template(1) ### Will propagate the error on alpha
    dc[br].set_np("nomlization of sig", s_alpha/alpha, -s_alpha/alpha, NULL,1,NULL,-1)
   
    
    dc[br].make(sigpdf,br/alpha,0,1, "2011")
    dc_no_syst[br].make(sigpdf,br/alpha,0,1, "2011")
    #### Set the "test" hypothesis (S+B)
    
    test[br] = csm_model()
    test_no_syst[br] = csm_model()
    bkg.add_to(test[br])
    dc[br].add_to(test[br])
    bkg_no_syst.add_to(test_no_syst[br])
    dc_no_syst[br].add_to(test_no_syst[br])
   
   
    ### Prepare the stuff that calculates the limits
    
    CL = mclimit_csm()
    
    ## nul and test hypothesis for test statistics. If you put models with systematics here, you activate
    ## refiting of the nuisance parameters ---> computationaly QUITE expensive
    
    CL.set_null_hypothesis(nul_no_syst)  
    CL.set_test_hypothesis(test_no_syst[br])

    ## nul and test hypothesis for pseudexperiments
    if SYST:
        CL.set_null_hypothesis_pe(nul)
        CL.set_test_hypothesis_pe(test[br])
    else:
        CL.set_null_hypothesis_pe(nul_no_syst)
        CL.set_test_hypothesis_pe(test_no_syst[br])
    ### Add the observed data
    
    CL.set_datahist(DataHist, "TheData")
    CL.set_npe(800000)  #to tune the no. of pe. default is usually fine unless you have several np.
   
    CL.run_pseudoexperiments()

    cls = CL.cls()
    clb = CL.clb()
    clsb = CL.clsb()
    ts = CL.ts()
    return cls, clb, clsb, ts

#### Set data histogram
## (invented)

def doBkgToyMC(fluctuated = 1, ext_name = "", excl_t =1):
    from scipy import random as rnd
    toyMC = bkgpdf.Clone()
    toyMC.Scale(Nb)
    ###### fluctuate
    for i in range(toyMC.GetNbinsX()):
        for j in range(toyMC.GetNbinsY()):
            toyMC.SetBinContent(i+1,j+1, rnd.poisson(toyMC.GetBinContent(i+1,j+1)))
    return toyMC

DataHist = doBkgToyMC(ext_name = "2011")
c.cd(3)
### Display normalized bkg to compare to data
bdisp = bkgpdf.Clone()
bdisp.Scale(Nb)
bdisp.Draw("TEXTBOX")
c.cd(4)
DataHist.Draw("TEXTBOX")
print "prepare scan"

def do_scan():
    """ Fill a text file with the BR vs CL curve
    """
    from XTuple import XTuple

    tup = XTuple("tau23mu",["br/F","cls/F","clb/F","clsb/F","ts/F", "ns/F"])
    dc = {}
    for i in range(15):
        ns = float(.1+0.3*i)
        br = ns*alpha
        print ns, br
        cls,clb,clsb,ts = doSignalHyp(br,DataHist )
        print "still alive"
        tup.fillItem("ns",ns)
        tup.fillItem("br",br)
        tup.fillItem("cls", cls)
        tup.fillItem("clb", clb)
        tup.fillItem("clsb", clsb)
        tup.fillItem("ts", ts)
         #tup.fillItem("chi2", CL.calc_chi2(testpes[i*1e-9],a2012.DataHist))

        tup.fill()
        print " ---- DONE", cls, clb
    tup.close()
    return dc
#do_scan()
from triggerclass import *
def doWeirdPlot(yname = "clsb"):
    
    ch = channelData("tau23mu.dat", typ = "ASCII")
    x = ch.takeKey("ns")
    y = ch.takeKey(yname)
    y2 = ch.takeKey("ts")
    f1 = NF(x,y)
    d = f1.derivativeF()
    y3 = []
    for x_ in x: y3.append(-2*log(-d(x_)))
    y3m = min(y3)
    y2m = min(y2)
    y2b = []
    y3b = []
    for y_ in y2: y2b.append(y_-y2m)
    for y_ in y3: y3b.append(y_-y3m)
    f2 = NF(x, y2b)
    f3 = NF(x, y3b)
    zzz2 = f2.Draw(kBlue)
    zzz3 = f3.Draw(kRed)
    zzz2[-1].Draw("*L")
    return zzz2,zzz3
