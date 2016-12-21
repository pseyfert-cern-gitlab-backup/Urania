#from ROOT import *
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

rt.gROOT.SetBatch()

# Loads the lhcb style for the plots 
rt.gROOT.ProcessLine( '.x lhcbStyle.C' )

# Loads the functions used in the fit
rt.gROOT.ProcessLine('.L $URANIAROOT/src/RooIpatia2.cxx++')
rt.gROOT.ProcessLine('.L $URANIAROOT/src/RooAmorosoPdf.cxx++')
rt.gROOT.ProcessLine('.L $SOMEMASSMODELSROOT/src/RooPowerLaw.cxx++')
rt.gROOT.ProcessLine('.L ./RooPrior.cxx++')
#rt.gROOT.ProcessLine(".x BifurcatedCB.cxx+")
#from ROOT import BifurcatedCB

#-----------------------------------------------------------------------------
COMBINE_2011 = 1
BLIND = 1
POWER_LAW = 1 ### if set to zero it will use an exponential for the misid bkg
EXPO = 1 ### if set to zero it will use a polynomial for the comb bkg
FIXEXPOVALS = 0
BR_MINOS = 0
PROFILE = 1
TOYSTUDY = 0
MAKEPLOTS = 0
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Range for the dimuon mass
#MASS_MIN  = 465.
MASS_MIN  = 470.
BLIND_MIN = 492.
BLIND_MAX = 504.
MASS_MAX  = 600.
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
if not BLIND:
    print ''
    print ''
    print ''
    print '0o0   0o0    0o0   0o0   0o0  0o0  0o0  0o0'
    print ' ALARM!, ALARM!, YOU ARE UNBLINDING!!!'
    print '0o0   0o0    0o0   0o0   0o0  0o0  0o0  0o0'
    print ''
    print ''
    print ''
#-----------------------------------------------------------------------------

# Path to the input files
TUPLE_PATH = '~/eos/lhcb/wg/RD/K0SMuMu/NEW/DATA/'

# Defines the bins for each category. This list determines the bins that
# will be fitted.
categories = [ 'TOS1_', 'TOS2_' ]
BINNING = OrderedDict(
    #[('TOS1_', range(3,10))]
    #[('TOS2_', range(3,10))]
    [('TOS1_', range(0,10)),
     ('TOS2_', range(0, 10))]
    )

# Fitting variable and ranges
Mass = rt.RooRealVar('KS0_MM', 'm_{#mu^{+}#mu^{-}}', MASS_MIN, MASS_MAX, 'MeV/c^{2}')
category =  rt.RooCategory('sample',  'sample')
Mass.setRange('all', Mass.getMin(), Mass.getMax() )
Mass.setRange('lsb', Mass.getMin(), BLIND_MIN     )
Mass.setRange('rsb', BLIND_MAX    , Mass.getMax() )

for key, kbin in BINNING.iteritems():
    for i in kbin:
        category.defineType(key + str(i))

#-----------------------------------------------------------------------------
# Creates the subsamples to perform the fit faster
CREATE_FILES = False
if CREATE_FILES:
    f = rt.TFile(TUPLE_PATH + 'Ksmumu_Data2012_MVA.root')
    t = f.Get('DecayTree')
    BDTplusMuID = {}
    for key in categories:
        BDTplusMuID[key] = BDTplusMuID_cuts(key)
    print '-- Fiducial cuts:', SEL
    print '-- BDT and MuID cuts:', BDTplusMuID

