from Urania import *
AccessPackage("Bs2MuMu")
from ROOT import *
import TheTable
from constrain_funcs import *
from fiducial import *
from bisect import *
import priormcmc1 as PRIOR
from Urania import PDG

gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx++")
gROOT.ProcessLine(".L $URANIAROOT/src/RooAmorosoPdf.cxx++")
gROOT.ProcessLine(".L $SOMEMASSMODELSROOT/src/RooPowerLaw.cxx++")

COMBINE_2011 = 1
BLIND = 1
POWER_LAW = 1 ### if set to zero it will use an exponential for the misid bkg

if not BLIND:
    print ""
    print ""
    print ""
    print "0o0   0o0    0o0   0o0   0o0  0o0  0o0  0o0"
    print " ALARM!, ALARM!, YOU ARE UNBLINDING!!!"
    print "0o0   0o0    0o0   0o0   0o0  0o0  0o0  0o0"
    print ""
    print ""
    print ""

TUPLE_PATH = "/scratch18/diego/Ksmm/"

massname = "KS0_MM"
samplename = "sample"
bdtname = "BDTb025de4nt1000M1"#BDTflat_BDT9_BDTScut05"

Binning = {}
Binning["TIS_"] =  binTIS[bisect(binTIS,0.32):]
Binning["TOS1_"] =  binTOS1[bisect(binTOS1,0.2):]
Binning["TOS2_"] =  binTOS2[bisect(binTOS2,0.3):]


Mass = RooRealVar(massname,massname,465,600)
mass = Mass
cat =  RooCategory(samplename, samplename)
mass.setRange("lsb", mass.getMin(), PDG.K0.mass-5)
mass.setRange("rsb", PDG.K0.mass+5, mass.getMax() )



for key in Binning.keys():
    for i in range(len(Binning[key])-1): cat.defineType(key + str(i))

######  Prepare files
f, t = {}, {}
f["TIS_"] = TFile(TUPLE_PATH +"Ks0mumu_Data2012_Splitted_Res20_MuPtCutOff2500_TisTisTos_MVA.root")
t["TIS_"] = f["TIS_"].Get("KS0mumu")
f["TOS1_"] = TFile(TUPLE_PATH + "Ks0mumu_Data2012_Splitted_Res20_MuPtCutOff2500_TosTos1Tos_MVA.root")
t["TOS1_"] = f["TOS1_"].Get("KS0mumu")
f["TOS2_"] = TFile(TUPLE_PATH + "Ks0mumu_Data2012_Splitted_Res20_MuPtCutOff2500_TosTos2Tos_MVA.root")
t["TOS2_"] = f["TOS2_"].Get("KS0mumu")


#TFile("/afs/cern.ch/user/d/diegoms/public/top_secret/unblind_bsmumu_1fb_2.root")
BDT = {}
for key in Binning.keys(): BDT[key] = BDT_cuts(bdtname, Binning[key])
#fiducial =  "(1>0)"
print "fiducial cuts:", SEL

############################################ Bs --> mm
fmm, tmm, datamm, catdatamm = {},{},{}, {}
for key in Binning.keys():
    for i in range(len(Binning[key])-1):
        ix = key + str(i)
        fmm[ix] = TFile(TUPLE_PATH + "prof_mm"+ix+".root","recreate")
        tmm[ix] = t[key].CopyTree(SEL[key] + BDT[key][i])
        neim = tmm[ix].GetName()
        tmm[ix].Write()
        fmm[ix].Close()
        fmm[ix] = TFile(TUPLE_PATH + "prof_mm"+ix+".root")
        tmm[ix] = fmm[ix].Get(neim)
        datamm[ix] = RooDataSet("datamm"+ix,"datamm"+ix,tmm[ix],RooArgSet(Mass))
        catdatamm[ix] = RooDataSet("catdatamm"+ix,"catdatamm"+ix,RooArgSet(Mass),RooFit.Index(cat), RooFit.Import(ix, datamm[ix]))

BR = RooRealVar("BR","BR", 1,-1,10)
prior = RooAmorosoPdf("PRIOR", "PRIOR" ,BR, PRIOR.offset, PRIOR.theta, PRIOR.alpha, PRIOR.beta)

v = vars()
### Create constraints. Example
summaryConstraints = RooArgSet()
Ipa_m_const = {}
Alpha_const = {}

for key in Binning.keys():
    for i in range(len(Binning[key])-1):
        ix = key + str(i)
        Alpha_const[key + str(i)] = createConst(TheTable.alpha[ix],TheTable.s_alpha[ix], "alphaconst"+ix)
        summaryConstraints.add(Alpha_const[key + str(i)][-1])
 ##         Ipa_m_const[key + str(i)] = createBifurConst(TheTable.sigmaKMuNu1,TheTable.sigmaKMuNu1ErrMinus,TheTable.sigmaKMuNu1ErrPlus, "sigmaKMuNu1")

if COMBINE_2011: summaryConstraints.add(prior)

