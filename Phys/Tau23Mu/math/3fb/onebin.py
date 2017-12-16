#! /usr/bin/env python
import sys
if (len(sys.argv)<4) :
  print "USAGE"
  print "for example run in a loop"
  print 'for h in {1..30} ; do for a in "" "a" ; do for b in "" "b" ; do for c in "" "c" ; do python combinelimits_2012_tau23mu.py "$a" "$b" "$c" $h > file$a.$b.$c.log & done & done & done & done'
  print "the first argument, cast to bool, determines whether 2011 is used"
  print "the second argument, cast to bool, determines whether 2012 is used"
  print "the third argument, cast to bool, determines whether basem's fits are used"
  print "the fourth argument, cast to int, determines the branching fraction hypothesis to be tested"
  print "the fifth argument specifies which bin is used"
  sys.exit()
  
                 
def onebin(hist,binnumber,doscale):
   retval = TH2F(hist.GetName()+"one",hist.GetTitle()+"one",1,0.,1.,hist.GetNbinsY(),hist.GetYaxis().GetBinLowEdge(1),hist.GetYaxis().GetBinUpEdge(int(hist.GetNbinsY())))
   for y in range(hist.GetNbinsY()):
     targetbin = retval.GetBin(1,y+1)
     sourcebin = hist.GetBin(int(binnumber),y+1)
     bincontent = hist.GetBinContent(sourcebin)
     retval.SetBinContent(targetbin,bincontent)
   scale = retval.GetSum()
   if doscale:
      retval.Scale(1./retval.GetSum())
   return retval,scale


alpha_2011 = 4.05e-9  # jon's alpha w/ mass, w/o trash
s_alpha_2011 = 0.48e-9

onlyonebin = None
if (len(sys.argv)>5):
  onlyonebin = int(sys.argv[5])
print "only one bin", onlyonebin

alpha_2011 = alpha_2011 * 9.607e-01 # improve by my ctau to avoid double accounting
s_alpha_2011 = s_alpha_2011 * 9.607e-01 # improve by my ctau to avoid double accounting

print " AT THE MOMENT NOT FOR 2012 !!!!!!!!!"



alpha_2012 = alpha_2012 * 9.607e-01 # improve by my ctau to avoid double accounting
s_alpha_2012 = s_alpha_2012 * 9.607e-01 # improve by my ctau to avoid double accounting



#operator = "VLLRRRAD_"
operator = sys.argv[4]
polarity = "down" #"up","down"

NTOYS = 100000




CHANNEL = "Tau -> 3 mu"
print "aruments", sys.argv[1], sys.argv[2], sys.argv[3] 
use_2011_tau23mu = bool(sys.argv[1])
use_2012_tau23mu = bool(sys.argv[2])
basem = bool(sys.argv[3])
# THIS WE WILL USE FOR full statistics runs 
if (len(sys.argv)==5):
  external_BR=int(sys.argv[4])
else:
  external_BR=None
print "external_BR: ", external_BR
# does this passing even work?


addSM_toBkg = 0
SYST = 0
ISTYLE = 1 # VERTICAL EXT=3, VERTICAL ONLY = 1 , HORIZONTAL = DEFAULT = 0

outname = "toy_"
if basem:
  outname += "Basem"
else:
  outname += "Marcin"

if use_2011_tau23mu:
  outname += "_2011"
if use_2012_tau23mu:
  outname += "_2012"
if external_BR is not None:
  outname += "_" + str(external_BR)
if onlyonebin is not None:
  outname += "_bin" + str(onlyonebin)


if not (use_2011_tau23mu or use_2012_tau23mu):
  print "no year chosen"
  sys.exit()

print outname

print "Using Tau23Mu 2011:", use_2011_tau23mu
print "Using Tau23Mu 2012:", use_2012_tau23mu

from ROOT import *
from MCLimit import *
import sys
from XTuple import *
from SomeUtils.alyabar import *


#######################
## Null hypothesis   ##
#######################

nul = csm_model()
nul_no_syst = csm_model()

