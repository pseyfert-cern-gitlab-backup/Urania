from ROOT import *
from Urania import *
AccesPackage('Bs2MuMu')
from smartpyROOT import *
from Bs2JpsiPhiParams.Selections import cutswide
from fiducial import *

gSystem.Load('libMathMore')
gROOT.ProcessLine('.L $URANIAROOT/src/RooIpatia2.cxx+')
gROOT.ProcessLine('.L $SOMEMASSMODELSROOT/src/RooJohanCruijff.cxx++')

# To prevent ROOT from showing the canvas
gROOT.SetBatch()

#-------------------------------------------------------------------------------------------------
# Mass limits
MASS_MIN = 470.
MASS_MAX = 525.

#-------------------------------------------------------------------------------------------------
# Arguments to parse => trigger category + bin number
import argparse
categories = ['TIS_', 'TOS1_', 'TOS2_']
parser = argparse.ArgumentParser(description='fit')
parser.add_argument('category', type=str, choices = categories,
                    help='Trigger category' )
parser.add_argument('bin', type=int, choices=[0,1,2,3,4,5,6,7,8,9],
                   help='Bins go from 1 to 9')
args = parser.parse_args()

# The selection is taken from the parsed information
cuts = SEL[args.category] + BDTplusMuID_cuts(args.category)[args.bin]
#-------------------------------------------------------------------------------------------------

TUPLE_PATH = '~/eos/lhcb/wg/RD/K0SMuMu/NEW/MC/'
mvar = 'KS0_MM'

uselessfile = TFile( 'uselessfile.root', 'RECREATE' )
#fpipi = TFile(TUPLE_PATH + 'Kspipi_MC2012_mcMatch_MVA.root')
#itree = fpipi.Get('DecayTree').CopyTree(cuts)
fmumu = TFile(TUPLE_PATH + 'Ksmumu_StrippedMC2012_mcMatch_MVA.root')
uselessfile.cd()
print '-- COPYING TREE'
itree = fmumu.Get('DecayTree').CopyTree(cuts)

#-------------------------------------------------------------------------------------------------
# IPATIA
mass  = RooRealVar(mvar, mvar, MASS_MIN, MASS_MAX, 'MeV/c^{2}')
a2    = RooRealVar('a2', 'a2', 200.)
a     = RooRealVar('a', 'a' , 2, 1, 10)#2,1,10
n     = RooRealVar('n', 'n', 1., 0.8, 10)#1.,0.8,10
n2    = RooRealVar('n2','n2', 1)
ipa_s = RooRealVar('ipa_s', 'ipa_s', 0.1, 7) #0.1, 7
ipa_m = RooRealVar('ipa_m', 'ipa_m', 491, 501)#491,501
beta  = RooRealVar('beta', 'beta', 0)
zeta  = RooRealVar('zeta', 'zeta', 6.21949e-01)
l     = RooRealVar('l', 'l', -4, -6, -2.)

ipatia = RooIpatia2('bullshit_miriam','bullshit_miriam',mass,l,zeta,beta,ipa_s,ipa_m,a,n,a2,n2)

#-------------------------------------------------------------------------------------------------
# CONSTRAINTS
import ROOT
from ROOT.RooFit import RooConst
a_cnstr     = RooGaussian( 'a_cnstr', 'a_cnstr', a, RooConst(2), RooConst(0.25) )
n_cnstr     = RooGaussian( 'n_cnstr', 'n_cnstr', n, RooConst(2), RooConst(0.25) )
ipa_s_cnstr = RooGaussian( 'ipa_s_cnstr', 'ipa_s_cnstr', ipa_s, RooConst(3.78), RooConst(0.35) )
ipa_m_cnstr = RooGaussian( 'ipa_m_cnstr', 'ipa_m_cnstr', ipa_m, RooConst(497.78), RooConst(4.1) )
l_cnstr     = RooGaussian( 'l_cnstr', 'l_cnstr', l, RooConst(-3.91), RooConst(0.39) )
CONSTRAINTS = RooArgSet(a_cnstr, n_cnstr, ipa_s_cnstr, ipa_m_cnstr, l_cnstr)

#-------------------------------------------------------------------------------------------------
# FIT
data = RooDataSet( 'Data', 'Data', itree, RooArgSet( mass ) )

ipatia.fitTo(data, RooFit.Minos(1), RooFit.ExternalConstraints(CONSTRAINTS), RooFit.Offset(kTRUE))

kCanvas = TCanvas()
kCanvas.Divide(1, 2)
fr = mass.frame()
data.plotOn(fr, RooFit.Binning(100))
ipatia.plotOn(fr,RooFit.LineColor(kOrange))

pad = kCanvas.cd( 1 )
pad.SetPad( 0.01,0.28,0.99,0.99 )
fr.Draw()

pad = kCanvas.cd( 2 )
pad.SetPad( 0.01,0.01,0.99,0.23 )
pull = fr.pullHist()
pull.GetXaxis().SetLabelSize(0.15)
pull.GetYaxis().SetLabelSize(0.15)
pull.GetYaxis().SetNdivisions(504)
pull.SetMinimum( -5 )
pull.SetMaximum( +5 )
pull.GetXaxis().SetRangeUser( MASS_MIN, MASS_MAX )
botline = TLine( MASS_MIN, -3., MASS_MAX, -3. )
midline = TLine( MASS_MIN,  0., MASS_MAX,  0. )
topline = TLine( MASS_MIN, +3., MASS_MAX, +3. )
pull.Draw()
for i, line in enumerate([ botline, midline, topline ]):
     line.SetLineColor( kRed )
     if i != 1:
          line.SetLineStyle( kDotted )
     line.Draw('SAME')

#-------------------------------------------------------------------------------------------------
# Saves the output values on a python file
pars = RooArgList( a, a2, n, n2, ipa_s, ipa_m, beta, zeta, l )
ofile = open( 'KsMuMuPeakPars.py', 'at+' )
ofile.write( 'class KsMuMuIpaPars_' + args.category + str(args.bin) + ':\n' )
for i in xrange(len(pars)):
     var = pars.at(i)
     ofile.write( '\t' + var.GetName() + ' = ' + str(var.getVal()) + '\n' )
ofile.write('\n')
ofile.close()

# Because maybe one can see the plot before continuing
#raw_input('Press enter to continue')

ofile = TFile( 'OutputPlots.root', 'UPDATE' )
kCanvas.Write(args.category + str(args.bin))
ofile.Close()
