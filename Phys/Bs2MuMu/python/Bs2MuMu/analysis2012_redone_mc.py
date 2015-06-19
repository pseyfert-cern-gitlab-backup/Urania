#! /usr/bin/env python

#############################################
# 2012                                #######
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
#from Bs2MuMuParams
from Bs2MuMuParams import toytable_test_1fb_AleInput as TheTable
import sys, os

from Bs2MuMuParams import toytable_test_1fb_AleInput as autum2012table
sSMrel = autum2012table.Bsmumu_BRErr/autum2012table.Bsmumu_BR

CHANNEL = "Bs"
SM = 0
sigma_hh = 5.
sigma_B  = 5.
#sigma_Bn  = 1.
sigma_Bk = 5.
sigma_Ba = 3.
pfunc = "BG"
#pfunc = ""
glname = "BDT9_05"
MISID = 1

if pfunc == "95":
    def poissonE(x):
        a,b = poissonErrors95(x)
        return a/1.96, b/1.96
elif pfunc == "50":
    def poissonE(x):
        a,b = poissonErrors50(x)
        return a/.6745, b/.6745
elif pfunc == "BG":
    def poissonE(x): return fuckingErrorsB(x)
elif pfunc == "BGX":
    def poissonE(x):
        a, b= fuckingErrors(x)
        return a, a
else:
    def poissonE(x): return poissonErrors(x)


if CHANNEL == "Bs":
    mean = TheTable.MassMeanBs
    s_mean = 3*TheTable.MassMeanErrBs
    if MISID: MISID = TheTable.MisIDGlobalFactor * TheTable.MisIDfBs * TheTable.TisTot  ### Inside the tight window
    s_MISIDp_asym_rel =  TheTable.MisIDfErrPBs/TheTable.MisIDfBs
    s_MISIDn_asym_rel = TheTable.MisIDfErrNBs/TheTable.MisIDfBs
    s_MISID_sym_rel = TheTable.MisIDGlobalFactorErr / TheTable.MisIDGlobalFactor
    fmisid = TFile(os.environ["BS2MUMUPARAMSROOT"] + "/histos/misid_Bs.root")
    hMmisid = fmisid.Get("misid Bs nom")
    hMmisid_down = fmisid.Get("misid Bs sm")
    hMmisid_up = fmisid.Get("misid Bs pes")
   

    
elif CHANNEL == "Bd":
    mean = TheTable.MassMeanBd
    s_mean = 3*TheTable.MassMeanErrBd
    if MISID: MISID = TheTable.MisIDGlobalFactor * TheTable.MisIDfBd * TheTable.TisTot  ### Inside the tight window
    s_MISIDp_asym_rel =  TheTable.MisIDfErrPBd/TheTable.MisIDfBd
    s_MISIDn_asym_rel = TheTable.MisIDfErrNBd/TheTable.MisIDfBd
    s_MISID_sym_rel = TheTable.MisIDGlobalFactorErr / TheTable.MisIDGlobalFactor
    fmisid = TFile(os.environ["BS2MUMUPARAMSROOT"] + "/histos/misid_Bd.root")
    hMmisid = fmisid.Get("misid Bd nom")
    hMmisid_up = fmisid.Get("misid Bd sm")
    hMmisid_down = fmisid.Get("misid Bd pes")

glbins = [0, .25,.4,.5,.6,.7,.8,.9,1.]
massbins = [mean-60., mean-48., mean-36., mean-30., mean-18., mean+18., mean+30., mean+36., mean+48., mean+60.]
#massbins = [5312.96, 5324.96, 5336.96, 5342.96, 5354.96, 5390.96, 5402.96, 5408.96, 5420.96, 5432.96]
#[5224.6300000000001, 5236.6300000000001, 5248.6300000000001, 5254.6300000000001, 5266.6300000000001, 5302.6300000000001, 5314.6300000000001, 5320.6300000000001, 5332.6300000000001, 5344.6300000000001]

filename = '~/vol5/Bs2mumu341'

misidname = "/afs/cern.ch/user/d/diegoms/vol5/MCbhh_mixed_X_misidp_rnd0.0"
misidname_o = "/afs/cern.ch/user/d/diegoms/vol5/MCbhh_mixed_X_misidp_worseall_rnd0.0"