fmm, tmm, datamm, catdatamm = {}, {}, {}, {}
tempfile = rt.TFile( 'tempfile.root', 'RECREATE' )
for key, kbin in BINNING.iteritems():
    if CREATE_FILES:
        print '--- COPYING TREE FOR %s' %key
        tempfile.cd()
        temptree = t.CopyTree( SEL[key] )
    for i in kbin:
        ix = key + str(i)
        if CREATE_FILES:
            print '--- CREATING FILE FOR %s' %ix
            fmm[ix] = rt.TFile('./prof_mm' + ix + '.root', 'recreate')
            tmm[ix] = temptree.CopyTree(BDTplusMuID[key][i][3:])
            tmm[ix].Write()
            fmm[ix].Close()
        
        fmm[ix] = rt.TFile('./prof_mm' + ix + '.root')
        tmm[ix] = fmm[ix].Get('DecayTree')
        datamm[ix] = rt.RooDataSet('datamm' + ix, 'datamm' + ix, tmm[ix], rt.RooArgSet(Mass))
        catdatamm[ix] = rt.RooDataSet('catdatamm' + ix, 'catdatamm' + ix, rt.RooArgSet(Mass), rf.Index(category), rf.Import(ix, datamm[ix]))
if CREATE_FILES:
    import os
    os.system('rm tempfile.root')
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Blinds the branching fraction if required. The random blinding factor is
# stored in UnBlindBr, so do not look at it ;).
BR_ = rt.RooRealVar('BR', 'BR', 5., 0., 10.)# 0., 0., 7. => this converges
if BLIND:
    BR = rt.RooUnblindPrecision("BR_UNB", "BR_UNB", TheTable.Blinding, 0.5, 2., BR_)
    #ublindfct = rt.gRandom.Uniform( BR_.getVal(), 1000 )
    #UnBlindBr = rt.RooConstVar( 'BR_UNBFCT', 'BR_UNBFCT', ublindfct )
    #BR        = rt.RooFormulaVar( 'BR_UNB', 'BR_UNB', 'BR*BR_UNBFCT', rt.RooArgList( BR_, UnBlindBr ) )
else:
    BR = BR_
#prior = rt.RooAmorosoPdf('PRIOR', 'PRIOR' , BR_, PRIOR.offset, PRIOR.theta, PRIOR.alpha, PRIOR.beta)

prior = rt.RooPrior('PRIOR', 'PRIOR' , BR_)#, PRIOR.offset, PRIOR.theta, PRIOR.alpha, PRIOR.beta)

#fr = BR_.frame()
#prior.plotOn(fr)
#prior2.plotOn(fr)
#fr.Draw()

#BREAK
# Defines the constraints for the fit
summaryConstraints = rt.RooArgSet()

# Calculates the common factor
from math import sqrt
ComFctrSig = {}
mismierdas = {}
for key, kbin in BINNING.iteritems():
    mean = 0
    for i in kbin:
        ix = key + str( i )
        mean += TheTable.s_alpha_corr[ix]*1./TheTable.alpha[ix]
    mean /= float(len(kbin))

    # All the systematics are added in quadrature
    tracksyst = TheTable.TrackingSyst**2
    selsyst   = TheTable.SelectionSyst[ key ]**2
    trigsyst  = TheTable.TriggerSyst[ key ]**2
    kspecsyst = TheTable.KspectrumSyst**2
    muidsyst  = TheTable.MuIDSyst[ key ]**2
    sigshape  = TheTable.SigShapeSyst**2

    sigma = sqrt( mean**2 + tracksyst + selsyst + trigsyst + kspecsyst + muidsyst + sigshape )
    mismierdas [key] = sigma
    ComFctrSig[ key ] = createConst( 1, sigma, 'ComFctr' + key )
    #ComFctrSig[ key ] [0].setConstant(rt.kTRUE)
    summaryConstraints.add( ComFctrSig[ key ][-1])
    #ComFctrSig[ key ] = const

Ipa_m_const = {}
Alpha_const = {}
Alpha = {}
for key, kbin in BINNING.iteritems():
    for i in kbin:
        ix = key + str(i)
        
        alpha = TheTable.alpha[ix]*1e09
        s_alpha = TheTable.s_alpha_uncorr[ix]*1e09
        
        Alpha_const[ix] = createConst(alpha, s_alpha, 'alphaconst' + ix)
        summaryConstraints.add(Alpha_const[ix][-1])
        #Alpha_const[ix] = const
        
        Alpha[ix] = rt.RooFormulaVar( 'alpha' + ix, 'alpha' + ix, 'ComFctr' + key + '*alphaconst' + ix, rt.RooArgList( ComFctrSig[key][0], Alpha_const[ix][0] ) )

        # Ipa_m_const[key + str(i)] = createBifurConst(TheTable.sigmaKMuNu1, TheTable.sigmaKMuNu1ErrMinus, TheTable.sigmaKMuNu1ErrPlus, 'sigmaKMuNu1')
