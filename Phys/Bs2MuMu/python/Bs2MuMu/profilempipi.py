from ROOT import *


#Gl = RooRealVar("BDTflatNEW","BDTflatNEW",0,1)\
Mpipi = RooRealVar("Mpipi","Mpipi",5000, 5700)#4000, 8000)
Mass = RooRealVar("Bmass","Bmass",4200, 7700)#4000, 8000)
#hhMass = RooRealVar("Mipi","Mpipi",4800, 5700)
#ID = RooRealVar("AreMuons","AreMuons", 0,1)

## c1 = RooRealVar("c1","c1",-3,3)
## c2 = RooRealVar("c2","c2",-3,3)
## c3 = RooRealVar("c3","c3",-3,3)
## c4 = RooRealVar("c4","c4",-3,3)
## c5 = RooRealVar("c5","c5",-3,3)

cat =  RooCategory("sample", "sample")
cat.defineType("hh bin1")
cat.defineType("hh bin2")
cat.defineType("hh bin3")
cat.defineType("hh bin4")

cat.defineType("mumu bin1")
cat.defineType("mumu bin2")
cat.defineType("mumu bin3")
cat.defineType("mumu bin4")


#f1 = RooRealVar("f1","f1",2.03137e-01)#0,1)
#cf2 = RooRealVar("cf2","cf2",3.00932e-01)#0,1)
#cf3 = RooRealVar("cf3","cf3", 4.33122e-01)#0,1)

f1 = RooRealVar("f1","f1",   0,1)
cf2 = RooRealVar("cf2","cf2", 0,1)
cf3 = RooRealVar("cf3","cf3",  0,1)
#cf4 = RooRealVar("cf4","cf4",0,1)

f2 = RooFormulaVar("f2","f2","cf2*(1-f1)",RooArgList(f1,cf2))
f3 = RooFormulaVar("f3","f3","cf3*(1-f1-f2)",RooArgList(f1,cf3,f2))
f4 = RooFormulaVar("f4","f4","(1-f1-f2-f3)",RooArgList(f1,f3,f2))

j1 = RooRealVar("j1","j1",1)
j2 = RooRealVar("j2","j2",1)
j3 = RooRealVar("j3","j3",1)
j4 = RooRealVar("j4","j4",1)

nbs = RooRealVar("NBs","NBs", 0,40)
nmis = RooRealVar("Nmis","Nmis", 0,40)
bdbs = RooRealVar("bdbs","bdbs", 0,5)
nbd = RooFormulaVar("NBd","NBd","bdbs*NBs",RooArgList(nbs,bdbs))
Nhh = RooRealVar("Nhh","Nhh", 2000,20000)

a = RooRealVar("CB trans","CB trans", 2.5)
n = RooRealVar( "n", "n", 1)
sigma = RooRealVar("sigma","sigma", 22)
meanBs = RooRealVar("MBs","MBs", 5358)
meanBd = RooRealVar("MBd","MBds", 5272)

v = vars()

### B2hh crap ######################################
mhyp = "Mpipi"#"Bmass"
IncFit01, IncFit02 = {}, {}
IncFit01["Bmass"] = {'f1': 0.0678, 'n': 1.0, 'a3': 1.38, 'a2': -1.19,  'n2': 9.28, 'd1': 72.4}
IncFit01["B_mass"] = IncFit01["Bmass"]
IncFit01["Mpipi"] = {'f1': 0.0707, 'n': 1.0, 'a3': 1.41, 'a2': -1.25,  'n2': 8.53, 'd1': 72.3}
IncFit01["MpiK"]  = {'f1': 0.833,  'n': 1.0, 'a3': 1.35, 'a2': -0.718, 'n2': 4.33, 'd1': 54.0}
IncFit01["MKpi"]  = {'f1': 0.855,  'n': 1.0, 'a3': 1.46, 'a2': -0.758, 'n2': 4.08, 'd1': 59.0}
IncFit01["MKK"]   = {'f1': 0.687,  'n': 1.0, 'a3': 2.33, 'a2': -0.5,   'n2': 4.85, 'd1': 50.4}
hh_f05 = RooRealVar("0.55", "0.5", 0.5) ### This is here just to create double crystalballs (I think)
hh_f1 = RooRealVar("fraction","fraction",0.0678)#, 0., 1.)
hh_mean1 = RooRealVar("mean1","mean1",5050, 5600)#5168.)
hh_d1= RooRealVar("d1","d1", 72.4)#, 20., 120.)
hh_mean2 = RooFormulaVar("mean2","mean2", "mean1 + d1" ,RooArgList(hh_mean1,hh_d1) )
hh_sigma = RooRealVar("hh_sigma","hh_sigma", 20.,50)#35.)

