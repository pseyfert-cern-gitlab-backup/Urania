# Run "SetupProject Brunel" first
# and then "python -i efficiencyRatio.py"
from ROOT import TH2D, TFile, TRandom3
import GaudiPython
import GaudiKernel.SystemOfUnits as units
from math import sqrt

f2010 = TFile("ratio2010.root")
hRatio2010 = f2010.Get("Ratio")

f2011 = TFile("ratio2011.root")
hRatio2011 = f2011.Get("Ratio")

# Create a new histogram with the spectrum from the MC
hSpectrumMC = hRatio2011.Clone("SpectrumMC")
hSpectrumMC.Reset()

def fillSpectrum( p, eta ) :
    p /= units.GeV
    hSpectrumMC.Fill(p, eta)

def effRatioDataOverMC( p, eta, year="2011" ) :
    p /= units.GeV
    if( year == "2011") : hRatio = hRatio2011
    elif( year == "2010" ) : hRatio = hRatio2010
    i = hRatio.GetXaxis().FindBin(p)
    j = hRatio.GetYaxis().FindBin(eta)
    # Protect against under and overflow bins
    if( i == 0 ) : i = 1
    if( j == 0 ) : j = 1
    if( i > hRatio.GetNbinsX() ) : i = hRatio.GetNbinsX()
    if( j > hRatio.GetNbinsY() ) : j = hRatio.GetNbinsY()
    ratio = hRatio.GetBinContent( i, j )
    return ratio

def errRatioDataOverMC( p, eta, year="2011" ) :
    p /= units.GeV
    if( year == "2011") : hRatio = hRatio2011
    elif( year == "2010" ) : hRatio = hRatio2010
    i = hRatio.GetXaxis().FindBin(p)
    j = hRatio.GetYaxis().FindBin(eta)
    # Protect against under and overflow bins
    if( i == 0 ) : i = 1
    if( j == 0 ) : j = 1
    if( i > hRatio.GetNbinsX() ) : i = hRatio.GetNbinsX()
    if( j > hRatio.GetNbinsY() ) : j = hRatio.GetNbinsY()
    error = hRatio.GetBinError( i, j )
    return error

def effRatioDataOverMC_Smeared( p, eta, seed, year="2011" ) :
    ratio = effRatioDataOverMC( p, eta, year )
    error = errRatioDataOverMC( p, eta, year )
    rnd = TRandom3()
    seed += int(abs(ratio-1.0)*1E5) # Different seed in every bin
    rnd.SetSeed(seed) 
    smearedRatio = rnd.Gaus(ratio, error)
    return smearedRatio

def drawEffRatioTable( year="2011" ) :
    from ROOT import gROOT, gStyle
    gROOT.ProcessLine(".x myStyle.C")
    if( year == "2011") : hRatio = hRatio2011
    elif( year == "2010" ) : hRatio = hRatio2010
    hRatio.SetMarkerSize(1.4)
    hRatio.GetYaxis().SetTitleOffset(0.7);
    hRatio.Draw("COLZ");
    hRatio.Draw("TEXTE SAME");

def drawSpectrumMyMC() :
    from ROOT import gROOT, gStyle
    gROOT.ProcessLine(".x myStyle.C")
    hSpectrumMC.SetMarkerSize(1.4)
    hSpectrumMC.GetYaxis().SetTitleOffset(0.7);
    hSpectrumMC.Draw("COLZ");
    hSpectrumMC.Draw("TEXTE SAME");

def totalStatError( year="2011" ) :
    totWeight = 0.0
    totError2 = 0.0
    for j in range(1,hSpectrumMC.GetNbinsY()+1) :
        for i in range(1,hSpectrumMC.GetNbinsX()+1) :
            weight = hSpectrumMC.GetBinContent(i,j)
            totWeight += weight
            p = (hSpectrumMC.GetXaxis().GetBinCenter(i))*units.GeV
            eta = hSpectrumMC.GetYaxis().GetBinCenter(j) 
            error = errRatioDataOverMC( p, eta, year )
            totError2 += pow(weight*error, 2)
    return sqrt(totError2)/totWeight

def totalEfficiencyRatio( year="2011" ) :
    totWeight = 0.0
    totRatio  = 0.0
    for j in range(1,hSpectrumMC.GetNbinsY()+1) :
        for i in range(1,hSpectrumMC.GetNbinsX()+1) :
            weight = hSpectrumMC.GetBinContent(i,j)
            totWeight += weight
            p = hSpectrumMC.GetXaxis().GetBinCenter(i)*units.GeV
            eta = hSpectrumMC.GetYaxis().GetBinCenter(j) 
            ratio = effRatioDataOverMC( p, eta, year )
            totRatio += weight*ratio
    return totRatio/totWeight

def totalStatErrorFromSpectrum(hMySpectrum, year="2011" ) :
    totWeight = 0.0
    totError2 = 0.0
    for j in range(1,hMySpectrum.GetNbinsY()+1) :
        for i in range(1,hMySpectrum.GetNbinsX()+1) :
            weight = hMySpectrum.GetBinContent(i,j)
            totWeight += weight
            p = (hMySpectrum.GetXaxis().GetBinCenter(i))*units.GeV
            eta = hMySpectrum.GetYaxis().GetBinCenter(j) 
            error = errRatioDataOverMC( p, eta, year )
            totError2 += pow(weight*error, 2)
    return sqrt(totError2)/totWeight

def totalEfficiencyRatioFromSpectrum(hMySpectrum, year="2011") :
    totWeight = 0.0
    totRatio  = 0.0
    for j in range(1,hMySpectrum.GetNbinsY()+1) :
        for i in range(1,hMySpectrum.GetNbinsX()+1) :
            weight = hMySpectrum.GetBinContent(i,j)
            totWeight += weight
            p = hMySpectrum.GetXaxis().GetBinCenter(i)*units.GeV
            eta = hMySpectrum.GetYaxis().GetBinCenter(j) 
            ratio = effRatioDataOverMC( p, eta, year )
            totRatio += weight*ratio
    return totRatio/totWeight
