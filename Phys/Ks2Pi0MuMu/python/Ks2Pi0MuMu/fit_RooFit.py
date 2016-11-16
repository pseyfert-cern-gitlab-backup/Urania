from ROOT import *
from Urania import *
AccessPackage("Bs2MuMu")
from constrain_funcs import *
from smartpyROOT import *
from OurSites import *

gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx++")

kPaula = TColor.GetColor("#ff99cc")
mass_name = "M_VC"
bdtname = "VCGLBDT"

######  Prepare files
tmm0, mainF =  getTuple(MY_TUPLE_PATH + "KsPi0MM_dataL0Tis_GL_2_fitPlane")

mass = RooRealVar(mass_name,mass_name,420,580)
Mass = mass
samplename = "sample"

Binning = {}
Binning[bdtname] = [.2,.4,.6,.8, 1.]

UNIFORM_KAPPA = 0
DOUBLE_EXPO = 0

BDT_PDF = {str(i): 0.2 for i in range(1,len(Binning[bdtname])+1)}
Nbins = len(Binning[bdtname]) -1
cat =  RooCategory(samplename, samplename)
for i in range(Nbins): cat.defineType("bin" + str(i))

alpha_s = RooRealVar("alpha_S","alpha_s", 1)#0.31838135587209603,0.001,0.6)
alpha_s_cons = RooGaussian("alpha_s_const","alpha_s_const",alpha_s,RooFit.RooConst(0.31838135587209603),RooFit.RooConst(0.027318398127746596))
BR_s = RooRealVar("BRs","BRs", 1,-1.,1e06)
nbs = RooFormulaVar("NBs","NBs", "BRs/alpha_S", RooArgList(alpha_s,BR_s))

a2 = RooRealVar("a2","a2",100) ### Ponhendo os parametros da CB lonje, quedamonos so co core
a = RooRealVar("a","a" ,100) ### Ponhendo os parametros da CB lonje, quedamonos so co core
n = RooRealVar("n","n",1.)#,0.8,10)
n2 = RooRealVar("n2","n2",1)#.,0.8,60)

ipa_s = RooRealVar("ipa_s","ipa_s", 50.1)
ipa_m = RooRealVar("ipa_m","ipa_m",498)
beta = RooRealVar("beta","beta", 2e-03)#
zeta = RooRealVar("zeta","zeta",7e-02)#1e-03, 0, 5)
ipa_l = RooRealVar("l","l",-0.33)
#ipatia = 

fractions = {}
for i in range(2,5): fractions[str(i)] = RooRealVar("f"+str(i), "f"+str(i) , BDT_PDF[str(i)])

fractions['1'] = RooFormulaVar("f1", "f1", "(1-f2-f3-f4)", RooArgList(fractions['2'],fractions['3'],fractions['4']))

v = vars()

####################################################

class Ks2Pi0MuMuModel:

    def __init__(self, glbin):
        self.i = str(glbin)
        i = self.i

        self.nbs = RooFormulaVar("NBs" + i ,"NBs" + i, "NBs*f"+i, RooArgList(fractions[i],v["nbs"]))
       
        self.nbkg = RooRealVar("MuMuBkg"+i,"MuMuBkg"+i, 0,70000)
        #self.nmis = RooFormulaVar("Nmis" + i ,"Nmis" + i, "Nmis*f"+i+ "*1./missid_corr"+i, RooArgList(v["f"+i],v["nmis"],v["j"+i],v["missid_corr"+i]))

        if UNIFORM_KAPPA and i!= "1": self.k = mm[1].k
        else: self.k = RooRealVar("MuMu_k_"+i,"MuMu_k_" + i, -7e-04, -1e-02,1e-02)

        self.dk = RooRealVar("MuMu_dk_"+i,"MuMu_dk_" + i,-7e-04, -1e-02,0)#1e-02)
        self.kb = RooFormulaVar("MuMu_kb_"+i,"MuMu_kb_" + i,"MuMu_k_"+i + " + MuMu_dk_" + i, RooArgList(self.k,self.dk))
        self.bkg1 = RooExponential("bkg1 MuMu model" + i , "bkg1 MuMu model" + i, Mass,self.k)
        self.bkg2 = RooExponential("bkg2 MuMu model" + i , "bkg2 MuMu model" + i, Mass,self.kb)

        self.fb = RooRealVar("MuMu_f_"+i,"MuMu_f_" + i,0.5,0.,1.)
        if DOUBLE_EXPO: self.bkg = RooAddPdf("bkg MuMu model" + i, "bkg MuMu model" + i, self.bkg1,self.bkg2, self.fb)
        else: self.bkg = self.bkg1
        self.Bs = RooIpatia2("Ipatia" + i,"Ipatia" + i,mass,ipa_l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)
        self.model = RooAddPdf("mumu model " + i, "mumu model " + i, RooArgList(self.bkg,self.Bs), RooArgList(self.nbkg,self.nbs))


