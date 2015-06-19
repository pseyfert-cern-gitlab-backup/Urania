from ROOT import *

mass = RooRealVar("mass","mass", 633,1900)
c = RooRealVar("c","c",-3,3)


mass_m = [813,896,961,1079,1444]
mass_min = [633,856,936,1000,1200]
mass_max = [856,936,1000,1200,1897]

c1 = [ -0.491,-0.488,-0.426 , -0.392 , -0.149]
sc1 = [ 0.035, 0.014,0.033,0.052,0.087]

c2 =  [-0.700,-0.642, -0.632,-0.624, -0.26]
sc2 = [0.056,0.022,0.048,0.022,0.12 ]

c3 = [ -0.42,-0.331 ,-0.33 ,-0.39 ,-0.23 ]
sc3 = [ 0.15,0.045, 0.11, 0.15, 0.29]

c4 = [ 0.26,0.092,0.021, -0.059 , -0.40]
sc4= [ 0.061, 0.023, 0.052, 0.067, 0.12]



y = [0.,0.,2.9e-03, 14e-03, 0.260]
sy_u = [1.e-03, 1.6e-04, 3.8e-03, 7.3e-03, 0.033]
sy_l = [0.,0.,2.7e-03,6.2e-03, 0.033 ]

cT = [-0.145 ,-0.1783 , -0.220 ,-0.202 , -0.241 ]
scT = [0.020,0.0075, 0.017,0.022,0.034 ]

zeros = 5*[0.]

def do(c_m,sc_u, sc_l):
    d = RooDataSet("data","data",RooArgSet(mass,c),RooFit.StoreAsymError(RooArgSet(mass,c)))
    for i in range(len(mass_m)):
        mass.setVal(mass_m[i])
        mass.setAsymError(mass_min[i] - mass_m[i], mass_max[i] - mass_m[i])
    
        c.setVal(c_m[i])
        c.setAsymError(-1*sc_l[i], sc_u[i])
        d.add(RooArgSet(mass,c))
    fr = mass.frame()
    d.plotOnXY(fr,RooFit.YVar(c))
    return d, fr

#d, fr = do(y,sy_u,sy_l)
d, fr = do(c4,sc4,sc4)
k0 = RooRealVar("k0","k0",-1,0)
k1 = RooRealVar("k1","k1", 0,300)
k2 = RooRealVar("k2","k2",-1e-02,0)
k3 = RooRealVar("k3","k3",800,2000)
#k5 = RooRealVar("k5","k5",-1,0)

a0 = RooRealVar("a0","a0",0,30)
a1 = RooRealVar("a1","a1", -0.02,0)
a2 = RooRealVar("a2","a2",0,1e-06)


func = RooFormulaVar("f","f", "a0 + a1*mass + a2*mass*mass",RooArgList(mass,a0,a1,a2))
#func = RooFormulaVar("f","f", "k0*(1-1./(1.+k1*exp(k2*(mass-k3))))",RooArgList(mass,k0,k1,k2,k3))#,k5))
#func = RooFormulaVar("f","f", "k0/(1.+k1*exp(k2*(mass-k3)))",RooArgList(mass,k0,k1,k2,k3))#,k5))
func.chi2FitTo(d,RooFit.YVar(c),RooFit.Minos(kTRUE))#, RooFit.Integrate(kTRUE))
#d, fr = do(c4,sc4,sc4)
#www = []
#for i in range(5): www.append(c2[i]+c4[i])
#d, fr = do(www,sc2,sc2)
func.plotOn(fr)
fr.Draw()
