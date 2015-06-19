from ROOT import *
import fit_2011_data as a2011
Table_old = a2011.TheTable
from Bs2MuMuParams import toytable_test_Autumn2012 as TheTable
from NTuple_names import *
from constrain_funcs import *
gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
if "NormBu_fullmass" not in dir(TheTable):
    print "INVENTING VALUE FOR THE NORMALIZATION FACTOR 2012"
    TheTable.NormBu_fullmass = TheTable.NormBu
    TheTable.NormKPi_fullmass = TheTable.NormKPi
    TheTable.NormBu_fullmassErr = TheTable.NormBuErr
    TheTable.NormKPi_fullmassErr = TheTable.NormKPiErr
    
#BREEAK
#massname = "B_mass"
#samplename = "sample"
#bdtname = "BDTflat_BDT9_BDTScut05"
Binning = {}
Binning[bdtname] = [0, .25,.4,.5,.6,.7,.8,1.]

fiducial_autum = "(1>0)"#"muplus_TRACK_GhostProb<0.4373 && muminus_TRACK_GhostProb<0.4373 && aBDT05flat!=0. && B_s0_BDTS>0.05 && B_s0_PT>500 && B_s0_TAU*1000<13.248 && muplus_P<0.5e06 && muminus_P<0.5e06  && muplus_PT<4e04 && muminus_PT<4e04 && muminus_PIDK<10 && muplus_PIDK<10 && muminus_PIDmu>-5 && muplus_PIDmu>-5"


COSME = 0  ### fix many np to compare with Cosme's stat error
SERENA = 1 ### Add gaussian B->pimunu based on Serena's numbers/model
UNIFORM_KAPPA = 0
DOUBLE_EXPO = 0
FORCE_INDEX = 1
N_BINS = 7


if DOUBLE_EXPO: Mass = RooRealVar(massname,massname,4170, 6565)
#else: Mass = RooRealVar(massname,massname,5432.96 - 120,6000)#4900, 6000)
else: Mass = RooRealVar(massname,massname,4900, 6000)
cat =  a2011.cat
for i in range(1,N_BINS +1 ): cat.defineType("mumu autum bin" + str(i))
justine = {"T":1., 0:TheTable.Justine1, 1: TheTable.Justine2, 2:TheTable.Justine3 , 3: TheTable.Justine4, 4: TheTable.Justine5, 5:TheTable.Justine6 , 6: TheTable.Justine7}
#justine = {"T":1., 0:1, 1: 1, 2:1 , 3: 1, 4:1, 5:1 , 6: 1}

mid_idf = [TheTable.MisIDfBDTBin1,TheTable.MisIDfBDTBin2,TheTable.MisIDfBDTBin3,TheTable.MisIDfBDTBin4,TheTable.MisIDfBDTBin5,TheTable.MisIDfBDTBin6,TheTable.MisIDfBDTBin7]

j1 = RooRealVar("j1_autum","j1_autum",justine[0])
j2 = RooRealVar("j2_autum","j2_autum",justine[1])
j3 = RooRealVar("j3_autum","j3_autum",justine[2])
j4 = RooRealVar("j4_autum","j4_autum",justine[3])

j5 = RooRealVar("j5_autum","j5_autum",justine[4])
j6 = RooRealVar("j6_autum","j6_autum",justine[5])
j7 = RooRealVar("j7_autum","j7_autum",justine[6])


missid_corr1 = RooRealVar("missid_corr1_autum","missid_corr1_autum",mid_idf[0])
missid_corr2 = RooRealVar("missid_corr2_autum","missid_corr2_autum",mid_idf[1])
missid_corr3 = RooRealVar("missid_corr3_autum","missid_corr3_autum",mid_idf[2])
missid_corr4 = RooRealVar("missid_corr4_autum","missid_corr4_autum",mid_idf[3])

missid_corr5 = RooRealVar("missid_corr5_autum","missid_corr5_autum",mid_idf[4])
missid_corr6 = RooRealVar("missid_corr6_autum","missid_corr6_autum",mid_idf[5])
missid_corr7 = RooRealVar("missid_corr7_autum","missid_corr7_autum",mid_idf[6])


#1,0.6)
NormBu, NormBu_cons = createConst(TheTable.NormBu_fullmass, TheTable.NormBu_fullmassErr, "NormBu_autum", 1) 
NormKPi, NormKPi_cons = createConst(TheTable.NormKPi_fullmass, TheTable.NormKPi_fullmassErr, "NormKPi_autum", 1)

alpha_s = RooFormulaVar("alpha_S_autum","alpha_S_autum" , "((NormBu_autum/pow(3.8859342678999996e-12 ,2)+NormKPi_autum/4.5045014793224593e-23)/(pow(3.8859342678999996e-12 ,-2.)+(1./4.5045014793224593e-23 )))*fdfs*1e09", RooArgList(NormBu,NormKPi,a2011.fdfs))
#alpha_s =  RooRealVar("alpha_S_autum","alpha_S_autum" ,1)
nbs = RooFormulaVar("NBs_autum","NBs_autum", "BRs/alpha_S_autum", RooArgList(alpha_s,a2011.BR_s))
misid_global_factor, misid_global_cons =createConst(TheTable.MisIDGlobalFactor,TheTable.MisIDGlobalFactorErr, "misidP_autum") 

nbd = RooRealVar("NBd_autum","NBd_autum",5.,0.,20)
a = linkToConst(TheTable.CBTrans,TheTable.CBTransErr, a2011.a, a2011.TheTable.CBTrans,a2011.TheTable.CBTransErr, "_autum")



meanBs, meanBs_cons = createConst(TheTable.MassMeanBs, TheTable.MassMeanErrBs, "meanBs_autum", 1) 
meanBd, meanBd_cons = createConst(TheTable.MassMeanBd, TheTable.MassMeanErrBd, "meanBd_autum", 1) 

sigmaBs, sigmaBs_cons = createConst(TheTable.MassResoBs, TheTable.MassResoErrBs, "sigmaBs_autum", 1) 
sigmaBd, sigmaBd_cons = createConst(TheTable.MassResoBd, TheTable.MassResoErrBd, "sigmaBd_autum", 1) 

Nhh1, Nhh1_cons = createConst(TheTable.BDT_sig1,TheTable.BDT_sigErr1,"Nhh1_autum",1)
Nhh2, Nhh2_cons = createConst(TheTable.BDT_sig2,TheTable.BDT_sigErr2,"Nhh2_autum",1)
Nhh3, Nhh3_cons = createConst(TheTable.BDT_sig3,TheTable.BDT_sigErr3,"Nhh3_autum",1)
Nhh4, Nhh4_cons = createConst(TheTable.BDT_sig4,TheTable.BDT_sigErr4,"Nhh4_autum",1)
Nhh5, Nhh5_cons = createConst(TheTable.BDT_sig5,TheTable.BDT_sigErr5,"Nhh5_autum",1)
Nhh6, Nhh6_cons = createConst(TheTable.BDT_sig6,TheTable.BDT_sigErr6,"Nhh6_autum",1)
Nhh7, Nhh7_cons = createConst(TheTable.BDT_sig7,TheTable.BDT_sigErr7,"Nhh7_autum",1)
NhhTOT, NhhTOT_cons = createConst(TheTable.TisTot,TheTable.TisErrTot,"NhhTOT_autum",1)

