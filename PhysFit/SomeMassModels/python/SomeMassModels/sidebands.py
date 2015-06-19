from ROOT import *
from FiterBasis import *
from SomeUtils.alyabar import *

class sidebandsFiter:
    def __init__(self,tree, var="Bmass",cuts="", left = 5215.01, right = 5423.1, shorTime = True, weight_var=0, bkgf = bkg_with_gauss_shoulder, fit_in_init = 1, Mmin =0, Mmax =0, chi2 = 0, left2 =0,right2 = 0, cpus = 1):
        print cuts
        self.var = var
        f = TFile("borrame_ho.root","recreate")
        t = tree.CopyTree(cuts)
        if Mmin: self.Mmin = Mmin
        else : self.Mmin = t.GetMinimum(var)
        if Mmax: self.Mmax = Mmax
        else : self.Mmax = t.GetMaximum(var)
        
        self.left = left
        self.right = right
        if not left2 : self.left2 = self.left
        else: self.left2 = left2
        if not right2 : self.right2 = self.right
        else: self.right2 = right2
        
        self.mass = RooRealVar(var,var, self.Mmin, self.Mmax)
        self.mass.setRange("left_SB", self.Mmin, left)
        self.mass.setRange("right_SB", right, self.Mmax)
        self.mass.setRange("left_SB0", 5366.3-600, left)
        self.mass.setRange("right_SB0", right, 5366.3+600)
        self.mass.setRange("signal_region", self.left2, self.right2)
        
                
        ### fit
        if weight_var:
            self.w = RooRealVar(weight_var, weight_var,  tree.GetMinimum(weight_var), tree.GetMaximum(weight_var))
            self.data = RooDataSet("data","data", t, RooArgSet(self.mass, self.w))
            self.data.setWeightVar(self.w)

        else: self.data = RooDataSet("data","data", t, RooArgSet(self.mass))
        #self.data = RooDataSet("data","data", t, RooArgSet(self.mass))
        #sigf(self)
        bkgf(self)

        #self.nsig = RooRealVar("Sigfraction", "Sigfraction", 0.5*self.data.tree().GetEntries(),0.,self.data.tree().GetEntries())
        self.nbkg = RooRealVar("bkgfraction", "bkgfraction", 0.5*self.data.tree().GetEntries(),0.,self.data.tree().GetEntries())
        
        self.model = RooExtendPdf(  'epdf_bkg', 'extended bkg pdf', self.bkg, self.nbkg,"signal_region" )# RooAddPdf("model","model", RooArgList(self.sig, self.bkg), RooArgList(self.nsig, self.nbkg))
        f.Close()
       
        
       
        self.use_chi2 = chi2
        #self.fitRange =  RooFit.Range("left_SB,right_SB")
        if fit_in_init: self.fit(var,shorTime, cpus)
      ##  self.sbmodels = {}

        
        
    def fit(self, var, shorTime = True, cpus = 1):
        N = self.data.tree().GetEntries()

        if self.use_chi2:
            print "CHI2 "#, fitting in 20 Bins ......."
            #self.mass.setBins(20)
            h = RooDataHist(var,var,RooArgSet(self.mass), self.data)#,RooFit.Binning(20))
            print h
            chi2 = RooChi2Var("chi2","chi2", self.model,h, RooFit.Range("left_SB,right_SB"))
            m = RooMinuit(chi2)
            m.migrad()
            m.hesse()
            m.save()
            #self.model.fitTo(h, RooFit.Range("left_SB,right_SB"))
        if not shorTime:
            print "Fitting to NTuple"
            self.model.fitTo(self.data, RooFit.Range("left_SB,right_SB"),RooFit.Minos(True), RooFit.Strategy(1), RooFit.Extended(True),RooFit.Save(true),RooFit.Verbose(False), RooFit.NumCPU(cpus))
        else:
            print "Fitting HISTOGRAM"
            h = RooDataHist(var,var,RooArgSet(self.mass), self.data)
            print h
            self.model.fitTo(h, RooFit.Range("left_SB,right_SB"),RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(true),RooFit.Verbose(False), RooFit.Extended(True),RooFit.NumCPU(cpus))
            
    def fitOneSB(self,sb = "left_SB", shorTime = False, cpus=1):
        
        if self.use_chi2:
            print "CHI2 "#, fitting in 20 Bins ......."
            #self.mass.setBins(20)
            h = RooDataHist(var,var,RooArgSet(self.mass), self.data)#,RooFit.Binning(20))
            print h
            chi2 = RooChi2Var("chi2","chi2", self.model,h, RooFit.Range(sb))
            m = RooMinuit(chi2)
            m.migrad()
            m.hesse()
            m.save()
            #self.model.fitTo(h, RooFit.Range("left_SB,right_SB"))
        if not shorTime:
            print "Fitting to NTuple"
            self.model.fitTo(self.data, RooFit.Range(sb),RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(true),RooFit.Verbose(False), RooFit.Extended(True),RooFit.NumCPU(cpus))
        else:
            print "Fitting HISTOGRAM"
            h = RooDataHist(var,var,RooArgSet(self.mass), self.data,RooFit.Minos(True), RooFit.Strategy(1), RooFit.Save(true),RooFit.Verbose(False), RooFit.Extended(True),RooFit.NumCPU(cpus))
            print h
            self.model.fitTo(h, RooFit.Range(sb))
        
    
    def toy(self,Number):
        """Generates a toy acording to the current model
        """
        if not isinstance(Number, int):
            print "Warning: Expected 'int', taking int(Number)"
            Number = int(Number)
        return self.model.generate(RooArgSet(self.mass),  Number, kFALSE)
        
    def plot(self, bins = 100, adders = None, models =[], add_one_exp = False):
        """Plots the data and the models
        """
        fr = self.mass.frame()
        
        if add_one_exp:
            self.data.plotOn(fr, RooFit.Binning(bins),RooFit.Range("left_SB0,right_SB0"))
            self.model.plotOn(fr,RooFit.Range("left_SB0,right_SB0"))
        else:
            self.data.plotOn(fr, RooFit.Binning(bins))
            self.model.plotOn(fr)#, RooFit.Range("left_SB,right_SB"))
            self.model.plotOn(fr, RooFit.Range("signal_region"), RooFit.LineStyle(kDashed))
            
        for model in models:
            if add_one_exp: self.model.plotOn(fr,RooFit.Range("left_SB0,right_SB0"), RooFit.Components(model), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
            else: self.model.plotOn(fr,RooFit.Range("left_SB,right_SB"), RooFit.Components(model), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
       
            
        if adders:
            x = getattr(self,adders)
            x0 = x.getVal()
            x1 = x.getError()
            x.setVal(x0-x1)
            self.model.plotOn(fr, RooFit.LineStyle(kDashed))
            x.setVal(x0+x1)
            self.model.plotOn(fr, RooFit.LineStyle(kDashed))
        if add_one_exp:
            self.indx1.setVal(add_one_exp[0])
            self.indx1.setError(add_one_exp[1])
            self.f1.setVal(1)
            self.model.plotOn(fr, RooFit.LineStyle(kDotted),RooFit.LineColor(kMagenta), RooFit.Range("left_SB0,right_SB0"), RooFit.NormRange("left_SB0,right_SB0"))
            self.indx1.setVal(add_one_exp[0] + add_one_exp[1])
            self.model.plotOn(fr, RooFit.LineStyle(kDashed),RooFit.LineColor(kMagenta), RooFit.Range("left_SB0,right_SB0"), RooFit.NormRange("left_SB0,right_SB0"))
            self.indx1.setVal(add_one_exp[0] - add_one_exp[1])
            self.model.plotOn(fr, RooFit.LineStyle(kDashed),RooFit.LineColor(kMagenta), RooFit.Range("left_SB0,right_SB0"), RooFit.NormRange("left_SB0,right_SB0"))
                        
        fr.Draw()
        return(fr)
    
    def fractionInRange(self, xmin, xmax):
        self.mass.setVal(xmin)
        y1 = self.model.createCdf(RooArgSet(self.mass))
        y1 = y1.getVal()
        self.mass.setVal(xmax)
        y2 = self.model.createCdf(RooArgSet(self.mass))
        y2 = y2.getVal()

        return y2 - y1

    def fractionInSB(self):
        return self.fractionInRange(self.Mmin, self.left) + self.fractionInRange(self.right, self.Mmax)
    
    def fractionInBd(self):
        print "Bd region : ", self.left, " - " , self.left +120
        return self.fractionInRange(self.left,self.left + 120)

    def fractionInBs(self):
        print "Bd region : ", self.right-120, " - " , self.right
        return self.fractionInRange(self.right-120,self.right)
    
    def KScheck(self, n = 10000, st = None):
        x = self.toy(n)
        ltoy = []
        l = []
        for entry in x.tree():
            m = entry.Bmass
            if m > self.left and m < self.right: continue
            ltoy.append(m)
        ltoy.sort()
        
        for entry in self.data.tree():
            m = entry.Bmass
            if m > self.left and m < self.right: continue
            l.append(m)
        ks = KSstat(ltoy,l,st)
        return TMath.KolmogorovProb(ks)

    def KStoycheck(self, n = 10000, st = None):
        x = self.toy(n)
        y = self.toy(n)
        
        ltoy = []
        l = []
        for entry in x.tree():
            m = entry.Bmass
            if m > self.left and m < self.right: continue
            ltoy.append(m)
        ltoy.sort()
        
        for entry in y.tree():
            m = entry.Bmass
            if m > self.left and m < self.right: continue
            l.append(m)
        ks = KSstat(ltoy,l,st)
        return TMath.KolmogorovProb(ks)
        
    def getSignal(self):
        var = self.var
        print self.data.tree().GetEntries(var + ">"+str(self.left) + "&&" + var + "<"+str(self.right)) - self.nbkg.getVal()
        print self.data.tree().GetEntries(var + ">"+str(self.left) + "&& "+var+"<"+str(self.right)) - self.data.tree().GetEntries("!("+var+">"+str(self.left) + "&&"+var+"<"+str(self.right)+")")*(1-self.fractionInSB())*1./self.fractionInSB()
        
        return self.data.tree().GetEntries(var+">"+str(self.left) + "&& "+var+"<"+str(self.right)) - self.nbkg.getVal()
