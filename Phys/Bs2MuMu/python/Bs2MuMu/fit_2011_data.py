from ROOT import *
from Bs2MuMuParams import toytable_test_1fb_AleInput as TheTable
from NTuple_names import *
from constrain_funcs import *

#if "alpha_fit" not in dir(TheTable):
 #   print "INVENTING VALUE FOR THE NORMALIZATION FACTOR"
  #  TheTable.alpha_fit = 0.31838135587209603
   # TheTable.alpha_fitErr = 0.027318398127746596

if "NormBu_fullmass" not in dir(TheTable):
    print "INVENTING VALUE FOR THE NORMALIZATION FACTOR 2011"
    TheTable.NormBu_fullmass = TheTable.NormBu
    TheTable.NormKPi_fullmass = TheTable.NormKPi
    TheTable.NormBu_fullmassErr = TheTable.NormBuErr
    TheTable.NormKPi_fullmassErr = TheTable.NormKPiErr
    
#massname = "B_mass"
samplename = "sample"
#bdtname = "BDTflat_BDT9_BDTScut05"
Binning = {}
Binning[bdtname] = [0, .25,.4,.5,.6,.7,.8,.9,1.]


COSME = 0  ### fix many np to compare with Cosme's stat error
SERENA = 1 ### Add gaussian B->pimunu based on Serena's numbers/model
UNIFORM_KAPPA = 0
DOUBLE_EXPO = 0
FORCE_INDEX = 1
USE_7_BINS = 0
BDT_DEN = 1.76201e+04 
BDT_PDF = {"2":5.33030e+02*1./BDT_DEN, "3":1.26436e+02*1./BDT_DEN, "4":4.53571e+01*1./BDT_DEN, "5":3.15557e+01*1./BDT_DEN,"6":7.38383e+00*1./BDT_DEN, "7":9.30460e+00*1./BDT_DEN, "8": 1.97407e+00*1./BDT_DEN}

if DOUBLE_EXPO: Mass = RooRealVar(massname,massname,4170, 6565)
#else: Mass = RooRealVar(massname,massname,5432.96 - 120,6000)#4900, 6000)
else: Mass = RooRealVar(massname,massname,4900, 6000)
cat =  RooCategory(samplename, samplename)
for i in range(1,9): cat.defineType("mumu bin" + str(i))
justine = {"T":1., 0:1., 1: TheTable.Justine2, 2:TheTable.Justine3 , 3: TheTable.Justine4, 4: TheTable.Justine5, 5:TheTable.Justine6 , 6: TheTable.Justine7, 7: TheTable.Justine8}
mid_idf = [1.,TheTable.MisIDfBDTBin2,TheTable.MisIDfBDTBin3,TheTable.MisIDfBDTBin4,TheTable.MisIDfBDTBin5,TheTable.MisIDfBDTBin6,TheTable.MisIDfBDTBin7,TheTable.MisIDfBDTBin8]
j1 = RooRealVar("j1","j1",justine[0])
j2 = RooRealVar("j2","j2",justine[1])
j3 = RooRealVar("j3","j3",justine[2])
j4 = RooRealVar("j4","j4",justine[3])

j5 = RooRealVar("j5","j5",justine[4])
j6 = RooRealVar("j6","j6",justine[5])
j7 = RooRealVar("j7","j7",justine[6])
j8 = RooRealVar("j8","j8",justine[7])

missid_corr1 = RooRealVar("missid_corr1","missid_corr1",mid_idf[0])
missid_corr2 = RooRealVar("missid_corr2","missid_corr2",mid_idf[1])
missid_corr3 = RooRealVar("missid_corr3","missid_corr3",mid_idf[2])
missid_corr4 = RooRealVar("missid_corr4","missid_corr4",mid_idf[3])

missid_corr5 = RooRealVar("missid_corr5","missid_corr5",mid_idf[4])
missid_corr6 = RooRealVar("missid_corr6","missid_corr6",mid_idf[5])
missid_corr7 = RooRealVar("missid_corr7","missid_corr7",mid_idf[6])
missid_corr8 = RooRealVar("missid_corr8","missid_corr8",mid_idf[7])

NormBu, NormBu_cons = createConst(TheTable.NormBu_fullmass, TheTable.NormBu_fullmassErr, "NormBu", 1) 
NormKPi, NormKPi_cons = createConst(TheTable.NormKPi_fullmass, TheTable.NormKPi_fullmassErr, "NormKPi", 1)
NormPhi, NormPhi_cons = createConst(TheTable.NormPhi_fullmass, TheTable.NormPhi_fullmassErr, "NormPhi", 1)
fdfs, fdfs_cons = createConst(TheTable.fsfd, sqrt(TheTable.fsfdErrP**2 + TheTable.fsfdErrN**2)/sqrt(2.), "fdfs", 1)

