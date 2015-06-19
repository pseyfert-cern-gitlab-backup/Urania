# ==================================================
# Some helpers for the exclusive bkg evaluation 
from betaparam import *
from errors import *
from math import * 
from alphaparam_Autumn2012 import fsfd, BuBR
from ROOT import TFile, TH1D, TH2D, TProfile
from texlper import *

beta11, beta_s11, beta_lambda11 = beta2011()
beta12, beta_s12, beta_lambda12 = beta2012()


def check(chname='Lbpmunu'):  
    """ print the exclusive bkg information
    """
    def sval(vname):
        sname = chname+str(vname)
        v = eval(sname)
        return v
    print ' ---------------------------------- '
    print ' Value for: ',chname
#    print ' Luminosity in fb-1  ',luminosity
    print ' BR ',sval('_BR')
#    print ' Eff recsel ',sval('_recsel_eff')
    print ' Eff trg ',sval('_trg_eff')
    print ' Eff tot ',sval('_tot_eff')
#    print ' Channel Crossection ', sval('_cross')
    print ' Expected events 2011 ', sval('_exp11')
    print ' Expected events 2012 ', sval('_exp12')
#    print ' Expected events 2011 (mw) ', sval('_exp11_mw')
#    print ' Expected events 2012 (mw) ', sval('_exp12_mw')
    
def eff_EVal(n,N):
    eff = n/N 
    eff_err = sqrt(eff*(1-eff)/N)
    return EVal(eff, eff_err)

def printTable(histo, normalization):
    proj = histo.ProjectionY("",1, histo.GetNbinsX())#override stupid root defaults
    prof = histo.ProfileY()
    ntot = EVal(histo.GetSum(),0.)
    mynorm = normalization / ntot
    bdt_g05 = EVal(0,0)
    bdt_g08 = EVal(0,0)
    print mynorm
    print "BDT bin \t & $N_{exp}$ &  f  \\\\"
    lastbins = EVal(0.,0.)
    for i in range(1,9):
        n  = EVal(proj.GetBinContent(i), proj.GetBinError(i))
        if val(n)>0 :
            if i>=5 : bdt_g05 = bdt_g05 + n
            if i>=7 :
                bdt_g08 = bdt_g08 + n
                lastbins = lastbins + n 
            nnorm = mynorm * n 
            frac = n / ntot
#            frac.error[0] = sqrt(val(frac)*(1-val(frac))/val(ntot)) this gives same results so I leave the automatic one
            print  i , " \t &" ,tex(nnorm) , "\t & " , tex(frac,3), "\\\\"
        else :
            n = EVal(2.30,0)
            nnorm = mynorm * n
            frac = n / ntot
            print  i , " \t &" , "<", tex(nnorm) , "\t & ",  "\\\\"
    nnorm = mynorm * lastbins
    frac =  lastbins / ntot
    print "7\\&8" , " \t &" ,tex(nnorm) , "\t & " , tex(frac,3), "\\\\"

    
    
    bdt_g05norm = mynorm * bdt_g05
    bdt_g08norm = mynorm * bdt_g08 
    print "BDT>0.5 \t & ",  tex(bdt_g05norm)
    print "BDT>0.8 \t & ",  tex(bdt_g08norm)
    

def histError(hist):
    nbins = hist.GetNbinsX()
    err = 0
    for i in range(1, nbins) :
        err = err +  hist.GetBinError(i)
    return err 
        

def printVector(histo, normalization):
    ntot = EVal(histo.GetSum(),0.)
#    print "print vector norma " , normalization
    mynorm = normalization / ntot
#    print "print vector m", mynorm 
    nbins = histo.GetNbinsX()
    for i in range(1, nbins+1):
        n  = EVal(histo.GetBinContent(i), histo.GetBinError(i))
        if val(n)>0 :
            nnorm = mynorm * n 
            print  tex(nnorm) , "\t & " ,
        else :
            n = EVal(2.30,0)
            nnorm = mynorm * n
            print  "<", tex(nnorm) ,"\t ",
    print " " 
    

#============================================================
# Lambdab to p l nu 
# Branching ratio calculation

#Lbpmunu_gamma = EVal(6.48e12,0) # partial gammma = 6.48e12*vub^2
print "============================================================"
print "    Lb-> p mu nu    " 
Lbpmunu_gamma = EVal(6.48e12,3.24e12) # partial gammma = 6.48e12*vub^2

