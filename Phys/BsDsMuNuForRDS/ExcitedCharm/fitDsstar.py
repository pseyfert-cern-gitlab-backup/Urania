from BsDsMuNuForRDS.DataRetrieval import *
import sys, os
from ROOT import TFile, TTree, gROOT, gDirectory, RooStats, RooAbsData
from ROOT import RooFit, RooRealVar, RooDataSet, RooArgList, RooFormulaVar
from ROOT import RooEffProd, RooCBShape, RooArgSet, RooExponential, RooExtendPdf
from ROOT import RooAddPdf, TCanvas, kBlue, kGreen, kRed, RooWorkspace, RooNovosibirsk, RooBukinPdf
RooWorkspace.rfimport = getattr(RooWorkspace, 'import')
RooWorkspace.rfprint  = getattr(RooWorkspace, 'Print')
gROOT.SetBatch(True)
gROOT.ProcessLine('.x ~/lhcbStyle.C')
RooAbsData.setDefaultStorageType(RooAbsData.Tree)

# Some settings
dataTag  = 'MC_AllNeutrals'
polarity = 'MagUp'
tName    = "B2DsMuNuTuple"
sigFrac = 8.0/23.0

# Get the chain
#c = getProcessedChain(dataTag, polarity)#, "Dsstar")
#c.Print()
# Import the DataSet file which has already been created by another script.
# RDs_DataSet_MC_AllNeutrals_MagUp_DsstarNoFeedDown.root
cutName = 'DsstarNoFeedDown'
inFileName = "RDs_DataSet_%s_%s_%s.root" %(dataTag, polarity, cutName)
inFile = TFile.Open(inFileName)
w = inFile.Get('RDs_Workspace')
w.Print()
rdsName = 'rds_mass' 
rds_mass = w.data(rdsName)
rds_mass.Print()
rv_mass = w.var('hDsMuMassFirstG04')
rv_mass.Print

# And also the other parameters we wish to keep or cut on.
#rv_mass     = RooRealVar("hDsMuMassFirstG04", "hDsMuMassFirstG04", 1950, 2600)
rv_mass.setRange("AllRange", 1950, 2600)
#rv_isGamma1InCone = RooRealVar("isGamma1InCone", "isGamma1InCone", 0, 1)
#rv_isGamma2 = RooRealVar("isGamma2InCone", "isGamma2InCone", 0, 1)
#rv_MM2      = RooRealVar("MM2", "MM2", -20e6, 12e6)
#rv_Emu      = RooRealVar("Emu", "Emu", 0, 3.5e3)
#rv_q2       = RooRealVar("q2", "q2", -20e6, 13e6)

# Now import the RooDataSet from the tree.
# Apply a cut to get rid of events with no photons.
#myCut = "(isGamma1InCone==1 && hDsMuMassFirstG04 > 1950 && hDsMuMassFirstG04 < 2600 && MM2 > -20e6 && MM2 < 12e6 && Emu < 3.5e3 && q2 > -20e6 && q2 < 13e6)"
#sys.exit()
#dataSetVars = RooArgSet(rv_mass, rv_MM2, rv_Emu, rv_q2, rv_isGamma1InCone)
#rds_mass = RooDataSet("rds_mass", "rds_mass",
#                      dataSetVars,
#                      RooFit.Import(c),
#                      RooFit.Cut(myCut))

print 'Imported RooDataSet'
initialConditionsDict = {
    'Data_AllNeutrals' : { 'thMass'   : 2010
                           ,'thSigma' : 22
                           ,'c'       : -0.007
                           ,'sigFrac' : 0.07 }
    ,'MC_AllNeutrals'  : { 'thMass'   : 2000
                           ,'thSigma' : 24
                           ,'c'       : -0.01
                           ,'sigFrac' : 0.35 }
    }


# Now ones for the PDFs.
rv_mean    = RooRealVar("Mean", "mean", 2112.1, 2109.1, 2115.1, "MeV/c^{2}")
rv_sigma   = RooRealVar("Sigma", "sigma", 8, 5, 60, "MeV/c^{2}")
rv_alpha1  = RooRealVar("alpha1", "alpha1", 1.6, 0., 3.)
rv_n1      = RooRealVar("n1", "n1", 7., 1., 20.)
rv_alpha2  = RooRealVar("alpha2", "alpha2", -2.0, -15.0, 0.0)
rv_n2      = RooRealVar("n2", "n2", 15., 1., 60.)
rv_frac    = RooRealVar("frac","frac",0.5,0.,1.)

# Declare the PDFs
rpdf_sig  = RooCBShape("sig2", "signal CB", rv_mass, rv_mean, rv_sigma, rv_alpha2, rv_n2)

rv_c      = RooRealVar("c", "c", initialConditionsDict[dataTag]['c'],
                       -1., 0.)
rpdf_expo = RooExponential("expo", "exponential", rv_mass, rv_c)

rv_thMass    = RooRealVar("thMass", "thMass", initialConditionsDict[dataTag]['thMass'],
                          1970, 2050, "MeV/c^{2}")
rv_thSigma   = RooRealVar("thSigma", "thSigma", initialConditionsDict[dataTag]['thSigma'],
                          5, 30, "MeV/c^{2}")