NhhTOT, NhhTOT_cons = createConst(TheTable.TisTot,TheTable.TisErrTot, "NhhTOT", 1)  
#Nhh1 = RooRealVar("Nhh1","Nhh1",1000,100,9000)
#Nhh1_cons = RooGaussian("Nhh1_const","Nhh1_const",Nhh1,RooFit.RooConst(TheTable.Tis1),RooFit.RooConst(TheTable.Tis1Err)) 
Nhh2, Nhh2_cons = createConst(TheTable.Tis2,TheTable.TisErr2,"Nhh2",1)
Nhh3, Nhh3_cons = createConst(TheTable.Tis3,TheTable.TisErr3,"Nhh3",1)
Nhh4, Nhh4_cons = createConst(TheTable.Tis4,TheTable.TisErr4,"Nhh4",1)
Nhh5, Nhh5_cons = createConst(TheTable.Tis5,TheTable.TisErr5,"Nhh5",1)
Nhh6, Nhh6_cons = createConst(TheTable.Tis6,TheTable.TisErr6,"Nhh6",1)
Nhh7, Nhh7_cons = createConst(TheTable.Tis7,TheTable.TisErr7,"Nhh7",1)
Nhh8, Nhh8_cons = createConst(TheTable.Tis8,TheTable.TisErr8,"Nhh8",1)
Nhh1 = RooFormulaVar("Nhh1","Nhh1", "NhhTOT- (Nhh2 + Nhh3 +Nhh4+Nhh5 + Nhh6 + Nhh7 +Nhh8)",RooArgList(NhhTOT,Nhh2,Nhh3,Nhh4,Nhh5,Nhh6,Nhh7,Nhh8))

norm_formula = "(((NormBu/pow(4.3306713840400002e-12 ,2)+(NormKPi/NhhTOT)/(pow(1.24054854979e-07/NhhTOT,2.) + pow(NormKPi*1312.3387520000001/pow(NhhTOT,2) ,2.)))/(pow(4.3306713840400002e-12 ,-2.)+(1./(pow(1.24054854979e-07/NhhTOT,2.) + pow(NormKPi*1312.3387520000001/pow(NhhTOT,2) ,2.)) )))*fdfs/((1./(pow(4.3306713840400002e-12 ,-2.)+(1./(pow(1.24054854979e-07/NhhTOT,2.) + pow(NormKPi*1312.3387520000001/pow(NhhTOT,2) ,2.)) )))*pow(fdfs,2.) + pow(((NormBu/pow(4.3306713840400002e-12 ,2)+(NormKPi/NhhTOT)/(pow(1.24054854979e-07/NhhTOT,2.) + pow(NormKPi*1312.3387520000001/pow(NhhTOT,2) ,2.)))/(pow(4.3306713840400002e-12 ,-2.)+(1./(pow(1.24054854979e-07/NhhTOT,2.) + pow(NormKPi*1312.3387520000001/pow(NhhTOT,2) ,2.)) )))*0.28756189594500003 ,2)) +  NormPhi/pow(1.12333757341e-10,2))/(1./((1./(pow(4.3306713840400002e-12 ,-2.)+(1./(pow(1.24054854979e-07/NhhTOT,2.) + pow(NormKPi*1312.3387520000001/pow(NhhTOT,2) ,2.)) )))*pow(fdfs,2.) + pow(((NormBu/pow(4.3306713840400002e-12 ,2)+(NormKPi/NhhTOT)/(pow(1.24054854979e-07/NhhTOT,2.) + pow(NormKPi*1312.3387520000001/pow(NhhTOT,2) ,2.)))/(pow(4.3306713840400002e-12 ,-2.)+(1./(pow(1.24054854979e-07/NhhTOT,2.) + pow(NormKPi*1312.3387520000001/pow(NhhTOT,2) ,2.)) )))*0.28756189594500003 ,2)) + 1./pow(1.12333757341e-10,2))*(1e09)"


alpha_s = RooFormulaVar("alpha_S","alpha_S" , norm_formula , RooArgList(NormBu,NormKPi,NormPhi,fdfs,NhhTOT))
#alpha_s, alpha_s_cons = createConst(TheTable.alpha_fit, TheTable.alpha_fitErr, "alpha_S",1)# = RooRealVar("alpha_S","alpha_s", 0.31838135587209603,0.001,0.6) 
BR_s = RooRealVar("BRs","BRs", 1,0.,10)
nbs = RooFormulaVar("NBs","NBs", "BRs/alpha_S", RooArgList(alpha_s,BR_s))
misid_global_factor, misid_global_cons =createConst(TheTable.MisIDGlobalFactor,TheTable.MisIDGlobalFactorErr, "misidP") 


#bdbs = RooRealVar("bdbs","bdbs", 0.,5)
#nbd = RooFormulaVar("NBd","NBd","bdbs*NBs",RooArgList(nbs,bdbs))
nbd = RooRealVar("NBd","NBd",5.,0.,20)
a = RooRealVar("CB_trans","CB_trans", TheTable.CBTrans, 1.5,3)
n = RooRealVar( "n", "n", 1)

