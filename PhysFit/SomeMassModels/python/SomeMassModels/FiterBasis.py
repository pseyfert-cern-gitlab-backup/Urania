from ROOT import *



def exp_bkg(fiter,lambda_b = 0):
    """ models the bkg as an exponential
    """
    ###bkg pdf
    fiter.indx = RooRealVar("indx", "indx", -1e-04, -1., 0.)
    fiter.bkg = RooExponential("bkg", "Exponential background pdf", fiter.mass, fiter.indx)
        
    return 1

def exp_bkg_pos(fiter,lambda_b = 0):
    """ models the bkg as an exponential
    """
    ###bkg pdf
    fiter.indx = RooRealVar("indx", "indx", 1e-04, 0, 1.)
    fiter.bkg = RooExponential("bkg", "Exponential background pdf", fiter.mass, fiter.indx)
        
    return 1

def exp_and_log(fiter):
    fiter.indx = RooRealVar("indx", "indx", -1e-04, -1., 0.)
    fiter.expbkg = RooExponential("expbkg", "Exponential background pdf", fiter.mass, fiter.indx)
    fiter.logvar = RooRealVar("logvar", "logvar", 620.,600,800)
    fiter.fexpbkg = RooRealVar("fbkg","fbkg",0.5,0.,1.)
    fiter.logbkg = RooGenericPdf("logBkg","log("+fiter.var+"-logvar)",RooArgList(fiter.mass,fiter.logvar))
    fiter.bkg=RooAddPdf("bkg","background pdf",fiter.expbkg,fiter.logbkg,fiter.fexpbkg)
            


def double_exp_bkg(fiter,lambda_b = 0):
    """ models the bkg as an double exponential +
    """
    ###bkg pdf
    fiter.indx1 = RooRealVar("indx1", "indx1", -1e-04, -1., 0.)
    fiter.delta = RooRealVar("delta", "delta", -1e-04, -1., 0.)
    fiter.indx2 = RooFormulaVar("indx2","indx2", "indx1 + delta" ,RooArgList(fiter.indx1,fiter.delta) )
    fiter.bkg1 = RooExponential("bkg 1", "Exponential background pdf 1", fiter.mass, fiter.indx1)
    fiter.bkg2 = RooExponential("bkg 2", "Exponential background pdf 2", fiter.mass, fiter.indx2)
    fiter.f1 = RooRealVar("f1","f1",0.5, 0., 1.)
    fiter.bkg = RooAddPdf("bkg", "background pdf", fiter.bkg1, fiter.bkg2, fiter.f1)    
    return 1

def lin_bkg(fiter):
    fiter.indx = RooRealVar("indx", "indx", 0. -1., 1.)
    fiter.bkg = RooPolynomial("expBkg", "Exponential background pdf", fiter.mass, RooArgList(fiter.indx))


def gaussian_signal(fiter):
    fiter.mean = RooRealVar("mean","mean",5050, 5300)#5168.)
    fiter.sigma = RooRealVar("sigma","sigma", 16.,46)#35.)
    fiter.sig  = RooGaussian("Sigmodel","Sigmodel", fiter.mass, fiter.mean, fiter.sigma)
    return 1

def cruijff_signal(fiter):
    fiter.mean = RooRealVar("mean","mean",5200, 5400)#5168.)
    fiter.sigmaL = RooRealVar("sigmaL","sigmaL", 4.,46)#35.)
    fiter.sigmaR = RooRealVar("sigmaR","sigmaR", 4.,46)#35.)
    fiter.alphaL = RooRealVar("alphaL","alphaL", 1e-06,0.,.5)#35.)
    fiter.alphaR = RooRealVar("alphaR","alphaR", 1e-06,0.,.5)#35.)
    
    fiter.sig  = RooJohanCruijff("Sigmodel","Sigmodel", fiter.mass, fiter.mean, fiter.sigmaL,fiter.sigmaR,fiter.alphaL,fiter.alphaR)
    return 1


def apollonios_signal(fiter):
    fiter.mean = RooRealVar("mean","mean",5200,5400.)
    fiter.sigma = RooRealVar("sigma","sigma", 2.,46)#35.)
    fiter.b = RooRealVar("b","b",1,0.5,4)
    fiter.n = RooRealVar("n","n",1,40)
    fiter.a = RooRealVar("a","a",1,20)
    fiter.sig  = RooApollonios("Sigmodel","Sigmodel", fiter.mass, fiter.mean, fiter.sigma, fiter.b, fiter.a, fiter.n)
    return 1

