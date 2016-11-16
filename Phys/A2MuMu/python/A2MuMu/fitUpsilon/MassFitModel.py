from ROOT import gROOT, RooRealVar, RooGaussian, RooFFTConvPdf
gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx+")
#gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx")
from ROOT import RooIpatia2

def getMassFitModel(mvar, mother='A1', mass=10000, fixedPars = True, takeParsFrom = 'Y1MC2012' ):

    CentralMass = {'Y1': 9468, 'Y2': 10023, 'Y3': 10355}
    if mother in CentralMass.keys():
        mass = CentralMass(mother)

    ipa_s = RooRealVar("ipa_s","ipa_s", 59., 10.,200.)
    ipa_m = RooRealVar("ipa_m","ipa_m",mass, mass-60, mass+60)
    beta = RooRealVar("beta","beta",0.,-0.1, 0.1)
    zeta = RooRealVar("zeta","zeta",2.5e-4)
    l = RooRealVar("l","l",-1.25,-6,-1.)
    #a = RooRealVar("a","a",1.58,1.0,10.0)
    a = RooRealVar("a","a",1.4)
    n = RooRealVar("n","n",1.,0.1,50) #leaving just n parameter of left tail free
    n2 = RooRealVar("n2","n2",0) ## remove right tail
    a2 = RooRealVar("a2","a2",100.)
    ipatia = RooIpatia2("ipatia","ipatia", mvar, l, zeta, beta, ipa_s, ipa_m, a, n, a2, n2)
    sigma0= RooRealVar("sigma0","sigma0",25, 15, 40)
    mean0= RooRealVar("mean0","mean0",0)
    res0 = RooGaussian("reso0","reso0",mvar,mean0,sigma0)
    ipa2 = RooFFTConvPdf("ipa2","ipa2",mvar, ipatia,res0)
    sigPDF = ipa2

    if fixedPars:
        import simplejson as json
        def importResultFile(tag):
            resultfile = open('./FIT_RESULTS/fitParResults_{0}.py'.format(tag),'r')
            sample = json.load(resultfile)
            return sample

        fixedPars = importResultFile(takeParsFrom + "_Allpt")

        val = {}
        err = {}
        (minpt, maxpt,
               val['a'], err['a'],
               val['a2'], err['a2'],
               val['n'], err['n'],
               val['n2'], err['n2'],
               val['l'], err['l'],
               val['zeta'], err['zeta'],
               val['beta'], err['beta'],
               val['ipa_s'], err['ipa_s'],
               val['ipa_m'], err['ipa_m'],
               val['sigma0'], err['sigma0'],
               chi2) = fixedPars[0]

        def estimateSigma0(inputmass):
            slope = 0.00235
            y0 = 3.73
            sigma0 = inputmass*slope + y0
            return sigma0

        val['sigma0'] = estimateSigma0(mass)

        variablesToBeFixed = {'a':a, 'a2':a2, 'n':n, 'n2':n2, 'l':l, 'zeta':zeta, 'beta':beta, 'ipa_m':ipa_m, 'ipa_s':ipa_s, 'sigma0':sigma0}

        for vname, variable in variablesToBeFixed.items():
            variable.setVal(val[vname])
            variable.setConstant()
    xframe = mvar.frame()
    sigPDF.plotOn(xframe)
    xframe.Draw()

    return sigPDF

def getStupidGaussian(mvar):
    mean = RooRealVar('mean','mean',0)
    sigma = RooRealVar('sigma','sigma',1)
    gauss = RooGaussian('gauss','gauss',mvar, mean, sigma)
    return gauss


