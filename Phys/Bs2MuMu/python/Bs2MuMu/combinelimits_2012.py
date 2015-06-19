#! /usr/bin/env python

CHANNEL = "Bs"
use_2012= 0
use_autum = 0
use_2010 = 0
use_cms = 1
#use_cms = use_cms*use_2010
use_cdf = 0*use_cms
use_atlas = 0#*use_cms

from ROOT import *
from MCLimit import *
import sys
from XTuple import *
from SomeUtils.alyabar import *
#from SomeMassModels import B2JpsiModels
#if CHANNEL == "Bd":
 #   import analysis2010_for_CombBd as a2010
  #  import analysis2012Bd as a2012   #### 2012 data, models, syst....
   # import cmsBd as cms
    #use_atlas = 0
    #use_cdf = 0
#else:
import analysis2010_for_Comb_mc  as a2010
import analysis2012_redone_mc as a2012   #### 2012 data, models, syst..
import analysis2012_autum_mc as autum   #### 2012 data, models, syst....
import cms_mc as cms
   
import atlas_mc as atlas
import cdf3_mc as cdf
if CHANNEL != a2012.CHANNEL : cancer
if CHANNEL != autum.CHANNEL : cancer


XFEED = (a2012.CHANNEL == "Bd")
addSM_toBkg = 0
SYST = 1
PROFILEATLAS = 0
ISTYLE = 1 # VERTICAL EXT=3, VERTICAL ONLY = 1 , HORIZONTAL = DEFAULT = 0

print "Using CMS:", use_cms
print "Using CDF:", use_cdf

#######################
## Null hypothesis   ##
#######################

nulpe = csm_model()     #### This must contain ALL syst
nul = csm_model()       #### Here only the syst you want to fit


if use_cms:  
    cms.bkg_b.add_to(nulpe)
    cms.bkg_e.add_to(nulpe)
    cms.bkg_b_no_syst.add_to(nul)
    cms.bkg_e_no_syst.add_to(nul)
    if addSM_toBkg:
        cms.sm1.add_to(nulpe)
        cms.sm2.add_to(nulpe)

if use_atlas:  
    atlas.bkg_r1.add_to(nulpe)
    atlas.bkg_r2.add_to(nulpe)
    atlas.bkg_r3.add_to(nulpe)
    if PROFILEATLAS:
        atlas.bkg_r1.add_to(nul)
        atlas.bkg_r2.add_to(nul)
        atlas.bkg_r3.add_to(nul)
        #atlas.bkg_r1_no_syst.add_to(nul)
        #atlas.bkg_r2_no_syst.add_to(nul)
        #atlas.bkg_r3_no_syst.add_to(nul)
        
    else:
        atlas.bkg_r1_no_syst.add_to(nul)
        atlas.bkg_r2_no_syst.add_to(nul)
        atlas.bkg_r3_no_syst.add_to(nul)
    if addSM_toBkg:
        atlas.sm1.add_to(nulpe)
        atlas.sm2.add_to(nulpe)
        atlas.sm3.add_to(nulpe)
    


if use_cdf:
    for i in range(8):
        cdf.dcBkgCDF["bkg CDF CC B" + str(i+1)].add_to(nulpe)
        cdf.dcBkgCDF["bkg CDF CF B" + str(i+1)].add_to(nulpe)
        cdf.dcBkgCDF["bkg CDF CC B" + str(i+1) +"no_syst"].add_to(nul)
        cdf.dcBkgCDF["bkg CDF CF B" + str(i+1) +"no_syst"].add_to(nul)    
    
if use_2012:
    a2012.bkg.add_to(nulpe) ### Now add 2012
    a2012.bkg_no_syst.add_to(nul) 

    if a2012.MISID:
        a2012.misid_no_syst.add_to(nul)
        a2012.misid.add_to(nulpe)
        #a2012.misid_no_syst.add_to(nulpe) ### ignore bkg sys!!
        
    if XFEED: #a2012.CHANNEL == "Bd":
        print "Think on the resolution issuse"
        #BREAK
    
        a2012.crossfeed_no_syst.add_to(nul)
        a2012.crossfeed.add_to(nulpe)
        
    if addSM_toBkg:
        a2012.sm.add_to(nulpe)
        #a2012.sm_no_syst.add_to(nul)
    nulpe.set_interpolation_style("2012",ISTYLE)
