from ROOT import *
from ROOT import Double as double
from math import *
import os
import sys
import time
from Urania import *
AccessPackage("Bs2MuMu")
from smartpyROOT import *
from PDF_2013_Asym_toys import *
from parameters import KpiBins4 as KpiBins, myCsp4 as myCsp
print "Python code for generating pseudo experiments."

gROOT.ProcessLine( "struct MyStructF{ Float_t afloat; };" )
gROOT.ProcessLine( "struct MyStructI{ Int_t aint; };" )

# ------ Input args ----------
iexp          = int(sys.argv[1]) # int to tag the mKpi bin
OutPutTag     = str(sys.argv[2]) # string to tag the name of the OutPutFile
_USE_GRID_    = int(sys.argv[3]) # int to tag the use of GRID
doPeakingBkgs = int(sys.argv[4]) # int to enable peaking bkgs generation
nonZeroACPs   = int(sys.argv[5]) # int to flag if we generate the ACPs with non zero values
if nonZeroACPs:
    ACPset    = str(sys.argv[6]) # string to tag the set of ACPs

from parameters_toys import yields_toys_bins_True        as yieldsBinsTrue
from parameters_toys import yields_toys_bins_Poissonized as yieldsBinsPoisson

from parameters_toys import mass_params as massParams
from parameters_toys import angular_params as angParams
from parameters_toys import parametric_angular_acceptance as acc_params

from parameters_toys import d_ACPs

debug = False#True

gRandom = TRandom3()
seed = 0 # see http://root.cern.ch/root/html/TRandom3.html#TRandom3:SetSeed
gRandom.SetSeed(seed)

ACC_TYPE = 1
SAME_ACC = 1
flatAcc = 0

Pi = 3.141592653589793
TwoPi = 2.*Pi
verbose = False

l_years = ["2011","2012"]
l_signs = ["neg","pos"]
l_bins = []
for ibin in range(len(KpiBins)-1):
    l_bins.append(ibin)

l_speciesName = ["Bs","Bd","Combi"]
if doPeakingBkgs:
    l_speciesName.append("Lb2JpsipK")
    l_speciesName.append("Lb2JpsipPi")
    
# -----------------------------------------------------------------------------------------------------------------------
# ANGULAR PDF DEFINITIONS
# -----------------------------------------------------------------------------------------------------------------------

# -----------------------------------------------------------------------
# Bd
# -----------------------------------------------------------------------
# -----------------------------------------------------------------------

# 2011 pos
AngBd_2011p, AngBd_2011n = InitSignalPdfs("Bd","2011",acc_type = ACC_TYPE)
AngBd_2011p.OwnPhys(equalAsym = 1)
if flatAcc:
    AngBd_2011p.FlatAcc()
else:
    AngBd_2011p.OwnAcc()

#Bd paper values 
fL_Bd  = angParams["Bd"][0]["fL"]
fpa_Bd = angParams["Bd"][0]["fpa"]
dpa_Bd = angParams["Bd"][0]["dpa"]
dpe_Bd = angParams["Bd"][0]["dpe"]
ds_Bd  = angParams["Bd"][0]["ds"]
As2_Bd = angParams["Bd"][0]["As2"]

AngBd_2011p.modParamAsym("fL",  fL_Bd,   fL_Bd,         1-fL_Bd,       False) 
AngBd_2011p.modParamAsym("fpa", fpa_Bd,  fpa_Bd,        1-fpa_Bd,      False)#)
AngBd_2011p.modParamAsym("dpa", dpa_Bd,  TwoPi-dpa_Bd,  TwoPi+dpa_Bd,  False)
AngBd_2011p.modParamAsym("dpe", dpe_Bd,  TwoPi-dpe_Bd,  TwoPi+dpe_Bd,  False)

AngBd_2011p.modParamAsym("ds",  ds_Bd,   TwoPi-ds_Bd,   TwoPi+ds_Bd,  False)
AngBd_2011p.modParamAsym("As2", As2_Bd,  As2_Bd,        1-As2_Bd,     False)#2012
AngBd_2011p.modParam("CSP",1.,.1,True)

