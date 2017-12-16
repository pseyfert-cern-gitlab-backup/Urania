#! /usr/bin/env python

alpha_2011 = 2.92e-9
s_alpha_2011 = 0.41e-9


# CHANGE THIS!
alpha_2012 = 2.92e-9
s_alpha_2012 = 0.41e-9


CHANNEL = "Tau -> 3 mu"
use_2011_tau23mu =1
use_2012_tau23mu =0


from ROOT import *
from MCLimit import *
import sys
from XTuple import *
from SomeUtils.alyabar import *

addSM_toBkg = 0
SYST = 0
ISTYLE = 1 # VERTICAL EXT=3, VERTICAL ONLY = 1 , HORIZONTAL = DEFAULT = 0

print "Using Tau23Mu 2011:", use_2011_tau23mu
print "Using Tau23Mu 2012:", use_2012_tau23mu

#######################
## Null hypothesis   ##
#######################

nul = csm_model()
nul_no_syst = csm_model()


if use_2011_tau23mu:
    unbfile_2011 = "../../params/3fb/2011_PDF_BCK/bck_eta_cut450.root"
    sigfile_2011="../../params/3fb/preliminary_2011_notrash.root"
    bkgfile_2011="../../params/3fb/2011_PDF_BCK/bck_eta_cut450.root"
    f_bkg_2011=TFile(bkgfile_2011)

       
    bkgpdf_2011 = f_bkg_2011.Get("expected_exp")
    bkgpdf_2011.SetTitle("bkg pdf")
    
    #unbTfile_2011 = TFile(unbfile_2011)
    #unbhist_2011 = unbTfile_2011.Get("expected_exp")
    
    


    
    numberBkg_2011=bkgpdf_2011.GetSum()
    print "bkgpdf.GetSum(): ",bkgpdf_2011.GetSum()
    bkgpdfsum_2011 = bkgpdf_2011.GetSum()
    
    bkgpdf_2011.Scale(1./bkgpdf_2011.GetSum())
    print "normalized bkgpdf_2011.GetSum(): ",bkgpdf_2011.GetSum()
    
    
    f_sig_2011 = TFile(sigfile_2011)
    sigpdf_2011 = f_sig_2011.Get("skimmed")#central")
    ## Normalize (I always use normalized pdf's, a
    sigpdf_2011.Scale(1./sigpdf_2011.GetSum())
    sigpdfsum_2011 = sigpdf_2011.GetSum()
    alpha_2011=alpha_2011/sigpdfsum_2011


    print "set bkg model"
    bkg_no_syst_2011 = csm_template(0)
    bkg_2011 = csm_template(0)
    bkg_2011.make(bkgpdf_2011,numberBkg_2011 ,0,0, "2011")
    bkg_no_syst_2011.make(bkgpdf_2011,numberBkg_2011 ,0,0, "2011")
    bkg_2011.add_to(nul) 
    bkg_no_syst_2011.add_to(nul_no_syst) 
    #nul.set_interpolation_style("2011",ISTYLE)
    #nul_no_syst.set_interpolation_style("2011",ISTYLE)
    #unbTfile_2011=do2012BkgToyMC()
    print "DOING A TOY DATA"
    from scipy import random as rnd
    toyMC = bkgpdf_2011.Clone()
    toyMC.Scale(100)
    toyMC.SetName("aaaa")
    
    ###### fluctuate
    for i in range(toyMC.GetNbinsX()):
        for j in range(toyMC.GetNbinsY()):
            toyMC.SetBinContent(i+1,j+1, rnd.poisson(toyMC.GetBinContent(i+1,j+1)))
            
    unbhist_2011=toyMC        


