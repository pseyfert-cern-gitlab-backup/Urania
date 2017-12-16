#! /usr/bin/env python

#############################################
# steering parameters
import sys

if (len(sys.argv)!=2) :
    print "Usage python " + sys.argv[0] + " <mode> <gridpoint>"
    print "where <gridpoint> is the number of the gridpoint which you want to process"
    print "branching ratio = 1e-8 + <gridpoint> * 0.3e-8"

mode = sys.argv[1]#"OS" # may be "OS" or "SS"
trash = False # FIXME needs to be tested

if "OS"==mode:
  alpha = 6.0e-8     #normalisation factor
  s_alpha = 1.2e-8   #error on normalisation
else:
  alpha = 6.9e-8     #normalisation factor
  s_alpha = 1.4e-8   #error on normalisation

NTOYS = 3000000

# systematics for which background bins
bkgpar = [0,1,2,3]

#switches for signal systematics
use_s_alpha = True
use_s_pdf = True
if (int(sys.argv[2])>800):
   use_s_mass = True
else:
   use_s_mass = False


throw_trash=True

outfilenameroot = "tau2pmumulimit"

sigfile="../params/PMuMu/tau2pmumu"+mode
unbfile="../params/PMuMu/tau2pmumu"+mode
if throw_trash:
   sigfile+="_trash"
   unbfile+="_trash"
sigfile+="_sigPDF.root"
unbfile+="_observed.root"

ISTYLE = 1  

# steering parameters
#############################################

from ROOT import *
from MCLimit import *

outfilename=outfilenameroot+"_"+mode+str(sys.argv[2])




bkgfile="../params/PMuMu/tau2pmumu"+mode
if throw_trash:
   bkgfile+="_trash"
bkgfile+="_bkgPDF.root"
print "opening ", bkgfile
f_bkg = TFile(bkgfile)

bkgpdf = f_bkg.Get("expected_exp")
bkgpdf.SetTitle("bkg pdf")


### get the unblinded histogram from the file specified above
unbTfile = TFile(unbfile)
unbhist = unbTfile.Get("observed")

######unbhist = bkgpdf.Clone("fake")

#number of bkg events
numberBkg=bkgpdf.GetSum()

## Normalize
print "bkgpdf.GetSum(): ",bkgpdf.GetSum()
bkgpdfsum = bkgpdf.GetSum()
bkgpdf.Scale(1./bkgpdf.GetSum())
print "normalized bkgpdf.GetSum(): ",bkgpdf.GetSum()


if not use_s_pdf:
    if use_s_mass:
        print "sorry not implemented"
        sys.exit(1)

f_sig = TFile(sigfile)

sigpdf = f_sig.Get("central")
if throw_trash:
    sigpdfsum = sigpdf.GetSum()
    sigpdf.Scale(1./sigpdf.GetSum())
else:
    sigpdf.Scale(1./sigpdf.GetSum())
    sigpdfsum = sigpdf.GetSum()

print "after scaling signal sum ",sigpdf.GetSum()



c1 = TCanvas()
c2 = TCanvas()
c3 = TCanvas()


gStyle.SetPaintTextFormat("5.1f")
c1.cd()
sigpdf.Draw("TEXTBOX")


### Set the bkg model
print "set bkg model"
bkg_no_syst = csm_template(0)   ### No systematics (used for the test statistic)


bkg = csm_template(len(bkgpar))   
#bkg = csm_template(1+len(bkgpar))
npb_plist = []
npb_mlist = []
ffblist = []
bevup = []
bevdown = []
if (0<len(bkgpar)):
   for jj in bkgpar:
           ii = jj
           f_now = TFile("../params/PMuMu/tau2pmumu"+mode+"_trash_systematics_bkg"+str(ii)+".root")
           pl = f_now.Get("expected_plus")
           mi = f_now.Get("expected_minus")
           ffblist+=[f_now]
           npb_plist+=[pl]
           npb_mlist+=[mi]
           bevup+=[(pl.GetSum()-bkgpdfsum)/bkgpdfsum/3]
           bevdown+=[(mi.GetSum()-bkgpdfsum)/bkgpdfsum/3]
           
for ii in bkgpar:
    jj = ii
    npb_plist[jj].Scale(1./npb_plist[jj].GetSum())
    npb_mlist[jj].Scale(1./npb_mlist[jj].GetSum())
    bkg.set_np("error pdf bin"+str(jj),bevup[jj],bevdown[jj],npb_plist[jj],3.,npb_mlist[jj],-3.)
           



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

