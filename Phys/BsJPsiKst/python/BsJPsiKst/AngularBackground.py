from ROOT import *
from math import *


print "Class for fitting angular background: AngularBkgPDF"

#gROOT.ProcessLine(".x /dos/Trabajo/Usefulthings/lhcbstyle_2.C")

class AngularBkgPDF:
    def __init__(self):

        self.Phi = RooRealVar("PhiP","PhiP",-1.*pi,pi)
        self.CPsi = RooRealVar("CPsi","CPsi",-1.,1.)
        self.CTheta = RooRealVar("CTheta","CTheta",-1.,1.)



        ## Acceptance parameters                                                                                                                                                        

        self.c1_psi = RooRealVar("c1_psi","c1_psi",-2.,0.)
        self.c2_psi = RooRealVar("c2_psi","c2_psi",-2,0.)
        self.c3_psi = RooRealVar("c3_psi","c3_psi",-2,2.)
        self.c4_psi = RooRealVar("c4_psi","c4_psi",-1,1.)

        self.y = RooRealVar("y","y",0.)#,3.)
#         self.c3_psi = RooFormulaVar("c3_psi","c3_psi","y + (-1.-c1_psi-c2_psi)",RooArgList(self.y,self.c1_psi,self.c2_psi))
        self.c5_psi = RooFormulaVar("c5_psi","c5_psi","y + (-1.-c1_psi-c2_psi-c3_psi-c4_psi)",RooArgList(self.y,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
#         self.c5_psi = RooRealVar("c5_psi","c5_psi",0.,5.)                                                                                                                  

        self.c1_theta = RooRealVar("c1_theta","c1_theta",0)#)
        self.c2_theta = RooRealVar("c2_theta","c2_theta",-1.,1.)

        #Polynom.
        self.c1_phi = RooRealVar("c1_phi","c1_phi",-4.38046e-01, -1,1)
        self.c2_phi = RooRealVar("c2_phi","c2_phi",1.24342e-01,-1,1)
        self.c3_phi = RooRealVar("c3_phi","c3_phi",4.63368e-02,-1,1)
        
        #Sin
#         self.c1_phi = RooRealVar("c1_phi_bkg","c1_phi_bkg", 1.,10.)
#         self.c2_phi = RooRealVar("c2_phi_bkg","c2_phi_bkg",0.1,5.)
#         self.c3_phi = RooRealVar("c3_phi_bkg","c3_phi_bkg",-pi, pi)
        
##         self.c1_phi = RooRealVar("c1_phi","c1_phi",-pi/2.,pi/2.)#0.,2.) 
##         self.c2_phi = RooRealVar("c2_phi","c2_phi",0.,3.)
##         self.c3_phi = RooRealVar("c3_phi","c3_phi",-pi/2.,pi/2.)
##         self.c4_phi = RooRealVar("c4_phi","c4_phi",0.,0.5)
##         self.c5_phi = RooRealVar("c5_phi","c5_phi",0.,6.)
##         self.c6_phi = RooRealVar("c6_phi","c6_phi",-pi/2.,pi/2.)



        ## Model

        self.psibkg = RooPolynomial("psibkg","psibkg",self.CPsi,RooArgList(self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi,self.c5_psi))

        self.thetabkg = RooPolynomial("thetabkg","thetabkg",self.CTheta,RooArgList(self.c1_theta,self.c2_theta))

#         self.phibkg = RooGenericPdf("phibkg","phibkg","1+c1_phi*cos(c2_phi*PhiP + c3_phi)",RooArgList(self.Phi,self.c1_phi,self.c2_phi,self.c3_phi))

        self.phibkg = RooGenericPdf("phibkg","phibkg","1+c1_phi*PhiP + c2_phi*PhiP*PhiP + c3_phi*PhiP*PhiP*PhiP",RooArgList(self.Phi,self.c1_phi,self.c2_phi,self.c3_phi))
#         self.phibkg = RooGenericPdf("phibkg","phibkg","c1_phi_bkg +sin(c2_phi_bkg*PhiP + c3_phi_bkg)",RooArgList(self.Phi,self.c1_phi,self.c2_phi,self.c3_phi))

        self.bkgmodel = RooProdPdf("bkgmodel","bkgmodel",RooArgList(self.psibkg,self.thetabkg,self.phibkg))

        


if __name__=="__main__":


    f=TFile("~diegoms/vol5/BsJPsiKst_341_v2.root")
    t2=f.Get("T/T")


    cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6"
    #cuts += "&& Bmass_JC<(5279-25)"
    cuts += "&& Bmass_JC>(5366.3+50) "
    cuts += "&& kaon_pt>500 && pion_pt>500"
    cuts += "&& abs(Mjpsik-5279)>60"
    cuts += "&& abs(KstMass-896)<40"
    #cuts += "&& Bmass_JC>5150 && Bmass_JC<5600"
    trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"

    cuts += " && "+ trigger


    f2=TFile("nada.root","recreate")
    t=t2.CopyTree(cuts+"&& GL11sb.>0.2")


    fit = AngularBkgPDF()

    fit.c1_psi.setVal(-0.522)
    fit.c2_psi.setVal(-0.723)
    fit.c3_psi.setVal(-0.19)
    fit.c4_psi.setVal(0.208)
##     fit.y.setVal(1.07372e-09)
    fit.c1_theta.setVal(0.)
    fit.c2_theta.setVal(-1.78335e-01)

    fit.c1_psi.setVal(-0.565)
    fit.c2_psi.setVal(-0.7)
    fit.c3_psi.setVal(-0.04)
    fit.c4_psi.setVal(-0.1)
##     fit.y.setVal(1.07372e-09)
    fit.c1_theta.setVal(0.)
    fit.c2_theta.setVal(-0.04)
##     fit.c1_phi.setVal(7.84410e-02)
##     fit.c2_phi.setVal(1.95819e+00)
##   ##   fit.c3_phi.setVal(2.49770e-01)
## ##     fit.c4_phi.setVal(0.)
## ##     fit.c6_phi.setVal(0.)
## ##     fit.c5_phi.setVal(0.)


    fit.c1_psi.setConstant(1)                                                                                                                                                
    #fit.c2_psi.setConstant(1)                                                                                                                                                
    fit.c3_psi.setConstant(1)                                                                                                                                                
    fit.c4_psi.setConstant(1)                     
    
##     fit.y.setConstant(1)                                                                                                                                                     
    fit.c1_theta.setConstant(1)                                                                                                                                              
    fit.c2_theta.setConstant(1)                       
    
#     fit.c1_phi.setConstant(1)                                                                                                                                                
#     fit.c2_phi.setConstant(1)                                                                                                                                                
#     fit.c3_phi.setConstant(1)                                                                                                                                                
  #  fit.c4_phi.setConstant(1)                                                                                                                                                
  #  fit.c6_phi.setConstant(1)                                                                                                                                                
  #  fit.c5_phi.setConstant(1)                                                                                                                                                



    dataset = RooDataSet("data","data",t,RooArgSet(fit.CPsi,fit.CTheta,fit.Phi))



    fitres = fit.bkgmodel.fitTo(dataset,RooFit.Minos(1),RooFit.Save())

    nbins = 8#10#30

#     cv3 = TCanvas()
#     cv3.SetFillColor(0)
#     cv3.Divide(2,2)

    cv31 = TCanvas()
#     cv3.cd(1)
    cpsif = fit.CPsi.frame()
    RooAbsData.plotOn(dataset,cpsif,RooFit.Binning(nbins))
    fit.bkgmodel.plotOn(cpsif)
    cpsif.Draw()

    cv32 = TCanvas()
#     cv3.cd(2)
    cthf = fit.CTheta.frame()
    RooAbsData.plotOn(dataset,cthf,RooFit.Binning(nbins))
    fit.bkgmodel.plotOn(cthf)
    cthf.Draw()

    cv33 = TCanvas()
#     cv3.cd(3)
    cphif = fit.Phi.frame()
    RooAbsData.plotOn(dataset,cphif,RooFit.Binning(nbins))
    padphi = fit.bkgmodel.plotOn(cphif)
    cphif.Draw()


    nll = fit.bkgmodel.createNLL(dataset)
    print "Min NLL: ",nll.getVal()
    nparam = 3
    nodf = nbins-nparam
    chi2 = padphi.chiSquare(nparam)*nodf
    print "Chi2/nodf: "+str(chi2)+"/"+str(nodf)
    