def intefy(hist, norm):
  from scipy import random as rnd
  rethist = hist.Clone(hist.GetName()+"_random")
  rethist.Reset()
  for x in range(hist.GetNbinsX()):
    for y in range(hist.GetNbinsX()):
      bin = rethist.GetBin(x+1,y+1)
      rethist.SetBinContent(bin,float(int(norm * rnd.poisson(hist.GetBinContent(bin)))))
  return rethist


if use_2011_tau23mu:

    if basem:
      bkgfile_2011="../../params/3fb/background_2011_notrash.root"
      f_bkg_2011=TFile(bkgfile_2011)
      bkgpdf_2011 = f_bkg_2011.Get("expected").Clone("bkg_2011")
    else:
      bkgfile_2011="../../params/3fb/2011_PDF_BCK_FINAL/bck_eta_cut450_notrash.root"
      f_bkg_2011=TFile(bkgfile_2011)
      bkgpdf_2011 = f_bkg_2011.Get("expected_exp").Clone("bkg_2011")

    if onlyonebin is not None:
      bkgpdf_2011,factor = onebin(bkgpdf_2011,onlyonebin,False)


    numberBkg_2011 = bkgpdf_2011.GetSum()
    # bkgpdfsum_2011 = bkgpdf_2011.GetSum()
    bkgpdf_2011.Scale(1./bkgpdf_2011.GetSum())
    #FUCK DON"T YOU DARE USE THIS! 
    #unbfile_2011="../../params/3fb/background_2011_notrash.root"
    #unbTfile_2011 = TFile(unbfile_2011)
    #unbhist_2011 = unbTfile_2011.Get("skimmed").Clone("data_2011")
    #unbhist_2011 = intefy(bkgpdf_2011,numberBkg_2011)
    #sigfile_2011 = "../../params/3fb/preliminary_2011_notrash.root"
    sigfile_2011="../../params/3fb/base_2011_calibV4_"+polarity+operator+"_trash.root"
    f_sig_2011 = TFile(sigfile_2011)
    sigpdf_2011 = f_sig_2011.Get("central").Clone("sig_2011")
    sigpdfsum_2011 = sigpdf_2011.GetSum()
    # now in alpha
    alpha_2011=alpha_2011/sigpdfsum_2011
    s_alpha_2011=s_alpha_2011/sigpdfsum_2011
    sigpdf_2011.Scale(1./sigpdf_2011.GetSum())
    if onlyonebin is not None:
      sigpdf_2011,factor = onebin(sigpdf_2011,onlyonebin,True)
      alpha_2011=alpha_2011/factor


    print "Making toys for Cls, aka making dummy unblided file"
    from scipy import random as rnd
    toyMC_2011 = bkgpdf_2011.Clone()
    toyMC_2011.Scale(numberBkg_2011)
    toyMC_2011.SetName("DUMMY OBSERVED")
    for i in range(toyMC_2011.GetNbinsX()):
      for j in range(toyMC_2011.GetNbinsY()):
                    toyMC_2011.SetBinContent(i+1,j+1, rnd.poisson(toyMC_2011.GetBinContent(i+1,j+1)))

    unbhist_2011=toyMC_2011
    print "normalized bkgpdf_2011.GetSum(): ",bkgpdf_2011.GetSum()
    

    print "set bkg model"

    bkg_2011 = csm_template(0)
    bkg_2011.make(bkgpdf_2011,numberBkg_2011 ,0,0, "2011")
    bkg_2011.add_to(nul) 
    nul.set_interpolation_style("2011",ISTYLE)
     
    bkg_no_syst_2011 = csm_template(0)
    bkg_no_syst_2011.make(bkgpdf_2011,numberBkg_2011 ,0,0, "2011")
    bkg_no_syst_2011.add_to(nul_no_syst) 
    nul_no_syst.set_interpolation_style("2011",ISTYLE)
    