#BREAK
if COMBINE_2011:
    summaryConstraints.add(prior)

###########################################################################################
# FIT MODEL
class KsMuMuModel:

    def __init__(self, name ):
        self.i = name
        i = self.i
        self.alpha = Alpha[i]

        # OPTIONS IMPORTED FROM A HELPER
        import fithelp
        nbkg = getattr(fithelp, 'MuMuBkg' + i)
        self.nbs  = rt.RooFormulaVar('NKs' + i, 'NKs' + i, BR.GetName()+ '/(alpha' + i +")", rt.RooArgList(self.alpha, BR))
        self.nbkg = rt.RooRealVar('MuMuBkg' + i, 'MuMuBkg' + i, nbkg, 0, max(2*tmm[i].GetEntries(), 20))

        #self.k  = rt.RooRealVar('MuMu_k_' + i, 'MuMu_k_' + i, -7e-04, -.1, .1)
        #self.dk = rt.RooRealVar('MuMu_dk_' + i, 'MuMu_dk_' + i, -7e-04, -100, 0)#1e-02)
        #self.kb = rt.RooFormulaVar('MuMu_kb_' + i, 'MuMu_kb_' + i, 'MuMu_k_' + i + ' + MuMu_dk_' + i, rt.RooArgList(self.k, self.dk))
        
        #self.bkg1 = rt.RooExponential('bkg1_MuMu_model' + i, 'bkg1_MuMu_model' + i, Mass, self.k)
        #self.bkg2 = rt.RooExponential('bkg2_MuMu_model' + i, 'bkg2_MuMu_model' + i, Mass, self.kb)

        misidPars = __import__( 'KsMuMuResults' )
        misidPars = getattr(misidPars, 'KsPiPiMisid_' + i)

        #self.misid_ap = rt.RooRealVar('misid_' +  i + 'a', 'misid_' +  i + 'a', -2, -100, -0.1)

        # OPTIONS IMPORTED FROM A HELPER
        f_misid = getattr(fithelp, 'f_misid_' + i)
        misid_m = getattr(fithelp, 'misid_' + i + 'm')
        misid_n = getattr(fithelp, 'misid_' + i + 'n')

        self.misid_n = rt.RooRealVar('misid_' +  i + 'n', 'misid_' +  i + 'n', misid_n, 0.6*misid_n, 120)# 10, 1, 120 # misid_n - 2
        #self.misid_s = rt.RooRealVar('misid_' +  i + 's', 'misid_' +  i + 's', 3, 1, 10)
        times_misid_m = 1.5
        if times_misid_m*misid_m >= MASS_MIN:
            times_misid_m = (MASS_MIN - 1.)/misid_m
        self.misid_m = rt.RooRealVar('misid_' +  i + 'm', 'misid_' +  i + 'm', misid_m, 0.6*misid_m, times_misid_m*misid_m)#320, 200, 469
        #fix_m = 0#("TIS_3" in name) or ("TIS_4" in name)# or ("TIS_9" in name)
        #self.misid_m.setConstant(fix_m)
        self.misid = rt.RooPowerLaw('misid_' + i, 'misid_' + i, Mass, self.misid_m, self.misid_n)
        
        #self.bkg = rt.RooAddPdf('AllBkg' + i, 'AllBkg' + i, self.misid, self.bkg1, self.f_misid)
        
        if EXPO:
            dk = getattr(fithelp, 'MuMu_dk_' + i)
            self.k = rt.RooRealVar( 'MuMu_dk_' + i, 'MuMu_dk_' + i, dk, 1.5*dk, 0. )#-1e-2, -.1, .1
            self.bkg1 = rt.RooExponential("bkg1_MuMu_model" + i, "bkg1_MuMu_model" + i, Mass, self.k)
            if FIXEXPOVALS:
                import fitPars
                self.k.setVal( getattr( fitPars, i ) )
                self.k.setConstant( 1 )
        else:
            self.bkg1_m1 = rt.RooRealVar( 'Cbkg_m1_' + i, 'Cbkg_m1_' + i, -0.9, -4, 0 )
            self.bkg1_m2 = rt.RooRealVar( 'Cbkg_m2_' + i, 'Cbkg_m2_' + i, 0.16, 0, 4 )
            #self.bkg1 = rt.RooPolynomial( 'bkg1_MuMu_model' + i, 'bkg1_MuMu_model' + i, Mass, rt.RooArgList( self.bkg1_m ) )
            self.bkg1 = rt.RooChebychev( 'bkg1_MuMu_model' + i, 'bkg1_MuMu_model' + i, Mass, rt.RooArgList( self.bkg1_m1, self.bkg1_m2 ) )
        '''
        self.misid_alphaRK = rt.RooRealVar( 'misid_' + i + 'alphaRK', 'misid' + i + 'alphaRK', misidPars.alphaRK , -0.8, -0.1 )
        self.misid_nRK     = rt.RooRealVar( 'misid_' + i + 'nRK', 'misid' + i + 'nRK', misidPars.nRK , 5., 300. )
        self.misid_sigmaK  = rt.RooRealVar( 'misid_' + i + 'sigmaK', 'misid' + i + 'sigmaK', misidPars.sigmaK , 0.7, 1.1 )
        self.misid_mK      = rt.RooRealVar( 'misid_' + i + 'mK', 'misid_' + i + 'mK', misidPars.mK )#, 455., 470. )
        args = [Mass, self.misid_mK, self.misid_sigmaK, self.misid_alphaRK, self.misid_nRK]
        self.misid = rt.RooCBShape( 'misid_' + i, 'misid_' + i, *args )
        '''

        #f_misid = misidPars.NSig*1./( misidPars.NCombBkg + misidPars.NSig )
        self.f_misid = rt.RooRealVar('f_misid_' + i, 'f_misid_' + i, f_misid, 0.9*f_misid, 1)#f_misid, 0.5, 1
        if POWER_LAW:
            self.bkg = rt.RooAddPdf('bkg MuMu_model' + i, 'bkg MuMu_model' + i, self.misid, self.bkg1, self.f_misid)
        else:
            self.bkg = rt.RooAddPdf('bkg MuMu_model' + i, 'bkg MuMu_model' + i, self.bkg2, self.bkg1, self.f_misid)
        
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
        '''
        self.ipa_s   = rt.RooRealVar('ipa_s' + i, 'ipa_s' + i, TheTable.sigma[i])#, 1, 20)
        self.ipa_m   = rt.RooRealVar('ipa_m' + i, 'ipa_m' + i, TheTable.mean[i])#, 490, 50)
        self.beta    = rt.RooRealVar('beta' + i, 'beta' + i, TheTable.beta[i])#, -1e-03, 1e-03)#
        self.zeta    = rt.RooRealVar('zeta' + i, 'zeta' + i, TheTable.zeta[i])#1e-03, 0, 5)
        self.ipa_l   = rt.RooRealVar('l' + i, 'l' + i, TheTable.landa[i])#, 0, 3)
        self.ipa_a1  = rt.RooRealVar('a1' + i, 'a1' + i, TheTable.a1[i])
        self.ipa_a2  = rt.RooRealVar('a2' + i, 'a2' + i, 100)
        self.ipa_n1  = rt.RooRealVar('n1' + i, 'n1' + i, TheTable.n1[i])
        self.ipa_n2  = rt.RooRealVar('n2' + i, 'n2' + i, 1)
        '''
        
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

