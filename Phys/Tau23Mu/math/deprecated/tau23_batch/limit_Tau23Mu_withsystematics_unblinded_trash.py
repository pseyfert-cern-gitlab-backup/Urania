#! /usr/bin/env python

alpha = 2.515e-9
NTOYS = 500000
#systematics for which background bins
bkgpar=range(1,26) #[10,15,19,22,20,25,23,24] #20,25 missing

#switches for signal systematics
use_s_alpha = True
use_s_pdf = True


from ROOT import *
from MCLimit import *
import sys

if (len(sys.argv)!=2) :
    print "Usage python " + argv[0] + " <gridpoint>"
    print "where <gridpoint> is the number of the gridpoint which you want to process"
    print "branching ratio = 1e-8 + <gridpoint> * 0.01e-8"

##outfilename="vetos_mod"+str(sys.argv[1])
##unbfile = "../params/v5_unblinded_vetos_mod.root"
##sigfile="../params/v5_sigPDF_withetaveto.root"
##bkgfile="../params/v5_bck_vetos.root"
##alpha = alpha/0.71325581

outfilename="twopdf_alpha_sig_chbkg_smallstat"+str(sys.argv[1])
unbfile = "../../params/v5_unblinded.root"
bkgfile="../../params/v5_eta_bck_good_errors.root"
sigfile="../../params/v5_sigPDF.root"

##outfilename="twopdf_newerr_mod"+str(sys.argv[1])
##unbfile = "../params/v5_unblinded.root"
##bkgfile="../params/v5_eta_bck.root"
##sigfile="../params/v5_sigPDF_mod.root"
##alpha = alpha/0.8776


##outfilename="test_"+str(sys.argv[1])
##unbfile = "../params/v5_unblinded.root"
##bkgfile="../params/v5_bck_noetapdf_no_vetos.root"
##sigfile="../params/v5_sigPDF.root"
##


ISTYLE = 1  
s_alpha = 0.324e-9#*alpha#guesstimate


######  bkg pdf (TH1D or TH2D)
#  Asmue flat in mass, 4 bins between -30 and 30 around tau mass
#  Content per BDT bin (mass integrated): 40, 8.3, 2.6  (invented numbers. Just took the sidebands and divide by 10)
######################################################################################################################

######  bkg pdf (TH1D or TH2D)
#  Asmue flat in mass, 6 bins between -15 and 15 around tau mass
#  BDT, mass integrated, 5 bins, content: 420, 72,24,12,6 guesstimate from 78pb 
######################################################################################################################



#bkgpdf = TH2D("bkgPdf", "bkg pdf", 10, 0,1, 6, -30,30)
#bkgpdf_u = TH2D("bkgPdf_u", "bkg pdf upper", 10, 0,1, 6, -30,30)
#bkgpdf_d = TH2D("bkgPdf_d", "bkg pdf lower", 10, 0,1, 6, -30,30)

f_bkg = TFile(bkgfile)
#f_bkg = TFile("../params/v5_eta_bck_good_errors.root")
#f_bkg = TFile("../params/v5_eta_bck_good_errors.root")


#print "iuse bkg file $TAU23MUROOT/params/v4_bkg_geo7pid5_comb.root"
bkgpdf = f_bkg.Get("expected_exp")
bkgpdf.SetTitle("bkg pdf")
bkgpdf_u = f_bkg.Get("expected_plus")
bkgpdf_u.SetTitle("bkg pdf plus errors")
bkgpdf_d = f_bkg.Get("expected_minus")
bkgpdf_d.SetTitle("bkg pdf minus errors")


unbTfile = TFile(unbfile)
unbhist = unbTfile.Get("observed")

#for i in range(bkgpdf_d.GetNbinsX()):
#        for j in range(bkgpdf_d.GetNbinsY()):
            #if bkgpdf_d.GetBinContent(i+1,j+1)<0.001:
#                print "bin cont: ",bkgpdf_d.GetBinContent(i+1,j+1 )
#                bkgpdf_d.SetBinContent(i+1,j+1, 0 )


