from ROOT import *
from math import *

gSystem.Load("libMathMore")
gROOT.ProcessLine(".x $BSKSTKSTROOT/src/TimeIntegratedAcc5D_MCTruth/MassIntegrator.cxx+")

m1 = RooRealVar("m1","m1",896-150,896+150)
m2 = RooRealVar("m2","m2",896-150,896+150)

MBs = RooRealVar("MBs","MBs",5366.3)
# DGs = RooRealVar("DGs","DGs",-2.)
# Gs = RooRealVar("Gs","Gs",0)
DGs = RooRealVar("DGs","DGs",0.)
Gs = RooRealVar("Gs","Gs",1.)

m_kst = RooRealVar("m_kst","m_kst",8.95279e+02)
m_kst0 = RooRealVar("m_kst0","m_kst0",1430.)
g_kst = RooRealVar("g_kst","g_kst",5.01156e+01)
g_kst0 = RooRealVar("g_kst0","g_kst0",279.)


A = RooRealVar("A","A",1)
dA = RooRealVar("dA","dA",0)
dAp = RooRealVar("dAp","dAp",-pi/2)


n_m1 = RooRealVar("n_m1","n_m1",0)
n_m2 = RooRealVar("n_m2","n_m2",1)


indx = RooRealVar("indx","indx",1)
norm = RooRealVar("norm","norm",1)


# massint = MassIntegrator("massint","massint",indx,m1,m2,A,dA,A,dA,A,dA,
#                          Gs,DGs,m_kst,m_kst0,g_kst,g_kst0,MBs,norm,n_m1,n_m2)

massint = MassIntegrator("massint","massint",indx,m1,m2,
                         A,A,A,A,A,
                         dA,dA,dA,dA,dA,
                         Gs,DGs,m_kst,m_kst0,g_kst,g_kst0,MBs,norm,norm,norm,norm,
                         n_m1,n_m2)

# massintpi = MassIntegrator("massintpi","massintpi",indx,m1,m2,A,dA,A,dA,A,dAp,
#                          Gs,DGs,m_kst,m_kst0,g_kst,g_kst0,MBs,norm,n_m1,n_m2)

# massintpi = MassIntegrator("massintpi","massintpi",indx,m1,m2,A,dA,A,dAp,A,dAp,
#                          Gs,DGs,m_kst,m_kst0,g_kst,g_kst0,MBs,norm,n_m1,n_m2)



n_max = 3

massintvals = {}
massintpivals = {}

for i in range(n_max):
    for j in range(n_max):

        n_m1.setVal(i)
        n_m2.setVal(j)
        massintval = massint.createIntegral(RooArgSet(m1,m2)).getVal()
#         massintpival = massintpi.createIntegral(RooArgSet(m1,m2)).getVal()

        massintvals[i+n_max*j]=massintval
#         massintpivals[i+n_max*j]=massintpival



for n in massintvals.keys():
    
    print "if n_m1m2==",n,": return (",massintvals[n],"))*norm;"
#     print "if n_m1m2==",n,": return (Keven.Re()*(",massintvals[n],") + Keven.Im()*(",massintpivals[n],"))*norm;"
#     print "if n_m1m2==",n,": return (K10.Re()*(",massintvals[n],") + K10.Im()*(",massintpivals[n],"))*norm;"
#     print "if n_m1m2==",n,": return (K11.Re()*(",massintvals[n],") + K11.Im()*(",massintpivals[n],"))*norm;"
#     print "if n_m1m2==",n,": return (K12*(",massintvals[n],"))*norm;"
#     print "if n_m1m2==",n,": return (",massintvals[n],")*norm;"
#     print "if n_m1m2==",n,": return (Keven.Re()*(",massintvals[n],") + Keven.Im()*(",massintpivals[n],"))*norm;"
#     print "if n_m1m2==",n,": return K7*(",massintvals[n],")*norm;"


        

BREAK



cv = TCanvas()
cv.Divide(2,2)
cv.cd(1)
m1f = m1.frame()
massint.createIntegral(RooArgSet(m2)).plotOn(m1f)
m1f.Draw()
cv.cd(2)
m2f = m2.frame()
massint.createIntegral(RooArgSet(m1)).plotOn(m2f)
m2f.Draw()
cv.cd(3)
histo_ = massint.createHistogram("hito_",m1,RooFit.Binning(50),RooFit.YVar(m2,RooFit.Binning(50)))
histo_.Draw("LEGO2")


cv2 = TCanvas()
cv2.Divide(2,2)
cv2.cd(1)
m1f2 = m1.frame()
massintb.createIntegral(RooArgSet(m2)).plotOn(m1f2)
m1f2.Draw()
cv2.cd(2)
m2f2 = m2.frame()
massintb.createIntegral(RooArgSet(m1)).plotOn(m2f2)
m2f2.Draw()
cv2.cd(3)
histo_ = massintb.createHistogram("hito_",m1,RooFit.Binning(50),RooFit.YVar(m2,RooFit.Binning(50)))
histo_.Draw("LEGO2")


# massintval = massint.createIntegral(RooArgSet(m1,m2)).getVal()


# print "**********************************************************"
# print "**********************************************************"
# print
# print "Ingegral of MassTerm(",int(indx.getVal()),")xP(",int(n_m1.getVal()),",m1)xP(",int(n_m2.getVal()),",m2): ",massintval
# print
# print "**********************************************************"
# print "**********************************************************"