if use_2012_tau23mu:
    unbfile_2012 = "../../params/3fb/bck_eta_cut450_2012.root"
    sigfile_2012="../../params/3fb/preliminary_2012_notrash.root"
    bkgfile_2012="../../params/3fb/2012_PDF_BCK/bck_eta_cut450_2012.root"
    f_bkg_2012=TFile(bkgfile_2012)
    
    bkgpdf_2012 = f_bkg_2012.Get("expected_exp")
    bkgpdf_2012.SetTitle("bkg pdf")
    
    unbTfile_2012 = TFile(unbfile_2012)
    unbhist_2012 = unbTfile_2012.Get("expected_exp")
    numberBkg_2012=bkgpdf_2012.GetSum()
    print "bkgpdf.GetSum(): ",bkgpdf_2012.GetSum()
    bkgpdfsum_2012 = bkgpdf_2012.GetSum()
    
    bkgpdf_2012.Scale(1./bkgpdf_2012.GetSum())
    print "normalized bkgpdf_2012.GetSum(): ",bkgpdf_2012.GetSum()
    
    
    f_sig_2012 = TFile(sigfile_2012)
    sigpdf_2012 = f_sig_2012.Get("private")#central")
    ## Normalize (I always use normalized pdf's, a
    sigpdf_2012.Scale(1./sigpdf_2012.GetSum())
    sigpdfsum_2012 = sigpdf_2012.GetSum()
    alpha_2012=alpha_2012/sigpdfsum_2012


    print "set bkg model"
    bkg_no_syst_2012 = csm_template(0)
    bkg_2012 = csm_template(0)
    bkg_2012.make(bkgpdf_2012,numberBkg_2012 ,0,0, "2012")
    bkg_no_syst_2012.make(bkgpdf_2012,numberBkg_2012 ,0,0, "2012")
    bkg_no_syst_2012.add_to(nul) 
    bkg_no_syst_2012.add_to(nul_no_syst) 
    #nul.set_interpolation_style("2012",ISTYLE)
    #nul_no_syst.set_interpolation_style("2012",ISTYLE)


######################################################
#bkg.add_to(nul)
#bkg_no_syst.add_to(nul_no_syst)


####################

c1 = TCanvas()
c2 = TCanvas()
c3 = TCanvas()
#
#gStyle.SetPaintTextFormat("5.1f")
bkgpdf_2011.Draw("TEXTBOX")
#c1.cd()
sigpdf_2011.Draw("TEXTBOX")



#bkg.add_to(nul)
#bkg_no_syst.add_to(nul_no_syst)   



                
    
   # nulpe.set_interpolation_style("2012",ISTYLE)


################################
## Test Hypothesis function  ###
################################

def DoTestHyp(BR):
   
    test = csm_model()
    test_no_syst = csm_model()

    returnparameters = []

    if use_2011_tau23mu:
      bkg_2011.add_to(test)
      bkg_no_syst_2011.add_to(test_no_syst)
 
      dc_2011 = csm_template(0)
      dc_no_syst_2011 = csm_template(0)
      dc_2011.make(sigpdf_2011, BR/alpha_2011 ,0,1, "2011")
      dc_no_syst_2011.make(sigpdf_2011, BR/alpha_2011 ,0,1, "2011")
      dc_2011.add_to(test)
      dc_no_syst_2011.add_to(test_no_syst)
       
      #test.set_interpolation_style("2011",ISTYLE)
      #test_no_syst.set_interpolation_style("2011",ISTYLE)
      returnparameters += [dc_2011,dc_no_syst_2011]


    if use_2012_tau23mu:
      bkg_2012.add_to(test)
      bkg_no_syst_2012.add_to(test_no_syst)

      dc_2012 = csm_template(0)
      dc_no_syst_2012 = csm_template(0)
      dc_2012.make(sigpdf_2012,BR/alpha_2012,0,1, "2012")
      dc_no_syst_2012.make(sigpdf_2012,BR/alpha_2012,0,1, "2012")
      dc_2012.add_to(test)
      dc_no_syst_2012.add_to(test_no_syst)
    
      #test.set_interpolation_style("2012",ISTYLE)
      #test_no_syst.set_interpolation_style("2012",ISTYLE)
      returnparameters += [dc_2012,dc_no_syst_2012]
    

    
    CL = mclimit_csm()
    CL.set_null_hypothesis(nul_no_syst)
    CL.set_test_hypothesis(test_no_syst)
    
    CL.set_null_hypothesis_pe(nul)
    CL.set_test_hypothesis_pe(test)

    if use_2011_tau23mu:
      CL.set_datahist(unbhist_2011, "2011")
    if use_2012_tau23mu:
      CL.set_datahist(unbhist_2012, "2012")
        
    CL.run_pseudoexperiments()
    cls = CL.cls()
    clb = CL.clb()
    clsb = CL.clsb()
    CL.set_npe(100000)

    return CL,  test, test_no_syst, returnparameters
