from ROOT import *
from array import array as afC
from SomeUtils.alyabar import *
from fiducial import *
import histoTex as M
import KsmmMathCrap as K
import cPickle

mK0 = 497.614
BDTNAME = "BDTDTOSB"
MISID = 1
ptbins = afC('d', [150,650,1000,2500])
ybins = afC('d' , [2,2.5,3,3.5,4, 4.5])

#ptbins = afC('d', [0,150,650,1000,2500,4000])
#ybins = afC('d' , [0,2,2.5,3,3.5,4, 4.5,7])

def isPromptish(t): return abs(t.mc_myv_z) <100 and abs(t.mc_myv_x)<.05 and abs(t.mc_myv_y)<.05
isPrompt = isPromptish
epsTOS = cPickle.load(file("eps_TOS"))
epsTIS = cPickle.load(file("eps_TIS"))
if "TOS" in BDTNAME:
    eps = epsTOS
    fiducial = fiducialtos
else: eps = epsTIS

###########################
##                       ##
## Data Min Bias NTuple ##
##                       ##
###########################

fmb = TFile("minbias.root")
tmb2 = fmb.Get("T")

#################
##             ##
##  MC NTuples ##
##             ##
#################

if MISID:
    fpipiMCT = TFile("KsPiPi_MC11_tisstudies_ntuples.root")
    fpipi = TFile("~/vol5/ks/kspipi_misid11.root")
else: 
    fpipiMCT = TFile("KsPiPi_MC11_ntuples.root")
    fpipi = TFile("~/vol5/ks/kspipimc11.root")
fmumuMCT = TFile("KsMuMu_MC11_ntuples.root")
fmumu = TFile("~/vol5/ks/ksmmmc11.root")

tpipiMCT = fpipiMCT.Get("Kspipi_mct")
tmumuMCT = fmumuMCT.Get("Ksmumu_mct")
#tpipiR = fpipiMCT.Get("Kspipi")
tmumu2 = fmumu.Get("T")
tpipi2 = fpipi.Get("T")

#################
##             ##
## Apply cuts  ##
##             ##
#################


f_trash = TFile("/tmp/eraseme.root","recreate")
tpipi = tpipi2.CopyTree(fiducial + aa + BDTNAME+ ">0.2")#+str(eps(0.2))+" && " + BDTNAME+ " < " +str(eps(0.1)))
tmumu = tmumu2.CopyTree(fiducial + aa + BDTNAME+ ">0.2")#+str(eps(0.2))+" && " + BDTNAME+ " < " +str(eps(0.1)))
#BREAK

tmb = tmb2.CopyTree(fiducial + "&&" + BDTNAME+ ">0.2")#+str(eps(0.2))+" && " + BDTNAME+ " < " +str(eps(0.1)))


###################################
##                               ##
## Reference Xsection histograms ##
##                               ##
###################################

## Magnet Up

hrefU = TH2F("spRU","spRU",len(ptbins)-1, ptbins, len(ybins)-1,ybins)

hrefU.SetBinContent(1,1,4715) , hrefU.SetBinContent(1,2,4893), hrefU.SetBinContent(1,3,4603), hrefU.SetBinContent(1,4,4252), hrefU.SetBinContent(1,5,3906)
hrefU.SetBinContent(2,1,2096), hrefU.SetBinContent(2,2,2040), hrefU.SetBinContent(2,3,1893), hrefU.SetBinContent(2,4,1717), hrefU.SetBinContent(2,5,1495)
hrefU.SetBinContent(3,1,2040), hrefU.SetBinContent(3,2,1969), hrefU.SetBinContent(3,3,1798), hrefU.SetBinContent(3,4,1546), hrefU.SetBinContent(3,5,1306)

hrefU.SetBinError(1,1,75) , hrefU.SetBinError(1,2,23), hrefU.SetBinError(1,3,13), hrefU.SetBinError(1,4,12), hrefU.SetBinError(1,5,20)
hrefU.SetBinError(2,1,26), hrefU.SetBinError(2,2,11), hrefU.SetBinError(2,3,9), hrefU.SetBinError(2,4,8), hrefU.SetBinError(2,5,12)
hrefU.SetBinError(3,1,19), hrefU.SetBinError(3,2,11), hrefU.SetBinError(3,3,12), hrefU.SetBinError(3,4,10), hrefU.SetBinError(3,5,14)


### Magnet Down

hrefD = TH2F("spRD","spRD",len(ptbins)-1, ptbins, len(ybins)-1,ybins)

