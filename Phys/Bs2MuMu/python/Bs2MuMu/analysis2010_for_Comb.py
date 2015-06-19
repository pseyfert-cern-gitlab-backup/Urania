#! /usr/bin/env python
from ROOT import *
from MCLimit import *

from smartpyROOT import *
from array import array as afC
from XTuple import XTuple
from SomeUtils.dataManage import rms
from scipy import double
#from BsMuMuPy.pyAna.CLclass import *
from SomeUtils.alyabar import *
import signalPDF 
import bkgPDF
from Bs2MuMuParams import toytable_GLAna2010 as TheTable
from functions_for_finalanalysis import *
import sys, os

MC_GL = 0
MISID = 0.   ### Inside the tight window
s_MISID = 0.1
SM = 1
CHANNEL = "Bs"

glname = "GLKsm_MC10sb."

if CHANNEL == "Bd":
    mean = double(5275.01) #(Bd)
    s_mean = 3*0.87 
else:
    mean = double(5363.1)#
    s_mean = 3*1.5
#s_mean = 0.87 (Bd)


glbins = doNbins(4,0., 1)
massbins = doNbins(6,mean-60., mean + 60.)

filename = '/afs/cern.ch/project/lbcern/vol5//diegoms/NTuples/merged/stp12WM_merged'

misidname = "/scratch/diegoms/NTuples/MC/misid_fromhh"
#misidname = "/scratch/diegoms/NTuples/MC/misid_from_muh"

datatree, datafile = getTuple(filename, thing = "Bs2MuMu")
tmis, fmis = getTuple(misidname)

Binning = {glname : afC('f',glbins), "Bmass": afC('f',massbins)}

M_min = {0:5366.3-600.,1:5366.3-600,2:5366.3-1200,  3:5366.3-1200}              #max(datatree.GetMinimum("Bmass"), 4769.6)}
M_max = {0:5366.3+600.,1:5366.3+600,2:5366.3+1200,  3:5366.3+1200}   

M_b = 5215.01     # Binning["Bmass"][0] ### 5200
M_c = 5423.10    

def bkg_in_bin(x,y,Nsb,idx,  a = M_min, b = M_b , c = M_c, d = M_max):#, b = Binning["Bmass"][0], c = Binning["Bmass"][1]):

    kl = idx
    iDk = 1./(exp(kl*a) +exp(kl*c) - exp(kl*b) - exp(kl*d))
    Nxy = iDk*Nsb*(exp(kl*x)-exp(kl*y))
    return Nxy

def fillB(Nsb, idx,name):
    hbpdf = TH2D(name,name,len(Binning[glname])-1,Binning[glname],  len(Binning["Bmass"]) -1, Binning["Bmass"])
    N = 0.
    for i in range(hspdf.GetNbinsX()):
       
        for k in range(hbpdf.GetNbinsY()):
           
            Nxy = bkg_in_bin(Binning["Bmass"][k],Binning["Bmass"][k+1], Nsb[i],idx[i], a = M_min[i], d = M_max[i])
            hbpdf.SetBinContent(i+1, k+ 1, Nxy)
            N+=Nxy

    hbpdf.Scale(double(1.)/hbpdf.GetSum()) ## normalize once again
    return N, hbpdf

def fillS(fgl, masspdf, name):
    hspdf = TH2D(name,name,len(Binning[glname])-1,Binning[glname],  len(Binning["Bmass"]) -1, Binning["Bmass"])
    #f = {0:f1, 1:1-f1}
    for i in range(hspdf.GetNbinsX()):
        for k in range(hspdf.GetNbinsY()):
            mk, merr_k = masspdf(Binning["Bmass"][k],Binning["Bmass"][k+1])
            hspdf.SetBinContent(i+1, k+ 1, fgl[i]*mk)
    hspdf.Scale(double(1.)/hspdf.GetSum())
    return hspdf
           

##############################
### NORMALIZATION

c_phi = 10.5e-09
sc_phi = 2.9e-09    