#NhhTOT = RooFormulaVar("NhhTOT_autum","NhhTOT_autum", "Nhh1_autum + Nhh2_autum + Nhh3_autum + Nhh4_autum + Nhh5_autum + Nhh6_autum + Nhh7_autum",RooArgList(Nhh1,Nhh2,Nhh3,Nhh4,Nhh5,Nhh6,Nhh7))

nmis = RooFormulaVar("Nmis_autum","Nmis_autum", "NhhTOT_autum*misidP_autum",RooArgList(NhhTOT,misid_global_factor))#,40)
f2 = RooFormulaVar("f2_autum","f2_autum", "Nhh2_autum",RooArgList(Nhh2))
f3 = RooFormulaVar("f3_autum","f3_autum", "Nhh3_autum",RooArgList(Nhh3))
f4 = RooFormulaVar("f4_autum","f4_autum", "Nhh4_autum",RooArgList(Nhh4))
f5 = RooFormulaVar("f5_autum","f5_autum", "Nhh5_autum",RooArgList(Nhh5))
f6 = RooFormulaVar("f6_autum","f6_autum", "Nhh6_autum",RooArgList(Nhh6))
f7 = RooFormulaVar("f7_autum","f7_autum", "Nhh7_autum",RooArgList(Nhh7))

f1 = RooFormulaVar("f1_autum", "f1_autum", "(1-f2_autum-f3_autum-f4_autum-f5_autum-f6_autum-f7_autum)", RooArgList(f2,f3,f4,f5,f6,f7))

v = vars()

############ MISID
missid_mean1 = RooRealVar("missid_mean1_autum","missid_mean1_autum",5.09168e+03+100+TheTable.MassMeanBs - Table_old.MassMeanBs)#5050, 5600)#5168.)
missid_mean2 = RooFormulaVar("missid_mean2_autum","missid_mean2_autum", "missid_mean1_autum + missid_d1" ,RooArgList(missid_mean1,a2011.missid_d1) )
missid_mean3 = RooFormulaVar("missid_mean3_autum","missid_mean3_autum", "missid_mean2_autum + missid_d2" ,RooArgList(missid_mean2,a2011.missid_d2) )

### B0-> Pi Mu Nu bkg

sigmaPiMuNu1 = linkToConst(TheTable.sigmaPiMuNu1,0.5*(abs(TheTable.sigmaPiMuNu1ErrMinus) + abs(TheTable.sigmaPiMuNu1ErrPlus)), a2011.sigmaPiMuNu1,a2011.TheTable.sigmaPiMuNu1,0.5*(abs(a2011.TheTable.sigmaPiMuNu1ErrMinus) + abs(a2011.TheTable.sigmaPiMuNu1ErrPlus)) , "_autum")
meanPiMuNu1 = linkToConst(TheTable.meanPiMuNu1,0.5*(abs(TheTable.meanPiMuNu1ErrMinus) + abs(TheTable.meanPiMuNu1ErrPlus)), a2011.meanPiMuNu1, a2011.TheTable.meanPiMuNu1,0.5*(abs(a2011.TheTable.meanPiMuNu1ErrMinus) + abs(a2011.TheTable.meanPiMuNu1ErrPlus)), "_autum")
sigmaPiMuNu2 = linkToConst(TheTable.sigmaPiMuNu2,0.5*(abs(TheTable.sigmaPiMuNu2ErrMinus) + abs(TheTable.sigmaPiMuNu2ErrPlus)), a2011.sigmaPiMuNu2,a2011.TheTable.sigmaPiMuNu2,0.5*(abs(a2011.TheTable.sigmaPiMuNu2ErrMinus) + abs(a2011.TheTable.sigmaPiMuNu2ErrPlus)) , "_autum")
meanPiMuNu2 = linkToConst(TheTable.meanPiMuNu2,0.5*(abs(TheTable.meanPiMuNu2ErrMinus) + abs(TheTable.meanPiMuNu2ErrPlus)), a2011.meanPiMuNu2, a2011.TheTable.meanPiMuNu2,0.5*(abs(a2011.TheTable.meanPiMuNu2ErrMinus) + abs(a2011.TheTable.meanPiMuNu2ErrPlus)), "_autum")
sigmaPiMuNu3 = linkToConst(TheTable.sigmaPiMuNu3,0.5*(abs(TheTable.sigmaPiMuNu3ErrMinus) + abs(TheTable.sigmaPiMuNu3ErrPlus)), a2011.sigmaPiMuNu3,a2011.TheTable.sigmaPiMuNu3,0.5*(abs(a2011.TheTable.sigmaPiMuNu3ErrMinus) + abs(a2011.TheTable.sigmaPiMuNu3ErrPlus)) , "_autum")
meanPiMuNu3 = linkToConst(TheTable.meanPiMuNu3,0.5*(abs(TheTable.meanPiMuNu3ErrMinus) + abs(TheTable.meanPiMuNu3ErrPlus)), a2011.meanPiMuNu3, a2011.TheTable.meanPiMuNu3,0.5*(abs(a2011.TheTable.meanPiMuNu3ErrMinus) + abs(a2011.TheTable.meanPiMuNu3ErrPlus)), "_autum")
sigmaPiMuNu4 = linkToConst(TheTable.sigmaPiMuNu4,0.5*(abs(TheTable.sigmaPiMuNu4ErrMinus) + abs(TheTable.sigmaPiMuNu4ErrPlus)), a2011.sigmaPiMuNu4,a2011.TheTable.sigmaPiMuNu4,0.5*(abs(a2011.TheTable.sigmaPiMuNu4ErrMinus) + abs(a2011.TheTable.sigmaPiMuNu4ErrPlus)) , "_autum")
meanPiMuNu4 = linkToConst(TheTable.meanPiMuNu4,0.5*(abs(TheTable.meanPiMuNu4ErrMinus) + abs(TheTable.meanPiMuNu4ErrPlus)), a2011.meanPiMuNu4, a2011.TheTable.meanPiMuNu4,0.5*(abs(a2011.TheTable.meanPiMuNu4ErrMinus) + abs(a2011.TheTable.meanPiMuNu4ErrPlus)), "_autum")
sigmaPiMuNu5 = linkToConst(TheTable.sigmaPiMuNu5,0.5*(abs(TheTable.sigmaPiMuNu5ErrMinus) + abs(TheTable.sigmaPiMuNu5ErrPlus)), a2011.sigmaPiMuNu5,a2011.TheTable.sigmaPiMuNu5,0.5*(abs(a2011.TheTable.sigmaPiMuNu5ErrMinus) + abs(a2011.TheTable.sigmaPiMuNu5ErrPlus)) , "_autum")
meanPiMuNu5 = linkToConst(TheTable.meanPiMuNu5,0.5*(abs(TheTable.meanPiMuNu5ErrMinus) + abs(TheTable.meanPiMuNu5ErrPlus)), a2011.meanPiMuNu5, a2011.TheTable.meanPiMuNu5,0.5*(abs(a2011.TheTable.meanPiMuNu5ErrMinus) + abs(a2011.TheTable.meanPiMuNu5ErrPlus)), "_autum")
sigmaPiMuNu6 = linkToConst(TheTable.sigmaPiMuNu6,0.5*(abs(TheTable.sigmaPiMuNu6ErrMinus) + abs(TheTable.sigmaPiMuNu6ErrPlus)), a2011.sigmaPiMuNu6,a2011.TheTable.sigmaPiMuNu6,0.5*(abs(a2011.TheTable.sigmaPiMuNu6ErrMinus) + abs(a2011.TheTable.sigmaPiMuNu6ErrPlus)) , "_autum")
meanPiMuNu6 = linkToConst(TheTable.meanPiMuNu6,0.5*(abs(TheTable.meanPiMuNu6ErrMinus) + abs(TheTable.meanPiMuNu6ErrPlus)), a2011.meanPiMuNu6, a2011.TheTable.meanPiMuNu6,0.5*(abs(a2011.TheTable.meanPiMuNu6ErrMinus) + abs(a2011.TheTable.meanPiMuNu6ErrPlus)), "_autum")
sigmaPiMuNu7 = linkToConst(TheTable.sigmaPiMuNu7,0.5*(abs(TheTable.sigmaPiMuNu7ErrMinus) + abs(TheTable.sigmaPiMuNu7ErrPlus)), a2011.sigmaPiMuNu7,a2011.TheTable.sigmaPiMuNu7,0.5*(abs(a2011.TheTable.sigmaPiMuNu7ErrMinus) + abs(a2011.TheTable.sigmaPiMuNu7ErrPlus)) , "_autum")
meanPiMuNu7 = linkToConst(TheTable.meanPiMuNu7,0.5*(abs(TheTable.meanPiMuNu7ErrMinus) + abs(TheTable.meanPiMuNu7ErrPlus)), a2011.meanPiMuNu7, a2011.TheTable.meanPiMuNu7,0.5*(abs(a2011.TheTable.meanPiMuNu7ErrMinus) + abs(a2011.TheTable.meanPiMuNu7ErrPlus)), "_autum")