# Creates the samples for each of the different categories (joinning all the datasets from each bin)
def defineData( cat ):
    ibin = BINNING[ cat ][ 0 ]
    data = catdatamm[ cat + str(ibin) ].Clone()
    for ibin in BINNING[ cat ][ 1: ]:
        data.append(catdatamm[ cat + str( ibin ) ])
    data.SetNameTitle(cat + 'data', cat + 'data')
    return data
    
DATA = {}
for kw in BINNING:
    DATA[kw] = defineData(kw)

# Merges the samples of the different trigger categories into one
alldata = DATA.items()[0][1].Clone()
for kw, el in DATA.items()[1:]:
    alldata.append(el)
DATA['ALL'] = alldata

#-----------------------------------------------------------------------------
# Stores the initial values in the fit
pars = mainModel.getParameters( DATA['ALL'] )
it  = pars.createIterator()
var = it.Next()
initialValues = {}
while var:
    if var.GetName() != 'dummyBlindState':
        print '--- Getting:', var.GetName()
        initialValues[ var.GetName() ] = var.getVal()
    var = it.Next()

#-----------------------------------------------------------------------------
# Fits to the whole sample
print '*************************************** MAIN FIT STARTS HERE ***************************************'
fitOpts = [rf.Minos(rt.kFALSE), rf.ExternalConstraints(summaryConstraints),
           rf.Offset(True), rf.Save(True) , rf.NumCPU(12)]#, rf.Strategy(2))
