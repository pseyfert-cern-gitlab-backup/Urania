#! /usr/bin/env python
from ROOT import *
from MCLimit import *
from Bs2MuMuParams import toytable_eps_bdt as TheTable

from smartpyROOT import *
from array import array as afC
from XTuple import XTuple
from SomeUtils.dataManage import rms
from scipy import double
#from BsMuMuPy.pyAna.CLclass import *
from SomeUtils.alyabar import *
import signalPDF 
import bkgPDF

from functions_for_finalanalysis import *
import sys, os
from Bs2MuMuParams import toytable_test_1fb_AleInput as autum2012table
sSMrel = autum2012table.Bsmumu_BRErr/autum2012table.Bsmumu_BR

fdfs = TheTable.fsfd
s_fdfs = TheTable.fsfdErr
PROFILE = 1
SYST = 1

eps = 4.45e03
s_eps_rel = .45/4.45

## substract fdfs

s_eps_rel = sqrt( s_eps_rel **2 - (s_fdfs/fdfs)**2)

eps_r1 = 3.14e04
s_eps_r1_rel = .17e04/eps_r1
eps_r2 = 1.4e04
s_eps_r2_rel = .15e04/eps_r2
eps_r3 = 1.58e04
s_eps_r3_rel = .26e04/eps_r3


ns_r1 = eps_r1*eps*3.2e-09
ns_r2 = eps_r2*eps*3.2e-09
ns_r3 = eps_r3*eps*3.2e-09

R = 1#6.1/(5/1.29+2/.88)

R1 = R*1.29
R2 = R*1.14
R3 = R*.88

nb_r1 = 5/R1 + 0.1

snb_r1p_rel, snb_r1n_rel = poissonErrors(5)
snb_r1p_rel *= 1./nb_r1
snb_r1n_rel *= 1./nb_r1
#BREAK
nb_r2 = 0.11/R2 +0.06

#snb_r2p, snb_r2n = 0.78, -0.18#poissonErrors(0)
snb_r2p_rel, snb_r2n_rel = 0.62/.11, 0.31/.11#poissonErrors(0)
#snb_r2p, snb_r2n = poissonErrors(0)
#snb_r2p *= 1./R2
#snb_r2n *= 1./R2


nb_r3 =2/R3 + 0.08
snb_r3p_rel, snb_r3n_rel = poissonErrors(2)
snb_r3p_rel *= 1./nb_r3
snb_r3n_rel *= 1./nb_r3



Nobs_r1 = 2
Nobs_r2 = 1
Nobs_r3 = 0

CHANNEL = "Bs"

#else:
hs_r1 = TH1D("s atlas r1", "s atlas r1",1,0,1)
hs_r2 = TH1D("s atlas r2", "s atlas r2",1,0,1)
hs_r3 = TH1D("s atlas r3", "s atlas r3",1,0,1)
hs_r1.SetBinContent(1,double(1.))
hs_r2.SetBinContent(1,double(1.))
hs_r3.SetBinContent(1,double(1.))

hb_r1 = TH1D("b atlas r1", "s atlas r1",1,0,1)
hb_r2 = TH1D("b atlas r2", "s atlas r2",1,0,1)
hb_r3 = TH1D("b atlas r3", "s atlas r3",1,0,1)
hb_r1.SetBinContent(1,double(1.))
hb_r2.SetBinContent(1,double(1.))
hb_r3.SetBinContent(1,double(1.))
    
DataHist_r1 = TH1F("D atlas r1", "D atlas r1", 1,0,1)
DataHist_r2 = TH1F("D atlas r2", "D atlas r2", 1,0,1)
DataHist_r3 = TH1F("D atlas r3", "D atlas r3", 1,0,1)
DataHist_r1.SetBinContent(1,Nobs_r1)
DataHist_r2.SetBinContent(1,Nobs_r2)
DataHist_r3.SetBinContent(1,Nobs_r3)
    
bkg_r1 = csm_template(2)
bkg_r1_no_syst = csm_template(0)
bkg_r2 = csm_template(2)
bkg_r2_no_syst = csm_template(0)
bkg_r3 = csm_template(2)
bkg_r3_no_syst = csm_template(0)