PiMuNu, PiMuNu_cons = createConst(TheTable.PiMuNuYield, TheTable.PiMuNuYieldErr, "PiMuNu_autum",1)
PiMuNu2 = linkToConst(TheTable.PiMuNu2, TheTable.PiMuNu2Err, a2011.PiMuNu2, a2011.TheTable.PiMuNu2, a2011.TheTable.PiMuNu2Err, "_autum")
PiMuNu3 = linkToConst(TheTable.PiMuNu3, TheTable.PiMuNu3Err, a2011.PiMuNu3, a2011.TheTable.PiMuNu3, a2011.TheTable.PiMuNu3Err, "_autum")
PiMuNu4 = linkToConst(TheTable.PiMuNu4, TheTable.PiMuNu4Err, a2011.PiMuNu4, a2011.TheTable.PiMuNu4, a2011.TheTable.PiMuNu4Err, "_autum")
PiMuNu5 = linkToConst(TheTable.PiMuNu5, TheTable.PiMuNu5Err, a2011.PiMuNu5, a2011.TheTable.PiMuNu5, a2011.TheTable.PiMuNu5Err, "_autum")
PiMuNu6 = linkToConst(TheTable.PiMuNu6, TheTable.PiMuNu6Err, a2011.PiMuNu6, a2011.TheTable.PiMuNu6, a2011.TheTable.PiMuNu6Err, "_autum")
PiMuNu7 = linkToConst(TheTable.PiMuNu7, TheTable.PiMuNu7Err, a2011.PiMuNu7, a2011.TheTable.PiMuNu7, a2011.TheTable.PiMuNu7Err, "_autum")


PiMuNu1 = RooFormulaVar("PiMuNu1_autum","1-PiMuNu7_autum - PiMuNu6_autum - PiMuNu5_autum-PiMuNu4_autum -PiMuNu3_autum-PiMuNu2_autum",RooArgList(PiMuNu2,PiMuNu3,PiMuNu4,PiMuNu5,PiMuNu6,PiMuNu7))

### Bs --> Kmu nu

