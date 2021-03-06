#! /usr/bin/env python
from ROOT import *
from Urania import *
#recoverTree()
from scipy import random as rnd
import sys
AccessPackage("Bs2MuMu")
from constrain_funcs import *
from smartpyROOT import *
from OurSites import *
from scipy import random as rnd
import ipa_mlPARTIAL as ipa_params
gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx++")

L = 50
if len (sys.argv)>1:
    L = float(sys.argv[1])
kPaula = TColor.GetColor("#ff99cc")
mass_name = "M_V0"#"M_VC"
bdtname = "DMGLBDTG"

NTIS_pipi = 373740 * 0.5 ## We split half for training and half for fitting
Leff= .765e-03/2 ## We split half for training and half for fitting
#eff_TIS = 0.002518145459931862 This is not needed
eff_PIPI = 0.23e-02/1000.
eff_Sig = 3.0e-03
######  Prepare files
tmm0, mainF =  getTuple("/scratch18/Kspi0/Data16_PARTIAL_GL_2_noGhost")#MY_TUPLE_PATH + "kspi0mumu_ntupleData15_TIS_2_GL")#"kspi0mumu_ntuple_march2016_GL_2_conf4_fitPlane_conf4")
#BREAK

mass = RooRealVar(mass_name,mass_name,420,580)
Mass = mass
samplename = "sample"

Binning = {}
Binning[bdtname] = [.6,.7, .8, .9, 1.]

UNIFORM_KAPPA = 0
DOUBLE_EXPO = 0
KAPPA_VC = 0
kappas_vc = {"1": 0.016080499575 , "2": 0.001277219534826 , "3": -0.008131488447299, "4": 0.008787340526 }
BDT_PDF = {str(i): 0.1 for i in range(1,len(Binning[bdtname])+1)}
Nbins = len(Binning[bdtname]) -1
cat =  RooCategory(samplename, samplename)
for i in range(1, Nbins + 1): cat.defineType("bin" + str(i))

alpha0 = 0.692*1./NTIS_pipi * (eff_PIPI/eff_Sig)
alpha_s = RooRealVar("alpha_S","alpha_s",alpha0)#0.31838135587209603,0.001,0.6)
alpha_s_cons = RooGaussian("alpha_s_const","alpha_s_const",alpha_s,RooFit.RooConst(alpha_s.getVal()),RooFit.RooConst(0.1*alpha_s.getVal()))
BR_s = RooRealVar("BRs","BRs", 1e-09,0.,3e-07)
nbs = RooFormulaVar("NBs","NBs", "BRs/alpha_S", RooArgList(alpha_s,BR_s))

nbs = RooRealVar("NBs","NBs",0,100)


fractions = {}
for i in range(1,Nbins+1): fractions[str(i)] = RooRealVar("f"+str(i), "f"+str(i) , BDT_PDF[str(i)])


v = vars()

####################################################

class Ks2Pi0MuMuModel:

    def __init__(self, glbin):
        self.i = str(glbin)
        i = self.i

        self.nbs = RooFormulaVar("NBs" + i ,"NBs" + i, "NBs*f"+i, RooArgList(fractions[i],v["nbs"]))
       
        self.nbkg = RooRealVar("MuMuBkg"+i,"MuMuBkg"+i,0,100)
        #self.nmis = RooFormulaVar("Nmis" + i ,"Nmis" + i, "Nmis*f"+i+ "*1./missid_corr"+i, RooArgList(v["f"+i],v["nmis"],v["j"+i],v["missid_corr"+i]))

        if UNIFORM_KAPPA and i!= "1": self.k = mm[1].k
        else: self.k = RooRealVar("MuMu_k_"+i,"MuMu_k_" + i, -7e-04, -1,1)
        if KAPPA_VC:
            self.k.setVal(-1*kappas_vc[i])
            self.k.setConstant(kTRUE)
        self.dk = RooRealVar("MuMu_dk_"+i,"MuMu_dk_" + i,-7e-04, -1e-02,0)#1e-02)
        self.kb = RooFormulaVar("MuMu_kb_"+i,"MuMu_kb_" + i,"MuMu_k_"+i + " + MuMu_dk_" + i, RooArgList(self.k,self.dk))
        self.bkg1 = RooExponential("bkg1 MuMu model" + i , "bkg1 MuMu model" + i, Mass,self.k)
        self.bkg2 = RooExponential("bkg2 MuMu model" + i , "bkg2 MuMu model" + i, Mass,self.kb)

        self.fb = RooRealVar("MuMu_f_"+i,"MuMu_f_" + i,0.5,0.,1.)
        if DOUBLE_EXPO: self.bkg = RooAddPdf("bkg MuMu model" + i, "bkg MuMu model" + i, self.bkg1,self.bkg2, self.fb)
        else: self.bkg = self.bkg1
        self.ipa_s = RooRealVar("ipa_s" + i,"ipa_s" + i, ipa_params.sigma[i])#,1,20)
        self.ipa_m = RooRealVar("ipa_m" + i,"ipa_m" + i,ipa_params.mean[i])#,490,50)
        self.beta = RooRealVar("beta" + i,"beta" + i, ipa_params.beta[i])#,-1e-03,1e-03)#
        self.zeta = RooRealVar("zeta" + i,"zeta" + i,ipa_params.zeta[i])#1e-03, 0, 5)
        self.ipa_l = RooRealVar("l" + i,"l" + i, ipa_params.landa[i])#, 0, 3)
        self.a2 = RooRealVar("a2" +i, "a2" +i,ipa_params.a2[i])#,.1,100) ### Ponhendo os parametros da CB lonje, quedamonos so co core
        self.a = RooRealVar("a1" +i,"a1" +i ,ipa_params.a[i])#5,.1,100) ### Ponhendo os parametros da CB lonje, quedamonos so co core
        self.n = RooRealVar("n1" +i,"n1" +i,ipa_params.n[i])
        self.n2 = RooRealVar("n2"+i,"n2" +i,ipa_params.n2[i])

        self.Bs = RooIpatia2("Ipatia" + i,"Ipatia" + i,mass,self.ipa_l,self.zeta,self.beta,self.ipa_s,self.ipa_m,self.a,self.n,self.a2,self.n2)
        self.model = RooAddPdf("mumu model " + i, "mumu model " + i, RooArgList(self.bkg,self.Bs), RooArgList(self.nbkg,self.nbs))


