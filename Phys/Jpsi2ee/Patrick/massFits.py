from AllMacroes import *
from ROOT import *

## start with
dir = "root://eoslhcb.cern.ch//eos/lhcb/user/p/pkoppenb/Jpsi2ee/" # CERN
dir = "/project/bfys/pkoppenb/Jpsi2ee/"                           # Nikhef
_ee = TFile.Open(dir+"Jpsi2ee-MC-2016-1536.root")
_mm = TFile.Open(dir+"Jpsi2mumu-MC-2016-1545.root")
_data = TFile.Open(dir+"Jpsi2017-1533.root")
_data.ls()
mcEE = _ee.Get("EmulatedTrigger_Tuple/DecayTree") # simulated J/psi->ee
mcMM = _mm.Get("EmulatedTrigger_Tuple/DecayTree") # simulated J/psi->mumu
dataMM = _data.Get("Hlt2DiMuonJPsiTurbo_Tuple/DecayTree") # data mumu
dataEE = _data.Get("Hlt2DiElectronJPsiEETurbo_Tuple/DecayTree") # data ee

GetLumi(_data) # 17/pb of data

dataEE.Show(0) # all leaves of the Tree

dataEE.Draw("Psi_M") # the mass
mcEE.Draw("Psi_M","Psi_BKGCAT==0 || Psi_BKGCAT==50") # the mass. Background category tells if the right thing was reconstructed

######################################################
# Fit a pdf on simulated data
######################################################
# 1. variables
mass = RooRealVar("Psi_M","Psi_M",2000.,4000.)
psiPT = RooRealVar("Psi_PT","Psi_M",2000.,100000.) # will be handy
psiBKG = RooRealVar("Psi_BKGCAT","Psi_BKGCAT",0.,200.) # will be handy
mcset = RooDataSet("MC","MC",mcEE,RooArgSet(mass,psiPT,psiBKG),"Psi_BKGCAT==0 || Psi_BKGCAT==50") # don't worry about "out of range events. It's the 2-4 GeV mass window.

# 2. plot
plot = mass.frame()
mcset.plotOn(plot)
plot.Draw()

# 3. A pdf : sum of a crystal ball and two Gaussians
mean = RooRealVar("mean","peak of crystal ball",3100.,3000.,3200.)
mean2 = RooRealVar("mean2","mean of gauss 2",3100.,3000.,3200.)
mean3 = RooRealVar("mean3","mean of gauss 3",3100.,3000.,3200.)
sigma = RooRealVar("sigma","sigma of crystal ball",50.,10.,100.)
sigma2 = RooRealVar("sigma2","sigma of gauss 2",50.,10.,200.)
sigma3 = RooRealVar("sigma3","sigma of gauss 3",200.,50.,500.)
cb_n = RooRealVar("CB_n","n of CB",1.,0.5,2.)
cb_a = RooRealVar("CB_a","alpha of CB",1.,0.1,3.)
CB = RooCBShape("CB","CB",mass,mean,sigma,cb_a,cb_n)
Gauss2 = RooGaussian("Gauss2","Gaussian",mass,mean2,sigma2)
Gauss3 = RooGaussian("Gauss3","Gaussian 3",mass,mean3,sigma3)
frac1 = RooRealVar("frac1","fraction of CB",0.7,0.,1.)
frac2 = RooRealVar("frac2","fraction of Gauss 2",0.2,0.,1.) # frac 3 = 1-frac1-frac2
signal = RooAddPdf("signal","sgnal pdf",RooArgList(CB,Gauss2,Gauss3),RooArgList(frac1,frac2))

plot = mass.frame()
mcset.plotOn(plot)
signal.plotOn(plot) # does not look Good
plot.Draw()

fit = signal.fitTo(mcset,RooFit.Save())  # do the fit. ! VERBOSE !
fit.Print()

plot = mass.frame()
mcset.plotOn(plot)
signal.plotOn(plot) # looks quite neat
signal.plotOn(plot,RooFit.Components("CB"),RooFit.LineColor(kGreen)) 
signal.plotOn(plot,RooFit.Components("Gauss2"),RooFit.LineColor(kRed)) 
signal.plotOn(plot,RooFit.Components("Gauss3"),RooFit.LineColor(kMagenta)) 
plot.Draw()
gPad.SaveAs("three_shape_fit.pdf")

gPad.SetLogy(1) # now in log.
gPad.SaveAs("three_shape_fit_log.pdf")


# you can try to see if CB plus one Gaussian is enough
# Also, can the fit good by forcing one Gaussian to ahve the same mean as the CB
# I'd be interested in seeing how the fit changes if you look at ranges of PT
# For instance psi_PT in 3-4, 4-5, 5-6 GeV, etc...


# This is for later...

######################################################
# Now for data
######################################################
# There is a background from electrons of low pt. Remove it by cutting on asymmetry
dataEE.Draw("(eplus_PT-eminus_PT)/(eplus_PT+eminus_PT)")
# it is somewhat correlated with mass at a given PT. 
dataEE.Draw("Psi_M","abs(Psi_PT-3000)<500")
dataEE.Draw("Psi_M","abs(Psi_PT-4000)<500")
dataEE.Draw("Psi_M","abs(Psi_PT-5000)<500")
dataEE.Draw("Psi_M","abs(Psi_PT-6000)<500")
# Lets' cut it away
asym = TCut("abs(eplus_PT-eminus_PT)/(eplus_PT+eminus_PT)<0.7")
dataEE.Draw("Psi_M",asym)

# 1. define variables and data
mass = RooRealVar("Psi_M","Psi_M",2000.,4000.)
eppt = RooRealVar("eplus_PT","eplus_PT",0.,1e6.);
empt = RooRealVar("eminus_PT","eminus_PT",0.,1e6.);
dataset = RooDataSet("data","data",dataEE,RooArgSet(mass,eppt,empt),asym.GetVal())
dataset.GetEntries()

# 2. a plot
plot = mass.frame()
dataset.plotOn(plot)
plot.Draw()

# 3. a PDF