if use_autum:
    autum.bkg.add_to(nulpe) ### Now add 2012
    autum.bkg_no_syst.add_to(nul) 

    if autum.MISID:
        autum.misid_no_syst.add_to(nul)
        autum.misid.add_to(nulpe)
        #autum.misid_no_syst.add_to(nulpe) ### ignore bkg sys!!
        
    if XFEED: #autum.CHANNEL == "Bd":
        print "Think on the resolution issuse"
        #BREAK
    
        autum.crossfeed_no_syst.add_to(nul)
        autum.crossfeed.add_to(nulpe)
        
    if addSM_toBkg:
        autum.sm.add_to(nulpe)
        #a2012.sm_no_syst.add_to(nul)
    nulpe.set_interpolation_style("2012autum",ISTYLE)
    
if use_2010:
    a2010.bkg.add_to(nulpe) ### Now add 2012
    a2010.bkg_no_syst.add_to(nul)
    if addSM_toBkg:
        a2010.sm.add_to(nulpe)
    nulpe.set_interpolation_style("2010",ISTYLE)

################################
## Test Hypothesis function  ###
################################

def DoTestHyp(BR):
   
    ns2012 = BR/a2012.alpha
    ns2012autum = BR/autum.alpha
    ns2010 = BR/a2010.alpha

    
    a2012.DoSigModel(ns2012)
    autum.DoSigModel(ns2012autum)
    a2010.DoSigModel(ns2010)

    test = csm_model()
    testpe = csm_model()
   
        
    if use_cms:
        cms.DoTestHyp(BR)
        cms.dcCMS[str(BR) + "barrel"].add_to(testpe)
        cms.dcCMS[str(BR) + "EC"].add_to(testpe)
        cms.dcCMS[str(BR) + "barrel_no_syst"].add_to(test)
        cms.dcCMS[str(BR) + "EC_no_syst"].add_to(test)
        cms.bkg_b.add_to(testpe)
        cms.bkg_e.add_to(testpe)
        cms.bkg_b_no_syst.add_to(test)
        cms.bkg_e_no_syst.add_to(test)
    if use_atlas:
        atlas.DoTestHyp(BR)
        atlas.dcATLAS[str(BR) + "r1"].add_to(testpe)
        atlas.dcATLAS[str(BR) + "r2"].add_to(testpe)
        atlas.dcATLAS[str(BR) + "r3"].add_to(testpe)
        atlas.bkg_r1.add_to(testpe)
        atlas.bkg_r2.add_to(testpe)
        atlas.bkg_r3.add_to(testpe)
        if PROFILEATLAS:
            #atlas.dcATLAS[str(BR) + "r1"].add_to(test)
            #atlas.dcATLAS[str(BR) + "r2"].add_to(test)
            #atlas.dcATLAS[str(BR) + "r3"].add_to(test)
            atlas.dcATLAS[str(BR) + "r1_no_syst"].add_to(test)
            atlas.dcATLAS[str(BR) + "r2_no_syst"].add_to(test)
            atlas.dcATLAS[str(BR) + "r3_no_syst"].add_to(test)
            #atlas.bkg_r1_no_syst.add_to(test)
            #atlas.bkg_r2_no_syst.add_to(test)
            #atlas.bkg_r3_no_syst.add_to(test)
            atlas.bkg_r1.add_to(test)
            atlas.bkg_r2.add_to(test)
            atlas.bkg_r3.add_to(test)
            
        else:
            atlas.dcATLAS[str(BR) + "r1_no_syst"].add_to(test)
            atlas.dcATLAS[str(BR) + "r2_no_syst"].add_to(test)
            atlas.dcATLAS[str(BR) + "r3_no_syst"].add_to(test)

            atlas.bkg_r1_no_syst.add_to(test)
            atlas.bkg_r2_no_syst.add_to(test)
            atlas.bkg_r3_no_syst.add_to(test)
        
        
    if use_cdf:
        cdf.DoTestHyp(BR)
        for i in range(8):
            cdf.dcBkgCDF["bkg CDF CC B" + str(i+1)].add_to(testpe)
            cdf.dcBkgCDF["bkg CDF CF B" + str(i+1)].add_to(testpe)
            cdf.dcBkgCDF["bkg CDF CC B" + str(i+1) +"no_syst"].add_to(test)
            cdf.dcBkgCDF["bkg CDF CF B" + str(i+1) +"no_syst"].add_to(test)
            
            cdf.dcCDF[str(BR) + "CDF CC B" + str(i+1)].add_to(testpe)
            cdf.dcCDF[str(BR) + "CDF CF B" + str(i+1)].add_to(testpe)
            cdf.dcCDF[str(BR) + "CDF CC B" + str(i+1) +"no_syst"].add_to(test)
            cdf.dcCDF[str(BR) + "CDF CF B" + str(i+1) +"no_syst"].add_to(test)
            
        
    if use_2012:
        a2012.bkg.add_to(testpe)
        a2012.bkg_no_syst.add_to(test)
        #a2012.bkg_no_syst.add_to(testpe) ## ignore bkg ssyt
        if a2012.MISID:
            a2012.misid_no_syst.add_to(test)
            a2012.misid.add_to(testpe)
            #a2012.misid_no_syst.add_to(testpe) ##ignore bkg syst
        if XFEED:
            a2012.crossfeed_no_syst.add_to(test)
            a2012.crossfeed.add_to(testpe)
        if addSM_toBkg:
            a2012.sm.add_to(testpe)
            a2012.sm_no_syst.add_to(test)
        
        a2012.dc2012[ns2012].add_to(testpe)
        a2012.dc2012[str(ns2012) + "_no_syst"].add_to(test)
        testpe.set_interpolation_style("2012",ISTYLE)
        
    if use_autum:
        autum.bkg.add_to(testpe)
        autum.bkg_no_syst.add_to(test)
        #autum.bkg_no_syst.add_to(testpe) ## ignore bkg ssyt
        if autum.MISID:
            autum.misid_no_syst.add_to(test)
            autum.misid.add_to(testpe)
            #autum.misid_no_syst.add_to(testpe) ##ignore bkg syst
        if XFEED:
            autum.crossfeed_no_syst.add_to(test)
            autum.crossfeed.add_to(testpe)
        if addSM_toBkg:
            autum.sm.add_to(testpe)
            autum.sm_no_syst.add_to(test)
        
        autum.dc2012autum[ns2012autum].add_to(testpe)
        autum.dc2012autum[str(ns2012autum) + "_no_syst"].add_to(test)
        testpe.set_interpolation_style("2012autum",ISTYLE)
        
    if use_2010:
        a2010.bkg.add_to(testpe)
        a2010.bkg_no_syst.add_to(test)
        #a2012.bkg_no_syst.add_to(testpe) ## ignore bkg ssyt
        a2010.dc2010[ns2010].add_to(testpe)
        a2010.dc2010[str(ns2010) + "_no_syst"].add_to(test)
        testpe.set_interpolation_style("2010",ISTYLE)
    return testpe, test