def double_apollonios_signal(fiter):
    fiter.mean = RooRealVar("mean","mean",5200,5400.)
    fiter.sigma = RooRealVar("sigma","sigma", 2.,46)#35.)
    fiter.delta_s = RooRealVar("delta_s", "delta_s", 2., 35.)
    fiter.sigma2 = RooFormulaVar("sigma2","sigma2", "sigma + delta_s" ,RooArgList(fiter.sigma,fiter.delta_s) )
   
    fiter.b = RooRealVar("b","b",1,0.5,4)
    fiter.n = RooRealVar("n","n",1,40)
    fiter.a = RooRealVar("a","a",1,20)
    fiter.fapo1 = RooRealVar("fapo1","fapo1",0,1)
    fiter.sig1  = RooApollonios("Sigmodel1","Sigmodel1", fiter.mass, fiter.mean, fiter.sigma, fiter.b, fiter.a, fiter.n)
    fiter.sig2  = RooApollonios("Sigmodel2","Sigmodel2", fiter.mass, fiter.mean, fiter.sigma2, fiter.b, fiter.a, fiter.n)
    fiter.sig  = RooAddPdf("Sigmodel","Sigmodel", fiter.sig1,fiter.sig2,fiter.fapo1)
    return 1

def double_gaussian1peak(fiter):
    fiter.mean1 = RooRealVar("mean1","mean1",5250, 5400)#5168.)
    fiter.sigma1 = RooRealVar("sigma1","sigma1", 6.,20)#35.)    
    fiter.delta_s = RooRealVar("delta_s", "delta_s", 2., 35.)
    fiter.sigma2 = RooFormulaVar("sigma2","sigma2", "sigma1 + delta_s" ,RooArgList(fiter.sigma1,fiter.delta_s) )
    fiter.sigb11  = RooGaussian("SigmodelB11","SigmodelB11", fiter.mass, fiter.mean1, fiter.sigma1)
    fiter.sigb12  = RooGaussian("SigmodelB12","SigmodelB12", fiter.mass, fiter.mean1, fiter.sigma2)
    fiter.f1 = RooRealVar("f small res","f small res",0.5, 0., 1.)
    fiter.sig  = RooAddPdf("Sigmodel","Sigmodel", fiter.sigb11, fiter.sigb12, fiter.f1)
    
    return 1

def triple_gaussian1peak(fiter):
    fiter.mean1 = RooRealVar("mean1","mean1",5250, 5400)#5168.)
    fiter.sigma1 = RooRealVar("sigma1","sigma1", 6.,20)#35.)    
    fiter.delta_s = RooRealVar("delta_s", "delta_s", 2., 35.)
    fiter.delta_s2 = RooRealVar("delta_s2", "delta_s2", 2., 35.)
    fiter.sigma2 = RooFormulaVar("sigma2","sigma2", "sigma1 + delta_s" ,RooArgList(fiter.sigma1,fiter.delta_s) )
    fiter.sigma3 = RooFormulaVar("sigma3","sigma3", "sigma2 + delta_s2" ,RooArgList(fiter.sigma2,fiter.delta_s2) )
    fiter.sigb11  = RooGaussian("SigmodelB11","SigmodelB11", fiter.mass, fiter.mean1, fiter.sigma1)
    fiter.sigb12  = RooGaussian("SigmodelB12","SigmodelB12", fiter.mass, fiter.mean1, fiter.sigma2)
    fiter.sigb13  = RooGaussian("SigmodelB13","SigmodelB13", fiter.mass, fiter.mean1, fiter.sigma3)

    fiter.f1 = RooRealVar("f small res","f small res",0.5, 0., 1.)
    fiter.f2 = RooRealVar("f small res 2","f small res 2",0.5, 0., 1.)
    fiter.sig1  = RooAddPdf("Sigmodel1","Sigmodel1", fiter.sigb11, fiter.sigb12, fiter.f1)
    fiter.sig  = RooAddPdf("Sigmodel","Sigmodel", fiter.sig1, fiter.sigb13, fiter.f2)
    return 1


def BW_signal(fiter):
    fiter.mean = RooRealVar("mean","mean",892,800,1200)#5168.)
    fiter.sigma = RooRealVar("sigma","sigma", 50.,30,100)
    fiter.sig  = RooBreitWigner("Sigmodel","Sigmodel", fiter.mass, fiter.mean, fiter.sigma)
    return 1

def double_gaussian(fiter):
    fiter.mean1 = RooRealVar("mean1","mean1",5250, 5400)#5168.)
    fiter.sigma1 = RooRealVar("sigma1","sigma1", 6.,20)#35.)
    
    fiter.delta_s = RooRealVar("delta_s", "delta_s", 2., 35.)
    fiter.delta_m = RooRealVar("delta_m", "delta_m", 50., 120.)
    fiter.sigma2 = RooFormulaVar("sigma2","sigma2", "sigma1 + delta_s" ,RooArgList(fiter.sigma1,fiter.delta_s) )
    fiter.mean2 = RooFormulaVar("mean2","mean2", "mean1 + delta_m" ,RooArgList(fiter.mean1,fiter.delta_m) )
    fiter.sigb11  = RooGaussian("SigmodelB11","SigmodelB11", fiter.mass, fiter.mean1, fiter.sigma1)
    fiter.sigb12  = RooGaussian("SigmodelB12","SigmodelB12", fiter.mass, fiter.mean1, fiter.sigma2)
    fiter.sigb21  = RooGaussian("SigmodelB21","SigmodelB21", fiter.mass, fiter.mean2, fiter.sigma1)
    fiter.sigb22  = RooGaussian("SigmodelB22","SigmodelB22", fiter.mass, fiter.mean2, fiter.sigma2)
    fiter.f1 = RooRealVar("f small res","f small res",0.5, 0., 1.)
    fiter.sigB1  = RooAddPdf("SigmodelB1","SigmodelB1", fiter.sigb11, fiter.sigb12, fiter.f1)
    fiter.sigB2  = RooAddPdf("SigmodelB2","SigmodelB2", fiter.sigb21, fiter.sigb22, fiter.f1)
    fiter.fB2 = RooRealVar("fB2","fB2",0.5, 0., 1.)
    fiter.sig  = RooAddPdf("Sigmodel","Sigmodel", fiter.sigB2, fiter.sigB1, fiter.fB2)
    return 1