mm = {}
fiter = RooSimultaneous("fitter", "fitter", cat)

for i in fractions.keys():
    mm[i] = Ks2Pi0MuMuModel(i)
    fiter.addPdf(mm[i].model,"bin" + str(i))



fiducial = "(1>0)"

print "fiducial cuts:", fiducial

############################################ Bs --> mm
fmm, tmm, datamm = {},{},{}
for i in range(1,Nbins+1):
    ix = str(i)
    fmm[i] = TFile(MY_TUPLE_PATH + "prof_mm"+ix+".root","recreate")
    tmm[i] = tmm0.CopyTree(fiducial + "&& " + bdtname + "> " +str(Binning[bdtname][i-1]) + "&& " + bdtname + "< " +str(Binning[bdtname][i])) 
    tmm[i].Write()
    fmm[i].Close()
    fmm[i] = TFile(MY_TUPLE_PATH + "prof_mm"+ix+".root")
    tmm[i] = fmm[i].Get("T")
    datamm[i] = RooDataSet("datamm"+ix,"datamm"+ix,tmm[i],RooArgSet(Mass))

mumuDataLG = RooDataSet("mumu data Low GL", "mumu data Low GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("bin1", datamm[1]), RooFit.Import("bin2", datamm[2]), RooFit.Import("bin3", datamm[3]),RooFit.Import("bin4", datamm[4]))


allData = mumuDataLG.Clone() #RooDataSet("all data","all data", RooArgSet(Mass,cat), RooFit.Import(hhData), RooFit.Import(mumuData))
#allData.append(mumuDataHG)

summaryConstraints = RooArgSet(alpha_s_cons)


fiter.fitTo(allData,RooFit.Minos(kTRUE))#, RooFit.ExternalConstraints(RooArgSet(summaryConstraints)),RooFit.Strategy(2))


## #size = (Mass.getMax()-Mass.getMin())*1./binning

def plot(deitasets):
    c = TCanvas()
    c.Divide(2,2)
    fr = {}
    binning = 20
    #sp_data = deita.split(cat)
    for i in datamm.keys():
        print "i=",i
        print "fr=",fr
        c.cd(i)
        fr[i] = Mass.frame()
        print "fr after=",fr
        print "deitasets=",deitasets
        deitasets[i].plotOn(fr[i], RooFit.Binning(binning))
        #deita.plotOn(fr[i],RooFit.Slice(cat, "bin"+str(i)), RooFit.Binning(binning)) 
        #deita.plotOn(fr[i], RooFit.Binning(binning), RooFit.Cut(samplename + "== " + samplename +"::bin"+str(i)))
        mm[str(i)].model.plotOn(fr[i])#
        mm[str(i)].model.plotOn(fr[i], RooFit.Components("Ipatia"+str(i)),RooFit.LineColor(kPaula),RooFit.LineStyle(9))
        mm[str(i)].model.plotOn(fr[i], RooFit.Components("bkg1 MuMu model" +str(i)),RooFit.LineColor(kBlack),RooFit.LineStyle(kDotted))
    
        fr[i].GetXaxis().SetTitle("m_{#pi^{0}#mu#mu} ( MeV/c^{2} )")
        fr[i].GetYaxis().SetTitle("Candidates / ( MeV/c^{2} )")
        fr[i].GetYaxis().SetRangeUser(0,12)#Title("Candidates / ( MeV/c^{2} )")
        fr[i].SetTitle("K_{S}^{0}#rightarrow#tilde{#pi^{0}}#mu^{+}#mu^{-} candidates, BIN [" + str(Binning[bdtname][i-1]) + ", " +str(Binning[bdtname][i])+"]" )

        fr[i].GetYaxis().SetTitleOffset(1.)
        fr[i].Draw()
    return c, fr

a = plot(datamm)
BREAK
## c = TCanvas()
## c.Divide(2,2)
## c.cd(1)
## a[1][1].Draw()
## c.cd(2)
## a[1][2].Draw()
## c.cd(3)
## a[1][3].Draw()
## c.cd(4)
## a[1][4].Draw()

BR_s.setVal(0.)
BR_s.setConstant(kTRUE)
fiter.fitTo(allData,RooFit.Minos(kTRUE))#, RooFit.ExternalConstraints(RooArgSet(summaryConstraint
BR_s.setConstant(kFALSE)
#
##BREAK   #################################### ML: I have to do up to here
bkgs = {}
for i in mm.keys(): bkgs[i] = [mm[i].nbkg.getVal(), mm[i].nbkg.getError()]
from scipy.stats import poisson
def genB(N):
    if N > 14: return rnd.normal(N,sqrt(N))
    x = rnd.random()* min(10, N+sqrt(N)*5)
    p = poisson.pmf(N,x)
    pmax = poisson.pmf(N,max(N,.00001))
    y =rnd.random()*pmax
    if p>=y : return x
    else: return genB(N)
   
#meanbs = {}
#meanbs = {'1': 9.126531453699645, '3': 4.052571636169251, '2': 5.128871743437573, '4': 0.3917544944986389}#{'1': 8.40279447256816, '3': 1.2323226356579844, '2': 8.254177070568243, '4': 0.40771815182069215}
#for i in mm.keys():
 #   l = []
  #  for j in range(1000): l.append(genB(i))
   # meanbs[i] = rms(l)[0]
    #meanbs[i] = mm[i].nbkg.getVal() #+ mm[i].nbkg.getError()
#BREAK
meanbs = {}
sigmasbs_minus = {}
sigmasbs_plus = {}

obsbs = {}
for i in mm.keys():
    #l = []
    #for j in range(1000): l.append(genB(i))
    #meanbs[i] = rms(l)[0]
    obsbs[i] = mm[i].nbkg.getVal() 
    #meanbs[i] = mm[i].nbkg.getVal()
    #sigmasbs_minus[i] = mm[i].nbkg.getAsymErrorLo()
    #sigmasbs_plus[i] = mm[i].nbkg.getAsymErrorHi()
    mm[i].nbkg.setMax(1e08)
#BREAK
gendeitas = {}
def doToy(leibol, gendeita):
    BR_s.setVal(2.9e-9)
    #gendeita = {}
    for i in datamm.keys():
        alpha_s.setVal(alpha0 *Leff*1./L)
        #B = obsbs[str(i)]*L*1./(Leff)
        B = genB(obsbs[str(i)])*L*1./(Leff)

        print B
        mm[str(i)].nbkg.setVal( B )
        gendeita[i] = mm[str(i)].model.generateBinned(RooArgSet(Mass),RooFit.Extended())
    deita2 = RooDataHist(leibol + "gendeita", leibol + "gendeita", RooArgList(Mass), RooFit.Index(cat), RooFit.Import("bin1", gendeita[1]), RooFit.Import("bin2", gendeita[2]), RooFit.Import("bin3", gendeita[3]),RooFit.Import("bin4", gendeita[4]))
    ## Todo peta. TODO. Me cago en dios...
    fiter.fitTo(deita2, RooFit.Minos(RooArgSet(BR_s)))
    return BR_s.getVal(), BR_s.getAsymErrorLo(),  BR_s.getAsymErrorHi()#, gendeita

sml, spl = [], []
dat = {}
#BREAK
##br, sm, sp  = doToy(str(i),dat) 
#a = plot(dat) 
#BREAK 

for i in range(5000):
    print "-_-", i
    gendeitas[i] = {}
    br, sm, sp  = doToy(str(i), gendeitas[i])
    if not sm: continue
    if not sp: continue
    sml.append(sm)
    spl.append(sp)

print rms(sml)
print rms(spl)

#50
#(-9.712252284147969e-10, 1.8161393558109025e-10)
#(1.1170069629734814e-09, 1.3550940664660493e-10)

#50
#(-1.2055300555780324e-09, 1.5111751714939047e-10)
#(1.548824345811501e-09, 2.818907507123162e-10)
# 1.5x10-9