meanBs, meanBs_cons = createConst(TheTable.MassMeanBs, TheTable.MassMeanErrBs, "meanBs", 1) 
meanBd, meanBd_cons = createConst(TheTable.MassMeanBd, TheTable.MassMeanErrBd, "meanBd", 1) 

sigmaBs, sigmaBs_cons = createConst(TheTable.MassResoBs, TheTable.MassResoErrBs, "sigmaBs", 1) 
sigmaBd, sigmaBd_cons = createConst(TheTable.MassResoBd, TheTable.MassResoErrBd, "sigmaBd", 1) 

a_cons = RooGaussian("trans_cons","trans_cons",a,RooFit.RooConst(TheTable.CBTrans),RooFit.RooConst(TheTable.CBTransErr))


nmis = RooFormulaVar("Nmis","Nmis", "NhhTOT*misidP",RooArgList(NhhTOT,misid_global_factor))#,40)
f2 = RooFormulaVar("f2","f2", "Nhh2/NhhTOT",RooArgList(Nhh2,NhhTOT))
f3 = RooFormulaVar("f3","f3", "Nhh3/NhhTOT",RooArgList(Nhh3,NhhTOT))
f4 = RooFormulaVar("f4","f4", "Nhh4/NhhTOT",RooArgList(Nhh4,NhhTOT))
f5 = RooFormulaVar("f5","f5", "Nhh5/NhhTOT",RooArgList(Nhh5,NhhTOT))
f6 = RooFormulaVar("f6","f6", "Nhh6/NhhTOT",RooArgList(Nhh6,NhhTOT))
f7 = RooFormulaVar("f7","f7", "Nhh7/NhhTOT",RooArgList(Nhh7,NhhTOT))
f8 = RooFormulaVar("f8","f8", "Nhh8/NhhTOT",RooArgList(Nhh8,NhhTOT))
f1 = RooFormulaVar("f1", "f1", "(1-f2-f3-f4-f5-f6-f7-f8)", RooArgList(f2,f3,f4,f5,f6,f7,f8))

v = vars()

############ MISID
missid_mean1 = RooRealVar("missid_mean1","missid_mean1",5.09168e+03+100)#5050, 5600)#5168.)
missid_d1= RooRealVar("missid_d1","missid_d1", 4.01034e+01)#72.4, 20., 200.)
missid_d2= RooRealVar("missid_d2","missid_d2", 4.03549e+01)#72.4, 20., 200.)
missid_mean2 = RooFormulaVar("missid_mean2","missid_mean2", "missid_mean1 + missid_d1" ,RooArgList(missid_mean1,missid_d1) )
missid_mean3 = RooFormulaVar("missid_mean3","missid_mean3", "missid_mean2 + missid_d2" ,RooArgList(missid_mean2,missid_d2) )
missid_sigma = RooRealVar("missid_sigma","missid_sigma",1.06965e+02  )# 20.,200.)
missid_sigma2 = RooRealVar("missid_sigma2","missid_sigma2",  3.17942e+01)#20.,100.)
missid_sigma3 = RooRealVar("missid_sigma3","missid_sigma3", 3.00653e+01 )#20.,100.)

missid_n = RooRealVar("missid_exponent", "missid_exponent",2.63840e+01  )#1.,  0.1, 120 )
missid_n2 = RooRealVar("missid_exponent2", "missid_exponent2",  7.65872e+00 )# 9.28 ,.1, 120)

missid_a2 = RooRealVar("missid_transition2","missid_transition2",-1.18668e+00 )#-1.19, -3, -0.2) ## Transition point, in sigmas
missid_a3 = RooRealVar("missid_transition3","missid_transition3",2.98721e+00 )#1.38, 0.2, 3) ## Transition point, in sigmas

missid_nb = RooRealVar("missid_exponentb", "missid_exponentb",2.67165e+00)#1.,  0.1, 120 )
missid_n2b = RooRealVar("missid_exponent2b", "missid_exponent2b",  3.16407e+01   )#9.28 ,.1, 120)

missid_a2b = RooRealVar("missid_transition2b","missid_transition2b", -1.85453e+00  )#-1.19, -3, -0.2) ## Transition point, in sigmas
missid_a3b = RooRealVar("missid_transition3b","missid_transition3b", 6.69876e-01  )#1.38, 0.2, 3) ## Transition point, in sigmas1


missid_nc = RooRealVar("missid_exponentc", "missid_exponentc",1.00041e-01  )#1.,  0.1, 12 )
missid_n2c = RooRealVar("missid_exponent2c", "missid_exponent2c",   1.85700e+00)#9.28 ,.1, 12)

missid_a2c = RooRealVar("missid_transition2c","missid_transition2c", -1.75217e+00)# -1.19, -3, -0.2) ## Transition point, in sigmas
missid_a3c = RooRealVar("missid_transition3c","missid_transition3c",1.64220e+00 )#1.38, 0.2, 3) ## Transition point, in sigmas1



