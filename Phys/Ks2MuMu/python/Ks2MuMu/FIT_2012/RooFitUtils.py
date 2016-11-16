#!/usr/bin/env python
# =============================================================================
# @file   RooFitUtils.py
# @author Albert Puig (albert.puig@epfl.ch)
# @date   15.02.2013
# =============================================================================

from uuid import uuid4
from math import sqrt, log
import ROOT
from pdb import set_trace

class ResidualPlot(object):
    def __init__(self, title, frame):
        self.title = title
        self._id = str(uuid4())
        self._frame = frame
        self.residualHisto = None
        self.pullHisto = None
        self.alphaLabel = None
        self.canvas = None
        self.pullCanvas = None
        self.objects = {}
        self.boxes = []
        self._boxes = []

    def plot(self, bigLabels=False, removeTitle=True, residualBand=False, yLogScale=False, statusLabel=None, labelPosition="L"):
        def _setMargins(pad):
            pad.SetBottomMargin(0.1)
            pad.SetLeftMargin(0.13)
            pad.SetTopMargin(0.05)
            pad.SetRightMargin(0.05)

        self.canvas = ROOT.TCanvas("{0}_{1}".format(self.title, self._id), self.title, 800, 700)
        padHisto, padResid = self.prepareCanvas(bool(self.residualHisto))
        if removeTitle:
            ROOT.gStyle.SetOptTitle(0)
        if padHisto:
            if removeTitle:
                padHisto.SetTitle("")
            padHisto.cd()
            _setMargins(padHisto)
        _setMargins(self.canvas)
        fXAxis = self._frame.GetXaxis()
        fYAxis = self._frame.GetYaxis()
        if bigLabels:
            fXAxis.SetTitleOffset(1.0)
            fXAxis.SetTitleSize(0.045)
            fXAxis.SetLabelSize(0.045)
            fYAxis.SetTitleSize(0.045)
            fYAxis.SetLabelSize(0.042)
            fYAxis.SetTitleOffset(1.45)
        else:
            fXAxis.SetTitleOffset(1.0)
            fXAxis.SetTitleSize(0.04)
            fXAxis.SetLabelSize(0.04)
            fYAxis.SetTitleSize(0.04)
            fYAxis.SetLabelSize(0.04)
            fYAxis.SetTitleOffset(1.55)
        self._frame.Draw()
        for boxMin,boxMax in self.boxes:
            box = ROOT.TBox(max(fXAxis.GetXmin(),boxMin),
                                 0,
                                 min(fXAxis.GetXmax(),boxMax),
                                 self._frame.GetMaximum())
            box.SetFillStyle(1001)
            box.SetFillColor(ROOT.kGray)
            line = ROOT.TLine(max(fXAxis.GetXmin(),boxMin),self._frame.GetMaximum(),min(fXAxis.GetXmax(),boxMax),self._frame.GetMaximum())
            self._boxes.append(box)
            self._boxes.append(line)
            box.Draw("same")
            line.Draw("same")
        self._frame.Draw("same")
        if padHisto:
            if yLogScale:
                padHisto.SetLogy()
            if statusLabel:
                from rootpy.plotting.style.lhcb.labels import LHCb_label as lhcb_label
                statusArgs = {'status': statusLabel}
                if statusLabel not in ['final', 'preliminary', 'unofficial']:
                    statusArgs['status'] = 'custom'
                    if statusLabel == 'simulation':
                        statusArgs['text'] = "#splitline{LHCb}{#scale[1.0]{Simulation}}"
                    else:
                        statusArgs['text'] = statusLabel
                statusArgs['pad'] = padHisto
                label, _ = lhcb_label(labelPosition, **statusArgs)
                label.SetFillStyle(0)
        for obj in self.objects.values():
            obj.Draw("same")
        if self.residualHisto:
            fXAxis.CenterTitle()
            fXAxis.SetTitleOffset(0.5)
            fXAxis.SetLabelSize(0)
            padResid.cd()
            padHisto.SetLeftMargin(0.13)
            padHisto.SetBottomMargin(0.07)
            self.upad=padHisto
            padResid.SetRightMargin(0.05)
            padResid.SetLeftMargin(0.13)
            # Axes
            resXaxis = self.residualHisto.GetXaxis()
            resYaxis = self.residualHisto.GetYaxis()
            sr = 1.0/0.2
            #srH = 1.0/0.8
            resXaxis.SetTickLength ( sr * resXaxis.GetTickLength() )
            resXaxis.SetLabelOffset( sr * resXaxis.GetLabelOffset() )
            resXaxis.SetTitleSize    ( 0 )
            resXaxis.SetLabelOffset(0.05)
            resYaxis.SetNdivisions ( 504 )
            if bigLabels:
                fYAxis.SetTitleSize(0.05)
                fXAxis.SetTitleSize(0.05)
                fYAxis.SetLabelSize(0.05)
                fYAxis.SetTitleOffset(1.35)
                resXaxis.SetLabelSize    ( sr * 0.04 )
                resYaxis.SetLabelSize    ( sr * 0.04 )
            else:
                fYAxis.SetTitleSize(0.045)
                fXAxis.SetTitleSize(0.045)
                fYAxis.SetLabelSize(0.045)
                fYAxis.SetTitleOffset(1.45)
                resXaxis.SetLabelSize    ( 0.037*sr )
                resYaxis.SetLabelSize    ( 0.037*sr )
            if not residualBand:
                self.residualHisto.Draw("E1")
            else:
                self.residualHisto.SetFillColor(39)
                self.residualHisto.SetMarkerSize(0.01)
                self.residualHisto.Draw("E3")
            self.lines = self.plotLines(self.residualHisto)
            if self.alphaLabel:
                self.canvas.cd()
                self.alphaLabel.Draw()
                self.canvas.Update()
            padResid.Update()

    def plotPull(self):
        #gStyle.SetOptStat(0)
        #gStyle.SetOptFit(0111)
        self.pullCanvas = ROOT.TCanvas()
        self.pullHisto.GetXaxis().SetTitle("residuals")
        self.pullHisto.Fit('gaus')

    def addResidual(self, histName, curveName, xMin=None, xMax=None, numParams=0):
        histo = self._frame.getHist(histName)
        curve = self._frame.getCurve(curveName)
        xaxis = self._frame.GetXaxis()
        #xaxis = histo.GetXaxis()
        if not histo:
            raise ValueError("Cannot find histo -> %s" % histName)
        if not curve:
            raise ValueError("Cannot find curve -> %s" % curveName)
        # Residual range
        if xMin is None:
            xMin = xaxis.GetXmin()
        if xMax is None:
            xMax = xaxis.GetXmax()
        # Create residual histogram
        self.residualHisto, chisum = self.residualHist(histo, curve, xaxis, (xMin, xMax))
        if numParams > 0:
            dof = self._frame.getHist(histName).GetN() - numParams - 1
            self.alphaLabel = self.calculateAlpha(chisum, dof)
        return chisum

    def prepareCanvas(self, addResidual):
        padHisto = self.canvas.GetListOfPrimitives().At(0)
        padResid = None
        if addResidual:
            self.canvas.Divide(1, 2, 0.01, 0.01)
            padHisto = self.canvas.GetListOfPrimitives().At(0)
            padResid = self.canvas.GetListOfPrimitives().At(1)
            small = 0.07
            r = 0.2
            # Configure the pad for the histo
            padHisto.SetPad(0.,r ,1.0, 1.0)
            # Configure the pad for the residuals
            padHisto.SetBottomMargin(small-0.01)
            padResid.SetPad(0.0, 0.0, 1.0, r)
            padResid.SetBottomMargin(0.25)
            padResid.SetTopMargin(small)
        return padHisto, padResid

    def calculateAlpha(self, chisum, dof):
        #print "chisum",chisum
        #print "dof", dof
        alpha = ROOT.TMath.Prob(chisum, dof)
        alphaStr = "#alpha = %.4f" % alpha
        label = ROOT.TLatex(0.83, 0.2, alphaStr)
        label.SetTextSize(0.03)
        print "I have a chi2 of %s and %s dof, so alpha is %s" % (chisum, dof, alpha)
        return label

    def residualHist(self, data, curve, xAxis, resRange, chisum=0.0):
        #def poisson_errors(N, coverage=0.6827):
        #    alpha = 1.0-coverage
        #    L, U = 0, 0
        #    if N > 0:
                # WORKAROUND (see above)
                #L = ROOT.Math.gamma_quantile(alpha/2, N, 1.)
        #        L = ROOT.Math.gamma_quantile_c((1. - alpha/2), N, 1.)
        #    if N == 0:
        #        U =  ROOT.Math.gamma_quantile_c(alpha,N+1,1)
        #    else:
        #        U = ROOT.Math.gamma_quantile_c(alpha/2,N+1,1)
        #    return L, U

        #def getResidual(datum, pdf):
        #    idatum = int(datum) #ROOT.TMath.Nint(datum) #assumes datum is integer # events
        #    elow, ehigh = poisson_errors(idatum)
        #    if pdf < 0: return 0
        #    delta = datum - pdf
        #    return delta/elow if delta > 0 else delta/ehigh
        def getResidual(datum, pdf):
            chi2 = 0.0
            if pdf > 0:
                chi2 += 2.0 * (pdf-datum)
                if datum > 0:
                    chi2 += 2.0 * datum * log(datum/pdf)
            return sqrt(chi2) if datum > pdf else -sqrt(chi2)

        # Proportion correction
        #r = 0.2
        #sr = 1.0/0.2
        # Histo features
        n = data.GetN()
        #print "N bins: ",n
        xMin = xAxis.GetXmin()
        xMax = xAxis.GetXmax()
        #print xMin, xMax
        # Create residual histo
        residuals = ROOT.TH1F("residuals_{0}".format(self._id), "", n, xMin, xMax)
        pulls     = ROOT.TH1F("pulls_{0}".format(self._id), "", 11, -5.5, 5.5)
        datum = ROOT.Double(0.0)
        pdf     = 0.0
        xBin    = ROOT.Double(0.0)
        resValue = ROOT.Double(0.0)
        # ranges
        rangeMin, rangeMax = resRange
        if curve:
            for bin in range(n):
                data.GetPoint(bin, xBin, datum)
                if xBin < rangeMin or xBin > rangeMax:
                    continue
                pdf = curve.Eval(xBin)
                resValue = getResidual(datum, pdf)
                print xBin, datum, pdf, '-->', resValue
                chisum += resValue*resValue
                #print datum, pdf
                #print "chisum:", chisum
                #print "Setting bin: ", bin+1, resValue
                residuals.SetBinContent(bin+1, resValue)
                residuals.SetBinError(bin+1, 1.0)
                pulls.Fill(resValue)
        # Cosmetics
        residuals.SetMinimum        ( -5.     )
        residuals.SetMaximum        (    5.     )
        residuals.SetStats            ( False )
        residuals.SetMarkerStyle( 20        )
        residuals.SetMarkerSize ( 1        )
        self.pullHisto = pulls
        return residuals, chisum

    def plotLines(self, residHisto):
        xMin = residHisto.GetXaxis().GetXmin()
        xMax = residHisto.GetXaxis().GetXmax()
        # Create lines
        uppLine = ROOT.TLine(xMin, 2.0, xMax, 2.0)
        midLine = ROOT.TLine(xMin, 0.0, xMax, 0.0)
        lowLine = ROOT.TLine(xMin, -2.0, xMax, -2.0)
        uppLine.SetLineColor( ROOT.kRed )
        lowLine.SetLineColor( ROOT.kRed )
        uppLine.Draw("same")
        midLine.Draw("same")
        lowLine.Draw("same")
        return uppLine, midLine, lowLine

    def getHistoPad(self):
        return self.canvas.GetListOfPrimitives().At(0) if self.canvas else None

    def getResidualPad(self):
        return self.canvas.GetListOfPrimitives().At(1) if self.canvas and self.residualHisto else None

    def addObject(self, obj, name):
        self.objects[name] = obj

    def getObject(self, name):
        return self.objects.get(name, self.objects.get(name, None))

    def addBox(self, binMin, binMax):
        if binMax <= binMin:
            return
        xMin = self._frame.GetXaxis().GetXmin()
        xMax = self._frame.GetXaxis().GetXmax()
        if binMin > xMin or binMax < xMax:
            self.boxes.append((binMin,binMax))

    def addLeftLabel(self, text):
        # Add MC label
        labelMC = ROOT.TLatex(0.17, 0.85, text)
        labelMC.SetTextSize(labelMC.GetTextSize()*1.8)
        labelMC.SetNDC(True)
        self.addObject(labelMC, text)

    def fixYLabel(self, histo_name):
        histo = self._frame.getHist(histo_name)
        self._frame.SetYTitle(histo.getYAxisLabel().replace('Events', 'Candidates'))


# EOF