##########################################
##   Confidendce level calculator    #####
##########################################

tests, testpes = {}, {}

def do2012BkgToyMC(fluctuated = 1, ext_name = "2012", addbr = 0):
    print "DOING A TOY DATA"
    from scipy import random as rnd
    toyMC = a2012.hbpdf.Clone()
    toyMC.Scale(a2012.Nb)
    toyMC.SetName(ext_name)
    if a2012.MISID:
        toyB = a2012.hmisid.Clone()
        toyB.Scale(a2012.MISID)
        toyMC.Add(toyB)

    if addbr:
        toyS = a2012.hspdf.Clone()
        toyS.Scale(addbr*1e-09/alpha)
        toyMC.Add(toyB)
        
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

def DoCL(BR, npe =0, syst = 0 ):
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
        
    if use_cms:
        CL.set_datahist(cms.DataHist_b,"CMS barrel")
        CL.set_datahist(cms.DataHist_e,"CMS EC")
    if use_cdf:
        for i in range(8):
            CL.set_datahist(cdf.DCC[i], "CDF CC B" + str(i+1))
            CL.set_datahist(cdf.DCF[i], "CDF CF B" + str(i+1))
    if use_atlas:
        CL.set_datahist(atlas.DataHist_r1, "ATLAS r1")
        CL.set_datahist(atlas.DataHist_r2, "ATLAS r2")
        CL.set_datahist(atlas.DataHist_r3, "ATLAS r3")
    if use_2010: CL.set_datahist(a2010.DataHist, "2010")
    if use_2012: CL.set_datahist(a2012.DataHist, "2012")
    if use_autum: CL.set_datahist(autum.DataHist, "2012autum")
    
    if npe: CL.set_npe(npe)
    
    return CL
##################333
## SCAN
####################
import sys
st0 = float(sys.argv[1])

