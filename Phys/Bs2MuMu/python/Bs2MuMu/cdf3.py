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

fdfs0 = 3.55#TheTable.fsfd
s_fdfs0 = 0.47#TheTable.fsfdErr

fdfs = TheTable.fsfd
s_fdfs = TheTable.fsfdErr



def do_cdf_bin(x, binname = "b cdf CC bin1", scale_to = 0., scale_by = 0.):
    h = TH1D(binname ,  binname,5,0,1)
    for i in range(5):
        h.SetBinContent(i+1, x[i])
    if scale_to: h.Scale(scale_to*1./h.GetSum())
    if scale_by: h.Scale(scale_by)
    return h

CHANNEL = "Bs"

BCC = 8*[TH1F()]
BCF = 8*[TH1F()]
SCC = 8*[TH1F()]
SCF = 8*[TH1F()]
DCC = 8*[TH1F()]
DCF = 8*[TH1F()]

dcBkgCDF = {}
if CHANNEL == "Bd":
    mean = double(5275.01) #(Bd)
    s_mean = 0.87
    
else:
    BCC[0] = do_cdf_bin([8.02, 7.94, 7.87, 7.79, 7.71], "b cdf CC bin1", scale_to = 53.6)
    BCC[1] = do_cdf_bin([8.43, 8.34, 8.26, 8.18, 8.10], "b cdf CC bin2", scale_to = 52.5)
    BCC[2] = do_cdf_bin([3.55, 3.51, 3.48, 3.44, 3.41], "b cdf CC bin3", scale_to = 23.04)
    BCC[3] = do_cdf_bin([3.51, 3.47, 3.44, 3.41, 3.37], "b cdf CC bin4", scale_to = 26.6)
    BCC[4] = do_cdf_bin([2.87, 2.84, 2.81, 2.78, 2.75], "b cdf CC bin5", scale_to = 19.36)
    BCC[5] = do_cdf_bin([1.62, 1.60, 1.58, 1.57, 1.55], "b cdf CC bin6", scale_to = 12.7)
    BCC[6] = do_cdf_bin([0.82, 0.80, 0.79, 0.78, 0.78], "b cdf CC bin7", scale_to = 4.56)
    BCC[7] = do_cdf_bin([0.21, 0.18, 0.16, 0.16, 0.16], "b cdf CC bin8", scale_to = 1.22)

    SCC[0] = do_cdf_bin([0.002, 0.007, 0.011, 0.006, 0.001], "s cdf CC bin1", scale_by = 1.22)
    SCC[1] = do_cdf_bin([0.004, 0.015, 0.020, 0.011, 0.003], "s cdf CC bin2", scale_by = 1.22)
    SCC[2] = do_cdf_bin([0.004, 0.010, 0.014, 0.008, 0.002], "s cdf CC bin3", scale_by = 1.22)
    SCC[3] = do_cdf_bin([0.005, 0.016, 0.023, 0.012, 0.002], "s cdf CC bin4", scale_by = 1.22)
    SCC[4] = do_cdf_bin([0.008, 0.022, 0.032, 0.016, 0.003], "s cdf CC bin5", scale_by = 1.22)
    SCC[5] = do_cdf_bin([0.010, 0.029, 0.041, 0.022, 0.005], "s cdf CC bin6", scale_by = 1.22)
    SCC[6] = do_cdf_bin([0.013, 0.046, 0.062, 0.031, 0.007], "s cdf CC bin7", scale_by = 1.22)
    SCC[7] = do_cdf_bin([0.052, 0.167, 0.227, 0.119, 0.029], "s cdf CC bin8", scale_by = 1.22)

    DCC[0] = do_cdf_bin([9+1, 6+2, 6+1, 2+1, 5+2], "D cdf CC bin1")
    DCC[1] = do_cdf_bin([8+2, 6+3, 11+2, 11+2, 7+2], "D cdf CC bin2")
    DCC[2] = do_cdf_bin([5, 6+1, 2+1, 5+1, 4+2], "D cdf CC bin3")
    DCC[3] = do_cdf_bin([4+1, 5+2, 4+1, 5+1, 7+1], "D cdf CC bin4")
    DCC[4] = do_cdf_bin([4+1, 5+1, 2+1, 3+1, 4+1], "D cdf CC bin5")
    DCC[5] = do_cdf_bin([1, 4, 7+1, 1+1, 3], "D cdf CC bin6")
    DCC[6] = do_cdf_bin([1, 1, 3, 0+1, 0], "D cdf CC bin7")
    DCC[7] = do_cdf_bin([0, 1, 2, 0, 1], "D cdf CC bin8")

    BCF[0] = do_cdf_bin([8.49, 8.39, 8.28, 8.17, 8.07], "b cdf CF bin1", scale_to = 42.0)
    BCF[1] = do_cdf_bin([9.45, 9.33, 9.21, 9.10, 8.98], "b cdf CF bin2", scale_to = 50.3)
    BCF[2] = do_cdf_bin([4.91, 4.85, 4.79, 4.73, 4.67], "b cdf CF bin3", scale_to = 25.97)
    BCF[3] = do_cdf_bin([3.87, 3.82, 3.77, 3.73, 3.68], "b cdf CF bin4", scale_to = 18.21)
    BCF[4] = do_cdf_bin([3.29, 3.25, 3.21, 3.17, 3.12], "b cdf CF bin5", scale_to = 19.5)
    BCF[5] = do_cdf_bin([2.38, 2.34, 2.31, 2.28, 2.25], "b cdf CF bin6", scale_to = 12.88)
    BCF[6] = do_cdf_bin([0.67, 0.66, 0.65, 0.64, 0.63], "b cdf CF bin7", scale_to = 3.70)
    BCF[7] = do_cdf_bin([0.56, 0.54, 0.53, 0.52, 0.51], "b cdf CF bin8",scale_to = 3.817)

    SCF[0] = do_cdf_bin([0.002, 0.006, 0.007, 0.005, 0.001], "s cdf CF bin1", scale_by = 1.22)
    SCF[1] = do_cdf_bin([0.003, 0.012, 0.015, 0.009, 0.002], "s cdf CF bin2", scale_by = 1.22)
    SCF[2] = do_cdf_bin([0.003, 0.009, 0.012, 0.006, 0.001], "s cdf CF bin3", scale_by = 1.22)
    SCF[3] = do_cdf_bin([0.004, 0.012, 0.017, 0.009, 0.002], "s cdf CF bin4", scale_by = 1.22)
    SCF[4] = do_cdf_bin([0.005, 0.015, 0.021, 0.013, 0.003], "s cdf CF bin5", scale_by = 1.22)
    SCF[5] = do_cdf_bin([0.008, 0.026, 0.036, 0.019, 0.005], "s cdf CF bin6", scale_by = 1.22)
    SCF[6] = do_cdf_bin([0.007, 0.021, 0.029, 0.017, 0.004], "s cdf CF bin7", scale_by = 1.22)
    SCF[7] = do_cdf_bin([0.039, 0.116, 0.159, 0.090, 0.023], "s cdf CF bin8", scale_by = 1.22)

    DCF[0] = do_cdf_bin([8+2, 13+2, 9+2, 9+4, 9+2], "D cdf CF bin1")
    DCF[1] = do_cdf_bin([7+2, 8+2, 7+2, 11+2, 4+2], "D cdf CF bin2")
    DCF[2] = do_cdf_bin([1+1, 5+1, 6+1, 3+1, 5+1], "D cdf CF bin3")
    DCF[3] = do_cdf_bin([4+1, 1+1, 6, 3+1, 3+2], "D cdf CF bin4")
    DCF[4] = do_cdf_bin([0+1, 5+1, 3+1, 4, 5+1], "D cdf CF bin5")
    DCF[5] = do_cdf_bin([1, 4+1, 3, 1, 2+1], "D cdf CF bin6")
    DCF[6] = do_cdf_bin([1, 1, 0+1, 1, 0], "D cdf CF bin7")
    DCF[7] = do_cdf_bin([1, 1, 0, 1, 1], "D cdf CF bin8")
    

