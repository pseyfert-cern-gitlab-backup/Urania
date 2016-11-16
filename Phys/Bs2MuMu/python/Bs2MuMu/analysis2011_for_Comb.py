#! /usr/bin/env python

#############################################
# 2011                                #######
#############################################

from ROOT import *
from MCLimit import *

from smartpyROOT import *
from array import array as afC
from XTuple import XTuple
from SomeUtils.dataManage import rms
from scipy import double

from SomeUtils.alyabar import *
import signalPDF 
import bkgPDF

from functions_for_finalanalysis import *
from Bs2MuMuParams import toytable_Autumn2011 as TheTable
import sys, os


CHANNEL = "Bs"
SM = 0
#
glname = "BDTflatNEW"

if CHANNEL == "Bs":
    mean = TheTable.MassMeanBs
    s_mean = 3*TheTable.MassMeanErrBs
    MISID = TheTable.MisIDN * TheTable.MisIDfBs   ### Inside the tight window
    
    s_MISID = TheTable.MisIDNErr * TheTable.MisIDfBs
    s_MISID_2 = -TheTable.MisIDN * TheTable.MisIDfErrBs ### from mass pdf. The minus sign is just to have consistency with the pdf used. "unsmeared pdf" -> LOWER yield in Bs.

    
elif CHANNEL == "Bd":
    mean = TheTable.MassMeanBd
    s_mean = 3*TheTable.MassMeanErrBd
    MISID = TheTable.MisIDN * TheTable.MisIDfBd   ### Inside the tight window
    s_MISID = TheTable.MisIDNErr * TheTable.MisIDfBd
    s_MISID_2 = TheTable.MisIDN * TheTable.MisIDfErrBd ### from mass pdf. The minus sign is just to have consistency with the pdf used. "unsmeared pdf" -> LOWER yield in Bs.
    

glbins = doNbins(4,0., 1)
massbins = doNbins(6,mean-60., mean + 60.)

filename = '~/vol5/Bs2mumu341'

misidname = "/afs/cern.ch/user/d/diegoms/vol5/MCbhh_mixed_X_misidp_rnd0.0"
misidname_o = "/afs/cern.ch/user/d/diegoms/vol5/MCbhh_mixed_X_misidp_worseall_rnd0.0"


datatree, datafile = getTuple(filename, thing = "Bs2MuMu")
tmis, fmis = getTuple(misidname)
tmis_o, fmis_o = getTuple(misidname_o)

Binning = {glname : afC('f',glbins), "Bmass": afC('f',massbins)}

M_min = {0:TheTable.GL1MassSb1,1:TheTable.GL2MassSb1,2:TheTable.GL3MassSb1,3:TheTable.GL1MassSb1}
M_max = {0:TheTable.GL1MassSb4,1:TheTable.GL2MassSb4,2:TheTable.GL3MassSb4,3:TheTable.GL1MassSb4}  


M_b = TheTable.GL1MassSb2 
M_c = TheTable.GL1MassSb3    

def bkg_in_bin(x,y,Nsb,idx,  a = M_min, b = M_b , c = M_c, d = M_max):

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

c_phi = TheTable.NormPhi
sc_phi =  TheTable.NormPhiErr    

c_bu = TheTable.NormBu
sc_bu = TheTable.NormBuErr 

b_kpi = TheTable.NormKPi
sb_kpi = TheTable.NormKPiErr 


Ntis_hh = TheTable.TisTot
sNtis_hh = TheTable.TisErrTot

fdfs = TheTable.fsfd
s_fdfs = TheTable.fsfdErr

c_kpi, sc_kpi = do_kpi_coef(b_kpi,sb_kpi,Ntis_hh, sNtis_hh)

alpha, s_alpha = calculateNormalizationFactor( c_bu, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)

#############################################################################
# GL pdf

