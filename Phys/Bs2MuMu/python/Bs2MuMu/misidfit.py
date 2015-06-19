from ROOT import *
#from SomeMassModels import B2hhmodels as B
#f = TFile("/afs/cern.ch/user/d/diegoms/vol5/MCbhh_mixed_X_misidp_rnd0.0.root")
f = TFile("~/vol5/MCbhh_mixed_2012_misidp_0mistic_fdfsm1s_rnd0.0.root")#"/afs/cern.ch/user/d/diegoms/vol5/MCbhh_mixed_X_misidp_rnd0.0.root")
t = f.Get("T")
#BREAK
## op = B.InclusiveFiter01(t,"Bmass", "Bmass>4800 && Bmass<5700", fixtails = 0)
## op.nbkg.setVal(0)
## op.nbkg.setConstant(kTRUE)
## op.a2.setConstant(kFALSE)
## op.a2.setMin(-3)
## op.a2.setMax(-0.5)
## op.a3.setMin(0.1)
## op.a3.setMax(3)
## op.fsh.setConstant(kTRUE)
## op.bkg_indx.setConstant(kTRUE)
## op.a3.setConstant(kFALSE)
## op.f1.setConstant(kFALSE)
## op.f1.setMin(0)
## op.f1.setMax(1)
## op.d1.setConstant(kFALSE)
## op.d1.setMin(2)
## op.d1.setMax(200)
## op.n.setConstant(kFALSE)
## #op.n.setMin(0.8)
## #op.n.setMin)

## op.n2.setConstant(kFALSE)
## op.sigma.setMax(100)
## op.fit()
mass = RooRealVar("Bmass","Bmass", 4800, 5500)
massS = mass#RooFormulaVar("Bmass+100","Bmass+100",RooArgList(mass))
misid = RooDataSet("misid","misid", t, RooArgSet(mass))


missid_mean1 = RooRealVar("missid_mean1","missid_mean1",5.20586e+03,5050, 5600)#5168.)
missid_d1= RooRealVar("missid_d1","missid_d1", 3.65105e+01, 20., 200.)
missid_d2= RooRealVar("missid_d2","missid_d2", 2.50666e+01, 20., 200.)
missid_mean2 = RooFormulaVar("missid_mean2","missid_mean2", "missid_mean1 + missid_d1" ,RooArgList(missid_mean1,missid_d1) )
missid_mean3 = RooFormulaVar("missid_mean3","missid_mean3", "missid_mean2 + missid_d2" ,RooArgList(missid_mean2,missid_d2) )
missid_sigma = RooRealVar("missid_sigma","missid_sigma",1.23888e+02 , 20.,200.)
missid_sigma2 = RooRealVar("missid_sigma2","missid_sigma2", 3.63338e+01,20.,100.)
missid_sigma3 = RooRealVar("missid_sigma3","missid_sigma3", 2.30405e+01 ,20.,100.)

missid_n = RooRealVar("missid_exponent", "missid_exponent",1.16669e+02,  0.1, 120 )
missid_n2 = RooRealVar("missid_exponent2", "missid_exponent2",   9.28 ,.1, 120)

missid_a2 = RooRealVar("missid_transition2","missid_transition2",-1.19, -3, -0.2) ## Transition point, in sigmas
missid_a3 = RooRealVar("missid_transition3","missid_transition3",1.38, 0.2, 3) ## Transition point, in sigmas

missid_nb = RooRealVar("missid_exponentb", "missid_exponentb",1.,  0.1, 120 )
missid_n2b = RooRealVar("missid_exponent2b", "missid_exponent2b",  9.28 ,.1, 120)

missid_a2b = RooRealVar("missid_transition2b","missid_transition2b", -1.19, -3, -0.2) ## Transition point, in sigmas
missid_a3b = RooRealVar("missid_transition3b","missid_transition3b",1.38, 0.2, 3) ## Transition point, in sigmas1


missid_nc = RooRealVar("missid_exponentc", "missid_exponentc",1.,  0.1, 12 )
missid_n2c = RooRealVar("missid_exponent2c", "missid_exponent2c",  9.28 ,.1, 12)

missid_a2c = RooRealVar("missid_transition2c","missid_transition2c",  -1.19, -3, -0.2) ## Transition point, in sigmas
missid_a3c = RooRealVar("missid_transition3c","missid_transition3c",1.38, 0.2, 3) ## Transition point, in sigmas1

missid_MSu1 = RooCBShape("missid_MSu","missid_MSu", massS, missid_mean1, missid_sigma, missid_a2, missid_n2)
missid_MSd1 = RooCBShape("missid_MSd","missid_MSd", massS, missid_mean1, missid_sigma, missid_a3, missid_n)
missid_MSu2 = RooCBShape("missid_MSu2","missid_MSu2", massS, missid_mean2, missid_sigma2, missid_a2b, missid_n2b)
missid_MSd2 = RooCBShape("missid_MSd2","missid_MSd2", massS, missid_mean2, missid_sigma2, missid_a3b, missid_nb)

missid_MSu3 = RooCBShape("missid_MSu3","missid_MSu3", massS, missid_mean3, missid_sigma3, missid_a2c, missid_n2c)
missid_MSd3 = RooCBShape("missid_MSd3","missid_MSd3", massS, missid_mean3, missid_sigma3, missid_a3c, missid_nc)

missid_f05 = RooRealVar("missid_0.55", "missid_0.5", 0.5) ### This is here just to create double crystalballs (I think)
missid_MS1 = RooAddPdf("missid_MS1","missid_MS1",missid_MSu1,missid_MSd1,missid_f05)
missid_MS2 = RooAddPdf("missid_MS2","missid_MS2",missid_MSu2,missid_MSd2,missid_f05)
missid_MS3 = RooAddPdf("missid_MS3","missid_MS3",missid_MSu3,missid_MSd3,missid_f05)
missid_f1 = RooRealVar("missid_fraction","missid_fraction",0.5, 0., 1.)
missid_f2 = RooRealVar("missid_fraction2","missid_fraction2",0.5, 0., 1.)
    
    
missid_sig0  = RooAddPdf("missid_Sigmodel0","missid_Sigmodel0", missid_MS1, missid_MS2, missid_f1)

missid_sig  = RooAddPdf("missid_Sigmodel","missid_Sigmodel", missid_sig0, missid_MS3, missid_f2)

hmisid = RooDataHist("h","h", RooArgSet(mass),misid)


#pdf = RooKeysPdf("misid pdf", "misid pdf"nn, mass, misid, 0,20)

missid_sig.fitTo(hmisid)
fr = mass.frame()
misid.plotOn(fr)
missid_sig.plotOn(fr)
fr.Draw()
