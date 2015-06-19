from ROOT import *
from math import *
from polarization import AngularPDF as otherPDF


gROOT.ProcessLine(".x TransF1.cxx+")
gROOT.ProcessLine(".x TransF2.cxx+")
gROOT.ProcessLine(".x TransF3.cxx+")
gROOT.ProcessLine(".x TransF5.cxx+")
gROOT.ProcessLine(".x TransF7.cxx+")
gROOT.ProcessLine(".x TransF8.cxx+")
gROOT.ProcessLine(".x TransF10.cxx+")

#gSystem.Load("AngJPsiKst_cxx")


print "Class for fitting polarization: AngularPDF"


c1_psi = RooRealVar("c1_psi","c1_psi",-0.488)
c2_psi = RooRealVar("c2_psi","c2_psi",-0.642)
c3_psi = RooRealVar("c3_psi","c3_psi",-0.331)
c4_psi = RooRealVar("c4_psi","c4_psi",0.092)

y = RooRealVar("y","y",0.)
c5_psi = RooFormulaVar("c5_psi","c5_psi","y + (-1.-c1_psi-c2_psi-c3_psi-c4_psi)",RooArgList(y,c1_psi,c2_psi,c3_psi,c4_psi))

        
c1_theta = RooRealVar("c1_theta","c1_theta",0.)
c2_theta = RooRealVar("c2_theta","c2_theta",-0.1783)

c1_phi = RooRealVar("c1_phi","c1_phi",0.0784)
c2_phi = RooRealVar("c2_phi","c2_phi",1.958)
c3_phi = RooRealVar("c3_phi","c3_phi",.25)
c4_phi = RooRealVar("c4_phi","c4_phi",0.)
c5_phi = RooRealVar("c5_phi","c5_phi",0.)
c6_phi = RooRealVar("c6_phi","c6_phi",0.)