N_sig_gl = [0., TheTable.Tis2, TheTable.Tis3, TheTable.Tis4]
sN_sig_gl = [0., TheTable.TisErr2, TheTable.TisErr3, TheTable.TisErr4]
justine = {"T":1., 0:1., 1: TheTable.Justine2, 2:TheTable.Justine3 , 3: TheTable.Justine4}

for i in range(len(N_sig_gl)):
    N_sig_gl[i] =  N_sig_gl[i] *1./justine[i]
    sN_sig_gl[i] =  sqrt( (sN_sig_gl[i] *1./justine[i]) **2 )#+ (0.04*N_sig_gl[i])**2 +(0.05*N_sig_gl[i])**2)
    
fgl = convert_tofractions(N_sig_gl, Ntis_hh*1./justine["T"])


################################################################################
## Signal Mass pdf parameters

mean = mean #### se at the begining of the file
s_mean = s_mean

if CHANNEL == "Bs":
    sigma = TheTable.MassReso
    s_sigma = 3*TheTable.MassResoErr
    a = TheTable.CBTrans
    s_a = 3*TheTable.CBTransErr

if CHANNEL == "Bd":
    sigma = TheTable.MassReso
    s_sigma = 3*TheTable.MassResoErr
    a = TheTable.CBTrans
    s_a = 3*TheTable.CBTransErr


