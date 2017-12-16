#! /usr/bin/env python

#############################################
# steering parameters


mode = "OS" # may be "OS" or "SS"
blind = True
trash = False # FIXME needs to be tested

if "OS"==mode:
  alpha = 6.2e-8     #normalisation factor
  s_alpha = 0.1e-8   #error on normalisation
else:
  alpha = 7.5e-8     #normalisation factor
  s_alpha = 0.1e-8   #error on normalisation

NTOYS = 10000

# systematics for which background bins
bkgpar = []

#switches for signal systematics
use_s_alpha = True
use_s_pdf = True


outfilenameroot = "sigsystematicstest"
if not blind:
     unbfile = "../params/v5_unblinded.root" #FIXME this is copy & paste from tau23mu. take the correct file here

bkgfile=mode+"_bck.root"
sigfile="../params/tau2pmumu"+mode+"_sig.root"


ISTYLE = 1  

# steering parameters
#############################################

from ROOT import *
from MCLimit import *
import sys

if (len(sys.argv)!=2) :
    print "Usage python " + argv[0] + " <gridpoint>"
    print "where <gridpoint> is the number of the gridpoint which you want to process"
    print "branching ratio = 1e-8 + <gridpoint> * 0.3e-8"


import os.path
#if not os.path.exists(outfilenameroot+".sh") :
if False:
   print "since this script processes parallel several gridpoints and produces output for each process"
   print "the output files need to be merged. This instance here creates a script " + outfilenameroot + ".sh"
   print "which shall do the merging for you. Since this is a script written by a script, it braintwisting"
   print "to write and certainly needs more debuging, than I put in, so treat with care!"
   scriptfile = open(outfilenameroot+".sh")
   scriptfile.write("#!/usr/bin/env zsh")
   scriptfile.write("output="+outfilenameroot+".dat")
   scriptfile.write("firstfile=`ls "+outfilenameroot+"[0-9]*.dat | head -1`")
   scriptfile.write("length=`wc -l $firstfile`")
   scriptfile.write("pointsperfile=`expr $length - 1`")
   scriptfile.write("touch $output")
   scriptfile.write("head -1 $firstfile > $output")
   scriptfile.write("for v in "+outfilenameroot+"[0-9].dat :")
   scriptfile.write("  do")
   scriptfile.write("  tail -$pointsperfile $v >> $output")
   scriptfile.write("  done")
   scriptfile.write("for v in "+outfilenameroot+"[0-9][0-9].dat :")
   scriptfile.write("  do")
   scriptfile.write("  tail -$pointsperfile $v >> $output")
   scriptfile.write("  done")
   scriptfile.write("for v in "+outfilenameroot+"[0-9][0-9][0-9].dat :")
   scriptfile.write("  do")
   scriptfile.write("  tail -$pointsperfile $v >> $output")
   scriptfile.write("  done")
   scriptfile.close()

outfilename=outfilenameroot+"_"+mode+str(sys.argv[1])

f_bkg = TFile(bkgfile)

bkgpdf = f_bkg.Get("expected_exp")
bkgpdf.SetTitle("bkg pdf")
bkgpdf_u = f_bkg.Get("expected_plus")
bkgpdf_u.SetTitle("bkg pdf plus errors")
bkgpdf_d = f_bkg.Get("expected_minus")
bkgpdf_d.SetTitle("bkg pdf minus errors")


### get the unblinded histogram from the file specified above
if not blind:
    unbTfile = TFile(unbfile)
    unbhist = unbTfile.Get("observed")


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



f_sig = TFile(sigfile)

sigpdf = f_sig.Get("central")
sigpdfsum = sigpdf.GetSum()
if trash:
   sigpdfoldsum = sigpdfsum
   for mm in range(sigpdf.GetNbinsY):
      sigpdf.SetBinContent(sigpdf.GetBin(1,1+mm),0)
   sigpdfsum = sigpdf.GetSum()
   alpha = alpha * sigpdfsumold / sigpdfsum
   s_alpha = s_alpha * sigpdfsumold / sigpdfsum
sigpdf.Scale(1./sigpdf.GetSum())
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
   for jj in range(25):
           ii = jj+1
           f_now = TFile("../params/rightbkg_sys_"+str(ii)+".root")
           pl = f_now.Get("expected_plus")
           mi = f_now.Get("expected_minus")
           ffblist+=[f_now]
           npb_plist+=[pl]
           npb_mlist+=[mi]
           bevup+=[(pl.GetSum()-bkgpdfsum)/bkgpdfsum/3]
           bevdown+=[(mi.GetSum()-bkgpdfsum)/bkgpdfsum/3]
           
