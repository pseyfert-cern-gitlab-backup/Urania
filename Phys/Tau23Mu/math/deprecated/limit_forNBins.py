#! /usr/bin/env python

alpha = 2.92e-9
s_alpha = 0.41e-9
NTOYS = 5000000
INPUT_SIGSYS = 12    # 10 when using trash, 8 when throwing away

# for new wide range
#alpha  = alpha*0.925325
#s_alpha  = s_alpha*0.925325

# systematics for which background bins
bkgpar = range(1,26)#marcin
bkgpar = range(1,37)#basem

#bkgpar = []

binorder = [ 18
, 3 
, 13
, 8 
, 17
, 23
, 19
, 22
, 4 
, 2 
, 9 
, 12
, 7 
, 14
, 20
, 16
, 5 
, 24
, 1 
, 21
, 11
, 10
, 6 
, 15
, 25


]


#switches for signal systematics
use_s_alpha = True
use_s_pdf = True
use_s_mass = True

trash_trash = False

throw_trash = True
use_veto = True

from ROOT import *
from MCLimit import *

import sys

binstotake = []
for i in range(int(sys.argv[3])):
   binstotake += [binorder[i]]



if (len(sys.argv)!=2) :
    print "Usage python " + sys.argv[0] + " <gridpoint>"
    print "where <gridpoint> is the number of the gridpoint which you want to process"
    print "branching ratio = 1e-8 + <gridpoint> * 0.3e-8"

print "Usage python " +sys.argv[0]+" <sysnumber>(0..9) <deviation>(plus/minus)"

##outfilename="vetos_mod"+str(sys.argv[1])
##unbfile = "../params/v5_unblinded_vetos_mod.root"
##sigfile="../params/v5_sigPDF_withetaveto.root"
##bkgfile="../params/v5_bck_vetos.root"
##alpha = alpha/0.71325581

outfilename="ProbNN_"+sys.argv[1]+sys.argv[2]+".forNbins_"+sys.argv[3]
unbfile = "../params/ProbNNmu/v4_"
sigfile="../params/ProbNNmu/v4_"
bkgfile="../params/ProbNNmu/v3_basem"

if use_veto:
   sigfile+="with450Veto_"
   bkgfile+="_with450Veto"
   unbfile+="with450Veto_"
if throw_trash:
   sigfile+="trash_"
   bkgfile+="_trash"
   unbfile+="trash_"


sigfile+="sigPDF.root"
bkgfile+=".root"
unbfile+="observed.root"
#sigfile="../params/ProbNNmu/v3_trash_sigPDF.root"
#bkgfile="../params/ProbNNmu/v3_basem_trash.root"

#sigfile="../params/ProbNNmu/v3_sigPDF_with450Veto.root"
#outfilename="ProbNN_etaveto_"+sys.argv[1]+sys.argv[2]
#bkgfile="../params/ProbNNmu/v3_basem_with450Veto.root"
#alpha = alpha/0.812



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















def onebin(hist,binnumber,doscale):
   retval = TH2F(hist.GetName()+"one",hist.GetTitle()+"one",len(binstotake),0.,float(len(binstotake)),hist.GetNbinsY(),hist.GetYaxis().GetBinLowEdge(1),hist.GetYaxis().GetBinUpEdge(int(hist.GetNbinsY())))
   targetx = 0
   for binnumber in binstotake:
    targetx = targetx+1
    for y in range(hist.GetNbinsY()):
     targetbin = retval.GetBin(targetx,y+1)
     sourcebin = hist.GetBin(int(binnumber),y+1)
     bincontent = hist.GetBinContent(sourcebin)
     retval.SetBinContent(targetbin,bincontent)
   scale = retval.GetSum()
   if doscale:
      retval.Scale(1./retval.GetSum())
   return retval,scale



def trash_woscale(hist):
    for m in range(hist.GetNbinsY()):
      for x in [1,2,3,4,5,6,11,16,21] :
         binnumber = hist.GetBin(1+m,x)
         hist.SetBinContent(binnumber,0)
    return hist


def trash(hist) :
    hist.Scale(1./hist.GetSum())
    for m in range(hist.GetNbinsY()):
      for x in [1,2,3,4,5,6,11,16,21] :
         binnumber = hist.GetBin(x,1+m)
         hist.SetBinContent(binnumber,0)
    correction = hist.GetSum()
    hist.Scale(1./correction)
    return hist, correction





ISTYLE = 1  


f_bkg = TFile(bkgfile)

bkgpdf = f_bkg.Get("expected")
bkgpdf.SetTitle("bkg pdf")
bkgpdf, bkgscale = onebin(bkgpdf,sys.argv[3],False)
#bkgpdf_u = f_bkg.Get("expected_plus")
#bkgpdf_u.SetTitle("bkg pdf plus errors")
#bkgpdf_d = f_bkg.Get("expected_minus")
#bkgpdf_d.SetTitle("bkg pdf minus errors")


unbTfile = TFile(unbfile)
if not os.path.isfile(os.getcwd()+"/"+unbfile) :
    print "where is my data?"