datatree, datafile = getTuple(filename, thing = "Bs2MuMu")
tmis, fmis = getTuple(misidname)
tmis_o, fmis_o = getTuple(misidname_o)

Binning = {glname : afC('f',glbins), "Bmass": afC('f',massbins)}

M_min = {0:TheTable.GL1MassSb1,1:TheTable.GL2MassSb1,2:TheTable.GL3MassSb1,3:TheTable.GL4MassSb1,4:TheTable.GL5MassSb1,5:TheTable.GL6MassSb1,6:TheTable.GL7MassSb1,7:TheTable.GL8MassSb1}
M_max = {0:TheTable.GL1MassSb4,1:TheTable.GL2MassSb4,2:TheTable.GL3MassSb4,3:TheTable.GL4MassSb4,4:TheTable.GL5MassSb4,5:TheTable.GL6MassSb4,6:TheTable.GL7MassSb4,7:TheTable.GL8MassSb4}  


M_b = TheTable.GL1MassSb2 
M_c = TheTable.GL1MassSb3    

def bkg_in_bin(x,y,Nsb,idx,f_ale,  a = M_min, b = M_b , c = M_c, d = M_max):
    
    kl = idx
    Dk = (exp(kl*a) +exp(kl*c) - exp(kl*b) - exp(kl*d))
    iDk = 1./Dk
    
    Nxy = iDk*Nsb*(exp(kl*x)-exp(kl*y))
    f = f_ale*Dk / (exp(kl*a)-exp(kl*d))
    #return Nxy
    return Nxy*f

def fillB(Nsb, idx,ale, name):
    hbpdf = TH2D(name,name,len(Binning[glname])-1,Binning[glname],  len(Binning["Bmass"]) -1, Binning["Bmass"])
    N = 0.
    for i in range(hspdf.GetNbinsX()):
       
        for k in range(hbpdf.GetNbinsY()):
           
            Nxy = bkg_in_bin(Binning["Bmass"][k],Binning["Bmass"][k+1], Nsb[i],idx[i],ale[i], a = M_min[i], d = M_max[i])
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

def makeMisid(hMmisid, fmisid, name):
    h = TH2D(name,name,len(Binning[glname])-1,Binning[glname],  len(Binning["Bmass"]) -1, Binning["Bmass"])

    for i in range(h.GetNbinsX()):
        for j in range(h.GetNbinsY()):
            h.SetBinContent(i+1,j+1, fmisid[i]*hMmisid.GetBinContent(j+1))
    return h

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
s_fdfs = sqrt(TheTable.fsfdErrP**2 + TheTable.fsfdErrN**2)/sqrt(2.)

c_kpi, sc_kpi = do_kpi_coef(b_kpi,sb_kpi,Ntis_hh, sNtis_hh)

alpha, s_alpha = calculateNormalizationFactor( c_bu, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)

#############################################################################
# GL pdf
N_misid_bdt = 8*[0.]
N_sig_gl = [0., TheTable.Tis2, TheTable.Tis3, TheTable.Tis4, TheTable.Tis5,TheTable.Tis6, TheTable.Tis7, TheTable.Tis8]
sN_sig_gl = [0., TheTable.TisErr2, TheTable.TisErr3,TheTable.TisErr4, TheTable.TisErr5, TheTable.TisErr6, TheTable.TisErr7, TheTable.TisErr8]
sN_misid_gl = [0., TheTable.TisErr2, TheTable.TisErr3,TheTable.TisErr4, TheTable.TisErr5, TheTable.TisErr6, TheTable.TisErr7, TheTable.TisErr8]
justine = {"T":1., 0:1., 1: TheTable.Justine2, 2:TheTable.Justine3 , 3: TheTable.Justine4, 4: TheTable.Justine5, 5:TheTable.Justine6 , 6: TheTable.Justine7, 7: TheTable.Justine8}
mid_idf = [TheTable.MisIDfBDTBin1,TheTable.MisIDfBDTBin2,TheTable.MisIDfBDTBin3,TheTable.MisIDfBDTBin4,TheTable.MisIDfBDTBin5,TheTable.MisIDfBDTBin6,TheTable.MisIDfBDTBin7,TheTable.MisIDfBDTBin8]
for i in range(len(N_sig_gl)):
    N_misid_bdt[i] =  N_sig_gl[i]/mid_idf[i]
    N_sig_gl[i] =  N_sig_gl[i] *1./justine[i]
    sN_sig_gl[i] =  sqrt( (sN_sig_gl[i] *1./justine[i]) **2 )#+ (0.04*N_sig_gl[i])**2 +(0.05*N_sig_gl[i])**2)
    sN_misid_gl[i] =  sqrt( (sN_misid_gl[i] *1./mid_idf[i]) **2 )#+ (0.04*N_sig_gl[i])**2 +(0.05*N_sig_gl[i])**2)
    