Lbpmunu_tau = EVal(1.425e-12, 0.032e-12)
vub = EVal(4.15e-3, 0.49e-3)
#Lbpmunu_BR = Lbpmunu_tau * Lbpmunu_gamma * vub * vub
Lbpmunu_BR = EVal(5.1e-4, 2.2e-4)

# Efficiencies
Lbpmunu_gen_eff    = EVal(0.1975,0.0006) 
Lbpmunu_trg_eff = EVal(1.,0.) # already included in recseleff

Lbpmunu_f2011 = TFile("LbStrip17_ptbdt.root")
Lbpmunu_h2011 = Lbpmunu_f2011.Get("hptbdt")
Lbpmunu_f2012 = TFile("LbStrip19a_ptbdt.root")
Lbpmunu_h2012 = Lbpmunu_f2012.Get("hptbdt")
Lbpmunu_tot11 = Lbpmunu_h2011.GetSum()
Lbpmunu_tot12 = Lbpmunu_h2012.GetSum()
Lbpmunu_recsel_eff11 = eff_EVal(Lbpmunu_tot11, 514496)
Lbpmunu_recsel_eff12 = eff_EVal(Lbpmunu_tot12, 514496)

Lbpmunu_tot_eff11 = Lbpmunu_recsel_eff11 * Lbpmunu_gen_eff
Lbpmunu_tot_eff12 = Lbpmunu_recsel_eff12 * Lbpmunu_gen_eff

# expected number 
#Lbpmunu_cross = sigma_bb * 2 * f_lb * Lbpmunu_BR
#Lbpmunu_expected = luminosity * Lbpmunu_cross * Lbpmunu_tot_eff 

flambda =  flambdab(Lbpmunu_h2011.ProjectionX().GetMean()/1000.)
beta_lambda11 = flambda* beta11 /f_bu
flambda =  flambdab(Lbpmunu_h2012.ProjectionX().GetMean()/1000.)
beta_lambda12 = flambda* beta12 /f_bu

Lbpmunu_exp11 = beta_lambda11 * Lbpmunu_BR * Lbpmunu_tot_eff11
Lbpmunu_exp12 = beta_lambda12 * Lbpmunu_BR * Lbpmunu_tot_eff12
print "N_{exp}^{2011} = ", tex(Lbpmunu_exp11)
print "N_{exp}^{2012} = ", tex(Lbpmunu_exp12)
print " Bs mw " 
Lbpmunu_f2011_mw = TFile("LbStrip17_bsmwbdt.root")
Lbpmunu_h2011_mw = Lbpmunu_f2011_mw.Get("bsmwbdt")
Lbpmunu_f2012_mw = TFile("LbStrip19a_bsmwbdt.root")
Lbpmunu_h2012_mw = Lbpmunu_f2012_mw.Get("bsmwbdt")
Lbpmunu_herr11 = histError(Lbpmunu_h2011_mw)
Lbpmunu_herr12 = histError(Lbpmunu_h2012_mw)
#print " total = " , Lbpmunu_h2011_mw.GetSum() , " +- " , Lbpmunu_herr11
Lbpmunu_exp11_mw = beta_lambda11 * EVal(Lbpmunu_h2011_mw.GetSum()/514496, Lbpmunu_herr11/514496) * Lbpmunu_gen_eff * Lbpmunu_BR
Lbpmunu_exp12_mw = beta_lambda12 * EVal(Lbpmunu_h2012_mw.GetSum()/514496, Lbpmunu_herr12/514496) * Lbpmunu_gen_eff * Lbpmunu_BR