def CB_plus_gaussian(fiter):
    fiter.mean1 = RooRealVar("mean1","mean1",5250, 5400)#5168.)
    fiter.sigma1 = RooRealVar("sigma1","sigma1", 6.,20)#35.)
    fiter.n = RooRealVar("exponent", "exponent",1.)
    fiter.a1 = RooRealVar("transition1","transition1",2.5,1.,3.)
    
    fiter.delta_s = RooRealVar("delta_s", "delta_s", 2., 40.)
    fiter.delta_m = RooRealVar("delta_m", "delta_m", 50., 120.)
    fiter.sigma2 = RooFormulaVar("sigma2","sigma2", "sigma1 + delta_s" ,RooArgList(fiter.sigma1,fiter.delta_s) )
    fiter.mean2 = RooFormulaVar("mean2","mean2", "mean1 + delta_m" ,RooArgList(fiter.mean1,fiter.delta_m) )
    fiter.sigb11  = RooCBShape("SigmodelB11","SigmodelB11", fiter.mass, fiter.mean1, fiter.sigma1,fiter.a1,fiter.n)
    fiter.sigb12  = RooGaussian("SigmodelB12","SigmodelB12", fiter.mass, fiter.mean1, fiter.sigma2)
    fiter.sigb21  = RooCBShape("SigmodelB21","SigmodelB21", fiter.mass, fiter.mean2, fiter.sigma1,fiter.a1,fiter.n)
    fiter.sigb22  = RooGaussian("SigmodelB22","SigmodelB22", fiter.mass, fiter.mean2, fiter.sigma2)
    fiter.f1 = RooRealVar("f small res","f small res",0.5, 0., 1.)
    fiter.sigB1  = RooAddPdf("SigmodelB1","SigmodelB1", fiter.sigb11, fiter.sigb12, fiter.f1)
    fiter.sigB2  = RooAddPdf("SigmodelB2","SigmodelB2", fiter.sigb21, fiter.sigb22, fiter.f1)
    fiter.fB2 = RooRealVar("fB2","fB2",0.5, 0., 1.)
    fiter.sig  = RooAddPdf("Sigmodel","Sigmodel", fiter.sigB2, fiter.sigB1, fiter.fB2)
    return 1


def CB_signal(fiter):
    fiter.mean = RooRealVar("mean","mean",5050, 5300)#5168.)
    fiter.sigma = RooRealVar("sigma","sigma", 16.,46)#35.)
    fiter.n = RooRealVar("exponent", "exponent",1.)
    fiter.a = RooRealVar("transition","transition",1.9)
    fiter.sig  = RooCBShape("Sigmodel","Sigmodel", fiter.mass, fiter.mean, fiter.sigma, fiter.a, fiter.n)
    return 1

def InvCB_signal(fiter):
    fiter.mean = RooRealVar("mean","mean",5200, 5400)#5168.)
    fiter.sigma = RooRealVar("sigma","sigma", 16.,46)#35.)
    fiter.n = RooRealVar("exponent", "exponent",1.)
    fiter.a = RooRealVar("transition","transition",-0.5,-3)
    fiter.sig  = RooCBShape("Sigmodel","Sigmodel", fiter.mass, fiter.mean, fiter.sigma, fiter.a, fiter.n)
    return 1

def bkg_with_Pshoulder(fiter):
    ###bkg pdf
    fiter.indx = RooRealVar("indx", "indx", 0., -10., 10.)
    fiter.linbkg = RooExponential("expBkg", "Exponential background pdf", fiter.mass, fiter.indx)
    #fiter.linbkg = RooPolynomial("expBkg", "Exponential background pdf", fiter.mass)
    
    
    ###Shoulder
    fiter.sh_mean = RooRealVar("sh_mean", "sh_mean", 5107, 4700.,5150.)
    fiter.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 36., 30.,50.)
    fiter.sh_dtrans = RooRealVar("sh_dtrans", "sh_dtrans", 2., 0.5,30.)
    fiter.sh_trans = RooFormulaVar("sh_trans", "sh_trans", "sh_mean - sh_dtrans", RooArgList(fiter.sh_mean,fiter.sh_dtrans))