#nuissance
np_plist = []
devup_list = []
np_mlist = []
devdown_list = []
fflist = []
if use_s_pdf:
    for jj in range(5):
           fname = "../params/PMuMu/tau2pmumu"+mode+"_"
           if throw_trash:
               fname+="trash_"
           fname += "systematics_sig"+str(jj)+".root"
           f_now = TFile(fname)
           print "opened ", fname
           #f_now = TFile("../params/ProbNNmu/v4_trash_systematics_sig"+str(jj)+".root")
           #f_now = TFile("../params/ProbNNmu/v4_with450Veto_systematics_sig"+str(jj)+".root")
           pl = f_now.Get("plus")
           plsum = pl.GetSum()
           mi = f_now.Get("minus")
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
           fname = "../params/PMuMu/tau2pmumu"+mode+"_"
           if throw_trash:
               fname+="trash_"
           fname += "mean.root"
           f_now = TFile(fname)
           print "opened ", fname
           #f_now = TFile("../params/ProbNNmu/v4_trash_systematics_sig"+str(jj)+".root")
           #f_now = TFile("../params/ProbNNmu/v4_with450Veto_systematics_sig"+str(jj)+".root")
           pl = f_now.Get("plus")
           plsum = pl.GetSum()
           mi = f_now.Get("minus")
           misum = mi.GetSum()
           plcorr = pl.GetSum()
           micorr = mi.GetSum()
           pl.Scale(1./pl.GetSum())
           mi.Scale(1./mi.GetSum())
           print "plcorr = " + str(plcorr)

           fflist+=[f_now]
           np_plist+=[pl]
           np_mlist+=[mi]
           devup_list += [plcorr-1.]
           print "devup = " + str(devup_list[len(devup_list)-1])
           devdown_list += [micorr-1.]
           fname = "../params/PMuMu/tau2pmumu"+mode+"_"
           if throw_trash:
               fname+="trash_"
           fname += "sigma1.root"
           f_now = TFile(fname)
           print "opened ", fname
           #f_now = TFile("../params/ProbNNmu/v4_trash_systematics_sig"+str(jj)+".root")
           #f_now = TFile("../params/ProbNNmu/v4_with450Veto_systematics_sig"+str(jj)+".root")
           pl = f_now.Get("plus")
           plsum = pl.GetSum()
           mi = f_now.Get("minus")
           misum = mi.GetSum()
           plcorr = pl.GetSum()
           micorr = mi.GetSum()
           pl.Scale(1./pl.GetSum())
           mi.Scale(1./mi.GetSum())
           print "plcorr = " + str(plcorr)

           fflist+=[f_now]
           np_plist+=[pl]
           np_mlist+=[mi]
           devup_list += [plcorr-1.]
           print "devup = " + str(devup_list[len(devup_list)-1])
           devdown_list += [micorr-1.]


           fname = "../params/PMuMu/tau2pmumu"+mode+"_"
           if throw_trash:
               fname+="trash_"
           fname += "sigma2.root"
           f_now = TFile(fname)
           print "opened ", fname
           #f_now = TFile("../params/ProbNNmu/v4_trash_systematics_sig"+str(jj)+".root")
           #f_now = TFile("../params/ProbNNmu/v4_with450Veto_systematics_sig"+str(jj)+".root")
           pl = f_now.Get("plus")
           plsum = pl.GetSum()
           mi = f_now.Get("minus")
           misum = mi.GetSum()
           plcorr = pl.GetSum()
           micorr = mi.GetSum()
           pl.Scale(1./pl.GetSum())
           mi.Scale(1./mi.GetSum())
           print "plcorr = " + str(plcorr)
           print "micorr = " + str(micorr)

           fflist+=[f_now]
           np_plist+=[pl]
           np_mlist+=[mi]
           devup_list += [plcorr-1.]
           print "devup = " + str(devup_list[len(devup_list)-1])
           devdown_list += [micorr-1.]





for jj in range(len(np_plist)):
     print np_plist[jj].GetTitle()

def doSignalHyp(first, br, DataHist, npe = 1000):
    """  Function to make a signal model for a given br hypothesis
    """
    if first:
        dc_no_syst[br] = csm_template(0)
        NSIGSYS = 0 
        if use_s_alpha:
            NSIGSYS = NSIGSYS + 1
        if use_s_pdf:
            NSIGSYS = NSIGSYS + 5
        if use_s_mass:
            NSIGSYS = NSIGSYS + 3
        dc[br] = csm_template(NSIGSYS) ### Will propagate the error on alpha

        if use_s_alpha:
             dc[br].set_np("nomlization of sig", s_alpha/alpha, -s_alpha/alpha, NULL,1,NULL,-1)




        if use_s_pdf:
              for jj in range(5):
                 devup = devup_list[jj]
                 devdown = devdown_list[jj]
                 print "normalisation changes due to trashing by " + str(devup)
                 dc[br].set_np("BDTcalibration"+str(jj), devup/3.,devdown/3. , np_plist[jj],3,np_mlist[jj],-3)


        if use_s_mass:
              for jj in range(5,8):
                 devup = devup_list[jj]
                 devdown = devdown_list[jj]
                 print "normalisation changes due to mass resolution by " + str(devup)
                 print "                                            and " + str(devdown)
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
    ### Prepare the stuff that calculates the limits
    CL = mclimit_csm()
    
    ## nul and test hypothesis for test statistics. If you put models with systematics here, you activate
    ## refiting of the nuisance parameters ---> computationaly QUITE expensive
    
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
    dc = {}
    #print "2"
    lower = 010.e-08
    upper = 080.e-08
    nSteps=30
    cl90=0
    br90=0

#### TODO as you see, this was once supposed to process more than one grid point. However that got broken from Erasmus v6 to v7. Anyhow the fully parallel version also has advantages.

    #for i in [int(sys.argv[2])]:#range(1*(int(sys.argv[1])-1),1*int(sys.argv[1])):
    for i in range(nSteps):

        print "process iteration: ",i," of ",nSteps
        #ns = float(5+0.05*i)
        #ns = float(5+0.5*i)
        br = (lower + i* (upper-lower)/float(nSteps))
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



do_scan(unbhist)