missid_f1 = RooRealVar("missid_fraction","missid_fraction", 7.02356e-01 )#0.5, 0., 1.)
missid_f2 = RooRealVar("missid_fraction2","missid_fraction2",6.66982e-01)#0.5, 0., 1.)
hh_f05 = RooRealVar("0.55", "0.5", 0.5) ### This is here just to create double crystalballs (I think) I don't remember

### B0-> Pi Mu Nu bkg

sigmaPiMuNu1,sigmaPiMuNu1_cons = createBifurConst(TheTable.sigmaPiMuNu1,TheTable.sigmaPiMuNu1ErrMinus,TheTable.sigmaPiMuNu1ErrPlus, "sigmaPiMuNu1")
meanPiMuNu1,meanPiMuNu1_cons = createBifurConst(TheTable.meanPiMuNu1,TheTable.meanPiMuNu1ErrMinus,TheTable.meanPiMuNu1ErrPlus,  "meanPiMuNu1")

sigmaPiMuNu2,sigmaPiMuNu2_cons = createBifurConst(TheTable.sigmaPiMuNu2,TheTable.sigmaPiMuNu2ErrMinus,TheTable.sigmaPiMuNu2ErrPlus, "sigmaPiMuNu2")
meanPiMuNu2,meanPiMuNu2_cons = createBifurConst(TheTable.meanPiMuNu2,TheTable.meanPiMuNu2ErrMinus,TheTable.meanPiMuNu2ErrPlus,  "meanPiMuNu2")

sigmaPiMuNu3,sigmaPiMuNu3_cons = createBifurConst(TheTable.sigmaPiMuNu3,TheTable.sigmaPiMuNu3ErrMinus,TheTable.sigmaPiMuNu3ErrPlus, "sigmaPiMuNu3")
meanPiMuNu3,meanPiMuNu3_cons = createBifurConst(TheTable.meanPiMuNu3,TheTable.meanPiMuNu3ErrMinus,TheTable.meanPiMuNu3ErrPlus,  "meanPiMuNu3")

sigmaPiMuNu4,sigmaPiMuNu4_cons = createBifurConst(TheTable.sigmaPiMuNu4,TheTable.sigmaPiMuNu4ErrMinus,TheTable.sigmaPiMuNu4ErrPlus, "sigmaPiMuNu4")
meanPiMuNu4,meanPiMuNu4_cons = createBifurConst(TheTable.meanPiMuNu4,TheTable.meanPiMuNu4ErrMinus,TheTable.meanPiMuNu4ErrPlus,  "meanPiMuNu4")

sigmaPiMuNu5,sigmaPiMuNu5_cons = createBifurConst(TheTable.sigmaPiMuNu5,TheTable.sigmaPiMuNu5ErrMinus,TheTable.sigmaPiMuNu5ErrPlus, "sigmaPiMuNu5")
meanPiMuNu5,meanPiMuNu5_cons = createBifurConst(TheTable.meanPiMuNu5,TheTable.meanPiMuNu5ErrMinus,TheTable.meanPiMuNu5ErrPlus,  "meanPiMuNu5")

sigmaPiMuNu6,sigmaPiMuNu6_cons = createBifurConst(TheTable.sigmaPiMuNu6,TheTable.sigmaPiMuNu6ErrMinus,TheTable.sigmaPiMuNu6ErrPlus, "sigmaPiMuNu6")
meanPiMuNu6,meanPiMuNu6_cons = createBifurConst(TheTable.meanPiMuNu6,TheTable.meanPiMuNu6ErrMinus,TheTable.meanPiMuNu6ErrPlus,  "meanPiMuNu6")

sigmaPiMuNu7,sigmaPiMuNu7_cons = createBifurConst(TheTable.sigmaPiMuNu7,TheTable.sigmaPiMuNu7ErrMinus,TheTable.sigmaPiMuNu7ErrPlus, "sigmaPiMuNu7")
meanPiMuNu7,meanPiMuNu7_cons = createBifurConst(TheTable.meanPiMuNu7,TheTable.meanPiMuNu7ErrMinus,TheTable.meanPiMuNu7ErrPlus,  "meanPiMuNu7")

sigmaPiMuNu8,sigmaPiMuNu8_cons = createBifurConst(TheTable.sigmaPiMuNu8,TheTable.sigmaPiMuNu8ErrMinus,TheTable.sigmaPiMuNu8ErrPlus, "sigmaPiMuNu8")
meanPiMuNu8,meanPiMuNu8_cons = createBifurConst(TheTable.meanPiMuNu8,TheTable.meanPiMuNu8ErrMinus,TheTable.meanPiMuNu8ErrPlus,  "meanPiMuNu8")


