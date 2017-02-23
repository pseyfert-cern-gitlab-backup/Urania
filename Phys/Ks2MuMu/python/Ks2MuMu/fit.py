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
rt.RooWorkspace.Import = getattr(rt.RooWorkspace, 'import') ### RooFit method < import > is not allowed in python

# Loads the lhcb style for the plots 
rt.gROOT.ProcessLine( '.x lhcbStyle.C' )

# Loads the functions used in the fit
rt.gROOT.ProcessLine('.L $URANIAROOT/src/RooIpatia2.cxx++')
rt.gROOT.ProcessLine('.L $URANIAROOT/src/RooAmorosoPdf.cxx++')
rt.gROOT.ProcessLine('.L $SOMEMASSMODELSROOT/src/RooPowerLaw.cxx++')
rt.gROOT.ProcessLine('.L ./RooPrior.cxx++')

# Enum for the profile
class ProfileType:
    NoProfile = 0 ### No profile is calculated
    BayesCalc = 1 ### Use BayesianCalculator
    MCMC      = 2 ### Use the MCMC method
    NLL       = 3 ### Use the -logL profile directly
    NLLcalc   = 4 ### Use the -logL calculator of ROOT

#-----------------------------------------------------------------------------
COMBINE_2011 = 1 ### 1 - Combine with the result from 2011
BLIND        = 0 ### 0 - Global status of the fit
POWER_LAW    = 1 ### 1 - if set to zero it will use an exponential for the misid bkg
EXPO         = 1 ### 1 - if set to zero it will use a polynomial for the comb bkg
FIXEXPOVALS  = 0 ### 0 - Fix exponential values to study the bkg syst
BR_MINOS     = 1 ### 1 - Get the asymmetric errors using minos
MAKEPLOTS    = 1 ### 1 - Create and save the mass fit plots
### ProfileType.NLL - Get the profile
PROFILE = ProfileType.NLL
#PROFILE = ProfileType.NoProfile
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
    #[('TOS1_', range(0,2))]
    # ('TOS2_', range(0,2))]
    [('TOS1_', range(0, 10)),
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
BR_ = rt.RooRealVar('BR', 'BR', 0., 0., 7.)# 0., 0., 7. => this converges 7., 0., 10.
if BLIND:
    BR = rt.RooUnblindPrecision("BR_UNB", "BR_UNB", TheTable.Blinding, 0.5, 2., BR_)
else:
    BR = BR_
parOfInt = rt.RooArgSet(BR_)

#prior = rt.RooAmorosoPdf('PRIOR', 'PRIOR' , BR_, PRIOR.offset, PRIOR.theta, PRIOR.alpha, PRIOR.beta)

prior = rt.RooPrior('PRIOR', 'PRIOR' , BR_)#, PRIOR.offset, PRIOR.theta, PRIOR.alpha, PRIOR.beta)

#fr = BR_.frame()
#prior.plotOn(fr)
#prior2.plotOn(fr)
#fr.Draw()

#BREAK
# Defines the constraints for the fit
summaryConstraints  = rt.RooArgSet()
# Nuisance parameters (all the RooRealVar objects but the BR)
nuisance_parameters = rt.RooArgSet()
# RooFormulaVar objects
formula_parameters  = rt.RooArgSet()
# Constant parameters
constant_parameters = rt.RooArgSet()

# Calculates the common factor
from math import sqrt
ComFctrSig = {}
sigma_lst = {}
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
    sigma_lst[key] = sigma
    ComFctrSig[ key ] = createConst( 1, sigma, 'ComFctr' + key )
    #ComFctrSig[ key ] [0].setConstant(rt.kTRUE)
    summaryConstraints.add( ComFctrSig[ key ][-1])
    #ComFctrSig[ key ] = const

    # Add to nuis. par.
    for el in ComFctrSig[ key ][:-1]:
        nuisance_parameters.add(el)

    # Add constant parameters
    for el in ComFctrSig[key][1:-1]:
        constant_parameters.add(el)

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

        # Add to nuis. par.
        for el in Alpha_const[ix][:-1]:
            nuisance_parameters.add(el)

        # Add the other parameters
        formula_parameters.add(Alpha[ix])

        # Add constant parameters
        for el in Alpha_const[ix][1:-1]:
            constant_parameters.add(el)
        
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

        # START VALUES IMPORTED FROM A HELPER MODULE
        import fithelp
        nbkg = getattr(fithelp, 'MuMuBkg' + i)

        # YIELDS
        self.nbs  = rt.RooFormulaVar('NKs' + i, 'NKs' + i, BR.GetName()+ '/(alpha' + i +")",
                                     rt.RooArgList(self.alpha, BR))
        self.nbkg = rt.RooRealVar('MuMuBkg' + i, 'MuMuBkg' + i, nbkg,
                                  0, max(2*tmm[i].GetEntries(), 20))

        # Append the number of background events as a nuis. par.
        nuisance_parameters.add(self.nbkg)

        # Append RooFormulaVar
        formula_parameters.add(self.nbs)
        
        # MISID
        misidPars = __import__( 'KsMuMuResults' )
        misidPars = getattr(misidPars, 'KsPiPiMisid_' + i)

        f_misid = getattr(fithelp, 'f_misid_' + i)
        misid_m = getattr(fithelp, 'misid_' + i + 'm')
        misid_n = getattr(fithelp, 'misid_' + i + 'n')

        self.misid_n = rt.RooRealVar('misid_' +  i + 'n', 'misid_' +  i + 'n',
                                     0.94*misid_n, 0.55*misid_n, 120)# 10, 1, 120 # misid_n - 2 #0.94misid_n, 0.6*misid_n, 120
        times_misid_m = 1.5
        if times_misid_m*misid_m >= MASS_MIN:
            times_misid_m = (MASS_MIN - 1.)/misid_m
        self.misid_m = rt.RooRealVar('misid_' +  i + 'm', 'misid_' +  i + 'm',
                                     misid_m, 0.6*misid_m, times_misid_m*misid_m)#320, 200, 469

        # pdf
        self.misid = rt.RooPowerLaw('misid_' + i, 'misid_' + i, Mass, self.misid_m, self.misid_n)

        # Add misid nuis. pars.
        for el in (self.misid_n, self.misid_m):
            nuisance_parameters.add(el)
        
        # COMB. BKG.
        if EXPO:
            dk = getattr(fithelp, 'MuMu_dk_' + i)
            self.k = rt.RooRealVar( 'MuMu_dk_' + i, 'MuMu_dk_' + i, dk, 1.5*dk, 0. )#-1e-2, -.1, .1
            
            if FIXEXPOVALS:
                import fitPars
                self.k.setVal( getattr( fitPars, 'MuMu_dk_' + i ) )
                self.k.setConstant( 1 )

            # pdf
            self.bkg1 = rt.RooExponential("bkg1_MuMu_model" + i, "bkg1_MuMu_model" + i, Mass, self.k)

            # Add bkg. nuis. par.
            nuisance_parameters.add(self.k)
        else:
            self.bkg1_m1 = rt.RooRealVar( 'Cbkg_m1_' + i, 'Cbkg_m1_' + i, -0.1, -10, 0 )
            self.bkg1_m2 = rt.RooRealVar( 'Cbkg_m2_' + i, 'Cbkg_m2_' + i, 0.1, 0, 10 )

            # pdf
            self.bkg1 = rt.RooChebychev( 'bkg1_MuMu_model' + i, 'bkg1_MuMu_model' + i,
                                         Mass, rt.RooArgList( self.bkg1_m1, self.bkg1_m2 ) )
            
            # Add bkg. nuis. par.
            for el in (self.bkg1_m1, self.bkg1_m2):
                nuisance_parameters.add(el)
        
        # MISID/BKG YIELD
        #f_misid = misidPars.NSig*1./( misidPars.NCombBkg + misidPars.NSig )
        self.f_misid = rt.RooRealVar('f_misid_' + i, 'f_misid_' + i,
                                     f_misid, 0.88*f_misid, 1)#f_misid, 0.5, 1

        # Add the fraction of misid as a nuis. par.
        nuisance_parameters.add(self.f_misid)

        # BACKGROUND
        if POWER_LAW:
            self.bkg = rt.RooAddPdf('bkg_MuMu_model' + i, 'bkg_MuMu_model' + i,
                                    self.misid, self.bkg1, self.f_misid)
        else:
            self.bkg = rt.RooAddPdf('bkg_MuMu_model' + i, 'bkg_MuMu_model' + i,
                                    self.bkg2, self.bkg1, self.f_misid)
        
        # SIGNAL
        ipaPars = __import__( 'KsMuMuPeakPars' )
        ipaPars = getattr( ipaPars, 'KsMuMuIpaPars_' + i )

        self.ipa_s   = rt.RooRealVar('ipa_s' + i, 'ipa_s' + i, ipaPars.ipa_s)#, 1, 20)
        self.ipa_m   = rt.RooRealVar('ipa_m' + i, 'ipa_m' + i, ipaPars.ipa_m)#, 490, 50)
        self.beta    = rt.RooRealVar('beta' + i, 'beta' + i, ipaPars.beta)#, -1e-03, 1e-03)
        self.zeta    = rt.RooRealVar('zeta' + i, 'zeta' + i, ipaPars.zeta)#1e-03, 0, 5)
        self.ipa_l   = rt.RooRealVar('l' + i, 'l' + i, ipaPars.l)#, 0, 3)
        self.ipa_a1  = rt.RooRealVar('a1' + i, 'a1' + i, ipaPars.a)
        self.ipa_a2  = rt.RooRealVar('a2' + i, 'a2' + i, ipaPars.a2)
        self.ipa_n1  = rt.RooRealVar('n1' + i, 'n1' + i, ipaPars.n)
        self.ipa_n2  = rt.RooRealVar('n2' + i, 'n2' + i, ipaPars.n2)

        # pdf
        self.Ks = rt.RooIpatia2('Ipatia' + i, 'Ipatia' + i, Mass,
                                self.ipa_l, self.zeta, self.beta,
                                self.ipa_s, self.ipa_m,
                                self.ipa_a1, self.ipa_n1, self.ipa_a2, self.ipa_n2)

        ipa_pars = (self.ipa_s, self.ipa_m, self.beta, self.zeta, self.ipa_l,
                    self.ipa_a1, self.ipa_a2, self.ipa_n1, self.ipa_n2)

        # Add nuis. pars. from Ipatia function
        for el in ipa_pars:
            nuisance_parameters.add(el)

        # Add constant parameters
        for el in ipa_pars:
            constant_parameters.add(el)

        # MODEL FOR THE BIN < i >
        self.model = rt.RooAddPdf('mumu_model_' + i, 'mumu_model_' + i,
                                  rt.RooArgList(self.bkg, self.Ks),
                                  rt.RooArgList(self.nbkg, self.nbs))

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
alldata.SetName('ALL')
DATA['ALL'] = alldata

#-----------------------------------------------------------------------------
# Fits to the whole sample
print '*** MAIN FIT STARTS HERE ***'
fitOpts = [rf.Minos(rt.kFALSE), rf.ExternalConstraints(summaryConstraints),
           rf.Offset(True), rf.Save(True) , rf.NumCPU(12)]
fitResults = mainModel.fitTo(DATA['ALL'], *fitOpts)
fitResults.Print()
print '*** MAIN FIT ENDS HERE ***'
nll = mainModel.createNLL(DATA['ALL'],
                          rf.Offset(True), rf.ExternalConstraints(summaryConstraints), rf.NumCPU(12))

# Build the workspace
workspace = rt.RooWorkspace('Workspace')
workspace.Import(DATA['ALL'])
workspace.Import(mainModel)
workspace.defineSet("NuisPars", nuisance_parameters, True)
workspace.defineSet("ParsOfInt", parOfInt, True)
workspace.defineSet("Formulas", formula_parameters, True)
workspace.defineSet("Constants", constant_parameters, True)

# Apply minos to the BR if specified
if BR_MINOS:
    print '*** CALCULATING MINOS FOR BR ***'
    myminuit = rt.RooMinuit(nll)
    myminuit.minos(rt.RooArgSet(BR_))
    fitResults = myminuit.save()

# Calculate the profile if specified:
# 0 - No calculation
# 1 - Limit using MCMCCalculator
# 2 - Limit using the NLL
if PROFILE != ProfileType.NoProfile:
    rt.gROOT.SetBatch()
    print '*** CREATING PROFILE ***'
    if FIXEXPOVALS:
        f = rt.TFile('BRprofile_BkgSyst_FixExpo_' + ''.join(BINNING.keys())[:-1] + '.root', 'RECREATE')
    elif EXPO:
        if COMBINE_2011:
            name = 'BRprofile_' + ''.join(BINNING.keys())[:-1] + '.root'
        else:
            name = 'BRprofile_No2011_' + ''.join(BINNING.keys())[:-1] + '.root'
        f = rt.TFile(name, 'RECREATE')
    else:
        f = rt.TFile('BRprofile_BkgSyst_' + ''.join(BINNING.keys())[:-1] + '.root', 'RECREATE')

    import getlimit
    if PROFILE == ProfileType.BayesCalc:
        out_limit = getlimit.limitBayesCalc(DATA['ALL'], workspace, parOfInt, nuisance_parameters,
                                            summaryConstraints)
    elif PROFILE == ProfileType.MCMC:
        out_limit = getlimit.limitMCMC(workspace, parOfInt, nuisance_parameters,
                                       fitResults, summaryConstraints)
    elif PROFILE == ProfileType.NLL:
        out_limit = getlimit.limitNLL(nll, parOfInt)
    elif PROFILE == ProfileType.NLLcalc:
        out_limit = getlimit.limitProfileCalc( DATA['ALL'], workspace, parOfInt, nuisance_parameters,
                                               summaryConstraints )
    else:
        print '*** UNKNOWN PROFILE TYPE', PROFILE, '=> skipping ***'

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
        mainPdf.plotOn(fr[ix], rf.Components('bkg1_MuMu_model' + ix), rf.LineColor( rt.kRed ), rf.LineStyle(rt.kDotted), *plotOpts)
        mainPdf.plotOn(fr[ix], rf.Components('misid_' + ix), rf.LineColor(rt.kGreen + 2), rf.LineStyle(7), *plotOpts)
        mainPdf.plotOn(fr[ix], rf.Components('Ipatia' +  ix), rf.LineColor(rt.TColor.GetColor('#ff99cc')), *plotOpts)
        mainPdf.plotOn(fr[ix], rf.Name( 'MainModel' ), rf.LineColor(rt.kBlue), *plotOpts)

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
    rt.gROOT.SetBatch()
    strkws = [ str( kw ) for kw in BINNING ]
    if FIXEXPOVALS:
        oplots = rt.TFile.Open( 'FitPlots_BkgSyst_FixExpo_' + ''.join( strkws )[:-1] + '.root', 'RECREATE' )
    elif EXPO:
        oplots = rt.TFile.Open( 'FitPlots_' + ''.join( strkws )[:-1] + '.root', 'RECREATE' )
    else:
        oplots = rt.TFile.Open( 'FitPlots_BkgSyst_' + ''.join( strkws )[:-1] + '.root', 'RECREATE' )
    for kw, bins in BINNING.iteritems():
        for i in bins:
            c = plot( kw + str( i ) )
            c.Write()
print 'End of script!'