mm = {}
fiter = RooSimultaneous("fitter", "fitter", cat)

for i in fractions.keys():
    mm[i] = Ks2Pi0MuMuModel(i)
    fiter.addPdf(mm[i].model,"mumu bin" + str(i))


#tmm0 = mainF.Get("B2HHTuple/DecayTree")
#BDT = BDT_cuts(bdtname)
fiducial = "(1>0)"
#fiducial = 'B_s0_BDTS>0.05   && B_s0_PT>500 && B_s0_TAU*1000.<13.248 && muminus_P<500e03 && muplus_P<500e03 && muminus_PT<40e03 && muplus_PT<40e03  && muminus_PIDK<10 && muplus_PIDK<10 && muminus_PIDmu>-5 && muplus_PIDmu>-5 &&B_s0_PT>500 && B_s0_TAU*1000.<13.248 && muminus_P<500e03 && muplus_P<500e03 && muminus_PT<40e03 && muplus_PT<40e03&&muminus_PIDK<10 && muplus_PIDK<10 && muminus_PIDmu>-5 && muplus_PIDmu>-5&&B_s0_BDTS>0.05 '
print "fiducial cuts:", fiducial

############################################ Bs --> mm
fmm, tmm, datamm = {},{},{}
for i in range(1,Nbins+1):
    ix = str(i)
    fmm[i] = TFile("/scratch18/prof_mm"+ix+".root","recreate")
    tmm[i] = tmm0.CopyTree(fiducial + "&& " + bdtname + "> " +str(Binning[bdtname][i-1]) + "&& " + bdtname + "< " +str(Binning[bdtname][i])) 
    tmm[i].Write()
    fmm[i].Close()
    fmm[i] = TFile("/scratch18/prof_mm"+ix+".root")
    tmm[i] = fmm[i].Get("T")
    datamm[i] = RooDataSet("datamm"+ix,"datamm"+ix,tmm[i],RooArgSet(Mass))

mumuDataLG = RooDataSet("mumu data Low GL", "mumu data Low GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu bin1", datamm[1]), RooFit.Import("mumu bin2", datamm[2]), RooFit.Import("mumu bin3", datamm[3]),RooFit.Import("mumu bin4", datamm[4]))


#mumuDataHG = RooDataSet("mumu data High GL", "mumu data High GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu bin5", datamm[5]), RooFit.Import("mumu bin6", datamm[6]), RooFit.Import("mumu bin7", datamm[7]),RooFit.Import("mumu bin8", datamm[8]))

allData = mumuDataLG.Clone() #RooDataSet("all data","all data", RooArgSet(Mass,cat), RooFit.Import(hhData), RooFit.Import(mumuData))
#allData.append(mumuDataHG)

summaryConstraints = RooArgSet(alpha_s_cons)
#summaryConstraints.add(RooArgSet(sigmaBs_cons ,sigmaBd_cons,meanBd_cons,meanBs_cons, a_cons, alpha_s_cons,misid_global_cons))
#summaryConstraints.add(RooArgSet(PiMuNu2_cons,PiMuNu3_cons,PiMuNu4_cons,PiMuNu5_cons,PiMuNu6_cons,PiMuNu7_cons, PiMuNu8_cons, PiMuNu_cons))
#summaryConstraints.add(RooArgSet(sigmaPiMuNu1_cons,sigmaPiMuNu2_cons,sigmaPiMuNu3_cons,sigmaPiMuNu4_co

fiter.fitTo(allData,RooFit.Minos(kTRUE))#, RooFit.ExternalConstraints(RooArgSet(summaryConstraints)),RooFit.Strategy(2))