#    fiter.sh_trans = RooRealVar("sh_trans", "sh_trans", 5105., 5050.,5150.)
    #fiter.sh_trans.setConstant(kTRUE)
    fiter.sh_sigma.setConstant(kTRUE)
    #fiter.sh_mean.setConstant(kTRUE)
    
    fiter.shoulder = RooExpAndGauss("shoulder", "shoulder pdf", fiter.mass,fiter.sh_mean, fiter.sh_sigma, fiter.sh_trans)
  
    fiter.fsh = RooRealVar("fh", "shoulder fraction in background", 0.5,0.,1.)
    fiter.bkg = RooAddPdf("bkg", "background pdf", fiter.shoulder, fiter.linbkg, fiter.fsh)

    return 1
def bujpsik_bkg(fiter):
    ###bkg pdf
    fiter.indx = RooRealVar("indx", "indx", 0., -10., 10.)
    fiter.linbkg = RooExponential("expBkg", "Exponential background pdf", fiter.mass, fiter.indx)
    #fiter.linbkg = RooPolynomial("expBkg", "Exponential background pdf", fiter.mass)
    
    
    ###Shoulder
    fiter.sh_mean = RooRealVar("sh_mean", "sh_mean", 5107, 4700.,5150.)
    if fiter.var =="Bmass_JC":
        fiter.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 14., 10.,18.)
        fiter.sh_dtrans = RooRealVar("sh_dtrans", "sh_dtrans", 2., 0.3,0.6)
    else:
        fiter.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 16., 8.,50.)
        fiter.sh_dtrans = RooRealVar("sh_dtrans", "sh_dtrans", 2., 0.5,30.)
    fiter.sh_trans = RooFormulaVar("sh_trans", "sh_trans", "sh_mean - sh_dtrans", RooArgList(fiter.sh_mean,fiter.sh_dtrans))
    #fiter.sh_sigma.setConstant(kTRUE)
    fiter.shoulder = RooExpAndGauss("shoulder", "shoulder pdf", fiter.mass,fiter.sh_mean, fiter.sh_sigma, fiter.sh_trans)

    fiter.pi_mean = RooFormulaVar("pi_mean","pi_mean","mean1 + 50", RooArgList(fiter.mean1))
    fiter.pi_sigma = RooRealVar("pi_sigma","pi_sigma", 18,13,23)
    fiter.pi_n = RooRealVar("pi_exponent", "pi_exponent",4.,2.5,5.5)
    fiter.pi_a = RooRealVar("pi_transition","pi_transition",-0.43,-0.6, -0.3)
    fiter.pi_bkg  = RooCBShape("pi model","pi model", fiter.mass, fiter.pi_mean, fiter.pi_sigma, fiter.pi_a, fiter.pi_n)
    fiter.f_pi = RooRealVar("fpi", "parameter for pi bkg", 0.5,0.,1.)
    
    fiter.linbkg0 = RooAddPdf("bkg with pi", "bkg with pi", fiter.pi_bkg, fiter.linbkg, fiter.f_pi)
    fiter.fsh = RooRealVar("fh", "shoulder fraction in background", 0.5,0.,1.)
    fiter.bkg = RooAddPdf("bkg", "background pdf", fiter.shoulder, fiter.linbkg0, fiter.fsh)

    return 1


