from ROOT import *
from math import *
from array import *

gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
#gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/Kpi_resonances.cxx+')
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/TwoBW.cxx+')
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/Kmatrix_2res.cxx+')
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/Kmatrix_nonRes.cxx+')
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/Swave.cxx+')
gROOT.ProcessLine('.x $SOMEMASSMODELSROOT/src/Wave_3res.cxx+')

gStyle.SetPalette(1)    #Color Palette
RooFit.PrintLevel(3)

plot = 1

background = 1
option = "Bd"
if option == "Bs":
  fhist = TFile('/afs/cern.ch/user/d/diegoms/vol5/antoni/for_diego/Kst_for_Bs.root')
  mass_B = 5366.3
else:
  fhist = TFile('/afs/cern.ch/user/d/diegoms/vol5/antoni/for_diego/Kst_for_Bd.root')
  mass_B = 5279.

label = 'PLOT'


h1 = fhist.Get('hist_Kst_Bs')

P1mass = RooRealVar("P1_mass","M(K#pi) ", h1.GetBinLowEdge(1), h1.GetBinLowEdge(h1.GetNbinsX()+1),"MeV/c^{2}")
P1mass.setRange("REDUCED",  h1.GetBinLowEdge(1), 1000)
#P1mass.setRange("REDUCED",  h1.GetBinLowEdge(1), h1.GetBinLowEdge(h1.GetNbinsX()+1))
P1mass.setRange("TIGHT",  856,936)
data = RooDataHist(label, label, RooArgList(P1mass),h1)

###### Some Variables

L0 = RooRealVar("L0","L0",0.)
L1 = RooRealVar("L1","L1",1.)
L2 = RooRealVar("L2","L2",2.)
L3 = RooRealVar("L3","L3",3.)
L4 = RooRealVar("L4","L4",4.)
#@L2 = RooRealVar("L2","L2",2.)


mb = RooRealVar("mb","mb",mass_B)
mv = RooRealVar("mv","mv",3096.916)


###### S - wave
m0S = RooRealVar("m0S","m0S",1425.)#, 1360,1480)
gamma0S = RooRealVar("gamma0S","gamma0S",270.)#,170,370)
kappaS = RooRealVar("kappaS","kappaS",0.1,0.,1)
phaseS = RooRealVar("phaseS","phaseS",0.)#15)#,0,2*pi)

#sw_a = RooRealVar("sw_a","sw_a",1.94e-03)#, 1.e-03, 6.e-03)
#sw_r = RooRealVar("sw_r","sw_r",1.76e-03)#, 1e-03,3e-03)
sw_a = RooRealVar("sw_a","sw_a",4.03e-03)#, 1.e-03, 6.e-03)
sw_r = RooRealVar("sw_r","sw_r",1.29e-03)#, 1
#swave = Swave("swave","swave",P1mass,sw_a,sw_r, m0S, gamma0S,kappa,mb,mv)
swave = Kmatrix_nonRes("swave","swave",P1mass, m0S, gamma0S,kappaS,phaseS,mb,mv,L0)
#swave= Wave_3res("swave", "swave",P1mass, m0S,gamma0S,m0S,gamma0S,m0S,gamma0S,L0,L0,L0,mb,mv,L0)

##### P-wave

m0P = RooRealVar("m0P","m0P",895.94, (1-5e-03)*895.94,900)
gamma0P = RooRealVar("gamma0P","gamma0P",20.,10,100)

m1P = RooRealVar("m1P","m1P",1414)#,1390,1430)
gamma1P = RooRealVar("gamma1P","gamma1P",232.)#,200,250.)

m2P = RooRealVar("m2P","m2P",1717)#,1690.,1740)
gamma2P = RooRealVar("gamma2P","gamma2P",322.)#,200,400.)
beta = RooRealVar("beta","beta",3.,0,20)
phase = RooRealVar("phase","phase",0,2*pi)