PiMuNu, PiMuNu_cons = createConst(TheTable.PiMuNuYield, TheTable.PiMuNuYieldErr, "PiMuNu",1)
PiMuNu2, PiMuNu2_cons = createConst(TheTable.PiMuNu2, TheTable.PiMuNu2Err, "PiMuNu2",1)
PiMuNu3, PiMuNu3_cons = createConst(TheTable.PiMuNu3, TheTable.PiMuNu3Err, "PiMuNu3",1)
PiMuNu4, PiMuNu4_cons = createConst(TheTable.PiMuNu4, TheTable.PiMuNu4Err, "PiMuNu4",1)
PiMuNu5, PiMuNu5_cons = createConst(TheTable.PiMuNu5, TheTable.PiMuNu5Err, "PiMuNu5",1)
PiMuNu6, PiMuNu6_cons = createConst(TheTable.PiMuNu6, TheTable.PiMuNu6Err, "PiMuNu6",1)
PiMuNu7, PiMuNu7_cons = createConst(TheTable.PiMuNu7, TheTable.PiMuNu7Err, "PiMuNu7",1)
PiMuNu8, PiMuNu8_cons = createConst(TheTable.PiMuNu8, TheTable.PiMuNu8Err, "PiMuNu8",1)


PiMuNu1 = RooFormulaVar("PiMuNu1","1-PiMuNu8-PiMuNu7 - PiMuNu6 - PiMuNu5-PiMuNu4 -PiMuNu3-PiMuNu2",RooArgList(PiMuNu2,PiMuNu3,PiMuNu4,PiMuNu5,PiMuNu6,PiMuNu7, PiMuNu8))


### Bs --> Kmu nu
sigmaPiMuMu1,sigmaPiMuMu1_cons = createBifurConst(TheTable.sigmaPiMuMu1,TheTable.sigmaPiMuMu1ErrMinus,TheTable.sigmaPiMuMu1ErrPlus, "sigmaPiMuMu1")
meanPiMuMu1,meanPiMuMu1_cons = createBifurConst(TheTable.meanPiMuMu1,TheTable.meanPiMuMu1ErrMinus,TheTable.meanPiMuMu1ErrPlus,  "meanPiMuMu1")

sigmaPiMuMu2,sigmaPiMuMu2_cons = createBifurConst(TheTable.sigmaPiMuMu2,TheTable.sigmaPiMuMu2ErrMinus,TheTable.sigmaPiMuMu2ErrPlus, "sigmaPiMuMu2")
meanPiMuMu2,meanPiMuMu2_cons = createBifurConst(TheTable.meanPiMuMu2,TheTable.meanPiMuMu2ErrMinus,TheTable.meanPiMuMu2ErrPlus,  "meanPiMuMu2")

sigmaPiMuMu3,sigmaPiMuMu3_cons = createBifurConst(TheTable.sigmaPiMuMu3,TheTable.sigmaPiMuMu3ErrMinus,TheTable.sigmaPiMuMu3ErrPlus, "sigmaPiMuMu3")
meanPiMuMu3,meanPiMuMu3_cons = createBifurConst(TheTable.meanPiMuMu3,TheTable.meanPiMuMu3ErrMinus,TheTable.meanPiMuMu3ErrPlus,  "meanPiMuMu3")

sigmaPiMuMu4,sigmaPiMuMu4_cons = createBifurConst(TheTable.sigmaPiMuMu4,TheTable.sigmaPiMuMu4ErrMinus,TheTable.sigmaPiMuMu4ErrPlus, "sigmaPiMuMu4")
meanPiMuMu4,meanPiMuMu4_cons = createBifurConst(TheTable.meanPiMuMu4,TheTable.meanPiMuMu4ErrMinus,TheTable.meanPiMuMu4ErrPlus,  "meanPiMuMu4")

sigmaPiMuMu5,sigmaPiMuMu5_cons = createBifurConst(TheTable.sigmaPiMuMu5,TheTable.sigmaPiMuMu5ErrMinus,TheTable.sigmaPiMuMu5ErrPlus, "sigmaPiMuMu5")
meanPiMuMu5,meanPiMuMu5_cons = createBifurConst(TheTable.meanPiMuMu5,TheTable.meanPiMuMu5ErrMinus,TheTable.meanPiMuMu5ErrPlus,  "meanPiMuMu5")

sigmaPiMuMu6,sigmaPiMuMu6_cons = createBifurConst(TheTable.sigmaPiMuMu6,TheTable.sigmaPiMuMu6ErrMinus,TheTable.sigmaPiMuMu6ErrPlus, "sigmaPiMuMu6")
meanPiMuMu6,meanPiMuMu6_cons = createBifurConst(TheTable.meanPiMuMu6,TheTable.meanPiMuMu6ErrMinus,TheTable.meanPiMuMu6ErrPlus,  "meanPiMuMu6")

sigmaPiMuMu7,sigmaPiMuMu7_cons = createBifurConst(TheTable.sigmaPiMuMu7,TheTable.sigmaPiMuMu7ErrMinus,TheTable.sigmaPiMuMu7ErrPlus, "sigmaPiMuMu7")
meanPiMuMu7,meanPiMuMu7_cons = createBifurConst(TheTable.meanPiMuMu7,TheTable.meanPiMuMu7ErrMinus,TheTable.meanPiMuMu7ErrPlus,  "meanPiMuMu7")

