from ROOT import *


class ProbTool:
    def __init__(self, inputs, models, name = "ProbTool"):
        self.name = name
        self.input_names = []
        if isinstance(models, list):
            self.models = RooArgList()
            for model in models : self.models.add(model)
            
        else : self.models = models
        if isinstance(inputs, list):
            self.inputs = RooArgSet()
            for input in inputs:
                self.inputs.add(input)
                self.input_names.append(input.GetName())
        else: self.inputs = inputs
        #self.model = RooProdPdf()
        
        self.updateModel()
        
    def updateModel(self): self.model = RooProdPdf(self.name,self.name,self.models)
    
    def readDic(self, inputDic):
        """
        Read a dictionary with values for the input parameters, and evaluate the pdf of such point
        """
        for key in inputDic.keys():
            self.inputs[key].setVal(inputDic[key])
        return self.model.getVal()
    
    def read_pe(self, pe):
        """
        Read a pseudoexperiment and evaluate the pdf of such point
        """
        for key in self.input_names:
            self.inputs[key].setVal(pe[key].getVal())
        return self.model.getVal()
   
    
    def run_ps(self, N = 50000):
        """
        Run the pseudoexperiments
        """
        self.pes = self.model.generate(self.inputs,N, kFALSE)
    
    def prepareCL(self):
        """
        Runs the pseudoexperiments -call to run_ps-  and evaluates the distribution of the pdf 
        """
        if "pes" not in dir(self): self.run_ps()
        self.Xvals = []
        for i in range(self.pes.tree().GetEntries()):
            self.Xvals.append(self.read_pe(self.pes.get(i)))
        self.Xvals.sort()
        
    def CL(self,x):
        """
        Calculates a 'goodenss of fit' CL as Prob( pdf_perfect <= pdf_observed)
        """
        n = 0
        for y in self.Xvals:
            if y>x : break
            n+=1
        return n*1./len(self.Xvals)
        
    def evaluateCL_dict(self, pointDic):
        """
        Read a dictionary with values for the input parameters, and evaluate a 'goodness of fit' CL for such point
        """
        x = self.readDic(pointDic)
        return self.CL(x)
    
    def pdfCombinedVar(self, formula, varname = "", xmin = "", xmax ="", Nbins  = 300):
        """
        Creates a pdf for a variable that is a combination of the input parameters
        """
        if not varname:  varname = formula
        if "pes" not in dir(self): self.run_ps()
        eta = RooFormulaVar(varname + "For" ,varname + "For", formula, RooArgList(self.inputs) )
        l = []
        for i in range(self.pes.tree().GetEntries()):
            pe = self.pes.get(i)
            for key in self.input_names:
                self.inputs[key].setVal(pe[key].getVal())
            l.append(eta.getVal())
        if xmin == "": xmin = min(l)
        if xmax == "": xmax = max(l)

        h = TH1F(varname + "TH1F",varname + "TH1F", Nbins,xmin,xmax)
        eta0 = RooRealVar(varname,varname, xmin, xmax)
        for x in l: h.Fill(x)
        pdfname = varname
        h2 = RooDataHist(varname+"RooDataist",varname + "RooDataHist", RooArgList(eta0),h)
        
        return eta0, RooHistPdf(pdfname+"Roo",pdfname + "Roo", RooArgSet(eta0),h2), h2, h
    
    def integral(self, param, xmin,xmax):
        """
        Calculates the probability that 'param' falls between xmin and xmax
        """
        for i in range(len(self.input_names)):
            if self.input_names[i] == param: break
        pdf = self.models[i]
        self.inputs[param].setVal(xmin)
        y1 = pdf.createCdf(RooArgSet(self.inputs[param]))
        y1 = y1.getVal()
        self.inputs[param].setVal(xmax)
        y2 = pdf.createCdf(RooArgSet(self.inputs[param]))
        y2 = y2.getVal()

        return y2 - y1
    
    def range(self,param,cl = 0.68268949213708596, N = 10000, SYM =0 , center = "no"):
        """
        
        """
        #if not "pes" in dir(self): self.run_ps()
        l = []
        if (1-cl) * N < 100:
            print "warning. Using ",N," pes for a cl of", cl
            print "You might want to increase the no. of pes"
        p2 = param + "_copy"
        a =  self.pdfCombinedVar( param, p2, self.inputs[param].getMin(),self.inputs[param].getMax())
        tool2 = ProbTool([a[0]],[a[1]])
        
        tool2.run_ps(N)
        tool2.prepareCL()
        print "here"
        #from SomeUtils import numericFunctionClass
        #NF = numericFunctionClass.NF
        for i in range(tool2.pes.tree().GetEntries()):
            pe = tool2.pes.get(i)
            R = pe[p2].getVal()
            #print i
            l.append([tool2.evaluateCL_dict({p2:R}),R])
        print "there"
        l.sort()
        l.reverse()
        
        if center == "no": M = l[0][1]
        else: M = center
        x_0 = ""
        x_1 = ""
        for entry in l:
            CL = entry[0]
            R = entry[1]
            if (not SYM) and (CL > 1-cl): continue
            if R < M and x_0 == "": x_0 = R
            if R > M and x_1 == "": x_1 = R
            if x_0 != "" and x_1 !="":
                if not SYM: break
                #I0 = self.integral(param,x_0,x_1)
                
                I1 =  self.integral(param,x_0,M)
                if I1 < 0.5*cl: x_0 = ""
                I2 = self.integral(param,M, x_1)
                if I2 < 0.5*cl: x_1 = ""
                
        if x_0 == "": x_0 = a[0].getMin()
        if x_1 == "": x_1 = a[0].getMax()
        I0 = self.integral(param,x_0,x_1)
        I1 =  self.integral(param,x_0,M)
        I2 = self.integral(param,M, x_1)
        print "Integral from lower bound to upper bound :", I0
        print "Integral from lower bound to most probable value :", I1
        print "Integral from upper bound to most probable value :", I2
        return M, x_0, x_1
    
    def plot_pdf(self, param):
        fr = self.inputs[param].frame()
        for i in range(len(self.input_names)):
            if self.input_names[i] == param: break
        pdf = self.models[i]
        pdf.plotOn(fr)
        fr.Draw()
        return fr
        
        
        
            
        
        