class AngularPDF:
    def __init__(self):

        self.Phi = RooRealVar("PhiP","PhiP",-1.*pi,pi)
        self.CPsi = RooRealVar("CPsi","CPsi",-1.,1.)
        self.CTheta = RooRealVar("CTheta","CTheta",-1.,1.)

        ## Parameters of interest
        
        self.A02 = RooRealVar("A02","A02",.5,0.,1.)
        self.x1 = RooRealVar("x1","x1",.5,0.,1.)
        self.Apa2 = RooFormulaVar("Apa2","Apa2","x1*(1-A02)",RooArgList(self.x1,self.A02))
        self.x2 = RooRealVar("x2","x2",.5,0.,1.)
        self.Ape2 = RooFormulaVar("Ape2","Ape2","x2*(1-A02-Apa2)",RooArgList(self.x2,self.A02,self.Apa2))
        self.As2 = RooFormulaVar("As2","As2","(1-A02-Apa2-Ape2)",RooArgList(self.A02,self.Apa2,self.Ape2))

        # self.As = RooFormulaVar("As","As","sqrt(As2)",RooArgList(self.As2))
        self.As = RooRealVar("As","As",0.)
        self.Ape = RooFormulaVar("Ape","Ape","sqrt(1-A02-Apa2)",RooArgList(self.A02,self.Apa2))
        self.A0 = RooFormulaVar("A0","A0","sqrt(A02)",RooArgList(self.A02))
        self.Apa = RooFormulaVar("Apa","Apa","sqrt(Apa2)",RooArgList(self.Apa2))
        # self.Ape = RooFormulaVar("Ape","Ape","sqrt(Ape2)",RooArgList(self.Ape2))
        
        self.dpa = RooRealVar("dpa","dpa",0.,2*pi)
        self.ds = RooRealVar("ds","ds",0.)#,2*pi)










        # Efficiency weights
        self.Sum = [61535.72950271251, 66296.60714819525, 59820.554993499594, -194.7632799232486, 56098.581926667975, 609.2725834393826, -61560.47927008221]

   
        self.X1 = RooRealVar("X1","X1",1.)
        self.X2 = RooRealVar("X2","X2",1.)
        self.X3 = RooRealVar("X3","X3",1.)
        self.X5 = RooRealVar("X5","X5",1.)
        self.X7 = RooRealVar("X7","X7",1.)
        self.X8 = RooRealVar("X8","X8",1.)
        self.X10 = RooRealVar("X10","X10",1.)


        self.apply_weights()

        # Time integrated amplitudes
        
        self.K1 = RooFormulaVar("K1","A0*A0",RooArgList(self.A0)) 
        self.K2 = RooFormulaVar("K2","Apa*Apa",RooArgList(self.Apa)) 
        self.K3 = RooFormulaVar("K3","Ape*Ape",RooArgList(self.Ape)) 
        self.K5 = RooFormulaVar("K5","A0*Apa*cos(dpa)",RooArgList(self.A0,self.Apa,self.dpa))         
        self.K7 = RooFormulaVar("K7","As*As",RooArgList(self.As))         
        self.K8 = RooFormulaVar("K8","Apa*As*cos(dpa-ds)",RooArgList(self.Apa,self.As,self.dpa,self.ds))
        self.K10 = RooFormulaVar("K10","A0*As*cos(ds)",RooArgList(self.A0,self.As,self.ds))


        # Angular amplitudes
        self.f1 = TransF1("f1","f1",self.CPsi,self.CTheta,self.Phi,self.X1)
        self.f2 = TransF2("f2","f2",self.CPsi,self.CTheta,self.Phi,self.X2)
        self.f3 = TransF3("f3","f3",self.CPsi,self.CTheta,self.Phi,self.X3)
        self.f5 = TransF5("f5","f5",self.CPsi,self.CTheta,self.Phi,self.X5)
        self.f7 = TransF7("f7","f7",self.CPsi,self.CTheta,self.Phi)#,self.X7)
        self.f8 = TransF8("f8 ","f8 ",self.CPsi,self.CTheta,self.Phi)#,self.X8)
        self.f10 = TransF10("f10","f10",self.CPsi,self.CTheta,self.Phi)#,self.X10)


        self.products = [0,0,0,0,0,0,0]

        self.products[0] = RooProduct("K1f1","K1f1",RooArgSet(self.K1,self.f1))
        self.products[1] = RooProduct("K2f2","K2f2",RooArgSet(self.K2,self.f2))
        self.products[2] = RooProduct("K3f3","K3f3",RooArgSet(self.K3,self.f3))
        self.products[3] = RooProduct("K5f5","K5f5",RooArgSet(self.K5,self.f5))
        self.products[4] = RooProduct("K7f7","K7f7",RooArgSet(self.K7,self.f7))
        self.products[5] = RooProduct("K8f8","K8f8",RooArgSet(self.K8,self.f8))
        self.products[6] = RooProduct("K10f10","K10f10",RooArgSet(self.K10,self.f10))
        

        self.dummyParamList = RooArgList() ## 24 times 1
        self.een = RooRealVar("een","een",1.)
        for i in range(7):
            self.dummyParamList.add(self.een)
      
        self.finalFuncList = RooArgList()
        for i in range(7):
            self.finalFuncList.add(self.products[i])
          
        
        
        #//*********************//
        #//***   Total PDF   ***//
        #//*********************//


        self.sigmodel = RooRealSumPdf("sigmodel", "sigmodel", self.finalFuncList,self.dummyParamList)





        # Background
        self.c1_phi_bkg = RooRealVar("c1_phi_bkg","c1_phi_bkg",-4.38046e-01)
        self.c2_phi_bkg = RooRealVar("c2_phi_bkg","c2_phi_bkg",1.24342e-01)
        self.c3_phi_bkg = RooRealVar("c3_phi_bkg","c3_phi_bkg",4.63368e-02)


        self.psibkg = RooPolynomial("psibkg","psibkg",self.CPsi,RooArgList(c1_psi,c2_psi,c3_psi,c4_psi,c5_psi))

        self.thetabkg = RooPolynomial("thetabkg","thetabkg",self.CTheta,RooArgList(c1_theta,c2_theta))

        self.phibkg = RooGenericPdf("phibkg","phibkg","1+c1_phi_bkg*PhiP + c2_phi_bkg*PhiP*PhiP + c3_phi_bkg*PhiP*PhiP*PhiP",RooArgList(self.Phi,self.c1_phi_bkg,self.c2_phi_bkg,self.c3_phi_bkg))

        self.bkgmodel = RooProdPdf("bkgmodel","bkgmodel",RooArgList(self.psibkg,self.thetabkg,self.phibkg))

        self.fsig = RooRealVar("fsig","fsig",0.,1.)
        self.model = RooAddPdf("model","model",self.sigmodel,self.bkgmodel,self.fsig)



    def getAngularFunctions(self,cpsi,ctheta,phi):

        self.CPsi.setVal(cpsi)
        self.CTheta.setVal(ctheta)
        self.Phi.setVal(phi)

        f1v = self.f1.getVal()
        f2v = self.f2.getVal()
        f3v = self.f3.getVal()
        f5v = self.f5.getVal()
        f7v = self.f7.getVal()
        f8v = self.f8.getVal()
        f10v = self.f10.getVal()

        return f1v, f2v, f3v, f5v, f7v, f8v, f10v
    



    def getweights(self,tree):

        numAngularTerms = 7
        f = [0.0]*numAngularTerms # the angular functions
        xi = [0.0]*numAngularTerms # the angular weights
        evalPDFraw, evalPDFnorm, val = 0.0, 0.0, 0.0
        numEvents = tree.GetEntries()
        self.Sum = [0.0]*numAngularTerms
        self.Sum_sq = [[0.0]*numAngularTerms]*numAngularTerms
        self.cov = [[0.0]*numAngularTerms]*numAngularTerms
        self.cor = [[0.0]*numAngularTerms]*numAngularTerms

        sigpdf = otherPDF()
        Hp = 0.159
        Hz = 0.775
        Hm = 0.612
        pHp = 1.563
        pHm = 2.712
    
        _Hp = complex(Hp *cos(pHp), Hp*sin(pHp))
        _Hm = complex(Hm *cos(pHm), Hm*sin(pHm))
        _Hz = complex(Hz, 0)
    ## Define pHz 0.0

        _a1 = 1./sqrt(2) *(_Hp + _Hm)
        _a2 = 1./sqrt(2) *(_Hp - _Hm)
        suma =  .775**2 + .159**2 +.612**2
        
        Apa2 = (_a1*_a1.conjugate()).real/suma
        Ape2 = (_a2*_a2.conjugate()).real/suma #0.1601
        A02 = 1.-Apa2-Ape2
        dpa = atan(_a1.imag/_a1.real) + pi


        sigpdf.A02.setVal(A02)
        sigpdf.A02.setConstant(kTRUE)
        sigpdf.x.setVal(Apa2/(1-A02))
        sigpdf.x.setConstant(kTRUE)
        sigpdf.cdpa.setVal(cos(dpa))
        sigpdf.cdpa.setConstant(kTRUE)

        ### set acc

        sigpdf.c1_psi.setVal(0)
        sigpdf.c1_psi.setConstant(kTRUE)
        sigpdf.c2_psi.setVal(0)
        sigpdf.c2_psi.setConstant(kTRUE)
        sigpdf.c3_psi.setVal(0)
        sigpdf.c3_psi.setConstant(kTRUE)
        sigpdf.c4_psi.setVal(0)
        sigpdf.c4_psi.setConstant(kTRUE)
        sigpdf.y.setVal(1)
        sigpdf.y.setConstant(kTRUE)
        sigpdf.c1_theta.setVal(0)
        sigpdf.c1_theta.setConstant(kTRUE)
        sigpdf.c2_theta.setVal(0)
        sigpdf.c2_theta.setConstant(kTRUE)

        sigpdf.c1_phi.setVal(0)
        sigpdf.c1_phi.setConstant(kTRUE)
        sigpdf.c2_phi.setVal(0)
        sigpdf.c2_phi.setConstant(kTRUE)
        sigpdf.c3_phi.setVal(0)
        sigpdf.c3_phi.setConstant(kTRUE)
        sigpdf.c4_phi.setVal(0)
        sigpdf.c4_phi.setConstant(kTRUE)
        sigpdf.c5_phi.setVal(0)
        sigpdf.c5_phi.setConstant(kTRUE)
        sigpdf.c6_phi.setVal(0)
        sigpdf.c6_phi.setConstant(kTRUE)


        cosPsi, cosTheta, phi = 0.0,0.0,0.0
        for e in range(numEvents):

            if (e % 1000 == 0): print "Event # ",e
            event = tree.GetEntry(e)
            cosTheta = tree.CTheta
            phi      = tree.Phi
            cosPsi   = tree.CPsi

            f[0], f[1], f[2], f[3], f[4], f[5], f[6] = self.getAngularFunctions( cosPsi, cosTheta, phi)
      
            sigpdf.CPsi.setVal(cosPsi)
            sigpdf.CTheta.setVal(cosTheta)
            sigpdf.Phi.setVal(phi)
            
            #val = self.sigmodel.getVal(RooArgSet(self.CPsi,self.CTheta,self.Phi))
            val = sigpdf.sigmodel.getVal()#RooArgSet(sigpdf.CPsi,sigpdf.CTheta,sigpdf.Phi))
      
            for j in range(numAngularTerms):
            
                self.Sum[j] = self.Sum[j] + f[j]/val/numEvents;
                xi[j] += f[j]/val;
	  
                for k in range(numAngularTerms):
	    
                    self.Sum_sq[j][k] += f[j]/val*f[k]/val;
	    
      
            # print "Covariance matrix "
            # for j in range(numAngularTerms):
            #     for k in range(numAngularTerms):
	
            #         self.cov[j][k] = 1./numEvents/numEvents * ( self.Sum_sq[j][k] - self.Sum[j]*self.Sum[k]/numEvents);
            #         print self.cov[j][k],"\t",

            # print
            


            # print "Correlation matrix "
            # for j in range(numAngularTerms):
            #     for k in range(numAngularTerms):

            #         self.cor[j][k] = self.cov[j][k]/(sqrt(abs(self.cov[j][j]))*sqrt(abs(self.cov[k][k])));

            #         print self.cov[j][k],"\t",

            # print




  
            print "Weight +- error "
            for i in range(numAngularTerms):
    
                print self.Sum[i]#xi[i]/numEvents," \\pm ", sqrt(abs(self.cov[i][i]))



        return 1.

    def apply_weights(self):

        self.X1.setVal(self.Sum[0])
        self.X2.setVal(self.Sum[1])
        self.X3.setVal(self.Sum[2])
        self.X5.setVal(self.Sum[3])
        self.X7.setVal(self.Sum[4])
        self.X8.setVal(self.Sum[5])
        self.X10.setVal(self.Sum[6])


        

    