rv_eff       = RooFormulaVar("eff","0.5*(TMath::Erf((hDsMuMassFirstG04-thMass)/thSigma)+1)",
                             RooArgList(rv_mass,rv_thMass,rv_thSigma))
rpdf_bkg     = RooEffProd("modelEff", "model with efficiency", rpdf_expo, rv_eff)

# A Novosibirsk function for the background.
#rv_Nmean  = RooRealVar("Nmean", "Nmean", 2024, 2000, 2500)
#rv_Nsigma = RooRealVar("Nsigma", "Nsigma", 40, 0, 1000)
#rv_Ntail  = RooRealVar("Ntail", "Ntail", -2.0, -5.00, 0.00)
#rpdf_NovosibirskBkg = RooNovosibirsk("PDF_NovoBkg", "PDF_NovoBkg", rv_mass,
#                                     rv_Nmean, rv_Nsigma, rv_Ntail)

rv_Bmean  = RooRealVar("Bmean",  "Bmean",  2024, 2000, 2500)
rv_Bsigma = RooRealVar("Bsigma", "Bsigma", 40, 0, 1000)
rv_Brho1  = RooRealVar("Brho1",  "Brho1",  1.5, -5.00, 5.00)
rv_Brho2  = RooRealVar("Brho2",  "Brho2",  0.0, -5.00, 5.00)
rv_Bxi    = RooRealVar("Bxi",    "Bxi", 0.12, -2.0, 2.0)
rpdf_BukinBkg = RooBukinPdf("PDF_BukinBkg", "PDF_BukinBKG", rv_mass,
                            rv_Bmean, rv_Bsigma, rv_Bxi, rv_Brho1, rv_Bxi)

rpdf_bkg = rpdf_BukinBkg
#sys.exit()

# Now vars for the yields.
entries = rds_mass.numEntries()
sigFrac = initialConditionsDict[dataTag]['sigFrac']
rv_nSig = RooRealVar("N_{sig}", "number of signal", sigFrac*entries, entries*0.0, 1.0*entries)
#rv_nSig.setError( float(entries)**0.5 )
rv_nBkg = RooRealVar("N_{bkg}", "number of background", (1-sigFrac)*entries,
                     entries*0.0, 1.00*entries)
#rv_nBkg.setError(float(entries)**0.5)

# Make the extended PDF
rpdf_sig_E    = RooExtendPdf("sig_E","Extended signal PDF",rpdf_sig,rv_nSig)
rpdf_bkg_E    = RooExtendPdf("bkg_E","Extended background PDF",rpdf_bkg,rv_nBkg)
rpdf_totalPDF = RooAddPdf("total", "right sign pdf", RooArgList(rpdf_sig_E,rpdf_bkg_E))

# Make the frame and plot the data
plot = rv_mass.frame(RooFit.Title("M(D#gamma)"))
rds_mass.plotOn(plot)

isTest = True
if isTest:
    c = TCanvas('c', 'c', 800, 600)
    c.cd()
    rpdf_totalPDF.plotOn(plot,RooFit.LineColor(kBlue))
    rpdf_totalPDF.plotOn(plot,RooFit.Components("sig_E"),RooFit.LineColor(kGreen+3))
    rpdf_totalPDF.plotOn(plot,RooFit.Components("bkg_E"),RooFit.LineColor(kRed))
    plot.Draw()
    c.SaveAs('test.eps')
    sys.exit()

#rfr_result = rpdf_totalPDF.fitTo(rds_mass, RooFit.Extended(True), RooFit.Minos(True),
#                                 RooFit.NumCPU(4), RooFit.Strategy(2), RooFit.Save(True),
#                                 RooFit.Verbose(False),RooFit.Timer(True))
rfr_result = rpdf_totalPDF.fitTo(rds_mass, RooFit.Extended(True),
                                 RooFit.Save(True),
                                 RooFit.Verbose(False),RooFit.Timer(True))
rpdf_totalPDF.plotOn(plot,RooFit.LineColor(kBlue))
rpdf_totalPDF.plotOn(plot,RooFit.Components("sig_E"),RooFit.LineColor(kGreen+3))
rpdf_totalPDF.plotOn(plot,RooFit.Components("bkg_E"),RooFit.LineColor(kRed))

# Save a TCanvas of the fit.
#isTest = True
#if isTest:
#    c = TCanvas('c', 'c', 800, 600)
#    c.cd()
#    plot.Draw()
#    c.SaveAs('test.eps')
#    sys.exit()
    
# Save all the objects in a workspace.
w = RooWorkspace('RDs_Workspace', 'RDs_Workspace')
w.rfimport(rpdf_totalPDF)
w.rfimport(rds_mass)
w.rfimport(rfr_result)
w.rfimport(rv_mass)
fNamesWorkspace = "RDs_FitResult_%s_%s.root" %(dataTag, polarity)
w.writeToFile(fNamesWorkspace)

# Now make some sWeights.
fNamesWeights = "RDs_sWeights_%s_%s.root" %(dataTag, polarity)
f_out = TFile(fNamesWeights, 'recreate')
sw_data = RooStats.SPlot('sData', 'An SPlot',
                         rds_mass, rpdf_totalPDF,
                         RooArgList(rv_nSig, rv_nBkg))
rds_mass.tree().Print()
rds_mass.tree().Write()
f_out.Close()
print '*'*100