hrefD.SetBinContent(1,1,2349), hrefD.SetBinContent(1,2,2465), hrefD.SetBinContent(1,3,2290), hrefD.SetBinContent(1,4,2104), hrefD.SetBinContent(1,5,1951)
hrefD.SetBinContent(2,1,1044), hrefD.SetBinContent(2,2,1024), hrefD.SetBinContent(2,3,945), hrefD.SetBinContent(2,4,841), hrefD.SetBinContent(2,5,749)
hrefD.SetBinContent(3,1,1002), hrefD.SetBinContent(3,2,984), hrefD.SetBinContent(3,3,889), hrefD.SetBinContent(3,4,743), hrefD.SetBinContent(3,5,621)

hrefD.SetBinError(1,1,41), hrefD.SetBinError(1,2,13), hrefD.SetBinError(1,3,7), hrefD.SetBinError(1,4,7), hrefD.SetBinError(1,5,11)
hrefD.SetBinError(2,1,14), hrefD.SetBinError(2,2,6), hrefD.SetBinError(2,3,6), hrefD.SetBinError(2,4,5), hrefD.SetBinError(2,5,7)
hrefD.SetBinError(3,1,10), hrefD.SetBinError(3,2,6), hrefD.SetBinError(3,3,6), hrefD.SetBinError(3,4,5), hrefD.SetBinError(3,5,7)

#href.Scale(1./href.GetSum())
def fillH_MCT(t, name, BREAK = -1):
    h = TH2F(name,name,len(ptbins)-1,ptbins,len(ybins)-1,ybins)
    hpt = TH1F(name + "_pt",name + "_pt",100,0,4000)
    N = 0
    for entry in t:
        if entry.mc_ks_pz<0: continue
        if entry.decayType != 2: continue
        if not isPrompt(entry):  continue
        if entry.mc_sv_z> 1000:  continue
        if sqrt(entry.mc_sv_x**2+entry.mc_sv_y**2)> 30: continue
        
        p = vector(entry.mc_ks_px, entry.mc_ks_py,entry.mc_ks_pz)
        pt = vtmod(p)
        hpt.Fill(pt)

        E = sqrt(mK0**2 + vmod(p)**2)
        pz = p[2]
        if pz < 0: continue
        y = 0.5*log( (E+pz)/(E-pz))  
        h.Fill(pt, y)
        N += 1
        if N == BREAK: break

    return h, hpt


def fillH(t2, name, cuts = ""):
    h = TH2F(name,name,len(ptbins)-1,ptbins,len(ybins)-1,ybins)
    hpt = TH1F(name + "_pt",name + "_pt",100,0,4000)
    f_w = TFile("/tmp/crap","recreate")
    t = t2.CopyTree(cuts)
    #if t.GetEntries()!= t.GetEntries("str_match"): print "WARNING: STP mismatch"
    for entry in t:
        p = vector(entry.mu1p1 + entry.mu2p1,entry.mu1p2 + entry.mu2p2 ,entry.mu1p3 + entry.mu2p3)#, entry.mc_ks_py,entry.mc_ks_pz)
        pt = vtmod(p)
        hpt.Fill(pt)
        E = sqrt(mK0**2 + vmod(p)**2)
        pz = p[2]
        if pz <0 : continue
        y = 0.5*log( (E+pz)/(E-pz))
        h.Fill(pt, y)
    f_w.Close()    
    return h, hpt


hsel, hsel_pt = fillH(tpipi,"pipi", "")
hmsel, hmsel_pt = fillH(tmumu,"mm","")



hT, h_pt = fillH_MCT(tpipiMCT, "pipiMCT")#, BREAK = 10*hsel.GetSum())
hmT, hm_pt = fillH_MCT(tmumuMCT, "mmMCT")#, BREAK = 10*hmsel.GetSum())

###

# 2D map efficiencies and ratios


## Build an alternate ref
hmb, hmb_pt = fillH(tmb,"mb")
sigma_corr = K.hratio2(hmb,hsel)  ### MB  / pipi Sel
sigma = K.product2(sigma_corr, hT) ### MB / pipi sel * pipi MC
# compare to ref
#sigmaX = K.hratio2(sigma,href) 
def doMC_eff(hsel,hmsel):
    sel_eff_pipi = K.hratio2(hsel,hT)
    sel_eff_mumu = K.hratio2(hmsel,hmT)
    sel_ratio = K.hratio2(sel_eff_pipi,sel_eff_mumu)
    return sel_ratio, sel_eff_pipi, sel_eff_mumu

