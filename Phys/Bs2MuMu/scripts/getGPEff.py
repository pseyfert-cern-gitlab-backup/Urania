from ROOT import *
gROOT.SetBatch(True)

from readData import *
import os
from array import *
import cutStrings as cs

from SBsubtraction import getSBSubtractedHist2 #getSBSubtractedHist2(tree, variables,  binnings, discVar, discVarMean, sw_range = 35, sb_start = 70,  mass_range = 100, cut = ''):
from getUniBinning import getUniBinning #def getUniBinning(tree, var, nBins, cut='', opts={}):

directory = 'GPEff'
if not os.path.exists(directory):
    os.makedirs(directory)


#This is how to run:

#getGPEff('2011_20r1_July_SEL',[6,4],opts = {}):

def plotProj(nameBase,vars,hist_cut, hist_fid, setLog = True):

    gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
    gStyle.SetFillStyle(4000)
    gStyle.SetLabelOffset(0.02)

    # Projection of the X axis
    hist_cut_x = hist_cut.ProjectionX('cut_x',0,-1,'eo')
    hist_fid_x = hist_fid.ProjectionX('fid_x',0,-1,'eo')
    hist_eff_x = hist_cut_x.Clone('hist_eff_x')
    hist_eff_x.Divide(hist_cut_x, hist_fid_x , 1. , 1. , "c1=0.683 b(1,1) mode")

    #Make a 1D projection plot of the axis
    canv = TCanvas('Cut efficiency','Cut efficiency',1200,600)
    #gStyle.SetOptStat(kFALSE)
    hist_eff_x.SetMarkerStyle(20)
    hist_eff_x.SetLineWidth(2)
    hist_eff_x.SetLineColor(1)
    hist_eff_x.SetMarkerColor(kBlack)
    hist_eff_x.SetFillColor(kGreen-3)

    hist_eff_x.SetTitle('GhostProb cut eff. on muons in B^{+}#rightarrowJ/#psiK^{+};'+vars[0])
    hist_eff_x.GetXaxis().SetTitleOffset(1.5)

    #Fit the histogram with a straight line and a slope
    f_slope = TF1("f_slope","([0] + [1]*x)", hist_eff_x.GetXaxis().GetXmin(), hist_eff_x.GetXaxis().GetXmax())
    f_slope.SetParNames('a1','b1')
    f_slope.SetParameters(0.99,0.)
    hist_eff_x.Fit('f_slope')
    a1 = f_slope.GetParameter(0)
    a1_err = f_slope.GetParError(0)
    b1 = f_slope.GetParameter(1)
    b1_err = f_slope.GetParError(1)

    f_flat = TF1("f_flat","[0]", hist_eff_x.GetXaxis().GetXmin(), hist_eff_x.GetXaxis().GetXmax())
    f_flat.SetParameter(0,0.99)
    f_flat.SetParName(0,'a')
    hist_eff_x.Fit('f_flat')
    a0 = f_flat.GetParameter(0)
    a0_err = f_flat.GetParError(0)

    if setLog: gPad.SetLogx()
    gPad.SetRightMargin(0.3)
    hist_eff_x.Draw('E2')
    hist_eff_x.Draw('sameE1')
    f_flat.SetLineColor(kBlue)
    f_flat.Draw('sameE')
    f_slope.SetLineColor(kRed)
    f_slope.Draw('sameE')

    #Draw the Legend
    leg = TLegend(0.72, 0.6 , 0.95 , 0.9)
    leg.SetFillColor(kWhite)
    leg.AddEntry('hist_eff_x', 'MuMu GhostProb eff.','lep')
    leg.AddEntry('f_flat', 'f(x) = a_{0}','l')
    leg.AddEntry(0, ' a_{0} = %.3e +- %.3e' %(a0,a0_err),'')
    leg.AddEntry('f_slope', 'f(x) = a_{1}+b_{1}*x','l')
    leg.AddEntry(0, ' a_{1} = %.3e +- %.3e' %(a1,a1_err),'')
    leg.AddEntry(0, ' b_{1} = %.3e +- %.3e' %(b1,b1_err),'')
    leg.Draw('same')
    canv.Print(directory+'/'+nameBase+'_cutEff_'+vars[0]+'.ps')

    #########################################################
    #Projection of the X axis
    #########################################################

    #Projection of the X axis
    hist_cut_y = hist_cut.ProjectionY('cut_y',0,-1,'eo')
    hist_fid_y = hist_fid.ProjectionY('fid_y',0,-1,'eo')
    hist_eff_y = hist_cut_y.Clone('hist_eff_y')
    hist_eff_y.Divide(hist_cut_y, hist_fid_y , 1. , 1. , "c1=0.683 b(1,1) mode")

    #Make a 1D projection plot of the axis
    canv = TCanvas('Cut efficiency','Cut efficiency',1200,600)
    #gStyle.SetOptStat(kFALSE)
    hist_eff_y.SetMarkerStyle(20)
    hist_eff_y.SetLineWidth(2)
    hist_eff_y.SetLineColor(1)
    hist_eff_y.SetMarkerColor(kBlack)
    hist_eff_y.SetFillColor(kGreen-3)

    hist_eff_y.SetTitle('GhostProb cut eff. on muons in B^{+}#rightarrowJ/#psiK^{+};'+vars[1])
    hist_eff_y.GetXaxis().SetTitleOffset(1.5)

    #Fit the histogram with a straight line and a slope
    f_slope = TF1("f_slope","([0] + [1]*x)", hist_eff_y.GetXaxis().GetXmin(), hist_eff_y.GetXaxis().GetXmax())
    f_slope.SetParNames('a1','b1')
    f_slope.SetParameters(0.99,0.)
    hist_eff_y.Fit('f_slope')
    a1 = f_slope.GetParameter(0)
    a1_err = f_slope.GetParError(0)
    b1 = f_slope.GetParameter(1)
    b1_err = f_slope.GetParError(1)

    f_flat = TF1("f_flat","[0]", hist_eff_y.GetXaxis().GetXmin(), hist_eff_y.GetXaxis().GetXmax())
    f_flat.SetParameter(0,0.99)
    f_flat.SetParName(0,'a')
    hist_eff_y.Fit('f_flat')
    a0 = f_flat.GetParameter(0)
    a0_err = f_flat.GetParError(0)

    gPad.SetLogx()
    gPad.SetRightMargin(0.3)
    hist_eff_y.Draw('E2')
    hist_eff_y.Draw('sameE1')
    f_flat.SetLineColor(kBlue)
    f_flat.Draw('sameE')
    f_slope.SetLineColor(kRed)
    f_slope.Draw('sameE')

    #Draw the Legend
    leg = TLegend(0.72, 0.6 , 0.95 , 0.9)
    leg.SetFillColor(kWhite)
    leg.AddEntry('hist_eff_y', 'MuMu GhostProb eff.','lep')
    leg.AddEntry('f_flat', 'f(x) = a_{0}','l')
    leg.AddEntry(0, ' a_{0} = %.3e +- %.3e' %(a0,a0_err),'')
    leg.AddEntry('f_slope', 'f(x) = a_{1}+b_{1}*x','l')
    leg.AddEntry(0, ' a_{1} = %.3e +- %.3e' %(a1,a1_err),'')
    leg.AddEntry(0, ' b_{1} = %.3e +- %.3e' %(b1,b1_err),'')
    leg.Draw('same')
    canv.Print(directory+'/'+nameBase+'_cutEff_'+vars[1]+'.ps')


