from ROOT import *
print RooFit

def createConst(m,s1, name, signed = 0):
    if s1 :
        if not signed: x = RooRealVar(name,name, m, m-10*s1,m+10*s1)
        if signed == 1:  x = RooRealVar(name,name, m, max(0, m-10*s1),m+10*s1)
        if signed == -1 :  x = RooRealVar(name,name, m, m-10*s1,min( m+10*s1,0.))
        x_cons = RooGaussian(name + "_const",name + "_const",x,RooFit.RooConst(m),RooFit.RooConst(s1))
    else:
        x = RooRealVar(name,name, m)#,m-10*s1,m+10*s1)
        x_cons = RooGaussian(name + "_const",name + "_const",x,RooFit.RooConst(m),RooFit.RooConst(400))
    return x, x_cons

def createBifurConst(m,s1,s2, name, signed = 0):
    if s1 == 0 :return createConst(m,s2,name)
    s1 = abs(s1)
    s2 = abs(s2)
    if not signed: x = RooRealVar(name,name, m, m-10*s1,m+10*s2)
    if signed == 1:  x = RooRealVar(name,name, m, max(0, m-10*s1),m+10*s2)
    if signed == -1 :  x = RooRealVar(name,name, m, m-10*s1,min( m+10*s2,0.))
    #x = RooRealVar(name,name, m,m-5*s1,m+5*s2)
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