#bkg_r1.set_np("R",-snb_r1n/nb_r1, snb_r1p/nb_r1, NULL,1, NULL,-1)
#bkg_r2.set_np("R",-snb_r2n/nb_r2, snb_r2p/nb_r2, NULL, 1, NULL, -1)
bkg_r1.set_np("R",-0.04,0.04, NULL, 1, NULL, -1)
bkg_r2.set_np("R",-0.04,0.04, NULL, 1, NULL, -1)
bkg_r3.set_np("R",-0.04,0.04, NULL, 1, NULL, -1)

bkg_r1.set_np("bkg level r1",-snb_r1n_rel, snb_r1p_rel, NULL,1, NULL,-1)
bkg_r2.set_np("bkg level r2",-snb_r2n_rel, snb_r2p_rel, NULL, 1, NULL, -1)
bkg_r3.set_np("bkg level r3",-snb_r3n_rel, snb_r3p_rel, NULL, 1, NULL, -1)

bkg_r1.make(hb_r1, nb_r1,0,0,"ATLAS r1")
bkg_r1_no_syst.make(hb_r1, nb_r1,0,0,"ATLAS r1")

bkg_r2.make(hb_r2, nb_r2,0,0,"ATLAS r2")
bkg_r2_no_syst.make(hb_r2, 0.06,0,0,"ATLAS r2")

bkg_r3.make(hb_r3, nb_r3,0,0,"ATLAS r3")
bkg_r3_no_syst.make(hb_r3, nb_r3,0,0,"ATLAS r3")


dcATLAS = {}

#print err_r1, err_r2

###SM
BR_SM = 3.2e-09 ### Nazila 2012
sBR_SM = 0.2#0.3e-09 ## Nazila 2012

sm1 = csm_template(4)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
sm2 = csm_template(4)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model 
sm3 = csm_template(4)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model

sm1.set_np("fdfs",-1*s_fdfs/fdfs, 1*s_fdfs/fdfs ,NULL,1., NULL, -1.)
sm2.set_np("fdfs",-1*s_fdfs/fdfs, 1*s_fdfs/fdfs ,NULL,1., NULL, -1.)
sm3.set_np("fdfs",-1*s_fdfs/fdfs, 1*s_fdfs/fdfs ,NULL,1., NULL, -1.)

sm1.set_np("e_ATLAS1",-1*s_eps_r1_rel, 1*s_eps_r1_rel,NULL,1., NULL, -1) ## COrrelated
sm2.set_np("e_ATLAS2",-1*s_eps_r2_rel, 1*s_eps_r2_rel,NULL,1., NULL, -1) ## COrrelated
sm3.set_np("e_ATLAS3",-1*s_eps_r3_rel, 1*s_eps_r3_rel,NULL,1., NULL, -1) ## COrrelated

sm1.set_np("e_ATLAS",-1*s_eps_rel/eps, 1*s_eps_rel/eps,NULL,1., NULL, -1) ## COrrelated
sm2.set_np("e_ATLAS",-1*s_eps_rel/eps, 1*s_eps_rel/eps,NULL,1., NULL, -1) ## COrrelated
sm3.set_np("e_ATLAS",-1*s_eps_rel/eps, 1*s_eps_rel/eps,NULL,1., NULL, -1) ## COrrelated

sm1.set_np("SM",-1*sBR_SM/BR_SM, 1*sBR_SM/BR_SM,NULL,1., NULL, -1) ## COrrelated
sm2.set_np("SM",-1*sBR_SM/BR_SM, 1*sBR_SM/BR_SM,NULL,1., NULL, -1) ## COrrelated
sm3.set_np("SM",-1*sBR_SM/BR_SM, 1*sBR_SM/BR_SM,NULL,1., NULL, -1) ## COrrelated

    
#BREAK
sm1.make(hs_r1,ns_r1,0,1, "ATLAS r1")
sm2.make(hs_r2,ns_r2,0,1, "ATLAS r2")
sm3.make(hs_r3,ns_r3,0,1, "ATLAS r3")

