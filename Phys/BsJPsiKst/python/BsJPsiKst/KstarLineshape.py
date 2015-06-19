from ROOT import *
from math import *
from array import *

gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/Kstar1D_gamma.cxx+')

gStyle.SetPalette(1)    #Color Palette
RooFit.PrintLevel(3)

plot = 1

background = 1

#fhist = TFile('/afs/cern.ch/user/d/diegoms/vol5/antoni/for_diego/Kst_for_Bs.root')   
fhist = TFile('/afs/cern.ch/user/d/diegoms/vol5/antoni/for_diego/Kst_for_Bd.root')

label = 'PLOT'


h1 = fhist.Get('hist_Kst_Bs')

P1mass = RooRealVar("P1_mass","M(K#pi) ", h1.GetBinLowEdge(1), h1.GetBinLowEdge(h1.GetNbinsX()+1),"MeV/c^{2}")

data = RooDataHist(label, label, RooArgList(P1mass),h1)


#BW definition

##### P-wave

m0 = RooRealVar("m0","m0",895.94)
gamma0 = RooRealVar("gamma0","gamma0",50.)

m0hi = RooRealVar("m0hi","m0hi",1414.)
gamma0hi = RooRealVar("gamma0hi","gamma0hi",232.)

##### S - wave
m0S = RooRealVar("m0S","m0S",1425.)
gamma0S = RooRealVar("gamma0S","gamma0S",270.)
swave = RooBreitWigner("swave","swave",P1mass, m0S, gamma0S)

#### D- wave

m0D = RooRealVar("m0D","m0D",1432.)
gamma0D = RooRealVar("gamma0D","gamma0D",109.)
dwave = RooBreitWigner("dwave","dwave",P1mass, m0D, gamma0D)

f_swave = RooRealVar("fswave","fswave", 0.3,0.,1.)
Zwaves = RooAddPdf("Zwave","Zwave",swave,dwave,f_swave)

alpha = RooRealVar("alpha","alpha",1.)
beta = RooRealVar("beta","beta",0.,0,20*sqrt(3.9/9.8))#10.)#0.18)#,1.)
#beta  = RooRealVar("beta","beta", betaval)
phase = RooRealVar("phase","phase",0.15, 0,2*pi)

Signal = Kstar1D_gamma("Signal", "Signal",P1mass,alpha,beta,phase,m0,m0hi,gamma0,gamma0hi)


#Bkg definition
#logarithmic PDF = log(loga * P1mass + logb)
 
loga = RooRealVar('loga', 'loga', 744, 720, 780)
logbkg = RooGenericPdf('logbkg','log(P1_mass - loga)', RooArgList(P1mass, loga))


#Model definition

f_nores = RooRealVar( "f_nores", "f_nores", 0.3, 0, 1)
f_x = RooRealVar( "f_x", "f_x", 0.)#0.1, 0, 1)
modelnpw = RooAddPdf("no p-wave", "no p-wave", RooArgList( logbkg, Zwaves), RooArgList( f_x))
model = RooAddPdf("model", "model", RooArgList( modelnpw, Signal), RooArgList( f_nores))

#fitting
res = model.fitTo(data,RooFit.Minos(),RooFit.Save())

#number of events of BW1 should be (1 - f_nores)/(BW1*BW1 + beta*beta*BW2*BW2 + 2 beta Re{exp(iphi)*Int{BW1*BW2 } }




  
c=TCanvas()
c.SetFillColor(0)
gStyle.SetOptTitle(0)