def getGPEff(nTuple = 'MC12_Sm0',nBins=[6,4],opts = {}):

    #Define the variables
    print ' o) Define the cuts:'
    fidcut = cs.minimalNormBu_lnf

    #Define the cut and variables to be studied
    cut = fidcut + cs.MuMu_GhostProb_03
    cutName = opts.get('cut','GP_MuMu_03')
    vars = ['J_psi_1S_PT', 'J_psi_1S_PZ']

    if cutName is 'GP_MuMu_043':
        cut = fidcut + cs.MuMu_GhostProb
        vars = ['J_psi_1S_PT', 'J_psi_1S_PZ']

    if cutName is 'GP_MuMinus_03':
        cut = fidcut + cs.MuMinus_GhostProb_03
        vars = ['muminus_PT', 'muminus_PZ']

    if cutName is 'GP_MuPlus_03':
        cut = fidcut + cs.MuPlus_GhostProb_03
        vars = ['muplus_PT', 'muplus_PZ']

    if cutName is 'GP_MuMinus_043':
        cut = fidcut + cs.MuMinus_GhostProb
        vars = ['muminus_PT', 'muminus_PZ']

    if cutName is 'GP_Mu_plus_043':
        cut = fidcut + cs.MuPlus_GhostProb
        vars = ['muplus_PT', 'muplus_PZ']

    print '     CutName:', cutName
    print '     Cut: ' , cut
    print '   ---------    '
    print '  Variables to bin: ', vars
    print '  Number of bins for vars:', nBins
    print '  Fiducial cut: ' , fidcut


    #Configure the SB subtraction:
    massVar = 'Bplus_JCMass'
    massMean = 5279.17 #PDG
    sw_range = 100
    sb_start = 65
    mass_range = 100
    print ' Discriminating variable for the sieband subtraction: ', massVar

    #Build a recognizable name tag
    nameBase = nTuple +'_cut_'+cutName+'_nBins_'+vars[0]+'_'+str(nBins[0])+'_'+vars[1]+'_'+str(nBins[1])

    #Load in the trees
    data = readData(nTuple)
    tree = data.get('tree')

    #Get the binning
    print ' o) Determine the optimal binning for the tree:'
    binnings = []
    binnings.append(getUniBinning(tree, vars[0],nBins[0],fidcut))
    binnings.append(getUniBinning(tree, vars[1],nBins[1],fidcut))

    #Move slightly away from zero to be able to plot the 2D plot in log scale
    binnings[0][0] += 1.
    binnings[1][0] += 1.
    print 'The best binning for var 1:', binnings[0]
    print 'The best binning for var 2:', binnings[1]

    #Calculate the efficiencies in bins
    hist_fid = getSBSubtractedHist2(tree, vars, binnings, massVar, massMean, sw_range, sb_start, mass_range, fidcut)[0]
    hist_cut = getSBSubtractedHist2(tree, vars, binnings, massVar, massMean, sw_range, sb_start, mass_range, cut)[0]
    hist_fid.Sumw2()
    hist_cut.Sumw2()

    hist_eff = hist_cut.Clone('hist_eff')

    #Using the Bayes errors for the efficiency
    hist_eff.Divide(hist_cut, hist_fid , 1. , 1. , "c1=0.683 b(1,1) mode")

    #----------------------------#
    #Plot the efficiency in bins
    #----------------------------#

    canv = TCanvas('Cut efficiency','Cut efficiency',1200,600)
    gStyle.SetOptStat(kFALSE)
    gStyle.SetPaintTextFormat('.4f')
    hist_eff.SetTitle(nTuple+': GhostProb cut eff. on muons in B^{+}#rightarrowJ/#psiK^{+}; '+vars[0]+' ; '+vars[1] )

    #Set log scale
    gPad.SetLogx()
    gPad.SetLogy()
    hist_eff.Draw('COLZBOXTEXT45')

    canv.Print(directory+'/'+nameBase+'_cutEff.ps')
    f_h = TFile(directory+'/'+nameBase+'_cutEff.root','recreate')
    hist_eff.Write()

    #Plot the projections
    plotProj(nameBase,vars,hist_cut, hist_fid, opts.get('setLog',0))

    #Print the info to the file
    f = open(directory+'/'+nameBase+'_cutEff_Info.txt','w')
    print >> f, ' #--------------------------------------------------------------------------------------------------#	'
    print >> f, ' # Cut efficiency calculation INFO FOR: ', data.get('name')
    print >> f, ' #     CHANNEL : B+JpsiK+'
    print >> f, ' #     Luminosity in pb : ',data.get('lumi').getVal()," +- ",data.get('lumi').getErr()
    print >> f, ' # SIDEBAND SUBTRACTION: ', massVar
    print >> f, ' #     MassVar: ', massVar
    print >> f, ' #     MassMean: ', massMean
    print >> f, ' #     sb_start :', sb_start
    print >> f, ' #     sw_range :', sw_range
    print >> f, ' #     mass_range :', mass_range
    print >> f, ' #     Vars :', vars
    print >> f, ' #     The best binning for var 1:', binnings[0]
    print >> f, ' #     The best binning for var 1:', binnings[1]
    print >> f, ' #--------------------------------------------------------------------------------------------------#	'
    print >> f, ' #     Fidcut :', fidcut
    print >> f, ' #     cut :', cut
    print >> f, ' #--------------------------------------------------------------------------------------------------#	'
    print >> f, ' #     Efficiencies per [pT,pZ] bins:'
    for x in range(nBins[0]):
        x+=1
        for y in range(nBins[1]):
           y+=1
           val = hist_eff.GetBinContent(x,y)
           e_hi = hist_eff.GetBinErrorUp(x,y)
           e_lo = hist_eff.GetBinErrorLow(x,y)
           print >> f, '           [%i,%i]: %.5f (+%.5f /- %.5f)' % (x,y,val,e_hi,e_lo)

    print >> f, ' #--------------------------------------------------------------------------------------------------#	'
    f.close()

    return 1