def DoSigModel(BR, dc = dcATLAS):
    
    dc[str(BR) + "r1"] = csm_template(4)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
    dc[str(BR) + "r1_no_syst"] = csm_template(0)
    dc[str(BR) + "r2"] = csm_template(4)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
    dc[str(BR) + "r2_no_syst"] = csm_template(0)

    dc[str(BR) + "r3"] = csm_template(4)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
    dc[str(BR) + "r3_no_syst"] = csm_template(0)
    
    dc[str(BR) + "r1"].set_np("fdfs",-1*s_fdfs/fdfs, 1*s_fdfs/fdfs ,NULL,1., NULL, -1.)
    dc[str(BR) + "r2"].set_np("fdfs",-1*s_fdfs/fdfs, 1*s_fdfs/fdfs ,NULL,1., NULL, -1.)
    dc[str(BR) + "r3"].set_np("fdfs",-1*s_fdfs/fdfs, 1*s_fdfs/fdfs ,NULL,1., NULL, -1.)
    
    dc[str(BR) + "r1"].set_np("e_ATLAS1",-1*s_eps_r1_rel, 1*s_eps_r1_rel,NULL,1., NULL, -1) ## COrrelated
    dc[str(BR) + "r2"].set_np("e_ATLAS2",-1*s_eps_r2_rel, 1*s_eps_r2_rel,NULL,1., NULL, -1) ## COrrelated
    dc[str(BR) + "r3"].set_np("e_ATLAS3",-1*s_eps_r3_rel, 1*s_eps_r3_rel,NULL,1., NULL, -1) ## COrrelated

    dc[str(BR) + "r1"].set_np("e_ATLAS",-1*s_eps_rel/eps, 1*s_eps_rel/eps,NULL,1., NULL, -1) ## COrrelated
    dc[str(BR) + "r2"].set_np("e_ATLAS",-1*s_eps_rel/eps, 1*s_eps_rel/eps,NULL,1., NULL, -1) ## COrrelated
    dc[str(BR) + "r3"].set_np("e_ATLAS",-1*s_eps_rel/eps, 1*s_eps_rel/eps,NULL,1., NULL, -1) ## COrrelated

    dc[str(BR) + "r1"].set_np("TH",-sSMrel, sSMrel,NULL, 1., NULL, -1.)
    dc[str(BR) + "r2"].set_np("TH",-sSMrel, sSMrel,NULL, 1., NULL, -1.)
    dc[str(BR) + "r3"].set_np("TH",-sSMrel, sSMrel,NULL, 1., NULL, -1.)
    
    ns1 = ns_r1*BR/3.2e-09
    ns2 = ns_r2*BR/3.2e-09
    ns3 = ns_r3*BR/3.2e-09
    
    #BREAK
    dc[str(BR) + "r1"].make(hs_r1,ns1,0,1, "ATLAS r1")
    dc[str(BR) + "r1_no_syst"].make(hs_r1,ns1,0,1, "ATLAS r1")

    dc[str(BR) + "r2"].make(hs_r2,ns2,0,1, "ATLAS r2")
    dc[str(BR) + "r2_no_syst"].make(hs_r2,ns2,0,1, "ATLAS r2")

    dc[str(BR) + "r3"].make(hs_r3,ns3,0,1, "ATLAS r3")
    dc[str(BR) + "r3_no_syst"].make(hs_r3,ns3,0,1, "ATLAS r3")
    return dc

tests, testpes = {}, {}
  
nulpe = csm_model()     #### This must contain ALL syst
nul = csm_model()   

bkg_r1.add_to(nulpe)
bkg_r1_no_syst.add_to(nul)
bkg_r2.add_to(nulpe)
bkg_r2_no_syst.add_to(nul)
bkg_r3.add_to(nulpe)
bkg_r3_no_syst.add_to(nul)


