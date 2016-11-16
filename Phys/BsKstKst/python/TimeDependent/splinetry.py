from ROOT import *
from GetAcc import *

gROOT.ProcessLine(".L ../../src/TimeDependent/SplineTAcc.cxx++")

datalist = LoadDataTime(data_file,data_tree,MC_datatype,evnum_limit) 

knotlists = getKnots(5,*datalist)

t0 = RooRealVar("t0","t0",knotlists[0][0])
t1 = RooRealVar("t1","t1",knotlists[0][1])
t2 = RooRealVar("t2","t2",knotlists[0][2])
t3 = RooRealVar("t3","t3",knotlists[0][3])
t4 = RooRealVar("t4","t4",knotlists[0][4])

c0 = RooRealVar("c0","c0",0.)
c1 = RooRealVar("c1","c1",-4.50386e-04,-1.,1.)
c2 = RooRealVar("c2","c2",1.01620e+00,0.,5.)
c3 = RooRealVar("c3","c3",1.11458e+00,0.,5.)
c4 = RooRealVar("c4","c4",1.34619e+00,0.,5.)
c5 = RooRealVar("c5","c5",9.03046e-01,0.,5.)
c6 = RooRealVar("c6","c6",1.)

splpdf = SplineTAcc("splpdf","splpdf",t_MC,t0,t1,t2,t3,t4,c0,c1,c2,c3,c4,c5,c6)

spldata = RooDataSet("spldata","spldata",datalist[0],datalist[0].get(),"",MCweight4.GetName())

splpdf.fitTo(spldata,RooFit.NumCPU(6))#,RooFit.Strategy(2),RooFit.Minos(1))

fr = t_MC.frame()
spldata.plotOn(fr)
splpdf.plotOn(fr,RooFit.LineColor(kRed))
fr.Draw()

tl1 = 0.14+knotlists[0][1]/12.*0.81
tl2 = 0.14+knotlists[0][2]/12.*0.81
tl3 = 0.14+knotlists[0][3]/12.*0.81

l1 = TLine(tl1,0.16,tl1,0.95)
l1.SetNDC()
l1.SetLineStyle(2)
l2 = TLine(tl2,0.16,tl2,0.95)
l2.SetNDC()
l2.SetLineStyle(2)
l3 = TLine(tl3,0.16,tl3,0.95)
l3.SetNDC()
l3.SetLineStyle(2)
l1.Draw()
l2.Draw()
l3.Draw()
