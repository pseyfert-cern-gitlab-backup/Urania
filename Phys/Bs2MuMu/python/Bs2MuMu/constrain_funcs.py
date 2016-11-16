from ROOT import *
print RooFit
S_RANGE = 3.

def createConst(m,s1, name, signed = 0):
    if s1 :
        if not signed:
            x = RooRealVar(name,name, m, m-S_RANGE*s1,m+S_RANGE*s1)
            _mean = RooRealVar(name+"_mean",name+"_mean", m)
            _mean.setConstant(True)
            _sigma = RooRealVar(name+"_sigma",name+"_sigma", s1)
            _sigma.setConstant(True)
        if signed == 1:
            x = RooRealVar(name,name, m, max(0, m-S_RANGE*s1),m+S_RANGE*s1)
            _mean = RooRealVar(name+"_mean",name+"_mean", m,max(0, m-S_RANGE*s1),m+S_RANGE*s1)
            _mean.setConstant(True)
            _sigma = RooRealVar(name+"_sigma",name+"_sigma", s1)
            _sigma.setConstant(True)
        if signed == -1 :
            x = RooRealVar(name,name, m, m-S_RANGE*s1,min( m+S_RANGE*s1,0.))
            _mean = RooRealVar(name+"_mean",name+"_mean", m, m-S_RANGE*s1,min( m+S_RANGE*s1,0.))
            _mean.setConstant(True)
            _sigma = RooRealVar(name+"_sigma",name+"_sigma", s1)
            _sigma.setConstant(True)
        x_cons = RooGaussian(name + "_const",name + "_const",x, _mean, _sigma)
    else:
        x = RooRealVar(name,name, m)
        _mean = RooRealVar(name+"_mean",name+"_mean", m)
        _mean.setConstant(True)
        _sigma = RooRealVar(name+"_sigma",name+"_sigma", 400)
        _sigma.setConstant(True)
        x_cons = RooGaussian(name + "_const",name + "_const",x,_mean, _sigma)
    return x,_mean,_sigma,  x_cons

def createStableConst(m,s1, name, signed = 0):
    mymax = m+S_RANGE*s1
    mymin = m-S_RANGE*s1
    if abs(mymax) > 2e3*s1 :
        mymax = mymax*0.999

    if not signed: x = RooRealVar(name,name, m, mymin,mymax)
    if signed == 1:  x = RooRealVar(name,name, m, max(0, mymin),mymax)
    if signed == -1 :  x = RooRealVar(name,name, m, mymin,min( mymax,0.))
    x_cons = RooGaussian(name + "_const",name + "_const",x,RooFit.RooConst(m),RooFit.RooConst(s1))
    
    return x, x_cons


def createBifurConst(m,s1,s2, name, signed = 0):
    if s1 == 0 :return createConst(m,s2,name)
    s1 = abs(s1)
    s2 = abs(s2)
    if not signed: x = RooRealVar(name,name, m, m-S_RANGE*s1,m+S_RANGE*s2)
    if signed == 1:  x = RooRealVar(name,name, m, max(0, m-S_RANGE*s1),m+S_RANGE*s2)
    if signed == -1 :  x = RooRealVar(name,name, m, m-S_RANGE*s1,min( m+S_RANGE*s2,0.))
    #x = RooRealVar(name,name, m,m-S_RANGE*s1,m+S_RANGE*s2)
    x_cons = RooBifurGauss(name + "_const",name + "_const",x,RooFit.RooConst(m),RooFit.RooConst(s1),RooFit.RooConst(s2))
    return x, x_cons

def linkToConst(m, s, x, m_old,s_old, name2):
    yname = x.GetName() + name2

    x0 = m_old
    x1 = str(x0 + s_old)
    x0 = str(x0)
    y0 = str(m)
    y1 = str(m + s)
    
    y = RooFormulaVar(yname, yname, y0 + " + (" + x.GetName() + "-" + x0 +")*(" + y1 + "- " + y0 + ")/("+ x1 + "- " + x0 +")", RooArgList(x))
    return y