def bdjpsikstar_full_bkg(fiter):
    ###bkg pdf
    fiter.indx = RooRealVar("indx", "indx", 0., -10., 10.)
    fiter.linbkg = RooExponential("expBkg", "Exponential background pdf", fiter.mass, fiter.indx)
    #fiter.linbkg = RooPolynomial("expBkg", "Exponential background pdf", fiter.mass)
    
    
    ###Shoulder
    fiter.sh_mean = RooRealVar("sh_mean", "sh_mean", 5107, 5000.,5150.)
    if fiter.var =="Bmass_JC":
        fiter.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 14., 10.,18.)
        fiter.sh_dtrans = RooRealVar("sh_dtrans", "sh_dtrans", .4, 0.3,2.)
        fiter.sh_dtrans2 = RooRealVar("sh_dtrans2", "sh_dtrans2", .4, 0.3,2.)
        fiter.sh_sigma2 = RooRealVar("sh_sigma2", "sh_sigma2", 14, 10.,18.)
    else:
        fiter.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 16., 8.,50.)
        fiter.sh_dtrans = RooRealVar("sh_dtrans", "sh_dtrans", 2., 0.5,30.)
        fiter.sh_dtrans2 = RooRealVar("sh_dtrans2", "sh_dtrans2", 2., 0.5,30.)
        fiter.sh_sigma2 = RooRealVar("sh_sigma2", "sh_sigma2", 38, 30.,50.)
        
    fiter.sh_trans = RooFormulaVar("sh_trans", "sh_trans", "sh_mean - sh_dtrans", RooArgList(fiter.sh_mean,fiter.sh_dtrans))
    fiter.sh_mean2 = RooRealVar("sh_mean2", "sh_mean2", 5472.57, 5300.,5700.)
    fiter.sh_trans2 = RooFormulaVar("sh_trans2", "sh_trans2", "sh_mean2 + sh_dtrans2", RooArgList(fiter.sh_mean2,fiter.sh_dtrans2))
   
  
    fiter.shoulder = RooExpAndGauss("shoulder1", "shoulde1r pdf", fiter.mass,fiter.sh_mean, fiter.sh_sigma, fiter.sh_trans)
    fiter.shoulder2 = RooExpAndGaussInv("shoulder2", "shoulder pdf", fiter.mass,fiter.sh_mean2, fiter.sh_sigma2, fiter.sh_trans2)
  
    fiter.fsh = RooRealVar("fh", "shoulder fraction in background", 0.5,0.,1.)
    fiter.fsh2 = RooRealVar("fh2", "shoulder2 fraction in background", 0.5,0.,1.)

    fiter.phi_mean = RooRealVar("phi_mean1","phi_mean1",5.29164e+03)#5250, 5320)#5168.)
    fiter.phi_d1= RooRealVar("phi_d1","phi_d1", 9.09101e+01)#, 20., 120.)
    fiter.phi_mean2 = RooFormulaVar("phi_mean2","phi_mean2", "phi_mean1 + phi_d1" ,RooArgList(fiter.phi_mean,fiter.phi_d1) )
    fiter.phi_sigma = RooRealVar("phi_sigma","phi_sigma",1.56679e+01)# 20., 12.,40.)#35.)
    
    fiter.phi_n = RooRealVar("phi_exponent", "phi_exponent",1.)#,  0., 12 )
    #fiter.n2 = RooRealVar("exponent2", "exponent2",  5.1 .1, 12)
    
    #fiter.a2 = RooRealVar("transition2","transition2", -1.21, -3, -0.5) ## Transition point, in sigmas
    fiter.phi_a = RooRealVar("phi_transition","phi_transition",9.82982e-01)#, 0.5, 3) ## Transition point, in sigmas
    
    fiter.phi_Sd = RooCBShape("phi Bd peak","phi Bd peak", fiter.mass, fiter.phi_mean, fiter.phi_sigma, fiter.phi_a, fiter.phi_n)
    fiter.phi_Ss = RooCBShape("phi Bs peak","phi Bs peak", fiter.mass, fiter.phi_mean2, fiter.phi_sigma, fiter.phi_a, fiter.phi_n)
   
    fiter.phi_f1 = RooRealVar("phi_f1fraction","phi_f1fraction",9.38669e-01)#0.5, 0., 1.)
    fiter.f_phi = RooRealVar("f_phi","f_phi",3e-02, 0., .1) 
    fiter.phi_bkg  = RooAddPdf("phi","phi", fiter.phi_Sd, fiter.phi_Ss, fiter.phi_f1)
    
    fiter.bkg0 = RooAddPdf("shoulder", "shoulder pdf", fiter.shoulder2, fiter.shoulder, fiter.fsh2)
    fiter.bkg1 = RooAddPdf("comb+phi", "comb+phi", fiter.phi_bkg, fiter.linbkg, fiter.f_phi)

    
    fiter.bkg = RooAddPdf("bkg", "background pdf", fiter.bkg0, fiter.bkg1, fiter.fsh)
    return 1


def bkg_with_RooPhysBkg(fiter):
    ###bkg pdf
    fiter.indx = RooRealVar("indx", "indx", 0., -10., 10.)
    fiter.linbkg = RooExponential("expBkg", "Exponential background pdf", fiter.mass, fiter.indx)
    #fiter.linbkg = RooPolynomial("expBkg", "Exponential background pdf", fiter.mass)
    
    
    ###Shoulder
    fiter.sh_mean = RooRealVar("sh_mean", "sh_mean", 5100, 4950.,5370.)
    fiter.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 26., 20.,50.)
    fiter.sh_c = RooRealVar("sh_c", "sh_c", 0.005, 0.,0.02)
    #fiter.sh_trans.setConstant(kTRUE)
    #fiter.sh_sigma.setConstant(kTRUE)
    #fiter.sh_mean.setConstant(kTRUE)
    
    fiter.shoulder = RooPhysBkg("shoulder", "shoulder pdf", fiter.mass,fiter.sh_mean, fiter.sh_c, fiter.sh_sigma)
  
    fiter.fsh = RooRealVar("fh", "shoulder fraction in background", 0.5,0.,1.)
    fiter.bkg = RooAddPdf("bkg", "background pdf", fiter.shoulder, fiter.linbkg, fiter.fsh)

    return 1