if use_2012_tau23mu:
    if basem:
       bkgfile_2012="../../params/3fb/background_2012_notrash.root"
       f_bkg_2012=TFile(bkgfile_2012)
       bkgpdf_2012 = f_bkg_2012.Get("expected").Clone("bkg_2012")
    else:
       bkgfile_2012="../../params/3fb/2012_PDF_BCK_FINAL/bck_eta_cut450_notrash.root"
       f_bkg_2012=TFile(bkgfile_2012)
       bkgpdf_2012 = f_bkg_2012.Get("expected_exp").Clone("bkg_2012")

    if onlyonebin is not None:
      bkgpdf_2012,factor = onebin(bkgpdf_2012,onlyonebin,False)

    numberBkg_2012=bkgpdf_2012.GetSum()
    # bkgpdfsum_2012 = bkgpdf_2012.GetSum()
    bkgpdf_2012.Scale(1./bkgpdf_2012.GetSum())
    ###unbfile_2012 = "../../params/3fb/background_2012_notrash.root"
    ###unbTfile_2012 = TFile(unbfile_2012)
    ###unbhist_2012 = unbTfile_2012.Get("expected").Clone("data_2012")
    ###unbhist_2012 = intefy(bkgpdf_2012,numberBkg_2012)
    sigfile_2012="../../params/3fb/base_2012_calibV4_"+polarity+operator+"_trash.root"
    f_sig_2012 = TFile(sigfile_2012)
    sigpdf_2012 = f_sig_2012.Get("central").Clone("sig_2012")
    sigpdfsum_2012 = sigpdf_2012.GetSum()
    alpha_2012=alpha_2012/sigpdfsum_2012
    s_alpha_2012=s_alpha_2012/sigpdfsum_2012
    sigpdf_2012.Scale(1./sigpdf_2012.GetSum())
    if onlyonebin is not None:
      sigpdf_2012,factor = onebin(sigpdf_2012,onlyonebin,True)
      alpha_2012=alpha_2012/factor

    
    print "Making toys for Cls, aka making dummy unblided file"
    from scipy import random as rnd
    toyMC_2012 = bkgpdf_2012.Clone()
    toyMC_2012.Scale(numberBkg_2012)
    toyMC_2012.SetName("DUMMY OBSERVED 2012")
    for i in range(toyMC_2012.GetNbinsX()):
      for j in range(toyMC_2012.GetNbinsY()):
        toyMC_2012.SetBinContent(i+1,j+1, rnd.poisson(toyMC_2012.GetBinContent(i+1,j+1)))
        
    unbhist_2012=toyMC_2012

    bkg_2012 = csm_template(0)
    bkg_2012.make(bkgpdf_2012,numberBkg_2012 ,0,0, "2012")
    bkg_2012.add_to(nul) 
    nul.set_interpolation_style("2012",ISTYLE)
    
    bkg_no_syst_2012 = csm_template(0)
    bkg_no_syst_2012.make(bkgpdf_2012,numberBkg_2012 ,0,0, "2012")
    bkg_no_syst_2012.add_to(nul_no_syst) 
    nul_no_syst.set_interpolation_style("2012",ISTYLE)
   
######################################################
#bkg.add_to(nul)
#bkg_no_syst.add_to(nul_no_syst)


####################

#c1 = TCanvas()
#c2 = TCanvas()
#c3 = TCanvas()
#
#gStyle.SetPaintTextFormat("5.1f")
##bkgpdf.Draw("TEXTBOX")
#c1.cd()
#sigpdf.Draw("TEXTBOX")



#bkg.add_to(nul)
#bkg_no_syst.add_to(nul_no_syst)   



                
    
   # nulpe.set_interpolation_style("2012",ISTYLE)


################################
## Test Hypothesis function  ###
################################