if __name__=="__main__":


    f = TFile("/home/paula/Trabajo/BsJpsiKst/NTuples/BdJpsiKstTotMC11_v2.root")
    t2 = f.Get("T/T")

    cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 && Bmass_JC>5150 && Bmass_JC<5800 "
    cuts += "&& kaon_pt>500 && pion_pt>500 "
    cuts += "&& abs(Mjpsik-5279)>60"
    cuts += "&& abs(KstMass-896)<40"
    cuts += "&& abs(Bmass_JC-5279.5)<25"

    trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"
    
    cuts += " && "+ trigger

    f2=TFile("trash.root","recreate")
    t=t2.CopyTree(cuts+"&& GL11sb.>0.2")

    fit = AngularPDF()
    #fit.getweights(t)

#     CHANNEL = "Bd"

#     f=TFile("/home/paula/Trabajo/BsJpsiKst/NTuples/BsJPsiKst_341_v2.root")
#     t2=f.Get("T/T")


#     cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 "
# #     cuts += "&& Bmass_JC>5150 && Bmass_JC<5800"
# #     cuts += "&& abs(Bmass_JC-5279.5)<25"
    
#     cuts += "&& kaon_pt>500 && pion_pt>500"
#     if CHANNEL =="Bs":
#         cuts += "&& abs(Bmass_JC-5366.3)<25"
#         _fsig = 1-0.13
#         nbins = 9
#     else:
#         cuts += "&& abs(Bmass_JC-5279)<25"
#         _fsig = 1-2.1e-03
#         nbins = 50
        