fitResults = mainModel.fitTo(DATA['ALL'], *fitOpts)
fitResults.Print()
print '*************************************** MAIN FIT ENDS HERE ***************************************'
nll = mainModel.createNLL(DATA['ALL'], rf.ExternalConstraints(summaryConstraints), rf.NumCPU(12))

if BR_MINOS:
    print '********************************** CALCULATING MINOS FOR BR **************************************'
    myminuit = rt.RooMinuit(nll)
    myminuit.minos(rt.RooArgSet(BR_))
if PROFILE:
    rt.gROOT.SetBatch()
    print '*** CREATING PROFILE ***'
    pl = nll.createProfile(rt.RooArgSet(BR_))
    fr = BR_.frame( rf.Bins( 200 ), rf.Title( '' ) )
    pl.plotOn(fr, rf.ShiftToZero())
    profile = rt.TCanvas( 'Profile', 'Profile' )
    fr.Draw()
    f = rt.TFile( 'BRprofile_' + ''.join(BINNING.keys())[:-1] + '.root', 'RECREATE' )
    profile.Write()
    fr.Write( 'ProfileFrame' )
    f.Close()
#-----------------------------------------------------------------------------


#-----------------------------------------------------------------------------
# Function to remove the points inside the specified range (just for the data,
# for the PDFs the < Range > cmd can be used.
def removeDataOutOf( curve, roovar, ranges ):
    ranges = ranges.split(',')
    xval, yval = rt.Double( 0. ), rt.Double( 0. )
    values = []
    for rng in ranges:
        binptr = roovar.getBinningPtr( rng )
        values.append( (binptr.lowBound(), binptr.highBound() ) )
    points2Del = []
    for ip in xrange( curve.GetN() ):
        curve.GetPoint( ip, xval, yval )
        if not any( xval >= vmin and xval < vmax for vmin, vmax in values ):
            points2Del.append( ip )
    points2Del.reverse()
    for ip in points2Del:
        curve.RemovePoint( ip )