fgl = convert_tofractions(N_sig_gl, Ntis_hh*1./justine["T"])
fgl_misid = convert_tofractions(N_misid_bdt, Ntis_hh)


################################################################################
## Signal Mass pdf parameters

mean = mean #### se at the begining of the file
s_mean = s_mean

if CHANNEL == "Bs":
    sigma = TheTable.MassResoBs
    s_sigma = 3*TheTable.MassResoErrBs
    a = TheTable.CBTrans
    s_a = 3*TheTable.CBTransErr

if CHANNEL == "Bd":
    sigma = TheTable.MassResoBd
    s_sigma = 3*TheTable.MassResoErrBd
    a = TheTable.CBTrans
    s_a = 3*TheTable.CBTransErr


sMpdf = signalPDF.massDescriptor(mean, sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 

###############33
## BKG parameters
#######################################################################
#### yields in sidebands
Nsb = {0: TheTable.SbGL1, 1: TheTable.SbGL2, 2:TheTable.SbGL3, 3:TheTable.SbGL4,4: TheTable.SbGL5, 5: TheTable.SbGL6, 6:TheTable.SbGL7, 7:TheTable.SbGL8}  ## central value
sNsbp = {} ## upper ~poisson error
sNsbn = {} ## lower ~posission erro

for i in range(8): sNsbp[i], sNsbn[i] = poissonE(Nsb[i])

#### Syst in bkg bin 1

syst_bkg_ext = 1
if syst_bkg_ext :
    print "extra syst from double expo ENABLED"
    for i in range(8):
        sNsbp[i] = sqrt(sNsbp[i]**2 + ( getattr(TheTable, "SystBkgBin"+str(i+1))*Nsb[i])**2)
        sNsbn[i] = sqrt(sNsbn[i]**2 + ( getattr(TheTable, "SystBkgBin"+str(i+1))*Nsb[i])**2)

else: print "extra syst from double expo DISABLED"


#####################################################
### exponential index in sidebands

idx = [ TheTable.BkgMassk1, TheTable.BkgMassk2, TheTable.BkgMassk3 , TheTable.BkgMassk4, TheTable.BkgMassk5, TheTable.BkgMassk6, TheTable.BkgMassk7 , TheTable.BkgMassk8]  
s_idx_p = [ TheTable.BkgMasskErrP1, TheTable.BkgMasskErrP2, TheTable.BkgMasskErrP3 , TheTable.BkgMasskErrP4, TheTable.BkgMasskErrP5, TheTable.BkgMasskErrP6, TheTable.BkgMasskErrP7 , TheTable.BkgMasskErrP8]
s_idx_n = [ TheTable.BkgMasskErrN1, TheTable.BkgMasskErrN2, TheTable.BkgMasskErrN3 , TheTable.BkgMasskErrN4, TheTable.BkgMasskErrN5, TheTable.BkgMasskErrN6, TheTable.BkgMasskErrN7 , TheTable.BkgMasskErrN8]

#####################################################
### Alessio's factors

alessio = [ TheTable.FracCombBin1, TheTable.FracCombBin2, TheTable.FracCombBin3 , TheTable.FracCombBin4, TheTable.FracCombBin5, TheTable.FracCombBin6, TheTable.FracCombBin7 , TheTable.FracCombBin8]  
s_alessio_p = [ TheTable.FracCombErrP1, TheTable.FracCombErrP2, TheTable.FracCombErrP3 , TheTable.FracCombErrP4, TheTable.FracCombErrP5, TheTable.FracCombErrP6, TheTable.FracCombErrP7 , TheTable.FracCombErrP8]
s_alessio_n = [ TheTable.FracCombErrN1, TheTable.FracCombErrN2, TheTable.FracCombErrN3 , TheTable.FracCombErrN4, TheTable.FracCombErrN5, TheTable.FracCombErrN6, TheTable.FracCombErrN7 , TheTable.FracCombErrN8] 
        
###########################################
##### Signal 2D  PDF's

hspdf = fillS(fgl, sMpdf, "hspdf 2012")
#hspdf.Scale(double(1.)/double(hspdf.GetSum()))
###########################################
#### Bkg 2D  PDF's

Nb, hbpdf = fillB(Nsb,idx, alessio, "hbpdf 2012")


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
fdfsp, fdfsn = fdfs + TheTable.fsfdErrP, fdfs + TheTable.fsfdErrN
alpha_fp, s_alphaz  = calculateNormalizationFactor( c_bu, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, fdfsp, s_fdfs, channel = CHANNEL)
alpha_fn, s_alphaz  = calculateNormalizationFactor( c_bu, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, fdfsn, s_fdfs, channel = CHANNEL)

## Ntis_hh

c_kpiTp, sc_kpip = do_kpi_coef(b_kpi,sb_kpi,Ntis_hh + sNtis_hh, sNtis_hh)
c_kpiTn, sc_kpin = do_kpi_coef(b_kpi,sb_kpi,Ntis_hh -sNtis_hh, sNtis_hh)

alpha_Tp, s_alphaz  = calculateNormalizationFactor( c_bu, c_phi, c_kpiTp,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)
alpha_Tn, s_alphaz  = calculateNormalizationFactor( c_bu, c_phi, c_kpiTn,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel = CHANNEL)

fgl_Tp = convert_tofractions(N_sig_gl, (Ntis_hh + sigma_hh*sNtis_hh)*1./justine["T"])
fgl_Tn = convert_tofractions(N_sig_gl, (Ntis_hh - sigma_hh*sNtis_hh)*1./justine["T"])

fmis_gl_Tp = convert_tofractions(N_misid_bdt, (Ntis_hh + sigma_hh*sNtis_hh))
fmis_gl_Tn = convert_tofractions(N_misid_bdt, (Ntis_hh - sigma_hh*sNtis_hh))


hspdf_Tp = fillS(fgl_Tp, sMpdf, "hspdf_Tp_2012")
hspdf_Tn = fillS(fgl_Tn, sMpdf, "hspdf_Tn_2012")

hmispdf_Tp = makeMisid(hMmisid, fmis_gl_Tp, "hmispdf_Tp_2012")
hmispdf_Tn = makeMisid(hMmisid, fmis_gl_Tn, "hmispdf_Tn_2012")


### N gl 2, 3, 4, ...

N_gl_p, N_gl_n = {},{}
f_gl_p, f_gl_n = {},{}
hspdf_p, hspdf_n = {},{}

Nmis_gl_p, Nmis_gl_n = {},{}
fmis_gl_p, fmis_gl_n = {},{}
hmispdf_p, hmispdf_n = {},{}

for i in range(len(N_sig_gl)):
    N_gl_p[i] = 8*[0.]
    N_gl_n[i] = 8*[0.]
    Nmis_gl_p[i] = 8*[0.]
    Nmis_gl_n[i] = 8*[0.]
    for j in range(len(N_sig_gl)):
        if i==j:
            N_gl_p[i][j] = N_sig_gl[i] + sigma_hh*sN_sig_gl[i]
            N_gl_n[i][j] = N_sig_gl[i] - sigma_hh*sN_sig_gl[i]

            Nmis_gl_p[i][j] = N_misid_bdt[i] + sigma_hh*sN_misid_gl[i]
            Nmis_gl_n[i][j] = N_misid_bdt[i] - sigma_hh*sN_misid_gl[i]
            continue
        N_gl_p[i][j] = N_sig_gl[j]
        N_gl_n[i][j] = N_sig_gl[j]

        Nmis_gl_p[i][j] = N_misid_bdt[j] #+ 3*sN_misid_gl[i]
        Nmis_gl_n[i][j] = N_misid_bdt[j] #- 3*sN_misid_gl[i]
        
    f_gl_p[i] = convert_tofractions(N_gl_p[i], Ntis_hh*1./justine["T"])
    f_gl_n[i] = convert_tofractions(N_gl_n[i], Ntis_hh*1./justine["T"])
    hspdf_p[i] =fillS(f_gl_p[i], sMpdf, "hspdf_"+str(i)+"p_2012")
    hspdf_n[i] =fillS(f_gl_n[i], sMpdf, "hspdf_"+str(i)+"n_2012")

    fmis_gl_p[i] = convert_tofractions(Nmis_gl_p[i], Ntis_hh)
    fmis_gl_n[i] = convert_tofractions(Nmis_gl_n[i], Ntis_hh)
    
    hmispdf_n[i] =makeMisid(hMmisid,fmis_gl_n[i], "misid n" + str(i) + " 2012",)# "hspdf_"+str(i)+"n_2012")
    hmispdf_p[i] =makeMisid(hMmisid,fmis_gl_p[i], "misid p" + str(i) + " 2012",)# "hspdf_"+str(i)+"n_2012")

    


### mas paramters  ### Errors multiplied by three at the beginning to cover 3 sgima range !!!!!!!!!!!!!!!!!!

sMpdf_mp = signalPDF.massDescriptor(mean + s_mean, sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_mn = signalPDF.massDescriptor(mean - s_mean, sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_sp = signalPDF.massDescriptor(mean, sigma + s_sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_sn = signalPDF.massDescriptor(mean, sigma - s_sigma, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_ap = signalPDF.massDescriptor(mean, sigma, a + s_a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 
sMpdf_an = signalPDF.massDescriptor(mean, sigma, a - s_a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])   ### Crystalball 

hspdf_mp = fillS(fgl, sMpdf_mp, "hspdf_mp_2012")
hspdf_mn = fillS(fgl, sMpdf_mn, "hspdf_mn_2012")
hspdf_sp = fillS(fgl, sMpdf_mp, "hspdf_sp_2012")
hspdf_sn = fillS(fgl, sMpdf_mn, "hspdf_sn_2012")
hspdf_ap = fillS(fgl, sMpdf_mp, "hspdf_ap_2012")
hspdf_an = fillS(fgl, sMpdf_mn, "hspdf_an_2012")

## CB systematics

h_mass_mcpdfp = TH2D("mc massp 2012", "mc massp 2012", len(Binning[glname])-1,Binning[glname], len(Binning["Bmass"]) -1, Binning["Bmass"])
h_mass_mcpdfn = TH2D("mc massn 2012", "mc massn 2012", len(Binning[glname])-1,Binning[glname], len(Binning["Bmass"]) -1, Binning["Bmass"])
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
Nb_sb_p, Nb_sb_n = {}, {}
hbpdf_sb_p , hbpdf_sb_n = {}, {}

sigma_Bn = {}  ### To correct the number of sigmas.
_l0, _l1 ={},{}  ### incrementos !!

for i in range(len(N_sig_gl)):
    _l0[i] = {}
    _l1[i] = {}
    for j in range(len(N_sig_gl)):
        if i!= j:
            _l0[i][j] = 0
            _l1[i][j] = 0
            continue
        _l0[i][i] = sigma_B*sNsbp[i]
        if abs(sNsbn[i]*sigma_B < Nsb[i]):
            sigma_Bn[i] = sigma_B
            _l1[i][i] = sigma_B*sNsbn[i]
        else:
            sigma_Bn[i] = abs(Nsb[i]/sNsbn[i])
            _l1[i][i] = sigma_Bn[i]*sNsbn[i]
        
    nnsbp, nnsbn = fluctuateSidebands(Nsb, _l0[i], _l1[i])
    Nb_sb_p[i], hbpdf_sb_p[i] = fillB(nnsbp, idx, alessio, "hbpdf_sb"+str(i)+"_p_2012")
    Nb_sb_n[i], hbpdf_sb_n[i] = fillB(nnsbn, idx, alessio, "hbpdf_sb"+str(i)+"_n_2012")

### bkg exponential index
idxp,  idxn = {},{}
Nbp_i, Nbn_i = {}, {}
hbpdfp_i, hbpdfn_i = {}, {}

for i in range(len(N_sig_gl)-1):
    idxp[i] = {}
    idxn[i] = {}
    #Nbp_i[i] ={}
    #Nbn_i[i] = {}
    for j in range(len(N_sig_gl)):
        if i!= j:
            idxp[i][j] = idx[j]
            idxn[i][j] = idx[j]
            continue
        idxp[i][i] = idx[i]+sigma_Bk*s_idx_p[i]
        idxn[i][i] = idx[i]+sigma_Bk*s_idx_n[i]

### Force last two bins to fluctuate together
idxp[6][7] = idxp[6][6]
#idxp[7][6] = idxp[7][7]
idxn[6][7] = idxn[6][6]
#idxn[7][6] = idxn[7][7]

for i in range(len(N_sig_gl)-1):
    Nbp_i[i], hbpdfp_i[i] = fillB(Nsb, idxp[i], alessio, "hbpdfp_i"+str(i)+"_2012")
    Nbn_i[i], hbpdfn_i[i] = fillB(Nsb, idxn[i], alessio, "hbpdfn_i"+str(i)+"_2012")

### Alessio's factors
alessiop,  alession = {},{}
Nbp_a, Nbn_a = {}, {}
hbpdfp_a, hbpdfn_a = {}, {}

for i in range(len(N_sig_gl)):
    alessiop[i] = {}
    alession[i] = {}
    #Nbp_i[i] ={}
    #Nbn_i[i] = {}
    for j in range(len(N_sig_gl)):
        if i!= j:
            alessiop[i][j] = alessio[j]
            alession[i][j] = alessio[j]
            continue
        alessiop[i][i] = alessio[i]+sigma_Bk*s_alessio_p[i]
        alession[i][i] = alessio[i]+sigma_Bk*s_alessio_n[i]
for i in range(len(N_sig_gl)):
    Nbp_a[i], hbpdfp_a[i] = fillB(Nsb, idx,alessiop[i], "hbpdfp_a"+str(i)+"_2012")
    Nbn_a[i], hbpdfn_a[i] = fillB(Nsb, idx,alession[i], "hbpdfn_a"+str(i)+"_2012")



### Create Bkg hypothesis

bkg_no_syst = csm_template(0)#8)
bkg = csm_template(3*int(len(N_sig_gl)) -1 )
for i in range(len(N_sig_gl)):
    bkg.set_np("Nsb"+str(i)+"_2012", (Nb_sb_n[i]-Nb)/(sigma_Bn[i]*Nb), (Nb_sb_p[i]-Nb)/(sigma_B*Nb), hbpdf_sb_p[i], sigma_B, hbpdf_sb_n[i],-1.*sigma_Bn[i]) ### systematic from N sidebands  check sigmas.... 
    if i<7: bkg.set_np("i_"+str(i)+"_2012", (Nb-Nbn_i[i])/(sigma_Bk*Nb), (Nb-Nbp_i[i])/(sigma_Bk*Nb), hbpdfp_i[i], sigma_Bk, hbpdfn_i[i],-1.*sigma_Bk) ### systematic from indices check sigmas....
    bkg.set_np("a_"+str(i)+"_2012", (Nb-Nbn_a[i])/(sigma_Ba*Nb), (Nb-Nbp_a[i])/(sigma_Ba*Nb), hbpdfp_a[i], sigma_Ba, hbpdfn_a[i],-1.*sigma_Ba) ### systematic from indices check sigmas....
    


bkg.make(hbpdf,Nb, 0,0,"2012")
bkg_no_syst.make(hbpdf,Nb, 0,0,"2012")

#DataHist = FitInBinning_2D(datatree,Binning, glname = glname, name = "data 2012")

name_cu = "c_u"
name_cphi = "c_phi"
name_ckpi = "c_kpi"
name_fdfs = "fdfs"
name_kpiT = "c_kpiT_2012"
name_n= {}
for i in range(2,9):
    name_n[i] = "n"+str(i)+"_2012"

name_m = "m_2012"
name_s = "s_2012"
name_a = "a_2012"


if MISID:
    
    misid = csm_template(10) ### Ntishh, NGL 2-8, TOT Misid and Misid in mass window.
    misid_no_syst = csm_template(0)
    hmisid = makeMisid(hMmisid,fgl_misid, "misid 2012")
    hmisid.Scale(Double(1.)/Double(hmisid.GetSum()))

    misid.set_np(name_kpiT,-sNtis_hh/Ntis_hh,sNtis_hh/Ntis_hh , hmispdf_Tp, sigma_hh, hmispdf_Tn, -1.*sigma_hh)
    for i in range(1,8):
        misid.set_np(name_n[i+1],0., 0.,hmispdf_p[i], 3., hmispdf_n[i], -3.)
    hmisid_u = makeMisid(hMmisid_up , fgl_misid, "misid up 2012")
    hmisid_d = makeMisid(hMmisid_down , fgl_misid, "misid down 2012")

    misid.set_np("misid yield", s_MISID_sym_rel  ,-s_MISID_sym_rel , NULL, 1., NULL , -1.)
    misid.set_np("misid mass pdf", s_MISIDn_asym_rel,s_MISIDp_asym_rel, hmisid_u, 3., hmisid_d , -3.) ## The bounds are assumed to be 3 sigma
    misid.make(hmisid,MISID, 0,0,"2012")
    misid_no_syst.make(hmisid,MISID, 0,0,"2012")

BR_Bs = TheTable.Bsmumu_BR 
sBR_Bs1 = TheTable.Bsmumu_BRErr #0.9-4.3
sBR_Bs2 = -TheTable.Bsmumu_BRErr #9.2-4.3

if CHANNEL == "Bd":
    bs_in_bdsMpdf = signalPDF.massDescriptor(TheTable.MassMeanBs, TheTable.MassResoBs, a, limits = [Binning["Bmass"][0],Binning["Bmass"][-1]])
    
    
    alpha_Bs = 3.31584e-10

    eff_Bs = bs_in_bdsMpdf(Binning["Bmass"][0],Binning["Bmass"][-1])[0]*1./bs_in_bdsMpdf(TheTable.MassMeanBs-60,TheTable.MassMeanBs+60)[0]
    print "Crossfeed efficiency", eff_Bs
    crossfeed_pdf = fillS(fgl,bs_in_bdsMpdf , "crossfeed") #### Normalized
    
    crossfeed = csm_template(1)
    crossfeed_no_syst = csm_template(0)
    crossfeed.set_np("2012 xfeed yield", sBR_Bs1/BR_Bs ,sBR_Bs2/BR_Bs, NULL, 1., NULL , -1.)
    crossfeed.make(crossfeed_pdf, eff_Bs*BR_Bs/alpha_Bs, 0,0,"2012")
    crossfeed_no_syst.make(crossfeed_pdf,  eff_Bs*BR_Bs/alpha_Bs, 0,0,"2012")
    

dc2012 = {}
#if SM:
######################
## SM              ###
######################

BR_SM = BR_Bs ### Nazila 2012
sBR_SM = TheTable.Bsmumu_BRErr#0.3e-09 ## Nazila 2012

sm = csm_template(16)  ####### 12 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
sm_no_syst = csm_template(0)
    
sm.set_np(name_cu,(alpha_bun-alpha)/alpha, (alpha_bup - alpha)/alpha,NULL,1., NULL, -1.)  ### void csm_template::set_np(char *name, Double_t low, Double_t high, TH1 *h_high, Double_t sigma_high, TH1 *h_low, Double_t sigma_low)
sm.set_np(name_m,0., 0.,hspdf_mp,3., hspdf_mn, -3.)
sm.set_np(name_s,0., 0.,hspdf_sp,3, hspdf_sn, -3.)
sm.set_np(name_a,0., 0.,hspdf_ap,3., hspdf_an, -3.)

sm.set_np(name_cphi,(alpha_phin-alpha)/alpha, (alpha_phip - alpha)/alpha,NULL, 1., NULL, -1.)
sm.set_np(name_ckpi,(alpha_kpin-alpha)/alpha, (alpha_kpip - alpha)/alpha,NULL, 1., NULL, -1.)
sm.set_np(name_fdfs,(alpha_fn-alpha)/alpha, (alpha_fp - alpha)/alpha,NULL, 1., NULL, -1.)

sm.set_np(name_kpiT,(alpha_Tn-alpha)/alpha, (alpha_Tp - alpha)/alpha,hspdf_Tp, 3., hspdf_Tn, -3.)
#for i in range(2,
for i in range(1,8):
        sm.set_np(name_n[i+1],0., 0.,hspdf_p[i], sigma_hh, hspdf_n[i], -1.*sigma_hh)
sm.set_np("SM",-sBR_SM/BR_SM, sBR_SM/BR_SM,NULL, 1., NULL, -1.)

sm.make(hspdf,BR_SM/alpha,0,0, "2012")
sm_no_syst.make(hspdf,BR_SM/alpha,0,0, "2012")


def DoSigModel(ns, dc = dc2012):
    
    dc[ns] = csm_template(16)  ####### 15 nuissance parameters:   (c_u, c_phi, b_kpi, fdfs, Ntis_hh), (mean, sigma, trans), ( N_GL :2,3,4) , CB model
    dc[str(ns) + "_no_syst"] = csm_template(0)

    dc[ns].set_np(name_cu, (alpha_bun-alpha)/alpha, (alpha_bup - alpha)/alpha,NULL,1., NULL, -1.) 
    dc[ns].set_np(name_m,0., 0.,hspdf_mp,3., hspdf_mn, -3.)
    dc[ns].set_np(name_s,0., 0.,hspdf_sp,3, hspdf_sn, -3.)
    dc[ns].set_np(name_a,0., 0.,hspdf_ap,3., hspdf_an, -3.)


    dc[ns].set_np(name_cphi,(alpha_phin-alpha)/alpha, (alpha_phip - alpha)/alpha,NULL, 1., NULL, -1.)
    dc[ns].set_np(name_ckpi,(alpha_kpin-alpha)/alpha, (alpha_kpip - alpha)/alpha,NULL, 1., NULL, -1.)
    dc[ns].set_np(name_fdfs,(alpha_fn-alpha)/alpha, (alpha_fp - alpha)/alpha,NULL, 1., NULL, -1.)
    dc[ns].set_np("TH",-sSMrel, sSMrel,NULL, 1., NULL, -1.)
    
    dc[ns].set_np(name_kpiT,(alpha_Tn-alpha)/alpha, (alpha_Tp - alpha)/alpha ,hspdf_Tp, sigma_hh, hspdf_Tn, -1.*sigma_hh)
    for i in range(1,8):
        dc[ns].set_np(name_n[i+1],0., 0.,hspdf_p[i], sigma_hh, hspdf_n[i], -1.*sigma_hh)
  
    dc[ns].make(hspdf,ns,0,1, "2012")
    dc[str(ns) + "_no_syst"].make(hspdf,ns,0,1, "2012")
    return dc
    ## print "ooooo"
#fDat = TFile("Data_2012_Bsmm_TOP_SECRET.root")
#DataHist = fDat.Get("hbpdf 2012")

if CHANNEL == "Bs":
    fDat = TFile("~/public/Bsmm1fbLNF.root")#/afs/cern.ch/user/d/diegoms/public/top_secret/unblind_bsmumu_1fb_histo.root")
    DataHist = fDat.Get("xyz")
else:
    fDat = TFile("~/public/for_Mathieu/Data_Bd_Comb.root")#/afs/cern.ch/user/d/diegoms/public/top_secret/unblind_bsmumu_1fb_histo.root")
    DataHist = fDat.Get("xyz")

## bin 0: 258.618       1.26794
## bin 1: 256.487       3.17734
## bin 2: 127.459       2.7064
## bin 3: 253.37       8.19294
## bin 4: 747.945       36.0911
## bin 5: 245.33       8.19294
## bin 6: 121.928       2.7064
## bin 7: 242.394       3.17734
## bin 8: 240.458       1.26794


def checkpdfs():
    hbpdf.Scale(Nb)
    hspdf.Scale(TheTable.Bsmumu_BR/alpha)
    hmisid.Scale(MISID)
    