def do_scan(filename, stop_95 = False):
    tup = XTuple(filename, labels = ["BR/F","ts/F", "chi2/F", "CLs/F","CLb/F", "CLsb/F","CLs_exp_b_med/F" , "CLs_exp_b_p1/F", "CLs_exp_b_p2/F","CLs_exp_b_m1/F" ,"CLs_exp_b_m2/F","CLb_exp_s_med/F" , "CLb_exp_s_p1/F", "CLb_exp_s_p2/F","CLb_exp_s_m1/F" ,"CLb_exp_s_m2/F"])
   
    print a2012.CHANNEL
    c90, c95 = 0.,0
    for j in range(4):
        
        i = st0 + .05*j
        print "ps for BR:", i
        CL = DoCL(i*1e-9 ,1000000, syst=SYST)
        #CL.setpxprintflag(1)
        CL.run_pseudoexperiments()
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
        if cl < 0.1 and not c90: c90 = i
        if cl<0.05:
            print "C90:",c90
            print "c95:",i
            if stop_95:
                tup.close()
                return c90, i
    tup.close()

#do_scan("LHCb_CMS_CDF_Hi")
#CL = DoCL(1e-8, syst=0)
#from array import array as afC
#x = afC("d",[0.])
#CL.bayes_heinrich(.9, x,afC("d",[0.]))#,1000, afC("d",[0.]),afC("d",[0.]),afC("d",[0.]),afC("d",[0.]),afC("d",[0.]))

def read_q(line):
    words = line.split()
    qb = words[4]
    qs = words[5]
    return float(qb), float(qs)

def do_Qplot(f, CL):
    #CL.setpxprintflag(1)
    
    hs = TH1F("A","A",100,-50,50)
    hb = TH1F("B","B",100,-50,50)
    f = file(f)
    lines = f.readlines()
    for line in lines:
        if line.find(" Null"):continue
        qb,qs = read_q(line)
        hb.Fill(qb)
        hs.Fill(qs)
        
    
    return hs, hb

#CL = DoCL(1.5e-08,0,0)
#CL.run_pseudoexperiments()
#print CL.ts()


def do_Qs(f):
    #CL.setpxprintflag(1)
    
    xs = {}
    xb = {}
    f = file(f)
    lines = f.readlines()
    for line in lines:
        if line.find("ps for BR") == 0:
            names = line.split()
            br = float(names[-1])
            xs[br] = []
            xb[br] = []
            
        if line.find(" Null"):continue
        qb,qs = read_q(line)
        xs[br].append(qs)
        xb[br].append(qb)
        
    
    return xs, xb

def do_psCLsb(xs,xb):
    clsb = {}; cls = {}
    for br in xs.keys():
        qs = xs[br]
        qb = xb[br]
        qs.sort()
        qb.sort()
        x_obs, x_1sm, x_1sp = median(qb)[0], median(qb)[1], median(qb)[2]
        print x_obs, x_1sm, x_1sp
        x0, x1, x2 = 0, 0, 0
        for entry in qs:
            if entry > x_obs: x0+=1
            if entry > x_1sm: x1+=1
            if entry > x_1sp: x2+=1
            
        clsb[br] = [x0 *1./len(qs), x1 *1./len(qs),x2 *1./len(qs)]
    for key in clsb.keys():
        cls[key] = [clsb[key][0]/.5, clsb[key][1]/.84, clsb[key][2]/.16]
    return clsb, cls


#def prepare_banana(): return "banana"

## from SomeUtils.numericFunctionClass import *
## ch = channelData("Bs_syst_wCMS.dat",typ = "ASCII")

## x = ch.takeKey("BR")
## y = ch.takeKey("CLs")

## x2, y2 = [], []

## for i in range(len(x)):
##     if i%10:continue
##     x2.append(x[i])
##     y2.append(y[i])

## g = NF(x2,y2)
## b = g.Draw()

def do_sensitivity(filename, stop_95 = False):
    tup = XTuple(filename, labels = ["l3s/F","l5s/F","BR/F"])
  
    print a2012.CHANNEL
    c90, c95 = 0.,0
    for j in range(200):
        i = 0.25*(1.+ 0.1*j)
        print "ps for BR:", i
        CL = DoCL(i*1e-09, syst=0)
        #CL.setpxprintflag(1)
        CL.run_pseudoexperiments()
        l3s = CL.lumi3s()
        l5s = CL.lumi5s()
       
        tup.fillItem("l3s",l3s)
        tup.fillItem("l5s",l5s)

        #tup.fillItem("CLsb",clsb)
        tup.fillItem("BR", i)
        tup.fill()
        
    tup.close()

