# This example script calculates the efficiency over the phase space 
# of four-body decay D0->K+K-pi+pi-. The phase space variables are 
#   * M(KK)
#   * M(pipi)
#   * KK helicity angle (thetaK)
#   * PiPi helicity angle (thetaPi)
#   * Angle phi between pipi and KK planes
# In fact, this script only parametrises the 2D M(KK) vs M(pipi)
# distribution and each of the 1D angular distributions, separately. 
# The total efficiency is (probably) well represented by the product of 
# those distributions. If not, the full 5D kernel density correction 
# can be done, but not attempted here (yet?). 


from ROOT import gSystem, gStyle, gROOT, RooRealVar

gSystem.Load("../lib/libMeerkat.so")

from ROOT import OneDimPhaseSpace, ParametricPhaseSpace, CombinedPhaseSpace
from ROOT import BinnedKernelDensity, PolynomialDensity
from ROOT import TFile, TNtuple, TCanvas, TH2F, TH1F, TMath

# Masses of final state particles
md = 1865.e-3
mk = 498.e-3
mpi = 139.e-3

# Numbers of events to read
full_events = 2000000
cut_events = 200000

# 1D angular phase spaces
thk_phsp  = OneDimPhaseSpace("ThKPhsp", -1., 1.)
thpi_phsp = OneDimPhaseSpace("ThPiPhsp", -1., 1.)
phi_phsp =  OneDimPhaseSpace("PhiPhsp", -TMath.Pi(), TMath.Pi() )

# 1D m(KK) phase space 
mkk_phsp =  OneDimPhaseSpace("MKKPhsp", 2*mk, md-2*mpi)
# 2D m(pipi) vs M(KK) phase space
#   The phase space has triangular shape, 
#   with m(pipi) ranging from 2m(pi) to m(D)-2m(KK)
mm_phsp = ParametricPhaseSpace("MMPhsp", mkk_phsp, "2.*%f" % mpi, "%f-x" % md, 2.*mpi, md-2.*mk)

# Combined 5D phase space ( M(pipi)*M(KK)*thetaK*thetaPi*phi )
phsp = CombinedPhaseSpace("Phsp", mm_phsp, thk_phsp, thpi_phsp, phi_phsp)

# Read generator-level MC sample (pure phase space)
f = TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/user/p/poluekt/D2HHHH/d2kkpipi_all.root")
ntuple = gROOT.FindObject("nt")

# Create kernel PDF from the phase space sample
mm_phsp_pdf = BinnedKernelDensity("MMPhspPDF", 
                          mm_phsp, 
                          ntuple,        # Input ntuple
                          "mkk","mpipi", # Variables to use
                          100, 100,      # Number of bins
                          0.025, 0.025,  # Kernel width
                          0,             # Approximation PDF (0 for flat approximation)
                          2*full_events, # Sample size for MC convolution (0 for binned convolution)
                          full_events,   # Sample size to read from the ntuple (0 for all events)
                         )

f.Close()

# Read reconstructed MC sample (after the reconstruction+cuts) for efficiency estimation
f = TFile.Open("root://eoslhcb.cern.ch//eos/lhcb/user/p/poluekt/D2HHHH/d2kkpipi_cut.root")
ntuple = gROOT.FindObject("nt")

# Create kernel PDF from the reconstructed MC sample
# Use generator-level distribution as the approximation PDF
mm_cut_pdf = BinnedKernelDensity("MMCutPDF", 
                          mm_phsp, 
                          ntuple, # Input ntuple
                          "mkk","mpipi",# Variables to use
                          100, 100,     # Number of bins
                          0.04, 0.04,   # Kernel width
                          mm_phsp_pdf,  # Approximation PDF (0 for flat approximation)
                          2*full_events,# Sample size for MC convolution (0 for binned convolution)
                          cut_events    # Sample size to read from the ntuple (0 for all events)
                         )

# ThetaK 1D distribution is fitted with polynomial
thk_cut_pdf = PolynomialDensity("ThKCutPDF", 
                          thk_phsp, 
                          2, 
                          ntuple,   # Input ntuple
                          "thk",     # Variables to use
                          cut_events
                         )