sigmaPiMuMu8,sigmaPiMuMu8_cons = createBifurConst(TheTable.sigmaPiMuMu8,TheTable.sigmaPiMuMu8ErrMinus,TheTable.sigmaPiMuMu8ErrPlus, "sigmaPiMuMu8")
meanPiMuMu8,meanPiMuMu8_cons = createBifurConst(TheTable.meanPiMuMu8,TheTable.meanPiMuMu8ErrMinus,TheTable.meanPiMuMu8ErrPlus,  "meanPiMuMu8")


PiMuMu, PiMuMu_cons = createConst(TheTable.PiMuMuYield, TheTable.PiMuMuYieldErr, "PiMuMu",1)
PiMuMu2, PiMuMu2_cons = createConst(TheTable.PiMuMu2, TheTable.PiMuMu2Err, "PiMuMu2",1)
PiMuMu3, PiMuMu3_cons = createConst(TheTable.PiMuMu3, TheTable.PiMuMu3Err, "PiMuMu3",1)
PiMuMu4, PiMuMu4_cons = createConst(TheTable.PiMuMu4, TheTable.PiMuMu4Err, "PiMuMu4",1)
PiMuMu5, PiMuMu5_cons = createConst(TheTable.PiMuMu5, TheTable.PiMuMu5Err, "PiMuMu5",1)
PiMuMu6, PiMuMu6_cons = createConst(TheTable.PiMuMu6, TheTable.PiMuMu6Err, "PiMuMu6",1)
PiMuMu7, PiMuMu7_cons = createConst(TheTable.PiMuMu7, TheTable.PiMuMu7Err, "PiMuMu7",1)
PiMuMu8, PiMuMu8_cons = createConst(TheTable.PiMuMu8, TheTable.PiMuMu8Err, "PiMuMu8",1)



PiMuMu1 = RooFormulaVar("PiMuMu1","1-PiMuMu8-PiMuMu7 - PiMuMu6 - PiMuMu5-PiMuMu4 -PiMuMu3-PiMuMu2",RooArgList(PiMuMu2,PiMuMu3,PiMuMu4,PiMuMu5,PiMuMu6,PiMuMu7, PiMuMu8))


####################################################

class BsMuMuModel:

    def __init__(self, glbin):
        self.i = str(glbin)
        i = self.i
       
        self.nbs = RooFormulaVar("NBs" + i ,"NBs" + i, "NBs*1/j"+i+"*f"+i, RooArgList(v["f"+i],v["nbs"],v["j"+i]))
        self.nbd = RooFormulaVar("NBd" + i ,"NBd" + i, "NBd*1/j"+i+"*f"+i, RooArgList(v["f"+i],v["nbd"],v["j"+i]))
        if COSME and i!= "1":self.nbkg = RooFormulaVar("MuMuBkg"+i,"MuMuBkg"+i, "MuMuBkg1*"+str(BDT_PDF[i]),RooArgList(mm[1].nbkg))
        else: self.nbkg = RooRealVar("MuMuBkg"+i,"MuMuBkg"+i, 0,70000)
        self.nmis = RooFormulaVar("Nmis" + i ,"Nmis" + i, "Nmis*f"+i+ "*1./missid_corr"+i, RooArgList(v["f"+i],v["nmis"],v["j"+i],v["missid_corr"+i]))
        
        if UNIFORM_KAPPA and i!= "1": self.k = mm[1].k
        elif FORCE_INDEX and i=="8": self.k = mm[7].k
        else: self.k = RooRealVar("MuMu_k_"+i,"MuMu_k_" + i, -7e-04, -1e-02,1e-02)
        
        self.dk = RooRealVar("MuMu_dk_"+i,"MuMu_dk_" + i,-7e-04, -1e-02,0)#1e-02)
        self.kb = RooFormulaVar("MuMu_kb_"+i,"MuMu_kb_" + i,"MuMu_k_"+i + " + MuMu_dk_" + i, RooArgList(self.k,self.dk))
        self.bkg1 = RooExponential("bkg1 MuMu model" + i , "bkg1 MuMu model" + i, Mass,self.k)
        self.bkg2 = RooExponential("bkg2 MuMu model" + i , "bkg2 MuMu model" + i, Mass,self.kb)
        
        self.fb = RooRealVar("MuMu_f_"+i,"MuMu_f_" + i,0.5,0.,1.)
        if DOUBLE_EXPO: self.bkg = RooAddPdf("bkg MuMu model" + i, "bkg MuMu model" + i, self.bkg1,self.bkg2, self.fb)
        else: self.bkg = self.bkg1
        self.Bs = RooCBShape("model Bs" + i, "model Bs"+ i, Mass, meanBs,sigmaBs,a,n)
        self.Bd = RooCBShape("model Bd" + i, "model Bd"+ i, Mass, meanBd,sigmaBs,a,n)
        self.PiMuNu = RooGaussian("B0pimunu " + i, "B0pimunu "+ i, Mass, v["meanPiMuNu"+i],v["sigmaPiMuNu"+i])
        self.PiMuMu = RooGaussian("BKmunu " + i, "BKmunu "+ i, Mass, v["meanPiMuMu"+i],v["sigmaPiMuMu"+i])#,a,n)
        #self.nPiMuNu = RooRealVar("B0 pimunu yield " + i,"B0 pimunu yield " + i, PiMuNuYields[int(i)-1])

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
        self.nPiMuNu = RooFormulaVar("B0 pimunu yield " + i,"PiMuNu"+i + "*PiMuNu",RooArgList(v["PiMuNu"+i],v["PiMuNu"]))
        self.nPiMuMu = RooFormulaVar("Bs Kmunu yield " + i,"PiMuMu"+i + "*PiMuMu",RooArgList(v["PiMuMu"+i],v["PiMuMu"]))
        if SERENA:
            self.model = RooAddPdf("mumu model " + i, "mumu model " + i, RooArgList(self.bkg,self.Bs,self.Bd,self.missid_peak,self.PiMuNu,self.PiMuMu), RooArgList(self.nbkg,self.nbs,self.nbd,self.nmis,self.nPiMuNu,self.nPiMuMu))
        else: self.model = RooAddPdf("mumu model " + i, "mumu model " + i, RooArgList(self.bkg,self.Bs,self.Bd,self.missid_peak), RooArgList(self.nbkg,self.nbs,self.nbd,self.nmis))

        