sigmaPiMuMu1 = linkToConst(TheTable.sigmaPiMuMu1,0.5*(abs(TheTable.sigmaPiMuMu1ErrMinus) + abs(TheTable.sigmaPiMuMu1ErrPlus)), a2011.sigmaPiMuMu1,a2011.TheTable.sigmaPiMuMu1,0.5*(abs(a2011.TheTable.sigmaPiMuMu1ErrMinus) + abs(a2011.TheTable.sigmaPiMuMu1ErrPlus)) , "_autum")
meanPiMuMu1 = linkToConst(TheTable.meanPiMuMu1,0.5*(abs(TheTable.meanPiMuMu1ErrMinus) + abs(TheTable.meanPiMuMu1ErrPlus)), a2011.meanPiMuMu1, a2011.TheTable.meanPiMuMu1,0.5*(abs(a2011.TheTable.meanPiMuMu1ErrMinus) + abs(a2011.TheTable.meanPiMuMu1ErrPlus)), "_autum")
sigmaPiMuMu2 = linkToConst(TheTable.sigmaPiMuMu2,0.5*(abs(TheTable.sigmaPiMuMu2ErrMinus) + abs(TheTable.sigmaPiMuMu2ErrPlus)), a2011.sigmaPiMuMu2,a2011.TheTable.sigmaPiMuMu2,0.5*(abs(a2011.TheTable.sigmaPiMuMu2ErrMinus) + abs(a2011.TheTable.sigmaPiMuMu2ErrPlus)) , "_autum")
meanPiMuMu2 = linkToConst(TheTable.meanPiMuMu2,0.5*(abs(TheTable.meanPiMuMu2ErrMinus) + abs(TheTable.meanPiMuMu2ErrPlus)), a2011.meanPiMuMu2, a2011.TheTable.meanPiMuMu2,0.5*(abs(a2011.TheTable.meanPiMuMu2ErrMinus) + abs(a2011.TheTable.meanPiMuMu2ErrPlus)), "_autum")
sigmaPiMuMu3 = linkToConst(TheTable.sigmaPiMuMu3,0.5*(abs(TheTable.sigmaPiMuMu3ErrMinus) + abs(TheTable.sigmaPiMuMu3ErrPlus)), a2011.sigmaPiMuMu3,a2011.TheTable.sigmaPiMuMu3,0.5*(abs(a2011.TheTable.sigmaPiMuMu3ErrMinus) + abs(a2011.TheTable.sigmaPiMuMu3ErrPlus)) , "_autum")
meanPiMuMu3 = linkToConst(TheTable.meanPiMuMu3,0.5*(abs(TheTable.meanPiMuMu3ErrMinus) + abs(TheTable.meanPiMuMu3ErrPlus)), a2011.meanPiMuMu3, a2011.TheTable.meanPiMuMu3,0.5*(abs(a2011.TheTable.meanPiMuMu3ErrMinus) + abs(a2011.TheTable.meanPiMuMu3ErrPlus)), "_autum")
sigmaPiMuMu4 = linkToConst(TheTable.sigmaPiMuMu4,0.5*(abs(TheTable.sigmaPiMuMu4ErrMinus) + abs(TheTable.sigmaPiMuMu4ErrPlus)), a2011.sigmaPiMuMu4,a2011.TheTable.sigmaPiMuMu4,0.5*(abs(a2011.TheTable.sigmaPiMuMu4ErrMinus) + abs(a2011.TheTable.sigmaPiMuMu4ErrPlus)) , "_autum")
meanPiMuMu4 = linkToConst(TheTable.meanPiMuMu4,0.5*(abs(TheTable.meanPiMuMu4ErrMinus) + abs(TheTable.meanPiMuMu4ErrPlus)), a2011.meanPiMuMu4, a2011.TheTable.meanPiMuMu4,0.5*(abs(a2011.TheTable.meanPiMuMu4ErrMinus) + abs(a2011.TheTable.meanPiMuMu4ErrPlus)), "_autum")
sigmaPiMuMu5 = linkToConst(TheTable.sigmaPiMuMu5,0.5*(abs(TheTable.sigmaPiMuMu5ErrMinus) + abs(TheTable.sigmaPiMuMu5ErrPlus)), a2011.sigmaPiMuMu5,a2011.TheTable.sigmaPiMuMu5,0.5*(abs(a2011.TheTable.sigmaPiMuMu5ErrMinus) + abs(a2011.TheTable.sigmaPiMuMu5ErrPlus)) , "_autum")
meanPiMuMu5 = linkToConst(TheTable.meanPiMuMu5,0.5*(abs(TheTable.meanPiMuMu5ErrMinus) + abs(TheTable.meanPiMuMu5ErrPlus)), a2011.meanPiMuMu5, a2011.TheTable.meanPiMuMu5,0.5*(abs(a2011.TheTable.meanPiMuMu5ErrMinus) + abs(a2011.TheTable.meanPiMuMu5ErrPlus)), "_autum")
sigmaPiMuMu6 = linkToConst(TheTable.sigmaPiMuMu6,0.5*(abs(TheTable.sigmaPiMuMu6ErrMinus) + abs(TheTable.sigmaPiMuMu6ErrPlus)), a2011.sigmaPiMuMu6,a2011.TheTable.sigmaPiMuMu6,0.5*(abs(a2011.TheTable.sigmaPiMuMu6ErrMinus) + abs(a2011.TheTable.sigmaPiMuMu6ErrPlus)) , "_autum")
meanPiMuMu6 = linkToConst(TheTable.meanPiMuMu6,0.5*(abs(TheTable.meanPiMuMu6ErrMinus) + abs(TheTable.meanPiMuMu6ErrPlus)), a2011.meanPiMuMu6, a2011.TheTable.meanPiMuMu6,0.5*(abs(a2011.TheTable.meanPiMuMu6ErrMinus) + abs(a2011.TheTable.meanPiMuMu6ErrPlus)), "_autum")
sigmaPiMuMu7 = linkToConst(TheTable.sigmaPiMuMu7,0.5*(abs(TheTable.sigmaPiMuMu7ErrMinus) + abs(TheTable.sigmaPiMuMu7ErrPlus)), a2011.sigmaPiMuMu7,a2011.TheTable.sigmaPiMuMu7,0.5*(abs(a2011.TheTable.sigmaPiMuMu7ErrMinus) + abs(a2011.TheTable.sigmaPiMuMu7ErrPlus)) , "_autum")
meanPiMuMu7 = linkToConst(TheTable.meanPiMuMu7,0.5*(abs(TheTable.meanPiMuMu7ErrMinus) + abs(TheTable.meanPiMuMu7ErrPlus)), a2011.meanPiMuMu7, a2011.TheTable.meanPiMuMu7,0.5*(abs(a2011.TheTable.meanPiMuMu7ErrMinus) + abs(a2011.TheTable.meanPiMuMu7ErrPlus)), "_autum")




PiMuMu, PiMuMu_cons = createConst(TheTable.PiMuMuYield, TheTable.PiMuMuYieldErr, "PiMuMu_autum",1)
PiMuMu2 = linkToConst(TheTable.PiMuMu2, TheTable.PiMuMu2Err, a2011.PiMuMu2, a2011.TheTable.PiMuMu2, a2011.TheTable.PiMuMu2Err, "_autum")
PiMuMu3 = linkToConst(TheTable.PiMuMu3, TheTable.PiMuMu3Err, a2011.PiMuMu3, a2011.TheTable.PiMuMu3, a2011.TheTable.PiMuMu3Err, "_autum")
PiMuMu4 = linkToConst(TheTable.PiMuMu4, TheTable.PiMuMu4Err, a2011.PiMuMu4, a2011.TheTable.PiMuMu4, a2011.TheTable.PiMuMu4Err, "_autum")
PiMuMu5 = linkToConst(TheTable.PiMuMu5, TheTable.PiMuMu5Err, a2011.PiMuMu5, a2011.TheTable.PiMuMu5, a2011.TheTable.PiMuMu5Err, "_autum")
PiMuMu6 = linkToConst(TheTable.PiMuMu6, TheTable.PiMuMu6Err, a2011.PiMuMu6, a2011.TheTable.PiMuMu6, a2011.TheTable.PiMuMu6Err, "_autum")
PiMuMu7 = linkToConst(TheTable.PiMuMu7, TheTable.PiMuMu7Err, a2011.PiMuMu7, a2011.TheTable.PiMuMu7, a2011.TheTable.PiMuMu7Err, "_autum")


PiMuMu1 = RooFormulaVar("PiMuMu1_autum","1-PiMuMu7_autum - PiMuMu6_autum - PiMuMu5_autum-PiMuMu4_autum -PiMuMu3_autum-PiMuMu2_autum",RooArgList(PiMuMu2,PiMuMu3,PiMuMu4,PiMuMu5,PiMuMu6,PiMuMu7))


####################################################

