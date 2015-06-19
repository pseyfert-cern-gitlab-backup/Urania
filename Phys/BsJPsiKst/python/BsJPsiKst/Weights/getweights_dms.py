from ROOT import *
from math import *
from polarization import AngularPDF as otherPDF


gROOT.ProcessLine(".L TransF1.cxx++")
gROOT.ProcessLine(".L TransF2.cxx++")
gROOT.ProcessLine(".L TransF3.cxx++")
gROOT.ProcessLine(".L TransF5.cxx++")
gROOT.ProcessLine(".L TransF7.cxx++")
gROOT.ProcessLine(".L TransF8.cxx++")
gROOT.ProcessLine(".L TransF10.cxx++")

#gSystem.Load("AngJPsiKst_cxx")


print "Class for fitting polarization: AngularPDF"





class AngularPDF:
    def __init__(self):

        self.Phi = RooRealVar("PhiP","PhiP",-1.*pi,pi)
        self.cTh1P = RooRealVar("cTh1P","cTh1P",-1.,1.)
        self.cTh2P = RooRealVar("cTh2P","cTh2P",-1.,1.)

        ## Parameters of interest
        
        self.A02 = RooRealVar("A02","A02",0.,1.)
        self.x1 = RooRealVar("x1","x1",0.,1.)
        self.Apa2 = RooFormulaVar("Apa2","Apa2","x1*(1-A02)",RooArgList(self.x1,self.A02))
        self.x2 = RooRealVar("x2","x2",0.,1.)
        self.Ape2 = RooFormulaVar("Ape2","Ape2","x2*(1-A02-Apa2)",RooArgList(self.x2,self.A02,self.Apa2))
        self.As2 = RooFormulaVar("As2","As2","(1-A02-Apa2-Ape2)",RooArgList(self.A02,self.Apa2,self.Ape2))

        self.As = RooFormulaVar("As","As","sqrt(As2)",RooArgList(self.As2))
        self.A0 = RooFormulaVar("A0","A0","sqrt(A02)",RooArgList(self.A02))
        self.Apa = RooFormulaVar("Apa","Apa","sqrt(Apa2)",RooArgList(self.Apa2))
        self.Ape = RooFormulaVar("Ape","Ape","sqrt(Ape2)",RooArgList(self.Ape2))
        
        self.dpa = RooRealVar("dpa","dpa",0.,2*pi)
        self.ds = RooRealVar("ds","ds",0.,2*pi)



        # Time integrated amplitudes
        
        self.K1 = RooFormulaVar("K1","A0*A0",RooArgList(self.A0)) 
        self.K2 = RooFormulaVar("K2","Apa*Apa",RooArgList(self.Apa)) 
        self.K3 = RooFormulaVar("K3","Ape*Ape",RooArgList(self.Ape)) 
        self.K5 = RooFormulaVar("K5","A0*Apa*cos(dpa)",RooArgList(self.A0,self.Apa,self.dpa))         
        self.K7 = RooFormulaVar("K7","As*As",RooArgList(self.As))         
        self.K8 = RooFormulaVar("K8","Apa*As*cos(dpa-ds)",RooArgList(self.Apa,self.As,self.dpa,self.ds))
        self.K10 = RooFormulaVar("K10","A0*As*cos(ds)",RooArgList(self.A0,self.As,self.ds))


        # Angular amplitudes
        self.f1 = TransF1("f1","f1",self.cTh1P,self.cTh2P,self.Phi)
        self.f2 = TransF2("f2","f2",self.cTh1P,self.cTh2P,self.Phi)
        self.f3 = TransF3("f3","f3",self.cTh1P,self.cTh2P,self.Phi)
        self.f5 = TransF5("f5","f5",self.cTh1P,self.cTh2P,self.Phi)
        self.f7 = TransF7("f7","f7",self.cTh1P,self.cTh2P,self.Phi)
        self.f8 = TransF8("f8 ","f8 ",self.cTh1P,self.cTh2P,self.Phi)
        self.f10 = TransF10("f10","f10",self.cTh1P,self.cTh2P,self.Phi)


        self.products = [0,0,0,0,0,0,0]

        self.products[0] = RooProduct("K1f1","K1f1",RooArgSet(self.K1,self.f1))
        self.products[1] = RooProduct("K2f2","K2f2",RooArgSet(self.K2,self.f2))
        self.products[2] = RooProduct("K3f3","K3f3",RooArgSet(self.K3,self.f3))
        self.products[3] = RooProduct("K5f5","K5f5",RooArgSet(self.K5,self.f5))
        self.products[4] = RooProduct("K7f7","K7f7",RooArgSet(self.K7,self.f7))
        self.products[5] = RooProduct("K8f8","K8f8",RooArgSet(self.K8,self.f8))
        self.products[6] = RooProduct("K10f10","K10f10",RooArgSet(self.K10,self.f10))
        

        dummyParamList = RooArgList() ## 24 times 1
        een = RooRealVar("een","een",1.)
        for i in range(7):
            dummyParamList.add(een)
      
        finalFuncList = RooArgList()
        for i in range(7):
            finalFuncList.add(self.products[i])
          
        
        
        #//*********************//
        #//***   Total PDF   ***//
        #//*********************//


        self.sigmodel = RooRealSumPdf("sigmodel", "sigmodel", finalFuncList,dummyParamList)

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



        # Background
        self.c1_phi_bkg = RooRealVar("c1_phi_bkg","c1_phi_bkg",-4.38046e-01)
        self.c2_phi_bkg = RooRealVar("c2_phi_bkg","c2_phi_bkg",1.24342e-01)
        self.c3_phi_bkg = RooRealVar("c3_phi_bkg","c3_phi_bkg",4.63368e-02)


        self.psibkg = RooPolynomial("psibkg","psibkg",self.cTh1P,RooArgList(c1_psi,c2_psi,c3_psi,c4_psi,c5_psi))

        self.thetabkg = RooPolynomial("thetabkg","thetabkg",self.cTh2P,RooArgList(c1_theta,c2_theta))

        self.phibkg = RooGenericPdf("phibkg","phibkg","1+c1_phi_bkg*PhiP + c2_phi_bkg*PhiP*PhiP + c3_phi_bkg*PhiP*PhiP*PhiP",RooArgList(self.Phi,self.c1_phi_bkg,self.c2_phi_bkg,self.c3_phi_bkg))

        self.bkgmodel = RooProdPdf("bkgmodel","bkgmodel",RooArgList(self.psibkg,self.thetabkg,self.phibkg))

        self.fsig = RooRealVar("fsig","fsig",1-2.1e-03)
        self.model = RooAddPdf("model","model",self.sigmodel,self.bkgmodel,self.fsig)



    def getAngularFunctions(self,cpsi,ctheta,phi):

        self.cTh1P.setVal(cpsi)
        self.cTh2P.setVal(ctheta)
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

        #boundary = dataSet.GetBoundary()
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
        sigpdf.cTh1P = sigpdf.CPsi
        sigpdf.cTh2P = sigpdf.CTheta
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

        A0 = sqrt(A02)
        Apa = sqrt(Apa2)
        Ape = sqrt(Ape2)
        
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
            phi      = tree.Phi
            cosPsi   = tree.cTh1P

            f[0], f[1], f[2], f[3], f[4], f[5], f[6] = self.getAngularFunctions( cosPsi, cosTheta, phi)
      
            self.cTh1P.setVal(cosPsi)
            self.cTh2P.setVal(cosTheta)
            self.Phi.setVal(phi)

            sigpdf.cTh1P.setVal(cosPsi)
            sigpdf.cTh2P.setVal(cosTheta)
            sigpdf.Phi.setVal(phi)
            
            #val = self.sigmodel.getVal(RooArgSet(self.cTh1P,self.cTh2P,self.Phi))
            #val = sigpdf.sigmodel.getVal(RooArgSet(sigpdf.cTh1P,sigpdf.cTh2P,sigpdf.Phi))

            val = A02*self.f1.getVal() + Apa2*self.f2.getVal() + Ape*Ape*self.f3.getVal()+ A0*Apa*cos(dpa)*self.f5.getVal()
            #print val, val2
            for j in range(numAngularTerms):
            
                self.Sum[j] += f[j]/val;
                xi[j] += f[j]/val;
	  