for i in range(8):
    dcBkgCDF["bkg CDF CC B" + str(i+1)] = csm_template(1)
    dcBkgCDF["bkg CDF CC B" + str(i+1) + "no_syst"] = csm_template(0)
    dcBkgCDF["bkg CDF CF B" + str(i+1)] = csm_template(1)
    dcBkgCDF["bkg CDF CF B" + str(i+1) + "no_syst"] = csm_template(0)
#test_bccb1  = csm_template(1)
#test_bccb1.set_np("bkg level cdf cc b1",-0.62/8.02, 0.62/8.02, NULL,1, NULL,-1)
#test_bccb1.make(BCC[0],1.,0,0,"CDF CC B1")
corr_f = sqrt(7.5/10)
dcBkgCDF["bkg CDF CC B1"].set_np("bkg level cdf cc b1",-0.62/8.02*corr_f, 0.62/8.02*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CC B2"].set_np("bkg level cdf cc b2",-0.64/8.43*corr_f, 0.64/8.43*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CC B3"].set_np("bkg level cdf cc b3",-0.39/3.55*corr_f, 0.39/3.55*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CC B4"].set_np("bkg level cdf cc b4",-0.39/3.51*corr_f, 0.39/3.51*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CC B5"].set_np("bkg level cdf cc b5",-0.35/2.87*corr_f, 0.35/2.87*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CC B6"].set_np("bkg level cdf cc b6",-0.49/1.62*corr_f, 0.49/1.62*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CC B7"].set_np("bkg level cdf cc b7",-0.27/0.82*corr_f, 0.27/0.82*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CC B8"].set_np("bkg level cdf cc b8",-0.14/0.21*corr_f, 0.14/0.21*corr_f, NULL,1, NULL,-1)


dcBkgCDF["bkg CDF CF B1"].set_np("bkg level cdf cf b1",-0.65/8.49*corr_f, 0.65/8.49*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CF B2"].set_np("bkg level cdf cf b2",-0.69/9.45*corr_f, 0.69/9.45*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CF B3"].set_np("bkg level cdf cf b3",-0.48/4.91*corr_f, 0.48/4.91*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CF B4"].set_np("bkg level cdf cf b4",-0.42/3.87*corr_f, 0.42/3.87*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CF B5"].set_np("bkg level cdf cf b5",-0.38/3.29*corr_f, 0.38/3.92*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CF B6"].set_np("bkg level cdf cf b6",-0.56/2.38*corr_f, 0.56/2.38*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CF B7"].set_np("bkg level cdf cf b7",-0.24/0.67*corr_f, 0.24/0.67*corr_f, NULL,1, NULL,-1)
dcBkgCDF["bkg CDF CF B8"].set_np("bkg level cdf cf b8",-0.39/0.56*corr_f, 0.39/0.56*corr_f, NULL,1, NULL,-1)
##


for i in range(8):
    dcBkgCDF["bkg CDF CC B" + str(i+1)].make(BCC[i],1.,0,0,"CDF CC B" + str(i+1))
    dcBkgCDF["bkg CDF CC B" + str(i+1) + "no_syst"].make(BCC[i],1.,0,0,"CDF CC B" + str(i+1))
    dcBkgCDF["bkg CDF CF B" + str(i+1)].make(BCF[i],1,0,0,"CDF CF B" + str(i+1))
    dcBkgCDF["bkg CDF CF B" + str(i+1) + "no_syst"].make(BCF[i],1.,0,0,"CDF CF B" + str(i+1))
    

dcCDF = {}

def DoSigModel(BR, dc = dcCDF):
    ns = BR/3.2e-09
    ns = ns *fdfs0/fdfs
    for i in range(8):
        dc[str(BR) + "CDF CC B" + str(i+1)] = csm_template(2) 
        dc[str(BR) + "CDF CC B" + str(i+1) +"no_syst"] = csm_template(0)
        dc[str(BR) + "CDF CC B" + str(i+1)].set_np("fdfs",-1*s_fdfs/fdfs, 1*s_fdfs/fdfs ,NULL,1., NULL, -1.)
        dc[str(BR) + "CDF CC B" + str(i+1)].set_np("CDF ERR 1",-0.14, 0.14 ,NULL,1., NULL, -1.)
        dc[str(BR) + "CDF CC B" + str(i+1)].make(SCC[i], ns, 0, 1, "CDF CC B"+str(i+1))
        dc[str(BR) + "CDF CC B" + str(i+1) +"no_syst"].make(SCC[i], ns, 0, 1, "CDF CC B"+str(i+1))

        dc[str(BR) + "CDF CF B" + str(i+1)] = csm_template(2) 
        dc[str(BR) + "CDF CF B" + str(i+1) +"no_syst"] = csm_template(0)
        dc[str(BR) + "CDF CF B" + str(i+1)].set_np("fdfs",-1*s_fdfs/fdfs, 1*s_fdfs/fdfs ,NULL,1., NULL, -1.)
        dc[str(BR) + "CDF CF B" + str(i+1)].set_np("CDF ERR 2",-0.14, 0.14 ,NULL,1., NULL, -1.)
        dc[str(BR) + "CDF CF B" + str(i+1)].make(SCF[i], ns, 0, 1, "CDF CF B"+str(i+1))
        dc[str(BR) + "CDF CF B" + str(i+1) +"no_syst"].make(SCF[i], ns, 0, 1, "CDF CF B"+str(i+1))
    
    return dc

tests, testpes = {}, {}
  
nulpe = csm_model()     #### This must contain ALL syst
nul = csm_model()

for i in range(8):
    dcBkgCDF["bkg CDF CC B" + str(i+1)].add_to(nulpe)
    dcBkgCDF["bkg CDF CF B" + str(i+1)].add_to(nulpe)
    dcBkgCDF["bkg CDF CC B" + str(i+1) +"no_syst"].add_to(nul)
    dcBkgCDF["bkg CDF CF B" + str(i+1) +"no_syst"].add_to(nul)
print "here A"

def DoTestHyp(BR):
   

    DoSigModel(BR)
   

    test = csm_model()
    testpe = csm_model()

    for i in range(8):
        dcBkgCDF["bkg CDF CC B" + str(i+1)].add_to(testpe)
        dcBkgCDF["bkg CDF CF B" + str(i+1)].add_to(testpe)
        dcBkgCDF["bkg CDF CC B" + str(i+1) +"no_syst"].add_to(test)
        dcBkgCDF["bkg CDF CF B" + str(i+1) +"no_syst"].add_to(test)
        
        dcCDF[str(BR) + "CDF CC B" + str(i+1)].add_to(testpe)
        dcCDF[str(BR) + "CDF CF B" + str(i+1)].add_to(testpe)
        dcCDF[str(BR) + "CDF CC B" + str(i+1) +"no_syst"].add_to(test)
        dcCDF[str(BR) + "CDF CF B" + str(i+1) +"no_syst"].add_to(test)
    
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
    for i in range(8):
        CL.set_datahist(DCC[i], "CDF CC B" + str(i+1))
        CL.set_datahist(DCF[i], "CDF CF B" + str(i+1))
 
    if npe: CL.set_npe(npe)
    
    return CL




def do_scan(filename, stop_95 = False):
    tup = XTuple(filename, labels = ["BR/F", "CLs/F","CLb/F", "CLsb/F"])
   
    c90, c95 = 0.,0
    for j in range(25,45):
        i = 1*j
        CL = DoCL(i*1e-09,10000, syst=1)
        print "CL done"
        CL.run_pseudoexperiments()
        cl = CL.cls()
        clb = CL.clb()
        clsb = CL.clsb()
        print i,cl, clb, clsb
        tup.fillItem("BR", i)
        tup.fillItem("CLs",cl)
        tup.fillItem("CLb",clb)
        tup.fillItem("CLsb",clsb)
        tup.fill()
        if cl < 0.1 and not c90: c90 = i
        if cl<0.05:
            print "C90:",c90
            print "c95:",i
            if stop_95:
                tup.close()
                return c90, i
    tup.close()

#do_scan("CDF")#, stop_95 = True)