print "N_{exp}^{2011} (mw) = ", tex(Lbpmunu_exp11_mw)
print "N_{exp}^{2012} (mw) = ", tex(Lbpmunu_exp12_mw)
printVector(Lbpmunu_h2011_mw,Lbpmunu_exp11_mw)
printVector(Lbpmunu_h2012_mw,Lbpmunu_exp12_mw)
print " Bd mw " 
Lbpmunu_f2011_bdmw = TFile("LbStrip17_bdmwbdt.root")
Lbpmunu_h2011_bdmw = Lbpmunu_f2011_bdmw.Get("bdmwbdt")
Lbpmunu_f2012_bdmw = TFile("LbStrip19a_bdmwbdt.root")
Lbpmunu_h2012_bdmw = Lbpmunu_f2012_bdmw.Get("bdmwbdt")
Lbpmunu_herr11_bd = histError(Lbpmunu_h2011_bdmw)
Lbpmunu_herr12_bd = histError(Lbpmunu_h2012_bdmw)
Lbpmunu_exp11_bdmw = beta_lambda11 * EVal(Lbpmunu_h2011_bdmw.GetSum()/514496, Lbpmunu_herr11_bd/514496) * Lbpmunu_gen_eff * Lbpmunu_BR
Lbpmunu_exp12_bdmw = beta_lambda12 * EVal(Lbpmunu_h2012_bdmw.GetSum()/514496, Lbpmunu_herr12_bd/514496) * Lbpmunu_gen_eff * Lbpmunu_BR
print "N_{exp}^{2011} (mw) = ", tex(Lbpmunu_exp11_bdmw)
print "N_{exp}^{2012} (mw) = ", tex(Lbpmunu_exp12_bdmw)
printVector(Lbpmunu_h2011_bdmw,Lbpmunu_exp11_bdmw)
printVector(Lbpmunu_h2012_bdmw,Lbpmunu_exp12_bdmw)





#Lbpmunu_exp11_mw = beta_lambda11 * Lbpmunu_BR * Lbpmunu_tot_eff_mw
#Lbpmunu_exp12_mw = beta_lambda12 * Lbpmunu_BR * Lbpmunu_tot_eff_mw

def lambdaTable(histo):
    proj = histo.ProjectionY("",1, histo.GetNbinsX())#override stupid root defaults
    prof = histo.ProfileY()
    print "\\toprule " 
    print "BDT bin \t & $p_T$ \t  & $f_{\Lambda}$ \t & $\\beta$ \t & $N_{exp}$ \t & f \\\\"
    print "\\midrule "
    nexp = []
    nseen = []
    flambda = []
    beta = []
    pt = []
    for i in range(1,9):
        pt.append(EVal(prof.GetBinContent(i),prof.GetBinError(i)))
        nseen.append(EVal(proj.GetBinContent(i), proj.GetBinError(i)))
        flambda.append(flambdab(pt[i-1]/1000.))
        #    print "lambda = ",  tex(flambda)
        beta.append(flambda[i-1] * beta11 /f_bu)
        #    print "beta = ", tex(beta)
        eff = nseen[i-1]/514496.
        nexp.append(beta[i-1] * Lbpmunu_BR * eff  *Lbpmunu_gen_eff)
    totalexp = EVal(0,0)
    total = EVal(0,0)
    for n in nexp:
        totalexp = n + totalexp
    for n in nseen:
        total = n + total 
        
    print "Table N_{exp} =  " ,tex(totalexp)
    for i in range(1,9):
        print  i , " \t &" , tex(pt[i-1]), "\t & "#, tex(n) , "\t & " 
        frac = nexp[i-1]/totalexp
        print tex(flambda[i-1]), "\t & ", tex(beta[i-1]), "\t & "
        print tex(nexp[i-1]) , " \t & ", tex(frac), " \\\\"
    print " \\bottomrule" 

lambdaTable(Lbpmunu_h2011)
lambdaTable(Lbpmunu_h2012)

print "============================================================"
print "   B+ -> pi+ mu mu   " 
# B+ -> pi mu mu 
bupimumu_BR = EVal(2.3e-8,0.6e-8)
#bupimumu_gen_eff = EVal(0.4985,0.001026)
bupimumu_gen_eff = EVal(0.264, 0.001)# Patrick Robbe 17102012
#bupimumu_gen_eff = EVal(0.15,0.001026)
#bupimumu_recsel_eff = eff_EVal(125, 512996.) #in sidebands bdt>0.8
bupimumu_f= TFile("BuPiMuMu_MCcorrected_MvsBDT.root")
bupimumu_hmbdt = bupimumu_f.Get("MvsBdt")
bupimumu_selected = bupimumu_hmbdt.GetSum()
print "bupimumu selected " , bupimumu_selected 
bupimumu_recsel_eff = eff_EVal(bupimumu_selected, 506996+506499) #in sidebands ,without peak bdt>0.5
bupimumu_trg_eff = EVal(1., 0.)#already included in recsel eff
bupimumu_tot_eff  = bupimumu_gen_eff * bupimumu_recsel_eff * bupimumu_trg_eff
###bupimumu_cross = sigma_bb * 2 * f_bu * bupimumu_BR
bupimumu_exp11 = beta11 * bupimumu_tot_eff * bupimumu_BR
bupimumu_exp12 = beta12 * bupimumu_tot_eff * bupimumu_BR
check("bupimumu")
printTable(bupimumu_hmbdt, bupimumu_exp11 )
printTable(bupimumu_hmbdt, bupimumu_exp12 )