def DoTestHyp(internal_BR):
   
    test = csm_model()
    test_no_syst = csm_model()

    returnparameters = []

    if use_2011_tau23mu:
      bkg_2011.add_to(test)
      bkg_no_syst_2011.add_to(test_no_syst)
 
      dc_2011 = csm_template(0)
      dc_no_syst_2011 = csm_template(0)
      dc_2011.make(sigpdf_2011,internal_BR/alpha_2011,0,1, "2011")
      dc_no_syst_2011.make(sigpdf_2011,internal_BR/alpha_2011,0,1, "2011")
      dc_2011.add_to(test)
      dc_no_syst_2011.add_to(test_no_syst)
       
      test.set_interpolation_style("2011",ISTYLE)
      test_no_syst.set_interpolation_style("2011",ISTYLE)
      returnparameters += [dc_2011,dc_no_syst_2011]


    if use_2012_tau23mu:
      bkg_2012.add_to(test)
      bkg_no_syst_2012.add_to(test_no_syst)

      dc_2012 = csm_template(0)
      dc_no_syst_2012 = csm_template(0)
      dc_2012.make(sigpdf_2012,internal_BR/alpha_2012,0,1, "2012")
      dc_no_syst_2012.make(sigpdf_2012,internal_BR/alpha_2012,0,1, "2012")
      dc_2012.add_to(test)
      dc_no_syst_2012.add_to(test_no_syst)
    
      test.set_interpolation_style("2012",ISTYLE)
      test_no_syst.set_interpolation_style("2012",ISTYLE)
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

    CL.set_npe(NTOYS)
    CL.run_pseudoexperiments()
    cls = CL.cls()
    clb = CL.clb()
    clsb = CL.clsb()

    return CL, test, test_no_syst, returnparameters
##########################################
##   Confidendce level calculator    #####
##########################################

tests, testpes = {}, {}

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

def do_scan(filename, stop_95 = False):
    #tup = XTuple(filename, labels = ["BR/F","ts/F", "chi2/F", "CLs/F","CLb/F", "CLsb/F","CLs_exp_b_med/F" , "CLs_exp_b_p1/F", "CLs_exp_b_p2/F","CLs_exp_b_m1/F" ,"CLs_exp_b_m2/F","CLb_exp_s_med/F" , "CLb_exp_s_p1/F", "CLb_exp_s_p2/F","CLb_exp_s_m1/F" ,"CLb_exp_s_m2/F"])
    tup = XTuple(filename, labels = ["BR/F","CLs_exp_b_med/F" ])
   
    print CHANNEL
    c90, c95 = 0.,0
    print filename
    buffer = []
    brloop = []
    if external_BR is None:
      brloop = range(10,23)
      brloop = [20,25,31,37,45,50,60,70,80,90,100,120,140,160,180,200,230,260,300,340,380,430,490,550,600,700,800,900,1000,1200,1400,1600,1900,2300]
      lloop = []
      for br in range(len(brloop)-1):
        lloop += [brloop[br],(brloop[br]+brloop[br+1])/2]
      brloop = lloop 
    else:
      brloop = [external_BR]
    for j in brloop:
        
        i =  0.5e-8 * float(j)
        print "ps for BR:", i
        CL,a,b,c = DoTestHyp(i)# ,1000000, syst=SYST)
        buffer += [a,b,c]
        print "got CL"
        #CL.setpxprintflag(1)
        cl = CL.cls()
        clb = CL.clb()
        clsb = CL.clsb()
        tup.fillItem("BR", i)
        #tup.fillItem("ts", CL.ts())
        #tup.fillItem("chi2", CL.calc_chi2(testpes[i*1e-9],a2012.DataHist))
        #tup.fillItem("CLs",cl)
        #tup.fillItem("CLb",clb)
        #tup.fillItem("CLsb",clsb)
        tup.fillItem("CLs_exp_b_med",CL.clsexpbmed())
        #tup.fillItem("CLs_exp_b_p1",CL.clsexpbp1())
        #tup.fillItem("CLs_exp_b_p2",CL.clsexpbp2())
        #tup.fillItem("CLs_exp_b_m1",CL.clsexpbm1())
        #tup.fillItem("CLs_exp_b_m2",CL.clsexpbm2())

        #tup.fillItem("CLb_exp_s_med",CL.clbexpsmed())
        #tup.fillItem("CLb_exp_s_p1",CL.clbexpsp1())
        #tup.fillItem("CLb_exp_s_p2",CL.clbexpsp2())
        #tup.fillItem("CLb_exp_s_m1",CL.clbexpsm1())
        #tup.fillItem("CLb_exp_s_m2",CL.clbexpsm2())
        
        print i,cl, clb, clsb, CL.clsexpbmed()
        tup.fill()
        #if cl < 0.1 and not c90: c90 = i
        #if cl<0.05:
        #    print "C90:",c90
        #    print "c95:",i
        #    if stop_95:
        #        tup.close()
        #        return c90, i
    tup.close()
    print "Done? ", filename

do_scan(outname)