## c1 = TCanvas()
## c1.Divide(2,2)
## c1.cd(1)
## bkgpdf.Draw("TEXTBOX")
## c1.cd(2)
## bkgpdf_u.Draw("TEXTBOX")
## c1.cd(3)
## bkgpdf_d.Draw("TEXTBOX")

#number of bkg events
numberBkg=bkgpdf.GetSum()

## Normalize
print "bkgpdf.GetSum(): ",bkgpdf.GetSum()
bkgpdfsum = bkgpdf.GetSum()
bkgpdfsum_u = bkgpdf_u.GetSum()
bkgpdfsum_d = bkgpdf_d.GetSum()
bkgpdf.Scale(1./bkgpdf.GetSum())
bkgpdf_u.Scale(1./bkgpdf_u.GetSum())
bkgpdf_d.Scale(1./bkgpdf_d.GetSum())
print "normalized bkgpdf.GetSum(): ",bkgpdf.GetSum()
### Some systematics, let's assume all bins well known, but bin 3, which has 25% error.
## Make the corresponding pdf's to +- X sigmas (X ~ 2,3 if possible)


#print "sclae of u, d",bkgpdf_u.GetSum(), " , ",bkgpdf_d.GetSum()
#bkgpdf_u.Scale(1./bkgpdf_u.GetSum())
#bkgpdf_d.Scale(1./bkgpdf_d.GetSum())
#print "sclae of u, d",bkgpdf_u.GetSum(), " , ",bkgpdf_d.GetSum()
######## Signal pdf (TH1D or TH2D)###########################################
## Asumed flat in BDT
## Assume symmetric peak, content made up from Ds2PhiPi data peak
##         
#############################################################################


#f_sig=TFile("~albrecht/public/forDiego/v0.2_sigPDF.root")
#f_sig = TFile("$TAU23MUROOT/params/v4_sigPDF.root")
#f_sig = TFile("$TAU23MUROOT/params/v4.1_sigPDF.root")
f_sig = TFile(sigfile)
#f_sig = TFile("/afs/cern.ch/user/m/mchrzasz/cmtuser/Bender_v19r1/Phys/Tau23Mu/params/test2_sigPDF.root")
#f_sig = TFile("/afs/cern.ch/user/m/mchrzasz/cmtuser/Bender_v19r1/Phys/Tau23Mu/params/test3_sigPDF.root")
#f_sig = TFile("/afs/cern.ch/user/m/mchrzasz/cmtuser/Bender_v19r1/Phys/Tau23Mu/params/test4_sigPDF.root")

#print "use signal file $TAU23MUROOT/params/v4_sigPDF.root"
sigpdf = f_sig.Get("central")#central")
#print "before scaling signal sum ",sigpdf.GetSum()
## Normalize (I always use normalized pdf's, and then give the expectation as the scale factor)
#alpha = alpha/sigpdf.GetSum()
sigpdfsum = sigpdf.GetSum()
sigpdf.Scale(1./sigpdf.GetSum())
print "after scaling signal sum ",sigpdf.GetSum()



c1 = TCanvas()
c2 = TCanvas()
c3 = TCanvas()


#c.cd(1)
#print "draw bkg & sig"
gStyle.SetPaintTextFormat("5.1f")
#bkgpdf.Draw("TEXTBOX")
c1.cd()
sigpdf.Draw("TEXTBOX")

## Assume signal pdf perfectly well calibrated

### Set the bkg model
print "set bkg model"
bkg_no_syst = csm_template(0)   ### No systematics (used for the test statistic)

#bkg.set_np("error pdf bin 3", 0, 0, bkgpdf_u, 3., bkgpdf_d,-3.)    ### Works as follows:  Normalization impact at +-1 sigma, pdf impact at _X_ sigma, where X is specified (here 3 and -3)
#### 25 like this### 


bkg = csm_template(len(bkgpar))   ### 2 systematics 
#bkg = csm_template(1+len(bkgpar))   ### 2 systematics 
#bkg.set_np("error pdf bin 3", (bkgpdfsum_u-bkgpdfsum)/1./bkgpdfsum, (bkgpdfsum_u-bkgpdfsum)/1./bkgpdfsum, bkgpdf_u, 1., bkgpdf_d,-1.)    ### Works as follows:  Normalization impact at +-1 sigma, pdf impact at _X_ sigma, where X is specified (here 3 and -3)
npb_plist = []
npb_mlist = []
ffblist = []
bevup = []
bevdown = []