cP1 = RooRealVar("cP1","cP1",.1,0,20)
cP2 = RooRealVar("cP2","cP2",.1,0,20)
cnR = RooRealVar("cPnR","cPnR",0)#,20)
kappaP = RooRealVar("kappaP","kappaP",0.1,0.,1)
#
#Signal= TwoBW("Signal", "Signaml",P1mass, beta,phase,m0P,m1P,gamma0P,gamma1P,L1, mb,mv)
#Signal= Kmatrix_2res("Signal", "Signal",P1mass, beta,phase,m0P,m1P,gamma0P,gamma1P,L1, mb,mv)
Signal = Kmatrix_nonRes("Signal","Signal",P1mass, m0P, gamma0P,cnR,L0,mb,mv,L1)
SP= Kmatrix_nonRes("SP","SP",P1mass, m0P, gamma0P,kappaP,L0,mb,mv,L1)
#Signal= Wave_3res("Signal", "Signal",P1mass, m0P,gamma0P,m1P,gamma1P,m2P,gamma2P,cP1,cP2,cnR,mb,mv,L1)





f_swave = RooRealVar("fswave","fswave", 0.5, 0.3,1)
f_fwave = RooRealVar("ffwave","ffwave", 0.5, 0.3,1)
f_Lwave = RooRealVar("fLwave","fLwave", 0.5, 0.3,1.)


f_nop = RooRealVar( "f_nop", "f_nop", 0.3, 0.25, 0.35)#
nsig = RooRealVar("nsig","nsig",0,50000)
nbkg = RooRealVar("nbkg","nbkg",0,50000)
fnr = RooFormulaVar("fnr","fnr","nsig/(nsig+nbkg)",RooArgList(nsig,nbkg))

bkg = RooAddPdf("Lwave","Lwave",swave,SP,f_swave)
#model = RooAddPdf("model", "model", RooArgList( Zwaves, Signal), RooArgList( f_nop))
#model = RooAddPdf("model", "model", RooArgList( ZE, SignalE))#, RooArgList( f_nop))
modelSP = RooAddPdf("model", "model", bkg, Signal, f_nop)
#model = Signal

#res = model.fitTo(data,RooFit.Minos(),RooFit.Save(), RooFit.Range("REDUCED"),RooFit.Minos(True), RooFit.Strategy(1), RooFit.Extended(True),RooFit.Save(true),RooFit.Verbose(False))
res = modelSP.fitTo(data,RooFit.Minos(),RooFit.Save(), RooFit.Range("REDUCED"))

#        number of events of BW1 should be (1 - f_nores)/(BW1*BW1 + beta*beta*BW2*BW2 + 2 beta Re{exp(iphi)*Int{BW1*BW2 } }





  
c=TCanvas()
c.SetFillColor(0)
gStyle.SetOptTitle(0)

Kstframe = P1mass.frame()
Kstplot = RooAbsData.plotOn( data, Kstframe, RooFit.Name("histo_data"), RooFit.Binning(h1.GetNbinsX()))
model.plotOn(Kstframe,RooFit.Range("REDUCED"))
model.plotOn(Kstframe, RooFit.Components("Signal"), RooFit.LineStyle(kDashed))
model.plotOn(Kstframe, RooFit.Components("logbkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kRed))
model.plotOn(Kstframe, RooFit.Components("swave"), RooFit.LineStyle(kDashed), RooFit.LineColor(kMagenta))
model.plotOn(Kstframe, RooFit.Components("dwave"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlack))
model.plotOn(Kstframe, RooFit.Components("fwave"), RooFit.LineStyle(kDashed), RooFit.LineColor(kGreen))
model.plotOn(Kstframe, RooFit.Components("hwave"), RooFit.LineStyle(kDashed), RooFit.LineColor(kOrange))
  
Kstframe.Draw()   

area = h1.GetSum()*(h1.GetBinLowEdge(h1.GetNbinsX()+1)*1.-h1.GetBinLowEdge(1))/h1.GetNbinsX() #para a normalizacion
q = model.createCdf(RooArgSet(P1mass))

print fnr.getVal(), fnr.getPropagatedError(res)
BREAK

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


