from ROOT import *
from os import *
from SomeMassModels import B2JpsiModels as B

print " ciao!"
    
from math import *
import cutStrings as cs

def getNormBu_lnf():

    #on afs, you should be able to read this path, careful,
    #its not eaxctly the right file
    f=TFile("/afs/cern.ch/project/lbcern/vol2/albrecht/Bs2mm/JA_ntuples/1020_unblindSidebands_LNF/ForJohannes_B2JpsiK.root")    
    tK2 = f.Get("B2JpsiK")#

    #f=TFile("Test10pb_2012.root")
    #tK2 = f.Get("B2JpsiKTuple/DecayTree")



    print "tree has ",tK2.GetEntries()," entries"
    print "cuts applied",cs.minimalNormBu_lnf
    print "tree has ",tK2.GetEntries(cs.minimalNormBu_lnf)," entries after cuts"
    #return
    #fitBu = B.BuJPsiK(tK,"Bplus_M","fabs(Bplus_M-5279.17)<100&&fabs(J_psi_1S_M-3096.916)<60&&Jpsi_dist_chi2_r>15")
    #fitBu = B.BuJPsiK(tK2,"Bplus_JCMass","fabs(Bplus_JCMass-5279.17)<100&&fabs(J_psi_1S_M-3096.916)<60&&Jpsi_dist_chi2_r>15")
    
   

    fitBu = B.BuJPsiK(tK2,"Bplus_JCMass",cs.minimalNormBu_lnf)


    fitBu.fsh.setVal(0)
    fitBu.fsh.setConstant(kTRUE)
    fitBu.sh_mean.setConstant(kTRUE)
    fitBu.sh_sigma.setConstant(kTRUE)
    fitBu.fit()


#    fitBu.fit()
    print "Bu-->JPsi K+ nSignal: ",fitBu.nsig.getVal()," +- ",fitBu.nsig.getError()," and S/B: " ,  fitBu.nsig.getVal()/(1.*fitBu.nbkg.getVal())
     
    ef=fitBu.f1.getError()/fitBu.f1.getVal()
    es1=fitBu.sigma1.getError()/fitBu.sigma1.getVal()
    es2=sqrt((fitBu.sigma1.getError()/fitBu.sigma1.getVal())**2+(fitBu.delta_s.getError()/(fitBu.sigma1.getVal()+fitBu.sigma2.getVal()))**2)
    res=fitBu.f1.getVal()*fitBu.sigma1.getVal()+(1-fitBu.f1.getVal())*fitBu.sigma2.getVal()
    eres=sqrt(ef**2+es1**2)*fitBu.f1.getVal()*fitBu.sigma1.getVal()+sqrt(ef**2+es2**2)*(1-fitBu.f1.getVal())*fitBu.sigma2.getVal()

    print "resolution: ",res," +- ",eres
    return fitBu



def getNormBs_lnf():

    
    f=TFile("~/NTuples/1020_unblindSidebands_LNF/ForJohannes_B2JpsiPhi.root")
    tjpsiphi2 = f.Get("B2JpsiPhi")



   #f=TFile("~/NTuples/lnfTuples/allthree_B2JpsiKTupleeraseme.root")
    #f=TFile("/afs/cern.ch/project/lbcern/vol9/albrecht/stp17_Bsmm_blind_lnf_835pb.root")
    #tjpsiphi2 = f.Get("B2JpsiPhiTuple/DecayTree")    

    #f=TFile("~/NTuples/lnfTuples/allthree_B2JpsiPhiTupleeraseme.root")
    #tjpsiphi2 = f.Get("DecayTree")

    print cs.normBs_lnf
    fitBu = B.DoubleGaussian(tjpsiphi2,"B_s0_JCMass",cs.normBs_lnf)
#+"&&weightB>0",weight_var='weightB')
    

    print "Bs-->JPs Phi nSignal: ",fitBu.nsig.getVal()," +- ",fitBu.nsig.getError()," and S/B: " ,  fitBu.nsig.getVal()/(1.*fitBu.nbkg.getVal())

    ef=fitBu.f1.getError()/fitBu.f1.getVal()
    es1=fitBu.sigma1.getError()/fitBu.sigma1.getVal()
    es2=sqrt((fitBu.sigma1.getError()/fitBu.sigma1.getVal())**2+(fitBu.delta_s.getError()/(fitBu.sigma1.getVal()+fitBu.sigma2.getVal()))**2)
    res=fitBu.f1.getVal()*fitBu.sigma1.getVal()+(1-fitBu.f1.getVal())*fitBu.sigma2.getVal()
    eres=sqrt(ef**2+es1**2)*fitBu.f1.getVal()*fitBu.sigma1.getVal()+sqrt(ef**2+es2**2)*(1-fitBu.f1.getVal())*fitBu.sigma2.getVal()

    print "resolution: ",res," +- ",eres

    return fitBu

    