print "before loop" 
       
           

for jj in range(25):
    ii = jj
    f_now = TFile("../../params/v5_systematics_bkg"+str(jj+1)+".root")
    pl = f_now.Get("expected_plus")
    mi = f_now.Get("expected_minus")
    ffblist+=[f_now]
    npb_plist+=[pl]
    npb_mlist+=[mi]
    bevup+=[(pl.GetSum()-bkgpdfsum)/bkgpdfsum/3]
    bevdown+=[(mi.GetSum()-bkgpdfsum)/bkgpdfsum/3]
   # print "syspdf"+mode+"2/"+mode+"_3sigma"+str(ii)+".root"
           
for ii in bkgpar:
    print ii
    jj = ii-1
    npb_plist[jj].Scale(1./npb_plist[jj].GetSum())
    npb_mlist[jj].Scale(1./npb_mlist[jj].GetSum())
    bkg.set_np("error pdf bin"+str(jj),bevup[jj],bevdown[jj],npb_plist[jj],9.,npb_mlist[jj],-9.)




print "here ok?"
#bkg = csm_template(0)   ### 2 systematics 
#bkg = csm_template(1)   ### 2 systematics 
#bkg.set_np("nomlization of sig", s_alpha/alpha, -s_alpha/alpha, NULL,1,NULL,-1)
#bkg.set_np("error pdf bin 3", (Nkg_tot_new-Nbkg_tot)/Nbkg_tot, -(Nkg_tot_new-Nbkg_tot)/Nbkg_tot , bkgpdf_u, 3., bkgpdf_d,-3.)    ### Works as follows:  Normalization impact at +-1 sigma, pdf impact at _X_ sigma, where X is specified (here 3 and -3)
### IMPORTANT: Normalization is ALWAYS +- 1 sigma, regardless of what you put in the pdf
#bkg.set_np("nomlizationOfBkg", .1, -0.1, NULL,1,NULL,-1)    ### Asume 10% overal normalization error on the bkgd.



## "make" the models
#Nb = 551.9
#Nb = 2*1891#341pb
#Nb = 11260*0.96#tot bkg fit screwed
#Nb = 8327
Nb=numberBkg

bkg.make(bkgpdf, Nb ,0,0, "2011") ### Suppose 45 total events, "2011" indicates the 'channel'. Can be used for combinations
bkg_no_syst.make(bkgpdf, Nb ,0,0, "2011") ### Suppose 45 total events, "2011" indicates the 'channel'. Can be used for combinations

## make the "null" hypothesis. Typically bkg-alone, but can be SM, for example.
print "make null hypo"
nul = csm_model()
print "here?"
nul_no_syst = csm_model()
print "ok?"
bkg.add_to(nul)
print "adding problem?"
bkg_no_syst.add_to(nul_no_syst)
nul.set_interpolation_style("2011",ISTYLE)
print "after iterpolation"
##### Some dictionaries used to store models
dc = {}
dc_no_syst = {}  
test = {}
test_no_syst = {}
## Function to make a signal model for a given br hypothesis

#nuissance
np_plist = []
np_mlist = []
fflist = []
for jj in range(12):
           f_now = TFile("../../params/v5_systematics_sig"+str(jj)+".root")
           pl = f_now.Get("plus")
           mi = f_now.Get("minus")
           fflist+=[f_now]
           np_plist+=[pl]
           np_mlist+=[mi]
print "opened signals"
for jj in range(len(np_plist)):
     print np_plist[jj].GetTitle()

def doSignalHyp(first, br, DataHist, npe = 1000):
    """  Function to make a signal model for a given br hypothesis
    """