hh_n = RooRealVar("exponent", "exponent",1.)#,  0., 12 )
hh_n2 = RooRealVar("exponent2", "exponent2",  9.28 )#,.1, 12)

hh_a2 = RooRealVar("transition2","transition2", -1.19)#, -3, -0.5) ## Transition point, in sigmas
hh_a3 = RooRealVar("transition3","transition3",1.38)#, 0.5, 3) ## Transition point, in sigmas

for key in IncFit01[mhyp].keys():
    v["hh_"+key].setVal(IncFit01[mhyp][key])


 
sh_mean = RooRealVar("sh_mean", "sh_mean", 4729.)#, 4200.,5000.)
sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 294.)#, 100.,400.)

############ MISID
missid_mean1 = RooRealVar("missid_mean1","missid_mean1",5.20586e+03)#5050, 5600)#5168.)
missid_d1= RooRealVar("missid_d1","missid_d1", 3.65105e+01)#72.4, 20., 200.)
missid_d2= RooRealVar("missid_d2","missid_d2", 2.50666e+01)#72.4, 20., 200.)
missid_mean2 = RooFormulaVar("missid_mean2","missid_mean2", "missid_mean1 + missid_d1" ,RooArgList(missid_mean1,missid_d1) )
missid_mean3 = RooFormulaVar("missid_mean3","missid_mean3", "missid_mean2 + missid_d2" ,RooArgList(missid_mean2,missid_d2) )
missid_sigma = RooRealVar("missid_sigma","missid_sigma",1.23888e+02 )# 20.,200.)
missid_sigma2 = RooRealVar("missid_sigma2","missid_sigma2", 3.63338e+01)#20.,100.)
missid_sigma3 = RooRealVar("missid_sigma3","missid_sigma3", 2.30405e+01 )#20.,100.)

missid_n = RooRealVar("missid_exponent", "missid_exponent",1.16669e+02)#1.,  0.1, 120 )
missid_n2 = RooRealVar("missid_exponent2", "missid_exponent2",  2.53388e-01 )# 9.28 ,.1, 120)

missid_a2 = RooRealVar("missid_transition2","missid_transition2", -1.96672e+00)#-1.19, -3, -0.2) ## Transition point, in sigmas
missid_a3 = RooRealVar("missid_transition3","missid_transition3",2.99950e+00 )#1.38, 0.2, 3) ## Transition point, in sigmas

missid_nb = RooRealVar("missid_exponentb", "missid_exponentb",6.46682e+00)#1.,  0.1, 120 )
missid_n2b = RooRealVar("missid_exponent2b", "missid_exponent2b",  1.11984e+02 )#9.28 ,.1, 120)

missid_a2b = RooRealVar("missid_transition2b","missid_transition2b", -1.64475e+00)#-1.19, -3, -0.2) ## Transition point, in sigmas
missid_a3b = RooRealVar("missid_transition3b","missid_transition3b",3.21189e-01 )#1.38, 0.2, 3) ## Transition point, in sigmas1


missid_nc = RooRealVar("missid_exponentc", "missid_exponentc",4.32501e-01)#1.,  0.1, 12 )
missid_n2c = RooRealVar("missid_exponent2c", "missid_exponent2c",   6.21115e+00)#9.28 ,.1, 12)

missid_a2c = RooRealVar("missid_transition2c","missid_transition2c", -1.80624e+00)# -1.19, -3, -0.2) ## Transition point, in sigmas
missid_a3c = RooRealVar("missid_transition3c","missid_transition3c",1.37096e+00 )#1.38, 0.2, 3) ## Transition point, in sigmas1



missid_f1 = RooRealVar("missid_fraction","missid_fraction",5.22734e-01 )#0.5, 0., 1.)
missid_f2 = RooRealVar("missid_fraction2","missid_fraction2",7.92744e-01)#0.5, 0., 1.)
    
    





####################################################

