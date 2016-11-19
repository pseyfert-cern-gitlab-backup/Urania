from ROOT import *
import sys, os
gROOT.SetBatch()
gROOT.ProcessLine('.x ~/lhcbStyle.C')
#from LcTophhBFStuff.Funcs.TupleFetchers import getCurrentName
#gStyle.SetLabelFont(132)
#gStyle.SetTitleFont(132)
#gStyle.SetLegendFont(132)
# Process filename argument
#if len(sys.argv)!=2:
#    sys.exit('ERROR: give workspace filename as argument')
# Lc2pKK_promptdata21r1_MagDown_tightPIDKV_oct14_fitresults.root
#fName = sys.argv[1]#'Lc2pKK_promptdata17b_all_noweights_moderatePID_may14_fitresults.root'
from os import listdir
from os.path import isfile, join
mypath = os.getcwd()
fNameIn = sys.argv[1]
#onlyROOTfiles = [f for f in listdir(mypath) if (isfile(join(mypath, f)) and ('.root' in f))]
#print onlyROOTfiles
#sys.exit()
onlyROOTfiles = [fNameIn]

for fName in onlyROOTfiles:

    f = TFile(fName, 'read')
    # RDs_FitResult_MC_AllNeutrals_MagDown.root
    dataTag = 'MC_AllNeutrals'
    if 'Data_AllNeutrals' in fName:
        dataTag = 'Data_AllNeutrals'
    pol = 'MagDown'
    if 'MagUp' in fName:
        pol = 'MagUp'

    # Get everything from the workspace
    w = f.Get('RDs_Workspace')
    w.Print()
    
    pdfName = 'total'

    # Make the RDS name
    rdsName = 'rds_mass' #'%s_promptdata%s_%s_noweights_%sPID_0.0004' %(mode, strip, pol, pid)

    pdf = w.pdf(pdfName)
    rds = w.data(rdsName)
    rvm = w.var('hDsMuMassFirstG04')

    pdf.Print()
    rds.Print()
    rvm.Print()

    # Get the parameters we need to plot.
    ns = w.var('N_{sig}')
    ns.SetNameTitle('N_{sig}', 'N_{sig}')
    
    nb = w.var('N_{bkg}')
    nb.SetNameTitle('N_{bkg}', 'N_{bkg}')

    cbm = w.var('Mean')
    cbs = w.var('Sigma')
    cba = w.var("alpha2")
    cbn = w.var('n2')

    expc = w.var('c')

    disp_par_mass = RooArgSet(ns, nb, cbm, cbs, cba, cbn)

    # Now make the frame, plot the dataset and the pdfs.
    myframe = rvm.frame(RooFit.Title(''), RooFit.Bins(60))
    
    rds.plotOn(myframe)
    pdf.plotOn(myframe, RooFit.Components('bkg_E'), RooFit.LineColor(kRed), RooFit.LineStyle(kDashed))
    pdf.plotOn(myframe, RooFit.Components('sig_E'), RooFit.LineColor(kGreen+3), RooFit.LineStyle(kDashed))
    pdf.plotOn(myframe, RooFit.LineColor(kBlue))
    
    cbm.SetName('#mu')
    cbs.SetName('#sigma')

    #pdf.paramOn(myframe, RooFit.Layout(0.175, 0.2, 0.45),
    #            RooFit.Parameters( disp_par_mass),
    #            RooFit.Format('NEAU', RooFit.AutoPrecision(1)))
    #else:
    pdf.paramOn(myframe, RooFit.Layout(0.5, 0.85, 0.93),
                RooFit.Parameters( disp_par_mass),
                RooFit.Format('NEAU', RooFit.AutoPrecision(1)))
    
    myframe.getAttFill().SetLineColor(0)
    myframe.getAttFill().SetTextSize(0.05)
    
    myframe.GetXaxis().SetLabelSize(0)
    myframe.GetXaxis().SetLabelOffset(999)
    myframe.GetXaxis().SetTitleSize(0)
    myframe.GetXaxis().SetTitleOffset(999)
    myframe.GetXaxis().SetTickLength(0.055)

    myframe.GetYaxis().SetLabelSize(0.058)
    myframe.GetYaxis().SetRangeUser(0.001, myframe.GetMaximum()*1.01)
    myframe.GetYaxis().SetTitleSize(0.065)
    myframe.GetYaxis().SetTitleOffset(0.95)

    myframe.GetXaxis().SetTitle('M(D_{s}#gamma) [MeV/c^{2}]')
    
    pullHist = myframe.pullHist()
    pullHist.SetLineColor(kWhite)
    
    pullFrame = rvm.frame()
    pullFrame.SetLineColor(kWhite)
    pullFrame.addPlotable(pullHist, 'B')
    pullFrame.SetTitle("")
    pullFrame.Print()

    pullFrame.GetXaxis().SetTitle('M(D_{s}#gamma) [MeV/c^{2}]')
    pullFrame.GetXaxis().SetLabelSize(0.12)
    pullFrame.GetXaxis().SetTitleSize(0.134)
    pullFrame.GetXaxis().SetTitleOffset(1.2)
    pullFrame.GetXaxis().SetTickLength(0.1)
    
    pullFrame.GetYaxis().SetTitle('Residual pull')
    pullFrame.GetYaxis().SetTitleSize(0.13)
    pullFrame.GetYaxis().SetTitleOffset(0.44)
    pullFrame.GetYaxis().SetLabelSize(0.1)
    pullFrame.GetYaxis().SetRangeUser(-4.99,4.99)
    pullFrame.GetYaxis().SetNdivisions(9)
    
    pullFrame.SetMarkerColor(0)
    pullFrame.SetMarkerSize(0)
    pullFrame.SetLineColor(kWhite)
    
    c = TCanvas('c','c',800,600)
    c.cd()
    
    p1 = TPad('p1','p1',0.0,0.35,1.0,1.0)
    p2 = TPad('p2','p2',0.0,0.0,1.0,0.35)

    p1.SetBottomMargin(0)
    p1.SetRightMargin(0.05)
    p1.SetTickx(0)
    p2.SetTopMargin(0)
    p2.SetBottomMargin(0.4)
    p2.SetRightMargin(0.05)
    p2.Draw()
    p1.Draw()
    
    p1.cd()
    myframe.Draw()
    
    gStyle.SetLineWidth(1)
    gStyle.SetErrorX(0.0)
    
    p2.cd()
    pullFrame.Draw()
    
    l=TLine()
    l.SetLineColor(2)
    l.SetLineStyle(2)
    l.SetLineWidth(1)
    l.DrawLine( rvm.getMin(), 3,
                rvm.getMax(), 3 )
    l.DrawLine( rvm.getMin(), -3,
                rvm.getMax(), -3 )
    l.SetLineColor(kBlack)
    l.SetLineStyle(1)
    l.DrawLine( rvm.getMin(), 0,
                rvm.getMax(), 0 )

    # Name it and save it
    plotName = 'DsstarFit_%s_%s.eps' %(dataTag, pol)
    c.SaveAs(plotName)