unbhist = unbTfile.Get("observed")
unbhist, noise = onebin(unbhist,sys.argv[3],False)

numberBkg=bkgpdf.GetSum()

## Normalize
print "bkgpdf.GetSum(): ",bkgpdf.GetSum()
bkgpdfsum = bkgpdf.GetSum()
#bkgpdfsum_u = bkgpdf_u.GetSum()
#bkgpdfsum_d = bkgpdf_d.GetSum()
bkgpdf.Scale(1./bkgpdf.GetSum())
#bkgpdf_u.Scale(1./bkgpdf_u.GetSum())
#bkgpdf_d.Scale(1./bkgpdf_d.GetSum())
print "normalized bkgpdf.GetSum(): ",bkgpdf.GetSum()

## Make the corresponding pdf's to +- X sigmas (X ~ 2,3 if possible)
if trash_trash:
    bkgpdf, bkgret = trash(bkgpdf)
    #bkgpdf_u = trash(bkgpdf_u)
    #bkgpdf_d = trash(bkgpdf_d)
    bkgpdfsum = bkgpdfsum * bkgret



f_sig = TFile(sigfile)
sigpdf = f_sig.Get("central")#central")
## Normalize (I always use normalized pdf's, and then give the expectation as the scale factor)


#trash
if use_veto:
    #alpha=alpha/0.827
    #s_alpha=s_alpha/0.827
    print "Jon took care of the eta veto"
if throw_trash:
    sigpdfsum = sigpdf.GetSum()
    sigpdf.Scale(1./sigpdf.GetSum())
    sigpdf, factor = onebin(sigpdf,sys.argv[3],True)
    sigpdfsum = sigpdfsum*factor
else:
    sigpdf.Scale(1./sigpdf.GetSum())
    sigpdfsum = sigpdf.GetSum()
    sigpdf, factor = onebin(sigpdf,sys.argv[3],True)

print "    ************************** alpha change due to trashing **************"
print "============= alpha:   ", alpha, "  ==================="
alpha=alpha/sigpdfsum
print "============= alpha:   ", alpha, "  ==================="
print "    **************************************************"
print " there should be a line below here"
print "sigpdfsum = " , str(sigpdfsum)
print " there should be a line above here"




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
#if use_s_pdf:
for jj in range(len(bkgpar)):
           ii = jj+1
           fname = "../params/ProbNNmu/v3_basem"
           if use_veto:
               fname+="_with450Veto"
           if throw_trash:
               fname+="_trash"
           fname+="_sys"+str(ii)+".root"
           f_now = TFile(fname)
           #f_now = TFile("../params/ProbNNmu/v3_basem_trash_sys"+str(ii)+".root")
           #f_now = TFile("../params/ProbNNmu/v3_basem_with450Veto_sys"+str(ii)+".root")
           pl = f_now.Get("expected_plus")
           mi = f_now.Get("expected_minus")
           pl, noise = onebin(pl,sys.argv[3],False)
           mi, noise = onebin(mi,sys.argv[3],False)
           if trash_trash:
               pl = trash_woscale(pl)
               mi = trash_woscale(mi)
           ffblist+=[f_now]
           npb_plist+=[pl]
           npb_mlist+=[mi]
           bevup+=[(pl.GetSum()-bkgpdfsum)/bkgpdfsum/3.]
           bevdown+=[(mi.GetSum()-bkgpdfsum)/bkgpdfsum/3.]
           
for ii in bkgpar:
    jj = ii-1
    npb_plist[jj].Scale(1./npb_plist[jj].GetSum())
    npb_mlist[jj].Scale(1./npb_mlist[jj].GetSum())
    bkg.set_np("error pdf bin"+str(jj),bevup[jj],bevdown[jj],npb_plist[jj],3.,npb_mlist[jj],-3.)
           


#bkg = csm_template(0)   ### 2 systematics 
#bkg = csm_template(1)   ### 2 systematics 
#bkg.set_np("nomlization of sig", s_alpha/alpha, -s_alpha/alpha, NULL,1,NULL,-1)
#bkg.set_np("error pdf bin 3", (Nkg_tot_new-Nbkg_tot)/Nbkg_tot, -(Nkg_tot_new-Nbkg_tot)/Nbkg_tot , bkgpdf_u, 3., bkgpdf_d,-3.)    ### Works as follows:  Normalization impact at +-1 sigma, pdf impact at _X_ sigma, where X is specified (here 3 and -3)
### IMPORTANT: Normalization is ALWAYS +- 1 sigma, regardless of what you put in the pdf
#bkg.set_np("nomlizationOfBkg", .1, -0.1, NULL,1,NULL,-1)    ### Asume 10% overal normalization error on the bkgd.



Nb=numberBkg

bkg.make(bkgpdf, Nb ,0,0, "2011") 
bkg_no_syst.make(bkgpdf, Nb ,0,0, "2011") 

## make the "null" hypothesis. Typically bkg-alone, but can be SM, for example.
print "make null hypo"
nul = csm_model()
nul_no_syst = csm_model()
bkg.add_to(nul)
bkg_no_syst.add_to(nul_no_syst)
nul.set_interpolation_style("2011",ISTYLE)