class BsMuMuModel:

    def __init__(self, glbin):
        self.i = str(glbin)
        i = self.i
       
        self.nbs = RooFormulaVar("NBs" + i ,"NBs" + i, "NBs*j"+i+"*f"+i, RooArgList(v["f"+i],v["nbs"],v["j"+i]))
        self.nbd = RooFormulaVar("NBd" + i ,"NBd" + i, "NBd*j"+i+"*f"+i, RooArgList(v["f"+i],v["nbd"],v["j"+i]))
        self.nbkg = RooRealVar("MuMuBkg"+i,"MuMuBkg"+i, 0,70000)
        self.nmis = RooFormulaVar("Nmis" + i ,"Nmis" + i, "Nmis*j"+i+"*f"+i, RooArgList(v["f"+i],v["nmis"],v["j"+i]))
        
        self.k = RooRealVar("MuMu_k_"+i,"MuMu_k_" + i, -1e-02,0)
        self.dk = RooRealVar("MuMu_dk_"+i,"MuMu_dk_" + i, -1e-02,0)
        self.kb = RooFormulaVar("MuMu_kb_"+i,"MuMu_kb_" + i,"MuMu_k_"+i + " + MuMu_dk_" + i, RooArgList(self.k,self.dk))
        self.bkg1 = RooExponential("bkg1 MuMu model" + i , "bkg1 MuMu model" + i, Mass,self.k)
        self.bkg2 = RooExponential("bkg2 MuMu model" + i , "bkg2 MuMu model" + i, Mass,self.kb)
        
        self.fb = RooRealVar("MuMu_f_"+i,"MuMu_f_" + i,0.5,0.,1.)
        self.bkg = RooAddPdf("bkg MuMu model" + i, "bkg MuMu model" + i, self.bkg1,self.bkg2, self.fb)
        self.Bs = RooCBShape("model Bs" + i, "model Bs"+ i, Mass, meanBs,sigma,a,n)
        self.Bd = RooCBShape("model Bd" + i, "model Bd"+ i, Mass, meanBd,sigma,a,n)

        self.missid_MSu1 = RooCBShape("missid_MSu" + "_"+ i,"missid_MSu"+ "_"+ i, Mass, missid_mean1, missid_sigma, missid_a2, missid_n2)
        self.missid_MSd1 = RooCBShape("missid_MSd"+ "_"+ i,"missid_MSd"+ "_"+ i, Mass, missid_mean1, missid_sigma, missid_a3, missid_n)
        self.missid_MSu2 = RooCBShape("missid_MSu2"+ "_"+ i,"missid_MSu2"+ "_"+ i, Mass, missid_mean2, missid_sigma2, missid_a2b, missid_n2b)
        self.missid_MSd2 = RooCBShape("missid_MSd2"+ "_"+ i,"missid_MSd2"+ "_"+ i, Mass, missid_mean2, missid_sigma2, missid_a3b, missid_nb)

        self.missid_MSu3 = RooCBShape("missid_MSu3"+ "_"+ i,"missid_MSu3"+ "_"+ i, Mass, missid_mean3, missid_sigma3, missid_a2c, missid_n2c)
        self.missid_MSd3 = RooCBShape("missid_MSd3"+ "_"+ i,"missid_MSd3"+ "_"+ i, Mass, missid_mean3, missid_sigma3, missid_a3c, missid_nc)
        self.missid_MS1 = RooAddPdf("missid_MS1"+ "_"+ i,"missid_MS1"+ "_"+ i,self.missid_MSu1,self.missid_MSd1,hh_f05)
        self.missid_MS2 = RooAddPdf("missid_MS2"+ "_"+ i,"missid_MS2"+ "_"+ i,self.missid_MSu2,self.missid_MSd2,hh_f05)
        self.missid_MS3 = RooAddPdf("missid_MS3"+ "_"+ i,"missid_MS3"+ "_"+ i,self.missid_MSu3,self.missid_MSd3,hh_f05)
        
        self.missid_sig0  = RooAddPdf("missid_Sigmodel0" + i,"missid_Sigmodel0"+i, self.missid_MS1, self.missid_MS2, missid_f1)
        self.missid_peak  = RooAddPdf("missid" + i ,"missid"+i, self.missid_sig0, self.missid_MS3, missid_f2)
        
        self.model = RooAddPdf("mumu model " + i, "mumu model " + i, RooArgList(self.bkg,self.Bs,self.Bd,self.missid_peak), RooArgList(self.nbkg,self.nbs,self.nbd,self.nmis))
        

