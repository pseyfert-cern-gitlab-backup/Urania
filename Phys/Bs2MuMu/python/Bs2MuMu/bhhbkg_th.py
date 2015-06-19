from ROOT import *
gSystem.Load("libRooFit")
from BsMuMuPy.pyMyRoot.smartpyROOT import *

gl = RooRealVar("GLTsb.","GLTsb.",0.,1.)


cmb_bkg_idx = -9.28618e-004  # error 1.06270e-004
"""
 EXT PARAMETER
 NO.   NAME      VALUE            ERROR
  1  Constant    2.14361e+001  8.27643e+000
  2  Mean        4.72937e+003  2.16356e+002
  3  Sigma       2.94080e+002  8.58990e+001
"""

class GL_phys:

    def __init__(self,tree):
        self.gl = RooRealVar("GLsb.","GLsb.",0,1)
        self.c1 = RooRealVar("c1","c1",-0.5,0.,10.)
        self.bkg_1 = RooPolynomial("bkg_1","bkg_1", self.gl,RooArgList(self.c1))
        self.data = RooDataSet("data","data", tree, RooArgSet(self.mass))
        self.model = self.bkg_1
        self.model.fitTo(self.data)

    def plot(self):
        """Plots the data and the models
        """
        fr = self.gl.frame()
        self.data.plotOn(fr, RooLinkedList())
        self.model.plotOn(fr)
        #self.model.plotOn(fr,RooFit.Components("bkg"), RooFit.LineStyle(kDashed))
        #self.model.plotOn(fr,RooFit.Components("sig"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        fr.Draw()
        return(fr)

class BkgMassGen:
   
    def __init__(self, shf = 0.1):
       
        self.mass = RooRealVar("Bmass","Bmass", 4779, 5779)
       
        ###bkg pdf
        self.indx = RooRealVar("indx", "indx", cmb_bkg_idx)
        self.linbkg = RooExponential("expBkg", "Exponential background pdf", self.mass, self.indx)

        ###Shoulder
        self.sh_mean = RooRealVar("sh_mean", "sh_mean", 4729.)
        self.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 294.)
       
        self.sh_sigma.setConstant(kTRUE)
        #self.sh_mean.setConstant(kTRUE)
       
        #self.shoulder = RooExpAndGauss("shoulder", "shoulder pdf", self.mass,self.sh_mean, self.sh_sigma, self.sh_trans)
        self.shoulder = RooGaussian("shoulder","shoulder pdf", self.mass, self.sh_mean, self.sh_sigma)
        #### model
        
        self.fsh = RooRealVar("fh", "shoulder fraction in background", shf)
        self.bkg = RooAddPdf("bkg", "background pdf", self.shoulder, self.linbkg, self.fsh)
        
        self.model = self.bkg
        #self.model  = RooAddPdf("model","model", self.sig, self.bkg, self.fsig)
       
        
    
    def toy(self,Number, fluc = 0):
        """Generates a toy acording to the current model
        """
        if fluc: print "Not Implemented"       
        if not isinstance(Number, int):
            print "Warning: Expected 'int', taking int(Number)"
            Number = int(Number)
        return self.model.generate(RooArgSet(self.mass),  Number, kFALSE)
    def reboot(self):
        """Fits again to the initializing data
        """
        self.model.fitTo(self.data)
    def fitToy(self,Number):
        """Number = number of events to be 'simulated'
            Generates a toyMC, and fits to it
        """
        data2 = self.toy(Number)
        if Number < 10000:
            self.model.fitTo(data2)
            return
        print "Too Large Data, fitting to corresponding default histogram"
        h = RooDataHist("Bmass","Bmass",RooArgSet(self.mass), data2)
        self.model.fitTo(h)
    def signalFraction(self):
        """retuns the signal component of the current model
        """
        return self.fsig.getVal(), self.fsig.getAsymErrorHi(), self.fsig.getAsymErrorLo()
    def signalInToy(self, Number):
        """does .fitToy(Number)
        and returns the number of signal events with its errors
        """
        self.fitToy(Number)
        m , h, l = self.signalFraction()
        self.reboot()
        return m*Number, h*Number, l*Number
    def FitToH(self,H):
        h = RooDataHist("Bmass","Bmass",RooArgList(self.mass), H)
        self.model.fitTo(h)

    def generateTuple(self,N, name):
        from RTuple import RTuple
        tup = RTuple(name,["evt/F","Bmass/F"])
        EVT = 1
        while 1:
            if EVT >= N: break 
            data = self.toy(min(10000, N-EVT))
            t = data.tree()
            for i in range(t.GetEntries()):
                t.GetEntry(i)
                tup.fillItem("evt",EVT)
               
                tup.fillItem("Bmass",t.Bmass)
                
                tup.fill()
                EVT += 1
            print "processed ",EVT-1, " events"
        tup.close() 
    #def UseShoulder(self):
     #   self.shoulder = True


def sbSample(N, Ns, f_phys, sig = "tuplas\\bhh_tesis\\tis_015_0025", name = "toy"):
    from scipy import random as rnd
    from smartpyROOT import getTuple
    from RTuple import RTuple
    
    N = int(rnd.normal(N,sqrt(N)))
    print N
    th,fh = getTuple(sig)
    op = BkgMassGen(f_phys)
    tup = RTuple("tuplas\\bhh_tesis\\\\" + name,["evt/F","Bmass/F"])#,"GLsb./F"])
    EVT = 1
    while 1:
        if EVT >= N: break 
        data = op.toy(min(10000, N-EVT))
        t = data.tree()
        for i in range(t.GetEntries()):
            t.GetEntry(i)
            tup.fillItem("evt",EVT)
         #   tup.fillItem("GLsb.",getattr(t,"GLsb."))
            tup.fillItem("Bmass",t.Bmass)
            tup.fill()
            EVT += 1
        print "processed ",EVT-1, " events"
  
                     
    for i in range(Ns):
        th.GetEntry(i)
        if th.Bmass<4779: continue
        if th.Bmass>5779: continue
        tup.fillItem("evt",EVT+th.evt)
        #tup.fillItem("GLsb.",getattr(th,"GLsb."))
        tup.fillItem("Bmass",th.Bmass)
        tup.fill()
    tup.close()
    fh.Close()
