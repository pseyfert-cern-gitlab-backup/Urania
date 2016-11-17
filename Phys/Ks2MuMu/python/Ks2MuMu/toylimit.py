from Urania import *
AccessPackage("Bs2MuMu")
import ROOT as rt
from ROOT import RooFit as rf
import TheTable
from constrain_funcs import *
from fiducial import *
from bisect import *
import priormcmc1 as PRIOR
from Urania import PDG
from collections import OrderedDict
import sys
sys.path.append('./FIT_2012')

# Loads the lhcb style for the plots 
rt.gROOT.ProcessLine( '.x lhcbStyle.C' )

# Loads the functions used in the fit
rt.gROOT.ProcessLine('.L $URANIAROOT/src/RooIpatia2.cxx++')
rt.gROOT.ProcessLine('.L $URANIAROOT/src/RooAmorosoPdf.cxx++')
rt.gROOT.ProcessLine('.L $SOMEMASSMODELSROOT/src/RooPowerLaw.cxx++')

COMBINE_2011 = 1

#-----------------------------------------------------------------------------
# Range for the dimuon mass
MASS_MIN  = 465.
BLIND_MIN = 492.
BLIND_MAX = 504.
MASS_MAX  = 600.
#-----------------------------------------------------------------------------

# Defines the bins for each category. This list determines the bins that
# will be fitted.
categories = [ 'TIS_', 'TOS1_', 'TOS2_' ]
BINNING = OrderedDict(
    #[('TOS1_', range(3,10))]
    #[('TOS2_', range(1,10))]
    #[('TIS_' , range(1,10))]
    [('TOS1_', range(3,10)),
    ('TOS2_', range(3,10)),
    ('TIS_' , range(3,10))]
    )

# Fitting variable and ranges
Mass = rt.RooRealVar('KS0_MM', 'KS0_MM', MASS_MIN, MASS_MAX)
category =  rt.RooCategory('sample',  'sample')
Mass.setRange('all', Mass.getMin(), Mass.getMax() )
Mass.setRange('lsb', Mass.getMin(), BLIND_MIN     )
Mass.setRange('rsb', BLIND_MAX    , Mass.getMax() )

for key, kbin in BINNING.iteritems():
    for i in kbin:
        category.defineType(key + str(i))

#-----------------------------------------------------------------------------
# Blinds the branching fraction if required. The random blinding factor is
# stored in UnBlindBr, so do not look at it ;).
BR = rt.RooRealVar('BR', 'BR', 10., 0., 30)
prior = rt.RooAmorosoPdf('PRIOR', 'PRIOR' , BR, PRIOR.offset, PRIOR.theta, PRIOR.alpha, PRIOR.beta)

# Defines the constraints for the fit
summaryConstraints = rt.RooArgSet()

Ipa_m_const = {}
Alpha_const = {}
for key, kbin in BINNING.iteritems():
    for i in kbin:
        ix = key + str(i)
        Alpha_const[key + str(i)] = createConst(TheTable.alpha[ix]*1e09, TheTable.s_alpha_corr[ix]*1e09, 'alphaconst' + ix)
        summaryConstraints.add(Alpha_const[key + str(i)][-1])
if COMBINE_2011:
    summaryConstraints.add(prior)

# Number of events for each generation
NEVTS = 90000

import convresults
initialValues = { kw: getattr( convresults, kw ) for kw in dir(convresults) if not kw.startswith( '__' ) }
initialValues[ 'BR' ] = BR.getVal()