#    print "is first? ",first
    if first:
        #print "1"
        dc_no_syst[br] = csm_template(0)
        #print "1a"
        NSIGSYS = 0 
        if use_s_alpha:
            NSIGSYS = NSIGSYS + 1
        if use_s_pdf:
            NSIGSYS = NSIGSYS + 12
        dc[br] = csm_template(NSIGSYS) ### Will propagate the error on alpha
        #dc[br] = csm_template(12) ### Will propagate the error on alpha
        #print "1b"

        if use_s_alpha:
             dc[br].set_np("nomlization of sig", s_alpha/alpha, -s_alpha/alpha, NULL,1,NULL,-1)



        #### Add 12 like this:
        ###dc[br].set_np("parameter name", 0, 0, fluct_h3sigma,3,fluct_h_3sigma_neg,-3)
              ### histograms ar fluctuated (and NORMALIZED) pdfs.
              ### Fluctation consistent with the no. of sigmas specified
              ### Try to use a "large" ~3 no. of sigmas.
   



        #dc[br] = csm_template(12) ### Will propagate the error on alpha
        if use_s_pdf:
              for jj in range(10):
                 np_plist[jj].Scale(1./np_plist[jj].GetSum())
                 np_mlist[jj].Scale(1./np_mlist[jj].GetSum())
                 dc[br].set_np("BDTcalibration"+str(jj), 0, 0, np_plist[jj],6,np_mlist[jj],-6)
              devup = (np_plist[10].GetSum()-sigpdfsum)/sigpdfsum
              devdown = (np_mlist[10].GetSum()-sigpdfsum)/sigpdfsum
              np_plist[10].Scale(1./np_plist[10].GetSum())
              np_mlist[10].Scale(1./np_mlist[10].GetSum())
              dc[br].set_np("BDTcalibration"+str(10), devup, devdown, np_plist[10],3,np_mlist[10],-3)
              devuptoo = (np_plist[11].GetSum()-sigpdfsum)/sigpdfsum
              devdowntoo = (np_mlist[11].GetSum()-sigpdfsum)/sigpdfsum
              np_plist[11].Scale(1./np_plist[11].GetSum())
              np_mlist[11].Scale(1./np_mlist[11].GetSum())
              dc[br].set_np("BDTcalibration"+str(11), devuptoo, devdowntoo, np_plist[11],3,np_mlist[11],-3)




        dc[br].make(sigpdf,br/alpha,0,1, "2011")
        dc_no_syst[br].make(sigpdf,br/alpha,0,1, "2011")
    #### Set the "test" hypothesis (S+B)
        #print "3"
        test[br] = csm_model()
        test_no_syst[br] = csm_model()
        bkg.add_to(test[br])
        dc[br].add_to(test[br])
        bkg_no_syst.add_to(test_no_syst[br])
        dc_no_syst[br].add_to(test_no_syst[br])
        test[br].set_interpolation_style("2011",ISTYLE)
   
        #print "4"
    ### Prepare the stuff that calculates the limits
    
    CL = mclimit_csm()
    
    ## nul and test hypothesis for test statistics. If you put models with systematics here, you activate
    ## refiting of the nuisance parameters ---> computationaly QUITE expensive
    
    #print "5"
    CL.set_null_hypothesis(nul_no_syst)  
    CL.set_test_hypothesis(test_no_syst[br])
    #CL.set_null_hypothesis(nul)  
    #CL.set_test_hypothesis(test[br])

    ## nul and test hypothesis for pseudexperiments
    CL.set_null_hypothesis_pe(nul)
    CL.set_test_hypothesis_pe(test[br])
    #CL.set_null_hypothesis_pe(nul_no_syst)
    #CL.set_test_hypothesis_pe(test_no_syst[br])
    
    ### Add the observed data
    #print "6"
    CL.set_datahist(DataHist, "TheData")
    CL.set_npe(npe)#  to tune the no. of pe. default is usually fine unless you have several np.
    #CL.setpxprintflag(1)
    #print "7"
    CL.run_pseudoexperiments()
    #print "8"
    cls = CL.cls()
    clb = CL.clb()
    clsb = CL.clsb()

    return cls, clb, clsb, CL

#### Set data histogram
## (invented)

def doBkgToyMC(fluctuated = 1, ext_name = "", excl_t =1):
    from scipy import random as rnd
    toyMC = bkgpdf.Clone()
    toyMC.Scale(Nb)
    ###### fluctuate
    for i in range(toyMC.GetNbinsX()):
        for j in range(toyMC.GetNbinsY()):
            toyMC.SetBinContent(i+1,j+1, rnd.poisson(toyMC.GetBinContent(i+1,j+1)))
    return toyMC


