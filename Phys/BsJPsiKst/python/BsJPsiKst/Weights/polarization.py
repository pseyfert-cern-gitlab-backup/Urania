from ROOT import *
from math import *
gROOT.ProcessLine(".x $BSJPSIKSTROOT/src/AngJPsiKst.cxx++")
#gSystem.Load("AngJPsiKst_cxx")


print "Class for fitting polarization: AngularPDF"



class AngularPDF:
    def __init__(self):

        self.Phi = RooRealVar("PhiP","PhiP",-1.*pi,pi)
        self.CPsi = RooRealVar("CPsi","CPsi",-1.,1.)
        self.CTheta = RooRealVar("CTheta","CTheta",-1.,1.)



        ## Parameters of interest
        
        self.A02 = RooRealVar("A02","A02",0.,1.)
        self.x = RooRealVar("x","x",0.,1.)
        self.Apa2 = RooFormulaVar("Apa2","Apa2","x*(1-A02)",RooArgList(self.x,self.A02))
        self.A0 = RooFormulaVar("A0","A0","sqrt(A02)",RooArgList(self.A02))
        self.Apa = RooFormulaVar("Apa","Apa","sqrt(Apa2)",RooArgList(self.Apa2))
        self.Ape = RooFormulaVar("Ape","Ape","sqrt(1-A02-Apa2)",RooArgList(self.A02,self.Apa2))
        self.cdpa = RooRealVar("cdpa","cdpa",-1.,1.)



        ## Acceptance

        self.c1_psi = RooRealVar("c1_psi","c1_psi",-1.,0.)#0.5,3.)
        self.c2_psi = RooRealVar("c2_psi","c2_psi",-1.5,0.)#-3.,-1.)
        self.c3_psi = RooRealVar("c3_psi","c3_psi",-0.7,0.7)#0.5,3.)#-1.,1.)
        self.c4_psi = RooRealVar("c4_psi","c4_psi",-0.7,0.7)#-3.,-1.)

        
        self.y = RooRealVar("y","y",0.,3.)
        self.c5_psi = RooFormulaVar("c5_psi","c5_psi","y + (-1.-c1_psi-c2_psi-c3_psi-c4_psi)",RooArgList(self.y,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
        # self.c5_psi = RooRealVar("c5_psi","c5_psi",0.,5.)

        self.c1_theta = RooRealVar("c1_theta","c1_theta",-1.,1.)
        self.c2_theta = RooRealVar("c2_theta","c2_theta",-1.,1.)

        self.c1_phi = RooRealVar("c1_phi","c1_phi",0.,2.)
        self.c2_phi = RooRealVar("c2_phi","c2_phi",0.,6.)
        self.c3_phi = RooRealVar("c3_phi","c3_phi",-pi/2.,pi/2.)
        self.c4_phi = RooRealVar("c4_phi","c4_phi",0.,0.5)
        self.c5_phi = RooRealVar("c5_phi","c5_phi",0.,6.)
        self.c6_phi = RooRealVar("c6_phi","c6_phi",-pi/2.,pi/2.)
        

        ## Model

        # Signal

        self.sigmodel = AngJPsiKst("sigmodel","sigmodel",self.CPsi,self.CTheta,self.Phi,self.A0,self.Apa,self.Ape,self.cdpa,
                                   self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi,self.c5_psi,self.c1_theta,self.c2_theta,self.c1_phi,self.c2_phi,self.c3_phi,self.c4_phi,self.c5_phi,self.c6_phi)



        






if __name__=="__main__":


    f=TFile("~diegoms/vol5/BsJPsiKst_341_v2.root")
    t2=f.Get("T/T")


    cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 "
#     cuts += "&& Bmass_JC>5150 && Bmass_JC<5800"
    cuts += "&& abs(Bmass_JC-5279.5)<25"
    cuts += "&& kaon_pt>500 && pion_pt>500"
    cuts += "&& abs(Mjpsik-5279)>60"
    cuts += "&& abs(KstMass-896)<40"

    trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"

    cuts += " && "+ trigger


    f2=TFile("nada.root","recreate")
    t=t2.CopyTree(cuts+"&& GL11sb.>0.2")

    

    
    fit = AngularPDF()

    
    
    fit.c1_psi.setVal(0)
    fit.c2_psi.setVal(0)
    fit.c3_psi.setVal(0)
    fit.c4_psi.setVal(0.)
    fit.y.setVal(1)
    fit.c1_theta.setVal(0.)
    fit.c2_theta.setVal(2.72129e-02)
    fit.c1_phi.setVal(1.22839e-01)
    fit.c2_phi.setVal(1.98006e+00)
    fit.c3_phi.setVal(-2.45259e-02)
#     fit.c1_phi.setVal(0.)
#     fit.c2_phi.setVal(0.)
#     fit.c3_phi.setVal(0.)
    fit.c4_phi.setVal(0.)
    fit.c6_phi.setVal(0.)
    fit.c5_phi.setVal(0.)


    fit.c1_psi.setConstant(1)
    fit.c2_psi.setConstant(1)
    fit.c3_psi.setConstant(1)
    fit.c4_psi.setConstant(1)
    fit.y.setConstant(1)
    fit.c1_theta.setConstant(1)
    fit.c2_theta.setConstant(1)
    fit.c1_phi.setConstant(1)
    fit.c2_phi.setConstant(1)
    fit.c3_phi.setConstant(1)
    fit.c4_phi.setConstant(1)
    fit.c6_phi.setConstant(1)
    fit.c5_phi.setConstant(1)




    dataset = RooDataSet("data","data",t,RooArgSet(fit.CPsi,fit.CTheta,fit.Phi))


        
    fitres = fit.sigmodel.fitTo(dataset,RooFit.Minos(1),RooFit.Save())

    nbins = 30

    cv3 = TCanvas()
    cv3.SetFillColor(0)
    cv3.Divide(2,2)

    cv3.cd(1)
    cpsif = fit.CPsi.frame()
    RooAbsData.plotOn(dataset,cpsif,RooFit.Binning(nbins))
    fit.sigmodel.plotOn(cpsif)
    cpsif.Draw()

    cv3.cd(2)
    cthf = fit.CTheta.frame()
    RooAbsData.plotOn(dataset,cthf,RooFit.Binning(nbins))
    fit.sigmodel.plotOn(cthf)
    cthf.Draw()

    cv3.cd(3)
    cphif = fit.Phi.frame()
    RooAbsData.plotOn(dataset,cphif,RooFit.Binning(nbins))
    fit.sigmodel.plotOn(cphif)
    cphif.Draw()