##### Some dictionaries used to store models
dc = {}
dc_no_syst = {}  
test = {}
test_no_syst = {}
## Function to make a signal model for a given br hypothesis

#nuissance
np_plist = []
devup_list = []
np_mlist = []
devdown_list = []
fflist = []
if use_s_pdf:
    for jj in range(INPUT_SIGSYS):  #FIXME what if trashing?
           fname = "../params/ProbNNmu/v4_"
           if use_veto:
               fname+="with450Veto_"
           if throw_trash:
               fname+="trash_"
           fname += "systematics_sig"+str(jj)+".root"
           f_now = TFile(fname)
           #f_now = TFile("../params/ProbNNmu/v4_trash_systematics_sig"+str(jj)+".root")
           #f_now = TFile("../params/ProbNNmu/v4_with450Veto_systematics_sig"+str(jj)+".root")
           pl = f_now.Get("plus")
           pl, noise = onebin(pl,sys.argv[3],False)
           plsum = pl.GetSum()
           mi = f_now.Get("minus")
           mi, noise = onebin(mi,sys.argv[3],False)
           misum = mi.GetSum()
           if throw_trash:
              plcorr = pl.GetSum()
              micorr = mi.GetSum()
              pl.Scale(1./pl.GetSum())
              mi.Scale(1./mi.GetSum())
           else:
              pl.Scale(1./pl.GetSum())
              mi.Scale(1./mi.GetSum())
              plcorr = pl.GetSum()
              micorr = mi.GetSum()
           print "plcorr = " + str(plcorr)

           fflist+=[f_now]
           np_plist+=[pl]
           np_mlist+=[mi]
           devup_list += [(plcorr-sigpdfsum)/sigpdfsum]
           print "devup = " + str(devup_list[len(devup_list)-1])
           devdown_list += [(micorr-sigpdfsum)/sigpdfsum]

if use_s_mass:
    for jj in range(INPUT_SIGSYS,INPUT_SIGSYS+3):  #FIXME what if trashing?
           fname = "../params/ProbNNmu/v4_"
           if use_veto:
               fname+="with450Veto_"
           if throw_trash:
               fname+="trash_"
           fname += "systematics_sig"+str(jj)+".root"
           f_now = TFile(fname)
           #f_now = TFile("../params/ProbNNmu/v4_trash_systematics_sig"+str(jj)+".root")
           #f_now = TFile("../params/ProbNNmu/v4_with450Veto_systematics_sig"+str(jj)+".root")
           pl = f_now.Get("plus")
           pl, noise = onebin(pl,sys.argv[3],False)
           plsum = pl.GetSum()
           mi = f_now.Get("minus")
           mi, noise = onebin(mi,sys.argv[3],False)
           misum = mi.GetSum()
           plcorr = pl.GetSum()
           micorr = mi.GetSum()
           pl.Scale(1./pl.GetSum())
           mi.Scale(1./mi.GetSum())
           print "plcorr = " + str(plcorr)

           fflist+=[f_now]
           np_plist+=[pl]
           np_mlist+=[mi]
           devup_list += [(plcorr-1.)]
           print "devup = " + str(devup_list[len(devup_list)-1])
           devdown_list += [(micorr-1.)]


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
            NSIGSYS = NSIGSYS + INPUT_SIGSYS
        if use_s_mass:
            NSIGSYS = NSIGSYS + 3
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
              for jj in range(INPUT_SIGSYS):
                 devup = devup_list[jj]
                 devdown = devdown_list[jj]
                 print "normalisation changes due to trashing by " + str(devup)
                 dc[br].set_np("BDTcalibration"+str(jj), devup/3.,devdown/3. , np_plist[jj],3,np_mlist[jj],-3)
              if use_s_mass:
                for jj in range(INPUT_SIGSYS,INPUT_SIGSYS+3):
                 devup = devup_list[jj]
                 devdown = devdown_list[jj]
                 print "normalisation changes due to masswindow systematics by " + str(devup)
                 dc[br].set_np("BDTcalibration"+str(jj), devup/3.,devdown/3. , np_plist[jj],3,np_mlist[jj],-3)




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


    lower =  030.e-09
    upper = 0400.e-09

    llower = TMath.Log(lower)
    lupper = TMath.Log(upper)

    linear = False
    nSteps=31
    cl90=0
    br90=0
    #for i in range(nSteps):
    for i in [int(sys.argv[2])-1]:
        print "process iteration: ",i," of ",nSteps
        #ns = float(5+0.05*i)
        #ns = float(5+0.5*i)
        if linear:
          br = (lower + i* (upper-lower)/float(nSteps))
        if not linear:
          br = TMath.Exp(llower + i* (lupper-llower)/float(nSteps))
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
        #FIXME when debuging this can be annoying
        if cls < 0.001: break
    tup.close()
    #print "ret"
    return cl90, br90, dc

fakeData = doBkgToyMC(ext_name = "2011")
do_scan(fakeData)

#do_scan(unbhist)
