from AllMacroes import *
from ROOT import *
gROOT.ProcessLine(".x lhcbStyle.C")

## start with
dir = "root://eoslhcb.cern.ch//eos/lhcb/user/p/pkoppenb/Jpsi2ee/" # CERN
_data = TFile.Open(dir+"Jpsi2017-1548-1554.root")
_small = TFile.Open(dir+"Jpsi2017-1548-1554-Small.root")
#_mc = TFile.Open(dir+"Jpsi2017-MC-1531.root")
_mc.ls()
dataEE = _data.Get("Hlt2DiElectronJPsiEETurbo_Tuple/DecayTree") # data ee
#mcEE = _mc.Get("EmulatedTrigger_Tuple/DecayTree") # data ee
_small.ls()
smallEE = _small.Get("Jpsi2ee") # data ee
dataEE.AddFriend(smallEE)
# dataEE.Draw("Psi_PT:pt")
GetLumi(_data) # 17/pb of data
dataEE.Show(0) # all leaves of the Tree
smallEE.Show(0) # all leaves of the Tree
# dataEE.Draw("Psi_M") # the mass
# smallEE.Draw("mass","fabs(epPT-emPT)/(epPT-emPT)<0.7 && pt>5000 && pt<6000")

# SandB(mcEE,0,"Psi_M","Psi_PT>5000 && Psi_PT<6000","","1","N")
p = SandB(smallEE,0,"mass","pt<6000","pt>6000","fabs(epPT-emPT)/(epPT+emPT)<0.7","N",2000,4200)
p
png("mass for less and more than 6")

p = SandB(smallEE,0,"(epPT-emPT)/(epPT+emPT)","mass<3200","mass>3200","pt<6000","N",-1.,1.)
p
png("asymmetry below 6 ")

p = SandB(smallEE,0,"mass","(epBrem>0)&&(emBrem>0)","","pt>3000 && pt<4000 && fabs(epPT-emPT)/(epPT+emPT)<0.7","N",2000,4200)
p
png("mass versus Brem at 3<pt<4")

p = SandB(smallEE,0,"mass","(epBrem>0)&&(emBrem>0)","","pt>3000 && pt<4000","N",2000,4200)
p
png("mass versus Brem at 3<pt<4 noasym")

p = SandB(smallEE,0,"mass","fabs(epPT-emPT)/(epPT+emPT)<0.7","","pt>2500 && pt<3000 && (epBrem>0)&&(emBrem>0)","N",2000,4200)
p
png("mass versus asym at 2.5<pt<3 2 Brem")

p = SandB(smallEE,0,"mass","fabs(epPT-emPT)/(epPT+emPT)<0.7","","pt>3000 && pt<3500 && (epBrem>0)&&(emBrem>0)","N",2000,4200)
p
png("mass versus asym at 3<pt<3.5 2 Brem")

p = SandB(smallEE,0,"mass","fabs(epPT-emPT)/(epPT+emPT)<0.7","","pt>3500 && pt<4000 && (epBrem>0)&&(emBrem>0)","N",2000,4200)
p
png("mass versus asym at 3.5<pt<4 2 Brem")

p = SandB(smallEE,0,"mass","fabs(epPT-emPT)/(epPT+emPT)<0.7","","pt>4000 && pt<4500 && (epBrem>0)&&(emBrem>0)","N",2000,4200)
p
png("mass versus asym at 4<pt<4.5 2 Brem")

p = SandB(dataEE,0,"((eminus_PE-eminus_BremPE)-(eplus_PE-eplus_BremPE))/((eminus_PE-eminus_BremPE)+(eplus_PE-eplus_BremPE))","mass>3000","mass<3000","fabs(epPT-emPT)/(epPT+emPT)<0.7 && pt>3000 && pt<3500","N",2000,4200)
p
png("brem asymmetry in 3 to 3.5 versus mass")

dataEE.Draw("log(eminus_BremPE)/log(10.):log(eminus_PE)/log(10.)","eminus_HasBremAdded==1")
temp = gPad.GetPrimitive("htemp")
SetTitle("log_{10}(e^{-} E/MeV)","log_{10}(Brem e^{-} E/MeV)",h)
gPad.SetLogz()
h.Draw("COL")
png("e- brem E vs E")

dataEE.Draw("log(eminus_BremPE)/log(10.):log(eminus_PE)/log(10.)","eminus_HasBremAdded==1")
temp = gPad.GetPrimitive("htemp")
SetTitle("log_{10}(e^{-} E/MeV)","log_{10}(Brem e^{-} E/MeV)",h)
gPad.SetLogz()
h.Draw("COL")
png("e- brem E vs E")

h2=TH2D("h2","h2",40,3,7,40,3,7)
dataEE.Draw("log(eminus_PE-eminus_BremPE)/log(10.):log(eminus_PE)/log(10.) >> h2","eminus_HasBremAdded==1")
SetTitle("log_{10}(e^{-} E/MeV)","log_{10}(e^{-} E-Brem E/MeV)",h2)
gPad.SetLogz()
h2.Draw("COL")
png("e- E-brem_E vs E")

