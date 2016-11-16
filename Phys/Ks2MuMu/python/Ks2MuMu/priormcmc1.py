from ROOT import *

alphaval = 1

# 1  beta         1.97463e+01   2.83176e-05                            
#   2  mean         7.18127e+01   8.09778e-05                            
#   3  theta       -6.77783e+01   3.01489e-04                            
  
thetaval =   -6.77783e+01
betaval =  1.97463e+01#7.18127e+01
aval = 7.18127e+01


theta = RooRealVar("theta","theta",thetaval)#1000) ## kind of sigma
alpha = RooRealVar("alpha","alpha",alphaval)#, .1, 10) alpha = 1 is Fisher-Tippet distrib.
offset = RooRealVar("mean","mean",aval)
beta = RooRealVar("beta", "beta", betaval)