class B2hhModel:
    def __init__(self, glbin):
        self.i = str(glbin)
        i = self.i
        #v = vars()
        """ models the signal as two peaks, each peak being a two-sided crystalball
        """
        self.MSu1 = RooCBShape("MSu"+i,"MSu"+i, Mpipi, hh_mean1, hh_sigma, hh_a2, hh_n2)
        self.MSd1 = RooCBShape("MSd"+i,"MSd"+i,   Mpipi, hh_mean1, hh_sigma, hh_a3, hh_n)
        self.MSu2 = RooCBShape("MSu2"+i,"MSu2"+i, Mpipi, hh_mean2, hh_sigma, hh_a2, hh_n2)
        self.MSd2 = RooCBShape("MSd2"+i,"MSd2"+i, Mpipi, hh_mean2, hh_sigma, hh_a3, hh_n)
        self.MS1 = RooAddPdf("MS1"+i,"MS1"+i,self.MSu1,self.MSd1,hh_f05)
        self.MS2 = RooAddPdf("MS2"+i,"MS2"+i,self.MSu2,self.MSd2,hh_f05)
        self.k = RooRealVar("hh_k_"+i,"hh_k" + i, -1e-02,0)
        self.bkg = RooExponential("bkg hh model" + i , "bkg hh model" + i, Mpipi,self.k)
        self.shoulder = RooGaussian("shoulder"+i,"shoulder+i",Mpipi, sh_mean, sh_sigma)
        self.sig  = RooAddPdf("Sigmodel" + i,"Sigmodel" + i, self.MS1, self.MS2, hh_f1)

        self.nsig = RooFormulaVar("Nhh"+i, "Nhh"+i,"Nhh*f"+i, RooArgList(Nhh,v["f"+i]))
        self.nEbkg = RooRealVar("hh exp bkg " + i, "hh exp bkg " + i,0,1e06)
        self.nPbkg = RooRealVar("hh phys bkg " + i, "hh phys bkg " + i,0,1e06)

        self.model = RooAddPdf("hh model " + i, "hh model " + i,RooArgList(self.sig,self.bkg,self.shoulder), RooArgList(self.nsig,self.nEbkg,self.nPbkg))
                                 
        
        #return 1

mm1 = BsMuMuModel(1)
mm2 = BsMuMuModel(2)
mm3 = BsMuMuModel(3)
mm4 = BsMuMuModel(4)


hh1 = B2hhModel(1)
hh2 = B2hhModel(2)
hh3 = B2hhModel(3)
hh4 = B2hhModel(4)

fiter = RooSimultaneous("fitter", "fitter", cat)
fiter.addPdf(hh1.model,"hh bin1")
fiter.addPdf(hh2.model,"hh bin2")
fiter.addPdf(hh3.model,"hh bin3")
fiter.addPdf(hh4.model,"hh bin4")

fiter.addPdf(mm1.model,"mumu bin1")
fiter.addPdf(mm2.model,"mumu bin2")
fiter.addPdf(mm3.model,"mumu bin3")
fiter.addPdf(mm4.model,"mumu bin4")


######  Prepare files

kullback = "mu1_track_CloneDist>5000 && mu2_track_CloneDist>5000"
hhcuts = "Bmass>4800 && Bmass<5700 && mu1_pidPreslMom && mu2_pidPreslMom && mu1_pidInAcc && mu2_pidInAcc && " + kullback + "&& Blife_ps<7.36 && Bpt>500 && mu1ptot<1e06 && mu2ptot<1e06 && L0Tis && Hlt1Tis"


mainF = TFile("/afs/cern.ch/user/d/diegoms/vol5/Bs2mumu341.root")
mainF2 = TFile("/afs/cern.ch/user/d/diegoms/vol5/B2hhcalib.root")
thh = mainF2.Get("B2hh")
tmm = mainF.Get("Bs2MuMu")

fhh1 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_hh1.root","recreate")
thh1 = thh.CopyTree(hhcuts + "&& !mu1ismu && !mu2ismu && BDTflatNEW >0.2 && BDTflatNEW<0.4")
thh1.Write()
fhh1.Close()
fhh1 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_hh1.root")
thh1 = fhh1.Get("B2hh")
datahh1 = RooDataSet("datahh1","datahh1",thh1,RooArgSet(Mpipi))


fhh2 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_hh2.root","recreate")
thh2 = thh.CopyTree(hhcuts + "&& !mu1ismu && !mu2ismu && BDTflatNEW >0.4 && BDTflatNEW<0.6")
thh2.Write()
fhh2.Close()
fhh2 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_hh2.root")
thh2 = fhh2.Get("B2hh")
datahh2 = RooDataSet("datahh2","datahh2",thh2,RooArgSet(Mpipi))


