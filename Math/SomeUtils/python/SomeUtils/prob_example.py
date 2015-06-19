from ROOT import *
from probTool import *

####
# Combining  a measurement of "x", with central value "m" and errors "s1" "s2", with a gaussian "sy" systematic
x = RooRealVar("x","x",-100,100)
y = RooRealVar("y","y",-6,6)

meanx = RooRealVar("m","m",5)
meany = RooRealVar("my","my",1)

s1 = RooRealVar("s1","s1",5)
s2 = RooRealVar("s2","s2",5)
sy = RooRealVar("sy","sy",0.1/meanx.getVal())

#model = RooGenericPdf("Gb","exp( -0.5 * (1/(2*(s1/m+s2/m)) *((s2/m-s1/m) + sqrt((s2/m-s1/m)^2 -8*(s1/m+s2/m)*(1-P/m)  ) ))^2)",RooArgList(x,mean,s1,s2))

modelx = RooBifurGauss("Gb","A Bifurcated Gaussian Distribution",x,meanx,s1,s2)

modely = RooGaussian("Gs","A G",y,meany,sy)#,s2)

tool = ProbTool([x,y],[modelx,modely])
stuff = tool.pdfCombinedVar("y*x","z")
#errors =  tool.range("P", center = meanx.getVal())
tool2 = ProbTool([stuff[0]],[stuff[1]])

#print "Errors (init) ", errors[1]-meanx.getVal(), errors[2]-meanx.getVal()
errors = tool2.range("z", center = meanx.getVal())

print "Errors", errors[1]-meanx.getVal(), errors[2]-meanx.getVal()


## Try more analytical

s1z = RooRealVar("s1z","s1z",0., sqrt(s1.getVal()**2 + (sy.getVal()*meanx.getVal())**2) * 2 )
s2z = RooRealVar("s2z","s2z",0., sqrt(s2.getVal()**2 + (sy.getVal()*meanx.getVal())**2) * 2 )

modelz = RooBifurGauss("Gb","A Bifurcated Gaussian Distribution",stuff[0],meanx,s1z,s2z)
modelz.fitTo(stuff[2],RooFit.Minos(kTRUE))

fr = stuff[0].frame()
stuff[1].plotOn(fr)
modelz.plotOn(fr, RooFit.LineColor(kRed))
fr.Draw()
