# import anaFdFs
from ROOT import *
from os import *
#from BsMuMuPy.pyAna import B2JpsiModels as B
#from BsMuMuPy.pyAna import sidebands as S
from SomeMassModels import DsModels as B
S=0

#MeV/c^{2}
#m(#mu^{+}#mu^{-}#pi^{+})(MeV/c^{2})

#f=TFile("~/NTuples/tau23mu/matt/v1.2_tau23mu_md.root")
#f=TFile("~/NTuples/tau23mu/matt/v1.2_Ds23pi_md_10k.root")
#f=TFile("~/NTuples/tau23mu/matt/v1.2_Ds2PhiPi_md_10k.root")
#f=TFile("~/NTuples/tau23mu/stp15_j184_178pb.root")

#f=TFile("~/tauNT/stp15_tauDsDs_JAj201_pyNT_md_179pb.root")
#f=TFile("~/tauNT/stp15_tauDs_JAj201j203_pyNT_mud_250pb.root")
#f=TFile("~/tauNT/flatBDTtriggerS17_S17data.root")
#f=TFile("~/tauNT/flatBDTtriggerS17_dvLX762LX760.root")

#f=TFile("~/tauNT/s17_mu_noBDT_168pb_flat.root")
#f=TFile("~/tauNT/s17_md_noBDT_173pb_flat.root")
#f=TFile("/afs/cern.ch/user/a/albrecht/tauNT/stp17_mud_noBDT_698pb_flat.root")
#f=TFile("~/vol9/tau23mu/stp17_mud_BDTv2p2_1024pb_flat.root_merged.root")
f=TFile("~/vol9/tau23mu/stp17_forTISTOS_flat.root")
f.ls()

#tDs23 = f.Get("Ds23Pi")
#tDsPhi= f.Get("Ds2PhiPi")
#tDsPhi= f.Get("B24mu/B24mu")
tDsPhi= f.Get("Ds2PhiPi")#flatStrippingTau23MuDs2PhiPiLine")
tDs23= f.Get("flatStrippingTau23MuDs23PiLine")
tDs23TIS= f.Get("flatStrippingTau23MuDs23PiTISLine")
#from PDG
mBs = 5366.3
mBu = 5279.17
mBd = 5279.5
mJPsi = 3096.916
mPhi = 1019.455


#S15And17="Bpt>2000&&min(mu0pt,min(mu1pt,mu2pt))>300&&mu0track_Chi2DoF<4&&mu1track_Chi2DoF<4&&mu2track_Chi2DoF<4&&lessIPSmu>3.464&&Vchi2<15&&Blife_ctau>0.1&&Bips<3"
S15And17="1"#pt>2000"
#DsMass = '&&Bmass>1918.47&&Bmass<2018.47'
#DsMass = '&&abs(mass-1968.47)<70'#mass>1918.47&&mass<2018.47'
DsMass = '&&abs(mass-1970.2)<50'
tauMass = '&&Bmass>1700&&Bmass<1850'
#phiMass="&&abs(sqrt((mu2ptot+mu1ptot)**2+210**2-(mu2p1+mu1p1)**2-(mu2p2+mu1p2)**2-(mu2p3+mu1p3)**2))-1020<20"
phiMass="&&abs(mass_p1p2-1020.4)<20"
triggerDec="&&L0Dec&&Hlt1Dec&&Hlt2Dec"
clean="&&LifeTime>-0.01&&LifeTime<0.025&&dira>0.99&&mass_p0p1>250."

minPID="min(singlePID_p0,min(singlePID_p1,singlePID_p2))"

def getNormDs23pi():
    
    fitBu = B.SigGaussFiter(tDs23TIS,"mass","1"+DsMass+"&&VertexChi<10&&erstpt>500&firstpt>500&&secondpt>500&&IPSig<5")
    print "Bu-->JPsi K+ nSignal: ",fitBu.nsig.getVal()," +- ",fitBu.nsig.getError()," and S/B: " ,  fitBu.nsig.getVal()/(1.*fitBu.nbkg.getVal())

    res=fitBu.sigma.getVal()
    eres=fitBu.sigma.getError()

    print "resolution: ",res," +- ",eres
    return fitBu