# ThetaPi 1D distribution is fitted with polynomial
thpi_cut_pdf = PolynomialDensity("ThPiCutPDF", 
                          thpi_phsp, 
                          2, 
                          ntuple,   # Input ntuple
                          "thpi",   # Variables to use
                          cut_events
                         )

# Phi 1D distribution is fitted with polynomial
phi_cut_pdf = PolynomialDensity("PhiCutPDF", 
                          phi_phsp, 
                          2, 
                          ntuple,   # Input ntuple
                          "phi",    # Variables to use
                          cut_events
                         )

thk_data   = TH1F("thk_data",   "cos(KK helicity)", 100, -1., 1.)
thpi_data  = TH1F("thpi_data",  "cos(pipi helicity)", 100, -1., 1.)
phi_data   = TH1F("phi_data",   "phi", 100, -TMath.Pi(), TMath.Pi())

ntuple.Project("thk_data","thk","","",cut_events)
ntuple.Project("thpi_data","thpi","","",cut_events)
ntuple.Project("phi_data","phi","","",cut_events)

thk_data.SetDirectory(0)
thpi_data.SetDirectory(0)
phi_data.SetDirectory(0)

f.Close()

mm_phsp_hist = TH2F("mm_phsp_hist", "m(KK) vs m(pipi), phase space", 100, 2*mk, md-2*mpi, 100, 2*mpi, md-2*mk)
mm_cut_hist  = TH2F("mm_cut_hist",  "m(KK) vs m(pipi), reconstructed", 100, 2*mk, md-2*mpi, 100, 2*mpi, md-2*mk)
mm_eff_hist  = TH2F("mm_eff_hist",  "m(KK) vs m(pipi), Efficiency", 100, 2*mk, md-2*mpi, 100, 2*mpi, md-2*mk)

thk_hist   = TH1F("thk_hist",   "cos(K helicity)", 100, -1., 1.)
thpi_hist  = TH1F("thpi_hist",  "cos(Pi helicity)", 100, -1., 1.)
phi_hist   = TH1F("phi_hist",   "Phi", 100, -TMath.Pi(), TMath.Pi())

# Project phase space distribution into 2D histogram
mm_phsp_pdf.project(mm_phsp_hist)
# Project reconstructed MC distribution into 2D histogram
mm_cut_pdf.project(mm_cut_hist)

# Project reconstructed MC relative to approximation PDF (which is phase-space MC)
# into the 2D histogram. Since approximation PDF is phase-space MC (before all the cuts), 
# the resulting distribution is proportional to efficiency 
mm_cut_pdf.setFractionalMode(True)
mm_cut_pdf.project(mm_eff_hist)

# Project 1D angular distributions
thk_cut_pdf.project(thk_hist)
thpi_cut_pdf.project(thpi_hist)
phi_cut_pdf.project(phi_hist)

gStyle.SetOptStat(0)

canvas = TCanvas("canvas", "d2fourbody", 750, 500)

canvas.Divide(3, 2)

canvas.cd(1)
mm_phsp_hist.Draw("zcol")

canvas.cd(2)
mm_cut_hist.Draw("zcol")

canvas.cd(3)
mm_eff_hist.Draw("zcol")

canvas.cd(4)
thk_data.SetMinimum(0.)
thk_data.Draw()
thk_hist.Scale( thk_data.GetSumOfWeights() / thk_hist.GetSumOfWeights() )
thk_hist.SetLineColor(2)
thk_hist.SetMinimum(0.)
thk_hist.Draw("same")

canvas.cd(5)
thpi_data.SetMinimum(0.)
thpi_data.Draw()
thpi_hist.Scale( thpi_data.GetSumOfWeights() / thpi_hist.GetSumOfWeights() )
thpi_hist.SetLineColor(2)
thpi_hist.Draw("same")

canvas.cd(6)
phi_data.SetMinimum(0.)
phi_data.Draw()
phi_hist.Scale( phi_data.GetSumOfWeights() / phi_hist.GetSumOfWeights() )
phi_hist.SetLineColor(2)
phi_hist.Draw("same")

canvas.Print("FourBodyPhaseSpace.png")