#DataHist = doBkgToyMC(ext_name = "2011")
#DataHist.SetTitle("invented (read fluctuated) data hist")

c2.cd()
### Display normalized bkg to compare to data
bdisp = bkgpdf.Clone()
bdisp.SetTitle("bkg normalized to n data events")
bdisp.Scale(Nb)
bdisp.Draw("TEXTBOX")
c3.cd()
print "draw datahist"
#DataHist.Draw("TEXTBOX")

print "prepare scan"

def do_scan(myData):
    """ Fill a text file with the BR vs CL curve
    """
    from XTuple import XTuple
    #print "1"

    tup = XTuple(outfilename, labels = ["br/F","cls/F","clb/F", "clsb/F","CLs_exp_b_med/F" , "CLs_exp_b_p1/F", "CLs_exp_b_p2/F","CLs_exp_b_m1/F" ,"CLs_exp_b_m2/F","CLb_exp_s_med/F" , "CLb_exp_s_p1/F", "CLb_exp_s_p2/F","CLb_exp_s_m1/F" ,"CLb_exp_s_m2/F"])
#
 #   tup = XTuple("23muons_v2", labels = ["br/F","CLs_exp_b_med/F" , "CLs_exp_b_m1/F" ,"CLs_exp_b_p1/F" ])

    #tup = XTuple("tau23mu",["br/F","cls/F","clb/F","clsb/F"])
    dc = {}
    #print "2"
    nSteps=180
    cl90=0
    br90=0
    #for i in range(nSteps):
    for i in range(1*(int(sys.argv[1])-1),1*int(sys.argv[1])):
        print "process iteration: ",i," of ",nSteps
        #ns = float(5+0.05*i)
        #ns = float(5+0.5*i)
        br = (10. + 0.1*i)*1e-09
        #ns = float(4+i)
        
        #br = ns*alpha
        ns = br/alpha
        print ns, br
        cls,clb,clsb, CL = doSignalHyp(1,br,myData,NTOYS )
        #print "still alive"
        
        if cls < 0.1 and not cl90:
            print "cls around 90%: ", cls
            cl90 = cls
            br90=br

        tup.fillItem("br",br)
        tup.fillItem("cls", cls)
        tup.fillItem("clb", clb)
        tup.fillItem("clsb", clsb)
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
        print br, " ---- DONE, cls= ",cls," , clb = ", clb," , clsb = ",clsb
        print ""
        if cls < 0.001: break
    tup.close()
    #print "ret"
    return cl90, br90, dc

#large +-50%
#huge +100%-99%

## def do_limit():
##     f = TFile( 'limit_v03_1000toys_fineSteps.root',"recreate")
##     limit = TH2D("limit", "limit", 25, 0,25, 400, 0,1)
    
##     nToys=100
##     isFirst=1
##     for j in range(nToys):
##         print "process toy #",j+1," from ",nToys
        
##         fakeData = doBkgToyMC(ext_name = "2011")

##         #c.cd(4)
##         #fakeData.Draw("TEXTBOX")
##         nSteps=40
##         last=1
##         for i in range(nSteps):
##             print "process iteration: ",i+1," of ",nSteps
##             #@ja
##             if last<0.03: continue
##             ns = float(10+1*i)#1
##             br = ns*alpha
##             print "nSignal: ", ns,"and BR: ", br
##             cls,clb,clsb, CL = doSignalHyp(isFirst,br,fakeData )
##             print " ---- DONE, cls= ",cls," , clb = ", clb," , clsb = ",clsb
##             print ""
            
## #            print "ready to fill th2 with ",br*1e8,cls
##             limit.Fill(br*1e8,cls)
##             last=cls
##             #if cls < 0.03: break
##         fakeData.Delete()
##         isFirst=0
##     print "write and close"
##     limit.Write()
##     f.Close()
## fakeData = doBkgToyMC(ext_name = "2011")

#do_scan(fakeData)
do_scan(unbhist)
#do_limit()
