#same as KstarAntonio, but all parameters left free

from ROOT import *
from math import *
from array import *
#from SomeMassmodels.FiterBasis import * estas duas non funcionaban no meu ordenador
#from SomeMassmodels.B2JpsiModels import *



#gSystem.Load("Kstar1D_gamma_cxx")
#gSystem.Load("Kstar2D_swave_gamma_cxx")
gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/Kstar1D_gamma.cxx+')
#gROOT.ProcessLine('.x Kstar1D_gamma.cxx++')


gROOT.Reset()
gROOT.SetStyle("Plain") #white background
gStyle.SetPalette(1)    #Color Palette
RooFit.PrintLevel(3)

plot = 1
imprime = 0
background = 1
option  = 0 #1 for Bs, 0 for Bd


Bs = 5366.3
DeltaM = 1050.-760.


if (option):
    fhist = TFile('/afs/cern.ch/user/d/diegoms/vol5/antoni/for_diego/Kst_for_Bs.root')
    label = 'Bs'
else:    
    fhist = TFile('/afs/cern.ch/user/d/diegoms/vol5/antoni/for_diego/Kst_for_Bd.root')
#    h1 = fhist.Get('hist_Kst_Bd')
    label = 'Bd'


h1 = fhist.Get('hist_Kst_Bs')

######################
##definition f BW. aqui se define a funcion de onda da BW, e as partes real e imaxinaria de BW1*BW2, necesario para calcular a PDF do termo de interferencia
######################

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


mk1 = 895.94 #parameters of the kstars
gammak1 = 50
mk2 = 1425
gammak2 = 270

#BW1*BW2 = f1 + f2i
inte = Math.Integrator()
def f1(mass):
  val = BW(mass[0],mk1,gammak1)*BW(mass[0],mk2,gammak2)
  return val.real
f1T = TF1('f1', f1, 0, 2000)
w = Math.WrappedTF1(f1T)
F1 = inte.Integral(w,h1.GetBinLowEdge(1),h1.GetBinLowEdge(h1.GetNbinsX()+1))
def f2(mass):
  val = BW(mass[0],mk1,gammak1)*BW(mass[0],mk2,gammak2)
  return val.imag
f2T = TF1('f2', f2, 0, 2000)
w = Math.WrappedTF1(f2T)
F2 = inte.Integral(w,h1.GetBinLowEdge(1),h1.GetBinLowEdge(h1.GetNbinsX()+1))

def cuad(mass):
  val = BW(mass[0],a,b)
  out = val*val.conjugate()
  return out.real

a = mk1
b = gammak1
f  = TF1('f', cuad, h1.GetBinLowEdge(1), h1.GetBinLowEdge(h1.GetNbinsX()+1))
w = Math.WrappedTF1(f)
mod1 = inte.Integral(w,h1.GetBinLowEdge(1),h1.GetBinLowEdge(h1.GetNbinsX()+1))

a = mk2
b = gammak2
f  = TF1('f', cuad, h1.GetBinLowEdge(1), h1.GetBinLowEdge(h1.GetNbinsX()+1))
w = Math.WrappedTF1(f)
mod2 = inte.Integral(w,h1.GetBinLowEdge(1),h1.GetBinLowEdge(h1.GetNbinsX()+1))


phi_c = 180/TMath.Pi()*Math.atan(F1/F2) #angle at which the interference is cancelled

#############################################
#############################################


if(background):
  bkglabel = ''
else:
  bkglabel = '_nobkg_'

out = open('logKstar_free.txt', 'a')
out.write('Log for ' + label +' ')
if not (background):
  out.write('without bkg fitting')
out.write('\n\n\n')



P1mass = RooRealVar("P1_mass","M(k#pi) ", h1.GetBinLowEdge(1), h1.GetBinLowEdge(h1.GetNbinsX()+1),"MeV/c^{2}")

data = RooDataHist(label, label, RooArgList(P1mass),h1)


#BW definition
m0 = RooRealVar("m0","m0",895.94)
gamma0 = RooRealVar("gamma0","gamma0",50.)
m0hi = RooRealVar("m0hi","m0hi",1425)
gamma0hi = RooRealVar("gamma0hi","gamma0hi",270.)


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
gammaval = 1-.8918
if(background):
  gamma = RooRealVar( "gamma", "gamma", gammaval, 0, 1)
else:
  gamma = RooRealVar( "gamma", "gamma", 0)

model = RooAddPdf("model", "model", RooArgList( logbkg, Signal), RooArgList( gamma))

#fitting
res = model.fitTo(data,RooFit.Minos(),RooFit.Save())




#number of events of BW1 should be (1 - gamma)/(BW1*BW1 + beta*beta*BW2*BW2 + 2 beta Re{exp(iphi)*Int{BW1*BW2 } }

int_real = RooRealVar('int_real','int_real', F1)
int_imag = RooRealVar('int_imag', 'int_imag', F2)
mod1R = RooRealVar('mod1','mod1',mod1)
mod2R = RooRealVar('mod2','mod2',mod2)
nsig1 = RooFormulaVar('nsig1', 'nsig1','mod1*(1 - gamma)/(mod1 + beta*beta*mod2 + 2*beta*(int_real*cos(phase)-int_imag*sin(phase)))',RooArgList(gamma,beta,phase,int_real,int_imag, mod1R, mod2R ))


out.write('Results\n\n')
out.write('gamma = ' + str(gamma.getVal()) + ' pm ' + str(gamma.getError()) + '\n')
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

if (plot):
  #draw
  c=TCanvas()
  c.SetFillColor(0)
  gStyle.SetOptTitle(0)

  Kstframe = P1mass.frame()
  Kstplot = RooAbsData.plotOn( data, Kstframe, RooFit.Name("histo_data"), RooFit.Binning(h1.GetNbinsX()))
  model.plotOn(Kstframe)
  model.plotOn(Kstframe, RooFit.Components("Signal"), RooFit.LineStyle(kDashed))
  model.plotOn(Kstframe, RooFit.Components("logbkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
  #model.paramOn(Kstframe)
  Kstframe.Draw()   

out.write('\n\n\n')
out.close()





area = h1.GetSum()*(h1.GetBinLowEdge(h1.GetNbinsX()+1)*1.-h1.GetBinLowEdge(1))/h1.GetNbinsX() #para a normalizacion


def pdf1(mass): #BW1
    P1mass.setVal(mass[0])
    norm = mod1 + mod2*beta.getVal()*beta.getVal() + 2*beta.getVal()*(Math.cos(phase.getVal())*F1- Math.sin(phase.getVal())*F2 )
    return area/norm*(BW(mass[0],mk1,gammak1)*BW(mass[0],mk1,gammak1).conjugate()).real*(1-gamma.getVal())
def pdf2(mass): #BW2 + interference
    P1mass.setVal(mass[0])
    norm = mod1 + mod2*beta.getVal()*beta.getVal() + 2*beta.getVal()*(Math.cos(phase.getVal())*F1- Math.sin(phase.getVal())*F2 )
    return area*((model.getVal(RooArgSet(P1mass))) - (BW(mass[0],mk1,gammak1)*BW(mass[0],mk1,gammak1).conjugate()).real/norm*(1-gamma.getVal()) - gamma.getVal()*logbkg.getVal(RooArgSet(P1mass)))

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

if (imprime):
  #c.Print('plots/fit_Kst_' + label + '_phi_' + str(phi) + '.pdf')
  c.Print('plots/fit_Kst_' +  label + bkglabel + 'beta_' + str(beta.getVal()) + '_phi_' + str(phase.getVal()) +  '.png')