def pdfFromAscii(xvar, filename,pdfname,  xname, yname, sc = 1., nbins = 1000):
    from dev_channelclass import channelData
    from SomeUtils import numericFunctionClass
    NF = numericFunctionClass.NF
    ch = channelData(filename, typ = "ASCII")
    x = ch.takeKey(xname)
    for i in range(len(x)):
        x[i]= sc*x[i] ### in case that a change of units is desired
    y = ch.takeKey(yname)
    F = NF(x,y)
    h = TH1F(pdfname,pdfname,nbins, xvar.getMin(),xvar.getMax())
    for i in range(nbins):
        h.SetBinContent(i+1, F(h.GetBinCenter(i+1)))
        h.SetBinError(i+1,0)
    h2 = RooDataHist(pdfname+"D",pdfname + "D", RooArgList(xvar),h)
    return RooHistPdf(pdfname+"Roo",pdfname + "Roo", RooArgSet(xvar),h2), h2, h

            
## x0 = RooRealVar("x0","x0", -100,100)
## m0 = RooRealVar("m0","m0", 0)
## s0 = RooRealVar("s0","s0", 1)
## g0 = RooGaussian("g0","g0", x0,m0,s0)

## x1 = RooRealVar("x1","x1", -100,100)
## m1 = RooRealVar("m1","m1", 5)
## s1 = RooRealVar("s1","s1", 3)
## g1 = RooGaussian("g1","g1", x1,m1,s1)

## x2 = RooRealVar("x2","x2", -100,100)
## m2 = RooRealVar("m2","m2", 0)
## s2 = RooRealVar("s2","s2", 2)
## g2 = RooGaussian("g2","g2", x2,m2,s2)

## tool = ProbTool([x0,x1,x2],[g0,g1,g2])
## tool.prepareCL()
## g_1, g_2, g_3 = TGraph(),TGraph(), TGraph()
## idx =0
## for i in range(20):
##     x = -10 + i
##     for j in range(20):
##         y = -10 + j
##         for k in range(20):
##             z = -10 + k
##             chi2 = x**2 + ((y-5)*1./3)**2 + (0.5*z)**2
##             w1 =  TMath.Prob(chi2,3)
##             g_2.SetPoint(idx, chi2,w1)
##             ww = tool.evaluateCL_dict({"x0":x, "x1":y,"x2":z})
##             g_1.SetPoint(idx, chi2,ww )
##             g_3.SetPoint(idx, w1,ww )
            
##             idx +=1
            
              

## x0 = RooRealVar("BR","BR", 0,20)
## h = pdfFromAscii(x0,"pdf_bsmm_cmslhcb.dat","Bs mumu pdf",  "BR", "pdf_sb", sc = 1., nbins = 1000)
## tool = ProbTool([x0],[h[0]])
## tool.prepareCL()
## g = TGraph()

## for i in range(200):
##     BR = 0.1*i
##     g.SetPoint(i,BR, tool.evaluateCL_dict({"BR":BR}))
## g.Draw("AL*")
               
