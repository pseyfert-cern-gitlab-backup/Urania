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

f = TFile("/home/paula/Trabajo/BsJpsiKst/NTuples/BdJpsiKst_mcgen.root")
t2 = f.Get("Bd2JPsiKstar/Bd2JPsiKstar")
f2=TFile("results/plots_Bd_MC11.root","recreate")
cuts=""
t=t2.CopyTree(cuts)

# f = TFile("/home/paula/Trabajo/BsJpsiKst/NTuples/BdJpsiKstTotMC11_v2.root")
# t2 = f.Get("T/T")

# cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 && Bmass_JC>5150 && Bmass_JC<5800 "
# cuts += "&& kaon_pt>500 && pion_pt>500 "
# cuts += "&& abs(Mjpsik-5279)>60"
# cuts += "&& abs(KstMass-896)<40"
# cuts += "&& abs(Bmass_JC-5279.5)<25"
# trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"
# cuts += " && "+ trigger

# f2=TFile("trash.root","recreate")
# t=t2.CopyTree(cuts+"&& GL11sb.>0.2")


print "Class for fitting polarization with weights for acceptance: AngularPDF"

class AngularPDF:
    def __init__(self):
        self.Phi = RooRealVar("PhiP","PhiP",-1.*pi,pi)
        self.CPsi = RooRealVar("cTh1P","cTh1P",-1.,1.)
        self.CTheta = RooRealVar("cTh2P","cTh2P",-1.,1.)
        # self.Phi = RooRealVar("PhiP","PhiP",-1.*pi,pi)
        # self.CPsi = RooRealVar("CPsi","CPsi",-1.,1.)
        # self.CTheta = RooRealVar("CTheta","CTheta",-1.,1.)

        ## Parameters of interest
        
        self.A02 = RooRealVar("A02","A02",.5,0.,1.)
        self.x1 = RooRealVar("x1","x1",.5,0.,1.)
        self.Apa2 = RooFormulaVar("Apa2","Apa2","x1*(1-A02)",RooArgList(self.x1,self.A02))
        self.Ape = RooFormulaVar("Ape","Ape","sqrt(1-A02-Apa2)",RooArgList(self.A02,self.Apa2))
        self.A0 = RooFormulaVar("A0","A0","sqrt(A02)",RooArgList(self.A02))
        self.Apa = RooFormulaVar("Apa","Apa","sqrt(Apa2)",RooArgList(self.Apa2))
        self.dpa = RooRealVar("dpa","dpa",0.,2*pi)


        # Efficiency weights

        
        self.X1 = RooRealVar("X1","X1",1.)
        self.X2 = RooRealVar("X2","X2",1.)
        self.X3 = RooRealVar("X3","X3",1.)
        self.X5 = RooRealVar("X5","X5",1.)


        #self.getweights(t)
        #self.Sum = [4.03751259777656, 4.349885647148805, 3.924975722951209, -0.012778904266337387] ## MC standard
        self.Sum = [0.9962310939061332, 1.0053133091896123, 1.0047457473387071, -0.0007565319464336661] ## MC sin cortes
        #self.Sum = [32.*pi/9,32.*pi/9,32.*pi/9,0.] ## Integrales fi
        self.apply_weights()

        # Time integrated amplitudes
        
        self.K1 = RooFormulaVar("K1","A0*A0",RooArgList(self.A0)) 
        self.K2 = RooFormulaVar("K2","Apa*Apa",RooArgList(self.Apa)) 
        self.K3 = RooFormulaVar("K3","Ape*Ape",RooArgList(self.Ape)) 
        self.K5 = RooFormulaVar("K5","A0*Apa*cos(dpa)",RooArgList(self.A0,self.Apa,self.dpa))         


        # Angular amplitudes
        self.f1 = TransF1("f1","f1",self.CPsi,self.CTheta,self.Phi,self.X1)
        self.f2 = TransF2("f2","f2",self.CPsi,self.CTheta,self.Phi,self.X2)
        self.f3 = TransF3("f3","f3",self.CPsi,self.CTheta,self.Phi,self.X3)
        self.f5 = TransF5("f5","f5",self.CPsi,self.CTheta,self.Phi,self.X5)


        self.products = [0]*4

        self.products[0] = RooProduct("K1f1","K1f1",RooArgSet(self.K1,self.f1))
        self.products[1] = RooProduct("K2f2","K2f2",RooArgSet(self.K2,self.f2))
        self.products[2] = RooProduct("K3f3","K3f3",RooArgSet(self.K3,self.f3))
        self.products[3] = RooProduct("K5f5","K5f5",RooArgSet(self.K5,self.f5))
        

        self.dummyParamList = RooArgList() ## 24 times 1
        self.een = RooRealVar("een","een",1.)
        for i in range(4):
            self.dummyParamList.add(self.een)
      
        self.finalFuncList = RooArgList()
        for i in range(4):
            self.finalFuncList.add(self.products[i])
          
        
        
        #//*********************//
        #//***   Total PDF   ***//
        #//*********************//


        self.sigmodel = RooRealSumPdf("sigmodel", "sigmodel", self.finalFuncList,self.dummyParamList)


    def getAngularFunctions(self,cpsi,ctheta,phi):


        f1_ = TransF1("f1_","f1_",self.CPsi,self.CTheta,self.Phi)
        f2_ = TransF2("f2_","f2_",self.CPsi,self.CTheta,self.Phi)
        f3_ = TransF3("f3_","f3_",self.CPsi,self.CTheta,self.Phi)
        f5_ = TransF5("f5_","f5_",self.CPsi,self.CTheta,self.Phi)

        self.CPsi.setVal(cpsi)
        self.CTheta.setVal(ctheta)
        self.Phi.setVal(phi)

        f1v = f1_.getVal()
        f2v = f2_.getVal()
        f3v = f3_.getVal()
        f5v = f5_.getVal()

        return f1v, f2v, f3v, f5v
    



    def getweights(self,tree):

        numAngularTerms = 4
        f = [0.0]*numAngularTerms # the angular functions
        xi = [0.0]*numAngularTerms # the angular weights
        evalPDFraw, evalPDFnorm, val = 0.0, 0.0, 0.0
        numEvents = tree.GetEntries()
        self.Sum = [0.0]*numAngularTerms
        self.Sum_sq = [[0.0]*numAngularTerms]*numAngularTerms
        self.cov = [[0.0]*numAngularTerms]*numAngularTerms
        # self.cor = [[0.0]*numAngularTerms]*numAngularTerms

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
            cosTheta = tree.cTh2P
            phi      = tree.PhiP
            cosPsi   = tree.cTh1P
            # cosTheta = tree.CTheta
            # phi      = tree.Phi
            # cosPsi   = tree.CPsi

            f[0], f[1], f[2], f[3] = self.getAngularFunctions( cosPsi, cosTheta, phi)
      
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
    
                print self.Sum[i]/numEvents#," \\pm ", sqrt(abs(self.cov[i][i]))



        return 1.

    def apply_weights(self):

        self.X1.setVal(self.Sum[0])
        self.X2.setVal(self.Sum[1])
        self.X3.setVal(self.Sum[2])
        self.X5.setVal(self.Sum[3])


        

    

if __name__=="__main__":

    fit = AngularPDF()

    dataset = RooDataSet("data","data",t,RooArgSet(fit.CPsi,fit.CTheta,fit.Phi))

    fitres = fit.sigmodel.fitTo(dataset,RooFit.Minos(1),RooFit.Save())
    nbins = 50

    print "A02", fit.A02.getVal(), "+/-", fit.A02.getError()
    print "Apa2", fit.Apa2.getVal(), "+/-", fit.Apa.getPropagatedError(fitres)
    print "dpa", fit.dpa.getVal(), "+/-", fit.dpa.getError()

    fit.f1.useX(0)
    fit.f2.useX(0)
    fit.f3.useX(0)
    fit.f5.useX(0)
    
    cv3 = TCanvas()
    cv3.SetFillColor(0)
    cv3.Divide(2,2)

    cv3.cd(1)
    cpsif = fit.CPsi.frame()
    RooAbsData.plotOn(dataset,cpsif,RooFit.Binning(nbins))
    fit.sigmodel.plotOn(cpsif)
    fit.sigmodel.paramOn(cpsif)
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