AngBd_2011p.ACPL.setVal(angParams["Bd"][0]["ACPL"])
AngBd_2011p.ACPL.setConstant(True)

if not flatAcc:
    AngBd_2011p.modParam("c1_psi",  acc_params["Bd"]["2011"]["c1_psi"],0.1)
    AngBd_2011p.modParam("c2_psi",  acc_params["Bd"]["2011"]["c2_psi"],0.1)
    AngBd_2011p.modParam("c3_psi",  acc_params["Bd"]["2011"]["c3_psi"],0.1)
    AngBd_2011p.modParam("c4_psi",  acc_params["Bd"]["2011"]["c4_psi"],0.1)
    AngBd_2011p.modParam("c2_theta",acc_params["Bd"]["2011"]["c2_theta"],0.1)

# 2011 neg
AngBd_2011n.CopyFreeParams(AngBd_2011p)
AngBd_2011n.CopyAcc(AngBd_2011p)

# -----------------------------------------------------------------------
# 2012 pos
AngBd_2012p,  AngBd_2012n = InitSignalPdfs("Bd","2012",acc_type = ACC_TYPE)
AngBd_2012p.CopyPhys(AngBd_2011p)
AngBd_2012p.CopyAcc(AngBd_2011p)

# 2012 neg
AngBd_2012n.CopyPhys(AngBd_2011n)
AngBd_2012n.CopyAcc(AngBd_2011p)

# -----------------------------------------------------------------------
# Bs  
# -----------------------------------------------------------------------
# -----------------------------------------------------------------------
# 2011 pos
AngBs_2011p,  AngBs_2011n = InitSignalPdfs("Bs","2011",acc_type = ACC_TYPE)
AngBs_2011p.OwnPhys(equalAsym = 0)

fL_Bs  = angParams["Bs"][0]["fL"]
fpa_Bs = angParams["Bs"][0]["fpa"]
dpa_Bs = angParams["Bs"][0]["dpa"]
dpe_Bs = angParams["Bs"][0]["dpe"]
ds_Bs  = angParams["Bs"][0]["ds"]
As2_Bs = angParams["Bs"][0]["As2"]

# Fix the angular parameters (by hand here)
AngBs_2011p.modParamAsym("fL",  fL_Bs,   fL_Bs,         1-fL_Bs,      False) 
AngBs_2011p.modParamAsym("fpa", fpa_Bs,  fpa_Bs,        1-fpa_Bs,     False)
AngBs_2011p.modParamAsym("dpa", dpa_Bs,  TwoPi-dpa_Bs,  TwoPi+dpa_Bs, False)
AngBs_2011p.modParamAsym("dpe", dpe_Bs,  TwoPi-dpe_Bs,  TwoPi+dpe_Bs, False)
AngBs_2011p.modParamAsym("ds",  ds_Bs,   TwoPi-ds_Bs,   TwoPi+ds_Bs,  False)
AngBs_2011p.modParamAsym("As2", As2_Bs,  As2_Bs,        1-As2_Bs,     False)#2012

AngBs_2011p.modParam("CSP",1.,.1,True)

ACPL_Bs  = angParams["Bs"][0]["ACPL"]
ACPpa_Bs = angParams["Bs"][0]["ACPpa"]
ACPpe_Bs = angParams["Bs"][0]["ACPpe"]
ACPS_Bs  = angParams["Bs"][0]["ACPS"]

if nonZeroACPs:
    ACPL_Bs  = d_ACPs[ACPset]["ACPL"]
    ACPpa_Bs = d_ACPs[ACPset]["ACPpa"]
    ACPpe_Bs = d_ACPs[ACPset]["ACPpe"]
    ACPS_Bs  = d_ACPs[ACPset]["ACPS"]

    print "Going to generate pseudo-experiment with ACPs values set to random set number %s :"%(ACPset[len(ACPset)-1:])
    for key in d_ACPs[ACPset].keys():
        print "%s = %s"%(key, d_ACPs[ACPset][key])
else:
    print "Going to generate pseudo-experiment with all ACPs set to zero (taken from parameters_toys.py) !!!"