#### Sart making efficiencies using a given ref

def do_effs(href, sel_ratio, hsel, hmsel):
    eff_h = K.product2(sel_ratio, href)
    q1, q2 = K.sumHisto(eff_h)
    sumw = 0
    for i in range(eff_h.GetNbinsX()):
        for j in range(eff_h.GetNbinsY()):
            if eff_h.GetBinContent(i+1,j+1): sumw+= href.GetBinContent(i+1,j+1)
    q1 = q1*1./sumw
    q2 = q2*1./sumw
    PC = 1-MISID*0.9
    emc1 = (PC*hsel.GetSumOfWeights()*1./hT.GetSumOfWeights())
    emc2 = (hmsel.GetSumOfWeights()*1./hmT.GetSumOfWeights())
    print hmsel.GetSumOfWeights(), hsel.GetSumOfWeights()
    print emc1, emc2
    print "efficiency ratio (MC)", emc1 / emc2
    print "efficiency ratio (MC) full space (skrewed)", (PC*hsel.GetSum()*1./hT.GetSum())/ (hmsel.GetSum()*1./hmT.GetSum())
    print "efficiency ratio (DATA)", PC*q1, PC*q2
    return PC*q1, PC*q2



def BDT_efficiency_table(bdt, eps, href, mumucuts = "(1>0)" ):
    cuts = fiducial
    if "TOS" in bdt:
        print "TOS"
        cuts = fiducialtos
    h = TH1F("A","A", 10,0,1)
    for i in range(10):
        x = 0.1*i
        hsel, hsel_pt = fillH(tpipi,"pipi", cuts + aa + bdt + ">" + str(eps(1-x)) + aa + bdt + "<" + str(eps(1-x-0.1)))
        hmsel, hmsel_pt = fillH(tmumu,"mm", cuts + aa + mumucuts + aa + bdt + ">" + str(eps(1-x)) + aa + bdt + "<" + str(eps(1-x-0.1)))
        shit = doMC_eff(hsel,hmsel)
        ef, sef = do_effs(href, shit[0], hsel, hmsel)
        h.SetBinContent(i+1,ef)
        h.SetBinError(i+1,sef)
        
    return h
    

#wght1 = "(0.292553 + (-0.000149493)*sqrt(mc_ks_px^2+mc_ks_py^2) +  ( 1.2067e-06)*sqrt(mc_ks_px^2+mc_ks_py^2)^2"
#wght1 += "+ ( -1.32673e-09)*sqrt(mc_ks_px^2+mc_ks_py^2)^3 +  (6.30603e-13)*sqrt(mc_ks_px^2+mc_ks_py^2)^4 +  (-1.3911e-16)*sqrt(mc_ks_px^2+mc_ks_py^2)^5"
#wght1 += "+( 1.16124e-20)*sqrt(mc_ks_px^2+mc_ks_py^2)^6)"

#M.doTex(href)
#M.doTex(sel_ratio)

def diagnosis():
    c = TCanvas()
    c.Divide(2,2)
    c.cd(1)
    hT.Draw("TEXTBOX")
    c.cd(2)
    hmT.Draw("TEXTBOX")
    c.cd(3)
    hsel.Draw("TEXTBOX")
    c.cd(4)
    hmsel.Draw("TEXTBOX")
    return c

def diagnosis_eff():
    c = TCanvas()
    c.Divide(2,2)
    c.cd(1)
    sel_eff_pipi.Draw("TEXTBOX")
    c.cd(2)
    sel_eff_mumu.Draw("TEXTBOX")
    c.cd(3)
    sel_ratio.Draw("TEXTBOX")
    c.cd(4)
    #hmsel.Draw("TEXTBOX")
    return c
def doBDTH(t,eps, cuts, bdt):
    h = TH1F("A","A", 10,0,1)
    for i in range(10):
        x = 0.1*i
        h.SetBinContent(i+1, t.GetEntries(cuts + aa + bdt + ">" + str(eps(1-x)) + aa + bdt + "<" + str(eps(1-x-0.1))))
    return h