pi0mumu_ratio = EValAsym(0.47, 0.22, -0.18)

bdpi0mumu_exp11 = pi0mumu_ratio * bupimumu_exp11 
bdpi0mumu_exp12 =  pi0mumu_ratio * bupimumu_exp12
print "B0->pi0mumu exp  "
print "N_{exp}^{2011} = ", tex(bdpi0mumu_exp11)
print "N_{exp}^{2012} = ", tex(bdpi0mumu_exp12)
print " Total pi0+ mumu is " 
print  "N_{exp}^{2011} = ", tex((pi0mumu_ratio+EVal(1,0)) * bupimumu_exp11 )
print  "N_{exp}^{2012} = ", tex((pi0mumu_ratio+EVal(1,0)) * bupimumu_exp12 )



print "============================================================"
print "   Bc->Jpsi mu nu " 
# Bc -> jpsi  mu nu
bcjpsimunu_BR = EVal(0.5* 5.2e-5, 0.5* 2.4e-5)#this also includes f_c
jpsimumu_BR = EVal( 0.0593, 0.0006)
bcjpsimunu_BR = bcjpsimunu_BR * jpsimumu_BR #not used actually now 

bcjpsimunu_tot = 508997
#bcjpsimunu_gen_eff = EVal(0.8102, 0.000530)
bcjpsimunu_gen_eff = EVal(0.137, 0.001) # Patrick Robbe 17102012
# Cross section ratio sigma(Bc)*BR(Bc)/(sigma(B+)BR(B+)
bcjpsimunu_ratio = EValAsym( 0.132, sqrt(0.041**2 + 0.031**2 + 0.0032), sqrt(0.037**2 + 0.031**2 + 0.020**2)) #CDF paper 

mynorm = bcjpsimunu_ratio * BuBR * EVal(0.5, 0)#this already includes also jpsimumu in the BuBR 
#remember alway divide a factor 2 because only muons  are considered

f = TFile("BcJpsiMuNu_mbdt.root")
bcjpsimunu_hmbdt = f.Get("MvsBdt")
bcjpsimunu_selected = bcjpsimunu_hmbdt.GetSum()
print "selected ", bcjpsimunu_selected
proj = bcjpsimunu_hmbdt.ProjectionY("",1, bcjpsimunu_hmbdt.GetNbinsX())#override stupid root defaults
#proj.Draw()
def massBc():
    proj = bcjpsimunu_hmbdt.ProjectionY("",1, bcjpsimunu_hmbdt.GetNbinsX())#override stupid root defaults
    proj.Draw()
    for i in range(1,9):
        n = EVal(proj.GetBinContent(i), proj.GetBinError(i))
        eff = n/bcjpsimunu_tot
        nexp = ( mynorm * beta11)* eff * bcjpsimunu_gen_eff 
        #    print n , " " , eff
        print "bdt bin", i, " & ", nexp

bcjpsimunu_recsel_eff = eff_EVal(bcjpsimunu_selected,bcjpsimunu_tot)
bcjpsimunu_trg_eff = EVal(1., 0.)#already included in recsel eff
bcjpsimunu_tot_eff  = bcjpsimunu_gen_eff * bcjpsimunu_recsel_eff * bcjpsimunu_trg_eff
bcjpsimunu_exp11 = (mynorm * beta11) * bcjpsimunu_tot_eff 
bcjpsimunu_exp12 = (mynorm * beta12) * bcjpsimunu_tot_eff
printTable(bcjpsimunu_hmbdt,bcjpsimunu_exp11 )
printTable(bcjpsimunu_hmbdt,bcjpsimunu_exp12 )        

crossold = sigma_bb * 2 * bcjpsimunu_BR
crossnew = (beta11/f_bu) *bcjpsimunu_BR
crossnewer = (mynorm * beta11)
expold = crossold * bcjpsimunu_tot_eff 
print "cross old " , crossold
print "cross new " , crossnew
print "cross newer", crossnewer 
print "exp old " , expold
check("bcjpsimunu")