AngBs_2011p.ACPL.setVal(ACPL_Bs)
AngBs_2011p.ACPL.setConstant(True)
AngBs_2011p.ACPpa.setVal(ACPpa_Bs)
AngBs_2011p.ACPpa.setConstant(True)
AngBs_2011p.ACPpe.setVal(ACPpe_Bs)
AngBs_2011p.ACPpe.setConstant(True)
AngBs_2011p.ACPS.setVal(ACPS_Bs)
AngBs_2011p.ACPS.setConstant(True)

# 2011 neg
AngBs_2011n.CopyFreeParams(AngBs_2011p)

# -----------------------------------------------------------------------
# 2012 
AngBs_2012p,  AngBs_2012n = InitSignalPdfs("Bs","2012",acc_type = ACC_TYPE)
AngBs_2012p.CopyPhys(AngBs_2011p)
AngBs_2012n.CopyPhys(AngBs_2011n)

# -----------------------------------------------------------------------
# COPY ACCEPTANCE PARAMETERS
if SAME_ACC:
    AngBs_2011p.CopyAcc(AngBd_2011p)
    AngBs_2012p.CopyAcc(AngBd_2012p)
    AngBs_2011n.CopyAcc(AngBd_2011n)
    AngBs_2012n.CopyAcc(AngBd_2012n)

# --------------------------------------
# MAKE THE PDFs
AngBd_2011n.make() 
AngBs_2011n.make()
AngBd_2011p.make()
AngBs_2011p.make()

AngBd_2012n.make()
AngBs_2012n.make()
AngBd_2012p.make()
AngBs_2012p.make()

AngModels = {}
for name in ("Bs","Bd"):
    AngModels[name]={}

AngModels["Bd"]["2011"] = {"neg": AngBd_2011n, "pos": AngBd_2011p}
AngModels["Bd"]["2012"] = {"neg": AngBd_2012n, "pos": AngBd_2012p}
AngModels["Bs"]["2011"] = {"neg": AngBs_2011n, "pos": AngBs_2011p}
AngModels["Bs"]["2012"] = {"neg": AngBs_2012n, "pos": AngBs_2012p}

# -------------------------------------------------------
# BACKGROUNDS  
# -------------------------------------------------------
CombiBkgmodel = {}
for year in l_years:
    CombiBkgmodel[year] = FullBackground("CombiBkg_%s"%year)

    if ACC_TYPE !=2:
        CombiBkgmodel[year].thetaFromAcc(AngModels["Bd"][year]["pos"])
    else:
        CombiBkgmodel[year].OwnTheta()

    CombiBkgmodel[year].modParam("c1_phi_bkg",0,0)
    CombiBkgmodel[year].modParam("c2_phi_bkg",1,0)
    CombiBkgmodel[year].modParam("c3_phi_bkg",0,0)
    
    # --------------------------------------
    # MAKE THE PDFs
    CombiBkgmodel[year].make()

# -- Lb peaking bkgs
if doPeakingBkgs:
    LbpKmodel = LambdaDecay("Lb2JpsipK")
    Lbppimodel = LambdaDecay("Lb2JpsipPi")
	
# -----------------------------------------------------------------------------------------------------------------------
# DATASET GENERATION FOR MASS & ANGLES 
# -----------------------------------------------------------------------------------------------------------------------

for name in l_speciesName:
    for year in l_years:
        for sign in l_signs:
            for ibin in l_bins:
                print'nEvts to generate for %s in %s%s_%s_%s = %s'%(name,year,sign,KpiBins[ibin],KpiBins[ibin+1],
                                                                    yieldsBinsPoisson[name][year][sign][ibin])

# -----------------------------------------------------------------------------------------------------------------------
# Bs and Bd datasets
MassDataset = {}
AngDataset = {}

