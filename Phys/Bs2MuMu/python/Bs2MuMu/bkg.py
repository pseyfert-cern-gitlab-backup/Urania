from ROOT import *

from SomeMassModels import sidebands as S
aa = "&&"
kullback = "mu1_track_CloneDist>5000 && mu2_track_CloneDist>5000"
trchi2 = "mu1_track_Chi2DoF<4 && mu2_track_Chi2DoF<4"

fiducial = kullback + aa + trchi2 + "&& Blife_ps_r<13.248   && mu1ptot<0.5e06 && mu2ptot <0.5e06 && Bpt>500 && BDTS_cx>0.05 && mu1pt<4e04 && mu2pt<4e04"
#f_flavio = TFile("/afs/cern.ch/user/d/diegoms/vol5/1020pbDecember7BDTSwBDT.root")
f_flavio = TFile("/afs/cern.ch/user/d/diegoms/vol5/ntuple_1fb_unblinded.root")
t_flavio = f_flavio.Get("B2MuMuTuple/DecayTree")

f_cern = TFile("/afs/cern.ch/project/lbcern/vol2/albrecht/Bs2mm/JA_ntuples/BsMuMu_blinded_ntuples_1025pb_withbdt9.root")
t_cern = f_cern.Get("Bs2MuMu")




dll ="Bmass>0" + '  && PIDk1<10 && PIDk2<10 && PIDmu1>-5 && PIDmu2>-5'
insb  = " && (Bmass<5000 || Bmass>5433)"

fiducial = dll + "&& Bmass>4900 && Bmass<6000 && Blife_ps_r<13.248   && mu1ptot<5e05 && mu2ptot <5e05 && Bpt>500 && BDTS_cx>0.05 && mu1pt<4e04 && mu2pt<4e04 && mu1_pidPreslMom && mu2_pidPreslMom && mu1_pidInAcc && mu2_pidInAcc" #+ "&& Hlt2Tis"


#op2 = S.sidebandsFiter(t, "Bmass", "Bpt>500 && Bmass>4000 && Bmass<8000 && BDTflat<0.25", left = 5000, right = 5358+60, bkgf = S.double_exp_bkg,left2 = 5272-60, shorTime = False)


fiducial_cut = 'B_s0_PT>500 && B_s0_TAU*1000.<13.248 && muminus_P<500e03 && muplus_P<500e03 && muminus_PT<40e03 && muplus_PT<40e03 && B_s0_MM > 4900 && B_s0_MM <6000'
BDTS_cut = 'B_s0_BDTS>0.05 '
DLL_cut = 'muminus_PIDK<10 && muplus_PIDK<10 && muminus_PIDmu>-5 && muminus_PIDmu>-5'


massname = 'B_s0_MM'
if massname == 'B_s0_MM':
    bdtname = 'aBDT05flat'
    t = t_flavio
    fiducial = fiducial_cut +aa+ DLL_cut + aa  +BDTS_cut 
    insb =  " && (B_s0_MM<5000 || B_s0_MM>5433)"
else: t = t_cern

def bkg_in_bin(x,y,Nsb,idx,  a = 4900, b = 5000 , c = 5418, d = 6000):#, b = Binning[massname][0], c = Binning[massname][1]):
    ## a = M_min
##     b = M_b
##     c = M_c
##     d = M_max
    kl = idx
    iDk = 1./(exp(kl*a) +exp(kl*c) - exp(kl*b) - exp(kl*d))
    Nxy = iDk*Nsb*(exp(kl*x)-exp(kl*y))
    return Nxy


BDT = {}
BDT[1] =  "&& "+bdtname+"<0.25 && "+bdtname+"<0.25"
BDT[2] =  "&& "+bdtname+">0.25 && "+bdtname+"<0.4"
BDT[3] =  "&& "+bdtname+">0.4 && "+bdtname+"<0.5"
BDT[4] =  "&& "+bdtname+">0.5 && "+bdtname+"<0.6"
BDT[5] =  "&& "+bdtname+">0.6 && "+bdtname+"<0.7"
BDT[6] =  "&& "+bdtname+">0.7 && "+bdtname+"<0.8"
BDT[7] =  "&& "+bdtname+">0.8 && "+bdtname+"<0.9"
BDT[8] =  "&& "+bdtname+">0.9 && "+bdtname+"<1.0"

BDT["L"] =  "&& "+bdtname+">0.8 && "+bdtname+"<1.0"


c = TCanvas()
c.Divide(4,2)

op = {}

for i in (range(1,9) + ["L"]):
    op[i] = S.sidebandsFiter(t, massname, fiducial + BDT[i], left = 5000, right = 5433, bkgf = S.exp_bkg,left2 = 5224.63, shorTime = False,Mmin = 4900,Mmax=6000)
    
op[7].indx.setVal(op["L"].indx.getVal())
op[7].indx.setConstant(kTRUE)
op[7].fit(massname)
op[8].indx.setVal(op["L"].indx.getVal())
op[8].indx.setConstant(kTRUE)
op[8].fit(massname)

for i in range(1,9):
    c.cd(i)
    op[i].plot(20)
    print "BIN:" , i
    print "Nsb:", t.GetEntries(fiducial + BDT[i]+ insb)
    print op[i].nbkg.getVal(), op[i].nbkg.getAsymErrorHi(), op[i].nbkg.getAsymErrorLo()
    if i< 7: print op[i].indx.getVal(), op[i].indx.getAsymErrorHi(), op[i].indx.getAsymErrorLo()
    else: print op["L"].indx.getVal(), op["L"].indx.getAsymErrorHi(), op["L"].indx.getAsymErrorLo()
    print "-_- -_- -_- -_- -_- -_- -_-"
    


## MY SPECIAL TUPLE  N_left    N_right   N_side_tot
## bin1_4900_5000    2096      7140      9236      
## bin2_4900_5000    70        204       274        
## bin3_4900_5000    20        53        73        
## bin4_4900_5000    6         15        21        
## bin5_4900_5000    3         13        16        
## bin6_4900_5000    2         3         5          
## bin7_4900_5000    3         3         6          
## bin8_4900_5000    2         0         2  


## OFFICIAL ONE      N_left    N_right   N_side_tot
## bin1_4900_5000    2096      7140      9236      
## bin2_4900_5000    70        204       274        
## bin3_4900_5000    20        53        73        
## bin4_4900_5000    6         15        21        
## bin5_4900_5000    3         13        16        
## bin6_4900_5000    2         3         5          
## bin7_4900_5000    3         3         6          