def bkg_with_gauss_shoulder(fiter,lambda_b = False):
    """ models the bkg as an exponential + a shoulder on the left described as a wide Gaussian. Optionally adds a Lambda_b component
    """

    
    ###bkg pdf
    fiter.bkg_indx = RooRealVar("indx", "indx", -0.001, -0.01, 0.)
    fiter.linbkg = RooExponential("expBkg", "Exponential background pdf", fiter.mass, fiter.bkg_indx)
        
    if lambda_b:
        fiter.meanL = RooRealVar("lambdaPeak","lambdaPeak", 5500.,5400.,5600.)
        fiter.sigmaL = RooRealVar("sigmaL","sigmaL", 30., 20., 40.)
        fiter.lambda_b = RooGaussian("lambda","lambda",fiter.mass,fiter.meanL,fiter.sigmaL)
        fiter.fLambda= RooRealVar("fLambda","fLambda", 0.5,0.,1.)
    
    ###Shoulder
    fiter.sh_mean = RooRealVar("sh_mean", "sh_mean", 4729., 4200.,5000.)
    fiter.sh_sigma = RooRealVar("sh_sigma", "sh_sigma", 294., 100.,400.)
       
    #fiter.sh_trans.setConstant(kTRUE)
    fiter.sh_sigma.setConstant(kTRUE)
    fiter.sh_mean.setConstant(kTRUE)
       
    #fiter.shoulder = RooExpAndGauss("shoulder", "shoulder pdf", fiter.mass,fiter.sh_mean, fiter.sh_sigma, fiter.sh_trans)
    fiter.shoulder = RooGaussian("shoulder","shoulder pdf", fiter.mass, fiter.sh_mean, fiter.sh_sigma)
    #### model
   
    fiter.fsh = RooRealVar("fh", "shoulder fraction in background", 0.5,0.,1.)
    fiter.bkg1 = RooAddPdf("bkg1", "background pdf1", fiter.shoulder, fiter.linbkg, fiter.fsh)
    if lambda_b: fiter.bkg = RooAddPdf("bkg", "background pdf", fiter.lambda_b, fiter.bkg1, fiter.fLambda)
    else:    fiter.bkg = fiter.bkg1 ## RooAddPdf("bkg", "background pdf", self.lambda_b, self.bkg1, self.fLambda)
    return 1

def bkg_with_gauss_shoulder_and_L(fiter):
    return bkg_with_gauss_shoulder(fiter, True)


def two_double_cb(fiter):
    """ models the signal as two peaks, each peak being a two-sided crystalball
    """
    
    fiter.mean1 = RooRealVar("mean1","mean1",5050, 5600)#5168.)
    fiter.d1= RooRealVar("d1","d1", 72.4)#, 20., 120.)
    fiter.mean2 = RooFormulaVar("mean2","mean2", "mean1 + d1" ,RooArgList(fiter.mean1,fiter.d1) )
    fiter.sigma = RooRealVar("sigma","sigma", 20.,50)#35.)
    
    fiter.n = RooRealVar("exponent", "exponent",1.)#,  0., 12 )
    fiter.n2 = RooRealVar("exponent2", "exponent2",  9.28 )#,.1, 12)
    
    fiter.a2 = RooRealVar("transition2","transition2", -1.19)#, -3, -0.5) ## Transition point, in sigmas
    fiter.a3 = RooRealVar("transition3","transition3",1.38)#, 0.5, 3) ## Transition point, in sigmas
    
    fiter.MSu1 = RooCBShape("MSu","MSu", fiter.mass, fiter.mean1, fiter.sigma, fiter.a2, fiter.n2)
    fiter.MSd1 = RooCBShape("MSd","MSd", fiter.mass, fiter.mean1, fiter.sigma, fiter.a3, fiter.n)
    fiter.MSu2 = RooCBShape("MSu2","MSu2", fiter.mass, fiter.mean2, fiter.sigma, fiter.a2, fiter.n2)
    fiter.MSd2 = RooCBShape("MSd2","MSd2", fiter.mass, fiter.mean2, fiter.sigma, fiter.a3, fiter.n)
    
    fiter.f05 = RooRealVar("0.55", "0.5", 0.5) ### This is here just to create double crystalballs (I think)
    fiter.MS1 = RooAddPdf("MS1","MS1",fiter.MSu1,fiter.MSd1,fiter.f05)
    fiter.MS2 = RooAddPdf("MS2","MS2",fiter.MSu2,fiter.MSd2,fiter.f05)
    fiter.f1 = RooRealVar("fraction","fraction",0.0678)#, 0., 1.)
    
    
    fiter.sig  = RooAddPdf("Sigmodel","Sigmodel", fiter.MS1, fiter.MS2, fiter.f1)

    return 1

def two_cb(fiter):
    """ models the signal as two peaks, each peak being a two-sided crystalball
    """
    
    fiter.mean = RooRealVar("mean1","mean1",5250, 5320)#5168.)
    fiter.d1= RooRealVar("d1","d1", 100., 20., 120.)
    fiter.mean2 = RooFormulaVar("mean2","mean2", "mean1 + d1" ,RooArgList(fiter.mean,fiter.d1) )
    fiter.sigma = RooRealVar("sigma","sigma", 20., 12.,40.)#35.)
    
    fiter.n = RooRealVar("exponent", "exponent",1.)#,  0., 12 )
    #fiter.n2 = RooRealVar("exponent2", "exponent2",  5.1 .1, 12)
    
    #fiter.a2 = RooRealVar("transition2","transition2", -1.21, -3, -0.5) ## Transition point, in sigmas
    fiter.a = RooRealVar("transition","transition",2.)#, 0.5, 3) ## Transition point, in sigmas
    
    fiter.Sd = RooCBShape("Bd peak","Bd peak", fiter.mass, fiter.mean, fiter.sigma, fiter.a, fiter.n)
    fiter.Ss = RooCBShape("Bs peak","Bs peak", fiter.mass, fiter.mean2, fiter.sigma, fiter.a, fiter.n)
   
    fiter.f1 = RooRealVar("fraction","fraction",0.5, 0., 1.) 
    fiter.sig  = RooAddPdf("Sigmodel","Sigmodel", fiter.Sd, fiter.Ss, fiter.f1)

    return 1