#CL = DoCL(3e-09, syst=0)
#print CL.lumi3s()
#do_sensitivity("sensitivity_NOsys_LHCb_alone")

def sensit_curve(file1 = "sensitivity_NOsys.dat",file2 ="sensitivity_wsys.dat", l = 3,scx = 1.):
    dc = {3:"l3s",5:"l5s"}
    from dev_channelclass import channelData
    from SomeUtils.numericFunctionClass import NF
    ch1 = channelData(file1,typ = "ASCII")
    ch2 = channelData(file2,typ = "ASCII")
    y1 = ch1.takeKey("BR")
    x1 = ch1.takeKey(dc[l])
    for i in range(len(x1)):
        x1[i] = x1[i]*scx
    
    y2 = ch2.takeKey("BR")
    x2 = ch2.takeKey(dc[l])
    for i in range(len(x2)):
        x2[i] = x2[i]*scx
    f1 = NF(x1,y1)
    f2 = NF(x2,y2)
    band = TGraph()
    for i in range(f1.refSize):
        band.SetPoint(i,f1.References[i],f1(f1.References[i]))
        band.SetPoint(2*f1.refSize -i -1,f2.References[i],f2(f2.References[i]))
    band.SetFillColor(kGreen)
    band.SetFillStyle(3013)
    return band

def legend(g3,g5, h = ""):
    l = TLegend(0.75,0.75,1.,1., h)
   
    l.AddEntry(g5,"5#sigma discovery","f")
    l.AddEntry(g3,"3#sigma evidence","f")
    return l


def scan_params(model):
    for i in range(10000):
        model.varysyst()
        model.print_nuisance_params()
def read_params(text):
    dc = {}
    f = file(text,"r")
    lines = f.readlines()
    start = 1
    names = ["Nsb0_2012"," i_0_2012","Nsb1_2012","i_1_2012","Nsb2_2012"," i_2_2012","Nsb3_2012","i_3_2012","Nsb4_2012"," i_4_2012","Nsb5_2012","i_5_2012","Nsb6_2012"," i_6_2012","Nsb7_2012","i_7_2012"]

    for name in names:
        dc[name] = TH1F(name,name, 100,-5,5)
        
    for line in lines:
        words = line.split()
        if len(words)<3:continue
        if words[1] in names: dc[words[1]].Fill(float(words[2]))
    return dc

def scan_yields(mod, syst = 1):
    d = {}
    mod.undo_nuisance_response()
    w = a2012.hbpdf.ProjectionX()
    w.Scale(a2012.Nb)
    for i in range(8):
        xmax = max(a2012.Nb_sb_p[i]*a2012.hbpdf_sb_p[i].ProjectionX().GetBinContent(i+1)+3*sqrt(w.GetBinContent(i+1)), 10)
        xmin = a2012.Nb_sb_n[i]*a2012.hbpdf_sb_n[i].ProjectionX().GetBinContent(i+1)-3*sqrt(w.GetBinContent(i+1))
        if i == 7: xmin = 0
        print i, xmin, xmax
        d[i]  = TH1F("w","w",int(xmax-xmin)+1,xmin-0.5,xmax+0.5)
        d[i].SetLineColor(kCyan)
    for i in range(10000):
        h3 = a2012.DataHist.Clone()
        if syst: mod.varysyst()
        mod.single_pseudoexperiment(h3)
        h4 = h3.ProjectionX()
        for j in range(h4.GetNbinsX()):
            d[j].Fill(h4.GetBinContent(j+1))
    return d
def expected_fluct_yields_nok(sb, N0, N1):
    Nsb = a2012.Nsb
    h = TH1F("A","A", N1-N0+1 , N0-0.5,N1+0.5)
    m0 = Nsb[sb] + 0.5
    Binning = a2012.Binning
    ## def bkg_in_bin(x,y,Nsb,idx,  a = a2012.M_min, b =a2012.M_b , c = a2012.M_c, d = a2012.M_max):