c_bu = 2.27e-09
sc_bu = 0.18e-9    #

b_kpi = 1.89e-06
sb_kpi = 3.1e-07


Ntis_hh = 955.
sNtis_hh = 119 #

fdfs = 3.75
s_fdfs = 0.29 ## update

c_kpi, sc_kpi = do_kpi_coef(b_kpi,sb_kpi,Ntis_hh, sNtis_hh)

alpha, s_alpha = calculateNormalizationFactor( c_bu, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)

#############################################################################
# GL pdf

N_sig_gl = [0., 225., 166., 232.]
sN_sig_gl = [0., sqrt(50.**2 + 69**2) , sqrt(18.**2 + 32**2),sqrt(18.**2 + (0.03*N_sig_gl[3])**2)]
justine = {"T":1., 0:1., 1: 0.986, 2:.990 , 3: 1.08}

for i in range(len(N_sig_gl)):
    N_sig_gl[i] =  N_sig_gl[i] *1./justine[i]
    sN_sig_gl[i] =  sqrt( (sN_sig_gl[i] *1./justine[i]) **2 + (0.04*N_sig_gl[i])**2 +(0.05*N_sig_gl[i])**2)
    
fgl = convert_tofractions(N_sig_gl, Ntis_hh*1./justine["T"])


################################################################################
## Signal Mass pdf parameters

mean = mean #### se at the begining of the file
s_mean = s_mean

sigma = 26.71
s_sigma = 3*0.95