for name in l_speciesName:
    MassDataset[name] = {}
    AngDataset[name] = {}
    for year in l_years:
        MassDataset[name][year] = {}
        AngDataset[name][year] = {}
        for sign in l_signs:
            MassDataset[name][year][sign] = {}
            AngDataset[name][year][sign] = {}
            for ibin in l_bins:
                # Signal datasets
                if name != "Combi" and "Lb2Jpsi" not in name:
                    # -- MASS
                    if name == "Bs": 
                        signalMassModel = SignalMassIpatia("signal_%s_%s_%s_%i"%(name,year,sign,ibin), year, ibin, sign)
                        MassDataset[name][year][sign][ibin] = signalMassModel.sigBs.generate(RooArgSet(Mass),
                                                                                             int(round(yieldsBinsPoisson[name][year][sign][ibin])),
                                                                                             RooFit.Verbose(verbose))
                    if name == "Bd": 
                        signalMassModel = SignalMassIpatia("signal_%s_%s_%s_%i"%(name,year,sign,ibin), year, ibin, sign)
                        MassDataset[name][year][sign][ibin] = signalMassModel.sigBd.generate(RooArgSet(Mass),
                                                                                             int(round(yieldsBinsPoisson[name][year][sign][ibin])),
                                                                                             RooFit.Verbose(verbose))


                    # -- ANGLES
                    AngModels[name][year][sign].ds.setVal(angParams[name][ibin]["ds"])
                    AngModels[name][year][sign].As2.setVal(angParams[name][ibin]["As2"])
                    AngModels[name][year][sign].CSP.setVal(angParams[name][ibin]["CSP"])
                    AngDataset[name][year][sign][ibin] = AngModels[name][year][sign].model.generate(RooArgSet(CPsi, CTheta, Phi),
                                                                                                    int(round(yieldsBinsPoisson[name][year][sign][ibin])),
                                                                                                    RooFit.Verbose(verbose))
                # Combinatorial background datasets
                if name == "Combi":
                    CombiBkgmodel[year].kbkg.setVal(massParams[name][year][sign][ibin]["k"])
                    MassDataset[name][year][sign][ibin] = CombiBkgmodel[year].massbkg.generate(RooArgSet(Mass),
                                                                                               int(round(yieldsBinsPoisson[name][year][sign][ibin])),
                                                                                               RooFit.Verbose(verbose))
                    AngDataset[name][year][sign][ibin] = CombiBkgmodel[year].model.generate(RooArgSet(CPsi, CTheta, Phi),
                                                                                            int(round(yieldsBinsPoisson[name][year][sign][ibin])),
                                                                                            RooFit.Verbose(verbose))
                # Lambda peaking backgrounds datasets
                if name == "Lb2JpsipK":
                    for key in massParams["Lb2JpsipK"][year][sign][ibin].keys():
                        LbpKmodel.set(key,massParams["Lb2JpsipK"][year][sign][ibin][key])
                    MassDataset[name][year][sign][ibin] = LbpKmodel.mass_model.generate(RooArgSet(Mass),
                                                                                        int(round(yieldsBinsPoisson[name][year][sign][ibin])),
                                                                                        RooFit.Verbose(verbose))
                    print "WARNING:: For %s events, generating angular distributions from combinatorial background PDFs"%(name)
                    AngDataset[name][year][sign][ibin] = CombiBkgmodel[year].model.generate(RooArgSet(CPsi, CTheta, Phi),
                                                                                            int(round(yieldsBinsPoisson[name][year][sign][ibin])),
                                                                                            RooFit.Verbose(verbose))
                if name == "Lb2JpsipPi":
                    for key in massParams["Lb2JpsipPi"][year][sign][ibin].keys():
                        Lbppimodel.set(key,massParams["Lb2JpsipPi"][year][sign][ibin][key])
                    MassDataset[name][year][sign][ibin] = LbpKmodel.mass_model.generate(RooArgSet(Mass),
                                                                                        int(round(yieldsBinsPoisson[name][year][sign][ibin])),
                                                                                        RooFit.Verbose(verbose))
                    print "WARNING:: For %s events, generating angular distributions from combinatorial background PDFs"%(name)
                    AngDataset[name][year][sign][ibin] = CombiBkgmodel[year].model.generate(RooArgSet(CPsi, CTheta, Phi),
                                                                                            int(round(yieldsBinsPoisson[name][year][sign][ibin])),
                                                                                            RooFit.Verbose(verbose))


# -----------------------------------------------------------------------------------------------------------------------
# EMBED THE PEAKING BACKROUNDS
# -----------------------------------------------------------------------------------------------------------------------

