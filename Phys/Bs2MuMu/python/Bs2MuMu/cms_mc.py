#! /usr/bin/env python
from ROOT import *
from MCLimit import *
from Bs2MuMuParams import toytable_eps_bdt as TheTable

from smartpyROOT import *
from array import array as afC
from XTuple import XTuple
from SomeUtils.dataManage import rms
from scipy import double
from SomeUtils.alyabar import *
import signalPDF 
import bkgPDF

from functions_for_finalanalysis import *
import sys, os

from Bs2MuMuParams import toytable_test_1fb_AleInput as autum2012table
sSMrel = autum2012table.Bsmumu_BRErr/autum2012table.Bsmumu_BR

fdfs = TheTable.fsfd
s_fdfs = TheTable.fsfdErr

ns_b = 2.70 ## SM = 3.2
ns_c = 1.23

err_b = 0.41 ## 
err_c = 0.18


err_b = sqrt(err_b**2 - (s_fdfs/fdfs * ns_b)**2) #- ((.2/3.2) * ns_b)**2)
err_c = sqrt(err_c**2 - (s_fdfs/fdfs * ns_c)**2) #- ((.2/3.2) * ns_c)**2)

nb_b = 0.59 + .18
snb_b = sqrt(0.06**2 + 0.50**2)


nb_c = 1.14+0.08
snb_c = sqrt(0.02**2 + 0.53**2)


Nobs_b = 2
Nobs_e = 4

CHANNEL = "Bs"

#if 0: return "wwwww"
#else:
hs_b = TH1D("s cms barrel", "s cms barrel",1,0,1)
hs_e = TH1D("s cms endcup", "s cms endcup",1,0,1)
hs_b.SetBinContent(1,double(1.))
hs_e.SetBinContent(1,double(1.))

hb_b = TH1D("b cms barrel", "s cms barrel",1,0,1)
hb_e = TH1D("b cms endcup", "s cms endcup",1,0,1)
hb_b.SetBinContent(1,double(1.))
hb_e.SetBinContent(1,double(1.))

DataHist_b = TH1F("D cms barrel", "D cms barrel", 1,0,1)
DataHist_e = TH1F("D cms endcup", "D cms endcup", 1,0,1)
DataHist_b.SetBinContent(1,Nobs_b)
DataHist_e.SetBinContent(1,Nobs_e)
    
bkg_b = csm_template(1)
bkg_b_no_syst = csm_template(0)
bkg_e = csm_template(1)
bkg_e_no_syst = csm_template(0)

#bkg_b.set_np("bkg level barrel",-snb_b/nb_b, snb_b/nb_b, NULL,1, NULL,-1)
#bkg_e.set_np("bkg level EC",-snb_c/nb_c, snb_c/nb_c, NULL, 1, NULL, -1)

bkg_b.set_np("bkg level",-snb_b/nb_b, snb_b/nb_b, NULL,1, NULL,-1)
bkg_e.set_np("bkg level",-snb_c/nb_c, snb_c/nb_c, NULL, 1, NULL, -1)
bkg_b.make(hb_b, nb_b,0,0,"CMS barrel")
bkg_b_no_syst.make(hb_b, nb_b,0,0,"CMS barrel")
bkg_e.make(hb_e, nb_c,0,0,"CMS EC")
bkg_e_no_syst.make(hb_e, nb_c,0,0,"CMS EC")


dcCMS = {}

BR_SM = 3.2e-09 ### Nazila 2012
sBR_SM = 0.2#0.3e-09 ## Nazila 2012


sm1 = csm_template(3)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
sm2 = csm_template(3)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model

sm1.set_np("fdfs",-1*s_fdfs/fdfs, 1*s_fdfs/fdfs ,NULL,1., NULL, -1.)
sm2.set_np("fdfs",-1*s_fdfs/fdfs, 1*s_fdfs/fdfs ,NULL,1., NULL, -1.)

sm1.set_np("e_CMS",-1*err_b/ns_b, 1*err_b/ns_b,NULL,1., NULL, -1) ## COrrelated
sm2.set_np("e_CMS",-1*err_c/ns_c, 1*err_c/ns_c,NULL,1., NULL, -1.) ## COrrelated

sm1.set_np("SM",-1*sBR_SM/BR_SM, 1*sBR_SM/BR_SM,NULL,1., NULL, -1) ## COrrelated
sm2.set_np("SM",-1*sBR_SM/BR_SM, 1*sBR_SM/BR_SM,NULL,1., NULL, -1) ## COrrelated