bdt="&&GeoMVA>0.44"
def getNormDsPhi():
    
    #vpm="&&abs(mass_p1p2-1020)<5"

    fitBu = B.SigGaussFiter(tDsPhi,"mass","1"+DsMass+phiMass+triggerDec+clean)#+trg)
    #fitBu = B.SigGaussFiter(tDsPhi,"mass","1"+DsMass+trigger+vpm)  
   

    #fitBu = B.DoubleGaussian(tDsPhi,"mass","1"+DsMass+phiMass+trigger)
    #fitBu = B.SigCBFiter(tDsPhi,"mass","1"+DsMass+phiMass+trigger)

   #fitBu = B.SigGaussFiter(tDs23,"mass","1"+DsMass+"&&VertexChi<10&&erstpt>500&firstpt>500&&secondpt>500")
    #fitBu = B.DoubleGaussian(tDsPhi,"Bmass",commonCuts+DsMass)
    print "Bu-->JPsi K+ nSignal: ",fitBu.nsig.getVal()," +- ",fitBu.nsig.getError()," and S/B: " ,  fitBu.nsig.getVal()/(1.*fitBu.nbkg.getVal())
    '''
    ef=fitBu.f1.getError()/fitBu.f1.getVal()
    es1=fitBu.sigma1.getError()/fitBu.sigma1.getVal()
    es2=sqrt((fitBu.sigma1.getError()/fitBu.sigma1.getVal())**2+(fitBu.delta_s.getError()/(fitBu.sigma1.getVal()+fitBu.sigma2.getVal()))**2)
    res=fitBu.f1.getVal()*fitBu.sigma1.getVal()+(1-fitBu.f1.getVal())*fitBu.sigma2.getVal()
    eres=sqrt(ef**2+es1**2)*fitBu.f1.getVal()*fitBu.sigma1.getVal()+sqrt(ef**2+es2**2)*(1-fitBu.f1.getVal())*fitBu.sigma2.getVal()
    '''
  #  res=fitBu.sigma.getVal()
  #  eres=fitBu.sigma.getError()

   # print "resolution: ",res," +- ",eres
    return fitBu




def getNormTau():
    
    fitBu = B.SigGaussFiter(tDsPhi,"Bmass",commonCuts+tauMass)
 
    print "tau23mu nSignal: ",fitBu.nsig.getVal()," +- ",fitBu.nsig.getError()," and S/B: " ,  fitBu.nsig.getVal()/(1.*fitBu.nbkg.getVal())
 
    res=fitBu.sigma.getVal()
    eres=fitBu.sigma.getError()

    print "resolution: ",res," +- ",eres
    return fitBu


    
def sidebands():
    from SomeMassModels import sidebands as S
    
    cut="1"+phiMass+trigger
    #op = S.sidebandsFiter(tDsPhi, "mass",cut, left = 5225.5,right = 5328.5, Mmin = 5200, Mmax=5350,bkgf=S.exp_bkg)
    op = S.sidebandsFiter(tDsPhi, "mass",cut, left = 1930,right = 2010, Mmin = 1910, Mmax=2100,bkgf=S.exp_bkg)

    

    #lin_bkg
    #left and right give you the limits of the signal region 
    #bkgf is the bkg model for the subtraction, usually you could use S.exp_bkg but I added yesterday night also the linear bkg (do svn update of FiterBasis, moreover now you should not need any change for getting the right Bs mean), this one seems very reasonable for BsJpsiPhi for example.

    op1=op
    op.fitOneSB() 
    op2=op
    #print "fitoneSB", op.getSignal() 
    
    #shyould retunr you the no. of signal. Also will print in the screen two no.s thatt should *NOT* agree amongst them)

    #and from the right SB: 
    op.fitOneSB("right_SB")  ### The spelling is very important. RooFit does not crash if she gets an unknon range, nad just fits in all window!
    op3=op

    
    #print "right SB ", op.getSignal()

    
    print"op1"
    print "nSig: ",op1.getSignal()
    print ""
    print"op2"
    print "nSig: ",op2.getSignal()
    print ""
    print"op3"
    print "nSig: ",op3.getSignal()
    print ""

    return op1, op2, op3

'''
from Bs2MuMu.triggerclass import *
from Bs2MuMu.smartpyROOT import *

def getDuplicates():


    cuts="1"+"&&abs(mass_p1p2-1020)<20"+"&&L0Dec&&Hlt1Dec&&Hlt2Dec"


    tightDs="&&abs(mass-1968.47)<15"
    #tightDs="&&abs(mass-2168.47)<15"

    bdt=""#&&GeoMVA>0"
    
    cuts=cuts+tightDs+bdt
    
    
    print "cuts: ", cuts
    
    t2 = tDsPhi.CopyTree(cuts)
    
    ch = channelData(fromRootToListDic(t2, labels = ["eventNumber", "runNumber","mass"]))
    
  

    #x0 = max(ch.takeKey("evtNum"))
    #print "duplicate?", t2.GetEntries("Bmass>5279&&Bmass<5279.01")
    for entry in ch:
        entry["evt"] = entry["runNumber"] + 200000*entry["eventNumber"] 
  

    ch.checkForDuplicates()

    Ncand = len(ch)
    ch.agrupateInEvents()
    Nevt = len(ch)
    
    print "candidates: ",Ncand," in events: ",Nevt
    print "ratio : ",Ncand/(1.*Nevt)
'''