class BsMuMuModel:

    def __init__(self, glbin):
        self.i = str(glbin)
        i = self.i
       
        self.nbs = RooFormulaVar("NBs_autum" + i ,"NBs_autum" + i, "NBs_autum*1/j"+i+"_autum*f"+i + "_autum", RooArgList(v["f"+i],v["nbs"],v["j"+i]))
        self.nbd = RooFormulaVar("NBd_autum" + i ,"NBd_autum" + i, "NBd_autum*1/j"+i+"_autum*f"+i + "_autum", RooArgList(v["f"+i],v["nbd"],v["j"+i]))
        #if COSME and i!= "1":self.nbkg = RooFormulaVar("MuMuBkg"+i,"MuMuBkg"+i, "MuMuBkg1*"+str(BDT_PDF[i]),RooArgList(mm[1].nbkg))
        self.nbkg = RooRealVar("MuMuBkg_autum"+i,"MuMuBkg_autum"+i, 0,70000)
        self.nmis = RooFormulaVar("Nmis_autum" + i ,"Nmis_autum" + i, "Nmis_autum*f"+i+ "_autum*1./missid_corr"+i+"_autum", RooArgList(v["f"+i],v["nmis"],v["j"+i],v["missid_corr"+i]))
        
        if UNIFORM_KAPPA and i!= "1": self.k = mm[1].k
        else: self.k = RooRealVar("MuMu_k_"+i+"_autum","MuMu_k_" + i+"_autum", -7e-04, -1e-02,1e-02)
        
        self.dk = RooRealVar("MuMu_dk_"+i+"_autum","MuMu_dk_" + i+"_autum",-7e-04, -1e-02,0)#1e-02)
        self.kb = RooFormulaVar("MuMu_kb_"+i+"_autum","MuMu_kb_" + i+"_autum","MuMu_k_"+i +"_autum" + " + MuMu_dk_" + i+"_autum", RooArgList(self.k,self.dk))
        self.bkg1 = RooExponential("bkg1 MuMu model_autum" + i , "bkg1 MuMu model_autum" + i, Mass,self.k)
        self.bkg2 = RooExponential("bkg2 MuMu model_autum" + i , "bkg2 MuMu model_autum" + i, Mass,self.kb)
        
        self.fb = RooRealVar("MuMu_f_"+i +"_autum","MuMu_f_" + i+"_autum",0.5,0.,1.)
        if DOUBLE_EXPO: self.bkg = RooAddPdf("bkg MuMu model_autum" + i, "bkg MuMu model_autum" + i, self.bkg1,self.bkg2, self.fb)
        else: self.bkg = self.bkg1
        self.Bs = RooCBShape("model Bs_autum" + i, "model Bs_autum"+ i, Mass, meanBs,sigmaBs,a,a2011.n)
        self.Bd = RooCBShape("model Bd_autum" + i, "model Bd_autum"+ i, Mass, meanBd,sigmaBs,a,a2011.n)
        self.PiMuNu = RooGaussian("B0pimunu_autum " + i, "B0pimunu_autum "+ i, Mass, v["meanPiMuNu"+i],v["sigmaPiMuNu"+i])
        self.PiMuMu = RooGaussian("BKmunu_autum " + i, "BKmunu_autum "+ i, Mass, v["meanPiMuMu"+i],v["sigmaPiMuMu"+i])#,a,n)
        #self.nPiMuNu = RooRealVar("B0 pimunu yield " + i,"B0 pimunu yield " + i, PiMuNuYields[int(i)-1])

        self.missid_MSu1 = RooCBShape("missid_MSu_autum" + "_"+ i,"missid_MSu_autum"+ "_"+ i, Mass, missid_mean1, a2011.missid_sigma, a2011.missid_a2, a2011.missid_n2)
        self.missid_MSd1 = RooCBShape("missid_MSd_autum"+ "_"+ i,"missid_MSd_autum"+ "_"+ i, Mass, missid_mean1, a2011.missid_sigma, a2011.missid_a3, a2011.missid_n)
        self.missid_MSu2 = RooCBShape("missid_MSu2_autum"+ "_"+ i,"missid_MSu2_autum"+ "_"+ i, Mass, missid_mean2, a2011.missid_sigma2, a2011.missid_a2b, a2011.missid_n2b)
        self.missid_MSd2 = RooCBShape("missid_MSd2_autum"+ "_"+ i,"missid_MSd2_autum"+ "_"+ i, Mass, missid_mean2, a2011.missid_sigma2, a2011.missid_a3b, a2011.missid_nb)

        self.missid_MSu3 = RooCBShape("missid_MSu3_autum"+ "_"+ i,"missid_MSu3_autum"+ "_"+ i, Mass, missid_mean3, a2011.missid_sigma3, a2011.missid_a2c, a2011.missid_n2c)
        self.missid_MSd3 = RooCBShape("missid_MSd3_autum"+ "_"+ i,"missid_MSd3_autum"+ "_"+ i, Mass, missid_mean3, a2011.missid_sigma3, a2011.missid_a3c, a2011.missid_nc)
        self.missid_MS1 = RooAddPdf("missid_MS1_autum"+ "_"+ i,"missid_MS1_autum"+ "_"+ i,self.missid_MSu1,self.missid_MSd1,a2011.hh_f05)
        self.missid_MS2 = RooAddPdf("missid_MS2_autum"+ "_"+ i,"missid_MS2_autum"+ "_"+ i,self.missid_MSu2,self.missid_MSd2,a2011.hh_f05)
        self.missid_MS3 = RooAddPdf("missid_MS3_autum"+ "_"+ i,"missid_MS3_autum"+ "_"+ i,self.missid_MSu3,self.missid_MSd3,a2011.hh_f05)
        
        self.missid_sig0  = RooAddPdf("missid_Sigmodel0_autum" + i,"missid_Sigmodel0_autum"+i, self.missid_MS1, self.missid_MS2, a2011.missid_f1)
        self.missid_peak  = RooAddPdf("missid_autum" + i ,"missid_autum"+i, self.missid_sig0, self.missid_MS3, a2011.missid_f2)
        self.nPiMuNu = RooFormulaVar("B0 pimunu_autum yield " + i,"PiMuNu"+i + "_autum*PiMuNu_autum",RooArgList(v["PiMuNu"+i],v["PiMuNu"]))
        self.nPiMuMu = RooFormulaVar("Bs Kmunu_autum yield " + i,"PiMuMu"+i + "_autum*PiMuMu_autum",RooArgList(v["PiMuMu"+i],v["PiMuMu"]))
        if SERENA:
            self.model = RooAddPdf("mumu_autum model " + i, "mumu_autum model " + i, RooArgList(self.bkg,self.Bs,self.Bd,self.missid_peak,self.PiMuNu,self.PiMuMu), RooArgList(self.nbkg,self.nbs,self.nbd,self.nmis,self.nPiMuNu,self.nPiMuMu))
        else: self.model = RooAddPdf("mumu_autum model " + i, "mumu_autum model " + i, RooArgList(self.bkg,self.Bs,self.Bd,self.missid_peak), RooArgList(self.nbkg,self.nbs,self.nbd,self.nmis))

        
mm = {}
fiter = RooSimultaneous("fitter_autum", "fitter_autum", cat)
combination = RooSimultaneous("combination", "combination", cat)

for i in range(1,9):
    #mm[i] = BsMuMuModel(i)
    #fiter.addPdf(mm[i].model,"mumu autum bin" + str(i))
    #combination.addPdf(mm[i].model,"mumu autum bin" + str(i))
    combination.addPdf(a2011.mm[i].model,"mumu bin" + str(i))
for i in range(1,N_BINS+1):
    mm[i] = BsMuMuModel(i)
    fiter.addPdf(mm[i].model,"mumu autum bin" + str(i))
    combination.addPdf(mm[i].model,"mumu autum bin" + str(i))
    #combination.addPdf(a2011.mm[i].model,"mumu bin" + str(i))