def getValidEntries(nVals,nMax):
    if nVals>=nMax: 
        print"ERROR: number of values to draw: %i, larger or equal to the max range: %i"%(nVals,nMax)
        exit(1)
    else :
        print'>>> drawing %i events from out of %i available events in tree'%(nVals,nMax)
    setEntries = set()
    while len(setEntries) <= nVals:
        setEntries.add(int(round(gRandom.Uniform(0,nMax))))
    listEntries = list(setEntries)
    listEntries.sort()
    return listEntries
        
def getValues(name,year,sign,ibin):
    Values = {}
    Values["Mass"] = []
    Values["CPsi"] = []
    Values["CTheta"] = []
    Values["Phi"] = []
    Values["wMC"] = []

    filename = ""
    if _USE_GRID_:
        # input GRID files are available on /lhcb/user/s/sakar/MC/JpsiKst/Bd2JpsiKst/
        filename = "AllPeakingBkgs_KstRange.root"
    else:
        filename = "/zfs_lhcb/Bs2JpsiKst/Toys/Tuples/PeakingBkgs/AllPeakingBkgs_KstRange.root"
    
    file = TFile(filename)
    dummyTree = file.Get("genTree")#file.Get("DecayTree")
    dummyfile = TFile("dummyTmp_File.root","recreate")
    selectionCut = "Kst_892_0_MM > %d && Kst_892_0_MM < %d && %s==1 && Year==%s"%(KpiBins[ibin],KpiBins[ibin+1], 
                                                                                  "sig%s%s"%(name[:2], name[7:]), year)
    if debug: print selectionCut
    tree = dummyTree.CopyTree(selectionCut)
    listEntriesData = getValidEntries(int(round(yieldsBinsPoisson[name][year][sign][ibin])),
                                      int(round(tree.GetEntries())))
    listEntriesMC   = getValidEntries(int(round(gRandom.Poisson(yieldsBinsTrue[name][year][sign][ibin]))),
                                      int(round(tree.GetEntries())))

    for entry in listEntriesData:
        tree.GetEntry(entry)
        Values["Mass"].append(float(tree.B0_MM))
        Values["CPsi"].append(float(tree.helcosthetaL))
        Values["CTheta"].append(float(tree.helcosthetaK))
        Values["Phi"].append(float(tree.B0_Phi))
        Values["wMC"].append(float(1))
        #Values["wMC"].append(float(tree.wMC))

    for entry in listEntriesMC:
        tree.GetEntry(entry)
        Values["Mass"].append(float(tree.B0_MM))
        Values["CPsi"].append(float(tree.helcosthetaL))
        Values["CTheta"].append(float(tree.helcosthetaK))
        Values["Phi"].append(float(tree.B0_Phi))
        Values["wMC"].append(-1.0 *(float(len(listEntriesData))/float(len(listEntriesMC))) )


    file.Close()
    dummyfile.Close()
    os.system("rm dummyTmp_File.root")

    return Values


if doPeakingBkgs:
    DatasetPeakingBkg = {}
    for name in ("Bs2JpsiKK","Bs2Jpsipipi","Bd2Jpsipipi"):
        print"Retrieving %s information for..."%name
        DatasetPeakingBkg[name] = {}
        for year in l_years:
            DatasetPeakingBkg[name][year] = {}
            for sign in l_signs:
                DatasetPeakingBkg[name][year][sign] = {}
                for ibin in l_bins:
                    DatasetPeakingBkg[name][year][sign][ibin] = getValues(name,year,sign,ibin)
                    
# -----------------------------------------------------------------------------------------------------------------------
# DEFINE THE OUTPUTTREE STRUCTURE
# -----------------------------------------------------------------------------------------------------------------------
outputFileName = ""
if doPeakingBkgs:
    OutPutTag += "_withPeakingBkgs"
if nonZeroACPs:
    OutPutTag += "_ACPs_%s"%ACPset

if _USE_GRID_:
    outputFileName = "genData_%s_Exp%i.root"%(OutPutTag,iexp)