a = 2.11
s_a = 3*0.05
sMpdf = signalPDF.massDescriptor(mean, sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 

#######################################################################
#### yields in sidebands
Nsb = {}  ## central value
sNsbp = {} ## upper poisson error
sNsbn = {} ## lower posission error

Nsb = {0:TheTable.SbGL1,1:TheTable.SbGL2,2:TheTable.SbGL3,3:TheTable.SbGL4}
for i in range(4):
    #ct0 = glname +">"+str(Binning[glname][i]) + "&& " + glname + "<"+str(Binning[glname][i+1])
    #Nsb[i] = Thdatatree.GetEntries(ct0 +" && Bmass > " + str(M_min[i]) + "&&  Bmass< "+ str(M_max[i]) + " && (Bmass< "+ str(M_b) + "  || Bmass> " + str(M_c) +")")
    sNsbp[i], sNsbn[i] = poissonErrors(Nsb[i])

#####################################################
### exponential index in sidebands

idx = [ -7.48e-04, -0.00136, -0.00229 , -0.00415]  
s_idx = [ 5.10e-05, 3.5e-04,2.8e-04,9.1e-04]
        
###########################################
##### Signal 2D  PDF's

hspdf = fillS(fgl, sMpdf, "hspdf 2010")
#hspdf.Scale(double(1.)/double(hspdf.GetSum()))
###########################################
#### Bkg 2D  PDF's

Nb, hbpdf = fillB(Nsb,idx,"hbpdf 2010")


########################################
# SIGNAL NUISSANCE PARAMETERS        ###
########################################

## c_bu
c_bup, c_bun = c_bu + sc_bu,c_bu - sc_bu 
alpha_bup, s_alphaz = calculateNormalizationFactor( c_bup, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)
alpha_bun, s_alphaz = calculateNormalizationFactor( c_bun, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)

## c_phi
c_phip, c_phin = c_phi + sc_phi, c_phi - sc_phi
alpha_phip, s_alphaz = calculateNormalizationFactor( c_bu, c_phip, c_kpi,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)
alpha_phin, s_alphaz  = calculateNormalizationFactor( c_bu, c_phin, c_kpi,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)

## b_kpi
b_kpip, b_kpin = b_kpi + sb_kpi, b_kpi - sb_kpi
c_kpip, sc_kpip = do_kpi_coef(b_kpip,sb_kpi,Ntis_hh, sNtis_hh)
c_kpin, sc_kpin = do_kpi_coef(b_kpin,sb_kpi,Ntis_hh, sNtis_hh)

alpha_kpip, s_alphaz  = calculateNormalizationFactor( c_bu, c_phi, c_kpip,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)
alpha_kpin, s_alphaz  = calculateNormalizationFactor( c_bu, c_phi, c_kpin,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)

## fdfs
fdfsp, fdfsn = fdfs + s_fdfs, fdfs - s_fdfs
alpha_fp, s_alphaz  = calculateNormalizationFactor( c_bu, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, fdfsp, s_fdfs, channel = CHANNEL)
alpha_fn, s_alphaz  = calculateNormalizationFactor( c_bu, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, fdfsn, s_fdfs, channel = CHANNEL)

## Ntis_hh

#Ntis_hhp, Ntis_hhn = Ntis_hh + 2*sNtis_hh, Ntis_hh - 2*sNtis_hh
c_kpiTp, sc_kpip = do_kpi_coef(b_kpi,sb_kpi,Ntis_hh + sNtis_hh, sNtis_hh)
c_kpiTn, sc_kpin = do_kpi_coef(b_kpi,sb_kpi,Ntis_hh - sNtis_hh, sNtis_hh)

alpha_Tp, s_alphaz  = calculateNormalizationFactor( c_bu, c_phi, c_kpiTp,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)
alpha_Tn, s_alphaz  = calculateNormalizationFactor( c_bu, c_phi, c_kpiTn,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)

fgl_Tp = convert_tofractions(N_sig_gl, (Ntis_hh + sNtis_hh)*1./justine["T"])
fgl_Tn = convert_tofractions(N_sig_gl, (Ntis_hh - sNtis_hh)*1./justine["T"])

hspdf_Tp = fillS(fgl_Tp, sMpdf, "hspdf_Tp_2010")
hspdf_Tn = fillS(fgl_Tn, sMpdf, "hspdf_Tn_2010")

### N gl 2, 3, 4

N_gl_2p = [ N_sig_gl[0],  N_sig_gl[1] +  2*sN_sig_gl[1], N_sig_gl[2],  N_sig_gl[3]]
N_gl_2n = [ N_sig_gl[0],  N_sig_gl[1] -  2*sN_sig_gl[1], N_sig_gl[2],  N_sig_gl[3]]
fgl_2p = convert_tofractions(N_gl_2p, Ntis_hh*1./justine["T"])
fgl_2n = convert_tofractions(N_gl_2n, Ntis_hh*1./justine["T"])

hspdf_2p = fillS(fgl_2p, sMpdf, "hspdf_2p_2010")
hspdf_2n = fillS(fgl_2n, sMpdf, "hspdf_2n_2010")

N_gl_3p = [ N_sig_gl[0],  N_sig_gl[1] , N_sig_gl[2] +  2*sN_sig_gl[2],  N_sig_gl[3]]
N_gl_3n = [ N_sig_gl[0],  N_sig_gl[1] , N_sig_gl[2] -  2*sN_sig_gl[2],  N_sig_gl[3]]
fgl_3p = convert_tofractions(N_gl_3p, Ntis_hh*1./justine["T"])
fgl_3n = convert_tofractions(N_gl_3n, Ntis_hh*1./justine["T"])

hspdf_3p = fillS(fgl_3p, sMpdf, "hspdf_3p_2010")
hspdf_3n = fillS(fgl_3n, sMpdf, "hspdf_3n_2010")

N_gl_4p = [ N_sig_gl[0],  N_sig_gl[1] , N_sig_gl[2] ,  N_sig_gl[3] +  2*sN_sig_gl[3]]
N_gl_4n = [ N_sig_gl[0],  N_sig_gl[1] , N_sig_gl[2] ,  N_sig_gl[3] -  2*sN_sig_gl[3]]
fgl_4p = convert_tofractions(N_gl_4p, Ntis_hh*1./justine["T"])
fgl_4n = convert_tofractions(N_gl_4n, Ntis_hh*1./justine["T"])

hspdf_4p = fillS(fgl_4p, sMpdf, "hspdf_4p_2010")
hspdf_4n = fillS(fgl_4n, sMpdf, "hspdf_4n_2010")


### mas paramters

sMpdf_mp = signalPDF.massDescriptor(mean + s_mean, sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_mn = signalPDF.massDescriptor(mean - s_mean, sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_sp = signalPDF.massDescriptor(mean, sigma + s_sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_sn = signalPDF.massDescriptor(mean, sigma - s_sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_ap = signalPDF.massDescriptor(mean, sigma, a + s_a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_an = signalPDF.massDescriptor(mean, sigma, a - s_a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 

hspdf_mp = fillS(fgl, sMpdf_mp, "hspdf_mp_2010")
hspdf_mn = fillS(fgl, sMpdf_mn, "hspdf_mn_2010")
hspdf_sp = fillS(fgl, sMpdf_mp, "hspdf_sp_2010")
hspdf_sn = fillS(fgl, sMpdf_mn, "hspdf_sn_2010")
hspdf_ap = fillS(fgl, sMpdf_mp, "hspdf_ap_2010")
hspdf_an = fillS(fgl, sMpdf_mn, "hspdf_an_2010")

## CB systematics

h_mass_mcpdfp = TH2D("mc massp 2010", "mc massp 2010", len(Binning[glname])-1,Binning[glname], len(Binning["Bmass"]) -1, Binning["Bmass"])
h_mass_mcpdfn = TH2D("mc massn 2010", "mc massn 2010", len(Binning[glname])-1,Binning[glname], len(Binning["Bmass"]) -1, Binning["Bmass"])
delta_mass_mc = [0.063, -0.054, 0.018,0.033,-0.037,-0.056]
hcb = hspdf.ProjectionY()
hglst = hspdf.ProjectionX()
for i in range(6):
    for j in range(4):
        h_mass_mcpdfp.SetBinContent(j+1, i+1, hglst.GetBinContent(j+1)*hcb.GetBinContent(i+1)*(1+delta_mass_mc[i]))
        h_mass_mcpdfn.SetBinContent(j+1, i+1, hglst.GetBinContent(j+1)*hcb.GetBinContent(i+1)*(1-delta_mass_mc[i]))
        
h_mass_mcpdfp.Scale(double(1.)*1./double(h_mass_mcpdfp.GetSum()))
h_mass_mcpdfn.Scale(double(1.)*1./double(h_mass_mcpdfn.GetSum()))




###################################
## BKG NUISANCE PARAMETERS      ###
###################################

### sidebands yields
nnsb1p, nnsb1n = fluctuateSidebands(Nsb, {0:sNsbp[0], 1:0, 2:0, 3:0}, {0:sNsbn[0], 1:0, 2:0, 3:0})  #sideband 1
nnsb2p, nnsb2n = fluctuateSidebands(Nsb, {0:0, 1:sNsbp[1], 2:0, 3:0}, {0:0, 1:sNsbn[1], 2:0, 3:0})  #sideband 2
nnsb3p, nnsb3n = fluctuateSidebands(Nsb, {0:0, 1:0, 2:sNsbp[2], 3:0}, {0:0, 1:0, 2:sNsbn[2], 3:0})  #sideband 3
nnsb4p, nnsb4n = fluctuateSidebands(Nsb, {0:0, 1:0, 2:0, 3:sNsbp[3]}, {0:0, 1:0, 2:0, 3:sNsbn[3]})  #sideband 4


Nb_sb1_1, hbpdf_sb1_1 = fillB(nnsb1p, idx, "hbpdf_sb1_1_2010")
Nb_sb1_2, hbpdf_sb1_2 = fillB(nnsb1n, idx, "hbpdf_sb1_2_2010")

Nb_sb2_1, hbpdf_sb2_1 = fillB(nnsb2p, idx, "hbpdf_sb2_1_2010")
Nb_sb2_2, hbpdf_sb2_2 = fillB(nnsb2n, idx, "hbpdf_sb2_2_2010")

Nb_sb3_1, hbpdf_sb3_1 = fillB(nnsb3p, idx, "hbpdf_sb3_1_2010")
Nb_sb3_2, hbpdf_sb3_2 = fillB(nnsb3n, idx, "hbpdf_sb3_2_2010")

Nb_sb4_1, hbpdf_sb4_1 = fillB(nnsb4p, idx, "hbpdf_sb4_1_2010")
Nb_sb4_2, hbpdf_sb4_2 = fillB(nnsb4n, idx, "hbpdf_sb4_2_2010")

### bkg exponential index

idx1p= [idx[0] + s_idx[0], idx[1], idx[2], idx[3]]
idx1n= [idx[0] - s_idx[0], idx[1], idx[2], idx[3]]

idx2p= [idx[0], idx[1] + s_idx[1], idx[2], idx[3]]
idx2n= [idx[0], idx[1] - s_idx[1], idx[2], idx[3]]

idx3p= [idx[0], idx[1], idx[2] + s_idx[2], idx[3]]  
idx3n= [idx[0], idx[1], idx[2] - s_idx[2], idx[3]]

idx4p= [idx[0], idx[1], idx[2], idx[3] + s_idx[3]]  
idx4n= [idx[0], idx[1], idx[2], idx[3] - s_idx[3]]

#idx1p= [idx[0]+ s_idx[0], idx[1]+ s_idx[0], idx[2] + s_idx[0], idx[3] + s_idx[0]]  ### All fluctuaded consistently
#idx1n= [idx[0]- s_idx[0], idx[1]- s_idx[0], idx[2] - s_idx[0], idx[3] - s_idx[0]]  ### All fluctuaded consistently


Nb_i1_1, hbpdf_i1_1 = fillB(Nsb, idx1p, "hbpdf_i1_1_2010")
Nb_i1_2, hbpdf_i1_2 = fillB(Nsb, idx1n, "hbpdf_i1_2_2010")

Nb_i2_1, hbpdf_i2_1 = fillB(Nsb, idx2p, "hbpdf_i2_1_2010")
Nb_i2_2, hbpdf_i2_2 = fillB(Nsb, idx2n, "hbpdf_i2_2_2010")

Nb_i3_1, hbpdf_i3_1 = fillB(Nsb, idx3p, "hbpdf_i3_1_2010")
Nb_i3_2, hbpdf_i3_2 = fillB(Nsb, idx3n, "hbpdf_i3_2_2010")

Nb_i4_1, hbpdf_i4_1 = fillB(Nsb, idx4p, "hbpdf_i4_1_2010")
Nb_i4_2, hbpdf_i4_2 = fillB(Nsb, idx4n, "hbpdf_i4_2_2010")



### Create Bkg hypothesis

bkg_no_syst = csm_template(0)#8)
bkg = csm_template(8)
bkg.set_np("Nsb1_2010", (Nb_sb1_2-Nb)/Nb, (Nb_sb1_1-Nb)/Nb, hbpdf_sb1_1, 1., hbpdf_sb1_2,-1.) ## void csm_template::set_np(char *name, Double_t low, Double_t high, TH1 *h_high, Double_t sigma_high, TH1 *h_low, Double_t sigma_low)
bkg.set_np("Nsb2_2010", (Nb_sb2_2-Nb)/Nb, (Nb_sb2_1-Nb)/Nb, hbpdf_sb2_1, 1., hbpdf_sb2_2,-1.)


bkg.set_np("Nsb3_2010", (Nb-Nb_sb3_2)/Nb, (Nb-Nb_sb3_1)/Nb, hbpdf_sb3_1, 1., hbpdf_sb3_2,-1.)
bkg.set_np("Nsb4_2010", (Nb-Nb_sb4_2)/Nb, (Nb-Nb_sb4_1)/Nb, hbpdf_sb4_1, 1., hbpdf_sb4_2,-1.)

bkg.set_np("i_2010", (Nb-Nb_i1_2)/Nb, (Nb-Nb_i1_1)/Nb, hbpdf_i1_1, 1., hbpdf_i1_2,-1.)

bkg.set_np("i2_2010", (Nb-Nb_i2_2)/Nb, (Nb-Nb_i2_1)/Nb, hbpdf_i2_1, 1., hbpdf_i2_2,-1.)
bkg.set_np("i3_2010", (Nb-Nb_i3_2)/Nb, (Nb-Nb_i3_1)/Nb, hbpdf_i3_1, 1., hbpdf_i3_2,-1.)
bkg.set_np("i4_2010", (Nb-Nb_i4_2)/Nb, (Nb-Nb_i4_1)/Nb, hbpdf_i4_1, 1., hbpdf_i4_2,-1.)

bkg.make(hbpdf,Nb, 0,0,"2010")
bkg_no_syst.make(hbpdf,Nb, 0,0,"2010")


#fDat = TFile("/afs/cern.ch/user/d/diegoms/public/for_Mathieu/2010.root")
#DataHist = fDat.Get("data 2010")


fdata = TFile(os.environ["BS2MUMUPARAMSROOT"]+"/histos/Data2010Bs.root")
DataHist = fdata.Get("data 2010")#FitInBinning_2D(datatree,Binning, glname = glname, name = "data 2010")

#nul = csm_model()
#nulpe = csm_model()
        
#bkg.add_to(nulpe)
#bkg_no_syst.add_to(nul)

if MISID: 
    misid = csm_template(0)
    hmisid = FitInBinning_2D(tmis,Binning, glname = glname, name = "missid 2010")
    misid.make(hmisid,MISID, 1,0,"2010")
 #   misid.add_to(nul)
  #  misid.add_to(nulpe)

name_cu = "c_u"
name_cphi = "c_phi"
name_ckpi = "c_kpi"
name_fdfs = "fdfs"
name_kpiT = "c_kpiT_2010"
name_n2 = "n2_2010"
name_n3 = "n3_2010"
name_n4 = "n4_2010"
name_m = "m_2010"
name_s = "s_2010"
name_a = "a_2010"

if SM:
######################
## SM              ###
######################

    BR_SM = 3.2e-09 
    sBR_SM = 0.2e-09 

    sm = csm_template(12)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
    sm_no_syst = csm_template(0)

    sm.set_np(name_cu,(alpha_bun-alpha)/alpha, (alpha_bup - alpha)/alpha,NULL,1., NULL, -1.)  
    sm.set_np(name_m,0., 0.,hspdf_mp,3., hspdf_mn, -3.)
    sm.set_np(name_s,0., 0.,hspdf_sp,3, hspdf_sn, -3.)
    sm.set_np(name_a,0., 0.,hspdf_ap,3., hspdf_an, -3.)

    sm.set_np(name_cphi,(alpha_phin-alpha)/alpha, (alpha_phip - alpha)/alpha,NULL, 1., NULL, -1.)
    sm.set_np(name_ckpi,(alpha_kpin-alpha)/alpha, (alpha_kpip - alpha)/alpha,NULL, 1., NULL, -1.)
    sm.set_np(name_fdfs,(alpha_fn-alpha)/alpha, (alpha_fp - alpha)/alpha,NULL, 1., NULL, -1.)

    sm.set_np(name_kpiT,(alpha_Tn-alpha)/alpha, (alpha_Tp - alpha)/alpha,hspdf_Tp, 3., hspdf_Tn, -3.)

    sm.set_np(name_n2,0., 0.,hspdf_2p, 3., hspdf_2n, -3.)
    sm.set_np(name_n3,0., 0.,hspdf_3p, 3., hspdf_3n, -3.)
    sm.set_np(name_n4,0., 0.,hspdf_4p, 3., hspdf_4n, -3.)
    sm.set_np("SM",-sBR_SM/BR_SM, sBR_SM/BR_SM,NULL, 1., NULL, -1.)

    sm.make(hspdf,BR_SM/alpha,0,0, "2010")
    sm_no_syst.make(hspdf,BR_SM/alpha,0,0, "2010")
    
dc2010 = {}

def DoSigModel(ns, dc = dc2010):   
    dc[ns] = csm_template(12)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
    dc[str(ns) + "_no_syst"] = csm_template(0)
    
    dc[ns].set_np(name_cu,(alpha_bun-alpha)/alpha, (alpha_bup - alpha)/alpha,NULL,1., NULL, -1.)  ### void csm_template::set_np(char *name, Double_t low, Double_t high, TH1 *h_high, Double_t sigma_high, TH1 *h_low, Double_t sigma_low)
    dc[ns].set_np(name_m,0., 0.,hspdf_mp,3., hspdf_mn, -3.)
    dc[ns].set_np(name_s,0., 0.,hspdf_sp,3., hspdf_sn, -3.)
    dc[ns].set_np(name_a,0., 0.,hspdf_ap,3., hspdf_an, -3.)


    dc[ns].set_np(name_cphi,(alpha_phin-alpha)/alpha, (alpha_phip - alpha)/alpha,NULL, 1., NULL, -1.)
    dc[ns].set_np(name_ckpi,(alpha_kpin-alpha)/alpha, (alpha_kpip - alpha)/alpha,NULL, 1., NULL, -1.)
    dc[ns].set_np(name_fdfs , (alpha_fn-alpha)/alpha, (alpha_fp - alpha)/alpha,NULL, 1., NULL, -1.)
    
    dc[ns].set_np(name_kpiT,(alpha_Tn-alpha)/alpha, (alpha_Tp - alpha)/alpha,hspdf_Tp, 2., hspdf_Tn, -2.)
    

    dc[ns].set_np(name_n2,0., 0.,hspdf_2p, 2., hspdf_2n, -2.)
    dc[ns].set_np(name_n3,0., 0.,hspdf_3p, 2., hspdf_3n, -2.)
    dc[ns].set_np(name_n4,0., 0.,hspdf_4p, 2., hspdf_4n, -2.)
    dc[ns].set_np("CB model_2010",0., 0.,h_mass_mcpdfp, 1., h_mass_mcpdfn, -1.)
   
    
    #BREAK
    dc[ns].make(hspdf,ns,0,1, "2010")
    dc[str(ns) + "_no_syst"].make(hspdf,ns,0,1, "2010")
    return dc
    ## print "ooooo"
##     bkg.add_to(testpe)
##     bkg_no_syst.add_to(test)
    
##     if MISID:
##         misid.add_to(testpe)
##         misid.add_to(test)
        
##     dc[ns].add_to(testpe)
##     dc[str(ns) + "_no_syst"].add_to(test)
##     #return test
    
    
##     CL = mclimit_csm()
##     CL.set_null_hypothesis(nul)
##     CL.set_test_hypothesis(test)
##     CL0 = mclimit_csm()
##     CL0.set_null_hypothesis(nul)
##     CL0.set_test_hypothesis(test)
    
##     CL.set_null_hypothesis_pe(nulpe)
##     CL.set_test_hypothesis_pe(testpe)
##     CL0.set_null_hypothesis_pe(nul) #### no syst
##     CL0.set_test_hypothesis_pe(test)
##     CL.set_datahist(DataHist, "TheData")
##     CL0.set_datahist(DataHist, "TheData")
##     CL.set_npe(20000)
##     CL0.set_npe(20000)
##     return CL, test, testpe, CL0
   
##     CL.run_pseudoexperiments()
## #    print "\\\\\\"
##     cls = CL.cls()
##     clb = CL.clb()
##     print "\\\\\\"
##     #tup.fillItem("br",br)
##     #tup.fillItem("cls",CL.cls())
##     #tup.fillItem("clb",CL.clb())
##     #tup.fill()
    
##     del(CL)
##     print "1"
##     del(test)
##     print 2
##     #del(sig)
##     #print 3
    
   # return cls, clb
#STOP