c = TCanvas()
c.Divide(2,2)
fr = {}
binning = 10
## #size = (Mass.getMax()-Mass.getMin())*1./binning
for i in datamm.keys():
    c.cd(i)
    fr[i] = Mass.frame()
    datamm[i].plotOn(fr[i], RooFit.Binning(binning))
    mm[str(i)].model.plotOn(fr[i])#
    #mm[str(i)].model.plotOn(fr[i])#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
    mm[str(i)].model.plotOn(fr[i], RooFit.Components("Ipatia"+str(i)),RooFit.LineColor(kPaula),RooFit.LineStyle(9))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
    
    
    fr[i].GetXaxis().SetTitle("m_{#mu#mu} ( MeV/c^{2} )")
    fr[i].SetTitle("K_{S}^{0}#rightarrow#tilde{#pi^{0}}#mu^{+}#mu^{-} candidates, BIN [" + str(Binning[bdtname][i-1]) + ", " +str(Binning[bdtname][i])+"]" )

    #fr[i].GetYaxis().SetTitle("Events /( "+str(int(size))+" MeV/c^{2} )")
    fr[i].GetYaxis().SetTitleOffset(1.4)
    #else: fr[i].GetYaxis().SetTitleOffset(1.6)
    fr[i].Draw()

#nll = fiter.createNLL(allData,RooFit.NumCPU(2),RooFit.ExternalConstraints(RooArgSet(summaryConstraints)))
## #nll.migrad()

#nll.migrad()
#nll.hesse()
#nll.minos()

#  RooPlot* frame1 = frac.frame(Bins(10),Range(0.01,0.95),Title("LL and profileLL in frac")) ;
#  nll->plotOn(frame1,ShiftToZero()) ;

#fr = BR_s.frame(RooFit.Title("LL of BR(B_{s}^{0}#rightarrow #mu^{+}#mu^{-})"),RooFit.Range(-0.5,10))

##pl_Bs = nll.createProfile(RooArgSet(BR_s))

#nll.plotOn(fr,RooFit.ShiftToZero())

#pl_Bs.plotOn(fr)


## zx = fr.Draw()
#pl_Bd = nll.createProfile(RooArgSet(bdbs))

## c.cd(4)
## fr4 = Mass.frame()
## datamm4.plotOn(fr4, RooFit.Binning(10))#, RooFit.Cut("Bmass<4"))
## mm4.model.plotOn(fr4)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## mm4.model.plotOn(fr4, RooFit.Components("model Bs4"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## mm4.model.plotOn(fr4, RooFit.Components("model Bd4"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## mm4.model.plotOn(fr4, RooFit.Components("missid4"),RooFit.LineColor(kMagenta))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## fr4.Draw()

##############################


## c2.cd(4)
## hfr4 = Mass.frame()
## datahh4.plotOn(hfr4)#, RooFit.Cut("Bmass<4"))
## hh4.model.plotOn(hfr4)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## hh4.model.plotOn(hfr4, RooFit.Components("Sigmodel4"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## hh4.model.plotOn(hfr3, RooFit.Components("shoulder4"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## hfr4.Draw()


## #### inspired on Francesco code
## wsp = RooWorkspace("workspace","workspace")
## modelConfig = RooStats.ModelConfig("my_problem",wsp)
## modelConfig.SetPdf(fiter)
## modelConfig.SetParametersOfInterest(RooArgSet(BR_s))
## modelConfig.SetObservables(RooArgSet(Mass,cat))
## #modelConfig.SetObservables(RooArgSet(massname,samplename))#
## modelConfig.SetConstraintParameters(summaryConstraints)

## fc = RooStats.FeldmanCousins(allData,modelConfig)


## fc.SetTestSize(0.31731050786291404)#0.05)
## fc.UseAdaptiveSampling(kTRUE)
## fc.SetNBins(100)
## #fc.GetInterval()

## ## wsp = RooWorkspace("workspace","workspace")
## ## modelConfig = RooStats.ModelConfig("my_problem",wsp)
## ## modelConfig.SetPdf(mm[8].model)
## ## modelConfig.SetParametersOfInterest(RooArgSet(nbs))
## ## modelConfig.SetObservables(RooArgSet(massname))
## ## modelConfig.SetConstraintParameters(summaryConstraints)

## ## fc = RooStats.FeldmanCousins(datamm[8],modelConfig)
## #interval = fc.GetInterval()

## mcstudy = RooMCStudy(fiter,RooArgSet(Mass,cat),RooFit.Silence(), RooFit.FitOptions(RooFit.Save(kTRUE),RooFit.PrintEvalErrors(0), RooFit.ExternalConstraints(RooArgSet(summaryConstraints)),RooFit.Minos(kTRUE)),RooFit.Extended())

## mcstudy = RooMCStudy(fiter,RooArgSet(Mass,cat),RooFit.Silence(), RooFit.FitOptions(RooFit.Save(kTRUE),RooFit.PrintEvalErrors(0),RooFit.Minos(kTRUE)),RooFit.Extended())
## #mcstudy.generateAndFit(1000)