else:
    os.system("mkdir /zfs_lhcb/Bs2JpsiKst/Toys/Tuples/%s"%(OutPutTag))
    outputFileName = "/zfs_lhcb/Bs2JpsiKst/Toys/Tuples/%s/genData_%s_Exp%i.root"%(OutPutTag,OutPutTag,iexp)

outputFile = TFile(outputFileName,"RECREATE")
outputTree = TTree("genTree","genTree")

# General flags
iExp = MyStructI()
iExp_br = outputTree.Branch("iExp", AddressOf(iExp,'aint'),"iExp/I") 

# Yields values
trueYield = MyStructI()
trueYield_br = outputTree.Branch("nTrue", AddressOf(trueYield,'aint'),"nTrue/I") 

# Specie flags
sigCombi = MyStructI()
sigBs = MyStructI()
sigBd = MyStructI()
sigLbpK = MyStructI()
sigLbppi = MyStructI()
sigBsKK = MyStructI()
sigBspipi = MyStructI()
sigBdpipi = MyStructI()
sigCombi_br = outputTree.Branch("sigCombi", AddressOf(sigCombi,'aint'),"sigCombi/I") 
sigBs_br = outputTree.Branch("sigBs", AddressOf(sigBs,'aint'),"sigBs/I") 
sigBd_br = outputTree.Branch("sigBd", AddressOf(sigBd,'aint'),"sigBd/I") 
sigLbpK_br = outputTree.Branch("sigLbpK", AddressOf(sigLbpK,'aint'),"sigLbpK/I") 
sigLbppi_br = outputTree.Branch("sigLbppi", AddressOf(sigLbppi,'aint'),"sigLbppi/I") 
sigBsKK_br = outputTree.Branch("sigBsKK", AddressOf(sigBsKK,'aint'),"sigBsKK/I") 
sigBspipi_br = outputTree.Branch("sigBspipi", AddressOf(sigBspipi,'aint'),"sigBspipi/I") 
sigBdpipi_br = outputTree.Branch("sigBdpipi", AddressOf(sigBdpipi,'aint'),"sigBdpipi/I") 

# Type specification
KpiBin_val = MyStructI()
Year_val = MyStructI()
Kcharge_val = MyStructI()
KpiBin_br = outputTree.Branch("KpiBin", AddressOf(KpiBin_val,'aint'),"KpiBin/I") 
Year_br = outputTree.Branch("Year", AddressOf(Year_val,'aint'),"Year/I") 
Kcharge_br = outputTree.Branch("Kcharge", AddressOf(Kcharge_val,'aint'),"Kcharge/I") 

# Variables
Mass_val = MyStructF()
CPsi_val = MyStructF()
CTheta_val = MyStructF()
Phi_val = MyStructF()
wMC_val = MyStructF()
Mass_br = outputTree.Branch(Mass.GetName(), AddressOf(Mass_val,'afloat'),Mass.GetName()+"/F") 
CPsi_br = outputTree.Branch(CPsi.GetName(), AddressOf(CPsi_val,'afloat'),CPsi.GetName()+"/F") 
CTheta_br = outputTree.Branch(CTheta.GetName(), AddressOf(CTheta_val,'afloat'),CTheta.GetName()+"/F") 
Phi_br = outputTree.Branch(Phi.GetName(), AddressOf(Phi_val,'afloat'),Phi.GetName()+"/F") 
wMC_br = outputTree.Branch("wMC", AddressOf(wMC_val,'afloat'),"wMC/F") 

# -----------------------------------------------------------------------------------------------------------------------
# FILL THE OUTPUTTREE 
# -----------------------------------------------------------------------------------------------------------------------