def doBDTHs():
    hpipiTIS = doBDTH(tpipi,epsTIS, fiducial + aa + "!mu1ismu && !mu2ismu", "BDTDA")
    hmumuTIS = doBDTH(tmumu,epsTIS, fiducial + aa + "mu1ismu && mu2ismu", "BDTDA")
    hmbTIS = doBDTH(tmb,epsTIS, fiducial + aa + "!mu1ismu && !mu2ismu", "BDTDA")

    hpipiTOS = doBDTH(tpipi,epsTOS, fiducialtos + aa + "!mu1ismu && !mu2ismu", "BDTDTOSA")
    hmumuTOS = doBDTH(tmumu,epsTOS, fiducialtos + aa + tos + aa + "mu1ismu && mu2ismu", "BDTDTOSA")
    hmbTOS = doBDTH(tmb,epsTOS, fiducialtos + aa + "!mu1ismu && !mu2ismu", "BDTDTOSA")

   
    hpipiTIS.Scale(hmumuTIS.GetSum()*1/hpipiTIS.GetSum())
    hpipiTOS.Scale(hmumuTOS.GetSum()*1/hpipiTOS.GetSum())
    hmbTIS.Scale(hmumuTIS.GetSum()*1/hmbTIS.GetSum())
    hmbTOS.Scale(hmumuTOS.GetSum()*1/hmbTOS.GetSum())
    
    hpipiTIS.SetLineWidth(3), hmumuTIS.SetLineWidth(3), hmbTIS.SetLineWidth(3)
    hpipiTOS.SetLineWidth(3), hmumuTOS.SetLineWidth(3), hmbTOS.SetLineWidth(3)
    hpipiTIS.SetLineColor(kRed), hmbTIS.SetLineColor(kBlack)
    hpipiTOS.SetLineColor(kRed), hmbTOS.SetLineColor(kBlack)
    hmumuTIS.SetMinimum(0)
    hmumuTOS.SetMinimum(0)
    
    c = TCanvas()
    c.Divide(2,1)
    c.cd(1)

    hmumuTIS.Draw("err")
    hpipiTIS.Draw("same")
    hmbTIS.Draw("same")

    c.cd(2)
    hmumuTOS.Draw("err")
    hpipiTOS.Draw("same")
    hmbTOS.Draw("same")

    return c, hpipiTIS, hpipiTOS, hmumuTIS, hmumuTOS, hmbTIS, hmbTOS
    

eff = BDT_efficiency_table(BDTNAME, epsTOS, hrefD)
M.doTex1(eff)
for i in range(eff.GetNbinsX()):
    print "eoff" +  BDTNAME[-1] +".append(["+str(eff.GetBinContent(i+1)) +","+str(eff.GetBinError(i+1))+"])"

def doMass(sm, cuts):
    fiducial = cuts
    smM = "((Bmass -497.7)*"+str(sm) + " + 497.7)"
    mW = smM +">492 && " + smM +"<504"
    epi = tpipi2.GetEntries(mW + aa + fiducial) *1./tpipi2.GetEntries(fiducial)
    emu = tmumu2.GetEntries(mW + aa + fiducial + "&& mu1ismu && mu2ismu") *1./tmumu2.GetEntries(fiducial+ "&& mu1ismu && mu2ismu")
    print tmumu2.GetEntries(fiducial+ "&& mu1ismu && mu2ismu")
    print tpipi2.GetEntries(fiducial)
    print epi, emu, epi/emu


def ratioPlot(varname, binning,hname):
    tpipiMCT.Draw( varname + ">>" +hname+"B1"+binning , "10.*(mc_ks_pz>0 && decayType==2 && mc_sv_z<1000 && sqrt(mc_sv_x*mc_sv_x + mc_sv_y*mc_sv_y)<30)")
    tmumuMCT.Draw( varname + ">>" +hname+"C1"+binning , "(mc_ks_pz>0 && decayType==2 && mc_sv_z<1000 && sqrt(mc_sv_x*mc_sv_x + mc_sv_y*mc_sv_y)<30)")
    tpipi2.Draw( varname + ">>" +hname+"B2"+binning)# , "(mc_ks_pz>0 && decayType==2 && mc_sv_z<1000 && sqrt(mc_sv_x*mc_sv_x + mc_sv_y*mc_sv_y)<30)")
    tmumu2.Draw( varname + ">>" +hname+"C2"+binning)# , "(mc_ks_pz>0 && decayType==2 && mc_sv_z<1000 && sqrt(mc_sv_x*mc_sv_x + mc_sv_y*mc_sv_y)<30)")

    C1 = vars()[hname +"C1"]
    C2 = vars()[hname +"C2"]
    B1 = vars()[hname +"B1"]
    B2 = vars()[hname +"B2"]
    C2.Divide(C1)
    B2.Divide(B1)
    B2.Divide(C2)
    return B2