##                 for k in range(numAngularTerms):
	    
##                     self.Sum_sq[j][k] += f[j]/val*f[k]/val;
	    
      
##             print "Covariance matrix "
##             for j in range(numAngularTerms):
##                 for k in range(numAngularTerms):
	
##                     self.cov[j][k] = 1./numEvents/numEvents * ( self.Sum_sq[j][k] - self.Sum[j]*self.Sum[k]/numEvents);
##                     print self.cov[j][k],"\t",

##             print
            


##             print "Correlation matrix "
##             for j in range(numAngularTerms):
##                 for k in range(numAngularTerms):

##                     self.cor[j][k] = self.cov[j][k]/(sqrt(abs(self.cov[j][j]))*sqrt(abs(self.cov[k][k])));

##                     print self.cov[j][k],"\t",

##             print




  
        print "Weight +- error "
        for i in range(numAngularTerms):
            
            print self.Sum[i]/numEvents," \\pm ", sqrt(abs(self.cov[i][i])) 
    

if __name__=="__main__":

    
    
    fit = AngularPDF()

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


    fit.A02.setVal(A02)
    fit.A02.setConstant(kTRUE)
    fit.x1.setVal(Apa2/(1-A02))
    fit.x1.setConstant(kTRUE)
    fit.x2.setVal(1.)
    fit.x2.setConstant(kTRUE)
    fit.dpa.setVal(dpa)
    fit.dpa.setConstant(kTRUE)
    fit.ds.setVal(0)
    fit.ds.setConstant(kTRUE)



    ## f = TFile("/home/paula/Trabajo/BsJpsiKst/NTuples/BdJpsiKstTotMC11_v2.root")
##     t2 = f.Get("T/T")

##     cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 && Bmass_JC>5150 && Bmass_JC<5800 "
##     cuts += "&& kaon_pt>500 && pion_pt>500 "
##     cuts += "&& abs(Mjpsik-5279)>60"
##     cuts += "&& abs(KstMass-896)<40"
##     cuts += "&& abs(Bmass_JC-5279.5)<25"

##     trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"
    
##     cuts += " && "+ trigger

    f2=TFile("~/vol5/BdJpsiKst_mcgen.root")
    t = f2.Get("Bd2JPsiKstar/Bd2JPsiKstar")

    dataset = RooDataSet("dataset","dataset",t,RooArgSet(fit.cTh1P,fit.cTh2P,fit.Phi))

    fit.getweights(t)


## 10.084609399  \pm  0.0
## 14.8597134679  \pm  0.0
## 13.7044758708  \pm  0.0
## 2.09808801413  \pm  0.0
## 10.3556894534  \pm  0.0
## -0.00874903851555  \pm  0.0
## 0.00494651877778  \pm  0.0