for ii in bkgpar:
    jj = ii-1
    npb_plist[jj].Scale(1./npb_plist[jj].GetSum())
    npb_mlist[jj].Scale(1./npb_mlist[jj].GetSum())
    bkg.set_np("error pdf bin"+str(jj),bevup[jj],bevdown[jj],npb_plist[jj],9.,npb_mlist[jj],-9.)
           



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
np_mlist = []
fflist = []
if use_s_pdf:
   pl =  f_sig.Get("central_plus")
   mi =  f_sig.Get("central_minus")
   for jj in range(sigpdf.GetNbinsX()):
           thispl = sigpdf.Clone("BDTcalibration_systematics_parameter"+str(jj)+"_plus")
           thismi = sigpdf.Clone("BDTcalibration_systematics_parameter"+str(jj)+"_plus")
           for mm in range(sigpdf.GetNbinsY()):
             thispl.SetBinContent(thispl.GetBin(1+jj,1+mm),3*pl.GetBinContent(pl.GetBin(1+jj,1+mm))-2*sigpdf.GetBinContent(mi.GetBin(1+jj,1+mm)))
             thismi.SetBinContent(thismi.GetBin(1+jj,1+mm),3*mi.GetBinContent(mi.GetBin(1+jj,1+mm))-2*sigpdf.GetBinContent(mi.GetBin(1+jj,1+mm)))
           if trash:
             for mm in range(sigpdf.GetNbinsY):
                thismi.SetBinContent(sigpdf.GetBin(1,1+mm),0)
                thispl.SetBinContent(sigpdf.GetBin(1,1+mm),0)
           #BUGFIX: the following two lines were missing in the previous version
           thispl.Scale(1./thispl.GetSum())
           thismi.Scale(1./thismi.GetSum())
           np_plist+=[thispl]
           np_mlist+=[thismi]

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
            NSIGSYS = NSIGSYS + 2 + sigpdf.GetNbinsX() 
            if trash:  #correction seems appropriate with trashing
                NSIGSYS = NSIGSYS - 1
        dc[br] = csm_template(NSIGSYS) ### Will propagate the error on alpha

        if use_s_alpha:
             dc[br].set_np("nomlization of sig", s_alpha/alpha, -s_alpha/alpha, NULL,1,NULL,-1)




        if use_s_pdf:
              for jj in range(sigpdf.GetNbinsX()):
                 if (trash):  #correction seems appropriate with trashing
                    if 0==jj:
                        continue
                 np_plist[jj].Scale(1./np_plist[jj].GetSum())
                 np_mlist[jj].Scale(1./np_mlist[jj].GetSum())
                 dc[br].set_np("BDTcalibration"+str(jj), 0, 0, np_plist[jj],3,np_mlist[jj],-3)


              f_massmeancalibplus   = TFile("../params/tau2pmumu"+mode+"_sig_highmean.root")
              h_massmeancalibplus = f_massmeancalibplus.Get("central")
              f_massmeancalibminus  = TFile("../params/tau2pmumu"+mode+"_sig_lowmean.root")
              h_massmeancalibminus = f_massmeancalibminus.Get("central")
              devup = (h_massmeancalibplus.GetSum()-sigpdfsum)/sigpdfsum
              devdown = (h_massmeancalibminus.GetSum()-sigpdfsum)/sigpdfsum
              dc[br].set_np("massmeancalibration", devup, devdown, h_massmeancalibplus,3,h_massmeancalibminus,-3)
              f_masswidthcalibplus  = TFile("../params/tau2pmumu"+mode+"_sig_widewidth.root")
              h_masswidthcalibplus = f_masswidthcalibplus.Get("central")
              f_masswidthcalibminus = TFile("../params/tau2pmumu"+mode+"_sig_smallwidth.root")
              h_masswidthcalibminus = f_masswidthcalibminus.Get("central")
              devup = (h_masswidthcalibplus.GetSum()-sigpdfsum)/sigpdfsum
              devdown = (h_masswidthcalibminus.GetSum()-sigpdfsum)/sigpdfsum
              dc[br].set_np("masswidthcalibration", devup, devdown, h_masswidthcalibplus,3,h_masswidthcalibminus,-3)



        dc[br].make(sigpdf,br/alpha,0,1, "2011")
        dc_no_syst[br].make(sigpdf,br/alpha,0,1, "2011")
    #### Set the "test" hypothesis (S+B)
        test[br] = csm_model()
        test_no_syst[br] = csm_model()
        bkg.add_to(test[br])
        dc[br].add_to(test[br])
        bkg_no_syst.add_to(test_no_syst[br])
        dc_no_syst[br].add_to(test_no_syst[br])
        test[br].set_interpolation_style("2011",ISTYLE)
   
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
    nSteps=180
    cl90=0
    br90=0

#### TODO as you see, this was once supposed to process more than one grid point. However that got broken from Erasmus v6 to v7. Anyhow the fully parallel version also has advantages.

    for i in [int(sys.argv[1])]:#range(1*(int(sys.argv[1])-1),1*int(sys.argv[1])):

        print "process iteration: ",i," of ",nSteps
        #ns = float(5+0.05*i)
        #ns = float(5+0.5*i)
        br = (10. + 3*i)*1e-09
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



if blind:
   fakeData = doBkgToyMC(ext_name = "2011")
   do_scan(fakeData)
else:
   do_scan(unbhist)
