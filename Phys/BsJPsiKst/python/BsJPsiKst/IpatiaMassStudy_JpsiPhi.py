from ROOT import *
from math import *
import os
import sys
from Urania import *
AccessPackage("Bs2MuMu")
#from OurSites import NTUPLE_PATH
#from Cuts2013 import cuts12noKpi as cuts12, cuts11noKpi as cuts11
#from parameters import KpiBins4 as Kpibins
if not "BSJPSIKSTROOT" in os.environ.keys(): os.environ["BSJPSIKSTROOT"] = "../../"
gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/RooPhiBkg.cxx++")
gROOT.ProcessLine(".L RooIpatia2.cxx+")


# ------ Input args ----------
#iBin        = int(sys.argv[1]) # int to tag the mKpi bin
#Type        = str(sys.argv[2]) # string to tag the type: 'Bd' or 'Bs'
Year        = str(sys.argv[1]) # string to tag the year: '2011' or '2012'
#OutPutTag   = str(sys.argv[4]) # string to tag the name of the OutPutFile

# ------ mKpi mass range ----------
#mKpi_max = Kpibins[iBin+1] 
#mKpi_min = Kpibins[iBin] 

#mKpi_max = Kpibins[3]
#mKpi_min = Kpibins[0] 

#TRUEID = 0

# ------ Retrieve the data ntuple ----------
filename = "../../pid_selected_MC/"
filename11 = filename+"2011.root"
filename12 = filename+"2012.root"

file11 = TFile(filename11)
tree11 = file11.Get("DecayTree")
#Dummytree11 = file11.Get("DecayTree")
#Dummyfile11 = TFile("dummyTmp_File11.root","recreate")
#selectionCut = "abs(B0_TRUEID) == %i && Kst_892_0_MM > %d && Kst_892_0_MM < %d && %s"%(TRUEID,mKpi_min,mKpi_max,cuts11)
#print"----> Selecting events with:",selectionCut
#tree11 = Dummytree11.CopyTree(selectionCut)
nEntries11 = tree11.GetEntries()
#print"Number of events before selection for 2011:",Dummytree11.GetEntries()
print"Number of events for 2011:",nEntries11

file12 = TFile(filename12)
tree12 = file12.Get("DecayTree")
#Dummytree12 = file12.Get("DecayTree")
#Dummyfile12 = TFile("dummyTmp_File12.root","recreate")
#selectionCut = "abs(B0_TRUEID) == %i && Kst_892_0_MM > %d && Kst_892_0_MM < %d && %s"%(TRUEID,mKpi_min,mKpi_max,cuts12)
#print"----> Selecting events with:",selectionCut
#tree12 = Dummytree12.CopyTree(selectionCut)
nEntries12 = tree12.GetEntries()
#print"Number of events before selection for 2012:",Dummytree12.GetEntries()
print"Number of events for 2012:",nEntries12

# ------ Fitting variable ----------
mvar = "B_s0_MM"
mass = RooRealVar(mvar,mvar,5150., 5650.)
w_val = 2*float(nEntries11)/float(nEntries12)
lumi_w = RooRealVar("lumi_w","lumi_w",w_val)

# ------ DataSet (imported from tree) ----------
lumi_w.setVal(1)
data11 = RooDataSet("data11","data11", tree11, RooArgSet(mass, lumi_w),"","lumi_w")
lumi_w.setVal(w_val)
data12 = RooDataSet("data12","data12", tree12, RooArgSet(mass, lumi_w),"","lumi_w")

#if Year=="1112":
#    data = RooDataSet("data","data", data11, RooArgSet(mass, lumi_w),"","lumi_w")
#    data.Print()
#    data.append(data12)
#    data.Print()

if Year=="2011":
    data = RooDataSet("data","data", data11, RooArgSet(mass))
    data.Print()
if Year=="2012":
    data = RooDataSet("data","data", data12, RooArgSet(mass))
    data.Print()

# ------ Ipatia Params ----------
a2 = RooRealVar("a2","a2",3,1,200)
a = RooRealVar("a","a" , 3,1,200)
n = RooRealVar("n","n",1.,0.8,10)
n2 = RooRealVar("n2","n2",1.,0.8,60)

ipa_s = RooRealVar("ipa_s","ipa_s", 3, 12)

#ipa_m_min = 0.
#ipa_m_max = 0.

ipa_m_min = 5270.
ipa_m_max = 5380.

#if Type=="Bd":
#    ipa_m_min = 5270
#    ipa_m_max = 5290
#if Type=="Bs":
#    ipa_m_min = 5350
#    ipa_m_max = 5380

ipa_m = RooRealVar("ipa_m","ipa_m",ipa_m_min,ipa_m_max)
beta = RooRealVar("beta","beta",0)
zeta = RooRealVar("zeta","zeta",1e-04)
l = RooRealVar("l","l",-10, -.1)

ipatia = RooIpatia2("ipatia","ipatia",mass,l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)

# ------ Fit to data ----------
#if Year=="1112":
#    ipatia.fitTo(data,RooFit.Minos(False), RooFit.SumW2Error(kTRUE), RooFit.Offset(True), RooFit.NumCPU(1))
#else:
    #ipatia.fitTo(data,RooFit.Minos(False), RooFit.SumW2Error(kFALSE), RooFit.Offset(True), RooFit.NumCPU(1))
ipatia.fitTo(data,RooFit.Minos(False), RooFit.SumW2Error(kFALSE), RooFit.Offset(True), RooFit.NumCPU(1))

# ------ Fit projection ----------
frame = mass.frame()
data.plotOn(frame,RooFit.Binning(100))
ipatia.plotOn(frame)
frame.Draw()
frame.SaveAs("IpatiaMassStudy_results_"+Year+".root")
frame.SaveAs("IpatiaMassStudy_results_"+Year+".pdf")
#frame.SaveAs("IpatiaMassFitResults/%s_%s_%s.root"%(Year,Type,OutPutTag))
#frame.SaveAs("IpatiaMassFitResults/%s_%s_%s.pdf"%(Year,Type,OutPutTag))


# ------ Print output fit results ----------
prlist = [a,a2,n,n2,l,ipa_s,ipa_m]

outVal = {}
outErr = {}
for thing in prlist:
    outVal[thing.GetName()] = thing.getVal()
    outErr[thing.GetName()] = thing.getError()
print Year
print outVal
print outErr
