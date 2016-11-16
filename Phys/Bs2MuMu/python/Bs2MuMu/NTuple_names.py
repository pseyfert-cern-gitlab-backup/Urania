aa = "&&"
kullback = "mu1_track_CloneDist>5000 && mu2_track_CloneDist>5000"
trchi2 = "mu1_track_Chi2DoF<4 && mu2_track_Chi2DoF<4"

fiducial = kullback + aa + trchi2 + "&& Blife_ps_r<13.248   && mu1ptot<0.5e06 && mu2ptot <0.5e06 && Bpt>500 && BDTS_cx>0.05 && mu1pt<4e04 && mu2pt<4e04"




dll ="Bmass>0" + '  && PIDk1<10 && PIDk2<10 && PIDmu1>-5 && PIDmu2>-5'
insb  = " && (Bmass<5000 || Bmass>5433)"


fiducial0 =  "Blife_ps_r<13.248   && mu1ptot<5e05 && mu2ptot <5e05 && Bpt>500 && BDTS_cx>0.05 && mu1pt<4e04 && mu2pt<4e04 && mu1_pidPreslMom && mu2_pidPreslMom &&  mu1_pidInAcc && mu2_pidInAcc" #+ "&& Hlt2Tis"

fiducial = dll + aa + fiducial0


#op2 = S.sidebandsFiter(t, "Bmass", "Bpt>500 && Bmass>4000 && Bmass<8000 && BDTflat<0.25", left = 5000, right = 5358+60, bkgf = S.double_exp_bkg,left2 = 5272-60, shorTime = False)


fiducial_cut = 'aBDT05flat!=0.   && B_s0_BDTS>0.05   && B_s0_PT>500 && B_s0_TAU*1000.<13.248 && muminus_P<500e03 && muplus_P<500e03 && muminus_PT<40e03 && muplus_PT<40e03  && muminus_PIDK<10 && muplus_PIDK<10 && muminus_PIDmu>-5 && muplus_PIDmu>-5 &&B_s0_PT>500 && B_s0_TAU*1000.<13.248 && muminus_P<500e03 && muplus_P<500e03 && muminus_PT<40e03 && muplus_PT<40e03'# && B_s0_MM > 4900 && B_s0_MM <6000'
BDTS_cut = 'B_s0_BDTS>0.05 '
DLL_cut = 'muminus_PIDK<10 && muplus_PIDK<10 && muminus_PIDmu>-5 && muplus_PIDmu>-5'
bdtname = "BDT9_05"


massname = 'B_s0_MM'
if massname == 'B_s0_MM':
    bdtname = 'aBDT05flat'
    #t = t_flavio
    fiducial = fiducial_cut +aa+ DLL_cut + aa  +BDTS_cut 
    insb =  " && (B_s0_MM<5000 || B_s0_MM>5433)"
#else: t = t_cern

def BDT_cuts(bdtname, Binning):
    BDT = {}
    for i  in range(len(Binning[bdtname])-1):
        BDT[i+1] =  "&& "+bdtname+">=" + str(Binning[bdtname][i]) +" && "+bdtname+"<" + str(Binning[bdtname][i+1])
    
    BDT["L"] =  "&& "+bdtname+">0.8 && "+bdtname+"<1.0"
    return BDT