## def three_cb(fiter, lab = "S"):
##     """ models the signal as two peaks, each peak being a two-sided crystalball
##     """
    
##     fiter.cb3mean = RooRealVar("cb3mean1","cb3mean1",5250, 5320)#5168.)
##     fiter.cb3d1= RooRealVar("cb3d1","cb3d1", 100., 20., 120.)
##     fiter.cb3d1= RooRealVar("cb3d2","cb3d2", 100., 20., 120.)
##     fiter.cb3mean2 = RooFormulaVar("cb3mean2","cb3mean2", "cb3mean2 + cb3d2" ,RooArgList(fiter.cb3mean,fiter.d1) )
##     fiter.cb3sigma = RooRealVar("cb3sigma","cb3sigma", 20., 12.,40.)#35.)
    
##     fiter.cb3n = RooRealVar("cb3exponent", "cb3exponent",1.)#,  0., 12 )
##     #fiter.n2 = RooRealVar("exponent2", "exponent2",  5.1 .1, 12)
    
##     #fiter.a2 = RooRealVar("transition2","transition2", -1.21, -3, -0.5) ## Transition point, in cb3sigmas
##     fiter.cb3a = RooRealVar("cb3transition","cb3transition",2., 0.5, 3) ## Transition point, in cb3sigmas
    
##     fiter.cb3S1 = RooCBShape("cb3 peak1","cb3 peak 1", fiter.mass, fiter.cb3mean, fiter.cb3sigma, fiter.cb3a, fiter.cb3n)
##     fiter.cb3S2 = RooCBShape("cb3 peak2","cb3 peak 2", fiter.mass, fiter.cb3mean2, fiter.cb3sigma, fiter.cb3a, fiter.cb3n)
##     fiter.cb3S3 = RooCBShape("cb3 peak3","cb3 peak 3", fiter.mass, fiter.cb3mean3, fiter.cb3sigma, fiter.cb3a, fiter.cb3n)
   
##     fiter.cb3f1 = RooRealVar("cb3f1 fraction","cb3f1 fraction",0.5, 0., 1.) 
##     if lab = "S" :fiter.sig  = RooAddPdf("Sigmodel","Sigmodel", fiter.Sd, fiter.Ss, fiter.f1)
##     else: fiter.bkg  = RooAddPdf("cb3bkgmodel","cb3bkgmodel", fiter.Sd, fiter.Ss, fiter.f1)

##     return 1

def ipatia_signal(fiter):
    fiter.mean = RooRealVar("mean","mean",5365,5370.)
    fiter.sigma = RooRealVar("sigma","sigma", 6.,15)#35.)
    fiter.l = RooRealVar("l","l",-2.5,-10,-1)
    fiter.zeta = RooRealVar("zeta","zeta",0,2)
    fiter.beta = RooRealVar("beta","beta",0)#-0.01,0.01)

    fiter.n = RooRealVar("n","n",0.8,40)
    fiter.a = RooRealVar("a","a",1,40)
    fiter.n2 = RooRealVar("n2","n2",0.9,40)
    fiter.a2 = RooRealVar("a2","a2",1, 4)

    fiter.sig  = RooIpatia2("Sigmodel","Sigmodel", fiter.mass, fiter.l, fiter.zeta, fiter.beta, fiter.sigma, fiter.mean, fiter.a, fiter.n, fiter.a2,fiter.n2)
    return 1


def sig_with_erf(fiter):
    """ the parameterization of Justine
    """
    
    fiter.mean = RooRealVar("mean","mean",5250, 5100, 5400,"MeV/c^{2}");
    fiter.sigma1 = RooRealVar("#sigma_{1}","#sigma_{1}", 97, 10, 200,"MeV/c^{2}");
    fiter.sigma2 = RooRealVar("#sigma_{2}","#sigma_{2}",34.32, 10, 150,"MeV/c^{2}");
    fiter.fgauss = RooRealVar("f_{G}","f_{G}",.5,0.,1.)#0.1202,0,1);
    fiter.ftail = RooRealVar("f_{E}","f_{E}",.5,0.,1.)# 0.2142,0,1);
    fiter.rad_slope = RooRealVar("rad_s","rad_s",0.007364,0,1,"c^{2}/MeV");

    ##### To fix some parameters
    #5  f_{E}        1.26737e-01   1.21679e-01   6.24582e-04  -8.42826e-01
    #6  f_{G}        3.14101e-01   1.07644e-01   4.05959e-04  -3.80945e-01
    #10  rad_s        7.69684e-03   2.30388e-02   5.40037e-05  -1.39511e+00

    #fiter.fgauss.setVal(0.31)
    #fiter.sigma1.setVal(120)
    #fiter.sigma1.setConstant(kTRUE)
    #fiter.fgauss.setConstant(kTRUE)
    #fiter.ftail.setVal(0.13)
    #fiter.ftail.setConstant(kTRUE)
    #fiter.rad_slope.setConstant(kTRUE)

    ### end fixing parameters
  
  
    fiter.gaus1 = RooGaussian("gaus1","gaus1",fiter.mass,fiter.mean,fiter.sigma1);
    fiter.gaus2 = RooGaussian("gaus2","gaus2",fiter.mass,fiter.mean,fiter.sigma2);
  
    fiter.rtail1 = RooRadiativeTail("rtail1","rtail1",fiter.mass,fiter.rad_slope,fiter.mean,fiter.sigma1);
    fiter.rtail2 = RooRadiativeTail("rtail2","rtail2",fiter.mass,fiter.rad_slope,fiter.mean,fiter.sigma2);
  
    fiter.dgaus = RooAddPdf("dgaus","dgaus",fiter.gaus1,fiter.gaus2,fiter.fgauss);
    fiter.dtail = RooAddPdf("dtail","dtail",fiter.rtail1,fiter.rtail2, fiter.fgauss);
    fiter.sig = RooAddPdf("Sigmodel","Sigmodel", fiter.dtail,fiter.dgaus, fiter.ftail)
  
  
    return 1