class sbFiter_HW:
    def __init__(self,tree, var,cuts="", shorTime = True, shoulder = True, weight_var=0):
       
        f = TFile("borrame_ho.root","recreate")
        t = tree.CopyTree(cuts)
        m0 = t.GetMinimum(var)
        m1 = t.GetMaximum(var)
        self.mass = RooRealVar(var,var,  m0 , m1)
        
        self.createvars(shoulder)
        ### fit
        
        self.data = RooDataSet("data","data", t, RooArgSet(self.mass))
        #self.data = RooDataSet("data","data", t, RooArgSet(self.mass))    
        N = t.GetEntries()
        
        
        print "Fitting HISTOGRAM"

        h = TH1F("A","A", 100,m0, m1)
        haux = TH1F("B","B", 100,m0, m1)
        for entry in t:
            h.Fill(getattr(t,var),getattr(t,weight_var))
            haux.Fill(getattr(t,var))
        for i in range(h.GetNbinsX()):
            if not haux.GetBinContent(i+1): continue
            h.SetBinError(i+1,haux.GetBinError(i+1)*h.GetBinContent(i+1)/haux.GetBinContent(i+1))
        self.h = h
        self.FitRooH(h)        
        f.Close()    
        
    def createvars(self,shoulder):
        ## sig pdf
        self.mean1 = RooRealVar("mean1","mean1",5050, 5300)#5168.)
        self.d1= RooRealVar("d1","d1", 92.1)#, 80., 120.)
        self.mean2 = RooFormulaVar("mean2","mean2", "mean1 + d1" ,RooArgList(self.mean1,self.d1) )
        self.sigma = RooRealVar("sigma","sigma", 36.5)#, 32.,38)#35.)

        self.n = RooRealVar("exponent", "exponent",1.)#, 0., 8.01 )
        self.n2 = RooRealVar("exponent2", "exponent2", 5.1 )
        
        self.a2 = RooRealVar("transition2","transition2", -1.21) ## Transition point, in sigmas
        self.a3 = RooRealVar("transition3","transition3",1.51) ## Transition point, in sigmas

        self.MSu1 = RooCBShape("MSu","MSu", self.mass, self.mean1, self.sigma, self.a2, self.n2)
        self.MSd1 = RooCBShape("MSd","MSd", self.mass, self.mean1, self.sigma, self.a3, self.n)
        self.MSu2 = RooCBShape("MSu2","MSu2", self.mass, self.mean2, self.sigma, self.a2, self.n2)
        self.MSd2 = RooCBShape("MSd2","MSd2", self.mass, self.mean2, self.sigma, self.a3, self.n)
        
        self.f05 = RooRealVar("0.55", "0.5", 0.5) ### This is here just to create double crystalballs (I think)
        self.MS1 = RooAddPdf("MS1","MS1",self.MSu1,self.MSd1,self.f05)
        self.MS2 = RooAddPdf("MS2","MS2",self.MSu2,self.MSd2,self.f05)
        self.f1 = RooRealVar("fraction","fraction",0.081)#0.08, 0., 1.)
        ###bkg pdf
        self.indx = RooRealVar("indx", "indx", -0.001, -0.01, 0.)
        self.linbkg = RooExponential("expBkg", "Exponential background pdf", self.mass, self.indx)
        
        # Lambda
        self.meanL = RooRealVar("lambdaPeak","lambdaPeak", 5500.,5400.,5600.)
        self.sigmaL = RooRealVar("sigmaL","sigmaL", 30., 20., 70.)
        self.lambda_b = RooGaussian("lambda","lambda",self.mass,self.meanL,self.sigmaL)
        self.fLambda= RooRealVar("fLambda","fLambda", 0.5,0.,1.)

        ###Shoulder
        self.sh_mean = RooRealVar("sh_mean", "sh_mean", 4500., 4200.,5000.)
        self.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 200., 100.,400.)
       
        #self.sh_trans.setConstant(kTRUE)
        self.sh_sigma.setConstant(kTRUE)
        #self.sh_mean.setConstant(kTRUE)
       
        #self.shoulder = RooExpAndGauss("shoulder", "shoulder pdf", self.mass,self.sh_mean, self.sh_sigma, self.sh_trans)
        self.shoulder = RooGaussian("shoulder","shoulder pdf", self.mass, self.sh_mean, self.sh_sigma)
        #### model
        if not shoulder:
            self.fsh = RooRealVar("fh", "shoulder fraction in background", 0.)#,0.,1.)
            self.fsh.setConstant(kTRUE)
            self.sh_sigma.setConstant(kTRUE)
            self.sh_mean.setConstant(kTRUE)
        else: 
            self.fsh = RooRealVar("fh", "shoulder fraction in background", 0.5,0.,1.)
        self.bkg1 = RooAddPdf("bkg1", "background pdf1", self.shoulder, self.linbkg, self.fsh)
        self.bkg = RooAddPdf("bkg", "background pdf", self.lambda_b, self.bkg1, self.fLambda)
        #self.bkg = RooAddPdf("bkg", "background pdf", self.shoulder, self.linbkg, self.fsh)

        self.sf = RooRealVar("Sigfraction", "Sigfraction", 0.5,0.,1.) 
        self.sig  = RooAddPdf("Sigmodel","Sigmodel", self.MS1, self.MS2, self.f1)        
        self.model = RooAddPdf("model","model", self.sig, self.bkg, self.sf)
        
    def plot(self):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        self.data.plotOn(fr, RooLinkedList())
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("MS2"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("MS1"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("linbkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("lambda"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
        fr.Draw()
        return(fr)
    def toy(self,Number):
        """Generates a toy acording to the current model
        """
        if not isinstance(Number, int):
            print "Warning: Expected 'int', taking int(Number)"
            Number = int(Number)
        return self.model.generate(RooArgSet(self.mass),  Number, kFALSE)
    def reboot(self):
        """Fits again to the initializing data
        """
        self.createvars()
        self.model.fitTo(self.data)
    def fitToy(self,Number):
        """Number = number of events to be 'simulated'
            Generates a toyMC, and fits to it
        """
        data2 = self.toy(Number)
        if Number < 10000:
            self.model.fitTo(data2)
            return
        print "Too Large Data, fitting to corresponding default histogram"
        h = RooDataHist("Bmass","Bmass",RooArgSet(self.mass), data2)
        self.model.fitTo(h)
    def FitRooH(self,h):
        hr = RooDataHist("Bmass","Bmass",RooArgList(self.mass),h)
        self.createvars(1)
        self.model.fitTo(hr)
        fr = self.mass.frame()
        hr.plotOn(fr,RooTreeData.PlotOpt())
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("MS2"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("MS1"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("linbkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlack))

        fr.Draw()
        return(fr)  
def makefiles(tis, phys, comb, sel):
    from triggerclass import Cut, trigger
    t = sel(tis)
    p = sel(phys)
    c = sel(comb)
    gl = Cut("GLTsb.<0.25")
    t1 = gl(t)
    p1 = gl(p)
    c1 = gl(c)
    t1.save("tuplas\\bhh_tesis\\tis_0025_selxx")
    nphys = len(p1) * 0.02 *.15/6.49e-05
    ncomb = len(c1) * 0.067*.15/6.49e-05
    nmb = 0.4*ncomb
    Nb = nmb+nphys+ncomb
    f = nphys*1./Nb
    Ns = len(t1) * 1150*1.5/len(tis)
    print Ns, f
    sbSample(Nb,Ns,f, "tuplas\\bhh_tesis\\tis_0025_selxx","toy_025")
    gl = trigger()
    gl.addCut("GLTsb.>0.25")
    gl.addCut("GLTsb.<0.5")
    t1 = gl(t)
    p1 = gl(p)
    c1 = gl(c)
    t1.save("tuplas\\bhh_tesis\\tis_02505_selxx")
    nphys = len(p1) * 0.02 *.15/6.49e-05
    ncomb = len(c1) * 0.067*.15/6.49e-05
    nmb = 0.4*ncomb
    Nb = nmb+nphys+ncomb
    f = nphys*1./Nb
    Ns = len(t1) * 1150*1.5/len(tis)
    print Ns, f
    sbSample(Nb,Ns,f, "tuplas\\bhh_tesis\\tis_02505_selxx","toy_05")
    gl = trigger()
    gl.addCut("GLTsb.>0.5")
    gl.addCut("GLTsb.<0.75")
    t1 = gl(t)
    p1 = gl(p)
    c1 = gl(c)
    t1.save("tuplas\\bhh_tesis\\tis_05075_selxx")
    nphys = len(p1) * 0.02 *.15/6.49e-05
    ncomb = len(c1) * 0.067*.15/6.49e-05
    nmb = 0.4*ncomb
    Nb = nmb+nphys+ncomb
    f = nphys*1./Nb
    Ns = len(t1) * 1150*1.5/len(tis)
    print Ns,f
    sbSample(Nb,Ns,f, "tuplas\\bhh_tesis\\tis_05075_selxx","toy_075")
    gl = trigger()
    gl.addCut("GLTsb.>0.75")
    #gl.addCut("GLTsb.<0.5")
    t1 = gl(t)
    p1 = gl(p)
    c1 = gl(c)
    t1.save("tuplas\\bhh_tesis\\tis_0751_selxx")
    nphys = len(p1) * 0.02 *.15/6.49e-05
    ncomb = len(c1) * 0.067*.15/6.49e-05
    nmb = 0.4*ncomb
    Nb = nmb+nphys+ncomb
    f = nphys*1./Nb
    Ns = len(t1) * 1150*1.5/len(tis)
    print Ns, f
    sbSample(Nb,Ns,f, "tuplas\\bhh_tesis\\tis_0751_selxx","toy_1")

class sbFiter:
    def __init__(self,tree, var,cuts="", shorTime = True, shoulder = True, weight_var=0):
        """ROOT TTree,, option 'ShorTime' does the fit to be
done in histogram instead of NTuple
        """
        f = TFile("borrame_ho.root","recreate")
        t = tree.CopyTree(cuts)
        self.mass = RooRealVar(var,var,  t.GetMinimum(var), t.GetMaximum(var))
        
        self.createvars(shoulder)
        ### fit
        if weight_var:
            self.w = RooRealVar(weight_var, weight_var,  t.GetMinimum(weight_var), t.GetMaximum(weight_var))
            self.data = RooDataSet("data","data", t, RooArgSet(self.mass, self.w))
            self.data.setWeightVar(self.w)

        else: self.data = RooDataSet("data","data", t, RooArgSet(self.mass))
        #self.data = RooDataSet("data","data", t, RooArgSet(self.mass))    
        N = t.GetEntries()
        f.Close()
        if N < 10000 or (not shorTime):
            print "Fitting to NTuple"
            self.model.fitTo(self.data)
        else:
            print "Fitting HISTOGRAM"
            h = RooDataHist(var,var,RooArgSet(self.mass), self.data)
            print h
            self.model.fitTo(h)
        
    def createvars(self,shoulder):
        ## sig pdf
        self.mean1 = RooRealVar("mean1","mean1",5050, 5300)#5168.)
        self.d1= RooRealVar("d1","d1", 92.1)#, 80., 120.)
        self.mean2 = RooFormulaVar("mean2","mean2", "mean1 + d1" ,RooArgList(self.mean1,self.d1) )
        self.sigma = RooRealVar("sigma","sigma", 36.5)#, 32.,38)#35.)

        self.n = RooRealVar("exponent", "exponent",1.)#, 0., 8.01 )
        self.n2 = RooRealVar("exponent2", "exponent2", 5.1 )
        
        self.a2 = RooRealVar("transition2","transition2", -1.21) ## Transition point, in sigmas
        self.a3 = RooRealVar("transition3","transition3",1.51) ## Transition point, in sigmas

        self.MSu1 = RooCBShape("MSu","MSu", self.mass, self.mean1, self.sigma, self.a2, self.n2)
        self.MSd1 = RooCBShape("MSd","MSd", self.mass, self.mean1, self.sigma, self.a3, self.n)
        self.MSu2 = RooCBShape("MSu2","MSu2", self.mass, self.mean2, self.sigma, self.a2, self.n2)
        self.MSd2 = RooCBShape("MSd2","MSd2", self.mass, self.mean2, self.sigma, self.a3, self.n)
        
        self.f05 = RooRealVar("0.55", "0.5", 0.5) ### This is here just to create double crystalballs (I think)
        self.MS1 = RooAddPdf("MS1","MS1",self.MSu1,self.MSd1,self.f05)
        self.MS2 = RooAddPdf("MS2","MS2",self.MSu2,self.MSd2,self.f05)
        self.f1 = RooRealVar("fraction","fraction",0.081)#0.08, 0., 1.)
        ###bkg pdf
        self.indx = RooRealVar("indx", "indx", -0.001, -0.01, 0.)
        self.linbkg = RooExponential("expBkg", "Exponential background pdf", self.mass, self.indx)
        
        # Lambda
        #self.meanL = RooRealVar("lambdaPeak","lambdaPeak", 5500.,5400.,5600.)
        #self.sigmaL = RooRealVar("sigmaL","sigmaL", 30., 20., 70.)
        #self.lambda_b = RooGaussian("lambda","lambda",self.mass,self.meanL,self.sigmaL)
        #self.fLambda= RooRealVar("fLambda","fLambda", 0.5,0.,1.)

        ###Shoulder
        self.sh_mean = RooRealVar("sh_mean", "sh_mean", 4729.)#., 4200.,5000.)
        self.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 294)#., 100.,400.)
       
        #self.sh_trans.setConstant(kTRUE)
        self.sh_sigma.setConstant(kTRUE)
        #self.sh_mean.setConstant(kTRUE)
       
        #self.shoulder = RooExpAndGauss("shoulder", "shoulder pdf", self.mass,self.sh_mean, self.sh_sigma, self.sh_trans)
        self.shoulder = RooGaussian("shoulder","shoulder pdf", self.mass, self.sh_mean, self.sh_sigma)
        #### model
        if not shoulder:
            self.fsh = RooRealVar("fh", "shoulder fraction in background", 0.)#,0.,1.)
            self.fsh.setConstant(kTRUE)
            self.sh_sigma.setConstant(kTRUE)
            self.sh_mean.setConstant(kTRUE)
        else: 
            self.fsh = RooRealVar("fh", "shoulder fraction in background", 0.5,0.,1.)
        self.bkg1 = RooAddPdf("bkg1", "background pdf1", self.shoulder, self.linbkg, self.fsh)
        self.bkg = self.bkg1 ## RooAddPdf("bkg", "background pdf", self.lambda_b, self.bkg1, self.fLambda)
        #self.bkg = RooAddPdf("bkg", "background pdf", self.shoulder, self.linbkg, self.fsh)

        self.sf = RooRealVar("Sigfraction", "Sigfraction", 0.5,0.,1.) 
        self.sig  = RooAddPdf("Sigmodel","Sigmodel", self.MS1, self.MS2, self.f1)        
        self.model = RooAddPdf("model","model", self.sig, self.bkg, self.sf)
        
    def plot(self, bins = 100):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        self.data.plotOn(fr, RooFit.Binning(bins))
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("MS2"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("MS1"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("linbkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("lambda"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
        fr.Draw()
        return(fr)
    def toy(self,Number):
        """Generates a toy acording to the current model
        """
        if not isinstance(Number, int):
            print "Warning: Expected 'int', taking int(Number)"
            Number = int(Number)
        return self.model.generate(RooArgSet(self.mass),  Number, kFALSE)
    def reboot(self):
        """Fits again to the initializing data
        """
        self.createvars()
        self.model.fitTo(self.data)
    def fitToy(self,Number):
        """Number = number of events to be 'simulated'
            Generates a toyMC, and fits to it
        """
        data2 = self.toy(Number)
        if Number < 10000:
            self.model.fitTo(data2)
            return
        print "Too Large Data, fitting to corresponding default histogram"
        h = RooDataHist("Bmass","Bmass",RooArgSet(self.mass), data2)
        self.model.fitTo(h)
    def FitRooH(self,h):
        hr = RooDataHist("Bmass","Bmass",RooArgList(self.mass),h)
        self.createvars()
        self.model.fitTo(hr)
        fr = self.mass.frame()
        hr.plotOn(fr,RooTreeData.PlotOpt())
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("MS2"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("MS1"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("linbkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlack))

        fr.Draw()
        return(fr)
    
    
class sbFiter_ex:
    def __init__(self,tree, var,cuts="", shorTime = True, shoulder = True,fixTo = [0,0,0,0,0], bothBs = 0, weight_var = 0):
        """ROOT TTree,, option 'ShorTime' does the fit to be
done in histogram instead of NTuple
        """
        f = TFile("borrame_ho.root","recreate")
        t = tree.CopyTree(cuts)
        self.mass = RooRealVar(var,var,  t.GetMinimum(var), t.GetMaximum(var))
        self.createvars(shoulder, fixTo, bothBs)
        ### fit
        
        if weight_var:
            self.w = RooRealVar(weight_var, weight_var,  t.GetMinimum(weight_var), t.GetMaximum(weight_var))
            self.data = RooDataSet("data","data", t, RooArgSet(self.mass, self.w))
            self.data.setWeightVar(self.w)

        else: self.data = RooDataSet("data","data", t, RooArgSet(self.mass))
        
        N = t.GetEntries()
        f.Close()
        if N < 10000 or (not shorTime):
            print "Fitting to NTuple"
            self.model.fitTo(self.data)
        else:
            print "Fitting HISTOGRAM"
            h = RooDataHist(var,var,RooArgSet(self.mass), self.data)
            print h
            self.model.fitTo(h)
        
    def createvars(self,shoulder, fixTo, bothBs):
        ## sig pdf
        self.mean = RooRealVar("mean","mean", 5300.,5200.,5400.)
        
        self.sigma1 = RooRealVar("sigma1","sigma1", 18., 10., 40.)
        self.sigma2 = RooRealVar("sigma2","sigma2", 30., 20., 70.)
        
        self.a = RooRealVar("transition","transition", 1., 0.1, 3.) ## Transition point, in sigmas
        self.n = RooRealVar("exponent", "exponent",1.)#, 0.99, 1.01 )
        self.f= RooRealVar("fCB","fCB", 0.75,0.5,1.)
        
       
        if fixTo[0]: self.mean = RooRealVar("mean","mean", fixTo[0])
        if fixTo[1]: self.sigma1 = RooRealVar("sigma1","sigma1", fixTo[1])
        if fixTo[2]: self.a = RooRealVar("transition","transition", fixTo[2]) ## Transition point, in sigmas
        if fixTo[3]: self.f = RooRealVar("fCB","fCB", fixTo[3]) ## Transition point, in sigmas
        if fixTo[4]: self.sigma2 = RooRealVar("sigma2","sigma2", fixTo[4])
        self.d1= RooRealVar("d1","d1", 60., 40.,100)#80.)
        self.mean2 = RooFormulaVar("mean2","mean2", "mean + d1" ,RooArgList(self.mean,self.d1) )
        
        self.model1 = RooCBShape("sigCB","signal CB", self.mass, self.mean, self.sigma1, self.a, self.n)
        self.model2 = RooGaussian("sigG","signal G", self.mass, self.mean, self.sigma2)
        self.sigmodel1 = RooAddPdf("sig1", "signal pdf1", self.model1, self.model2, self.f)

        ## Create a 2nd B meson:
        self.model1s = RooCBShape("sigCB2","signal CB2", self.mass, self.mean2, self.sigma1, self.a, self.n)
        self.model2s = RooGaussian("sigG2","signal G2", self.mass, self.mean2, self.sigma2)
        self.sigmodel2 = RooAddPdf("sig2", "signal pdf2", self.model1s, self.model2s, self.f)
        self.fbs= RooRealVar("fbs","fbs", 0.75,0.5,1.)
        
        ## Confirm you add it or not
        if bothBs: self.sigmodel = RooAddPdf("sig", "signal pdf", self.sigmodel1, self.sigmodel2, self.fbs)
        else: self.sigmodel = self.sigmodel1
            
        ###bkg pdf
        self.idx= RooRealVar("idx","idx", -0.001, -1., 0.)
        self.linbkg = RooExponential("expBkg", "Exponential background pdf", self.mass, self.idx)

        # Lambda (Disabled right now)
        self.meanL = RooRealVar("lambdaPeak","lambdaPeak", 5500.)#,5400.,5600.)
        self.sigmaL = RooRealVar("sigmaL","sigmaL", 30.)#, 20., 70.)
        self.lambda_b = RooGaussian("lambda","lambda",self.mass,self.meanL,self.sigmaL)
        self.fLambda= RooRealVar("fLambda","fLambda", 0.)#0.5,0.,1.)
        ###Shoulder
        self.sh_mean = RooRealVar("sh_mean", "sh_mean", 4500., 4200.,5000.)
        self.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 300.)#, 100.,400.)
       
        #self.sh_trans.setConstant(kTRUE)
        #self.sh_sigma.setConstant(kTRUE)
        #self.sh_mean.setConstant(kTRUE)
       
        #self.shoulder = RooExpAndGauss("shoulder", "shoulder pdf", self.mass,self.sh_mean, self.sh_sigma, self.sh_trans)
        self.shoulder = RooGaussian("shoulder","shoulder pdf", self.mass, self.sh_mean, self.sh_sigma)
        #### model
        if not shoulder:
            self.fsh = RooRealVar("fh", "shoulder fraction in background", 0.)#,0.,1.)
            self.fsh.setConstant(kTRUE)
            self.sh_sigma.setConstant(kTRUE)
            self.sh_mean.setConstant(kTRUE)
        else: 
            self.fsh = RooRealVar("fh", "shoulder fraction in background", 0.5,0.,1.)
        self.bkg1 = RooAddPdf("bkg1", "background pdf1", self.shoulder, self.linbkg, self.fsh)
        self.bkg = RooAddPdf("bkg", "background pdf", self.lambda_b, self.bkg1, self.fLambda)

        self.fsig= RooRealVar("fsig","fsig", 0.5,0.,1.)
         
        self.model = RooAddPdf("model","model", self.sigmodel, self.bkg, self.fsig)
        
    def plot(self):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        self.data.plotOn(fr, RooLinkedList())
        self.model.plotOn(fr)
#        self.model.plotOn(fr,RooFit.Components("MS2"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("lambda"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
        self.model.plotOn(fr,RooFit.Components("expBkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("sig"), RooFit.LineColor(kRed))
        fr.Draw()
        return(fr)
    def toy(self,Number):
        """Generates a toy acording to the current model
        """
        if not isinstance(Number, int):
            print "Warning: Expected 'int', taking int(Number)"
            Number = int(Number)
        return self.model.generate(RooArgSet(self.mass),  Number, kFALSE)
    def reboot(self):
        """Fits again to the initializing data
        """
        self.createvars()
        self.model.fitTo(self.data)
    def fitToy(self,Number):
        """Number = number of events to be 'simulated'
            Generates a toyMC, and fits to it
        """
        data2 = self.toy(Number)
        if Number < 10000:
            self.model.fitTo(data2)
            return
        print "Too Large Data, fitting to corresponding default histogram"
        h = RooDataHist("Bmass","Bmass",RooArgSet(self.mass), data2)
        self.model.fitTo(h)
    def FitRooH(self,h):
        hr = RooDataHist("Bmass","Bmass",RooArgList(self.mass),h)
        self.createvars()
        self.model.fitTo(hr)
        fr = self.mass.frame()
        hr.plotOn(fr,RooTreeData.PlotOpt())
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("MS2"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("MS1"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("linbkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlack))

        fr.Draw()
        return(fr)
    

class sbFiter_simpl:
    def __init__(self,tree, var,cuts="", shorTime = True, shoulder = True):
        """ROOT TTree,, option 'ShorTime' does the fit to be
done in histogram instead of NTuple
        """
        f = TFile("borrame_ho.root","recreate")
        t = tree.CopyTree(cuts)
        self.mass = RooRealVar(var,var,  t.GetMinimum(var), t.GetMaximum(var))
        
        self.createvars(shoulder)
        ### fit
        self.data = RooDataSet("data","data", t, RooArgSet(self.mass))    
        N = t.GetEntries()
        f.Close()
        if N < 10000 or (not shorTime):
            print "Fitting to NTuple"
            self.model.fitTo(self.data)
        else:
            print "Fitting HISTOGRAM"
            h = RooDataHist(var,var,RooArgSet(self.mass), self.data)
            print h
            self.model.fitTo(h)
        
    def createvars(self,shoulder):
        ## sig pdf
        self.mean1 = RooRealVar("mean1","mean1", 5050, 5300)#5168.)
        self.sigma = RooRealVar("sigma","sigma", 40., 30.,50)#35.)

        self.sig = RooGaussian("Sigmodel","Sigmodel", self.mass,self.mean1, self.sigma)

        ###bkg pdf
        self.indx = RooRealVar("indx", "indx", -0.001, -0.01, 0.)
        self.linbkg = RooExponential("expBkg", "Exponential background pdf", self.mass, self.indx)

        ###Shoulder
        self.sh_mean = RooRealVar("sh_mean", "sh_mean", 4500., 4200.,5000.)
        self.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 200., 100.,400.)
       
        #self.sh_trans.setConstant(kTRUE)
        #self.sh_sigma.setConstant(kTRUE)
        #self.sh_mean.setConstant(kTRUE)
       
        #self.shoulder = RooExpAndGauss("shoulder", "shoulder pdf", self.mass,self.sh_mean, self.sh_sigma, self.sh_trans)
        self.shoulder = RooGaussian("shoulder","shoulder pdf", self.mass, self.sh_mean, self.sh_sigma)
        #### model
        if not shoulder:
            self.fsh = RooRealVar("fh", "shoulder fraction in background", 0.)#,0.,1.)
            self.fsh.setConstant(kTRUE)
            self.sh_sigma.setConstant(kTRUE)
            self.sh_mean.setConstant(kTRUE)
        else: 
            self.fsh = RooRealVar("fh", "shoulder fraction in background", 0.5,0.,1.)
        self.bkg = RooAddPdf("bkg", "background pdf", self.shoulder, self.linbkg, self.fsh)

        self.sf = RooRealVar("Sigfraction", "Sigfraction", 0.5,0.,1.) 
        #self.sig  = RooAddPdf("Sigmodel","Sigmodel", self.MS1, self.MS2, self.f1)        
        self.model = RooAddPdf("model","model", self.sig, self.bkg, self.sf)
        
    def plot(self):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        self.data.plotOn(fr, RooLinkedList())
        self.model.plotOn(fr)
        
        self.model.plotOn(fr,RooFit.Components("linbkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))

        fr.Draw()
        return(fr)
    def toy(self,Number):
        """Generates a toy acording to the current model
        """
        if not isinstance(Number, int):
            print "Warning: Expected 'int', taking int(Number)"
            Number = int(Number)
        return self.model.generate(RooArgSet(self.mass),  Number, kFALSE)
    def reboot(self):
        """Fits again to the initializing data
        """
        self.createvars()
        self.model.fitTo(self.data)
    def fitToy(self,Number):
        """Number = number of events to be 'simulated'
            Generates a toyMC, and fits to it
        """
        data2 = self.toy(Number)
        if Number < 10000:
            self.model.fitTo(data2)
            return
        print "Too Large Data, fitting to corresponding default histogram"
        h = RooDataHist("Bmass","Bmass",RooArgSet(self.mass), data2)
        self.model.fitTo(h)
    def FitRooH(self,h):
        hr = RooDataHist("Bmass","Bmass",RooArgList(self.mass),h)
        self.createvars()
        self.model.fitTo(hr)
        fr = self.mass.frame()
        hr.plotOn(fr,RooTreeData.PlotOpt())
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("MS2"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
        self.model.plotOn(fr,RooFit.Components("MS1"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("linbkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlack))

        fr.Draw()
        return(fr)
    
    
def generateFromOp(op, N, filename, labels2= []):
    from RTuple import RTuple
    from scipy import random
    from numpy import array, matrixmultiply
    from dev_unifun_byLines import toGauss_0 as G
    from numericFunctionClass import NF
    data1 = G.DataBase.keys()
    data2 = G.DataBase.values()
    qw = NF(data2, data1)    
    n = len(op.U1FS)
    if not labels2: labels2 = n*['var']
    labels = []
    for i in range(n):
        labels.append(labels2[i] + "/F")
    labels.append("evt/F")
    tup = RTuple(filename, labels)
    for i in range(N):
        evt = n*[0.]
        ni = n*[0.]
        for j in range(n):
            x = random.random()
            ni[j] = op.U2FS[j].inverse(x)
        x2 = array(matrixmultiply(op.R.I,array(ni)))
#        print x2
        tup.fillItem("evt",i)
        for j in range(n):
            tup.fillItem(labels2[j],op.U1FS[j].inverse(qw(x2[0][j])))
        tup.fill()
    tup.close()

####"mu1_track_Chi2DoF<1.4&&mu2_track_Chi2DoF<1.4&&Vchi2<4.89&&Bips<1.72&&Bdissig>15
##&&Blife_ps>0.35&&lessIPSmu>11.5"
    
def pidloop(t,Bhadron = "B0s",cuts = "GLTsb.>0.5", mass = "Bmass", w = [5000.6,5800], var = "PIDk", sg1 = ">", sg2 = ">",rang = [-10,30], N= 20):
    var1 = var + "1"+sg1
    var2 = var + "2"+sg2
    if sg1 == ">": s1 = 1.
    else: s1 = -1.
    if sg2 == ">": s2 = 1.
    else: s2 = -1.
    a = " && "
    both = 0#(sg1 != sg2)
    print "BOTH:", both
    
    cuts += "&& " + mass +">"+ str(w[0]) +" && "+mass +"<"+str(w[1])
    tup = XTuple("pid_loop_on_"+mass+"_fit",["cut/F","m/F","sm/F","sig/F","ssig/F","t/F","st/F","sig2/F","ssig2/F","fcb/F","sfcb/F","fsig/F","sfsig/F","N/F", "fLambda/F","sfL/F", "mL/F","sigL/F","smL/F","ssigL/F", "mean2/F","smean2/F","fbs/F","sfbs/F"])
    for i in range(N):
        ct = rang[0] + i*1./(N-1)*rang[1]
        
        cut = cuts + a + var1 + str(s1*ct) +a + var2+str(s2*ct)
        print cut
        op = sbFiter_ex(t, mass, cut, Bhadron, fixTo=[0,0,2,1.,1.], bothBs = both)
        tup.fillItem("cut",ct)
        tup.fillItem("m",op.mean.getVal())
        tup.fillItem("sm",op.mean.getError())
        tup.fillItem("sig",op.sigma1.getVal())   
        tup.fillItem("ssig",op.sigma1.getError())
        tup.fillItem("t",op.a.getVal())
        tup.fillItem("st",op.a.getError())
        tup.fillItem("N", t.GetEntries(cut))
        tup.fillItem("sig2",op.sigma2.getVal())   
        tup.fillItem("ssig2",op.sigma2.getError())
        tup.fillItem("fcb",op.f.getVal())   
        tup.fillItem("sfcb",op.f.getError())
        tup.fillItem("fsig",op.fsig.getVal())   
        tup.fillItem("sfsig",op.fsig.getError())
        tup.fillItem("fLambda",op.fLambda.getVal())
        tup.fillItem("sfL",op.fLambda.getError())
        tup.fillItem("mL",op.meanL.getVal())
        tup.fillItem("smL",op.meanL.getError())
        tup.fillItem("sigL",op.sigmaL.getVal())   
        tup.fillItem("ssigL",op.sigmaL.getError())
        tup.fillItem("mean2",op.mean2.getVal())
        sm2 = sqrt(op.mean.getError()**2 + op.d1.getError()**2)
        
        tup.fillItem("smean2",sm2)
        tup.fillItem("fbs",op.fbs.getVal())   
        tup.fillItem("sfbs",op.fbs.getError())
        tup.fill()
    tup.close()
    return op

def pidloopInc(t,cuts = "GLTsb.>0.5", mass = "Bmass", w = [5000.6,5800], rang = [-10,60], N= 20):
    var1 = "abs(PIDk1)>"
    var2 = "abs(PIDk2)>"
    
    a = " && "
    
    cuts += "&& " + mass +">"+ str(w[0]) +" && "+mass +"<"+str(w[1])
    tup = XTuple("pid_loop_Inc",["cut/F","m/F","sm/F","sig/F","ssig/F","fsig/F","sfsig/F","N/F", "fLambda/F","sfL/F", "mL/F","sigL/F","smL/F","ssigL/F", "mean2/F","smean2/F", "f1/F","sf1/F"])
    for i in range(N):
        ct = rang[0] + i*1./(N-1)*rang[1]
        
        cut = cuts + a + var1 + str(ct) +a + var2+str(ct)
        op = sbFiter(t, mass, cut)
        tup.fillItem("cut",ct)
        tup.fillItem("m",op.mean1.getVal())
        tup.fillItem("sm",op.mean1.getError())
        tup.fillItem("sig",op.sigma.getVal())   
        tup.fillItem("ssig",op.sigma.getError())
        tup.fillItem("N", t.GetEntries(cut))
        tup.fillItem("fsig",op.sf.getVal())   
        tup.fillItem("sfsig",op.sf.getError())
        tup.fillItem("f1",op.f1.getVal())   
        tup.fillItem("sf1",op.f1.getError())
        tup.fillItem("fLambda",op.fLambda.getVal())
        tup.fillItem("sfL",op.fLambda.getError())
        tup.fillItem("mL",op.meanL.getVal())
        tup.fillItem("smL",op.meanL.getError())
        tup.fillItem("sigL",op.sigmaL.getVal())   
        tup.fillItem("ssigL",op.sigmaL.getError())
        tup.fillItem("mean2",op.mean2.getVal())
        sm2 = sqrt(op.mean1.getError()**2 + op.d1.getError()**2)
        tup.fillItem("smean2",sm2)
        
        tup.fill()
    tup.close()
   
def generateFromVars(ch, v,N, filename):
    xm = []
    from dev_unifun_byLines import UnCorrGaussOperator
    for var in v:
        xm.append(ch.takeKey(var))
    op = UnCorrGaussOperator(xm)
    generateFromOp(op,N,filename, v)

def Etis(t,txtos,var = "Bpt", cuts = "GLTsb.>0.5", mass = "Bmass", w = [5000.,5800], N= 20):
    v = []
    for i in range(t.GetEntries()):
        t.GetEntry(i)
        if getattr(t, "GLTsb.")<0.5 : continue
        if t.L0_tos < 0.5: continue
        if t.HLT1_tos < 0.5: continue
        if t.HLT2_tos < 0.5: continue
        
        v.append(getattr(t,var))
       # print t.var
    v.sort()
    print len(v)
    a = " && "
    cuts += a + mass +">"+ str(w[0]) +a+mass +"<"+str(w[1])
    tup = XTuple("etis_sb_"+var,["cut/F","Ntistos/F","fsig_tis/F","sfsig_tis/F","Nxtos/F","fsig_xtos/F","sfsig_xtos/F","etis/F","setis/F"])
    for i in range(len(v)-N):
        if i%N: continue
        cut = cuts + a + var + ">=" + str(v[i]) + a + var + "<" + str(v[i+N])
        op = sbFiter(t, mass, cut + "&& L0_tos >0.5 && HLT1_tos >0.5 && HLT2_tos > 0.5")   ##### TIS AND TOS
        tup.fillItem("cut",(v[i]+ v[i+N])*.5)
        #tup.fillItem("m",op.mean1.getVal())
        #tup.fillItem("sm",op.mean1.getError())
        #tup.fillItem("sig",op.sigma.getVal())   
        #tup.fillItem("ssig",op.sigma.getError())
        Ntistos = op.data.tree().GetEntries()
        Ntistos_s = Ntistos* op.sf.getVal()
        sNtistos_s = sqrt(1./Ntistos + (op.sf.getError()/op.sf.getVal())**2)*Ntistos_s
        tup.fillItem("Ntistos", Ntistos)
        tup.fillItem("fsig_tis",op.sf.getVal())   
        tup.fillItem("sfsig_tis",op.sf.getError())

        
       # tup.fillItem("f1",op.f1.getVal())   
       # tup.fillItem("sf1",op.f1.getError())
       # tup.fillItem("fLambda",op.fLambda.getVal())
       # tup.fillItem("sfL",op.fLambda.getError())
       # tup.fillItem("mL",op.meanL.getVal())
       # tup.fillItem("smL",op.meanL.getError())
       # tup.fillItem("sigL",op.sigmaL.getVal())   
       # tup.fillItem("ssigL",op.sigmaL.getError())
       # tup.fillItem("mean2",op.mean2.getVal())
        #sm2 = sqrt(op.mean1.getError()**2 + op.d1.getError()**2)
        #tup.fillItem("smean2",sm2)
        op = sbFiter(txtos, mass, cut)   
        Nxtos = op.data.tree().GetEntries()
        Nxtos_s = Nxtos* op.sf.getVal()
        sNxtos_s = sqrt(1./Nxtos + (op.sf.getError()/op.sf.getVal())**2)*Nxtos_s

        etis, setis = nonIndepErrors(Ntistos_s, Ntistos_s+Nxtos_s, sNtistos_s, sNxtos_s)
       
        tup.fillItem("Nxtos", Nxtos)
        tup.fillItem("fsig_xtos",op.sf.getVal())   
        tup.fillItem("sfsig_xtos",op.sf.getError())
        tup.fillItem("etis",etis)
        tup.fillItem("setis",setis)
        
        tup.fill()
    tup.close()
    
def s_abc(a,b,c,sa,sb,sc):
    """ S( (A+B)/(A+C) ) """
    aci = 1./(a+c)
    ta = (c-b)*aci
    tb = 1
    tc = (a+b)*aci
    return (a+b)*aci, aci*sqrt((ta*sa)**2 + (tb*sb)**2 +(tc*sc)**2)

def bkg_inbin(x,y,k,Nsb):
    
    a = 5369.6 - 600
    b = 5200
    c = 5450
    d = 5369.6 + 600
    #Nsb = t.GetEntries("(Bmass<"+str(b)+ "|| Bmass> " + str(c) +")"+ cut)
    #print Nsb
    #sNsb = sqrt(Nsb)
    kl = -k
    iDk = 1./(exp(kl*a) +exp(kl*c) - exp(kl*b) - exp(kl*d))
    Nxy = iDk*Nsb*(exp(kl*x)-exp(kl*y))
    #ddk = iDk*Nsb*((-x*exp(kl*x)+y*exp(kl*y))-iDk*(exp(kl*x)-exp(kl*y))*(-1)*(a*exp(kl*a) +c*exp(kl*c) - b*exp(kl*b) - d*exp(kl*d)))
    #sNxy = sqrt((ddk*sk)**2 + (iDk*sNsb*(exp(kl*x)-exp(kl*y)))**2)
    return Nxy
    

def br_F(bru, sbru,brj,sbrj,brd,sbrd,nd,snd,nu,snu):
    brd = brd
    ibrd = 1./brd
    bru2 = bru*bru
    nu2 = nu*nu
    inu2 = 1./nu2
    alpha = bru2*brj*nd*ibrd*inu2*3./2

    ddu = 2*bru*brj*nd*inu2*ibrd*3./2
    ddj = alpha/brj
    ddnd = alpha/nd
    ddnu = -2*alpha/nu
    ddd = -alpha*ibrd

    return alpha, sqrt( (ddu*sbru)**2 + (ddj*sbrj)**2 + (ddnd*snd)**2 + (ddnu*snu)**2 + (ddd*sbrd)**2)


Mpi = 139.57018
Mk = 493.677
Mmu = 105.658367

def mass(p1,p2,m1,m2,x):
    m1_2 = m1**2
    m2_2 = m2**2
    p1_2 = p1**2
    p2_2 = p2**2
    return sqrt(m1_2 + m2_2 + 2*p1*p2*x + 2*sqrt((p1_2+m1_2)*(p2_2+m2_2)))

def addMasses(name, path = "B2hh", m1 = Mmu, m2 = Mmu):
    f = TFile(name + ".root")
    t = f.Get(path)
    a = t.GetListOfBranches()
    names, labels = [], []
    for branch in a:
        names.append(branch.GetName())
        labels.append(branch.GetName() + "/F")
    labels+=["Mmumu/F","MKpi/F","MpiK/F","Mpipi/F","MKK/F","ThM/F"]
    tup = RTuple(name + "_withM", labels)
    rangeN = range(t.GetEntries())

    for i in rangeN:
        t.GetEntry(i)
        for name in names:
            tup.fillItem(name,getattr(t,name))
        Bm_2 = t.Bmass**2
        p1 = vector(t.mu1p1,t.mu1p2,t.mu1p3)
        p2 = vector(t.mu2p1,t.mu2p2,t.mu2p3)
        p1m = vmod(p1)
        p2m = vmod(p2)
        p1_2 = p1m**2
        p2_2 = p2m**2
        m1_2 = m1**2
        m2_2 = m2**2

        x = (Bm_2 -  2*sqrt((p1_2+m1_2)*(p2_2+m2_2)) - m1_2-m2_2)/(2*p1m*p2m)

        tup.fillItem("ThM",x)
        tup.fillItem("Mmumu",mass(p1m,p2m,Mmu,Mmu,x))
        tup.fillItem("MKK",mass(p1m,p2m,Mk,Mk,x))
        tup.fillItem("MKpi",mass(p1m,p2m,Mk,Mpi,x))
        tup.fillItem("MpiK",mass(p1m,p2m,Mpi,Mk,x))
        tup.fillItem("Mpipi",mass(p1m,p2m,Mpi,Mpi,x))
        tup.fill()
    tup.close()
        
        
        
        