fhh3 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_hh3.root","recreate")
thh3 = thh.CopyTree(hhcuts + "&& !mu1ismu && !mu2ismu && BDTflatNEW >0.6 && BDTflatNEW<0.8")
thh3.Write()
fhh3.Close()
fhh3 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_hh3.root")
thh3 = fhh3.Get("B2hh")
datahh3 = RooDataSet("datahh3","datahh3",thh3,RooArgSet(Mpipi))

fhh4 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_hh4.root","recreate")
thh4 = thh.CopyTree(hhcuts + "&& !mu1ismu && !mu2ismu && BDTflatNEW >0.8")
thh4.Write()
fhh4.Close()
fhh4 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_hh4.root")
thh4 = fhh4.Get("B2hh")
datahh4 = RooDataSet("datahh4","datahh4",thh4,RooArgSet(Mpipi))

############################################ Bs --> mm
mmcuts = kullback + "&& Blife_ps<7.36 && Bpt>500 && mu1ptot<1e06 && mu2ptot<1e06"


fmm1 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_mm1.root","recreate")
tmm1 = tmm.CopyTree(mmcuts + "&& BDTflatNEW >0.2 && BDTflatNEW<0.4")
tmm1.Write()
fmm1.Close()
fmm1 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_mm1.root")
tmm1 = fmm1.Get("Bs2MuMu")
datamm1 = RooDataSet("datamm1","datamm1",tmm1,RooArgSet(Mass))


fmm2 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_mm2.root","recreate")
tmm2 = tmm.CopyTree(mmcuts + "&& BDTflatNEW >0.4 && BDTflatNEW<0.6")
tmm2.Write()
fmm2.Close()
fmm2 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_mm2.root")
tmm2 = fmm2.Get("Bs2MuMu")
datamm2 = RooDataSet("datamm2","datamm2",tmm2,RooArgSet(Mass))

fmm3 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_mm3.root","recreate")
tmm3 = tmm.CopyTree(mmcuts + "&& BDTflatNEW >0.6 && BDTflatNEW<0.8")
tmm3.Write()
fmm3.Close()
fmm3 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_mm3.root")
tmm3 = fmm3.Get("Bs2MuMu")
datamm3 = RooDataSet("datamm3","datamm3",tmm3,RooArgSet(Mass))

fmm4 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_mm4.root","recreate")
tmm4 = tmm.CopyTree(mmcuts + "&& BDTflatNEW >0.8")
tmm4.Write()
fmm4.Close()
fmm4 = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_mm4.root")
tmm4 = fmm4.Get("Bs2MuMu")
datamm4 = RooDataSet("datamm4","datamm4",tmm4,RooArgSet(Mass))

hhData = RooDataSet("hh data", "hh data", RooArgSet(Mpipi,Mass), RooFit.Index(cat), RooFit.Import("hh bin1", datahh1), RooFit.Import("hh bin2", datahh2), RooFit.Import("hh bin3", datahh3), RooFit.Import("hh bin4", datahh4))
mumuData = RooDataSet("mumu data", "mumu data", RooArgSet(Mpipi, Mass), RooFit.Index(cat), RooFit.Import("mumu bin1", datamm1), RooFit.Import("mumu bin2", datamm2), RooFit.Import("mumu bin3", datamm3),RooFit.Import("mumu bin4", datamm4))
#allData = RooDataSet("all data", "all data", RooArgSet(Mass,Mass), RooFit.Index(cat), RooFit.Import("hh bin1", datahh1), RooFit.Import("hh bin2", datahh2), RooFit.Import("hh bin3", datahh3), RooFit.Import("hh bin4", datahh4), RooFit.Import("mumu bin1", datamm1), RooFit.Import("mumu bin2", datamm2), RooFit.Import("mumu bin3", datamm3))#, RooFit.Import("mumu bin4", datamm4))

allData = mumuData.Clone() #RooDataSet("all data","all data", RooArgSet(Mass,cat), RooFit.Import(hhData), RooFit.Import(mumuData))
allData.append(hhData)
#BREAK
fiter.fitTo(allData, RooFit.Minos(kTRUE))

## nll = fiter.createNLL(allData,RooFit.NumCPU(2))
## #nll.migrad()

## pl_Bs = nll.createProfile(RooArgSet(nbs))
## pl_Bd = nll.createProfile(RooArgSet(bdbs))

