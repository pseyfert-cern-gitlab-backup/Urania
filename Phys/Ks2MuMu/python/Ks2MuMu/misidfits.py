from ROOT import *
gStyle.SetFillColor(0)
from ROOT import TBrowser
gSystem.Load("libRooFit")

from ROOT import TFile, RooFit, RooExtendPdf, RooRealVar, RooAddPdf, RooArgList, RooExponential
from ROOT import RooDataSet , RooArgSet, RooBinning, TPaveText, RooPolynomial
#f = TFile("ks2pipimc10.root")
#t = f.Get("T")
#from fiducial import *
class fit_bkg:

    def __init__(self,t0,cuts,mvar,eopt=0,m1=470,m2=485,m3=510,m4=550):
#ks2pipimc10.root
        f1=TFile("/tmp/jcidvida/eraseme.root","RECREATE")
        if len(cuts): t=t0.CopyTree(cuts)
        else: t=t0

        self.mass = RooRealVar(mvar, "M(K_{s}^{0})", m1,m4, "MeV/c^{2}")
        self.mass.setRange("left", m1,m2)
        self.mass.setRange("signal", m2,m3)
        self.mass.setRange("right", m3,m4)
        
        self.N_Bkg  = RooRealVar( "N_{bkg}", "Number of Bkg",  0.5*t.GetEntries() , 0, t.GetEntries())

        self.indx1 = RooRealVar("k1", "indx1", -1.e-04, -1., 1.)
        self.expbkg1 = RooExponential("expbkg1", " exp background pdf", self.mass, self.indx1)
        self.bkgmodel = self.expbkg1
        
        if eopt=="landau":
            self.mean = RooRealVar("mean", "mean", 450., -1., 600.)
            self.sigma = RooRealVar("sigma", "sigma", 0.5, -5., 5.)
            self.bkgmodel = RooLandau(eopt,eopt, self.mass, self.mean,self.sigma)

        elif eopt=="breit":
            self.mean = RooRealVar("mean", "mean", 450., -1., 600.)
            self.sigma = RooRealVar("sigma", "sigma", 0.5, -20., 20.)
            self.bkgmodel = RooBreitWigner(eopt,eopt, self.mass, self.mean,self.sigma)

        elif eopt=="npoly":
            self.mean = RooRealVar("mean", "mean", 450., -1., 600.)
            self.ind = RooRealVar("ind","ind",10.0,1.,50.) ;
            self.bkgmodel = RooGenericPdf (eopt,"1/(abs("+mvar+"-mean)^ind)",RooArgList(self.mass,self.ind, self.mean)) ;

        elif eopt=="lorentz":
            self.ind1 = RooRealVar("ind1","ind1",0.1,-5.,5.)
            self.ind2 = RooRealVar("ind2","ind2",250.0,1.,2000.)
            self.ind3 = RooRealVar("ind3","ind3",465.0,1.,1000.) 
            self.ind4 = RooRealVar("ind4","ind4",0.1,-5.,5.)

            self.bkgmodel = RooGenericPdf (eopt,"ind1+ind2/(1+(("+mvar+"-ind3)/ind4)^2)",RooArgList(self.mass,self.ind1,self.ind2,self.ind3,self.ind4)) ;
            

        elif eopt=="epoly":
            self.ind1 = RooRealVar("ind1","ind1",-10,-500.,500.) ;
            self.ind2 = RooRealVar("ind2","ind2",-10,-500.,500.) ;
            self.ind3 = RooRealVar("ind3","ind3",-10,-500.,500.) ;
            self.bkgmodel = RooGenericPdf ("epoly","exp(ind1*"+mvar+"+ind2*"+mvar+"^2+ind3*"+mvar+"^3)",RooArgList(self.mass,self.ind1,self.ind2, self.ind3)) ;

            
        self.data = RooDataSet("data","data", t, RooArgSet(self.mass))
        
        self.epdf_bkg = RooExtendPdf(  "epdf_bkg", "extended bkg pdf", self.bkgmodel , self.N_Bkg, "signal")
        self.right=False
        
        self.res =  self.epdf_bkg.fitTo(  self.data,   RooFit.Extended(True), RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(True),  RooFit.Verbose(False)  , RooFit.Range("left,right"))
        self.eopt=eopt


    def plot(self,bins=75):
        frame1 = self.mass.frame()
        frame1.SetTitle("")
        self.data.plotOn(frame1,RooFit.Binning(bins))
        self.epdf_bkg.plotOn(frame1, RooFit.Range("signal"), RooFit.NormRange("left,right"),RooFit.LineStyle(kDashed))
        self.epdf_bkg.plotOn(frame1, RooFit.Range("left,right"),RooFit.NormRange("left,right"))
        frame1.Draw()
        frame1.GetYaxis().SetRangeUser(0,30)
        return frame1

    def get_res(self): return self.N_Bkg.getVal(),self.N_Bkg.getAsymErrorLo(),self.N_Bkg.getAsymErrorHi()


    def get_params(self):
        
        def get_ind_res(ind):
            return ind.getVal(),ind.getError()
        
        if self.eopt=="landau":
            return map(get_ind_res,[self.mean,self.sigma])

        elif self.eopt=="breit":
            return map(get_ind_res,[self.mean,self.sigma])

        elif self.eopt=="npoly":
            return [get_ind_res(self.ind)]

        elif self.eopt=="lorentz":
            return map(get_ind_res,[self.ind1,self.ind2,self.ind3,self.ind4])

        elif self.eopt=="epoly":
            return map(get_ind_res,[self.ind1,self.ind2,self.ind3])

        return [get_ind_res(self.indx1)]