if doPeakingBkgs:
    # ------ Retrieve the MC ntuple ----------
    for name in ("Bs2JpsiKK","Bs2Jpsipipi","Bd2Jpsipipi"):
        for year in l_years:
            for sign in l_signs:
                for ibin in l_bins:
                    for entry in range(len(DatasetPeakingBkg[name][year][sign][ibin]["Mass"])):
                        trueYield.aint = yieldsBinsTrue[name][year][sign][ibin]
                        iExp.aint = iexp
                        if sign=="neg": Kcharge_val.aint = -1
                        else: Kcharge_val.aint = +1
                        KpiBin_val.aint = ibin
                        if year=="2011": Year_val.aint = 2011
                        else: Year_val.aint = 2012
                        if name=="Combi": sigCombi.aint = 1
                        else: sigCombi.aint = 0
                        if name=="Bs": sigBs.aint = 1
                        else: sigBs.aint = 0
                        if name=="Bd": sigBd.aint = 1
                        else: sigBd.aint = 0
                        if name=="Lb2JpsipK": sigLbpK.aint = 1
                        else: sigLbpK.aint = 0
                        if name=="Lb2JpsipPi": sigLbppi.aint = 1
                        else: sigLbppi.aint = 0
                        if name=="Bs2JpsiKK": sigBsKK.aint = 1
                        else: sigBsKK.aint = 0
                        if name=="Bs2Jpsipipi": sigBspipi.aint = 1
                        else: sigBspipi.aint = 0
                        if name=="Bd2Jpsipipi": sigBdpipi.aint = 1
                        else: sigBdpipi.aint = 0
                        Mass_val.afloat = DatasetPeakingBkg[name][year][sign][ibin]["Mass"][entry]
                        CPsi_val.afloat = DatasetPeakingBkg[name][year][sign][ibin]["CPsi"][entry]
                        CTheta_val.afloat = DatasetPeakingBkg[name][year][sign][ibin]["CTheta"][entry]
                        Phi_val.afloat = DatasetPeakingBkg[name][year][sign][ibin]["Phi"][entry]
                        wMC_val.afloat = DatasetPeakingBkg[name][year][sign][ibin]["wMC"][entry]
                        
                        outputTree.Fill()
                    # end of loop over map entries
                # end of loop over bins
            # end of loop over sign
        # end of loop over years 
    # end of loop over species
# end of condition on peaking bkgs
   
# ------ Retrieve the generated events ----------                                                                         
for name in l_speciesName:
    for year in l_years:
        for sign in l_signs:
            for ibin in l_bins:
                for entry in range(MassDataset[name][year][sign][ibin].numEntries()):
                    trueYield.aint = yieldsBinsTrue[name][year][sign][ibin]
                    iExp.aint = iexp
                    if sign=="neg": Kcharge_val.aint = -1
                    else: Kcharge_val.aint = +1
                    KpiBin_val.aint = ibin
                    if year=="2011": Year_val.aint = 2011
                    else: Year_val.aint = 2012
                    if name=="Combi": sigCombi.aint = 1
                    else: sigCombi.aint = 0
                    if name=="Bs": sigBs.aint = 1
                    else: sigBs.aint = 0
                    if name=="Bd": sigBd.aint = 1
                    else: sigBd.aint = 0
                    if name=="Lb2JpsipK": sigLbpK.aint = 1
                    else: sigLbpK.aint = 0
                    if name=="Lb2JpsipPi": sigLbppi.aint = 1
                    else: sigLbppi.aint = 0
                    if name=="Bs2JpsiKK": sigBsKK.aint = 1
                    else: sigBsKK.aint = 0
                    if name=="Bs2Jpsipipi": sigBspipi.aint = 1
                    else: sigBspipi.aint = 0
                    if name=="Bd2Jpsipipi": sigBdpipi.aint = 1
                    else: sigBdpipi.aint = 0
                    Mass_val.afloat = float((MassDataset[name][year][sign][ibin].get(entry).find(Mass.GetName())).getVal())
                    CPsi_val.afloat = float((AngDataset[name][year][sign][ibin].get(entry).find(CPsi.GetName())).getVal())
                    CTheta_val.afloat = float((AngDataset[name][year][sign][ibin].get(entry).find(CTheta.GetName())).getVal())
                    Phi_val.afloat = float((AngDataset[name][year][sign][ibin].get(entry).find(Phi.GetName())).getVal())
                    wMC_val.afloat = 1.0

                    outputTree.Fill()
                # end of loop over tree entries
            # end of loop over bins
        # end of loop over sign
    # end of loop over year
# end of loop over names

outputTree.Write("",TObject.kOverwrite)
outputFile.Close()


########################################################################################
##################################               #######################################
##################################  END OF FILE  #######################################
##################################               #######################################
########################################################################################