sm1.make(hs_b,ns_b,0,1, "CMS barrel")
sm2.make(hs_e,ns_c,0,1, "CMS EC")


print err_b, err_c
def DoSigModel(BR, dc = dcCMS):
    
    dc[str(BR) + "barrel"] = csm_template(3)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
    dc[str(BR) + "barrel_no_syst"] = csm_template(0)
    dc[str(BR) + "EC"] = csm_template(3)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
    dc[str(BR) + "EC_no_syst"] = csm_template(0)
    
    dc[str(BR) + "barrel"].set_np("fdfs",-1*s_fdfs/fdfs, 1*s_fdfs/fdfs ,NULL,1., NULL, -1.)
    dc[str(BR) + "EC"].set_np("fdfs",-1*s_fdfs/fdfs, 1*s_fdfs/fdfs ,NULL,1., NULL, -1.)
    dc[str(BR) + "EC"].set_np("TH",-sSMrel, sSMrel,NULL,1., NULL, -1.)
    dc[str(BR) + "barrel"].set_np("TH",-sSMrel, sSMrel,NULL,1., NULL, -1.)
     
    dc[str(BR) + "barrel"].set_np("e_CMS",-1*err_b/ns_b, 1*err_b/ns_b,NULL,1., NULL, -1) ## COrrelated
    dc[str(BR) + "EC"].set_np("e_CMS",-1*err_c/ns_c, 1*err_c/ns_c,NULL,1., NULL, -1.) ## COrrelated
    
    ns1 = ns_b*BR/3.2e-09
    ns2 = ns_c*BR/3.2e-09
    
    #BREAK
    dc[str(BR) + "barrel"].make(hs_b,ns1,0,1, "CMS barrel")
    dc[str(BR) + "barrel_no_syst"].make(hs_b,ns1,0,1, "CMS barrel")

    dc[str(BR) + "EC"].make(hs_e,ns2,0,1, "CMS EC")
    dc[str(BR) + "EC_no_syst"].make(hs_e,ns2,0,1, "CMS EC")
    return dc

tests, testpes = {}, {}
  
nulpe = csm_model()     #### This must contain ALL syst
nul = csm_model()   

bkg_b.add_to(nulpe)
bkg_b_no_syst.add_to(nul)
bkg_e.add_to(nulpe)
bkg_e_no_syst.add_to(nul)


def DoTestHyp(BR):
   

    DoSigModel(BR)
   

    test = csm_model()
    testpe = csm_model()
   
    bkg_b.add_to(testpe)
    bkg_e.add_to(testpe)
    bkg_b_no_syst.add_to(test)
    bkg_e_no_syst.add_to(test)
    
    dcCMS[str(BR)+"barrel"].add_to(testpe)
    dcCMS[str(BR)+"EC"].add_to(testpe)
    dcCMS[str(BR)+"barrel_no_syst"].add_to(test)
    dcCMS[str(BR)+"EC_no_syst"].add_to(test)

    return testpe, test

def DoCL(BR, npe =0, syst = 1 ):
    testpes[BR], tests[BR] = DoTestHyp(BR)
  
    CL = mclimit_csm()
    CL.set_null_hypothesis(nul)
    CL.set_test_hypothesis(tests[BR])

    if syst:
        CL.set_null_hypothesis_pe(nulpe)
        CL.set_test_hypothesis_pe(testpes[BR])
    else:
        CL.set_null_hypothesis_pe(nul) #### no syst
        CL.set_test_hypothesis_pe(tests[BR])
        
    CL.set_datahist(DataHist_b, "CMS barrel")
    CL.set_datahist(DataHist_e, "CMS EC")
   
    if npe: CL.set_npe(npe)
    
    return CL




def do_scan(filename, stop_95 = False):
    #tup = XTuple(filename, labels = ["BR/F", "CLs/F","CLb/F", "CLsb/F"])
    tup = XTuple(filename, labels = ["BR/F","ts/F", "chi2/F", "CLs/F","CLb/F", "CLsb/F","CLs_exp_b_med/F" , "CLs_exp_b_p1/F", "CLs_exp_b_p2/F","CLs_exp_b_m1/F" ,"CLs_exp_b_m2/F","CLb_exp_s_med/F" , "CLb_exp_s_p1/F", "CLb_exp_s_p2/F","CLb_exp_s_m1/F" ,"CLb_exp_s_m2/F"])

    c90, c95 = 0.,0
    for j in range(40):
        i = 2.0 + 0.05*j
        CL = DoCL(i*1e-09, 5000, syst=1)
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

#do_scan("CMS2012_syst_b")#, stop_95 = True)