class FiterBasis:
    def __init__(self,tree, var,cuts="", shorTime = True, weight_var=0,sigf = gaussian_signal , bkgf = exp_bkg, fit_in_init = 1):
        """ROOT TTree,, option 'ShorTime' does the fit to be
done in histogram instead of NTuple
        """
        self.var = var
        print cuts
        if cuts:
            f = TFile("/tmp/borrame_ho.root","recreate")
            t = tree.CopyTree(cuts)
        else: t = tree
        self.mass = RooRealVar(var,var,  t.GetMinimum(var), t.GetMaximum(var))
                
        ### fit
        if weight_var:
            self.w = RooRealVar(weight_var, weight_var,  t.GetMinimum(weight_var), t.GetMaximum(weight_var))
            self.data = RooDataSet("data","data", t, RooArgSet(self.mass, self.w),"100000000000000 > 0", weight_var) #RooFit.WeightVar(self.w))
            #self.data.setWeightVar(self.w)

        else: self.data = RooDataSet("data","data", t, RooArgSet(self.mass))
        #self.data = RooDataSet("data","data", t, RooArgSet(self.mass))

        sigf(self)
        bkgf(self)
        

        self.nsig = RooRealVar("nsig", "nsig", 0.5*t.GetEntries(),0.,t.GetEntries())
        self.nbkg = RooRealVar("nbkg", "nbkg", 0.5*t.GetEntries(),0.,t.GetEntries())
        
        self.model = RooAddPdf("model","model", RooArgList(self.sig, self.bkg), RooArgList(self.nsig, self.nbkg))
        if cuts: f.Close()
        self.short = shorTime
        if fit_in_init: self.result = self.fit()
        self.tree = t
        
    def fit(self, fixing = {}, cpus =1, minos = kTRUE):
        for key in fixing.keys():
            getattr(self, key).setVal(fixing[key])
            getattr(self, key).setConstant(kTRUE)
        N = self.nsig.getVal()+self.nbkg.getVal()
       
        if N < 10000 or (not self.short):
            print "Fitting to NTuple"
            return self.model.fitTo(self.data,RooFit.Minos(minos),RooFit.Verbose(False) ,RooFit.Save(),RooFit.NumCPU(cpus), RooFit.Offset(kTRUE))
        else:
            print "Fitting HISTOGRAM"
            h = RooDataHist(self.var,self.var,RooArgSet(self.mass), self.data)
            print h
            return self.model.fitTo(h,RooFit.Minos(minos),RooFit.Verbose(False),RooFit.Save(), RooFit.NumCPU(cpus), RooFit.Offset(kTRUE))
        
    
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
       
    def plot(self, bins = 100, setLog = False):
        """Plots the data and the models
        """
	
	if setLog: gPad.SetLogy()	
	
	fr = self.mass.frame()
        self.data.plotOn(fr, RooFit.Binning(bins))
        self.model.plotOn(fr)
        self.model.plotOn(fr,RooFit.Components("bkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
        self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
        self.model.plotOn(fr,RooFit.Components("lambda"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
        
        self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))

	#self.model.paramOn(fr)
	
	fr.Draw()
        return(fr)

    #Previous plot function:
    #def plot(self, bins = 100):
    #    """Plots the data and the models
    #    """
    #    fr = self.mass.frame()
    #    self.data.plotOn(fr, RooFit.Binning(bins))
    #    self.model.plotOn(fr)
    #    self.model.plotOn(fr,RooFit.Components("bkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
    #    self.model.plotOn(fr,RooFit.Components("shoulder"), RooFit.LineStyle(kDashed), RooFit.LineColor(kCyan))
    #    self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
    #    self.model.plotOn(fr,RooFit.Components("lambda"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
    #    
    #    self.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
    #    
    #    fr.Draw()
    #    return(fr)