##         kl = idx
##         print kl, a, b, c, d
##         iDk = 1./(exp(kl*a) +exp(kl*c) - exp(kl*b) - exp(kl*d))
##         Nxy = iDk*Nsb*(exp(kl*x)-exp(kl*y))
##         return Nxy
    from scipy import random as rnd
    for i in range(10000):
        nsb = rnd.poisson(m0)
        #print Binning["Bmass"][0], Binning["Bmass"][-1],nsb,a2012.idx[sb]
        h.Fill(rnd.poisson(a2012.bkg_in_bin( float(Binning["Bmass"][0]),float( Binning["Bmass"][-1]),float(nsb),float(a2012.idx[sb]), a = a2012.M_min[sb], d = a2012.M_max[sb] )  ))
    return h
                          

        
        
#BREAK
#do_scan(os.environ["BS2MUMUROOT"]+ "/python/Bs2MuMu/SMB_SYST"+str(SYST)+"_MISID"+str(a2012.MISID) + "_sBk" + str(a2012.sigma_Bk) + "_sB" + str(a2012.sigma_B) + "_shh"+str(a2012.sigma_hh) + "_"+a2012.pfunc+"_Istyle"+ str(ISTYLE)+"_ATLAS_PROF"+str(PROFILEATLAS) + "_" + CHANNEL)
#do_scan(os.environ["HOME"] + "/vol5/" + CHANNEL +  "TH_2012"*use_2012+ "_autum"*use_autum+ "_2010"*use_2010+ "_atlas"*use_atlas+ "_cms"*use_cms + "_cdf"*use_cdf+"_SYST"+ str(SYST) + "job"+ str(st0)+".dat")


from SomeUtils.numericFunctionClass import *
from triggerclass import *
def getOutput(filename):
    ch = channelData(filename, typ="ASCII")
    #ts = ch.takeKey("ts")
    #ts0 = min(ts)
    for i in range(len(ch)):
        ch[i]["evt"] = i
        ch[i]["oCLsb"] = 1-ch[i]["CLsb"]
        ch[i]["oCLs"] = 1-ch[i]["CLs"]
        #ch[i]["ets"] = exp(-(ch[i]["ts"]-ts0))
    x = ch.takeKey("BR")
    y0 = ch.takeKey("oCLsb")
    y1 = ch.takeKey("oCLs")
    #y = ch.takeKey("ets")
    f1 = NF(x,y0)
    #f2 = NF(x,y)
    f3 = NF(x,y1)
    return f1.derivativeF(), f3.derivativeF(),ch


def prepare_banana(f):
    w = getOutput(f)
    ch = w[-1]
    g0,g1 = TGraph(), TGraph()
    banana1,banana2 = TGraph(),TGraph()
    N = len(ch)
    i = 0
    for entry in ch:
        g0.SetPoint(i,entry["BR"], entry["CLs_exp_b_med"])
        g1.SetPoint(i,entry["BR"], entry["CLs"])
        ## gp1.SetPoint(i,entry["BR"], entry["CLs_exp_b_p1"])
##         gm1.SetPoint(i,entry["BR"], entry["CLs_exp_b_m1"])
##         gp2.SetPoint(i,entry["BR"], entry["CLs_exp_b_p2"])
##         gm2.SetPoint(i,entry["BR"], entry["CLs_exp_b_m2"])
        
        banana1.SetPoint(i,entry["BR"], entry["CLs_exp_b_p1"])
        banana1.SetPoint(2*N-i-1,entry["BR"], entry["CLs_exp_b_m1"])
        banana2.SetPoint(i,entry["BR"], entry["CLs_exp_b_p2"])
        banana2.SetPoint(2*N-i-1,entry["BR"], entry["CLs_exp_b_m2"])
        i +=1
    banana2.SetFillColor(kGreen)
    banana2.SetFillStyle(3013)
    banana1.SetFillColor(kYellow)
    banana1.SetFillStyle(3013)
    g0.SetLineStyle(9)
    
    
    return g0, g1, banana1, banana2

## from triggerclass import *

def Bayes(filename):
    tup = XTuple(filename, labels = ["BR/F", "CL/F"])
    #print a2010.CHANNEL
    #print a2011.CHANNEL
    CL = DoCL(1*1e-09, 50000,syst=0)
    c90, c95 = 0.,0
    from array import array as afC
    x = afC("d",[0.])
    for i in range(98):
        cl = 0.01*(1+i)
        CL.bayes_heinrich(cl, x,afC("d",[0.]))
        print "BR sc factor: ",x[0],"CL",cl
        tup.fillItem("BR",x[0])
        tup.fillItem("CL",cl)
        tup.fill()
    tup.close()

#Bayes("Beaujean_Bayes_2012_nosyst")