class KsMuMuModel:

    def __init__(self, name ):
        self.i = name
        i = self.i
        self.alpha = Alpha_const[i][0]
        
        self.nbs = RooFormulaVar("NKs" + i ,"NKs" + i, "BR/alphaconst"+i, RooArgList(self.alpha,v["BR"]))    
        self.nbkg = RooRealVar("MuMuBkg"+i,"MuMuBkg"+i, tmm[i].GetEntries(), 0,max(2*tmm[i].GetEntries(),20))
        
        self.k = RooRealVar("MuMu_k_"+i,"MuMu_k_" + i, -7e-04, -.1,.1)
        self.dk = RooRealVar("MuMu_dk_"+i,"MuMu_dk_" + i,-7e-04, -1,0)#1e-02)
        self.kb = RooFormulaVar("MuMu_kb_"+i,"MuMu_kb_" + i,"MuMu_k_"+i + " + MuMu_dk_" + i, RooArgList(self.k,self.dk))
       
        self.bkg1 = RooExponential("bkg1 MuMu model" + i , "bkg1 MuMu model" + i, Mass,self.k)
        self.bkg2 = RooExponential("bkg2 MuMu model" + i , "bkg2 MuMu model" + i, Mass,self.kb)

        self.misid_a = RooRealVar("misid "+ i + "a","misid "+ i + "a",-1, -100,-0.1)
        self.misid_n = RooRealVar("misid "+ i + "n","misid "+ i + "n",3, 1.5, 100)
        #self.misid_s = RooRealVar("misid "+ i + "s","misid "+ i + "s",3,1,10)
        self.misid_m = RooRealVar("misid "+ i + "m","misid "+ i + "m",410,350,420)
        self.misid = RooPowerLaw("misid " + i,"misid " + i,mass, self.misid_m, self.misid_n)
        self.f_misid = RooRealVar("Nmisid "+ i ,"Nmisid "+ i ,0.8,0.2,1)
        #self.bkg = RooAddPdf("AllBkg"+i,"AllBkg"+i, self.misid,self.bkg1,self.f_misid)
        if POWER_LAW: self.bkg = RooAddPdf("bkg MuMu model" + i, "bkg MuMu model" + i, self.misid,self.bkg1, self.f_misid)
        else: self.bkg = RooAddPdf("bkg MuMu model" + i, "bkg MuMu model" + i, self.bkg2,self.bkg1, self.f_misid)
        self.ipa_s = RooRealVar("ipa_s" + i,"ipa_s" + i, TheTable.sigma[i])#,1,20)
        self.ipa_m = RooRealVar("ipa_m" + i,"ipa_m" + i,TheTable.mean[i])#,490,50)
        self.beta = RooRealVar("beta" + i,"beta" + i, TheTable.beta[i])#,-1e-03,1e-03)#
        self.zeta = RooRealVar("zeta" + i,"zeta" + i,TheTable.zeta[i])#1e-03, 0, 5)
        self.ipa_l = RooRealVar("l" + i,"l" + i, TheTable.landa[i])#, 0, 3)
        self.ipa_a1 = RooRealVar("a1"+i,"a1"+i,TheTable.a1[i])
        self.ipa_a2 = RooRealVar("a2"+i,"a2"+i,100)
        self.ipa_n1 = RooRealVar("n1"+i,"n1"+i,TheTable.n1[i])
        self.ipa_n2 = RooRealVar("n2"+i,"n2"+i,1)
        
        self.Ks = RooIpatia2("Ipatia" + i,"Ipatia" + i,mass,self.ipa_l,self.zeta,self.beta,self.ipa_s,self.ipa_m,self.ipa_a1,self.ipa_n1,self.ipa_a2,self.ipa_n2)
        self.model = RooAddPdf("mumu model " + i, "mumu model " + i, RooArgList(self.bkg,self.Ks), RooArgList(self.nbkg,self.nbs))



       

####################################################


mm = {}
fiter = RooSimultaneous("fitter", "fitter", cat)
for key in Binning.keys():
    for i in range(len(Binning[key])-1):
        name = key + str(i)
        mm[name] = KsMuMuModel(name)
        fiter.addPdf(mm[name].model,name)



TISdata = catdatamm["TIS_0"].Clone()
TOS1data = catdatamm["TOS1_0"].Clone()
TOS2data = catdatamm["TOS2_0"].Clone()
for i in range(1,len(Binning["TIS_"])-1): TISdata.append(catdatamm["TIS_"+ str(i)])
for i in range(1,len(Binning["TOS1_"])-1): TOS1data.append(catdatamm["TOS1_"+ str(i)])
for i in range(1,len(Binning["TOS2_"])-1): TOS2data.append(catdatamm["TOS2_"+ str(i)])

        
allData = TISdata.Clone()
allData.append(TOS1data)
allData.append(TOS2data)

fiter.fitTo(allData, RooFit.ExternalConstraints(RooArgSet(summaryConstraints)), RooFit.Offset(kTRUE))#,RooFit.Strategy(2))

fr = {}
resid_hists = {}
pull_hists = {}
def plot(ix, binning = 100):
    fr[ix] = Mass.frame()
    datamm[ix].plotOn(fr[ix], RooFit.Binning(binning),RooFit.CutRange("lsb,rsb"))
    mm[ix].model.plotOn(fr[ix], RooFit.Components("misid "+ix),RooFit.LineColor(kGreen),RooFit.LineStyle(7))
    mm[ix].model.plotOn(fr[ix], RooFit.Components("bkg1 MuMu model "+ix),RooFit.LineStyle(kDotted))
    mm[ix].model.plotOn(fr[ix], RooFit.Components("Ipatia"+ ix),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.Range("lsb,rsb"))
    mm[ix].model.plotOn(fr[ix], RooFit.Range("lsb,rsb"))#

    c = TCanvas()
    c.Divide(1,3)
    c.cd(1)
    fr[ix].Draw()
    c.cd(2)
    fr[ix + "_resid"] = Mass.frame()
    resid_hists[ix] = fr[ix].residHist()
    fr[ix + "_resid"].addPlotable(resid_hists[ix],"P")
    fr[ix + "_resid"].Draw()
    c.cd(3)
    fr[ix + "_pull"] = Mass.frame()
    pull_hists[ix] = fr[ix].pullHist()
    fr[ix + "_pull"].addPlotable(pull_hists[ix],"P")

    fr[ix + "_pull"].Draw()
    return c


 