Kstframe = P1mass.frame()
Kstplot = RooAbsData.plotOn( data, Kstframe, RooFit.Name("histo_data"), RooFit.Binning(h1.GetNbinsX()))
model.plotOn(Kstframe)
model.plotOn(Kstframe, RooFit.Components("Signal"), RooFit.LineStyle(kDashed))
model.plotOn(Kstframe, RooFit.Components("logbkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
model.plotOn(Kstframe, RooFit.Components("swave"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
model.plotOn(Kstframe, RooFit.Components("dwave"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlack))
  
Kstframe.Draw()   

area = h1.GetSum()*(h1.GetBinLowEdge(h1.GetNbinsX()+1)*1.-h1.GetBinLowEdge(1))/h1.GetNbinsX() #para a normalizacion


######################
## ##definition f BW. aqui se define a funcion de onda da BW, e as partes real e imaxinaria de BW1*BW2, necesario para calcular a PDF do termo de interferencia
## ######################

MPion = 139.57018
MKaon = 493.667
MMuon = 105.65836668
MJPsi = 3096.916
R =  0.003

def BW(mass, mass0, Gamma0):  #breit wigner
  suma = (MPion+MKaon)*(MPion+MKaon)/(mass*mass);
  resta = (MPion-MKaon)*(MPion-MKaon)/(mass*mass);
  Km = mass/2.*TMath.Sqrt(1.-suma)*TMath.Sqrt(1.-resta);

  suma0 = (MPion+MKaon)*(MPion+MKaon)/(mass0*mass0);
  resta0 = (MPion-MKaon)*(MPion-MKaon)/(mass0*mass0);
  Km0 = mass0/2.*TMath.Sqrt(1.-suma0)*TMath.Sqrt(1.-resta0);
  
  Fm = 1./(1+R*R*Km*Km);
  Fm0 = 1./(1+R*R*Km0*Km0);

  Gamma = Gamma0*(mass0/mass)*(Km/Km0)*(Km/Km0)*(Km/Km0)*(Fm/Fm0);

  denom = complex(mass*mass-mass0*mass0,-Gamma*mass0)

  nu = TMath.Sqrt(mass0*mass0*(mass0*mass0+Gamma*Gamma));
  k = complex(TMath.Sqrt(2.*TMath.Sqrt(2.)*mass0*Gamma*nu/TMath.Pi()/TMath.Sqrt(mass0*mass0+nu)),0.);

  return k/denom;


#BW1*BW2 = f1 + f2i
inte = Math.Integrator()
def f1(mass):
  val = BW(mass[0],m0.getVal(),gamma0.getVal())*BW(mass[0],m0hi.getVal(),gamma0hi.getVal())
  return val.real
f1T = TF1('f1', f1, 0, 2000)
w = Math.WrappedTF1(f1T)
F1 = inte.Integral(w,h1.GetBinLowEdge(1),h1.GetBinLowEdge(h1.GetNbinsX()+1))
def f2(mass):
  val = BW(mass[0],m0.getVal(),gamma0.getVal())*BW(mass[0],m0hi.getVal(),gamma0hi.getVal())
  return val.imag
f2T = TF1('f2', f2, 0, 2000)
w = Math.WrappedTF1(f2T)
F2 = inte.Integral(w,h1.GetBinLowEdge(1),h1.GetBinLowEdge(h1.GetNbinsX()+1))

def cuad(mass):
  val = BW(mass[0],mX,gX)
  out = val*val.conjugate()
  return out.real

mX = m0.getVal()
gX = gamma0.getVal()

f  = TF1('f', cuad, h1.GetBinLowEdge(1), h1.GetBinLowEdge(h1.GetNbinsX()+1))
w = Math.WrappedTF1(f)
mod1 = inte.Integral(w,h1.GetBinLowEdge(1),h1.GetBinLowEdge(h1.GetNbinsX()+1))

mX = m0hi.getVal()
gX = gamma0hi.getVal()

f  = TF1('f', cuad, h1.GetBinLowEdge(1), h1.GetBinLowEdge(h1.GetNbinsX()+1))
w = Math.WrappedTF1(f)
mod2 = inte.Integral(w,h1.GetBinLowEdge(1),h1.GetBinLowEdge(h1.GetNbinsX()+1))


############## phi_c = 180/TMath.Pi()*Math.atan(F1/F2) #angle at which the interference is cancelled

#############################################
#############################################



def pdf1(mass): #BW1
    P1mass.setVal(mass[0])
    norm = mod1 + mod2*beta.getVal()*beta.getVal() + 2*beta.getVal()*(Math.cos(phase.getVal())*F1- Math.sin(phase.getVal())*F2 )
    return area/norm*(BW(mass[0],m0.getVal(),gamma0.getVal())*BW(mass[0],m0.getVal(),gamma0.getVal()).conjugate()).real*(1-f_nores.getVal())
def pdf2(mass): #BW2 + interference   ### CHECKK!!!
    P1mass.setVal(mass[0])
    norm = mod1 + mod2*beta.getVal()*beta.getVal() + 2*beta.getVal()*(Math.cos(phase.getVal())*F1- Math.sin(phase.getVal())*F2 )
    return area*((model.getVal(RooArgSet(P1mass))) - (BW(mass[0],m0.getVal(),gamma0.getVal())*BW(mass[0],m0.getVal(),gamma0.getVal()).conjugate()).real/norm*(1-f_nores.getVal()) - f_nores.getVal()*modelnpw.getVal(RooArgSet(P1mass)))

pru2 = TF1('pru2', pdf2, h1.GetBinLowEdge(1), h1.GetBinLowEdge(h1.GetNbinsX()+1))
pru2.SetLineStyle(kDashed)
pru2.SetLineColor(kOrange)
pru2.Draw('same')

pru1 = TF1('pru1', pdf1, h1.GetBinLowEdge(1), h1.GetBinLowEdge(h1.GetNbinsX()+1))
pru1.SetLineStyle(kDashed)
pru1.SetLineColor(kGreen)
pru1.Draw('same')

## def pdf0(mass):
##   P1mass.setVal(mass[0])
##   norm = mod1 + mod2*beta.getVal()*beta.getVal() + 2*beta.getVal()*(Math.cos(phase.getVal())*F1- Math.sin(phase.getVal())*F2 )
##   return area*(model.getVal(RooArgSet(P1mass)))

## pru0 = TF1('pru0', pdf0, h1.GetBinLowEdge(1), h1.GetBinLowEdge(h1.GetNbinsX()+1))
## pru0.SetLineStyle(kDashed)
## pru0.SetLineColor(kRed)
## pru0.Draw('same')

#if (imprime):
#c.Print('plots/fit_Kst_' + label + '_phi_' + str(phi) + '.pdf')

#####################
# UNCOMMENT TO SAVE #
#####################

#c.Print('plots/fit_Kst_' +  label + bkglabel + 'beta_' + str(beta.getVal()) + '_phi_' + str(phase.getVal()) +  '.png')

int_real = RooRealVar('int_real','int_real', F1)
int_imag = RooRealVar('int_imag', 'int_imag', F2)
mod1R = RooRealVar('mod1','mod1',mod1)
mod2R = RooRealVar('mod2','mod2',mod2)
nsig1 = RooFormulaVar('nsig1', 'nsig1','mod1*(1 - f_nores)/(mod1 + beta*beta*mod2 + 2*beta*(int_real*cos(phase)-int_imag*sin(phase)))',RooArgList(f_nores,beta,phase,int_real,int_imag, mod1R, mod2R ))


bkglabel = '_nobkg_'*bool(f_nores.getVal())

out = open('logKstar.txt', 'a')
out.write('Log for ' + label +' ')
if not (f_nores.getVal()):
  out.write('without bkg fitting')
out.write('\n\n\n')

out.write('Results\n\n')
out.write('f_nores = ' + str(f_nores.getVal()) + ' pm ' + str(f_nores.getError()) + '\n')
out.write('beta = ' + str(beta.getVal()) + ' pm ' + str(beta.getError()) + '\n')
out.write('phase = ' + str(phase.getVal()) + ' pm ' + str(phase.getError()) + '\n')
out.write('phase = ' + str(180/TMath.Pi()*phase.getVal()) + ' pm ' + str(180/TMath.Pi()*phase.getError()) + '\n')
out.write('loga = ' + str(loga.getVal()) + ' pm ' + str(loga.getError()) + '\n')
out.write('ratio of events of Kstar_895\n')# = ' + str(nkstar) + '\n')
try: #este da as veces erros
  error = nsig1.getPropagatedError(res)
except:
  out.write('nsig1 = ' + str(nsig1.getVal() ) + ' pm ' + ' ERROR:  Error could not be calculated\n')
else:
  out.write('nsig1 = ' + str(nsig1.getVal() ) + ' pm ' + str(error) + '\n')
out.write('\n\n')
out.write('\n\n\n')
out.close()