mm = {}
fiter = RooSimultaneous("fitter", "fitter", cat)

for i in range(1+USE_7_BINS,9):
    mm[i] = BsMuMuModel(i)
    fiter.addPdf(mm[i].model,"mumu bin" + str(i))

######  Prepare files

mainF =  TFile("/afs/cern.ch/user/d/diegoms/vol5/ntuple_1fb_unblinded.root")
#TFile("/afs/cern.ch/user/d/diegoms/public/top_secret/unblind_bsmumu_1fb_2.root")
mainF2 = TFile("/afs/cern.ch/user/d/diegoms/vol5/B2hhcalib.root")
thh = mainF2.Get("B2hh")
tmm0 = mainF.Get("B2MuMuTuple/DecayTree")
#tmm0 = mainF.Get("B2HHTuple/DecayTree")
BDT = BDT_cuts(bdtname, Binning)
#fiducial = "(1>0)"
#fiducial = 'B_s0_BDTS>0.05   && B_s0_PT>500 && B_s0_TAU*1000.<13.248 && muminus_P<500e03 && muplus_P<500e03 && muminus_PT<40e03 && muplus_PT<40e03  && muminus_PIDK<10 && muplus_PIDK<10 && muminus_PIDmu>-5 && muplus_PIDmu>-5 &&B_s0_PT>500 && B_s0_TAU*1000.<13.248 && muminus_P<500e03 && muplus_P<500e03 && muminus_PT<40e03 && muplus_PT<40e03&&muminus_PIDK<10 && muplus_PIDK<10 && muminus_PIDmu>-5 && muplus_PIDmu>-5&&B_s0_BDTS>0.05 '
print "fiducial cuts:", fiducial

############################################ Bs --> mm
fmm, tmm, datamm = {},{},{}
for i in range(1+USE_7_BINS,9):
    ix = str(i)
    fmm[i] = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_mm"+ix+".root","recreate")
    tmm[i] = tmm0.CopyTree(fiducial + BDT[i])
    tmm[i].Write()
    fmm[i].Close()
    fmm[i] = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_mm"+ix+".root")
    tmm[i] = fmm[i].Get("DecayTree")
    datamm[i] = RooDataSet("datamm"+ix,"datamm"+ix,tmm[i],RooArgSet(Mass))

if not USE_7_BINS: mumuDataLG = RooDataSet("mumu data Low GL", "mumu data Low GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu bin1", datamm[1]), RooFit.Import("mumu bin2", datamm[2]), RooFit.Import("mumu bin3", datamm[3]),RooFit.Import("mumu bin4", datamm[4]))

else: mumuDataLG = RooDataSet("mumu data Low GL", "mumu data Low GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu bin2", datamm[2]), RooFit.Import("mumu bin3", datamm[3]),RooFit.Import("mumu bin4", datamm[4]))
mumuDataHG = RooDataSet("mumu data High GL", "mumu data High GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu bin5", datamm[5]), RooFit.Import("mumu bin6", datamm[6]), RooFit.Import("mumu bin7", datamm[7]),RooFit.Import("mumu bin8", datamm[8]))

allData = mumuDataLG.Clone() #RooDataSet("all data","all data", RooArgSet(Mass,cat), RooFit.Import(hhData), RooFit.Import(mumuData))
allData.append(mumuDataHG)