def DoTestHyp(BR):
    DoSigModel(BR)
    test = csm_model()
    testpe = csm_model()
   
    bkg_r1.add_to(testpe)
    bkg_r2.add_to(testpe)
    bkg_r3.add_to(testpe)
    bkg_r1_no_syst.add_to(test)
    bkg_r2_no_syst.add_to(test)
    bkg_r3_no_syst.add_to(test)
   
    
    dcATLAS[str(BR)+"r1"].add_to(testpe)
    dcATLAS[str(BR)+"r2"].add_to(testpe)
    dcATLAS[str(BR)+"r3"].add_to(testpe)
    dcATLAS[str(BR)+"r1_no_syst"].add_to(test)
    dcATLAS[str(BR)+"r2_no_syst"].add_to(test)
    dcATLAS[str(BR)+"r3_no_syst"].add_to(test)

    return testpe, test

def DoCL(BR, npe =0, syst = 1 ):
    testpes[BR], tests[BR] = DoTestHyp(BR)
  
    CL = mclimit_csm()
    if not (PROFILE and syst):
        CL.set_null_hypothesis(nul)
        CL.set_test_hypothesis(tests[BR])
    else:
        CL.set_null_hypothesis(nulpe)
        CL.set_test_hypothesis(testpes[BR])
        
    if syst:
        CL.set_null_hypothesis_pe(nulpe)
        CL.set_test_hypothesis_pe(testpes[BR])
    else:
        CL.set_null_hypothesis_pe(nul) #### no syst
        CL.set_test_hypothesis_pe(tests[BR])
        
    CL.set_datahist(DataHist_r1, "ATLAS r1")
    CL.set_datahist(DataHist_r2, "ATLAS r2")
    CL.set_datahist(DataHist_r3, "ATLAS r3")
   
    if npe: CL.set_npe(npe)
    
    return CL




def do_scan(filename, stop_95 = False):
    #tup = XTuple(filename, labels = ["BR/F", "CLs/F","CLb/F", "CLsb/F"])
    tup = XTuple(filename, labels = ["BR/F","ts/F", "chi2/F", "CLs/F","CLb/F", "CLsb/F","CLs_exp_b_med/F" , "CLs_exp_b_p1/F", "CLs_exp_b_p2/F","CLs_exp_b_m1/F" ,"CLs_exp_b_m2/F","CLb_exp_s_med/F" , "CLb_exp_s_p1/F", "CLb_exp_s_p2/F","CLb_exp_s_m1/F" ,"CLb_exp_s_m2/F"])

    c90, c95 = 0.,0
    for j in range(10):
        i = 20 + j
        #i = 20 + 1*j
        CL = DoCL(i*1e-09,300000, syst=SYST)
        CL.run_pseudoexperiments()
        cl = CL.cls()
        clb = CL.clb()
        clsb = CL.clsb()
        print i,cl, clb, clsb
        tup.fillItem("BR", i)
        tup.fillItem("ts", CL.ts())

        tup.fillItem("CLs",cl)
        tup.fillItem("CLb",clb)
        tup.fillItem("CLsb",clsb)
        tup.fillItem("CLs_exp_b_med",CL.clsexpbmed())
        tup.fillItem("CLs_exp_b_p1",CL.clsexpbp1())
        tup.fillItem("CLs_exp_b_p2",CL.clsexpbp2())
        tup.fillItem("CLs_exp_b_m1",CL.clsexpbm1())
        tup.fillItem("CLs_exp_b_m2",CL.clsexpbm2())

        tup.fillItem("CLb_exp_s_med",CL.clbexpsmed())
        tup.fillItem("CLb_exp_s_p1",CL.clbexpsp1())
        tup.fillItem("CLb_exp_s_p2",CL.clbexpsp2())
        tup.fillItem("CLb_exp_s_m1",CL.clbexpsm1())
        tup.fillItem("CLb_exp_s_m2",CL.clbexpsm2())
        tup.fill()
        if cl < 0.1 and not c90: c90 = i
        if cl<0.05:
            print "C90:",c90
            print "c95:",i
            if stop_95:
                tup.close()
                return c90, i
    tup.close()

#do_scan("ATLAS2012_Profile"+str(PROFILE) + "_SYST"+str(SYST))#, stop_95 = True)