##########################################
##   Confidendce level calculator    #####
##########################################

tests, testpes = {}, {}

def do2011BkgToyMC(fluctuated = 1, ext_name = "2012", addbr = 0):
    print "DOING A TOY DATA 2011"

    from scipy import random as rnd
    toyMC = bkgpdf.Clone()
    toyMC.Scale(numberBkg_2011)
    
    return toyMC    

def do2012BkgToyMC(fluctuated = 1, ext_name = "2012", addbr = 0):
        print "DOING A TOY DATA"
        from scipy import random as rnd
        toyMC = bkgpdf_2011.Clone()
        toyMC.Scale(100)
        toyMC.SetName("aaaa")
        
        ###### fluctuate
        for i in range(toyMC.GetNbinsX()):
            for j in range(toyMC.GetNbinsY()):
                toyMC.SetBinContent(i+1,j+1, rnd.poisson(toyMC.GetBinContent(i+1,j+1)))
        return toyMC
                    
####################################
## TOY  random Data for 2012  ######
####################################

#a2012.DataHist = do2012BkgToyMC(addbr = float(sys.argv[1:][0]))

#########################################
#'''
#def DoCL(BR, npe =0, syst = 0 ):
#    testpes[BR], tests[BR] = DoTestHyp(BR)
#  
#    CL = mclimit_csm()
#    CL.set_null_hypothesis(nul)
#    CL.set_test_hypothesis(tests[BR])
#
#    
#    if use_tau23mu_2011: CL.set_datahist(utum.DataHist, "2012autum")
#    
#    if npe: CL.set_npe(npe)
#    
#    return CL
#'''

##################333
## SCAN
####################
import sys
st0 = float(sys.argv[1])

def do_scan(filename, stop_95 = False):
    tup = XTuple(filename, labels = ["BR/F","ts/F", "chi2/F", "CLs/F","CLb/F", "CLsb/F","CLs_exp_b_med/F" , "CLs_exp_b_p1/F", "CLs_exp_b_p2/F","CLs_exp_b_m1/F" ,"CLs_exp_b_m2/F","CLb_exp_s_med/F" , "CLb_exp_s_p1/F", "CLb_exp_s_p2/F","CLb_exp_s_m1/F" ,"CLb_exp_s_m2/F"])
   
    print CHANNEL
    c90, c95 = 0.,0
    print filename
    for j in [3.5e-8]:
        
        i =  j
        print "ps for BR:", i
        CL,a,b,c = DoTestHyp(i)# ,1000000, syst=SYST)
        print "got CL"
        #CL.setpxprintflag(1)
        cl = CL.cls()
        clb = CL.clb()
        clsb = CL.clsb()
        print i,cl, clb, clsb
        tup.fillItem("BR", i)
        tup.fillItem("ts", CL.ts())
        #tup.fillItem("chi2", CL.calc_chi2(testpes[i*1e-9],a2012.DataHist))
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
        tup.close()
        #if cl < 0.1 and not c90: c90 = i
        #if cl<0.05:
        #    print "C90:",c90
        #    print "c95:",i
        #    if stop_95:
        #        tup.close()
        #        return c90, i
    #tup.close()
    print "Done? ", filename

do_scan("dupa")


