from ROOT import *
from math import *
gROOT.ProcessLine(".x $BSJPSIKSTROOT/src/AngJpsiKst_Swave_ks.cxx++")
#gSystem.Load("AngJPsiKst_cxx")


print "Class for fitting polarization: AngularPDF"

CHANNEL = "Bd"
s_a = 3.
class AngularPDF:
    def __init__(self):

        self.Phi = RooRealVar("PhiP","PhiP",-1.*pi,pi)
        self.CPsi = RooRealVar("CPsi","CPsi",-1.,1.)
        self.CTheta = RooRealVar("CTheta","CTheta",-1.,1.)



        ## Parameters of interest
        
        self.A02 = RooRealVar("A02","A02",0.,1.)
        self.x1 = RooRealVar("x1","x1",0.,1.)
        self.ks1 = RooRealVar("ks1","ks1",-1.,1.)
        self.ks2 = RooRealVar("ks2","ks2",-1.,1)
        
        self.As2 = RooFormulaVar("As2","As2","x1*(1-A02)",RooArgList(self.x1,self.A02))
        self.x2 = RooRealVar("x2","x2",0.,1.)

        #self.Ape2 = RooFormulaVar("Ape2","Ape2","x2*(1-A02-Apa2)",RooArgList(self.x2,self.A02,self.Apa2))

        self.Apa2 = RooFormulaVar("Apa2","Apa2","x2*(1-A02-As2)",RooArgList(self.x2,self.A02,self.As2))#RooRealVar("As2","As2", 0.,.1)
        self.As = RooFormulaVar("As","As","sqrt(As2)",RooArgList(self.As2))
        self.Ape2 = RooFormulaVar("Ape2","Ape2","1-A02-Apa2-As2",RooArgList(self.A02,self.Apa2,self.As2))
        self.A0 = RooFormulaVar("A0","A0","sqrt(A02)",RooArgList(self.A02))
        self.Apa = RooFormulaVar("Apa","Apa","sqrt(Apa2)",RooArgList(self.Apa2))
        self.Ape = RooFormulaVar("Ape","Ape","sqrt(Ape2)",RooArgList(self.Ape2))
        
        #self.As = RooFormulaVar("As","As","sqrt(1-A02-Apa2-Ape2)",RooArgList(self.A02,self.Apa2,self.Ape2))


        

        self.dpa = RooRealVar("dpa","dpa",-pi,0)
      


        ## Acceptance
        
        self.c1_psi = RooRealVar("c1_psi","c1_psi",-0.488,-0.488-s_a*0.014,-0.488+s_a*.014)
        self.c2_psi = RooRealVar("c2_psi","c2_psi",-0.642,-0.642-s_a*0.022,-0.642+s_a*0.022)
        self.c3_psi = RooRealVar("c3_psi","c3_psi",-0.331,-0.331-3*s_a,0.331+3*s_a)
        self.c4_psi = RooRealVar("c4_psi","c4_psi",0.092,0.092-s_a*0.023,0.092+s_a*0.023)

        
        self.y = RooRealVar("y","y",0.,0.,s_a*1.6e-04)
        self.c5_psi = RooFormulaVar("c5_psi","c5_psi","y + (-1.-c1_psi-c2_psi-c3_psi-c4_psi)",RooArgList(self.y,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
        # self.c5_psi = RooRealVar("c5_psi","c5_psi",0.,5.)
        self.c1_theta = RooRealVar("c1_theta","c1_theta",0)
        self.c2_theta = RooRealVar("c2_theta","c2_theta",-0.1783,-0.1783-s_a*0.0075,-0.1783+s_a*0.0075)

        self.c1_phi = RooRealVar("c1_phi","c1_phi",0.0784,0.0784-s_a*0.0039,0.0784+s_a*0.0039)
        self.c2_phi = RooRealVar("c2_phi","c2_phi",1.958,1.958-s_a*0.029,1.958+s_a*0.029)
        self.c3_phi = RooRealVar("c3_phi","c3_phi",.25,.25-s_a*0.048,.25+s_a*0.048)
       

        ## Model

        # Signal

        self.sigmodel = AngJpsiKst_Swave_ks("sigmodel","sigmodel",self.CPsi,self.CTheta,self.Phi,self.A0,self.Apa,self.Ape,self.As,self.dpa,self.ks1,self.ks2,
                                   self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi,self.c5_psi,self.c2_theta,self.c1_phi,self.c2_phi,self.c3_phi)



        # Background

        self.c1_phi_bkg = RooRealVar("c1_phi_bkg","c1_phi_bkg",-4.38046e-01)
        self.c2_phi_bkg = RooRealVar("c2_phi_bkg","c2_phi_bkg",1.24342e-01)
        self.c3_phi_bkg = RooRealVar("c3_phi_bkg","c3_phi_bkg",4.63368e-02)


        self.psibkg = RooPolynomial("psibkg","psibkg",self.CPsi,RooArgList(self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi,self.c5_psi))

        self.thetabkg = RooPolynomial("thetabkg","thetabkg",self.CTheta,RooArgList(self.c1_theta,self.c2_theta))

        self.phibkg = RooGenericPdf("phibkg","phibkg","1+c1_phi_bkg*PhiP + c2_phi_bkg*PhiP*PhiP + c3_phi_bkg*PhiP*PhiP*PhiP",RooArgList(self.Phi,self.c1_phi_bkg,self.c2_phi_bkg,self.c3_phi_bkg))

        self.bkgmodel = RooProdPdf("bkgmodel","bkgmodel",RooArgList(self.psibkg,self.thetabkg,self.phibkg))

        self.fsig = RooRealVar("fsig","fsig",0.,1)
        self.model = RooAddPdf("model","model",self.sigmodel,self.bkgmodel,self.fsig)



if __name__=="__main__":


    f=TFile("~diegoms/vol5/BsJPsiKst_341_v2.root")
    t2=f.Get("T/T")


    cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 "
#     cuts += "&& Bmass_JC>5150 && Bmass_JC<5800"
#     cuts += "&& abs(Bmass_JC-5279.5)<25"
    
    cuts += "&& kaon_pt>500 && pion_pt>500"
    if CHANNEL =="Bs":
        cuts += "&& abs(Bmass_JC-5366.3)<25"
        _fsig = 0.13
    else:
        cuts += "&& abs(Bmass_JC-5279)<25"
        _fsig = 1-2.1e-03
        
    cuts += "&& abs(Mjpsik-5279)>60"
    cuts += "&& abs(KstMass-896)<40"

    trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"

    cuts += " && "+ trigger


    f2=TFile("nada.root","recreate")
    t=t2.CopyTree(cuts+"&& GL11sb.>0.2")

    

    
    fit = AngularPDF()
   


    fit.c1_psi.setVal(-4.88466e-01)
    fit.c2_psi.setVal(-6.42425e-01)
    fit.c3_psi.setVal(-3.30868e-01)
    fit.c4_psi.setVal(9.19671e-02)
    fit.y.setVal(1.07372e-09)
    
    fit.c2_theta.setVal(-1.78335e-01)
    fit.c1_phi.setVal(7.84410e-02)
    fit.c2_phi.setVal(1.95819e+00)
    fit.c3_phi.setVal(2.49770e-01)

    fit.c1_psi.setConstant(1)
    fit.c2_psi.setConstant(1)
    fit.c3_psi.setConstant(1)
    fit.c4_psi.setConstant(1)
    fit.y.setConstant(1)
    
    fit.c2_theta.setConstant(1)
    fit.c1_phi.setConstant(1)
    fit.c2_phi.setConstant(1)
    fit.c3_phi.setConstant(1)
   
    fit.fsig.setVal(_fsig)
    fit.fsig.setConstant(1)
    


    dataset = RooDataSet("data","data",t,RooArgSet(fit.CPsi,fit.CTheta,fit.Phi))


        
    fitres = fit.model.fitTo(dataset,RooFit.Minos(1),RooFit.Save())

    nbins = 9

    cv3 = TCanvas()
    cv3.SetFillColor(0)
    cv3.Divide(2,2)

    cv3.cd(1)
    cpsif = fit.CPsi.frame()
    RooAbsData.plotOn(dataset,cpsif,RooFit.Binning(nbins))
    fit.model.plotOn(cpsif)
    fit.model.plotOn(cpsif,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    fit.model.plotOn(cpsif,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    fit.model.paramOn(cpsif)
    cpsif.Draw()

    cv3.cd(2)
    cthf = fit.CTheta.frame()
    RooAbsData.plotOn(dataset,cthf,RooFit.Binning(nbins))
    fit.model.plotOn(cthf)
    fit.model.plotOn(cthf,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    fit.model.plotOn(cthf,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    cthf.Draw()

    cv3.cd(3)
    cphif = fit.Phi.frame()
    RooAbsData.plotOn(dataset,cphif,RooFit.Binning(nbins))
    fit.model.plotOn(cphif)
    fit.model.plotOn(cphif,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    fit.model.plotOn(cphif,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    cphif.Draw()

    Apa2 = fit.Apa2.getVal()
    Apa2err = fit.Apa2.getPropagatedError(fitres)
    Ape2 = fit.Ape2.getVal()
    Ape2err = fit.Ape2.getPropagatedError(fitres)
    As2 = fit.As.getVal()**2
    As2err = 2*fit.As.getVal()*fit.As.getPropagatedError(fitres)



    print "Apa2 = %.6f"%Apa2+" + %.6f"%Apa2err
    print "Ape2 = %.6f"%Ape2," + %.6f"%Ape2err
    print "As2 = %.6f"%As2," + %.6f"%As2err


    fl = RooFormulaVar("fl","fl","A02/(A02+Apa2+Ape2)",RooArgList(fit.A02,fit.Apa2,fit.Ape2))
    flerr = fl.getPropagatedError(fitres)
    print "f_L = %.3f"%fl.getVal()," + %.3f"%flerr

#print "Apa2 = %.6f"%Apa2+" + %.6f"%Apa2err
#print "Ape2 = %.6f"%Ape2," + %.6f"%Ape2err
#print "As2 = %.6f"%As2," + %.6f"%As2err