###########################################################################################
# FIT MODEL
class KsMuMuModel:

    def __init__(self, name ):
        self.i = name
        i = self.i
        self.alpha = Alpha_const[i][0]

        self.nbs  = rt.RooFormulaVar('NKs' + i, 'NKs' + i, BR.GetName()+ '/(alphaconst' + i +")", rt.RooArgList(self.alpha, BR))
        self.nbkg = rt.RooRealVar('MuMuBkg' + i, 'MuMuBkg' + i, initialValues['MuMuBkg' + i], 0, NEVTS)

        misidPars = __import__( 'KsMuMuResults' )
        misidPars = getattr(misidPars, 'KsPiPiMisid_' + i)

        self.misid_n = rt.RooRealVar('misid_' +  i + 'n', 'misid_' +  i + 'n', initialValues['misid_' + i + 'n'], 50, 110)#3, 1.5, 100) #misidPars.misid_n
        self.misid_m = rt.RooRealVar('misid_' +  i + 'm', 'misid_' +  i + 'm', initialValues['misid_' + i + 'm'], 200, 400)#410, 200, 460)#misidPars.misid_m
        self.misid = rt.RooPowerLaw('misid_' + i, 'misid_' + i, Mass, self.misid_m, self.misid_n)
    
        self.k = rt.RooRealVar( 'MuMu_dk_' + i, 'MuMu_dk_' + i, initialValues['MuMu_dk_' + i], -0.2, 0. )#misidPars.slopeK
        self.bkg1 = rt.RooExponential("bkg1_MuMu_model" + i, "bkg1_MuMu_model" + i, Mass, self.k)

        self.f_misid = rt.RooRealVar('f_misid_' +  i, 'f_misid_' +  i, initialValues['f_misid_' + i], 0.9, 1)
        self.bkg = rt.RooAddPdf('bkg MuMu_model' + i, 'bkg MuMu_model' + i, self.misid, self.bkg1, self.f_misid)
        
        ipaPars = __import__( 'KsMuMuPeakPars' )
        ipaPars = getattr( ipaPars, 'KsMuMuIpaPars_' + i )

        self.ipa_s   = rt.RooRealVar('ipa_s' + i, 'ipa_s' + i, ipaPars.ipa_s)#, 1, 20)
        self.ipa_m   = rt.RooRealVar('ipa_m' + i, 'ipa_m' + i, ipaPars.ipa_m)#, 490, 50)
        self.beta    = rt.RooRealVar('beta' + i, 'beta' + i, ipaPars.beta)#, -1e-03, 1e-03)#
        self.zeta    = rt.RooRealVar('zeta' + i, 'zeta' + i, ipaPars.zeta)#1e-03, 0, 5)
        self.ipa_l   = rt.RooRealVar('l' + i, 'l' + i, ipaPars.l)#, 0, 3)
        self.ipa_a1  = rt.RooRealVar('a1' + i, 'a1' + i, ipaPars.a)
        self.ipa_a2  = rt.RooRealVar('a2' + i, 'a2' + i, ipaPars.a2)
        self.ipa_n1  = rt.RooRealVar('n1' + i, 'n1' + i, ipaPars.n)
        self.ipa_n2  = rt.RooRealVar('n2' + i, 'n2' + i, ipaPars.n2)
        
        self.Ks = rt.RooIpatia2('Ipatia' + i, 'Ipatia' + i, Mass, self.ipa_l, self.zeta, self.beta, self.ipa_s, self.ipa_m, self.ipa_a1, self.ipa_n1, self.ipa_a2, self.ipa_n2)
        self.model = rt.RooAddPdf('mumu model ' + i, 'mumu model ' + i, rt.RooArgList(self.bkg, self.Ks), rt.RooArgList(self.nbkg, self.nbs))

###########################################################################################

# Creates the main model
mm = {}
mainModel = rt.RooSimultaneous('MainModel', 'MainModel', category)
for key, kbin in BINNING.iteritems():
    for i in kbin:
        name = key + str(i)
        mm[name] = KsMuMuModel(name)
        mainModel.addPdf(mm[name].model, name)

# Generates the first set of data
print '*** GENERATING FIRST SET OF DATA ***'
DATA = mainModel.generate( rt.RooArgSet( Mass, category ), NEVTS )

#-----------------------------------------------------------------------------
# Function that generates ntoys samples using the bkg model, fitting the whole
# PDF to them, and extracting a profile for each one
def makeToyMCstudy( results, ntoys, nevts = 10000 ):
    rt.gROOT.SetBatch()
    data = DATA
    ofile = rt.TFile( 'ToyMCstudy90k.root', 'RECREATE' )
    for it in xrange( ntoys ):
        print '*** GENERATING TOY <', it , '> ***'
        rndmpars = results.randomizePars()
        fitpars  = mainModel.getParameters( data )
        ''' Sets the values of the parameters to those of the random sampling '''
        for i in xrange( len( fitpars ) ):
            el = rndmpars.at( i )
            if el:
                name = el.GetName()
                fitpars[ name ].setVal( el.getVal() )
        BR.setVal(0.)
        #fitpars.Write( 'Parameters_' + str(it) )
        print '-- Generating data'
        data = mainModel.generate( rt.RooArgSet( Mass, category ), nevts )
        ''' Sets the values of the parameters to those previous to the main fit '''
        print '-- Setting intial values'
        for kw, el in initialValues.iteritems():
            fitpars[ kw ].setVal( el )
        parlst = initialValues.keys()
        parlst.sort()
        for kw in parlst:
            print ' - ', kw, ' => ', fitpars[ kw ].getVal()
        mainModel.fitTo( data, *fitOpts )

        ''' Creates the profile for the branching fraction '''
        nll = mainModel.createNLL(data, *fitOpts)
        myminuit = rt.RooMinuit(nll)
        myminuit.minos(rt.RooArgSet(BR))
        pl = nll.createProfile(rt.RooArgSet(BR))
        fr = BR.frame( rf.Bins( 200 ), rf.Title( '' ) )
        pl.plotOn(fr, rf.ShiftToZero())
        name = 'Profile_' + str(it)
        #profile = rt.TCanvas( name, name )
        #fr.Draw()
        #profile.Write()
        fr.Write( 'ProfileFrame_' + str(it) )
    ofile.Close()

# Does the fit once so it gets the fit results
fitOpts = [rf.Minos(rt.kFALSE), rf.ExternalConstraints(summaryConstraints),
           rf.Offset(True), rf.Save(True) , rf.NumCPU(12)]#, rf.Strategy(2))
fitResults = mainModel.fitTo( DATA, *fitOpts )

print '*** START TO GENERATE TOYS ***'
makeToyMCstudy( fitResults, 20, NEVTS )