## c3 = TCanvas()
## c3.Divide(2,1)
## c3.cd(1)
## frBs = nbs.frame()
## pl_Bs.plotOn(frBs)
## frBs.Draw()
## c3.cd(2)
## frBd = bdbs.frame()
## pl_Bd.plotOn(frBd)
## frBd.Draw()


#mm4.model.fitTo(datamm4)
#fr = Mass.frame()
#datamm4.plotOn(fr)
#mm4.model.plotOn(fr)
#fr.Draw()

## hh4.model.fitTo(datahh4)
## fr = Mass.frame()
## datahh4.plotOn(fr)
## hh4.model.plotOn(fr)
## fr.Draw()
c = TCanvas()
c.Divide(2,2)
c.cd(1)
fr1 = Mass.frame()
datamm1.plotOn(fr1)#,RooFit.Binning(20))#, RooFit.Cut("Bmass<4"))
mm1.model.plotOn(fr1)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
mm1.model.plotOn(fr1, RooFit.Components("model Bs1"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
mm1.model.plotOn(fr1, RooFit.Components("model Bd1"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
mm1.model.plotOn(fr1, RooFit.Components("missid1"),RooFit.LineColor(kMagenta))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
fr1.Draw()
c.cd(2)
fr2 = Mass.frame()
datamm2.plotOn(fr2)#,RooFit.Binning(20))#, RooFit.Cut("Bmass<4"))
mm2.model.plotOn(fr2)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
mm2.model.plotOn(fr2, RooFit.Components("model Bs2"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
mm2.model.plotOn(fr2, RooFit.Components("model Bd2"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
mm2.model.plotOn(fr2, RooFit.Components("missid2"),RooFit.LineColor(kMagenta))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
fr2.Draw()
c.cd(3)
fr3 = Mass.frame()
datamm3.plotOn(fr3)#,RooFit.Binning(10))#, RooFit.Cut("Bmass<4"))
mm3.model.plotOn(fr3)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
mm3.model.plotOn(fr3, RooFit.Components("model Bs3"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
mm3.model.plotOn(fr3, RooFit.Components("model Bd3"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
mm3.model.plotOn(fr3, RooFit.Components("missid3"),RooFit.LineColor(kMagenta))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
fr3.Draw()
c.cd(4)
fr4 = Mass.frame()
datamm4.plotOn(fr4)#, RooFit.Binning(10))#, RooFit.Cut("Bmass<4"))
mm4.model.plotOn(fr4)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
mm4.model.plotOn(fr4, RooFit.Components("model Bs4"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
mm4.model.plotOn(fr4, RooFit.Components("model Bd4"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
mm4.model.plotOn(fr4, RooFit.Components("missid4"),RooFit.LineColor(kMagenta))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
fr4.Draw()

##############################

c2 = TCanvas()
c2.Divide(2,2)
c2.cd(1)
hfr1 = Mpipi.frame()
datahh1.plotOn(hfr1)#, RooFit.Cut("Bmass<4"))
hh1.model.plotOn(hfr1)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
hh1.model.plotOn(hfr1, RooFit.Components("Sigmodel1"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
hh1.model.plotOn(hfr1, RooFit.Components("shoulder1"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
hfr1.Draw()

c2.cd(2)
hfr2 = Mpipi.frame()
datahh2.plotOn(hfr2)#, RooFit.Cut("Bmass<4"))
hh2.model.plotOn(hfr2)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
hh2.model.plotOn(hfr2, RooFit.Components("Sigmodel2"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
hh2.model.plotOn(hfr2, RooFit.Components("shoulder2"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
hfr2.Draw()

c2.cd(3)
hfr3 = Mpipi.frame()
datahh3.plotOn(hfr3)#, RooFit.Cut("Bmass<4"))
hh3.model.plotOn(hfr3)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
hh3.model.plotOn(hfr3, RooFit.Components("Sigmodel3"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
hh3.model.plotOn(hfr3, RooFit.Components("shoulder3"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
hfr3.Draw()

c2.cd(4)
hfr4 = Mpipi.frame()
datahh4.plotOn(hfr4)#, RooFit.Cut("Bmass<4"))
hh4.model.plotOn(hfr4)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
hh4.model.plotOn(hfr4, RooFit.Components("Sigmodel4"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
hh4.model.plotOn(hfr3, RooFit.Components("shoulder4"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
hfr4.Draw()



#############