sMpdf = signalPDF.massDescriptor(mean, sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 

#######################################################################
#### yields in sidebands
Nsb = {0: TheTable.SbGL1, 1: TheTable.SbGL2, 2:TheTable.SbGL3, 3:TheTable.SbGL4}  ## central value
sNsbp = {} ## upper poisson error
sNsbn = {} ## lower posission error

for i in range(4): sNsbp[i], sNsbn[i] = poissonErrors(Nsb[i])

#### Syst in bkg bin 1
sNsbp[0] = sqrt(sNsbp[0]**2 + (TheTable.SystBkgBin1*Nsb[0])**2)
sNsbn[0] = sqrt(sNsbn[0]**2 + (TheTable.SystBkgBin1*Nsb[0])**2)

#####################################################
### exponential index in sidebands

idx = [ TheTable.BkgMassk1, TheTable.BkgMassk2, TheTable.BkgMassk3 , TheTable.BkgMassk4]  
s_idx_p = [ TheTable.BkgMasskErrP1, TheTable.BkgMasskErrP2, TheTable.BkgMasskErrP3 , TheTable.BkgMasskErrP4]
s_idx_n = [ TheTable.BkgMasskErrN1, TheTable.BkgMasskErrN2, TheTable.BkgMasskErrN3 , TheTable.BkgMasskErrN4]  
        
###########################################
##### Signal 2D  PDF's

hspdf = fillS(fgl, sMpdf, "hspdf 2011")
#hspdf.Scale(double(1.)/double(hspdf.GetSum()))
###########################################
#### Bkg 2D  PDF's

Nb, hbpdf = fillB(Nsb,idx,"hbpdf 2011")


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

c_kpiTp, sc_kpip = do_kpi_coef(b_kpi,sb_kpi,Ntis_hh + sNtis_hh, sNtis_hh)
c_kpiTn, sc_kpin = do_kpi_coef(b_kpi,sb_kpi,Ntis_hh -sNtis_hh, sNtis_hh)

alpha_Tp, s_alphaz  = calculateNormalizationFactor( c_bu, c_phi, c_kpiTp,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)
alpha_Tn, s_alphaz  = calculateNormalizationFactor( c_bu, c_phi, c_kpiTn,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)

fgl_Tp = convert_tofractions(N_sig_gl, (Ntis_hh + 2*sNtis_hh)*1./justine["T"])
fgl_Tn = convert_tofractions(N_sig_gl, (Ntis_hh - 2*sNtis_hh)*1./justine["T"])

hspdf_Tp = fillS(fgl_Tp, sMpdf, "hspdf_Tp_2011")
hspdf_Tn = fillS(fgl_Tn, sMpdf, "hspdf_Tn_2011")

### N gl 2, 3, 4

N_gl_2p = [ N_sig_gl[0],  N_sig_gl[1] +  3*sN_sig_gl[1], N_sig_gl[2],  N_sig_gl[3]]
N_gl_2n = [ N_sig_gl[0],  N_sig_gl[1] -  3*sN_sig_gl[1], N_sig_gl[2],  N_sig_gl[3]]
fgl_2p = convert_tofractions(N_gl_2p, Ntis_hh*1./justine["T"])
fgl_2n = convert_tofractions(N_gl_2n, Ntis_hh*1./justine["T"])

hspdf_2p = fillS(fgl_2p, sMpdf, "hspdf_2p_2011")
hspdf_2n = fillS(fgl_2n, sMpdf, "hspdf_2n_2011")

N_gl_3p = [ N_sig_gl[0],  N_sig_gl[1] , N_sig_gl[2] +  3*sN_sig_gl[2],  N_sig_gl[3]]
N_gl_3n = [ N_sig_gl[0],  N_sig_gl[1] , N_sig_gl[2] -  3*sN_sig_gl[2],  N_sig_gl[3]]
fgl_3p = convert_tofractions(N_gl_3p, Ntis_hh*1./justine["T"])
fgl_3n = convert_tofractions(N_gl_3n, Ntis_hh*1./justine["T"])

hspdf_3p = fillS(fgl_3p, sMpdf, "hspdf_3p_2011")
hspdf_3n = fillS(fgl_3n, sMpdf, "hspdf_3n_2011")

N_gl_4p = [ N_sig_gl[0],  N_sig_gl[1] , N_sig_gl[2] ,  N_sig_gl[3] +  3*sN_sig_gl[3]]
N_gl_4n = [ N_sig_gl[0],  N_sig_gl[1] , N_sig_gl[2] ,  N_sig_gl[3] -  3*sN_sig_gl[3]]
fgl_4p = convert_tofractions(N_gl_4p, Ntis_hh*1./justine["T"])
fgl_4n = convert_tofractions(N_gl_4n, Ntis_hh*1./justine["T"])

hspdf_4p = fillS(fgl_4p, sMpdf, "hspdf_4p_2011")
hspdf_4n = fillS(fgl_4n, sMpdf, "hspdf_4n_2011")


### mas paramters  ### Errors multiplied by three at the beginning to cover 3 sgima range !!!!!!!!!!!!!!!!!!

sMpdf_mp = signalPDF.massDescriptor(mean + s_mean, sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_mn = signalPDF.massDescriptor(mean - s_mean, sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_sp = signalPDF.massDescriptor(mean, sigma + s_sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_sn = signalPDF.massDescriptor(mean, sigma - s_sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_ap = signalPDF.massDescriptor(mean, sigma, a + s_a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_an = signalPDF.massDescriptor(mean, sigma, a - s_a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 

hspdf_mp = fillS(fgl, sMpdf_mp, "hspdf_mp_2011")
hspdf_mn = fillS(fgl, sMpdf_mn, "hspdf_mn_2011")
hspdf_sp = fillS(fgl, sMpdf_mp, "hspdf_sp_2011")
hspdf_sn = fillS(fgl, sMpdf_mn, "hspdf_sn_2011")
hspdf_ap = fillS(fgl, sMpdf_mp, "hspdf_ap_2011")
hspdf_an = fillS(fgl, sMpdf_mn, "hspdf_an_2011")

## CB systematics

h_mass_mcpdfp = TH2D("mc massp 2011", "mc massp 2011", len(Binning[glname])-1,Binning[glname], len(Binning["Bmass"]) -1, Binning["Bmass"])
h_mass_mcpdfn = TH2D("mc massn 2011", "mc massn 2011", len(Binning[glname])-1,Binning[glname], len(Binning["Bmass"]) -1, Binning["Bmass"])
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


Nb_sb1_1, hbpdf_sb1_1 = fillB(nnsb1p, idx, "hbpdf_sb1_1_2011")
Nb_sb1_2, hbpdf_sb1_2 = fillB(nnsb1n, idx, "hbpdf_sb1_2_2011")

Nb_sb2_1, hbpdf_sb2_1 = fillB(nnsb2p, idx, "hbpdf_sb2_1_2011")
Nb_sb2_2, hbpdf_sb2_2 = fillB(nnsb2n, idx, "hbpdf_sb2_2_2011")

Nb_sb3_1, hbpdf_sb3_1 = fillB(nnsb3p, idx, "hbpdf_sb3_1_2011")
Nb_sb3_2, hbpdf_sb3_2 = fillB(nnsb3n, idx, "hbpdf_sb3_2_2011")

Nb_sb4_1, hbpdf_sb4_1 = fillB(nnsb4p, idx, "hbpdf_sb4_1_2011")
Nb_sb4_2, hbpdf_sb4_2 = fillB(nnsb4n, idx, "hbpdf_sb4_2_2011")

### bkg exponential index

idx1p= [idx[0] + s_idx_p[0], idx[1], idx[2], idx[3]]
idx1n= [idx[0] + s_idx_n[0], idx[1], idx[2], idx[3]]

idx2p= [idx[0], idx[1] + s_idx_p[1], idx[2], idx[3]]
idx2n= [idx[0], idx[1] + s_idx_n[1], idx[2], idx[3]]

idx3p= [idx[0], idx[1], idx[2] + s_idx_p[2], idx[3]]  
idx3n= [idx[0], idx[1], idx[2] + s_idx_n[2], idx[3]]

idx4p= [idx[0], idx[1], idx[2], idx[3] + s_idx_p[3]]  
idx4n= [idx[0], idx[1], idx[2], idx[3] + s_idx_n[3]]

#idx1p= [idx[0]+ s_idx[0], idx[1]+ s_idx[0], idx[2] + s_idx[0], idx[3] + s_idx[0]]  ### All fluctuaded consistently
#idx1n= [idx[0]- s_idx[0], idx[1]- s_idx[0], idx[2] - s_idx[0], idx[3] - s_idx[0]]  ### All fluctuaded consistently


Nb_i1_1, hbpdf_i1_1 = fillB(Nsb, idx1p, "hbpdf_i1_1_2011")
Nb_i1_2, hbpdf_i1_2 = fillB(Nsb, idx1n, "hbpdf_i1_2_2011")

Nb_i2_1, hbpdf_i2_1 = fillB(Nsb, idx2p, "hbpdf_i2_1_2011")
Nb_i2_2, hbpdf_i2_2 = fillB(Nsb, idx2n, "hbpdf_i2_2_2011")

Nb_i3_1, hbpdf_i3_1 = fillB(Nsb, idx3p, "hbpdf_i3_1_2011")
Nb_i3_2, hbpdf_i3_2 = fillB(Nsb, idx3n, "hbpdf_i3_2_2011")

Nb_i4_1, hbpdf_i4_1 = fillB(Nsb, idx4p, "hbpdf_i4_1_2011")
Nb_i4_2, hbpdf_i4_2 = fillB(Nsb, idx4n, "hbpdf_i4_2_2011")



### Create Bkg hypothesis

bkg_no_syst = csm_template(0)#8)
bkg = csm_template(8)
bkg.set_np("Nsb1_2011", (Nb_sb1_2-Nb)/Nb, (Nb_sb1_1-Nb)/Nb, hbpdf_sb1_1, 1., hbpdf_sb1_2,-1.) ## void csm_template::set_np(char *name, Double_t low, Double_t high, TH1 *h_high, Double_t sigma_high, TH1 *h_low, Double_t sigma_low)
bkg.set_np("Nsb2_2011", (Nb_sb2_2-Nb)/Nb, (Nb_sb2_1-Nb)/Nb, hbpdf_sb2_1, 1., hbpdf_sb2_2,-1.)


bkg.set_np("Nsb3_2011", (Nb-Nb_sb3_2)/Nb, (Nb-Nb_sb3_1)/Nb, hbpdf_sb3_1, 1., hbpdf_sb3_2,-1.)
bkg.set_np("Nsb4_2011", (Nb-Nb_sb4_2)/Nb, (Nb-Nb_sb4_1)/Nb, hbpdf_sb4_1, 1., hbpdf_sb4_2,-1.)

bkg.set_np("i_2011", (Nb-Nb_i1_2)/Nb, (Nb-Nb_i1_1)/Nb, hbpdf_i1_1, 1., hbpdf_i1_2,-1.)

bkg.set_np("i2_2011", (Nb-Nb_i2_2)/Nb, (Nb-Nb_i2_1)/Nb, hbpdf_i2_1, 1., hbpdf_i2_2,-1.)
bkg.set_np("i3_2011", (Nb-Nb_i3_2)/Nb, (Nb-Nb_i3_1)/Nb, hbpdf_i3_1, 1., hbpdf_i3_2,-1.)
bkg.set_np("i4_2011", (Nb-Nb_i4_2)/Nb, (Nb-Nb_i4_1)/Nb, hbpdf_i4_1, 1., hbpdf_i4_2,-1.)

bkg.make(hbpdf,Nb, 0,0,"2011")
bkg_no_syst.make(hbpdf,Nb, 0,0,"2011")

fdata = TFile(os.environ["BS2MUMUPARAMSROOT"]+"/histos/DataBs.root")
DataHist = fdata.Get("data 2011")#FitInBinning_2D(datatree,Binning, glname = glname, name = "data 2010")


#DataHist = FitInBinning_2D(datatree,Binning, glname = glname, name = "data 2011")

if MISID: 
    misid = csm_template(2)
    misid_no_syst = csm_template(0)
    xbinning = Binning
    xbinning["GLsb."] = Binning[glname]
    xbinning["GLKsm_MC10sb."] = Binning[glname]
    xbinning["Bmass_sm"] = Binning["Bmass"]
    
    hmisid = FitInBinning_2D(tmis,xbinning, glname = "GLKsm_MC10sb.", name = "missid 2011", flatgl = 1)
    unsmeared_misid = FitInBinning_2D(tmis,xbinning, glname = "GLKsm_MC10sb.", massname = "Bmass_sm", name = "missid 2011 u", flatgl = 1)
    oversmeared_misid = FitInBinning_2D(tmis,xbinning, glname = "GLKsm_MC10sb.", massname = "Bmass", name = "missid 2011 o", flatgl = 1)
    
    hmisid.Scale(Double(1.)/Double(hmisid.GetSum()))
    unsmeared_misid.Scale(Double(1.)/Double(unsmeared_misid.GetSum()))
    oversmeared_misid.Scale(Double(1.)/Double(oversmeared_misid.GetSum()))
    misid.set_np("misid yield", s_MISID/MISID ,-s_MISID/MISID, NULL, 1., NULL , -1.)
    misid.set_np("misid mass pdf", s_MISID_2/MISID,-s_MISID_2/MISID, unsmeared_misid, 1., oversmeared_misid , -1.)
   # BREAK
    misid.make(hmisid,MISID, 0,0,"2011")
    misid_no_syst.make(hmisid,MISID, 0,0,"2011")
    
if CHANNEL == "Bd":
    bs_in_bdsMpdf = signalPDF.massDescriptor(TheTable.MassMeanBs, sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])
    BR_Bs = 3.2
    sBR_Bs1 = 0.2#0.9-4.3
    sBR_Bs2 = -0.2#9.2-4.3
    
    alpha_Bs = 0.826
    eff_Bs = bs_in_bdsMpdf(Binning["Bmass"][0],Binning["Bmass"][-1])[0]*1./bs_in_bdsMpdf(TheTable.MassMeanBs-60,TheTable.MassMeanBs+60)[0]
    print "Crossfeed efficiency", eff_Bs
    crossfeed_pdf = fillS(fgl,bs_in_bdsMpdf , "crossfeed") #### Normalized
    
    crossfeed = csm_template(1)
    crossfeed_no_syst = csm_template(0)
    crossfeed.set_np("2011 xfeed yield", sBR_Bs1/BR_Bs ,sBR_Bs2/BR_Bs, NULL, 1., NULL , -1.)
    crossfeed.make(crossfeed_pdf, eff_Bs*BR_Bs/alpha_Bs, 0,0,"2011")
    crossfeed_no_syst.make(crossfeed_pdf,  eff_Bs*BR_Bs/alpha_Bs, 0,0,"2011")
    
name_cu = "c_u"
name_cphi = "c_phi"
name_ckpi = "c_kpi"
name_fdfs = "fdfs"
name_kpiT = "c_kpiT_2011"
name_n2 = "n2_2011"
name_n3 = "n3_2011"
name_n4 = "n4_2011"
name_m = "m_2011"
name_s = "s_2011"
name_a = "a_2011"

dc2011 = {}
if SM:
######################
## SM              ###
######################

    BR_SM = 3.5e-09 ### Nazila 2011
    sBR_SM = 0#0.3e-09 ## Nazila 2011

    sm = csm_template(12)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
    sm_no_syst = csm_template(0)
    
    sm.set_np(name_cu,(alpha_bun-alpha)/alpha, (alpha_bup - alpha)/alpha,NULL,1., NULL, -1.)  ### void csm_template::set_np(char *name, Double_t low, Double_t high, TH1 *h_high, Double_t sigma_high, TH1 *h_low, Double_t sigma_low)
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

    sm.make(hspdf,BR_SM/alpha,0,0, "2011")
    sm_no_syst.make(hspdf,BR_SM/alpha,0,0, "2011")


def DoSigModel(ns, dc = dc2011):
    #test = csm_model()
    #testpe = csm_model()

    dc[ns] = csm_template(11)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
    dc[str(ns) + "_no_syst"] = csm_template(0)

    ### c_u
    
    dc[ns].set_np(name_cu,3*(alpha_bun-alpha)/alpha, 3*(alpha_bup - alpha)/alpha,NULL,3., NULL, -3.)  ### void csm_template::set_np(char *name, Double_t low, Double_t high, TH1 *h_high, Double_t sigma_high, TH1 *h_low, Double_t sigma_low)
    dc[ns].set_np(name_m,0., 0.,hspdf_mp,3., hspdf_mn, -3.)
    dc[ns].set_np(name_s,0., 0.,hspdf_sp,3, hspdf_sn, -3.)
    dc[ns].set_np(name_a,0., 0.,hspdf_ap,3., hspdf_an, -3.)


    dc[ns].set_np(name_cphi,(alpha_phin-alpha)/alpha, (alpha_phip - alpha)/alpha,NULL, 1., NULL, -1.)
    dc[ns].set_np(name_ckpi,(alpha_kpin-alpha)/alpha, (alpha_kpip - alpha)/alpha,NULL, 1., NULL, -1.)
    dc[ns].set_np(name_fdfs,(alpha_fn-alpha)/alpha, (alpha_fp - alpha)/alpha,NULL, 1., NULL, -1.)
    
    dc[ns].set_np(name_kpiT,(alpha_Tn-alpha)/alpha, (alpha_Tp - alpha)/alpha,hspdf_Tp, 2., hspdf_Tn, -2.)
    

    dc[ns].set_np(name_n2,0., 0.,hspdf_2p, 3., hspdf_2n, -3.)
    dc[ns].set_np(name_n3,0., 0.,hspdf_3p, 3., hspdf_3n, -3.)
    dc[ns].set_np(name_n4,0., 0.,hspdf_4p, 3., hspdf_4n, -3.)
    #dc[ns].set_np("CB model_2011",0., 0.,h_mass_mcpdfp, 1., h_mass_mcpdfn, -1.)
   
    
    #BREAK
    dc[ns].make(hspdf,ns,0,1, "2011")
    dc[str(ns) + "_no_syst"].make(hspdf,ns,0,1, "2011")
    return dc
    ## print "ooooo"