######  Prepare files

mainF =  TFile("/afs/cern.ch/user/d/diegoms/public/for_Mathieu/unblind2012.root")
#TFile("/afs/cern.ch/user/d/diegoms/public/top_secret/unblind_bsmumu_1fb_2.root")
mainF2 = TFile("/afs/cern.ch/user/d/diegoms/vol5/B2hhcalib.root")
thh = mainF2.Get("B2hh")
tmm0 = mainF.Get("T")
#tmm0 = mainF.Get("B2HHTuple/DecayTree")
BDT = BDT_cuts(bdtname, Binning)
#fiducial = "(1>0)"
#fiducial = 'B_s0_BDTS>0.05   && B_s0_PT>500 && B_s0_TAU*1000.<13.248 && muminus_P<500e03 && muplus_P<500e03 && muminus_PT<40e03 && muplus_PT<40e03  && muminus_PIDK<10 && muplus_PIDK<10 && muminus_PIDmu>-5 && muplus_PIDmu>-5 &&B_s0_PT>500 && B_s0_TAU*1000.<13.248 && muminus_P<500e03 && muplus_P<500e03 && muminus_PT<40e03 && muplus_PT<40e03&&muminus_PIDK<10 && muplus_PIDK<10 && muminus_PIDmu>-5 && muplus_PIDmu>-5&&B_s0_BDTS>0.05 '
print "fiducial cuts:", fiducial_autum

############################################ Bs --> mm
fmm, tmm, datamm = {},{},{}
for i in range(1, N_BINS+1):
    ix = str(i)
    fmm[i] = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_mm_autum"+ix+".root","recreate")
    tmm[i] = tmm0.CopyTree(fiducial_autum + BDT[i])
    tmm[i].Write()
    fmm[i].Close()
    fmm[i] = TFile("/afs/cern.ch/user/d/diegoms/vol5/prof_mm_autum"+ix+".root")
    tmm[i] = fmm[i].Get(tmm0.GetName())
    datamm[i] = RooDataSet("datamm"+ix,"datamm"+ix,tmm[i],RooArgSet(Mass))

mumuDataLG = RooDataSet("mumu autum data Low GL", "mumu autum data Low GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu autum bin1", datamm[1]), RooFit.Import("mumu autum bin2", datamm[2]), RooFit.Import("mumu autum bin3", datamm[3]),RooFit.Import("mumu autum bin4", datamm[4]))

mumuDataHG = RooDataSet("mumu autum data High GL", "mumu autum data High GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu autum bin5", datamm[5]), RooFit.Import("mumu autum bin6", datamm[6]), RooFit.Import("mumu autum bin7", datamm[7]))

Data2012 = mumuDataLG.Clone() #RooDataSet("all data","all data", RooArgSet(Mass,cat), RooFit.Import(hhData), RooFit.Import(mumuData))
Data2012.append(mumuDataHG)
combinedData = Data2012.Clone()
combinedData.append(a2011.allData)

summaryConstraints = RooArgSet(Nhh2_cons,Nhh3_cons,Nhh4_cons,Nhh5_cons,Nhh6_cons,Nhh7_cons,Nhh1_cons, NhhTOT_cons )
summaryConstraints.add(RooArgSet(sigmaBs_cons ,sigmaBd_cons,meanBd_cons,meanBs_cons, a2011.a_cons, a2011.fdfs_cons,misid_global_cons))
summaryConstraints.add(RooArgSet(NormBu_cons,NormKPi_cons))
summaryConstraints.add(RooArgSet(a2011.PiMuNu2_cons,a2011.PiMuNu3_cons,a2011.PiMuNu4_cons,a2011.PiMuNu5_cons,a2011.PiMuNu6_cons,a2011.PiMuNu7_cons, PiMuNu_cons))
summaryConstraints.add(RooArgSet(a2011.sigmaPiMuNu1_cons,a2011.sigmaPiMuNu2_cons,a2011.sigmaPiMuNu3_cons,a2011.sigmaPiMuNu4_cons,a2011.sigmaPiMuNu5_cons,a2011.sigmaPiMuNu6_cons,a2011.sigmaPiMuNu7_cons))
summaryConstraints.add(RooArgSet(a2011.meanPiMuNu1_cons,a2011.meanPiMuNu2_cons,a2011.meanPiMuNu3_cons,a2011.meanPiMuNu4_cons,a2011.meanPiMuNu5_cons,a2011.meanPiMuNu6_cons,a2011.meanPiMuNu7_cons))
summaryConstraints.add(RooArgSet(a2011.PiMuMu2_cons,a2011.PiMuMu3_cons,a2011.PiMuMu4_cons,a2011.PiMuMu5_cons,a2011.PiMuMu6_cons,a2011.PiMuMu7_cons, PiMuMu_cons))
summaryConstraints.add(RooArgSet(a2011.sigmaPiMuMu1_cons,a2011.sigmaPiMuMu2_cons,a2011.sigmaPiMuMu3_cons,a2011.sigmaPiMuMu4_cons,a2011.sigmaPiMuMu5_cons,a2011.sigmaPiMuMu6_cons,a2011.sigmaPiMuMu7_cons))
summaryConstraints.add(RooArgSet(a2011.meanPiMuMu1_cons,a2011.meanPiMuMu2_cons,a2011.meanPiMuMu3_cons,a2011.meanPiMuMu4_cons,a2011.meanPiMuMu5_cons,a2011.meanPiMuMu6_cons,a2011.meanPiMuMu7_cons))

combination_summaryConstraints = RooArgSet(Nhh2_cons,Nhh3_cons,Nhh4_cons,Nhh5_cons,Nhh6_cons,Nhh7_cons,Nhh1_cons, NhhTOT_cons)
combination_summaryConstraints.add(RooArgSet(sigmaBs_cons ,sigmaBd_cons,meanBd_cons,meanBs_cons, misid_global_cons))
combination_summaryConstraints.add(RooArgSet(NormBu_cons,NormKPi_cons))
combination_summaryConstraints.add(a2011.summaryConstraints)
combination_summaryConstraints.add(RooArgSet(PiMuNu_cons,PiMuMu_cons ))