#-----------------------------------------------------------------------------
# Function that generates ntoys samples using the bkg model, fitting the whole
# PDF to them, and extracting a profile for each one
def makeToyMCstudy( results, ntoys, nevts = 10000 ):
    rt.gROOT.SetBatch()
    data  = DATA['ALL']
    name = 'ToyMCstudy_' + str(ntoys) + 'toys_' + str(nevts) + 'nevts.root'
    ofile = rt.TFile( name, 'RECREATE' )
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
        BR_.setVal(0.)
        fitpars.Write( 'Parameters_' + str(it) )
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
        myminuit.minos(rt.RooArgSet(BR_))
        pl = nll.createProfile(rt.RooArgSet(BR_))
        fr = BR_.frame( rf.Bins( 200 ), rf.Title( '' ) )
        pl.plotOn(fr, rf.ShiftToZero())
        name = 'Profile_' + str(it)
        #profile = rt.TCanvas( name, name )
        #fr.Draw()
        #profile.Write()
        fr.Write( 'ProfileFrame_' + str(it) )
    ofile.Close()

if TOYSTUDY:
    makeToyMCstudy( fitResults, 20, 90000 )

#-----------------------------------------------------------------------------
# Function to make the plot for a given bin (example: 'TIS_0')
fr = {}
def plot(ix, binning = 100):

    if BLIND:
        rng = 'lsb,rsb'
    else:
        rng = 'all'

    c = rt.TCanvas( ix, ix )
    c.Divide(1, 2)
    fr[ix] = Mass.frame( rf.Title( '' ) )
    datamm[ix].plotOn(fr[ix], rf.Binning(binning), rf.Name( 'DATA' ) )
    
    for r in rng.split(','):
        plotOpts = [rf.Range( r ), rf.NormRange( rng ), rf.LineWidth(2)]
        mainPdf  = mm[ix].model
        mainPdf.plotOn(fr[ix], rf.Components('bkg1_MuMu_model' + ix), rf.LineColor( rt.kOrange ), rf.LineStyle(rt.kDotted), *plotOpts)
        mainPdf.plotOn(fr[ix], rf.Components('misid_' + ix), rf.LineColor(rt.kGreen), rf.LineStyle(7), *plotOpts)
        mainPdf.plotOn(fr[ix], rf.Components('Ipatia' +  ix), rf.LineColor(rt.TColor.GetColor('#ff99cc')), *plotOpts)
        mainPdf.plotOn(fr[ix], rf.Name( 'MainModel' ), *plotOpts)

    # One must do it after drawing all the PDFs
    removeDataOutOf( fr[ix].getHist( 'DATA' ), Mass, rng )

    myPad1 = c.cd(1)
    c.SetLogy();
    myPad1.SetPad( 0, 0.2, 1, 1 )
    fr[ix].Draw()
    
    # Gets the pull plots
    from plotFunctions import makePullPlot
    pull   = makePullPlot(Mass, datamm[ix], binning, mainPdf, rng.split(',') )
    myPad2 = c.cd(2)
    myPad2.SetPad( 0, 0, 1, 0.2 )

    pull.GetXaxis().SetLabelSize(0.15)
    pull.GetYaxis().SetLabelSize(0.15)
    pull.GetYaxis().SetNdivisions(504)
    pull.SetMinimum( -5 )
    pull.SetMaximum( +5 )
    pull.GetXaxis().SetRangeUser( MASS_MIN, MASS_MAX )
    botline = rt.TLine( MASS_MIN, -3., MASS_MAX, -3. )
    midline = rt.TLine( MASS_MIN,  0., MASS_MAX,  0. )
    topline = rt.TLine( MASS_MIN, +3., MASS_MAX, +3. )
    pull.Draw()
    for i, line in enumerate([ botline, midline, topline ]):
        line.SetLineColor( rt.kRed )
        if i != 1:
            line.SetLineStyle( rt.kDotted )
        line.Draw('SAME')
    
    c.Update()

    fr[ix + '_pull']   = pull
    fr[ix + '_lines' ] = [botline, midline, topline]

    return c

if MAKEPLOTS:
    #rt.gROOT.SetBatch()
    strkws = [ str( kw ) for kw in BINNING ]
    oplots = rt.TFile.Open( 'FitPlots_' + ''.join( strkws )[:-1] + '.root', 'RECREATE' )
    for kw, bins in BINNING.iteritems():
        for i in bins:
            c = plot( kw + str( i ) )
            c.Write()
print 'End of script!'