summaryConstraints = RooArgSet(NhhTOT_cons,Nhh2_cons,Nhh3_cons,Nhh4_cons,Nhh5_cons,Nhh6_cons,Nhh7_cons,Nhh8_cons )
summaryConstraints.add(RooArgSet(sigmaBs_cons ,sigmaBd_cons,meanBd_cons,meanBs_cons, a_cons, fdfs_cons,misid_global_cons))
summaryConstraints.add(RooArgSet(NormBu_cons,NormKPi_cons, NormPhi_cons))
summaryConstraints.add(RooArgSet(PiMuNu2_cons,PiMuNu3_cons,PiMuNu4_cons,PiMuNu5_cons,PiMuNu6_cons,PiMuNu7_cons, PiMuNu8_cons, PiMuNu_cons))
summaryConstraints.add(RooArgSet(sigmaPiMuNu1_cons,sigmaPiMuNu2_cons,sigmaPiMuNu3_cons,sigmaPiMuNu4_cons,sigmaPiMuNu5_cons,sigmaPiMuNu6_cons,sigmaPiMuNu7_cons, sigmaPiMuNu8_cons))
summaryConstraints.add(RooArgSet(meanPiMuNu1_cons,meanPiMuNu2_cons,meanPiMuNu3_cons,meanPiMuNu4_cons,meanPiMuNu5_cons,meanPiMuNu6_cons,meanPiMuNu7_cons, meanPiMuNu8_cons))
summaryConstraints.add(RooArgSet(PiMuMu2_cons,PiMuMu3_cons,PiMuMu4_cons,PiMuMu5_cons,PiMuMu6_cons,PiMuMu7_cons, PiMuMu8_cons, PiMuMu_cons))
summaryConstraints.add(RooArgSet(sigmaPiMuMu1_cons,sigmaPiMuMu2_cons,sigmaPiMuMu3_cons,sigmaPiMuMu4_cons,sigmaPiMuMu5_cons,sigmaPiMuMu6_cons,sigmaPiMuMu7_cons, sigmaPiMuMu8_cons))
summaryConstraints.add(RooArgSet(meanPiMuMu1_cons,meanPiMuMu2_cons,meanPiMuMu3_cons,meanPiMuMu4_cons,meanPiMuMu5_cons,meanPiMuMu6_cons,meanPiMuMu7_cons, meanPiMuMu8_cons))

if COSME:
    
    NhhTOT.setConstant(kTRUE), Nhh2.setConstant(kTRUE), Nhh3.setConstant(kTRUE), Nhh4.setConstant(kTRUE), Nhh5.setConstant(kTRUE), Nhh6.setConstant(kTRUE), Nhh7.setConstant(kTRUE), Nhh8.setConstant(kTRUE)
    sigmaBs.setConstant(kTRUE), meanBs.setConstant(kTRUE),sigmaBd.setConstant(kTRUE), meanBd.setConstant(kTRUE)



def fitThis():
    fiter.fitTo(allData,RooFit.Minos(kTRUE), RooFit.ExternalConstraints(RooArgSet(summaryConstraints)),RooFit.Strategy(2))

    c = TCanvas()
    c.Divide(4,2)
    fr = {}
    binning = 10
    size = (Mass.getMax()-Mass.getMin())*1./binning
    for i in range(1+USE_7_BINS,9):
        c.cd(i)
        fr[i] = Mass.frame()
        datamm[i].plotOn(fr[i], RooFit.Binning(binning))
        mm[i].model.plotOn(fr[i])#
        mm[i].model.plotOn(fr[i])#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        mm[i].model.plotOn(fr[i], RooFit.Components("model Bs"+str(i)),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        mm[i].model.plotOn(fr[i], RooFit.Components("model Bd"+str(i)),RooFit.LineColor(kGreen),RooFit.LineStyle(7))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        mm[i].model.plotOn(fr[i], RooFit.Components("missid"+str(i)),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        if SERENA:
            mm[i].model.plotOn(fr[i], RooFit.Components("B0pimunu "+str(i)),RooFit.LineColor(kBlack),RooFit.LineStyle(kDotted))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
            mm[i].model.plotOn(fr[i], RooFit.Components("BKmunu "+str(i)),RooFit.LineColor(kCyan),RooFit.LineStyle(kDotted))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        fr[i].GetXaxis().SetTitle("m_{#mu#mu} ( MeV/c^{2} )")
        fr[i].SetTitle("B_{s}^{0}#rightarrow#mu^{+}#mu^{-} candidates, BIN [" + str(Binning[bdtname][i-1]) + ", " +str(Binning[bdtname][i])+"]" )
            
        fr[i].GetYaxis().SetTitle("Events /( "+str(int(size))+" MeV/c^{2} )")
        fr[i].GetYaxis().SetTitleOffset(1.4)
    
        fr[i].Draw()
    return c, fr

    
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