def fitThis(Minos = 0):
    result = fiter.fitTo(Data2012,RooFit.Minos(Minos), RooFit.ExternalConstraints(RooArgSet(summaryConstraints)), RooFit.Save(kTRUE))#, RooFit.Strategy(2))

    c = TCanvas()
    c.Divide(4,2)
    fr = {}
    binning = 10
    size = (Mass.getMax()-Mass.getMin())*1./binning
    for i in range(1,N_BINS+1):
        c.cd(i)
        fr[i] = Mass.frame()
        datamm[i].plotOn(fr[i], RooFit.Binning(binning))
        mm[i].model.plotOn(fr[i])#
        mm[i].model.plotOn(fr[i])#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        mm[i].model.plotOn(fr[i], RooFit.Components("model Bs_autum"+str(i)),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        mm[i].model.plotOn(fr[i], RooFit.Components("model Bd_autum"+str(i)),RooFit.LineColor(kGreen),RooFit.LineStyle(7))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        mm[i].model.plotOn(fr[i], RooFit.Components("missid_autum"+str(i)),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        if SERENA:
            mm[i].model.plotOn(fr[i], RooFit.Components("B0pimunu_autum "+str(i)),RooFit.LineColor(kBlack),RooFit.LineStyle(kDashed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
            mm[i].model.plotOn(fr[i], RooFit.Components("BKmunu_autum "+str(i)),RooFit.LineColor(kCyan),RooFit.LineStyle(8))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        fr[i].GetXaxis().SetTitle("m_{#mu#mu} ( MeV/c^{2} )")
        fr[i].SetTitle("B_{s}^{0}#rightarrow#mu^{+}#mu^{-} candidates, BIN [" + str(Binning[bdtname][i-1]) + ", " +str(Binning[bdtname][i])+"]" )
        lhcbName.Draw()
        fr[i].GetYaxis().SetTitle("Events /( "+str(int(size))+" MeV/c^{2} )")
        fr[i].GetYaxis().SetTitleOffset(1.4)
    
        fr[i].Draw()
    return c, fr, result


def fitAll(plot = 0, Minos = 0):
    result = combination.fitTo(combinedData,RooFit.Minos(Minos), RooFit.ExternalConstraints(RooArgSet(combination_summaryConstraints)),RooFit.Strategy(2), RooFit.Save(kTRUE))
    if not plot : return result
    c = TCanvas()
    c.Divide(4,2)
    c2 = TCanvas()
    c2.Divide(4,2)
    fr = {}
    fr2 = {}
    binning = 10
    size = (Mass.getMax()-Mass.getMin())*1./binning
    for i in range(1,N_BINS+1):
        c.cd(i)
        fr[i] = Mass.frame()
        datamm[i].plotOn(fr[i], RooFit.Binning(binning))
        mm[i].model.plotOn(fr[i])#
        mm[i].model.plotOn(fr[i])#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        mm[i].model.plotOn(fr[i], RooFit.Components("model Bs_autum"+str(i)),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        mm[i].model.plotOn(fr[i], RooFit.Components("model Bd_autum"+str(i)),RooFit.LineColor(kGreen),RooFit.LineStyle(7))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        mm[i].model.plotOn(fr[i], RooFit.Components("missid_autum"+str(i)),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        if SERENA:
            mm[i].model.plotOn(fr[i], RooFit.Components("B0pimunu_autum "+str(i)),RooFit.LineColor(kBlack),RooFit.LineStyle(kDotted))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
            mm[i].model.plotOn(fr[i], RooFit.Components("BKmunu_autum "+str(i)),RooFit.LineColor(kCyan),RooFit.LineStyle(kDotted))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        fr[i].GetXaxis().SetTitle("m_{#mu#mu} ( MeV/c^{2} )")
        fr[i].SetTitle("B_{s}^{0}#rightarrow#mu^{+}#mu^{-} candidates, BIN [" + str(Binning[bdtname][i-1]) + ", " +str(Binning[bdtname][i])+"]" )
            
        fr[i].GetYaxis().SetTitle("Events /( "+str(int(size))+" MeV/c^{2} )")
        fr[i].GetYaxis().SetTitleOffset(1.4)
    
        fr[i].Draw()
        lhcbName.Draw()
    for i in range(1,9):
        c2.cd(i)
        fr2[i] = a2011.Mass.frame()
        a2011.datamm[i].plotOn(fr2[i], RooFit.Binning(binning))
        a2011.mm[i].model.plotOn(fr2[i])#
        #a2011.mm[i].model.plotOn(fr2[i])#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        a2011.mm[i].model.plotOn(fr2[i], RooFit.Components("model Bs"+str(i)),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        a2011.mm[i].model.plotOn(fr2[i], RooFit.Components("model Bd"+str(i)),RooFit.LineColor(kGreen),RooFit.LineStyle(7))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        a2011.mm[i].model.plotOn(fr2[i], RooFit.Components("missid"+str(i)),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        if a2011.SERENA:
            a2011.mm[i].model.plotOn(fr2[i], RooFit.Components("B0pimunu "+str(i)),RooFit.LineColor(kBlack),RooFit.LineStyle(kDashed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
            a2011.mm[i].model.plotOn(fr2[i], RooFit.Components("BKmunu "+str(i)),RooFit.LineColor(kCyan),RooFit.LineStyle(8))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
        fr2[i].GetXaxis().SetTitle("m_{#mu#mu} ( MeV/c^{2} )")
        fr2[i].SetTitle("B_{s}^{0}#rightarrow#mu^{+}#mu^{-} candidates, BIN [" + str(a2011.Binning[bdtname][i-1]) + ", " +str(a2011.Binning[bdtname][i])+"]" )
            
        fr2[i].GetYaxis().SetTitle("Events /( "+str(int(size))+" MeV/c^{2} )")
        fr2[i].GetYaxis().SetTitleOffset(1.4)
    
        fr2[i].Draw()
        lhcbName.Draw()
    return c, c2, fr, fr2, result


def printLinkedConstraints(result):
    print "Linked constraints"
    print "===================="
    print "PiMu *Mu* stuff"
    for i in range(7):
        x = "PiMuMu"+str(i+1)
        print v[x].GetName(), v[x].getVal(), v[x].getPropagatedError(result)
    print "PiMu *Nu* stuff"
    for i in range(7):
        x = "PiMuNu"+str(i+1)
        print  v[x].GetName(), v[x].getVal(), v[x].getPropagatedError(result)
    for i in range(7):
        x = "meanPiMuMu"+str(i+1)
        print  v[x].GetName(), v[x].getVal(), v[x].getPropagatedError(result)
    for i in range(7):
        x = "sigmaPiMuMu"+str(i+1)
        print  v[x].GetName(), v[x].getVal(), v[x].getPropagatedError(result)
    for i in range(7):
        x = "meanPiMuNu"+str(i+1)
        print  v[x].GetName(), v[x].getVal(), v[x].getPropagatedError(result)
    for i in range(7):
        x = "sigmaPiMuNu"+str(i+1)
        print  v[x].GetName(), v[x].getVal(), v[x].getPropagatedError(result)
    print a.GetName(), a.getVal(), a.getPropagatedError(result)
    
        
www = fitThis()

BREAK
## nll = combination.createNLL(combinedData,RooFit.NumCPU(8),RooFit.ExternalConstraints(RooArgSet(combination_summaryConstraints)))
## #nll.migrad()
## #nll.migrad()
## #nll.hesse()
## #nll.minos()
## import os

## #  RooPlot* frame1 = frac.frame(Bins(10),Range(0.01,0.95),Title("LL and profileLL in frac")) ;
## #  nll->plotOn(frame1,ShiftToZero()) ;
## outputf = TFile(os.environ["HOME"] + "/profileMix.root","recreate")
## fr = a2011.BR_s.frame(RooFit.Title("LL of BR(B_{s}^{0}#rightarrow #mu^{+}#mu^{-})"),RooFit.Range(-0.5,10))

## pl_Bs = nll.createProfile(RooArgSet(a2011.BR_s))

## #nll.plotOn(fr,RooFit.ShiftToZero()) 

## pl_Bs.plotOn(fr)

## fr.Write()

## ouputf.Close()
## ## zx = fr.Draw()
## #pl_Bd = nll.createProfile(RooArgSet(bdbs))

## ## c.cd(4)
## ## fr4 = Mass.frame()
## ## datamm4.plotOn(fr4, RooFit.Binning(10))#, RooFit.Cut("Bmass<4"))
## ## mm4.model.plotOn(fr4)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## ## mm4.model.plotOn(fr4, RooFit.Components("model Bs4"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## ## mm4.model.plotOn(fr4, RooFit.Components("model Bd4"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## ## mm4.model.plotOn(fr4, RooFit.Components("missid4"),RooFit.LineColor(kMagenta))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## ## fr4.Draw()

## ##############################


## ## c2.cd(4)
## ## hfr4 = Mass.frame()
## ## datahh4.plotOn(hfr4)#, RooFit.Cut("Bmass<4"))
## ## hh4.model.plotOn(hfr4)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## ## hh4.model.plotOn(hfr4, RooFit.Components("Sigmodel4"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## ## hh4.model.plotOn(hfr3, RooFit.Components("shoulder4"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## ## hfr4.Draw()


## ## #### inspired on Francesco code
## ## wsp = RooWorkspace("workspace","workspace")
## ## modelConfig = RooStats.ModelConfig("my_problem",wsp)
## ## modelConfig.SetPdf(fiter)
## ## modelConfig.SetParametersOfInterest(RooArgSet(BR_s))
## ## modelConfig.SetObservables(RooArgSet(Mass,cat))
## ## #modelConfig.SetObservables(RooArgSet(massname,samplename))#
## ## modelConfig.SetConstraintParameters(summaryConstraints)

## ## fc = RooStats.FeldmanCousins(allData,modelConfig)


## ## fc.SetTestSize(0.31731050786291404)#0.05)
## ## fc.UseAdaptiveSampling(kTRUE)
## ## fc.SetNBins(100)
## ## #fc.GetInterval()

## ## ## wsp = RooWorkspace("workspace","workspace")
## ## ## modelConfig = RooStats.ModelConfig("my_problem",wsp)
## ## ## modelConfig.SetPdf(mm[8].model)
## ## ## modelConfig.SetParametersOfInterest(RooArgSet(nbs))
## ## ## modelConfig.SetObservables(RooArgSet(massname))
## ## ## modelConfig.SetConstraintParameters(summaryConstraints)

## ## ## fc = RooStats.FeldmanCousins(datamm[8],modelConfig)
## ## #interval = fc.GetInterval()

## ## mcstudy = RooMCStudy(fiter,RooArgSet(Mass,cat),RooFit.Silence(), RooFit.FitOptions(RooFit.Save(kTRUE),RooFit.PrintEvalErrors(0), RooFit.ExternalConstraints(RooArgSet(summaryConstraints)),RooFit.Minos(kTRUE)),RooFit.Extended())

## ## mcstudy = RooMCStudy(fiter,RooArgSet(Mass,cat),RooFit.Silence(), RooFit.FitOptions(RooFit.Save(kTRUE),RooFit.PrintEvalErrors(0),RooFit.Minos(kTRUE)),RooFit.Extended())
## ## #mcstudy.generateAndFit(1000)
## #w1, w2, w3 = fitThis()

def setEverythingConstant():
    a2011.NormBu.setConstant(kTRUE)
    a2011.NormKPi.setConstant(kTRUE)
    a2011.NormPhi.setConstant(kTRUE)
    a2011.NhhTOT.setConstant(kTRUE)
    a2011.nbd.setConstant(kTRUE)
    a2011.meanBs.setConstant(kTRUE)
    a2011.meanBd.setConstant(kTRUE)
    a2011.sigmaBd.setConstant(kTRUE)
    a2011.sigmaBs.setConstant(kTRUE)
    a2011.PiMuMu.setConstant(kTRUE)
    a2011.PiMuNu.setConstant(kTRUE)
    a2011.a.setConstant(kTRUE)
    a2011.fdfs.setConstant(kTRUE)
    a2011.misid_global_factor.setConstant(kTRUE)

    
    for i in range(1,9):
        if i > 1 :
            getattr(a2011,"Nhh" + str(i) ).setConstant(kTRUE)
            getattr(a2011,"PiMuMu" + str(i) ).setConstant(kTRUE)
            getattr(a2011,"PiMuNu" + str(i) ).setConstant(kTRUE)
        getattr(a2011,"sigmaPiMuMu" + str(i) ).setConstant(kTRUE)
        getattr(a2011,"meanPiMuMu" + str(i) ).setConstant(kTRUE)
        
        getattr(a2011,"sigmaPiMuNu" + str(i) ).setConstant(kTRUE)
        getattr(a2011,"meanPiMuNu" + str(i) ).setConstant(kTRUE)
        
        a2011.mm[i].k.setConstant(kTRUE)
        a2011.mm[i].nbkg.setConstant(kTRUE)
    
    NormBu.setConstant(kTRUE)
    NormKPi.setConstant(kTRUE)
    misid_global_factor.setConstant(kTRUE)
    #NormPhi.setConstant(kTRUE)
    NhhTOT.setConstant(kTRUE)
    nbd.setConstant(kTRUE)
    meanBs.setConstant(kTRUE)
    meanBd.setConstant(kTRUE)
    sigmaBd.setConstant(kTRUE)
    sigmaBs.setConstant(kTRUE)
    PiMuMu.setConstant(kTRUE)
    PiMuNu.setConstant(kTRUE)
    #a.setConstant(kTRUE)
    
    for i in range(1,8):
        v["Nhh" + str(i) ].setConstant(kTRUE)
        #v["sigmaPiMuMu" str(i) ).setConstant(kTRUE)
        #getattr(a2011,"meanPiMuMu" str(i) ).setConstant(kTRUE)
        #getattr(a2011,"PiMuMu" str(i) ).setConstant(kTRUE)
        #getattr(a2011,"sigmaPiMuNu" str(i) ).setConstant(kTRUE)
        #getattr(a2011,"meanPiMuNu" str(i) ).setConstant(kTRUE)
        #getattr(a2011,"PiMuNu" str(i) ).setConstant(kTRUE)
        
        mm[i].k.setConstant(kTRUE)
        mm[i].nbkg.setConstant(kTRUE)
def freebkg():
    for i in range(1,9):
        a2011.mm[i].k.setConstant(kFALSE)
        a2011.mm[i].nbkg.setConstant(kFALSE)
    for i in range(1,8):
        mm[i].k.setConstant(kFALSE)
        mm[i].nbkg.setConstant(kFALSE)
        

    
    
    
    
    
    
    