#     cuts += "&& abs(Mjpsik-5279)>60"
#     cuts += "&& abs(KstMass-896)<40"

#     trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"

#     cuts += " && "+ trigger


#     f2=TFile("nada.root","recreate")
#     t=t2.CopyTree(cuts+"&& GL11sb.>0.2")

    

    
    # fit = AngularPDF()
    # fit.fsig.setVal(_fsig)
    # fit.fsig.setConstant(1)

    fit.Sum = [61535.72950271251, 66296.60714819525, 59820.554993499594, -194.7632799232486, 56098.581926667975, 609.2725834393826, -61560.47927008221]

    fit.apply_weights()

    dataset = RooDataSet("data","data",t,RooArgSet(fit.CPsi,fit.CTheta,fit.Phi))


        
    fitres = fit.sigmodel.fitTo(dataset,RooFit.Minos(1),RooFit.Save())


    fit.f1.useX(0)
    fit.f2.useX(0)
    fit.f3.useX(0)
    fit.f5.useX(0)
    fit.f7.useX(0)
    fit.f8.useX(0)
    fit.f10.useX(0)

    nbins = 50

    cv3 = TCanvas()
    cv3.SetFillColor(0)
    cv3.Divide(2,2)

    cv3.cd(1)
    cpsif = fit.CPsi.frame()
    RooAbsData.plotOn(dataset,cpsif,RooFit.Binning(nbins))
    fit.sigmodel.plotOn(cpsif)
    fit.model.paramOn(cpsif)
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



    # cv3 = TCanvas()
    # cv3.SetFillColor(0)
    # cv3.Divide(2,2)

    # cv3.cd(1)
    # cpsif = fit.CPsi.frame()
    # RooAbsData.plotOn(dataset,cpsif,RooFit.Binning(nbins))
    # fit.model.plotOn(cpsif)
    # fit.model.plotOn(cpsif,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    # fit.model.plotOn(cpsif,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    # fit.model.paramOn(cpsif)
    # cpsif.Draw()

    # cv3.cd(2)
    # cthf = fit.CTheta.frame()
    # RooAbsData.plotOn(dataset,cthf,RooFit.Binning(nbins))
    # fit.model.plotOn(cthf)
    # fit.model.plotOn(cthf,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    # fit.model.plotOn(cthf,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    # cthf.Draw()

    # cv3.cd(3)
    # cphif = fit.Phi.frame()
    # RooAbsData.plotOn(dataset,cphif,RooFit.Binning(nbins))
    # fit.model.plotOn(cphif)
    # fit.model.plotOn(cphif,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    # fit.model.plotOn(cphif,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    # cphif.Draw()

    # Apa2 = fit.Apa2.getVal()
    # Apa2err = fit.Apa2.getPropagatedError(fitres)
    # Ape2 = fit.Ape2.getVal()
    # Ape2err = fit.Ape2.getPropagatedError(fitres)
    # As2 = fit.As.getVal()**2
    # As2err = 2*fit.As.getVal()*fit.As.getPropagatedError(fitres)



    # print "Apa2 = %.6f"%Apa2+" + %.6f"%Apa2err
    # print "Ape2 = %.6f"%Ape2," + %.6f"%Ape2err
    # print "As2 = %.6f"%As2," + %.6f"%As2err


    # fl = RooFormulaVar("fl","fl","A02/(A02+Apa2+Ape2)",RooArgList(fit.A02,fit.Apa2,fit.Ape2))
    # flerr = fl.getPropagatedError(fitres)
    # print "f_L = %.3f"%fl.getVal()," + %.3f"%flerr

def replot(nbins):
    

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

    return cv3, cphif,cthf, cpsif


# gStyle.SetOptTitle(0)

# ctheta = TCanvas()
# cthf.GetXaxis().SetTitle("cos(#theta)")
# cthf.GetXaxis().SetTitleSize(0.06)
# cthf.GetXaxis().SetLabelSize(0.05)
# cthf.GetYaxis().SetTitleSize(0.06)
# cthf.GetYaxis().SetLabelSize(0.05)
# cthf.Draw()



# cphi = TCanvas()
# cphif.GetXaxis().SetTitle("#varphi")
# cphif.GetXaxis().SetTitleSize(0.06)
# cphif.GetXaxis().SetLabelSize(0.05)
# cphif.GetYaxis().SetTitleSize(0.06)
# cphif.GetYaxis().SetLabelSize(0.05)
# cphif.Draw()
